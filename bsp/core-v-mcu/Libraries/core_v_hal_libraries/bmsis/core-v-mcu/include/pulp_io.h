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

/* Description: Register I/O access
 */

#ifndef __PULP_IO_H
#define __PULP_IO_H

#include <stdint.h>

/* generic I/O write */
static inline void writeb(uint8_t val, uintptr_t addr)
{
	asm volatile("sb %0, 0(%1)"
		     :
		     : "r"(val), "r"((volatile uint8_t *)addr));
}

static inline void writeh(uint16_t val, uintptr_t addr)
{
	asm volatile("sh %0, 0(%1)"
		     :
		     : "r"(val), "r"((volatile uint16_t *)addr));
}

static inline void writew(uint32_t val, uintptr_t addr)
{
	asm volatile("sw %0, 0(%1)"
		     :
		     : "r"(val), "r"((volatile uint32_t *)addr));
}

static inline void writed(uint64_t val, uintptr_t addr)
{
	asm volatile("sd %0, 0(%1)"
		     :
		     : "r"(val), "r"((volatile uint64_t *)addr));
}

/* generic I/O read */
static inline uint8_t readb(const uintptr_t addr)
{
	uint8_t val;

	asm volatile("lb %0, 0(%1)"
		     : "=r"(val)
		     : "r"((const volatile uint8_t *)addr));
	return val;
}

static inline uint16_t readh(const uintptr_t addr)
{
	uint16_t val;

	asm volatile("lh %0, 0(%1)"
		     : "=r"(val)
		     : "r"((const volatile uint16_t *)addr));
	return val;
}

static inline uint32_t readw(const uintptr_t addr)
{
	uint32_t val;

	asm volatile("lw %0, 0(%1)"
		     : "=r"(val)
		     : "r"((const volatile uint32_t *)addr));
	return val;
}

static inline uint64_t readd(const uintptr_t addr)
{
	uint64_t val;

	asm volatile("ld %0, 0(%1)"
		     : "=r"(val)
		     : "r"((const volatile uint64_t *)addr));
	return val;
}
#endif
