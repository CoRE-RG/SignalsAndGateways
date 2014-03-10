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
#include "Incoming.h"
#include "CTFrame.h"
#include "buffer/base/Buffer.h"

using namespace CoRE4INET;

TTEApplicationBase::TTEApplicationBase() {
    // TODO Auto-generated constructor stub

}

TTEApplicationBase::~TTEApplicationBase() {
    // TODO Auto-generated destructor stub
}

void TTEApplicationBase::initialize(){
    ApplicationBase::initialize();
}

void TTEApplicationBase::handleMessage(cMessage *msg) {
    ApplicationBase::handleMessage(msg);

    if(msg->arrivedOn("TTin"))
    {
        TransportMessage *transFrame = new TransportMessage();
        EV << getFullName()<< ": TransportFrame created!";
        transFrame->encapsulate(dynamic_cast<cPacket*>(msg));
        if(transFrame){
            send(transFrame, "ethInterface$o");
            EV << getFullName()<< ": Message send from gatewayApp to routing";
        }
    }else if(msg->arrivedOn("ethInterface$i")){
        TransportMessage *transFrame = dynamic_cast<TransportMessage*>(msg);
        CTFrame *ctFrame = dynamic_cast<CTFrame*>(transFrame->decapsulate());
        //delete transFrame;

        //Gate für BE-Traffik: getParentModule()->getSubmodule("bgOut");
        std::list<CoRE4INET::Buffer*> buffer = buffers[ctFrame->getCtID()];
        for(std::list<CoRE4INET::Buffer*>::iterator buf = buffer.begin();
                               buf!=buffer.end();buf++){
            Incoming *in = dynamic_cast<Incoming *>((*buf)->gate("in")->getPathStartGate()->getOwner());
            sendDirect(ctFrame->dup(), in->gate("in"));
        }
        delete ctFrame;
    }
    //delete msg;
}
