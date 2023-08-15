/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "hpm_mcan_drv.h"
#include <string.h>
#include <assert.h>

#define MCAN_CAN_BAUDRATE_DEFAULT (500UL * 1000UL)          /*!< Default CAN2.0 baudrate:500 kbps */
#define MCAN_CANFD_BAUDRATE_DEFAULT (2UL * 1000UL * 1000UL)  /*!< Default CANFD baudrate: 2 Mbps */

/***********************************************************************************************************************
 *
 *  Definitions
 *
 **********************************************************************************************************************/
#define NUM_TQ_SYNC_SEG (1U)

/**
 * @brief CAN2.0 Timing related definitions
 */
#define TSEG1_MIN_FOR_CAN2_0 (2U)
#define TSEG1_MAX_FOR_CAN2_0 (256U)
#define TSEG2_MIN_FOR_CAN2_0 (2U)
#define TSEG2_MAX_FOR_CAN2_0 (128U)
#define TSJW_MIN_FOR_CAN2_0 (1U)
#define TSJW_MAX_FOR_CAN2_0 (128U)
#define PRESCALER_MIN_FOR_CAN2_0 (1U)
#define PRESCALER_MAX_FOR_CAN2_0 (512U)
#define NUM_TQ_MIN_FOR_CAN2_0 (8U)
#define NUM_TQ_MAX_FOR_CAN2_0 (TSEG1_MAX_FOR_CAN2_0 + TSEG2_MAX_FOR_CAN2_0)

/**
 * @brief CANFD Nominal Timing related definitions
 */
#define TSEG1_MIN_FOR_CANFD_NOMINAL (2U)
#define TSEG1_MAX_FOR_CANFD_NOMINAL (256U)
#define TSEG2_MIN_FOR_CANFD_NOMINAL (1U)
#define TSEG2_MAX_FOR_CANFD_NOMINAL (32U)
#define TSJW_MIN_FOR_CANFD_NOMINAL (1U)
#define TSJW_MAX_FOR_CANFD_NOMINAL (128U)
#define NUM_TQ_MIN_FOR_CANFD_NOMINAL (8U)
#define NUM_TQ_MAX_FOR_CANFD_NOMINAL (TSEG1_MAX_FOR_CANFD_NOMINAL + TSEG2_MAX_FOR_CANFD_NOMINAL)
#define PRESCALER_MIN_FOR_CANFD_NOMINAL (1U)
#define PRESCALER_MAX_FOR_CANFD_NOMINAL (512U)

/**
 * @brief CANFD Data Timing related definitions
 */
#define TSEG1_MIN_FOR_CANFD_DATA (2U)
#define TSEG1_MAX_FOR_CANFD_DATA (31U)
#define TSEG2_MIN_FOR_CANFD_DATA (0U)
#define TSEG2_MAX_FOR_CANFD_DATA (15U)
#define TSJW_MIN_FOR_CANFD_DATA (0U)
#define TSJW_MAX_FOR_CANFD_DATA (15U)
#define PRESCALER_MIN_FOR_CANFD_DATA (1U)
#define PRESCALER_MAX_FOR_CANFD_DATA (32U)

#define NUM_TQ_MIN_FOR_CANFD_DATA (8U)
#define NUM_TQ_MAX_FOR_CANFD_DATA (TSEG1_MAX_FOR_CANFD_DATA + TSEG2_MAX_FOR_CANFD_DATA)

#define MIN_TQ_MUL_PRESCALE (8U)
#define NUM_PRESCALE_MAX (256U)

#define CAN_SAMPLEPOINT_MIN (750U)
#define CAN_SAMPLEPOINT_MAX (875U)

/* Invalid start address of MCAN RAM */
#define MCAN_RAM_ADDR_INVALID   ((1UL << 16) - 1U)

/* Maximum CAN TDC offset value */
#define MCAN_MAX_TDC_OFFSET ((uint32_t)(MCAN_TDCR_TDCO_MASK >> MCAN_TDCR_TDCO_SHIFT))

/**
 * @brief MCAN bit timing table
 */
typedef struct mcan_bit_timing_table_struct {
    uint16_t tq_min;                    /*!< Minimum Tq */
    uint16_t tq_max;                    /*!< Maximum Tq */
    uint16_t seg1_min;                  /*!< Minimum TSEG1 */
    uint16_t seg1_max;                  /*!< Maximum TSEG1 */
    uint8_t seg2_min;                   /*!< Minimum TSEG2 */
    uint8_t seg2_max;                   /*!< Maximum TSEG2 */
    uint8_t sjw_min;                    /*!< Minimum SJW */
    uint8_t sjw_max;                    /*!< Maximum SJW */
    uint8_t min_diff_seg1_minus_seg2;   /*!< Minimum value of (TSEG1 - TSEG2 ) */
    uint8_t prescaler_min;              /*!< Minimum Prescaler value */
    uint16_t prescaler_max;             /*!< Maximum Prescaler value */
} mcan_bit_timing_table_t;

/***********************************************************************************************************************
 *
 *  Variables
 *
 **********************************************************************************************************************/
static const mcan_bit_timing_table_t k_mcan_bit_timing_tbl[3] = {
    /* CAN2.0 bit timing requirement */
    {
        /* TQ range */
        .tq_min = NUM_TQ_MIN_FOR_CAN2_0, .tq_max = NUM_TQ_MAX_FOR_CAN2_0,
        /* SEG1 range(Including Sync_Seg +  Prop_Seg + Phase_Seg1 */
        .seg1_min = TSEG1_MIN_FOR_CAN2_0, .seg1_max = TSEG1_MAX_FOR_CAN2_0,
        /* SEG2 Range */
        .seg2_min = TSEG2_MIN_FOR_CAN2_0, .seg2_max = TSEG2_MAX_FOR_CAN2_0,
        /* SJW range */
        .sjw_min = TSJW_MIN_FOR_CAN2_0, .sjw_max = TSJW_MAX_FOR_CAN2_0, .min_diff_seg1_minus_seg2 = 2,
        /* Prescaler range */
        .prescaler_min = PRESCALER_MIN_FOR_CAN2_0, .prescaler_max = PRESCALER_MAX_FOR_CAN2_0,
    },
    /* CANFD Nominal Bit timing requirement */
    {
        /* TQ range */
        .tq_min = NUM_TQ_MIN_FOR_CANFD_NOMINAL, .tq_max = NUM_TQ_MAX_FOR_CANFD_NOMINAL,
        /* SEG1 range(Including Sync_Seg +  Prop_Seg + Phase_Seg1 */
        .seg1_min = TSEG1_MIN_FOR_CANFD_NOMINAL, .seg1_max = TSEG1_MAX_FOR_CANFD_NOMINAL,
        /* SEG2 range */
        .seg2_min = TSEG2_MIN_FOR_CANFD_NOMINAL, .seg2_max = TSEG2_MAX_FOR_CANFD_NOMINAL,
        /* SJW range */
        .sjw_min = TSJW_MIN_FOR_CANFD_NOMINAL, .sjw_max = TSJW_MAX_FOR_CANFD_NOMINAL, .min_diff_seg1_minus_seg2 = 2,
        /* Prescaler range */
        .prescaler_min = PRESCALER_MIN_FOR_CANFD_NOMINAL, .prescaler_max = PRESCALER_MAX_FOR_CANFD_NOMINAL
    },
    /* CANFD Data Bit timing requirement */
    {
        /* TQ range */
        .tq_min = NUM_TQ_MIN_FOR_CANFD_DATA, .tq_max = NUM_TQ_MAX_FOR_CANFD_DATA,
        /* SEG1 range(Including Sync_Seg +  Prop_Seg + Phase_Seg2 */
        .seg1_min = TSEG1_MIN_FOR_CANFD_DATA, .seg1_max = TSEG1_MAX_FOR_CANFD_DATA,
        /* SEG2 range */
        .seg2_min = TSEG2_MIN_FOR_CANFD_DATA, .seg2_max = TSEG2_MAX_FOR_CANFD_DATA,
        /* SJW range */
        .sjw_min = TSJW_MIN_FOR_CANFD_DATA, .sjw_max = TSJW_MAX_FOR_CANFD_DATA, .min_diff_seg1_minus_seg2 = 1,
        /* Prescaler range */
        .prescaler_min = PRESCALER_MIN_FOR_CANFD_DATA, .prescaler_max = PRESCALER_MAX_FOR_CANFD_DATA
    }};

static const mcan_filter_elem_t k_default_std_id_filter = {
    /* Use classic filter */
    .filter_type = MCAN_FILTER_TYPE_CLASSIC_FILTER,
    /* Store message into RXFIFO0 if matching */
    .filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH,
    /* For Standard Identify only */
    .can_id_type = MCAN_CAN_ID_TYPE_STANDARD,
    /* Sync Message, only evaluated when "CCCR.UTSU" is set */
    .sync_message = 0U,
    /* Don't care if mask is set to all 1s */
    .filter_id = 0U,
    /* Accept all messages */
    .filter_mask = 0x7FFU,
};

static const mcan_filter_elem_t k_default_ext_id_filter = {
    /* Use classic filter */
    .filter_type = MCAN_FILTER_TYPE_CLASSIC_FILTER,
    /* Store message into RXFIFO0 if matching */
    .filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH,
    /* For Standard Identify only */
    .can_id_type = MCAN_CAN_ID_TYPE_EXTENDED,
    /* Sync Message, only evaluated when "CCCR.UTSU" is set */
    .sync_message = 0,
    /* Don't care if mask is set to all 1s */
    .filter_id = 0,
    /* Accept all messages */
    .filter_mask = 0x1FFFFFFFUL,
};

/***********************************************************************************************************************
 *
 *  Prototypes
 *
 **********************************************************************************************************************/
/**
 * @brief Set Nominal Bit timing
 *
 * @param [in] ptr MCAN base
 * @param [in] bit_timing Bit timing parameter
 */
static void mcan_set_can_nominal_bit_timing(MCAN_Type *ptr, const mcan_bit_timing_param_t *bit_timing);

/**
 * @brief Set CANFD Data Bit timing
 *
 * @param [in] ptr MCAN base
 *
 * @param [in] bit_timing Bit timing parameter
 */
static void mcan_set_can_data_bit_timing(MCAN_Type *ptr, const mcan_bit_timing_param_t *bit_timing);

/**
 * @brief Calculate the closest prescaler
 *
 * @param [in] num_tq_mul_prescaler Number of TQ * Prescaler
 * @param [in] start_prescaler Start of Prescaler value
 * @param [in] max_tq Maximum Timing Quantum
 * @param [in] min_tq Minimum Timing Quantum
 *
 * @return Calculated prescaler value
 */
static uint32_t mcan_calculate_closest_prescaler(uint32_t num_tq_mul_prescaler,
                                                 uint32_t start_prescaler,
                                                 uint32_t max_tq,
                                                 uint32_t min_tq);

/**
 * @brief Calculate Bit timing from baudrate
 *
 * @param [in] src_clk_freq CAN IP clock used for generating bit timing
 * @param [in] option CAN bit timing option
 * @param [in] baudrate CAN baudrate in bps
 * @param [in] samplepoint_min Minimum sample point, value = actual sample point * 1000
 * @param [in] samplepoint_max Maximum sample point, value = actual sample point * 1000
 * @param [out] timing_param Calculated Bit timing parameter
 *
 * @retval status_success if no errors happened
 * @retval status_invalid_argument if the timing parameters cannot be calculated from specified baudrate
 */
static hpm_stat_t mcan_calc_bit_timing_from_baudrate(uint32_t src_clk_freq,
                                                     mcan_bit_timing_option_t option,
                                                     uint32_t baudrate,
                                                     uint16_t samplepoint_min,
                                                     uint16_t samplepoint_max,
                                                     mcan_bit_timing_param_t *timing_param);

/**
 * @brief Set MCAN bit timing from Baudrate
 *
 * @param [in] ptr MCAN base
 * @param [in] option MCAN bit timing option
 * @param [in] src_clk_freq CAN IP clock used for generating bit timing
 * @param [in] baudrate Baudrate in bps
 * @param [in] samplepoint_min Minimum sample point, value = actual sample point * 1000
 * @param [in] samplepoint_max Maximum sample point, value = actual sample point * 1000
 *
 * @retval status_success if no errors happened
 * @retval status_invalid_argument if the timing parameters cannot be calculated from specified baudrate
 */
static hpm_stat_t mcan_set_bit_timing_from_baudrate(MCAN_Type *ptr,
                                                    mcan_bit_timing_option_t option,
                                                    uint32_t src_clk_freq,
                                                    uint32_t baudrate,
                                                    uint16_t samplepoint_min,
                                                    uint16_t samplepoint_max);

/**
 * @brief Configure MCAN TSU
 *
 * @param [in] ptr MCAN base
 * @param [in] config TSU configuration
 * @retval status_success if no errors happened
 *
 * @retval status_invalid_arugment if any parameters are invalid
 */
static hpm_stat_t mcan_set_tsu(MCAN_Type *ptr, mcan_tsu_config_t *config);

/**
 * @brief Configure MCAN internal timestamp
 *
 * @param [in] ptr MCAN base
 * @param [in] config Internal Timestamp Configuratiojn
 * @retval status_success if no errors happened
 *
 * @retval status_invalid_arugment if any parameters are invalid
 */
static hpm_stat_t mcan_set_internal_timestamp(MCAN_Type *ptr, mcan_internal_timestamp_config_t *config);

/***********************************************************************************************************************
 *
 *  Codes
 */
static void mcan_set_can_nominal_bit_timing(MCAN_Type *ptr, const mcan_bit_timing_param_t *bit_timing)
{
    ptr->NBTP = MCAN_NBTP_NBRP_SET(bit_timing->prescaler - 1U) | MCAN_NBTP_NTSEG1_SET(bit_timing->num_seg1 - 1U) |
                MCAN_NBTP_NTSEG2_SET(bit_timing->num_seg2 - 1U) | MCAN_NBTP_NSJW_SET(bit_timing->num_sjw - 1U);
}

static void mcan_set_can_data_bit_timing(MCAN_Type *ptr, const mcan_bit_timing_param_t *bit_timing)
{
    ptr->DBTP = MCAN_DBTP_DBRP_SET(bit_timing->prescaler - 1U) | MCAN_DBTP_DTSEG1_SET(bit_timing->num_seg1 - 1U) |
                MCAN_DBTP_DTSEG2_SET(bit_timing->num_seg2 - 1U) | MCAN_DBTP_DSJW_SET(bit_timing->num_sjw - 1U) |
                MCAN_DBTP_TDC_SET((uint32_t) bit_timing->enable_tdc);
}

static uint32_t mcan_calculate_closest_prescaler(uint32_t num_tq_mul_prescaler,
                                                 uint32_t start_prescaler,
                                                 uint32_t max_tq,
                                                 uint32_t min_tq)
{
    bool has_found = false;

    uint32_t prescaler = start_prescaler;

    while (!has_found) {
        if ((num_tq_mul_prescaler / prescaler > max_tq) || (num_tq_mul_prescaler % prescaler != 0)) {
            ++prescaler;
            continue;
        } else {
            uint32_t tq = num_tq_mul_prescaler / prescaler;
            if (tq * prescaler == num_tq_mul_prescaler) {
                has_found = true;
                break;
            } else if (tq < min_tq) {
                has_found = false;
                break;
            } else {
                ++prescaler;
            }
        }
    }

    return has_found ? prescaler : 0U;
}

static hpm_stat_t mcan_calc_bit_timing_from_baudrate(uint32_t src_clk_freq,
                                                     mcan_bit_timing_option_t option,
                                                     uint32_t baudrate,
                                                     uint16_t samplepoint_min,
                                                     uint16_t samplepoint_max,
                                                     mcan_bit_timing_param_t *timing_param)
{
    hpm_stat_t status = status_invalid_argument;
    do {
        if ((option > mcan_bit_timing_canfd_data) || (baudrate == 0U) ||
            (src_clk_freq / baudrate < MIN_TQ_MUL_PRESCALE) || (timing_param == NULL)) {
            break;
        }

        const mcan_bit_timing_table_t *tbl = &k_mcan_bit_timing_tbl[(uint8_t) option];

        /* According to the CAN specification 2.0,
         * the Tq must be in range specified in the above CAN bit-timing table
         */
        if (src_clk_freq / baudrate < tbl->tq_min) {
            break;
        }

        uint32_t num_tq_mul_prescaler = src_clk_freq / baudrate;
        uint32_t start_prescaler = 1U;
        uint32_t num_seg1, num_seg2;
        bool has_found = false;

        /* Find out the minimum prescaler */
        uint32_t current_prescaler;
        while (!has_found) {
            current_prescaler =
                mcan_calculate_closest_prescaler(num_tq_mul_prescaler, start_prescaler, tbl->tq_max, tbl->tq_min);
            if ((current_prescaler < start_prescaler) || (current_prescaler > NUM_PRESCALE_MAX)) {
                break;
            }
            uint32_t num_tq = num_tq_mul_prescaler / current_prescaler;

            num_seg2 = (num_tq - tbl->min_diff_seg1_minus_seg2) / 2U;
            num_seg1 = num_tq - num_seg2;
            while (num_seg2 > tbl->seg2_max) {
                num_seg2--;
                num_seg1++;
            }

            /* Recommended sample point is 75% - 87.5% */
            while ((num_seg1 * 1000U) / num_tq < samplepoint_min) {
                ++num_seg1;
                --num_seg2;
            }

            if ((num_seg1 * 1000U) / num_tq > samplepoint_max) {
                break;
            }

            if ((num_seg2 >= tbl->seg2_min) && (num_seg1 <= tbl->seg1_max)) {
                has_found = true;
            } else {
                start_prescaler = current_prescaler + 1U;
            }
        }

        if (has_found) {
            uint32_t num_sjw = MIN(tbl->sjw_max, num_seg2);
            timing_param->num_seg1 = num_seg1 - NUM_TQ_SYNC_SEG; /* Should exclude the Sync_Reg */
            timing_param->num_seg2 = num_seg2;
            timing_param->num_sjw = num_sjw;
            timing_param->prescaler = current_prescaler;
            status = status_success;
        }
    } while (false);

    return status;
}

static hpm_stat_t mcan_set_bit_timing_from_baudrate(MCAN_Type *ptr,
                                                    mcan_bit_timing_option_t option,
                                                    uint32_t src_clk_freq,
                                                    uint32_t baudrate,
                                                    uint16_t samplepoint_min,
                                                    uint16_t samplepoint_max)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        if (ptr == NULL) {
            break;
        }

        mcan_bit_timing_param_t timing_param = { 0 };
        status = mcan_calc_bit_timing_from_baudrate(src_clk_freq,
                                                    option,
                                                    baudrate,
                                                    samplepoint_min,
                                                    samplepoint_max,
                                                    &timing_param);

        if (status == status_success) {
            if (option < mcan_bit_timing_canfd_data) {
                mcan_set_can_nominal_bit_timing(ptr, &timing_param);
            } else {
                mcan_set_can_data_bit_timing(ptr, &timing_param);
            }
            status = status_success;
        }

    } while (false);

    return status;
}

void mcan_get_default_ram_config(MCAN_Type *ptr, mcan_ram_config_t *simple_config, bool enable_canfd)
{
    (void) memset(simple_config, 0, sizeof(mcan_ram_config_t));
    uint32_t start_addr = mcan_get_ram_offset(ptr);

    if (!enable_canfd) {
        simple_config->enable_std_filter = true;
        simple_config->std_filter_elem_count = MCAN_FILTER_SIZE_CAN_DEFAULT;
        start_addr += MCAN_FILTER_ELEM_STD_ID_SIZE * MCAN_FILTER_SIZE_CAN_DEFAULT;

        simple_config->enable_ext_filter = true;
        simple_config->ext_filter_elem_count = MCAN_FILTER_SIZE_CAN_DEFAULT;
        start_addr += MCAN_FILTER_ELEM_EXT_ID_SIZE * MCAN_FILTER_SIZE_CAN_DEFAULT;

        simple_config->enable_txbuf = true;
        simple_config->txbuf_dedicated_txbuf_elem_count = MCAN_TXBUF_SIZE_CAN_DEFAULT / 2;
        simple_config->txbuf_fifo_or_queue_elem_count = MCAN_TXBUF_SIZE_CAN_DEFAULT / 2;
        simple_config->txfifo_or_txqueue_mode = MCAN_TXBUF_OPERATION_MODE_FIFO;
        simple_config->txbuf_data_field_size = MCAN_DATA_FIELD_SIZE_8BYTES;
        start_addr += MCAN_TXBUF_SIZE_CAN_DEFAULT * MCAN_TXRX_ELEM_SIZE_CAN_MAX;

        for (uint32_t i = 0; i < ARRAY_SIZE(simple_config->rxfifos); i++) {
            simple_config->rxfifos[i].enable = true;
            simple_config->rxfifos[i].elem_count = MCAN_RXFIFO_SIZE_CAN_DEFAULT;
            simple_config->rxfifos[i].operation_mode = MCAN_FIFO_OPERATION_MODE_BLOCKING;
            simple_config->rxfifos[i].watermark = 1U;
            simple_config->rxfifos[i].data_field_size = MCAN_DATA_FIELD_SIZE_8BYTES;
            start_addr += MCAN_RXFIFO_SIZE_CAN_DEFAULT * MCAN_TXRX_ELEM_SIZE_CAN_MAX;
        }
        simple_config->enable_rxbuf = true;
        simple_config->rxbuf_elem_count = MCAN_RXBUF_SIZE_CAN_DEFAULT;
        simple_config->rxbuf_data_field_size = MCAN_DATA_FIELD_SIZE_8BYTES;
        start_addr += MCAN_RXBUF_SIZE_CAN_DEFAULT * MCAN_TXRX_ELEM_SIZE_CAN_MAX;
    } else {
        simple_config->enable_std_filter = true;
        simple_config->std_filter_elem_count = MCAN_FILTER_SIZE_CANFD_DEFAULT;
        start_addr += MCAN_FILTER_ELEM_STD_ID_SIZE * MCAN_FILTER_SIZE_CANFD_DEFAULT;

        simple_config->enable_ext_filter = true;
        simple_config->ext_filter_elem_count = MCAN_FILTER_SIZE_CANFD_DEFAULT;
        start_addr += MCAN_FILTER_ELEM_EXT_ID_SIZE * MCAN_FILTER_SIZE_CANFD_DEFAULT;

        simple_config->enable_txbuf = true;
        simple_config->txbuf_dedicated_txbuf_elem_count = MCAN_TXBUF_SIZE_CANFD_DEFAULT / 2;
        simple_config->txbuf_fifo_or_queue_elem_count = MCAN_TXBUF_SIZE_CANFD_DEFAULT / 2;
        simple_config->txfifo_or_txqueue_mode = MCAN_TXBUF_OPERATION_MODE_FIFO;
        simple_config->txbuf_data_field_size = MCAN_DATA_FIELD_SIZE_64BYTES;
        start_addr += MCAN_TXBUF_SIZE_CANFD_DEFAULT * MCAN_TXRX_ELEM_SIZE_CANFD_MAX;

        for (uint32_t i = 0; i < ARRAY_SIZE(simple_config->rxfifos); i++) {
            simple_config->rxfifos[i].enable = true;
            simple_config->rxfifos[i].elem_count = MCAN_RXFIFO_SIZE_CANFD_DEFAULT;
            simple_config->rxfifos[i].operation_mode = MCAN_FIFO_OPERATION_MODE_BLOCKING;
            simple_config->rxfifos[i].watermark = 1U;
            simple_config->rxfifos[i].data_field_size = MCAN_DATA_FIELD_SIZE_64BYTES;
            start_addr += MCAN_RXFIFO_SIZE_CANFD_DEFAULT * MCAN_TXRX_ELEM_SIZE_CANFD_MAX;
        }
        simple_config->enable_rxbuf = true;
        simple_config->rxbuf_elem_count = MCAN_RXBUF_SIZE_CANFD_DEFAULT;
        simple_config->rxbuf_data_field_size = MCAN_DATA_FIELD_SIZE_64BYTES;
        start_addr += MCAN_RXBUF_SIZE_CANFD_DEFAULT * MCAN_TXRX_ELEM_SIZE_CANFD_MAX;
    }
    simple_config->enable_tx_evt_fifo = true;
    uint32_t tx_fifo_elem_count =
        simple_config->txbuf_dedicated_txbuf_elem_count + simple_config->txbuf_fifo_or_queue_elem_count;
    simple_config->tx_evt_fifo_elem_count = tx_fifo_elem_count;
    simple_config->tx_evt_fifo_watermark = 1U;

    start_addr += MCAN_TXEVT_ELEM_SIZE * tx_fifo_elem_count;

    assert((start_addr - mcan_get_ram_offset(ptr)) <= mcan_get_ram_size(ptr));
}

void mcan_get_default_ram_flexible_config(MCAN_Type *ptr, mcan_ram_flexible_config_t *ram_config, bool enable_canfd)
{
    (void) memset(ram_config, 0, sizeof(mcan_ram_config_t));
    uint32_t start_addr = mcan_get_ram_offset(ptr);

    if (!enable_canfd) {
        ram_config->enable_std_filter = true;
        ram_config->std_filter_config.list_start_addr = start_addr;
        ram_config->std_filter_config.list_size = MCAN_FILTER_SIZE_CAN_DEFAULT;
        start_addr += MCAN_FILTER_ELEM_STD_ID_SIZE * MCAN_FILTER_SIZE_CAN_DEFAULT;

        ram_config->enable_ext_filter = true;
        ram_config->ext_filter_config.list_start_addr = start_addr;
        ram_config->ext_filter_config.list_size = MCAN_FILTER_SIZE_CAN_DEFAULT;
        start_addr += MCAN_FILTER_ELEM_EXT_ID_SIZE * MCAN_FILTER_SIZE_CAN_DEFAULT;

        ram_config->enable_txbuf = true;
        ram_config->txbuf_config.start_addr = start_addr;
        ram_config->txbuf_config.dedicated_tx_buf_size = MCAN_TXBUF_SIZE_CAN_DEFAULT / 2;
        ram_config->txbuf_config.fifo_queue_size = MCAN_TXBUF_SIZE_CAN_DEFAULT / 2;
        ram_config->txbuf_config.tx_fifo_queue_mode = MCAN_TXBUF_OPERATION_MODE_FIFO;
        ram_config->txbuf_elem_config.data_field_size = MCAN_DATA_FIELD_SIZE_8BYTES;
        start_addr += MCAN_TXBUF_SIZE_CAN_DEFAULT * MCAN_TXRX_ELEM_SIZE_CAN_MAX;

        ram_config->enable_rxfifo0 = true;
        ram_config->rxfifo0_config.start_addr = start_addr;
        ram_config->rxfifo0_config.fifo_size = MCAN_RXFIFO_SIZE_CAN_DEFAULT;
        ram_config->rxfifo0_config.operation_mode = MCAN_FIFO_OPERATION_MODE_BLOCKING;
        ram_config->rxfifo0_config.watermark = 1U;
        start_addr += MCAN_RXFIFO_SIZE_CAN_DEFAULT * MCAN_TXRX_ELEM_SIZE_CAN_MAX;

        ram_config->enable_rxfifo1 = true;
        ram_config->rxfifo1_config.start_addr = start_addr;
        ram_config->rxfifo1_config.fifo_size = MCAN_RXFIFO_SIZE_CAN_DEFAULT;
        ram_config->rxfifo1_config.operation_mode = MCAN_FIFO_OPERATION_MODE_BLOCKING;
        ram_config->rxfifo1_config.watermark = 1U;
        start_addr += MCAN_RXFIFO_SIZE_CAN_DEFAULT * MCAN_TXRX_ELEM_SIZE_CAN_MAX;

        ram_config->enable_rxbuf = true;
        ram_config->rxbuf_config.start_addr = start_addr;
        start_addr += MCAN_RXBUF_SIZE_CAN_DEFAULT * MCAN_TXRX_ELEM_SIZE_CAN_MAX;
    } else {
        ram_config->enable_std_filter = true;
        ram_config->std_filter_config.list_start_addr = start_addr;
        ram_config->std_filter_config.list_size = MCAN_FILTER_SIZE_CANFD_DEFAULT;
        start_addr += MCAN_FILTER_ELEM_STD_ID_SIZE * MCAN_FILTER_SIZE_CANFD_DEFAULT;

        ram_config->enable_ext_filter = true;
        ram_config->ext_filter_config.list_start_addr = start_addr;
        ram_config->ext_filter_config.list_size = MCAN_FILTER_SIZE_CANFD_DEFAULT;
        start_addr += MCAN_FILTER_ELEM_EXT_ID_SIZE * MCAN_FILTER_SIZE_CANFD_DEFAULT;

        ram_config->enable_txbuf = true;
        ram_config->txbuf_config.start_addr = start_addr;
        ram_config->txbuf_config.dedicated_tx_buf_size = MCAN_TXBUF_SIZE_CANFD_DEFAULT / 2;
        ram_config->txbuf_config.fifo_queue_size = MCAN_TXBUF_SIZE_CANFD_DEFAULT / 2;
        ram_config->txbuf_config.tx_fifo_queue_mode = MCAN_TXBUF_OPERATION_MODE_FIFO;
        ram_config->txbuf_elem_config.data_field_size = MCAN_DATA_FIELD_SIZE_64BYTES;
        start_addr += MCAN_TXBUF_SIZE_CAN_DEFAULT * MCAN_TXRX_ELEM_SIZE_CAN_MAX;

        ram_config->enable_rxfifo0 = true;
        ram_config->rxfifo0_config.start_addr = start_addr;
        ram_config->rxfifo0_config.fifo_size = MCAN_RXFIFO_SIZE_CANFD_DEFAULT;
        ram_config->rxfifo0_config.operation_mode = MCAN_FIFO_OPERATION_MODE_BLOCKING;
        ram_config->rxfifo0_config.watermark = 1U;
        start_addr += MCAN_RXFIFO_SIZE_CANFD_DEFAULT * MCAN_TXRX_ELEM_SIZE_CANFD_MAX;

        ram_config->enable_rxfifo1 = true;
        ram_config->rxfifo1_config.start_addr = start_addr;
        ram_config->rxfifo1_config.fifo_size = MCAN_RXFIFO_SIZE_CANFD_DEFAULT;
        ram_config->rxfifo1_config.operation_mode = MCAN_FIFO_OPERATION_MODE_BLOCKING;
        ram_config->rxfifo1_config.watermark = 1U;
        start_addr += MCAN_RXFIFO_SIZE_CANFD_DEFAULT * MCAN_TXRX_ELEM_SIZE_CANFD_MAX;

        ram_config->enable_rxbuf = true;
        ram_config->rxbuf_config.start_addr = start_addr;
        start_addr += MCAN_RXBUF_SIZE_CANFD_DEFAULT * MCAN_TXRX_ELEM_SIZE_CANFD_MAX;
    }
    ram_config->enable_tx_evt_fifo = true;
    ram_config->tx_evt_fifo_config.start_addr = start_addr;
    uint32_t tx_fifo_size = ram_config->txbuf_config.dedicated_tx_buf_size + ram_config->txbuf_config.fifo_queue_size;
    ram_config->tx_evt_fifo_config.fifo_size = tx_fifo_size;
    ram_config->tx_evt_fifo_config.fifo_watermark = 1U;

    start_addr += MCAN_TXEVT_ELEM_SIZE * tx_fifo_size;

    /* Ensure the requested MCAN RAM size is less than or equal to the total MCAN RAM size */
    assert((start_addr - mcan_get_ram_offset(ptr)) <= mcan_get_ram_size(ptr));
}

void mcan_get_default_config(MCAN_Type *ptr, mcan_config_t *config)
{
    (void) memset(config, 0, sizeof(mcan_config_t));
    config->baudrate = MCAN_CAN_BAUDRATE_DEFAULT;
    config->baudrate_fd = MCAN_CANFD_BAUDRATE_DEFAULT;
    config->can20_samplepoint_max = CAN_SAMPLEPOINT_MAX;
    config->can20_samplepoint_min = CAN_SAMPLEPOINT_MIN;
    config->canfd_samplepoint_max = CAN_SAMPLEPOINT_MAX;
    config->canfd_samplepoint_min = CAN_SAMPLEPOINT_MIN;

    config->mode = mcan_mode_normal;
    config->enable_canfd = false;

    /* Default Filter settings */
    mcan_all_filters_config_t *filters_config = &config->all_filters_config;
    filters_config->global_filter_config.reject_remote_ext_frame = false;
    filters_config->global_filter_config.reject_remote_std_frame = false;
    filters_config->global_filter_config.accept_non_matching_std_frame_option =
        MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;
    filters_config->global_filter_config.accept_non_matching_ext_frame_option =
        MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;
    filters_config->ext_id_mask = 0x1FFFFFFFUL;
    filters_config->std_id_filter_list.filter_elem_list = &k_default_std_id_filter;
    filters_config->std_id_filter_list.mcan_filter_elem_count = 1;
    filters_config->ext_id_filter_list.filter_elem_list = &k_default_ext_id_filter;
    filters_config->ext_id_filter_list.mcan_filter_elem_count = 1;

    /* Default MCAN RAM Configuration */
    mcan_ram_config_t *ram_config = &config->ram_config;
    mcan_get_default_ram_config(ptr, ram_config, false);

    /* Default Internal Timestamp Configuration */
    mcan_internal_timestamp_config_t *ts_config = &config->timestamp_cfg;
    ts_config->counter_prescaler = 1U;
    ts_config->timestamp_selection = MCAN_TIMESTAMP_SEL_VALUE_ALWAYS_ZERO;

    /* Default TSU configuration */
    mcan_tsu_config_t *tsu_config = &config->tsu_config;
    tsu_config->prescaler = 1U;
    tsu_config->ext_timebase_src = MCAN_TSU_EXT_TIMEBASE_SRC_PTP;
    tsu_config->use_ext_timebase = false;
    tsu_config->capture_on_sof = false;
    tsu_config->enable_tsu = false;
}

static void mcan_config_rxfifo(MCAN_Type *ptr, uint32_t index, uint32_t reg_val)
{
    if (index == 0U) {
        ptr->RXF0C = reg_val;
    } else {
        ptr->RXF1C = reg_val;
    }
}

hpm_stat_t mcan_config_ram(MCAN_Type *ptr, mcan_ram_config_t *config)
{
    hpm_stat_t status = status_invalid_argument;
    do {
        uint32_t elem_bytes;
        uint32_t elem_count;
        uint32_t start_addr = mcan_get_ram_offset(ptr);
        if (config->enable_std_filter) {
            mcan_filter_config_t filter_config = { .reg_val = 0 };
            filter_config.list_size = config->std_filter_elem_count;
            filter_config.list_start_addr = start_addr;
            ptr->SIDFC = filter_config.reg_val;
            start_addr += MCAN_FILTER_ELEM_STD_ID_SIZE * (uint32_t) config->std_filter_elem_count;
        } else {
            ptr->SIDFC = MCAN_RAM_ADDR_INVALID;
        }

        if (config->enable_ext_filter) {
            mcan_filter_config_t filter_config = { .reg_val = 0 };
            filter_config.list_size = config->ext_filter_elem_count;
            filter_config.list_start_addr = start_addr;
            ptr->XIDFC = filter_config.reg_val;
            start_addr += MCAN_FILTER_ELEM_EXT_ID_SIZE * (uint32_t) config->std_filter_elem_count;
        } else {
            ptr->XIDFC = MCAN_RAM_ADDR_INVALID;
        }

        mcan_rx_fifo_or_buf_elem_config_t rx_fifo_buf_elem_config = { .reg_val = 0U };

        for (uint32_t i = 0; i < ARRAY_SIZE(config->rxfifos); i++) {
            if (config->rxfifos[i].enable) {
                elem_bytes =
                    mcan_get_data_field_size(config->rxfifos[i].data_field_size) + MCAN_MESSAGE_HEADER_SIZE_IN_BYTES;
                elem_count = config->rxfifos[i].elem_count;
                mcan_rxfifo_config_t rxfifo_config = { .reg_val = 0 };
                rxfifo_config.start_addr = start_addr;
                rxfifo_config.watermark = 1U;
                rxfifo_config.operation_mode = config->rxfifos[i].operation_mode;
                rxfifo_config.fifo_size = elem_count;
                mcan_config_rxfifo(ptr, i, rxfifo_config.reg_val);

                if (i == 0) {
                    rx_fifo_buf_elem_config.fifo0_data_field_size = config->rxfifos[i].data_field_size;
                } else {
                    rx_fifo_buf_elem_config.fifo1_data_field_size = config->rxfifos[i].data_field_size;
                }

                start_addr += elem_bytes * elem_count;
            } else {
                mcan_config_rxfifo(ptr, i, MCAN_RAM_ADDR_INVALID);
                if (i == 0) {
                    rx_fifo_buf_elem_config.fifo0_data_field_size = 0;
                } else {
                    rx_fifo_buf_elem_config.fifo1_data_field_size = 0;
                }
            }
        }

        if (config->enable_rxbuf) {
            elem_bytes = mcan_get_data_field_size(config->rxbuf_data_field_size) + MCAN_MESSAGE_HEADER_SIZE_IN_BYTES;
            elem_count = config->rxbuf_elem_count;
            ptr->RXBC = start_addr;
            rx_fifo_buf_elem_config.buf_data_field_size = config->rxbuf_data_field_size;

            start_addr += elem_bytes * elem_count;;
        } else {
            rx_fifo_buf_elem_config.buf_data_field_size = 0;
            ptr->RXBC = MCAN_RAM_ADDR_INVALID;
        }
        ptr->RXESC = rx_fifo_buf_elem_config.reg_val;

        mcan_txbuf_config_t txbuf_config = { .reg_val = 0 };
        if (config->enable_txbuf) {
            txbuf_config.start_addr = start_addr;
            txbuf_config.fifo_queue_size = config->txbuf_fifo_or_queue_elem_count;
            txbuf_config.dedicated_tx_buf_size = config->txbuf_dedicated_txbuf_elem_count;
            txbuf_config.tx_fifo_queue_mode = config->txfifo_or_txqueue_mode;

            elem_count = config->txbuf_fifo_or_queue_elem_count + config->txbuf_dedicated_txbuf_elem_count;
            elem_bytes = mcan_get_data_field_size(config->txbuf_data_field_size) + MCAN_MESSAGE_HEADER_SIZE_IN_BYTES;

            start_addr += elem_count * elem_bytes;
            ptr->TXESC = (uint32_t) config->txbuf_data_field_size;
        } else {
            ptr->TXESC = MCAN_RAM_ADDR_INVALID;
        }

        ptr->TXBC = txbuf_config.reg_val;

        mcan_tx_evt_fifo_config_t txevt_fifo_config = { .reg_val = 0 };
        if (config->enable_tx_evt_fifo) {
            elem_bytes = sizeof(mcan_tx_event_fifo_elem_t);
            elem_count = config->tx_evt_fifo_elem_count;
            txevt_fifo_config.start_addr = start_addr;
            txevt_fifo_config.fifo_size = elem_count;
            txevt_fifo_config.fifo_watermark = 1U;
            ptr->TXEFC = txevt_fifo_config.reg_val;

            start_addr += elem_bytes * elem_count;
        } else {
            ptr->TXEFC = MCAN_RAM_ADDR_INVALID;
        }

        /* Check whether the requested RAM space exceeds the valid RAM range */
        uint32_t requested_ram_size = start_addr - mcan_get_ram_offset(ptr);
        if (requested_ram_size > mcan_get_ram_size(ptr)) {
            status = status_mcan_ram_out_of_range;
            break;
        }

        status = status_success;

    } while (false);

    return status;
}

hpm_stat_t mcan_config_ram_with_flexible_config(MCAN_Type *ptr, mcan_ram_flexible_config_t *config)
{
    hpm_stat_t status = status_invalid_argument;
    do {
        if (config->enable_std_filter) {
            ptr->SIDFC = config->std_filter_config.reg_val;
        } else {
            ptr->SIDFC = MCAN_RAM_ADDR_INVALID;
        }

        if (config->enable_ext_filter) {
            ptr->XIDFC = config->ext_filter_config.reg_val;
        } else {
            ptr->XIDFC = MCAN_RAM_ADDR_INVALID;
        }

        if (config->enable_rxfifo0) {
            ptr->RXF0C = config->rxfifo0_config.reg_val;
        } else {
            ptr->RXF0C = MCAN_RAM_ADDR_INVALID;
        }

        if (config->enable_rxfifo1) {
            ptr->RXF1C = config->rxfifo1_config.reg_val;
        } else {
            ptr->RXF1C = MCAN_RAM_ADDR_INVALID;
        }

        if (config->enable_rxbuf) {
            ptr->RXBC = config->rxbuf_config.start_addr;
        } else {
            ptr->RXBC = MCAN_RAM_ADDR_INVALID;
        }

        ptr->RXESC = config->rx_elem_config.reg_val;
        if (config->enable_txbuf) {
            ptr->TXESC = config->txbuf_elem_config.data_field_size;
        } else {
            ptr->TXESC = MCAN_RAM_ADDR_INVALID;
        }

        ptr->TXBC = config->txbuf_config.reg_val;

        if (config->enable_tx_evt_fifo) {
            ptr->TXEFC = config->tx_evt_fifo_config.reg_val;
        } else {
            ptr->TXEFC = MCAN_RAM_ADDR_INVALID;
        }

        status = status_success;

    } while (false);

    return status;
}

hpm_stat_t mcan_config_all_filters(MCAN_Type *ptr, mcan_all_filters_config_t *config)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        if ((ptr == NULL) || (config == NULL)) {
            break;
        }

        ptr->XIDAM = config->ext_id_mask;

        ptr->GFC = MCAN_GFC_RRFE_SET(config->global_filter_config.reject_remote_ext_frame) |
                   MCAN_GFC_RRFS_SET(config->global_filter_config.reject_remote_std_frame) |
                   MCAN_GFC_ANFE_SET(config->global_filter_config.accept_non_matching_ext_frame_option) |
                   MCAN_GFC_ANFS_SET(config->global_filter_config.accept_non_matching_std_frame_option);

        uint32_t elem_count = 0;
        const mcan_filter_elem_t *elem = NULL;
        if (config->ext_id_filter_list.mcan_filter_elem_count > 0) {
            elem_count = config->ext_id_filter_list.mcan_filter_elem_count;
            elem = config->ext_id_filter_list.filter_elem_list;
            for (uint32_t i = 0; i < elem_count; i++) {
                if (elem->can_id_type != MCAN_CAN_ID_TYPE_EXTENDED) {
                    status = status_invalid_argument;
                    break;
                }

                status = mcan_set_filter_element(ptr, elem, i);
                if (status != status_success) {
                    break;
                }
                ++elem;
            }
            if (status != status_success) {
                break;
            }
        }
        if (config->std_id_filter_list.mcan_filter_elem_count > 0) {
            elem_count = config->std_id_filter_list.mcan_filter_elem_count;
            elem = config->std_id_filter_list.filter_elem_list;
            for (uint32_t i = 0; i < elem_count; i++) {
                if (elem->can_id_type != MCAN_CAN_ID_TYPE_STANDARD) {
                    status = status_invalid_argument;
                    break;
                }
                status = mcan_set_filter_element(ptr, elem, i);
                if (status != status_success) {
                    break;
                }
                ++elem;
            }
            if (status != status_success) {
                break;
            }
        }
        status = status_success;

    } while (false);

    return status;
}

static hpm_stat_t mcan_set_tsu(MCAN_Type *ptr, mcan_tsu_config_t *config)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        uint32_t tscfg = 0;

        if ((config->prescaler < 1U) || (config->prescaler > 256U) ||
            (config->ext_timebase_src > MCAN_TSU_EXT_TIMEBASE_SRC_MAX)) {
            break;
        }

        if (config->enable_tsu) {
            tscfg |= MCAN_TSCFG_TSUE_MASK;
        }
        if (config->capture_on_sof) {
            tscfg |= MCAN_TSCFG_SCP_MASK;
        }
        if (config->use_ext_timebase) {
            tscfg |= MCAN_TSCFG_TBCS_MASK;
            mcan_set_tsu_ext_timebase_src(ptr, config->ext_timebase_src);
        }
        if (config->enable_64bit_timestamp) {
            tscfg |= MCAN_TSCFG_EN64_MASK;
        }

        tscfg |= MCAN_TSCFG_TBPRE_SET(config->prescaler - 1U);

        ptr->TSCFG = tscfg;

        status = status_success;
    } while (false);

    return status;
}

static hpm_stat_t mcan_set_internal_timestamp(MCAN_Type *ptr, mcan_internal_timestamp_config_t *config)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        if ((config->counter_prescaler < 1U) || (config->counter_prescaler > 16) ||
            (config->timestamp_selection > MCAN_TIMESTAMP_SEL_MAX)) {
            break;
        }

        ptr->TSCC = MCAN_TSCC_TCP_SET(config->counter_prescaler - 1U) | MCAN_TSCC_TSS_SET(config->timestamp_selection);

        status = status_success;
    } while (false);

    return status;
}

hpm_stat_t mcan_init(MCAN_Type *ptr, mcan_config_t *config, uint32_t src_clk_freq)
{
    hpm_stat_t status = status_invalid_argument;
    do {
        if ((ptr == NULL) || (config == NULL)) {
            break;
        }

        ptr->CCCR |= MCAN_CCCR_INIT_MASK;
        while ((ptr->CCCR & MCAN_CCCR_INIT_MASK) == 0) {

        }
        ptr->CCCR |= MCAN_CCCR_CCE_MASK;

        if (!config->use_lowlevel_timing_setting) {
            if (config->enable_canfd) {
                status = mcan_set_bit_timing_from_baudrate(ptr,
                                                           mcan_bit_timing_canfd_nominal,
                                                           src_clk_freq,
                                                           config->baudrate,
                                                           config->can20_samplepoint_min,
                                                           config->can20_samplepoint_max);
                HPM_BREAK_IF(status != status_success);
                status = mcan_set_bit_timing_from_baudrate(ptr,
                                                           mcan_bit_timing_canfd_data,
                                                           src_clk_freq,
                                                           config->baudrate_fd,
                                                           config->canfd_samplepoint_min,
                                                           config->canfd_samplepoint_max);
            } else {
                status = mcan_set_bit_timing_from_baudrate(ptr,
                                                           mcan_bit_timing_can2_0,
                                                           src_clk_freq,
                                                           config->baudrate,
                                                           config->can20_samplepoint_min,
                                                           config->can20_samplepoint_max);
            }
            HPM_BREAK_IF(status != status_success);
        } else {
            mcan_set_can_nominal_bit_timing(ptr, &config->can_timing);
            if (config->enable_canfd) {
                mcan_set_can_data_bit_timing(ptr, &config->canfd_timing);
            }
        }

        switch (config->mode) {
        default:
        case mcan_mode_normal:
            ptr->CCCR &= ~(MCAN_CCCR_MON_MASK | MCAN_CCCR_TEST_MASK);
            break;
        case mcan_mode_loopback_internal:
            ptr->CCCR |= MCAN_CCCR_MON_MASK | MCAN_CCCR_TEST_MASK;
            ptr->TEST |= MCAN_TEST_LBCK_MASK;
            break;
        case mcan_mode_loopback_external:
            ptr->CCCR |= MCAN_CCCR_TEST_MASK;
            ptr->TEST |= MCAN_TEST_LBCK_MASK;
            break;
        case mcan_mode_listen_only:
            ptr->CCCR |= MCAN_CCCR_MON_MASK;
            break;
        }

        if (config->enable_canfd) {
            ptr->CCCR |= MCAN_CCCR_FDOE_MASK | MCAN_CCCR_BRSE_MASK;
        } else {
            ptr->CCCR &= ~(MCAN_CCCR_FDOE_MASK | MCAN_CCCR_BRSE_MASK);
        }
        if (config->enable_non_iso_mode) {
            ptr->CCCR |= MCAN_CCCR_NISO_MASK;
        } else {
            ptr->CCCR &= ~MCAN_CCCR_NISO_MASK;
        }

        if (config->enable_transmit_pause) {
            ptr->CCCR |= MCAN_CCCR_TXP_MASK;
        } else {
            ptr->CCCR &= ~MCAN_CCCR_TXP_MASK;
        }

        if (config->disable_protocol_exception_handling) {
            ptr->CCCR |= MCAN_CCCR_PXHD_MASK;
        } else {
            ptr->CCCR &= ~MCAN_CCCR_PXHD_MASK;
        }

        if (config->enable_wide_message_marker) {
            ptr->CCCR |= MCAN_CCCR_WMM_MASK;
        } else {
            ptr->CCCR &= ~MCAN_CCCR_WMM_MASK;
        }

        if (config->enable_edge_filtering) {
            ptr->CCCR |= MCAN_CCCR_EFBI_MASK;
        } else {
            ptr->CCCR &= ~MCAN_CCCR_EFBI_MASK;
        }

        /* Configure Transmitter Delay Compensation */
        if (config->enable_tdc) {
            ptr->DBTP |= MCAN_DBTP_TDC_MASK;
            ptr->TDCR &= ~MCAN_TDCR_TDCO_MASK;
            uint32_t data_seg1 = MCAN_DBTP_DTSEG1_GET(ptr->DBTP);
            uint32_t prescaler = MCAN_DBTP_DSJW_GET(ptr->DBTP);

            uint32_t calc_val = (data_seg1 + 2U) * (prescaler + 1U);
            if (calc_val < MCAN_MAX_TDC_OFFSET) {
                ptr->TDCR |= MCAN_TDCR_TDCO_SET(calc_val);
            } else {
                ptr->TDCR |= MCAN_TDCR_TDCO_SET(MCAN_MAX_TDC_OFFSET);
            }
        } else {
            ptr->DBTP &= ~MCAN_DBTP_TDC_MASK;
        }

        /* Configure TSU */
        if (config->use_timestamping_unit) {
            ptr->CCCR |= MCAN_CCCR_UTSU_MASK;
            status = mcan_set_tsu(ptr, &config->tsu_config);
            HPM_BREAK_IF(status != status_success);
        } else {
            ptr->CCCR &= ~MCAN_CCCR_UTSU_MASK;
        }

        /* Configure Internal Timestamp */
        status = mcan_set_internal_timestamp(ptr, &config->timestamp_cfg);
        HPM_BREAK_IF(status != status_success);

        /* Initialize CAN RAM */
        uint32_t can_ram_size = mcan_get_ram_size(ptr);
        uint32_t *ram_base = (uint32_t *) (mcan_get_ram_base(ptr) + mcan_get_ram_offset(ptr));
        for (uint32_t i = 0U; i < can_ram_size / sizeof(uint32_t); i++) {
            ram_base[i] = 0UL;
        }
        status = mcan_config_ram(ptr, &config->ram_config);
        HPM_BREAK_IF(status != status_success);

        /* Configure Filters */
        status = mcan_config_all_filters(ptr, &config->all_filters_config);
        HPM_BREAK_IF(status != status_success);

        /* Clear all Interrupt Flags */
        mcan_clear_interrupt_flags(ptr, ~0UL);

        ptr->CCCR &= ~MCAN_CCCR_INIT_MASK;
        while ((ptr->CCCR & MCAN_CCCR_INIT_MASK) != 0U) {
        }

        status = status_success;

    } while (false);

    return status;
}

hpm_stat_t mcan_set_filter_element(MCAN_Type *ptr, const mcan_filter_elem_t *filter_elem, uint32_t index)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        if ((ptr == NULL) || (filter_elem == NULL)) {
            break;
        }
        bool is_ext_id = (filter_elem->can_id_type == MCAN_CAN_ID_TYPE_EXTENDED);

        uint32_t ram_offset;
        uint32_t filter_elem_size;
        uint32_t size_max;
        if (is_ext_id) {
            ram_offset = MCAN_XIDFC_FLESA_GET(ptr->XIDFC) << MCAN_XIDFC_FLESA_SHIFT;
            filter_elem_size = MCAN_FILTER_ELEM_EXT_ID_SIZE;
            size_max = MCAN_XIDFC_LSE_GET(ptr->XIDFC);
        } else {
            ram_offset = MCAN_SIDFC_FLSSA_GET(ptr->SIDFC) << MCAN_SIDFC_FLSSA_SHIFT;
            filter_elem_size = MCAN_FILTER_ELEM_STD_ID_SIZE;
            size_max = MCAN_SIDFC_LSS_GET(ptr->SIDFC);
        }

        if (index >= size_max) {
            status = status_mcan_filter_index_out_of_range;
            break;
        }

        volatile uint32_t *config_start;
        config_start = (volatile uint32_t *) (mcan_get_ram_base(ptr) + ram_offset + filter_elem_size * index);

        uint32_t config_words[2] = { 0, 0 };
        if (is_ext_id) {
            /* EFEC + EFID1 */
            config_words[0] = ((uint32_t) (filter_elem->filter_config) << 29) | filter_elem->id1;

            /* EFT + ESYNC + EFFID2 */
            config_words[1] = filter_elem->id2;
            config_words[1] |= (filter_elem->sync_message != 0) ? (1UL << 29) : 0;
            config_words[1] |= ((uint32_t) filter_elem->filter_type) << 30;

            config_start[0] = config_words[0];
            config_start[1] = config_words[1];
        } else {
            config_words[0] = (filter_elem->id2 & 0x7FFUL) | ((filter_elem->id1 & 0x7FFU) << 16);
            config_words[0] |= (filter_elem->sync_message != 0) ? (1UL << 15) : 0;
            config_words[0] |= ((uint32_t) filter_elem->filter_config) << 27;
            config_words[0] |= ((uint32_t) filter_elem->filter_type) << 30;

            config_start[0] = config_words[0];
        }

        status = status_success;

    } while (false);

    return status;
}

static uint32_t mcan_get_rxfifo0_base(MCAN_Type *ptr)
{
    uint32_t rxfifo0_buf_offset = MCAN_RXF0C_F0SA_GET(ptr->RXF0C) << 2;
    uint32_t fifo_addr_base = mcan_get_ram_base(ptr) + rxfifo0_buf_offset;
    return fifo_addr_base;
}

static uint32_t mcan_get_rxfifo1_base(MCAN_Type *ptr)
{
    uint32_t rxfifo1_buf_offset = MCAN_RXF1C_F1SA_GET(ptr->RXF1C) << 2;
    uint32_t fifo_addr_base = mcan_get_ram_base(ptr) + rxfifo1_buf_offset;
    return fifo_addr_base;
}

static uint32_t mcan_get_rxbuf_elem_addr(MCAN_Type *ptr, uint32_t index)
{
    uint32_t elem_size;
    uint32_t elem_size_option = MCAN_RXESC_RBDS_GET(ptr->RXESC);
    if (elem_size_option < 5U) {
        elem_size = 8U + 4U * elem_size_option;
    } else {
        elem_size = 32U + (elem_size_option - 5U) * 16U;
    }
    elem_size += MCAN_MESSAGE_HEADER_SIZE_IN_BYTES;

    uint32_t rxbuf_offset = MCAN_RXBC_RBSA_GET(ptr->RXBC) << MCAN_RXBC_RBSA_SHIFT;

    uint32_t rxbuf_addr_base = mcan_get_ram_base(ptr) + rxbuf_offset;

    uint32_t elem_addr = rxbuf_addr_base + elem_size * index;

    return elem_addr;
}

static uint32_t mcan_get_txbuf_elem_addr(MCAN_Type *ptr, uint32_t index)
{
    uint32_t elem_size;
    uint32_t elem_size_option = MCAN_TXESC_TBDS_GET(ptr->TXESC);
    if (elem_size_option < 5U) {
        elem_size = 8U + 4U * elem_size_option;
    } else {
        elem_size = 32U + (elem_size_option - 5U) * 16U;
    }
    elem_size += MCAN_MESSAGE_HEADER_SIZE_IN_BYTES;

    uint32_t txbuf_offset = MCAN_TXBC_TBSA_GET(ptr->TXBC) << MCAN_TXBC_TBSA_SHIFT;

    uint32_t txbuf_addr_base = mcan_get_ram_base(ptr) + txbuf_offset;

    uint32_t elem_addr = txbuf_addr_base + elem_size * index;

    return elem_addr;
}

uint8_t mcan_get_message_size_from_dlc(uint8_t dlc)
{
    uint32_t msg_size;
    if (dlc <= 8U) {
        msg_size = dlc;
    } else if (dlc <= 12U) {
        msg_size = 8 + (dlc - 8) * 4;
    } else {
        msg_size = 32 + (dlc - 13) * 16U;
    }
    return msg_size;
}

uint8_t mcan_get_data_field_size(uint8_t data_field_size_option)
{
    uint8_t size_in_bytes = 0;

    switch (data_field_size_option) {
    case MCAN_DATA_FIELD_SIZE_8BYTES:
        size_in_bytes = 8U;
        break;
    case MCAN_DATA_FIELD_SIZE_12BYTES:
        size_in_bytes = 12U;
        break;
    case MCAN_DATA_FIELD_SIZE_16BYTES:
        size_in_bytes = 16U;
        break;
    case MCAN_DATA_FIELD_SIZE_20BYTES:
        size_in_bytes = 20U;
        break;
    case MCAN_DATA_FIELD_SIZE_24BYTES:
        size_in_bytes = 24U;
        break;
    case MCAN_DATA_FIELD_SIZE_32BYTES:
        size_in_bytes = 32U;
        break;
    case MCAN_DATA_FIELD_SIZE_48BYTES:
        size_in_bytes = 48U;
        break;
    case MCAN_DATA_FIELD_SIZE_64BYTES:
        size_in_bytes = 64U;
        break;
    default:
        /* Invalid option */
        break;
    }
    return size_in_bytes;
}

hpm_stat_t mcan_write_txbuf(MCAN_Type *ptr, uint32_t index, mcan_tx_frame_t *tx_frame)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        if ((ptr == NULL) || (tx_frame == NULL)) {
            break;
        }

        uint32_t txbuf_index_max = MCAN_TXBC_NDTB_GET(ptr->TXBC);
        if (index >= txbuf_index_max) {
            status = status_mcan_txbuf_index_out_of_range;
            break;
        }

        if (!mcan_is_transmit_request_pending(ptr, index)) {
            uint32_t *msg_hdr = (uint32_t *) mcan_get_txbuf_elem_addr(ptr, index);
            uint32_t *msg_data = msg_hdr + 2;
            uint8_t msg_size_words = (mcan_get_message_size_from_dlc(tx_frame->dlc) + 3U) / sizeof(uint32_t);
            uint32_t *tx_frame_u32 = (uint32_t *) tx_frame;
            msg_hdr[0] = tx_frame_u32[0];
            msg_hdr[1] = tx_frame_u32[1];

            for (uint32_t i = 0; i < msg_size_words; i++) {
                msg_data[i] = tx_frame->data_32[i];
            }

            status = status_success;
        } else {
            status = status_fail;
        }
    } while (false);

    return status;
}

hpm_stat_t mcan_write_txfifo(MCAN_Type *ptr, mcan_tx_frame_t *tx_frame)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        if ((ptr == NULL) || (tx_frame == NULL)) {
            break;
        }
        if (!mcan_is_txfifo_full(ptr)) {
            uint32_t put_index = mcan_get_txfifo_put_index(ptr);
            uint32_t *msg_hdr = (uint32_t *) mcan_get_txbuf_elem_addr(ptr, put_index);
            uint32_t *msg_data = msg_hdr + 2;
            uint8_t msg_size_words = (mcan_get_message_size_from_dlc(tx_frame->dlc) + 3U) / sizeof(uint32_t);
            uint32_t *tx_frame_u32 = (uint32_t *) tx_frame;
            msg_hdr[0] = tx_frame_u32[0];
            msg_hdr[1] = tx_frame_u32[1];

            for (uint32_t i = 0; i < msg_size_words; i++) {
                msg_data[i] = tx_frame->data_32[i];
            }
            status = status_success;
        } else {
            status = status_mcan_txfifo_full;
        }
    } while (false);

    return status;
}

hpm_stat_t mcan_read_rxbuf(MCAN_Type *ptr, uint32_t index, mcan_rx_message_t *rx_frame)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        if ((ptr == NULL) || (rx_frame == NULL)) {
            break;
        }

        if (!mcan_is_rxbuf_data_available(ptr, index)) {
            status = status_mcan_rxbuf_empty;
            break;
        }

        uint32_t *msg_hdr = (uint32_t *) mcan_get_rxbuf_elem_addr(ptr, index);
        uint32_t *msg_data = msg_hdr + 2;
        uint32_t *rx_frame_u32 = (uint32_t *) rx_frame;
        rx_frame_u32[0] = msg_hdr[0];
        rx_frame_u32[1] = msg_hdr[1];
        uint8_t msg_size_words = (mcan_get_message_size_from_dlc(rx_frame->dlc) + 3) / 4;
        for (uint32_t i = 0; i < msg_size_words; i++) {
            rx_frame->data_32[i] = msg_data[i];
        }
        status = status_success;

    } while (false);

    return status;
}

hpm_stat_t mcan_read_rxfifo(MCAN_Type *ptr, uint32_t fifo_index, mcan_rx_message_t *rx_frame)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        if ((ptr == NULL) || (rx_frame == NULL)) {
            break;
        }

        uint32_t base_addr;
        uint32_t elem_index;
        uint32_t elem_size;
        uint32_t elem_size_option;
        if (fifo_index == 0) {
            uint32_t rxf0s = ptr->RXF0S;
            if (MCAN_RXF0S_F0FL_GET(rxf0s) == 0) {
                status = status_mcan_rxfifo_empty;
                break;
            }
            base_addr = mcan_get_rxfifo0_base(ptr);
            elem_size_option = MCAN_RXESC_F0DS_GET(ptr->RXESC);
            elem_index = MCAN_RXF0S_F0GI_GET(rxf0s);
        } else {
            uint32_t rxf1s = ptr->RXF1S;
            if (MCAN_RXF1S_F1FL_GET(rxf1s) == 0) {
                status = status_mcan_rxfifo_empty;
                break;
            }
            base_addr = mcan_get_rxfifo1_base(ptr);
            elem_size_option = MCAN_RXESC_F1DS_GET(ptr->RXESC);
            elem_index = MCAN_RXF1S_F1GI_GET(rxf1s);
        }


        if (elem_size_option < 5U) {
            elem_size = 8U + 4U * elem_size_option;
        } else {
            elem_size = 32U + (elem_size_option - 5U) * 16U;
        }
        elem_size += MCAN_MESSAGE_HEADER_SIZE_IN_BYTES;

        uint32_t elem_addr = base_addr + elem_size * elem_index;
        uint32_t *msg_hdr = (uint32_t *) elem_addr;
        uint32_t *msg_data = msg_hdr + 2;
        uint32_t *rx_frame_u32 = (uint32_t *) rx_frame;
        rx_frame_u32[0] = msg_hdr[0];
        rx_frame_u32[1] = msg_hdr[1];
        uint8_t msg_size_words = (mcan_get_message_size_from_dlc(rx_frame->dlc) + 3) / 4;
        for (uint32_t i = 0; i < msg_size_words; i++) {
            rx_frame->data_32[i] = msg_data[i];
        }

        if (fifo_index == 0) {
            ptr->RXF0A = MCAN_RXF0S_F0GI_GET(ptr->RXF0S);
        } else {
            ptr->RXF1A = MCAN_RXF1S_F1GI_GET(ptr->RXF1S);
        }

        status = status_success;

    } while (false);

    return status;
}

hpm_stat_t mcan_read_tx_evt_fifo(MCAN_Type *ptr, mcan_tx_event_fifo_elem_t *tx_evt)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        if ((ptr == NULL) || (tx_evt == NULL)) {
            break;
        }

        uint32_t txefs = ptr->TXEFS;

        if (MCAN_TXEFS_EFFL_GET(txefs) == 0U) {
            status = status_mcan_tx_evt_fifo_empty;
            break;
        }

        uint32_t base_addr = mcan_get_ram_base(ptr) + (MCAN_TXEFC_EFSA_GET(ptr->TXEFC) << MCAN_TXEFC_EFSA_SHIFT);
        uint32_t elem_size = sizeof(mcan_tx_event_fifo_elem_t);
        uint32_t elem_index = MCAN_TXEFS_EFGI_GET(txefs);

        uint32_t elem_addr = base_addr + elem_size * elem_index;
        uint32_t *tx_evt_buf = (uint32_t *) elem_addr;

        tx_evt->words[0] = tx_evt_buf[0];
        tx_evt->words[1] = tx_evt_buf[1];

        ptr->TXEFA = MCAN_TXEFA_EFAI_SET(elem_index);

        status = status_success;

    } while (false);

    return status;
}

hpm_stat_t mcan_transmit_via_txbuf_nonblocking(MCAN_Type *ptr, uint32_t index, mcan_tx_frame_t *tx_frame)
{
    hpm_stat_t status = status_invalid_argument;
    do {
        if ((ptr == NULL) || (tx_frame == NULL)) {
            break;
        }

        status = mcan_write_txbuf(ptr, index, tx_frame);
        HPM_BREAK_IF(status != status_success);

        mcan_send_add_request(ptr, index);
        status = status_success;

    } while (false);
    return status;
}

hpm_stat_t mcan_transmit_blocking(MCAN_Type *ptr, mcan_tx_frame_t *tx_frame)
{
    hpm_stat_t status = status_invalid_argument;
    do {
        if ((ptr == NULL) || (tx_frame == NULL)) {
            break;
        }
        if (mcan_is_txfifo_full(ptr)) {
            status = status_mcan_txfifo_full;
            break;
        }

        status = mcan_write_txfifo(ptr, tx_frame);
        HPM_BREAK_IF(status != status_success);

        uint32_t put_index = mcan_get_txfifo_put_index(ptr);
        mcan_send_add_request(ptr, put_index);

        uint32_t retry_cnt = 0;
        while (!mcan_is_transmit_occurred(ptr, put_index)) {
            retry_cnt++;
            if (retry_cnt >= MCAN_TX_RETRY_COUNT_MAX) {
                break;
            }
        }
        if (retry_cnt >= MCAN_TX_RETRY_COUNT_MAX) {
            status = status_timeout;
        } else {
            status = status_success;
        }
    } while (false);
    return status;
}

hpm_stat_t mcan_receive_from_buf_blocking(MCAN_Type *ptr, uint32_t index, mcan_rx_message_t *rx_frame)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        uint32_t retry_cnt = 0;

        while (!mcan_is_rxbuf_data_available(ptr, index)) {
            retry_cnt++;
            if (retry_cnt >= MCAN_RX_RETRY_COUNT_MAX) {
                status = status_timeout;
                break;
            }
        }
        if (status == status_timeout) {
            break;
        }

        mcan_clear_rxbuf_data_available_flag(ptr, index);
        status = mcan_read_rxbuf(ptr, index, rx_frame);
    } while (false);

    return status;
}

hpm_stat_t mcan_receive_from_fifo_blocking(MCAN_Type *ptr, uint32_t fifo_index, mcan_rx_message_t *rx_frame)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        uint32_t retry_cnt = 0;
        uint32_t interrupt_flag = (fifo_index == 0U) ? MCAN_IR_RF0N_MASK : MCAN_IR_RF1N_MASK;

        while (!mcan_is_interrupt_flag_set(ptr, interrupt_flag)) {
            retry_cnt++;
            if (retry_cnt >= MCAN_RX_RETRY_COUNT_MAX) {
                status = status_timeout;
                break;
            }
        }
        if (status == status_timeout) {
            break;
        }

        mcan_clear_interrupt_flags(ptr, interrupt_flag);
        status = mcan_read_rxfifo(ptr, fifo_index, rx_frame);
    } while (false);

    return status;
}

void mcan_get_high_priority_message_status(MCAN_Type *ptr, mcan_high_priority_message_status_t *status)
{
    uint32_t hpms = ptr->HPMS;
    status->buffer_index = MCAN_HPMS_BIDX_GET(hpms);
    status->filter_index = MCAN_HPMS_FIDX_GET(hpms);
    status->filter_list_type = MCAN_HPMS_FLST_GET(hpms);
    status->message_storage_indicator = MCAN_HPMS_MSI_GET(hpms);
}

hpm_stat_t mcan_set_global_filter_config(MCAN_Type *ptr, mcan_global_filter_config_t *filter_config)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        if ((ptr == NULL) || (filter_config == NULL)) {
            break;
        }

        ptr->GFC = MCAN_GFC_ANFE_SET(filter_config->accept_non_matching_ext_frame_option) |
                   MCAN_GFC_ANFS_SET(filter_config->accept_non_matching_std_frame_option) |
                   MCAN_GFC_RRFS_SET(filter_config->reject_remote_std_frame) |
                   MCAN_GFC_RRFE_SET(filter_config->reject_remote_ext_frame);

        status = status_success;

    } while (false);

    return status;
}

hpm_stat_t mcan_config_transmitter_delay_compensation(MCAN_Type *ptr, mcan_tdc_config_t *config)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        if ((ptr == NULL) || (config == NULL)) {
            break;
        }

        ptr->TDCR = MCAN_TDCR_TDCO_SET(config->ssp_offset) | MCAN_TDCR_TDCF_SET(config->filter_window_length);
        status = status_success;

    } while (false);
    return status;
}

uint32_t mcan_read_32bit_tsu_timestamp(MCAN_Type *ptr, uint32_t index)
{
    uint32_t ts_val = 0U;
    if (index < ARRAY_SIZE(ptr->TS_SEL)) {
        ts_val = ptr->TS_SEL[index];
    }
    return ts_val;
}

uint64_t mcan_read_64bit_tsu_timestamp(MCAN_Type *ptr, uint32_t index)
{
    uint64_t ts_val = 0U;
    uint32_t real_index = index & 0x7U; /* Clear bit3 according to IP design */
    if (index < ARRAY_SIZE(ptr->TS_SEL)) {
        ts_val = ((uint64_t) (ptr->TS_SEL[2U * real_index + 1]) << 32U);
        ts_val |= ptr->TS_SEL[2U * real_index];
        /* Workaround: dummy read to clear the corresponding bits in TSS1 if the index is equal to/greater than 8 */
        if (index >= 8U) {
            (void) ptr->TS_SEL[index];
        }
    }

    return ts_val;
}

hpm_stat_t mcan_get_timestamp_from_tx_event(MCAN_Type *ptr,
                                            const mcan_tx_event_fifo_elem_t *tx_evt,
                                            mcan_timestamp_value_t *timestamp)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        HPM_BREAK_IF((ptr == NULL) || (tx_evt == NULL) || (timestamp == NULL));

        (void) memset(timestamp, 0, sizeof(mcan_timestamp_value_t));

        bool is_tsu_used = mcan_is_tsu_used(ptr);
        if (!is_tsu_used) {
            timestamp->is_16bit = true;
            timestamp->ts_16bit = tx_evt->tx_timestamp;
        } else if (tx_evt->tx_timestamp_captured != 0U) {
            bool is_64bit_ts = mcan_is_64bit_tsu_timestamp_used(ptr);
            uint32_t ts_index = tx_evt->tx_timestamp_pointer;
            if (!is_64bit_ts) {
                timestamp->is_32bit = true;
                timestamp->ts_32bit = mcan_read_32bit_tsu_timestamp(ptr, ts_index);
            } else {
                timestamp->is_64bit = true;
                timestamp->ts_64bit = mcan_read_64bit_tsu_timestamp(ptr, ts_index);
            }
            status = status_success;
        } else {
            status = status_mcan_timestamp_not_exist;
        }

    } while (false);

    return status;
}

hpm_stat_t mcan_get_timestamp_from_received_message(MCAN_Type *ptr,
                                                    const mcan_rx_message_t *rx_msg,
                                                    mcan_timestamp_value_t *timestamp)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        HPM_BREAK_IF((ptr == NULL) || (rx_msg == NULL) || (timestamp == NULL));

        (void) memset(timestamp, 0, sizeof(mcan_timestamp_value_t));

        bool is_tsu_used = mcan_is_tsu_used(ptr);
        if (!is_tsu_used) {
            timestamp->is_16bit = true;
            timestamp->ts_16bit = rx_msg->rx_timestamp;
        } else if (rx_msg->rx_timestamp_captured != 0U) {
            bool is_64bit_ts = mcan_is_64bit_tsu_timestamp_used(ptr);
            uint32_t ts_index = rx_msg->rx_timestamp_pointer;
            if (!is_64bit_ts) {
                timestamp->is_32bit = true;
                timestamp->ts_32bit = mcan_read_32bit_tsu_timestamp(ptr, ts_index);
            } else {
                timestamp->is_64bit = true;
                timestamp->ts_64bit = mcan_read_64bit_tsu_timestamp(ptr, ts_index);
            }
            status = status_success;
        } else {
            status = status_mcan_timestamp_not_exist;
        }
    } while (false);

    return status;
}
