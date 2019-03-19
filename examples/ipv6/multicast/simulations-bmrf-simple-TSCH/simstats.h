/*
 * Copyright (c) 2014, VUB - ETRO.
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
 *
 */

/**
 * \file
 *         Header file for simulation statistics
 * \author
 *         Guillermo Gastón Lorente
 */

#ifndef SIMSTATS_H_
#define SIMSTATS_H_

struct simstats {
  unsigned long lltx;
  unsigned long pkttx;
unsigned long broadcastTX;
  unsigned long unicastTX;
};

#if SIMSTATS_CONF_ENABLED
/* Don't access this variable directly, use SIMSTATS_ADD and SIMSTATS_GET */
extern struct simstats simstats;

#define SIMSTATS_ADD(x) simstats.x++
#define SIMSTATS_GET(x) simstats.x
#else /* SIMSTATS_CONF_ENABLED */
#define SIMSTATS_ADD(x)
#define SIMSTATS_GET(x) 0
#endif /* SIMSTATS_CONF_ENABLED */

#endif /* SIMSTATS_H_ */
