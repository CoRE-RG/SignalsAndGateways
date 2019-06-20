#Try to detect INET if variable is not set
ifndef INET_PROJ
    ifneq ($(wildcard ../inet),)
        INET_PROJ=../../inet
    else
        $(error "Cannot find INET framework in the usual location. You have to set the PATH to INET in the INET_PROJ variable")
    endif
endif
#Try to detect CoRE4INET if variable is not set
ifndef CORE4INET_PROJ
    ifneq ($(wildcard ../CoRE4INET),)
        CORE4INET_PROJ=../../CoRE4INET
    else
        $(error "Cannot find CoRE4INET framework in the usual location. You have to set the PATH to INET in the INET_PROJ variable")
    endif
endif
#Try to detect FiCo4OMNeT if variable is not set
ifndef FICO4OMNET_PROJ
    ifneq ($(wildcard ../FiCo4OMNeT),)
        FICO4OMNET_PROJ=../../FiCo4OMNeT
    else
        $(error "Cannot find FiCo4OMNeT in the usual location. You have to set the PATH to INET in the INET_PROJ variable")
    endif
endif

all: checkmakefiles src/signalsandgateways/features.h 
	cd src && $(MAKE)

clean: checkmakefiles
	cd src && $(MAKE) clean

cleanall: checkmakefiles
	cd src && $(MAKE) MODE=release clean
	cd src && $(MAKE) MODE=debug clean
	rm -f src/Makefile src/signalsandgateways/features.h

MAKEMAKE_OPTIONS := -f --deep --no-deep-includes -I. -I$(INET_PROJ)/src/ -I$(CORE4INET_PROJ)/src/ -I$(FICO4OMNET_PROJ)/src/ -L$(INET_PROJ)/src -L$(CORE4INET_PROJ)/src -L$(FICO4OMNET_PROJ)/src -lCoRE4INET_dbg -lINET_dbg -lFiCo4OMNeT_dbg -KINET_PROJ=$(INET_PROJ) -KCORE4INET_PROJ=$(CORE4INET_PROJ) -KFICO4OMNET_PROJ=$(FICO4OMNET_PROJ)

makefiles: src/signalsandgateways/features.h makefiles-so

makefiles-so:
	@FEATURE_OPTIONS=$$(opp_featuretool options -f -l -c) && cd src && opp_makemake --make-so $(MAKEMAKE_OPTIONS) $$FEATURE_OPTIONS

makefiles-lib:
	@FEATURE_OPTIONS=$$(opp_featuretool options -f -l -c) && cd src && opp_makemake --make-lib $(MAKEMAKE_OPTIONS) $$FEATURE_OPTIONS

makefiles-exe:
	@FEATURE_OPTIONS=$$(opp_featuretool options -f -l -c) && cd src && opp_makemake $(MAKEMAKE_OPTIONS) $$FEATURE_OPTIONS

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
	@opp_featuretool defines >src/signalsandgateways/features.h

doxy:
	doxygen doxy.cfg