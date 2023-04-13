/**
  ******************************************************************************
  * @file    usb_v1_reg.h
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
#ifndef __HARDWARE_USB_V1_H__
#define __HARDWARE_USB_V1_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define USB_CONFIG_OFFSET            (0x0)   /* usb_config */
#define USB_LPM_CONFIG_OFFSET        (0x4)   /* usb_lpm_config */
#define USB_RESUME_CONFIG_OFFSET     (0x8)   /* usb_resume_config */
#define USB_SETUP_DATA_0_OFFSET      (0x10)  /* usb_setup_data_0 */
#define USB_SETUP_DATA_1_OFFSET      (0x14)  /* usb_setup_data_1 */
#define USB_FRAME_NO_OFFSET          (0x18)  /* usb_frame_no */
#define USB_ERROR_OFFSET             (0x1C)  /* usb_error */
#define USB_INT_EN_OFFSET            (0x20)  /* USB interrupt enable */
#define USB_INT_STS_OFFSET           (0x24)  /* USB interrupt status */
#define USB_INT_MASK_OFFSET          (0x28)  /* USB interrupt mask */
#define USB_INT_CLEAR_OFFSET         (0x2C)  /* USB interrupt clear */
#define USB_EP1_CONFIG_OFFSET        (0x40)  /* ep1_config */
#define USB_EP2_CONFIG_OFFSET        (0x44)  /* ep2_config */
#define USB_EP3_CONFIG_OFFSET        (0x48)  /* ep3_config */
#define USB_EP4_CONFIG_OFFSET        (0x4C)  /* ep4_config */
#define USB_EP5_CONFIG_OFFSET        (0x50)  /* ep5_config */
#define USB_EP6_CONFIG_OFFSET        (0x54)  /* ep6_config */
#define USB_EP7_CONFIG_OFFSET        (0x58)  /* ep7_config */
#define USB_EP0_FIFO_CONFIG_OFFSET   (0x100) /* ep0_fifo_config */
#define USB_EP0_FIFO_STATUS_OFFSET   (0x104) /* ep0_fifo_status */
#define USB_EP0_TX_FIFO_WDATA_OFFSET (0x108) /* ep0_tx_fifo_wdata */
#define USB_EP0_RX_FIFO_RDATA_OFFSET (0x10C) /* ep0_rx_fifo_rdata */
#define USB_EP1_FIFO_CONFIG_OFFSET   (0x110) /* ep1_fifo_config */
#define USB_EP1_FIFO_STATUS_OFFSET   (0x114) /* ep1_fifo_status */
#define USB_EP1_TX_FIFO_WDATA_OFFSET (0x118) /* ep1_tx_fifo_wdata */
#define USB_EP1_RX_FIFO_RDATA_OFFSET (0x11C) /* ep1_rx_fifo_rdata */
#define USB_EP2_FIFO_CONFIG_OFFSET   (0x120) /* ep2_fifo_config */
#define USB_EP2_FIFO_STATUS_OFFSET   (0x124) /* ep2_fifo_status */
#define USB_EP2_TX_FIFO_WDATA_OFFSET (0x128) /* ep2_tx_fifo_wdata */
#define USB_EP2_RX_FIFO_RDATA_OFFSET (0x12C) /* ep2_rx_fifo_rdata */
#define USB_EP3_FIFO_CONFIG_OFFSET   (0x130) /* ep3_fifo_config */
#define USB_EP3_FIFO_STATUS_OFFSET   (0x134) /* ep3_fifo_status */
#define USB_EP3_TX_FIFO_WDATA_OFFSET (0x138) /* ep3_tx_fifo_wdata */
#define USB_EP3_RX_FIFO_RDATA_OFFSET (0x13C) /* ep3_rx_fifo_rdata */
#define USB_EP4_FIFO_CONFIG_OFFSET   (0x140) /* ep4_fifo_config */
#define USB_EP4_FIFO_STATUS_OFFSET   (0x144) /* ep4_fifo_status */
#define USB_EP4_TX_FIFO_WDATA_OFFSET (0x148) /* ep4_tx_fifo_wdata */
#define USB_EP4_RX_FIFO_RDATA_OFFSET (0x14C) /* ep4_rx_fifo_rdata */
#define USB_EP5_FIFO_CONFIG_OFFSET   (0x150) /* ep5_fifo_config */
#define USB_EP5_FIFO_STATUS_OFFSET   (0x154) /* ep5_fifo_status */
#define USB_EP5_TX_FIFO_WDATA_OFFSET (0x158) /* ep5_tx_fifo_wdata */
#define USB_EP5_RX_FIFO_RDATA_OFFSET (0x15C) /* ep5_rx_fifo_rdata */
#define USB_EP6_FIFO_CONFIG_OFFSET   (0x160) /* ep6_fifo_config */
#define USB_EP6_FIFO_STATUS_OFFSET   (0x164) /* ep6_fifo_status */
#define USB_EP6_TX_FIFO_WDATA_OFFSET (0x168) /* ep6_tx_fifo_wdata */
#define USB_EP6_RX_FIFO_RDATA_OFFSET (0x16C) /* ep6_rx_fifo_rdata */
#define USB_EP7_FIFO_CONFIG_OFFSET   (0x170) /* ep7_fifo_config */
#define USB_EP7_FIFO_STATUS_OFFSET   (0x174) /* ep7_fifo_status */
#define USB_EP7_TX_FIFO_WDATA_OFFSET (0x178) /* ep7_tx_fifo_wdata */
#define USB_EP7_RX_FIFO_RDATA_OFFSET (0x17C) /* ep7_rx_fifo_rdata */
#define USB_RSVD_0_OFFSET            (0x1F0) /* rsvd_0 */
#define USB_RSVD_1_OFFSET            (0x1F4) /* rsvd_1 */
#define USB_XCVR_IF_CONFIG_OFFSET    (0x1FC) /* xcvr_if_config */

/* Register Bitfield definitions *****************************************************/

/* 0x0 : usb_config */
#define USB_CR_USB_EN                (1 << 0U)
#define USB_CR_USB_ROM_DCT_EN        (1 << 4U)
#define USB_CR_USB_EP0_SW_CTRL       (1 << 8U)
#define USB_CR_USB_EP0_SW_ADDR_SHIFT (9U)
#define USB_CR_USB_EP0_SW_ADDR_MASK  (0x7f << USB_CR_USB_EP0_SW_ADDR_SHIFT)
#define USB_CR_USB_EP0_SW_SIZE_SHIFT (16U)
#define USB_CR_USB_EP0_SW_SIZE_MASK  (0xff << USB_CR_USB_EP0_SW_SIZE_SHIFT)
#define USB_CR_USB_EP0_SW_STALL      (1 << 24U)
#define USB_CR_USB_EP0_SW_NACK_IN    (1 << 25U)
#define USB_CR_USB_EP0_SW_NACK_OUT   (1 << 26U)
#define USB_CR_USB_EP0_SW_RDY        (1 << 27U)
#define USB_STS_USB_EP0_SW_RDY       (1 << 28U)

/* 0x4 : usb_lpm_config */
#define USB_CR_LPM_EN          (1 << 0U)
#define USB_CR_LPM_RESP_UPD    (1 << 1U)
#define USB_CR_LPM_RESP_SHIFT  (2U)
#define USB_CR_LPM_RESP_MASK   (0x3 << USB_CR_LPM_RESP_SHIFT)
#define USB_STS_LPM_ATTR_SHIFT (20U)
#define USB_STS_LPM_ATTR_MASK  (0x7ff << USB_STS_LPM_ATTR_SHIFT)
#define USB_STS_LPM            (1 << 31U)

/* 0x8 : usb_resume_config */
#define USB_CR_RES_WIDTH_SHIFT (0U)
#define USB_CR_RES_WIDTH_MASK  (0x7ff << USB_CR_RES_WIDTH_SHIFT)
#define USB_CR_RES_TRIG        (1 << 12U)
#define USB_CR_RES_FORCE       (1 << 31U)

/* 0x10 : usb_setup_data_0 */
#define USB_STS_SETUP_DATA_B0_SHIFT (0U)
#define USB_STS_SETUP_DATA_B0_MASK  (0xff << USB_STS_SETUP_DATA_B0_SHIFT)
#define USB_STS_SETUP_DATA_B1_SHIFT (8U)
#define USB_STS_SETUP_DATA_B1_MASK  (0xff << USB_STS_SETUP_DATA_B1_SHIFT)
#define USB_STS_SETUP_DATA_B2_SHIFT (16U)
#define USB_STS_SETUP_DATA_B2_MASK  (0xff << USB_STS_SETUP_DATA_B2_SHIFT)
#define USB_STS_SETUP_DATA_B3_SHIFT (24U)
#define USB_STS_SETUP_DATA_B3_MASK  (0xff << USB_STS_SETUP_DATA_B3_SHIFT)

/* 0x14 : usb_setup_data_1 */
#define USB_STS_SETUP_DATA_B4_SHIFT (0U)
#define USB_STS_SETUP_DATA_B4_MASK  (0xff << USB_STS_SETUP_DATA_B4_SHIFT)
#define USB_STS_SETUP_DATA_B5_SHIFT (8U)
#define USB_STS_SETUP_DATA_B5_MASK  (0xff << USB_STS_SETUP_DATA_B5_SHIFT)
#define USB_STS_SETUP_DATA_B6_SHIFT (16U)
#define USB_STS_SETUP_DATA_B6_MASK  (0xff << USB_STS_SETUP_DATA_B6_SHIFT)
#define USB_STS_SETUP_DATA_B7_SHIFT (24U)
#define USB_STS_SETUP_DATA_B7_MASK  (0xff << USB_STS_SETUP_DATA_B7_SHIFT)

/* 0x18 : usb_frame_no */
#define USB_STS_FRAME_NO_SHIFT (0U)
#define USB_STS_FRAME_NO_MASK  (0x7ff << USB_STS_FRAME_NO_SHIFT)
#define USB_STS_PID_SHIFT      (12U)
#define USB_STS_PID_MASK       (0xf << USB_STS_PID_SHIFT)
#define USB_STS_EP_NO_SHIFT    (16U)
#define USB_STS_EP_NO_MASK     (0xf << USB_STS_EP_NO_SHIFT)

/* 0x1C : usb_error */
#define USB_UTMI_RX_ERR (1 << 0U)
#define USB_XFER_TO_ERR (1 << 1U)
#define USB_IVLD_EP_ERR (1 << 2U)
#define USB_PID_SEQ_ERR (1 << 3U)
#define USB_PID_CKS_ERR (1 << 4U)
#define USB_CRC5_ERR    (1 << 5U)
#define USB_CRC16_ERR   (1 << 6U)

/* 0x20 : USB interrupt enable */
#define USB_CR_SOF_EN            (1 << 0U)
#define USB_CR_USB_RESET_EN      (1 << 1U)
#define USB_CR_VBUS_TGL_EN       (1 << 2U)
#define USB_CR_GET_DCT_CMD_EN    (1 << 3U)
#define USB_CR_EP0_SETUP_CMD_EN  (1 << 4U)
#define USB_CR_EP0_SETUP_DONE_EN (1 << 5U)
#define USB_CR_EP0_IN_CMD_EN     (1 << 6U)
#define USB_CR_EP0_IN_DONE_EN    (1 << 7U)
#define USB_CR_EP0_OUT_CMD_EN    (1 << 8U)
#define USB_CR_EP0_OUT_DONE_EN   (1 << 9U)
#define USB_CR_EP1_CMD_EN        (1 << 10U)
#define USB_CR_EP1_DONE_EN       (1 << 11U)
#define USB_CR_EP2_CMD_EN        (1 << 12U)
#define USB_CR_EP2_DONE_EN       (1 << 13U)
#define USB_CR_EP3_CMD_EN        (1 << 14U)
#define USB_CR_EP3_DONE_EN       (1 << 15U)
#define USB_CR_EP4_CMD_EN        (1 << 16U)
#define USB_CR_EP4_DONE_EN       (1 << 17U)
#define USB_CR_EP5_CMD_EN        (1 << 18U)
#define USB_CR_EP5_DONE_EN       (1 << 19U)
#define USB_CR_EP6_CMD_EN        (1 << 20U)
#define USB_CR_EP6_DONE_EN       (1 << 21U)
#define USB_CR_EP7_CMD_EN        (1 << 22U)
#define USB_CR_EP7_DONE_EN       (1 << 23U)
#define USB_CR_USB_REND_EN       (1 << 27U)
#define USB_CR_LPM_WKUP_EN       (1 << 28U)
#define USB_CR_LPM_PKT_EN        (1 << 29U)
#define USB_CR_SOF_3MS_EN        (1 << 30U)
#define USB_CR_USB_ERR_EN        (1 << 31U)

/* 0x24 : USB interrupt status */
#define USB_SOF_INT            (1 << 0U)
#define USB_RESET_INT          (1 << 1U)
#define USB_VBUS_TGL_INT       (1 << 2U)
#define USB_GET_DCT_CMD_INT    (1 << 3U)
#define USB_EP0_SETUP_CMD_INT  (1 << 4U)
#define USB_EP0_SETUP_DONE_INT (1 << 5U)
#define USB_EP0_IN_CMD_INT     (1 << 6U)
#define USB_EP0_IN_DONE_INT    (1 << 7U)
#define USB_EP0_OUT_CMD_INT    (1 << 8U)
#define USB_EP0_OUT_DONE_INT   (1 << 9U)
#define USB_EP1_CMD_INT        (1 << 10U)
#define USB_EP1_DONE_INT       (1 << 11U)
#define USB_EP2_CMD_INT        (1 << 12U)
#define USB_EP2_DONE_INT       (1 << 13U)
#define USB_EP3_CMD_INT        (1 << 14U)
#define USB_EP3_DONE_INT       (1 << 15U)
#define USB_EP4_CMD_INT        (1 << 16U)
#define USB_EP4_DONE_INT       (1 << 17U)
#define USB_EP5_CMD_INT        (1 << 18U)
#define USB_EP5_DONE_INT       (1 << 19U)
#define USB_EP6_CMD_INT        (1 << 20U)
#define USB_EP6_DONE_INT       (1 << 21U)
#define USB_EP7_CMD_INT        (1 << 22U)
#define USB_EP7_DONE_INT       (1 << 23U)
#define USB_REND_INT           (1 << 27U)
#define USB_LPM_WKUP_INT       (1 << 28U)
#define USB_LPM_PKT_INT        (1 << 29U)
#define USB_SOF_3MS_INT        (1 << 30U)
#define USB_ERR_INT            (1 << 31U)

/* 0x28 : USB interrupt mask */
#define USB_CR_SOF_MASK            (1 << 0U)
#define USB_CR_USB_RESET_MASK      (1 << 1U)
#define USB_CR_VBUS_TGL_MASK       (1 << 2U)
#define USB_CR_GET_DCT_CMD_MASK    (1 << 3U)
#define USB_CR_EP0_SETUP_CMD_MASK  (1 << 4U)
#define USB_CR_EP0_SETUP_DONE_MASK (1 << 5U)
#define USB_CR_EP0_IN_CMD_MASK     (1 << 6U)
#define USB_CR_EP0_IN_DONE_MASK    (1 << 7U)
#define USB_CR_EP0_OUT_CMD_MASK    (1 << 8U)
#define USB_CR_EP0_OUT_DONE_MASK   (1 << 9U)
#define USB_CR_EP1_CMD_MASK        (1 << 10U)
#define USB_CR_EP1_DONE_MASK       (1 << 11U)
#define USB_CR_EP2_CMD_MASK        (1 << 12U)
#define USB_CR_EP2_DONE_MASK       (1 << 13U)
#define USB_CR_EP3_CMD_MASK        (1 << 14U)
#define USB_CR_EP3_DONE_MASK       (1 << 15U)
#define USB_CR_EP4_CMD_MASK        (1 << 16U)
#define USB_CR_EP4_DONE_MASK       (1 << 17U)
#define USB_CR_EP5_CMD_MASK        (1 << 18U)
#define USB_CR_EP5_DONE_MASK       (1 << 19U)
#define USB_CR_EP6_CMD_MASK        (1 << 20U)
#define USB_CR_EP6_DONE_MASK       (1 << 21U)
#define USB_CR_EP7_CMD_MASK        (1 << 22U)
#define USB_CR_EP7_DONE_MASK       (1 << 23U)
#define USB_CR_USB_REND_MASK       (1 << 27U)
#define USB_CR_LPM_WKUP_MASK       (1 << 28U)
#define USB_CR_LPM_PKT_MASK        (1 << 29U)
#define USB_CR_SOF_3MS_MASK        (1 << 30U)
#define USB_CR_USB_ERR_MASK        (1 << 31U)

/* 0x2C : USB interrupt clear */
#define USB_CR_SOF_CLR            (1 << 0U)
#define USB_CR_USB_RESET_CLR      (1 << 1U)
#define USB_CR_VBUS_TGL_CLR       (1 << 2U)
#define USB_CR_GET_DCT_CMD_CLR    (1 << 3U)
#define USB_CR_EP0_SETUP_CMD_CLR  (1 << 4U)
#define USB_CR_EP0_SETUP_DONE_CLR (1 << 5U)
#define USB_CR_EP0_IN_CMD_CLR     (1 << 6U)
#define USB_CR_EP0_IN_DONE_CLR    (1 << 7U)
#define USB_CR_EP0_OUT_CMD_CLR    (1 << 8U)
#define USB_CR_EP0_OUT_DONE_CLR   (1 << 9U)
#define USB_CR_EP1_CMD_CLR        (1 << 10U)
#define USB_CR_EP1_DONE_CLR       (1 << 11U)
#define USB_CR_EP2_CMD_CLR        (1 << 12U)
#define USB_CR_EP2_DONE_CLR       (1 << 13U)
#define USB_CR_EP3_CMD_CLR        (1 << 14U)
#define USB_CR_EP3_DONE_CLR       (1 << 15U)
#define USB_CR_EP4_CMD_CLR        (1 << 16U)
#define USB_CR_EP4_DONE_CLR       (1 << 17U)
#define USB_CR_EP5_CMD_CLR        (1 << 18U)
#define USB_CR_EP5_DONE_CLR       (1 << 19U)
#define USB_CR_EP6_CMD_CLR        (1 << 20U)
#define USB_CR_EP6_DONE_CLR       (1 << 21U)
#define USB_CR_EP7_CMD_CLR        (1 << 22U)
#define USB_CR_EP7_DONE_CLR       (1 << 23U)
#define USB_CR_USB_REND_CLR       (1 << 27U)
#define USB_CR_LPM_WKUP_CLR       (1 << 28U)
#define USB_CR_LPM_PKT_CLR        (1 << 29U)
#define USB_CR_SOF_3MS_CLR        (1 << 30U)
#define USB_CR_USB_ERR_CLR        (1 << 31U)

/* 0x40 : ep1_config */
#define USB_CR_EP1_SIZE_SHIFT (0U)
#define USB_CR_EP1_SIZE_MASK  (0x7ff << USB_CR_EP1_SIZE_SHIFT)
#define USB_CR_EP1_DIR_SHIFT  (11U)
#define USB_CR_EP1_DIR_MASK   (0x3 << USB_CR_EP1_DIR_SHIFT)
#define USB_CR_EP1_TYPE_SHIFT (13U)
#define USB_CR_EP1_TYPE_MASK  (0x7 << USB_CR_EP1_TYPE_SHIFT)
#define USB_CR_EP1_STALL      (1 << 16U)
#define USB_CR_EP1_NACK       (1 << 17U)
#define USB_CR_EP1_RDY        (1 << 18U)
#define USB_STS_EP1_RDY       (1 << 19U)

/* 0x44 : ep2_config */
#define USB_CR_EP2_SIZE_SHIFT (0U)
#define USB_CR_EP2_SIZE_MASK  (0x7ff << USB_CR_EP2_SIZE_SHIFT)
#define USB_CR_EP2_DIR_SHIFT  (11U)
#define USB_CR_EP2_DIR_MASK   (0x3 << USB_CR_EP2_DIR_SHIFT)
#define USB_CR_EP2_TYPE_SHIFT (13U)
#define USB_CR_EP2_TYPE_MASK  (0x7 << USB_CR_EP2_TYPE_SHIFT)
#define USB_CR_EP2_STALL      (1 << 16U)
#define USB_CR_EP2_NACK       (1 << 17U)
#define USB_CR_EP2_RDY        (1 << 18U)
#define USB_STS_EP2_RDY       (1 << 19U)

/* 0x48 : ep3_config */
#define USB_CR_EP3_SIZE_SHIFT (0U)
#define USB_CR_EP3_SIZE_MASK  (0x7ff << USB_CR_EP3_SIZE_SHIFT)
#define USB_CR_EP3_DIR_SHIFT  (11U)
#define USB_CR_EP3_DIR_MASK   (0x3 << USB_CR_EP3_DIR_SHIFT)
#define USB_CR_EP3_TYPE_SHIFT (13U)
#define USB_CR_EP3_TYPE_MASK  (0x7 << USB_CR_EP3_TYPE_SHIFT)
#define USB_CR_EP3_STALL      (1 << 16U)
#define USB_CR_EP3_NACK       (1 << 17U)
#define USB_CR_EP3_RDY        (1 << 18U)
#define USB_STS_EP3_RDY       (1 << 19U)

/* 0x4C : ep4_config */
#define USB_CR_EP4_SIZE_SHIFT (0U)
#define USB_CR_EP4_SIZE_MASK  (0x7ff << USB_CR_EP4_SIZE_SHIFT)
#define USB_CR_EP4_DIR_SHIFT  (11U)
#define USB_CR_EP4_DIR_MASK   (0x3 << USB_CR_EP4_DIR_SHIFT)
#define USB_CR_EP4_TYPE_SHIFT (13U)
#define USB_CR_EP4_TYPE_MASK  (0x7 << USB_CR_EP4_TYPE_SHIFT)
#define USB_CR_EP4_STALL      (1 << 16U)
#define USB_CR_EP4_NACK       (1 << 17U)
#define USB_CR_EP4_RDY        (1 << 18U)
#define USB_STS_EP4_RDY       (1 << 19U)

/* 0x50 : ep5_config */
#define USB_CR_EP5_SIZE_SHIFT (0U)
#define USB_CR_EP5_SIZE_MASK  (0x7ff << USB_CR_EP5_SIZE_SHIFT)
#define USB_CR_EP5_DIR_SHIFT  (11U)
#define USB_CR_EP5_DIR_MASK   (0x3 << USB_CR_EP5_DIR_SHIFT)
#define USB_CR_EP5_TYPE_SHIFT (13U)
#define USB_CR_EP5_TYPE_MASK  (0x7 << USB_CR_EP5_TYPE_SHIFT)
#define USB_CR_EP5_STALL      (1 << 16U)
#define USB_CR_EP5_NACK       (1 << 17U)
#define USB_CR_EP5_RDY        (1 << 18U)
#define USB_STS_EP5_RDY       (1 << 19U)

/* 0x54 : ep6_config */
#define USB_CR_EP6_SIZE_SHIFT (0U)
#define USB_CR_EP6_SIZE_MASK  (0x7ff << USB_CR_EP6_SIZE_SHIFT)
#define USB_CR_EP6_DIR_SHIFT  (11U)
#define USB_CR_EP6_DIR_MASK   (0x3 << USB_CR_EP6_DIR_SHIFT)
#define USB_CR_EP6_TYPE_SHIFT (13U)
#define USB_CR_EP6_TYPE_MASK  (0x7 << USB_CR_EP6_TYPE_SHIFT)
#define USB_CR_EP6_STALL      (1 << 16U)
#define USB_CR_EP6_NACK       (1 << 17U)
#define USB_CR_EP6_RDY        (1 << 18U)
#define USB_STS_EP6_RDY       (1 << 19U)

/* 0x58 : ep7_config */
#define USB_CR_EP7_SIZE_SHIFT (0U)
#define USB_CR_EP7_SIZE_MASK  (0x7ff << USB_CR_EP7_SIZE_SHIFT)
#define USB_CR_EP7_DIR_SHIFT  (11U)
#define USB_CR_EP7_DIR_MASK   (0x3 << USB_CR_EP7_DIR_SHIFT)
#define USB_CR_EP7_TYPE_SHIFT (13U)
#define USB_CR_EP7_TYPE_MASK  (0x7 << USB_CR_EP7_TYPE_SHIFT)
#define USB_CR_EP7_STALL      (1 << 16U)
#define USB_CR_EP7_NACK       (1 << 17U)
#define USB_CR_EP7_RDY        (1 << 18U)
#define USB_STS_EP7_RDY       (1 << 19U)

/* 0x100 : ep0_fifo_config */
#define USB_EP0_DMA_TX_EN         (1 << 0U)
#define USB_EP0_DMA_RX_EN         (1 << 1U)
#define USB_EP0_TX_FIFO_CLR       (1 << 2U)
#define USB_EP0_RX_FIFO_CLR       (1 << 3U)
#define USB_EP0_TX_FIFO_OVERFLOW  (1 << 4U)
#define USB_EP0_TX_FIFO_UNDERFLOW (1 << 5U)
#define USB_EP0_RX_FIFO_OVERFLOW  (1 << 6U)
#define USB_EP0_RX_FIFO_UNDERFLOW (1 << 7U)

/* 0x104 : ep0_fifo_status */
#define USB_EP0_TX_FIFO_CNT_SHIFT (0U)
#define USB_EP0_TX_FIFO_CNT_MASK  (0x7f << USB_EP0_TX_FIFO_CNT_SHIFT)
#define USB_EP0_TX_FIFO_EMPTY     (1 << 14U)
#define USB_EP0_TX_FIFO_FULL      (1 << 15U)
#define USB_EP0_RX_FIFO_CNT_SHIFT (16U)
#define USB_EP0_RX_FIFO_CNT_MASK  (0x7f << USB_EP0_RX_FIFO_CNT_SHIFT)
#define USB_EP0_RX_FIFO_EMPTY     (1 << 30U)
#define USB_EP0_RX_FIFO_FULL      (1 << 31U)

/* 0x108 : ep0_tx_fifo_wdata */
#define USB_EP0_TX_FIFO_WDATA_SHIFT (0U)
#define USB_EP0_TX_FIFO_WDATA_MASK  (0xff << USB_EP0_TX_FIFO_WDATA_SHIFT)

/* 0x10C : ep0_rx_fifo_rdata */
#define USB_EP0_RX_FIFO_RDATA_SHIFT (0U)
#define USB_EP0_RX_FIFO_RDATA_MASK  (0xff << USB_EP0_RX_FIFO_RDATA_SHIFT)

/* 0x110 : ep1_fifo_config */
#define USB_EP1_DMA_TX_EN         (1 << 0U)
#define USB_EP1_DMA_RX_EN         (1 << 1U)
#define USB_EP1_TX_FIFO_CLR       (1 << 2U)
#define USB_EP1_RX_FIFO_CLR       (1 << 3U)
#define USB_EP1_TX_FIFO_OVERFLOW  (1 << 4U)
#define USB_EP1_TX_FIFO_UNDERFLOW (1 << 5U)
#define USB_EP1_RX_FIFO_OVERFLOW  (1 << 6U)
#define USB_EP1_RX_FIFO_UNDERFLOW (1 << 7U)

/* 0x114 : ep1_fifo_status */
#define USB_EP1_TX_FIFO_CNT_SHIFT (0U)
#define USB_EP1_TX_FIFO_CNT_MASK  (0x7f << USB_EP1_TX_FIFO_CNT_SHIFT)
#define USB_EP1_TX_FIFO_EMPTY     (1 << 14U)
#define USB_EP1_TX_FIFO_FULL      (1 << 15U)
#define USB_EP1_RX_FIFO_CNT_SHIFT (16U)
#define USB_EP1_RX_FIFO_CNT_MASK  (0x7f << USB_EP1_RX_FIFO_CNT_SHIFT)
#define USB_EP1_RX_FIFO_EMPTY     (1 << 30U)
#define USB_EP1_RX_FIFO_FULL      (1 << 31U)

/* 0x118 : ep1_tx_fifo_wdata */
#define USB_EP1_TX_FIFO_WDATA_SHIFT (0U)
#define USB_EP1_TX_FIFO_WDATA_MASK  (0xff << USB_EP1_TX_FIFO_WDATA_SHIFT)

/* 0x11C : ep1_rx_fifo_rdata */
#define USB_EP1_RX_FIFO_RDATA_SHIFT (0U)
#define USB_EP1_RX_FIFO_RDATA_MASK  (0xff << USB_EP1_RX_FIFO_RDATA_SHIFT)

/* 0x120 : ep2_fifo_config */
#define USB_EP2_DMA_TX_EN         (1 << 0U)
#define USB_EP2_DMA_RX_EN         (1 << 1U)
#define USB_EP2_TX_FIFO_CLR       (1 << 2U)
#define USB_EP2_RX_FIFO_CLR       (1 << 3U)
#define USB_EP2_TX_FIFO_OVERFLOW  (1 << 4U)
#define USB_EP2_TX_FIFO_UNDERFLOW (1 << 5U)
#define USB_EP2_RX_FIFO_OVERFLOW  (1 << 6U)
#define USB_EP2_RX_FIFO_UNDERFLOW (1 << 7U)

/* 0x124 : ep2_fifo_status */
#define USB_EP2_TX_FIFO_CNT_SHIFT (0U)
#define USB_EP2_TX_FIFO_CNT_MASK  (0x7f << USB_EP2_TX_FIFO_CNT_SHIFT)
#define USB_EP2_TX_FIFO_EMPTY     (1 << 14U)
#define USB_EP2_TX_FIFO_FULL      (1 << 15U)
#define USB_EP2_RX_FIFO_CNT_SHIFT (16U)
#define USB_EP2_RX_FIFO_CNT_MASK  (0x7f << USB_EP2_RX_FIFO_CNT_SHIFT)
#define USB_EP2_RX_FIFO_EMPTY     (1 << 30U)
#define USB_EP2_RX_FIFO_FULL      (1 << 31U)

/* 0x128 : ep2_tx_fifo_wdata */
#define USB_EP2_TX_FIFO_WDATA_SHIFT (0U)
#define USB_EP2_TX_FIFO_WDATA_MASK  (0xff << USB_EP2_TX_FIFO_WDATA_SHIFT)

/* 0x12C : ep2_rx_fifo_rdata */
#define USB_EP2_RX_FIFO_RDATA_SHIFT (0U)
#define USB_EP2_RX_FIFO_RDATA_MASK  (0xff << USB_EP2_RX_FIFO_RDATA_SHIFT)

/* 0x130 : ep3_fifo_config */
#define USB_EP3_DMA_TX_EN         (1 << 0U)
#define USB_EP3_DMA_RX_EN         (1 << 1U)
#define USB_EP3_TX_FIFO_CLR       (1 << 2U)
#define USB_EP3_RX_FIFO_CLR       (1 << 3U)
#define USB_EP3_TX_FIFO_OVERFLOW  (1 << 4U)
#define USB_EP3_TX_FIFO_UNDERFLOW (1 << 5U)
#define USB_EP3_RX_FIFO_OVERFLOW  (1 << 6U)
#define USB_EP3_RX_FIFO_UNDERFLOW (1 << 7U)

/* 0x134 : ep3_fifo_status */
#define USB_EP3_TX_FIFO_CNT_SHIFT (0U)
#define USB_EP3_TX_FIFO_CNT_MASK  (0x7f << USB_EP3_TX_FIFO_CNT_SHIFT)
#define USB_EP3_TX_FIFO_EMPTY     (1 << 14U)
#define USB_EP3_TX_FIFO_FULL      (1 << 15U)
#define USB_EP3_RX_FIFO_CNT_SHIFT (16U)
#define USB_EP3_RX_FIFO_CNT_MASK  (0x7f << USB_EP3_RX_FIFO_CNT_SHIFT)
#define USB_EP3_RX_FIFO_EMPTY     (1 << 30U)
#define USB_EP3_RX_FIFO_FULL      (1 << 31U)

/* 0x138 : ep3_tx_fifo_wdata */
#define USB_EP3_TX_FIFO_WDATA_SHIFT (0U)
#define USB_EP3_TX_FIFO_WDATA_MASK  (0xff << USB_EP3_TX_FIFO_WDATA_SHIFT)

/* 0x13C : ep3_rx_fifo_rdata */
#define USB_EP3_RX_FIFO_RDATA_SHIFT (0U)
#define USB_EP3_RX_FIFO_RDATA_MASK  (0xff << USB_EP3_RX_FIFO_RDATA_SHIFT)

/* 0x140 : ep4_fifo_config */
#define USB_EP4_DMA_TX_EN         (1 << 0U)
#define USB_EP4_DMA_RX_EN         (1 << 1U)
#define USB_EP4_TX_FIFO_CLR       (1 << 2U)
#define USB_EP4_RX_FIFO_CLR       (1 << 3U)
#define USB_EP4_TX_FIFO_OVERFLOW  (1 << 4U)
#define USB_EP4_TX_FIFO_UNDERFLOW (1 << 5U)
#define USB_EP4_RX_FIFO_OVERFLOW  (1 << 6U)
#define USB_EP4_RX_FIFO_UNDERFLOW (1 << 7U)

/* 0x144 : ep4_fifo_status */
#define USB_EP4_TX_FIFO_CNT_SHIFT (0U)
#define USB_EP4_TX_FIFO_CNT_MASK  (0x7f << USB_EP4_TX_FIFO_CNT_SHIFT)
#define USB_EP4_TX_FIFO_EMPTY     (1 << 14U)
#define USB_EP4_TX_FIFO_FULL      (1 << 15U)
#define USB_EP4_RX_FIFO_CNT_SHIFT (16U)
#define USB_EP4_RX_FIFO_CNT_MASK  (0x7f << USB_EP4_RX_FIFO_CNT_SHIFT)
#define USB_EP4_RX_FIFO_EMPTY     (1 << 30U)
#define USB_EP4_RX_FIFO_FULL      (1 << 31U)

/* 0x148 : ep4_tx_fifo_wdata */
#define USB_EP4_TX_FIFO_WDATA_SHIFT (0U)
#define USB_EP4_TX_FIFO_WDATA_MASK  (0xff << USB_EP4_TX_FIFO_WDATA_SHIFT)

/* 0x14C : ep4_rx_fifo_rdata */
#define USB_EP4_RX_FIFO_RDATA_SHIFT (0U)
#define USB_EP4_RX_FIFO_RDATA_MASK  (0xff << USB_EP4_RX_FIFO_RDATA_SHIFT)

/* 0x150 : ep5_fifo_config */
#define USB_EP5_DMA_TX_EN         (1 << 0U)
#define USB_EP5_DMA_RX_EN         (1 << 1U)
#define USB_EP5_TX_FIFO_CLR       (1 << 2U)
#define USB_EP5_RX_FIFO_CLR       (1 << 3U)
#define USB_EP5_TX_FIFO_OVERFLOW  (1 << 4U)
#define USB_EP5_TX_FIFO_UNDERFLOW (1 << 5U)
#define USB_EP5_RX_FIFO_OVERFLOW  (1 << 6U)
#define USB_EP5_RX_FIFO_UNDERFLOW (1 << 7U)

/* 0x154 : ep5_fifo_status */
#define USB_EP5_TX_FIFO_CNT_SHIFT (0U)
#define USB_EP5_TX_FIFO_CNT_MASK  (0x7f << USB_EP5_TX_FIFO_CNT_SHIFT)
#define USB_EP5_TX_FIFO_EMPTY     (1 << 14U)
#define USB_EP5_TX_FIFO_FULL      (1 << 15U)
#define USB_EP5_RX_FIFO_CNT_SHIFT (16U)
#define USB_EP5_RX_FIFO_CNT_MASK  (0x7f << USB_EP5_RX_FIFO_CNT_SHIFT)
#define USB_EP5_RX_FIFO_EMPTY     (1 << 30U)
#define USB_EP5_RX_FIFO_FULL      (1 << 31U)

/* 0x158 : ep5_tx_fifo_wdata */
#define USB_EP5_TX_FIFO_WDATA_SHIFT (0U)
#define USB_EP5_TX_FIFO_WDATA_MASK  (0xff << USB_EP5_TX_FIFO_WDATA_SHIFT)

/* 0x15C : ep5_rx_fifo_rdata */
#define USB_EP5_RX_FIFO_RDATA_SHIFT (0U)
#define USB_EP5_RX_FIFO_RDATA_MASK  (0xff << USB_EP5_RX_FIFO_RDATA_SHIFT)

/* 0x160 : ep6_fifo_config */
#define USB_EP6_DMA_TX_EN         (1 << 0U)
#define USB_EP6_DMA_RX_EN         (1 << 1U)
#define USB_EP6_TX_FIFO_CLR       (1 << 2U)
#define USB_EP6_RX_FIFO_CLR       (1 << 3U)
#define USB_EP6_TX_FIFO_OVERFLOW  (1 << 4U)
#define USB_EP6_TX_FIFO_UNDERFLOW (1 << 5U)
#define USB_EP6_RX_FIFO_OVERFLOW  (1 << 6U)
#define USB_EP6_RX_FIFO_UNDERFLOW (1 << 7U)

/* 0x164 : ep6_fifo_status */
#define USB_EP6_TX_FIFO_CNT_SHIFT (0U)
#define USB_EP6_TX_FIFO_CNT_MASK  (0x7f << USB_EP6_TX_FIFO_CNT_SHIFT)
#define USB_EP6_TX_FIFO_EMPTY     (1 << 14U)
#define USB_EP6_TX_FIFO_FULL      (1 << 15U)
#define USB_EP6_RX_FIFO_CNT_SHIFT (16U)
#define USB_EP6_RX_FIFO_CNT_MASK  (0x7f << USB_EP6_RX_FIFO_CNT_SHIFT)
#define USB_EP6_RX_FIFO_EMPTY     (1 << 30U)
#define USB_EP6_RX_FIFO_FULL      (1 << 31U)

/* 0x168 : ep6_tx_fifo_wdata */
#define USB_EP6_TX_FIFO_WDATA_SHIFT (0U)
#define USB_EP6_TX_FIFO_WDATA_MASK  (0xff << USB_EP6_TX_FIFO_WDATA_SHIFT)

/* 0x16C : ep6_rx_fifo_rdata */
#define USB_EP6_RX_FIFO_RDATA_SHIFT (0U)
#define USB_EP6_RX_FIFO_RDATA_MASK  (0xff << USB_EP6_RX_FIFO_RDATA_SHIFT)

/* 0x170 : ep7_fifo_config */
#define USB_EP7_DMA_TX_EN         (1 << 0U)
#define USB_EP7_DMA_RX_EN         (1 << 1U)
#define USB_EP7_TX_FIFO_CLR       (1 << 2U)
#define USB_EP7_RX_FIFO_CLR       (1 << 3U)
#define USB_EP7_TX_FIFO_OVERFLOW  (1 << 4U)
#define USB_EP7_TX_FIFO_UNDERFLOW (1 << 5U)
#define USB_EP7_RX_FIFO_OVERFLOW  (1 << 6U)
#define USB_EP7_RX_FIFO_UNDERFLOW (1 << 7U)

/* 0x174 : ep7_fifo_status */
#define USB_EP7_TX_FIFO_CNT_SHIFT (0U)
#define USB_EP7_TX_FIFO_CNT_MASK  (0x7f << USB_EP7_TX_FIFO_CNT_SHIFT)
#define USB_EP7_TX_FIFO_EMPTY     (1 << 14U)
#define USB_EP7_TX_FIFO_FULL      (1 << 15U)
#define USB_EP7_RX_FIFO_CNT_SHIFT (16U)
#define USB_EP7_RX_FIFO_CNT_MASK  (0x7f << USB_EP7_RX_FIFO_CNT_SHIFT)
#define USB_EP7_RX_FIFO_EMPTY     (1 << 30U)
#define USB_EP7_RX_FIFO_FULL      (1 << 31U)

/* 0x178 : ep7_tx_fifo_wdata */
#define USB_EP7_TX_FIFO_WDATA_SHIFT (0U)
#define USB_EP7_TX_FIFO_WDATA_MASK  (0xff << USB_EP7_TX_FIFO_WDATA_SHIFT)

/* 0x17C : ep7_rx_fifo_rdata */
#define USB_EP7_RX_FIFO_RDATA_SHIFT (0U)
#define USB_EP7_RX_FIFO_RDATA_MASK  (0xff << USB_EP7_RX_FIFO_RDATA_SHIFT)

/* 0x1F0 : rsvd_0 */

/* 0x1F4 : rsvd_1 */

/* 0x1FC : xcvr_if_config */
#define USB_CR_XCVR_FORCE_TX_EN (1 << 0U)
#define USB_CR_XCVR_FORCE_TX_OE (1 << 1U)
#define USB_CR_XCVR_FORCE_TX_DP (1 << 2U)
#define USB_CR_XCVR_FORCE_TX_DN (1 << 3U)
#define USB_CR_XCVR_FORCE_RX_EN (1 << 4U)
#define USB_CR_XCVR_FORCE_RX_D  (1 << 5U)
#define USB_CR_XCVR_FORCE_RX_DP (1 << 6U)
#define USB_CR_XCVR_FORCE_RX_DN (1 << 7U)
#define USB_CR_XCVR_OM_RX_SEL   (1 << 8U)
#define USB_CR_XCVR_OM_RX_D     (1 << 9U)
#define USB_CR_XCVR_OM_RX_DP    (1 << 10U)
#define USB_CR_XCVR_OM_RX_DN    (1 << 11U)
#define USB_STS_VBUS_DET        (1 << 31U)

#endif /* __HARDWARE_USB_V1_H__ */
