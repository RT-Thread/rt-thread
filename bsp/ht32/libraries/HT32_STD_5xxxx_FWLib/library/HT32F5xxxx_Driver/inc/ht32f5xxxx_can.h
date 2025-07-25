/*********************************************************************************************************//**
 * @file    ht32f5xxxx_can.h
 * @version $Rev:: 8284         $
 * @date    $Date:: 2024-11-22 #$
 * @brief   The header file of the CAN library.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F5XXXX_CAN_H
#define __HT32F5XXXX_CAN_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup CAN
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup CAN_Exported_Types CAN exported types
  * @{
  */

/**
  * @brief  CAN init structure definition
  */
typedef struct
{
  u16 CAN_BRPrescaler;    /* Synchronisation Jump Width , Range: 1~1024.                                    */
  u8 CAN_Mode;            /* CAN_MODE_NORMAL             : Normal mode.                                     */
                          /* CAN_MODE_BASIC              : Basic mode.                                      */
                          /* CAN_MODE_SILENT             : Silent mode.                                     */
                          /* CAN_MODE_LBACK              : Loop Back Mode.                                  */
                          /* CAN_MODE_MONITORER          : Sample Point can be monitored.                   */
                          /* CAN_MODE_TX_DOMINANT        : CAN_TX pin drives a dominant.                    */
                          /* CAN_MODE_TX_RECESSIVE       : CAN_TX pin drives a recessive.                   */
  u8 CAN_SJW;             /* Synchronisation Jump Width , Range: 1~4.                                       */
  u8 CAN_TSEG0;           /* The time segment before the sample point.                                      */
  u8 CAN_TSEG1;           /* The time segment after the sample point.                                       */
  ControlStatus CAN_NART; /* Set the no automatic retransmission                                            */
} CAN_InitTypeDef;

/**
 * @brief CAN receive status structure
 */
typedef enum
{
  MSG_RX_FINISH,
  MSG_OBJ_NOT_SET,
  MSG_NOT_RECEIVED,
  MSG_OVER_RUN
} CAN_RxStatus_TypeDef;

/**
 * @brief CAN mask message structure
 */
typedef enum
{
  NO_ERROR      = 0,
  STUFF_ERROR   = 1,
  FORM_ERROR    = 2,
  ACK_ERROR     = 3,
  BIT1_EROR     = 4,
  BIT0_ERROR    = 5,
  CRC_ERROR     = 6,
  NO_CHANGE     = 7
} CAN_LastErrorCode_TypeDef;

/**
 * @brief Message ID Type Constant structure
 */
typedef enum
{
  CAN_STD_ID =  0,
  CAN_EXT_ID =  1
} CAN_IdType_Enum;

/**
 * @brief Message Frame Type Constant structure
 */
typedef enum
{
  CAN_REMOTE_FRAME =     0,
  CAN_DATA_FRAME   =     1
} CAN_FrameType_Enum;

/**
 * @brief CAN message structure
 */
typedef struct
{
  u32 Id;                          /* Arbitration ID. Rang 0x0 ~ 0x1FFFFFFF                                 */
  u32 IdMask;                      /* Arbitration ID mask. Rang 0x0 ~ 0x1FFFFFFF                            */
  u8 MsgNum;                       /* Message number                                                        */
  CAN_IdType_Enum IdType;          /* CAN_STD_ID (0x0 ~ 0x7FF) or CAN_EXT_ID (0x0 ~ 0x1FFFFFFF)             */
  CAN_FrameType_Enum FrameType;    /* CAN_REMOTE_FRAME or CAN_DATA_FRAME                                    */
} CAN_MSG_TypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup CAN_Exported_Constants CAN exported constants
  * @{
  */
#define IS_CAN(x)                IS_CAN0(x)
#define IS_CAN0(x)               (x == HT_CAN0)

#define CAN_STD_FRAME_Msk           0x7FF
#define CAN_EXT_FRAME_MSB_Msk       0x1FFF
#define CAN_EXT_FRAME_LSB_Msk       0xFFFF


#define CAN_MODE_NORMAL             0
#define MSG_OBJ_TOTAL_NUM           32

/**
 * @brief CAN CR Bit Field Definitions
 */
#define CAN_CR_TEST_Pos           7                                   /*!< CAN_T::CR: TEST Position         */
#define CAN_CR_TEST               (1ul << CAN_CR_TEST_Pos)            /*!< CAN_T::CR: TEST                  */

#define CAN_CR_CCE_Pos            6                                   /*!< CAN_T::CR: CCE Position          */
#define CAN_CR_CCE                (1ul << CAN_CR_CCE_Pos)             /*!< CAN_T::CR: CCE                   */

#define CAN_CR_DAR_Pos            5                                   /*!< CAN_T::CR: DAR Position          */
#define CAN_CR_DAR                (1ul << CAN_CR_DAR_Pos)             /*!< CAN_T::CR: DAR                   */

#define CAN_CR_EIE_Pos            3                                   /*!< CAN_T::CR: EIE Position          */
#define CAN_INT_EIE               (1ul << CAN_CR_EIE_Pos)             /*!< CAN_T::CR: EIE                   */

#define CAN_CR_SIE_Pos            2                                   /*!< CAN_T::CR: SIE Position          */
#define CAN_INT_SIE               (1ul << CAN_CR_SIE_Pos)             /*!< CAN_T::CR  SIE                   */

#define CAN_CR_IE_Pos             1                                   /*!< CAN_T::CR: IE Position           */
#define CAN_INT_IE                (1ul << CAN_CR_IE_Pos)              /*!< CAN_T::CR: IE                    */

#define CAN_INT_ALL               (CAN_INT_EIE | CAN_INT_SIE | CAN_INT_IE)

#define CAN_CR_INIT_Pos           0                                   /*!< CAN_T::CR: INIT Position         */
#define CAN_CR_INIT               (1ul << CAN_CR_INIT_Pos)            /*!< CAN_T::CR: INIT                  */

/**
 * @brief CAN STATUS Bit Field Definitions
 */
#define CAN_BOFF_Pos        7                                      /*!< CAN_T::STATUS: BOFF Position        */
#define CAN_FLAG_BOFF       (1ul << CAN_BOFF_Pos)                  /*!< CAN_T::STATUS: BOFF Flag            */

#define CAN_EWARN_Pos       6                                      /*!< CAN_T::STATUS: EWARN Position       */
#define CAN_FLAG_EWARN      (1ul << CAN_EWARN_Pos)                 /*!< CAN_T::STATUS: EWARN Flag           */

#define CAN_EPASS_Pos       5                                      /*!< CAN_T::STATUS: EPASS Position       */
#define CAN_FLAG_EPASS      (1ul << CAN_EPASS_Pos)                 /*!< CAN_T::STATUS: EPASS Flag           */

#define CAN_RXOK_Pos        4                                      /*!< CAN_T::STATUS: RXOK Position        */
#define CAN_FLAG_RXOK       (1ul << CAN_RXOK_Pos)                  /*!< CAN_T::STATUS: RXOK Flag            */

#define CAN_TXOK_Pos        3                                      /*!< CAN_T::STATUS: TXOK Position        */
#define CAN_FLAG_TXOK       (1ul << CAN_TXOK_Pos)                  /*!< CAN_T::STATUS: TXOK Flag            */

#define CAN_LEC_Pos         0                                      /*!< CAN_T::STATUS: LEC Position         */
#define CAN_LEC_Msk         (0x7ul << CAN_LEC_Pos)                 /*!< CAN_T::STATUS: LEC Mask             */

/**
 * @brief CAN ECR Bit Field Definitions
 */
#define CAN_ECR_RP_Pos             15                                 /*!< CAN_T::ECR: RP Position          */
#define CAN_ECR_RP_MsK             (1ul << CAN_ECR_RP_Pos)            /*!< CAN_T::ECR: RP                   */

#define CAN_ECR_REC_Pos            8                                  /*!< CAN_T::ECR: REC Position         */
#define CAN_ECR_REC_MsK            (0x7Ful << CAN_ECR_REC_Pos)        /*!< CAN_T::ECR: REC Mask             */

#define CAN_ECR_TEC_Pos            0                                  /*!< CAN_T::ECR: TEC Position         */
#define CAN_ECR_TEC_MsK            (0xFFul << CAN_ECR_TEC_Pos)        /*!< CAN_T::ECR: TEC Mask             */

/**
 * @brief CAN BTR Bit Field Definitions
 */
#define CAN_BTR_TSEG1_Pos        12                                   /*!< CAN_T::BTR: TSEG1 Position       */
#define CAN_BTR_TSEG1_Msk        (0x7ul << CAN_BTR_TSEG1_Pos)         /*!< CAN_T::BTR: TSEG1 Mask           */

#define CAN_BTR_TSEG0_Pos        8                                    /*!< CAN_T::BTR: TSEG0 Position       */
#define CAN_BTR_TSEG0_Msk        (0xFul << CAN_BTR_TSEG0_Pos)         /*!< CAN_T::BTR: TSEG0 Mask           */

#define CAN_BTR_SJW_Pos          6                                    /*!< CAN_T::BTR: SJW Position         */
#define CAN_BTR_SJW_Msk          (0x3ul << CAN_BTR_SJW_Pos)           /*!< CAN_T::BTR: SJW Mask             */

#define CAN_BTR_BRP_Pos          0                                    /*!< CAN_T::BTR: BRP Position         */
#define CAN_BTR_BRP_Msk          (0x3Ful << CAN_BTR_BRP_Pos)          /*!< CAN_T::BTR: BRP Mask             */

/**
 * @brief CAN IR Bit Field Definitions
 */
#define CAN_IR_INTID_Pos         0                                    /*!< CAN_T::IR: INTID Position        */
#define CAN_IR_INTID_Msk         (0xFFFFul << CAN_IR_INTID_Pos)       /*!< CAN_T::IR: INTID Mask            */

/**
 * @brief CAN TEST Bit Field Definitions
 */
#define CAN_TEST_RX_Pos              7                                 /*!< CAN_T::TEST: RX Position        */
#define CAN_TEST_RX                  (1ul << CAN_TEST_RX_Pos)          /*!< CAN_T::TEST: RX                 */

#define CAN_TEST_TX_Pos              5                                 /*!< CAN_T::TEST: TX Position        */
#define CAN_MODE_MONITORER          (0x1ul << CAN_TEST_TX_Pos)         /*!< CAN_T::TEST: SP monitored       */
#define CAN_MODE_TX_DOMINANT        (0x2ul << CAN_TEST_TX_Pos)         /*!< CAN_T::TEST: TX dominant        */
#define CAN_MODE_TX_RECESSIVE       (0x3ul << CAN_TEST_TX_Pos)         /*!< CAN_T::TEST: TX recessive       */

#define CAN_TEST_LBACK_Pos          4                                  /*!< CAN_T::TEST: LBACK Position     */
#define CAN_MODE_LBACK              (1ul << CAN_TEST_LBACK_Pos)        /*!< CAN_T::TEST: LBACK              */

#define CAN_TEST_SILENT_Pos         3                                  /*!< CAN_T::TEST: Silent Position    */
#define CAN_MODE_SILENT             (1ul << CAN_TEST_SILENT_Pos)       /*!< CAN_T::TEST: Silent             */

#define CAN_TEST_BASIC_Pos          2                                  /*!< CAN_T::TEST: Basic Position     */
#define CAN_MODE_BASIC              (1ul << CAN_TEST_BASIC_Pos)        /*!< CAN_T::TEST: Basic              */

/**
 * @brief CAN BPRE Bit Field Definitions
 */
#define CAN_BRPE_BRPE_Pos          0                                  /*!< CAN_T::BRPE: BRPE Position       */
#define CAN_BRPE_BRPE_Msk          (0xFul << CAN_BRPE_BRPE_Pos)       /*!< CAN_T::BRPE: BRPE Mask           */

/**
 * @brief CAN IFn_CREQ Bit Field Definitions
 */
#define CAN_IF_CREQ_BUSY_Pos       15                                  /*!< CAN_T::IFnCREQ: BUSY Position   */
#define CAN_FLAG_IF_BUSY           (1ul << CAN_IF_CREQ_BUSY_Pos)       /*!< CAN_T::IFnCREQ: BUSY FLAG       */

#define CAN_IF_CREQ_MSGNUM_Pos     0                                   /*!< CAN_T::IFnCREQ: MSGNUM Position */
#define CAN_IF_CREQ_MSGNUM_Msk     (0x3Ful << CAN_IF_CREQ_MSGNUM_Pos)  /*!< CAN_T::IFnCREQ: MSGNUM Mask     */

/**
 * @brief CAN IFn_CMASK Bit Field Definitions
 */
#define CAN_IF_CMASK_WRRD_Pos      7                                     /*!< CAN_T::IFnCMASK: WRRD Position          */
#define CAN_IF_CMASK_WRRD      (1ul << CAN_IF_CMASK_WRRD_Pos)            /*!< CAN_T::IFnCMASK: WRRD                   */

#define CAN_IF_CMASK_MASK_Pos      6                                     /*!< CAN_T::IFnCMASK: MASK Position          */
#define CAN_IF_CMASK_MASK      (1ul << CAN_IF_CMASK_MASK_Pos)            /*!< CAN_T::IFnCMASK: MASK                   */

#define CAN_IF_CMASK_ARB_Pos       5                                     /*!< CAN_T::IFnCMASK: ARB Position           */
#define CAN_IF_CMASK_ARB       (1ul << CAN_IF_CMASK_ARB_Pos)             /*!< CAN_T::IFnCMASK: ARB                    */

#define CAN_IF_CMASK_CONTROL_Pos   4                                     /*!< CAN_T::IFnCMASK: CONTROL Position       */
#define CAN_IF_CMASK_CONTROL   (1ul << CAN_IF_CMASK_CONTROL_Pos)         /*!< CAN_T::IFnCMASK: CONTROL                */

#define CAN_IF_CMASK_CLRINTPND_Pos 3                                     /*!< CAN_T::IFnCMASK: CLRINTPND Position     */
#define CAN_IF_CMASK_CLRINTPND (1ul << CAN_IF_CMASK_CLRINTPND_Pos)       /*!< CAN_T::IFnCMASK: CLRINTPND              */

#define CAN_IF_CMASK_TXRQSTNEWDAT_Pos 2                                  /*!< CAN_T::IFnCMASK: TXRQSTNEWDAT Position  */
#define CAN_IF_CMASK_TXRQSTNEWDAT (1ul << CAN_IF_CMASK_TXRQSTNEWDAT_Pos) /*!< CAN_T::IFnCMASK: TXRQSTNEWDAT           */

#define CAN_IF_CMASK_DATAA_Pos     1                                     /*!< CAN_T::IFnCMASK: DATAA Position         */
#define CAN_IF_CMASK_DATAA     (1ul << CAN_IF_CMASK_DATAA_Pos)           /*!< CAN_T::IFnCMASK: DATAA                  */

#define CAN_IF_CMASK_DATAB_Pos     0                                     /*!< CAN_T::IFnCMASK: DATAB Position         */
#define CAN_IF_CMASK_DATAB     (1ul << CAN_IF_CMASK_DATAB_Pos)           /*!< CAN_T::IFnCMASK: DATAB                  */

/**
 * @brief CAN IFn_MASK0 Bit Field Definitions
 */
#define CAN_IF_MASK0_MSK_Pos       0                                    /*!< CAN_T::IFnMASK0: MSK Position  */
#define CAN_IF_MASK0_MSK_Msk       (0xFFul << CAN_IF_MASK0_MSK_Pos)     /*!< CAN_T::IFnMASK0: MSK Mask      */

/**
 * @brief CAN IFn_MASK1 Bit Field Definitions
 */
#define CAN_IF_MASK1_MXTD_Pos      15                                   /*!< CAN_T::IFnMASK1: MXTD Position */
#define CAN_IF_MASK1_MXTD          (1ul << CAN_IF_MASK1_MXTD_Pos)       /*!< CAN_T::IFnMASK1: MXTD          */

#define CAN_IF_MASK1_MDIR_Pos      14                                   /*!< CAN_T::IFnMASK1: MDIR Position */
#define CAN_IF_MASK1_MDIR          (1ul << CAN_IF_MASK1_MDIR_Pos)       /*!< CAN_T::IFnMASK1: MDIR          */

#define CAN_IF_MASK1_MSK_Pos       0                                    /*!< CAN_T::IFnMASK1: MSK Position  */
#define CAN_IF_MASK1_MSK_Msk       (0x1FFul << CAN_IF_MASK1_MSK_Pos)    /*!< CAN_T::IFnMASK1: MSK Mask      */

/**
 * @brief CAN IFn_ARB0 Bit Field Definitions
 */
#define CAN_IF_ARB0_ID_Pos         0                                    /*!< CAN_T::IFnARB0: ID Position    */
#define CAN_IF_ARB0_ID_Msk         (0xFFFFul << CAN_IF_ARB0_ID_Pos)     /*!< CAN_T::IFnARB0: ID Mask        */

/**
 * @brief CAN IFn_ARB1 Bit Field Definitions
 */
#define CAN_IF_ARB1_MSGVAL_Pos     15                                  /*!< CAN_T::IFnARB1: MSGVAL Position */
#define CAN_IF_ARB1_MSGVAL         (1ul << CAN_IF_ARB1_MSGVAL_Pos)     /*!< CAN_T::IFnARB1: MSGVAL          */

#define CAN_IF_ARB1_XTD_Pos        14                                  /*!< CAN_T::IFnARB1: XTD Position    */
#define CAN_IF_ARB1_XTD            (1ul << CAN_IF_ARB1_XTD_Pos)        /*!< CAN_T::IFnARB1: XTD             */

#define CAN_IF_ARB1_DIR_Pos        13                                  /*!< CAN_T::IFnARB1: DIR Position    */
#define CAN_IF_ARB1_DIR            (1ul << CAN_IF_ARB1_DIR_Pos)        /*!< CAN_T::IFnARB1: DIR             */

#define CAN_IF_ARB1_ID_Pos         0                                   /*!< CAN_T::IFnARB1: ID Position     */
#define CAN_IF_ARB1_ID_Msk         (0x1FFFul << CAN_IF_ARB1_ID_Pos)    /*!< CAN_T::IFnARB1: ID Mask         */

/**
 * @brief CAN IFn_MCR Bit Field Definitions
 */
#define CAN_IF_MCR_NEWDAT_Pos     15                                   /*!< CAN_T::IFnMCON: NEWDAT Position */
#define CAN_IF_MCR_NEWDAT         (1ul << CAN_IF_MCR_NEWDAT_Pos)       /*!< CAN_T::IFnMCON: NEWDAT          */

#define CAN_IF_MCR_MSGLST_Pos     14                                   /*!< CAN_T::IFnMCON: MSGLST Position */
#define CAN_IF_MCR_MSGLST         (1ul << CAN_IF_MCR_MSGLST_Pos)       /*!< CAN_T::IFnMCON: MSGLST          */

#define CAN_IF_MCR_INTPND_Pos     13                                   /*!< CAN_T::IFnMCON: INTPND Position */
#define CAN_IF_MCR_INTPND         (1ul << CAN_IF_MCR_INTPND_Pos)       /*!< CAN_T::IFnMCON: INTPND          */

#define CAN_IF_MCR_UMASK_Pos      12                                   /*!< CAN_T::IFnMCON: UMASK Position  */
#define CAN_IF_MCR_UMASK          (1ul << CAN_IF_MCR_UMASK_Pos)        /*!< CAN_T::IFnMCON: UMASK           */

#define CAN_IF_MCR_TXIE_Pos       11                                   /*!< CAN_T::IFnMCON: TXIE Position   */
#define CAN_IF_MCR_TXIE           (1ul << CAN_IF_MCR_TXIE_Pos)         /*!< CAN_T::IFnMCON: TXIE            */

#define CAN_IF_MCR_RXIE_Pos       10                                   /*!< CAN_T::IFnMCON: RXIE Position   */
#define CAN_IF_MCR_RXIE           (1ul << CAN_IF_MCR_RXIE_Pos)         /*!< CAN_T::IFnMCON: RXIE            */

#define CAN_IF_MCR_RMTEN_Pos      9                                    /*!< CAN_T::IFnMCON: RMTEN Position  */
#define CAN_IF_MCR_RMTEN          (1ul << CAN_IF_MCR_RMTEN_Pos)        /*!< CAN_T::IFnMCON: RMTEN           */

#define CAN_IF_MCR_TXRQST_Pos     8                                    /*!< CAN_T::IFnMCON: TXRQST Position */
#define CAN_IF_MCR_TXRQST         (1ul << CAN_IF_MCR_TXRQST_Pos)       /*!< CAN_T::IFnMCON: TXRQST          */

#define CAN_IF_MCR_EOB_Pos        7                                    /*!< CAN_T::IFnMCON: EOB Position    */
#define CAN_IF_MCR_EOB            (1ul << CAN_IF_MCR_EOB_Pos)          /*!< CAN_T::IFnMCON: EOB             */

#define CAN_IF_MCR_DLC_Pos        0                                    /*!< CAN_T::IFnMCON: DLC Position    */
#define CAN_IF_MCR_DLC_Msk        (0xFul << CAN_IF_MCR_DLC_Pos)       /*!< CAN_T::IFnMCON: DLC Mask         */

/**
 * @brief CAN IFn_DATA_A0 Bit Field Definitions
 */
#define CAN_IF_DAT_A0_DATA1_Pos   8                                   /*!< CAN_T::IFnDATAA0: DATA1 Position */
#define CAN_IF_DAT_A0_DATA1_Msk   (0xFFul << CAN_IF_DAT_A0_DATA1_Pos) /*!< CAN_T::IFnDATAA0: DATA1 Mask     */

#define CAN_IF_DAT_A0_DATA0_Pos   0                                   /*!< CAN_T::IFnDATAA0: DATA0 Position */
#define CAN_IF_DAT_A0_DATA0_Msk   (0xFFul << CAN_IF_DAT_A0_DATA0_Pos) /*!< CAN_T::IFnDATAA0: DATA0 Mask     */

/**
 * @brief CAN IFn_DATA_A1 Bit Field Definitions
 */
#define CAN_IF_DAT_A1_DATA3_Pos   8                                   /*!< CAN_T::IFnDATAA1: DATA3 Position */
#define CAN_IF_DAT_A1_DATA3_Msk   (0xFFul << CAN_IF_DAT_A1_DATA3_Pos) /*!< CAN_T::IFnDATAA1: DATA3 Mask     */

#define CAN_IF_DAT_A1_DATA2_Pos   0                                   /*!< CAN_T::IFnDATAA1: DATA2 Position */
#define CAN_IF_DAT_A1_DATA2_Msk   (0xFFul << CAN_IF_DAT_A1_DATA2_Pos) /*!< CAN_T::IFnDATAA1: DATA2 Mask     */

/**
 * @brief CAN IFn_DATA_B0 Bit Field Definitions
 */
#define CAN_IF_DAT_B0_DATA5_Pos   8                                   /*!< CAN_T::IFnDATAB0: DATA5 Position */
#define CAN_IF_DAT_B0_DATA5_Msk   (0xFFul << CAN_IF_DAT_B0_DATA5_Pos) /*!< CAN_T::IFnDATAB0: DATA5 Mask     */

#define CAN_IF_DAT_B0_DATA4_Pos   0                                   /*!< CAN_T::IFnDATAB0: DATA4 Position */
#define CAN_IF_DAT_B0_DATA4_Msk   (0xFFul << CAN_IF_DAT_B0_DATA4_Pos) /*!< CAN_T::IFnDATAB0: DATA4 Mask     */

/**
 * @brief CAN IFn_DATA_B1 Bit Field Definitions
 */
#define CAN_IF_DAT_B1_DATA7_Pos   8                                   /*!< CAN_T::IFnDATAB1: DATA7 Position */
#define CAN_IF_DAT_B1_DATA7_Msk   (0xFFul << CAN_IF_DAT_B1_DATA7_Pos) /*!< CAN_T::IFnDATAB1: DATA7 Mask     */

#define CAN_IF_DAT_B1_DATA6_Pos   0                                   /*!< CAN_T::IFnDATAB1: DATA6 Position */
#define CAN_IF_DAT_B1_DATA6_Msk   (0xFFul << CAN_IF_DAT_B1_DATA6_Pos) /*!< CAN_T::IFnDATAB1: DATA6 Mask     */

/**
 * @brief CAN IFn_TXRQST0 Bit Field Definitions
 */
#define CAN_IF_TXRQST0_TXRQST_Pos  0                                        /*!< CAN_T::IFnTXRQST0: TXRQST Position   */
#define CAN_IF_TXRQST0_TXRQST_Msk  (0xFFFFul << CAN_IF_TXRQST0_TXRQST_Pos)  /*!< CAN_T::IFnTXRQST0: TXRQST Mask       */

/**
 * @brief CAN IFn_TXRQST1 Bit Field Definitions
 */
#define CAN_IF_TXRQST1_TXRQST_Pos  0                                        /*!< CAN_T::IFnTXRQST1: TXRQST Position   */
#define CAN_IF_TXRQST1_TXRQST_Msk  (0xFFFFul << CAN_IF_TXRQST1_TXRQST_Pos)  /*!< CAN_T::IFnTXRQST1: TXRQST Mask       */

/**
 * @brief CAN IFn_NDAT0 Bit Field Definitions
 */
#define CAN_IF_NDAT0_NEWDATA_Pos   0                                        /*!< CAN_T::IFnNDAT0: NEWDATA Position    */
#define CAN_IF_NDAT0_NEWDATA_Msk   (0xFFFFul << CAN_IF_NDAT0_NEWDATA_Pos)   /*!< CAN_T::IFnNDAT0: NEWDATA Mask        */

/**
 * @brief CAN IFn_NDAT1 Bit Field Definitions
 */
#define CAN_IF_NDAT1_NEWDATA_Pos   0                                        /*!< CAN_T::IFnNDAT1: NEWDATA Position    */
#define CAN_IF_NDAT1_NEWDATA_Msk   (0xFFFFul << CAN_IF_NDAT1_NEWDATA_Pos)   /*!< CAN_T::IFnNDAT1: NEWDATA Mask        */

/**
 * @brief CAN IFn_IPND0 Bit Field Definitions
 */
#define CAN_IF_IPND0_INTPND_Pos   0                                         /*!< CAN_T::IFnIPND0: INTPND Position     */
#define CAN_IF_IPND0_INTPND_Msk   (0xFFFFul << CAN_IF_IPND0_INTPND_Pos)     /*!< CAN_T::IFnIPND0: INTPND Mask         */

/**
 * @brief CAN IFn_IPND1 Bit Field Definitions
 */
#define CAN_IF_IPND1_INTPND_Pos   0                                         /*!< CAN_T::IFnIPND1: INTPND Position     */
#define CAN_IF_IPND1_INTPND_Msk   (0xFFFFul << CAN_IF_IPND1_INTPND_Pos)     /*!< CAN_T::IFnIPND1: INTPND Mask         */

/**
 * @brief CAN IFn_MVLD0 Bit Field Definitions
 */
#define CAN_IF_MVLD0_MSGVAL_Pos   0                                         /*!< CAN_T::IFnMVLD0: MSGVAL Position     */
#define CAN_IF_MVLD0_MSGVAL_Msk   (0xFFFFul << CAN_IF_MVLD0_MSGVAL_Pos)     /*!< CAN_T::IFnMVLD0: MSGVAL Mask         */

/**
 * @brief CAN IFn_MVLD1 Bit Field Definitions
 */
#define CAN_IF_MVLD1_MSGVAL_Pos   0                                         /*!< CAN_T::IFnMVLD1: MSGVAL Position     */
#define CAN_IF_MVLD1_MSGVAL_Msk   (0xFFFFul << CAN_IF_MVLD1_MSGVAL_Pos)     /*!< CAN_T::IFnMVLD1: MSGVAL Mask         */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup CAN_Exported_Functions CAN exported functions
  * @{
  */
/* Initialization functions *********************************************************************************/
void CAN_DeInit(HT_CAN_TypeDef* CANx);
void CAN_Init(HT_CAN_TypeDef* CANx, CAN_InitTypeDef* CAN_InitStruct);

/* Interrupts and flags management functions ****************************************************************/
void CAN_IntConfig(HT_CAN_TypeDef *CANx, u32 CAN_Int, ControlStatus NewState);
FlagStatus CAN_GetIntStatus(HT_CAN_TypeDef* CANx, u32 CAN_Int);
FlagStatus CAN_GetFlagStatus(HT_CAN_TypeDef* CANx, uint32_t CAN_Flag);
void CAN_ClearFlag(HT_CAN_TypeDef* CANx, uint32_t CAN_Flag);

/* Error management functions *******************************************************************************/
CAN_LastErrorCode_TypeDef CAN_GetLastErrorCode(HT_CAN_TypeDef* CANx);
u32 CAN_GetReceiveErrorCounter(HT_CAN_TypeDef* CANx);
u32 CAN_GetLSBTransmitErrorCounter(HT_CAN_TypeDef* CANx);
void CAN_BusOffRecovery(HT_CAN_TypeDef *CANx);

/* Test Mode functions **************************************************************************************/
void CAN_EnterTestMode(HT_CAN_TypeDef *CANx, u32 u8TestMask);
void CAN_LeaveTestMode(HT_CAN_TypeDef *CANx);
ErrStatus CAN_BasicSendMsg(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg, u8* data, u8 len);
ErrStatus CAN_BasicReceiveMsg(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg, u8* data, u8* len);

/* Transmit/Receive functions *******************************************************************************/
ErrStatus CAN_Transmit(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg, u8* data, u8 len);
CAN_RxStatus_TypeDef CAN_Receive(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg, u8* data, u32* len);
ErrStatus CAN_UpdateTxMsgData(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg, u8* data, u8 len);
ErrStatus CAN_TriggerTxMsg(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg);

/* Set Rx Message Object ************************************************************************************/
ErrStatus CAN_SetRxMsg(HT_CAN_TypeDef *CANx ,CAN_MSG_TypeDef* pCanMsg, u32 FifoDepth);

/* Message Object status function ***************************************************************************/
ErrStatus CAN_CancelTransmit(HT_CAN_TypeDef* CANx, CAN_MSG_TypeDef* pCanMsg);
ErrStatus CAN_DiscardRxMsg(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg);
bool      CAN_NewDataReceived(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg);
s32       CAN_TransmitStatus(HT_CAN_TypeDef* CANx, CAN_MSG_TypeDef* pCanMsg);
bool      CAN_GetMsgPending(HT_CAN_TypeDef* CANx, CAN_MSG_TypeDef* pCanMsg);
ErrStatus CAN_ClearMsgPendingFlag(HT_CAN_TypeDef *CANx, CAN_MSG_TypeDef* pCanMsg);
void      CAN_ClearAllMsgPendingFlag(HT_CAN_TypeDef *CANx);
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
