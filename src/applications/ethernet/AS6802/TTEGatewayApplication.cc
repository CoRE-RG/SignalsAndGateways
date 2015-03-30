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

#include "TTEGatewayApplication.h"
#include "CoRE4INET_Incoming.h"
#include "AVBFrame_m.h"
#include "CoRE4INET_CTFrame.h"
#include "CoRE4INET_CTBuffer.h"
#include "CoRE4INET_BGBuffer.h"
#include "TTBufferEmpty_m.h"

using namespace CoRE4INET;

namespace SignalsAndGateways {

Define_Module(TTEGatewayApplication);

TTEGatewayApplication::TTEGatewayApplication() {

}

TTEGatewayApplication::~TTEGatewayApplication() {

}

void TTEGatewayApplication::initialize(){
    CTApplicationBase::initialize();
}

void TTEGatewayApplication::handleMessage(cMessage *msg) {
    CTApplicationBase::handleMessage(msg);

    if(dynamic_cast<TTBufferEmpty*>(msg) != 0){
        delete msg;
    }else if(msg->arrivedOn("TTin") || msg->arrivedOn("RCin") || msg->arrivedOn("in")){
        send(msg, "upperLayerOut");
    }else if(msg->arrivedOn("upperLayerIn")){
        if(AVBFrame* avbFrame = dynamic_cast<AVBFrame*>(msg)){
            //TODO AVB transfer
        }else if(CTFrame* ctFrame = dynamic_cast<CTFrame*>(msg)){
            std::list<CoRE4INET::CTBuffer*> buffer = ctbuffers[ctFrame->getCtID()];
            for(std::list<CoRE4INET::CTBuffer*>::iterator buf = buffer.begin(); buf!=buffer.end(); buf++){
                Incoming *in = dynamic_cast<Incoming *>((*buf)->gate("in")->getPathStartGate()->getOwner());
                sendDirect(ctFrame->dup(), in->gate("in"));
            }
            delete ctFrame;
        }else if(inet::EthernetIIFrame* ethernetFrame = dynamic_cast<inet::EthernetIIFrame*>(msg)){
            for (std::list<BGBuffer*>::iterator buf = bgbuffers.begin(); buf != bgbuffers.end(); buf++) {
                sendDirect(ethernetFrame->dup(), (*buf)->gate("in"));
            }
            delete ethernetFrame;
        }
    }else{
        delete msg;
    }
}

}
