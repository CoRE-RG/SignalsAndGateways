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

#ifndef SIGNALSANDGATEWAYS_CANSINKGATEWAYAPP_H_
#define SIGNALSANDGATEWAYS_CANSINKGATEWAYAPP_H_

//SignalsAndGateways
#include "signalsandgateways/base/SignalsAndGateways_Defs.h"
//FiCo4OMNeT
#include "fico4omnet/applications/can/sink/CanTrafficSinkAppBase.h"

namespace SignalsAndGateways {

using namespace omnetpp;

/**
 * @brief Source-Application for the CAN-Node
 *
 * This module receives a CanDataFrame and forwards it to the gateway.
 *
 * @author Sebastian Mueller
 */
class CanSinkGatewayApp : public virtual FiCo4OMNeT::CanTrafficSinkAppBase
{
  protected:
    /**
     * @brief Handles incoming TransportMessages
     *
     * If the incoming message is a CanDataFrame, then the CanDataFrame is send to the upper layer gateway.
     *
     * @param msg The incoming message
     */
    void handleMessage(cMessage *msg) override;
};

}

#endif
