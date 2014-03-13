/*
 * TransportHeaderFieldElement.h
 *
 *  Created on: Mar 11, 2014
 *      Author: sebastian
 */

#ifndef TRANSPORTHEADERFIELDELEMENT_H_
#define TRANSPORTHEADERFIELDELEMENT_H_

#include <FieldElement.h>

namespace dataStruct {

class TransportHeaderFieldElement: public dataStruct::FieldElement {
public:
    TransportHeaderFieldElement();
    virtual ~TransportHeaderFieldElement();

    bool isActualityFlag() const {
        return actualityFlag;
    }

    void setActualityFlag(bool actualityFlag) {
        this->actualityFlag = actualityFlag;
    }

    int getStaticBusId() const {
        return staticBusID;
    }

    void setStaticBusId(int staticBusId) {
        staticBusID = staticBusId;
    }

    int getStaticTranslationId() const {
        return staticTranslationID;
    }

    void setStaticTranslationId(int staticTranslationId) {
        staticTranslationID = staticTranslationId;
    }

private:
    int staticTranslationID;
    int staticBusID;
    bool actualityFlag;
};

} /* namespace Transformation */

#endif /* TRANSPORTHEADERFIELDELEMENT_H_ */
