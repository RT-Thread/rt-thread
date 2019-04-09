/**
******************************************************************************
* @file    HAL_syscfg.h
* @author  AE Team
* @version  V2.0.0
* @date  22/08/2017
* @brief   This file contains all the functions prototypes for the SYSCFG firmware 
*          library.
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT 2017 MindMotion</center></h2>
*
*/

/*!< Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_SYSCFG_H
#define __HAL_SYSCFG_H

#ifdef __cplusplus
extern "C" {
#endif
    
    /*!< Includes ------------------------------------------------------------------*/
#include "HAL_device.h"
    
    /** @addtogroup StdPeriph_Driver
    * @{
    */
    
    /** @addtogroup SYSCFG
    * @{
    */
    /* Exported types ------------------------------------------------------------*/
    /* Exported constants --------------------------------------------------------*/
    
    /** @defgroup SYSCFG_Exported_Constants
    * @{
    */ 
    
    /** @defgroup SYSCFG_EXTI_Port_Sources 
    * @{
    */ 
#define EXTI_PortSourceGPIOA       ((uint8_t)0x00)
#define EXTI_PortSourceGPIOB       ((uint8_t)0x01)
#define EXTI_PortSourceGPIOC       ((uint8_t)0x02)
#define EXTI_PortSourceGPIOD       ((uint8_t)0x03) 
#define EXTI_PortSourceGPIOE       ((uint8_t)0x04) 
#define EXTI_PortSourceGPIOF       ((uint8_t)0x05)
    
#define IS_EXTI_PORT_SOURCE(PORTSOURCE) (((PORTSOURCE) == EXTI_PortSourceGPIOA) || \
    ((PORTSOURCE) == EXTI_PortSourceGPIOB) || \
        ((PORTSOURCE) == EXTI_PortSourceGPIOC) || \
            ((PORTSOURCE) == EXTI_PortSourceGPIOD) || \
                ((PORTSOURCE) == EXTI_PortSourceGPIOE) || \
                    ((PORTSOURCE) == EXTI_PortSourceGPIOF)) 
/**
* @}
*/

/** @defgroup SYSCFG_EXTI_Pin_sources 
* @{
*/ 
#define EXTI_PinSource0            ((uint8_t)0x00)
#define EXTI_PinSource1            ((uint8_t)0x01)
#define EXTI_PinSource2            ((uint8_t)0x02)
#define EXTI_PinSource3            ((uint8_t)0x03)
#define EXTI_PinSource4            ((uint8_t)0x04)
#define EXTI_PinSource5            ((uint8_t)0x05)
#define EXTI_PinSource6            ((uint8_t)0x06)
#define EXTI_PinSource7            ((uint8_t)0x07)
#define EXTI_PinSource8            ((uint8_t)0x08)
#define EXTI_PinSource9            ((uint8_t)0x09)
#define EXTI_PinSource10           ((uint8_t)0x0A)
#define EXTI_PinSource11           ((uint8_t)0x0B)
#define EXTI_PinSource12           ((uint8_t)0x0C)
#define EXTI_PinSource13           ((uint8_t)0x0D)
#define EXTI_PinSource14           ((uint8_t)0x0E)
#define EXTI_PinSource15           ((uint8_t)0x0F)

#define IS_EXTI_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == EXTI_PinSource0) || \
((PINSOURCE) == EXTI_PinSource1) || \
    ((PINSOURCE) == EXTI_PinSource2) || \
        ((PINSOURCE) == EXTI_PinSource3) || \
            ((PINSOURCE) == EXTI_PinSource4) || \
                ((PINSOURCE) == EXTI_PinSource5) || \
                    ((PINSOURCE) == EXTI_PinSource6) || \
                        ((PINSOURCE) == EXTI_PinSource7) || \
                            ((PINSOURCE) == EXTI_PinSource8) || \
                                ((PINSOURCE) == EXTI_PinSource9) || \
                                    ((PINSOURCE) == EXTI_PinSource10) || \
                                        ((PINSOURCE) == EXTI_PinSource11) || \
                                            ((PINSOURCE) == EXTI_PinSource12) || \
                                                ((PINSOURCE) == EXTI_PinSource13) || \
                                                    ((PINSOURCE) == EXTI_PinSource14) || \
                                                        ((PINSOURCE) == EXTI_PinSource15))
/**
* @}
*/

/** @defgroup SYSCFG_Memory_Remap_Config 
* @{
*/ 
#define SYSCFG_MemoryRemap_Flash                ((uint8_t)0x00)
#define SYSCFG_MemoryRemap_SystemMemory         ((uint8_t)0x01)
#define SYSCFG_MemoryRemap_SRAM                 ((uint8_t)0x03)


#define IS_SYSCFG_MEMORY_REMAP(REMAP) (((REMAP) == SYSCFG_MemoryRemap_Flash) || \
((REMAP) == SYSCFG_MemoryRemap_SystemMemory) || \
    ((REMAP) == SYSCFG_MemoryRemap_SRAM))

/**
* @}
*/

/** @defgroup SYSCFG_DMA_Remap_Config 
* @{
*/ 
#define SYSCFG_DMARemap_TIM17       SYSCFG_CFGR_TIM17_DMA_RMP    /* Remap TIM17 DMA requests from channel1 to channel2 */
#define SYSCFG_DMARemap_TIM16       SYSCFG_CFGR_TIM16_DMA_RMP    /* Remap TIM16 DMA requests from channel3 to channel4 */
#define SYSCFG_DMARemap_UART1Rx    SYSCFG_CFGR_UART1RX_DMA_RMP /* Remap UART1 Rx DMA requests from channel3 to channel5 */
#define SYSCFG_DMARemap_UART1Tx    SYSCFG_CFGR_UART1TX_DMA_RMP /* Remap UART1 Tx DMA requests from channel2 to channel4 */
#define SYSCFG_DMARemap_ADC1        SYSCFG_CFGR_ADC_DMA_RMP      /* Remap ADC1 DMA requests from channel1 to channel2 */

#define IS_SYSCFG_DMA_REMAP(REMAP) (((REMAP) == SYSCFG_DMARemap_TIM17) || \
((REMAP) == SYSCFG_DMARemap_TIM16) || \
    ((REMAP) == SYSCFG_DMARemap_UART1Rx) || \
        ((REMAP) == SYSCFG_DMARemap_UART1Tx) || \
            ((REMAP) == SYSCFG_CFGR1_TIM3_DMA_RMP) || \
                ((REMAP) == SYSCFG_CFGR1_TIM2_DMA_RMP) || \
                    ((REMAP) == SYSCFG_CFGR1_TIM1_DMA_RMP) || \
                        ((REMAP) == SYSCFG_CFGR1_I2C1_DMA_RMP) || \
                            ((REMAP) == SYSCFG_CFGR1_UART3_DMA_RMP) || \
                                ((REMAP) == SYSCFG_CFGR1_UART2_DMA_RMP) || \
                                    ((REMAP) == SYSCFG_CFGR1_SPI2_DMA_RMP) || \
                                        ((REMAP) == SYSCFG_CFGR1_TIM17_DMA_RMP2) || \
                                            ((REMAP) == SYSCFG_CFGR1_TIM16_DMA_RMP2) || \
                                                ((REMAP) == SYSCFG_DMARemap_ADC1))


/**
* @}
*/




/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the SYSCFG configuration to the default reset state **/
void SYSCFG_DeInit(void);

/* SYSCFG configuration functions *********************************************/ 
void SYSCFG_MemoryRemapConfig(uint32_t SYSCFG_MemoryRemap);
void SYSCFG_DMAChannelRemapConfig(uint32_t SYSCFG_DMARemap, FunctionalState NewState);
void SYSCFG_I2CFastModePlusConfig(uint32_t SYSCFG_I2CFastModePlus, FunctionalState NewState);
void SYSCFG_IRDAEnvSelection(uint32_t SYSCFG_IRDAEnv);
void SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex);
uint32_t SYSCFG_GetPendingIT(uint32_t ITSourceLine);
void SYSCFG_BreakConfig(uint32_t SYSCFG_Break);
FlagStatus SYSCFG_GetFlagStatus(uint32_t SYSCFG_Flag);
void SYSCFG_ClearFlag(uint32_t SYSCFG_Flag);

#ifdef __cplusplus
}
#endif

#endif /*__HAL_SYSCFG_H */

/**
* @}
*/ 

/**
* @}
*/ 

/*-------------------------(C) COPYRIGHT 2017 MindMotion ----------------------*/
