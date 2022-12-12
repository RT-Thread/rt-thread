/********************************** (C) COPYRIGHT *******************************
* File Name          : system_ch32f20x.h
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/08/08
* Description        : CH32F20x Device Peripheral Access Layer System Header File.
*******************************************************************************/
#ifndef __SYSTEM_CH32F20x_H
#define __SYSTEM_CH32F20x_H

#ifdef __cplusplus
 extern "C" {
#endif 

extern uint32_t SystemCoreClock;          /* System Clock Frequency (Core Clock) */

/* System_Exported_Functions */  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /*__CH32F20x_SYSTEM_H */



