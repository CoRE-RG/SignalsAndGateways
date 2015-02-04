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

#include <DedicatedGatewayMetaData.h>

using namespace std;

DedicatedGatewayMetaData::DedicatedGatewayMetaData() {
    busGateMapping = map<string, cGate*>();
    timeBuffers = map<string, TimeTriggeredBuffer*>();
}

DedicatedGatewayMetaData::~DedicatedGatewayMetaData() {
    // TODO Auto-generated destructor stub
}

void DedicatedGatewayMetaData::registerBusGate(string busName, cGate *gate){
    busGateMapping.insert(pair<string, cGate*>(busName, gate));
}

cGate *DedicatedGatewayMetaData::getBusGate(string busName){
    map<string, cGate*>::const_iterator pos = busGateMapping.find(busName);
    cGate *value = NULL;
    if(pos == busGateMapping.end()){
        value = NULL;
    }else{
        value = pos->second;
    }
    return value;
}

bool DedicatedGatewayMetaData::checkBusRegistered(string busName){
    bool registered = false;
    map<string, cGate*>::const_iterator pos = busGateMapping.find(busName);
    if(pos != busGateMapping.end()){
        registered = true;
    }
    return registered;
}

void DedicatedGatewayMetaData::registerTimeBuffer(string identifier, TimeTriggeredBuffer *timeBuffer){
    timeBuffers.insert(map<string, TimeTriggeredBuffer*>::value_type(identifier, timeBuffer));
}

TimeTriggeredBuffer *DedicatedGatewayMetaData::getTimeBuffer(string identifier){
    map<string, TimeTriggeredBuffer*>::const_iterator pos = timeBuffers.find(identifier);
    TimeTriggeredBuffer *value = NULL;
    if(pos == timeBuffers.end()){
        value = NULL;
    }else{
        value = pos->second;
    }
    return value;
}

bool DedicatedGatewayMetaData::checkTimeBufferRegistered(string identifier){
    bool registered = false;
    map<string, TimeTriggeredBuffer*>::const_iterator pos = timeBuffers.find(identifier);
    if(pos != timeBuffers.end()){
        registered = true;
    }
    return registered;
}
