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

#include "TimeTriggeredBuffer.h"

Define_Module(TimeTriggeredBuffer);

void TimeTriggeredBuffer::initialize()
{
    buffer = FieldSequenceBuffer();
    timerEvent = new cMessage("Timer");
}

void TimeTriggeredBuffer::handleMessage(cMessage *msg)
{
    if(dynamic_cast<FieldSequenceMessage*>(msg) != NULL){
        FieldSequenceMessage *fieldSequence = dynamic_cast<FieldSequenceMessage*>(msg);
        if((timerEvent->getTimestamp()-simTime()) > fieldSequence->getMaxWaitingTime()){
            cancelEvent(timerEvent);
            timerEvent->setTimestamp(fieldSequence->getMaxWaitingTime());
            scheduleAt(fieldSequence->getMaxWaitingTime(), timerEvent);
        }
        buffer.enqueue(fieldSequence);

    }else if(msg == timerEvent){
        MultipleFieldSequenceMessage *multiFieldSequence = new MultipleFieldSequenceMessage();
        while(not(buffer.isEmpty())){
            multiFieldSequence->pushFieldSequence(buffer.dequeue()->getTransportFrame());
        }
        send(multiFieldSequence, "bufferOut");
    }
}