/*
 * FieldElement.h
 *
 *  Created on: Mar 10, 2014
 *      Author: sebastian
 */

#ifndef FIELDELEMENT_H_
#define FIELDELEMENT_H_

#include <string>

namespace dataStruct {

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
