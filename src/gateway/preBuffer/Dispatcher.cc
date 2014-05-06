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

Define_Module(Dispatcher);

void Dispatcher::initialize()
{
    //Initialisierung der Map notwendig?

    routingTable = par("routingTable").xmlValue();
    items = routingTable->getChildren();
    int i = 0;
    for(auto &element : items){
        for(auto &destination : element->getChildrenByTagName("destination")){
            const char* backboneCTID = destination->getFirstChildWithTag("backboneCTID")->getNodeValue();
            std::string str_backboneCTID = UTLTY::Utility::stripNonAlphaNum(backboneCTID, 10);
            cModule *msgBuffer = getParentModule()->getSubmodule("messageBuffers", i);
            TimeTriggeredBuffer *currentBuffer = dynamic_cast<TimeTriggeredBuffer*>(msgBuffer);
            currentBuffer->setDispatchedCTID(str_backboneCTID);
            timeBuffers.insert(ValuePair(str_backboneCTID, currentBuffer));
            i++;

        }
    }
}

void Dispatcher::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("moduleConnect$i")){
        InterConnectMsg *interDataStructure = dynamic_cast<InterConnectMsg*>(msg);
        std::string key = std::to_string(interDataStructure->getBackboneCTID());
        TTBufferMap::const_iterator bufferPosition = timeBuffers.find(key);
        FieldSequenceMessage *fieldSequence = dynamic_cast<FieldSequenceMessage*>(interDataStructure->decapsulate());
        if(bufferPosition != timeBuffers.end()){
            TimeTriggeredBuffer *foundBuffer =
                    dynamic_cast<TimeTriggeredBuffer*>(bufferPosition->second);
            sendDirect(fieldSequence, foundBuffer, "bufferIn");
        }else{
            opp_error("Cannot find Pre-Buffer to specified backboneID in Message!");
        }
        delete msg;
    }else if(msg->arrivedOn("triggerIn")){
        MultipleFieldSequenceMessage *multiFieldSequence = dynamic_cast<MultipleFieldSequenceMessage*>(msg);
        InterConnectMsg *interDataStructure = new InterConnectMsg();
        TimeTriggeredBuffer *sendBuffer = dynamic_cast<TimeTriggeredBuffer*>(msg->getSenderModule());
        interDataStructure->setBackboneCTID(atoi((sendBuffer->getDispatchedCTID()).c_str()));
        interDataStructure->encapsulate(multiFieldSequence);
        send(interDataStructure, "moduleConnect$o");
    }
}
