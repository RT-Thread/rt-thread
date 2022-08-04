/**
 *******************************************************************************
 * @file  usb_dev_driver.c
 * @brief Peripheral Device Interface Layer
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
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
#include "usb_dev_driver.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_CORE
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

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
 * @brief  Device intialize
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_initdev(usb_core_instance *pdev)
{
    uint32_t tmp_1;
    USB_DEV_EP *iep, *oep;

    usb_setregaddr(&pdev->regs, &pdev->basic_cfgs);
    pdev->dev.device_cur_status = (uint8_t)USB_DEV_DEFAULT;
    pdev->dev.device_address = 0U;
    tmp_1 = 0UL;
    do {
        iep = &pdev->dev.in_ep[tmp_1];
        oep = &pdev->dev.out_ep[tmp_1];
        iep->ep_dir = 1U;
        oep->ep_dir = 0U;
        iep->epidx = (uint8_t)tmp_1;
        oep->epidx = iep->epidx;
        iep->tx_fifo_num = (uint16_t)tmp_1;
        oep->tx_fifo_num = iep->tx_fifo_num;
        iep->trans_type = EP_TYPE_CTRL;
        oep->trans_type = iep->trans_type;
        iep->maxpacket = USB_MAX_EP0_SIZE;
        oep->maxpacket = iep->maxpacket;
        iep->xfer_buff = 0U;
        oep->xfer_buff = iep->xfer_buff;
        iep->xfer_len = 0UL;
        oep->xfer_len = iep->xfer_len;
        tmp_1++;
    } while (tmp_1 < pdev->basic_cfgs.dev_epnum);

    usb_gintdis(&pdev->regs);
    /*Init the Core (common init.) */
    usb_initusbcore(&pdev->regs, &pdev->basic_cfgs);
    /* Force Device Mode*/
    usb_modeset(&pdev->regs, DEVICE_MODE);
    /* Init Device */
    usb_devmodeinit(&pdev->regs, &pdev->basic_cfgs);
    /* Enable USB Global interrupt */
    usb_ginten(&pdev->regs);
}

/**
 * @brief  Configure and open an endpoint
 * @param  [in] pdev        device instance
 * @param  [in] ep_addr     endpoint address
 * @param  [in] ep_mps      endpoint mps
 * @param  [in] ep_type     endpoint type
 * @retval None
 */
void usb_opendevep(usb_core_instance *pdev, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type)
{
    USB_DEV_EP *ep;
    __IO uint8_t tmp_1, tmp_2;

    tmp_1 = ep_addr >> 7;     /* EP type, it is IN(=1) or OUT(=0) */
    tmp_2 = ep_addr & 0x7FU;  /* EP number */
    if (tmp_1 == 1U) {
        ep = &pdev->dev.in_ep[tmp_2];
    } else {
        ep = &pdev->dev.out_ep[tmp_2];
    }

    ep->epidx  = tmp_2;

    ep->ep_dir = tmp_1;
    ep->maxpacket = ep_mps;
    ep->trans_type = ep_type;
    if (tmp_1 == 1U) {
        /* Assign a Tx FIFO */
        ep->tx_fifo_num = tmp_2;
    }
    /* Set initial data PID. */
    if (ep_type == EP_TYPE_BULK) {
        ep->data_pid_start = 0U;
    }
    usb_epactive(&pdev->regs, ep);
}

/**
 * @brief  called when an EP is disabled
 * @param  [in] pdev        device instance
 * @param  [in] ep_addr     endpoint address
 * @retval None
 */
void usb_shutdevep(usb_core_instance *pdev, uint8_t  ep_addr)
{
    USB_DEV_EP *ep;
    __IO uint8_t tmp_1, tmp_2;

    tmp_1 = ep_addr >> 7;     /* EP type, it is IN(=1) or OUT(=0) */
    tmp_2 = ep_addr & 0x7FU;   /* EP number */
    if (tmp_1 == 1U) {
        ep = &pdev->dev.in_ep[tmp_2];
    } else {
        ep = &pdev->dev.out_ep[tmp_2];
    }
    ep->epidx  = tmp_2;
    ep->ep_dir = tmp_1;
    usb_epdeactive(&pdev->regs, ep);
}

/**
 * @brief  usb_readytorx
 * @param  [in] pdev        device instance
 * @param  [in] ep_addr     endpoint address
 * @param  [out] pbuf       pointer to Rx buffer
 * @param  [in] buf_len     data length
 * @retval status
 */
void usb_readytorx(usb_core_instance *pdev, uint8_t ep_addr, uint8_t *pbuf, uint16_t buf_len)
{
    USB_DEV_EP *ep;
    __IO uint8_t tmp_1;

    tmp_1 = ep_addr & 0x7FU;   /* EP number */
    ep = &pdev->dev.out_ep[tmp_1];
    /*setup and start the Xfer */
    ep->xfer_buff = pbuf;
    ep->xfer_len = (uint32_t)buf_len;
    ep->xfer_count = 0UL;
    ep->ep_dir = 0U;
    ep->epidx = tmp_1;

    if (pdev->basic_cfgs.dmaen == 1U) {
        ep->dma_addr = (uint32_t)pbuf;
    }

    if (tmp_1 == 0U) {
        usb_ep0transbegin(&pdev->regs, ep, pdev->basic_cfgs.dmaen);
    } else {
        usb_epntransbegin(&pdev->regs, ep, pdev->basic_cfgs.dmaen);
    }
}

/**
 * @brief  configures EPO to receive SETUP packets from host
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_ep0outstart(usb_core_instance *pdev)
{
    pdev->dev.out_ep[0].xfer_len       = 64U;
    pdev->dev.out_ep[0].rem_data_len   = 64U;
    pdev->dev.out_ep[0].total_data_len = 64U;
    usb_ep0revcfg(&pdev->regs, pdev->basic_cfgs.dmaen, pdev->dev.setup_pkt_buf);
}

/**
 * @brief  Transmit data over USB
 * @param  [in] pdev        device instance
 * @param  [in] ep_addr     endpoint address
 * @param  [in] pbuf        pointer to Tx buffer
 * @param  [in] buf_len     data length
 * @retval None
 */
void usb_deveptx(usb_core_instance *pdev, uint8_t ep_addr, uint8_t *pbuf, uint32_t buf_len)
{
    USB_DEV_EP *ep;
    __IO uint8_t tmp_1;

    tmp_1 = ep_addr & 0x7FU;   /* EP number */
    ep = &pdev->dev.in_ep[tmp_1];

    /* Setup and start the Transfer */
    ep->ep_dir = 1U;
    ep->epidx = tmp_1;
    ep->xfer_buff = pbuf;
    ep->dma_addr = (uint32_t)pbuf;
    ep->xfer_count = 0UL;
    ep->xfer_len  = buf_len;

    if (tmp_1 == 0U) {
        usb_ep0transbegin(&pdev->regs, ep, pdev->basic_cfgs.dmaen);
    } else {
        usb_epntransbegin(&pdev->regs, ep, pdev->basic_cfgs.dmaen);
    }
}

/**
 * @brief  Stall an endpoint.
 * @param  [in] pdev        device instance
 * @param  [in] epnum       endpoint address
 * @retval None
 */
void usb_stalldevep(usb_core_instance *pdev, uint8_t epnum)
{
    USB_DEV_EP *ep;
    __IO uint8_t tmp_1, tmp_2;

    tmp_1 = epnum >> 7;     /* EP type, it is IN(=1) or OUT(=0) */
    tmp_2 = epnum & 0x7FU;  /* EP number */

    if (tmp_1 != 0U) {
        ep = &pdev->dev.in_ep[tmp_2];
    } else {
        ep = &pdev->dev.out_ep[tmp_2];
    }

    ep->ep_stall = 1U;
    ep->epidx    = tmp_2;
    if (tmp_1 != 0U) {
        ep->ep_dir = 1U;
    } else {
        ep->ep_dir = 0U;
    }

    usb_setepstall(&pdev->regs, ep);
}

/**
 * @brief  Clear stall condition on endpoints.
 * @param  [in] pdev        device instance
 * @param  [in] epnum       endpoint address
 * @retval status
 */
void usb_clrstall(usb_core_instance *pdev, uint8_t epnum)
{
    USB_DEV_EP *ep;
    __IO uint8_t tmp_1, tmp_2;

    tmp_1 = epnum >> 7;     /* EP type, it is IN(=1) or OUT(=0) */
    tmp_2 = epnum & 0x7FU;  /* EP number */
    if (tmp_1 != 0U) {
        ep = &pdev->dev.in_ep[tmp_2];
    } else {
        ep = &pdev->dev.out_ep[tmp_2];
    }

    ep->ep_stall = 0U;
    ep->epidx    = tmp_2;
    if (tmp_1 != 0U) {
        ep->ep_dir = 1U;
    } else {
        ep->ep_dir = 0U;
    }

    usb_clearepstall(&pdev->regs, ep);
}

/**
 * @brief  This Function flushes the FIFOs.
 * @param  [in] pdev        device instance
 * @param  [in] epnum       endpoint address
 * @retval status
 */
void usb_flsdevep(usb_core_instance *pdev, uint8_t epnum)
{
    __IO uint8_t tmp_1;

    tmp_1 = epnum >> 7;     /* EP type, it is IN(=1) or OUT(=0) */
    if (tmp_1 != 0U) {
        usb_txfifoflush(&pdev->regs, (uint32_t)epnum & (uint32_t)0x7F);
    } else {
        usb_rxfifoflush(&pdev->regs);
    }
}

/**
 * @brief  This Function set USB device address
 * @param  [in] pdev        device instance
 * @param  [in] devaddr     new device address
 * @retval None
 */
void usb_addrset(usb_core_instance *pdev, uint8_t devaddr)
{
    usb_devaddrset(&pdev->regs, devaddr);
}

/**
 * @brief  control device connect or disconnect
 * @param  [in] pdev        device instance
 * @param  [in] link        0(conn) or 1(disconn)
 * @retval None
 */
void usb_conndevctrl(usb_core_instance *pdev, uint8_t link)
{
    usb_ctrldevconnect(&pdev->regs, link);
}

/**
 * @brief  returns the EP Status
 * @param  [in] pdev        device instance
 * @param  [in] epnum       endpoint address
 * @retval EP status
 */
uint32_t usb_devepstatusget(usb_core_instance *pdev, uint8_t epnum)
{
    USB_DEV_EP *ep;
    uint32_t Status;
    __IO uint8_t tmp_1, tmp_2;

    tmp_1 = epnum >> 7;     /* EP type, it is IN(=1) or OUT(=0) */
    tmp_2 = epnum & 0x7FU;  /* EP number */
    if (tmp_1 != 0U) {
        ep = &pdev->dev.in_ep[tmp_2];
    } else {
        ep = &pdev->dev.out_ep[tmp_2];
    }

    Status = usb_epstatusget(&pdev->regs, ep);
    /* Return the current status */
    return Status;
}

/**
 * @brief  Set the EP Status
 * @param  [in] pdev        device instance
 * @param  [in] status      new Status
 * @param  [in] epnum       EP address
 * @retval None
 */
void usb_devepstatusset(usb_core_instance *pdev, uint8_t epnum, uint32_t status)
{
    USB_DEV_EP *ep;
    __IO uint8_t tmp_1, tmp_2;

    tmp_1 = epnum >> 7;     /* EP type, it is IN(=1) or OUT(=0) */
    tmp_2 = epnum & 0x7FU;  /* EP number */
    if (tmp_1 != 0U) {
        ep = &pdev->dev.in_ep[tmp_2];
    } else {
        ep = &pdev->dev.out_ep[tmp_2];
    }

    usb_epstatusset(&pdev->regs, ep, status);
}

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
