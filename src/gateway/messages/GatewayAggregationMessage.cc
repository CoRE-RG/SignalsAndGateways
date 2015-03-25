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

#include <GatewayAggregationMessage.h>

namespace SignalsAndGateways {

void GatewayAggregationMessage::encapUnit(UnitMessage* unit){
    take(unit);
    setByteLength(getByteLength() + unit->getByteLength());
    units.push_back(unit);
}

UnitMessage* GatewayAggregationMessage::decapUnit(){
    UnitMessage* unit = NULL;
    if(units.size() > 0){
        unit = units.front();
        setByteLength(getByteLength() - unit->getByteLength());
        units.pop_front();
        drop(unit);
    }
    return unit;
}

size_t GatewayAggregationMessage::getUnitCnt(){
    return units.size();
}

} // namespace

