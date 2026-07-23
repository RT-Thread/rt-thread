/*******************************************************************************
* Copyright (C) 2018, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/******************************************************************************/
/** \file gpio.h
 **
 ** GPIO driver
 ** @link GPIO Group Some description @endlink
 **
 **   - 2018-04-18
 **
 ******************************************************************************/

#ifndef __GPIO_H__
#define __GPIO_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32l196_ddl.h"


/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup GpioGroup General Purpose I/O (GPIO)
 **
 **
 ******************************************************************************/
//@{
#define GPIO_GPSZ       (0x40u)

/*******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief GPIO PORT类型定义
 ******************************************************************************/
typedef enum en_gpio_port
{
    GpioPortA = 0x00u,                 ///< GPIO PORT A
    GpioPortB = 0x40u,                 ///< GPIO PORT B
    GpioPortC = 0x80u,                 ///< GPIO PORT C
    GpioPortD = 0xc0u,                 ///< GPIO PORT D
    GpioPortE = 0x1000u,               ///< GPIO PORT E
    GpioPortF = 0x1040u,               ///< GPIO PORT F
}en_gpio_port_t;

/**
 *******************************************************************************
 ** \brief GPIO PIN类型定义
 ******************************************************************************/
typedef enum en_gpio_pin
{
    GpioPin0  = 0u,                 ///< GPIO PIN0
    GpioPin1  = 1u,                 ///< GPIO PIN1
    GpioPin2  = 2u,                 ///< GPIO PIN2
    GpioPin3  = 3u,                 ///< GPIO PIN3
    GpioPin4  = 4u,                 ///< GPIO PIN4
    GpioPin5  = 5u,                 ///< GPIO PIN5
    GpioPin6  = 6u,                 ///< GPIO PIN6
    GpioPin7  = 7u,                 ///< GPIO PIN7
    GpioPin8  = 8u,                 ///< GPIO PIN8
    GpioPin9  = 9u,                 ///< GPIO PIN9
    GpioPin10 = 10u,                ///< GPIO PIN10
    GpioPin11 = 11u,                ///< GPIO PIN11
    GpioPin12 = 12u,                ///< GPIO PIN12
    GpioPin13 = 13u,                ///< GPIO PIN13
    GpioPin14 = 14u,                ///< GPIO PIN14
    GpioPin15 = 15u,                ///< GPIO PIN15
}en_gpio_pin_t;

/**
 *******************************************************************************
 ** \brief GPIO 端口复用功能(AF-Alternate function)类型定义
 ** \note  具体功能及含义请参考用户手册GPIO复用表或下表
 ******************************************************************************/
typedef enum en_gpio_af
{
    GpioAf0  = 0u,      ///< GPIO功能
    GpioAf1  = 1u,      ///< GPIO AF1:复用功能1
    GpioAf2  = 2u,      ///< GPIO AF2:复用功能2
    GpioAf3  = 3u,      ///< GPIO AF3:复用功能3
    GpioAf4  = 4u,      ///< GPIO AF4:复用功能4
    GpioAf5  = 5u,      ///< GPIO AF5:复用功能5
    GpioAf6  = 6u,      ///< GPIO AF6:复用功能6
    GpioAf7  = 7u,      ///< GPIO AF7:复用功能7
}en_gpio_af_t;

///*||======||=============||=============||=============||=============||=============||=============||=============||*///
///*||PSEL  ||   GpioAf1   ||   GpioAf2   ||   GpioAf3   ||   GpioAf4   ||   GpioAf5   ||   GpioAf6   ||   GpioAf7   ||*///
///*||======||=============||=============||=============||=============||=============||=============||=============||*///
///*||PA00  ||UART1_CTS    ||LPUART1_TXD  ||TIM0_ETR     ||VC0_OUT      ||TIM1_CHA     ||TIM3_ETR     ||TIM0_CHA     ||*///
///*||PA01  ||UART1_RTS    ||LPUART1_RXD  ||TIM0_CHB     ||TIM1_ETR     ||TIM1_CHB     ||HCLK_OUT     ||SPI1_MOSI    ||*///
///*||PA02  ||UART1_TXD    ||TIM0_CHA     ||VC1_OUT      ||TIM1_CHA     ||TIM2_CHA     ||PCLK_OUT     ||SPI1_MISO    ||*///
///*||PA03  ||UART1_RXD    ||TIM0_GATE    ||TIM1_CHB     ||TIM2_CHB     ||SPI1_CS      ||TIM3_CH1A    ||TIM5_CHA     ||*///
///*||PA04  ||SPI0_CS      ||UART1_TXD    ||PCA_CH4      ||TIM2_ETR     ||TIM5_CHA     ||LVD_OUT      ||TIM3_CH2B    ||*///
///*||PA05  ||SPI0_SCK     ||TIM0_ETR     ||PCA_ECI      ||TIM0_CHA     ||TIM5_CHB     ||XTL_OUT      ||XTH_OUT      ||*///
///*||PA06  ||SPI0_MISO    ||PCA_CH0      ||TIM3_BK      ||TIM1_CHA     ||VC0_OUT      ||TIM3_GATE    ||LPUART0_CTS  ||*///
///*||PA07  ||SPI0_MOSI    ||PCA_CH1      ||HCLK_OUT     ||TIM3_CH0B    ||TIM2_CHA     ||VC1_OUT      ||TIM4_CHB     ||*///
///*||PA08  ||UART0_TXD    ||TIM3_CH0A    ||             ||             ||TIM1_GATE    ||TIM4_CHA     ||TIM3_BK      ||*///
///*||PA09  ||UART0_TXD    ||TIM3_CH1A    ||TIM0_BK      ||I2C0_SCL     ||             ||HCLK_OUT     ||TIM5_CHA     ||*///
///*||PA10  ||UART0_RXD    ||TIM3_CH2A    ||TIM2_BK      ||I2C0_SDA     ||TIM2_GATE    ||PCLK_OUT     ||TIM6_CHA     ||*///
///*||PA11  ||UART0_CTS    ||TIM3_GATE    ||I2C1_SCL     ||             ||VC0_OUT      ||SPI0_MISO    ||TIM4_CHB     ||*///
///*||PA12  ||UART0_RTS    ||TIM3_ETR     ||I2C1_SDA     ||             ||VC1_OUT      ||SPI0_MOSI    ||PCNT_S0      ||*///
///*||PA13  ||IR_OUT       ||UART0_RXD    ||LVD_OUT      ||TIM3_ETR     ||RTC_1HZ      ||PCNT_S1      ||VC2_OUT      ||*///
///*||PA14  ||UART1_TXD    ||UART0_TXD    ||TIM3_CH2A    ||LVD_OUT      ||RCH_OUT      ||RCL_OUT      ||PLL_OUT      ||*///
///*||PA15  ||SPI0_CS      ||UART1_RXD    ||LPUART1_RTS  ||TIM0_ETR     ||TIM0_CHA     ||TIM3_CH1A    ||             ||*///
///*||PB00  ||PCA_CH2      ||TIM3_CH1B    ||LPUART0_TXD  ||TIM5_CHB     ||RCH_OUT      ||RCL_OUT      ||PLL_OUT      ||*///
///*||PB01  ||PCA_CH3      ||PCLK_OUT     ||TIM3_CH2B    ||TIM6_CHB     ||LPUART0_RTS  ||VC2_OUT      ||TCLK_OUT　   ||*///
///*||PB02  ||LPTIM_TOG    ||PCA_ECI      ||LPUART1_TXD  ||TIM4_CHA     ||TIM1_BK      ||TIM0_BK      ||TIM2_BK      ||*///
///*||PB03  ||SPI0_SCK     ||TIM0_CHB     ||TIM1_GATE    ||TIM3_CH0A    ||LPTIM_GATE   ||XTL_OUT      ||XTH_OUT      ||*///
///*||PB04  ||SPI0_MISO    ||PCA_CH0      ||TIM2_BK      ||UART0_CTS    ||TIM2_GATE    ||TIM3_CH0B    ||LPTIM_ETR    ||*///
///*||PB05  ||SPI0_MOSI    ||             ||TIM1_BK      ||PCA_CH1      ||LPTIM_GATE   ||PCNT_S0      ||UART0_RTS    ||*///
///*||PB06  ||I2C0_SCL     ||UART0_TXD    ||TIM1_CHB     ||TIM0_CHA     ||LPTIM_ETR    ||TIM3_CH0A    ||LPTIM_TOG    ||*///
///*||PB07  ||I2C0_SDA     ||UART0_RXD    ||TIM2_CHB     ||LPUART1_CTS  ||TIM0_CHB     ||LPTIM_TOGN   ||PCNT_S1      ||*///
///*||PB08  ||I2C0_SCL     ||TIM1_CHA     ||             ||TIM2_CHA     ||TIM0_GATE    ||TIM3_CH2A    ||UART0_TXD    ||*///
///*||PB09  ||I2C0_SDA     ||IR_OUT       ||SPI1_CS      ||TIM2_CHA     ||             ||TIM2_CHB     ||UART0_RXD    ||*///
///*||PB10  ||I2C1_SCL     ||SPI1_SCK     ||TIM1_CHA     ||LPUART0_TXD  ||TIM3_CH1A    ||LPUART1_RTS  ||UART1_RTS    ||*///
///*||PB11  ||I2C1_SDA     ||TIM1_CHB     ||LPUART0_RXD  ||TIM2_GATE    ||TIM6_CHA     ||LPUART1_CTS  ||UART1_CTS    ||*///
///*||PB12  ||SPI1_CS      ||TIM3_BK      ||LPUART0_TXD  ||TIM0_BK      ||             ||LPUART0_RTS  ||TIM6_CHA     ||*///
///*||PB13  ||SPI1_SCK     ||I2C1_SCL     ||TIM3_CH0B    ||LPUART0_CTS  ||TIM1_CHA     ||TIM1_GATE    ||TIM6_CHB     ||*///
///*||PB14  ||SPI1_MISO    ||I2C1_SDA     ||TIM3_CH1B    ||TIM0_CHA     ||RTC_1HZ      ||LPUART0_RTS  ||TIM1_BK      ||*///
///*||PB15  ||SPI1_MOSI    ||TIM3_CH2B    ||TIM0_CHB     ||TIM0_GATE    ||             ||             ||LPUART1_RXD  ||*///
///*||PC00  ||LPTIM_GATE   ||PCNT_S0      ||UART1_CTS    ||UART2_RTS    ||             ||             ||             ||*///
///*||PC01  ||LPTIM_TOG    ||TIM5_CHB     ||UART1_RTS    ||PCNT_S0FO    ||             ||UART2_CTS    ||             ||*///
///*||PC02  ||SPI1_MISO    ||LPTIM_TOGN   ||PCNT_S1      ||UART2_RXD    ||             ||             ||             ||*///
///*||PC03  ||SPI1_MOSI    ||LPTIM_ETR    ||LPTIM_TOGN   ||PCNT_S1FO    ||UART2_TXD    ||             ||             ||*///
///*||PC04  ||LPUART0_TXD  ||TIM2_ETR     ||IR_OUT       ||VC2_OUT      ||             ||             ||             ||*///
///*||PC05  ||LPUART0_RXD  ||TIM6_CHB     ||PCA_CH4      ||             ||             ||             ||             ||*///
///*||PC06  ||PCA_CH0      ||TIM4_CHA     ||TIM2_CHA     ||LPTIM1_GATE  ||             ||UART3_RXD    ||             ||*///
///*||PC07  ||PCA_CH1      ||TIM5_CHA     ||TIM2_CHB     ||LPTIM1_ETR   ||             ||UART3_TXD    ||             ||*///
///*||PC08  ||PCA_CH2      ||TIM6_CHA     ||TIM2_ETR     ||LPTIM1_TOG   ||             ||UART3_CTS    ||             ||*///
///*||PC09  ||PCA_CH3      ||TIM4_CHB     ||TIM1_ETR     ||LPTIM1_TOGN  ||             ||UART3_RTS    ||             ||*///
///*||PC10  ||LPUART1_TXD  ||LPUART0_TXD  ||PCA_CH2      ||             ||             ||             ||             ||*///
///*||PC11  ||LPUART1_RXD  ||LPUART0_RXD  ||PCA_CH3      ||PCNT_S0FO    ||             ||             ||             ||*///
///*||PC12  ||LPUART0_TXD  ||LPUART1_TXD  ||PCA_CH4      ||PCNT_S1FO    ||             ||             ||             ||*///
///*||PC13  ||             ||RTC_1HZ      ||TIM3_CH1B    ||             ||             ||             ||             ||*///
///*||PC14  ||             ||             ||             ||             ||             ||             ||             ||*///
///*||PC15  ||             ||             ||             ||             ||             ||             ||             ||*///
///*||PD00  ||             ||SPI1_CS      ||             ||             ||             ||             ||             ||*///
///*||PD01  ||             ||SPI1_SCK     ||             ||             ||             ||             ||             ||*///
///*||PD02  ||PCA_ECI      ||LPUART0_RTS  ||TIM1_ETR     ||             ||             ||             ||             ||*///
///*||PD03  ||UART1_CTS    ||SPI1_MISO    ||LPTIM1_TOG   ||             ||             ||             ||             ||*///
///*||PD04  ||UART1_RTS    ||SPI1_MOSI    ||LPTIM1_TOGN  ||             ||             ||             ||             ||*///
///*||PD05  ||UART1_TXD    ||LPTIM1_GATE  ||             ||             ||             ||             ||             ||*///
///*||PD06  ||UART1_RXD    ||LPTIM1_ETR   ||             ||             ||             ||             ||             ||*///
///*||PD07  ||UART1_TXD    ||             ||             ||             ||             ||             ||             ||*///
///*||PD08  ||LPUART0_TXD  ||             ||             ||             ||             ||             ||             ||*///
///*||PD09  ||LPUART0_RXD  ||             ||             ||             ||             ||             ||             ||*///
///*||PD10  ||LPUART0_TXD  ||             ||             ||             ||             ||             ||             ||*///
///*||PD11  ||LPUART0_CTS  ||             ||             ||             ||             ||             ||             ||*///
///*||PD12  ||LPUART0_RTS  ||UART2_RTS    ||             ||             ||             ||             ||             ||*///
///*||PD13  ||UART2_RXD    ||             ||             ||             ||             ||             ||             ||*///
///*||PD14  ||UART2_TXD    ||             ||             ||             ||             ||             ||             ||*///
///*||PD15  ||             ||UART2_CTS    ||             ||             ||             ||             ||             ||*///
///*||PE00  ||TIM1_CHA     ||             ||             ||             ||             ||             ||             ||*///
///*||PE01  ||TIM2_CHA     ||             ||             ||             ||             ||             ||             ||*///
///*||PE02  ||PCA_ECI      ||             ||             ||             ||             ||             ||             ||*///
///*||PE03  ||PCA_CH0      ||             ||             ||             ||             ||             ||             ||*///
///*||PE04  ||PCA_CH1      ||             ||             ||             ||             ||             ||             ||*///
///*||PE05  ||PCA_CH2      ||             ||             ||             ||             ||             ||             ||*///
///*||PE06  ||PCA_CH3      ||             ||             ||             ||             ||             ||             ||*///
///*||PE07  ||TIM3_ETR     ||LPTIM1_GATE  ||             ||             ||             ||             ||             ||*///
///*||PE08  ||TIM3_CH0B    ||LPTIM1_ETR   ||             ||             ||             ||             ||             ||*///
///*||PE09  ||TIM3_CH0A    ||LPTIM1_TOG   ||             ||             ||             ||             ||             ||*///
///*||PE10  ||TIM3_CH1B    ||LPTIM1_TOGN  ||             ||             ||             ||             ||             ||*///
///*||PE11  ||TIM3_CH1A    ||             ||             ||             ||             ||             ||             ||*///
///*||PE12  ||TIM3_CH2B    ||SPI0_CS      ||UART3_CTS    ||             ||             ||             ||             ||*///
///*||PE13  ||TIM3_CH2A    ||SPI0_SCK     ||UART3_RTS    ||             ||             ||             ||             ||*///
///*||PE14  ||TIM3_CH0B    ||SPI0_MISO    ||UART3_RXD    ||             ||             ||             ||             ||*///
///*||PE15  ||TIM3_BK      ||SPI0_MOSI    ||UART3_TXD    ||             ||             ||             ||             ||*///
///*||PF00  ||I2C0_SDA     ||             ||UART1_TXD    ||             ||             ||             ||             ||*///
///*||PF01  ||I2C0_SCL     ||TIM4_CHB     ||UART1_RXD    ||             ||             ||             ||             ||*///
///*||PF02  ||             ||             ||             ||             ||             ||             ||             ||*///
///*||PF03  ||             ||             ||             ||             ||             ||             ||             ||*///
///*||PF04  ||             ||             ||             ||             ||             ||             ||             ||*///
///*||PF05  ||             ||             ||             ||             ||             ||             ||             ||*///
///*||PF06  ||I2C1_SCL     ||LPUART1_CTS  ||UART0_CTS    ||             ||             ||             ||             ||*///
///*||PF07  ||I2C1_SDA     ||LPUART1_RTS  ||UART0_RTS    ||             ||             ||             ||             ||*///
///*||PF09  ||TIM0_CHA     ||             ||             ||             ||             ||             ||             ||*///
///*||PF10  ||TIM0_CHB     ||             ||             ||             ||             ||             ||             ||*///
///*||PF11  ||             ||             ||             ||             ||             ||             ||             ||*///
///*||======||=============||=============||=============||=============||=============||=============||=============||*///

/**
 *******************************************************************************
 ** \brief GPIO输入输出配置数据类型定义
 ******************************************************************************/
typedef enum en_gpio_dir
{
    GpioDirOut = 0u,                ///< GPIO 输出
    GpioDirIn  = 1u,                ///< GPIO 输入
}en_gpio_dir_t;

/**
 *******************************************************************************
 ** \brief GPIO端口上拉配置数据类型定义
 ******************************************************************************/
typedef enum en_gpio_pu
{
    GpioPuDisable = 0u,                ///< GPIO无上拉
    GpioPuEnable  = 1u,                ///< GPIO上拉
}en_gpio_pu_t;

/**
 *******************************************************************************
 ** \brief GPIO端口下拉配置数据类型定义
 ******************************************************************************/
typedef enum en_gpio_pd
{
    GpioPdDisable = 0u,                ///< GPIO无下拉
    GpioPdEnable  = 1u,                ///< GPIO下拉
}en_gpio_pd_t;
/**
 *******************************************************************************
 ** \brief GPIO端口输出驱动能力配置数据类型定义
 ******************************************************************************/
typedef enum en_gpio_drv
{
    GpioDrvH = 0u,                  ///< GPIO高驱动能力
    GpioDrvL = 1u,                  ///< GPIO低驱动能力
}en_gpio_drv_t;

/**
 *******************************************************************************
 ** \brief GPIO端口开漏输出控制数据类型定义
 ******************************************************************************/
typedef enum en_gpio_od
{
    GpioOdDisable = 0u,             ///< GPIO开漏输出关闭
    GpioOdEnable  = 1u,             ///< GPIO开漏输出使能
}en_gpio_od_t;

/**
 *******************************************************************************
 ** \brief GPIO端口输入/输出值寄存器总线控制模式选择
 ******************************************************************************/
typedef enum en_gpio_ctrl_mode
{
    GpioFastIO = 0u,             ///< FAST IO 总线控制模式
    GpioAHB  = 1u,               ///< AHB 总线控制模式
}en_gpio_ctrl_mode_t;

/**
 *******************************************************************************
 ** \brief GPIO中断触发方式类型定义
 ******************************************************************************/
typedef enum en_gpio_irqtype
{
    GpioIrqHigh     = 0u,           ///< GPIO高电平触发
    GpioIrqLow      = 1u,           ///< GPIO低电平触发
    GpioIrqRising   = 2u,           ///< GPIO上升沿触发
    GpioIrqFalling  = 3u,           ///< GPIO下降沿触发
}en_gpio_irqtype_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）端口中断模式类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_irqmode
{
    GpioSfIrqDpslpMode  = 1u,        ///< Deep Sleep模式
    GpioSfIrqActSlpMode = 0u,        ///< Active/Sleep模式
}en_gpio_sf_irqmode_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）HCLK输出门控类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_hclkout_g
{
    GpioSfHclkOutDisable = 0u,       ///< HCLK输出门控关闭
    GpioSfHclkOutEnable  = 1u,       ///< HCLK输出门控使能
}en_gpio_sf_hclkout_g_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）HCLK输出分频选择类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_hclkout_div
{
    GpioSfHclkOutDiv1 = 0u,         ///< HCLK
    GpioSfHclkOutDiv2 = 1u,         ///< HCLK/2
    GpioSfHclkOutDiv4 = 2u,         ///< HCLK/4
    GpioSfHclkOutDiv8 = 3u,         ///< HCLK/8
}en_gpio_sf_hclkout_div_t;
/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）PCLK输出门控类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_pclkout_g
{
    GpioSfPclkOutDisable = 0u,       ///< PCLK输出门控关闭
    GpioSfPclkOutEnable  = 1u,       ///< PCLK输出门控使能
}en_gpio_sf_pclkout_g_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）PCLK输出分频选择类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_pclkout_div
{
    GpioSfPclkOutDiv1 = 0u,         ///< PCLK
    GpioSfPclkOutDiv2 = 1u,         ///< PCLK/2
    GpioSfPclkOutDiv4 = 2u,         ///< PCLK/4
    GpioSfPclkOutDiv8 = 3u,         ///< PCLK/8
}en_gpio_sf_pclkout_div_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）IR输出极性选择类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_irpol
{
    GpioSfIrP = 0u,                  ///< IR正向输出
    GpioSfIrN = 1u,                  ///< IR反向输出
}en_gpio_sf_irpol_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）SSN通道类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_ssnspi
{
    GpioSpi0 = 0u,                   ///< SPI0 SSN
    GpioSpi1 = 1u,                   ///< SPI1 SSN
}en_gpio_sf_ssnspi_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）SSN与外部时钟输入信号源选择类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_ssn_extclk
{
    GpioSfSsnExtClkH    = 0u,        ///< 高电平
    GpioSfSsnExtClkPA03 = 1u,        ///< PA03
    GpioSfSsnExtClkPA04 = 2u,        ///< PA04
    GpioSfSsnExtClkPA06 = 3u,        ///< PA06
    GpioSfSsnExtClkPA08 = 4u,        ///< PA08
    GpioSfSsnExtClkPA09 = 5u,        ///< PA09
    GpioSfSsnExtClkPA12 = 6u,        ///< PA12
    GpioSfSsnExtClkPA15 = 7u,        ///< PA15
    GpioSfSsnExtClkPB01 = 8u,        ///< PB01
    GpioSfSsnExtClkPB02 = 9u,        ///< PB02
    GpioSfSsnExtClkPB05 = 10u,       ///< PB05
    GpioSfSsnExtClkPB06 = 11u,       ///< PB06
    GpioSfSsnExtClkPB09 = 12u,       ///< PB09
    GpioSfSsnExtClkPB10 = 13u,       ///< PB10
    GpioSfSsnExtClkPB12 = 14u,       ///< PB12
    GpioSfSsnExtClkPB14 = 15u,       ///< PB14
}en_gpio_sf_ssn_extclk_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）定时器互联功能选择类型定义
 ** \note  具体功能及含义请参考用户手册GPIO辅助寄存器描述
 ******************************************************************************/
typedef enum en_gpio_sf
{
    GpioSf0 = 0u,       ///< SF0:PX_SEL的配置功能
    GpioSf1 = 1u,       ///< SF1:辅助功能1
    GpioSf2 = 2u,       ///< SF2:辅助功能2
    GpioSf3 = 3u,       ///< SF3:辅助功能3
    GpioSf4 = 4u,       ///< SF4:辅助功能4
    GpioSf5 = 5u,       ///< SF5:辅助功能5
    GpioSf6 = 6u,       ///< SF6:辅助功能6
    GpioSf7 = 7u,       ///< SF7:辅助功能7
}en_gpio_sf_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）定时器门控类型选择数据类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_tim_g
{
    GpioSfTim0G   = 0u,                   ///<Tim0定时器GATE输入选择
    GpioSfTim1G   = 3u,                   ///<Tim1定时器GATE输入选择
    GpioSfTim2G   = 6u,                   ///<Tim2定时器GATE输入选择
    GpioSfTim3G   = 9u,                   ///<Tim3定时器GATE输入选择
    GpioSfLpTim0G = 12u,                  ///<LPTim0定时器GATE输入选择
    GpioSfLpTim1G = 38u,                  ///<LPTim1定时器GATE输入选择
}en_gpio_sf_tim_g_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）定时器ETR类型选择数据类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_tim_e
{
    GpioSfTim0E   = 0u,                   ///<Tim0定时器ETR输入选择
    GpioSfTim1E   = 3u,                   ///<Tim1定时器ETR输入选择
    GpioSfTim2E   = 6u,                   ///<Tim2定时器ETR输入选择
    GpioSfTim3E   = 9u,                   ///<Tim3定时器ETR输入选择
    GpioSfLpTim0E = 12u,                  ///<LPTim0定时器ETR输入选择
    GpioSfLpTim1E = 41u,                  ///<LPTim1定时器ETR输入选择
}en_gpio_sf_tim_e_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）定时器捕获输入类型选择数据类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_tim_c
{
    GpioSfTim0CA = 0u,                   ///<Tim0定时器CHA输入选择
    GpioSfTim1CA = 3u,                   ///<Tim1定时器CHA输入选择
    GpioSfTim2CA = 6u,                   ///<Tim2定时器CHA输入选择
    GpioSfTim3CA = 9u,                   ///<Tim3定时器CH0A输入选择
    GpioSfTim3CB = 12u,                  ///<Tim3定时器CH0B输入选择
}en_gpio_sf_tim_c_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）PCA捕获选择数据类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_pca
{
    GpioSfPcaCH0 = 0u,                   ///<PCA_CH0捕获口输入选择
    GpioSfPcaECI = 3u,                   ///<PCA ECI时钟输入选择
}en_gpio_sf_pca_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）PCNT脉冲输入选择数据类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_pcnt
{
    GpioSfPcntS0 = 0u,                   ///<PCNT_S0输入选择
    GpioSfPcntS1 = 3u,                   ///<PCNT_S1输入选择
}en_gpio_sf_pcnt_t;

/**
 *******************************************************************************
 ** \brief GPIO 端口配置结构体定义
 ******************************************************************************/
typedef struct
{
    boolean_t           bOutputVal;      ///< 默认端口输出电平
    en_gpio_dir_t       enDir;           ///< 端口方向配置
    en_gpio_drv_t       enDrv;           ///< 端口驱动能力配置
    en_gpio_pu_t        enPu;            ///< 端口上拉配置
    en_gpio_pd_t        enPd;            ///< 端口下拉配置
    en_gpio_od_t        enOD;            ///< 端口开漏输出配置
    en_gpio_ctrl_mode_t enCtrlMode;      ///< 端口输入/输出值寄存器总线控制模式配置
}stc_gpio_cfg_t;

/*******************************************************************************
 * Global definitions——(GPIO 复用功能宏定义)
 ******************************************************************************/
///< GPIO 复用功能宏定义
///< GpioAf1
#define PA00_UART1_CTS    (GpioPortA<<16u|GpioPin0 <<8u|GpioAf1)
#define PA01_UART1_RTS    (GpioPortA<<16u|GpioPin1 <<8u|GpioAf1)
#define PA02_UART1_TXD    (GpioPortA<<16u|GpioPin2 <<8u|GpioAf1)
#define PA03_UART1_RXD    (GpioPortA<<16u|GpioPin3 <<8u|GpioAf1)
#define PA04_SPI0_CS      (GpioPortA<<16u|GpioPin4 <<8u|GpioAf1)
#define PA05_SPI0_SCK     (GpioPortA<<16u|GpioPin5 <<8u|GpioAf1)
#define PA06_SPI0_MISO    (GpioPortA<<16u|GpioPin6 <<8u|GpioAf1)
#define PA07_SPI0_MOSI    (GpioPortA<<16u|GpioPin7 <<8u|GpioAf1)
#define PA08_UART0_TXD    (GpioPortA<<16u|GpioPin8 <<8u|GpioAf1)
#define PA09_UART0_TXD    (GpioPortA<<16u|GpioPin9 <<8u|GpioAf1)
#define PA10_UART0_RXD    (GpioPortA<<16u|GpioPin10<<8u|GpioAf1)
#define PA11_UART0_CTS    (GpioPortA<<16u|GpioPin11<<8u|GpioAf1)
#define PA12_UART0_RTS    (GpioPortA<<16u|GpioPin12<<8u|GpioAf1)
#define PA13_IR_OUT       (GpioPortA<<16u|GpioPin13<<8u|GpioAf1)
#define PA14_UART1_TXD    (GpioPortA<<16u|GpioPin14<<8u|GpioAf1)
#define PA15_SPI0_CS      (GpioPortA<<16u|GpioPin15<<8u|GpioAf1)
#define PB00_PCA_CH2      (GpioPortB<<16u|GpioPin0 <<8u|GpioAf1)
#define PB01_PCA_CH3      (GpioPortB<<16u|GpioPin1 <<8u|GpioAf1)
#define PB02_LPTIM_TOG    (GpioPortB<<16u|GpioPin2 <<8u|GpioAf1)
#define PB03_SPI0_SCK     (GpioPortB<<16u|GpioPin3 <<8u|GpioAf1)
#define PB04_SPI0_MISO    (GpioPortB<<16u|GpioPin4 <<8u|GpioAf1)
#define PB05_SPI0_MOSI    (GpioPortB<<16u|GpioPin5 <<8u|GpioAf1)
#define PB06_I2C0_SCL     (GpioPortB<<16u|GpioPin6 <<8u|GpioAf1)
#define PB07_I2C0_SDA     (GpioPortB<<16u|GpioPin7 <<8u|GpioAf1)
#define PB08_I2C0_SCL     (GpioPortB<<16u|GpioPin8 <<8u|GpioAf1)
#define PB09_I2C0_SDA     (GpioPortB<<16u|GpioPin9 <<8u|GpioAf1)
#define PB10_I2C1_SCL     (GpioPortB<<16u|GpioPin10<<8u|GpioAf1)
#define PB11_I2C1_SDA     (GpioPortB<<16u|GpioPin11<<8u|GpioAf1)
#define PB12_SPI1_CS      (GpioPortB<<16u|GpioPin12<<8u|GpioAf1)
#define PB13_SPI1_SCK     (GpioPortB<<16u|GpioPin13<<8u|GpioAf1)
#define PB14_SPI1_MISO    (GpioPortB<<16u|GpioPin14<<8u|GpioAf1)
#define PB15_SPI1_MOSI    (GpioPortB<<16u|GpioPin15<<8u|GpioAf1)
#define PC00_LPTIM_GATE   (GpioPortC<<16u|GpioPin0 <<8u|GpioAf1)
#define PC01_LPTIM_TOG    (GpioPortC<<16u|GpioPin1 <<8u|GpioAf1)
#define PC02_SPI1_MISO    (GpioPortC<<16u|GpioPin2 <<8u|GpioAf1)
#define PC03_SPI1_MOSI    (GpioPortC<<16u|GpioPin3 <<8u|GpioAf1)
#define PC04_LPUART0_TXD  (GpioPortC<<16u|GpioPin4 <<8u|GpioAf1)
#define PC05_LPUART0_RXD  (GpioPortC<<16u|GpioPin5 <<8u|GpioAf1)
#define PC06_PCA_CH0      (GpioPortC<<16u|GpioPin6 <<8u|GpioAf1)
#define PC07_PCA_CH1      (GpioPortC<<16u|GpioPin7 <<8u|GpioAf1)
#define PC08_PCA_CH2      (GpioPortC<<16u|GpioPin8 <<8u|GpioAf1)
#define PC09_PCA_CH3      (GpioPortC<<16u|GpioPin9 <<8u|GpioAf1)
#define PC10_LPUART1_TXD  (GpioPortC<<16u|GpioPin10<<8u|GpioAf1)
#define PC11_LPUART1_RXD  (GpioPortC<<16u|GpioPin11<<8u|GpioAf1)
#define PC12_LPUART0_TXD  (GpioPortC<<16u|GpioPin12<<8u|GpioAf1)
#define PC13_1x           (GpioPortC<<16u|GpioPin13<<8u|GpioAf1)
#define PC14_1x           (GpioPortC<<16u|GpioPin14<<8u|GpioAf1)
#define PC15_1x           (GpioPortC<<16u|GpioPin15<<8u|GpioAf1)
#define PD00_1x           (GpioPortD<<16u|GpioPin0 <<8u|GpioAf1)
#define PD01_1x           (GpioPortD<<16u|GpioPin1 <<8u|GpioAf1)
#define PD02_PCA_ECI      (GpioPortD<<16u|GpioPin2 <<8u|GpioAf1)
#define PD03_UART1_CTS    (GpioPortD<<16u|GpioPin3 <<8u|GpioAf1)
#define PD04_UART1_RTS    (GpioPortD<<16u|GpioPin4 <<8u|GpioAf1)
#define PD05_UART1_TXD    (GpioPortD<<16u|GpioPin5 <<8u|GpioAf1)
#define PD06_UART1_RXD    (GpioPortD<<16u|GpioPin6 <<8u|GpioAf1)
#define PD07_UART1_TXD    (GpioPortD<<16u|GpioPin7 <<8u|GpioAf1)
#define PD08_LPUART0_TXD  (GpioPortD<<16u|GpioPin8 <<8u|GpioAf1)
#define PD09_LPUART0_RXD  (GpioPortD<<16u|GpioPin9 <<8u|GpioAf1)
#define PD10_LPUART0_TXD  (GpioPortD<<16u|GpioPin10<<8u|GpioAf1)
#define PD11_LPUART0_CTS  (GpioPortD<<16u|GpioPin11<<8u|GpioAf1)
#define PD12_LPUART0_RTS  (GpioPortD<<16u|GpioPin12<<8u|GpioAf1)
#define PD13_UART2_RXD    (GpioPortD<<16u|GpioPin13<<8u|GpioAf1)
#define PD14_UART2_TXD    (GpioPortD<<16u|GpioPin14<<8u|GpioAf1)
#define PD15_1x           (GpioPortD<<16u|GpioPin15<<8u|GpioAf1)
#define PE00_TIM1_CHA     (GpioPortE<<16u|GpioPin0 <<8u|GpioAf1)
#define PE01_TIM2_CHA     (GpioPortE<<16u|GpioPin1 <<8u|GpioAf1)
#define PE02_PCA_ECI      (GpioPortE<<16u|GpioPin2 <<8u|GpioAf1)
#define PE03_PCA_CH0      (GpioPortE<<16u|GpioPin3 <<8u|GpioAf1)
#define PE04_PCA_CH1      (GpioPortE<<16u|GpioPin4 <<8u|GpioAf1)
#define PE05_PCA_CH2      (GpioPortE<<16u|GpioPin5 <<8u|GpioAf1)
#define PE06_PCA_CH3      (GpioPortE<<16u|GpioPin6 <<8u|GpioAf1)
#define PE07_TIM3_ETR     (GpioPortE<<16u|GpioPin7 <<8u|GpioAf1)
#define PE08_TIM3_CH0B    (GpioPortE<<16u|GpioPin8 <<8u|GpioAf1)
#define PE09_TIM3_CH0A    (GpioPortE<<16u|GpioPin9 <<8u|GpioAf1)
#define PE10_TIM3_CH1B    (GpioPortE<<16u|GpioPin10<<8u|GpioAf1)
#define PE11_TIM3_CH1A    (GpioPortE<<16u|GpioPin11<<8u|GpioAf1)
#define PE12_TIM3_CH2B    (GpioPortE<<16u|GpioPin12<<8u|GpioAf1)
#define PE13_TIM3_CH2A    (GpioPortE<<16u|GpioPin13<<8u|GpioAf1)
#define PE14_TIM3_CH0B    (GpioPortE<<16u|GpioPin14<<8u|GpioAf1)
#define PE15_TIM3_BK      (GpioPortE<<16u|GpioPin15<<8u|GpioAf1)
#define PF00_I2C0_SDA     (GpioPortF<<16u|GpioPin0 <<8u|GpioAf1)
#define PF01_I2C0_SCL     (GpioPortF<<16u|GpioPin1 <<8u|GpioAf1)
#define PF02_1x           (GpioPortF<<16u|GpioPin2 <<8u|GpioAf1)
#define PF03_1x           (GpioPortF<<16u|GpioPin3 <<8u|GpioAf1)
#define PF04_1x           (GpioPortF<<16u|GpioPin4 <<8u|GpioAf1)
#define PF05_1x           (GpioPortF<<16u|GpioPin5 <<8u|GpioAf1)
#define PF06_I2C1_SCL     (GpioPortF<<16u|GpioPin6 <<8u|GpioAf1)
#define PF07_I2C1_SDA     (GpioPortF<<16u|GpioPin7 <<8u|GpioAf1)
#define PF09_TIM0_CHA     (GpioPortF<<16u|GpioPin9 <<8u|GpioAf1)
#define PF10_TIM0_CHB     (GpioPortF<<16u|GpioPin10<<8u|GpioAf1)
#define PF11_1x           (GpioPortF<<16u|GpioPin11<<8u|GpioAf1)


 ///< GpioAf2
#define PA00_LPUART1_TXD  (GpioPortA<<16u|GpioPin0 <<8u|GpioAf2)
#define PA01_LPUART1_RXD  (GpioPortA<<16u|GpioPin1 <<8u|GpioAf2)
#define PA02_TIM0_CHA     (GpioPortA<<16u|GpioPin2 <<8u|GpioAf2)
#define PA03_TIM0_GATE    (GpioPortA<<16u|GpioPin3 <<8u|GpioAf2)
#define PA04_UART1_TXD    (GpioPortA<<16u|GpioPin4 <<8u|GpioAf2)
#define PA05_TIM0_ETR     (GpioPortA<<16u|GpioPin5 <<8u|GpioAf2)
#define PA06_PCA_CH0      (GpioPortA<<16u|GpioPin6 <<8u|GpioAf2)
#define PA07_PCA_CH1      (GpioPortA<<16u|GpioPin7 <<8u|GpioAf2)
#define PA08_TIM3_CH0A    (GpioPortA<<16u|GpioPin8 <<8u|GpioAf2)
#define PA09_TIM3_CH1A    (GpioPortA<<16u|GpioPin9 <<8u|GpioAf2)
#define PA10_TIM3_CH2A    (GpioPortA<<16u|GpioPin10<<8u|GpioAf2)
#define PA11_TIM3_GATE    (GpioPortA<<16u|GpioPin11<<8u|GpioAf2)
#define PA12_TIM3_ETR     (GpioPortA<<16u|GpioPin12<<8u|GpioAf2)
#define PA13_UART0_RXD    (GpioPortA<<16u|GpioPin13<<8u|GpioAf2)
#define PA14_UART0_TXD    (GpioPortA<<16u|GpioPin14<<8u|GpioAf2)
#define PA15_UART1_RXD    (GpioPortA<<16u|GpioPin15<<8u|GpioAf2)
#define PB00_TIM3_CH1B    (GpioPortB<<16u|GpioPin0 <<8u|GpioAf2)
#define PB01_PCLK_OUT     (GpioPortB<<16u|GpioPin1 <<8u|GpioAf2)
#define PB02_PCA_ECI      (GpioPortB<<16u|GpioPin2 <<8u|GpioAf2)
#define PB03_TIM0_CHB     (GpioPortB<<16u|GpioPin3 <<8u|GpioAf2)
#define PB04_PCA_CH0      (GpioPortB<<16u|GpioPin4 <<8u|GpioAf2)
#define PB05_2x           (GpioPortB<<16u|GpioPin5 <<8u|GpioAf2)
#define PB06_UART0_TXD    (GpioPortB<<16u|GpioPin6 <<8u|GpioAf2)
#define PB07_UART0_RXD    (GpioPortB<<16u|GpioPin7 <<8u|GpioAf2)
#define PB08_TIM1_CHA     (GpioPortB<<16u|GpioPin8 <<8u|GpioAf2)
#define PB09_IR_OUT       (GpioPortB<<16u|GpioPin9 <<8u|GpioAf2)
#define PB10_SPI1_SCK     (GpioPortB<<16u|GpioPin10<<8u|GpioAf2)
#define PB11_TIM1_CHB     (GpioPortB<<16u|GpioPin11<<8u|GpioAf2)
#define PB12_TIM3_BK      (GpioPortB<<16u|GpioPin12<<8u|GpioAf2)
#define PB13_I2C1_SCL     (GpioPortB<<16u|GpioPin13<<8u|GpioAf2)
#define PB14_I2C1_SDA     (GpioPortB<<16u|GpioPin14<<8u|GpioAf2)
#define PB15_TIM3_CH2B    (GpioPortB<<16u|GpioPin15<<8u|GpioAf2)
#define PC00_PCNT_S0      (GpioPortC<<16u|GpioPin0 <<8u|GpioAf2)
#define PC01_TIM5_CHB     (GpioPortC<<16u|GpioPin1 <<8u|GpioAf2)
#define PC02_LPTIM_TOGN   (GpioPortC<<16u|GpioPin2 <<8u|GpioAf2)
#define PC03_LPTIM_ETR    (GpioPortC<<16u|GpioPin3 <<8u|GpioAf2)
#define PC04_TIM2_ETR     (GpioPortC<<16u|GpioPin4 <<8u|GpioAf2)
#define PC05_TIM6_CHB     (GpioPortC<<16u|GpioPin5 <<8u|GpioAf2)
#define PC06_TIM4_CHA     (GpioPortC<<16u|GpioPin6 <<8u|GpioAf2)
#define PC07_TIM5_CHA     (GpioPortC<<16u|GpioPin7 <<8u|GpioAf2)
#define PC08_TIM6_CHA     (GpioPortC<<16u|GpioPin8 <<8u|GpioAf2)
#define PC09_TIM4_CHB     (GpioPortC<<16u|GpioPin9 <<8u|GpioAf2)
#define PC10_LPUART0_TXD  (GpioPortC<<16u|GpioPin10<<8u|GpioAf2)
#define PC11_LPUART0_RXD  (GpioPortC<<16u|GpioPin11<<8u|GpioAf2)
#define PC12_LPUART1_TXD  (GpioPortC<<16u|GpioPin12<<8u|GpioAf2)
#define PC13_RTC_1HZ      (GpioPortC<<16u|GpioPin13<<8u|GpioAf2)
#define PC14_2x           (GpioPortC<<16u|GpioPin14<<8u|GpioAf2)
#define PC15_2x           (GpioPortC<<16u|GpioPin15<<8u|GpioAf2)
#define PD00_SPI1_CS      (GpioPortD<<16u|GpioPin0 <<8u|GpioAf2)
#define PD01_SPI1_SCK     (GpioPortD<<16u|GpioPin1 <<8u|GpioAf2)
#define PD02_LPUART0_RTS  (GpioPortD<<16u|GpioPin2 <<8u|GpioAf2)
#define PD03_SPI1_MISO    (GpioPortD<<16u|GpioPin3 <<8u|GpioAf2)
#define PD04_SPI1_MOSI    (GpioPortD<<16u|GpioPin4 <<8u|GpioAf2)
#define PD05_LPTIM1_GATE  (GpioPortD<<16u|GpioPin5 <<8u|GpioAf2)
#define PD06_LPTIM1_ETR   (GpioPortD<<16u|GpioPin6 <<8u|GpioAf2)
#define PD07_2x           (GpioPortD<<16u|GpioPin7 <<8u|GpioAf2)
#define PD08_2x           (GpioPortD<<16u|GpioPin8 <<8u|GpioAf2)
#define PD09_2x           (GpioPortD<<16u|GpioPin9 <<8u|GpioAf2)
#define PD10_2x           (GpioPortD<<16u|GpioPin10<<8u|GpioAf2)
#define PD11_2x           (GpioPortD<<16u|GpioPin11<<8u|GpioAf2)
#define PD12_UART2_RTS    (GpioPortD<<16u|GpioPin12<<8u|GpioAf2)
#define PD13_2x           (GpioPortD<<16u|GpioPin13<<8u|GpioAf2)
#define PD14_2x           (GpioPortD<<16u|GpioPin14<<8u|GpioAf2)
#define PD15_UART2_CTS    (GpioPortD<<16u|GpioPin15<<8u|GpioAf2)
#define PE00_2x           (GpioPortE<<16u|GpioPin0 <<8u|GpioAf2)
#define PE01_2x           (GpioPortE<<16u|GpioPin1 <<8u|GpioAf2)
#define PE02_2x           (GpioPortE<<16u|GpioPin2 <<8u|GpioAf2)
#define PE03_2x           (GpioPortE<<16u|GpioPin3 <<8u|GpioAf2)
#define PE04_2x           (GpioPortE<<16u|GpioPin4 <<8u|GpioAf2)
#define PE05_2x           (GpioPortE<<16u|GpioPin5 <<8u|GpioAf2)
#define PE06_2x           (GpioPortE<<16u|GpioPin6 <<8u|GpioAf2)
#define PE07_LPTIM1_GATE  (GpioPortE<<16u|GpioPin7 <<8u|GpioAf2)
#define PE08_LPTIM1_ETR   (GpioPortE<<16u|GpioPin8 <<8u|GpioAf2)
#define PE09_LPTIM1_TOG   (GpioPortE<<16u|GpioPin9 <<8u|GpioAf2)
#define PE10_LPTIM1_TOGN  (GpioPortE<<16u|GpioPin10<<8u|GpioAf2)
#define PE11_2x           (GpioPortE<<16u|GpioPin11<<8u|GpioAf2)
#define PE12_SPI0_CS      (GpioPortE<<16u|GpioPin12<<8u|GpioAf2)
#define PE13_SPI0_SCK     (GpioPortE<<16u|GpioPin13<<8u|GpioAf2)
#define PE14_SPI0_MISO    (GpioPortE<<16u|GpioPin14<<8u|GpioAf2)
#define PE15_SPI0_MOSI    (GpioPortE<<16u|GpioPin15<<8u|GpioAf2)
#define PF00_2x           (GpioPortF<<16u|GpioPin0 <<8u|GpioAf2)
#define PF01_TIM4_CHB     (GpioPortF<<16u|GpioPin1 <<8u|GpioAf2)
#define PF02_2x           (GpioPortF<<16u|GpioPin2 <<8u|GpioAf2)
#define PF03_2x           (GpioPortF<<16u|GpioPin3 <<8u|GpioAf2)
#define PF04_2x           (GpioPortF<<16u|GpioPin4 <<8u|GpioAf2)
#define PF05_2x           (GpioPortF<<16u|GpioPin5 <<8u|GpioAf2)
#define PF06_LPUART1_CTS  (GpioPortF<<16u|GpioPin6 <<8u|GpioAf2)
#define PF07_LPUART1_RTS  (GpioPortF<<16u|GpioPin7 <<8u|GpioAf2)
#define PF09_2x           (GpioPortF<<16u|GpioPin9 <<8u|GpioAf2)
#define PF10_2x           (GpioPortF<<16u|GpioPin10<<8u|GpioAf2)
#define PF11_2x           (GpioPortF<<16u|GpioPin11<<8u|GpioAf2)

///< GpioAf3
#define PA00_TIM0_ETR     (GpioPortA<<16u|GpioPin0 <<8u|GpioAf3)
#define PA01_TIM0_CHB     (GpioPortA<<16u|GpioPin1 <<8u|GpioAf3)
#define PA02_VC1_OUT      (GpioPortA<<16u|GpioPin2 <<8u|GpioAf3)
#define PA03_TIM1_CHB     (GpioPortA<<16u|GpioPin3 <<8u|GpioAf3)
#define PA04_PCA_CH4      (GpioPortA<<16u|GpioPin4 <<8u|GpioAf3)
#define PA05_PCA_ECI      (GpioPortA<<16u|GpioPin5 <<8u|GpioAf3)
#define PA06_TIM3_BK      (GpioPortA<<16u|GpioPin6 <<8u|GpioAf3)
#define PA07_HCLK_OUT     (GpioPortA<<16u|GpioPin7 <<8u|GpioAf3)
#define PA08_3x           (GpioPortA<<16u|GpioPin8 <<8u|GpioAf3)
#define PA09_TIM0_BK      (GpioPortA<<16u|GpioPin9 <<8u|GpioAf3)
#define PA10_TIM2_BK      (GpioPortA<<16u|GpioPin10<<8u|GpioAf3)
#define PA11_I2C1_SCL     (GpioPortA<<16u|GpioPin11<<8u|GpioAf3)
#define PA12_I2C1_SDA     (GpioPortA<<16u|GpioPin12<<8u|GpioAf3)
#define PA13_LVD_OUT      (GpioPortA<<16u|GpioPin13<<8u|GpioAf3)
#define PA14_TIM3_CH2A    (GpioPortA<<16u|GpioPin14<<8u|GpioAf3)
#define PA15_LPUART1_RTS  (GpioPortA<<16u|GpioPin15<<8u|GpioAf3)
#define PB00_LPUART0_TXD  (GpioPortB<<16u|GpioPin0 <<8u|GpioAf3)
#define PB01_TIM3_CH2B    (GpioPortB<<16u|GpioPin1 <<8u|GpioAf3)
#define PB02_LPUART1_TXD  (GpioPortB<<16u|GpioPin2 <<8u|GpioAf3)
#define PB03_TIM1_GATE    (GpioPortB<<16u|GpioPin3 <<8u|GpioAf3)
#define PB04_TIM2_BK      (GpioPortB<<16u|GpioPin4 <<8u|GpioAf3)
#define PB05_TIM1_BK      (GpioPortB<<16u|GpioPin5 <<8u|GpioAf3)
#define PB06_TIM1_CHB     (GpioPortB<<16u|GpioPin6 <<8u|GpioAf3)
#define PB07_TIM2_CHB     (GpioPortB<<16u|GpioPin7 <<8u|GpioAf3)
#define PB08_3x           (GpioPortB<<16u|GpioPin8 <<8u|GpioAf3)
#define PB09_SPI1_CS      (GpioPortB<<16u|GpioPin9 <<8u|GpioAf3)
#define PB10_TIM1_CHA     (GpioPortB<<16u|GpioPin10<<8u|GpioAf3)
#define PB11_LPUART0_RXD  (GpioPortB<<16u|GpioPin11<<8u|GpioAf3)
#define PB12_LPUART0_TXD  (GpioPortB<<16u|GpioPin12<<8u|GpioAf3)
#define PB13_TIM3_CH0B    (GpioPortB<<16u|GpioPin13<<8u|GpioAf3)
#define PB14_TIM3_CH1B    (GpioPortB<<16u|GpioPin14<<8u|GpioAf3)
#define PB15_TIM0_CHB     (GpioPortB<<16u|GpioPin15<<8u|GpioAf3)
#define PC00_UART1_CTS    (GpioPortC<<16u|GpioPin0 <<8u|GpioAf3)
#define PC01_UART1_RTS    (GpioPortC<<16u|GpioPin1 <<8u|GpioAf3)
#define PC02_PCNT_S1      (GpioPortC<<16u|GpioPin2 <<8u|GpioAf3)
#define PC03_LPTIM_TOGN   (GpioPortC<<16u|GpioPin3 <<8u|GpioAf3)
#define PC04_IR_OUT       (GpioPortC<<16u|GpioPin4 <<8u|GpioAf3)
#define PC05_PCA_CH4      (GpioPortC<<16u|GpioPin5 <<8u|GpioAf3)
#define PC06_TIM2_CHA     (GpioPortC<<16u|GpioPin6 <<8u|GpioAf3)
#define PC07_TIM2_CHB     (GpioPortC<<16u|GpioPin7 <<8u|GpioAf3)
#define PC08_TIM2_ETR     (GpioPortC<<16u|GpioPin8 <<8u|GpioAf3)
#define PC09_TIM1_ETR     (GpioPortC<<16u|GpioPin9 <<8u|GpioAf3)
#define PC10_PCA_CH2      (GpioPortC<<16u|GpioPin10<<8u|GpioAf3)
#define PC11_PCA_CH3      (GpioPortC<<16u|GpioPin11<<8u|GpioAf3)
#define PC12_PCA_CH4      (GpioPortC<<16u|GpioPin12<<8u|GpioAf3)
#define PC13_TIM3_CH1B    (GpioPortC<<16u|GpioPin13<<8u|GpioAf3)
#define PC14_3x           (GpioPortC<<16u|GpioPin14<<8u|GpioAf3)
#define PC15_3x           (GpioPortC<<16u|GpioPin15<<8u|GpioAf3)
#define PD00_3x           (GpioPortD<<16u|GpioPin0 <<8u|GpioAf3)
#define PD01_3x           (GpioPortD<<16u|GpioPin1 <<8u|GpioAf3)
#define PD02_TIM1_ETR     (GpioPortD<<16u|GpioPin2 <<8u|GpioAf3)
#define PD03_LPTIM1_TOG   (GpioPortD<<16u|GpioPin3 <<8u|GpioAf3)
#define PD04_LPTIM1_TOGN  (GpioPortD<<16u|GpioPin4 <<8u|GpioAf3)
#define PD05_3x           (GpioPortD<<16u|GpioPin5 <<8u|GpioAf3)
#define PD06_3x           (GpioPortD<<16u|GpioPin6 <<8u|GpioAf3)
#define PD07_3x           (GpioPortD<<16u|GpioPin7 <<8u|GpioAf3)
#define PD08_3x           (GpioPortD<<16u|GpioPin8 <<8u|GpioAf3)
#define PD09_3x           (GpioPortD<<16u|GpioPin9 <<8u|GpioAf3)
#define PD10_3x           (GpioPortD<<16u|GpioPin10<<8u|GpioAf3)
#define PD11_3x           (GpioPortD<<16u|GpioPin11<<8u|GpioAf3)
#define PD12_3x           (GpioPortD<<16u|GpioPin12<<8u|GpioAf3)
#define PD13_3x           (GpioPortD<<16u|GpioPin13<<8u|GpioAf3)
#define PD14_3x           (GpioPortD<<16u|GpioPin14<<8u|GpioAf3)
#define PD15_3x           (GpioPortD<<16u|GpioPin15<<8u|GpioAf3)
#define PE00_3x           (GpioPortE<<16u|GpioPin0 <<8u|GpioAf3)
#define PE01_3x           (GpioPortE<<16u|GpioPin1 <<8u|GpioAf3)
#define PE02_3x           (GpioPortE<<16u|GpioPin2 <<8u|GpioAf3)
#define PE03_3x           (GpioPortE<<16u|GpioPin3 <<8u|GpioAf3)
#define PE04_3x           (GpioPortE<<16u|GpioPin4 <<8u|GpioAf3)
#define PE05_3x           (GpioPortE<<16u|GpioPin5 <<8u|GpioAf3)
#define PE06_3x           (GpioPortE<<16u|GpioPin6 <<8u|GpioAf3)
#define PE07_3x           (GpioPortE<<16u|GpioPin7 <<8u|GpioAf3)
#define PE08_3x           (GpioPortE<<16u|GpioPin8 <<8u|GpioAf3)
#define PE09_3x           (GpioPortE<<16u|GpioPin9 <<8u|GpioAf3)
#define PE10_3x           (GpioPortE<<16u|GpioPin10<<8u|GpioAf3)
#define PE11_3x           (GpioPortE<<16u|GpioPin11<<8u|GpioAf3)
#define PE12_UART3_CTS    (GpioPortE<<16u|GpioPin12<<8u|GpioAf3)
#define PE13_UART3_RTS    (GpioPortE<<16u|GpioPin13<<8u|GpioAf3)
#define PE14_UART3_RXD    (GpioPortE<<16u|GpioPin14<<8u|GpioAf3)
#define PE15_UART3_TXD    (GpioPortE<<16u|GpioPin15<<8u|GpioAf3)
#define PF00_UART1_TXD    (GpioPortF<<16u|GpioPin0 <<8u|GpioAf3)
#define PF01_UART1_RXD    (GpioPortF<<16u|GpioPin1 <<8u|GpioAf3)
#define PF02_3x           (GpioPortF<<16u|GpioPin2 <<8u|GpioAf3)
#define PF03_3x           (GpioPortF<<16u|GpioPin3 <<8u|GpioAf3)
#define PF04_3x           (GpioPortF<<16u|GpioPin4 <<8u|GpioAf3)
#define PF05_3x           (GpioPortF<<16u|GpioPin5 <<8u|GpioAf3)
#define PF06_UART0_CTS    (GpioPortF<<16u|GpioPin6 <<8u|GpioAf3)
#define PF07_UART0_RTS    (GpioPortF<<16u|GpioPin7 <<8u|GpioAf3)
#define PF09_3x           (GpioPortF<<16u|GpioPin9 <<8u|GpioAf3)
#define PF10_3x           (GpioPortF<<16u|GpioPin10<<8u|GpioAf3)
#define PF11_3x           (GpioPortF<<16u|GpioPin11<<8u|GpioAf3)

///< GpioAf4
#define PA00_VC0_OUT      (GpioPortA<<16u|GpioPin0 <<8u|GpioAf4)
#define PA01_TIM1_ETR     (GpioPortA<<16u|GpioPin1 <<8u|GpioAf4)
#define PA02_TIM1_CHA     (GpioPortA<<16u|GpioPin2 <<8u|GpioAf4)
#define PA03_TIM2_CHB     (GpioPortA<<16u|GpioPin3 <<8u|GpioAf4)
#define PA04_TIM2_ETR     (GpioPortA<<16u|GpioPin4 <<8u|GpioAf4)
#define PA05_TIM0_CHA     (GpioPortA<<16u|GpioPin5 <<8u|GpioAf4)
#define PA06_TIM1_CHA     (GpioPortA<<16u|GpioPin6 <<8u|GpioAf4)
#define PA07_TIM3_CH0B    (GpioPortA<<16u|GpioPin7 <<8u|GpioAf4)
#define PA08_4x           (GpioPortA<<16u|GpioPin8 <<8u|GpioAf4)
#define PA09_I2C0_SCL     (GpioPortA<<16u|GpioPin9 <<8u|GpioAf4)
#define PA10_I2C0_SDA     (GpioPortA<<16u|GpioPin10<<8u|GpioAf4)
#define PA11_4x           (GpioPortA<<16u|GpioPin11<<8u|GpioAf4)
#define PA12_4x           (GpioPortA<<16u|GpioPin12<<8u|GpioAf4)
#define PA13_TIM3_ETR     (GpioPortA<<16u|GpioPin13<<8u|GpioAf4)
#define PA14_LVD_OUT      (GpioPortA<<16u|GpioPin14<<8u|GpioAf4)
#define PA15_TIM0_ETR     (GpioPortA<<16u|GpioPin15<<8u|GpioAf4)
#define PB00_TIM5_CHB     (GpioPortB<<16u|GpioPin0 <<8u|GpioAf4)
#define PB01_TIM6_CHB     (GpioPortB<<16u|GpioPin1 <<8u|GpioAf4)
#define PB02_TIM4_CHA     (GpioPortB<<16u|GpioPin2 <<8u|GpioAf4)
#define PB03_TIM3_CH0A    (GpioPortB<<16u|GpioPin3 <<8u|GpioAf4)
#define PB04_UART0_CTS    (GpioPortB<<16u|GpioPin4 <<8u|GpioAf4)
#define PB05_PCA_CH1      (GpioPortB<<16u|GpioPin5 <<8u|GpioAf4)
#define PB06_TIM0_CHA     (GpioPortB<<16u|GpioPin6 <<8u|GpioAf4)
#define PB07_LPUART1_CTS  (GpioPortB<<16u|GpioPin7 <<8u|GpioAf4)
#define PB08_TIM2_CHA     (GpioPortB<<16u|GpioPin8 <<8u|GpioAf4)
#define PB09_TIM2_CHA     (GpioPortB<<16u|GpioPin9 <<8u|GpioAf4)
#define PB10_LPUART0_TXD  (GpioPortB<<16u|GpioPin10<<8u|GpioAf4)
#define PB11_TIM2_GATE    (GpioPortB<<16u|GpioPin11<<8u|GpioAf4)
#define PB12_TIM0_BK      (GpioPortB<<16u|GpioPin12<<8u|GpioAf4)
#define PB13_LPUART0_CTS  (GpioPortB<<16u|GpioPin13<<8u|GpioAf4)
#define PB14_TIM0_CHA     (GpioPortB<<16u|GpioPin14<<8u|GpioAf4)
#define PB15_TIM0_GATE    (GpioPortB<<16u|GpioPin15<<8u|GpioAf4)
#define PC00_UART2_RTS    (GpioPortC<<16u|GpioPin0 <<8u|GpioAf4)
#define PC01_PCNT_S0FO    (GpioPortC<<16u|GpioPin1 <<8u|GpioAf4)
#define PC02_UART2_RXD    (GpioPortC<<16u|GpioPin2 <<8u|GpioAf4)
#define PC03_PCNT_S1FO    (GpioPortC<<16u|GpioPin3 <<8u|GpioAf4)
#define PC04_VC2_OUT      (GpioPortC<<16u|GpioPin4 <<8u|GpioAf4)
#define PC05_4x           (GpioPortC<<16u|GpioPin5 <<8u|GpioAf4)
#define PC06_LPTIM1_GATE  (GpioPortC<<16u|GpioPin6 <<8u|GpioAf4)
#define PC07_LPTIM1_ETR   (GpioPortC<<16u|GpioPin7 <<8u|GpioAf4)
#define PC08_LPTIM1_TOG   (GpioPortC<<16u|GpioPin8 <<8u|GpioAf4)
#define PC09_LPTIM1_TOGN  (GpioPortC<<16u|GpioPin9 <<8u|GpioAf4)
#define PC10_4x           (GpioPortC<<16u|GpioPin10<<8u|GpioAf4)
#define PC11_PCNT_S0FO    (GpioPortC<<16u|GpioPin11<<8u|GpioAf4)
#define PC12_PCNT_S1FO    (GpioPortC<<16u|GpioPin12<<8u|GpioAf4)
#define PC13_4x           (GpioPortC<<16u|GpioPin13<<8u|GpioAf4)
#define PC14_4x           (GpioPortC<<16u|GpioPin14<<8u|GpioAf4)
#define PC15_4x           (GpioPortC<<16u|GpioPin15<<8u|GpioAf4)
#define PD00_4x           (GpioPortD<<16u|GpioPin0 <<8u|GpioAf4)
#define PD01_4x           (GpioPortD<<16u|GpioPin1 <<8u|GpioAf4)
#define PD02_4x           (GpioPortD<<16u|GpioPin2 <<8u|GpioAf4)
#define PD03_4x           (GpioPortD<<16u|GpioPin3 <<8u|GpioAf4)
#define PD04_4x           (GpioPortD<<16u|GpioPin4 <<8u|GpioAf4)
#define PD05_4x           (GpioPortD<<16u|GpioPin5 <<8u|GpioAf4)
#define PD06_4x           (GpioPortD<<16u|GpioPin6 <<8u|GpioAf4)
#define PD07_4x           (GpioPortD<<16u|GpioPin7 <<8u|GpioAf4)
#define PD08_4x           (GpioPortD<<16u|GpioPin8 <<8u|GpioAf4)
#define PD09_4x           (GpioPortD<<16u|GpioPin9 <<8u|GpioAf4)
#define PD10_4x           (GpioPortD<<16u|GpioPin10<<8u|GpioAf4)
#define PD11_4x           (GpioPortD<<16u|GpioPin11<<8u|GpioAf4)
#define PD12_4x           (GpioPortD<<16u|GpioPin12<<8u|GpioAf4)
#define PD13_4x           (GpioPortD<<16u|GpioPin13<<8u|GpioAf4)
#define PD14_4x           (GpioPortD<<16u|GpioPin14<<8u|GpioAf4)
#define PD15_4x           (GpioPortD<<16u|GpioPin15<<8u|GpioAf4)
#define PE00_4x           (GpioPortE<<16u|GpioPin0 <<8u|GpioAf4)
#define PE01_4x           (GpioPortE<<16u|GpioPin1 <<8u|GpioAf4)
#define PE02_4x           (GpioPortE<<16u|GpioPin2 <<8u|GpioAf4)
#define PE03_4x           (GpioPortE<<16u|GpioPin3 <<8u|GpioAf4)
#define PE04_4x           (GpioPortE<<16u|GpioPin4 <<8u|GpioAf4)
#define PE05_4x           (GpioPortE<<16u|GpioPin5 <<8u|GpioAf4)
#define PE06_4x           (GpioPortE<<16u|GpioPin6 <<8u|GpioAf4)
#define PE07_4x           (GpioPortE<<16u|GpioPin7 <<8u|GpioAf4)
#define PE08_4x           (GpioPortE<<16u|GpioPin8 <<8u|GpioAf4)
#define PE09_4x           (GpioPortE<<16u|GpioPin9 <<8u|GpioAf4)
#define PE10_4x           (GpioPortE<<16u|GpioPin10<<8u|GpioAf4)
#define PE11_4x           (GpioPortE<<16u|GpioPin11<<8u|GpioAf4)
#define PE12_4x           (GpioPortE<<16u|GpioPin12<<8u|GpioAf4)
#define PE13_4x           (GpioPortE<<16u|GpioPin13<<8u|GpioAf4)
#define PE14_4x           (GpioPortE<<16u|GpioPin14<<8u|GpioAf4)
#define PE15_4x           (GpioPortE<<16u|GpioPin15<<8u|GpioAf4)
#define PF00_4x           (GpioPortF<<16u|GpioPin0 <<8u|GpioAf4)
#define PF01_4x           (GpioPortF<<16u|GpioPin1 <<8u|GpioAf4)
#define PF02_4x           (GpioPortF<<16u|GpioPin2 <<8u|GpioAf4)
#define PF03_4x           (GpioPortF<<16u|GpioPin3 <<8u|GpioAf4)
#define PF04_4x           (GpioPortF<<16u|GpioPin4 <<8u|GpioAf4)
#define PF05_4x           (GpioPortF<<16u|GpioPin5 <<8u|GpioAf4)
#define PF06_4x           (GpioPortF<<16u|GpioPin6 <<8u|GpioAf4)
#define PF07_4x           (GpioPortF<<16u|GpioPin7 <<8u|GpioAf4)
#define PF09_4x           (GpioPortF<<16u|GpioPin9 <<8u|GpioAf4)
#define PF10_4x           (GpioPortF<<16u|GpioPin10<<8u|GpioAf4)
#define PF11_4x           (GpioPortF<<16u|GpioPin11<<8u|GpioAf4)

///< GpioAf5
#define PA00_TIM1_CHA     (GpioPortA<<16u|GpioPin0 <<8u|GpioAf5)
#define PA01_TIM1_CHB     (GpioPortA<<16u|GpioPin1 <<8u|GpioAf5)
#define PA02_TIM2_CHA     (GpioPortA<<16u|GpioPin2 <<8u|GpioAf5)
#define PA03_SPI1_CS      (GpioPortA<<16u|GpioPin3 <<8u|GpioAf5)
#define PA04_TIM5_CHA     (GpioPortA<<16u|GpioPin4 <<8u|GpioAf5)
#define PA05_TIM5_CHB     (GpioPortA<<16u|GpioPin5 <<8u|GpioAf5)
#define PA06_VC0_OUT      (GpioPortA<<16u|GpioPin6 <<8u|GpioAf5)
#define PA07_TIM2_CHA     (GpioPortA<<16u|GpioPin7 <<8u|GpioAf5)
#define PA08_TIM1_GATE    (GpioPortA<<16u|GpioPin8 <<8u|GpioAf5)
#define PA09_5x           (GpioPortA<<16u|GpioPin9 <<8u|GpioAf5)
#define PA10_TIM2_GATE    (GpioPortA<<16u|GpioPin10<<8u|GpioAf5)
#define PA11_VC0_OUT      (GpioPortA<<16u|GpioPin11<<8u|GpioAf5)
#define PA12_VC1_OUT      (GpioPortA<<16u|GpioPin12<<8u|GpioAf5)
#define PA13_RTC_1HZ      (GpioPortA<<16u|GpioPin13<<8u|GpioAf5)
#define PA14_RCH_OUT      (GpioPortA<<16u|GpioPin14<<8u|GpioAf5)
#define PA15_TIM0_CHA     (GpioPortA<<16u|GpioPin15<<8u|GpioAf5)
#define PB00_RCH_OUT      (GpioPortB<<16u|GpioPin0 <<8u|GpioAf5)
#define PB01_LPUART0_RTS  (GpioPortB<<16u|GpioPin1 <<8u|GpioAf5)
#define PB02_TIM1_BK      (GpioPortB<<16u|GpioPin2 <<8u|GpioAf5)
#define PB03_LPTIM_GATE   (GpioPortB<<16u|GpioPin3 <<8u|GpioAf5)
#define PB04_TIM2_GATE    (GpioPortB<<16u|GpioPin4 <<8u|GpioAf5)
#define PB05_LPTIM_GATE   (GpioPortB<<16u|GpioPin5 <<8u|GpioAf5)
#define PB06_LPTIM_ETR    (GpioPortB<<16u|GpioPin6 <<8u|GpioAf5)
#define PB07_TIM0_CHB     (GpioPortB<<16u|GpioPin7 <<8u|GpioAf5)
#define PB08_TIM0_GATE    (GpioPortB<<16u|GpioPin8 <<8u|GpioAf5)
#define PB09_5x           (GpioPortB<<16u|GpioPin9 <<8u|GpioAf5)
#define PB10_TIM3_CH1A    (GpioPortB<<16u|GpioPin10<<8u|GpioAf5)
#define PB11_TIM6_CHA     (GpioPortB<<16u|GpioPin11<<8u|GpioAf5)
#define PB12_5x           (GpioPortB<<16u|GpioPin12<<8u|GpioAf5)
#define PB13_TIM1_CHA     (GpioPortB<<16u|GpioPin13<<8u|GpioAf5)
#define PB14_RTC_1HZ      (GpioPortB<<16u|GpioPin14<<8u|GpioAf5)
#define PB15_5x           (GpioPortB<<16u|GpioPin15<<8u|GpioAf5)
#define PC00_5x           (GpioPortC<<16u|GpioPin0 <<8u|GpioAf5)
#define PC01_5x           (GpioPortC<<16u|GpioPin1 <<8u|GpioAf5)
#define PC02_5x           (GpioPortC<<16u|GpioPin2 <<8u|GpioAf5)
#define PC03_UART2_TXD    (GpioPortC<<16u|GpioPin3 <<8u|GpioAf5)
#define PC04_5x           (GpioPortC<<16u|GpioPin4 <<8u|GpioAf5)
#define PC05_5x           (GpioPortC<<16u|GpioPin5 <<8u|GpioAf5)
#define PC06_5x           (GpioPortC<<16u|GpioPin6 <<8u|GpioAf5)
#define PC07_5x           (GpioPortC<<16u|GpioPin7 <<8u|GpioAf5)
#define PC08_5x           (GpioPortC<<16u|GpioPin8 <<8u|GpioAf5)
#define PC09_5x           (GpioPortC<<16u|GpioPin9 <<8u|GpioAf5)
#define PC10_5x           (GpioPortC<<16u|GpioPin10<<8u|GpioAf5)
#define PC11_5x           (GpioPortC<<16u|GpioPin11<<8u|GpioAf5)
#define PC12_5x           (GpioPortC<<16u|GpioPin12<<8u|GpioAf5)
#define PC13_5x           (GpioPortC<<16u|GpioPin13<<8u|GpioAf5)
#define PC14_5x           (GpioPortC<<16u|GpioPin14<<8u|GpioAf5)
#define PC15_5x           (GpioPortC<<16u|GpioPin15<<8u|GpioAf5)
#define PD00_5x           (GpioPortD<<16u|GpioPin0 <<8u|GpioAf5)
#define PD01_5x           (GpioPortD<<16u|GpioPin1 <<8u|GpioAf5)
#define PD02_5x           (GpioPortD<<16u|GpioPin2 <<8u|GpioAf5)
#define PD03_5x           (GpioPortD<<16u|GpioPin3 <<8u|GpioAf5)
#define PD04_5x           (GpioPortD<<16u|GpioPin4 <<8u|GpioAf5)
#define PD05_5x           (GpioPortD<<16u|GpioPin5 <<8u|GpioAf5)
#define PD06_5x           (GpioPortD<<16u|GpioPin6 <<8u|GpioAf5)
#define PD07_5x           (GpioPortD<<16u|GpioPin7 <<8u|GpioAf5)
#define PD08_5x           (GpioPortD<<16u|GpioPin8 <<8u|GpioAf5)
#define PD09_5x           (GpioPortD<<16u|GpioPin9 <<8u|GpioAf5)
#define PD10_5x           (GpioPortD<<16u|GpioPin10<<8u|GpioAf5)
#define PD11_5x           (GpioPortD<<16u|GpioPin11<<8u|GpioAf5)
#define PD12_5x           (GpioPortD<<16u|GpioPin12<<8u|GpioAf5)
#define PD13_5x           (GpioPortD<<16u|GpioPin13<<8u|GpioAf5)
#define PD14_5x           (GpioPortD<<16u|GpioPin14<<8u|GpioAf5)
#define PD15_5x           (GpioPortD<<16u|GpioPin15<<8u|GpioAf5)
#define PE00_5x           (GpioPortE<<16u|GpioPin0 <<8u|GpioAf5)
#define PE01_5x           (GpioPortE<<16u|GpioPin1 <<8u|GpioAf5)
#define PE02_5x           (GpioPortE<<16u|GpioPin2 <<8u|GpioAf5)
#define PE03_5x           (GpioPortE<<16u|GpioPin3 <<8u|GpioAf5)
#define PE04_5x           (GpioPortE<<16u|GpioPin4 <<8u|GpioAf5)
#define PE05_5x           (GpioPortE<<16u|GpioPin5 <<8u|GpioAf5)
#define PE06_5x           (GpioPortE<<16u|GpioPin6 <<8u|GpioAf5)
#define PE07_5x           (GpioPortE<<16u|GpioPin7 <<8u|GpioAf5)
#define PE08_5x           (GpioPortE<<16u|GpioPin8 <<8u|GpioAf5)
#define PE09_5x           (GpioPortE<<16u|GpioPin9 <<8u|GpioAf5)
#define PE10_5x           (GpioPortE<<16u|GpioPin10<<8u|GpioAf5)
#define PE11_5x           (GpioPortE<<16u|GpioPin11<<8u|GpioAf5)
#define PE12_5x           (GpioPortE<<16u|GpioPin12<<8u|GpioAf5)
#define PE13_5x           (GpioPortE<<16u|GpioPin13<<8u|GpioAf5)
#define PE14_5x           (GpioPortE<<16u|GpioPin14<<8u|GpioAf5)
#define PE15_5x           (GpioPortE<<16u|GpioPin15<<8u|GpioAf5)
#define PF00_5x           (GpioPortF<<16u|GpioPin0 <<8u|GpioAf5)
#define PF01_5x           (GpioPortF<<16u|GpioPin1 <<8u|GpioAf5)
#define PF02_5x           (GpioPortF<<16u|GpioPin2 <<8u|GpioAf5)
#define PF03_5x           (GpioPortF<<16u|GpioPin3 <<8u|GpioAf5)
#define PF04_5x           (GpioPortF<<16u|GpioPin4 <<8u|GpioAf5)
#define PF05_5x           (GpioPortF<<16u|GpioPin5 <<8u|GpioAf5)
#define PF06_5x           (GpioPortF<<16u|GpioPin6 <<8u|GpioAf5)
#define PF07_5x           (GpioPortF<<16u|GpioPin7 <<8u|GpioAf5)
#define PF09_5x           (GpioPortF<<16u|GpioPin9 <<8u|GpioAf5)
#define PF10_5x           (GpioPortF<<16u|GpioPin10<<8u|GpioAf5)
#define PF11_5x           (GpioPortF<<16u|GpioPin11<<8u|GpioAf5)

///< GpioAf6
#define PA00_TIM3_ETR     (GpioPortA<<16u|GpioPin0 <<8u|GpioAf6)
#define PA01_HCLK_OUT     (GpioPortA<<16u|GpioPin1 <<8u|GpioAf6)
#define PA02_PCLK_OUT     (GpioPortA<<16u|GpioPin2 <<8u|GpioAf6)
#define PA03_TIM3_CH1A    (GpioPortA<<16u|GpioPin3 <<8u|GpioAf6)
#define PA04_LVD_OUT      (GpioPortA<<16u|GpioPin4 <<8u|GpioAf6)
#define PA05_XTL_OUT      (GpioPortA<<16u|GpioPin5 <<8u|GpioAf6)
#define PA06_TIM3_GATE    (GpioPortA<<16u|GpioPin6 <<8u|GpioAf6)
#define PA07_VC1_OUT      (GpioPortA<<16u|GpioPin7 <<8u|GpioAf6)
#define PA08_TIM4_CHA     (GpioPortA<<16u|GpioPin8 <<8u|GpioAf6)
#define PA09_HCLK_OUT     (GpioPortA<<16u|GpioPin9 <<8u|GpioAf6)
#define PA10_PCLK_OUT     (GpioPortA<<16u|GpioPin10<<8u|GpioAf6)
#define PA11_SPI0_MISO    (GpioPortA<<16u|GpioPin11<<8u|GpioAf6)
#define PA12_SPI0_MOSI    (GpioPortA<<16u|GpioPin12<<8u|GpioAf6)
#define PA13_PCNT_S1      (GpioPortA<<16u|GpioPin13<<8u|GpioAf6)
#define PA14_RCL_OUT      (GpioPortA<<16u|GpioPin14<<8u|GpioAf6)
#define PA15_TIM3_CH1A    (GpioPortA<<16u|GpioPin15<<8u|GpioAf6)
#define PB00_RCL_OUT      (GpioPortB<<16u|GpioPin0 <<8u|GpioAf6)
#define PB01_VC2_OUT      (GpioPortB<<16u|GpioPin1 <<8u|GpioAf6)
#define PB02_TIM0_BK      (GpioPortB<<16u|GpioPin2 <<8u|GpioAf6)
#define PB03_XTL_OUT      (GpioPortB<<16u|GpioPin3 <<8u|GpioAf6)
#define PB04_TIM3_CH0B    (GpioPortB<<16u|GpioPin4 <<8u|GpioAf6)
#define PB05_PCNT_S0      (GpioPortB<<16u|GpioPin5 <<8u|GpioAf6)
#define PB06_TIM3_CH0A    (GpioPortB<<16u|GpioPin6 <<8u|GpioAf6)
#define PB07_LPTIM_TOGN   (GpioPortB<<16u|GpioPin7 <<8u|GpioAf6)
#define PB08_TIM3_CH2A    (GpioPortB<<16u|GpioPin8 <<8u|GpioAf6)
#define PB09_TIM2_CHB     (GpioPortB<<16u|GpioPin9 <<8u|GpioAf6)
#define PB10_LPUART1_RTS  (GpioPortB<<16u|GpioPin10<<8u|GpioAf6)
#define PB11_LPUART1_CTS  (GpioPortB<<16u|GpioPin11<<8u|GpioAf6)
#define PB12_LPUART0_RTS  (GpioPortB<<16u|GpioPin12<<8u|GpioAf6)
#define PB13_TIM1_GATE    (GpioPortB<<16u|GpioPin13<<8u|GpioAf6)
#define PB14_LPUART0_RTS  (GpioPortB<<16u|GpioPin14<<8u|GpioAf6)
#define PB15_6x           (GpioPortB<<16u|GpioPin15<<8u|GpioAf6)
#define PC00_6x           (GpioPortC<<16u|GpioPin0 <<8u|GpioAf6)
#define PC01_UART2_CTS    (GpioPortC<<16u|GpioPin1 <<8u|GpioAf6)
#define PC02_6x           (GpioPortC<<16u|GpioPin2 <<8u|GpioAf6)
#define PC03_6x           (GpioPortC<<16u|GpioPin3 <<8u|GpioAf6)
#define PC04_6x           (GpioPortC<<16u|GpioPin4 <<8u|GpioAf6)
#define PC05_6x           (GpioPortC<<16u|GpioPin5 <<8u|GpioAf6)
#define PC06_UART3_RXD    (GpioPortC<<16u|GpioPin6 <<8u|GpioAf6)
#define PC07_UART3_TXD    (GpioPortC<<16u|GpioPin7 <<8u|GpioAf6)
#define PC08_UART3_CTS    (GpioPortC<<16u|GpioPin8 <<8u|GpioAf6)
#define PC09_UART3_RTS    (GpioPortC<<16u|GpioPin9 <<8u|GpioAf6)
#define PC10_6x           (GpioPortC<<16u|GpioPin10<<8u|GpioAf6)
#define PC11_6x           (GpioPortC<<16u|GpioPin11<<8u|GpioAf6)
#define PC12_6x           (GpioPortC<<16u|GpioPin12<<8u|GpioAf6)
#define PC13_6x           (GpioPortC<<16u|GpioPin13<<8u|GpioAf6)
#define PC14_6x           (GpioPortC<<16u|GpioPin14<<8u|GpioAf6)
#define PC15_6x           (GpioPortC<<16u|GpioPin15<<8u|GpioAf6)
#define PD00_6x           (GpioPortD<<16u|GpioPin0 <<8u|GpioAf6)
#define PD01_6x           (GpioPortD<<16u|GpioPin1 <<8u|GpioAf6)
#define PD02_6x           (GpioPortD<<16u|GpioPin2 <<8u|GpioAf6)
#define PD03_6x           (GpioPortD<<16u|GpioPin3 <<8u|GpioAf6)
#define PD04_6x           (GpioPortD<<16u|GpioPin4 <<8u|GpioAf6)
#define PD05_6x           (GpioPortD<<16u|GpioPin5 <<8u|GpioAf6)
#define PD06_6x           (GpioPortD<<16u|GpioPin6 <<8u|GpioAf6)
#define PD07_6x           (GpioPortD<<16u|GpioPin7 <<8u|GpioAf6)
#define PD08_6x           (GpioPortD<<16u|GpioPin8 <<8u|GpioAf6)
#define PD09_6x           (GpioPortD<<16u|GpioPin9 <<8u|GpioAf6)
#define PD10_6x           (GpioPortD<<16u|GpioPin10<<8u|GpioAf6)
#define PD11_6x           (GpioPortD<<16u|GpioPin11<<8u|GpioAf6)
#define PD12_6x           (GpioPortD<<16u|GpioPin12<<8u|GpioAf6)
#define PD13_6x           (GpioPortD<<16u|GpioPin13<<8u|GpioAf6)
#define PD14_6x           (GpioPortD<<16u|GpioPin14<<8u|GpioAf6)
#define PD15_6x           (GpioPortD<<16u|GpioPin15<<8u|GpioAf6)
#define PE00_6x           (GpioPortE<<16u|GpioPin0 <<8u|GpioAf6)
#define PE01_6x           (GpioPortE<<16u|GpioPin1 <<8u|GpioAf6)
#define PE02_6x           (GpioPortE<<16u|GpioPin2 <<8u|GpioAf6)
#define PE03_6x           (GpioPortE<<16u|GpioPin3 <<8u|GpioAf6)
#define PE04_6x           (GpioPortE<<16u|GpioPin4 <<8u|GpioAf6)
#define PE05_6x           (GpioPortE<<16u|GpioPin5 <<8u|GpioAf6)
#define PE06_6x           (GpioPortE<<16u|GpioPin6 <<8u|GpioAf6)
#define PE07_6x           (GpioPortE<<16u|GpioPin7 <<8u|GpioAf6)
#define PE08_6x           (GpioPortE<<16u|GpioPin8 <<8u|GpioAf6)
#define PE09_6x           (GpioPortE<<16u|GpioPin9 <<8u|GpioAf6)
#define PE10_6x           (GpioPortE<<16u|GpioPin10<<8u|GpioAf6)
#define PE11_6x           (GpioPortE<<16u|GpioPin11<<8u|GpioAf6)
#define PE12_6x           (GpioPortE<<16u|GpioPin12<<8u|GpioAf6)
#define PE13_6x           (GpioPortE<<16u|GpioPin13<<8u|GpioAf6)
#define PE14_6x           (GpioPortE<<16u|GpioPin14<<8u|GpioAf6)
#define PE15_6x           (GpioPortE<<16u|GpioPin15<<8u|GpioAf6)
#define PF00_6x           (GpioPortF<<16u|GpioPin0 <<8u|GpioAf6)
#define PF01_6x           (GpioPortF<<16u|GpioPin1 <<8u|GpioAf6)
#define PF02_6x           (GpioPortF<<16u|GpioPin2 <<8u|GpioAf6)
#define PF03_6x           (GpioPortF<<16u|GpioPin3 <<8u|GpioAf6)
#define PF04_6x           (GpioPortF<<16u|GpioPin4 <<8u|GpioAf6)
#define PF05_6x           (GpioPortF<<16u|GpioPin5 <<8u|GpioAf6)
#define PF06_6x           (GpioPortF<<16u|GpioPin6 <<8u|GpioAf6)
#define PF07_6x           (GpioPortF<<16u|GpioPin7 <<8u|GpioAf6)
#define PF09_6x           (GpioPortF<<16u|GpioPin9 <<8u|GpioAf6)
#define PF10_6x           (GpioPortF<<16u|GpioPin10<<8u|GpioAf6)
#define PF11_6x           (GpioPortF<<16u|GpioPin11<<8u|GpioAf6)

///< GpioAf7
#define PA00_TIM0_CHA     (GpioPortA<<16u|GpioPin0 <<8u|GpioAf7)
#define PA01_SPI1_MOSI    (GpioPortA<<16u|GpioPin1 <<8u|GpioAf7)
#define PA02_SPI1_MISO    (GpioPortA<<16u|GpioPin2 <<8u|GpioAf7)
#define PA03_TIM5_CHA     (GpioPortA<<16u|GpioPin3 <<8u|GpioAf7)
#define PA04_TIM3_CH2B    (GpioPortA<<16u|GpioPin4 <<8u|GpioAf7)
#define PA05_XTH_OUT      (GpioPortA<<16u|GpioPin5 <<8u|GpioAf7)
#define PA06_LPUART0_CTS  (GpioPortA<<16u|GpioPin6 <<8u|GpioAf7)
#define PA07_TIM4_CHB     (GpioPortA<<16u|GpioPin7 <<8u|GpioAf7)
#define PA08_TIM3_BK      (GpioPortA<<16u|GpioPin8 <<8u|GpioAf7)
#define PA09_TIM5_CHA     (GpioPortA<<16u|GpioPin9 <<8u|GpioAf7)
#define PA10_TIM6_CHA     (GpioPortA<<16u|GpioPin10<<8u|GpioAf7)
#define PA11_TIM4_CHB     (GpioPortA<<16u|GpioPin11<<8u|GpioAf7)
#define PA12_PCNT_S0      (GpioPortA<<16u|GpioPin12<<8u|GpioAf7)
#define PA13_VC2_OUT      (GpioPortA<<16u|GpioPin13<<8u|GpioAf7)
#define PA14_PLL_OUT      (GpioPortA<<16u|GpioPin14<<8u|GpioAf7)
#define PA15_7x           (GpioPortA<<16u|GpioPin15<<8u|GpioAf7)
#define PB00_PLL_OUT      (GpioPortB<<16u|GpioPin0 <<8u|GpioAf7)
#define PB01_TCLK_OUT     (GpioPortB<<16u|GpioPin1 <<8u|GpioAf7)
#define PB02_TIM2_BK      (GpioPortB<<16u|GpioPin2 <<8u|GpioAf7)
#define PB03_XTH_OUT      (GpioPortB<<16u|GpioPin3 <<8u|GpioAf7)
#define PB04_LPTIM_ETR    (GpioPortB<<16u|GpioPin4 <<8u|GpioAf7)
#define PB05_UART0_RTS    (GpioPortB<<16u|GpioPin5 <<8u|GpioAf7)
#define PB06_LPTIM_TOG    (GpioPortB<<16u|GpioPin6 <<8u|GpioAf7)
#define PB07_PCNT_S1      (GpioPortB<<16u|GpioPin7 <<8u|GpioAf7)
#define PB08_UART0_TXD    (GpioPortB<<16u|GpioPin8 <<8u|GpioAf7)
#define PB09_UART0_RXD    (GpioPortB<<16u|GpioPin9 <<8u|GpioAf7)
#define PB10_UART1_RTS    (GpioPortB<<16u|GpioPin10<<8u|GpioAf7)
#define PB11_UART1_CTS    (GpioPortB<<16u|GpioPin11<<8u|GpioAf7)
#define PB12_TIM6_CHA     (GpioPortB<<16u|GpioPin12<<8u|GpioAf7)
#define PB13_TIM6_CHB     (GpioPortB<<16u|GpioPin13<<8u|GpioAf7)
#define PB14_TIM1_BK      (GpioPortB<<16u|GpioPin14<<8u|GpioAf7)
#define PB15_LPUART1_RXD  (GpioPortB<<16u|GpioPin15<<8u|GpioAf7)
#define PC00_7x           (GpioPortC<<16u|GpioPin0 <<8u|GpioAf7)
#define PC01_7x           (GpioPortC<<16u|GpioPin1 <<8u|GpioAf7)
#define PC02_7x           (GpioPortC<<16u|GpioPin2 <<8u|GpioAf7)
#define PC03_7x           (GpioPortC<<16u|GpioPin3 <<8u|GpioAf7)
#define PC04_7x           (GpioPortC<<16u|GpioPin4 <<8u|GpioAf7)
#define PC05_7x           (GpioPortC<<16u|GpioPin5 <<8u|GpioAf7)
#define PC06_7x           (GpioPortC<<16u|GpioPin6 <<8u|GpioAf7)
#define PC07_7x           (GpioPortC<<16u|GpioPin7 <<8u|GpioAf7)
#define PC08_7x           (GpioPortC<<16u|GpioPin8 <<8u|GpioAf7)
#define PC09_7x           (GpioPortC<<16u|GpioPin9 <<8u|GpioAf7)
#define PC10_7x           (GpioPortC<<16u|GpioPin10<<8u|GpioAf7)
#define PC11_7x           (GpioPortC<<16u|GpioPin11<<8u|GpioAf7)
#define PC12_7x           (GpioPortC<<16u|GpioPin12<<8u|GpioAf7)
#define PC13_7x           (GpioPortC<<16u|GpioPin13<<8u|GpioAf7)
#define PC14_7x           (GpioPortC<<16u|GpioPin14<<8u|GpioAf7)
#define PC15_7x           (GpioPortC<<16u|GpioPin15<<8u|GpioAf7)
#define PD00_7x           (GpioPortD<<16u|GpioPin0 <<8u|GpioAf7)
#define PD01_7x           (GpioPortD<<16u|GpioPin1 <<8u|GpioAf7)
#define PD02_7x           (GpioPortD<<16u|GpioPin2 <<8u|GpioAf7)
#define PD03_7x           (GpioPortD<<16u|GpioPin3 <<8u|GpioAf7)
#define PD04_7x           (GpioPortD<<16u|GpioPin4 <<8u|GpioAf7)
#define PD05_7x           (GpioPortD<<16u|GpioPin5 <<8u|GpioAf7)
#define PD06_7x           (GpioPortD<<16u|GpioPin6 <<8u|GpioAf7)
#define PD07_7x           (GpioPortD<<16u|GpioPin7 <<8u|GpioAf7)
#define PD08_7x           (GpioPortD<<16u|GpioPin8 <<8u|GpioAf7)
#define PD09_7x           (GpioPortD<<16u|GpioPin9 <<8u|GpioAf7)
#define PD10_7x           (GpioPortD<<16u|GpioPin10<<8u|GpioAf7)
#define PD11_7x           (GpioPortD<<16u|GpioPin11<<8u|GpioAf7)
#define PD12_7x           (GpioPortD<<16u|GpioPin12<<8u|GpioAf7)
#define PD13_7x           (GpioPortD<<16u|GpioPin13<<8u|GpioAf7)
#define PD14_7x           (GpioPortD<<16u|GpioPin14<<8u|GpioAf7)
#define PD15_7x           (GpioPortD<<16u|GpioPin15<<8u|GpioAf7)
#define PE00_7x           (GpioPortE<<16u|GpioPin0 <<8u|GpioAf7)
#define PE01_7x           (GpioPortE<<16u|GpioPin1 <<8u|GpioAf7)
#define PE02_7x           (GpioPortE<<16u|GpioPin2 <<8u|GpioAf7)
#define PE03_7x           (GpioPortE<<16u|GpioPin3 <<8u|GpioAf7)
#define PE04_7x           (GpioPortE<<16u|GpioPin4 <<8u|GpioAf7)
#define PE05_7x           (GpioPortE<<16u|GpioPin5 <<8u|GpioAf7)
#define PE06_7x           (GpioPortE<<16u|GpioPin6 <<8u|GpioAf7)
#define PE07_7x           (GpioPortE<<16u|GpioPin7 <<8u|GpioAf7)
#define PE08_7x           (GpioPortE<<16u|GpioPin8 <<8u|GpioAf7)
#define PE09_7x           (GpioPortE<<16u|GpioPin9 <<8u|GpioAf7)
#define PE10_7x           (GpioPortE<<16u|GpioPin10<<8u|GpioAf7)
#define PE11_7x           (GpioPortE<<16u|GpioPin11<<8u|GpioAf7)
#define PE12_7x           (GpioPortE<<16u|GpioPin12<<8u|GpioAf7)
#define PE13_7x           (GpioPortE<<16u|GpioPin13<<8u|GpioAf7)
#define PE14_7x           (GpioPortE<<16u|GpioPin14<<8u|GpioAf7)
#define PE15_7x           (GpioPortE<<16u|GpioPin15<<8u|GpioAf7)
#define PF00_7x           (GpioPortF<<16u|GpioPin0 <<8u|GpioAf7)
#define PF01_7x           (GpioPortF<<16u|GpioPin1 <<8u|GpioAf7)
#define PF02_7x           (GpioPortF<<16u|GpioPin2 <<8u|GpioAf7)
#define PF03_7x           (GpioPortF<<16u|GpioPin3 <<8u|GpioAf7)
#define PF04_7x           (GpioPortF<<16u|GpioPin4 <<8u|GpioAf7)
#define PF05_7x           (GpioPortF<<16u|GpioPin5 <<8u|GpioAf7)
#define PF06_7x           (GpioPortF<<16u|GpioPin6 <<8u|GpioAf7)
#define PF07_7x           (GpioPortF<<16u|GpioPin7 <<8u|GpioAf7)
#define PF09_7x           (GpioPortF<<16u|GpioPin9 <<8u|GpioAf7)
#define PF10_7x           (GpioPortF<<16u|GpioPin10<<8u|GpioAf7)
#define PF11_7x           (GpioPortF<<16u|GpioPin11<<8u|GpioAf7)


/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
typedef uint32_t GpioPinMux;
/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
  Global function prototypes (definition in C source)
*******************************************************************************/
 ///< GPIO IO初始化/去初始化
en_result_t Gpio_Init(en_gpio_port_t enPort, en_gpio_pin_t enPin, stc_gpio_cfg_t *pstcGpioCfg);

///< GPIO 获取端口输入电平
boolean_t   Gpio_GetInputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin);
uint16_t    Gpio_GetInputData(en_gpio_port_t enPort);

///< GPIO 设置端口输出
///< GPIO 端口输出电平配置及获取
en_result_t Gpio_WriteOutputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin, boolean_t bVal);
boolean_t   Gpio_ReadOutputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin);
///< GPIO 端口/引脚输出电平置位
en_result_t Gpio_SetPort(en_gpio_port_t enPort, uint16_t u16ValMsk);
en_result_t Gpio_SetIO(en_gpio_port_t enPort, en_gpio_pin_t enPin);
///< GPIO 端口/引脚输出电平清零
en_result_t Gpio_ClrPort(en_gpio_port_t enPort, uint16_t u16ValMsk);
en_result_t Gpio_ClrIO(en_gpio_port_t enPort, en_gpio_pin_t enPin);
///< GPIO 端口输出电平置位与清零设置
en_result_t Gpio_SetClrPort(en_gpio_port_t enPort, uint32_t u32ValMsk);

///< GPIO 设置端口为模拟功能
en_result_t Gpio_SetAnalogMode(en_gpio_port_t enPort, en_gpio_pin_t enPin);

///< GPIO 设置端口为端口复用功能
en_result_t Gpio_SetAfMode(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_af_t enAf);
void Gpio_SetAfMode_Lite(GpioPinMux PinMux);

///< GPIO 端口中断控制功能使能/关闭
en_result_t Gpio_EnableIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_irqtype_t enType);
en_result_t Gpio_DisableIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_irqtype_t enType);
///< GPIO 中断状态获取
boolean_t   Gpio_GetIrqStatus(en_gpio_port_t enPort, en_gpio_pin_t enPin);
///< GPIO 中断标志清除
en_result_t Gpio_ClearIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin);

///< GPIO 端口辅助功能配置
///< GPIO 中断模式配置
en_result_t Gpio_SfIrqModeCfg(en_gpio_sf_irqmode_t enIrqMode);
///< GPIO IR输出极性配置
en_result_t Gpio_SfIrPolCfg(en_gpio_sf_irpol_t enIrPolMode);
///< GPIO HCLK输出配置
en_result_t Gpio_SfHClkOutputCfg(en_gpio_sf_hclkout_g_t enGate, en_gpio_sf_hclkout_div_t enDiv);
///< GPIO PCLK输出配置
en_result_t Gpio_SfPClkOutputCfg(en_gpio_sf_pclkout_g_t enGate, en_gpio_sf_pclkout_div_t enDiv);
///< GPIO 外部时钟输入配置
en_result_t Gpio_SfExtClkCfg(en_gpio_sf_ssn_extclk_t enExtClk);
///< GPIO SPI SSN输入配置
en_result_t Gpio_SfSsnCfg(en_gpio_sf_ssnspi_t enSpi, en_gpio_sf_ssn_extclk_t enSsn);
///< GPIO Timer 门控输入配置
en_result_t Gpio_SfTimGCfg(en_gpio_sf_tim_g_t enTimG, en_gpio_sf_t enSf);
///< GPIO Timer ETR选择配置
en_result_t Gpio_SfTimECfg(en_gpio_sf_tim_e_t enTimE, en_gpio_sf_t enSf);
///< GPIO Timer 捕获输入配置
en_result_t Gpio_SfTimCCfg(en_gpio_sf_tim_c_t enTimC, en_gpio_sf_t enSf);
///< GPIO PCA捕获选择配置
en_result_t Gpio_SfPcaCfg(en_gpio_sf_pca_t enPca, en_gpio_sf_t enSf);
///< GPIO PCNT捕获选择配置
en_result_t Gpio_SfPcntCfg(en_gpio_sf_pcnt_t enPcnt, en_gpio_sf_t enSf);

//@} // GpioGroup

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
