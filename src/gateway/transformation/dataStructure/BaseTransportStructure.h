//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#ifndef BASETRANSPORTSTRUCTURE_H_
#define BASETRANSPORTSTRUCTURE_H_

#include <string>
#include <omnetpp.h>

namespace SignalsAndGateways {

/**
 * @brief Base structure for inner-Gateway information transportation
 *
 * @author Philipp Meyer
 */
class BaseTransportStructure {
public:
    BaseTransportStructure();
    virtual ~BaseTransportStructure();

    int getStaticTranslationID() const;
    void setStaticTranslationID(int newStaticTranslationId);
    std::string getStaticBusID() const;
    void setStaticBusID(std::string newStaticBusId);
    bool isActualityFlag() const;
    void setActualityFlag(bool newActualityFlag);
    simtime_t getTimestamp() const;
    void setTimestamp(simtime_t newTimestamp);
private:
    int staticTranslationID;
    std::string staticBusID;
    bool actualityFlag;
    simtime_t timestamp;
};

}

#endif /* BASETRANSPORTSTRUCTURE_H_ */
