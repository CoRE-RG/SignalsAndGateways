/*
 * StaticTransformationIDList.h
 *
 *  Created on: Mar 11, 2014
 *      Author: sebastian
 */

#ifndef STATICTRANSFORMATIONIDLIST_H_
#define STATICTRANSFORMATIONIDLIST_H_

#include <map>
#include <string>

using std::map;
using std::string;

class StaticTransformationIDList {
public:
    StaticTransformationIDList();
    virtual ~StaticTransformationIDList();
    int getTransformationID(const string transformation);
private:
    typedef map<string, int> Map;
    Map transformationIDList;
};

#endif /* STATICTRANSFORMATIONIDLIST_H_ */
