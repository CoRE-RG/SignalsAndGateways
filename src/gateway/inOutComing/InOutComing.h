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

#ifndef __INOUTCOMING_H_
#define __INOUTCOMING_H_

#include <omnetpp.h>

/**
 * @brief Receiving and forwarding messages from and to the network nodes.
 *
 * This module receives messages from the network nodes of the gateway and sends the messages further in the gateway logic.
 * In addition messages, which were handled by the gateway, are forwarded to the appropriate network node.
 * A network node can be an ethernet or a bus node.
 *
 * @author Sebastian Mueller
 */
class InOutComing : public cSimpleModule
{
  protected:
    /**
     * @brief method not used at the moment
     */
    virtual void initialize();
    /**
     * @brief Handles incoming messages
     *
     * On the one hand the encapsulated DataFrames of the incoming TransportMessages are extracted and encapsulated in a InterConnectMsg.
     * The InterConnectMsg represents the DataFormat for the data interchange within the core gateway modules.
     * On the other hand messages, which are handled by the gateway, arrive at this module and are forwarded to the appropriate network node.
     * The conversion to the proper data format is done within that module as well.
     *
     * @param msg The incoming message
     */
    virtual void handleMessage(cMessage *msg);
};

#endif
