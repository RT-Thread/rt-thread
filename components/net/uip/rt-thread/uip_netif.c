#include "rtdef.h"
#include "uip-conf.h"
#include "uip.h"
#include "uip_netif.h"
#include "uip_arp.h"
#include "rtconfig.h"
#include "uip_pbuf.h"

void netif_set_default(struct netif *netif)
{
  
}
void netif_set_addr(struct netif *netif, struct ip_addr *ipaddr,  struct ip_addr *netmask,
    struct ip_addr *gw)
{
     uip_ipaddr_t hipaddr;
     uip_ipaddr(hipaddr, RT_LWIP_IPADDR0,RT_LWIP_IPADDR1,RT_LWIP_IPADDR2,RT_LWIP_IPADDR3);
     uip_sethostaddr(hipaddr);
     uip_ipaddr(hipaddr, RT_LWIP_GWADDR0,RT_LWIP_GWADDR1,RT_LWIP_GWADDR2,RT_LWIP_GWADDR3);
     uip_setdraddr(hipaddr);
     uip_ipaddr(hipaddr, RT_LWIP_MSKADDR0,RT_LWIP_MSKADDR1,RT_LWIP_MSKADDR2,RT_LWIP_MSKADDR3);
     uip_setnetmask(hipaddr);
     return ;
}

struct netif *
netif_add(struct netif *netif, struct ip_addr *ipaddr,  struct ip_addr *netmask,
  struct ip_addr *gw,
  void *state,
  err_t (* init)(struct netif *netif),
  err_t (* input)(struct pbuf *p, struct netif *netif))
{
	//if (netif_add(netif, IP_ADDR_ANY, IP_ADDR_BROADCAST, IP_ADDR_ANY, dev,
		//eth_init, eth_input) == RT_NULL)
    // netif->uip_hostaddr = ipaddr;
     //netif->uip_draddr = netmask;
    // netif->uip_netmask = gw;
    // netif_set_addr(netif,ipaddr,netmask,gw);  
     
       // call user specified initialization function for netif  
     if (init(netif) != 0) {
        return RT_NULL;
     }
     netif->input = input;
     netif->state = state;
     netif_set_addr(netif,ipaddr,netmask,gw);
     return netif;
               
}
err_t etharp_output(struct netif *netif, struct pbuf *q, struct ip_addr *ipaddr)
{
     return 0;
}
