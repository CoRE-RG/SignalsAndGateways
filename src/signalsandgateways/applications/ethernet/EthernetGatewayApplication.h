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

//SignalsAndGateways
#include "signalsandgateways/base/SignalsAndGateways_Defs.h"
//CoRE4INET
#include "core4inet/applications/AS6802/CTApplicationBase.h"

namespace SignalsAndGateways {

/**
 * @brief Gateway application for the Ethernet node.
 *
 * This module represents the connection between the Ethernet backbone network and the gateway.
 *
 * @author Sebastian Mueller
 */
class EthernetGatewayApplication: public virtual CoRE4INET::CTApplicationBase {

private:
    /**
     * @brief Calls the inherited initialize method.
     */
    void initialize();

    /**
     * @brief Handles incoming messages.
     *
     * Messages from the Ethernet network are forwarded to the gateway.
     * Messages from the gateway are forwarded to the Ethernet network.
     *
     * @param msg The incoming message
     */
    void handleMessage(cMessage *msg);

public:
    /**
     * @brief Constructor
     */
    EthernetGatewayApplication();

    /**
     * @brief Destructor
     */
    virtual ~EthernetGatewayApplication();
};

}

#endif /* TTEAPPLICATIONBASE_H_ */
