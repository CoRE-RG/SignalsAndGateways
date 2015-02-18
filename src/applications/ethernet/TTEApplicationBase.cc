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

#include "TTEApplicationBase.h"
#include "CoRE4INET_Incoming.h"
#include "CoRE4INET_CTFrame.h"
#include "CoRE4INET_CTBuffer.h"
#include "CoRE4INET_BGBuffer.h"
#include "MultipleFieldSequenceMessage.h"
#include "TTBufferEmpty_m.h"

using namespace CoRE4INET;

namespace SignalsAndGateways {

Define_Module(TTEApplicationBase);

TTEApplicationBase::TTEApplicationBase() {

}

TTEApplicationBase::~TTEApplicationBase() {

}

void TTEApplicationBase::initialize(){
    CTApplicationBase::initialize();
}

void TTEApplicationBase::handleMessage(cMessage *msg) {
    CTApplicationBase::handleMessage(msg);

    if(dynamic_cast<TTBufferEmpty*>(msg) != 0){
            delete msg;
    }else if(msg->arrivedOn("TTin") || msg->arrivedOn("RCin") || msg->arrivedOn("in")){
        TransportMessage *transFrame = new TransportMessage();
        EV << getFullName()<< ": TransportFrame created!";
        transFrame->encapsulate(dynamic_cast<cPacket*>(msg));
        if(transFrame){
            send(transFrame, "ethInterface$o");
            EV << getFullName()<< ": Message send from gatewayApp to gatewayBase" << endl;
        }
    }else if(msg->arrivedOn("ethInterface$i")){
        TransportMessage *transFrame = dynamic_cast<TransportMessage*>(msg);
        if(strcmp(transFrame->getBackboneTransferType(), "BE") == 0){
            inet::EthernetIIFrame *bgFrame = dynamic_cast<inet::EthernetIIFrame*>(transFrame->decapsulate());
            for (std::list<BGBuffer*>::iterator buf = bgbuffers.begin(); buf != bgbuffers.end(); buf++) {
                sendDirect(bgFrame->dup(), (*buf)->gate("in"));
            }
            delete bgFrame;
        }else if(strcmp(transFrame->getBackboneTransferType(), "AVB") == 0){
            //TODO: AVB transfer
        }else {
            CTFrame *ctFrame = dynamic_cast<CTFrame*>(transFrame->decapsulate());
            std::list<CoRE4INET::CTBuffer*> buffer = ctbuffers[ctFrame->getCtID()];
            for(std::list<CoRE4INET::CTBuffer*>::iterator buf = buffer.begin(); buf!=buffer.end(); buf++){
                Incoming *in = dynamic_cast<Incoming *>((*buf)->gate("in")->getPathStartGate()->getOwner());
                sendDirect(ctFrame->dup(), in->gate("in"));
            }
            delete ctFrame;
        }
        delete transFrame;
    }
}

}
