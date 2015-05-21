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

namespace SignalsAndGateways;

//
// This packet holds all Unit Messages which are going to be sent within an ethernet frame.
// 
packet GatewayAggregationMessage {
    @customize(true);
    uint8_t units;
    uint8_t sequence_number;
    uint8_t fragments;
    uint8_t fragment_number;
    byteLength = 4;
}
