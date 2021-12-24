/*
File Name    : board_config.h
Author       : Yichip
Version      : V1.0
Date         : 2020/07/17
Description  : misc file.
*/

#ifndef __MISC_H
#define __MISC_H
#include "yc3121.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    SVCall_IRQn		= -5, //SVC_IRQHandler
    PendSV_IRQn		= -2, //PENDSV_IRQHandler
    SysTick_IRQn	= -1, //SYSTICK_IRQHandler
    USB_IRQn   		= 0,
    IIC_IRQn   		= 1,
    QSPI_IRQn  		= 2,
    SPI0_IRQn  		= 3,
    SPI1_IRQn  		= 4,
    UART0_IRQn 		= 5,
    UART1_IRQn 		= 6,
    MEMCP_IRQn 		= 7,//DMA MEM_TO_MEM
    RSA_IRQn   		= 8,
    SCI0_IRQn  		= 9,
    SCI1_IRQn  		= 10,
    BT_IRQn    		= 11,
    GPIO_IRQn  		= 12,
    TIM0_IRQn  		= 13,
    TIM1_IRQn  		= 14,
    TIM2_IRQn  		= 15,
    TIM3_IRQn  		= 16,
    TIM4_IRQn  		= 17,
    TIM5_IRQn  		= 18,
    TIM6_IRQn  		= 19,
    TIM7_IRQn  		= 20,
    TIM8_IRQn  		= 21,
    SM4_IRQn   		= 22,
    SEC_IRQn   		= 23,
    MSR_IRQn   		= 24,
    TRNG_IRQn  		= 25,
    WDT_IRQn   		= 26
} IRQn_Type;

/**
  * @brief  Enable External Interrupt
  * @param  IRQnx IRQn External interrupt number. Value cannot be negative.
  * @retval none
  */
void	NVIC_EnableIRQ(IRQn_Type IRQnx);

/**
  * @brief  Disable External Interrupt
  * @param  IRQnx IRQn External interrupt number. Value cannot be negative.
  * @retval none
  */
void NVIC_DisableIRQ(IRQn_Type IRQnx);

/**
 * @brief  Set  Interrupt Priority
 * @param  IRQn  Interrupt number.
 * @retval SUCCESS or ERROR
 */
uint32_t NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority);


/**
 * @brief  trigger PendSV Interrupt
 * @param  none
 * @retval none
 */
void trigger_PendSV(void);

/**
 * @brief  System Reset
 * @param  none
 * @retval none
 */
void soft_reset(void);


#ifdef __cplusplus
}
#endif

#endif /* __MISC_H */

