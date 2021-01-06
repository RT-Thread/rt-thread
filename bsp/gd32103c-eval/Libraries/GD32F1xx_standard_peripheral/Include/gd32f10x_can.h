/**
  ******************************************************************************
  * @brief   CAN header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10X_CAN_H
#define __GD32F10X_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @addtogroup CAN
  * @{
  */

/** @defgroup CAN_Exported_Types
  * @{
  */

/**
  * @brief  CAN Initial Parameters
  */

typedef struct {
    uint16_t CAN_Prescaler;   /*!< Baud rate prescaler.It can be 1 to 1024. */

    uint8_t CAN_Mode;         /*!< Set the CAN operating mode. */

    uint8_t CAN_SJW;          /*!< Set Resynchronization jump width */

    uint8_t CAN_BS1;          /*!< Set time segment 1. */

    uint8_t CAN_BS2;          /*!< Set time segment 2. */

    TypeState CAN_TTC;       /*!< Set time triggered communication mode. */

    TypeState CAN_ABOR;       /*!< Set automatic bus-off recovery. */

    TypeState CAN_AWK;       /*!< Set the automatic wake-up mode. */

    TypeState CAN_ARD;       /*!< Set the automatic retransmission mode. */

    TypeState CAN_RFOD;       /*!< Receive FIFO overwrite mode. */

    TypeState CAN_TFO;       /*!< Set the Transmit FIFO order. */
} CAN_InitPara;

/**
  * @brief  CAN filter Initial Parameters
  */

typedef struct {
    uint16_t CAN_FilterListHigh;         /*!< the filter List number.
                                              If the filter scale is 32-bit,the filter list number is MSBs.
                                              If the filter scale is 16-bit,the filter list number is first one.
                                              This value can take from 0x0000 to 0xFFFF */

    uint16_t CAN_FilterListLow;          /*!< the filter List number.
                                              If the filter scale is 32-bit,the filter list number is LSBs.
                                              If the filter scale is 16-bit,the filter list number is second one.
                                              This value can take from 0x0000 to 0xFFFF */

    uint16_t CAN_FilterMaskListHigh;     /*!< the filter mask number or list number,according to the filter mode.
                                              If the filter scale is 32-bit,the filter mask number or list number is MSBs.
                                              If the filter scale is 16-bit,the filter mask number or list number is first one.
                                              This value can take from 0x0000 to 0xFFFF */

    uint16_t CAN_FilterMaskListLow;      /*!< the filter mask number or list number,according to the filter mode.
                                              If the filter scale is 32-bit,the filter mask number or list number is LSBs.
                                              If the filter scale is 16-bit,the filter mask number or list number is second one.
                                              This value can take from 0x0000 to 0xFFFF */

    uint16_t CAN_FilterFIFOAssociation; /*!< Set the FIFO (0 or 1) which will be associated with the filter. */

    uint8_t CAN_FilterNumber;          /*!< Set the which filter to be initialized. It ranges from 0 to 13 or 0 to 27(in GD32F10X_CL). */

    uint8_t CAN_FilterMode;            /*!< Set the filter mode to be identifier mask or identifier list. */

    uint8_t CAN_FilterScale;           /*!< Set the filter scale. */

    TypeState CAN_FilterWork;    /*!< Set the filter to work or not. */
} CAN_FilterInitPara;

/**
  * @brief  CAN Tx message structure definition
  */

typedef struct {
    uint32_t StdId;  /*!< Set the standard format frame identifier.
                        This value can take from 0 to 0x7FF. */

    uint32_t ExtId;  /*!< Set the extended format frame identifier.
                        This value can take from 0 to 0x1FFFFFFF. */

    uint8_t FF;     /*!< Set the format of Frame , Standard or extended Frame
                        for the message that will be transmitted. */

    uint8_t FT;     /*!< Set the type of frame, Data or remote
                        for the message that will be transmitted. */

    uint8_t DLC;     /*!< Set the length of the frame that will be transmitted.
                        This value can take from 0 to 8 */

    uint8_t Data[8]; /*!< store the data that will be transmitted.
                        This value can take from 0 to 0xFF. */
} CanTxMessage;

/**
  * @brief  CAN Rx message structure definition
  */

typedef struct {
    uint32_t StdId;  /*!< Set the standard format frame identifier.
                        This value can take from 0 to 0x7FF. */

    uint32_t ExtId;  /*!< Set the extended format frame identifier.
                        This value can take from 0 to 0x1FFFFFFF. */

    uint8_t FF;     /*!< Set the format of Frame , Standard or extended Frame
                        for the message that will be received. */

    uint8_t FT;     /*!< Set the type of frame, Data or remote
                        for the message that will be received. */

    uint8_t DLC;     /*!< Set the length of the frame that will be received.
                        This value can take from 0 to 8 */

    uint8_t Data[8]; /*!< store the data that will be received.
                        This value can take from 0 to 0xFF. */

    uint8_t FI;     /*!< The index of the filter by which the frame is passed..
                        This value can take from 0 to 0xFF */
} CanRxMessage;

/**
  * @}
  */

/** @defgroup CAN_Exported_Constants
  * @{
  */

/** @defgroup CAN_sleep_constants
  * @{
  */
#define CAN_INITSTATE_FAILED              ((uint8_t)0x00) /*!< CAN initialization failed */
#define CAN_INITSTATE_SUCCESS             ((uint8_t)0x01) /*!< CAN initialization OK */

/**
  * @}
  */

/** @defgroup CAN_Communication_Mode
  * @{
  */
#define CAN_MODE_NORMAL             ((uint8_t)0x00)  /*!< Normal communication mode */
#define CAN_MODE_LOOPBACK           ((uint8_t)0x01)  /*!< Loopback communication mode */
#define CAN_MODE_SILENT             ((uint8_t)0x02)  /*!< Silent communication mode */
#define CAN_MODE_SILENT_LOOPBACK    ((uint8_t)0x03)  /*!< Loopback and silent communication mode */

/**
  * @}
  */


/**
  * @defgroup CAN_Working_Mode
  * @{
  */
#define CAN_WORKINGMODE_INITIAL         ((uint8_t)0x00) /*!< Initial working mode */
#define CAN_WORKINGMODE_NORMAL          ((uint8_t)0x01) /*!< Normal working mode */
#define CAN_WORKINGMODE_SLEEP           ((uint8_t)0x02) /*!< Sleep working mode */

/**
  * @}
  */


/**
  * @defgroup CAN_Mode_State
  * @{
  */
#define CAN_MODESTATE_FAILED    ((uint8_t)0x00)                    /*!< CAN entering the specified mode failed */
#define CAN_MODESTATE_SUCCESS   ((uint8_t)!CAN_MODESTATE_FAILED)   /*!< CAN entering the specified mode Succeed */

/**
  * @}
  */

/** @defgroup CAN_Synchronisation_Jump_Width
  * @{
  */
#define CAN_SJW_1TQ                 ((uint8_t)0x00)  /*!< 1 time quanta */
#define CAN_SJW_2TQ                 ((uint8_t)0x01)  /*!< 2 time quanta */
#define CAN_SJW_3TQ                 ((uint8_t)0x02)  /*!< 3 time quanta */
#define CAN_SJW_4TQ                 ((uint8_t)0x03)  /*!< 4 time quanta */

/**
  * @}
  */

/** @defgroup CAN_Time_Quanta_In_Bit_Segment_1
  * @{
  */
#define CAN_BS1_1TQ                 ((uint8_t)0x00)  /*!< 1 time quanta */
#define CAN_BS1_2TQ                 ((uint8_t)0x01)  /*!< 2 time quanta */
#define CAN_BS1_3TQ                 ((uint8_t)0x02)  /*!< 3 time quanta */
#define CAN_BS1_4TQ                 ((uint8_t)0x03)  /*!< 4 time quanta */
#define CAN_BS1_5TQ                 ((uint8_t)0x04)  /*!< 5 time quanta */
#define CAN_BS1_6TQ                 ((uint8_t)0x05)  /*!< 6 time quanta */
#define CAN_BS1_7TQ                 ((uint8_t)0x06)  /*!< 7 time quanta */
#define CAN_BS1_8TQ                 ((uint8_t)0x07)  /*!< 8 time quanta */
#define CAN_BS1_9TQ                 ((uint8_t)0x08)  /*!< 9 time quanta */
#define CAN_BS1_10TQ                ((uint8_t)0x09)  /*!< 10 time quanta */
#define CAN_BS1_11TQ                ((uint8_t)0x0A)  /*!< 11 time quanta */
#define CAN_BS1_12TQ                ((uint8_t)0x0B)  /*!< 12 time quanta */
#define CAN_BS1_13TQ                ((uint8_t)0x0C)  /*!< 13 time quanta */
#define CAN_BS1_14TQ                ((uint8_t)0x0D)  /*!< 14 time quanta */
#define CAN_BS1_15TQ                ((uint8_t)0x0E)  /*!< 15 time quanta */
#define CAN_BS1_16TQ                ((uint8_t)0x0F)  /*!< 16 time quanta */

/**
  * @}
  */

/** @defgroup CAN_Time_Quanta_In_Bit_Segment_2
  * @{
  */
#define CAN_BS2_1TQ                 ((uint8_t)0x00)  /*!< 1 time quanta */
#define CAN_BS2_2TQ                 ((uint8_t)0x01)  /*!< 2 time quanta */
#define CAN_BS2_3TQ                 ((uint8_t)0x02)  /*!< 3 time quanta */
#define CAN_BS2_4TQ                 ((uint8_t)0x03)  /*!< 4 time quanta */
#define CAN_BS2_5TQ                 ((uint8_t)0x04)  /*!< 5 time quanta */
#define CAN_BS2_6TQ                 ((uint8_t)0x05)  /*!< 6 time quanta */
#define CAN_BS2_7TQ                 ((uint8_t)0x06)  /*!< 7 time quanta */
#define CAN_BS2_8TQ                 ((uint8_t)0x07)  /*!< 8 time quanta */

/**
  * @}
  */


/** @defgroup CAN_Filter_Mode
  * @{
  */
#define CAN_FILTERMODE_MASK            ((uint8_t)0x00)  /*!< mask mode */
#define CAN_FILTERMODE_LIST            ((uint8_t)0x01)  /*!< List mode */

/**
  * @}
  */

/** @defgroup CAN_Filter_Scale
  * @{
  */
#define CAN_FILTERSCALE_16BIT       ((uint8_t)0x00) /*!< Two 16-bit filters */
#define CAN_FILTERSCALE_32BIT       ((uint8_t)0x01) /*!< One 32-bit filter */

/**
  * @}
  */

/** @defgroup CAN_Filter_FIFO
  * @{
  */
#define CAN_FILTER_FIFO0             ((uint8_t)0x00)  /*!< Filter associated with FIFO0 */
#define CAN_FILTER_FIFO1             ((uint8_t)0x01)  /*!< Filter associated with FIFO1 */

/**
  * @}
  */

/** @defgroup CAN_Format_Frame
  * @{
  */
#define CAN_FF_STANDARD             ((uint32_t)0x00000000)  /*!< Standard format frame */
#define CAN_FF_EXTENDED             ((uint32_t)0x00000004)  /*!< Extended format frame */

/**
  * @}
  */

/** @defgroup CAN_Frame_Type
  * @{
  */
#define CAN_FT_DATA                ((uint32_t)0x00000000)  /*!< Data frame */
#define CAN_FT_REMOTE              ((uint32_t)0x00000002)  /*!< Remote frame */

/**
  * @}
  */

/** @defgroup CAN_Transmit_State
  * @{
  */
#define CAN_TXSTATE_FAILED         ((uint8_t)0x00)/*!< CAN transmitted failure */
#define CAN_TXSTATE_OK             ((uint8_t)0x01) /*!< CAN transmitted success */
#define CAN_TXSTATE_PENDING        ((uint8_t)0x02) /*!< CAN transmitted pending */
#define CAN_TXSTATE_NOMAILBOX      ((uint8_t)0x04) /*!< No empty mailbox to be used for CAN */

/**
  * @}
  */

/** @defgroup CAN_Receive_FIFO_Number_Constants
  * @{
  */
#define CAN_FIFO0                 ((uint8_t)0x00) /*!< Use CAN FIFO 0 to receive */
#define CAN_FIFO1                 ((uint8_t)0x01) /*!< Use CAN FIFO 1 to receive */

/**
  * @}
  */

/** @defgroup CAN_Sleep_Constants
  * @{
  */
#define CAN_SLEEP_FAILED     ((uint8_t)0x00) /*!< CAN entered the sleep mode failed */
#define CAN_SLEEP_OK         ((uint8_t)0x01) /*!< CAN entered the sleep mode succeeded */

/**
  * @}
  */

/** @defgroup CAN_Wake_Wp_Constants
  * @{
  */
#define CAN_WAKEUP_FAILED        ((uint8_t)0x00) /*!< CAN leaved the sleep mode failed */
#define CAN_WAKEUP_OK            ((uint8_t)0x01) /*!< CAN leaved the sleep mode succeeded */

/**
  * @}
  */

/**
  * @defgroup   CAN_Error_Type_Constants
  * @{
  */
#define CAN_ERRORTYPE_NOERR           ((uint8_t)0x00) /*!< No Error */
#define CAN_ERRORTYPE_STUFFERR        ((uint8_t)0x10) /*!< Stuff Error */
#define CAN_ERRORTYPE_FORMERR         ((uint8_t)0x20) /*!< Form Error */
#define CAN_ERRORTYPE_ACKERR          ((uint8_t)0x30) /*!< Acknowledgment Error */
#define CAN_ERRORTYPE_BITRECESSIVEERR ((uint8_t)0x40) /*!< Bit Recessive Error */
#define CAN_ERRORTYPE_BITDOMINANTERR  ((uint8_t)0x50) /*!< Bit Dominant Error */
#define CAN_ERRORTYPE_CRCERR          ((uint8_t)0x60) /*!< CRC Error  */
#define CAN_ERRORTYPE_SOFTWARESETERR  ((uint8_t)0x70) /*!< Set by software */

/**
  * @}
  */

/** @defgroup CAN_flags
  * @{
  */
/* The flag value of 0x3XXXXXXX is used with CAN_GetBitState()and CAN_ClearBitState() functions. */
/* The flag value of 0x1XXXXXXX is only used with CAN_GetBitState() function.  */

/* Transmit Flags */
#define CAN_FLAG_MTF0              ((uint32_t)0x38000001) /*!< Mailbox 0 transmit finished Flag */
#define CAN_FLAG_MTF1              ((uint32_t)0x38000100) /*!< Mailbox 1 transmit finished Flag */
#define CAN_FLAG_MTF2              ((uint32_t)0x38010000) /*!< Mailbox 2 transmit finished Flag */

/* Receive Flags */
#define CAN_FLAG_RFL0              ((uint32_t)0x12000003) /*!< the length of the receive FIFO0 Flag */
#define CAN_FLAG_RFF0              ((uint32_t)0x32000008) /*!< Receive FIFO 0 full Flag */
#define CAN_FLAG_RFO0              ((uint32_t)0x32000010) /*!< Receive FIFO 0 overfull  Flag */
#define CAN_FLAG_RFL1              ((uint32_t)0x14000003) /*!< the length of the receive FIFO1 Flag */
#define CAN_FLAG_RFF1              ((uint32_t)0x34000008) /*!< Receive FIFO 1 full Flag */
#define CAN_FLAG_RFO1              ((uint32_t)0x34000010) /*!< Receive FIFO 1 overfull Flag */

/* Working Mode Flags, in CAN status register */
#define CAN_FLAG_WU                ((uint32_t)0x31000008) /*!< Wake up Flag */
#define CAN_FLAG_SLP               ((uint32_t)0x31000012) /*!< Sleep working state Flag */

/* Error Flags, in CAN error register  */
#define CAN_FLAG_WE                ((uint32_t)0x10F00001) /*!< Warning error Flag */
#define CAN_FLAG_PE                ((uint32_t)0x10F00002) /*!< Passive error Flag */
#define CAN_FLAG_BOE               ((uint32_t)0x10F00004) /*!< Bus-off error Flag */
#define CAN_FLAG_ET                ((uint32_t)0x30F00070) /*!< Error type Flag  */

/**
  * @}
  */


/** @defgroup CAN_interrupts
  * @{
  */
#define CAN_INT_TME                  ((uint32_t)0x00000001) /*!< Transmit mailbox empty Interrupt*/

/* Receive Interrupts */
#define CAN_INT_RFNE0                ((uint32_t)0x00000002) /*!< FIFO 0 not empty interrupt */
#define CAN_INT_RFF0                 ((uint32_t)0x00000004) /*!< FIFO 0 full Interrupt*/
#define CAN_INT_RFO0                 ((uint32_t)0x00000008) /*!< FIFO 0 overrun Interrupt*/
#define CAN_INT_RFNE1                ((uint32_t)0x00000010) /*!< FIFO 1 not empty interrupt*/
#define CAN_INT_RFF1                 ((uint32_t)0x00000020) /*!< FIFO 1 full Interrupt*/
#define CAN_INT_RFO1                 ((uint32_t)0x00000040) /*!< FIFO 1 overfull Interrupt*/

/* Working Mode Interrupts */
#define CAN_INT_WU                   ((uint32_t)0x00010000) /*!< Wake-up Interrupt*/
#define CAN_INT_SLP                  ((uint32_t)0x00020000) /*!< Sleep Interrupt*/

/* Error Interrupts */
#define CAN_INT_WE                   ((uint32_t)0x00000100) /*!< Warning error Interrupt*/
#define CAN_INT_PE                   ((uint32_t)0x00000200) /*!< Passive error Interrupt*/
#define CAN_INT_BOE                  ((uint32_t)0x00000400) /*!< Bus-off error Interrupt*/
#define CAN_INT_ET                   ((uint32_t)0x00000800) /*!< error type Interrupt*/
#define CAN_INT_ERR                  ((uint32_t)0x00008000) /*!< Error Interrupt*/

#define CAN_INT_MTF0   CAN_INT_TME
#define CAN_INT_MTF1   CAN_INT_TME
#define CAN_INT_MTF2   CAN_INT_TME

/**
  * @}
  */

/** @defgroup CAN_Legacy
  * @{
  */
#define CANINITFAILED               CAN_INITSTATE_FAILED
#define CANINITOK                   CAN_INITSTATE_SUCCESS
#define CAN_FILTERFIFO0             CAN_FILTER_FIFO0
#define CAN_FILTERFIFO1             CAN_FILTER_FIFO1
#define CAN_FF_STD                  CAN_FF_STANDARD
#define CAN_FF_EXT                  CAN_FF_EXTENDED
//#define CAN_FT_DATA                 CAN_FT_DATA
//#define CAN_FT_REMOTE               CAN_FT_REMOTE
#define CANTXFAILE                  CAN_TXSTATE_FAILED
#define CANTXOK                     CAN_TXSTATE_OK
#define CANTXPENDING                CAN_TXSTATE_PENDING
#define CAN_NO_MB                   CAN_TXSTATE_NOMAILBOX
#define CANSLEEPFAILED              CAN_SLEEP_FAILED
#define CANSLEEPOK                  CAN_SLEEP_OK
#define CANWAKEUPFAILED             CAN_WAKEUP_FAILED
#define CANWAKEUPOK                 CAN_WAKEUP_OK

/**
  * @}
  */

/**
  * @}
  */


/** @defgroup CAN_Exported_Functions
  * @{
  */
void CAN_DeInit(CAN_TypeDef *CANx);
uint8_t CAN_Init(CAN_TypeDef *CANx, CAN_InitPara *CAN_InitParaStruct);
void CAN_FilterInit(CAN_FilterInitPara *CAN_FilterInitParaStruct);
void CAN_StructInit(CAN_InitPara *CAN_InitParaStruct);
void CAN_HeaderBank(uint8_t CAN_HeaderBankNumber);
void CAN_DebugFreeze(CAN_TypeDef *CANx, TypeState NewValue);
void CAN_TimeTrigComMode_Enable(CAN_TypeDef *CANx, TypeState NewValue);

/* Transmit functions */
uint8_t CAN_Transmit(CAN_TypeDef *CANx, CanTxMessage *TxMessage);
uint8_t CAN_TransmitState(CAN_TypeDef *CANx, uint8_t TransmitMailbox);
void CAN_StopTransmit(CAN_TypeDef *CANx, uint8_t Mailbox);

/* Receive functions */
void CAN_Receive(CAN_TypeDef *CANx, uint8_t FIFONumber, CanRxMessage *RxMessage);
void CAN_FIFODequeue(CAN_TypeDef *CANx, uint8_t FIFONumber);
uint8_t CAN_MessageLength(CAN_TypeDef *CANx, uint8_t FIFONumber);


/* Working modes functions */
uint8_t CAN_WorkingMode(CAN_TypeDef *CANx, uint8_t CAN_WorkingMode);
uint8_t CAN_EnterSleep(CAN_TypeDef *CANx);
uint8_t CAN_WakeUp(CAN_TypeDef *CANx);

/* Error management functions */
uint8_t CAN_GetErrorType(CAN_TypeDef *CANx);
uint8_t CAN_GetReceiveErrorCounter(CAN_TypeDef *CANx);
uint8_t CAN_GetTransmitErrorCounter(CAN_TypeDef *CANx);

/* Interrupts and flags management functions */
void CAN_INTConfig(CAN_TypeDef *CANx, uint32_t CAN_INT, TypeState NewValue);
TypeState CAN_GetBitState(CAN_TypeDef *CANx, uint32_t CAN_FLAG);
void CAN_ClearBitState(CAN_TypeDef *CANx, uint32_t CAN_FLAG);
TypeState CAN_GetIntBitState(CAN_TypeDef *CANx, uint32_t CAN_INT);
void CAN_ClearIntBitState(CAN_TypeDef *CANx, uint32_t CAN_INT);
static TypeState CheckINTState(uint32_t CAN_Reg, uint32_t Int_Bit);

#ifdef __cplusplus
}
#endif

#endif /* __GD32F10x_CAN_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
