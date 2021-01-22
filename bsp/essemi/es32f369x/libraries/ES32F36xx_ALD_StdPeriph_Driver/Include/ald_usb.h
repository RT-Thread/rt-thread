/**
  *********************************************************************************
  *
  * @file    ald_usb.h
  * @brief   Header file of USB module driver.
  *
  * @version V1.0
  * @date    25 Dec 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  ********************************************************************************
  */

#ifndef __ALD_USB_H__
#define __ALD_USB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "utils.h"
#include "ald_rmu.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup USB
  * @{
  */

/** @defgroup USB_Public_Macros USB Public Macros
  * @{
  */

#define USB_POWER_ISOUP         0x00000080U
#define USB_POWER_SOFTCONN      0x00000040U
#define USB_POWER_HS_EN		0x00000020U
#define USB_POWER_HS_M		0x00000010U
#define USB_POWER_RESET         0x00000008U
#define USB_POWER_RESUME        0x00000004U
#define USB_POWER_SUSPEND       0x00000002U
#define USB_POWER_PWRDNPHY      0x00000001U

#define USB_DEVCTL_DEV          0x00000080U
#define USB_DEVCTL_FSDEV        0x00000040U
#define USB_DEVCTL_LSDEV        0x00000020U
#define USB_DEVCTL_VBUS_M       0x00000018U
#define USB_DEVCTL_VBUS_NONE    0x00000000U
#define USB_DEVCTL_VBUS_SEND    0x00000008U
#define USB_DEVCTL_VBUS_AVALID  0x00000010U
#define USB_DEVCTL_VBUS_VALID   0x00000018U
#define USB_DEVCTL_HOST         0x00000004U
#define USB_DEVCTL_HOSTREQ      0x00000002U
#define USB_DEVCTL_SESSION      0x00000001U

#define USB_RXCSRH1_AUTOCL      0x00000080U
#define USB_RXCSRH1_AUTORQ      0x00000040U
#define USB_RXCSRH1_ISO         0x00000040U
#define USB_RXCSRH1_DMAEN       0x00000020U
#define USB_RXCSRH1_DISNYET     0x00000010U
#define USB_RXCSRH1_PIDERR      0x00000010U
#define USB_RXCSRH1_DMAMOD      0x00000008U
#define USB_RXCSRH1_DTWE        0x00000004U
#define USB_RXCSRH1_DT          0x00000002U
#define USB_RXCSRH1_INCOMPRX    0x00000001U

#define USB_CSRH0_DISPING       0x00000008U
#define USB_CSRH0_DTWE          0x00000004U
#define USB_CSRH0_DT            0x00000002U
#define USB_CSRH0_FLUSH         0x00000001U

#define USB_TXCSRH1_AUTOSET     0x00000080U
#define USB_TXCSRH1_ISO         0x00000040U
#define USB_TXCSRH1_MODE        0x00000020U
#define USB_TXCSRH1_DMAEN       0x00000010U
#define USB_TXCSRH1_FDT         0x00000008U
#define USB_TXCSRH1_DMAMOD      0x00000004U
#define USB_TXCSRH1_DTWE        0x00000002U
#define USB_TXCSRH1_DT          0x00000001U

#define USB_TXCSRL1_NAKTO       0x00000080U
#define USB_TXCSRL1_CLRDT       0x00000040U
#define USB_TXCSRL1_STALLED     0x00000020U
#define USB_TXCSRL1_STALL       0x00000010U
#define USB_TXCSRL1_SETUP       0x00000010U
#define USB_TXCSRL1_FLUSH       0x00000008U
#define USB_TXCSRL1_ERROR       0x00000004U
#define USB_TXCSRL1_UNDRN       0x00000004U
#define USB_TXCSRL1_FIFONE      0x00000002U
#define USB_TXCSRL1_TXRDY       0x00000001U

#define USB_RXCSRL1_CLRDT       0x00000080U
#define USB_RXCSRL1_STALLED     0x00000040U
#define USB_RXCSRL1_STALL       0x00000020U
#define USB_RXCSRL1_REQPKT      0x00000020U
#define USB_RXCSRL1_FLUSH       0x00000010U
#define USB_RXCSRL1_DATAERR     0x00000008U
#define USB_RXCSRL1_NAKTO       0x00000008U
#define USB_RXCSRL1_OVER        0x00000004U
#define USB_RXCSRL1_ERROR       0x00000004U
#define USB_RXCSRL1_FULL        0x00000002U
#define USB_RXCSRL1_RXRDY       0x00000001U

#define USB_CSRL0_NAKTO         0x00000080U
#define USB_CSRL0_SETENDC       0x00000080U
#define USB_CSRL0_STATUS        0x00000040U
#define USB_CSRL0_RXRDYC        0x00000040U
#define USB_CSRL0_REQPKT        0x00000020U
#define USB_CSRL0_STALL         0x00000020U
#define USB_CSRL0_SETEND        0x00000010U
#define USB_CSRL0_ERROR         0x00000010U
#define USB_CSRL0_DATAEND       0x00000008U
#define USB_CSRL0_SETUP         0x00000008U
#define USB_CSRL0_STALLED       0x00000004U
#define USB_CSRL0_TXRDY         0x00000002U
#define USB_CSRL0_RXRDY         0x00000001U

#define USB_TYPE0_SPEED_M       0x000000C0U
#define USB_TYPE0_SPEED_HIGH    0x00000040U
#define USB_TYPE0_SPEED_FULL    0x00000080U
#define USB_TYPE0_SPEED_LOW     0x000000C0U

#define USB_TXTYPE1_SPEED_M     0x000000C0U
#define USB_TXTYPE1_SPEED_DFLT  0x00000000U
#define USB_TXTYPE1_SPEED_HIGH  0x00000040U
#define USB_TXTYPE1_SPEED_FULL  0x00000080U
#define USB_TXTYPE1_SPEED_LOW   0x000000C0U
#define USB_TXTYPE1_PROTO_M     0x00000030U
#define USB_TXTYPE1_PROTO_CTRL  0x00000000U
#define USB_TXTYPE1_PROTO_ISOC  0x00000010U
#define USB_TXTYPE1_PROTO_BULK  0x00000020U
#define USB_TXTYPE1_PROTO_INT   0x00000030U
#define USB_TXTYPE1_TEP_M       0x0000000FU
#define USB_TXTYPE1_TEP_S       0U

#define USB_LPMATTR_ENDPT_M     0x0000F000U
#define USB_LPMATTR_RMTWAK      0x00000100U
#define USB_LPMATTR_HIRD_M      0x000000F0U
#define USB_LPMATTR_LS_M        0x0000000FU
#define USB_LPMATTR_LS_L1       0x00000001U
#define USB_LPMATTR_ENDPT_S     12U
#define USB_LPMATTR_HIRD_S      4U

#define USB_LPMCNTRL_LPMRES	0x00000002U
#define USB_LPMCNTRL_LPMXMT	0x00000001U
#define USB_LPMCNTRL_ENABLE	0x00000006U
#define USB_LPMCNTRL_DISABLE	0x00000000U

#define USB_INTCTRL_ALL         0x000003FFU
#define USB_INTCTRL_STATUS      0x000000FFU
#define USB_INTCTRL_VBUS_ERR    0x00000080U
#define USB_INTCTRL_SESSION     0x00000040U
#define USB_INTCTRL_SESSION_END 0x00000040U
#define USB_INTCTRL_DISCONNECT  0x00000020U
#define USB_INTCTRL_CONNECT     0x00000010U
#define USB_INTCTRL_SOF         0x00000008U
#define USB_INTCTRL_BABBLE      0x00000004U
#define USB_INTCTRL_RESET       0x00000004U
#define USB_INTCTRL_RESUME      0x00000002U
#define USB_INTCTRL_SUSPEND     0x00000001U
#define USB_INTCTRL_MODE_DETECT 0x00000200U
#define USB_INTCTRL_POWER_FAULT 0x00000100U

#define USB_INTEP_ALL           0xFFFFFFFFU
#define USB_INTEP_HOST_IN       0xFFFE0000U
#define USB_INTEP_HOST_IN_15    0x80000000U
#define USB_INTEP_HOST_IN_14    0x40000000U
#define USB_INTEP_HOST_IN_13    0x20000000U
#define USB_INTEP_HOST_IN_12    0x10000000U
#define USB_INTEP_HOST_IN_11    0x08000000U
#define USB_INTEP_HOST_IN_10    0x04000000U
#define USB_INTEP_HOST_IN_9     0x02000000U
#define USB_INTEP_HOST_IN_8     0x01000000U
#define USB_INTEP_HOST_IN_7     0x00800000U
#define USB_INTEP_HOST_IN_6     0x00400000U
#define USB_INTEP_HOST_IN_5     0x00200000U
#define USB_INTEP_HOST_IN_4     0x00100000U
#define USB_INTEP_HOST_IN_3     0x00080000U
#define USB_INTEP_HOST_IN_2     0x00040000U
#define USB_INTEP_HOST_IN_1     0x00020000U

#define USB_INTEP_DEV_OUT       0xFFFE0000U
#define USB_INTEP_DEV_OUT_15    0x80000000U
#define USB_INTEP_DEV_OUT_14    0x40000000U
#define USB_INTEP_DEV_OUT_13    0x20000000U
#define USB_INTEP_DEV_OUT_12    0x10000000U
#define USB_INTEP_DEV_OUT_11    0x08000000U
#define USB_INTEP_DEV_OUT_10    0x04000000U
#define USB_INTEP_DEV_OUT_9     0x02000000U
#define USB_INTEP_DEV_OUT_8     0x01000000U
#define USB_INTEP_DEV_OUT_7     0x00800000U
#define USB_INTEP_DEV_OUT_6     0x00400000U
#define USB_INTEP_DEV_OUT_5     0x00200000U
#define USB_INTEP_DEV_OUT_4     0x00100000U
#define USB_INTEP_DEV_OUT_3     0x00080000U
#define USB_INTEP_DEV_OUT_2     0x00040000U
#define USB_INTEP_DEV_OUT_1     0x00020000U

#define USB_INTEP_HOST_OUT      0x0000FFFEU
#define USB_INTEP_HOST_OUT_15   0x00008000U
#define USB_INTEP_HOST_OUT_14   0x00004000U
#define USB_INTEP_HOST_OUT_13   0x00002000U
#define USB_INTEP_HOST_OUT_12   0x00001000U
#define USB_INTEP_HOST_OUT_11   0x00000800U
#define USB_INTEP_HOST_OUT_10   0x00000400U
#define USB_INTEP_HOST_OUT_9    0x00000200U
#define USB_INTEP_HOST_OUT_8    0x00000100U
#define USB_INTEP_HOST_OUT_7    0x00000080U
#define USB_INTEP_HOST_OUT_6    0x00000040U
#define USB_INTEP_HOST_OUT_5    0x00000020U
#define USB_INTEP_HOST_OUT_4    0x00000010U
#define USB_INTEP_HOST_OUT_3    0x00000008U
#define USB_INTEP_HOST_OUT_2    0x00000004U
#define USB_INTEP_HOST_OUT_1    0x00000002U

#define USB_INTEP_DEV_IN        0x0000FFFEU
#define USB_INTEP_DEV_IN_15     0x00008000U
#define USB_INTEP_DEV_IN_14     0x00004000U
#define USB_INTEP_DEV_IN_13     0x00002000U
#define USB_INTEP_DEV_IN_12     0x00001000U
#define USB_INTEP_DEV_IN_11     0x00000800U
#define USB_INTEP_DEV_IN_10     0x00000400U
#define USB_INTEP_DEV_IN_9      0x00000200U
#define USB_INTEP_DEV_IN_8      0x00000100U
#define USB_INTEP_DEV_IN_7      0x00000080U
#define USB_INTEP_DEV_IN_6      0x00000040U
#define USB_INTEP_DEV_IN_5      0x00000020U
#define USB_INTEP_DEV_IN_4      0x00000010U
#define USB_INTEP_DEV_IN_3      0x00000008U
#define USB_INTEP_DEV_IN_2      0x00000004U
#define USB_INTEP_DEV_IN_1      0x00000002U

#define USB_INTEP_0             0x00000001U

#define USB_UNDEF_SPEED         0x80000000U
#define USB_HIGH_SPEED          0x00000002U
#define USB_FULL_SPEED          0x00000001U
#define USB_LOW_SPEED           0x00000000U

#define USB_HOST_IN_STATUS      0x114F0000U
#define USB_HOST_IN_PID_ERROR   0x10000000U
#define USB_HOST_IN_NOT_COMP    0x01000000U
#define USB_HOST_IN_STALL       0x00400000U
#define USB_HOST_IN_DATA_ERROR  0x00080000U

#define USB_HOST_IN_NAK_TO      0x00080000U

#define USB_HOST_IN_ERROR       0x00040000U

#define USB_HOST_IN_FIFO_FULL   0x00020000U
#define USB_HOST_IN_PKTRDY      0x00010000U
#define USB_HOST_OUT_STATUS     0x000000A7U
#define USB_HOST_OUT_NAK_TO     0x00000080U

#define USB_HOST_OUT_NOT_COMP   0x00000080U

#define USB_HOST_OUT_STALL      0x00000020U
#define USB_HOST_OUT_ERROR      0x00000004U

#define USB_HOST_OUT_FIFO_NE    0x00000002U
#define USB_HOST_OUT_PKTPEND    0x00000001U
#define USB_HOST_EP0_NAK_TO     0x00000080U

#define USB_HOST_EP0_STATUS     0x00000040U
#define USB_HOST_EP0_ERROR      0x00000010U

#define USB_HOST_EP0_RX_STALL   0x00000004U
#define USB_HOST_EP0_RXPKTRDY   0x00000001U
#define USB_DEV_RX_PID_ERROR    0x01000000U

#define USB_DEV_RX_SENT_STALL   0x00400000U
#define USB_DEV_RX_DATA_ERROR   0x00080000U
#define USB_DEV_RX_OVERRUN      0x00040000U

#define USB_DEV_RX_FIFO_FULL    0x00020000U
#define USB_DEV_RX_PKT_RDY      0x00010000U
#define USB_DEV_TX_NOT_COMP     0x00000080U

#define USB_DEV_TX_SENT_STALL   0x00000020U
#define USB_DEV_TX_UNDERRUN     0x00000004U
#define USB_DEV_TX_FIFO_NE      0x00000002U
#define USB_DEV_TX_TXPKTRDY     0x00000001U
#define USB_DEV_EP0_SETUP_END   0x00000010U

#define USB_DEV_EP0_SENT_STALL  0x00000004U
#define USB_DEV_EP0_IN_PKTPEND  0x00000002U
#define USB_DEV_EP0_OUT_PKTRDY  0x00000001U

#define USB_EP_AUTO_SET         0x00000001U
#define USB_EP_AUTO_REQUEST     0x00000002U
#define USB_EP_AUTO_CLEAR       0x00000004U
#define USB_EP_DMA_MODE_0       0x00000008U
#define USB_EP_DMA_MODE_1       0x00000010U
#define USB_EP_DIS_NYET         0x00000020U


#define USB_EP_MODE_ISOC        0x00000000U
#define USB_EP_MODE_BULK        0x00000100U
#define USB_EP_MODE_INT         0x00000200U
#define USB_EP_MODE_CTRL        0x00000300U
#define USB_EP_MODE_MASK        0x00000300U
#define USB_EP_SPEED_LOW        0x00000000U
#define USB_EP_SPEED_FULL       0x00001000U
#define USB_EP_SPEED_HIGH       0x00004000U
#define USB_EP_HOST_IN          0x00000000U
#define USB_EP_HOST_OUT         0x00002000U
#define USB_EP_DEV_IN           0x00002000U
#define USB_EP_DEV_OUT          0x00000000U

#define USB_HOST_PWRFLT_LOW     0x00000010U
#define USB_HOST_PWRFLT_HIGH    0x00000030U
#define USB_HOST_PWRFLT_EP_NONE 0x00000000U
#define USB_HOST_PWRFLT_EP_TRI  0x00000140U
#define USB_HOST_PWRFLT_EP_LOW  0x00000240U
#define USB_HOST_PWRFLT_EP_HIGH 0x00000340U
#define USB_HOST_PWREN_MAN_LOW  0x00000000U
#define USB_HOST_PWREN_MAN_HIGH 0x00000001U
#define USB_HOST_PWREN_AUTOLOW  0x00000002U
#define USB_HOST_PWREN_AUTOHIGH 0x00000003U
#define USB_HOST_PWREN_FILTER   0x00010000U

#define USB_HOST_LPM_RMTWAKE    0x00000100U
#define USB_HOST_LPM_L1         0x00000001U
#define USB_DEV_LPM_NAK         0x00000010U
#define USB_DEV_LPM_NONE        0x00000000U
#define USB_DEV_LPM_EN          0x0000000cU
#define USB_DEV_LPM_EXTONLY     0x00000004U
#define USB_DEV_LPM_LS_RMTWAKE  0x00000100U
#define USB_DEV_LPM_LS_L1       0x00000001U
#define USB_INTLPM_ERROR        0x00000020U
#define USB_INTLPM_RESUME       0x00000010U
#define USB_INTLPM_INCOMPLETE   0x00000008U
#define USB_INTLPM_ACK          0x00000004U
#define USB_INTLPM_NYET         0x00000002U
#define USB_INTLPM_STALL        0x00000001U

#define MAX_NAK_LIMIT           31U
#define DISABLE_NAK_LIMIT       0U

#define MAX_PACKET_SIZE_EP0     64U
#define USB_EP_0                0U
#define USB_EP_1                1U
#define USB_EP_2                2U
#define USB_EP_3                3U
#define USB_EP_4                4U
#define USB_EP_5                5U
#define NUM_USB_EP              6U
#define IndexToUSBEP(x)         ((x))
#define USBEPToIndex(x)         ((x))

#define USB_FIFO_SZ_8           0x00000000U
#define USB_FIFO_SZ_16          0x00000001U
#define USB_FIFO_SZ_32          0x00000002U
#define USB_FIFO_SZ_64          0x00000003U
#define USB_FIFO_SZ_128         0x00000004U
#define USB_FIFO_SZ_256         0x00000005U
#define USB_FIFO_SZ_512         0x00000006U
#define USB_FIFO_SZ_1024        0x00000007U
#define USB_FIFO_SZ_2048        0x00000008U
#define USBFIFOSizeToBytes(x)   (8 << (x))

#define USB_TRANS_OUT           0x00000102U
#define USB_TRANS_IN            0x00000102U
#define USB_TRANS_IN_LAST       0x0000010aU
#define USB_TRANS_SETUP         0x0000110aU
#define USB_TRANS_STATUS        0x00000142U

#define USB_DUAL_MODE_HOST      0x00000001U
#define USB_DUAL_MODE_DEVICE    0x00000081U
#define USB_DUAL_MODE_NONE      0x00000080U
#define USB_OTG_MODE_ASIDE_HOST 0x0000001dU
#define USB_OTG_MODE_ASIDE_NPWR 0x00000001U
#define USB_OTG_MODE_ASIDE_SESS 0x00000009U
#define USB_OTG_MODE_ASIDE_AVAL 0x00000011U
#define USB_OTG_MODE_ASIDE_DEV  0x00000019U
#define USB_OTG_MODE_BSIDE_HOST 0x0000009dU
#define USB_OTG_MODE_BSIDE_DEV  0x00000099U
#define USB_OTG_MODE_BSIDE_NPWR 0x00000081U
#define USB_OTG_MODE_NONE       0x00000080U

#define USB_DMA_INT_CH8         0x00000080U
#define USB_DMA_INT_CH7         0x00000040U
#define USB_DMA_INT_CH6         0x00000020U
#define USB_DMA_INT_CH5         0x00000010U
#define USB_DMA_INT_CH4         0x00000008U
#define USB_DMA_INT_CH3         0x00000004U
#define USB_DMA_INT_CH2         0x00000002U
#define USB_DMA_INT_CH1         0x00000001U
#define USB_DMA_EP_CFG_TX	0x00000001U
#define USB_DMA_EP_CFG_RX_DEV	0x00000002U
#define USB_DMA_EP_CFG_RX_HOST	0x00000004U
#define USB_DMA_EP_TX_MSK	0x94U
#define USB_DMA_EP_RX_DEV_MSK	0xA8U
#define USB_DMA_EP_RX_HOST_MSK	0xE8U
#define USB_DMA_STATUS_ERROR    0x00000100U

#define USB_MODE_HOST_VBUS      0x00000004U
#define USB_MODE_HOST           0x00000002U
#define USB_MODE_DEV_VBUS       0x00000005U
#define USB_MODE_DEV            0x00000003U
#define USB_MODE_OTG            0x00000000U

#define USB_RX_EPSTATUS_SHIFT   16U
#define USB_INTEP_RX_SHIFT      16U

#define USB_DMA_CFG_START	0x00000001U
#define USB_DMA_CFG_START_NO	0x00000000U
#define USB_DMA_CFG_DIR_WR	0x00000000U
#define USB_DMA_CFG_DIR_RD	0x00000002U
#define USB_DMA_CFG_MODE_0	0x00000000U
#define USB_DMA_CFG_MODE_1	0x00000004U
#define USB_DMA_CFG_IE_DIS	0x00000000U
#define USB_DMA_CFG_IE_EN	0x00000008U
#define USB_DMA_CFG_EP_1	0x00000010U
#define USB_DMA_CFG_EP_2	0x00000020U
#define USB_DMA_CFG_EP_3	0x00000030U
#define USB_DMA_CFG_EP_4	0x00000040U
#define USB_DMA_CFG_EP_5	0x00000050U
#define USB_DMA_CFG_BURST_NONE	0x00000000U
#define USB_DMA_CFG_BURST_4	0x00000200U
#define USB_DMA_CFG_BURST_8	0x00000400U
#define USB_DMA_CFG_BURST_16	0x00000600U
#define USB_DMA_CFG_MODE_MSK	0x00000004U
#define USB_DMA_CFG_EP_POS	0x00000004U
#define USB_DMA_CFG_EP_MSK	0x000000F0U
#define USB_DMA_CH_ERR_MSK	0x100U
/**
  * @}
  */

/** @addtogroup USB_Public_Functions
  * @{
  */

/** @addtogroup USB_Public_Functions_Group1
  * @{
  */
/* Base functions */
extern uint32_t ald_usb_frame_number_get(void);
extern void ald_usb_otg_session_request(bool start);
extern uint32_t ald_usb_mode_get(void);
extern void ald_usb_high_speed_enable(bool enable);
extern uint32_t ald_usb_device_speed_get(void);
extern uint32_t ald_usb_num_ep_get( void);
extern void ald_usb_control_reset(void);
extern void ald_usb_clock_output(void);
extern int ald_usb_eye_diagram_start(uint8_t *buf, uint16_t len);
/**
  * @}
  */

/** @addtogroup USB_Public_Functions_Group2
  * @{
  */
/* Device functions */
extern uint8_t ald_usb_dev_get_addr(void);
extern void ald_usb_dev_set_addr(uint8_t addr);
extern void ald_usb_dev_connect(void);
extern void ald_usb_dev_disconnect(void);
extern void ald_usb_dev_ep_config(uint32_t ep_idx, uint32_t p_max, uint32_t flags);
extern void ald_usb_dev_ep_get_config(uint32_t ep_idx, uint32_t *p_max, uint32_t *flags);
extern void ald_usb_dev_ep_data_ack(uint32_t ep_idx, bool last);
extern void ald_usb_dev_ep_stall(uint32_t ep_idx, uint32_t flags);
extern void ald_usb_dev_ep_stall_clear(uint32_t ep_idx, uint32_t flags);
extern void ald_usb_dev_ep_status_clear(uint32_t ep_idx, uint32_t flags);
/**
  * @}
  */

/** @addtogroup USB_Public_Functions_Group3
  * @{
  */
/* Host functions */
extern uint32_t ald_usb_host_addr_get(uint32_t ep_idx, uint32_t flags);
extern void ald_usb_host_addr_set(uint32_t ep_idx, uint32_t addr, uint32_t flags);
extern void ald_usb_host_ep_config(uint32_t ep_idx, uint32_t p_max, uint32_t nak_val, uint32_t t_ep, uint32_t flags);
extern void ald_usb_host_ep_data_ack(uint32_t ep_idx);
extern void ald_usb_host_ep_data_toggle(uint32_t ep_idx, bool toggle, uint32_t flags);
extern void ald_usb_host_ep_status_clear(uint32_t ep_idx, uint32_t flags);
extern uint32_t ald_usb_host_hub_addr_get(uint32_t ep_idx, uint32_t flags);
extern void ald_usb_host_hub_addr_set(uint32_t ep_idx, uint32_t addr, uint32_t flags);
extern void ald_usb_host_pwr_disable(void);
extern void ald_usb_host_pwr_enable(void);
extern void ald_usb_host_pwr_config(uint32_t flags);
extern void ald_usb_host_pwr_fault_disable(void);
extern void ald_usb_host_pwr_fault_enable(void);
extern void ald_usb_host_request_in(uint32_t ep_idx);
extern void ald_usb_host_request_in_clear(uint32_t ep_idx);
extern void ald_usb_host_request_status(void);
extern void ald_usb_host_reset(bool start);
extern void ald_usb_host_resume(bool start);
extern void ald_usb_host_suspend(void);
extern uint32_t ald_usb_host_speed_get(void);
extern void ald_usb_host_ep_speed_set(uint32_t ep_idx, uint32_t flags);
extern void ald_usb_host_ep_ping(uint32_t ep_idx, bool enable);
/**
  * @}
  */

/** @addtogroup USB_Public_Functions_Group4
  * @{
  */
/* Endpoint functions */
extern uint32_t ald_usb_ep_data_avail(uint32_t ep_idx);
extern int32_t ald_usb_ep_data_get(uint32_t ep_idx, uint8_t *data, uint32_t *size);
extern int32_t ald_usb_ep_data_put(uint32_t ep_idx, uint8_t *data, uint32_t size);
extern int32_t ald_usb_ep_data_send(uint32_t ep_idx, uint32_t tx_type);
extern void ald_usb_ep_data_toggle_clear(uint32_t ep_idx, uint32_t flags);
extern void ald_usb_ep_req_packet_count(uint32_t ep_idx, uint32_t count);
extern uint32_t ald_usb_ep_status(uint32_t ep_idx);
extern void ald_usb_ep_dma_config(uint32_t ep_idx, uint32_t flag, type_func_t en);
/**
  * @}
  */

/** @addtogroup USB_Public_Functions_Group5
  * @{
  */
/* FIFO functions */
extern uint32_t ald_usb_fifo_addr_get(uint32_t ep_idx);
extern void ald_usb_fifo_config_get(uint32_t ep_idx, uint32_t *addr, uint32_t *size, uint32_t flags);
extern void ald_usb_fifo_config_set(uint32_t ep_idx, uint32_t addr, uint32_t size, uint32_t flags);
extern void ald_usb_fifo_flush(uint32_t ep_idx, uint32_t flags);
/**
  * @}
  */

/** @addtogroup USB_Public_Functions_Group6
  * @{
  */
/* Interrupt functions */
extern void ald_usb_int_disable(uint32_t flags);
extern void ald_usb_int_enable(uint32_t flags);
extern uint32_t ald_usb_int_status_get(void);
extern void ald_usb_int_disable_ep(uint32_t flags);
extern void ald_usb_int_enable_ep(uint32_t flags);
extern uint32_t ald_usb_int_status_ep_get(void);
extern void ald_usb_int_register(void);
extern void ald_usb_int_unregister(void);
extern uint32_t ald_usb_int_num_get(void);
/**
  * @}
  */

/** @addtogroup USB_Public_Functions_Group7
  * @{
  */
/* DMA functions */
extern void ald_usb_dma_channel_config(uint8_t ch, uint32_t addr, uint32_t count, uint32_t ctrl);
extern void ald_usb_dma_mult_recv_start(uint32_t ep_idx);
extern void ald_usb_dma_channel_start(uint8_t ch);
extern void ald_usb_dma_channel_stop(uint8_t ch);
extern uint32_t ald_usb_dma_get_interrupt_flag(void);
extern uint32_t ald_usb_dma_get_channel_error(uint8_t ch);
extern void ald_usb_dma_clear_channel_error(uint8_t ch);
/**
  * @}
  */

/** @addtogroup USB_Public_Functions_Group8
  * @{
  */
/* LPM functions */
extern void ald_usb_host_lpm_send(uint32_t addr, uint32_t ep_idx);
extern void ald_usb_host_lpm_config(uint32_t resume_time, uint32_t config);
extern uint32_t ald_usb_lpm_remote_wake_is_enable(void);
extern void ald_usb_host_lpm_resume(void);
extern void ald_usb_dev_lpm_remote_wake(void);
extern void ald_usb_dev_lpm_config(uint32_t config);
extern void ald_usb_dev_lpm_enable(void);
extern void ald_usb_dev_lpm_disable(void);
extern uint32_t ald_usb_lpm_link_status_get(void);
extern uint32_t ald_usb_lpm_ep_get(void);
extern uint32_t ald_usb_lpm_int_status_get(void);
extern void ald_usb_lpm_int_disable(uint32_t ints);
extern void ald_usb_lpm_int_enable(uint32_t ints);
/**
  * @}
  */

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
