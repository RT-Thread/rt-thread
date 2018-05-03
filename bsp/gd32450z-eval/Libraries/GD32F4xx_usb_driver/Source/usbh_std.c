/*!
    \file  usbh_std.c
    \brief USB 2.0 standard function definition
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.1, firmware for GD32F4xx
*/

#include "usbh_core.h"
#include "usbh_usr.h"
#include "usbh_std.h"
#include "usbh_ctrl.h"

uint8_t local_buffer[64];
uint8_t usbh_cfg_desc[512];
uint8_t enum_polling_handle_flag = 0U;

static void enum_idle_handle                       (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void enum_get_full_dev_desc_handle          (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void enum_set_addr_handle                   (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void enum_get_cfg_desc_handle               (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void enum_get_full_cfg_desc_handle          (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void enum_get_mfc_string_desc_handle        (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void enum_get_product_string_desc_handle    (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void enum_get_serialnum_string_desc_handle  (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void enum_set_configuration_handle          (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void enum_dev_configured_handle             (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);

/* the enumeration state handle function array */
void (*enum_state_handle[]) (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate) =
{
    enum_idle_handle,
    enum_set_addr_handle,
    enum_get_full_dev_desc_handle,
    enum_get_cfg_desc_handle,
    enum_get_full_cfg_desc_handle,
    enum_get_mfc_string_desc_handle,
    enum_get_product_string_desc_handle,
    enum_get_serialnum_string_desc_handle,
    enum_set_configuration_handle,
    enum_dev_configured_handle,
};

/* the enumeration state handle table */
state_table_struct enum_handle_table[ENUM_HANDLE_TABLE_SIZE] = 
{
    /* the current state             the current event                     the next state                   the event function */
    {ENUM_IDLE,                      ENUM_EVENT_SET_ADDR,                  ENUM_SET_ADDR,                   only_state_move     },
    {ENUM_SET_ADDR,                  ENUN_EVENT_GET_FULL_DEV_DESC,         ENUM_GET_FULL_DEV_DESC,          only_state_move     },
    {ENUM_GET_FULL_DEV_DESC,         ENUN_EVENT_GET_CFG_DESC,              ENUM_GET_CFG_DESC,               only_state_move     },
    {ENUM_GET_CFG_DESC,              ENUN_EVENT_GET_FULL_CFG_DESC,         ENUM_GET_FULL_CFG_DESC,          only_state_move     },
    {ENUM_GET_FULL_CFG_DESC,         ENUN_EVENT_GET_MFC_STRING_DESC,       ENUM_GET_MFC_STRING_DESC,        only_state_move     },
    {ENUM_GET_MFC_STRING_DESC,       ENUN_EVENT_GET_PRODUCT_STRING_DESC,   ENUM_GET_PRODUCT_STRING_DESC,    only_state_move     },
    {ENUM_GET_PRODUCT_STRING_DESC,   ENUN_EVENT_GET_SERIALNUM_STRING_DESC, ENUM_GET_SERIALNUM_STRING_DESC,  only_state_move     },
    {ENUM_GET_SERIALNUM_STRING_DESC, ENUN_EVENT_SET_CONFIGURATION,         ENUM_SET_CONFIGURATION,          only_state_move     },
    {ENUM_SET_CONFIGURATION,         ENUN_EVENT_DEV_CONFIGURED,            ENUM_DEV_CONFIGURED,             only_state_move     },
    {ENUM_DEV_CONFIGURED,            GO_TO_UP_STATE_EVENT,                 UP_STATE,                        goto_up_state_fun   },
};

/*!
    \brief      the polling function of enumeration state
    \param[in]  pudev: pointer to USB device
    \param[in]  puhost: pointer to USB host
    \param[in]  pustate: pointer to USB state driver
    \param[out] none
    \retval     usb host status
*/
usbh_status_enum enum_state_polling_fun (usb_core_handle_struct *pudev, usbh_host_struct *puhost, void *pustate)
{
    usbh_status_enum exe_state = USBH_BUSY;
    usbh_state_handle_struct *p_state;
    p_state = (usbh_state_handle_struct *)pustate;

    if (0U == enum_polling_handle_flag) {
        enum_polling_handle_flag = 1U;
        scd_table_push(p_state);
        scd_state_move(p_state, ENUM_IDLE);
    }
    
    /* start the enumeration state handle */
    scd_begin(p_state,ENUM_FSM_ID);
    
    if (0U == p_state->usbh_current_state_stack_top) {
        enum_state_handle[p_state->usbh_current_state](pudev, puhost, p_state);
    } else {
        enum_state_handle[p_state->stack[1].state](pudev, puhost, p_state);
    }

    /* determine the enumeration whether to complete  */
    if (ENUM_DEV_CONFIGURED == puhost->usbh_backup_state.enum_backup_state) {
        puhost->usbh_backup_state.enum_backup_state = ENUM_IDLE;
        enum_polling_handle_flag = 0U;
        exe_state = USBH_OK;
    }

    return exe_state;
}

/*!
    \brief      the handle function of ENUM_IDLE state
    \param[in]  pudev: pointer to USB device
    \param[in]  puhost: pointer to USB host
    \param[in]  pustate: pointer to USB state driver
    \param[out] none
    \retval     none
*/
static void enum_idle_handle (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate)
{
    puhost->usbh_backup_state.enum_backup_state = ENUM_IDLE;

    if (CTRL_IDLE == puhost->usbh_backup_state.ctrl_backup_state) {
        usbh_enum_desc_get(pudev, 
                           puhost, 
                           pudev->host.rx_buffer, 
                           USB_REQTYPE_DEVICE | USB_STANDARD_REQ, 
                           USB_DEVDESC, 
                           8U);
        if ((void *)0 != pudev->mdelay) {
            pudev->mdelay(100U);
        }
    }

    if (USBH_OK == ctrl_state_polling_fun(pudev, puhost, pustate)) {
        usbh_device_desc_parse(&puhost->device.dev_desc, pudev->host.rx_buffer, 8U);
        puhost->control.ep0_size = puhost->device.dev_desc.bMaxPacketSize0;

        /* issue reset */
        usb_port_reset(pudev);

        /* modify control channels configuration for maxpacket size */
        usbh_channel_modify (pudev,
                             puhost->control.hc_out_num,
                             0U,
                             0U,
                             0U,
                             (uint16_t)puhost->control.ep0_size);

        usbh_channel_modify (pudev,
                             puhost->control.hc_in_num,
                             0U,
                             0U,
                             0U,
                             (uint16_t)puhost->control.ep0_size);

        scd_event_handle(pudev, 
                         puhost, 
                         pustate, 
                         ENUM_EVENT_SET_ADDR, 
                         pustate->usbh_current_state);
    }
}

/*!
    \brief      the handle function of ENUM_GET_FULL_DEV_DESC state
    \param[in]  pudev: pointer to USB device
    \param[in]  puhost: pointer to USB host
    \param[in]  pustate: pointer to USB state driver
    \param[out] none
    \retval     none
*/
static void enum_get_full_dev_desc_handle (usb_core_handle_struct *pudev, 
                                           usbh_host_struct *puhost, 
                                           usbh_state_handle_struct *pustate)
{
    puhost->usbh_backup_state.enum_backup_state = ENUM_GET_FULL_DEV_DESC;

    if (CTRL_IDLE == puhost->usbh_backup_state.ctrl_backup_state) {
        usbh_enum_desc_get(pudev, 
                           puhost, 
                           pudev->host.rx_buffer, 
                           USB_REQTYPE_DEVICE | USB_STANDARD_REQ, 
                           USB_DEVDESC, 
                           USB_DEVDESC_SIZE);
    }
    
    if(USBH_OK == ctrl_state_polling_fun(pudev, puhost, pustate)){
        usbh_device_desc_parse(&puhost->device.dev_desc, pudev->host.rx_buffer, USB_DEVDESC_SIZE);
        puhost->usr_cb->device_desc_available(&puhost->device.dev_desc);

        scd_event_handle(pudev, 
                         puhost, 
                         pustate, 
                         ENUN_EVENT_GET_CFG_DESC, 
                         pustate->usbh_current_state);
    }
}

/*!
    \brief      the handle function of ENUM_SET_ADDR state
    \param[in]  pudev: pointer to USB device
    \param[in]  puhost: pointer to USB host
    \param[in]  pustate: pointer to USB state driver
    \param[out] none
    \retval     none
*/
static void enum_set_addr_handle (usb_core_handle_struct *pudev, 
                                  usbh_host_struct *puhost, 
                                  usbh_state_handle_struct *pustate)
{
    puhost->usbh_backup_state.enum_backup_state = ENUM_SET_ADDR;

    if (CTRL_IDLE == puhost->usbh_backup_state.ctrl_backup_state) {
        usbh_enum_addr_set(pudev, puhost,USBH_DEVICE_ADDRESS);
        if ((void *)0 != pudev->mdelay) {
            pudev->mdelay(100U);
        }
    }
    
    if (USBH_OK == ctrl_state_polling_fun(pudev, puhost, pustate)) {
        if ((void *)0 != pudev->mdelay) {
            pudev->mdelay(2U);
        }
        puhost->device.address = USBH_DEVICE_ADDRESS;

        /* user callback for device address assigned */
        puhost->usr_cb->device_address_set();

        /* modify control channels to update device address */
        usbh_channel_modify (pudev,
                             puhost->control.hc_in_num,
                             puhost->device.address,
                             0U,
                             0U,
                             0U);

        usbh_channel_modify (pudev,
                             puhost->control.hc_out_num,
                             puhost->device.address,
                             0U,
                             0U,
                             0U);

        scd_event_handle(pudev, 
                         puhost, 
                         pustate, 
                         ENUN_EVENT_GET_FULL_DEV_DESC, 
                         pustate->usbh_current_state);
    }
}

/*!
    \brief      the handle function of ENUM_GET_CFG_DESC state
    \param[in]  pudev: pointer to USB device
    \param[in]  puhost: pointer to USB host
    \param[in]  pustate: pointer to USB state driver
    \param[out] none
    \retval     none
*/
static void enum_get_cfg_desc_handle (usb_core_handle_struct *pudev, 
                                      usbh_host_struct *puhost, 
                                      usbh_state_handle_struct *pustate)
{
    uint16_t index = 0U;

    puhost->usbh_backup_state.enum_backup_state = ENUM_GET_CFG_DESC;

    if (CTRL_IDLE == puhost->usbh_backup_state.ctrl_backup_state) {
        usbh_enum_desc_get(pudev, 
                           puhost, 
                           pudev->host.rx_buffer, 
                           USB_REQTYPE_DEVICE | USB_STANDARD_REQ, 
                           USB_CFGDESC, 
                           USB_CFGDESC_SIZE);
    }
    
    if (USBH_OK == ctrl_state_polling_fun(pudev, puhost, pustate)) {
        /* save configuration descriptor for class parsing usage */
        for (; index < USB_CFGDESC_SIZE; index ++) {
            usbh_cfg_desc[index] = pudev->host.rx_buffer[index];
        }

        /* commands successfully sent and response received */
        usbh_cfg_desc_parse (&puhost->device.cfg_desc,
                              puhost->device.itf_desc,
                              puhost->device.ep_desc, 
                              pudev->host.rx_buffer,
                              USB_CFGDESC_SIZE);

        scd_event_handle(pudev, 
                         puhost, 
                         pustate, 
                         ENUN_EVENT_GET_FULL_CFG_DESC, 
                         pustate->usbh_current_state);
    }
}

/*!
    \brief      the handle function of ENUM_GET_FULL_CFG_DESC state
    \param[in]  pudev: pointer to USB device
    \param[in]  puhost: pointer to USB host
    \param[in]  pustate: pointer to USB state driver
    \param[out] none
    \retval     none
*/
static void enum_get_full_cfg_desc_handle (usb_core_handle_struct *pudev, 
                                           usbh_host_struct *puhost, 
                                           usbh_state_handle_struct *pustate)
{

    uint16_t index = 0U;

    puhost->usbh_backup_state.enum_backup_state = ENUM_GET_FULL_CFG_DESC;

    if (CTRL_IDLE == puhost->usbh_backup_state.ctrl_backup_state) {
        usbh_enum_desc_get (pudev, puhost, pudev->host.rx_buffer, 
                            USB_REQTYPE_DEVICE | USB_STANDARD_REQ, 
                            USB_CFGDESC, puhost->device.cfg_desc.wTotalLength);
    }

    
    if (USBH_OK == ctrl_state_polling_fun(pudev, puhost, pustate)) {
        /* save configuration descriptor for class parsing usage */
        for (; index < puhost->device.cfg_desc.wTotalLength; index ++) {
            usbh_cfg_desc[index] = pudev->host.rx_buffer[index];
        }

        /* commands successfully sent and response received */
        usbh_cfg_desc_parse (&puhost->device.cfg_desc, 
                              puhost->device.itf_desc, 
                              puhost->device.ep_desc, 
                              pudev->host.rx_buffer, 
                              puhost->device.cfg_desc.wTotalLength);

        /* User callback for configuration descriptors available */
        puhost->usr_cb->configuration_desc_available(&puhost->device.cfg_desc,
                                                      puhost->device.itf_desc,
                                                      puhost->device.ep_desc[0]);

        scd_event_handle(pudev, 
                         puhost, 
                         pustate, 
                         ENUN_EVENT_GET_MFC_STRING_DESC, 
                         pustate->usbh_current_state);
    }
}

/*!
    \brief      the handle function of ENUM_GET_MFC_STRING_DESC state
    \param[in]  pudev: pointer to USB device
    \param[in]  puhost: pointer to USB host
    \param[in]  pustate: pointer to USB state driver
    \param[out] none
    \retval     none
*/
static void enum_get_mfc_string_desc_handle (usb_core_handle_struct *pudev, 
                                             usbh_host_struct *puhost, 
                                             usbh_state_handle_struct *pustate)
{
    puhost->usbh_backup_state.enum_backup_state = ENUM_GET_MFC_STRING_DESC;

    if (0U != puhost->device.dev_desc.iManufacturer) {
        if(CTRL_IDLE == puhost->usbh_backup_state.ctrl_backup_state) {
            usbh_enum_desc_get(pudev, 
                               puhost, 
                               pudev->host.rx_buffer, 
                               USB_REQTYPE_DEVICE | USB_STANDARD_REQ, 
                               USB_STRDESC | puhost->device.dev_desc.iManufacturer,
                               0xffU);
        }
        
        if (USBH_OK == ctrl_state_polling_fun(pudev, puhost, pustate)) {
            usbh_string_desc_parse(pudev->host.rx_buffer, local_buffer, 0xffU);
            puhost->usr_cb->manufacturer_string(local_buffer);
            
            scd_event_handle(pudev, 
                             puhost, 
                             pustate, 
                             ENUN_EVENT_GET_PRODUCT_STRING_DESC, 
                             pustate->usbh_current_state);
        }
    } else {
        puhost->usr_cb->manufacturer_string("N/A");
        scd_state_move((usbh_state_handle_struct *)pustate, ENUM_GET_PRODUCT_STRING_DESC);
    }
}

/*!
    \brief      the handle function of ENUM_GET_PRODUCT_STRING_DESC state
    \param[in]  pudev: pointer to USB device
    \param[in]  puhost: pointer to USB host
    \param[in]  pustate: pointer to USB state driver
    \param[out] none
    \retval     none
*/
static void enum_get_product_string_desc_handle (usb_core_handle_struct *pudev, 
                                                 usbh_host_struct *puhost, 
                                                 usbh_state_handle_struct *pustate)
{
    puhost->usbh_backup_state.enum_backup_state = ENUM_GET_PRODUCT_STRING_DESC;

    if (0U != puhost->device.dev_desc.iProduct) {
        if (CTRL_IDLE == puhost->usbh_backup_state.ctrl_backup_state) {
            usbh_enum_desc_get(pudev, 
                               puhost, 
                               pudev->host.rx_buffer,
                               USB_REQTYPE_DEVICE | USB_STANDARD_REQ, 
                               USB_STRDESC | puhost->device.dev_desc.iProduct,
                               0xffU);
        }
        
        if (USBH_OK == ctrl_state_polling_fun(pudev, puhost, pustate)) {
            usbh_string_desc_parse(pudev->host.rx_buffer, local_buffer, 0xffU);
          
            /* User callback for Product string */
            puhost->usr_cb->product_string(local_buffer);
          
            scd_event_handle(pudev, 
                             puhost, 
                             pustate, 
                             ENUN_EVENT_GET_SERIALNUM_STRING_DESC, 
                             pustate->usbh_current_state);
        }
        
    } else {
        puhost->usr_cb->product_string("N/A");
        scd_event_handle(pudev, 
                         puhost, 
                         pustate, 
                         ENUN_EVENT_GET_SERIALNUM_STRING_DESC, 
                         pustate->usbh_current_state);
    }
}

/*!
    \brief      the handle function of ENUM_GET_SERIALNUM_STRING_DESC state
    \param[in]  pudev: pointer to USB device
    \param[in]  puhost: pointer to USB host
    \param[in]  pustate: pointer to USB state driver
    \param[out] none
    \retval     none
*/
static void enum_get_serialnum_string_desc_handle (usb_core_handle_struct *pudev, 
                                                   usbh_host_struct *puhost, 
                                                   usbh_state_handle_struct *pustate)
{
    puhost->usbh_backup_state.enum_backup_state = ENUM_GET_SERIALNUM_STRING_DESC;

    if (0U != puhost->device.dev_desc.iSerialNumber) {
        if (CTRL_IDLE == puhost->usbh_backup_state.ctrl_backup_state) {
            usbh_enum_desc_get(pudev, 
                               puhost, 
                               pudev->host.rx_buffer, 
                               USB_REQTYPE_DEVICE | USB_STANDARD_REQ, 
                               USB_STRDESC | puhost->device.dev_desc.iSerialNumber,
                               0xffU);
        }
        
        if (USBH_OK == ctrl_state_polling_fun(pudev, puhost, pustate)){
            usbh_string_desc_parse(pudev->host.rx_buffer, local_buffer, 0xffU);
          
            /* user callback for product string */
            puhost->usr_cb->serial_num_string(local_buffer);
            scd_event_handle(pudev, 
                             puhost, 
                             pustate, 
                             ENUN_EVENT_SET_CONFIGURATION, 
                             pustate->usbh_current_state);
        }
    } else {
        puhost->usr_cb->serial_num_string("N/A");
        scd_event_handle(pudev, 
                         puhost, 
                         pustate, 
                         ENUN_EVENT_SET_CONFIGURATION, 
                         pustate->usbh_current_state);
    }
}

/*!
    \brief      the handle function of ENUM_SET_CONFIGURATION state
    \param[in]  pudev: pointer to USB device
    \param[in]  puhost: pointer to USB host
    \param[in]  pustate: pointer to USB state driver
    \param[out] none
    \retval     none
*/
static void enum_set_configuration_handle (usb_core_handle_struct *pudev, 
                                           usbh_host_struct *puhost, 
                                           usbh_state_handle_struct *pustate)
{
    puhost->usbh_backup_state.enum_backup_state = ENUM_SET_CONFIGURATION;

    if (CTRL_IDLE == puhost->usbh_backup_state.ctrl_backup_state ) {
        usbh_enum_cfg_set(pudev, puhost, (uint16_t)puhost->device.cfg_desc.bConfigurationValue);
    }
    
    if (USBH_OK == ctrl_state_polling_fun(pudev, puhost, pustate)) {
        scd_event_handle(pudev, 
                         puhost, 
                         pustate, 
                         ENUN_EVENT_DEV_CONFIGURED, 
                         pustate->usbh_current_state);
    }
}

/*!
    \brief      the handle function of ENUM_DEV_CONFIGURED state
    \param[in]  pudev: pointer to USB device
    \param[in]  puhost: pointer to USB host
    \param[in]  pustate: pointer to USB state driver
    \param[out] none
    \retval     none
*/
static void enum_dev_configured_handle (usb_core_handle_struct *pudev, 
                                        usbh_host_struct *puhost, 
                                        usbh_state_handle_struct *pustate)
{
    puhost->usbh_backup_state.enum_backup_state = ENUM_DEV_CONFIGURED;
    scd_event_handle(pudev, puhost, pustate, GO_TO_UP_STATE_EVENT, pustate->usbh_current_state);
}

/*!
    \brief      get descriptor in usb host enumeration stage
    \param[in]  pudev: pointer to USB device
    \param[in]  puhost: pointer to USB host
    \param[in]  buf: buffer to store the descriptor
    \param[in]  ReqType: descriptor type
    \param[in]  ValueIdx: wValue for the GetDescriptr request
    \param[in]  Len: length of the descriptor
    \param[out] none
    \retval     none
*/
void usbh_enum_desc_get(usb_core_handle_struct *pudev, 
                        usbh_host_struct *puhost, 
                        uint8_t *buf, 
                        uint8_t  req_type, 
                        uint16_t value_idx, 
                        uint16_t len)
{
    usb_setup_union *pSetup = &(puhost->control.setup);

    pSetup->b.bmRequestType = USB_DIR_IN | req_type;
    pSetup->b.bRequest = USBREQ_GET_DESCRIPTOR;
    pSetup->b.wValue = value_idx;

    if (USB_STRDESC == (value_idx & 0xff00U)){
        pSetup->b.wIndex = 0x0409U;
    } else {
        pSetup->b.wIndex = 0U;
    }

    pSetup->b.wLength = len;
    
    puhost->control.buff = buf;
    puhost->control.length = len;
    
}

/*!
    \brief      set address in usb host enumeration stage
    \param[in]  pudev: pointer to USB device
    \param[in]  puhost: pointer to USB host
    \param[in]  device_address: the device address
    \param[out] none
    \retval     none
*/
void usbh_enum_addr_set(usb_core_handle_struct *pudev, 
                        usbh_host_struct *puhost,
                        uint8_t device_address)
{
    usb_setup_union *p_setup = &(puhost->control.setup);

    p_setup->b.bmRequestType = USB_DIR_OUT | USB_REQTYPE_DEVICE | USB_STANDARD_REQ;
    p_setup->b.bRequest = USBREQ_SET_ADDRESS;
    p_setup->b.wValue = (uint16_t)device_address;
    p_setup->b.wIndex = 0U;
    p_setup->b.wLength = 0U;
    puhost->control.buff = 0U;
    puhost->control.length = 0U;
}

/*!
    \brief      set configuration in usb host enumeration stage
    \param[in]  pudev: pointer to USB device
    \param[in]  puhost: pointer to USB host
    \param[in]  cfg_idx: the index of the configuration
    \param[out] none
    \retval     none
*/
void usbh_enum_cfg_set(usb_core_handle_struct *pudev, 
                       usbh_host_struct *puhost,
                       uint16_t cfg_idx)
{
    usb_setup_union *p_setup = &(puhost->control.setup);

    p_setup->b.bmRequestType = USB_DIR_OUT | USB_REQTYPE_DEVICE | USB_STANDARD_REQ;
    p_setup->b.bRequest = USBREQ_SET_CONFIGURATION;
    p_setup->b.wValue = cfg_idx;
    p_setup->b.wIndex = 0U;
    p_setup->b.wLength = 0U;
    puhost->control.buff = 0;
    puhost->control.length = 0U;
}

/*!
    \brief      parse the device descriptor
    \param[in]  dev_desc: device_descriptor destinaton address 
    \param[in]  buf: buffer where the source descriptor is available
    \param[in]  len: length of the descriptor
    \param[out] none
    \retval     none
*/
void usbh_device_desc_parse (usb_descriptor_device_struct *dev_desc, uint8_t *buf, uint16_t len)
{
    dev_desc->Header.bLength  = *(uint8_t *)(buf + 0);
    dev_desc->Header.bDescriptorType = *(uint8_t *)(buf + 1);
    dev_desc->bcdUSB          = SWAPBYTE(buf + 2);
    dev_desc->bDeviceClass    = *(uint8_t *)(buf + 4);
    dev_desc->bDeviceSubClass = *(uint8_t *)(buf + 5);
    dev_desc->bDeviceProtocol = *(uint8_t *)(buf + 6);
    dev_desc->bMaxPacketSize0 = *(uint8_t *)(buf + 7);

    if (len > 8U){
        /* for 1st time after device connection, host may issue only 8 bytes for device descriptor length  */
        dev_desc->idVendor      = SWAPBYTE(buf + 8);
        dev_desc->idProduct     = SWAPBYTE(buf + 10);
        dev_desc->bcdDevice     = SWAPBYTE(buf + 12);
        dev_desc->iManufacturer = *(uint8_t *)(buf + 14);
        dev_desc->iProduct      = *(uint8_t *)(buf + 15);
        dev_desc->iSerialNumber = *(uint8_t *)(buf + 16);
        dev_desc->bNumberConfigurations = *(uint8_t *)(buf + 17);
    }
}

/*!
    \brief      parse the configuration descriptor
    \param[in]  cfg_desc: configuration descriptor address
    \param[in]  itf_desc: interface descriptor address
    \param[in]  ep_desc: endpoint descriptor address
    \param[in]  buf: buffer where the source descriptor is available
    \param[in]  len: length of the descriptor
    \param[out] none
    \retval     none
*/
void  usbh_cfg_desc_parse (usb_descriptor_configuration_struct *cfg_desc,
                           usb_descriptor_interface_struct *itf_desc,
                           usb_descriptor_endpoint_struct ep_desc[][USBH_MAX_EP_NUM],
                           uint8_t *buf,
                           uint16_t len)
{  
    usb_descriptor_interface_struct *pitf = NULL;
    usb_descriptor_interface_struct temp_pitf;
    usb_descriptor_endpoint_struct *pep = NULL;
    usb_descriptor_header_struct *pdesc = (usb_descriptor_header_struct *)buf;

    uint8_t itf_ix = 0U;
    uint8_t ep_ix = 0U;
    uint16_t ptr = 0U;
    static uint8_t prev_itf = 0U;
    static uint16_t prev_ep_size = 0U;

    /* parse configuration descriptor */
    cfg_desc->Header.bLength         = *(uint8_t *)(buf + 0);
    cfg_desc->Header.bDescriptorType = *(uint8_t *)(buf + 1);
    cfg_desc->wTotalLength           = SWAPBYTE(buf + 2);
    cfg_desc->bNumInterfaces         = *(uint8_t *)(buf + 4);
    cfg_desc->bConfigurationValue    = *(uint8_t *)(buf + 5);
    cfg_desc->iConfiguration         = *(uint8_t *)(buf + 6);
    cfg_desc->bmAttributes           = *(uint8_t *)(buf + 7);
    cfg_desc->bMaxPower              = *(uint8_t *)(buf + 8);

    if (len > USB_CFGDESC_SIZE) {
        ptr = USB_CFG_DESC_LEN;

        if (cfg_desc->bNumInterfaces <= USBH_MAX_INTERFACES_NUM) {
            pitf = (usb_descriptor_interface_struct *)0;

            for (; ptr < cfg_desc->wTotalLength; ) {
                pdesc = usbh_next_desc_get((uint8_t *)pdesc, &ptr);

                if (USB_DESCTYPE_INTERFACE == pdesc->bDescriptorType) {
                    itf_ix = *((uint8_t *)pdesc + 2U);
                    pitf = &itf_desc[itf_ix];

                    if (*((uint8_t *)pdesc + 3U) < 3U) {
                        usbh_interface_desc_parse (&temp_pitf, (uint8_t *)pdesc);

                        /* parse endpoint descriptors relative to the current interface */
                        if (temp_pitf.bNumEndpoints <= USBH_MAX_EP_NUM) {
                            for (ep_ix = 0U; ep_ix < temp_pitf.bNumEndpoints;) {
                                pdesc = usbh_next_desc_get((void* )pdesc, &ptr);

                                if (USB_DESCTYPE_ENDPOINT == pdesc->bDescriptorType) {
                                    pep = &ep_desc[itf_ix][ep_ix];

                                    if (prev_itf != itf_ix) {
                                        prev_itf = itf_ix;
                                        usbh_interface_desc_parse (pitf, (uint8_t *)&temp_pitf);
                                    } else {
                                        if (prev_ep_size > SWAPBYTE((uint8_t *)pdesc + 4)) {
                                            break;
                                        } else {
                                            usbh_interface_desc_parse (pitf, (uint8_t *)&temp_pitf);
                                        }
                                    }

                                    usbh_endpoint_desc_parse (pep, (uint8_t *)pdesc);
                                    prev_ep_size = SWAPBYTE((uint8_t *)pdesc + 4);
                                    ep_ix++;
                                }
                            }
                        }
                    }
                }
            }
        }

        prev_ep_size = 0U;
        prev_itf = 0U; 
    }
}

/*!
    \brief      parse the interface descriptor
    \param[in]  itf_desc: interface descriptor destination
    \param[in]  buf: buffer where the descriptor data is available
    \param[out] none
    \retval     none
*/
void  usbh_interface_desc_parse (usb_descriptor_interface_struct *itf_desc, uint8_t *buf)
{
    itf_desc->Header.bLength         = *(uint8_t *)(buf + 0);
    itf_desc->Header.bDescriptorType = *(uint8_t *)(buf + 1);
    itf_desc->bInterfaceNumber       = *(uint8_t *)(buf + 2);
    itf_desc->bAlternateSetting      = *(uint8_t *)(buf + 3);
    itf_desc->bNumEndpoints          = *(uint8_t *)(buf + 4);
    itf_desc->bInterfaceClass        = *(uint8_t *)(buf + 5);
    itf_desc->bInterfaceSubClass     = *(uint8_t *)(buf + 6);
    itf_desc->bInterfaceProtocol     = *(uint8_t *)(buf + 7);
    itf_desc->iInterface             = *(uint8_t *)(buf + 8);
}

/*!
    \brief      parse the endpoint descriptor
    \param[in]  ep_desc: endpoint descriptor destination address
    \param[in]  buf: buffer where the parsed descriptor stored
    \param[out] none
    \retval     none
*/
void  usbh_endpoint_desc_parse (usb_descriptor_endpoint_struct *ep_desc, uint8_t *buf)
{
    ep_desc->Header.bLength          = *(uint8_t *)(buf + 0);
    ep_desc->Header.bDescriptorType  = *(uint8_t *)(buf + 1);
    ep_desc->bEndpointAddress = *(uint8_t *)(buf + 2);
    ep_desc->bmAttributes     = *(uint8_t *)(buf + 3);
    ep_desc->wMaxPacketSize   = SWAPBYTE(buf + 4);
    ep_desc->bInterval        = *(uint8_t *)(buf + 6);
}

/*!
    \brief      parse the string descriptor
    \param[in]  psrc: source pointer containing the descriptor data
    \param[in]  pdest: destination address pointer
    \param[in]  len: length of the descriptor
    \param[out] none
    \retval     none
*/
void usbh_string_desc_parse (uint8_t* psrc, uint8_t* pdest, uint16_t len)
{
    uint16_t strlength;
    uint16_t idx;

    /* the unicode string descriptor is not null-terminated. the string length is
        computed by substracting two from the value of the first byte of the descriptor.
    */

    /* check which is lower size, the size of string or the length of bytes read from the device */

    if (USB_DESCTYPE_STRING == psrc[1]){
        /* make sure the descriptor is string type */

        /* psrc[0] contains size of descriptor, subtract 2 to get the length of string */      
        strlength = ((((uint16_t)psrc[0] - 2U) <= len) ? ((uint16_t)psrc[0] - 2U) : len);
        psrc += 2; /* adjust the offset ignoring the string len and descriptor type */

        for (idx = 0U; idx < strlength; idx += 2U) {
            /* copy only the string and ignore the unicode id, hence add the src */
            *pdest = psrc[idx];
            pdest++;
        }

        *pdest = 0U; /* mark end of string */  
    }
}

/*!
    \brief      get the next descriptor header
    \param[in]  pbuf: pointer to buffer where the cfg descriptor is available
    \param[in]  ptr: data popinter inside the configuration descriptor
    \param[out] none
    \retval     next descriptor header
*/
usb_descriptor_header_struct *usbh_next_desc_get (uint8_t *pbuf, uint16_t *ptr)
{
    uint8_t len = ((usb_descriptor_header_struct *)pbuf)->bLength;

    usb_descriptor_header_struct *pnext;

    *ptr += len;

    pnext = (usb_descriptor_header_struct *)((uint8_t *)pbuf + len);

    return(pnext);
}

