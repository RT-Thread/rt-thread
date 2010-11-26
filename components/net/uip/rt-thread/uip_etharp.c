#include "uip_pbuf.h"
#include "uip-conf.h"
#include "rtdef.h"
#include "uip.h"
#include "uip_arp.h"
#include "uip_netif.h"

extern u16_t uip_len, uip_slen;
void 
etharp_ip_input(struct netif *netif, struct pbuf *p)
{
    u8_t *ptr;
    int i;
    ptr = p->payload;
    uip_len = p->len;
    for (i=0;i<p->len;i++) uip_buf[i] = ptr[i];
    uip_arp_ipin();
    uip_input();
    return;
}
void 
etharp_arp_input(struct netif *netif, struct eth_addr *ethaddr, struct pbuf *p)
{    
    u8_t *ptr,*pdata;
    //struct pbuf *q;
    int i;
    ptr = p->payload;
    uip_len = p->len;
    for (i=0;i<p->len;i++) uip_buf[i] = ptr[i];
    uip_arp_arpin();  //update arp table  uip_arp_arpin
    if (uip_len) 
    {
       if (( pdata =(u8_t*)rt_malloc(1500*sizeof(u8_t))) ==RT_NULL)
       {
          pbuf_free(p);
          return;
       }
       for (i=0; i < (UIP_LLH_LEN + 40); ++i) 
       {
           pdata[i] =  uip_buf[i];
        }
        for (; i < uip_len; ++i) 
        {
            pdata[i] =  uip_appdata[i - UIP_LLH_LEN - 40 ];
        }
        //q = p;
        p ->payload = pdata;
        p->len = uip_len;
        netif->linkoutput(netif,p);
        rt_free(pdata);
        pbuf_free(p);
      //  pbuf_free(q);
        return ;
        
       // return 0;    //ERR_OK
    }
    pbuf_free(p);
}