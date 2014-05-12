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
        dispatcher = msg->getSenderModule();
        FieldSequenceMessage *fieldSequence = dynamic_cast<FieldSequenceMessage*>(msg);
        char buf[32];
        //simtimeToStr(simTime(),buf);
        simtime_t test0 = timerEvent->getTimestamp();
        simtime_t test1 = timerEvent->getTimestamp()-simTime();
        simtime_t test2 = fieldSequence->getMaxWaitingTime();
        simtime_t test3 = test1 - test2;
        if(not(timerEvent->isScheduled()) || ((timerEvent->getTimestamp()-simTime()) > fieldSequence->getMaxWaitingTime())){
            cancelEvent(timerEvent);
            simtime_t timerValue = simTime()+SimTime(fieldSequence->getMaxWaitingTime()/mili);
            timerEvent->setTimestamp(timerValue);

            EV << "Max waiting time: " << fieldSequence->getMaxWaitingTime() << " timerValue: " << timerValue << endl;
            scheduleAt(timerValue, timerEvent);
        }
        buffer.enqueue(fieldSequence);

    }else if(msg == timerEvent){
        MultipleFieldSequenceMessage *multiFieldSequence = new MultipleFieldSequenceMessage();
        while(not(buffer.isEmpty())){
            multiFieldSequence->pushFieldSequence(buffer.dequeue()->getTransportFrame());
        }
        buffer.clear();
        sendDirect(multiFieldSequence, dispatcher, "triggerIn");
    }
}
