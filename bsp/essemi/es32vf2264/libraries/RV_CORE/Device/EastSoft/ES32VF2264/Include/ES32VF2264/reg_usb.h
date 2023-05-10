/**
  **************************************************************************************
  * @file    reg_usb.h
  * @brief   USB Head File
  * @data    5/22/2018
  * @author  Eastsoft AE Team
  * @note
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  **************************************************************************************
  */

#ifndef __REG_USB_H__
#define __REG_USB_H__


/******************************************************************************/
/*                                 特殊结构体定义                             */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
/* #pragma anon_unions */

/****************** Bit definition for USB_FADDR register ************************/

#define USB_FADDR_ADDR_POSS 0U
#define USB_FADDR_ADDR_POSE 6U
#define USB_FADDR_ADDR_MSK BITS(USB_FADDR_ADDR_POSS,USB_FADDR_ADDR_POSE)

/****************** Bit definition for USB_POWER register ************************/

/* device/host mode */
#define USB_POWER_ISOUDT_POS 7U
#define USB_POWER_ISOUDT_MSK BIT(USB_POWER_ISOUDT_POS)

/* device mode */
#define USB_POWER_RESET_POS 3U
#define USB_POWER_RESET_MSK BIT(USB_POWER_RESET_POS)

#define USB_POWER_RESUME_POS 2U
#define USB_POWER_RESUME_MSK BIT(USB_POWER_RESUME_POS)

#define USB_POWER_SUSPEND_POS 1U
#define USB_POWER_SUSPEND_MSK BIT(USB_POWER_SUSPEND_POS)

/* device mode */
#define USB_POWER_SUSPENDEN_POS 0U
#define USB_POWER_SUSPENDEN_MSK BIT(USB_POWER_SUSPENDEN_POS)

/****************** Bit definition for USB_DPDMCON register ************************/

#define USB_DPDMCON_DPPUD_POSS 3U
#define USB_DPDMCON_DPPUD_POSE 4U
#define USB_DPDMCON_DPPUD_MSK BITS(USB_DPDMCON_DPPUD_POSS,USB_DPDMCON_DPPUD_POSE)

#define USB_DPDMCON_DMPUD_POSS 1U
#define USB_DPDMCON_DMPUD_POSE 2U
#define USB_DPDMCON_DMPUD_MSK BITS(USB_DPDMCON_DMPUD_POSS,USB_DPDMCON_DMPUD_POSE)

#define USB_DPDMCON_PHYPWREN_POS 0U
#define USB_DPDMCON_PHYPWREN_MSK BIT(USB_DPDMCON_PHYPWREN_POS)

/****************** Bit definition for USB_SWCID register ************************/

#define USB_SWCID_HOST_POS 1U
#define USB_SWCID_HOST_MSK BIT(USB_SWCID_HOST_POS)

#define USB_SWCID_CIDCTRL_POS 0U
#define USB_SWCID_CIDCTRL_MSK BIT(USB_SWCID_CIDCTRL_POS)

/****************** Bit definition for USB_SWVBUS register ************************/

#define USB_SWVBUS_VALTH_POS 3U
#define USB_SWVBUS_VALTH_MSK BIT(USB_SWVBUS_VALTH_POS)

#define USB_SWVBUS_SESVALTH_POS 2U
#define USB_SWVBUS_SESVALTH_MSK BIT(USB_SWVBUS_SESVALTH_POS)

#define USB_SWVBUS_SESENDTH_POS 1U
#define USB_SWVBUS_SESENDTH_MSK BIT(USB_SWVBUS_SESENDTH_POS)

#define USB_SWVBUS_SIGCTRL_POS 0U
#define USB_SWVBUS_SIGCTRL_MSK BIT(USB_SWVBUS_SIGCTRL_POS)

/****************** Bit definition for USB_TMODE register ************************/

#define USB_TMODE_PROTECT_POSS 2U
#define USB_TMODE_PROTECT_POSE 7U
#define USB_TMODE_PROTECT_MSK BITS(USB_TMODE_PROTECT_POSS,USB_TMODE_PROTECT_POSE)

#define USB_TMODE_MEMTST_EN_POS 1U
#define USB_TMODE_MEMTST_EN_MSK BIT(USB_TMODE_MEMTST_EN_POS)
#define USB_TMODE_MEMTST_EN     USB_TMODE_MEMTST_EN_MSK

#define USB_TMODE_ENABLE_POS 0U
#define USB_TMODE_ENABLE_MSK BIT(USB_TMODE_ENABLE_POS)

/****************** Bit definition for USB_FRAME1 register ************************/

#define USB_FRAME1_LOWFRAME_POSS 0U
#define USB_FRAME1_LOWFRAME_POSE 7U
#define USB_FRAME1_LOWFRAME_MSK BITS(USB_FRAME1_LOWFRAME_POSS,USB_FRAME1_LOWFRAME_POSE)

/****************** Bit definition for USB_FRAME2 register ************************/

#define USB_FRAME2_UPFRAME_POSS 0U
#define USB_FRAME2_UPFRAME_POSE 2U
#define USB_FRAME2_UPFRAME_MSK BITS(USB_FRAME2_UPFRAME_POSS,USB_FRAME2_UPFRAME_POSE)

/****************** Bit definition for USB_INDEX register ************************/

#define USB_INDEX_EPTIDX_POSS 0U
#define USB_INDEX_EPTIDX_POSE 3U
#define USB_INDEX_EPTIDX_MSK BITS(USB_INDEX_EPTIDX_POSS,USB_INDEX_EPTIDX_POSE)

/****************** Bit definition for USB_DEVCON register ************************/

#define USB_DEVCON_FSDEV_POS 6U
#define USB_DEVCON_FSDEV_MSK BIT(USB_DEVCON_FSDEV_POS)

#define USB_DEVCON_LSDEV_POS 5U
#define USB_DEVCON_LSDEV_MSK BIT(USB_DEVCON_LSDEV_POS)

#define USB_DEVCON_HOST_POS 2U
#define USB_DEVCON_HOST_MSK BIT(USB_DEVCON_HOST_POS)

#define USB_DEVCON_HOSTREQ_POS 1U
#define USB_DEVCON_HOSTREQ_MSK BIT(USB_DEVCON_HOSTREQ_POS)

#define USB_DEVCON_SESSION_POS 0U
#define USB_DEVCON_SESSION_MSK BIT(USB_DEVCON_SESSION_POS)

/****************** Bit definition for USB_TXMAXP register ************************/

#define USB_TXMAXP_MAXSIZE_POSS 0U
#define USB_TXMAXP_MAXSIZE_POSE 7U
#define USB_TXMAXP_MAXSIZE_MSK BITS(USB_TXMAXP_MAXSIZE_POSS,USB_TXMAXP_MAXSIZE_POSE)

/****************** Bit definition for USB_CSR0L_TXCSRL register ************************/

/* Endpoint 0 */
/* device mode */
#define USB_CSR0L_SETENDC_POS 7U
#define USB_CSR0L_SETENDC_MSK BIT(USB_CSR0L_SETENDC_POS)

#define USB_CSR0L_RXRDYC_POS 6U
#define USB_CSR0L_RXRDYC_MSK BIT(USB_CSR0L_RXRDYC_POS)

#define USB_CSR0L_STALL_POS 5U
#define USB_CSR0L_STALL_MSK BIT(USB_CSR0L_STALL_POS)

#define USB_CSR0L_SETEND_POS 4U
#define USB_CSR0L_SETEND_MSK BIT(USB_CSR0L_SETEND_POS)

#define USB_CSR0L_DATAEND_POS 3U
#define USB_CSR0L_DATAEND_MSK BIT(USB_CSR0L_DATAEND_POS)

/* host mode */
#define USB_CSR0L_NAKTO_POS 7U
#define USB_CSR0L_NAKTO_MSK BIT(USB_CSR0L_NAKTO_POS)

#define USB_CSR0L_STATUSPKT_POS 6U
#define USB_CSR0L_STATUSPKT_MSK BIT(USB_CSR0L_STATUSPKT_POS)

#define USB_CSR0L_REQPKT_POS 5U
#define USB_CSR0L_REQPKT_MSK BIT(USB_CSR0L_REQPKT_POS)

#define USB_CSR0L_ERROR_POS 4U
#define USB_CSR0L_ERROR_MSK BIT(USB_CSR0L_ERROR_POS)

#define USB_CSR0L_SETUPPKT_POS 3U
#define USB_CSR0L_SETUPPKT_MSK BIT(USB_CSR0L_SETUPPKT_POS)

/* device/host mode */
#define USB_CSR0L_STALLED_POS 2U
#define USB_CSR0L_STALLED_MSK BIT(USB_CSR0L_STALLED_POS)

#define USB_CSR0L_TXRDY_POS 1U
#define USB_CSR0L_TXRDY_MSK BIT(USB_CSR0L_TXRDY_POS)

#define USB_CSR0L_RXRDY_POS 0U
#define USB_CSR0L_RXRDY_MSK BIT(USB_CSR0L_RXRDY_POS)

/* Endpoint 1-6 */
/* host mode */
#define USB_TXCSRL_NAKTO_POS 7U
#define USB_TXCSRL_NAKTO_MSK BIT(USB_TXCSRL_NAKTO_POS)

/* device/host mode */
#define USB_TXCSRL_CLRDT_POS 6U
#define USB_TXCSRL_CLRDT_MSK BIT(USB_TXCSRL_CLRDT_POS)

#define USB_TXCSRL_STALLED_POS 5U
#define USB_TXCSRL_STALLED_MSK BIT(USB_TXCSRL_STALLED_POS)

/* device mode */
#define USB_TXCSRL_STALL_POS 4U
#define USB_TXCSRL_STALL_MSK BIT(USB_TXCSRL_STALL_POS)

/* device/host mode */
#define USB_TXCSRL_FLUSH_POS 3U
#define USB_TXCSRL_FLUSH_MSK BIT(USB_TXCSRL_FLUSH_POS)

/* device mode */
#define USB_TXCSRL_UNDRUN_POS 2U
#define USB_TXCSRL_UNDRUN_MSK BIT(USB_TXCSRL_UNDRUN_POS)

/* host mode */
#define USB_TXCSRL_ERROR_POS 2U
#define USB_TXCSRL_ERROR_MSK BIT(USB_TXCSRL_ERROR_POS)

/* device/host mode */
#define USB_TXCSRL_FIFONE_POS 1U
#define USB_TXCSRL_FIFONE_MSK BIT(USB_TXCSRL_FIFONE_POS)

#define USB_TXCSRL_TXRDY_POS 0U
#define USB_TXCSRL_TXRDY_MSK BIT(USB_TXCSRL_TXRDY_POS)

/****************** Bit definition for USB_CSR0H_TXCSRH register ************************/

/* Endpoint 0 */
/* device/host mode */
#define USB_CSR0H_FLUSH_POS 0U
#define USB_CSR0H_FLUSH_MSK BIT(USB_CSR0H_FLUSH_POS)

/* For endpoint 1-6 */
/* device/host mode */
#define USB_TXCSRH_AUTOSET_POS 7U
#define USB_TXCSRH_AUTOSET_MSK BIT(USB_TXCSRH_AUTOSET_POS)

#define USB_TXCSRH_ISO_POS 6U
#define USB_TXCSRH_ISO_MSK BIT(USB_TXCSRH_ISO_POS)

#define USB_TXCSRH_MODE_POS 5U
#define USB_TXCSRH_MODE_MSK BIT(USB_TXCSRH_MODE_POS)

#define USB_TXCSRH_FDT_POS 3U
#define USB_TXCSRH_FDT_MSK BIT(USB_TXCSRH_FDT_POS)

/****************** Bit definition for USB_RXMAXP register ************************/

#define USB_RXMAXP_MAXSIZE_POSS 0U
#define USB_RXMAXP_MAXSIZE_POSE 7U
#define USB_RXMAXP_MAXSIZE_MSK BITS(USB_RXMAXP_MAXSIZE_POSS,USB_RXMAXP_MAXSIZE_POSE)

/****************** Bit definition for USB_RXCSRL register ************************/

/* device/host mode */
#define USB_RXCSRL_CLRDT_POS 7U
#define USB_RXCSRL_CLRDT_MSK BIT(USB_RXCSRL_CLRDT_POS)

#define USB_RXCSRL_STALLED_POS 6U
#define USB_RXCSRL_STALLED_MSK BIT(USB_RXCSRL_STALLED_POS)

/* device mode */
#define USB_RXCSRL_STALL_POS 5U
#define USB_RXCSRL_STALL_MSK BIT(USB_RXCSRL_STALL_POS)

/* host mode */
#define USB_RXCSRL_REQPKT_POS 5U
#define USB_RXCSRL_REQPKT_MSK BIT(USB_RXCSRL_REQPKT_POS)

/* device/host mode */
#define USB_RXCSRL_FLUSH_POS 4U
#define USB_RXCSRL_FLUSH_MSK BIT(USB_RXCSRL_FLUSH_POS)

/* device/host mode */
#define USB_RXCSRL_DATAERR_POS 3U
#define USB_RXCSRL_DATAERR_MSK BIT(USB_RXCSRL_DATAERR_POS)

/* host mode */
#define USB_RXCSRL_NAKTO_POS 3U
#define USB_RXCSRL_NAKTO_MSK BIT(USB_RXCSRL_NAKTO_POS)

/* device mode */
#define USB_RXCSRL_OVERRUN_POS 2U
#define USB_RXCSRL_OVERRUN_MSK BIT(USB_RXCSRL_OVERRUN_POS)

/* host mode */
#define USB_RXCSRL_ERROR_POS 2U
#define USB_RXCSRL_ERROR_MSK BIT(USB_RXCSRL_ERROR_POS)

/* device/host mode */
#define USB_RXCSRL_FULL_POS 1U
#define USB_RXCSRL_FULL_MSK BIT(USB_RXCSRL_FULL_POS)

#define USB_RXCSRL_RXRDY_POS 0U
#define USB_RXCSRL_RXRDY_MSK BIT(USB_RXCSRL_RXRDY_POS)

/****************** Bit definition for USB_RXCSRH register ************************/

/* device/host mode */
#define USB_RXCSRH_AUTOCLR_POS 7U
#define USB_RXCSRH_AUTOCLR_MSK BIT(USB_RXCSRH_AUTOCLR_POS)

/* device mode */
#define USB_RXCSRH_ISO_POS 6U
#define USB_RXCSRH_ISO_MSK BIT(USB_RXCSRH_ISO_POS)

/* host mode */
#define USB_RXCSRH_AUTOREQ_POS 6U
#define USB_RXCSRH_AUTOREQ_MSK BIT(USB_RXCSRH_AUTOREQ_POS)

/****************** Bit definition for USB_COUNT0_RX1 register ************************/

/* Endpoint 0 */
#define USB_COUNT0_COUNT_POSS 0U
#define USB_COUNT0_COUNT_POSE 6U
#define USB_COUNT0_COUNT_MSK BITS(USB_COUNT0_COUNT_POSS,USB_COUNT0_COUNT_POSE)

//
//For endpoint 1-6
//
#define USB_RX1_PKTLOW_POSS 0U
#define USB_RX1_PKTLOW_POSE 7U
#define USB_RX1_PKTLOW_MSK BITS(USB_RX1_PKTLOW_POSS,USB_RX1_PKTLOW_POSE)

/****************** Bit definition for USB_RXCOUNT2 register ************************/

#define USB_RXCOUNT2_PKTHIGH_POSS 0U
#define USB_RXCOUNT2_PKTHIGH_POSE 2U
#define USB_RXCOUNT2_PKTHIGH_MSK BITS(USB_RXCOUNT2_PKTHIGH_POSS,USB_RXCOUNT2_PKTHIGH_POSE)

/****************** Bit definition for USB_TXTYPE register ************************/

#define USB_TXTYPE_PROTOCOL_POSS 4U
#define USB_TXTYPE_PROTOCOL_POSE 5U
#define USB_TXTYPE_PROTOCOL_MSK BITS(USB_TXTYPE_PROTOCOL_POSS,USB_TXTYPE_PROTOCOL_POSE)

#define USB_TXTYPE_TEPN_POSS 0U
#define USB_TXTYPE_TEPN_POSE 3U
#define USB_TXTYPE_TEPN_MSK BITS(USB_TXTYPE_TEPN_POSS,USB_TXTYPE_TEPN_POSE)

/****************** Bit definition for USB_NAKLIMIT0_TXINTERVAL register ************************/

/* Endpoint 0 */
#define USB_NAKLIMIT0_NAKLMT_POSS 0U
#define USB_NAKLIMIT0_NAKLMT_POSE 7U
#define USB_NAKLIMIT0_NAKLMT_MSK BITS(USB_NAKLIMIT0_NAKLMT_POSS,USB_NAKLIMIT0_NAKLMT_POSE)

/* For endpoint 1-6 */
#define USB_TXINTERVAL_TXPOLL_POSS 0U
#define USB_TXINTERVAL_TXPOLL_POSE 7U
#define USB_TXINTERVAL_TXPOLL_MSK BITS(USB_TXINTERVAL_TXPOLL_POSS,USB_TXINTERVAL_TXPOLL_POSE)

#define USB_TXINTERVAL_NAKLMT_POSS 0U
#define USB_TXINTERVAL_NAKLMT_POSE 7U
#define USB_TXINTERVAL_NAKLMT_MSK BITS(USB_TXINTERVAL_NAKLMT_POSS,USB_TXINTERVAL_NAKLMT_POSE)

/****************** Bit definition for USB_RXTYPE register ************************/

#define USB_RXTYPE_PROTOCOL_POSS 4U
#define USB_RXTYPE_PROTOCOL_POSE 5U
#define USB_RXTYPE_PROTOCOL_MSK BITS(USB_RXTYPE_PROTOCOL_POSS,USB_RXTYPE_PROTOCOL_POSE)

#define USB_RXTYPE_TEPN_POSS 0U
#define USB_RXTYPE_TEPN_POSE 3U
#define USB_RXTYPE_TEPN_MSK BITS(USB_RXTYPE_TEPN_POSS,USB_RXTYPE_TEPN_POSE)

/****************** Bit definition for USB_RXINTERVAL register ************************/

#define USB_RXINTERVAL_RXPOLL_POSS 0U
#define USB_RXINTERVAL_RXPOLL_POSE 7U
#define USB_RXINTERVAL_RXPOLL_MSK BITS(USB_RXINTERVAL_RXPOLL_POSS,USB_RXINTERVAL_RXPOLL_POSE)

#define USB_RXINTERVAL_NAKLMT_POSS 0U
#define USB_RXINTERVAL_NAKLMT_POSE 7U
#define USB_RXINTERVAL_NAKLMT_MSK BITS(USB_RXINTERVAL_NAKLMT_POSS,USB_RXINTERVAL_NAKLMT_POSE)

/****************** Bit definition for USB_TXFIFO1 register ************************/

#define USB_TXFIFO1_ADDRL_POSS 0U
#define USB_TXFIFO1_ADDRL_POSE 7U
#define USB_TXFIFO1_ADDRL_MSK BITS(USB_TXFIFO1_ADDRL_POSS,USB_TXFIFO1_ADDRL_POSE)

/****************** Bit definition for USB_TXFIFO2 register ************************/

#define USB_TXFIFO2_MAXPKTSIZE_POSS 5U
#define USB_TXFIFO2_MAXPKTSIZE_POSE 7U
#define USB_TXFIFO2_MAXPKTSIZE_MSK BITS(USB_TXFIFO2_MAXPKTSIZE_POSS,USB_TXFIFO2_MAXPKTSIZE_POSE)

#define USB_TXFIFO2_DPB_POS 4U
#define USB_TXFIFO2_DPB_MSK BIT(USB_TXFIFO2_DPB_POS)

#define USB_TXFIFO2_ADDRH_POSS 0U
#define USB_TXFIFO2_ADDRH_POSE 3U
#define USB_TXFIFO2_ADDRH_MSK BITS(USB_TXFIFO2_ADDRH_POSS,USB_TXFIFO2_ADDRH_POSE)

/****************** Bit definition for USB_RXFIFO1 register ************************/

#define USB_RXFIFO1_ADDRL_POSS 0U
#define USB_RXFIFO1_ADDRL_POSE 7U
#define USB_RXFIFO1_ADDRL_MSK BITS(USB_RXFIFO1_ADDRL_POSS,USB_RXFIFO1_ADDRL_POSE)

/****************** Bit definition for USB_RXFIFO2 register ************************/

#define USB_RXFIFO2_MAXPKTSIZE_POSS 5U
#define USB_RXFIFO2_MAXPKTSIZE_POSE 7U
#define USB_RXFIFO2_MAXPKTSIZE_MSK BITS(USB_RXFIFO2_MAXPKTSIZE_POSS,USB_RXFIFO2_MAXPKTSIZE_POSE)

#define USB_RXFIFO2_DPB_POS 4U
#define USB_RXFIFO2_DPB_MSK BIT(USB_RXFIFO2_DPB_POS)

#define USB_RXFIFO2_ADDRH_POSS 0U
#define USB_RXFIFO2_ADDRH_POSE 3U
#define USB_RXFIFO2_ADDRH_MSK BITS(USB_RXFIFO2_ADDRH_POSS,USB_RXFIFO2_ADDRH_POSE)

/************* Bit definition for USB_EP0FIFO/USB_EPxFIFO register *****************/

#define USB_EP0FIFO_FIFO0_POSS 0U
#define USB_EP0FIFO_FIFO0_POSE 7U
#define USB_EP0FIFO_FIFO0_MSK BITS(USB_EP0FIFO_FIFO0_POSS,USB_EP0FIFO_FIFO0_POSE)

#define USB_EP1FIFO_FIFO1_POSS 0U
#define USB_EP1FIFO_FIFO1_POSE 7U
#define USB_EP1FIFO_FIFO1_MSK BITS(USB_EP1FIFO_FIFO1_POSS,USB_EP1FIFO_FIFO1_POSE)

#define USB_EP2FIFO_FIFO2_POSS 0U
#define USB_EP2FIFO_FIFO2_POSE 7U
#define USB_EP2FIFO_FIFO2_MSK BITS(USB_EP2FIFO_FIFO2_POSS,USB_EP2FIFO_FIFO2_POSE)

#define USB_EP3FIFO_FIFO3_POSS 0U
#define USB_EP3FIFO_FIFO3_POSE 7U
#define USB_EP3FIFO_FIFO3_MSK BITS(USB_EP3FIFO_FIFO3_POSS,USB_EP3FIFO_FIFO3_POSE)

#define USB_EP4FIFO_FIFO4_POSS 0U
#define USB_EP4FIFO_FIFO4_POSE 7U
#define USB_EP4FIFO_FIFO4_MSK BITS(USB_EP4FIFO_FIFO4_POSS,USB_EP4FIFO_FIFO4_POSE)

#define USB_EP5FIFO_FIFO5_POSS 0U
#define USB_EP5FIFO_FIFO5_POSE 7U
#define USB_EP5FIFO_FIFO5_MSK BITS(USB_EP5FIFO_FIFO5_POSS,USB_EP5FIFO_FIFO5_POSE)

#define USB_EP6FIFO_FIFO6_POSS 0U
#define USB_EP6FIFO_FIFO6_POSE 7U
#define USB_EP6FIFO_FIFO6_MSK BITS(USB_EP6FIFO_FIFO6_POSS,USB_EP6FIFO_FIFO6_POSE)

#define USB_EPxFIFO_FIFOx_POSS 0U
#define USB_EPxFIFO_FIFOx_POSE 7U
#define USB_EPxFIFO_FIFOx_MSK BITS(USB_EPxFIFO_FIFOx_POSS,USB_EPxFIFO_FIFOx_POSE)

/****************** Bit definition for USB_TXIER register ************************/

#define USB_TXIER_EP6IE_POS 6U
#define USB_TXIER_EP6IE_MSK BIT(USB_TXIER_EP6IE_POS)

#define USB_TXIER_EP5IE_POS 5U
#define USB_TXIER_EP5IE_MSK BIT(USB_TXIER_EP5IE_POS)

#define USB_TXIER_EP4IE_POS 4U
#define USB_TXIER_EP4IE_MSK BIT(USB_TXIER_EP4IE_POS)

#define USB_TXIER_EP3IE_POS 3U
#define USB_TXIER_EP3IE_MSK BIT(USB_TXIER_EP3IE_POS)

#define USB_TXIER_EP2IE_POS 2U
#define USB_TXIER_EP2IE_MSK BIT(USB_TXIER_EP2IE_POS)

#define USB_TXIER_EP1IE_POS 1U
#define USB_TXIER_EP1IE_MSK BIT(USB_TXIER_EP1IE_POS)

#define USB_TXIER_EP0IE_POS 0U
#define USB_TXIER_EP0IE_MSK BIT(USB_TXIER_EP0IE_POS)

/****************** Bit definition for USB_RXIER register ************************/

#define USB_RXIER_EP6IE_POS 6U
#define USB_RXIER_EP6IE_MSK BIT(USB_RXIER_EP6IE_POS)

#define USB_RXIER_EP5IE_POS 5U
#define USB_RXIER_EP5IE_MSK BIT(USB_RXIER_EP5IE_POS)

#define USB_RXIER_EP4IE_POS 4U
#define USB_RXIER_EP4IE_MSK BIT(USB_RXIER_EP4IE_POS)

#define USB_RXIER_EP3IE_POS 3U
#define USB_RXIER_EP3IE_MSK BIT(USB_RXIER_EP3IE_POS)

#define USB_RXIER_EP2IE_POS 2U
#define USB_RXIER_EP2IE_MSK BIT(USB_RXIER_EP2IE_POS)

#define USB_RXIER_EP1IE_POS 1U
#define USB_RXIER_EP1IE_MSK BIT(USB_RXIER_EP1IE_POS)

/****************** Bit definition for USB_TXIDR register ************************/

#define USB_TXIDR_EP6ID_POS 6U
#define USB_TXIDR_EP6ID_MSK BIT(USB_TXIDR_EP6ID_POS)

#define USB_TXIDR_EP5ID_POS 5U
#define USB_TXIDR_EP5ID_MSK BIT(USB_TXIDR_EP5ID_POS)

#define USB_TXIDR_EP4ID_POS 4U
#define USB_TXIDR_EP4ID_MSK BIT(USB_TXIDR_EP4ID_POS)

#define USB_TXIDR_EP3ID_POS 3U
#define USB_TXIDR_EP3ID_MSK BIT(USB_TXIDR_EP3ID_POS)

#define USB_TXIDR_EP2ID_POS 2U
#define USB_TXIDR_EP2ID_MSK BIT(USB_TXIDR_EP2ID_POS)

#define USB_TXIDR_EP1ID_POS 1U
#define USB_TXIDR_EP1ID_MSK BIT(USB_TXIDR_EP1ID_POS)

#define USB_TXIDR_EP0ID_POS 0U
#define USB_TXIDR_EP0ID_MSK BIT(USB_TXIDR_EP0ID_POS)

/****************** Bit definition for USB_RXIDR register ************************/

#define USB_RXIDR_EP6ID_POS 6U
#define USB_RXIDR_EP6ID_MSK BIT(USB_RXIDR_EP6ID_POS)

#define USB_RXIDR_EP5ID_POS 5U
#define USB_RXIDR_EP5ID_MSK BIT(USB_RXIDR_EP5ID_POS)

#define USB_RXIDR_EP4ID_POS 4U
#define USB_RXIDR_EP4ID_MSK BIT(USB_RXIDR_EP4ID_POS)

#define USB_RXIDR_EP3ID_POS 3U
#define USB_RXIDR_EP3ID_MSK BIT(USB_RXIDR_EP3ID_POS)

#define USB_RXIDR_EP2ID_POS 2U
#define USB_RXIDR_EP2ID_MSK BIT(USB_RXIDR_EP2ID_POS)

#define USB_RXIDR_EP1ID_POS 1U
#define USB_RXIDR_EP1ID_MSK BIT(USB_RXIDR_EP1ID_POS)

/****************** Bit definition for USB_TXIVS register ************************/

#define USB_TXIVS_EP6IVS_POS 6U
#define USB_TXIVS_EP6IVS_MSK BIT(USB_TXIVS_EP6IVS_POS)

#define USB_TXIVS_EP5IVS_POS 5U
#define USB_TXIVS_EP5IVS_MSK BIT(USB_TXIVS_EP5IVS_POS)

#define USB_TXIVS_EP4IVS_POS 4U
#define USB_TXIVS_EP4IVS_MSK BIT(USB_TXIVS_EP4IVS_POS)

#define USB_TXIVS_EP3IVS_POS 3U
#define USB_TXIVS_EP3IVS_MSK BIT(USB_TXIVS_EP3IVS_POS)

#define USB_TXIVS_EP2IVS_POS 2U
#define USB_TXIVS_EP2IVS_MSK BIT(USB_TXIVS_EP2IVS_POS)

#define USB_TXIVS_EP1IVS_POS 1U
#define USB_TXIVS_EP1IVS_MSK BIT(USB_TXIVS_EP1IVS_POS)

#define USB_TXIVS_EP0IVS_POS 0U
#define USB_TXIVS_EP0IVS_MSK BIT(USB_TXIVS_EP0IVS_POS)

/****************** Bit definition for USB_RXIVS register ************************/

#define USB_RXIVS_EP6IVS_POS 6U
#define USB_RXIVS_EP6IVS_MSK BIT(USB_RXIVS_EP6IVS_POS)

#define USB_RXIVS_EP5IVS_POS 5U
#define USB_RXIVS_EP5IVS_MSK BIT(USB_RXIVS_EP5IVS_POS)

#define USB_RXIVS_EP4IVS_POS 4U
#define USB_RXIVS_EP4IVS_MSK BIT(USB_RXIVS_EP4IVS_POS)

#define USB_RXIVS_EP3IVS_POS 3U
#define USB_RXIVS_EP3IVS_MSK BIT(USB_RXIVS_EP3IVS_POS)

#define USB_RXIVS_EP2IVS_POS 2U
#define USB_RXIVS_EP2IVS_MSK BIT(USB_RXIVS_EP2IVS_POS)

#define USB_RXIVS_EP1IVS_POS 1U
#define USB_RXIVS_EP1IVS_MSK BIT(USB_RXIVS_EP1IVS_POS)

/****************** Bit definition for USB_TXRIF register ************************/

#define USB_TXRIF_EP6RIF_POS 6U
#define USB_TXRIF_EP6RIF_MSK BIT(USB_TXRIF_EP6RIF_POS)

#define USB_TXRIF_EP5RIF_POS 5U
#define USB_TXRIF_EP5RIF_MSK BIT(USB_TXRIF_EP5RIF_POS)

#define USB_TXRIF_EP4RIF_POS 4U
#define USB_TXRIF_EP4RIF_MSK BIT(USB_TXRIF_EP4RIF_POS)

#define USB_TXRIF_EP3RIF_POS 3U
#define USB_TXRIF_EP3RIF_MSK BIT(USB_TXRIF_EP3RIF_POS)

#define USB_TXRIF_EP2RIF_POS 2U
#define USB_TXRIF_EP2RIF_MSK BIT(USB_TXRIF_EP2RIF_POS)

#define USB_TXRIF_EP1RIF_POS 1U
#define USB_TXRIF_EP1RIF_MSK BIT(USB_TXRIF_EP1RIF_POS)

#define USB_TXRIF_EP0RIF_POS 0U
#define USB_TXRIF_EP0RIF_MSK BIT(USB_TXRIF_EP0RIF_POS)

/****************** Bit definition for USB_RXRIF register ************************/

#define USB_RXRIF_EP6RIF_POS 6U
#define USB_RXRIF_EP6RIF_MSK BIT(USB_RXRIF_EP6RIF_POS)

#define USB_RXRIF_EP5RIF_POS 5U
#define USB_RXRIF_EP5RIF_MSK BIT(USB_RXRIF_EP5RIF_POS)

#define USB_RXRIF_EP4RIF_POS 4U
#define USB_RXRIF_EP4RIF_MSK BIT(USB_RXRIF_EP4RIF_POS)

#define USB_RXRIF_EP3RIF_POS 3U
#define USB_RXRIF_EP3RIF_MSK BIT(USB_RXRIF_EP3RIF_POS)

#define USB_RXRIF_EP2RIF_POS 2U
#define USB_RXRIF_EP2RIF_MSK BIT(USB_RXRIF_EP2RIF_POS)

#define USB_RXRIF_EP1RIF_POS 1U
#define USB_RXRIF_EP1RIF_MSK BIT(USB_RXRIF_EP1RIF_POS)

/****************** Bit definition for USB_TXIFM register ************************/

#define USB_TXIFM_EP6IFM_POS 6U
#define USB_TXIFM_EP6IFM_MSK BIT(USB_TXIFM_EP6IFM_POS)

#define USB_TXIFM_EP5IFM_POS 5U
#define USB_TXIFM_EP5IFM_MSK BIT(USB_TXIFM_EP5IFM_POS)

#define USB_TXIFM_EP4IFM_POS 4U
#define USB_TXIFM_EP4IFM_MSK BIT(USB_TXIFM_EP4IFM_POS)

#define USB_TXIFM_EP3IFM_POS 3U
#define USB_TXIFM_EP3IFM_MSK BIT(USB_TXIFM_EP3IFM_POS)

#define USB_TXIFM_EP2IFM_POS 2U
#define USB_TXIFM_EP2IFM_MSK BIT(USB_TXIFM_EP2IFM_POS)

#define USB_TXIFM_EP1IFM_POS 1U
#define USB_TXIFM_EP1IFM_MSK BIT(USB_TXIFM_EP1IFM_POS)

#define USB_TXIFM_EP0IFM_POS 0U
#define USB_TXIFM_EP0IFM_MSK BIT(USB_TXIFM_EP0IFM_POS)

/****************** Bit definition for USB_RXIFM register ************************/

#define USB_RXIFM_EP6IFM_POS 6U
#define USB_RXIFM_EP6IFM_MSK BIT(USB_RXIFM_EP6IFM_POS)

#define USB_RXIFM_EP5IFM_POS 5U
#define USB_RXIFM_EP5IFM_MSK BIT(USB_RXIFM_EP5IFM_POS)

#define USB_RXIFM_EP4IFM_POS 4U
#define USB_RXIFM_EP4IFM_MSK BIT(USB_RXIFM_EP4IFM_POS)

#define USB_RXIFM_EP3IFM_POS 3U
#define USB_RXIFM_EP3IFM_MSK BIT(USB_RXIFM_EP3IFM_POS)

#define USB_RXIFM_EP2IFM_POS 2U
#define USB_RXIFM_EP2IFM_MSK BIT(USB_RXIFM_EP2IFM_POS)

#define USB_RXIFM_EP1IFM_POS 1U
#define USB_RXIFM_EP1IFM_MSK BIT(USB_RXIFM_EP1IFM_POS)

/****************** Bit definition for USB_TXICR register ************************/

#define USB_TXICR_EP6ICR_POS 6U
#define USB_TXICR_EP6ICR_MSK BIT(USB_TXICR_EP6ICR_POS)

#define USB_TXICR_EP5ICR_POS 5U
#define USB_TXICR_EP5ICR_MSK BIT(USB_TXICR_EP5ICR_POS)

#define USB_TXICR_EP4ICR_POS 4U
#define USB_TXICR_EP4ICR_MSK BIT(USB_TXICR_EP4ICR_POS)

#define USB_TXICR_EP3ICR_POS 3U
#define USB_TXICR_EP3ICR_MSK BIT(USB_TXICR_EP3ICR_POS)

#define USB_TXICR_EP2ICR_POS 2U
#define USB_TXICR_EP2ICR_MSK BIT(USB_TXICR_EP2ICR_POS)

#define USB_TXICR_EP1ICR_POS 1U
#define USB_TXICR_EP1ICR_MSK BIT(USB_TXICR_EP1ICR_POS)

#define USB_TXICR_EP0ICR_POS 0U
#define USB_TXICR_EP0ICR_MSK BIT(USB_TXICR_EP0ICR_POS)

/****************** Bit definition for USB_RXICR register ************************/

#define USB_RXICR_EP6ICR_POS 6U
#define USB_RXICR_EP6ICR_MSK BIT(USB_RXICR_EP6ICR_POS)

#define USB_RXICR_EP5ICR_POS 5U
#define USB_RXICR_EP5ICR_MSK BIT(USB_RXICR_EP5ICR_POS)

#define USB_RXICR_EP4ICR_POS 4U
#define USB_RXICR_EP4ICR_MSK BIT(USB_RXICR_EP4ICR_POS)

#define USB_RXICR_EP3ICR_POS 3U
#define USB_RXICR_EP3ICR_MSK BIT(USB_RXICR_EP3ICR_POS)

#define USB_RXICR_EP2ICR_POS 2U
#define USB_RXICR_EP2ICR_MSK BIT(USB_RXICR_EP2ICR_POS)

#define USB_RXICR_EP1ICR_POS 1U
#define USB_RXICR_EP1ICR_MSK BIT(USB_RXICR_EP1ICR_POS)

/****************** Bit definition for USB_IER register ************************/

/* device/host mode */
#define USB_IER_SESREQIE_POS 6U
#define USB_IER_SESREQIE_MSK BIT(USB_IER_SESREQIE_POS)

#define USB_IER_DISCONIE_POS 5U
#define USB_IER_DISCONIE_MSK BIT(USB_IER_DISCONIE_POS)

/* host mode */
#define USB_IER_CONIE_POS 4U
#define USB_IER_CONIE_MSK BIT(USB_IER_CONIE_POS)

/* device/host mode */
#define USB_IER_SOFIE_POS 3U
#define USB_IER_SOFIE_MSK BIT(USB_IER_SOFIE_POS)

/* device mode */
#define USB_IER_RESTIE_POS 2U
#define USB_IER_RESTIE_MSK BIT(USB_IER_RESTIE_POS)

/* host mode */
#define USB_IER_BABIE_POS 2U
#define USB_IER_BABIE_MSK BIT(USB_IER_BABIE_POS)

/* device/host mode */
#define USB_IER_RESIE_POS 1U
#define USB_IER_RESIE_MSK BIT(USB_IER_RESIE_POS)

#define USB_IER_SUSPDIE_POS 0U
#define USB_IER_SUSPDIE_MSK BIT(USB_IER_SUSPDIE_POS)

/****************** Bit definition for USB_IDR register ************************/

/* device/host mode */
#define USB_IDR_SESREQID_POS 6U
#define USB_IDR_SESREQID_MSK BIT(USB_IDR_SESREQID_POS)

#define USB_IDR_DISCONID_POS 5U
#define USB_IDR_DISCONID_MSK BIT(USB_IDR_DISCONID_POS)

/* host mode */
#define USB_IDR_CONID_POS 4U
#define USB_IDR_CONID_MSK BIT(USB_IDR_CONID_POS)

/* device/host mode */
#define USB_IDR_SOFID_POS 3U
#define USB_IDR_SOFID_MSK BIT(USB_IDR_SOFID_POS)

/* device mode */
#define USB_IDR_RESTID_POS 2U
#define USB_IDR_RESTID_MSK BIT(USB_IDR_RESTID_POS)

/* host mode */
#define USB_IDR_BABID_POS 2U
#define USB_IDR_BABID_MSK BIT(USB_IDR_BABID_POS)

/* device/host mode */
#define USB_IDR_RESID_POS 1U
#define USB_IDR_RESID_MSK BIT(USB_IDR_RESID_POS)

#define USB_IDR_SUSPDID_POS 0U
#define USB_IDR_SUSPDID_MSK BIT(USB_IDR_SUSPDID_POS)

/****************** Bit definition for USB_IVS register ************************/

/* device/host mode */
#define USB_IVS_SESREQIVS_POS 6U
#define USB_IVS_SESREQIVS_MSK BIT(USB_IVS_SESREQIVS_POS)

#define USB_IVS_DISCONIVS_POS 5U
#define USB_IVS_DISCONIVS_MSK BIT(USB_IVS_DISCONIVS_POS)

/* host mode */
#define USB_IVS_CONIVS_POS 4U
#define USB_IVS_CONIVS_MSK BIT(USB_IVS_CONIVS_POS)

/* device/host mode */
#define USB_IVS_SOFIVS_POS 3U
#define USB_IVS_SOFIVS_MSK BIT(USB_IVS_SOFIVS_POS)

/* device mode */
#define USB_IVS_RESTIVS_POS 2U
#define USB_IVS_RESTIVS_MSK BIT(USB_IVS_RESTIVS_POS)

/* host mode */
#define USB_IVS_BABIVS_POS 2U
#define USB_IVS_BABIVS_MSK BIT(USB_IVS_BABIVS_POS)

/* device/host mode */
#define USB_IVS_RESIVS_POS 1U
#define USB_IVS_RESIVS_MSK BIT(USB_IVS_RESIVS_POS)

#define USB_IVS_SUSPDIVS_POS 0U
#define USB_IVS_SUSPDIVS_MSK BIT(USB_IVS_SUSPDIVS_POS)

/****************** Bit definition for USB_RIF register ************************/

/* device/host mode */
#define USB_RIF_SESREQRIF_POS 6U
#define USB_RIF_SESREQRIF_MSK BIT(USB_RIF_SESREQRIF_POS)

#define USB_RIF_DISCONRIF_POS 5U
#define USB_RIF_DISCONRIF_MSK BIT(USB_RIF_DISCONRIF_POS)

/* host mode */
#define USB_RIF_CONRIF_POS 4U
#define USB_RIF_CONRIF_MSK BIT(USB_RIF_CONRIF_POS)

/* device/host mode */
#define USB_RIF_SOFRIF_POS 3U
#define USB_RIF_SOFRIF_MSK BIT(USB_RIF_SOFRIF_POS)

/* device mode */
#define USB_RIF_RESTRIF_POS 2U
#define USB_RIF_RESTRIF_MSK BIT(USB_RIF_RESTRIF_POS)

/* host mode */
#define USB_RIF_BABRIF_POS 2U
#define USB_RIF_BABRIF_MSK BIT(USB_RIF_BABRIF_POS)

/* device/host mode */
#define USB_RIF_RESRIF_POS 1U
#define USB_RIF_RESRIF_MSK BIT(USB_RIF_RESRIF_POS)

#define USB_RIF_SUSPDRIF_POS 0U
#define USB_RIF_SUSPDRIF_MSK BIT(USB_RIF_SUSPDRIF_POS)

/****************** Bit definition for USB_IFM register ************************/

/* device/host mode */
#define USB_IFM_SESREQIFM_POS 6U
#define USB_IFM_SESREQIFM_MSK BIT(USB_IFM_SESREQIFM_POS)

#define USB_IFM_DISCONIFM_POS 5U
#define USB_IFM_DISCONIFM_MSK BIT(USB_IFM_DISCONIFM_POS)

/* host mode */
#define USB_IFM_CONIFM_POS 4U
#define USB_IFM_CONIFM_MSK BIT(USB_IFM_CONIFM_POS)

/* device/host mode */
#define USB_IFM_SOFIFM_POS 3U
#define USB_IFM_SOFIFM_MSK BIT(USB_IFM_SOFIFM_POS)

/* device mode */
#define USB_IFM_RESTIFM_POS 2U
#define USB_IFM_RESTIFM_MSK BIT(USB_IFM_RESTIFM_POS)

/* host mode */
#define USB_IFM_BABIFM_POS 2U
#define USB_IFM_BABIFM_MSK BIT(USB_IFM_BABIFM_POS)

/* device/host mode */
#define USB_IFM_RESIFM_POS 1U
#define USB_IFM_RESIFM_MSK BIT(USB_IFM_RESIFM_POS)

#define USB_IFM_SUSPDIFM_POS 0U
#define USB_IFM_SUSPDIFM_MSK BIT(USB_IFM_SUSPDIFM_POS)

/****************** Bit definition for USB_ICR register ************************/

/* device/host mode */
#define USB_ICR_SESREQICR_POS 6U
#define USB_ICR_SESREQICR_MSK BIT(USB_ICR_SESREQICR_POS)

#define USB_ICR_DISCONICR_POS 5U
#define USB_ICR_DISCONICR_MSK BIT(USB_ICR_DISCONICR_POS)

/* host mode */
#define USB_ICR_CONICR_POS 4U
#define USB_ICR_CONICR_MSK BIT(USB_ICR_CONICR_POS)

/* device/host mode */
#define USB_ICR_SOFICR_POS 3U
#define USB_ICR_SOFICR_MSK BIT(USB_ICR_SOFICR_POS)

/* device mode */
#define USB_ICR_RESTICR_POS 2U
#define USB_ICR_RESTICR_MSK BIT(USB_ICR_RESTICR_POS)

/* host mode */
#define USB_ICR_BABICR_POS 2U
#define USB_ICR_BABICR_MSK BIT(USB_ICR_BABICR_POS)

/* device/host mode */
#define USB_ICR_RESICR_POS 1U
#define USB_ICR_RESICR_MSK BIT(USB_ICR_RESICR_POS)

#define USB_ICR_SUSPDICR_POS 0U
#define USB_ICR_SUSPDICR_MSK BIT(USB_ICR_SUSPDICR_POS)

typedef struct
{
  __IO uint8_t   FADDR       ; //0x0000              Function address register.
  __IO uint8_t   POWER       ; //0x0001              Power management register.
  __IO uint8_t   DPDMCON     ; //0x0002              DP DM Control register.
  __IO uint8_t   SWCID       ; //0x0003              Softwave CID register.
  __IO uint8_t   SWVBUS      ; //0x0004              Softwave VBUS register.
  __IO uint8_t   TMODE       ; //0x0005              Test Mode register.
  __IO uint8_t   RES002[6]   ; //0x0006~0x0B,        Reserved
  __IO uint8_t   FRAME1      ; //0x000C,             Frame number bits 0 to 7.
  __IO uint8_t   FRAME2      ; //0x000D,             Frame number bits 8 to 10.
  __IO uint8_t   INDEX       ; //0x000E,             Index register for selecting the endp
  __IO uint8_t   DEVCON      ; //0x000F,             USB device control register.
  __IO uint8_t   TXMAXP      ; //0x0010,             Peripheral mode - Maximum packet size
  __IO uint8_t   CSR0L_TXCSRL ;//0x0011,             Peripheral mode - Control Status regi
  __IO uint8_t   CSR0H_TXCSRH ;//0x0012,             Peripheral mode - Control Status regi
  __IO uint8_t   RXMAXP      ; //0x0013,             Peripheral mode - Maximum packet size
  __IO uint8_t   RXCSRL      ; //0x0014,             Peripheral mode - Control Status regi
  __IO uint8_t   RXCSRH      ; //0x0015,             Peripheral mode - Control Status regi
  __IO uint8_t   COUNT0_RX1  ; //0x0016,             Peripheral mode - Number of bytes in
  __IO uint8_t   RXCOUNT2    ; //0x0017,             Peripheral mode - Number of bytes in
  __IO uint8_t   TXTYPE      ; //0x0018,             Peripheral mode -  //
  __IO uint8_t   NAKLIMIT0_TXINTERVAL  ; //0x0019,   Peripheral mode - //
  __IO uint8_t   RXTYPE      ; //0x001A,             Peripheral mode - //
  __IO uint8_t   RXINTERVAL  ; //0x001B,             Peripheral mode - //
  __IO uint8_t   TXFIFO1     ; //0x001C,             Tx Endpoint FIFO details
  __IO uint8_t   TXFIFO2     ; //0x001D,             Tx Endpoint FIFO details
  __IO uint8_t   RXFIFO1     ; //0x001E,             Rx Endpoint FIFO details
  __IO uint8_t   RXFIFO2     ; //0x001F,             Rx Endpoint FIFO details
  __IO uint8_t   EP0FIFO     ; //0x0020,             FIFOs for Endpoints 0.
  __IO uint8_t   RES021[3]   ; //0x0021~0x23,        Reserved
  __IO uint8_t   EP1FIFO     ; //0x0024,             FIFOs for Endpoints 1.
  __IO uint8_t   RES025[3]   ; //0x0025~0x27,        Reserved
  __IO uint8_t   EP2FIFO     ; //0x0028,             FIFOs for Endpoints 2.
  __IO uint8_t   RES029[3]   ; //0x0029~0x2B,        Reserved
  __IO uint8_t   EP3FIFO     ; //0x002C,             FIFOs for Endpoints 3.
  __IO uint8_t   RES02D[3]   ; //0x002D~0x2F,        Reserved
  __IO uint8_t   EP4FIFO     ; //0x0030,             FIFOs for Endpoints 4.
  __IO uint8_t   RES031[3]   ; //0x0031~0x33,        Reserved
  __IO uint8_t   EP5FIFO     ; //0x0034,             FIFOs for Endpoints 5.
  __IO uint8_t   RES035[3]   ; //0x0035~0x37,        Reserved
  __IO uint8_t   EP6FIFO     ; //0x0038,             FIFOs for Endpoints 6.
  __IO uint8_t   RES039[71]  ; //0x0039~0x7C,        Reserved
  __IO uint8_t   TXIER       ; //0x0080,             TX Endpoint 0~6 Interrupt Enable
  __IO uint8_t   RES081      ; //0x0081,             Reserved
  __IO uint8_t   RXIER       ; //0x0082,             RX Endpoint 0~6 Interrupt Enable
  __IO uint8_t   RES083      ; //0x0083,             Reserved
  __IO uint8_t   TXIDR       ; //0x0084,             TX Endpoint 0~6 Interrupt Disable
  __IO uint8_t   RES085      ; //0x0085,             Reserved
  __IO uint8_t   RXIDR       ; //0x0086,             RX Endpoint 0~6 Interrupt Disable
  __IO uint8_t   RES087      ; //0x0087,             Reserved
  __IO uint8_t   TXIVS       ; //0x0088,             TX Endpoint 0~6 Interrupt Valid Status
  __IO uint8_t   RES089      ; //0x0089,             Reserved
  __IO uint8_t   RXIVS       ; //0x008A,             RX Endpoint 0~6 Interrupt Valid Status
  __IO uint8_t   RES08B      ; //0x008B,             Reserved
  __IO uint8_t   TXRIF       ; //0x008C,             TX Endpoint 0~6 Raw Interrupt Flag Status
  __IO uint8_t   RES08D      ; //0x008D,             Reserved
  __IO uint8_t   RXRIF       ; //0x008E,             RX Endpoint 0~6 Raw Interrupt Flag Status
  __IO uint8_t   RES08F      ; //0x008F,             Reserved
  __IO uint8_t   TXIFM       ; //0x0090,             TX Endpoint 0~6 Interrupt Flag Masked Status
  __IO uint8_t   RES091      ; //0x0091,             Reserved
  __IO uint8_t   RXIFM       ; //0x0092,             RX Endpoint 0~6 Interrupt Flag Masked Status
  __IO uint8_t   RES093      ; //0x0093,             Reserved
  __IO uint8_t   TXICR       ; //0x0094,             TX Endpoint 0~6 Interrupt Clear Register
  __IO uint8_t   RES095      ; //0x0095,             Reserved
  __IO uint8_t   RXICR       ; //0x0096,             RX Endpoint 0~6 Interrupt Clear Register
  __IO uint8_t   RES097[9]   ; //0x0097~0x9C,        Reserved
  __O  uint32_t  IER         ; //0x00A0,             USB Interrupt Enable Register
  __O  uint32_t  IDR         ; //0x00A4,             USB Interrupt Disable Register
  __I  uint32_t  IVS         ; //0x00A8,             USB Interrupt Valid Register
  __I  uint32_t  RIF         ; //0x00AC,             USB Raw Interrupt Flag Status Register
  __I  uint32_t  IFM         ; //0x00B0,             USB Interrupt Flag Masked Status
  __O  uint32_t  ICR         ; //0x00B4,             USB Interrupt Clear Register
} USB_TypeDef;


#endif
