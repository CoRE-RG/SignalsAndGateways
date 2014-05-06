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

#ifndef __SIGNALSANDGATEWAYS_DISPATCHER_H_
#define __SIGNALSANDGATEWAYS_DISPATCHER_H_

#include <omnetpp.h>
#include "TimeTriggeredBuffer.h"
#include <map>
#include <string>

//Definition of the map to administrate the TimeTriggerdBuffers
typedef std::map<std::string, TimeTriggeredBuffer*> TTBufferMap;
typedef TTBufferMap::value_type ValuePair;
/**
 * @brief Dispatches the incoming messages to the appropriate TimeTriggeredBuffer.
 *
 * For each virtual link, which are defined in the routing table, the appropriate TimeTriggeredBuffer
 * is generated automatically within the initialization process.
 * Incoming messages are stored in the corresponding TimeTriggeredBuffer and will be hold there according to the time strategy.
 * According to the time strategy all stored messages of the TimeTriggeredBuffer are returning to this Dispatcher in a MultipleFieldSequenceMessage.
 *
 * @see TimeTriggeredBuffer, MultipleFieldSequenceMessage
 *
 * @author Sebastian Mueller
 */
class Dispatcher: public cSimpleModule {
private:
    //entire routing table
    cXMLElement *routingTable;
    //all items of the routing table
    cXMLElementList items;
    //map to administrate TimeTriggerdBuffers
    TTBufferMap timeBuffers;
protected:
    /**
     * @brief For each virtual link, which are defined in the routing table, the appropriate TimeTriggeredBuffer is generated automatically and for administration purposes linked in a map.
     */
    virtual void initialize();
    /**
     * @brief Handles incoming messages
     *
     * Incoming messages are stored in the corresponding TimeTriggeredBuffer and will be hold there according to the time strategy.
     * According to the time strategy all stored messages of the TimeTriggeredBuffer are returning to this Dispatcher in a MultipleFieldSequenceMessage.
     * The returning MultipleFieldSequenceMessage of the TimeTriggeredBuffer is send back to the PreBuffer module encapsulated in a InterConnectMsg.
     *
     * @see TimeTriggerdBuffer, MultipleFieldSequenceMessage
     *
     * @param msg The incoming message
     */
    virtual void handleMessage(cMessage *msg);
};

#endif
