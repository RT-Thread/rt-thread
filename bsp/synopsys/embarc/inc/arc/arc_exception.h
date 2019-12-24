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
 * \date 2014-07-15
 * \author Wayne Ren(Wei.Ren@synopsys.com)
--------------------------------------------- */

/**
 * \file
 * \ingroup ARC_HAL_EXCEPTION_CPU ARC_HAL_EXCEPTION_INTERRUPT
 * \brief header file of exception and interrupt management module
 */

#ifndef _ARC_HAL_EXCEPTION_H_
#define _ARC_HAL_EXCEPTION_H_

#include "inc/embARC_toolchain.h"
#include "inc/arc/arc.h"
#include "inc/arc/arc_builtin.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup ARC_HAL_EXCEPTION_CPU
 * @{
 * \todo need a conf.h from application or board to define the
 * features of processor, such as number of exception, code
 * density and FIQ.
 */
#ifndef NUM_EXC_CPU
#define NUM_EXC_CPU	16	/*!< number of CPU exceptions */
#endif

#ifndef NUM_EXC_INT
#define NUM_EXC_INT	9	/*!< number of interrupt exceptions, defined by users*/
#endif

#define NUM_EXC_ALL	(NUM_EXC_CPU + NUM_EXC_INT) /*!< total number of exceptions */



#ifdef ARC_FEATURE_SEC_PRESENT
typedef struct int_exc_frame {
	uint32_t erbta;

	uint32_t r30;	/* r30 is useless, skipped? */
	uint32_t ilink;	/* r29 is useless, skipped?*/
	/* r28 is sp, saved other place */
	uint32_t fp;	/* r27 */
	uint32_t gp;	/* r26 */

	uint32_t r12;

	uint32_t lp_end, lp_start, lp_count;

#ifdef ARC_FEATURE_CODE_DENSITY
	uint32_t ei, ldi, jli;
#endif

	uint32_t r0, r1, r2, r3;
#ifndef ARC_FEATURE_RF16
	uint32_t r4, r5, r6, r7, r8, r9;
#endif
	uint32_t r10, r11;

	uint32_t blink;	/* r31 */
	uint32_t ret;
	uint32_t sec_stat;
	uint32_t status32;
} EMBARC_PACKED INT_EXC_FRAME;
#else
typedef struct int_exc_frame {
	uint32_t erbta;

	uint32_t r30;	/* r30 is useless, skipped? */
	uint32_t ilink;	/* r29 is useless, skipped?*/
	/* r28 is sp, saved other place */
	uint32_t fp;	/* r27 */
	uint32_t gp;	/* r26 */

	uint32_t r12;

	uint32_t r0, r1, r2, r3;
#ifndef ARC_FEATURE_RF16
	uint32_t r4, r5, r6, r7, r8, r9;
#endif
	uint32_t r10, r11;

	uint32_t blink;	/* r31 */

	uint32_t lp_end, lp_start, lp_count;

#ifdef ARC_FEATURE_CODE_DENSITY
	uint32_t ei, ldi, jli;
#endif

	uint32_t ret;
	uint32_t status32;
} EMBARC_PACKED INT_EXC_FRAME;
#endif

typedef struct callee_frame {
#ifndef ARC_FEATURE_RF16
	uint32_t r25;
	uint32_t r24;
	uint32_t r23;
	uint32_t r22;
	uint32_t r21;
	uint32_t r20;
	uint32_t r19;
	uint32_t r18;
	uint32_t r17;
	uint32_t r16;
#endif
	uint32_t r15;
	uint32_t r14;
	uint32_t r13;
} EMBARC_PACKED CALLEE_FRAME;

typedef struct processor_frame {
	CALLEE_FRAME callee_regs;
	INT_EXC_FRAME exc_frame;
} EMBARC_PACKED PROCESSOR_FRAME;

#define ARC_PROCESSOR_FRAME_SIZE	(sizeof(PROCESSOR_FRAME) / sizeof(uint32_t))
#define ARC_EXC_FRAME_SIZE		(sizeof(INT_EXC_FRAME) / sizeof(uint32_t))
#define ARC_CALLEE_FRAME_SIZE		(sizeof(CALLEE_FRAME) / sizeof(uint32_t))


extern uint32_t exc_nest_count;

/**
 * \brief write the exception vector base
 *
 * \param[in] vec_base the target vector base
 */
Inline void arc_vector_base_write(const void * vec_base)
{
	_arc_aux_write(AUX_INT_VECT_BASE, (uint32_t)vec_base);
}

/**
 * \brief read current exception vector base
 *
 * \returns exception vector base (uint32_t)
 */
Inline uint32_t arc_vector_base_read(void)
{
	return _arc_aux_read(AUX_INT_VECT_BASE);
}

/**
 * \brief  sense whether in exc/interrupt processing
 *
 * \retval 0	not in exc/interrupt processing
 * \retval 1	in exc/interrupt processing
 */
Inline uint32_t exc_sense(void)
{
	return (exc_nest_count > 0U);
}

/** @}*/

/**
 * \addtogroup ARC_HAL_EXCEPTION_INTERRUPT
 * @{
 */
#ifndef INT_PRI_MIN
#define INT_PRI_MIN	(-2)		/*!< the minimum interrupt priority */
#endif

#define INT_PRI_MAX (-1)		/*!< the maximum interrupt priority */
/**
 * \brief disable the specific interrupt
 *
 * \param[in] intno interrupt number
 */
Inline void arc_int_disable(const uint32_t intno)
{
	_arc_aux_write(AUX_IRQ_SELECT, intno);
	_arc_aux_write(AUX_IRQ_ENABLE, 0);
}

/**
 * \brief  enable the specific int
 *
 * \param[in] intno interrupt number
 */
Inline void arc_int_enable(const uint32_t intno)
{
	_arc_aux_write(AUX_IRQ_SELECT, intno);
	_arc_aux_write(AUX_IRQ_ENABLE, 1);
}

/**
 * \brief  check whether the specific int is enabled
 *
 * \param[in] intno interrupt number
 * \return 0 disabled, 1 enabled
 */
Inline uint32_t arc_int_enabled(const uint32_t intno)
{
	_arc_aux_write(AUX_IRQ_SELECT, intno);
	return _arc_aux_read(AUX_IRQ_ENABLE);
}

/**
 * \brief  get the interrupt priority mask
 *
 * \returns interrupt priority mask, negative num
 */
Inline uint32_t arc_int_ipm_get(void)
{
	return ((_arc_aux_read(AUX_STATUS32) >> 1) & 0x0f);
}

/**
 * \brief  set the interrupt priority mask
 *
 * \param[in] intpri interrupt priority
 */
Inline void arc_int_ipm_set(uint32_t intpri)
{
	volatile uint32_t status;
	status = _arc_aux_read(AUX_STATUS32) & ~0x1e;

	status = status | ((intpri << 1) & 0x1e);
	/* sr cannot write AUX_STATUS32 */
	Asm("kflag %0"::"ir"(status));
}

/**
 * \brief  get current interrupt priority mask
 *
 * \param[in] intno interrupt number
 */
Inline uint32_t arc_int_pri_get(const uint32_t intno)
{
	_arc_aux_write(AUX_IRQ_SELECT, intno);
	return _arc_aux_read(AUX_IRQ_PRIORITY);
}

/**
 * \brief set interrupt priority
 *
 * \param[in] intno interrupt number
 * \param[in] intpri interrupt priority
 */
Inline void arc_int_pri_set(const uint32_t intno, uint32_t intpri)
{
	_arc_aux_write(AUX_IRQ_SELECT, intno);
	_arc_aux_write(AUX_IRQ_PRIORITY, intpri | (_arc_aux_read(AUX_IRQ_PRIORITY) & 0xfffffff0));
}

/**
 * \brief set interrupt secure or not secure
 *
 * \param[in] intno interrupt number
 * \param[in] secure, 0 for normal, >0 for secure
 */
Inline void arc_int_secure_set(const uint32_t intno, uint32_t secure)
{

	_arc_aux_write(AUX_IRQ_SELECT, intno);

	if (secure) {
		_arc_aux_write(AUX_IRQ_PRIORITY, _arc_aux_read(AUX_IRQ_PRIORITY) |
			(1 << AUX_IRQ_PRIORITY_BIT_S));
	} else {
		_arc_aux_write(AUX_IRQ_PRIORITY, _arc_aux_read(AUX_IRQ_PRIORITY) & 0xf);
	}

}

/**
 * \brief  probe the pending status of interrupt
 *
 * \param[in] intno interrupt number
 *
 * \returns 1 pending, 0 no pending
 */
Inline uint32_t arc_int_probe(const uint32_t intno)
{
	_arc_aux_write(AUX_IRQ_SELECT, intno);
	return _arc_aux_read(AUX_IRQ_PENDING);
}

/**
 * \brief  trigger the interrupt in software
 *
 * \param[in] intno interrupt number
 */
Inline void arc_int_sw_trigger(const uint32_t intno)
{
	_arc_aux_write(AUX_IRQ_HINT, intno);
}

/**
 * \brief  config the interrupt level triggered or pulse triggered
 *
 * \param[in] intno interrupt number
 * \param[in] level, 0-level trigger, 1-pluse triggered
 */
Inline void arc_int_level_config(const uint32_t intno, const uint32_t level)
{
	_arc_aux_write(AUX_IRQ_SELECT, intno);
	_arc_aux_write(AUX_IRQ_TRIGGER, level);
}

/**
 * \brief  lock cpu, disable interrupts
 */
Inline void arc_lock(void)
{
	Asm("clri");
	Asm("":::"memory");
}

/**
 * \brief  unlock cpu, enable interrupts to happen
 */
Inline void arc_unlock(void)
{
	Asm("":::"memory");
	Asm("seti");
}

/**
 * \brief  lock cpu and staus
 *
 * \returns cpu status
 */
Inline uint32_t arc_lock_save(void)
{
	return _arc_clri();
}

/**
 * \brief  unlock cpu with the specific status
 *
 * \param[in] status  cpu status saved by cpu_lock_save
 */
Inline void arc_unlock_restore(const uint32_t status)
{
	_arc_seti(status);
}
/** @}*/

/**
 * \addtogroup ARC_HAL_EXCEPTION_CPU
 * @{
 */
/**
 * \typedef EXC_ENTRY
 * \brief  the data type for exception entry
 */
typedef void (*EXC_ENTRY) (void);
/**
 * \typedef EXC_HANDLER
 * \brief  the data type for exception handler
 */
typedef	void (*EXC_HANDLER) (void *exc_frame);
/** @}*/


/**
 * \ingroup ARC_HAL_EXCEPTION_INTERRUPT
 * \typedef INT_HANDLER
 * \brief  the data type for interrupt handler
 */
typedef void (*INT_HANDLER) (void *ptr);

extern EXC_ENTRY exc_entry_table[NUM_EXC_ALL];
extern EXC_HANDLER exc_int_handler_table[NUM_EXC_ALL];

/** \ingroup ARC_HAL_EXCEPTION_CPU
 * @{
 */
/**
 * \fn _arc_reset
 * \brief the reset entry
 */
extern void _arc_reset(void);
/**
 * \fn exc_entry_cpu
 * \brief the default CPU exception entry
 */
extern void exc_entry_cpu(void);

/**
 * \fn exc_entry_firq
 * \brief the fast interrupt exception entry
 */
extern void exc_entry_firq(void);
/**
 * \fn exc_entry_int
 * \brief the interrupt exception entry
 */
extern void exc_entry_int(void);
/** @}*/

/* excetpion related apis */
extern void exc_int_init(void);
extern int32_t exc_entry_install(const uint32_t excno, EXC_ENTRY entry);
extern EXC_ENTRY exc_entry_get(const uint32_t excno);
extern int32_t exc_handler_install(const uint32_t excno, EXC_HANDLER handler);
extern EXC_HANDLER exc_handler_get(const uint32_t excno);

/* interrupt related apis */
extern int32_t int_disable(const uint32_t intno);
extern int32_t int_enable(const uint32_t intno);
extern int32_t int_enabled(const uint32_t intno);
extern int32_t int_ipm_get(void);
extern int32_t int_ipm_set(int32_t intpri);
extern int32_t int_pri_get(const uint32_t intno);
extern int32_t int_pri_set(const uint32_t intno, int32_t intpri);
extern int32_t int_probe(const uint32_t intno);
extern int32_t int_sw_trigger(const uint32_t intno);
extern int32_t int_level_config(const uint32_t intno, const uint32_t level);
extern void cpu_lock(void);
extern void cpu_unlock(void);
extern uint32_t cpu_lock_save(void);
extern void cpu_unlock_restore(const uint32_t status);
extern int32_t int_handler_install(const uint32_t intno, INT_HANDLER handler);
extern INT_HANDLER int_handler_get(const uint32_t intno);
extern int32_t int_secure_set(const uint32_t intno, uint32_t secure);

#ifdef __cplusplus
}
#endif

#endif /* _ARC_HAL_EXCEPTION_H_*/
