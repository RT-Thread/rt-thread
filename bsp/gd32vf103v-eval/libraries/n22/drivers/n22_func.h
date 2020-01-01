// See LICENSE file for licence details

#ifndef N22_FUNC_H
#define N22_FUNC_H


#include "n22_tmr.h"
#include "n22_eclic.h"

#define	ECLIC_GROUP_LEVEL0_PRIO4	0
#define	ECLIC_GROUP_LEVEL1_PRIO3	1
#define	ECLIC_GROUP_LEVEL2_PRIO2	2
#define	ECLIC_GROUP_LEVEL3_PRIO1	3
#define	ECLIC_GROUP_LEVEL4_PRIO0	4

void switch_m2u_mode();
uint32_t get_tmr_freq();
uint32_t mtime_lo(void);
uint32_t mtime_hi(void);
uint64_t get_timer_value();
uint64_t get_instret_value();
uint64_t get_cycle_value();

void eclic_init(uint32_t num_irq);

void eclic_enable_interrupt(uint32_t source);
void eclic_disable_interrupt(uint32_t source);

void eclic_set_pending(uint32_t source);
void eclic_clear_pending(uint32_t source);

void eclic_set_intctrl(uint32_t source, uint8_t intctrl);
uint8_t eclic_get_intctrl(uint32_t source);

void eclic_set_intattr(uint32_t source, uint8_t intattr);
uint8_t eclic_get_intattr(uint32_t source);

void eclic_set_ecliccfg(uint8_t ecliccfg);
uint8_t eclic_get_ecliccfg();

void eclic_set_mth(uint8_t mth);
uint8_t eclic_get_mth();

void eclic_set_nlbits(uint8_t nlbits);
uint8_t eclic_get_nlbits();

uint8_t eclic_set_int_level(uint32_t source, uint8_t level);
uint8_t eclic_get_int_level(uint32_t source);

uint8_t eclic_set_int_priority(uint32_t source, uint8_t priority);
uint8_t eclic_get_int_priority(uint32_t source);

void eclic_mode_enable();
void eclic_set_shv(uint32_t source, uint8_t shv);
void eclic_set_trig(uint32_t source, uint8_t trig);

///** \brief  Wait For Interrupt
//
//    Wait For Interrupt is a hint instruction that suspends execution
//    until one of a number of events occurs.
// */
__attribute__( ( always_inline ) ) static inline void __WFI(void) {
	__asm volatile ("wfi");
}
//
//
/** \brief  Wait For Event

    Wait For Event is a hint instruction that permits the processor to enter
    a low-power state until one of a number of events occurs.
 */
__attribute__( ( always_inline ) ) static inline  void __WFE(void)
{
  __asm volatile ("wfi");
}

void close_timer(void);
void open_timer(void);
void enable_timer_interrupt(void);
void clear_timer_interrupt(void);

#endif
