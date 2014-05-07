
#ifndef TIMESTAMPFIELDELEMENT_H_
#define TIMESTAMPFIELDELEMENT_H_

#include <FieldElement.h>

namespace dataStruct {

/**
 * @brief FieldElement for the FieldSequenceMessages which stores the timestamp
 *
 * @see FieldElement
 *
 * @author Sebastian Mueller
 */
class TimestampFieldElement: public dataStruct::FieldElement {
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
    virtual void dummy();
    clock_t timestamp;
};

} /* namespace Transformation */

#endif /* TIMESTAMPFIELDELEMENT_H_ */
