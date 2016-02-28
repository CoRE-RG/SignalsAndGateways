
//INET
#include "INETDefs.h"
//INET
#include "CoRE4INET_Defs.h"

#include "../features.h"
#include "inet/features.h"
#include "core4inet/features.h"
#include "fico4omnet/features.h"

/**
 * Check for minimal OMNeT++ Version requirements
 */
#if OMNETPP_VERSION < 0x0406
#  error At least OMNeT++/OMNEST version 4.6 required
#endif

/**
 * Check for minimal INET Version requirements
 */
#if INET_VERSION < 0x0301
#  error At least INET version 3.1 required
#endif

/**
 * Check for minimal CoRE4INET Version requirements
 */
#if CoRE4INET_VERSION < 0x0100
#  error At least CoRE4INET version 1.0 required
#endif

/**
 * Check for feature availability
 */
#ifndef WITH_ETHERNET
#  error You must enable the Ethernet feature in INET framework
#endif

#ifndef WITH_CAN_COMMON
#  error You must enable the CAN feature in FiCo4OMNeT
#endif

#ifndef WITH_FR_COMMON
#  error You must enable the FlexRay feature in FiCo4OMNeT
#endif

#ifndef WITH_AVB_COMMON
#  error You must enable the AVB feature in CoRE4INET
#endif

#ifndef WITH_AS6802_COMMON
#  error You must enable the AS6802 feature in CoRE4INET
#endif

#ifndef WITH_IEEE8021Q_COMMON
#  error You must enable the IEEE 802.1Q feature in CoRE4INET
#endif
