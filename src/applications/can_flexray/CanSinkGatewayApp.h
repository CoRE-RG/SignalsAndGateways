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

#ifndef __SIGNALSANDGATEWAYS_CANSINKGATEWAYAPP_H_
#define __SIGNALSANDGATEWAYS_CANSINKGATEWAYAPP_H_

#include <omnetpp.h>
#include "FiCo4OMNeT_CanTrafficSinkAppBase.h"

/**
 * @brief Source-Application for the CAN-Node
 *
 * This module receives a TransportMessage with an encapsulated CanDataFrame.
 * The CanDataFrame is decapsulated and applied to the CAN-bus.
 *
 * @author Sebastian Mueller
 */

using namespace FiCo4OMNeT;

class CanSinkGatewayApp : public virtual CanTrafficSinkAppBase
{
  protected:
    /**
     * @brief Handles incoming TransportMessages
     *
     * If the incoming message is a TransportMessage, then the encapsulated CanDataFrame is decapsulated and send to the CanBuffer.
     *
     * @param msg The incoming message
     */
    void handleMessage(cMessage *msg);
};

#endif
