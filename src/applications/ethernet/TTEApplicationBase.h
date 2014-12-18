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

#ifndef TTEAPPLICATIONBASE_H_
#define TTEAPPLICATIONBASE_H_

#include <omnetpp.h>
#include "CoRE4INET_CTApplicationBase.h"
#include "TransportMessage_m.h"

/**
 * @brief gateway application for the Ethernet-Node
 *
 * This module represents the connection between the ethernet-backbone network and the gateway.
 *
 * @author Sebastian Mueller
 */
class TTEApplicationBase: public virtual CoRE4INET::CTApplicationBase {
private:
    /**
     * @brief calls the inherited initialize-method
     */
    void initialize();
    /**
     * @brief Handles incoming messages
     *
     * Messages from the ethernet network are encapsulated in a TransportMessage und forwarded to the gateway.
     * And the other direction, which means messages from the gateway, are send to the ethernet network as CT-Frames.
     *
     * @param msg The incoming message
     */
    void handleMessage(cMessage *msg);
public:
    TTEApplicationBase();
    virtual ~TTEApplicationBase();
};

#endif /* TTEAPPLICATIONBASE_H_ */
Define_Module(TTEApplicationBase);
