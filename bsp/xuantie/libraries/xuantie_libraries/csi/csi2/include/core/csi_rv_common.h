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



#endif /* __CSI_RV_COMMON_H__ */

