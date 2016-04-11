/**
 * NAT - NAT implementation for lwIP supporting TCP/UDP and ICMP.
 * Copyright (c) 2009 Christian Walter, ?Embedded Solutions, Vienna 2009.
 *
 * Copyright (c) 2010 lwIP project ;-)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 */

/*
 * File      : ipv4_nat.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-01-26     Hichard      porting to RT-Thread
 * 2015-01-27     Bernard      code cleanup for lwIP in RT-Thread
 */

#ifndef __LWIP_NAT_H__
#define __LWIP_NAT_H__

#include <rtthread.h>

#ifdef LWIP_USING_NAT

#include "lwip/err.h"
#include "lwip/ip_addr.h"
#include "lwip/opt.h"

/** Timer interval at which to call ip_nat_tmr() */
#define LWIP_NAT_TMR_INTERVAL_SEC        (30)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct netif;
struct pbuf;

typedef struct ip_nat_entry
{
  ip_addr_t    source_net;
  ip_addr_t    source_netmask;
  ip_addr_t    dest_net;
  ip_addr_t    dest_netmask;
  struct netif *out_if;
  struct netif *in_if;
} ip_nat_entry_t;

void  ip_nat_init(void);
void  ip_nat_tmr(void);
u8_t  ip_nat_input(struct pbuf *p);
u8_t  ip_nat_out(struct pbuf *p);

err_t ip_nat_add(const ip_nat_entry_t *new_entry);
void  ip_nat_remove(const ip_nat_entry_t *remove_entry);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IP_NAT */

#endif /* __LWIP_NAT_H__ */
