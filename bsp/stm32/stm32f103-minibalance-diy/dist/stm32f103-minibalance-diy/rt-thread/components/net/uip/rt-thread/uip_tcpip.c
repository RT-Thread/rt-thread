#include "uip_pbuf.h"
#include "uip-conf.h"
#include "rtdef.h"
#include "uip.h"
#include "uip_arp.h"
#include "uip_netif.h"

err_t
tcpip_input(struct pbuf *p, struct netif *inp)
{
     int i;
     u8_t *pdata;
     if (uip_len)
     {
        uip_arp_out(); 
        if (( pdata =(u8_t*)rt_malloc(1500*sizeof(u8_t))) == RT_NULL)
        {
            pbuf_free(p);
            return 1;
        }
        for (i=0; i < (UIP_LLH_LEN + 40); ++i) // 14+40 =54
        {
            pdata[i] =  uip_buf[i]; /* get dest an src ipaddr */
        }
            // Copy the data portion part  
        for(; i < uip_len; ++i)
        {
                pdata[i] =  uip_appdata[i - UIP_LLH_LEN - 40 ];
        }
        p ->payload = pdata;
        p->len = uip_len;
        inp->linkoutput(inp,p);
        rt_free(pdata);
        return 1;
    }
    else
    {
        pbuf_free(p);
        return 0;
    }  
}