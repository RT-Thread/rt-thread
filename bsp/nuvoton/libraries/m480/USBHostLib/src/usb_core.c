/**************************************************************************//**
 * @file     usb_core.c
 * @version  V1.10
 * @brief   USB Host library core.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "NuMicro.h"

#include "usb.h"
#include "hub.h"

/// @cond HIDDEN_SYMBOLS

USBH_T     *_ohci;
HSUSBH_T   *_ehci;

static UDEV_DRV_T *  _drivers[MAX_UDEV_DRIVER];
static CONN_FUNC  *g_conn_func, *g_disconn_func;

/**
  * @brief       Initialize M480 USB Host controller and USB stack.
  *
  * @return      None.
  */
void  usbh_core_init()
{
    NVIC_DisableIRQ(HSUSBH_IRQn);
    NVIC_DisableIRQ(USBH_IRQn);

    _ohci = USBH;
    _ehci = HSUSBH;

    memset(_drivers, 0, sizeof(_drivers));

    g_conn_func = NULL;
    g_disconn_func = NULL;

//    usbh_hub_init();

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)    /* Only M480MD has EHCI. */
    {
        _ehci->USBPCR0 = 0x160;                /* enable PHY 0          */
        _ehci->USBPCR1 = 0x520;                /* enable PHY 1          */
    }

    usbh_memory_init();

    _ohci->HcMiscControl |= USBH_HcMiscControl_OCAL_Msk; /* Over-current active low  */
    //_ohci->HcMiscControl &= ~USBH_HcMiscControl_OCAL_Msk; /* Over-current active high  */

#ifdef ENABLE_OHCI
    ohci_driver.init();
    ENABLE_OHCI_IRQ();
#endif

#ifdef ENABLE_EHCI
    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)    /* Only M480MD has EHCI. */
    {
        ehci_driver.init();
        ENABLE_EHCI_IRQ();
    }
#endif
}

/**
  * @brief    Let USB stack polls all root hubs. If there's any hub port
  *           change found, USB stack will manage the hub events in this function call.
  *           In this function, USB stack enumerates newly connected devices and remove staff
  *           of disconnected devices. User's application should periodically invoke this
  *           function.
  * @return   There's hub port change or not.
  * @retval   0   No any hub port status changes found.
  * @retval   1   There's hub port status changes.
  */
int  usbh_polling_root_hubs(void)
{
    int   ret, change = 0;

#ifdef ENABLE_EHCI
    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)    /* Only M480MD has EHCI. */
    {
        _ehci->UPSCR[1] = HSUSBH_UPSCR_PP_Msk | HSUSBH_UPSCR_PO_Msk;     /* set port 2 owner to OHCI              */
        do
        {
            ret = ehci_driver.rthub_polling();
            if (ret)
                change = 1;
        }
        while (ret == 1);
    }
#endif

#ifdef ENABLE_OHCI
    do
    {
        ret = ohci_driver.rthub_polling();
        if (ret)
            change = 1;
    }
    while (ret == 1);
#endif

    return change;
}

/**
  * @brief    Force to quit an endpoint transfer.
  * @param[in]  udev     The USB device.
  * @param[in]  ep       The endpoint to be quit.
  * @retval   0     Transfer success
  * @retval   < 0   Failed. Refer to error code definitions.
  */
int usbh_quit_xfer(UDEV_T *udev, EP_INFO_T *ep)
{
    return udev->hc_driver->quit_xfer(NULL, ep);
}


int usbh_connect_device(UDEV_T *udev)
{
    usbh_delay_ms(100);                   /* initially, give 100 ms delay               */

    if (g_conn_func)
        g_conn_func(udev, 0);
    
    return 0;
}


void usbh_disconnect_device(UDEV_T *udev)
{
    USB_debug("disconnect device...\n");

    if (g_disconn_func)
        g_disconn_func(udev, 0);

    
#if 1    //CHECK: Maybe create a new API to quit_xfer and free udev for application    
    usbh_quit_xfer(udev, &(udev->ep0));    /* Quit control transfer if hw_pipe is not NULL.  */

    /* remove device from global device list */
//    free_dev_address(udev->dev_num);
    free_device(udev);

//    usbh_memory_used();
#endif
}

/**
  * @brief    Install device connect and disconnect callback function.
  *
  * @param[in]  conn_func       Device connect callback function.
  * @param[in]  disconn_func    Device disconnect callback function.
  * @return      None.
  */
void usbh_install_conn_callback(CONN_FUNC *conn_func, CONN_FUNC *disconn_func)
{
    g_conn_func = conn_func;
    g_disconn_func = disconn_func;
}

int usbh_reset_port(UDEV_T *udev)
{
    if (udev->parent == NULL)
    {
        if (udev->hc_driver)
            return udev->hc_driver->rthub_port_reset(udev->port_num-1);
        else
            return USBH_ERR_NOT_FOUND;
    }
    else
    {
        return udev->parent->port_reset(udev->parent, udev->port_num);
    }
}


/**
  * @brief    Force to quit an UTR transfer.
  * @param[in]  utr    The UTR transfer to be quit.
  * @retval   0     Transfer success
  * @retval   < 0   Failed. Refer to error code definitions.
  */
int usbh_quit_utr(UTR_T *utr)
{
    if (!utr || !utr->udev)
        return USBH_ERR_NOT_FOUND;

    return utr->udev->hc_driver->quit_xfer(utr, NULL);
}


/**
  * @brief    Execute an USB request in control transfer. This function returns after the request
  *           was done or aborted.
  * @param[in]  udev            The target USB device.
  * @param[in]  bmRequestType   Characteristics of request
  * @param[in]  bRequest        Specific request
  * @param[in]  wValue          Word-sized field that varies according to request
  * @param[in]  wIndex          Word-sized field that varies according to request
  * @param[in]  wLength         Number of bytes to transfer if there is a Data stage
  * @param[in]  buff            Data buffer used in data stage
  * @param[out] xfer_len        Transmitted/received length of data
  * @param[in]  timeout         Time-out limit (in 10ms - timer tick) of this transfer
  * @retval   0     Transfer success
  * @retval   < 0   Transfer failed. Refer to error code definitions.
  */
int usbh_ctrl_xfer(UDEV_T *udev, uint8_t bmRequestType, uint8_t bRequest, uint16_t wValue, uint16_t wIndex,
                   uint16_t wLength, uint8_t *buff, uint32_t *xfer_len, uint32_t timeout)
{
    UTR_T      *utr;
    uint32_t   t0, timeout_tick;
    int        status;

    *xfer_len = 0;

    //if (check_device(udev))
    //    return USBH_ERR_INVALID_PARAM;

    utr = alloc_utr(udev);
    if (utr == NULL)
        return USBH_ERR_MEMORY_OUT;

    utr->setup.bmRequestType = bmRequestType;
    utr->setup.bRequest   = bRequest;
    utr->setup.wValue     = wValue;
    utr->setup.wIndex     = wIndex;
    utr->setup.wLength    = wLength;

    utr->buff = buff;
    utr->data_len = wLength;
    utr->bIsTransferDone = 0;
    status = udev->hc_driver->ctrl_xfer(utr);
    if (status < 0)
    {
        udev->ep0.hw_pipe = NULL;
        free_utr(utr);
        return status;
    }

    timeout_tick = usbh_tick_from_millisecond(timeout);
    t0 = usbh_get_ticks();
    while (utr->bIsTransferDone == 0)
    {
        if (usbh_get_ticks() - t0 > timeout_tick)
        {
            usbh_quit_utr(utr);
            free_utr(utr);
            udev->ep0.hw_pipe = NULL;
            return USBH_ERR_TIMEOUT;
        }
    }

    status = utr->status;

    if (status == 0)
    {
        *xfer_len = utr->xfer_len;
    }
    free_utr(utr);

    return status;
}

/**
  * @brief    Execute a bulk transfer request. This function will return immediately after
  *           issued the bulk transfer. USB stack will later call back utr->func() once the bulk
  *           transfer was done or aborted.
  * @param[in]  utr    The bulk transfer request.
  * @retval   0     Transfer success
  * @retval   < 0   Failed. Refer to error code definitions.
  */
int usbh_bulk_xfer(UTR_T *utr)
{
    return utr->udev->hc_driver->bulk_xfer(utr);
}

/**
  * @brief    Execute an interrupt transfer request. This function will return immediately after
  *           issued the interrupt transfer. USB stack will later call back utr->func() once the
  *           interrupt transfer was done or aborted.
  * @param[in]  utr    The interrupt transfer request.
  * @retval   0     Transfer success
  * @retval   < 0   Failed. Refer to error code definitions.
  */
int usbh_int_xfer(UTR_T *utr)
{
    return utr->udev->hc_driver->int_xfer(utr);
}


