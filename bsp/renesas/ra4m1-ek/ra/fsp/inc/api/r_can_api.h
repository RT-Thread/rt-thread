/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_CAN_API_H
#define R_CAN_API_H

/*******************************************************************************************************************//**
 * @ingroup RENESAS_CONNECTIVITY_INTERFACES
 * @defgroup CAN_API CAN Interface
 * @brief Interface for CAN peripheral
 *
 * @section CAN_INTERFACE_SUMMARY Summary
 * The CAN interface provides common APIs for CAN HAL drivers. CAN interface supports following features.
 * - Full-duplex CAN communication
 * - Generic CAN parameter setting
 * - Interrupt driven transmit/receive processing
 * - Callback function support with returning event code
 * - Hardware resource locking during a transaction
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#if BSP_FEATURE_CANFD_NUM_CHANNELS
 #define CAN_DATA_BUFFER_LENGTH    (64)
#else
 #define CAN_DATA_BUFFER_LENGTH    (8)
#endif

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#ifndef BSP_OVERRIDE_CAN_EVENT_T

/** CAN event codes */
typedef enum e_can_event
{
    CAN_EVENT_ERR_WARNING          = 0x0002, ///< Error Warning event.
    CAN_EVENT_ERR_PASSIVE          = 0x0004, ///< Error Passive event.
    CAN_EVENT_ERR_BUS_OFF          = 0x0008, ///< Bus Off event.
    CAN_EVENT_BUS_RECOVERY         = 0x0010, ///< Bus Off Recovery event.
    CAN_EVENT_MAILBOX_MESSAGE_LOST = 0x0020, ///< Mailbox has been overrun.
    CAN_EVENT_ERR_BUS_LOCK         = 0x0080, ///< Bus lock detected (32 consecutive dominant bits).
    CAN_EVENT_ERR_CHANNEL          = 0x0100, ///< Channel error has occurred.
    CAN_EVENT_TX_ABORTED           = 0x0200, ///< Transmit abort event.
    CAN_EVENT_RX_COMPLETE          = 0x0400, ///< Receive complete event.
    CAN_EVENT_TX_COMPLETE          = 0x0800, ///< Transmit complete event.
    CAN_EVENT_ERR_GLOBAL           = 0x1000, ///< Global error has occurred.
    CAN_EVENT_TX_FIFO_EMPTY        = 0x2000, ///< Transmit FIFO is empty.
    CAN_EVENT_FIFO_MESSAGE_LOST    = 0x4000, ///< Receive FIFO overrun.
} can_event_t;

#endif

/** CAN Operation modes */
typedef enum e_can_operation_mode
{
    CAN_OPERATION_MODE_NORMAL = 0,              ///< CAN Normal Operation Mode
    CAN_OPERATION_MODE_RESET,                   ///< CAN Reset Operation Mode
    CAN_OPERATION_MODE_HALT,                    ///< CAN Halt Operation Mode
    CAN_OPERATION_MODE_SLEEP            = 5,    ///< CAN Sleep Operation Mode
    CAN_OPERATION_MODE_GLOBAL_OPERATION = 0x80, // CANFD Global Operation Mode
    CAN_OPERATION_MODE_GLOBAL_RESET,            // CANFD Global Reset Mode
    CAN_OPERATION_MODE_GLOBAL_HALT,             // CANFD Global Halt Mode
    CAN_OPERATION_MODE_GLOBAL_SLEEP = 0x85      // CANFD Global Sleep Mode
} can_operation_mode_t;

/** CAN Test modes */
typedef enum e_can_test_mode
{
    CAN_TEST_MODE_DISABLED          = 0,   ///< CAN Test Mode Disabled.
    CAN_TEST_MODE_LISTEN            = 3,   ///< CAN Test Listen Mode.
    CAN_TEST_MODE_LOOPBACK_EXTERNAL = 5,   ///< CAN Test External Loopback Mode.
    CAN_TEST_MODE_LOOPBACK_INTERNAL = 7,   ///< CAN Test Internal Loopback Mode.
    CAN_TEST_MODE_INTERNAL_BUS      = 0x80 ///< CANFD Internal CAN Bus Communication Test Mode.
} can_test_mode_t;

#ifndef BSP_OVERRIDE_CAN_INFO_T

/** CAN status info */
typedef struct st_can_info
{
    uint32_t status;                   ///< Useful information from the CAN status register.
    uint32_t rx_mb_status;             ///< RX Message Buffer New Data flags.
    uint32_t rx_fifo_status;           ///< RX FIFO Empty flags.
    uint8_t  error_count_transmit;     ///< Transmit error count.
    uint8_t  error_count_receive;      ///< Receive error count.
    uint32_t error_code;               ///< Error code, cleared after reading.
} can_info_t;

#endif

#ifndef BSP_OVERRIDE_CAN_ID_MODE_T

/** CAN ID modes */
typedef enum e_can_id_mode
{
    CAN_ID_MODE_STANDARD,              ///< Standard IDs of 11 bits used.
    CAN_ID_MODE_EXTENDED,              ///< Extended IDs of 29 bits used.
} can_id_mode_t;

#endif

#ifndef BSP_OVERRIDE_CAN_FRAME_TYPE_T

/** CAN frame types */
typedef enum e_can_frame_type
{
    CAN_FRAME_TYPE_DATA,               ///< Data frame.
    CAN_FRAME_TYPE_REMOTE,             ///< Remote frame.
} can_frame_type_t;

#endif

/** CAN bit rate configuration. */
typedef struct st_can_bit_timing_cfg
{
    uint32_t baud_rate_prescaler;        ///< Baud rate prescaler. Valid values: 1 - 1024.
    uint32_t time_segment_1;             ///< Time segment 1 control.
    uint32_t time_segment_2;             ///< Time segment 2 control.
    uint32_t synchronization_jump_width; ///< Synchronization jump width.
} can_bit_timing_cfg_t;

#ifndef BSP_OVERRIDE_CAN_FRAME_T

/** CAN data Frame */
typedef struct st_can_frame
{
    uint32_t         id;                           ///< CAN ID.
    can_id_mode_t    id_mode;                      ///< Standard or Extended ID (IDE).
    can_frame_type_t type;                         ///< Frame type (RTR).
    uint8_t          data_length_code;             ///< CAN Data Length Code (DLC).
    uint32_t         options;                      ///< Implementation-specific options.
    uint8_t          data[CAN_DATA_BUFFER_LENGTH]; ///< CAN data.
} can_frame_t;

#endif

#ifndef BSP_OVERRIDE_CAN_CALLBACK_ARGS_T

/** CAN callback parameter definition */
typedef struct st_can_callback_args
{
    uint32_t    channel;               ///< Device channel number.
    can_event_t event;                 ///< Event code.
    uint32_t    error;                 ///< Error code.
    union
    {
        uint32_t mailbox;              ///< Mailbox number of interrupt source.
        uint32_t buffer;               ///< Buffer number of interrupt source.
    };
    void      * p_context;             ///< Context provided to user during callback.
    can_frame_t frame;                 ///< Received frame data.
} can_callback_args_t;

#endif

/** CAN Configuration */
typedef struct st_can_cfg
{
    /* CAN generic configuration */
    uint32_t               channel;                    ///< CAN channel.
    can_bit_timing_cfg_t * p_bit_timing;               ///< CAN bit timing.

    /* Configuration for CAN Event processing */
    void (* p_callback)(can_callback_args_t * p_args); ///< Pointer to callback function
    void * p_context;                                  ///< User defined callback context.

    /* Pointer to CAN peripheral specific configuration */
    void const * p_extend;                             ///< CAN hardware dependent configuration
    uint8_t      ipl;                                  ///< Error/Transmit/Receive interrupt priority
    IRQn_Type    error_irq;                            ///< Error IRQ number
    IRQn_Type    rx_irq;                               ///< Receive IRQ number
    IRQn_Type    tx_irq;                               ///< Transmit IRQ number
} can_cfg_t;

/** CAN control block.  Allocate an instance specific control block to pass into the CAN API calls.
 */
typedef void can_ctrl_t;

/** Shared Interface definition for CAN */
typedef struct st_can_api
{
    /** Open function for CAN device
     *
     * @param[in,out]  p_ctrl     Pointer to the CAN control block. Must be declared by user. Value set here.
     * @param[in]      p_cfg      Pointer to CAN configuration structure. All elements of this structure must be set by
     *                            user.
     */
    fsp_err_t (* open)(can_ctrl_t * const p_ctrl, can_cfg_t const * const p_cfg);

    /** Write function for CAN device
     * @param[in]   p_ctrl          Pointer to the CAN control block.
     * @param[in]   buffer          Buffer number (mailbox or message buffer) to write to.
     * @param[in]   p_frame         Pointer for frame of CAN ID, DLC, data and frame type to write.
     */
    fsp_err_t (* write)(can_ctrl_t * const p_ctrl, uint32_t buffer_number, can_frame_t * const p_frame);

    /** Read function for CAN device
     * @param[in]   p_ctrl          Pointer to the CAN control block.
     * @param[in]   buffer          Message buffer (number) to read from.
     * @param[in]   p_frame         Pointer to store the CAN ID, DLC, data and frame type.
     */
    fsp_err_t (* read)(can_ctrl_t * const p_ctrl, uint32_t buffer_number, can_frame_t * const p_frame);

    /** Close function for CAN device
     * @param[in]   p_ctrl     Pointer to the CAN control block.
     */
    fsp_err_t (* close)(can_ctrl_t * const p_ctrl);

    /** Mode Transition function for CAN device
     * @param[in]   p_ctrl               Pointer to the CAN control block.
     * @param[in]   operation_mode       Destination CAN operation state.
     * @param[in]   test_mode            Destination CAN test state.
     */
    fsp_err_t (* modeTransition)(can_ctrl_t * const p_ctrl, can_operation_mode_t operation_mode,
                                 can_test_mode_t test_mode);

    /** Get CAN channel info.
     *
     * @param[in]   p_ctrl  Handle for channel (pointer to channel control block)
     * @param[out]  p_info  Memory address to return channel specific data to.
     */
    fsp_err_t (* infoGet)(can_ctrl_t * const p_ctrl, can_info_t * const p_info);

    /** Specify callback function and optional context pointer and working memory pointer.
     *
     * @param[in]   p_ctrl                   Control block set in @ref can_api_t::open call.
     * @param[in]   p_callback               Callback function to register
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(can_ctrl_t * const p_ctrl, void (* p_callback)(can_callback_args_t *),
                              void * const p_context, can_callback_args_t * const p_callback_memory);
} can_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_can_instance
{
    can_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    can_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    can_api_t const * p_api;           ///< Pointer to the API structure for this instance
} can_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup CAN_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
