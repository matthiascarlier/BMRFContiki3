DEFINES+=PROJECT_CONF_H=\"project-conf.h\"
PROJECT_SOURCEFILES += simstats.c
UIP_CONF_IPV6=1

CONTIKI_PROJECT = root intermediate sink internal-seed
all: $(CONTIKI_PROJECT)

CONTIKI = ../../../..

MODULES += core/net/ipv6/multicast

include $(CONTIKI)/Makefile.include
