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
import signalsandgateways.gateway.IConnection;

//
// FieldSequenceMessage are redirected to a Buffer for accumulation of multiple Frames or optionally forwarded immediate. CanDataFrames are always forwarded immediate.
//
// The parameter "cumulate" indicates whether the incoming FieldSequenceMessages,
// which are produced by the Transformation module, are forwarded immediate or collected
// in a TimeTriggerdBuffer. The TimeTriggerdBuffer will hold the incoming messages for a
// preexisting time defined in the routing table(holdUpTime) to wait for contingently messages to the same virtual link.
// This opens the opportunity to collect multiple bus messages in a single ethernet backbone message.
//
// @see Dispatcher, TimeTriggeredBuffer
//
// @author Sebastian Mueller
//
simple PreBuffer like IConnection
{

    parameters:
        @display("bgb=209,144;i=block/queue");
        //Indicates whether frame accumulation is activated or not.
        bool cumulate = default(true);
    gates:
		//Input connection for the inter module data exchange within the gateway
        input in @label(InterConnectMsg);
        //Output connection for the inter module data exchange within the gateway
        output out @label(InterConnectMsg);
        //connection to the underlying module
        inout moduleConnect @label(InterConnectMsg);
}
