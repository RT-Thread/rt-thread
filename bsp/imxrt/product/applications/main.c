/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-06     tyustli      first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drv_gpio.h>
#include <fsl_gpio.h>
#include <stdio.h>
#include "lwip/apps/lwiperf.h"

const char *report_type_str[] = {
    "TCP_DONE_SERVER (RX)",        /* LWIPERF_TCP_DONE_SERVER_RX,*/
    "TCP_DONE_SERVER (TX)",        /* LWIPERF_TCP_DONE_SERVER_TX,*/
    "TCP_DONE_CLIENT (TX)",        /* LWIPERF_TCP_DONE_CLIENT_TX,*/
    "TCP_DONE_CLIENT (RX)",        /* LWIPERF_TCP_DONE_CLIENT_RX,*/
    "TCP_ABORTED_LOCAL",           /* LWIPERF_TCP_ABORTED_LOCAL, */
    "TCP_ABORTED_LOCAL_DATAERROR", /* LWIPERF_TCP_ABORTED_LOCAL_DATAERROR, */
    "TCP_ABORTED_LOCAL_TXERROR",   /* LWIPERF_TCP_ABORTED_LOCAL_TXERROR, */
    "TCP_ABORTED_REMOTE",          /* LWIPERF_TCP_ABORTED_REMOTE, */
    "UDP_DONE_SERVER (RX)",        /* LWIPERF_UDP_DONE_SERVER_RX, */
    "UDP_DONE_SERVER (TX)",        /* LWIPERF_UDP_DONE_SERVER_TX, */
    "UDP_DONE_CLIENT (TX)",        /* LWIPERF_UDP_DONE_CLIENT_TX, */
    "UDP_DONE_CLIENT (RX)",        /* LWIPERF_UDP_DONE_CLIENT_RX, */
    "UDP_ABORTED_LOCAL",           /* LWIPERF_UDP_ABORTED_LOCAL, */
    "UDP_ABORTED_LOCAL_DATAERROR", /* LWIPERF_UDP_ABORTED_LOCAL_DATAERROR, */
    "UDP_ABORTED_LOCAL_TXERROR",   /* LWIPERF_UDP_ABORTED_LOCAL_TXERROR, */
    "UDP_ABORTED_REMOTE",          /* LWIPERF_UDP_ABORTED_REMOTE, */
};


static void lwiperf_report(void *arg,
                           enum lwiperf_report_type report_type,
                           const ip_addr_t *local_addr,
                           uint16_t local_port,
                           const ip_addr_t *remote_addr,
                           uint16_t remote_port,
                           uint32_t bytes_transferred,
                           uint32_t ms_duration,
                           uint32_t bandwidth_kbitpsec)
{
    printf("-------------------------------------------------\r\n");
    if (report_type < (sizeof(report_type_str) / sizeof(report_type_str[0])))
    {
        printf(" %s \r\n", report_type_str[report_type]);
        if (local_addr && remote_addr)
        {
            printf(" Local address : %u.%u.%u.%u ", ((u8_t *)local_addr)[0], ((u8_t *)local_addr)[1],
                   ((u8_t *)local_addr)[2], ((u8_t *)local_addr)[3]);
            printf(" Port %d \r\n", local_port);
            printf(" Remote address : %u.%u.%u.%u ", ((u8_t *)remote_addr)[0], ((u8_t *)remote_addr)[1],
                   ((u8_t *)remote_addr)[2], ((u8_t *)remote_addr)[3]);
            printf(" Port %u \r\n", remote_port);
            printf(" Bytes Transferred %u \r\n", bytes_transferred);
            printf(" Duration (ms) %u \r\n", ms_duration);
            printf(" Bandwidth (kbitpsec) %u \r\n", bandwidth_kbitpsec);
        }
    }
    else
    {
        printf(" IPERF Report error\r\n");
    }
    printf("\r\n");
}

extern int eps32_init(void);

int main(void)
{    

    (void)lwiperf_start_tcp_server(IP_ADDR_ANY, 5001, lwiperf_report, 0);   
    eps32_init();
    while (1)
    {
        rt_thread_mdelay(1000);
    }
}

