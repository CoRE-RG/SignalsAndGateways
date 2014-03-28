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
 * @ingroup EnumsTypes
 */
typedef int (*compareFunc)(cObject *a, cObject *b);

class FieldSequenceBuffer {
public:
    FieldSequenceBuffer();
    virtual ~FieldSequenceBuffer();
    void enqueue(FieldSequenceMessage*);
    FieldSequenceMessage* dequeue();
    bool isEmpty();

    const cQueue getQueue() {
        return timeQueue;
    }

private:
    cQueue timeQueue;
    int compareFunc(cObject *a, cObject *b);
    CompareFunc compare;
};

#endif /* FIELDSEQUENCEBUFFER_H_ */
