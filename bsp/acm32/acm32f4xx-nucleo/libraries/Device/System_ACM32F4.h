/*
  ******************************************************************************
  * @file    System_ACM32F4.h
  * @version V1.0.0
  * @date    2020
  * @brief   CMSIS Cortex-M33 Device Peripheral Access Layer System Headler File.
  ******************************************************************************
*/
#ifndef __SYSTEM_ACM32F4_H__
#define __SYSTEM_ACM32F4_H__

#include "ACM32Fxx_HAL.h"

/* ================================================================================ */
/* =======================     Use Uart to Debug print     ======================== */
/* ================================================================================ */
#define UART_DEBUG_ENABLE

#ifdef UART_DEBUG_ENABLE
    #define printfS    printf
#else
    #define printfS(format, ...)    ((void)0)
#endif
/* ================================================================================ */

#define PLLCLK_SRC_RC4M                      (0x00)   
#define PLLCLK_SRC_XTH                       (0x01)  

#define DEFAULT_SYSTEM_CLOCK    (180000000)    // system clock frequency, 32M/64M/120M/180M
#define PLL_SOURCE_FROM         (PLLCLK_SRC_RC4M) 

/* CLK source Index */
#define SYS_CLK_SRC_RCH                      (0x00)    // CLK source from RC64M
#define SYS_CLK_SRC_RC32K                    (0x01)    // CLK source from RC32K
#define SYS_CLK_SRC_XTH                      (0x02)    // CLK source from XTH
#define SYS_CLK_SRC_XTL                      (0x03)    // CLK source from XTL
#define SYS_CLK_SRC_PLLCLK                   (0x04)    // CLK source from PLLCLK 

/* APB Frequencey Division */
#define APB_CLK_DIV_0                        (0 << 8)
#define APB_CLK_DIV_2                        (4 << 8)
#define APB_CLK_DIV_4                        (5 << 8)
#define APB_CLK_DIV_8                        (6 << 8)
#define APB_CLK_DIV_16                       (7 << 8)

/* STOP WAKEUP Sorce */
#define STOP_WAKEUP_GPIO_PIN0         BIT0
#define STOP_WAKEUP_GPIO_PIN1         BIT1
#define STOP_WAKEUP_GPIO_PIN2         BIT2
#define STOP_WAKEUP_GPIO_PIN3         BIT3
#define STOP_WAKEUP_GPIO_PIN4         BIT4
#define STOP_WAKEUP_GPIO_PIN5         BIT5
#define STOP_WAKEUP_GPIO_PIN6         BIT6
#define STOP_WAKEUP_GPIO_PIN7         BIT7
#define STOP_WAKEUP_GPIO_PIN8         BIT8
#define STOP_WAKEUP_GPIO_PIN9         BIT9
#define STOP_WAKEUP_GPIO_PIN10        BIT10
#define STOP_WAKEUP_GPIO_PIN11        BIT11
#define STOP_WAKEUP_GPIO_PIN12        BIT12
#define STOP_WAKEUP_GPIO_PIN13        BIT13
#define STOP_WAKEUP_GPIO_PIN14        BIT14   
#define STOP_WAKEUP_GPIO_PIN15        BIT15 
#define STOP_WAKEUP_PERIPHERAL_LVD    BIT16
#define STOP_WAKEUP_PERIPHERAL_RTC    BIT17
#define STOP_WAKEUP_PERIPHERAL_LPUART BIT18
#define STOP_WAKEUP_PERIPHERAL_IWDT   BIT19    
#define STOP_WAKEUP_PERIPHERAL_COMP1  BIT20
#define STOP_WAKEUP_PERIPHERAL_COMP2  BIT21 
#define STOP_WAKEUP_RESERVE           BIT22   
#define STOP_WAKEUP_PERIPHERAL_USB    BIT23     
#define STOP_WAKEUP_ALL               (0xFFFFFFU)   

#define STANDBY_WAKEUP_PINS        6              
#define STANDBY_WAKEUP_SOURCE_IO1  BIT0   
#define STANDBY_WAKEUP_SOURCE_IO2  BIT1  
#define STANDBY_WAKEUP_SOURCE_IO3  BIT2   
#define STANDBY_WAKEUP_SOURCE_IO4  BIT3  
#define STANDBY_WAKEUP_SOURCE_IO5  BIT4   
#define STANDBY_WAKEUP_SOURCE_IO6  BIT5 
#define STANDBY_WAKEUP_SOURCE_RTC  BIT6    
#define STANDBY_WAKEUP_SOURCE_ALL  0x7FU    

// sleep/low power mode definition  
#define STOPENTRY_WFI   0  
#define STOPENTRY_WFE   1 

#define SLEEPENTRY_WFI  0  
#define SLEEPENTRY_WFE  1  
/*
 * @brief  STOP WAKEUP EDGE structures definition
 */
typedef enum  
{
    WAKEUP_RISING = 0,
    WAKEUP_FALLING = 1,
    WAKEUP_RISING_FALLING = 2, // 0:rising, 1:falling, 2: rising and falling   
}STOP_WAKEUP_EDGE;    

typedef enum
{
    FUNC_DISABLE = 0x00U,
    FUNC_ENABLE  = 0x01U,  
}FUNC_DISABLE_ENABLE;    

typedef enum
{
    RESET_ENABLE_SOURCE_LVD   = 0x00U,
	RESET_ENABLE_SOURCE_WDT   = 0x01U,  
	RESET_ENABLE_SOURCE_IWDT  = 0x02U,  
	RESET_ENABLE_SOURCE_LOCKUP  = 0x03U,          
}RESET_ENABLE_SOURCE;   

typedef enum
{
    RESET_SOURCE_EFC   = 0x00U,
	RESET_SOURCE_NVIC_RESET  = 0x01U,  
	RESET_SOFT_RESET  = 0x02U,             
}RESET_SOURCE; 

/*
 * @brief  Peripheral Reset structures definition
 */
typedef enum
{
    RST_SPI4   = 38,
    RST_GPIOEF = 37,
    RST_SPI3   = 36,
    RST_UART4  = 35,
    RST_TIM4   = 34,
    RST_CAN2   = 33,
    RST_I2S1   = 32,
    
    RST_CAN1   = 31,
    RST_TIM2   = 30,
    RST_USB    = 29,
    RST_UAC    = 28,
    RST_TIM17  = 27,
    RST_TIM16  = 26,
    RST_TIM15  = 25,
    RST_TIM14  = 24,
    RST_TIM7   = 23,
    RST_TIM6   = 22,
    RST_TIM3   = 21,
    RST_TIM1   = 20,
    RST_UART3  = 19,
    RST_EXTI   = 18,
    RST_OPA    = 17,
    RST_COMP   = 16,
    RST_TKEY   = 15,
    RST_ADC    = 14,
    RST_DAC    = 13,
    RST_DMA    = 12,
    RST_CRC    = 11,
    RST_IWDT   = 10,
    RST_WDT    = 9,
    RST_LPUART = 8,
    RST_I2C2   = 7,
    RST_I2C1   = 6,
    RST_SPI2   = 5,
    RST_SPI1   = 4,
    RST_UART2  = 3,
    RST_UART1  = 2,
    RST_GPIOCD = 1,
    RST_GPIOAB = 0,
}enum_RST_ID_t;

/****************  Bit definition for SCU RCR register  ***********************/
#define SCU_RCR_SOFT_RST                    BIT30
#define SCU_RCR_EFC_RST                     BIT29
#define SCU_RCR_REMAP_EN                    BIT16
#define SCU_RCR_LOCKRST_EN                  BIT3
#define SCU_RCR_IWDTRST_EN                  BIT2
#define SCU_RCR_WDTRST_EN                   BIT1
#define SCU_RCR_LVDRST_EN                   BIT0
	
/****************  Bit definition for SCU RSR register  ***********************/	
#define SCU_RSR_RSTFLAG_CLR                 BIT16
#define SCU_RSR_PWRRST_F                    BIT10
#define SCU_RSR_POR12RST_F                  BIT9
#define SCU_RSR_SRST_F                      BIT8
#define SCU_RSR_SRSTNM_F                    BIT7
#define SCU_RSR_EFC_RST_F                   BIT6
#define SCU_RSR_RSTN_F                      BIT5
#define SCU_RSR_SYSREQRST_F                 BIT4
#define SCU_RSR_LOCKRST_F                   BIT3
#define SCU_RSR_IWDTRST_F                   BIT2
#define SCU_RSR_WDTRST_F                    BIT1
#define SCU_RSR_VDLRST_F                    BIT0

/****************  Bit definition for SCU IPRST register  **********************/
#define SCU_IPRST_UACRST                    BIT28
#define SCU_IPRST_TIM17RST                  BIT27
#define SCU_IPRST_TIM16RST                  BIT26
#define SCU_IPRST_TIM15RST                  BIT25
#define SCU_IPRST_TIM14RST                  BIT24
#define SCU_IPRST_TIM6RST                   BIT22
#define SCU_IPRST_TIM3RST                   BIT21
#define SCU_IPRST_TIM1RST                   BIT20
#define SCU_IPRST_UART3RST                  BIT19
#define SCU_IPRST_EXTIRST                   BIT18
#define SCU_IPRST_OPARST                    BIT17
#define SCU_IPRST_CMPRST                    BIT16
#define SCU_IPRST_TKEYRST                   BIT15
#define SCU_IPRST_ADCRST                    BIT14
#define SCU_IPRST_DMACRST                   BIT12
#define SCU_IPRST_CRCRST                    BIT11
#define SCU_IPRST_IWDTRST                   BIT10
#define SCU_IPRST_WDTRST                    BIT9
#define SCU_IPRST_LPUART                    BIT8
#define SCU_IPRST_I2C2RST                   BIT7
#define SCU_IPRST_I2C1RST                   BIT6
#define SCU_IPRST_SPI2RST                   BIT5
#define SCU_IPRST_SPI1RST                   BIT4
#define SCU_IPRST_UART2RST                  BIT3
#define SCU_IPRST_UART1RST                  BIT2
#define SCU_IPRST_GPIO2RST                  BIT1
#define SCU_IPRST_GPIO1RST                  BIT0

/****************  Bit definition for SCU CCR1 register  ***********************/
#define SCU_CCR1_SYS_CLK_SEL               (BIT2|BIT1|BIT0)
#define SCU_CCR1_SYS_PLL                   (BIT2)

/****************  Bit definition for SCU CCR2 register  ***********************/
#define SCU_CCR2_DIVDONE                    BIT31
#define SCU_CCR2_TKSCLK_SEL                 BIT16
#define SCU_CCR2_FLTCLK_SEL                 BIT15
#define SCU_CCR2_LPUCLK_SEL                (BIT14|BIT13)
#define SCU_CCR2_LPUARTDIV                 (BIT12|BIT11)
#define SCU_CCR2_PCLKDIV                   (BIT10|BIT9|BIT8)
#define SCU_CCR2_SYSDIV1                   (BIT7|BIT6|BIT5|BIT4)
#define SCU_CCR2_SYSDIV0                   (BIT3|BIT2|BIT1|BIT0)

/****************  Bit definition for SCU CIR register  ***********************/
#define SCU_CIR_RC4MRDYIC                   BIT21
#define SCU_CIR_PLLLOCKIC                   BIT20
#define SCU_CIR_XTHRDYIC                    BIT19
#define SCU_CIR_RCHRDYIC                    BIT18
#define SCU_CIR_XTLRDYIC                    BIT17
#define SCU_CIR_RC32KRDYIC                  BIT16
#define SCU_CIR_RC4MRDYIE                   BIT13
#define SCU_CIR_PLLLOCKIE                   BIT12
#define SCU_CIR_XTHRDYIE                    BIT11
#define SCU_CIR_RCHRDYIE                    BIT10
#define SCU_CIR_XTLRDYIE                    BIT9
#define SCU_CIR_RC32KRDYIE                  BIT8
#define SCU_CIR_RC4MRDYIF                   BIT5
#define SCU_CIR_PLLLOCKIF                   BIT4
#define SCU_CIR_XTHRDYIF                    BIT3
#define SCU_CIR_RCHRDYIF                    BIT2
#define SCU_CIR_XTLRDYIF                    BIT1
#define SCU_CIR_RC32KRDYIF                  BIT0

/****************  Bit definition for SCU IPCKENR register  ********************/
#define SCU_IPCKENR_ROMCLKEN                BIT30
#define SCU_IPCKENR_HRNGCLKEN               BIT29
#define SCU_IPCKENR_AESCLKEN                BIT28
#define SCU_IPCKENR_TIM17CLKEN              BIT27
#define SCU_IPCKENR_TIM16CLKEN              BIT26
#define SCU_IPCKENR_TIM15CLKEN              BIT25
#define SCU_IPCKENR_TIM14CLKEN              BIT24
#define SCU_IPCKENR_TIM6CLKEN               BIT22
#define SCU_IPCKENR_TIM3CLKEN               BIT21
#define SCU_IPCKENR_TIM1CLKEN               BIT20
#define SCU_IPCKENR_UART3CLKEN              BIT19
#define SCU_IPCKENR_OPACLKEN                BIT17
#define SCU_IPCKENR_CMPCLKEN                BIT16
#define SCU_IPCKENR_TKEYCLKEN               BIT15
#define SCU_IPCKENR_ADCCLKEN                BIT14
#define SCU_IPCKENR_RTCCLKEN                BIT13
#define SCU_IPCKENR_DMACCLKEN               BIT12
#define SCU_IPCKENR_CRCCLKEN                BIT11
#define SCU_IPCKENR_LPUARTCLKEN             BIT8
#define SCU_IPCKENR_I2C2CLKEN               BIT7
#define SCU_IPCKENR_I2C1CLKEN               BIT6
#define SCU_IPCKENR_SPI2CLKEN               BIT5
#define SCU_IPCKENR_SPI1CLKEN               BIT4
#define SCU_IPCKENR_UART2CLKEN              BIT3
#define SCU_IPCKENR_UART1CLKEN              BIT2

/****************  Bit definition for SCU IPCKENR2 register  ********************/
#define SCU_IPCKENR2_EFCCLKEN               BIT6
#define SCU_IPCKENR2_SRAMCLKEN              BIT5
#define SCU_IPCKENR2_EXTICLKEN              BIT4
#define SCU_IPCKENR2_IWDTCLKEN              BIT3
#define SCU_IPCKENR2_WDTCLKEN               BIT2
#define SCU_IPCKENR2_GPIO2CLKEN             BIT1
#define SCU_IPCKENR2_GPIO1CLKEN             BIT0

/****************  Bit definition for SCU RCHCR register  **********************/
#define SCU_RCHCR_RC4MRDY                   BIT22
#define SCU_RCHCR_RC4M_TRIM                (BIT21|BIT20|BIT19|BIT18|BIT17)
#define SCU_RCHCR_RC4M_EN                   BIT16
#define SCU_RCHCR_RCHRDY                    BIT9
#define SCU_RCHCR_RCH_DIV                   BIT8
#define SCU_RCHCR_RCH_TRIM                 (BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1)
#define SCU_RCHCR_RCH_EN                    BIT0

/****************  Bit definition for SCU RCHCR register  **********************/
#define SCU_XTHCR_XTHRDY                    BIT4
#define SCU_XTHCR_XTH_RDYTIME              (BIT3|BIT2)
#define SCU_XTHCR_XTH_BYP                   BIT1
#define SCU_XTHCR_XTH_EN                    BIT0
#define SCU_XTHCR_READYTIME_1024             0
#define SCU_XTHCR_READYTIME_4096             BIT2 
#define SCU_XTHCR_READYTIME_16384            BIT3
#define SCU_XTHCR_READYTIME_32768            (BIT3|BIT2)    

/****************  Bit definition for SCU PLLCR register  **********************/
#define SCU_PLLCR_PLL_LOCK_SEL              BIT31
#define SCU_PLLCR_PLL_FREE_RUN              BIT30
#define SCU_PLLCR_PLL_LOCK                  BIT29
#define SCU_PLLCR_PLL_RUN_DLY              (BIT28|BIT27|BIT26|BIT25|BIT24|BIT23)
#define SCU_PLLCR_PLL_UPDATE_EN             BIT22
#define SCU_PLLCR_PLL_SLEEP                 BIT21
#define SCU_PLLCR_PLL_OD                   (BIT19|BIT18)
#define SCU_PLLCR_PLL_N                    (BIT15|BIT14)
#define SCU_PLLCR_PLL_M                    (BIT6|BIT5|BIT4|BIT3)
#define SCU_PLLCR_PLL_SRC_SEL              (BIT2|BIT1)
#define SCU_PLLCR_PLL_EN                   (BIT0)

/****************  Bit definition for SCU LDOCR register  **********************/
#define SCU_LDOCR_LPLDO12_TRIM              (BIT28|BIT27|BIT26)
#define SCU_LDOCR_LPSTP_SFT                  BIT25
#define SCU_LDOCR_LPLDO12_EN_SFT             BIT24
#define SCU_LDOCR_MLDO12_LOWP_SFT            BIT22
#define SCU_LDOCR_MLDO12_LV_SFT             (BIT21|BIT20)
#define SCU_LDOCR_LDO18A_EN                  BIT19
#define SCU_LDOCR_ANATEST_SEL               (BIT18|BIT17|BIT16)
#define SCU_LDOCR_LDO18A_TRIM               (BIT15|BIT14|BIT13)
#define SCU_LDOCR_LDO18_TRIM                (BIT12|BIT11|BIT10)
#define SCU_LDOCR_LDO18_EN                   BIT9
#define SCU_LDOCR_LDOCTL_SEL                 BIT8
#define SCU_LDOCR_LDO12_TRIM                (BIT7|BIT6|BIT5|BIT4)
#define SCU_LDOCR_VREF_TRIM                 (BIT2|BIT1|BIT0)

/****************  Bit definition for SCU WMR register  ***********************/
#define SCU_WMR_RTC_READY                    BIT6
#define SCU_WMR_REMAP_FLAG                   BIT4
#define SCU_WMR_BOOTPIN                      BIT3

/****************  Bit definition for SCU CLKOCR register  ********************/
#define SCU_CLKOCR_BUZZER2_EN                BIT31
#define SCU_CLKOCR_BUZZER2_POL               BIT30
#define SCU_CLKOCR_BUZZER2_DIV              (BIT29|BIT28|BIT27|BIT26|BIT25|BIT24)
#define SCU_CLKOCR_BUZZER_EN                 BIT23
#define SCU_CLKOCR_BUZZER_POL                BIT22
#define SCU_CLKOCR_BUZZER_DIV               (0x3FFFE0)
#define SCU_CLKOCR_CLKOUT_SEL                BIT4
#define SCU_CLKOCR_CLKTEST_SEL              (BIT3|BIT2|BIT1|BIT0)

/****************  Bit definition for SCU SYSCFG1 register  ********************/
#define SCU_SYSCFG1_TIM15_CH2_SEL           (BIT25|BIT24)
#define SCU_SYSCFG1_TIM15_CH1_SEL           (BIT23|BIT22)
#define SCU_SYSCFG1_TIM14_CH1_SEL            BIT20
#define SCU_SYSCFG1_IR_MODE                 (BIT18|BIT17)
#define SCU_SYSCFG1_IR_POL                   BIT16
#define SCU_SYSCFG1_SRAM_PEF                 BIT8
#define SCU_SYSCFG1_LVD_LOCK                 BIT2
#define SCU_SYSCFG1_SRAM_PARITY_LOCK         BIT1
#define SCU_SYSCFG1_LOCKUP_LOCK              BIT0

/****************  Bit definition for SCU LVDCFG register  ********************/
#define SCU_LVDCFG_LVD_VALUE                 BIT15
#define SCU_LVDCFG_LVD_FILTER                BIT14
#define SCU_LVDCFG_FLT_TIME                 (BIT11|BIT10|BIT9)
#define SCU_LVDCFG_LVD_FLTEN                 BIT8
#define SCU_LVDCFG_LVD_TRIM                 (BIT4|BIT3|BIT2|BIT1)
#define SCU_LVDCFG_LVDEN                     BIT0

/****************  Bit definition for SCU STOPCFG register  ********************/
#define SCU_STOPCFG_LPLDO12_LV              (BIT15|BIT14|BIT13)
#define SCU_STOPCFG_TKPCLK_SEL               BIT12
#define SCU_STOPCFG_PDDS                     BIT11
#define SCU_STOPCFG_TK_LPLDOLV               BIT10
#define SCU_STOPCFG_LPSTOP                   BIT9
#define SCU_STOPCFG_RCH_DIV_EN               BIT8
#define SCU_STOPCFG_MLDO12_LOWP              BIT6
#define SCU_STOPCFG_MLDO12_LV               (BIT5|BIT4)
#define SCU_STOPCFG_RC64MPDEN                BIT3
#define SCU_STOPCFG_RTC_WE                   BIT0

/**************  Bit definition for SCU VECTOROFFSET register  *****************/
#define SCU_VECTOROFFSET_VOFFSETEN           BIT0

/****************  Bit definition for SCU PASEL1 register  *********************/
#define SCU_PASEL1_PA7_SEL                  (BIT31|BIT30|BIT29|BIT28)
#define SCU_PASEL1_PA6_SEL                  (BIT27|BIT26|BIT25|BIT24)
#define SCU_PASEL1_PA5_SEL                  (BIT23|BIT22|BIT21|BIT20)
#define SCU_PASEL1_PA4_SEL                  (BIT19|BIT18|BIT17|BIT16)
#define SCU_PASEL1_PA3_SEL                  (BIT15|BIT14|BIT13|BIT12)
#define SCU_PASEL1_PA2_SEL                  (BIT11|BIT10|BIT9|BIT8)
#define SCU_PASEL1_PA1_SEL                  (BIT7|BIT6|BIT5|BIT4)
#define SCU_PASEL1_PA0_SEL                  (BIT3|BIT2|BIT1|BIT0)

/****************  Bit definition for SCU PASEL2 register  *********************/
#define SCU_PASEL2_PA15_SEL                 (BIT31|BIT30|BIT29|BIT28)
#define SCU_PASEL2_PA14_SEL                 (BIT27|BIT26|BIT25|BIT24)
#define SCU_PASEL2_PA13_SEL                 (BIT23|BIT22|BIT21|BIT20)
#define SCU_PASEL2_PA12_SEL                 (BIT19|BIT18|BIT17|BIT16)
#define SCU_PASEL2_PA11_SEL                 (BIT15|BIT14|BIT13|BIT12)
#define SCU_PASEL2_PA10_SEL                 (BIT11|BIT10|BIT9|BIT8)
#define SCU_PASEL2_PA9_SEL                  (BIT7|BIT6|BIT5|BIT4)
#define SCU_PASEL2_PA8_SEL                  (BIT3|BIT2|BIT1|BIT0)

/****************  Bit definition for SCU PBSEL1 register  *********************/
#define SCU_PBSEL1_PB7_SEL                  (BIT31|BIT30|BIT29|BIT28)
#define SCU_PBSEL1_PB6_SEL                  (BIT27|BIT26|BIT25|BIT24)
#define SCU_PBSEL1_PB5_SEL                  (BIT23|BIT22|BIT21|BIT20)
#define SCU_PBSEL1_PB4_SEL                  (BIT19|BIT18|BIT17|BIT16)
#define SCU_PBSEL1_PB3_SEL                  (BIT15|BIT14|BIT13|BIT12)
#define SCU_PBSEL1_PB2_SEL                  (BIT11|BIT10|BIT9|BIT8)
#define SCU_PBSEL1_PB1_SEL                  (BIT7|BIT6|BIT5|BIT4)
#define SCU_PBSEL1_PB0_SEL                  (BIT3|BIT2|BIT1|BIT0)

/****************  Bit definition for SCU PBSEL2 register  *********************/
#define SCU_PBSEL2_PB15_SEL                 (BIT31|BIT30|BIT29|BIT28)
#define SCU_PBSEL2_PB14_SEL                 (BIT27|BIT26|BIT25|BIT24)
#define SCU_PBSEL2_PB13_SEL                 (BIT23|BIT22|BIT21|BIT20)
#define SCU_PBSEL2_PB12_SEL                 (BIT19|BIT18|BIT17|BIT16)
#define SCU_PBSEL2_PB11_SEL                 (BIT15|BIT14|BIT13|BIT12)
#define SCU_PBSEL2_PB10_SEL                 (BIT11|BIT10|BIT9|BIT8)
#define SCU_PBSEL2_PB9_SEL                  (BIT7|BIT6|BIT5|BIT4)
#define SCU_PBSEL2_PB8_SEL                  (BIT3|BIT2|BIT1|BIT0)

/****************  Bit definition for SCU PASTR register  **********************/
#define SCU_PASTR_PA15_STH                  (BIT31|BIT30)
#define SCU_PASTR_PA14_STH                  (BIT29|BIT28)
#define SCU_PASTR_PA13_STH                  (BIT27|BIT26)
#define SCU_PASTR_PA12_STH                  (BIT25|BIT24)
#define SCU_PASTR_PA11_STH                  (BIT23|BIT22)
#define SCU_PASTR_PA10_STH                  (BIT21|BIT20)
#define SCU_PASTR_PA9_STH                   (BIT19|BIT18)
#define SCU_PASTR_PA8_STH                   (BIT17|BIT16)
#define SCU_PASTR_PA7_STH                   (BIT15|BIT14)
#define SCU_PASTR_PA6_STH                   (BIT13|BIT12)
#define SCU_PASTR_PA5_STH                   (BIT11|BIT10)
#define SCU_PASTR_PA4_STH                   (BIT9|BIT8)
#define SCU_PASTR_PA3_STH                   (BIT7|BIT6)
#define SCU_PASTR_PA2_STH                   (BIT5|BIT4)
#define SCU_PASTR_PA1_STH                   (BIT3|BIT2)
#define SCU_PASTR_PA0_STH                   (BIT1|BIT0)

/****************  Bit definition for SCU PBSTR register  **********************/
#define SCU_PBSTR_PB15_STH                  (BIT31|BIT30)
#define SCU_PBSTR_PB14_STH                  (BIT29|BIT28)
#define SCU_PBSTR_PB13_STH                  (BIT27|BIT26)
#define SCU_PBSTR_PB12_STH                  (BIT25|BIT24)
#define SCU_PBSTR_PB11_STH                  (BIT23|BIT22)
#define SCU_PBSTR_PB10_STH                  (BIT21|BIT20)
#define SCU_PBSTR_PB9_STH                   (BIT19|BIT18)
#define SCU_PBSTR_PB8_STH                   (BIT17|BIT16)
#define SCU_PBSTR_PB7_STH                   (BIT15|BIT14)
#define SCU_PBSTR_PB6_STH                   (BIT13|BIT12)
#define SCU_PBSTR_PB5_STH                   (BIT11|BIT10)
#define SCU_PBSTR_PB4_STH                   (BIT9|BIT8)
#define SCU_PBSTR_PB3_STH                   (BIT7|BIT6)
#define SCU_PBSTR_PB2_STH                   (BIT5|BIT4)
#define SCU_PBSTR_PB1_STH                   (BIT3|BIT2)
#define SCU_PBSTR_PB0_STH                   (BIT1|BIT0)

/****************  Bit definition for SCU PCSEL1 register  *********************/
#define SCU_PCSEL1_PC7_SEL                  (BIT31|BIT30|BIT29|BIT28)
#define SCU_PCSEL1_PC6_SEL                  (BIT27|BIT26|BIT25|BIT24)
#define SCU_PCSEL1_PC5_SEL                  (BIT23|BIT22|BIT21|BIT20)
#define SCU_PCSEL1_PC4_SEL                  (BIT19|BIT18|BIT17|BIT16)
#define SCU_PCSEL1_PC3_SEL                  (BIT15|BIT14|BIT13|BIT12)
#define SCU_PCSEL1_PC2_SEL                  (BIT11|BIT10|BIT9|BIT8)
#define SCU_PCSEL1_PC1_SEL                  (BIT7|BIT6|BIT5|BIT4)
#define SCU_PCSEL1_PC0_SEL                  (BIT3|BIT2|BIT1|BIT0)

/****************  Bit definition for SCU PCSEL2 register  *********************/
#define SCU_PCSEL2_PC15_SEL                 (BIT31|BIT30|BIT29|BIT28)
#define SCU_PCSEL2_PC14_SEL                 (BIT27|BIT26|BIT25|BIT24)
#define SCU_PCSEL2_PC13_SEL                 (BIT23|BIT22|BIT21|BIT20)
#define SCU_PCSEL2_PC12_SEL                 (BIT19|BIT18|BIT17|BIT16)
#define SCU_PCSEL2_PC11_SEL                 (BIT15|BIT14|BIT13|BIT12)
#define SCU_PCSEL2_PC10_SEL                 (BIT11|BIT10|BIT9|BIT8)
#define SCU_PCSEL2_PC9_SEL                  (BIT7|BIT6|BIT5|BIT4)
#define SCU_PCSEL2_PC8_SEL                  (BIT3|BIT2|BIT1|BIT0)

/****************  Bit definition for SCU PDSEL1 register  *********************/
#define SCU_PDSEL1_PD7_SEL                  (BIT31|BIT30|BIT29|BIT28)
#define SCU_PDSEL1_PD6_SEL                  (BIT27|BIT26|BIT25|BIT24)
#define SCU_PDSEL1_PD5_SEL                  (BIT23|BIT22|BIT21|BIT20)
#define SCU_PDSEL1_PD4_SEL                  (BIT19|BIT18|BIT17|BIT16)
#define SCU_PDSEL1_PD3_SEL                  (BIT15|BIT14|BIT13|BIT12)
#define SCU_PDSEL1_PD2_SEL                  (BIT11|BIT10|BIT9|BIT8)
#define SCU_PDSEL1_PD1_SEL                  (BIT7|BIT6|BIT5|BIT4)
#define SCU_PDSEL1_PD0_SEL                  (BIT3|BIT2|BIT1|BIT0)

/****************  Bit definition for SCU PCSTR register  **********************/
#define SCU_PCSTR_PC12_STH                  (BIT25|BIT24)
#define SCU_PCSTR_PC11_STH                  (BIT23|BIT22)
#define SCU_PCSTR_PC10_STH                  (BIT21|BIT20)
#define SCU_PCSTR_PC9_STH                   (BIT19|BIT18)
#define SCU_PCSTR_PC8_STH                   (BIT17|BIT16)
#define SCU_PCSTR_PC7_STH                   (BIT15|BIT14)
#define SCU_PCSTR_PC6_STH                   (BIT13|BIT12)
#define SCU_PCSTR_PC5_STH                   (BIT11|BIT10)
#define SCU_PCSTR_PC4_STH                   (BIT9|BIT8)
#define SCU_PCSTR_PC3_STH                   (BIT7|BIT6)
#define SCU_PCSTR_PC2_STH                   (BIT5|BIT4)
#define SCU_PCSTR_PC1_STH                   (BIT3|BIT2)
#define SCU_PCSTR_PC0_STH                   (BIT1|BIT0)

/****************  Bit definition for SCU PDSTR register  **********************/
#define SCU_PDSTR_PD7_STH                   (BIT15|BIT14)
#define SCU_PDSTR_PD6_STH                   (BIT13|BIT12)
#define SCU_PDSTR_PD5_STH                   (BIT11|BIT10)
#define SCU_PDSTR_PD4_STH                   (BIT9|BIT8)
#define SCU_PDSTR_PD3_STH                   (BIT7|BIT6)
#define SCU_PDSTR_PD2_STH                   (BIT5|BIT4)
#define SCU_PDSTR_PD1_STH                   (BIT3|BIT2)
#define SCU_PDSTR_PD0_STH                   (BIT1|BIT0)

/*
 * @brief  Peripheral Enable structures definition
 */
typedef enum
{
    EN_CAN1   = 45,
    EN_ROM    = 44,
    EN_HRNG   = 43,
    EN_AES    = 42,
    EN_TIM17  = 41,
    EN_TIM16  = 40,
    EN_TIM15  = 39,
    EN_TIM14  = 38,
    EN_TIM7   = 37,
    EN_TIM6   = 36,
    EN_TIM3   = 35,
    EN_TIM1   = 34,
    EN_UART3  = 33,
    EN_TIM2   = 32,
    EN_OPA    = 31,
    EN_COMP   = 30,
    EN_TKEY   = 29,
    EN_ADC    = 28,
    EN_RTC    = 27,
    EN_DMA    = 26,
    EN_CRC    = 25,
    EN_DAC    = 24,
    EN_USB    = 23,
    EN_LPUART = 22,
    EN_I2C2   = 21,
    EN_I2C1   = 20,
    EN_SPI2   = 19,
    EN_SPI1   = 18,
    EN_UART2  = 17,
    EN_UART1  = 16,
    EN_CAN2   = 15,
    EN_I2S1   = 14,
    
    EN_SPI4   = 13,
    EN_GPIOEF = 12,
    EN_SPI3   = 11,
    EN_UART4  = 10,
    EN_TIM4   = 9,
    EN_FAU    = 8,
    EN_EFC    = 6,
    EN_SRAM   = 5,
    EN_EXTI   = 4,
    EN_IWDT   = 3,
    EN_WDT    = 2,
    EN_GPIOCD = 1,
    EN_GPIOAB = 0,
}enum_Enable_ID_t;

typedef enum
{
    RESET_REASON_LOW_VOLTAGE   = 0x00U,   // low voltage detected, leads to reset  
	RESET_REASON_WDT           = 0x01U,   // System WDT reset 
	RESET_REASON_IWDT          = 0x02U,   // IWDT reset 
	RESET_REASON_LOCKUP        = 0x03U,   // cortex-m0 lockup leads to reset  
	RESET_REASON_SYSREQ        = 0x04U,   // system reset 
	RESET_REASON_RSTN          = 0x05U,   // RSTN negative pulse leads to reset   
	RESET_REASON_EFC           = 0x06U,   // efc reset leads to reset   
    RESET_REASON_SOFT          = 0x07U,   // soft reset 
	RESET_REASON_POR12         = 0x09U,   // core power on reset, rtc not reset, eg:wakeup from standby   
	RESET_REASON_POR           = 0x0AU,   // chip power on reset 
	RESET_REASON_INVALID,  
}RESET_REASON; 

#define NVIC_PRIORITY_GROUP_3  0x00000004U   // 3 bits for pre-emption priority, 0 bit for subpriority   
#define NVIC_PRIORITY_GROUP_2  0x00000005U   // 2 bits for pre-emption priority, 1 bit for subpriority    
#define NVIC_PRIORITY_GROUP_1  0x00000006U   // 1 bits for pre-emption priority, 2 bit for subpriority    
#define NVIC_PRIORITY_GROUP_0  0x00000007U   // 0 bits for pre-emption priority, 3 bit for subpriority         

#define SYSTEM_TIMEOUT  (1000000)   


/* System_Init */
void System_Init(void);

/* System_Core_Config */
void System_Core_Config(void);

/* System_Clock_Init */
bool System_Clock_Init(uint32_t fu32_Clock);

/* System_SysTick_Init */
void System_SysTick_Init(void);

/* System_Get_SystemClock */
uint32_t System_Get_SystemClock(void);

/* System_Get_APBClock */
uint32_t System_Get_APBClock(void);

/* System_Module_Reset */
void System_Module_Reset(enum_RST_ID_t fe_ID_Index);

/* System_Module_Enable */
void System_Module_Enable(enum_Enable_ID_t fe_ID_Index);

/* System_Module_Disable */
void System_Module_Disable(enum_Enable_ID_t fe_ID_Index);

/* System_Delay */
void System_Delay(volatile uint32_t fu32_Delay); 

/* System_Delay_MS */
void System_Delay_MS(volatile uint32_t fu32_Delay);

/* System_Enable_RC32K */
void System_Enable_RC32K(void);

/* System_Disable_RC32K */
void System_Disable_RC32K(void);

/* System_Enable_XTAL */
void System_Enable_XTAL(void);

/* System_Disable_XTAL */
void System_Disable_XTAL(void);
 
/* System_Clear_Stop_Wakeup */
void System_Clear_Stop_Wakeup(void);

/* System_Enter_Standby_Mode */
void System_Enter_Standby_Mode(void);       

/* System_Enter_Stop_Mode */
void System_Enter_Stop_Mode(uint8_t STOPEntry);    

/* System_Enter_Sleep_Mode */     
void System_Enter_Sleep_Mode(uint8_t SleepEntry);   

/* System_Enable_Disable_Reset */
void System_Enable_Disable_Reset(RESET_ENABLE_SOURCE source, FUNC_DISABLE_ENABLE enable_disable);   

/* System_Reset_MCU */   
void System_Reset_MCU(RESET_SOURCE source);    

/* System_Enable_Disable_RTC_Domain_Access */
void System_Enable_Disable_RTC_Domain_Access(FUNC_DISABLE_ENABLE enable_disable);  

/* System_Return_Last_Reset_Reason */
RESET_REASON System_Return_Last_Reset_Reason(void) ;   

/* System_Set_Buzzer_Divider */    
void System_Set_Buzzer_Divider(uint32_t div, FUNC_DISABLE_ENABLE enable);     

/* System_USB_PHY_Config */  
uint32_t System_USB_PHY_Config(void);  

#endif  




