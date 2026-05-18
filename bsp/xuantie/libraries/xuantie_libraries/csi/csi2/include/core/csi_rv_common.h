 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __CSI_RV_COMMON_H__
#define __CSI_RV_COMMON_H__

#include <stdlib.h>
#include <stdint.h>

#ifndef __ASM
#define __ASM                   __asm     /*!< asm keyword for GNU Compiler */
#endif

#ifndef __INLINE
#define __INLINE                inline    /*!< inline keyword for GNU Compiler */
#endif

#ifndef __ALWAYS_STATIC_INLINE
#define __ALWAYS_STATIC_INLINE  __attribute__((always_inline)) static inline
#endif

#ifndef __STATIC_INLINE
#define __STATIC_INLINE         static inline
#endif

#ifndef __NO_RETURN
#define __NO_RETURN             __attribute__((__noreturn__))
#endif

#ifndef __USED
#define __USED                  __attribute__((used))
#endif

#ifndef __WEAK
#define __WEAK                  __attribute__((weak))
#endif

#ifndef __PACKED
#define __PACKED                __attribute__((packed, aligned(1)))
#endif

#ifndef __PACKED_STRUCT
#define __PACKED_STRUCT         struct __attribute__((packed, aligned(1)))
#endif

#ifndef __PACKED_UNION
#define __PACKED_UNION          union __attribute__((packed, aligned(1)))
#endif

#ifdef __ASSEMBLY__
#define __ASM_STR(x)    x
#else
#define __ASM_STR(x)    #x
#endif

#define     __I      volatile const       /*!< Defines 'read only' permissions */
#define     __O      volatile             /*!< Defines 'write only' permissions */
#define     __IO     volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const       /*! Defines 'read only' structure member permissions */
#define     __OM     volatile             /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile             /*! Defines 'read / write' structure member permissions */

#ifndef __ASSEMBLY__

#define RISCV_FENCE(p, s) \
    __asm__ __volatile__ ("fence " #p "," #s : : : "memory")

#define rv_csr_read(csr)                                   \
    ({                                                  \
        register unsigned long __v;                     \
        __asm__ __volatile__("csrr %0, " __ASM_STR(csr) \
                             : "=r"(__v)                \
                             :                          \
                             : "memory");               \
        __v;                                            \
    })

#define rv_csr_write(csr, val)                                \
    ({                                                     \
        unsigned long __v = (unsigned long)(val);          \
        __asm__ __volatile__("csrw " __ASM_STR(csr) ", %0" \
                             :                             \
                             : "rK"(__v)                   \
                             : "memory");                  \
    })

#define rv_csr_read_set(csr, val)                                  \
    ({                                                          \
        unsigned long __v = (unsigned long)(val);               \
        __asm__ __volatile__("csrrs %0, " __ASM_STR(csr) ", %1" \
                             : "=r"(__v) : "rK"(__v)            \
                             : "memory");                       \
        __v;                                                    \
    })

#define rv_csr_set(csr, val)                                  \
    ({                                                     \
        unsigned long __v = (unsigned long)(val);          \
        __asm__ __volatile__("csrs " __ASM_STR(csr) ", %0" \
                             : : "rK"(__v)                 \
                             : "memory");                  \
    })

#define rv_csr_read_clear(csr, val)                                \
    ({                                                          \
        unsigned long __v = (unsigned long)(val);               \
        __asm__ __volatile__("csrrc %0, " __ASM_STR(csr) ", %1" \
                             : "=r"(__v) : "rK"(__v)            \
                             : "memory");                       \
        __v;                                                    \
    })

#define rv_csr_clear(csr, val)                                \
    ({                                                     \
        unsigned long __v = (unsigned long)(val);          \
        __asm__ __volatile__("csrc " __ASM_STR(csr) ", %0" \
                             : : "rK"(__v)                 \
                             : "memory");                  \
    })

#define rv_csr_read_write(csr, val)                              \
     ({                                                          \
         unsigned long __v = (unsigned long)(val);               \
         __asm__ __volatile__("csrrw %0, " __ASM_STR(csr) ", %1" \
                              : "=r"(__v)                        \
                              : "rK"(__v)                        \
                              : "memory");                       \
         __v;                                                    \
     })

 __ALWAYS_STATIC_INLINE uint8_t rv_readb(uintptr_t addr)
 {
    uint8_t val;

    val = *(volatile uint8_t *)addr;
    RISCV_FENCE(ir, ir);
    return val;
 }

 __ALWAYS_STATIC_INLINE uint16_t rv_readw(uintptr_t addr)
 {
    uint16_t val;

    val = *(volatile uint16_t *)addr;
    RISCV_FENCE(ir, ir);
    return val;
 }

 __ALWAYS_STATIC_INLINE uint32_t rv_readl(uintptr_t addr)
 {
    uint32_t val;

    val = *(volatile uint32_t *)addr;
    RISCV_FENCE(ir, ir);
    return val;
 }

 __ALWAYS_STATIC_INLINE uint64_t rv_readq(uintptr_t addr)
 {
    uint64_t val;

    val = *(volatile uint64_t *)addr;
    RISCV_FENCE(ir, ir);
    return val;
 }

 __ALWAYS_STATIC_INLINE void rv_writeb(uint8_t val, uintptr_t addr)
 {
    *(volatile uint8_t *)addr = val;
    RISCV_FENCE(ow, ow);
 }

 __ALWAYS_STATIC_INLINE void rv_writew(uint16_t val, uintptr_t addr)
 {
    *(volatile uint16_t *)addr = val;
    RISCV_FENCE(ow, ow);
 }

 __ALWAYS_STATIC_INLINE void rv_writel(uint32_t val, uintptr_t addr)
 {
    *(volatile uint32_t *)addr = val;
    RISCV_FENCE(ow, ow);
 }

 __ALWAYS_STATIC_INLINE void rv_writeq(uint64_t val, uintptr_t addr)
 {
    *(volatile uint64_t *)addr = val;
    RISCV_FENCE(ow, ow);
 }

/**
  \brief   Get low 32 bits of MSTATEEN0
  \details Returns the current value of the MSTATEEN0 register.
  \return               MSTATEEN0 Register value
  */
__ALWAYS_STATIC_INLINE unsigned long __get_MSTATEEN0(void)
{
    volatile unsigned long result;
    __ASM volatile("csrr %0, mstateen0" : "=r"(result));
    return (result);
}

/**
  \brief   Set low 32 bits of of MSTATEEN0
  \details Assigns the given value to the MSTATEEN0 register.
  \param [in]    mstateen0  MSTATEEN0 value to set
  */
__ALWAYS_STATIC_INLINE void __set_MSTATEEN0(unsigned long mstateen0)
{
    __ASM volatile("csrw mstateen0, %0" : : "r"(mstateen0));
}

/**
  \brief   Get high 32 bits of MSTATEEN0
  \details Returns the current value of the MSTATEEN0H register.
  \return               MSTATEEN0 Register value
  */
__ALWAYS_STATIC_INLINE unsigned long __get_MSTATEEN0H(void)
{
    volatile unsigned long result;
    __ASM volatile("csrr %0, mstateen0h" : "=r"(result));
    return (result);
}

/**
  \brief   Set high 32 bits of of MSTATEEN0
  \details Assigns the given value to the MSTATEEN0H register.
  \param [in]    mstateen0  MSTATEEN0 value to set
  */
__ALWAYS_STATIC_INLINE void __set_MSTATEEN0H(unsigned long mstateen0h)
{
    __ASM volatile("csrw mstateen0h, %0" : : "r"(mstateen0h));
}

/**
  \brief   Get MIREG
  \details Returns the current value of the MIREG.
  \return               MIREG Register value
  */
__ALWAYS_STATIC_INLINE unsigned long __get_MIREG(void)
{
    register unsigned long result;
    __ASM volatile("csrr %0, mireg" : "=r"(result));
    return (result);
}

/**
  \brief   Set MIREG
  \details Assigns the given value to the MIREG.
  \param [in]    mireg  MIREG value to set
  */
__ALWAYS_STATIC_INLINE void __set_MIREG(unsigned long mireg)
{
    __ASM volatile("csrw mireg, %0" : : "r"(mireg));
}

/**
  \brief   Get MIREG2
  \details Returns the current value of the MIREG2.
  \return               MIREG2 Register value
  */
__ALWAYS_STATIC_INLINE unsigned long __get_MIREG2(void)
{
    register unsigned long result;
    __ASM volatile("csrr %0, mireg2" : "=r"(result));
    return (result);
}

/**
  \brief   Set MIREG2
  \details Assigns the given value to the MIREG2.
  \param [in]    mireg2  MIREG2 value to set
  */
__ALWAYS_STATIC_INLINE void __set_MIREG2(unsigned long mireg2)
{
    __ASM volatile("csrw mireg2, %0" : : "r"(mireg2));
}

/**
  \brief   Get SIREG
  \details Returns the current value of the SIREG.
  \return               SIREG Register value
  */
__ALWAYS_STATIC_INLINE unsigned long __get_SIREG(void)
{
    register unsigned long result;
    __ASM volatile("csrr %0, sireg" : "=r"(result));
    return (result);
}

/**
  \brief   Set SIREG
  \details Assigns the given value to the SIREG.
  \param [in]    sireg  SIREG value to set
  */
__ALWAYS_STATIC_INLINE void __set_SIREG(unsigned long sireg)
{
    __ASM volatile("csrw sireg, %0" : : "r"(sireg));
}

/**
  \brief   Get SIREG2
  \details Returns the current value of the SIREG2.
  \return               SIREG2 Register value
  */
__ALWAYS_STATIC_INLINE unsigned long __get_SIREG2(void)
{
    register unsigned long result;
    __ASM volatile("csrr %0, sireg2" : "=r"(result));
    return (result);
}

/**
  \brief   Set SIREG2
  \details Assigns the given value to the SIREG2.
  \param [in]    sireg2  SIREG2 value to set
  */
__ALWAYS_STATIC_INLINE void __set_SIREG2(unsigned long sireg2)
{
    __ASM volatile("csrw sireg2, %0" : : "r"(sireg2));
}

/**
  \brief   Get MISELECT
  \details Returns the current value of the MISELECT.
  \return               MISELECT Register value
  */
__ALWAYS_STATIC_INLINE unsigned long __get_MISELECT(void)
{
    register unsigned long result;
    __ASM volatile("csrr %0, miselect" : "=r"(result));
    return (result);
}

/**
  \brief   Set MISELECT
  \details Assigns the given value to the MISELECT.
  \param [in]    miselect  MISELECT value to set
  */
__ALWAYS_STATIC_INLINE void __set_MISELECT(unsigned long miselect)
{
    __ASM volatile("csrw miselect, %0" : : "r"(miselect));
}

/**
  \brief   Get SISELECT
  \details Returns the current value of the SISELECT.
  \return               SISELECT Register value
  */
__ALWAYS_STATIC_INLINE unsigned long __get_SISELECT(void)
{
    register unsigned long result;
    __ASM volatile("csrr %0, siselect" : "=r"(result));
    return (result);
}

/**
  \brief   Set SISELECT
  \details Assigns the given value to the SISELECT.
  \param [in]    siselect  SISELECT value to set
  */
__ALWAYS_STATIC_INLINE void __set_SISELECT(unsigned long siselect)
{
    __ASM volatile("csrw siselect, %0" : : "r"(siselect));
}

__ALWAYS_STATIC_INLINE uint8_t is_power_of_two(uint32_t x)
{
    return x && !(x & (x - 1));
}

__ALWAYS_STATIC_INLINE uint32_t log2_ulong(unsigned long x)
{
    uint32_t result = 0;
    while (x > 1) {
        x >>= 1;
        result++;
    }
    return result;
}

__ALWAYS_STATIC_INLINE unsigned long align_to_power_of_two(unsigned long size)
{
    if (size <= 1) {
        return size;
    }

#if defined(__GNUC__) || defined(__clang__)
    unsigned long leading_zeros = __builtin_clzl(size - 1);
    return 1UL << ((sizeof(unsigned long) << 3) - leading_zeros);
#else
    unsigned long value = size - 1;
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
#if __SIZEOF_LONG__ == 8
    value |= value >> 32;
#endif
    return value + 1;
#endif
}

#endif /* __ASSEMBLY__ */

#endif /* __CSI_RV_COMMON_H__ */
