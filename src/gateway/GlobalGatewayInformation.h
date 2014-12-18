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

/**
 * @brief Operates as a registration interface for all gateways in the simulation.
 *
 * @author Sebastian Mueller
 */
class GlobalGatewayInformation {
public:
    GlobalGatewayInformation();
    virtual ~GlobalGatewayInformation();
    /**
     * @brief registration of a gateway
     *
     * Further registration of gates and buffers can only be made if the gateway was registered here.
     *
     * @param string gatewayName
     */
    static void registerGateway(string gatewayName);
    /**
     * @brief registration of a bus
     *
     * Extending the gateways meta-data with the specified information by using an DedicatedGatewayMetaData-functions.
     *
     * @param string gatewayName, string busName, cGate* gate
     *
     * @see DedicatedGatewayMetaData
     */
    static void registerBusGate(string gatewayName, string busName, cGate *gate);
    /**
     * @brief checks registration of a bus
     *
     * Previously registered busNames will return true, while non registered busNames returns false.
     * Uses the functions of DedicatedGatewayMetaData.
     * @see DedicatedGatewayMetaData
     *
     * @param string gatewayName, string busName
     * @return bool registered
     */
    static bool checkBusRegistered(string gatewayName, string busName);
    /**
     * @brief returns a gate-reference to the busName
     *
     * The gate-reference is returned only if the busName with corresponding gate was registered before.
     * If the busName never was registered, NULL is returned.
     * Uses the functions of DedicatedGatewayMetaData.
     * @see DedicatedGatewayMetaData
     *
     * @param string gatewayName, string busName
     * @return cGate* gate-reference
     */
    static cGate *getBusGate(string gatewayName, string busName);
    /**
     * @brief registration of a TimeBuffer
     *
     * Mapping of identifier, which means in the majority of cases the virtual link identifier, and appropriate TimeBuffer-reference.
     * Uses the functions of DedicatedGatewayMetaData.
     * @see DedicatedGatewayMetaData
     *
     * @param string gatewayName, string identifier, TimeTriggeredBuffer* identifier
     */
    static void registerTimeBuffer(string gatewayName, string identifier, TimeTriggeredBuffer *timeBuffer);
    /**
     * @brief returns a TimeBuffer-reference to the identifier
     *
     * The gate-reference is returned only if the identifier with corresponding TimeBuffer-reference was registered before.
     * If the identifier never was registered, NULL is returned.
     * Uses the functions of DedicatedGatewayMetaData.
     * @see DedicatedGatewayMetaData
     *
     * @param string gatewayName, string identifier
     * @return TimeTriggeredBuffer* TimeTriggeredBuffer-reference
     */
    static TimeTriggeredBuffer *getTimeBuffer(string gatewayName, string identifier);
    /**
     * @brief checks registration of a TimeBuffer
     *
     * Previously registered TimeBuffer with appropriate identifier will return true, while non registered TimeBuffers returns false.
     * Uses the functions of DedicatedGatewayMetaData.
     * @see DedicatedGatewayMetaData
     *
     * @param string gatewayName, string identifier
     * @return bool registered
     */
    static bool checkTimeBufferRegistered(string gatewayName, string identifier);
private:
    static GatewayMap gateways;
    /**
     * @brief Returns the DedicatedGatewayMetaData-reference to a gatewayName
     *
     * If a gatewayName is not found in the map, then a cRuntimeError is thrown.
     *
     * @param string gatewayName
     * @return DedicatedGatewayMetaData* gatewayMetaData
     */
    static DedicatedGatewayMetaData *findGateway(string gatewayName);
};

#endif /* GLOBALGATEWAYINFORMATION_H_ */
