/******************************************************************************
**
** \file      gh_i2c.c
**
** \brief     I2C.
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
#include <gtypes.h>

#include "gd_i2c.h"
#include "gd_gpio.h"
#include "gd_int.h"
#include "gd_timer.h"
#include "gh_i2c.h"
#ifndef GD_I2C_SOFTWARE /* do we use HW or SW I2C driver ?????? */
/*---------------------------------------------------------------------------*/
/* local defines                                                             */
/*---------------------------------------------------------------------------*/
#define I2C_START   0x04
#define I2C_OPT     0x00
#define I2C_RESPOND 0x02
#define I2C_STOP    0x08
#define I2C_ACK     0x01
#define I2C_NO_ACK  0x00
#define I2C_BLOCK_COUNT     2
#define I2C_TIME_OUT        1000

typedef     GD_INT_DATA_S* (*GD_I2C_ISR_T)(U8 channelIndex);
typedef enum
{
    GD_I2C_STATE_IDLE       = 0,
    GD_I2C_STATE_START_WRITE= 1,
    GD_I2C_STATE_WRITE      = 2,
    GD_I2C_STATE_START_READ = 3,
    GD_I2C_STATE_READ       = 4,
    GD_I2C_STATE_STOP       = 5,
}gd_i2c_state_e;
typedef struct
{
    U32                 channel;
    U32                 using;
    GD_I2C_SPEED_E      speed;
    GD_I2C_MODE_E       mode;
    GD_HANDLE           i2cHandle;      /* INT handle */

    GBOOL               lock;
    gd_i2c_state_e      eState;
    GERR                i2cErrorState;  /* error state of block */

    U8                  address;        /* i2c address */
    U8*                 ReadBufferP;    /* read buffer pointer */
    U8*                 WriteBufferP;   /* write buffer pointer */
    U32                 rxLength;       /* read buffer length */
    U32                 txLength;       /* write buffer length */

    GD_I2C_ISR_T        i2cIsr;         /* ISR of the block */
} GD_I2C_STATE_MACHINE_S;

volatile GD_I2C_STATE_MACHINE_S i2c_state_machine_data[I2C_BLOCK_COUNT] = {0};
/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/
static U8                       I2cInitDone = 0;  //is or not already initialized

static GISR1 gd_i2c_isr0(void)
{
    GD_INT_HANDLER_F Handler;
    GD_INT_DATA_S*   intDataP;
    Handler  = GD_INT_GetHandler( GD_INT_IDC_IRQ );
    intDataP = Handler();
    if ( intDataP->processor )
        intDataP->processor( intDataP->data );
}

static GISR1 gd_i2c_isr1(void)
{
    GD_INT_HANDLER_F Handler;
    GD_INT_DATA_S*   intDataP;
    Handler  = GD_INT_GetHandler( GD_INT_IDC2_IRQ );
    intDataP = Handler();
    if ( intDataP->processor )
        intDataP->processor( intDataP->data );
}

/*!
*******************************************************************************
**
** \brief   This function processes the I2C interrupt (normal operation).
**
** \sa      FI_I2C_LowISR() <br>
**          FI_I2C_MidISR()
**
******************************************************************************/
static GD_INT_DATA_S* i2cHandler_0(void)
{

    GD_INT_DATA_S* intDataPtr = NULL;

    intDataPtr = i2c_state_machine_data[GD_I2C_CHANNEL_ONE].i2cIsr(GD_I2C_CHANNEL_ONE);

    return( intDataPtr );
}

/*!
*******************************************************************************
**
** \brief   This function processes the I2C interrupt (normal operation).
**
** \sa      FI_I2C_LowISR() <br>
**          FI_I2C_MidISR()
**
******************************************************************************/
static GD_INT_DATA_S* i2cHandler_1(void)
{

    GD_INT_DATA_S* intDataPtr = NULL;

    intDataPtr = i2c_state_machine_data[GD_I2C_CHANNEL_TWO].i2cIsr(GD_I2C_CHANNEL_TWO);

    return( intDataPtr );
}

static GERR gd_i2c_ack(U32 channel, U8 ack)
{
    U32     timeout;
    timeout = I2C_TIME_OUT;
    while(timeout&&((GH_I2C_get_CONTROL(channel)&ack)!=ack))
    {
        timeout--;
    }
    if((timeout == 0) && ((GH_I2C_get_CONTROL(channel)&ack)!=ack))
    {
        return GD_ERR_I2C_NOACK;
    }
    return GD_OK;
}

static GD_INT_DATA_S* i2cHandler_AM(U8 channelIndex)
{
    static GD_INT_DATA_S intData;
    volatile GD_I2C_STATE_MACHINE_S* i2c_handle_ptr = NULL;

    intData.length      = 0;
    intData.data        = NULL;
    intData.processor   = NULL;

    if (channelIndex >= I2C_BLOCK_COUNT)
    {
        return  &intData;
    }
    i2c_handle_ptr = &i2c_state_machine_data[channelIndex];

    //status_reg = GH_I2C_get_STATUS(i2c_handle_ptr->channel);
    //control_reg = GH_I2C_get_CONTROL(i2c_handle_ptr->channel);

    switch(i2c_handle_ptr->eState)
    {
    case GD_I2C_STATE_START_WRITE:
        if(gd_i2c_ack(i2c_handle_ptr->channel, I2C_RESPOND|I2C_ACK) == GD_OK)
        {
            GH_I2C_set_DATA_Data(i2c_handle_ptr->channel,*i2c_handle_ptr->WriteBufferP++);
            i2c_handle_ptr->txLength--;
            i2c_handle_ptr->eState = GD_I2C_STATE_WRITE;
            GH_I2C_set_CONTROL(i2c_handle_ptr->channel,I2C_OPT);
        }
        else
        {
			GH_I2C_set_CONTROL(i2c_handle_ptr->channel,I2C_OPT|I2C_STOP);
            i2c_handle_ptr->i2cErrorState  = GD_ERR_I2C_START_NOACK;
        }
        break;

    case GD_I2C_STATE_WRITE:
        if(gd_i2c_ack(i2c_handle_ptr->channel, I2C_RESPOND|I2C_ACK) == GD_OK)
        {
            if(i2c_handle_ptr->txLength)
            {
                GH_I2C_set_DATA_Data(i2c_handle_ptr->channel,*i2c_handle_ptr->WriteBufferP++);
                i2c_handle_ptr->txLength--;
                GH_I2C_set_CONTROL(i2c_handle_ptr->channel,I2C_OPT);
            }
            else
            {
                if(i2c_handle_ptr->rxLength)
                {
                    GH_I2C_set_DATA(i2c_handle_ptr->channel,i2c_handle_ptr->address | 0x01);
                    i2c_handle_ptr->eState = GD_I2C_STATE_START_READ;
                    GH_I2C_set_CONTROL(i2c_handle_ptr->channel,I2C_START);
                }
                else
                {
                    i2c_handle_ptr->eState = GD_I2C_STATE_STOP;
                    i2c_handle_ptr->i2cErrorState  = GD_OK;
                    GH_I2C_set_CONTROL(i2c_handle_ptr->channel,I2C_STOP);
                }
            }
        }
        else
        {
			GH_I2C_set_CONTROL(i2c_handle_ptr->channel,I2C_OPT);
            i2c_handle_ptr->i2cErrorState  = GD_ERR_I2C_NOACK;
        }
        break;

    case GD_I2C_STATE_START_READ:
        if(gd_i2c_ack(i2c_handle_ptr->channel, I2C_RESPOND|I2C_ACK) == GD_OK)
        {
            i2c_handle_ptr->eState = GD_I2C_STATE_READ;
            i2c_handle_ptr->rxLength--;
            if(i2c_handle_ptr->rxLength)
            {
                GH_I2C_set_CONTROL(i2c_handle_ptr->channel,I2C_OPT);
            }
            else
            {
                GH_I2C_set_CONTROL(i2c_handle_ptr->channel,I2C_OPT|I2C_ACK);
            }
        }
        else
        {
			GH_I2C_set_CONTROL(i2c_handle_ptr->channel,I2C_OPT|I2C_STOP);
            i2c_handle_ptr->i2cErrorState  = GD_ERR_I2C_READ_NOACK;
        }
        break;

    case GD_I2C_STATE_READ:
        if(i2c_handle_ptr->rxLength)
        {
            if(gd_i2c_ack(i2c_handle_ptr->channel, I2C_RESPOND|I2C_ACK) != GD_OK)
            {
				GH_I2C_set_CONTROL(i2c_handle_ptr->channel,I2C_OPT);
                i2c_handle_ptr->i2cErrorState  = GD_ERR_I2C_READ_NOACK;
                break;
            }
            i2c_handle_ptr->rxLength--;
            *i2c_handle_ptr->ReadBufferP++ = GH_I2C_get_DATA_Data(i2c_handle_ptr->channel);

            if(i2c_handle_ptr->rxLength)
            {
                GH_I2C_set_CONTROL(i2c_handle_ptr->channel,I2C_OPT);
            }
            else
            {
                GH_I2C_set_CONTROL(i2c_handle_ptr->channel,I2C_OPT|I2C_ACK);
            }
        }
        else
        {
            if(gd_i2c_ack(i2c_handle_ptr->channel, I2C_RESPOND|I2C_NO_ACK) != GD_OK)
            {
				GH_I2C_set_CONTROL(i2c_handle_ptr->channel,I2C_OPT);
                i2c_handle_ptr->i2cErrorState  = GD_ERR_I2C_READ_NOACK;
                break;
            }
            *i2c_handle_ptr->ReadBufferP++ = GH_I2C_get_DATA_Data(i2c_handle_ptr->channel);

            i2c_handle_ptr->eState = GD_I2C_STATE_STOP;
            i2c_handle_ptr->i2cErrorState  = GD_OK;
            GH_I2C_set_CONTROL(i2c_handle_ptr->channel,I2C_STOP);
        }
        break;

    case GD_I2C_STATE_STOP:
        i2c_handle_ptr->eState = GD_I2C_STATE_IDLE;
        i2c_handle_ptr->i2cErrorState  = GD_OK;
        break;

    case GD_I2C_STATE_IDLE:
        i2c_handle_ptr->i2cErrorState  = GD_OK;
        break;
    }

    return( &intData );
}

static GERR i2cHandleCheck( GD_HANDLE pHandle )
{
    U32                ii;
    /* check if handle is valid */
    for (ii = 0; ii < I2C_BLOCK_COUNT; ii++)
    {
        if ((pHandle == (GD_HANDLE)(&i2c_state_machine_data[ii])) && (i2c_state_machine_data[ii].using))
        {
            return GD_OK;
        }
    }
    if (ii >= I2C_BLOCK_COUNT)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    return GD_OK;
}

GERR GD_I2C_Init( GD_I2C_INIT_PARAMS_S* paramsP )
{
    U32     i;
    GERR    ret;
    GD_INT_OPEN_PARAMS_S    paramsInt;
    GD_HANDLE               i2cHandle  = 0;

    /* check if already initialized */
    if(I2cInitDone != 0)
    {
        return GD_ERR_ALREADY_INITIALIZED;
    }

    for (i = 0; i < I2C_BLOCK_COUNT; i++)
    {
        i2c_state_machine_data[i].channel       = 0;
        i2c_state_machine_data[i].speed         = GD_I2C_100KBPS;  // 100kbps
        i2c_state_machine_data[i].using         = 0;
        i2c_state_machine_data[i].lock          = GFALSE;
    }
    /* Open the I2C interrupt */
    paramsInt.active      = GD_INT_NO_INVERT_IRQ;
    paramsInt.priority    = paramsP->priority;
    paramsInt.sensitivity = GD_INT_LEVEL_HIGH;

    paramsInt.type        = GD_INT_IDC_IRQ;
    paramsInt.isrFct.lowPrio = gd_i2c_isr0;
    ret = GD_INT_Open(&paramsInt, &i2cHandle);
    i2c_state_machine_data[GD_I2C_CHANNEL_ONE].i2cHandle = i2cHandle;
    if (ret != GD_OK)
        return GD_ERR_I2C_INT_ERR;
    GD_INT_SetHandler( paramsInt.type, i2cHandler_0);

    paramsInt.type        = GD_INT_IDC2_IRQ;
    paramsInt.isrFct.lowPrio = gd_i2c_isr1;
    ret = GD_INT_Open(&paramsInt, &i2cHandle);
    i2c_state_machine_data[GD_I2C_CHANNEL_TWO].i2cHandle = i2cHandle;
    if (ret != GD_OK)
        return GD_ERR_I2C_INT_ERR;
    GD_INT_SetHandler( paramsInt.type, i2cHandler_1);
    GD_INT_Enable(&i2cHandle, GD_INT_DISABLED);

    I2cInitDone = 1;

    return GD_OK;
}


GERR GD_I2C_Exit( void )
{
    U32            ii;

    if( I2cInitDone == 0 )
        return( GD_ERR_NOT_INITIALIZED );

    for (ii = 0; ii < I2C_BLOCK_COUNT; ii++)
    {
        i2c_state_machine_data[ii].using    = 0;
    }
    I2cInitDone = 0;

    return( GD_OK );
}

GERR GD_I2C_Open( GD_I2C_OPEN_PARAMS_S *openParamsP, GD_HANDLE* pHandle  )
{
    U16             prescale;
    GD_HANDLE       Gpiohandle;

    if((openParamsP == NULL) || (openParamsP->speed == 0))
    {
        return GD_ERR_BAD_PARAMETER;
    }
    switch(openParamsP->channel)
    {
    case GD_I2C_CHANNEL_ONE:
        GD_GPIO_OpenFunctionMode(GD_GPIO_TYPE_INOUT_I2C_DATA, &Gpiohandle);
        GD_GPIO_OpenFunctionMode(GD_GPIO_TYPE_INOUT_I2C_CLK, &Gpiohandle);
        break;
    case GD_I2C_CHANNEL_TWO:
        GD_GPIO_OpenFunctionMode(GD_GPIO_TYPE_INOUT_I2C_DATA2, &Gpiohandle);
        GD_GPIO_OpenFunctionMode(GD_GPIO_TYPE_INOUT_I2C_CLK2, &Gpiohandle);
        break;
    }
    if(i2c_state_machine_data[openParamsP->channel].using)
    {
        return GD_ERR_DEVICE_BUSY;
    }
    i2c_state_machine_data[openParamsP->channel].channel      = openParamsP->channel;
    i2c_state_machine_data[openParamsP->channel].using        = GTRUE;
    i2c_state_machine_data[openParamsP->channel].speed        = openParamsP->speed;
    i2c_state_machine_data[openParamsP->channel].mode         = openParamsP->mode;

    // IDC period = (IDC_clk) / (4*(prescale[15:0]+1) + 2)
    // (prescale[15:0] = ((IDC_clk / period - 2) / 4) - 1
    prescale = ((GD_GET_APB_ClkHz()/(U32)openParamsP->speed - 2) >> 2) - 1;
    // enable
    GH_I2C_set_ENABLE_en(openParamsP->channel, 0);

    GH_I2C_set_PRESCALEL_scale(openParamsP->channel, (prescale & 0xFF));
    GH_I2C_set_PRESCALEH_scale(openParamsP->channel, (prescale & 0xFF00)>>8);
    GH_I2C_set_ENABLE_en(openParamsP->channel, 1);

    // clear the DR
    i2c_state_machine_data[openParamsP->channel].i2cIsr = i2cHandler_AM;

    //
    *pHandle = (GD_HANDLE)(&i2c_state_machine_data[openParamsP->channel]);
    return( GD_OK );
}

GERR GD_I2C_Close( GD_HANDLE *pHandle )
{
    GERR            ret;
    GD_I2C_STATE_MACHINE_S    *device;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device = (GD_I2C_STATE_MACHINE_S *)(*pHandle);

    ret = i2cHandleCheck(*pHandle);
    if (GD_OK != ret)
    {
        return ret;
    }

    device->using = GFALSE;
    pHandle = NULL;

    GH_I2C_set_ENABLE_en(device->channel, 0);
    return( GD_OK );
}

GERR GD_I2C_Process( GD_HANDLE* pHandle, U8 address, U8* writeDataP, U32 wrDataLen, U8* readDataP, U32 rdDataLen )
{
    U32     stTime, endTime;
    S32     diff, timeOut;
    GD_I2C_STATE_MACHINE_S    *i2c_handle_ptr;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    i2c_handle_ptr = (GD_I2C_STATE_MACHINE_S *)(*pHandle);

    if( i2c_handle_ptr->i2cErrorState == GD_ERR_I2C_BUSY )
        return GD_ERR_I2C_BUSY;
    if (i2c_handle_ptr->speed == GD_I2C_100KBPS)
        timeOut = ((wrDataLen+rdDataLen)<<4)/100 + I2C_TIME_OUT;
    else
        timeOut = ((wrDataLen+rdDataLen)<<4)/400 + I2C_TIME_OUT;

    //GD_INT_Enable(&i2c_handle_ptr->i2cHandle, GD_INT_ENABLED);
    /* set pointer buffer for ISR */
    i2c_handle_ptr->WriteBufferP = writeDataP;
    i2c_handle_ptr->ReadBufferP  = readDataP;
    i2c_handle_ptr->txLength     = wrDataLen;
    i2c_handle_ptr->rxLength     = rdDataLen;
    i2c_handle_ptr->address      = address;

	if(writeDataP && (wrDataLen > 0))//dx8 chip only do write opreation when need. youbo,20170926
	{
	    GH_I2C_set_DATA(i2c_handle_ptr->channel,address & 0xFE);
	    i2c_handle_ptr->eState = GD_I2C_STATE_START_WRITE;
	}
	else
	{
        GH_I2C_set_DATA(i2c_handle_ptr->channel,address | 0x01);
	    i2c_handle_ptr->eState = GD_I2C_STATE_START_READ;
	}
	
    i2c_handle_ptr->i2cErrorState= GD_ERR_I2C_BUSY;

    GH_I2C_set_CONTROL(i2c_handle_ptr->channel,I2C_START);

    GD_INT_Enable(&i2c_handle_ptr->i2cHandle, GD_INT_ENABLED);

    stTime = GD_TIMER_ReadTimerStamp();
    endTime= GD_TIMER_ReadTimerStamp();
    do
    {
        endTime= GD_TIMER_ReadTimerStamp();
        diff = endTime - stTime;
        if(stTime > endTime) /* check overflow */
            diff = ((diff < 0L) ? -diff : diff); /* C-LIB code for labs() */
    }while((i2c_handle_ptr->i2cErrorState == GD_ERR_I2C_BUSY) && (diff < timeOut));

    if (i2c_handle_ptr->i2cErrorState  == GD_ERR_I2C_BUSY)
        i2c_handle_ptr->i2cErrorState  = GD_ERR_TIMEOUT;
    /* disable IRQ mask */
    GD_INT_Enable(&(i2c_handle_ptr->i2cHandle), GD_INT_DISABLED);

    return i2c_handle_ptr->i2cErrorState;
}

GERR GD_I2C_Write( GD_HANDLE *pHandle,U8 address,U8* buffer, U32 bytes )
{
    GERR            ret;
    GD_I2C_STATE_MACHINE_S    *device;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device = (GD_I2C_STATE_MACHINE_S *)(*pHandle);
    /* check if handle is valid */
    ret = i2cHandleCheck(*pHandle);
    if (GD_OK != ret)
    {
        return ret;
    }
    switch(device->mode)
    {
    case GD_I2C_TURBO_MODE:
        //if(bytes >= 63)
        //{
        //    return GD_ERR_I2C_FIFO_OVERFLOW;
        //}
        GD_INT_Enable(&device->i2cHandle, GD_INT_DISABLED);
        GH_I2C_set_FMCONTROL(device->channel,I2C_START);
        GH_I2C_set_FMDATA(device->channel,address & 0xFE);

        while(bytes)
        {
            GH_I2C_set_FMDATA(device->channel,*buffer++);
            bytes--;
        }
        GH_I2C_set_FMCONTROL(device->channel,I2C_STOP|I2C_RESPOND);
        //if(gd_i2c_ack(device->channel, I2C_RESPOND|I2C_ACK) != GD_OK)
        //{
        //    return GD_ERR_I2C_SL_NACK;
        //}
        // clear FIFO
        GH_I2C_set_CONTROL(device->channel,0x01);
        break;
    case GD_I2C_INTERRUPT:
        return GD_I2C_Process(pHandle, address, buffer, bytes, NULL, 0);
    case GD_I2C_NORMAL:
    default:
        GD_INT_Enable(&device->i2cHandle, GD_INT_DISABLED);

        GH_I2C_set_DATA(device->channel,address & 0xFE);
        GH_I2C_set_CONTROL(device->channel,I2C_START);
        if(gd_i2c_ack(device->channel, I2C_RESPOND|I2C_ACK) != GD_OK)
        {
            return GD_ERR_I2C_START_NOACK;
        }
        while(bytes)
        {
            GH_I2C_set_DATA_Data(device->channel,*buffer++);
            GH_I2C_set_CONTROL(device->channel,I2C_OPT);
            bytes--;
            if(gd_i2c_ack(device->channel, I2C_RESPOND|I2C_ACK) != GD_OK)
            {
                return GD_ERR_I2C_DATA_NOACK;
            }
        }
        GH_I2C_set_CONTROL(device->channel,I2C_STOP);
        break;
    }
    return( GD_OK );
}

GERR GD_I2C_Read( GD_HANDLE* pHandle, U8 address, U8* regbuffer,U32 regbytes,U8* buffer, U32 bytes )
{
    GERR    ret;
    GD_I2C_STATE_MACHINE_S    *device;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device = (GD_I2C_STATE_MACHINE_S *)(*pHandle);
    /* check if handle is valid */
    ret = i2cHandleCheck(*pHandle);
    if (GD_OK != ret)
    {
        return ret;
    }
    switch(device->mode)
    {
    case GD_I2C_INTERRUPT:
        return GD_I2C_Process(pHandle, address, regbuffer, regbytes, buffer, bytes);
    case GD_I2C_TURBO_MODE:  // write operation only.
    case GD_I2C_NORMAL:
    default:
        GD_INT_Enable(&device->i2cHandle, GD_INT_DISABLED);

		if(regbytes)//dx8 chip only do write opreation when need. youbo,20170926
		{
	        GH_I2C_set_DATA(device->channel,address & 0xFE);
	        GH_I2C_set_CONTROL(device->channel,I2C_START);
	        if(gd_i2c_ack(device->channel, I2C_RESPOND|I2C_ACK) != GD_OK)
	        {	
	            return GD_ERR_I2C_START_NOACK;
	        }
		}
		
        while(regbytes)
        {
            GH_I2C_set_DATA_Data(device->channel,*regbuffer++);
            GH_I2C_set_CONTROL(device->channel,I2C_OPT);
            regbytes--;
            if(gd_i2c_ack(device->channel, I2C_RESPOND|I2C_ACK) != GD_OK)
            {
                return GD_ERR_I2C_ADDR_NOACK;
            }
        }

        GH_I2C_set_DATA(device->channel,address | 0x01);
        GH_I2C_set_CONTROL(device->channel,I2C_START);
        if(gd_i2c_ack(device->channel, I2C_RESPOND|I2C_ACK) != GD_OK)
        {
            return GD_ERR_I2C_RESTART_NOACK;
        }
        while(bytes)
        {
            bytes--;
            if(bytes)
            {
                GH_I2C_set_CONTROL(device->channel,I2C_OPT);
                if(gd_i2c_ack(device->channel, I2C_RESPOND|I2C_ACK) != GD_OK)
                {
                    return GD_ERR_I2C_READ_NOACK;
                }
            }
            else
            {
                GH_I2C_set_CONTROL(device->channel,I2C_OPT|I2C_ACK);
                if(gd_i2c_ack(device->channel, I2C_RESPOND|I2C_NO_ACK) != GD_OK)
                {
                    return GD_ERR_I2C_READ_NOACK;
                }
            }
            *buffer++ = GH_I2C_get_DATA_Data(device->channel);
        }
        GH_I2C_set_CONTROL(device->channel,I2C_STOP);
        break;
    }
    return( GD_OK );
}

GERR GD_I2C_SetOperationMode(GD_I2C_CHANNEL_E channel,GD_I2C_OPEN_MODE_E operationMode)
{
    return GD_OK;
}

GERR GD_I2C_SetProtocol(GD_HANDLE *handleP,GD_I2C_PROTOCOL_E protocol)
{
    return GD_OK;
}

GERR GD_I2C_SetMode(GD_HANDLE *pHandle, GD_I2C_MODE_E Mode)
{
    GERR            ret;
    GD_I2C_STATE_MACHINE_S    *device;
    if(pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device = (GD_I2C_STATE_MACHINE_S *)(*pHandle);
    /* check if handle is valid */
    ret = i2cHandleCheck(*pHandle);
    if (GD_OK != ret)
    {
        return ret;
    }
    switch(Mode)
    {
    case GD_I2C_TURBO_MODE:
        device->mode = GD_I2C_TURBO_MODE;
        break;
    case GD_I2C_INTERRUPT:
        device->mode = GD_I2C_INTERRUPT;
        break;
    case GD_I2C_NORMAL:
    default:
        device->mode = GD_I2C_NORMAL;
        break;
    }
    return GD_OK;
}

#endif
/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

