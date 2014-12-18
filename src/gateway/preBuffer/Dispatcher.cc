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

#include "Dispatcher.h"
#include "Utility.h"
#include "InterConnectMsg_m.h"
#include "GlobalGatewayInformation.h"

Define_Module(Dispatcher);

template <typename T>
std::string numberToString ( T number ){
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

void Dispatcher::initialize()
{
    routingTable = par("routingTable").xmlValue();
    items = routingTable->getChildren();
    gatewayName = getParentModule()->getParentModule()->getParentModule()->getName();


    int i = 0;
    for(cXMLElementList::iterator element = items.begin(); element != items.end(); ++element){
        cXMLElement *source = (*element)->getFirstChildWithTag("source");
        std::string sourceBusID = source->getFirstChildWithTag("sourceBusID")->getNodeValue();
        UTLTY::Utility::stripNonAlphaNum(sourceBusID);
        if(GlobalGatewayInformation::checkBusRegistered(gatewayName, sourceBusID)){
            cXMLElementList destinationList = (*element)->getChildrenByTagName("destination");
            for(cXMLElementList::iterator destination = destinationList.begin(); destination != destinationList.end(); ++destination){
                cXMLElementList backboneProperties = (*destination)->getChildrenByTagName("backbone");
                for(cXMLElementList::iterator property = backboneProperties.begin(); property != backboneProperties.end(); ++property){
                    cModule *msgBuffer = getParentModule()->getSubmodule("messageBuffers", i);
                    TimeTriggeredBuffer *currentBuffer = dynamic_cast<TimeTriggeredBuffer*>(msgBuffer);
                    std::string backboneTransferType = (*property)->getFirstChildWithTag("backboneTransferType")->getNodeValue();
                    UTLTY::Utility::stripNonAlphaNum(backboneTransferType);
                    currentBuffer->setDispatchedBackboneTransferType(backboneTransferType);
                    if(strcmp(backboneTransferType.c_str(), "BE") == 0){
                        std::string directMacAdress = (*property)->getFirstChildWithTag("directMacAdress")->getNodeValue();
                        UTLTY::Utility::stripNonAlphaNum(directMacAdress);
                        if(not(GlobalGatewayInformation::checkTimeBufferRegistered(gatewayName, directMacAdress))){
                            currentBuffer->setDispatchedCTID(directMacAdress);
                            GlobalGatewayInformation::registerTimeBuffer(gatewayName, directMacAdress, currentBuffer);
                            i++;
                        }
                    }else{
                        std::string backboneCTID = (*property)->getFirstChildWithTag("backboneCTID")->getNodeValue();
                        UTLTY::Utility::stripNonAlphaNum(backboneCTID);
                        if(not(GlobalGatewayInformation::checkTimeBufferRegistered(gatewayName, backboneCTID))){
                            currentBuffer->setDispatchedCTID(backboneCTID);
                            GlobalGatewayInformation::registerTimeBuffer(gatewayName, backboneCTID, currentBuffer);
                            i++;
                        }
                    }

                }
            }
        }
    }
}

void Dispatcher::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("moduleConnect$i")){
        InterConnectMsg *interDataStructure = dynamic_cast<InterConnectMsg*>(msg);
        std::string key;
        if(strcmp(interDataStructure->getBackboneTransferType(), "BE") == 0){
            key = interDataStructure->getDirectMacAdress();
        }else{
            key = numberToString(interDataStructure->getBackboneCTID());
        }
        TimeTriggeredBuffer *foundBuffer = GlobalGatewayInformation::getTimeBuffer(gatewayName, key);
        FieldSequenceMessage *fieldSequence = dynamic_cast<FieldSequenceMessage*>(interDataStructure->decapsulate());
        if(foundBuffer != NULL){
            sendDirect(fieldSequence, foundBuffer, "bufferIn");
        }else{
            opp_error("Cannot find Pre-Buffer to specified backboneID in Message!");
        }
        delete msg;
    }else if(msg->arrivedOn("triggerIn")){
        MultipleFieldSequenceMessage *multiFieldSequence = dynamic_cast<MultipleFieldSequenceMessage*>(msg);
        InterConnectMsg *interDataStructure = new InterConnectMsg();
        TimeTriggeredBuffer *sendBuffer = dynamic_cast<TimeTriggeredBuffer*>(msg->getSenderModule());
        std::string dispatchedBackboneTransferType = sendBuffer->getDispatchedBackboneTransferType();
        interDataStructure->setBackboneTransferType(dispatchedBackboneTransferType.c_str());
        if(strcmp(dispatchedBackboneTransferType.c_str(), "BE") == 0){
            interDataStructure->setDirectMacAdress((sendBuffer->getDispatchedCTID()).c_str());
        }else{
            interDataStructure->setBackboneCTID(atoi((sendBuffer->getDispatchedCTID()).c_str()));
        }
        interDataStructure->encapsulate(multiFieldSequence);
        send(interDataStructure, "moduleConnect$o");
    }
}
