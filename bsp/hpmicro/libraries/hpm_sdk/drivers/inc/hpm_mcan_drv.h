/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_MCAN_DRV_H
#define HPM_MCAN_DRV_H

#include "hpm_common.h"
#include "hpm_mcan_regs.h"
#include "hpm_mcan_soc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief MCAN driver APIs
* @defgroup mcan_interface MCAN driver APIs
* @ingroup mcan_interfaces
* @{
*
*/


enum {
    status_mcan_filter_index_out_of_range = MAKE_STATUS(status_group_mcan, 0),
    status_mcan_rxfifo_empty,
    status_mcan_rxfifo_full,
    status_mcan_txbuf_full,
    status_mcan_txfifo_full,
    status_mcan_rxfifo0_busy,
    status_mcan_rxfifo1_busy,
    status_mcan_txbuf_index_out_of_range,
    status_mcan_rxbuf_index_out_of_range,
    status_mcan_rxbuf_empty,
    status_mcan_tx_evt_fifo_empty,
    status_mcan_timestamp_not_exist,
    status_mcan_ram_out_of_range,
};

/**
 * @brief CAN Interrupt Mask
 */
#define MCAN_INT_ACCESS_TO_RESERVED_ADDR    MCAN_IR_ARA_MASK     /*!< Access to Reserved Address */
#define MCAN_INT_PROTOCOL_ERR_IN_DATA_PHASE MCAN_IR_PED_MASK     /*!< Protocol Error Happened at Data Phase */
#define MCAN_INT_PROTOCOL_ERR_IN_ARB_PHASE  MCAN_IR_PEA_MASK     /*!< Protocol Error Happened at Arbitration Phase */
#define MCAN_INT_WATCHDOG_INT               MCAN_IR_WDI_MASK     /*!< Watchdog interrupt */

#define MCAN_INT_BUS_OFF_STATUS             MCAN_IR_BO_MASK      /*!< Bus-off State Change */
#define MCAN_INT_WARNING_STATUS             MCAN_IR_EW_MASK      /*!< Error Warning State Change */
#define MCAN_INT_ERROR_PASSIVE              MCAN_IR_EP_MASK      /*!< Error Passive State Change */
#define MCAN_INT_ERROR_LOGGING_OVERFLOW     MCAN_IR_ELO_MASK     /*!< Error Logging Overflow */
#define MCAN_INT_BIT_ERROR_UNCORRECTED      MCAN_IR_BEU_MASK     /*!< Bit Error was not corrected */
#define MCAN_INT_BIT_ERROR_CORRECTED        MCAN_IR_BEC_MASK     /*!< Bit Error was corrected */

#define MCAN_INT_MSG_STORE_TO_RXBUF         MCAN_IR_DRX_MASK    /*!< Message was stored to RX Buffer */
#define MCAN_INT_TIMEOUT_OCCURRED           MCAN_IR_TOO_MASK    /*!< Timeout Interrupt */
#define MCAN_INT_MSG_RAM_ACCESS_FAILURE     MCAN_IR_MRAF_MASK   /*!< Message RAM Access Failure */
#define MCAN_INT_TIMESTAMP_WRAPAROUND       MCAN_IR_TSW_MASK    /*!< Timestamp Counter Wrap Around */

#define MCAN_INT_TX_EVT_FIFO_EVT_LOST       MCAN_IR_TEFL_MASK   /*!< TX Event FIFO Element Lost */
#define MCAN_INT_TX_EVT_FIFO_FULL           MCAN_IR_TEFF_MASK   /*!< TX Event FIFO Full */
#define MCAN_INT_TX_EVT_FIFO_WMK_REACHED    MCAN_IR_TEFW_MASK   /*!< TX Event FIFO Watermark Reached */
#define MCAN_INT_TX_EVT_FIFO_NEW_ENTRY      MCAN_IR_TEFN_MASK   /*!< TX Event FIFO New Entry */

#define MCAN_INT_TXFIFO_EMPTY               MCAN_IR_TFE_MASK    /*!< TX FIFO Empty */
#define MCAN_INT_TX_CANCEL_FINISHED         MCAN_IR_TCF_MASK    /*!< Transmission Cancellation Finished */
#define MCAN_INT_TX_COMPLETED               MCAN_IR_TC_MASK     /*!< Transmission Completed */
#define MCAN_INT_HIGH_PRIORITY_MSG          MCAN_IR_HPM_MASK    /*!< High Priority Message */

#define MCAN_INT_RXFIFO1_MSG_LOST           MCAN_IR_RF1L_MASK   /*!< RX FIFO0 Message Lost */
#define MCAN_INT_RXFIFO1_FULL               MCAN_IR_RF1F_MASK   /*!< RX FIFO1 Full */
#define MCAN_INT_RXFIFO1_WMK_REACHED        MCAN_IR_RF1W_MASK   /*!< RX FIFO1 Watermark Reached */
#define MCAN_INT_RXFIFO1_NEW_MSG            MCAN_IR_RF1N_MASK   /*!< RX FIFO1 New Message */

#define MCAN_INT_RXFIFO0_MSG_LOST           MCAN_IR_RF0L_MASK   /*!< RX FIFO0 Message Lost */
#define MCAN_INT_RXFIFO0_FULL               MCAN_IR_RF0F_MASK   /*!< RX FIFO0 Full */
#define MCAN_INT_RXFIFO0_WMK_REACHED        MCAN_IR_RF0W_MASK   /*!< RX FIFO0 Watermark Reached */
#define MCAN_INT_RXFIFI0_NEW_MSG            MCAN_IR_RF0N_MASK   /*!< RX FIFO0 New Message */

/**
 * @brief MCAN Receive Event Flags
 */
#define MCAN_EVENT_RECEIVE (MCAN_INT_RXFIFI0_NEW_MSG | MCAN_INT_RXFIFO1_NEW_MSG | MCAN_INT_MSG_STORE_TO_RXBUF)

/**
 * @brief MCAN Transmit Event Flags
 */
#define MCAN_EVENT_TRANSMIT (MCAN_INT_TX_COMPLETED)
/**
 * @brief MCAN Error Event Flags
 */
#define MCAN_EVENT_ERROR (MCAN_INT_BUS_OFF_STATUS | MCAN_INT_WARNING_STATUS \
                        | MCAN_INT_ERROR_PASSIVE | MCAN_INT_BIT_ERROR_UNCORRECTED)

/**
 * @brief Maximum Transmission Retry Count
 */
#define MCAN_TX_RETRY_COUNT_MAX (10000000UL)
/**
 * @brief Maximum Receive Wait Retry Count
 */
#define MCAN_RX_RETRY_COUNT_MAX (80000000UL)

/***********************************************************************************************************************
 * @brief Default CAN RAM definitions
 **********************************************************************************************************************/
#define MCAN_RAM_WORD_SIZE  (640U)                                  /*!< RAM WORD Size */
/* CAN Filter Element Size Definitions */
#define MCAN_FILTER_ELEM_STD_ID_SIZE (4U)                           /*!< Standard Filter Element Size in Bytes */
#define MCAN_FILTER_ELEM_EXT_ID_SIZE (8U)                           /*!< Extended Filter Element SIze in Bytes */
#define MCAN_STD_FILTER_ELEM_SIZE_MAX (128U)                        /*!< Maximum Standard Filter Element Count */
#define MCAN_EXT_FILTER_ELEM_SIZE_MAX  (64U)                        /*!< Maximum Extended Filter Element Count */
/* MCAN Default Field Size Definitions for CAN2.0 */
#define MCAN_TXRX_ELEM_SIZE_CAN_MAX (4U * sizeof(uint32_t))
#define MCAN_FILTER_SIZE_CAN_DEFAULT (32U)
#define MCAN_TXBUF_SIZE_CAN_DEFAULT (32U)
#define MCAN_RXFIFO_SIZE_CAN_DEFAULT (32U)
#define MCAN_RXBUF_SIZE_CAN_DEFAULT (16U)
/* MCAN Default Field Size Definitions for CANFD */
#define MCAN_TXRX_ELEM_SIZE_CANFD_MAX (18U * sizeof(uint32_t))
#define MCAN_FILTER_SIZE_CANFD_DEFAULT (16U)
#define MCAN_TXBUF_SIZE_CANFD_DEFAULT (8U)
#define MCAN_RXFIFO_SIZE_CANFD_DEFAULT (8U)
#define MCAN_RXBUF_SIZE_CANFD_DEFAULT (4U)

#define MCAN_TXEVT_ELEM_SIZE (8U)

/**
 * @brief CAN Bit Timing Parameters
 */
typedef struct mcan_bit_timing_param_struct {
    uint16_t prescaler; /*!< Data Bit Rate Prescaler */
    uint16_t num_seg1;  /*!< Time segment before sample point (including prop_seg and phase_sge1 */
    uint16_t num_seg2;  /*!< Time segment after sample point */
    uint8_t num_sjw;    /*!< Data (Re)Synchronization Jump Width */
    bool enable_tdc;    /*!< Enable TDC flag, for CANFD data bit timing only */
} mcan_bit_timing_param_t;

/**
 * @brief CAN Bit Timing Options
 */
typedef enum mcan_bit_timing_option {
    mcan_bit_timing_can2_0,          /**< CAN 2.0 bit timing option */
    mcan_bit_timing_canfd_nominal,   /**< CANFD nominal timing option */
    mcan_bit_timing_canfd_data,      /**< CANFD data timing option */
} mcan_bit_timing_option_t;

/**
 * @brief CAN Message Header Size
 */
#define MCAN_MESSAGE_HEADER_SIZE_IN_BYTES (8U)
#define MCAN_MESSAGE_HEADER_SIZE_IN_WORDS (2U)

/**
 * @brief CAN Transmit Message Frame
 *
 * @note Users need to pay attention to the CAN Identifier settings
 *       For standard identifier, the use_ext_id should be set to 0 and the std_id should be used
 *       For extended identifier, the use_ext_id should be set to 1 and the ext_id should be used
 */
typedef struct mcan_tx_message_struct {
    union {
        struct {
            uint32_t ext_id: 29;                        /*!< Extended CAN Identifier */
            uint32_t rtr: 1;                            /*!< Remote Transmission Request */
            uint32_t use_ext_id: 1;                     /*!< Extended Identifier */
            uint32_t error_state_indicator: 1;          /*!< Error State Indicator */
        };
        struct {
            uint32_t : 18;
            uint32_t std_id: 11;                        /*!< Standard CAN Identifier */
            uint32_t : 3;
        };
    };
    struct {
        uint32_t : 8;
        uint32_t message_marker_h: 8;                   /*!< Message Marker[15:8] */
        uint32_t dlc: 4;                                /*!< Data Length Code */
        uint32_t bitrate_switch: 1;                     /*!< Bit Rate Switch */
        uint32_t canfd_frame: 1;                        /*!< CANFD frame */
        uint32_t timestamp_capture_enable: 1;           /*!< Timestamp Capture Enable for TSU */
        uint32_t event_fifo_control: 1;                 /*!< Event FIFO control */
        uint32_t message_marker_l: 8;                   /*!< Message Marker[7:0] */
    };
    union {
        uint8_t data_8[64];                             /*!< Data buffer as byte array */
        uint32_t data_32[16];                           /*!< Data buffer as word array */
    };
} mcan_tx_frame_t;

/**
 * @brief CAN Receive Message Frame
 *
 * @note Users need to pay attention to the CAN Identifier settings
 *       For standard identifier, the use_ext_id should be set to 0 and the std_id should be used
 *       For extended identifier, the use_ext_id should be set to 1 and the ext_id should be used
 */
typedef struct mcan_rx_message_struct {
    union {
        struct {
            uint32_t ext_id: 29;                   /*!< Extended CAN Identifier */
            uint32_t rtr: 1;                       /*!< Remote Frame Flag */
            uint32_t use_ext_id: 1;                /*!< Extended Identifier */
            uint32_t error_state_indicator: 1;     /*!< Error State Indicator */
        };
        struct {
            uint32_t : 18;
            uint32_t std_id: 11;                   /*!< Standard CAN Identifier */
            uint32_t : 3;
        };
    };
    struct {
        union {
            uint16_t rx_timestamp;                  /*!< Received timestamp */
            struct {
                uint16_t rx_timestamp_pointer: 4;   /*!< Timestamp Pointer */
                uint16_t rx_timestamp_captured: 1;  /*!< Timestamp Captured flag */
                uint16_t : 11;
            };
        };
    };
    struct {
        uint16_t dlc: 4;                            /*!< Data Length Code */
        uint16_t bitrate_switch: 1;                 /*!< Bit rate switch flag */
        uint16_t canfd_frame: 1;                    /*!< CANFD Frame flag */
        uint16_t : 1;
        uint16_t filter_index: 7;                   /*!< CAN filter index */
        uint16_t accepted_non_matching_frame: 1;    /*!< Accept non-matching Frame flag */
    };
    union {
        uint8_t data_8[64];                         /*!< Data buffer as byte array */
        uint32_t data_32[16];                       /*!< Data buffer as word array */
    };
} mcan_rx_message_t;

/**
 * @brief TX Event Fifo Element Structure
 */
typedef union mcan_tx_event_fifo_elem_struct {
    struct {
        /* First word */
        union {
            struct {
                uint32_t ext_id: 29;                    /*!< CAN Identifier */
                uint32_t rtr: 1;                        /*!< Remote Transmission Request */
                uint32_t extend_id: 1;                  /*!< Extended Identifier */
                uint32_t error_state_indicator: 1;      /*!< Error State Indicator */
            };
            struct {
                uint32_t : 18;
                uint32_t std_id: 11;
                uint32_t : 3;
            };
        };

        /* first 16-bit of the 2nd word */
        union {
            uint16_t tx_timestamp;                      /*!< Tx Timestamp */
            struct {
                uint16_t tx_timestamp_pointer: 4;       /*!< TX timestamp pointer */
                uint16_t tx_timestamp_captured: 1;      /*!< TX timestamp captured flag */
                uint16_t : 11;
            };
        };
        /* high-half 16-bit of the 2nd word */
        struct {
            uint16_t dlc: 4;                            /*!< Data length code */
            uint16_t bitrate_switch: 1;                 /*!< Bitrate Switch flag */
            uint16_t canfd_frame: 1;                    /*!< CANFD frame */
            uint16_t event_type: 2;                     /*!< Event type */
            uint16_t message_marker: 8;                 /*!< Message Marker */
        };
    };
    uint32_t words[2];
} mcan_tx_event_fifo_elem_t;



/**
 * @brief CAN Identifier Types
 */
#define MCAN_CAN_ID_TYPE_STANDARD (0U)      /*!< Standard Identifier */
#define MCAN_CAN_ID_TYPE_EXTENDED (1U)      /*!< Extended Identifier */

/**
 * @brief MCAN Filter Configuration
 */
typedef union mcan_filter_config_struct {
    struct {
        uint16_t list_start_addr;       /*!< List Start address (CAN Message Buffer Offset) */
        uint16_t list_size;             /*!< Element Count */
    };
    uint32_t reg_val;                   /*!< Register value */
} mcan_filter_config_t;

/**
 * @brief MCAN RXFIFO Configuration
 */
typedef union mcan_rxfifo_config_struct {
    struct {
        uint32_t start_addr: 16;        /*!< Start address (CAN Message Buffer Offset) */
        uint32_t fifo_size: 8;          /*!< FIFO element count */
        uint32_t watermark: 7;          /*!< FIFO watermark */
        uint32_t operation_mode: 1;     /*!< Operation mode */
    };
    uint32_t reg_val;                   /*!< Register value */
} mcan_rxfifo_config_t;

/**
 * @brief MCAN RXBUF Configuration
 */
typedef struct {
    uint32_t start_addr;                /*!< Start address (CAN Message Buffer Offset) */
} mcan_rxbuf_config_t;

/**
 * @brief MCAN Data Field Size Definitions
 */
#define MCAN_DATA_FIELD_SIZE_8BYTES     (0U)
#define MCAN_DATA_FIELD_SIZE_12BYTES    (1U)
#define MCAN_DATA_FIELD_SIZE_16BYTES    (2U)
#define MCAN_DATA_FIELD_SIZE_20BYTES    (3U)
#define MCAN_DATA_FIELD_SIZE_24BYTES    (4U)
#define MCAN_DATA_FIELD_SIZE_32BYTES    (5U)
#define MCAN_DATA_FIELD_SIZE_48BYTES    (6U)
#define MCAN_DATA_FIELD_SIZE_64BYTES    (7U)

/**
 * @brief MCAN FIFO Operation Mode types
 */
#define MCAN_FIFO_OPERATION_MODE_BLOCKING (0U)
#define MCAN_FIFO_OPERATION_MODE_OVERWRITE (1U)

/**
 * @brief  MCAN RXBUF or RXFIFO Element Configuration
 */
typedef union mcan_rx_fifo_or_buf_elem_config_struct {
    struct {
        uint32_t fifo0_data_field_size: 4;      /*!< FIFO0 data field size option */
        uint32_t fifo1_data_field_size: 4;      /*!< FIFO1 data field size option */
        uint32_t buf_data_field_size: 4;        /*!< Buffer Data field size option */
        uint32_t : 20;
    };
    uint32_t reg_val;                           /*!< Register value */
} mcan_rx_fifo_or_buf_elem_config_t;

/**
 * @brief MCAN TXBUF operation mode types
 */
#define MCAN_TXBUF_OPERATION_MODE_FIFO  (0U)
#define MCAN_TXBUF_OPERATION_MODE_QUEUE (1U)


typedef union mcan_txbuf_config_struct {
    struct {
        uint32_t start_addr: 16;                /*!< Start address (CAN Message Buffer Offset) */
        uint32_t dedicated_tx_buf_size: 6;      /*!< Dedicated TX buffer size */
        uint32_t : 2;
        uint32_t fifo_queue_size: 6;            /*!< FIFO or Queue Size */
        uint32_t tx_fifo_queue_mode: 1;         /*!< FIFO or Queue mode selection */
        uint32_t : 1;
    };
    uint32_t reg_val;                           /*!< register value */
} mcan_txbuf_config_t;

typedef struct mcan_txbuf_elem_config_struct {
    uint32_t data_field_size;                   /*!< Data Field size option */
} mcan_txbuf_elem_config_t;

/**
 * @brief MCAN TX Event FIFO Structure
 */
typedef union {
    struct {
        uint16_t start_addr;                    /*!< Start Address(CAN Message Buffer Offset */
        uint8_t fifo_size;                      /*!< FIFO element count */
        uint8_t fifo_watermark;                 /*!< FIFO watermark */
    };
    uint32_t reg_val;                           /*!< register value */
} mcan_tx_evt_fifo_config_t;

/**
 * @brief MCAN RAM Flexible Configuration
 *
 * @Note This Configration provides the full MCAN RAM configuration, this configuration is recommended only for
 *       experienced developers who is skilled at the MCAN IP
 */
typedef struct mcan_ram_flexible_config_struct {
    bool enable_std_filter;                             /*!< Enable Standard Identifier Filter */
    bool enable_ext_filter;                             /*!< Enable Extended Identifier Filter */
    bool enable_rxfifo0;                                /*!< Enable RXFIFO */
    bool enable_rxfifo1;                                /*!< Enable RXFIF1 */
    bool enable_rxbuf;                                  /*!< Enable RXBUF */
    bool enable_txbuf;                                  /*!< Enable TXBUF */
    bool enable_tx_evt_fifo;                            /*!< Enable TX Event FIFO */

    mcan_filter_config_t std_filter_config;             /*!< Standard Identifier Filter Configuration */
    mcan_filter_config_t ext_filter_config;             /*!< Extended Identifier Filter Configuration */

    mcan_txbuf_config_t txbuf_config;                   /*!< TXBUF Configuration */
    mcan_txbuf_elem_config_t txbuf_elem_config;         /*!< TXBUF Element Configuration */
    mcan_tx_evt_fifo_config_t tx_evt_fifo_config;       /*!< TX Event FIFO Configuration */

    mcan_rxfifo_config_t rxfifo0_config;                /*!< RXFIFO0 Configuration */
    mcan_rxfifo_config_t rxfifo1_config;                /*!< RXFIFO1 Configuration */
    mcan_rxbuf_config_t rxbuf_config;                   /*!< RXBUF Configuration */
    mcan_rx_fifo_or_buf_elem_config_t rx_elem_config;   /*!< RX Element Configuration */
} mcan_ram_flexible_config_t;

/**
 * @brief MCAN RAM configuration
 *
 * @Note: This Configuration focuses on the minimum required information for MCAN RAM configuration
 *        The Start address of each BUF/FIFO will be automatically calculated by the MCAN Driver API
 *        This RAM configuration is recommended for the most developers
 */
typedef struct mcan_ram_config_struct {
    bool enable_std_filter;                             /*!< Enable Standard Identifier Filter */
    uint8_t std_filter_elem_count;                      /*!< Standard Identifier Filter Element Count */

    bool enable_ext_filter;                             /*!< Enable Extended Identifier Filter */
    uint8_t ext_filter_elem_count;                      /*!< Extended Identifier Filter Element Count */

    struct {
        uint32_t enable: 4;                            /*!< Enable Flag for RXFIFO */
        uint32_t elem_count: 8;                        /*!< Element Count for RXFIFO */
        uint32_t watermark: 8;                         /*!< Watermark for RXFIFO */
        uint32_t operation_mode: 4;                    /*!< Operation Mode for RXFIFO */
        uint32_t data_field_size: 8;                   /*!< Data field size option for RXFIFO */
    } rxfifos[2];

    bool enable_rxbuf;                                  /*!< Enable RXBUF */
    uint8_t rxbuf_elem_count;                           /*!< RXBUF Element count */
    uint16_t rxbuf_data_field_size;                     /*!< RXBUF Data Field Size option */

    bool enable_txbuf;                                  /*!< Enable TXBUF */
    uint8_t txbuf_data_field_size;                      /*!< TXBUF Data Field Size option */
    uint8_t txbuf_dedicated_txbuf_elem_count;           /*!< Dedicated TXBUF element count */
    uint8_t txbuf_fifo_or_queue_elem_count;             /*!< FIFO/Queue element count */
    uint8_t txfifo_or_txqueue_mode;                     /*!< TXFIFO/QUEUE mode */

    bool enable_tx_evt_fifo;                            /*!< Enable TX Event FIFO */
    uint8_t tx_evt_fifo_elem_count;                     /*!< TX Event FIFO Element count */
    uint8_t tx_evt_fifo_watermark;                      /*!< TX Event FIFO Watermark */
} mcan_ram_config_t;

/**
 * @brief MCAN Accept Non-Matching Frame options
 */
#define MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0 (0U)   /*!< Save non-matching frame to RXFIFO0 */
#define MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO1 (1U)   /*!< Save non-matching frame to RXFIFO1 */
#define MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_REJECT (2U)       /*!< Reject non-matching frame */

/**
 * @brief MCAN Global CAN configuration
 */
typedef struct mcan_global_filter_config_struct {
    uint8_t accept_non_matching_std_frame_option;   /*!< Accept non-matching standard frame option */
    uint8_t accept_non_matching_ext_frame_option;   /*!< Accept non-matching extended frame option */
    bool reject_remote_std_frame;                   /*!< Reject Remote Standard Frame */
    bool reject_remote_ext_frame;                   /*!< Reject Remote Extended Frame */
} mcan_global_filter_config_t;

/**
 * @brief MCAN Filter type definitions
 */
#define MCAN_FILTER_TYPE_RANGE_FILTER (0U)              /*!< CAN Identifier Range filter */
#define MCAN_FILTER_TYPE_SPECIFIED_ID_FILTER (1U)       /*!< CAN Identifier ID filter */
#define MCAN_FILTER_TYPE_CLASSIC_FILTER (2U)            /*!< CAN classic filter */
#define MCAN_FILTER_TYPE_FILTER_DISABLED (3U)           /*!< CAN filter disabled */
#define MCAN_FILTER_TYPE_DUAL_ID_EXT_FILTER_IGNORE_MASK /*!< CAN Identifier Range filter, ignoring extended ID mask */

/**
 * @brief MCAN Filter Configuration Options
 */
#define MCAN_FILTER_ELEM_CFG_DISABLED (0)                                   /*!<  Disable Filter Element */
#define MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH (1U)                /*!< Store data into RXFIFO0 if matching */
#define MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO1_IF_MATCH (2U)                /*!< Store data into RXFIFO1 if matching */
#define MCAN_FILTER_ELEM_CFG_REJECT_ID_IF_MATCH (3U)                        /*!< Reject ID if matching */
#define MCAN_FILTER_ELEM_CFG_SET_PRIORITY_IF_MATCH (4U)                     /*!< Set Priority if matching */
/*!< Set Priority and store into RXFIFO0 if matching */
#define MCAN_FILTER_ELEM_CFG_SET_PRIORITY_AND_STORE_IN_FIFO0_IF_MATCH (5U)
/*!< Set Priority and store into RXFIFO1 if matching */
#define MCAN_FILTER_ELEM_CFG_SET_PRIORITY_AND_STORE_IN_FIFO1_IF_MATCH (6U)
#define MCAN_FILTER_ELEM_CFG_STORE_INTO_RX_BUFFER_OR_AS_DBG_MSG (7U)        /*!< Store into RXBUF if matching */

/**
 * @brief MCAN Filter Element definitions
 */
typedef struct mcan_std_id_filter_elem_struct {
    uint8_t filter_type;            /*!< Filter type */
    uint8_t filter_config;          /*!< Filter configuration */
    uint8_t can_id_type;            /*!< CAN ID type */
    uint8_t sync_message;           /*!< Sync Message */
    union {
        /* This definition takes effect if the filter type is range filter */
        struct {
            uint32_t start_id;      /*!< Start of ID range */
            uint32_t end_id;        /*!< End of ID range */
        };
        /* This definition takes effect if the filter type is dual id filter */
        struct {
            uint32_t id1;           /*!< ID1 */
            uint32_t id2;           /*!< ID2 */
        };
        /* This definition takes effect if the filter type is classic filter */
        struct {
            uint32_t filter_id;     /*!< Filter ID */
            uint32_t filter_mask;   /*!< Filter Mask */
        };
        /* This definition takes effect if the filter configuration is "store into RX Buffer or as debug message"
         *
         *  In this definition, only the extact ID matching mode is activated
         */
        struct {
            uint32_t match_id;          /*!< Matching ID */
            uint32_t offset: 6;         /*!< RX Buffer Index */
            uint32_t filter_event: 3;   /*!< Filter event, set to 0 */
            uint32_t store_location: 2; /*!< Store location, 0 - RX buffer */
            uint32_t : 21;
        };
    };
} mcan_filter_elem_t;

/**
 * @brief MCAN Filter Element List structure
 */
typedef struct mcan_filter_elem_list_struct {
    uint32_t mcan_filter_elem_count;            /*!< Number of Filter element */
    const mcan_filter_elem_t *filter_elem_list; /*!< Filter element list */
} mcan_filter_elem_list_t;

/**
 * @brief MCAN Configuration for all filters
 *
 * @Note The MCAN RAM related settings are excluded
 */
typedef struct mcan_all_filters_config_struct {
    mcan_global_filter_config_t global_filter_config;   /*!< Global Filter configuration */
    uint32_t ext_id_mask;                               /*!< Extended ID mask */
    mcan_filter_elem_list_t std_id_filter_list;         /*!< Standard Identifier Configuration List */
    mcan_filter_elem_list_t ext_id_filter_list;         /*!< Extended Identifier Configuration List */
} mcan_all_filters_config_t;

/**
 * @brief CAN Node Mode types
 */
typedef enum mcan_node_mode_enum {
    mcan_mode_normal = 0,               /*!< CAN works in normal mode */
    mcan_mode_loopback_internal = 1,    /*!< CAN works in internal loopback mode */
    mcan_mode_loopback_external = 2,    /*!< CAN works in external loopback mode */
    mcan_mode_listen_only = 3,          /*!< CAN works in listen-only mode */
} mcan_node_mode_t;

/**
 * @brief MCAN Timestamp Value
 */
typedef struct mcan_timestamp_value_struct {
    bool is_16bit;                  /*!< Timestamp is 16-bit */
    bool is_32bit;                  /*!< Timestamp is 32-bit */
    bool is_64bit;                  /*!< Timestamp is 64-bit */
    bool is_empty;                  /*!< Timestamp is empty */
    union {
        uint16_t ts_16bit;          /*!< 16-bit timestamp value */
        uint32_t ts_32bit;          /*!< 32-bit timestamp value */
        uint64_t ts_64bit;          /*!< 64-bit timestamp value */
        uint32_t words[2];          /*!< timestamp words */
    };
} mcan_timestamp_value_t;

/**
 * @brief MCAN TSU Configuration
 */
typedef struct mcan_tsu_config_struct {
    uint16_t prescaler;             /*!< Prescaler for MCAN clock, Clock source: AHB clock */
    bool capture_on_sof;            /*!< Capture On SOF, true - Capture on SOF, false - Capture on EOF */
    bool use_ext_timebase;          /*!< Use External Timebase */
    uint16_t ext_timebase_src;      /*!< External Timebase source, see the hpm_mcan_soc.h for more details */
    bool enable_tsu;                /*!< Enable Timestamp Unit */
    bool enable_64bit_timestamp;    /*!< Enable 64bit Timestamp */
} mcan_tsu_config_t;

/**
 * @brief MCAN Timestamp Select
 */
#define MCAN_TIMESTAMP_SEL_MIN               (0U)
#define MCAN_TIMESTAMP_SEL_VALUE_ALWAYS_ZERO (0U)     /*!< Timestamp value always equal to 0 */
#define MCAN_TIMESTAMP_SEL_VALUE_INCREMENT   (1U)     /*!< Timestamp value increments according to prescaler */
#define MCAN_TIMESTAMP_SEL_EXT_TS_VAL_USED   (2U)     /*!< External Timestamp value used */
#define MCAN_TIMESTAMP_SEL_MAX               (MCAN_TIMESTAMP_SEL_EXT_TS_VAL_USED)

/**
 * @brief MCAN Internal timestamp configuration
 */
typedef struct mcan_internal_timestamp_config_struct {
    uint8_t counter_prescaler;          /*!< Timestamp Counter Prescaler, clock source: AHB clock */
    uint8_t timestamp_selection;        /*!< Timestamp Select */
} mcan_internal_timestamp_config_t;

/**
 * @brief MCAN Configuration Structure
 */
typedef struct mcan_config_struct {
    union {
        /* This struct takes effect if use_lowlevl_timing_setting = false */
        struct {
            uint32_t baudrate;                      /*!< CAN 2.0 baudrate/CAN-FD Nominal Baudrate, in terms of bps */
            uint32_t baudrate_fd;                   /*!< CANFD data baudrate, in terms of bps */
            uint16_t can20_samplepoint_min;         /*!< Value = Minimum CAN2.0 sample point * 10 */
            uint16_t can20_samplepoint_max;         /*!< Value = Maximum CAN2.0 sample point * 10 */
            uint16_t canfd_samplepoint_min;         /*!< Value = Minimum CANFD sample point * 10 */
            uint16_t canfd_samplepoint_max;         /*!< Value = Maximum CANFD sample point * 10 */
        };
        /* This struct takes effect if use_lowlevl_timing_setting = true */
        struct {
            mcan_bit_timing_param_t can_timing;     /*!< CAN2.0/CANFD nominal timing setting */
            mcan_bit_timing_param_t canfd_timing;   /*!< CANFD data timing setting */
        };
    };
    bool use_lowlevel_timing_setting;               /*!< Use Low-level timing setting */
    mcan_node_mode_t mode;                          /*!< CAN node mode */
    bool enable_non_iso_mode;                       /*!< Enable Non-ISO FD mode */
    bool enable_transmit_pause;                     /*!< Enable Transmit Pause */
    bool enable_edge_filtering;                     /*!< Enable Edge Filtering */
    bool disable_protocol_exception_handling;       /*!< Disable Protocol Exception Handling */
    bool enable_wide_message_marker;                /*!< Enable Wide Message Marker */
    bool use_timestamping_unit;                     /*!< Use external Timestamp Unit */
    bool enable_canfd;                              /*!< Enable CANFD mode */
    bool enable_tdc;                                /*!< Enable transmitter delay compensation */
    mcan_internal_timestamp_config_t timestamp_cfg; /*!< Internal Timestamp Configuration */
    mcan_tsu_config_t tsu_config;                   /*!< TSU configuration */
    mcan_ram_config_t ram_config;                   /*!< MCAN RAM configuration */
    mcan_all_filters_config_t all_filters_config;   /*!< All Filter configuration */
} mcan_config_t;

/**
 * @brief MCAN Timeout Selection Options
 */
#define MCAN_TIMEOUT_SEL_TYPE_CONTINUOUS_OPERATION (0U)
#define MCAN_TIMEOUT_SEL_TYPE_TIMEOUT_CTRL_BY_TX_EVT_FIFO (1U)
#define MCAN_TIMEOUT_SEL_TYPE_TIMEOUT_CTRL_BY_RX_FIFO0 (2U)
#define MCAN_TIMEOUT_SEL_TYPE_TIMEOUT_CTRL_BY_RX_FIFO1 (3U)

/**
 * @brief MCAN Timeout Counter Configuration
 */
typedef struct mcan_timeout_counter_config_struct {
    bool enable_timeout_counter;            /*!< Enable Timeout counter */
    uint8_t timeout_selection;              /*!< Timeout source selection */
    uint16_t timeout_period;                /*!< Timeout period */
} mcan_timeout_counter_config_t;

/**
 * @brief MCAN Error Count Information
 */
typedef struct mcan_error_count_struct {
    uint8_t transmit_error_count;       /*!< Transmit Error Count */
    uint8_t receive_error_count;        /*!< Receive Error Count */
    bool receive_error_passive;         /*!< The Receive Error Counter has reached the error passive level */
    uint8_t can_error_logging_count;    /*!< CAN Error Logging count */
} mcan_error_count_t;

/**
 * @brief MCAN Transmitter Delay Compensation Configuration
 */
typedef struct mcan_tdc_config_t {
    uint8_t ssp_offset;                 /*!< SSP offset */
    uint8_t filter_window_length;       /*!< Filter Window Length */
} mcan_tdc_config_t;


/**
 * @brief MCAN Message Storage Indicator Types
 */
#define MCAN_MESSAGE_STORAGE_INDICATOR_NO_FIFO_SELECTED     (0U)
#define MCAN_MESSAGE_STORAGE_INDICATOR_FIFO_MESSAGE_LOST    (1U)
#define MCAN_MESSAGE_STORAGE_INDICATOR_RXFIFO0              (2U)
#define MCAN_MESSAGE_STORAGE_INDICATOR_RXFIFO1              (3U)

/**
 * @brief MCAN High Priority Message Status Information
 */
typedef struct mcan_high_priority_message_status_struct {
    uint8_t filter_list_type;                            /*!< Filter List Type, 0 - STD filter, 1 - EXT filter */
    uint8_t filter_index;                                /*!< Filter Elem List */
    uint8_t message_storage_indicator;                   /*!< Message Storage Indicator */
    uint8_t buffer_index;
} mcan_high_priority_message_status_t;

/**
 * @brief Enable Transmit Pause
 * @param [in] ptr MCAN base
 */
static inline void mcan_enable_transmit_pause(MCAN_Type *ptr)
{
    ptr->CCCR |= MCAN_CCCR_TXP_MASK;
}

/**
 * @brief Disable Transmit Pause
 * @param [in] ptr MCAN base
 */
static inline void mcan_disable_transmit_pause(MCAN_Type *ptr)
{
    ptr->CCCR &= ~MCAN_CCCR_TXP_MASK;
}

/**
 * @brief Enable Edge Filtering
 * @param [in] ptr MCAN base
 */
static inline void mcan_enable_edge_filtering(MCAN_Type *ptr)
{
    ptr->CCCR |= MCAN_CCCR_EFBI_MASK;
}

/**
 * @brief Disable Edge Filtering
 * @param [in] ptr MCAN base
 */
static inline void mcan_disable_edge_filtering(MCAN_Type *ptr)
{
    ptr->CCCR &= ~MCAN_CCCR_EFBI_MASK;
}

/**
 * @brief Enable Protocol Exception Handling
 * @param [in] ptr MCAN base
 */
static inline void mcan_enable_protocol_exception_handling(MCAN_Type *ptr)
{
    ptr->CCCR &= ~MCAN_CCCR_PXHD_MASK;
}

/**
 * @brief Disable Protocol Exception Handling
 * @param [in] ptr MCAN base
 */
static inline void mcan_disable_protocol_exception_handling(MCAN_Type *ptr)
{
    ptr->CCCR |= MCAN_CCCR_PXHD_MASK;
}

/**
 * @brief Enable Wide Message Marker
 * @param [in] ptr MCAN base
 */
static inline void mcan_enable_wide_message_marker(MCAN_Type *ptr)
{
    ptr->CCCR |= MCAN_CCCR_WMM_MASK;
}

/**
 * @brief Disable Wide Message Marker
 * @param [in] ptr MCAN base
 */
static inline void mcan_disable_wide_message_marker(MCAN_Type *ptr)
{
    ptr->CCCR &= ~MCAN_CCCR_WMM_MASK;
}

/**
 * @brief Enable External Timestamp Unit
 * @param [in] ptr MCAN base
 */
static inline void mcan_enable_tsu(MCAN_Type *ptr)
{
    ptr->CCCR |= MCAN_CCCR_UTSU_MASK;
}

/**
 * @brief Disable External Timestamp Unit
 * @param [in] ptr MCAN base
 */
static inline void mcan_disable_tsu(MCAN_Type *ptr)
{
    ptr->CCCR &= ~MCAN_CCCR_UTSU_MASK;
}

/**
 * @brief Check whether TSU is used
 * @param [in] ptr MCAN base
 * @retval true if TSU is used
 * @retval false if TSU is not used
 */
static inline bool mcan_is_tsu_used(MCAN_Type *ptr)
{
    return ((ptr->CCCR & MCAN_CCCR_UTSU_MASK) != 0U);
}

/**
 * @brief Check whether 64-bit TSU timestamp is used
 * @param [in] ptr MCAN base
 * @retval true if 64-bit timestamp is used
 * @retval false if 32-bit timestamp is used
 */
static inline bool mcan_is_64bit_tsu_timestamp_used(MCAN_Type *ptr)
{
    return ((ptr->TSCFG & MCAN_TSCFG_EN64_MASK) != 0U);
}

/**
 * @brief Enable Bit Rate Switch
 * @param [in] ptr MCAN base
 */
static inline void mcan_enable_bitrate_switch(MCAN_Type *ptr)
{
    ptr->CCCR |= MCAN_CCCR_BRSE_MASK;
}

/**
 * @brief Disable Bit Rate Switch
 * @param [in] ptr MCAN base
 */
static inline void mcan_disable_bitrate_switch(MCAN_Type *ptr)
{
    ptr->CCCR &= ~MCAN_CCCR_BRSE_MASK;
}

/**
 * @brief Enable Auto Retransmission
 * @param [in] ptr MCAN base
 */
static inline void mcan_enable_auto_retransmission(MCAN_Type *ptr)
{
    ptr->CCCR &= ~MCAN_CCCR_DAR_MASK;
}

/**
 * @brief Disable Auto Transmission
 * @param [in] ptr MCAN base
 */
static inline void mcan_disable_auto_retransmission(MCAN_Type *ptr)
{
    ptr->CCCR |= MCAN_CCCR_DAR_MASK;
}

/**
 * @brief Disable Bus monitoring Mode
 * @param [in] ptr MCAN base
 */
static inline void mcan_disable_bus_monitoring_mode(MCAN_Type *ptr)
{
    ptr->CCCR &= ~MCAN_CCCR_MON_MASK;
}

/**
 * @brief Enable Clock Stop Request
 * @param [in] ptr MCAN base
 */
static inline void mcan_enable_clock_stop_request(MCAN_Type *ptr)
{
    ptr->CCCR |= MCAN_CCCR_CSR_MASK;
}

/**
 * @brief Disable Clock Stop Request
 * @param [in] ptr MCAN base
 */
static inline void mcan_disable_clock_stop_request(MCAN_Type *ptr)
{
    ptr->CCCR &= ~MCAN_CCCR_CSR_MASK;
}

/**
 * @brief Enable Clock Stop Acknowledge
 * @param [in] ptr MCAN base
 */
static inline void mcan_enable_clock_stop_acknowledge(MCAN_Type *ptr)
{
    ptr->CCCR |= MCAN_CCCR_CSA_MASK;
}

/**
 * @brief Disable Clock Stop Acknowledge
 * @param [in] ptr MCAN base
 */
static inline void mcan_disable_clock_stop_acknowledge(MCAN_Type *ptr)
{
    ptr->CCCR &= ~MCAN_CCCR_CSA_MASK;
}

/**
 * @brief Disable Restricted Operation Mode
 * @param [in] ptr MCAN base
 */
static inline void mcan_disable_restricted_operation_mode(MCAN_Type *ptr)
{
    ptr->CCCR &= ~MCAN_CCCR_ASM_MASK;
}

/**
 * @brief Get Timestamp Counter Value
 * @param [in] ptr MCAN base
 * @return timestamp value
 */
static inline uint16_t mcan_get_timestamp_counter_value(MCAN_Type *ptr)
{
    return ptr->TSCV;
}

/**
 * @brief Get Timeout value
 * @param [in] ptr MCAN base
 * @return timeout value
 */
static inline uint16_t mcan_get_timeout_counter_value(MCAN_Type *ptr)
{
    return ptr->TOCV;
}

/**
 * @brief Get Error Counter Information
 * @param [in] ptr MCAN base
 * @param [out] err_cnt Error Count buffer
 */
static inline void mcan_get_error_counter(MCAN_Type *ptr, mcan_error_count_t *err_cnt)
{
    uint32_t ecr = ptr->ECR;
    err_cnt->transmit_error_count = MCAN_ECR_TEC_GET(ecr);
    err_cnt->receive_error_count = MCAN_ECR_REC_GET(ecr);
    err_cnt->receive_error_passive = (MCAN_ECR_RP_GET(ecr) == 1U);
    err_cnt->can_error_logging_count = MCAN_ECR_CEL_GET(ecr);
}

/**
 * @brief Get Last Error Code
 * @param [in] ptr MCAN base
 * @return Last Error code
 */
static inline uint8_t mcan_get_last_error_code(MCAN_Type *ptr)
{
    return MCAN_PSR_LEC_GET(ptr->PSR);
}

/**
 * @brief Get Last Data Phase Error Code
 * @param [in] ptr MCAN base
 * @return Last Error Code in Data phase
 */
static inline uint8_t mcan_get_last_data_error_code(MCAN_Type *ptr)
{
    return MCAN_PSR_DLEC_GET(ptr->PSR);
}

/**
 * @brief Get CAN Activity
 * @param [in] ptr MCAN base
 * @return  CAN IP activity
 */
static inline uint8_t mcan_get_activity(MCAN_Type *ptr)
{
    return MCAN_PSR_ACT_GET(ptr->PSR);
}

/**
 * @brief Check whether the CAN node is under error passive state
 * @param [in] ptr MCAN base
 * @return true is CAN is under error passive state
 */
static inline bool mcan_is_in_err_passive_state(MCAN_Type *ptr)
{
    return (MCAN_PSR_EP_GET(ptr->PSR) == 1U);
}

/**
 * @brief Check whether the CAN mode is under Warning State
 * @param [in] ptr MCAN base
 * @return true if the CAN node is under Error Warning State
 */
static inline bool mcan_is_in_error_warning_state(MCAN_Type *ptr)
{
    return (MCAN_PSR_EW_GET(ptr->PSR) == 1U);
}

/**
 * @brief Check whether the CAN node is under Bus-off state
 * @param [in] ptr MCAN base
 * @return true if the CAN node is under Bus-off state
 */
static inline bool mcan_is_in_busoff_state(MCAN_Type *ptr)
{
    return (MCAN_PSR_BO_GET(ptr->PSR) == 1U);
}

/**
 * @brief Get the Last Data Phase Error
 * @param [in] ptr MCAN base
 * @return  The last Data Phase Error
 */
static inline uint8_t mcan_get_data_phase_last_error_code(MCAN_Type *ptr)
{
    return MCAN_PSR_DLEC_GET(ptr->PSR);
}

/**
 * @brief Check Whether the Error Status Indicator Flag is set in the last received CANFD message
 * @param [in] ptr MCAN base
 * @return true if the Error Status Indicator Flag is set in the last received CANFD Message
 */
static inline bool mcan_is_error_state_indicator_flag_set_in_last_received_canfd_msg(MCAN_Type *ptr)
{
    return (MCAN_PSR_RESI_GET(ptr->PSR) == 1U);
}

/**
 * @brief Check whether the Bitrate Switch Flag is set in the last received CANFD message
 * @param [in] ptr MCAN base
 * @return true if Bit rate switch flag is set in the last received CANFD message
 */
static inline bool mcan_is_bitrate_switch_flag_set_in_last_received_canfd_msg(MCAN_Type *ptr)
{
    return (MCAN_PSR_RBRS_GET(ptr->PSR) == 1U);
}

/**
 * @brief Check whether CANFD messages were received
 * @param [in] ptr MCAN base
 * @return true if a CANFD message was received
 */
static inline bool mcan_is_canfd_message_received(MCAN_Type *ptr)
{
    return (MCAN_PSR_RFDF_GET(ptr->PSR) == 1U);
}

/**
 * @brief Check whether Protocol Exception Events were occurred
 * @param [in] ptr MCAN base
 * @return true if Protocol Exception Events were occurred
 */
static inline bool mcan_is_protocol_exception_event_occurred(MCAN_Type *ptr)
{
    return (MCAN_PSR_PXE_GET(ptr->PSR) == 1U);
}

/**
 * @brief Get the Transmitter Delay Compensation Value
 * @param [in] ptr MCAN base
 * @return Transmitter Delay Compensation value
 */
static inline uint8_t mcan_get_transmitter_delay_compensation_value(MCAN_Type *ptr)
{
    return MCAN_PSR_TDCV_GET(ptr->PSR);
}

/**
 * @brief Get Interrupt Flags
 * @param [in] ptr MCAN base
 * @return Interrupt Flags
 */
static inline uint32_t mcan_get_interrupt_flags(MCAN_Type *ptr)
{
    return ptr->IR;
}

/**
 * @brief Clear Interrupt Flags
 * @param [in] ptr MCAN base
 * @param [in] mask Interrupt Mask
 */
static inline void mcan_clear_interrupt_flags(MCAN_Type *ptr, uint32_t mask)
{
    ptr->IR = mask;
}

/**
 * @brief Enable Interrupts
 * @param [in] ptr MCAN base
 * @param [in] mask Interrupt mask
 */
static inline void mcan_enable_interrupts(MCAN_Type *ptr, uint32_t mask)
{
    ptr->ILS &= ~mask;
    ptr->IE |= mask;
    ptr->ILE = 1U;
}

/**
 * @brief Enable TXBUF Interrupt
 * @param [in] ptr MCAN base
 * @param [in] mask Interrupt mask
 */
static inline void mcan_enable_txbuf_interrupt(MCAN_Type *ptr, uint32_t mask)
{
    ptr->TXBTIE |= mask;
}

/**
 * @brief Disable TXBUF Interrupt
 * @param [in] ptr MCAN base
 * @param [in] mask Interrupt mask
 */
static inline void mcan_disable_txbuf_interrupt(MCAN_Type *ptr, uint32_t mask)
{
    ptr->TXBTIE &= ~mask;
}

/**
 * @brief Disable Interrupts
 * @param [in] ptr MCAN base
 * @param [in] mask Interrupt mask
 */
static inline void mcan_disable_interrupts(MCAN_Type *ptr, uint32_t mask)
{
    ptr->IE &= ~mask;
}

/**
 * @brief Enable TXBUF Transmission interrupt
 * @param [in] ptr MCAN base
 * @param [in] mask Interrupt mask
 */
static inline void mcan_enable_txbuf_transmission_interrupt(MCAN_Type *ptr, uint32_t mask)
{
    ptr->TXBTIE |= mask;
}

/**
 * @brief Disable TXBUF Transmission interrupt
 * @param [in] ptr MCAN base
 * @param [in] mask Interrupt mask
 */
static inline void mcan_disable_txbuf_transmission_interrupt(MCAN_Type *ptr, uint32_t mask)
{
    ptr->TXBTIE &= ~mask;
}

/**
 * @brief Enable TXBUF Cancellation Finish interrupt
 * @param [in] ptr MCAN base
 * @param [in] mask Interrupt mask
 */
static inline void mcan_enable_txbuf_cancel_finish_interrupt(MCAN_Type *ptr, uint32_t mask)
{
    ptr->TXBCIE |= mask;
}

/**
 * @brief Disable TXBUF Cancellation Finish interrupt
 * @param [in] ptr MCAN base
 * @param [in] mask Interrupt mask
 */
static inline void mcan_disable_txbuf_cancel_finish_interrupt(MCAN_Type *ptr, uint32_t mask)
{
    ptr->TXBCIE &= ~mask;
}

/**
 * @brief Select Interrupt Line
 * @param [in] ptr MCAN base
 * @param [in] mask Interrupt mask
 * @param [in] line_index Interrupt Line Index
 */
static inline void mcan_interrupt_line_select(MCAN_Type *ptr, uint32_t mask, uint8_t line_index)
{
    if (line_index == 0) {
        ptr->ILS &= ~mask;
    } else {
        ptr->ILS |= mask;
    }
    ptr->ILE = (1UL << line_index);
}

/**
 * @brief Check whether a TXFIFO/TXBUF transmission request is pending
 * @param [in] ptr CAN Base
 * @param [in] index TXBUF/TXFIFO Index
 * @return True is the specified TXFIFO/TXBUF Transmission request is pending
 */
static inline bool mcan_is_transmit_request_pending(MCAN_Type *ptr, uint32_t index)
{
    return ((ptr->TXBRP & ((1UL << index))) != 0U);
}

/**
 * @brief Check whether TXFIFO is full
 * @param [in] ptr MCAN base
 * @return true if TXFIFO is full
 */
static inline bool mcan_is_txfifo_full(MCAN_Type *ptr)
{
    return ((ptr->TXFQS & MCAN_TXFQS_TFQF_MASK) != 0U);
}

/**
 * @brief Get the TXFIFO Put Index
 * @param [in] ptr MCAN base
 * @return The TX FIFO Put Index
 */
static inline uint32_t mcan_get_txfifo_put_index(MCAN_Type *ptr)
{
    return MCAN_TXFQS_TFQPI_GET(ptr->TXFQS);
}

/**
 * @brief Request A Transmission via specified TXBUF Index
 * @param [in] ptr MCAN Base
 * @param [in] index TXBUF index
 */
static inline void mcan_send_add_request(MCAN_Type *ptr, uint32_t index)
{
    ptr->TXBAR = (1UL << index);
}

/**
 * @brief Check whether the Transmission completed via specified TXBUF/TXFIFO
 * @param [in] ptr MCAN base
 * @param [in] index TXBUF Index
 * @return True is the Transmission completed via specified TXBUF
 */
static inline bool mcan_is_transmit_occurred(MCAN_Type *ptr, uint32_t index)
{
    return ((ptr->TXBTO & (1UL << index)) != 0U);
}

/**
 * @brief Check Whether there are data available in specified RXBUF
 * @param [in] ptr MCAN Base
 * @param [in] index  RXBUF index
 * @return True if there are data available
 */
static inline bool mcan_is_rxbuf_data_available(MCAN_Type *ptr, uint32_t index)
{
    bool result;
    if (index < 32U) {
        result = (ptr->NDAT1 & (1UL << index)) != 0U;
    } else if (index < 64U) {
        result = (ptr->NDAT2 & (1UL << (index - 32U))) != 0U;
    } else {
        result = false;
    }
    return result;
}

/**
 * @brief Clear RXBUF Data available Flag for specified RXBUF
 * @param [in] ptr MCAN base
 * @param [in] index RXBUF index
 */
static inline void mcan_clear_rxbuf_data_available_flag(MCAN_Type *ptr, uint32_t index)
{
    if (index < 32U) {
        ptr->NDAT1 = (1UL << index);
    } else if (index < 64U) {
        ptr->NDAT2 = (1UL << (index - 32U));
    } else {
        /* Do nothing */
    }
}

/**
 * @brief Check whether specified Interrupt is set
 * @param [in] ptr MCAN Base
 * @param [in] mask Interrupt Flags
 * @retval true if corresponding bits are set
 */
static inline bool mcan_is_interrupt_flag_set(MCAN_Type *ptr, uint32_t mask)
{
    return ((ptr->IR & mask) != 0U);
}

static inline bool mcan_is_tsu_timestamp_available(MCAN_Type *ptr, uint32_t index)
{
    bool is_available = false;
    if (index < ARRAY_SIZE(ptr->TS_SEL)) {
        is_available = ((ptr->TSS1 & (1UL << index)) != 0U);
    }
    return is_available;
}

/**
 * @brief Read 32bit Timestamp value from TSU
 * @param [in] ptr MCAN Base
 * @param [in] index Timestamp pointer
 * @return Timestamp value
 */
uint32_t mcan_read_32bit_tsu_timestamp(MCAN_Type *ptr, uint32_t index);

/**
 * @brief Read 64bit Timestamp value from TSU
 * @param [in] ptr MCAN Base
 * @param [in] index Timestamp pointer
 * @return Timestamp value
 */
uint64_t mcan_read_64bit_tsu_timestamp(MCAN_Type *ptr, uint32_t index);

/**
 * @brief Get High Priority Message Status
 * @param [in] ptr MCAN base
 * @param [out] status Pointer to High Priority Message Status Buffer
 */
void mcan_get_high_priority_message_status(MCAN_Type *ptr, mcan_high_priority_message_status_t *status);

/**
 * @brief Get Default CAN configuration
 * @param [in] ptr MCAN base
 * @param [out] config CAN configuration
 */
void mcan_get_default_config(MCAN_Type *ptr, mcan_config_t *config);

/**
 * @brief Get message Size from Data Length Code
 * @param [in] dlc Data Length Code
 * @return Message Size in Bytes
 */
uint8_t mcan_get_message_size_from_dlc(uint8_t dlc);

uint8_t mcan_get_data_field_size(uint8_t data_field_size_option);

/**
 * @brief Get Default Full MCAN RAM configuration
 * If the device is configured as classic CAN node, the default CAN RAM settings are as below:
 *  - Standard Identifier Filter Elements: 32
 *  - Extended Identifier Filter Elements: 32
 *  - TXBUF Elements Info:
 *      - Element Count:32
 *      - Dedicated TXBUF element count: 16
 *      - TXFIFO/QQueue element count: 16
 *      - Data Field Size: 8
 *   - RXFIFO0 Elements Info:
 *      - Element Count :32
 *      - Data Field Size: 8
 *   - RXFIFO1 Elements Info:
 *      - Element Count : 32
 *      - Data Field Size: 8
 *    - RXBUF Element Info:
 *      - Element Count: 16
 *      - Data Field Size : 8
 *    - TX Event FIFO Element Count: 32
 * If the device is configured as CANFD node, the default CAN RAM settings are as below:
 *  - Standard Identifier Filter Elements: 16
 *  - Extended Identifier Filter Elements: 16
 *  - TXBUF Elements Info:
 *      - Element Count:8
 *      - Dedicated TXBUF element count: 4
 *      - TXFIFO/QQueue element count: 4
 *      - Data Field Size: 64
 *   - RXFIFO0 Elements Info:
 *      - Element Count : 8
 *      - Data Field Size: 64
 *   - RXFIFO1 Elements Info:
 *      - Element Count : 8
 *      - Data Field Size: 64
 *    - RXBUF Element Info:
 *      - Element Count: 4
 *      - Data Field Size : 64
 *    - TX Event FIFO Element Count: 8
 *
 * @param [in] ptr MCAN base
 * @param [out] ram_config CAN RAM Configuration
 * @param [in] enable_canfd CANFD enable flag
 */
void mcan_get_default_ram_flexible_config(MCAN_Type *ptr, mcan_ram_flexible_config_t *ram_config, bool enable_canfd);

/**
 * @brief Get Default MCAN RAM configuration
 * If the device is configured as classic CAN node, the default CAN RAM settings are as below:
 *  - Standard Identifier Filter Elements: 32
 *  - Extended Identifier Filter Elements: 32
 *  - TXBUF Elements Info:
 *      - Element Count:32
 *      - Dedicated TXBUF element count: 16
 *      - TXFIFO/QQueue element count: 16
 *      - Data Field Size: 8
 *   - RXFIFO0 Elements Info:
 *      - Element Count :32
 *      - Data Field Size: 8
 *   - RXFIFO1 Elements Info:
 *      - Element Count : 32
 *      - Data Field Size: 8
 *    - RXBUF Element Info:
 *      - Element Count: 16
 *      - Data Field Size : 8
 *    - TX Event FIFO Element Count: 32
 * If the device is configured as CANFD node, the default CAN RAM settings are as below:
 *  - Standard Identifier Filter Elements: 16
 *  - Extended Identifier Filter Elements: 16
 *  - TXBUF Elements Info:
 *      - Element Count:8
 *      - Dedicated TXBUF element count: 4
 *      - TXFIFO/QQueue element count: 4
 *      - Data Field Size: 64
 *   - RXFIFO0 Elements Info:
 *      - Element Count : 8
 *      - Data Field Size: 64
 *   - RXFIFO1 Elements Info:
 *      - Element Count : 8
 *      - Data Field Size: 64
 *    - RXBUF Element Info:
 *      - Element Count: 4
 *      - Data Field Size : 64
 *    - TX Event FIFO Element Count: 8
 *
 * @param [in] ptr MCAN base
 * @param [out] ram_config CAN RAM Configuration
 * @param [in] enable_canfd CANFD enable flag
 */
void mcan_get_default_ram_config(MCAN_Type *ptr, mcan_ram_config_t *simple_config, bool enable_canfd);

/**
 * @brief Initialize CAN controller
 * @param [in] ptr MCAN base
 * @param [in] config CAN configuration
 * @param [in] src_clk_freq CAN clock frequency
 * @retval status_success if operation is successful
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t mcan_init(MCAN_Type *ptr, mcan_config_t *config, uint32_t src_clk_freq);

/**
 * @brief Configure MCAN RAM will Full RAM configuration
 * @param [in] ptr MCAN base
 * @param [in] config MCAN RAM Full Configuration
 * @return status_success if no errors reported
 */
hpm_stat_t mcan_config_ram_with_flexible_config(MCAN_Type *ptr, mcan_ram_flexible_config_t *config);

/**
 * @brief Configure MCAN RAM will Simplified RAM configuration
 * @param [in] ptr MCAN base
 * @param [in] config MCAN RAM configuration
 * @return status_success if no errors reported
 */
hpm_stat_t mcan_config_ram(MCAN_Type *ptr, mcan_ram_config_t *config);

/**
 * @brief Configure All CAN filters
 * @param [in] ptr MCAN base
 * @param [in] config All CAN Filter configuration
 * @return status_success if no errors reported
 */
hpm_stat_t mcan_config_all_filters(MCAN_Type *ptr, mcan_all_filters_config_t *config);

/**
 * @brief Configure Transmitter Delay Compensation
 * @param [in] ptr MCAN base
 * @param [in] config Transmitter Delay compensation configure
 * @return status_success if no errors reported
 */
hpm_stat_t mcan_config_transmitter_delay_compensation(MCAN_Type *ptr, mcan_tdc_config_t *config);

/**
 * @brief Configure Global Filter
 * @param [in] ptr MCAN base
 * @param [in] filter_config Global Filter Configuration
 * @return status_success if no errors reported
 */
hpm_stat_t mcan_set_global_filter_config(MCAN_Type *ptr, mcan_global_filter_config_t *filter_config);

/**
 * @brief Set CAN filter element
 * @param [in] ptr MCAN base
 * @param [in] filter_elem CAN filter element
 * @param [in] index CAN Filter element index
 * @return status_success if no errors reported
 */
hpm_stat_t mcan_set_filter_element(MCAN_Type *ptr, const mcan_filter_elem_t *filter_elem, uint32_t index);

/**
 * @brief Write Frame to CAN TX Buffer
 * @param [in] ptr MCAN base
 * @param [in] index TX Buffer Index
 * @param [in] tx_frame TX frame
 * @return status_success if no errors reported
 */
hpm_stat_t mcan_write_txbuf(MCAN_Type *ptr, uint32_t index, mcan_tx_frame_t *tx_frame);

/**
 * @brief Write Frame CAN to TXFIFO
 * @param [in] ptr MCAN base
 * @param [in] tx_frame TX frame
 * @return status_success if no errors reported
 */
hpm_stat_t mcan_write_txfifo(MCAN_Type *ptr, mcan_tx_frame_t *tx_frame);

/**
 * @brief Read message from CAN RXBUF
 * @param [in] ptr MCAN base
 * @param [in] index Index of RXBUF
 * @param [out] rx_frame Buffer to hold RX frame
 * @return status_success if no errors reported
 */
hpm_stat_t mcan_read_rxbuf(MCAN_Type *ptr, uint32_t index, mcan_rx_message_t *rx_frame);

/**
 * @brief Read message from CAN RXBUF
 * @param [in] ptr MCAN base
 * @param [in] fifo_index RXFIFO index, 0 - RXFO0, 1 - RXFIFO1
 * @param [out] rx_frame Buffer to hold RX frame
 * @return status_success if no errors reported
 */
hpm_stat_t mcan_read_rxfifo(MCAN_Type *ptr, uint32_t fifo_index, mcan_rx_message_t *rx_frame);

/**
 * @brief Read TX Event from CAN TX EVENT FIFO
 * @param [in] ptr MCAN base
 * @param [out] tx_evt TX Event Buffer
 * @retval status_success if no errors happened
 * @retval status_mcan_tx_evt_fifo_empty if there are no TX events available
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t mcan_read_tx_evt_fifo(MCAN_Type *ptr, mcan_tx_event_fifo_elem_t *tx_evt);

/**
 * @brief Transmit CAN message in blocking way
 * @param [in] ptr MCAN base
 * @param [in] tx_frame CAN Transmit Message buffer
 * @return status_success if no errors reported
 */
hpm_stat_t mcan_transmit_blocking(MCAN_Type *ptr, mcan_tx_frame_t *tx_frame);

/**
 * @brief Transmit CAN message via TX in blocking way
 * @param [in] ptr MCAN base
 * @param [in] tx_frame CAN Transmit Message buffer
 * @return status_success if no errors reported
 */
hpm_stat_t mcan_transmit_via_txbuf_nonblocking(MCAN_Type *ptr, uint32_t index, mcan_tx_frame_t *tx_frame);

/**
 * @brief Receive CAN Frame from RXBUF in blocking way
 * @param [in] ptr MCAN base
 * @param [in] index RXBUF index
 * @param [out] rx_frame Buffer to hold Received Frame
 * @return status_success if no errors reported
 */
hpm_stat_t mcan_receive_from_buf_blocking(MCAN_Type *ptr, uint32_t index, mcan_rx_message_t *rx_frame);

/**
 * @brief Receive CAN Frame from RXFIFO in blocking way
 * @param [in] ptr MCAN base
 * @param [in] fifo_index RXFIFO index, 0 - RXFIFO0, 1 - RXFIFO1
 * @param [out] rx_frame Buffer to hold Received Frame
 * @return status_success if no errors reported
 */
hpm_stat_t mcan_receive_from_fifo_blocking(MCAN_Type *ptr, uint32_t fifo_index, mcan_rx_message_t *rx_frame);

/**
 * @brief Get Timstamp from MCAN TX Event
 * @param [in] ptr MCAN base
 * @param [in] tx_evt TX Event Element
 * @param [out] timestamp Timestamp value
 * @retval status_success if no errors happened
 * @retval status_invalid_argument if any parameters are invalid
 * @retval status_mcan_timestamp_not_exist if no timestamp information is available
 */
hpm_stat_t mcan_get_timestamp_from_tx_event(MCAN_Type *ptr,
                                            const mcan_tx_event_fifo_elem_t *tx_evt,
                                            mcan_timestamp_value_t *timestamp);

/**
 * @brief Get Timstamp from MCAN RX frame
 * @param [in] ptr MCAN base
 * @param [in] rx_msg Received message
 * @param [out] timestamp Timestamp value
 * @retval status_success if no errors happened
 * @retval status_invalid_argument if any parameters are invalid
 * @retval status_mcan_timestamp_not_exist if no timestamp information is available
 */
hpm_stat_t mcan_get_timestamp_from_received_message(MCAN_Type *ptr,
                                                    const mcan_rx_message_t *rx_msg,
                                                    mcan_timestamp_value_t *timestamp);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif


#endif /* HPM_MCAN_DRV_H */
