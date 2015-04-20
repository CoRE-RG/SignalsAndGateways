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

#include "BaseGatewayRouter.h"

#include <algorithm>

#include "CanDataFrame_m.h"
#include "AVBFrame_m.h"
#include "CoRE4INET_CTFrame.h"

using namespace std;
using namespace FiCo4OMNeT;
using namespace CoRE4INET;

namespace SignalsAndGateways {

Define_Module(BaseGatewayRouter);

const std::string BaseGatewayRouter::CANPREFIX = "can_";
const std::string BaseGatewayRouter::AVBPREFIX = "avb_";
const std::string BaseGatewayRouter::TTEPREFIX = "tte_";
const std::string BaseGatewayRouter::ETHPREFIX = "eth_";

void BaseGatewayRouter::initialize()
{
    droppedFramesSignal = registerSignal("droppedFramesSignal");
    readConfigXML();
}

void BaseGatewayRouter::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("in")){
        vector<int> destinationGateIndices;
        if(CanDataFrame* canFrame = dynamic_cast<CanDataFrame*>(msg)){
            destinationGateIndices = getDestinationGateIndices(canFrame->getArrivalGate()->getIndex(), CANPREFIX + to_string(canFrame->getCanID()));
        }else if(AVBFrame* avbFrame = dynamic_cast<AVBFrame*>(msg)){
            destinationGateIndices = getDestinationGateIndices(avbFrame->getArrivalGate()->getIndex(), AVBPREFIX + to_string(avbFrame->getStreamID()));
        }else if(CTFrame* ctFrame = dynamic_cast<CTFrame*>(msg)){
            destinationGateIndices = getDestinationGateIndices(ctFrame->getArrivalGate()->getIndex(), TTEPREFIX + to_string(ctFrame->getCtID()));
        }else if(inet::EthernetIIFrame* ethernetFrame = dynamic_cast<inet::EthernetIIFrame*>(msg)){
            destinationGateIndices = getDestinationGateIndices(ethernetFrame->getArrivalGate()->getIndex(), ETHPREFIX + ethernetFrame->getDest().str());
        }
        if (destinationGateIndices.empty()) {
            emit(droppedFramesSignal,static_cast<unsigned long>(1));
        }
        for(size_t i=0; i<destinationGateIndices.size(); i++){
            if(destinationGateIndices[i] < gateSize("out")){
                send(msg->dup(), "out", destinationGateIndices[i]);
            }
        }
    }
    delete msg;
}

void BaseGatewayRouter::readConfigXML(){
    cXMLElement* xmlDoc = par("configXML").xmlValue();
    string gatewayName = this->getParentModule()->getParentModule()->getName();
    string xpath = "/config/gateway[@id='" + gatewayName + "']/routing";
    cXMLElement* xmlRouting = xmlDoc->getElementByPath(xpath.c_str(), xmlDoc);
    if(xmlRouting){
        cXMLElementList xmlRoutes = xmlRouting->getChildrenByTagName("route");
        for(size_t i=0; i<xmlRoutes.size(); i++){
            int source = atoi(xmlRoutes[i]->getAttribute("source"));
            int destination = atoi(xmlRoutes[i]->getAttribute("destination"));
            cXMLElementList xmlRouteMessages = xmlRoutes[i]->getChildren();
            for(size_t j=0; j<xmlRouteMessages.size(); j++){
                const char* xmlMessageId;
                xmlMessageId = xmlRouteMessages[j]->getAttribute("canId");
                if(xmlMessageId){
                    string messageID = xmlMessageId;
                    routing[source][destination].push_back(CANPREFIX + messageID);
                }
                xmlMessageId = xmlRouteMessages[j]->getAttribute("streamId");
                if(xmlMessageId){
                    string messageID = xmlMessageId;
                    routing[source][destination].push_back(AVBPREFIX + messageID);
                }
                xmlMessageId = xmlRouteMessages[j]->getAttribute("ctId");
                if(xmlMessageId){
                    string messageID = xmlMessageId;
                    routing[source][destination].push_back(TTEPREFIX + messageID);
                }
                xmlMessageId = xmlRouteMessages[j]->getAttribute("dst");
                if(xmlMessageId){
                    string messageID = xmlMessageId;
                    routing[source][destination].push_back(ETHPREFIX + messageID);
                }
            }
        }
    }
}

vector<int> BaseGatewayRouter::getDestinationGateIndices(int sourceIndex, string messageID){
    vector<int> destinationGateIndices;
    for(map<int, list<string> >::iterator it = routing[sourceIndex].begin(); it != routing[sourceIndex].end(); ++it)
    {
        if(find(it->second.begin(), it->second.end(), messageID) != it->second.end()){
            destinationGateIndices.push_back(it->first);
        }
    }
    return destinationGateIndices;
}

} //namespace
