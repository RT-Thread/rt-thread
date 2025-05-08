/**
 *******************************************************************************
 * @file  hc32_ll_usb.c
 * @brief USB core driver.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-06-30       CDT             Add USB core ID select function
   2022-10-31       CDT             Add USB DMA function
   2023-09-30       CDT             Fix bug for function usb_clearepstall()
                                    Modify typo
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_usb.h"
#include "usb_bsp.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_USB USB
 * @brief USB Driver Library
 * @{
 */

#if (LL_USB_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*  Parameters check */
#define IS_USB_CORE_ID(x)                                                      \
(   ((x) == USBFS_CORE_ID)                      ||                             \
    ((x) == USBHS_CORE_ID))

#define IS_USB_PHY_TYPE(x)                                                     \
(   ((x) == USBHS_PHY_EMBED)                    ||                             \
    ((x) == USBHS_PHY_EXT))

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup USB_Global_Functions USB Global Functions
 * @{
 */

/**
 * @brief  core software reset
 * @param  [in] USBx        usb instance
 * @retval None
 */
void usb_coresoftrst(LL_USB_TypeDef *USBx)
{
    __IO uint8_t u8Status = USB_OK;;
    __IO uint32_t u32grstctl = 0UL;
    __IO uint32_t u32Count = 0UL;

    /* Wait for AHB master to be idle. */
    do {
        usb_udelay(1UL);
        u32grstctl = READ_REG32(USBx->GREGS->GRSTCTL);
        if (++u32Count > 100000UL) {
            u8Status = USB_ERROR;
        }
    } while (0UL == (u32grstctl & USBFS_GRSTCTL_AHBIDL));

    if (USB_OK == u8Status) {
        /* Write the Core Soft Reset bit to reset the USB core */
        u32Count = 0UL;
        u32grstctl |= USBFS_GRSTCTL_CSRST;
        WRITE_REG32(USBx->GREGS->GRSTCTL, u32grstctl);

        /* Wait for the reset finishing */
        do {
            u32grstctl = READ_REG32(USBx->GREGS->GRSTCTL);
            if (u32Count > 100000UL) {
                break;
            }
            u32Count++;
            usb_udelay(1UL);
        } while (0UL != (u32grstctl & USBFS_GRSTCTL_CSRST));
        /* Wait for at least 3 PHY clocks after the core resets */
        usb_udelay(3UL);
    }
}

/**
 * @brief  Writes a packet whose byte number is len into the Tx FIFO associated
 *         with the EP
 * @param  [in] USBx        usb instance
 * @param  [in] src         source pointer used to hold the transmitted data
 * @param  [in] ch_ep_num   end point index
 * @param  [in] len         length in bytes
 * @param  [in] u8DmaEn     USB DMA status
 * @retval None
 */
void usb_wrpkt(LL_USB_TypeDef *USBx, uint8_t *src, uint8_t ch_ep_num, uint16_t len, uint8_t u8DmaEn)
{
    __IO uint32_t u32pAddr;
    __IO uint32_t *fifo;
    uint32_t u32Count32b;
    uint32_t u32Tmp;
    if (u8DmaEn == 0U) {
        u32Count32b = (len + 3UL);
        u32Count32b = u32Count32b >> 2U;
        fifo = USBx->DFIFO[ch_ep_num];
        u32Tmp = 0UL;
        while (u32Tmp < u32Count32b) {
            WRITE_REG32(*fifo, *((uint32_t *)src));
            u32pAddr = (uint32_t)src;
            src = (uint8_t *)(u32pAddr + 4U);
            u32Tmp++;
        }
    }
}

/**
 * @brief  Reads a packet whose byte number is len from the Rx FIFO
 * @param  [in] USBx        usb instance
 * @param  [in] dest        destination pointer that point to the received data
 * @param  [in] len         number of bytes
 * @retval None
 */
void usb_rdpkt(LL_USB_TypeDef *USBx, uint8_t *dest, uint16_t len)
{
    uint32_t u32Tmp;
    __IO uint32_t u32Count32b;
    __IO uint32_t u32pAddr;

    __IO uint32_t *fifo = USBx->DFIFO[0];
    u32Count32b = (len + 3UL);
    u32Count32b = u32Count32b >> 2U;
    u32pAddr = 0UL;
    u32Tmp = 0UL;
    while (u32Tmp < u32Count32b) {
        *(uint32_t *)dest = READ_REG32(*fifo);
        u32pAddr = (uint32_t)dest;
        dest = (uint8_t *)(u32pAddr + 4U);
        u32Tmp++;
    }
}

/**
 * @brief  Initialize the addresses of the core registers.
 * @param  [in] USBx                usb instance
 * @param  [in] pstcPortIdentify    usb core and phy select
 * @param  [in] basic_cfgs          usb core basic cfgs
 * @retval None
 */
void usb_setregaddr(LL_USB_TypeDef *USBx, stc_usb_port_identify *pstcPortIdentify, USB_CORE_BASIC_CFGS *basic_cfgs)
{
    uint32_t u32Tmp = 0UL;
    uint32_t u32baseAddr = CM_USBFS_BASE;
    DDL_ASSERT(IS_USB_CORE_ID(pstcPortIdentify->u8CoreID));
    DDL_ASSERT(IS_USB_PHY_TYPE(pstcPortIdentify->u8PhyType));
#if defined (USB_INTERNAL_DMA_ENABLED)
    basic_cfgs->dmaen = 1U;
#else
    basic_cfgs->dmaen = 0U;
#endif
    /* initialize device cfg following its address */
    basic_cfgs->host_chnum = USB_MAX_CH_NUM;
    basic_cfgs->dev_epnum = USB_MAX_EP_NUM;
    basic_cfgs->core_type = pstcPortIdentify->u8CoreID;
    basic_cfgs->phy_type = pstcPortIdentify->u8PhyType;
    if (USBFS_CORE_ID == pstcPortIdentify->u8CoreID) {
#ifdef USB_FS_MODE
        u32baseAddr = CM_USBFS_BASE;
#endif
    } else {
#ifdef USB_HS_MODE
        u32baseAddr = CM_USBHS_BASE;
#endif
    }

    USBx->GREGS = (USB_CORE_GREGS *)(u32baseAddr + 0UL);
    USBx->DREGS = (USB_CORE_DREGS *)(u32baseAddr + 0x800UL);

    while (u32Tmp < basic_cfgs->dev_epnum) {
        USBx->INEP_REGS[u32Tmp]  = (USB_CORE_INEPREGS *)(u32baseAddr + 0x900UL + (u32Tmp * 0x20UL));
        USBx->OUTEP_REGS[u32Tmp] = (USB_CORE_OUTEPREGS *)(u32baseAddr + 0xb00UL + (u32Tmp * 0x20UL));
        u32Tmp++;
    }
    u32Tmp = 0UL;
    while (u32Tmp < basic_cfgs->dev_epnum) {
        USBx->DFIFO[u32Tmp] = (uint32_t *)(u32baseAddr + 0x1000UL + (u32Tmp * 0x1000UL));
        u32Tmp++;
    }
    USBx->GCCTL = (uint32_t *)(u32baseAddr + 0xe00UL);
#ifdef USE_HOST_MODE     /* if the application mode is host */
    USBx->HREGS = (USB_CORE_HREGS *)(u32baseAddr + 0x400UL);
    USBx->HPRT = (uint32_t *)(u32baseAddr + 0x440UL);
    u32Tmp = 0UL;
    while (u32Tmp < basic_cfgs->host_chnum) {
        USBx->HC_REGS[u32Tmp] = (USB_CORE_HC_REGS *)(u32baseAddr + 0x500UL + (u32Tmp * 0x20UL));
        u32Tmp++;
    }
#endif  /* USE_HOST_MODE */
}

/**
 * @brief  Initializes the USB controller registers and prepares the core
 *         device mode or host mode operation.
 * @param  [in] USBx        usb instance
 * @param  [in] basic_cfgs  usb core basic cfgs
 * @retval None
 */
void usb_initusbcore(LL_USB_TypeDef *USBx, USB_CORE_BASIC_CFGS *basic_cfgs)
{
    /* reset the core through core soft reset */
    usb_coresoftrst(USBx);

    /* Select PHY for USB core*/
    usb_PhySelect(USBx, basic_cfgs->phy_type);
    if ((basic_cfgs->phy_type == USBHS_PHY_EMBED) && (basic_cfgs->core_type == USBHS_CORE_ID)) {
        /* enable the embedded PHY in USBHS mode */
        CM_PERIC->USB_SYCTLREG |= PERIC_USB_SYCTLREG_USBHS_FSPHYE;
    }
    /* reset the core through core soft reset */
    usb_coresoftrst(USBx);
    usb_mdelay(20UL);
    if (basic_cfgs->dmaen == 1U) {
        /* burst length/type(HBstLen) 64-words x32-bit,  core operates in a DMA mode*/
        usb_BurstLenConfig(USBx, 5U);
        usb_DmaCmd(USBx, 1U);
    }
}

/**
 * @brief  Flush a Tx FIFO whose index is num
 * @param  [in] USBx        usb instance
 * @param  [in] num         txFIFO index
 * @retval None
 */
void usb_txfifoflush(LL_USB_TypeDef *USBx, uint32_t num)
{
    __IO uint32_t u32grstctl;
    __IO uint32_t u32Tmp = 0UL;

    u32grstctl = USBFS_GRSTCTL_TXFFLSH | ((num & 0x1FUL) << USBFS_GRSTCTL_TXFNUM_POS);
    /* set the TxFIFO Flush bit, set TxFIFO Number */
    WRITE_REG32(USBx->GREGS->GRSTCTL, u32grstctl);

    /* wait for the finishing of txFIFO flushing */
    do {
        u32grstctl = READ_REG32(USBx->GREGS->GRSTCTL);
        if (u32Tmp <= 200000UL) {
            u32Tmp++;
        } else {
            break;
        }
        usb_udelay(1UL);
    } while (0UL != (u32grstctl & USBFS_GRSTCTL_TXFFLSH));
    /* Wait for at least 3 PHY clocks after the txfifo has been flushed */
    usb_udelay(3UL);
}

/**
 * @brief  Flush the whole rxFIFO
 * @param  [in] USBx        usb instance
 * @retval None
 */
void usb_rxfifoflush(LL_USB_TypeDef *USBx)
{
    __IO uint32_t u32grstctl;
    __IO uint32_t u32Tmp = 0UL;

    u32grstctl = USBFS_GRSTCTL_RXFFLSH;    /* set the RxFIFO Flush bit */
    WRITE_REG32(USBx->GREGS->GRSTCTL, u32grstctl);
    /* wait for the finishing of rxFIFO flushing */
    do {
        u32grstctl = READ_REG32(USBx->GREGS->GRSTCTL);
        if (u32Tmp <= 200000UL) {
            u32Tmp++;
        } else {
            break;
        }
        usb_udelay(1UL);
    } while (0UL != (u32grstctl & USBFS_GRSTCTL_RXFFLSH));
    /* Wait for at least 3 PHY clocks after the rxfifo has been flushed */
    usb_udelay(3UL);
}

/**
 * @brief  set the core to be host mode or device mode through the second
 *         input parameter.
 * @param  [in] USBx        usb instance
 * @param  [in] mode        mode of HOST_MODE or DEVICE_MODE that the core would be
 * @retval None
 */
void usb_modeset(LL_USB_TypeDef *USBx, uint8_t mode)
{
    if (mode == HOST_MODE) {
        MODIFY_REG32(USBx->GREGS->GUSBCFG, USBFS_GUSBCFG_FHMOD | USBFS_GUSBCFG_FDMOD, USBFS_GUSBCFG_FHMOD);
    } else {
        MODIFY_REG32(USBx->GREGS->GUSBCFG, USBFS_GUSBCFG_FHMOD | USBFS_GUSBCFG_FDMOD, USBFS_GUSBCFG_FDMOD);
    }
    /* wate for the change to take effect */
    usb_mdelay(50UL);
}

#ifdef USE_DEVICE_MODE

/**
 * @brief  initializes the initial status of all endpoints of the device to be
 *         disable.
 * @param  [in] USBx        usb instance
 * @param  [in] u8EpNum     EP number
 * @retval None
 */
void usb_devepdis(LL_USB_TypeDef *USBx, uint8_t u8EpNum)
{
    uint8_t u8Tmp = 0U;

    while (u8Tmp < u8EpNum) {
        if (0UL != READ_REG32_BIT(USBx->INEP_REGS[u8Tmp]->DIEPCTL, USBFS_DIEPCTL_EPENA)) {
            WRITE_REG32(USBx->INEP_REGS[u8Tmp]->DIEPCTL, USBFS_DIEPCTL_EPDIS | USBFS_DIEPCTL_SNAK);
        } else {
            WRITE_REG32(USBx->INEP_REGS[u8Tmp]->DIEPCTL, 0UL);
        }
        WRITE_REG32(USBx->INEP_REGS[u8Tmp]->DIEPTSIZ, 0UL);
        WRITE_REG32(USBx->INEP_REGS[u8Tmp]->DIEPINT, 0xFFUL);
        u8Tmp++;
    }

    u8Tmp = 0U;
    while (u8Tmp < u8EpNum) {
        if (0UL != READ_REG32_BIT(USBx->OUTEP_REGS[u8Tmp]->DOEPCTL, USBFS_DOEPCTL_EPENA)) {
            WRITE_REG32(USBx->OUTEP_REGS[u8Tmp]->DOEPCTL, USBFS_DOEPCTL_EPDIS | USBFS_DOEPCTL_SNAK);
        } else {
            WRITE_REG32(USBx->OUTEP_REGS[u8Tmp]->DOEPCTL, 0UL);
        }
        WRITE_REG32(USBx->OUTEP_REGS[u8Tmp]->DOEPTSIZ, 0UL);
        WRITE_REG32(USBx->OUTEP_REGS[u8Tmp]->DOEPINT, 0xFFUL);
        u8Tmp++;
    }
}

#ifdef USB_FS_MODE
static void usb_DevFSFifoConfig(LL_USB_TypeDef *USBx)
{
    uint32_t u32StardAddr;

    WRITE_REG32(USBx->GREGS->GRXFSIZ, RX_FIFO_FS_SIZE);
    /* set txFIFO and rxFIFO size of EP0 */
    u32StardAddr = RX_FIFO_FS_SIZE;
    WRITE_REG32(USBx->GREGS->HNPTXFSIZ,
                (RX_FIFO_FS_SIZE << USBFS_HNPTXFSIZ_NPTXFSA_POS) | (TX0_FIFO_FS_SIZE << USBFS_HNPTXFSIZ_NPTXFD_POS));
    /* set txFIFO size of EP1 */
    u32StardAddr += TX0_FIFO_FS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[0],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX1_FIFO_FS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP2 */
    u32StardAddr += TX1_FIFO_FS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[1],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX2_FIFO_FS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP3 */
    u32StardAddr += TX2_FIFO_FS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[2],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX3_FIFO_FS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP4 */
    u32StardAddr += TX3_FIFO_FS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[3],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX4_FIFO_FS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP5 */
    u32StardAddr += TX4_FIFO_FS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[4],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX5_FIFO_FS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP6 */
    u32StardAddr += TX5_FIFO_FS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[5],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX6_FIFO_FS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP7 */
    u32StardAddr += TX6_FIFO_FS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[6],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX7_FIFO_FS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP8 */
    u32StardAddr += TX7_FIFO_FS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[7],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX8_FIFO_FS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP9 */
    u32StardAddr += TX8_FIFO_FS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[8],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX9_FIFO_FS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP10 */
    u32StardAddr += TX9_FIFO_FS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[9],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX10_FIFO_FS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP11 */
    u32StardAddr += TX10_FIFO_FS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[10],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX11_FIFO_FS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP12 */
    u32StardAddr += TX11_FIFO_FS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[11],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX12_FIFO_FS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP13 */
    u32StardAddr += TX12_FIFO_FS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[12],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX13_FIFO_FS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP14 */
    u32StardAddr += TX13_FIFO_FS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[13],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX14_FIFO_FS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP15 */
    u32StardAddr += TX14_FIFO_FS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[14],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX15_FIFO_FS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
}
#endif

#ifdef USB_HS_MODE
static void usb_DevHSFifoConfig(LL_USB_TypeDef *USBx)
{
    uint32_t u32StardAddr;

    WRITE_REG32(USBx->GREGS->GRXFSIZ, RX_FIFO_HS_SIZE);
    /* set txFIFO and rxFIFO size of EP0 */
    u32StardAddr = RX_FIFO_HS_SIZE;
    WRITE_REG32(USBx->GREGS->HNPTXFSIZ,
                (RX_FIFO_HS_SIZE << USBFS_HNPTXFSIZ_NPTXFSA_POS) | (TX0_FIFO_HS_SIZE << USBFS_HNPTXFSIZ_NPTXFD_POS));
    /* set txFIFO size of EP1 */
    u32StardAddr += TX0_FIFO_HS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[0],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX1_FIFO_HS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP2 */
    u32StardAddr += TX1_FIFO_HS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[1],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX2_FIFO_HS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP3 */
    u32StardAddr += TX2_FIFO_HS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[2],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX3_FIFO_HS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP4 */
    u32StardAddr += TX3_FIFO_HS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[3],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX4_FIFO_HS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP5 */
    u32StardAddr += TX4_FIFO_HS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[4],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX5_FIFO_HS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP6 */
    u32StardAddr += TX5_FIFO_HS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[5],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX6_FIFO_HS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP7 */
    u32StardAddr += TX6_FIFO_HS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[6],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX7_FIFO_HS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP8 */
    u32StardAddr += TX7_FIFO_HS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[7],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX8_FIFO_HS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP9 */
    u32StardAddr += TX8_FIFO_HS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[8],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX9_FIFO_HS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP10 */
    u32StardAddr += TX9_FIFO_HS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[9],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX10_FIFO_HS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP11 */
    u32StardAddr += TX10_FIFO_HS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[10],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX11_FIFO_HS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP12 */
    u32StardAddr += TX11_FIFO_HS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[11],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX12_FIFO_HS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP13 */
    u32StardAddr += TX12_FIFO_HS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[12],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX13_FIFO_HS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP14 */
    u32StardAddr += TX13_FIFO_HS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[13],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX14_FIFO_HS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
    /* set txFIFO size of EP15 */
    u32StardAddr += TX14_FIFO_HS_SIZE;
    WRITE_REG32(USBx->GREGS->DIEPTXF[14],
                (u32StardAddr << USBFS_DIEPTXF_INEPTXSA_POS) | (TX15_FIFO_HS_SIZE << USBFS_DIEPTXF_INEPTXFD_POS));
}
#endif

/**
 * @brief  initializes the USB controller, include the size of txFIFO, rxFIFO
 *         status of endpoints, interrupt register etc. Details are shown as
 *         follows.
 * @param  [in] USBx        usb instance
 * @param  [in] basic_cfgs  usb core basic cfgs
 * @retval None
 */
void usb_devmodeinit(LL_USB_TypeDef *USBx, USB_CORE_BASIC_CFGS *basic_cfgs)
{
    usb_FrameIntervalConfig(USBx, USB_FRAME_INTERVAL_80);
    usb_DevPhySelect(USBx, basic_cfgs->phy_type);

    if (basic_cfgs->core_type == 0U) {
#ifdef USB_FS_MODE
        usb_DevFSFifoConfig(USBx);
#endif
    } else {
#ifdef USB_HS_MODE
        usb_DevHSFifoConfig(USBx);
#endif
    }

    usb_clrandmskepint(USBx);
    usb_devepdis(USBx, basic_cfgs->dev_epnum);
    usb_coreconn(USBx);
    usb_devinten(USBx, basic_cfgs->dmaen);
}

/**
 * @brief  Enable the interrupt setting when in device mode.
 * @param  [in] USBx        usb instance
 * @param  [in] u8DmaEn     USB DMA status
 * @retval None
 */
void usb_devinten(LL_USB_TypeDef *USBx, uint8_t u8DmaEn)
{
    uint32_t  u32gintmskTmp = 0UL;

    WRITE_REG32(USBx->GREGS->GINTMSK, 0UL);
    WRITE_REG32(USBx->GREGS->GINTSTS, 0xBFFFFFFFUL);
    /* Enable the normal interrupt setting */
    usb_normalinten(USBx);
    if (u8DmaEn == 0U) {
        u32gintmskTmp |= USBFS_GINTMSK_RXFNEM;
    }
    /* Enable interrupts bits corresponding to the Device mode */
    u32gintmskTmp |= (USBFS_GINTMSK_USBSUSPM | USBFS_GINTMSK_USBRSTM | USBFS_GINTMSK_ENUMDNEM
                      | USBFS_GINTMSK_IEPIM | USBFS_GINTMSK_OEPIM | USBFS_GINTMSK_SOFM
                      | USBFS_GINTMSK_IISOIXFRM | USBFS_GINTMSK_IPXFRM_INCOMPISOOUTM);
#ifdef VBUS_SENSING_ENABLED
    u32gintmskTmp |= USBFS_GINTMSK_VBUSVIM;
#endif
    SET_REG32_BIT(USBx->GREGS->GINTMSK, u32gintmskTmp);
}

/**
 * @brief  get the working status of endpoint.
 * @param  [in] USBx        usb instance
 * @param  [in] ep          endpoint instance
 * @retval current status of the endpoint
 */
uint32_t usb_epstatusget(LL_USB_TypeDef *USBx, USB_DEV_EP *ep)
{
    __IO uint32_t u32Status = 0UL;
    uint32_t u32dxepctl;

    if (ep->ep_dir == 1U) {
        u32dxepctl = READ_REG32(USBx->INEP_REGS[ep->epidx]->DIEPCTL);

        if (0UL != (u32dxepctl & USBFS_DIEPCTL_STALL)) {
            u32Status = USB_EP_TX_STALL;
        } else if (0UL != (u32dxepctl & USBFS_DIEPCTL_NAKSTS)) {
            u32Status = USB_EP_TX_NAK;
        } else {
            u32Status = USB_EP_TX_VALID;
        }
    } else {
        u32dxepctl = READ_REG32(USBx->OUTEP_REGS[ep->epidx]->DOEPCTL);
        if (0UL != (u32dxepctl & USBFS_DOEPCTL_STALL)) {
            u32Status = USB_EP_RX_STALL;
        } else if (0UL != (u32dxepctl & USBFS_DOEPCTL_NAKSTS)) {
            u32Status = USB_EP_RX_NAK;
        } else {
            u32Status = USB_EP_RX_VALID;
        }
    }

    return u32Status;
}

/**
 * @brief  set the working status of endpoint.
 * @param  [in] USBx        usb instance
 * @param  [in] ep          endpoint instance
 * @param  [in] Status      new Status that the endpoint would be
 * @retval None
 */
void usb_epstatusset(LL_USB_TypeDef *USBx, USB_DEV_EP *ep, uint32_t Status)
{
    uint32_t u32dxepctl;
    uint8_t u8RetFlag = 0U;

    if (ep->ep_dir == 1U) {
        u32dxepctl = READ_REG32(USBx->INEP_REGS[ep->epidx]->DIEPCTL);

        switch (Status) {
            case USB_EP_TX_STALL:
                usb_setepstall(USBx, ep);
                u8RetFlag = 1U;
                break;
            case USB_EP_TX_NAK:
                u32dxepctl |= USBFS_DIEPCTL_SNAK;
                break;
            case USB_EP_TX_VALID:
                if (0UL != (u32dxepctl & USBFS_DIEPCTL_STALL)) {
                    ep->datax_pid = 0U;
                    usb_clearepstall(USBx, ep);
                    u8RetFlag = 1U;
                }
                u32dxepctl |= (USBFS_DIEPCTL_CNAK | USBFS_DIEPCTL_USBAEP | USBFS_DIEPCTL_EPENA);
                break;
            case USB_EP_TX_DIS:
                u32dxepctl &= (~USBFS_DIEPCTL_USBAEP);
                break;
            default:
                break;
        }
        /* Write register */
        if (1U != u8RetFlag) {
            WRITE_REG32(USBx->INEP_REGS[ep->epidx]->DIEPCTL, u32dxepctl);
        }
    } else {
        u32dxepctl = READ_REG32(USBx->OUTEP_REGS[ep->epidx]->DOEPCTL);

        switch (Status) {
            case USB_EP_RX_STALL:
                u32dxepctl |= USBFS_DOEPCTL_STALL;
                break;
            case USB_EP_RX_NAK:
                u32dxepctl |= USBFS_DOEPCTL_SNAK;
                break;
            case USB_EP_RX_VALID:
                if (0UL != (u32dxepctl & USBFS_DOEPCTL_STALL)) {
                    ep->datax_pid = 0U;
                    usb_clearepstall(USBx, ep);
                    u8RetFlag = 1U;
                }
                u32dxepctl |= (USBFS_DOEPCTL_CNAK | USBFS_DOEPCTL_USBAEP | USBFS_DOEPCTL_EPENA);
                break;
            case USB_EP_RX_DIS:
                u32dxepctl &= (~USBFS_DOEPCTL_USBAEP);
                break;
            default:
                break;
        }
        /* Write register */
        if (1U != u8RetFlag) {
            WRITE_REG32(USBx->OUTEP_REGS[ep->epidx]->DOEPCTL, u32dxepctl);
        }
    }
}

/**
 * @brief  enable the EP0 to be actiove
 * @param  [in] USBx        usb instance
 * @retval None
 */
void  usb_ep0activate(LL_USB_TypeDef *USBx)
{
    uint32_t u32EnumSpeed;
    uint32_t u32DiepctlTmp;

    u32EnumSpeed = READ_REG32(USBx->DREGS->DSTS) & USBFS_DSTS_ENUMSPD;
    u32DiepctlTmp = READ_REG32(USBx->INEP_REGS[0]->DIEPCTL);
    /* Set the MPS of the DIEPCTL0 based on the enumeration speed */
    if ((DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ == u32EnumSpeed)
        || (DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ == u32EnumSpeed)
        || (DSTS_ENUMSPD_FS_PHY_48MHZ == u32EnumSpeed)) {
        u32DiepctlTmp &= (~USBFS_DIEPCTL_MPSIZ);
    } else if (DSTS_ENUMSPD_LS_PHY_6MHZ == u32EnumSpeed) {
        u32DiepctlTmp &= (~USBFS_DIEPCTL_MPSIZ);
        u32DiepctlTmp |= (3UL << USBFS_DIEPCTL_MPSIZ_POS);
    } else {
        ;
    }
    WRITE_REG32(USBx->INEP_REGS[0]->DIEPCTL, u32DiepctlTmp);
    SET_REG32_BIT(USBx->DREGS->DCTL, USBFS_DCTL_CGINAK);
}

/**
 * @brief  enable an EP to be active
 * @param  [in] USBx        usb instance
 * @param  [in] ep          endpoint instance
 * @retval None
 */
void usb_epactive(LL_USB_TypeDef *USBx, USB_DEV_EP *ep)
{
    uint32_t u32Addr;
    uint32_t u32dxepctl;
    uint32_t u32Daintmsk;

    if (ep->ep_dir == 1U) {
        u32Addr = (uint32_t)(&(USBx->INEP_REGS[ep->epidx]->DIEPCTL));
        u32Daintmsk = 1UL << ep->epidx;
    } else {
        u32Addr = (uint32_t)(&(USBx->OUTEP_REGS[ep->epidx]->DOEPCTL));
        u32Daintmsk = 1UL << (USBFS_DAINTMSK_OEPINTM_POS + ep->epidx);
    }
    u32dxepctl = READ_REG32(*(__IO uint32_t *)u32Addr);
    if (0UL == (u32dxepctl & USBFS_DIEPCTL_USBAEP)) {
        u32dxepctl = ((ep->maxpacket << USBFS_DIEPCTL_MPSIZ_POS)
                      | (((uint32_t)ep->trans_type) << USBFS_DIEPCTL_EPTYP_POS)
                      | (((uint32_t)ep->tx_fifo_num) << USBFS_DIEPCTL_TXFNUM_POS)
                      | USBFS_DIEPCTL_SD0PID_SEVNFRM
                      | USBFS_DIEPCTL_USBAEP);

        WRITE_REG32(*(__IO uint32_t *)u32Addr, u32dxepctl);
    }
    SET_REG32_BIT(USBx->DREGS->DAINTMSK, u32Daintmsk);
}

/**
 * @brief  enable an EP to be deactive state if it is active
 * @param  [in] USBx        usb instance
 * @param  [in] ep          endpoint instance
 * @retval None
 */
void usb_epdeactive(LL_USB_TypeDef *USBx, USB_DEV_EP *ep)
{
    uint32_t u32Daintmsk;

    if (ep->ep_dir == 1U) {
        CLR_REG32_BIT(USBx->INEP_REGS[ep->epidx]->DIEPCTL, USBFS_DIEPCTL_USBAEP);
        u32Daintmsk  = 1UL << ep->epidx;
    } else {
        CLR_REG32_BIT(USBx->OUTEP_REGS[ep->epidx]->DOEPCTL, USBFS_DOEPCTL_USBAEP);
        u32Daintmsk = 1UL << (USBFS_DAINTMSK_OEPINTM_POS + ep->epidx);
    }
    CLR_REG32_BIT(USBx->DREGS->DAINTMSK, u32Daintmsk);
}

/**
 * @brief  Setup the data into the EP and begin to transmit data.
 * @param  [in] USBx        usb instance
 * @param  [in] ep          endpoint instance
 * @param  [in] u8DmaEn     USB DMA status
 * @retval None
 */
void usb_epntransbegin(LL_USB_TypeDef *USBx, USB_DEV_EP *ep, uint8_t u8DmaEn)
{
    uint32_t u32depctl;
    uint32_t u32DeptsizTmp;
    uint32_t u32Pktcnt;
    uint32_t u32Xfersize;

    if (ep->ep_dir == 1U) {
        u32depctl = READ_REG32(USBx->INEP_REGS[ep->epidx]->DIEPCTL);
        /* Zero Length Packet? */
        if (ep->xfer_len == 0UL) {
            u32Xfersize = 0UL;
            u32Pktcnt = 1UL;
            u32DeptsizTmp = (u32Xfersize << USBFS_DIEPTSIZ_XFRSIZ_POS) | (u32Pktcnt << USBFS_DIEPTSIZ_PKTCNT_POS);
        } else {
            /* Program the transfer size and packet count
            * as follows: xfersize = N * maxpacket +
            * short_packet pktcnt = N + (short_packet
            * exist ? 1 : 0)
            */
            u32Xfersize = ep->xfer_len;
            u32Pktcnt = (ep->xfer_len - 1U + ep->maxpacket) / ep->maxpacket;
            u32DeptsizTmp = (u32Xfersize << USBFS_DIEPTSIZ_XFRSIZ_POS) | (u32Pktcnt << USBFS_DIEPTSIZ_PKTCNT_POS);
            if (ep->trans_type == EP_TYPE_ISOC) {
                u32DeptsizTmp |= (1UL << USBFS_DIEPTSIZ_MCNT_POS);
            }
        }
        MODIFY_REG32(USBx->INEP_REGS[ep->epidx]->DIEPTSIZ, USBFS_DIEPTSIZ_XFRSIZ | USBFS_DIEPTSIZ_PKTCNT, u32DeptsizTmp);

        if (u8DmaEn == 1U) {
            WRITE_REG32(USBx->INEP_REGS[ep->epidx]->DIEPDMA, ep->dma_addr);
        } else {
            if (ep->trans_type != EP_TYPE_ISOC) {
                /* Enable the Tx FIFO Empty Interrupt for this EP */
                if (ep->xfer_len > 0U) {
                    SET_REG32_BIT(USBx->DREGS->DIEPEMPMSK, 1UL << ep->epidx);
                }
            }
        }

        if (ep->trans_type == EP_TYPE_ISOC) {
            if (((READ_REG32(USBx->DREGS->DSTS) >> USBFS_DSTS_FNSOF_POS) & 0x1U) == 0U) {
                u32depctl |= USBFS_DIEPCTL_SODDFRM;
            } else {
                u32depctl |= USBFS_DIEPCTL_SD0PID_SEVNFRM;
            }
        }

        u32depctl |= (USBFS_DIEPCTL_CNAK | USBFS_DIEPCTL_EPENA);
        WRITE_REG32(USBx->INEP_REGS[ep->epidx]->DIEPCTL, u32depctl);

        if (ep->trans_type == EP_TYPE_ISOC) {
            usb_wrpkt(USBx, ep->xfer_buff, ep->epidx, (uint16_t)ep->xfer_len, u8DmaEn);
        }
    } else {
        u32depctl = READ_REG32(USBx->OUTEP_REGS[ep->epidx]->DOEPCTL);
        /* Program the transfer size and packet count as follows:
        * pktcnt = N
        * xfersize = N * maxpacket
        */
        if (ep->xfer_len == 0U) {
            u32Xfersize = ep->maxpacket;
            u32Pktcnt = 1UL;
            u32DeptsizTmp = (u32Xfersize << USBFS_DOEPTSIZ_XFRSIZ_POS) | (u32Pktcnt << USBFS_DOEPTSIZ_PKTCNT_POS);
        } else {
            u32Pktcnt   = (ep->xfer_len + (ep->maxpacket - 1U)) / ep->maxpacket;
            u32Xfersize = u32Pktcnt * ep->maxpacket;
            u32DeptsizTmp = (u32Xfersize << USBFS_DOEPTSIZ_XFRSIZ_POS) | (u32Pktcnt << USBFS_DOEPTSIZ_PKTCNT_POS);
            ep->xfer_len = u32Xfersize;
        }
        MODIFY_REG32(USBx->OUTEP_REGS[ep->epidx]->DOEPTSIZ, USBFS_DOEPTSIZ_XFRSIZ | USBFS_DOEPTSIZ_PKTCNT, u32DeptsizTmp);

        if (u8DmaEn == 1U) {
            WRITE_REG32(USBx->OUTEP_REGS[ep->epidx]->DOEPDMA, ep->dma_addr);
        }

        if (ep->trans_type == EP_TYPE_ISOC) {
            if (0U != ep->datax_pid) {
                u32depctl |= USBFS_DOEPCTL_SD1PID;
            } else {
                u32depctl |= USBFS_DOEPCTL_SD0PID;
            }
        }
        u32depctl |= (USBFS_DOEPCTL_CNAK | USBFS_DOEPCTL_EPENA);
        WRITE_REG32(USBx->OUTEP_REGS[ep->epidx]->DOEPCTL, u32depctl);
    }
}

/**
 * @brief  Setup the data into the EP0 and begin to transmit data.
 * @param  [in] USBx        usb instance
 * @param  [in] ep          endpoint instance
 * @param  [in] u8DmaEn     USB DMA status
 * @retval None
 */
void usb_ep0transbegin(LL_USB_TypeDef *USBx, USB_DEV_EP *ep, uint8_t u8DmaEn)
{
    uint32_t u32depctl;
    uint32_t u32DeptsizTmp;
    uint32_t u32Pktcnt;
    uint32_t u32Xfersize;

    if (ep->ep_dir == 1U) {
        u32depctl = READ_REG32(USBx->INEP_REGS[0]->DIEPCTL);
        /* Zero Length Packet? */
        if (ep->xfer_len == 0U) {
            u32Xfersize = 0UL;
            u32Pktcnt = 1UL;
            u32DeptsizTmp = (u32Xfersize << USBFS_DIEPTSIZ_XFRSIZ_POS) | (u32Pktcnt << USBFS_DIEPTSIZ_PKTCNT_POS);
        } else {
            if (ep->xfer_len > ep->maxpacket) {
                ep->xfer_len = ep->maxpacket;
                u32Xfersize = ep->maxpacket;
            } else {
                u32Xfersize = ep->xfer_len;
            }
            u32Pktcnt = 1UL;
            u32DeptsizTmp = (u32Xfersize << USBFS_DIEPTSIZ_XFRSIZ_POS) | (u32Pktcnt << USBFS_DIEPTSIZ_PKTCNT_POS);
        }
        MODIFY_REG32(USBx->INEP_REGS[0]->DIEPTSIZ, USBFS_DIEPTSIZ_XFRSIZ | USBFS_DIEPTSIZ_PKTCNT, u32DeptsizTmp);

        if (u8DmaEn == 1U) {
            WRITE_REG32(USBx->INEP_REGS[ep->epidx]->DIEPDMA, ep->dma_addr);
        }

        u32depctl |= (USBFS_DIEPCTL_CNAK | USBFS_DIEPCTL_EPENA);
        WRITE_REG32(USBx->INEP_REGS[0]->DIEPCTL, u32depctl);

        if (u8DmaEn == 0U) {
            /* Enable the Tx FIFO Empty Interrupt for this EP */
            if (ep->xfer_len > 0U) {
                SET_REG32_BIT(USBx->DREGS->DIEPEMPMSK, 1UL << ep->epidx);
            }
        }
    } else {
        u32depctl  = READ_REG32(USBx->OUTEP_REGS[0]->DOEPCTL);
        /* Program the transfer size and packet count as follows:
        * xfersize = N * (maxpacket + 4 - (maxpacket % 4))
        * pktcnt = N           */
        if (ep->xfer_len == 0U) {
            u32Xfersize = 0UL;
            u32Pktcnt = 1UL;
        } else {
            ep->xfer_len = LL_MIN(ep->rem_data_len, ep->maxpacket);
            u32Xfersize = ep->xfer_len;
            u32Pktcnt   = 1UL;
        }
        u32DeptsizTmp = (u32Xfersize << USBFS_DOEPTSIZ_XFRSIZ_POS) | (u32Pktcnt << USBFS_DOEPTSIZ_PKTCNT_POS);
        MODIFY_REG32(USBx->OUTEP_REGS[ep->epidx]->DOEPTSIZ, USBFS_DOEPTSIZ_XFRSIZ | USBFS_DOEPTSIZ_PKTCNT, u32DeptsizTmp);

        if (u8DmaEn == 1U) {
            WRITE_REG32(USBx->OUTEP_REGS[ep->epidx]->DOEPDMA, ep->dma_addr);
        }
        u32depctl |= (USBFS_DOEPCTL_CNAK | USBFS_DOEPCTL_EPENA);
        WRITE_REG32(USBx->OUTEP_REGS[ep->epidx]->DOEPCTL, u32depctl);
    }
}

/**
 * @brief  Set the EP to be stall status
 * @param  [in] USBx        usb instance
 * @param  [in] ep          endpoint instance
 * @retval None
 */
void usb_setepstall(LL_USB_TypeDef *USBx, USB_DEV_EP *ep)
{
    uint32_t u32depctl;

    if (ep->ep_dir == 1U) {
        u32depctl = READ_REG32(USBx->INEP_REGS[ep->epidx]->DIEPCTL);
        if (0UL != (u32depctl & USBFS_DIEPCTL_EPENA)) {
            u32depctl |= USBFS_DIEPCTL_EPDIS;
        }
        u32depctl |= USBFS_DIEPCTL_STALL;
        WRITE_REG32(USBx->INEP_REGS[ep->epidx]->DIEPCTL, u32depctl);
    } else {
        u32depctl = READ_REG32(USBx->OUTEP_REGS[ep->epidx]->DOEPCTL);
        u32depctl |= USBFS_DOEPCTL_STALL;
        WRITE_REG32(USBx->OUTEP_REGS[ep->epidx]->DOEPCTL, u32depctl);
    }
}

/**
 * @brief  clear the stall status of a EP
 * @param  [in] USBx        usb instance
 * @param  [in] ep          endpoint instance
 * @retval None
 */
void usb_clearepstall(LL_USB_TypeDef *USBx, USB_DEV_EP *ep)
{
    uint32_t tmp_depctl_addr;
    uint32_t u32depctl;
    if (ep->ep_dir == 1U) {
        tmp_depctl_addr = (uint32_t)(&(USBx->INEP_REGS[ep->epidx]->DIEPCTL));
    } else {
        tmp_depctl_addr = (uint32_t)(&(USBx->OUTEP_REGS[ep->epidx]->DOEPCTL));
    }
    u32depctl = READ_REG32(*(__IO uint32_t *)tmp_depctl_addr);

    u32depctl &= (~USBFS_DIEPCTL_STALL);
    if ((ep->trans_type == EP_TYPE_INTR) || (ep->trans_type == EP_TYPE_BULK)) {
        u32depctl |= USBFS_DIEPCTL_SD0PID_SEVNFRM;
    }

    WRITE_REG32(*(__IO uint32_t *)tmp_depctl_addr, u32depctl);
}

/**
 * @brief  configure the EPO to receive data packets
 * @param  [in] USBx        usb instance
 * @param  [in] u8DmaEn     USB DMA status
 * @retval None
 */
void usb_ep0revcfg(LL_USB_TypeDef *USBx, uint8_t u8DmaEn, uint8_t *u8RevBuf)
{
    uint32_t u32deptsize;
    uint32_t u32doepctl;

    u32deptsize = (3UL << USBFS_DOEPTSIZ0_STUPCNT_POS)
                  | (1UL << USBFS_DOEPTSIZ0_PKTCNT_POS)
                  | (64UL << USBFS_DOEPTSIZ0_XFRSIZ_POS);

    WRITE_REG32(USBx->OUTEP_REGS[0]->DOEPTSIZ, u32deptsize);

    if (u8DmaEn == 1U) {
        WRITE_REG32(USBx->OUTEP_REGS[0]->DOEPDMA, (uint32_t)&u8RevBuf[0]);
        u32doepctl = READ_REG32(USBx->OUTEP_REGS[0]->DOEPCTL);
        u32doepctl |= (USBFS_DOEPCTL_EPENA | USBFS_DOEPCTL_USBAEP);
        WRITE_REG32(USBx->OUTEP_REGS[0]->DOEPCTL, u32doepctl);
    }
}

/**
 * @brief  enable remote wakeup active
 * @param  [in] USBx        usb instance
 * @retval None
 */
void usb_remotewakeupen(LL_USB_TypeDef *USBx)
{
    uint32_t u32dsts;

    u32dsts = READ_REG32(USBx->DREGS->DSTS);
    if (0UL != (u32dsts & USBFS_DSTS_SUSPSTS)) {
        /* un-gate USB Core clock */
        CLR_REG32_BIT(*USBx->GCCTL, USBFS_GCCTL_GATEHCLK | USBFS_GCCTL_STPPCLK);
    }

    SET_REG32_BIT(USBx->DREGS->DCTL, USBFS_DCTL_RWUSIG);
    usb_mdelay(5UL);
    CLR_REG32_BIT(USBx->DREGS->DCTL, USBFS_DCTL_RWUSIG);
}

/**
 * @brief  control the device to connect or disconnect
 * @param  [in] USBx        usb instance
 * @param  [in] link        0(conn) or 1(disconn)
 * @retval None
 */
void usb_ctrldevconnect(LL_USB_TypeDef *USBx, uint8_t link)
{
    if (0U == link) {
        CLR_REG32_BIT(USBx->DREGS->DCTL, USBFS_DCTL_SDIS);
    } else {
        SET_REG32_BIT(USBx->DREGS->DCTL, USBFS_DCTL_SDIS);
    }
    usb_mdelay(3UL);
}
#endif

#ifdef USE_HOST_MODE
/**
 * @brief  Initializes the USB controller when it is host mode
 * @param  [in] USBx        usb instance
 * @param  [in] basic_cfgs  usb core basic cfgs
 * @retval None
 */
void usb_hostmodeinit(LL_USB_TypeDef *USBx, USB_CORE_BASIC_CFGS *basic_cfgs)
{
    __IO uint8_t u8Tmp = 0U;
    WRITE_REG32(*USBx->GCCTL, 0UL);  /* reset the register-GCCTL */
    if (USBHS_PHY_EMBED == basic_cfgs->phy_type) {
        usb_fslspclkselset(USBx, HCFG_6_MHZ);  /* PHY clock is running at 6MHz */
    } else {
        usb_fslspclkselset(USBx, HCFG_30_60_MHZ);  /* PHY clock is running at 6MHz */
    }
    usb_hprtrst(USBx);                     /* reset the port */
    usb_enumspeed(USBx);                   /* FS or LS bases on the maximum speed supported by the connected device */
    usb_sethostfifo(USBx, basic_cfgs->core_type);
    /* Flush all the txFIFO and the whole rxFIFO */
    usb_txfifoflush(USBx, 0x10UL);
    usb_rxfifoflush(USBx);
    /* Clear all HC Interrupt bits that are pending */
    while (u8Tmp < basic_cfgs->host_chnum) {
        WRITE_REG32(USBx->HC_REGS[u8Tmp]->HCINT, 0xFFFFFFFFUL);
        WRITE_REG32(USBx->HC_REGS[u8Tmp]->HCINTMSK, 0UL);
        u8Tmp++;
    }
    usb_hostinten(USBx, basic_cfgs->dmaen);
}

/**
 * @brief  set the vbus if state is 1 or reset the vbus if state is 0.
 * @param  [in] USBx        usb instance
 * @param  [in] u8State       the vbus state it would be.
 * @retval None
 */
void usb_vbusctrl(LL_USB_TypeDef *USBx, uint8_t u8State)
{
    uint32_t u32hprt;

    u32hprt = usb_rdhprt(USBx);
    if ((0UL == (u32hprt & USBFS_HPRT_PWPR)) && (1U == u8State)) {
        u32hprt |= USBFS_HPRT_PWPR;
        WRITE_REG32(*USBx->HPRT, u32hprt);
    }
    if ((0UL != (u32hprt & USBFS_HPRT_PWPR)) && (0U == u8State)) {
        u32hprt &= (~USBFS_HPRT_PWPR);
        WRITE_REG32(*USBx->HPRT, u32hprt);
    }
}

/**
 * @brief  Enables the related interrupts when the core is host mode
 * @param  [in] USBx        usb instance
 * @param  [in] u8DmaEn     USB DMA status
 * @retval None
 */
void usb_hostinten(LL_USB_TypeDef *USBx, uint8_t u8DmaEn)
{
    uint32_t u32gIntmsk = 0UL;
    WRITE_REG32(USBx->GREGS->GINTMSK, 0UL);
    /* Clear the pending interrupt bits */
    WRITE_REG32(USBx->GREGS->GINTSTS, 0xFFFFFFFFUL);

    /* Enable the normal interrupt bits */
    usb_normalinten(USBx);

    if (u8DmaEn == 0U) {
        u32gIntmsk |= USBFS_GINTMSK_RXFNEM;
    }
    u32gIntmsk |= (USBFS_GINTMSK_HPRTIM
                   | USBFS_GINTMSK_HCIM
                   | USBFS_GINTMSK_DISCIM
                   | USBFS_GINTMSK_SOFM
                   | USBFS_GINTMSK_IPXFRM_INCOMPISOOUTM);
    SET_REG32_BIT(USBx->GREGS->GINTMSK, u32gIntmsk);
}

/**
 * @brief  Reset the port, the 1'b0 state must last at lease 10ms.
 * @param  [in] USBx        usb instance
 * @retval None
 */
void usb_hprtrst(LL_USB_TypeDef *USBx)
{
    uint32_t u32hprt;
    u32hprt = usb_rdhprt(USBx);
    u32hprt |= USBFS_HPRT_PRST;
    WRITE_REG32(*USBx->HPRT, u32hprt);
    usb_mdelay(10UL);
    u32hprt &= ~USBFS_HPRT_PRST;
    WRITE_REG32(*USBx->HPRT, u32hprt);
    usb_mdelay(20UL);
}

/**
 * @brief  Prepares transferring packets on a host channel
 * @param  [in] USBx        usb instance
 * @param  [in] hc_num      channel index
 * @param  [in] pCh         channel structure
 * @param  [in] u8DmaEn     USB DMA status
 * @retval status in byte
 */
uint8_t usb_inithch(LL_USB_TypeDef *USBx, uint8_t hc_num, USB_HOST_CH *pCh, uint8_t u8DmaEn)
{
    uint32_t u32hcintmsk = 0UL;
    uint32_t u32hcchar = 0UL;

    WRITE_REG32(USBx->HC_REGS[hc_num]->HCINT, 0xFFFFFFFFUL);
    if (u8DmaEn == 1U) {
        u32hcintmsk |= USBFS_HCINTMSK_AHBERRM;
    }
    switch (pCh->ep_type) {
        case EP_TYPE_CTRL:
        case EP_TYPE_BULK:
            u32hcintmsk |= (USBFS_HCINTMSK_XFRCM
                            | USBFS_HCINTMSK_STALLM
                            | USBFS_HCINTMSK_TXERRM
                            | USBFS_HCINTMSK_DTERRM
                            | USBFS_HCINTMSK_NAKM);
            if (0U != pCh->is_epin) {
                u32hcintmsk |= USBFS_HCINTMSK_BBERRM;
            } else {
                u32hcintmsk |= USBHS_HCINT_NYET;
                if (0U != pCh->do_ping) {
                    u32hcintmsk |= USBFS_HCINTMSK_ACKM;
                }
            }
            break;
        case EP_TYPE_INTR:
            u32hcintmsk |= (USBFS_HCINTMSK_XFRCM
                            | USBFS_HCINTMSK_NAKM
                            | USBFS_HCINTMSK_STALLM
                            | USBFS_HCINTMSK_TXERRM
                            | USBFS_HCINTMSK_DTERRM
                            | USBFS_HCINTMSK_FRMORM);
            if (0U != pCh->is_epin) {
                u32hcintmsk |= USBFS_HCINTMSK_BBERRM;
            }
            break;
        case EP_TYPE_ISOC:
            u32hcintmsk |= (USBFS_HCINTMSK_XFRCM
                            | USBFS_HCINTMSK_FRMORM
                            | USBFS_HCINTMSK_ACKM);

            if (0U != pCh->is_epin) {
                u32hcintmsk |= (USBFS_HCINTMSK_TXERRM | USBFS_HCINTMSK_BBERRM);
            }
            break;
        default:
            break;
    }

    WRITE_REG32(USBx->HC_REGS[hc_num]->HCINTMSK, u32hcintmsk);
    SET_REG32_BIT(USBx->HREGS->HAINTMSK, 1UL << hc_num);

    /* enable the host channel interrupts */
    SET_REG32_BIT(USBx->GREGS->GINTMSK, USBFS_GINTMSK_HCIM);

    /* modify HCCHAR */
    u32hcchar |= (((uint32_t)pCh->dev_addr) << USBFS_HCCHAR_DAD_POS);
    u32hcchar |= (((uint32_t)pCh->ep_idx) << USBFS_HCCHAR_EPNUM_POS);
    u32hcchar |= (((uint32_t)pCh->is_epin) << USBFS_HCCHAR_EPDIR_POS);
    u32hcchar |= (((uint32_t)pCh->ep_type) << USBFS_HCCHAR_EPTYP_POS);
    u32hcchar |= (((uint32_t)pCh->max_packet) << USBFS_HCCHAR_MPSIZ_POS);
    if (PRTSPD_LOW_SPEED == pCh->ch_speed) {
        u32hcchar |= USBFS_HCCHAR_LSDEV;
    } else {
        u32hcchar &= ~USBFS_HCCHAR_LSDEV;
    }

    if (pCh->ep_type == EP_TYPE_INTR) {
        u32hcchar |= USBFS_HCCHAR_ODDFRM;
    }
    WRITE_REG32(USBx->HC_REGS[hc_num]->HCCHAR, u32hcchar);
    return USB_OK;
}

/**
 * @brief  Start transfer on the channel whose index is hc_num.
 * @param  [in] USBx        usb instance
 * @param  [in] hc_num      channel index
 * @param  [in] pCh         channel structure
 * @param  [in] u8DmaEn     USB DMA status
 * @retval status in 8 bits
 */
uint8_t usb_hchtransbegin(LL_USB_TypeDef *USBx, uint8_t hc_num, USB_HOST_CH *pCh, uint8_t u8DmaEn)
{
    uint32_t u32hcchar;
    uint32_t u32hctsiz = 0UL;
    uint32_t u32hnptxsts;
    uint32_t u32hptxsts;
    uint16_t u16LenWords;
    uint16_t u16NumPacket;
    uint16_t u16MaxHcPktCount = 256U;

    /* Compute the expected number of packets associated to the transfer */
    if (pCh->xfer_len > 0U) {
        u16NumPacket = (uint16_t)((pCh->xfer_len +
                                   (uint32_t)pCh->max_packet - 1UL) / (uint32_t)pCh->max_packet);

        if (u16NumPacket > u16MaxHcPktCount) {
            u16NumPacket = u16MaxHcPktCount;
            pCh->xfer_len = (uint32_t)u16NumPacket * (uint32_t)pCh->max_packet;
        }
    } else {
        u16NumPacket = 1U;
    }
    if (0U != pCh->is_epin) {
        pCh->xfer_len = (uint32_t)u16NumPacket * (uint32_t)pCh->max_packet;
    }

    u32hctsiz |= (((uint32_t)pCh->xfer_len) << USBFS_HCTSIZ_XFRSIZ_POS);
    u32hctsiz |= (((uint32_t)u16NumPacket) << USBFS_HCTSIZ_PKTCNT_POS);
    u32hctsiz |= (((uint32_t)pCh->pid_type) << USBFS_HCTSIZ_DPID_POS);
    WRITE_REG32(USBx->HC_REGS[hc_num]->HCTSIZ, u32hctsiz);

    if (u8DmaEn == 1U) {
        WRITE_REG32(USBx->HC_REGS[hc_num]->HCDMA, pCh->xfer_buff);
    }

    u32hcchar = READ_REG32(USBx->HC_REGS[hc_num]->HCCHAR);
    u32hcchar &= ~USBFS_HCCHAR_ODDFRM;
    u32hcchar |= (usb_ifevenframe(USBx) << USBFS_HCCHAR_ODDFRM_POS);

    /* enable this host channel whose number is hc_num */
    u32hcchar |= USBFS_HCCHAR_CHENA;
    u32hcchar &= ~USBFS_HCCHAR_CHDIS;
    WRITE_REG32(USBx->HC_REGS[hc_num]->HCCHAR, u32hcchar);

    if (u8DmaEn == 0U) {
        if ((pCh->is_epin == 0U) && (pCh->xfer_len > 0U)) {
            switch (pCh->ep_type) {
                /* Non-periodic transmit */
                case EP_TYPE_CTRL:
                case EP_TYPE_BULK:
                    u32hnptxsts = READ_REG32(USBx->GREGS->HNPTXSTS);
                    u16LenWords = (uint16_t)((pCh->xfer_len + 3UL) / 4UL);
                    /* check if the amount of free space available in the non-periodic txFIFO is enough */
                    if (u16LenWords > ((u32hnptxsts & USBFS_HNPTXSTS_NPTXFSAV) >> USBFS_HNPTXSTS_NPTXFSAV_POS)) {
                        /* enable interrrupt of nptxfempty of GINTMSK*/
                        SET_REG32_BIT(USBx->GREGS->GINTMSK, USBFS_GINTMSK_NPTXFEM);
                    }
                    break;
                /* Periodic trnsmit */
                case EP_TYPE_INTR:
                case EP_TYPE_ISOC:
                    u32hptxsts = READ_REG32(USBx->HREGS->HPTXSTS);
                    u16LenWords = (uint16_t)((pCh->xfer_len + 3UL) / 4UL);
                    /* check if the space of periodic TxFIFO is enough */
                    if (u16LenWords > ((u32hptxsts & USBFS_HPTXSTS_PTXFSAVL) >> USBFS_HPTXSTS_PTXFSAVL_POS)) {
                        /* enable interrrupt of ptxfempty of GINTMSK */
                        SET_REG32_BIT(USBx->GREGS->GINTMSK, USBFS_GINTMSK_PTXFEM);
                    }
                    break;
                default:
                    break;
            }

            usb_wrpkt(USBx, pCh->xfer_buff, hc_num, (uint16_t)pCh->xfer_len, u8DmaEn);
        }
    }
    return USB_OK;
}

/**
 * @brief  Stop the host and flush all the txFIFOs and the whole rxFIFO.
 * @param  [in] USBx        usb instance
 * @param  [in] u8ChNum     Host channel number
 * @retval None
 */
void usb_hoststop(LL_USB_TypeDef *USBx, uint8_t u8ChNum)
{
    __IO uint32_t u32Tmp = 0UL;

    WRITE_REG32(USBx->HREGS->HAINTMSK, 0UL);
    WRITE_REG32(USBx->HREGS->HAINT, 0xFFFFFFFFUL);

    do {
        usb_chrst(USBx, (uint8_t)u32Tmp);
        u32Tmp++;
    } while (u32Tmp < u8ChNum);
    /* flush all the txFIFOs and the whole rxFIFO */
    usb_rxfifoflush(USBx);
    usb_txfifoflush(USBx, 0x10UL);
}

/**
 * @brief  make the channel to halt
 * @param  [in] USBx        usb instance
 * @param  [in] hc_num      channel index
 * @retval None
 */
void usb_hchstop(LL_USB_TypeDef *USBx, uint8_t hc_num)
{
    uint32_t u32hcchar;

    u32hcchar = READ_REG32(USBx->HC_REGS[hc_num]->HCCHAR);
    u32hcchar |= USBFS_HCCHAR_CHDIS;
    /* Check for space in the request queue to issue the halt. */
    if ((EP_TYPE_CTRL == ((u32hcchar & USBFS_HCCHAR_EPTYP) >> USBFS_HCCHAR_EPTYP_POS))
        || (EP_TYPE_BULK == ((u32hcchar & USBFS_HCCHAR_EPTYP) >> USBFS_HCCHAR_EPTYP_POS))) {
        if (0UL == (READ_REG32(USBx->GREGS->HNPTXSTS) & USBFS_HNPTXSTS_NPTQXSAV)) {
            u32hcchar &= (~USBFS_HCCHAR_CHENA);
            WRITE_REG32(USBx->HC_REGS[hc_num]->HCCHAR, u32hcchar);
        }
    } else {
        if (0UL == (READ_REG32(USBx->HREGS->HPTXSTS) & USBFS_HPTXSTS_PTXQSAV)) {
            u32hcchar &= (~USBFS_HCCHAR_CHENA);
            WRITE_REG32(USBx->HC_REGS[hc_num]->HCCHAR, u32hcchar);
        }
    }
    u32hcchar |= USBFS_HCCHAR_CHENA;
    WRITE_REG32(USBx->HC_REGS[hc_num]->HCCHAR, u32hcchar);
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
