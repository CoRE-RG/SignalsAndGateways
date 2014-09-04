package smallNetwork;
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

import core4inet.nodes.ethernet.AS6802.TTEEtherHost;
import signalsandgateways.BusEthernetGateway;
import fico4omnet.bus.can.CanBus;
import fico4omnet.nodes.can.CanNode;

//
// Small sample network with three hosts and one switch that shows how to 
// configure the TTEthernet Model. Configuration in omnetpp.ini
// - Uses 5ms Cycletime
// - 80ns Tick length
//
network gateway_network
{
    parameters:
        @display("bgb=554,300,white");
        double measure_interval @unit(s) = default(1s);
        int countOfCanBussesGW1 = default(1);
        int countOfCanBussesGW2 = default(1);
    types:
        //
        // All links are configured with 100MBit per second and variable delay
        //
        channel cable extends ned.DatarateChannel
        {
            datarate = 100Mbps;
            //bit error rate (probability (0.0-1.0) per bit)  
            ber = 0;
            //packet error rate (probability (0.0-1.0) per packet)  
            per = 0;
        }
    submodules:
        canbus1: CanBus {
            @display("i=abstract/bus;p=104,150");
        }
        canbus1_nodes[2]: CanNode {

            @display("p=65,224");
        }
        canbus2: CanBus {
            @display("i=abstract/bus;p=434,150");
        }
        canbus2_nodes[2]: CanNode {

            @display("p=473,224");
        }
        gateway1: Gateway1 {
            @display("p=188,150");
        }

        rtswitch: RTSwitch {
            parameters:
                @display("p=262,62");
            gates:
                ethg[3];
        }

        gateway2: Gateway2 {
            @display("p=348,150");
        }

    connections:
        //
        // The example uses a simple star topology
        //

        gateway1.ethg <--> cable {  delay = 100ns; } <--> rtswitch.ethg[0];
        gateway2.ethg <--> cable {  delay = 50ns; } <--> rtswitch.ethg[1];

        for i=0..(1) {
            canbus1.gate++ <--> canbus1_nodes[i].gate;
        }
        gateway1.cang[0] <--> cable {  delay = 50ns; } <--> canbus1.gate++;

        for i=0..(1) {
            canbus2.gate++ <--> canbus2_nodes[i].gate;
        }
        gateway2.cang[0] <--> cable {  delay = 50ns; } <--> canbus2.gate++;
}
