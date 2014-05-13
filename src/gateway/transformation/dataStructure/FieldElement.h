
#ifndef FIELDELEMENT_H_
#define FIELDELEMENT_H_

#include <string>

namespace dataStruct {

/**
 * @brief FieldElement which compose the base of all FieldElements.
 *
 * @see DataFieldElement, IdentifierFieldElement, TimestampFieldElement, TransportHeaderFieldElement
 *
 * @author Sebastian Mueller
 */
class FieldElement {
public:
    FieldElement();
    virtual ~FieldElement();
    std::string getFieldID();
protected:
    void setFieldID(std::string fieldID);
private:
    std::string fieldID;
};

} /* namespace Transformation */

#endif /* FIELDELEMENT_H_ */
