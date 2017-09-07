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
 
#ifndef FH_DMA_H_
#define FH_DMA_H_


/****************************************************************************
* #include section
*	add #include here if any
***************************************************************************/

#include <rtthread.h>


/*********************************
 *
 * DMA SOC define start
 *
 *********************************/


#define FH81_MAX_CHANNEL					(4)
#define FH81_CHANNEL_MAX_TRANSFER_SIZE		(4095)




enum DMA_HW_HS_MAP{
	ACODEC_RX = 0,
	ACODEC_TX,
	SPI0_RX,
	SPI0_TX,
	SPI1_RX,
	SPI1_TX,
	UART0_RX,
	UART0_TX,
	UART1_RX,
	UART1_TX,
	DMA_HW_HS_END,
};

/*********************************
 *
 * DMA SOC define end
 *
 *********************************/

//user use the dma could use callback function,when the dma make the work done...
typedef void (*dma_complete_callback)(void *complete_para);

typedef void (*user_prepare)(void *prepare_para);



/****************************		i'm cut-off line		************************************/






//controller private para...
struct fh81_dma;


struct dw_lli {
	/* values that are not changed by hardware */
	rt_uint32_t	sar;
	rt_uint32_t	dar;
	rt_uint32_t	llp;		/* chain to next lli */
	rt_uint32_t		ctllo;
	/* values that may get written back: */
	rt_uint32_t		ctlhi;
	/* sstat and dstat can snapshot peripheral register state.
	 * silicon config may discard either or both...
	 */
	rt_uint32_t		sstat;
	rt_uint32_t		dstat;
	rt_uint32_t reserve;

};

//transfer use below
struct dma_transfer{
	//this is private for the dma drive....app don't touch it,the driver will manger it
	//link interface for more transfer to the controller...
	rt_list_t transfer_list;
	struct fh81_dma *dma_controller;
	//this the mem add....the dma controller will load the setting to move data ....
	//user don't touch it
	struct dw_lli *first_lli;
	rt_uint32_t lli_size;
	//new add for allign get desc...
	rt_uint32_t actual_lli_size;


	//user could set paras below~~~
#define AUTO_FIND_CHANNEL		(0xff)
	//transfer with which dma channel...if the data is 0xff, the driver will auto find a free channel.
	rt_uint32_t		channel_number;
	//which dma you want to use...for fh81....only 0!!!
	rt_uint32_t		dma_number;


	//user should set the para below
#define	DMA_M2M 			(0)		//	MEM <=> MEM
#define	DMA_M2P 			(1)		//	MEM => peripheral A
#define	DMA_P2M 			(2)		//	MEM <= peripheral A
#define	DMA_P2P 			(3)		//	peripheral A <=> peripheral B
	rt_uint32_t			fc_mode;//ip->mem. mem->mem. mem->ip




#define DMA_HW_HANDSHAKING	(0)
#define DMA_SW_HANDSHAKING	(1)
	rt_uint32_t			src_hs;			//src
	//if use hw handshaking ,you need to set the hw handshaking number, this SOC defined
	rt_uint32_t			src_per;		//src hw handshake number
	//rt_uint32_t			irq_mode;//for each transfer,irq maybe not same. suggest for the default(transfer isr)

#define	DW_DMA_SLAVE_WIDTH_8BIT 	(0)
#define	DW_DMA_SLAVE_WIDTH_16BIT 	(1)
#define	DW_DMA_SLAVE_WIDTH_32BIT 	(2)
	rt_uint32_t			src_width;

	//the user should reference the hw handshaking watermark..
#define DW_DMA_SLAVE_MSIZE_1		 (0)
#define DW_DMA_SLAVE_MSIZE_4		 (1)
#define DW_DMA_SLAVE_MSIZE_8		 (2)
#define DW_DMA_SLAVE_MSIZE_16		 (3)
#define DW_DMA_SLAVE_MSIZE_32		 (4)
#define DW_DMA_SLAVE_MSIZE_64		 (5)
#define DW_DMA_SLAVE_MSIZE_128		 (6)
#define DW_DMA_SLAVE_MSIZE_256		 (7)
	rt_uint32_t			src_msize;
	rt_uint32_t			src_add;
#define DW_DMA_SLAVE_INC		(0)
#define DW_DMA_SLAVE_DEC		(1)
#define DW_DMA_SLAVE_FIX		(2)
	rt_uint32_t			src_inc_mode;	//increase mode: increase or not change


//#define DMA_DST_HW_HANDSHAKING	(0)
//#define DMA_DST_SW_HANDSHAKING	(1)
	rt_uint32_t			dst_hs;			//src
	//if use hw handshaking ,you need to set the hw handshaking number, this SOC defined
	rt_uint32_t			dst_per;		//dst hw handshake number
//#define	DW_DMA_SLAVE_WIDTH_8BIT 	(0)
//#define	DW_DMA_SLAVE_WIDTH_16BIT 	(1)
//#define	DW_DMA_SLAVE_WIDTH_32BIT 	(2)
	rt_uint32_t			dst_width;
//#define DW_DMA_SLAVE_MSIZE_1		 (0)
//#define DW_DMA_SLAVE_MSIZE_4		 (1)
//#define DW_DMA_SLAVE_MSIZE_8		 (2)
//#define DW_DMA_SLAVE_MSIZE_16		 (3)
//#define DW_DMA_SLAVE_MSIZE_32		 (4)
//#define DW_DMA_SLAVE_MSIZE_64		 (5)
//#define DW_DMA_SLAVE_MSIZE_128		 (6)
//#define DW_DMA_SLAVE_MSIZE_256		 (7)
	rt_uint32_t			dst_msize;
	rt_uint32_t			dst_add;
//#define DW_DMA_SLAVE_INC		(0)
//#define DW_DMA_SLAVE_DEC		(1)
//#define DW_DMA_SLAVE_FIX		(2)
	rt_uint32_t			dst_inc_mode;	//increase mode: increase or not change


	//total sizes, unit: src_width/DW_DMA_SLAVE_WIDTH_8BIT...
	//exg: src_width = DW_DMA_SLAVE_WIDTH_32BIT. trans_len = 2...means that: the dma will transfer 2*4 bytes..
	//exg: src_width = DW_DMA_SLAVE_WIDTH_8BIT. trans_len = 6...means that: the dma will transfer 1*6 bytes..
	rt_uint32_t			trans_len;



	//this is used when dma finish transfer job
	dma_complete_callback complete_callback;
	void				*complete_para; //for the driver data use the dma driver.


	//this is used when dma before work..the user maybe need to set his own private para..
	user_prepare	prepare_callback;
	void				*prepare_para;


	//add cyclic para...
	//period len..
	rt_uint32_t period_len;


};








/****************************************************************************
* #define section
*	add constant #define here if any
***************************************************************************/


/****************************************************************************
* ADT section
*	add Abstract Data Type definition here
***************************************************************************/



/****************************************************************************
*  extern variable declaration section
***************************************************************************/

/****************************************************************************
*  section
*	add function prototype here if any
***************************************************************************/
rt_err_t fh81_dma_register(struct fh81_dma * fh81_dma_p,
                             char * dma_name);
void rt_fh_dma_init(void);
/********************************End Of File********************************/




#endif /* FH81_DMA_H_ */

