/*!
    \file  usbh_core.c 
    \brief this file implements the functions for the core state machine process
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#include "usbh_hcs.h"
#include "usbh_core.h"
#include "usbh_int.h"
#include "stdio.h"
#include "usbh_std.h"
#include "usbh_ctrl.h"
#include "usb_core.h"

extern class_polling_fun_cb_struct class_polling_cb;

uint8_t usbh_sof          (usb_core_handle_struct *pudev);
uint8_t usbh_connected    (usb_core_handle_struct *pudev);
uint8_t usbh_disconnected (usb_core_handle_struct *pudev);

usbh_hcd_int_cb_struct usbh_hcd_int_cb = 
{
    usbh_sof,
    usbh_connected,
    usbh_disconnected,
};

usbh_hcd_int_cb_struct  *usbh_hcd_int_fops = &usbh_hcd_int_cb;
extern usbh_state_handle_struct usbh_state_core;

static void host_idle_handle             (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void host_dev_attached_handle     (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void host_dev_detached_handle     (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void host_detect_dev_speed_handle (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void host_enum_handle             (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void host_class_request_handle    (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void host_class_handle            (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void host_user_input_handle       (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void host_suspended_handle        (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void host_error_handle            (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);

static usbh_status_enum class_req_state_polling_fun  (usb_core_handle_struct *pudev, usbh_host_struct *puhost, void *pustate);
static usbh_status_enum class_state_polling_fun      (usb_core_handle_struct *pudev, usbh_host_struct *puhost, void *pustate);

/* the host state handle function array */
void (*host_state_handle[]) (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate) =
{
    host_idle_handle,
    host_dev_attached_handle,
    host_dev_detached_handle,
    host_detect_dev_speed_handle,
    host_enum_handle,
    host_class_request_handle,
    host_class_handle,
    host_user_input_handle,
    host_suspended_handle,
    host_error_handle,
};

/* the host state handle table */
state_table_struct host_handle_table[HOST_HANDLE_TABLE_SIZE] = 
{
    /* the current state  the current event        the next state        the event function */
    {HOST_IDLE,           HOST_EVENT_ATTACHED,     HOST_DEV_ATTACHED,    only_state_move     },
    {HOST_DEV_ATTACHED,   HOST_EVENT_ENUM,         HOST_ENUMERATION,     only_state_move     },
    {HOST_ENUMERATION,    HOST_EVENT_USER_INPUT,   HOST_USER_INPUT,      only_state_move     },
    {HOST_USER_INPUT,     HOST_EVENT_CLASS_REQ,    HOST_CLASS_REQUEST,   only_state_move     },
    {HOST_CLASS_REQUEST,  HOST_EVENT_CLASS,        HOST_CLASS,           only_state_move     },
    {HOST_CLASS,          HOST_EVENT_ERROR,        HOST_ERROR,           only_state_move     },
    {HOST_ERROR,          HOST_EVENT_IDLE,         HOST_IDLE,            only_state_move     },
    {HOST_DEV_DETACHED,   HOST_EVENT_IDLE,         HOST_IDLE,            only_state_move     },
    {HOST_CLASS_REQUEST,  HOST_EVENT_ERROR,        HOST_ERROR,           only_state_move     },
};

/*!
    \brief      the polling function of HOST state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
usbh_status_enum host_state_polling_fun (usb_core_handle_struct *pudev, 
                                         usbh_host_struct *puhost, 
                                         void *pustate)
{
    usbh_state_handle_struct *p_state = (usbh_state_handle_struct *)pustate;

    scd_begin(p_state, HOST_FSM_ID);

    if (-1 == p_state->usbh_current_state_stack_top) {
        uint8_t cur_state = p_state->usbh_current_state;

        if ((0U == hcd_is_device_connected(pudev)) && (HOST_IDLE != cur_state)) {
            if (HOST_DEV_DETACHED != cur_state) {
                p_state->usbh_current_state = HOST_DEV_DETACHED;
                cur_state = HOST_DEV_DETACHED;
            }
        }

        host_state_handle[cur_state](pudev, puhost, p_state);
    } else {
        uint8_t stack0_state = p_state->stack[0].state;

        if ((0U == hcd_is_device_connected(pudev)) && (HOST_IDLE != stack0_state)) {
            if (HOST_DEV_DETACHED != stack0_state) {
                p_state->stack[0].state = HOST_DEV_DETACHED;
                stack0_state = HOST_DEV_DETACHED;
                p_state->usbh_current_state = HOST_DEV_DETACHED;
            }
        }

        host_state_handle[stack0_state](pudev, puhost, p_state);
    }

    return USBH_OK;
}

/*!
    \brief      the handle function of HOST_IDLE state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
static void host_idle_handle (usb_core_handle_struct *pudev, 
                              usbh_host_struct *puhost, 
                              usbh_state_handle_struct *pustate)
{
    if (hcd_is_device_connected(pudev)) {
        scd_event_handle(pudev, puhost, pustate, HOST_EVENT_ATTACHED, pustate->usbh_current_state);

        if ((void *)0 != pudev->mdelay) {
            pudev->mdelay(100U);
        }
    }
}

/*!
    \brief      the handle function of HOST_DEV_ATTACHED state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
static void host_dev_attached_handle (usb_core_handle_struct *pudev, 
                                      usbh_host_struct *puhost, 
                                      usbh_state_handle_struct *pustate)
{
    puhost->usr_cb->device_connected();
    puhost->control.hc_out_num = usbh_channel_alloc(pudev, 0x00U);
    puhost->control.hc_in_num = usbh_channel_alloc(pudev, 0x80U);

    /* reset usb device */
    if (0U == usb_port_reset(pudev)) {
        puhost->usr_cb->device_reset();

        /* wait for USB USBH_ISR_PrtEnDisableChange()
         * host is now ready to start the enumeration
         */
        puhost->device.speed = (uint8_t)USB_CURRENT_SPEED_GET();
        puhost->usr_cb->device_speed_detected(puhost->device.speed);

        /* open IN control pipes */
        usbh_channel_open (pudev,
                           puhost->control.hc_in_num,
                           puhost->device.address,
                           puhost->device.speed,
                           USB_EPTYPE_CTRL,
                           (uint16_t)puhost->control.ep0_size);

        /* open OUT control pipes */
        usbh_channel_open (pudev,
                           puhost->control.hc_out_num,
                           puhost->device.address,
                           puhost->device.speed,
                           USB_EPTYPE_CTRL,
                           (uint16_t)puhost->control.ep0_size);

        scd_event_handle(pudev, puhost, pustate, HOST_EVENT_ENUM, pustate->usbh_current_state);
    }
}

/*!
    \brief      the handle function of HOST_ENUMERATION state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
static void host_enum_handle (usb_core_handle_struct *pudev, 
                              usbh_host_struct *puhost, 
                              usbh_state_handle_struct *pustate)
{
    if (USBH_OK == enum_state_polling_fun(pudev, puhost, pustate)) {
        puhost->usr_cb->enumeration_finish();
        scd_event_handle(pudev, 
                         puhost, 
                         pustate, 
                         HOST_EVENT_USER_INPUT, 
                         pustate->usbh_current_state);
    }
}

/*!
    \brief      the handle function of HOST_USER_INPUT state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
static void host_user_input_handle (usb_core_handle_struct *pudev, 
                                    usbh_host_struct *puhost, 
                                    usbh_state_handle_struct *pustate)
{
    if (USBH_USER_RESP_OK == puhost->usr_cb->user_input()) {
        if (USBH_OK == (puhost->class_init(pudev, puhost))) {
            scd_event_handle(pudev, 
                             puhost, 
                             pustate, 
                             HOST_EVENT_CLASS_REQ, 
                             pustate->usbh_current_state);
        }
    }
}

/*!
    \brief      the handle function of HOST_CLASS_REQUEST state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
static void host_class_request_handle (usb_core_handle_struct *pudev, 
                                       usbh_host_struct *puhost, 
                                       usbh_state_handle_struct *pustate)
{
    if (USBH_OK == class_req_state_polling_fun(pudev, puhost, pustate)) {
        scd_event_handle(pudev, puhost, pustate, HOST_EVENT_CLASS, pustate->usbh_current_state);
    }
}

/*!
    \brief      the handle function of HOST_CLASS state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
static void host_class_handle (usb_core_handle_struct *pudev, 
                               usbh_host_struct *puhost, 
                               usbh_state_handle_struct *pustate)
{
    class_state_polling_fun(pudev, puhost, pustate);
}

/*!
    \brief      the handle function of HOST_SUSPENDED state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
static void host_suspended_handle (usb_core_handle_struct *pudev, 
                                   usbh_host_struct *puhost, 
                                   usbh_state_handle_struct *pustate)
{
    /* no operation */
}

/*!
    \brief      the handle function of HOST_ERROR state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
static void host_error_handle (usb_core_handle_struct *pudev, 
                               usbh_host_struct *puhost, 
                               usbh_state_handle_struct *pustate)
{
    /* re-initilaize host for new enumeration */
    usbh_deinit (pudev, puhost,&usbh_state_core);
    puhost->usr_cb->deinit();
    puhost->class_deinit(pudev, &puhost->device);
    scd_event_handle(pudev, puhost, pustate, HOST_EVENT_IDLE, pustate->usbh_current_state);
}

/*!
    \brief      the handle function of HOST_DEV_DETACHED state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
static void host_dev_detached_handle (usb_core_handle_struct *pudev, 
                                      usbh_host_struct *puhost, 
                                      usbh_state_handle_struct *pustate)
{
    /* manage user disconnect operations*/
    puhost->usr_cb->device_disconnected();

    /* re-initilaize host for new enumeration */
    usbh_deinit(pudev, puhost,&usbh_state_core);
    puhost->usr_cb->deinit();
    puhost->class_deinit(pudev, &puhost->device);
    usbh_allchannel_dealloc(pudev);
    scd_event_handle(pudev, puhost, pustate, HOST_EVENT_IDLE, pustate->usbh_current_state);
}

/*!
    \brief      the handle function of HOST_DETECT_DEV_SPEED state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
static void host_detect_dev_speed_handle (usb_core_handle_struct *pudev, 
                                          usbh_host_struct *puhost, 
                                          usbh_state_handle_struct *pustate)
{
    /* no operation */
}

/*!
    \brief      usb connect callback function from the interrupt. 
    \param[in]  pudev: pointer to usb device
    \param[out] none
    \retval     operation status
*/
uint8_t usbh_connected (usb_core_handle_struct *pudev)
{
    pudev->host.connect_status = 1U;

    return 0U;
}

/*!
    \brief      usb disconnect callback function from the interrupt. 
    \param[in]  pudev: pointer to usb device
    \param[out] none
    \retval     operation status
*/
uint8_t usbh_disconnected (usb_core_handle_struct *pudev)
{
    pudev->host.connect_status = 0U;

    return 0U;
}

/*!
    \brief      usb sof callback function from the interrupt. 
    \param[in]  pudev: pointer to usb device
    \param[out] none
    \retval     operation status
*/
uint8_t usbh_sof (usb_core_handle_struct *pudev)
{
    /* this callback could be used to implement a scheduler process */
    return 0U;
}

/*!
    \brief      initialize the host portion of the driver.
    \param[in]  pudev: pointer to usb device
    \param[in]  core_id: usb otg core identifier(high-speed or full-speed)
    \param[out] none
    \retval     operation status
*/
uint32_t hcd_init(usb_core_handle_struct *pudev, usb_core_id_enum core_id)
{
    pudev->host.connect_status = 0U;

    pudev->host.host_channel[0].endp_mps = 8U;

    usb_core_select(pudev, core_id);

#ifndef DUAL_ROLE_MODE_ENABLED

    USB_GLOBAL_INT_DISABLE();

    usb_core_init(pudev);

    /* force host mode*/
    usb_mode_set(pudev, HOST_MODE);

    usb_hostcore_init(pudev);

    USB_GLOBAL_INT_ENABLE();

#endif

    return 0U;
}

/*!
    \brief      check if the device is connected.
    \param[in]  pudev: pointer to usb device
    \param[out] none
    \retval     device connection status. 1 -> connected and 0 -> disconnected
*/
uint32_t hcd_is_device_connected(usb_core_handle_struct *pudev)
{
    return (uint32_t)(pudev->host.connect_status);
}

/*!
    \brief      this function returns the last URBstate
    \param[in]  pudev: pointer to usb device
    \param[in]  channel_num: host channel number which is in (0..7)
    \param[out] none
    \retval     urb_state_enum
*/
urb_state_enum hcd_urb_state_get (usb_core_handle_struct *pudev, uint8_t channel_num) 
{
    return pudev->host.host_channel[channel_num].urb_state;
}

/*!
    \brief      this function returns the last URBstate
    \param[in]  pudev: pointer to usb device
    \param[in]  channel_num: host channel number which is in (0..7)
    \param[out] none
    \retval     No. of data bytes transferred
*/
uint32_t hcd_xfer_count_get (usb_core_handle_struct *pudev, uint8_t channel_num) 
{
    return pudev->host.host_channel[channel_num].xfer_count;
}

/*!
    \brief      de-initialize host
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[out] none
    \retval     host status
*/
usbh_status_enum usbh_deinit(usb_core_handle_struct *pudev, 
                             usbh_host_struct *puhost, 
                             usbh_state_handle_struct* pustate)
{
    /* software init */

    puhost->control.ep0_size = USB_MAX_EP0_SIZE;

    puhost->device.address = USBH_DEVICE_ADDRESS_DEFAULT;
    puhost->device.speed = HPRT_PRTSPD_FULL_SPEED;

    usbh_channel_free(pudev, puhost->control.hc_in_num);
    usbh_channel_free(pudev, puhost->control.hc_out_num);
    
    scd_init(pustate);
    scd_table_regist(pustate, host_handle_table, HOST_FSM_ID, HOST_HANDLE_TABLE_SIZE);
    scd_table_regist(pustate, enum_handle_table, ENUM_FSM_ID, ENUM_HANDLE_TABLE_SIZE);
    scd_table_regist(pustate, ctrl_handle_table, CTRL_FSM_ID, CTRL_HANDLE_TABLE_SIZE);
  
    scd_begin(pustate,HOST_FSM_ID);
    scd_state_move(pustate, HOST_IDLE);

    return USBH_OK;
}

/*!
    \brief      state core driver init
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
void scd_init(usbh_state_handle_struct* pustate)
{
    /* init the state core */
    pustate->usbh_current_state = 0U;
    pustate->usbh_current_state_table = NULL;
    pustate->usbh_current_state_table_size = 0U;
  
    pustate->usbh_current_state_stack_top = -1;
    pustate->stack->state = 0U;
    pustate->stack->table_size = 0U;
    pustate->stack->table = NULL;
  
    pustate->usbh_regist_state_table_num = 0U;
    pustate->usbh_regist_state_table->table = NULL;
    pustate->usbh_regist_state_table->table_size = 0U;
    pustate->usbh_regist_state_table->id = 0U;
  
    /* init the control and the enumeration polling handle flag */
    ctrl_polling_handle_flag = 0U;
    enum_polling_handle_flag = 0U;
}

/*!
    \brief      state core driver table regist
    \param[in]  pustate: pointer to usb state driver
    \param[in]  pstate_table: pointer to the table to regist
    \param[in]  table_id: the id of the table to regist
    \param[in]  current_table_size: the size of the current table to regist
    \param[out] none
    \retval     none
*/
void scd_table_regist (usbh_state_handle_struct* pustate, 
                       state_table_struct* pstate_table, 
                       uint8_t table_id, 
                       uint8_t current_table_size)
{
    usbh_state_regist_table_struct *cur_state_reg_table;

    cur_state_reg_table = &pustate->usbh_regist_state_table[pustate->usbh_regist_state_table_num];

    cur_state_reg_table->id = table_id;
    cur_state_reg_table->table = pstate_table;
    cur_state_reg_table->table_size = current_table_size;

    pustate->usbh_regist_state_table_num++;
}

/*!
    \brief      state core driver begin
    \param[in]  pustate: pointer to usb state driver
    \param[in]  table_id: the id of the table to begin
    \param[out] none
    \retval     none
*/
void scd_begin(usbh_state_handle_struct* pustate, uint8_t table_id)
{
    uint8_t i = 0, table_num = pustate->usbh_regist_state_table_num;
    usbh_state_regist_table_struct *cur_state_reg_table;

    for (i = 0; i < table_num; i++) {
        cur_state_reg_table = &pustate->usbh_regist_state_table[i];

        if (table_id == cur_state_reg_table->id) {
            pustate->usbh_current_state_table = cur_state_reg_table->table;
            pustate->usbh_current_state_table_size = cur_state_reg_table->table_size;
            break;
        }
    }
}

/*!
    \brief      state core driver move state
    \param[in]  pustate: pointer to usb state driver
    \param[in]  state: the state to move
    \param[out] none
    \retval     none
*/
void scd_state_move(usbh_state_handle_struct* pustate, uint8_t state)
{
    pustate->usbh_current_state = state;
}

/*!
    \brief      state core driver event handle
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[in]  event: the current event
    \param[in]  state: the current state
    \param[out] none
    \retval     host status
*/
usbh_status_enum scd_event_handle (usb_core_handle_struct *pudev, 
                                   usbh_host_struct *puhost, 
                                   usbh_state_handle_struct* pustate, 
                                   uint8_t event, 
                                   uint8_t state)
{
    uint8_t i = 0;
    ACT_FUN event_act_fun = NULL;
    state_table_struct *backup_state_t = pustate->usbh_current_state_table;
    state_table_struct *executive_state_table = pustate->usbh_current_state_table;

    /* look up the table to find the action function */
    for (i = 0; i < pustate->usbh_current_state_table_size; i++) {
        if (state == executive_state_table->cur_state) {
            if (event == executive_state_table->cur_event) {
                 state = executive_state_table->next_state;
                 event_act_fun = executive_state_table->event_action_fun;
                 break;
            } else {
                executive_state_table++;
            }
        } else {
            executive_state_table++;
        }
    }

    pustate->usbh_current_state_table = backup_state_t;

    /* if the action function is not NULL, execute the action function */
    if (event_act_fun) {
        if (event_act_fun == &only_state_move) {
            pustate->usbh_current_state = state;
        } else {
            return event_act_fun(pudev, puhost, pustate);
        }
    }

    return USBH_BUSY;
}

/*!
    \brief      state core driver table push
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
void scd_table_push(usbh_state_handle_struct* pustate)
{
    usbh_state_stack_struct *top_state_element;

    if (pustate->usbh_current_state_stack_top < MAX_USBH_STATE_STACK_DEEP) {
        pustate->usbh_current_state_stack_top++;

        top_state_element = &pustate->stack[pustate->usbh_current_state_stack_top];

        /* put the current state table into the state stack */
        top_state_element->state = pustate->usbh_current_state;
        top_state_element->table = pustate->usbh_current_state_table;
        top_state_element->table_size = pustate->usbh_current_state_table_size;
    }
}

/*!
    \brief      state core driver table pop
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
void scd_table_pop (usbh_state_handle_struct* pustate)
{
    usbh_state_stack_struct *top_state_element;

    top_state_element = &pustate->stack[pustate->usbh_current_state_stack_top];

    if (pustate->usbh_current_state_stack_top > -1) {
        /* get the current state table from the state stack */
        pustate->usbh_current_state = top_state_element->state;
        pustate->usbh_current_state_table = top_state_element->table;
        pustate->usbh_current_state_table_size = top_state_element->table_size;
        pustate->usbh_current_state_stack_top--;
    }
}
/*!
    \brief      the polling function of class req state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     host status
*/
static usbh_status_enum class_req_state_polling_fun (usb_core_handle_struct *pudev, usbh_host_struct *puhost, void *pustate)
{
    return class_polling_cb.class_req_polling(pudev, puhost, pustate);
}

/*!
    \brief      the polling function of class state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     host status
*/
static usbh_status_enum class_state_polling_fun (usb_core_handle_struct *pudev, usbh_host_struct *puhost, void *pustate)
{
    return class_polling_cb.class_polling(pudev, puhost, pustate);
}

/*!
    \brief      the function is only used to state move
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
usbh_status_enum only_state_move (usb_core_handle_struct *pudev, usbh_host_struct *puhost, void *pustate)
{
    return USBH_OK;
}

/*!
    \brief      the function to the up state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
usbh_status_enum goto_up_state_fun (usb_core_handle_struct *pudev, usbh_host_struct *puhost, void *pustate)
{
    scd_table_pop((usbh_state_handle_struct *)pustate);

    return USBH_OK;
}
