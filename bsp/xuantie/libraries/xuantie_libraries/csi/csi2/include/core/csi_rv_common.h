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

#ifndef __ASSEMBLY__
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
#endif

#define CSR_MCOR        0x7c2
#define CSR_MHCR        0x7c1
#define CSR_MCCR2       0x7c3
#define CSR_MHINT       0x7c5
#define CSR_MHINT2      0x7cc
#define CSR_MHINT3      0x7cd
#define CSR_MHINT4      0x7ce
#define CSR_MXSTATUS    0x7c0
#define CSR_PLIC_BASE   0xfc1
#define CSR_MRMR        0x7c6
#define CSR_MRVBR       0x7c7
#define CSR_MCOUNTERWEN 0x7c9
#define CSR_MSMPR       0x7f3

#define CSR_MARCHID     0xf12
#define CSR_MIMPID      0xf13
#define CSR_MHARTID     0xf14
#define CSR_MCPUID      0xfc0

#define CSR_MSTATUS     0x300
#define CSR_MISA        0x301
#define CSR_MEDELEG     0x302
#define CSR_MIDELEG     0x303
#define CSR_MIE         0x304
#define CSR_MTVEC       0x305
#define CSR_MCOUNTEREN  0x306
#define CSR_MENVCFG     0x30a
#define CSR_MSTATUSH    0x310
#define CSR_MSCRATCH    0x340
#define CSR_MEPC        0x341
#define CSR_MCAUSE      0x342
#define CSR_MTVAL       0x343
#define CSR_MIP         0x344
#define CSR_MTINST      0x34a
#define CSR_MTVAL2      0x34b

 /* Machine Memory Protection */
#define CSR_PMPCFG0     0x3a0
#define CSR_PMPCFG1     0x3a1
#define CSR_PMPCFG2     0x3a2
#define CSR_PMPCFG3     0x3a3
#define CSR_PMPCFG4     0x3a4
#define CSR_PMPCFG5     0x3a5
#define CSR_PMPCFG6     0x3a6
#define CSR_PMPCFG7     0x3a7
#define CSR_PMPCFG8     0x3a8
#define CSR_PMPCFG9     0x3a9
#define CSR_PMPCFG10    0x3aa
#define CSR_PMPCFG11    0x3ab
#define CSR_PMPCFG12    0x3ac
#define CSR_PMPCFG13    0x3ad
#define CSR_PMPCFG14    0x3ae
#define CSR_PMPCFG15    0x3af
#define CSR_PMPADDR0    0x3b0
#define CSR_PMPADDR1    0x3b1
#define CSR_PMPADDR2    0x3b2
#define CSR_PMPADDR3    0x3b3
#define CSR_PMPADDR4    0x3b4
#define CSR_PMPADDR5    0x3b5
#define CSR_PMPADDR6    0x3b6
#define CSR_PMPADDR7    0x3b7

#endif /* __CSI_RV_COMMON_H__ */

