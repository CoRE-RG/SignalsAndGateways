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

#ifndef SIGNALSANDGATEWAYS_CANSOURCEGATEWAYAPP_H_
#define SIGNALSANDGATEWAYS_CANSOURCEGATEWAYAPP_H_

//SignalsAndGateways
#include "signalsandgateways/base/SignalsAndGateways_Defs.h"
//FiCo4OMNeT
#include "fico4omnet/applications/can/source/CanTrafficSourceAppBase.h"

namespace SignalsAndGateways {

using namespace omnetpp;

/**
 * @brief Source-Application for the CAN-Node
 *
 * This module receives CanDataFrames from the gateway and forwards it to the CAN-bus.
 *
 * @author Sebastian Mueller
 */
class CanSourceGatewayApp : public FiCo4OMNeT::CanTrafficSourceAppBase
{
  public:
    /**
     * @brief Destructor of CanSourceGatewayApp
     */
    virtual ~CanSourceGatewayApp() override;
  protected:
    /**
     * @brief Handles incoming TransportMessages
     *
     * If the incoming message is a CanDataFrame, then the CanDataFrame is forwarded to the CAN-bus.
     *
     * @param msg The incoming message
     */
    virtual void handleMessage(cMessage *msg) override;
};

}

#endif
