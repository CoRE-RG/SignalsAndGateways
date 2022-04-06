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

using namespace omnetpp;

/**
 * @brief Gateway application for the Ethernet node.
 *
 * This module represents the connection between the Ethernet backbone network and the gateway.
 *
 * @author Sebastian Mueller
 */
class EthernetGatewayApplication: public virtual CoRE4INET::CTApplicationBase {

protected:
    /**
     * @brief Calls the inherited initialize method.
     */
    virtual void initialize() override;

    /**
     * @brief Handles incoming messages.
     *
     * Messages from the Ethernet network are forwarded to the gateway.
     * Messages from the gateway are forwarded to the Ethernet network.
     *
     * @param msg The incoming message
     */
    virtual void handleMessage(cMessage *msg) override;

public:
    /**
     * @brief Constructor
     */
    EthernetGatewayApplication();

    /**
     * @brief Destructor
     */
    virtual ~EthernetGatewayApplication() override;

    /**
     * @brief Register a Gate to receive messages of a certain CAN ID as RAW GatewayAggregationMessage.
     *
     * @param canID         The can ID to receive
     * @param deliveryGate  The cGate to which messages should be delivered
     */
    virtual void registerForCANID(unsigned int canID, cGate* deliveryGate);


private:
    /**
     * Map for delivery gates for each can id
     */
    std::unordered_map<unsigned int, std::vector<cGate*>> _canIdSubMap;
};

}

#endif /* TTEAPPLICATIONBASE_H_ */
