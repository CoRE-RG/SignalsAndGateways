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

#include "Routing.h"
#include "InterConnectMsg_m.h"
#include "candataframe_m.h"
#include "CTFrame_m.h"
#include "FieldSequenceMessage_m.h"
#include "MultipleFieldSequenceMessage.h"
#include "IdentifierFieldElement.h"
#include "TransportHeaderFieldElement.h"

Define_Module(Routing);

void Routing::initialize()
{
    routingTable = par("routingTable").xmlValue();
    items = routingTable->getChildren();
}

void Routing::handleMessage(cMessage *msg)
{
    InterConnectMsg *interDataStructure = dynamic_cast<InterConnectMsg*>(msg);
    cPacket *delivery = interDataStructure->decapsulate();
    if(dynamic_cast<CanDataFrame*>(delivery) != NULL){
        CanDataFrame *canDataFrame = dynamic_cast<CanDataFrame*>(delivery);
        InterConnectMsg *newInterDateStructure = new InterConnectMsg;
        newInterDateStructure->encapsulate(delivery);
        for(auto &element : items){
            const char* sourceBusID = element->getFirstChildWithTag("source")->getFirstChildWithTag ("sourceBusID")->getNodeValue();
            if(strcmp(sourceBusID, canDataFrame->getNode())){
                const char* sourceObjectID = element->getFirstChildWithTag("source")->getFirstChildWithTag ("sourceObjectID")->getNodeValue();
                if(atoi(sourceObjectID) == canDataFrame->getCanID()){
                    newInterDateStructure->setRoutingData(*element);
                    send(newInterDateStructure, "out");
                    break;
                }
            }

        }
    }else if(dynamic_cast<MultipleFieldSequenceMessage*>(delivery) != NULL){
        MultipleFieldSequenceMessage *multiFieldSequence = dynamic_cast<MultipleFieldSequenceMessage*>(delivery);
        while(multiFieldSequence->getFieldCount() > 0){
            InterConnectMsg *newInterDateStructure = new InterConnectMsg;
            FieldSequenceDataStructure transportFrame = multiFieldSequence->popFieldSequence();
            for(auto &element : items){
                const char* sourceBusID = element->getFirstChildWithTag("source")->getFirstChildWithTag ("sourceBusID")->getNodeValue();
                    std::shared_ptr<TransportHeaderFieldElement> identifierElement = transportFrame.getField<TransportHeaderFieldElement>();
                    if(strcmp(sourceBusID, identifierElement->getStaticBusID())){
                        const char* sourceObjectID = element->getFirstChildWithTag("source")->getFirstChildWithTag ("sourceObjectID")->getNodeValue();
                        std::shared_ptr<IdentifierFieldElement> identifierElement = transportFrame.getField<IdentifierFieldElement>();
                        if(atoi(sourceObjectID) == identifierElement->getIdentifier()){
                            newInterDateStructure->setRoutingData(*element);
                            break;
                        }
                    }
            }
            FieldSequenceMessage *fieldSequence = new FieldSequenceMessage;
            fieldSequence->setTransportFrame(transportFrame);
            newInterDateStructure->encapsulate(fieldSequence);
            send(newInterDateStructure, "out");
        }
    }

    delete interDataStructure;
}
