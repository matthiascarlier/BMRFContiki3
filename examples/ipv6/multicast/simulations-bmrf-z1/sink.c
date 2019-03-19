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
 *         This node is part of the RPL multicast example. It is a node that
 *         joins a multicast group and listens for messages. It also knows how
 *         to forward messages down the tree.
 *         For the example to work, we need one or more of those nodes.
 *
 * \author
 *         George Oikonomou - <oikonomou@users.sourceforge.net>
 */

#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"
#include "net/ipv6/multicast/uip-mcast6.h"
#include "simstats.h"
#include "node-id.h"
//#include "random.h"
#include "dev/watchdog.h"

#include <string.h>

#define DEBUG DEBUG_PRINT
#include "net/ip/uip-debug.h"

#define MCAST_SINK_UDP_PORT 3001 /* Host byte order */

static struct uip_udp_conn *sink_conn;
static uint16_t count;
static uint8_t received[100];
static uint8_t duplicates;

uint32_t lltx;
uint32_t pkttx;
uint32_t listen;
uint32_t transmit;
uint32_t lpm;
uint32_t cpu;

int rseed;
uint32_t hops;

#define UIP_IP_BUF   ((struct uip_ip_hdr *)&uip_buf[UIP_LLH_LEN])

#define WAIT_END 50

#ifdef MCAST_CONF_START_DELAY
#define START_DELAY MCAST_CONF_START_DELAY
#else
#define START_DELAY 60
#endif

#if defined(MCAST_CONF_SEND_INTERVAL) && defined(MCAST_CONF_MESSAGES) && defined(MCAST_CONF_START_DELAY)
#define WAIT_FOR_END ((MCAST_CONF_SEND_INTERVAL * MCAST_CONF_MESSAGES) + MCAST_CONF_START_DELAY + 163)
#else
#define WAIT_FOR_END 160 + 65
#endif

#if !UIP_CONF_ROUTER || !UIP_CONF_IPV6_RPL
#error "This example can not work with the current contiki configuration"
#error "Check the values of: UIP_CONF_IPV6, UIP_CONF_ROUTER, UIP_CONF_IPV6_RPL"
#endif


//for TSCH
#include "net/ipv6/uip-ds6-route.h"
#include "net/mac/tsch/tsch.h"
#include "net/rpl/rpl-private.h"
#if WITH_ORCHESTRA
#include "orchestra.h"
#endif /* WITH_ORCHESTRA */
//END for TSCH
/*---------------------------------------------------------------------------*/
PROCESS(mcast_sink_process, "Multicast Sink");
AUTOSTART_PROCESSES(&mcast_sink_process);
/*---------------------------------------------------------------------------*/



static void
tcpip_handler(void)
{
  static uint8_t packet_number;
  hops = uip_ds6_if.cur_hop_limit - UIP_IP_BUF->ttl + 1;
  if(uip_newdata()) {
    packet_number = (uint8_t)uip_ntohl((unsigned long) *((uint32_t *)(uip_appdata)));
    if (received[packet_number] == 0) {
      count++;
      received[packet_number] = 1;
      PRINTF("In;%u\n",
      packet_number);
    } else {
      duplicates++;
      PRINTF("Received duplicate; packet number %u from ",
      packet_number);
      PRINTLLADDR(packetbuf_addr(PACKETBUF_ADDR_SENDER));
      PRINTF("\n");
    }
  }
  return;
}
/*---------------------------------------------------------------------------*/
static uip_ds6_maddr_t *
join_mcast_group(void)
{
  uip_ipaddr_t addr;
  uip_ds6_maddr_t *rv;

  /* First, set our v6 global */
  uip_ip6addr(&addr, 0xaaaa, 0, 0, 0, 0, 0, 0, 0);
  uip_ds6_set_addr_iid(&addr, &uip_lladdr);
  uip_ds6_addr_add(&addr, 0, ADDR_AUTOCONF);

  /*
   * IPHC will use stateless multicast compression for this destination
   * (M=1, DAC=0), with 32 inline bits (1E 89 AB CD)
   */
  uip_ip6addr(&addr, 0xFF1E,0,0,0,0,0,0x89,0xABCD);
  rv = uip_ds6_maddr_add(&addr);

  if(rv) {
    PRINTF("Joined multicast group ");
    PRINT6ADDR(&uip_ds6_maddr_lookup(&addr)->ipaddr);
    PRINTF("\n");
  }
  return rv;
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(mcast_sink_process, ev, data)
{
  static struct etimer et;
  static struct etimer et_init;
  static struct etimer st;

  PROCESS_BEGIN();

watchdog_stop();
  rseed = node_id;
  random_init(rseed);
  etimer_set(&et, WAIT_FOR_END * CLOCK_SECOND);
  //etimer_set(&et_init, START_DELAY * CLOCK_SECOND);
  etimer_set(&st, MCAST_CONF_START_DELAY * CLOCK_SECOND);

  PRINTF("Multicast Engine: '%s'\n", UIP_MCAST6.name);

  if(join_mcast_group() == NULL) {
    PRINTF("Failed to join multicast group\n");
    PROCESS_EXIT();
  }

  count = 0;

  sink_conn = udp_new(NULL, UIP_HTONS(0), NULL);
  udp_bind(sink_conn, UIP_HTONS(MCAST_SINK_UDP_PORT));

  PRINTF("Listening: ");
  PRINT6ADDR(&sink_conn->ripaddr);
  PRINTF(" local/remote port %u/%u\n",
        UIP_HTONS(sink_conn->lport), UIP_HTONS(sink_conn->rport));

  while(1) {
    PROCESS_YIELD();
    if(ev == tcpip_event) {
      tcpip_handler();
      //etimer_restart(&et);
    } else if(etimer_expired(&et)) {
      PRINTF("%u; %u; %lu; %lu; %lu; %lu; %lu; %lu\n",
        count,
	hops,
        SIMSTATS_GET(lltx),
          SIMSTATS_GET(pkttx),
          energest_type_time(ENERGEST_TYPE_LISTEN),
          energest_type_time(ENERGEST_TYPE_TRANSMIT),
          energest_type_time(ENERGEST_TYPE_LPM),
          energest_type_time(ENERGEST_TYPE_CPU));
      PRINTF("Duplicates; %u\n",
        duplicates);
    }
    // else if(etimer_expired(&et) && !etimer_expired(&et_init)){
    //   etimer_restart(&et);
    // } else if(!etimer_expired(&et) && etimer_expired(&et_init)){
    //   etimer_restart(&et);
    // }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
