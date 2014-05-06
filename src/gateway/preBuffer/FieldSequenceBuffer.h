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

#include "FieldSequenceMessage_m.h"
#include <cqueue.h>
#include "candataframe_m.h"

/**
 * Type for comparison functions for cObject. Return value should be:
 * - less than zero if a < b
 * - greater than zero if a > b
 * - zero if a == b
 *
 */
typedef int (*compareFunc)(cObject *a, cObject *b);

/**
 * @brief Stores FieldSequenceMessages in a cQueue ordered by the IdentifierFieldElement.
 *
 * @see FieldSequenceMessage, IdentifierFieldElement, TimeTriggeredBuffer
 *
 * @author Sebastian Mueller
 */
class FieldSequenceBuffer {
public:
    FieldSequenceBuffer();
    virtual ~FieldSequenceBuffer();
    /**
     * @brief Enqueues a FieldSequenceMessage ordered by the IdentifierFieldElement
     *
     * @param FieldSequenceMessage to enqueue
     */
    void enqueue(FieldSequenceMessage*);
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

private:
    //Queue to hold the FieldSequenceMessages
    cQueue timeQueue;
    /**
     * @brief Compare-Function to compare to Objects of the queue. This function defines the order of the queue.
     * @return less than zero if a < b OR greater than zero if a > b OR zero if a == b
     */
    int compareFunc(cObject *a, cObject *b);
    CompareFunc compare;
};

#endif /* FIELDSEQUENCEBUFFER_H_ */
