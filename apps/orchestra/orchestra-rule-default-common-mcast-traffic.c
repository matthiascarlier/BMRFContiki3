/*
 * Copyright (c) 2015, Swedish Institute of Computer Science.
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
 */
/**
 * \file
 *         Orchestra: a slotframe with a single shared link, common to all nodes
 *         in the network, used for unicast and broadcast.
 *
 * \author Simon Duquennoy <simonduq@sics.se>
 */

#include "contiki.h"
#include "orchestra.h"

#define UIP_IP_BUF ((struct uip_ip_hdr *)&uip_buf[UIP_LLH_LEN])

static uint16_t slotframe_handle = 0;
static uint16_t channel_offset = 0;


/* There is no slotframe for EBs, use this slotframe both EB and non-EB traffic */
#define ORCHESTRA_COMMON_SHARED_TYPE              LINK_TYPE_ADVERTISING

/*---------------------------------------------------------------------------*/
static int
select_packet(uint16_t *slotframe, uint16_t *timeslot)
{//TODO: broadcast doesnt work now..
  uip_ipaddr_t ipaddr;
  uip_ip6addr(&ipaddr, 0xFF1E,0,0,0,0,0,0x89,0xABCD);

	  //if(uip_is_addr_mcast(&UIP_IP_BUF->destipaddr) && (packetbuf_attr(PACKETBUF_ATTR_FRAME_TYPE) != FRAME802154_BEACONFRAME) && !uip_ipaddr_cmp(&UIP_IP_BUF->destipaddr, &ipaddr)) {printf("accepted\n");
  if(uip_is_addr_mcast(&UIP_IP_BUF->destipaddr) && packetbuf_attr(PACKETBUF_ATTR_FRAME_TYPE) != FRAME802154_BEACONFRAME) {
	  if(slotframe != NULL) {
		*slotframe = slotframe_handle;
	  }
	  if(timeslot != NULL) {
		*timeslot = 0;
	  }
	  return 1;
  }
  return 0; 
}
/*---------------------------------------------------------------------------*/
static void
init(uint16_t sf_handle)
{
  slotframe_handle = sf_handle;
  channel_offset = slotframe_handle;
  /* Default slotframe: for broadcast or unicast to neighbors we
   * do not have a link to */
  struct tsch_slotframe *sf_common = tsch_schedule_add_slotframe(slotframe_handle, ORCHESTRA_COMMON_SHARED_PERIOD);
  tsch_schedule_add_link(sf_common,
      LINK_OPTION_RX | LINK_OPTION_TX | LINK_OPTION_SHARED,
      ORCHESTRA_COMMON_SHARED_TYPE, &tsch_broadcast_address,
      0, channel_offset);
}
/*---------------------------------------------------------------------------*/
struct orchestra_rule default_common_mcast_traffic = {
  init,
  NULL,
  select_packet,
  NULL,
  NULL,
};
