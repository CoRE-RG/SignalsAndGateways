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

#ifndef DEDICATEDGATEWAYMETADATA_H_
#define DEDICATEDGATEWAYMETADATA_H_

#include "omnetpp.h"
#include "TimeTriggeredBuffer.h"

using namespace std;

typedef map<string, cGate*> GateMap;
//Definition of the map to administrate the TimeTriggerdBuffers
typedef map<string, TimeTriggeredBuffer*> TTBufferMap;
typedef TTBufferMap::value_type ValuePair;

class DedicatedGatewayMetaData {
public:
    DedicatedGatewayMetaData();
    virtual ~DedicatedGatewayMetaData();

    void registerBusGate(string busName, cGate *gate);
    bool checkBusRegistered(string busName);
    cGate *getBusGate(string busName);
    void registerTimeBuffer(string identifier, TimeTriggeredBuffer *timeBuffer);
    TimeTriggeredBuffer *getTimeBuffer(string identifier);
    bool checkTimeBufferRegistered(string identifier);
private:
    GateMap busGateMapping;
    //map to administrate TimeTriggerdBuffers
    TTBufferMap timeBuffers;
};

#endif /* DEDICATEDGATEWAYMETADATA_H_ */
