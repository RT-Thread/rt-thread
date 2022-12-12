/**************************************************************************//**
 * @file     usbd.h
 * @brief    N9H30 USBD driver header file
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_USBD_H__
#define __NU_USBD_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_USBD_Driver USBD Driver
  @{
*/

/** @addtogroup N9H30_USBD_EXPORTED_CONSTANTS USBD Exported Constants
  @{
*/
/// @cond HIDDEN_SYMBOLS
#define USBD_MAX_EP     12

#define Maximum(a,b)    (a)>(b) ? (a) : (b)
#define Minimum(a,b)    (a)<(b) ? (a) : (b)


#define CEP     0xff    /*!< Control Endpoint  \hideinitializer */
#define EPA     0       /*!< Endpoint A  \hideinitializer */
#define EPB     1       /*!< Endpoint B  \hideinitializer */
#define EPC     2       /*!< Endpoint C  \hideinitializer */
#define EPD     3       /*!< Endpoint D  \hideinitializer */
#define EPE     4       /*!< Endpoint E  \hideinitializer */
#define EPF     5       /*!< Endpoint F  \hideinitializer */
#define EPG     6       /*!< Endpoint G  \hideinitializer */
#define EPH     7       /*!< Endpoint H  \hideinitializer */
#define EPI     8       /*!< Endpoint I  \hideinitializer */
#define EPJ     9       /*!< Endpoint J  \hideinitializer */
#define EPK     10      /*!< Endpoint K  \hideinitializer */
#define EPL     11      /*!< Endpoint L  \hideinitializer */

/* USB Request Type */
#define REQ_STANDARD        0x00
#define REQ_CLASS           0x20
#define REQ_VENDOR          0x40

/* USB Standard Request */
#define GET_STATUS          0x00
#define CLEAR_FEATURE       0x01
#define SET_FEATURE         0x03
#define SET_ADDRESS         0x05
#define GET_DESCRIPTOR      0x06
#define SET_DESCRIPTOR      0x07
#define GET_CONFIGURATION   0x08
#define SET_CONFIGURATION   0x09
#define GET_INTERFACE       0x0A
#define SET_INTERFACE       0x0B
#define SYNC_FRAME          0x0C

/* USB Descriptor Type */
#define DESC_DEVICE         0x01
#define DESC_CONFIG         0x02
#define DESC_STRING         0x03
#define DESC_INTERFACE      0x04
#define DESC_ENDPOINT       0x05
#define DESC_QUALIFIER      0x06
#define DESC_OTHERSPEED     0x07
#define DESC_IFPOWER        0x08
#define DESC_OTG            0x09

/* USB HID Descriptor Type */
#define DESC_HID            0x21
#define DESC_HID_RPT        0x22

/* USB Descriptor Length */
#define LEN_DEVICE          18
#define LEN_QUALIFIER       10
#define LEN_CONFIG          9
#define LEN_INTERFACE       9
#define LEN_ENDPOINT        7
#define LEN_OTG             5
#define LEN_HID             9

/* USB Endpoint Type */
#define EP_ISO              0x01
#define EP_BULK             0x02
#define EP_INT              0x03

#define EP_INPUT            0x80
#define EP_OUTPUT           0x00

/* USB Feature Selector */
#define FEATURE_DEVICE_REMOTE_WAKEUP    0x01
#define FEATURE_ENDPOINT_HALT           0x00
/// @endcond HIDDEN_SYMBOLS
/********************* Bit definition of CEPCTL register **********************/
#define USB_CEPCTL_NAKCLR               ((uint32_t)0x00000000)      /*!<NAK clear  \hideinitializer */
#define USB_CEPCTL_STALL                ((uint32_t)0x00000002)      /*!<Stall  \hideinitializer */
#define USB_CEPCTL_ZEROLEN              ((uint32_t)0x00000004)      /*!<Zero length packet  \hideinitializer */
#define USB_CEPCTL_FLUSH                ((uint32_t)0x00000008)      /*!<CEP flush  \hideinitializer */

/********************* Bit definition of EPxRSPCTL register **********************/
#define USB_EP_RSPCTL_FLUSH             ((uint32_t)0x00000001)      /*!<Buffer Flush  \hideinitializer */
#define USB_EP_RSPCTL_MODE_AUTO         ((uint32_t)0x00000000)      /*!<Auto-Validate Mode  \hideinitializer */
#define USB_EP_RSPCTL_MODE_MANUAL       ((uint32_t)0x00000002)      /*!<Manual-Validate Mode  \hideinitializer */
#define USB_EP_RSPCTL_MODE_FLY          ((uint32_t)0x00000004)      /*!<Fly Mode  \hideinitializer */
#define USB_EP_RSPCTL_MODE_MASK         ((uint32_t)0x00000006)      /*!<Mode Mask  \hideinitializer */
#define USB_EP_RSPCTL_TOGGLE            ((uint32_t)0x00000008)      /*!<Clear Toggle bit  \hideinitializer */
#define USB_EP_RSPCTL_HALT              ((uint32_t)0x00000010)      /*!<Endpoint halt  \hideinitializer */
#define USB_EP_RSPCTL_ZEROLEN           ((uint32_t)0x00000020)      /*!<Zero length packet IN  \hideinitializer */
#define USB_EP_RSPCTL_SHORTTXEN         ((uint32_t)0x00000040)      /*!<Packet end  \hideinitializer */
#define USB_EP_RSPCTL_DISBUF            ((uint32_t)0x00000080)      /*!<Disable buffer  \hideinitializer */

/********************* Bit definition of EPxCFG register **********************/
#define USB_EP_CFG_VALID                ((uint32_t)0x00000001)      /*!<Endpoint Valid  \hideinitializer */
#define USB_EP_CFG_TYPE_BULK            ((uint32_t)0x00000002)      /*!<Endpoint type - bulk  \hideinitializer */
#define USB_EP_CFG_TYPE_INT             ((uint32_t)0x00000004)      /*!<Endpoint type - interrupt  \hideinitializer */
#define USB_EP_CFG_TYPE_ISO             ((uint32_t)0x00000006)      /*!<Endpoint type - isochronous  \hideinitializer */
#define USB_EP_CFG_TYPE_MASK            ((uint32_t)0x00000006)      /*!<Endpoint type mask  \hideinitializer */
#define USB_EP_CFG_DIR_OUT              ((uint32_t)0x00000000)      /*!<OUT endpoint  \hideinitializer */
#define USB_EP_CFG_DIR_IN               ((uint32_t)0x00000008)      /*!<IN endpoint  \hideinitializer */


/*@}*/ /* end of group N9H30_USBD_EXPORTED_CONSTANTS */

/** @addtogroup N9H30_USBD_EXPORTED_STRUCT USBD Exported Struct
  @{
*/


/** \brief  Structure type of USB Setup Packet.
 */
typedef struct usbd_cmd_struct
{
    uint8_t  bmRequestType; /*!< Request type */
    uint8_t  bRequest;      /*!< Request */
    uint16_t wValue;        /*!< value */
    uint16_t wIndex;        /*!< index */
    uint16_t wLength;       /*!< length */

} S_USBD_CMD_T; /*!<USB Setup Packet Structure */


/** \brief  Structure type of Device Descriptor
 */
typedef struct s_usbd_info
{
    uint8_t *gu8DevDesc;            /*!< Device descriptor */
    uint8_t *gu8ConfigDesc;         /*!< Config descriptor */
    uint8_t **gu8StringDesc;        /*!< Pointer for USB String Descriptor pointers */
    uint8_t *gu8QualDesc;           /*!< Qualifier descriptor */
    uint8_t *gu8OtherConfigDesc;    /*!< Other Speed Config descriptor */
    uint8_t **gu8HidReportDesc;     /*!< Pointer for HID Report descriptor */
    uint32_t *gu32HidReportSize;    /*!< Pointer for HID Report descriptor Size */

} S_USBD_INFO_T; /*!<USB Information Structure */


/*@}*/ /* end of group N9H30_USBD_EXPORTED_STRUCT */

/// @cond HIDDEN_SYMBOLS
extern uint32_t g_u32EpStallLock;
extern uint8_t volatile g_usbd_Configured;
extern uint8_t g_usbd_ShortPacket;
extern uint8_t g_usbd_CtrlZero;
extern uint8_t g_usbd_UsbAddr;
extern uint8_t g_usbd_EpHalt[];
extern uint32_t volatile g_usbd_DmaDone;
extern uint32_t g_usbd_CtrlInSize;
extern S_USBD_INFO_T gsInfo;
extern S_USBD_CMD_T gUsbCmd;
/// @endcond /* HIDDEN_SYMBOLS */

/// @cond HIDDEN_SYMBOLS
typedef struct
{

    union
    {
        volatile uint32_t EPDAT;
        volatile uint8_t  EPDAT_BYTE;

    } ep;
    volatile uint32_t EPINTSTS;
    volatile uint32_t EPINTEN;
    volatile const  uint32_t EPDATCNT;
    volatile uint32_t EPRSPCTL;
    volatile uint32_t EPMPS;
    volatile uint32_t EPTXCNT;
    volatile uint32_t EPCFG;
    volatile uint32_t EPBUFSTART;
    volatile uint32_t EPBUFEND;

} USBD_EP_T;

typedef struct
{
    volatile const  uint32_t GINTSTS;
    uint32_t RESERVE0[1];
    volatile uint32_t GINTEN;
    uint32_t RESERVE1[1];
    volatile uint32_t BUSINTSTS;
    volatile uint32_t BUSINTEN;
    volatile uint32_t OPER;
    volatile const  uint32_t FRAMECNT;
    volatile uint32_t FADDR;
    volatile uint32_t TEST;
    union
    {
        volatile uint32_t CEPDAT;
        volatile uint8_t  CEPDAT_BYTE;
    } cep;
    volatile uint32_t CEPCTL;
    volatile uint32_t CEPINTEN;
    volatile uint32_t CEPINTSTS;
    volatile uint32_t CEPTXCNT;
    volatile const  uint32_t CEPRXCNT;
    volatile const  uint32_t CEPDATCNT;
    volatile const  uint32_t SETUP1_0;
    volatile const  uint32_t SETUP3_2;
    volatile const  uint32_t SETUP5_4;
    volatile const  uint32_t SETUP7_6;
    volatile uint32_t CEPBUFSTART;
    volatile uint32_t CEPBUFEND;
    volatile uint32_t DMACTL;
    volatile uint32_t DMACNT;
    USBD_EP_T EP[12];
    uint32_t RESERVE2[303];
    volatile uint32_t DMAADDR;
    volatile uint32_t PHYCTL;

} USBD_T;

#define USBD   ((USBD_T *) USBD_BA)




#define USBD_GINTSTS_USBIF_Pos           (0)                                               /*!< USBD GINTSTS: USBIF Position           */
#define USBD_GINTSTS_USBIF_Msk           (0x1ul << USBD_GINTSTS_USBIF_Pos)                 /*!< USBD GINTSTS: USBIF Mask               */

#define USBD_GINTSTS_CEPIF_Pos           (1)                                               /*!< USBD GINTSTS: CEPIF Position           */
#define USBD_GINTSTS_CEPIF_Msk           (0x1ul << USBD_GINTSTS_CEPIF_Pos)                 /*!< USBD GINTSTS: CEPIF Mask               */

#define USBD_GINTSTS_EPAIF_Pos           (2)                                               /*!< USBD GINTSTS: EPAIF Position           */
#define USBD_GINTSTS_EPAIF_Msk           (0x1ul << USBD_GINTSTS_EPAIF_Pos)                 /*!< USBD GINTSTS: EPAIF Mask               */

#define USBD_GINTSTS_EPBIF_Pos           (3)                                               /*!< USBD GINTSTS: EPBIF Position           */
#define USBD_GINTSTS_EPBIF_Msk           (0x1ul << USBD_GINTSTS_EPBIF_Pos)                 /*!< USBD GINTSTS: EPBIF Mask               */

#define USBD_GINTSTS_EPCIF_Pos           (4)                                               /*!< USBD GINTSTS: EPCIF Position           */
#define USBD_GINTSTS_EPCIF_Msk           (0x1ul << USBD_GINTSTS_EPCIF_Pos)                 /*!< USBD GINTSTS: EPCIF Mask               */

#define USBD_GINTSTS_EPDIF_Pos           (5)                                               /*!< USBD GINTSTS: EPDIF Position           */
#define USBD_GINTSTS_EPDIF_Msk           (0x1ul << USBD_GINTSTS_EPDIF_Pos)                 /*!< USBD GINTSTS: EPDIF Mask               */

#define USBD_GINTSTS_EPEIF_Pos           (6)                                               /*!< USBD GINTSTS: EPEIF Position           */
#define USBD_GINTSTS_EPEIF_Msk           (0x1ul << USBD_GINTSTS_EPEIF_Pos)                 /*!< USBD GINTSTS: EPEIF Mask               */

#define USBD_GINTSTS_EPFIF_Pos           (7)                                               /*!< USBD GINTSTS: EPFIF Position           */
#define USBD_GINTSTS_EPFIF_Msk           (0x1ul << USBD_GINTSTS_EPFIF_Pos)                 /*!< USBD GINTSTS: EPFIF Mask               */

#define USBD_GINTSTS_EPGIF_Pos           (8)                                               /*!< USBD GINTSTS: EPGIF Position           */
#define USBD_GINTSTS_EPGIF_Msk           (0x1ul << USBD_GINTSTS_EPGIF_Pos)                 /*!< USBD GINTSTS: EPGIF Mask               */

#define USBD_GINTSTS_EPHIF_Pos           (9)                                               /*!< USBD GINTSTS: EPHIF Position           */
#define USBD_GINTSTS_EPHIF_Msk           (0x1ul << USBD_GINTSTS_EPHIF_Pos)                 /*!< USBD GINTSTS: EPHIF Mask               */

#define USBD_GINTSTS_EPIIF_Pos           (10)                                              /*!< USBD GINTSTS: EPIIF Position           */
#define USBD_GINTSTS_EPIIF_Msk           (0x1ul << USBD_GINTSTS_EPIIF_Pos)                 /*!< USBD GINTSTS: EPIIF Mask               */

#define USBD_GINTSTS_EPJIF_Pos           (11)                                              /*!< USBD GINTSTS: EPJIF Position           */
#define USBD_GINTSTS_EPJIF_Msk           (0x1ul << USBD_GINTSTS_EPJIF_Pos)                 /*!< USBD GINTSTS: EPJIF Mask               */

#define USBD_GINTSTS_EPKIF_Pos           (12)                                              /*!< USBD GINTSTS: EPKIF Position           */
#define USBD_GINTSTS_EPKIF_Msk           (0x1ul << USBD_GINTSTS_EPKIF_Pos)                 /*!< USBD GINTSTS: EPKIF Mask               */

#define USBD_GINTSTS_EPLIF_Pos           (13)                                              /*!< USBD GINTSTS: EPLIF Position           */
#define USBD_GINTSTS_EPLIF_Msk           (0x1ul << USBD_GINTSTS_EPLIF_Pos)                 /*!< USBD GINTSTS: EPLIF Mask               */

#define USBD_GINTEN_USBIE_Pos            (0)                                               /*!< USBD GINTEN: USBIE Position            */
#define USBD_GINTEN_USBIE_Msk            (0x1ul << USBD_GINTEN_USBIE_Pos)                  /*!< USBD GINTEN: USBIE Mask                */

#define USBD_GINTEN_CEPIE_Pos            (1)                                               /*!< USBD GINTEN: CEPIE Position            */
#define USBD_GINTEN_CEPIE_Msk            (0x1ul << USBD_GINTEN_CEPIE_Pos)                  /*!< USBD GINTEN: CEPIE Mask                */

#define USBD_GINTEN_EPAIE_Pos            (2)                                               /*!< USBD GINTEN: EPAIE Position            */
#define USBD_GINTEN_EPAIE_Msk            (0x1ul << USBD_GINTEN_EPAIE_Pos)                  /*!< USBD GINTEN: EPAIE Mask                */

#define USBD_GINTEN_EPBIE_Pos            (3)                                               /*!< USBD GINTEN: EPBIE Position            */
#define USBD_GINTEN_EPBIE_Msk            (0x1ul << USBD_GINTEN_EPBIE_Pos)                  /*!< USBD GINTEN: EPBIE Mask                */

#define USBD_GINTEN_EPCIE_Pos            (4)                                               /*!< USBD GINTEN: EPCIE Position            */
#define USBD_GINTEN_EPCIE_Msk            (0x1ul << USBD_GINTEN_EPCIE_Pos)                  /*!< USBD GINTEN: EPCIE Mask                */

#define USBD_GINTEN_EPDIE_Pos            (5)                                               /*!< USBD GINTEN: EPDIE Position            */
#define USBD_GINTEN_EPDIE_Msk            (0x1ul << USBD_GINTEN_EPDIE_Pos)                  /*!< USBD GINTEN: EPDIE Mask                */

#define USBD_GINTEN_EPEIE_Pos            (6)                                               /*!< USBD GINTEN: EPEIE Position            */
#define USBD_GINTEN_EPEIE_Msk            (0x1ul << USBD_GINTEN_EPEIE_Pos)                  /*!< USBD GINTEN: EPEIE Mask                */

#define USBD_GINTEN_EPFIE_Pos            (7)                                               /*!< USBD GINTEN: EPFIE Position            */
#define USBD_GINTEN_EPFIE_Msk            (0x1ul << USBD_GINTEN_EPFIE_Pos)                  /*!< USBD GINTEN: EPFIE Mask                */

#define USBD_GINTEN_EPGIE_Pos            (8)                                               /*!< USBD GINTEN: EPGIE Position            */
#define USBD_GINTEN_EPGIE_Msk            (0x1ul << USBD_GINTEN_EPGIE_Pos)                  /*!< USBD GINTEN: EPGIE Mask                */

#define USBD_GINTEN_EPHIE_Pos            (9)                                               /*!< USBD GINTEN: EPHIE Position            */
#define USBD_GINTEN_EPHIE_Msk            (0x1ul << USBD_GINTEN_EPHIE_Pos)                  /*!< USBD GINTEN: EPHIE Mask                */

#define USBD_GINTEN_EPIIE_Pos            (10)                                              /*!< USBD GINTEN: EPIIE Position            */
#define USBD_GINTEN_EPIIE_Msk            (0x1ul << USBD_GINTEN_EPIIE_Pos)                  /*!< USBD GINTEN: EPIIE Mask                */

#define USBD_GINTEN_EPJIE_Pos            (11)                                              /*!< USBD GINTEN: EPJIE Position            */
#define USBD_GINTEN_EPJIE_Msk            (0x1ul << USBD_GINTEN_EPJIE_Pos)                  /*!< USBD GINTEN: EPJIE Mask                */

#define USBD_GINTEN_EPKIE_Pos            (12)                                              /*!< USBD GINTEN: EPKIE Position            */
#define USBD_GINTEN_EPKIE_Msk            (0x1ul << USBD_GINTEN_EPKIE_Pos)                  /*!< USBD GINTEN: EPKIE Mask                */

#define USBD_GINTEN_EPLIE_Pos            (13)                                              /*!< USBD GINTEN: EPLIE Position            */
#define USBD_GINTEN_EPLIE_Msk            (0x1ul << USBD_GINTEN_EPLIE_Pos)                  /*!< USBD GINTEN: EPLIE Mask                */

#define USBD_BUSINTSTS_SOFIF_Pos         (0)                                               /*!< USBD BUSINTSTS: SOFIF Position         */
#define USBD_BUSINTSTS_SOFIF_Msk         (0x1ul << USBD_BUSINTSTS_SOFIF_Pos)               /*!< USBD BUSINTSTS: SOFIF Mask             */

#define USBD_BUSINTSTS_RSTIF_Pos         (1)                                               /*!< USBD BUSINTSTS: RSTIF Position         */
#define USBD_BUSINTSTS_RSTIF_Msk         (0x1ul << USBD_BUSINTSTS_RSTIF_Pos)               /*!< USBD BUSINTSTS: RSTIF Mask             */

#define USBD_BUSINTSTS_RESUMEIF_Pos      (2)                                               /*!< USBD BUSINTSTS: RESUMEIF Position      */
#define USBD_BUSINTSTS_RESUMEIF_Msk      (0x1ul << USBD_BUSINTSTS_RESUMEIF_Pos)            /*!< USBD BUSINTSTS: RESUMEIF Mask          */

#define USBD_BUSINTSTS_SUSPENDIF_Pos     (3)                                               /*!< USBD BUSINTSTS: SUSPENDIF Position     */
#define USBD_BUSINTSTS_SUSPENDIF_Msk     (0x1ul << USBD_BUSINTSTS_SUSPENDIF_Pos)           /*!< USBD BUSINTSTS: SUSPENDIF Mask         */

#define USBD_BUSINTSTS_HISPDIF_Pos       (4)                                               /*!< USBD BUSINTSTS: HISPDIF Position       */
#define USBD_BUSINTSTS_HISPDIF_Msk       (0x1ul << USBD_BUSINTSTS_HISPDIF_Pos)             /*!< USBD BUSINTSTS: HISPDIF Mask           */

#define USBD_BUSINTSTS_DMADONEIF_Pos     (5)                                               /*!< USBD BUSINTSTS: DMADONEIF Position     */
#define USBD_BUSINTSTS_DMADONEIF_Msk     (0x1ul << USBD_BUSINTSTS_DMADONEIF_Pos)           /*!< USBD BUSINTSTS: DMADONEIF Mask         */

#define USBD_BUSINTSTS_PHYCLKVLDIF_Pos   (6)                                               /*!< USBD BUSINTSTS: PHYCLKVLDIF Position   */
#define USBD_BUSINTSTS_PHYCLKVLDIF_Msk   (0x1ul << USBD_BUSINTSTS_PHYCLKVLDIF_Pos)         /*!< USBD BUSINTSTS: PHYCLKVLDIF Mask       */

#define USBD_BUSINTSTS_VBUSDETIF_Pos     (8)                                               /*!< USBD BUSINTSTS: VBUSDETIF Position     */
#define USBD_BUSINTSTS_VBUSDETIF_Msk     (0x1ul << USBD_BUSINTSTS_VBUSDETIF_Pos)           /*!< USBD BUSINTSTS: VBUSDETIF Mask         */

#define USBD_BUSINTEN_SOFIEN_Pos         (0)                                               /*!< USBD BUSINTEN: SOFIEN Position         */
#define USBD_BUSINTEN_SOFIEN_Msk         (0x1ul << USBD_BUSINTEN_SOFIEN_Pos)               /*!< USBD BUSINTEN: SOFIEN Mask             */

#define USBD_BUSINTEN_RSTIEN_Pos         (1)                                               /*!< USBD BUSINTEN: RSTIEN Position         */
#define USBD_BUSINTEN_RSTIEN_Msk         (0x1ul << USBD_BUSINTEN_RSTIEN_Pos)               /*!< USBD BUSINTEN: RSTIEN Mask             */

#define USBD_BUSINTEN_RESUMEIEN_Pos      (2)                                               /*!< USBD BUSINTEN: RESUMEIEN Position      */
#define USBD_BUSINTEN_RESUMEIEN_Msk      (0x1ul << USBD_BUSINTEN_RESUMEIEN_Pos)            /*!< USBD BUSINTEN: RESUMEIEN Mask          */

#define USBD_BUSINTEN_SUSPENDIEN_Pos     (3)                                               /*!< USBD BUSINTEN: SUSPENDIEN Position     */
#define USBD_BUSINTEN_SUSPENDIEN_Msk     (0x1ul << USBD_BUSINTEN_SUSPENDIEN_Pos)           /*!< USBD BUSINTEN: SUSPENDIEN Mask         */

#define USBD_BUSINTEN_HISPDIEN_Pos       (4)                                               /*!< USBD BUSINTEN: HISPDIEN Position       */
#define USBD_BUSINTEN_HISPDIEN_Msk       (0x1ul << USBD_BUSINTEN_HISPDIEN_Pos)             /*!< USBD BUSINTEN: HISPDIEN Mask           */

#define USBD_BUSINTEN_DMADONEIEN_Pos     (5)                                               /*!< USBD BUSINTEN: DMADONEIEN Position     */
#define USBD_BUSINTEN_DMADONEIEN_Msk     (0x1ul << USBD_BUSINTEN_DMADONEIEN_Pos)           /*!< USBD BUSINTEN: DMADONEIEN Mask         */

#define USBD_BUSINTEN_PHYCLKVLDIEN_Pos   (6)                                               /*!< USBD BUSINTEN: PHYCLKVLDIEN Position   */
#define USBD_BUSINTEN_PHYCLKVLDIEN_Msk   (0x1ul << USBD_BUSINTEN_PHYCLKVLDIEN_Pos)         /*!< USBD BUSINTEN: PHYCLKVLDIEN Mask       */

#define USBD_BUSINTEN_VBUSDETIEN_Pos     (8)                                               /*!< USBD BUSINTEN: VBUSDETIEN Position     */
#define USBD_BUSINTEN_VBUSDETIEN_Msk     (0x1ul << USBD_BUSINTEN_VBUSDETIEN_Pos)           /*!< USBD BUSINTEN: VBUSDETIEN Mask         */

#define USBD_OPER_RESUMEEN_Pos           (0)                                               /*!< USBD OPER: RESUMEEN Position           */
#define USBD_OPER_RESUMEEN_Msk           (0x1ul << USBD_OPER_RESUMEEN_Pos)                 /*!< USBD OPER: RESUMEEN Mask               */

#define USBD_OPER_HISPDEN_Pos            (1)                                               /*!< USBD OPER: HISPDEN Position            */
#define USBD_OPER_HISPDEN_Msk            (0x1ul << USBD_OPER_HISPDEN_Pos)                  /*!< USBD OPER: HISPDEN Mask                */

#define USBD_OPER_CURSPD_Pos             (2)                                               /*!< USBD OPER: CURSPD Position             */
#define USBD_OPER_CURSPD_Msk             (0x1ul << USBD_OPER_CURSPD_Pos)                   /*!< USBD OPER: CURSPD Mask                 */

#define USBD_FRAMECNT_MFRAMECNT_Pos      (0)                                               /*!< USBD FRAMECNT: MFRAMECNT Position      */
#define USBD_FRAMECNT_MFRAMECNT_Msk      (0x7ul << USBD_FRAMECNT_MFRAMECNT_Pos)            /*!< USBD FRAMECNT: MFRAMECNT Mask          */

#define USBD_FRAMECNT_FRAMECNT_Pos       (3)                                               /*!< USBD FRAMECNT: FRAMECNT Position       */
#define USBD_FRAMECNT_FRAMECNT_Msk       (0x7fful << USBD_FRAMECNT_FRAMECNT_Pos)           /*!< USBD FRAMECNT: FRAMECNT Mask           */

#define USBD_FADDR_FADDR_Pos             (0)                                               /*!< USBD FADDR: FADDR Position             */
#define USBD_FADDR_FADDR_Msk             (0x7ful << USBD_FADDR_FADDR_Pos)                  /*!< USBD FADDR: FADDR Mask                 */

#define USBD_TEST_TESTMODE_Pos           (0)                                               /*!< USBD TEST: TESTMODE Position           */
#define USBD_TEST_TESTMODE_Msk           (0x7ul << USBD_TEST_TESTMODE_Pos)                 /*!< USBD TEST: TESTMODE Mask               */

#define USBD_CEPDAT_DAT_Pos              (0)                                               /*!< USBD CEPDAT: DAT Position              */
#define USBD_CEPDAT_DAT_Msk              (0xfffffffful << USBD_CEPDAT_DAT_Pos)             /*!< USBD CEPDAT: DAT Mask                  */

#define USBD_CEPCTL_NAKCLR_Pos           (0)                                               /*!< USBD CEPCTL: NAKCLR Position           */
#define USBD_CEPCTL_NAKCLR_Msk           (0x1ul << USBD_CEPCTL_NAKCLR_Pos)                 /*!< USBD CEPCTL: NAKCLR Mask               */

#define USBD_CEPCTL_STALLEN_Pos          (1)                                               /*!< USBD CEPCTL: STALLEN Position          */
#define USBD_CEPCTL_STALLEN_Msk          (0x1ul << USBD_CEPCTL_STALLEN_Pos)                /*!< USBD CEPCTL: STALLEN Mask              */

#define USBD_CEPCTL_ZEROLEN_Pos          (2)                                               /*!< USBD CEPCTL: ZEROLEN Position          */
#define USBD_CEPCTL_ZEROLEN_Msk          (0x1ul << USBD_CEPCTL_ZEROLEN_Pos)                /*!< USBD CEPCTL: ZEROLEN Mask              */

#define USBD_CEPCTL_FLUSH_Pos            (3)                                               /*!< USBD CEPCTL: FLUSH Position            */
#define USBD_CEPCTL_FLUSH_Msk            (0x1ul << USBD_CEPCTL_FLUSH_Pos)                  /*!< USBD CEPCTL: FLUSH Mask                */

#define USBD_CEPINTEN_SETUPTKIEN_Pos     (0)                                               /*!< USBD CEPINTEN: SETUPTKIEN Position     */
#define USBD_CEPINTEN_SETUPTKIEN_Msk     (0x1ul << USBD_CEPINTEN_SETUPTKIEN_Pos)           /*!< USBD CEPINTEN: SETUPTKIEN Mask         */

#define USBD_CEPINTEN_SETUPPKIEN_Pos     (1)                                               /*!< USBD CEPINTEN: SETUPPKIEN Position     */
#define USBD_CEPINTEN_SETUPPKIEN_Msk     (0x1ul << USBD_CEPINTEN_SETUPPKIEN_Pos)           /*!< USBD CEPINTEN: SETUPPKIEN Mask         */

#define USBD_CEPINTEN_OUTTKIEN_Pos       (2)                                               /*!< USBD CEPINTEN: OUTTKIEN Position       */
#define USBD_CEPINTEN_OUTTKIEN_Msk       (0x1ul << USBD_CEPINTEN_OUTTKIEN_Pos)             /*!< USBD CEPINTEN: OUTTKIEN Mask           */

#define USBD_CEPINTEN_INTKIEN_Pos        (3)                                               /*!< USBD CEPINTEN: INTKIEN Position        */
#define USBD_CEPINTEN_INTKIEN_Msk        (0x1ul << USBD_CEPINTEN_INTKIEN_Pos)              /*!< USBD CEPINTEN: INTKIEN Mask            */

#define USBD_CEPINTEN_PINGIEN_Pos        (4)                                               /*!< USBD CEPINTEN: PINGIEN Position        */
#define USBD_CEPINTEN_PINGIEN_Msk        (0x1ul << USBD_CEPINTEN_PINGIEN_Pos)              /*!< USBD CEPINTEN: PINGIEN Mask            */

#define USBD_CEPINTEN_TXPKIEN_Pos        (5)                                               /*!< USBD CEPINTEN: TXPKIEN Position        */
#define USBD_CEPINTEN_TXPKIEN_Msk        (0x1ul << USBD_CEPINTEN_TXPKIEN_Pos)              /*!< USBD CEPINTEN: TXPKIEN Mask            */

#define USBD_CEPINTEN_RXPKIEN_Pos        (6)                                               /*!< USBD CEPINTEN: RXPKIEN Position        */
#define USBD_CEPINTEN_RXPKIEN_Msk        (0x1ul << USBD_CEPINTEN_RXPKIEN_Pos)              /*!< USBD CEPINTEN: RXPKIEN Mask            */

#define USBD_CEPINTEN_NAKIEN_Pos         (7)                                               /*!< USBD CEPINTEN: NAKIEN Position         */
#define USBD_CEPINTEN_NAKIEN_Msk         (0x1ul << USBD_CEPINTEN_NAKIEN_Pos)               /*!< USBD CEPINTEN: NAKIEN Mask             */

#define USBD_CEPINTEN_STALLIEN_Pos       (8)                                               /*!< USBD CEPINTEN: STALLIEN Position       */
#define USBD_CEPINTEN_STALLIEN_Msk       (0x1ul << USBD_CEPINTEN_STALLIEN_Pos)             /*!< USBD CEPINTEN: STALLIEN Mask           */

#define USBD_CEPINTEN_ERRIEN_Pos         (9)                                               /*!< USBD CEPINTEN: ERRIEN Position         */
#define USBD_CEPINTEN_ERRIEN_Msk         (0x1ul << USBD_CEPINTEN_ERRIEN_Pos)               /*!< USBD CEPINTEN: ERRIEN Mask             */

#define USBD_CEPINTEN_STSDONEIEN_Pos     (10)                                              /*!< USBD CEPINTEN: STSDONEIEN Position     */
#define USBD_CEPINTEN_STSDONEIEN_Msk     (0x1ul << USBD_CEPINTEN_STSDONEIEN_Pos)           /*!< USBD CEPINTEN: STSDONEIEN Mask         */

#define USBD_CEPINTEN_BUFFULLIEN_Pos     (11)                                              /*!< USBD CEPINTEN: BUFFULLIEN Position     */
#define USBD_CEPINTEN_BUFFULLIEN_Msk     (0x1ul << USBD_CEPINTEN_BUFFULLIEN_Pos)           /*!< USBD CEPINTEN: BUFFULLIEN Mask         */

#define USBD_CEPINTEN_BUFEMPTYIEN_Pos    (12)                                              /*!< USBD CEPINTEN: BUFEMPTYIEN Position    */
#define USBD_CEPINTEN_BUFEMPTYIEN_Msk    (0x1ul << USBD_CEPINTEN_BUFEMPTYIEN_Pos)          /*!< USBD CEPINTEN: BUFEMPTYIEN Mask        */

#define USBD_CEPINTSTS_SETUPTKIF_Pos     (0)                                               /*!< USBD CEPINTSTS: SETUPTKIF Position     */
#define USBD_CEPINTSTS_SETUPTKIF_Msk     (0x1ul << USBD_CEPINTSTS_SETUPTKIF_Pos)           /*!< USBD CEPINTSTS: SETUPTKIF Mask         */

#define USBD_CEPINTSTS_SETUPPKIF_Pos     (1)                                               /*!< USBD CEPINTSTS: SETUPPKIF Position     */
#define USBD_CEPINTSTS_SETUPPKIF_Msk     (0x1ul << USBD_CEPINTSTS_SETUPPKIF_Pos)           /*!< USBD CEPINTSTS: SETUPPKIF Mask         */

#define USBD_CEPINTSTS_OUTTKIF_Pos       (2)                                               /*!< USBD CEPINTSTS: OUTTKIF Position       */
#define USBD_CEPINTSTS_OUTTKIF_Msk       (0x1ul << USBD_CEPINTSTS_OUTTKIF_Pos)             /*!< USBD CEPINTSTS: OUTTKIF Mask           */

#define USBD_CEPINTSTS_INTKIF_Pos        (3)                                               /*!< USBD CEPINTSTS: INTKIF Position        */
#define USBD_CEPINTSTS_INTKIF_Msk        (0x1ul << USBD_CEPINTSTS_INTKIF_Pos)              /*!< USBD CEPINTSTS: INTKIF Mask            */

#define USBD_CEPINTSTS_PINGIF_Pos        (4)                                               /*!< USBD CEPINTSTS: PINGIF Position        */
#define USBD_CEPINTSTS_PINGIF_Msk        (0x1ul << USBD_CEPINTSTS_PINGIF_Pos)              /*!< USBD CEPINTSTS: PINGIF Mask            */

#define USBD_CEPINTSTS_TXPKIF_Pos        (5)                                               /*!< USBD CEPINTSTS: TXPKIF Position        */
#define USBD_CEPINTSTS_TXPKIF_Msk        (0x1ul << USBD_CEPINTSTS_TXPKIF_Pos)              /*!< USBD CEPINTSTS: TXPKIF Mask            */

#define USBD_CEPINTSTS_RXPKIF_Pos        (6)                                               /*!< USBD CEPINTSTS: RXPKIF Position        */
#define USBD_CEPINTSTS_RXPKIF_Msk        (0x1ul << USBD_CEPINTSTS_RXPKIF_Pos)              /*!< USBD CEPINTSTS: RXPKIF Mask            */

#define USBD_CEPINTSTS_NAKIF_Pos         (7)                                               /*!< USBD CEPINTSTS: NAKIF Position         */
#define USBD_CEPINTSTS_NAKIF_Msk         (0x1ul << USBD_CEPINTSTS_NAKIF_Pos)               /*!< USBD CEPINTSTS: NAKIF Mask             */

#define USBD_CEPINTSTS_STALLIF_Pos       (8)                                               /*!< USBD CEPINTSTS: STALLIF Position       */
#define USBD_CEPINTSTS_STALLIF_Msk       (0x1ul << USBD_CEPINTSTS_STALLIF_Pos)             /*!< USBD CEPINTSTS: STALLIF Mask           */

#define USBD_CEPINTSTS_ERRIF_Pos         (9)                                               /*!< USBD CEPINTSTS: ERRIF Position         */
#define USBD_CEPINTSTS_ERRIF_Msk         (0x1ul << USBD_CEPINTSTS_ERRIF_Pos)               /*!< USBD CEPINTSTS: ERRIF Mask             */

#define USBD_CEPINTSTS_STSDONEIF_Pos     (10)                                              /*!< USBD CEPINTSTS: STSDONEIF Position     */
#define USBD_CEPINTSTS_STSDONEIF_Msk     (0x1ul << USBD_CEPINTSTS_STSDONEIF_Pos)           /*!< USBD CEPINTSTS: STSDONEIF Mask         */

#define USBD_CEPINTSTS_BUFFULLIF_Pos     (11)                                              /*!< USBD CEPINTSTS: BUFFULLIF Position     */
#define USBD_CEPINTSTS_BUFFULLIF_Msk     (0x1ul << USBD_CEPINTSTS_BUFFULLIF_Pos)           /*!< USBD CEPINTSTS: BUFFULLIF Mask         */

#define USBD_CEPINTSTS_BUFEMPTYIF_Pos    (12)                                              /*!< USBD CEPINTSTS: BUFEMPTYIF Position    */
#define USBD_CEPINTSTS_BUFEMPTYIF_Msk    (0x1ul << USBD_CEPINTSTS_BUFEMPTYIF_Pos)          /*!< USBD CEPINTSTS: BUFEMPTYIF Mask        */

#define USBD_CEPTXCNT_TXCNT_Pos          (0)                                               /*!< USBD CEPTXCNT: TXCNT Position          */
#define USBD_CEPTXCNT_TXCNT_Msk          (0xfful << USBD_CEPTXCNT_TXCNT_Pos)               /*!< USBD CEPTXCNT: TXCNT Mask              */

#define USBD_CEPRXCNT_RXCNT_Pos          (0)                                               /*!< USBD CEPRXCNT: RXCNT Position          */
#define USBD_CEPRXCNT_RXCNT_Msk          (0xfful << USBD_CEPRXCNT_RXCNT_Pos)               /*!< USBD CEPRXCNT: RXCNT Mask              */

#define USBD_CEPDATCNT_DATCNT_Pos        (0)                                               /*!< USBD CEPDATCNT: DATCNT Position        */
#define USBD_CEPDATCNT_DATCNT_Msk        (0xfffful << USBD_CEPDATCNT_DATCNT_Pos)           /*!< USBD CEPDATCNT: DATCNT Mask            */

#define USBD_SETUP1_0_SETUP0_Pos         (0)                                               /*!< USBD SETUP1_0: SETUP0 Position         */
#define USBD_SETUP1_0_SETUP0_Msk         (0xfful << USBD_SETUP1_0_SETUP0_Pos)              /*!< USBD SETUP1_0: SETUP0 Mask             */

#define USBD_SETUP1_0_SETUP1_Pos         (8)                                               /*!< USBD SETUP1_0: SETUP1 Position         */
#define USBD_SETUP1_0_SETUP1_Msk         (0xfful << USBD_SETUP1_0_SETUP1_Pos)              /*!< USBD SETUP1_0: SETUP1 Mask             */

#define USBD_SETUP3_2_SETUP2_Pos         (0)                                               /*!< USBD SETUP3_2: SETUP2 Position         */
#define USBD_SETUP3_2_SETUP2_Msk         (0xfful << USBD_SETUP3_2_SETUP2_Pos)              /*!< USBD SETUP3_2: SETUP2 Mask             */

#define USBD_SETUP3_2_SETUP3_Pos         (8)                                               /*!< USBD SETUP3_2: SETUP3 Position         */
#define USBD_SETUP3_2_SETUP3_Msk         (0xfful << USBD_SETUP3_2_SETUP3_Pos)              /*!< USBD SETUP3_2: SETUP3 Mask             */

#define USBD_SETUP5_4_SETUP4_Pos         (0)                                               /*!< USBD SETUP5_4: SETUP4 Position         */
#define USBD_SETUP5_4_SETUP4_Msk         (0xfful << USBD_SETUP5_4_SETUP4_Pos)              /*!< USBD SETUP5_4: SETUP4 Mask             */

#define USBD_SETUP5_4_SETUP5_Pos         (8)                                               /*!< USBD SETUP5_4: SETUP5 Position         */
#define USBD_SETUP5_4_SETUP5_Msk         (0xfful << USBD_SETUP5_4_SETUP5_Pos)              /*!< USBD SETUP5_4: SETUP5 Mask             */

#define USBD_SETUP7_6_SETUP6_Pos         (0)                                               /*!< USBD SETUP7_6: SETUP6 Position         */
#define USBD_SETUP7_6_SETUP6_Msk         (0xfful << USBD_SETUP7_6_SETUP6_Pos)              /*!< USBD SETUP7_6: SETUP6 Mask             */

#define USBD_SETUP7_6_SETUP7_Pos         (8)                                               /*!< USBD SETUP7_6: SETUP7 Position         */
#define USBD_SETUP7_6_SETUP7_Msk         (0xfful << USBD_SETUP7_6_SETUP7_Pos)              /*!< USBD SETUP7_6: SETUP7 Mask             */

#define USBD_CEPBUFSTART_SADDR_Pos       (0)                                               /*!< USBD CEPBUFSTART: SADDR Position       */
#define USBD_CEPBUFSTART_SADDR_Msk       (0xffful << USBD_CEPBUFSTART_SADDR_Pos)           /*!< USBD CEPBUFSTART: SADDR Mask           */

#define USBD_CEPBUFEND_EADDR_Pos         (0)                                               /*!< USBD CEPBUFEND: EADDR Position         */
#define USBD_CEPBUFEND_EADDR_Msk         (0xffful << USBD_CEPBUFEND_EADDR_Pos)             /*!< USBD CEPBUFEND: EADDR Mask             */

#define USBD_DMACTL_EPNUM_Pos            (0)                                               /*!< USBD DMACTL: EPNUM Position            */
#define USBD_DMACTL_EPNUM_Msk            (0xful << USBD_DMACTL_EPNUM_Pos)                  /*!< USBD DMACTL: EPNUM Mask                */

#define USBD_DMACTL_DMARD_Pos            (4)                                               /*!< USBD DMACTL: DMARD Position            */
#define USBD_DMACTL_DMARD_Msk            (0x1ul << USBD_DMACTL_DMARD_Pos)                  /*!< USBD DMACTL: DMARD Mask                */

#define USBD_DMACTL_DMAEN_Pos            (5)                                               /*!< USBD DMACTL: DMAEN Position            */
#define USBD_DMACTL_DMAEN_Msk            (0x1ul << USBD_DMACTL_DMAEN_Pos)                  /*!< USBD DMACTL: DMAEN Mask                */

#define USBD_DMACTL_SGEN_Pos             (6)                                               /*!< USBD DMACTL: SGEN Position             */
#define USBD_DMACTL_SGEN_Msk             (0x1ul << USBD_DMACTL_SGEN_Pos)                   /*!< USBD DMACTL: SGEN Mask                 */

#define USBD_DMACTL_DMARST_Pos           (7)                                               /*!< USBD DMACTL: DMARST Position           */
#define USBD_DMACTL_DMARST_Msk           (0x1ul << USBD_DMACTL_DMARST_Pos)                 /*!< USBD DMACTL: DMARST Mask               */

#define USBD_DMACNT_DMACNT_Pos           (0)                                               /*!< USBD DMACNT: DMACNT Position           */
#define USBD_DMACNT_DMACNT_Msk           (0xffffful << USBD_DMACNT_DMACNT_Pos)             /*!< USBD DMACNT: DMACNT Mask               */

#define USBD_EPDAT_EPDAT_Pos             (0)                                               /*!< USBD EPDAT: EPDAT Position            */
#define USBD_EPDAT_EPDAT_Msk             (0xfffffffful << USBD_EPDAT_EPDAT_Pos)            /*!< USBD EPDAT: EPDAT Mask                */

#define USBD_EPINTSTS_BUFFULLIF_Pos      (0)                                               /*!< USBD EPINTSTS: BUFFULLIF Position     */
#define USBD_EPINTSTS_BUFFULLIF_Msk      (0x1ul << USBD_EPINTSTS_BUFFULLIF_Pos)            /*!< USBD EPINTSTS: BUFFULLIF Mask         */

#define USBD_EPINTSTS_BUFEMPTYIF_Pos     (1)                                               /*!< USBD EPINTSTS: BUFEMPTYIF Position    */
#define USBD_EPINTSTS_BUFEMPTYIF_Msk     (0x1ul << USBD_EPINTSTS_BUFEMPTYIF_Pos)           /*!< USBD EPINTSTS: BUFEMPTYIF Mask        */

#define USBD_EPINTSTS_SHORTTXIF_Pos      (2)                                               /*!< USBD EPINTSTS: SHORTTXIF Position     */
#define USBD_EPINTSTS_SHORTTXIF_Msk      (0x1ul << USBD_EPINTSTS_SHORTTXIF_Pos)            /*!< USBD EPINTSTS: SHORTTXIF Mask         */

#define USBD_EPINTSTS_TXPKIF_Pos         (3)                                               /*!< USBD EPINTSTS: TXPKIF Position        */
#define USBD_EPINTSTS_TXPKIF_Msk         (0x1ul << USBD_EPINTSTS_TXPKIF_Pos)               /*!< USBD EPINTSTS: TXPKIF Mask            */

#define USBD_EPINTSTS_RXPKIF_Pos         (4)                                               /*!< USBD EPINTSTS: RXPKIF Position        */
#define USBD_EPINTSTS_RXPKIF_Msk         (0x1ul << USBD_EPINTSTS_RXPKIF_Pos)               /*!< USBD EPINTSTS: RXPKIF Mask            */

#define USBD_EPINTSTS_OUTTKIF_Pos        (5)                                               /*!< USBD EPINTSTS: OUTTKIF Position       */
#define USBD_EPINTSTS_OUTTKIF_Msk        (0x1ul << USBD_EPINTSTS_OUTTKIF_Pos)              /*!< USBD EPINTSTS: OUTTKIF Mask           */

#define USBD_EPINTSTS_INTKIF_Pos         (6)                                               /*!< USBD EPINTSTS: INTKIF Position        */
#define USBD_EPINTSTS_INTKIF_Msk         (0x1ul << USBD_EPINTSTS_INTKIF_Pos)               /*!< USBD EPINTSTS: INTKIF Mask            */

#define USBD_EPINTSTS_PINGIF_Pos         (7)                                               /*!< USBD EPINTSTS: PINGIF Position        */
#define USBD_EPINTSTS_PINGIF_Msk         (0x1ul << USBD_EPINTSTS_PINGIF_Pos)               /*!< USBD EPINTSTS: PINGIF Mask            */

#define USBD_EPINTSTS_NAKIF_Pos          (8)                                               /*!< USBD EPINTSTS: NAKIF Position         */
#define USBD_EPINTSTS_NAKIF_Msk          (0x1ul << USBD_EPINTSTS_NAKIF_Pos)                /*!< USBD EPINTSTS: NAKIF Mask             */

#define USBD_EPINTSTS_STALLIF_Pos        (9)                                               /*!< USBD EPINTSTS: STALLIF Position       */
#define USBD_EPINTSTS_STALLIF_Msk        (0x1ul << USBD_EPINTSTS_STALLIF_Pos)              /*!< USBD EPINTSTS: STALLIF Mask           */

#define USBD_EPINTSTS_NYETIF_Pos         (10)                                              /*!< USBD EPINTSTS: NYETIF Position        */
#define USBD_EPINTSTS_NYETIF_Msk         (0x1ul << USBD_EPINTSTS_NYETIF_Pos)               /*!< USBD EPINTSTS: NYETIF Mask            */

#define USBD_EPINTSTS_ERRIF_Pos          (11)                                              /*!< USBD EPINTSTS: ERRIF Position         */
#define USBD_EPINTSTS_ERRIF_Msk          (0x1ul << USBD_EPINTSTS_ERRIF_Pos)                /*!< USBD EPINTSTS: ERRIF Mask             */

#define USBD_EPINTSTS_SHORTRXIF_Pos      (12)                                              /*!< USBD EPINTSTS: SHORTRXIF Position     */
#define USBD_EPINTSTS_SHORTRXIF_Msk      (0x1ul << USBD_EPINTSTS_SHORTRXIF_Pos)            /*!< USBD EPINTSTS: SHORTRXIF Mask         */

#define USBD_EPINTEN_BUFFULLIEN_Pos      (0)                                               /*!< USBD EPINTEN: BUFFULLIEN Position     */
#define USBD_EPINTEN_BUFFULLIEN_Msk      (0x1ul << USBD_EPINTEN_BUFFULLIEN_Pos)            /*!< USBD EPINTEN: BUFFULLIEN Mask         */

#define USBD_EPINTEN_BUFEMPTYIEN_Pos     (1)                                               /*!< USBD EPINTEN: BUFEMPTYIEN Position    */
#define USBD_EPINTEN_BUFEMPTYIEN_Msk     (0x1ul << USBD_EPINTEN_BUFEMPTYIEN_Pos)           /*!< USBD EPINTEN: BUFEMPTYIEN Mask        */

#define USBD_EPINTEN_SHORTTXIEN_Pos      (2)                                               /*!< USBD EPINTEN: SHORTTXIEN Position     */
#define USBD_EPINTEN_SHORTTXIEN_Msk      (0x1ul << USBD_EPINTEN_SHORTTXIEN_Pos)            /*!< USBD EPINTEN: SHORTTXIEN Mask         */

#define USBD_EPINTEN_TXPKIEN_Pos         (3)                                               /*!< USBD EPINTEN: TXPKIEN Position        */
#define USBD_EPINTEN_TXPKIEN_Msk         (0x1ul << USBD_EPINTEN_TXPKIEN_Pos)               /*!< USBD EPINTEN: TXPKIEN Mask            */

#define USBD_EPINTEN_RXPKIEN_Pos         (4)                                               /*!< USBD EPINTEN: RXPKIEN Position        */
#define USBD_EPINTEN_RXPKIEN_Msk         (0x1ul << USBD_EPINTEN_RXPKIEN_Pos)               /*!< USBD EPINTEN: RXPKIEN Mask            */

#define USBD_EPINTEN_OUTTKIEN_Pos        (5)                                               /*!< USBD EPINTEN: OUTTKIEN Position       */
#define USBD_EPINTEN_OUTTKIEN_Msk        (0x1ul << USBD_EPINTEN_OUTTKIEN_Pos)              /*!< USBD EPINTEN: OUTTKIEN Mask           */

#define USBD_EPINTEN_INTKIEN_Pos         (6)                                               /*!< USBD EPINTEN: INTKIEN Position        */
#define USBD_EPINTEN_INTKIEN_Msk         (0x1ul << USBD_EPINTEN_INTKIEN_Pos)               /*!< USBD EPINTEN: INTKIEN Mask            */

#define USBD_EPINTEN_PINGIEN_Pos         (7)                                               /*!< USBD EPINTEN: PINGIEN Position        */
#define USBD_EPINTEN_PINGIEN_Msk         (0x1ul << USBD_EPINTEN_PINGIEN_Pos)               /*!< USBD EPINTEN: PINGIEN Mask            */

#define USBD_EPINTEN_NAKIEN_Pos          (8)                                               /*!< USBD EPINTEN: NAKIEN Position         */
#define USBD_EPINTEN_NAKIEN_Msk          (0x1ul << USBD_EPINTEN_NAKIEN_Pos)                /*!< USBD EPINTEN: NAKIEN Mask             */

#define USBD_EPINTEN_STALLIEN_Pos        (9)                                               /*!< USBD EPINTEN: STALLIEN Position       */
#define USBD_EPINTEN_STALLIEN_Msk        (0x1ul << USBD_EPINTEN_STALLIEN_Pos)              /*!< USBD EPINTEN: STALLIEN Mask           */

#define USBD_EPINTEN_NYETIEN_Pos         (10)                                              /*!< USBD EPINTEN: NYETIEN Position        */
#define USBD_EPINTEN_NYETIEN_Msk         (0x1ul << USBD_EPINTEN_NYETIEN_Pos)               /*!< USBD EPINTEN: NYETIEN Mask            */

#define USBD_EPINTEN_ERRIEN_Pos          (11)                                              /*!< USBD EPINTEN: ERRIEN Position         */
#define USBD_EPINTEN_ERRIEN_Msk          (0x1ul << USBD_EPINTEN_ERRIEN_Pos)                /*!< USBD EPINTEN: ERRIEN Mask             */

#define USBD_EPINTEN_SHORTRXIEN_Pos      (12)                                              /*!< USBD EPINTEN: SHORTRXIEN Position     */
#define USBD_EPINTEN_SHORTRXIEN_Msk      (0x1ul << USBD_EPINTEN_SHORTRXIEN_Pos)            /*!< USBD EPINTEN: SHORTRXIEN Mask         */

#define USBD_EPDATCNT_DATCNT_Pos         (0)                                               /*!< USBD EPDATCNT: DATCNT Position        */
#define USBD_EPDATCNT_DATCNT_Msk         (0xfffful << USBD_EPDATCNT_DATCNT_Pos)            /*!< USBD EPDATCNT: DATCNT Mask            */

#define USBD_EPDATCNT_DMALOOP_Pos        (16)                                              /*!< USBD EPDATCNT: DMALOOP Position       */
#define USBD_EPDATCNT_DMALOOP_Msk        (0x7ffful << USBD_EPDATCNT_DMALOOP_Pos)           /*!< USBD EPDATCNT: DMALOOP Mask           */

#define USBD_EPRSPCTL_FLUSH_Pos          (0)                                               /*!< USBD EPRSPCTL: FLUSH Position         */
#define USBD_EPRSPCTL_FLUSH_Msk          (0x1ul << USBD_EPRSPCTL_FLUSH_Pos)                /*!< USBD EPRSPCTL: FLUSH Mask             */

#define USBD_EPRSPCTL_MODE_Pos           (1)                                               /*!< USBD EPRSPCTL: MODE Position          */
#define USBD_EPRSPCTL_MODE_Msk           (0x3ul << USBD_EPRSPCTL_MODE_Pos)                 /*!< USBD EPRSPCTL: MODE Mask              */

#define USBD_EPRSPCTL_TOGGLE_Pos         (3)                                               /*!< USBD EPRSPCTL: TOGGLE Position        */
#define USBD_EPRSPCTL_TOGGLE_Msk         (0x1ul << USBD_EPRSPCTL_TOGGLE_Pos)               /*!< USBD EPRSPCTL: TOGGLE Mask            */

#define USBD_EPRSPCTL_HALT_Pos           (4)                                               /*!< USBD EPRSPCTL: HALT Position          */
#define USBD_EPRSPCTL_HALT_Msk           (0x1ul << USBD_EPRSPCTL_HALT_Pos)                 /*!< USBD EPRSPCTL: HALT Mask              */

#define USBD_EPRSPCTL_ZEROLEN_Pos        (5)                                               /*!< USBD EPRSPCTL: ZEROLEN Position       */
#define USBD_EPRSPCTL_ZEROLEN_Msk        (0x1ul << USBD_EPRSPCTL_ZEROLEN_Pos)              /*!< USBD EPRSPCTL: ZEROLEN Mask           */

#define USBD_EPRSPCTL_SHORTTXEN_Pos      (6)                                               /*!< USBD EPRSPCTL: SHORTTXEN Position     */
#define USBD_EPRSPCTL_SHORTTXEN_Msk      (0x1ul << USBD_EPRSPCTL_SHORTTXEN_Pos)            /*!< USBD EPRSPCTL: SHORTTXEN Mask         */

#define USBD_EPRSPCTL_DISBUF_Pos         (7)                                               /*!< USBD EPRSPCTL: DISBUF Position        */
#define USBD_EPRSPCTL_DISBUF_Msk         (0x1ul << USBD_EPRSPCTL_DISBUF_Pos)               /*!< USBD EPRSPCTL: DISBUF Mask            */

#define USBD_EPMPS_EPMPS_Pos             (0)                                               /*!< USBD EPMPS: EPMPS Position            */
#define USBD_EPMPS_EPMPS_Msk             (0x7fful << USBD_EPMPS_EPMPS_Pos)                 /*!< USBD EPMPS: EPMPS Mask                */

#define USBD_EPTXCNT_TXCNT_Pos           (0)                                               /*!< USBD EPTXCNT: TXCNT Position          */
#define USBD_EPTXCNT_TXCNT_Msk           (0x7fful << USBD_EPTXCNT_TXCNT_Pos)               /*!< USBD EPTXCNT: TXCNT Mask              */

#define USBD_EPCFG_EPEN_Pos              (0)                                               /*!< USBD EPCFG: EPEN Position             */
#define USBD_EPCFG_EPEN_Msk              (0x1ul << USBD_EPCFG_EPEN_Pos)                    /*!< USBD EPCFG: EPEN Mask                 */

#define USBD_EPCFG_EPTYPE_Pos            (1)                                               /*!< USBD EPCFG: EPTYPE Position           */
#define USBD_EPCFG_EPTYPE_Msk            (0x3ul << USBD_EPCFG_EPTYPE_Pos)                  /*!< USBD EPCFG: EPTYPE Mask               */

#define USBD_EPCFG_EPDIR_Pos             (3)                                               /*!< USBD EPCFG: EPDIR Position            */
#define USBD_EPCFG_EPDIR_Msk             (0x1ul << USBD_EPCFG_EPDIR_Pos)                   /*!< USBD EPCFG: EPDIR Mask                */

#define USBD_EPCFG_EPNUM_Pos             (4)                                               /*!< USBD EPCFG: EPNUM Position            */
#define USBD_EPCFG_EPNUM_Msk             (0xful << USBD_EPCFG_EPNUM_Pos)                   /*!< USBD EPCFG: EPNUM Mask                */

#define USBD_EPBUFSTART_SADDR_Pos        (0)                                               /*!< USBD EPBUFSTART: SADDR Position       */
#define USBD_EPBUFSTART_SADDR_Msk        (0xffful << USBD_EPBUFSTART_SADDR_Pos)            /*!< USBD EPBUFSTART: SADDR Mask           */

#define USBD_EPBUFEND_EADDR_Pos          (0)                                               /*!< USBD EPBUFEND: EADDR Position         */
#define USBD_EPBUFEND_EADDR_Msk          (0xffful << USBD_EPBUFEND_EADDR_Pos)              /*!< USBD EPBUFEND: EADDR Mask             */

#define USBD_DMAADDR_DMAADDR_Pos         (0)                                               /*!< USBD DMAADDR: DMAADDR Position         */
#define USBD_DMAADDR_DMAADDR_Msk         (0xfffffffful << USBD_DMAADDR_DMAADDR_Pos)        /*!< USBD DMAADDR: DMAADDR Mask             */

#define USBD_PHYCTL_DPPUEN_Pos           (8)                                               /*!< USBD PHYCTL: DPPUEN Position           */
#define USBD_PHYCTL_DPPUEN_Msk           (0x1ul << USBD_PHYCTL_DPPUEN_Pos)                 /*!< USBD PHYCTL: DPPUEN Mask               */

#define USBD_PHYCTL_PHYEN_Pos            (9)                                               /*!< USBD PHYCTL: PHYEN Position            */
#define USBD_PHYCTL_PHYEN_Msk            (0x1ul << USBD_PHYCTL_PHYEN_Pos)                  /*!< USBD PHYCTL: PHYEN Mask                */

#define USBD_PHYCTL_WKEN_Pos             (24)                                              /*!< USBD PHYCTL: WKEN Position             */
#define USBD_PHYCTL_WKEN_Msk             (0x1ul << USBD_PHYCTL_WKEN_Pos)                   /*!< USBD PHYCTL: WKEN Mask                 */

#define USBD_PHYCTL_VBUSDET_Pos          (31)                                              /*!< USBD PHYCTL: VBUSDET Position          */
#define USBD_PHYCTL_VBUSDET_Msk          (0x1ul << USBD_PHYCTL_VBUSDET_Pos)                /*!< USBD PHYCTL: VBUSDET Mask              */
/// @endcond
/** @addtogroup N9H30_USBD_EXPORTED_MACROS USBD Exported Macros
  @{
*/

#define USBD_ENABLE_USB()               ((uint32_t)(USBD->PHYCTL |= (USBD_PHYCTL_PHYEN_Msk|USBD_PHYCTL_DPPUEN_Msk))) /*!<Enable USB  \hideinitializer */
#define USBD_DISABLE_USB()              ((uint32_t)(USBD->PHYCTL &= ~USBD_PHYCTL_DPPUEN_Msk)) /*!<Disable USB  \hideinitializer */
#define USBD_ENABLE_PHY()               ((uint32_t)(USBD->PHYCTL |= USBD_PHYCTL_PHYEN_Msk)) /*!<Enable PHY  \hideinitializer */
#define USBD_DISABLE_PHY()              ((uint32_t)(USBD->PHYCTL &= ~USBD_PHYCTL_PHYEN_Msk)) /*!<Disable PHY  \hideinitializer */
#define USBD_SET_SE0()                  ((uint32_t)(USBD->PHYCTL &= ~USBD_PHYCTL_DPPUEN_Msk)) /*!<Enable SE0, Force USB PHY Transceiver to Drive SE0  \hideinitializer */
#define USBD_CLR_SE0()                  ((uint32_t)(USBD->PHYCTL |= USBD_PHYCTL_DPPUEN_Msk)) /*!<Disable SE0  \hideinitializer */
#define USBD_SET_ADDR(addr)             (USBD->FADDR = (addr)) /*!<Set USB address  \hideinitializer */
#define USBD_GET_ADDR()                 ((uint32_t)(USBD->FADDR)) /*!<Get USB address  \hideinitializer */
#define USBD_ENABLE_USB_INT(intr)       (USBD->GINTEN = (intr)) /*!<Enable USB Interrupt  \hideinitializer */
#define USBD_ENABLE_BUS_INT(intr)       (USBD->BUSINTEN = (intr)) /*!<Enable BUS Interrupt  \hideinitializer */
#define USBD_GET_BUS_INT_FLAG()         (USBD->BUSINTSTS)        /*!<Clear Bus interrupt flag  \hideinitializer */
#define USBD_CLR_BUS_INT_FLAG(flag)     (USBD->BUSINTSTS = flag) /*!<Clear Bus interrupt flag  \hideinitializer */
#define USBD_ENABLE_CEP_INT(intr)       (USBD->CEPINTEN = (intr)) /*!<Enable CEP Interrupt  \hideinitializer */
#define USBD_CLR_CEP_INT_FLAG(flag)     (USBD->CEPINTSTS = flag) /*!<Clear CEP interrupt flag  \hideinitializer */
#define USBD_SET_CEP_STATE(flag)        (USBD->CEPCTL = flag) /*!<Set CEP state  \hideinitializer */
#define USBD_START_CEP_IN(size)         (USBD->CEPTXCNT = size) /*!<Start CEP IN Transfer  \hideinitializer */
#define USBD_SET_MAX_PAYLOAD(ep, size)  (USBD->EP[ep].EPMPS = (size)) /*!<Set EPx Maximum Packet Size  \hideinitializer */
#define USBD_ENABLE_EP_INT(ep, intr)    (USBD->EP[ep].EPINTEN = (intr)) /*!<Enable EPx Interrupt  \hideinitializer */
#define USBD_GET_EP_INT_FLAG(ep)        (USBD->EP[ep].EPINTSTS) /*!<Get EPx interrupt flag  \hideinitializer */
#define USBD_CLR_EP_INT_FLAG(ep, flag)  (USBD->EP[ep].EPINTSTS = (flag)) /*!<Clear EPx interrupt flag  \hideinitializer */
#define USBD_SET_DMA_LEN(len)           (USBD->DMACNT = len) /*!<Set DMA transfer length  \hideinitializer */
#define USBD_SET_DMA_ADDR(addr)         (USBD->DMAADDR = addr) /*!<Set DMA transfer address  \hideinitializer */
#define USBD_SET_DMA_READ(epnum)        (USBD->DMACTL = (USBD->DMACTL & ~USBD_DMACTL_EPNUM_Msk) | USBD_DMACTL_DMARD_Msk | epnum) /*!<Set DMA transfer type to read \hideinitializer */
#define USBD_SET_DMA_WRITE(epnum)       (USBD->DMACTL = (USBD->DMACTL & ~(USBD_DMACTL_EPNUM_Msk | USBD_DMACTL_DMARD_Msk)) | epnum) /*!<Set DMA transfer type to write \hideinitializer */
#define USBD_ENABLE_DMA()               (USBD->DMACTL |= USBD_DMACTL_DMAEN_Msk) /*!<Enable DMA transfer  \hideinitializer */
#define USBD_IS_ATTACHED()              ((uint32_t)(USBD->PHYCTL & USBD_PHYCTL_VBUSDET_Msk)) /*!<Check cable connect state  \hideinitializer */

/*@}*/ /* end of group N9H30_USBD_EXPORTED_MACROS */

/** @addtogroup N9H30_USBD_EXPORTED_FUNCTIONS USBD Exported Functions
  @{
*/
/**
  * @brief  USBD_memcpy, Copy bytes hardware limitation
  * @param[in]  u8Dst   Destination pointer.
  * @param[in]  u8Src   Source pointer.
  * @param[in]  i32Size Copy size.
  * @retval None.
  */
static __inline void USBD_MemCopy(uint8_t *u8Dst, uint8_t *u8Src, int32_t i32Size)
{
    while (i32Size--) *u8Dst++ = *u8Src++;
}

/**
  * @brief  USBD_ResetDMA
  * @param  None
  * @retval None.
  */
static __inline void USBD_ResetDMA(void)
{
    USBD->DMACNT = 0;
    USBD->DMACTL = 0x80;
    USBD->DMACTL = 0x00;
}
/**
  * @brief  USBD_SetEpBufAddr, Set Endpoint buffer address
  * @param[in]  u32Ep      Endpoint Number
  * @param[in]  u32Base    Buffer Start Address
  * @param[in]  u32Len     Buffer length
  * @retval None.
  */
static __inline void USBD_SetEpBufAddr(uint32_t u32Ep, uint32_t u32Base, uint32_t u32Len)
{
    if (u32Ep == CEP)
    {
        USBD->CEPBUFSTART = u32Base;
        USBD->CEPBUFEND   = u32Base + u32Len - 1;
    }
    else
    {
        USBD->EP[u32Ep].EPBUFSTART = u32Base;
        USBD->EP[u32Ep].EPBUFEND = u32Base + u32Len - 1;
    }
}

/**
  * @brief  USBD_ConfigEp, Config Endpoint
  * @param[in]  u32Ep      USB endpoint
  * @param[in]  u32EpNum   Endpoint number
  * @param[in]  u32EpType  Endpoint type
  * @param[in]  u32EpDir   Endpoint direction
  * @retval None.
  */
static __inline void USBD_ConfigEp(uint32_t u32Ep, uint32_t u32EpNum, uint32_t u32EpType, uint32_t u32EpDir)
{
    if (u32EpType == USB_EP_CFG_TYPE_BULK)
        USBD->EP[u32Ep].EPRSPCTL = (USB_EP_RSPCTL_FLUSH | USB_EP_RSPCTL_MODE_AUTO);
    else if (u32EpType == USB_EP_CFG_TYPE_INT)
        USBD->EP[u32Ep].EPRSPCTL = (USB_EP_RSPCTL_FLUSH | USB_EP_RSPCTL_MODE_MANUAL);
    else if (u32EpType == USB_EP_CFG_TYPE_ISO)
        USBD->EP[u32Ep].EPRSPCTL = (USB_EP_RSPCTL_FLUSH | USB_EP_RSPCTL_MODE_FLY);

    USBD->EP[u32Ep].EPCFG = (u32EpType | u32EpDir | USB_EP_CFG_VALID | (u32EpNum << 4));
}

/**
  * @brief       Set USB endpoint stall state
  * @param[in]   u32Ep  The USB endpoint ID.
  * @return      None
  * @details     Set USB endpoint stall state for the specified endpoint ID. Endpoint will respond STALL token automatically.
  */
static __inline void USBD_SetEpStall(uint32_t u32Ep)
{
    if (u32Ep == CEP)
        USBD_SET_CEP_STATE(USB_CEPCTL_STALL);
    else
    {
        USBD->EP[u32Ep].EPRSPCTL = USBD->EP[u32Ep].EPRSPCTL & 0xf7 | USB_EP_RSPCTL_HALT;
    }
}

/**
 * @brief       Set USB endpoint stall state
 *
 * @param[in]   u32EpNum         USB endpoint
 * @return      None
 *
 * @details     Set USB endpoint stall state, endpoint will return STALL token.
 */
static __inline void USBD_SetStall(uint32_t u32EpNum)
{
    int i;

    if (u32EpNum == 0)
        USBD_SET_CEP_STATE(USB_CEPCTL_STALL);
    else
    {
        for (i = 0; i < USBD_MAX_EP; i++)
        {
            if (((USBD->EP[i].EPCFG & 0xf0) >> 4) == u32EpNum)
            {
                USBD->EP[i].EPRSPCTL = USBD->EP[i].EPRSPCTL & 0xf7 | USB_EP_RSPCTL_HALT;
            }
        }
    }
}

/**
  * @brief       Clear USB endpoint stall state
  * @param[in]   u32Ep  The USB endpoint ID.
  * @return      None
  * @details     Clear USB endpoint stall state for the specified endpoint ID. Endpoint will respond ACK/NAK token.
  */
static __inline void  USBD_ClearEpStall(uint32_t u32Ep)
{
    USBD->EP[u32Ep].EPRSPCTL = USB_EP_RSPCTL_TOGGLE;
}

/**
 * @brief       Clear USB endpoint stall state
 *
 * @param[in]   u32EpNum         USB endpoint
 * @return      None
 *
 * @details     Clear USB endpoint stall state, endpoint will return ACK/NAK token.
 */
static __inline void USBD_ClearStall(uint32_t u32EpNum)
{
    int i;

    for (i = 0; i < USBD_MAX_EP; i++)
    {
        if (((USBD->EP[i].EPCFG & 0xf0) >> 4) == u32EpNum)
        {
            USBD->EP[i].EPRSPCTL = USB_EP_RSPCTL_TOGGLE;
        }
    }
}

/**
  * @brief       Get USB endpoint stall state
  * @param[in]   u32Ep  The USB endpoint ID.
  * @retval      0      USB endpoint is not stalled.
  * @retval      Others USB endpoint is stalled.
  * @details     Get USB endpoint stall state of the specified endpoint ID.
  */
static __inline uint32_t USBD_GetEpStall(uint32_t u32Ep)
{
    return (USBD->EP[u32Ep].EPRSPCTL & USB_EP_RSPCTL_HALT);
}

/**
 * @brief       Get USB endpoint stall state
 *
 * @param[in]   u32EpNum         USB endpoint
 * @retval      0: USB endpoint is not stalled.
 * @retval      non-0: USB endpoint is stalled.
 *
 * @details     Get USB endpoint stall state.
 */
static __inline uint32_t USBD_GetStall(uint32_t u32EpNum)
{
    int i;

    for (i = 0; i < USBD_MAX_EP; i++)
    {
        if (((USBD->EP[i].EPCFG & 0xf0) >> 4) == u32EpNum)
        {
            return (USBD->EP[i].EPRSPCTL & USB_EP_RSPCTL_HALT);
        }
    }
    return 0;
}


/*-------------------------------------------------------------------------------------------*/
typedef void (*VENDOR_REQ)(void); /*!<USB Vendor request callback function */
typedef void (*CLASS_REQ)(void); /*!<USB Class request callback function */
typedef void (*SET_INTERFACE_REQ)(uint32_t u32AltInterface); /*!<USB Standard request "Set Interface" callback function */

void USBD_Open(S_USBD_INFO_T *param, CLASS_REQ pfnClassReq, SET_INTERFACE_REQ pfnSetInterface);
void USBD_Start(void);
void USBD_ProcessSetupPacket(void);
void USBD_StandardRequest(void);
void USBD_UpdateDeviceState(void);
void USBD_PrepareCtrlIn(uint8_t *pu8Buf, uint32_t u32Size);
void USBD_CtrlIn(void);
void USBD_CtrlOut(uint8_t *pu8Buf, uint32_t u32Size);
void USBD_SwReset(void);
void USBD_SetVendorRequest(VENDOR_REQ pfnVendorReq);



/*@}*/ /* end of group N9H30_USBD_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_USBD_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__NU_USBD_H__

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
