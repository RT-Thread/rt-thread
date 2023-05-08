/**
  ******************************************************************************
  * @file    usb_v2_reg.h
  * @version V1.0
  * @date    2022-08-15
  * @brief   This file is the description of.IP register
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __HARDWARE_USB_V2_H__
#define __HARDWARE_USB_V2_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define USB_HCCAP_OFFSET            (0x0)   /* HCCAP */
#define USB_HCSPARAMS_OFFSET        (0x4)   /* HCSPARAMS */
#define USB_HCCPARAMS_OFFSET        (0x8)   /* HCCPARAMS */
#define USBCMD_OFFSET               (0x10)  /* USBCMD */
#define USBSTS_OFFSET               (0x14)  /* USBSTS */
#define USBINTR_OFFSET              (0x18)  /* USBINTR */
#define USB_FRINDEX_OFFSET          (0x1C)  /* FRINDEX */
#define USB_PERIODICLISTBASE_OFFSET (0x24)  /* PERIODICLISTBASE */
#define USB_ASYNCLISTADDR_OFFSET    (0x28)  /* ASYNCLISTADDR */
#define USB_PORTSC_OFFSET           (0x30)  /* PORTSC */
#define USB_HCMISC_OFFSET           (0x40)  /* HCMISC */
#define USB_FS_EOF_OFFSET           (0x44)  /* FS_EOF */
#define USB_HS_EOF_OFFSET           (0x48)  /* HS_EOF */
#define USB_OTG_CSR_OFFSET          (0x80)  /* OTG_CSR */
#define USB_OTG_ISR_OFFSET          (0x84)  /* OTG_ISR */
#define USB_OTG_IER_OFFSET          (0x88)  /* OTG_IER */
#define USB_GLB_ISR_OFFSET          (0xC0)  /* GLB_ISR */
#define USB_GLB_INT_OFFSET          (0xC4)  /* GLB_INT */
#define USB_REVISION_OFFSET         (0xE0)  /* REVISION */
#define USB_FEATURE_OFFSET          (0xE4)  /* FEATURE */
#define USB_AXI_CR_OFFSET           (0xE8)  /* AXI_CR */
#define USB_DEV_CTL_OFFSET          (0x100) /* DEV_CTL */
#define USB_DEV_ADR_OFFSET          (0x104) /* DEV_ADR */
#define USB_DEV_TST_OFFSET          (0x108) /* DEV_TST */
#define USB_DEV_SFN_OFFSET          (0x10C) /* DEV_SFN */
#define USB_DEV_SMT_OFFSET          (0x110) /* DEV_SMT */
#define USB_PHY_TST_OFFSET          (0x114) /* PHY_TST */
#define USB_DEV_VCTL_OFFSET         (0x118) /* DEV_VCTL */
#define USB_DEV_CXCFG_OFFSET        (0x11C) /* DEV_CXCFG */
#define USB_DEV_CXCFE_OFFSET        (0x120) /* DEV_CXCFE */
#define USB_DEV_ICR_OFFSET          (0x124) /* DEV_ICR */
#define USB_DEV_MIGR_OFFSET         (0x130) /* DEV_MIGR */
#define USB_DEV_MISG0_OFFSET        (0x134) /* DEV_MISG0 */
#define USB_DEV_MISG1_OFFSET        (0x138) /* DEV_MISG1 */
#define USB_DEV_MISG2_OFFSET        (0x13C) /* DEV_MISG2 */
#define USB_DEV_IGR_OFFSET          (0x140) /* DEV_IGR */
#define USB_DEV_ISG0_OFFSET         (0x144) /* DEV_ISG0 */
#define USB_DEV_ISG1_OFFSET         (0x148) /* DEV_ISG1 */
#define USB_DEV_ISG2_OFFSET         (0x14C) /* DEV_ISG2 */
#define USB_DEV_RXZ_OFFSET          (0x150) /* DEV_RXZ */
#define USB_DEV_TXZ_OFFSET          (0x154) /* DEV_TXZ */
#define USB_DEV_ISE_OFFSET          (0x158) /* DEV_ISE */
#define USB_DEV_INMPS1_OFFSET       (0x160) /* DEV_INMPS1 */
#define USB_DEV_INMPS2_OFFSET       (0x164) /* DEV_INMPS2 */
#define USB_DEV_INMPS3_OFFSET       (0x168) /* DEV_INMPS3 */
#define USB_DEV_INMPS4_OFFSET       (0x16C) /* DEV_INMPS4 */
#define USB_DEV_INMPS5_OFFSET       (0x170) /* DEV_INMPS5 */
#define USB_DEV_INMPS6_OFFSET       (0x174) /* DEV_INMPS6 */
#define USB_DEV_INMPS7_OFFSET       (0x178) /* DEV_INMPS7 */
#define USB_DEV_INMPS8_OFFSET       (0x17C) /* DEV_INMPS8 */
#define USB_DEV_OUTMPS1_OFFSET      (0x180) /* DEV_OUTMPS1 */
#define USB_DEV_OUTMPS2_OFFSET      (0x184) /* DEV_OUTMPS2 */
#define USB_DEV_OUTMPS3_OFFSET      (0x188) /* DEV_OUTMPS3 */
#define USB_DEV_OUTMPS4_OFFSET      (0x18C) /* DEV_OUTMPS4 */
#define USB_DEV_OUTMPS5_OFFSET      (0x190) /* DEV_OUTMPS5 */
#define USB_DEV_OUTMPS6_OFFSET      (0x194) /* DEV_OUTMPS6 */
#define USB_DEV_OUTMPS7_OFFSET      (0x198) /* DEV_OUTMPS7 */
#define USB_DEV_OUTMPS8_OFFSET      (0x19C) /* DEV_OUTMPS8 */
#define USB_DEV_EPMAP0_OFFSET       (0x1A0) /* DEV_EPMAP0 */
#define USB_DEV_EPMAP1_OFFSET       (0x1A4) /* DEV_EPMAP1 */
#define USB_DEV_FMAP_OFFSET         (0x1A8) /* DEV_FMAP */
#define USB_DEV_FCFG_OFFSET         (0x1AC) /* DEV_FCFG */
#define USB_DEV_FIBC0_OFFSET        (0x1B0) /* DEV_FIBC0 */
#define USB_DEV_FIBC1_OFFSET        (0x1B4) /* DEV_FIBC1 */
#define USB_DEV_FIBC2_OFFSET        (0x1B8) /* DEV_FIBC2 */
#define USB_DEV_FIBC3_OFFSET        (0x1BC) /* DEV_FIBC3 */
#define USB_DMA_TFN_OFFSET          (0x1C0) /* DMA_TFN */
#define USB_DMA_CPS0_OFFSET         (0x1C4) /* DMA_CPS0 */
#define USB_DMA_CPS1_OFFSET         (0x1C8) /* DMA_CPS1 */
#define USB_DMA_CPS2_OFFSET         (0x1CC) /* DMA_CPS2 */
#define USB_DMA_CPS3_OFFSET         (0x1D0) /* DMA_CPS3 */
#define USB_DMA_CPS4_OFFSET         (0x1D4) /* DMA_CPS4 */
#define USB_DEV_FMAP2_OFFSET        (0x1D8) /* DEV_FMAP2 */
#define USB_DEV_FCFG2_OFFSET        (0x1DC) /* DEV_FCFG2 */
#define USB_DEV_FMAP3_OFFSET        (0x1E0) /* DEV_FMAP3 */
#define USB_DEV_FCFG3_OFFSET        (0x1E4) /* DEV_FCFG3 */
#define USB_DEV_FMAP4_OFFSET        (0x1E8) /* DEV_FMAP4 */
#define USB_DEV_FCFG4_OFFSET        (0x1EC) /* DEV_FCFG4 */
#define USB_DEV_FIBC4_OFFSET        (0x1F0) /* DEV_FIBC4 */
#define USB_DEV_FIBC5_OFFSET        (0x1F4) /* DEV_FIBC5 */
#define USB_DEV_FIBC6_OFFSET        (0x1F8) /* DEV_FIBC6 */
#define USB_DEV_FIBC7_OFFSET        (0x1FC) /* DEV_FIBC7 */
#define USB_VDMA_CXFPS1_OFFSET      (0x300) /* VDMA_CXFPS1 */
#define USB_VDMA_CXFPS2_OFFSET      (0x304) /* VDMA_CXFPS2 */
#define USB_VDMA_F0PS1_OFFSET       (0x308) /* VDMA_F0PS1 */
#define USB_VDMA_F0PS2_OFFSET       (0x30C) /* VDMA_F0PS2 */
#define USB_VDMA_F1PS1_OFFSET       (0x310) /* VDMA_F1PS1 */
#define USB_VDMA_F1PS2_OFFSET       (0x314) /* VDMA_F1PS2 */
#define USB_VDMA_F2PS1_OFFSET       (0x318) /* VDMA_F2PS1 */
#define USB_VDMA_F2PS2_OFFSET       (0x31C) /* VDMA_F2PS2 */
#define USB_VDMA_F3PS1_OFFSET       (0x320) /* VDMA_F3PS1 */
#define USB_VDMA_F3PS2_OFFSET       (0x324) /* VDMA_F3PS2 */
#define USB_DEV_ISG3_OFFSET         (0x328) /* DEV_ISG3 */
#define USB_DEV_MISG3_OFFSET        (0x32C) /* DEV_MISG3 */
#define USB_VDMA_CTRL_OFFSET        (0x330) /* VDMA_CTRL */
#define USB_LPM_CAP_OFFSET          (0x334) /* LPM_CAP */
#define USB_DEV_ISG4_OFFSET         (0x338) /* DEV_ISG4 */
#define USB_DEV_MISG4_OFFSET        (0x33C) /* DEV_MISG4 */
#define USB_VDMA_FNPS1_OFFSET       (0x350) /* VDMA_FNPS1 */
#define USB_VDMA_FNPS2_OFFSET       (0x354) /* VDMA_FNPS2 */

/* Register Bitfield definitions *****************************************************/

/* 0x0 : HCCAP */
#define USB_CAPLENGTH_SHIFT  (0U)
#define USB_CAPLENGTH_MASK   (0xff << USB_CAPLENGTH_SHIFT)
#define USB_HCIVERSION_SHIFT (16U)
#define USB_HCIVERSION_MASK  (0xffff << USB_HCIVERSION_SHIFT)

/* 0x4 : HCSPARAMS */
#define USB_N_PORTS_SHIFT (0U)
#define USB_N_PORTS_MASK  (0xf << USB_N_PORTS_SHIFT)

/* 0x8 : HCCPARAMS */
#define USB_PROG_FR_LIST_FLAG (1 << 1U)
#define USB_ASYN_SCH_PARK_CAP (1 << 2U)

/* 0x10 : USBCMD */
#define USB_RS                (1 << 0U)
#define USB_HC_RESET          (1 << 1U)
#define USB_FRL_SIZE_SHIFT    (2U)
#define USB_FRL_SIZE_MASK     (0x3 << USB_FRL_SIZE_SHIFT)
#define USB_PSCH_EN           (1 << 4U)
#define USB_ASCH_EN           (1 << 5U)
#define USB_INT_OAAD          (1 << 6U)
#define USB_ASYN_PK_CNT_SHIFT (8U)
#define USB_ASYN_PK_CNT_MASK  (0x3 << USB_ASYN_PK_CNT_SHIFT)
#define USB_ASYN_PK_EN        (1 << 11U)
#define USB_INT_THRC_SHIFT    (16U)
#define USB_INT_THRC_MASK     (0xff << USB_INT_THRC_SHIFT)

/* 0x14 : USBSTS */
#define USB_INT         (1 << 0U)
#define USBERR_INT      (1 << 1U)
#define USB_PO_CHG_DET  (1 << 2U)
#define USB_FRL_ROL     (1 << 3U)
#define USB_H_SYSERR    (1 << 4U)
#define USB_INT_OAA     (1 << 5U)
#define USB_HCHALTED    (1 << 12U)
#define USB_RECLAMATION (1 << 13U)
#define USB_PSCH_STS    (1 << 14U)
#define USB_ASCH_STS    (1 << 15U)

/* 0x18 : USBINTR */
#define USB_INT_EN        (1 << 0U)
#define USBERR_INT_EN     (1 << 1U)
#define USB_PO_CHG_INT_EN (1 << 2U)
#define USB_FRL_ROL_EN    (1 << 3U)
#define USB_H_SYSERR_EN   (1 << 4U)
#define USB_INT_OAA_EN    (1 << 5U)

/* 0x1C : FRINDEX */
#define USB_FRINDEX_SHIFT (0U)
#define USB_FRINDEX_MASK  (0x3fff << USB_FRINDEX_SHIFT)

/* 0x24 : PERIODICLISTBASE */
#define USB_PERI_BASADR_SHIFT (12U)
#define USB_PERI_BASADR_MASK  (0xfffff << USB_PERI_BASADR_SHIFT)

/* 0x28 : ASYNCLISTADDR */
#define USB_ASYNC_LADR_SHIFT (5U)
#define USB_ASYNC_LADR_MASK  (0x7fffff << USB_ASYNC_LADR_SHIFT)

/* 0x30 : PORTSC */
#define USB_CONN_STS        (1 << 0U)
#define USB_CONN_CHG        (1 << 1U)
#define USB_PO_EN           (1 << 2U)
#define USB_PO_EN_CHG       (1 << 3U)
#define USB_F_PO_RESM       (1 << 6U)
#define USB_PO_SUSP         (1 << 7U)
#define USB_PO_RESET        (1 << 8U)
#define USB_LINE_STS_SHIFT  (10U)
#define USB_LINE_STS_MASK   (0x3 << USB_LINE_STS_SHIFT)
#define USB_PORT_TEST_SHIFT (16U)
#define USB_PORT_TEST_MASK  (0xf << USB_PORT_TEST_SHIFT)
#define USB_HC_TST_PKDONE   (1 << 20U)

/* 0x40 : HCMISC */
#define USB_ASYN_SCH_SLPT_SHIFT (0U)
#define USB_ASYN_SCH_SLPT_MASK  (0x3 << USB_ASYN_SCH_SLPT_SHIFT)
#define USB_EOF1_TIME_SHIFT     (2U)
#define USB_EOF1_TIME_MASK      (0x3 << USB_EOF1_TIME_SHIFT)
#define USB_EOF2_TIME_SHIFT     (4U)
#define USB_EOF2_TIME_MASK      (0x3 << USB_EOF2_TIME_SHIFT)
#define USB_HOSTPHY_SUSPEND     (1 << 6U)
#define USB_HC_WKP_DET_EN       (1 << 8U)
#define USB_HC_CONN_DET_EN      (1 << 9U)

/* 0x44 : FS_EOF */
#define USB_FS_EOF1_TIME_SHIFT       (0U)
#define USB_FS_EOF1_TIME_MASK        (0xfff << USB_FS_EOF1_TIME_SHIFT)
#define USB_FS_EOF1_TIME_125US_SHIFT (12U)
#define USB_FS_EOF1_TIME_125US_MASK  (0x7 << USB_FS_EOF1_TIME_125US_SHIFT)
#define USB_ITDDMASM_SHIFT           (16U)
#define USB_ITDDMASM_MASK            (0xf << USB_ITDDMASM_SHIFT)
#define USB_ITDTRAVSM_SHIFT          (20U)
#define USB_ITDTRAVSM_MASK           (0x3 << USB_ITDTRAVSM_SHIFT)
#define USB_DMADMSM_SHIFT            (22U)
#define USB_DMADMSM_MASK             (0xf << USB_DMADMSM_SHIFT)
#define USB_QHTTRSM_SHIFT            (26U)
#define USB_QHTTRSM_MASK             (0x7 << USB_QHTTRSM_SHIFT)
#define USB_QHTRAVSM_SHIFT           (29U)
#define USB_QHTRAVSM_MASK            (0x7 << USB_QHTRAVSM_SHIFT)

/* 0x48 : HS_EOF */
#define USB_HS_EOF1_TIME_SHIFT       (0U)
#define USB_HS_EOF1_TIME_MASK        (0xfff << USB_HS_EOF1_TIME_SHIFT)
#define USB_FS_EOF1_TIME_125US_SHIFT (12U)
#define USB_FS_EOF1_TIME_125US_MASK  (0x7 << USB_FS_EOF1_TIME_125US_SHIFT)
#define USB_SITDDMASM_SHIFT          (16U)
#define USB_SITDDMASM_MASK           (0xf << USB_SITDDMASM_SHIFT)
#define USB_SITDTRAVSM_SHIFT         (20U)
#define USB_SITDTRAVSM_MASK          (0x3 << USB_SITDTRAVSM_SHIFT)

/* 0x80 : OTG_CSR */
#define USB_B_BUS_REQ             (1 << 0U)
#define USB_B_HNP_EN              (1 << 1U)
#define USB_B_DSCHRG_VBUS         (1 << 2U)
#define USB_A_BUS_REQ_HOV         (1 << 4U)
#define USB_A_BUS_DROP_HOV        (1 << 5U)
#define USB_A_SET_B_HNP_EN        (1 << 6U)
#define USB_A_SRP_DET_EN          (1 << 7U)
#define USB_A_SRP_RESP_TYP        (1 << 8U)
#define USB_ID_FLT_SEL            (1 << 9U)
#define USB_VBUS_FLT_SEL_HOV_POV  (1 << 10U)
#define USB_HDISCON_FLT_SEL_HOV   (1 << 11U)
#define USB_IDPULUP_HOV_POV       (1 << 13U)
#define USB_B_SESS_END_POV        (1 << 16U)
#define USB_B_SESS_VLD_POV        (1 << 17U)
#define USB_A_SESS_VLD            (1 << 18U)
#define USB_VBUS_VLD_HOV          (1 << 19U)
#define USB_CROLE_HOV_POV         (1 << 20U)
#define USB_ID_HOV_POV            (1 << 21U)
#define USB_SPD_TYP_HOV_POV_SHIFT (22U)
#define USB_SPD_TYP_HOV_POV_MASK  (0x3 << USB_SPD_TYP_HOV_POV_SHIFT)

/* 0x84 : OTG_ISR */
#define USB_B_SRP_DN           (1 << 0U)
#define USB_A_SRP_DET          (1 << 4U)
#define USB_A_VBUS_ERR_HOV     (1 << 5U)
#define USB_B_SESS_END_INT_POV (1 << 6U)
#define USB_RLCHG              (1 << 8U)
#define USB_IDCHG              (1 << 9U)
#define USB_OVC_HOV            (1 << 10U)
#define USB_A_WAIT_CON_HOV     (1 << 11U)
#define USB_APLGRMV            (1 << 12U)

/* 0x88 : OTG_IER */
#define USB_B_SRP_DN_EN       (1 << 0U)
#define USB_A_SRP_DET_INT_EN  (1 << 4U)
#define USB_A_VBUS_ERR_EN_HOV (1 << 5U)
#define USB_B_SESS_END_EN_POV (1 << 6U)
#define USB_RLCHG_EN          (1 << 8U)
#define USB_IDCHG_EN          (1 << 9U)
#define USB_OVC_EN_HOV        (1 << 10U)
#define USB_A_WAIT_CON_EN_HOV (1 << 11U)
#define USB_APLGRMV_EN        (1 << 12U)

/* 0xC0 : GLB_ISR */
#define USB_DEV_INT (1 << 0U)
#define USB_OTG_INT (1 << 1U)
#define USB_HC_INT  (1 << 2U)

/* 0xC4 : GLB_INT */
#define USB_MDEV_INT (1 << 0U)
#define USB_MOTG_INT (1 << 1U)
#define USB_MHC_INT  (1 << 2U)

/* 0xE0 : REVISION */
#define USB_REVISION_SHIFT (0U)
#define USB_REVISION_MASK  (0xffffffff << USB_REVISION_SHIFT)

/* 0xE4 : FEATURE */
#define USB_DMABUFSIZE_SHIFT (0U)
#define USB_DMABUFSIZE_MASK  (0x1f << USB_DMABUFSIZE_SHIFT)
#define USB_FIFO_NUM_SHIFT   (5U)
#define USB_FIFO_NUM_MASK    (0x1f << USB_FIFO_NUM_SHIFT)
#define USB_EP_NUM_SHIFT     (10U)
#define USB_EP_NUM_MASK      (0x1f << USB_EP_NUM_SHIFT)
#define USB_DEV_ONLY         (1 << 15U)
#define USB_HOST_ONLY        (1 << 16U)

/* 0xE8 : AXI_CR */
#define USB_AXI_SGLBST (1 << 0U)

/* 0x100 : DEV_CTL */
#define USB_CAP_RMWAKUP        (1 << 0U)
#define USB_HALF_SPEED_HOV     (1 << 1U)
#define USB_GLINT_EN_HOV       (1 << 2U)
#define USB_GOSUSP             (1 << 3U)
#define USB_SFRST_HOV          (1 << 4U)
#define USB_CHIP_EN_HOV        (1 << 5U)
#define USB_HS_EN_HOV          (1 << 6U)
#define USB_SYSBUS_WIDTH_HOV   (1 << 7U)
#define USB_FORCE_FS           (1 << 9U)
#define USB_IDLE_DEGLITCH_HOV  (1 << 10U)
#define USB_LPM_BESL_MAX_SHIFT (12U)
#define USB_LPM_BESL_MAX_MASK  (0xf << USB_LPM_BESL_MAX_SHIFT)
#define USB_LPM_BESL_MIN_SHIFT (16U)
#define USB_LPM_BESL_MIN_MASK  (0xf << USB_LPM_BESL_MIN_SHIFT)
#define USB_LPM_BESL_SHIFT     (20U)
#define USB_LPM_BESL_MASK      (0xf << USB_LPM_BESL_SHIFT)
#define USB_LPM_EN             (1 << 25U)
#define USB_LPM_ACCEPT         (1 << 26U)

/* 0x104 : DEV_ADR */
#define USB_DEVADR_SHIFT (0U)
#define USB_DEVADR_MASK  (0x7f << USB_DEVADR_SHIFT)
#define USB_AFT_CONF     (1 << 7U)

/* 0x108 : DEV_TST */
#define USB_TST_CLRFF_HOV   (1 << 0U)
#define USB_TST_LPCX        (1 << 1U)
#define USB_TST_CLREA       (1 << 2U)
#define USB_TST_DISTO_HOV   (1 << 4U)
#define USB_TST_MOD_HOV     (1 << 5U)
#define USB_DISGENSOF       (1 << 6U)
#define USB_TST_MOD_TYP_HOV (1 << 7U)

/* 0x10C : DEV_SFN */
#define USB_SOFN_SHIFT  (0U)
#define USB_SOFN_MASK   (0x7ff << USB_SOFN_SHIFT)
#define USB_USOFN_SHIFT (11U)
#define USB_USOFN_MASK  (0x7 << USB_USOFN_SHIFT)

/* 0x110 : DEV_SMT */
#define USB_SOFMT_SHIFT (0U)
#define USB_SOFMT_MASK  (0xffff << USB_SOFMT_SHIFT)

/* 0x114 : PHY_TST */
#define USB_UNPLUG     (1 << 0U)
#define USB_TST_JSTA   (1 << 1U)
#define USB_TST_KSTA   (1 << 2U)
#define USB_TST_SE0NAK (1 << 3U)
#define USB_TST_PKT    (1 << 4U)

/* 0x11C : DEV_CXCFG */
#define USB_VSTA_HOV_SHIFT (0U)
#define USB_VSTA_HOV_MASK  (0xff << USB_VSTA_HOV_SHIFT)

/* 0x120 : DEV_CXCFE */
#define USB_CX_DONE    (1 << 0U)
#define USB_TST_PKDONE (1 << 1U)
#define USB_CX_STL     (1 << 2U)
#define USB_CX_CLR     (1 << 3U)
#define USB_CX_FUL     (1 << 4U)
#define USB_CX_EMP     (1 << 5U)
#define USB_F0_EMP     (1 << 8U)
#define USB_F1_EMP     (1 << 9U)
#define USB_F2_EMP     (1 << 10U)
#define USB_F3_EMP     (1 << 11U)

/* 0x124 : DEV_ICR */
#define USB_IDLE_CNT_SHIFT (0U)
#define USB_IDLE_CNT_MASK  (0x7 << USB_IDLE_CNT_SHIFT)

/* 0x130 : DEV_MIGR */
#define USB_MINT_G0 (1 << 0U)
#define USB_MINT_G1 (1 << 1U)
#define USB_MINT_G2 (1 << 2U)
#define USB_MINT_G3 (1 << 3U)
#define USB_MINT_G4 (1 << 4U)

/* 0x134 : DEV_MISG0 */
#define USB_MCX_SETUP_INT    (1 << 0U)
#define USB_MCX_IN_INT       (1 << 1U)
#define USB_MCX_OUT_INT      (1 << 2U)
#define USB_MCX_COMFAIL_INT  (1 << 4U)
#define USB_MCX_COMABORT_INT (1 << 5U)

/* 0x138 : DEV_MISG1 */
#define USB_MF0_OUT_INT (1 << 0U)
#define USB_MF0_SPK_INT (1 << 1U)
#define USB_MF1_OUT_INT (1 << 2U)
#define USB_MF1_SPK_INT (1 << 3U)
#define USB_MF2_OUT_INT (1 << 4U)
#define USB_MF2_SPK_INT (1 << 5U)
#define USB_MF3_OUT_INT (1 << 6U)
#define USB_MF3_SPK_INT (1 << 7U)
#define USB_MF0_IN_INT  (1 << 16U)
#define USB_MF1_IN_INT  (1 << 17U)
#define USB_MF2_IN_INT  (1 << 18U)
#define USB_MF3_IN_INT  (1 << 19U)

/* 0x13C : DEV_MISG2 */
#define USB_MUSBRST_INT        (1 << 0U)
#define USB_MSUSP_INT          (1 << 1U)
#define USB_MRESM_INT          (1 << 2U)
#define USB_MSEQ_ERR_INT       (1 << 3U)
#define USB_MSEQ_ABORT_INT     (1 << 4U)
#define USB_MTX0BYTE_INT       (1 << 5U)
#define USB_MRX0BYTE_INT       (1 << 6U)
#define USB_MDMA_CMPLT_HOV     (1 << 7U)
#define USB_MDMA_ERROR_HOV     (1 << 8U)
#define USB_MDEV_IDLE_HOV      (1 << 9U)
#define USB_MDEV_WAKEUP_BYVBUS (1 << 10U)

/* 0x140 : DEV_IGR */
#define USB_INT_G0 (1 << 0U)
#define USB_INT_G1 (1 << 1U)
#define USB_INT_G2 (1 << 2U)
#define USB_INT_G3 (1 << 3U)
#define USB_INT_G4 (1 << 4U)

/* 0x144 : DEV_ISG0 */
#define USB_CX_SETUP_INT   (1 << 0U)
#define USB_CX_IN_INT      (1 << 1U)
#define USB_CX_OUT_INT     (1 << 2U)
#define USB_CX_COMFAIL_INT (1 << 4U)
#define USB_CX_COMABT_INT  (1 << 5U)

/* 0x148 : DEV_ISG1 */
#define USB_F0_OUT_INT (1 << 0U)
#define USB_F0_SPK_INT (1 << 1U)
#define USB_F1_OUT_INT (1 << 2U)
#define USB_F1_SPK_INT (1 << 3U)
#define USB_F2_OUT_INT (1 << 4U)
#define USB_F2_SPK_INT (1 << 5U)
#define USB_F3_OUT_INT (1 << 6U)
#define USB_F3_SPK_INT (1 << 7U)
#define USB_F0_IN_INT  (1 << 16U)
#define USB_F1_IN_INT  (1 << 17U)
#define USB_F2_IN_INT  (1 << 18U)
#define USB_F3_IN_INT  (1 << 19U)

/* 0x14C : DEV_ISG2 */
#define USBRST_INT            (1 << 0U)
#define USB_SUSP_INT          (1 << 1U)
#define USB_RESM_INT          (1 << 2U)
#define USB_ISO_SEQ_ERR_INT   (1 << 3U)
#define USB_ISO_SEQ_ABORT_INT (1 << 4U)
#define USB_TX0BYTE_INT       (1 << 5U)
#define USB_RX0BYTE_INT       (1 << 6U)
#define USB_DMA_CMPLT_HOV     (1 << 7U)
#define USB_DMA_ERROR_HOV     (1 << 8U)
#define USB_DEV_IDLE_HOV      (1 << 9U)
#define USB_DEV_WAKEUP_BYVBUS (1 << 10U)

/* 0x150 : DEV_RXZ */
#define USB_RX0BYTE_EP1 (1 << 0U)
#define USB_RX0BYTE_EP2 (1 << 1U)
#define USB_RX0BYTE_EP3 (1 << 2U)
#define USB_RX0BYTE_EP4 (1 << 3U)

/* 0x154 : DEV_TXZ */
#define USB_TX0BYTE_EP1 (1 << 0U)
#define USB_TX0BYTE_EP2 (1 << 1U)
#define USB_TX0BYTE_EP3 (1 << 2U)
#define USB_TX0BYTE_EP4 (1 << 3U)

/* 0x158 : DEV_ISE */
#define USB_ISO_ABT_ERR_EP1 (1 << 0U)
#define USB_ISO_ABT_ERR_EP2 (1 << 1U)
#define USB_ISO_ABT_ERR_EP3 (1 << 2U)
#define USB_ISO_ABT_ERR_EP4 (1 << 3U)
#define USB_ISO_SEQ_ERR_EP1 (1 << 16U)
#define USB_ISO_SEQ_ERR_EP2 (1 << 17U)
#define USB_ISO_SEQ_ERR_EP3 (1 << 18U)
#define USB_ISO_SEQ_ERR_EP4 (1 << 19U)

/* 0x160 : DEV_INMPS1 */
#define USB_MAXPS_IEP1_SHIFT      (0U)
#define USB_MAXPS_IEP1_MASK       (0x7ff << USB_MAXPS_IEP1_SHIFT)
#define USB_STL_IEP1              (1 << 11U)
#define USB_RSTG_IEP1             (1 << 12U)
#define USB_TX_NUM_HBW_IEP1_SHIFT (13U)
#define USB_TX_NUM_HBW_IEP1_MASK  (0x3 << USB_TX_NUM_HBW_IEP1_SHIFT)
#define USB_TX0BYTE_IEP1          (1 << 15U)

/* 0x164 : DEV_INMPS2 */
/* 0x168 : DEV_INMPS3 */
/* 0x16C : DEV_INMPS4 */
/* 0x170 : DEV_INMPS5 */
/* 0x174 : DEV_INMPS6 */
/* 0x178 : DEV_INMPS7 */
/* 0x17C : DEV_INMPS8 */

/* 0x180 : DEV_OUTMPS1 */
#define USB_MAXPS_OEP1_SHIFT (0U)
#define USB_MAXPS_OEP1_MASK  (0x7ff << USB_MAXPS_OEP1_SHIFT)
#define USB_STL_OEP1         (1 << 11U)
#define USB_RSTG_OEP1        (1 << 12U)

/* 0x184 : DEV_OUTMPS2 */
/* 0x188 : DEV_OUTMPS3 */
/* 0x18C : DEV_OUTMPS4 */
/* 0x190 : DEV_OUTMPS5 */
/* 0x194 : DEV_OUTMPS6 */
/* 0x198 : DEV_OUTMPS7 */
/* 0x19C : DEV_OUTMPS8 */

/* 0x1A0 : DEV_EPMAP0 */
#define USB_FNO_IEP1_SHIFT (0U)
#define USB_FNO_IEP1_MASK  (0xf << USB_FNO_IEP1_SHIFT)
#define USB_FNO_OEP1_SHIFT (4U)
#define USB_FNO_OEP1_MASK  (0xf << USB_FNO_OEP1_SHIFT)
#define USB_FNO_IEP2_SHIFT (8U)
#define USB_FNO_IEP2_MASK  (0xf << USB_FNO_IEP2_SHIFT)
#define USB_FNO_OEP2_SHIFT (12U)
#define USB_FNO_OEP2_MASK  (0xf << USB_FNO_OEP2_SHIFT)
#define USB_FNO_IEP3_SHIFT (16U)
#define USB_FNO_IEP3_MASK  (0xf << USB_FNO_IEP3_SHIFT)
#define USB_FNO_OEP3_SHIFT (20U)
#define USB_FNO_OEP3_MASK  (0xf << USB_FNO_OEP3_SHIFT)
#define USB_FNO_IEP4_SHIFT (24U)
#define USB_FNO_IEP4_MASK  (0xf << USB_FNO_IEP4_SHIFT)
#define USB_FNO_OEP4_SHIFT (28U)
#define USB_FNO_OEP4_MASK  (0xf << USB_FNO_OEP4_SHIFT)

/* 0x1A4 : DEV_EPMAP1 */

/* 0x1A8 : DEV_FMAP */
#define USB_EPNO_FIFO0_SHIFT (0U)
#define USB_EPNO_FIFO0_MASK  (0xf << USB_EPNO_FIFO0_SHIFT)
#define USB_DIR_FIFO0_SHIFT  (4U)
#define USB_DIR_FIFO0_MASK   (0x3 << USB_DIR_FIFO0_SHIFT)
#define USB_EPNO_FIFO1_SHIFT (8U)
#define USB_EPNO_FIFO1_MASK  (0xf << USB_EPNO_FIFO1_SHIFT)
#define USB_DIR_FIFO1_SHIFT  (12U)
#define USB_DIR_FIFO1_MASK   (0x3 << USB_DIR_FIFO1_SHIFT)
#define USB_EPNO_FIFO2_SHIFT (16U)
#define USB_EPNO_FIFO2_MASK  (0xf << USB_EPNO_FIFO2_SHIFT)
#define USB_DIR_FIFO2_SHIFT  (20U)
#define USB_DIR_FIFO2_MASK   (0x3 << USB_DIR_FIFO2_SHIFT)
#define USB_EPNO_FIFO3_SHIFT (24U)
#define USB_EPNO_FIFO3_MASK  (0xf << USB_EPNO_FIFO3_SHIFT)
#define USB_DIR_FIFO3_SHIFT  (28U)
#define USB_DIR_FIFO3_MASK   (0x3 << USB_DIR_FIFO3_SHIFT)

/* 0x1AC : DEV_FCFG */
#define USB_BLK_TYP_F0_SHIFT (0U)
#define USB_BLK_TYP_F0_MASK  (0x3 << USB_BLK_TYP_F0_SHIFT)
#define USB_BLKNO_F0_SHIFT   (2U)
#define USB_BLKNO_F0_MASK    (0x3 << USB_BLKNO_F0_SHIFT)
#define USB_BLKSZ_F0         (1 << 4U)
#define USB_EN_F0            (1 << 5U)
#define USB_BLK_TYP_F1_SHIFT (8U)
#define USB_BLK_TYP_F1_MASK  (0x3 << USB_BLK_TYP_F1_SHIFT)
#define USB_BLKNO_F1_SHIFT   (10U)
#define USB_BLKNO_F1_MASK    (0x3 << USB_BLKNO_F1_SHIFT)
#define USB_BLKSZ_F1         (1 << 12U)
#define USB_EN_F1            (1 << 13U)
#define USB_BLK_TYP_F2_SHIFT (16U)
#define USB_BLK_TYP_F2_MASK  (0x3 << USB_BLK_TYP_F2_SHIFT)
#define USB_BLKNO_F2_SHIFT   (18U)
#define USB_BLKNO_F2_MASK    (0x3 << USB_BLKNO_F2_SHIFT)
#define USB_BLKSZ_F2         (1 << 20U)
#define USB_EN_F2            (1 << 21U)
#define USB_BLK_TYP_F3_SHIFT (24U)
#define USB_BLK_TYP_F3_MASK  (0x3 << USB_BLK_TYP_F3_SHIFT)
#define USB_BLKNO_F3_SHIFT   (26U)
#define USB_BLKNO_F3_MASK    (0x3 << USB_BLKNO_F3_SHIFT)
#define USB_BLKSZ_F3         (1 << 28U)
#define USB_EN_F3            (1 << 29U)

/* 0x1B0 : DEV_FIBC0 */
#define USB_BC_F0_SHIFT (0U)
#define USB_BC_F0_MASK  (0x7ff << USB_BC_F0_SHIFT)
#define USB_FFRST0_HOV  (1 << 12U)

/* 0x1B4 : DEV_FIBC1 */
/* 0x1B8 : DEV_FIBC2 */
/* 0x1BC : DEV_FIBC3 */

/* 0x1C0 : DMA_TFN */
#define USB_ACC_F0_HOV  (1 << 0U)
#define USB_ACC_F1_HOV  (1 << 1U)
#define USB_ACC_F2_HOV  (1 << 2U)
#define USB_ACC_F3_HOV  (1 << 3U)
#define USB_ACC_CXF_HOV (1 << 4U)

/* 0x1C4 : DMA_CPS0 */
#define USB_AWCHACHE_HOV_SHIFT (0U)
#define USB_AWCHACHE_HOV_MASK  (0xf << USB_AWCHACHE_HOV_SHIFT)
#define USB_AWPORT_HOV_SHIFT   (4U)
#define USB_AWPORT_HOV_MASK    (0x7 << USB_AWPORT_HOV_SHIFT)
#define USB_AWLOCK_HOV_SHIFT   (7U)
#define USB_AWLOCK_HOV_MASK    (0x3 << USB_AWLOCK_HOV_SHIFT)
#define USB_ARCACHE_HOV_SHIFT  (9U)
#define USB_ARCACHE_HOV_MASK   (0xf << USB_ARCACHE_HOV_SHIFT)
#define USB_ARPORT_HOV_SHIFT   (13U)
#define USB_ARPORT_HOV_MASK    (0x7 << USB_ARPORT_HOV_SHIFT)
#define USB_ARLOCK_HOV_SHIFT   (16U)
#define USB_ARLOCK_HOV_MASK    (0x3 << USB_ARLOCK_HOV_SHIFT)
#define USB_BUF_LD_EN_HOV      (1 << 18U)
#define USB_DST_WD_HOV         (1 << 19U)

/* 0x1C8 : DMA_CPS1 */
#define USB_DMA_START_HOV        (1 << 0U)
#define USB_DMA_TYPE_HOV         (1 << 1U)
#define USB_DMA_IO_HOV           (1 << 2U)
#define USB_DMA_ABORT_HOV        (1 << 3U)
#define USB_CLRFIFO_DMAABORT_HOV (1 << 4U)
#define USB_DMA_LEN_HOV_SHIFT    (8U)
#define USB_DMA_LEN_HOV_MASK     (0x1ffff << USB_DMA_LEN_HOV_SHIFT)
#define USB_R_HPORT_HOV_SHIFT    (25U)
#define USB_R_HPORT_HOV_MASK     (0xf << USB_R_HPORT_HOV_SHIFT)
#define USB_UNDEF_LEN_BURST_HOV  (1 << 29U)
#define USB_L1_WAKEUP            (1 << 30U)
#define USB_DEVPHY_SUSPEND_HOV   (1 << 31U)

/* 0x1CC : DMA_CPS2 */
#define USB_DMA_MADDR_HOV_SHIFT (0U)
#define USB_DMA_MADDR_HOV_MASK  (0xffffffff << USB_DMA_MADDR_HOV_SHIFT)

/* 0x1D0 : DMA_CPS3 */
#define USB_SETUP_CMD_RPORT_SHIFT (0U)
#define USB_SETUP_CMD_RPORT_MASK  (0xffffffff << USB_SETUP_CMD_RPORT_SHIFT)

/* 0x1D4 : DMA_CPS4 */
/* 0x1D8 : DEV_FMAP2 */
/* 0x1DC : DEV_FCFG2 */
/* 0x1E0 : DEV_FMAP3 */
/* 0x1E4 : DEV_FCFG3 */
/* 0x1E8 : DEV_FMAP4 */
/* 0x1EC : DEV_FCFG4 */
/* 0x1F0 : DEV_FIBC4 */
/* 0x1F4 : DEV_FIBC5 */
/* 0x1F8 : DEV_FIBC6 */
/* 0x1FC : DEV_FIBC7 */

/* 0x300 : VDMA_CXFPS1 */
#define USB_VDMA_START_CXF     (1 << 0U)
#define USB_VDMA_TYPE_CXF      (1 << 1U)
#define USB_VDMA_IO_CXF        (1 << 2U)
#define USB_VDMA_LEN_CXF_SHIFT (8U)
#define USB_VDMA_LEN_CXF_MASK  (0x1ffff << USB_VDMA_LEN_CXF_SHIFT)

/* 0x304 : VDMA_CXFPS2 */
#define USB_VDMA_MADDR_CXF_SHIFT (8U)
#define USB_VDMA_MADDR_CXF_MASK  (0x1ffff << USB_VDMA_MADDR_CXF_SHIFT)

/* 0x308 : VDMA_F0PS1 */
#define USB_VDMA_START_F0     (1 << 0U)
#define USB_VDMA_TYPE_F0      (1 << 1U)
#define USB_VDMA_IO_F0        (1 << 2U)
#define USB_VDMA_LEN_F0_SHIFT (8U)
#define USB_VDMA_LEN_F0_MASK  (0x1ffff << USB_VDMA_LEN_F0_SHIFT)

/* 0x30c : VDMA_F0PS2 */
#define USB_VDMA_MADDR_F0_SHIFT (8U)
#define USB_VDMA_MADDR_F0_MASK  (0x1ffff << USB_VDMA_MADDR_F0_SHIFT)

/* 0x310 : VDMA_F1PS1 */
/* 0x314 : VDMA_F1PS2 */
/* 0x318 : VDMA_F2PS1 */
/* 0x31C : VDMA_F2PS2 */
/* 0x320 : VDMA_F3PS1 */
/* 0x324 : VDMA_F3PS2 */

/* 0x328 : DEV_ISG3 */
#define USB_VDMA_CMPLT_CXF (1 << 0U)
#define USB_VDMA_CMPLT_F0  (1 << 1U)
#define USB_VDMA_CMPLT_F1  (1 << 2U)
#define USB_VDMA_CMPLT_F2  (1 << 3U)
#define USB_VDMA_CMPLT_F3  (1 << 4U)
#define USB_VDMA_ERROR_CXF (1 << 16U)
#define USB_VDMA_ERROR_F0  (1 << 17U)
#define USB_VDMA_ERROR_F1  (1 << 18U)
#define USB_VDMA_ERROR_F2  (1 << 19U)
#define USB_VDMA_ERROR_F3  (1 << 20U)

/* 0x32C : DEV_MISG3 */
#define USB_MVDMA_CMPLT_CXF (1 << 0U)
#define USB_MVDMA_CMPLT_F0  (1 << 1U)
#define USB_MVDMA_CMPLT_F1  (1 << 2U)
#define USB_MVDMA_CMPLT_F2  (1 << 3U)
#define USB_MVDMA_CMPLT_F3  (1 << 4U)
#define USB_MVDMA_ERROR_CXF (1 << 16U)
#define USB_MVDMA_ERROR_F0  (1 << 17U)
#define USB_MVDMA_ERROR_F1  (1 << 18U)
#define USB_MVDMA_ERROR_F2  (1 << 19U)
#define USB_MVDMA_ERROR_F3  (1 << 20U)

/* 0x330 : VDMA_CTRL */
#define USB_VDMA_EN (1 << 0U)

/* 0x334 : LPM_CAP */
#define USB_LPM_WAKEUP_EN (1 << 0U)

/* 0x338 : DEV_ISG4 */
#define USB_L1_INT (1 << 0U)

/* 0x33C : DEV_MISG4 */
#define USB_ML1_INT (1 << 0U)

/* 0x350 : VDMA_FnPS1 */
/* 0x354 : VDMA_FnPS2 */

#endif /* __HARDWARE_USB_V2_H__ */
