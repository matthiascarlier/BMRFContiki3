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
 *         This node is part of the RPL multicast example. It is an RPL root
 *         and sends a multicast message periodically. For the example to work,
 *         we need one of those nodes.
 *
 * \author
 *         George Oikonomou - <oikonomou@users.sourceforge.net>
 */


#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"
#include "net/ipv6/multicast/uip-mcast6.h"

#include <string.h>

#define DEBUG DEBUG_PRINT
#include "net/ip/uip-debug.h"
#include "net/rpl/rpl.h"

#include "simstats.h"

#define MAX_PAYLOAD_LEN 120
#define MCAST_SINK_UDP_PORT 3001 /* Host byte order */

#ifdef MCAST_CONF_SEND_INTERVAL
#define SEND_INTERVAL MCAST_CONF_SEND_INTERVAL * CLOCK_SECOND /* clock ticks */
#else
#define SEND_INTERVAL CLOCK_SECOND
#endif
#ifdef MCAST_CONF_MESSAGES
#define ITERATIONS MCAST_CONF_MESSAGES /* messages */
#else
#define ITERATIONS 10
#endif

/* Start sending messages START_DELAY secs after we start so that routing can
 * converge */
#ifdef MCAST_CONF_START_DELAY
#define START_DELAY MCAST_CONF_START_DELAY
#else
#define START_DELAY 60
#endif

// sender power
// possible values =  0dBm = 31;  -1dBm = 27;  -3dBm = 23;  -5dBm = 19;
//                   -7dBm = 15; -10dBm = 11; -15dBm =  7; -25dBM =  3;
uint8_t power = 15;

static struct uip_udp_conn * mcast_conn;
static char buf[MAX_PAYLOAD_LEN];
static uint32_t seq_id;


int startedSending = 0;
uint32_t lltx;
uint32_t pkttx;
uint32_t listen;
uint32_t transmit;
uint32_t lpm;
uint32_t cpu;

#if !UIP_CONF_ROUTER || !UIP_CONF_IPV6_RPL
#error "This example can not work with the current contiki configuration"
#error "Check the values of: UIP_CONF_IPV6, UIP_CONF_ROUTER, UIP_CONF_IPV6_RPL, UIP_CONF_IPV6_MULTICAST"
#endif


/*---------------------------------------------------------------------------*/
PROCESS(rpl_root_process, "RPL ROOT, Multicast Sender");
AUTOSTART_PROCESSES(&rpl_root_process);
/*---------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------
 * SETTING THE GPIOS
 *-------------------------------------------------------------------------------*/

void
GPIOS_init(void)
{
	//configuring pin as GPIO

	P1SEL &= ~0xC1;			//GPIO P1.0 P1.6 P1.7
	P2SEL &= ~0x18;			//GPIO P2.3 P2.4
	P4SEL &= ~0x0D;			//GPIO P4.0 P4.2 P4.3

	//configuring pin as OUTPUT

	P1DIR |= 0xC1;
	P2DIR |= 0x18;
	P4DIR |= 0x0D;


}

void
clear_GPIOS(void)
{
//clear all output pins
	P1OUT &= ~BIT6;		//P1.6 AS 0
	P1OUT &= ~BIT7;		//P1.7 AS 0

	P2OUT &= ~BIT3;		//P2.3 AS 0
	P2OUT &= ~BIT4;		//P2.4 AS 0

	P4OUT &= ~BIT0;		//P4.0 AS 0
	P4OUT &= ~BIT2;		//P4.2 AS 0
	P4OUT &= ~BIT3;		//P4.3 AS 0

}

/*---------------------------------------------------------------------------*/



static void
multicast_send(void)
{
  uint32_t id;

  id = uip_htonl(seq_id);
  memset(buf, 0, MAX_PAYLOAD_LEN);
  memcpy(buf, &id, sizeof(seq_id));

  PRINTF("Send to: ");
  PRINT6ADDR(&mcast_conn->ripaddr);
  PRINTF(" Remote Port %u,", uip_ntohs(mcast_conn->rport));
  PRINTF(" (msg=0x%08lx)", (unsigned long)uip_ntohl(*((uint32_t *)buf)));
  PRINTF(" %lu bytes\n", (unsigned long)sizeof(id));

  PRINTF("Out;%lu;n\n", seq_id);
  
  
  
  static uint8_t seqno_bits[6];				//convert seqno into bits for sending to white receiver
	uint8_t i;
    for (i = 0; i < 6; i++) {
	seqno_bits[i] = seq_id & (1 << i) ? 1 : 0;
    }		//least significant bit in seqno_bits[0]

    clear_GPIOS();
    if ( seqno_bits[0]==1 )	P1OUT |= BIT6;       //  write a 1 in P1.6
    if ( seqno_bits[1]==1 )	P1OUT |= BIT7;       //  write a 1 in P1.7
    if ( seqno_bits[2]==1 )	P2OUT |= BIT3;       //  write a 1 in P2.3
    if ( seqno_bits[3]==1 )	P4OUT |= BIT0;       //  write a 1 in P4.0
    //if ( seqno_bits[4]==1 )	P4OUT |= BIT2;       //  write a 1 in P4.2
    //if ( seqno_bits[5]==1 )	P4OUT |= BIT3;       //  write a 1 in P4.3
        P1OUT ^= BIT0;               // change state of P1.0 to trigger reading by white mote
  seq_id++;  
  
  uip_udp_packet_send(mcast_conn, buf, sizeof(id));
}
/*---------------------------------------------------------------------------*/
static void
prepare_mcast(void)
{
  uip_ipaddr_t ipaddr;

  /*
   * IPHC will use stateless multicast compression for this destination
   * (M=1, DAC=0), with 32 inline bits (1E 89 AB CD)
   */
  uip_ip6addr(&ipaddr, 0xFF1E,0,0,0,0,0,0x89,0xABCD);
  mcast_conn = udp_new(&ipaddr, UIP_HTONS(MCAST_SINK_UDP_PORT), NULL);
}
/*---------------------------------------------------------------------------*/
static void
set_own_addresses(void)
{
  int i;
  uint8_t state;
  rpl_dag_t *dag;
  uip_ipaddr_t ipaddr;

  uip_ip6addr(&ipaddr, 0xaaaa, 0, 0, 0, 0, 0, 0, 0);
  uip_ds6_set_addr_iid(&ipaddr, &uip_lladdr);
  uip_ds6_addr_add(&ipaddr, 0, ADDR_AUTOCONF);

  PRINTF("Our IPv6 addresses:\n");
  for(i = 0; i < UIP_DS6_ADDR_NB; i++) {
    state = uip_ds6_if.addr_list[i].state;
    if(uip_ds6_if.addr_list[i].isused && (state == ADDR_TENTATIVE || state
        == ADDR_PREFERRED)) {
      PRINTF("  ");
      PRINT6ADDR(&uip_ds6_if.addr_list[i].ipaddr);
      PRINTF("\n");
      if(state == ADDR_TENTATIVE) {
        uip_ds6_if.addr_list[i].state = ADDR_PREFERRED;
      }
    }
  }

  /* Become root of a new DODAG with ID our global v6 address */
  dag = rpl_set_root(RPL_DEFAULT_INSTANCE, &ipaddr);
  if(dag != NULL) {
    rpl_set_prefix(dag, &ipaddr, 64);
    PRINTF("Created a new RPL dag with ID: ");
    PRINT6ADDR(&dag->dag_id);
    PRINTF("\n");
  }
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(rpl_root_process, ev, data)
{
  static struct etimer et;

  PROCESS_BEGIN();
  
   GPIOS_init();
  /*Set the tx_power to reduce collision and have a real multi-hop network*/
  cc2420_set_txpower(power);

  PRINTF("Multicast Engines: '%s'\n", UIP_MCAST6.name);

  NETSTACK_MAC.off(1);

  set_own_addresses();

  prepare_mcast();

  etimer_set(&et, START_DELAY * CLOCK_SECOND);
  while(1) {
    PROCESS_YIELD();
    if(etimer_expired(&et)) {
      if(seq_id == ITERATIONS) {
        etimer_stop(&et);
        PRINTF("n; %lu; %lu; %lu; %lu; %lu; %lu; 0\n",
          SIMSTATS_GET(lltx),
          SIMSTATS_GET(pkttx),
          energest_type_time(ENERGEST_TYPE_LISTEN),
          energest_type_time(ENERGEST_TYPE_TRANSMIT),
          energest_type_time(ENERGEST_TYPE_LPM),
          energest_type_time(ENERGEST_TYPE_CPU));
      } else {
        multicast_send();
        etimer_set(&et, SEND_INTERVAL);
      }
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
