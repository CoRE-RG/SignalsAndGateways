/*
 * IdentifierFieldElement.h
 *
 *  Created on: Mar 11, 2014
 *      Author: sebastian
 */

#ifndef IDENTIFIERFIELDELEMENT_H_
#define IDENTIFIERFIELDELEMENT_H_

#include <dataStructure/FieldElement.h>

namespace dataStruct {

class IdentifierFieldElement: public dataStruct::FieldElement {
public:
    IdentifierFieldElement();
    virtual ~IdentifierFieldElement();

    int getIdentifier() const {
        return identifier;
    }

    void setIdentifier(int identifier) {
        this->identifier = identifier;
    }

private:
    virtual void dummy();
    int identifier;
};

} /* namespace Transformation */

#endif /* IDENTIFIERFIELDELEMENT_H_ */
