/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_ffa_drv.h"
#include <assert.h>

#define FFA_ERROR_MASKS (FFA_STATUS_FIR_OV_MASK | FFA_STATUS_FFT_OV_MASK | FFA_STATUS_WR_ERR_MASK | FFA_STATUS_RD_NXT_ERR_MASK | FFA_STATUS_RD_ERR_MASK)

static bool is_point_num_valid(uint16_t num_point);
static uint32_t get_fft_misc_reg_fft_len(uint16_t num_point);
static hpm_stat_t get_fft_error_kind(uint32_t ffa_status);

static bool is_point_num_valid(uint16_t num_point)
{
    return ((num_point & (num_point - 1U)) == 0U) && (num_point >= 8U);
}

static uint32_t get_fft_misc_reg_fft_len(uint16_t num_point)
{
    uint32_t count = 0U;
    num_point /= 8;
    while (num_point > 0) {
        count++;
        num_point >>= 1U;
    }

    return (count - 1U);
}

void ffa_start_fft(FFA_Type *ptr, fft_xfer_t *fft_xfer)
{

    assert((ptr != NULL) && (fft_xfer != NULL) && is_point_num_valid(fft_xfer->num_points));

    ffa_disable(ptr);

    ffa_enable_interrupt(ptr, fft_xfer->interrupt_mask);

    ptr->OP_CTRL = FFA_OP_CTRL_EN_MASK;

    uint32_t op_cmd = FFA_OP_CMD_CMD_SET(FFA_OPCMD_FFT) | FFA_OP_CMD_IND_TYPE_SET(fft_xfer->src_data_type) |
        FFA_OP_CMD_OUTD_TYPE_SET(fft_xfer->dst_data_type);
    ptr->OP_CMD = op_cmd;

    uint32_t fft_len = get_fft_misc_reg_fft_len(fft_xfer->num_points);
    uint32_t fft_misc =
        FFA_OP_FFT_MISC_FFT_LEN_SET(fft_len) | FFA_OP_FFT_MISC_TMP_BLK_SET(1) | FFA_OP_FFT_MISC_IND_BLK_SET(0);
    if (fft_xfer->is_ifft) {
        fft_misc |= FFA_OP_FFT_MISC_IFFT_MASK;
    }
    ptr->OP_REG0 = fft_misc;

    ptr->OP_REG1 = 0;
    ptr->OP_REG2 = (uint32_t) fft_xfer->src;
    ptr->OP_REG4 = (uint32_t) fft_xfer->dst;

    ffa_enable(ptr);
}

void ffa_start_fir(FFA_Type *ptr, fir_xfer_t *fir_xfer)
{
    assert((ptr != NULL) && (fir_xfer != NULL));

    ffa_disable(ptr);

    ffa_enable_interrupt(ptr, fir_xfer->interrupt_mask);

    ptr->OP_CTRL = FFA_OP_CTRL_EN_MASK;

    uint32_t op_cmd = FFA_OP_CMD_CMD_SET(FFA_OPCMD_FIR) | FFA_OP_CMD_IND_TYPE_SET(fir_xfer->data_type) |
        FFA_OP_CMD_OUTD_TYPE_SET(fir_xfer->data_type) | FFA_OP_CMD_COEF_TYPE_SET(fir_xfer->data_type);
    ptr->OP_CMD = op_cmd;

    uint32_t fir_misc = FFA_OP_FIR_MISC_FIR_COEF_TAPS_SET(fir_xfer->coef_taps);
    ptr->OP_REG0 = fir_misc;

    uint32_t fir_misc1 = FFA_OP_FIR_MISC1_OUTD_MEM_BLK_SET(0) | FFA_OP_FIR_MISC1_COEF_MEM_BLK_SET(1) |
        FFA_OP_FIR_MISC1_IND_MEM_BLK_SET(2) | FFA_OP_FIR_MISC1_FIR_DATA_TAPS_SET(fir_xfer->input_taps);

    ptr->OP_REG1 = fir_misc1;
    ptr->OP_REG2 = 0xFFFFFFFFUL;
    ptr->OP_REG3 = (uint32_t) fir_xfer->src;
    ptr->OP_REG4 = (uint32_t) fir_xfer->coeff;
    ptr->OP_REG5 = (uint32_t) fir_xfer->dst;

    ffa_enable(ptr);
}

static hpm_stat_t get_fft_error_kind(uint32_t ffa_status)
{
    hpm_stat_t status;
    if (IS_HPM_BITMASK_SET(ffa_status, FFA_ERROR_MASKS)) {
        if (IS_HPM_BITMASK_SET(ffa_status, FFA_STATUS_FIR_OV_MASK)) {
            status = status_ffa_fir_overflow;
        } else if (IS_HPM_BITMASK_SET(ffa_status, FFA_STATUS_FFT_OV_MASK)) {
            status = status_ffa_fft_overflow;
        } else if (IS_HPM_BITMASK_SET(ffa_status, FFA_STATUS_WR_ERR_MASK)) {
            status = status_ffa_write_error;
        } else if (IS_HPM_BITMASK_SET(ffa_status, FFA_STATUS_RD_NXT_ERR_MASK)) {
            status = status_ffa_read_next_error;
        } else {
            status = status_ffa_read_error;
        }
    } else {
        status = status_success;
    }
    return status;
}

hpm_stat_t ffa_calculate_fft_blocking(FFA_Type *ptr, fft_xfer_t *fft_xfer)
{
    hpm_stat_t status = status_invalid_argument;
    do {
        HPM_BREAK_IF((ptr == NULL) || (fft_xfer == NULL) || !is_point_num_valid(fft_xfer->num_points));

        fft_xfer->interrupt_mask = 0;

        ffa_start_fft(ptr, fft_xfer);

        while (!IS_HPM_BITMASK_SET(ptr->STATUS, FFA_STATUS_OP_CMD_DONE_MASK)) {
        }

        uint32_t ffa_status = ptr->STATUS;
        status = get_fft_error_kind(ffa_status);
    } while (false);

    return status;
}

hpm_stat_t ffa_calculate_fir_blocking(FFA_Type *ptr, fir_xfer_t *fir_xfer)
{
    hpm_stat_t status = status_invalid_argument;
    do {
        HPM_BREAK_IF((ptr == NULL) || (fir_xfer == NULL));

        fir_xfer->interrupt_mask = 0;

        ffa_start_fir(ptr, fir_xfer);

        while (!IS_HPM_BITMASK_SET(ptr->STATUS, FFA_STATUS_OP_CMD_DONE_MASK)) {
        }

        uint32_t ffa_status = ptr->STATUS;
        status = get_fft_error_kind(ffa_status);
    } while (false);

    return status;
}
