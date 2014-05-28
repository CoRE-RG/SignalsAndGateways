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

#include "AVBGatewaySourceApplication.h"
#include "AVBTrafficSourceApp.h"
#include "HelperFunctions.h"
#include <SRPFrame_m.h>
#include <AVBFrame_m.h>
#include <Timer.h>
#include <ModuleAccess.h>
#include "CoRE4INETDefs.h"

#include "SRPTable.h"

Define_Module(AVBGatewaySourceApplication);
using namespace CoRE4INET;

void AVBGatewaySourceApplication::sendAVBFrame()
{

//    char name[10];
//    sprintf(name, "Stream %ld", streamID);
//    AVBFrame *outFrame = new AVBFrame(name);
//    outFrame->setStreamID(streamID);
//    outFrame->setDest(multicastMAC);
//
//    cPacket *payloadPacket = new cPacket;
//    payloadPacket->setByteLength(payload);
//    outFrame->encapsulate(payloadPacket);
////Padding
//    if (outFrame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
//    {
//        outFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
//    }
//    sendDirect(outFrame, avbOutCTC->gate("in"));
//
////class measurement interval = 125us
//    simtime_t tick = check_and_cast<Oscillator*>(findModuleWhereverInNode("oscillator", getParentModule()))->getTick();
//    simtime_t interval = SR_CLASS_A_INTERVAL / intervalFrames;
//
////double interval = (AVB_CLASSMEASUREMENTINTERVAL_US / intervalFrames) / 1000000.00;
//    SchedulerTimerEvent *event = new SchedulerTimerEvent("API Scheduler Task Event", TIMER_EVENT);
//
//    event->setTimer((uint64_t) ceil(interval / tick));
//    event->setDestinationGate(gate("schedulerIn"));
//    getTimer()->registerEvent(event);
}
