/**
  ******************************************************************************
  * @file    tae32g58xx.h
  * @author  MCD Application Team
  * @brief   CMSIS TAE32G58xx(Cortex-M4) Device Peripheral Access Layer Header File.
  *          This file contains all the peripheral register's definitions, bits
  *          definitions and memory mapping for TAE32G58xx devices.
  *
  *          This file contains:
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *           - Macros to access peripheral registers hardware
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32G58XX_H_
#define _TAE32G58XX_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/** @defgroup TAE_CMSIS TAE CMSIS
  * @brief    TAE CMSIS
  * @{
  */

/** @defgroup TAE32G58xx_Series TAE32G58xx Series
  * @brief    TAE32G58xx Series
  * @{
  */


/* -------  Start of section using anonymous unions and disabling warnings  ------- */
#if   defined (__CC_ARM)
#pragma push
#pragma anon_unions
#elif defined (__ICCARM__)
#pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc11-extensions"
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
/* anonymous unions are enabled by default */
#elif defined (__TMS470__)
/* anonymous unions are enabled by default */
#elif defined (__TASKING__)
#pragma warning 586
#elif defined (__CSMC__)
/* anonymous unions are enabled by default */
#else
#warning Not supported compiler type
#endif


/* Includes ------------------------------------------------------------------*/
//#define TAE32G58XX_REG_BIT_VERSION

#ifdef TAE32G58XX_REG_BIT_VERSION
#include "myChip_struct.h"
#else
#include "myChip.h"
#endif

#if ((__CM_CMSIS_VERSION_MAIN < 5) || \
    ((__CM_CMSIS_VERSION_MAIN == 5) && (__CM_CMSIS_VERSION_SUB < 4)) || \
    ((!defined(__CM_CMSIS_VERSION_MAIN)) || (!defined(__CM_CMSIS_VERSION_SUB))))
#error "Please upgrade the CMSIS component to at least version 5.0.4, \
or add the CMSIS library path provided by TAE: ../Drivers/CMSIS/Core/Include ."
#endif


/* Exported Types ------------------------------------------------------------*/
/** @defgroup TAE32G58xx_Exported_Types TAE32G58xx Exported Types
  * @brief    TAE32G58xx Exported Types
  * @{
  */

/** @defgroup TAE32G58xx_Peripheral_Registers_Structures_Alias TAE32G58xx Peripheral Registers Structures Alias
  * @brief    TAE32G58xx Peripheral Registers Structures Alias
  * @{
  */

/* Internal Class Peripheral */
typedef RCU_Type     RCU_TypeDef;               /*!< RCU Peripheral Registers Structures Alias      */
typedef SYSCTRL_Type SYSCTRL_TypeDef;           /*!< SYSCTRL Peripheral Registers Structures Alias  */
typedef FLASH_Type   EFLASH_TypeDef;            /*!< EFLASH Peripheral Registers Structures Alias   */
typedef GPIOA_Type   GPIO_TypeDef;              /*!< GPIO Peripheral Registers Structures Alias     */
typedef TMR9_Type    TMR_TypeDef;               /*!< TMR Peripheral Registers Structures Alias      */
typedef TMR6_Type    LPTMR_TypeDef;             /*!< LPTMR Peripheral Registers Structures Alias    */
typedef IIR0_Type    IIR_TypeDef;               /*!< IIR Peripheral Registers Structures Alias      */
typedef CORDIC_Type  CORDIC_TypeDef;            /*!< CORDIC Peripheral Registers Structures Alias   */
typedef QEI0_Type    QEI_TypeDef;               /*!< QEI Peripheral Registers Structures Alias      */
typedef IWDG_Type    IWDG_TypeDef;              /*!< IWDG Peripheral Registers Structures Alias     */
typedef WWDG_Type    WWDG_TypeDef;              /*!< WWDG Peripheral Registers Structures Alias     */

/* Interface Class Peripheral */
typedef I2C0_Type    I2C_TypeDef;               /*!< I2C Peripheral Registers Structures Alias      */
typedef UART0_Type   UART_TypeDef;              /*!< UART Peripheral Registers Structures Alias     */
typedef SPI0_Type    SPI_TypeDef;               /*!< SPI Peripheral Registers Structures Alias      */
typedef CAN0_Type    CAN_TypeDef;               /*!< CAN Peripheral Registers Structures Alias      */
typedef USB_Type     USB_TypeDef;               /*!< USB Peripheral Registers Structures Alias      */
typedef XIF_Type     XIF_TypeDef;               /*!< XIF Peripheral Registers Structures Alias      */

/* Analog Class Peripheral */
typedef ADC0_Type    ADC_TypeDef;               /*!< ADC Peripheral Registers Structures Alias      */
typedef DAC0_Type    DAC_TypeDef;               /*!< DAC Peripheral Registers Structures Alias      */
typedef CMP0_Type    CMP_TypeDef;               /*!< CMP Peripheral Registers Structures Alias      */
typedef PDM0_Type    PDM_TypeDef;               /*!< PDM Peripheral Registers Structures Alias      */

/**
  * @}
  */


/** @defgroup TAE32G58xx_Peripheral_Registers_Structures TAE32G58xx Peripheral Registers Structures
  * @brief    TAE32G58xx Peripheral Registers Structures
  * @{
  */

/**
  * @brief IIR Coef Registers Structure
  */
typedef struct {
    __IOM uint32_t GNB0R;           /*!< (@ 0x00000030) IIR GN B0COEF Register  */
    __IOM uint32_t GNB1R;           /*!< (@ 0x00000034) IIR GN B1COEF Register  */
    __IOM uint32_t GNB2R;           /*!< (@ 0x00000038) IIR GN B2COEF Register  */
    __IOM uint32_t GNB3R;           /*!< (@ 0x0000003C) IIR GN B3COEF Register  */
    __IOM uint32_t GNB4R;           /*!< (@ 0x00000040) IIR GN B4COEF Register  */
    __IOM uint32_t GNB5R;           /*!< (@ 0x00000044) IIR GN B5COEF Register  */
    __IM  uint32_t RESERVED[2];
    __IOM uint32_t GNA1R;           /*!< (@ 0x00000050) IIR GN A1COEF Register  */
    __IOM uint32_t GNA2R;           /*!< (@ 0x00000054) IIR GN A2COEF Register  */
    __IOM uint32_t GNA3R;           /*!< (@ 0x00000058) IIR GN A3COEF Register  */
    __IOM uint32_t GNA4R;           /*!< (@ 0x0000005C) IIR GN A4COEF Register  */
} IIR_Coef_TypeDef;


/**
  * @brief CORDIC Channel
  */
typedef struct {
    __IOM uint32_t CSR;             /*!< (@ 0x00000000) CORDIC Control / Status Register    */
    __IOM uint32_t ARX;             /*!< (@ 0x00000004) CORDIC Argument / Result Register X */
    __IOM uint32_t ARY;             /*!< (@ 0x00000008) CORDIC Argument / Result Register Y */
    __IM  uint32_t RESERVED[5];
} CORDIC_CH_TypeDef;


/**
  * @brief DMA Channel Numbers
  */
#define DMA_CH_NUMS     (6)

/**
  * @brief DMA Channel
  */
typedef struct {
    DMA0_Type     REG;              /*!< DMA Register                   */
    __IM uint32_t RESERVED[1];
} DMA_CH_TypeDef;

/**
  * @brief DMA Registers Structure
  */
typedef struct {                    /*!< (@ 0x40022000) DMA Structure   */
    DMA_CH_TypeDef CH[DMA_CH_NUMS]; /*!< DMA Channel control Register   */
} DMA_TypeDef;                      /*!< Size = 192 (0xc0)              */


/**
  * @brief ADC DMA
  */
typedef struct {
    __IOM uint32_t TCR;             /*!< (@ 0x00000000) ADC DMA Transfer Control Register    */
    __IOM uint32_t TAR;             /*!< (@ 0x00000004) ADC DMA Transfer Address Register    */
    __IOM uint32_t TLR;             /*!< (@ 0x00000008) ADC DMA Transfer Length Register     */
    __IM  uint32_t RESERVED;
} ADC_DMA_TypeDef;


/**
  * @brief HRPWM PWMx Registers
  */
typedef struct {
    HRPWM_SLV0_Type REG;            /*!< HRPWM Slave Register           */
    __IM  uint32_t  RESERVED3[32];
} HRPWM_PWMx_TypeDef;

/**
  * @brief HRPWM Registers Structure
  */
typedef struct {                    /*!< (@ 0x4003B000) HRPWM Structure */
    HRPWM_MST_Type     Master;      /*!< HRPWM Master Registers         */
    __IM  uint32_t     RESERVED[32];
    HRPWM_PWMx_TypeDef PWM[8];      /*!< HRPWM PWMx Registers           */
    __IM  uint32_t     RESERVED1[384];
    HRPWM_COM_Type     Common;      /*!< HRPWM Common Registers         */
} HRPWM_TypeDef;                    /*!< Size = 4084 (0xFF4)            */

/**
  * @}
  */

/**
  * @}
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup TAE32G58xx_Exported_Constants TAE32G58xx Exported Constants
  * @brief    TAE32G58xx Exported Constants
  * @{
  */

#define EFLASH_IRQn             (FLASH_IRQn)                    /*!< EFLASH IRQ Number Alias                                */


/** @defgroup TAE32G58xx_Peripheral_Memory_Map TAE32G58xx Peripheral Memory Map
  * @brief    TAE32G58xx Peripheral Memory Map
  * @{
  */

/* Memory Region Map */
#define EFLASH_MEM_BASE         0x08000000UL                    /*!< EFLASH Memory base address in the alias region         */
#define EFLASH_BANK_END         0x080FFFFFUL                    /*!< EFLASH Bank End address in the alias region            */
#define SRAMA_BASE              0x20000000UL                    /*!< SRAMA base address in the alias region                 */
#define SRAMB_BASE              0x20008000UL                    /*!< SRAMB base address in the alias region                 */
#define SRAMC_BASE              0x20010000UL                    /*!< SRAMC base address in the alias region                 */
#define SRAMD_BASE              0x20018000UL                    /*!< SRAMD base address in the alias region                 */

/* Peripheral Bus Map */
#define PERIPH_BASE             0x40000000UL                    /*!< Peripheral base address in the alias region            */
#define APB0PERIPH_BASE         (PERIPH_BASE               )    /*!< APB0 Peripheral base address in the alias region       */
#define APB1PERIPH_BASE         (PERIPH_BASE + 0x00010000UL)    /*!< APB1 Peripheral base address in the alias region       */
#define AHB0PERIPH_BASE         (PERIPH_BASE + 0x00020000UL)    /*!< AHB0 Peripheral base address in the alias region       */
#define AHB1PERIPH_BASE         (PERIPH_BASE + 0x00030000UL)    /*!< AHB1 Peripheral base address in the alias region       */

/**
  * @}
  */


/** @defgroup TAE32G58xx_Peripheral_Declaration TAE32G58xx Peripheral Declaration
  * @brief    TAE32G58xx Peripheral Declaration
  * @{
  */

#undef I2C0
#undef I2C1
#undef I2C2
#undef UART0
#undef UART1
#undef UART2
#undef TMR7
#undef TMR8
#undef IWDG
#undef WWDG

#undef UART3
#undef UART4
#undef SPI0
#undef SPI1
#undef CAN0
#undef CAN1
#undef XIF
#undef PDM0
#undef PDM1
#undef PDM2
#undef PDM3
#undef TMR0
#undef TMR1
#undef TMR2

#undef RCU
#undef SYSCTRL
#undef FLASH
#undef GPIOA
#undef GPIOB
#undef GPIOC
#undef GPIOD
#undef GPIOE
#undef GPIOF
#undef TMR3
#undef TMR4
#undef QEI0
#undef QEI1
#undef QEI2

#undef TMR9
#undef TMR10
#undef USB
#undef ADC0
#undef ADC1
#undef ADC2
#undef ADC3
#undef DAC0
#undef DAC1
#undef DAC2
#undef DAC3
#undef DAC4
#undef DAC5
#undef DAC6
#undef DAC7
#undef DAC8
#undef CMP0
#undef CMP1
#undef CMP2
#undef CMP3
#undef CMP4
#undef CMP5
#undef CMP6
#undef CMP7
#undef CMP8
#undef IIR0
#undef IIR1
#undef IIR2
#undef IIR3
#undef IIR4
#undef IIR5
#undef CORDIC

#undef TMR6

#define I2C0        ((I2C_TypeDef     *) I2C0_BASE      )       /*!< I2C0 Peripheral Declaration    */
#define I2C1        ((I2C_TypeDef     *) I2C1_BASE      )       /*!< I2C1 Peripheral Declaration    */
#define I2C2        ((I2C_TypeDef     *) I2C2_BASE      )       /*!< I2C2 Peripheral Declaration    */
#define UART0       ((UART_TypeDef    *) UART0_BASE     )       /*!< UART0 Peripheral Declaration   */
#define UART1       ((UART_TypeDef    *) UART1_BASE     )       /*!< UART1 Peripheral Declaration   */
#define UART2       ((UART_TypeDef    *) UART2_BASE     )       /*!< UART2 Peripheral Declaration   */
#define TMR7        ((TMR_TypeDef     *) TMR7_BASE      )       /*!< TMR7 Peripheral Declaration    */
#define TMR8        ((TMR_TypeDef     *) TMR8_BASE      )       /*!< TMR8 Peripheral Declaration    */
#define IWDG        ((IWDG_TypeDef    *) IWDG_BASE      )       /*!< IWDG Peripheral Declaration    */
#define WWDG        ((WWDG_TypeDef    *) WWDG_BASE      )       /*!< WWDG Peripheral Declaration    */

#define UART3       ((UART_TypeDef    *) UART3_BASE     )       /*!< UART3 Peripheral Declaration   */
#define UART4       ((UART_TypeDef    *) UART4_BASE     )       /*!< UART4 Peripheral Declaration   */
#define SPI0        ((SPI_TypeDef     *) SPI0_BASE      )       /*!< SPI0 Peripheral Declaration    */
#define SPI1        ((SPI_TypeDef     *) SPI1_BASE      )       /*!< SPI1 Peripheral Declaration    */
#define CAN0        ((CAN_TypeDef     *) CAN0_BASE      )       /*!< CAN0 Peripheral Declaration    */
#define CAN1        ((CAN_TypeDef     *) CAN1_BASE      )       /*!< CAN1 Peripheral Declaration    */
#define XIF         ((XIF_TypeDef     *) XIF_BASE       )       /*!< XIF Peripheral Declaration     */
#define PDM0        ((PDM_TypeDef     *) PDM0_BASE      )       /*!< PDM0 Peripheral Declaration    */
#define PDM1        ((PDM_TypeDef     *) PDM1_BASE      )       /*!< PDM1 Peripheral Declaration    */
#define PDM2        ((PDM_TypeDef     *) PDM2_BASE      )       /*!< PDM2 Peripheral Declaration    */
#define PDM3        ((PDM_TypeDef     *) PDM3_BASE      )       /*!< PDM3 Peripheral Declaration    */
#define TMR0        ((TMR_TypeDef     *) TMR0_BASE      )       /*!< TMR0 Peripheral Declaration    */
#define TMR1        ((TMR_TypeDef     *) TMR1_BASE      )       /*!< TMR1 Peripheral Declaration    */
#define TMR2        ((TMR_TypeDef     *) TMR2_BASE      )       /*!< TMR2 Peripheral Declaration    */

#define RCU         ((RCU_TypeDef     *) RCU_BASE       )       /*!< RCU Peripheral Declaration     */
#define SYSCTRL     ((SYSCTRL_TypeDef *) SYSCTRL_BASE   )       /*!< SYSCTRL Peripheral Declaration */
#define DMA         ((DMA_TypeDef     *) DMA0_BASE      )       /*!< DMA Peripheral Declaration     */
#define EFLASH      ((EFLASH_TypeDef  *) FLASH_BASE     )       /*!< EFLASH Peripheral Declaration  */
#define GPIOA       ((GPIO_TypeDef    *) GPIOA_BASE     )       /*!< GPIOA Peripheral Declaration   */
#define GPIOB       ((GPIO_TypeDef    *) GPIOB_BASE     )       /*!< GPIOB Peripheral Declaration   */
#define GPIOC       ((GPIO_TypeDef    *) GPIOC_BASE     )       /*!< GPIOC Peripheral Declaration   */
#define GPIOD       ((GPIO_TypeDef    *) GPIOD_BASE     )       /*!< GPIOD Peripheral Declaration   */
#define GPIOE       ((GPIO_TypeDef    *) GPIOE_BASE     )       /*!< GPIOE Peripheral Declaration   */
#define GPIOF       ((GPIO_TypeDef    *) GPIOF_BASE     )       /*!< GPIOF Peripheral Declaration   */
#define TMR3        ((TMR_TypeDef     *) TMR3_BASE      )       /*!< TMR3 Peripheral Declaration    */
#define TMR4        ((TMR_TypeDef     *) TMR4_BASE      )       /*!< TMR4 Peripheral Declaration    */
#define QEI0        ((QEI_TypeDef     *) QEI0_BASE      )       /*!< QEI0 Peripheral Declaration    */
#define QEI1        ((QEI_TypeDef     *) QEI1_BASE      )       /*!< QEI1 Peripheral Declaration    */
#define QEI2        ((QEI_TypeDef     *) QEI2_BASE      )       /*!< QEI2 Peripheral Declaration    */

#define TMR9        ((TMR_TypeDef     *) TMR9_BASE      )       /*!< TMR9 Peripheral Declaration    */
#define TMR10       ((TMR_TypeDef     *) TMR10_BASE     )       /*!< TMR10 Peripheral Declaration   */
#define USB         ((USB_TypeDef     *) USB_BASE       )       /*!< USB Peripheral Declaration     */
#define ADC0        ((ADC_TypeDef     *) ADC0_BASE      )       /*!< ADC0 Peripheral Declaration    */
#define ADC1        ((ADC_TypeDef     *) ADC1_BASE      )       /*!< ADC1 Peripheral Declaration    */
#define ADC2        ((ADC_TypeDef     *) ADC2_BASE      )       /*!< ADC2 Peripheral Declaration    */
#define ADC3        ((ADC_TypeDef     *) ADC3_BASE      )       /*!< ADC3 Peripheral Declaration    */
#define DAC0        ((DAC_TypeDef     *) DAC0_BASE      )       /*!< DAC0 Peripheral Declaration    */
#define DAC1        ((DAC_TypeDef     *) DAC1_BASE      )       /*!< DAC1 Peripheral Declaration    */
#define DAC2        ((DAC_TypeDef     *) DAC2_BASE      )       /*!< DAC2 Peripheral Declaration    */
#define DAC3        ((DAC_TypeDef     *) DAC3_BASE      )       /*!< DAC3 Peripheral Declaration    */
#define DAC4        ((DAC_TypeDef     *) DAC4_BASE      )       /*!< DAC4 Peripheral Declaration    */
#define DAC5        ((DAC_TypeDef     *) DAC5_BASE      )       /*!< DAC5 Peripheral Declaration    */
#define DAC6        ((DAC_TypeDef     *) DAC6_BASE      )       /*!< DAC6 Peripheral Declaration    */
#define DAC7        ((DAC_TypeDef     *) DAC7_BASE      )       /*!< DAC7 Peripheral Declaration    */
#define DAC8        ((DAC_TypeDef     *) DAC8_BASE      )       /*!< DAC8 Peripheral Declaration    */
#define CMP0        ((CMP_TypeDef     *) CMP0_BASE      )       /*!< CMP0 Peripheral Declaration    */
#define CMP1        ((CMP_TypeDef     *) CMP1_BASE      )       /*!< CMP1 Peripheral Declaration    */
#define CMP2        ((CMP_TypeDef     *) CMP2_BASE      )       /*!< CMP2 Peripheral Declaration    */
#define CMP3        ((CMP_TypeDef     *) CMP3_BASE      )       /*!< CMP3 Peripheral Declaration    */
#define CMP4        ((CMP_TypeDef     *) CMP4_BASE      )       /*!< CMP4 Peripheral Declaration    */
#define CMP5        ((CMP_TypeDef     *) CMP5_BASE      )       /*!< CMP5 Peripheral Declaration    */
#define CMP6        ((CMP_TypeDef     *) CMP6_BASE      )       /*!< CMP6 Peripheral Declaration    */
#define CMP7        ((CMP_TypeDef     *) CMP7_BASE      )       /*!< CMP7 Peripheral Declaration    */
#define CMP8        ((CMP_TypeDef     *) CMP8_BASE      )       /*!< CMP8 Peripheral Declaration    */
#define HRPWM       ((HRPWM_TypeDef   *) HRPWM_MST_BASE )       /*!< HRPWM Peripheral Declaration   */
#define IIR0        ((IIR_TypeDef     *) IIR0_BASE      )       /*!< IIR0 Peripheral Declaration    */
#define IIR1        ((IIR_TypeDef     *) IIR1_BASE      )       /*!< IIR1 Peripheral Declaration    */
#define IIR2        ((IIR_TypeDef     *) IIR2_BASE      )       /*!< IIR2 Peripheral Declaration    */
#define IIR3        ((IIR_TypeDef     *) IIR3_BASE      )       /*!< IIR3 Peripheral Declaration    */
#define IIR4        ((IIR_TypeDef     *) IIR4_BASE      )       /*!< IIR4 Peripheral Declaration    */
#define IIR5        ((IIR_TypeDef     *) IIR5_BASE      )       /*!< IIR5 Peripheral Declaration    */
#define CORDIC      ((CORDIC_TypeDef  *) CORDIC_BASE    )       /*!< CORDIC Peripheral Declaration  */

#ifdef TAE32G58XX_REG_BIT_VERSION
#define TMR6        ((LPTMR_TypeDef   *) TMR6_BASE      )       /*!< TMR6 Peripheral Declaration   */
#else
#define TMR6        ((TMR_TypeDef     *) TMR6_BASE      )       /*!< TMR6 Peripheral Declaration   */
#endif

/**
  * @}
  */

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup TAE32G58xx_Exported_Macros TAE32G58xx Exported Macros
  * @brief    TAE32G58xx Exported Macros
  * @{
  */

/**
  * @brief  Judge is I2C instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't I2C instance
  * @retval 1 is I2C instance
  */
#define IS_I2C_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == I2C0 || (__INSTANCE__) == I2C1 || (__INSTANCE__) == I2C2)

/**
  * @brief  Judge is UART instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't UART instance
  * @retval 1 is UART instance
  */
#define IS_UART_ALL_INSTANCE(__INSTANCE__)          ((__INSTANCE__) == UART0 || (__INSTANCE__) == UART1 || \
                                                     (__INSTANCE__) == UART2 || (__INSTANCE__) == UART3 || \
                                                     (__INSTANCE__) == UART4)

/**
  * @brief  Judge is BSTMR instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't BSTMR instance
  * @retval 1 is BSTMR instance
  */
#define IS_BSTMR_ALL_INSTANCE(__INSTANCE__)         ((__INSTANCE__) == TMR7 || (__INSTANCE__) == TMR8)

/**
  * @brief  Judge is IWDG instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't IWDG instance
  * @retval 1 is IWDG instance
  */
#define IS_IWDG_ALL_INSTANCE(__INSTANCE__)          ((__INSTANCE__) == IWDG)

/**
  * @brief  Judge is WWDG instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't WWDG instance
  * @retval 1 is WWDG instance
  */
#define IS_WWDG_ALL_INSTANCE(__INSTANCE__)          ((__INSTANCE__) == WWDG)


/**
  * @brief  Judge is SPI instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't SPI instance
  * @retval 1 is SPI instance
  */
#define IS_SPI_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == SPI0 || (__INSTANCE__) == SPI1)

/**
  * @brief  Judge is CAN instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't CAN instance
  * @retval 1 is CAN instance
  */
#define IS_CAN_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == CAN0 || (__INSTANCE__) == CAN1)

/**
  * @brief  Judge is XIF instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't XIF instance
  * @retval 1 is XIF instance
  */
#define IS_XIF_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == XIF)

/**
  * @brief  Judge is PDM instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't PDM instance
  * @retval 1 is PDM instance
  */
#define IS_PDM_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == PDM0 || (__INSTANCE__) == PDM1 || \
                                                     (__INSTANCE__) == PDM2 || (__INSTANCE__) == PDM3)

/**
  * @brief  Judge is GPTMRX instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't GPTMRX instance
  * @retval 1 is GPTMRX instance
  */
#define IS_GPTMRX_ALL_INSTANCE(__INSTANCE__)        ((__INSTANCE__) == TMR0 || (__INSTANCE__) == TMR1 || (__INSTANCE__) == TMR2)


/**
  * @brief  Judge is RCU instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't RCU instance
  * @retval 1 is RCU instance
  */
#define IS_RCU_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == RCU)

/**
  * @brief  Judge is SYSCTRL instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't SYSCTRL instance
  * @retval 1 is SYSCTRL instance
  */
#define IS_SYSCTRL_ALL_INSTANCE(__INSTANCE__)       ((__INSTANCE__) == SYSCTRL)

/**
  * @brief  Judge is DMA instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't DMA instance
  * @retval 1 is DMA instance
  */
#define IS_DMA_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == DMA)

/**
  * @brief  Judge is EFLASH instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't EFLASH instance
  * @retval 1 is EFLASH instance
  */
#define IS_EFLASH_ALL_INSTANCE(__INSTANCE__)        ((__INSTANCE__) == EFLASH)

/**
  * @brief  Judge is GPIO instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't GPIO instance
  * @retval 1 is GPIO instance
  */
#define IS_GPIO_ALL_INSTANCE(__INSTANCE__)          ((__INSTANCE__) == GPIOA || (__INSTANCE__) == GPIOB || \
                                                     (__INSTANCE__) == GPIOC || (__INSTANCE__) == GPIOD || \
                                                     (__INSTANCE__) == GPIOE || (__INSTANCE__) == GPIOF)

/**
  * @brief  Judge is GPTMRY instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't GPTMRY instance
  * @retval 1 is GPTMRY instance
  */
#define IS_GPTMRY_ALL_INSTANCE(__INSTANCE__)        ((__INSTANCE__) == TMR3 || (__INSTANCE__) == TMR4)

/**
  * @brief  Judge is QEI instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't QEI instance
  * @retval 1 is QEI instance
  */
#define IS_QEI_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == QEI0 || (__INSTANCE__) == QEI1 || (__INSTANCE__) == QEI2)


/**
  * @brief  Judge is ADTMR instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't ADTMR instance
  * @retval 1 is ADTMR instance
  */
#define IS_ADTMR_ALL_INSTANCE(__INSTANCE__)         ((__INSTANCE__) == TMR9 || (__INSTANCE__) == TMR10)

/**
  * @brief  Judge is USB instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't USB instance
  * @retval 1 is USB instance
  */
#define IS_USB_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == USB)

/**
  * @brief  Judge is ADC instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't ADC instance
  * @retval 1 is ADC instance
  */
#define IS_ADC_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == ADC0 || (__INSTANCE__) == ADC1 || \
                                                     (__INSTANCE__) == ADC2 || (__INSTANCE__) == ADC3)

/**
  * @brief  Judge is DAC instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't DAC instance
  * @retval 1 is DAC instance
  */
#define IS_DAC_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == DAC0 || (__INSTANCE__) == DAC1 || \
                                                     (__INSTANCE__) == DAC2 || (__INSTANCE__) == DAC3 || \
                                                     (__INSTANCE__) == DAC4 || (__INSTANCE__) == DAC5 || \
                                                     (__INSTANCE__) == DAC6 || (__INSTANCE__) == DAC7 || \
                                                     (__INSTANCE__) == DAC8)

/**
  * @brief  Judge is CMP instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't CMP instance
  * @retval 1 is CMP instance
  */
#define IS_CMP_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == CMP0 || (__INSTANCE__) == CMP1 || \
                                                     (__INSTANCE__) == CMP2 || (__INSTANCE__) == CMP3 || \
                                                     (__INSTANCE__) == CMP4 || (__INSTANCE__) == CMP5 || \
                                                     (__INSTANCE__) == CMP6 || (__INSTANCE__) == CMP7 || \
                                                     (__INSTANCE__) == CMP8)

/**
  * @brief  Judge is HRPWM instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't HRPWM instance
  * @retval 1 is HRPWM instance
  */
#define IS_HRPWM_ALL_INSTANCE(__INSTANCE__)         ((__INSTANCE__) == HRPWM)

/**
  * @brief  Judge is IIR instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't IIR instance
  * @retval 1 is IIR instance
  */
#define IS_IIR_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == IIR0 || (__INSTANCE__) == IIR1 || \
                                                     (__INSTANCE__) == IIR2 || (__INSTANCE__) == IIR3 || \
                                                     (__INSTANCE__) == IIR4 || (__INSTANCE__) == IIR5)

/**
  * @brief  Judge is IIRx instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't IIRx instance
  * @retval 1 is IIRx instance
  */
#define IS_IIRx_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == IIR0 || (__INSTANCE__) == IIR1 || (__INSTANCE__) == IIR2)

/**
  * @brief  Judge is IIRy instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't IIRy instance
  * @retval 1 is IIRy instance
  */
#define IS_IIRy_ALL_INSTANCE(__INSTANCE__)           ((__INSTANCE__) == IIR3 || (__INSTANCE__) == IIR4 || (__INSTANCE__) == IIR5)

/**
  * @brief  Judge is CORDIC instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't CORDIC instance
  * @retval 1 is CORDIC instance
  */
#define IS_CORDIC_ALL_INSTANCE(__INSTANCE__)        ((__INSTANCE__) == CORDIC)

/**
  * @brief  Judge is LPTMR instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't LPTMR instance
  * @retval 1 is LPTMR instance
  */
#define IS_LPTMR_ALL_INSTANCE(__INSTANCE__)         ((__INSTANCE__) == TMR6)


/**
  * @brief  Judge is TMR instance or not
  * @param  __INSTANCE__ instance to be judged
  * @retval 0 isn't TMR instance
  * @retval 1 is TMR instance
  */
#define IS_TMR_ALL_INSTANCE(__INSTANCE__)           (IS_BSTMR_ALL_INSTANCE(__INSTANCE__)  || \
                                                     IS_GPTMRX_ALL_INSTANCE(__INSTANCE__) || \
                                                     IS_GPTMRY_ALL_INSTANCE(__INSTANCE__) || \
                                                     IS_ADTMR_ALL_INSTANCE(__INSTANCE__)  || \
                                                     IS_LPTMR_ALL_INSTANCE(__INSTANCE__))


/**
  * @brief  Get I2C IRQn Number
  * @param  __INSTANCE__ instance
  * @return IRQn_Type for I2C
 */
#define GET_I2C_IRQ_NUMBER(__INSTANCE__)            \
    (  ((__INSTANCE__) == I2C0)   ? I2C0_IRQn       \
     : ((__INSTANCE__) == I2C1)   ? I2C1_IRQn       \
     : ((__INSTANCE__) == I2C2)   ? I2C2_IRQn       \
                                  : -128)

/**
  * @brief  Get UART IRQn Number
  * @param  __INSTANCE__ instance
  * @return IRQn_Type for UART
 */
#define GET_UART_IRQ_NUMBER(__INSTANCE__)           \
    (  ((__INSTANCE__) == UART0)  ? UART0_IRQn      \
     : ((__INSTANCE__) == UART1)  ? UART1_IRQn      \
     : ((__INSTANCE__) == UART2)  ? UART2_IRQn      \
     : ((__INSTANCE__) == UART3)  ? UART3_IRQn      \
     : ((__INSTANCE__) == UART4)  ? UART4_IRQn      \
                                  : -128)

/**
  * @brief  Get SPI IRQn Number
  * @param  __INSTANCE__ instance
  * @return IRQn_Type for SPI
 */
#define GET_SPI_IRQ_NUMBER(__INSTANCE__)            \
    (  ((__INSTANCE__) == SPI0)   ? SPI0_IRQn       \
     : ((__INSTANCE__) == SPI1)   ? SPI1_IRQn       \
                                  : -128)

/**
  * @brief  Get CAN INT0 IRQn Number
  * @param  __INSTANCE__ instance
  * @return IRQn_Type for CAN
 */
#define GET_CAN_INT0_IRQ_NUMBER(__INSTANCE__)       \
    (  ((__INSTANCE__) == CAN0)   ? CAN0_IRQn       \
     : ((__INSTANCE__) == CAN1)   ? CAN1_IRQn       \
                                  : -128)

/**
  * @brief  Get CAN INT1 IRQn Number
  * @param  __INSTANCE__ instance
  * @return IRQn_Type for CAN
 */
#define GET_CAN_INT1_IRQ_NUMBER(__INSTANCE__)       \
    (  ((__INSTANCE__) == CAN0)   ? CAN0_INT1_IRQn  \
     : ((__INSTANCE__) == CAN1)   ? CAN1_INT1_IRQn  \
                                  : -128)

/**
  * @brief  Get XIF IRQn Number
  * @param  __INSTANCE__ instance
  * @return IRQn_Type for XIF
 */
#define GET_XIF_IRQ_NUMBER(__INSTANCE__)            \
    (  ((__INSTANCE__) == XIF)    ? XIF_IRQn        \
                                  : -128)

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/


/* --------  End of section using anonymous unions and disabling warnings  -------- */
#if   defined (__CC_ARM)
#pragma pop
#elif defined (__ICCARM__)
/* leave anonymous unions enabled */
#elif (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
#pragma clang diagnostic pop
#elif defined (__GNUC__)
/* anonymous unions are enabled by default */
#elif defined (__TMS470__)
/* anonymous unions are enabled by default */
#elif defined (__TASKING__)
#pragma warning restore
#elif defined (__CSMC__)
/* anonymous unions are enabled by default */
#else
#warning Not supported compiler type
#endif


/**
  * @}
  */


/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif  /* _TAE32G58XX_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

