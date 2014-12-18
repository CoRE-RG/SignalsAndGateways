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
#include "simtime.h"
#define MAX_FRAME_LENGTH 1500

Define_Module(TimeTriggeredBuffer);

void TimeTriggeredBuffer::initialize()
{
    buffer = FieldSequenceBuffer();
    timerEvent = new cMessage("Timer");
}

void TimeTriggeredBuffer::handleMessage(cMessage *msg)
{
    if(dynamic_cast<FieldSequenceMessage*>(msg) != NULL){
        dispatcher = msg->getSenderModule();
        FieldSequenceMessage *fieldSequence = dynamic_cast<FieldSequenceMessage*>(msg);
        simtime_t maxWaitingTime = SimTime::parse(fieldSequence->getMaxWaitingTime());
        simtime_t currentTimerValue = timerEvent->getTimestamp()-simTime();
        if(((timerEvent->getTimestamp()-simTime()) > maxWaitingTime) || not(timerEvent->isScheduled())){
            cancelEvent(timerEvent);
            simtime_t timerValue = simTime()+maxWaitingTime;
            timerEvent->setTimestamp(timerValue);

            EV << "Max waiting time: " << fieldSequence->getMaxWaitingTime() << " timerValue: " << timerValue << endl;
            scheduleAt(timerValue, timerEvent);
        }
        buffer.enqueue(fieldSequence);

    }else if(msg == timerEvent){
        MultipleFieldSequenceMessage *multiFieldSequence = new MultipleFieldSequenceMessage();
        while(not(buffer.isEmpty())){
            FieldSequenceMessage *fieldSequence = buffer.dequeue();
            if(multiFieldSequence->getByteLength()+sizeof(&fieldSequence) < MAX_FRAME_LENGTH){
                multiFieldSequence->pushFieldSequence(fieldSequence->getTransportFrame());
                //multiFieldSequence->pushFieldSequence(fieldSequence->getTransportFrame());
            }else{
                sendDirect(multiFieldSequence->dup(), dispatcher, "triggerIn");
                multiFieldSequence = new MultipleFieldSequenceMessage();
                multiFieldSequence->pushFieldSequence(fieldSequence->getTransportFrame());
                //multiFieldSequence->pushFieldSequence(fieldSequence->getTransportFrame());
            }

            delete fieldSequence;
        }
        buffer.clear();
        EV << "TimeTriggeredBuffer: Size of MultipleFieldSequenceMessage " << multiFieldSequence->getByteLength() << endl;
        sendDirect(multiFieldSequence, dispatcher, "triggerIn");
    }
}

TimeTriggeredBuffer::~TimeTriggeredBuffer(){
    cancelEvent(timerEvent);
    delete timerEvent;
}
