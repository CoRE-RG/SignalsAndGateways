/*
 * TransportHeaderFieldElement.h
 *
 *  Created on: Mar 11, 2014
 *      Author: sebastian
 */

#ifndef TRANSPORTHEADERFIELDELEMENT_H_
#define TRANSPORTHEADERFIELDELEMENT_H_

#include <FieldElement.h>
#include <string>

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

    std::string getStaticBusID() const {
        return staticBusID;
    }

    void setStaticBusID(std::string staticBusId) {
        staticBusID = staticBusId;
    }

private:
    virtual void dummy();
    int staticTranslationID;
    std::string staticBusID;
    bool actualityFlag;
};

} /* namespace Transformation */

#endif /* TRANSPORTHEADERFIELDELEMENT_H_ */
