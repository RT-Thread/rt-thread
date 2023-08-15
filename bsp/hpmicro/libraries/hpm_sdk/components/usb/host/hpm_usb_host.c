/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*---------------------------------------------------------------------
 * Includes
 *---------------------------------------------------------------------
 */
#include "hpm_usb_host.h"
#include "hpm_misc.h"
#include "hpm_common.h"
#include "board.h"

/*---------------------------------------------------------------------
 * Macros
 *---------------------------------------------------------------------
 */

#define USB_QHD_TYP_SHIFT           (1U)

#define USB_PERIOD_1MS              (1U)
#define USB_PERIOD_2MS              (2U)
#define USB_PERIOD_4MS              (4U)
#define USB_PERIOD_8MS              (8U)

#define USB_DEFAULT_ADDR            (0U)
#define USB_HIGH_SPPED_INTERVAL_MAX (16)
#define USB_SETUP_PACKET_LEN        (8U)

#define USB_BIN8(x)               ((uint8_t)  (0b##x))
#define USB_BIN16(b1, b2)         ((uint16_t) (0b##b1##b2))
#define USB_BIN32(b1, b2, b3, b4) ((uint32_t) (0b##b1##b2##b3##b4))

/* helper functions */
static uint8_t usb_log2(uint32_t value)
{
    uint8_t result = 0;

    while (value >>= 1) {
        result++;
    }

    return result;
}

/*****************************************************************************/
/*                             list functions                                */
/*****************************************************************************/
static void usb_host_list_insert(hcd_link_t *current, hcd_link_t *new, uint8_t new_type)
{
    new->address = current->address;
    current->address = core_local_mem_to_sys_address(USB_HOST_MCU_CORE, (uint32_t)new) | (new_type << USB_QHD_TYP_SHIFT);
}

static void usb_host_list_remove_qhd_by_addr(hcd_link_t *list_head, uint8_t dev_addr)
{
    hcd_qhd_t *qhd;

    for (hcd_link_t *prev = list_head;
        !prev->terminate && (sys_address_to_core_local_mem(USB_HOST_MCU_CORE, usb_host_align32(prev->address)) != (uint32_t)list_head);
        prev = (hcd_link_t *)sys_address_to_core_local_mem(USB_HOST_MCU_CORE, (uint32_t)usb_host_list_next(prev))) {

        /* TODO check type for ISO iTD and siTD */
        qhd = (hcd_qhd_t *)sys_address_to_core_local_mem(USB_HOST_MCU_CORE, (uint32_t)usb_host_list_next(prev));

        if (qhd->dev_addr == dev_addr) {
            /* TODO deactive all TD, wait for QHD to inactive before removal */
            prev->address = qhd->next.address;

            /* EHCI link the removed qhd to async head (which always reachable by Host Controller) */
            qhd->next.address = core_local_mem_to_sys_address(USB_HOST_MCU_CORE, (uint32_t)list_head) | (usb_qtype_qhd << USB_QHD_TYP_SHIFT);

            if (qhd->int_smask) {
                /* period list queue element is guarantee to be free in the next frame (1 ms) */
                qhd->used = 0;
            } else {
                /* async list use async advance handshake */
                /* mark as removing, will completely re-usable when async advance isr occurs */
                qhd->removing = 1;
            }
        }
    }
}

hcd_link_t *usb_host_list_next(hcd_link_t *p_link_pointer)
{
    return (hcd_link_t *)usb_host_align32(p_link_pointer->address);
}

/*************************************************************/
/*                      qhd functions                        */
/*************************************************************/
static hcd_qhd_t *usb_host_qhd_control(usb_host_handle_t *handle, uint8_t dev_addr)
{
    return &handle->hcd_data->control[dev_addr].qhd;
}

hcd_qhd_t *usb_host_qhd_next(hcd_qhd_t const *p_qhd)
{
    return (hcd_qhd_t *)usb_host_align32(p_qhd->next.address);
}

static hcd_qhd_t *usb_host_qhd_find_free(usb_host_handle_t *handle)
{
    for (uint32_t i = 0; i < USB_HCD_MAX_QHD_COUNT; i++) {
        if (!handle->hcd_data->qhd_pool[i].used) {
            return &handle->hcd_data->qhd_pool[i];
        }
    }

    return NULL;
}

static hcd_qhd_t *usb_host_qhd_get_from_addr(usb_host_handle_t *handle, uint8_t dev_addr, uint8_t ep_addr)
{
    hcd_qhd_t *qhd_pool = handle->hcd_data->qhd_pool;

    for (uint32_t i = 0; i < USB_HCD_MAX_QHD_COUNT; i++) {
        if ((qhd_pool[i].dev_addr == dev_addr) &&
                ep_addr == usb_edpt_addr(qhd_pool[i].ep_number, qhd_pool[i].pid)) {
            return &qhd_pool[i];
        }
    }

    return NULL;
}

static bool usb_host_qhd_init(usb_host_handle_t *handle, hcd_qhd_t *p_qhd, uint8_t dev_addr, usb_desc_endpoint_t const *ep_desc)
{
    uint8_t const xfer_type = ep_desc->bmAttributes.xfer;
    uint8_t const interval = ep_desc->bInterval;

    /* address 0 is used as async head, which always on the list --> cannot be cleared (ehci halted otherwise) */
    if (dev_addr != 0) {
        memset(p_qhd, 0, sizeof(hcd_qhd_t));
    }

    p_qhd->dev_addr              = dev_addr;
    p_qhd->fl_inactive_next_xact = 0;
    p_qhd->ep_number             = usb_edpt_number(ep_desc->bEndpointAddress);
    p_qhd->ep_speed              = handle->ep_speed;
    p_qhd->data_toggle_control   = (xfer_type == usb_xfer_control) ? 1 : 0;
    p_qhd->head_list_flag        = (dev_addr == USB_DEFAULT_ADDR) ? 1 : 0; /* addr0's endpoint is the static async list head */
    p_qhd->max_packet_size       = ep_desc->wMaxPacketSize.size;
    p_qhd->fl_ctrl_ep_flag       = ((xfer_type == usb_xfer_control) && (p_qhd->ep_speed != usb_speed_high))  ? 1 : 0;
    p_qhd->nak_reload            = 0;

    if (usb_xfer_interrupt == xfer_type) {
        if (usb_speed_high == p_qhd->ep_speed) {
            if (interval > USB_HIGH_SPPED_INTERVAL_MAX) {
                return false;
            }

            if (interval < 4) { /* sub millisecond interval */
                p_qhd->interval_ms = 0;
                p_qhd->int_smask   = (interval == 1) ? USB_BIN8(11111111) :
                                     (interval == 2) ? USB_BIN8(10101010) : USB_BIN8(01000100);
            } else {
                p_qhd->interval_ms = (uint8_t)MIN(1 << (interval - 4), 255);
                p_qhd->int_smask = HPM_BITSMASK(1, interval % 8);
            }
        } else {
            if (interval == 0) {
                return false;
            }

            /* Full/Low:(EHCI) case 1 schedule start split at 1 us & complete split at 2,3,4 uframes */
            p_qhd->int_smask    = 0x01;
            p_qhd->fl_int_cmask = USB_BIN8(11100);
            p_qhd->interval_ms  = interval;
        }
    } else {
        /* Bulk/Control -> smask = cmask = 0 */
        p_qhd->int_smask = p_qhd->fl_int_cmask = 0;
    }

    p_qhd->fl_hub_addr     = handle->hub_addr;
    p_qhd->fl_hub_port     = handle->hub_port;
    p_qhd->mult            = 1;

    /* HCD Management Data */
    p_qhd->used            = 1;
    p_qhd->removing        = 0;
    p_qhd->p_qtd_list_head = NULL;
    p_qhd->p_qtd_list_tail = NULL;
    p_qhd->pid = usb_edpt_dir(ep_desc->bEndpointAddress) ? usb_pid_in : usb_pid_out; /* PID for TD under this endpoint */

    /* Active, but no TD list */
    p_qhd->qtd_overlay.halted              = 0;
    p_qhd->qtd_overlay.next.terminate      = 1;
    p_qhd->qtd_overlay.alternate.terminate = 1;

    if (usb_xfer_bulk == xfer_type && p_qhd->ep_speed == usb_speed_high && p_qhd->pid == usb_pid_out) {
        p_qhd->qtd_overlay.ping_err = 1; /* Do PING for Highspeed Bulk OUT, EHCI */
    }

    return true;
}

hcd_qhd_t *usb_host_qhd_async_head(usb_host_handle_t *handle)
{
    /* control qhd of dev0 is used as async head */
    return usb_host_qhd_control(handle, 0);
}

bool usb_host_qhd_has_xact_error(hcd_qhd_t *p_qhd)
{
    return (p_qhd->qtd_overlay.buffer_err || p_qhd->qtd_overlay.babble_err || p_qhd->qtd_overlay.xact_err);
}

hcd_link_t *usb_host_get_period_head(usb_host_handle_t *handle, uint8_t interval_ms)
{
    return (hcd_link_t *)&handle->hcd_data->period_head_arr[usb_log2(MIN(USB_HOST_FRAMELIST_SIZE, interval_ms))];
}

/*************************************************************/
/*                      qtd functions                        */
/*************************************************************/
static hcd_qtd_t *usb_host_qtd_find_free(usb_host_handle_t *handle)
{
    for (uint32_t i = 0; i < USB_HCD_MAX_QTD_COUNT; i++) {
        if (!handle->hcd_data->qtd_pool[i].used) {
            return &handle->hcd_data->qtd_pool[i];
        }
    }

    return NULL;
}

static hcd_qtd_t *usb_host_qtd_next(hcd_qtd_t const *p_qtd)
{
    return (hcd_qtd_t *)usb_host_align32(p_qtd->next.address);
}

static void usb_host_qtd_insert_to_qhd(hcd_qhd_t *p_qhd, hcd_qtd_t *p_qtd_new)
{
    if (p_qhd->p_qtd_list_head == NULL) {   /* empty list */
        p_qhd->p_qtd_list_head               = p_qhd->p_qtd_list_tail = p_qtd_new;
    } else {
        p_qhd->p_qtd_list_tail->next.address = (uint32_t)p_qtd_new;
        p_qhd->p_qtd_list_tail               = p_qtd_new;
    }
}

static void usb_host_qtd_init(hcd_qtd_t *p_qtd, void *buffer, uint16_t total_bytes)
{
    memset(p_qtd, 0, sizeof(hcd_qtd_t));

    p_qtd->used                = 1;
    p_qtd->next.terminate      = 1; /* init to null */
    p_qtd->alternate.terminate = 1; /* not used, always set to terminated */
    p_qtd->active              = 1;
    p_qtd->err_count           = 3;
    p_qtd->data_toggle         = 0;
    p_qtd->total_bytes         = total_bytes;
    p_qtd->expected_bytes      = total_bytes;

    if (buffer != NULL) {
        p_qtd->buffer[0] = (uint32_t)buffer;

        for (uint8_t i = 1; i < USB_SOC_HCD_QTD_BUFFER_COUNT; i++) {
            p_qtd->buffer[i] |= usb_host_align4k(p_qtd->buffer[i-1]) + 4096UL;
        }
    }
}

void usb_host_qtd_remove_1st_from_qhd(hcd_qhd_t *p_qhd)
{
    if (p_qhd->p_qtd_list_head == p_qhd->p_qtd_list_tail)  { /* last TD --> make it NULL */
        p_qhd->p_qtd_list_head = p_qhd->p_qtd_list_tail = NULL;
    } else {
        p_qhd->p_qtd_list_head = usb_host_qtd_next(p_qhd->p_qtd_list_head);
    }
}

hcd_qtd_t *usb_host_qtd_control(usb_host_handle_t *handle, uint8_t dev_addr)
{
    return &handle->hcd_data->control[dev_addr].qtd;
}

static void usb_host_init_async_list(usb_host_handle_t *handle)
{
    hcd_qhd_t *async_head = usb_host_qhd_async_head(handle);

    memset(async_head, 0, sizeof(hcd_qhd_t));

    async_head->next.address                    = core_local_mem_to_sys_address(USB_HOST_MCU_CORE, (uint32_t)async_head);       /* circular list, next is itself */
    async_head->next.type                       = usb_qtype_qhd;
    async_head->head_list_flag                  = 1;
    async_head->qtd_overlay.halted              = 1;
    async_head->qtd_overlay.next.terminate      = 1;

    usb_hcd_set_async_list_addr(handle->regs, core_local_mem_to_sys_address(USB_HOST_MCU_CORE, (uint32_t)async_head));
}

static void usb_host_init_periodic_list(usb_host_handle_t *handle)
{
    hcd_link_t *framelist;
    hcd_link_t *period_1ms;

    /* Build the polling interval tree with 1 ms, 2 ms, 4 ms and 8 ms (framesize) only */
    for (uint32_t i = 0; i < 4; i++) {
        handle->hcd_data->period_head_arr[i].int_smask          = 1; /* queue head in period list must have non-zero smask */
        handle->hcd_data->period_head_arr[i].qtd_overlay.halted = 1; /* dummy node, always inactive */
    }

    framelist  = handle->hcd_data->period_framelist;
    period_1ms = usb_host_get_period_head(handle, USB_PERIOD_1MS);

    /* all links --> period_head_arr[0] (1ms)
     * 0, 2, 4, 6 etc --> period_head_arr[1] (2ms)
     * 1, 5 --> period_head_arr[2] (4ms)
     * 3 --> period_head_arr[3] (8ms)
     */
    for (uint32_t i = 0; i < USB_HOST_FRAMELIST_SIZE; i++) {
        framelist[i].address = core_local_mem_to_sys_address(USB_HOST_MCU_CORE, (uint32_t)period_1ms);
        framelist[i].type    = usb_qtype_qhd;
    }

    for (uint32_t i = 0; i < USB_HOST_FRAMELIST_SIZE; i += 2) {
        usb_host_list_insert(framelist + i, usb_host_get_period_head(handle, USB_PERIOD_2MS), usb_qtype_qhd);
    }

    for (uint32_t i = 1; i < USB_HOST_FRAMELIST_SIZE; i += 4) {
        usb_host_list_insert(framelist + i, usb_host_get_period_head(handle, USB_PERIOD_4MS), usb_qtype_qhd);
    }

    for (uint32_t i = 3; i < USB_HOST_FRAMELIST_SIZE; i += 8) {
        usb_host_list_insert(framelist + i, usb_host_get_period_head(handle, USB_PERIOD_8MS), usb_qtype_qhd);
    }

    period_1ms->terminate = 1;

    usb_hcd_set_periodic_list_addr(handle->regs, core_local_mem_to_sys_address(USB_HOST_MCU_CORE, (uint32_t)framelist));
}

/* enable vbus output */
static void usb_host_vbus_ctrl(usb_host_handle_t *handle)
{
    handle->hcd_vbus_ctrl_cb(handle->rhport, 1);
}

bool usb_host_init(usb_host_handle_t *handle, uint32_t int_mask, uint16_t framelist_size)
{
    usb_hcd_init(handle->regs, int_mask, framelist_size);
    memset(handle->hcd_data, 0, sizeof(hcd_data_t));
    usb_host_init_async_list(handle);
    usb_host_init_periodic_list(handle);
    usb_host_vbus_ctrl(handle);
    usb_hcd_run(handle->regs);
    usb_hcd_enable_port_power(handle->regs);
    return true;
}

void usb_host_port_reset(usb_host_handle_t *handle)
{
    usb_hcd_port_reset(handle->regs);
}

uint32_t usb_host_uframe_number(usb_host_handle_t *handle)
{
    return handle->hcd_data->uframe_number + usb_hcd_get_frame_index(handle->regs);
}

bool usb_host_get_port_ccs(usb_host_handle_t *handle)
{
    return usb_get_port_ccs(handle->regs);
}

bool usb_host_port_csc(usb_host_handle_t *handle)
{
    return usb_hcd_get_port_csc(handle->regs);
}

uint32_t usb_host_status_flags(usb_host_handle_t *handle)
{
    return usb_get_status_flags(handle->regs);
}

uint32_t usb_host_interrupts(usb_host_handle_t *handle)
{
    return usb_get_interrupts(handle->regs);
}

void usb_host_clear_status_flags(usb_host_handle_t *handle, uint32_t status)
{
    usb_clear_status_flags(handle->regs, status);
}

uint8_t usb_host_get_port_speed(usb_host_handle_t *handle)
{
    return usb_get_port_speed(handle->regs);
}

/* Close all opened endpoint belong to this device */
void usb_host_device_close(usb_host_handle_t *handle, uint8_t dev_addr)
{
    /* skip dev0 */
    if (dev_addr == USB_DEFAULT_ADDR) {
        return;
    }

    /* Remove from async list */
    usb_host_list_remove_qhd_by_addr((hcd_link_t *) usb_host_qhd_async_head(handle), dev_addr);

    /* Remove from all interval period list */
    for (uint8_t i = 0; i < ARRAY_SIZE(handle->hcd_data->period_head_arr); i++) {
        usb_host_list_remove_qhd_by_addr((hcd_link_t *)&handle->hcd_data->period_head_arr[i], dev_addr);
    }

    /* Async doorbell (EHCI for operational details) */
    usb_hcd_set_command(handle->regs, USB_USBCMD_IAA_MASK);
}

/*---------------------------------------------------------------------
 * Control Pipe API
 *---------------------------------------------------------------------
 */
bool usb_host_edpt_xfer(usb_host_handle_t *handle, uint8_t dev_addr, uint8_t ep_addr, uint8_t *buffer, uint16_t buflen)
{
    uint8_t const epnum = usb_edpt_number(ep_addr);
    uint8_t const dir   = usb_edpt_dir(ep_addr);
    hcd_qhd_t *qhd;
    hcd_qtd_t *qtd;
    hcd_qhd_t *p_qhd;
    hcd_qtd_t *p_qtd;

    if (buffer != NULL) {
        buffer = (uint8_t *)core_local_mem_to_sys_address(USB_HOST_MCU_CORE, (uint32_t)buffer);
    }

    if (epnum == 0) {
        qhd = usb_host_qhd_control(handle, dev_addr);
        qtd = usb_host_qtd_control(handle, dev_addr);

        usb_host_qtd_init(qtd, buffer, buflen);

        /* first first data toggle is always 1 (data & setup stage) */
        qtd->data_toggle = 1;
        qtd->pid = dir ? usb_pid_in : usb_pid_out;

        qtd->int_on_complete = 1;
        qtd->next.terminate  = 1;

        /* sw region */
        qhd->p_qtd_list_head = qtd;
        qhd->p_qtd_list_tail = qtd;

        /* attach TD */
        qhd->qtd_overlay.next.address = core_local_mem_to_sys_address(USB_HOST_MCU_CORE, (uint32_t)qtd);
    } else {
        p_qhd = usb_host_qhd_get_from_addr(handle, dev_addr, ep_addr);
        p_qtd = usb_host_qtd_find_free(handle);

        if (p_qhd == NULL || p_qtd == NULL) {
            return false;
        }

        usb_host_qtd_init(p_qtd, buffer, buflen);
        p_qtd->pid = p_qhd->pid;

        /* Insert TD to QH */
        usb_host_qtd_insert_to_qhd(p_qhd, p_qtd);
        p_qhd->p_qtd_list_tail->int_on_complete = 1;

        /* attach head QTD to QHD start transferring */
        p_qhd->qtd_overlay.next.address = core_local_mem_to_sys_address(USB_HOST_MCU_CORE, (uint32_t)p_qhd->p_qtd_list_head);
    }

    return true;
}

bool usb_host_setup_send(usb_host_handle_t *handle, uint8_t dev_addr, const uint8_t *setup_packet)
{
    uint32_t *p = NULL;

    hcd_qhd_t *qhd = &handle->hcd_data->control[dev_addr].qhd;
    hcd_qtd_t *td  = &handle->hcd_data->control[dev_addr].qtd;

    if (setup_packet != NULL) {
        p = (uint32_t *)core_local_mem_to_sys_address(USB_HOST_MCU_CORE, (uint32_t)setup_packet);
    }

    usb_host_qtd_init(td, (void *)p, USB_SETUP_PACKET_LEN);
    td->pid             = usb_pid_setup;
    td->int_on_complete = 1;
    td->next.terminate  = 1;

    /* sw region */
    qhd->p_qtd_list_head = td;
    qhd->p_qtd_list_tail = td;

    /* attach TD */
    qhd->qtd_overlay.next.address = core_local_mem_to_sys_address(USB_HOST_MCU_CORE, (uint32_t)td);

    return true;
}

bool usb_host_edpt_open(usb_host_handle_t *handle, uint8_t dev_addr, usb_desc_endpoint_t const *ep_desc)
{
    hcd_qhd_t *p_qhd = NULL;
    hcd_link_t *list_head = NULL;

    if (ep_desc->bmAttributes.xfer == usb_xfer_isochronous) {
        return false;
    }

    /* Prepare Queue Head */
    if (ep_desc->bEndpointAddress == 0) {
        p_qhd = usb_host_qhd_control(handle, dev_addr);
    } else {
        p_qhd = usb_host_qhd_find_free(handle);
    }

    /* Initialize Qhd */
    usb_host_qhd_init(handle, p_qhd, dev_addr, ep_desc);

    switch (ep_desc->bmAttributes.xfer) {
    case usb_xfer_control:
    case usb_xfer_bulk:
        list_head = (hcd_link_t *)usb_host_qhd_async_head(handle);   /* control of dev0 is always present as async head */
        break;

    case usb_xfer_interrupt:
        list_head = usb_host_get_period_head(handle, p_qhd->interval_ms);
        break;

    case usb_xfer_isochronous:
        break;

    default:
        break;
    }

    /* Insert to list */
    usb_host_list_insert(list_head, (hcd_link_t *)p_qhd, usb_qtype_qhd);

    return true;
}

bool usb_host_pipe_queue_xfer(usb_host_handle_t *handle, uint8_t dev_addr, uint8_t ep_addr, uint8_t buffer[], uint16_t total_bytes)
{
    hcd_qhd_t *p_qhd = usb_host_qhd_get_from_addr(handle, dev_addr, ep_addr);
    hcd_qtd_t *p_qtd = usb_host_qtd_find_free(handle);

    if (p_qhd == NULL || p_qtd == NULL) {
        return false;
    }

    /* Initialize QTD */
    usb_host_qtd_init(p_qtd, buffer, total_bytes);
    p_qtd->pid = p_qhd->pid;

    /* Insert TD to TD list */
    usb_host_qtd_insert_to_qhd(p_qhd, p_qtd);

    return true;
}

bool usb_host_pipe_xfer(usb_host_handle_t *handle, uint8_t dev_addr, uint8_t ep_addr, uint8_t buffer[], uint16_t total_bytes, bool int_on_complete)
{
    hcd_qhd_t *p_qhd = usb_host_qhd_get_from_addr(handle, dev_addr, ep_addr);

    if (usb_host_pipe_queue_xfer(handle, dev_addr, ep_addr, buffer, total_bytes) == false) {
        return false;
    }

    if (int_on_complete) {
        /* the just added qtd is pointed by list_tail */
        p_qhd->p_qtd_list_tail->int_on_complete = 1;
    }

    /* attach head QTD to QHD start transferring */
    p_qhd->qtd_overlay.next.address = core_local_mem_to_sys_address(USB_HOST_MCU_CORE, (uint32_t)p_qhd->p_qtd_list_head);

    return true;
}

bool usb_host_edpt_busy(usb_host_handle_t *handle, uint8_t dev_addr, uint8_t ep_addr)
{
    hcd_qhd_t *p_qhd = usb_host_qhd_get_from_addr(handle, dev_addr, ep_addr);

    return ((!p_qhd->qtd_overlay.halted) && (p_qhd->p_qtd_list_head != NULL));
}

bool usb_host_edpt_stalled(usb_host_handle_t *handle, uint8_t dev_addr, uint8_t ep_addr)
{
    hcd_qhd_t *p_qhd = usb_host_qhd_get_from_addr(handle, dev_addr, ep_addr);

    return p_qhd->qtd_overlay.halted && !usb_host_qhd_has_xact_error(p_qhd);
}

bool usb_host_edpt_clear_stall(usb_host_handle_t *handle, uint8_t dev_addr, uint8_t ep_addr)
{
    hcd_qhd_t *p_qhd = usb_host_qhd_get_from_addr(handle, dev_addr, ep_addr);

    p_qhd->qtd_overlay.halted = 0;

    return true;
}
