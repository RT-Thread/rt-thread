#ifndef __PLAT_HAL_H_
#define __PLAT_HAL_H_

#include "inttypes.h"


/********************************
 * 	INTC HAL DEFINE
 ********************************/

#define IRQ_EDGE_TRIGGER	1
#define IRQ_LEVEL_TRIGGER	0

#define IRQ_ACTIVE_HIGH		1
#define IRQ_ACTIVE_LOW		0

void hal_intc_init();
void hal_intc_swi_enable();
void hal_intc_swi_disable();
void hal_intc_swi_clean();
void hal_intc_swi_trigger();

/* Call by HISR.
 * Since our mask/unmask are not atomic. 
 * And HISR is task level ISR in RTOS, we need make sure it is atomic. 
 *
 * TODO remove gie if atomic 
 */
#define HAL_INTC_IRQ_ATOMIC_DISABLE(_irq_) \
		do \
		{ \
			unsigned long _gie_; \
			GIE_SAVE(&_gie_); \
			hal_intc_irq_disable(_irq_); \
			GIE_RESTORE(_gie_); \
		} while(0)

#define HAL_INTC_IRQ_ATOMIC_ENABLE(_irq_) \
		do \
		{ \
			unsigned long _gie_; \
			GIE_SAVE(&_gie_); \
			hal_intc_irq_enable(_irq_); \
			GIE_RESTORE(_gie_); \
		} while(0)


uint32_t hal_intc_irq_mask(int _irqs_);
void     hal_intc_irq_unmask(int _irqs_);
void     hal_intc_irq_clean(int _irqs_);
void     hal_intc_irq_clean_all();
void     hal_intc_irq_enable(uint32_t _irqs_);
void     hal_intc_irq_disable(uint32_t _irqs_);
void     hal_intc_irq_disable_all();
void     hal_intc_irq_set_priority(uint32_t _prio_ );
void     hal_intc_irq_config(uint32_t _irqs_, uint32_t _edge_, uint32_t _falling_);
uint32_t hal_intc_get_all_pend();

/********************************
 * 	TIMER HAL DEFINE	
 ********************************/

uint32_t hal_timer_irq_mask(uint32_t _tmr_ );
void     hal_timer_irq_unmask(uint32_t _msk_ );
void     hal_timer_irq_clear(uint32_t _tmr_ );
void     hal_timer_start(uint32_t _tmr_);
void     hal_timer_stop(uint32_t _tmr_ );
uint32_t hal_timer_read(uint32_t _tmr_ );
void     hal_timer_set_period(uint32_t _tmr_, uint32_t _period_ );
void     hal_timer_set_upward(uint32_t _tmr_ ,uint32_t up);
void     hal_timer_init(uint32_t _tmr_ );
void     hal_timer_irq_control(uint32_t _tmr_, uint32_t enable );
uint32_t hal_timer_irq_status(uint32_t _tmr_);
void     hal_timer_set_match1(uint32_t _tmr_ , uint32_t match );
uint32_t hal_timer_count_read(uint32_t _tmr_);

#endif
