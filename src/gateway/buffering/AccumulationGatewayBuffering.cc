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

#include "AccumulationGatewayBuffering.h"

using namespace SignalsAndGateways;
using namespace FiCo4OMNeT;
//using namespace CoRE4INET;

Define_Module(AccumulationGatewayBuffering);

void AccumulationGatewayBuffering::initialize()
{
    // TODO - Generated method body
}

void AccumulationGatewayBuffering::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        std::list<cMessage*>* poolList = getPoolList(msg);
        // jeder pool hat eine eigene hold up time
        // bei self message ist eine abgelaufen und es muss herausgefunden werden für welchen pool die Zeit abgelaufen ist... x_x
        //
    } else if(CanDataFrame* dataFrame = dynamic_cast<CanDataFrame*> (msg)) {
        unsigned int canID = dataFrame->getCanID();
        std::list<cMessage*>* poolList = getPoolList(canID);
        if(poolList != NULL){
            poolList->push_back(dataFrame);
            cMessage* poolHoldUpTimeEvent = getPoolHoldUpTimeEvent(poolList);
            simtime_t IDHoldUpTime = getIDHoldUpTime(canID);
            if (IDHoldUpTime < getCurrentPoolHoldUpTime(poolHoldUpTimeEvent)) {
                simtime_t eventTime = IDHoldUpTime + simTime();
                cancelEvent(poolHoldUpTimeEvent);
                scheduleAt(eventTime,poolHoldUpTimeEvent);
                scheduledTimes.at(poolHoldUpTimeEvent) = eventTime;
            }
        }
        // Pool Liste herausfinden
        // wenn es liste gibt: an Liste anhängen & ggf holuptime anpassen
        //


    } else if(dynamic_cast<EthernetIIFrame*>(msg)) {
        send(msg, gate("out"));
    }
}

std::list<cMessage*>* AccumulationGatewayBuffering::getPoolList(unsigned int canID){
    return & poolMap.at(canID);
}

std::list<cMessage*>* AccumulationGatewayBuffering::getPoolList(cMessage* holdUpTimeEvent){
    std::map<std::list<cMessage*>*,cMessage*>::iterator it;
    for (it = scheduledHoldUpTimes.begin(); it != scheduledHoldUpTimes.end(); it++)
    {
        if (it->second == holdUpTimeEvent) {
            return it->first;
        }
    }
    return NULL;
}

simtime_t AccumulationGatewayBuffering::getIDHoldUpTime(unsigned int canID){
    return holdUpTimes.at(canID);
}

cMessage* AccumulationGatewayBuffering::getPoolHoldUpTimeEvent(std::list<cMessage*>* poolList){
    return scheduledHoldUpTimes.at(poolList);
}

simtime_t AccumulationGatewayBuffering::getCurrentPoolHoldUpTime(cMessage* poolHoldUpTimeEvent){
    simtime_t scheduledTime = scheduledTimes.at(poolHoldUpTimeEvent);
    return scheduledTime - simTime();
}












