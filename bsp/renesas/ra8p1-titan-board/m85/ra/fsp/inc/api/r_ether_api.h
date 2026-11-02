/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_NETWORKING_INTERFACES
 * @defgroup ETHER_API Ethernet Interface
 * @brief Interface for Ethernet functions.
 *
 * @section ETHER_API_Summary Summary
 * The Ethernet interface provides Ethernet functionality.
 * The Ethernet interface supports the following features:
 * - Transmit/receive processing (Blocking and Non-Blocking)
 * - Callback function with returned event code
 * - Magic packet detection mode support
 * - Auto negotiation support
 * - Flow control support
 * - Multicast filtering support
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_ETHER_API_H
#define R_ETHER_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "r_ether_phy_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Wake on LAN */
typedef enum e_ether_wake_on_lan
{
    ETHER_WAKE_ON_LAN_DISABLE = 0,     ///< Disable Wake on LAN
    ETHER_WAKE_ON_LAN_ENABLE  = 1,     ///< Enable Wake on LAN
} ether_wake_on_lan_t;

/** Flow control functionality  */
typedef enum e_ether_flow_control
{
    ETHER_FLOW_CONTROL_DISABLE = 0,    ///< Disable flow control functionality
    ETHER_FLOW_CONTROL_ENABLE  = 1,    ///< Enable flow control functionality with pause frames
} ether_flow_control_t;

/** Multicast Filter */
typedef enum e_ether_multicast
{
    ETHER_MULTICAST_DISABLE = 0,       ///< Disable reception of multicast frames
    ETHER_MULTICAST_ENABLE  = 1,       ///< Enable reception of multicast frames
} ether_multicast_t;

/** Promiscuous Mode */
typedef enum e_ether_promiscuous
{
    ETHER_PROMISCUOUS_DISABLE = 0,     ///< Only receive packets with current MAC address, multicast, and broadcast
    ETHER_PROMISCUOUS_ENABLE  = 1,     ///< Receive all packets
} ether_promiscuous_t;

/** Zero copy */
typedef enum e_ether_zerocopy
{
    ETHER_ZEROCOPY_DISABLE = 0,        ///< Disable zero copy in Read/Write function
    ETHER_ZEROCOPY_ENABLE  = 1,        ///< Enable zero copy in Read/Write function
} ether_zerocopy_t;

typedef enum e_ether_padding
{
    ETHER_PADDING_DISABLE = 0,
    ETHER_PADDING_1BYTE   = 1,
    ETHER_PADDING_2BYTE   = 2,
    ETHER_PADDING_3BYTE   = 3,
} ether_padding_t;

#ifndef BSP_OVERRIDE_ETHER_EVENT_T

/** Event code of callback function */
typedef enum e_ether_event
{
    ETHER_EVENT_WAKEON_LAN,            ///< Magic packet detection event
    ETHER_EVENT_LINK_ON,               ///< Link up detection event
    ETHER_EVENT_LINK_OFF,              ///< Link down detection event
    ETHER_EVENT_RX_COMPLETE,           ///< Receive complete event.
    ETHER_EVENT_RX_MESSAGE_LOST,       ///< Receive FIFO overflow or Receive descriptor is full.
    ETHER_EVENT_TX_COMPLETE,           ///< Transmit complete event.
    ETHER_EVENT_TX_BUFFER_EMPTY,       ///< Transmit descriptor or FIFO is empty.
    ETHER_EVENT_TX_ABORTED,            ///< Transmit abort event.
    ETHER_EVENT_ERR_GLOBAL,            ///< Global error has occurred.
    ETHER_EVENT_GET_NIC_INFO,          ///< Get NIC Info.
} ether_event_t;
#endif

/** Network interface device infomation */
typedef struct st_ether_nic_info
{
    uint8_t     * p_mac_address;        ///< MAC address
} ether_nic_info_t;

#ifndef BSP_OVERRIDE_ETHER_CALLBACK_ARGS_T

/** Callback function parameter data */
typedef struct st_ether_callback_args
{
    uint32_t            channel;        ///< Device channel number
    ether_event_t       event;          ///< Event code
    uint32_t            status_ecsr;    ///< ETHERC status register for interrupt handler
    uint32_t            status_eesr;    ///< ETHERC/EDMAC status register for interrupt handler
    ether_nic_info_t    * p_nic_info;   ///< Pointer of NIC info

    void                * p_context;    ///< Placeholder for user data.  Set in @ref ether_api_t::open function in @ref ether_cfg_t.
} ether_callback_args_t;
#endif

/** Control block.  Allocate an instance specific control block to pass into the API calls.
 */
typedef void ether_ctrl_t;

/** Configuration parameters. */
typedef struct st_ether_cfg
{
    uint8_t              channel;                        ///< Channel
    ether_zerocopy_t     zerocopy;                       ///< Zero copy enable or disable in Read/Write function
    ether_multicast_t    multicast;                      ///< Multicast enable or disable
    ether_promiscuous_t  promiscuous;                    ///< Promiscuous mode enable or disable
    ether_flow_control_t flow_control;                   ///< Flow control functionally enable or disable
    ether_padding_t      padding;                        ///< Padding length inserted into the received Ethernet frame.
    uint32_t             padding_offset;                 ///< Offset of the padding inserted into the received Ethernet frame.
    uint32_t             broadcast_filter;               ///< Limit of the number of broadcast frames received continuously
    uint8_t            * p_mac_address;                  ///< Pointer of MAC address

    uint8_t num_tx_descriptors;                          ///< Number of transmission descriptor
    uint8_t num_rx_descriptors;                          ///< Number of receive descriptor

    uint8_t ** pp_ether_buffers;                         ///< Transmit and receive buffer

    uint32_t ether_buffer_size;                          ///< Size of transmit and receive buffer

    IRQn_Type irq;                                       ///< Interrupt number
    uint32_t  interrupt_priority;                        ///< Interrupt priority

    void (* p_callback)(ether_callback_args_t * p_args); ///< Callback provided when an ISR occurs.

    ether_phy_instance_t const * p_ether_phy_instance;   ///< Pointer to ETHER_PHY instance

    /** Placeholder for user data.  Passed to the user callback in ether_callback_args_t. */
    void       * p_context;                              ///< Placeholder for user data.
    void const * p_extend;                               ///< Placeholder for user extension.
} ether_cfg_t;

/** Functions implemented at the HAL layer will follow this API. */
typedef struct st_ether_api
{
    /** Open driver.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(ether_ctrl_t * const p_ctrl, ether_cfg_t const * const p_cfg);

    /** Close driver.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(ether_ctrl_t * const p_ctrl);

    /** Read packet if data is available.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_buffer     Pointer to where to store read data.
     * @param[in]  length_bytes Number of bytes in buffer
     */
    fsp_err_t (* read)(ether_ctrl_t * const p_ctrl, void * const p_buffer, uint32_t * const length_bytes);

    /** Release rx buffer from buffer pool process in zero-copy read operation.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* bufferRelease)(ether_ctrl_t * const p_ctrl);

    /** Update the buffer pointer in the current receive descriptor.
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  p_buffer         New address to write into the rx buffer descriptor.
     */
    fsp_err_t (* rxBufferUpdate)(ether_ctrl_t * const p_ctrl, void * const p_buffer);

    /** Write packet.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_buffer     Pointer to data to write.
     * @param[in]  frame_length Send ethernet frame size (without 4 bytes of CRC data size).
     */
    fsp_err_t (* write)(ether_ctrl_t * const p_ctrl, void * const p_buffer, uint32_t const frame_length);

    /** Process link.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* linkProcess)(ether_ctrl_t * const p_ctrl);

    /** Enable magic packet detection.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* wakeOnLANEnable)(ether_ctrl_t * const p_ctrl);

    /** Get the address of the most recently sent buffer.
     *
     * @param[in]   p_ctrl             Pointer to control structure.
     * @param[out]  p_buffer_address   Pointer to the address of the most recently sent buffer.
     */
    fsp_err_t (* txStatusGet)(ether_ctrl_t * const p_ctrl, void * const p_buffer_address);

    /**
     * Specify callback function and optional context pointer and working memory pointer.
     *
     * @param[in]   p_ctrl                   Pointer to the ETHER control block.
     * @param[in]   p_callback               Callback function
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(ether_ctrl_t * const p_ctrl, void (* p_callback)(ether_callback_args_t *),
                              void * const p_context, ether_callback_args_t * const p_callback_memory);
} ether_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_ether_instance
{
    ether_ctrl_t      * p_ctrl;        ///< Pointer to the control structure for this instance
    ether_cfg_t const * p_cfg;         ///< Pointer to the configuration structure for this instance
    ether_api_t const * p_api;         ///< Pointer to the API structure for this instance
} ether_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup ETHER_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_ETHERNET_API_H */
