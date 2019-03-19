CONTIKI = ../../..
APPS = powertrace collect-view
CONTIKI_PROJECT = udp-sender udp-sink
PROJECT_SOURCEFILES += collect-common.c

CFLAGS += -DPROJECT_CONF_H=\"project-conf.h\"

ifeq ($(MAKE_WITH_NON_STORING),1)
CFLAGS += -DWITH_NON_STORING=1
endif

MAKE_WITH_ORCHESTRA = 1 # force Orchestra from command line
MAKE_WITH_SECURITY = 1 # force Security from command line

APPS += orchestra
MODULES += core/net/mac/tsch

ifeq ($(MAKE_WITH_ORCHESTRA),1)
CFLAGS += -DWITH_ORCHESTRA=1
endif

ifeq ($(MAKE_WITH_SECURITY),1)
CFLAGS += -DWITH_SECURITY=1
endif

ifdef PERIOD
CFLAGS=-DPERIOD=$(PERIOD)
endif

all: $(CONTIKI_PROJECT)

CONTIKI_WITH_IPV6 = 1
include $(CONTIKI)/Makefile.include
