/**
  **************************************************************************
  * @file     at32f425_usb.h
  * @brief    at32f425 usb header file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F425_USB_H
#define __AT32F425_USB_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f425.h"

/** @addtogroup AT32F425_periph_driver
  * @{
  */

/** @addtogroup USB
  * @{
  */

/** @defgroup USB_global_interrupts_definition
  * @brief usb global interrupt mask
  * @{
  */

#define USB_OTG_MODEMIS_INT              ((uint32_t)0x00000002) /*!< usb otg mode mismatch interrupt */
#define USB_OTG_OTGINT_INT               ((uint32_t)0x00000004) /*!< usb otg interrupt */
#define USB_OTG_SOF_INT                  ((uint32_t)0x00000008) /*!< usb otg sof interrupt */
#define USB_OTG_RXFLVL_INT               ((uint32_t)0x00000010) /*!< usb otg receive fifo non-empty interrupt */
#define USB_OTG_NPTXFEMP_INT             ((uint32_t)0x00000020) /*!< usb otg non-periodic tx fifo empty interrupt */
#define USB_OTG_GINNAKEFF_INT            ((uint32_t)0x00000040) /*!< usb otg global non-periodic in nak effective interrupt */
#define USB_OTG_GOUTNAKEFF_INT           ((uint32_t)0x00000080) /*!< usb otg global out nak effective interrupt */
#define USB_OTG_ERLYSUSP_INT             ((uint32_t)0x00000400) /*!< usb otg early suspend interrupt */
#define USB_OTG_USBSUSP_INT              ((uint32_t)0x00000800) /*!< usb otg suspend interrupt */
#define USB_OTG_USBRST_INT               ((uint32_t)0x00001000) /*!< usb otg reset interrupt */
#define USB_OTG_ENUMDONE_INT             ((uint32_t)0x00002000) /*!< usb otg enumeration done interrupt */
#define USB_OTG_ISOOUTDROP_INT           ((uint32_t)0x00004000) /*!< usb otg isochronous out packet dropped interrut */
#define USB_OTG_EOPF_INT                 ((uint32_t)0x00008000) /*!< usb otg eop interrupt */
#define USB_OTG_IEPT_INT                 ((uint32_t)0x00040000) /*!< usb otg in endpoint interrupt */
#define USB_OTG_OEPT_INT                 ((uint32_t)0x00080000) /*!< usb otg out endpoint interrupt */
#define USB_OTG_INCOMISOIN_INT           ((uint32_t)0x00100000) /*!< usb otg incomplete isochronous in transfer interrupt */
#define USB_OTG_INCOMPIP_INCOMPISOOUT_INT ((uint32_t)0x00200000) /*!< usb otg incomplete periodic transfer/isochronous out interrupt */
#define USB_OTG_PRT_INT                  ((uint32_t)0x01000000) /*!< usb otg host port interrupt */
#define USB_OTG_HCH_INT                  ((uint32_t)0x02000000) /*!< usb otg host channel interrupt */
#define USB_OTG_PTXFEMP_INT              ((uint32_t)0x04000000) /*!< usb otg periodic txfifo empty interrupt */
#define USB_OTG_CONIDSCHG_INT            ((uint32_t)0x10000000) /*!< usb otg connector id status change interrupt */
#define USB_OTG_DISCON_INT               ((uint32_t)0x20000000) /*!< usb otg disconnect detected interrupt */
#define USB_OTG_WKUP_INT                 ((uint32_t)0x80000000) /*!< usb otg wakeup interrupt */

/**
  * @}
  */

/** @defgroup USB_global_interrupt_flags_definition
  * @brief usb global interrupt flag
  * @{
  */

#define USB_OTG_CURMODE                  ((uint32_t)0x00000001) /*!< usb otg current mode */
#define USB_OTG_MODEMIS_FLAG             ((uint32_t)0x00000002) /*!< usb otg mode mismatch flag */
#define USB_OTG_OTGINT_FLAG              ((uint32_t)0x00000004) /*!< usb otg flag */
#define USB_OTG_SOF_FLAG                 ((uint32_t)0x00000008) /*!< usb otg sof flag */
#define USB_OTG_RXFLVL_FLAG              ((uint32_t)0x00000010) /*!< usb otg receive fifo non-empty flag */
#define USB_OTG_NPTXFEMP_FLAG            ((uint32_t)0x00000020) /*!< usb otg non-periodic tx fifo empty flag */
#define USB_OTG_GINNAKEFF_FLAG           ((uint32_t)0x00000040) /*!< usb otg global non-periodic in nak effective flag */
#define USB_OTG_GOUTNAKEFF_FLAG          ((uint32_t)0x00000080) /*!< usb otg global out nak effective flag */
#define USB_OTG_ERLYSUSP_FLAG            ((uint32_t)0x00000400) /*!< usb otg early suspend flag */
#define USB_OTG_USBSUSP_FLAG             ((uint32_t)0x00000800) /*!< usb otg suspend flag */
#define USB_OTG_USBRST_FLAG              ((uint32_t)0x00001000) /*!< usb otg reset flag */
#define USB_OTG_ENUMDONE_FLAG            ((uint32_t)0x00002000) /*!< usb otg enumeration done flag */
#define USB_OTG_ISOOUTDROP_FLAG          ((uint32_t)0x00004000) /*!< usb otg isochronous out packet dropped flag */
#define USB_OTG_EOPF_FLAG                ((uint32_t)0x00008000) /*!< usb otg eop flag */
#define USB_OTG_IEPT_FLAG                ((uint32_t)0x00040000) /*!< usb otg in endpoint flag */
#define USB_OTG_OEPT_FLAG                ((uint32_t)0x00080000) /*!< usb otg out endpoint flag */
#define USB_OTG_INCOMISOIN_FLAG          ((uint32_t)0x00100000) /*!< usb otg incomplete isochronous in transfer flag */
#define USB_OTG_INCOMPIP_INCOMPISOOUT_FLAG   ((uint32_t)0x00200000) /*!< usb otg incomplete periodic transfer/isochronous out flag */
#define USB_OTG_PRT_FLAG                 ((uint32_t)0x01000000) /*!< usb otg host port flag */
#define USB_OTG_HCH_FLAG                 ((uint32_t)0x02000000) /*!< usb otg host channel flag */
#define USB_OTG_PTXFEMP_FLAG             ((uint32_t)0x04000000) /*!< usb otg periodic txfifo empty flag */
#define USB_OTG_CONIDSCHG_FLAG           ((uint32_t)0x10000000) /*!< usb otg connector id status change flag */
#define USB_OTG_DISCON_FLAG              ((uint32_t)0x20000000) /*!< usb otg disconnect detected flag */
#define USB_OTG_WKUP_FLAG                ((uint32_t)0x80000000) /*!< usb otg wakeup flag */

/**
  * @}
  */


/** @defgroup USB_global_setting_definition
  * @brief usb global setting
  * @{
  */

/**
  * @brief usb turnaround time
  */
#define USB_TRDTIM_8                     0x9 /*!< usb turn around time 8 */
#define USB_TRDTIM_16                    0x5 /*!< usb turn around time 16 */

/**
  * @brief usb receive status
  */
#define USB_OTG_GRXSTSP_EPTNUM           ((uint32_t)0x0000000F) /*!< usb device receive packet endpoint number*/
#define USB_OTG_GRXSTSP_CHNUM            ((uint32_t)0x0000000F) /*!< usb host receive packet channel number*/
#define USB_OTG_GRXSTSP_BCNT             ((uint32_t)0x00007FF0) /*!< usb receive packet byte count */
#define USB_OTG_GRXSTSP_DPID             ((uint32_t)0x00018000) /*!< usb receive packet pid */
#define USB_OTG_GRXSTSP_PKTSTS           ((uint32_t)0x001E0000) /*!< usb receive packet status */

/**
  * @brief usb host packet status
  */
#define PKTSTS_IN_DATA_PACKET_RECV       0x2 /*!< usb host in data packet received */
#define PKTSTS_IN_TRANSFER_COMPLETE      0x3 /*!< usb host in transfer completed */
#define PKTSTS_DATA_BIT_ERROR            0x5 /*!< usb host data toggle error */
#define PKTSTS_CHANNEL_STOP              0x7 /*!< usb host channel halted */

/**
  * @brief usb device  packet status
  */
#define USB_OUT_STS_NAK                  0x1 /*!< usb device global out nak */
#define USB_OUT_STS_DATA                 0x2 /*!< usb device out data packet received */
#define USB_OUT_STS_COMP                 0x3 /*!< usb device out transfer completed */
#define USB_SETUP_STS_COMP               0x4 /*!< usb device setup transcation completed */
#define USB_SETUP_STS_DATA               0x6 /*!< usb device setup data packet received */

/**
  * @}
  */

/** @defgroup USB_host_config_definition
  * @{
  */

/**
  * @brief usb host phy clock
  */
#define USB_HCFG_CLK_60M                 0 /*!< usb host phy clock 60mhz */
#define USB_HCFG_CLK_48M                 1 /*!< usb host phy clock 48mhz */
#define USB_HCFG_CLK_6M                  2 /*!< usb host phy clock 6mhz */

/**
  * @brief usb host port status
  */
#define USB_OTG_HPRT_PRTCONSTS           ((uint32_t)0x00000001) /*!< usb host port connect status */
#define USB_OTG_HPRT_PRTCONDET           ((uint32_t)0x00000002) /*!< usb host port connect detected */
#define USB_OTG_HPRT_PRTENA              ((uint32_t)0x00000004) /*!< usb host port enable */
#define USB_OTG_HPRT_PRTENCHNG           ((uint32_t)0x00000008) /*!< usb host port enable/disable change */
#define USB_OTG_HPRT_PRTOVRCACT          ((uint32_t)0x00000010) /*!< usb host port overcurrent active */
#define USB_OTG_HPRT_PRTOVRCCHNG         ((uint32_t)0x00000020) /*!< usb host port overcurrent change */
#define USB_OTG_HPRT_PRTRES              ((uint32_t)0x00000040) /*!< usb host port resume */
#define USB_OTG_HPRT_PRTSUSP             ((uint32_t)0x00000080) /*!< usb host port suspend */
#define USB_OTG_HPRT_PRTRST              ((uint32_t)0x00000100) /*!< usb host port reset */
#define USB_OTG_HPRT_PRTLNSTS            ((uint32_t)0x00000C00) /*!< usb host port line status */
#define USB_OTG_HPRT_PRTPWR              ((uint32_t)0x00001000) /*!< usb host port power */
#define USB_OTG_HPRT_PRTSPD              ((uint32_t)0x00060000) /*!< usb host port speed */

/**
  * @brief usb port speed
  */
#define USB_PRTSPD_HIGH_SPEED            0 /*!< usb host port high speed */
#define USB_PRTSPD_FULL_SPEED            1 /*!< usb host port full speed */
#define USB_PRTSPD_LOW_SPEED             2 /*!< usb host port low speed */

/**
  * @brief usb host register hcchar bit define
  */
#define USB_OTG_HCCHAR_MPS               ((uint32_t)0x000007FF) /*!< channel maximum packet size */
#define USB_OTG_HCCHAR_EPTNUM            ((uint32_t)0x00007800) /*!< endpoint number */
#define USB_OTG_HCCHAR_EPTDIR            ((uint32_t)0x00008000) /*!< endpoint direction */
#define USB_OTG_HCCHAR_LSPDDEV           ((uint32_t)0x00020000) /*!< low speed device */
#define USB_OTG_HCCHAR_EPTYPE            ((uint32_t)0x000C0000) /*!< endpoint type */
#define USB_OTG_HCCHAR_MC                ((uint32_t)0x00300000) /*!< multi count */
#define USB_OTG_HCCHAR_DEVADDR           ((uint32_t)0x1FC00000) /*!< device address */
#define USB_OTG_HCCHAR_ODDFRM            ((uint32_t)0x20000000) /*!< odd frame */
#define USB_OTG_HCCHAR_CHDIS             ((uint32_t)0x40000000) /*!< channel disable */
#define USB_OTG_HCCHAR_CHENA             ((uint32_t)0x80000000) /*!< channel enable */

/**
  * @brief usb host register hctsiz bit define
  */
#define USB_OTG_HCTSIZ_XFERSIZE          ((uint32_t)0x0007FFFF) /*!< channel transfer size */
#define USB_OTG_HCTSIZ_PKTCNT            ((uint32_t)0x1FF80000) /*!< channel packet count */
#define USB_OTG_HCTSIZ_PID               ((uint32_t)0x60000000) /*!< channel pid */

/**
  * @brief usb host channel interrupt mask
  */
#define USB_OTG_HC_XFERCM_INT            ((uint32_t)0x00000001) /*!< channel transfer complete interrupt */
#define USB_OTG_HC_CHHLTDM_INT           ((uint32_t)0x00000002) /*!< channel halted interrupt */
#define USB_OTG_HC_STALLM_INT            ((uint32_t)0x00000008) /*!< channel stall interrupt */
#define USB_OTG_HC_NAKM_INT              ((uint32_t)0x00000010) /*!< channel nak interrupt */
#define USB_OTG_HC_ACKM_INT              ((uint32_t)0x00000020) /*!< channel ack interrupt */
#define USB_OTG_HC_NYETM_INT             ((uint32_t)0x00000040) /*!< channel nyet interrupt */
#define USB_OTG_HC_XACTERRM_INT          ((uint32_t)0x00000080) /*!< channel transaction error interrupt */
#define USB_OTG_HC_BBLERRM_INT           ((uint32_t)0x00000100) /*!< channel babble error interrupt */
#define USB_OTG_HC_FRMOVRRUN_INT         ((uint32_t)0x00000200) /*!< channel frame overrun interrupt */
#define USB_OTG_HC_DTGLERRM_INT          ((uint32_t)0x00000400) /*!< channel data toggle interrupt */

/**
  * @brief usb host channel interrupt flag
  */
#define USB_OTG_HC_XFERC_FLAG            ((uint32_t)0x00000001) /*!< channel transfer complete flag */
#define USB_OTG_HC_CHHLTD_FLAG           ((uint32_t)0x00000002) /*!< channel halted flag */
#define USB_OTG_HC_STALL_FLAG            ((uint32_t)0x00000008) /*!< channel stall flag */
#define USB_OTG_HC_NAK_FLAG              ((uint32_t)0x00000010) /*!< channel nak flag */
#define USB_OTG_HC_ACK_FLAG              ((uint32_t)0x00000020) /*!< channel ack flag */
#define USB_OTG_HC_NYET_FLAG             ((uint32_t)0x00000040) /*!< channel nyet flag */
#define USB_OTG_HC_XACTERR_FLAG          ((uint32_t)0x00000080) /*!< channel transaction error flag */
#define USB_OTG_HC_BBLERR_FLAG           ((uint32_t)0x00000100) /*!< channel babble error flag */
#define USB_OTG_HC_FRMOVRRUN_FLAG        ((uint32_t)0x00000200) /*!< channel frame overrun flag */
#define USB_OTG_HC_DTGLERR_FLAG          ((uint32_t)0x00000400) /*!< channel data toggle flag */

/**
  * @}
  */


/** @defgroup USB_device_config_definition
  * @{
  */
/**
  * @brief usb device periodic frame interval
  */
typedef enum
{
  DCFG_PERFRINT_80                       = 0x00, /*!< periodic frame interval 80% */
  DCFG_PERFRINT_85                       = 0x01, /*!< periodic frame interval 85% */
  DCFG_PERFRINT_90                       = 0x02, /*!< periodic frame interval 90% */
  DCFG_PERFRINT_95                       = 0x03  /*!< periodic frame interval 95% */
} dcfg_perfrint_type;


/**
  * @brief usb device full speed
  */
#define USB_DCFG_FULL_SPEED              3 /*!< device full speed */

/**
  * @brief usb device ctrl define
  */
#define USB_OTG_DCTL_RWKUPSIG            ((uint32_t)0x00000001) /*!< usb device remote wakeup signaling */
#define USB_OTG_DCTL_SFTDISCON           ((uint32_t)0x00000002) /*!< usb device soft disconnect */
#define USB_OTG_DCTL_GNPINNAKSTS         ((uint32_t)0x00000004) /*!< usb device global non-periodic in nak status */
#define USB_OTG_DCTL_GOUTNAKSTS          ((uint32_t)0x00000008) /*!< usb device global out nak status */
#define USB_OTG_DCTL_SGNPINNAK           ((uint32_t)0x00000080) /*!< usb device set global non-periodic in nak */
#define USB_OTG_DCTL_CGNPINNAK           ((uint32_t)0x00000100) /*!< usb device clear global non-periodic in nak */
#define USB_OTG_DCTL_SGOUTNAK            ((uint32_t)0x00000200) /*!< usb device set global out nak status */
#define USB_OTG_DCTL_CGOUTNAK            ((uint32_t)0x00000400) /*!< usb device clear global out nak status */
#define USB_OTG_DCTL_PWROPRGDNE          ((uint32_t)0x00000800) /*!< usb device power on programming done */

/**
  * @brief usb device in endpoint flag
  */
#define USB_OTG_DIEPINT_XFERC_FLAG       ((uint32_t)0x00000001) /*!< usb device in transfer completed flag */
#define USB_OTG_DIEPINT_EPTDISD_FLAG     ((uint32_t)0x00000002) /*!< usb device endpoint disable flag */
#define USB_OTG_DIEPINT_TIMEOUT_FLAG     ((uint32_t)0x00000008) /*!< usb device in timeout */
#define USB_OTG_DIEPINT_INTKNTXFEMP_FLAG ((uint32_t)0x00000010) /*!< usb device in token received when tx fifo is empty flag */
#define USB_OTG_DIEPINT_INEPTNAK_FLAG    ((uint32_t)0x00000040) /*!< usb device in endpoint nak effective flag */
#define USB_OTG_DIEPINT_TXFEMP_FLAG      ((uint32_t)0x00000080) /*!< usb device transmit fifo empty flag */

/**
  * @brief usb device out endpoint flag
  */
#define USB_OTG_DOEPINT_XFERC_FLAG       ((uint32_t)0x00000001) /*!< usb device out transfer completed flag */
#define USB_OTG_DOEPINT_EPTDISD_FLAG     ((uint32_t)0x00000002) /*!< usb device endpoint disable flag */
#define USB_OTG_DOEPINT_SETUP_FLAG       ((uint32_t)0x00000008) /*!< usb device setup flag */
#define USB_OTG_DOEPINT_OUTTEPD_FLAG     ((uint32_t)0x00000010) /*!< usb device out token recevied when endpoint disable flag */
#define USB_OTG_DOEPINT_B2BSTUP_FLAG     ((uint32_t)0x00000040) /*!< back-to-back setup packets received */

/**
  * @brief usb device in endpoint fifo space mask
  */
#define USB_OTG_DTXFSTS_INEPTFSAV        ((uint32_t)0x0000FFFF) /*!< usb device in endpoint tx fifo space avail */

/**
  * @brief endpoint0 maximum packet size
  */
#define USB_EPT0_MPS_64                  0 /*!< usb device endpoint 0 maximum packet size 64byte */
#define USB_EPT0_MPS_32                  1 /*!< usb device endpoint 0 maximum packet size 32byte */
#define USB_EPT0_MPS_16                  2 /*!< usb device endpoint 0 maximum packet size 16byte */
#define USB_EPT0_MPS_8                   3 /*!< usb device endpoint 0 maximum packet size 8byte */

/**
  * @}
  */

/**
  * @brief otg fifo size (word)
  */
#define OTG_FIFO_SIZE                    320 /*!< otg usb total fifo size */

/**
  * @brief otg host max buffer length (byte)
  */
#define USB_MAX_DATA_LENGTH              0x200 /*!< usb host maximum buffer size */

#define OTGFS_USB_GLOBAL
#define OTGFS_USB_DEVICE
#define OTGFS_USB_HOST

/** @defgroup USB_exported_enum_types
  * @{
  */

/**
  * @brief usb mode define(device, host, drd)
  */
typedef enum
{
  OTG_DEVICE_MODE, /*!< usb device mode */
  OTG_HOST_MODE,   /*!< usb host mode */
  OTG_DRD_MODE     /*!< usb drd mode */
} otg_mode_type;

/**
  * @brief endpoint type define
  */
typedef enum
{
  EPT_CONTROL_TYPE                       = 0x00, /*!< usb endpoint type control */
  EPT_ISO_TYPE                           = 0x01, /*!< usb endpoint type iso */
  EPT_BULK_TYPE                          = 0x02, /*!< usb endpoint type bulk */
  EPT_INT_TYPE                           = 0x03  /*!< usb endpoint type interrupt */
} endpoint_trans_type;

/**
  * @brief usb endpoint number define type
  */
typedef enum
{
  USB_EPT0                               = 0x00, /*!< usb endpoint 0 */
  USB_EPT1                               = 0x01, /*!< usb endpoint 1 */
  USB_EPT2                               = 0x02, /*!< usb endpoint 2 */
  USB_EPT3                               = 0x03, /*!< usb endpoint 3 */
  USB_EPT4                               = 0x04, /*!< usb endpoint 4 */
  USB_EPT5                               = 0x05, /*!< usb endpoint 5 */
  USB_EPT6                               = 0x06, /*!< usb endpoint 6 */
  USB_EPT7                               = 0x07  /*!< usb endpoint 7 */
} usb_endpoint_number_type;

/**
  * @brief usb endpoint max num define
  */
#ifndef USB_EPT_MAX_NUM
#define USB_EPT_MAX_NUM                   8  /*!< usb device support endpoint number */
#endif
/**
  * @brief usb channel max num define
  */
#ifndef USB_HOST_CHANNEL_NUM
#define USB_HOST_CHANNEL_NUM             16 /*!< usb host support channel number */
#endif

/**
  * @brief endpoint trans dir type
  */
typedef enum
{
  EPT_DIR_IN                             = 0x00, /*!< usb transfer direction in */
  EPT_DIR_OUT                            = 0x01  /*!< usb transfer direction out */
} endpoint_dir_type;

/**
  * @brief otgfs1 and otgfs2 select type
  */
typedef enum
{
  USB_OTG1_ID, /*!< usb otg 1 id */
  USB_OTG2_ID  /*!< usb otg 2 id */
} otg_id_type;

/**
  * @brief usb clock select
  */
typedef enum
{
  USB_CLK_HICK,  /*!< usb clock use hick */
  USB_CLK_HEXT   /*!< usb clock use hext */
}usb_clk48_s;

/**
  * @}
  */



/** @defgroup USB_exported_types
  * @{
  */

/**
  * @brief  usb endpoint infomation structure definition
  */
typedef struct
{
  uint8_t                                eptn;                        /*!< endpoint register number (0~7) */
  uint8_t                                ept_address;                 /*!< endpoint address */
  uint8_t                                inout;                       /*!< endpoint dir EPT_DIR_IN or EPT_DIR_OUT */
  uint8_t                                trans_type;                  /*!< endpoint type:
                                                                         EPT_CONTROL_TYPE, EPT_BULK_TYPE, EPT_INT_TYPE, EPT_ISO_TYPE*/
  uint16_t                               tx_addr;                     /*!< endpoint tx buffer offset address */
  uint16_t                               rx_addr;                     /*!< endpoint rx buffer offset address */
  uint32_t                               maxpacket;                   /*!< endpoint max packet*/
  uint8_t                                is_double_buffer;            /*!< endpoint double buffer flag */
  uint8_t                                stall;                       /*!< endpoint is stall state */
  uint32_t                               status;

  /* transmission buffer and count */
  uint8_t                                *trans_buf;                  /*!< endpoint transmission buffer */
  uint32_t                               total_len;                   /*!< endpoint transmission lengtg */
  uint32_t                               trans_len;                   /*!< endpoint transmission length*/

  uint32_t                               last_len;                    /*!< last transfer length */
  uint32_t                               rem0_len;                    /*!< rem transfer length */
  uint32_t                               ept0_slen;                   /*!< endpoint 0 transfer sum length */
} usb_ept_info;


/**
  * @brief  usb host channel infomation structure definition
  */
typedef struct
{
  uint8_t                                ch_num;                      /*!< host channel number */
  uint8_t                                address;                     /*!< device address */
  uint8_t                                dir;                         /*!< transmission direction */
  uint8_t                                ept_num;                     /*!< device endpoint number */
  uint8_t                                ept_type;                    /*!< channel transmission type */
  uint32_t                               maxpacket;                   /*!< support max packet size */
  uint8_t                                data_pid;                    /*!< data pid */
  uint8_t                                speed;                       /*!< usb speed */
  uint8_t                                stall;                       /*!< channel stall flag */
  uint32_t                               status;                      /*!< channel status */
  uint32_t                               state;                       /*!< channel state */
  uint32_t                               urb_sts;                     /*!< usb channel request block state */

  uint8_t                                toggle_in;                   /*!< channel in transfer toggle */
  uint8_t                                toggle_out;                  /*!< channel out transfer toggle */

  /* transmission buffer and count */
  uint8_t                                *trans_buf;                  /* host channel buffer */
  uint32_t                               trans_len;                   /* host channel transmission len */
  uint32_t                               trans_count;                 /* host channel transmission count*/
} usb_hch_type;


typedef struct
{
  /**
  * @brief otgfs control and status register, offset:0x00
  */
  union
  {
    __IO uint32_t gotgctrl;
    struct
    {
      __IO uint32_t reserved1                : 16; /* [15:0] */
      __IO uint32_t cidsts                   : 1; /* [16] */
      __IO uint32_t reserved2                : 4; /* [20:17] */
      __IO uint32_t curmod                   : 1; /* [21] */
      __IO uint32_t reserved3                : 10; /* [31:22] */
    } gotgctrl_bit;
  };

     /**
  * @brief otgfs interrupt register, offset:0x04
  */
  union
  {
    __IO uint32_t gotgint;
    struct
    {
      __IO uint32_t reserved1                : 2; /* [1:0] */
      __IO uint32_t sesenddet                : 1; /* [2] */
      __IO uint32_t reserved2                : 29; /* [31:3] */

    } gotgint_bit;
  };

  /**
  * @brief otgfs gahbcfg configuration register, offset:0x08
  */
  union
  {
    __IO uint32_t gahbcfg;
    struct
    {
      __IO uint32_t glbintmsk                : 1; /* [0] */
      __IO uint32_t reserved1                : 6; /* [6:1] */
      __IO uint32_t nptxfemplvl              : 1; /* [7] */
      __IO uint32_t ptxfemplvl               : 1; /* [8] */
      __IO uint32_t reserved2                : 23; /* [31:9] */
    } gahbcfg_bit;
  };

  /**
  * @brief otgfs usb configuration register, offset:0x0C
  */
  union
  {
    __IO uint32_t gusbcfg;
    struct
    {
      __IO uint32_t toutcal                  : 3; /* [2:0] */
      __IO uint32_t reserved1                : 7; /* [9:3] */
      __IO uint32_t usbtrdtim                : 4; /* [13:10] */
      __IO uint32_t reserved2                : 15; /* [28:14] */
      __IO uint32_t fhstmode                 : 1; /* [29] */
      __IO uint32_t fdevmode                 : 1; /* [30] */
      __IO uint32_t cotxpkt                  : 1; /* [31] */
    } gusbcfg_bit;
  };

  /**
  * @brief otgfs reset register, offset:0x10
  */
  union
  {
    __IO uint32_t grstctl;
    struct
    {
      __IO uint32_t csftrst                  : 1; /* [0] */
      __IO uint32_t piusftrst                : 1; /* [1] */
      __IO uint32_t frmcntrst                : 1; /* [2] */
      __IO uint32_t reserved1                : 1; /* [3] */
      __IO uint32_t rxfflsh                  : 1; /* [4] */
      __IO uint32_t txfflsh                  : 1; /* [5] */
      __IO uint32_t txfnum                   : 5; /* [10:6] */
      __IO uint32_t reserved2                : 20; /* [30:11] */
      __IO uint32_t ahbidle                  : 1; /* [31] */
    } grstctl_bit;
  };

  /**
  * @brief otgfs core interrupt register, offset:0x14
  */
  union
  {
    __IO uint32_t gintsts;
    struct
    {
      __IO uint32_t curmode                  : 1; /* [0] */
      __IO uint32_t modemis                  : 1; /* [1] */
      __IO uint32_t otgint                   : 1; /* [2] */
      __IO uint32_t sof                      : 1; /* [3] */
      __IO uint32_t rxflvl                   : 1; /* [4] */
      __IO uint32_t nptxfemp                 : 1; /* [5] */
      __IO uint32_t ginnakeff                : 1; /* [6] */
      __IO uint32_t goutnakeff               : 1; /* [7] */
      __IO uint32_t reserved1                : 2; /* [9:8]] */
      __IO uint32_t erlysusp                 : 1; /* [10] */
      __IO uint32_t usbsusp                  : 1; /* [11] */
      __IO uint32_t usbrst                   : 1; /* [12] */
      __IO uint32_t enumdone                 : 1; /* [13] */
      __IO uint32_t isooutdrop               : 1; /* [14] */
      __IO uint32_t eopf                     : 1; /* [15] */
      __IO uint32_t reserved2                : 2; /* [17:16]] */
      __IO uint32_t ieptint                  : 1; /* [18] */
      __IO uint32_t oeptint                  : 1; /* [19] */
      __IO uint32_t incompisoin              : 1; /* [20] */
      __IO uint32_t incompip_incompisoout    : 1; /* [21] */
      __IO uint32_t reserved3                : 2; /* [23:22] */
      __IO uint32_t prtint                   : 1; /* [24] */
      __IO uint32_t hchint                   : 1; /* [25] */
      __IO uint32_t ptxfemp                  : 1; /* [26] */
      __IO uint32_t reserved4                : 1; /* [27] */
      __IO uint32_t conidschg                : 1; /* [28] */
      __IO uint32_t disconint                : 1; /* [29] */
      __IO uint32_t reserved5                : 1; /* [30] */
      __IO uint32_t wkupint                  : 1; /* [31] */
    } gintsts_bit;
  };

  /**
  * @brief otgfs interrupt mask register, offset:0x18
  */
  union
  {
    __IO uint32_t gintmsk;
    struct
    {
      __IO uint32_t reserved1                : 1; /* [0] */
      __IO uint32_t modemismsk               : 1; /* [1] */
      __IO uint32_t otgintmsk                : 1; /* [2] */
      __IO uint32_t sofmsk                   : 1; /* [3] */
      __IO uint32_t rxflvlmsk                : 1; /* [4] */
      __IO uint32_t nptxfempmsk              : 1; /* [5] */
      __IO uint32_t ginnakeffmsk             : 1; /* [6] */
      __IO uint32_t goutnakeffmsk            : 1; /* [7] */
      __IO uint32_t reserved2                : 2; /* [9:8]] */
      __IO uint32_t erlysuspmsk              : 1; /* [10] */
      __IO uint32_t usbsuspmsk               : 1; /* [11] */
      __IO uint32_t usbrstmsk                : 1; /* [12] */
      __IO uint32_t enumdonemsk              : 1; /* [13] */
      __IO uint32_t isooutdropmsk            : 1; /* [14] */
      __IO uint32_t eopfmsk                  : 1; /* [15] */
      __IO uint32_t reserved3                : 2; /* [17:16]] */
      __IO uint32_t ieptintmsk               : 1; /* [18] */
      __IO uint32_t oeptintmsk               : 1; /* [19] */
      __IO uint32_t incompisoinmsk           : 1; /* [20] */
      __IO uint32_t incompip_incompisooutmsk : 1; /* [21] */
      __IO uint32_t reserved4                : 2; /* [23:22] */
      __IO uint32_t prtintmsk                : 1; /* [24] */
      __IO uint32_t hchintmsk                : 1; /* [25] */
      __IO uint32_t ptxfempmsk               : 1; /* [26] */
      __IO uint32_t reserved5                : 1; /* [27] */
      __IO uint32_t conidschgmsk             : 1; /* [28] */
      __IO uint32_t disconintmsk             : 1; /* [29] */
      __IO uint32_t reserved6                : 1; /* [30] */
      __IO uint32_t wkupintmsk               : 1; /* [31] */
    } gintmsk_bit;
  };

   /**
  * @brief otgfs rx status debug read register, offset:0x1C
  */
  union
  {
    __IO uint32_t grxstsr;
    struct
    {
      __IO uint32_t eptnum                   : 4; /* [3:0] */
      __IO uint32_t bcnt                     : 11; /* [14:4] */
      __IO uint32_t dpid                     : 2; /* [16:15] */
      __IO uint32_t pktsts                   : 4; /* [20:17] */
      __IO uint32_t fn                       : 4; /* [24:21] */
      __IO uint32_t reserved1                : 7; /* [31:25] */
    } grxstsr_bit;
  };

  /**
  * @brief otgfs rx status read and pop register, offset:0x20
  */
  union
  {
    __IO uint32_t grxstsp;
    struct
    {
      __IO uint32_t chnum                    : 4; /* [3:0] */
      __IO uint32_t bcnt                     : 11; /* [14:4] */
      __IO uint32_t dpid                     : 2; /* [16:15] */
      __IO uint32_t pktsts                   : 4; /* [20:17] */
      __IO uint32_t reserved1                : 11; /* [31:21] */
    } grxstsp_bit;
  };

  /**
  * @brief otgfs rx fifo size register, offset:0x24
  */
  union
  {
    __IO uint32_t grxfsiz;
    struct
    {
      __IO uint32_t rxfdep                   : 16; /* [15:0] */
      __IO uint32_t reserved1                : 16; /* [31:16] */
    } grxfsiz_bit;
  };

  /**
  * @brief otgfs non-periodic and ept0 tx fifo size register, offset:0x28
  */
  union
  {
    __IO uint32_t gnptxfsiz_ept0tx;
    struct
    {
      __IO uint32_t nptxfstaddr              : 16; /* [15:0] */
      __IO uint32_t nptxfdep                 : 16; /* [31:16] */
    } gnptxfsiz_ept0tx_bit;
  };

  /**
  * @brief otgfs non-periodic tx fifo request queue status register, offset:0x2C
  */
  union
  {
    __IO uint32_t gnptxsts;
    struct
    {
      __IO uint32_t nptxfspcavail            : 16; /* [15:0] */
      __IO uint32_t nptxqspcavail            : 8; /* [23:16] */
      __IO uint32_t nptxqtop                 : 7; /* [30:24] */
    } gnptxsts_bit;
  };

  __IO uint32_t reserved2[2];

  /**
  * @brief otgfs general core configuration register, offset:0x38
  */
  union
  {
    __IO uint32_t gccfg;
    struct
    {
      __IO uint32_t reserved1                : 16; /* [15:0] */
      __IO uint32_t pwrdown                  : 1; /* [16] */
      __IO uint32_t lp_mode                  : 1; /* [17] */
      __IO uint32_t reserved2                : 2; /* [19:18] */
      __IO uint32_t sofouten                 : 1; /* [20] */
      __IO uint32_t vbusig                   : 1; /* [21] */
      __IO uint32_t reserved3                : 10; /* [31:22] */
    } gccfg_bit;
  };

  /**
  * @brief otgfs core id register, offset:0x3C
  */
  union
  {
    __IO uint32_t guid;
    struct
    {
      __IO uint32_t userid                 : 32; /* [31:0] */
    } guid_bit;
  };

  __IO uint32_t reserved3[48];

  /**
  * @brief otgfs host periodic tx fifo size register, offset:0x100
  */
  union
  {
    __IO uint32_t hptxfsiz;
    struct
    {
      __IO uint32_t ptxfstaddr               : 16; /* [15:0] */
      __IO uint32_t ptxfsize                 : 16; /* [31:16] */
    } hptxfsiz_bit;
  };

   /**
  * @brief otgfs host periodic tx fifo size register, offset:0x100
  */
  union
  {
    __IO uint32_t dieptxfn[7];
    struct
    {
      __IO uint32_t ineptxfstaddr            : 16; /* [15:0] */
      __IO uint32_t ineptxfdep               : 16; /* [31:16] */
    } dieptxfn_bit[7];
  };
} otg_global_type;


typedef struct
{
  /**
  * @brief otgfs host mode configuration register, offset:0x400
  */
  union
  {
    __IO uint32_t hcfg;
    struct
    {
      __IO uint32_t fslspclksel              : 2; /* [1:0] */
      __IO uint32_t fslssupp                 : 1; /* [2] */
      __IO uint32_t reserved1                : 29; /* [31:3] */
    } hcfg_bit;
  };

  /**
  * @brief otgfs host frame interval register, offset:0x404
  */
  union
  {
    __IO uint32_t hfir;
    struct
    {
      __IO uint32_t frint                   : 16; /* [15:0] */
      __IO uint32_t reserved1               : 16; /* [31:15] */
    } hfir_bit;
  };

  /**
  * @brief otgfs host frame number and time remaining register, offset:0x408
  */
  union
  {
    __IO uint32_t hfnum;
    struct
    {
      __IO uint32_t frnum                   : 16; /* [15:0] */
      __IO uint32_t ftrem                   : 16; /* [31:15] */
    } hfnum_bit;
  };

  __IO uint32_t reserved1;

  /**
  * @brief otgfs host periodic tx fifo request queue register, offset:0x410
  */
  union
  {
    __IO uint32_t hptxsts;
    struct
    {
      __IO uint32_t ptxfspcavil               : 16; /* [15:0] */
      __IO uint32_t ptxqspcavil               : 8; /* [23:16] */
      __IO uint32_t ptxqtop                  : 8; /* [31:24] */
    } hptxsts_bit;
  };

  /**
  * @brief otgfs host all channel interrupt register, offset:0x414
  */
  union
  {
    __IO uint32_t haint;
    struct
    {
      __IO uint32_t haint                    : 16; /* [15:0] */
      __IO uint32_t reserved1                : 16; /* [32:16] */
    } haint_bit;
  };

  /**
  * @brief otgfs host all channel interrupt mask register, offset:0x418
  */
  union
  {
    __IO uint32_t haintmsk;
    struct
    {
      __IO uint32_t haintmsk                 : 16; /* [15:0] */
      __IO uint32_t reserved1                : 16; /* [32:16] */
    } haintmsk_bit;
  };

  __IO uint32_t reserved2[9];

  /**
  * @brief otgfs host port control and status register, offset:0x440
  */
  union
  {
    __IO uint32_t hprt;
    struct
    {
      __IO uint32_t prtconsts                : 1; /* [0] */
      __IO uint32_t prtcondet                : 1; /* [1] */
      __IO uint32_t prtena                   : 1; /* [2] */
      __IO uint32_t prtenchng                : 1; /* [3] */
      __IO uint32_t prtovrcact               : 1; /* [4] */
      __IO uint32_t prtovrcchng              : 1; /* [5] */
      __IO uint32_t prtres                   : 1; /* [6] */
      __IO uint32_t prtsusp                  : 1; /* [7] */
      __IO uint32_t prtrst                   : 1; /* [8] */
      __IO uint32_t reserved1                : 1; /* [9] */
      __IO uint32_t prtlnsts                 : 2; /* [11:10] */
      __IO uint32_t prtpwr                   : 1; /* [12] */
      __IO uint32_t prttsctl                 : 4; /* [16:13] */
      __IO uint32_t prtspd                   : 2; /* [18:17] */
      __IO uint32_t reserved2                : 13; /* [31:19] */

    } hprt_bit;
  };
} otg_host_type;

typedef struct
{
  /**
  * @brief otgfs host channel x characterisic register, offset:0x500
  */
  union
  {
    __IO uint32_t hcchar;
    struct
    {
      __IO uint32_t mps                      : 11; /* [10:0] */
      __IO uint32_t eptnum                   : 4; /* [14:11] */
      __IO uint32_t eptdir                   : 1; /* [15] */
      __IO uint32_t reserved1                : 1; /* [16] */
      __IO uint32_t lspddev                  : 1; /* [17] */
      __IO uint32_t eptype                   : 2; /* [19:18] */
      __IO uint32_t mc                       : 2; /* [21:20] */
      __IO uint32_t devaddr                  : 7; /* [28:22] */
      __IO uint32_t oddfrm                   : 1; /* [29] */
      __IO uint32_t chdis                    : 1; /* [30] */
      __IO uint32_t chena                    : 1; /* [31] */
    } hcchar_bit;
  };

  /**
  * @brief otgfs host channel split control register, offset:0x504
  */
  union
  {
    __IO uint32_t hcsplt;
    struct
    {
      __IO uint32_t prtaddr                  : 7; /* [6:0] */
      __IO uint32_t hubaddr                  : 7; /* [13:7] */
      __IO uint32_t xactpos                  : 2; /* [15:14] */
      __IO uint32_t compsplt                 : 1; /* [16] */
      __IO uint32_t reserved1                : 14; /* [30:17] */
      __IO uint32_t spltena                  : 1; /* [31] */
    } hcsplt_bit;
  };

  /**
  * @brief otgfs host channel interrupt register, offset:0x508
  */
  union
  {
    __IO uint32_t hcint;
    struct
    {
      __IO uint32_t xferc                    : 1; /* [0] */
      __IO uint32_t chhltd                   : 1; /* [1] */
      __IO uint32_t reserved1                : 1; /* [2] */
      __IO uint32_t stall                    : 1; /* [3] */
      __IO uint32_t nak                      : 1; /* [4] */
      __IO uint32_t ack                      : 1; /* [5] */
      __IO uint32_t reserved2                : 1; /* [6] */
      __IO uint32_t xacterr                  : 1; /* [7] */
      __IO uint32_t bblerr                   : 1; /* [8] */
      __IO uint32_t frmovrun                 : 1; /* [9] */
      __IO uint32_t dtglerr                  : 1; /* [10] */
      __IO uint32_t reserved3                : 21; /* [31:11] */
    } hcint_bit;
  };

  /**
  * @brief otgfs host channel interrupt mask register, offset:0x50C
  */
  union
  {
    __IO uint32_t hcintmsk;
    struct
    {
      __IO uint32_t xfercmsk                 : 1; /* [0] */
      __IO uint32_t chhltdmsk                : 1; /* [1] */
      __IO uint32_t reserved1                : 1; /* [2] */
      __IO uint32_t stallmsk                 : 1; /* [3] */
      __IO uint32_t nakmsk                   : 1; /* [4] */
      __IO uint32_t ackmsk                   : 1; /* [5] */
      __IO uint32_t reserved2                : 1; /* [6] */
      __IO uint32_t xacterrmsk               : 1; /* [7] */
      __IO uint32_t bblerrmsk                : 1; /* [8] */
      __IO uint32_t frmovrunmsk              : 1; /* [9] */
      __IO uint32_t dtglerrmsk               : 1; /* [10] */
      __IO uint32_t reserved3                : 21; /* [31:11] */
    } hcintmsk_bit;
  };

  /**
  * @brief otgfs host channel transfer size register, offset:0x510
  */
  union
  {
    __IO uint32_t hctsiz;
    struct
    {
      __IO uint32_t xfersize                 : 19; /* [18:0] */
      __IO uint32_t pktcnt                   : 10; /* [28:19] */
      __IO uint32_t pid                      : 2; /* [30:29] */
      __IO uint32_t reserved1                : 1; /* [31] */
    } hctsiz_bit;
  };
  __IO uint32_t reserved3[3];

}otg_hchannel_type;


typedef struct
{
  /**
  * @brief otgfs device configuration register, offset:0x800
  */
  union
  {
    __IO uint32_t dcfg;
    struct
    {
      __IO uint32_t devspd                   : 2; /* [1:0] */
      __IO uint32_t nzstsouthshk             : 1; /* [2] */
      __IO uint32_t reserved1                : 1; /* [3] */
      __IO uint32_t devaddr                  : 7; /* [10:4] */
      __IO uint32_t perfrint                 : 2; /* [12:11] */
      __IO uint32_t reserved2                : 19; /* [31:13] */
    } dcfg_bit;
  };

  /**
  * @brief otgfs device controls register, offset:0x804
  */
  union
  {
    __IO uint32_t dctl;
    struct
    {
      __IO uint32_t rwkupsig                 : 1; /* [0] */
      __IO uint32_t sftdiscon                : 1; /* [1] */
      __IO uint32_t gnpinnaksts              : 1; /* [2] */
      __IO uint32_t goutnaksts               : 1; /* [3] */
      __IO uint32_t tstctl                   : 3; /* [6:4] */
      __IO uint32_t sgnpinak                 : 1; /* [7] */
      __IO uint32_t cgnpinak                 : 1; /* [8] */
      __IO uint32_t sgoutnak                 : 1; /* [9] */
      __IO uint32_t cgoutnak                 : 1; /* [10] */
      __IO uint32_t pwroprgdne               : 1; /* [11] */
      __IO uint32_t reserved1                : 20; /* [31:12] */
    } dctl_bit;
  };

  /**
  * @brief otgfs device status register, offset:0x80C
  */
  union
  {
    __IO uint32_t dsts;
    struct
    {
      __IO uint32_t suspsts                  : 1; /* [0] */
      __IO uint32_t enumspd                  : 2; /* [2:1] */
      __IO uint32_t eticerr                  : 1; /* [3] */
      __IO uint32_t reserved1                : 4; /* [7:4] */
      __IO uint32_t soffn                    : 14; /* [21:8] */
      __IO uint32_t reserved2                : 10; /* [31:22] */
    } dsts_bit;
  };

   __IO uint32_t reserved1;
  /**
  * @brief otgfs device in endpoint general interrupt mask register, offset:0x810
  */
  union
  {
    __IO uint32_t diepmsk;
    struct
    {
      __IO uint32_t xfercmsk                 : 1; /* [0] */
      __IO uint32_t eptdismsk                : 1; /* [1] */
      __IO uint32_t reserved1                : 1; /* [2] */
      __IO uint32_t timeoutmsk               : 1; /* [3] */
      __IO uint32_t intkntxfempmsk           : 1; /* [4] */
      __IO uint32_t intkneptmismsk           : 1; /* [5] */
      __IO uint32_t ineptnakmsk              : 1; /* [6] */
      __IO uint32_t reserved2                : 1; /* [7] */
      __IO uint32_t txfifoudrmsk             : 1; /* [8] */
      __IO uint32_t bnainmsk                 : 1; /* [9] */
      __IO uint32_t reserved3                : 22; /* [31:10] */
    } diepmsk_bit;
  };

  /**
  * @brief otgfs device out endpoint general interrupt mask register, offset:0x814
  */
  union
  {
    __IO uint32_t doepmsk;
    struct
    {
      __IO uint32_t xfercmsk                 : 1; /* [0] */
      __IO uint32_t eptdismsk                : 1; /* [1] */
      __IO uint32_t reserved1                : 1; /* [2] */
      __IO uint32_t setupmsk                 : 1; /* [3] */
      __IO uint32_t outtepdmsk               : 1; /* [4] */
      __IO uint32_t reserved2                : 1; /* [5] */
      __IO uint32_t b2bsetupmsk              : 1; /* [6] */
      __IO uint32_t reserved3                : 1; /* [7] */
      __IO uint32_t outperrmsk               : 1; /* [8] */
      __IO uint32_t bnaoutmsk                : 1; /* [9] */
      __IO uint32_t reserved4                : 22; /* [31:10] */
    } doepmsk_bit;
  };

  /**
  * @brief otgfs device all endpoint interrupt register, offset:0x818
  */
  union
  {
    __IO uint32_t daint;
    struct
    {
      __IO uint32_t ineptint                 : 16; /* [15:0] */
      __IO uint32_t outeptint                : 16; /* [31:16] */
    } daint_bit;
  };

  /**
  * @brief otgfs device all endpoint interrupt mask register, offset:0x81C
  */
  union
  {
    __IO uint32_t daintmsk;
    struct
    {
      __IO uint32_t ineptmsk                 : 16; /* [15:0] */
      __IO uint32_t outeptmsk                : 16; /* [31:16] */
    } daintmsk_bit;
  };

  __IO uint32_t reserved2[5];

  /**
  * @brief otgfs device in endpoint fifo empty interrupt mask register, offset:0x834
  */
  union
  {
    __IO uint32_t diepempmsk;
    struct
    {
      __IO uint32_t ineptxfemsk              : 16; /* [15:0] */
      __IO uint32_t reserved1                : 16; /* [31:16] */
    } diepempmsk_bit;
  };

} otg_device_type;

typedef struct
{
  /**
  * @brief otgfs device out endpoint control register, offset:0x900
  */
  union
  {
    __IO uint32_t diepctl;
    struct
    {
      __IO uint32_t mps                      : 11; /* [10:0] */
      __IO uint32_t reserved1                : 4; /* [14:11] */
      __IO uint32_t usbacept                 : 1; /* [15] */
      __IO uint32_t dpid                     : 1; /* [16] */
      __IO uint32_t naksts                   : 1; /* [17] */
      __IO uint32_t eptype                   : 2; /* [19:18] */
      __IO uint32_t reserved2                : 1; /* [20] */
      __IO uint32_t stall                    : 1; /* [21] */
      __IO uint32_t txfnum                   : 4; /* [25:22] */
      __IO uint32_t cnak                     : 1; /* [26] */
      __IO uint32_t snak                     : 1; /* [27] */
      __IO uint32_t setd0pid                 : 1; /* [28] */
      __IO uint32_t setd1pid                 : 1; /* [29] */
      __IO uint32_t eptdis                   : 1; /* [30] */
      __IO uint32_t eptena                   : 1; /* [31] */
    } diepctl_bit;
  };
  __IO uint32_t reserved1;

  /**
  * @brief otgfs device in endpoint interrupt register, offset:0x908
  */
  union
  {
    __IO uint32_t diepint;
    struct
    {
      __IO uint32_t xferc                    : 1; /* [0] */
      __IO uint32_t epdisd                   : 1; /* [1] */
      __IO uint32_t reserved1                : 1; /* [2] */
      __IO uint32_t timeout                  : 1; /* [3] */
      __IO uint32_t intkntxfemp              : 1; /* [4] */
      __IO uint32_t reserved2                : 1; /* [5] */
      __IO uint32_t ineptnak                 : 1; /* [6] */
      __IO uint32_t txfemp                   : 1; /* [7] */
      __IO uint32_t reserved3                : 24; /* [31:8] */
    } diepint_bit;
  };
  __IO uint32_t reserved2;

  /**
  * @brief otgfs device in endpoint transfer size register, offset:0x910 + endpoint number * 0x20
  */
  union
  {
    __IO uint32_t dieptsiz;
    struct
    {
      __IO uint32_t xfersize                 : 19; /* [18:0] */
      __IO uint32_t pktcnt                   : 10; /* [28:19] */
      __IO uint32_t mc                       : 2; /* [30:29] */
      __IO uint32_t reserved1                : 1; /* [31] */
    } dieptsiz_bit;
  };

  __IO uint32_t reserved3;

  /**
  * @brief otgfs device in endpoint tx fifo status register, offset:0x918 + endpoint number * 0x20
  */
  union
  {
    __IO uint32_t dtxfsts;
    struct
    {
      __IO uint32_t ineptxfsav               : 16; /* [15:0] */
      __IO uint32_t reserved1                : 16; /* [31:16] */
    } dtxfsts_bit;
  };

} otg_eptin_type;

typedef struct
{
  /**
  * @brief otgfs device out endpoint control register, offset:0xb00 + endpoint number * 0x20
  */
  union
  {
    __IO uint32_t doepctl;
    struct
    {
      __IO uint32_t mps                      : 11; /* [10:0] */
      __IO uint32_t reserved1                : 4; /* [14:11] */
      __IO uint32_t usbacept                 : 1; /* [15] */
      __IO uint32_t dpid                     : 1; /* [16] */
      __IO uint32_t naksts                   : 1; /* [17] */
      __IO uint32_t eptype                   : 2; /* [19:18] */
      __IO uint32_t snpm                     : 1; /* [20] */
      __IO uint32_t stall                    : 1; /* [21] */
      __IO uint32_t reserved2                : 4; /* [25:22] */
      __IO uint32_t cnak                     : 1; /* [26] */
      __IO uint32_t snak                     : 1; /* [27] */
      __IO uint32_t setd0pid                 : 1; /* [28] */
      __IO uint32_t setd1pid                 : 1; /* [29] */
      __IO uint32_t eptdis                   : 1; /* [30] */
      __IO uint32_t eptena                   : 1; /* [31] */
    } doepctl_bit;
  };
  __IO uint32_t reserved1;

  /**
  * @brief otgfs device out endpoint interrupt register, offset:0xb08 + endpoint number * 0x20
  */
  union
  {
    __IO uint32_t doepint;
    struct
    {
      __IO uint32_t xferc                    : 1; /* [0] */
      __IO uint32_t epdisd                   : 1; /* [1] */
      __IO uint32_t reserved1                : 1; /* [2] */
      __IO uint32_t setup                    : 1; /* [3] */
      __IO uint32_t outtepd                  : 1; /* [4] */
      __IO uint32_t reserved2                : 1; /* [5] */
      __IO uint32_t b2pstup                  : 1; /* [6] */
      __IO uint32_t reserved3                : 25; /* [31:7] */
    } doepint_bit;
  };
  __IO uint32_t reserved2;

  /**
  * @brief otgfs device out endpoint transfer size register, offset:0xb10 + endpoint number * 0x20
  */
  union
  {
    __IO uint32_t doeptsiz;
    struct
    {
      __IO uint32_t xfersize                 : 19; /* [18:0] */
      __IO uint32_t pktcnt                   : 10; /* [28:19] */
      __IO uint32_t rxdpid_setupcnt          : 2; /* [30:29] */
      __IO uint32_t reserved1                : 1; /* [31] */
    } doeptsiz_bit;
  };
} otg_eptout_type;

typedef struct
{
  /**
  * @brief otgfs power and clock gating control registers, offset:0xe00
  */
  union
  {
    __IO uint32_t pcgcctl;
    struct
    {
      __IO uint32_t stoppclk                 : 1; /* [0] */
      __IO uint32_t reserved1                : 3; /* [3:1] */
      __IO uint32_t suspendm                 : 1; /* [4] */
      __IO uint32_t reserved2                : 27; /* [31:5] */
    } pcgcctl_bit;
  };
} otg_pcgcctl_type;

/**
  * @}
  */

/** @defgroup USB_exported_functions
  * @{
  */

/**
  * @brief usb host and device offset address
  */
#define OTG_HOST_ADDR_OFFSET             0x400  /*!< usb host register offset address */
#define OTG_HOST_CHANNEL_ADDR_OFFSET     0x500  /*!< usb host channel register offset address */
#define OTG_DEVICE_ADDR_OFFSET           0x800  /*!< usb device register offset address */
#define OTG_DEVICE_EPTIN_ADDR_OFFSET     0x900  /*!< usb device endpoint in register offset address */
#define OTG_DEVICE_EPTOUT_ADDR_OFFSET    0xB00  /*!< usb device endpoint out register offset address */
#define OTG_PCGCCTL_ADDR_OFFSET          0xE00  /*!< usb power and clock control register offset address */
#define OTG_FIFO_ADDR_OFFSET             0x1000 /*!< usb fifo offset address */

/**
  * @brief usb host and device register define
  */
#define OTG1_GLOBAL ((otg_global_type *)(OTGFS1_BASE)) /*!< usb otg1 global register */
#define OTG_PCGCCTL(usbx) ((otg_pcgcctl_type *)((uint32_t)usbx + OTG_PCGCCTL_ADDR_OFFSET))                             /*!< usb power and clock control register */
#define OTG_DEVICE(usbx) ((otg_device_type *)((uint32_t)usbx + OTG_DEVICE_ADDR_OFFSET))                                /*!< usb device register */
#define OTG_HOST(usbx) ((otg_host_type *)((uint32_t)usbx + OTG_HOST_ADDR_OFFSET))                                      /*!< usb host register */
#define USB_CHL(usbx, n) ((otg_hchannel_type *)((uint32_t)usbx + OTG_HOST_CHANNEL_ADDR_OFFSET + n * 0x20))             /*!< usb channel n register */
#define USB_INEPT(usbx, eptn) ((otg_eptin_type *)((uint32_t)usbx + OTG_DEVICE_EPTIN_ADDR_OFFSET + eptn * 0x20))        /*!< usb device endpoint in register */
#define USB_OUTEPT(usbx, eptn) ((otg_eptout_type *)((uint32_t)usbx + OTG_DEVICE_EPTOUT_ADDR_OFFSET + eptn * 0x20))     /*!< usb device endpoint out register */
#define USB_FIFO(usbx, eptn) *(__IO uint32_t *)((uint32_t)usbx + OTG_FIFO_ADDR_OFFSET + eptn * 0x1000)                 /*!< usb fifo address */



typedef otg_global_type usb_reg_type;

/** @defgroup USB_exported_functions
  * @{
  */

#ifdef OTGFS_USB_GLOBAL
error_status usb_global_reset(otg_global_type *usbx);
void usb_global_init(otg_global_type *usbx);
otg_global_type *usb_global_select_core(uint8_t usb_id);
void usb_flush_tx_fifo(otg_global_type *usbx, uint32_t fifo_num);
void usb_flush_rx_fifo(otg_global_type *usbx);
void usb_global_interrupt_enable(otg_global_type *usbx, uint16_t interrupt, confirm_state new_state);
uint32_t usb_global_get_all_interrupt(otg_global_type *usbx);
void usb_global_clear_interrupt(otg_global_type *usbx, uint32_t flag);
void usb_interrupt_enable(otg_global_type *usbx);
void usb_interrupt_disable(otg_global_type *usbx);
void usb_set_rx_fifo(otg_global_type *usbx, uint16_t size);
void usb_set_tx_fifo(otg_global_type *usbx, uint8_t txfifo, uint16_t size);
void usb_global_set_mode(otg_global_type *usbx, uint32_t mode);
void usb_global_power_on(otg_global_type *usbx);
void usb_write_packet(otg_global_type *usbx, uint8_t *pusr_buf, uint16_t num, uint16_t nbytes);
void usb_read_packet(otg_global_type *usbx, uint8_t *pusr_buf, uint16_t num, uint16_t nbytes);
void usb_stop_phy_clk(otg_global_type *usbx);
void usb_open_phy_clk(otg_global_type *usbx);
#endif

#ifdef OTGFS_USB_DEVICE
void usb_ept_open(otg_global_type *usbx, usb_ept_info *ept_info);
void usb_ept_close(otg_global_type *usbx, usb_ept_info *ept_info);
void usb_ept_stall(otg_global_type *usbx, usb_ept_info *ept_info);
void usb_ept_clear_stall(otg_global_type *usbx, usb_ept_info *ept_info);
uint32_t usb_get_all_out_interrupt(otg_global_type *usbx);
uint32_t usb_get_all_in_interrupt(otg_global_type *usbx);
uint32_t usb_ept_out_interrupt(otg_global_type *usbx, uint32_t eptn);
uint32_t usb_ept_in_interrupt(otg_global_type *usbx, uint32_t eptn);
void usb_ept_out_clear(otg_global_type *usbx, uint32_t eptn, uint32_t flag);
void usb_ept_in_clear(otg_global_type *usbx, uint32_t eptn, uint32_t flag);
void usb_set_address(otg_global_type *usbx, uint8_t address);
void usb_ept0_start(otg_global_type *usbx);
void usb_ept0_setup(otg_global_type *usbx);
void usb_connect(otg_global_type *usbx);
void usb_disconnect(otg_global_type *usbx);
void usb_remote_wkup_set(otg_global_type *usbx);
void usb_remote_wkup_clear(otg_global_type *usbx);
uint8_t usb_suspend_status_get(otg_global_type *usbx);
#endif

#ifdef OTGFS_USB_HOST
void usb_port_power_on(otg_global_type *usbx, confirm_state state);
uint32_t usbh_get_frame(otg_global_type *usbx);
void usb_hc_enable(otg_global_type *usbx,
                   uint8_t chn,
                   uint8_t ept_num,
                   uint8_t dev_address,
                   uint8_t type,
                   uint16_t maxpacket,
                   uint8_t speed);
uint32_t usb_hch_read_interrupt(otg_global_type *usbx);
void usb_host_disable(otg_global_type *usbx);
void usb_hch_halt(otg_global_type *usbx, uint8_t chn);
void usbh_fsls_clksel(otg_global_type *usbx, uint8_t clk);
#endif
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
