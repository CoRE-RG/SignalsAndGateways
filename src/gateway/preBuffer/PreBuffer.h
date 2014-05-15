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

#ifndef __SIGNALSANDGATEWAYS_PREBUFFER_H_
#define __SIGNALSANDGATEWAYS_PREBUFFER_H_

#include <omnetpp.h>

/**
 * @brief FieldSequenceMessage are redirected to a Buffer for accumulation of multiple Frames or optionally forwarded immediate. CanDataFrames are always forwarded immediate.
 *
 * The parameter "cumulate" indicates whether the incoming FieldSequenceMessages,
 * which are produced by the Transformation module, are forwarded immediate or collected
 * in a TimeTriggerdBuffer. The TimeTriggerdBuffer will hold the incoming messages for a
 * preexisting time defined in the routing table(holdUpTime) to wait for contingently messages to the same virtual link.
 * This opens the opportunity to collect multiple bus messages in a single ethernet backbone message.
 *
 * @see Dispatcher, TimeTriggeredBuffer
 *
 * @author Sebastian Mueller
 */
class PreBuffer: public cSimpleModule {
protected:
    /**
     * @brief Initialization of the parameters
     */
    virtual void initialize();
    /**
     * @brief Handles incoming messages
     *
     * First the encapsulated payload of the InterConnectMsg is decapsulated.
     * That contains the result of the transformation process, either a FieldSequenceMessage or a CanDataFrame.
     * If cumulation is activated the data is forwarded to the Dispatcher for the TimeTriggerdBuffers.
     * If cumulation is deactivated the FieldSequenceMessage is encapsulated in a MultiFieldSequenceMessage
     * and unaffected forwarded to the inOutComing module.
     * Returning message from the Dispatcher and CanDataFrames are directly forwarded to the inOutComing module.
     *
     * @see Dispatcher, TimeTriggeredBuffer, InOutComing, FieldSequenceMessage, MultiFieldSequenceMessage
     *
     * @param msg The incoming message
     */
    virtual void handleMessage(cMessage *msg);
private:
    //Indicates whether frame accumulation is activated or not.
    bool cumulate;
};

#endif
