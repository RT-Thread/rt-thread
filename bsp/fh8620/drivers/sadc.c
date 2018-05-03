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

#include "sadc.h"
#ifdef RT_USING_SADC
#include "inc/fh_driverlib.h"
#include "board_info.h"
#include <rtdef.h>

//#define FH_SADC_DEBUG
//#define FH_TEST_SADC


#ifdef FH_SADC_DEBUG
#define PRINT_SADC_DBG(fmt, args...)     \
    do                                  \
    {                                   \
        rt_kprintf("FH_SADC_DEBUG: ");   \
        rt_kprintf(fmt, ## args);       \
    }                                   \
    while(0)
#else
#define PRINT_SADC_DBG(fmt, args...)  do { } while (0)
#endif





#define __raw_writeb(v,a)	( *(volatile unsigned char  *)(a) = (v))
#define __raw_writew(v,a)	( *(volatile unsigned short *)(a) = (v))
#define __raw_writel(v,a)	( *(volatile unsigned int   *)(a) = (v))

#define __raw_readb(a)		( *(volatile unsigned char   *)(a))
#define __raw_readw(a)		( *(volatile unsigned short  *)(a))
#define __raw_readl(a)		( *(volatile unsigned int    *)(a))


#define wrap_readl(wrap, name) \
	__raw_readl(&(((struct wrap_sadc_reg *)wrap->regs)->name))

#define wrap_writel(wrap, name, val) \
	__raw_writel((val), &(((struct wrap_sadc_reg *)wrap->regs)->name))

#define wrap_readw(wrap, name) \
	__raw_readw(&(((struct wrap_sadc_reg *)wrap->regs)->name))

#define wrap_writew(wrap, name, val) \
	__raw_writew((val), &(((struct wrap_sadc_reg *)wrap->regs)->name))

#define wrap_readb(wrap, name) \
	__raw_readb(&(((struct wrap_sadc_reg *)wrap->regs)->name))

#define wrap_writeb(wrap, name, val) \
	__raw_writeb((val), &(((struct wrap_sadc_reg *)wrap->regs)->name))



#define IOCTL_GET_SADC_DATA 	1
#define IOCTL_SADC_POWER_DOWN 	0xff
#define SADC_WRAP_BASE			(0xf1200000)
#define SADC_IRQn         		(23)
#define SADC_MAX_CONTROLLER		(1)
#define SADC_STATUS_COLESD		(0)
#define SADC_STATUS_OPEN		(1)



rt_err_t fh_sadc_isr_read_data(struct wrap_sadc_obj *sadc, rt_uint32_t channel,
		rt_uint16_t *buf) {
	rt_uint32_t xainsel = 1 << channel;
	rt_uint32_t xversel = 0;
	rt_uint32_t xpwdb = 1;
	//cnt
	rt_uint32_t sel2sam_pre_cnt = 2;
	rt_uint32_t sam_cnt = 2;
	rt_uint32_t sam2sel_pos_cnt = 2;
	//time out
	rt_uint32_t eoc_tos = 0xff;
	rt_uint32_t eoc_toe = 0xff;
	rt_uint32_t time_out = 0xffff;
	//set isr en..
	rt_uint32_t sadc_isr = 0x01;
	//start
	rt_uint32_t sadc_cmd = 0x01;
	//get data
	rt_uint32_t temp_data = 0;
	rt_err_t ret;


	//control...
	wrap_writel(sadc, sadc_control, xainsel | (xversel << 8) | (xpwdb << 12));


	wrap_writel(sadc, sadc_cnt,
			sel2sam_pre_cnt | (sam_cnt << 8) | (sam2sel_pos_cnt << 16));

	wrap_writel(sadc, sadc_timeout,
			eoc_tos | (eoc_toe << 8) | (time_out << 16));

	wrap_writel(sadc, sadc_ier, sadc_isr);

	wrap_writel(sadc, sadc_cmd, sadc_cmd);


   // ret = rt_completion_wait(&sadc->completion, RT_TICK_PER_SECOND / 2);

	ret = rt_sem_take(&sadc->completion, 5000);
	if(ret != RT_EOK)
		return ret;

	switch (channel) {
	case 0:
	case 1:
		//read channel 0 1
		temp_data = wrap_readl(sadc, sadc_dout0);
		break;

	case 2:
	case 3:
		//read channel 2 3
		temp_data = wrap_readl(sadc, sadc_dout1);
		break;

	case 4:
	case 5:
		//read channel 4 5
		temp_data = wrap_readl(sadc, sadc_dout2);
		break;

	case 6:
	case 7:
		//read channel 6 7
		temp_data = wrap_readl(sadc, sadc_dout3);
		break;
	default:
		break;
	}
	if (channel % 2) {
		//read low 16bit
		*buf = (rt_uint16_t) (temp_data & 0xffff);
	} else {
		//read high 16bit
		*buf = (rt_uint16_t) (temp_data >> 16);
	}
	return RT_EOK;

}






static rt_err_t fh_sadc_init(rt_device_t dev)
{

   // struct fh_pwm_obj *pwm_obj = (struct fh_pwm_obj *)pwm_drv.priv;
    PRINT_SADC_DBG("%s\n",__func__);
    struct wrap_sadc_obj *sadc_pri =(struct wrap_sadc_obj *)dev->user_data;
    return RT_EOK;
}



static rt_err_t fh_sadc_open(rt_device_t dev, rt_uint16_t oflag)
{
   // struct fh_pwm_obj *pwm_obj = (struct fh_pwm_obj *)pwm_drv.priv;
    PRINT_SADC_DBG("%s\n",__func__);
    struct wrap_sadc_obj *sadc_pri =(struct wrap_sadc_obj *)dev->user_data;
    return RT_EOK;
}

static rt_err_t fh_sadc_close(rt_device_t dev)
{
    PRINT_SADC_DBG("%s\n",__func__);
    struct wrap_sadc_obj *sadc_pri =(struct wrap_sadc_obj *)dev->user_data;
    return RT_EOK;
}

static rt_err_t fh_sadc_ioctl(rt_device_t dev, int cmd, void *arg)
{

	rt_uint32_t control_reg;
	struct wrap_sadc_obj *sadc_pri =(struct wrap_sadc_obj *)dev->user_data;
	rt_uint32_t ad_data;
	rt_uint16_t ad_raw_data;

	SADC_INFO *sadc_info = (SADC_INFO *)arg;
	rt_err_t ret;
	switch(cmd){
	case SADC_CMD_READ_RAW_DATA:
		ret = fh_sadc_isr_read_data(sadc_pri, sadc_info->channel, &ad_raw_data);
		if(ret != RT_EOK)
			return ret;
		sadc_info->sadc_data = ad_raw_data;

		break;
	case SADC_CMD_READ_VOLT:
		ret = fh_sadc_isr_read_data(sadc_pri, sadc_info->channel, &ad_raw_data);
		if(ret != RT_EOK)
			return ret;

		ad_data = ad_raw_data * SADC_REF;
		ad_data /= SADC_MAX_AD_VALUE;
		sadc_info->sadc_data = ad_data;

		break;
	case SADC_CMD_DISABLE:
		control_reg = wrap_readl(sadc_pri, sadc_control);
		control_reg &= ~(1 << 12);
		wrap_writel(sadc_pri, sadc_control, control_reg);

		break;
	default :
		rt_kprintf("wrong para...\n");
		return RT_EIO;
	}

    return RT_EOK;
}



static void fh_sadc_interrupt(int irq, void *param)
{

    rt_uint32_t isr_status;
	struct wrap_sadc_obj *sadc = (struct wrap_sadc_obj *) param;

	isr_status = wrap_readl(sadc, sadc_int_status);

	if (isr_status & 0x01) {
		//close isr
		rt_uint32_t sadc_isr = 0x00;

		wrap_writel(sadc, sadc_ier, sadc_isr);
		//clear status..

		wrap_writel(sadc, sadc_int_status, isr_status);

		rt_sem_release(&sadc->completion);
	   // rt_completion_done(&sadc->completion);
	} else {
		//add error handle process
		rt_kprintf("sadc maybe error!\n");
	}


}


int fh_sadc_probe(void *priv_data)
{
    int ret;

    rt_device_t sadc_dev;
    //check if the hw is init already...
    //caution this is a read only data...if the driver want to use.malloc and copy it..
    struct wrap_sadc_obj *sadc_obj = (struct wrap_sadc_obj *)priv_data;
    if(sadc_obj->init_flag == SADC_INIT_ALREADY)
     	return RT_EFULL;


    //malloc a rt device..
    sadc_dev = RT_KERNEL_MALLOC(sizeof(struct rt_device));
    if(!sadc_dev){
    	return RT_ENOMEM;
    }
    rt_memset(sadc_dev, 0, sizeof(struct rt_device));
    PRINT_SADC_DBG("id:%d,\treg:%x,\tirq:%d\n",sadc_obj->id,(rt_uint32_t)sadc_obj->regs,sadc_obj->irq_no);

    //bind rtdev to obj data...
    //caution ...this is used to free mem when exit....
    //free step:1:get sadc obj...2:free sadc_obj->rt_dev->user_data..3:free sadc_obj->rt_dev 4:sadc_obj->rt_dev = NULL
    sadc_obj->rt_dev = sadc_dev;



    //malloc a private data sadc use only...copy data from platform...
    struct wrap_sadc_obj *sadc_pri = RT_KERNEL_MALLOC(sizeof(struct wrap_sadc_obj));
    if(!sadc_pri){

    	RT_KERNEL_FREE(sadc_dev);
    	return RT_ENOMEM;
    }

    //copy platform data to pri data..
    rt_memcpy(sadc_pri,sadc_obj,sizeof(struct wrap_sadc_obj));

    PRINT_SADC_DBG("pri....id:%d,\treg:%x,\tirq:%d\n",sadc_pri->id,(rt_uint32_t)sadc_pri->regs,sadc_pri->irq_no);



    //init sem
    //rt_completion_init(&sadc_obj->completion);
    rt_sem_init(&sadc_pri->completion, "sadc_sem", 0, RT_IPC_FLAG_FIFO);

    //init lock
    rt_mutex_init(&sadc_pri->lock,"sadc_lock", RT_IPC_FLAG_FIFO);


    //bind pri data to rt_sadc_dev...
    sadc_dev->user_data = (void *)sadc_pri;
    sadc_dev->open =fh_sadc_open;
    sadc_dev->close = fh_sadc_close;
    sadc_dev->control = fh_sadc_ioctl;
    sadc_dev->init = fh_sadc_init;

    if(sadc_pri->id ==0){
        rt_hw_interrupt_install(sadc_pri->irq_no, fh_sadc_interrupt,
                                (void *)sadc_pri, "sadc_isr_0");
    }

    rt_hw_interrupt_umask(sadc_pri->irq_no);

    rt_device_register(sadc_dev, "sadc", RT_DEVICE_FLAG_RDWR);

    sadc_obj->init_flag = SADC_INIT_ALREADY;

    return RT_EOK;

}


int fh_sadc_exit(void *priv_data)
{

	PRINT_SADC_DBG("%s\n",__func__);
	struct wrap_sadc_obj *sadc_obj = (struct wrap_sadc_obj *)priv_data;

	struct wrap_sadc_obj *sadc_pri = sadc_obj->rt_dev->user_data;
	//release sem;
	rt_sem_detach(&sadc_pri->completion);
	//sadc_pri->completion = RT_NULL;

	//release lock;
	rt_mutex_detach(&sadc_pri->lock);

	RT_KERNEL_FREE(sadc_obj->rt_dev->user_data);


	sadc_obj->rt_dev->user_data = RT_NULL;
	RT_KERNEL_FREE(sadc_obj->rt_dev);
	sadc_obj->rt_dev = RT_NULL;

    return 0;
}

struct fh_board_ops sdac_driver_ops =
{
        .probe = fh_sadc_probe,
        .exit = fh_sadc_exit,
};

void rt_hw_sadc_init(void)
{
    int ret;
    fh_board_driver_register("sadc", &sdac_driver_ops);
}


#ifdef FH_TEST_SADC
int fh_sadc_test(void){

	rt_device_t sadc_dev;
	SADC_INFO info;
	info.channel = 0;
	info.sadc_data = 0;
	sadc_dev = rt_device_find("sadc");
	if(!sadc_dev){
		rt_kprintf("cann't find the sadc dev\n");
	}
	sadc_dev->init(sadc_dev);
	sadc_dev->open(sadc_dev,0);
	while(1)
	{
		sadc_dev->control(sadc_dev,SADC_CMD_READ_VOLT,&info);
		rt_kprintf("channel:%d,volt:%dmv\n",info.channel,info.sadc_data);
	}

	return 0;
}
#endif

#ifdef RT_USING_FINSH
#include <finsh.h>
#ifdef FH_TEST_SADC
FINSH_FUNCTION_EXPORT(fh_sadc_test, fh_sadc_test);
#endif
#endif

#endif
