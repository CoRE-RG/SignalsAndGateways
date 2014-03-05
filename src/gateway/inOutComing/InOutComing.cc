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

#include "InOutComing.h"

Define_Module(InOutComing);

void InOutComing::initialize()
{
    // TODO - Generated method body
}

void InOutComing::handleMessage(cMessage *msg)
{
    TransportMessage *frame = dynamic_cast<TransportMessage*>(msg);
    EV << getFullName()<< ": Message arrival gate: " << msg->getArrivalGate()->getName() << " : Message arrival gate id: " << msg->getArrivalGateId();
    if(msg->arrivedOn("appInterface$i",0)){
        send(frame, "appInterface$o",1);
        EV << getFullName()<< ": Message forwarded to Interface 1";
    }else if(msg->arrivedOn("appInterface$i",1)){
        send(frame, "appInterface$o",0);
        EV << getFullName()<< ": Message forwarded to Interface 0";
    }
    //delete frame;
}
