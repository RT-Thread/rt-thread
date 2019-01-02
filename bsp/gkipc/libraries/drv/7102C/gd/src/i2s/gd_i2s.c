/******************************************************************************
**
** \file      gh_i2s.c
**
** \brief     I2S.
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#include <stdio.h>
#include <string.h>

#include "gh_i2s.h"
	
#include "gd_dma.h"
#include "gd_i2s.h"
#include "gd_timer.h"


#define I2S_DEBUG
#ifdef I2S_DEBUG
#define I2S_PRINTF(args...) printf(args)
#else
#define I2S_PRINTF(args...)
#endif

#define I2S_STATE_DISABLE  0
#define I2S_STATE_ENABLE   1
#define I2S_STATE_RUNNING  2
#define I2S_STATE_WAITING  3

#define I2S_DEV_ID        (0x00533249)  //'I2S'
#define I2S_DEV_RX_ID     (0x52533249)  //'I2SR'
#define I2S_DEV_TX_ID     (0x54533249)  //'I2ST'
#define I2S_DEV_MIN_FRAME (2)    				 //minimum frame number which device supported.
#define I2S_DEV_MAX_FRAME (DMA_CHAN_MAX_DESC)	 //maximum frame number which device supported.
#define I2S_DEV_MAX_BUFF  (I2S_DEV_MAX_FRAME*512)
#define I2S_BUF_MIN_FRAME (2)                    //data level  

typedef struct
{
	U32       subDevID;
	U32       state;
	U32       event;
	GD_HANDLE dmaHandle;
	GD_I2S_Notifier notifier;	
	U32       frameNumber;
	U32       frameSize;
	U32       nextDescriptor;
	U32      *dmaReportBuffer;
	U8       *dmaFrameBuffer;
	U8       *rdPointer;
	U8       *wrPointer;
	U8       *rearPointer;
}SUB_DEVICE_S;

typedef struct
{
    U32                 devID;
	GBOOL               master;
	GBOOL               directMode;         //rx --> tx
    GD_I2S_CHANNEL_E    channel;
    GD_I2S_MODE_E       mode;
    GD_I2S_SPEED_E      speed;
    GD_I2S_WLEN_E       wlen;  
	SUB_DEVICE_S        rx;
	SUB_DEVICE_S        tx;
} I2S_DEVICE_S;

static I2S_DEVICE_S i2sDev __attribute__ ((section(".nocache_buffer")));
static U32 rxReportBuffer[I2S_DEV_MAX_FRAME] __attribute__ ((section(".nocache_buffer")));
static U32 txReportBuffer[I2S_DEV_MAX_FRAME] __attribute__ ((section(".nocache_buffer")));
static U8 rxDmaBuffer[I2S_DEV_MAX_BUFF] __attribute__ ((aligned(DMA_BUFF_ADDR_ALIGN),section(".nocache_buffer")));
static U8 txDmaBuffer[I2S_DEV_MAX_BUFF] __attribute__ ((aligned(DMA_BUFF_ADDR_ALIGN),section(".nocache_buffer")));
static SUB_DEVICE_S * const prxDev = &i2sDev.rx;
static SUB_DEVICE_S * const ptxDev = &i2sDev.tx;


static void rx_int_handler(void)
{
	U32 curDescriptor = 0;
	U32 dmaStatus     = 0;
	U32 revFrameNumber = 0;
	U8 *frameReadPointer = 0;
	U8 *frameWritePointer = 0;	
	SUB_DEVICE_S * pDev = prxDev;
	
	curDescriptor = pDev->nextDescriptor;
	pDev->nextDescriptor++;
	if(pDev->nextDescriptor >= pDev->frameNumber)
	{
		pDev->nextDescriptor = 0;
	}	

	dmaStatus = pDev->dmaReportBuffer[curDescriptor];	
	if(dmaStatus & DMA_CHAN_STATE_DD)
	{
	
	}	
	
	if(dmaStatus & DMA_CHAN_STATE_OD) /* DO NOT verify this field, report buffer will not refresh after DMA int sometimes. */
	{
		pDev->wrPointer += pDev->frameSize;
		if(pDev->wrPointer >= pDev->rearPointer)
		{
			pDev->wrPointer = pDev->dmaFrameBuffer;
		}

		pDev->dmaReportBuffer[curDescriptor] &= ~(DMA_CHAN_STATE_OD|DMA_CHAN_STATE_DN);
		
		if(pDev->notifier != NULL)
		{
			pDev->notifier(I2S_EVENT_FRAME);
		}
	}
	else /* not expected interrupt */
	{
		pDev->event = I2S_EVENT_UNDEFINED;		  //for debug only.
		pDev->notifier(I2S_EVENT_UNDEFINED);
	}

	frameReadPointer  = pDev->rdPointer;
	frameWritePointer = pDev->wrPointer;
	if(frameReadPointer <= frameWritePointer)
	{
		revFrameNumber = (frameWritePointer - frameReadPointer) / pDev->frameSize;
	}
	else
	{
		revFrameNumber = pDev->frameNumber -(frameReadPointer - frameWritePointer) / pDev->frameSize;
	}
	if(revFrameNumber >= pDev->frameNumber - I2S_BUF_MIN_FRAME)
	{
		if(pDev->notifier != NULL)
		{
			pDev->notifier(I2S_EVENT_WILL_OVERFLOW);
		}
		pDev->event = I2S_EVENT_WILL_OVERFLOW;
	}
	if(revFrameNumber == 0)
	{
		if(pDev->notifier != NULL)
		{
			pDev->notifier(I2S_EVENT_ALREADY_OVERFLOW);
		}
		pDev->event =I2S_EVENT_ALREADY_OVERFLOW;
	}		

}

static void tx_int_handler(void)
{
	U32 curDescriptor = 0;
	U32 dmaStatus     = 0;
	U32 revFrameNumber = 0;
	U8 *frameReadPointer = 0;
	U8 *frameWritePointer = 0;	
	SUB_DEVICE_S * pDev = ptxDev;
	
	curDescriptor = pDev->nextDescriptor;
	pDev->nextDescriptor++;
	if(pDev->nextDescriptor >= pDev->frameNumber)
	{
		pDev->nextDescriptor = 0;
	}

	dmaStatus = pDev->dmaReportBuffer[curDescriptor];
	if(dmaStatus & DMA_CHAN_STATE_DD)
	{
		
	}

	
	if(dmaStatus & DMA_CHAN_STATE_OD) /* DO NOT verify this field, report buffer will not refresh after DMA int sometimes. */
	{
		pDev->rdPointer += pDev->frameSize;
		if(pDev->rdPointer >= pDev->rearPointer)
		{
			pDev->rdPointer = pDev->dmaFrameBuffer;
		}

		pDev->dmaReportBuffer[curDescriptor] &= ~(DMA_CHAN_STATE_OD|DMA_CHAN_STATE_DN);

		if(pDev->notifier != NULL)
		{
			pDev->notifier(I2S_EVENT_FRAME);
		}
	}		
	else /* not expected interrupt */
	{
		pDev->event = I2S_EVENT_UNDEFINED;         //for debug only.
		pDev->notifier(I2S_EVENT_UNDEFINED);
	}


	frameReadPointer  = pDev->rdPointer;
	frameWritePointer = pDev->wrPointer;
	if(frameReadPointer <= frameWritePointer)
	{
		revFrameNumber = (frameWritePointer - frameReadPointer) / pDev->frameSize;
	}
	else
	{
		revFrameNumber = pDev->frameNumber -(frameReadPointer - frameWritePointer) / pDev->frameSize;
	}

	if(revFrameNumber <= 0)
	{
		if(pDev->notifier != NULL)
		{
			pDev->notifier(I2S_EVENT_ALREADY_UNDERFLOW);
		}
		pDev->event = I2S_EVENT_ALREADY_UNDERFLOW;

		GH_I2S_set_Initreg_te(0);
		pDev->state = I2S_STATE_WAITING;
	}		
	else if(revFrameNumber <= I2S_BUF_MIN_FRAME)
	{
		if(pDev->notifier != NULL)
		{
			pDev->notifier(I2S_EVENT_WILL_UNDERFLOW);
		}
		pDev->event = I2S_EVENT_WILL_UNDERFLOW;
	}
}


static GERR dma_open(SUB_DEVICE_S *dev)
{
	U32 i = 0;
	U32 align_offset = 0;
	GERR err = GD_OK;
	GD_DMA_DESCRIPTOR_S dmaDescriptor;
	GD_DMA_OPEN_PARAM_S dmaOpenParam;
		
	if(dev->frameNumber<=0 || dev->frameSize<=0)
	{
		return GD_ERR_BAD_PARAMETER;
	}

	////////////////////////////////
	//config descriptor
	////////////////////////////////
	
	if(dev->subDevID == I2S_DEV_RX_ID)
	{
		dev->dmaFrameBuffer  = rxDmaBuffer;
		dev->dmaReportBuffer = rxReportBuffer;
		dev->nextDescriptor  = 0;
		dev->rdPointer       = dev->dmaFrameBuffer;
		dev->wrPointer       = dev->dmaFrameBuffer;
		dev->rearPointer     = dev->dmaFrameBuffer + dev->frameNumber*dev->frameSize;	
		
		dmaOpenParam.channel = DMA_CHAN_I2S_RX;
		dmaOpenParam.mode    = DMA_MODE_DESCRIPTOR;
		dmaOpenParam.intNotifier = rx_int_handler;
	}
	else /* I2S_DEV_TX_ID */
	{
		dev->dmaFrameBuffer  = txDmaBuffer;
		dev->dmaReportBuffer = txReportBuffer;
		dev->nextDescriptor  = 0;
		dev->rdPointer       = dev->dmaFrameBuffer;
		dev->wrPointer       = dev->dmaFrameBuffer;
		dev->rearPointer     = dev->dmaFrameBuffer + dev->frameNumber*dev->frameSize;
		
		dmaOpenParam.channel = DMA_CHAN_I2S_TX;
		dmaOpenParam.mode	 = DMA_MODE_DESCRIPTOR;
		dmaOpenParam.intNotifier = tx_int_handler;
	}
	I2S_PRINTF("[GD_I2S]dmaFrameBuffer:0x%08X\n", dev->dmaFrameBuffer);
	
	err = GD_DMA_Open(&dmaOpenParam, &dev->dmaHandle);
	if(err != GD_OK)
	{
		return err;
	}

	////////////////////////////////
	//config descriptor
	////////////////////////////////	
	for(i=0; i<dev->frameNumber; i++)
	{
		if(dev->subDevID == I2S_DEV_RX_ID)
		{
			dmaDescriptor.srcAddr  = DMA_RX_REG;
			dmaDescriptor.dstAddr  = (U32)dev->dmaFrameBuffer + i * dev->frameSize;
			dmaDescriptor.descAttr = DMA_DESC_WM|DMA_DESC_NI|DMA_DESC_TS_4B /*|DMA_DESC_EOC*/
				                   |DMA_DESC_BLK_8B|DMA_DESC_ID|DMA_DESC_IE|DMA_DESC_ST;
		}
		else /* I2S_DEV_TX_ID */
		{
			dmaDescriptor.srcAddr  = (U32)dev->dmaFrameBuffer + i * dev->frameSize;
			dmaDescriptor.dstAddr  = DMA_TX_REG;
			dmaDescriptor.descAttr = DMA_DESC_RM|DMA_DESC_NI|DMA_DESC_TS_4B /*|DMA_DESC_EOC*/
				                   |DMA_DESC_BLK_8B|DMA_DESC_ID|DMA_DESC_IE|DMA_DESC_ST;		
		}

		dmaDescriptor.dataLength = dev->frameSize;
		dmaDescriptor.reportAddr = (U32)(dev->dmaReportBuffer + i);
		dmaDescriptor.next       = NULL;

		err = GD_DMA_AddDescriptor(dev->dmaHandle, &dmaDescriptor);
		if(err != GD_OK)
		{
			return err;
		}		
	} 

	return GD_OK;	
}

static GERR dma_close(SUB_DEVICE_S *dev)
{
	if(dev == NULL)
	{
		return GD_ERR_BAD_PARAMETER;
	}

	////////////////////////////////
	//disable DMA
	////////////////////////////////	
	GD_DMA_Stop(dev->dmaHandle);
	GD_DMA_Close(dev->dmaHandle);

	return GD_OK;
}

GERR GD_I2S_RX_Open(GD_I2S_OPEN_PARAM_S *openParams)
{
	U32  frameNumber = 0;
	U32  frameSize = 0;
	GERR err = GD_OK;
	SUB_DEVICE_S *pDev = prxDev;

    if(openParams == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    if(openParams->frameSize <= 0)
    {
        return GD_ERR_BAD_PARAMETER;
    }
    if(i2sDev.devID == 0)
    {
        return GD_ERR_NOT_INITIALIZED;
    }
	if(pDev->subDevID == I2S_DEV_RX_ID)
	{
		return GD_ERR_ALREADY_OPEN;
	}

	frameSize   = openParams->frameSize;
	frameNumber = I2S_DEV_MAX_BUFF / frameSize;
	if(frameNumber < I2S_DEV_MIN_FRAME)
	{
		return GD_ERR_FEATURE_NOT_SUPPORTED;
	}
	if(frameNumber > I2S_DEV_MAX_FRAME)
	{
		frameNumber = I2S_DEV_MAX_FRAME;
	}	

	pDev->frameNumber     = frameNumber;
	pDev->frameSize       = frameSize;
	pDev->notifier        = openParams->notifier;
	pDev->subDevID        = I2S_DEV_RX_ID;
	pDev->state           = I2S_STATE_DISABLE;
	I2S_PRINTF("[GD_I2S]RX frame: number %d, size 0x%08X\n", frameNumber, frameSize);

	err = dma_open(pDev);
	if(err != GD_OK)
	{
		return err;
	}	

	GH_I2S_set_RxContr(0x00);
	GH_I2S_set_RxContr_rwi(1);
	if(i2sDev.master == GTRUE)
	{
		GH_I2S_set_RxContr_rwm(1);
	}
	else
	{	
		GH_I2S_set_RxContr_rwm(0);
	}		

    return GD_OK;
}

GERR GD_I2S_RX_Enable(void)
{
	SUB_DEVICE_S *pDev = prxDev;

	if(pDev->state==I2S_STATE_ENABLE || pDev->state==I2S_STATE_RUNNING)
	{
		return GD_ERR_I2S_BUSY;
	}		
	
    GH_I2S_set_MultipMode_en(0x1);
    GH_I2S_set_RxFifoGth(0x10);
    GH_I2S_set_Initreg_re(1);

	memset(pDev->dmaFrameBuffer, 0, pDev->frameNumber*pDev->frameSize);
	pDev->nextDescriptor = 0;
	pDev->rdPointer = pDev->dmaFrameBuffer;
	pDev->wrPointer = pDev->dmaFrameBuffer;	
	pDev->state = I2S_STATE_ENABLE;
	
	GD_DMA_Start(pDev->dmaHandle, 0);	
	pDev->state = I2S_STATE_RUNNING;

	return GD_OK;
}

GERR GD_I2S_RX_Disable(void)
{
	SUB_DEVICE_S *pDev = prxDev;

	GD_DMA_Stop(pDev->dmaHandle);
	pDev->state = I2S_STATE_DISABLE;

	return GD_OK;
}

GERR GD_I2S_RX_Read_Frame(U8 *data, U32 *length)
{
	U32 revFrameNumber = 0;
	SUB_DEVICE_S *pDev = prxDev;
	U8 *frameReadPointer = NULL; 
	U8 *frameWritePointer = NULL;
	
	if(data==NULL || length==NULL)
	{
		return GD_ERR_BAD_PARAMETER;
	}

	if(pDev->state == I2S_STATE_DISABLE)
	{
		return GD_ERR_FEATURE_NOT_SUPPORTED;
	}	

	if(pDev->event == I2S_EVENT_ALREADY_OVERFLOW)
	{
		// TODO: overflow.
	}	

	frameReadPointer = pDev->rdPointer; 
	frameWritePointer = pDev->wrPointer;

	if(frameWritePointer == frameReadPointer)
	{
		return GD_ERR_I2S_WAIT;
	}		

	memcpy(data, frameReadPointer, pDev->frameSize);

	pDev->rdPointer += pDev->frameSize;
	if(pDev->rdPointer >= pDev->rearPointer)
	{
		pDev->rdPointer = pDev->dmaFrameBuffer;
	}

	*length = pDev->frameSize;
    return GD_OK;
}


GERR GD_I2S_RX_Close(void)
{
	GERR err = GD_OK;
    SUB_DEVICE_S *pDev = prxDev;
	
    if(pDev->subDevID != I2S_DEV_RX_ID)
    {
        return GD_ERR_NOT_ALLOWED;
    }
	
	err = dma_close(pDev);
	if(err != GD_OK)
	{
		return err;
	}

	GD_TIMER_Delay(5);
	GD_I2S_RX_Disable();
    memset((void *)pDev, 0, sizeof(SUB_DEVICE_S));
	
    return GD_OK;
}


GERR GD_I2S_TX_Open(GD_I2S_OPEN_PARAM_S *openParams)
{
	U32  frameNumber = 0;
	U32  frameSize = 0;
	GERR err = GD_OK;
	SUB_DEVICE_S *pDev = ptxDev;

    if(openParams == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    if(openParams->frameSize <= 0)
    {
        return GD_ERR_BAD_PARAMETER;
    }
    if(i2sDev.devID == 0)
    {
        return GD_ERR_NOT_INITIALIZED;
    }
	if(pDev->subDevID == I2S_DEV_TX_ID)
	{
		return GD_ERR_ALREADY_OPEN;
	}

	frameSize   = openParams->frameSize;
	frameNumber = I2S_DEV_MAX_BUFF / frameSize;
	if(frameNumber < I2S_DEV_MIN_FRAME)
	{
		return GD_ERR_FEATURE_NOT_SUPPORTED;
	}
	if(frameNumber > I2S_DEV_MAX_FRAME)
	{
		frameNumber = I2S_DEV_MAX_FRAME;
	}	

	pDev->frameNumber     = frameNumber;
	pDev->frameSize       = frameSize;
	pDev->notifier        = openParams->notifier;
	pDev->subDevID        = I2S_DEV_TX_ID;
	pDev->state           = I2S_STATE_DISABLE;
	I2S_PRINTF("[GD_I2S]TX frame: number %d, size 0x%08X\n", frameNumber, frameSize);

	err = dma_open(pDev);
	if(err != GD_OK)
	{
		return err;
	}	

	GH_I2S_set_TxContr(0x00);
	GH_I2S_set_TxContr_twi(1);
	if(i2sDev.master == GTRUE)
	{
		GH_I2S_set_TxContr_twm(1);
	}
	else
	{	
		GH_I2S_set_TxContr_twm(0);
	}	

    return GD_OK;
}


GERR GD_I2S_TX_Enable(void)
{
	SUB_DEVICE_S *pDev = ptxDev;

	if(pDev->state==I2S_STATE_ENABLE || pDev->state==I2S_STATE_RUNNING)
	{
		return GD_ERR_I2S_BUSY;
	}	

    GH_I2S_set_MultipMode_en(0x1);
    GH_I2S_set_TxFifoLth(0x10);
    GH_I2S_set_Initreg_te(1);

	memset(pDev->dmaFrameBuffer, 0, pDev->frameNumber*pDev->frameSize);
	pDev->nextDescriptor = 0;
	pDev->rdPointer = pDev->dmaFrameBuffer;
	pDev->wrPointer = pDev->dmaFrameBuffer;
	pDev->state = I2S_STATE_ENABLE;

	return GD_OK;
}

GERR GD_I2S_TX_Disable(void)
{
	SUB_DEVICE_S *pDev = ptxDev;

	GD_DMA_Stop(pDev->dmaHandle);
	pDev->state = I2S_STATE_DISABLE;

	return GD_OK;
}

GERR GD_I2S_TX_Mute(void)
{
	GH_I2S_set_TxContr_mute(1);
	return GD_OK;
}

GERR GD_I2S_TX_Unmute(void)
{
	GH_I2S_set_TxContr_mute(0);
	return GD_OK;
}

GERR GD_I2S_TX_Write_Frame(U8 *data, U32 length)
{
	U32 revFrameNumber = 0;
	GERR err = GD_OK;
	SUB_DEVICE_S *pDev = ptxDev;
	U8 *frameReadPointer = pDev->rdPointer; 
	U8 *frameWritePointer = pDev->wrPointer;
	
	if(data == NULL || length <=0 || length > pDev->frameSize)
	{
		return GD_ERR_BAD_PARAMETER;
	}
	
	if(pDev->state == I2S_STATE_DISABLE)
	{
		return GD_ERR_FEATURE_NOT_SUPPORTED;
	}		

	if(((frameWritePointer-pDev->dmaFrameBuffer)/pDev->frameSize+1)%pDev->frameNumber == 
		(frameReadPointer-pDev->dmaFrameBuffer)/pDev->frameSize)
	{
		return GD_ERR_I2S_BUSY;
	}	

	memset(frameWritePointer, 0, pDev->frameSize);
	memcpy(frameWritePointer, data, length);

	pDev->wrPointer += pDev->frameSize;
	if(pDev->wrPointer >= pDev->rearPointer)
	{
		pDev->wrPointer = pDev->dmaFrameBuffer;
	}


	if(pDev->state==I2S_STATE_ENABLE || pDev->state==I2S_STATE_WAITING)
	{
		if(frameReadPointer <= frameWritePointer)
		{
			revFrameNumber = (frameWritePointer - frameReadPointer) / pDev->frameSize;
		}
		else
		{
			revFrameNumber = pDev->frameNumber - (frameReadPointer - frameWritePointer) / pDev->frameSize;
		}

		if(revFrameNumber>=I2S_BUF_MIN_FRAME && pDev->state==I2S_STATE_ENABLE)
		{
			err = GD_DMA_Start(pDev->dmaHandle, 0);
			if(err != GD_OK)
			{
				return err;
			}
			pDev->state = I2S_STATE_RUNNING;
		}
		if(revFrameNumber>=I2S_BUF_MIN_FRAME && pDev->state==I2S_STATE_WAITING)
		{
			GH_I2S_set_Initreg_te(1);
			pDev->state = I2S_STATE_RUNNING;
		}		
	}

	return GD_OK;
}


GERR GD_I2S_TX_Close(void)
{
	GERR err = GD_OK;
    SUB_DEVICE_S *pDev = prxDev;
	
    if(pDev->subDevID != I2S_DEV_RX_ID)
    {
        return GD_ERR_NOT_ALLOWED;
    }
	
	err = dma_close(pDev);
	if(err != GD_OK)
	{
		return err;
	}

	GD_TIMER_Delay(5);
	GD_I2S_RX_Disable();
    memset((void *)pDev, 0, sizeof(SUB_DEVICE_S));
	
    return GD_OK;
}

GERR GD_I2S_SetClock(GD_I2S_SPEED_E speed)
{
    U32 i2s_clk = 0;
    U32 clk_div = 0;
	U32 bit_num = 0;
	I2S_DEVICE_S *pDev = &i2sDev;
	
	if(pDev->wlen == GD_I2S_16BIT)
	{
		bit_num = 16;
	}
	else
	{
		bit_num = 32;
	}

	
    i2s_clk = GD_GET_I2S_ClkHz();
	clk_div = i2s_clk/(speed*bit_num)/2/2 - 1; /* div = (clk_au / (2*clk_i2s)) - 1 */
	GH_I2S_set_Clock_clk_div(clk_div); 

	pDev->speed = speed;
    return GD_OK;
}

GERR GD_I2S_SetWlen(GD_I2S_WLEN_E wlen)
{
    I2S_DEVICE_S *pDev = &i2sDev;
    
    GH_I2S_set_WlReg(wlen-1);	

	pDev->wlen = wlen;
    return GD_OK;
}

GERR GD_I2S_SetMode(GD_I2S_MODE_E mode)
{
    I2S_DEVICE_S *pDev = &i2sDev;
	
    GH_I2S_set_Mode_MODE(mode);

	pDev->mode = mode;
    return GD_OK;
}

GERR GD_I2S_SetChannel(GD_I2S_CHANNEL_E channel)
{
    I2S_DEVICE_S *pDev = &i2sDev;
    	
	GH_I2S_set_ChanSlect(channel);

	pDev->channel = channel;
    return GD_OK;
}

GERR GD_I2S_Init(GD_I2S_INIT_PARAM_S *initParams)
{
	I2S_DEVICE_S *pDev = &i2sDev;

    if(initParams == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }

	memset(pDev, 0, sizeof(I2S_DEVICE_S));
	pDev->master  = initParams->master;
    pDev->channel = initParams->channel;
    pDev->mode    = initParams->mode;
    pDev->wlen    = initParams->wlen;
    pDev->speed   = initParams->speed;
    pDev->devID   = I2S_DEV_ID;

	GH_I2S_set_Clock(0x00);
	GH_I2S_set_Clock_rsp(1);
	GH_I2S_set_Clock_tsp(1);
	if(pDev->master == GTRUE)
	{
		GH_I2S_set_Clock_ss(1);
		GH_I2S_set_Clock_soe(1);
		GH_I2S_set_Clock_woe(1);
	}	
	
	GD_I2S_SetMode(pDev->mode);
	GD_I2S_SetClock(pDev->speed);
	GD_I2S_SetWlen(pDev->wlen);
	GD_I2S_SetChannel(pDev->channel);
		
    return GD_OK;
}

GERR GD_I2S_Bind_Rx2Tx(void)
{
	I2S_DEVICE_S *pDev = &i2sDev;

	if(pDev->directMode == GTRUE)
	{
		return GD_OK;
	}

	GD_I2S_RX_Disable();
	GD_I2S_TX_Disable();
	GD_TIMER_Delay(10);
	GH_I2S_set_TxContr_loopback(1);	
	GH_I2S_set_Initreg_re(1);
	GH_I2S_set_Initreg_te(1);
	
	pDev->directMode  = GTRUE;
    return GD_OK;
}

GERR GD_I2S_Unbind_Rx2Tx(void)
{
	I2S_DEVICE_S *pDev = &i2sDev;
	
	if(pDev->directMode == GFALSE)
	{
		return GD_OK;
	}

	GH_I2S_set_TxContr_loopback(0);
	GD_I2S_RX_Enable();
	GD_I2S_TX_Enable();
	
	pDev->directMode  = GFALSE;
    return GD_OK;
}


GERR GD_I2S_Exit(void)
{
	memset(&i2sDev, 0, sizeof(I2S_DEVICE_S));
	
    return GD_OK;
}

