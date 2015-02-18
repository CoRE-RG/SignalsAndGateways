
#ifndef STATICTRANSFORMATIONIDLIST_H_
#define STATICTRANSFORMATIONIDLIST_H_

#include <map>
#include <string>

using std::map;
using std::string;

namespace SignalsAndGateways {

/**
 * @brief The StaticTransformationList is used to predefine transformation pattern.
 *
 * Predefined string representations of different transformation processes are associated
 * to a number in a map.
 * The transformation ID can be found by the string representation. This offers the opportunity
 * to check if the transformation is valid.
 *
 * @author Sebastian Mueller
 */
class StaticTransformationIDList {
public:
    /**
     * @brief Predefined initialization of the transformation map
     */
    StaticTransformationIDList();
    virtual ~StaticTransformationIDList();
    /**
     * @brief Returns the transformationID to the corresponding string representation of the transformation process
     *
     * @param transformation string representation of the transformation process
     * @return int transformationID corresponding to the string representation
     */
    int getTransformationID(const string transformation);
private:
    typedef map<string, int> Map;
    //Predefined transformation list
    Map transformationIDList;
};

}

#endif /* STATICTRANSFORMATIONIDLIST_H_ */
