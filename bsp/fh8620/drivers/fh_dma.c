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
 
/*****************************************************************************
 *  Include Section
 *  add all #include here
 *****************************************************************************/
//#include "drivers/fh_dma.h"
#include "fh_dma.h"
#include "mmu.h"
#include "drivers/dma.h"
#include <stdint.h>
#include <rtdevice.h>
#include <rthw.h>
#include "fh_arch.h"
#include "mmu.h"
#include "fh_def.h"
/*****************************************************************************
 * Define section
 * add all #define here
 *****************************************************************************/
//#define DMA_DEBUG
#ifdef DMA_DEBUG

#define FH_DMA_DEBUG(fmt, args...)	    		\
			rt_kprintf(fmt,##args);
#else
#define FH_DMA_DEBUG(fmt, args...)
#endif


#define		DMA_REG_BASE		(0xEE000000)
#define 	DMA_CONTROLLER_NUMBER		(1)



#define WORK_QUEUE_STACK_SIZE		512
#define WORK_QUEUE_PRIORITY			12


#define TEST_PER_NO			(10)

#define DESC_MAX_SIZE			(20)
/*********************************
 *
 * copy from the linux core start
 *
 *********************************/
//this is the ip reg offset....don't change!!!!!!!
#define DW_DMA_MAX_NR_CHANNELS	8

/*
 * Redefine this macro to handle differences between 32- and 64-bit
 * addressing, big vs. little endian, etc.
 */
#define DW_REG(name)		rt_uint32_t name; rt_uint32_t __pad_##name

/* Hardware register definitions. */
struct dw_dma_chan_regs {
	DW_REG(SAR);		/* Source Address Register */
	DW_REG(DAR);		/* Destination Address Register */
	DW_REG(LLP);		/* Linked List Pointer */
	rt_uint32_t	CTL_LO;		/* Control Register Low */
	rt_uint32_t	CTL_HI;		/* Control Register High */
	DW_REG(SSTAT);
	DW_REG(DSTAT);
	DW_REG(SSTATAR);
	DW_REG(DSTATAR);
	rt_uint32_t	CFG_LO;		/* Configuration Register Low */
	rt_uint32_t	CFG_HI;		/* Configuration Register High */
	DW_REG(SGR);
	DW_REG(DSR);
};

struct dw_dma_irq_regs {
	DW_REG(XFER);
	DW_REG(BLOCK);
	DW_REG(SRC_TRAN);
	DW_REG(DST_TRAN);
	DW_REG(ERROR);
};

struct dw_dma_regs {
	/* per-channel registers */
	struct dw_dma_chan_regs	CHAN[DW_DMA_MAX_NR_CHANNELS];

	/* irq handling */
	struct dw_dma_irq_regs	RAW;		/* r */
	struct dw_dma_irq_regs	STATUS;		/* r (raw & mask) */
	struct dw_dma_irq_regs	MASK;		/* rw (set = irq enabled) */
	struct dw_dma_irq_regs	CLEAR;		/* w (ack, affects "raw") */

	DW_REG(STATUS_INT);			/* r */

	/* software handshaking */
	DW_REG(REQ_SRC);
	DW_REG(REQ_DST);
	DW_REG(SGL_REQ_SRC);
	DW_REG(SGL_REQ_DST);
	DW_REG(LAST_SRC);
	DW_REG(LAST_DST);

	/* miscellaneous */
	DW_REG(CFG);
	DW_REG(CH_EN);
	DW_REG(ID);
	DW_REG(TEST);

	/* optional encoded params, 0x3c8..0x3 */
};




/* Bitfields in CTL_LO */
#define DWC_CTLL_INT_EN			(1 << 0)	/* irqs enabled? */
#define DWC_CTLL_DST_WIDTH(n)	((n)<<1)	/* bytes per element */
#define DWC_CTLL_SRC_WIDTH(n)	((n)<<4)

#define DWC_CTLL_DST_INC_MODE(n) ((n)<<7)

#define DWC_CTLL_DST_INC		(0<<7)		/* DAR update/not */
#define DWC_CTLL_DST_DEC		(1<<7)
#define DWC_CTLL_DST_FIX		(2<<7)


#define DWC_CTLL_SRC_INC_MODE(n) ((n)<<9)


#define DWC_CTLL_SRC_INC		(0<<9)		/* SAR update/not */
#define DWC_CTLL_SRC_DEC		(1<<9)
#define DWC_CTLL_SRC_FIX		(2<<9)
#define DWC_CTLL_DST_MSIZE(n)	((n)<<11)	/* burst, #elements */
#define DWC_CTLL_SRC_MSIZE(n)	((n)<<14)
#define DWC_CTLL_S_GATH_EN		(1 << 17)	/* src gather, !FIX */
#define DWC_CTLL_D_SCAT_EN		(1 << 18)	/* dst scatter, !FIX */
#define DWC_CTLL_FC(n)			((n) << 20)
#define DWC_CTLL_FC_M2M			(0 << 20)	/* mem-to-mem */
#define DWC_CTLL_FC_M2P			(1 << 20)	/* mem-to-periph */
#define DWC_CTLL_FC_P2M			(2 << 20)	/* periph-to-mem */
#define DWC_CTLL_FC_P2P			(3 << 20)	/* periph-to-periph */
/* plus 4 transfer types for peripheral-as-flow-controller */
#define DWC_CTLL_DMS(n)			((n)<<23)	/* dst master select */
#define DWC_CTLL_SMS(n)			((n)<<25)	/* src master select */
#define DWC_CTLL_LLP_D_EN		(1 << 27)	/* dest block chain */
#define DWC_CTLL_LLP_S_EN		(1 << 28)	/* src block chain */

/* Bitfields in CTL_HI */
#define DWC_CTLH_DONE			0x00001000
#define DWC_CTLH_BLOCK_TS_MASK	0x00000fff

/* Bitfields in CFG_LO. Platform-configurable bits are in <linux/dw_dmac.h> */
#define DWC_CFGL_CH_PRIOR_MASK	(0x7 << 5)	/* priority mask */
#define DWC_CFGL_CH_PRIOR(x)	((x) << 5)	/* priority */
#define DWC_CFGL_CH_SUSP		(1 << 8)	/* pause xfer */
#define DWC_CFGL_FIFO_EMPTY		(1 << 9)	/* pause xfer */


#define DWC_CFGL_HS_DST			(1 << 10)	/* handshake w/dst */
#define DWC_CFGL_HS_SRC			(1 << 11)	/* handshake w/src */
#define DWC_CFGL_MAX_BURST(x)	((x) << 20)
#define DWC_CFGL_RELOAD_SAR		(1 << 30)
#define DWC_CFGL_RELOAD_DAR		(1 << 31)

/* Bitfields in CFG_HI. Platform-configurable bits are in <linux/dw_dmac.h> */
#define DWC_CFGH_DS_UPD_EN		(1 << 5)
#define DWC_CFGH_SS_UPD_EN		(1 << 6)

/* Bitfields in SGR */
#define DWC_SGR_SGI(x)			((x) << 0)
#define DWC_SGR_SGC(x)			((x) << 20)

/* Bitfields in DSR */
#define DWC_DSR_DSI(x)			((x) << 0)
#define DWC_DSR_DSC(x)			((x) << 20)

/* Bitfields in CFG */
#define DW_CFG_DMA_EN			(1 << 0)

#define DW_REGLEN				0x400


/* Platform-configurable bits in CFG_HI */
#define DWC_CFGH_FCMODE		(1 << 0)
#define DWC_CFGH_FIFO_MODE	(1 << 1)
#define DWC_CFGH_PROTCTL(x)	((x) << 2)
#define DWC_CFGH_SRC_PER(x)	((x) << 7)
#define DWC_CFGH_DST_PER(x)	((x) << 11)

/* Platform-configurable bits in CFG_LO */
#define DWC_CFGL_LOCK_CH_XFER	(0 << 12)	/* scope of LOCK_CH */
#define DWC_CFGL_LOCK_CH_BLOCK	(1 << 12)
#define DWC_CFGL_LOCK_CH_XACT	(2 << 12)
#define DWC_CFGL_LOCK_BUS_XFER	(0 << 14)	/* scope of LOCK_BUS */
#define DWC_CFGL_LOCK_BUS_BLOCK	(1 << 14)
#define DWC_CFGL_LOCK_BUS_XACT	(2 << 14)
#define DWC_CFGL_LOCK_CH	(1 << 15)	/* channel lockout */
#define DWC_CFGL_LOCK_BUS	(1 << 16)	/* busmaster lockout */
#define DWC_CFGL_HS_DST_POL	(1 << 18)	/* dst handshake active low */
#define DWC_CFGL_HS_SRC_POL	(1 << 19)	/* src handshake active low */




#define lift_shift_bit_num(bit_num)			(1<<bit_num)


#define __raw_writeb(v,a)       (*(volatile unsigned char  *)(a) = (v))
#define __raw_writew(v,a)       (*(volatile unsigned short *)(a) = (v))
#define __raw_writel(v,a)       (*(volatile unsigned int   *)(a) = (v))

#define __raw_readb(a)          (*(volatile unsigned char  *)(a))
#define __raw_readw(a)          (*(volatile unsigned short *)(a))
#define __raw_readl(a)          (*(volatile unsigned int   *)(a))

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))




#define dw_readl(dw, name) \
	__raw_readl(&(((struct dw_dma_regs *)dw->regs)->name))
#define dw_writel(dw, name, val) \
	__raw_writel((val), &(((struct dw_dma_regs *)dw->regs)->name))
#define dw_readw(dw, name) \
	__raw_readw(&(((struct dw_dma_regs *)dw->regs)->name))
#define dw_writew(dw, name, val) \
	__raw_writew((val), &(((struct dw_dma_regs *)dw->regs)->name))






#define CHANNEL0		(lift_shift_bit_num(0))
#define CHANNEL1		(lift_shift_bit_num(1))
#define CHANNEL2		(lift_shift_bit_num(2))
#define CHANNEL3		(lift_shift_bit_num(3))

#define channel_set_bit(dw, reg, mask) \
	dw_writel(dw, reg, ((mask) << 8) | (mask))
#define channel_clear_bit(dw, reg, mask) \
	dw_writel(dw, reg, ((mask) << 8) | 0)




/****************************************************************************
 * ADT section
 *  add definition of user defined Data Type that only be used in this file  here
 ***************************************************************************/

struct dw_dma{
	//vadd
	void 				*regs;
	//padd
	rt_uint32_t			paddr;
	rt_uint32_t			irq;
	rt_uint32_t			channel_max_number;

#define CONTROLLER_STATUS_CLOSED		(0)
#define CONTROLLER_STATUS_OPEN			(1)
	rt_uint32_t			controller_status;
#define FH81_DMA_INIT_NOT_YET		(0)
#define FH81_DMA_INIT_ALREADY		(1)
	rt_uint32_t			init;
	rt_uint32_t			id;
	char	 *name;
	rt_uint32_t channel_work_done;
};


struct dma_channel {
#define CHANNEL_STATUS_CLOSED	(0)
#define CHANNEL_STATUS_OPEN		(1)
#define CHANNEL_STATUS_IDLE		(2)
#define CHANNEL_STATUS_BUSY		(3)

	rt_uint32_t channel_status;	//open, busy ,closed
	rt_uint32_t	desc_trans_size;

	//isr will set it complete.
	struct rt_completion transfer_completion;
	//add lock,when set the channel.lock it
	struct rt_semaphore channel_lock;
	//struct rt_mutex                 lock;
	//rt_enter_critical();
	rt_list_t queue;
	//active transfer now!!!
	struct dma_transfer *active_trans;

#define SINGLE_TRANSFER			(0)
#define CYCLIC_TRANSFER			(1)
#define DEFAULT_TRANSFER		SINGLE_TRANSFER
	rt_uint32_t open_flag;
	//



	//new add para...
	rt_uint32_t desc_total_no;
	rt_uint32_t free_index;
	rt_uint32_t used_index;
	rt_uint32_t desc_left_cnt;

	rt_uint32_t allign_malloc;
	struct dw_lli *base_lli;
};


struct fh81_dma{
	//core use ,this must be the first para!!!!
	struct rt_dma_device parent;
	//myown
	struct dw_dma dwc;
	//channel obj
	struct dma_channel dma_channel[FH81_MAX_CHANNEL];

	//struct rt_workqueue* isr_workqueue;
	//struct rt_work *isr_work;

};



#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = rt_list_entry((head)->next, typeof(*pos), member),	\
		n = rt_list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = rt_list_entry(n->member.next, typeof(*n), member))


/******************************************************************************
 * Function prototype section
 * add prototypes for all functions called by this file,execepting those
 * declared in header file
 *****************************************************************************/


/*****************************************************************************
 * Global variables section - Exported
 * add declaration of global variables that will be exported here
 * e.g.
 *  int8_t foo;
 ****************************************************************************/


/*****************************************************************************

 *  static fun;
 *****************************************************************************/
static rt_err_t init (struct rt_dma_device *dma);
static rt_err_t control (struct rt_dma_device *dma, int cmd, void *arg);


static void rt_fh_dma_cyclic_stop(struct dma_transfer *p);
static void rt_fh_dma_cyclic_start(struct dma_transfer *p);
static void rt_fh_dma_cyclic_prep(struct fh81_dma * fh81_dma_p,struct dma_transfer *p);
static void rt_fh_dma_cyclic_free(struct dma_transfer *p);

static struct rt_dma_ops fh81_dma_ops =
{
		init,
		control
};




/*****************************************************************************
 * Global variables section - Local
 * define global variables(will be refered only in this file) here,
 * static keyword should be used to limit scope of local variable to this file
 * e.g.
 *  static uint8_t ufoo;
 *****************************************************************************/
static struct fh81_dma	fh81_dma_controller[DMA_CONTROLLER_NUMBER] = {0};

/* function body */
/*****************************************************************************
 * Description:
 *      add funtion description here
 * Parameters:
 *      description for each argument, new argument starts at new line
 * Return:
 *      what does this function returned?
 *****************************************************************************/

static rt_uint32_t allign_func(rt_uint32_t in_addr,rt_uint32_t allign_size){
	return (in_addr + allign_size-1) & (~(allign_size - 1));
}


struct dw_lli * get_desc(struct fh81_dma  *p_dma,struct dma_transfer *p_transfer,rt_uint32_t lli_size){
	struct dw_lli * ret_lli;
	rt_uint32_t free_index;
	rt_uint32_t allign_left;
	rt_uint32_t totoal_desc;
	rt_uint32_t actual_get_desc;
	rt_uint32_t totoal_free_desc;
	totoal_free_desc = p_dma->dma_channel[p_transfer->channel_number].desc_left_cnt;
	free_index = p_dma->dma_channel[p_transfer->channel_number].free_index;
	totoal_desc = p_dma->dma_channel[p_transfer->channel_number].desc_total_no;
	allign_left = totoal_desc - free_index;

	//check first..
	if(totoal_free_desc < lli_size){
		rt_kprintf("not enough desc to get...\n");
		rt_kprintf("get size is %d,left is %d\n",lli_size,totoal_free_desc);
		return RT_NULL;
	}
	//rt_kprintf("get desc in...\n");

	//rt_kprintf("lli size is %d\n",lli_size);
	if(lli_size > allign_left){
		//if allign desc not enough...just reset null....
		if((totoal_free_desc - allign_left) < lli_size){
			rt_kprintf("not enough desc to get...\n");
			rt_kprintf("app need size is %d, totoal left is %d, allign left is %d\n",lli_size,totoal_free_desc,allign_left);
			rt_kprintf("from head to get desc size is %d, actual get is %d\n",(totoal_free_desc - allign_left),(allign_left +lli_size));
			return RT_NULL;
		}
		else{
			actual_get_desc = allign_left +lli_size;
			free_index = 0;
		}
	}


	//ret_lli = &p_dma->dma_channel[p_transfer->channel_number].base_lli[free_index];

	ret_lli = &p_dma->dma_channel[p_transfer->channel_number].base_lli[free_index];
//	rt_kprintf("get desc base index addr:%08x\n",(rt_uint32_t)&p_dma->dma_channel[p_transfer->channel_number].base_lli[0]);
//	rt_kprintf("get desc free index addr:%08x\n",(rt_uint32_t)ret_lli);
//	rt_kprintf("get desc request size:%08x\n",lli_size);
//	rt_kprintf("get desc total size:%08x\n",p_dma->dma_channel[p_transfer->channel_number].desc_total_no);
//	rt_kprintf("one desc size is:%08x\n",sizeof(	struct dw_lli));

	p_dma->dma_channel[p_transfer->channel_number].free_index += actual_get_desc;

	//rt_kprintf("get desc free index addr:%08x\n",(rt_uint32_t)&p_dma->dma_channel[p_transfer->channel_number].base_lli[p_dma->dma_channel[p_transfer->channel_number].free_index]);

	p_dma->dma_channel[p_transfer->channel_number].free_index %= p_dma->dma_channel[p_transfer->channel_number].desc_total_no;
	p_dma->dma_channel[p_transfer->channel_number].desc_left_cnt -= actual_get_desc;
	p_transfer->lli_size = lli_size;
	p_transfer->actual_lli_size = actual_get_desc;
	return ret_lli;
}


rt_uint32_t put_desc(struct fh81_dma  *p_dma,struct dma_transfer *p_transfer){
	struct dw_lli * ret_lli;
	rt_uint32_t used_index;
	rt_uint32_t lli_size;
	//rt_kprintf("put desc in...\n");
	used_index = p_dma->dma_channel[p_transfer->channel_number].used_index;
	lli_size = p_transfer->actual_lli_size;
	p_dma->dma_channel[p_transfer->channel_number].used_index += lli_size;
	p_dma->dma_channel[p_transfer->channel_number].used_index %= p_dma->dma_channel[p_transfer->channel_number].desc_total_no;
	p_dma->dma_channel[p_transfer->channel_number].desc_left_cnt += lli_size;
	p_transfer->lli_size  = 0;
	p_transfer->actual_lli_size = 0;
	return 0;
}

/*****************************************************************************
 * Description:
 *      add funtion description here
 * Parameters:
 *      description for each argument, new argument starts at new line
 * Return:
 *      what does this function returned?
 *****************************************************************************/

static rt_err_t init (struct rt_dma_device *dma){


	//init the clk table


	struct fh81_dma *my_own = (struct  fh81_dma *)dma->parent.user_data;

	FH_DMA_DEBUG("my_own value:0x%x\n",(rt_uint32_t)my_own);

	//check the user data
	RT_ASSERT(my_own != RT_NULL);

	return RT_EOK;

}





/*****************************************************************************
 * Description:
 *      add funtion description here
 * Parameters:
 *      description for each argument, new argument starts at new line
 * Return:
 *      what does this function returned?
 *****************************************************************************/

static void handle_dma_open(struct fh81_dma  *p_dma){

	rt_uint32_t i;
	struct dw_dma *temp_dwc;
	temp_dwc = &p_dma->dwc;

	dw_writel(temp_dwc, CFG, 1);
	p_dma->dwc.controller_status = CONTROLLER_STATUS_OPEN;

}


/*****************************************************************************
 * Description:
 *      add funtion description here
 * Parameters:
 *      description for each argument, new argument starts at new line
 * Return:
 *      what does this function returned?
 *****************************************************************************/
static void handle_dma_close(struct fh81_dma  *p_dma){


	rt_uint32_t i;
	struct dw_dma *temp_dwc;
	temp_dwc = &p_dma->dwc;

	//take lock
	for(i=0;i<p_dma->dwc.channel_max_number;i++){
		rt_sem_take(&p_dma->dma_channel[i].channel_lock, RT_WAITING_FOREVER);

		channel_clear_bit(temp_dwc, CH_EN, lift_shift_bit_num(i));
		p_dma->dma_channel[i].channel_status = CHANNEL_STATUS_CLOSED;
	}
	dw_writel(temp_dwc, CFG, 0);
	p_dma->dwc.controller_status = CONTROLLER_STATUS_CLOSED;

	//release lock
	for(i=0;i<p_dma->dwc.channel_max_number;i++){
		rt_sem_release(&p_dma->dma_channel[i].channel_lock);
	}

	//destroy the workqueue..
	//rt_workqueue_destroy(p_dma->isr_workqueue);


}


/*****************************************************************************
 * Description:
 *      add funtion description here
 * Parameters:
 *      description for each argument, new argument starts at new line
 * Return:
 *      what does this function returned?
 *****************************************************************************/

#define CHANNEL_REAL_FREE			(0)
#define CHANNEL_NOT_FREE			(1)

static rt_uint32_t check_channel_real_free(struct fh81_dma  *p_dma,rt_uint32_t channel_number){


	struct dw_dma *temp_dwc;
	temp_dwc = &p_dma->dwc;
	rt_uint32_t ret_status;


	RT_ASSERT(channel_number < p_dma->dwc.channel_max_number);

	ret_status = dw_readl(temp_dwc, CH_EN);
	if(ret_status & lift_shift_bit_num(channel_number)){
		//the channel is still busy!!!error here
		//FH_DMA_DEBUG("auto request channel error\n");
		return CHANNEL_NOT_FREE;
	}
	return CHANNEL_REAL_FREE;

}



/*****************************************************************************
 * Description:
 *      add funtion description here
 * Parameters:
 *      description for each argument, new argument starts at new line
 * Return:
 *      what does this function returned?
 *****************************************************************************/

static rt_err_t handle_request_channel(struct fh81_dma  *p_dma,struct dma_transfer *p_transfer){

	rt_uint32_t i;
	struct dw_dma *temp_dwc;
	temp_dwc = &p_dma->dwc;
	rt_err_t ret_status = RT_EOK;

	//handle if auto check channel...
	if(p_transfer->channel_number == AUTO_FIND_CHANNEL){
		//check each channel lock,find a free channel...
		for(i=0;i<p_dma->dwc.channel_max_number;i++){
			ret_status = rt_sem_trytake(&p_dma->dma_channel[i].channel_lock);
			if(ret_status == RT_EOK){
				break;
			}
		}

		if(i < p_dma->dwc.channel_max_number){
			ret_status = check_channel_real_free(p_dma,i);
			if(ret_status!= CHANNEL_REAL_FREE){
				FH_DMA_DEBUG("auto request channel error\n");
				RT_ASSERT(ret_status == CHANNEL_REAL_FREE);
			}
			//caution : channel is already locked here....
			p_transfer->channel_number = i;
			//bind to the controller.
			//p_transfer->dma_controller = p_dma;
			p_dma->dma_channel[i].channel_status = CHANNEL_STATUS_OPEN;
		}
		else
			return -RT_ENOMEM;

	}

	// request channel by user
	else{
		//

		RT_ASSERT(p_transfer->channel_number < p_dma->dwc.channel_max_number);
		ret_status = rt_sem_take(&p_dma->dma_channel[p_transfer->channel_number].channel_lock, RT_TICK_PER_SECOND*50);
		if(ret_status != RT_EOK)
			return -RT_ENOMEM;
		//rt_enter_critical();
		ret_status = check_channel_real_free(p_dma,p_transfer->channel_number);
		if(ret_status!= CHANNEL_REAL_FREE){
			FH_DMA_DEBUG("user request channel error\n");
			RT_ASSERT(ret_status == CHANNEL_REAL_FREE);
		}

		//bind to the controller
		//p_transfer->dma_controller = p_dma;
		p_dma->dma_channel[p_transfer->channel_number].channel_status = CHANNEL_STATUS_OPEN;
		//rt_exit_critical();
	}


	//malloc desc for this one channel...
	//fix me....

	p_dma->dma_channel[p_transfer->channel_number].allign_malloc =	(rt_uint32_t) rt_malloc(
			(p_dma->dma_channel[p_transfer->channel_number].desc_total_no
					* sizeof(struct dw_lli)) + CACHE_LINE_SIZE);


	if(!p_dma->dma_channel[p_transfer->channel_number].allign_malloc){
		//release channel
		rt_kprintf("[dma]: no mem to malloc channel%d desc..\n",p_transfer->channel_number);
		p_dma->dma_channel[p_transfer->channel_number].channel_status = CHANNEL_STATUS_CLOSED;
		rt_sem_release(&p_dma->dma_channel[p_transfer->channel_number].channel_lock);
		return -RT_ENOMEM;
	}


	p_dma->dma_channel[p_transfer->channel_number].base_lli =
			(struct dw_lli *) allign_func(
					p_dma->dma_channel[p_transfer->channel_number].allign_malloc,
					CACHE_LINE_SIZE);

	FH_DMA_DEBUG("dma desc addr is %x\n",(rt_uint32_t)p_dma->dma_channel[p_transfer->channel_number].base_lli);
	//t1 = (UINT32)rt_malloc(GMAC_TX_RING_SIZE * sizeof(Gmac_Tx_DMA_Descriptors) + CACHE_LINE_SIZE);


	if(!p_dma->dma_channel[p_transfer->channel_number].base_lli){
		FH_DMA_DEBUG("request desc failed..\n");
		RT_ASSERT(p_dma->dma_channel[p_transfer->channel_number].base_lli != RT_NULL);
	}

	if((rt_uint32_t)p_dma->dma_channel[p_transfer->channel_number].base_lli % 32){
		rt_kprintf("malloc is not cache allign..");

	}



	//rt_memset((void *)dma_trans_desc->first_lli, 0, lli_size * sizeof(struct dw_lli));
	rt_memset((void *) p_dma->dma_channel[p_transfer->channel_number].base_lli,
			0,
			p_dma->dma_channel[p_transfer->channel_number].desc_total_no
					* sizeof(struct dw_lli));

	p_dma->dma_channel[p_transfer->channel_number].desc_left_cnt = p_dma->dma_channel[p_transfer->channel_number].desc_total_no;
	p_dma->dma_channel[p_transfer->channel_number].free_index = 0;
	p_dma->dma_channel[p_transfer->channel_number].used_index = 0;


	return RT_EOK;

}









/*****************************************************************************
 * Description:
 *      add funtion description here
 * Parameters:
 *      description for each argument, new argument starts at new line
 * Return:
 *      what does this function returned?
 *****************************************************************************/

static rt_uint32_t handle_release_channel(struct fh81_dma  *p_dma,struct dma_transfer *p_transfer){


	rt_uint32_t i;
	struct dw_dma *temp_dwc;
	temp_dwc = &p_dma->dwc;
	rt_uint32_t ret_status;

	//rt_enter_critical();
	ret_status = p_dma->dma_channel[p_transfer->channel_number].channel_status;


	RT_ASSERT(p_transfer->channel_number < p_dma->dwc.channel_max_number);


	if(ret_status == CHANNEL_STATUS_CLOSED){
		FH_DMA_DEBUG("release channel error,reason: release a closed channel!!\n");
		RT_ASSERT(ret_status != CHANNEL_STATUS_CLOSED);
	}

	channel_clear_bit(temp_dwc, CH_EN, lift_shift_bit_num(p_transfer->channel_number));
	rt_sem_release(&p_dma->dma_channel[p_transfer->channel_number].channel_lock);
	//p_transfer->dma_controller = RT_NULL;
	p_dma->dma_channel[p_transfer->channel_number].channel_status = CHANNEL_STATUS_CLOSED;
	p_dma->dma_channel[p_transfer->channel_number].open_flag = DEFAULT_TRANSFER;
	//rt_exit_critical();

	//release this channel malloc mem...
	//fix me.....
	rt_free((void *)p_dma->dma_channel[p_transfer->channel_number].allign_malloc);
	p_dma->dma_channel[p_transfer->channel_number].allign_malloc = RT_NULL;
	p_dma->dma_channel[p_transfer->channel_number].base_lli = RT_NULL;
	p_dma->dma_channel[p_transfer->channel_number].desc_left_cnt = p_dma->dma_channel[p_transfer->channel_number].desc_total_no;
	p_dma->dma_channel[p_transfer->channel_number].free_index = 0;
	p_dma->dma_channel[p_transfer->channel_number].used_index = 0;

	return RT_EOK;


}



static rt_uint32_t cal_lli_size(struct dma_transfer *p_transfer){
	RT_ASSERT(p_transfer != RT_NULL);
	RT_ASSERT(p_transfer->dma_controller != RT_NULL);
	RT_ASSERT(p_transfer->src_width <= DW_DMA_SLAVE_WIDTH_32BIT);
	rt_uint32_t lli_number = 0;
	rt_uint32_t channel_max_trans_per_lli = 0;
	channel_max_trans_per_lli = p_transfer->dma_controller->dma_channel[p_transfer->channel_number].desc_trans_size;


	lli_number = (p_transfer->trans_len % channel_max_trans_per_lli) ? 1:0;
	lli_number += p_transfer->trans_len / channel_max_trans_per_lli;

	return lli_number;

}


static void dump_lli(struct dw_lli *p_lli){
	FH_DMA_DEBUG("link_mem padd:0x%x\n sar:0x%x\n dar:0x%x\n llp:0x%x\n ctllo:0x%x\n ctlhi:0x%x\n sstat:0x%x\n dstat:0x%x\n",
			(rt_uint32_t)p_lli,p_lli->sar, p_lli->dar, p_lli->llp,
			p_lli->ctllo, p_lli->ctlhi,p_lli->sstat,p_lli->dstat);
}
/*****************************************************************************
 * Description:
 *      add funtion description here
 * Parameters:
 *      description for each argument, new argument starts at new line
 * Return:
 *      what does this function returned?
 *****************************************************************************/
static void handle_single_transfer(struct fh81_dma  *p_dma,struct dma_transfer *p_transfer){


	rt_uint32_t i;
	struct dw_dma *temp_dwc;
	temp_dwc = &p_dma->dwc;
	volatile rt_uint32_t ret_status;
	rt_list_t *p_controller_list;
	rt_uint32_t lli_size,max_trans_size;
	struct dw_lli  *p_lli = RT_NULL;
	struct dma_transfer *dma_trans_desc;
	struct dma_transfer *_dma_trans_desc;


	rt_uint32_t temp_src_add;
	rt_uint32_t temp_dst_add;
	rt_uint32_t trans_total_len = 0;
	rt_uint32_t temp_trans_size = 0;
	//rt_uint32_t dma_channl_no = 0;

	RT_ASSERT(p_transfer->channel_number < p_dma->dwc.channel_max_number);
	RT_ASSERT(p_transfer->dma_number < DMA_CONTROLLER_NUMBER);
	RT_ASSERT(&fh81_dma_controller[p_transfer->dma_number] == p_dma);
	//when the dma transfer....the lock should be 0!!!!
	//or user may not request the channel...
	RT_ASSERT(p_dma->dma_channel[p_transfer->channel_number].channel_lock.value == 0);


	ret_status = p_dma->dma_channel[p_transfer->channel_number].channel_status;
	if(ret_status == CHANNEL_STATUS_CLOSED){
		FH_DMA_DEBUG("transfer error,reason: use a closed channel..\n");
		RT_ASSERT(ret_status != CHANNEL_STATUS_CLOSED);
	}
	p_transfer->dma_controller = p_dma;



	rt_list_init(&p_transfer->transfer_list);
	max_trans_size = p_transfer->dma_controller->dma_channel[p_transfer->channel_number].desc_trans_size;
	//add transfer to the controller's queue list
	//here should  insert before and handle after....this could be a fifo...
	rt_list_insert_before(&p_dma->dma_channel[p_transfer->channel_number].queue , &p_transfer->transfer_list);


	p_controller_list = &p_dma->dma_channel[p_transfer->channel_number].queue;


	//here the driver could make a queue to cache the transfer and kick a thread to handle the queue~~~
	//but now,this is a easy version...,just handle the transfer now!!!
	list_for_each_entry_safe(dma_trans_desc, _dma_trans_desc, p_controller_list, transfer_list) {

		//the dma controller could see the active transfer .....
		p_transfer->dma_controller->dma_channel[p_transfer->channel_number].active_trans = dma_trans_desc;


		trans_total_len = p_transfer->trans_len;


		//handle desc
		//step1:cal lli size...
		lli_size = cal_lli_size(dma_trans_desc);
		//step2:malloc lli_size  mem
		//dma_trans_desc->first_lli = (struct dw_lli *)rt_malloc(lli_size * sizeof(struct dw_lli));

		dma_trans_desc->first_lli = get_desc(p_dma,p_transfer,lli_size);

		//not enough mem..
		if(dma_trans_desc->first_lli == RT_NULL){

			FH_DMA_DEBUG("transfer error,reason: not enough mem..\n");
			RT_ASSERT(dma_trans_desc->first_lli != RT_NULL);
		}


		//bug here....
		rt_memset((void *)dma_trans_desc->first_lli, 0, lli_size * sizeof(struct dw_lli));

		p_lli = dma_trans_desc->first_lli;

		//warnning!!!!must check if the add is 32bits ally...
		RT_ASSERT(((rt_uint32_t)p_lli & 0x03) == 0);

		RT_ASSERT(dma_trans_desc->dst_inc_mode <=DW_DMA_SLAVE_FIX);
		RT_ASSERT(dma_trans_desc->src_inc_mode <=DW_DMA_SLAVE_FIX);
		//step3: set the mem..
		for(i=0;i<lli_size;i++){
			//parse trans para...
			//para add:

			switch(dma_trans_desc->dst_inc_mode){
			case DW_DMA_SLAVE_INC:
				temp_dst_add = dma_trans_desc->dst_add + i * max_trans_size * (1<<dma_trans_desc->dst_width);
				break;
			case DW_DMA_SLAVE_DEC:
				temp_dst_add = dma_trans_desc->dst_add - i * max_trans_size * (1<<dma_trans_desc->dst_width);
				break;
			case DW_DMA_SLAVE_FIX:
				temp_dst_add = dma_trans_desc->dst_add;
				break;

			}


			switch(dma_trans_desc->src_inc_mode){
			case DW_DMA_SLAVE_INC:
				temp_src_add = dma_trans_desc->src_add + i * max_trans_size * (1<<dma_trans_desc->src_width);
				break;
			case DW_DMA_SLAVE_DEC:
				temp_src_add = dma_trans_desc->src_add - i * max_trans_size * (1<<dma_trans_desc->src_width);
				break;
			case DW_DMA_SLAVE_FIX:
				temp_src_add = dma_trans_desc->src_add ;
				break;

			}


			p_lli[i].sar = temp_src_add;
			p_lli[i].dar = temp_dst_add;

			//para ctl
			temp_trans_size = (trans_total_len / max_trans_size)? max_trans_size : (trans_total_len % max_trans_size);
			trans_total_len -= temp_trans_size;

			RT_ASSERT(dma_trans_desc->dst_width <=DW_DMA_SLAVE_WIDTH_32BIT);
			RT_ASSERT(dma_trans_desc->src_width <=DW_DMA_SLAVE_WIDTH_32BIT);

			RT_ASSERT(dma_trans_desc->dst_msize <=DW_DMA_SLAVE_MSIZE_256);
			RT_ASSERT(dma_trans_desc->src_msize <=DW_DMA_SLAVE_MSIZE_256);
			RT_ASSERT(dma_trans_desc->fc_mode <=DMA_P2P);



			p_lli[i].ctllo = DWC_CTLL_INT_EN|DWC_CTLL_DST_WIDTH(dma_trans_desc->dst_width)|DWC_CTLL_SRC_WIDTH(dma_trans_desc->src_width)
					|DWC_CTLL_DST_INC_MODE(dma_trans_desc->dst_inc_mode)|DWC_CTLL_SRC_INC_MODE(dma_trans_desc->src_inc_mode)
					|DWC_CTLL_DST_MSIZE(dma_trans_desc->dst_msize)|DWC_CTLL_SRC_MSIZE(dma_trans_desc->src_msize)|DWC_CTLL_FC(dma_trans_desc->fc_mode)
					|DWC_CTLL_DMS(0)|DWC_CTLL_SMS(0);
			//block size
			p_lli[i].ctlhi = temp_trans_size;


			if(trans_total_len > 0){
				p_lli[i].llp = (rt_uint32_t)&p_lli[i+1];
				p_lli[i].ctllo |= DWC_CTLL_LLP_D_EN|DWC_CTLL_LLP_S_EN;
			}

			//flush cache to mem
			mmu_clean_invalidated_dcache((rt_uint32_t)&p_lli[i],sizeof(struct dw_lli));

			dump_lli(&p_lli[i]);
		}

		//clear the isr status




		//set the dma config reg
		//clear cfg reload reg
		//ret_status = dw_readl(temp_dwc,CHAN[dma_trans_desc->channel_number].CFG_LO);
		//ret_status &= ~(DWC_CFGL_RELOAD_SAR|DWC_CFGL_RELOAD_DAR);
		dw_writel(temp_dwc,CHAN[dma_trans_desc->channel_number].CFG_LO,0);

		//set the first link add
		//ret_status = dw_readl(temp_dwc,CHAN[dma_trans_desc->channel_number].LLP);
		ret_status = 0;
		ret_status = (rt_uint32_t)&p_lli[0];
		dw_writel(temp_dwc,CHAN[dma_trans_desc->channel_number].LLP,ret_status);

		//set link enable
		//ret_status = dw_readl(temp_dwc,CHAN[dma_trans_desc->channel_number].CTL_LO);
		ret_status = 0;
		ret_status =DWC_CTLL_LLP_D_EN|DWC_CTLL_LLP_S_EN;
		dw_writel(temp_dwc,CHAN[dma_trans_desc->channel_number].CTL_LO,ret_status);

		dw_writel(temp_dwc,CHAN[dma_trans_desc->channel_number].CTL_HI,0);
		//set handshaking

		RT_ASSERT(dma_trans_desc->dst_hs <=	DMA_SW_HANDSHAKING);
		RT_ASSERT(dma_trans_desc->src_hs <=	DMA_SW_HANDSHAKING);

		if(dma_trans_desc->dst_hs == DMA_SW_HANDSHAKING){
			ret_status = dw_readl(temp_dwc,CHAN[dma_trans_desc->channel_number].CFG_LO);
			ret_status |= DWC_CFGL_HS_DST;
			dw_writel(temp_dwc,CHAN[dma_trans_desc->channel_number].CFG_LO,ret_status);
		}
		else{
			ret_status = dw_readl(temp_dwc,CHAN[dma_trans_desc->channel_number].CFG_LO);
			ret_status &= ~DWC_CFGL_HS_DST;
			dw_writel(temp_dwc,CHAN[dma_trans_desc->channel_number].CFG_LO,ret_status);
		}

		if(dma_trans_desc->src_hs == DMA_SW_HANDSHAKING){
			ret_status = dw_readl(temp_dwc,CHAN[dma_trans_desc->channel_number].CFG_LO);
			ret_status |= DWC_CFGL_HS_SRC;
			dw_writel(temp_dwc,CHAN[dma_trans_desc->channel_number].CFG_LO,ret_status);
		}
		else{
			ret_status = dw_readl(temp_dwc,CHAN[dma_trans_desc->channel_number].CFG_LO);
			ret_status &= ~DWC_CFGL_HS_SRC;
			dw_writel(temp_dwc,CHAN[dma_trans_desc->channel_number].CFG_LO,ret_status);
		}


		//only hw handshaking need this..
		switch(dma_trans_desc->fc_mode){
		case	DMA_M2M:
			break;
		case	DMA_M2P:
			//set dst per...
			RT_ASSERT(dma_trans_desc->dst_per <	DMA_HW_HS_END);

			ret_status = dw_readl(temp_dwc,CHAN[dma_trans_desc->channel_number].CFG_HI);

			//clear 43 ~ 46 bit
			ret_status &= ~0x7800;

			ret_status |= DWC_CFGH_DST_PER(dma_trans_desc->dst_per);
			dw_writel(temp_dwc,CHAN[dma_trans_desc->channel_number].CFG_HI,ret_status);
			//DWC_CFGH_SRC_PER


			break;
		case 	DMA_P2M:
			//set src per...
			RT_ASSERT(dma_trans_desc->src_per <	DMA_HW_HS_END);


			ret_status = dw_readl(temp_dwc,CHAN[dma_trans_desc->channel_number].CFG_HI);

			//clear 39 ~ 42 bit
			ret_status &= ~0x780;


			ret_status |= DWC_CFGH_SRC_PER(dma_trans_desc->src_per);
			dw_writel(temp_dwc,CHAN[dma_trans_desc->channel_number].CFG_HI,ret_status);

			break;
		case 	DMA_P2P:
			//set src and dst..
			RT_ASSERT(dma_trans_desc->dst_per <	DMA_HW_HS_END);
			RT_ASSERT(dma_trans_desc->src_per <	DMA_HW_HS_END);

			ret_status = dw_readl(temp_dwc,CHAN[dma_trans_desc->channel_number].CFG_HI);
			ret_status &= ~0x7800;
			ret_status &= ~0x780;
			ret_status |= DWC_CFGH_SRC_PER(dma_trans_desc->src_per) | DWC_CFGH_DST_PER(dma_trans_desc->dst_per);
			dw_writel(temp_dwc,CHAN[dma_trans_desc->channel_number].CFG_HI,ret_status);

			break;
		default:
			break;
		}


		dma_trans_desc->dma_controller->dma_channel[dma_trans_desc->channel_number].channel_status = CHANNEL_STATUS_BUSY;
		//enable isr...
		channel_set_bit(temp_dwc, MASK.XFER, lift_shift_bit_num(dma_trans_desc->channel_number));
		channel_set_bit(temp_dwc, MASK.ERROR, lift_shift_bit_num(dma_trans_desc->channel_number));
		//close
		channel_clear_bit(temp_dwc, MASK.BLOCK, lift_shift_bit_num(dma_trans_desc->channel_number));

		dw_writel(temp_dwc, CLEAR.XFER, 1<<(dma_trans_desc->channel_number));
		dw_writel(temp_dwc, CLEAR.BLOCK, 1<<(dma_trans_desc->channel_number));
		dw_writel(temp_dwc, CLEAR.SRC_TRAN, 1<<(dma_trans_desc->channel_number));
		dw_writel(temp_dwc, CLEAR.DST_TRAN, 1<<(dma_trans_desc->channel_number));
		dw_writel(temp_dwc, CLEAR.ERROR, 1<<(dma_trans_desc->channel_number));


		ret_status = dw_readl(temp_dwc,CHAN[dma_trans_desc->channel_number].CFG_HI);
		FH_DMA_DEBUG("cfg_hi value:0x%x\n",ret_status);

		ret_status = dw_readl(temp_dwc,CHAN[dma_trans_desc->channel_number].CFG_LO);
		FH_DMA_DEBUG("cfg_low value:0x%x\n",ret_status);


		ret_status = dw_readl(temp_dwc, MASK.BLOCK);
		FH_DMA_DEBUG("mask block value:0x%x\n",ret_status);

		ret_status = dw_readl(temp_dwc, MASK.XFER);
		FH_DMA_DEBUG("mask xfer value:0x%x\n",ret_status);



		if(dma_trans_desc->prepare_callback){
				dma_trans_desc->prepare_callback(dma_trans_desc->prepare_para);
		}
		//enable the channle to transfer
		channel_set_bit(temp_dwc, CH_EN, lift_shift_bit_num(dma_trans_desc->channel_number));



	}

}

/*****************************************************************************
 * Description:
 *      add funtion description here
 * Parameters:
 *      description for each argument, new argument starts at new line
 * Return:
 *      what does this function returned?
 *****************************************************************************/
static rt_err_t control (struct rt_dma_device *dma, int cmd, void *arg){


	struct fh81_dma *my_own = (struct fh81_dma *)dma->parent.user_data;
	rt_uint32_t i;
	struct dw_dma *dwc;
	dwc = &my_own->dwc;

	rt_err_t ret = RT_EOK;

	struct dma_transfer *p_dma_transfer = (struct dma_transfer *)arg;

	//FH_DMA_DEBUG("p_dma_transfer value:0x%x\n",(rt_uint32_t)p_dma_transfer);


	RT_ASSERT(my_own != RT_NULL);
	RT_ASSERT(dwc != RT_NULL);



	switch(cmd){
	case RT_DEVICE_CTRL_DMA_OPEN:

		//open the controller..
		handle_dma_open(my_own);
		break;
	case RT_DEVICE_CTRL_DMA_CLOSE:

		//close the controller..
		handle_dma_close(my_own);
		break;
	case RT_DEVICE_CTRL_DMA_REQUEST_CHANNEL:
		//request a channel for the user
		RT_ASSERT(p_dma_transfer != RT_NULL);
		ret = handle_request_channel(my_own,p_dma_transfer);

		break;
	case RT_DEVICE_CTRL_DMA_RELEASE_CHANNEL:
		//release a channel
		RT_ASSERT(p_dma_transfer != RT_NULL);

		ret = handle_release_channel(my_own,p_dma_transfer);


		break;

	case RT_DEVICE_CTRL_DMA_SINGLE_TRANSFER:
		//make a channel to transfer data.
		RT_ASSERT(p_dma_transfer != RT_NULL);
		//check if the dma channel is open,or return error.

		my_own->dma_channel[p_dma_transfer->channel_number].open_flag = SINGLE_TRANSFER;
		handle_single_transfer(my_own,p_dma_transfer);
		//then wait for the channel is complete..
		//caution that::we should be in the "rt_enter_critical()"when set the dma to work.
		break;


	case RT_DEVICE_CTRL_DMA_CYCLIC_PREPARE:
		RT_ASSERT(p_dma_transfer != RT_NULL);
		my_own->dma_channel[p_dma_transfer->channel_number].open_flag = CYCLIC_TRANSFER;
		rt_fh_dma_cyclic_prep(my_own,p_dma_transfer);
		break;

	case RT_DEVICE_CTRL_DMA_CYCLIC_START:
		rt_fh_dma_cyclic_start(p_dma_transfer);
		break;

	case RT_DEVICE_CTRL_DMA_CYCLIC_STOP:
		rt_fh_dma_cyclic_stop(p_dma_transfer);
		break;

	case RT_DEVICE_CTRL_DMA_CYCLIC_FREE:
		rt_fh_dma_cyclic_free(p_dma_transfer);
		break;

	default:
		break;

	}

	return ret;


}



static void rt_fh81_dma_isr(int irq, void *param)
{


	RT_ASSERT(irq == DMAC_IRQn);
	rt_uint32_t isr_channel_x,i,error,isr_channel_b;
	struct fh81_dma *my_own = (struct fh81_dma *)param;
	struct dw_dma *dwc;
	struct dma_transfer *p_transfer;
	dwc = &my_own->dwc;
	//p_transfer =
	//rt_kprintf("dma isr get in~~~\n");
	error = dw_readl(dwc,STATUS.ERROR);
	if(error != 0){
		FH_DMA_DEBUG("dma isr error!!!!\n");
		RT_ASSERT(error == RT_NULL);
	}

	isr_channel_x = dw_readl(dwc,STATUS.XFER);
	isr_channel_b = dw_readl(dwc,STATUS.BLOCK);
	//for single check the transfer status
	//check which channel...

	for(i=0;i<my_own->dwc.channel_max_number;i++){

		if(my_own->dma_channel[i].open_flag == SINGLE_TRANSFER){
			if(isr_channel_x & 1<<i){
				dw_writel(dwc, CLEAR.XFER, 1<<i);

				p_transfer = my_own->dma_channel[i].active_trans;

				if(p_transfer->complete_callback){
						p_transfer->complete_callback(p_transfer->complete_para);
				}
				p_transfer->dma_controller->dma_channel[p_transfer->channel_number].channel_status = CHANNEL_STATUS_IDLE;
				//here is a bug...do not free here
				//rt_free(p_transfer->first_lli);
				put_desc(my_own,p_transfer);
				rt_list_remove(&p_transfer->transfer_list);
			}

		}

		else if(my_own->dma_channel[i].open_flag == CYCLIC_TRANSFER){
			if(isr_channel_b & 1<<i){
				p_transfer = my_own->dma_channel[i].active_trans;
				dw_writel(dwc, CLEAR.BLOCK, 1<<(p_transfer->channel_number));
				if(p_transfer->complete_callback){
						p_transfer->complete_callback(p_transfer->complete_para);
				}
			}
		}
	}


}



/*****************************************************************************
 * Description:
 *      add funtion description here
 * Parameters:
 *      description for each argument, new argument starts at new line
 * Return:
 *      what does this function returned?
 *****************************************************************************/

const char *channel_lock_name[FH81_MAX_CHANNEL] = {
		"channel_0_lock",
		"channel_1_lock",
		"channel_2_lock",
		"channel_3_lock",
};

rt_err_t fh81_dma_register(struct fh81_dma * fh81_dma_p,
                             char * dma_name){

	rt_uint32_t i;

	RT_ASSERT(fh81_dma_p != RT_NULL);
	RT_ASSERT(dma_name != RT_NULL);
	//RT_ASSERT(fh81_dma_p->dwc.init != FH81_DMA_INIT_ALREADY);


	if(fh81_dma_p->dwc.init == FH81_DMA_INIT_ALREADY)
		return 0;

	struct rt_dma_device *rt_dma;
	rt_dma = &fh81_dma_p->parent;
	rt_dma->ops = &fh81_dma_ops;


	//soc para set
	fh81_dma_p->dwc.name = dma_name;
	fh81_dma_p->dwc.regs =(void *)DMA_REG_BASE;
	fh81_dma_p->dwc.paddr =	DMA_REG_BASE;
	fh81_dma_p->dwc.irq = DMAC_IRQn;
	fh81_dma_p->dwc.channel_max_number = FH81_MAX_CHANNEL;
	fh81_dma_p->dwc.controller_status = CONTROLLER_STATUS_CLOSED;
	fh81_dma_p->dwc.init = FH81_DMA_INIT_ALREADY;
	fh81_dma_p->dwc.id = 0;
	//channel set
	for(i=0;i<FH81_MAX_CHANNEL;i++){
		fh81_dma_p->dma_channel[i].channel_status = CHANNEL_STATUS_CLOSED;
		fh81_dma_p->dma_channel[i].desc_total_no = DESC_MAX_SIZE;
		//rt_completion_init(&(fh81_dma_p->dma_channel[i].transfer_completion));
		rt_list_init(&(fh81_dma_p->dma_channel[i].queue));
		fh81_dma_p->dma_channel[i].desc_trans_size = FH81_CHANNEL_MAX_TRANSFER_SIZE;
		rt_sem_init(&fh81_dma_p->dma_channel[i].channel_lock, channel_lock_name[i], 1, RT_IPC_FLAG_FIFO);
	}

	//isr
	rt_hw_interrupt_install(fh81_dma_p->dwc.irq, rt_fh81_dma_isr,
							(void *)fh81_dma_p, "dma_isr");
	rt_hw_interrupt_umask(fh81_dma_p->dwc.irq);

	return	rt_hw_dma_register(rt_dma,dma_name,RT_DEVICE_FLAG_RDWR,fh81_dma_p);


}


static void rt_fh_dma_cyclic_stop(struct dma_transfer *p){

	struct fh81_dma *my_own = p->dma_controller;
	struct dw_dma *dwc;
	dwc = &my_own->dwc;
	channel_clear_bit(dwc, CH_EN, 1<<(p->channel_number));
}




static void rt_fh_dma_cyclic_start(struct dma_transfer *p){

	struct fh81_dma *my_own = p->dma_controller;
	struct dw_dma *dwc;
	dwc = &my_own->dwc;
	volatile uint32_t ret_status;
	struct dw_lli  *p_lli = RT_NULL;
	p_lli = p->first_lli;

	//32bit ally
	RT_ASSERT(((uint32_t)p_lli & 0x03) == 0);

	dw_writel(dwc, CLEAR.XFER, 1<<(p->channel_number));
	dw_writel(dwc, CLEAR.BLOCK, 1<<(p->channel_number));
	dw_writel(dwc, CLEAR.ERROR, 1<<(p->channel_number));


	//enable isr
	channel_set_bit(dwc, MASK.BLOCK, lift_shift_bit_num(p->channel_number));
	//disable isr
	channel_clear_bit(dwc, MASK.XFER, lift_shift_bit_num(p->channel_number));

	ret_status = dw_readl(dwc,CHAN[p->channel_number].CFG_LO);
	ret_status &= ~(DWC_CFGL_RELOAD_SAR|DWC_CFGL_RELOAD_DAR);
	dw_writel(dwc,CHAN[p->channel_number].CFG_LO,ret_status);

	//set the first link add
	ret_status = dw_readl(dwc,CHAN[p->channel_number].LLP);
	ret_status = (uint32_t)&p_lli[0];
	dw_writel(dwc,CHAN[p->channel_number].LLP,ret_status);

	//set link enable
	//ret_status = dw_readl(dwc,CHAN[p->channel_number].CTL_LO);
	ret_status =DWC_CTLL_LLP_D_EN|DWC_CTLL_LLP_S_EN;
	dw_writel(dwc,CHAN[p->channel_number].CTL_LO,ret_status);

	//clear ctl_hi
	dw_writel(dwc,CHAN[p->channel_number].CTL_HI,0);

	//enable channle
	channel_set_bit(dwc, CH_EN, 1<<(p->channel_number));


}


static void rt_fh_dma_cyclic_prep(struct fh81_dma * fh81_dma_p,struct dma_transfer *p) {

	//bind the controller to the transfer
	p->dma_controller = fh81_dma_p;
	//bind active transfer
	fh81_dma_p->dma_channel[p->channel_number].active_trans = p;
	//p_transfer->dma_controller->dma_channel[p_transfer->channel_number].active_trans = dma_trans_desc;
	struct fh81_dma *my_own = p->dma_controller;
	struct dw_dma *dwc;
	dwc = &my_own->dwc;
	volatile uint32_t ret_status;
	struct dw_lli  *p_lli = RT_NULL;
	uint32_t periods,i;
	uint32_t temp_src_add;
	uint32_t temp_dst_add;
	uint32_t buf_len = p->trans_len;
	uint32_t period_len = p->period_len;

	struct dma_transfer * dma_trans_desc = p;
	//check first...
	RT_ASSERT(buf_len % period_len == 0);

	//cal the periods...
	periods = buf_len / period_len;


	//get desc....
	//dma_trans_desc->first_lli = (struct dw_lli *)rt_malloc(periods * sizeof(struct dw_lli));
	dma_trans_desc->first_lli  = get_desc(fh81_dma_p,dma_trans_desc,periods);

	if(dma_trans_desc->first_lli == RT_NULL){

		FH_DMA_DEBUG("transfer error,reason: not enough mem..\n");
		RT_ASSERT(dma_trans_desc->first_lli != RT_NULL);
	}

	rt_memset((void *)dma_trans_desc->first_lli, 0, periods * sizeof(struct dw_lli));
	p_lli = dma_trans_desc->first_lli;

	RT_ASSERT(((uint32_t)p_lli & 0x03) == 0);


	RT_ASSERT(dma_trans_desc->dst_inc_mode <=DW_DMA_SLAVE_FIX);
	RT_ASSERT(dma_trans_desc->src_inc_mode <=DW_DMA_SLAVE_FIX);
	//step3: set the mem..
	for(i=0;i<periods;i++){
		//parse trans para...
		//para add:
		switch(dma_trans_desc->dst_inc_mode){
		case DW_DMA_SLAVE_INC:
			temp_dst_add = dma_trans_desc->dst_add + i * period_len * (1<<dma_trans_desc->dst_width);
			break;
		case DW_DMA_SLAVE_DEC:
			temp_dst_add = dma_trans_desc->dst_add - i * period_len * (1<<dma_trans_desc->dst_width);
			break;
		case DW_DMA_SLAVE_FIX:
			temp_dst_add = dma_trans_desc->dst_add;
			break;

		}


		switch(dma_trans_desc->src_inc_mode){
		case DW_DMA_SLAVE_INC:
			temp_src_add = dma_trans_desc->src_add + i * period_len * (1<<dma_trans_desc->src_width);
			break;
		case DW_DMA_SLAVE_DEC:
			temp_src_add = dma_trans_desc->src_add - i * period_len * (1<<dma_trans_desc->src_width);
			break;
		case DW_DMA_SLAVE_FIX:
			temp_src_add = dma_trans_desc->src_add ;
			break;

		}


		p_lli[i].sar = temp_src_add;
		p_lli[i].dar = temp_dst_add;

		//para ctl


		RT_ASSERT(dma_trans_desc->dst_width <=DW_DMA_SLAVE_WIDTH_32BIT);
		RT_ASSERT(dma_trans_desc->src_width <=DW_DMA_SLAVE_WIDTH_32BIT);

		RT_ASSERT(dma_trans_desc->dst_msize <=DW_DMA_SLAVE_MSIZE_256);
		RT_ASSERT(dma_trans_desc->src_msize <=DW_DMA_SLAVE_MSIZE_256);
		RT_ASSERT(dma_trans_desc->fc_mode <=DMA_P2P);



		p_lli[i].ctllo = DWC_CTLL_INT_EN|DWC_CTLL_DST_WIDTH(dma_trans_desc->dst_width)|DWC_CTLL_SRC_WIDTH(dma_trans_desc->src_width)
				|DWC_CTLL_DST_INC_MODE(dma_trans_desc->dst_inc_mode)|DWC_CTLL_SRC_INC_MODE(dma_trans_desc->src_inc_mode)
				|DWC_CTLL_DST_MSIZE(dma_trans_desc->dst_msize)|DWC_CTLL_SRC_MSIZE(dma_trans_desc->src_msize)|DWC_CTLL_FC(dma_trans_desc->fc_mode)
				|DWC_CTLL_DMS(0)|DWC_CTLL_SMS(0);
		//block size
		p_lli[i].ctlhi = period_len;



		p_lli[i].llp = (uint32_t)&p_lli[i+1];
		p_lli[i].ctllo |= DWC_CTLL_LLP_D_EN|DWC_CTLL_LLP_S_EN;


		//flush cache to mem
		mmu_clean_invalidated_dcache((uint32_t)&p_lli[i],sizeof(struct dw_lli));

		dump_lli(&p_lli[i]);
	}
	//make a ring here
	p_lli[periods -1 ].llp = (uint32_t)&p_lli[0];

	mmu_clean_invalidated_dcache((uint32_t)&p_lli[periods -1 ],sizeof(struct dw_lli));



	//parse the handshake
	RT_ASSERT(dma_trans_desc->dst_hs <=	DMA_SW_HANDSHAKING);
	RT_ASSERT(dma_trans_desc->src_hs <=	DMA_SW_HANDSHAKING);

	//dst handshake
	dw_writel(dwc,CHAN[dma_trans_desc->channel_number].CFG_LO,0);
	ret_status = 0;
	if(dma_trans_desc->dst_hs == DMA_SW_HANDSHAKING){
		ret_status |= DWC_CFGL_HS_DST;
	}
	else{
		ret_status &= ~DWC_CFGL_HS_DST;
	}
	dw_writel(dwc,CHAN[dma_trans_desc->channel_number].CFG_LO,ret_status);



	//src handshake
	ret_status = dw_readl(dwc,CHAN[dma_trans_desc->channel_number].CFG_LO);
	if(dma_trans_desc->src_hs == DMA_SW_HANDSHAKING){
		ret_status |= DWC_CFGL_HS_SRC;
	}
	else{
		ret_status &= ~DWC_CFGL_HS_SRC;
	}
	dw_writel(dwc,CHAN[dma_trans_desc->channel_number].CFG_LO,ret_status);


	//only hw handshaking need this..
	switch(dma_trans_desc->fc_mode){
	case	DMA_M2M:
		break;
	case	DMA_M2P:
		//set dst per...
		RT_ASSERT(dma_trans_desc->dst_per <	DMA_HW_HS_END);
		ret_status = dw_readl(dwc,CHAN[dma_trans_desc->channel_number].CFG_HI);
		//clear 43 ~ 46 bit
		ret_status &= ~0x7800;
		ret_status |= DWC_CFGH_DST_PER(dma_trans_desc->dst_per);
		dw_writel(dwc,CHAN[dma_trans_desc->channel_number].CFG_HI,ret_status);
		//DWC_CFGH_SRC_PER

		break;
	case 	DMA_P2M:
		//set src per...
		RT_ASSERT(dma_trans_desc->src_per <	DMA_HW_HS_END);
		ret_status = dw_readl(dwc,CHAN[dma_trans_desc->channel_number].CFG_HI);
		//clear 39 ~ 42 bit
		ret_status &= ~0x780;
		ret_status |= DWC_CFGH_SRC_PER(dma_trans_desc->src_per);
		dw_writel(dwc,CHAN[dma_trans_desc->channel_number].CFG_HI,ret_status);

		break;
	case 	DMA_P2P:
		//set src and dst..
		RT_ASSERT(dma_trans_desc->dst_per <	DMA_HW_HS_END);
		RT_ASSERT(dma_trans_desc->src_per <	DMA_HW_HS_END);

		ret_status = dw_readl(dwc,CHAN[dma_trans_desc->channel_number].CFG_HI);
		ret_status &= ~0x7800;
		ret_status &= ~0x780;
		ret_status |= DWC_CFGH_SRC_PER(dma_trans_desc->src_per) | DWC_CFGH_DST_PER(dma_trans_desc->dst_per);
		dw_writel(dwc,CHAN[dma_trans_desc->channel_number].CFG_HI,ret_status);

		break;
	default:
		break;
	}

	dma_trans_desc->dma_controller->dma_channel[dma_trans_desc->channel_number].channel_status = CHANNEL_STATUS_BUSY;

	if(dma_trans_desc->prepare_callback){
			dma_trans_desc->prepare_callback(dma_trans_desc->prepare_para);
	}

}


static void rt_fh_dma_cyclic_free(struct dma_transfer *p){

	struct fh81_dma *my_own = p->dma_controller;
	struct dw_dma *dwc;
	dwc = &my_own->dwc;
	volatile uint32_t ret_status;
	struct dw_lli  *p_lli = RT_NULL;
	p_lli = p->first_lli;


	//close channel first..
	channel_clear_bit(dwc, CH_EN, 1<<(p->channel_number));

	//check if close really
	while (dw_readl(dwc, CH_EN) & 1<<(p->channel_number));

	dw_writel(dwc, CLEAR.XFER, 1<<(p->channel_number));
	dw_writel(dwc, CLEAR.BLOCK, 1<<(p->channel_number));
	dw_writel(dwc, CLEAR.ERROR, 1<<(p->channel_number));




	//rt_free(p->first_lli);
	put_desc(my_own,p);

}


void rt_fh_dma_init(void){
	fh81_dma_register(&fh81_dma_controller[0],"fh81_dma");

}
