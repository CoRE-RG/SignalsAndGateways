package deprecatedSmallNetwork;

import fico4omnet.bus.can.CanBus;
import fico4omnet.nodes.can.CanNode;

// Generic network configuration for CAN-Networks
// 
// Can be used for various number of CAN-Nodes, but the design of the network can't be changed. Used for all examples.
module CanBus2
{
	@display("bgb=550,350,white");
	gates:
	    inout gatewayConnect;
    submodules:
        bus: CanBus {
            @display("i=abstract/bus");
        }
        node[2]: CanNode;
        
    connections:
        for i=0..(1) {
            bus.gate++ <--> node[i].gate;
        }
        bus.gate++ <--> gatewayConnect;
}