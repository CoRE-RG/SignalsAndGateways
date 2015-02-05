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

#include <GlobalGatewayInformation.h>

using namespace std;

namespace SignalsAndGateways {

map<string, DedicatedGatewayMetaData> GlobalGatewayInformation::gateways = map<string, DedicatedGatewayMetaData>();

GlobalGatewayInformation::GlobalGatewayInformation() {

}

GlobalGatewayInformation::~GlobalGatewayInformation() {

}

void GlobalGatewayInformation::registerGateway(string gatewayName){
    gateways.insert(std::pair<string, DedicatedGatewayMetaData>(gatewayName, DedicatedGatewayMetaData()));
}

void GlobalGatewayInformation::registerBusGate(string gatewayName, string busName, cGate *gate){
    DedicatedGatewayMetaData *metaData = findGateway(gatewayName);
    metaData->registerBusGate(busName, gate);
}

bool GlobalGatewayInformation::checkBusRegistered(string gatewayName, string busName){
    DedicatedGatewayMetaData *metaData = findGateway(gatewayName);
    bool registered = false;
    if(metaData->checkBusRegistered(busName)){
        registered = true;
    }
    return registered;
}

cGate *GlobalGatewayInformation::getBusGate(string gatewayName, string busName){
    DedicatedGatewayMetaData *metaData = findGateway(gatewayName);
    return metaData->getBusGate(busName);
}

void GlobalGatewayInformation::registerTimeBuffer(string gatewayName, string identifier, TimeTriggeredBuffer *timeBuffer){
    DedicatedGatewayMetaData *metaData = findGateway(gatewayName);
    metaData->registerTimeBuffer(identifier, timeBuffer);
}

TimeTriggeredBuffer *GlobalGatewayInformation::getTimeBuffer(string gatewayName, string identifier){
    DedicatedGatewayMetaData *metaData = findGateway(gatewayName);
    return metaData->getTimeBuffer(identifier);
}

bool GlobalGatewayInformation::checkTimeBufferRegistered(string gatewayName, string identifier){
    DedicatedGatewayMetaData *metaData = findGateway(gatewayName);
    bool registered = false;
    if(metaData->checkTimeBufferRegistered(identifier)){
        registered = true;
    }
    return registered;
}

DedicatedGatewayMetaData *GlobalGatewayInformation::findGateway(string gatewayName){
    map<string, DedicatedGatewayMetaData>::iterator pos = gateways.find(gatewayName);
    DedicatedGatewayMetaData *value = NULL;
    if(pos == gateways.end()){
        throw cRuntimeError(("Gateway '"+gatewayName+"' is not registered! Please check your network setup!").c_str());
    }else{
        value = &(pos->second);
    }
    return value;
}

}
