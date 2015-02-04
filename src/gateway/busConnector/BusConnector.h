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

#ifndef __SIGNALSANDGATEWAYS_BUSCONNECTOR_H_
#define __SIGNALSANDGATEWAYS_BUSCONNECTOR_H_

#include <omnetpp.h>

namespace SignalsAndGateways {

/**
 * @brief Redirects the CanDataFrames from and to the gateway.
 *
 * Incoming CanDataFrames from the connected busses are forwarded to the gateway. Outgoing CanDataFrames from the gateway are redirected to the proper CAN-bus.
 *
 * @author Sebastian Mueller
 */
using namespace std;

class BusConnector : public cSimpleModule
{
  protected:
    /**
     * @brief Automated registration of the connected CAN-busses in an simulation wide index.
     *
     * Every CAN-bus is registered by gatewayName, busName and busGate-reference.
     */
    virtual void initialize();
    /**
     * @brief Handles incoming messages
     *
     * Incoming CanDataFrames from the CAN-busses are unaffected forwarded to the gateway.
     * Outgoing CanDataFrames are redirected to the proper CAN-bus by analyzing the routing Information of the enclosing InterConnectMsg.
     *
     * @param msg The incoming message
     */
    virtual void handleMessage(cMessage *msg);
  private:
    string gatewayName;

};

}

#endif
