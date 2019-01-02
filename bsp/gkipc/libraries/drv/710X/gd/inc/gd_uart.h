/*!
*******************************************************************************
**
** \file      gd_uart.h
**
** \brief     UART driver.
**
**            The driver provides functions to use the GK6202's UART
**            interface.
**
**           Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version
**
******************************************************************************/
#ifndef _GD_UART_H_
#define _GD_UART_H_

#include <gtypes.h>
#include <gmodids.h>

/*---------------------------------------------------------------------------*/
/* constants and macros                                                      */
/*---------------------------------------------------------------------------*/


#define GD_UART_ERR_BASE (GD_UART_MODULE_ID<<16)  //!< Error base value
#define GD_UART_COUNT        3

#define UART0_RX_BUF_SIZE    1024   /* size of uart0 receive ring buffer */
#define UART0_TX_BUF_SIZE    1024   /* size of uart0 trasmit ring buffer */
#define UART1_RX_BUF_SIZE    1024  /* size of uart1 receive ring buffer */
#define UART1_TX_BUF_SIZE    1024  /* size of uart1 trasmit ring buffer */
#define UART2_RX_BUF_SIZE    1024  /* size of uart2 receive ring buffer */
#define UART2_TX_BUF_SIZE    1024  /* size of uart2 trasmit ring buffer */
#define UART_FIFO_SIZE       16   /* size of uart FIFO in bytes */

/*---------------------------------------------------------------------------*/
/* types, enums and structures                                               */
/*---------------------------------------------------------------------------*/

/*!
*******************************************************************************
**
** \brief UART parity settings.
**
******************************************************************************/
typedef enum
{
    /*! Specifies \b NONE parity. */
    GD_UART_NO_PARITY   = 0,
    /*! Specifies \b EVEN parity. */
    GD_UART_EVEN_PARITY = 1,
    /*! Specifies \b ODD parity. */
    GD_UART_ODD_PARITY  = 2
} GD_UART_PARITY_E;

/*!
*******************************************************************************
**
** \brief UART data bit settings.
**
******************************************************************************/
typedef enum
{
    /*! Specifies \b 5 data bits. */
    GD_UART_5_DATATBITS = 4,
    /*! Specifies \b 6 data bits. */
    GD_UART_6_DATATBITS = 5,
    /*! Specifies \b 7 data bits. */
    GD_UART_7_DATATBITS = 6,
    /*! Specifies \b 8 data bits. */
    GD_UART_8_DATATBITS = 7
} GD_UART_DATABITS_E;

/*!
*******************************************************************************
**
** \brief UART stop bit settings.
**
******************************************************************************/
typedef enum
{
    /*! Specifies \b 1 stop bit. */
    GD_UART_10_STOPBITS = 0,
    /*! Specifies \b 2 stop bits. */
    GD_UART_20_STOPBITS = 1
} GD_UART_STOPBITS_E;

/*!
*******************************************************************************
**
** \brief UART protocol settings.
**
******************************************************************************/
typedef enum
{
    /*! Specifies \b NO protocol usage. */
    GD_UART_NO_PROTOCOL         = 0,
    /*! Specifies \b FLOW-CONTROL protocol of DTR mode */
    GD_UART_FLOWCTRL_DTR        = 0x00000001,
    /*! Specifies \b FLOW-CONTROL protocol of RTS mode */
    GD_UART_FLOWCTRL_RTS        = 0x00000002,
    GD_UART_FLOWCTRL_OUT1       = 0x00000004,
    GD_UART_FLOWCTRL_OUT2       = 0x00000008,
    GD_UART_FLOWCTRL_LOOPBACK   = 0x00000010,
    GD_UART_FLOWCTRL_AFCE       = 0x00000020,
    GD_UART_FLOWCTRL_SIRE       = 0x00000040,
} GD_UART_PROTOCOL_E;

/*!
*******************************************************************************
**
** \brief UART baud rate settings.
**
******************************************************************************/
typedef enum
{
    /*! Specifies \b 110 baud. */
    GD_UART_BAUD_RATE110    = 110,
    /*! Specifies \b 300 baud. */
    GD_UART_BAUD_RATE300    = 300,
    /*! Specifies \b 1200 baud. */
    GD_UART_BAUD_RATE1200   = 1200,
    /*! Specifies \b 2400 baud. */
    GD_UART_BAUD_RATE2400   = 2400,
    /*! Specifies \b 4800 baud. */
    GD_UART_BAUD_RATE4800   = 4800,
    /*! Specifies \b 9600 baud. */
    GD_UART_BAUD_RATE9600   = 9600,
    /*! Specifies \b 9600 baud. */
    GD_UART_BAUD_RATE14400  = 14400,
    /*! Specifies \b 14400 baud. */
    GD_UART_BAUD_RATE19200  = 19200,
    /*! Specifies \b 38400 baud. */
    GD_UART_BAUD_RATE38400  = 38400,
    /*! Specifies \b 57600 baud. */
    GD_UART_BAUD_RATE57600  = 57600,
    /*! Specifies \b 115200 baud. */
    GD_UART_BAUD_RATE115200 = 115200,

    /*! Specifies \b 230400 baud.
     *  \attention May cause possible clock error of more than 10%.
     */
    GD_UART_BAUD_RATE230400 = 230400,
    /*! Specifies \b 460800 baud.
     *  \attention May cause possible clock error of more than 10%.
     */
    GD_UART_BAUD_RATE460800 = 460800,
    /*! Specifies \b 921600 baud.
     *  \attention May cause possible clock error of more than 10%.
     */
    GD_UART_BAUD_RATE921600 = 921600
} GD_UART_BAUDRATE_E;

/*!
*******************************************************************************
**
** \brief UART RX/TX buffer state.
**
******************************************************************************/
typedef enum
{
    RX_BUFFER_STATE_EMPTY    = 0,
    RX_BUFFER_STATE_NORMAL   = 1,
    RX_BUFFER_STATE_OVERFLOW = 2,
    RX_BUFFER_STATE_ABNORMAL = 3,
    TX_BUFFER_STATE_EMPTY    = 4,
    TX_BUFFER_STATE_NORMAL   = 5,
    TX_BUFFER_STATE_OVERFLOW = 6,
    TX_BUFFER_STATE_ABNORMAL = 7
}GD_UART_BUFFER_STATE_E;

/*!
*******************************************************************************
**
** \brief UART connection paramter.
**
******************************************************************************/
typedef struct
{
    /*! The data rate of the connection. */
    GD_UART_BAUDRATE_E dataRate;
    /*! The data bit setting to be applied. */
    GD_UART_DATABITS_E numDataBits;
    /*! The stop bit setting to be applied. */
    GD_UART_STOPBITS_E numStopBits;
    /*! The protocol setting to be applied. */
    GD_UART_PROTOCOL_E protocol;
    /*! The parity setting to be applied. */
    GD_UART_PARITY_E   parity;
} GD_UART_PARAMS_S;

/*!
*******************************************************************************
**
** \brief UART driver's initialization parameter.
**
******************************************************************************/
typedef struct
{
    /*! The default connection parameters to be applied. */
    GD_UART_PARAMS_S  *defaultParamsP;
    /*! The CPU  frequency */
    U32               cpuFreq;
    /*! interrupt mode enable/disable*/
    GBOOL         interruptEnable;
    /*! The priority of the UART interrupt. */
    S8                irqPriority;
    /*! The function to be called when new data were received. */
    void              (*notifyFunction)(U32);
} GD_UART_INIT_PARAMS_S;

/*!
*******************************************************************************
**
** \brief UART open parameter.
**
******************************************************************************/
typedef struct
{
    /*! The connection parameters to be applied when open an instance of the
        driver.
     */
    GD_UART_PARAMS_S  *paramsP;
    S8          gpioRxPin;
    S8          gpioTxPin;
    S8          gpioRtsPin;
    S8          gpioCtsPin;
    U8          channel;
    void (*NotifyFunction)(U32);
	GBOOL       interruptEnable;
} GD_UART_OPEN_PARAMS_S;

/*!
*******************************************************************************
**
** \brief UART statistic parameter.
**
******************************************************************************/
typedef struct
{
    /*! The number of transmitted characters. */
    U32 numTransmittedChar;
    /*! The number of received characters. */
    U32 numReceivedChar;
    /*! The number  of parity  errors. */
    U32 numParityError;
} GD_UART_STATISTICS;

/*!
*******************************************************************************
**
** \brief UART state machine parameters.
**
******************************************************************************/
typedef volatile struct
{
    GBOOL               inUse;          /* specifies if block is in use */
    U8                  channel;
    U32                 RealBaudRate;
    GD_UART_PARAMS_S    SetParamsData;
    GD_UART_STATISTICS  UartStatics;

    void (*NotifyFunction)(U32);
    volatile U8 *RxBuffer;
    volatile U32 RxBufWrite; /* start and stop pointer of RX buffer */
    volatile U32 RxBufRead;
    volatile U32 RxBufCounter;
    volatile U32 RxBufSize;
    volatile U8 *TxBuffer;
    volatile U32 TxBufWrite; /* start and stop pointer of TX buffer */
    volatile U32 TxBufRead;
    volatile U32 TxBufCounter;
    volatile U32 TxBufSize;
    GBOOL    interruptEnable;
}GD_UART_STATE_MACHINE_S;


/*---------------------------------------------------------------------------*/
/* function prototypes                                                       */
/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef USE_RT_DRIVER_FRAMEWORK

GERR GD_UART_CheckRxBuffer(GD_HANDLE handle, GBOOL *dataAvailable);
GERR GD_UART_Close(GD_HANDLE *handleP);
GERR GD_UART_Flush(GD_HANDLE handle);
GERR GD_UART_GetRealBaudRate(GD_HANDLE handle, U32 *rateP);
U8  *GD_UART_GetRevisionString(void);
GERR GD_UART_GetParams(GD_HANDLE handle, GD_UART_PARAMS_S *paramsP);
GERR GD_UART_GetStatistics(GD_HANDLE handle, GD_UART_STATISTICS *statisticsP);
GERR GD_UART_Init(GD_UART_INIT_PARAMS_S *initParamsP);
GERR GD_UART_Open(GD_UART_OPEN_PARAMS_S *openParamsP, GD_HANDLE *handleP);
GERR GD_UART_Read(GD_HANDLE handle, U8 *bufferP, U16 desiredReadBytes, U16 *actualReceivedBytesP);
GERR GD_UART_SetParams(GD_HANDLE handle, GD_UART_PARAMS_S *paramsP);
GERR GD_UART_Write(GD_HANDLE handle, U8 *bufferP, U16 bufferSize);
GERR GD_UART_SetInterruptMode(GD_HANDLE handle, GBOOL enable);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GD_UART_H_ */
/* end of gd_uart.h */
