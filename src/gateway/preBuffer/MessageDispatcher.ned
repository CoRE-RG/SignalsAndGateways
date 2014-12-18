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
// Represents the connection between dispatching messages and storing respectively cumulating messages in the TimeTriggeredBuffers.
//
// @author Sebastian Mueller
module MessageDispatcher
{
    parameters:
        //number of varied virual links defined in the routing table
        int totalNumberOfVlinks = default(0);
        @display("bgb=268,218;i=block/subqueue");
    gates:
        //connection between Dispatcher and PreBuffer
        inout moduleConnect @label(InterConnectMsg);
    submodules:
        //vector of TimeTriggeredBuffers to store and cumulate the messages
        messageBuffers[totalNumberOfVlinks]: TimeTriggeredBuffer {
            @display("p=134,125");
        }
        //redirectes the incoming messages to the corresponding TimeTriggeredBuffer
        dispatcher: Dispatcher {
            @display("p=134,45");
        }
    connections:
        //inter module connection of Dispatcher and PreBuffer
        moduleConnect <--> dispatcher.moduleConnect;
}
