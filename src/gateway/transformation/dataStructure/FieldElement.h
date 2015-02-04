
#ifndef FIELDELEMENT_H_
#define FIELDELEMENT_H_

#include <string>
#include <omnetpp.h>

namespace SignalsAndGateways {

/**
 * @brief FieldElement which compose the base of all FieldElements.
 *
 * @see DataFieldElement, IdentifierFieldElement, TimestampFieldElement, TransportHeaderFieldElement
 *
 * @author Sebastian Mueller
 */
class FieldElement : public cObject{
public:
    FieldElement();
    virtual ~FieldElement();
    std::string getFieldID();
protected:
    void setFieldID(std::string fieldID);
private:
    std::string fieldID_;
};

}

#endif /* FIELDELEMENT_H_ */
