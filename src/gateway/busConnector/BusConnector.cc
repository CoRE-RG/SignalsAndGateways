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

#include "BusConnector.h"
#include "InterConnectMsg_m.h"
#include "TransportMessage_m.h"
#include "Utility.h"
#include "CanDataFrame_m.h"

Define_Module(BusConnector);

using namespace std;
using namespace FiCo4OMNeT;

void BusConnector::initialize()
{
    for(int i = 0; i < gate("busConnect$i",0)->getVectorSize(); i++){
        string busName = gate("busConnect$o",i)->getPathEndGate()->getOwnerModule()->getParentModule()->gate("gate$o")->getPathEndGate()->getOwnerModule()->getParentModule()->getParentModule()->getName();
        this->nameGateMapping.insert(std::pair<std::string, cGate*>(busName, gate("busConnect$o",i)));
    }
}

void BusConnector::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("in")){
        InterConnectMsg *interDataStructure = dynamic_cast<InterConnectMsg*>(msg);
        cXMLElementList routingData =  interDataStructure->getRoutingData();
        CanDataFrame *canDataFrame = dynamic_cast<CanDataFrame*>(interDataStructure->decapsulate());
//        if(routingData){
            cXMLElementList destinations;
            for(auto &element : routingData){
                if(strcmp(element->getTagName(), "destination") == 0){
                    destinations = element->getParentNode()->getChildrenByTagName("destination");
                }
            }
            for(auto &element : destinations){
                string destinationType = element->getFirstChildWithTag("destinationType")->getNodeValue();
                UTLTY::Utility::stripNonAlphaNum(destinationType);
                string destinationBusID = element->getFirstChildWithTag("destinationBusID")->getNodeValue();
                UTLTY::Utility::stripNonAlphaNum(destinationBusID);
                cGate *currentGate = getBusGate(destinationBusID);
                if((strcmp(destinationType.c_str(), "can") == 0) && currentGate != NULL){
                    TransportMessage *transportMsg = new TransportMessage;
                    transportMsg->encapsulate(canDataFrame->dup());
                    send(transportMsg, currentGate);
                }else{
                    opp_error("BusConnector could not resolve the destinationBusID for this CanDataFrame! Make sure that the values in the RoutingTable are correct!");
                }

            }
//        }else{
//            opp_error("BusConnector could not retrieve the RoutingData from InterConnectMessage!");
//        }
        delete canDataFrame;
    }else if(msg->arrivedOn("busConnect$i")){
        send(msg, "out");
    }
}

cGate *BusConnector::getBusGate(std::string gateName){
    Map::const_iterator pos = this->nameGateMapping.find(gateName);
    cGate *value = NULL;
    if(pos == nameGateMapping.end()){
        value = NULL;
    }else{
        value = pos->second;
    }
    return value;
}

