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
#include "InterConnectMsg_m.h"
#include "CanDataFrame_m.h"
#include "CanTransportStructure.h"

namespace SignalsAndGateways {

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
     */
    virtual void transform(cMessage *msg);
  private:
    //Predefined transformation list
    StaticTransformationIDList *transformMap;
    /**
     * @brief Transforms a CanDataFrame to a FieldSequnceDataStructure
     *
     * The CanID and data is extracted from the CanDataFrame and added to a sequence list.
     * Following additional fields are added to the sequence list:
     * - TransportHeader composed of staticTransformationID, staticBusID and actualityFlag.
     * - Timestamp set to the arrival time on the Can-Interface of the gateway
     *
     * More detailed specification of the meta information in the TransportHeader:
     * - StaticTranslationID: declare the translation process
     * - StaticBusID: identifies the corresponding arrival bus
     * - ActualityFlag: specifies whether the frame is allready send or not(used in PreBuffer)
     *
     * @see FieldSequnceDataStructure, CanDataFrame, StaticTransformationList, DataFieldElement, IdentifierFieldElement, TimestampFieldElement, TransportHeaderFieldElement
     *
     * @param msg CanDataFrame
     * @return FieldSequenceDataStructure performed data structure by transformation process
     */
    CanTransportStructure* transformCanToTransport(FiCo4OMNeT::CanDataFrame *msg);
    /**
     * @brief Transforms a FieldSequenceDataStructure to a CanDataFrame
     *
     * The CanID of the new CanDataFrame is set to the destinationCanID of the corresponding entry in the routingTable.
     * The data field and timestamp field will be retrieved from the FieldSequenceDataStructure and added to the CanDataFrame
     *
     * If single FieldElements will not be found, then a exception is thrown.
     *
     * @see FieldSequenceDataStructure, CanDataFrame, DataFieldElement, IdentifierFieldElement, TimestampFieldElement
     *
     * @param transportFrame FieldSequenceDataStructure, which will be transformed
     * @param routingDestination cXMLElement*
     *
     * @return CanDataFrame new performed CanDataFrame
     *
     */
    FiCo4OMNeT::CanDataFrame* transformTransportToCan(CanTransportStructure* transportFrame, cXMLElement* routingDestination);
    //entire routing table
    cXMLElement *routingTable;
    //all items of the routing table
    cXMLElementList items;
    //source field of current item
    cXMLElement* source;
    //all destination fields of current item
    cXMLElementList destination;
    //options field of current item
    cXMLElement* gatewayOptions;
    string gatewayName;
};

}

#endif
