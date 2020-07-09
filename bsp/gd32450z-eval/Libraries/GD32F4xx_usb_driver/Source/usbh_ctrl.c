/*!
    \file  usbh_ctrl.c 
    \brief this file implements the functions for the control transmit process
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/
#include "usbh_core.h"
#include "usbh_std.h"
#include "usbh_ctrl.h"

uint8_t ctrl_polling_handle_flag = 0U;
uint8_t ctrl_setup_wait_flag = 0U;
uint8_t ctrl_data_wait_flag = 0U;
uint8_t ctrl_status_wait_flag = 0U;

static uint16_t timeout = 0U;

static void ctrl_idle_handle      (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void ctrl_setup_handle     (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void ctrl_data_handle      (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void ctrl_status_handle    (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void ctrl_error_handle     (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void ctrl_stalled_handle   (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);
static void ctrl_complete_handle  (usb_core_handle_struct *pudev, usbh_host_struct *puhost, usbh_state_handle_struct *pustate);

/* the ctrl state handle function array */
void (*ctrl_state_handle[]) (usb_core_handle_struct *pudev, 
                             usbh_host_struct *puhost, 
                             usbh_state_handle_struct *pustate) =
{
    ctrl_idle_handle,
    ctrl_setup_handle,
    ctrl_data_handle,
    ctrl_status_handle,
    ctrl_error_handle,
    ctrl_stalled_handle,
    ctrl_complete_handle,
};

/* the ctrl state handle table */
state_table_struct ctrl_handle_table[CTRL_HANDLE_TABLE_SIZE] = 
{
    /* the current state   the current event           the next state        the event function */
    {CTRL_IDLE,            CTRL_EVENT_SETUP,           CTRL_SETUP,           only_state_move     },
    {CTRL_SETUP,           CTRL_EVENT_DATA,            CTRL_DATA,            only_state_move     },
    {CTRL_SETUP,           CTRL_EVENT_STATUS,          CTRL_STATUS,          only_state_move     },
    {CTRL_SETUP,           CTRL_EVENT_ERROR,           CTRL_ERROR,           only_state_move     },
    {CTRL_DATA,            CTRL_EVENT_STATUS,          CTRL_STATUS,          only_state_move     },
    {CTRL_DATA,            CTRL_EVENT_ERROR,           CTRL_ERROR,           only_state_move     },
    {CTRL_DATA,            CTRL_EVENT_STALLED,         CTRL_STALLED,         only_state_move     },
    {CTRL_STATUS,          CTRL_EVENT_COMPLETE,        CTRL_COMPLETE,        only_state_move     },
    {CTRL_STATUS,          CTRL_EVENT_ERROR,           CTRL_ERROR,           only_state_move     },
    {CTRL_STATUS,          CTRL_EVENT_STALLED,         CTRL_STALLED,         only_state_move     },
    {CTRL_ERROR,           GO_TO_UP_STATE_EVENT,       UP_STATE,             goto_up_state_fun   },
    {CTRL_STALLED,         GO_TO_UP_STATE_EVENT,       UP_STATE,             goto_up_state_fun   },
    {CTRL_COMPLETE,        GO_TO_UP_STATE_EVENT,       UP_STATE,             goto_up_state_fun   },
};

/*!
    \brief      the polling function of CTRL state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
usbh_status_enum ctrl_state_polling_fun (usb_core_handle_struct *pudev, 
                                    usbh_host_struct *puhost, 
                                    void *pustate)
{
    usbh_status_enum exe_state = USBH_BUSY;
    usbh_state_handle_struct *p_state;

    p_state = (usbh_state_handle_struct *)pustate;
  
    /* if first enter this function, begin the ctrl state */
    if (0U == ctrl_polling_handle_flag) {
        ctrl_polling_handle_flag = 1U;
        scd_table_push(p_state);
        scd_state_move(p_state, CTRL_IDLE);
    }

    /* base on the current state to handle the ctrl state */
    scd_begin(p_state, CTRL_FSM_ID);
    ctrl_state_handle[p_state->usbh_current_state](pudev, puhost, p_state);

    /* determine the control transfer whether to complete */
    switch (puhost->usbh_backup_state.ctrl_backup_state) {
        case CTRL_COMPLETE:
            ctrl_polling_handle_flag = 0U;
            puhost->usbh_backup_state.ctrl_backup_state = CTRL_IDLE;
            exe_state = USBH_OK;
            break;
        case CTRL_STALLED:
            ctrl_polling_handle_flag = 0U;
            puhost->usbh_backup_state.ctrl_backup_state = CTRL_IDLE;
            exe_state = USBH_NOT_SUPPORTED;
            break;
        case CTRL_ERROR:
            ctrl_polling_handle_flag = 0U;
            puhost->usbh_backup_state.ctrl_backup_state = CTRL_IDLE;
            exe_state = USBH_FAIL;
            break;
        default:
            exe_state = USBH_BUSY;
            break;
    }

    return exe_state;
}

/*!
    \brief      the handle function of CTRL_IDLE state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
static void ctrl_idle_handle (usb_core_handle_struct *pudev, 
                              usbh_host_struct *puhost, 
                              usbh_state_handle_struct *pustate)
{
    puhost->usbh_backup_state.ctrl_backup_state = CTRL_IDLE;
    scd_event_handle(pudev, puhost, pustate, CTRL_EVENT_SETUP, pustate->usbh_current_state);
}

/*!
    \brief      the handle function of CTRL_SETUP state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
static void ctrl_setup_handle (usb_core_handle_struct *pudev, 
                               usbh_host_struct *puhost, 
                               usbh_state_handle_struct *pustate)
{
    urb_state_enum urb_status = URB_IDLE;
    puhost->usbh_backup_state.ctrl_backup_state = CTRL_SETUP;

    if (0U == ctrl_setup_wait_flag) {
        ctrl_setup_wait_flag = 1U;

        /* send a setup packet */
        usbh_ctltx_setup (pudev, 
                          puhost->control.setup.data, 
                          puhost->control.hc_out_num);
    } else {
        urb_status = hcd_urb_state_get(pudev, puhost->control.hc_out_num);

        /* case setup packet sent successfully */
        if (URB_DONE == urb_status) {
            /* check if there is a data stage */
            if (0U != puhost->control.setup.b.wLength) {
                ctrl_setup_wait_flag = 0U;
                timeout = DATA_STAGE_TIMEOUT;
                scd_event_handle(pudev, puhost, pustate, CTRL_EVENT_DATA, pustate->usbh_current_state);
            /* no data stage */
            } else {
                timeout = NODATA_STAGE_TIMEOUT;
                ctrl_setup_wait_flag = 0U;
                scd_event_handle(pudev, 
                                 puhost, 
                                 pustate, 
                                 CTRL_EVENT_STATUS, 
                                 pustate->usbh_current_state);
            }

            /* set the delay timer to enable timeout for data stage completion */
            puhost->control.timer = (uint16_t)USB_CURRENT_FRAME_GET();
        } else if (URB_ERROR == urb_status) {
            ctrl_setup_wait_flag = 0U;
            scd_event_handle(pudev, puhost, pustate, CTRL_EVENT_ERROR, pustate->usbh_current_state);
        } else {
            /* no operation */
        }
    }
}

/*!
    \brief      the handle function of CTRL_DATA state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
static void ctrl_data_handle (usb_core_handle_struct *pudev, 
                              usbh_host_struct *puhost, 
                              usbh_state_handle_struct *pustate)
{
    uint8_t direction;  
    urb_state_enum urb_status = URB_IDLE;
    puhost->usbh_backup_state.ctrl_backup_state = CTRL_DATA;
  
    direction = (puhost->control.setup.b.bmRequestType & USB_DIR_MASK);
    
    if (USB_DIR_IN == direction) {
        if (0U == ctrl_data_wait_flag) {
            ctrl_data_wait_flag = 1U;

            /* issue an IN token */ 
            usbh_xfer(pudev,
                      puhost->control.buff,
                      puhost->control.hc_in_num,
                      puhost->control.length);
        } else {
            urb_status = hcd_urb_state_get(pudev, puhost->control.hc_in_num);

            /* check is data packet transfered successfully */
            switch (urb_status) {
                case URB_DONE:
                    ctrl_data_wait_flag = 0U;

                    scd_event_handle(pudev, 
                                     puhost, 
                                     pustate, 
                                     CTRL_EVENT_STATUS, 
                                     pustate->usbh_current_state);
                    break;
                case URB_STALL:
                    ctrl_data_wait_flag = 0U;
   
                    scd_event_handle(pudev, 
                                     puhost, 
                                     pustate, 
                                     CTRL_EVENT_STALLED, 
                                     pustate->usbh_current_state);
                    break;
                case URB_ERROR:
                    ctrl_data_wait_flag = 0U;

                    /* device error */
                    scd_event_handle(pudev, 
                                     puhost, 
                                     pustate, 
                                     CTRL_EVENT_ERROR, 
                                     pustate->usbh_current_state);
                    break;
                default:
                    if (((uint16_t)USB_CURRENT_FRAME_GET() - puhost->control.timer) > timeout) {
                        ctrl_data_wait_flag = 0U;

                        /* timeout for IN transfer */
                        scd_event_handle(pudev, 
                                         puhost, 
                                         pustate, 
                                         CTRL_EVENT_ERROR, 
                                         pustate->usbh_current_state);
                    }
                    break;
            }
        }
    } else {
        if (0U == ctrl_data_wait_flag) {
            ctrl_data_wait_flag = 1U;

            /* start DATA out transfer (only one DATA packet)*/
            pudev->host.host_channel[puhost->control.hc_out_num].data_tg_out = 1U; 

            usbh_xfer(pudev,
                      puhost->control.buff,
                      puhost->control.hc_out_num,
                      puhost->control.length);
        } else {
            urb_status = hcd_urb_state_get(pudev, puhost->control.hc_out_num);

            switch (urb_status) {
                case URB_DONE:
                    ctrl_data_wait_flag = 0U;

                    /* if the setup pkt is sent successful, then change the state */
                    scd_event_handle(pudev, 
                                     puhost, 
                                     pustate, 
                                     CTRL_EVENT_STATUS, 
                                     pustate->usbh_current_state);
                    break;
                case URB_STALL:
                    ctrl_data_wait_flag = 0U;

                    scd_event_handle(pudev, 
                                     puhost, 
                                     pustate, 
                                     CTRL_EVENT_STALLED, 
                                     pustate->usbh_current_state);
                    break;
                case URB_NOTREADY:
                    /* nack received from device */
                    ctrl_data_wait_flag = 0U;
                    break;
                case URB_ERROR:
                    ctrl_data_wait_flag = 0U;

                    /* device error */
                    scd_event_handle(pudev, 
                                     puhost, 
                                     pustate, 
                                     CTRL_EVENT_ERROR, 
                                     pustate->usbh_current_state);
                    break;
                default:
                    break;
            }
        }
    }
}

/*!
    \brief      the handle function of CTRL_STATUS state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
static void ctrl_status_handle (usb_core_handle_struct *pudev, 
                                usbh_host_struct *puhost, 
                                usbh_state_handle_struct *pustate)
{
    uint8_t direction;  
    urb_state_enum urb_status = URB_IDLE;
  
    puhost->usbh_backup_state.ctrl_backup_state = CTRL_STATUS;

    /* get the transfer direction in the data state, but the transfer direction in the status state is opposite */
    direction = (puhost->control.setup.b.bmRequestType & USB_DIR_MASK);

    if (USB_DIR_OUT == direction) {
        /* handle status in */
        if (0U == ctrl_status_wait_flag) {
            ctrl_status_wait_flag = 1U;
            usbh_xfer (pudev, 0U, puhost->control.hc_in_num, 0U);
        } else {
            urb_status = hcd_urb_state_get(pudev, puhost->control.hc_in_num); 

            switch (urb_status) {
                case URB_DONE:
                    ctrl_status_wait_flag = 0U;

                    /* handle URB_DONE status */
                    scd_event_handle(pudev, 
                                     puhost, 
                                     pustate, 
                                     CTRL_EVENT_COMPLETE, 
                                     pustate->usbh_current_state);
                    break;
                case URB_ERROR:
                    ctrl_status_wait_flag = 0U;

                    /* handle URB_STALL status*/
                    scd_event_handle(pudev, 
                                     puhost, 
                                     pustate, 
                                     CTRL_EVENT_ERROR, 
                                     pustate->usbh_current_state);
                    break;
                case URB_STALL:
                    ctrl_status_wait_flag = 0U;

                    /* handle URB_STALL status */
                    scd_event_handle(pudev, 
                                     puhost, 
                                     pustate, 
                                     CTRL_EVENT_STALLED, 
                                     pustate->usbh_current_state);
                    break;
                default:
                    if (((uint16_t)USB_CURRENT_FRAME_GET() - puhost->control.timer) > timeout) {
                        ctrl_status_wait_flag = 0U;

                        /* handle timeout */
                        scd_event_handle(pudev, 
                                         puhost, 
                                         pustate, 
                                         CTRL_EVENT_ERROR, 
                                         pustate->usbh_current_state);
                    }
                    break;
            }
        }
    } else {
        /* handle status out */
        if (0U == ctrl_status_wait_flag) {
            ctrl_status_wait_flag = 1U;
            pudev->host.host_channel[puhost->control.hc_out_num].data_tg_out ^= 1U;
            usbh_xfer (pudev, 0U, puhost->control.hc_out_num, 0U);

            {
                uint32_t host_ctlr = 0;

                host_ctlr = USB_HCHxLEN(puhost->control.hc_out_num);
                USB_HCHxLEN(puhost->control.hc_out_num) = host_ctlr | 1;
                host_ctlr = USB_HCHxCTL(puhost->control.hc_out_num);
                USB_HCHxCTL(puhost->control.hc_out_num) = (host_ctlr & 0x3FFFFFFF) | 0x80000000;
            }
        } else {
            urb_status = hcd_urb_state_get(pudev, puhost->control.hc_out_num);

            switch (urb_status) {
                case URB_DONE:
                    ctrl_status_wait_flag = 0U;

                    /* handle URB_DONE status */
                    scd_event_handle(pudev, 
                                     puhost, 
                                     pustate, 
                                     CTRL_EVENT_COMPLETE, 
                                     pustate->usbh_current_state);
                    break;
                case URB_NOTREADY:
                    /* handle URB_NOTREADY status */
                    ctrl_status_wait_flag = 0U;
                    break;
                case URB_ERROR:
                    ctrl_status_wait_flag = 0U;

                    /* handle URB_ERROR status */
                    scd_event_handle(pudev, 
                                     puhost, 
                                     pustate, 
                                     CTRL_EVENT_ERROR, 
                                     pustate->usbh_current_state);
                    break;
                default:
                    break;
            }
        }
    }
}

/*!
    \brief      the handle function of CTRL_ERROR state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
static void ctrl_error_handle (usb_core_handle_struct *pudev, 
                               usbh_host_struct *puhost, 
                               usbh_state_handle_struct *pustate)
{
    puhost->usbh_backup_state.ctrl_backup_state = CTRL_ERROR;

    if (++puhost->control.error_count <= USBH_MAX_ERROR_COUNT) {
        /* do the transmission again, starting from SETUP Packet */
        scd_event_handle(pudev, puhost, pustate, CTRL_EVENT_SETUP, pustate->usbh_current_state);
    } else {
        scd_event_handle(pudev, puhost, pustate, GO_TO_UP_STATE_EVENT, pustate->usbh_current_state);
    }
}

/*!
    \brief      the handle function of CTRL_STALLED state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
static void ctrl_stalled_handle (usb_core_handle_struct *pudev, 
                                 usbh_host_struct *puhost, 
                                 usbh_state_handle_struct *pustate)
{
    puhost->usbh_backup_state.ctrl_backup_state = CTRL_STALLED;
    scd_event_handle(pudev, puhost, pustate, GO_TO_UP_STATE_EVENT, pustate->usbh_current_state);
}

/*!
    \brief      the handle function of CTRL_COMPLETE state
    \param[in]  pudev: pointer to usb device
    \param[in]  puhost: pointer to usb host
    \param[in]  pustate: pointer to usb state driver
    \param[out] none
    \retval     none
*/
static void ctrl_complete_handle (usb_core_handle_struct *pudev, 
                                  usbh_host_struct *puhost, 
                                  usbh_state_handle_struct *pustate)
{
    puhost->usbh_backup_state.ctrl_backup_state = CTRL_COMPLETE;
    scd_event_handle(pudev, puhost, pustate, GO_TO_UP_STATE_EVENT, pustate->usbh_current_state);
}

/*!
    \brief      send datas from the host channel
    \param[in]  pudev: pointer to usb device
    \param[in]  buf: data buffer address to send datas
    \param[in]  hc_num: the number of the host channel
    \param[in]  len: length of the send data
    \param[out] none
    \retval     host operation status
*/
usbh_status_enum usbh_xfer (usb_core_handle_struct *pudev, 
                       uint8_t *buf, 
                       uint8_t  hc_num,
                       uint16_t len)
{
    usb_hostchannel_struct *puhc = &pudev->host.host_channel[hc_num];

    puhc->xfer_buff = buf;
    puhc->xfer_len = len;

    switch (puhc->endp_type) {
        case USB_EPTYPE_CTRL:
            if (0U == puhc->endp_in) {
                if (0U == len) {
                    /* for status out stage, length = 0, status out pid = 1 */
                    puhc->data_tg_out = 1U;
                }

                /* set the data toggle bit as per the flag */
                if (0U == puhc->data_tg_out) {
                    /* put the pid 0 */
                    puhc->DPID = HC_PID_DATA0;
                } else {
                    /* put the pid 1 */
                    puhc->DPID = HC_PID_DATA1;
                }
            } else {
                puhc->DPID = HC_PID_DATA1;
            }
            break;

        case USB_EPTYPE_ISOC:
            puhc->DPID = HC_PID_DATA0;
            break;

        case USB_EPTYPE_BULK:
            if (0U == puhc->endp_in) {
                /* set the data toggle bit as per the flag */
                if (0U == puhc->data_tg_out) {
                    /* put the pid 0 */
                    puhc->DPID = HC_PID_DATA0;
                } else {
                    /* put the pid 1 */
                    puhc->DPID = HC_PID_DATA1;
                }
            } else {
                if (0U == puhc->data_tg_in) {
                    puhc->DPID = HC_PID_DATA0;
                } else {
                    puhc->DPID = HC_PID_DATA1;
                }
            }
            break;

        case USB_EPTYPE_INTR:
            if (0U == puhc->endp_in) {
                if (0U == puhc->data_tg_out) {
                    puhc->DPID = HC_PID_DATA0;
                } else {
                    puhc->DPID = HC_PID_DATA1;
                }

                /* toggle data pid */
                puhc->data_tg_out ^= 1U;
            } else {
                if (0U == puhc->data_tg_in) {
                    puhc->DPID = HC_PID_DATA0;
                } else {
                    puhc->DPID = HC_PID_DATA1;
                }

                /* toggle data pid */
                puhc->data_tg_in ^= 1U;
            }
            break;

        default:
            break;
    }

    hcd_submit_request (pudev, hc_num);

    return USBH_OK;
}

/*!
    \brief      send the setup packet to the device
    \param[in]  pudev: pointer to usb device
    \param[in]  buf: buffer pointer from which the data will be send to device
    \param[in]  hc_num: host channel number
    \param[out] none
    \retval     host operation status
*/
usbh_status_enum usbh_ctltx_setup (usb_core_handle_struct *pudev, uint8_t *buf, uint8_t  hc_num)
{
    usb_hostchannel_struct *puhc = &pudev->host.host_channel[hc_num];

    puhc->DPID = HC_PID_SETUP;
    puhc->xfer_buff = buf;
    puhc->xfer_len = USBH_SETUP_PACKET_SIZE;

    return (usbh_status_enum)hcd_submit_request (pudev, hc_num);
}

/*!
    \brief      this function prepare a hc and start a transfer
    \param[in]  pudev: pointer to usb device
    \param[in]  channel_num: host channel number which is in (0..7)
    \param[out] none
    \retval     host operation status
*/
uint32_t hcd_submit_request (usb_core_handle_struct *pudev, uint8_t channel_num) 
{
    usb_hostchannel_struct *puhc = &pudev->host.host_channel[channel_num];

    puhc->urb_state = URB_IDLE;
    puhc->xfer_count = 0U;

    return (uint32_t)usb_hostchannel_startxfer(pudev, channel_num);
}
