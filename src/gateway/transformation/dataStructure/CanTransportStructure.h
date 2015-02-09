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

#ifndef CANTRANSPORTSTRUCTURE_H_
#define CANTRANSPORTSTRUCTURE_H_

#include "BaseTransportStructure.h"

namespace SignalsAndGateways {

/**
 * @brief CAN structure for inner-Gateway information transportation
 *
 * @author Philipp Meyer
 *
 * @sa BaseTransportStructure
 */
class CanTransportStructure : public BaseTransportStructure {
public:
    CanTransportStructure(unsigned int dataLength);
    virtual ~CanTransportStructure();

    unsigned int getIdentifier() const;
    void setIdentifier(unsigned int newIdentifier);
    bool isRtr() const;
    void setRtr(bool newRtr);
    unsigned int getDataLength() const;
    void setDataLength(unsigned int newDataLength);
    char getData(unsigned int index) const;
    void setData(unsigned int index, char newData);
private:
    unsigned int identifier;
    bool rtr;
    unsigned int dataLength;
    char *data;
};

}

#endif /* CANTRANSPORTSTRUCTURE_H_ */
