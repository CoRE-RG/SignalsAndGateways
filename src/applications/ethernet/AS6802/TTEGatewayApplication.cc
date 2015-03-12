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
#include "CoRE4INET_CTFrame.h"
#include "CoRE4INET_CTBuffer.h"
#include "CoRE4INET_BGBuffer.h"
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
        send(msg, "upperLayerOut");
    }else if(msg->arrivedOn("upperLayerIn")){
        //TODO if BE
        //TODO if AVB
        //TODO if CT
    }else{
        delete msg;
    }
}

}
