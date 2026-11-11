/*
 * Copyright 2020 ETH Zurich
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
 *
 * SPDX-License-Identifier: Apache-2.0
 * Author: Robert Balas (balasr@iis.ee.ethz.ch)
 */

/* Description: CSR access macros */

#ifndef __CSR_H
#define __CSR_H

#include "bits.h"

/* TODO: complete this */
#define CSR_MSTATUS  0x300
#define CSR_MISA     0x301
#define CSR_MIE	     0x304
#define CSR_MTVEC    0x305
#define CSR_MSCRATCH 0x340
#define CSR_MEPC     0x341
#define CSR_MCAUSE   0x342
#define CSR_MTVAL    0x343
#define CSR_MIP	     0x344
#define CSR_PMPCFG0  0x3a0
#define CSR_PMPADDR0 0x3b0
#define CSR_MHARTID  0xf14

/* TODO: complete this */
#define MSTATUS_IE BIT(3)

#define __CSR_EXPAND(x) #x

#define csr_read(csr)                                                          \
	({                                                                     \
		register unsigned long __val;                                  \
		asm volatile("csrr %0, " __CSR_EXPAND(csr)                     \
			     : "=r"(__val)                                     \
			     :                                                 \
			     : "memory");                                      \
		__val;                                                         \
	})

#define csr_write(csr, val)                                                    \
	({                                                                     \
		unsigned long __val = (unsigned long)(val);                    \
		asm volatile("csrw " __CSR_EXPAND(csr) ", %0"                  \
			     :                                                 \
			     : "rK"(__val)                                     \
			     : "memory");                                      \
	})

/* TODO: I hope this properly does a memory barrier with the "memory" hint */
#define csr_read_clear(csr, val)                                               \
	({                                                                     \
		unsigned long __val = (unsigned long)(val);                    \
		asm volatile("csrrc %0, " __CSR_EXPAND(csr) ", %1"             \
			     : "=r"(__val)                                     \
			     : "rK"(__val)                                     \
			     : "memory");                                      \
		__val;                                                         \
	})

#define csr_read_set(csr, val)                                                 \
	({                                                                     \
		unsigned long __val = (unsigned long)(val);                    \
		asm volatile("csrrs %0, " __CSR_EXPAND(csr) ", %1"             \
			     : "=r"(__val)                                     \
			     : "rK"(__val)                                     \
			     : "memory");                                      \
		__val;                                                         \
	})

#endif
