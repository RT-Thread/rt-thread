#ifndef LIBOS_OS_H__
#define LIBOS_OS_H__

#include <rtdef.h>
#include <rthw.h>
#include <cpuport.h>

// typedef rt_sem_t OS_Semaphore_t;

#define isb() rt_hw_isb()
#define dsb(v) rt_hw_dsb()

#define ENTER_CRITICAL(flag)    rt_hw_interrupt_disable()
#define EXIT_CRITICAL(flag)     rt_hw_interrupt_enable(flag)

int32_t esCFG_GetKeyValue(char *SecName, char *KeyName, int32_t Value[], int32_t Count);
int32_t esCFG_GetGPIOSecKeyCount(char *GPIOSecName);
int32_t esCFG_GetGPIOSecData(char *GPIOSecName, void *pGPIOCfg, int32_t GPIONum);

#endif
