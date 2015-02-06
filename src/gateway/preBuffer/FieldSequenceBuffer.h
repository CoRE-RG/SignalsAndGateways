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

#ifndef FIELDSEQUENCEBUFFER_H_
#define FIELDSEQUENCEBUFFER_H_

#include <cqueue.h>

#include "FieldSequenceMessage_m.h"
#include "CanDataFrame_m.h"
#include "CanTransportStructure.h"

namespace SignalsAndGateways {

/**
 * @brief Stores FieldSequenceMessages in a cQueue ordered by the IdentifierFieldElement.
 *
 * @see FieldSequenceMessage, IdentifierFieldElement, TimeTriggeredBuffer
 *
 * @author Sebastian Mueller
 */
class FieldSequenceBuffer: public cObject {
public:
    FieldSequenceBuffer();
    virtual ~FieldSequenceBuffer();
    /**
     * @brief Enqueues a FieldSequenceMessage ordered by the IdentifierFieldElement
     *
     * @param value FieldSequenceMessage to enqueue
     */
    void enqueue(FieldSequenceMessage* value);
    /**
     * @brief Dequeues a FieldSequenceMessage according to the order in the queue
     * @return Next FieldSequenceMessage of the queue
     */
    FieldSequenceMessage* dequeue();
    /**
     * @brief Indicates whether the queue is empty or not.
     * @return true if queue contains no objects or false if the queue contains at least one object
     */
    bool isEmpty();
    /**
     * @brief Return the entire queue as cQueue.
     * @return entire cQueue
     */
    const cQueue getQueue() {
        return timeQueue;
    }

    /**
     * @brief Calls the clear() function of cQueue
     *
     * Empties the container. Contained objects that were owned by the
     * queue (see getTakeOwnership()) will be deleted.
     */
    void clear(){
        timeQueue.clear();
    }

private:
    //Queue to hold the FieldSequenceMessages
    cQueue timeQueue;
    /**
     * Type for comparison functions for cObject. Return value should be:
     * - less than zero if a < b
     * - greater than zero if a > b
     * - zero if a == b
     *
     */
    typedef int (*compareFunc)(cObject *a, cObject *b);

    /**
     * @brief Compare-Function to compare to Objects of the queue. This function defines the order of the queue.
     * @return less than zero if a < b OR greater than zero if a > b OR zero if a == b
     */
    static int compareFieldSequenceMessage(cObject *a, cObject *b){
        FieldSequenceMessage* canA = dynamic_cast<FieldSequenceMessage*>(a);
        FieldSequenceMessage* canB = dynamic_cast<FieldSequenceMessage*>(b);
        int returnValue = 0;
        if(canA && canB){
            CanTransportStructure* canA_fieldSequence = dynamic_cast<CanTransportStructure*>(canA->getTransportFrame());
            CanTransportStructure* canB_fieldSequence = dynamic_cast<CanTransportStructure*>(canB->getTransportFrame());
            if(canA_fieldSequence && canB_fieldSequence){
                returnValue = (canA_fieldSequence->getIdentifier())-(canB_fieldSequence->getIdentifier());
            }else{
                opp_error("Insertion of object in PreBuffer failed. Only CAN-FieldSequenceMessage-objects are supported!");
            }
        }else{
            opp_error("Insertion of object in PreBuffer failed. Only FieldSequenceMessage-objects are supported!");
        }
        return returnValue;
    }

    compareFunc pCompare = &compareFieldSequenceMessage;

};

}

#endif /* FIELDSEQUENCEBUFFER_H_ */
