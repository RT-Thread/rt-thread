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

#define RX_485_BUF_LEN 512
#define TEST_485_FRAME_LEN 256

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

static rt_sem_t dev485_rx_notice;
//static rt_sem_t dev485_tx_notice;

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

static rt_err_t dev485_rx_ind(rt_device_t dev, rt_size_t size) 
{
	return rt_sem_release(dev485_rx_notice);	
}
/*static rt_err_t dev485_tx_ind(rt_device_t dev, void *buffer) 
{
	return rt_sem_release(dev485_tx_notice);	
}*/


extern int eps32_init(void);
extern void *itcam_malloc(uint32_t size);
static uint32_t rx_485_cnt = 0;
static uint32_t tx_485_cnt = 0;
static uint32_t tx_485_fail = 0;



void test_pingpong_485() {
    uint32_t offset = 0;
    rt_size_t recv_len;
    rt_device_t dev485;
    char *ch = malloc(TEST_485_FRAME_LEN);

    dev485 = rt_device_find("uart8");
    if (RT_EOK != rt_device_open(dev485, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_DMA_RX)) {
        rt_kprintf("oepn 485 serial error!\n");
    } else {
        dev485_rx_notice = rt_sem_create("rx_485", 0, RT_IPC_FLAG_FIFO);
        //dev485_tx_notice = rt_sem_create("tx_485", 0, RT_IPC_FLAG_FIFO);
        rt_device_set_rx_indicate(dev485, dev485_rx_ind);
        //rt_device_set_tx_complete(dev485, dev485_tx_ind);       
    }
    
    while (1)
    {  
        
        if(RT_EOK == rt_sem_take(dev485_rx_notice, RT_WAITING_FOREVER)) {
            do 
            {
                recv_len = rt_device_read(dev485, 0, ch+offset, RX_485_BUF_LEN-offset);                
                if(recv_len > 0) {     
                    rx_485_cnt += recv_len;    
                    offset += recv_len;                    
                    if(TEST_485_FRAME_LEN == offset) {
                        if(offset != rt_device_write(dev485, 0, ch, offset)) {
                            tx_485_fail++;
                        } else {
                            tx_485_cnt += offset;
                        }
                        offset = 0;
                    } else if (offset > TEST_485_FRAME_LEN) {
                        rt_kprintf("The peer sends too fast!\n");
                        offset = 0;
                    }  
                }                
            } while(recv_len > 0); 
        }
    }
    
}


int main(void)
{    
    rt_thread_t tid_test_485;
    rt_size_t recv_len;
    char *ch = malloc(RX_485_BUF_LEN);
    rt_device_t dev485;   
    
    
    (void)lwiperf_start_tcp_server(IP_ADDR_ANY, 5001, lwiperf_report, 0);  
    tid_test_485 = rt_thread_create("test_485",
                     test_pingpong_485,
                     NULL,
                     1024,
                     RT_THREAD_PRIORITY_MAX / 3 - 1,
                     5);
    if(tid_test_485) {
        rt_thread_startup(tid_test_485);
    } else {
        rt_kprintf("creak task test_485 fail!\n");
    }
    while (1)
    {      
        rt_thread_delay(1000);        
    }
}

void show_485_stat(int argc, char *argv[]) {
    rt_kprintf("rx_485_cnt=%u\n",rx_485_cnt);
    rt_kprintf("tx_485_cnt=%u\n",tx_485_cnt);
    rt_kprintf("tx_485_fail=%u\n",tx_485_fail);   
    
}

void reset_485_stat(int argc, char *argv[]) {
    rx_485_cnt = 0;
    tx_485_cnt = 0;
    tx_485_fail = 0;
}

MSH_CMD_EXPORT(show_485_stat,);
MSH_CMD_EXPORT(reset_485_stat,);



