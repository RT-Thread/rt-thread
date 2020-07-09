/******************************************************************************
**
** \file      gd_ir.c
**
** \brief     Infrared driver.
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version
**
******************************************************************************/
#include <stdio.h>
#include <string.h>

#include "gtypes.h"

#include "gh_pmu_irr.h"
#include "gh_pmu_irt.h"
#include "gh_pmu_rtc.h"
#include "gh_pmu.h"

#include "gd_gpio.h"
#include "gd_ir.h"
#include "gd_int.h"

//#define DEBUG_PRINT
#ifdef DEBUG_PRINT
#include <gm_lib/gm_debug.h>
#endif

/*---------------------------------------------------------------------------*/
/* local defines                                                             */
/*---------------------------------------------------------------------------*/
#define IRR_MAX_DATA        0x0100

/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/
static U8      Ir_Status        = 0;
/*for receiver*/
static U16     IrBuffer[IRR_MAX_DATA] = {0};
static U16     IrDataNumber     = 0;        //number of the received data.
static U16     IrSeqNumber      = 0;         //number of the sequence command
static U16     IrReadPointer    = 0;
static U16     IrWritePointer   = 0;
static U8      IrBufferOver     = 0;
static U8      IrBufferOverApi  = 0;
static U8      IRDataAvailable  = 0;
static GD_RTC_NOTIFY RtcNotify  = NULL;
static U32     RtcPreCount      = 0;
static U32     RtcIndex         = 0;

static void (*IrNotifyFunction)();

/*---------------------------------------------------------------------------*/
/* local functions                                                           */
/*---------------------------------------------------------------------------*/
static void         irrInitial(void);
static GISR1        GI_IR_ISR(void);
static void         GD_IR_ISR_IRT(void);

/*---------------------------------------------------------------------------*/
/* GOKESDK functions                                                            */
/*---------------------------------------------------------------------------*/
/*!
*******************************************************************************
**
** \brief  Closes an instance of the IR driver.
**
**         If closing is successful, the handle variable will be set to NULL
**         and GD_OK will be returned.
**
** \param  pHandle  Pointer to the handle of the driver to close.
**
** \return Possible return codes:
**         - #GD_OK
**         - #GD_ERR_INVALID_HANDLE
**
** \sa     GD_IR_Open()
**
******************************************************************************/
GERR GD_IR_Close(GD_HANDLE *pHandle)
{
    if(*pHandle == GD_IR_RECEIVER )
    {
        if((Ir_Status & GD_IR_RECEIVER_OPENED) != GD_IR_RECEIVER_OPENED)
            return GD_ERR_INVALID_HANDLE;
        Ir_Status &= (~GD_IR_RECEIVER_OPENED);
        GH_PMU_IRR_set_Prog(0x08);
    }
    else if  (*pHandle == GD_IR_TRANSMITTER)
    {
        if((Ir_Status & GD_IR_TRANSMITTER_OPENED) != GD_IR_TRANSMITTER_OPENED)
            return GD_ERR_INVALID_HANDLE;
        Ir_Status &= (~GD_IR_TRANSMITTER_OPENED);
    }
    else return  GD_ERR_INVALID_HANDLE;

    *pHandle = 0;

    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Initialises the IR driver.
**
**         This function must be called at start-up to set the interrupt service
**         routine for the infrared interrupt and to register the callback
**         function.
**
** \param  pInitParams  Pointer to the init parameters.
**
** \return Possible return codes:
**         - #GD_OK
**         - #GD_ERR_ALREADY_INITIALIZED
**
** \sa     GD_IR_SetNotifyFunction()
**
******************************************************************************/
GERR GD_IR_Init(GD_IR_INIT_PARAMS_S *pInitParams)
{
    GD_INT_OPEN_PARAMS_S intParams;
    GERR ret;
    GD_HANDLE handle;

    intParams.type           = GD_INT_PMU_IRQ;
    intParams.sensitivity    = GD_INT_LEVEL_LOW;
    intParams.active         = GD_INT_NO_INVERT_IRQ;
    intParams.priority       = GD_INT_MID_PRIORITY;
    intParams.isrFct.lowPrio = GI_IR_ISR;
    IrNotifyFunction         = pInitParams->notifyFunction;
    ret = GD_INT_Open(&intParams,&handle);
    if (ret != GD_OK) return GD_ERR_ALREADY_INITIALIZED;

    GH_PMU_set_IRQ_EN_MASK(0x00);
    GH_PMU_set_IRQ_CLR_RTC(IRQ_EN_RTC);
    GH_PMU_set_IRQ_CLR_IRR(IRQ_EN_IRR);
    GH_PMU_set_IRQ_CLR_IRT(IRQ_EN_IRT);
    GH_PMU_set_IRQ_EN_MASK((IRQ_EN_IRT|IRQ_EN_IRR|IRQ_EN_RTC));

    GD_INT_Enable(&handle, GD_INT_ENABLED);

    return GD_OK;

}

/*!
*******************************************************************************
**
** \brief  Opens an instance of the driver.
**
** \param  pOpenParams  Pointer to configuration parameters.
** \param  pHandle      Pointer to handle assigned to the opened instance.
**
** \return Possible return codes:
**         - #GD_OK
**         - #GD_ERR_BAD_PARAMETER
**         - #GD_ERR_ALREADY_OPEN
**
******************************************************************************/
GERR GD_IR_IrrOpen(GD_IR_OPEN_PARAMS_S *pOpenParams, GD_HANDLE *pHandle)
{
    GERR err = GD_OK;

    if( pOpenParams != NULL )
    {
        if((Ir_Status & GD_IR_RECEIVER_OPENED) == GD_IR_RECEIVER_OPENED)
            return  GD_ERR_ALREADY_OPEN;
        GH_PMU_IRR_set_Prog(0x08);
        GH_PMU_IRR_set_PreScaler_h_VALUE((U8)(((pOpenParams->irr_config_s.prescaler) >> 8) & 0xff));
        GH_PMU_IRR_set_PreScaler_l_VALUE((U8)(pOpenParams->irr_config_s.prescaler & 0xff));
        irrInitial();
        Ir_Status |= GD_IR_RECEIVER_OPENED;

        *pHandle = GD_IR_RECEIVER;
    }

    return err;
}

/*!
*******************************************************************************
**
** \brief  Reads data from the IR receice buffer.
**
** \param  handle  Handle of IR receiver.
** \param  pData   Pointer to data array.
** \param  num     Number of data to be read.
**
** \return Possible return codes:
**         - #GD_OK
**         - #GD_ERR_INVALID_HANDLE
**
******************************************************************************/
GERR GD_IR_Receive(GD_HANDLE handle, U16 *pData, U16 num)
{
    U16 TimeData;
    U16 ix;

    if (handle != GD_IR_RECEIVER) return GD_ERR_INVALID_HANDLE;

    for (ix=0; ix<num; ix++)
    {
        TimeData = IrBuffer[IrReadPointer++];
        *pData++ = TimeData;
        IrDataNumber--;

        if (IrReadPointer >= IRR_MAX_DATA)
            IrReadPointer = 0;
    }

    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Sets the notification function.
**
**         This function sets the notification function which will be called
**         when an interrupt occurs.
**         Make sure that the receiving module is powered up when
**         the notify function is called.
**
**         Note that the notification function is called in ISR context.
**
** \param  nfyFunc  Pointer to notification function.
**
******************************************************************************/
void GD_IR_SetNotifyFunction(void(*nfyFunc)())
{
    IrNotifyFunction = nfyFunc;
}

/*!
*******************************************************************************
**
** \brief  Checks the status of an instance.
**
**         This function returns the status the of the receiver or transmitter.
**         If receiving is complete, it returns the number of received data.
**         If transmitting is complete, it returns the number of transmitted
**         data.
**
** \param  handle  Handle of receiver or transmitter to check.
** \param  pNum    Number of time data stored in the IR buffer.
**
** \return Possible return codes:
**         - #GD_OK
**         - #GD_ERR_IR_NO_SEQUENCE          Receiving is not completed yet.
**         - #GD_ERR_OUT_OF_MEMORY           Receiver buffer overflow
**         - #GD_ERR_IR_TRANSMIT_INPROCESS   Transmitting is not yet complete.
**         - #GD_ERR_INVALID_HANDLE
**
******************************************************************************/
GERR GD_IR_Status(GD_HANDLE handle, U16* pNum)
{
    U32 ReturnValue;

    if(handle == GD_IR_RECEIVER )
    {
        ReturnValue = GD_ERR_IR_NO_SEQUENCE;
        if (IrDataNumber)
            ReturnValue = GD_OK;
        if (IrBufferOverApi)
        {
            IrBufferOverApi = 0;
            ReturnValue = GD_ERR_OUT_OF_MEMORY;
        }
        *pNum = IrSeqNumber;

        return ReturnValue;
    }
    else
        return GD_ERR_INVALID_HANDLE;
}

/*---------------------------------------------------------------------------*/
/* local functions                                                           */
/*---------------------------------------------------------------------------*/

static U16 ir_count2time(U32 count)
{
    return (U16)((10000 * count) /(IR_FREQ * 10));
}


void  GD_RTC_RegisterNotify(GD_RTC_NOTIFY rtcNotifyFunc,U32 preCount)
{
    RtcPreCount = preCount;
    RtcNotify = rtcNotifyFunc;
}

/******************************************************************************

Name:       GI_IR_ISR / GD_IR_Handler

Description: This function processes the IR interrupt
             for receiver   : store the time data into IR Buffer.
                            : call the function if a sequence was received.
             for transmitter: transmit the stored data in the buffer

             In case of standby mode the SmartMPEG is powered up with
             limited functionality to be able to access the IR module.
             It is powered down at the end of the routine in order not
             to interfere with settings in the application.

Parameters:  None

Returns:     None

******************************************************************************/
static GISR1 GI_IR_ISR(void)
{
    U32 irdata = 0,irtdata = 0,irq_flag = 0;
    U16 tmp_value = 0;

    irq_flag = GH_PMU_get_IRQ_STATUS();

    if(irq_flag & IRQ_EN_IRR) // irr irq
    {
        irdata = GH_PMU_IRR_get_Read();
        irtdata = GH_PMU_IRT_get_Read();

        if (GH_PMU_IRR_getm_Read_VALID() == 1)
        {
            tmp_value = ((irtdata & 0x00000003) | ((irdata << 2) & 0x000000fc));
            if (tmp_value < 0xfC)
            {
                GH_PMU_IRR_set_Prog(0x03);
                tmp_value = ir_count2time(tmp_value);

                IrBuffer[IrWritePointer++] = tmp_value;
                IrDataNumber++;
                IrSeqNumber++;
                IRDataAvailable = 1;
            }
            else if (tmp_value >= 0xfC)
            {
                GH_PMU_IRR_set_Prog(0x02);
                if (IrNotifyFunction)
                {
                    IrNotifyFunction();
                    IrDataNumber    = 0;
                    IrSeqNumber     = 0;
                    IrReadPointer   = 0;
                    IrWritePointer  = 0;
                    IRDataAvailable = 0;
                    memset(&IrBuffer, 0, sizeof(IrBuffer));
                }
            }

            if (IrDataNumber>=IRR_MAX_DATA)
            {
                IrBufferOverApi = 1;
            }
            if (IrWritePointer >= IRR_MAX_DATA)
                IrWritePointer = 0;
        }

        GH_PMU_set_IRQ_CLR_IRR(IRQ_EN_IRR);    // clear irr irq

    }

    if(irq_flag & IRQ_EN_IRT) // irt irq
    {
        GD_IR_ISR_IRT();
        GH_PMU_set_IRQ_CLR_IRT(IRQ_EN_IRT);    // clear irt irq
    }

    if(irq_flag & IRQ_EN_RTC) // rtc irq
    {
        if(RtcNotify)
        {
            RtcIndex ++;
            if(RtcIndex >= RtcPreCount)
            {
                RtcNotify();
                RtcIndex = 0;
            }
        }

        GH_PMU_RTC_set_IRQ_CLEAR(0x01);
        GH_PMU_RTC_set_IRQ_CLEAR(0x00);
        GH_PMU_set_IRQ_CLR_RTC(IRQ_EN_RTC);        // clear rtc irq
    }
}

/******************************************************************************

Name:        irrInitial

Description: This function initialize the variables of IR receiver and reset
             the receiver

Parameters:  None

Returns:     None

******************************************************************************/
static void irrInitial()
{
    GH_PMU_IRR_set_Prog(0x02);
    GH_PMU_IRR_set_IrqMask_h(0xFF);
    GH_PMU_IRR_set_IrqMask_l(0xFF);
    IrDataNumber    = 0;
    IrSeqNumber     = 0;
    IrReadPointer   = 0;
    IrWritePointer  = 0;
    IrBufferOver    = 0;
    IRDataAvailable = 0;
}


/***************************************************************************/
/*                                 InfraRed Transmitter Function                                                   */
/***************************************************************************/
/******************************************************************************
**
** \file      gd_ir_transmit.c
**
** \brief     Infrared transmitter driver.
**
**            (C) Goke Microelectronics China 2002 - 2007
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version   \$Id: gd_ir_transmit.c,v 1.4 2007/06/05 07:56:02 skau Exp $
**
******************************************************************************/


/*---------------------------------------------------------------------------*/
/* local defines                                                             */
/*---------------------------------------------------------------------------*/
#define IRT_COMPLETED               0x01
#define IRT_INPROGRESS              0xFF

#define IRT_GPIO7_IR_IN             (1)
#define IRT_GPIO7_IR_OUT            (0)

/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/
U8      BitData[GD_IR_TRANSFER_MAX_DATA][32];
U8      BitPtr;
U16     NumberInU32;
U8      TransFlag;

/*---------------------------------------------------------------------------*/
/* local functions                                                           */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* local functions                                                           */
/*---------------------------------------------------------------------------*/

/******************************************************************************

Name:        IRT_ConvertData

Description: This function convert the key value to be sent by user

Parameters:  data : key value
             datap: property of this data
             pSendNumber:point to the sending data buffer

Returns:     GD_OK
             GD_ERR_BAD_PARAMETER

******************************************************************************/
GERR IRT_ConvertData(GD_IR_DATA_S* data, GD_IR_DATA_PROPERTY_S* datap,
                        U16* pSendNumber)
{
    U16 i;
    U16 Mask;
    U16 databit;

    if (!(data->validbit))  return GD_ERR_BAD_PARAMETER;
    Mask = 0x01;
    while(Mask < (U16)(1 << (data->validbit)))  //send from bit0 to bit7
    {
        if (data->value & Mask) // 1 -> 1000
        {
            for (i = 0; i < datap->bitvalue1; i++)
            {
                if (BitPtr==32)
                {
                    (*pSendNumber)++;
                    BitPtr=0;
                }
                databit = ((datap->nValidbit1) >> ((datap->bitvalue1)-1-i)) & 0x01;
                BitData [*pSendNumber][BitPtr++] = databit;
            }
        }
        else    // 0 -> 10
        {
            for (i = 0; i < datap->bitvalue0; i++)
            {
                 if (BitPtr==32)
                 {
                    (*pSendNumber)++;
                    BitPtr=0;
                 }
                 databit = ((datap->nValidbit0) >> ((datap->bitvalue0)-1-i)) & 0x01;
                 BitData [*pSendNumber][BitPtr++] = databit;
            }
        }

        Mask <<= 1;

    }

    return GD_OK;

}


/******************************************************************************

Name:        IRT_GetStatus

Description: Status of IR transmitter.

Parameters:  None

Returns:     None

******************************************************************************/
GERR IRT_GetStatus(U16 *pNum)
{
    if( TransFlag == IRT_COMPLETED)
    {
        *pNum     = NumberInU32;
        TransFlag = 0;
        return GD_OK;
    }
    else
        return GD_ERR_IR_TRANSMIT_INPROCESS;
}

/*!
******************************************************************************

Name:        IRT_InsertPulse

Description: This function insert the header of footer of waveform to be sent

Parameters:  number : the number of logic 0 or 1
             bool   : logic of 0 or 1
             pSendNumber: the number of 32bit word to be sent

Returns:     GD_OK

******************************************************************************/
GERR IRT_InsertPulse(U16 number,U8 bool,U16* pSendNumber)
{
    U16 i;

    for (i=0;i<number;i++) {
        if (BitPtr==32) {
            (*pSendNumber)++;
            BitPtr=0;
        }
        BitData [*pSendNumber][BitPtr++]= bool;
    }
    return GD_OK;
}

/*---------------------------------------------------------------------------*/
/* GOKESDK functions                                                         */
/*---------------------------------------------------------------------------*/
/*!
*******************************************************************************
**
** \brief  Converts the input parameters into a 32bit data.
**
**         This function converts the input parameters into the 32bit data,
**         then stores these data into the transmitting buffer.
**         At the same time, it stores the number of these 32bit data.
**
** \param  handle        Handle of the transmitter.
** \param  header        Pointer to the header of the waveform to be sent.
** \param  nheader       Number of pulses in the header.
** \param  data          Pointer to the actual data of the waveform to be sent.
** \param  ndata         Number of data.
** \param  dataproperty  Pointer to the data property of the waveform.
** \param  footer        Pointer to the footer of the waveform to be sent.
** \param  nfooter       Number of pulses in the footer.
** \param  pSendBuffer   Pointer to the buffer to which the upper header,data
**                       data and footer will be stored.
** \param  pSendNumber   Number of 32bit data to be sent.
**
** \return Possible return codes:
**         - #GD_OK
**         - #GD_ERR_INVALID_HANDLE
**         - #GD_ERR_BAD_PARAMETER
**
** \sa     GD_IR_Transmit()
**
******************************************************************************/
GERR GD_IR_SetParams(GD_HANDLE handle,
                     GD_IR_INSERT_S* header,
                     U8 nheader,
                     GD_IR_DATA_S* data,
                     U8 ndata,
                     GD_IR_DATA_PROPERTY_S* dataproperty,
                     GD_IR_INSERT_S* footer,
                     U8 nfooter,
                     U32* pSendBuffer,
                     U16* pSendNumber)
{
    U16 i;
    U8  j;
    GERR stat;
    U32 temp;

    if  (handle != GD_IR_TRANSMITTER )
        return  GD_ERR_INVALID_HANDLE;

    *pSendNumber=0; BitPtr=0;
    while(nheader--)
    {
        IRT_InsertPulse (header->number,header->bit,pSendNumber);
        header++;
    };
    while(ndata--)
    {
        stat =  IRT_ConvertData(data,dataproperty,pSendNumber) ;
        if (stat)  return GD_ERR_BAD_PARAMETER;
        data++;
    };
    while(nfooter--)
    {
        IRT_InsertPulse (footer->number,footer->bit,pSendNumber);
        footer++;
    };
    *pSendNumber = (*pSendNumber)+1;
    if(*pSendNumber > GD_IR_TRANSFER_MAX_DATA)
    {
        return GD_ERR_OUT_OF_MEMORY;
    }

    for (i=0;i<*pSendNumber;i++)
    {
        temp = 0;
        for (j=0;j<32;j++)
            temp |= (BitData [i][j]<<(31-j));
        *pSendBuffer = temp;
        pSendBuffer++;
    }

    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Starts the transmission of infrared data.
**
**         This function transfers the data into the internal buffer of the
**         transmitter and starts the transmission.
**
** \param  wData   the data to be sent.
**
**
******************************************************************************/
void GD_IR_Set_Irt_Transmit0(U32 wData)
{
    GH_PMU_IRT_set_Transmit0_0_VALUE((U8)((wData >> 0) & 0xff));
    GH_PMU_IRT_set_Transmit0_1_VALUE((U8)((wData >> 8) & 0xff));
    GH_PMU_IRT_set_Transmit0_2_VALUE((U8)((wData >> 16) & 0xff));
    GH_PMU_IRT_set_Transmit0_3_VALUE((U8)((wData >> 24) & 0xff));
}

/*!
*******************************************************************************
**
** \brief  Starts the transmission of infrared data.
**
**         This function transfers the data into the internal buffer of the
**         transmitter and starts the transmission.
**
** \param  wData   the data to be sent.
**
**
******************************************************************************/
void GD_IR_Set_Irt_Transmit1(U32 wData)
{
    GH_PMU_IRT_set_Transmit1_0_VALUE((U8)((wData >> 0) & 0xff));
    GH_PMU_IRT_set_Transmit1_1_VALUE((U8)((wData >> 8) & 0xff));
    GH_PMU_IRT_set_Transmit1_2_VALUE((U8)((wData >> 16) & 0xff));
    GH_PMU_IRT_set_Transmit1_3_VALUE((U8)((wData >> 24) & 0xff));
}

/*!
*******************************************************************************
**
** \brief  Starts the transmission of infrared data.
**
**         This function transfers the data into the internal buffer of the
**         transmitter and starts the transmission.
**
** \param  wData   the data to be sent.
**
**
******************************************************************************/
void GD_IR_Set_Irt_Transmit2(U32 wData)
{
    GH_PMU_IRT_set_Transmit2_0_VALUE((U8)((wData >> 0) & 0xff));
    GH_PMU_IRT_set_Transmit2_1_VALUE((U8)((wData >> 8) & 0xff));
    GH_PMU_IRT_set_Transmit2_2_VALUE((U8)((wData >> 16) & 0xff));
    GH_PMU_IRT_set_Transmit2_3_VALUE((U8)((wData >> 24) & 0xff));
}

/*!
*******************************************************************************
**
** \brief  Starts the transmission of infrared data.
**
**         This function transfers the data into the internal buffer of the
**         transmitter and starts the transmission.
**
** \param  wData   the data to be sent.
**
**
******************************************************************************/
void GD_IR_Set_Irt_Transmit3(U32 wData)
{
    GH_PMU_IRT_set_Transmit3_0_VALUE((U8)((wData >> 0) & 0xff));
    GH_PMU_IRT_set_Transmit3_1_VALUE((U8)((wData >> 8) & 0xff));
    GH_PMU_IRT_set_Transmit3_2_VALUE((U8)((wData >> 16) & 0xff));
    GH_PMU_IRT_set_Transmit3_3_VALUE((U8)((wData >> 24) & 0xff));
}

/*!
*******************************************************************************
**
** \brief  Starts the transmission of infrared data.
**
**         This function transfers the data into the internal buffer of the
**         transmitter and starts the transmission.
**
** \param  wData   the data to be sent.
**
**
******************************************************************************/
void GD_IR_Set_Irt_Data(U32 index, U32 wData)
{
    switch(index)
    {
        case 0:
            GD_IR_Set_Irt_Transmit0(wData);
            break;
        case 1:
            GD_IR_Set_Irt_Transmit1(wData);
            break;
        case 2:
            GD_IR_Set_Irt_Transmit2(wData);
            break;
        case 3:
            GD_IR_Set_Irt_Transmit3(wData);
            break;
        default:
#ifdef DEBUG_PRINT
            GM_Printf("%s:Error Index(0 ~ 3) = %d\n",__FUNCTION__, index);
#endif
            break;
    }
}

/*!
*******************************************************************************
**
** \brief  Starts the transmission of infrared data.
**
**         This function transfers the data into the internal buffer of the
**         transmitter and starts the transmission.
**
** \param  handle  Handle of transmitter.
** \param  pData   Pointer to the data to be sent.
** \param  num     Number of data values.
**
** \return Possible return codes:
**         - #GD_OK
**         - #GD_ERR_INVALID_HANDLE
**
******************************************************************************/
GERR GD_IR_Transmit(GD_HANDLE handle, U32 *pData, U16 num)
{
    U16 i;

    if  (handle != GD_IR_TRANSMITTER )
        return  GD_ERR_INVALID_HANDLE;

    NumberInU32 = num;

#ifdef DEBUG_PRINT
    GM_Printf("SendNum = %d\n", num);
#endif

    GH_PMU_set_SYS_REG_CFG1_GPIO7(IRT_GPIO7_IR_OUT);

    for(i = 0; i < num; i++)
    {
        GD_IR_Set_Irt_Data(i, pData[i]);
    }

    GH_PMU_IRT_set_Start_START_TX(1);

    TransFlag = IRT_INPROGRESS;

    return GD_OK;

}

/******************************************************************************

Name:        IRT_IrqHandler

Description: IRQ handler of IR transmitter.

Parameters:  None

Returns:     None

******************************************************************************/
void GD_IR_ISR_IRT(void)
{
    BitPtr    = 0;
    TransFlag = IRT_COMPLETED;
    GH_PMU_set_SYS_REG_CFG1_GPIO7(IRT_GPIO7_IR_IN);
}


/******************************************************************************

Name:        IRT_Initial

Description: This function initialize the variables of IR transmitter

Parameters:  None

Returns:     None

******************************************************************************/





/*!
*******************************************************************************
**
** \brief  Opens IR transmitter.
**
** \param  openParams  Pointer to configuration parameters.
** \param  handle      Pointer to handle assigned to the opened instance.
**
******************************************************************************/
GERR GD_IR_IrtOpen(GD_IR_OPEN_PARAMS_S *pOpenParams, GD_HANDLE *pHandle)
{
    GERR err = GD_ERR_BAD_PARAMETER;
    unsigned int prescaler = (U32)pOpenParams->irt_config_s.prescaler;

    if( pOpenParams != NULL )
    {
        if((Ir_Status & GD_IR_TRANSMITTER_OPENED) == GD_IR_TRANSMITTER_OPENED)
            return  GD_ERR_ALREADY_OPEN;

        /* set transmit prescaler */
        GH_PMU_IRT_set_Sent_Clock_h_VALUE((U8)((prescaler >> 8) & 0xff));
        GH_PMU_IRT_set_Sent_Clock_l_VALUE((U8)(prescaler & 0xff));

        /* set IR shift clock */
        GH_PMU_IRT_set_Shift_Clock_VALUE(pOpenParams->irt_config_s.shift_counter);

        /* set IR TX mode */
        GH_PMU_IRT_set_Sent_Conf(pOpenParams->irt_config_s.programming);

        /* set IRT compare value */
        GH_PMU_IRT_set_Compvalue_VALUE(pOpenParams->irt_config_s.compare_value);

        BitPtr    = 0;
        TransFlag = 0;

        /* update the IR status */
        Ir_Status |= GD_IR_TRANSMITTER_OPENED;

        *pHandle = GD_IR_TRANSMITTER;

        err = GD_OK;

    }

    return err;

}

