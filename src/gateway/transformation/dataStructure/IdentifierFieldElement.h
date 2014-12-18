
#ifndef IDENTIFIERFIELDELEMENT_H_
#define IDENTIFIERFIELDELEMENT_H_

#include <dataStructure/FieldElement.h>

namespace dataStruct {

/**
 * @brief FieldElement for the FieldSequenceMessages which stores the identifier
 *
 * @see FieldElement
 *
 * @author Sebastian Mueller
 */
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
    int identifier;
};

} /* namespace Transformation */

#endif /* IDENTIFIERFIELDELEMENT_H_ */
