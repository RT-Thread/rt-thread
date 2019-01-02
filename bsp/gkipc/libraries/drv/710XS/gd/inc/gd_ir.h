/*!
*******************************************************************************
**
** \file      gd_ir.h
**
** \brief     Infrared driver.
**
**            The infrared driver is designed for GOKE decoder and
**            supports two functions:
**            - IR Receiver
**            - IR Transmitter
**
**            The first one is to receive the remote controller signal and
**            decode it. The other function is to generate the infrared signal
**            and transmit it to other devices. The transmitter can be used to
**            control external devices for example a VCR or TV set.
**            The driver supports only the access to the hardware layer and
**            does not handle any IR protocols like RC5, RC6 or Kaseikyou.
**            These protocols have to be implemented on the top of this driver.
**
**            The IR receiver is a pulse-width counter and is clocked by the
**            output of a 54MHz clocked pre-scaler.
**            Every time the pre-scaler generates an enable signal the IR
**            receiver checks if an edge on the input signal has occurred.
**            The edge sensitivity of the IR receiver is programmable.
**            After the time value is received, the upper level application
**            should analyse the stored data and parse them.
**
**            The IR transmitter is a pulse generator. It consists of two
**            32bit registers to hold the data to be sent and
**            a send_clock, a shift_clock, a compare and a mode register.
**            Each time the sent clock counter counts to 0, the phase of the
**            shift clock is inverted. The shift clock counter defines how
**            many shift clocks are needed before shifting the data by one bit.
**            The total number of 54MHz cycles per bit is therefore:
**            2 x (prescaler +1) x (shift_clock_count + 1).
**
**            In IRDA mode the compare register defines how many of the
**            sent clocks are output. When starting
**            the module the data of the first register are sent (MSB first).
**            When a data word (32bit) is finished the module checks if data
**            is available in the second register. If yes, this register is
**            copied into the first register and sent afterwards.
**            At the same time, an IRQ is generated to tell the system that
**            new data are required.
**            All data have to be written to register1 except the first 32bit
**            to be sent.
**
**            Following are the IR sending out signal:
**
**            \image html gd_ir_timings.gif
**
**            - T1 = 2 x 1/54MHz x ( prescaler + 1 )
**            - T2 = T1 x ( shift_clock_count + 1 )
**            - T3 = T1 x ( comp_val + 1 )
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
#ifndef _GD_IR_H_
#define _GD_IR_H_

#include <gtypes.h>
#include <gmodids.h>

/*---------------------------------------------------------------------------*/
/* constants and macros                                                      */
/*---------------------------------------------------------------------------*/
#ifdef BOARD_FPGA
#define IR_INPUT_CLK                24000000    // for 27MHZ Crystal
#else
#define IR_INPUT_CLK                24000000    // for 24MHZ Crystal
#endif

#define IR_FREQ                     38          // for NEC unit:MHz

/********************************/
/*     IRQ_EN_MASK Register              */
/********************************/
#define     IRQ_EN_RTC      (1<<0)
#define     IRQ_EN_IRR      (1<<1)
#define     IRQ_EN_GPIO     (1<<3)
#define     IRQ_EN_IRT      (1<<6)


#define GD_IR_ERR_BASE              (GD_IR_MODULE_ID<<16)    //!< Error base value.

#define GD_IR_EDGE_FLAG             0x0100
#define GD_IR_VAL_BIT_MASK          0x00FF
#define GD_IR_TRANSFER_MAX_DATA     32

/*!
*******************************************************************************
**
** \brief IR driver error codes.
**
******************************************************************************/
enum
{
    GD_ERR_IR_NO_SEQUENCE = GD_IR_ERR_BASE, //!< No sequence stored in IR buffer.
    GD_ERR_IR_TRANSMIT_INPROCESS,   //!< IR transmission not finished yet.
    GD_ERR_IR_TRANSMIT_FAILURE,     //!< IR transmission failed.
};


/*---------------------------------------------------------------------------*/
/* types, enums and structures                                               */
/*---------------------------------------------------------------------------*/
/*!
*******************************************************************************
**
** \brief IR type definitions.
**
******************************************************************************/
typedef enum
{
    GD_IR_RECEIVER = 1,   //!< Receiver function.
    GD_IR_TRANSMITTER,    //!< Transmitter function.
} GD_IR_TYPE_E;

/*!
*******************************************************************************
**
** \brief IR driver status.
**
******************************************************************************/
typedef enum
{
    GD_IR_RECEIVER_OPENED    = 1,   //!< IR receiver is open.
    GD_IR_TRANSMITTER_OPENED = 2,   //!< IR transmitter is open.
} GD_IR_STATUS_E;

/*!
*******************************************************************************
**
** \brief Transmitter configuration parameters.
**
******************************************************************************/
typedef struct
{
    U8  programming;     //!< Programming register configuration.
    U16 prescaler;       //!< IRDA clock register configuration.
    U8  shift_counter;   //!< IRDA shift clock register configuration.
    U8  compare_value;   //!< Compare value register configuration.
    S8  gpioIrtPin;      //!< GPIO Pin to be assigned for IRT function.
} GD_IR_TRANS_CONFIG_S;

/*!
*******************************************************************************
**
** \brief Receiver configuration parameters.
**
******************************************************************************/
typedef struct
{
    U16 prescaler;       //!< Prescaler for IR receiver.
    S8  gpioIrrPin;      //!< GPIO Pin to be assigned for IRR function.
} GD_IR_RECEV_CONFIG_S;

/*!
*******************************************************************************
**
** \brief Driver init parameters.
**
** \sa    GD_IR_Init()
**
******************************************************************************/
typedef struct
{
    void (*notifyFunction)(); //!< Pointer to notification function.
} GD_IR_INIT_PARAMS_S;

/*!
*******************************************************************************
**
** \brief Open parameters.
**
** \sa    GD_IR_Open()
**
******************************************************************************/
typedef struct
{
    GD_IR_TYPE_E         type;         //!< Receiver or transmitter.
    GD_IR_TRANS_CONFIG_S irt_config_s; //!< Configuration of transmitter.
    GD_IR_RECEV_CONFIG_S irr_config_s; //!< Configuration of receiver.
} GD_IR_OPEN_PARAMS_S;

/*!
*******************************************************************************
**
** \brief Data property for IR transmitter.
**
**        This structure defines the property of the transmitting
**        data, the width for logic 1 and logic 0
**        and the valid bits of the value of width.
**
** \sa    GD_IR_SetParams()
**
******************************************************************************/
typedef struct
{
    U16 nValidbit0;   //!< Valid bits of the value for logic 0.
    U16 bitvalue0;    //!< Value for logic 0.
    U16 nValidbit1;   //!< Valid bits of the value for logic 1.
    U16 bitvalue1;    //!< Value for logic 1.
} GD_IR_DATA_PROPERTY_S;

/*!
*******************************************************************************
**
** \brief Insert data structure for IR transmitter.
**
**        This structure defines the header and footer or some other parts
**        for the transmitter to insert the logic 0 or logic 1 into the
**        output buffer.
**
** \sa    GD_IR_SetParams()
**
******************************************************************************/
typedef struct
{
    U16 number;       //!< Number of logic bit to be inserted.
    U8  bit;          //!< Logic 0 or logic 1.
} GD_IR_INSERT_S;

/*!
*******************************************************************************
**
** \brief Output data structure for IR transmitter.
**
**        This structure defines the data value and the valid bits of this
**        data.
**
** \sa    GD_IR_SetParams()
**
******************************************************************************/
typedef struct
{
    U8 value;         //!< Data value in byte.
    U8 validbit;      //!< Valid bit of this data.
} GD_IR_DATA_S;

/*---------------------------------------------------------------------------*/
/* function prototypes                                                       */
/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

GERR GD_IR_Close(GD_HANDLE *pHandle);
GERR GD_IR_Init(GD_IR_INIT_PARAMS_S *pInitParams);
GERR GD_IR_IrtOpen(GD_IR_OPEN_PARAMS_S *pOpenParams, GD_HANDLE *pHandle);
GERR GD_IR_IrrOpen(GD_IR_OPEN_PARAMS_S *pOpenParams, GD_HANDLE *pHandle);

GERR GD_IR_Receive(GD_HANDLE handle, U16 *pData, U16 num);
void GD_IR_SetNotifyFunction(void(*nfyFunc)());

GERR GD_IR_SetParams(GD_HANDLE             handle,
                     GD_IR_INSERT_S        *header,
                     U8                    nheader,
                     GD_IR_DATA_S          *data,
                     U8                    ndata,
                     GD_IR_DATA_PROPERTY_S *dataproperty,
                     GD_IR_INSERT_S*       footer,
                     U8                    nfooter,
                     U32                   *pSendBuffer,
                     U16                   *pSendNumber);

GERR GD_IR_Status(GD_HANDLE handle, U16* pNum);
GERR GD_IR_Transmit(GD_HANDLE handle, U32 *pData, U16 num);
typedef void (*GD_RTC_NOTIFY)(void);
void  GD_RTC_RegisterNotify(GD_RTC_NOTIFY rtcNotifyFunc,U32 preCount);

#ifdef __cplusplus
}
#endif

#endif /* _GD_IR_H_ */
/* end of gd_ir.h */
