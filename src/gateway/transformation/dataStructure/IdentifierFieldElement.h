/*
 * IdentifierFieldElement.h
 *
 *  Created on: Mar 11, 2014
 *      Author: sebastian
 */

#ifndef IDENTIFIERFIELDELEMENT_H_
#define IDENTIFIERFIELDELEMENT_H_

#include <dataStructure/FieldElement.h>

namespace Transformation {

class IdentifierFieldElement: public Transformation::FieldElement {
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
    int identifier;
};

} /* namespace Transformation */

#endif /* IDENTIFIERFIELDELEMENT_H_ */
