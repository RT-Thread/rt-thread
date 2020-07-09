/*!
    \file  usbh_ctrl.h
    \brief header file for usbh_ctrl.c
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#ifndef USBH_CTRL_H
#define USBH_CTRL_H

#include "usbh_core.h"
#include "usbh_usr.h"

#define CTRL_HANDLE_TABLE_SIZE   13U    /*!< the ctrl handle table size define */

extern state_table_struct        ctrl_handle_table[CTRL_HANDLE_TABLE_SIZE];
extern uint8_t                   ctrl_polling_handle_flag;

/* the enum of CTRL event */
typedef enum 
{
    CTRL_EVENT_IDLE = 0,   /* the ctrl idle event */
    CTRL_EVENT_SETUP,      /* the ctrl setup event */
    CTRL_EVENT_DATA,       /* the ctrl data event */
    CTRL_EVENT_STATUS,     /* the ctrl status event */
    CTRL_EVENT_COMPLETE,   /* the ctrl complete event */
    CTRL_EVENT_ERROR,      /* the ctrl error event */
    CTRL_EVENT_STALLED,    /* the ctrl stalled event */
}ctrl_event_enum;

/* function declarations */
/* the polling function of control transfer state handle */
usbh_status_enum ctrl_state_polling_fun (usb_core_handle_struct *pudev, usbh_host_struct *puhost, void *pustate);
/* send datas from the host channel */
usbh_status_enum usbh_xfer (usb_core_handle_struct *pudev, uint8_t *buf, uint8_t  hc_num, uint16_t len);
/* send the setup packet to the device */
usbh_status_enum usbh_ctltx_setup (usb_core_handle_struct *pudev, uint8_t *buf, uint8_t  hc_num);
/* this function prepare a hc and start a transfer */
uint32_t  hcd_submit_request (usb_core_handle_struct *pudev, uint8_t channel_num);

#endif /* USBH_CTRL_H */
