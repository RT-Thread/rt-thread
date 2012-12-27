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

#define SERIAL_RX_BUFFER_SIZE 80
struct serial_int_rx
{
    rt_uint8_t  rx_buffer[SERIAL_RX_BUFFER_SIZE];
    rt_uint32_t read_index, save_index;
};

rt_err_t rt_hw_serial_init(void);
#endif
