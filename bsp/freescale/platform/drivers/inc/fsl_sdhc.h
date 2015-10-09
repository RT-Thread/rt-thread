/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __SDHC_H__
#define __SDHC_H__

/*! @addtogroup sdhc_std_def */
/*! @{ */

#define SDHC_DMA_ADDRESS           (0x00U)                  /*!< SDHC DMA ADDRESS REG */
#define SDHC_ARGUMENT2             SDHC_DMA_ADDRESS
#define SDHC_BLOCK_SIZE            (0x04U)                  /*!< SDHC BLOCK SIZE REG */
#define SDHC_BLOCK_COUNT           (0x06U)                  /*!< SDHC BLOCK COUNT REG */
#define SDHC_ARGUMENT              (0x08U)                  /*!< SDHC ARGUMENT REG */

#define SDHC_TRANSFER_MODE         (0x0C)                   /*!< SDHC TRANSFER MODE REG */
#define  SDHC_TRNSM_DMA_EN          (0x01U)                 /*!< SDHC TRANSFER MODE DMA ENABLE BIT */
#define  SDHC_TRNSM_BLKCNT_EN       (0x02U)                 /*!< SDHC TRANSFER MODE BLOCK COUNT ENABLE BIT */
#define  SDHC_TRNSM_AUTOCMD12       (0x04U)                 /*!< SDHC TRANSFER MODE AUTO CMD12 BIT */
#define  SDHC_TRNSM_AUTOCMD23       (0x08U)                 /*!< SDHC TRANSFER MODE AUTO CMD23 BIT */
#define  SDHC_TRNSM_READ            (0x10U)                 /*!< SDHC TRANSFER MODE READ DATA BIT */
#define  SDHC_TRNSM_MULTI           (0x20U)                 /*!< SDHC TRANSFER MODE MULTIBLOCK BIT */

#define SDHC_COMMAND               (0x0E)                   /*!< SDHC COMMAND REG */
#define  SDHC_CMD_RESPTYPE_LSF     (0U)                     /*!< SDHC COMMAND RESPONSE TYPE SHIFT */
#define  SDHC_CMD_RESPTYPE_MASK    (0x03U)                  /*!< SDHC COMMAND RESPONSE MASK */
#define  SDHC_CMD_CRC_CHK          (0x08U)                  /*!< SDHC COMMAND CRC CHEKCING BIT */
#define  SDHC_CMD_INDEX_CHK        (0x10U)                  /*!< SDHC COMMAND INDEX CHECKING BIT */
#define  SDHC_CMD_DATA_PRSNT       (0x20U)                  /*!< SDHC COMMAND DATA PRESENT BIT*/
#define  SDHC_CMD_CMDTYPE_LSF      (6U)                     /*!< SDHC COMMAND COMMAND TYPE SHIFT */
#define  SDHC_CMD_CMDTYPE_MASK     (0xC0U)                  /*!< SDHC COMMAND COMMAND TYPE MASK*/
#define  SDHC_CMD_CMDINDEX_LSF     (8U)                     /*!< SDHC COMMAND COMMAND INDEX SHIFT */
#define  SDHC_CMD_CMDINDEX_MASK    (0x3F)                   /*!< SDHC COMMAND COMMAND INDEX MASK */

#define SDHC_RESPONSE              (0x10U)                  /*!< SDHC RESPONSE REG */

#define SDHC_BUFFER                (0x20U)                  /*!< SDHC BUFFER REG */

#define SDHC_PRESENT_STATE         (0x24U)                  /*!< SDHC PRESENT STATE REG */
#define  SDHC_PRST_CMD_INHIBIT     (0x1U)                   /*!< SDHC PRESENT STATE CMD INHIBIT BIT */
#define  SDHC_PRST_DATA_INHIBIT    (0x1 << 1)               /*!< SDHC PRESENT STATE DATA INHIBIT BIT */
#define  SDHC_PRST_DLA             (0x1 << 2)               /*!< SDHC PRESENT STATE DATA LINE ACTIVE BIT */
#define  SDHC_PRST_RETUNE_REQ      (0x1 << 3)               /*!< SDHC PRESENT STATE RETUNE REQUEST BIT */
#define  SDHC_PRST_WR_TRANS_A      (0x1 << 8)               /*!< SDHC PRESENT STATE WRITE TRANSFER ACTIVE BIT */
#define  SDHC_PRST_RD_TRANS_A      (0x1 << 9)               /*!< SDHC PRESENT STATE READ TRANSFER ACTIVE BIT */
#define  SDHC_PRST_BUFF_WR         (0x1 << 10)              /*!< SDHC PRESENT STATE BUFFER WRITE ENABLE BIT */
#define  SDHC_PRST_BUFF_RD         (0x1 << 11)              /*!< SDHC PRESENT STATE BUFFER READ ENABLE BIT */
#define  SDHC_PRST_CARD_INSERTED   (0x1 << 16)              /*!< SDHC PRESENT STATE CARD INSERTED BIT */
#define  SDHC_PRST_CSS             (0x1 << 17)              /*!< SDHC PRESENT STATE CARD STATE STABLE BIT */
#define  SDHC_PRST_CD_LVL          (0x1 << 18)              /*!< SDHC PRESENT STATE CARD DETECT PIN LEVEL BIT */
#define  SDHC_PRST_WP_LVL          (0x1 << 19)              /*!< SDHC PRESENT STATE WRITE PROTECT PIN LEVEL BIT*/
#define  SDHC_PRST_DLSL_0_3_LSF    (20U)                    /*!< SDHC PRESENT STATE DAT[3:0] LINE LEVEL SHIFT */
#define  SDHC_PRST_DLSL_0_3_MASK   (0x0F000000U)            /*!< SDHC PRESENT STATE DAT[3:0] LINE LEVEL MASK */
#define  SDHC_PRST_CMD_LVL       (0x1 << 24)                /*!< SDHC PRESENT STATE CMD LINE LEVEL BIT */

#define SDHC_HOST_CONTROL1          (0x28U)                 /*!< SDHC HOST CONTROL1 REG */
#define  SDHC_CTRL_LED             (0x01U)                  /*!< SDHC HOST CONTROL1 LED CONTROL BIT */
#define  SDHC_CTRL_4BIT            (0x02U)                  /*!< SDHC HOST CONTROL1 DATA TRANSFER WIDTH BIT */
#define  SDHC_CTRL_HISPD           (0x04U)                  /*!< SDHC HOST CONTROL1 HIGH SPEED ENABLE BIT */
#define  SDHC_CTRL_DMA_LSF         (0x3U)                   /*!< SDHC HOST CONTROL1 DMA SELECT SHIFT */
#define  SDHC_CTRL_DMA_MASK        (0x18U)                  /*!< SDHC HOST CONTROL1 DMA SELECT MASK */
#define   SDHC_CTRL_DMA_SDMA       (0x0U)                   /*!< SDHC HOST CONTROL1 DMA SELECT SDMA */
#define   SDHC_CTRL_DMA_ADMA32     (0x2U)                   /*!< SDHC HOST CONTROL1 DMA SELECT ADMA32 */
#define   SDHC_CTRL_DMA_ADMA64     (0x3U)                   /*!< SDHC HOST CONTROL1 DMA SELECT ADMA64 */
#define  SDHC_CTRL_8BIT            (0x20U)                  /*!< SDHC HOST CONTROL1 EXTENDED DATA TRANSFER WIDTH BIT */
#define  SDHC_CTRL_CD_TEST_LVL     (0x40U)                  /*!< SDHC HOST CONTROL1 CARD DETECT TEST LEVEL BIT */
#define  SDHC_CTRL_CD_SSELECT      (0x80U)                  /*!< SDHC HOST CONTROL1 CARD DETECT SIGNAL SELECTION BIT*/

#define SDHC_POWER_CONTROL         (0x29U)                  /*!< SDHC POWER CONTROL REG */
#define  SDHC_POWER_ON             (0x01U)                  /*!< SDHC POWER CONTROL SD BUS POWER */
#define  SDHC_POWER_180            (0x0A)                   /*!< SDHC POWER CONTROL SD BUS POWER 1.8V */
#define  SDHC_POWER_300            (0x0C)                   /*!< SDHC POWER CONTROL SD BUS POWER 3.0V */
#define  SDHC_POWER_330            (0x0E)                   /*!< SDHC POWER CONTROL SD BUS POWER 3.3V */

#define SDHC_BLOCK_GAP_CTRL        (0x2A)                   /*!< SDHC BLOCK GAP CONTROL REG */
#define  SDHC_BGCTRL_STPATGAPREQ   (0x01U)                  /*!< SDHC BLOCK GAP CONTROL STOP AT BLOCK GAP BIT */
#define  SDHC_BGCTRL_CNTNREQ       (0x02U)                  /*!< SDHC BLOCK GAP CONTROL CONTINUE REQUEST BIT */
#define  SDHC_BGCTRL_READWAIT      (0x04U)                  /*!< SDHC BLOCK GAP CONTROL READ WAIT CONTROL BIT */
#define  SDHC_BGCTRL_INTRATGAP     (0x08U)                  /*!< SDHC BLOCK GAP CONTROL INTERRUPT AT BLOCK GAP BIT */

#define SDHC_WAKEUP_CONTROL       (0x2B)                    /*!< SDHC WAKEUP CONTROL REG */
#define  SDHC_WAKE_ON_INT          (0x01U)                  /*!< SDHC WAKEUP CONTROL WAKEUP ON CARD INTERRUPT BIT */
#define  SDHC_WAKE_ON_INSERT       (0x02U)                  /*!< SDHC WAKEUP CONTROL WAKEUP ON CARD INSERTION BIT */
#define  SDHC_WAKE_ON_REMOVE       (0x04U)                  /*!< SDHC WAKEUP CONTROL WAKEUP ON CARD REMOVAL BIT */

#define SDHC_CLOCK_CONTROL         (0x2C)                   /*!< SDHC CLOCK CONTROL REG */
#define  SDHC_CLK_INTCLK_EN        (0x0001U)                /*!< SDHC CLOCK CONTROL INTERNAL CLOCK ENABLE BIT */
#define  SDHC_CLK_INTCLK_STB       (0x0002U)                /*!< SDHC CLOCK CONTROL INTERNAL CLOCK STABLE BIT */
#define  SDHC_CLK_SDCLK_EN         (0x0004U)                /*!< SDHC CLOCK CONTROL SD CLOCK ENABLE BIT */
#define  SDHC_CLK_CLKGEN_PRG_SEL   (0x0020U)                /*!< SDHC CLOCK CONTROL CLOCK GENERATOR SELECTOR BIT */
#define  SDHC_CLK_FREQ_U_LSF       (6U)                     /*!< SDHC CLOCK CONTROL UPPER BITS OF FREQUENCY SELECTOR SHIFT */
#define  SDHC_CLK_FREQ_U_MASK      (0x00C0U)                /*!< SDHC CLOCK CONTROL UPPER BITS OF FREQUENCY SELECTOR MASK */
#define  SDHC_CLK_FREQ_SEL_LSF     (8U)                     /*!< SDHC CLOCK CONTROL FREQUENCY SELECTOR SHIFT */
#define  SDHC_CLK_FREQ_SEL_MASK    (0xFF00U)                /*!< SDHC CLOCK CONTROL FREQUENCY SELECTOR MASK */

#define SDHC_TIMEOUT_CONTROL       (0x2E)                   /*!< SDHC TIMEOUT CONTROL REG */

#define SDHC_SOFTWARE_RESET        (0x2F)                   /*!< SDHC SOFTWARE RESET REG */
#define  SDHC_RESET_ALL            (0x01U)                  /*!< SDHC SOFTWARE RESET RESET FOR ALL*/
#define  SDHC_RESET_CMD            (0x02U)                  /*!< SDHC SOFTWARE RESET RESET FOR CMD LINE */
#define  SDHC_RESET_DATA           (0x04U)                  /*!< SDHC SOFTWARE RESET RESET FOR DATA LINE */

#define SDHC_INT_STATUS            (0x30U)                  /*!< SDHC NORMAL INTERRUPT STATUS REG */
#define SDHC_INT_ENABLE            (0x34U)                  /*!< SDHC NORMAL INTERRUPT STATUS ENABLE REG */
#define SDHC_SIGNAL_ENABLE         (0x38U)                  /*!< SDHC NORMAL INTERRUPT SIGNAL REG */
#define  SDHC_INT_CMD_DONE         (0x1U << 0)               /*!< SDHC NORMAL INTERRUPT CMD COMPLETE EVENT BIT */
#define  SDHC_INT_TRANSFER_DONE    (0x1U << 1)               /*!< SDHC NORMAL INTERRUPT TRANSFER COMPLETE EVENT BIT */
#define  SDHC_INT_BLKGAP_EVENT     (0x1U << 2)               /*!< SDHC NORMAL INTERRUPT BLOCK GAP EVENT BIT */
#define  SDHC_INT_DMA              (0x1U << 3)               /*!< SDHC NORMAL INTERRUPT DMA EVENT BIT */
#define  SDHC_INT_WBUF_READY       (0x1U << 4)               /*!< SDHC NORMAL INTERRUPT WRITE BUFFER READY EVENT BIT */
#define  SDHC_INT_RBUF_READY       (0x1U << 5)               /*!< SDHC NORMAL INTERRUPT READ BUFFER READY EVENT BIT */
#define  SDHC_INT_CARD_INSERT      (0x1U << 6)               /*!< SDHC NORMAL INTERRUPT CARD INSERTION EVENT BIT */
#define  SDHC_INT_CARD_REMOVE      (0x1U << 7)               /*!< SDHC NORMAL INTERRUPT CARD REMOVAL EVENT BIT */
#define  SDHC_INT_CARD_INTR        (0x1U << 8)               /*!< SDHC NORMAL INTERRUPT CARD INTERRUPT BIT */
#define  SDHC_INT_INT_A            (0x1U << 9)               /*!< SDHC NORMAL INTERRUPT INT_A EVENT BIT */
#define  SDHC_INT_INT_B            (0x1U << 10)              /*!< SDHC NORMAL INTERRUPT INT_B EVENT BIT */
#define  SDHC_INT_INT_C            (0x1U << 11)              /*!< SDHC NORMAL INTERRUPT INT_C EVENT BIT */
#define  SDHC_INT_RETUNING         (0x1U << 12)              /*!< SDHC NORMAL INTERRUPT RETUNING EVENT BIT */
#define  SDHC_INT_ERROR_INTR       (0x1U << 15)              /*!< SDHC NORMAL INTERRUPT ERROR INTERRUPT BIT */
#define  SDHC_INT_E_CMD_TIMEOUT    (0x1U << 16)              /*!< SDHC NORMAL INTERRUPT CMD TIMEOUT ERROR BIT */
#define  SDHC_INT_E_CMD_CRC        (0x1U << 17)              /*!< SDHC NORMAL INTERRUPT CMD CRC ERROR BIT */
#define  SDHC_INT_E_CMD_END_BIT    (0x1U << 18)              /*!< SDHC NORMAL INTERRUPT CMD INDEX ERROR BIT */
#define  SDHC_INT_E_CMD_INDEX      (0x1U << 19)              /*!< SDHC NORMAL INTERRUPT CMD END BIT ERROR BIT */
#define  SDHC_INT_E_DATA_TIMEOUT   (0x1U << 20)              /*!< SDHC NORMAL INTERRUPT DATA TIMEOUT ERROR BIT */
#define  SDHC_INT_E_DATA_CRC       (0x1U << 21)              /*!< SDHC NORMAL INTERRUPT DATA CRC ERROR BIT */
#define  SDHC_INT_E_DATA_END_BIT   (0x1U << 22)              /*!< SDHC NORMAL INTERRUPT DATA END BIT ERROR BIT */
#define  SDHC_INT_E_CUR_LIMIT      (0x1U << 23)              /*!< SDHC NORMAL INTERRUPT CURRENT LIMIT ERROR BIT */
#define  SDHC_INT_E_AUTOCMD12      (0x1U << 24)              /*!< SDHC NORMAL INTERRUPT AUTO CMD12 ERROR BIT */
#define  SDHC_INT_E_ADMA           (0x1U << 25)              /*!< SDHC NORMAL INTERRUPT ADMA ERROR BIT */
#define  SDHC_INT_E_TUNING         (0x1U << 26)              /*!< SDHC NORMAL INTERRUPT TUNING ERROR BIT */

#define SDHC_INT_CMD_MASK          (SDHC_INT_CMD_DONE | SDHC_INT_E_CMD_TIMEOUT |\
                                    SDHC_INT_E_CMD_CRC | SDHC_INT_E_CMD_INDEX |\
                                    SDHC_INT_E_CMD_END_BIT)
#define SDHC_INT_DATA_MASK         (SDHC_INT_TRANSFER_DONE | SDHC_INT_E_DATA_TIMEOUT |\
                                    SDHC_INT_E_DATA_CRC | SDHC_INT_E_DATA_END_BIT)
#define SDHC_INT_CARD_DET_MASK     (SDHC_INT_CARD_REMOVE | SDHC_INT_CARD_INSERT)
#define SDHC_INT_NORMAL_MASK       (0x00007FFFU)
#define SDHC_INT_ERROR_MASK        (0xFFFF8000U)
#define SDHC_INT_ALL_MASK          ((uint32_t)-1)

#define SDHC_ACMD12_ERROR          (0x3CU)                  /*!< SDHC AUTO CMD12 ERROR REG */

#define SDHC_HOST_CONTROL2         (0x3EU)                  /*!< SDHC HOST CONTROL2 REG */
#define  SDHC_CTRL2_UHS_MASK       (0x0007U)                /*!< SDHC HOST CONTROL2 UHS MODE MASK */
#define  SDHC_CTRL2_UHS_SDR12      (0x0000U)                /*!< SDHC HOST CONTROL2 UHS-I SDR12 */
#define  SDHC_CTRL2_UHS_SDR25      (0x0001U)                /*!< SDHC HOST CONTROL2 UHS-I SDR25 */
#define  SDHC_CTRL2_UHS_SDR50      (0x0002U)                /*!< SDHC HOST CONTROL2 UHS-I SDR50 */
#define  SDHC_CTRL2_UHS_SDR104     (0x0003U)                /*!< SDHC HOST CONTROL2 UHS-I SDR104 */
#define  SDHC_CTRL2_UHS_DDR50      (0x0004U)                /*!< SDHC HOST CONTROL2 UHS-I DDR50 */
#define  SDHC_CTRL2_HS_SDR200      (0x0005U)                /*!< SDHC HOST CONTROL2 HS SDR2000*/
#define SDHC_CTRL2_VDD_180         (0x0008U)                /*!< SDHC HOST CONTROL2 1.8V SINGALING ENABLE */
#define SDHC_CTRL2_DRV_TYPE_MASK   (0x0030U)                /*!< SDHC HOST CONTROL2 DRIVE MASK */
#define  SDHC_CTRL2_DRV_TYPE_B     (0x0000U)                /*!< SDHC HOST CONTROL2 DRIVE TYPE B */
#define  SDHC_CTRL2_DRV_TYPE_A     (0x0010U)                /*!< SDHC HOST CONTROL2 DRIVE TYPE A */
#define  SDHC_CTRL2_DRV_TYPE_C     (0x0020U)                /*!< SDHC HOST CONTROL2 DRIVE TYPE C */
#define  SDHC_CTRL2_DRV_TYPE_D     (0x0030U)                /*!< SDHC HOST CONTROL2 DRIVE TYPE D */
#define SDHC_CTRL2_EXEC_TUNING     (0x0040U)                /*!< SDHC HOST CONTROL2 EXECUTE TUNING */
#define SDHC_CTRL2_TUNED_CLK       (0x0080U)                /*!< SDHC HOST CONTROL2 SAMPLING CLOCK SELECT */
#define SDHC_CTRL2_ASNYC_INTR_EN   (0x4000U)                /*!< SDHC HOST CONTROL2 ASYNC INTERRUPT ENABLE*/
#define SDHC_CTRL2_PRESET_VAL_EN   (0x8000U)                /*!< SDHC HOST CONTROL2 PRESET VALUE ENABLE */

#define SDHC_HOST_CAPABILITIES     (0x40U)                  /*!< SDHC CAPABILITIES REG */
#define  SDHC_HCAP_TOCLKFREQ_MASK  (0x0000003F)             /*!< SDHC CAPABILITIES TIMEOUT CLOCK FREQUENCY */
#define  SDHC_HCAP_TOCKLUINT_MHZ   (0x00000080U)            /*!< SDHC CAPABILITIES TIMEOUT CLOCK UNIT */
#define  SDHC_HCAP_CLK_BASE_MASK   (0x00003F00U)            /*!< SDHC CAPABILITIES BASE CLOCK FREQUENCY FOR SD CLOCK MASK */
#define  SDHC_HCAP_MAX_BLK_LSF     (16U)                    /*!< SDHC CAPABILITIES MAX BLOCK LENGTH SHIFT */
#define  SDHC_HCAP_MAX_BLK_MASK    (0x00030000U)            /*!< SDHC CAPABILITIES MAX BLOCK LENGTH MASK */
#define   SDHC_HCAP_MAXBLK_512     (0x0U)                   /*!< SDHC CAPABILITIES MAX BLOCK LENGTH 512B */
#define   SDHC_HCAP_MAXBLK_1024    (0x1U)                   /*!< SDHC CAPABILITIES MAX BLOCK LENGTH 1024B */
#define   SDHC_HCAP_MAXBLK_2048    (0x2U)                   /*!< SDHC CAPABILITIES MAX BLOCK LENGTH 2048B */
#define  SDHC_HCAP_SUPPORT_8BIT    (0x00040000U)            /*!< SDHC CAPABILITIES SUPPORT 8 BIT */
#define  SDHC_HCAP_SUPPORT_ADMA2   (0x00080000U)            /*!< SDHC CAPABILITIES SUPPORT ADMA2 */
#define  SDHC_HCAP_SUPPORT_ADMA1   (0x00100000U)            /*!< SDHC CAPABILITIES SUPPORT ADMA1 */
#define  SDHC_HCAP_SUPPORT_HISPD   (0x00200000U)            /*!< SDHC CAPABILITIES SUPPORT HIGH SPEED */
#define  SDHC_HCAP_SUPPORT_SDMA    (0x00400000U)            /*!< SDHC CAPABILITIES SUPPORT SDMA */
#define  SDHC_HCAP_SUPPORT_SUSPEND (0x00800000U)            /*!< SDHC CAPABILITIES SUPPORT SUSPEND RESUME */
#define  SDHC_HCAP_SUPPORT_V330    (0x01000000U)            /*!< SDHC CAPABILITIES SUPPORT 3.3V */
#define  SDHC_HCAP_SUPPORT_V300    (0x02000000U)            /*!< SDHC CAPABILITIES SUPPORT 3.0V */
#define  SDHC_HCAP_SUPPORT_V180    (0x04000000U)            /*!< SDHC CAPABILITIES SUPPORT 1.8V */
#define  SDHC_HCAP_SUPPORT_64BIT   (0x10000000U)            /*!< SDHC CAPABILITIES SUPPORT 64-BIT */
#define  SDHC_HCAP_SUPPORT_ASYNC   (0x20000000U)            /*!< SDHC CAPABILITIES SUPPORT ASYNC INTERRUPT */
#define  SDHC_HCAP_SLOT_TYPE_LSF   (30U)                    /*!< SDHC CAPABILITIES SLOT TYPE SHIFT */
#define  SDHC_HCAP_SLOT_TYPE_MASK  (0xC0000000U)            /*!< SDHC CAPABILITIES SLOT TYPE MASK */
#define   SDHC_HCAP_SLOT_REMOVABLE (0x0U)                   /*!< SDHC CAPABILITIES SLOT TYPE REMOVABLE */
#define   SDHC_HCAP_SLOT_EMBEDDED  (0x1U)                   /*!< SDHC CAPABILITIES SLOT TYPE EMBEDDED SLOT FOR ONE DEVICE */
#define   SDHC_HCAP_SLOT_SHARED    (0x2U)                   /*!< SDHC CAPABILITIES SLOT TYPE SHARED BUS SLOT */

#define SDHC_HOST_CAPABILITIES_1   (0x44U)                  /*!< SDHC CAPABILITIES1 REG */
#define  SDHC_HCAP_SUPORT_SDR50    (0x00000001U)            /*!< SDHC CAPABILITIES1 SUPPORT SDR50 */
#define  SDHC_HCAP_SUPORT_SDR104   (0x00000002U)            /*!< SDHC CAPABILITIES1 SUPPORT SDR104 */
#define  SDHC_HCAP_SUPORT_DDR50    (0x00000004U)            /*!< SDHC CAPABILITIES1 SUPPORT DDR50 */
#define  SDHC_HCAP_DRIVER_TYPE_A   (0x00000010U)            /*!< SDHC CAPABILITIES1 SUPPORT DRIVER TYPE A */
#define  SDHC_HCAP_DRIVER_TYPE_C   (0x00000020U)            /*!< SDHC CAPABILITIES1 SUPPORT DRIVER TYPE C */
#define  SDHC_HCAP_DRIVER_TYPE_D   (0x00000040U)            /*!< SDHC CAPABILITIES1 SUPPORT DRIVER TYPE D */
#define  SDHC_HCAP_RT_TMCNT_LSF    (8U)                     /*!< SDHC CAPABILITIES1 TIMER COUNT FOR RETUNING SHIFT */
#define  SDHC_HCAP_RT_TMCNT_MASK   (0x00000F00U)            /*!< SDHC CAPABILITIES1 TIMER COUNT FOR RETUNING MASK */
#define  SDHC_HCAP_USE_SDR50_TUNE  (0x00002000U)            /*!< SDHC CAPABILITIES1 USE TUNING FOR SDR50 */
#define  SDHC_HCAP_RT_MODE_LSF     (14U)                    /*!< SDHC CAPABILITIES1 RETUNE MODE SHIFT */
#define  SDHC_HCAP_RT_MODE_MASK    (0x0000C000U)            /*!< SDHC CAPABILITIES1 RETUNE MODE MASK */
#define  SDHC_HCAP_CLK_MUL_LSF     (16U)                    /*!< SDHC CAPABILITIES1 CLOCK MULTIPLIER SHIFT */
#define  SDHC_HCAP_CLK_MUL_MASK    (0x00FF0000U)            /*!< SDHC CAPABILITIES1 CLOCK MULTIPLIER MASK */

#define SDHC_MAX_CURRENT           (0x48U)                  /*!< SDHC MAX CURRENT REG */
#define  SDHC_MC_330_LSF           (0U)                     /*!< SDHC MAX CURRENT MAXIMUM CURRENT FOR 3.3V SHIFT */
#define  SDHC_MC_330_MASK          (0x0000FF)               /*!< SDHC MAX CURRENT MAXIMUM CURRENT FOR 3.3V MASK */
#define  SDHC_MC_300_LSF           (8U)                     /*!< SDHC MAX CURRENT MAXIMUM CURRENT FOR 3.0V SHIFT */
#define  SDHC_MC_300_MASK          (0x00FF00U)              /*!< SDHC MAX CURRENT MAXIMUM CURRENT FOR 3.0V MASK */
#define  SDHC_MC_180_LSF           (16U)                    /*!< SDHC MAX CURRENT MAXIMUM CURRENT FOR 1.8V SHIFT */
#define  SDHC_MC_180_MASK          (0xFF0000U)              /*!< SDHC MAX CURRENT MAXIMUM CURRENT FOR 1.8V MASK */

#define SDHC_FRC_EVENT_AUTOCMD     (0x50U)                  /*!< SDHC FORCE EVENT FOR AUTOCMD REG */
#define  SDHC_FEA_E_NO_ACMD12_EXEC (0x0001U)                /*!< SDHC FORCE EVENT AUTO CMD12 NOT EXECUTED */
#define  SDHC_FEA_E_ACMD_TIMEOUT   (0x002U)                 /*!< SDHC FORCE EVENT AUTO CMD TIMEOUT ERROR */
#define  SDHC_FEA_E_ACMD_CRC       (0x0004U)                /*!< SDHC FORCE EVENT AUTO CMD CRC ERROR */
#define  SDHC_FEA_E_ACMD_END       (0x0008U)                /*!< SDHC FORCE EVENT AUTO CMD END BIT ERROR */
#define  SDHC_FEA_E_ACMD_INDEX     (0x0010U)                /*!< SDHC FORCE EVENT AUTO CMD INDEX ERROR */
#define  SDHC_FEA_E_CMD_NOT_BY_ACMD12 (0x0080U)             /*!< SDHC FORCE EVENT AUTO CMD NOT ISSUED ERROR */

#define SDHC_FRC_EVENT_ERROR_INTR  (0x52U)                  /*!< SDHC FORCE EVENT FOR ERROR REG */
#define  SDHC_FEI_E_CMD_TIMEOUT    (0x0001U)                /*!< SDHC FORCE CMD TIMEOUT ERROR */
#define  SDHC_FEI_E_CMD_CRC        (0x0002U)                /*!< SDHC FORCE CMD CRC ERROR */
#define  SDHC_FEI_E_CMD_END_BIT    (0x0004U)                /*!< SDHC FORCE CMD END BIT ERROR */
#define  SDHC_FEI_E_DATA_TIMEOUT   (0x0008U)                /*!< SDHC FORCE DATA TIMEOUT ERROR */
#define  SDHC_FEI_E_DATA_CRC       (0x0010U)                /*!< SDHC FORCE DATA CRC ERROR */
#define  SDHC_FEI_E_DATA_END_BIT   (0x0020U)                /*!< SDHC FORCE DATA END BIT ERROR */
#define  SDHC_FEI_E_CURRENT_LIMIT  (0x0040U)                /*!< SDHC FORCE CURRENT LIMIT ERROR */
#define  SDHC_FEI_E_AUTO_CMD       (0x0080U)                /*!< SDHC FORCE AUTOCMD ERROR */
#define  SDHC_FEI_E_ADMA           (0x0100U)                /*!< SDHC FORCE ADMA ERROR */

#define SDHC_ADMA_ERROR            (0x54U)                  /*!< SDHC ADMA ERROR REG */
#define SDHC_ADMA_ADDRESS          (0x58U)                  /*!< SDHC ADMA ADDRESS REG */

#define SDHC_SLOT_INT_STATUS       (0xFCU)                  /*!< SDHC SLOT INTERRUPT STATUS REG */
#define SDHC_HOST_VERSION          (0xFEU)                  /*!< SDHC HOST CONTROLLER VERSION REG */
#define  SDHC_VENDOR_VER_LSF       (8U)                     /*!< SDHC HOST CONTROLLER VERSION VENDOR VERSION SHIFT */
#define  SDHC_VENDOR_VER_MASK      (0xFF00U)                /*!< SDHC HOST CONTROLLER VERSION VENDOR VERSION MASK */
#define  SDHC_SPEC_VER_LSF         (0U)                     /*!< SDHC HOST CONTROLLER VERSION SPEC VERSION SHIFT */
#define  SDHC_SPEC_VER_MASK        (0x00FFU)                /*!< SDHC HOST CONTROLLER VERSION SPEC VERSION MASK */
#define   SDHC_SPEC_100            (0U)                     /*!< SDHC HOST CONTROLLER VERSION SPEC VERSION 1.00 */
#define   SDHC_SPEC_200            (1U)                     /*!< SDHC HOST CONTROLLER VERSION SPEC VERSION 2.00 */
#define   SDHC_SPEC_300            (2U)                     /*!< SDHC HOST CONTROLLER VERSION SPEC VERSION 3.00 */

/*! @} */
#endif

/*************************************************************************************************
 * EOF
 ************************************************************************************************/
