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

#include "PreBuffer.h"
#include "InterConnectMsg_m.h"
#include "FieldSequenceMessage_m.h"
#include "MultipleFieldSequenceMessage.h"
#include "CanDataFrame_m.h"

namespace SignalsAndGateways {

Define_Module(PreBuffer);

void PreBuffer::initialize()
{

}

void PreBuffer::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("in")){
        InterConnectMsg *interDataStructure = dynamic_cast<InterConnectMsg*>(msg);
        cPacket *delivery = interDataStructure->decapsulate();
        if(dynamic_cast<FieldSequenceMessage*>(delivery) != NULL){
            if(interDataStructure->getMessageAccumulation()){
                interDataStructure->encapsulate(delivery);
                send(interDataStructure, "moduleConnect$o");
            }else{
                FieldSequenceMessage *fieldSequence = dynamic_cast<FieldSequenceMessage*>(delivery);
                MultipleFieldSequenceMessage *multiFieldSequence = new MultipleFieldSequenceMessage;
                multiFieldSequence->pushFieldSequence(fieldSequence->getTransportFrame());
                interDataStructure->encapsulate(multiFieldSequence);
                send(interDataStructure, "out");
                delete fieldSequence;
            }

        }else if(dynamic_cast<FiCo4OMNeT::CanDataFrame*>(delivery) != NULL){
            interDataStructure->encapsulate(delivery);
            send(interDataStructure, "out");
        } else {
            delete delivery;
        }

    }else if(msg->arrivedOn("moduleConnect$i")){
        InterConnectMsg *interDataStructure = dynamic_cast<InterConnectMsg*>(msg);
        send(interDataStructure, "out");
    } else {
        delete msg;
    }
}

}

