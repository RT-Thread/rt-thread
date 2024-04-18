/*********************************************************************************************************//**
 * @file    ht32f5xxxx_can.h
 * @version $Rev:: 7188         $
 * @date    $Date:: 2023-08-31 #$
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
 * @brief CAN message structure
 */
typedef struct
{
  u32  IdType;
  u32  FrameType;
  u32  Id;
  u32  DLC;
} STR_CANMSG_TypeDef;

/**
 * @brief CAN TX message structure
 */
typedef struct
{
  u32  IdType;
  u32  FrameType;
  u32  Id;
  u32  MCR;
  u32  DLC;
  u32  EOB;
  u32  RMTEN;
  u32  UMASK;
  u32  Data[8];
} STR_CANMSG_T_TypeDef;

/**
 * @brief CAN RX message structure
 */
typedef struct
{
  u32  IdType;
  u32  Id;
  u32  u8Xtd;
  u32  u8Dir;
  u32  MCR;
  u32  MASK0;
  u32  MASK1;
  u32  EOB;
  u32  UMASK;
  u32  RMTEN;
  u32  DIR;            /* For receive remote frame. */
 } STR_CANMSG_R_TypeDef;

/**
 * @brief CAN mask message structure
 */
typedef struct
{
  u32  u8Xtd;
  u32  u8Dir;
  u32  u32Id;
  u32  u8IdType;
} STR_CANMASK_TyprDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup CAN_Exported_Constants CAN exported constants
  * @{
  */
#define IS_CAN(x)                IS_CAN0(x)
#define IS_CAN0(x)               (x == HT_CAN0)

/**
 * @brief CAN Test Mode Constant Definitions
 */
#define    CAN_NORMAL_MODE   0
#define    CAN_BASIC_MODE    0x04
#define    CAN_SILENT_MODE   0x08
#define    CAN_LBACK_MODE    0x10
#define    CAN_LBS_MODE      0x18

/**
 * @brief DMessage ID Type Constant Definitions
 */
#define    CAN_STD_ID    0
#define    CAN_EXT_ID    1

/**
 * @brief Message Frame Type Constant Definitions
 */
#define    CAN_REMOTE_FRAME       0
#define    CAN_DATA_FRAME         1

#define    CAN_NBR                1
#define    CAN_VECTOR_NBR         1
#define    DATA_NBR               4

/**
 * @brief CAN CR Bit Field Definitions
 */
#define CAN_CR_TEST_Pos           7                                   /*!< CAN_T::CR: TEST Position */
#define CAN_CR_TEST_Msk           (1ul << CAN_CR_TEST_Pos)            /*!< CAN_T::CR: TEST Mask     */

#define CAN_CR_CCE_Pos            6                                   /*!< CAN_T::CR: CCE Position  */
#define CAN_CR_CCE_Msk            (1ul << CAN_CR_CCE_Pos)             /*!< CAN_T::CR: CCE Mask      */

#define CAN_CR_DAR_Pos            5                                   /*!< CAN_T::CR: DAR Position  */
#define CAN_CR_DAR_Msk            (1ul << CAN_CR_DAR_Pos)             /*!< CAN_T::CR: DAR Mask      */

#define CAN_CR_EIE_Pos            3                                   /*!< CAN_T::CR: EIE Position  */
#define CAN_CR_EIE_Msk            (1ul << CAN_CR_EIE_Pos)             /*!< CAN_T::CR: EIE Mask      */

#define CAN_CR_SIE_Pos            2                                   /*!< CAN_T::CR: SIE Position  */
#define CAN_CR_SIE_Msk            (1ul << CAN_CR_SIE_Pos)             /*!< CAN_T::CR SIE Mask      */

#define CAN_CR_IE_Pos             1                                   /*!< CAN_T::CR: IE Position   */
#define CAN_CR_IE_Msk             (1ul << CAN_CR_IE_Pos)              /*!< CAN_T::CR: IE Mask       */

#define CAN_CR_INIT_Pos           0                                   /*!< CAN_T::CR: INIT Position */
#define CAN_CR_INIT_Msk           (1ul << CAN_CR_INIT_Pos)            /*!< CAN_T::CR: INIT Mask     */

/**
 * @brief CAN STATUS Bit Field Definitions
 */
#define CAN_SR_BOFF_Pos        7                                      /*!< CAN_T::STATUS: BOFF Position  */
#define CAN_SR_BOFF_Msk        (1ul << CAN_SR_BOFF_Pos)               /*!< CAN_T::STATUS: BOFF Mask      */

#define CAN_SR_EWARN_Pos       6                                      /*!< CAN_T::STATUS: EWARN Position */
#define CAN_SR_EWARN_Msk       (1ul << CAN_SR_EWARN_Pos)              /*!< CAN_T::STATUS: EWARN Mask     */

#define CAN_SR_EPASS_Pos       5                                      /*!< CAN_T::STATUS: EPASS Position */
#define CAN_SR_EPASS_Msk       (1ul << CAN_SR_EPASS_Pos)              /*!< CAN_T::STATUS: EPASS Mask     */

#define CAN_SR_RXOK_Pos        4                                      /*!< CAN_T::STATUS: RXOK Position  */
#define CAN_SR_RXOK_Msk        (1ul << CAN_SR_RXOK_Pos)               /*!< CAN_T::STATUS: RXOK Mask      */

#define CAN_SR_TXOK_Pos        3                                      /*!< CAN_T::STATUS: TXOK Position  */
#define CAN_SR_TXOK_Msk        (1ul << CAN_SR_TXOK_Pos)               /*!< CAN_T::STATUS: TXOK Mask      */

#define CAN_SR_LEC_Pos         0                                      /*!< CAN_T::STATUS: LEC Position   */
#define CAN_SR_LEC_Msk         (0x3ul << CAN_SR_LEC_Pos)               /*!< CAN_T::STATUS: LEC Mask       */

/**
 * @brief CAN ECR Bit Field Definitions
 */
#define CAN_ECR_RP_Pos             15                                 /*!< CAN_T::ECR: RP Position       */
#define CAN_ECR_RP_Msk             (1ul << CAN_ECR_RP_Pos)            /*!< CAN_T::ECR: RP Mask           */

#define CAN_ECR_REC_Pos            8                                  /*!< CAN_T::ECR: REC Position      */
#define CAN_ECR_REC_Msk            (0x7Ful << CAN_ECR_REC_Pos)        /*!< CAN_T::ECR: REC Mask          */

#define CAN_ECR_TEC_Pos            0                                  /*!< CAN_T::ECR: TEC Position      */
#define CAN_ECR_TEC_Msk            (0xFFul << CAN_ECR_TEC_Pos)        /*!< CAN_T::ECR: TEC Mask          */

/**
 * @brief CAN BTR Bit Field Definitions
 */
#define CAN_BTR_TSEG1_Pos        12                                   /*!< CAN_T::BTR: TSEG1 Position  */
#define CAN_BTR_TSEG1_Msk        (0x7ul << CAN_BTR_TSEG1_Pos)         /*!< CAN_T::BTR: TSEG1 Mask      */

#define CAN_BTR_TSEG0_Pos        8                                    /*!< CAN_T::BTR: TSEG0 Position  */
#define CAN_BTR_TSEG0_Msk        (0xFul << CAN_BTR_TSEG0_Pos)         /*!< CAN_T::BTR: TSEG0 Mask      */

#define CAN_BTR_SJW_Pos          6                                    /*!< CAN_T::BTR: SJW Position    */
#define CAN_BTR_SJW_Msk          (0x3ul << CAN_BTR_SJW_Pos)           /*!< CAN_T::BTR: SJW Mask        */

#define CAN_BTR_BRP_Pos          0                                    /*!< CAN_T::BTR: BRP Position    */
#define CAN_BTR_BRP_Msk          (0x3Ful << CAN_BTR_BRP_Pos)          /*!< CAN_T::BTR: BRP Mask        */

/**
 * @brief CAN IR Bit Field Definitions
 */
#define CAN_IR_INTID_Pos         0                                    /*!< CAN_T::IR: INTID Position   */
#define CAN_IR_INTID_Msk         (0xFFFFul << CAN_IR_INTID_Pos)       /*!< CAN_T::R: INTID Mask       */

/**
 * @brief CAN TEST Bit Field Definitions
 */
#define CAN_TEST_RX_Pos            7                                  /*!< CAN_T::TEST: RX Position      */
#define CAN_TEST_RX_Msk            (1ul << CAN_TEST_RX_Pos)           /*!< CAN_T::TEST: RX Mask          */

#define CAN_TEST_TX_Pos            5                                  /*!< CAN_T::TEST: TX Position      */
#define CAN_TEST_TX_Msk            (0x3ul << CAN_TEST_TX_Pos)         /*!< CAN_T::TEST: TX Mask          */

#define CAN_TEST_LBACK_Pos         4                                  /*!< CAN_T::TEST: LBACK Position   */
#define CAN_TEST_LBACK_Msk         (1ul << CAN_TEST_LBACK_Pos)        /*!< CAN_T::TEST: LBACK Mask       */

#define CAN_TEST_SILENT_Pos        3                                  /*!< CAN_T::TEST: Silent Position  */
#define CAN_TEST_SILENT_Msk        (1ul << CAN_TEST_SILENT_Pos)       /*!< CAN_T::TEST: Silent Mask      */

#define CAN_TEST_BASIC_Pos         2                                  /*!< CAN_T::TEST: Basic Position   */
#define CAN_TEST_BASIC_Msk         (1ul << CAN_TEST_BASIC_Pos)        /*!< CAN_T::TEST: Basic Mask       */

/**
 * @brief CAN BPRE Bit Field Definitions
 */
#define CAN_BRPE_BRPE_Pos          0                                  /*!< CAN_T::BRPE: BRPE Position    */
#define CAN_BRPE_BRPE_Msk          (0xFul << CAN_BRPE_BRPE_Pos)       /*!< CAN_T::BRPE: BRPE Mask        */

/**
 * @brief CAN IFn_CREQ Bit Field Definitions
 */
#define CAN_IF_CREQ_BUSY_Pos       15                                   /*!< CAN_T::IFnCREQ: BUSY Position */
#define CAN_IF_CREQ_BUSY_Msk       (1ul << CAN_IF_CREQ_BUSY_Pos)        /*!< CAN_T::IFnCREQ: BUSY Mask     */

#define CAN_IF_CREQ_MSGNUM_Pos     0                                    /*!< CAN_T::IFnCREQ: MSGNUM Position */
#define CAN_IF_CREQ_MSGNUM_Msk     (0x3Ful << CAN_IF_CREQ_MSGNUM_Pos)   /*!< CAN_T::IFnCREQ: MSGNUM Mask     */

/**
 * @brief CAN IFn_CMASK Bit Field Definitions
 */
#define CAN_IF_CMASK_WRRD_Pos      7                                    /*!< CAN_T::IFnCMASK: WRRD Position */
#define CAN_IF_CMASK_WRRD_Msk      (1ul << CAN_IF_CMASK_WRRD_Pos)       /*!< CAN_T::IFnCMASK: WRRD Mask     */

#define CAN_IF_CMASK_MASK_Pos      6                                    /*!< CAN_T::IFnCMASK: MASK Position */
#define CAN_IF_CMASK_MASK_Msk      (1ul << CAN_IF_CMASK_MASK_Pos)       /*!< CAN_T::IFnCMASK: MASK Mask     */

#define CAN_IF_CMASK_ARB_Pos       5                                    /*!< CAN_T::IFnCMASK: ARB Position  */
#define CAN_IF_CMASK_ARB_Msk       (1ul << CAN_IF_CMASK_ARB_Pos)        /*!< CAN_T::IFnCMASK: ARB Mask      */

#define CAN_IF_CMASK_CONTROL_Pos   4                                    /*!< CAN_T::IFnCMASK: CONTROL Position */
#define CAN_IF_CMASK_CONTROL_Msk   (1ul << CAN_IF_CMASK_CONTROL_Pos)    /*!< CAN_T::IFnCMASK: CONTROL Mask */

#define CAN_IF_CMASK_CLRINTPND_Pos 3                                    /*!< CAN_T::IFnCMASK: CLRINTPND Position */
#define CAN_IF_CMASK_CLRINTPND_Msk (1ul << CAN_IF_CMASK_CLRINTPND_Pos)  /*!< CAN_T::IFnCMASK: CLRINTPND Mask */

#define CAN_IF_CMASK_TXRQSTNEWDAT_Pos 2                                         /*!< CAN_T::IFnCMASK: TXRQSTNEWDAT Position */
#define CAN_IF_CMASK_TXRQSTNEWDAT_Msk (1ul << CAN_IF_CMASK_TXRQSTNEWDAT_Pos)    /*!< CAN_T::IFnCMASK: TXRQSTNEWDAT Mask     */

#define CAN_IF_CMASK_DATAA_Pos     1                                    /*!< CAN_T::IFnCMASK: DATAA Position */
#define CAN_IF_CMASK_DATAA_Msk     (1ul << CAN_IF_CMASK_DATAA_Pos)      /*!< CAN_T::IFnCMASK: DATAA Mask     */

#define CAN_IF_CMASK_DATAB_Pos     0                                    /*!< CAN_T::IFnCMASK: DATAB Position */
#define CAN_IF_CMASK_DATAB_Msk     (1ul << CAN_IF_CMASK_DATAB_Pos)      /*!< CAN_T::IFnCMASK: DATAB Mask     */

/**
 * @brief CAN IFn_MASK0 Bit Field Definitions
 */
#define CAN_IF_MASK0_MSK_Pos       0                                    /*!< CAN_T::IFnMASK0: MSK Position   */
#define CAN_IF_MASK0_MSK_Msk       (0xFFul << CAN_IF_MASK0_MSK_Pos)     /*!< CAN_T::IFnMASK0: MSK Mask       */

/**
 * @brief CAN IFn_MASK1 Bit Field Definitions
 */
#define CAN_IF_MASK1_MXTD_Pos      15                                   /*!< CAN_T::IFnMASK1: MXTD Position */
#define CAN_IF_MASK1_MXTD_Msk      (1ul << CAN_IF_MASK1_MXTD_Pos)       /*!< CAN_T::IFnMASK1: MXTD Mask     */

#define CAN_IF_MASK1_MDIR_Pos      14                                   /*!< CAN_T::IFnMASK1: MDIR Position */
#define CAN_IF_MASK1_MDIR_Msk      (1ul << CAN_IF_MASK1_MDIR_Pos)       /*!< CAN_T::IFnMASK1: MDIR Mask     */

#define CAN_IF_MASK1_MSK_Pos       0                                    /*!< CAN_T::IFnMASK1: MSK Position */
#define CAN_IF_MASK1_MSK_Msk       (0x1FFul << CAN_IF_MASK1_MSK_Pos)    /*!< CAN_T::IFnMASK1: MSK Mask     */

/**
 * @brief CAN IFn_ARB0 Bit Field Definitions
 */
#define CAN_IF_ARB0_ID_Pos         0                                    /*!< CAN_T::IFnARB0: ID Position   */
#define CAN_IF_ARB0_ID_Msk         (0xFFFFul << CAN_IF_ARB0_ID_Pos)     /*!< CAN_T::IFnARB0: ID Mask       */

/**
 * @brief CAN IFn_ARB1 Bit Field Definitions
 */
#define CAN_IF_ARB1_MSGVAL_Pos     15                                   /*!< CAN_T::IFnARB1: MSGVAL Position */
#define CAN_IF_ARB1_MSGVAL_Msk     (1ul << CAN_IF_ARB1_MSGVAL_Pos)      /*!< CAN_T::IFnARB1: MSGVAL Mask     */

#define CAN_IF_ARB1_XTD_Pos        14                                   /*!< CAN_T::IFnARB1: XTD Position    */
#define CAN_IF_ARB1_XTD_Msk        (1ul << CAN_IF_ARB1_XTD_Pos)         /*!< CAN_T::IFnARB1: XTD Mask        */

#define CAN_IF_ARB1_DIR_Pos        13                                   /*!< CAN_T::IFnARB1: DIR Position    */
#define CAN_IF_ARB1_DIR_Msk        (1ul << CAN_IF_ARB1_DIR_Pos)         /*!< CAN_T::IFnARB1: DIR Mask        */

#define CAN_IF_ARB1_ID_Pos         0                                    /*!< CAN_T::IFnARB1: ID Position     */
#define CAN_IF_ARB1_ID_Msk         (0x1FFFul << CAN_IF_ARB1_ID_Pos)     /*!< CAN_T::IFnARB1: ID Mask         */

/**
 * @brief CAN IFn_MCR Bit Field Definitions
 */
#define CAN_IF_MCR_NEWDAT_Pos     15                                   /*!< CAN_T::IFnMCON: NEWDAT Position */
#define CAN_IF_MCR_NEWDAT_Msk     (1ul << CAN_IF_MCR_NEWDAT_Pos)       /*!< CAN_T::IFnMCON: NEWDAT Mask     */

#define CAN_IF_MCR_MSGLST_Pos     14                                   /*!< CAN_T::IFnMCON: MSGLST Position */
#define CAN_IF_MCR_MSGLST_Msk     (1ul << CAN_IF_MCR_MSGLST_Pos)       /*!< CAN_T::IFnMCON: MSGLST Mask     */

#define CAN_IF_MCR_INTPND_Pos     13                                   /*!< CAN_T::IFnMCON: INTPND Position */
#define CAN_IF_MCR_INTPND_Msk     (1ul << CAN_IF_MCR_INTPND_Pos)       /*!< CAN_T::IFnMCON: INTPND Mask     */

#define CAN_IF_MCR_UMASK_Pos      12                                   /*!< CAN_T::IFnMCON: UMASK Position  */
#define CAN_IF_MCR_UMASK_Msk      (1ul << CAN_IF_MCR_UMASK_Pos)        /*!< CAN_T::IFnMCON: UMASK Mask      */

#define CAN_IF_MCR_TXIE_Pos       11                                   /*!< CAN_T::IFnMCON: TXIE Position   */
#define CAN_IF_MCR_TXIE_Msk       (1ul << CAN_IF_MCR_TXIE_Pos)         /*!< CAN_T::IFnMCON: TXIE Mask       */

#define CAN_IF_MCR_RXIE_Pos       10                                   /*!< CAN_T::IFnMCON: RXIE Position   */
#define CAN_IF_MCR_RXIE_Msk       (1ul << CAN_IF_MCR_RXIE_Pos)         /*!< CAN_T::IFnMCON: RXIE Mask       */

#define CAN_IF_MCR_RMTEN_Pos      9                                    /*!< CAN_T::IFnMCON: RMTEN Position  */
#define CAN_IF_MCR_RMTEN_Msk      (1ul << CAN_IF_MCR_RMTEN_Pos)        /*!< CAN_T::IFnMCON: RMTEN Mask      */

#define CAN_IF_MCR_TXRQST_Pos     8                                    /*!< CAN_T::IFnMCON: TXRQST Position */
#define CAN_IF_MCR_TXRQST_Msk     (1ul << CAN_IF_MCR_TXRQST_Pos)       /*!< CAN_T::IFnMCON: TXRQST Mask     */

#define CAN_IF_MCR_EOB_Pos        7                                    /*!< CAN_T::IFnMCON: EOB Position    */
#define CAN_IF_MCR_EOB_Msk        (1ul << CAN_IF_MCR_EOB_Pos)          /*!< CAN_T::IFnMCON: EOB Mask        */

#define CAN_IF_MCR_DLC_Pos        0                                    /*!< CAN_T::IFnMCON: DLC Position    */
#define CAN_IF_MCR_DLC_Msk        (0xFul << CAN_IF_MCR_DLC_Pos)        /*!< CAN_T::IFnMCON: DLC Mask        */

/**
 * @brief CAN IFn_DATA_A0 Bit Field Definitions
 */
#define CAN_IF_DAT_A0_DATA1_Pos    8                                    /*!< CAN_T::IFnDATAA0: DATA1 Position */
#define CAN_IF_DAT_A0_DATA1_Msk    (0xFFul << CAN_IF_DAT_A0_DATA1_Pos)  /*!< CAN_T::IFnDATAA0: DATA1 Mask     */

#define CAN_IF_DAT_A0_DATA0_Pos    0                                    /*!< CAN_T::IFnDATAA0: DATA0 Position */
#define CAN_IF_DAT_A0_DATA0_Msk    (0xFFul << CAN_IF_DAT_A0_DATA0_Pos)  /*!< CAN_T::IFnDATAA0: DATA0 Mask     */

/**
 * @brief CAN IFn_DATA_A1 Bit Field Definitions
 */
#define CAN_IF_DAT_A1_DATA3_Pos    8                                    /*!< CAN_T::IFnDATAA1: DATA3 Position */
#define CAN_IF_DAT_A1_DATA3_Msk    (0xFFul << CAN_IF_DAT_A1_DATA3_Pos)  /*!< CAN_T::IFnDATAA1: DATA3 Mask     */

#define CAN_IF_DAT_A1_DATA2_Pos    0                                    /*!< CAN_T::IFnDATAA1: DATA2 Position */
#define CAN_IF_DAT_A1_DATA2_Msk    (0xFFul << CAN_IF_DAT_A1_DATA2_Pos)  /*!< CAN_T::IFnDATAA1: DATA2 Mask     */

/**
 * @brief CAN IFn_DATA_B0 Bit Field Definitions
 */
#define CAN_IF_DAT_B0_DATA5_Pos    8                                    /*!< CAN_T::IFnDATAB0: DATA5 Position */
#define CAN_IF_DAT_B0_DATA5_Msk    (0xFFul << CAN_IF_DAT_B0_DATA5_Pos)  /*!< CAN_T::IFnDATAB0: DATA5 Mask */

#define CAN_IF_DAT_B0_DATA4_Pos    0                                    /*!< CAN_T::IFnDATAB0: DATA4 Position */
#define CAN_IF_DAT_B0_DATA4_Msk    (0xFFul << CAN_IF_DAT_B0_DATA4_Pos)  /*!< CAN_T::IFnDATAB0: DATA4 Mask */

/**
 * @brief CAN IFn_DATA_B1 Bit Field Definitions
 */
#define CAN_IF_DAT_B1_DATA7_Pos    8                                    /*!< CAN_T::IFnDATAB1: DATA7 Position */
#define CAN_IF_DAT_B1_DATA7_Msk    (0xFFul << CAN_IF_DAT_B1_DATA7_Pos)  /*!< CAN_T::IFnDATAB1: DATA7 Mask     */

#define CAN_IF_DAT_B1_DATA6_Pos    0                                    /*!< CAN_T::IFnDATAB1: DATA6 Position */
#define CAN_IF_DAT_B1_DATA6_Msk    (0xFFul << CAN_IF_DAT_B1_DATA6_Pos)  /*!< CAN_T::IFnDATAB1: DATA6 Mask     */

/**
 * @brief CAN IFn_TXRQST0 Bit Field Definitions
 */
#define CAN_IF_TXRQST0_TXRQST_Pos  0                                        /*!< CAN_T::IFnTXRQST0: TXRQST Position */
#define CAN_IF_TXRQST0_TXRQST_Msk  (0xFFFFul << CAN_IF_TXRQST0_TXRQST_Pos)  /*!< CAN_T::IFnTXRQST0: TXRQST Mask     */

/**
 * @brief CAN IFn_TXRQST1 Bit Field Definitions
 */
#define CAN_IF_TXRQST1_TXRQST_Pos  0                                        /*!< CAN_T::IFnTXRQST1: TXRQST Position  */
#define CAN_IF_TXRQST1_TXRQST_Msk  (0xFFFFul << CAN_IF_TXRQST1_TXRQST_Pos)  /*!< CAN_T::IFnTXRQST1: TXRQST Mask      */

/**
 * @brief CAN IFn_NDAT0 Bit Field Definitions
 */
#define CAN_IF_NDAT0_NEWDATA_Pos   0                                        /*!< CAN_T::IFnNDAT0: NEWDATA Position */
#define CAN_IF_NDAT0_NEWDATA_Msk   (0xFFFFul << CAN_IF_NDAT0_NEWDATA_Pos)   /*!< CAN_T::IFnNDAT0: NEWDATA Mask     */

/**
 * @brief CAN IFn_NDAT1 Bit Field Definitions
 */
#define CAN_IF_NDAT1_NEWDATA_Pos   0                                        /*!< CAN_T::IFnNDAT1: NEWDATA Position */
#define CAN_IF_NDAT1_NEWDATA_Msk   (0xFFFFul << CAN_IF_NDAT1_NEWDATA_Pos)   /*!< CAN_T::IFnNDAT1: NEWDATA Mask     */

/**
 * @brief CAN IFn_IPND0 Bit Field Definitions
 */
#define CAN_IF_IPND0_INTPND_Pos   0                                         /*!< CAN_T::IFnIPND0: INTPND Position */
#define CAN_IF_IPND0_INTPND_Msk   (0xFFFFul << CAN_IF_IPND0_INTPND_Pos)     /*!< CAN_T::IFnIPND0: INTPND Mask     */

/**
 * @brief CAN IFn_IPND1 Bit Field Definitions
 */
#define CAN_IF_IPND1_INTPND_Pos   0                                         /*!< CAN_T::IFnIPND1: INTPND Position */
#define CAN_IF_IPND1_INTPND_Msk   (0xFFFFul << CAN_IF_IPND1_INTPND_Pos)     /*!< CAN_T::IFnIPND1: INTPND Mask     */

/**
 * @brief CAN IFn_MVLD0 Bit Field Definitions
 */
#define CAN_IF_MVLD0_MSGVAL_Pos   0                                         /*!< CAN_T::IFnMVLD0: MSGVAL Position */
#define CAN_IF_MVLD0_MSGVAL_Msk   (0xFFFFul << CAN_IF_MVLD0_MSGVAL_Pos)     /*!< CAN_T::IFnMVLD0: MSGVAL Mask     */

/**
 * @brief CAN IFn_MVLD1 Bit Field Definitions
 */
#define CAN_IF_MVLD1_MSGVAL_Pos   0                                         /*!< CAN_T::IFnMVLD1: MSGVAL Position */
#define CAN_IF_MVLD1_MSGVAL_Msk   (0xFFFFul << CAN_IF_MVLD1_MSGVAL_Pos)     /*!< CAN_T::IFnMVLD1: MSGVAL Mask     */

/**
 * @brief CAN WUEN Bit Field Definitions
 */
#define CAN_WUEN_WAKUP_EN_Pos     0                                         /*!< CAN_T::WUEN: WAKUP_EN Position */
#define CAN_WUEN_WAKUP_EN_Msk    (1ul << CAN_WUEN_WAKUP_EN_Pos)             /*!< CAN_T::WUEN: WAKUP_EN Mask     */

/**
 * @brief CAN WUSTATUS Bit Field Definitions
 */
#define CAN_WUSTATUS_WAKUP_STS_Pos     0                                    /*!< CAN_T::WUSTATUS: WAKUP_STS Position */
#define CAN_WUSTATUS_WAKUP_STS_Msk    (1ul << CAN_WUSTATUS_WAKUP_STS_Pos)   /*!< CAN_T::WUSTATUS: WAKUP_STS Mask     */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup CAN_Exported_Functions CAN exported functions
  * @{
  */
void CAN_DeInit(HT_CAN_TypeDef* CANx);
u32 CAN_SetBaudRate(HT_CAN_TypeDef *CANx, u32 u32BaudRate);
void CAN_Close(HT_CAN_TypeDef *CANx);
u32 CAN_Open(HT_CAN_TypeDef *CANx, u32 u32BaudRate, u32 u32Mode);
void CAN_CLR_INT_PENDING_BIT(HT_CAN_TypeDef *CANx, u32 u32MsgNum);
void CAN_EnableInt(HT_CAN_TypeDef *CANx, u32 u32Mask);
void CAN_DisableInt(HT_CAN_TypeDef *CANx, u32 u32Mask);
s32 CAN_Transmit(HT_CAN_TypeDef *CANx, u32 u32MsgNum , STR_CANMSG_T_TypeDef* pCanMsg);
s32 CAN_Receive(HT_CAN_TypeDef *CANx, u32 u32MsgNum , STR_CANMSG_T_TypeDef* pCanMsg);
s32 CAN_SetRxMsg(HT_CAN_TypeDef *CANx, u32 u32MsgNum , STR_CANMSG_R_TypeDef* pCanMsg);
s32 CAN_SetTxMsg(HT_CAN_TypeDef *CANx, u32 u32MsgNum , STR_CANMSG_T_TypeDef* pCanMsg);
s32 CAN_TriggerTxMsg(HT_CAN_TypeDef  *CANx, u32 u32MsgNum);
void CAN_EnterInitMode(HT_CAN_TypeDef *CANx);
void CAN_LeaveInitMode(HT_CAN_TypeDef *CANx);
void CAN_WaitMsg(HT_CAN_TypeDef *CANx);
u32 CAN_GetCANBitRate(HT_CAN_TypeDef  *CANx);
void CAN_EnterTestMode(HT_CAN_TypeDef *CANx, u32 u8TestMask);
void CAN_LeaveTestMode(HT_CAN_TypeDef *CANx);
u32 CAN_IsNewDataReceived(HT_CAN_TypeDef *CANx, u32 u8MsgObj);
s32 CAN_BasicSendMsg(HT_CAN_TypeDef *CANx, STR_CANMSG_T_TypeDef* pCanMsg);
s32 CAN_BasicReceiveMsg(HT_CAN_TypeDef *CANx, STR_CANMSG_T_TypeDef* pCanMsg);
s32 CAN_SetRxMsgObj(HT_CAN_TypeDef  *CANx, u32 MsgObj, STR_CANMSG_R_TypeDef* pCanMsg);
s32 CAN_ReadMsgObj(HT_CAN_TypeDef *CANx, u32 u8MsgObj, u32 u8Release, STR_CANMSG_T_TypeDef* pCanMsg);
s32 CAN_MsgObjMaskConfig(HT_CAN_TypeDef *tCAN, u32 u8MsgObj, STR_CANMSG_R_TypeDef* MaskMsg);
s32 CAN_SetMultiRxMsg(HT_CAN_TypeDef *CANx, u32 u32MsgNum , u32 u32MsgCount, STR_CANMSG_R_TypeDef* pCanMsg);
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
