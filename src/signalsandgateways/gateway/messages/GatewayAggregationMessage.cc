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

#include "signalsandgateways/gateway/messages/GatewayAggregationMessage.h"

using namespace std;

namespace SignalsAndGateways {

Register_Class(GatewayAggregationMessage);

void GatewayAggregationMessage::copy(const GatewayAggregationMessage& other){
    for(list<UnitMessage*>::const_iterator it = other.units.begin(); it != other.units.end(); ++it){
        UnitMessage* unit = (*it)->dup();
        take(unit);
        this->units.push_back(unit);
    }
}

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

list<UnitMessage*> GatewayAggregationMessage::getEncapUnits() const{
    return units;
}

size_t GatewayAggregationMessage::getUnitCnt(){
    return units.size();
}

} // namespace

