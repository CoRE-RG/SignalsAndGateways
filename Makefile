all: checkmakefiles src/signalsandgateways/features.h 
	cd src && $(MAKE)

clean: checkmakefiles
	cd src && $(MAKE) clean

cleanall: checkmakefiles
	cd src && $(MAKE) MODE=release clean
	cd src && $(MAKE) MODE=debug clean
	rm -f src/Makefile src/signalsandgateways/features.h

INET_PROJ?=../../inet
CORE4INET_PROJ?=../../CoRE4INET
FICO4OMNET_PROJ?=../../FiCo4OMNeT
MAKEMAKE_OPTIONS := -f --deep --no-deep-includes -I. -I$(INET_PROJ)/src/ -I$(CORE4INET_PROJ)/src/ -I$(FICO4OMNET_PROJ)/src/ -DINET_IMPORT -L$(INET_PROJ)/src -L$(CORE4INET_PROJ)/src -L$(FICO4OMNET_PROJ)/src -lCoRE4INET -lINET -lFiCo4OMNeT -KINET_PROJ=$(INET_PROJ) -KCORE4INET_PROJ=$(CORE4INET_PROJ) -KFICO4OMNET_PROJ=$(FICO4OMNET_PROJ)

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