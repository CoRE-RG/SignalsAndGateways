/*
 * TimestampFieldElement.h
 *
 *  Created on: Mar 11, 2014
 *      Author: sebastian
 */

#ifndef TIMESTAMPFIELDELEMENT_H_
#define TIMESTAMPFIELDELEMENT_H_

#include <FieldElement.h>

namespace Transformation {

class TimestampFieldElement: public Transformation::FieldElement {
public:
    TimestampFieldElement();
    virtual ~TimestampFieldElement();

    clock_t getTimestamp() const {
        return timestamp;
    }

    void setTimestamp(clock_t timestamp) {
        this->timestamp = timestamp;
    }

private:
    clock_t timestamp;
};

} /* namespace Transformation */

#endif /* TIMESTAMPFIELDELEMENT_H_ */
