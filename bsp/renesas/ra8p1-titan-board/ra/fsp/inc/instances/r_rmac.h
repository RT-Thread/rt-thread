/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_RMAC_H
#define R_RMAC_H

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_ether_api.h"
#include "r_layer3_switch.h"

FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef enum e_ether_previous_link_status
{
    ETHER_PREVIOUS_LINK_STATUS_DOWN = 0, ///< Previous link status is down
    ETHER_PREVIOUS_LINK_STATUS_UP   = 1, ///< Previous link status is up
} ether_previous_link_status_t;

typedef enum e_ether_link_change
{
    ETHER_LINK_CHANGE_NO_CHANGE = 0,   ///< Link status is no change
    ETHER_LINK_CHANGE_LINK_DOWN = 1,   ///< Link status changes to down
    ETHER_LINK_CHANGE_LINK_UP   = 2,   ///< Link status changes to up
} ether_link_change_t;

typedef enum e_ether_link_establish_status
{
    ETHER_LINK_ESTABLISH_STATUS_DOWN = 0, ///< Link establish status is down
    ETHER_LINK_ESTABLISH_STATUS_UP   = 1, ///< Link establish status is up
} ether_link_establish_status_t;

/** Information of a descriptor queue. */
typedef struct st_rmac_queue_info
{
    layer3_switch_descriptor_queue_cfg_t queue_cfg; ///< Queue configuration.
    uint32_t index;                                 ///< Queue index.
} rmac_queue_info_t;

/** Write configuration. */
typedef struct st_rmac_write_cfg
{
    uint32_t tx_timestamp_enable : 1;  ///< Enable to get TX timestamp.
    uint32_t reserved            : 31;
} rmac_write_cfg_t;

/** Timestamp. */
typedef struct st_rmac_timestamp
{
    uint16_t sec_upper;                ///< Timestamp second (Upper 16 bit).
    uint32_t sec_lower;                ///< Timestamp second (Lower 32 bit).
    uint32_t ns;                       ///< Timestamp nanosecond.
} rmac_timestamp_t;

/** Node to manage buffer. */
typedef struct st_rmac_buffer_node
{
    void   * p_buffer;                   ///< Pointer to the buffer.
    uint32_t size;                       ///< Buffer size.
#if LAYER3_SWITCH_CFG_GPTP_ENABLE
    rmac_timestamp_t timestamp;          ///< RX timestamp value.
#endif
    struct st_rmac_buffer_node * p_next; ///< Pointer to the next node.
} rmac_buffer_node_t;

/** Queue of internal buffers. */
typedef struct st_rmac_buffer_queue
{
    rmac_buffer_node_t * p_head;       ///< Pointer to the head of the queue.
    rmac_buffer_node_t * p_tail;       ///< Pointer to the tail of the queue.
} rmac_buffer_queue_t;

/* Extended configuration. */
typedef struct st_rmac_extended_cfg
{
    ether_switch_instance_t const * p_ether_switch; ///< Pointer to ETHER_SWITCH instance.

    uint32_t tx_queue_num;                          ///< Number of TX descriptor queues.
    uint32_t rx_queue_num;                          ///< Number of RX descriptor queues.

    rmac_queue_info_t * p_ts_queue;                 ///< Configuration of TS queue.
    rmac_queue_info_t * p_tx_queue_list;            ///< TX queue list.
    rmac_queue_info_t * p_rx_queue_list;            ///< RX queue list.

    IRQn_Type            rmpi_irq;                  ///< Magic packet detection interrupt number.
    uint32_t             rmpi_ipl;                  ///< Magic packet detection interrupt priority.
    rmac_buffer_node_t * p_buffer_node_list;        ///< List of buffer nodes for managing TX/RX buffers.
    uint32_t             buffer_node_num;           ///< Length of buffer nodes list.
} rmac_extended_cfg_t;

/** Instance control block. DO NOT INITIALIZE.  Initialization occurs when @ref spi_flash_api_t::open is called */
typedef struct st_rmac_instance_ctrl
{
    uint32_t            open;          // Whether or not driver is open
    ether_cfg_t const * p_cfg;         // Pointer to initial configuration

    bool is_lost_rx_packet;

    /* IP dependent members. */
    R_ETHA0_Type * p_reg_etha;
    R_RMAC0_Type * p_reg_rmac;

    /* RX statuses. */
    uint32_t            read_queue_index;                ///< RX queue that used for next BufferRelease API.
    uint32_t            rx_running_queue_index;          ///< Whether a RX queue is running or not.
    rmac_buffer_queue_t rx_completed_buffer_queue;       ///< RX buffers that have completed reception.
    rmac_buffer_queue_t rx_unreleased_buffer_queue;      ///< RX buffers that  have been read but not yet released.
    rmac_buffer_queue_t rx_empty_buffer_queue;           ///< RX Buffers that have no data.
    uint32_t            rx_initialized_buffer_num;       ///< RX buffer num of initialized. This is used in RxBufferUpdate API.

    /* TX statuses. */
    uint32_t            write_queue_index;               ///< TX queue that used for next Write API.
    uint32_t            tx_running_queue_index;          ///< Index of the queue that is running now.
    void              * p_last_sent_buffer;              ///< Pointer to the last sent TX buffer.
    rmac_buffer_queue_t tx_pending_buffer_queue;         ///< Delayed TX buffers.
    rmac_buffer_queue_t tx_empty_buffer_queue;           ///< TX Buffers that have no data.
    uint32_t            write_descriptor_count;          ///< Count of descriptor that already write in active queue.

    rmac_buffer_queue_t buffer_node_pool;                ///< Buffer nodes pool.

    /* Timestamp features. */
    rmac_timestamp_t * p_rx_timestamp;                   ///< RX timestamp pointer.
    rmac_timestamp_t   tx_timestamp;                     ///< TX timestamp.
    uint32_t           tx_timestamp_seq_num;             ///< Sequence number of TX timestamp.
    rmac_write_cfg_t   write_cfg;                        ///< Configuration of transmission.

    /* Status of ethernet driver. */
    ether_previous_link_status_t  previous_link_status;  ///< Previous link status
    ether_link_change_t           link_change;           ///< Status of link change
    ether_link_establish_status_t link_establish_status; ///< Current Link status
    ether_wake_on_lan_t           wake_on_lan;           ///< Wake on LAN mode.

    /* Pointer to callback and optional working memory */
    void (* p_callback)(ether_callback_args_t *);
    ether_callback_args_t * p_callback_memory;

    /* Pointer to context to be passed into callback function */
    void * p_context;
} rmac_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const ether_api_t g_ether_on_rmac;

/** @endcond */

fsp_err_t R_RMAC_Open(ether_ctrl_t * p_ctrl, ether_cfg_t const * const p_cfg);
fsp_err_t R_RMAC_Close(ether_ctrl_t * p_ctrl);
fsp_err_t R_RMAC_BufferRelease(ether_ctrl_t * const p_ctrl);
fsp_err_t R_RMAC_RxBufferUpdate(ether_ctrl_t * const p_ctrl, void * const p_buffer);
fsp_err_t R_RMAC_LinkProcess(ether_ctrl_t * const p_ctrl);
fsp_err_t R_RMAC_WakeOnLANEnable(ether_ctrl_t * const p_ctrl);
fsp_err_t R_RMAC_Read(ether_ctrl_t * const p_ctrl, void * const p_buffer, uint32_t * const length_bytes);
fsp_err_t R_RMAC_Write(ether_ctrl_t * const p_ctrl, void * const p_buffer, uint32_t const frame_length);
fsp_err_t R_RMAC_TxStatusGet(ether_ctrl_t * const p_ctrl, void * const p_buffer_address);
fsp_err_t R_RMAC_CallbackSet(ether_ctrl_t * const          p_api_ctrl,
                             void (                      * p_callback)(ether_callback_args_t *),
                             void * const                  p_context,
                             ether_callback_args_t * const p_callback_memory);
fsp_err_t R_RMAC_SetWriteConfig(ether_ctrl_t * const p_ctrl, rmac_write_cfg_t * const p_write_cfg);
fsp_err_t R_RMAC_GetTxTimestamp(ether_ctrl_t * const p_ctrl, rmac_timestamp_t * const p_timestamp);
fsp_err_t R_RMAC_GetRxTimestamp(ether_ctrl_t * const p_ctrl, rmac_timestamp_t * const p_timestamp);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_RMAC_H */
