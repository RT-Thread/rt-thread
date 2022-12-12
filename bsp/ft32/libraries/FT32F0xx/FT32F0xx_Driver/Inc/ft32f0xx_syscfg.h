/**
  ******************************************************************************
  * @file               ft32f0xx_syscfg.h
  * @author             FMD AE
  * @brief              This file contains all the functions prototypes for the SYSCFG firmware
  *                     library.
  * @version            V1.0.0
  * @data                   2021-07-01
  ******************************************************************************
  */


/*!< Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F0XX_SYSCFG_H
#define __FT32F0XX_SYSCFG_H

#ifdef __cplusplus
 extern "C" {
#endif

/*!< Includes ------------------------------------------------------------------*/
#include "ft32f0xx.h"


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
#define SYSCFG_DMARemap_TIM3        SYSCFG_CFGR1_TIM3_DMA_RMP      /* Remap TIM3 DMA requests from channel4 to channel6*/
#define SYSCFG_DMARemap_TIM2        SYSCFG_CFGR1_TIM2_DMA_RMP      /* Remap TIM2 DMA requests from channel3/4 to channel7*/
#define SYSCFG_DMARemap_TIM1        SYSCFG_CFGR1_TIM1_DMA_RMP      /* Remap TIM1 DMA requests from channel2/3/4 to channel6*/
#define SYSCFG_DMARemap_I2C1        SYSCFG_CFGR1_I2C1_DMA_RMP      /* Remap I2C1 DMA requests from channel3/2 to channel7/6*/
#define SYSCFG_DMARemap_USART3      SYSCFG_CFGR1_USART3_DMA_RMP    /* Remap USART3 DMA requests from channel6/7 to channel3/2*/
#define SYSCFG_DMARemap_USART2      SYSCFG_CFGR1_USART2_DMA_RMP    /* Remap USART2 DMA requests from channel4/5 to channel6/7*/
#define SYSCFG_DMARemap_SPI2        SYSCFG_CFGR1_SPI2_DMA_RMP      /* Remap SPI2 DMA requests from channel4/5 to channel6/7*/
#define SYSCFG_DMARemap_TIM17_2     SYSCFG_CFGR1_TIM17_DMA_RMP2    /* Remap TIM17 DMA requests from channel1/2 to channel7*/
#define SYSCFG_DMARemap_TIM16_2     SYSCFG_CFGR1_TIM16_DMA_RMP2    /* Remap TIM16 DMA requests from channel3/4 to channel6*/
#define SYSCFG_DMARemap_TIM17       SYSCFG_CFGR1_TIM17_DMA_RMP     /* Remap TIM17 DMA requests from channel1 to channel2*/
#define SYSCFG_DMARemap_TIM16       SYSCFG_CFGR1_TIM16_DMA_RMP     /* Remap TIM16 DMA requests from channel3 to channel4*/
#define SYSCFG_DMARemap_USART1Rx    SYSCFG_CFGR1_USART1RX_DMA_RMP  /* Remap USART1 Rx DMA requests from channel3 to channel5*/
#define SYSCFG_DMARemap_USART1Tx    SYSCFG_CFGR1_USART1TX_DMA_RMP  /* Remap USART1 Tx DMA requests from channel2 to channel4*/
#define SYSCFG_DMARemap_ADC1        SYSCFG_CFGR1_ADC_DMA_RMP       /* Remap ADC1 DMA requests from channel1 to channel2*/

#define IS_SYSCFG_DMA_REMAP(REMAP) (((REMAP) == SYSCFG_DMARemap_TIM17) || \
                                    ((REMAP) == SYSCFG_DMARemap_TIM16) || \
                                    ((REMAP) == SYSCFG_DMARemap_USART1Rx) || \
                                    ((REMAP) == SYSCFG_DMARemap_USART1Tx) || \
                                    ((REMAP) == SYSCFG_CFGR1_TIM3_DMA_RMP) || \
                                    ((REMAP) == SYSCFG_CFGR1_TIM2_DMA_RMP) || \
                                    ((REMAP) == SYSCFG_CFGR1_TIM1_DMA_RMP) || \
                                    ((REMAP) == SYSCFG_CFGR1_I2C1_DMA_RMP) || \
                                    ((REMAP) == SYSCFG_CFGR1_USART3_DMA_RMP) || \
                                    ((REMAP) == SYSCFG_CFGR1_USART2_DMA_RMP) || \
                                    ((REMAP) == SYSCFG_CFGR1_SPI2_DMA_RMP) || \
                                    ((REMAP) == SYSCFG_CFGR1_TIM17_DMA_RMP2) || \
                                    ((REMAP) == SYSCFG_CFGR1_TIM16_DMA_RMP2) || \
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
#define SYSCFG_I2CFastModePlus_I2C1      SYSCFG_CFGR1_I2C_FMP_I2C1 /* Enable Fast Mode Plus on PB10, PB11, PF6 and PF7*/
#define SYSCFG_I2CFastModePlus_I2C2      SYSCFG_CFGR1_I2C_FMP_I2C2 /* Enable Fast Mode Plus on I2C2 pins*/
#define SYSCFG_I2CFastModePlus_PA9       SYSCFG_CFGR1_I2C_FMP_PA9 /* Enable Fast Mode Plus on PA9*/
#define SYSCFG_I2CFastModePlus_PA10      SYSCFG_CFGR1_I2C_FMP_PA10/* Enable Fast Mode Plus on PA10*/

#define IS_SYSCFG_I2C_FMP(PIN) (((PIN) == SYSCFG_I2CFastModePlus_PB6)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB7)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB8)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB9)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_I2C1) || \
                                ((PIN) == SYSCFG_I2CFastModePlus_I2C2) || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PA9)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PA10))


/**
  * @}
  */

/** @defgroup SYSCFG_Lock_Config
  * @{
  */
#define SYSCFG_Break_PVD                     SYSCFG_CFGR2_PVD_LOCK       /*!< Connects the PVD event to the Break Input of TIM1 */
#define SYSCFG_Break_Lockup                  SYSCFG_CFGR2_LOCKUP_LOCK       /*!< Connects Lockup output of CortexM0 to the break input of TIM1 */

#define IS_SYSCFG_LOCK_CONFIG(CONFIG) (((CONFIG) == SYSCFG_Break_PVD)        || \
                                       ((CONFIG) == SYSCFG_Break_Lockup))

/**
  * @}
  */

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

/**
  * @}
  */
/** @defgroup IRDA_ENV_SEL
  * @{
  */
#define SYSCFG_IRDA_ENV_SEL_TIM16     (SYSCFG_CFGR1_IRDA_ENV_SEL_0&SYSCFG_CFGR1_IRDA_ENV_SEL_1)    /* Timer16 is selected as IRDA Modulation envelope source */
#define SYSCFG_IRDA_ENV_SEL_USART1    (SYSCFG_CFGR1_IRDA_ENV_SEL_0)  /* USART1 is selected as IRDA Modulation envelope source.*/
#define SYSCFG_IRDA_ENV_SEL_USART2    (SYSCFG_CFGR1_IRDA_ENV_SEL_1)  /* USART2 is selected as IRDA Modulation envelope source.*/

#define IS_SYSCFG_IRDA_ENV(ENV) (((ENV) == SYSCFG_IRDA_ENV_SEL_TIM16)      || \
                                 ((ENV) == SYSCFG_IRDA_ENV_SEL_USART1)     || \
                                 ((ENV) == SYSCFG_IRDA_ENV_SEL_USART2))
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
void SYSCFG_BreakConfig(uint32_t SYSCFG_Break);

#ifdef __cplusplus
}
#endif

#endif /*__FT32F0XX_SYSCFG_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
