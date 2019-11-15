//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "signalsandgateways/gateway/buffering/AccumulationGatewayBuffering.h"

using namespace FiCo4OMNeT;
using namespace std;

namespace SignalsAndGateways {

Define_Module(AccumulationGatewayBuffering);

AccumulationGatewayBuffering::~AccumulationGatewayBuffering() {
    for (map<cMessage*, simtime_t>::iterator it = scheduledTimes.begin();
            it != scheduledTimes.end(); ++it) {
        if (it->first) {
            cancelAndDelete(it->first);
        }
    }
}

void AccumulationGatewayBuffering::initialize() {
    handleParameterChange(nullptr);
    readConfigXML();

    size_t numPools = scheduledHoldUpTimes.size();
    for (size_t i = 0; i < numPools; i++) {
        string strBufHoldUpTime = "pool" + to_string(i) + "HoldUpTime";
        string strBufPoolSize = "pool" + to_string(i) + "MessageSize";

        simsignal_t signalHoldUpTime = registerSignal(strBufHoldUpTime.c_str());
        cProperty *statisticTemplateHoldUpTime = getProperties()->get(
                "statisticTemplate", "poolHoldUpTime");
        getEnvir()->addResultRecorders(this, signalHoldUpTime, strBufHoldUpTime.c_str(),
                statisticTemplateHoldUpTime);
        poolHoldUpTimeSignals.push_back(signalHoldUpTime);

        simsignal_t signalPoolSize = registerSignal(strBufPoolSize.c_str());
        cProperty *statisticTemplatePoolSize = getProperties()->get(
                "statisticTemplate", "poolMessageSize");
        getEnvir()->addResultRecorders(this, signalPoolSize, strBufPoolSize.c_str(),
                statisticTemplatePoolSize);
        poolSizeSignals.push_back(signalPoolSize);
    }
}

void AccumulationGatewayBuffering::handleParameterChange(const char* parname) {

    if (!parname || !strcmp(parname, "gatewayID"))
    {
        this->gatewayID = par("gatewayID").stringValue();
        if(this->gatewayID.empty() || !strcmp(this->gatewayID.c_str(), "auto")){
            //auto create id!
            this->gatewayID = this->getParentModule()->getParentModule()->getName();
        }
    }
}

void AccumulationGatewayBuffering::readConfigXML() {
    cXMLElement* xmlDoc = par("configXML").xmlValue();
    string gatewayName = this->gatewayID;
    string xpath = "/config/gateway[@id='" + gatewayName + "']/buffering";
    cXMLElement* xmlBuffering = xmlDoc->getElementByPath(xpath.c_str(), xmlDoc);
    if (xmlBuffering) {
        cXMLElementList xmlPools = xmlBuffering->getChildrenByTagName("pool");
        for (size_t i = 0; i < xmlPools.size(); i++) {
            cMessagePointerList* poolList = new cMessagePointerList();
            cMessage* holdUpTimeEvent = new cMessage();
            scheduledHoldUpTimes.insert(
                    pair<cMessagePointerList*, cMessage*>(poolList,
                            holdUpTimeEvent));
            scheduledTimes.insert(
                    pair<cMessage*, simtime_t>(holdUpTimeEvent, 0));
            poolArrivalTimes.insert(
                    pair<cMessagePointerList*, list<simtime_t>>(poolList,
                            list<simtime_t>()));
            cXMLElementList xmlHoldUpTimes = xmlPools[i]->getChildren();
            for (size_t j = 0; j < xmlHoldUpTimes.size(); j++) {
                simtime_t holdUpTime = SimTime::parse(
                        xmlHoldUpTimes[j]->getAttribute("time"));
                cXMLElementList xmlPoolMessages =
                        xmlHoldUpTimes[j]->getChildren();
                for (size_t k = 0; k < xmlPoolMessages.size(); k++) {
                    unsigned int canID = static_cast<unsigned int>(atoi(
                            xmlPoolMessages[k]->getAttribute("canId")));
                    poolMap.insert(
                            pair<unsigned int, cMessagePointerList*>(canID,
                                    poolList));
                    holdUpTimes.insert(
                            pair<unsigned int, simtime_t>(canID, holdUpTime));
                }
            }
        }
    }
}

void AccumulationGatewayBuffering::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        cMessagePointerList* poolList = getPoolList(msg);
        unsigned int poolID = getPoolID(poolList);
        emitSignals(poolList);
        PoolMessage* poolMsg = new PoolMessage(("Pool " + to_string(poolID)).c_str());
        poolMsg->setPool(*poolList);
        poolList->clear();
        send(poolMsg, gate("out"));
    } else if (CanDataFrame* dataFrame = dynamic_cast<CanDataFrame*>(msg)) {
        unsigned int canID = dataFrame->getCanID();
        cMessagePointerList* poolList;
        poolList = getPoolList(canID);
        if (poolList != nullptr) {
            cMessage* poolHoldUpTimeEvent = getPoolHoldUpTimeEvent(poolList);
            simtime_t IDHoldUpTime = getIDHoldUpTime(canID);
            if (poolList->empty()
                    || (IDHoldUpTime
                            < getCurrentPoolHoldUpTime(poolHoldUpTimeEvent))) {
                simtime_t eventTime = IDHoldUpTime + simTime();
                cancelEvent(poolHoldUpTimeEvent);
                scheduleAt(eventTime, poolHoldUpTimeEvent);
                scheduledTimes[poolHoldUpTimeEvent] = eventTime;
            }
            poolList->push_back(dataFrame);
            poolArrivalTimes[poolList].push_back(simTime());
        } else {
            send(msg, gate("out"));
        }
    } else if (dynamic_cast<inet::EthernetIIFrame*>(msg)) {
        send(msg, gate("out"));
    }
}

cMessagePointerList* AccumulationGatewayBuffering::getPoolList(
        unsigned int canID) {
    return poolMap[canID];
}

cMessagePointerList* AccumulationGatewayBuffering::getPoolList(
        cMessage* holdUpTimeEvent) {
    map<cMessagePointerList*, cMessage*>::iterator it;
    for (it = scheduledHoldUpTimes.begin(); it != scheduledHoldUpTimes.end();
            ++it) {
        if (it->second == holdUpTimeEvent) {
            return it->first;
        }
    }
    throw 0;
}

simtime_t AccumulationGatewayBuffering::getIDHoldUpTime(unsigned int canID) {
    return holdUpTimes[canID];
}

cMessage* AccumulationGatewayBuffering::getPoolHoldUpTimeEvent(
        cMessagePointerList* poolList) {
    return scheduledHoldUpTimes[poolList];
}

simtime_t AccumulationGatewayBuffering::getCurrentPoolHoldUpTime(
        cMessage* poolHoldUpTimeEvent) {
    simtime_t scheduledTime = scheduledTimes[poolHoldUpTimeEvent];
    return scheduledTime - simTime();
}

void AccumulationGatewayBuffering::emitSignals(cMessagePointerList* poolList) {
    if (simTime() > getSimulation()->getWarmupPeriod()) {
        unsigned int poolID = getPoolID(poolList);
        list<simtime_t>::iterator it;
        for (it = poolArrivalTimes[poolList].begin();
                it != poolArrivalTimes[poolList].end(); ++it) {
            simtime_t holdUpTime = simTime() - *it;
            emit(poolHoldUpTimeSignals[poolID], holdUpTime);
        }
        poolArrivalTimes[poolList].clear();
        emit(poolSizeSignals[poolID], static_cast<unsigned long>(poolList->size()));
    }
}

unsigned int AccumulationGatewayBuffering::getPoolID(
        cMessagePointerList* poolList) {
    map<cMessagePointerList*, cMessage*>::iterator it1;
    unsigned int poolID = 0;
    for (it1 = scheduledHoldUpTimes.begin(); it1 != scheduledHoldUpTimes.end();
            ++it1) {
        if (it1->first == poolList) {
            break;
        }
        poolID++;
    }
    return poolID;
}

} //namespace
