/*
 * Copyright (c) 2001, Adam Dunkels.
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
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by Adam Dunkels.
 * 4. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack.
 *
 * $Id: main.c,v 1.16 2006/06/11 21:55:03 adam Exp $
 *
 */
#include "uip.h"
#include "uip_arp.h"
#include "stm32_eth.h"
#include "rtconfig.h"
#include "rtdef.h"
#include "uip_timer.h"
#include "rtthread.h"





#define BUF ((struct uip_eth_hdr *)&uip_buf[0])
// Define Prototypes
void TransmitPacket(void)
{
    int i;
    u8_t data[1500];
    // Copy the header portion part
    for(i=0; i < (UIP_LLH_LEN + 40); ++i) 
    {
         data[i] =  uip_buf[i];
    }
    // Copy the data portion part
    for(; i < uip_len; ++i) 
    {
        data[i] =  uip_appdata[i - UIP_LLH_LEN - 40 ];
    }
    ETH_HandleTxPkt(data,uip_len);
}
void uip_tcpip_thread(void *parameter)
{
    int i;
    static u8_t cnt;
    while(1)
    {
        rt_thread_delay(CLOCK_SECOND*5);
        for (i = 0; i < UIP_CONNS; i++) 
        {
	    uip_periodic(i);
	/* If the above function invocation resulted in data that
	   should be sent out on the network, the global variable
	   uip_len is set to a value > 0. */
	    if (uip_len > 0)
            {
	        uip_arp_out();
                TransmitPacket();
	    }
        }
#if UIP_UDP
        for (i = 0; i < UIP_UDP_CONNS; i++)
        {
	    uip_udp_periodic(i);
	/* If the above function invocation resulted in data that
	   should be sent out on the network, the global variable
	   uip_len is set to a value > 0. */
	   if (uip_len > 0)
           {
	      uip_arp_out();
              TransmitPacket();
	   }
        }
#endif /* UIP_UDP */  
      /* Call the ARP timer function every 10 seconds. */
	 if (++cnt > 2) uip_arp_timer();
    }
}

rt_thread_t sys_thread_new(char *name, void (* thread)(void *arg), void *arg, int stacksize, int prio)
{
    rt_thread_t t;
    t = rt_thread_create(name, thread, arg, stacksize, prio, 20);
    RT_ASSERT(t != RT_NULL);
    rt_thread_startup(t);
    return t;
}


void uip_sys_init(void)
{

    uip_init();         //uip init
    sys_thread_new("uip",uip_tcpip_thread, RT_NULL, RT_LWIP_TCPTHREAD_STACKSIZE, RT_LWIP_TCPTHREAD_PRIORITY);
    hello_world_init(); //
}

/*---------------------------------------------------------------------------*/
void uip_log(char *m)
{
    rt_kprintf("uIP log message: %s\n", m);
}
