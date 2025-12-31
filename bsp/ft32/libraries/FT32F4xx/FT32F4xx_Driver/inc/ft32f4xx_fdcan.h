/**
  ******************************************************************************
  * @file               ft32f4xx_fdcan.h
  * @author             FMD AE
  * @brief              This file contains all the functions prototypes for the FDCAN firmware
  *                     library.
  * @version            V1.0.0
  * @data                   2025-03-06
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_FDCAN_H
#define __FT32F4XX_FDCAN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"


/** @addtogroup FDCAN
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  FDCAN Init structure definition
  */
typedef struct
{

    uint32_t Mode;                                   /*!< Specifies the FDCAN mode.
                                                        This parameter can be a value of @ref FDCAN_operating_mode   */

    uint32_t FrameFormat;                            /*!< Specifies the FDCAN frame format.
                                                        This parameter can be a value of @ref FDCAN_frame_format
                                                        Be used config CAN_F_SEG_UNIT_SET register                   */

    FunctionalState AutoPrimaryRetransmission;       /*!< Enable or disable the automatic retransmission mode for PTB.
                                                        This parameter can be set to ENABLE or DISABLE               */

    FunctionalState AutoSecondaryRetransmission;     /*!< Enable or disable the automatic retransmission mode for STB.
                                                        This parameter can be set to ENABLE or DISABLE               */

    FunctionalState TTCANMode;                       /*!< Enable or disable the Time Trigger CAN.
                                                        This parameter can be set to ENABLE or DISABLE*/

    uint32_t FDCANSACK;                              /*!< Specifies the Self-ACKnowledge in External LoopBack mode.
                                                        This parameter can be a value of @ref FDCAN_SACK */

    uint32_t ReceiveBufferStoreAllFrames;            /*!< Specifies the receive buffer stores all frames or normal frames.
                                                        This parameter can be a value of @FDCAN_ReceiveBufferStoreAllFrames */

    uint32_t NominalPrescaler;                       /*!< Specifies the value by which the oscillator frequency is
                                                        divided for generating the nominal bit time quanta.
                                                        This parameter must be a number between 1 and 255            */

    uint32_t NominalSyncJumpWidth;                   /*!< Specifies the maximum number of time quanta the FDCAN
                                                        hardware is allowed to lengthen or shorten a bit to perform
                                                        resynchronization.
                                                        This parameter must be a number between 2 and 127            */

    uint32_t NominalTimeSeg1;                        /*!< Specifies the number of time quanta in Bit Segment 1.
                                                        This parameter must be a number between 3 and 255            */

    uint32_t NominalTimeSeg2;                        /*!< Specifies the number of time quanta in Bit Segment 2.
                                                        This parameter must be a number between 2 and 127            */

    uint32_t DataPrescaler;                          /*!< Specifies the value by which the oscillator frequency is
                                                        divided for generating the data bit time quanta.
                                                        This parameter must be a number between 1 and 255             */

    uint32_t DataSyncJumpWidth;                      /*!< Specifies the maximum number of time quanta the FDCAN
                                                        hardware is allowed to lengthen or shorten a data bit to
                                                        perform resynchronization.
                                                        This parameter must be a number between 2 and 15             */

    uint32_t DataTimeSeg1;                           /*!< Specifies the number of time quanta in Data Bit Segment 1.
                                                        This parameter must be a number between 3 and 31             */

    uint32_t DataTimeSeg2;                           /*!< Specifies the number of time quanta in Data Bit Segment 2.
                                                        This parameter must be a number between 2 and 15             */

    uint32_t TimeTriggerPrescaler;                   /*!< Specifies the value by which bit time is divided for
                                                        time trigger timer.
                                                        This parameter can be a value of @ref Time_Trigger_Prescaler */

    uint32_t TriggerTime;                            /*!< Specifies the cycle time for a trigger.
                                                        This paramter must be a value between 0 and 255              */

    uint32_t TransmitEnableWindow;                   /*!< Specifies the ticks of transmit enable window.
                                                        This paramter must be a value between 0 and 15               */

    uint32_t TimeTriggerType;                        /*!< Specifies the kind of trigger in Time Trigger mode.
                                                        This paramter can be a value of @ref FDCAN_Trigger_Type      */

    uint32_t TransmitTriggerTbSolt;                  /*!< Specifies the TTPTR */

    uint32_t WatchTriggerTime;                       /*!< Specifies the cycle time for a watch trigger.
                                                        This paramter must be a value between 0 and 255              */

} FDCAN_InitTypeDef;


/**
  * @brief  FDCAN filter structure definition
  */
typedef struct
{
    uint32_t FilterAddress;                          /*!< Specifies the filter which will be initialized.
                                                        This parameter must be a number between:
                                                         - 0 and 15 */

    FunctionalState SelectAcceptanceMask;            /*!< Enable or disable the filter mask.
                                                        This parameter can be set to ENABLE or DISABLE        */

    uint32_t FilterAcceptanceCODE;                   /*!< Specifies the filter identification.
                                                        This parameter must be a number between:
                                                         - 0 and 0x7FF for standard frames
                                                         - 0 and 0x1FFFFFFF for extended frames               */

    uint32_t FilterAcceptanceMASK;                   /*!< Specifies the filter acceptance mask.
                                                        1 : acceptance check for these bis of receive ID disable
                                                        0 : acceptance check for these bis of receive ID enable
                                                        This parameter must be a number between:
                                                         - 0 and 0x7FF for standard frames
                                                         - 0 and 0x1FFFFFFF for extended frames               */

    uint32_t FilterAcceptanceMaskIDECheck;           /*!< Specifies the filter acceptance mask IDE bit check enable.
                                                        This parameter can be a value of @Acceptance_Mask_IDE_Check_Enable */

    uint32_t FilterAcceptanceMaskIDE;                /*!< Specifies the filter acceptance mask IDE bit value.
                                                        This parameter can be a value of @Acceptance_Mask_IDE_Type,
                                                        only valid if FilterAcceptanceMaskIDECheck is enable. */

} FDCAN_FilterTypeDef;



/**
  * @brief  FDCAN Tx header structure definition
  */
typedef struct
{
    uint32_t Identifier;                             /*!< Specifies the identifier.
                                                        This parameter must be a number between:
                                                         - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
                                                         - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID               */

    uint32_t IdType;                                 /*!< Specifies the identifier type for the transmitted message.
                                                        This parameter can be a value of @ref FDCAN_id_type               */

    uint32_t TxFrameType;                            /*!< Specifies the frame type of the transmitted message.
                                                        This parameter can be a value of @ref FDCAN_frame_type            */

    uint32_t DataLength;                             /*!< Specifies the length of the transmitted frame.
                                                        This parameter can be a value of @ref FDCAN_data_length_code      */

    uint32_t BitRateSwitch;                          /*!< Specifies whether the Tx frame is transmitted with or without bit
                                                        rate switching.
                                                        This parameter can be a value of @ref FDCAN_bit_rate_switching    */

    uint32_t FDFormat;                               /*!< Specifies whether the Tx frame is transmitted in classic or FD
                                                        format.
                                                        This parameter can be a value of @ref FDCAN_format                */

    uint32_t TTSEN;                                  /*!< Specifies the enable if transmit Time-Stamp in CiA 603.
                                                        This patameter can be a value of @ref Transmit_Time_Stamp_Enable */

} FDCAN_TxHeaderTypeDef;

/**
  * @brief  FDCAN Rx header structure definition
  */
typedef struct
{
    uint32_t Identifier;                             /*!< Specifies the identifier.
                                                        This parameter must be a number between:
                                                         - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
                                                         - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID               */

    uint32_t IdType;                                 /*!< Specifies the identifier type of the received message.
                                                        This parameter can be a value of @ref FDCAN_id_type               */

    uint32_t RxFrameType;                            /*!< Specifies the the received message frame type.
                                                        This parameter can be a value of @ref FDCAN_frame_type            */

    uint32_t DataLength;                             /*!< Specifies the received frame length.
                                                         This parameter can be a value of @ref FDCAN_data_length_code     */

    uint32_t ErrorStateIndicator;                    /*!< Specifies the error state indicator.
                                                        This parameter can be a value of @ref FDCAN_error_state_indicator */

    uint32_t BitRateSwitch;                          /*!< Specifies whether the Rx frame is received with or without bit
                                                        rate switching.
                                                        This parameter can be a value of @ref FDCAN_bit_rate_switching    */

    uint32_t FDFormat;                               /*!< Specifies whether the Rx frame is received in classic or FD
                                                        format.
                                                        This parameter can be a value of @ref FDCAN_format                */


    uint32_t RxKOER;                                 /*!< Specifies the kind of ERROR of receive frames.
                                                        This parameter can be a value of @ref FDCAN_Error_Kind            */

    uint32_t CycleTime;                              /*!< Specifies the time-stamp cycle time only in TTCAN mode.
                                                        This parameter must be a number between 0 and 0xFFFF              */

} FDCAN_RxHeaderTypeDef;

/**
  * @brief  FDCAN Error and Arbitration structure definition
  */
typedef struct
{
    uint32_t ArbitrationLostCapture;                 /*!< Specifies the bit position in the frame where the arbitration
                                                        has been lost.
                                                        This parameter must be a number between 0 and 31                  */

} FDCAN_ArbitrationLostCaptureTypeDef;

/**
  * @brief  FDCAN Error Counters structure definition
  */
typedef struct
{
    uint32_t TxErrorCnt;                             /*!< Specifies the Transmit Error Counter Value.
                                                        This parameter can be a number between 0 and 255                  */

    uint32_t RxErrorCnt;                             /*!< Specifies the Receive Error Counter Value.
                                                        This parameter can be a number between 0 and 255                  */

    uint32_t KOER;                                   /*!< Specifies the kind of Error.
                                                        This parameter can be a value of @ref FDCAN_Error_Kind            */

} FDCAN_ErrorCountersTypeDef;

#define Empty                           ((uint32_t)0x00000000U)
#define Less_HalfFull                   ((uint32_t)0x00000001U)
#define More_HalfFull                   ((uint32_t)0x00000002U)
#define Full                            ((uint32_t)0x00000003U)

#define CAN_INT_FLAG1_MASK              ((uint32_t)0xFFEA00FFU)

/* Exported constants --------------------------------------------------------*/
/** @defgroup FDCAN_operating_mode
  * @{
  */
#define FDCAN_MODE_NORMAL               ((uint32_t)0x00000000U) /*!< Normal mode               */
#define FDCAN_MODE_LOM                  ((uint32_t)0x00004000U) /*!< Listen Only mode          */
#define FDCAN_MODE_INTERNAL_LOOPBACK    ((uint32_t)0x00000020U) /*!< Internal LoopBack mode    */
#define FDCAN_MODE_EXTERNAL_LOOPBACK    ((uint32_t)0x00000040U) /*!< External LoopBack mode    */
/**
  * @}
  */

/** @defgroup FDCAN_frame_format
  * @{
  */
#define FDCAN_FRAME_CLASSIC             ((uint32_t)0x00000000U)  /*!< Classic mode                      */
#define FDCAN_FRAME_FD_NO_BRS           ((uint32_t)0x00000001U)  /*!< FD mode without BitRate Switching */
#define FDCAN_FRAME_FD_BRS              ((uint32_t)0x00000002U)  /*!< FD mode with BitRate Switching    */
/**
  * @}
  */


/** @defgroup TBUF_select
  * @{
  */
#define FDCAN_SELECT_PTB                ((uint32_t)0x00000000U)        /*!< Select PTB */
#define FDCAN_SELECT_STB                ((uint32_t)CAN_CMD_CTRL_TBSEL) /*!< Select STB */
/**
  * @}
  */

/** @defgroup FDCAN_STBFifoPriority_Mode
  * @{
  */
#define FDCAN_STB_FIFO                  ((uint32_t)0x00000000U)         /*!< FIFO mode for STB              */
#define FDCAN_STB_PRIORITY              ((uint32_t)CAN_CMD_CTRL_TSMODE) /*!< Priority decision mode for STB */
/**
  * @}
  */

/** @defgroup FDCAN_STBTransmitOneAll_Mode
  * @{
  */
#define FDCAN_STB_NO_TRANSMIT           ((uint32_t)0x00000000U)        /*!< No transmission for the STB                   */
#define FDCAN_STB_NO_TRANSMIT_ONE       ((uint32_t)CAN_CMD_CTRL_TSONE) /*!< Transmisson enable of one in the STB          */
#define FDCAN_STB_NO_TRANSMIT_ALL       ((uint32_t)CAN_CMD_CTRL_TSALL) /*!< Transmisson enable of all messages in the STB */
/**
  * @}
  */

/** @defgroup FDCAN_SACK
  * @{
  */
#define FDCAN_NO_SACK                   ((uint32_t)0x00000000U)        /*!< No self-ACK                                  */
#define FDCAN_SACK                      ((uint32_t)CAN_CMD_CTRL_SACK)  /*!< Self-ACK when LBME=1(External LoopBack mode) */
/**
  * @}
  */

/** @defgroup FDCAN_ReceiveBufferOverflow_Mode
  * @{
  */
#define FDCAN_RECEIVE_OVERFLOW_OVERWRITTEN     ((uint32_t)0x00000000U)        /*!< The oldest message will be overwritten */
#define FDCAN_RECEIVE_OVERFLOW_DISCARD         ((uint32_t)CAN_CMD_CTRL_ROM)   /*!< The new message will not be stored     */
#define IS_RECEIVE_BUFFER_OVERFLOW_MODE(ROM)  (((ROM)==FDCAN_RECEIVE_OVERFLOW_OVERWRITTEN) || \
                                               ((ROM)==FDCAN_RECEIVE_OVERFLOW_DISCARD)        )


/**
  * @}
  */

/** @defgroup FDCAN_ReceiveBufferStoreAllFrames
  * @{
  */
#define FDCAN_RBUF_STORE_NORMAL_OPERATION  ((uint32_t)0x00000000U)        /*!< Receive buffer only store valid data frames */
#define FDCAN_RBUF_STORE_ALL_DATA_FRAMES   ((uint32_t)CAN_CMD_CTRL_RBALL) /*!< Receive buffer store correct data frames as well as data frame with error */
/**
  * @}
  */



/** @defgroup Acceptance_Mask_IDE_Check_Enable
  * @{
  */
#define FDCAN_ACCEP_MASK_AIDE_DISABLE      ((uint32_t)0x00000000U)        /*!< Acceptance filter accepts frame both standard or extended */
#define FDCAN_ACCEP_MASK_AIDE_ENABLE       ((uint32_t)CAN_ACF_AIDEE)      /*!< Acceptance filter accepts frame define by FilterAcceptanceMaskIDE */
/**
  * @}
  */

/** @defgroup Acceptance_Mask_IDE_Type
  * @{
  */
#define FDCAN_ACCEP_MASK_IDE_STANDARD      ((uint32_t)0x00000000U)        /*!< Acceptance filter accepts only extended frames */
#define FDCAN_ACCEP_MASK_IDE_EXTENDED      ((uint32_t)CAN_ACF_AIDE)       /*!< Acceptance filter accepts only standard frames */
/**
  * @}
  */

/** @defgroup FDCAN_id_type
  * @{
  */
#define FDCAN_STANDARD_ID               ((uint32_t)0x00000000U)        /*!< Standard ID element */
#define FDCAN_EXTENDED_ID               ((uint32_t)0x00000080U)        /*!< Extended ID element */
#define IS_FDCAN_IDTYPE(TYPE)    (((TYPE)==FDCAN_STANDARD_ID) | \
                                  ((TYPE)==FDCAN_EXTENDED_ID) )

/**
  * @}
  */

/** @defgroup FDCAN_frame_type
  * @{
  */
#define FDCAN_DATA_FRAME                ((uint32_t)0x00000000U)        /*!< Data frame   */
#define FDCAN_REMOTE_FRAME              ((uint32_t)0x00000040U)        /*!< Remote frame */
#define IS_FDCAN_FRAME_TYPE(TYPE)      (((TYPE)==FDCAN_DATA_FRAME) || \
                                        ((TYPE)==FDCAN_REMOTE_FRAME) )
/**
  * @}
  */

/** @defgroup FDCAN_data_length_code
  * @{
  */
#define FDCAN_DLC_BYTES_0               ((uint32_t)0x00000000U)        /*!< 0 bytes data field  */
#define FDCAN_DLC_BYTES_1               ((uint32_t)0x00000001U)        /*!< 1 bytes data field  */
#define FDCAN_DLC_BYTES_2               ((uint32_t)0x00000002U)        /*!< 2 bytes data field  */
#define FDCAN_DLC_BYTES_3               ((uint32_t)0x00000003U)        /*!< 3 bytes data field  */
#define FDCAN_DLC_BYTES_4               ((uint32_t)0x00000004U)        /*!< 4 bytes data field  */
#define FDCAN_DLC_BYTES_5               ((uint32_t)0x00000005U)        /*!< 5 bytes data field  */
#define FDCAN_DLC_BYTES_6               ((uint32_t)0x00000006U)        /*!< 6 bytes data field  */
#define FDCAN_DLC_BYTES_7               ((uint32_t)0x00000007U)        /*!< 7 bytes data field  */
#define FDCAN_DLC_BYTES_8               ((uint32_t)0x00000008U)        /*!< 8 bytes data field  */
#define FDCAN_DLC_BYTES_12              ((uint32_t)0x00000009U)        /*!< 12 bytes data field */
#define FDCAN_DLC_BYTES_16              ((uint32_t)0x0000000AU)        /*!< 16 bytes data field */
#define FDCAN_DLC_BYTES_20              ((uint32_t)0x0000000BU)        /*!< 20 bytes data field */
#define FDCAN_DLC_BYTES_24              ((uint32_t)0x0000000CU)        /*!< 24 bytes data field */
#define FDCAN_DLC_BYTES_32              ((uint32_t)0x0000000DU)        /*!< 32 bytes data field */
#define FDCAN_DLC_BYTES_48              ((uint32_t)0x0000000EU)        /*!< 48 bytes data field */
#define FDCAN_DLC_BYTES_64              ((uint32_t)0x0000000FU)        /*!< 64 bytes data field */
#define IS_FDCAN_DATA_LENGTH(LENGTH)    ((LENGTH==FDCAN_DLC_BYTES_0)  ||  (LENGTH == FDCAN_DLC_BYTES_1)  || \
                                         (LENGTH==FDCAN_DLC_BYTES_2)  ||  (LENGTH == FDCAN_DLC_BYTES_3)  || \
                                         (LENGTH==FDCAN_DLC_BYTES_4)  ||  (LENGTH == FDCAN_DLC_BYTES_5)  || \
                                         (LENGTH==FDCAN_DLC_BYTES_6)  ||  (LENGTH == FDCAN_DLC_BYTES_7)  || \
                                         (LENGTH==FDCAN_DLC_BYTES_8)  ||  (LENGTH == FDCAN_DLC_BYTES_12) || \
                                         (LENGTH==FDCAN_DLC_BYTES_16) ||  (LENGTH == FDCAN_DLC_BYTES_20) || \
                                         (LENGTH==FDCAN_DLC_BYTES_24) ||  (LENGTH == FDCAN_DLC_BYTES_32) || \
                                         (LENGTH==FDCAN_DLC_BYTES_48) ||  (LENGTH == FDCAN_DLC_BYTES_64))
/**
  * @}
  */

/** @defgroup FDCAN_bit_rate_switching
  * @{
  */
#define FDCAN_BRS_OFF                   ((uint32_t)0x00000000U)        /*!< FDCAN frames transmitted/received without bit rate switching */
#define FDCAN_BRS_ON                    ((uint32_t)0x00000010U)        /*!< FDCAN frames transmitted/received with bit rate switching    */
#define IS_FDCAN_BRS(BRS)               ((BRS == FDCAN_BRS_OFF) || (BRS == FDCAN_BRS_ON))
/**
  * @}
  */

/** @defgroup FDCAN_format
  * @{
  */
#define FDCAN_CLASSIC_CAN               ((uint32_t)0x00000000U)        /*!< Frame transmitted/received in Classic CAN format */
#define FDCAN_FD_CAN                    ((uint32_t)0x00000020U)        /*!< Frame transmitted/received in FDCAN format       */
#define IS_FDCAN_TYPE(TYPE)             ((TYPE == FDCAN_CLASSIC_CAN) || (TYPE == FDCAN_FD_CAN))
/**
  * @}
  */

/** @defgroup Transmit_Time_Stamp_Enable
  * @{
  */
#define FDCAN_TTS_DISABLE               ((uint32_t)0x00000000U)        /*!< No acquisition of a transmit time stamp for this frame */
#define FDCAN_TTS_ENABLE                ((uint32_t)0x80000000U)        /*!< TTS update enabled                                     */
#define IS_FDCAN_TTS_STATE(STATE)       ((STATE ==FDCAN_TTS_DISABLE) || (STATE ==FDCAN_TTS_ENABLE))
/**
  * @}
  */

/** @defgroup FDCAN_error_state_indicator
  * @{
  */
#define FDCAN_ESI_ACTIVE                ((uint32_t)0x00000000U)        /*!< CAN node is error active  */
#define FDCAN_ESI_PASSIVE               ((uint32_t)0x80000000U)        /*!< CAN node is error passive */
#define IS_FDCAN_ERROR_STATE_INDICATOR(STATE) ((STATE == FDCAN_ESI_ACTIVE) || (STATE == FDCAN_ESI_PASSIVE))
/**
  * @}
  */

/** @defgroup FDCAN_Error_Kind
  * @{
  */
#define FDCAN_NO_ERROR                  ((uint32_t)0x00000000U)        /*!< No error              */
#define FDCAN_BIT_ERROR                 ((uint32_t)0x00000001U)        /*!< Bit error             */
#define FDCAN_FORM_ERROR                ((uint32_t)0x00000002U)        /*!< Form error            */
#define FDCAN_STUFF_ERROR               ((uint32_t)0x00000003U)        /*!< Stuff error           */
#define FDCAN_ACK_ERROR                 ((uint32_t)0x00000004U)        /*!< Acknowledgement error */
#define FDCAN_CRC_ERROR                 ((uint32_t)0x00000005U)        /*!< CRC error             */
#define FDCAN_OTHER_ERROR               ((uint32_t)0x00000006U)        /*!< Other error           */
#define FDCAN_NOT_USED                  ((uint32_t)0x00000007U)        /*!< Not used              */
/**
  * @}
  */

/** @defgroup Time_Trigger_Prescaler
  * @{
  */
#define FDCAN_TIME_TRIGGER_PRESCALER_1     ((uint32_t)0x00000000U)     /*!< No prescaler */
#define FDCAN_TIME_TRIGGER_PRESCALER_2     ((uint32_t)0x02000000U)     /*!< Divide 2     */
#define FDCAN_TIME_TRIGGER_PRESCALER_4     ((uint32_t)0x04000000U)     /*!< Divide 4     */
#define FDCAN_TIME_TRIGGER_PRESCALER_8     ((uint32_t)0x06000000U)     /*!< Divide 8     */
/**
  * @}
  */

/** @defgroup FDCAN_Trigger_Type
  * @{
  */
#define FDCAN_TTCAN_IMMEDIATE_TRIG      ((uint32_t)0x00000000U)        /*!< Immediate Trigger */
#define FDCAN_TTCAN_TIME_TRIG           ((uint32_t)0x00000100U)        /*!< Time Trigger */
#define FDCAN_TTCAN_SINGLE_SHOT_TRIG    ((uint32_t)0x00000200U)        /*!< Single Shot Transmit Trigger */
#define FDCAN_TTCAN_TRANSMIT_START_TRIG ((uint32_t)0x00000300U)        /*!< Transmit start Trigger */
#define FDCAN_TTCAN_TRANSMIT_STOP_TRIG  ((uint32_t)0x00000400U)        /*!< Transmit stop Trigger */
/**
  * @}
  */



/** @defgroup
  * @{
  */

/**
  * @}
  */

/** @defgroup FDCAN_Interrupts
  * @{
  */
#define FDCAN_IT_RECEIVE                    CAN_INT_FLAG1_RIE          /*!< Receive                             */
#define FDCAN_IT_RBUF_OVERRUN               CAN_INT_FLAG1_ROIE         /*!< RBUF overrun                        */
#define FDCAN_IT_RBUF_FULL                  CAN_INT_FLAG1_RFIE         /*!< RBUF full                           */
#define FDCAN_IT_RB_ALMOST_FULL             CAN_INT_FLAG1_RAFIE        /*!< RBUF almost full                    */
#define FDCAN_IT_TRANSMISSION_PRIMARY       CAN_INT_FLAG1_TPIE         /*!< Transmission primary successfully   */
#define FDCAN_IT_TRANSMISSION_SECONDARY     CAN_INT_FLAG1_TSIE         /*!< Transmission secondary successfully */
#define FDCAN_IT_ERROR                      CAN_INT_FLAG1_EIE          /*!< Error                               */
#define FDCAN_IT_ERROR_PASSIVE              CAN_INT_FLAG1_EPIE         /*!< Node is error passive               */
#define FDCAN_IT_ARBITRATION_LOST           CAN_INT_FLAG1_ALIE         /*!< Lost arbitration                    */
#define FDCAN_IT_BUS_ERROR                  CAN_INT_FLAG1_BEIE         /*!< Bus error                           */
#define FDCAN_IT_TIME_TRIGGER               CAN_INT_FLAG2_TTIE         /*!< Time Trigger                        */
#define FDCAN_IT_WATCH_TRIGGER              CAN_INT_FLAG2_WTIE         /*!< Watch Trigger                       */

/** @defgroup Interrupt_Masks Interrupt masks
  * @{
  */
#define FDCAN_IR_MASK ((uint32_t)0x902A00FEU) /*!< FDCAN interrupts mask */

#define FDCAN_TIMESTAMP_SOF                ((uint32_t)0x00000000U)
#define FDCAN_TIMESTAMP_EOF                ((uint32_t)0x00000200U)
#define IS_FDCAN_TIME_STAMP_LOCATION(LOC)  (((LOC) == FDCAN_TIMESTAMP_SOF) || \
                                            ((LOC) == FDCAN_TIMESTAMP_EOF)  )
#define FDCAN_TIMESTAMP_DISABLE            ((uint32_t)0x00000000U)
#define FDCAN_TIMESTAMP_ENABLE             ((uint32_t)0x00000100U)

#define FDCAN_TXDELAY_DISABLE              ((uint32_t)0x00000000U)
#define FDCAN_TXDELAY_ENABLE               ((uint32_t)0x00008000U)
/* Exported functions --------------------------------------------------------*/
/** @addtogroup FDCAN_Exported_Functions
  * @{
  */
/* Initialization and Configuration functions *********************************/

/**
  * @}
  */



/* Private macros ------------------------------------------------------------*/
/** @defgroup FDCAN_Private_Macros FDCAN Private Macros
  * @{
  */

#define IS_FDCAN_ALL_INSTANCE(PERIPH) ((PERIPH == FDCAN1) || \
                                       (PERIPH == FDCAN2) || \
                                       (PERIPH == FDCAN3) || \
                                       (PERIPH == FDCAN4))
#define IS_FDCAN_MODE(MODE) ((MODE == FDCAN_MODE_NORMAL           ) || \
                             (MODE == FDCAN_MODE_LOM              ) || \
                             (MODE == FDCAN_MODE_INTERNAL_LOOPBACK) || \
                             (MODE == FDCAN_MODE_EXTERNAL_LOOPBACK))
#define IS_FDCAN_FRAME_FORMAT(FRAME_FORMAT) ((FRAME_FORMAT == FDCAN_FRAME_CLASSIC  ) || \
                                             (FRAME_FORMAT == FDCAN_FRAME_FD_NO_BRS) || \
                                             (FRAME_FORMAT == FDCAN_FRAME_FD_BRS   ))
#define IS_FDCAN_BUF_SEL(TBUF_SEL)  ((TBUF_SEL == FDCAN_SELECT_PTB)|| \
                                           (TBUF_SEL == FDCAN_SELECT_STB))
#define IS_FDCAN_STB_FP_MODE(STB_FP_MODE) ((STB_FP_MODE == FDCAN_STB_FIFO    ) || \
                                           (STB_FP_MODE == FDCAN_STB_PRIORITY))
#define IS_FDCAN_STB_OA_MODE(STB_OA_MODE) ((STB_OA_MODE == FDCAN_STB_NO_TRANSMIT ) || \
                                           (STB_OA_MODE == FDCAN_STB_NO_TRANSMIT_ONE) || \
                                           (STB_OA_MODE == FDCAN_STB_NO_TRANSMIT_ALL))
#define IS_FDCAN_TTCAN_TBUF_MODE(TTCAN_TBUF_MODE) ((TTCAN_TBUF_MODE == FDCAN_TTCAN_TRANSMIT_SEPARATE) || \
                                                   (TTCAN_TBUF_MODE == FDCAN_TTCAN_TRANSMIT_FULL    ))
#define IS_FDCAN_FDCANSACK(FDCANSACK) ((FDCANSACK == FDCAN_NO_SACK) || \
                                       (FDCANSACK == FDCAN_SACK   ))
#define IS_FDCAN_RBUF_OVERFLOW_MODE(OVERFLOW_MODE) ((OVERFLOW_MODE == FDCAN_RECEIVE_OVERFLOW_OVERWRITTEN) || \
                                                    (OVERFLOW_MODE == FDCAN_RECEIVE_OVERFLOW_DISCARD    ))
#define IS_FDCAN_RBUF_STORE_ALL(STORE_ALL) ((STORE_ALL == FDCAN_RBUF_STORE_NORMAL_OPERATION) || \
                                            (STORE_ALL == FDCAN_RBUF_STORE_ALL_DATA_FRAMES ))
#define IS_FDCAN_RBUF_AF_LIMIT(AF_LIMIT) ((AF_LIMIT >= 0U) && (AF_LIMIT <= 6U))
#define IS_FDCAN_PROG_ERROR_WARN_LIMIT(ERROR_WARN_LIMIT) ((ERROR_WARN_LIMIT >= 0U) && (ERROR_WARN_LIMIT <= 15U))
#define IS_FDCAN_NOMINAL_PRESCALER(N_PRESCALER) ((N_PRESCALER >= 0U) && (N_PRESCALER <= 255U))
#define IS_FDCAN_NOMINAL_SJW(N_SJW) ((N_SJW >= 0U) && (N_SJW <= 127U))
#define IS_FDCAN_NOMANAL_SEG1(N_SEG1) ((N_SEG1 >= 0U) && (N_SEG1 <= 255U))
#define IS_FDCAN_NOMANAL_SEG2(N_SEG2) ((N_SEG2 >= 0U) && (N_SEG2 <= 127U))
#define IS_FDCAN_DATA_PRESCALER(D_PRESCALER) ((D_PRESCALER >= 0U) && (D_PRESCALER <= 255U))
#define IS_FDCAN_DATA_SJW(D_SJW) ((D_SJW >= 0U) && (D_SJW <= 15U))
#define IS_FDCAN_DATA_SEG1(D_SEG1) ((D_SEG1 >= 0U) && (D_SEG1 <= 31U))
#define IS_FDCAN_DATA_SEG2(D_SEG2) ((D_SEG2 >= 0U) && (D_SEG2 <= 15U))
#define IS_FDCAN_TTCAN_PRESCALER(TTCAN_PRESCALER) ((TTCAN_PRESCALER == FDCAN_TIME_TRIGGER_PRESCALER_1) || \
                                                   (TTCAN_PRESCALER == FDCAN_TIME_TRIGGER_PRESCALER_2) || \
                                                   (TTCAN_PRESCALER == FDCAN_TIME_TRIGGER_PRESCALER_4) || \
                                                   (TTCAN_PRESCALER == FDCAN_TIME_TRIGGER_PRESCALER_8))
#define IS_FDCAN_TTCAN_REF_IDE(REF_IDE) ((REF_IDE == FDCAN_STANDARD_ID) || \
                                         (REF_IDE == FDCAN_EXTENDED_ID))
#define IS_FDCAN_ID(ID)               ((ID >= 0x0U) && (ID <= 0x1FFFFFFFU))
#define IS_FDCAN_TTCAN_REF_ID(REF_ID) ((REF_ID >= 0x0U) && (REF_ID <= 0x1FFFFFFFU))
#define IS_FDCAN_TTCAN_TBUF_POINTER(TTCAN_TBUF_POINTER) ((TTCAN_TBUF_POINTER >= 0U) && (TTCAN_TBUF_POINTER <= 3U))
#define IS_FDCAN_TTCAN_TYPE(TTCAN_TYPE) ((TTCAN_TYPE == FDCAN_TTCAN_IMMEDIATE_TRIG     ) || \
                                         (TTCAN_TYPE == FDCAN_TTCAN_TIME_TRIG          ) || \
                                         (TTCAN_TYPE == FDCAN_TTCAN_SINGLE_SHOT_TRIG   ) || \
                                         (TTCAN_TYPE == FDCAN_TTCAN_TRANSMIT_START_TRIG) || \
                                         (TTCAN_TYPE == FDCAN_TTCAN_TRANSMIT_STOP_TRIG ))
#define IS_FDCAN_TTCAN_TR_EN_WIN(TTCAN_TR_EN_WIN) ((TTCAN_TR_EN_WIN >= 0U) && (TTCAN_TR_EN_WIN <= 15U))
#define IS_FDCAN_TTCAN_TRIGGER_TIME(TTCAN_TRIGGER_TIME) ((TTCAN_TRIGGER_TIME >= 0U) && (TTCAN_TRIGGER_TIME <= 0XFFFFU))
#define IS_FDCAN_TTCAN_WATCH_TIME(TTCAN_WATCH_TIME) ((TTCAN_WATCH_TIME >= 0U) && (TTCAN_WATCH_TIME <= 0XFFFFU))

#define IS_FDCAN_FILTER_ADDR(ADDR) ((ADDR >= 0U) && (ADDR <= 15U))
#define IS_FDCAN_FILTER_ACODE(ACODE) ((ACODE >= 0U) && (ACODE <= 0x1FFFFFFFU))
#define IS_FDCAN_FILTER_AMASK(AMASK) ((AMASK >= 0U) && (AMASK <= 0x1FFFFFFFU))
#define IS_FDCAN_FILTER_AMASK_IDEE(AMASK_IDEE) ((AMASK_IDEE == FDCAN_ACCEP_MASK_AIDE_DISABLE) || \
                                                (AMASK_IDEE == FDCAN_ACCEP_MASK_AIDE_ENABLE ))
#define IS_FDCAN_FILTER_AMASK_IDE(AMASK_IDE) ((AMASK_IDE == FDCAN_ACCEP_MASK_IDE_STANDARD) || \
                                              (AMASK_IDE == FDCAN_ACCEP_MASK_IDE_EXTENDED))


#define IS_FDCAN_IT(IT)               (((IT) & ~(FDCAN_IR_MASK)) == 0U)

#define IS_FDCAN_TXDELAY_VALUE(VALUE) ((VALUE >= 0U) && (VALUE <= 0x7FU))

#define IS_FDCAN_ARBLOSTCAP_VALUE(VALUE) ((VALUE >= 0U) && (VALUE <= 0x1FU))

#define FDCAN_FLAG_ROV                        FDCAN_ISR_ROV
#define FDCAN_FLAG_RACTIVE                    FDCAN_ISR_RACTIVE
#define FDCAN_FLAG_TACTIVE                    FDCAN_ISR_TACTIVE
#define FDCAN_FLAG_EPIF                       CAN_INT_FLAG1_EPIF
#define FDCAN_FLAG_ALIF                       CAN_INT_FLAG1_ALIF
#define FDCAN_FLAG_BEIF                       CAN_INT_FLAG1_BEIF
#define FDCAN_FLAG_RIF                        CAN_INT_FLAG1_RIF
#define FDCAN_FLAG_ROIF                       CAN_INT_FLAG1_ROIF
#define FDCAN_FLAG_RFIF                       CAN_INT_FLAG1_RFIF
#define FDCAN_FLAG_RAFIF                      CAN_INT_FLAG1_RAFIF
#define FDCAN_FLAG_TPIF                       CAN_INT_FLAG1_TPIF
#define FDCAN_FLAG_TSIF                       CAN_INT_FLAG1_TSIF
#define FDCAN_FLAG_EIF                        CAN_INT_FLAG1_EIF
#define FDCAN_FLAG_AIF                        CAN_INT_FLAG1_AIF
#define FDCAN_FLAG_WTIF                       CAN_INT_FLAG2_WTIF
#define FDCAN_FLAG_TEIF                       CAN_INT_FLAG2_TEIF
#define FDCAN_FLAG_TTIF                       CAN_INT_FLAG2_TTIF
#define FDCAN_FLAG_RTIF_ALL                   ((uint32_t)0x0000FF00U)
#define IS_FDCAN_FLAG(FLAG) (((FLAG) == FDCAN_FLAG_RACTIVE) || ((FLAG) == FDCAN_FLAG_TACTIVE) || \
                             ((FLAG) == FDCAN_FLAG_ROV)     || ((FLAG) == FDCAN_FLAG_EPIF)    || \
                             ((FLAG) == FDCAN_FLAG_ALIF)    || ((FLAG) == FDCAN_FLAG_BEIF)    || \
                             ((FLAG) == FDCAN_FLAG_RIF)     || ((FLAG) == FDCAN_FLAG_ROIF)    || \
                             ((FLAG) == FDCAN_FLAG_RFIF)    || ((FLAG) == FDCAN_FLAG_RAFIF)   || \
                             ((FLAG) == FDCAN_FLAG_TPIF)    || ((FLAG) == FDCAN_FLAG_TSIF)    || \
                             ((FLAG) == FDCAN_FLAG_EIF)     || ((FLAG) == FDCAN_FLAG_AIF)     || \
                             ((FLAG) == FDCAN_FLAG_WTIF)    || ((FLAG) == FDCAN_FLAG_TEIF)    || \
                             ((FLAG) == FDCAN_FLAG_TTIF)    || ((FLAG) == FDCAN_FLAG_RTIF_ALL))

#define FDCAN_FLAG_REG_CMD                       ((uint32_t)0x00000000U)
#define FDCAN_FLAG_REG_FLAG1                     ((uint32_t)0x00000001U)
#define FDCAN_FLAG_REG_FLAG2                     ((uint32_t)0x00000002U)
#define IS_FDCAN_FLAG_REG(REG) (((REG) == FDCAN_FLAG_REG_CMD) || ((REG) == FDCAN_FLAG_REG_FLAG1) || \
                                ((REG) == FDCAN_FLAG_REG_FLAG2))

#define FDCAN_INT_REG_FLAG1                     ((uint32_t)0x00000001U)
#define FDCAN_INT_REG_FLAG2                     ((uint32_t)0x00000002U)
#define IS_FDCAN_INT_REG(REG)  (((REG) == FDCAN_INT_REG_FLAG1) || ((REG) == FDCAN_INT_REG_FLAG2))

#define FDCAN_TRANS_BUFFER_STAT                     ((uint32_t)0x00000000U)
#define FDCAN_RECEIVE_BUFFER_STAT                   ((uint32_t)0x00000001U)
#define FDCAN_TBUF_FULL                             FDCAN_ISR_TSSTAT
#define FDCAN_RBUF_FULL                             FDCAN_ISR_RSTAT

#define FDCAN_CAN_FILTER0                     CAN_FILTER_CTRL_AE_0
#define FDCAN_CAN_FILTER1                     CAN_FILTER_CTRL_AE_1
#define FDCAN_CAN_FILTER2                     CAN_FILTER_CTRL_AE_2
#define FDCAN_CAN_FILTER3                     CAN_FILTER_CTRL_AE_3
#define FDCAN_CAN_FILTER4                     CAN_FILTER_CTRL_AE_4
#define FDCAN_CAN_FILTER5                     CAN_FILTER_CTRL_AE_5
#define FDCAN_CAN_FILTER6                     CAN_FILTER_CTRL_AE_6
#define FDCAN_CAN_FILTER7                     CAN_FILTER_CTRL_AE_7
#define FDCAN_CAN_FILTER8                     CAN_FILTER_CTRL_AE_8
#define FDCAN_CAN_FILTER9                     CAN_FILTER_CTRL_AE_9
#define FDCAN_CAN_FILTER10                    CAN_FILTER_CTRL_AE_10
#define FDCAN_CAN_FILTER11                    CAN_FILTER_CTRL_AE_11
#define FDCAN_CAN_FILTER12                    CAN_FILTER_CTRL_AE_12
#define FDCAN_CAN_FILTER13                    CAN_FILTER_CTRL_AE_13
#define FDCAN_CAN_FILTER14                    CAN_FILTER_CTRL_AE_14
#define FDCAN_CAN_FILTER15                    CAN_FILTER_CTRL_AE_15
#define FDCAN_CAN_FILTER_ALL                  ((uint32_t)0xFFFF0000U)
#define IS_FDCAN_FILTER_ACE(ACE)           (((ACE) == FDCAN_CAN_FILTER0)  || ((ACE) == FDCAN_CAN_FILTER1)  || \
                                            ((ACE) == FDCAN_CAN_FILTER2)  || ((ACE) == FDCAN_CAN_FILTER3)  || \
                                            ((ACE) == FDCAN_CAN_FILTER4)  || ((ACE) == FDCAN_CAN_FILTER5)  || \
                                            ((ACE) == FDCAN_CAN_FILTER6)  || ((ACE) == FDCAN_CAN_FILTER7)  || \
                                            ((ACE) == FDCAN_CAN_FILTER8)  || ((ACE) == FDCAN_CAN_FILTER9)  || \
                                            ((ACE) == FDCAN_CAN_FILTER10) || ((ACE) == FDCAN_CAN_FILTER11) || \
                                            ((ACE) == FDCAN_CAN_FILTER12) || ((ACE) == FDCAN_CAN_FILTER13) || \
                                            ((ACE) == FDCAN_CAN_FILTER14) || ((ACE) == FDCAN_CAN_FILTER15) || \
                                            ((ACE) == FDCAN_CAN_FILTER_ALL))

/** @defgroup FDCAN_REF_MSG_id_type
  * @{
  */
#define FDCAN_REF_MSG_STD                 ((uint32_t)0x00000000U)        /*!< Standard ID element */
#define FDCAN_REF_MSG_EXT                 ((uint32_t)0x80000000U)        /*!< Extended ID element */
#define IS_FDCAN_REF_MSG_IDTYPE(TYPE)    (((TYPE)==FDCAN_REF_MSG_STD) | \
                                          ((TYPE)==FDCAN_REF_MSG_EXT) )

#define IS_FDCAN_REF_MSG_ID_VALUE(VALUE)  ((VALUE >= 0U) && (VALUE <= 0x1FFFFFFFU))

#define IS_FDCAN_TBPTR_VALUE(VALUE)  ((VALUE >= 0U) && (VALUE <= 0x3FU))
#define IS_FDCAN_TTPTR_VALUE(VALUE)  ((VALUE >= 0U) && (VALUE <= 0x3FU))

#define FDCAN_TIMEPOS_SOF                 ((uint32_t)0x00000000U)        /*!< TIME STAMP POSITION IN SOF */
#define FDCAN_TIMEPOS_EOF                 ((uint32_t)0x00000200U)        /*!< TIME STAMP POSITION IN EOF */
#define IS_FDCAN_TIME_POS(POS)           (((POS)==FDCAN_TIMEPOS_SOF) | \
                                          ((POS)==FDCAN_TIMEPOS_EOF) )




/**
  * @}
  */

/* Exported functions --------------------------------------------------------------- */
/** @addtogroup FDCAN_Exported_Functions
 *  @{
 */

/** @addtogroup FDCAN_Exported_Functions_Group1
 *  @{
 */
/* Initialization and de-initialization functions *************************************/
void FDCAN_Init(FDCAN_TypeDef* fdcan, FDCAN_InitTypeDef* fdcanInit);/*Function used initial fdcan*/
void FDCAN_DeInit(FDCAN_TypeDef* fdcan);/*Function used de-initial fdcan*/
void FDCAN_Reset(FDCAN_TypeDef* fdcan, FunctionalState NewState);/*Function used set fdcan in reset*/
void FDCAN_ConfigMode(FDCAN_TypeDef* fdcan, uint32_t Mode);/*Function used config fdcan mode*/
void FDCAN_SetRxBufAFWL(FDCAN_TypeDef* fdcan, uint32_t ReceiveBufferAlmostFullWarningLimit);/*Function used set fdcan AFWL*/
void FDCAN_SetEWL(FDCAN_TypeDef* fdcan, uint32_t ProgrammableErrorWarningLimit);/*Function used set fdcan EWL*/
void FDCAN_TransBufferSelect(FDCAN_TypeDef* fdcan, uint32_t TransBufferSelect);/*Function used select trans buffer*/
void FDCAN_TTCANTransBufferMode(FDCAN_TypeDef* fdcan, FunctionalState NewState);/*Function used select TTCAN Trans buffer Mode*/
void FDCAN_PTBTrans(FDCAN_TypeDef* fdcan, FunctionalState NewState);/*Function used start ptb trans*/
void FDCAN_PTBAbort(FDCAN_TypeDef* fdcan, FunctionalState NewState);/*Function used abort ptb trans*/
void FDCAN_TransSTBMode(FDCAN_TypeDef* fdcan, uint32_t STBFifoPriorityMode);/*Function used config tsmode*/
void FDCAN_STBTrans(FDCAN_TypeDef* fdcan, uint32_t STBTransmitOneAllMode, FunctionalState NewState);/*Function used start stb trans*/
void FDCAN_STBAbort(FDCAN_TypeDef* fdcan, FunctionalState NewState);/*Function used abort stb trans*/
uint8_t FDCAN_GetArbLostPosition(FDCAN_TypeDef* fdcan);/* Function use get arbitration lost position */
uint8_t FDCAN_GetKindOfError(FDCAN_TypeDef* fdcan);/* Function use get Kind Of Error */
void FDCAN_RxBufRelease(FDCAN_TypeDef* fdcan, FunctionalState NewState);/*Function used Release RxBuffer*/
void FDCAN_StandbyMode(FDCAN_TypeDef* fdcan, FunctionalState NewState);/*Function used enable can standby*/
void FDCAN_RbufOverFlowMode(FDCAN_TypeDef* fdcan, uint32_t FDCAN_ReceiveBufferOverflow_Mode);/*Function used config ROM*/



/**
  * @}
  */

/** @addtogroup FDCAN_Exported_Functions_Group2
 *  @{
 */
/* Configuration functions *************************************/
void FDCAN_ConfigFilter(FDCAN_TypeDef* fdcan, FDCAN_FilterTypeDef* sFilterConfig);/*Function used config filter*/
void FDCAN_EnableFilter(FDCAN_TypeDef* fdcan, uint32_t FDCAN_ACE, FunctionalState NewState);/*Function used enable or disable filter*/
void FDCAN_ConfigRxFifoOverwrite(FDCAN_TypeDef* fdcan, uint32_t FdcanRbOverMode);/*Function used config Receive Buffer write mode while full*/
void FDCAN_ConfigTimestampLocation(FDCAN_TypeDef* fdcan, uint32_t FdcanTimeStampLocation);/*Function used config timestamp Location*/
void FDCAN_EnableTimestampCounter(FDCAN_TypeDef* fdcan, FunctionalState NewState);/*Function used enable Fdcan timestamp*/
void FDCAN_ConfigTxDelayCompensation(FDCAN_TypeDef* fdcan, uint32_t FdcanTxDelayValue);/*Function used config TxDelay value */
void FDCAN_EnableTxDelayCompensation(FDCAN_TypeDef* fdcan, FunctionalState NewState);/*Function used enable Fdcan TxDelay */
void FDCAN_EnableISOMode(FDCAN_TypeDef* fdcan);/* Function used select ISO_CAN mode */
void FDCAN_DisableISOMode(FDCAN_TypeDef* fdcan);/* Function used select BoShi CAN_FD mode */
/**
  * @}
  */

/** @addtogroup FDCAN_Exported_Functions_Group3
 *  @{
 */
/* Configuration TxBuffer And Get RxBuffer  *************************************/
void FDCAN_ConfigTxBuffer(FDCAN_TypeDef* fdcan, FDCAN_TxHeaderTypeDef* TxHeader, uint8_t message_data[16][4]);/* Function used config TxBuffer */
void FDCAN_GetRxBuffer(FDCAN_TypeDef* fdcan, FDCAN_RxHeaderTypeDef* RxHeader, uint8_t message_data[16][4]);/* Function used get RxBuffer */
void FDCAN_GetArbLostCap(FDCAN_TypeDef* fdcan, FDCAN_ArbitrationLostCaptureTypeDef* ArbLostCap);/* Function used get ALC */
void FDCAN_GetErrorCnt(FDCAN_TypeDef* fdcan, FDCAN_ErrorCountersTypeDef* ErrorCnt);/* Function used get TECNT, RECNT and KOER */
void FDCAN_ConfigTsnext(FDCAN_TypeDef* fdcan);/* Function used set tsnext=1 and wait auto clear by hardware */
void FDCAN_ConfigInitialOffset(FDCAN_TypeDef* fdcan);/* Function used set initial offset value */
/**
  * @}
  */

/** @addtogroup FDCAN_Exported_Functions_Group4
 *  @{
 */
/* Interrupts management *************************************/
void FDCAN_ActivateNotification(FDCAN_TypeDef* fdcan, uint32_t FDCAN_INT_REG, uint32_t ActiveITs);/* Function used enable interrupt */
void FDCAN_DeactivateNotification(FDCAN_TypeDef* fdcan, uint32_t FDCAN_INT_REG, uint32_t InactiveITs);/* Function used disable interrupt */
FlagStatus FDCAN_GetFlagStatus(FDCAN_TypeDef* fdcan, uint32_t FDCAN_FLAG_REG, uint32_t FDCAN_FLAG);/* Function used get flag */
void FDCAN_ClearInterruptFlag(FDCAN_TypeDef* fdcan,  uint32_t FDCAN_FLAG_REG, uint32_t FDCAN_FLAG);/* Function used clear interrupt flag */
int  FDCAN_GetFifoStatus(FDCAN_TypeDef* fdcan, uint32_t FDCAN_BUF_TYPE);/* Function used get tbuf and rbuf status */
/**
  * @}
  */

/** @addtogroup FDCAN_Exported_Functions_Group5
 *  @{
 */
/* TTCAN management *************************************/
void FDCAN_RefMessageSet(FDCAN_TypeDef* fdcan, uint32_t FDCAN_REF_MSG_IDE, uint32_t FDCAN_REF_MSG_ID);/* Function used config reference message */
void FDCAN_TbufSoltPoint(FDCAN_TypeDef* fdcan, uint32_t FDCAN_TBPTR);/* Function used config TBPTR */
void FDCAN_TransmitSoltPoint(FDCAN_TypeDef* fdcan, uint32_t FDCAN_TTPTR);/* Function used config TTPTR */
void FDCAN_SetTbufSoltEmpty(FDCAN_TypeDef* fdcan, FunctionalState NewState);/* Function used config TBPTR choose's solt empty*/
void FDCAN_SetTbufSoltFull(FDCAN_TypeDef* fdcan, FunctionalState NewState);/* Function used config TBPTR choose's solt full*/
void FDCAN_TimeTrigEnable(FDCAN_TypeDef* fdcan, FunctionalState NewState);/* Function used enbale tten*/
void FDCAN_TimeStampPosition(FDCAN_TypeDef* fdcan, uint32_t FDCAN_TIMEPOS);/* Function used set timepos*/
void FDCAN_TimeStampEnable(FDCAN_TypeDef* fdcan, FunctionalState NewState);/* Function used enbale timepos*/
void FDCAN_GetCanTransmisionTs(FDCAN_TypeDef* fdcan, uint32_t can_transmission_ts[2]);/* Function used get transmision ts */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /*__FT32F4XX_FDCAN_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

