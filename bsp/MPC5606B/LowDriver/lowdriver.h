#ifndef LOWDRIVER_H
#define LOWDRIVER_H

#include <MPC5606B.h>

#ifndef NULL
#define NULL 0
#endif

#ifndef __weak
    #define __weak __attribute__((weak))
#endif

static inline
void irqIsrEnable(void)
{
	__asm__("wrteei  1");

}

/**
 * @brief   Globally disables interrupts.
 *
 * @special
 */
static inline
void irqIsrDisable(void)
{

	__asm__("wrteei  0");
}
#endif // LOWDRIVER_H
