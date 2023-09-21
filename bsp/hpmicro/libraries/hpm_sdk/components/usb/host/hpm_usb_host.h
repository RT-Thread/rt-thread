/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_USB_HOST_H
#define HPM_USB_HOST_H

/*---------------------------------------------------------------------
 * Includes
 *---------------------------------------------------------------------
 */
#include "hpm_usb_drv.h"
#include "hpm_common.h"
#include "hpm_soc_feature.h"

/*---------------------------------------------------------------------
 * Macros
 *---------------------------------------------------------------------
 */


#ifndef USB_HCD_PERIODIC_ARR_COUNT
#define USB_HCD_PERIODIC_ARR_COUNT     (4U)
#endif

#ifndef USB_HCD_MAX_CONNECTED_DEVICES
#define USB_HCD_MAX_CONNECTED_DEVICES  (5U)
#endif

#ifndef USB_HCD_MAX_QHD_COUNT
#define USB_HCD_MAX_QHD_COUNT          (USB_HCD_MAX_CONNECTED_DEVICES * 16U * 2U)
#endif

#ifndef USB_HCD_MAX_QTD_COUNT
#define USB_HCD_MAX_QTD_COUNT          (USB_HCD_MAX_QHD_COUNT * 2U)
#endif
/*---------------------------------------------------------------------
 * Enum Declarations
 *---------------------------------------------------------------------
 */
typedef enum {
    usb_max_itd  = 4,
    usb_max_sitd = 16
} usb_max_xtd_t;

typedef enum {
    usb_qtype_itd = 0,
    usb_qtype_qhd,
    usb_qtype_sitd,
    usb_qtype_fstn
} usb_qtype_t;

typedef enum {
    usb_pid_out = 0,
    usb_pid_in,
    usb_pid_setup
} usb_pid_t;

typedef enum {
    usb_speed_full = 0,
    usb_speed_low,
    usb_speed_high,
    usb_speed_invalid = 0xff,
} usb_speed_t;

typedef enum  {
    usb_cmd_pos_run_stop               = 0,
    usb_cmd_pos_framelist_szie         = 2,
    usb_cmd_pos_period_enable          = 4,
    usb_cmd_pos_async_enable           = 5,
    usb_cmd_pos_framelist_size_msb     = 15,
    usb_cmd_pos_interrupt_threshold    = 16
} usb_cmd_pos_t;

typedef enum {
    usb_portsc_mask_current_connect_status = HPM_BITSMASK(1, 0),
    usb_portsc_mask_connect_status_change  = HPM_BITSMASK(1, 1),
    usb_portsc_mask_port_eanbled           = HPM_BITSMASK(1, 2),
    usb_portsc_mask_port_enable_chagne     = HPM_BITSMASK(1, 3),
    usb_portsc_mask_over_current_change    = HPM_BITSMASK(1, 5),
    usb_portsc_mask_port_reset             = HPM_BITSMASK(1, 8),

    usb_portsc_mask_all                    = usb_portsc_mask_connect_status_change
                                           | usb_portsc_mask_port_enable_chagne
                                           | usb_portsc_mask_over_current_change
} usb_portsc_change_mask_t;

/* Link pointer */
typedef union {
    volatile uint32_t address;
    struct  {
        volatile uint32_t terminate : 1;
        volatile uint32_t type      : 2;
    };
} hcd_link_t;

/* Queue Element Transfer Descriptor */
/* Qtd is used to declare overlay in hcd_qhd_t */
typedef struct {
    /* Word 0: Next QTD Pointer */
    volatile hcd_link_t next;

    /* Word 1: Alternate Next QTD Pointer (not used) */
    union{
        volatile hcd_link_t alternate;
        struct {
            volatile  uint32_t                : 5;
            volatile  uint32_t used           : 1;
            volatile  uint32_t                : 10;
            volatile  uint32_t expected_bytes : 16;
        };
    };

    /* Word 2: qTQ Token */
    volatile uint32_t ping_err             : 1  ; /* For Highspeed: 0 Out, 1 Ping. Full/Slow used as error indicator */
    volatile uint32_t non_hs_split_state   : 1  ; /* Used by HC to track the state of slipt transaction */
    volatile uint32_t non_hs_missed_uframe : 1  ; /* HC misses a complete slip transaction */
    volatile uint32_t xact_err             : 1  ; /* Error (Timeout, CRC, Bad PID ... ) */
    volatile uint32_t babble_err           : 1  ; /* Babble detected, also set Halted bit to 1 */
    volatile uint32_t buffer_err           : 1  ; /* Data overrun/underrun error */
    volatile uint32_t halted               : 1  ; /* Serious error or STALL received */
    volatile uint32_t active               : 1  ; /* Start transfer, clear by HC when complete */
    volatile uint32_t pid                  : 2  ; /* 0: OUT, 1: IN, 2 Setup */
    volatile uint32_t err_count            : 2  ; /* Error Counter of consecutive errors */
    volatile uint32_t current_page         : 3  ; /* Index into the qTD buffer pointer list */
    volatile uint32_t int_on_complete      : 1  ; /* Interrupt on complete */
    volatile uint32_t total_bytes          : 15 ; /* Transfer bytes, decreased during transaction */
    volatile uint32_t data_toggle          : 1  ; /* Data Toggle bit */

    /* Buffer Page Pointer List, Each element in the list is a 4K page aligned, physical memory address. The lower 12 bits in each pointer are reserved (except for the first one) as each memory pointer must reference the start of a 4K page */
    volatile uint32_t buffer[USB_SOC_HCD_QTD_BUFFER_COUNT];
} hcd_qtd_t;

/* Queue Head */
typedef struct {
    /* Word 0: Next QHD */
    hcd_link_t next;

    /* Word 1: Endpoint Characteristics */
    volatile uint32_t dev_addr              : 7  ; /* device address */
    volatile uint32_t fl_inactive_next_xact : 1  ; /* Only valid for Periodic with Full/Slow speed */
    volatile uint32_t ep_number             : 4  ; /* EP number */
    volatile uint32_t ep_speed              : 2  ; /* 0: Full, 1: Low, 2: High */
    volatile uint32_t data_toggle_control   : 1  ; /* 0: use DT in qHD, 1: use DT in qTD */
    volatile uint32_t head_list_flag        : 1  ; /* Head of the queue */
    volatile uint32_t max_packet_size       : 11 ; /* Max packet size */
    volatile uint32_t fl_ctrl_ep_flag       : 1  ; /* 1 if is Full/Low speed control endpoint */
    volatile uint32_t nak_reload            : 4  ; /* Used by HC */

    /* Word 2: Endpoint Capabilities */
    volatile uint32_t int_smask             : 8  ; /* Interrupt Schedule Mask */
    volatile uint32_t fl_int_cmask          : 8  ; /* Split Completion Mask for Full/Slow speed */
    volatile uint32_t fl_hub_addr           : 7  ; /* Hub Address for Full/Slow speed */
    volatile uint32_t fl_hub_port           : 7  ; /* Hub Port for Full/Slow speed */
    volatile uint32_t mult                  : 2  ; /* Transaction per micro frame */

    /* Word 3: Current qTD Pointer */
    volatile uint32_t qtd_addr;

    /* Word 4-11: Transfer Overlay */
    volatile hcd_qtd_t qtd_overlay;

    /*--------------------------------------------------------------------
     * Due to the fact QHD is 32 bytes aligned but occupies only 48 bytes
     * thus there are 16 bytes padding free that we can make use of.
     *--------------------------------------------------------------------
     */
    uint8_t used;
    uint8_t removing;    /* removed from async list, waiting for async advance */
    uint8_t pid;
    uint8_t interval_ms; /* polling interval in frames (or millisecond) */

    uint16_t total_xferred_bytes; /* number of bytes xferred until a qtd with ioc bit set */
    uint8_t reserved2[2];

    hcd_qtd_t * volatile p_qtd_list_head;	/* head of the scheduled TD list */
    hcd_qtd_t * volatile p_qtd_list_tail;	/* tail of the scheduled TD list */
} hcd_qhd_t;

typedef struct {
    hcd_link_t period_framelist[USB_HOST_FRAMELIST_SIZE];

    /* for ECHI, only implement 1 ms & 2 ms & 4 ms, 8 ms (framelist)
     * [0] : 1ms, [1] : 2ms, [2] : 4ms, [3] : 8 ms
     */
    hcd_qhd_t period_head_arr[USB_HCD_PERIODIC_ARR_COUNT];

    /* Note control qhd of dev0 is used as head of async list */
    struct {
        hcd_qhd_t qhd;
        hcd_qtd_t qtd;
    } control[USB_HCD_MAX_CONNECTED_DEVICES + 1];

    hcd_qhd_t qhd_pool[USB_HCD_MAX_QHD_COUNT];
    hcd_qtd_t qtd_pool[USB_HCD_MAX_QTD_COUNT];

    uint32_t uframe_number;
} hcd_data_t;

typedef struct {
    uint8_t     rhport;
    uint8_t     ep_speed;
    uint8_t     hub_addr;
    uint8_t     hub_port;
    USB_Type    *regs;
    hcd_data_t  *hcd_data;
    void (*hcd_vbus_ctrl_cb)(uint8_t rhport, uint8_t level);
} usb_host_handle_t;

/* USB Endpoint Descriptor */
typedef struct __attribute__ ((packed))
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bEndpointAddress;

    struct __attribute__ ((packed)) {
        uint8_t xfer  : 2;
        uint8_t sync  : 2;
        uint8_t usage : 2;
        uint8_t       : 2;
    } bmAttributes;

    struct __attribute__ ((packed)) {
        uint16_t size           : 11;
        uint16_t hs_period_mult : 2;
        uint16_t                : 3;
    } wMaxPacketSize;

    uint8_t  bInterval;
} usb_desc_endpoint_t;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/* Get direction from Endpoint address */
static inline usb_dir_t usb_edpt_dir(uint8_t addr)
{
    return (addr & usb_dir_in_mask) ? usb_dir_in : usb_dir_out;
}

/* Get Endpoint number from address */
static inline uint8_t usb_edpt_number(uint8_t addr)
{
    return (uint8_t)(addr & (~usb_dir_in_mask));
}

/* Get Endpoint address */
static inline uint8_t usb_edpt_addr(uint8_t num, uint8_t dir)
{
    return (uint8_t)(num | (dir ? usb_dir_in_mask : 0));
}

static inline uint32_t usb_host_align16(uint32_t value) { return (value & 0xFFFFFFF0UL); }
static inline uint32_t usb_host_align32(uint32_t value) { return (value & 0xFFFFFFE0UL); }
static inline uint32_t usb_host_align4k(uint32_t value) { return (value & 0xFFFFF000UL); }
static inline uint32_t usb_host_offset4k(uint32_t value) { return (value & 0xFFFUL); }

bool usb_host_qhd_has_xact_error(hcd_qhd_t *p_qhd);
bool usb_host_qhd_has_xact_error(hcd_qhd_t *p_qhd);
void usb_host_qtd_remove_1st_from_qhd(hcd_qhd_t *p_qhd);
hcd_link_t *usb_host_list_next(hcd_link_t *p_link_pointer);
hcd_link_t *usb_host_get_period_head(usb_host_handle_t *handle, uint8_t interval_ms);
hcd_qhd_t *usb_host_qhd_async_head(usb_host_handle_t *handle);
hcd_qhd_t *usb_host_qhd_next(hcd_qhd_t const *p_qhd);
hcd_qtd_t *usb_host_qtd_control(usb_host_handle_t *handle, uint8_t dev_addr);
uint32_t usb_host_uframe_number(usb_host_handle_t *handle);
uint32_t usb_host_status_flags(usb_host_handle_t *handle);
uint32_t usb_host_interrupts(usb_host_handle_t *handle);
void usb_host_clear_status_flags(usb_host_handle_t *handle, uint32_t status);
uint8_t  usb_host_get_port_speed(usb_host_handle_t *handle);
void usb_host_port_reset(usb_host_handle_t *handle);
bool usb_host_init(usb_host_handle_t *handle, uint32_t int_mask, uint16_t framelist_size);
bool usb_host_get_port_ccs(usb_host_handle_t *handle);
bool usb_host_port_csc(usb_host_handle_t *handle);
void usb_host_device_close(usb_host_handle_t *handle, uint8_t dev_addr);
bool usb_host_edpt_xfer(usb_host_handle_t *handle, uint8_t dev_addr, uint8_t ep_addr, uint8_t *buffer, uint16_t buflen);
bool usb_host_setup_send(usb_host_handle_t *handle, uint8_t dev_addr,  const uint8_t *setup_packet);
bool usb_host_edpt_open(usb_host_handle_t *handle, uint8_t dev_addr, usb_desc_endpoint_t const *ep_desc);
bool usb_host_pipe_queue_xfer(usb_host_handle_t *handle, uint8_t dev_addr, uint8_t ep_addr, uint8_t buffer[], uint16_t total_bytes);
bool usb_host_pipe_xfer(usb_host_handle_t *handle, uint8_t dev_addr, uint8_t ep_addr, uint8_t buffer[], uint16_t total_bytes, bool int_on_complete);
bool usb_host_edpt_busy(usb_host_handle_t *handle, uint8_t dev_addr, uint8_t ep_addr);
bool usb_host_edpt_stalled(usb_host_handle_t *handle, uint8_t dev_addr, uint8_t ep_addr);
bool usb_host_edpt_clear_stall(usb_host_handle_t *handle, uint8_t dev_addr, uint8_t ep_addr);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* HPM_USB_HOST_H */
