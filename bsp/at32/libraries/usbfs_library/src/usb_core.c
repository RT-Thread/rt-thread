/**
  **************************************************************************
  * @file     usb_core.c
  * @brief    usb driver
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
#include "usb_core.h"

/** @defgroup USB_drivers_core
  * @brief usb global drivers core
  * @{
  */

/** @defgroup USB_core_private_functions
  * @{
  */

usb_sts_type usb_core_config(otg_core_type *udev, uint8_t core_id);

/**
  * @brief  usb core config
  * @param  otgdev: to the structure of otg_core_type
  * @param  core_id: usb core id number (USB_FULL_SPEED_CORE_ID)
  * @retval usb_sts_type
  */
usb_sts_type usb_core_config(otg_core_type *otgdev, uint8_t core_id)
{
  /* set usb speed and core id */
  otgdev->cfg.speed = core_id;
  otgdev->cfg.core_id = core_id;

  /* default sof out and vbus ignore */
  otgdev->cfg.sof_out = FALSE;
  otgdev->cfg.vbusig = FALSE;

  /* set max size */
  otgdev->cfg.max_size = 64;

  /* set support number of channel and endpoint */
#ifdef USE_OTG_HOST_MODE
  otgdev->cfg.hc_num = USB_HOST_CHANNEL_NUM;
#endif
#ifdef USE_OTG_DEVICE_MODE
  otgdev->cfg.ept_num = USB_EPT_MAX_NUM;
#endif
  otgdev->cfg.fifo_size = OTG_FIFO_SIZE;
  if(core_id == USB_FULL_SPEED_CORE_ID)
  {
    otgdev->cfg.phy_itface = 2;
  }
#ifdef USB_SOF_OUTPUT_ENABLE
  otgdev->cfg.sof_out = TRUE;
#endif

#ifdef USB_VBUS_IGNORE
  otgdev->cfg.vbusig = TRUE;
#endif

  return USB_OK;
}

#ifdef USE_OTG_DEVICE_MODE
/**
  * @brief  usb device initialization
  * @param  otgdev: to the structure of otg_core_type
  * @param  core_id: usb core id number (USB_FULL_SPEED_CORE_ID)
  * @param  usb_id: select use OTG1 or OTG2
  *         this parameter can be one of the following values:
  *         - USB_OTG1_ID
  *         - USB_OTG2_ID
  * @param  dev_handler: usb class callback handler
  * @param  desc_handler: device config callback handler
  * @retval usb_sts_type
  */
usb_sts_type usbd_init(otg_core_type *otgdev,
                  uint8_t core_id, uint8_t usb_id)
{
  usb_sts_type usb_sts = USB_OK;

  /* select use OTG1 or OTG2 */
  otgdev->usb_reg = usb_global_select_core(usb_id);

  /* usb device core config */
  usb_core_config(otgdev, core_id);

  if(otgdev->cfg.sof_out)
  {
    otgdev->usb_reg->gccfg_bit.sofouten = TRUE;
  }

  if(otgdev->cfg.vbusig)
  {
    otgdev->usb_reg->gccfg_bit.vbusig = TRUE;
  }

  /* usb device core init */
  usbd_core_init(&(otgdev->dev), otgdev->usb_reg,
                core_id);

  return usb_sts;
}
#endif

#ifdef USE_OTG_HOST_MODE

/**
  * @brief  usb host initialization.
  * @param  otgdev: to the structure of otg_core_type
  * @param  core_id: usb core id number (USB_FULL_SPEED_CORE_ID)
  * @param  usb_id: select use OTG1 or OTG2
  *         this parameter can be one of the following values:
  *         - USB_OTG1_ID
  *         - USB_OTG2_ID
  * @param  class_handler: usb class callback handler
  * @param  user_handler: user callback handler
  * @retval usb_sts_type
  */
usb_sts_type usbh_init(otg_core_type *otgdev,
                  uint8_t core_id, uint8_t usb_id)
{
  usb_sts_type status = USB_OK;

  /* select use otg1 or otg2 */
  otgdev->usb_reg = usb_global_select_core(usb_id);

  /* usb core config */
  usb_core_config(otgdev, core_id);

  if(otgdev->cfg.sof_out)
  {
    otgdev->usb_reg->gccfg_bit.sofouten = TRUE;
  }

  if(otgdev->cfg.vbusig)
  {
    otgdev->usb_reg->gccfg_bit.vbusig = TRUE;
  }

  /* usb host core init */
  usbh_core_init(&otgdev->host, otgdev->usb_reg,
                core_id);

  return status;
}
#endif

/**
  * @}
  */

/**
  * @}
  */

