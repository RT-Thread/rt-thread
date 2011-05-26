#include <rtthread.h>
#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#include "lwip/debug.h"
#include "lwip/mem.h"
#include "lwip/sys.h"
#include "lwip/stats.h"
#include "lwip/tcpip.h"
#include "lwip/ip_addr.h"
#include "lwip/dhcp.h"

#include "netif/ethernetif.h"
#include "netif/etharp.h"

/*
 * lwip system initial entry
 */
void lwip_sys_init()
{
	struct ip_addr ipaddr, netmask, gw;

#if LWIP_DHCP
	rt_uint32_t mscnt = 0;

	IP4_ADDR(&gw, 0,0,0,0);
	IP4_ADDR(&ipaddr, 0,0,0,0);
	IP4_ADDR(&netmask, 0,0,0,0);
#else
	IP4_ADDR(&ipaddr, RT_LWIP_IPADDR0, RT_LWIP_IPADDR1, RT_LWIP_IPADDR2, RT_LWIP_IPADDR3);
	IP4_ADDR(&gw, RT_LWIP_GWADDR0, RT_LWIP_GWADDR1, RT_LWIP_GWADDR2, RT_LWIP_GWADDR3);
	IP4_ADDR(&netmask, RT_LWIP_MSKADDR0, RT_LWIP_MSKADDR1, RT_LWIP_MSKADDR2, RT_LWIP_MSKADDR3);
#endif

  	tcpip_init(RT_NULL, RT_NULL);

	netif_set_addr(netif_default, &ipaddr, &netmask, &gw);
	netif_set_up(netif_default);

#if LWIP_DHCP
	/* use DHCP client */
	dhcp_start(netif_default);

    while (netif_default->ip_addr.addr == 0)
	{
        rt_thread_delay(DHCP_FINE_TIMER_MSECS * RT_TICK_PER_SECOND / 1000);

        dhcp_fine_tmr();
        mscnt += DHCP_FINE_TIMER_MSECS;
        if (mscnt >= DHCP_COARSE_TIMER_SECS*1000)
        {
            dhcp_coarse_tmr();
            mscnt = 0;
        }
    }
	
	rt_kprintf("Acquired IP address from DHCP server:");
	rt_kprintf("%d.%d.%d.%d\n", netif_default->ip_addr.addr & 0xff,
		(netif_default->ip_addr.addr>>8) & 0xff,
		(netif_default->ip_addr.addr>>16) & 0xff, 
		(netif_default->ip_addr.addr>>24) & 0xff);
#endif

#if defined(RT_USING_FINSH) && (LWIP_STATS_DISPLAY)
    finsh_syscall_append("lwip_info", (syscall_func)stats_display);
#endif
}
