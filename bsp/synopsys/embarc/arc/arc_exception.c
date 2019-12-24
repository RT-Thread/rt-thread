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
 * \brief C Implementation of exception and interrupt management
 */
#include "inc/arc/arc_exception.h"
#include "inc/arc/arc_cache.h"

//#define	 DBG_LESS
//#include "embARC_debug.h"

/**
 * \addtogroup ARC_HAL_EXCEPTION_CPU
 * @{
 * \var exc_entry_table
 * \brief exception entry table
 *
 * install exception entry table to ARC_AUX_INT_VECT_BASE in startup.
 * According to ARCv2 ISA, vectors are fetched in instruction space and thus
 * may be present in ICCM, Instruction Cache, or
 * main memory accessed by instruction fetch logic.
 * So it is put into a specific section .vector.
 *
 * Please note that the exc_entry_table maybe cached in ARC. Some functions is
 * defined in .s files.
 *
 */

/**
 * \ingroup ARC_HAL_EXCEPTION_CPU
 * \brief  default cpu exception handler
 * \param p_excinf pointer to the exception frame
 */
static void exc_handler_default(void *p_excinf)
{
	// uint32_t excpt_cause_reg = 0;
	// uint32_t excpt_ret_reg = 0;
	// uint32_t exc_no = 0;

	// excpt_cause_reg = _arc_aux_read(AUX_ECR);
	// excpt_ret_reg = _arc_aux_read(AUX_ERRET);
	// exc_no = (excpt_cause_reg >> 16) & 0xff;

	Asm("kflag 1");
}


/**
 * \ingroup ARC_HAL_EXCEPTION_INTERRUPT
 * \brief  default interrupt handler
 * \param[in] p_excinf	information for interrupt handler
 */
static void int_handler_default(void *p_excinf)
{
	// uint32_t int_cause_reg = 0;

	// int_cause_reg = _arc_aux_read(AUX_IRQ_CAUSE);
	Asm("kflag 1");
}

__attribute__ ((aligned(1024), section(".vector")))
EXC_ENTRY exc_entry_table[NUM_EXC_ALL] = {
 	[0] = _arc_reset,
 	[1 ... NUM_EXC_CPU-1] = exc_entry_cpu,
	[NUM_EXC_CPU ... NUM_EXC_ALL-1] = exc_entry_int
 };
/**
 * \var exc_int_handler_table
 * \brief the cpu exception and interrupt exception handler table
 * called in exc_entry_default and exc_entry_int
 */
EXC_HANDLER exc_int_handler_table[NUM_EXC_ALL] = {
	 [0 ... NUM_EXC_CPU-1] = exc_handler_default,
	 [NUM_EXC_CPU ... NUM_EXC_ALL-1] = int_handler_default
};

/**
 * \var exc_nest_count
 * \brief the counter for exc/int processing, =0 no int/exc
 * >1 in int/exc processing
 * @}
 */
uint32_t exc_nest_count;

typedef struct aux_irq_ctrl_field {
	/* note: little endian */
	uint32_t save_nr_gpr_pairs: 5;	/** Indicates number of general-purpose register pairs saved, from 0 to 8/16 */
	uint32_t res: 4;		/** Reserved */
	uint32_t save_blink: 1;		/** Indicates whether to save and restore BLINK */
	uint32_t save_lp_regs: 1;	/** Indicates whether to save and restore loop registers (LP_COUNT, LP_START, LP_END) */
	uint32_t save_u_to_u: 1;	/** Indicates if user context is saved to user stack */
	uint32_t res2: 1;		/** Reserved */
	uint32_t save_idx_regs: 1;	/** Indicates whether to save and restore code-density registers (EI_BASE, JLI_BASE, LDI_BASE) */
	uint32_t res3: 18;		/** Reserved */
} aux_irq_ctrl_field_t;

typedef union {
	aux_irq_ctrl_field_t bits;
	uint32_t value;
} aux_irq_ctrl_t;

/**
 * \ingroup ARC_HAL_EXCEPTION_CPU ARC_HAL_EXCEPTION_INTERRUPT
 * \brief  intialize the exception and interrupt handling
 */
void exc_int_init(void)
{
	uint32_t i;
	uint32_t status;
	aux_irq_ctrl_t ictrl;

	ictrl.value = 0;

#ifndef ARC_FEATURE_RF16
	ictrl.bits.save_nr_gpr_pairs = 6;	/* r0 to r11 (r12 saved manually) */
#else
	ictrl.bits.save_nr_gpr_pairs = 3;	/* r0 to r3, r10, r11  */
#endif
	ictrl.bits.save_blink = 1;
	ictrl.bits.save_lp_regs = 1;		/* LP_COUNT, LP_START, LP_END */
	ictrl.bits.save_u_to_u = 0;		/* user ctxt saved on kernel stack */
	ictrl.bits.save_idx_regs = 1;		/* JLI, LDI, EI */

	status = arc_lock_save();
	for (i = NUM_EXC_CPU; i < NUM_EXC_ALL; i++) {
		/* interrupt level triggered, disabled, priority is the lowest */
		_arc_aux_write(AUX_IRQ_SELECT, i);
		_arc_aux_write(AUX_IRQ_ENABLE, 0);
		_arc_aux_write(AUX_IRQ_TRIGGER, 0);
#if defined(ARC_FEATURE_SEC_PRESENT) && (SECURESHIELD_VERSION < 2)
		_arc_aux_write(AUX_IRQ_PRIORITY, (1 << AUX_IRQ_PRIORITY_BIT_S)|(INT_PRI_MAX - INT_PRI_MIN));
#else
		_arc_aux_write(AUX_IRQ_PRIORITY, INT_PRI_MAX - INT_PRI_MIN);
#endif
	}
	_arc_aux_write(AUX_IRQ_CTRL, ictrl.value);

	arc_unlock_restore(status);

	/** ipm should be set after cpu unlock restore to avoid reset of the status32 value */
	arc_int_ipm_set((INT_PRI_MAX - INT_PRI_MIN));
}

/**
 * \ingroup ARC_HAL_EXCEPTION_CPU
 * \brief  install a CPU exception entry
 * \param[in] excno exception number
 * \param[in] entry the entry of exception to install
 */
int32_t exc_entry_install(const uint32_t excno, EXC_ENTRY entry)
{
	uint32_t status;

	EXC_ENTRY *table = (EXC_ENTRY *)_arc_aux_read(AUX_INT_VECT_BASE);

	if (excno < NUM_EXC_ALL && entry != NULL
		&& table[excno] != entry) {
		status = cpu_lock_save();
		/* directly write to mem, as arc gets exception handler from mem not from cache */
		/* FIXME, here maybe icache is dirty, need to be invalidated */
		table[excno] = entry;

		if (_arc_aux_read(AUX_BCR_D_CACHE) > 0x2) {
		/* dcache is available */
			dcache_flush_line((uint32_t)&table[excno]);
		}

		if (_arc_aux_read(AUX_BCR_D_CACHE) > 0x2) {
		/* icache is available */
			icache_invalidate_line((uint32_t)&table[excno]);
		}
		cpu_unlock_restore(status);
		return 0;
	}
	return -1;
}

/**
 * \ingroup ARC_HAL_EXCEPTION_CPU
 * \brief  get the installed CPU exception entry
 * \param[in] excno exception number
 * \return the installed CPU exception entry
 */
EXC_ENTRY exc_entry_get(const uint32_t excno)
{
	if (excno < NUM_EXC_ALL) {
		return exc_entry_table[excno];
	}
	return NULL;
}

/**
 * \ingroup ARC_HAL_EXCEPTION_CPU
 * \brief  install an exception handler
 * \param[in] excno	exception number
 * \param[in] handler the handler of exception to install
 */
int32_t exc_handler_install(const uint32_t excno, EXC_HANDLER handler)
{
	if (excno < NUM_EXC_ALL && handler != NULL) {
		exc_int_handler_table[excno] = handler;
		return 0;
	}

	return -1;
}

/**
 * \ingroup ARC_HAL_EXCEPTION_CPU
 * \brief  get the installed exception handler
 * \param[in] excno	exception number
 * \return the installed exception handler or NULL
 */
EXC_HANDLER exc_handler_get(const uint32_t excno)
{
	if (excno < NUM_EXC_ALL) {
		return exc_int_handler_table[excno];
	}

	return NULL;
}


#ifndef EMBARC_OVERRIDE_ARC_INTERRUPT_MANAGEMENT
/**
 * \brief disable the specific interrupt
 *
 * \param[in] intno interrupt number
 */
int32_t int_disable(const uint32_t intno)
{
	if (intno >= NUM_EXC_CPU && intno < NUM_EXC_ALL) {
		arc_int_disable(intno);
		return 0;
	}

	return -1;
}

/**
 * \brief  enable the specific int
 *
 * \param[in] intno interrupt number
 */
int32_t int_enable(const uint32_t intno)
{
	if (intno >= NUM_EXC_CPU && intno < NUM_EXC_ALL) {
		arc_int_enable(intno);
		return 0;
	}

	return -1;
}

/**
 * \brief  check whether the specific int is enabled
 *
 * \param[in] intno interrupt number
 * \return 0 disabled, 1 enabled, < 0 error
 */
int32_t int_enabled(const uint32_t intno)
{
	if (intno >= NUM_EXC_CPU && intno < NUM_EXC_ALL) {
		_arc_aux_write(AUX_IRQ_SELECT, intno);
		return _arc_aux_read(AUX_IRQ_ENABLE);
	}

	return -1;
}

/**
 * \brief  get the interrupt priority mask
 *
 * \returns interrupt priority mask, negative num
 */
int32_t int_ipm_get(void)
{
	return ((int32_t)arc_int_ipm_get() + INT_PRI_MIN);
}


/**
 * \brief  set the interrupt priority mask
 *
 * \param[in] intpri interrupt priority
 */
int32_t int_ipm_set(int32_t intpri)
{
	if (intpri >= INT_PRI_MIN && intpri <= INT_PRI_MAX) {
		intpri = intpri - INT_PRI_MIN;
		arc_int_ipm_set(intpri);
		return 0;
	}

	return  -1;
}


/**
 * \brief  get current interrupt priority mask
 *
 * \param[in] intno interrupt number
 * \return  <0 interrupt priority, 0 error
 */
int32_t int_pri_get(const uint32_t intno)
{
	if (intno >= NUM_EXC_CPU && intno < NUM_EXC_ALL) {
		return (int32_t)arc_int_pri_get(intno) + INT_PRI_MIN;
	}

	return 0;
}


/**
 * \brief set interrupt priority
 *
 * \param[in] intno interrupt number
 * \param[in] intpri interrupt priority
 * \return  <0 error, 0 ok
 */
int32_t int_pri_set(const uint32_t intno, int32_t intpri)
{
	uint32_t status;

	if (intno >= NUM_EXC_CPU && intno < NUM_EXC_ALL) {
		status = cpu_lock_save();
		intpri = intpri - INT_PRI_MIN;
		arc_int_pri_set(intno,(uint32_t)intpri);
		cpu_unlock_restore(status);
		return 0;
	}
	return -1;
}

/**
 * \brief set interrupt secure or not secure
 * This function is valid in secureshield v2
 * \param[in] intno interrupt number
 * \param[in] secure, 0 for normal, >0 for secure
 * \return <0 error, 0 ok
 */
int32_t int_secure_set(const uint32_t intno, uint32_t secure)
{
	if (intno >= NUM_EXC_CPU && intno < NUM_EXC_ALL) {
		arc_int_secure_set(intno, secure);
		return 0;
	}
	return -1;

}


/**
 * \brief  probe the pending status of interrupt
 *
 * \param[in] intno interrupt number
 *
 * \returns 1 pending, 0 no pending, -1 error
 */
int32_t int_probe(const uint32_t intno)
{
	if (intno >= NUM_EXC_CPU && intno < NUM_EXC_ALL) {
		return arc_int_probe(intno);
	}
	return -1;
}


/**
 * \brief  trigger the interrupt in software
 *
 * \param[in] intno interrupt number
 * \return 0 ok, -1 error
 */
int32_t int_sw_trigger(const uint32_t intno)
{
	if (intno >= NUM_EXC_CPU && intno < NUM_EXC_ALL) {
		arc_int_sw_trigger(intno);
		return 0;
	}
	return -1;
}

/**
 * \brief  config the interrupt level triggered or pulse triggered
 *
 * \param[in] intno interrupt number
 * \param[in] level, 0-level trigger, 1-pulse triggered
 * \return 0 ok, -1 error
 */
int32_t int_level_config(const uint32_t intno, const uint32_t level)
{
	if (intno >= NUM_EXC_CPU && intno < NUM_EXC_ALL) {
		arc_int_level_config(intno, level);
		return 0;
	}
	return -1;
}


/**
 * \brief  lock cpu, disable interrupts
 */
void cpu_lock(void)
{
	arc_lock();
}

/**
 * \brief  unlock cpu, enable interrupts to happen
 */
void cpu_unlock(void)
{
	arc_unlock();
}

/**
 * \brief  lock cpu and return status
 *
 * \returns cpu status
 */
uint32_t cpu_lock_save(void)
{
	return arc_lock_save();
}

/**
 * \brief  unlock cpu with the specific status
 *
 * \param[in] status  cpu status saved by cpu_lock_save
 */
void cpu_unlock_restore(const uint32_t status)
{
	arc_unlock_restore(status);
}

/**
 * \ingroup ARC_HAL_EXCEPTION_INTERRUPT
 * \brief  install an interrupt handler
 * \param[in] intno	interrupt number
 * \param[in] handler interrupt handler to install
 */
int32_t int_handler_install(const uint32_t intno, INT_HANDLER handler)
{
	/*!< \todo parameter check ? */
	if (intno >= NUM_EXC_CPU) {
		return exc_handler_install(intno, handler);
	}

	return -1;
}

/**
 * \ingroup ARC_HAL_EXCEPTION_INTERRUPT
 * \brief  get the installed an interrupt handler
 * \param[in] intno interrupt number
 * \return the installed interrupt handler or NULL
 */
INT_HANDLER int_handler_get(const uint32_t intno)
{
	if (intno >= NUM_EXC_CPU) {
		return exc_handler_get(intno);
	}

	return NULL;
}
#endif /* EMBARC_OVERRIDE_ARC_INTERRUPT_MANAGEMENT */
