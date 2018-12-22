/**
	*****************************************************************************
	* @file     cmem7_it.h
	*
	* @brief    CMEM7 system exception interrupt header file
	*
	*
	* @version  V1.0
	* @date     3. September 2013
	*
	* @note     Actually, you don't have to implement below involved function 
	*           whick were defined as weak dummy functions in startup file.
	*           
	*****************************************************************************
	* @attention
	*
	* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
	* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
	* TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT, 
	* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
	* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
	* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
	*
	* <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
	*****************************************************************************
	*/

#ifndef __CMEM7_IT_H
#define __CMEM7_IT_H

#include "cmem7.h"

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void);

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void);

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void);

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void);

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void);

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void);

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void);

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void);

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void);

/**
  * @brief  This function handles ethernet interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void ETH_IRQHandler(void);

/**
  * @brief  This function handles USB interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void USB_IRQHandler(void);

/**
  * @brief  This function handles DMA interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void DMAC_IRQHandler(void);

/**
  * @brief  This function handles CAN0 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void CAN0_IRQHandler(void); 

/**
  * @brief  This function handles CAN1 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void CAN1_IRQHandler(void); 

/**
  * @brief  This function handles FP0 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void FP0_IRQHandler(void);  

/**
  * @brief  This function handles FP1 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void FP1_IRQHandler(void);          

/**
  * @brief  This function handles FP2 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void FP2_IRQHandler(void);          		

/**
  * @brief  This function handles FP3 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void FP3_IRQHandler(void); 

/**
  * @brief  This function handles FP4 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void FP4_IRQHandler(void); 

/**
  * @brief  This function handles FP5 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void FP5_IRQHandler(void); 

/**
  * @brief  This function handles FP6 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void FP6_IRQHandler(void);

/**
  * @brief  This function handles FP7 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void FP7_IRQHandler(void);

/**
  * @brief  This function handles FP8 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void FP8_IRQHandler(void);

/**
  * @brief  This function handles FP9 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void FP9_IRQHandler(void);

/**
  * @brief  This function handles FP10 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void FP10_IRQHandler(void);

/**
  * @brief  This function handles FP11 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void FP11_IRQHandler(void);

/**
  * @brief  This function handles FP12 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void FP12_IRQHandler(void);

/**
  * @brief  This function handles FP13 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void FP13_IRQHandler(void);

/**
  * @brief  This function handles FP14 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void FP14_IRQHandler(void);

/**
  * @brief  This function handles FP15 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void FP15_IRQHandler(void); 

/**
  * @brief  This function handles UART0 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void UART0_IRQHandler(void);

/**
  * @brief  This function handles UART1 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void UART1_IRQHandler(void);

/**
  * @brief  This function handles ADC interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void ADC_IRQHandler(void); 

/**
  * @brief  This function handles GPIO interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void GPIO_IRQHandler(void);

/**
  * @brief  This function handles SPI1 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void SPI1_IRQHandler(void);

/**
  * @brief  This function handles I2C1 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void I2C1_IRQHandler(void);

/**
  * @brief  This function handles SPI0 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void SPI0_IRQHandler(void);

/**
  * @brief  This function handles I2C0 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void I2C0_IRQHandler(void);

/**
  * @brief  This function handles RTC second interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void RTC_1S_IRQHandler(void); 

/**
  * @brief  This function handles RTC microsecond interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void RTC_1MS_IRQHandler(void);

/**
  * @brief  This function handles watchdog interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void WDG_IRQHandler(void); 

/**
  * @brief  This function handles timer interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void TIMER_IRQHandler(void); 

/**
  * @brief  This function handles DDR interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void DDRC_SW_PROC_IRQHandler(void); 

/**
  * @brief  This function handles ethernet pmt interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void ETH_PMT_IRQHandler(void); 

/**
  * @brief  This function handles pad interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void PAD_IRQHandler(void);

/**
  * @brief  This function handles DDR interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void DDRC_LANE_SYNC_IRQHandler(void); 

/**
  * @brief  This function handles UART2 interrupt.
  * @param  None
  * @retval None
	* @note   Implement it in your interrupt handler
  */
void UART2_IRQHandler(void);            

#endif /* __CMEM7_IT_H */

