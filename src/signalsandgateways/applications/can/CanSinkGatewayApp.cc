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

//FiCo4OMNeT
#include "fico4omnet/buffer/can/CanInputBuffer.h"
//Auto-generated messages
#include "fico4omnet/linklayer/can/messages/CanDataFrame_m.h"

using namespace FiCo4OMNeT;

namespace SignalsAndGateways {

Define_Module(CanSinkGatewayApp);

void CanSinkGatewayApp::handleMessage(cMessage *msg) {
    if (msg->arrivedOn("controllerIn")) {
        bufferMessageCounter++;
        if (idle) {
            requestFrame();
        }
        delete msg;
    } else if (CanDataFrame *frame = dynamic_cast<CanDataFrame *>(msg)) {
        currentFrameID = frame->getCanID();
        bufferMessageCounter--;
        send(frame, "out");
    } else if (msg->isSelfMessage()) {
        CanInputBuffer *buffer = dynamic_cast<CanInputBuffer *>(getParentModule()->getSubmodule("bufferIn"));
        buffer->deleteFrame(currentFrameID);
        if (bufferMessageCounter > 0) {
            requestFrame();
        } else {
            idle = true;
        }
        delete msg;
    }
}

}
