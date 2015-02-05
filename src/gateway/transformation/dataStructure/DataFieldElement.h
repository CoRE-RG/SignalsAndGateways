
#ifndef DATAFIELDELEMENT_H_
#define DATAFIELDELEMENT_H_

#include "FieldElement.h"

namespace SignalsAndGateways {

/**
 * @brief FieldElement for the FieldSequenceMessages which stores the payload
 *
 * @see FieldElement
 *
 * @author Sebastian Mueller
 */
class DataFieldElement: public FieldElement {
public:
    DataFieldElement(unsigned int dataLength);
    virtual ~DataFieldElement();

    unsigned int getDataLength() const {
        return dataLength_;
    }

    char getData(unsigned int index) const {
        return data_[index];
    }

    void setData(unsigned int index, char data) {
        data_[index] = data;
    }

    void setDataLength(unsigned int dataLength) {
        dataLength_ = dataLength;
    }

private:
    unsigned int dataLength_;
    char *data_;
};

}

#endif /* DATAFIELDELEMENT_H_ */
