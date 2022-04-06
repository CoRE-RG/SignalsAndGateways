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

#ifndef SIGNALSANDGATEWAYS_ACCUMULATIONGATEWAYBUFFERING_H_
#define SIGNALSANDGATEWAYS_ACCUMULATIONGATEWAYBUFFERING_H_

//Std
#include <string>
#include <map>

//SignalsAndGateways
#include "signalsandgateways/base/SignalsAndGateways_Defs.h"

//Inet auto-generated messages
#include "inet/linklayer/ethernet/EtherFrame_m.h"
//FiCo4OMNeT auto-generated messages
#include "fico4omnet/linklayer/can/messages/CanDataFrame_m.h"
//SignalsAndGateways auto-generated messages
#include "signalsandgateways/gateway/messages/PoolMessage_m.h"

namespace SignalsAndGateways {

using namespace omnetpp;

/**
 * @brief This buffering module accumulates incoming can frames according to the configuration in the XML files.
 *
 * According to the XML files incoming can frames are grouped. Every frame has a specific hold up time and as soon as the timer of a frame reaches zero the whole group is forwarded to the transformation module.
 *
 * @author Stefan Buschmann, Timo Haeckel
 */
class AccumulationGatewayBuffering : public virtual cSimpleModule
{
public:
    /**
     * @brief Destructor
     */
    virtual ~AccumulationGatewayBuffering() override;

protected:
    /**
     * @brief Initialization of the module.
     */
    virtual void initialize() override;

    virtual void handleParameterChange(const char *parname) override;

    /**
     * @brief Self messages represent the end of a pool-hold-up time. Messages from the routing module are processed.
     *
     * @param msg Message from the routing module or self message from a pool.
     */
    virtual void handleMessage(cMessage *msg) override;

private:
    /**
     * @brief This map holds pointer to the lists which contain all messages which are currently in the pool. The canIDs serve as the keys.
     */
    std::map<unsigned int,cMessagePointerList*> poolMap;

    /**
     * @brief This map holds the maximum hold up time for the given canID.
     */
    std::map<unsigned int,simtime_t> holdUpTimes;

    /**
     * @brief This map holds the hold up time events for every pool.
     */
    std::map<cMessagePointerList*,cMessage*> scheduledHoldUpTimes;

    /**
     * @brief This maps holds the scheduled times for all pools of the gateway.
     */
    std::map<cMessage*,simtime_t> scheduledTimes;

    /**
     * @brief This map holds the arrival times of the messages which are currently buffered.
     */
    std::map<cMessagePointerList*,std::list<simtime_t>> poolArrivalTimes;

    /**
     * @brief Simsignal for the pool size.
     */
    std::vector<simsignal_t> poolSizeSignals;

    /**
     * @brief Signals that are emitted when a pool is forwarded to the next module.
     */
    std::vector<simsignal_t> poolHoldUpTimeSignals;

    /**
     * @brief Gateway ID in gateway config file. If auto or empty the gateway module name will be used.
     */
    std::string gatewayID;

    /**
     * @brief Gateway configuration using information from assigned XML file.
     */
    void readConfigXML();

    /**
     * @brief Returns a list with all messages which are currently in the pool based on a canID.
     */
    cMessagePointerList* getPoolList(unsigned int canID);

    /**
     * @brief Returns a list with all messages which are currently in the pool based on a holdUpTimeEvnet.
     */
    cMessagePointerList* getPoolList(cMessage* holdUpTimeEvent);

    /**
     * @brief Returns the hold up time for the given canID.
     */
    simtime_t getIDHoldUpTime(unsigned int canID);

    /**
     * @brief Returns the event which can be used to get the remaining hold up time for the given pool.
     */
    cMessage* getPoolHoldUpTimeEvent(cMessagePointerList* poolList);

    /**
     * @brief Returns the remaining hold up time for a specific pool to which the event is assigned.
     */
    simtime_t getCurrentPoolHoldUpTime(cMessage* poolHoldUpTimeEvent);

    /**
     * @brief Emits the arrival times of the messages which are forwarded to the transformation module.
     */
    void emitSignals(cMessagePointerList* poolList);

    /**
     * @brief Returns the id of a pool.
     */
    unsigned int getPoolID(cMessagePointerList* poolList);
};

} //namespace

#endif
