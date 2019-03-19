/*
 * Copyright (c) 2010, Loughborough University - Computer Science
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 */

/**
 * \file
 *         This node is part of the RPL multicast example. It basically
 *         represents a node that does not join the multicast group
 *         but still knows how to forward multicast packets
 *         The example will work with or without any number of these nodes
 *
 *         Also, performs some sanity checks for the contiki configuration
 *         and generates an error if the conf is bad
 *
 * \author
 *         George Oikonomou - <oikonomou@users.sourceforge.net>
 */

#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"
#include "net/ipv6/multicast/uip-mcast6.h"
#include "simstats.h"
#include "dev/watchdog.h"

#define DEBUG DEBUG_PRINT
#include "net/ip/uip-debug.h"

#if !UIP_CONF_ROUTER || !UIP_CONF_IPV6_RPL
#error "This example can not work with the current contiki configuration"
#error "Check the values of: UIP_CONF_IPV6, UIP_CONF_ROUTER, UIP_CONF_IPV6_RPL"
#endif

uint32_t lltx;
uint32_t pkttx;
uint32_t listen;
uint32_t transmit;
uint32_t lpm;
uint32_t cpu;


#if defined(MCAST_CONF_SEND_INTERVAL) && defined(MCAST_CONF_MESSAGES) && defined(MCAST_CONF_START_DELAY)
#define WAIT_FOR_END ((MCAST_CONF_SEND_INTERVAL * MCAST_CONF_MESSAGES) + MCAST_CONF_START_DELAY + 163)
#else
#define WAIT_FOR_END 160 + 50
#endif

/*---------------------------------------------------------------------------*/
PROCESS(mcast_intermediate_process, "Intermediate Process");
AUTOSTART_PROCESSES(&mcast_intermediate_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(mcast_intermediate_process, ev, data)
{
  static struct etimer et;
static struct etimer st;

  PROCESS_BEGIN();
watchdog_stop();
  etimer_set(&et, WAIT_FOR_END * CLOCK_SECOND);
  etimer_set(&st, MCAST_CONF_START_DELAY * CLOCK_SECOND);
  printf("WAIT_FOR_END: %u\n", WAIT_FOR_END);


  while(1) {
    PROCESS_YIELD();
    if(etimer_expired(&et)) {
      PRINTF("n; %lu; %lu; %lu; %lu; %lu; %lu\n",
        SIMSTATS_GET(lltx),
          SIMSTATS_GET(pkttx),
          energest_type_time(ENERGEST_TYPE_LISTEN),
          energest_type_time(ENERGEST_TYPE_TRANSMIT),
          energest_type_time(ENERGEST_TYPE_LPM),
          energest_type_time(ENERGEST_TYPE_CPU));
      etimer_stop(&et);
      break;
    }
  }


  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
