/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-24     chinesebear  first version
 */


#ifndef SYNOP_GMAC_NETWORK_INTERFACE_H
#define SYNOP_GMAC_NETWORK_INTERFACE_H 1


#include <lwip/sys.h>
#include <netif/ethernetif.h>
#include "synopGMAC_plat.h"
#include "synopGMAC_Host.h"
#include "synopGMAC_Dev.h"

//#include <common.h>
//#include <net.h>
//#include <linux/stddef.h>


#define NET_IF_TIMEOUT (10*HZ)
#define CHECK_TIME (HZ)

s32  synopGMAC_init_network_interface(char* xname,u64 synopGMACMappedAddr);
void  synopGMAC_exit_network_interface(void);

s32 synopGMAC_linux_open(struct eth_device *);
s32 synopGMAC_linux_close(struct eth_device *);
//s32 synopGMAC_linux_xmit_frames(struct ifnet *);
struct net_device_stats * synopGMAC_linux_get_stats(struct synopGMACNetworkAdapter *);
//void synopGMAC_linux_set_multicast_list(struct net_device *);
//s32 synopGMAC_linux_set_mac_address(struct synopGMACNetwokrAdapter*,void *);
//s32 synopGMAC_linux_change_mtu(struct net_device *,s32);
//s32 synopGMAC_linux_do_ioctl(struct ifnet *,struct ifreq *,s32);
//void synopGMAC_linux_tx_timeout(struct net_device *);

s32 synopGMAC_test(synopGMACdevice * gmacdev_0,synopGMACdevice * gmacdev_1);

void dumpreg(u64 );
void dumpphyreg();

/*
 *  gethex(vp,p,n)
 *      convert n hex digits from p to binary, result in vp,
 *      rtn 1 on success
 */
static int gethex(u8 *vp, char *p, int n)
{
        u8 v;
        int digit;

        for (v = 0; n > 0; n--) {
                if (*p == 0)
                        return (0);
                if (*p >= '0' && *p <= '9')
                        digit = *p - '0';
                else if (*p >= 'a' && *p <= 'f')
                        digit = *p - 'a' + 10;
                else if (*p >= 'A' && *p <= 'F')
                        digit = *p - 'A' + 10;
                else
                        return (0);

                v <<= 4;
                v |= digit;
                p++;
        }
        *vp = v;
        return (1);
}

#endif /* End of file */
