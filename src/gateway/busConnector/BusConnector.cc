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
#include "GlobalGatewayInformation.h"

Define_Module(BusConnector);

using namespace std;
using namespace FiCo4OMNeT;

void BusConnector::initialize()
{
    gatewayName = getParentModule()->getParentModule()->getName();
    GlobalGatewayInformation::registerGateway(gatewayName);
    for(int i = 0; i < gate("busConnect$i",0)->getVectorSize(); i++){
        string busName = gate("busConnect$o",i)->getPathEndGate()->getOwnerModule()->getParentModule()->gate("gate$o")->getPathEndGate()->getOwnerModule()->getParentModule()->getName();
        GlobalGatewayInformation::registerBusGate(gatewayName, busName, gate("busConnect$o",i));
    }
}

void BusConnector::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("in")){
        InterConnectMsg *interDataStructure = dynamic_cast<InterConnectMsg*>(msg);
        cXMLElementList routingData =  interDataStructure->getRoutingData();
        CanDataFrame *canDataFrame = dynamic_cast<CanDataFrame*>(interDataStructure->decapsulate());
        cXMLElementList destinations;
        for(cXMLElementList::iterator element = routingData.begin(); element != routingData.end(); ++element){
            if(strcmp((*element)->getTagName(), "destination") == 0){
                destinations = (*element)->getParentNode()->getChildrenByTagName("destination");
            }
        }
        int destinationCount = 0;
        for(cXMLElementList::iterator element = destinations.begin(); element != destinations.end(); ++element){
            if(destinationCount == interDataStructure->getAssignedDestinationCount()){
                string destinationType = (*element)->getFirstChildWithTag("destinationType")->getNodeValue();
                UTLTY::Utility::stripNonAlphaNum(destinationType);
                string destinationBusID = (*element)->getFirstChildWithTag("destinationBusID")->getNodeValue();
                UTLTY::Utility::stripNonAlphaNum(destinationBusID);
                cGate *currentGate = GlobalGatewayInformation::getBusGate(gatewayName, destinationBusID);
                if((strcmp(destinationType.c_str(), "can") == 0) && currentGate != NULL){
                    TransportMessage *transportMsg = new TransportMessage;
                    transportMsg->encapsulate(canDataFrame->dup());
                    send(transportMsg, currentGate);
                    EV << "CanDataFrame in "+gatewayName+" forwarded to "+destinationBusID << endl;
                }else{
                    string errMsg = "BusConnector of "+gatewayName+" could not resolve the destinationBusID '"+destinationBusID+"' for this CanDataFrame! Modification of that behavior can be made in the RoutingTable!";
                    EV << errMsg << endl;
                }
            }
            destinationCount++;
        }
        delete canDataFrame;
        delete interDataStructure;
    }else if(msg->arrivedOn("busConnect$i")){
        send(msg, "out");
    }
}

