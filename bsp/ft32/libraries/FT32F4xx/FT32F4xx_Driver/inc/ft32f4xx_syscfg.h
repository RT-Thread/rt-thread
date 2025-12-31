/**
  ******************************************************************************
  * @file               ft32f4xx_syscfg.h
  * @author             FMD XA
  * @brief              This file contains all the functions prototypes for the SYSCFG firmware
  *                     library.
  * @version            V1.0.0
  * @data                   2025-04-08
  ******************************************************************************
  */


/*!< Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_SYSCFG_H
#define __FT32F4XX_SYSCFG_H

#ifdef __cplusplus
extern "C" {
#endif

/*!< Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"


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
#define EXTI_PortSourceGPIOH       ((uint8_t)0x07)

#define IS_EXTI_PORT_SOURCE(PORTSOURCE) (((PORTSOURCE) == EXTI_PortSourceGPIOA) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOB) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOC) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOD) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOE) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOH))
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
#define SYSCFG_MemoryRemap_Flash                ((uint32_t)0x00)
#define SYSCFG_MemoryRemap_SystemMemory         ((uint32_t)0x01)
#define SYSCFG_MemoryRemap_SRAM                 ((uint32_t)0x03)
#define SYSCFG_MemoryRemap_FMC1                 ((uint32_t)0x02)
#define SYSCFG_MemoryRemap_FMC2                 ((uint32_t)0x04)
#define SYSCFG_MemoryRemap_QSPI                 ((uint32_t)0x05)


#define IS_SYSCFG_MEMORY_REMAP(REMAP) (((REMAP) == SYSCFG_MemoryRemap_Flash) || \
                                       ((REMAP) == SYSCFG_MemoryRemap_SystemMemory) || \
                                       ((REMAP) == SYSCFG_MemoryRemap_SRAM) || \
                                       ((REMAP) == SYSCFG_MemoryRemap_FMC1) || \
                                       ((REMAP) == SYSCFG_MemoryRemap_FMC2) || \
                                       ((REMAP) == SYSCFG_MemoryRemap_QSPI) )

/**
  * @}
  */

/** @defgroup SYSCFG_FMC_Memory_mapping_swap_Config
  * @{
  */
#define SYSCFG_FMC_SWP_ENABLE                SYSCFG_MEMRMP_SWP_FMC_MAP
#define SYSCFG_FMC_SWP_DISABLE               SYSCFG_MEMRMP_SWP_FMC_NO


#define IS_SYSCFG_FMC_SWP(FMCCFG)   (((FMCCFG) == SYSCFG_FMC_SWP_ENABLE) || \
                                     ((FMCCFG) == SYSCFG_FMC_SWP_DISABLE) )

/**
  * @}
  */

/** @defgroup SYSCFG_ETH_MII_RMII_Config
  * @{
  */
#define SYSCFG_ETH_MII_RMII_SEL_MII                ((uint32_t)0x00)
#define SYSCFG_ETH_MII_RMII_SEL_RMII               SYSCFG_PMC_MII_RMII_SEL


#define IS_SYSCFG_ETH_MII_RMII_SEL(ETHCFG)   (((ETHCFG) == SYSCFG_ETH_MII_RMII_SEL_MII) || \
                                              ((ETHCFG) == SYSCFG_ETH_MII_RMII_SEL_RMII) )

/**
  * @}
  */



/** @defgroup SYSCFG_BoostEN_Config
  * @{
  */
#define SYSCFG_PMC_BoostEN_ENABLE               SYSCFG_PMC_BOOSTEN
#define SYSCFG_PMC_BoostEN_DISABLE              ((uint32_t)0x00)

#define IS_SYSCFG_PMC_BoostEN(BOOSTCFG) (((BOOSTCFG) == SYSCFG_PMC_BoostEN_ENABLE) || \
                                        ((BOOSTCFG) == SYSCFG_PMC_BoostEN_DISABLE)  )

/**
  * @}
  */


/** @defgroup SYSCFG_I2C_FastModePlus_Config
  * @{
  */
#define SYSCFG_I2CFastModePlus_PB6       SYSCFG_PMC_I2C_PB6_FMP /* Enable Fast Mode Plus on PB6 */
#define SYSCFG_I2CFastModePlus_PB7       SYSCFG_PMC_I2C_PB7_FMP /* Enable Fast Mode Plus on PB7 */
#define SYSCFG_I2CFastModePlus_PB8       SYSCFG_PMC_I2C_PB8_FMP /* Enable Fast Mode Plus on PB8 */
#define SYSCFG_I2CFastModePlus_PB9       SYSCFG_PMC_I2C_PB9_FMP /* Enable Fast Mode Plus on PB9 */
#define SYSCFG_I2CFastModePlus_I2C1      SYSCFG_PMC_I2C1_FMP    /* Enable Fast Mode Plus on PB10, PB11, PF6 and PF7*/
#define SYSCFG_I2CFastModePlus_I2C2      SYSCFG_PMC_I2C2_FMP    /* Enable Fast Mode Plus on I2C2 pins*/
#define SYSCFG_I2CFastModePlus_I2C3      SYSCFG_PMC_I2C3_FMP    /* Enable Fast Mode Plus on I2C3 pins*/

#define IS_SYSCFG_I2C_FMP(PIN) (((PIN) == SYSCFG_I2CFastModePlus_PB6)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB7)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB8)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB9)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_I2C1) || \
                                ((PIN) == SYSCFG_I2CFastModePlus_I2C2) || \
                                ((PIN) == SYSCFG_I2CFastModePlus_I2C3) )


/**
  * @}
  */

/** @defgroup SYSCFG_Lock_Config
  * @{
  */
#define SYSCFG_Break_PVD                     SYSCFG_CFGR_PVD_LOCK       /*!< Connects the PVD event to the Break Input of TIM1 */
#define SYSCFG_Break_Lockup                  SYSCFG_CFGR_LOCKUP_LOCK       /*!< Connects Lockup output of CortexM0 to the break input of TIM1 */

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

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the SYSCFG configuration to the default reset state **/
void SYSCFG_DeInit(void);

/* SYSCFG configuration functions *********************************************/
void SYSCFG_MemoryRemapConfig(uint32_t SYSCFG_MemoryRemap);
void SYSCFG_FMCSWPConfig(uint32_t SYSCFG_FMCSWPCFG);
void SYSCFG_BoostENConfig(uint32_t SYSCFG_BoostENCFG);
void SYSCFG_I2CFastModePlusConfig(uint32_t SYSCFG_I2CFastModePlus, FunctionalState NewState);
void SYSCFG_MII_RMIIConfig(uint32_t SYSCFG_MII_RMIICFG);
void SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex);
void SYSCFG_BreakConfig(uint32_t SYSCFG_Break);

#ifdef __cplusplus
}
#endif

#endif /*__FT32F4XX_SYSCFG_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
