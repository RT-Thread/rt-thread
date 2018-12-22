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
 
#include <rtdevice.h>
#include <drivers/spi.h>
#include "fh_arch.h"
#include "board_info.h"
#include "ssi.h"
#include "gpio.h"
#include "inc/fh_driverlib.h"
#include "dma.h"
#include "dma_mem.h"
#include "mmu.h"
//#define FH_SPI_DEBUG

#ifdef FH_SPI_DEBUG
#define PRINT_SPI_DBG(fmt, args...)     \
    do                                  \
    {                                   \
        rt_kprintf("FH_SPI_DEBUG: ");   \
        rt_kprintf(fmt, ## args);       \
    }                                   \
    while(0)
#else
#define PRINT_SPI_DBG(fmt, args...)  do { } while (0)
#endif


#define RX_DMA_CHANNEL	AUTO_FIND_CHANNEL
#define TX_DMA_CHANNEL	AUTO_FIND_CHANNEL

#define DMA_OR_ISR_THRESHOLD		20
#define MALLOC_DMA_MEM_SIZE			0x1000


//static rt_uint32_t allign_func(rt_uint32_t in_addr,rt_uint32_t allign_size){
//	return (in_addr + allign_size-1) & (~(allign_size - 1));
//}


void * fh_get_spi_dev_pri_data(struct rt_spi_device* device){
	return device->parent.user_data;
}

static rt_err_t fh_spi_configure(struct rt_spi_device* device,
                          struct rt_spi_configuration* configuration)
{

    struct spi_slave_info *spi_slave;
    struct spi_controller *spi_control;
    struct fh_spi_obj *spi_obj;
    struct spi_config *config;
    rt_uint32_t status;
    rt_uint32_t spi_hz;

    spi_slave = ( struct spi_slave_info *)fh_get_spi_dev_pri_data(device);
    spi_control = spi_slave->control;
    spi_obj = &spi_control->obj;
    config = &spi_obj->config;

    PRINT_SPI_DBG("configuration: \n");
    PRINT_SPI_DBG("\tmode: 0x%x\n", configuration->mode);
    PRINT_SPI_DBG("\tdata_width: 0x%x\n", configuration->data_width);
    PRINT_SPI_DBG("\tmax_hz: 0x%x\n", configuration->max_hz);

    do{
	  status = SPI_ReadStatus(spi_obj);
	}
    while(status & SPI_STATUS_BUSY);


	/* data_width */
	if(configuration->data_width <= 8){
	  config->data_size = SPI_DATA_SIZE_8BIT;
	}
	else if(configuration->data_width <= 16){
	  config->data_size = SPI_DATA_SIZE_16BIT;
	}
	else{
	  return -RT_ERROR;
	}

	if(configuration->max_hz > spi_control->max_hz)
		spi_hz = spi_control->max_hz;
	else
		spi_hz = configuration->max_hz;

	//fixme: div
	config->clk_div = spi_control->clk_in/spi_hz;
	//config->clk_div = 8;
	PRINT_SPI_DBG("config hz:%d spi div:%d\n",spi_hz,config->clk_div);
	/* CPOL */
	if(configuration->mode & RT_SPI_CPOL){
	  config->clk_polarity = SPI_POLARITY_HIGH;
	}
	else{
	  config->clk_polarity = SPI_POLARITY_LOW;
	}

	/* CPHA */
	if(configuration->mode & RT_SPI_CPHA){
	  config->clk_phase = SPI_PHASE_TX_FIRST;
	}
	else{
	  config->clk_phase = SPI_PHASE_RX_FIRST;
	}

	config->frame_format = SPI_FORMAT_MOTOROLA;
	config->transfer_mode = SPI_MODE_TX_RX;

	SPI_Enable(spi_obj, 0);
	SPI_SetParameter(spi_obj);
	SPI_DisableInterrupt(spi_obj, SPI_IRQ_ALL);
	SPI_Enable(spi_obj, 1);

    return RT_EOK;
}


static void xfer_dma_done(void *arg)
{
	struct spi_controller *spi_control = (struct spi_controller *)arg;
	spi_control->dma_complete_times++;

    struct fh_spi_obj *spi_obj;
    int ret;
    rt_uint32_t slave_id;
    spi_obj = &spi_control->obj;


	//rt_kprintf("spi dma isr done.....\n");
	if (spi_control->dma_complete_times == 2) {
		spi_control->dma_complete_times = 0;

		//add memcpy to user buff
		if(spi_control->current_message->recv_buf){
			rt_memcpy((void*)spi_control->current_message->recv_buf,(void*)spi_control->dma.rx_dummy_buff,spi_control->current_message->length);
		}

		SPI_Enable(spi_obj,0);
		SPI_DisableDma(spi_obj,SPI_TX_DMA|SPI_RX_DMA);
		SPI_Enable(spi_obj,1);

		rt_completion_done(&spi_control->transfer_completion);
	}

}

void dma_set_tx_data(struct spi_controller *spi_control){

	struct dma_transfer *trans;
	rt_uint32_t hs_no;
	struct rt_spi_message* current_message = spi_control->current_message;
	trans = &spi_control->dma.tx_trans;
	hs_no = spi_control->dma.tx_hs;

	struct fh_spi_obj *spi_obj;
	spi_obj = &spi_control->obj;



	if(current_message->length > MALLOC_DMA_MEM_SIZE){
		rt_kprintf("[spi_dma]message len too large..\n");
		rt_kprintf("[spi_dma] message len is %d,max len is %d\n",current_message->length,MALLOC_DMA_MEM_SIZE);
		RT_ASSERT(current_message->length <= MALLOC_DMA_MEM_SIZE);
	}


	rt_memset((void*)spi_control->dma.tx_dummy_buff,0xff,current_message->length);
	//copy tx data....
	if(current_message->send_buf){
		rt_memcpy(spi_control->dma.tx_dummy_buff,current_message->send_buf,current_message->length);
	}


	trans->dma_number = 0;
	trans->dst_add = (rt_uint32_t)(spi_obj->base + OFFSET_SPI_DR);

	trans->dst_hs = DMA_HW_HANDSHAKING;
	trans->dst_inc_mode = DW_DMA_SLAVE_FIX;
	trans->dst_msize = DW_DMA_SLAVE_MSIZE_1;
	trans->dst_per = hs_no;
	trans->dst_width = DW_DMA_SLAVE_WIDTH_8BIT;
	trans->fc_mode = DMA_M2P;

	trans->src_add = (rt_uint32_t)spi_control->dma.tx_dummy_buff;

	trans->src_inc_mode = DW_DMA_SLAVE_INC;
	trans->src_msize = DW_DMA_SLAVE_MSIZE_1;

	trans->src_width = DW_DMA_SLAVE_WIDTH_8BIT;
	trans->trans_len = current_message->length;


	trans->complete_callback = (void *)xfer_dma_done;
	trans->complete_para = (void *)spi_control;




}

void dma_set_rx_data(struct spi_controller *spi_control){

	struct dma_transfer *trans;
	rt_uint32_t hs_no;
	struct rt_spi_message* current_message = spi_control->current_message;
	trans = &spi_control->dma.rx_trans;
	hs_no = spi_control->dma.rx_hs;

	struct fh_spi_obj *spi_obj;
	spi_obj = &spi_control->obj;

	if(current_message->length > MALLOC_DMA_MEM_SIZE){
		rt_kprintf("[spi_dma]message len too large..len is %d\n",current_message->length);
		RT_ASSERT(current_message->length <= MALLOC_DMA_MEM_SIZE);
	}


	//rt_memset((void *)spi_control->dma.rx_dummy_buff,0,MALLOC_DMA_MEM_SIZE);

	trans->dma_number = 0;
	trans->fc_mode = DMA_P2M;

	trans->dst_add = (rt_uint32_t)spi_control->dma.rx_dummy_buff;
	trans->dst_inc_mode = DW_DMA_SLAVE_INC;
	trans->dst_msize = DW_DMA_SLAVE_MSIZE_1;
	trans->dst_width = DW_DMA_SLAVE_WIDTH_8BIT;



	trans->src_add = (rt_uint32_t)(spi_obj->base + OFFSET_SPI_DR);
	trans->src_inc_mode = DW_DMA_SLAVE_FIX;
	trans->src_msize = DW_DMA_SLAVE_MSIZE_1;
	trans->src_width = DW_DMA_SLAVE_WIDTH_8BIT;
	trans->src_hs = DMA_HW_HANDSHAKING;
	trans->src_per = hs_no;
	trans->trans_len = current_message->length;



	trans->complete_callback = (void *)xfer_dma_done;
	trans->complete_para = (void *)spi_control;


}


rt_uint32_t xfer_data_dma(struct spi_controller *spi_control){
	int ret;

	struct fh_spi_obj *spi_obj;
	spi_obj = &spi_control->obj;

	struct rt_dma_device *dma_dev = spi_control->dma.dma_dev;


	//tx data prepare
	dma_set_tx_data(spi_control);
	//rx data prepare
	dma_set_rx_data(spi_control);
	//dma go...


	SPI_Enable(spi_obj,0);

	//SPI_WriteTxDmaLevel(spi_obj,SPI_FIFO_DEPTH / 4);
	SPI_WriteTxDmaLevel(spi_obj,1);
	//SPI_WriteTxDmaLevel(spi_obj,0);
	SPI_WriteRxDmaLevel(spi_obj,0);
	SPI_EnableDma(spi_obj,SPI_TX_DMA|SPI_RX_DMA);
	SPI_Enable(spi_obj,1);

	dma_dev->ops->control(dma_dev,RT_DEVICE_CTRL_DMA_SINGLE_TRANSFER,(void *)&spi_control->dma.rx_trans);
	dma_dev->ops->control(dma_dev,RT_DEVICE_CTRL_DMA_SINGLE_TRANSFER,(void *)&spi_control->dma.tx_trans);

	ret = rt_completion_wait(&spi_control->transfer_completion, RT_TICK_PER_SECOND*50);
	//release channel..

	//dma_dev->ops->control(dma_dev,RT_DEVICE_CTRL_DMA_RELEASE_CHANNEL,(void *)&spi_control->dma.tx_trans);
	//dma_dev->ops->control(dma_dev,RT_DEVICE_CTRL_DMA_RELEASE_CHANNEL,(void *)&spi_control->dma.rx_trans);

	if(ret)
	{
		rt_kprintf("ERROR: %s, transfer timeout\n", __func__);
		return -RT_ETIMEOUT;
	}

	return RT_EOK;
}

rt_uint32_t xfer_data_isr(struct spi_controller *spi_control){

	int ret;
	struct fh_spi_obj *spi_obj;
	spi_obj = &spi_control->obj;
    SPI_SetTxLevel(spi_obj, SPI_FIFO_DEPTH / 2);
    SPI_EnableInterrupt(spi_obj, SPI_IRQ_TXEIM);
	ret = rt_completion_wait(&spi_control->transfer_completion, RT_TICK_PER_SECOND*50);
	if(ret)
	{
		rt_kprintf("ERROR: %s, transfer timeout\n", __func__);
		return -RT_ETIMEOUT;
	}

	return RT_EOK;
}


void fix_spi_xfer_mode(struct spi_controller *spi_control){
	 //switch dma or isr....first check dma ...is error .use isr xfer...
	struct rt_dma_device * rt_dma_dev;
	struct dma_transfer *tx_trans;
	struct dma_transfer *rx_trans;
	int ret;
	//retry to check if the dma status...
	if(spi_control->dma.dma_flag == DMA_BIND_OK){
		//if transfer data too short...use isr..
		if(spi_control->current_message->length < DMA_OR_ISR_THRESHOLD){
			spi_control->xfer_mode = XFER_USE_ISR;
			return;
		}
#if(0)
		rt_dma_dev = spi_control->dma.dma_dev;
		//first request channel

		tx_trans = &spi_control->dma.tx_trans;
		rx_trans = &spi_control->dma.rx_trans;
		tx_trans->channel_number = TX_DMA_CHANNEL;
		rx_trans->channel_number = RX_DMA_CHANNEL;


		ret = rt_dma_dev->ops->control(rt_dma_dev,RT_DEVICE_CTRL_DMA_REQUEST_CHANNEL,(void *)tx_trans);
		if(ret != RT_EOK){
			spi_control->xfer_mode = XFER_USE_ISR;
			return;
		}

		ret = rt_dma_dev->ops->control(rt_dma_dev,RT_DEVICE_CTRL_DMA_REQUEST_CHANNEL,(void *)rx_trans);
		if(ret != RT_EOK){
			//release tx channel...
			rt_dma_dev->ops->control(rt_dma_dev,RT_DEVICE_CTRL_DMA_RELEASE_CHANNEL,(void *)&tx_trans);
			spi_control->xfer_mode = XFER_USE_ISR;
			return;
		}
#endif
		spi_control->xfer_mode = XFER_USE_DMA;
		//if error use isr mode
	}
	else
		spi_control->xfer_mode = XFER_USE_ISR;




}

static rt_uint32_t fh_spi_xfer(struct rt_spi_device* device, struct rt_spi_message* message)
{

    struct spi_slave_info *spi_slave;
    struct spi_controller *spi_control;
    struct fh_spi_obj *spi_obj;
    int ret;
    rt_uint32_t slave_id;
    spi_slave = ( struct spi_slave_info *)fh_get_spi_dev_pri_data(device);
    spi_control = spi_slave->control;
    spi_obj = &spi_control->obj;
    spi_control->transfered_len = 0;
    spi_control->received_len = 0;

	rt_sem_take(&spi_control->xfer_lock, RT_WAITING_FOREVER);

    rt_completion_init(&spi_control->transfer_completion);

    spi_control->current_message = message;
    /* take CS */
    if(message->cs_take)
    {
    	if(spi_slave->plat_slave.actice_level == ACTIVE_LOW)
    		gpio_direction_output(spi_slave->plat_slave.cs_pin, 0);
    	else
    		gpio_direction_output(spi_slave->plat_slave.cs_pin, 1);

    	//here will always use the slave_0 because that the cs is gpio...
    	SPI_EnableSlaveen(spi_obj, 0);
    }

    //fix transfer mode .....
    fix_spi_xfer_mode(spi_control);


	switch(spi_control->xfer_mode){
	case XFER_USE_DMA:
		PRINT_SPI_DBG("use dma xfer.....###############\n");
		ret = xfer_data_dma(spi_control);
		if(ret == RT_EOK){
			break;
		}
		else{
			//use the isr mode to transfer
			spi_control->xfer_mode = XFER_USE_ISR;
			rt_kprintf("%s dma transfer error no:%x\n",__func__,ret);
		}
	case XFER_USE_ISR:
		PRINT_SPI_DBG("use isr xfer.....&&&&&&&&&&&&&\n");
		ret = xfer_data_isr(spi_control);
		if(ret != RT_EOK)
			rt_kprintf("%s isr transfer error no:%x\n",__func__,ret);
		break;

	default:
		rt_kprintf("%s unknow xfer func...\n",__func__);
		while(1)
			;
	}

    /* release CS */
    if(message->cs_release)
    {
    	if(spi_slave->plat_slave.actice_level == ACTIVE_LOW)
    		gpio_direction_output(spi_slave->plat_slave.cs_pin, 1);
    	else
    		gpio_direction_output(spi_slave->plat_slave.cs_pin, 0);
    	SPI_DisableSlaveen(spi_obj, 0);
    }

    rt_sem_release(&spi_control->xfer_lock);
    PRINT_SPI_DBG("%s end\n", __func__);

    return message->length;
}

static struct rt_spi_ops fh_spi_ops =
{

    .configure  = fh_spi_configure,
    .xfer       = fh_spi_xfer,

};


static void fh_spi_interrupt(int irq, void *param)
{


    struct spi_controller *spi_control;
    struct fh_spi_obj *spi_obj;

    spi_control = (struct spi_controller *)param;
    spi_obj = &spi_control->obj;
    rt_uint32_t rx_fifo_capability,tx_fifo_capability;
    rt_uint8_t data = 0;
    rt_uint8_t *p;
    rt_uint32_t status;

//

	if(spi_control->current_message == RT_NULL){
		rt_kprintf("ERROR: %s, current_message is incorrect\n", __func__);
	}

	status =  SPI_InterruptStatus(spi_obj);
	PRINT_SPI_DBG("status: 0x%x\n", status);
	//fixme: ??recv overflow, underflow; tran overflow??
	if(status & SPI_ISR_ERROR){
		rt_kprintf("ERROR: %s, status=%d\n", __func__, status);
		SPI_ClearInterrupt(spi_obj);
		//fixme: handle error
		return;
	}

	rx_fifo_capability = SPI_ReadRxFifoLevel(spi_obj);
	tx_fifo_capability = MIN(
			(SPI_FIFO_DEPTH - SPI_ReadTxFifoLevel(spi_obj)) / 2,
			(spi_control->current_message->length - spi_control->transfered_len));


	PRINT_SPI_DBG("rx_fifo_capability=%d\n", rx_fifo_capability);

	//rx
	spi_control->received_len += rx_fifo_capability;
	while(rx_fifo_capability)
	{
		data = SPI_ReadData(spi_obj);
		if(spi_control->current_message->recv_buf){
			*(rt_uint8_t *)spi_control->current_message->recv_buf++ = data;
		}
		PRINT_SPI_DBG("rx, data: 0x%x\n", data);
		//rt_kprintf("rx, data: 0x%x\n", data);
		rx_fifo_capability--;
	}

	if(spi_control->received_len == spi_control->current_message->length)
	{

		//rt_kprintf("asdasdq4902834908dklfkldjsdhgkljshfgljkhsgfkljhsdfkljghklj");
		SPI_DisableInterrupt(spi_obj, SPI_ISR_FLAG);
		PRINT_SPI_DBG("finished, length=%d, received_len=%d\n", spi_control->current_message->length, spi_control->received_len);
		rt_completion_done(&spi_control->transfer_completion);


		return;
	}

	//tx

	spi_control->transfered_len +=tx_fifo_capability;
	if(spi_control->current_message->send_buf){
		p = (rt_uint8_t *)spi_control->current_message->send_buf;
		while(tx_fifo_capability){
			PRINT_SPI_DBG("tx, data: 0x%x\n", *p);
			//rt_kprintf("tx, data: 0x%x\n", *p);
			SPI_WriteData(spi_obj, *p++);
			tx_fifo_capability--;
		}
		spi_control->current_message->send_buf = p;
	}
	else{
		while(tx_fifo_capability){

			SPI_WriteData(spi_obj, 0xff);
			tx_fifo_capability--;
		}
	}



}


int fh_spi_probe(void *priv_data)
{
    char spi_dev_name[20] = {0};
    char spi_bus_name[20] = {0};
    char spi_isr_name[20] = {0};
    char spi_lock_name[20] = {0};

    struct spi_slave_info *spi_slave;
    struct spi_slave_info *next_slave;

    struct spi_slave_info **control_slave;

    struct spi_controller *spi_control;
    struct spi_control_platform_data *plat_data;
    int i,ret;

	struct rt_dma_device * rt_dma_dev;
	struct dma_transfer *tx_trans;
	struct dma_transfer *rx_trans;

    //check data...
    plat_data = (struct spi_control_platform_data *)priv_data;

    if(!plat_data){
		rt_kprintf("ERROR:platform data null...\n");
		return -RT_ENOMEM;
    }
    if(plat_data->slave_no > FH_SPI_SLAVE_MAX_NO){
    	rt_kprintf("ERROR:spi controller not support %d slave..\n",plat_data->slave_no);
    	return -RT_ENOMEM;
    }


    //malloc data
    spi_control = (struct spi_controller*)rt_malloc(sizeof(struct spi_controller));
    if(!spi_control){
    	rt_kprintf("ERROR:no mem for malloc the spi controller..\n");
    	goto error_malloc_bus;
    }

    rt_memset(spi_control, 0, sizeof(struct spi_controller));
    //parse platform control data
    spi_control->base = plat_data->base;
    spi_control->id = plat_data->id;
    spi_control->irq = plat_data->irq;
    spi_control->max_hz = plat_data->max_hz;
    spi_control->slave_no = plat_data->slave_no;
    spi_control->obj.base = plat_data->base;
    spi_control->clk_in = plat_data->clk_in;
    spi_control->plat_data = plat_data;

    rt_sprintf(spi_lock_name, "%s%d", "spi_lock", spi_control->id);
    rt_sem_init(&spi_control->xfer_lock, spi_lock_name, 1, RT_IPC_FLAG_FIFO);

    rt_sprintf(spi_bus_name, "%s%d", "spi_bus", spi_control->id);

    ret = rt_spi_bus_register(&spi_control->spi_bus, spi_bus_name, &fh_spi_ops);

    PRINT_SPI_DBG("bus name is :%s\n",spi_bus_name);

    //isr...
    rt_sprintf(spi_isr_name, "%s%d", "ssi_isr", spi_control->id);
    rt_hw_interrupt_install(spi_control->irq, fh_spi_interrupt,
                                   (void *)spi_control, spi_isr_name);

    rt_hw_interrupt_umask(spi_control->irq);
    PRINT_SPI_DBG("isr name is :%s\n",spi_isr_name);

    //check dma ....
    if(plat_data->transfer_mode == USE_DMA_TRANSFER){

        spi_control->dma.dma_dev = (struct rt_dma_device *)rt_device_find(plat_data->dma_name);
    	if(spi_control->dma.dma_dev == RT_NULL){
    		rt_kprintf("can't find dma dev\n");
    		//goto error_malloc_slave;
    		//spi_control->dma_xfer_flag = USE_ISR_TRANSFER;
//    		spi_control->dma.dma_flag = DMA_BIND_ERROR;
//    		spi_control->xfer_mode = XFER_USE_ISR;
    		goto BIND_DMA_ERROR;
    	}
    	else{

			spi_control->dma.control = spi_control;
			spi_control->dma.rx_hs = plat_data->rx_hs_no;
			spi_control->dma.tx_hs = plat_data->tx_hs_no;
			spi_control->dma.dma_name = plat_data->dma_name;

			spi_control->dma.rx_dummy_buff = fh_dma_mem_malloc(MALLOC_DMA_MEM_SIZE);
			if(!spi_control->dma.rx_dummy_buff){
				rt_kprintf("malloc rx dma buff failed...\n");
				//spi_control->xfer_mode = XFER_USE_ISR;
				goto BIND_DMA_ERROR;
			}



			spi_control->dma.tx_dummy_buff = fh_dma_mem_malloc(MALLOC_DMA_MEM_SIZE);
			if(!spi_control->dma.tx_dummy_buff){
				rt_kprintf("malloc tx dma buff failed...\n");
				fh_dma_mem_free(spi_control->dma.rx_dummy_buff);
				//spi_control->xfer_mode = XFER_USE_ISR;
				goto BIND_DMA_ERROR;
			}

			if(((rt_uint32_t)spi_control->dma.tx_dummy_buff % 4)||((rt_uint32_t)spi_control->dma.rx_dummy_buff % 4)){
				rt_kprintf("dma malloc buff not allign..\n");
				fh_dma_mem_free(spi_control->dma.rx_dummy_buff);
				fh_dma_mem_free(spi_control->dma.tx_dummy_buff);
				goto BIND_DMA_ERROR;
			}

	    	//open dma dev.
	    	spi_control->dma.dma_dev->ops->control(spi_control->dma.dma_dev,RT_DEVICE_CTRL_DMA_OPEN,RT_NULL);

	    	//request channel
	    	rt_dma_dev = spi_control->dma.dma_dev;
			//first request channel
			tx_trans = &spi_control->dma.tx_trans;
			rx_trans = &spi_control->dma.rx_trans;
			tx_trans->channel_number = TX_DMA_CHANNEL;
			rx_trans->channel_number = RX_DMA_CHANNEL;

			ret = rt_dma_dev->ops->control(rt_dma_dev,RT_DEVICE_CTRL_DMA_REQUEST_CHANNEL,(void *)tx_trans);
			if(ret != RT_EOK){
				goto BIND_DMA_ERROR;
			}

			ret = rt_dma_dev->ops->control(rt_dma_dev,RT_DEVICE_CTRL_DMA_REQUEST_CHANNEL,(void *)rx_trans);
			if(ret != RT_EOK){
				//release tx channel...
				rt_dma_dev->ops->control(rt_dma_dev,RT_DEVICE_CTRL_DMA_RELEASE_CHANNEL,(void *)&tx_trans);
				goto BIND_DMA_ERROR;
			}

	    	//spi_control->xfer_mode = XFER_USE_DMA;
	    	spi_control->dma.dma_flag = DMA_BIND_OK;
    	}
    }
    else{

BIND_DMA_ERROR:
			spi_control->dma.dma_flag = DMA_BIND_ERROR;
			//spi_control->xfer_mode = XFER_USE_ISR;
    }




    control_slave = &spi_control->spi_slave;
    for(i=0;i<plat_data->slave_no;i++){
    	spi_slave = (struct spi_slave_info*)rt_malloc(sizeof(struct spi_slave_info));
    	if(!spi_slave){
    		rt_kprintf("ERROR:no mem for malloc the spi_slave%d..\n",i);
    		goto error_malloc_slave;
    	}
    	rt_memset(spi_slave, 0, sizeof(struct spi_slave_info));

    	//parse platform data...
    	spi_slave->id = i;
    	//bind to the spi control....will easy to find all the data...
    	spi_slave->control = spi_control;
    	spi_slave->plat_slave.cs_pin = plat_data->plat_slave[i].cs_pin;
    	spi_slave->plat_slave.actice_level = plat_data->plat_slave[i].actice_level;
    	rt_sprintf(spi_dev_name, "%s%d%s%d", "ssi", spi_control->id,"_",spi_slave->id);

    	*control_slave = spi_slave;
    	control_slave = &spi_slave->next;

    	//register slave dev...
    	ret = rt_spi_bus_attach_device(&spi_slave->spi_device,spi_dev_name,spi_bus_name,spi_slave);
    	if(ret != RT_EOK){
    		rt_kprintf("register dev to bus failed...\n");
    		goto error_malloc_slave;
    	}

    }



    //request gpio...
	spi_slave = spi_control->spi_slave;
	while(spi_slave != RT_NULL)
	{
		next_slave = spi_slave->next;

		ret = gpio_request(spi_slave->plat_slave.cs_pin);
		if(ret!=0){
			rt_kprintf("request gpio_%d failed...\n",spi_slave->plat_slave.cs_pin);
			goto error_malloc_slave;
		}


		PRINT_SPI_DBG("spi_slave info addr:%x,id:%d,cs:%d,active:%d\n",(rt_uint32_t)spi_slave, spi_slave->id,
				spi_slave->plat_slave.cs_pin,
				spi_slave->plat_slave.actice_level);
		spi_slave = next_slave;
	}

	//this will be used in platform exit..
	plat_data->control = spi_control;
    return RT_EOK;

error_malloc_slave:
	//free the slaveinfo already malloc
	spi_slave = spi_control->spi_slave;
	while(spi_slave != RT_NULL)
	{
		next_slave = spi_slave->next;
		gpio_release(spi_slave->plat_slave.cs_pin);
		rt_free(spi_slave);
		spi_slave = next_slave;
	}
	//mask isr
	rt_hw_interrupt_mask(spi_control->irq);
	//release sem ..
	rt_sem_detach(&spi_control->xfer_lock);

	//free the control malloc .
	rt_free(spi_control);

	//fixme:unregister spi_bus...

error_malloc_bus:
	return -RT_ENOMEM;





}

int fh_spi_exit(void *priv_data)
{

    struct spi_controller *spi_control;
    struct spi_control_platform_data *plat_data;
    struct spi_slave_info *spi_slave;
    struct spi_slave_info *next_slave;

    plat_data = (struct spi_control_platform_data *)priv_data;
    spi_control = plat_data->control;
	spi_slave = spi_control->spi_slave;

	while(spi_slave != RT_NULL)
	{
		next_slave = spi_slave->next;
		gpio_release(spi_slave->plat_slave.cs_pin);
		rt_free(spi_slave);
		spi_slave = next_slave;
	}
	//mask isr
	rt_hw_interrupt_mask(spi_control->irq);
	//release sem ..
	rt_sem_detach(&spi_control->xfer_lock);

	//free the control malloc .
	rt_free(spi_control);
    //fixme free all the malloc data ...

    return 0;
}

struct fh_board_ops spi_driver_ops =
{

        .probe = fh_spi_probe,
        .exit = fh_spi_exit,

};

void rt_hw_spi_init(void)
{

    int ret;

  //  rt_kprintf("%s start\n", __func__);
    PRINT_SPI_DBG("%s start\n", __func__);
    fh_board_driver_register("spi", &spi_driver_ops);
    PRINT_SPI_DBG("%s end\n", __func__);
    //fixme: never release?

}
#if(0)
#define TEST_SPI_BUFF_SIZE			0x100
static rt_uint8_t tx_buf[TEST_SPI_BUFF_SIZE] = {0};
static rt_uint8_t rx_buf[TEST_SPI_BUFF_SIZE] = {0};
int ssi_test(void){
	struct rt_spi_device * rt_spi_device;

	int ret;
	rt_spi_device = (struct rt_spi_device *)rt_device_find("ssi1_0");

	if(rt_spi_device == RT_NULL)
	{
		rt_kprintf("%s spi device %s not found!\r\n",__func__ ,"ssi1_0");
		return -RT_ENOSYS;
	}

    /* config spi */
    {
        struct rt_spi_configuration cfg;
        cfg.data_width = 8;
        cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible: Mode 0 and Mode 3 */
        cfg.max_hz = 50 * 1000 * 1000; /* 50M */
        rt_spi_configure(rt_spi_device, &cfg);
    }
    rt_memset(tx_buf,0x55,TEST_SPI_BUFF_SIZE);

    rt_spi_transfer(rt_spi_device,tx_buf,rx_buf,TEST_SPI_BUFF_SIZE);


    ret = rt_memcmp(tx_buf,rx_buf,TEST_SPI_BUFF_SIZE);
    if(ret != 0){
    	rt_kprintf("compare error ..error data %x\n",ret);
    }
    rt_kprintf("test done \n");
    return 0;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(ssi_test, fh_ssi_test);
#endif
#endif
