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


    int getStaticTranslationID() const {
        return staticTranslationID;
    }

    void setStaticTranslationID(int staticTranslationId) {
        staticTranslationID = staticTranslationId;
    }

    const char* getStaticBusID() const {
        return staticBusID;
    }

    void setStaticBusID(const char* staticBusId) {
        staticBusID = staticBusId;
    }

private:
    virtual void dummy();
    int staticTranslationID;
    const char* staticBusID;
    bool actualityFlag;
};

} /* namespace Transformation */

#endif /* TRANSPORTHEADERFIELDELEMENT_H_ */
