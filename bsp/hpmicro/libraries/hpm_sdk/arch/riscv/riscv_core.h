/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef RISCV_CORE_H
#define RISCV_CORE_H

#include "hpm_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  write fp csr
 *
 * @param v value to be set
 */
#define write_fcsr(v) __asm volatile("fscsr %0" : : "r"(v))

/**
 * @brief clear bits in csr
 *
 * @param csr_num specific csr
 * @param bit bits to be cleared
 */
#define clear_csr(csr_num, bit) __asm volatile("csrc %0, %1" : : "i"(csr_num), "r"(bit))

/**
 * @brief set bits in csr
 *
 * @param csr_num specific csr
 * @param bit bits to be set
 */
#define set_csr(csr_num, bit) __asm volatile("csrs %0, %1" : : "i"(csr_num), "r"(bit))

/**
 * @brief write value to csr
 *
 * @param csr_num specific csr
 * @param v value to be written
 */
#define write_csr(csr_num, v) __asm volatile("csrw %0, %1" : : "i"(csr_num), "r"(v))

/**
 * @brief read value of specific csr
 *
 * @param csr_num specific csr
 *
 * @return csr value
 */
#define read_csr(csr_num) ({ uint32_t v; __asm volatile("csrr %0, %1" : "=r"(v) : "i"(csr_num)); v; })

/**
 * @brief read fp csr
 *
 * @return fp csr value
 */
#define read_fcsr() ({ uint32_t v; __asm volatile("frcsr %0" : "=r"(v)); v; })

/**
 * @brief execute fence.i
 *
 */
#define fencei() __asm volatile("fence.i")

#ifdef __cplusplus
}
#endif


#endif /* RISCV_CORE_H */
