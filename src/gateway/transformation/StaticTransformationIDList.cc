/*
 * StaticTransformationIDList.cc
 *
 *  Created on: Mar 11, 2014
 *      Author: sebastian
 */

#include "StaticTransformationIDList.h"

namespace SignalsAndGateways {

StaticTransformationIDList::StaticTransformationIDList() {
    this->transformationIDList.insert(std::pair<std::string, int>("canTocan", 1));
    this->transformationIDList.insert(std::pair<std::string, int>("canToflexray", 2));
    this->transformationIDList.insert(std::pair<std::string, int>("flexrayToflexray", 3));
    this->transformationIDList.insert(std::pair<std::string, int>("flexrayTocan", 4));
}

StaticTransformationIDList::~StaticTransformationIDList() {

}

int StaticTransformationIDList::getTransformationID(std::string transformation){
    Map::const_iterator pos = this->transformationIDList.find(transformation);
    int value = 0;
    if(pos == transformationIDList.end()){
        value = -1;
    }else{
        value = pos->second;
    }
    return value;
}

}
