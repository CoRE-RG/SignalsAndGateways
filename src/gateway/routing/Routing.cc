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

Define_Module(Routing);

void Routing::initialize()
{
    routingTable = par("routingTable").xmlValue();
    items = routingTable->getChildren();
}

void Routing::handleMessage(cMessage *msg)
{
    InterConnectMsg *interDataStructure = dynamic_cast<InterConnectMsg*>(msg);
    cPacket *delivery = interDataStructure->getEncapsulatedPacket();
    if(dynamic_cast<CanDataFrame*>(delivery) != NULL){
        CanDataFrame *canDataFrame = dynamic_cast<CanDataFrame*>(delivery);
        for(auto &element : items){
            const char* elementValue = element->getFirstChildWithTag("source")->getFirstChildWithTag ("sourceObjectID")->getNodeValue();
            if(atoi(elementValue) == canDataFrame->getCanID()){
                interDataStructure->setRoutingData(*element);
                break;
            }
        }
    }else if(dynamic_cast<FieldSequenceMessage*>(delivery) != NULL){ //Muss später in MultipleFieldSequenceMessage geaendert werden!
        FieldSequenceMessage *fieldSequence = dynamic_cast<FieldSequenceMessage*>(delivery);
        for(auto &element : items){
            const char* elementValue = element->getFirstChildWithTag("source")->getFirstChildWithTag ("sourceObjectID")->getNodeValue();
            std::shared_ptr<IdentifierFieldElement> identifierElement = fieldSequence->getTransportFrame().getField<IdentifierFieldElement>();
            if(atoi(elementValue) == identifierElement->getIdentifier()){
                interDataStructure->setRoutingData(*element);
                break;
            }
        }
    }

    send(interDataStructure, "out");
}
