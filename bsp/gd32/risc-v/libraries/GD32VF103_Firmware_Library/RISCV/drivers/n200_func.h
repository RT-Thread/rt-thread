/* See LICENSE file for licence details */

#ifndef N200_FUNC_H
#define N200_FUNC_H


#include <stddef.h>
#include "n200_timer.h"
#include "n200_eclic.h"

#define ECLIC_GROUP_LEVEL0_PRIO4        0
#define ECLIC_GROUP_LEVEL1_PRIO3        1
#define ECLIC_GROUP_LEVEL2_PRIO2        2
#define ECLIC_GROUP_LEVEL3_PRIO1        3
#define ECLIC_GROUP_LEVEL4_PRIO0        4

void pmp_open_all_space(void);

void switch_m2u_mode(void);

uint32_t get_mtime_freq(void);

uint32_t mtime_lo(void);

uint32_t mtime_hi(void);

uint64_t get_mtime_value(void);

uint64_t get_instret_value(void);

uint64_t get_cycle_value(void);

uint32_t get_cpu_freq(void);

uint32_t __attribute__((noinline)) measure_cpu_freq(size_t n);

/* ECLIC relevant functions */
void eclic_init ( uint32_t num_irq );
uint64_t get_timer_value(void);
void eclic_enable_interrupt (uint32_t source);
void eclic_disable_interrupt (uint32_t source);

void eclic_set_pending(uint32_t source);
void eclic_clear_pending(uint32_t source);

void eclic_set_intctrl (uint32_t source, uint8_t intctrl);
uint8_t eclic_get_intctrl  (uint32_t source);

void eclic_set_intattr (uint32_t source, uint8_t intattr);
uint8_t eclic_get_intattr  (uint32_t source);

void eclic_set_cliccfg (uint8_t cliccfg);
uint8_t eclic_get_cliccfg (void);

void eclic_set_mth (uint8_t mth);
uint8_t eclic_get_mth(void);

/* sets nlbits */
void eclic_set_nlbits(uint8_t nlbits);


/* get nlbits */
uint8_t eclic_get_nlbits(void);

void eclic_set_irq_lvl(uint32_t source, uint8_t lvl);
uint8_t eclic_get_irq_lvl(uint32_t source);

void eclic_set_irq_lvl_abs(uint32_t source, uint8_t lvl_abs);
uint8_t eclic_get_irq_lvl_abs(uint32_t source);

uint8_t eclic_set_irq_priority(uint32_t source, uint8_t priority);
uint8_t eclic_get_irq_priority(uint32_t source);

void eclic_mode_enable(void);

void eclic_set_vmode(uint32_t source);
void eclic_set_nonvmode(uint32_t source);

void eclic_set_level_trig(uint32_t source);
void eclic_set_posedge_trig(uint32_t source);
void eclic_set_negedge_trig(uint32_t source);


/** \brief  Wait For Interrupt

    Wait For Interrupt is a hint instruction that suspends execution
    until one of a number of events occurs.
 */
__attribute__( ( always_inline ) ) static inline void __WFI(void) {
    __asm volatile ("wfi");
}

/** \brief  Wait For Event

    Wait For Event is a hint instruction that permits the processor to enter
    a low-power state until one of a number of events occurs.
 */
__attribute__( ( always_inline ) ) static inline  void __WFE(void) {
    __asm volatile ("csrs 0x810, 0x1");
    __asm volatile ("wfi");
    __asm volatile ("csrc 0x810, 0x1");
}


#endif
