/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*---------------------------------------------------------------------
 * Include
 *---------------------------------------------------------------------
 */
#include "hpm_usb_device.h"
#include "hpm_misc.h"
#include "hpm_common.h"

/* Initialize qtd */
static void usb_qtd_init(dcd_qtd_t *p_qtd, void *data_ptr, uint16_t total_bytes)
{
    memset(p_qtd, 0, sizeof(dcd_qtd_t));

    p_qtd->next        = USB_SOC_DCD_QTD_NEXT_INVALID;
    p_qtd->active      = 1;
    p_qtd->total_bytes = p_qtd->expected_bytes = total_bytes;

    if (data_ptr != NULL) {
        p_qtd->buffer[0]   = (uint32_t)data_ptr;
        for (uint8_t i = 1; i < USB_SOC_DCD_QHD_BUFFER_COUNT; i++) {
            p_qtd->buffer[i] |= ((p_qtd->buffer[i-1]) & 0xFFFFF000UL) + 4096U;
        }
    }
}

/*---------------------------------------------------------------------
 * Device API
 *---------------------------------------------------------------------
 */
dcd_qhd_t *usb_device_qhd_get(usb_device_handle_t *handle, uint8_t ep_idx)
{
    return &handle->dcd_data->qhd[ep_idx];
}

dcd_qtd_t *usb_device_qtd_get(usb_device_handle_t *handle, uint8_t ep_idx)
{
    return &handle->dcd_data->qtd[ep_idx * USB_SOC_DCD_QTD_COUNT_EACH_ENDPOINT];
}

void usb_device_bus_reset(usb_device_handle_t *handle, uint16_t ep0_max_packet_size)
{
    dcd_data_t *dcd_data = handle->dcd_data;

    usb_dcd_bus_reset(handle->regs, ep0_max_packet_size);

     /* Queue Head & Queue TD */
    memset(dcd_data, 0, sizeof(dcd_data_t));

    /* Set up Control Endpoints (0 OUT, 1 IN) */
    dcd_data->qhd[0].zero_length_termination = dcd_data->qhd[1].zero_length_termination = 1;
    dcd_data->qhd[0].max_packet_size         = dcd_data->qhd[1].max_packet_size         = ep0_max_packet_size;
    dcd_data->qhd[0].qtd_overlay.next        = dcd_data->qhd[1].qtd_overlay.next        = USB_SOC_DCD_QTD_NEXT_INVALID;

    /* OUT only */
    dcd_data->qhd[0].int_on_setup = 1;
}

bool usb_device_init(usb_device_handle_t *handle, uint32_t int_mask)
{
    /* Clear memroy */
    if (handle->dcd_data == NULL) {
        return false;
    }

    memset(handle->dcd_data, 0, sizeof(dcd_data_t));

    /* Initialize controller in device mode */
    usb_dcd_init(handle->regs);

    /* Set endpoint list address */
    usb_dcd_set_edpt_list_addr(handle->regs, core_local_mem_to_sys_address(0,  (uint32_t)handle->dcd_data->qhd));

    /* Clear status */
    usb_clear_status_flags(handle->regs, usb_get_status_flags(handle->regs));

    /* Enable interrupt mask */
    usb_enable_interrupts(handle->regs, int_mask);

    /* Connect */
    usb_dcd_connect(handle->regs);

    return true;
}

void usb_device_deinit(usb_device_handle_t *handle)
{
    /* Clear memroy */
    memset(handle->dcd_data, 0, sizeof(dcd_data_t));

    usb_dcd_deinit(handle->regs);

    for (uint32_t i = 0; i < USB_SOC_DCD_MAX_ENDPOINT_COUNT; i++) {
        usb_dcd_edpt_close(handle->regs, (i | (usb_dir_in  << 0x07)));
        usb_dcd_edpt_close(handle->regs, (i | (usb_dir_out << 0x07)));
    }
}

uint32_t usb_device_status_flags(usb_device_handle_t *handle)
{
    return usb_get_status_flags(handle->regs);
}

void usb_device_clear_status_flags(usb_device_handle_t *handle, uint32_t mask)
{
    usb_clear_status_flags(handle->regs, mask);
}

uint32_t usb_device_interrupts(usb_device_handle_t *handle)
{
    return usb_get_interrupts(handle->regs);
}

uint8_t usb_device_get_port_speed(usb_device_handle_t *handle)
{
    return usb_get_port_speed(handle->regs);
}

uint8_t usb_device_get_suspend_status(usb_device_handle_t *handle)
{
    return usb_get_suspend_status(handle->regs);
}

void usb_device_set_address(usb_device_handle_t *handle, uint8_t dev_addr)
{
    /* Response with status first before changing device address */
    usb_device_edpt_xfer(handle, 0 | usb_dir_in_mask, NULL, 0);

    usb_dcd_set_address(handle->regs, dev_addr);
}

uint8_t usb_device_get_address(usb_device_handle_t *handle)
{
    return usb_dcd_get_device_addr(handle->regs);
}

void usb_device_remote_wakeup(usb_device_handle_t *handle)
{
    usb_dcd_remote_wakeup(handle->regs);
}

void usb_device_connect(usb_device_handle_t *handle)
{
    usb_dcd_connect(handle->regs);
}

void usb_device_disconnect(usb_device_handle_t *handle)
{
    usb_dcd_disconnect(handle->regs);
}

bool usb_device_get_port_ccs(usb_device_handle_t *handle)
{
    return usb_get_port_ccs(handle->regs);
}

bool usb_device_get_port_reset_status(usb_device_handle_t *handle)
{
    return usb_get_port_reset_status(handle->regs);
}

uint32_t usb_device_get_edpt_complete_status(usb_device_handle_t *handle)
{
    return usb_dcd_get_edpt_complete_status(handle->regs);
}

void usb_device_clear_edpt_complete_status(usb_device_handle_t *handle, uint32_t mask)
{
    usb_dcd_clear_edpt_complete_status(handle->regs, mask);
}

uint32_t usb_device_get_setup_status(usb_device_handle_t *handle)
{
    return usb_dcd_get_edpt_setup_status(handle->regs);
}

void usb_device_clear_setup_status(usb_device_handle_t *handle, uint32_t mask)
{
    usb_dcd_clear_edpt_setup_status(handle->regs, mask);
}

/*---------------------------------------------------------------------
 * Endpoint API
 *---------------------------------------------------------------------
 */
bool usb_device_edpt_open(usb_device_handle_t *handle, usb_endpoint_config_t *config)
{
    uint8_t const epnum  = config->ep_addr & 0x0f;
    uint8_t const dir = (config->ep_addr & 0x80) >> 7;
    uint8_t const ep_idx = 2 * epnum + dir;

    dcd_qhd_t *p_qhd;

    /* Must not exceed max endpoint number */
    if (epnum >= USB_SOC_DCD_MAX_ENDPOINT_COUNT) {
        return false;
    }

    /* Prepare Queue Head */
    p_qhd = &handle->dcd_data->qhd[ep_idx];
    memset(p_qhd, 0, sizeof(dcd_qhd_t));

    p_qhd->zero_length_termination = 1;
    p_qhd->max_packet_size         = config->max_packet_size & 0x7FFu;
    p_qhd->qtd_overlay.next        = USB_SOC_DCD_QTD_NEXT_INVALID;
    if (config->xfer == usb_xfer_isochronous) {
        p_qhd->iso_mult = ((config->max_packet_size >> 11u) & 0x3u) + 1u;
    }

    usb_dcd_edpt_open(handle->regs, config);

    return true;
}

bool usb_device_edpt_xfer(usb_device_handle_t *handle, uint8_t ep_addr, uint8_t *buffer, uint32_t total_bytes)
{
    uint8_t const epnum = ep_addr & 0x0f;
    uint8_t const dir   = (ep_addr & 0x80) >> 7;
    uint8_t const ep_idx = 2 * epnum + dir;
    uint8_t qtd_num;
    uint8_t i;
    uint32_t xfer_len;
    dcd_qhd_t *p_qhd;
    dcd_qtd_t *p_qtd;
    dcd_qtd_t *first_p_qtd = NULL;
    dcd_qtd_t *prev_p_qtd = NULL;

    if (epnum == 0) {
        /* follows UM Setup packet handling using setup lockout mechanism
         * wait until ENDPTSETUPSTAT before priming data/status in response TODO add time out
         */
        while (usb_dcd_get_edpt_setup_status(handle->regs) & HPM_BITSMASK(1, 0)) {
        }
    }

    qtd_num = (total_bytes + 0x3fff) / 0x4000;
    if (qtd_num > USB_SOC_DCD_QTD_COUNT_EACH_ENDPOINT) {
        return false;
    }

    if (buffer != NULL) {
        buffer = (uint8_t *)core_local_mem_to_sys_address(0, (uint32_t)buffer);
    }
    p_qhd = &handle->dcd_data->qhd[ep_idx];
    i = 0;
    do {
        p_qtd = &handle->dcd_data->qtd[ep_idx * USB_SOC_DCD_QTD_COUNT_EACH_ENDPOINT + i];
        i++;

        if (total_bytes > 0x4000) {
            xfer_len = 0x4000;
            total_bytes -= 0x4000;
        } else {
            xfer_len = total_bytes;
            total_bytes = 0;
        }

        usb_qtd_init(p_qtd, (void *)buffer, xfer_len);
        if (total_bytes == 0) {
            p_qtd->int_on_complete = true;
        }
        buffer += xfer_len;

        if (prev_p_qtd) {
            prev_p_qtd->next = (uint32_t)p_qtd;
        } else {
            first_p_qtd = p_qtd;
        }
        prev_p_qtd = p_qtd;
    } while (total_bytes > 0);

    p_qhd->qtd_overlay.next = core_local_mem_to_sys_address(0, (uint32_t) first_p_qtd); /* link qtd to qhd */

    usb_dcd_edpt_xfer(handle->regs, ep_idx);

    return true;
}

void usb_device_edpt_stall(usb_device_handle_t *handle, uint8_t ep_addr)
{
    usb_dcd_edpt_stall(handle->regs, ep_addr);
}

void usb_device_edpt_clear_stall(usb_device_handle_t *handle, uint8_t ep_addr)
{
    usb_dcd_edpt_clear_stall(handle->regs, ep_addr);
}

bool usb_device_edpt_check_stall(usb_device_handle_t *handle, uint8_t ep_addr)
{
    return usb_dcd_edpt_check_stall(handle->regs, ep_addr);
}

void usb_device_edpt_close(usb_device_handle_t *handle, uint8_t ep_addr)
{
    usb_dcd_edpt_close(handle->regs, ep_addr);
}

void usb_device_edpt_close_all(usb_device_handle_t *handle)
{
    for (uint32_t i = 1; i < USB_SOC_DCD_MAX_ENDPOINT_COUNT; i++) {
        usb_device_edpt_close(handle, i);
    }
}
