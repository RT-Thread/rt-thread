/***************COPYRIGHT(C)  2019 WCH. A11 rights reserved*********************
* File Name          : ch32f10x_system.h
* Author             : WCH
* Version            : V1.0.0
* Date               : 2019/10/15
* Description        : CMSIS Cortex-M3 Device Peripheral Access Layer System Header File. 
*******************************************************************************/
#ifndef __SYSTEM_CH32F10X_H
#define __SYSTEM_CH32F10X_H

#ifdef __cplusplus
 extern "C" {
#endif 


extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */


/* CH32F10x_System_Exported_Functions */  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);


#ifdef __cplusplus
}
#endif

#endif /*__CH32F10x_SYSTEM_H */





