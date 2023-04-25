package signalsandgateways.examples.car;

import core4inet.nodes.ethernet.avb_AS6802.TTEAVBEtherHost;
import inet.node.ethernet.EtherLink;
import fico4omnet.bus.can.CanBus;
import fico4omnet.nodes.can.CanNode;

network car
{
    parameters:
        @display("bgb=,,white");
        double measure_interval @unit(s) = default(1s);

    types:
        channel ETH_100MBIT extends EtherLink
        {
            datarate = 100000000bps;
            length = 0.0m;
            ber = 0.0;
            per = 0.0;
        }

    submodules:
        infotainment: infotainment {
            parameters:

                @display("p=728,762");
        }
        radar: radar {
            parameters:
                @display("p=619,121");
        }
        cas: cas {
            parameters:
                @display("p=728,1090");
        }
        fusi: fusi {
            parameters:
                @display("p=991,3008");
        }

        cam_Front: cam_Front {
            parameters:
                @display("p=811,121");
        }

        cam_Rear: cam_Rear {
            parameters:
                @display("p=619,3008");
        }

        lid_FrontLeft: lid_FrontLeft {
            parameters:
                @display("p=400,121");
        }

        lid_FrontRight: lid_FrontRight {
            parameters:
                @display("p=1195,121");
        }

        gw_FrontLeft: gw_FrontLeft {
            parameters:
                @display("p=247,704");
        }

        gw_Front: gw_Front {
            parameters:
                @display("p=991,762");
        }

        gw_FrontRight: gw_FrontRight {
            parameters:
                @display("p=1195,704");
        }

        gw_CenterLeft: gw_CenterLeft {
            parameters:
                @display("p=301,1147");
        }

        gw_Center: gw_Center {
            parameters:
                @display("p=991,1383");
        }

        gw_CenterRight: gw_CenterRight {
            parameters:
                @display("p=1450,1147");
        }

        gw_RearLeft: gw_RearLeft {
            parameters:
                @display("p=200,2858");
        }

        gw_Rear: gw_Rear {
            parameters:
                @display("p=811,3386");
        }

        gw_RearRight: gw_RearRight {
            parameters:
                @display("p=1459,2858");
        }

        ecu1: CanNode {
            parameters:
                @display("p=330,450");
        }

        ecu2: CanNode {
            parameters:
                @display("p=1450,450");
        }

        ecu3: CanNode {
            parameters:
                @display("p=200,1298");
        }

        ecu21: CanNode {
            parameters:
                @display("p=850,1630");
        }

        ecu34: CanNode {
            parameters:
                @display("p=380,1030");
        }

        ecu39: CanNode {
            parameters:
                @display("p=580,450");
        }

        ecu48: CanNode {
            parameters:
                @display("p=400,600");
        }

        ecu50: CanNode {
            parameters:
                @display("p=900,1450");
        }

        ecu51: CanNode {
            parameters:
                @display("p=900,880");
        }

        ecu64: CanNode {
            parameters:
                @display("p=900,120");
        }

        ecu65: CanNode {
            parameters:
                @display("p=900,1880");
        }

        ecu67: CanNode {
            parameters:
                @display("p=900,1780");
        }

        ecu70: CanNode {
            parameters:
                @display("p=900,4200");
        }

        ecu76: CanNode {
            parameters:
                @display("p=900,3260");
        }

        ecu80: CanNode {
            parameters:
                @display("p=1320,1000");
        }

        ecu84: CanNode {
            parameters:
                @display("p=182,4210");
        }

        ecu85: CanNode {
            parameters:
                @display("p=380,1000");
        }

        ecu88: CanNode {
            parameters:
                @display("p=450,1330");
        }

        ecu90: CanNode {
            parameters:
                @display("p=900,1000");
        }

        ecu91: CanNode {
            parameters:
                @display("p=1081,1604");
        }

        ecu93: CanNode {
            parameters:
                @display("p=1081,1656");
        }

        ecu94: CanNode {
            parameters:
                @display("p=1081,1701");
        }

        ecu95: CanNode {
            parameters:
                @display("p=1130,1604");
        }

        ecu96: CanNode {
            parameters:
                @display("p=1130,1656");
        }

        ecu97: CanNode {
            parameters:
                @display("p=1130,1701");
        }

        ecu99: CanNode {
            parameters:
                @display("p=1179,1604");
        }

        ecu100: CanNode {
            parameters:
                @display("p=1179,1656");
        }

        ecu103: CanNode {
            parameters:
                @display("p=900,4150");
        }

        ecu105: CanNode {
            parameters:
                @display("p=221,4210");
        }

        ecu106: CanNode {
            parameters:
                @display("p=221,1330");
        }

        ecu107: CanNode {
            parameters:
                @display("p=380,1730");
        }

        ecu111: CanNode {
            parameters:
                @display("p=400,1330");
        }

        ecu113: CanNode {
            parameters:
                @display("p=850,1530");
        }

        ecu114: CanNode {
            parameters:
                @display("p=380,1430");
        }

        ecu115: CanNode {
            parameters:
                @display("p=1250,1530");
        }

        ecu116: CanNode {
            parameters:
                @display("p=900,2000");
        }

        ecu121: CanNode {
            parameters:
                @display("p=380,1675");
        }

        ecu124: CanNode {
            parameters:
                @display("p=1700,1480");
        }

        ecu125: CanNode {
            parameters:
                @display("p=100,1480");
        }

        switch_Front: switch_Front {
            parameters:
                @display("p=811,704");
            gates:
                ethg[9];
        }

        switch_Center: switch_Center {
            parameters:
                @display("p=811,1147");
            gates:
                ethg[6];
        }

        switch_Rear: switch_Rear {
            parameters:
                @display("p=811,2858");
            gates:
                ethg[6];
        }

        bus1_FrontLeft: CanBus {
            parameters:
                @display("p=247,451");
            gates:
                gate[2];
        }
        
        bus3_FrontLeft: CanBus {
            parameters:
                @display("p=400,451");
            gates:
                gate[4];
        }

        bus5_FrontLeft: CanBus {
            parameters:
                @display("p=247,1001");
            gates:
                gate[2];
        }

        bus3_Front: CanBus {
            parameters:
                @display("p=900,762");
            gates:
                gate[2];
        }

        bus4_Front: CanBus {
            parameters:
                @display("p=991,121");
            gates:
                gate[2];
        }

        bus5_Front: CanBus {
            parameters:
                @display("p=991,1001");
            gates:
                gate[2];
        }

        bus1_FrontRight: CanBus {
            parameters:
                @display("p=1195,451");
            gates:
                gate[2];
        }

        bus5_FrontRight: CanBus {
            parameters:
                @display("p=1195,1001");
            gates:
                gate[2];
        }

        bus1_CenterLeft: CanBus {
            parameters:
                @display("p=200,1147");
            gates:
                gate[2];
        }

        bus5_CenterLeft: CanBus {
            parameters:
                @display("p=450,1238");
            gates:
                gate[2];
        }

        bus7_CenterLeft: CanBus {
            parameters:
                @display("p=301,1331");
            gates:
                gate[7];
        }

        bus2_Center: CanBus {
            parameters:
                @display("p=952,1631");
            gates:
                gate[2];
        }

        bus3_Center: CanBus {
            parameters:
                @display("p=900,1383");
            gates:
                gate[2];
        }

        bus4_Center: CanBus {
            parameters:
                @display("p=991,1781");
            gates:
                gate[3];
        }

        bus6_Center: CanBus {
            parameters:
                @display("p=1130,1383");
            gates:
                gate[9];
        }

        bus7_Center: CanBus {
            parameters:
                @display("p=1030,2001");
            gates:
                gate[3];
        }

        bus7_CenterRight: CanBus {
            parameters:
                @display("p=1450,1481");
            gates:
                gate[3];
        }

        bus5_RearLeft: CanBus {
            parameters:
                @display("p=62,3614");
            gates:
                gate[2];
        }

        bus7_RearLeft: CanBus {
            parameters:
                @display("p=340,3614");
            gates:
                gate[2];
        }

        bus4_Rear: CanBus {
            parameters:
                @display("p=811,4201");
            gates:
                gate[2];
        }

        bus5_Rear: CanBus {
            parameters:
                @display("p=900,3386");
            gates:
                gate[2];
        }

        bus6_Rear: CanBus {
            parameters:
                @display("p=900,3734");
            gates:
                gate[2];
        }

    connections:
        infotainment.ethg <--> ETH_100MBIT <--> switch_Front.ethg[8];
        radar.ethg <--> ETH_100MBIT <--> switch_Front.ethg[7];
        cas.ethg <--> ETH_100MBIT <--> switch_Center.ethg[5];
        gw_FrontLeft.ethg[0] <--> ETH_100MBIT <--> switch_Front.ethg[0];
        gw_Front.ethg[0] <--> ETH_100MBIT <--> switch_Front.ethg[1];
        gw_FrontRight.ethg[0] <--> ETH_100MBIT <--> switch_Front.ethg[2];
        gw_CenterLeft.ethg[0] <--> ETH_100MBIT <--> switch_Center.ethg[0];
        gw_Center.ethg[0] <--> ETH_100MBIT <--> switch_Center.ethg[1];
        gw_CenterRight.ethg[0] <--> ETH_100MBIT <--> switch_Center.ethg[2];
        gw_RearLeft.ethg[0] <--> ETH_100MBIT <--> switch_Rear.ethg[0];
        gw_Rear.ethg[0] <--> ETH_100MBIT <--> switch_Rear.ethg[1];
        gw_RearRight.ethg[0] <--> ETH_100MBIT <--> switch_Rear.ethg[2];
        switch_Front.ethg[3] <--> ETH_100MBIT <--> switch_Center.ethg[3];
        switch_Center.ethg[4] <--> ETH_100MBIT <--> switch_Rear.ethg[3];
        cam_Front.ethg <--> ETH_100MBIT <--> switch_Front.ethg[4];
        lid_FrontLeft.ethg <--> ETH_100MBIT <--> switch_Front.ethg[5];
        lid_FrontRight.ethg <--> ETH_100MBIT <--> switch_Front.ethg[6];
        cam_Rear.ethg <--> ETH_100MBIT <--> switch_Rear.ethg[4];
        fusi.ethg <--> ETH_100MBIT <--> switch_Rear.ethg[5];
        gw_FrontLeft.cang[0] <--> bus1_FrontLeft.gate[0];
        ecu1.gate <--> bus1_FrontLeft.gate[1];
        gw_FrontLeft.cang[1] <--> bus3_FrontLeft.gate[0];
        ecu34.gate <--> bus3_FrontLeft.gate[1];
        ecu39.gate <--> bus3_FrontLeft.gate[2];
        ecu48.gate <--> bus3_FrontLeft.gate[3];
        gw_FrontLeft.cang[2] <--> bus5_FrontLeft.gate[0];
        ecu85.gate <--> bus5_FrontLeft.gate[1];
        gw_Front.cang[0] <--> bus3_Front.gate[0];
        ecu51.gate <--> bus3_Front.gate[1];
        gw_Front.cang[1] <--> bus4_Front.gate[0];
        ecu64.gate <--> bus4_Front.gate[1];
        gw_Front.cang[2] <--> bus5_Front.gate[0];
        ecu90.gate <--> bus5_Front.gate[1];
        gw_FrontRight.cang[0] <--> bus1_FrontRight.gate[0];
        ecu2.gate <--> bus1_FrontRight.gate[1];
        gw_FrontRight.cang[1] <--> bus5_FrontRight.gate[0];
        ecu80.gate <--> bus5_FrontRight.gate[1];
        gw_CenterLeft.cang[0] <--> bus1_CenterLeft.gate[0];
        ecu3.gate <--> bus1_CenterLeft.gate[1];
        gw_CenterLeft.cang[1] <--> bus5_CenterLeft.gate[0];
        ecu88.gate <--> bus5_CenterLeft.gate[1];
        gw_CenterLeft.cang[2] <--> bus7_CenterLeft.gate[0];
        ecu106.gate <--> bus7_CenterLeft.gate[1];
        ecu107.gate <--> bus7_CenterLeft.gate[2];
        ecu111.gate <--> bus7_CenterLeft.gate[3];
        ecu114.gate <--> bus7_CenterLeft.gate[4];
        ecu121.gate <--> bus7_CenterLeft.gate[5];
        ecu125.gate <--> bus7_CenterLeft.gate[6];
        gw_Center.cang[0] <--> bus2_Center.gate[0];
        ecu21.gate <--> bus2_Center.gate[1];
        gw_Center.cang[1] <--> bus3_Center.gate[0];
        ecu50.gate <--> bus3_Center.gate[1];
        gw_Center.cang[2] <--> bus4_Center.gate[0];
        ecu65.gate <--> bus4_Center.gate[1];
        ecu67.gate <--> bus4_Center.gate[2];
        gw_Center.cang[3] <--> bus6_Center.gate[0];
        ecu91.gate <--> bus6_Center.gate[1];
        ecu93.gate <--> bus6_Center.gate[2];
        ecu94.gate <--> bus6_Center.gate[3];
        ecu95.gate <--> bus6_Center.gate[4];
        ecu96.gate <--> bus6_Center.gate[5];
        ecu97.gate <--> bus6_Center.gate[6];
        ecu99.gate <--> bus6_Center.gate[7];
        ecu100.gate <--> bus6_Center.gate[8];
        gw_Center.cang[4] <--> bus7_Center.gate[0];
        ecu113.gate <--> bus7_Center.gate[1];
        ecu116.gate <--> bus7_Center.gate[2];
        gw_CenterRight.cang[0] <--> bus7_CenterRight.gate[0];
        ecu115.gate <--> bus7_CenterRight.gate[1];
        ecu124.gate <--> bus7_CenterRight.gate[2];
        gw_RearLeft.cang[0] <--> bus5_RearLeft.gate[0];
        ecu84.gate <--> bus5_RearLeft.gate[1];
        gw_RearLeft.cang[1] <--> bus7_RearLeft.gate[0];
        ecu105.gate <--> bus7_RearLeft.gate[1];
        gw_Rear.cang[0] <--> bus4_Rear.gate[0];
        ecu70.gate <--> bus4_Rear.gate[1];
        gw_Rear.cang[1] <--> bus5_Rear.gate[0];
        ecu76.gate <--> bus5_Rear.gate[1];
        gw_Rear.cang[2] <--> bus6_Rear.gate[0];
        ecu103.gate <--> bus6_Rear.gate[1];

}
