/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#ifndef SADC_H_
#define SADC_H_

#include <rtdef.h>
#ifdef RT_USING_SADC


/****************************************************************************
 * #define section
 *	add constant #define here if any
 ***************************************************************************/
//#define FH_SADC_PROC_FILE    "driver/sadc"
#define MAX_CHANNEL_NO		(8)
#define SADC_REF			(3300)
#define SADC_MAX_AD_VALUE	(0x3ff)
#define LOOP_MODE			(0x55)
#define ISR_MODE			(0xAA)


#define SADC_INIT_ALREADY		(0x33)
#define SADC_INIT_NOT_YET		(0)


#define SADC_CMD_READ_RAW_DATA			(0x22)
#define SADC_CMD_READ_VOLT				(0x33)
#define SADC_CMD_DISABLE				(0x44)

/****************************************************************************
 * ADT section
 *	add Abstract Data Type definition here
 ***************************************************************************/

struct wrap_sadc_reg {
	rt_uint32_t sadc_cmd;
	rt_uint32_t sadc_control;
	rt_uint32_t sadc_ier;
	rt_uint32_t sadc_int_status;
	rt_uint32_t sadc_dout0;
	rt_uint32_t sadc_dout1;
	rt_uint32_t sadc_dout2;
	rt_uint32_t sadc_dout3;
	rt_uint32_t sadc_debuge0;
	rt_uint32_t sadc_status;
	rt_uint32_t sadc_cnt;
	rt_uint32_t sadc_timeout;
};

struct wrap_sadc_obj {
	rt_uint32_t id;
	void *regs;
	rt_uint32_t irq_no;
	rt_uint32_t init_flag;
	rt_uint32_t active_channel_no;
	rt_uint32_t active_channel_status;
	rt_uint16_t channel_data[MAX_CHANNEL_NO];
	rt_uint32_t error_rec;
	rt_uint32_t en_isr;
	rt_uint32_t sample_mode;
	struct rt_mutex lock;
	struct rt_semaphore completion;

    //bind to the rtdev..
    rt_device_t rt_dev;

};

typedef struct{
	rt_uint32_t channel;
	rt_uint32_t sadc_data;
}SADC_INFO;


/****************************************************************************
 *  extern variable declaration section
 ***************************************************************************/

/****************************************************************************
 *  section
 *	add function prototype here if any
 ***************************************************************************/
void rt_hw_sadc_init(void);
#endif
#endif /* SADC_H_ */
