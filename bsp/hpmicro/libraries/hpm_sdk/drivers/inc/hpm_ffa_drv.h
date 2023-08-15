/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_FFA_DRV_H
#define HPM_FFA_DRV_H

#include "hpm_common.h"
#include "hpm_ffa_regs.h"

/**
 * @brief FFA driver APIs
 * @defgroup ffa_interface FFA driver APIs
 * @ingroup ffa_interfaces
 * @{
 *
 */

/***********************************************************************************************************************
 *
 * Definitions
 *
 **********************************************************************************************************************/
/**
 * @brief Operation commands supported by FFA
 */
#define FFA_OPCMD_FIR (0U)      /* !< FIR operation command index */
#define FFA_OPCMD_FFT (2U)      /* !< FFT operation command index */

/**
 * @brief Data type supported by FFA
 */
#define FFA_DATA_TYPE_REAL_Q31      (0U)    /* !< FFA Data type:  Real Q31 */
#define FFA_DATA_TYPE_REAL_Q15      (1U)    /* !< FFA Data type: Real Q15 */
#define FFA_DATA_TYPE_COMPLEX_Q31   (2U)    /* !< FFA Data type: Complex Q31 */
#define FFA_DATA_TYPE_COMPLEX_Q15   (3U)    /* !< FFA Data type: Complex Q15 */

/**
 * @brief FFA Q31 data type definition
 */
typedef int32_t ffa_q31_t;

/**
 * @brief FFA Q15 data type definition
 */
typedef int16_t ffa_q15_t;

/**
 * @brief FFA complex Q31 data type definition
 */
typedef struct {
    ffa_q31_t real;
    ffa_q31_t image;
} ffa_complex_q31_t;

/**
 * @brief FFA complex Q15 data type definition
 */
typedef struct {
    ffa_q15_t real;
    ffa_q15_t image;
} ffa_complex_q15_t;

/**
 * @brief FFT transform context
 */
typedef struct {
    uint16_t is_ifft;           /* !< Is Inverse FFT transform */
    uint8_t src_data_type;      /* !< Source data type */
    uint8_t dst_data_type;      /* !< Destination date type */
    uint32_t num_points;        /* !< Number of points */
    const void *src;            /* !< Source data buffer */
    void *dst;                  /* !< Destination Data buffer */
    uint32_t interrupt_mask;    /* !< Interrupt mask */
} fft_xfer_t;

/**
 * @brief FIR transform context
 */
typedef struct {
    uint16_t data_type;         /* !< Data type */
    uint16_t coef_taps;         /* !< Coefficient taps */
    uint32_t input_taps;        /* !< Input data taps */
    const void *src;            /* !< Source data buffer */
    const void *coeff;          /* !< Coefficient data buffer */
    void *dst;                  /* !< Destination data buffer */
    uint32_t interrupt_mask;    /* !< Interrupt mask */
} fir_xfer_t;

/**
 * @brief FFA error codes
 */
enum {
    status_ffa_fir_overflow = MAKE_STATUS(status_group_ffa, 0),         /* !< FIR overflow */
    status_ffa_fft_overflow = MAKE_STATUS(status_group_ffa, 1),         /* !< FFR overflow */
    status_ffa_write_error = MAKE_STATUS(status_group_ffa, 2),          /* !< FFA write error */
    status_ffa_read_next_error = MAKE_STATUS(status_group_ffa, 3),      /* !< FFA read next data error */
    status_ffa_read_error = MAKE_STATUS(status_group_ffa, 4),           /*!< FFA read error */
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enable FFA module and start an specified FFA operation
 *
 * @param [in] ptr FFA base address
 */
static inline void ffa_enable(FFA_Type *ptr)
{
    ptr->CTRL = (ptr->CTRL & ~FFA_CTRL_SFTRST_MASK) | FFA_CTRL_EN_MASK;
}

/**
 * @brief Stop FFA module
 *
 * @param [in] ptr FFA base address
 */
static inline void ffa_disable(FFA_Type *ptr)
{
    ptr->CTRL = (ptr->CTRL & ~FFA_CTRL_EN_MASK) | FFA_CTRL_SFTRST_MASK;
}

/**
 * @brief Get FFA status
 *
 * @param [in] ptr FFA base address
 * @return FFA status register value
 */
static inline uint32_t ffa_get_status(FFA_Type *ptr)
{
    return ptr->STATUS;
}

/**
 * @brief Enable FFA Interrupt
 *
 * @param [in] ptr FFA base address
 * @param [in] mask FFA interrupt mask
 */
static inline void ffa_enable_interrupt(FFA_Type *ptr, uint32_t mask)
{
    ptr->INT_EN |= mask;
}

/**
 * @brief Disable FFA interrupt
 *
 * @param [in] ptr FFA base address
 * @param [in] mask FFA interrupt mask
 */
static inline void ffa_disable_interrupt(FFA_Type *ptr, uint32_t mask)
{
    ptr->INT_EN &= ~mask;
}

/**
 * @brief Start an FFT operation
 *
 * @param [in] ptr FFA base address
 * @param [in] fft_xfer FFT transform context
 */
void ffa_start_fft(FFA_Type *ptr, fft_xfer_t *fft_xfer);

/**
 * @brief Start an FIR operation
 *
 * @param [in] ptr FFA base address
 * @param [in] fir_xfer FIR transform context
 */
void ffa_start_fir(FFA_Type *ptr, fir_xfer_t *fir_xfer);

/**
 * @brief Perform FFT transformation in blocking mode
 *
 * @param [in] ptr FFA base address
 * @param [in, out] fft_xfer FFT transform context
 * @return FFT operation result
 */
hpm_stat_t ffa_calculate_fft_blocking(FFA_Type *ptr, fft_xfer_t *fft_xfer);

/**
 * @brief Perform FIR transform in blocking mode
 *
 * @param [in] ptr FFA base address
 * @param [in, out] fir_xfer FIR transform context
 * @return FIR operation result
 */
hpm_stat_t ffa_calculate_fir_blocking(FFA_Type *ptr, fir_xfer_t *fir_xfer);


#ifdef __cplusplus
}
#endif
/**
 * @}
 *
 */


#endif /* HPM_FFA_DRV_H */
