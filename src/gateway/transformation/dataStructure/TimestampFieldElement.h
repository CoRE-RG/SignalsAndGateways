
#ifndef TIMESTAMPFIELDELEMENT_H_
#define TIMESTAMPFIELDELEMENT_H_

#include "FieldElement.h"

namespace SignalsAndGateways {

/**
 * @brief FieldElement for the FieldSequenceMessages which stores the timestamp
 *
 * @see FieldElement
 *
 * @author Sebastian Mueller
 */
class TimestampFieldElement: public FieldElement {
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

}

#endif /* TIMESTAMPFIELDELEMENT_H_ */
