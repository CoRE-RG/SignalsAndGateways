
#ifndef TRANSPORTHEADERFIELDELEMENT_H_
#define TRANSPORTHEADERFIELDELEMENT_H_

#include <FieldElement.h>
#include <string>

namespace dataStruct {

/**
 * @brief FieldElement for the FieldSequenceMessages which stores the transport header.
 * Following fields are included:
 * - StaticBusID
 * - StaticTranslationID
 * - ActualityFlag
 *
 * @see FieldElement
 *
 * @author Sebastian Mueller
 */
class TransportHeaderFieldElement: public dataStruct::FieldElement {
public:
    TransportHeaderFieldElement();
    virtual ~TransportHeaderFieldElement();

    bool isActualityFlag() const {
        return actualityFlag_;
    }

    void setActualityFlag(bool actualityFlag) {
        actualityFlag_ = actualityFlag;
    }


    int getStaticTranslationID() const {
        return staticTranslationID_;
    }

    void setStaticTranslationID(int staticTranslationId) {
        staticTranslationID_ = staticTranslationId;
    }

    std::string getStaticBusID() const {
        return staticBusID_;
    }

    void setStaticBusID(std::string staticBusId) {
        staticBusID_ = staticBusId;
    }

private:
    int staticTranslationID_;
    std::string staticBusID_;
    bool actualityFlag_;
};

} /* namespace Transformation */

#endif /* TRANSPORTHEADERFIELDELEMENT_H_ */
