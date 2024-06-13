/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_USB_DEVICE_H
#define HPM_USB_DEVICE_H

/*---------------------------------------------------------------------
 * Includes
 *---------------------------------------------------------------------
 */
#include "hpm_usb_drv.h"
#include "hpm_soc_feature.h"
/*---------------------------------------------------------------------
 *  Macro Constant Declarations
 *---------------------------------------------------------------------
 */

/*---------------------------------------------------------------------
 * Macro Typedef Declaration
 *---------------------------------------------------------------------
 */

/* Queue Transfer Descriptor */
typedef struct {
    /* Word 0: Next QTD Pointer */
    volatile uint32_t next; /* Next link pointer This field contains the physical memory address of the next dTD to be processed */

    /* Word 1: qTQ Token */
    volatile uint32_t                      : 3;
    volatile uint32_t xact_err             : 1;
    volatile uint32_t                      : 1;
    volatile uint32_t buffer_err           : 1;
    volatile uint32_t halted               : 1;
    volatile uint32_t active               : 1;
    volatile uint32_t                      : 2;
    volatile uint32_t iso_mult_override    : 2  ; /* This field can be used for transmit ISOs to override the MULT field in the dQH. This field must be zero for all packet types that are not transmit-ISO. */
    volatile uint32_t                      : 3;
    volatile uint32_t int_on_complete      : 1;
    volatile uint32_t total_bytes          : 15;
    volatile uint32_t                      : 0;

    /* Word 2-6: Buffer Page Pointer List, Each element in the list is a 4K page aligned, physical memory address. The lower 12 bits in each pointer are reserved (except for the first one) as each memory pointer must reference the start of a 4K page */
    volatile uint32_t buffer[USB_SOC_DCD_QHD_BUFFER_COUNT];

    /*------------- DCD Area -------------*/
    volatile uint16_t expected_bytes;
    volatile uint8_t reserved[2];
} dcd_qtd_t;

/* Queue Head */
typedef struct {
    /* Word 0: Capabilities and Characteristics */

    volatile uint32_t                         : 15 ; /* Number of packets executed per transaction descriptor 00 - Execute N transactions as demonstrated by the USB variable length protocol where N is computed using Max_packet_length and the Total_bytes field in the dTD. 01 - Execute one transaction 10 - Execute two transactions 11 - Execute three transactions Remark: Non-isochronous endpoints must set MULT = 00. Remark: Isochronous endpoints must set MULT = 01, 10, or 11 as needed. */
    volatile uint32_t int_on_setup            : 1  ; /* Interrupt on setup This bit is used on control type endpoints to indicate if USBINT is set in response to a setup being received. */
    volatile uint32_t max_packet_size         : 11 ; /* This directly corresponds to the maximum packet size of the associated endpoint (wMaxPacketSize) */
    volatile uint32_t                         : 2;
    volatile uint32_t zero_length_termination : 1  ; /* This bit is used for non-isochronous endpoints to indicate when a zero-length packet is received to terminate transfers in case the total transfer length is “multiple”. 0 - Enable zero-length packet to terminate transfers equal to a multiple of Max_packet_length (default). 1 - Disable zero-length packet on transfers that are equal in length to a multiple Max_packet_length. */
    volatile uint32_t iso_mult                : 2;
    volatile uint32_t                         : 0;

    /* Word 1: Current qTD Pointer */
    volatile uint32_t qtd_addr;

    /* Word 2-9: Transfer Overlay */
    volatile dcd_qtd_t qtd_overlay;

    /* Word 10-11: Setup request (control OUT only) */
    volatile usb_control_request_t setup_request;

    /*--------------------------------------------------------------------
     * Due to the fact QHD is 64 bytes aligned but occupies only 48 bytes
     * thus there are 16 bytes padding free that we can make use of.
     *--------------------------------------------------------------------
     */
    volatile uint8_t reserved[16];
} dcd_qhd_t;

typedef struct {
    dcd_qhd_t qhd[USB_SOS_DCD_MAX_QHD_COUNT];
    dcd_qtd_t qtd[USB_SOC_DCD_MAX_QTD_COUNT];
} dcd_data_t;

typedef struct {
    USB_Type     *regs;
    dcd_data_t   *dcd_data;
} usb_device_handle_t;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*---------------------------------------------------------------------
 *   Exported Function Declarations
 *---------------------------------------------------------------------
 */
/* Get a qhd of the specifed endpoint */
dcd_qhd_t *usb_device_qhd_get(usb_device_handle_t *handle, uint8_t ep_idx);

/* Get a qtd of the specifed endpoint */
dcd_qtd_t *usb_device_qtd_get(usb_device_handle_t *handle, uint8_t ep_idx);

/* USB bus reset */
void usb_device_bus_reset(usb_device_handle_t *handle, uint16_t ep0_max_packet_size);

/* Initialize controller to device mode */
bool usb_device_init(usb_device_handle_t *handle, uint32_t int_mask);

/* De-initialize controller */
void usb_device_deinit(usb_device_handle_t *handle);

/* Set Address request */
void usb_device_set_address(usb_device_handle_t *handle, uint8_t dev_addr);

/* Get device address */
uint8_t usb_device_get_address(usb_device_handle_t *handle);

/* Wake up host */
void usb_device_remote_wakeup(usb_device_handle_t *handle);

/* Connect by enabling internal pull-up resistor on D+/D- */
void usb_device_connect(usb_device_handle_t *handle);

/* Disconnect by disabling internal pull-up resistor on D+/D- */
void usb_device_disconnect(usb_device_handle_t *handle);

/* Configure an endpoint */
bool usb_device_edpt_open(usb_device_handle_t *handle, usb_endpoint_config_t *config);

/* Submit a transfe */
bool usb_device_edpt_xfer(usb_device_handle_t *handle, uint8_t ep_addr, uint8_t *buffer, uint32_t total_bytes);

/* Stall endpoint */
void usb_device_edpt_stall(usb_device_handle_t *handle, uint8_t ep_addr);

/* clear stall */
void usb_device_edpt_clear_stall(usb_device_handle_t *handle, uint8_t ep_addr);

/* check stall */
bool usb_device_edpt_check_stall(usb_device_handle_t *handle, uint8_t ep_addr);

/* close a specified endpoint */
void usb_device_edpt_close(usb_device_handle_t *handle, uint8_t ep_addr);

void usb_device_edpt_close_all(usb_device_handle_t *handle);

uint32_t usb_device_status_flags(usb_device_handle_t *handle);

void usb_device_clear_status_flags(usb_device_handle_t *handle, uint32_t mask);

uint32_t usb_device_interrupts(usb_device_handle_t *handle);

uint8_t usb_device_get_port_speed(usb_device_handle_t *handle);

uint8_t usb_device_get_suspend_status(usb_device_handle_t *handle);

bool usb_device_get_port_ccs(usb_device_handle_t *handle);

bool usb_device_get_port_reset_status(usb_device_handle_t *handle);

uint32_t usb_device_get_edpt_complete_status(usb_device_handle_t *handle);

void usb_device_clear_edpt_complete_status(usb_device_handle_t *handle, uint32_t mask);

uint32_t usb_device_get_setup_status(usb_device_handle_t *handle);

void usb_device_clear_setup_status(usb_device_handle_t *handle, uint32_t mask);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* HPM_USB_DEVICE_H */
