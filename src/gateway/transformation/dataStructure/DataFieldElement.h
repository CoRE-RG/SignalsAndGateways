
#ifndef DATAFIELDELEMENT_H_
#define DATAFIELDELEMENT_H_

#include "FieldElement.h"

/**
 * @brief FieldElement for the FieldSequenceMessages which stores the payload
 *
 * @see FieldElement
 *
 * @author Sebastian Mueller
 */
class DataFieldElement: public FieldElement {
public:
    DataFieldElement(int dataLength);
    virtual ~DataFieldElement();

    int getDataLength() const {
        return dataLength_;
    }

    const char getData(int index) const {
        return data_[index];
    }

    void setData(int index, char data) {
        data_[index] = data;
    }

    void setDataLength(int dataLength) {
        dataLength_ = dataLength;
    }

private:
    int dataLength_;
    char *data_;
};

#endif /* DATAFIELDELEMENT_H_ */
