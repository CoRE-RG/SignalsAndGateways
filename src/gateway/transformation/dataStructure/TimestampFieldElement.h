
#ifndef TIMESTAMPFIELDELEMENT_H_
#define TIMESTAMPFIELDELEMENT_H_

#include <FieldElement.h>
#include <simtime_t.h>

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

    simtime_t getTimestamp() const {
        return timestamp_;
    }

    void setTimestamp(simtime_t timestamp) {
        this->timestamp_ = timestamp;
    }

private:
    simtime_t timestamp_;

};

} /* namespace Transformation */

#endif /* TIMESTAMPFIELDELEMENT_H_ */
