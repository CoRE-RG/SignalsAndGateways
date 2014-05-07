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

#ifndef __SIGNALSANDGATEWAYS_ROUTING_H_
#define __SIGNALSANDGATEWAYS_ROUTING_H_

#include <omnetpp.h>
#include "IRouting.h"

/**
 * @brief Based on the content of the incoming message the corresponding routing data is collected.
 *
 * Independent of the message type, which can be CanDataFrame or MultipleFieldSequenceMessage, the
 * same search keys are used.
 * The routing table is specified by the parameter 'routingTable'.
 *
 * @author Sebastian Mueller
 */
class Routing : public cSimpleModule, IRouting
{
private:
    //entire routing table
    cXMLElement *routingTable;
    //all items of the routing table
    cXMLElementList items;
protected:
    /**
     * @brief Routing table is loaded.
     */
    virtual void initialize();
    /**
     * @brief Handles incoming messages
     *
     * The corresponding routing data is collected and appended to the InterConnectMsg.
     * Both CanDataFrames and MultipleFieldSequenceMessages uses the same search keys.
     * If the incoming message comes from the CAN-bus the routine for CanDataFrames is executed
     * and if the arriving message comes from the ethernet backbone network the routine for
     * MutlipleFieldSequnceMessage is executed.
     *
     * Both routines uses the following search keys to identify the proper routing item:
     * 1. sourceBusID
     * 2. sourceObjectID
     *
     * Provided a routing item is found, the entire item is bound to the InterConnectMsg
     * for further use in the upcoming modules.
     *
     * @see CanDataFrame, MultipleFieldSequenceMessage
     *
     * @param msg The incoming message
     */
    virtual void handleMessage(cMessage *msg);
};

#endif
