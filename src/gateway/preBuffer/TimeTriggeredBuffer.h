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

#ifndef __SIGNALSANDGATEWAYS_TIMETRIGGEREDBUFFER_H_
#define __SIGNALSANDGATEWAYS_TIMETRIGGEREDBUFFER_H_

#include <omnetpp.h>
#include "FieldSequenceBuffer.h"
#include "MultipleFieldSequenceMessage.h"

/**
 * @brief Stores FieldSequenceMessages in a FieldSequenceBuffer according to a time strategy.
 *
 * According to the time strategy all stored messages in the FieldSequnceBuffer are retrieved and collected in a MultipleFieldSequenceMessage,
 * which is send back to the Dispatcher.
 * For each bus message, which is identified by the member-/object-ID, a maximum holdUpTime is defined in the routing table.
 * The TimeTriggeredBuffer is using these parameters to calculate the remaining waiting time.
 *
 * @see FieldSequenceBuffer, Dispatcher, MultipleFieldSequenceMessage
 *
 * @author Sebastian Mueller
 */
class TimeTriggeredBuffer : public cSimpleModule
{
public:
    /**
     * @brief Returns the CTID which is dedicated for that TimeTriggeredBuffer and match with the virtual link.
     *
     */
    std::string getDispatchedCTID() const {
        return dispatchedCTID;
    }

    /**
     * @brief Assigns the CTID to that TimeTriggeredBuffer and should match with the corresponding virtual link.
     *
     * @param dispatchedCTID CTID which that TimeTriggeredBuffer shall be dedicated for
     */
    void setDispatchedCTID(std::string dispatchedCTID) {
        this->dispatchedCTID = dispatchedCTID;
    }

    const std::string& getDispatchedBackboneTransferType() const {
        return dispatchedBackboneTransferType;
    }

    void setDispatchedBackboneTransferType(
            const std::string& dispatchedBackboneTransferType) {
        this->dispatchedBackboneTransferType = dispatchedBackboneTransferType;
    }

  protected:
    /**
     * @brief Initialization of some member variables
     */
    virtual void initialize();
    /**
     * @brief Handles incoming messages
     *
     * The incoming FieldSequenceMessage is enqueued in the FieldSequenceBuffer.
     * There the Message is hold according to the time strategy.
     * The time strategy is defined as follows:
     * If the timer is not scheduled yet, the timer will be set to the holdUpTime.
     * The holdUpTime is defined in the routing table and every member-/object ID of the
     * bus messages have its own, specific holdUpTime defined there.
     * If the timer is already scheduled, the minimum of the current timer value and the
     * holdUpTime of the received message is used to reschedule the timer.
     *
     * Once the timer is expired the hole content of the FieldSequenceBuffer, which consist
     * of all received FieldSequenceMessages in the last timer period, is retrieved and
     * collected in a MultipleFieldSequenceMessage. That message will be send back to the
     * Dispatcher immediately.
     *
     * @see TimeTriggerdBuffer, MultipleFieldSequenceMessage
     *
     * @param msg The incoming message
     */
    virtual void handleMessage(cMessage *msg);
  private:
    //Queue to store the FieldSequenceMessages
    FieldSequenceBuffer buffer;
    //Message which is used for the timer
    cMessage *timerEvent;
    //Dedicated CTID which that TimeTriggeredBuffer is assigned to
    std::string dispatchedCTID;
    //BackboneTransferType to the corresponding dispatchedCTID
    std::string dispatchedBackboneTransferType;
    //Module pointer to the dispatcher
    cModule *dispatcher;
    ~TimeTriggeredBuffer();
};

#endif
