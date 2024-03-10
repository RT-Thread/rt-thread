/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __CORTEXA_GCC_H
#define __CORTEXA_GCC_H

#include "cmsis_gcc.h"

#define __STRINGIFY(x) #x

#define __MCR(coproc, opcode_1, src, CRn, CRm, opcode_2)                          \
    __ASM volatile ("MCR " __STRINGIFY(p##coproc) ", " __STRINGIFY(opcode_1) ", " \
                    "%0, " __STRINGIFY(c##CRn) ", " __STRINGIFY(c##CRm) ", "      \
                    __STRINGIFY(opcode_2)                                         \
                    : : "r" (src) )

#define __MRC(coproc, opcode_1, CRn, CRm, opcode_2)                               \
  ({                                                                              \
    uint32_t __dst;                                                               \
    __ASM volatile ("MRC " __STRINGIFY(p##coproc) ", " __STRINGIFY(opcode_1) ", " \
                    "%0, " __STRINGIFY(c##CRn) ", " __STRINGIFY(c##CRm) ", "      \
                    __STRINGIFY(opcode_2)                                         \
                    : "=r" (__dst) );                                             \
    __dst;                                                                        \
  })

__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_APSR(uint32_t apsr)
{
  __ASM volatile ("MSR apsr, %0" : : "r" (apsr) : "cc");
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_CPSR(void)
{
  uint32_t result;

  __ASM volatile ("MRS %0, cpsr" : "=r" (result) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_CPSR(uint32_t cpsr)
{
  __ASM volatile ("MSR cpsr, %0" : : "r" (cpsr) : "cc");
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_FPEXC(void)
{
  uint32_t result;

  __ASM volatile ("VMRS %0, fpexc" : "=r" (result) );
  return result;
}

__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_FPEXC(uint32_t fpexc)
{
  __ASM volatile ("VMSR fpexc, %0" : : "r" (fpexc));
}

#endif /* __CORTEXA_GCC_H */
