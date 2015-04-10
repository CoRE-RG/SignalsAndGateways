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

#include "GatewayTransformation.h"

#include <algorithm>

using namespace std;
using namespace FiCo4OMNeT;
using namespace CoRE4INET;

namespace SignalsAndGateways {

Define_Module(GatewayTransformation);

const int GatewayTransformation::CANCRCBITLENGTH = 16;

void GatewayTransformation::initialize()
{
    readConfigXML();
}

void GatewayTransformation::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("in")){
        list<cMessage*> transformedMsgs;
        if(CanDataFrame* canFrame = dynamic_cast<CanDataFrame*>(msg)){
            transformedMsgs = transformCanFrame(canFrame);
        }else if(PoolMessage* poolMessage = dynamic_cast<PoolMessage*>(msg)){
            transformedMsgs = transformPoolMessage(poolMessage);
        }else if(EthernetIIFrame* ethernetFrame = dynamic_cast<EthernetIIFrame*>(msg)){
            transformedMsgs = transformEthernetFrame(ethernetFrame);
        }
        for(list<cMessage*>::iterator it = transformedMsgs.begin(); it != transformedMsgs.end(); ++it){
            send((*it), "out");
        }
    }
    delete msg;
}

void GatewayTransformation::readConfigXML(){
    cXMLElement* xmlDoc = par("configXML").xmlValue();
    string gatewayName = this->getParentModule()->getParentModule()->getName();
    string thisGateNo = to_string(this->getIndex());
    string xpath = "/config/gateway[@id='" + gatewayName + "']/transformation[@destination='" + thisGateNo + "']";
    cXMLElement* xmlTransformation = xmlDoc->getElementByPath(xpath.c_str(), xmlDoc);
    if(xmlTransformation){
        string type = xmlTransformation->getAttribute("type");
        if(type.compare("canToEthernet") == 0){
            cXMLElementList xmlEthernetFrames = xmlTransformation->getChildrenByTagName("ethernetFrame");
            for(cXMLElementList::iterator it = xmlEthernetFrames.begin(); it != xmlEthernetFrames.end(); ++it){
                string xmlDst = (*it)->getAttribute("dst");
                cXMLElementList xmlCanFrames = (*it)->getChildrenByTagName("canFrame");
                for(cXMLElementList::iterator it2 = xmlCanFrames.begin(); it2 != xmlCanFrames.end(); ++it2){
                    canToBEEthernet[atoi((*it2)->getAttribute("canId"))].push_back(xmlDst);
                }
            }
        }else if(type.compare("ethernetToCan") == 0){
            cXMLElementList xmlEthernetFrames = xmlTransformation->getChildrenByTagName("ethernetFrame");
            for(cXMLElementList::iterator it = xmlEthernetFrames.begin(); it != xmlEthernetFrames.end(); ++it){
                string xmlDst = (*it)->getAttribute("dst");
                beEthernetToCan.push_back(xmlDst);
            }
        }
    }
}

list<cMessage*> GatewayTransformation::transformCanFrame(FiCo4OMNeT::CanDataFrame* canFrame){
    list<cMessage*> transformedMsgs;
    if(canToBEEthernet.find(canFrame->getCanID()) != canToBEEthernet.end()){
        for(list<string>::iterator it = canToBEEthernet[canFrame->getCanID()].begin(); it != canToBEEthernet[canFrame->getCanID()].end(); ++it){
            EthernetIIFrame* ethernetFrame = transformCanToBEEthernet(canFrame);
            ethernetFrame->setDest(MACAddress((*it).c_str()));
            transformedMsgs.push_back(ethernetFrame);
        }
    }else if(canToRCEthernet.find(canFrame->getCanID()) != canToRCEthernet.end()){

    }else if(canToTTEthernet.find(canFrame->getCanID()) != canToTTEthernet.end()){

    }
    return transformedMsgs;
}

list<cMessage*> GatewayTransformation::transformPoolMessage(PoolMessage* poolMessage){
    list<cMessage*> transformedMsgs;
    map<string, list<CanDataFrame*> > beTargetMap;
    map<uint16_t, list<CanDataFrame*> > rcTargetMap;
    map<uint16_t, list<CanDataFrame*> > ttTargetMap;
    cMessagePointerList pool = poolMessage->getPool();
    for(cMessagePointerList::iterator it = pool.begin(); it != pool.end(); ++it){
        CanDataFrame* canFrame= dynamic_cast<CanDataFrame*>(*it);
        take(canFrame);
        if(canToBEEthernet.find(canFrame->getCanID()) != canToBEEthernet.end()){
            for(list<string>::iterator it2 = canToBEEthernet[canFrame->getCanID()].begin(); it2 != canToBEEthernet[canFrame->getCanID()].end(); ++it2){
                beTargetMap[*it2].push_back(canFrame->dup());
            }
        }
        if(canToRCEthernet.find(canFrame->getCanID()) != canToRCEthernet.end()){
            for(list<uint16_t>::iterator it2 = canToRCEthernet[canFrame->getCanID()].begin(); it2 != canToRCEthernet[canFrame->getCanID()].end(); ++it2){
                rcTargetMap[*it2].push_back(canFrame->dup());
            }
        }
        if(canToTTEthernet.find(canFrame->getCanID()) != canToTTEthernet.end()){
            for(list<uint16_t>::iterator it2 = canToTTEthernet[canFrame->getCanID()].begin(); it2 != canToTTEthernet[canFrame->getCanID()].end(); ++it2){
                ttTargetMap[*it2].push_back(canFrame->dup());
            }
        }
        delete canFrame;
    }
    for(map<string, list<CanDataFrame*> >::iterator it = beTargetMap.begin(); it != beTargetMap.end(); ++it){
        EthernetIIFrame* ethernetFrame = transformCanToBEEthernet(it->second);
        ethernetFrame->setDest(MACAddress(it->first.c_str()));
        transformedMsgs.push_back(ethernetFrame);
    }
    for(map<uint16_t, list<CanDataFrame*> >::iterator it = rcTargetMap.begin(); it != rcTargetMap.end(); ++it){
        RCFrame* rcFrame = transformCanToRCEthernet(it->second);
        rcFrame->setCtID(it->first);
        transformedMsgs.push_back(rcFrame);
    }
    for(map<uint16_t, list<CanDataFrame*> >::iterator it = ttTargetMap.begin(); it != ttTargetMap.end(); ++it){
        TTFrame* ttFrame = transformCanToTTEthernet(it->second);
        ttFrame->setCtID(it->first);
        transformedMsgs.push_back(ttFrame);
    }
    return transformedMsgs;
}

list<cMessage*> GatewayTransformation::transformEthernetFrame(EthernetIIFrame* ethernetFrame){
    list<cMessage*> transformedMsgs;
    if(AVBFrame* avbFrame = dynamic_cast<AVBFrame*>(ethernetFrame)){
        //TODO
    }else if(CTFrame* ctFrame = dynamic_cast<CTFrame*>(ethernetFrame)){
        if(find(ctEthernetToCan.begin(), ctEthernetToCan.end(), ctFrame->getCtID()) != ctEthernetToCan.end()){
            list<CanDataFrame*> canFrames = transformEthernetToCan(ctFrame);
            for(list<CanDataFrame*>::iterator it = canFrames.begin(); it != canFrames.end(); ++it){
                transformedMsgs.push_back(dynamic_cast<cMessage*>(*it));
            }
        }
    }else{
        if(find(beEthernetToCan.begin(), beEthernetToCan.end(), ethernetFrame->getDest().str()) != beEthernetToCan.end()){
            list<CanDataFrame*> canFrames = transformEthernetToCan(ethernetFrame);
            for(list<CanDataFrame*>::iterator it = canFrames.begin(); it != canFrames.end(); ++it){
                transformedMsgs.push_back(dynamic_cast<cMessage*>(*it));
            }
        }
    }
    return transformedMsgs;
}

EthernetIIFrame* GatewayTransformation::transformCanToBEEthernet(FiCo4OMNeT::CanDataFrame* canFrame){
    list<UnitMessage*> units;
    units.push_back(generateUnitMessage(canFrame->dup()));
    GatewayAggregationMessage* gatewayAggregationMessage = generateGatewayAggregationMessage(units);
    EthernetIIFrame* ethernetFrame = new EthernetIIFrame();
    ethernetFrame->encapsulate(gatewayAggregationMessage);
    setEthernetFrameSize(ethernetFrame);
    return ethernetFrame;
}

EthernetIIFrame* GatewayTransformation::transformCanToBEEthernet(list<CanDataFrame*> canFrames){
    list<UnitMessage*> units;
    for(list<CanDataFrame*>::iterator it = canFrames.begin(); it != canFrames.end(); ++it){
        units.push_back(generateUnitMessage(dynamic_cast<CanDataFrame*>(*it)));
    }
    GatewayAggregationMessage* gatewayAggregationMessage = generateGatewayAggregationMessage(units);
    EthernetIIFrame* ethernetFrame = new EthernetIIFrame();
    ethernetFrame->encapsulate(gatewayAggregationMessage);
    setEthernetFrameSize(ethernetFrame);
    return ethernetFrame;
}

RCFrame* GatewayTransformation::transformCanToRCEthernet(CanDataFrame* canFrame){
    list<UnitMessage*> units;
    units.push_back(generateUnitMessage(canFrame->dup()));
    GatewayAggregationMessage* gatewayAggregationMessage = generateGatewayAggregationMessage(units);
    RCFrame* rcFrame = new RCFrame();
    rcFrame->encapsulate(gatewayAggregationMessage);
    setEthernetFrameSize(rcFrame);
    return rcFrame;
}

RCFrame* GatewayTransformation::transformCanToRCEthernet(list<CanDataFrame*> canFrames){
    list<UnitMessage*> units;
    for(list<CanDataFrame*>::iterator it = canFrames.begin(); it != canFrames.end(); ++it){
        units.push_back(generateUnitMessage(dynamic_cast<CanDataFrame*>(*it)));
    }
    GatewayAggregationMessage* gatewayAggregationMessage = generateGatewayAggregationMessage(units);
    RCFrame* rcFrame = new RCFrame();
    rcFrame->encapsulate(gatewayAggregationMessage);
    setEthernetFrameSize(rcFrame);
    return rcFrame;
}

TTFrame* GatewayTransformation::transformCanToTTEthernet(CanDataFrame* canFrame){
    list<UnitMessage*> units;
    units.push_back(generateUnitMessage(canFrame->dup()));
    GatewayAggregationMessage* gatewayAggregationMessage = generateGatewayAggregationMessage(units);
    TTFrame* ttFrame = new TTFrame();
    ttFrame->encapsulate(gatewayAggregationMessage);
    setEthernetFrameSize(ttFrame);
    return ttFrame;
}

TTFrame* GatewayTransformation::transformCanToTTEthernet(list<CanDataFrame*> canFrames){
    list<UnitMessage*> units;
    for(list<CanDataFrame*>::iterator it = canFrames.begin(); it != canFrames.end(); ++it){
        units.push_back(generateUnitMessage(dynamic_cast<CanDataFrame*>(*it)));
    }
    GatewayAggregationMessage* gatewayAggregationMessage = generateGatewayAggregationMessage(units);
    TTFrame* ttFrame = new TTFrame();
    ttFrame->encapsulate(gatewayAggregationMessage);
    setEthernetFrameSize(ttFrame);
    return ttFrame;
}

list<CanDataFrame*> GatewayTransformation::transformEthernetToCan(EthernetIIFrame* ethernetFrame){
    list<CanDataFrame*> canFrames;
    GatewayAggregationMessage* gatewayAggregationMessage = dynamic_cast<GatewayAggregationMessage*>(ethernetFrame->decapsulate());
    while(UnitMessage* unitMessage = gatewayAggregationMessage->decapUnit()){
        CanDataFrame* canFrame = dynamic_cast<CanDataFrame*>(unitMessage->decapsulate());
        canFrame->setBitLength(canFrame->getBitLength() + CANCRCBITLENGTH);
        canFrames.push_back(canFrame);
        delete unitMessage;
    }
    delete gatewayAggregationMessage;
    return canFrames;
}

void GatewayTransformation::setEthernetFrameSize(EthernetIIFrame* ethernetFrame){
    if(ethernetFrame->getEncapsulatedPacket()->getByteLength() <= (MIN_ETHERNET_FRAME_BYTES - ETHER_MAC_FRAME_BYTES)){
        ethernetFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
    }else{
        ethernetFrame->setByteLength(ethernetFrame->getEncapsulatedPacket()->getByteLength() + ETHER_MAC_FRAME_BYTES);
    }
}

UnitMessage* GatewayTransformation::generateUnitMessage(FiCo4OMNeT::CanDataFrame* canFrame){
    UnitMessage* unitMessage = new UnitMessage();
    canFrame->setBitLength(canFrame->getBitLength() - CANCRCBITLENGTH);
    unitMessage->setLength(static_cast<uint16_t>(canFrame->getByteLength()));
    unitMessage->encapsulate(canFrame);
    return unitMessage;
}

GatewayAggregationMessage* GatewayTransformation::generateGatewayAggregationMessage(list<UnitMessage*> units){
    GatewayAggregationMessage* gatewayAggregationMessage = new GatewayAggregationMessage();
    for(list<UnitMessage*>::iterator it = units.begin(); it != units.end(); ++it){
        gatewayAggregationMessage->encapUnit((*it));
    }
    gatewayAggregationMessage->setUnits(static_cast<uint8_t>(gatewayAggregationMessage->getUnitCnt()));
    return gatewayAggregationMessage;
}

} //namespace