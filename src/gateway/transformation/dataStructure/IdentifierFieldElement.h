
#ifndef IDENTIFIERFIELDELEMENT_H_
#define IDENTIFIERFIELDELEMENT_H_

#include "FieldElement.h"

/**
 * @brief FieldElement for the FieldSequenceMessages which stores the identifier
 *
 * @see FieldElement
 *
 * @author Sebastian Mueller
 */
class IdentifierFieldElement: public FieldElement {
public:
    IdentifierFieldElement();
    virtual ~IdentifierFieldElement();

    int getIdentifier() const {
        return identifier_;
    }

    void setIdentifier(int identifier) {
        this->identifier_ = identifier;
    }

private:
    int identifier_;
};

#endif /* IDENTIFIERFIELDELEMENT_H_ */
