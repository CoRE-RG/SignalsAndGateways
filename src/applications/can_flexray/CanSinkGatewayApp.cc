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

#include "CanSinkGatewayApp.h"
#include "TransportMessage_m.h"
#include "CanDataFrame_m.h"

using namespace FiCo4OMNeT;

Define_Module(CanSinkGatewayApp);

template <typename T>
std::string numberToString ( T number ){
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

void CanSinkGatewayApp::handleMessage(cMessage *msg) {
    std::string msgClass = msg->getClassName();
    if (msg->arrivedOn("controllerIn")) {
        bufferMessageCounter++;
        if (idle) {
            requestFrame();
        }
    } else if (CanDataFrame *frame = dynamic_cast<CanDataFrame *>(msg)) {
        currentFrameID = frame->getCanID();
        for(unsigned int i = 0; i < frame->getDataArraySize(); i++){
            std::string i_str = numberToString(i);
            frame->setData(i, *i_str.c_str());
        }
        //simtime_t currentTime = simTime();
        //std::string currentTime_str = simtimeToStr(currentTime);

        bufferMessageCounter--;
        TransportMessage *transFrame = new TransportMessage();
        transFrame->setFirstArrivalTimeOnCan(msg->getArrivalTime());
        EV << "CanSinkGatewayApp: firstCanArrivalTime: " << msg->getArrivalTime() << endl;
        transFrame->encapsulate(frame->dup());
        send(transFrame, "busInterfaceOut");
        EV << "TransportMessage with encapsulated 'CanDataFrame' send to 'busInterfaceOut'" << endl;

//        CanInputBuffer *buffer =  //TODO not needed with the current version of multiple sink apps
//                (CanInputBuffer*) (getParentModule()->getSubmodule("bufferIn"));
//        buffer->deleteFrame(currentFrameID);
//        idle = true;

    } else if (msg->isSelfMessage()) {
        CanInputBuffer *buffer = dynamic_cast<CanInputBuffer *>(getParentModule()->getSubmodule("bufferIn"));
        buffer->deleteFrame(currentFrameID);
        if (bufferMessageCounter > 0) {
            requestFrame();
        } else {
            idle = true;
        }
    }
    delete msg;
}
