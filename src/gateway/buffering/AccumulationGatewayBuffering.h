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

#ifndef __SIGNALSANDGATEWAYS_ACCUMULATIONGATEWAYBUFFERING_H_
#define __SIGNALSANDGATEWAYS_ACCUMULATIONGATEWAYBUFFERING_H_

#include <omnetpp.h>
#include <string>
#include <map>
#include "CanDataFrame_m.h"
#include "EtherFrame_m.h"
#include "PoolMessage_m.h"


namespace SignalsAndGateways {

/**
 * @brief This buffering module accumulates incoming can frames according to the configuration in the XML files.
 *
 * According to the XML files incoming can frames are grouped. Every frame has a specific hold up time and as soon as the timer of a frame reaches zero the whole group is forwarded to the transformation module.
 *
 */
class AccumulationGatewayBuffering : public cSimpleModule
{
  protected:
    /**
     * @brief Initialization of the module.
     */
    virtual void initialize();
    /**
     * @brief Self messages represent the end of a pool-hold-up time. Messages from the routing module are processed.
     *
     * @param msg Message from the routing module or self message from a pool.
     */
    virtual void handleMessage(cMessage *msg);

  private:
    std::map<unsigned int,cMessagePointerList*> poolMap;
    std::map<unsigned int,simtime_t> holdUpTimes;
    std::map<cMessagePointerList*,cMessage*> scheduledHoldUpTimes;
    std::map<cMessage*,simtime_t> scheduledTimes;

    /**
     * @brief Simsignal for the pool size.
     */
    simsignal_t poolSizeSignal;

    /**
     *
     */
    void readConfigXML();

    /**
     *
     */
    cMessagePointerList* getPoolList(unsigned int canID);

    /**
     *
     */
    cMessagePointerList* getPoolList(cMessage* holdUpTimeEvent);

    /**
     *
     */
    simtime_t getIDHoldUpTime(unsigned int canID);

    cMessage* getPoolHoldUpTimeEvent(cMessagePointerList* poolList);

    simtime_t getCurrentPoolHoldUpTime(cMessage* poolHoldUpTimeEvent);
};

} //namespace

#endif
