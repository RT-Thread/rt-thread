/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup TRANSFER_API Transfer Interface
 *
 * @brief Interface for data transfer functions.
 *
 * @section TRANSFER_API_SUMMARY Summary
 * The transfer interface supports background data transfer (no CPU intervention).
 *
 * Implemented by:
 * - @ref DTC
 * - @ref DMAC
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_TRANSFER_API_H
#define R_TRANSFER_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Common error codes and definitions. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define TRANSFER_SETTINGS_MODE_BITS           (30U)
#define TRANSFER_SETTINGS_SIZE_BITS           (28U)
#define TRANSFER_SETTINGS_SRC_ADDR_BITS       (26U)
#define TRANSFER_SETTINGS_CHAIN_MODE_BITS     (22U)
#define TRANSFER_SETTINGS_IRQ_BITS            (21U)
#define TRANSFER_SETTINGS_REPEAT_AREA_BITS    (20U)
#define TRANSFER_SETTINGS_DEST_ADDR_BITS      (18U)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Transfer control block.  Allocate an instance specific control block to pass into the transfer API calls.
 * @par Implemented as
 * - dtc_instance_ctrl_t
 * - dmac_instance_ctrl_t
 */
typedef void transfer_ctrl_t;

/** Transfer mode describes what will happen when a transfer request occurs. */
typedef enum e_transfer_mode
{
    /** In normal mode, each transfer request causes a transfer of @ref transfer_size_t from the source pointer to
     *  the destination pointer.  The transfer length is decremented and the source and address pointers are
     *  updated according to @ref transfer_addr_mode_t.  After the transfer length reaches 0, transfer requests
     *  will not cause any further transfers. */
    TRANSFER_MODE_NORMAL = 0,

    /** Repeat mode is like normal mode, except that when the transfer length reaches 0, the pointer to the
     *  repeat area and the transfer length will be reset to their initial values.  If DMAC is used, the
     *  transfer repeats only transfer_info_t::num_blocks times.  After the transfer repeats
     *  transfer_info_t::num_blocks times, transfer requests will not cause any further transfers.  If DTC is
     *  used, the transfer repeats continuously (no limit to the number of repeat transfers). */
    TRANSFER_MODE_REPEAT = 1,

    /** In block mode, each transfer request causes transfer_info_t::length transfers of @ref transfer_size_t.
     *  After each individual transfer, the source and destination pointers are updated according to
     *  @ref transfer_addr_mode_t.  After the block transfer is complete, transfer_info_t::num_blocks is
     *  decremented.  After the transfer_info_t::num_blocks reaches 0, transfer requests will not cause any
     *  further transfers. */
    TRANSFER_MODE_BLOCK = 2,

    /** In addition to block mode features, repeat-block mode supports a ring buffer of blocks and offsets
     *  within a block (to split blocks into arrays of their first data, second data, etc.) */
    TRANSFER_MODE_REPEAT_BLOCK = 3
} transfer_mode_t;

/** Transfer size specifies the size of each individual transfer.
 *  Total transfer length = transfer_size_t * transfer_length_t
 */
typedef enum e_transfer_size
{
    TRANSFER_SIZE_1_BYTE = 0,          ///< Each transfer transfers a 8-bit value
    TRANSFER_SIZE_2_BYTE = 1,          ///< Each transfer transfers a 16-bit value
    TRANSFER_SIZE_4_BYTE = 2           ///< Each transfer transfers a 32-bit value
} transfer_size_t;

/** Address mode specifies whether to modify (increment or decrement) pointer after each transfer. */
typedef enum e_transfer_addr_mode
{
    /** Address pointer remains fixed after each transfer. */
    TRANSFER_ADDR_MODE_FIXED = 0,

    /** Offset is added to the address pointer after each transfer. */
    TRANSFER_ADDR_MODE_OFFSET = 1,

    /** Address pointer is incremented by associated @ref transfer_size_t after each transfer. */
    TRANSFER_ADDR_MODE_INCREMENTED = 2,

    /** Address pointer is decremented by associated @ref transfer_size_t after each transfer. */
    TRANSFER_ADDR_MODE_DECREMENTED = 3
} transfer_addr_mode_t;

/** Repeat area options (source or destination).  In @ref TRANSFER_MODE_REPEAT, the selected pointer returns to its
 *  original value after transfer_info_t::length transfers.  In @ref TRANSFER_MODE_BLOCK and @ref TRANSFER_MODE_REPEAT_BLOCK,
 *  the selected pointer returns to its original value after each transfer. */
typedef enum e_transfer_repeat_area
{
    /** Destination area repeated in @ref TRANSFER_MODE_REPEAT or @ref TRANSFER_MODE_BLOCK or @ref TRANSFER_MODE_REPEAT_BLOCK. */
    TRANSFER_REPEAT_AREA_DESTINATION = 0,

    /** Source area repeated in @ref TRANSFER_MODE_REPEAT or @ref TRANSFER_MODE_BLOCK or @ref TRANSFER_MODE_REPEAT_BLOCK. */
    TRANSFER_REPEAT_AREA_SOURCE = 1
} transfer_repeat_area_t;

/** Chain transfer mode options.
 *  @note Only applies for DTC. */
typedef enum e_transfer_chain_mode
{
    /** Chain mode not used. */
    TRANSFER_CHAIN_MODE_DISABLED = 0,

    /** Switch to next transfer after a single transfer from this @ref transfer_info_t. */
    TRANSFER_CHAIN_MODE_EACH = 2,

    /** Complete the entire transfer defined in this @ref transfer_info_t before chaining to next transfer. */
    TRANSFER_CHAIN_MODE_END = 3
} transfer_chain_mode_t;

/** Interrupt options. */
typedef enum e_transfer_irq
{
    /** Interrupt occurs only after last transfer. If this transfer is chained to a subsequent transfer,
     *  the interrupt will occur only after subsequent chained transfer(s) are complete.
     *  @warning  DTC triggers the interrupt of the activation source.  Choosing TRANSFER_IRQ_END with DTC will
     *            prevent activation source interrupts until the transfer is complete. */
    TRANSFER_IRQ_END = 0,

    /** Interrupt occurs after each transfer.
     *  @note     Not available in all HAL drivers.  See HAL driver for details. */
    TRANSFER_IRQ_EACH = 1
} transfer_irq_t;

/** Driver specific information. */
typedef struct st_transfer_properties
{
    uint32_t block_count_max;           ///< Maximum number of blocks
    uint32_t block_count_remaining;     ///< Number of blocks remaining
    uint32_t transfer_length_max;       ///< Maximum number of transfers
    uint32_t transfer_length_remaining; ///< Number of transfers remaining
} transfer_properties_t;

/** This structure specifies the properties of the transfer.
 *  @warning  When using DTC, this structure corresponds to the descriptor block registers required by the DTC.
 *            The following components may be modified by the driver: p_src, p_dest, num_blocks, and length.
 *  @warning  When using DTC, do NOT reuse this structure to configure multiple transfers.  Each transfer must
 *            have a unique transfer_info_t.
 *  @warning  When using DTC, this structure must not be allocated in a temporary location.  Any instance of this
 *            structure must remain in scope until the transfer it is used for is closed.
 *  @note     When using DTC, consider placing instances of this structure in a protected section of memory. */
typedef struct st_transfer_info
{
    union
    {
        struct
        {
            uint32_t : 16;
            uint32_t : 2;

            /** Select what happens to destination pointer after each transfer. */
            transfer_addr_mode_t dest_addr_mode : 2;

            /** Select to repeat source or destination area, unused in @ref TRANSFER_MODE_NORMAL. */
            transfer_repeat_area_t repeat_area : 1;

            /** Select if interrupts should occur after each individual transfer or after the completion of all planned
             *  transfers. */
            transfer_irq_t irq : 1;

            /** Select when the chain transfer ends. */
            transfer_chain_mode_t chain_mode : 2;

            uint32_t : 2;

            /** Select what happens to source pointer after each transfer. */
            transfer_addr_mode_t src_addr_mode : 2;

            /** Select number of bytes to transfer at once. @see transfer_info_t::length. */
            transfer_size_t size : 2;

            /** Select mode from @ref transfer_mode_t. */
            transfer_mode_t mode : 2;
        } transfer_settings_word_b;

        uint32_t transfer_settings_word;
    };

    void const * volatile p_src;       ///< Source pointer
    void * volatile       p_dest;      ///< Destination pointer

    /** Number of blocks to transfer when using @ref TRANSFER_MODE_BLOCK (both DTC an DMAC) or
     * @ref TRANSFER_MODE_REPEAT (DMAC only) or
     * @ref TRANSFER_MODE_REPEAT_BLOCK (DMAC only), unused in other modes. */
    volatile uint16_t num_blocks;

    /** Length of each transfer.  Range limited for @ref TRANSFER_MODE_BLOCK, @ref TRANSFER_MODE_REPEAT,
     *  and @ref TRANSFER_MODE_REPEAT_BLOCK
     *  see HAL driver for details. */
    volatile uint16_t length;
} transfer_info_t;

/** Driver configuration set in @ref transfer_api_t::open. All elements except p_extend are required and must be
 *  initialized. */
typedef struct st_transfer_cfg
{
    /** Pointer to transfer configuration options. If using chain transfer (DTC only), this can be a pointer to
     *  an array of chained transfers that will be completed in order. */
    transfer_info_t * p_info;

    void const * p_extend;             ///< Extension parameter for hardware specific settings.
} transfer_cfg_t;

/** Select whether to start single or repeated transfer with software start. */
typedef enum e_transfer_start_mode
{
    TRANSFER_START_MODE_SINGLE = 0,    ///< Software start triggers single transfer.
    TRANSFER_START_MODE_REPEAT = 1     ///< Software start transfer continues until transfer is complete.
} transfer_start_mode_t;

/** Transfer functions implemented at the HAL layer will follow this API. */
typedef struct st_transfer_api
{
    /** Initial configuration.
     * @par Implemented as
     * - @ref R_DTC_Open()
     * - @ref R_DMAC_Open()
     *
     * @param[in,out] p_ctrl   Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]     p_cfg    Pointer to configuration structure. All elements of this structure
     *                                               must be set by user.
     */
    fsp_err_t (* open)(transfer_ctrl_t * const p_ctrl, transfer_cfg_t const * const p_cfg);

    /** Reconfigure the transfer.
     * Enable the transfer if p_info is valid.
     * @par Implemented as
     * - @ref R_DTC_Reconfigure()
     * - @ref R_DMAC_Reconfigure()
     *
     * @param[in,out] p_ctrl   Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]     p_info   Pointer to a new transfer info structure.
     */
    fsp_err_t (* reconfigure)(transfer_ctrl_t * const p_ctrl, transfer_info_t * p_info);

    /** Reset source address pointer, destination address pointer, and/or length, keeping all other settings the same.
     * Enable the transfer if p_src, p_dest, and length are valid.
     * @par Implemented as
     * - @ref R_DTC_Reset()
     * - @ref R_DMAC_Reset()
     *
     * @param[in]     p_ctrl         Control block set in @ref transfer_api_t::open call for this transfer.
     * @param[in]     p_src          Pointer to source. Set to NULL if source pointer should not change.
     * @param[in]     p_dest         Pointer to destination. Set to NULL if destination pointer should not change.
     * @param[in]     num_transfers  Transfer length in normal mode or number of blocks in block mode.  In DMAC only,
     *                               resets number of repeats (initially stored in transfer_info_t::num_blocks) in
     *                               repeat mode.  Not used in repeat mode for DTC.
     */
    fsp_err_t (* reset)(transfer_ctrl_t * const p_ctrl, void const * p_src, void * p_dest,
                        uint16_t const num_transfers);

    /** Enable transfer. Transfers occur after the activation source event (or when
     * @ref transfer_api_t::softwareStart is called if ELC_EVENT_ELC_NONE is chosen as activation source).
     * @par Implemented as
     * - @ref R_DTC_Enable()
     * - @ref R_DMAC_Enable()
     *
     * @param[in]     p_ctrl   Control block set in @ref transfer_api_t::open call for this transfer.
     */
    fsp_err_t (* enable)(transfer_ctrl_t * const p_ctrl);

    /** Disable transfer. Transfers do not occur after the activation source event (or when
     * @ref transfer_api_t::softwareStart is called if ELC_EVENT_ELC_NONE is chosen as the DMAC activation source).
     * @note If a transfer is in progress, it will be completed.  Subsequent transfer requests do not cause a
     * transfer.
     * @par Implemented as
     * - @ref R_DTC_Disable()
     * - @ref R_DMAC_Disable()
     *
     * @param[in]     p_ctrl   Control block set in @ref transfer_api_t::open call for this transfer.
     */
    fsp_err_t (* disable)(transfer_ctrl_t * const p_ctrl);

    /** Start transfer in software.
     * @warning Only works if ELC_EVENT_ELC_NONE is chosen as the DMAC activation source.
     * @note Not supported for DTC.
     * @par Implemented as
     * - @ref R_DMAC_SoftwareStart()
     *
     * @param[in]     p_ctrl   Control block set in @ref transfer_api_t::open call for this transfer.
     * @param[in]     mode     Select mode from @ref transfer_start_mode_t.
     */
    fsp_err_t (* softwareStart)(transfer_ctrl_t * const p_ctrl, transfer_start_mode_t mode);

    /** Stop transfer in software. The transfer will stop after completion of the current transfer.
     * @note Not supported for DTC.
     * @note Only applies for transfers started with TRANSFER_START_MODE_REPEAT.
     * @warning Only works if ELC_EVENT_ELC_NONE is chosen as the DMAC activation source.
     * @par Implemented as
     * - @ref R_DMAC_SoftwareStop()
     *
     * @param[in]     p_ctrl   Control block set in @ref transfer_api_t::open call for this transfer.
     */
    fsp_err_t (* softwareStop)(transfer_ctrl_t * const p_ctrl);

    /** Provides information about this transfer.
     * @par Implemented as
     * - @ref R_DTC_InfoGet()
     * - @ref R_DMAC_InfoGet()
     *
     * @param[in]     p_ctrl         Control block set in @ref transfer_api_t::open call for this transfer.
     * @param[out]    p_properties   Driver specific information.
     */
    fsp_err_t (* infoGet)(transfer_ctrl_t * const p_ctrl, transfer_properties_t * const p_properties);

    /** Releases hardware lock.  This allows a transfer to be reconfigured using @ref transfer_api_t::open.
     * @par Implemented as
     * - @ref R_DTC_Close()
     * - @ref R_DMAC_Close()
     * @param[in]     p_ctrl    Control block set in @ref transfer_api_t::open call for this transfer.
     */
    fsp_err_t (* close)(transfer_ctrl_t * const p_ctrl);
} transfer_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_transfer_instance
{
    transfer_ctrl_t      * p_ctrl;     ///< Pointer to the control structure for this instance
    transfer_cfg_t const * p_cfg;      ///< Pointer to the configuration structure for this instance
    transfer_api_t const * p_api;      ///< Pointer to the API structure for this instance
} transfer_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup TRANSFER_API)
 **********************************************************************************************************************/
