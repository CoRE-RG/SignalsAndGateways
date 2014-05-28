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

package signalsandgateways.applications.ethernet;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherHost;
import core4inet.incoming.AS6802.TTIncoming;
import core4inet.buffer.AS6802.TTDoubleBuffer;
import core4inet.incoming.AS6802.RCIncoming;
import core4inet.buffer.AS6802.RCQueueBuffer;

//
// Represents the ethernet node in the ethernet backbone network with connection to the gateway.
//
// @author Sebastian Mueller
module EthernetGatewayHost extends TTEAVBEtherHost
{
    parameters:
        int numberOfTT_Vlinks = default(0);
        int numberOfRC_Vlinks = default(0);
        int numberOfBG_Vlinks = default(0);
    gates:
        inout ethInterface @labels(TransportMessage);
    submodules:
        //Application for the ethernet node in the gateway
        gatewayApp: TTEApplicationBase {
            @display("p=340,37");
        }
        //Vector of output buffers for timetriggered traffic(TT)
        TTvlinks[numberOfTT_Vlinks]: TTDoubleBuffer {
            @display("p=517,37");
        }
        //Vector of input buffers for timetriggered traffic(TT)
        TTvlinks_ctc[numberOfTT_Vlinks]: TTIncoming {
            @display("p=517,154");
        }
        //Vector of output buffers for rate constrained traffic(RC)
        RCvlinks[numberOfRC_Vlinks]: RCQueueBuffer {
            parameters:
                @display("p=768,37");
        }
        //Vector of input buffers for rate constrained traffic(RC)
        RCvlinks_ctc[numberOfRC_Vlinks]: RCIncoming {
            parameters:
                @display("p=768,154");
        }
    connections:
        ethInterface <--> gatewayApp.ethInterface;
        for i=0..numberOfTT_Vlinks-1 {
            TTvlinks_ctc[i].out --> TTvlinks[i].in;
        }
        for i=0..numberOfRC_Vlinks-1 {
            RCvlinks_ctc[i].out --> RCvlinks[i].in;
        }
}
