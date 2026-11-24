/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-07     RealThread   the first version
 */

#include "drv_usbh_pipe.h"

#if defined(BSP_USING_USB) && defined(RT_USING_USB_HOST)

static uint16_t usbh_freepipe_get(usb_core_driver *pudev);

/*!
    \brief      create a pipe
    \param[in]  pudev: pointer to usb core instance
    \param[in]  pp_num: pipe number
    \param[in]  udev: USB device
    \param[in]  ep_type: endpoint type
    \param[in]  ep_mpl: endpoint max packet length
    \param[out] none
    \retval     operation status
*/
uint8_t usbh_pipe_create(usb_core_driver *pudev,
                         uint8_t dev_addr,
                         uint8_t dev_speed,
                         uint8_t pp_num,
                         uint8_t ep_num,
                         uint8_t ep_type,
                         uint16_t ep_mpl)
{
    usb_pipe *pp = &pudev->host.pipe[pp_num];

    pp->dev_addr = dev_addr;
    pp->dev_speed = dev_speed;
    pp->ep.num = ep_num & 0x7FU;
    pp->ep.type = ep_type;
    pp->ep.mps = ep_mpl;

    if (((USB_EPTYPE_BULK == pp->ep.type) || (USB_EPTYPE_CTRL == pp->ep.type)))
    {
        pp->supp_ping = (uint8_t)(pp->dev_speed == PORT_SPEED_HIGH);
    }

    if (0x80U == (ep_num & 0x80U))
    {
        pp->ep.dir = 1;
    }
    else
    {
        pp->ep.dir = 0;
    }

    usb_pipe_init(pudev, pp_num);

    return HC_OK;
}

/*!
    \brief      modify a pipe
    \param[in]  pudev: pointer to usb core instance
    \param[in]  pp_num: pipe number
    \param[in]  dev_addr: device address
    \param[in]  dev_speed: device speed
    \param[in]  ep_type: endpoint type
    \param[in]  ep_mpl: endpoint max packet length
    \param[out] none
    \retval     operation status
*/
uint8_t usbh_pipe_update(usb_core_driver *pudev,
                         uint8_t pp_num,
                         uint8_t dev_addr,
                         uint32_t dev_speed,
                         uint16_t ep_mpl)
{
    usb_pipe *pp = &pudev->host.pipe[pp_num];

    if ((pp->dev_addr != dev_addr) && (dev_addr))
    {
        pp->dev_addr = dev_addr;
    }

    if ((pp->dev_speed != dev_speed) && (dev_speed))
    {
        pp->dev_speed = dev_speed;
    }

    if ((pp->ep.mps != ep_mpl) && (ep_mpl))
    {
        pp->ep.mps = ep_mpl;
    }

    usb_pipe_init(pudev, pp_num);

    return HC_OK;
}

/*!
    \brief      allocate a new pipe
    \param[in]  pudev: pointer to usb core instance
    \param[in]  ep_addr: endpoint address
    \param[out] none
    \retval     operation status
*/
uint8_t usbh_pipe_allocate(usb_core_driver *pudev, uint8_t ep_addr)
{
    uint16_t pp_num = usbh_freepipe_get(pudev);

    if (HC_ERROR != pp_num)
    {
        pudev->host.pipe[pp_num].in_used = 1U;
        pudev->host.pipe[pp_num].ep.dir = EP_DIR(ep_addr);
        pudev->host.pipe[pp_num].ep.num = EP_ID(ep_addr);
    }

    return pp_num;
}

/*!
    \brief      free a pipe
    \param[in]  pudev: pointer to usb core instance
    \param[in]  pp_num: pipe number
    \param[out] none
    \retval     operation status
*/
uint8_t usbh_pipe_free(usb_core_driver *pudev, uint8_t pp_num)
{
    if (pp_num < HC_MAX)
    {
        pudev->host.pipe[pp_num].in_used = 0U;
    }

    return USBH_OK;
}

/*!
    \brief      delete all USB host pipe
    \param[in]  pudev: pointer to usb core instance
    \param[out] none
    \retval     operation status
*/
uint8_t usbh_pipe_delete(usb_core_driver *pudev)
{
    uint8_t pp_num = 0U;

    for (pp_num = 2U; pp_num < HC_MAX; pp_num++)
    {
        pudev->host.pipe[pp_num] = (usb_pipe){ 0 };
    }

    return USBH_OK;
}

/*!
    \brief      get a free pipe number for allocation
    \param[in]  pudev: pointer to usb core instance
    \param[out] none
    \retval     operation status
*/
static uint16_t usbh_freepipe_get(usb_core_driver *pudev)
{
    uint8_t pp_num = 0U;

    for (pp_num = 0U; pp_num < HC_MAX; pp_num++)
    {
        if (pudev->host.pipe[pp_num].in_used == 0U)
        {
            return pp_num;
        }
    }

    return HC_ERROR;
}

#endif /* BSP_USING_USB && RT_USING_USB_HOST */
