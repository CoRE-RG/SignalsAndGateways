package majorNetwork.Archiv;

import fico4omnet.bus.can.CanBus;
import fico4omnet.nodes.can.CanNode;

// Generic network configuration for CAN-Networks
// 
// Can be used for various number of CAN-Nodes, but the design of the network can't be changed. Used for all examples.
module CanBus1
{
	@display("bgb=550,350,white");
	gates:
	    inout gatewayConnect;
    submodules:
        bus: CanBus {
            @display("i=abstract/bus");
        }
        node[3]: CanNode;
            
    connections:
        for i=0..(2) {
            bus.gate++ <--> node[i].gate;
        }
        bus.gate++ <--> gatewayConnect;
}