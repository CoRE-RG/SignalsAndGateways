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

package signalsandgateways.applications.can;

import fico4omnet.linklayer.can.CanNodePort;
import fico4omnet.buffer.can.CanInputBuffer;
import fico4omnet.buffer.can.CanOutputBuffer;
import fico4omnet.applications.ISourceApplication;
import fico4omnet.applications.ISinkApplication;
import fico4omnet.scheduler.can.CanClock;

//
// Participant of the Gateway. Represents the CAN port of a gateway.
//
// Forwards data, remote and error frames.
//
// @see ~CanNodePort, ~CanInputBuffer, ~CanOutputBuffer, ~CanSourceGatewayApp, ~CanSinkGatewayApp, ~CanClock
//
// @author Sebastian Mueller
//
module CanGatewayNode
{
    parameters:
        @display("i=block/app2;bgb=248,222");
        
        // If errors are enabled: percentage of errors
        int errorperc = default(0);							
        
    gates:
        inout gate;
        output upperLayerOut;
        input upperLayerIn;

    submodules:
        canNodePort: CanNodePort {
            @display("p=149,168");
            gates:
                phygate;
        }
        
        bufferIn[1]: CanInputBuffer {
            @display("p=203,102");
            gates:
                in[1];
        }
        
        bufferOut: CanOutputBuffer {
            @display("p=98,102");
            MOB = false;
            gates:
                in[1];
        }
        
        sourceApp[1]: CanSourceGatewayApp {
            @display("p=98,32,row,70");
        }
        
        sinkApp[1]: CanSinkGatewayApp {
            @display("p=203,32");
        }
        
        canClock: CanClock {
            @display("p=149,102");
        }
        
    connections:
        canNodePort.phygate <--> gate;
        canNodePort.upperLayerIn <-- bufferOut.out;
        sourceApp[0].out --> bufferOut.in[0];
        
        sinkApp[0].out --> upperLayerOut;
        sourceApp[0].in <-- upperLayerIn;
}
