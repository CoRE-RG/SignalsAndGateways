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

#ifndef __SIGNALSANDGATEWAYS_TRANSFORMATION_H_
#define __SIGNALSANDGATEWAYS_TRANSFORMATION_H_

#include <omnetpp.h>
#include "StaticTransformationIDList.h"
#include "ITransformation.h"
#include "FieldElement.h"
#include "InterConnectMsg_m.h"
#include "candataframe_m.h"
#include "FieldSequenceDataStructure.h"

/**
 * @brief Transformation of bus messages in FieldSequenceMessages and vice versa.
 *
 * This module converts the incoming bus message in a sequence of fields.
 * On the other hand incoming messages which consists of a sequence are converted to the specified bus message.
 * The conversion in a sequence of fields, which is called transport presentation, is
 * necessary to convert messages from one bus type into another and offers a simple way of transportation
 * within the ethernet backbone network. Which kind of transformation is used,
 * is to be defined in the routing table by 'sourceType' and 'destinationType'.
 *
 * @author Sebastian Mueller
 */
class Transformation : public cSimpleModule, ITransformation
{
  protected:
    /**
     * @brief Routing table is loaded and some member variables initialized.
     */
    virtual void initialize();
    /**
     * @brief Handles incoming messages
     *
     * Forwards the incoming messages to underlying routines.
     *
     * @param msg The incoming message
     */
    virtual void handleMessage(cMessage *msg);
    /**
     * @brief Handles incoming messages
     *
     * Based on the routing information of the InterConnectMsg, the transformation type is identified.
     * This is done by parsing 'sourceType' and 'destinationType' of the routing table to a valid string representation of the StaticTransformationList.
     * Example: "can"+"To"+"can"
     * Once the transformation type is identified the corresponding transformation routine is called.
     * The transformed message is send, encapsulated in an InterConnectMsg, to the following gateway module.
     *
     * @see CanDataFrame, InterConnectMsg, StaticTransformationList
     *
     * @param msg The incoming message
     * @return InterConnectMsg performed message by transformation process
     */
    virtual InterConnectMsg *transform(cMessage *msg);
  private:
    //Predefined transformation list
    StaticTransformationIDList *transformMap;
    /**
     * @brief Transforms a CanDataFrame to a FieldSequnceDataStructure
     *
     * The CanID and data is extracted from the CanDataFrame and added to a sequence list.
     * Following additional fields are added to the sequence list:
     * - TransportHeader composed of staticTransformationID, staticBusID and actualityFlag.
     * - Timestamp with current time
     *
     * @see CanDataFrame, StaticTransformationList, DataFieldElement, IdentifierFieldElement, TimestampFieldElement, TransportHeaderFieldElement
     *
     * @param msg CanDataFrame
     * @return FieldSequenceDataStructure performed data structure by transformation process
     */
    FieldSequenceDataStructure transformCanToTransport(CanDataFrame *msg);
    /**
     *
     */
    CanDataFrame *transformTransportToCan(FieldSequenceDataStructure transportFrame);
    //entire routing table
    cXMLElement *routingTable;
    //all items of the routing table
    cXMLElementList items;
    //source field of current item
    cXMLElement* source;
    //all destination fields of current item
    cXMLElementList destination;
    //options field of current item
    cXMLElement* options;
};

#endif
