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

/**
 * @brief Data-structure to store and handle meta data of the appropriate gateway.
 *
 * @author Sebastian Mueller
 */
class DedicatedGatewayMetaData {
public:
    DedicatedGatewayMetaData();
    virtual ~DedicatedGatewayMetaData();

    /**
     * @brief registration of a bus
     *
     * Mapping of busName and appropriate gate-reference.
     *
     * @param busName name of the bus
     * @param gate cGate*
     */
    void registerBusGate(std::string busName, cGate *gate);
    /**
     * @brief checks registration of a bus
     *
     * Previously registered busNames will return true, while non registered busNames returns false.
     *
     * @param busName name of the bus
     * @return bool registered
     */
    bool checkBusRegistered(std::string busName);
    /**
     * @brief returns a gate-reference to the busName
     *
     * The gate-reference is returned only if the busName with corresponding gate was registered before.
     * If the busName never was registered, NULL is returned.
     *
     * @param busName name of the bus
     * @return cGate* gate-reference
     */
    cGate *getBusGate(std::string busName);
    /**
     * @brief registration of a TimeBuffer
     *
     * Mapping of identifier, which means in the majority of cases the virtual link identifier, and appropriate TimeBuffer-reference.
     *
     * @param identifier virtual link identifier
     * @param timeBuffer TimeTriggeredBuffer*
     */
    void registerTimeBuffer(std::string identifier, TimeTriggeredBuffer *timeBuffer);
    /**
     * @brief returns a TimeBuffer-reference to the identifier
     *
     * The gate-reference is returned only if the identifier with corresponding TimeBuffer-reference was registered before.
     * If the identifier never was registered, NULL is returned.
     *
     * @param identifier virtual link identifier
     * @return TimeTriggeredBuffer* TimeTriggeredBuffer-reference
     */
    TimeTriggeredBuffer *getTimeBuffer(std::string identifier);
    /**
     * @brief checks registration of a TimeBuffer
     *
     * Previously registered TimeBuffer with appropriate identifier will return true, while non registered TimeBuffers returns false.
     *
     * @param identifier virtual link identifier
     * @return bool registered
     */
    bool checkTimeBufferRegistered(std::string identifier);
private:
    //map to assign busName to gate-reference
    std::map<std::string, cGate*> busGateMapping;
    //map to administrate TimeTriggerdBuffers
    std::map<std::string, TimeTriggeredBuffer*> timeBuffers;
};

#endif /* DEDICATEDGATEWAYMETADATA_H_ */
