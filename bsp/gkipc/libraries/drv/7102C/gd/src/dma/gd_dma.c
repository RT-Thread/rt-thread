/******************************************************************************
**
** \file      gd_uart.c
**
** \brief     DEMO test application.
**
**            (C) Goke Microelectronics China 2002 - 2007
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version   \$Id: gd_uart.c,v 1.8 2007/01/04 15:13:22 mneuma Exp $
**
******************************************************************************/
#include <stdio.h>
#include <string.h>

#include "gtypes.h"
#include "gd_int.h"
#include "gd_dma.h"
#include "gh_dma.h"

//*****************************************************************************
//*****************************************************************************
//** Local Defines
//*****************************************************************************
//*****************************************************************************

//#define DMA_DEBUG

#ifdef DMA_DEBUG
#define DMA_PRINTF(args...) printf(args)
#else
#define DMA_PRINTF(args...)
#endif	

//*****************************************************************************
//*****************************************************************************
//** Local structures
//*****************************************************************************
//*****************************************************************************

typedef struct
{
	GBOOL inUse;
	U32 channel;
	U32 mode;
	U32 descNumber;
	GD_DMA_DESCRIPTOR_S *pDescriptor;
	GD_DMA_NOTIFIER_F    notifier;
}DMA_DEVICE_S;

//*****************************************************************************
//*****************************************************************************
//** Global Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Local Data
//*****************************************************************************
//*****************************************************************************

static GD_HANDLE dmaIntHandle = 0;
static GD_DMA_DESCRIPTOR_S dmaDescriptor[DMA_CHAN_MAX_NUM][DMA_CHAN_MAX_DESC] __attribute__((aligned(DMA_BUFF_ADDR_ALIGN),section(".nocache_buffer")));
static DMA_DEVICE_S  dmaDev[DMA_CHAN_MAX_NUM];
static U8 initialised = 0;

//*****************************************************************************
//*****************************************************************************
//** Local Functions Declaration
//*****************************************************************************
//*****************************************************************************

static void dma_int_handler(void)
{
    U32 i = 0;
	U32 intSource = 0;

	intSource = GH_DMA_get_IR();
    for (i=0; i<=DMA_CHAN_MAX_NUM; i++)
    {
        if((intSource&(1<<i)) && (dmaDev[i].notifier!=NULL))
        {
            dmaDev[i].notifier();
			GH_DMA_set_Status(i,0);
        }
    }
}

static GERR dma_set_eoc(DMA_DEVICE_S *dev)
{
	U32 i = 0;
	GD_DMA_DESCRIPTOR_S *pdescriptor = NULL;
	
	if(dev == NULL)
	{
		return GD_ERR_BAD_PARAMETER;
	}

	pdescriptor = dev->pDescriptor;

	for(i=0; i<dev->descNumber; i++,pdescriptor++)
	{
		pdescriptor->descAttr |= DMA_DESC_EOC;	
	}

	return GD_OK;
}


static GERR dma_clr_eoc(DMA_DEVICE_S *dev)
{
	U32 i = 0;
	GD_DMA_DESCRIPTOR_S *pdescriptor = NULL;
	
	if(dev == NULL)
	{
		return GD_ERR_BAD_PARAMETER;
	}

	pdescriptor = dev->pDescriptor;

	for(i=0; i<dev->descNumber; i++,pdescriptor++)
	{
		pdescriptor->descAttr &= ~DMA_DESC_EOC;	
	}

	return GD_OK;
}


//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************
GERR GD_DMA_Init(void)
{
	GERR err = GD_OK;
    GD_INT_OPEN_PARAMS_S intParams;
	
    if(initialised)
    {
        return(GD_OK);
    }

	memset((void *)dmaDescriptor, 0, sizeof(GD_DMA_DESCRIPTOR_S)*DMA_CHAN_MAX_NUM*DMA_CHAN_MAX_DESC);
	memset((void *)dmaDev, 0, sizeof(DMA_DEVICE_S)*DMA_CHAN_MAX_NUM);

    intParams.type           = GD_INT_DMA_IRQ;
    intParams.sensitivity    = GD_INT_LEVEL_HIGH;
    intParams.active         = GD_INT_NO_INVERT_IRQ;
    intParams.priority       = GD_INT_MID_PRIORITY;
    intParams.isrFct.lowPrio = dma_int_handler;
    err = GD_INT_Open(&intParams,&dmaIntHandle);
	if(err != GD_OK)
	{
		return err;
	}

	GD_INT_Enable(&dmaIntHandle, GD_INT_ENABLED);
	
	initialised = 1;
		
	return GD_OK;

}

GERR GD_DMA_Exit(void)
{
    if(!initialised)
    {
        return(GD_ERR_NOT_INITIALIZED);
    }
	
	GD_INT_Enable(&dmaIntHandle, GD_INT_DISABLED);
	GD_INT_Close(&dmaIntHandle);

	initialised = 0;

	return GD_OK;
}

GERR GD_DMA_Open(GD_DMA_OPEN_PARAM_S *openParam, GD_HANDLE *handle)
{
	DMA_DEVICE_S *pDev = NULL;

	if(openParam==NULL || handle==NULL)
	{
		return GD_ERR_BAD_PARAMETER;
	}
	if(openParam->channel >= DMA_CHAN_MAX_NUM)
	{
		return GD_ERR_BAD_PARAMETER;
	}	
	
	pDev = &dmaDev[openParam->channel];
	if(pDev->inUse == GTRUE)
	{
		return GD_ERR_ALREADY_OPEN;
	}

	pDev->inUse       = GTRUE;
	pDev->channel     = openParam->channel;
	pDev->mode        = openParam->mode;
	pDev->notifier    = openParam->intNotifier;
	pDev->pDescriptor = dmaDescriptor[pDev->channel];
	pDev->descNumber  = 0;

	*handle = (GD_HANDLE)pDev;

	return GD_OK;
}

GERR GD_DMA_Close(GD_HANDLE handle)
{
	DMA_DEVICE_S *pDev = (DMA_DEVICE_S *)handle;

	memset((void *)pDev->pDescriptor, 0, sizeof(GD_DMA_DESCRIPTOR_S)*DMA_CHAN_MAX_DESC);
	memset((void *)pDev, 0, sizeof(DMA_DEVICE_S));

	return GD_OK;
}

GERR GD_DMA_AddDescriptor(GD_HANDLE handle, GD_DMA_DESCRIPTOR_S *descriptor)
{
	DMA_DEVICE_S *pDev = (DMA_DEVICE_S *)handle;
	GD_DMA_DESCRIPTOR_S *pLastDescriptor = NULL;

	if(pDev->inUse != GTRUE)
	{
		return GD_ERR_INVALID_HANDLE;
	}
	if(pDev->mode != DMA_MODE_DESCRIPTOR)
	{
		return GD_ERR_FEATURE_NOT_SUPPORTED;
	}	
	if(pDev->descNumber >= DMA_CHAN_MAX_DESC)
	{
		return GD_ERR_FEATURE_NOT_SUPPORTED;
	}		

	descriptor->next = pDev->pDescriptor;
	if(pDev->descNumber > 0)
	{
		pLastDescriptor       = pDev->pDescriptor+pDev->descNumber-1;
		pLastDescriptor->next = pDev->pDescriptor+pDev->descNumber;
	}
	memcpy((void *)(pDev->pDescriptor+pDev->descNumber), (void *)descriptor, sizeof(GD_DMA_DESCRIPTOR_S));
	pDev->descNumber++;

	return GD_OK;
}


GERR GD_DMA_Start(GD_HANDLE handle, U32 desc)
{
#ifdef DMA_DEBUG
	U32 i = 0;
	GD_DMA_DESCRIPTOR_S *pdescriptor = NULL;
#endif
	DMA_DEVICE_S *pDev = (DMA_DEVICE_S *)handle;

	if(pDev->inUse != GTRUE)
	{
		return GD_ERR_INVALID_HANDLE;
	}
	
	if(pDev->mode == DMA_MODE_NORMAL)
	{
		// TODO: DMA NORMAL MODE
	}
	else
	{
		if(desc >= pDev->descNumber)
		{
			return GD_ERR_FEATURE_NOT_SUPPORTED;
		}	

		dma_clr_eoc(pDev);
		
#ifdef DMA_DEBUG
		pdescriptor = pDev->pDescriptor;
		for(i=0; i<pDev->descNumber; i++,pdescriptor++)
		{
			DMA_PRINTF("[GD_DMA]DMA ch%d descriptor %d: 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X\n",
				pDev->channel, i+1,
				pdescriptor->srcAddr, pdescriptor->dstAddr, (U32)pdescriptor->next, 
				pdescriptor->reportAddr, pdescriptor->dataLength, pdescriptor->descAttr);
		}
#endif		
		GH_DMA_set_Status(pDev->channel, 0);
		GH_DMA_set_Descriptor_Address(pDev->channel, (U32)(pDev->pDescriptor+desc));
		GH_DMA_set_Control(pDev->channel, DMA_CHAN_CTRL_EN|DMA_CHAN_CTRL_D);
	}

    return GD_OK;
}


GERR GD_DMA_Stop(GD_HANDLE handle)
{
	DMA_DEVICE_S *pDev = (DMA_DEVICE_S *)handle;

	if(pDev->inUse != GTRUE)
	{
		return GD_ERR_INVALID_HANDLE;
	}
	
	if(pDev->mode == DMA_MODE_NORMAL)
	{
		// TODO: DMA NORMAL MODE
	}
	else
	{
		dma_set_eoc(pDev);
	}

    return GD_OK;
}


