/*!
 * @file        system_apm32f10x.h
 *
 * @brief       CMSIS Cortex-M3 Device Peripheral Access Layer System Source File
 *
 * @version     V1.0.1
 *
 * @date        2021-03-23
 *
 */

#ifndef __SYSTEM_APM32F10X_H
#define __SYSTEM_APM32F10X_H

#ifdef __cplusplus
 extern "C" {
#endif

extern uint32_t SystemCoreClock;

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_APM32F10X_H */

