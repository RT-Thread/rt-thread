/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PLB_DRV_H
#define HPM_PLB_DRV_H

#include "hpm_common.h"
#include "hpm_plb_regs.h"

/**
 * @brief PLB driver APIs
 * @defgroup plb_interface PLB driver APIs
 * @ingroup io_interfaces
 * @{
 */

#define PLB_SLICE_MASK  (0xf)
#define PLB_SLICE_HIGH_BIT_MASK_SET(slice) (PLB_SLICE_MASK << ((slice - plb_type_b_slice_8) << 2))
#define PLB_SLICE_HIGH_BIT_SHIFT(slice) ((slice - plb_type_b_slice_8) << 2)
#define PLB_SLICE_LOW_BIT_MASK_SET(slice) (PLB_SLICE_MASK << (slice << 2))
#define PLB_SLICE_LOW_BIT_SHIFT(slice) (slice << 2)

/**
 * @brief plb channels
 *
 */
typedef enum plb_chn {
#ifdef PLB_TYPE_B_0
    plb_chn0 = PLB_TYPE_B_0,
#endif
#ifdef PLB_TYPE_B_1
    plb_chn1 = PLB_TYPE_B_1,
#endif
#ifdef PLB_TYPE_B_2
    plb_chn2 = PLB_TYPE_B_2,
#endif
#ifdef PLB_TYPE_B_3
    plb_chn3 = PLB_TYPE_B_3,
#endif
#ifdef PLB_TYPE_B_4
    plb_chn4 = PLB_TYPE_B_4,
#endif
#ifdef PLB_TYPE_B_5
    plb_chn5 = PLB_TYPE_B_5,
#endif
#ifdef PLB_TYPE_B_6
    plb_chn6 = PLB_TYPE_B_6,
#endif
#ifdef PLB_TYPE_B_7
    plb_chn7 = PLB_TYPE_B_7,
#endif
} plb_chn_t;

/**
 * @brief PLB look-up table unit
 *
 */
typedef enum plb_type_a_lut_num {
#ifdef PLB_TYPE_A_0
    plb_type_a_table0 = PLB_TYPE_A_0,
#endif
#ifdef PLB_TYPE_A_1
    plb_type_a_table1 = PLB_TYPE_A_1,
#endif
#ifdef PLB_TYPE_A_2
    plb_type_a_table2 = PLB_TYPE_A_2,
#endif
#ifdef PLB_TYPE_A_3
    plb_type_a_table3 = PLB_TYPE_A_3,
#endif
#ifdef PLB_TYPE_A_4
    plb_type_a_table4 = PLB_TYPE_A_4,
#endif
#ifdef PLB_TYPE_A_5
    plb_type_a_table5 = PLB_TYPE_A_5,
#endif
#ifdef PLB_TYPE_A_6
    plb_type_a_table6 = PLB_TYPE_A_6,
#endif
#ifdef PLB_TYPE_A_7
    plb_type_a_table7 = PLB_TYPE_A_7,
#endif
} plb_type_a_lut_num_t;

/**
 * @brief PLB truth table configuration unit
 *
 */
typedef union {
    struct {
        uint16_t index0_1bit_out: 1;
        uint16_t index1_1bit_out: 1;
        uint16_t index2_1bit_out: 1;
        uint16_t index3_1bit_out: 1;
        uint16_t index4_1bit_out: 1;
        uint16_t index5_1bit_out: 1;
        uint16_t index6_1bit_out: 1;
        uint16_t index7_1bit_out: 1;
        uint16_t index8_1bit_out: 1;
        uint16_t index9_1bit_out: 1;
        uint16_t index10_1bit_out: 1;
        uint16_t index11_1bit_out: 1;
        uint16_t index12_1bit_out: 1;
        uint16_t index13_1bit_out: 1;
        uint16_t index14_1bit_out: 1;
        uint16_t index15_1bit_out: 1;
    };
    uint16_t val;
} plb_type_a_truth_t;

/**
 * @brief Index of slice
 *
 */
typedef enum plb_type_b_lut_slice {
    plb_type_b_slice_0 = 0,
    plb_type_b_slice_1 = 1,
    plb_type_b_slice_2 = 2,
    plb_type_b_slice_3 = 3,
    plb_type_b_slice_4 = 4,
    plb_type_b_slice_5 = 5,
    plb_type_b_slice_6 = 6,
    plb_type_b_slice_7 = 7,
    plb_type_b_slice_8 = 8,
    plb_type_b_slice_9 = 9,
    plb_type_b_slice_10 = 10,
    plb_type_b_slice_11 = 11,
    plb_type_b_slice_12 = 12,
    plb_type_b_slice_13 = 13,
    plb_type_b_slice_14 = 14,
    plb_type_b_slice_15 = 15,
} plb_type_b_lut_slice_t;

/**
 * @brief Configuration of slice
 *
 */
typedef enum plb_type_b_slice_opt {
    plb_slice_opt_keep = 0,                 /**< The data unit keeps the value of the previous cycle */
    plb_slice_opt_get_cmp0_val = 1,         /**< The data unit will take the value of the cmp0 register as the value for the next cycle */
    plb_slice_opt_get_cmp1_val = 2,         /**< The data unit will take the value of the cmp1 register as the value for the next cycle */
    plb_slice_opt_get_cmp2_val = 3,         /**< The data unit will take the value of the cmp2 register as the value for the next cycle */
    plb_slice_opt_add_one = 4,              /**< The next cycle value of the data cell is the current value plus 1 */
    plb_slice_opt_add_two = 5,              /**< The next cycle value of the data cell is the current value plus 2 */
    plb_slice_opt_sub_one = 6,              /**< The next cycle value of the data cell is the current value minus 1 */
    plb_slice_opt_sub_two = 7,              /**< The next cycle value of the data cell is the current value minus 2 */
    plb_slice_opt_shift_left = 4 << 8,      /**< The value of the next cycle of the data cell is shifted one place to the left of the current value */
    plb_slice_opt_shift_left_add_one = 5 << 8,  /**< The next cycle value of the data cell is the current value shifted one place to the left, with the lower bit complemented by one */
    plb_slice_opt_shift_right = 6 << 8,     /**< The value of the next cycle of the data cell is shifted one place to the right of the current value */
    plb_slice_opt_shift_right_add_one = 7 << 8, /**< The next cycle value of the data cell is the current value shifted one place to the right, with the lower bit complemented by one */
} plb_type_b_slice_opt_t;

/**
 * @brief Comparator index
 *
 */
typedef enum plb_type_b_cmp {
    plb_type_b_cmp0 = PLB_TYPE_B_CMP_0,
    plb_type_b_cmp1 = PLB_TYPE_B_CMP_1,
    plb_type_b_cmp2 = PLB_TYPE_B_CMP_2,
    plb_type_b_cmp3 = PLB_TYPE_B_CMP_3,
} plb_type_b_cmp_t;

/**
 * @brief Comparator operation
 *
 */
typedef enum plb_type_b_cmp_mode {
    plb_cmp_mode_out_zero = 0,          /**< output zero */
    plb_cmp_mode_out_one = 1,           /**< output one */
    plb_cmp_mode_gt = 2,                /**< Data unit greater than cmp output one, otherwise output zero */
    plb_cmp_mode_lt = 3,                /**< Data unit less than cmp output one, otherwise output zero */
    plb_cmp_mode_eq = 4,                /**< Data unit equal to cmp output one, otherwise output zero */
    plb_cmp_mode_ne = 5,                /**< Data unit not equal to cmp output one, otherwise output zero */
    plb_cmp_mode_ge = 6,                /**< Data unit greater than or equal to cmp output one, otherwise output zero */
    plb_cmp_mode_le = 7,                /**< Data unit less than or equal to cmp output one, otherwise output zero */
    plb_cmp_mode_and_mask = 10,         /**< The data cell corresponding to the bit set to one by cmp is and */
    plb_cmp_mode_or_mask = 11,          /**< The data cell corresponding to the bit set to one by cmp is or */
    plb_cmp_mode_xor_mask = 12,         /**< The data cell corresponding to the bit set to one by cmp is xor */
    plb_cmp_mode_nand_mask = 13,        /**< The data cell corresponding to the bit set to one by cmp is nand */
    plb_cmp_mode_nor_mask = 14,         /**< The data cell corresponding to the bit set to one by cmp is nor */
    plb_cmp_mode_xnor_mask = 15,        /**< The data cell corresponding to the bit set to one by cmp is xnor */
} plb_type_b_cmp_mode_t;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Configuring the truth table for lookup tables
 *
 * @param plb @ref PLB_Type plb base
 * @param chn @ref plb_chn_t
 * @param lut_num @ref plb_type_a_lut_num_t
 * @param truth @ref plb_type_a_truth_t
 */
static inline void plb_type_a_set_lut(PLB_Type *plb, plb_chn_t chn, plb_type_a_lut_num_t lut_num, plb_type_a_truth_t *truth)
{
    plb->TYPE_A[chn].LOOKUP_TABLE[lut_num] = PLB_TYPE_A_LOOKUP_TABLE_LOOKUP_TABLE_SET(truth->val);
}

/**
 * @brief The software injects a cycle value into the TYPE A channel.
 *
 * @param plb @ref PLB_Type plb base
 * @param chn @ref plb_chn_t
 * @param inject_val Injected values
 */
static inline void plb_type_a_inject_by_sw(PLB_Type *plb, plb_chn_t chn, uint8_t inject_val)
{
    plb->TYPE_A[chn].SW_INJECT = PLB_TYPE_A_SW_INJECT_SW_INJECT_SET(inject_val);
}

/**
 * @brief Configure the value of the CMP
 *
 * @param plb @ref PLB_Type plb base
 * @param chn @ref plb_chn_t
 * @param cmp_index @ref plb_type_b_cmp_t
 * @param val CMP value
 */
static inline void plb_type_b_set_cmp_val(PLB_Type *plb, plb_chn_t chn, plb_type_b_cmp_t cmp_index, uint32_t val)
{
    plb->TYPE_B[chn].CMP[cmp_index] = PLB_TYPE_B_CMP_CMP_VALUE_SET(val);
}

/**
 * @brief Setting the mode of the CMP
 *
 * @param plb @ref PLB_Type plb base
 * @param chn @ref plb_chn_t
 * @param cmp_index @ref plb_type_b_cmp_t
 * @param cmp_mode @ref plb_type_b_cmp_mode_t
 */
static inline void plb_type_b_set_cmp_mode(PLB_Type *plb, plb_chn_t chn, plb_type_b_cmp_t cmp_index, plb_type_b_cmp_mode_t cmp_mode)
{
    plb->TYPE_B[chn].MODE = (plb->TYPE_B[chn].MODE & (~(PLB_TYPE_B_MODE_OUT0_SEL_MASK << (cmp_index << 2)))) |
                            ((PLB_TYPE_B_MODE_OUT0_SEL_MASK & cmp_mode) << (cmp_index << 2));
}

/**
 * @brief Software injection values
 *
 * @param plb @ref PLB_Type plb base
 * @param chn @ref plb_chn_t
 * @param val value
 */
static inline void plb_type_b_inject_by_sw(PLB_Type *plb, plb_chn_t chn, uint32_t val)
{
    plb->TYPE_B[chn].SW_INJECT = val;
}

/**
 * @brief Configuring the PLB type_b's lookup table
 *
 * @param plb @ref PLB_Type plb base
 * @param chn @ref plb_chn_t
 * @param slice @ref plb_type_b_lut_slice_t
 * @param opt @ref plb_type_b_slice_opt_t
 */
void plb_type_b_set_lut(PLB_Type *plb, plb_chn_t chn, plb_type_b_lut_slice_t slice, plb_type_b_slice_opt_t opt);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* HPM_PLB_DRV_H */

