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

//
// Small sample network with three hosts and one switch that shows how to 
// configure the TTEthernet Model. Configuration in omnetpp.ini
// - Uses 5ms Cycletime
// - 80ns Tick length
//
network gateway_network
{
    parameters:
        @display("bgb=417,213,white");
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
        canbus1: CanBus1 {
            @display("p=39,70");
        }

        gateway1: Gateway1 {
            @display("p=115,158");
        }

        rtswitch: RTSwitch {
            parameters:
                @display("p=189,70");
            gates:
                ethg[3];
        }

        gateway2: Gateway2 {
            @display("p=275,158");
        }

        canbus2: CanBus2 {
            @display("p=365,70");
        }

    connections:
        //
        // The example uses a simple star topology
        //
        gateway1.cang <--> cable {  delay = 50ns; } <--> canbus1.gatewayConnect;
        gateway1.ethg <--> cable {  delay = 100ns; } <--> rtswitch.ethg[0];
        gateway2.ethg <--> cable {  delay = 50ns; } <--> rtswitch.ethg[1];
        gateway2.cang <--> cable {  delay = 50ns; } <--> canbus2.gatewayConnect;
}
