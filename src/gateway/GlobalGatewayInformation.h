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

#ifndef GLOBALGATEWAYINFORMATION_H_
#define GLOBALGATEWAYINFORMATION_H_

#include <omnetpp.h>
#include "TimeTriggeredBuffer.h"
#include "DedicatedGatewayMetaData.h"

using namespace std;
typedef map<string, DedicatedGatewayMetaData> GatewayMap;

class GlobalGatewayInformation {
public:
    GlobalGatewayInformation();
    virtual ~GlobalGatewayInformation();

    static void registerGateway(string gatewayName);
    static void registerBusGate(string gatewayName, string busName, cGate *gate);
    static bool checkBusRegistered(string gatewayName, string busName);
    static cGate *getBusGate(string gatewayName, string busName);
    static void registerTimeBuffer(string gatewayName, string identifier, TimeTriggeredBuffer *timeBuffer);
    static TimeTriggeredBuffer *getTimeBuffer(string gatewayName, string identifier);
    static bool checkTimeBufferRegistered(string gatewayName, string identifier);
private:
    static GatewayMap gateways;
    static DedicatedGatewayMetaData *findGateway(string gatewayName);
};

#endif /* GLOBALGATEWAYINFORMATION_H_ */
