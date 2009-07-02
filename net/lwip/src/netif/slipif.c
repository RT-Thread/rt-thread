/**
 * @file
 * SLIP Interface
 *
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
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
 * This file is built upon the file: src/arch/rtxc/netif/sioslip.c
 *
 * Author: Magnus Ivarsson <magnus.ivarsson(at)volvo.com> 
 */

/* 
 * This is an arch independent SLIP netif. The specific serial hooks must be
 * provided by another file. They are sio_open, sio_recv and sio_send
 */

#include "netif/slipif.h"
#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "lwip/sio.h"

#define SLIP_END     0300 /* 0xC0 */
#define SLIP_ESC     0333 /* 0xDB */
#define SLIP_ESC_END 0334 /* 0xDC */
#define SLIP_ESC_ESC 0335 /* 0xDD */

#define MAX_SIZE     1500

/**
 * Send a pbuf doing the necessary SLIP encapsulation
 *
 * Uses the serial layer's sio_send()
 *
 * @param netif the lwip network interface structure for this slipif
 * @param p the pbuf chaing packet to send
 * @param ipaddr the ip address to send the packet to (not used for slipif)
 * @return always returns ERR_OK since the serial layer does not provide return values
 */
err_t
slipif_output(struct netif *netif, struct pbuf *p, struct ip_addr *ipaddr)
{
  struct pbuf *q;
  u16_t i;
  u8_t c;

  LWIP_ASSERT("netif != NULL", (netif != NULL));
  LWIP_ASSERT("netif->state != NULL", (netif->state != NULL));
  LWIP_ASSERT("p != NULL", (p != NULL));

  LWIP_UNUSED_ARG(ipaddr);

  /* Send pbuf out on the serial I/O device. */
  sio_send(SLIP_END, netif->state);

  for (q = p; q != NULL; q = q->next) {
    for (i = 0; i < q->len; i++) {
      c = ((u8_t *)q->payload)[i];
      switch (c) {
      case SLIP_END:
        sio_send(SLIP_ESC, netif->state);
        sio_send(SLIP_ESC_END, netif->state);
        break;
      case SLIP_ESC:
        sio_send(SLIP_ESC, netif->state);
        sio_send(SLIP_ESC_ESC, netif->state);
        break;
      default:
        sio_send(c, netif->state);
        break;
      }
    }
  }
  sio_send(SLIP_END, netif->state);
  return ERR_OK;
}

/**
 * Handle the incoming SLIP stream character by character
 *
 * Poll the serial layer by calling sio_recv()
 *
 * @param netif the lwip network interface structure for this slipif
 * @return The IP packet when SLIP_END is received 
 */
static struct pbuf *
slipif_input(struct netif *netif)
{
  u8_t c;
  /* q is the whole pbuf chain for a packet, p is the current pbuf in the chain */
  struct pbuf *p, *q;
  u16_t recved;
  u16_t i;

  LWIP_ASSERT("netif != NULL", (netif != NULL));
  LWIP_ASSERT("netif->state != NULL", (netif->state != NULL));

  q = p = NULL;
  recved = i = 0;
  c = 0;

  while (1) {
    c = sio_recv(netif->state);
    switch (c) {
    case SLIP_END:
      if (recved > 0) {
        /* Received whole packet. */
        /* Trim the pbuf to the size of the received packet. */
        pbuf_realloc(q, recved);
        
        LINK_STATS_INC(link.recv);
        
        LWIP_DEBUGF(SLIP_DEBUG, ("slipif: Got packet\n"));
        return q;
      }
      break;

    case SLIP_ESC:
      c = sio_recv(netif->state);
      switch (c) {
      case SLIP_ESC_END:
        c = SLIP_END;
        break;
      case SLIP_ESC_ESC:
        c = SLIP_ESC;
        break;
      }
      /* FALLTHROUGH */

    default:
      /* byte received, packet not yet completely received */
      if (p == NULL) {
        /* allocate a new pbuf */
        LWIP_DEBUGF(SLIP_DEBUG, ("slipif_input: alloc\n"));
        p = pbuf_alloc(PBUF_LINK, PBUF_POOL_BUFSIZE, PBUF_POOL);

        if (p == NULL) {
          LINK_STATS_INC(link.drop);
          LWIP_DEBUGF(SLIP_DEBUG, ("slipif_input: no new pbuf! (DROP)\n"));
          /* don't process any further since we got no pbuf to receive to */
          break;
        }

        if (q != NULL) {
          /* 'chain' the pbuf to the existing chain */
          pbuf_cat(q, p);
        } else {
          /* p is the first pbuf in the chain */
          q = p;
        }
      }

      /* this automatically drops bytes if > MAX_SIZE */
      if ((p != NULL) && (recved <= MAX_SIZE)) {
        ((u8_t *)p->payload)[i] = c;
        recved++;
        i++;
        if (i >= p->len) {
          /* on to the next pbuf */
          i = 0;
          if (p->next != NULL && p->next->len > 0) {
            /* p is a chain, on to the next in the chain */
            p = p->next;
          } else {
            /* p is a single pbuf, set it to NULL so next time a new
             * pbuf is allocated */
            p = NULL;
          }
        }
      }
      break;
    }
  }
  return NULL;
}

#if !NO_SYS
/**
 * The SLIP input thread.
 *
 * Feed the IP layer with incoming packets
 *
 * @param nf the lwip network interface structure for this slipif
 */
static void
slipif_loop(void *nf)
{
  struct pbuf *p;
  struct netif *netif = (struct netif *)nf;

  while (1) {
    p = slipif_input(netif);
    if (p != NULL) {
      if (netif->input(p, netif) != ERR_OK) {
        pbuf_free(p);
        p = NULL;
      }
    }
  }
}
#endif /* !NO_SYS */

/**
 * SLIP netif initialization
 *
 * Call the arch specific sio_open and remember
 * the opened device in the state field of the netif.
 *
 * @param netif the lwip network interface structure for this slipif
 * @return ERR_OK if serial line could be opened,
 *         ERR_IF is serial line couldn't be opened
 *
 * @note netif->num must contain the number of the serial port to open
 *       (0 by default)
 */
err_t
slipif_init(struct netif *netif)
{

  LWIP_DEBUGF(SLIP_DEBUG, ("slipif_init: netif->num=%"U16_F"\n", (u16_t)netif->num));

  netif->name[0] = 's';
  netif->name[1] = 'l';
  netif->output = slipif_output;
  netif->mtu = MAX_SIZE;
  netif->flags = NETIF_FLAG_POINTTOPOINT;

  /* Try to open the serial port (netif->num contains the port number). */
  netif->state = sio_open(netif->num);
  if (!netif->state) {
    /* Opening the serial port failed. */
    return ERR_IF;
  }

  /* initialize the snmp variables and counters inside the struct netif
   * ifSpeed: no assumption can be made without knowing more about the
   * serial line!
   */
  NETIF_INIT_SNMP(netif, snmp_ifType_slip, 0);

  /* Create a thread to poll the serial line. */
  sys_thread_new(SLIPIF_THREAD_NAME, slipif_loop, netif, SLIPIF_THREAD_STACKSIZE, SLIPIF_THREAD_PRIO);
  return ERR_OK;
}
