/**
  ******************************************************************************
  * @file    hk32f0xx_syscfg.h 
  *  @version V1.0.1
  * @date    2019-08-15
  ******************************************************************************
  */

/*!< Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F0XX_SYSCFG_H
#define __HK32F0XX_SYSCFG_H

#ifdef __cplusplus
 extern "C" {
#endif

/*!< Includes ------------------------------------------------------------------*/
#include "hk32f0xx.h"

/** @addtogroup HK32F0xx_StdPeriph_Driver
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
#define EXTI_PortSourceGPIOD       ((uint8_t)0x03) /*!< not available for HK32F031 devices */
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
                
#define SYSCFG_DMARemap_USART3      SYSCFG_CFGR1_USART3_DMA_RMP    /* Remap USART3 DMA requests from channel6/7 to channel3/2 */
                                                                    
#define SYSCFG_DMARemap_TIM17       SYSCFG_CFGR1_TIM17_DMA_RMP    /* Remap TIM17 DMA requests from channel1 to channel2 */
#define SYSCFG_DMARemap_TIM16       SYSCFG_CFGR1_TIM16_DMA_RMP    /* Remap TIM16 DMA requests from channel3 to channel4 */
#define SYSCFG_DMARemap_USART1Rx    SYSCFG_CFGR1_USART1RX_DMA_RMP /* Remap USART1 Rx DMA requests from channel3 to channel5 */
#define SYSCFG_DMARemap_USART1Tx    SYSCFG_CFGR1_USART1TX_DMA_RMP /* Remap USART1 Tx DMA requests from channel2 to channel4 */
#define SYSCFG_DMARemap_ADC1        SYSCFG_CFGR1_ADC_DMA_RMP      /* Remap ADC1 DMA requests from channel1 to channel2 */
  
#define IS_SYSCFG_DMA_REMAP(REMAP) ( ((REMAP) == SYSCFG_DMARemap_USART3) || \
                                    ((REMAP) == SYSCFG_DMARemap_TIM17) || \
                                    ((REMAP) == SYSCFG_DMARemap_TIM16) || \
                                    ((REMAP) == SYSCFG_DMARemap_USART1Rx) || \
                                    ((REMAP) == SYSCFG_DMARemap_USART1Tx) || \
                                    ((REMAP) == SYSCFG_DMARemap_ADC1))

/**
  * @}
  */

/** @defgroup SYSCFG_I2C_FastModePlus_Config 
  * @{
  */ 
#define SYSCFG_I2CFastModePlus_PB6       SYSCFG_CFGR1_I2C_FMP_PB6 /* Enable Fast Mode Plus on PB6 */
#define SYSCFG_I2CFastModePlus_PB7       SYSCFG_CFGR1_I2C_FMP_PB7 /* Enable Fast Mode Plus on PB7 */
#define SYSCFG_I2CFastModePlus_PB8       SYSCFG_CFGR1_I2C_FMP_PB8 /* Enable Fast Mode Plus on PB8 */
#define SYSCFG_I2CFastModePlus_PB9       SYSCFG_CFGR1_I2C_FMP_PB9 /* Enable Fast Mode Plus on PB9 */
#define SYSCFG_I2CFastModePlus_I2C1      SYSCFG_CFGR1_I2C_FMP_I2C1 /* Enable Fast Mode Plus on PB10, PB11, PF6 and PF7(only for HK32F0031 and HK32F030 devices) */
#define SYSCFG_I2CFastModePlus_PA9       SYSCFG_CFGR1_I2C_FMP_PA9 /* Enable Fast Mode Plus on PA9 (only for HK32F031 and HK32F030 devices) */
#define SYSCFG_I2CFastModePlus_PA10      SYSCFG_CFGR1_I2C_FMP_PA10/* Enable Fast Mode Plus on PA10(only for HK32F031 and HK32F030 devices) */

#define IS_SYSCFG_I2C_FMP(PIN) (((PIN) == SYSCFG_I2CFastModePlus_PB6)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB7)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB8)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB9)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_I2C1) || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PA9)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PA10))


/**
  * @}
  */

/** @defgroup SYSCFG_Lock_Config 
  * @{
  */ 
#define SYSCFG_Break_PVD                     SYSCFG_CFGR2_PVD_LOCK       /*!< Connects the PVD event to the Break Input of TIM1 */
#define SYSCFG_Break_SRAMParity              SYSCFG_CFGR2_SRAM_PARITY_LOCK  /*!< Connects the SRAM_PARITY error signal to the Break Input of TIM1 */
#define SYSCFG_Break_Lockup                  SYSCFG_CFGR2_LOCKUP_LOCK       /*!< Connects Lockup output of CortexM0 to the break input of TIM1 */

#define IS_SYSCFG_LOCK_CONFIG(CONFIG) (((CONFIG) == SYSCFG_Break_PVD)        || \
                                       ((CONFIG) == SYSCFG_Break_SRAMParity) || \
                                       ((CONFIG) == SYSCFG_Break_Lockup))

/**
  * @}
  */

/** @defgroup SYSCFG_flags_definition 
  * @{
  */

#define SYSCFG_FLAG_PE               SYSCFG_CFGR2_SRAM_PE

#define IS_SYSCFG_FLAG(FLAG) (((FLAG) == SYSCFG_FLAG_PE))

/**
  * @}
  */

/** @defgroup SYSCFG_ISR_WRAPPER
  * @{
  */
#define SYSCFG_ITLINE0                           ((uint32_t) 0x00000000)
#define SYSCFG_ITLINE1                           ((uint32_t) 0x00000001)
#define SYSCFG_ITLINE2                           ((uint32_t) 0x00000002)
#define SYSCFG_ITLINE3                           ((uint32_t) 0x00000003)
#define SYSCFG_ITLINE4                           ((uint32_t) 0x00000004)
#define SYSCFG_ITLINE5                           ((uint32_t) 0x00000005)
#define SYSCFG_ITLINE6                           ((uint32_t) 0x00000006)
#define SYSCFG_ITLINE7                           ((uint32_t) 0x00000007)
#define SYSCFG_ITLINE8                           ((uint32_t) 0x00000008)
#define SYSCFG_ITLINE9                           ((uint32_t) 0x00000009)
#define SYSCFG_ITLINE10                          ((uint32_t) 0x0000000A)
#define SYSCFG_ITLINE11                          ((uint32_t) 0x0000000B)
#define SYSCFG_ITLINE12                          ((uint32_t) 0x0000000C)
#define SYSCFG_ITLINE13                          ((uint32_t) 0x0000000D)
#define SYSCFG_ITLINE14                          ((uint32_t) 0x0000000E)
#define SYSCFG_ITLINE15                          ((uint32_t) 0x0000000F)
#define SYSCFG_ITLINE16                          ((uint32_t) 0x00000010)
#define SYSCFG_ITLINE17                          ((uint32_t) 0x00000011)
#define SYSCFG_ITLINE18                          ((uint32_t) 0x00000012)
#define SYSCFG_ITLINE19                          ((uint32_t) 0x00000013)
#define SYSCFG_ITLINE20                          ((uint32_t) 0x00000014)
#define SYSCFG_ITLINE21                          ((uint32_t) 0x00000015)
#define SYSCFG_ITLINE22                          ((uint32_t) 0x00000016)
#define SYSCFG_ITLINE23                          ((uint32_t) 0x00000017)
#define SYSCFG_ITLINE24                          ((uint32_t) 0x00000018)
#define SYSCFG_ITLINE25                          ((uint32_t) 0x00000019)
#define SYSCFG_ITLINE26                          ((uint32_t) 0x0000001A)
#define SYSCFG_ITLINE27                          ((uint32_t) 0x0000001B)
#define SYSCFG_ITLINE28                          ((uint32_t) 0x0000001C)
#define SYSCFG_ITLINE29                          ((uint32_t) 0x0000001D)
#define SYSCFG_ITLINE30                          ((uint32_t) 0x0000001E)
#define SYSCFG_ITLINE31                          ((uint32_t) 0x0000001F)

#define ITLINE_EWDG           ((uint32_t) ((SYSCFG_ITLINE0 << 0x18) | SYSCFG_ITLINE0_SR_EWDG)) /* EWDG Interrupt */
#define ITLINE_PVDOUT         ((uint32_t) ((SYSCFG_ITLINE1 << 0x18) | SYSCFG_ITLINE1_SR_PVDOUT)) /* Power voltage detection Interrupt */
#define ITLINE_VDDIO2         ((uint32_t) ((SYSCFG_ITLINE1 << 0x18) | SYSCFG_ITLINE1_SR_VDDIO2)) /* VDDIO2 Interrupt */
#define ITLINE_RTC_WAKEUP     ((uint32_t) ((SYSCFG_ITLINE2 << 0x18) | SYSCFG_ITLINE2_SR_RTC_WAKEUP)) /* RTC WAKEUP -> exti[20] Interrupt */
#define ITLINE_RTC_TSTAMP     ((uint32_t) ((SYSCFG_ITLINE2 << 0x18) | SYSCFG_ITLINE2_SR_RTC_TSTAMP)) /* RTC Time Stamp -> exti[19] interrupt */
#define ITLINE_RTC_ALRA       ((uint32_t) ((SYSCFG_ITLINE2 << 0x18) | SYSCFG_ITLINE2_SR_RTC_ALRA)) /* RTC Alarm -> exti[17] interrupt */
#define ITLINE_FLASH_ITF      ((uint32_t) ((SYSCFG_ITLINE3 << 0x18) | SYSCFG_ITLINE3_SR_FLASH_ITF)) /* Flash ITF Interrupt */
#define ITLINE_CRS            ((uint32_t) ((SYSCFG_ITLINE4 << 0x18) | SYSCFG_ITLINE4_SR_CRS)) /* CRS Interrupt */
#define ITLINE_CLK_CTRL       ((uint32_t) ((SYSCFG_ITLINE4 << 0x18) | SYSCFG_ITLINE4_SR_CLK_CTRL)) /* CLK Control Interrupt */
#define ITLINE_EXTI0          ((uint32_t) ((SYSCFG_ITLINE5 << 0x18) | SYSCFG_ITLINE5_SR_EXTI0)) /* External Interrupt 0 */
#define ITLINE_EXTI1          ((uint32_t) ((SYSCFG_ITLINE5 << 0x18) | SYSCFG_ITLINE5_SR_EXTI1)) /* External Interrupt 1 */
#define ITLINE_EXTI2          ((uint32_t) ((SYSCFG_ITLINE6 << 0x18) | SYSCFG_ITLINE6_SR_EXTI2)) /* External Interrupt 2 */
#define ITLINE_EXTI3          ((uint32_t) ((SYSCFG_ITLINE6 << 0x18) | SYSCFG_ITLINE6_SR_EXTI3)) /* External Interrupt 3 */
#define ITLINE_EXTI4          ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI4)) /* EXTI4 Interrupt */
#define ITLINE_EXTI5          ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI5)) /* EXTI5 Interrupt */
#define ITLINE_EXTI6          ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI6)) /* EXTI6 Interrupt */
#define ITLINE_EXTI7          ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI7)) /* EXTI7 Interrupt */
#define ITLINE_EXTI8          ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI8)) /* EXTI8 Interrupt */
#define ITLINE_EXTI9          ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI9)) /* EXTI9 Interrupt */
#define ITLINE_EXTI10         ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI10)) /* EXTI10 Interrupt */
#define ITLINE_EXTI11         ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI11)) /* EXTI11 Interrupt */
#define ITLINE_EXTI12         ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI12)) /* EXTI12 Interrupt */
#define ITLINE_EXTI13         ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI13)) /* EXTI13 Interrupt */
#define ITLINE_EXTI14         ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI14)) /* EXTI14 Interrupt */
#define ITLINE_EXTI15         ((uint32_t) ((SYSCFG_ITLINE7 << 0x18) | SYSCFG_ITLINE7_SR_EXTI15)) /* EXTI15 Interrupt */
#define ITLINE_TSC_EOA        ((uint32_t) ((SYSCFG_ITLINE8 << 0x18) | SYSCFG_ITLINE8_SR_TSC_EOA)) /* Touch control EOA Interrupt */
#define ITLINE_TSC_MCE        ((uint32_t) ((SYSCFG_ITLINE8 << 0x18) | SYSCFG_ITLINE8_SR_TSC_MCE)) /* Touch control MCE Interrupt */
#define ITLINE_DMA1_CH1       ((uint32_t) ((SYSCFG_ITLINE9 << 0x18) | SYSCFG_ITLINE9_SR_DMA1_CH1)) /* DMA1 Channel 1 Interrupt */
#define ITLINE_DMA1_CH2       ((uint32_t) ((SYSCFG_ITLINE10 << 0x18) | SYSCFG_ITLINE10_SR_DMA1_CH2)) /* DMA1 Channel 2 Interrupt */
#define ITLINE_DMA1_CH3       ((uint32_t) ((SYSCFG_ITLINE10 << 0x18) | SYSCFG_ITLINE10_SR_DMA1_CH3)) /* DMA1 Channel 3 Interrupt */
#define ITLINE_DMA2_CH1       ((uint32_t) ((SYSCFG_ITLINE10 << 0x18) | SYSCFG_ITLINE10_SR_DMA2_CH1)) /* DMA2 Channel 1 Interrupt */
#define ITLINE_DMA2_CH2       ((uint32_t) ((SYSCFG_ITLINE10 << 0x18) | SYSCFG_ITLINE10_SR_DMA2_CH2)) /* DMA2 Channel 2 Interrupt */
#define ITLINE_DMA1_CH4       ((uint32_t) ((SYSCFG_ITLINE11 << 0x18) | SYSCFG_ITLINE11_SR_DMA1_CH4)) /* DMA1 Channel 4 Interrupt */
#define ITLINE_DMA1_CH5       ((uint32_t) ((SYSCFG_ITLINE11 << 0x18) | SYSCFG_ITLINE11_SR_DMA1_CH5)) /* DMA1 Channel 5 Interrupt */
#define ITLINE_DMA1_CH6       ((uint32_t) ((SYSCFG_ITLINE11 << 0x18) | SYSCFG_ITLINE11_SR_DMA1_CH6)) /* DMA1 Channel 6 Interrupt */
#define ITLINE_DMA1_CH7       ((uint32_t) ((SYSCFG_ITLINE11 << 0x18) | SYSCFG_ITLINE11_SR_DMA1_CH7)) /* DMA1 Channel 7 Interrupt */
#define ITLINE_DMA2_CH3       ((uint32_t) ((SYSCFG_ITLINE11 << 0x18) | SYSCFG_ITLINE11_SR_DMA2_CH3)) /* DMA2 Channel 3 Interrupt */
#define ITLINE_DMA2_CH4       ((uint32_t) ((SYSCFG_ITLINE11 << 0x18) | SYSCFG_ITLINE11_SR_DMA2_CH4)) /* DMA2 Channel 4 Interrupt */
#define ITLINE_DMA2_CH5       ((uint32_t) ((SYSCFG_ITLINE11 << 0x18) | SYSCFG_ITLINE11_SR_DMA2_CH5)) /* DMA2 Channel 5 Interrupt */
#define ITLINE_ADC            ((uint32_t) ((SYSCFG_ITLINE12 << 0x18) | SYSCFG_ITLINE12_SR_ADC)) /* ADC Interrupt */
#define ITLINE_COMP1          ((uint32_t) ((SYSCFG_ITLINE12 << 0x18) | SYSCFG_ITLINE12_SR_COMP1)) /* COMP1 Interrupt -> exti[21] */
#define ITLINE_COMP2          ((uint32_t) ((SYSCFG_ITLINE12 << 0x18) | SYSCFG_ITLINE12_SR_COMP2)) /* COMP2 Interrupt -> exti[21] */
#define ITLINE_TIM1_BRK       ((uint32_t) ((SYSCFG_ITLINE13 << 0x18) | SYSCFG_ITLINE13_SR_TIM1_BRK)) /* TIM1 BRK Interrupt */
#define ITLINE_TIM1_UPD       ((uint32_t) ((SYSCFG_ITLINE13 << 0x18) | SYSCFG_ITLINE13_SR_TIM1_UPD)) /* TIM1 UPD Interrupt */
#define ITLINE_TIM1_TRG       ((uint32_t) ((SYSCFG_ITLINE13 << 0x18) | SYSCFG_ITLINE13_SR_TIM1_TRG)) /* TIM1 TRG Interrupt */
#define ITLINE_TIM1_CCU       ((uint32_t) ((SYSCFG_ITLINE13 << 0x18) | SYSCFG_ITLINE13_SR_TIM1_CCU)) /* TIM1 CCU Interrupt */
#define ITLINE_TIM1_CC        ((uint32_t) ((SYSCFG_ITLINE14 << 0x18) | SYSCFG_ITLINE14_SR_TIM1_CC)) /* TIM1 CC Interrupt */
#define ITLINE_TIM2           ((uint32_t) ((SYSCFG_ITLINE15 << 0x18) | SYSCFG_ITLINE15_SR_TIM2_GLB)) /* TIM2 Interrupt */
#define ITLINE_TIM3           ((uint32_t) ((SYSCFG_ITLINE16 << 0x18) | SYSCFG_ITLINE16_SR_TIM3_GLB)) /* TIM3 Interrupt */
#define ITLINE_DAC            ((uint32_t) ((SYSCFG_ITLINE17 << 0x18) | SYSCFG_ITLINE17_SR_DAC)) /* DAC Interrupt */
#define ITLINE_TIM6           ((uint32_t) ((SYSCFG_ITLINE17 << 0x18) | SYSCFG_ITLINE17_SR_TIM6_GLB)) /* TIM6 Interrupt */
#define ITLINE_TIM7           ((uint32_t) ((SYSCFG_ITLINE18 << 0x18) | SYSCFG_ITLINE18_SR_TIM7_GLB)) /* TIM7 Interrupt */
#define ITLINE_TIM14          ((uint32_t) ((SYSCFG_ITLINE19 << 0x18) | SYSCFG_ITLINE19_SR_TIM14_GLB)) /* TIM14 Interrupt */
#define ITLINE_TIM15          ((uint32_t) ((SYSCFG_ITLINE20 << 0x18) | SYSCFG_ITLINE20_SR_TIM15_GLB)) /* TIM15 Interrupt */
#define ITLINE_TIM16          ((uint32_t) ((SYSCFG_ITLINE21 << 0x18) | SYSCFG_ITLINE21_SR_TIM16_GLB)) /* TIM16 Interrupt */
#define ITLINE_TIM17          ((uint32_t) ((SYSCFG_ITLINE22 << 0x18) | SYSCFG_ITLINE22_SR_TIM17_GLB)) /* TIM17 Interrupt */
#define ITLINE_I2C1           ((uint32_t) ((SYSCFG_ITLINE23 << 0x18) | SYSCFG_ITLINE23_SR_I2C1_GLB)) /* I2C1 Interrupt -> exti[23] */
#define ITLINE_I2C2           ((uint32_t) ((SYSCFG_ITLINE24 << 0x18) | SYSCFG_ITLINE24_SR_I2C2_GLB)) /* I2C2 Interrupt */
#define ITLINE_SPI1           ((uint32_t) ((SYSCFG_ITLINE25 << 0x18) | SYSCFG_ITLINE25_SR_SPI1)) /* I2C1 Interrupt -> exti[23] */
#define ITLINE_SPI2           ((uint32_t) ((SYSCFG_ITLINE26 << 0x18) | SYSCFG_ITLINE26_SR_SPI2)) /* SPI1 Interrupt */
#define ITLINE_USART1         ((uint32_t) ((SYSCFG_ITLINE27 << 0x18) | SYSCFG_ITLINE27_SR_USART1_GLB)) /*!< USART1 GLB Interrupt -> exti[25] */
#define ITLINE_USART2         ((uint32_t) ((SYSCFG_ITLINE28 << 0x18) | SYSCFG_ITLINE28_SR_USART2_GLB)) /*!< USART2 GLB Interrupt -> exti[26] */
#define ITLINE_USART3         ((uint32_t) ((SYSCFG_ITLINE29 << 0x18) | SYSCFG_ITLINE29_SR_USART3_GLB)) /* USART3 Interrupt */
#define ITLINE_USART4         ((uint32_t) ((SYSCFG_ITLINE29 << 0x18) | SYSCFG_ITLINE29_SR_USART4_GLB)) /* USART4 Interrupt */
#define ITLINE_USART5         ((uint32_t) ((SYSCFG_ITLINE29 << 0x18) | SYSCFG_ITLINE29_SR_USART5_GLB)) /* USART5 Interrupt */
#define ITLINE_USART6         ((uint32_t) ((SYSCFG_ITLINE29 << 0x18) | SYSCFG_ITLINE29_SR_USART6_GLB)) /* USART6 Interrupt */
#define ITLINE_USART7         ((uint32_t) ((SYSCFG_ITLINE29 << 0x18) | SYSCFG_ITLINE29_SR_USART7_GLB)) /* USART7 Interrupt */
#define ITLINE_USART8         ((uint32_t) ((SYSCFG_ITLINE29 << 0x18) | SYSCFG_ITLINE29_SR_USART8_GLB)) /* USART8 Interrupt */
#define ITLINE_CAN            ((uint32_t) ((SYSCFG_ITLINE30 << 0x18) | SYSCFG_ITLINE30_SR_CAN)) /* CAN Interrupt */
#define ITLINE_CEC            ((uint32_t) ((SYSCFG_ITLINE30 << 0x18) | SYSCFG_ITLINE30_SR_CEC)) /* CEC Interrupt -> exti[27] */

#define IS_SYSCFG_ITLINE(LINE) (((LINE) == ITLINE_EWDG)       || \
                                ((LINE) == ITLINE_PVDOUT)     || \
                                ((LINE) == ITLINE_VDDIO2)     || \
                                ((LINE) == ITLINE_RTC_WAKEUP) || \
                                ((LINE) == ITLINE_RTC_TSTAMP) || \
                                ((LINE) == ITLINE_RTC_ALRA)   || \
                                ((LINE) == ITLINE_FLASH_ITF)  || \
                                ((LINE) == ITLINE_CRS)        || \
                                ((LINE) == ITLINE_CLK_CTRL)   || \
                                ((LINE) == ITLINE_EXTI0)      || \
                                ((LINE) == ITLINE_EXTI1)      || \
                                ((LINE) == ITLINE_EXTI2)      || \
                                ((LINE) == ITLINE_EXTI3)      || \
                                ((LINE) == ITLINE_EXTI4)      || \
                                ((LINE) == ITLINE_EXTI5)      || \
                                ((LINE) == ITLINE_EXTI6)      || \
                                ((LINE) == ITLINE_EXTI7)      || \
                                ((LINE) == ITLINE_EXTI8)      || \
                                ((LINE) == ITLINE_EXTI9)      || \
                                ((LINE) == ITLINE_EXTI10)     || \
                                ((LINE) == ITLINE_EXTI11)     || \
                                ((LINE) == ITLINE_EXTI12)     || \
                                ((LINE) == ITLINE_EXTI13)     || \
                                ((LINE) == ITLINE_EXTI14)     || \
                                ((LINE) == ITLINE_EXTI15)     || \
                                ((LINE) == ITLINE_TSC_EOA)    || \
                                ((LINE) == ITLINE_TSC_MCE)    || \
                                ((LINE) == ITLINE_DMA1_CH1)   || \
                                ((LINE) == ITLINE_DMA1_CH2)   || \
                                ((LINE) == ITLINE_DMA1_CH3)   || \
                                ((LINE) == ITLINE_DMA1_CH4)   || \
                                ((LINE) == ITLINE_DMA1_CH5)   || \
                                ((LINE) == ITLINE_DMA1_CH6)   || \
                                ((LINE) == ITLINE_DMA1_CH7)   || \
                                ((LINE) == ITLINE_DMA2_CH1)   || \
                                ((LINE) == ITLINE_DMA2_CH2)   || \
                                ((LINE) == ITLINE_DMA2_CH3)   || \
                                ((LINE) == ITLINE_DMA2_CH4)   || \
                                ((LINE) == ITLINE_DMA2_CH5)   || \
                                ((LINE) == ITLINE_ADC)        || \
                                ((LINE) == ITLINE_COMP1)      || \
                                ((LINE) == ITLINE_COMP2)      || \
                                ((LINE) == ITLINE_TIM1_BRK)   || \
                                ((LINE) == ITLINE_TIM1_UPD)   || \
                                ((LINE) == ITLINE_TIM1_TRG)   || \
                                ((LINE) == ITLINE_TIM1_CCU)   || \
                                ((LINE) == ITLINE_TIM1_CC)    || \
                                ((LINE) == ITLINE_TIM2)       || \
                                ((LINE) == ITLINE_TIM3)       || \
                                ((LINE) == ITLINE_DAC)        || \
                                ((LINE) == ITLINE_TIM6)       || \
                                ((LINE) == ITLINE_TIM7)       || \
                                ((LINE) == ITLINE_TIM14)      || \
                                ((LINE) == ITLINE_TIM15)      || \
                                ((LINE) == ITLINE_TIM16)      || \
                                ((LINE) == ITLINE_TIM17)      || \
                                ((LINE) == ITLINE_I2C1)       || \
                                ((LINE) == ITLINE_I2C2)       || \
                                ((LINE) == ITLINE_SPI1)       || \
                                ((LINE) == ITLINE_SPI2)       || \
                                ((LINE) == ITLINE_USART1)     || \
                                ((LINE) == ITLINE_USART2)     || \
                                ((LINE) == ITLINE_USART3)     || \
                                ((LINE) == ITLINE_USART4)     || \
                                ((LINE) == ITLINE_USART5)     || \
                                ((LINE) == ITLINE_USART6)     || \
                                ((LINE) == ITLINE_USART7)     || \
                                ((LINE) == ITLINE_USART8)     || \
                                ((LINE) == ITLINE_CAN)        || \
                                ((LINE) == ITLINE_CEC))

/**
  * @}
  */
/** @defgroup IRDA_ENV_SEL
  * @{
  */
#define SYSCFG_IRDA_ENV_SEL_TIM16     (SYSCFG_CFGR1_IRDA_ENV_SEL_0&SYSCFG_CFGR1_IRDA_ENV_SEL_1)    /* Timer16 is selected as IRDA Modulation envelope source */
#define SYSCFG_IRDA_ENV_SEL_USART1    (SYSCFG_CFGR1_IRDA_ENV_SEL_0)  /* USART1 is selected as IRDA Modulation envelope source.*/
#define SYSCFG_IRDA_ENV_SEL_USART4    (SYSCFG_CFGR1_IRDA_ENV_SEL_1)  /* USART4 is selected as IRDA Modulation envelope source.*/

#define IS_SYSCFG_IRDA_ENV(ENV) (((ENV) == SYSCFG_IRDA_ENV_SEL_TIM16)      || \
                                 ((ENV) == SYSCFG_IRDA_ENV_SEL_USART1)     || \
                                 ((ENV) == SYSCFG_IRDA_ENV_SEL_USART4))
/**
  * @}
  */

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

#endif /*__HK32F0XX_SYSCFG_H */

/**
  * @}
  */ 

/**
  * @}
  */  
