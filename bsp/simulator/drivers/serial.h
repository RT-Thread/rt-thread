/*
*********************************************************************************************************
*                                       MC9S12DP256/DG128 Specific code
*                                          BANKED MEMORY MODEL
*
* File : rthw.c
* By   : parai
* email:parai@foxmail.com
*******************************************************************************************************/

#ifndef __RT_HW_SERIAL_H__
#define __RT_HW_SERIAL_H__

#include <rtdevice.h>
#define SERIAL_RX_BUFFER_SIZE 80
struct serial_int_rx
{
    rt_uint8_t  rx_buffer[SERIAL_RX_BUFFER_SIZE];
    rt_uint32_t read_index, save_index;
};

struct serial_device
{
    struct rt_device dev;
    struct serial_int_rx serial_rx;
};

#define SERIAL_DEVICE(dev)  ((struct serial_device *)(dev))

int seial_save_byte(unsigned char ch, struct serial_device * serial);
rt_err_t rt_hw_serial_init(struct serial_device * serial, char * name);
#endif
