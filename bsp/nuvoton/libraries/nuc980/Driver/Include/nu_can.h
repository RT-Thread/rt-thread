/**************************************************************************//**
 * @file     can.h
 * @version  V2.00
 * @brief    NUC980 Series CAN Driver Header File
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __NU_CAN_H__
#define __NU_CAN_H__

#include "nuc980.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup CAN_Driver CAN Driver
  @{
*/

/** @addtogroup CAN_EXPORTED_CONSTANTS CAN Exported Constants
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/* CAN Test Mode Constant Definitions                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define    CAN_NORMAL_MODE   0ul    /*!< CAN select normal mode \hideinitializer */
#define    CAN_BASIC_MODE    1ul    /*!< CAN select basic mode \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* Message ID Type Constant Definitions                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
#define    CAN_STD_ID    0ul    /*!< CAN select standard ID \hideinitializer */
#define    CAN_EXT_ID    1ul    /*!< CAN select extended ID \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* Message Frame Type Constant Definitions                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
#define    CAN_REMOTE_FRAME    0ul    /*!< CAN frame select remote frame \hideinitializer */
#define    CAN_DATA_FRAME    1ul      /*!< CAN frame select data frame \hideinitializer */

/*@}*/ /* end of group CAN_EXPORTED_CONSTANTS */


typedef struct
{
    __IO uint32_t CREQ;         /*!< [0x0020] IFn Command Request Register                                     */
    __IO uint32_t CMASK;        /*!< [0x0024] IFn Command Mask Register                                        */
    __IO uint32_t MASK1;        /*!< [0x0028] IFn Mask 1 Register                                              */
    __IO uint32_t MASK2;        /*!< [0x002c] IFn Mask 2 Register                                              */
    __IO uint32_t ARB1;         /*!< [0x0030] IFn Arbitration 1 Register                                       */
    __IO uint32_t ARB2;         /*!< [0x0034] IFn Arbitration 2 Register                                       */
    __IO uint32_t MCON;         /*!< [0x0038] IFn Message Control Register                                     */
    __IO uint32_t DAT_A1;       /*!< [0x003c] IFn Data A1 Register                                             */
    __IO uint32_t DAT_A2;       /*!< [0x0040] IFn Data A2 Register                                             */
    __IO uint32_t DAT_B1;       /*!< [0x0044] IFn Data B1 Register                                             */
    __IO uint32_t DAT_B2;       /*!< [0x0048] IFn Data B2 Register                                             */
    __I uint32_t RESERVE0[13];
} CAN_IF_T;

typedef struct
{
    __IO uint32_t CON;                   /*!< [0x0000] Control Register                                                 */
    __IO uint32_t STATUS;                /*!< [0x0004] Status Register                                                  */
    __I  uint32_t ERR;                   /*!< [0x0008] Error Counter Register                                           */
    __IO uint32_t BTIME;                 /*!< [0x000c] Bit Timing Register                                              */
    __I  uint32_t IIDR;                  /*!< [0x0010] Interrupt Identifier Register                                    */
    __IO uint32_t TEST;                  /*!< [0x0014] Test Register                                                    */
    __IO uint32_t BRPE;                  /*!< [0x0018] Baud Rate Prescaler Extension Register                           */
    __I  uint32_t RESERVE0[1];
    __IO CAN_IF_T IF[2];
    __I  uint32_t RESERVE2[8];
    __I  uint32_t TXREQ1;                /*!< [0x0100] Transmission Request Register 1                                  */
    __I  uint32_t TXREQ2;                /*!< [0x0104] Transmission Request Register 2                                  */
    __I  uint32_t RESERVE3[6];
    __I  uint32_t NDAT1;                 /*!< [0x0120] New Data Register 1                                              */
    __I  uint32_t NDAT2;                 /*!< [0x0124] New Data Register 2                                              */
    __I  uint32_t RESERVE4[6];
    __I  uint32_t IPND1;                 /*!< [0x0140] Interrupt Pending Register 1                                     */
    __I  uint32_t IPND2;                 /*!< [0x0144] Interrupt Pending Register 2                                     */
    __I  uint32_t RESERVE5[6];
    __I  uint32_t MVLD1;                 /*!< [0x0160] Message Valid Register 1                                         */
    __I  uint32_t MVLD2;                 /*!< [0x0164] Message Valid Register 2                                         */
    __IO uint32_t WU_EN;                 /*!< [0x0168] Wake-up Enable Control Register                                  */
    __IO uint32_t WU_STATUS;             /*!< [0x016c] Wake-up Status Register                                          */

} CAN_T;




#define CAN_CON_INIT_Pos                 (0)                                               /*!< CAN_T::CON: Init Position              */
#define CAN_CON_INIT_Msk                 (0x1ul << CAN_CON_INIT_Pos)                       /*!< CAN_T::CON: Init Mask                  */

#define CAN_CON_IE_Pos                   (1)                                               /*!< CAN_T::CON: IE Position                */
#define CAN_CON_IE_Msk                   (0x1ul << CAN_CON_IE_Pos)                         /*!< CAN_T::CON: IE Mask                    */

#define CAN_CON_SIE_Pos                  (2)                                               /*!< CAN_T::CON: SIE Position               */
#define CAN_CON_SIE_Msk                  (0x1ul << CAN_CON_SIE_Pos)                        /*!< CAN_T::CON: SIE Mask                   */

#define CAN_CON_EIE_Pos                  (3)                                               /*!< CAN_T::CON: EIE Position               */
#define CAN_CON_EIE_Msk                  (0x1ul << CAN_CON_EIE_Pos)                        /*!< CAN_T::CON: EIE Mask                   */

#define CAN_CON_DAR_Pos                  (5)                                               /*!< CAN_T::CON: DAR Position               */
#define CAN_CON_DAR_Msk                  (0x1ul << CAN_CON_DAR_Pos)                        /*!< CAN_T::CON: DAR Mask                   */

#define CAN_CON_CCE_Pos                  (6)                                               /*!< CAN_T::CON: CCE Position               */
#define CAN_CON_CCE_Msk                  (0x1ul << CAN_CON_CCE_Pos)                        /*!< CAN_T::CON: CCE Mask                   */

#define CAN_CON_TEST_Pos                 (7)                                               /*!< CAN_T::CON: Test Position              */
#define CAN_CON_TEST_Msk                 (0x1ul << CAN_CON_TEST_Pos)                       /*!< CAN_T::CON: Test Mask                  */

#define CAN_STATUS_LEC_Pos               (0)                                               /*!< CAN_T::STATUS: LEC Position            */
#define CAN_STATUS_LEC_Msk               (0x7ul << CAN_STATUS_LEC_Pos)                     /*!< CAN_T::STATUS: LEC Mask                */

#define CAN_STATUS_TXOK_Pos              (3)                                               /*!< CAN_T::STATUS: TxOK Position           */
#define CAN_STATUS_TXOK_Msk              (0x1ul << CAN_STATUS_TXOK_Pos)                    /*!< CAN_T::STATUS: TxOK Mask               */

#define CAN_STATUS_RXOK_Pos              (4)                                               /*!< CAN_T::STATUS: RxOK Position           */
#define CAN_STATUS_RXOK_Msk              (0x1ul << CAN_STATUS_RXOK_Pos)                    /*!< CAN_T::STATUS: RxOK Mask               */

#define CAN_STATUS_EPASS_Pos             (5)                                               /*!< CAN_T::STATUS: EPass Position          */
#define CAN_STATUS_EPASS_Msk             (0x1ul << CAN_STATUS_EPASS_Pos)                   /*!< CAN_T::STATUS: EPass Mask              */

#define CAN_STATUS_EWARN_Pos             (6)                                               /*!< CAN_T::STATUS: EWarn Position          */
#define CAN_STATUS_EWARN_Msk             (0x1ul << CAN_STATUS_EWARN_Pos)                   /*!< CAN_T::STATUS: EWarn Mask              */

#define CAN_STATUS_BOFF_Pos              (7)                                               /*!< CAN_T::STATUS: BOff Position           */
#define CAN_STATUS_BOFF_Msk              (0x1ul << CAN_STATUS_BOFF_Pos)                    /*!< CAN_T::STATUS: BOff Mask               */

#define CAN_ERR_TEC_Pos                  (0)                                               /*!< CAN_T::ERR: TEC Position               */
#define CAN_ERR_TEC_Msk                  (0xfful << CAN_ERR_TEC_Pos)                       /*!< CAN_T::ERR: TEC Mask                   */

#define CAN_ERR_REC_Pos                  (8)                                               /*!< CAN_T::ERR: REC Position               */
#define CAN_ERR_REC_Msk                  (0x7ful << CAN_ERR_REC_Pos)                       /*!< CAN_T::ERR: REC Mask                   */

#define CAN_ERR_RP_Pos                   (15)                                              /*!< CAN_T::ERR: RP Position                */
#define CAN_ERR_RP_Msk                   (0x1ul << CAN_ERR_RP_Pos)                         /*!< CAN_T::ERR: RP Mask                    */

#define CAN_BTIME_BRP_Pos                (0)                                               /*!< CAN_T::BTIME: BRP Position             */
#define CAN_BTIME_BRP_Msk                (0x3ful << CAN_BTIME_BRP_Pos)                     /*!< CAN_T::BTIME: BRP Mask                 */

#define CAN_BTIME_SJW_Pos                (6)                                               /*!< CAN_T::BTIME: SJW Position             */
#define CAN_BTIME_SJW_Msk                (0x3ul << CAN_BTIME_SJW_Pos)                      /*!< CAN_T::BTIME: SJW Mask                 */

#define CAN_BTIME_TSEG1_Pos              (8)                                               /*!< CAN_T::BTIME: TSeg1 Position           */
#define CAN_BTIME_TSEG1_Msk              (0xful << CAN_BTIME_TSEG1_Pos)                    /*!< CAN_T::BTIME: TSeg1 Mask               */

#define CAN_BTIME_TSEG2_Pos              (12)                                              /*!< CAN_T::BTIME: TSeg2 Position           */
#define CAN_BTIME_TSEG2_Msk              (0x7ul << CAN_BTIME_TSEG2_Pos)                    /*!< CAN_T::BTIME: TSeg2 Mask               */

#define CAN_IIDR_IntId_Pos               (0)                                               /*!< CAN_T::IIDR: IntId Position            */
#define CAN_IIDR_IntId_Msk               (0xfffful << CAN_IIDR_IntId_Pos)                  /*!< CAN_T::IIDR: IntId Mask                */

#define CAN_TEST_BASIC_Pos               (2)                                               /*!< CAN_T::TEST: Basic Position            */
#define CAN_TEST_BASIC_Msk               (0x1ul << CAN_TEST_BASIC_Pos)                     /*!< CAN_T::TEST: Basic Mask                */

#define CAN_TEST_SILENT_Pos              (3)                                               /*!< CAN_T::TEST: Silent Position           */
#define CAN_TEST_SILENT_Msk              (0x1ul << CAN_TEST_SILENT_Pos)                    /*!< CAN_T::TEST: Silent Mask               */

#define CAN_TEST_LBACK_Pos               (4)                                               /*!< CAN_T::TEST: LBack Position            */
#define CAN_TEST_LBACK_Msk               (0x1ul << CAN_TEST_LBACK_Pos)                     /*!< CAN_T::TEST: LBack Mask                */

#define CAN_TEST_Tx_Pos                  (5)                                               /*!< CAN_T::TEST: Tx Position               */
#define CAN_TEST_Tx_Msk                  (0x3ul << CAN_TEST_Tx_Pos)                        /*!< CAN_T::TEST: Tx Mask                   */

#define CAN_TEST_Rx_Pos                  (7)                                               /*!< CAN_T::TEST: Rx Position               */
#define CAN_TEST_Rx_Msk                  (0x1ul << CAN_TEST_Rx_Pos)                        /*!< CAN_T::TEST: Rx Mask                   */

#define CAN_BRPE_BRPE_Pos                (0)                                               /*!< CAN_T::BRPE: BRPE Position             */
#define CAN_BRPE_BRPE_Msk                (0xful << CAN_BRPE_BRPE_Pos)                      /*!< CAN_T::BRPE: BRPE Mask                 */

#define CAN_IF_CREQ_MSGNUM_Pos   (0)                                               /*!< CAN_IF_T::CREQ: MessageNumber Position*/
#define CAN_IF_CREQ_MSGNUM_Msk   (0x3ful << CAN_IF_CREQ_MSGNUM_Pos)        /*!< CAN_IF_T::CREQ: MessageNumber Mask    */

#define CAN_IF_CREQ_BUSY_Pos            (15)                                              /*!< CAN_IF_T::CREQ: Busy Position         */
#define CAN_IF_CREQ_BUSY_Msk            (0x1ul << CAN_IF_CREQ_BUSY_Pos)                   /*!< CAN_IF_T::CREQ: Busy Mask             */

#define CAN_IF_CMASK_DATAB_Pos          (0)                                               /*!< CAN_IF_T::CMASK: DAT_B Position       */
#define CAN_IF_CMASK_DATAB_Msk          (0x1ul << CAN_IF_CMASK_DATAB_Pos)                /*!< CAN_IF_T::CMASK: DAT_B Mask           */

#define CAN_IF_CMASK_DATAA_Pos          (1)                                               /*!< CAN_IF_T::CMASK: DAT_A Position       */
#define CAN_IF_CMASK_DATAA_Msk          (0x1ul << CAN_IF_CMASK_DATAA_Pos)                /*!< CAN_IF_T::CMASK: DAT_A Mask           */

#define CAN_IF_CMASK_TXRQSTNEWDAT_Pos  (2)                                               /*!< CAN_IF_T::CMASK: TxRqst_NewDat Position*/
#define CAN_IF_CMASK_TXRQSTNEWDAT_Msk  (0x1ul << CAN_IF_CMASK_TXRQSTNEWDAT_Pos)        /*!< CAN_IF_T::CMASK: TxRqst_NewDat Mask   */

#define CAN_IF_CMASK_CLRINTPND_Pos      (3)                                               /*!< CAN_IF_T::CMASK: ClrIntPnd Position   */
#define CAN_IF_CMASK_CLRINTPND_Msk      (0x1ul << CAN_IF_CMASK_CLRINTPND_Pos)            /*!< CAN_IF_T::CMASK: ClrIntPnd Mask       */

#define CAN_IF_CMASK_CONTROL_Pos        (4)                                               /*!< CAN_IF_T::CMASK: Control Position     */
#define CAN_IF_CMASK_CONTROL_Msk        (0x1ul << CAN_IF_CMASK_CONTROL_Pos)              /*!< CAN_IF_T::CMASK: Control Mask         */

#define CAN_IF_CMASK_ARB_Pos            (5)                                               /*!< CAN_IF_T::CMASK: Arb Position         */
#define CAN_IF_CMASK_ARB_Msk            (0x1ul << CAN_IF_CMASK_ARB_Pos)                  /*!< CAN_IF_T::CMASK: Arb Mask             */

#define CAN_IF_CMASK_MASK_Pos           (6)                                               /*!< CAN_IF_T::CMASK: Mask Position        */
#define CAN_IF_CMASK_MASK_Msk           (0x1ul << CAN_IF_CMASK_MASK_Pos)                 /*!< CAN_IF_T::CMASK: Mask Mask            */

#define CAN_IF_CMASK_WRRD_Pos          (7)                                               /*!< CAN_IF_T::CMASK: WR_RD Position       */
#define CAN_IF_CMASK_WRRD_Msk          (0x1ul << CAN_IF_CMASK_WRRD_Pos)                /*!< CAN_IF_T::CMASK: WR_RD Mask           */

#define CAN_IF_MASK1_Msk_Pos            (0)                                               /*!< CAN_IF_T::MASK1: Msk Position         */
#define CAN_IF_MASK1_Msk_Msk            (0xfffful << CAN_IF_MASK1_Msk_Pos)               /*!< CAN_IF_T::MASK1: Msk Mask             */

#define CAN_IF_MASK2_Msk_Pos            (0)                                               /*!< CAN_IF_T::MASK2: Msk Position         */
#define CAN_IF_MASK2_Msk_Msk            (0x1ffful << CAN_IF_MASK2_Msk_Pos)               /*!< CAN_IF_T::MASK2: Msk Mask             */

#define CAN_IF_MASK2_MDIR_Pos           (14)                                              /*!< CAN_IF_T::MASK2: MDir Position        */
#define CAN_IF_MASK2_MDIR_Msk           (0x1ul << CAN_IF_MASK2_MDIR_Pos)                 /*!< CAN_IF_T::MASK2: MDir Mask            */

#define CAN_IF_MASK2_MXTD_Pos           (15)                                              /*!< CAN_IF_T::MASK2: MXtd Position        */
#define CAN_IF_MASK2_MXTD_Msk           (0x1ul << CAN_IF_MASK2_MXTD_Pos)                 /*!< CAN_IF_T::MASK2: MXtd Mask            */

#define CAN_IF_ARB1_ID_Pos              (0)                                               /*!< CAN_IF_T::ARB1: ID Position           */
#define CAN_IF_ARB1_ID_Msk              (0xfffful << CAN_IF_ARB1_ID_Pos)                 /*!< CAN_IF_T::ARB1: ID Mask               */

#define CAN_IF_ARB2_ID_Pos              (0)                                               /*!< CAN_IF_T::ARB2: ID Position           */
#define CAN_IF_ARB2_ID_Msk              (0x1ffful << CAN_IF_ARB2_ID_Pos)                 /*!< CAN_IF_T::ARB2: ID Mask               */

#define CAN_IF_ARB2_DIR_Pos             (13)                                              /*!< CAN_IF_T::ARB2: Dir Position          */
#define CAN_IF_ARB2_DIR_Msk             (0x1ul << CAN_IF_ARB2_DIR_Pos)                   /*!< CAN_IF_T::ARB2: Dir Mask              */

#define CAN_IF_ARB2_XTD_Pos             (14)                                              /*!< CAN_IF_T::ARB2: Xtd Position          */
#define CAN_IF_ARB2_XTD_Msk             (0x1ul << CAN_IF_ARB2_XTD_Pos)                   /*!< CAN_IF_T::ARB2: Xtd Mask              */

#define CAN_IF_ARB2_MSGVAL_Pos          (15)                                              /*!< CAN_IF_T::ARB2: MsgVal Position       */
#define CAN_IF_ARB2_MSGVAL_Msk          (0x1ul << CAN_IF_ARB2_MSGVAL_Pos)                /*!< CAN_IF_T::ARB2: MsgVal Mask           */

#define CAN_IF_MCON_DLC_Pos             (0)                                               /*!< CAN_IF_T::MCON: DLC Position          */
#define CAN_IF_MCON_DLC_Msk             (0xful << CAN_IF_MCON_DLC_Pos)                   /*!< CAN_IF_T::MCON: DLC Mask              */

#define CAN_IF_MCON_EOB_Pos             (7)                                               /*!< CAN_IF_T::MCON: EoB Position          */
#define CAN_IF_MCON_EOB_Msk             (0x1ul << CAN_IF_MCON_EOB_Pos)                   /*!< CAN_IF_T::MCON: EoB Mask              */

#define CAN_IF_MCON_TxRqst_Pos          (8)                                               /*!< CAN_IF_T::MCON: TxRqst Position       */
#define CAN_IF_MCON_TxRqst_Msk          (0x1ul << CAN_IF_MCON_TxRqst_Pos)                /*!< CAN_IF_T::MCON: TxRqst Mask           */

#define CAN_IF_MCON_RmtEn_Pos           (9)                                               /*!< CAN_IF_T::MCON: RmtEn Position        */
#define CAN_IF_MCON_RmtEn_Msk           (0x1ul << CAN_IF_MCON_RmtEn_Pos)                 /*!< CAN_IF_T::MCON: RmtEn Mask            */

#define CAN_IF_MCON_RXIE_Pos            (10)                                              /*!< CAN_IF_T::MCON: RxIE Position         */
#define CAN_IF_MCON_RXIE_Msk            (0x1ul << CAN_IF_MCON_RXIE_Pos)                  /*!< CAN_IF_T::MCON: RxIE Mask             */

#define CAN_IF_MCON_TXIE_Pos            (11)                                              /*!< CAN_IF_T::MCON: TxIE Position         */
#define CAN_IF_MCON_TXIE_Msk            (0x1ul << CAN_IF_MCON_TXIE_Pos)                  /*!< CAN_IF_T::MCON: TxIE Mask             */

#define CAN_IF_MCON_UMASK_Pos           (12)                                              /*!< CAN_IF_T::MCON: UMask Position        */
#define CAN_IF_MCON_UMASK_Msk           (0x1ul << CAN_IF_MCON_UMASK_Pos)                 /*!< CAN_IF_T::MCON: UMask Mask            */

#define CAN_IF_MCON_IntPnd_Pos          (13)                                              /*!< CAN_IF_T::MCON: IntPnd Position       */
#define CAN_IF_MCON_IntPnd_Msk          (0x1ul << CAN_IF_MCON_IntPnd_Pos)                /*!< CAN_IF_T::MCON: IntPnd Mask           */

#define CAN_IF_MCON_MsgLst_Pos          (14)                                              /*!< CAN_IF_T::MCON: MsgLst Position       */
#define CAN_IF_MCON_MsgLst_Msk          (0x1ul << CAN_IF_MCON_MsgLst_Pos)                /*!< CAN_IF_T::MCON: MsgLst Mask           */

#define CAN_IF_MCON_NEWDAT_Pos          (15)                                              /*!< CAN_IF_T::MCON: NewDat Position       */
#define CAN_IF_MCON_NEWDAT_Msk          (0x1ul << CAN_IF_MCON_NEWDAT_Pos)                 /*!< CAN_IF_T::MCON: NewDat Mask           */

#define CAN_IF_DAT_A1_DATA0_Pos       (0)                                               /*!< CAN_IF_T::DAT_A1: Data_0_ Position    */
#define CAN_IF_DAT_A1_DATA0_Msk       (0xfful << CAN_IF_DAT_A1_DATA0_Pos)            /*!< CAN_IF_T::DAT_A1: Data_0_ Mask        */

#define CAN_IF_DAT_A1_DATA1_Pos       (8)                                               /*!< CAN_IF_T::DAT_A1: Data_1_ Position    */
#define CAN_IF_DAT_A1_DATA1_Msk       (0xfful << CAN_IF_DAT_A1_DATA1_Pos)            /*!< CAN_IF_T::DAT_A1: Data_1_ Mask        */

#define CAN_IF_DAT_A2_DATA2_Pos       (0)                                               /*!< CAN_IF_T::DAT_A2: Data_2_ Position    */
#define CAN_IF_DAT_A2_DATA2_Msk       (0xfful << CAN_IF_DAT_A2_DATA2_Pos)            /*!< CAN_IF_T::DAT_A2: Data_2_ Mask        */

#define CAN_IF_DAT_A2_DATA3_Pos       (8)                                               /*!< CAN_IF_T::DAT_A2: Data_3_ Position    */
#define CAN_IF_DAT_A2_DATA3_Msk       (0xfful << CAN_IF_DAT_A2_DATA3_Pos)            /*!< CAN_IF_T::DAT_A2: Data_3_ Mask        */

#define CAN_IF_DAT_B1_DATA4_Pos       (0)                                               /*!< CAN_IF_T::DAT_B1: Data_4_ Position    */
#define CAN_IF_DAT_B1_DATA4_Msk       (0xfful << CAN_IF_DAT_B1_DATA4_Pos)            /*!< CAN_IF_T::DAT_B1: Data_4_ Mask        */

#define CAN_IF_DAT_B1_DATA5_Pos       (8)                                               /*!< CAN_IF_T::DAT_B1: Data_5_ Position    */
#define CAN_IF_DAT_B1_DATA5_Msk       (0xfful << CAN_IF_DAT_B1_DATA5_Pos)            /*!< CAN_IF_T::DAT_B1: Data_5_ Mask        */

#define CAN_IF_DAT_B2_DATA6_Pos       (0)                                               /*!< CAN_IF_T::DAT_B2: Data_6_ Position    */
#define CAN_IF_DAT_B2_DATA6_Msk       (0xfful << CAN_IF_DAT_B2_DATA6_Pos)            /*!< CAN_IF_T::DAT_B2: Data_6_ Mask        */

#define CAN_IF_DAT_B2_DATA7_Pos       (8)                                               /*!< CAN_IF_T::DAT_B2: Data_7_ Position    */
#define CAN_IF_DAT_B2_DATA7_Msk       (0xfful << CAN_IF_DAT_B2_DATA7_Pos)            /*!< CAN_IF_T::DAT_B2: Data_7_ Mask        */

#define CAN_TXREQ1_TXRQST16_1_Pos        (0)                                               /*!< CAN_T::TXREQ1: TxRqst16_1 Position     */
#define CAN_TXREQ1_TXRQST16_1_Msk        (0xfffful << CAN_TXREQ1_TXRQST16_1_Pos)           /*!< CAN_T::TXREQ1: TxRqst16_1 Mask         */

#define CAN_TXREQ2_TXRQST32_17_Pos       (0)                                               /*!< CAN_T::TXREQ2: TxRqst32_17 Position    */
#define CAN_TXREQ2_TXRQST32_17_Msk       (0xfffful << CAN_TXREQ2_TXRQST32_17_Pos)          /*!< CAN_T::TXREQ2: TxRqst32_17 Mask        */

#define CAN_NDAT1_NewData16_1_Pos        (0)                                               /*!< CAN_T::NDAT1: NewData16_1 Position     */
#define CAN_NDAT1_NewData16_1_Msk        (0xfffful << CAN_NDAT1_NewData16_1_Pos)           /*!< CAN_T::NDAT1: NewData16_1 Mask         */

#define CAN_NDAT2_NewData32_17_Pos       (0)                                               /*!< CAN_T::NDAT2: NewData32_17 Position    */
#define CAN_NDAT2_NewData32_17_Msk       (0xfffful << CAN_NDAT2_NewData32_17_Pos)          /*!< CAN_T::NDAT2: NewData32_17 Mask        */

#define CAN_IPND1_IntPnd16_1_Pos         (0)                                               /*!< CAN_T::IPND1: IntPnd16_1 Position      */
#define CAN_IPND1_IntPnd16_1_Msk         (0xfffful << CAN_IPND1_IntPnd16_1_Pos)            /*!< CAN_T::IPND1: IntPnd16_1 Mask          */

#define CAN_IPND2_IntPnd32_17_Pos        (0)                                               /*!< CAN_T::IPND2: IntPnd32_17 Position     */
#define CAN_IPND2_IntPnd32_17_Msk        (0xfffful << CAN_IPND2_IntPnd32_17_Pos)           /*!< CAN_T::IPND2: IntPnd32_17 Mask         */

#define CAN_MVLD1_MsgVal16_1_Pos         (0)                                               /*!< CAN_T::MVLD1: MsgVal16_1 Position      */
#define CAN_MVLD1_MsgVal16_1_Msk         (0xfffful << CAN_MVLD1_MsgVal16_1_Pos)            /*!< CAN_T::MVLD1: MsgVal16_1 Mask          */

#define CAN_MVLD2_MsgVal32_17_Pos        (0)                                               /*!< CAN_T::MVLD2: MsgVal32_17 Position     */
#define CAN_MVLD2_MsgVal32_17_Msk        (0xfffful << CAN_MVLD2_MsgVal32_17_Pos)           /*!< CAN_T::MVLD2: MsgVal32_17 Mask         */

#define CAN_WU_EN_WAKUP_EN_Pos           (0)                                               /*!< CAN_T::WU_EN: WAKUP_EN Position        */
#define CAN_WU_EN_WAKUP_EN_Msk           (0x1ul << CAN_WU_EN_WAKUP_EN_Pos)                 /*!< CAN_T::WU_EN: WAKUP_EN Mask            */

#define CAN_WU_STATUS_WAKUP_STS_Pos      (0)                                               /*!< CAN_T::WU_STATUS: WAKUP_STS Position   */
#define CAN_WU_STATUS_WAKUP_STS_Msk      (0x1ul << CAN_WU_STATUS_WAKUP_STS_Pos)            /*!< CAN_T::WU_STATUS: WAKUP_STS Mask       */

#define CAN0                 ((CAN_T *)   CAN0_BA)
#define CAN1                 ((CAN_T *)   CAN1_BA)
#define CAN2                 ((CAN_T *)   CAN2_BA)
#define CAN3                 ((CAN_T *)   CAN3_BA)

/** @addtogroup CAN_EXPORTED_STRUCTS CAN Exported Structs
  @{
*/
/**
  * @details    CAN message structure
  */
typedef struct
{
    uint32_t  IdType;       /*!< ID type */
    uint32_t  FrameType;    /*!< Frame type */
    uint32_t  Id;           /*!< Message ID */
    uint8_t   DLC;          /*!< Data length */
    uint8_t   Data[8];      /*!< Data */
} STR_CANMSG_T;

/**
  * @details    CAN mask message structure
  */
typedef struct
{
    uint8_t   u8Xtd;      /*!< Extended ID */
    uint8_t   u8Dir;      /*!< Direction */
    uint32_t  u32Id;      /*!< Message ID */
    uint8_t   u8IdType;   /*!< ID type*/
} STR_CANMASK_T;

/*@}*/ /* end of group CAN_EXPORTED_STRUCTS */

/** @cond HIDDEN_SYMBOLS */
#define MSG(id)  (id)
/** @endcond HIDDEN_SYMBOLS */

/** @addtogroup CAN_EXPORTED_FUNCTIONS CAN Exported Functions
  @{
*/

/**
 * @brief Get interrupt status.
 *
 * @param[in] can The base address of can module.
 *
 * @return CAN module status register value.
 *
 * @details Status Interrupt is generated by bits BOff (CAN_STATUS[7]), EWarn (CAN_STATUS[6]),
 *          EPass (CAN_STATUS[5]), RxOk (CAN_STATUS[4]), TxOk (CAN_STATUS[3]), and LEC (CAN_STATUS[2:0]).
 *  \hideinitializer
 */
#define CAN_GET_INT_STATUS(can) ((can)->STATUS)

/**
 * @brief Get specified interrupt pending status.
 *
 * @param[in] can The base address of can module.
 *
 * @return The source of the interrupt.
 *
 * @details If several interrupts are pending, the CAN Interrupt Register will point to the pending interrupt
 *          with the highest priority, disregarding their chronological order.
 *  \hideinitializer
 */
#define CAN_GET_INT_PENDING_STATUS(can) ((can)->IIDR)

/**
 * @brief Disable wake-up function.
 *
 * @param[in] can The base address of can module.
 *
 * @return None
 *
 * @details  The macro is used to disable wake-up function.
 * \hideinitializer
 */
#define CAN_DISABLE_WAKEUP(can) ((can)->WU_EN = 0ul)

/**
 * @brief Enable wake-up function.
 *
 * @param[in] can The base address of can module.
 *
 * @return None
 *
 * @details User can wake-up system when there is a falling edge in the CAN_Rx pin.
 * \hideinitializer
 */
#define CAN_ENABLE_WAKEUP(can) ((can)->WU_EN = CAN_WU_EN_WAKUP_EN_Msk)

/**
 * @brief Get specified Message Object new data into bit value.
 *
 * @param[in] can The base address of can module.
 * @param[in] u32MsgNum Specified Message Object number, valid value are from 0 to 31.
 *
 * @return Specified Message Object new data into bit value.
 *
 * @details The NewDat bit (CAN_IFn_MCON[15]) of a specific Message Object can be set/reset by the software through the IFn Message Interface Registers
 *          or by the Message Handler after reception of a Data Frame or after a successful transmission.
 * \hideinitializer
 */
#define CAN_GET_NEW_DATA_IN_BIT(can, u32MsgNum) ((u32MsgNum) < 16 ? (can)->NDAT1 & (1 << (u32MsgNum)) : (can)->NDAT2 & (1 << ((u32MsgNum)-16)))


/*---------------------------------------------------------------------------------------------------------*/
/* Define CAN functions prototype                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
uint32_t CAN_SetBaudRate(CAN_T *tCAN, uint32_t u32BaudRate);
uint32_t CAN_Open(CAN_T *tCAN, uint32_t u32BaudRate, uint32_t u32Mode);
void CAN_Close(CAN_T *tCAN);
void CAN_CLR_INT_PENDING_BIT(CAN_T *tCAN, uint8_t u32MsgNum);
void CAN_EnableInt(CAN_T *tCAN, uint32_t u32Mask);
void CAN_DisableInt(CAN_T *tCAN, uint32_t u32Mask);
int32_t CAN_Transmit(CAN_T *tCAN, uint32_t u32MsgNum, STR_CANMSG_T *pCanMsg);
int32_t CAN_Receive(CAN_T *tCAN, uint32_t u32MsgNum, STR_CANMSG_T *pCanMsg);
int32_t CAN_SetMultiRxMsg(CAN_T *tCAN, uint32_t u32MsgNum, uint32_t u32MsgCount, uint32_t u32IDType, uint32_t u32ID);
int32_t CAN_SetRxMsg(CAN_T *tCAN, uint32_t u32MsgNum, uint32_t u32IDType, uint32_t u32ID);
int32_t CAN_SetRxMsgAndMsk(CAN_T *tCAN, uint32_t u32MsgNum, uint32_t u32IDType, uint32_t u32ID, uint32_t u32IDMask);
int32_t CAN_SetTxMsg(CAN_T *tCAN, uint32_t u32MsgNum, STR_CANMSG_T *pCanMsg);
int32_t CAN_TriggerTxMsg(CAN_T  *tCAN, uint32_t u32MsgNum);
int32_t CAN_BasicSendMsg(CAN_T *tCAN, STR_CANMSG_T *pCanMsg);
int32_t CAN_BasicReceiveMsg(CAN_T *tCAN, STR_CANMSG_T *pCanMsg);
void CAN_EnterInitMode(CAN_T *tCAN, uint8_t u8Mask);
void CAN_EnterTestMode(CAN_T *tCAN, uint8_t u8TestMask);
void CAN_LeaveTestMode(CAN_T *tCAN);
uint32_t CAN_GetCANBitRate(CAN_T *tCAN);
uint32_t CAN_IsNewDataReceived(CAN_T *tCAN, uint8_t u8MsgObj);
void CAN_LeaveInitMode(CAN_T *tCAN);
int32_t CAN_SetRxMsgObjAndMsk(CAN_T *tCAN, uint8_t u8MsgObj, uint8_t u8idType, uint32_t u32id, uint32_t u32idmask, uint8_t u8singleOrFifoLast);
int32_t CAN_SetRxMsgObj(CAN_T *tCAN, uint8_t u8MsgObj, uint8_t u8idType, uint32_t u32id, uint8_t u8singleOrFifoLast);
void CAN_WaitMsg(CAN_T *tCAN);
int32_t CAN_ReadMsgObj(CAN_T *tCAN, uint8_t u8MsgObj, uint8_t u8Release, STR_CANMSG_T *pCanMsg);

/*@}*/ /* end of group CAN_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CAN_Driver */

/*@}*/ /* end of group Standard_Driver */



#endif /*__NU_CAN_H__ */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
