/*!
    \file  usbh_core.c
    \brief USB host core state machine driver

    \version 2019-6-5, V1.0.0, firmware for GD32 USBFS&USBHS
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "drv_usb_hw.h"
#include "usbh_pipe.h"
#include "usbh_enum.h"
#include "usbh_core.h"
#include "drv_usbh_int.h"

uint8_t usbh_sof (usb_core_driver *pudev);

usbh_int_cb usbh_int_op = 
{
    usbh_sof
};

usbh_int_cb *usbh_int_fop = &usbh_int_op;

static usbh_status usbh_enum_task (usb_core_driver *pudev, usbh_host *puhost);

/*!
    \brief      USB SOF callback function from the interrupt
    \param[in]  pudev: pointer to usb core instance
    \param[out] none
    \retval     operation status
*/
uint8_t usbh_sof (usb_core_driver *pudev)
{
    /* this callback could be used to implement a scheduler process */
    return 0U;
}

/*!
    \brief      USB host stack initializations
    \param[in]  pudev: pointer to usb core instance
    \param[in]  core: USBFS core or USBHS core
    \param[in]  puhost: pointer to USB host
    \param[out] none
    \retval     operation status
*/
void usbh_init (usb_core_driver *pudev, usb_core_enum core, usbh_host *puhost)
{
    uint8_t i = 0U;

    /* host de-initializations */
    usbh_deinit(pudev, puhost);

    pudev->host.connect_status = 0U;

    for (i = 0U; i < USBFS_MAX_TX_FIFOS; i++) {
        pudev->host.pipe[i].err_count = 0U;
        pudev->host.pipe[i].pp_status = PIPE_IDLE;
        pudev->host.backup_xfercount[i] = 0U;
    }

    pudev->host.pipe[0].ep.mps = 8U;

    usb_basic_init (&pudev->bp, &pudev->regs, core);

#ifndef DUAL_ROLE_MODE_ENABLED

    usb_core_init (pudev->bp, &pudev->regs);

    usb_host_init (pudev);

#endif /* DUAL_ROLE_MODE_ENABLED */

    /* upon init call usr call back */
    puhost->usr_cb->dev_init();
}

/*!
    \brief      de-initialize USB host
    \param[in]  pudev: pointer to usb core instance
    \param[in]  puhost: pointer to USB host
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_deinit(usb_core_driver *pudev, usbh_host *puhost)
{
    /* software init */
    puhost->cur_state = HOST_DEFAULT;
    puhost->backup_state = HOST_DEFAULT;
    puhost->enum_state = ENUM_DEFAULT;

    puhost->control.ctl_state = CTL_IDLE;
    puhost->control.max_len = USB_FS_EP0_MAX_LEN;

    puhost->dev_prop.addr = USBH_DEV_ADDR_DEFAULT;
    puhost->dev_prop.speed = PORT_SPEED_FULL;

    usbh_pipe_free(pudev, puhost->control.pipe_in_num);
    usbh_pipe_free(pudev, puhost->control.pipe_out_num);

    return USBH_OK;
}

/*!
    \brief      USB host core main state machine process
    \param[in]  pudev: pointer to usb core instance
    \param[in]  puhost: pointer to USB host
    \param[out] none
    \retval     none
*/
void usbh_core_task (usb_core_driver *pudev, usbh_host *puhost)
{
    volatile usbh_status status = USBH_FAIL;

    /* check for host port events */
    if (((0U == pudev->host.connect_status) || (0U == pudev->host.port_enabled)) && (HOST_DEFAULT != puhost->cur_state)) {
        if (puhost->cur_state != HOST_DEV_DETACHED) {
            puhost->cur_state = HOST_DEV_DETACHED;
        }
    }

    switch (puhost->cur_state) {
        case HOST_DEFAULT:
            if (pudev->host.connect_status) {
                puhost->cur_state = HOST_DETECT_DEV_SPEED;

                usb_mdelay (100U);
               // usb_mdelay (2U);
                usb_port_reset (pudev);

                puhost->usr_cb->dev_reset();
            }
            break;

        case HOST_DETECT_DEV_SPEED:
            if (pudev->host.port_enabled) {
                puhost->cur_state = HOST_DEV_ATTACHED;
                puhost->dev_prop.speed = usb_curspeed_get (pudev);
                puhost->usr_cb->dev_speed_detected(puhost->dev_prop.speed);

                usb_mdelay (50U);               
            }
            break;

        case HOST_DEV_ATTACHED:
            puhost->usr_cb->dev_attach();
            puhost->control.pipe_out_num = usbh_pipe_allocate(pudev, 0x00U);
            puhost->control.pipe_in_num = usbh_pipe_allocate(pudev, 0x80U);

            /* reset USB device */
            usb_port_reset (pudev);

            /* open IN control pipe */
            usbh_pipe_create (pudev,
                              &puhost->dev_prop,
                              puhost->control.pipe_in_num,
                              USB_EPTYPE_CTRL,
                              puhost->control.max_len);

            /* open OUT control pipe */
            usbh_pipe_create (pudev,
                              &puhost->dev_prop,
                              puhost->control.pipe_out_num,
                              USB_EPTYPE_CTRL,
                              puhost->control.max_len);

            puhost->cur_state = HOST_ENUM;
            break;

        case HOST_ENUM:

            /* check for enumeration status */
            if (USBH_OK == usbh_enum_task (pudev, puhost)) {
                /* the function shall return USBH_OK when full enumeration is complete */

                /* user callback for end of device basic enumeration */
                puhost->usr_cb->dev_enumerated();
                puhost->cur_state = HOST_USER_INPUT;
            }
            break;

        case HOST_USER_INPUT:
            /* the function should return user response true to move to class state */
            if (USBH_USER_RESP_OK == puhost->usr_cb->dev_user_input()) {
                if ((USBH_OK == puhost->class_cb->class_init(pudev, puhost))) {
                    puhost->cur_state = HOST_CLASS_ENUM;
                }
            }
            break;

        case HOST_CLASS_ENUM:
            /* process class standard contol requests state machine */
            status = puhost->class_cb->class_requests(pudev, puhost);

            if (USBH_OK == status) {
                puhost->cur_state = HOST_CLASS_HANDLER;
            } else {
                usbh_error_handler (puhost, status);
            }
            break;

        case HOST_CLASS_HANDLER:
            /* process class state machine */
            status = puhost->class_cb->class_machine(pudev, puhost);

            usbh_error_handler (puhost, status);
            break;

        case HOST_SUSPENDED:
            break;

        case HOST_ERROR:
            /* re-initilaize host for new enumeration */
            usbh_deinit (pudev, puhost);
            puhost->usr_cb->dev_deinit();
            puhost->class_cb->class_deinit(pudev, puhost);
            break;

        case HOST_DEV_DETACHED:
            /* manage user disconnect operations*/
            puhost->usr_cb->dev_detach();

            /* re-initilaize host for new enumeration */
            usbh_deinit(pudev, puhost);
            puhost->usr_cb->dev_deinit();
            puhost->class_cb->class_deinit(pudev, puhost);
            usbh_pipe_delete(pudev);
            puhost->cur_state = HOST_DEFAULT;
            break;

        default:
            break;
    }
}

/*!
    \brief      handle the error on USB host side
    \param[in]  puhost: pointer to USB host
    \param[in]  err_type: type of error or busy/OK state
    \param[out] none
    \retval     none
*/
void usbh_error_handler (usbh_host *puhost, usbh_status err_type)
{
    /* error unrecovered or not supported device speed */
    if ((USBH_SPEED_UNKNOWN_ERROR == err_type) || (USBH_UNRECOVERED_ERROR == err_type)) {
        puhost->usr_cb->dev_error();

        puhost->cur_state = HOST_ERROR;
    } else if (USBH_APPLY_DEINIT == err_type) {
        puhost->cur_state = HOST_ERROR;

        /* user callback for initalization */
        puhost->usr_cb->dev_init();
    }
}

/*!
    \brief      handle the USB enumeration task
    \param[in]  pudev: pointer to selected USB device
    \param[in]  puhost: pointer to host
    \param[out] none
    \retval     none
*/
static usbh_status usbh_enum_task (usb_core_driver *pudev, usbh_host *puhost)
{
    uint8_t str_buf[64];

    usbh_status status = USBH_BUSY;

    static uint8_t index_mfc_str = 0U, index_prod_str = 0U, index_serial_str = 0U;

    switch (puhost->enum_state) {
        case ENUM_DEFAULT:
            /* get device descriptor for only 1st 8 bytes : to get ep0 maxpacketsize */
            if (USBH_OK == usbh_devdesc_get (pudev, puhost, 8U)) {

                puhost->control.max_len = puhost->dev_prop.dev_desc.bMaxPacketSize0;

                /* issue reset */
                usb_port_reset (pudev);

                /* modify control channels configuration for maximum packet size */
                usbh_pipe_update (pudev,
                                  puhost->control.pipe_out_num,
                                  0U, 0U,
                                  puhost->control.max_len);

                usbh_pipe_update (pudev,
                                  puhost->control.pipe_in_num,
                                  0U, 0U,
                                  puhost->control.max_len);

                puhost->enum_state = ENUM_GET_DEV_DESC;

            }
            break;

        case ENUM_GET_DEV_DESC:
            /* get full device descriptor */
            if (USBH_OK == usbh_devdesc_get (pudev, puhost, USB_DEV_DESC_LEN)) {
                puhost->usr_cb->dev_devdesc_assigned(&puhost->dev_prop.dev_desc);

                index_mfc_str = puhost->dev_prop.dev_desc.iManufacturer;
                index_prod_str = puhost->dev_prop.dev_desc.iProduct;
                index_serial_str = puhost->dev_prop.dev_desc.iSerialNumber;

                puhost->enum_state = ENUM_SET_ADDR;
            }
            break;

        case ENUM_SET_ADDR: 
            /* set address */
            if (USBH_OK == usbh_setaddress (pudev, puhost, USBH_DEV_ADDR)) {
                usb_mdelay (2);

                puhost->dev_prop.addr = USBH_DEV_ADDR;

                /* user callback for device address assigned */
                puhost->usr_cb->dev_address_set();

                /* modify control channels to update device address */
                usbh_pipe_update (pudev,
                                  puhost->control.pipe_in_num,
                                  puhost->dev_prop.addr,
                                  0U, 0U);

                usbh_pipe_update (pudev,
                                  puhost->control.pipe_out_num,
                                  puhost->dev_prop.addr,
                                  0U, 0U);

                puhost->enum_state = ENUM_GET_CFG_DESC;
            }
            break;

        case ENUM_GET_CFG_DESC:
            /* get standard configuration descriptor */
            if (USBH_OK == usbh_cfgdesc_get (pudev, puhost, USB_CFG_DESC_LEN)) {
                puhost->enum_state = ENUM_GET_CFG_DESC_SET;
            }
            break;

        case ENUM_GET_CFG_DESC_SET:
            /* get full config descriptor (config, interface, endpoints) */
            if (USBH_OK == usbh_cfgdesc_get (pudev, puhost, puhost->dev_prop.cfg_desc.wTotalLength)) {
                /* user callback for configuration descriptors available */
                puhost->usr_cb->dev_cfgdesc_assigned (&puhost->dev_prop.cfg_desc,
                                                       puhost->dev_prop.itf_desc,
                                                       puhost->dev_prop.ep_desc[0]);

                puhost->enum_state = ENUM_GET_STR_DESC;
            }
            break;

        case ENUM_GET_STR_DESC:
            if (index_mfc_str) {
                if (USBH_OK == usbh_strdesc_get (pudev, 
                                                 puhost, 
                                                 puhost->dev_prop.dev_desc.iManufacturer, 
                                                 str_buf,
                                                 0xFFU)) {
                    /* user callback for manufacturing string */
                    puhost->usr_cb->dev_mfc_str(str_buf);

                    index_mfc_str = 0U;
                }
            } else {
                if (index_prod_str) {
                    /* check that product string is available */
                    if (USBH_OK == usbh_strdesc_get (pudev, 
                                                     puhost, 
                                                     puhost->dev_prop.dev_desc.iProduct, 
                                                     str_buf, 
                                                     0xFFU)) {
                        puhost->usr_cb->dev_prod_str(str_buf);

                        index_prod_str = 0U;
                    }
                } else {
                    if (index_serial_str) {
                        if (USBH_OK == usbh_strdesc_get (pudev, 
                                                         puhost, 
                                                         puhost->dev_prop.dev_desc.iSerialNumber,
                                                         str_buf, 
                                                         0xFFU)) {
                            puhost->usr_cb->dev_seral_str(str_buf);
                            puhost->enum_state = ENUM_SET_CONFIGURATION;

                            index_serial_str = 0U;
                        }
                    } else {
                        puhost->enum_state = ENUM_SET_CONFIGURATION;
                    }
                }
            }
            break;

        case ENUM_SET_CONFIGURATION:
            if (USBH_OK == usbh_setcfg (pudev, 
                                        puhost,
                                        puhost->dev_prop.cfg_desc.bConfigurationValue)) {
                puhost->enum_state = ENUM_DEV_CONFIGURED;
            }
            break;

        case ENUM_DEV_CONFIGURED:
            status = USBH_OK;
            break;

        default:
            break;
    }

    return status;
}
