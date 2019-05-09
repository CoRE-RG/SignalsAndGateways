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

#include "signalsandgateways/applications/ethernet/EthernetGatewayApplication.h"

#include "core4inet/incoming/base/Incoming.h"
#include "core4inet/linklayer/ethernet/avb/AVBFrame_m.h"
#include "core4inet/linklayer/ethernet/AS6802/CTFrame.h"
#include "core4inet/buffer/AS6802/CTBuffer.h"
#include "core4inet/buffer/AS6802/TTBufferEmpty_m.h"
#include "core4inet/buffer/base/BGBuffer.h"

//SignalsAndGateways
#include "signalsandgateways/gateway/messages/GatewayAggregationMessage.h"

//FiCo4OMNeT
//Auto-generated messages
#include "fico4omnet/linklayer/can/messages/CanDataFrame_m.h"

using namespace CoRE4INET;
using namespace FiCo4OMNeT;

namespace SignalsAndGateways {

Define_Module(EthernetGatewayApplication);

EthernetGatewayApplication::EthernetGatewayApplication() {

}

EthernetGatewayApplication::~EthernetGatewayApplication() {

}

void EthernetGatewayApplication::initialize(){
    CTApplicationBase::initialize();
}

void EthernetGatewayApplication::handleMessage(cMessage *msg) {
    CTApplicationBase::handleMessage(msg);

    if(dynamic_cast<TTBufferEmpty*>(msg) != nullptr){
        delete msg;
    }else if(msg->arrivedOn("TTin") || msg->arrivedOn("RCin") || msg->arrivedOn("in")){
        send(msg, "upperLayerOut");
    }else if(msg->arrivedOn("upperLayerIn")){
        if(AVBFrame* avbFrame = dynamic_cast<AVBFrame*>(msg)){
            //TODO AVB transfer
            delete avbFrame;
        }else if(CTFrame* ctFrame = dynamic_cast<CTFrame*>(msg)){
            std::list<CoRE4INET::CTBuffer*> buffer = ctbuffers[ctFrame->getCtID()];
            for(std::list<CoRE4INET::CTBuffer*>::iterator buf = buffer.begin(); buf!=buffer.end(); ++buf){
                Incoming *in = dynamic_cast<Incoming *>((*buf)->gate("in")->getPathStartGate()->getOwner());
                sendDirect(ctFrame->dup(), in->gate("in"));
            }
            delete ctFrame;
        }else if(inet::EthernetIIFrame* ethernetFrame = dynamic_cast<inet::EthernetIIFrame*>(msg)){
            for (std::list<BGBuffer*>::iterator buf = bgbuffers.begin(); buf != bgbuffers.end(); ++buf) {
                sendDirect(ethernetFrame->dup(), (*buf)->gate("in"));
            }
            delete ethernetFrame;
        }else if(GatewayAggregationMessage* gwAggrFrame = dynamic_cast<GatewayAggregationMessage*>(msg)){
            //seperate the can messages
            while(UnitMessage* unitMessage = gwAggrFrame->decapUnit()){
                //is this a can message?
                if(CanDataFrame* canFrame = dynamic_cast<CanDataFrame*>(unitMessage->getEncapsulatedPacket())){
                    std::vector<cGate*> gates = _canIdSubMap[canFrame->getCanID()];
                    //check which gates are subscribed
                    for(std::vector<cGate*>::iterator gate = gates.begin(); gate != gates.end(); ++gate){
                        //deliver message to subscriber
                        GatewayAggregationMessage* deliver = new GatewayAggregationMessage();
                        deliver->encapUnit(unitMessage->dup());
                        sendDirect(deliver, *gate);
                    }
                }
                delete unitMessage;
            }
            delete msg;
        }else{
            delete msg;
        }
    }else{
        delete msg;
    }
}

void EthernetGatewayApplication::registerForCANID(unsigned int canID,
        cGate* deliveryGate) {
    _canIdSubMap[canID].push_back(deliveryGate);
}

}
