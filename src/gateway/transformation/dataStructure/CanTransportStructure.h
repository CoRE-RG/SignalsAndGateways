/*
 * CanSequenceStructure.h
 *
 *  Created on: 06.02.2015
 *      Author: Philipp
 */

#ifndef CANSEQUENCESTRUCTURE_H_
#define CANSEQUENCESTRUCTURE_H_

#include "BaseTransportStructure.h"

namespace SignalsAndGateways {

class CanTransportStructure : public BaseTransportStructure {
public:
    CanTransportStructure(unsigned int dataLength);
    virtual ~CanTransportStructure();

    unsigned int getIdentifier() const;
    void setIdentifier(unsigned int newIdentifier);
    bool isRtr() const;
    void setRtr(bool newRtr);
    unsigned int getDataLength() const;
    void setDataLength(unsigned int newDataLength);
    char getData(unsigned int index) const;
    void setData(unsigned int index, char newData);
private:
    unsigned int identifier;
    bool rtr;
    unsigned int dataLength;
    char *data;
};

}

#endif /* CANSEQUENCESTRUCTURE_H_ */
