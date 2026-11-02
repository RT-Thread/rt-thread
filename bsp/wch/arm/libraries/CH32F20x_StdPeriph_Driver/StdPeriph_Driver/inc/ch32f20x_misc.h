/********************************** (C) COPYRIGHT  *******************************
* File Name          : ch32f20x_misc.h
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/08/08
* Description        : This file contains all the functions prototypes for the 
*                      miscellaneous firmware library functions.
*******************************************************************************/   
#ifndef __CH32F20x_MISC_H
#define __CH32F20x_MISC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "ch32f20x.h"

/* NVIC Init Structure definition */	 
typedef struct
{
  uint8_t NVIC_IRQChannel;                    /* Specifies the IRQ channel to be enabled or disabled.
                                                 This parameter can be a value of @ref IRQn_Type 
                                                 (For the complete CH32 Devices IRQ Channels list, please
                                                  refer to ch32f10x.h file) */

  uint8_t NVIC_IRQChannelPreemptionPriority;  /* Specifies the pre-emption priority for the IRQ channel
                                                 specified in NVIC_IRQChannel. This parameter can be a value
                                                 between 0 and 15 as described in the table @ref NVIC_Priority_Table */

  uint8_t NVIC_IRQChannelSubPriority;         /* Specifies the subpriority level for the IRQ channel specified
                                                 in NVIC_IRQChannel. This parameter can be a value
                                                 between 0 and 15 as described in the table @ref NVIC_Priority_Table */

  FunctionalState NVIC_IRQChannelCmd;         /* Specifies whether the IRQ channel defined in NVIC_IRQChannel
                                                 will be enabled or disabled. 
                                                 This parameter can be set either to ENABLE or DISABLE */   
} NVIC_InitTypeDef;
 

/* Vector_Table_Base */
#define NVIC_VectTab_RAM               ((uint32_t)0x20000000)
#define NVIC_VectTab_FLASH             ((uint32_t)0x08000000)

/* System_Low_Power */
#define NVIC_LP_SEVONPEND              ((uint8_t)0x10)
#define NVIC_LP_SLEEPDEEP              ((uint8_t)0x04)
#define NVIC_LP_SLEEPONEXIT            ((uint8_t)0x02)


/* Preemption_Priority_Group */
#define NVIC_PriorityGroup_0           ((uint32_t)0x700) /* 0 bits for pre-emption priority
                                                            4 bits for subpriority */
#define NVIC_PriorityGroup_1           ((uint32_t)0x600) /* 1 bits for pre-emption priority
                                                            3 bits for subpriority */
#define NVIC_PriorityGroup_2           ((uint32_t)0x500) /* 2 bits for pre-emption priority
                                                            2 bits for subpriority */
#define NVIC_PriorityGroup_3           ((uint32_t)0x400) /* 3 bits for pre-emption priority
                                                            1 bits for subpriority */
#define NVIC_PriorityGroup_4           ((uint32_t)0x300) /* 4 bits for pre-emption priority
                                                            0 bits for subpriority */

/* SysTick_clock_source */
#define SysTick_CLKSource_HCLK_Div8    ((uint32_t)0xFFFFFFFB)
#define SysTick_CLKSource_HCLK         ((uint32_t)0x00000004)


void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState);
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);

#ifdef __cplusplus
}
#endif

#endif 

