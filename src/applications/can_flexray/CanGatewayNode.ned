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

package signalsandgateways.applications.can_flexray;

import fico4omnet.linklayer.can.CanNodePort;
import fico4omnet.buffer.can.CanInputBuffer;
import fico4omnet.buffer.can.CanOutputBuffer;
import fico4omnet.applications.ISourceApplication;
import fico4omnet.applications.can.source.CanTrafficSourceAppBase;
import fico4omnet.applications.can.sink.CanTrafficSinkAppBase;

//
// Participants in the network. 
//
// Generates data, remote and error frames.
//
//
module CanGatewayNode like IBusGatewayApplication
{
    parameters:
        int numSourceApps = default(1);						// Number of source apps in this node
        int errorperc = default(0);							// If errors are enabled: percentage of errors
        string node = default("0");							// Name of the node
        @display("i=block/app2;bgb=298,222");

    gates:
        inout gate;
        inout busInterface;
    submodules:
        canNodePort: CanNodePort {
            @display("p=149,168");
            gates:
                phygate;
        }
        bufferIn: CanInputBuffer {
            @display("p=233,102");
            gates:
                in[1];
        }
        bufferOut: CanOutputBuffer {
            @display("p=98,102");
            gates:
                in[numSourceApps];
        }
        sourceApp[numSourceApps]: CanSourceGatewayApp {
            @display("p=98,32,row,70");
        }
        sinkApp: CanSinkGatewayApp {
            @display("p=233,32");
        }
    connections:
        canNodePort.phygate <--> gate;
        canNodePort.upperLayerIn <-- bufferOut.out;
        canNodePort.upperLayerOut --> bufferIn.in[0];
        sinkApp.in <-- bufferIn.out;

        for i=0..numSourceApps-1 {
            sourceApp[i].out --> bufferOut.in[i];
            busInterface$i --> sourceApp[i].busInterfaceIn;
        }
        busInterface$o <-- sinkApp.busInterfaceOut;
}
