all: checkmakefiles src/signalsandgateways/features.h 
	cd src && $(MAKE)

clean: checkmakefiles
	cd src && $(MAKE) clean

cleanall: checkmakefiles
	cd src && $(MAKE) MODE=release clean
	cd src && $(MAKE) MODE=debug clean
	rm -f src/Makefile src/signalsandgateways/features.h

INET_PROJ=../../inet
CORE4INET_PROJ=../../CoRE4INET
FICO4OMNET_PROJ=../../FiCo4OMNeT
TMP_INCLUDES=-I../../CoRE4INET/src/core4inet/base/avb -I../../inet/src/inet/linklayer/ethernet -I../../CoRE4INET/src/core4inet/linklayer/ethernet/avb -I../../CoRE4INET/src/core4inet/linklayer/ethernet/base -I../../CoRE4INET/src/core4inet/linklayer/contract -I../../inet/src/inet/common -I../../CoRE4INET/src/core4inet/linklayer/ethernet/AS6802 -I../../CoRE4INET/src/core4inet/base -I../../CoRE4INET/src/core4inet/base/AS6802 -I../../CoRE4INET/src/core4inet/scheduler/period -I../../CoRE4INET/src/core4inet/scheduler/timer -I../../CoRE4INET/src/core4inet/utilities -I../../CoRE4INET/src/core4inet/scheduler/oscillator -I../../CoRE4INET/src/core4inet/applications/base -I../../CoRE4INET/src/core4inet/utilities/classes -I../../CoRE4INET/src/core4inet/buffer/AS6802 -I../../CoRE4INET/src/core4inet/applications/AS6802 -I../../CoRE4INET/src/core4inet -I../../CoRE4INET/src/core4inet/scheduler -I../../CoRE4INET/src/core4inet/buffer/base -I../../CoRE4INET/src/core4inet/incoming/base -I../../inet/src/inet
MAKEMAKE_OPTIONS := -f --deep --no-deep-includes $(TMP_INCLUDES) -I. -I$(INET_PROJ)/src/ -I$(CORE4INET_PROJ)/src/ -I$(FICO4OMNET_PROJ)/src/ -DINET_IMPORT -L$(INET_PROJ)/out/$$\(CONFIGNAME\)/src -L$(CORE4INET_PROJ)/out/$$\(CONFIGNAME\)/src -L$(FICO4OMNET_PROJ)/out/$$\(CONFIGNAME\)/src -lCoRE4INET -lINET -lFiCo4OMNeT -KINET_PROJ=$(INET_PROJ) -KCORE4INET_PROJ=$(CORE4INET_PROJ) -KFICO4OMNET_PROJ=$(FICO4OMNET_PROJ)

makefiles: src/signalsandgateways/features.h makefiles-so

makefiles-so:
	@FEATURE_OPTIONS=$$(./signalsandgateways_featuretool options -f -l) && cd src && opp_makemake --make-so $(MAKEMAKE_OPTIONS) $$FEATURE_OPTIONS

makefiles-lib:
	@FEATURE_OPTIONS=$$(./signalsandgateways_featuretool options -f -l) && cd src && opp_makemake --make-lib $(MAKEMAKE_OPTIONS) $$FEATURE_OPTIONS

makefiles-exe:
	@FEATURE_OPTIONS=$$(./signalsandgateways_featuretool options -f -l) && cd src && opp_makemake $(MAKEMAKE_OPTIONS) $$FEATURE_OPTIONS

checkmakefiles:
	@if [ ! -f src/Makefile ]; then \
	echo; \
	echo '======================================================================='; \
	echo 'src/Makefile does not exist. Please use "make makefiles" to generate it!'; \
	echo '======================================================================='; \
	echo; \
	exit 1; \
	fi

# generate an include file that contains all the WITH_FEATURE macros according to the current enablement of features
src/signalsandgateways/features.h: $(wildcard .oppfeaturestate) .oppfeatures
	@./signalsandgateways_featuretool defines >src/signalsandgateways/features.h

doxy:
	doxygen doxy.cfg