/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_CAN_DRV_H
#define HPM_CAN_DRV_H

#include "hpm_common.h"
#include "hpm_can_regs.h"
#include "hpm_soc_feature.h"

/**
 * @brief CAN driver APIs
 * @defgroup can_interface CAN driver APIs
 * @ingroup can_interfaces
 * @{
 *
 */

/***********************************************************************************************************************
 *
 * Definitions
 *
 **********************************************************************************************************************/

/**
 * @brief CAN error codes
 */
enum {
    status_can_bit_error = MAKE_STATUS(status_group_can, 0),            /**< CAN bit error */
    status_can_form_error = MAKE_STATUS(status_group_can, 1),           /**< CAN Form error */
    status_can_stuff_error = MAKE_STATUS(status_group_can, 2),          /**< CAN stuff error */
    status_can_ack_error = MAKE_STATUS(status_group_can, 3),            /**< CAN ACK error */
    status_can_crc_error = MAKE_STATUS(status_group_can, 4),            /**< CAN CRC error */
    status_can_other_error = MAKE_STATUS(status_group_can, 5),          /**< CAN other error */
    status_can_tx_fifo_full = MAKE_STATUS(status_group_can, 6),         /**< CAN TX fifo full */
    status_can_filter_index_invalid = MAKE_STATUS(status_group_can, 7), /**< CAN filter index is invalid */
    status_can_filter_num_invalid = MAKE_STATUS(status_group_can, 8),   /**< CAN filter number is invalid */
    status_can_invalid_bit_timing = MAKE_STATUS(status_group_can, 9),   /**< Invalid CAN bit timing parameter */
};

/**
 * @brief CAN Event definitions
 */
#define CAN_EVENT_RECEIVE (CAN_RTIF_RIF_MASK)               /**< CAN Receive event */
#define CAN_EVENT_RX_BUF_OVERRUN (CAN_RTIF_ROIF_MASK)       /**< CAN RX buffer overrun event */
#define CAN_EVENT_RX_BUF_FULL (CAN_RTIF_RFIF_MASK)          /**< CAN RX buffer full event */
#define CAN_EVENT_RX_BUF_ALMOST_FULL (CAN_RTIF_RAFIF_MASK)  /**< CAN RX buffer almost full event */
#define CAN_EVENT_TX_PRIMARY_BUF (CAN_RTIF_TPIF_MASK)       /**< CAN TX primary buffer event */
#define CAN_EVENT_TX_SECONDARY_BUF (CAN_RTIF_TSIF_MASK)     /**< CAN TX secondary buffer event */
#define CAN_EVENT_ERROR (CAN_RTIF_EIF_MASK)                 /**< CAN error event */
#define CAN_EVENT_ABORT (CAN_RTIF_AIF_MASK)                 /**< CAN abort event */

/**
 * @brief CAN Secondary Transmit buffer Status
 */
#define CAN_STB_IS_EMPTY (0U)                               /**< CAN Secondary Transmit buffer is empty */
#define CAN_STB_LESS_EQUAL_HALF_FULL (1U)                   /**< CAN Secondary Transmit buffer <= 1/2 * FULL */
#define CAN_STB_MORE_THAN_HALF_FULL (2U)                    /**< CAN Secondary Transmit buffer > 1/2 * FULL */
#define CAN_STB_IS_FULL (3U)                                /**< CAN Secondary Transmit buffer is full */

/**
 * @brief CAN Receive Buffer States
 */
#define CAN_RXBUF_IS_EMPTY (0U)                             /**< CAN Receive buffer is empty */
#define CAN_RXBUF_HAS_DATA (1U)                             /**< CAN Receive buffer has data */
#define CAN_RXBUF_ALMOST_FULL (2U)                          /**< CAN Receive buffer is almost full */
#define CAN_RXBUF_IS_FULL (3U)                              /**< CAN Receive buffer is full */

/**
 * @brief CAN Error interrupts/flags
 *
 */
#define CAN_ERROR_WARNING_LIMIT_FLAG           (CAN_ERRINT_EWARN_MASK)     /**< CAN Error Limit reached */
#define CAN_ERROR_PASSIVE_MODE_ACTIVE_FLAG     (CAN_ERRINT_EPASS_MASK)     /**< CAN Passive mode active */
#define CAN_ERROR_PASSIVE_INT_ENABLE           (CAN_ERRINT_EPIE_MASK)      /**< CAN Passive Interrupt Enable */
#define CAN_ERROR_PASSIVE_INT_FLAG             (CAN_ERRINT_EPIF_MASK)      /**< CAN Passive Interrupt Flag */
#define CAN_ERROR_ARBITRATION_LOST_INT_ENABLE  (CAN_ERRINT_ALIE_MASK)      /**< CAN Arbitration Lost Interrupt Enable */
#define CAN_ERROR_ARBITRATION_LOST_INT_FLAG    (CAN_ERRINT_ALIE_MASK)      /**< CAN arbitration Lost Interrupt Flag */
#define CAN_ERROR_BUS_ERROR_INT_ENABLE         (CAN_ERRINT_BEIE_MASK)      /**< CAN BUS error Interrupt Enable */
#define CAN_ERROR_BUS_ERROR_INT_FLAG           (CAN_ERRINT_BEIF_MASK)      /**< CAN BUS error Interrupt flag */

/**
 * @brief CAN Error Kinds
 *
 */
#define CAN_KIND_OF_ERROR_NO_ERROR      (0U)        /**< No error */
#define CAN_KIND_OF_ERROR_BIT_ERROR     (1U)        /**< Bit error */
#define CAN_KIND_OF_ERROR_FORM_ERROR    (2U)        /**< Form error */
#define CAN_KIND_OF_ERROR_STUFF_ERROR   (3U)        /**< Stuff error */
#define CAN_KIND_OF_ERROR_ACK_ERROR     (4U)        /**< Acknowledgment error */
#define CAN_KIND_OF_ERROR_CRC_ERROR     (5U)        /**< CRC error */
#define CAN_KIND_OF_ERROR_OTHER_ERROR   (6U)        /**< Other errors */
#define CAN_KIND_OF_ERROR_BUS_OFF       (7U)        /**< BUS off error */

/**
 * @brief CAN loopback types
 */
typedef enum _can_mode {
    can_mode_normal,              /**< Non-loopback mode */
    can_mode_loopback_internal,   /**< Internal loopback mode */
    can_mode_loopback_external,   /**< External loopback mode */
    can_mode_listen_only,         /**< CAN listen mode */
} can_node_mode_t;

/**
 * @brief CAN bit timing options
 */
typedef enum _can_bit_timing_option {
    can_bit_timing_can2_0,          /**< CAN 2.0 bit timing option */
    can_bit_timing_canfd_nominal,  /**< CANFD nominal timing option */
    can_bit_timing_canfd_data,      /**< CANFD data timing option */
} can_bit_timing_option_t;

/**
 * @brief CAN DLC definitions
 */
enum {
    can_payload_size_0 = 0,                 /**< Payload size is 0 */
    can_payload_size_1,                     /**< Payload size is 1 */
    can_payload_size_2,                     /**< Payload size is 2 */
    can_payload_size_3,                     /**< Payload size is 3 */
    can_payload_size_4,                     /**< Payload size is 4 */
    can_payload_size_5,                     /**< Payload size is 5 */
    can_payload_size_6,                     /**< Payload size is 6 */
    can_payload_size_7,                     /**< Payload size is 7 */
    can_payload_size_8,                     /**< Payload size is 8 */
    can_payload_size_12,                    /**< Payload size is 12 */
    can_payload_size_16,                    /**< Payload size is 16 */
    can_payload_size_20,                    /**< Payload size is 20 */
    can_payload_size_24,                    /**< Payload size is 24 */
    can_payload_size_32,                    /**< Payload size is 32 */
    can_payload_size_48,                    /**< Payload size is 48 */
    can_payload_size_64,                    /**< Payload size is 64 */
    can_payload_size_max = can_payload_size_64,
};

/**
 * @brief CAN Bit timing parameters
 */
typedef struct {
    uint16_t prescaler;     /**< Prescaler value */
    uint16_t num_seg1;      /**< Seg1 value */
    uint16_t num_seg2;      /**< Seg2 value */
    uint16_t num_sjw;       /**< SJW value */
} can_bit_timing_param_t;

/**
 * @brief CAN receive buffer data structure
 */
typedef union _can_rx_buf {
    uint32_t buffer[20];                        /**< CAN buffer size */
    struct {
        struct {
            uint32_t id: 29;                    /**< CAN ID */
            uint32_t : 1;
            uint32_t error_state_indicator: 1;  /**< Error state indicator */
        };
        struct {
            uint32_t dlc: 4;                   /**< Data length option */
            uint32_t bitrate_switch: 1;        /**< bitrate switch flag */
            uint32_t canfd_frame: 1;           /**< CANFD frame flag */
            uint32_t remote_frame: 1;          /**< Remote frame flag */
            uint32_t extend_id: 1;             /**< Extended ID flag */
            uint32_t : 4;
            uint32_t loopback_message: 1;      /**< Loopback message flag */
            uint32_t error_type: 3;            /**< Error type */
            uint32_t cycle_time: 16;           /**< Cycle time */
        };
        uint8_t data[];                        /**< Data pointer */
    };
} can_receive_buf_t;

/**
 * @brief CAN transmit buffer data structure
 */
typedef union _can_tx_buf {
    uint32_t buffer[18];                            /**< CAN transmit buffer */
    struct {
        struct {
            uint32_t id: 29;                       /**< CAN ID */
            uint32_t : 2;
            uint32_t transmit_timestamp_enable: 1;  /**< Timestamp enable flag */
        };
        struct {
            uint32_t dlc: 4;                        /**< Data length option */
            uint32_t bitrate_switch: 1;             /**< bitrate switch flag */
            uint32_t canfd_frame: 1;                /**< CANFD frame flag */
            uint32_t remote_frame: 1;               /**< remote_frame flag */
            uint32_t extend_id: 1;                  /**< Extended ID flag */
            uint32_t : 24;
        };
        uint8_t data[];                             /**< Data pointer */
    };
} can_transmit_buf_t;

/**
 * @brief CAN acceptance filter modes
 */
typedef enum _can_filter_id_mode {
    can_filter_id_mode_both_frames,                /**< Accept both standard frame and extended frame */
    can_filter_id_mode_standard_frames,            /**< Accept standard frame only */
    can_filter_id_mode_extended_frames,            /**< Accept extended frame only */
} can_filter_id_mode_t;

/**
 * @brief CAN acceptance filter configuration
 */
typedef struct {
    uint16_t index;                            /**< CAN filter index */
    can_filter_id_mode_t id_mode;              /**< CAN filter id mode */
    bool enable;                               /**< CAN filter enable flag */
    uint32_t code;                             /**< CAN filter code */
    uint32_t mask;                             /**< CAN filter mask */
} can_filter_config_t;

/**
 * @brief CAN configuration
 */
typedef struct {
    union {
        struct {
            uint32_t baudrate;                  /**< CAN2.0 baudrate / CANFD nominal baudrate */
            uint32_t baudrate_fd;               /**< CANFD data baudrate */
            /**< minimum sampling point, value range (0-1000), samplepoint_min/1000 will be used in driver */
            uint16_t can20_samplepoint_min;
            /**< maximum sampling point, value range (0-1000), samplepoint_max/1000 will be used in driver */
            uint16_t can20_samplepoint_max;
            /**< minimum sampling point, value range (0-1000), samplepoint_min/1000 will be used in driver */
            uint16_t canfd_samplepoint_min;
            /**< maximum sampling point, value range (0-1000), samplepoint_max/1000 will be used in driver */
            uint16_t canfd_samplepoint_max;
        };
        struct {
            can_bit_timing_param_t can_timing;  /**< CAN2.0 /CANFD nominal low-level bit timing parameters */
            can_bit_timing_param_t canfd_timing;/**< CANFD low-level bit timing parameters */
        };
    };

    can_node_mode_t mode;                       /**< CAN work mode */
    bool use_lowlevel_timing_setting;           /**< Use low-level timing setting */
    bool enable_canfd;                          /**< Enable CAN FD */
    bool enable_self_ack;                       /**< CAN self-ack flag */
    bool disable_ptb_retransmission;            /**< disable re-transmission for primary transmit buffer */
    bool disable_stb_retransmission;            /**< disable re-transmission for secondary transmit buffer */
    bool enable_tdc;                            /**< Enable transmitter delay compensation */

    uint8_t filter_list_num;                    /**< element number of CAN filters in filter list */
    can_filter_config_t *filter_list;           /**< CAN filter list pointer */

    uint8_t irq_txrx_enable_mask;               /**< CAN TX and RX IRQ Enable Mask */
    uint8_t irq_error_enable_mask;              /**< CAN Error IRQ Enable Mask */
    bool enable_tx_buffer_priority_mode;        /**< Enable Priority-based priority */
    bool enable_can_fd_iso_mode;                /**< Enable CAN-FD ISO mode */
} can_config_t;


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Reset CAN controller
 *
 * @param [in] base  CAN base address
 * @param [in] enable reset flag for CAN controller
 *  @arg true reset the CAN controller
 *  @arg false clear the CAN controller reset flag
 */
static inline void can_reset(CAN_Type *base, bool enable)
{
    if (enable) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_RESET_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_RESET_MASK;
    }
}

/**
 * @brief Force CAN controller to Bus-off mode
 * @param [in] base CAN base address
 */
static inline void can_force_bus_off(CAN_Type *base)
{
    base->CMD_STA_CMD_CTRL = CAN_CMD_STA_CMD_CTRL_BUSOFF_MASK;
}

/**
 * @brief Set CAN mode
 *
 * @param [in] base CAN base address
 * @param [in] mode CAN loopback mode
 *  @arg can_mode_normal Normal work mode
 *  @arg can_mode_loopback_internal internal loopback mode
 *  @arg can_mode_loopback_external external loopback mode
 *  @arg can_mode_listen_only CAN listen-only mode
 */
static inline void can_set_node_mode(CAN_Type *base, can_node_mode_t mode)
{
    uint32_t cfg_stat = base->CMD_STA_CMD_CTRL & ~(CAN_CMD_STA_CMD_CTRL_LBME_MASK | CAN_CMD_STA_CMD_CTRL_LBMI_MASK | CAN_CMD_STA_CMD_CTRL_LOM_MASK);
    if (mode == can_mode_loopback_internal) {
        cfg_stat |= CAN_CMD_STA_CMD_CTRL_LBMI_MASK;
    } else if (mode == can_mode_loopback_external) {
        cfg_stat |= CAN_CMD_STA_CMD_CTRL_LBME_MASK;
    } else if (mode == can_mode_listen_only) {
        cfg_stat |= CAN_CMD_STA_CMD_CTRL_LOM_MASK;
    } else {
        /* CAN normal work mode, no change needed here */
    }
    base->CMD_STA_CMD_CTRL = cfg_stat;
}

/**
 * @brief Enable CAN listen-only mode
 * @param [in] base CAN base address
 * @param [in] enable CAN listen-only mode enable flag
 *  @arg true enable listen-only mode
 *  @arg false disable listen-only mode
 */
static inline void can_enable_listen_only_mode(CAN_Type *base, bool enable)
{
    if (enable) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_LOM_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_LOM_MASK;
    }
}

/**
 * @brief Enter CAN standby mode
 * @param [in] base CAN base address
 * @param [in] enable  Can standby mode enable flag
 *  @arg true enable standby mode
 *  @arg false disable standby mode
 */
static inline void can_enter_standby_mode(CAN_Type *base, bool enable)
{
    if (enable) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_STBY_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_STBY_MASK;
    }
}

/**
 * @brief Disable the re-transmission for the primary transmission buffer
 *
 * @param [in] base CAN base address
 * @param [in] enable Flag for disabling re-transmission for PTB
 */
static inline void can_disable_ptb_retransmission(CAN_Type *base, bool enable)
{
    if (enable) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_TPSS_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_TPSS_MASK;
    }
}

/**
 * @brief Check whether re-transmission is disabled for PTB or not
 *
 * @param [in] base CAN base address
 * @return true Re-transmission is disabled for PTB
 * @return false Re-transmission is enabled for PTB
 */
static inline bool can_is_ptb_retransmission_disabled(CAN_Type *base)
{
    return ((base->CMD_STA_CMD_CTRL & CAN_CMD_STA_CMD_CTRL_TPSS_MASK) != 0);
}

/**
 * @brief Disable the re-transmission for the secondary transmission buffer
 *
 * @param [in] base CAN base address
 * @param [in] enable Flag for disabling re-transmission for STB
 */
static inline void can_disable_stb_retransmission(CAN_Type *base, bool enable)
{
    if (enable) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_TSSS_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_TSSS_MASK;
    }
}

/**
 * @brief Check whether re-transmission is disabled for STB or not
 *
 * @param [in] base CAN base address
 * @return true Re-transmission is disabled for STB
 * @return false Re-transmission is enabled for STB
 */
static inline bool can_is_stb_retransmission_disabled(CAN_Type *base)
{
    return ((base->CMD_STA_CMD_CTRL & CAN_CMD_STA_CMD_CTRL_TSSS_MASK) != 0);
}


/**
 * @brief Select CAN TX buffer
 * @param [in] base CAN base address
 * @param [in] select_secondary_buffer CAN secondary transmit buffer selection flag
 *  @arg true Select the secondary transmit buffer
 *  @arg false Select the primary transmit buffer
 */
static inline void can_select_tx_buffer(CAN_Type *base, bool select_secondary_buffer)
{
    if (select_secondary_buffer) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_TBSEL_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_TBSEL_MASK;
    }
}

/**
 * @brief Start CAN high priority message transmit
 * @param [in] base CAN base address
 *
 */
static inline void can_start_high_priority_message_transmit(CAN_Type *base)
{
    base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_TPE_MASK;
}

/**
 * @brief Abort CAN high priority message transmit
 * @param [in] base CAN base address
 */
static inline void can_abort_high_priority_message_transmit(CAN_Type *base)
{
    base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_TPA_MASK;
}

/**
 * @brief Start CAN message transmit
 * @param [in] base CAN base address
 */
static inline void can_start_message_transmit(CAN_Type *base)
{
    base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_TSONE_MASK;
}

/**
 * @brief Start CAN all messages transmit
 * @param [in] base CAN base address
 */
static inline void can_start_all_message_transmit(CAN_Type *base)
{
    base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_TSALL_MASK;
}

/**
 * @brief Abort CAN message transmit
 * @param [in] base CAN base address
 */
static inline void can_abort_message_transmit(CAN_Type *base)
{
    base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_TSA_MASK;
}

/**
 * @brief Switch to next CAN tx buffer
 * @param [in] base CAN base address
 */
static inline void can_switch_to_next_tx_buffer(CAN_Type *base)
{
    base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_TSNEXT_MASK;
}

/**
 * @brief Select CAN tx buffer priority mode
 * @param [in] base CAN base address
 * @param [in] enable_priority_decision CAN tx buffer priority mode selection flag
 *  @arg true priority decision mode
 *  @arg false FIFO mode
 */
static inline void can_select_tx_buffer_priority_mode(CAN_Type *base, bool enable_priority_decision)
{
    if (enable_priority_decision) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_TSMODE_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_TSMODE_MASK;
    }
}

/**
 * @brief Get CAN secondary transmit buffer status
 * @param [in] base CAN base address
 * @retval secondary transmit buffer status, 0: empty, 1: <= 1/2 full, 2: > 1/2 full, 3: full
 *
 */
static inline uint8_t can_get_secondary_transmit_buffer_status(CAN_Type *base)
{
    return CAN_CMD_STA_CMD_CTRL_TSSTAT_GET(base->CMD_STA_CMD_CTRL);
}

/**
 * @brief Check whether the primary transmit buffer is full
 * @param [in] base CAN base address
 * @return true for full
 */
static inline bool can_is_primary_transmit_buffer_full(CAN_Type *base)
{
    return ((base->CMD_STA_CMD_CTRL & CAN_CMD_STA_CMD_CTRL_TPE_MASK) != 0U);
}

/**
 * @brief Check whether the secondary transmit buffer is full
 * @param [in] base CAN base address
 * @return true for full
 */
static inline bool can_is_secondary_transmit_buffer_full(CAN_Type *base)
{
    return (CAN_CMD_STA_CMD_CTRL_TSSTAT_GET(base->CMD_STA_CMD_CTRL) == CAN_STB_IS_FULL);
}

/**
 * @brief Check whether the CAN is in BUS off mode
 *
 * @param [in] base CAN base address
 * @return true for bus off mode
 * @return false for non-bus off mode
 */
static inline bool can_is_in_bus_off_mode(CAN_Type *base)
{
    return ((base->CMD_STA_CMD_CTRL & CAN_CMD_STA_CMD_CTRL_BUSOFF_MASK) != 0U);
}

/**
 * @brief Enable can self ack
 * @param [in] base CAN base address
 * @param [in] enable Self-ack enable flag, true or false
 *
 */
static inline void can_enable_self_ack(CAN_Type *base, bool enable)
{
    if (enable) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_SACK_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_SACK_MASK;
    }
}

/**
 * @brief Set CAN receive buffer overflow mode
 * @param [in] base CAN base address
 * @param [in] override_enable receive buffer overflow mode option
 *  @arg true the oldest message will be overwritten
 *  @arg false the new message will not be stored
 */
static inline void can_set_receive_buffer_overflow_mode(CAN_Type *base, bool override_enable)
{
    if (override_enable) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_ROM_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_ROM_MASK;
    }
}

/**
 * @brief Check whether CAN receive buffer is overflow
 * @param [in] base CAN base address
 * @retval true or false
 */
static inline bool can_is_receive_buffer_overflow(CAN_Type *base)
{
    return IS_HPM_BITMASK_SET(base->CMD_STA_CMD_CTRL, CAN_CMD_STA_CMD_CTRL_ROV_MASK);
}

/**
 * @brief Release CAN receive buffer
 *
 * @param [in] base CAN base address
 */
static inline void can_release_receive_buffer(CAN_Type *base)
{
    base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_RREL_MASK;
}

/**
 * @brief Allow can store all date in receive buffer
 * @param [in] base CAN base address
 * @param [in] allow flag to determine whether to store error data frame
 */
static inline void can_allow_store_all_data_in_receive_buffer(CAN_Type *base, bool allow)
{
    if (allow) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_RBALL_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_RBALL_MASK;
    }
}

/**
 * @brief Get CAN receive buffer status
 * @param [in] base CAN base address
 * @retval Receive buffer status, 0: empty, 1: > empty, < almost full, 2: >= almost full, 3: full
 */
static inline uint8_t can_get_receive_buffer_status(CAN_Type *base)
{
    return CAN_CMD_STA_CMD_CTRL_RSTAT_GET(base->CMD_STA_CMD_CTRL);
}

/**
 * @brief Check whether there are data available in receive buffer
 * @param [in] base CAN base address
 * @return true if the receive buffer is not empty
 */
static inline bool can_is_data_available_in_receive_buffer(CAN_Type *base)
{
    return (CAN_CMD_STA_CMD_CTRL_RSTAT_GET(base->CMD_STA_CMD_CTRL) != CAN_RXBUF_IS_EMPTY);
}


/**
 * @brief Enable CAN FD ISO mode
 * @param [in] base CAN base address
 * @param enable CAN-FD ISO mode enable flag
 */
static inline void can_enable_can_fd_iso_mode(CAN_Type *base, bool enable)
{
    if (enable) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_FD_ISO_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_FD_ISO_MASK;
    }
}

/**
 * @brief Enable CAN TX/RX interrupt
 * @param [in] base CAN base address
 * @param [in] mask CAN interrupt mask
 */
static inline void can_enable_tx_rx_irq(CAN_Type *base, uint8_t mask)
{
    base->RTIE |= mask;
}

/**
 * @brief Disable CAN TX/RX interrupt
 * @param [in] base CAN base address
 * @param [in] mask CAN interrupt mask
 */
static inline void can_disable_tx_rx_irq(CAN_Type *base, uint8_t mask)
{
    base->RTIE &= ~mask;
}

/**
 * @brief Clear CAN TX/RX flags
 * @param [in] base CAN base address
 * @param [in] flags CAN TX/RX interrupt flags
 */
static inline void can_clear_tx_rx_flags(CAN_Type *base, uint8_t flags)
{
    base->RTIF = flags;
}

/**
 * @brief Get CAN TX/RX flags
 *
 * @param [in] base CAN base address
 * @retval CAN Tx/RX interrupt flags
 */
static inline uint8_t can_get_tx_rx_flags(CAN_Type *base)
{
    return base->RTIF;
}

/**
 * @brief Enable CAN error interrupt
 * @param [in] base CAN base address
 * @param [in] mask CAN error interrupt mask
 */
static inline void can_enable_error_irq(CAN_Type *base, uint8_t mask)
{
    base->ERRINT |= mask;
}

/**
 * @brief Disable CAN error interrupt
 *
 * @param [in] base CAN base address
 * @param [in] mask CAN error interrupt mask
 */
static inline void can_disable_error_irq(CAN_Type *base, uint8_t mask)
{
    base->ERRINT &= ~mask;
}

/**
 * @brief Get CAN error interrupt flags
 * @param [in] base CAN base address
 * @retval CAN error interrupt flags
 */
static inline uint8_t can_get_error_interrupt_flags(CAN_Type *base)
{
    return (base->ERRINT & (uint8_t) ~(CAN_ERRINT_EPIE_MASK | CAN_ERRINT_ALIE_MASK | CAN_ERRINT_BEIE_MASK));
}

/**
 * @brief Get CAN clear interrupt flags
 * @param [in] base CAN base address
 * @param [in] flags CAN error interrupt flags
 */
static inline void can_clear_error_interrupt_flags(CAN_Type *base, uint8_t flags)
{
    flags &= (uint8_t)~(CAN_ERRINT_EPIE_MASK | CAN_ERRINT_ALIE_MASK | CAN_ERRINT_BEIE_MASK);
    base->ERRINT |= flags;
}

/**
 * @brief Get last CAN error kind
 * @param [in] base CAN base address
 * @retval CAN last error kind
 */
static inline uint8_t can_get_last_error_kind(CAN_Type *base)
{
    return CAN_EALCAP_KOER_GET(base->EALCAP);
}

/**
 * @brief Get CAN last arbitrary lost position
 * @param [in] base CAN base address
 * @retval CAN last arbitrary lost position
 */
static inline uint8_t can_get_last_arbitration_lost_position(CAN_Type *base)
{
    return CAN_EALCAP_ALC_GET(base->EALCAP);
}

/**
 * @brief Set CAN transmitter delay compensation
 *
 * @param [in] base CAN base address
 * @param [in] sample_point delay compensation sample point
 * @param [in] enable delay compensation enable flag
 */
static inline void can_set_transmitter_delay_compensation(CAN_Type *base, uint8_t sample_point, bool enable)
{
#if defined(CAN_SOC_CANFD_TDC_REQUIRE_STUFF_EXCEPTION_WORKAROUND) && (CAN_SOC_CANFD_TDC_REQUIRE_STUFF_EXCEPTION_WORKAROUND == 1)
    (void) sample_point;
    (void) enable;
    base->TDC = CAN_TDC_TDCEN_SET((uint8_t) enable);
#else
    base->TDC = CAN_TDC_SSPOFF_SET(sample_point) | CAN_TDC_TDCEN_SET((uint8_t) enable);
#endif
}

/**
 * @brief Set CAN warning limits
 * @param [in] base CAN base address
 * @param [in] almost_full_limit
 * @param [in] error_warning_limit
 */
static inline void can_set_warning_limits(CAN_Type *base, uint8_t almost_full_limit, uint8_t error_warning_limit)
{
    base->LIMIT = CAN_LIMIT_AFWL_SET(almost_full_limit) | CAN_LIMIT_EWL_SET(error_warning_limit);
}

/**
 * @brief Get CAN receive error count
 * @param [in] base CAN base address
 * @retval CAN receive error count
 */
static inline uint8_t can_get_receive_error_count(CAN_Type *base)
{
    return base->RECNT;
}

/**
 * @brief Get CAN transmit error count
 * @param [in] base CAN base address
 * @retval CAN transmit error count
 */
static inline uint8_t can_get_transmit_error_count(CAN_Type *base)
{
    return base->TECNT;
}

/**
 * @brief Enable a specified CAN filter
 *
 * @param [in] base CAN base address
 * @param index  CAN filter index
 */
static inline void can_enable_filter(CAN_Type *base, uint32_t index)
{
    base->ACF_EN |= (uint16_t) (1U << index);
}

/**
 * @brief Disable a specified CAN filter
 *
 * @param [in] base CAN base address
 * @param index  CAN filter index
 */
static inline void can_disable_filter(CAN_Type *base, uint32_t index)
{
    base->ACF_EN &= (uint16_t) ~(1U << index);
}

/**
 * @brief Get default CAN configuration parameters
 * @param [out] config CAN configuration structure
 * @retval API execution status, status_success or status_invalid_argument
 */
hpm_stat_t can_get_default_config(can_config_t *config);

/**
 * @brief Initialize the CAN controller
 * @param [in] base CAN base address
 * @param [in] config CAN configuration
 * @param [in] src_clk_freq CAN IP source clock frequency
 * @retval API execution status, status_success or status_invalid_argument
 */
hpm_stat_t can_init(CAN_Type *base, can_config_t *config, uint32_t src_clk_freq);

/**
 * @brief De-initialize the CAN controller
 * @param [in] base CAN base address
 */
void can_deinit(CAN_Type *base);


/**
 * @brief Configure the Slow Speed Bit timing using low-level interface
 * @param [in] base CAN base address
 * @param [in] param CAN bit timing parameter
 */
static inline void can_set_slow_speed_timing(CAN_Type *base, const can_bit_timing_param_t *param)
{
    base->S_PRESC = CAN_S_PRESC_S_PRESC_SET(param->prescaler - 1U) | CAN_S_PRESC_S_SEG_1_SET(param->num_seg1 - 2U) |
                                CAN_S_PRESC_S_SEG_2_SET(param->num_seg2 - 1U) | CAN_S_PRESC_S_SJW_SET(param->num_sjw - 1U);
}

/**
 * @brief Configure the Fast Speed Bit timing using low-level interface
 * @param [in] base CAN base address
 * @param [in] param CAN bit timing parameter
 */
static inline void can_set_fast_speed_timing(CAN_Type *base, const can_bit_timing_param_t *param)
{
    base->F_PRESC = CAN_F_PRESC_F_PRESC_SET(param->prescaler - 1U) | CAN_F_PRESC_F_SEG_1_SET(param->num_seg1 - 2U) |
                                CAN_F_PRESC_F_SEG_2_SET(param->num_seg2 - 1U) | CAN_F_PRESC_F_SJW_SET(param->num_sjw - 1U);
}

/**
 * @brief Configure the CAN bit timing for CAN BUS
 * @param [in] base CAN base address
 * @param [in] option CAN bit timing option
 * @param [in] src_clk_freq CAN IP source clock frequency
 * @param [in] baudrate CAN baudrate in MHz
 * @param [in] samplepoint_min Minimum Sample point, range(0-1000), samplepoint_min / 1000 will be used in calculation
 * @param [in] samplepoint_max Maximum Sample point, range(0-1000), samplepoint_max / 1000 will be used in calculation
 * @retval API execution status, status_success or status_invalid_argument
 */
hpm_stat_t can_set_bit_timing(CAN_Type *base, can_bit_timing_option_t option,
                              uint32_t src_clk_freq, uint32_t baudrate,
                              uint16_t samplepoint_min, uint16_t samplepoint_max);


/**
 * @brief Calculate the CAN bit timing for CAN BUS
 * @param [in] src_clk_freq CAN IP source clock frequency
 * @param [in] option CAN bit timing option
 * @param [in] baudrate CAN baudrate in MHz
 * @param [in] samplepoint_min Minimum Sample point, range(0-1000), samplepoint_min / 1000 will be used in calculation
 * @param [in] samplepoint_max Maximum Sample point, range(0-1000), samplepoint_max / 1000 will be used in calculation
 * @param [out] timing_param Calculated CAN bit timing parameter
 * @retval API execution status, status_success or status_invalid_argument
 */
hpm_stat_t can_calculate_bit_timing(uint32_t src_clk_freq, can_bit_timing_option_t option, uint32_t baudrate,
                              uint16_t samplepoint_min, uint16_t samplepoint_max,
                              can_bit_timing_param_t *timing_param);



/**
 * @brief Configure the acceptable filter
 * @param [in] base CAN base address
 * @param [in] config CAN filter configuration
 * @retval API execution status, status_success or status_invalid_argument
 */
hpm_stat_t can_set_filter(CAN_Type *base, const can_filter_config_t *config);

/**
 * @brief Send CAN message using blocking transfer
 * @param [in] base CAN base address
 * @param [in] message CAN message to be sent out
 * @retval API execution status, status_success or status_invalid_argument
 */
hpm_stat_t can_send_message_blocking(CAN_Type *base, const can_transmit_buf_t *message);

/**
 * @brief Send high-priority message using blocking transfer
 * @param [in] base CAN base address
 * @param [in] message CAN message to be sent out
 * @retval API execution status, status_success or status_invalid_argument
 */
hpm_stat_t can_send_high_priority_message_blocking(CAN_Type *base, const can_transmit_buf_t *message);


/**
 * @brief Send CAN message using non-blocking transfer
 * @param [in] base CAN base address
 * @param [in] message CAN message to be sent out
 * @retval API execution status, status_success or status_invalid_argument
 */
hpm_stat_t can_send_message_nonblocking(CAN_Type *base, const can_transmit_buf_t *message);

/**
 * @brief Send high-priority message using non-blocking transfer
 * @param [in] base CAN base address
 * @param [in] message CAN message to be sent out
 * @retval API execution status, status_success or status_invalid_argument
 */
hpm_stat_t can_send_high_priority_message_nonblocking(CAN_Type *base, const can_transmit_buf_t *message);

/**
 * @brief Receive CAN message using blocking transfer
 *
 * @param [in] base CAN base address
 * @param [out] message CAN message buffer
 *
 * @retval status_success API execution is successful
 * @retval status_invalid_argument Invalid parameters
 * @retval status_can_bit_error CAN bit error happened during receiving message
 * @retval status_can_form_error  CAN form error happened during receiving message
 * @retval status_can_stuff_error CAN stuff error happened during receiving message
 * @retval status_can_ack_error CAN ack error happened during receiving message
 * @retval status_can_crc_error CAN crc error happened during receiving message
 * @retval status_can_other_error Other error happened during receiving message
 */
hpm_stat_t can_receive_message_blocking(CAN_Type *base, can_receive_buf_t *message);


/**
 * @brief Read Received CAN message
 *
 * @note  This API assumes that the received CAN message is available.
 *        It can be used in the interrupt handler
 * @param [in] base CAN base address
 * @param [out] message CAN message buffer
 *
 * @retval status_success API execution is successful
 * @retval status_invalid_argument Invalid parameters
 * @retval status_can_bit_error CAN bit error happened during receiving message
 * @retval status_can_form_error  CAN form error happened during receiving message
 * @retval status_can_stuff_error CAN stuff error happened during receiving message
 * @retval status_can_ack_error CAN ack error happened during receiving message
 * @retval status_can_crc_error CAN crc error happened during receiving message
 * @retval status_can_other_error Other error happened during receiving message
 */
hpm_stat_t can_read_received_message(CAN_Type *base, can_receive_buf_t *message);

/**
 * @}
 *
 */


#ifdef __cplusplus
}
#endif


#endif /* HPM_CAN_DRV_H */
