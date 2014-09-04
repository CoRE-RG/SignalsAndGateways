package majorNetwork;
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
network major_gateway_network
{
    parameters:
        @display("bgb=882,484,white");
        double measure_interval @unit(s) = default(1s);
        int countOfCanBussesGW1 = default(1);
        int countOfCanBussesGW2 = default(1);
        int countOfCanBussesGW3 = default(1);
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
            @display("i=abstract/bus;p=259,98");
        }
        canbus1_nodes[3]: CanNode {

            @display("p=129,52");
        }
        canbus2: CanBus {
            @display("i=abstract/bus;p=422,328");
        }
        canbus2_nodes[3]: CanNode {

            @display("p=422,424");
        }
        canbus3: CanBus {
            @display("i=abstract/bus;p=220,302");
        }
        canbus3_nodes[3]: CanNode {


            @display("p=129,385");
        }
        gateway1: Gateway1 {
            @display("p=324,149");
        }

        gateway2: Gateway2 {
            @display("p=324,277");
        }

        rtswitch: RTSwitch {
            parameters:
                @display("p=449,195");
            gates:
                ethg[3];
        }

        gateway3: Gateway3 {
            @display("p=560,195");
        }

        canbus4: CanBus {
            @display("i=abstract/bus;p=613,110");
        }
        canbus4_nodes[3]: CanNode {

            @display("p=696,79");
        }
        canbus5: CanBus {
            @display("i=abstract/bus;p=644,195");
        }
        canbus5_nodes[3]: CanNode {

            @display("p=755,195");
        }
        canbus6: CanBus {
            @display("i=abstract/bus;p=613,277");
        }
        canbus6_nodes[3]: CanNode {

            @display("p=696,313");
        }
    connections:
        //
        // The example uses a simple star topology
        //

        for i=0..(2) {
            canbus1.gate++ <--> canbus1_nodes[i].gate;
        }
        gateway1.cang[0] <--> cable {  delay = 50ns; } <--> canbus1.gate++;

        for i=0..(2) {
            canbus2.gate++ <--> canbus2_nodes[i].gate;
        }
        gateway2.cang[0] <--> cable {  delay = 50ns; } <--> canbus2.gate++;

        for i=0..(2) {
            canbus3.gate++ <--> canbus3_nodes[i].gate;
        }
        gateway2.cang[1] <--> cable {  delay = 50ns; } <--> canbus3.gate++;

        for i=0..(2) {
            canbus4.gate++ <--> canbus4_nodes[i].gate;
        }
        gateway3.cang[0] <--> cable {  delay = 50ns; } <--> canbus4.gate++;

        for i=0..(2) {
            canbus5.gate++ <--> canbus5_nodes[i].gate;
        }
        gateway3.cang[1] <--> cable {  delay = 50ns; } <--> canbus5.gate++;

        for i=0..(2) {
            canbus6.gate++ <--> canbus6_nodes[i].gate;
        }
        gateway3.cang[2] <--> cable {  delay = 50ns; } <--> canbus6.gate++;

        gateway1.ethg <--> cable {  delay = 100ns; } <--> rtswitch.ethg[0];
        gateway2.ethg <--> cable {  delay = 50ns; } <--> rtswitch.ethg[1];
        gateway3.ethg <--> cable {  delay = 50ns; } <--> rtswitch.ethg[2];
}
