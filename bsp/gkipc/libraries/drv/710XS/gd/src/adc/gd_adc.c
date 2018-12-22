/******************************************************************************
**
** \file      gh_adc.c
**
** \brief     ADC.
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
#include <string.h>
#include <stdio.h>
#include <gtypes.h>

#include "gd_adc.h"
#include "gd_int.h"
#include "gd_timer.h"
#include "gh_adc.h"
#ifdef GD_ADC_DEBUG
#define GD_ADC_PRINTF(args...) printf(args)
#else
#define GD_ADC_PRINTF(args...)
#endif
/*---------------------------------------------------------------------------*/
/* local defines                                                             */
/*---------------------------------------------------------------------------*/
typedef struct
{
    GD_ADC_CHANNEL_E channel;
    GD_ADC_CRYPTO_DATA_T control;
    GBOOL            using;
    GD_HANDLE        adcHandle;      /* INT handle */
    //GD_ADC_ISR_T        ADCIsr;         /* ISR of the block */
} GD_ADC_STATE_MACHINE_S;

volatile GD_ADC_STATE_MACHINE_S ADC_state_machine_data[GD_ADC_CHANNEL_COUNT] = {0};
/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/
static U8                       ADCInitDone = 0;  //is or not already initialized

static GISR1 gd_ADC_isr(void)
{
    printf("I--->ADC0:0x%08x\n", GH_ADC_get_ReadData(GD_ADC_CHANNEL_ONE));
    printf("I--->ADC1:0x%08x\n", GH_ADC_get_ReadData(GD_ADC_CHANNEL_TWO));
}

static GERR ADCHandleCheck( GD_HANDLE pHandle )
{
    U32                ii;
    /* check if handle is valid */
    for (ii = 0; ii < GD_ADC_CHANNEL_COUNT; ii++)
    {
        if ((pHandle == (GD_HANDLE)(&ADC_state_machine_data[ii])) && (ADC_state_machine_data[ii].using))
        {
            return GD_OK;
        }
    }
    if (ii >= GD_ADC_CHANNEL_COUNT)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    return GD_OK;
}

GERR GD_ADC_Init( void )
{
    U32     i;
    GERR    ret;
    GD_INT_OPEN_PARAMS_S    paramsInt;
    GD_HANDLE               adcHandle  = 0;

    /* check if already initialized */
    if(ADCInitDone != 0)
    {
        return GD_ERR_ALREADY_INITIALIZED;
    }

    for (i = 0; i < GD_ADC_CHANNEL_COUNT; i++)
    {
        ADC_state_machine_data[i].channel       = GD_ADC_CHANNEL_ONE;
        ADC_state_machine_data[i].using         = GFALSE;
    }

    /* Open the ADC interrupt */
    paramsInt.active      = GD_INT_NO_INVERT_IRQ;
    //paramsInt.priority    = paramsP->priority;
    paramsInt.sensitivity = GD_INT_BOTH_EDGES;

    paramsInt.type        = GD_INT_ADC_LEVEL_CHANGE_IRQ;
    paramsInt.isrFct.lowPrio = gd_ADC_isr;
    ret = GD_INT_Open(&paramsInt, &adcHandle);
    ADC_state_machine_data[GD_ADC_CHANNEL_ONE].adcHandle = adcHandle;
    ADC_state_machine_data[GD_ADC_CHANNEL_TWO].adcHandle = adcHandle;

    GH_ADC_set_Enable(GD_ADC_ENABLE_ENABLE);
    // 0 000 00 1 0 0101 101 0
    GH_ADC_set_AUX_ATOP_REG0(GD_ADC_AUX_ATOP_INITIALIZE);
    GH_ADC_set_AUX_ATOP_REG2(0x0075);
    // 001 0 1 0
    GH_ADC_set_Control(GD_ADC_CONTROL_INITIALIZE);
    ADCInitDone = 1;

    return GD_OK;
}


GERR GD_ADC_Exit( void )
{
    U32            ii;

    if( ADCInitDone == 0 )
        return( GD_ERR_NOT_INITIALIZED );

    for (ii = 0; ii < GD_ADC_CHANNEL_COUNT; ii++)
    {
        ADC_state_machine_data[ii].using    = GFALSE;
    }
    ADCInitDone = 0;

    GH_ADC_set_Enable(GD_ADC_ENABLE_DISABLE);
    return( GD_OK );
}

GERR GD_ADC_Open( GD_ADC_OPEN_PARAMS_S *openParamsP, GD_HANDLE* pHandle  )
{
    U16             prescale;
    GD_HANDLE       Gpiohandle;
    /* Open the ADC interrupt */
    if((openParamsP == NULL) || (openParamsP->channel >= GD_ADC_CHANNEL_COUNT))
    {
        return GD_ERR_BAD_PARAMETER;
    }
    GH_ADC_set_IntControl(openParamsP->channel, openParamsP->control.data);
    *pHandle = (GD_HANDLE)(&ADC_state_machine_data[openParamsP->channel]);
    if(openParamsP->channel == GD_ADC_CHANNEL_ONE)
    {
        GH_ADC_set_AUX_ATOP_REG0_sar_maxsel(GD_ADC_CONTROL_CHANNEL_ONE);
        GH_ADC_set_Control_channel(GD_ADC_REQ_CHANNEL_ONE);
    }
    else
    {
        GH_ADC_set_AUX_ATOP_REG0_sar_maxsel(GD_ADC_CONTROL_CHANNEL_TWO);
        GH_ADC_set_Control_channel(GD_ADC_REQ_CHANNEL_TWO);
    }

    ADC_state_machine_data[openParamsP->channel].channel       = openParamsP->channel;
    ADC_state_machine_data[openParamsP->channel].using         = GTRUE;

    GD_INT_Enable((GD_HANDLE*)&ADC_state_machine_data[openParamsP->channel].adcHandle, (U8)GD_INT_ENABLED);

    return( GD_OK );
}

GERR GD_ADC_Close( GD_HANDLE *pHandle )
{
    GERR            ret;
    GD_ADC_STATE_MACHINE_S    *device;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device = (GD_ADC_STATE_MACHINE_S *)(*pHandle);

    ret = ADCHandleCheck(*pHandle);
    if (GD_OK != ret)
    {
        return ret;
    }

    device->using = GFALSE;
    pHandle = NULL;

    return( GD_OK );
}

GERR GD_ADC_Read( GD_HANDLE* pHandle, U32* data)
{
    GERR    ret;
    GD_ADC_STATE_MACHINE_S    *device;

    if ((pHandle == NULL) || (data == NULL))
    {
        return GD_ERR_BAD_PARAMETER;
    }

    device = (GD_ADC_STATE_MACHINE_S *)(*pHandle);
    *data = GH_ADC_get_ReadData(device->channel);

    return( GD_OK );
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

