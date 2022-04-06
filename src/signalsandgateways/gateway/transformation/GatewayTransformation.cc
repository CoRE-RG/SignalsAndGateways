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

//std
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iterator>
#include <utility>
//INET
#include "inet/linklayer/common/MACAddress.h"
#include "inet/linklayer/ethernet/Ethernet.h"
//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
//FiCo4OMNeT
//Auto-generated messages
#include "fico4omnet/linklayer/can/messages/CanDataFrame_m.h"


using namespace std;
using namespace inet;
using namespace FiCo4OMNeT;
using namespace CoRE4INET;

namespace SignalsAndGateways {

Define_Module(GatewayTransformation);

const int GatewayTransformation::CANCRCBITLENGTH = 16;

void GatewayTransformation::initialize()
{
    handleParameterChange(nullptr);
    readConfigXML();
}

void GatewayTransformation::handleParameterChange(const char* parname) {

    if (!parname || !strcmp(parname, "gatewayID"))
    {
        this->gatewayID = par("gatewayID").stringValue();
        if(this->gatewayID.empty() || !strcmp(this->gatewayID.c_str(), "auto")){
            //auto create id!
            this->gatewayID = this->getParentModule()->getParentModule()->getName();
        }
    }
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
        }else if(GatewayAggregationMessage* rawDataFrame = dynamic_cast<GatewayAggregationMessage*>(msg)){
            transformedMsgs = transformRawDataFrame(rawDataFrame);
        }
        for(list<cMessage*>::iterator it = transformedMsgs.begin(); it != transformedMsgs.end(); ++it){
            send((*it), "out");
        }
    }
    delete msg;
}

void GatewayTransformation::readConfigXML(){
    //    string xpath = "/config/gateway[@id='" + gatewayName + "']/transformation[@destination='" + thisGateNo + "']";
    cXMLElement* xmlDoc = par("configXML").xmlValue();
    string gatewayName = this->gatewayID;
    string thisGateNo = to_string(this->getIndex());
    string xpath = "/config/gateway[@id='" + gatewayName + "']";
    cXMLElement* xmlGateway = xmlDoc->getElementByPath(xpath.c_str(), xmlDoc);
    cXMLElementList xmlTransformations = xmlGateway->getChildrenByTagName("transformation");
    for (auto iterTrans = xmlTransformations.begin(); iterTrans != xmlTransformations.end(); iterTrans++) {
        cXMLElement* xmlTransformation = *iterTrans;
        if(!strcmp(xmlTransformation->getAttribute("destination"), thisGateNo.c_str())){
            if(xmlTransformation){
                string type = xmlTransformation->getAttribute("type");
                if(type.compare("toEthernet") == 0){
                    cXMLElementList xmlEthernetFrames = xmlTransformation->getChildrenByTagName("ethernetframe");
                    for(cXMLElementList::iterator it = xmlEthernetFrames.begin(); it != xmlEthernetFrames.end(); ++it){
                        string xmlDst = (*it)->getAttribute("dst");
                        cXMLElementList xmlCanFrames = (*it)->getChildrenByTagName("canframe");
                        for(cXMLElementList::iterator it2 = xmlCanFrames.begin(); it2 != xmlCanFrames.end(); ++it2){
                            canToBEEthernet[static_cast<unsigned int>(atoi((*it2)->getAttribute("canId")))].push_back(xmlDst);
                        }
                    }
                    cXMLElementList xmlQFrames = xmlTransformation->getChildrenByTagName("ethernetqframe");
                    for(cXMLElementList::iterator it = xmlQFrames.begin(); it != xmlQFrames.end(); ++it){
                        string xmlDst = (*it)->getAttribute("dst");
                        const char* xmlVid = (*it)->getAttribute("vid");
                        int vid = 0;
                        if(xmlVid){
                            vid = atoi(xmlVid);
                            if(vid < 1 || vid > 4096){
                                vid = 0;
                            }
                        }
                        const char* xmlPcp = (*it)->getAttribute("pcp");
                        int pcp = 0;
                        if(xmlPcp){
                            pcp = atoi(xmlPcp);
                            if(pcp < 1 || pcp > 7){
                                pcp = 0;
                            }
                        }
                        cXMLElementList xmlCanFrames = (*it)->getChildrenByTagName("canframe");
                        for(cXMLElementList::iterator it2 = xmlCanFrames.begin(); it2 != xmlCanFrames.end(); ++it2){
                            QInfo qinfo;
                            qinfo.mac = xmlDst;
                            qinfo.vid = static_cast<uint16_t>(vid);
                            qinfo.pcp = static_cast<uint8_t>(pcp);
                            canToQEthernet[static_cast<unsigned int>(atoi((*it2)->getAttribute("canId")))].push_back(qinfo);
                        }
                    }
                    cXMLElementList xmlRCFrames = xmlTransformation->getChildrenByTagName("rcframe");
                    for(cXMLElementList::iterator it = xmlRCFrames.begin(); it != xmlRCFrames.end(); ++it){
                        uint16_t xmlCTID = static_cast<uint16_t>(atoi((*it)->getAttribute("ctId")));
                        cXMLElementList xmlCanFrames = (*it)->getChildrenByTagName("canframe");
                        for(cXMLElementList::iterator it2 = xmlCanFrames.begin(); it2 != xmlCanFrames.end(); ++it2){
                            canToRCEthernet[static_cast<unsigned int>(atoi((*it2)->getAttribute("canId")))].push_back(xmlCTID);
                        }
                    }
                    cXMLElementList xmlTTFrames = xmlTransformation->getChildrenByTagName("ttframe");
                    for(cXMLElementList::iterator it = xmlTTFrames.begin(); it != xmlTTFrames.end(); ++it){
                        uint16_t xmlCTID = static_cast<uint16_t>(atoi((*it)->getAttribute("ctId")));
                        cXMLElementList xmlCanFrames = (*it)->getChildrenByTagName("canframe");
                        for(cXMLElementList::iterator it2 = xmlCanFrames.begin(); it2 != xmlCanFrames.end(); ++it2){
                            canToTTEthernet[static_cast<unsigned int>(atoi((*it2)->getAttribute("canId")))].push_back(xmlCTID);
                        }
                    }
                }else if(type.compare("toCan") == 0){
                    cXMLElementList xmlCANFrames = xmlTransformation->getChildrenByTagName("canframe");
                    for(cXMLElementList::iterator it = xmlCANFrames.begin(); it != xmlCANFrames.end(); ++it){
                        unsigned int xmlCANID = static_cast<unsigned int>(atoi((*it)->getAttribute("canId")));
                        canToCan.push_back(xmlCANID);
                    }
                    cXMLElementList xmlEthernetFrames = xmlTransformation->getChildrenByTagName("ethernetframe");
                    for(cXMLElementList::iterator it = xmlEthernetFrames.begin(); it != xmlEthernetFrames.end(); ++it){
                        string xmlDst = (*it)->getAttribute("dst");
                        beEthernetToCan.push_back(xmlDst);
                    }
                    cXMLElementList xmlQFrames = xmlTransformation->getChildrenByTagName("ethernetqframe");
                    for(cXMLElementList::iterator it = xmlQFrames.begin(); it != xmlQFrames.end(); ++it){
                        string xmlDst = (*it)->getAttribute("dst");
                        qEthernetToCan.push_back(xmlDst);
                    }
                    cXMLElementList xmlRCFrames = xmlTransformation->getChildrenByTagName("rcframe");
                    for(cXMLElementList::iterator it = xmlRCFrames.begin(); it != xmlRCFrames.end(); ++it){
                        uint16_t xmlCTID = static_cast<uint16_t>(atoi((*it)->getAttribute("ctId")));
                        ctEthernetToCan.push_back(xmlCTID);
                    }
                    cXMLElementList xmlTTFrames = xmlTransformation->getChildrenByTagName("ttframe");
                    for(cXMLElementList::iterator it = xmlTTFrames.begin(); it != xmlTTFrames.end(); ++it){
                        uint16_t xmlCTID = static_cast<uint16_t>(atoi((*it)->getAttribute("ctId")));
                        ctEthernetToCan.push_back(xmlCTID);
                    }
                    cXMLElementList xmlAVBFrames = xmlTransformation->getChildrenByTagName("avbframe");
                    for(cXMLElementList::iterator it = xmlAVBFrames.begin(); it != xmlAVBFrames.end(); ++it){
                        uint16_t xmlStreamId = static_cast<uint16_t>(atoi((*it)->getAttribute("streamId")));
                        avbEthernetToCan.push_back(xmlStreamId);
                    }
                    cXMLElementList xmlRawData = xmlTransformation->getChildrenByTagName("rawdata");
                    for(cXMLElementList::iterator it = xmlRawData.begin(); it != xmlRawData.end(); ++it){
                        unsigned int xmlId = static_cast<unsigned int>(atoi((*it)->getAttribute("id")));
                        rawDataToCan.push_back(xmlId);
                    }
                }else if(type.compare("toMisc") == 0){
                    cXMLElementList xmlRawData = xmlTransformation->getChildrenByTagName("rawdata");
                    for(cXMLElementList::iterator it = xmlRawData.begin(); it != xmlRawData.end(); ++it){
                        uint16_t xmlId = static_cast<uint16_t>(atoi((*it)->getAttribute("id")));
                        cXMLElementList xmlCanFrames = (*it)->getChildrenByTagName("canframe");
                        for(cXMLElementList::iterator it2 = xmlCanFrames.begin(); it2 != xmlCanFrames.end(); ++it2){
                            canToRawData[static_cast<unsigned int>(atoi((*it2)->getAttribute("canId")))].push_back(xmlId);
                        }
                    }
                }
            }
        }
    }
}

list<cMessage*> GatewayTransformation::transformCanFrame(FiCo4OMNeT::CanDataFrame* canFrame){
    list<cMessage*> transformedMsgs;
    string messageName = createMessageName("singleFrame");
    // forward to another CAN?
    if(find(canToCan.begin(), canToCan.end(), canFrame->getCanID()) != canToCan.end()){
        transformedMsgs.push_back(canFrame->dup());
    }
    // forward to Q Ethernet
    if(canToQEthernet.find(canFrame->getCanID()) != canToQEthernet.end()){
        for(list<QInfo>::iterator it = canToQEthernet[canFrame->getCanID()].begin(); it != canToQEthernet[canFrame->getCanID()].end(); ++it){
            EthernetIIFrameWithQTag* qFrame = transformCanToQEthernet(canFrame);
            qFrame->setDest(MACAddress((*it).mac.c_str()));
            qFrame->setVID((*it).vid);
            qFrame->setPcp((*it).pcp);
            qFrame->setName(messageName.c_str());
            transformedMsgs.push_back(qFrame);
        }
    }
    // forward to RC Ethernet
    if(canToRCEthernet.find(canFrame->getCanID()) != canToRCEthernet.end()){
        for(list<uint16_t>::iterator it = canToRCEthernet[canFrame->getCanID()].begin(); it != canToRCEthernet[canFrame->getCanID()].end(); ++it){
            RCFrame* rcframe = transformCanToRCEthernet(canFrame);
            rcframe->setCtID(*it);
            rcframe->setName(messageName.c_str());
            transformedMsgs.push_back(rcframe);
        }
    }
    // forward to TT Ethernet
    if(canToTTEthernet.find(canFrame->getCanID()) != canToTTEthernet.end()){
        for(list<uint16_t>::iterator it = canToTTEthernet[canFrame->getCanID()].begin(); it != canToTTEthernet[canFrame->getCanID()].end(); ++it){
            TTFrame* ttframe = transformCanToTTEthernet(canFrame);
            ttframe->setCtID(*it);
            ttframe->setName(messageName.c_str());
            transformedMsgs.push_back(ttframe);
        }
    }
    // forward to RAW data subscribers
    if(canToRawData.find(canFrame->getCanID()) != canToRawData.end()){
        for(list<uint16_t>::iterator it = canToRawData[canFrame->getCanID()].begin(); it != canToRawData[canFrame->getCanID()].end(); ++it){
            GatewayAggregationMessage* rawdata = transformCanToRawData(canFrame);
            rawdata->setName(messageName.append(to_string(*it)).c_str());
            transformedMsgs.push_back(rawdata);
        }
    }
    // forward to BE Ethernet?
    if(canToBEEthernet.find(canFrame->getCanID()) != canToBEEthernet.end()){
        for(list<string>::iterator it = canToBEEthernet[canFrame->getCanID()].begin(); it != canToBEEthernet[canFrame->getCanID()].end(); ++it){
            EthernetIIFrame* ethernetFrame = transformCanToBEEthernet(canFrame);
            ethernetFrame->setDest(MACAddress((*it).c_str()));
            ethernetFrame->setName(messageName.c_str());
            transformedMsgs.push_back(ethernetFrame);
        }
    }
    return transformedMsgs;
}

list<cMessage*> GatewayTransformation::transformPoolMessage(PoolMessage* poolMessage){
    list<cMessage*> transformedMsgs;
    map<string, list<CanDataFrame*> > beTargetMap;
    map<string, pair<QInfo, list< CanDataFrame*> > > qTargetMap;
    map<uint16_t, list<CanDataFrame*> > rcTargetMap;
    map<uint16_t, list<CanDataFrame*> > ttTargetMap;
    map<uint16_t, list<CanDataFrame*> > rawTargetMap;
    cMessagePointerList pool = poolMessage->getPool();
    for(cMessagePointerList::iterator it = pool.begin(); it != pool.end(); ++it){
        CanDataFrame* canFrame= dynamic_cast<CanDataFrame*>(*it);
        take(canFrame);
        if(canToBEEthernet.find(canFrame->getCanID()) != canToBEEthernet.end()){
            for(list<string>::iterator it2 = canToBEEthernet[canFrame->getCanID()].begin(); it2 != canToBEEthernet[canFrame->getCanID()].end(); ++it2){
                beTargetMap[*it2].push_back(canFrame->dup());
            }
        }
        if(canToQEthernet.find(canFrame->getCanID()) != canToQEthernet.end()){
            for(list<QInfo>::iterator it2 = canToQEthernet[canFrame->getCanID()].begin(); it2 != canToQEthernet[canFrame->getCanID()].end(); ++it2){
                string targetID = ((*it2).mac + to_string((*it2).vid) + to_string((*it2).pcp));
                qTargetMap[targetID].first = (*it2);
                qTargetMap[targetID].second.push_back(canFrame->dup());
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
        if(canToRawData.find(canFrame->getCanID()) != canToRawData.end()){
            for(list<uint16_t>::iterator it2 = canToRawData[canFrame->getCanID()].begin(); it2 != canToRawData[canFrame->getCanID()].end(); ++it2){
                rawTargetMap[*it2].push_back(canFrame->dup());
            }
        }
        delete canFrame;
    }

    std::string messageName = createMessageName(poolMessage->getName());

    for(map<string, list<CanDataFrame*> >::iterator it = beTargetMap.begin(); it != beTargetMap.end(); ++it){
        EthernetIIFrame* ethernetFrame = transformCanToBEEthernet(it->second);
        ethernetFrame->setDest(MACAddress(it->first.c_str()));
        ethernetFrame->setName(messageName.data());
        transformedMsgs.push_back(ethernetFrame);
    }
    for(map<string, pair<QInfo, list<CanDataFrame*> > >::iterator it = qTargetMap.begin(); it != qTargetMap.end(); ++it){
        EthernetIIFrameWithQTag* qFrame = transformCanToQEthernet(it->second.second);
        qFrame->setDest(MACAddress(it->second.first.mac.c_str()));
        qFrame->setVID(it->second.first.vid);
        qFrame->setPcp(it->second.first.pcp);
        qFrame->setName(messageName.data());
        transformedMsgs.push_back(qFrame);
    }
    for(map<uint16_t, list<CanDataFrame*> >::iterator it = rcTargetMap.begin(); it != rcTargetMap.end(); ++it){
        RCFrame* rcFrame = transformCanToRCEthernet(it->second);
        rcFrame->setCtID(it->first);
        rcFrame->setName(messageName.data());
        transformedMsgs.push_back(rcFrame);
    }
    for(map<uint16_t, list<CanDataFrame*> >::iterator it = ttTargetMap.begin(); it != ttTargetMap.end(); ++it){
        TTFrame* ttFrame = transformCanToTTEthernet(it->second);
        ttFrame->setCtID(it->first);
        ttFrame->setName(messageName.data());
        transformedMsgs.push_back(ttFrame);
    }
    for(map<uint16_t, list<CanDataFrame*> >::iterator it = rawTargetMap.begin(); it != rawTargetMap.end(); ++it){
        GatewayAggregationMessage* rawData = transformCanToRawData(it->second);
        rawData->setName(messageName.append(to_string(it->first)).data());
        transformedMsgs.push_back(rawData);
    }
    return transformedMsgs;
}

list<cMessage*> GatewayTransformation::transformEthernetFrame(EthernetIIFrame* ethernetFrame){
    list<cMessage*> transformedMsgs;
    if(AVBFrame* avbFrame = dynamic_cast<AVBFrame*>(ethernetFrame)){
        if(find(avbEthernetToCan.begin(), avbEthernetToCan.end(), avbFrame->getStreamID()) != avbEthernetToCan.end()){
            list<CanDataFrame*> canFrames = transformEthernetToCan(avbFrame);
            for(list<CanDataFrame*>::iterator it = canFrames.begin(); it != canFrames.end(); ++it){
                transformedMsgs.push_back(dynamic_cast<cMessage*>(*it));
            }
        }
    }else if(CTFrame* ctFrame = dynamic_cast<CTFrame*>(ethernetFrame)){
        if(find(ctEthernetToCan.begin(), ctEthernetToCan.end(), ctFrame->getCtID()) != ctEthernetToCan.end()){
            list<CanDataFrame*> canFrames = transformEthernetToCan(ctFrame);
            for(list<CanDataFrame*>::iterator it = canFrames.begin(); it != canFrames.end(); ++it){
                transformedMsgs.push_back(dynamic_cast<cMessage*>(*it));
            }
        }
    }else if(EthernetIIFrameWithQTag* qFrame = dynamic_cast<EthernetIIFrameWithQTag*>(ethernetFrame)){
        if(find(qEthernetToCan.begin(), qEthernetToCan.end(), qFrame->getDest().str()) != qEthernetToCan.end()){
            list<CanDataFrame*> canFrames = transformEthernetToCan(qFrame);
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

std::list<cMessage*> GatewayTransformation::transformRawDataFrame(GatewayAggregationMessage* rawDataFrame) {
    list<cMessage*> transformedMsgs;
    if(rawDataFrame){
        if(rawDataFrame->getUnitCnt() != 1){
            std::string err = "Received RAW Frame with " + std::to_string(rawDataFrame->getUnitCnt()) + " Units. This is not yet supported.";
            throw cRuntimeError("%s", err.c_str());
        }
        if(CanDataFrame* rawCanFrame = dynamic_cast<CanDataFrame*>(rawDataFrame->getEncapUnits().front()->getEncapsulatedPacket())){
            if(find(rawDataToCan.begin(), rawDataToCan.end(), rawCanFrame->getCanID()) != rawDataToCan.end()){
                list<CanDataFrame*> canFrames = transformRawDataToCan(rawDataFrame);
                for(list<CanDataFrame*>::iterator it = canFrames.begin(); it != canFrames.end(); ++it){
                    transformedMsgs.push_back(dynamic_cast<cMessage*>(*it));
                }
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
        units.push_back(generateUnitMessage(*it));
    }
    GatewayAggregationMessage* gatewayAggregationMessage = generateGatewayAggregationMessage(units);
    EthernetIIFrame* ethernetFrame = new EthernetIIFrame();
    ethernetFrame->encapsulate(gatewayAggregationMessage);
    setEthernetFrameSize(ethernetFrame);
    return ethernetFrame;
}

EthernetIIFrameWithQTag* GatewayTransformation::transformCanToQEthernet(CanDataFrame* canFrame){
    list<UnitMessage*> units;
    units.push_back(generateUnitMessage(canFrame->dup()));
    GatewayAggregationMessage* gatewayAggregationMessage = generateGatewayAggregationMessage(units);
    EthernetIIFrameWithQTag* qFrame = new EthernetIIFrameWithQTag();
    qFrame->encapsulate(gatewayAggregationMessage);
    setEthernetQFrameSize(qFrame);
    return qFrame;
}

EthernetIIFrameWithQTag* GatewayTransformation::transformCanToQEthernet(list<CanDataFrame*> canFrames){
    list<UnitMessage*> units;
    for(list<CanDataFrame*>::iterator it = canFrames.begin(); it != canFrames.end(); ++it){
        units.push_back(generateUnitMessage(*it));
    }
    GatewayAggregationMessage* gatewayAggregationMessage = generateGatewayAggregationMessage(units);
    EthernetIIFrameWithQTag* qFrame = new EthernetIIFrameWithQTag();
    qFrame->encapsulate(gatewayAggregationMessage);
    setEthernetQFrameSize(qFrame);
    return qFrame;
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
        units.push_back(generateUnitMessage(*it));
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
        units.push_back(generateUnitMessage(*it));
    }
    GatewayAggregationMessage* gatewayAggregationMessage = generateGatewayAggregationMessage(units);
    TTFrame* ttFrame = new TTFrame();
    ttFrame->encapsulate(gatewayAggregationMessage);
    setEthernetFrameSize(ttFrame);
    return ttFrame;
}

GatewayAggregationMessage* GatewayTransformation::transformCanToRawData(CanDataFrame* canFrame){
    list<UnitMessage*> units;
    units.push_back(generateUnitMessage(canFrame->dup()));
    GatewayAggregationMessage* gatewayAggregationMessage = generateGatewayAggregationMessage(units);
    return gatewayAggregationMessage;
}

GatewayAggregationMessage* GatewayTransformation::transformCanToRawData(list<CanDataFrame*> canFrames){
    list<UnitMessage*> units;
    for(list<CanDataFrame*>::iterator it = canFrames.begin(); it != canFrames.end(); ++it){
        units.push_back(generateUnitMessage(*it));
    }
    GatewayAggregationMessage* gatewayAggregationMessage = generateGatewayAggregationMessage(units);
    return gatewayAggregationMessage;
}

list<CanDataFrame*> GatewayTransformation::transformEthernetToCan(EthernetIIFrame* ethernetFrame){
    list<CanDataFrame*> canFrames;
    GatewayAggregationMessage* gatewayAggregationMessage = dynamic_cast<GatewayAggregationMessage*>(ethernetFrame->decapsulate());
    if(gatewayAggregationMessage){
        while(UnitMessage* unitMessage = gatewayAggregationMessage->decapUnit()){
            CanDataFrame* canFrame = dynamic_cast<CanDataFrame*>(unitMessage->decapsulate());
            canFrame->setBitLength(canFrame->getBitLength() + CANCRCBITLENGTH);
            canFrames.push_back(canFrame);
            delete unitMessage;
        }
        delete gatewayAggregationMessage;
    }
    return canFrames;
}

std::list<FiCo4OMNeT::CanDataFrame*> GatewayTransformation::transformRawDataToCan(GatewayAggregationMessage* rawDataFrame) {
    list<CanDataFrame*> canFrames;
    if(rawDataFrame){
        while(UnitMessage* unitMessage = rawDataFrame->decapUnit()){
            CanDataFrame* canFrame = dynamic_cast<CanDataFrame*>(unitMessage->decapsulate());
            canFrame->setBitLength(canFrame->getBitLength() + CANCRCBITLENGTH);
            canFrames.push_back(canFrame);
            delete unitMessage;
        }
    }
    return canFrames;
}

void GatewayTransformation::setEthernetFrameSize(EthernetIIFrame* ethernetFrame){
    if(ethernetFrame->getEncapsulatedPacket()->getByteLength() <= (MIN_ETHERNET_FRAME_BYTES - ETHER_MAC_FRAME_BYTES)){
        ethernetFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
    }else{
        ethernetFrame->setByteLength(ethernetFrame->getEncapsulatedPacket()->getByteLength() + ETHER_MAC_FRAME_BYTES);
    }
}

void GatewayTransformation::setEthernetQFrameSize(EthernetIIFrameWithQTag* ethernetQFrame){
    if (ethernetQFrame->getEncapsulatedPacket()->getByteLength() <= (MIN_ETHERNET_FRAME_BYTES - ETHER_MAC_FRAME_BYTES - ETHER_8021Q_TAG_BYTES)){
        ethernetQFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
    }else{
        ethernetQFrame->setByteLength(ethernetQFrame->getEncapsulatedPacket()->getByteLength() + ETHER_MAC_FRAME_BYTES + ETHER_8021Q_TAG_BYTES);
    }
}

UnitMessage* GatewayTransformation::generateUnitMessage(CanDataFrame* canFrame){
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

string GatewayTransformation::createMessageName(const char* additionalInformation){
    string str;
    str.append(gatewayID);
    str.append(" - ");
    str.append(additionalInformation);
    return str;
}

} //namespace
