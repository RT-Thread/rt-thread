/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-24     chinesebear  first version
 */

#ifndef SYNOP_GMAC_HOST_H
#define SYNOP_GMAC_HOST_H 1

#include "synopGMAC_plat.h"
#include "synopGMAC_Dev.h"
#include "mii.h"

struct net_device_stats
{
    unsigned long    rx_packets;        /* total packets received    */
    unsigned long    tx_packets;        /* total packets transmitted    */
    unsigned long    rx_bytes;        /* total bytes received     */
    unsigned long    tx_bytes;        /* total bytes transmitted    */
    unsigned long    rx_errors;        /* bad packets received        */
    unsigned long    tx_errors;        /* packet transmit problems    */
    unsigned long    rx_dropped;        /* no space in linux buffers    */
    unsigned long    tx_dropped;        /* no space available in linux    */
    unsigned long    multicast;        /* multicast packets received    */
    unsigned long    collisions;

    /* detailed rx_errors: */
    unsigned long    rx_length_errors;
    unsigned long    rx_over_errors;        /* receiver ring buff overflow    */
    unsigned long    rx_crc_errors;        /* recved pkt with crc error    */
    unsigned long    rx_frame_errors;    /* recv'd frame alignment error */
    unsigned long    rx_fifo_errors;        /* recv'r fifo overrun        */
    unsigned long    rx_missed_errors;    /* receiver missed packet    */

    /* detailed tx_errors */
    unsigned long    tx_aborted_errors;
    unsigned long    tx_carrier_errors;
    unsigned long    tx_fifo_errors;
    unsigned long    tx_heartbeat_errors;
    unsigned long    tx_window_errors;
    
    /* for cslip etc */
    unsigned long    rx_compressed;
    unsigned long    tx_compressed;
};

typedef struct synopGMACNetworkAdapter{
/*Device Dependent Data structur*/
synopGMACdevice * synopGMACdev;

struct net_device_stats synopGMACNetStats;

struct mii_if_info mii;
} synopGMACPciNetworkAdapter;

#endif
