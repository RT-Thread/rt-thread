
#ifndef __ARCH_MACHINE_GIC_PL400_H
#define __ARCH_MACHINE_GIC_PL400_H

#include <stdint.h>

typedef uint16_t interrupt_t;
typedef uint16_t irq_t;
typedef uint64_t  bool_t;

/** MODIFIES: [*] */
interrupt_t getActiveIRQ(void);
/** MODIFIES: [*] */
interrupt_t getPendingIRQ(void);
/** MODIFIES: [*] */
bool_t isIRQPending(void);
/** MODIFIES: [*] */
void maskInterrupt(bool_t disable, interrupt_t irq);
/** MODIFIES: [*] */
void ackInterrupt(irq_t irq);
/** MODIFIES: [*] */
static inline void setInterruptMode(irq_t irq, bool_t levelTrigger, bool_t polarityLow) { }

/** MODIFIES: [*] */
void initIRQController(void);

void handleSpuriousIRQ(void);

void rt_hw_interrupt_umask(int vector);

int rt_hw_interrupt_get_irq(void);

void rt_hw_interrupt_ack(int fiq_irq);
#endif /* !__ARCH_MACHINE_GIC400_H */

