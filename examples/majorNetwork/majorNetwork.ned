package signalsandgateways.examples.majorNetwork;
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
import core4inet.utilities.modules.MessageNumProfiler;

//
// Small sample network with three hosts and one switch that shows how to 
// configure the TTEthernet Model. Configuration in omnetpp.ini
// - Uses 5ms Cycletime
// - 80ns Tick length
//
network majorNetwork
{
    parameters:
        @display("bgb=936,484,white");
        double measure_interval @unit(s) = default(1s);
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
        //Profiler: MessageNumProfiler{}
        Antrieb: CanBus {
            @display("i=block/network;p=259,98");
        }
        Antrieb_nodes[3]: CanNode {

            @display("p=104,62");
        }
        Infotainment: CanBus {
            @display("i=block/network;p=422,328");
        }
        Infotainment_nodes[3]: CanNode {

            @display("p=422,424");
        }
        Fahrdynamik1: CanBus {
            @display("i=block/network;p=220,302");
        }
        Fahrdynamik1_nodes[3]: CanNode {


            @display("p=86,302");
        }
        gateway1: Gateway1 {
            @display("p=324,149");
        }

        gateway2: Gateway2 {
            @display("p=324,277");
        }

        switch: Switch {
            parameters:
                @display("p=449,195");
            gates:
                ethg[3];
        }

        gateway3: Gateway3 {
            @display("p=560,195");
        }

        Fahrdynamik2: CanBus {
            @display("i=block/network;p=613,110");
        }
        Fahrdynamik2_nodes[3]: CanNode {

            @display("p=773,71");
        }
        Komfort1: CanBus {
            @display("i=block/network;p=700,195");
        }
        Komfort1_nodes[3]: CanNode {

            @display("p=848,195");
        }
        Komfort2: CanBus {
            @display("i=block/network;p=613,277");
        }
        Komfort2_nodes[3]: CanNode {

            @display("p=751,316");
        }
    connections:
        //
        // The example uses a simple star topology
        //

        for i=0..(2) {
            Antrieb.gate++ <--> Antrieb_nodes[i].gate;
        }
        gateway1.cang[0] <--> Antrieb.gate++;

        for i=0..(2) {
            Infotainment.gate++ <--> Infotainment_nodes[i].gate;
        }
        gateway2.cang[0] <-->  Infotainment.gate++;

        for i=0..(2) {
            Fahrdynamik1.gate++ <--> Fahrdynamik1_nodes[i].gate;
        }
        gateway2.cang[1] <--> Fahrdynamik1.gate++;

        for i=0..(2) {
            Fahrdynamik2.gate++ <--> Fahrdynamik2_nodes[i].gate;
        }
        gateway3.cang[0] <--> Fahrdynamik2.gate++;

        for i=0..(2) {
            Komfort1.gate++ <--> Komfort1_nodes[i].gate;
        }
        gateway3.cang[1] <--> Komfort1.gate++;

        for i=0..(2) {
            Komfort2.gate++ <--> Komfort2_nodes[i].gate;
        }
        gateway3.cang[2] <--> Komfort2.gate++;

		gateway1.ethg[0] <--> cable {  delay = 100ns; } <--> switch.ethg[0];
        gateway2.ethg[0] <--> cable {  delay = 100ns; } <--> switch.ethg[1];
        gateway3.ethg[0] <--> cable {  delay = 100ns; } <--> switch.ethg[2];
}
