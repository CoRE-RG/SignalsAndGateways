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

package signalsandgateways.gateway.preBuffer;

//
// Dispatches the incoming messages to the appropriate TimeTriggeredBuffer.
//
// For each virtual link, which are defined in the routing table, the appropriate TimeTriggeredBuffer
// is generated automatically within the initialization process.
// Incoming messages are stored in the corresponding TimeTriggeredBuffer and will be hold there according to the time strategy.
// According to the time strategy all stored messages of the TimeTriggeredBuffer are returning to this Dispatcher in a MultipleFieldSequenceMessage.
//
// @see TimeTriggeredBuffer, MultipleFieldSequenceMessage
//
// @author Sebastian Mueller
//
simple Dispatcher
{
    parameters:
        @display("i=block/transport");
        //path to the routing table
        xml routingTable;
    gates:
        //input connection for returning messages of the TimeTriggeredBuffer
        input triggerIn @directIn;
        //connection to the overlying module
        inout moduleConnect @label(InterConnectMsg);
}
