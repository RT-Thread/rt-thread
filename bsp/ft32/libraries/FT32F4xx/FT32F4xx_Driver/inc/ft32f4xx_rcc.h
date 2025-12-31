/**
  ******************************************************************************
  * @file               ft32f4xx_rcc.h
  * @author             Rwang
  * @brief              This file contains all the functions prototypes for the RCC
  *                     firmware library.
  * @version            V1.0.0
  * @data                   2025-03-03
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F0XX_RCC_H
#define __FT32F0XX_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"

/** @addtogroup RCC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

typedef struct
{
    uint32_t SYSCLK_Frequency;
    uint32_t HCLK_Frequency;
    uint32_t PCLK_Frequency;
    uint32_t PLLQ_Frequency;
    uint32_t PLLR_Frequency;
    uint32_t P2CLK_Frequency;
    uint32_t PLL2Q_Frequency;
    uint32_t PLL2R_Frequency;
    uint32_t QSPICLK_Frequency;
    uint32_t ADCCLK_Frequency;
    uint32_t CANCLK_Frequency;
    uint32_t LPTIMCLK_Frequency;
    uint32_t I2C3CLK_Frequency;
    uint32_t I2C2CLK_Frequency;
    uint32_t I2C1CLK_Frequency;
    uint32_t LPUARTCLK_Frequency;
    uint32_t PWMCLK_Frequency;
    uint32_t EQEPCLK_Frequency;
    uint32_t ECAPCLK_Frequency;
    uint32_t I2SCLK_Frequency;
} RCC_ClocksTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup RCC_Exported_Constants
  * @{
  */
#define RCC_FLAG_PLL2RDY                 ((uint32_t)0x08000000)
#define RCC_FLAG_PLLRDY                  ((uint32_t)0x02000000)
#define RCC_FLAG_HSERDY                  ((uint32_t)0x00020000)
#define RCC_FLAG_HSIRDY                  ((uint32_t)0x00000002)
#define RCC_FLAG_HSI48RDY                ((uint32_t)0x00020000)
#define RCC_FLAG_LSERDY                  ((uint32_t)0x00000002)
#define RCC_FLAG_LPWRRSTF                ((uint32_t)0x80000000)
#define RCC_FLAG_WWDGRSTF                ((uint32_t)0x40000000)
#define RCC_FLAG_IWDGRSTF                ((uint32_t)0x20000000)
#define RCC_FLAG_SFTRSTF                 ((uint32_t)0x10000000)
#define RCC_FLAG_PORRSTF                 ((uint32_t)0x08000000)
#define RCC_FLAG_PINRSTF                 ((uint32_t)0x04000000)
#define RCC_FLAG_RMVF                    ((uint32_t)0x01000000)
#define RCC_FLAG_LSIRDY                  ((uint32_t)0x00000002)
#define IS_RCC_FLAG(FLAG)               (((FLAG) == RCC_FLAG_PLL2RDY)  || ((FLAG) == RCC_FLAG_PLLRDY)   || \
                                         ((FLAG) == RCC_FLAG_HSERDY)   || ((FLAG) == RCC_FLAG_HSIRDY)   || \
                                         ((FLAG) == RCC_FLAG_HSI48RDY) || ((FLAG) == RCC_FLAG_LSERDY)   || \
                                         ((FLAG) == RCC_FLAG_LPWRRSTF) || ((FLAG) == RCC_FLAG_WWDGRSTF) || \
                                         ((FLAG) == RCC_FLAG_IWDGRSTF) || ((FLAG) == RCC_FLAG_SFTRSTF)  || \
                                         ((FLAG) == RCC_FLAG_PORRSTF)  || ((FLAG) == RCC_FLAG_PINRSTF)  || \
                                         ((FLAG) == RCC_FLAG_RMVF)     || ((FLAG) == RCC_FLAG_LSIRDY))

#define RCC_FLAG_REG_CR                  ((uint8_t)0x00)
#define RCC_FLAG_REG_CR2                 ((uint8_t)0x01)
#define RCC_FLAG_REG_BDCR                ((uint8_t)0x02)
#define RCC_FLAG_REG_CSR                 ((uint8_t)0x03)
#define IS_RCC_FLAG_REG(REG)            (((REG) == RCC_FLAG_REG_CR)   || ((REG) == RCC_FLAG_REG_CR2) || \
                                         ((REG) == RCC_FLAG_REG_BDCR) || ((REG) == RCC_FLAG_REG_CSR))

#define IS_RCC_HSI_CALIBRATION_VALUE(VALUE)   ((VALUE) <= 0x0000001F)


#define IS_RCC_HSI48_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x000001FF)



//RCC_CR_REG
#define RCC_SEL_PLL                      ((uint32_t)0x00000000)
#define RCC_SEL_PLL2                     ((uint32_t)0x00000001)
#define IS_RCC_SEL(SEL)                 (((SEL) == RCC_SEL_PLL) || \
                                         ((SEL) == RCC_SEL_PLL2))



#define RCC_HSE_OFF                      ((uint32_t)0x00000000)
#define RCC_HSE_ON                       ((uint32_t)0x00010000)
#define RCC_HSE_Bypass                   ((uint32_t)0x00050000)
#define IS_RCC_HSE(HSE)   (((HSE) == RCC_HSE_OFF)   || \
                           ((HSE) == RCC_HSE_ON)    || \
                           ((HSE) == RCC_HSE_Bypass)   )

#define RCC_HSI_OFF                      ((uint8_t)0x00)
#define RCC_HSI_ON                       ((uint8_t)0x01)
#define IS_RCC_HSI(HSI)   (((HSI) == RCC_HSI_OFF)   || \
                           ((HSI) == RCC_HSI_ON)       )

//RCC_PLLCFGR_REG
//PLLRCLK=((VCO/(PLLR+1))
#define IS_RCC_PLLR_VALUE(VALUE)   ((VALUE) <= (uint32_t)0x00000007)

#define RCC_PLLR_OFF               ((uint32_t)0x00000000)
#define RCC_PLLR_ON                ((uint32_t)0x00000001)
#define IS_RCC_PLLR(PLLR)         (((PLLR) == RCC_PLLR_OFF)   || \
                                   ((PLLR) == RCC_PLLR_ON)       )

//PLLQCLK=((VCO/(PLLQ+1))
#define IS_RCC_PLLQ_VALUE(VALUE)   ((VALUE) <= (uint32_t)0x0000000F)

#define RCC_PLLQ_OFF               ((uint32_t)0x00000000)
#define RCC_PLLQ_ON                ((uint32_t)0x00000001)
#define IS_RCC_PLLQ(PLLQ)         (((PLLQ) == RCC_PLLQ_OFF)   || \
                                   ((PLLQ) == RCC_PLLQ_ON)       )

//PLLPCLK=((VCO/(PLLP+1))
#define IS_RCC_PLLP_VALUE(VALUE)   ((VALUE) <= (uint32_t)0x00000007)

#define RCC_PLLP_OFF               ((uint32_t)0x00000000)
#define RCC_PLLP_ON                ((uint32_t)0x00000001)
#define IS_RCC_PLLP(PLLP)         (((PLLP) == RCC_PLLP_OFF)   || \
                                   ((PLLP) == RCC_PLLP_ON)       )

//RCC_PLL_Clock_Source PLLCLK_INPUT=HSE/HSI
#define RCC_PLLSource_HSI          ((uint32_t)0x00000000)
#define RCC_PLLSource_HSE          ((uint32_t)0x00000001)
#define IS_RCC_PLLSRC(SRC)        (((SRC) == RCC_PLLSource_HSI) || \
                                   ((SRC) == RCC_PLLSource_HSE))

// RCC_PLLN_Factor VCO_OUTCLK=VCO_IN*PLLN
#define IS_RCC_PLLN_VALUE(VALUE)   ((VALUE) <= (uint32_t)0x000000FF)

//VCO_OUT=PLL_IN*(PLLN/PLLM)
#define IS_RCC_PLLM_VALUE(VALUE)   ((VALUE) <= (uint32_t)0x0000001F)

/**
  * @}
  */

//RCC_PLL2CFGR_REG
//PLL2RCLK=((VCO/(PLL2R+1))
#define IS_RCC_PLL2R_VALUE(VALUE)   ((VALUE) <= (uint32_t)0x00000007)

#define RCC_PLL2R_OFF               ((uint32_t)0x00000000)
#define RCC_PLL2R_ON                ((uint32_t)0x00000001)
#define IS_RCC_PLL2R(PLL2R)        (((PLL2R) == RCC_PLL2R_OFF)   || \
                                    ((PLL2R) == RCC_PLL2R_ON)       )

//PLL2QCLK=((VCO/(PLL2Q+1))
#define IS_RCC_PLL2Q_VALUE(VALUE)   ((VALUE) <= (uint32_t)0x0000000F)

#define RCC_PLL2Q_OFF               ((uint32_t)0x00000000)
#define RCC_PLL2Q_ON                ((uint32_t)0x00000001)
#define IS_RCC_PLL2Q(PLL2Q)        (((PLL2Q) == RCC_PLL2Q_OFF)   || \
                                    ((PLL2Q) == RCC_PLL2Q_ON)       )

//RCC_PLL2_Clock_Source PLL2CLK_INPUT=HSE/HSI
#define RCC_PLL2Source_HSI          ((uint32_t)0x00000000)
#define RCC_PLL2Source_HSE          ((uint32_t)0x00000001)
#define IS_RCC_PLL2SRC(SRC)        (((SRC) == RCC_PLL2Source_HSI) || \
                                    ((SRC) == RCC_PLL2Source_HSE)    )

// RCC_PLL2N_Factor VCO_OUTCLK=VCO_IN*PLL2N
#define IS_RCC_PLL2N_VALUE(VALUE)   ((VALUE) <= (uint32_t)0x000000FF)

//VCO_OUT=PLL_IN*(PLL2N/PLL2M)
#define IS_RCC_PLL2M_VALUE(VALUE)   ((VALUE) <= (uint32_t)0x0000001F)
/**
  * @}
  */

/** @defgroup RCC_MCOSource_Select
  * @{
  */
#define RCC_MCOSource_NoClock       ((uint32_t)0x00000000)
#define RCC_MCOSource_SYSCLK        ((uint32_t)0x01000000)
#define RCC_MCOSource_PLL2R         ((uint32_t)0x02000000)
#define RCC_MCOSource_HSI16         ((uint32_t)0x03000000)
#define RCC_MCOSource_HSE           ((uint32_t)0x04000000)
#define RCC_MCOSource_PLLP          ((uint32_t)0x05000000)
#define RCC_MCOSource_LSI           ((uint32_t)0x06000000)
#define RCC_MCOSource_LSE           ((uint32_t)0x07000000)
#define RCC_MCOSource_HSI48         ((uint32_t)0x08000000)
#define IS_RCC_MCO_SOURCE(SRC)     (((SRC) == RCC_MCOSource_NoClock) || ((SRC) == RCC_MCOSource_SYSCLK) || \
                                    ((SRC) == RCC_MCOSource_PLL2R)   || ((SRC) == RCC_MCOSource_HSI16)  || \
                                    ((SRC) == RCC_MCOSource_HSE)     || ((SRC) == RCC_MCOSource_PLLP)   || \
                                    ((SRC) == RCC_MCOSource_LSI)     || ((SRC) == RCC_MCOSource_LSE)    || \
                                    ((SRC) == RCC_MCOSource_HSI48))
/**
  * @}
  */

/** @defgroup RCC_MCOPrescaler_Select
  * @{
  */
#define RCC_MCOPrescaler_1          ((uint32_t)0x00000000)
#define RCC_MCOPrescaler_2          ((uint32_t)0x10000000)
#define RCC_MCOPrescaler_4          ((uint32_t)0x20000000)
#define RCC_MCOPrescaler_8          ((uint32_t)0x30000000)
#define RCC_MCOPrescaler_16         ((uint32_t)0x40000000)
#define RCC_MCOPrescaler_32         ((uint32_t)0x50000000)
#define RCC_MCOPrescaler_64         ((uint32_t)0x60000000)
#define RCC_MCOPrescaler_128        ((uint32_t)0x70000000)
#define IS_RCC_MCO_PRESCALER(PRE)  (((PRE) == RCC_MCOPrescaler_1)  || ((PRE) == RCC_MCOPrescaler_2)  || \
                                    ((PRE) == RCC_MCOPrescaler_4)  || ((PRE) == RCC_MCOPrescaler_8)  || \
                                    ((PRE) == RCC_MCOPrescaler_16) || ((PRE) == RCC_MCOPrescaler_32) || \
                                    ((PRE) == RCC_MCOPrescaler_64) || ((PRE) == RCC_MCOPrescaler_128))
/**
  * @}
  */

/** @defgroup RCC_apbclk_division_factor(APBCLK=HCLK/DIV)
  * @{
  */
#define  RCC_HCLK_DIV1               ((uint32_t)0x00000000)
#define  RCC_HCLK_DIV2               ((uint32_t)0x00000004)
#define  RCC_HCLK_DIV4               ((uint32_t)0x00000005)
#define  RCC_HCLK_DIV8               ((uint32_t)0x00000006)
#define  RCC_HCLK_DIV16              ((uint32_t)0x00000007)
#define IS_RCC_PCLK(PCLK)           (((PCLK) == RCC_HCLK_DIV1) || ((PCLK) == RCC_HCLK_DIV2) || \
                                     ((PCLK) == RCC_HCLK_DIV4) || ((PCLK) == RCC_HCLK_DIV8) || \
                                     ((PCLK) == RCC_HCLK_DIV16))
/**
  * @}
  */

/** @defgroup RCC_AHB_Clock_Source(HCLK=SYSCLK/HPREDIV)
  * @{
  */

#define RCC_SYSCLK_DIV1                  RCC_CFGR_HPRE_DIV1
#define RCC_SYSCLK_DIV2                  RCC_CFGR_HPRE_DIV2
#define RCC_SYSCLK_DIV4                  RCC_CFGR_HPRE_DIV4
#define RCC_SYSCLK_DIV8                  RCC_CFGR_HPRE_DIV8
#define RCC_SYSCLK_DIV16                 RCC_CFGR_HPRE_DIV16
#define RCC_SYSCLK_DIV64                 RCC_CFGR_HPRE_DIV64
#define RCC_SYSCLK_DIV128                RCC_CFGR_HPRE_DIV128
#define RCC_SYSCLK_DIV256                RCC_CFGR_HPRE_DIV256
#define RCC_SYSCLK_DIV512                RCC_CFGR_HPRE_DIV512
#define IS_RCC_HCLK(HCLK) (((HCLK) == RCC_SYSCLK_DIV1)   || ((HCLK) == RCC_SYSCLK_DIV2)   || \
                           ((HCLK) == RCC_SYSCLK_DIV4)   || ((HCLK) == RCC_SYSCLK_DIV8)   || \
                           ((HCLK) == RCC_SYSCLK_DIV16)  || ((HCLK) == RCC_SYSCLK_DIV64)  || \
                           ((HCLK) == RCC_SYSCLK_DIV128) || ((HCLK) == RCC_SYSCLK_DIV256) || \
                           ((HCLK) == RCC_SYSCLK_DIV512))
/**
  * @}
  */

/** @defgroup RCC_SYSCLK_SOURCE
  * @{
  */

#define RCC_SYSCLKSource_HSI16         RCC_CFGR_SW_HSI
#define RCC_SYSCLKSource_HSE           RCC_CFGR_SW_HSE
#define RCC_SYSCLKSource_PLLCLK        RCC_CFGR_SW_PLL
#define IS_RCC_SYSCLK_SOURCE(SRC)    (((SRC) == RCC_SYSCLKSource_HSI16) || \
                                      ((SRC) == RCC_SYSCLKSource_HSE)   || \
                                      ((SRC) == RCC_SYSCLKSource_PLLCLK))
/**
  * @}
  */

//RCC_CIR_REG
/** @defgroup RCC_Interrupt_Source
  * @{
  */
#define RCC_ITCLR_CSS                     RCC_CIR_CSSC
#define RCC_ITCLR_PLL2RDY                 RCC_CIR_PLL2RDYC
#define RCC_ITCLR_PLLRDY                  RCC_CIR_PLLRDYC
#define RCC_ITCLR_HSERDY                  RCC_CIR_HSERDYC
#define RCC_ITCLR_HSI48RDY                RCC_CIR_HSI48RDYC
#define RCC_ITCLR_HSIRDY                  RCC_CIR_HSIRDYC
#define RCC_ITCLR_LSERDY                  RCC_CIR_LSERDYC
#define RCC_ITCLR_LSIRDY                  RCC_CIR_LSIRDYC
#define IS_RCC_ITCLR(ITCLR)   (((ITCLR) == RCC_ITCLR_LSIRDY)  || ((ITCLR) == RCC_ITCLR_LSERDY)   || \
                               ((ITCLR) == RCC_ITCLR_HSIRDY)  || ((ITCLR) == RCC_ITCLR_HSI48RDY) || \
                               ((ITCLR) == RCC_ITCLR_HSERDY)  || ((ITCLR) == RCC_ITCLR_PLLRDY)   || \
                               ((ITCLR) == RCC_ITCLR_PLL2RDY) || ((ITCLR) == RCC_ITCLR_CSS))

#define RCC_ITEN_PLL2RDY                 RCC_CIR_PLL2RDYIE
#define RCC_ITEN_PLLRDY                  RCC_CIR_PLLRDYIE
#define RCC_ITEN_HSERDY                  RCC_CIR_HSERDYIE
#define RCC_ITEN_HSI48RDY                RCC_CIR_HSI48RDYIE
#define RCC_ITEN_HSIRDY                  RCC_CIR_HSIRDYIE
#define RCC_ITEN_LSERDY                  RCC_CIR_LSERDYIE
#define RCC_ITEN_LSIRDY                  RCC_CIR_LSIRDYIE
#define IS_RCC_ITEN(ITEN)     (((ITEN) == RCC_ITEN_LSIRDY)  || ((ITEN) == RCC_ITEN_LSERDY)   || \
                               ((ITEN) == RCC_ITEN_HSIRDY)  || ((ITEN) == RCC_ITEN_HSI48RDY) || \
                               ((ITEN) == RCC_ITEN_HSERDY)  || ((ITEN) == RCC_ITEN_PLLRDY)   || \
                               ((ITEN) == RCC_ITEN_PLL2RDY))

#define RCC_ITFLAG_CSS                     RCC_CIR_CSSF
#define RCC_ITFLAG_PLL2RDY                 RCC_CIR_PLL2RDYF
#define RCC_ITFLAG_PLLRDY                  RCC_CIR_PLLRDYF
#define RCC_ITFLAG_HSERDY                  RCC_CIR_HSERDYF
#define RCC_ITFLAG_HSI48RDY                RCC_CIR_HSI48RDYF
#define RCC_ITFLAG_HSIRDY                  RCC_CIR_HSIRDYF
#define RCC_ITFLAG_LSERDY                  RCC_CIR_LSERDYF
#define RCC_ITFLAG_LSIRDY                  RCC_CIR_LSIRDYF
#define IS_RCC_ITFLAG(ITFLAG) (((ITFLAG) == RCC_ITFLAG_LSIRDY)  || ((ITFLAG) == RCC_ITFLAG_LSERDY)   || \
                               ((ITFLAG) == RCC_ITFLAG_HSIRDY)  || ((ITFLAG) == RCC_ITFLAG_HSI48RDY) || \
                               ((ITFLAG) == RCC_ITFLAG_HSERDY)  || ((ITFLAG) == RCC_ITFLAG_PLLRDY)   || \
                               ((ITFLAG) == RCC_ITFLAG_PLL2RDY) || ((ITFLAG) == RCC_ITFLAG_CSS))
/**
  * @}
  */

//RCC_AHB1/2/3_PERIPH_RSTR_REG
/** @defgroup RCC_AHB1/2/3_Peripherals_Reset
  * @{
  */
#define RCC_AHB1PeriphRst_USBOTGHS             RCC_AHB1RSTR_OTGHSRST
#define RCC_AHB1PeriphRst_ETHMAC               RCC_AHB1RSTR_ETHMACRST
#define RCC_AHB1PeriphRst_DMA2                 RCC_AHB1RSTR_DMA2RST
#define RCC_AHB1PeriphRst_DMA1                 RCC_AHB1RSTR_DMA1RST
#define RCC_AHB1PeriphRst_CRC                  RCC_AHB1RSTR_CRCRST
#define RCC_AHB1PeriphRst_GPIOH                RCC_AHB1RSTR_GPIOHRST
#define RCC_AHB1PeriphRst_GPIOE                RCC_AHB1RSTR_GPIOERST
#define RCC_AHB1PeriphRst_GPIOD                RCC_AHB1RSTR_GPIODRST
#define RCC_AHB1PeriphRst_GPIOC                RCC_AHB1RSTR_GPIOCRST
#define RCC_AHB1PeriphRst_GPIOB                RCC_AHB1RSTR_GPIOBRST
#define RCC_AHB1PeriphRst_GPIOA                RCC_AHB1RSTR_GPIOARST
#define IS_RCC_AHB1RST_PERIPH(PERIPH)     (((PERIPH) == RCC_AHB1PeriphRst_USBOTGHS) || ((PERIPH) == RCC_AHB1PeriphRst_ETHMAC) || \
                                           ((PERIPH) == RCC_AHB1PeriphRst_DMA2)     || ((PERIPH) == RCC_AHB1PeriphRst_DMA1)   || \
                                           ((PERIPH) == RCC_AHB1PeriphRst_CRC)      || ((PERIPH) == RCC_AHB1PeriphRst_GPIOH)  || \
                                           ((PERIPH) == RCC_AHB1PeriphRst_GPIOE)    || ((PERIPH) == RCC_AHB1PeriphRst_GPIOD)  || \
                                           ((PERIPH) == RCC_AHB1PeriphRst_GPIOC)    || ((PERIPH) == RCC_AHB1PeriphRst_GPIOB)  || \
                                           ((PERIPH) == RCC_AHB1PeriphRst_GPIOA))

#define RCC_AHB2PeriphRst_USBOTGFS             RCC_AHB2RSTR_OTGFSRST
#define RCC_AHB2PeriphRst_RNG                  RCC_AHB2RSTR_RNGRST
#define IS_RCC_AHB2RST_PERIPH(PERIPH)    (((PERIPH) == RCC_AHB2PeriphRst_USBOTGFS) || ((PERIPH) == RCC_AHB2PeriphRst_RNG))

#define RCC_AHB3PeriphRst_QSPI                 RCC_AHB3RSTR_QSPIRST
#define RCC_AHB3PeriphRst_FMC                  RCC_AHB3RSTR_FMCRST
#define IS_RCC_AHB3RST_PERIPH(PERIPH)    (((PERIPH) == RCC_AHB3PeriphRst_QSPI) || ((PERIPH) == RCC_AHB3PeriphRst_FMC))
/**
  * @}
  */

//RCC_APB1/2_PERIPH_RSTR_REG
/** @defgroup RCC_APB1/2_Peripherals_Reset
  * @{
  */
#define RCC_APB1PeriphRst_UART7                RCC_APB1RSTR_UART7RST
#define RCC_APB1PeriphRst_DAC                  RCC_APB1RSTR_DACRST
#define RCC_APB1PeriphRst_PWR                  RCC_APB1RSTR_PWRRST
#define RCC_APB1PeriphRst_CAN4                 RCC_APB1RSTR_CAN4RST
#define RCC_APB1PeriphRst_CAN3                 RCC_APB1RSTR_CAN3RST
#define RCC_APB1PeriphRst_CAN2                 RCC_APB1RSTR_CAN2RST
#define RCC_APB1PeriphRst_CAN1                 RCC_APB1RSTR_CAN1RST
#define RCC_APB1PeriphRst_I2C3                 RCC_APB1RSTR_I2C3RST
#define RCC_APB1PeriphRst_I2C2                 RCC_APB1RSTR_I2C2RST
#define RCC_APB1PeriphRst_I2C1                 RCC_APB1RSTR_I2C1RST
#define RCC_APB1PeriphRst_UART5                RCC_APB1RSTR_UART5RST
#define RCC_APB1PeriphRst_UART4                RCC_APB1RSTR_UART4RST
#define RCC_APB1PeriphRst_UART3                RCC_APB1RSTR_UART3RST
#define RCC_APB1PeriphRst_UART2                RCC_APB1RSTR_UART2RST
#define RCC_APB1PeriphRst_LPUART               RCC_APB1RSTR_LPUARTRST
#define RCC_APB1PeriphRst_SPI3                 RCC_APB1RSTR_SPI3RST
#define RCC_APB1PeriphRst_SPI2                 RCC_APB1RSTR_SPI2RST
#define RCC_APB1PeriphRst_I2S3                 RCC_APB1RSTR_I2S3RST
#define RCC_APB1PeriphRst_I2S2                 RCC_APB1RSTR_I2S2RST
#define RCC_APB1PeriphRst_WWDG                 RCC_APB1RSTR_WWDGRST
#define RCC_APB1PeriphRst_AC97                 RCC_APB1RSTR_AC97RST
#define RCC_APB1PeriphRst_CRS                  RCC_APB1RSTR_CRSRST
#define RCC_APB1PeriphRst_TIM14                RCC_APB1RSTR_TIM14RST
#define RCC_APB1PeriphRst_TIM13                RCC_APB1RSTR_TIM13RST
#define RCC_APB1PeriphRst_TIM12                RCC_APB1RSTR_TIM12RST
#define RCC_APB1PeriphRst_TIM7                 RCC_APB1RSTR_TIM7RST
#define RCC_APB1PeriphRst_TIM6                 RCC_APB1RSTR_TIM6RST
#define RCC_APB1PeriphRst_TIM5                 RCC_APB1RSTR_TIM5RST
#define RCC_APB1PeriphRst_TIM4                 RCC_APB1RSTR_TIM4RST
#define RCC_APB1PeriphRst_TIM3                 RCC_APB1RSTR_TIM3RST
#define RCC_APB1PeriphRst_TIM2                 RCC_APB1RSTR_TIM2RST
#define IS_RCC_APB1RST_PERIPH(PERIPH)    (((PERIPH) == RCC_APB1PeriphRst_UART7)  || ((PERIPH) == RCC_APB1PeriphRst_DAC)   || \
                                          ((PERIPH) == RCC_APB1PeriphRst_PWR)    || ((PERIPH) == RCC_APB1PeriphRst_CAN4)  || \
                                          ((PERIPH) == RCC_APB1PeriphRst_CAN3)   || ((PERIPH) == RCC_APB1PeriphRst_CAN2)  || \
                                          ((PERIPH) == RCC_APB1PeriphRst_CAN1)   || ((PERIPH) == RCC_APB1PeriphRst_I2C3)  || \
                                          ((PERIPH) == RCC_APB1PeriphRst_I2C2)   || ((PERIPH) == RCC_APB1PeriphRst_I2C1)  || \
                                          ((PERIPH) == RCC_APB1PeriphRst_UART5)  || ((PERIPH) == RCC_APB1PeriphRst_UART4) || \
                                          ((PERIPH) == RCC_APB1PeriphRst_UART3)  || ((PERIPH) == RCC_APB1PeriphRst_UART2) || \
                                          ((PERIPH) == RCC_APB1PeriphRst_LPUART) || ((PERIPH) == RCC_APB1PeriphRst_SPI3)  || \
                                          ((PERIPH) == RCC_APB1PeriphRst_SPI2)   || ((PERIPH) == RCC_APB1PeriphRst_I2S3)  || \
                                          ((PERIPH) == RCC_APB1PeriphRst_I2S2)   || ((PERIPH) == RCC_APB1PeriphRst_WWDG)  || \
                                          ((PERIPH) == RCC_APB1PeriphRst_AC97)   || ((PERIPH) == RCC_APB1PeriphRst_CRS)   || \
                                          ((PERIPH) == RCC_APB1PeriphRst_TIM14)  || ((PERIPH) == RCC_APB1PeriphRst_TIM13) || \
                                          ((PERIPH) == RCC_APB1PeriphRst_TIM12)  || ((PERIPH) == RCC_APB1PeriphRst_TIM7)  || \
                                          ((PERIPH) == RCC_APB1PeriphRst_TIM6)   || ((PERIPH) == RCC_APB1PeriphRst_TIM5)  || \
                                          ((PERIPH) == RCC_APB1PeriphRst_TIM4)   || ((PERIPH) == RCC_APB1PeriphRst_TIM3)  || \
                                          ((PERIPH) == RCC_APB1PeriphRst_TIM2))

#define RCC_APB2PeriphRst_EQEP                 RCC_APB2RSTR_EQEPRST
#define RCC_APB2PeriphRst_ECAP                 RCC_APB2RSTR_ECAPRST
#define RCC_APB2PeriphRst_EPWM4                RCC_APB2RSTR_EPWM4RST
#define RCC_APB2PeriphRst_EPWM3                RCC_APB2RSTR_EPWM3RST
#define RCC_APB2PeriphRst_EPWM2                RCC_APB2RSTR_EPWM2RST
#define RCC_APB2PeriphRst_EPWM1                RCC_APB2RSTR_EPWM1RST
#define RCC_APB2PeriphRst_TIM11                RCC_APB2RSTR_TIM11RST
#define RCC_APB2PeriphRst_TIM10                RCC_APB2RSTR_TIM10RST
#define RCC_APB2PeriphRst_TIM9                 RCC_APB2RSTR_TIM9RST
#define RCC_APB2PeriphRst_LPTIM                RCC_APB2RSTR_LPTIMRST
#define RCC_APB2PeriphRst_SYSCFG               RCC_APB2RSTR_SYSCFGRST
#define RCC_APB2PeriphRst_SPI1                 RCC_APB2RSTR_SPI1RST
#define RCC_APB2PeriphRst_SDIO                 RCC_APB2RSTR_SDIORST
#define RCC_APB2PeriphRst_SPD                  RCC_APB2RSTR_SPDRST
#define RCC_APB2PeriphRst_ADC                  RCC_APB2RSTR_ADCRST
#define RCC_APB2PeriphRst_USART6               RCC_APB2RSTR_USART6RST
#define RCC_APB2PeriphRst_USART1               RCC_APB2RSTR_USART1RST
#define RCC_APB2PeriphRst_TIM8                 RCC_APB2RSTR_TIM8RST
#define RCC_APB2PeriphRst_TIM1                 RCC_APB2RSTR_TIM1RST
#define IS_RCC_APB2RST_PERIPH(PERIPH)    (((PERIPH) == RCC_APB2PeriphRst_EQEP)   ||  ((PERIPH) == RCC_APB2PeriphRst_ECAP)   || \
                                          ((PERIPH) == RCC_APB2PeriphRst_EPWM4)  ||  ((PERIPH) == RCC_APB2PeriphRst_EPWM3)  || \
                                          ((PERIPH) == RCC_APB2PeriphRst_EPWM2)  ||  ((PERIPH) == RCC_APB2PeriphRst_EPWM1)  || \
                                          ((PERIPH) == RCC_APB2PeriphRst_TIM11)  ||  ((PERIPH) == RCC_APB2PeriphRst_TIM10)  || \
                                          ((PERIPH) == RCC_APB2PeriphRst_TIM9)   ||  ((PERIPH) == RCC_APB2PeriphRst_LPTIM)  || \
                                          ((PERIPH) == RCC_APB2PeriphRst_SYSCFG) ||  ((PERIPH) == RCC_APB2PeriphRst_SPI1)   || \
                                          ((PERIPH) == RCC_APB2PeriphRst_SDIO)   ||  ((PERIPH) == RCC_APB2PeriphRst_SPD)    || \
                                          ((PERIPH) == RCC_APB2PeriphRst_ADC)    ||  ((PERIPH) == RCC_APB2PeriphRst_USART6) || \
                                          ((PERIPH) == RCC_APB2PeriphRst_USART1) ||  ((PERIPH) == RCC_APB2PeriphRst_TIM8)   || \
                                          ((PERIPH) == RCC_APB2PeriphRst_TIM1))
/**
  * @}
  */

//RCC_AHB1/2/3_PERIPH_CLKEN_REG
/** @defgroup RCC_AHB1/2/3_Peripherals_Clken
  * @{
  */
#define RCC_AHB1Periph_USBOTGHS             RCC_AHB1ENR_OTGHSEN
#define RCC_AHB1Periph_ETHMACPTP            RCC_AHB1ENR_ETHMACPTPEN
#define RCC_AHB1Periph_ETHMACRX             RCC_AHB1ENR_ETHMACRXEN
#define RCC_AHB1Periph_ETHMACTX             RCC_AHB1ENR_ETHMACTXEN
#define RCC_AHB1Periph_ETHMAC               RCC_AHB1ENR_ETHMACEN
#define RCC_AHB1Periph_DMA2                 RCC_AHB1ENR_DMA2EN
#define RCC_AHB1Periph_DMA1                 RCC_AHB1ENR_DMA1EN
#define RCC_AHB1Periph_CCMDATARAM           RCC_AHB1ENR_CCMDATARAMEN
#define RCC_AHB1Periph_BKPSRAM              RCC_AHB1ENR_BKPSRAMEN
#define RCC_AHB1Periph_CRC                  RCC_AHB1ENR_CRCEN
#define RCC_AHB1Periph_GPIOH                RCC_AHB1ENR_GPIOHEN
#define RCC_AHB1Periph_GPIOE                RCC_AHB1ENR_GPIOEEN
#define RCC_AHB1Periph_GPIOD                RCC_AHB1ENR_GPIODEN
#define RCC_AHB1Periph_GPIOC                RCC_AHB1ENR_GPIOCEN
#define RCC_AHB1Periph_GPIOB                RCC_AHB1ENR_GPIOBEN
#define RCC_AHB1Periph_GPIOA                RCC_AHB1ENR_GPIOAEN
#define IS_RCC_AHB1_PERIPH(PERIPH)      (((PERIPH) == RCC_AHB1Periph_USBOTGHS)  ||  ((PERIPH) == RCC_AHB1Periph_ETHMACPTP)   || \
                                         ((PERIPH) == RCC_AHB1Periph_ETHMACRX)  ||  ((PERIPH) == RCC_AHB1Periph_ETHMACTX)    || \
                                         ((PERIPH) == RCC_AHB1Periph_ETHMAC)    ||  ((PERIPH) == RCC_AHB1Periph_DMA2)        || \
                                         ((PERIPH) == RCC_AHB1Periph_DMA1)      ||  ((PERIPH) == RCC_AHB1Periph_CCMDATARAM)  || \
                                         ((PERIPH) == RCC_AHB1Periph_BKPSRAM)   ||  ((PERIPH) == RCC_AHB1Periph_CRC)         || \
                                         ((PERIPH) == RCC_AHB1Periph_GPIOH)     ||  ((PERIPH) == RCC_AHB1Periph_GPIOE)       || \
                                         ((PERIPH) == RCC_AHB1Periph_GPIOD)     ||  ((PERIPH) == RCC_AHB1Periph_GPIOC)       || \
                                         ((PERIPH) == RCC_AHB1Periph_GPIOB)     ||  ((PERIPH) == RCC_AHB1Periph_GPIOA))

#define RCC_AHB2Periph_USBOTGFS          RCC_AHB2ENR_OTGFSEN
#define RCC_AHB2periph_RNG               RCC_AHB2ENR_RNGEN
#define IS_RCC_AHB2_PERIPH(PERIPH)      (((PERIPH) == RCC_AHB2Periph_USBOTGFS)  ||  ((PERIPH) == RCC_AHB2periph_RNG))

#define RCC_AHB3Periph_QSPI              RCC_AHB3ENR_QSPIEN
#define RCC_AHB3Periph_FMC               RCC_AHB3ENR_FMCEN
#define IS_RCC_AHB3_PERIPH(PERIPH)      (((PERIPH) == RCC_AHB3Periph_QSPI)      ||  ((PERIPH) == RCC_AHB3Periph_FMC))
/**
  * @}
  */

//RCC_APB1/2_PERIPH_CLKEN_REG
/** @defgroup RCC_APB1/2_Peripherals_Clken
  * @{
  */
#define RCC_APB1Periph_UART7                RCC_APB1ENR_UART7EN
#define RCC_APB1Periph_RAMP                 RCC_APB1ENR_RAMPEN
#define RCC_APB1Periph_DAC                  RCC_APB1ENR_DACEN
#define RCC_APB1Periph_PWR                  RCC_APB1ENR_PWREN
#define RCC_APB1Periph_CAN4                 RCC_APB1ENR_CAN4EN
#define RCC_APB1Periph_CAN3                 RCC_APB1ENR_CAN3EN
#define RCC_APB1Periph_CAN2                 RCC_APB1ENR_CAN2EN
#define RCC_APB1Periph_CAN1                 RCC_APB1ENR_CAN1EN
#define RCC_APB1Periph_I2C3                 RCC_APB1ENR_I2C3EN
#define RCC_APB1Periph_I2C2                 RCC_APB1ENR_I2C2EN
#define RCC_APB1Periph_I2C1                 RCC_APB1ENR_I2C1EN
#define RCC_APB1Periph_UART5                RCC_APB1ENR_UART5EN
#define RCC_APB1Periph_UART4                RCC_APB1ENR_UART4EN
#define RCC_APB1Periph_UART3                RCC_APB1ENR_UART3EN
#define RCC_APB1Periph_UART2                RCC_APB1ENR_UART2EN
#define RCC_APB1Periph_LPUART               RCC_APB1ENR_LPUARTEN
#define RCC_APB1Periph_SPI3                 RCC_APB1ENR_SPI3EN
#define RCC_APB1Periph_SPI2                 RCC_APB1ENR_SPI2EN
#define RCC_APB1Periph_I2S3                 RCC_APB1ENR_I2S3EN
#define RCC_APB1Periph_I2S2                 RCC_APB1ENR_I2S2EN
#define RCC_APB1Periph_WWDG                 RCC_APB1ENR_WWDGEN
#define RCC_APB1Periph_AC97                 RCC_APB1ENR_AC97EN
#define RCC_APB1Periph_CRS                  RCC_APB1ENR_CRSEN
#define RCC_APB1Periph_TIM14                RCC_APB1ENR_TIM14EN
#define RCC_APB1Periph_TIM13                RCC_APB1ENR_TIM13EN
#define RCC_APB1Periph_TIM12                RCC_APB1ENR_TIM12EN
#define RCC_APB1Periph_TIM7                 RCC_APB1ENR_TIM7EN
#define RCC_APB1Periph_TIM6                 RCC_APB1ENR_TIM6EN
#define RCC_APB1Periph_TIM5                 RCC_APB1ENR_TIM5EN
#define RCC_APB1Periph_TIM4                 RCC_APB1ENR_TIM4EN
#define RCC_APB1Periph_TIM3                 RCC_APB1ENR_TIM3EN
#define RCC_APB1Periph_TIM2                 RCC_APB1ENR_TIM2EN
#define IS_RCC_APB1_PERIPH(PERIPH)      (((PERIPH) == RCC_APB1Periph_UART7)  ||  ((PERIPH) == RCC_APB1Periph_RAMP)  || \
                                         ((PERIPH) == RCC_APB1Periph_DAC)    ||  ((PERIPH) == RCC_APB1Periph_PWR)   || \
                                         ((PERIPH) == RCC_APB1Periph_CAN4)   ||  ((PERIPH) == RCC_APB1Periph_CAN3)  || \
                                         ((PERIPH) == RCC_APB1Periph_CAN2)   ||  ((PERIPH) == RCC_APB1Periph_CAN1)  || \
                                         ((PERIPH) == RCC_APB1Periph_I2C3)   ||  ((PERIPH) == RCC_APB1Periph_I2C2)  || \
                                         ((PERIPH) == RCC_APB1Periph_I2C1)   ||  ((PERIPH) == RCC_APB1Periph_UART5) || \
                                         ((PERIPH) == RCC_APB1Periph_UART4)  ||  ((PERIPH) == RCC_APB1Periph_UART3) || \
                                         ((PERIPH) == RCC_APB1Periph_UART2)  ||  ((PERIPH) == RCC_APB1Periph_LPUART)|| \
                                         ((PERIPH) == RCC_APB1Periph_SPI3)   ||  ((PERIPH) == RCC_APB1Periph_SPI2)  || \
                                         ((PERIPH) == RCC_APB1Periph_I2S3)   ||  ((PERIPH) == RCC_APB1Periph_I2S2)  || \
                                         ((PERIPH) == RCC_APB1Periph_WWDG)   ||  ((PERIPH) == RCC_APB1Periph_AC97)  || \
                                         ((PERIPH) == RCC_APB1Periph_CRS)    ||  ((PERIPH) == RCC_APB1Periph_TIM14) || \
                                         ((PERIPH) == RCC_APB1Periph_TIM13)  ||  ((PERIPH) == RCC_APB1Periph_TIM12) || \
                                         ((PERIPH) == RCC_APB1Periph_TIM7)   ||  ((PERIPH) == RCC_APB1Periph_TIM6)  || \
                                         ((PERIPH) == RCC_APB1Periph_TIM5)   ||  ((PERIPH) == RCC_APB1Periph_TIM4)  || \
                                         ((PERIPH) == RCC_APB1Periph_TIM3)   ||  ((PERIPH) == RCC_APB1Periph_TIM2))

#define RCC_APB2Periph_TBCLK                RCC_APB2ENR_TBCLKSYNC
#define RCC_APB2Periph_EQEP                 RCC_APB2ENR_EQEPEN
#define RCC_APB2Periph_ECAP                 RCC_APB2ENR_ECAPEN
#define RCC_APB2Periph_EPWM4                RCC_APB2ENR_EPWM4EN
#define RCC_APB2Periph_EPWM3                RCC_APB2ENR_EPWM3EN
#define RCC_APB2Periph_EPWM2                RCC_APB2ENR_EPWM2EN
#define RCC_APB2Periph_EPWM1                RCC_APB2ENR_EPWM1EN
#define RCC_APB2Periph_TIM11                RCC_APB2ENR_TIM11EN
#define RCC_APB2Periph_TIM10                RCC_APB2ENR_TIM10EN
#define RCC_APB2Periph_TIM9                 RCC_APB2ENR_TIM9EN
#define RCC_APB2Periph_LPTIM                RCC_APB2ENR_LPTIMEN
#define RCC_APB2Periph_SYSCFG               RCC_APB2ENR_SYSCFGEN
#define RCC_APB2Periph_SPI1                 RCC_APB2ENR_SPI1EN
#define RCC_APB2Periph_SDIO                 RCC_APB2ENR_SDIOEN
#define RCC_APB2Periph_SPD                  RCC_APB2ENR_SPDEN
#define RCC_APB2Periph_ADC                  RCC_APB2ENR_ADCEN
#define RCC_APB2Periph_USART6               RCC_APB2ENR_USART6EN
#define RCC_APB2Periph_USART1               RCC_APB2ENR_USART1EN
#define RCC_APB2Periph_TIM8                 RCC_APB2ENR_TIM8EN
#define RCC_APB2Periph_TIM1                 RCC_APB2ENR_TIM1EN
#define IS_RCC_APB2_PERIPH(PERIPH)      (((PERIPH) == RCC_APB2Periph_TBCLK)  ||  ((PERIPH) == RCC_APB2Periph_EQEP)   || \
                                         ((PERIPH) == RCC_APB2Periph_ECAP)   ||  ((PERIPH) == RCC_APB2Periph_EPWM4)  || \
                                         ((PERIPH) == RCC_APB2Periph_EPWM3)  ||  ((PERIPH) == RCC_APB2Periph_EPWM2)  || \
                                         ((PERIPH) == RCC_APB2Periph_EPWM1)  ||  ((PERIPH) == RCC_APB2Periph_TIM11)  || \
                                         ((PERIPH) == RCC_APB2Periph_TIM10)  ||  ((PERIPH) == RCC_APB2Periph_TIM9)   || \
                                         ((PERIPH) == RCC_APB2Periph_LPTIM)  ||  ((PERIPH) == RCC_APB2Periph_SYSCFG) || \
                                         ((PERIPH) == RCC_APB2Periph_SPI1)   ||  ((PERIPH) == RCC_APB2Periph_SDIO)   || \
                                         ((PERIPH) == RCC_APB2Periph_SPD)    ||  ((PERIPH) == RCC_APB2Periph_ADC)    || \
                                         ((PERIPH) == RCC_APB2Periph_USART6) ||  ((PERIPH) == RCC_APB2Periph_USART1) || \
                                         ((PERIPH) == RCC_APB2Periph_TIM8)   ||  ((PERIPH) == RCC_APB2Periph_TIM1))
/**
  * @}
  */

//RCC_AHB1/2/3_PERIPH_LPCLKEN_REG
/** @defgroup RCC_AHB1/2/3_Peripherals_Lpclken
  * @{
  */
#define RCC_AHB1PeriphLpen_USBOTGHS         RCC_AHB1LPENR_OTGHSLPEN
#define RCC_AHB1PeriphLpen_ETHMACPTP        RCC_AHB1LPENR_ETHMACPTPLPEN
#define RCC_AHB1PeriphLpen_ETHMACRX         RCC_AHB1LPENR_ETHMACRXLPEN
#define RCC_AHB1PeriphLpen_ETHMACTX         RCC_AHB1LPENR_ETHMACTXLPEN
#define RCC_AHB1PeriphLpen_ETHMAC           RCC_AHB1LPENR_ETHMACLPEN
#define RCC_AHB1PeriphLpen_DMA2             RCC_AHB1LPENR_DMA2LPEN
#define RCC_AHB1PeriphLpen_DMA1             RCC_AHB1LPENR_DMA1LPEN
#define RCC_AHB1PeriphLpen_BKPSRAM          RCC_AHB1LPENR_BKPSRAMLPEN
#define RCC_AHB1PeriphLpen_SRAM2            RCC_AHB1LPENR_SRAM2LPEN
#define RCC_AHB1PeriphLpen_SRAM1            RCC_AHB1LPENR_SRAM1LPEN
#define RCC_AHB1PeriphLpen_CRC              RCC_AHB1LPENR_CRCLPEN
#define RCC_AHB1PeriphLpen_GPIOH            RCC_AHB1LPENR_GPIOHLPEN
#define RCC_AHB1PeriphLpen_GPIOE            RCC_AHB1LPENR_GPIOELPEN
#define RCC_AHB1PeriphLpen_GPIOD            RCC_AHB1LPENR_GPIODLPEN
#define RCC_AHB1PeriphLpen_GPIOC            RCC_AHB1LPENR_GPIOCLPEN
#define RCC_AHB1PeriphLpen_GPIOB            RCC_AHB1LPENR_GPIOBLPEN
#define RCC_AHB1PeriphLpen_GPIOA            RCC_AHB1LPENR_GPIOALPEN
#define IS_RCC_AHB1LP_PERIPH(PERIPH)     (((PERIPH) == RCC_AHB1PeriphLpen_USBOTGHS) || ((PERIPH) == RCC_AHB1PeriphLpen_ETHMACPTP) || \
                                          ((PERIPH) == RCC_AHB1PeriphLpen_ETHMACRX) || ((PERIPH) == RCC_AHB1PeriphLpen_ETHMACTX)  || \
                                          ((PERIPH) == RCC_AHB1PeriphLpen_ETHMAC)   || ((PERIPH) == RCC_AHB1PeriphLpen_DMA2)      || \
                                          ((PERIPH) == RCC_AHB1PeriphLpen_DMA1)     || ((PERIPH) == RCC_AHB1PeriphLpen_BKPSRAM)   || \
                                          ((PERIPH) == RCC_AHB1PeriphLpen_SRAM2)    || ((PERIPH) == RCC_AHB1PeriphLpen_SRAM1)     || \
                                          ((PERIPH) == RCC_AHB1PeriphLpen_CRC)      || ((PERIPH) == RCC_AHB1PeriphLpen_GPIOH)     || \
                                          ((PERIPH) == RCC_AHB1PeriphLpen_GPIOE)    || ((PERIPH) == RCC_AHB1PeriphLpen_GPIOD)     || \
                                          ((PERIPH) == RCC_AHB1PeriphLpen_GPIOC)    || ((PERIPH) == RCC_AHB1PeriphLpen_GPIOB)     || \
                                          ((PERIPH) == RCC_AHB1PeriphLpen_GPIOA))

#define RCC_AHB2PeriphLpen_USBOTGFS         RCC_AHB2LPENR_OTGFSLPEN
#define RCC_AHB2PeriphLpen_RNG              RCC_AHB2LPENR_RNGLPEN
#define IS_RCC_AHB2LP_PERIPH(PERIPH)     (((PERIPH) == RCC_AHB2PeriphLpen_USBOTGFS)  ||  ((PERIPH) == RCC_AHB2PeriphLpen_RNG))

#define RCC_AHB3PeriphLpen_QSPI             RCC_AHB3LPENR_QSPILPEN
#define RCC_AHB3PeriphLpen_FMC              RCC_AHB3LPENR_FMCLPEN
#define IS_RCC_AHB3LP_PERIPH(PERIPH)     (((PERIPH) == RCC_AHB3PeriphLpen_QSPI)  ||  ((PERIPH) == RCC_AHB3PeriphLpen_FMC))
/**
  * @}
  */

//RCC_APB1/2_PERIPH_LPCLKEN_REG
/** @defgroup RCC_APB1/2_Peripherals_Lpclken
  * @{
  */
#define RCC_APB1PeriphLpen_UART7               RCC_APB1LPENR_UART7LPEN
#define RCC_APB1PeriphLpen_RAMP                RCC_APB1LPENR_RAMPLPEN
#define RCC_APB1PeriphLpen_DAC                 RCC_APB1LPENR_DACLPEN
#define RCC_APB1PeriphLpen_PWR                 RCC_APB1LPENR_PWRLPEN
#define RCC_APB1PeriphLpen_CAN4                RCC_APB1LPENR_CAN4LPEN
#define RCC_APB1PeriphLpen_CAN3                RCC_APB1LPENR_CAN3LPEN
#define RCC_APB1PeriphLpen_CAN2                RCC_APB1LPENR_CAN2LPEN
#define RCC_APB1PeriphLpen_CAN1                RCC_APB1LPENR_CAN1LPEN
#define RCC_APB1PeriphLpen_I2C3                RCC_APB1LPENR_I2C3LPEN
#define RCC_APB1PeriphLpen_I2C2                RCC_APB1LPENR_I2C2LPEN
#define RCC_APB1PeriphLpen_I2C1                RCC_APB1LPENR_I2C1LPEN
#define RCC_APB1PeriphLpen_UART5               RCC_APB1LPENR_UART5LPEN
#define RCC_APB1PeriphLpen_UART4               RCC_APB1LPENR_UART4LPEN
#define RCC_APB1PeriphLpen_UART3               RCC_APB1LPENR_UART3LPEN
#define RCC_APB1PeriphLpen_UART2               RCC_APB1LPENR_UART2LPEN
#define RCC_APB1PeriphLpen_LPUART              RCC_APB1LPENR_LPUARTLPEN
#define RCC_APB1PeriphLpen_SPI3                RCC_APB1LPENR_SPI3LPEN
#define RCC_APB1PeriphLpen_SPI2                RCC_APB1LPENR_SPI2LPEN
#define RCC_APB1PeriphLpen_I2S3                RCC_APB1LPENR_I2S3LPEN
#define RCC_APB1PeriphLpen_I2S2                RCC_APB1LPENR_I2S2LPEN
#define RCC_APB1PeriphLpen_WWDG                RCC_APB1LPENR_WWDGLPEN
#define RCC_APB1PeriphLpen_AC97                RCC_APB1LPENR_AC97LPEN
#define RCC_APB1PeriphLpen_CRS                 RCC_APB1LPENR_CRSLPEN
#define RCC_APB1PeriphLpen_TIM14               RCC_APB1LPENR_TIM14LPEN
#define RCC_APB1PeriphLpen_TIM13               RCC_APB1LPENR_TIM13LPEN
#define RCC_APB1PeriphLpen_TIM12               RCC_APB1LPENR_TIM12LPEN
#define RCC_APB1PeriphLpen_TIM7                RCC_APB1LPENR_TIM7LPEN
#define RCC_APB1PeriphLpen_TIM6                RCC_APB1LPENR_TIM6LPEN
#define RCC_APB1PeriphLpen_TIM5                RCC_APB1LPENR_TIM5LPEN
#define RCC_APB1PeriphLpen_TIM4                RCC_APB1LPENR_TIM4LPEN
#define RCC_APB1PeriphLpen_TIM3                RCC_APB1LPENR_TIM3LPEN
#define RCC_APB1PeriphLpen_TIM2                RCC_APB1LPENR_TIM2LPEN
#define IS_RCC_APB1LP_PERIPH(PERIPH)    (((PERIPH) == RCC_APB1PeriphLpen_UART7)  ||  ((PERIPH) == RCC_APB1PeriphLpen_RAMP)  || \
                                         ((PERIPH) == RCC_APB1PeriphLpen_DAC)    ||  ((PERIPH) == RCC_APB1PeriphLpen_PWR)   || \
                                         ((PERIPH) == RCC_APB1PeriphLpen_CAN4)   ||  ((PERIPH) == RCC_APB1PeriphLpen_CAN3)  || \
                                         ((PERIPH) == RCC_APB1PeriphLpen_CAN2)   ||  ((PERIPH) == RCC_APB1PeriphLpen_CAN1)  || \
                                         ((PERIPH) == RCC_APB1PeriphLpen_I2C3)   ||  ((PERIPH) == RCC_APB1PeriphLpen_I2C2)  || \
                                         ((PERIPH) == RCC_APB1PeriphLpen_I2C1)   ||  ((PERIPH) == RCC_APB1PeriphLpen_UART5) || \
                                         ((PERIPH) == RCC_APB1PeriphLpen_UART4)  ||  ((PERIPH) == RCC_APB1PeriphLpen_UART3) || \
                                         ((PERIPH) == RCC_APB1PeriphLpen_UART2)  ||  ((PERIPH) == RCC_APB1PeriphLpen_LPUART)|| \
                                         ((PERIPH) == RCC_APB1PeriphLpen_SPI3)   ||  ((PERIPH) == RCC_APB1PeriphLpen_SPI2)  || \
                                         ((PERIPH) == RCC_APB1PeriphLpen_I2S3)   ||  ((PERIPH) == RCC_APB1PeriphLpen_I2S2)  || \
                                         ((PERIPH) == RCC_APB1PeriphLpen_WWDG)   ||  ((PERIPH) == RCC_APB1PeriphLpen_AC97)  || \
                                         ((PERIPH) == RCC_APB1PeriphLpen_CRS)    ||  ((PERIPH) == RCC_APB1PeriphLpen_TIM14) || \
                                         ((PERIPH) == RCC_APB1PeriphLpen_TIM13)  ||  ((PERIPH) == RCC_APB1PeriphLpen_TIM12) || \
                                         ((PERIPH) == RCC_APB1PeriphLpen_TIM7)   ||  ((PERIPH) == RCC_APB1PeriphLpen_TIM6)  || \
                                         ((PERIPH) == RCC_APB1PeriphLpen_TIM5)   ||  ((PERIPH) == RCC_APB1PeriphLpen_TIM4)  || \
                                         ((PERIPH) == RCC_APB1PeriphLpen_TIM3)   ||  ((PERIPH) == RCC_APB1PeriphLpen_TIM2))

#define RCC_APB2PeriphLpen_EQEP                RCC_APB2LPENR_EQEPLPEN
#define RCC_APB2PeriphLpen_ECAP                RCC_APB2LPENR_ECAPLPEN
#define RCC_APB2PeriphLpen_EPWM4               RCC_APB2LPENR_EPWM4LPEN
#define RCC_APB2PeriphLpen_EPWM3               RCC_APB2LPENR_EPWM3LPEN
#define RCC_APB2PeriphLpen_EPWM2               RCC_APB2LPENR_EPWM2LPEN
#define RCC_APB2PeriphLpen_EPWM1               RCC_APB2LPENR_EPWM1LPEN
#define RCC_APB2PeriphLpen_TIM11               RCC_APB2LPENR_TIM11LPEN
#define RCC_APB2PeriphLpen_TIM10               RCC_APB2LPENR_TIM10LPEN
#define RCC_APB2PeriphLpen_TIM9                RCC_APB2LPENR_TIM9LPEN
#define RCC_APB2PeriphLpen_LPTIM               RCC_APB2LPENR_LPTIMLPEN
#define RCC_APB2PeriphLpen_SYSCFG              RCC_APB2LPENR_SYSCFGLPEN
#define RCC_APB2PeriphLpen_SPI1                RCC_APB2LPENR_SPI1LPEN
#define RCC_APB2PeriphLpen_SDIO                RCC_APB2LPENR_SDIOLPEN
#define RCC_APB2PeriphLpen_SPD                 RCC_APB2LPENR_SPDLPEN
#define RCC_APB2PeriphLpen_ADC                 RCC_APB2LPENR_ADCLPEN
#define RCC_APB2PeriphLpen_USART6              RCC_APB2LPENR_USART6LPEN
#define RCC_APB2PeriphLpen_USART1              RCC_APB2LPENR_USART1LPEN
#define RCC_APB2PeriphLpen_TIM8                RCC_APB2LPENR_TIM8LPEN
#define RCC_APB2PeriphLpen_TIM1                RCC_APB2LPENR_TIM1LPEN
#define IS_RCC_APB2LP_PERIPH(PERIPH)    (((PERIPH) == RCC_APB2PeriphLpen_EQEP)   ||  ((PERIPH) == RCC_APB2PeriphLpen_ECAP)   || \
                                         ((PERIPH) == RCC_APB2PeriphLpen_EPWM4)  ||  ((PERIPH) == RCC_APB2PeriphLpen_EPWM3)  || \
                                         ((PERIPH) == RCC_APB2PeriphLpen_EPWM2)  ||  ((PERIPH) == RCC_APB2PeriphLpen_EPWM1)  || \
                                         ((PERIPH) == RCC_APB2PeriphLpen_TIM11)  ||  ((PERIPH) == RCC_APB2PeriphLpen_TIM10)  || \
                                         ((PERIPH) == RCC_APB2PeriphLpen_TIM9)   ||  ((PERIPH) == RCC_APB2PeriphLpen_LPTIM)  || \
                                         ((PERIPH) == RCC_APB2PeriphLpen_SYSCFG) ||  ((PERIPH) == RCC_APB2PeriphLpen_SPI1)   || \
                                         ((PERIPH) == RCC_APB2PeriphLpen_SDIO)   ||  ((PERIPH) == RCC_APB2PeriphLpen_SPD)    || \
                                         ((PERIPH) == RCC_APB2PeriphLpen_ADC)    ||  ((PERIPH) == RCC_APB2PeriphLpen_USART6) || \
                                         ((PERIPH) == RCC_APB2PeriphLpen_USART1) ||  ((PERIPH) == RCC_APB2PeriphLpen_TIM8)   || \
                                         ((PERIPH) == RCC_APB2PeriphLpen_TIM1))
/**
  * @}
  */

/** @defgroup RCC_QSPI_clock_source
  * @{
  */
#define RCC_QSPICLK_SYSCLK               ((uint32_t)0x00000000)
#define RCC_QSPICLK_HSI16                ((uint32_t)0x40000000)
#define RCC_QSPICLK_PLL1Q                ((uint32_t)0x80000000)
#define IS_RCC_QSPICLK(QSPICLK)         (((QSPICLK) == RCC_QSPICLK_SYSCLK) || ((QSPICLK) == RCC_QSPICLK_HSI16) || \
                                         ((QSPICLK) == RCC_QSPICLK_PLL1Q))
/**
  * @}
  */

/** @defgroup RCC_ADC_clock_source
  * @{
  */
/* These defines are obsolete and kept for legacy purpose only.
Proper ADC clock selection is done within ADC driver by mean of the ADC_ClockModeConfig() function */
#define RCC_ADCCLK_NOCLK                 ((uint32_t)0x00000000)
#define RCC_ADCCLK_PLL1R                 ((uint32_t)0x10000000)
#define RCC_ADCCLK_SYSCLK                ((uint32_t)0x20000000)
#define IS_RCC_ADCCLK(ADCCLK)           (((ADCCLK) == RCC_ADCCLK_NOCLK) || ((ADCCLK) == RCC_ADCCLK_PLL1R) || \
                                         ((ADCCLK) == RCC_ADCCLK_SYSCLK))
/**
  * @}
  */

/** @defgroup RCC_CAN_clock_source
  * @{
  */
#define RCC_CANCLK_HCLK                  ((uint32_t)0x00000000)
#define RCC_CANCLK_HCLK_DIV2             ((uint32_t)0x08000000)
#define RCC_CANCLK_HCLK_DIV4             ((uint32_t)0x09000000)
#define RCC_CANCLK_HCLK_DIV8             ((uint32_t)0x0A000000)
#define RCC_CANCLK_HCLK_DIV16            ((uint32_t)0x0B000000)
#define RCC_CANCLK_HCLK_DIV32            ((uint32_t)0x0C000000)
#define IS_RCC_CANCLK(CANCLK)           (((CANCLK) == RCC_CANCLK_HCLK)       || ((CANCLK) == RCC_CANCLK_HCLK_DIV2)  || \
                                         ((CANCLK) == RCC_CANCLK_HCLK_DIV4)  || ((CANCLK) == RCC_CANCLK_HCLK_DIV8)  || \
                                         ((CANCLK) == RCC_CANCLK_HCLK_DIV16) || ((CANCLK) == RCC_CANCLK_HCLK_DIV32))
/**
  * @}
  */

/** @defgroup RCC_LPTIM_clock_source
  * @{
  */
#define RCC_LPTIMCLK_PCLK                ((uint32_t)0x00000000)
#define RCC_LPTIMCLK_LSI                 ((uint32_t)0x00040000)
#define RCC_LPTIMCLK_HSI16               ((uint32_t)0x00080000)
#define RCC_LPTIMCLK_LSE                 ((uint32_t)0x000C0000)
#define IS_RCC_LPTIMCLK(LPTIMCLK)       (((LPTIMCLK) == RCC_LPTIMCLK_PCLK)   || ((LPTIMCLK) == RCC_LPTIMCLK_LSI)  || \
                                         ((LPTIMCLK) == RCC_LPTIMCLK_HSI16)  || ((LPTIMCLK) == RCC_LPTIMCLK_LSE))
/**
  * @}
  */

/** @defgroup RCC_I2C3_clock_source
  * @{
  */
#define RCC_I2C3CLK_PCLK                ((uint32_t)0x00000000)
#define RCC_I2C3CLK_SYSCLK              ((uint32_t)0x00010000)
#define RCC_I2C3CLK_HSI16               ((uint32_t)0x00020000)
#define IS_RCC_I2C3CLK(I2C3CLK)        (((I2C3CLK) == RCC_I2C3CLK_PCLK)   || ((I2C3CLK) == RCC_I2C3CLK_SYSCLK)  || \
                                        ((I2C3CLK) == RCC_I2C3CLK_HSI16))
/**
  * @}
  */

/** @defgroup RCC_I2C2_clock_source
  * @{
  */
#define RCC_I2C2CLK_PCLK                ((uint32_t)0x00000000)
#define RCC_I2C2CLK_SYSCLK              ((uint32_t)0x00004000)
#define RCC_I2C2CLK_HSI16               ((uint32_t)0x00008000)
#define IS_RCC_I2C2CLK(I2C2CLK)        (((I2C2CLK) == RCC_I2C2CLK_PCLK)   || ((I2C2CLK) == RCC_I2C2CLK_SYSCLK)  || \
                                        ((I2C2CLK) == RCC_I2C2CLK_HSI16))
/**
  * @}
  */

/** @defgroup RCC_I2C1_clock_source
  * @{
  */
#define RCC_I2C1CLK_PCLK                ((uint32_t)0x00000000)
#define RCC_I2C1CLK_SYSCLK              ((uint32_t)0x00001000)
#define RCC_I2C1CLK_HSI16               ((uint32_t)0x00002000)
#define IS_RCC_I2C1CLK(I2C1CLK)        (((I2C1CLK) == RCC_I2C1CLK_PCLK)   || ((I2C1CLK) == RCC_I2C1CLK_SYSCLK)  || \
                                        ((I2C1CLK) == RCC_I2C1CLK_HSI16))
/**
  * @}
  */

/** @defgroup RCC_LPUART_clock_source
  * @{
  */
#define RCC_LPUARTCLK_PCLK              ((uint32_t)0x00000000)
#define RCC_LPUARTCLK_LSE               ((uint32_t)0x00000800)
#define IS_RCC_LPUARTCLK(LPUARTCLK)    (((LPUARTCLK) == RCC_LPUARTCLK_PCLK)   || ((LPUARTCLK) == RCC_LPUARTCLK_LSE))
/**
  * @}
  */

/** @defgroup RCC_RNG_clock_div_factors
  * @{
  */
#define RCC_RNGCLK_DIV1                 ((uint32_t)0x00000000)
#define RCC_RNGCLK_DIV2                 ((uint32_t)0x00000100)
#define RCC_RNGCLK_DIV4                 ((uint32_t)0x00000200)
#define RCC_RNGCLK_DIV8                 ((uint32_t)0x00000300)
#define IS_RCC_RNGCLK_DIV(DIV)         (((DIV) == RCC_RNGCLK_DIV1)   || ((DIV) == RCC_RNGCLK_DIV2) || \
                                        ((DIV) == RCC_RNGCLK_DIV4)   || ((DIV) == RCC_RNGCLK_DIV8))
/**
  * @}
  */

/** @defgroup RCC_48M_clock_source
  * @{
  */
#define RCC_48MCLK_HSI48                ((uint32_t)0x00000000)
#define RCC_48MCLK_PLLQ                 ((uint32_t)0x00000080)
#define IS_RCC_48MCLK(RCC48MCLK)       (((RCC48MCLK) == RCC_48MCLK_HSI48)   || ((RCC48MCLK) == RCC_48MCLK_PLLQ))
/**
  * @}
  */

/** @defgroup RCC_EPWM_clock_source
  * @{
  */
#define RCC_EPWMCLK_SYSCLK              ((uint32_t)0x00000000)
#define RCC_EPWMCLK_SYSCLK_DIV2         ((uint32_t)0x00000020)
#define RCC_EPWMCLK_SYSCLK_DIV4         ((uint32_t)0x00000040)
#define IS_RCC_EPWMCLK(EPWMCLK)        (((EPWMCLK) == RCC_EPWMCLK_SYSCLK) || ((EPWMCLK) == RCC_EPWMCLK_SYSCLK_DIV2) || \
                                        ((EPWMCLK) == RCC_EPWMCLK_SYSCLK_DIV4))
/**
  * @}
  */

/** @defgroup RCC_EQEP_clock_source
  * @{
  */
#define RCC_EQEPCLK_SYSCLK              ((uint32_t)0x00000000)
#define RCC_EQEPCLK_SYSCLK_DIV2         ((uint32_t)0x00000008)
#define RCC_EQEPCLK_SYSCLK_DIV4         ((uint32_t)0x00000010)
#define IS_RCC_EQEPCLK(EQEPCLK)        (((EQEPCLK) == RCC_EQEPCLK_SYSCLK) || ((EQEPCLK) == RCC_EQEPCLK_SYSCLK_DIV2) || \
                                        ((EQEPCLK) == RCC_EQEPCLK_SYSCLK_DIV4))
/**
  * @}
  */

/** @defgroup RCC_ECAP_clock_source
  * @{
  */
#define RCC_ECAPCLK_SYSCLK              ((uint32_t)0x00000000)
#define RCC_ECAPCLK_SYSCLK_DIV2         ((uint32_t)0x00000002)
#define RCC_ECAPCLK_SYSCLK_DIV4         ((uint32_t)0x00000004)
#define IS_RCC_ECAPCLK(ECAPCLK)        (((ECAPCLK) == RCC_ECAPCLK_SYSCLK) || ((ECAPCLK) == RCC_ECAPCLK_SYSCLK_DIV2) || \
                                        ((ECAPCLK) == RCC_ECAPCLK_SYSCLK_DIV4))
/**
  * @}
  */

/** @defgroup RCC_I2S_clock_source
  * @{
  */
#define RCC_I2SCLK_PLL2Q               ((uint32_t)0x00000000)
#define RCC_I2SCLK_I2S_CLKIN           ((uint32_t)0x00000001)
#define IS_RCC_I2SCLK(I2SCLK)          (((I2SCLK) == RCC_I2SCLK_PLL2Q)   || ((I2SCLK) == RCC_I2SCLK_I2S_CLKIN))
/**
  * @}
  */


//RCC_BDCR_REG
/** @defgroup RCC_LSCO_clock_source
  * @brief
  * @{
  */
#define RCC_LSCOCLK_LSE               RCC_BDCR_LSCOSEL_LSE
#define RCC_LSCOCLK_LSI               RCC_BDCR_LSCOSEL_LSI
#define IS_RCC_LSCOCLK_SRC(SRC)      (((SRC) == RCC_LSCOCLK_LSE)   || ((SRC) == RCC_LSCOCLK_LSI))
/**
  * @}
  */

/** @defgroup RCC_LSCO_clock_enable
  * @brief
  * @{
  */
#define RCC_LSCOCLK_OFF                ((uint32_t)0x00000000)
#define RCC_LSCOCLK_ON                 ((uint32_t)0x01000000)
#define IS_RCC_LSCOCLK_STATUS(STATUS) (((STATUS) == RCC_LSCOCLK_OFF)   || ((STATUS) == RCC_LSCOCLK_ON))
/**
  * @}
  */

/** @defgroup RCC_RTC_soft_reset
  * @brief
  * @{
  */
#define RCC_RTC_BDRST_OFF             ((uint32_t)0x00000000)
#define RCC_RTC_BDRST_ON              ((uint32_t)0x00010000)
#define IS_RCC_RTC_BDRST(BDRST)      (((BDRST) == RCC_RTC_BDRST_OFF)   || ((BDRST) == RCC_RTC_BDRST_ON))
/**
  * @}
  */

/** @defgroup RCC_RTC_clock_enable
  * @brief
  * @{
  */
#define RCC_RTCCLK_OFF                ((uint32_t)0x00000000)
#define RCC_RTCCLK_ON                 ((uint32_t)0x00008000)
#define IS_RCC_RTCCLK_ENABLE(RTCCLK) (((RTCCLK) == RCC_RTCCLK_OFF)   || ((RTCCLK) == RCC_RTCCLK_ON))
/**
  * @}
  */

/** @defgroup RCC_RTC_clock_source
  * @brief
  * @{
  */
#define RCC_RTCCLKSource_HSE_Div32    RCC_BDCR_RTCSEL_HSEDIV32
#define RCC_RTCCLKSource_LSI          RCC_BDCR_RTCSEL_LSI
#define RCC_RTCCLKSource_LSE          RCC_BDCR_RTCSEL_LSE
#define IS_RCC_RTCCLK_SOURCE(SOURCE) (((SOURCE) == RCC_RTCCLKSource_HSE_Div32) || ((SOURCE) == RCC_RTCCLKSource_LSI) || \
                                      ((SOURCE) == RCC_RTCCLKSource_LSE))
/**
  * @}
  */

/** @defgroup RCC_LSE_drv
  * @brief
  * @{
  */
#define RCC_LSEDrive_Low             ((uint32_t)0x00000000)
#define RCC_LSEDrive_MediumLow       ((uint32_t)0x00000008)
#define RCC_LSEDrive_MediumHigh      ((uint32_t)0x00000010)
#define RCC_LSEDrive_High            ((uint32_t)0x00000018)
#define IS_RCC_LSE_DRIVE(DRIVE)     (((DRIVE) == RCC_LSEDrive_Low)        || ((DRIVE) == RCC_LSEDrive_MediumLow) || \
                                     ((DRIVE) == RCC_LSEDrive_MediumHigh) || ((DRIVE) == RCC_LSEDrive_High))
/**
  * @}
  */

/** @defgroup RCC_LSE_config
  * @brief
  * @{
  */
#define RCC_LSE_OFF                  ((uint32_t)0x00000000)
#define RCC_LSE_ON                   ((uint32_t)0x00000001)
#define RCC_LSE_BYP                  ((uint32_t)0x00000005)
#define IS_RCC_LSE(LSE)             (((LSE) == RCC_LSE_OFF)   || ((LSE) == RCC_LSE_ON)    || \
                                     ((LSE) == RCC_LSE_BYP))
/**
  * @}
  */


/** @defgroup RCC_LSI_clock_enable
  * @brief
  * @{
  */
#define RCC_LSI_OFF                  ((uint32_t)0x00000000)
#define RCC_LSI_ON                   ((uint32_t)0x00000001)
#define RCC_LSI_RDY                  ((uint32_t)0x00000002)
#define IS_RCC_LSI(LSI)             (((LSI) == RCC_LSI_OFF)   || ((LSI) == RCC_LSI_ON)    || \
                                     ((LSI) == RCC_LSI_RDY))
/**
  * @}
  */

//RCC_RAMCTL_REG
/** @defgroup RCC_RAMCTL_config
  * @brief
  * @{
  */
#define RCC_DCACHE_CTL               RCC_RAMCTL_DCHRAMSEL
#define RCC_ICACHE_CTL               RCC_RAMCTL_ICHRAMSEL
#define RCC_ETHMAC_CTL               RCC_RAMCTL_ETHRAMSEL
#define RCC_CAN_CTL                  RCC_RAMCTL_CANRAMSEL
#define RCC_USBHS_CTL                RCC_RAMCTL_UHSRAMSEL
#define RCC_USBFS_CTL                RCC_RAMCTL_UFSRAMSEL
#define IS_RCC_RAMCTL(CTL)          (((CTL) == RCC_DCACHE_CTL) || ((CTL) == RCC_ICACHE_CTL) || \
                                     ((CTL) == RCC_ETHMAC_CTL) || ((CTL) == RCC_CAN_CTL)    || \
                                     ((CTL) == RCC_USBHS_CTL)  || ((CTL) == RCC_USBFS_CTL))

#define RCC_RAM_CTL_SELF             ((uint32_t)0x00000000)
#define RCC_RAM_CTL_AHB              ((uint32_t)0x00000001)
#define IS_RCC_RAMCTL_SEL(SEL)      (((SEL) == RCC_RAM_CTL_SELF) || ((SEL) == RCC_RAM_CTL_AHB))

/**
  * @}
  */




/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Function used to set the RCC clock configuration to the default reset state */
void RCC_DeInit(void);

/* Internal/external clocks, PLL, CSS and MCO configuration functions *********/
void RCC_HSEConfig(uint32_t RCC_HSE);/* Function used config hse */
ErrorStatus RCC_WaitForHSEStartUp(void);/* Function used wait hserdy */
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue);/* Function usde hsi calibration value */
void RCC_HSICmd(FunctionalState NewState);/* Function usde enable hsi */
ErrorStatus RCC_WaitForHSIStartUp(void);/* Function used wait hsirdy */
void RCC_AdjustHSI48CalibrationValue(uint32_t HSI48CalibrationValue);/* Function used hsi48 calibration value */
void RCC_HSI48Cmd(FunctionalState NewState);/* Function used enable hsi48 */
ErrorStatus RCC_WaitForHSI48StartUp(void);/* Function used wait hsi48rdy */
void RCC_LSEConfig(uint32_t RCC_LSE);/* Function used config lse */
ErrorStatus RCC_WaitForLSEStartUp(void);/* Function used wait lserdy */
void RCC_LSEDriveConfig(uint32_t RCC_LSEDrive);/* Functoion usde config lse drive */
void RCC_LSICmd(FunctionalState NewState);/* Function used enable lsi */
ErrorStatus RCC_WaitForLSIStartUp(void);/* Function used wait lsirdy */
/* Function used config pllsource, pllm and plln */
void RCC_PLLVcoOutputConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLNul, uint32_t RCC_PLLMul);
void RCC_PLLROutputConfig(uint32_t RCC_PLLRStatus, uint32_t RCC_PLLR);/* Function used config pllren and pllr division value */
void RCC_PLLQOutputConfig(uint32_t RCC_PLLQStatus, uint32_t RCC_PLLQ);/* Function used config pllqen and pllq division value */
void RCC_PLLPOutputConfig(uint32_t RCC_PLLPStatus, uint32_t RCC_PLLP);/* Function used config pllpen and pllp division value */
/* Function used config pll2source, pll2m and pll2n */
void RCC_PLL2VcoOutputConfig(uint32_t RCC_PLL2Source, uint32_t RCC_PLL2Nul, uint32_t RCC_PLL2Mul);
void RCC_PLL2ROutputConfig(uint32_t RCC_PLL2RStatus, uint32_t RCC_PLL2R);/* Function used config pll2ren and pll2r division value */
void RCC_PLL2QOutputConfig(uint32_t RCC_PLL2QStatus, uint32_t RCC_PLL2Q);/* Function used config pll2qen and pll2q division value */
void RCC_PLLCmd(uint32_t RCC_PLLSelect, FunctionalState NewState);/* Function used enable pll and pll2 */
ErrorStatus RCC_WaitForPLLStartUp(void);/* Function used wait pllrdy */
ErrorStatus RCC_WaitForPLL2StartUp(void);/* Function used wait pll2rdy */
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);/* Function used enable css */
void RCC_MCOConfig(uint32_t RCC_MCOSource, uint32_t RCC_MCOPrescaler); /* Function used config MCO source and prescaler */

/* System, AHB and APB busses clocks configuration functions ******************/
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource);/* Function used config sysclk's source */
uint32_t RCC_GetSYSCLKSource(void);/* Function usde get sysclk's source */
void RCC_HCLKConfig(uint32_t RCC_SYSCLK);/* Function used config hclk's frequence  */
void RCC_PCLK1Config(uint32_t RCC_HCLK1);/* Function used config pclk1's frequence */
void RCC_PCLK2Config(uint32_t RCC_HCLK2);/* Function used config pclk2's frequence */
void RCC_QSPICLKConfig(uint32_t RCC_QSPICLK); /* Function used config qspi clk */
void RCC_ADCCLKConfig(uint32_t RCC_ADCCLK); /* Function used config adc123 clk */
void RCC_CANCLKConfig(uint32_t RCC_CANCLK); /* Function used config can clk */
void RCC_LPTIMCLKConfig(uint32_t RCC_LPTIMCLK); /* Function used config lptim clk */
void RCC_I2C3CLKConfig(uint32_t RCC_I2C3CLK); /* Function used config i2c3 clk */
void RCC_I2C2CLKConfig(uint32_t RCC_I2C2CLK); /* Function used config i2c2 clk */
void RCC_I2C1CLKConfig(uint32_t RCC_I2C1CLK); /* Function used config i2c1 clk */
void RCC_LPUARTCLKConfig(uint32_t RCC_LPUARTCLK);/* Function used config lpuart clk */
void RCC_RNGCLKDIVConfig(uint32_t RCC_RNGCLKDIV);/* Function used config rng division */
void RCC_48MCLKConfig(uint32_t RCC_48MCLK);/* Function used config 48MCLK's source */
void RCC_EPWMCLKConfig(uint32_t RCC_EPWMCLK);/* Function used config EPWM source */
void RCC_EQEPCLKConfig(uint32_t RCC_EQEPCLK);/* Function used config EQEP source */
void RCC_ECAPCLKConfig(uint32_t RCC_ECAPCLK);/* Function used config ECAP source */
void RCC_I2SCLKConfig(uint32_t RCC_I2SCLK);/* Function used config I2S source */
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);

/* Peripheral clocks configuration functions **********************************/
void RCC_LSCOCLKConfig(uint32_t RCC_LSCOCLKSource);
void RCC_LSCOCLKCmd(FunctionalState NewState);
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource);
void RCC_RTCCLKCmd(FunctionalState NewState);
void RCC_BackupResetCmd(FunctionalState NewState);
void RCC_AHB1PeriphClockCmd(uint32_t RCC_AHB1Periph, FunctionalState NewState);
void RCC_AHB2PeriphClockCmd(uint32_t RCC_AHB2Periph, FunctionalState NewState);
void RCC_AHB3PeriphClockCmd(uint32_t RCC_AHB3Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_AHB1PeriphLpenCmd(uint32_t RCC_AHB1PeriphLpen, FunctionalState NewState);
void RCC_AHB2PeriphLpenCmd(uint32_t RCC_AHB2PeriphLpen, FunctionalState NewState);
void RCC_AHB3PeriphLpenCmd(uint32_t RCC_AHB3PeriphLpen, FunctionalState NewState);
void RCC_APB1PeriphLpenCmd(uint32_t RCC_APB1PeriphLpen, FunctionalState NewState);
void RCC_APB2PeriphLpenCmd(uint32_t RCC_APB2PeriphLpen, FunctionalState NewState);
void RCC_AHB1PeriphResetCmd(uint32_t RCC_AHB1PeriphRst, FunctionalState NewState);
void RCC_AHB2PeriphResetCmd(uint32_t RCC_AHB2PeriphRst, FunctionalState NewState);
void RCC_AHB3PeriphResetCmd(uint32_t RCC_AHB3PeriphRst, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1PeriphRst, FunctionalState NewState);
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2PeriphRst, FunctionalState NewState);



/* Interrupts and flags management functions **********************************/
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG_REG, uint32_t RCC_FLAG);
void RCC_ClrRstFlag(void);
void RCC_ITConfig(uint32_t RCC_IT, FunctionalState NewState);
ITStatus RCC_GetITStatus(uint32_t RCC_IT_FLAG);
void RCC_ClearITPendingBit(uint32_t RCC_IT_CLR);
void RCC_RamCtrlSel(uint32_t RCC_RAM_CTL, uint32_t RCC_RAM_CTL_SEL);

#ifdef __cplusplus
}
#endif

#endif /* __FT32F0XX_RCC_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
