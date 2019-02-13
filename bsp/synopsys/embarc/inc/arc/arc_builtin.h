/* ------------------------------------------
 * Copyright (c) 2016, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

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
 *
 * \version 2016.05
 * \date 2014-06-12
 * \author Wayne Ren(Wei.Ren@synopsys.com)
--------------------------------------------- */

/**
 * \file
 * \ingroup ARC_HAL_BUILTIN
 * \brief header file of builtin and helper functions
 *
 * The Metaware toolchain and the GNU toolchain are supported. The details please go to see the file.
 */

/**
 * \addtogroup	ARC_HAL_BUILTIN
 * @{
 */

#ifndef _ARC_HAL_BUILTIN_H_
#define _ARC_HAL_BUILTIN_H_

#include "inc/embARC_toolchain.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__MW__)	/* Metaware toolchain */

#define _arc_nop			_nop 	/*!< no operation, generate a nop instruction produces a single NOP instruction in the compiled code */

#define _arc_brk			_brk 	/*!< generate a brk instruction */

#define _arc_clri			_clri  	/*!< generate a clri instruction */

#define _arc_seti(c)			_seti(c) /*!< generate a seti instruction */

#define	_arc_core_write(regno, val)	_core_write(val, regno)	/*!< write core register */

#define _arc_core_read(regno)		_core_read(regno)	/*!< read core register */

#define _arc_lr_reg(aux)		_lr(aux)	/*!< read auxiliary register */

#define _arc_sr_reg(aux, val)		_sr(val, aux)	/*!< write auxiliary register */

#define _arc_sleep(a)			_sleep(a)	/*!< generate a sleep instruction */

#define _arc_flag(a)			_flag(a)	/*!< generate a flag instruction */

#define _arc_kflag(a)

#define _arc_sync			_sync 		/*!< generate a sync instruction */

/*
 * !< _arc_usually (expr) evaluates expression expr and
 * informs the compiler that the value is usually true.
 */
#define _arc_usually(a)			_Usually((a))

/*
 * !< _arc_rarely (expr) evaluates expression expr and
 * informs the compiler that the value is rarely true.
 */
#define _arc_rarely(a)			_Rarely((a))

#if 0
/**
 * \brief 	Reverses the byte order of the 16-bit operand,
 *  		reversing the endianness of the value.
 *    		Not for ARC HS family
 */
#define _arc_swap16(a)			_swap16(a)
/**
 * \brief 	Reverses the byte order of the 32-bit operand,
 *  		reversing the endianness of the value.
 *    		Not for ARC HS family
 */
#define _arc_swap32(a)			_swap32(a)
#else
Inline uint32_t _arc_swap32(uint32_t val) {
	register uint32_t v;
	__asm__ volatile ("swape %0, %1" :"=r"(v): "r"(val));
	return v;
}

Inline uint16_t _arc_swap16(uint32_t val) {
	register uint32_t temp;
	register uint32_t v;
	__asm__ volatile ("swape %0, %1" :"=r"(temp): "r"(val));
	__asm__ volatile ("lsr16 %0, %1" :"=r"(v): "r"(temp));
	return (unsigned short)v;
}
#endif

/**
 * \brief 	Each call to _swi() generates one
 * 			software interrupt instruction (SWI) for processors
 * 			to support the SWI instruction.
 */
#define _arc_swi				_swi

/* \todo add more builtin functions of metaware tool */

#elif defined (__GNU__) /* GNU toolchain */

#define _arc_nop				__builtin_arc_nop
#define _arc_brk				__builtin_arc_brk
#define _arc_seti(c)				__builtin_arc_seti(c)
#define _arc_core_write(regno, val)		__builtin_arc_core_write(regno,val)
#define _arc_core_read(regno)			__builtin_arc_core_read(regno)
#define _arc_flag(a)				__builtin_arc_flag(a)
#define _arc_kflag(a)				__builtin_arc_kflag(a)
#define _arc_lr_reg(aux)			__builtin_arc_lr(aux)
/* don't uncomment this now */
//#define _arc_sr_reg(aux, val)			__builtin_arc_sr(aux, val)
#define _arc_sleep(a)				__builtin_arc_sleep(a)
//#define _arc_sync				__builtin_arc_sync

/**
 * \brief _arc_usually (expr) evaluates expression expr and
 * 		  informs the compiler that the value is usually true.
 */
#define _arc_usually(a)				__builtin_expect((int)(a), 1)

/**
 * \brief _arc_rarely (expr) evaluates expression expr and
 *	informs the compiler that the value is rarely true.
 */
#define _arc_rarely(a)				__builtin_expect((int)(a), 0)

/**
 * \brief 	Each call to _swi() generates one
 * 			software interrupt instruction (SWI) for processors
 * 			to support the SWI instruction.
 */
#define _arc_swi 				__builtin_arc_swi

Inline uint32_t _arc_clri(void) {
	register uint32_t v;
	__asm__ volatile ("clri %0" :"=r"(v));
	return v;

}
/* \todo add more builtin functions of gnu tool */

Inline uint32_t _arc_swap32(uint32_t val) {
	register uint32_t v;
	__asm__ volatile ("swape %0, %1" :"=r"(v): "r"(val));
	return v;
}

Inline uint16_t _arc_swap16(uint32_t val) {
	register uint32_t temp;
	register uint32_t v;
	__asm__ volatile ("swape %0, %1" :"=r"(temp): "r"(val));
	__asm__ volatile ("lsr16 %0, %1" :"=r"(v): "r"(temp));
	return (unsigned short)v;
}

Inline void _arc_sync(void) {
	__asm__ volatile ("sync");
}

/**
 * \note Following is a workaround for arc gcc
 *       built-in function __builtin_arc_sr.
 *       But it is wrong in GCC arc-4.8-R3-rc3 and shouldn't be used.
 */

/*
 * The auxiliary register address is specified as a long immediate operand by caller.
 * e.g.
 *    write_aux_reg(0x69, some_val);
 * This generates the tightest code.
 */
#define write_aux_reg(reg_imm, val)	\
({					\
	Asm(		\
	"	sr   %0, [%1]	\n"	\
	:				\
	: "ir"(val), "r"(reg_imm));	\
})

#define _arc_sr_reg(aux, val)			write_aux_reg(aux, val)

#endif

/* \todo add more helper functions here, such as memory operation */

#define _arc_aux_read(aux)			_arc_lr_reg(aux)
#define _arc_aux_write(aux, val)		_arc_sr_reg(aux, val)

/**
 * \name cache related helper function
 * @{
 */

/**
 * \brief  read memory and bypass the cache
 * \param[in] ptr memory address
 * \return value in the memory
 */
Inline uint32_t _arc_read_uncached_32(void *ptr)
{
	uint32_t __ret;
	Asm("ld.di %0, [%1]":"=r"(__ret):"r"(ptr));
	return __ret;
}

/**
 * \brief  write memory and bypass the cache
 * \param[in] ptr memory address
 * \param[in] data  vaule to be written
 */
Inline void _arc_write_uncached_32(void *ptr, uint32_t data)
{
	Asm("st.di %0, [%1]":: "r"(data), "r"(ptr));
}

/**
 * \brief  read memory with cache
 * \param[in] ptr memory address
 * \returns value in the memory
 */
Inline uint32_t _arc_read_cached_32(void *ptr)
{
	uint32_t __ret;
	Asm("ld %0, [%1]":"=r"(__ret):"r"(ptr));
	return __ret;
}

/**
 * \brief  read memory with cache
 * \param[in] ptr memory address
 * \param[in] data vaule to be written
 * \return description
 */
Inline void _arc_write_cached_32(void *ptr, uint32_t data)
{
	Asm("st %0, [%1]":: "r"(data), "r"(ptr));
}

/**
 * \brief go to main function with proper arguments
 * \param  argc argument count
 * \param  argv argument content array
 * \retval return value of main function
 */
Inline int32_t _arc_goto_main(int argc, char **argv) {
	int __ret;
	__asm__ volatile(
		"mov %%r0, %1\n"
		"mov %%r1, %2\n"
		"push_s %%blink\n"
		"jl main\n"
		"pop_s %%blink\n"
		"mov %0, %%r0"
		:"=r"(__ret): "r"(argc), "r"(argv));
	return (int)__ret;
}

#ifdef __cplusplus
}
#endif

#if defined(LIB_SECURESHIELD) && defined(LIB_SECURESHIELD_OVERRIDES) && (SECURESHIELD_VERSION == 1)
#define OVERRIDE_ARC_HAL_BUILTIN_H
#include "secureshield_overrides.h"
#endif

/** @} */
#endif /* _ARC_HAL_BUILTIN_H_ */
/** @} */
