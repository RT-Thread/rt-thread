/******************************************************************************
**
** \file      gd_audio.c
**
** \brief     AUDIO.
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      
**
******************************************************************************/
#include <string.h>
#include <stdio.h>

#include "gh_audio.h"
#include "gh_i2s.h"

#include "gd_dma.h"
#include "gd_audio.h"
#include "gd_timer.h"

#define AUDIO_DEBUG

//#define AUDIO_CHECK_CACHE

#ifdef AUDIO_DEBUG
#define AUDIO_PRINTF(args...) printf(args)
#else
#define AUDIO_PRINTF(args...)
#endif

#define AUDIO_DEV_AI	0x00004941  //"AI"
#define AUDIO_DEV_AO	0x00004F41	//"AO"

#define AI_DATA_CHANNEL 1 //single channel
#define AO_DATA_CHANNEL 2 //AO must stereo channel data.

#define AUDIO_STATE_DISABLE  0
#define AUDIO_STATE_ENABLE   1
#define AUDIO_STATE_RUNNING  2
#define AUDIO_STATE_WAITING  3

#define AUDIO_DEV_MIN_FRAME  2    				 //minimum frame number which device supported.
#define AUDIO_DEV_MAX_FRAME (DMA_CHAN_MAX_DESC)	 //maximum frame number which device supported.
#define AUDIO_DEV_MAX_BUFF  (AUDIO_DEV_MAX_FRAME*512)
#define AUDIO_BUF_MIN_FRAME  2                    //data level  

typedef struct
{
	GD_AUDIO_FRAME_S *frameBuffer;
	GD_AUDIO_FRAME_S *frameRead;
	GD_AUDIO_FRAME_S *frameWrite;
	GD_AUDIO_FRAME_S *frameQueHead;
	GD_AUDIO_FRAME_S *frameQueRear;
	U32               frameSequence;
}AUDIO_FRAME_QUENE_S;

typedef struct
{
	U32                       audioDev;
    GD_AUDIO_BIT_WIDTH_E      bitWidth;
    GD_AUDIO_SOUND_MODE_E     soundMode;
	GD_AUDIO_SAMPLE_RATE_E    sampleRate;
    U32                       sampleNumber;
    U32                       frameNumber;		  //max saved frame number.
	U32						  frameSize;
	U8                        *dmaFrameBuffer;    
	U32                       *dmaReportBuffer;
	U32                       nextDescriptor;
	GD_HANDLE                 dmaHandle;
	U32                       event;
	U32                       state;
	U32                       counter;
	U32                       dmaState;
	AUDIO_FRAME_QUENE_S       frameQuene;
	GD_AUDIO_Notifier         notifier;
}AUDIO_DEV_INFO_S;

static volatile U32  aecFrameSeq = 0;  /*aecNumber*/
static volatile GBOOL bindMode  = GFALSE;
static AUDIO_DEV_INFO_S aiDevInfo __attribute__ ((section(".nocache_buffer")));
static AUDIO_DEV_INFO_S aoDevInfo __attribute__ ((section(".nocache_buffer")));
static U32 aiReportBuffer[AUDIO_DEV_MAX_FRAME] __attribute__ ((section(".nocache_buffer")));
static U32 aoReportBuffer[AUDIO_DEV_MAX_FRAME] __attribute__ ((section(".nocache_buffer")));
static U8 aiDmaBuffer[AUDIO_DEV_MAX_BUFF] __attribute__ ((aligned(DMA_BUFF_ADDR_ALIGN),section(".nocache_buffer")));
static U8 aoDmaBuffer[AUDIO_DEV_MAX_BUFF] __attribute__ ((aligned(DMA_BUFF_ADDR_ALIGN),section(".nocache_buffer")));
static GD_AUDIO_FRAME_S aiFrameBuffer[AUDIO_DEV_MAX_FRAME] __attribute__ ((section(".nocache_buffer")));
static GD_AUDIO_FRAME_S aoFrameBuffer[AUDIO_DEV_MAX_FRAME] __attribute__ ((section(".nocache_buffer")));
static U8 gainLevel = 0;
static U32 RecAIFrameNum = 0;
static U32 RecAOFrameNum = 0;
static void GD_AUDIO_AI_Set_RecFrameNum(U32 RecFrameNum);
static void GD_AUDIO_AO_Set_RecFrameNum(U32 RecFrameNum);

/************************************************************************************************
**                             GAIN & REG CONFIG MAP
**
** register          : ana_ctrl04
** config value    :  0x2f  0x2e  0x28  0x29  0x2a  0x2b  0x2c  0x2d   0x3f  0x3e  0x38  0x39  0x3a  0x3b  0x3c  0x3d
** micA1 bit[4]    : |                         0                                      |                            1                                   |
** micA2 bit[2:0] :   7      6        0      1        2       3      4       5       7      6        0       1      2        3      4      5
** micA1 gain(dB): |              -1.5dB      (NOT 13dB)                   |                0.5dB      (NOT 23dB)                    |
** micA2 gain(dB):  -6    -3       0      3        6       9      12      15     -6     -3       0       3      6        9     12     15
** total   gain(dB): -7.5  -4.5   -1.5   1.5     4.5    7.5    10.5   13.5  -5.5  -2.5   0.5    3.5    6.5     9.5   12.5  15.5
**************************************************************************************************/
static unsigned char gainMap[GAIN_LEVEL_MAX]= 
{
    /*ana_ctrl04   */        
       0x2f,         /* -8  dB */ 
       0x3f,         /* -6  dB */ 
       0x2e,         /* -4  dB */ 
       0x3e,         /* -3  dB */ 
       0x28,         /* -2  dB */ 
       0x38,         /*   0  dB */
       0x29,         /*   2  dB */
       0x39,         /*   4  dB */
       0x2a,         /*   5  dB */
       0x3a,         /*   7  dB */
       0x2b,         /*   8  dB */
       0x3b,         /*  10  dB */
       0x2c,         /*  11  dB */
       0x3c,         /*  13  dB */
       0x2d,         /*  14  dB */
       0x3d,         /* 16  dB */ 
};

static void set_aec_frame_seq(AUDIO_FRAME_QUENE_S *frameQuene)
{
    GD_AUDIO_FRAME_S *ptr_read;

    ptr_read = frameQuene->frameRead;
    if(ptr_read + 1 >= frameQuene->frameQueRear) {
        ptr_read = frameQuene->frameQueHead;
        aecFrameSeq = ptr_read->aecSeq;
        ptr_read->aecSeq = 0;
    }
    else{
        aecFrameSeq = (ptr_read + 1)->aecSeq;
        (ptr_read + 1)->aecSeq = 0;
    }
}

static void get_aec_frame_seq(unsigned int *aecSeq)
{
    *aecSeq = aecFrameSeq;
    aecFrameSeq = 0;
}

static void ai_int_handler(void)
{
	U32 curDescriptor = 0;
	U32 dmaStatus     = 0;
	U32 revFrameNumber = 0;
	GD_AUDIO_FRAME_S * frameReadPointer = 0;
	GD_AUDIO_FRAME_S * frameWritePointer = 0;	
	AUDIO_DEV_INFO_S * pDev = &aiDevInfo;
	AUDIO_FRAME_QUENE_S *pFrameQue = &pDev->frameQuene;	
	
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
		pFrameQue->frameWrite->timeStamp = GD_TIMER_ReadTimerStamp();
		pFrameQue->frameWrite->seqNumber = pFrameQue->frameSequence;
		//pFrameQue->frameWrite->aecSeq	 = aecNumber;
        get_aec_frame_seq((unsigned int*)&pFrameQue->frameWrite->aecSeq);
		pFrameQue->frameSequence++;

		if(++pFrameQue->frameWrite >= pFrameQue->frameQueRear)
		{
			pFrameQue->frameWrite = pFrameQue->frameQueHead;
		}

		pDev->dmaReportBuffer[curDescriptor] &= ~(DMA_CHAN_STATE_OD|DMA_CHAN_STATE_DN);
		
		if(pDev->notifier != NULL)
		{
			pDev->notifier(AUDIO_EVENT_FRAME);
		}
	}
	else /* not expected interrupt */
	{
		pDev->event = AUDIO_EVENT_UNDEFINED;		  //for debug only.
		pDev->notifier(AUDIO_EVENT_UNDEFINED);
	}


	frameReadPointer  = pFrameQue->frameRead;
	frameWritePointer = pFrameQue->frameWrite;
	if(frameReadPointer <= frameWritePointer)
	{
		revFrameNumber = frameWritePointer - frameReadPointer;
	}
	else
	{
		revFrameNumber = pDev->frameNumber -(frameReadPointer - frameWritePointer);
	}
    
    GD_AUDIO_AI_Set_RecFrameNum(revFrameNumber); //set ai Frame Num
	if(revFrameNumber >= pDev->frameNumber - AUDIO_BUF_MIN_FRAME)
	{
		if(pDev->notifier != NULL)
		{
			pDev->notifier(AUDIO_EVENT_WILL_OVERFLOW);
		}
		pDev->event = AUDIO_EVENT_WILL_OVERFLOW;
	}
	if(revFrameNumber == 0)
	{
		if(pDev->notifier != NULL)
		{
			pDev->notifier(AUDIO_EVENT_ALREADY_OVERFLOW);
		}
		pDev->event = AUDIO_EVENT_ALREADY_OVERFLOW;
	}		

}

static void ao_int_handler(void)
{
	U32 curDescriptor = 0;
	U32 dmaStatus     = 0;
	U32 revFrameNumber = 0;
	GD_AUDIO_FRAME_S * frameReadPointer = 0;
	GD_AUDIO_FRAME_S * frameWritePointer = 0;	
	AUDIO_DEV_INFO_S * pDev = &aoDevInfo;
	AUDIO_FRAME_QUENE_S *pFrameQue = &pDev->frameQuene;
	
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

	//aecNumber = pFrameQue->frameRead->aecSeq;
    set_aec_frame_seq(pFrameQue);

	if(dmaStatus & DMA_CHAN_STATE_OD) /* DO NOT verify this field, report buffer will not refresh after DMA int sometimes. */
	{
	
		if(++pFrameQue->frameRead >= pFrameQue->frameQueRear)
		{
			pFrameQue->frameRead = pFrameQue->frameQueHead;
		}

		pDev->dmaReportBuffer[curDescriptor] &= ~(DMA_CHAN_STATE_OD|DMA_CHAN_STATE_DN);

		if(pDev->notifier != NULL)
		{
			pDev->notifier(AUDIO_EVENT_FRAME);
		}
	}		
	else /* not expected interrupt */
	{
		pDev->event = AUDIO_EVENT_UNDEFINED;         //for debug only.
		pDev->notifier(AUDIO_EVENT_UNDEFINED);
	}


	frameReadPointer  = pFrameQue->frameRead;
	frameWritePointer = pFrameQue->frameWrite;
	if(frameReadPointer <= frameWritePointer)
	{
		revFrameNumber = frameWritePointer - frameReadPointer;
	}
	else
	{
		revFrameNumber = pDev->frameNumber -(frameReadPointer - frameWritePointer);
	}

    GD_AUDIO_AO_Set_RecFrameNum(pDev->frameNumber - revFrameNumber); //set ao valid Frame buffer 
	if(revFrameNumber <= 0)
	{
		if(pDev->notifier != NULL)
		{
			pDev->notifier(AUDIO_EVENT_ALREADY_UNDERFLOW);
		}
		pDev->event = AUDIO_EVENT_ALREADY_UNDERFLOW;

		GH_AUDIO_set_FIFO_CTRL_TX_FIFO_ENABLE(0);
		pDev->state = AUDIO_STATE_WAITING;
	}		
	else if(revFrameNumber <= AUDIO_BUF_MIN_FRAME)
	{
		if(pDev->notifier != NULL)
		{
			pDev->notifier(AUDIO_EVENT_WILL_UNDERFLOW);
		}
		pDev->event = AUDIO_EVENT_WILL_UNDERFLOW;
	}
}


static GERR dma_open(AUDIO_DEV_INFO_S *dev)
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
	
	if(dev->audioDev == AUDIO_DEV_AI)
	{
		dev->dmaReportBuffer = aiReportBuffer;
		dev->dmaFrameBuffer  = aiDmaBuffer;
		dmaOpenParam.channel = DMA_CHAN_AUDIO_RX;
		dmaOpenParam.mode    = DMA_MODE_DESCRIPTOR;
		dmaOpenParam.intNotifier = ai_int_handler;
	}
	else /* AUDIO_DEV_AO */
	{
		dev->dmaReportBuffer = aoReportBuffer;
		dev->dmaFrameBuffer  = aoDmaBuffer;
		dmaOpenParam.channel = DMA_CHAN_AUDIO_TX;
		dmaOpenParam.mode	 = DMA_MODE_DESCRIPTOR;
		dmaOpenParam.intNotifier = ao_int_handler;
	}
	AUDIO_PRINTF("[GD_AUDIO]dmaFrameBuffer:0x%08X\n", dev->dmaFrameBuffer);
	
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
		if(dev->audioDev == AUDIO_DEV_AI)
		{
			dmaDescriptor.srcAddr  = DMA_RX_REG;
			dmaDescriptor.dstAddr  = (U32)dev->dmaFrameBuffer + i * dev->frameSize;
			dmaDescriptor.descAttr = DMA_DESC_WM|DMA_DESC_NI|DMA_DESC_TS_2B /*|DMA_DESC_EOC*/
				                   |DMA_DESC_BLK_8B|DMA_DESC_ID|DMA_DESC_IE|DMA_DESC_ST;
		}
		else /* AUDIO_DEV_AO */
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

static GERR dma_close(AUDIO_DEV_INFO_S *dev)
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

static GERR frame_open(AUDIO_DEV_INFO_S *dev)
{
	U32 i = 0;
	AUDIO_FRAME_QUENE_S *pQue = &dev->frameQuene;

	if(dev==NULL || dev->frameNumber<=0)
	{
		return GD_ERR_BAD_PARAMETER;
	}

	if(dev->audioDev == AUDIO_DEV_AI)
	{
		pQue->frameBuffer = aiFrameBuffer;
	}
	else /* AUDIO_DEV_AO */
	{
		pQue->frameBuffer = aoFrameBuffer;
	}

	for(i=0; i<dev->frameNumber; i++)
	{
		pQue->frameBuffer[i].frameAddr = (U32)dev->dmaFrameBuffer+dev->frameSize*i;
		pQue->frameBuffer[i].frameSize = dev->frameSize;
		pQue->frameBuffer[i].bitWidth  = dev->bitWidth;
		pQue->frameBuffer[i].soundMode = dev->soundMode;
		pQue->frameBuffer[i].sampleRate= dev->sampleRate;
	}

	pQue->frameQueHead = pQue->frameBuffer;
	pQue->frameQueRear = pQue->frameBuffer + dev->frameNumber;
	pQue->frameRead = pQue->frameQueHead;
	pQue->frameWrite= pQue->frameQueHead;
	pQue->frameSequence = 0;

	return GD_OK;
}

static GERR frame_close(AUDIO_DEV_INFO_S *dev)
{
	AUDIO_FRAME_QUENE_S *pQue = &dev->frameQuene;
	
	if(dev == NULL)
	{
		return GD_ERR_BAD_PARAMETER;
	}

	pQue->frameBuffer  = NULL;
	pQue->frameQueHead = NULL;
	pQue->frameQueRear = NULL;
	pQue->frameRead    = NULL;
	pQue->frameWrite   = NULL;
	pQue->frameSequence = 0;

	return GD_OK;
}

static void audio_init(void)
{
	/* DMA select */
    GH_AUDIO_set_AHB_GENERAL1(0x01);

	/* analog config */
	GH_AUDIO_set_ANALOG_CTRL00(0x8040);
	GH_AUDIO_set_ANALOG_CTRL03(0x4004);
	GH_AUDIO_set_ANALOG_CTRL04(0x2000);
	GH_AUDIO_set_ANALOG_CTRL06(0x0004);
	GH_AUDIO_set_ANALOG_CTRL11(0x0000);
	GH_AUDIO_set_ANALOG_CTRL13(0x6000);
	GD_TIMER_Delay(1);
	GH_AUDIO_set_ANALOG_CTRL00(0x8040);
	GH_AUDIO_set_ANALOG_CTRL03(0x401C);  
	GH_AUDIO_set_ANALOG_CTRL04(0x233A);	 
	GH_AUDIO_set_ANALOG_CTRL05(0x280C);
	GH_AUDIO_set_ANALOG_CTRL06(0x8407);
	GH_AUDIO_set_ANALOG_CTRL07(0x3802);
	GH_AUDIO_set_ANALOG_CTRL08(0x00F8);
	GH_AUDIO_set_ANALOG_CTRL09(0x0000);
	GH_AUDIO_set_ANALOG_CTRL10(0xC0C0);
	GH_AUDIO_set_ANALOG_CTRL11(0x9080);
	GH_AUDIO_set_ANALOG_CTRL12(0x0000);
	GH_AUDIO_set_ANALOG_CTRL13(0x6000);

	/* digital config */
	GH_AUDIO_set_MMP_DPGA_CFG1(0, 0x5);  //MMP1_DPGA_CFG1
	GH_AUDIO_set_MMP_DPGA_CFG1(1, 0x5);  //MMP2_DPGA_CFG1
	GH_AUDIO_set_SYS_RST_CTRL0(0xE000);
	GH_AUDIO_set_SYS_RST_CTRL0(0);
	GH_AUDIO_set_AUDIOBAND_CTRL0(2);
	GH_AUDIO_set_CKG_CTRL0(3);
	GH_AUDIO_set_TIMING_CTRL0(0x33F);
	GH_AUDIO_set_TIMING_CTRL1(0xF3E);
	GH_AUDIO_set_AUDIOBAND_CTRL2(0xFAAF);
	GH_AUDIO_set_SDM_CTRL0(0x15);
	GH_AUDIO_set_MMP_DPGA_CFG1(0, 0);  //MMP1_DPGA_CFG1
	GH_AUDIO_set_MMP_DPGA_CFG1(1, 0);  //MMP2_DPGA_CFG1
	GH_AUDIO_set_TIMING_CTRL0(0x23F);
	GH_AUDIO_set_MIX_CTRL0(0x2500);	   
	GH_AUDIO_set_TIMING_CTRL1(0x23E);
	GH_AUDIO_set_AUDIOBAND_CTRL1(0xEA82);
	GH_AUDIO_set_AUDIOBAND_CTRL2(0xAAAF);
	GH_AUDIO_set_ANALOG_CTRL02(8);
	
	GH_AUDIO_set_NF_SYNTH_1_NF_H(0x000000BB);
	GH_AUDIO_set_NF_SYNTH_1_NF_L(0x00008000);
    GD_TIMER_Delay(1);
	GH_AUDIO_set_NF_SYNTH_1_NF_H(0x0000C0BB);
    GD_TIMER_Delay(1);
	GH_AUDIO_set_NF_SYNTH_1_NF_H(0x000000BB);
	GH_AUDIO_set_NF_SYNTH_2_NF_H(0x000000c0);
	GH_AUDIO_set_NF_SYNTH_2_NF_L(0x00000000);
    GD_TIMER_Delay(1);
	GH_AUDIO_set_NF_SYNTH_2_NF_H(0x0000c0c0);
    GD_TIMER_Delay(1);
	GH_AUDIO_set_NF_SYNTH_2_NF_H(0x0000c0);
	GH_AUDIO_set_FIFO_TH_CTRL0(0x402);
	GH_AUDIO_set_FIFO_CTRL(0);
//	GH_AUDIO_set_FIFO_CTRL(0x8888);
}
#ifdef AUDIO_CHECK_CACHE
void audio_cache_config(void)
{
	U32 reg;
    __asm__ __volatile__ (
        " mrc p15, 0, %0, c1, c0, 0 \n"
        : "=r" (reg)
        :
        : "memory");
	AUDIO_PRINTF("cache 0x%X\n",reg);
}
#endif

static GERR audio_ai_set_attr(GD_AUDIO_ATTR_S *pattr)
{
    switch(pattr->sampleRate)
    {
	    case AUDIO_SAMPLE_RATE_8000:
			GH_AUDIO_set_TIMING_CTRL0(0x003F);
	        break;
	    case AUDIO_SAMPLE_RATE_16000:
	        GH_AUDIO_set_TIMING_CTRL0(0x013F);
	        break;
	    case AUDIO_SAMPLE_RATE_32000:
	        GH_AUDIO_set_TIMING_CTRL0(0x023F);
	        break;
	    default:
	        return GD_ERR_BAD_PARAMETER;
    }

    switch(pattr->soundMode)
    {
	    case AUDIO_SOUND_MODE_SINGLE:
			GH_AUDIO_set_MIX_CTRL0_SEL_DEC2_DOUT(0);
	        break;
	    case AUDIO_SOUND_MODE_STEREO:
	    case AUDIO_SOUND_MODE_LEFT:
	    case AUDIO_SOUND_MODE_RIGHT:
	    case AUDIO_SOUND_MODE_MONO:
	        return GD_ERR_AUDIO_NOT_SUPPORTED;
	    default:
	        return GD_ERR_BAD_PARAMETER;
    }
	
    return GD_OK;
}

static GERR audio_ao_set_attr(GD_AUDIO_ATTR_S *pattr)
{
    switch(pattr->sampleRate)
    {
	    case AUDIO_SAMPLE_RATE_8000:
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x000002EE);
			GH_AUDIO_set_NF_SYNTH_1_NF_L(0x00000000);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x0000C2EE);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x000002EE);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x00000300);
			GH_AUDIO_set_NF_SYNTH_2_NF_L(0x00000000);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x0000C300);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x00000300);			
	        break;
	    case AUDIO_SAMPLE_RATE_11025:
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x00000220);
			GH_AUDIO_set_NF_SYNTH_1_NF_L(0x000037BA);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x0000C220);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x00000220);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x0000022D);
			GH_AUDIO_set_NF_SYNTH_2_NF_L(0x00004766);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x0000C22D);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x0000022D);			
	        break;
	    case AUDIO_SAMPLE_RATE_12000:
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x000001F4);
			GH_AUDIO_set_NF_SYNTH_1_NF_L(0x00000000);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x0000C1F4);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x000001F4);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x00000200);
			GH_AUDIO_set_NF_SYNTH_2_NF_L(0x00000000);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x0000C200);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x00000200);			
	        break;
	    case AUDIO_SAMPLE_RATE_16000:
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x00000177);
			GH_AUDIO_set_NF_SYNTH_1_NF_L(0x00000000);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x0000C177);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x00000177);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x00000180);
			GH_AUDIO_set_NF_SYNTH_2_NF_L(0x00000000);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x0000C180);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x00000180);			
	        break;
	    case AUDIO_SAMPLE_RATE_22050:
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x00000110);
			GH_AUDIO_set_NF_SYNTH_1_NF_L(0x00001BDD);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x0000C110);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x00000110);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x00000116);
			GH_AUDIO_set_NF_SYNTH_2_NF_L(0x0000A3B3);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x0000C116);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x00000116);			
	        break;
	    case AUDIO_SAMPLE_RATE_24000:
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x000000FA);
			GH_AUDIO_set_NF_SYNTH_1_NF_L(0x00000000);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x0000C0FA);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x000000FA);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x00000100);
			GH_AUDIO_set_NF_SYNTH_2_NF_L(0x00000000);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x0000C100);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x00000100);			
	        break;
	    case AUDIO_SAMPLE_RATE_32000:
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x000000BB);
			GH_AUDIO_set_NF_SYNTH_1_NF_L(0x00008000);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x0000C0BB);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x000000BB);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x000000C0);
			GH_AUDIO_set_NF_SYNTH_2_NF_L(0x00000000);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x0000C0C0);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x000000C0);			
	        break;
	    case AUDIO_SAMPLE_RATE_44100:
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x00000088);
			GH_AUDIO_set_NF_SYNTH_1_NF_L(0x00000DEF);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x0000C088);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x00000088);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x0000008B);
			GH_AUDIO_set_NF_SYNTH_2_NF_L(0x000051DA);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x0000C08B);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x0000008B);			
	        break;
	    case AUDIO_SAMPLE_RATE_48000:
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x0000007D);
			GH_AUDIO_set_NF_SYNTH_1_NF_L(0x00000000);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x0000C07D);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_1_NF_H(0x0000007D);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x00000080);
			GH_AUDIO_set_NF_SYNTH_2_NF_L(0x00000000);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x0000C080);
		    GD_TIMER_Delay(1);
			GH_AUDIO_set_NF_SYNTH_2_NF_H(0x00000080);			
	        break;
	    default:
	        return GD_ERR_BAD_PARAMETER;
    }

    switch(pattr->soundMode)
    {
	    case AUDIO_SOUND_MODE_LEFT:
			GH_AUDIO_set_MIX_CTRL0_CH1_MUX_SEL(0);
			GH_AUDIO_set_MIX_CTRL0_CH2_MUX_SEL(3);
	        break;
	    case AUDIO_SOUND_MODE_RIGHT:
			GH_AUDIO_set_MIX_CTRL0_CH1_MUX_SEL(3);
			GH_AUDIO_set_MIX_CTRL0_CH2_MUX_SEL(0);
	        break;
	    case AUDIO_SOUND_MODE_STEREO:
	    case AUDIO_SOUND_MODE_MONO:
			GH_AUDIO_set_MIX_CTRL0_CH1_MUX_SEL(0);
			GH_AUDIO_set_MIX_CTRL0_CH2_MUX_SEL(0);
	        break;
	    case AUDIO_SOUND_MODE_SINGLE:
			GH_AUDIO_set_MIX_CTRL0_CH1_MUX_SEL(0);
			GH_AUDIO_set_MIX_CTRL0_CH2_MUX_SEL(3);
	        break;
	    default:
	        return GD_ERR_BAD_PARAMETER;
    }

    return GD_OK;
}

static void audio_ao_set_volume(int vol)
{
	U16 volume = 0;
	
    volume = vol<<8|vol;
	GH_AUDIO_set_PGA_DPGA_CFG(volume);
}

GERR GD_AUDIO_Init(void)
{
	GERR err = GD_OK;
	
    audio_init();
	audio_ao_set_volume(VOL_LEVEL_8);

	memset(&aiDevInfo, 0, sizeof(AUDIO_DEV_INFO_S));
	memset(&aoDevInfo, 0, sizeof(AUDIO_DEV_INFO_S));

#ifdef AUDIO_CHECK_CACHE
	audio_cache_config();
#endif
    return GD_OK;
}

GERR GD_AUDIO_Exit(void)
{
    return GD_OK;
}

GERR GD_AUDIO_Bind_Ai2Ao(void)
{
	if(bindMode == GTRUE)
	{
		return GD_OK;
	}

	GD_DMA_Stop(aiDevInfo.dmaHandle);	
	GD_DMA_Stop(aoDevInfo.dmaHandle);
	
	GD_TIMER_Delay(10);
	GH_AUDIO_set_MIX_CTRL0(0x6518);
	
	bindMode  = GTRUE;
    return GD_OK;
}

GERR GD_AUDIO_Unbind_Ai2Ao(void)
{
	if(bindMode == GFALSE)
	{
		return GD_OK;
	}

	GH_AUDIO_set_MIX_CTRL0(0x2500);

	GD_DMA_Start(aiDevInfo.dmaHandle, 0);	
	GD_DMA_Start(aoDevInfo.dmaHandle, 0);

	bindMode  = GFALSE;
    return GD_OK;
}

GERR GD_AUDIO_AI_Open(GD_AUDIO_OPEN_PARAM_S *openParamPtr)
{
	GERR err = GD_OK;
	U32  frameNumber = 0, frameSize = 0;
	GD_AUDIO_ATTR_S attr;
	AUDIO_DEV_INFO_S *pDev = &aiDevInfo;

	if(pDev->audioDev == AUDIO_DEV_AI)
	{
		return GD_ERR_ALREADY_OPEN;
	}
	if(openParamPtr->sampleNumber<=0)
	{
		return GD_ERR_BAD_PARAMETER;
	}

	frameSize = openParamPtr->sampleNumber * (openParamPtr->bitWidth>>3) * AI_DATA_CHANNEL;
	if((frameSize % DMA_BUFF_ADDR_ALIGN) != 0)
	{
		return GD_ERR_FEATURE_NOT_SUPPORTED;
	}

	frameNumber = AUDIO_DEV_MAX_BUFF / frameSize;
	if(frameNumber < AUDIO_DEV_MIN_FRAME)
	{
		return GD_ERR_FEATURE_NOT_SUPPORTED;
	}
	if(frameNumber > AUDIO_DEV_MAX_FRAME)
	{
		frameNumber = AUDIO_DEV_MAX_FRAME;
	}		
	
	pDev->audioDev     = AUDIO_DEV_AI;
	pDev->state        = AUDIO_STATE_DISABLE;
	pDev->bitWidth     = openParamPtr->bitWidth;
	pDev->sampleRate   = openParamPtr->sampleRate;
	pDev->sampleNumber = openParamPtr->sampleNumber;
	pDev->soundMode    = openParamPtr->soundMode;
	pDev->frameNumber  = frameNumber;
	pDev->frameSize    = frameSize;
	pDev->notifier     = openParamPtr->notifier;

	err = dma_open(pDev);
	if(err != GD_OK)
	{
		return err;
	}

	err = frame_open(pDev);
	if(err != GD_OK)
	{
		return err;
	}

	attr.sampleRate = openParamPtr->sampleRate;
	attr.soundMode  = openParamPtr->soundMode;
	err = audio_ai_set_attr(&attr);
	if(err != GD_OK)
	{
		return err;
	}

    return GD_OK;
}

GERR GD_AUDIO_AI_Close(void)
{
	GERR err = GD_OK;
	
	err = dma_close(&aiDevInfo);
	if(err != GD_OK)
	{
		return err;
	}

	err = frame_close(&aiDevInfo);
	if(err != GD_OK)
	{
		return err;
	}	

    return GD_OK;
}


GERR GD_AUDIO_AI_Enable(void)
{
	GERR err = GD_OK;
	AUDIO_DEV_INFO_S *pDev = &aiDevInfo;

	if(pDev->state==AUDIO_STATE_ENABLE || pDev->state==AUDIO_STATE_RUNNING)
	{
		return GD_ERR_AUDIO_DEV_BUSY;
	}	

	GH_AUDIO_set_FIFO_CTRL_RX_FIFO_STATUS_CLR(0);
	GH_AUDIO_set_FIFO_CTRL_RX_FIFO_INT_EN(8);
	GH_AUDIO_set_FIFO_CTRL_RX_FIFO_ENABLE(1);

	memset(pDev->dmaFrameBuffer, 0, pDev->frameNumber*pDev->frameSize);
	pDev->nextDescriptor = 0;
	pDev->frameQuene.frameRead = pDev->frameQuene.frameQueHead;
	pDev->frameQuene.frameWrite= pDev->frameQuene.frameQueHead;	
	pDev->state = AUDIO_STATE_ENABLE;
	
	err = GD_DMA_Start(pDev->dmaHandle, 0);
	if(err != GD_OK)
	{
		return err;
	}

	pDev->state = AUDIO_STATE_RUNNING;
	
    return GD_OK;
}

GERR GD_AUDIO_AI_Disable(void)
{
	GERR err = GD_OK;
	
	err = GD_DMA_Stop(aiDevInfo.dmaHandle);
	if(err != GD_OK)
	{
		return err;
	}

	aiDevInfo.state = AUDIO_STATE_DISABLE;
    return GD_OK;
}

GERR GD_AUDIO_AI_Read_Frame(GD_AUDIO_FRAME_S *frame)
{
	U32 revFrameNumber = 0;
	AUDIO_DEV_INFO_S    *pDev = &aiDevInfo;
	AUDIO_FRAME_QUENE_S *pFrameQue = &pDev->frameQuene;
	GD_AUDIO_FRAME_S    *frameReadPointer = NULL; 
	GD_AUDIO_FRAME_S    *frameWritePointer = NULL;
	
	if(frame == NULL)
	{
		return GD_ERR_BAD_PARAMETER;
	}

	if(pDev->state == AUDIO_STATE_DISABLE)
	{
		return GD_ERR_AUDIO_NOT_SUPPORTED;
	}	

	if(pDev->event == AUDIO_EVENT_ALREADY_OVERFLOW)
	{
		// TODO: overflow.
	}	
/*
	if(frameReadPointer <= frameWritePointer)
	{
		revFrameNumber = frameWritePointer - frameReadPointer;
	}
	else
	{
		revFrameNumber = pDev->frameNumber -(frameReadPointer - frameWritePointer);
	}

	if(revFrameNumber <= 0)
	{
		return GD_ERR_AUDIO_DEV_WAIT;
	}	
*/

	frameReadPointer = pFrameQue->frameRead; 
	frameWritePointer = pFrameQue->frameWrite;

	if(frameWritePointer == frameReadPointer)
	{
		return GD_ERR_AUDIO_DEV_WAIT;
	}		

	memcpy(frame, pFrameQue->frameRead, sizeof(GD_AUDIO_FRAME_S));

	if(++pFrameQue->frameRead>= pFrameQue->frameQueRear)
	{
		pFrameQue->frameRead = pFrameQue->frameQueHead;
	}
	
    return GD_OK;
}

static void GD_AUDIO_AI_Set_RecFrameNum(U32 RecFrameNum)
{
	RecAIFrameNum = RecFrameNum;
}

U32 GD_AUDIO_AI_Get_RecFrameNum(void)
{
	return RecAIFrameNum;
}

GERR GD_AUDIO_AI_Set_Attr(GD_AUDIO_ATTR_S *pattr)
{
	GERR err = GD_OK;

	err = audio_ai_set_attr(pattr);
    if(err == GD_OK)
	{
		aiDevInfo.sampleRate = pattr->sampleRate;
		aiDevInfo.soundMode  = pattr->soundMode;
	}

    return err;
}

GERR GD_AUDIO_AI_Get_Attr(GD_AUDIO_ATTR_S *pattr)
{
	pattr->sampleRate = aiDevInfo.sampleRate;
	pattr->soundMode  = aiDevInfo.soundMode;
    return GD_OK;
}

GERR GD_AUDIO_AI_Set_Gain(GD_AUDIO_GAIN_E gain)
{
	U16 value = 0;
	
	value = GH_AUDIO_get_ANALOG_CTRL04();
	GH_AUDIO_set_ANALOG_CTRL04((value&(~0x00FF))|gainMap[gain]);

    gainLevel = gain;
    return GD_OK;
}

GD_AUDIO_GAIN_E GD_AUDIO_AI_Get_Gain(void)
{
    return gainLevel;
}

GERR GD_AUDIO_AO_Open(GD_AUDIO_OPEN_PARAM_S *openParamPtr)
{
	GERR err = GD_OK;
	U32  frameNumber = 0, frameSize = 0;
	GD_AUDIO_ATTR_S attr;
	AUDIO_DEV_INFO_S *pDev = &aoDevInfo;

	if(pDev->audioDev == AUDIO_DEV_AO)
	{
		return GD_ERR_ALREADY_OPEN;
	}
	if(openParamPtr->sampleNumber<=0)
	{
		return GD_ERR_BAD_PARAMETER;
	}	

	frameSize = openParamPtr->sampleNumber * (openParamPtr->bitWidth>>3) * AO_DATA_CHANNEL;
	if((frameSize % DMA_BUFF_ADDR_ALIGN) != 0)
	{
		return GD_ERR_FEATURE_NOT_SUPPORTED;
	}

	frameNumber = AUDIO_DEV_MAX_BUFF / frameSize;
	if(frameNumber < AUDIO_DEV_MIN_FRAME)
	{
		return GD_ERR_FEATURE_NOT_SUPPORTED;
	}
	if(frameNumber > AUDIO_DEV_MAX_FRAME)
	{
		frameNumber = AUDIO_DEV_MAX_FRAME;
	}
	
	pDev->audioDev     = AUDIO_DEV_AO;
	pDev->state        = AUDIO_STATE_DISABLE;
	pDev->bitWidth     = openParamPtr->bitWidth;
	pDev->sampleRate   = openParamPtr->sampleRate;
	pDev->sampleNumber = openParamPtr->sampleNumber;
	pDev->soundMode    = openParamPtr->soundMode;
	pDev->frameNumber  = frameNumber;
	pDev->frameSize    = frameSize;
	pDev->notifier     = openParamPtr->notifier;

	err = dma_open(pDev);
	if(err != GD_OK)
	{
		return err;
	}

	err = frame_open(pDev);
	if(err != GD_OK)
	{
		return err;
	}	

	attr.sampleRate = openParamPtr->sampleRate;
	attr.soundMode  = openParamPtr->soundMode;
	err = audio_ao_set_attr(&attr);
	if(err != GD_OK)
	{
		return err;
	}

    return GD_OK;
}

GERR GD_AUDIO_AO_Close(void)
{
	GERR err = GD_OK;
	
	err = dma_close(&aoDevInfo);
	if(err != GD_OK)
	{
		return err;
	}

	err = frame_close(&aoDevInfo);
	if(err != GD_OK)
	{
		return err;
	}	

    return GD_OK;
}

GERR GD_AUDIO_AO_Enable(void)
{
	AUDIO_DEV_INFO_S	*pDev = &aoDevInfo;

	if(pDev->state==AUDIO_STATE_ENABLE || pDev->state==AUDIO_STATE_RUNNING)
	{
		return GD_ERR_AUDIO_DEV_BUSY;
	}

	GH_AUDIO_set_FIFO_CTRL_TX_FIFO_STATUS_CLR(0);
	GH_AUDIO_set_FIFO_CTRL_TX_FIFO_INT_EN(8);
	GH_AUDIO_set_FIFO_CTRL_TX_FIFO_ENABLE(1);			

	memset(pDev->dmaFrameBuffer, 0, pDev->frameNumber*pDev->frameSize);
	pDev->nextDescriptor = 0;
	pDev->frameQuene.frameRead = pDev->frameQuene.frameQueHead;
	pDev->frameQuene.frameWrite= pDev->frameQuene.frameQueHead;
	pDev->state = AUDIO_STATE_ENABLE;
	
    return GD_OK;
}

GERR GD_AUDIO_AO_Disable(void)
{
	GERR err = GD_OK;
	
	err = GD_DMA_Stop(aoDevInfo.dmaHandle);
	if(err != GD_OK)
	{
		return err;
	}

	aoDevInfo.state = AUDIO_STATE_DISABLE;	
    return GD_OK;
}

GERR GD_AUDIO_AO_Write_Frame(GD_AUDIO_FRAME_S *frame)
{
	U32 revFrameNumber = 0;
	GERR err = GD_OK;
	AUDIO_DEV_INFO_S	*pDev = &aoDevInfo;
	AUDIO_FRAME_QUENE_S *pFrameQue = &pDev->frameQuene;
	GD_AUDIO_FRAME_S	*frameReadPointer = pFrameQue->frameRead; 
	GD_AUDIO_FRAME_S	*frameWritePointer = pFrameQue->frameWrite;
	
	if(frame == NULL)
	{
		return GD_ERR_BAD_PARAMETER;
	}
	
	if(pDev->state == AUDIO_STATE_DISABLE)
	{
		return GD_ERR_AUDIO_NOT_SUPPORTED;
	}		

	if((frameWritePointer-pFrameQue->frameQueHead+1)%pDev->frameNumber == frameReadPointer-pFrameQue->frameQueHead)
	{
		return GD_ERR_AUDIO_DEV_BUSY;
	}	

	pFrameQue->frameWrite->aecSeq = frame->aecSeq;
	memcpy(frame, pFrameQue->frameWrite, sizeof(GD_AUDIO_FRAME_S));

	if(++pFrameQue->frameWrite >= pFrameQue->frameQueRear)
	{
		pFrameQue->frameWrite = pFrameQue->frameQueHead;
	}

	if(pDev->state==AUDIO_STATE_ENABLE || pDev->state==AUDIO_STATE_WAITING)
	{
		if(frameReadPointer <= frameWritePointer)
		{
			revFrameNumber = frameWritePointer - frameReadPointer;
		}
		else
		{
			revFrameNumber = pDev->frameNumber - (frameReadPointer - frameWritePointer);
		}

		if(revFrameNumber>=AUDIO_BUF_MIN_FRAME && pDev->state==AUDIO_STATE_ENABLE)
		{
			err = GD_DMA_Start(pDev->dmaHandle, 0);
			if(err != GD_OK)
			{
				return err;
			}
			pDev->state = AUDIO_STATE_RUNNING;
		}
		if(revFrameNumber>=AUDIO_BUF_MIN_FRAME && pDev->state==AUDIO_STATE_WAITING)
		{
			GH_AUDIO_set_FIFO_CTRL_TX_FIFO_ENABLE(1);
			pDev->state = AUDIO_STATE_RUNNING;
		}		
	}

	return GD_OK;
}

static void GD_AUDIO_AO_Set_RecFrameNum(U32 RecFrameNum)
{
	RecAOFrameNum = RecFrameNum;
}

U32 GD_AUDIO_AO_Get_RecFrameNum(void)
{
	return RecAOFrameNum;
}

GERR GD_AUDIO_AO_Set_Attr(GD_AUDIO_ATTR_S *pattr)
{
	GERR err = GD_OK;

	err = audio_ao_set_attr(pattr);
    if(err == GD_OK)
	{
		aoDevInfo.sampleRate = pattr->sampleRate;
		aoDevInfo.soundMode  = pattr->soundMode;
	}

    return err;
}

GERR GD_AUDIO_AO_Get_Attr(GD_AUDIO_ATTR_S *pattr)
{
	pattr->sampleRate = aoDevInfo.sampleRate;
	pattr->soundMode  = aoDevInfo.soundMode;

    return GD_OK;
}

GERR GD_AUDIO_AO_Set_Volume(GD_AUDIO_VOLUME_E volume)
{
	audio_ao_set_volume(volume);

    return GD_OK;
}

GD_AUDIO_VOLUME_E GD_AUDIO_AO_Get_Volume(void)
{
    return ((GH_AUDIO_get_PGA_DPGA_CFG()&(~0x4040))>>8);
}

GERR GD_AUDIO_AO_Mute(void)
{
	GH_AUDIO_set_PGA_DPGA_CFG_PGA1_mute(1);
	GH_AUDIO_set_PGA_DPGA_CFG_PGA2_mute(1);
    return GD_OK;
}

GERR GD_AUDIO_AO_Unmute(void)
{
	GH_AUDIO_set_PGA_DPGA_CFG_PGA1_mute(0);
	GH_AUDIO_set_PGA_DPGA_CFG_PGA2_mute(0);
    return GD_OK;
}

