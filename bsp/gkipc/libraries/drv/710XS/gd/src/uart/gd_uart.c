/******************************************************************************
**
** \file      gd_uart.c
**
** \brief     UART driver.
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

/* Enable this if you want to use the UART rx IRQ.
   The GD_UART_Read function waits in both cases until "bufferSize" chars are
   received. The main difference is that when using interrupts a notify
   function can be used to read a byte (trying to read more than 1 byte does
   not make sense because then the time for the second ... bytes will be wasted
   in the GD_UART_Read function again). */

#include <stdio.h>
#include <string.h>

#include "gtypes.h"
#include "gbitdefs.h"

#include "gh_uart.h"
#include "gh_debug_rct.h"

#include "gd_uart.h"
#include "gd_int.h"
#include "gd_gpio.h"
#include "gd_timer.h"

#ifndef USE_RT_DRIVER_FRAMEWORK

/*---------------------------------------------------------------------------*/
/* private data declarations                                                 */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* local defines                                                             */
/*---------------------------------------------------------------------------*/

#define UART_IRQ_CLEAR_ALL   0x3 /* IRQ CLR Register: rx_IRQ, rx_parity_IRQ  */
#define UART_RISING_TXE_RXE  0x3 /* for UART_control register:               */
                                 /* clock edge polarity = rising,            */
                                 /* TX = enable, RX = enable                 */

/* UART[x]_FC_REG */
#define UART_FC_RX_ONECHAR              0x0 /* RCVR_Trigger: FIFO has 1 char */
#define UART_FC_RX_QUARTER_FULL         0x1 /* RCVR_Trigger: FIFO is one-fourth to full */
#define UART_FC_RX_HALF_FULL            0x2 /* RCVR_Trigger: FIFO is half to full */
#define UART_FC_RX_2_TO_FULL            0x3 /* RCVR_Trigger: FIFO is 2 char to full */
#define UART_FC_TX_EMPTY                0x0 /* TX_Empty_Trigger:  FIFO is empty */
#define UART_FC_TX_2_IN_FIFO            0x1 /* TX_Empty_Trigger:  FIFO has 2 char */
#define UART_FC_TX_QUATER_IN_FIFO       0x2 /* TX_Empty_Trigger:  FIFO is one-fourth to full */
#define UART_FC_TX_HALF_IN_FIFO         0x3 /* TX_Empty_Trigger:  FIFO is half to full */

/* UART[x]_II_REG */
#define UART_II_MODEM_STATUS_CHANGED    0x0
#define UART_II_NO_INT_PENDING          0x1
#define UART_II_THR_EMPTY               0x2
#define UART_II_RCV_DATA_AVAIL          0x4
#define UART_II_RCV_STATUS              0x6
#define UART_II_CHAR_TIMEOUT            0xc

/*---------------------------------------------------------------------------*/
/* local data types                                                          */
/*---------------------------------------------------------------------------*/

typedef struct
{
    U32  IRQStatus;  //!< content of IRQ status register.
} UART_DATA_S;


/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/
static U8  CvsVersion[] = "$Revision: 1.1 $"; /* filled by CVS */
static U8  InitDone = 0;
static GD_HANDLE            intHandle;
static GD_HANDLE            int1Handle;
static GD_HANDLE            int2Handle;
//static U32                  uart_intr_flag = 0;

static GD_UART_STATE_MACHINE_S g_uart_state_machine_data[GD_UART_COUNT];
static U8 g_uart0_rx_buffer[UART0_RX_BUF_SIZE];
static U8 g_uart0_tx_buffer[UART0_TX_BUF_SIZE];
static U8 g_uart1_rx_buffer[UART1_RX_BUF_SIZE];
static U8 g_uart1_tx_buffer[UART1_TX_BUF_SIZE];
static U8 g_uart2_rx_buffer[UART2_RX_BUF_SIZE];
static U8 g_uart2_tx_buffer[UART2_TX_BUF_SIZE];

//0111 hhl add
static void uartProcessor(void* data);
static void uart1Processor(void* data);
static void uart2Processor(void* data);
static GISR1 uartISR(void);
static GISR1 uart1ISR(void);
static GISR1 uart2ISR(void);
static GD_INT_DATA_S* uartHandler(void);
static GD_INT_DATA_S* uart1Handler(void);
static GD_INT_DATA_S* uart2Handler(void);
GERR GD_UART_Set_IntMode(U8 channel);
int GM_Printf(const char * __format,...);
GERR GD_UART_Transmit_Chars(GD_UART_STATE_MACHINE_S *handle);
GERR GD_UART_Receive_Chars(GD_UART_STATE_MACHINE_S *handle, U32 timeout);


#if 0
static const U32 BaudRateTable[] = {
    /* baudrate            clk bound  delta 1  diff delta       mode*/
    GD_UART_BAUD_RATE110,    15339,     10,      1,            /* 0 */
    GD_UART_BAUD_RATE300,    5624,      0,       1,            /* 1 */
    GD_UART_BAUD_RATE1200,   1405,      1,       3,            /* 2 */
    GD_UART_BAUD_RATE2400,   702,       1,       7,            /* 3 */
    GD_UART_BAUD_RATE4800,   350,       9,       7,            /* 4 */
    GD_UART_BAUD_RATE9600,   174,       25,      7,            /* 5 */
    GD_UART_BAUD_RATE19200,  86,        57,      7,            /* 6 */
    GD_UART_BAUD_RATE38400,  42,        121,     7,            /* 7 */
    GD_UART_BAUD_RATE57600,  28,        19,      45,           /* 8 */
    GD_UART_BAUD_RATE115200, 13,        83,      45,           /* 9 */
    GD_UART_BAUD_RATE230400, 6,         83,      173,          /* a */
    GD_UART_BAUD_RATE460800, 2,         0x153,   173,          /* b */
    GD_UART_BAUD_RATE921600, 0,         0x1aa,   0x57,          /* c */
    0
};
#endif

/*---------------------------------------------------------------------------*/
/* local  functions                                                          */
/*---------------------------------------------------------------------------*/
static GERR     uartCheckParams(GD_UART_PARAMS_S *paramsP);

#if 0
static GISR1           uartISR(void);
static GISR1           uart1ISR(void);
static GD_INT_DATA_S*  uartHandler(void);
static GD_INT_DATA_S*  uart1Handler(void);
static void            uartProcessor(void* data);
static void            uart1Processor(void* data);
#endif

/*!
*******************************************************************************
**
** \brief  Checks the Rx buffer of the UART.
**
** Checks if RX buffer has received data. This is useful if no RTOS
** is used to avoid blocking calls of read function (\c GD_UART_Read()
** will then not be called until character is inside).
**
** \param handle Valid handle of the UART driver instance.
** \param dataAvailable Pointer to a boolean where the status of the
**                      Rx buffer will be stored:
**                      - \c #GFALSE if  receive buffer is empty
**                      - \c #GTRUE  if  receive buffer contains data
**
** \return One of the following status codes:
**         - \c #GD_OK if successful
**         - \c #GD_ERR_INVALID_HANDLE if the given handle is invalid.
**
******************************************************************************/
GERR GD_UART_CheckRxBuffer(GD_HANDLE handle, GBOOL *dataAvailable)
{
    U8 ret = GD_OK;
    GD_UART_STATE_MACHINE_S* uart_handle_ptr = NULL;

    if(handle == NULL)
        return GD_ERR_BAD_PARAMETER;

    if(dataAvailable == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }


    uart_handle_ptr = (GD_UART_STATE_MACHINE_S *)handle;
    if(uart_handle_ptr->inUse == GFALSE)
        return GD_ERR_NOT_INITIALIZED;

    *dataAvailable = GFALSE;


    if(uart_handle_ptr->interruptEnable)
    {
        if(uart_handle_ptr->RxBufRead != uart_handle_ptr->RxBufWrite)
        {
            *dataAvailable = GTRUE;
        }
        else
        {
            *dataAvailable = GFALSE;
        }
    }
    else
    {
        ret = GH_UART_get_LSR_dr(uart_handle_ptr->channel);
        if(ret == 0)
        {
            *dataAvailable = GFALSE;
        }
        else
        {
            *dataAvailable = GTRUE;
        }
    }

    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Closes an instance of the UART driver.
**
** \param handleP Pointer to the handle of the UART driver instance to be
**                closed
**
** \return One of the following status codes:
**         - \c #GD_OK if successful
**         - \c #GD_ERR_INVALID_HANDLE if the given handle is invalid.
**
** \sa GD_UART_Open
******************************************************************************/
GERR GD_UART_Close(GD_HANDLE* handleP)
{
    /* check if handle is valid */
    GD_UART_STATE_MACHINE_S* uart_handle_ptr = NULL;

    if(handleP == NULL)
        return GD_ERR_BAD_PARAMETER;


    uart_handle_ptr = (GD_UART_STATE_MACHINE_S *)(*handleP);

    if(uart_handle_ptr->inUse == GFALSE )
    {
        return GD_ERR_BAD_PARAMETER;
    }

    //GH_UART_set_Cr_Uarten(uart_handle_ptr->channel, 0);
    //GH_UART_set_Imsc_Rxim(uart_handle_ptr->channel, 0);
    //GH_UART_set_Imsc_Txim(uart_handle_ptr->channel, 0);
    //GH_UART_set_Imsc_Rtim(uart_handle_ptr->channel, 0);
    //GH_UART_set_Imsc_Oeim(uart_handle_ptr->channel, 0);

    // exit, to be used if necessary
    // GH_UART_set_Cr_Rxe(uart_handle_ptr->channel, 0);
    // GH_UART_set_Cr_Txe(uart_handle_ptr->channel, 0);
    // GH_UART_set_Cr_Uarten(uart_handle_ptr->channel, 0);
    // GH_UART_set_Imsc(uart_handle_ptr->channel, 0);

    /* handle close */
    uart_handle_ptr ->inUse = GFALSE;
    handleP = NULL;

    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Flushs the UART input buffer.
**
**         This function flushes the input buffer. It removes all data in the
**         input buffers. Discards any data waiting in the input buffers to be
**         read.
**
** \attention This operation will not work when \c GD_UART_Read() is pending.
**
** \param  handle Valid handle of the UART driver instance.
**
** \return One of the following status codes:
**         - \c #GD_OK if successful
**         - \c #GD_ERR_INVALID_HANDLE if the given handle is invalid.
**         - \c #GD_ERR_DEVICE_BUSY if the UART device is currently busy.
**
** \sa GD_UART_Read
******************************************************************************/
GERR GD_UART_Flush(GD_HANDLE handle)
{
    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Get current UART connection parameter.
**
** Get the currently active parameters for the UART driver instance.
** Copies the parameters currently in use to the user allocated
** Parameters structure.
**
** \param  handle  Valid handle of the UART driver instance.
** \param  paramsP Pointer to parameter structure that should be filled.
**
** \return One of the following status codes:
**         - \c #GD_OK if successful
**         - \c #GD_ERR_INVALID_HANDLE if the given handle is invalid.
**
******************************************************************************/
GERR GD_UART_GetParams(GD_HANDLE handle, GD_UART_PARAMS_S *paramsP)
{
    /* check if handle is valid */
    GD_UART_STATE_MACHINE_S* uart_handle_ptr = NULL;

    if(handle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    if(paramsP == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    uart_handle_ptr = (GD_UART_STATE_MACHINE_S *)handle;
    if(uart_handle_ptr->inUse == GFALSE)
        return GD_ERR_NOT_INITIALIZED;

    paramsP->dataRate    = uart_handle_ptr->SetParamsData.dataRate;
    paramsP->numDataBits = uart_handle_ptr->SetParamsData.numDataBits;
    paramsP->numStopBits = uart_handle_ptr->SetParamsData.numStopBits;
    paramsP->parity      = uart_handle_ptr->SetParamsData.parity;
    paramsP->protocol    = uart_handle_ptr->SetParamsData.protocol;

    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Get the actual baud rate of the UART device.
**
** Get the actual baud rate currently used by the device.
** The UART normally derives its baudrate from the CPU clock.
** Although the UART driver will always calculate the optimal clock
** divisor value, depending on the CPU clock speed, division
** rounding errors may cause the actual baud rate to differ from the
** ideal (required) baudrate.
**
** In practice this error will only be small (less than 4%) but in
** some cases (for higher baud rates where the sampling times are
** much less) it may be large enough to cause communications errors.
**
** For this reason it is useful to be able to access the actual
** baud rate being used.
**
** \param  handle Valid handle of the UART driver instance.
** \param  rateP Pointer where the actual baud rate should be stored.
**
** \return One of the following status codes:
**         - \c #GD_OK if successful
**         - \c #GD_ERR_INVALID_HANDLE if the given handle is invalid.
**
******************************************************************************/
GERR GD_UART_GetRealBaudRate(GD_HANDLE handle, U32 *rateP)
{
    GD_UART_STATE_MACHINE_S* uart_handle_ptr = NULL;
    /* check if handle is valid */
    if(handle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    if(rateP ==  NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    uart_handle_ptr = (GD_UART_STATE_MACHINE_S *)handle;

    if(uart_handle_ptr->inUse == GFALSE)
        return GD_ERR_NOT_INITIALIZED;

    *rateP = uart_handle_ptr->RealBaudRate;

    return GD_OK;
}
/*!
*******************************************************************************
**
** \brief  Get the current driver version.
**
** \return Pointer to the version string.
**
******************************************************************************/
U8 *GD_UART_GetRevisionString(void)
{
    return(CvsVersion);
}

/*!
*******************************************************************************
**
** \brief  Get statistical information of the UART device.
**
** Get communication informations, number of transmitted characters,
** received caharacters and parity errors.
**
** \param  handle Valid handle of the UART driver instance.
** \param  statisticsP Pointer where the statistical information should be
**                     stored.
**
** \return One of the following status codes:
**         - \c #GD_OK if successful
**         - \c #GD_ERR_INVALID_HANDLE if the given handle is invalid.
**
******************************************************************************/
GERR GD_UART_GetStatistics(GD_HANDLE handle, GD_UART_STATISTICS *statisticsP)
{
    GD_UART_STATE_MACHINE_S* uart_handle_ptr = NULL;

    /* check if handle is valid */
    if(handle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    if(statisticsP ==  NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }
    uart_handle_ptr = (GD_UART_STATE_MACHINE_S *)handle;
    if(uart_handle_ptr->inUse == GFALSE)
        return GD_ERR_NOT_INITIALIZED;

    *statisticsP = uart_handle_ptr->UartStatics;

    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Initializes the driver.
**
**         This function initializes the UART driver. It initializes the
**         internal variables and registers the UART interrupt.
**
** \param initParamsP Pointer to UART init data structure containing all
**                   customizable driver parameter.
**
** \return One of the following status codes:
**         - \c #GD_OK if successful
**         - \c #GD_ERR_ALREADY_INITIALIZED if this function has already been
**                                       called.
**         - \c #GD_ERR_BAD_PARAMETER if the initialization parameter are
**                                 not correctly specified.
******************************************************************************/
GERR GD_UART_Init(GD_UART_INIT_PARAMS_S *initParamsP)
{
    GERR                 ret;
    U8 channelIndex = 0;

    /* check if already initialized */
    if(InitDone != 0)
    {
        return GD_ERR_ALREADY_INITIALIZED;
    }
    if(initParamsP == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    for (channelIndex = 0; channelIndex < GD_UART_COUNT; channelIndex++)
    {
        memset(&g_uart_state_machine_data[channelIndex], 0, sizeof(GD_UART_STATE_MACHINE_S));
    }

    GH_PLL_set_SCALER_UART_Div(0x1);//div_uart = 1
    
    g_uart_state_machine_data[0].RxBuffer = g_uart0_rx_buffer;
    g_uart_state_machine_data[0].TxBuffer = g_uart0_tx_buffer;
    g_uart_state_machine_data[1].RxBuffer = g_uart1_rx_buffer;
    g_uart_state_machine_data[1].TxBuffer = g_uart1_tx_buffer;
    g_uart_state_machine_data[2].RxBuffer = g_uart2_rx_buffer;
    g_uart_state_machine_data[2].TxBuffer = g_uart2_tx_buffer;
    
    g_uart_state_machine_data[0].RxBufSize = UART0_RX_BUF_SIZE;
    g_uart_state_machine_data[0].TxBufSize = UART0_TX_BUF_SIZE;
    g_uart_state_machine_data[1].RxBufSize = UART1_RX_BUF_SIZE;
    g_uart_state_machine_data[1].TxBufSize = UART1_TX_BUF_SIZE;
    g_uart_state_machine_data[2].RxBufSize = UART2_RX_BUF_SIZE;
    g_uart_state_machine_data[2].TxBufSize = UART2_TX_BUF_SIZE;

    for(channelIndex = 0;channelIndex < GD_UART_COUNT;channelIndex ++)
    {
        /* initialize driver information */
        g_uart_state_machine_data[channelIndex].UartStatics.numTransmittedChar = 0;
        g_uart_state_machine_data[channelIndex].UartStatics.numReceivedChar    = 0;
        g_uart_state_machine_data[channelIndex].UartStatics.numParityError     = 0;
        g_uart_state_machine_data[channelIndex].interruptEnable = 0;
        g_uart_state_machine_data[channelIndex].inUse = GFALSE;
        g_uart_state_machine_data[channelIndex].channel = channelIndex;

        GH_UART_set_FCR(channelIndex, 0);
    }

    for(channelIndex = 0;channelIndex < GD_UART_COUNT;channelIndex ++)
    {
        /* init GD_UART_PARAMS */
        ret = GD_UART_SetParams((GD_HANDLE)(g_uart_state_machine_data + channelIndex), initParamsP->defaultParamsP);
        if(ret != GD_OK) return ret;

        GH_UART_set_THR_Data(g_uart_state_machine_data[channelIndex].channel, 0);

        g_uart_state_machine_data[channelIndex].RxBufWrite = 0;
        g_uart_state_machine_data[channelIndex].RxBufRead  = 0;
        g_uart_state_machine_data[channelIndex].RxBufCounter  = 0;
        g_uart_state_machine_data[channelIndex].TxBufWrite = 0;
        g_uart_state_machine_data[channelIndex].TxBufRead  = 0;
        g_uart_state_machine_data[channelIndex].TxBufCounter  = 0;


        g_uart_state_machine_data[channelIndex].NotifyFunction = initParamsP->notifyFunction;

        GD_UART_Flush((GD_HANDLE)(g_uart_state_machine_data + channelIndex)); /* empty receive register */
    }

    InitDone++;

    return GD_OK;
}


/*!
*******************************************************************************
**
** \brief  Opens an instance of the UART driver.
**
** \param openParamsP Pointer to the parameters to be applied when opening
**                    the driver or \c NULL if default parameter should
**                    be used.
** \param handleP Pointer where the handle of the UART driver instance should
**                be stored.
**
** \return One of the following status codes:
**         - \c #GD_OK if successful
**         - \c #GD_ERR_BAD_PARAMETER if the initialization parameter are not
**                                 correctly specified.
**         - \c #GD_ERR_ALREADY_OPEN  if the UART device has already been opened.
**
** \sa GD_UART_Close
******************************************************************************/
GERR GD_UART_Open(GD_UART_OPEN_PARAMS_S *openParamsP, GD_HANDLE *handleP)
{
    GERR ret;
    GD_UART_STATE_MACHINE_S* uart_handle_ptr = NULL;

    if(handleP == NULL)
        return GD_ERR_BAD_PARAMETER;

    if(openParamsP == NULL)
        return GD_ERR_BAD_PARAMETER;

    /* check if already opened */
    if(g_uart_state_machine_data[openParamsP->channel].inUse == GTRUE)
    {
        //1216 hhl add for uart2 test
        *handleP = (GD_HANDLE)(&(g_uart_state_machine_data[openParamsP->channel]));
        return GD_ERR_ALREADY_OPEN;
    }

    *handleP = (GD_HANDLE)(&(g_uart_state_machine_data[openParamsP->channel]));

    uart_handle_ptr = (GD_UART_STATE_MACHINE_S *)(*handleP);
    uart_handle_ptr->inUse = GTRUE;
    uart_handle_ptr->interruptEnable = openParamsP->interruptEnable;


    /* set user requested parameters */
    if( ( openParamsP != NULL ) && ( openParamsP->paramsP != NULL ) )
    {
        /* set open parameters */
        ret = GD_UART_SetParams(*handleP, openParamsP->paramsP);
        if(ret != GD_OK)
            return ret;

        //if(openParamsP->paramsP->protocol == GD_UART_HARDWARE) /* use CTS/RTS protocol */
    }
    
    if (openParamsP->NotifyFunction)
    {
        uart_handle_ptr->NotifyFunction = openParamsP->NotifyFunction;
    }
    if(uart_handle_ptr->interruptEnable)
    {        
        GH_UART_set_FCR_FIFO_Enable(uart_handle_ptr->channel, 1);
        GH_UART_set_FCR_RCVR_Trigger(uart_handle_ptr->channel, UART_FC_RX_2_TO_FULL);
        GH_UART_set_FCR_TX_Empty_Trigger(uart_handle_ptr->channel, UART_FC_TX_EMPTY);
        GH_UART_set_FCR_XMIT_FIFO_Reset(uart_handle_ptr->channel, 1);
        GH_UART_set_FCR_RCVR_FIFO_Reset(uart_handle_ptr->channel, 1);
        
        GH_UART_set_IER_etbei(uart_handle_ptr->channel, 0); //Turn off THRE interrupt

        //0108 hhl add for interrupt-mode test
        /*************0108 hhl add (head)***********/
        GD_UART_Set_IntMode(uart_handle_ptr->channel);
        if(uart_handle_ptr->channel == 0)
        {
            GD_INT_Enable(&intHandle,1);
            GH_UART_set_IER_erbfi(0,1);
            GH_UART_set_IER_elsi(0,1);
        }
        else if(uart_handle_ptr->channel == 1)
        {
            GD_INT_Enable(&int1Handle,1);
            GH_UART_set_IER_erbfi(1,1);
            GH_UART_set_IER_elsi(1,1);
        }
        else
        {
            GD_INT_Enable(&int2Handle,1);
            GH_UART_set_IER_erbfi(2,1);
            GH_UART_set_IER_elsi(2,1);
        }
        /*************0108 hhl add (end)***********/
        
    }
    else
		GH_UART_set_FCR_FIFO_Enable(uart_handle_ptr->channel, 1);

    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Reads data from the UART driver.
**
** Reads data of a driver instance and copies them into the destination
** buffer. Only when data are available the driver returns with success.
**
** \param  handle Valid handle of the UART driver instance.
** \param  bufferP Pointer to the destination buffer where data should be
**                 copied into.
** \param  bufferSize Length of destination buffer.
** \param  receivedSize Pointer to store the actual received bytes in this function call.
** It is only suitable for uart interrupt mode read, for polling mode, it can be set to NULL.
**
** \return One of the following status codes:
**         - \c #GD_OK if successful
**         - \c #GD_ERR_INVALID_HANDLE if the given handle is invalid.
**
** \sa GD_UART_Write
******************************************************************************/
GERR GD_UART_Read(GD_HANDLE handle, U8 *bufferP, U16 desiredReadBytes, U16 *actualReceivedBytesP)
{
    U16  i;
    U8   ret;
    GD_UART_STATE_MACHINE_S* uart_handle_ptr = NULL;

    if(handle == NULL)
        return GD_ERR_BAD_PARAMETER;

    if(bufferP == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    uart_handle_ptr = (GD_UART_STATE_MACHINE_S *)handle;
    if(uart_handle_ptr->inUse == GFALSE)
        return GD_ERR_NOT_INITIALIZED;

    if(uart_handle_ptr->interruptEnable )
    {
        if (uart_handle_ptr->RxBufRead == uart_handle_ptr->RxBufWrite)
        {
            if (uart_handle_ptr->RxBufCounter == 0)
            {
                if (actualReceivedBytesP != NULL)
                {
                    *actualReceivedBytesP = 0;
                }
                return GD_ERR_BUFFER_EMPTY;    //  RX_buffer is empty
            }
            else if (uart_handle_ptr->RxBufCounter >= uart_handle_ptr->RxBufSize)
            {
                // TODO: RX_buffer is overflow
            }
            else
            {
                return GD_ERR_OUT_OF_MEMORY;    //  RX_buffer state is abnormal
            }
        }
        i = 0;
        /* wait for enough bytes from interrupt routine */
        while ((i < desiredReadBytes) && (uart_handle_ptr->RxBufRead != uart_handle_ptr->RxBufWrite))
        {
            bufferP[i] = uart_handle_ptr->RxBuffer[uart_handle_ptr->RxBufRead++];
            i++;
            uart_handle_ptr->UartStatics.numReceivedChar++;
            if(uart_handle_ptr->RxBufCounter)
            {
                uart_handle_ptr->RxBufCounter--;
            }
            if (uart_handle_ptr->RxBufRead >= uart_handle_ptr->RxBufSize)
            {
                uart_handle_ptr->RxBufRead = 0;
            }
        }
        if (actualReceivedBytesP != NULL)
        {
            *actualReceivedBytesP = i;
        }
    }
    else
    {
        for(i=0; i<desiredReadBytes; i++)
        {
            /* TODO: blocking call... */
            do
            {
                ret = GH_UART_get_LSR_dr(uart_handle_ptr->channel);
            }while (!ret); /* while RX buffer empty */

            *bufferP++ = GH_UART_get_RBR_Data(uart_handle_ptr->channel);

            uart_handle_ptr->UartStatics.numReceivedChar++;
        }
        if (actualReceivedBytesP != NULL)
        {
            *actualReceivedBytesP = desiredReadBytes;
        }
    }
    return GD_OK;
}


//0108 hhl add new function for interrupt-mode test
/***************0108 hhl add (head)**************/
GERR GD_UART_Set_IntMode(U8 channel)
{
    
    GD_UART_STATE_MACHINE_S* uart_handle_ptr = NULL;
    GD_INT_OPEN_PARAMS_S intParams;
    GD_INT_HANDLER_F uartP = uartHandler;
    GD_INT_HANDLER_F uart1P = uart1Handler;
    GD_INT_HANDLER_F uart2P = uart2Handler;
    GERR                 ret = GD_OK;
    
    if(channel>2)
        return GD_ERR_BAD_PARAMETER;
    
    uart_handle_ptr = &(g_uart_state_machine_data[channel]);
    if(uart_handle_ptr->inUse == GFALSE)
        return GD_ERR_NOT_INITIALIZED;
    
    if(uart_handle_ptr->interruptEnable )
    {
        //if(uart_intr_flag == 0)
        //{ 
            intParams.sensitivity    = GD_INT_LEVEL_HIGH;    //hhl note: check this value.
            intParams.active         = GD_INT_INVERT_IRQ;
            intParams.priority       = GD_INT_MID_PRIORITY;
            
            if(channel == 0)
            {
                intParams.type           = (S8)GD_INT_UART_IRQ;
                intParams.isrFct.lowPrio = uartISR;
                ret = GD_INT_Open(&intParams, &intHandle);
            }
            else if(channel == 1)
            {
                intParams.type           = (S8)GD_INT_UART1_IRQ;
                intParams.isrFct.lowPrio = uart1ISR;
                ret = GD_INT_Open(&intParams, &int1Handle);
            }
            else
            {
                intParams.type           = (S8)GD_INT_UART2_IRQ;
                intParams.isrFct.lowPrio = uart2ISR;
                ret = GD_INT_Open(&intParams, &int2Handle);
            }
                        
            if(ret != GD_OK) return ret;
    
            /* Register interrupt handler function */
            if(channel == 0)
                GD_INT_SetHandler( intParams.type, uartP );
            else if(channel == 1)
                GD_INT_SetHandler( intParams.type, uart1P );
            else
                GD_INT_SetHandler( intParams.type, uart2P );

        //    uart_intr_flag = 1;
        //}
    
        //GH_UART_set_Imsc_Rxim(uart_handle_ptr->channel, 1);
        //GH_UART_set_Imsc_Txim(uart_handle_ptr->channel, 0);
        //GH_UART_set_Imsc_Rtim(uart_handle_ptr->channel, 1);
        //GH_UART_set_Imsc_Oeim(uart_handle_ptr->channel, 1);
        
        //GH_UART_set_FCR_RCVR_Trigger(uart_handle_ptr->channel, 0);
        //GH_UART_set_FCR_TX_Empty_Trigger(uart_handle_ptr->channel, 3);
    }
    else
    {
        GM_Printf("err call function: GD_UART_Set_IntMode!  \n");
    }
    return ret;
}
/***************0108 hhl add (end)**************/


GERR GD_UART_SetInterruptMode(GD_HANDLE handle, GBOOL enable)
{
    /* check if handle is valid */
#if 0
    GD_UART_STATE_MACHINE_S* uart_handle_ptr = NULL;
    GD_INT_OPEN_PARAMS_S intParams;
    GD_INT_HANDLER_F uartP = uartHandler;
    GD_INT_HANDLER_F uart1P = uart1Handler;
    GERR                 ret = GD_OK;

    if(handle == NULL)
        return GD_ERR_BAD_PARAMETER;

    uart_handle_ptr = (GD_UART_STATE_MACHINE_S *)handle;
    if(uart_handle_ptr->inUse == GFALSE)
        return GD_ERR_NOT_INITIALIZED;

    uart_handle_ptr->interruptEnable = enable;
    if(uart_handle_ptr->interruptEnable )
    {
        if(uart_intr_flag == 0)
        {
            intParams.type           = (S8)GD_INT_UART_IRQ;
            intParams.sensitivity    = GD_INT_LEVEL_SENSITIVE;
            intParams.active         = GD_INT_INVERT_IRQ;
            intParams.priority       = GD_INT_LOW_PRIORITY;
            intParams.isrFct.lowPrio = uartISR;
            ret = GD_INT_Open(&intParams, &intHandle);
            if(ret != GD_OK) return ret;

            /* Register interrupt handler function */
            GD_INT_SetHandler( intParams.type, uartP );

            intParams.type           = (S8)GD_INT_UART_IRQ;
            intParams.isrFct.lowPrio = uart1ISR;
            ret = GD_INT_Open(&intParams, &int1Handle);
            if(ret != GD_OK) return ret;

            /* Register interrupt handler function */
            GD_INT_SetHandler( intParams.type, uart1P );
            uart_intr_flag = 1;
        }

        //GH_UART_set_Imsc_Rxim(uart_handle_ptr->channel, 1);
        //GH_UART_set_Imsc_Txim(uart_handle_ptr->channel, 0);
        //GH_UART_set_Imsc_Rtim(uart_handle_ptr->channel, 1);
        //GH_UART_set_Imsc_Oeim(uart_handle_ptr->channel, 1);
        GH_UART_set_FCR_RCVR_Trigger(uart_handle_ptr->channel, 0);
        GH_UART_set_FCR_TX_Empty_Trigger(uart_handle_ptr->channel, 3);
    }
    else
    {
        //GH_UART_set_Imsc(uart_handle_ptr->channel, 0);
    }
//#else
//0106 hhl add "#else" for int-mode test
GD_UART_STATE_MACHINE_S* uart_handle_ptr = NULL;
GD_INT_OPEN_PARAMS_S intParams;
GD_INT_HANDLER_F uartP = uartHandler;
GD_INT_HANDLER_F uart1P = uart1Handler;
GERR                 ret = GD_OK;

if(handle == NULL)
    return GD_ERR_BAD_PARAMETER;

uart_handle_ptr = (GD_UART_STATE_MACHINE_S *)handle;
if(uart_handle_ptr->inUse == GFALSE)
    return GD_ERR_NOT_INITIALIZED;

uart_handle_ptr->interruptEnable = enable;
if(uart_handle_ptr->interruptEnable )
{
    if(uart_intr_flag == 0)
    {
        intParams.type           = (S8)GD_INT_UART_IRQ;
        intParams.sensitivity    = GD_INT_LEVEL_SENSITIVE;
        intParams.active         = GD_INT_INVERT_IRQ;
        intParams.priority       = GD_INT_LOW_PRIORITY;
        intParams.isrFct.lowPrio = uartISR;
        ret = GD_INT_Open(&intParams, &intHandle);
        if(ret != GD_OK) return ret;

        /* Register interrupt handler function */
        GD_INT_SetHandler( intParams.type, uartP );

        intParams.type           = (S8)GD_INT_UART_IRQ;
        intParams.isrFct.lowPrio = uart1ISR;
        ret = GD_INT_Open(&intParams, &int1Handle);
        if(ret != GD_OK) return ret;

        /* Register interrupt handler function */
        GD_INT_SetHandler( intParams.type, uart1P );
        uart_intr_flag = 1;
    }

    //GH_UART_set_Imsc_Rxim(uart_handle_ptr->channel, 1);
    //GH_UART_set_Imsc_Txim(uart_handle_ptr->channel, 0);
    //GH_UART_set_Imsc_Rtim(uart_handle_ptr->channel, 1);
    //GH_UART_set_Imsc_Oeim(uart_handle_ptr->channel, 1);
    GH_UART_set_FCR_RCVR_Trigger(uart_handle_ptr->channel, 0);
    GH_UART_set_FCR_TX_Empty_Trigger(uart_handle_ptr->channel, 3);
}
else
{
    //GH_UART_set_Imsc(uart_handle_ptr->channel, 0);
}

#endif
    return GD_OK;
}

/*
********************************************************************************
** \brief Sets a new baudrate
**
** This function sets the given baudrate value for the requested UART block.
** It accepts baudrate values in the range from #GOKESDK_UART_BAUDRATE_2400
** upto #GOKESDK_UART_BAUDRATE_460800.
**
** \param index The UART block to access, either '0' or '1'
** \param baudRate The baudrate value to write into the UART block
**
** \return
** - (1) if baudRate was successfully set
** - (0) if either the index or the baudRate is out of range
********************************************************************************
*/
static void uartSetBaudrate(U32 index, U32 baudRate)
{
    U32 brdi;
    GH_PLL_set_SCALER_UART(0x01);
    brdi = GD_GET_UART_ClkHz() * 10 / baudRate / 16;
    if (brdi % 10 >= 5)
        brdi = (brdi / 10) + 1;
    else
        brdi = (brdi / 10);
    GH_UART_set_LCR_dlab(index, 1);
    GH_UART_set_DLL_BaudDivint_L(index, brdi & 0xff);
    GH_UART_set_DLH_BaudDivint_H(index, (brdi >> 8) & 0xff);
    GH_UART_set_LCR_dlab(index, 0);
}

/*
********************************************************************************
** \brief Sets a new data word size
**
** This function sets the given data word size value (in bits) for the
** requested UART block.
** It accepts values in the range from #GOKESDK_UART_DATABITS_5
** upto #GOKESDK_UART_DATABITS_8.
**
** \param index The UART block to access, either '0' or '1'
** \param dataBits The data word size value to write into the UART block
**
** \return
** - (1) if dataBits was successfully set
** - (0) if either the index or the dataBits value is out of range
********************************************************************************
*/
static void uartSetDataBits(U32 index, U32 dataBits)
{
    U32 data_bits = dataBits;
    // 0 = use 5 data bits
    // 1 = use 6 data bits
    // 2 = use 7 data bits
    // 3 = use 8 data bits
    data_bits -= GD_UART_5_DATATBITS;

    if(GH_UART_get_LCR_cls(index) != data_bits)
    {
         GH_UART_set_LCR_cls(index, data_bits);
    }
}

/*
********************************************************************************
** \brief Sets a new stop bit count
**
** This function sets the given stop bit count (in bits) for the
** requested UART block.
** It accepts values in the range from #GOKESDK_UART_STOPBITS_1
** upto #GOKESDK_UART_STOPBITS_2.
**
** \param index The UART block to access, either '0' or '1'
** \param stopBits The stop bits value to write into the UART block
**
** \return
** - (1) if stopBits was successfully set
** - (0) if either the index or the stopBits value is out of range
********************************************************************************
*/
static void uartSetStopBits(U32 index, U32 stopBits)
{
    // 0 = use 1 stop bit
    // 1 = use 2 stop bits
    if(GH_UART_get_LCR_stop(index) != stopBits)
    {
         GH_UART_set_LCR_stop(index, stopBits);
    }
}

/*
********************************************************************************
** \brief Sets a new parity type
**
** This function sets the given parity type for the requested UART block.
** It accepts the values #GOKESDK_UART_PARITY_NONE, #GOKESDK_UART_PARITY_ODD
** and #GOKESDK_UART_PARITY_EVEN.
**
** \param index The UART block to access, either '0' or '1'
** \param parity The parity value to write into the UART block
**
** \return
** - (1) if parity was successfully set
** - (0) if either the index or the parity value is out of range
********************************************************************************
*/
static void uartSetParity(U32 index, U32 parity)
{
    switch(parity)
    {
    case GD_UART_NO_PARITY:
        if(GH_UART_get_LCR_pen(index))
        {
            GH_UART_set_LCR_pen(index, 0);
        }
        break;

    case GD_UART_ODD_PARITY:
        if(!GH_UART_get_LCR_pen(index))
        {
            GH_UART_set_LCR_pen(index, 1);
        }
        if(GH_UART_get_LCR_eps(index))
        {
            GH_UART_set_LCR_eps(index, 0);
        }
        break;

    case GD_UART_EVEN_PARITY:
        if(!GH_UART_get_LCR_pen(index))
        {
            GH_UART_set_LCR_pen(index, 1);
        }
        if(!GH_UART_get_LCR_eps(index))
        {
            GH_UART_set_LCR_eps(index, 1);
        }
        break;

    default:
        break;
    }
}

/*!
********************************************************************************
** \brief Sets a new hardware flow control type
**
** This function sets the given hardware flow control type for the requested
** UART block.
** It accepts the values #GOKESDK_UART_FLOWCTRL_NONE, #GOKESDK_UART_FLOWCTRL_CTS,
** #GOKESDK_UART_FLOWCTRL_RTS and #GOKESDK_UART_FLOWCTRL_CTS_RTS.
**
** \param index The UART block to access, either '0' or '1'
** \param flowCtrl The flow control value to write into the UART block
**
** \return
** - (1) if flowCtrl was successfully set
** - (0) if either the index or the flowCtrl value is out of range
********************************************************************************
*/
static void uartSetFlowControl(U32 index, U32 flowCtrl)
{
    if(index == 0)
    {
        // In UART0, only the Loopback bit is used and flow control is not supported.
        // In UART1, all the bits are used.
        if((flowCtrl == GD_UART_NO_PROTOCOL) || (flowCtrl == GD_UART_FLOWCTRL_LOOPBACK))
        {
            if(GH_UART_get_MCR(index) != flowCtrl)
            {
                GH_UART_set_MCR(index, flowCtrl);
            }
        }
        return;
    }
    if(GH_UART_get_MCR(index) != flowCtrl)
    {
        GH_UART_set_MCR(index, flowCtrl);
    }
}

/*!
*******************************************************************************
**
** \brief  Set UART connection parameter.
**
**         This function sets the connection parameter of the UART device.
**         Hereby it overwrites the default parameter specified during
**         initialization. The change of parameters will come into effect on the
**         next \c GD_UART_Read() or \c GD_UART_Write() function call, to
**         prevent corruption of data in transit.
**
** \param  handle Valid handle of the UART driver instance.
** \param  paramsP Pointer to a structure containing the required parameters.
**
** \return One of the following status codes:
**         - \c #GD_OK if successful
**         - \c #GD_ERR_INVALID_HANDLE if the given handle is invalid.
**         - \c #GD_ERR_BAD_PARAMETER if the initialization parameter are not
**                                 correctly specified.
**
** \sa GD_UART_Init <br>
**     GD_UART_Read <br>
**     GD_UART_Write
******************************************************************************/
GERR GD_UART_SetParams(GD_HANDLE handle, GD_UART_PARAMS_S *paramsP)
{
    //    GERR ret;
    GD_UART_STATE_MACHINE_S* uart_handle_ptr = NULL;

    if(handle == NULL)
        return GD_ERR_BAD_PARAMETER;
    /* check parameters */
    if(uartCheckParams(paramsP) == GD_ERR_BAD_PARAMETER)
        return GD_ERR_BAD_PARAMETER;

    uart_handle_ptr = (GD_UART_STATE_MACHINE_S *)handle;
    //if(uart_handle_ptr->inUse == GFALSE)
        //return GD_ERR_NOT_INITIALIZED;

    uartSetBaudrate(uart_handle_ptr->channel,   paramsP->dataRate);
    uartSetDataBits(uart_handle_ptr->channel,   paramsP->numDataBits);
    uartSetParity(uart_handle_ptr->channel,     paramsP->parity);
    uartSetStopBits(uart_handle_ptr->channel,   paramsP->numStopBits);
    uartSetFlowControl(uart_handle_ptr->channel,paramsP->protocol);

    /* copy parameters for GD_UART_GetParams */
    uart_handle_ptr->SetParamsData.dataRate    = paramsP->dataRate;
    uart_handle_ptr->SetParamsData.numDataBits = paramsP->numDataBits;
    uart_handle_ptr->SetParamsData.numStopBits = paramsP->numStopBits;
    uart_handle_ptr->SetParamsData.parity      = paramsP->parity;
    uart_handle_ptr->SetParamsData.protocol    = paramsP->protocol;

    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Writes data to the UART driver.
**
** Writes data from the source buffer into driver instance.
**
** \param  handle Valid handle of the UART driver instance.
** \param  bufferP Pointer to the source buffer.
** \param  bufferSize Length of source buffer.
**
** \return One of the following status codes:
**         - \c #GD_OK if successful
**         - \c #GD_ERR_INVALID_HANDLE if the given handle is invalid.
**
** \sa GD_UART_Read
******************************************************************************/
GERR GD_UART_Write(GD_HANDLE handle, U8 *bufferP, U16 bufferSize)
{
    U8 temp_data = 0;
    U8 intFlag = 0;
    U8  data;
    U16 i;
    U32 timeout = 10000;
    U32 writeCnt = 0;

    /* check if handle is valid */
    GD_UART_STATE_MACHINE_S* uart_handle_ptr = NULL;
    if(handle == NULL)
        return GD_ERR_BAD_PARAMETER;
    if (bufferP == NULL)
        return GD_ERR_BAD_PARAMETER;
    if (bufferSize == 0)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    uart_handle_ptr = (GD_UART_STATE_MACHINE_S *)handle;
    if(uart_handle_ptr->inUse == GFALSE)
        return GD_ERR_NOT_INITIALIZED;

    if (bufferSize == 1)
    {
        if (GH_UART_get_IER_etbei(uart_handle_ptr->channel) == 1)
        {
            intFlag = 1;
        }
        else
        {
            intFlag = 0;
        }
    }
    else
    {
        intFlag = 1;
    }

    
    for(i=0; i<bufferSize; i++)
    {
        if((uart_handle_ptr->interruptEnable) && intFlag)
        {
            while (uart_handle_ptr->TxBufCounter >= uart_handle_ptr->TxBufSize) //TxBuffer overflow, wait TX
            {
                GH_UART_set_IER_etbei(uart_handle_ptr->channel, 0); //Turn off THRE interrupt
                while (!GH_UART_get_LSR_temt(uart_handle_ptr->channel));
                data = uart_handle_ptr->TxBuffer[uart_handle_ptr->TxBufRead++];
                GH_UART_set_THR_Data(uart_handle_ptr->channel, data);
                if (uart_handle_ptr->TxBufRead >= uart_handle_ptr->TxBufSize)
                {
                    uart_handle_ptr->TxBufRead = 0;
                }
                uart_handle_ptr->TxBufCounter--;
                uart_handle_ptr->UartStatics.numTransmittedChar++;
            }
            
            /* If TxBuffer is not full, fill data into TxBuffer to prepare for transmitting */
            uart_handle_ptr->TxBuffer[uart_handle_ptr->TxBufWrite++] = *bufferP++;
            uart_handle_ptr->TxBufCounter++;
            if(uart_handle_ptr->TxBufWrite >= uart_handle_ptr->TxBufSize)
            {
                uart_handle_ptr->TxBufWrite = 0;
            }
        }
        else
        {
            if ((writeCnt % UART_FIFO_SIZE) == 0)
            {
                while(!GH_UART_get_LSR_temt(uart_handle_ptr->channel));
            }
            GH_UART_set_THR_Data(uart_handle_ptr->channel, *bufferP++);
            uart_handle_ptr->UartStatics.numTransmittedChar++;
            writeCnt++;
        }        
    }
    if((uart_handle_ptr->interruptEnable) && intFlag)
    {
        if (GH_UART_get_IER_etbei(uart_handle_ptr->channel) == 0)
        {
            GH_UART_set_IER_etbei(uart_handle_ptr->channel, 1); //Turn on THRE interrupt
        }
    }
    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Transmit chars to UART device continuously.
**
** Writes data from the UART TX buffer into driver instance.
**
** \param  handle Valid handle of the UART driver instance.
**
** \return One of the following status codes:
**         - \c #GD_OK if successful
**         - \c #GD_ERR_INVALID_HANDLE if the given handle is invalid.
**
******************************************************************************/
GERR GD_UART_Transmit_Chars(GD_UART_STATE_MACHINE_S *handle)
{
    GD_UART_STATE_MACHINE_S *uart_handle_ptr = NULL;
    U32 count;
    U8  data;
    GERR  ret = GD_OK;
    GD_UART_BUFFER_STATE_E txBufState;

    if(handle == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    uart_handle_ptr = handle;
    if(uart_handle_ptr->inUse == GFALSE)
    {
        return GD_ERR_NOT_INITIALIZED;
    }

    if (uart_handle_ptr->TxBufWrite != uart_handle_ptr->TxBufRead)
    {
        count = UART_FIFO_SIZE;
        while (count-- > 0)
        {
            data = uart_handle_ptr->TxBuffer[uart_handle_ptr->TxBufRead++];
            GH_UART_set_THR_Data(uart_handle_ptr->channel, data);
            if (uart_handle_ptr->TxBufRead >= uart_handle_ptr->TxBufSize)
            {
                uart_handle_ptr->TxBufRead = 0;
            }
            uart_handle_ptr->TxBufCounter--;
            uart_handle_ptr->UartStatics.numTransmittedChar++;

            if (uart_handle_ptr->TxBufWrite == uart_handle_ptr->TxBufRead)
            {
                GH_UART_set_IER_etbei(uart_handle_ptr->channel, 0); //Turn off THRE interrupt
                txBufState = TX_BUFFER_STATE_EMPTY;
                if (uart_handle_ptr->TxBufCounter != 0)
                {
                    uart_handle_ptr->TxBufCounter = 0;
                }
                break;
            }
            else
            {
                txBufState = TX_BUFFER_STATE_NORMAL;
            }
        }
    }
    else
    {
        if (uart_handle_ptr->TxBufCounter >= uart_handle_ptr->TxBufSize) //TXBuffer is overflow
        {
            txBufState = TX_BUFFER_STATE_OVERFLOW;
            count = UART_FIFO_SIZE;
            while (count-- > 0)
            {
                data = uart_handle_ptr->TxBuffer[uart_handle_ptr->TxBufRead++];
                GH_UART_set_THR_Data(uart_handle_ptr->channel, data);
                if (uart_handle_ptr->TxBufRead >= uart_handle_ptr->TxBufSize)
                {
                    uart_handle_ptr->TxBufRead = 0;
                }
                uart_handle_ptr->TxBufCounter--;
                uart_handle_ptr->UartStatics.numTransmittedChar++;
            }
            //GM_Printf("Error: TxBuffer is overflow!\n");
            ret = GD_ERR_BUFFER_OVERFLOW;
        }
        else    //TxBuffer is empty
        {
            txBufState = TX_BUFFER_STATE_EMPTY;
            if (uart_handle_ptr->TxBufCounter != 0)
            {
                uart_handle_ptr->TxBufCounter = 0;
            }
            GH_UART_set_IER_etbei(uart_handle_ptr->channel, 0); //Turn off THRE interrupt
        }
    }
    if (uart_handle_ptr->NotifyFunction)
    {
        uart_handle_ptr->NotifyFunction(txBufState);
    }
    return ret;
}

/*!
*******************************************************************************
**
** \brief  Receive chars from UART device continuously.
**
** Read data from the UART driver instance into UART RX buffer.
**
** \param  handle Valid handle of the UART driver instance.
**
** \return One of the following status codes:
**         - \c #GD_OK if successful
**         - \c #GD_ERR_INVALID_HANDLE if the given handle is invalid.
**
******************************************************************************/
GERR GD_UART_Receive_Chars(GD_UART_STATE_MACHINE_S *handle, U32 timeout)
{
    GD_UART_STATE_MACHINE_S *uart_handle_ptr = NULL;
    GD_UART_BUFFER_STATE_E rxBufState;
    U32 count;
    U8 line_status_BI;
    U8 line_status_FE;
    U8 line_status_PE;
    U8 line_status_OE;
    U8 line_status_DR;
    U8 character;
    GERR ret = GD_OK;

    if(handle == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    uart_handle_ptr = handle;
    if(uart_handle_ptr->inUse == GFALSE)
    {
        return GD_ERR_NOT_INITIALIZED;
    }

    line_status_BI = GH_UART_get_LSR_bi(uart_handle_ptr->channel);
    line_status_FE = GH_UART_get_LSR_fe(uart_handle_ptr->channel);
    line_status_PE = GH_UART_get_LSR_pe(uart_handle_ptr->channel);
    line_status_OE = GH_UART_get_LSR_oe(uart_handle_ptr->channel);
    line_status_DR = GH_UART_get_LSR_dr(uart_handle_ptr->channel);
    count = UART_FIFO_SIZE;
    if (uart_handle_ptr->RxBufCounter == 0)
    {
        rxBufState = RX_BUFFER_STATE_EMPTY;
    }
    
    do {
        if (line_status_BI || line_status_FE || line_status_PE || line_status_OE)
        {
            if (line_status_BI)
            {
                GM_Printf("Data break interrupt alarm! Input logic 0 maintains over maximum time.\n");
                GH_UART_get_RBR_Data(uart_handle_ptr->channel);
                line_status_BI = GH_UART_get_LSR_bi(uart_handle_ptr->channel);
                line_status_FE = GH_UART_get_LSR_fe(uart_handle_ptr->channel);
                line_status_PE = GH_UART_get_LSR_pe(uart_handle_ptr->channel);
                line_status_OE = GH_UART_get_LSR_oe(uart_handle_ptr->channel);
                line_status_DR = GH_UART_get_LSR_dr(uart_handle_ptr->channel);                
                continue;
            }
            if (line_status_FE)
            {
                GM_Printf("Frame error alarm! Stop bit has not been detected!\n");
            }
            if (line_status_PE)
            {
                uart_handle_ptr->UartStatics.numParityError++;
                GM_Printf("Parity error alarm! Parity check failed!\n");
            }
            if (line_status_OE)
            {
                GM_Printf("Override error alarm! New byte has been received when the last byte is still exits or FIFO is full!\n");
            }
        }

        if (line_status_DR)
        {
            character = GH_UART_get_RBR_Data(uart_handle_ptr->channel);
            if (uart_handle_ptr->RxBufCounter >= uart_handle_ptr->RxBufSize)
            {
                rxBufState = RX_BUFFER_STATE_OVERFLOW;
                continue;   //  Ignore char
            }
            else
            {
                rxBufState = RX_BUFFER_STATE_NORMAL;
                uart_handle_ptr->UartStatics.numReceivedChar++;
            }
            uart_handle_ptr->RxBuffer[uart_handle_ptr->RxBufWrite++] = character;
            if (uart_handle_ptr->RxBufWrite >= uart_handle_ptr->RxBufSize)
            {
                uart_handle_ptr->RxBufWrite = 0;
            }
            uart_handle_ptr->RxBufCounter++;
            timeout = 0;
        }
        else
        {
            if (timeout == 1)
            {
                character = GH_UART_get_RBR_Data(uart_handle_ptr->channel);
                GM_Printf("False timeout get %d\n", character);
            }
        }
        
        line_status_BI = GH_UART_get_LSR_bi(uart_handle_ptr->channel);
        line_status_FE = GH_UART_get_LSR_fe(uart_handle_ptr->channel);
        line_status_PE = GH_UART_get_LSR_pe(uart_handle_ptr->channel);
        line_status_OE = GH_UART_get_LSR_oe(uart_handle_ptr->channel);
        line_status_DR = GH_UART_get_LSR_dr(uart_handle_ptr->channel);
    }while (line_status_DR && (count-- > 0));
    if (uart_handle_ptr->NotifyFunction)
    {
        uart_handle_ptr->NotifyFunction(rxBufState);
}
    return ret;
}
/*!
*******************************************************************************
**
** \brief Get UART RX/TX buffer information.
**
** This function obtains the uart RX/TX buffer information, which can support application to read
** or write UART instance.
**
*******************************************************************************
*/
    
    

/*---------------------------------------------------------------------------*/
/* local  functions                                                          */
/*---------------------------------------------------------------------------*/

/*
*******************************************************************************
**
** \brief  Connection parameter check routine.
**
** \param  paramsP Pointer to the parameter to be checked.
**
** \return One of the following status codes:
**         - \c #GD_OK if successful
**         - \c #GD_ERR_BAD_PARAMETER if the initialization parameter are not
**                                 correctly specified.
******************************************************************************/
static GERR uartCheckParams(GD_UART_PARAMS_S *paramsP)
{
    switch (paramsP->numDataBits)
    {
    case GD_UART_5_DATATBITS:
    case GD_UART_6_DATATBITS:
    case GD_UART_7_DATATBITS:
    case GD_UART_8_DATATBITS:
        break;
    default:
        return GD_ERR_BAD_PARAMETER;
    }

    switch (paramsP->numStopBits)
    {
    case GD_UART_10_STOPBITS:
    case GD_UART_20_STOPBITS:
        break;
    default:
        return GD_ERR_BAD_PARAMETER;
    }

    /*switch (paramsP->protocol)
    {
    case GD_UART_NO_PROTOCOL:
    case GD_UART_HARDWARE:
    case GD_UART_FLOWCTRL_CTS:
    case GD_UART_FLOWCTRL_RTS:
    case GD_UART_FLOWCTRL_CTS_RTS:
        break;
    default:
        return GD_ERR_BAD_PARAMETER;
    }*/

    switch (paramsP->parity)
    {
    case GD_UART_NO_PARITY:
    case GD_UART_ODD_PARITY:
    case GD_UART_EVEN_PARITY:
        break;

    default:
        return GD_ERR_BAD_PARAMETER;
    }

    return GD_OK;
}


//0108 hhl modify for interrupt-mode test
//#if 0    //ori
#if 1    //hhl
/*
*******************************************************************************
**
** \brief  UART controller interrupt routine.
**
******************************************************************************/
static GISR1 uartISR(void)
{
    U8 interruptID;
    //GD_INT_DisableAllInterrupts();

    interruptID = GH_UART_get_IIR_interrupt_id(0);
    switch (interruptID)
    {
        case UART_II_MODEM_STATUS_CHANGED:
        case UART_II_NO_INT_PENDING:
            break;
        case UART_II_THR_EMPTY:
            GD_UART_Transmit_Chars(&g_uart_state_machine_data[0]);
            break;
        case UART_II_RCV_DATA_AVAIL:
        case UART_II_RCV_STATUS:
            GD_UART_Receive_Chars(&g_uart_state_machine_data[0], 0);
            break;
        case UART_II_CHAR_TIMEOUT:
            GD_UART_Receive_Chars(&g_uart_state_machine_data[0], 1);
            break;
        default:
            GM_Printf("Interrupt ID has not been recognized!\n");
            break;
    }
    //GD_INT_EnableAllInterrupts();
}
/*
*******************************************************************************
**
** \brief  UART controller interrupt routine.
**
******************************************************************************/
static GISR1 uart1ISR(void)
{
    U8 interruptID;
    //GD_INT_DisableAllInterrupts();

    interruptID = GH_UART_get_IIR_interrupt_id(1);
    switch (interruptID)
    {
        case UART_II_MODEM_STATUS_CHANGED:
        case UART_II_NO_INT_PENDING:
            break;
        case UART_II_THR_EMPTY:
            GD_UART_Transmit_Chars(&g_uart_state_machine_data[1]);
            break;
        case UART_II_RCV_DATA_AVAIL:
        case UART_II_RCV_STATUS:
            GD_UART_Receive_Chars(&g_uart_state_machine_data[1], 0);
            break;
        case UART_II_CHAR_TIMEOUT:
            GD_UART_Receive_Chars(&g_uart_state_machine_data[1], 1);
            break;
        default:
            GM_Printf("Interrupt ID has not been recognized!\n");
            break;
    }
    //GD_INT_EnableAllInterrupts();
}

/*
*******************************************************************************
**
** \brief  UART controller interrupt routine.
**
******************************************************************************/
static GISR1 uart2ISR(void)
{
    U8 interruptID;
    //GD_INT_DisableAllInterrupts();

    interruptID = GH_UART_get_IIR_interrupt_id(2);
    switch (interruptID)
    {
        case UART_II_MODEM_STATUS_CHANGED:
        case UART_II_NO_INT_PENDING:
            break;
        case UART_II_THR_EMPTY:
            GD_UART_Transmit_Chars(&g_uart_state_machine_data[2]);
            break;
        case UART_II_RCV_DATA_AVAIL:
        case UART_II_RCV_STATUS:
            GD_UART_Receive_Chars(&g_uart_state_machine_data[2], 0);
            break;
        case UART_II_CHAR_TIMEOUT:
            GD_UART_Receive_Chars(&g_uart_state_machine_data[2], 1);
            break;
        default:
            GM_Printf("Interrupt ID has not been recognized!\n");
            break;
    }
    //GD_INT_EnableAllInterrupts();
}
#endif
/*
*******************************************************************************
**
** \brief  UART interrupt handler.
**
** This function handles the UART interrupt. It simply reads and clears the
** interrupt statuts register and returns it contents for further processing.
**
******************************************************************************/
static GD_INT_DATA_S* uartHandler(void)
{
    static UART_DATA_S   uartData;
    static GD_INT_DATA_S intData;

    intData.length      = sizeof(UART_DATA_S);
    intData.data        = &uartData;
    intData.processor   = uartProcessor;

    uartData.IRQStatus = GH_UART_get_LSR(0);
    return(&intData);
}

/*
*******************************************************************************
**
** \brief  UART interrupt handler.
**
** This function handles the UART interrupt. It simply reads and clears the
** interrupt statuts register and returns it contents for further processing.
**
******************************************************************************/
static GD_INT_DATA_S* uart1Handler(void)
{
    static UART_DATA_S   uartData;
    static GD_INT_DATA_S intData;

    intData.length      = sizeof(UART_DATA_S);
    intData.data        = &uartData;
    intData.processor   = uart1Processor;

    //0111 hhl modify
    uartData.IRQStatus = GH_UART_get_LSR(1);    //ori
    //uartData.IRQStatus = GH_UART_get_IIR(1);    //hhl
    
    return(&intData);
}
/*
*******************************************************************************
**
** \brief  UART interrupt handler.
**
** This function handles the UART interrupt. It simply reads and clears the
** interrupt statuts register and returns it contents for further processing.
**
******************************************************************************/
static GD_INT_DATA_S* uart2Handler(void)
{
    static UART_DATA_S   uartData;
    static GD_INT_DATA_S intData;

    intData.length      = sizeof(UART_DATA_S);
    intData.data        = &uartData;
    intData.processor   = uart2Processor;

    //0111 hhl modify
    uartData.IRQStatus = GH_UART_get_LSR(2);    //ori
    //uartData.IRQStatus = GH_UART_get_IIR(2);    //hhl
    
    return(&intData);
}

/*
*******************************************************************************
**
** \brief  UART interrupt processor.
**
** This function processes the UART interrupt.
**
** \param Pointer to the UART driver data structure
**
******************************************************************************/
static void uartProcessor(void* data)
{
#if 0
    UART_DATA_S*  uartDataP = (UART_DATA_S*)data;

    U8 dataByte = 0;

    if(uartDataP->IRQStatus & 0x01)//Data Ready
    {
        if(uartDataP->IRQStatus & 0x10)
        {
            GH_UART_set_Icr_Rxic(0, 1);
        }
        if(uartDataP->IRQStatus & 0x40)
        {
            GH_UART_set_Icr_Rtic(0, 1);
        }
        while(GH_UART_get_LSR_dr(0))
        {
            if(g_uart_state_machine_data[0].RxBufCounter >= TX_BUF_SIZE)
            {
                break; //read buffer overflow;
            }
            dataByte = GH_UART_get_RBR_Data(0) & 0x000000FF;
            g_uart_state_machine_data[0].RxBuffer[g_uart_state_machine_data[0].RxBufWrite++] = dataByte;
            g_uart_state_machine_data[0].RxBufCounter++;
            if(g_uart_state_machine_data[0].RxBufWrite >= RX_BUF_SIZE)
            {
                g_uart_state_machine_data[0].RxBufWrite = 0;
            }
        }
    }
    if(uartDataP->IRQStatus & 0x20)
    {
        GH_UART_set_Icr_Txic(0, 1);
        GH_UART_set_Imsc_Txim(0, 0);
        while( g_uart_state_machine_data[0].TxBufRead != g_uart_state_machine_data[0].TxBufWrite)
        {
            if(!GH_UART_get_LSR_temt(0))
            {
                // if the TX-fifo-full bit is set, enable TX interrupts
                // and set the level changes to 7/8 of fifo, so that an
                // interrupt will be generated if the fifo level counts
                // down to less than the 14 of 16 entries
                GH_UART_set_Imsc_Txim(0, 1);
                GH_UART_set_FCR_TX_Empty_Trigger(0, 3);
                break;
            }
            dataByte = g_uart_state_machine_data[0].TxBuffer[g_uart_state_machine_data[0].TxBufRead++];
            g_uart_state_machine_data[0].TxBufCounter --;
            GH_UART_set_THR_Data(0, (U32)dataByte);
            if(g_uart_state_machine_data[0].TxBufRead >=  RX_BUF_SIZE)
            {
                g_uart_state_machine_data[0].TxBufRead = 0;
            }
        }
    }

    if(uartDataP->IRQStatus & 0x400)
    {
        GH_UART_set_Icr_Oeic(0, 1);
        g_uart_state_machine_data[0].UartStatics.numParityError++;
    }
#else
//0108 hhl add "#else"
#if 1
    //UART_DATA_S*  uartDataP = (UART_DATA_S*)data;

    U8 dataByte = 0;

    //0111 hhl modify(disable this instruct)
    //if(uartDataP->IRQStatus == 0x01)// Dr
    {
        while(GH_UART_get_LSR_dr(0))
        {
            if(g_uart_state_machine_data[0].RxBufCounter >= g_uart_state_machine_data[0].RxBufSize)
            {
                break; //read buffer overflow;
            }
            dataByte = GH_UART_get_RBR_Data(0) & 0x000000FF;
            g_uart_state_machine_data[0].RxBuffer[g_uart_state_machine_data[0].RxBufWrite++] = dataByte;
            g_uart_state_machine_data[0].RxBufCounter++;
            if(g_uart_state_machine_data[0].RxBufWrite >= g_uart_state_machine_data[0].RxBufSize)
            {
                g_uart_state_machine_data[0].RxBufWrite = 0;
            }
        }
    }
#else
    U8 int_id = 0;
    U8 data = 0;
    GD_HANDLE handleP = (GD_HANDLE)(&(g_uart_state_machine_data[0]));
     
    int_id = GH_UART_get_IIR_interrupt_id(0);

    if(handleP == NULL)
    {
        GM_Printf("bad par! \n");
        return;
    }
    if(int_id == 0)
    {
        GM_Printf("no interrupt! \n");
        return;
    }
    if(int_id & 0x08)    //Received Data available
    {
        GD_UART_Read(handleP, &data, 1, NULL);
    }
#endif
#endif
}

/*
*******************************************************************************
**
** \brief  UART interrupt processor.
**
** This function processes the UART interrupt.
**
** \param Pointer to the UART driver data structure
**
******************************************************************************/
static void uart1Processor(void* data)
{
#if 0
    UART_DATA_S*  uartDataP = (UART_DATA_S*)data;

    U8 dataByte = 0;

    if(uartDataP->IRQStatus & (0x10 | 0x40))
    {
        if(uartDataP->IRQStatus & 0x10)
        {
            GH_UART_set_Icr_Rxic(1, 1);
        }
        if(uartDataP->IRQStatus & 0x40)
        {
            GH_UART_set_Icr_Rtic(1, 1);
        }
        while(GH_UART_get_LSR_dr(1))
        {
            if(g_uart_state_machine_data[1].RxBufCounter >= TX_BUF_SIZE)
            {
                break; //read buffer overflow;
            }
            dataByte = GH_UART_get_RBR_Data(1) & 0x000000FF;
            g_uart_state_machine_data[1].RxBuffer[g_uart_state_machine_data[1].RxBufWrite++] = dataByte;
            g_uart_state_machine_data[1].RxBufCounter++;
            if(g_uart_state_machine_data[1].RxBufWrite >= RX_BUF_SIZE)
            {
                g_uart_state_machine_data[1].RxBufWrite = 0;
            }
        }
    }
    if(uartDataP->IRQStatus & 0x20)
    {
        GH_UART_set_Icr_Txic(1, 1);
        GH_UART_set_Imsc_Txim(1, 0);
        while( g_uart_state_machine_data[1].TxBufRead != g_uart_state_machine_data[1].TxBufWrite)
        {
            if(!GH_UART_get_LSR_temt(1))
            {
                // if the TX-fifo-full bit is set, enable TX interrupts
                // and set the level changes to 1/2 of fifo, so that an
                // interrupt will be generated if the fifo level counts
                // down to less than the 14 of 16 entries
                GH_UART_set_Imsc_Txim(1, 1);
                GH_UART_set_FCR_TX_Empty_Trigger(1, 3);
                break;
            }
            dataByte = g_uart_state_machine_data[1].TxBuffer[g_uart_state_machine_data[1].TxBufRead++];
            g_uart_state_machine_data[1].TxBufCounter --;
            GH_UART_set_THR_Data(1, (U32)dataByte);
            if(g_uart_state_machine_data[1].TxBufRead >=  RX_BUF_SIZE)
            {
                g_uart_state_machine_data[1].TxBufRead = 0;
            }
        }
    }

    if(uartDataP->IRQStatus & 0x400)
    {
        GH_UART_set_Icr_Oeic(1, 1);
        g_uart_state_machine_data[1].UartStatics.numParityError++;
    }
#else
//0108 hhl add "#else"
    U8 int_id = 0;
    U8 tem_data = 0;
    GD_HANDLE handleP = (GD_HANDLE)(&(g_uart_state_machine_data[1]));
     
    int_id = GH_UART_get_IIR_interrupt_id(1);

    if(handleP == NULL)
    {
        GM_Printf("bad par! \n");
        return;
    }
    if(int_id == 0)
    {
        GM_Printf("no interrupt! \n");
        return;
    }
    if(int_id & 0x08)    //Received Data available
    {
        GD_UART_Read(handleP, &tem_data, 1, NULL);
    }
#endif
}

/*
*******************************************************************************
**
** \brief  UART interrupt processor.
**
** This function processes the UART interrupt.
**
** \param Pointer to the UART driver data structure
**
******************************************************************************/
static void uart2Processor(void* data)
{
#if 0
    UART_DATA_S*  uartDataP = (UART_DATA_S*)data;

    U8 dataByte = 0;

    if(uartDataP->IRQStatus & (0x10 | 0x40))
    {
        if(uartDataP->IRQStatus & 0x10)
        {
            GH_UART_set_Icr_Rxic(1, 1);
        }
        if(uartDataP->IRQStatus & 0x40)
        {
            GH_UART_set_Icr_Rtic(1, 1);
        }
        while(GH_UART_get_LSR_dr(1))
        {
            if(g_uart_state_machine_data[1].RxBufCounter >= TX_BUF_SIZE)
            {
                break; //read buffer overflow;
            }
            dataByte = GH_UART_get_RBR_Data(1) & 0x000000FF;
            g_uart_state_machine_data[1].RxBuffer[g_uart_state_machine_data[1].RxBufWrite++] = dataByte;
            g_uart_state_machine_data[1].RxBufCounter++;
            if(g_uart_state_machine_data[1].RxBufWrite >= RX_BUF_SIZE)
            {
                g_uart_state_machine_data[1].RxBufWrite = 0;
            }
        }
    }
    if(uartDataP->IRQStatus & 0x20)
    {
        GH_UART_set_Icr_Txic(1, 1);
        GH_UART_set_Imsc_Txim(1, 0);
        while( g_uart_state_machine_data[1].TxBufRead != g_uart_state_machine_data[1].TxBufWrite)
        {
            if(!GH_UART_get_LSR_temt(1))
            {
                // if the TX-fifo-full bit is set, enable TX interrupts
                // and set the level changes to 1/2 of fifo, so that an
                // interrupt will be generated if the fifo level counts
                // down to less than the 14 of 16 entries
                GH_UART_set_Imsc_Txim(1, 1);
                GH_UART_set_FCR_TX_Empty_Trigger(1, 3);
                break;
            }
            dataByte = g_uart_state_machine_data[1].TxBuffer[g_uart_state_machine_data[1].TxBufRead++];
            g_uart_state_machine_data[1].TxBufCounter --;
            GH_UART_set_THR_Data(1, (U32)dataByte);
            if(g_uart_state_machine_data[1].TxBufRead >=  RX_BUF_SIZE)
            {
                g_uart_state_machine_data[1].TxBufRead = 0;
            }
        }
    }

    if(uartDataP->IRQStatus & 0x400)
    {
        GH_UART_set_Icr_Oeic(1, 1);
        g_uart_state_machine_data[1].UartStatics.numParityError++;
    }
#else
//0108 hhl add "#else"
    U8 int_id = 0;
    U8 tem_data = 0;
    GD_HANDLE handleP = (GD_HANDLE)(&(g_uart_state_machine_data[2]));
     
    int_id = GH_UART_get_IIR_interrupt_id(2);

    if(handleP == NULL)
    {
        GM_Printf("bad par! \n");
        return;
    }
    if(int_id == 0)
    {
        GM_Printf("no interrupt! \n");
        return;
    }
    if(int_id & 0x08)    //Received Data available
    {
        GD_UART_Read(handleP, &tem_data, 1, NULL);
    }
#endif
}

#endif

