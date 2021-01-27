/**
 **************************************************************************
 * File Name    : at32f4xx_rcc.h
 * Description  : at32f4xx RCC header file
 * Date         : 2018-02-26
 * Version      : V1.0.4
 **************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F4xx_RCC_H
#define __AT32F4xx_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/** @defgroup RCC_Exported_Types
  * @{
  */

typedef struct
{
    uint32_t SYSCLK_Freq;     /*!< returns SYSCLK clock frequency expressed in Hz */
    uint32_t AHBCLK_Freq;     /*!< returns HCLK clock frequency expressed in Hz */
    uint32_t APB1CLK_Freq;    /*!< returns PCLK1 clock frequency expressed in Hz */
    uint32_t APB2CLK_Freq;    /*!< returns PCLK2 clock frequency expressed in Hz */
    uint32_t ADCCLK_Freq;     /*!< returns ADCCLK clock frequency expressed in Hz */
} RCC_ClockType;

/**
  * @}
  */

/** @defgroup RCC_Exported_Constants
  * @{
  */

/** @defgroup HSE_configuration
  * @{
  */

#define RCC_HSE_DISABLE                 ((uint32_t)0x00000000)
#define RCC_HSE_ENABLE                  ((uint32_t)0x00010000)
#define RCC_HSE_BYPASS                  ((uint32_t)0x00040000)
#define IS_RCC_HSE(HSE)                 (((HSE) == RCC_HSE_DISABLE) || \
                                         ((HSE) == RCC_HSE_ENABLE)  || \
                                         ((HSE) == RCC_HSE_BYPASS))

/**
  * @}
  */

/** @defgroup PLL_entry_clock_source
  * @{
  */

#define RCC_PLLRefClk_HSI_Div2          ((uint32_t)0x00000000)

#define RCC_PLLRefClk_HSE_Div1          ((uint32_t)0x00010000)
#define RCC_PLLRefClk_HSE_Div2          ((uint32_t)0x00030000)
#define IS_RCC_PLL_CFG(CFG)             (((CFG) == RCC_PLLRefClk_HSI_Div2) || \
                                         ((CFG) == RCC_PLLRefClk_HSE_Div1) || \
                                         ((CFG) == RCC_PLLRefClk_HSE_Div2))


/**
  * @}
  */
#define RCC_PLL_RANGE                   72000000
/** @defgroup PLL_clock_range_setting
  * @{
  */
#define RCC_Range_LessEqual_72Mhz       ((uint32_t)0x00000000)
#define RCC_Range_GreatThan_72Mhz       ((uint32_t)0x80000000)
#define IS_RCC_PLL_RANGE(CFG)           (((CFG) == RCC_Range_LessEqual_72Mhz) || \
                                         ((CFG) == RCC_Range_GreatThan_72Mhz))
/**
  * @}
  */
/** @defgroup PLL_multiplication_factor
  * @{
  */
#define RCC_PLLMult_2                   RCC_CFG_PLLMULT2
#define RCC_PLLMult_3                   RCC_CFG_PLLMULT3
#define RCC_PLLMult_4                   RCC_CFG_PLLMULT4
#define RCC_PLLMult_5                   RCC_CFG_PLLMULT5
#define RCC_PLLMult_6                   RCC_CFG_PLLMULT6
#define RCC_PLLMult_7                   RCC_CFG_PLLMULT7
#define RCC_PLLMult_8                   RCC_CFG_PLLMULT8
#define RCC_PLLMult_9                   RCC_CFG_PLLMULT9
#define RCC_PLLMult_10                  RCC_CFG_PLLMULT10
#define RCC_PLLMult_11                  RCC_CFG_PLLMULT11
#define RCC_PLLMult_12                  RCC_CFG_PLLMULT12
#define RCC_PLLMult_13                  RCC_CFG_PLLMULT13
#define RCC_PLLMult_14                  RCC_CFG_PLLMULT14
#define RCC_PLLMult_15                  RCC_CFG_PLLMULT15
#define RCC_PLLMult_16                  RCC_CFG_PLLMULT16
#define RCC_PLLMult_17                  RCC_CFG_PLLMULT17 
#define RCC_PLLMult_18                  RCC_CFG_PLLMULT18 
#define RCC_PLLMult_19                  RCC_CFG_PLLMULT19 
#define RCC_PLLMult_20                  RCC_CFG_PLLMULT20 
#define RCC_PLLMult_21                  RCC_CFG_PLLMULT21 
#define RCC_PLLMult_22                  RCC_CFG_PLLMULT22 
#define RCC_PLLMult_23                  RCC_CFG_PLLMULT23 
#define RCC_PLLMult_24                  RCC_CFG_PLLMULT24 
#define RCC_PLLMult_25                  RCC_CFG_PLLMULT25 
#define RCC_PLLMult_26                  RCC_CFG_PLLMULT26 
#define RCC_PLLMult_27                  RCC_CFG_PLLMULT27 
#define RCC_PLLMult_28                  RCC_CFG_PLLMULT28 
#define RCC_PLLMult_29                  RCC_CFG_PLLMULT29 
#define RCC_PLLMult_30                  RCC_CFG_PLLMULT30 
#define RCC_PLLMult_31                  RCC_CFG_PLLMULT31 
#define RCC_PLLMult_32                  RCC_CFG_PLLMULT32 
#define RCC_PLLMult_33                  RCC_CFG_PLLMULT33 
#define RCC_PLLMult_34                  RCC_CFG_PLLMULT34 
#define RCC_PLLMult_35                  RCC_CFG_PLLMULT35 
#define RCC_PLLMult_36                  RCC_CFG_PLLMULT36 
#define RCC_PLLMult_37                  RCC_CFG_PLLMULT37 
#define RCC_PLLMult_38                  RCC_CFG_PLLMULT38 
#define RCC_PLLMult_39                  RCC_CFG_PLLMULT39 
#define RCC_PLLMult_40                  RCC_CFG_PLLMULT40 
#define RCC_PLLMult_41                  RCC_CFG_PLLMULT41 
#define RCC_PLLMult_42                  RCC_CFG_PLLMULT42 
#define RCC_PLLMult_43                  RCC_CFG_PLLMULT43 
#define RCC_PLLMult_44                  RCC_CFG_PLLMULT44 
#define RCC_PLLMult_45                  RCC_CFG_PLLMULT45 
#define RCC_PLLMult_46                  RCC_CFG_PLLMULT46 
#define RCC_PLLMult_47                  RCC_CFG_PLLMULT47 
#define RCC_PLLMult_48                  RCC_CFG_PLLMULT48 
#define RCC_PLLMult_49                  RCC_CFG_PLLMULT49 
#define RCC_PLLMult_50                  RCC_CFG_PLLMULT50 
#define RCC_PLLMult_51                  RCC_CFG_PLLMULT51 
#define RCC_PLLMult_52                  RCC_CFG_PLLMULT52 
#define RCC_PLLMult_53                  RCC_CFG_PLLMULT53 
#define RCC_PLLMult_54                  RCC_CFG_PLLMULT54 
#define RCC_PLLMult_55                  RCC_CFG_PLLMULT55 
#define RCC_PLLMult_56                  RCC_CFG_PLLMULT56 
#define RCC_PLLMult_57                  RCC_CFG_PLLMULT57 
#define RCC_PLLMult_58                  RCC_CFG_PLLMULT58 
#define RCC_PLLMult_59                  RCC_CFG_PLLMULT59 
#define RCC_PLLMult_60                  RCC_CFG_PLLMULT60 
#define RCC_PLLMult_61                  RCC_CFG_PLLMULT61 
#define RCC_PLLMult_62                  RCC_CFG_PLLMULT62 
#define RCC_PLLMult_63                  RCC_CFG_PLLMULT63 
#define RCC_PLLMult_64                  RCC_CFG_PLLMULT64 
#define IS_RCC_PLL_MULT(MULT)           (((MULT) & (~RCC_CFG_PLLMULT)) == 0x00000000)

#define RCC_GET_PLLMULT(MULT)           ((((MULT & RCC_CFG_PLLMULT_LB_MASK) >> RCC_CFG_PLLMULT_LB_POS) | \
                                            ((MULT & RCC_CFG_PLLMULT_HB_MASK) >> (RCC_CFG_PLLMULT_HB_POS - RCC_CFG_PLLMULT_HB_OFFSET))) +\
                                          ((((MULT & RCC_CFG_PLLMULT_HB_MASK)==0) && \
                                            ((MULT & RCC_CFG_PLLMULT_LB_MASK)!=RCC_CFG_PLLMULT_LB_MASK) )? 2 : 1 ))
											
/**
  * @}
  */
/** @defgroup System_clock_source
  * @{
  */

#define RCC_SYSCLKSelction_HSI          ((uint32_t)0x00000000)
#define RCC_SYSCLKSelction_HSE          ((uint32_t)0x00000001)
#define RCC_SYSCLKSelction_PLL          ((uint32_t)0x00000002)
#define IS_RCC_SYSCLK_CFG(CFG)          (((CFG) == RCC_SYSCLKSelction_HSI) || \
                                         ((CFG) == RCC_SYSCLKSelction_HSE) || \
                                         ((CFG) == RCC_SYSCLKSelction_PLL))
/**
  * @}
  */

/** @defgroup AHB_clock_source
  * @{
  */

#define RCC_SYSCLK_Div1                 ((uint32_t)0x00000000)
#define RCC_SYSCLK_Div2                 ((uint32_t)0x00000080)
#define RCC_SYSCLK_Div4                 ((uint32_t)0x00000090)
#define RCC_SYSCLK_Div8                 ((uint32_t)0x000000A0)
#define RCC_SYSCLK_Div16                ((uint32_t)0x000000B0)
#define RCC_SYSCLK_Div64                ((uint32_t)0x000000C0)
#define RCC_SYSCLK_Div128               ((uint32_t)0x000000D0)
#define RCC_SYSCLK_Div256               ((uint32_t)0x000000E0)
#define RCC_SYSCLK_Div512               ((uint32_t)0x000000F0)
#define IS_RCC_AHBCLK(CLK)              (((CLK) == RCC_SYSCLK_Div1)   || ((CLK) == RCC_SYSCLK_Div2)   || \
                                         ((CLK) == RCC_SYSCLK_Div4)   || ((CLK) == RCC_SYSCLK_Div8)   || \
                                         ((CLK) == RCC_SYSCLK_Div16)  || ((CLK) == RCC_SYSCLK_Div64)  || \
                                         ((CLK) == RCC_SYSCLK_Div128) || ((CLK) == RCC_SYSCLK_Div256) || \
                                         ((CLK) == RCC_SYSCLK_Div512))
/**
  * @}
  */

/** @defgroup APB1_APB2_clock_source
  * @{
  */

#define RCC_AHBCLK_Div1                 ((uint32_t)0x00000000)
#define RCC_AHBCLK_Div2                 ((uint32_t)0x00000400)
#define RCC_AHBCLK_Div4                 ((uint32_t)0x00000500)
#define RCC_AHBCLK_Div8                 ((uint32_t)0x00000600)
#define RCC_AHBCLK_Div16                ((uint32_t)0x00000700)
#define IS_RCC_APBCLK(CLK)              (((CLK) == RCC_AHBCLK_Div1) || ((CLK) == RCC_AHBCLK_Div2) || \
                                         ((CLK) == RCC_AHBCLK_Div4) || ((CLK) == RCC_AHBCLK_Div8) || \
                                         ((CLK) == RCC_AHBCLK_Div16))
/**
  * @}
  */

/** @defgroup RCC_Interrupt_source
  * @{
  */

#define RCC_INT_LSISTBL                 ((uint8_t)0x01)
#define RCC_INT_LSESTBL                 ((uint8_t)0x02)
#define RCC_INT_HSISTBL                 ((uint8_t)0x04)
#define RCC_INT_HSESTBL                 ((uint8_t)0x08)
#define RCC_INT_PLLSTBL                 ((uint8_t)0x10)
#define RCC_INT_HSECFD                  ((uint8_t)0x80)

#define IS_RCC_INT_EN(INT)              ((((INT) & (uint8_t)0xE0) == 0x00) && ((INT) != 0x00))
#define IS_RCC_INT_STS(INT)             (((INT) == RCC_INT_LSISTBL) || ((INT) == RCC_INT_LSESTBL) || \
                                         ((INT) == RCC_INT_HSISTBL) || ((INT) == RCC_INT_HSESTBL) || \
                                         ((INT) == RCC_INT_PLLSTBL) || ((INT) == RCC_INT_HSECFD))
#define IS_RCC_INT_CLR(INT)             ((((INT) & (uint8_t)0x60) == 0x00) && ((INT) != 0x00))
/**
  * @}
  */

/** @defgroup USB_Device_clock_source
  * @{
  */
#define RCC_USBCLKSelection_PLL_Div1_5   ((uint32_t)0x00000000)
#define RCC_USBCLKSelection_PLL_Div1     ((uint32_t)0x00400000)
#define RCC_USBCLKSelection_PLL_Div2_5   ((uint32_t)0x00800000)
#define RCC_USBCLKSelection_PLL_Div2     ((uint32_t)0x00C00000)
#define RCC_USBCLKSelection_PLL_Div3_5   ((uint32_t)0x08000000)
#define RCC_USBCLKSelection_PLL_Div3     ((uint32_t)0x08400000)
#define RCC_USBCLKSelection_PLL_Div4     ((uint32_t)0x08800000)

#define IS_RCC_USBCLK_CFG(CFG)      (((CFG) == RCC_USBCLKSelection_PLL_Div1_5) || \
                                     ((CFG) == RCC_USBCLKSelection_PLL_Div1)   || \
                                     ((CFG) == RCC_USBCLKSelection_PLL_Div2_5) || \
                                     ((CFG) == RCC_USBCLKSelection_PLL_Div2)   || \
																		 ((CFG) == RCC_USBCLKSelection_PLL_Div3_5) || \
																		 ((CFG) == RCC_USBCLKSelection_PLL_Div3)   || \
																		 ((CFG) == RCC_USBCLKSelection_PLL_Div4))						
/**
  * @}
  */

/** @defgroup ADC_clock_source
  * @{
  */

#define RCC_APB2CLK_Div2            ((uint32_t)0x00000000)
#define RCC_APB2CLK_Div4            ((uint32_t)0x00004000)
#define RCC_APB2CLK_Div6            ((uint32_t)0x00008000)
#define RCC_APB2CLK_Div8            ((uint32_t)0x0000C000)
#define RCC_APB2CLK_Div12           ((uint32_t)0x10004000)
#define RCC_APB2CLK_Div16           ((uint32_t)0x1000C000)
#define IS_RCC_ADCCLK(CLK)          (((CLK) == RCC_APB2CLK_Div2) || ((CLK) == RCC_APB2CLK_Div4) || \
                                     ((CLK) == RCC_APB2CLK_Div6) || ((CLK) == RCC_APB2CLK_Div8) || \
                                     ((CLK) == RCC_APB2CLK_Div12)|| ((CLK) == RCC_APB2CLK_Div16))
/**
  * @}
  */

/** @defgroup LSE_configuration
  * @{
  */

#define RCC_LSE_DISABLE             ((uint8_t)0x00)
#define RCC_LSE_ENABLE              ((uint8_t)0x01)
#define RCC_LSE_BYPASS              ((uint8_t)0x04)
#define IS_RCC_LSE(LSE)             (((LSE) == RCC_LSE_DISABLE) || ((LSE) == RCC_LSE_ENABLE) || \
                                     ((LSE) == RCC_LSE_BYPASS))
/**
  * @}
  */


#if defined (AT32F415xx)
/** @defgroup ERTC_clock_source
  * @{
  */
#define RCC_ERTCCLKSelection_LSE             ((uint32_t)0x00000100)
#define RCC_ERTCCLKSelection_LSI             ((uint32_t)0x00000200)
#define RCC_ERTCCLKSelection_HSE_Div128      ((uint32_t)0x00000300)
#define IS_RCC_ERTCCLK_SEL(SEL)              (((SEL) == RCC_ERTCCLKSelection_LSE) || \
                                              ((SEL)  == RCC_ERTCCLKSelection_LSI) || \
                                              ((SEL)  == RCC_ERTCCLKSelection_HSE_Div128))
#else
/** @defgroup RTC_clock_source
  * @{
  */
#define RCC_RTCCLKSelection_LSE             ((uint32_t)0x00000100)
#define RCC_RTCCLKSelection_LSI             ((uint32_t)0x00000200)
#define RCC_RTCCLKSelection_HSE_Div128      ((uint32_t)0x00000300)
#define IS_RCC_RTCCLK_SEL(SEL)              (((SEL) == RCC_RTCCLKSelection_LSE) || \
                                              ((SEL) == RCC_RTCCLKSelection_LSI) || \
                                              ((SEL) == RCC_RTCCLKSelection_HSE_Div128))
#endif
/**
  * @}
  */

/** @defgroup AHB_peripheral
  * @{
  */

#define RCC_AHBPERIPH_DMA1          ((uint32_t)0x00000001)
#define RCC_AHBPERIPH_DMA2          ((uint32_t)0x00000002)
#define RCC_AHBPERIPH_SRAM          ((uint32_t)0x00000004)
#define RCC_AHBPERIPH_FLASH         ((uint32_t)0x00000010)
#define RCC_AHBPERIPH_CRC           ((uint32_t)0x00000040)
#define RCC_AHBPERIPH_SDIO1         ((uint32_t)0x00000400)

#if defined (AT32F403xx) || defined (AT32F403Axx) || \
    defined (AT32F407xx)
#define RCC_AHBPERIPH_XMC           ((uint32_t)0x00000100)
#define RCC_AHBPERIPH_SDIO2         ((uint32_t)0x00000800)
#endif

#if defined (AT32F403Axx) || defined (AT32F407xx)
#define RCC_AHBPERIPH_ETHMAC        ((uint32_t)0x00004000)
#define RCC_AHBPERIPH_ETHMACTX      ((uint32_t)0x00008000)
#define RCC_AHBPERIPH_ETHMACRX      ((uint32_t)0x00010000)
#define RCC_AHBPERIPH_ETHMACPTP     ((uint32_t)0x10000000)
#endif

#if defined (AT32F415xx)
#define RCC_AHBPERIPH_USB           ((uint32_t)0x00001000)
#endif

#if defined (AT32F403xx)
#define IS_RCC_AHB_PERIPH(PERIPH)   ((((PERIPH) & 0xFFFFF2A8) == 0x00) && ((PERIPH) != 0x00))
#elif defined (AT32F413xx)
#define IS_RCC_AHB_PERIPH(PERIPH)   ((((PERIPH) & 0xFFFFFBA8) == 0x00) && ((PERIPH) != 0x00))
#elif defined (AT32F415xx)
#define IS_RCC_AHB_PERIPH(PERIPH)   ((((PERIPH) & 0xFFFFEBA8) == 0x00) && ((PERIPH) != 0x00))
#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define IS_RCC_AHB_PERIPH(PERIPH)   ((((PERIPH) & 0xEFFE32A8) == 0x00) && ((PERIPH) != 0x00))
#endif


/**
  * @}
  */

/** @defgroup APB2_peripheral
  * @{
  */

#define RCC_APB2PERIPH_AFIO         ((uint32_t)0x00000001)
#define RCC_APB2PERIPH_GPIOA        ((uint32_t)0x00000004)
#define RCC_APB2PERIPH_GPIOB        ((uint32_t)0x00000008)
#define RCC_APB2PERIPH_GPIOC        ((uint32_t)0x00000010)
#define RCC_APB2PERIPH_GPIOD        ((uint32_t)0x00000020)
#if !defined (AT32F403Axx) || !defined (AT32F407xx)
#define RCC_APB2PERIPH_GPIOF        ((uint32_t)0x00000080)
#endif
#define RCC_APB2PERIPH_ADC1         ((uint32_t)0x00000200)
#define RCC_APB2PERIPH_ADC2         ((uint32_t)0x00000400)
#define RCC_APB2PERIPH_TMR1         ((uint32_t)0x00000800)
#define RCC_APB2PERIPH_SPI1         ((uint32_t)0x00001000)
#define RCC_APB2PERIPH_USART1       ((uint32_t)0x00004000)
#define RCC_APB2PERIPH_TMR9         ((uint32_t)0x00080000)
#define RCC_APB2PERIPH_TMR10        ((uint32_t)0x00100000)
#define RCC_APB2PERIPH_TMR11        ((uint32_t)0x00200000)

#if defined (AT32F403xx)
#define RCC_APB2PERIPH_GPIOE        ((uint32_t)0x00000040)
#define RCC_APB2PERIPH_GPIOG        ((uint32_t)0x00000100)
#define RCC_APB2PERIPH_ADC3         ((uint32_t)0x00008000)
#define RCC_APB2PERIPH_TMR15        ((uint32_t)0x00010000)
#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define RCC_APB2PERIPH_GPIOE        ((uint32_t)0x00000040)
#define RCC_APB2PERIPH_ADC3         ((uint32_t)0x00008000)
#define RCC_APB2PERIPH_I2C3         ((uint32_t)0x00800000)
#define RCC_APB2PERIPH_USART6       ((uint32_t)0x01000000)
#define RCC_APB2PERIPH_UART7        ((uint32_t)0x02000000)
#define RCC_APB2PERIPH_UART8        ((uint32_t)0x04000000)
#endif

#if !defined (AT32F415xx)
#define RCC_APB2PERIPH_TMR8         ((uint32_t)0x00002000)
#endif

#if !defined (AT32F403xx)
#define RCC_APB2PERIPH_ACC          ((uint32_t)0x00400000)
#endif

#if defined (AT32F415xx)
#define RCC_APB2PERIPH_EFCB         ((uint32_t)0x00800000)
#endif

#if defined (AT32F403xx)
#define IS_RCC_APB2_PERIPH(PERIPH)  ((((PERIPH) & 0xFFC60002) == 0x00) && ((PERIPH) != 0x00))
#elif defined (AT32F413xx)
#define IS_RCC_APB2_PERIPH(PERIPH)  ((((PERIPH) & 0xFF878142) == 0x00) && ((PERIPH) != 0x00))
#elif defined (AT32F415xx)
#define IS_RCC_APB2_PERIPH(PERIPH)  ((((PERIPH) & 0xFF078142) == 0x00) && ((PERIPH) != 0x00))
#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define IS_RCC_APB2_PERIPH(PERIPH)  ((((PERIPH) & 0xF8070182) == 0x00) && ((PERIPH) != 0x00))
#endif

/**
  * @}
  */

/** @defgroup APB1_peripheral
  * @{
  */

#define RCC_APB1PERIPH_TMR2         ((uint32_t)0x00000001)
#define RCC_APB1PERIPH_TMR3         ((uint32_t)0x00000002)
#define RCC_APB1PERIPH_TMR4         ((uint32_t)0x00000004)
#define RCC_APB1PERIPH_TMR5         ((uint32_t)0x00000008)
#define RCC_APB1PERIPH_WWDG         ((uint32_t)0x00000800)
#define RCC_APB1PERIPH_SPI2         ((uint32_t)0x00004000)
#define RCC_APB1PERIPH_USART2       ((uint32_t)0x00020000)
#define RCC_APB1PERIPH_USART3       ((uint32_t)0x00040000)
#define RCC_APB1PERIPH_UART4        ((uint32_t)0x00080000)
#define RCC_APB1PERIPH_UART5        ((uint32_t)0x00100000)
#define RCC_APB1PERIPH_I2C1         ((uint32_t)0x00200000)
#define RCC_APB1PERIPH_I2C2         ((uint32_t)0x00400000)
#define RCC_APB1PERIPH_CAN1         ((uint32_t)0x02000000)
#define RCC_APB1PERIPH_PWR          ((uint32_t)0x10000000)

#if defined (AT32F403xx) || defined (AT32F403Axx) || \
    defined (AT32F407xx)
#define RCC_APB1PERIPH_TMR6         ((uint32_t)0x00000010)
#define RCC_APB1PERIPH_TMR7         ((uint32_t)0x00000020)
#define RCC_APB1PERIPH_TMR12        ((uint32_t)0x00000040)
#define RCC_APB1PERIPH_TMR13        ((uint32_t)0x00000080)
#define RCC_APB1PERIPH_TMR14        ((uint32_t)0x00000100)
#define RCC_APB1PERIPH_SPI3         ((uint32_t)0x00008000)
#define RCC_APB1PERIPH_SPI4         ((uint32_t)0x00010000)
#define RCC_APB1PERIPH_I2C3         ((uint32_t)0x04000000)
#define RCC_APB1PERIPH_DAC          ((uint32_t)0x20000000)
#endif

#if defined (AT32F413xx)
#define RCC_APB1PERIPH_CAN2         ((uint32_t)0x80000000)
#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define RCC_APB1PERIPH_CAN2         ((uint32_t)0x04000000)
#endif

#if !defined (AT32F415xx)
#define RCC_APB1PERIPH_USB          ((uint32_t)0x00800000)
#define RCC_APB1PERIPH_BKP          ((uint32_t)0x08000000)
#else
#define RCC_APB1PERIPH_COMP         ((uint32_t)0x00000200)
#endif

#if defined (AT32F403xx)
#define IS_RCC_APB1_PERIPH(PERIPH)  ((((PERIPH) & 0xC1003600) == 0x00) && ((PERIPH) != 0x00))
#elif defined (AT32F413xx)
#define IS_RCC_APB1_PERIPH(PERIPH)  ((((PERIPH) & 0x6501B7F0) == 0x00) && ((PERIPH) != 0x00))
#elif defined (AT32F415xx)
#define IS_RCC_APB1_PERIPH(PERIPH)  ((((PERIPH) & 0xED81B3F0) == 0x00) && ((PERIPH) != 0x00))
#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define IS_RCC_APB1_PERIPH(PERIPH)  ((((PERIPH) & 0xC1003600) == 0x00) && ((PERIPH) != 0x00))
#endif
/**
  * @}
  */

/** @defgroup Clock_source_to_output_on_CLKOUT_pin
  * @{
  */
#define RCC_CLKOUT_NOCLK            ((uint32_t)0x00000000)
#define RCC_CLKOUT_SYSCLK           ((uint32_t)0x04000000)
#define RCC_CLKOUT_HSI              ((uint32_t)0x05000000)
#define RCC_CLKOUT_HSE              ((uint32_t)0x06000000)
#define RCC_CLKOUT_PLL_Div2         ((uint32_t)0x07000000)
#define RCC_CLKOUT_PLL_Div4         ((uint32_t)0x14000000)
#define RCC_CLKOUT_USB              ((uint32_t)0x15000000)
#define RCC_CLKOUT_ADC              ((uint32_t)0x16000000)
#if !defined (AT32F403xx)
#define RCC_CLKOUT_LSI              ((uint32_t)0x02000000)
#define RCC_CLKOUT_LSE              ((uint32_t)0x03000000)
#endif
#if !defined (AT32F403xx)
#define IS_RCC_CLKOUT(CLK)          (((CLK) == RCC_CLKOUT_NOCLK)    || ((CLK) == RCC_CLKOUT_HSI)      || \
                                     ((CLK) == RCC_CLKOUT_SYSCLK)   || ((CLK) == RCC_CLKOUT_HSE)      || \
                                     ((CLK) == RCC_CLKOUT_PLL_Div2) || ((CLK) == RCC_CLKOUT_PLL_Div4) || \
                                     ((CLK) == RCC_CLKOUT_USB)      || ((CLK) == RCC_CLKOUT_ADC)      || \
                                     ((CLK) == RCC_CLKOUT_LSI)      || ((CLK) == RCC_CLKOUT_LSE))
#else
#define IS_RCC_CLKOUT(CLK)          (((CLK) == RCC_CLKOUT_NOCLK)    || ((CLK) == RCC_CLKOUT_HSI)      || \
                                     ((CLK) == RCC_CLKOUT_SYSCLK)   || ((CLK) == RCC_CLKOUT_HSE)      || \
                                     ((CLK) == RCC_CLKOUT_PLL_Div2) || ((CLK) == RCC_CLKOUT_PLL_Div4) || \
                                     ((CLK) == RCC_CLKOUT_USB)      || ((CLK) == RCC_CLKOUT_ADC))
#endif

/**
  * @}
  */

/** @defgroup HSE_Divider
  * @{
  */
#define RCC_HSE_DIV_MASK            RCC_MISC2_HSE_DIV_CTRL
#define RCC_HSE_DIV_2               RCC_MISC2_HSE_DIV_CTRL_2
#define RCC_HSE_DIV_3               RCC_MISC2_HSE_DIV_CTRL_3
#define RCC_HSE_DIV_4               RCC_MISC2_HSE_DIV_CTRL_4
#define RCC_HSE_DIV_5               RCC_MISC2_HSE_DIV_CTRL_5

#define IS_RCC_HSEDIV(CLK)          (((CLK) == RCC_HSE_DIV_2) || ((CLK) == RCC_HSE_DIV_3) || \
                                     ((CLK) == RCC_HSE_DIV_4) || ((CLK) == RCC_HSE_DIV_5))
/**
  * @}
  */

/** @defgroup Clock_source_to_output_MCOPRE
  * @{
  */
#define  RCC_MCOPRE_MASK            RCC_MISC_MCOPRE_MASK
#define  RCC_MCOPRE_1               RCC_MISC_MCOPRE_1
#define  RCC_MCOPRE_2               RCC_MISC_MCOPRE_2
#define  RCC_MCOPRE_4               RCC_MISC_MCOPRE_4
#define  RCC_MCOPRE_8               RCC_MISC_MCOPRE_8
#define  RCC_MCOPRE_16              RCC_MISC_MCOPRE_16
#define  RCC_MCOPRE_64              RCC_MISC_MCOPRE_64
#define  RCC_MCOPRE_128             RCC_MISC_MCOPRE_128
#define  RCC_MCOPRE_256             RCC_MISC_MCOPRE_256
#define  RCC_MCOPRE_512             RCC_MISC_MCOPRE_512

#if !defined (AT32F403xx)
#define IS_RCC_MCO(MCOPRE)          (((MCOPRE) == RCC_MCOPRE_1)    || ((MCOPRE) == RCC_MCOPRE_2)      || \
                                     ((MCOPRE) == RCC_MCOPRE_4)    || ((MCOPRE) == RCC_MCOPRE_8)      || \
                                     ((MCOPRE) == RCC_MCOPRE_16)   || ((MCOPRE) == RCC_MCOPRE_64)     || \
                                     ((MCOPRE) == RCC_MCOPRE_128)  || ((MCOPRE) == RCC_MCOPRE_256)    || \
                                     ((MCOPRE) == RCC_MCOPRE_512))
#endif
/**
  * @}
  */

/** @defgroup RCC_Flag
  * @{
  */

#define RCC_FLAG_HSISTBL            ((uint8_t)0x21)
#define RCC_FLAG_HSESTBL            ((uint8_t)0x31)
#define RCC_FLAG_PLLSTBL            ((uint8_t)0x39)
#define RCC_FLAG_LSESTBL            ((uint8_t)0x41)
#define RCC_FLAG_LSISTBL            ((uint8_t)0x61)
#define RCC_FLAG_PINRST             ((uint8_t)0x7A)
#define RCC_FLAG_PORST              ((uint8_t)0x7B)
#define RCC_FLAG_SWRST              ((uint8_t)0x7C)
#define RCC_FLAG_IWDGRST            ((uint8_t)0x7D)
#define RCC_FLAG_WWDGRST            ((uint8_t)0x7E)
#define RCC_FLAG_LPRST              ((uint8_t)0x7F)

#define IS_RCC_FLAG(FLAG)           (((FLAG) == RCC_FLAG_HSISTBL) || ((FLAG) == RCC_FLAG_HSESTBL) || \
                                     ((FLAG) == RCC_FLAG_PLLSTBL) || ((FLAG) == RCC_FLAG_LSESTBL) || \
                                     ((FLAG) == RCC_FLAG_LSISTBL) || ((FLAG) == RCC_FLAG_PINRST)  || \
                                     ((FLAG) == RCC_FLAG_PORST)   || ((FLAG) == RCC_FLAG_SWRST)   || \
                                     ((FLAG) == RCC_FLAG_IWDGRST) || ((FLAG) == RCC_FLAG_WWDGRST) || \
                                     ((FLAG) == RCC_FLAG_LPRST))
#if defined (AT32F403xx)
#define IS_RCC_TWEAK_VALUE(VALUE)    ((VALUE) <= 0x1F)
#else
#define IS_RCC_TWEAK_VALUE(VALUE)    ((VALUE) <= 0x3F)
#endif
#define IS_RCC_CALIB_VALUE(VALUE)    ((VALUE) <= 0xFF)

/**
  * @}
  */

/**
  * @}
  */

#if defined (AT32F415xx)
/** @defgroup RCC_PLL_Register_For_F415
  * @{
  */
#define PLL_FR_POS                   0
#define PLL_FR_MASK                  ((uint32_t)0x00000007)
#define PLL_FR_1                     ((uint32_t)0x00000000)
#define PLL_FR_2                     ((uint32_t)0x00000001)
#define PLL_FR_4                     ((uint32_t)0x00000002)
#define PLL_FR_8                     ((uint32_t)0x00000003)
#define PLL_FR_16                    ((uint32_t)0x00000004)
#define PLL_FR_32                    ((uint32_t)0x00000005)

#define PLL_MS_POS                   4
#define PLL_MS_MASK                  ((uint32_t)0x000000F0)

#define PLL_NS_POS                   8
#define PLL_NS_MASK                  ((uint32_t)0x0000FF00)

#define PLL_FREF_POS                 24
#define PLL_FREF_MASK                ((uint32_t)0x07000000)
#define PLL_FREF_4M                  ((uint32_t)0x00000000)
#define PLL_FREF_6M                  ((uint32_t)0x01000000)
#define PLL_FREF_8M                  ((uint32_t)0x02000000)
#define PLL_FREF_12M                 ((uint32_t)0x03000000)
#define PLL_FREF_16M                 ((uint32_t)0x04000000)
#define PLL_FREF_25M                 ((uint32_t)0x05000000)

#define PLL_CFGGEN_POS               31
#define PLL_CFGEN_ENABLE             ((uint32_t)0x80000000)
#define PLL_CFGEN_MASK               ((uint32_t)0x80000000)

#define IS_RCC_FR(PLL_FR)            (((PLL_FR) == PLL_FR_1)    || ((PLL_FR) == PLL_FR_2)      || \
                                      ((PLL_FR) == PLL_FR_4)    || ((PLL_FR) == PLL_FR_8)      || \
                                      ((PLL_FR) == PLL_FR_16)   || ((PLL_FR) == PLL_FR_32))

#define IS_RCC_FREF(PLL_FREF)        (((PLL_FREF) == PLL_FREF_4M)  || ((PLL_FREF) == PLL_FREF_6M)    || \
                                      ((PLL_FREF) == PLL_FREF_8M)  || ((PLL_FREF) == PLL_FREF_12M)   || \
                                      ((PLL_FREF) == PLL_FREF_16M) || ((PLL_FREF) == PLL_FREF_25M))

#define IS_RCC_MS_VALUE(VALUE)       (((VALUE) >= 0x1) && ((VALUE) <= 0xF))
#define IS_RCC_NS_VALUE(VALUE)       (((VALUE) >= 0x1F) && ((VALUE) <= 0x1F4))
#define IS_RCC_RESULT_VALUE(VALUE)   (((VALUE) >= 0x1F4) && ((VALUE) <= 0x3E8))

#define RCC_FREF_VALUE(VALUE, RET)   do                         \
                                     {                          \
                                       switch (VALUE)           \
                                       {                        \
                                         case PLL_FREF_4M:      \
                                         RET = 4;               \
                                         break;                 \
                                         case PLL_FREF_6M:      \
                                         RET = 6;               \
                                         break;                 \
                                         case PLL_FREF_8M:      \
                                         RET = 8;               \
                                         break;                 \
                                         case PLL_FREF_12M:     \
                                         RET = 12;              \
                                         break;                 \
                                         case PLL_FREF_16M:     \
                                         RET = 16;              \
                                         break;                 \
                                         case PLL_FREF_25M:     \
                                         RET = 25;              \
                                         break;                 \
                                         default:               \
                                         RET = 0;               \
                                         break;                 \
                                       }                        \
                                     }while(0)

#define RCC_FR_VALUE(VALUE, RET)     do                         \
                                     {                          \
                                       switch (VALUE)           \
                                       {                        \
                                         case PLL_FR_1:         \
                                         RET = 1;               \
                                         break;                 \
                                         case PLL_FR_2:         \
                                         RET = 2;               \
                                         break;                 \
                                         case PLL_FR_4:         \
                                         RET = 4;               \
                                         break;                 \
                                         case PLL_FR_8:         \
                                         RET = 8;               \
                                         break;                 \
                                         case PLL_FR_16:        \
                                         RET = 16;              \
                                         break;                 \
                                         case PLL_FR_32:        \
                                         RET = 32;              \
                                         break;                 \
                                         default:               \
                                         RET = 1;               \
                                         break;                 \
                                       }                        \
                                     }while(0)
/**
  * @}
  */
#endif

/**
  * @}
  */
  
/** @defgroup RCC_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions
  * @{
  */

void RCC_Reset(void);
void RCC_HSEConfig(uint32_t RCC_HSE);
ErrorStatus RCC_WaitForHSEStable(void);
void RCC_SetHSITweakValue(uint8_t HSITweakValue);
void RCC_SetHSICalibValue(uint8_t HSICalibValue);
void RCC_HSICmd(FunctionalState NewState);
void RCC_PLLConfig(uint32_t RCC_PLLRefClk, uint32_t RCC_PLLMult, uint32_t RCC_PLLRange);
void RCC_PLLCmd(FunctionalState NewState);
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSelect);
uint8_t RCC_GetSYSCLKSelction(void);
void RCC_AHBCLKConfig(uint32_t RCC_SYSCLK_Div);
void RCC_APB1CLKConfig(uint32_t RCC_HCLK_Div);
void RCC_APB2CLKConfig(uint32_t RCC_HCLK_Div);
void RCC_INTConfig(uint8_t RCC_INT, FunctionalState NewState);
void RCC_ADCCLKConfig(uint32_t RCC_PCLK2_Div);
void RCC_LSEConfig(uint8_t RCC_LSE);
void RCC_LSICmd(FunctionalState NewState);
#if defined (AT32F415xx)
void RCC_ERTCCLKConfig(uint32_t RCC_ERTCCLKSelect);
void RCC_ERTCCLKCmd(FunctionalState NewState);
#else
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSelect);
void RCC_RTCCLKCmd(FunctionalState NewState);
#endif
void RCC_GetClocksFreq(RCC_ClockType* RCC_Clocks);
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
#if defined (AT32F403Axx) || defined (AT32F407xx)
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
#endif
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
void RCC_BackupResetCmd(FunctionalState NewState);
void RCC_HSEClockFailureDetectorCmd(FunctionalState NewState);
#if defined (AT32F403xx)
void RCC_CLKOUTConfig(uint32_t RCC_CLKOUT);
#else
void RCC_CLKOUTConfig(uint32_t RCC_CLKOUT, uint32_t RCC_CLKOUTPRE);
#endif
FlagStatus RCC_GetFlagStatus(uint8_t RCC_Flag);
void RCC_ClearFlag(void);
ITStatus RCC_GetINTStatus(uint8_t RCC_INT);
void RCC_ClearINTPendingBit(uint8_t RCC_INT);
void RCC_USBCLKConfig(uint32_t RCC_USBCLKSelect);
void RCC_StepModeCmd(FunctionalState NewState);
void RCC_USBINTRemap(FunctionalState NewState);
void RCC_HSI2USB48M(FunctionalState NewState);
void RCC_MCO2TMR10(FunctionalState NewState);
#if defined (AT32F415xx)
void RCC_PLLconfig2(uint32_t PLL_FREF, uint32_t PLL_NS, uint32_t PLL_MS, \
                    uint32_t PLL_FR);
#endif
#if defined (AT32F403Axx) || defined (AT32F407xx)
void RCC_HSEDivConfig(uint32_t HSEDiv);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __AT32F4xx_RCC_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


