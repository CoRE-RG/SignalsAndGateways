package signalsandgateways.examples.smallNetwork;
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

//package signalsandgateways.examples;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherSwitch;
import core4inet.incoming.AS6802.TTIncoming;
import core4inet.buffer.AS6802.TTQueueBuffer;
import core4inet.incoming.AS6802.RCIncoming;
import core4inet.buffer.AS6802.RCQueueBuffer;

//
// switch1: configuration in switch1.ini
//
module Switch extends TTEAVBEtherSwitch
{
    parameters:
        @display("bgb=627,384");
    submodules:
        TTvlinks[1]: TTQueueBuffer {
            @display("p=567,41");
        }
        TTvlinks_ctc[1]: TTIncoming {
            @display("p=567,150");
        }
    connections:
        TTvlinks_ctc[0].out --> TTvlinks[0].in;
}
