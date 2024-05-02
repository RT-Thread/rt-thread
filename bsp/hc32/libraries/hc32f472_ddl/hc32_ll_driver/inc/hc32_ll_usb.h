/**
 *******************************************************************************
 * @file  hc32_ll_usb.h
 * @brief A detailed description is available at hardware registers.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Add API USB_DeInit()
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_USB_H__
#define __HC32_LL_USB_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"

#include "usb_app_conf.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_USB
 * @{
 */

#if (LL_USB_ENABLE == DDL_ON)

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define USB_MAX_TX_FIFOS                       (12U)
#define USB_MAX_CH_NUM                         (USB_MAX_TX_FIFOS)
#define USB_MAX_EP_NUM                         (6U)

/* USB Core ID define */
#define USBFS_CORE_ID                          (0U)
#define USBHS_CORE_ID                          (1U)

/* USB PHY type define for USBHS core */
#define USBHS_PHY_EMBED                        (0U)
#define USBHS_PHY_EXT                          (1U)

#define USB_MAX_EP0_SIZE                       (64U)
/* working mode of the USB core */
#define DEVICE_MODE                            (0U)
#define HOST_MODE                              (1U)

/* Macro definations for device mode*/
#define DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ     (0U << USBFS_DSTS_ENUMSPD_POS)
#define DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ     (1U << USBFS_DSTS_ENUMSPD_POS)
#define DSTS_ENUMSPD_LS_PHY_6MHZ               (2U << USBFS_DSTS_ENUMSPD_POS)
#define DSTS_ENUMSPD_FS_PHY_48MHZ              (3U << USBFS_DSTS_ENUMSPD_POS)

/* EP type */
#define EP_TYPE_CTRL                           (0U)
#define EP_TYPE_ISOC                           (1U)
#define EP_TYPE_BULK                           (2U)
#define EP_TYPE_INTR                           (3U)
#define EP_TYPE_MSK                            (3U)

/* USB port speed */
#define PRTSPD_FULL_SPEED                      (1U)
#define PRTSPD_LOW_SPEED                       (2U)

/* PHY clock */
#define HCFG_30_60_MHZ                         (0U)
#define HCFG_48_MHZ                            (1U)
#define HCFG_6_MHZ                             (2U)

#define USB_EP_TX_DIS                          (0x0000U)
#define USB_EP_TX_STALL                        (0x0010U)
#define USB_EP_TX_NAK                          (0x0020U)
#define USB_EP_TX_VALID                        (0x0030U)

#define USB_EP_RX_DIS                          (0x0000U)
#define USB_EP_RX_STALL                        (0x1000U)
#define USB_EP_RX_NAK                          (0x2000U)
#define USB_EP_RX_VALID                        (0x3000U)

#define USB_OK                              (0U)
#define USB_ERROR                           (1U)

#define USB_FRAME_INTERVAL_80                  (0UL << USBFS_DCFG_PFIVL_POS)
#define USB_FRAME_INTERVAL_85                  (1UL << USBFS_DCFG_PFIVL_POS)
#define USB_FRAME_INTERVAL_90                  (2UL << USBFS_DCFG_PFIVL_POS)
#define USB_FRAME_INTERVAL_95                  (3UL << USBFS_DCFG_PFIVL_POS)

#define SWAPBYTE(addr)          (((uint16_t)(*((uint8_t *)(addr)))) + \
                                (uint16_t)(((uint16_t)(*(((uint8_t *)(addr)) + 1U))) << 8U))
#define LOBYTE(x)               ((uint8_t)((uint16_t)(x) & 0x00FFU))
#define HIBYTE(x)               ((uint8_t)(((uint16_t)(x) & 0xFF00U) >>8U))

#ifdef USB_INTERNAL_DMA_ENABLED
#define __USB_ALIGN_END
#if defined   (__GNUC__)      /* GNU Compiler */
#define __USB_ALIGN_BEGIN       __attribute__ ((aligned (4)))
#elif defined   (__CC_ARM)    /* ARM Compiler */
#define __USB_ALIGN_BEGIN       __align(4)
#elif defined (__ICCARM__)    /* IAR Compiler */
#define __USB_ALIGN_BEGIN
#elif defined  (__TASKING__)  /* TASKING Compiler */
#define __USB_ALIGN_BEGIN       __align(4)
#endif
#else
#define __USB_ALIGN_BEGIN
#define __USB_ALIGN_END
#endif

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

typedef struct {
    __IO uint32_t GVBUSCFG;                   /* VBUS Configuration Register                      000h */
    uint32_t Reserved04;                      /* Reserved                                         004h */
    __IO uint32_t GAHBCFG;                    /* AHB Configuration Register                       008h */
    __IO uint32_t GUSBCFG;                    /* USB Configuration Register                       00Ch */
    __IO uint32_t GRSTCTL;                    /* Reset Register                                   010h */
    __IO uint32_t GINTSTS;                    /* Interrupt Register                               014h */
    __IO uint32_t GINTMSK;                    /* Interrupt Mask Register                          018h */
    __IO uint32_t GRXSTSR;                    /* Receive Sts Q Read Register                      01Ch */
    __IO uint32_t GRXSTSP;                    /* Receive Sts Q Read & POP Register                020h */
    __IO uint32_t GRXFSIZ;                    /* Receive FIFO Size Register                       024h */
    __IO uint32_t HNPTXFSIZ;                  /* HNPTXFSIZ: Host Non-Periodic Transmit FIFO Size Register 028h
                                                 DIEPTXF0: Device IN EP0 Transmit FIFO size register      028h */
    __IO uint32_t HNPTXSTS;                   /* Host Non Periodic Transmit FIFO/Queue Status Register    02Ch */
    uint32_t Reserved30[3];                   /* Reserved                                    030h-038h */
    __IO uint32_t CID;                        /* User ID Register                                 03Ch */
    uint32_t  Reserved40[5];                  /* Reserved                                    040h-050h */
    __IO uint32_t GLPMCFG;                    /* Low Power Mode Configuration Register            054h */
    uint32_t  Reserved58[42];                 /* Reserved                                    058h-0FCh */
    __IO uint32_t HPTXFSIZ;                   /* Host Periodic Transmit FIFO Size Register        100h */
    __IO uint32_t DIEPTXF[USB_MAX_TX_FIFOS];  /* Device Periodic Transmit FIFO Size Register           */
} USB_CORE_GREGS;

typedef struct {
    __IO uint32_t DCFG;         /* Device Configuration Register                     800h */
    __IO uint32_t DCTL;         /* Device Control Register                           804h */
    __IO uint32_t DSTS;         /* Device Status Register (RO)                       808h */
    uint32_t Reserved0C;        /* Reserved                                          80Ch */
    __IO uint32_t DIEPMSK;      /* Device IN EP Common Interrupt Mask Register       810h */
    __IO uint32_t DOEPMSK;      /* Device OUT EP Common Interrupt Mask Register      814h */
    __IO uint32_t DAINT;        /* Device All EP Interrupt Register                  818h */
    __IO uint32_t DAINTMSK;     /* Device All EP Interrupt Mask Register             81Ch */
    uint32_t Reserved20[4];     /* Reserved                                     820h-82Ch */
    __IO uint32_t DTHRCTL;      /* Device Threshold Control Register                 830h */
    __IO uint32_t DIEPEMPMSK;   /* Device IN EP FIFO Empty Interrupt Mask Register   834h */
    __IO uint32_t DEACHINT;     /* Device Each EP Interrupt Register                 838h */
    __IO uint32_t DEACHINTMSK;  /* Device Each EP Interrupt Mask Register            83Ch */
    uint32_t Reserved40;        /* Reserved                                          840h */
    __IO uint32_t DIEPEACHMSK1; /* Device IN EP1 Interrupt Mask Register             844h */
    uint32_t Reserved48[15];    /* Reserved                                      848-880h */
    __IO uint32_t DOEPEACHMSK1; /* Device OUT EP1 Interrupt Mask Register            884h */
} USB_CORE_DREGS;

typedef struct {
    __IO uint32_t DIEPCTL;  /* dev IN Endpoint Control Reg 900h + (ep_num * 20h) + 00h     */
    uint32_t Reserved04;        /* Reserved                    900h + (ep_num * 20h) + 04h */
    __IO uint32_t DIEPINT;  /* dev IN Endpoint Itr Reg     900h + (ep_num * 20h) + 08h     */
    uint32_t Reserved0C;        /* Reserved                    900h + (ep_num * 20h) + 0Ch */
    __IO uint32_t DIEPTSIZ; /* IN Endpoint Txfer Size      900h + (ep_num * 20h) + 10h     */
    __IO uint32_t DIEPDMA;  /* IN Endpoint DMA Address Reg 900h + (ep_num * 20h) + 14h     */
    __IO uint32_t DTXFSTS;  /* IN Endpoint Tx FIFO Status  900h + (ep_num * 20h) + 18h     */
    uint32_t Reserved18;        /* Reserved                    900h+(ep_num*20h)+1Ch-900h+ (ep_num * 20h) + 1Ch*/
} USB_CORE_INEPREGS;

typedef struct {
    __IO uint32_t DOEPCTL;   /* dev OUT Endpoint Control Reg  B00h + (ep_num * 20h) + 00h */
    uint32_t Reserved04;     /* Reserved                      B00h + (ep_num * 20h) + 04h */
    __IO uint32_t DOEPINT;   /* dev OUT Endpoint Itr Reg      B00h + (ep_num * 20h) + 08h */
    uint32_t Reserved0C;     /* Reserved                      B00h + (ep_num * 20h) + 0Ch */
    __IO uint32_t DOEPTSIZ;  /* dev OUT Endpoint Txfer Size   B00h + (ep_num * 20h) + 10h */
    __IO uint32_t DOEPDMA;   /* dev OUT Endpoint DMA Address  B00h + (ep_num * 20h) + 14h */
    uint32_t Reserved18[2];  /* Reserved                B00h + (ep_num * 20h) + 18h - B00h + (ep_num * 20h) + 1Ch */
} USB_CORE_OUTEPREGS;

typedef struct {
    __IO uint32_t HCFG;      /* Host Configuration Register    400h*/
    __IO uint32_t HFIR;      /* Host Frame Interval Register   404h*/
    __IO uint32_t HFNUM;     /* Host Frame Nbr/Frame Remaining 408h*/
    uint32_t Reserved40C;    /* Reserved                       40Ch*/
    __IO uint32_t HPTXSTS;   /* Host Periodic Tx FIFO/ Queue Status 410h*/
    __IO uint32_t HAINT;     /* Host All Channels Interrupt Register 414h*/
    __IO uint32_t HAINTMSK;  /* Host All Channels Interrupt Mask 418h*/
} USB_CORE_HREGS;

typedef struct {
    __IO uint32_t HCCHAR;
    __IO uint32_t HCSPLT;
    __IO uint32_t HCINT;
    __IO uint32_t HCINTMSK;
    __IO uint32_t HCTSIZ;
    __IO uint32_t HCDMA;
    uint32_t Reserved[2];
} USB_CORE_HC_REGS;

typedef struct { /* 000h */
    USB_CORE_GREGS     *GREGS;
    USB_CORE_DREGS     *DREGS;
    USB_CORE_HREGS     *HREGS;
    USB_CORE_INEPREGS  *INEP_REGS[USB_MAX_TX_FIFOS];
    USB_CORE_OUTEPREGS *OUTEP_REGS[USB_MAX_TX_FIFOS];
    USB_CORE_HC_REGS   *HC_REGS[USB_MAX_TX_FIFOS];
    __IO uint32_t  *HPRT;
    __IO uint32_t  *DFIFO[USB_MAX_TX_FIFOS];
    __IO uint32_t  *GCCTL;
} LL_USB_TypeDef;

typedef struct {
    uint8_t       host_chnum;
    uint8_t       dev_epnum;
    uint8_t       dmaen;
    uint8_t       low_power;
    uint8_t       phy_type;
    uint8_t       core_type;
} USB_CORE_BASIC_CFGS;

typedef struct {
    uint8_t       dev_addr;
    uint8_t       ep_idx;
    uint8_t       is_epin;
    uint8_t       ch_speed;
    uint8_t       do_ping;
    uint8_t       ep_type;
    uint16_t      max_packet;
    uint8_t       pid_type;
    uint8_t       in_toggle;
    uint8_t       out_toggle;
    /* transaction level variables*/
    uint32_t      dma_addr;
    uint32_t      xfer_len;
    uint32_t      xfer_count;
    uint8_t       *xfer_buff;
} USB_HOST_CH;

typedef struct {
    uint8_t        epidx;
    uint8_t        ep_dir;
    uint8_t        trans_type;
    uint8_t        ep_stall;
    uint8_t        data_pid_start;
    uint8_t        datax_pid;
    uint16_t       tx_fifo_num;
    uint32_t       maxpacket;
    /* Transfer level variables */
    uint32_t       rem_data_len;
    uint32_t       total_data_len;
    uint32_t       ctl_data_len;
    /* transaction level variables*/
    uint32_t       dma_addr;
    uint32_t       xfer_len;
    uint32_t       xfer_count;
    uint8_t        *xfer_buff;
} USB_DEV_EP;

typedef struct {
    uint8_t        u8CoreID;     /* USBFS_CORE_ID or USBHS_CORE_ID */
} stc_usb_port_identify;

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/

/**
 * @addtogroup USB_Global_Functions
 * @{
 */

/**
 * @brief  get the current mode of the usb core from the corresponding register
 * @param  [in] USBx        usb instance
 * @retval current mode     1: host mode   0: device mode
 */
__STATIC_INLINE uint8_t usb_getcurmod(LL_USB_TypeDef *USBx)
{
    if (0UL != READ_REG32_BIT(USBx->GREGS->GINTSTS, USBFS_GINTSTS_CMOD)) {
        return 1U;
    } else {
        return 0U;
    }
}

/**
 * @brief  Initializes the normal interrupts
 * @param  [in] USBx        usb instance
 * @retval None
 */
__STATIC_INLINE void usb_normalinten(LL_USB_TypeDef *USBx)
{
    WRITE_REG32(USBx->GREGS->GINTSTS, 0xBFFFFFFFUL);
    WRITE_REG32(USBx->GREGS->GINTMSK, USBFS_GINTMSK_WKUIM | USBFS_GINTMSK_USBSUSPM);
}

/**
 * @brief  clear all the pending device interrupt bits and mask the IN and OUT
 *         endpoint interrupts.
 * @param  [in] USBx        usb instance
 * @retval None
 */
__STATIC_INLINE void usb_clrandmskepint(LL_USB_TypeDef *USBx)
{
    WRITE_REG32(USBx->DREGS->DIEPMSK, 0UL);
    WRITE_REG32(USBx->DREGS->DOEPMSK, 0UL);
    WRITE_REG32(USBx->DREGS->DAINT, 0xFFFFFFFFUL);
    WRITE_REG32(USBx->DREGS->DAINTMSK, 0UL);
}

/**
 * @brief  generate a device connect signal to the USB host
 * @param  [in] USBx        usb instance
 * @retval None
 */
__STATIC_INLINE void usb_coreconn(LL_USB_TypeDef *USBx)
{
    CLR_REG32_BIT(USBx->DREGS->DCTL, USBFS_DCTL_SDIS);
}

/**
 * @brief  test of mode processing
 * @param  [in] USBx        usb instance
 * @param  [in] reg         Register write
 * @retval None
 */
__STATIC_INLINE void usb_runtestmode(LL_USB_TypeDef *USBx, uint32_t reg)
{
    WRITE_REG32(USBx->DREGS->DCTL, reg);
}

/**
 * @brief  Enables the controller's Global interrupts in the AHB Configuration
 *         registers.
 * @param  [in] USBx        usb instance
 * @retval None
 */
__STATIC_INLINE void usb_ginten(LL_USB_TypeDef *USBx)
{
    SET_REG32_BIT(USBx->GREGS->GAHBCFG, USBFS_GAHBCFG_GINTMSK);
}

/**
 * @brief  Disable the controller's Global interrupt in the AHB Configuration
 *         register.
 * @param  [in] USBx        usb instance
 * @retval None
 */
__STATIC_INLINE void usb_gintdis(LL_USB_TypeDef *USBx)
{
    CLR_REG32_BIT(USBx->GREGS->GAHBCFG, USBFS_GAHBCFG_GINTMSK);
}

/**
 * @brief  Get the Core Interrupt bits from the interrupt register not including
 *         the bits that are masked.
 * @param  [in] USBx        usb instance
 * @retval status[32bits]
 */
__STATIC_INLINE uint32_t usb_getcoreintr(LL_USB_TypeDef *USBx)
{
    uint32_t v;
    v  = READ_REG32(USBx->GREGS->GINTSTS);
    v &= READ_REG32(USBx->GREGS->GINTMSK);
    return v;
}

/**
 * @brief  Get the out endpoint interrupt bits from the all endpoint interrupt
 *         register not including the bits masked.
 * @param  [in] USBx        usb instance
 * @retval The status that shows which OUT EP have interrupted.
 */
__STATIC_INLINE uint32_t usb_getalloepintr(LL_USB_TypeDef *USBx)
{
    uint32_t v;
    v  = READ_REG32(USBx->DREGS->DAINT);
    v &= READ_REG32(USBx->DREGS->DAINTMSK);
    return ((v & 0xFFFF0000UL) >> 16U);
}

/**
 * @brief  Get the Device OUT EP Interrupt register(DOEPINT) not including the
 *         interrupt bits that are masked.
 * @param  [in] USBx        usb instance
 * @param  [in] epnum       end point index
 * @retval all the interrupt bits on DOEPINTn while n = epnum
 */
__STATIC_INLINE uint32_t usb_getoepintbit(LL_USB_TypeDef *USBx, uint8_t epnum)
{
    uint32_t v;
    v  = READ_REG32(USBx->OUTEP_REGS[epnum]->DOEPINT);
    v &= READ_REG32(USBx->DREGS->DOEPMSK);
    return v;
}

/**
 * @brief  Get the IN endpoint interrupt bits from the all endpoint interrupt
 *         register not including the bits masked.
 * @param  [in] USBx        usb instance
 * @retval The status that shows which IN EP have interrupted.
 */
__STATIC_INLINE uint32_t usb_getalliepintr(LL_USB_TypeDef *USBx)
{
    uint32_t v;
    v  = READ_REG32(USBx->DREGS->DAINT);
    v &= READ_REG32(USBx->DREGS->DAINTMSK);
    return (v & 0xFFFFUL);
}

/**
 * @brief  Set the device a new address.
 * @param  [in] USBx        usb instance
 * @param  [in] address     device address which will be set to the corresponding register.
 * @retval None
 */
__STATIC_INLINE void usb_devaddrset(LL_USB_TypeDef *USBx, uint8_t address)
{
    MODIFY_REG32(USBx->DREGS->DCFG, USBFS_DCFG_DAD, (uint32_t)address << USBFS_DCFG_DAD_POS);
}

/**
 * @brief  Select the USB PHY.
 * @param  [in] USBx        usb instance
 * @param  [in] PhyType      USB phy, 1 select external ULPI PHY, 0 select internal FS PHY
 * @retval None
 */
__STATIC_INLINE void usb_PhySelect(LL_USB_TypeDef *USBx, uint8_t PhyType)
{
    if (USBHS_PHY_EXT == PhyType) {
        CLR_REG32_BIT(USBx->GREGS->GUSBCFG, USBFS_GUSBCFG_PHYSEL);
        //SET_REG32_BIT(USBx->GREGS->GUSBCFG, 1UL<<4);
    } else {
        SET_REG32_BIT(USBx->GREGS->GUSBCFG, USBFS_GUSBCFG_PHYSEL);
    }
}

/**
 * @brief  Select the USB device PHY.
 * @param  [in] USBx        usb instance
 * @param  [in] PhyType      USB phy, 1 select external ULPI PHY, 0 select internal FS PHY
 * @retval None
 */
__STATIC_INLINE void usb_DevPhySelect(LL_USB_TypeDef *USBx, uint8_t PhyType)
{
    if (1U == PhyType) {
        CLR_REG32_BIT(USBx->DREGS->DCFG, USBFS_DCFG_DSPD);
    } else {
        SET_REG32_BIT(USBx->DREGS->DCFG, USBFS_DCFG_DSPD);
    }

}

/**
 * @brief  USB DMA function command.
 * @param  [in] USBx        usb instance
 * @param  [in] DmaCmd       USB DMA command status, 0 disable, 1 enable
 * @retval None
 */
__STATIC_INLINE void usb_DmaCmd(LL_USB_TypeDef *USBx, uint8_t DmaCmd)
{
    MODIFY_REG32(USBx->GREGS->GAHBCFG, USBFS_GAHBCFG_DMAEN, (uint32_t)DmaCmd << USBFS_GAHBCFG_DMAEN_POS);
}

/**
 * @brief  USB burst length config.
 * @param  [in] USBx        usb instance
 * @param  [in] len         Burst length
 * @retval None
 */
__STATIC_INLINE void usb_BurstLenConfig(LL_USB_TypeDef *USBx, uint8_t len)
{
    MODIFY_REG32(USBx->GREGS->GAHBCFG, USBFS_GAHBCFG_HBSTLEN, (uint32_t)len << USBFS_GAHBCFG_HBSTLEN_POS);
}

/**
 * @brief  USB frame interval config
 * @param  [in] USBx        usb instance
 * @param  [in] interval    Frame interval
 * @retval None
 */
__STATIC_INLINE void usb_FrameIntervalConfig(LL_USB_TypeDef *USBx, uint8_t interval)
{
    MODIFY_REG32(USBx->DREGS->DCFG, USBFS_DCFG_PFIVL, interval);
}

#ifdef USE_HOST_MODE
/**
 * @brief  Read the register HPRT and reset the following bits.
 * @param  [in] USBx        usb instance
 * @retval value of HPRT
 */
//#define USBFS_HPRT_PRTOVRCURRCHNG                            (0x00000020UL)
__STATIC_INLINE uint32_t usb_rdhprt(LL_USB_TypeDef *USBx)
{
    return (READ_REG32(*USBx->HPRT) & ~(USBFS_HPRT_PENA | USBFS_HPRT_PCDET | USBFS_HPRT_PENCHNG));
}

/**
 * @brief  Issues a ping token
 * @param  [in] USBx        usb instance
 * @param  [in] hc_num      the host channel index
 * @retval None
 */
//#define USBFS_HCTSIZ_DOPNG (0x80000000UL)
__STATIC_INLINE void usb_pingtokenissue(LL_USB_TypeDef *USBx, uint8_t hc_num)
{
    WRITE_REG32(USBx->HC_REGS[hc_num]->HCTSIZ, 1UL << USBFS_HCTSIZ_PKTCNT_POS);
    MODIFY_REG32(USBx->HC_REGS[hc_num]->HCCHAR, USBFS_HCCHAR_CHENA | USBFS_HCCHAR_CHDIS, USBFS_HCCHAR_CHENA);
}

/**
 * @brief  This function returns the frame number for sof packet
 * @param  [in] USBx        usb instance
 * @retval Frame number
 */
__STATIC_INLINE uint32_t usb_ifevenframe(LL_USB_TypeDef *USBx)
{
    return ((READ_REG32(USBx->HREGS->HFNUM) + 1UL) & 0x1UL);
}

/**
 * @brief  Initializes the FSLSPClkSel field of the HCFG register on the PHY type
 * @param  [in] USBx        usb instance
 * @param  [in] freq        clock frequency
 * @retval None
 */
__STATIC_INLINE void usb_fslspclkselset(LL_USB_TypeDef *USBx, uint8_t freq)
{
    MODIFY_REG32(USBx->HREGS->HCFG, USBFS_HCFG_FSLSPCS, (uint32_t)freq << USBFS_HCFG_FSLSPCS_POS);
}

/**
 * @brief  suspend the port
 * @param  [in] USBx        usb instance
 * @retval None
 */
__STATIC_INLINE void usb_prtsusp(LL_USB_TypeDef *USBx)
{
    uint32_t u32hprt;
    u32hprt = usb_rdhprt(USBx);
    u32hprt |= USBFS_HPRT_PSUSP;
    u32hprt &= ~USBFS_HPRT_PRES;
    WRITE_REG32(*USBx->HPRT, u32hprt);
}

/**
 * @brief  control the enumeration speed of the core, this function make sure that
 *         the maximum speed supperted by the connected device.
 * @param  [in] USBx        usb instance
 * @retval None
 */
__STATIC_INLINE void usb_enumspeed(LL_USB_TypeDef *USBx)
{
    CLR_REG32_BIT(USBx->HREGS->HCFG, USBFS_HCFG_FSLSS);
}

/**
 * @brief  set the TXFIFO and depth for non-periodic and periodic and RXFIFO size
 * @param  [in] USBx        usb instance
 * @retval None
 */
__STATIC_INLINE void usb_sethostfifo(LL_USB_TypeDef *USBx, uint8_t u8CoreID)
{
    if (USBFS_CORE_ID == u8CoreID) {
#ifdef USB_FS_MODE
        /* USBFS Core*/
        WRITE_REG32(USBx->GREGS->GRXFSIZ, RX_FIFO_FS_SIZE);   /* set the RxFIFO Depth */
        /* non-periodic transmit RAM start address, set the non-periodic TxFIFO depth */
        WRITE_REG32(USBx->GREGS->HNPTXFSIZ,
                    (RX_FIFO_FS_SIZE << USBFS_HNPTXFSIZ_NPTXFSA_POS)
                    | (TXH_NP_FS_FIFOSIZ << USBFS_HNPTXFSIZ_NPTXFD_POS));
        /* set the host periodic TxFIFO start address, set the host periodic TxFIFO depth */
        WRITE_REG32(USBx->GREGS->HPTXFSIZ,
                    ((RX_FIFO_FS_SIZE + TXH_NP_FS_FIFOSIZ) << USBFS_HPTXFSIZ_PTXSA_POS)
                    | (TXH_P_FS_FIFOSIZ << USBFS_HPTXFSIZ_PTXFD_POS));
#endif
    } else {
#ifdef USB_HS_MODE
        /* USBHS Core */
        WRITE_REG32(USBx->GREGS->GRXFSIZ, RX_FIFO_HS_SIZE);
        WRITE_REG32(USBx->GREGS->HNPTXFSIZ,
                    (RX_FIFO_HS_SIZE << USBFS_HNPTXFSIZ_NPTXFSA_POS)
                    | (TXH_NP_HS_FIFOSIZ << USBFS_HNPTXFSIZ_NPTXFD_POS));
        WRITE_REG32(USBx->GREGS->HPTXFSIZ,
                    ((RX_FIFO_HS_SIZE + TXH_NP_HS_FIFOSIZ) << USBFS_HPTXFSIZ_PTXSA_POS)
                    | (TXH_P_HS_FIFOSIZ << USBFS_HPTXFSIZ_PTXFD_POS));
#endif
    }
}

/**
 * @brief  reset the channel whose channel number is ch_idx
 * @param  [in] USBx        usb instance
 * @param  [in] ch_idx      channel number
 * @retval None
 */
__STATIC_INLINE void usb_chrst(LL_USB_TypeDef *USBx, uint8_t ch_idx)
{
    MODIFY_REG32(USBx->HC_REGS[ch_idx]->HCCHAR,
                 USBFS_HCCHAR_CHENA | USBFS_HCCHAR_CHDIS | USBFS_HCCHAR_EPDIR,
                 USBFS_HCCHAR_CHDIS);
}
#endif /* end of USE_HOST_MODE */

extern void usb_initusbcore(LL_USB_TypeDef *USBx, USB_CORE_BASIC_CFGS *basic_cfgs);
extern void usb_setregaddr(LL_USB_TypeDef *USBx, stc_usb_port_identify *pstcPortIdentify, USB_CORE_BASIC_CFGS *basic_cfgs);
extern void usb_rdpkt(LL_USB_TypeDef *USBx, uint8_t *dest, uint16_t len);
extern void usb_wrpkt(LL_USB_TypeDef *USBx, uint8_t *src, uint8_t ch_ep_num, uint16_t len, uint8_t u8DmaEn);
extern void usb_txfifoflush(LL_USB_TypeDef *USBx, uint32_t num);
extern void usb_rxfifoflush(LL_USB_TypeDef *USBx);
extern void usb_modeset(LL_USB_TypeDef *USBx, uint8_t mode);
extern void usb_coresoftrst(LL_USB_TypeDef *USBx);
extern int32_t USB_DeInit(LL_USB_TypeDef *USBx);

#ifdef USE_HOST_MODE
extern void usb_hostmodeinit(LL_USB_TypeDef *USBx, USB_CORE_BASIC_CFGS *basic_cfgs);
extern void usb_hostinten(LL_USB_TypeDef *USBx, uint8_t u8DmaEn);
extern uint8_t usb_inithch(LL_USB_TypeDef *USBx, uint8_t hc_num, USB_HOST_CH *pCh, uint8_t u8DmaEn);
extern void usb_hoststop(LL_USB_TypeDef *USBx, uint8_t u8ChNum);
extern void usb_hchstop(LL_USB_TypeDef *USBx, uint8_t hc_num);
extern uint8_t usb_hchtransbegin(LL_USB_TypeDef *USBx, uint8_t hc_num, USB_HOST_CH *pCh, uint8_t u8DmaEn);
extern void usb_hprtrst(LL_USB_TypeDef *USBx);
extern void usb_vbusctrl(LL_USB_TypeDef *USBx, uint8_t u8State);
#endif

#ifdef USE_DEVICE_MODE
extern void usb_devmodeinit(LL_USB_TypeDef *USBx, USB_CORE_BASIC_CFGS *basic_cfgs);
extern void usb_devinten(LL_USB_TypeDef *USBx, uint8_t u8DmaEn);
extern void usb_ep0activate(LL_USB_TypeDef *USBx);
extern void usb_epactive(LL_USB_TypeDef *USBx, USB_DEV_EP *ep);
extern void usb_epdeactive(LL_USB_TypeDef *USBx, USB_DEV_EP *ep);
extern void usb_epntransbegin(LL_USB_TypeDef *USBx, USB_DEV_EP *ep, uint8_t u8DmaEn);
extern void usb_ep0transbegin(LL_USB_TypeDef *USBx, USB_DEV_EP *ep, uint8_t u8DmaEn);
extern void usb_setepstall(LL_USB_TypeDef *USBx, USB_DEV_EP *ep);
extern void usb_clearepstall(LL_USB_TypeDef *USBx, USB_DEV_EP *ep);
extern void usb_ep0revcfg(LL_USB_TypeDef *USBx, uint8_t u8DmaEn, uint8_t *u8RevBuf);
extern void usb_remotewakeupen(LL_USB_TypeDef *USBx);
extern void usb_epstatusset(LL_USB_TypeDef *USBx, USB_DEV_EP *ep, uint32_t Status);
extern uint32_t usb_epstatusget(LL_USB_TypeDef *USBx, USB_DEV_EP *ep);
extern void usb_devepdis(LL_USB_TypeDef *USBx, uint8_t u8EpNum);
extern void usb_ctrldevconnect(LL_USB_TypeDef *USBx, uint8_t link);
#endif

/**
 * @}
 */

#endif /* LL_USB_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_USB_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
