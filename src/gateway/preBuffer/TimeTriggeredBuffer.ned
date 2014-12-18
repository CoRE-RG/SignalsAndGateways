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
// Stores FieldSequenceMessages in a FieldSequenceBuffer according to a time strategy.
//
// According to the time strategy all stored messages in the FieldSequnceBuffer are retrieved and collected in a MultipleFieldSequenceMessage,
// which is send back to the Dispatcher.
// For each bus message, which is identified by the member-/object-ID, a maximum holdUpTime is defined in the routing table.
// The TimeTriggeredBuffer is using these parameters to calculate the remaining waiting time.
//
// @see Dispatcher, MultipleFieldSequenceMessage
//
// @author Sebastian Mueller
//
simple TimeTriggeredBuffer
{
    parameters:
        @display("i=block/timer");
    gates:
        //input connection for incoming data frames
        input bufferIn @directIn;
}
