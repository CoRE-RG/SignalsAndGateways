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
        @display("bgb=936,511,white");
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
        Antrieb: CanBus {
            @display("i=block/network;p=220,62");
        }
        Antrieb_nodes[3]: CanNode {

            @display("p=86,62,c,60");
        }
        Infotainment: CanBus {
            @display("i=block/network;p=322,367");
        }
        Infotainment_nodes[3]: CanNode {

            @display("p=322,463,r,80");
        }
        Fahrdynamik1: CanBus {
            @display("i=block/network;p=220,277");
        }
        Fahrdynamik1_nodes[3]: CanNode {


            @display("p=86,277,c,60");
        }
        gateway1: Gateway1 {
            @display("p=324,149");
        }

        gateway2: Gateway2 {
            @display("p=324,277");
        }

        rtswitch: RTSwitch {
            parameters:
                @display("p=449,217");
            gates:
                ethg[3];
        }

        gateway3: Gateway3 {
            @display("p=560,217");
        }

        Fahrdynamik2: CanBus {
            @display("i=block/network;p=652,122");
        }
        Fahrdynamik2_nodes[3]: CanNode {

            @display("p=652,50,r,80");
        }
        Komfort1: CanBus {
            @display("i=block/network;p=652,217");
        }
        Komfort1_nodes[3]: CanNode {

            @display("p=778,157,c,60");
        }
        Komfort2: CanBus {
            @display("i=block/network;p=652,328");
        }
        Komfort2_nodes[3]: CanNode {

            @display("p=652,406,r,80");
        }
    connections:
        //
        // The example uses a simple star topology
        //

        for i=0..(2) {
            Antrieb.gate++ <--> Antrieb_nodes[i].gate;
        }
        gateway1.cang[0] <--> cable {  delay = 50ns; } <--> Antrieb.gate++;

        for i=0..(2) {
            Infotainment.gate++ <--> Infotainment_nodes[i].gate;
        }
        gateway2.cang[0] <--> cable {  delay = 50ns; } <--> Infotainment.gate++;

        for i=0..(2) {
            Fahrdynamik1.gate++ <--> Fahrdynamik1_nodes[i].gate;
        }
        gateway2.cang[1] <--> cable {  delay = 50ns; } <--> Fahrdynamik1.gate++;

        for i=0..(2) {
            Fahrdynamik2.gate++ <--> Fahrdynamik2_nodes[i].gate;
        }
        gateway3.cang[0] <--> cable {  delay = 50ns; } <--> Fahrdynamik2.gate++;

        for i=0..(2) {
            Komfort1.gate++ <--> Komfort1_nodes[i].gate;
        }
        gateway3.cang[1] <--> cable {  delay = 50ns; } <--> Komfort1.gate++;

        for i=0..(2) {
            Komfort2.gate++ <--> Komfort2_nodes[i].gate;
        }
        gateway3.cang[2] <--> cable {  delay = 50ns; } <--> Komfort2.gate++;

        gateway1.ethg <--> cable {  delay = 100ns; } <--> rtswitch.ethg[0];
        gateway2.ethg <--> cable {  delay = 100ns; } <--> rtswitch.ethg[1];
        gateway3.ethg <--> cable {  delay = 100ns; } <--> rtswitch.ethg[2];
}
