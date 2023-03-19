/**

  ******************************************************************************

  * @file    bl602_gpio.h

  * @version V1.2

  * @date    2019-12-14

  * @brief   This file is the description of.IP register

  ******************************************************************************

  * @attention

  *

  * <h2><center>&copy; COPYRIGHT(c) 2019 Bouffalo Lab</center></h2>

  *

  * Redistribution and use in source and binary forms, with or without modification,

  * are permitted provided that the following conditions are met:

  *   1. Redistributions of source code must retain the above copyright notice,

  *      this list of conditions and the following disclaimer.

  *   2. Redistributions in binary form must reproduce the above copyright notice,

  *      this list of conditions and the following disclaimer in the documentation

  *      and/or other materials provided with the distribution.

  *   3. Neither the name of Bouffalo Lab nor the names of its contributors

  *      may be used to endorse or promote products derived from this software

  *      without specific prior written permission.

  *

  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"

  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE

  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE

  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE

  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL

  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR

  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER

  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,

  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE

  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  *

  ******************************************************************************

  */

#ifndef __BL602_GPIO_H__
#define __BL602_GPIO_H__

typedef enum {
    GLB_GPIO_PIN_0 = 0,
    GLB_GPIO_PIN_1,
    GLB_GPIO_PIN_2,
    GLB_GPIO_PIN_3,
    GLB_GPIO_PIN_4,
    GLB_GPIO_PIN_5,
    GLB_GPIO_PIN_6,
    GLB_GPIO_PIN_7,
    GLB_GPIO_PIN_8,
    GLB_GPIO_PIN_9,
    GLB_GPIO_PIN_10,
    GLB_GPIO_PIN_11,
    GLB_GPIO_PIN_12,
    GLB_GPIO_PIN_13,
    GLB_GPIO_PIN_14,
    GLB_GPIO_PIN_15,
    GLB_GPIO_PIN_16,
    GLB_GPIO_PIN_17,
    GLB_GPIO_PIN_18,
    GLB_GPIO_PIN_19,
    GLB_GPIO_PIN_20,
    GLB_GPIO_PIN_21,
    GLB_GPIO_PIN_22,
    GLB_GPIO_PIN_MAX,
} GLB_GPIO_Type;

#define GPIO_MODE_INPUT  ((uint32_t)0x00000000U) /*!< Input Floating Mode                   */
#define GPIO_MODE_OUTPUT ((uint32_t)0x00000001U) /*!< Output Push Pull Mode                 */
#define GPIO_MODE_AF     ((uint32_t)0x00000002U) /*!< Alternate function                    */
#define GPIO_MODE_ANALOG ((uint32_t)0x00000003U) /*!< Analog function                       */
#define GPIO_PULL_UP     ((uint32_t)0x00000000U) /*!< GPIO pull up                          */
#define GPIO_PULL_DOWN   ((uint32_t)0x00000001U) /*!< GPIO pull down                        */
#define GPIO_PULL_NONE   ((uint32_t)0x00000002U) /*!< GPIO no pull up or down               */

typedef enum {
    GPIO_FUN_SDIO = 1,
    GPIO_FUN_FLASH = 2,
    GPIO_FUN_SPI = 4,
    GPIO_FUN_I2C = 6,
    GPIO_FUN_UART = 7,
    GPIO_FUN_PWM = 8,
    GPIO_FUN_EXT_PA = 9,
    GPIO_FUN_ANALOG = 10,
    GPIO_FUN_SWGPIO = 11,
    GPIO_FUN_GPIO = 11,
    GPIO_FUN_JTAG = 14,
    GPIO_FUN_UART0_RTS = 0x70,
    GPIO_FUN_UART0_CTS = 0x71,
    GPIO_FUN_UART0_TX = 0x72,
    GPIO_FUN_UART0_RX = 0x73,
    GPIO_FUN_UART1_RTS = 0x74,
    GPIO_FUN_UART1_CTS = 0x75,
    GPIO_FUN_UART1_TX = 0x76,
    GPIO_FUN_UART1_RX = 0x77,
    GPIO_FUN_GPIO_OUTPUT = 0x80,
    GPIO_FUN_GPIO_INPUT = 0x81,
    GPIO_FUN_UNUSED = 255,
} GLB_GPIO_FUNC_Type;

typedef struct
{
    uint8_t gpioPin;
    uint8_t gpioFun;
    uint8_t gpioMode;
    uint8_t pullType;
    uint8_t drive;
    uint8_t smtCtrl;
} GLB_GPIO_Cfg_Type;

/* GPIO0 function definition */
#define GPIO0_FUN_SDIO_CLK          1
#define GPIO0_FUN_SF_D1             2
#define GPIO0_FUN_UNUSED3           3
#define GPIO0_FUN_SPI_MOSI_SPI_MISO 4
#define GPIO0_FUN_UNUSED5           5
#define GPIO0_FUN_I2C_SCL           6
#define GPIO0_FUN_UART_SIG0         7
#define GPIO0_FUN_PWM_CH0           8
#define GPIO0_FUN_FEM_GPIO_0        9
#define GPIO0_FUN_ATEST_IN          10
#define GPIO0_FUN_SWGPIO_0          11
#define GPIO0_FUN_E21_TMS           14
/* GPIO1 function definition */
#define GPIO1_FUN_SDIO_CMD          1
#define GPIO1_FUN_SF_D2             2
#define GPIO1_FUN_UNUSED3           3
#define GPIO1_FUN_SPI_MISO_SPI_MOSI 4
#define GPIO1_FUN_UNUSED5           5
#define GPIO1_FUN_I2C_SDA           6
#define GPIO1_FUN_UART_SIG1         7
#define GPIO1_FUN_PWM_CH1           8
#define GPIO1_FUN_FEM_GPIO_1        9
#define GPIO1_FUN_ATEST_IP          10
#define GPIO1_FUN_SWGPIO_1          11
#define GPIO1_FUN_E21_TDI           14
/* GPIO2 function definition */
#define GPIO2_FUN_SDIO_DAT0  1
#define GPIO2_FUN_SF_D3      2
#define GPIO2_FUN_UNUSED3    3
#define GPIO2_FUN_SPI_SS     4
#define GPIO2_FUN_UNUSED5    5
#define GPIO2_FUN_I2C_SCL    6
#define GPIO2_FUN_UART_SIG2  7
#define GPIO2_FUN_PWM_CH2    8
#define GPIO2_FUN_FEM_GPIO_2 9
#define GPIO2_FUN_ATEST_QN   10
#define GPIO2_FUN_SWGPIO_2   11
#define GPIO2_FUN_E21_TCK    14
/* GPIO3 function definition */
#define GPIO3_FUN_SDIO_DAT1  1
#define GPIO3_FUN_UNUSED2    2
#define GPIO3_FUN_UNUSED3    3
#define GPIO3_FUN_SPI_SCLK   4
#define GPIO3_FUN_UNUSED5    5
#define GPIO3_FUN_I2C_SDA    6
#define GPIO3_FUN_UART_SIG3  7
#define GPIO3_FUN_PWM_CH3    8
#define GPIO3_FUN_FEM_GPIO_3 9
#define GPIO3_FUN_ATEST_QP   10
#define GPIO3_FUN_SWGPIO_3   11
#define GPIO3_FUN_E21_TDO    14
/* GPIO4 function definition */
#define GPIO4_FUN_SDIO_DAT2         1
#define GPIO4_FUN_UNUSED2           2
#define GPIO4_FUN_UNUSED3           3
#define GPIO4_FUN_SPI_MOSI_SPI_MISO 4
#define GPIO4_FUN_UNUSED5           5
#define GPIO4_FUN_I2C_SCL           6
#define GPIO4_FUN_UART_SIG4         7
#define GPIO4_FUN_PWM_CH4           8
#define GPIO4_FUN_FEM_GPIO_0        9
#define GPIO4_FUN_GPIP_CH1          10
#define GPIO4_FUN_SWGPIO_4          11
#define GPIO4_FUN_E21_TMS           14
/* GPIO5 function definition */
#define GPIO5_FUN_SDIO_DAT3         1
#define GPIO5_FUN_UNUSED2           2
#define GPIO5_FUN_UNUSED3           3
#define GPIO5_FUN_SPI_MISO_SPI_MOSI 4
#define GPIO5_FUN_UNUSED5           5
#define GPIO5_FUN_I2C_SDA           6
#define GPIO5_FUN_UART_SIG5         7
#define GPIO5_FUN_PWM_CH0           8
#define GPIO5_FUN_FEM_GPIO_1        9
#define GPIO5_FUN_GPIP_CH4          10
#define GPIO5_FUN_SWGPIO_5          11
#define GPIO5_FUN_E21_TDI           14
/* GPIO6 function definition */
#define GPIO6_FUN_UNUSED1    1
#define GPIO6_FUN_UNUSED2    2
#define GPIO6_FUN_UNUSED3    3
#define GPIO6_FUN_SPI_SS     4
#define GPIO6_FUN_UNUSED5    5
#define GPIO6_FUN_I2C_SCL    6
#define GPIO6_FUN_UART_SIG6  7
#define GPIO6_FUN_PWM_CH1    8
#define GPIO6_FUN_FEM_GPIO_2 9
#define GPIO6_FUN_GPIP_CH5   10
#define GPIO6_FUN_SWGPIO_6   11
#define GPIO6_FUN_E21_TCK    14
/* GPIO7 function definition */
#define GPIO7_FUN_UNUSED1    1
#define GPIO7_FUN_UNUSED2    2
#define GPIO7_FUN_UNUSED3    3
#define GPIO7_FUN_SPI_SCLK   4
#define GPIO7_FUN_UNUSED5    5
#define GPIO7_FUN_I2C_SDA    6
#define GPIO7_FUN_UART_SIG7  7
#define GPIO7_FUN_PWM_CH2    8
#define GPIO7_FUN_FEM_GPIO_3 9
#define GPIO7_FUN_UNUSED10   10
#define GPIO7_FUN_SWGPIO_7   11
#define GPIO7_FUN_E21_TDO    14
/* GPIO8 function definition */
#define GPIO8_FUN_UNUSED1           1
#define GPIO8_FUN_UNUSED2           2
#define GPIO8_FUN_UNUSED3           3
#define GPIO8_FUN_SPI_MOSI_SPI_MISO 4
#define GPIO8_FUN_UNUSED5           5
#define GPIO8_FUN_I2C_SCL           6
#define GPIO8_FUN_UART_SIG0         7
#define GPIO8_FUN_PWM_CH3           8
#define GPIO8_FUN_FEM_GPIO_0        9
#define GPIO8_FUN_UNUSED10          10
#define GPIO8_FUN_SWGPIO_8          11
#define GPIO8_FUN_E21_TMS           14
/* GPIO9 function definition */
#define GPIO9_FUN_UNUSED1           1
#define GPIO9_FUN_UNUSED2           2
#define GPIO9_FUN_UNUSED3           3
#define GPIO9_FUN_SPI_MISO_SPI_MOSI 4
#define GPIO9_FUN_UNUSED5           5
#define GPIO9_FUN_I2C_SDA           6
#define GPIO9_FUN_UART_SIG1         7
#define GPIO9_FUN_PWM_CH4           8
#define GPIO9_FUN_FEM_GPIO_1        9
#define GPIO9_FUN_GPIP_CH6_GPIP_CH7 10
#define GPIO9_FUN_SWGPIO_9          11
#define GPIO9_FUN_E21_TDI           14
/* GPIO10 function definition */
#define GPIO10_FUN_UNUSED1                   1
#define GPIO10_FUN_UNUSED2                   2
#define GPIO10_FUN_UNUSED3                   3
#define GPIO10_FUN_SPI_SS                    4
#define GPIO10_FUN_UNUSED5                   5
#define GPIO10_FUN_I2C_SCL                   6
#define GPIO10_FUN_UART_SIG2                 7
#define GPIO10_FUN_PWM_CH0                   8
#define GPIO10_FUN_FEM_GPIO_2                9
#define GPIO10_FUN_MICBIAS_GPIP_CH8_GPIP_CH9 10
#define GPIO10_FUN_SWGPIO_10                 11
#define GPIO10_FUN_E21_TCK                   14
/* GPIO11 function definition */
#define GPIO11_FUN_UNUSED1             1
#define GPIO11_FUN_UNUSED2             2
#define GPIO11_FUN_UNUSED3             3
#define GPIO11_FUN_SPI_SCLK            4
#define GPIO11_FUN_UNUSED5             5
#define GPIO11_FUN_I2C_SDA             6
#define GPIO11_FUN_UART_SIG3           7
#define GPIO11_FUN_PWM_CH1             8
#define GPIO11_FUN_FEM_GPIO_3          9
#define GPIO11_FUN_IRLED_OUT_GPIP_CH10 10
#define GPIO11_FUN_SWGPIO_11           11
#define GPIO11_FUN_E21_TDO             14
/* GPIO12 function definition */
#define GPIO12_FUN_UNUSED1                 1
#define GPIO12_FUN_UNUSED2                 2
#define GPIO12_FUN_UNUSED3                 3
#define GPIO12_FUN_SPI_MOSI_SPI_MISO       4
#define GPIO12_FUN_UNUSED5                 5
#define GPIO12_FUN_I2C_SCL                 6
#define GPIO12_FUN_UART_SIG4               7
#define GPIO12_FUN_PWM_CH2                 8
#define GPIO12_FUN_FEM_GPIO_0              9
#define GPIO12_FUN_GPIP_CH0_GPADC_VREF_EXT 10
#define GPIO12_FUN_SWGPIO_12               11
#define GPIO12_FUN_E21_TMS                 14
/* GPIO13 function definition */
#define GPIO13_FUN_UNUSED1           1
#define GPIO13_FUN_UNUSED2           2
#define GPIO13_FUN_UNUSED3           3
#define GPIO13_FUN_SPI_MISO_SPI_MOSI 4
#define GPIO13_FUN_UNUSED5           5
#define GPIO13_FUN_I2C_SDA           6
#define GPIO13_FUN_UART_SIG5         7
#define GPIO13_FUN_PWM_CH3           8
#define GPIO13_FUN_FEM_GPIO_1        9
#define GPIO13_FUN_GPIP_CH3          10
#define GPIO13_FUN_SWGPIO_13         11
#define GPIO13_FUN_E21_TDI           14
/* GPIO14 function definition */
#define GPIO14_FUN_UNUSED1    1
#define GPIO14_FUN_UNUSED2    2
#define GPIO14_FUN_UNUSED3    3
#define GPIO14_FUN_SPI_SS     4
#define GPIO14_FUN_UNUSED5    5
#define GPIO14_FUN_I2C_SCL    6
#define GPIO14_FUN_UART_SIG6  7
#define GPIO14_FUN_PWM_CH4    8
#define GPIO14_FUN_FEM_GPIO_2 9
#define GPIO14_FUN_GPIP_CH2   10
#define GPIO14_FUN_SWGPIO_14  11
#define GPIO14_FUN_E21_TCK    14
/* GPIO15 function definition */
#define GPIO15_FUN_UNUSED1                 1
#define GPIO15_FUN_UNUSED2                 2
#define GPIO15_FUN_UNUSED3                 3
#define GPIO15_FUN_SPI_SCLK                4
#define GPIO15_FUN_UNUSED5                 5
#define GPIO15_FUN_I2C_SDA                 6
#define GPIO15_FUN_UART_SIG7               7
#define GPIO15_FUN_PWM_CH0                 8
#define GPIO15_FUN_FEM_GPIO_3              9
#define GPIO15_FUN_PSW_IRRCV_OUT_GPIP_CH11 10
#define GPIO15_FUN_SWGPIO_15               11
#define GPIO15_FUN_E21_TDO                 14
/* GPIO16 function definition */
#define GPIO16_FUN_UNUSED1           1
#define GPIO16_FUN_UNUSED2           2
#define GPIO16_FUN_UNUSED3           3
#define GPIO16_FUN_SPI_MOSI_SPI_MISO 4
#define GPIO16_FUN_UNUSED5           5
#define GPIO16_FUN_I2C_SCL           6
#define GPIO16_FUN_UART_SIG0         7
#define GPIO16_FUN_PWM_CH1           8
#define GPIO16_FUN_FEM_GPIO_0        9
#define GPIO16_FUN_UNUSED10          10
#define GPIO16_FUN_SWGPIO_16         11
#define GPIO16_FUN_E21_TMS           14
/* GPIO17 function definition */
#define GPIO17_FUN_UNUSED1           1
#define GPIO17_FUN_SF_D3             2
#define GPIO17_FUN_UNUSED3           3
#define GPIO17_FUN_SPI_MISO_SPI_MOSI 4
#define GPIO17_FUN_UNUSED5           5
#define GPIO17_FUN_I2C_SDA           6
#define GPIO17_FUN_UART_SIG1         7
#define GPIO17_FUN_PWM_CH2           8
#define GPIO17_FUN_FEM_GPIO_1        9
#define GPIO17_FUN_PMIP_DC_TP_OUT    10
#define GPIO17_FUN_SWGPIO_17         11
#define GPIO17_FUN_E21_TDI           14
/* GPIO18 function definition */
#define GPIO18_FUN_UNUSED1    1
#define GPIO18_FUN_SF_D2      2
#define GPIO18_FUN_UNUSED3    3
#define GPIO18_FUN_SPI_SS     4
#define GPIO18_FUN_UNUSED5    5
#define GPIO18_FUN_I2C_SCL    6
#define GPIO18_FUN_UART_SIG2  7
#define GPIO18_FUN_PWM_CH3    8
#define GPIO18_FUN_FEM_GPIO_2 9
#define GPIO18_FUN_UNUSED10   10
#define GPIO18_FUN_SWGPIO_18  11
#define GPIO18_FUN_E21_TCK    14
/* GPIO19 function definition */
#define GPIO19_FUN_UNUSED1    1
#define GPIO19_FUN_SF_D1      2
#define GPIO19_FUN_UNUSED3    3
#define GPIO19_FUN_SPI_SCLK   4
#define GPIO19_FUN_UNUSED5    5
#define GPIO19_FUN_I2C_SDA    6
#define GPIO19_FUN_UART_SIG3  7
#define GPIO19_FUN_PWM_CH4    8
#define GPIO19_FUN_FEM_GPIO_3 9
#define GPIO19_FUN_UNUSED10   10
#define GPIO19_FUN_SWGPIO_19  11
#define GPIO19_FUN_E21_TDO    14
/* GPIO20 function definition */
#define GPIO20_FUN_UNUSED1           1
#define GPIO20_FUN_SF_D0             2
#define GPIO20_FUN_UNUSED3           3
#define GPIO20_FUN_SPI_MOSI_SPI_MISO 4
#define GPIO20_FUN_UNUSED5           5
#define GPIO20_FUN_I2C_SCL           6
#define GPIO20_FUN_UART_SIG4         7
#define GPIO20_FUN_PWM_CH0           8
#define GPIO20_FUN_FEM_GPIO_0        9
#define GPIO20_FUN_UNUSED10          10
#define GPIO20_FUN_SWGPIO_20         11
#define GPIO20_FUN_E21_TMS           14
/* GPIO21 function definition */
#define GPIO21_FUN_UNUSED1           1
#define GPIO21_FUN_SF_CS             2
#define GPIO21_FUN_UNUSED3           3
#define GPIO21_FUN_SPI_MISO_SPI_MOSI 4
#define GPIO21_FUN_UNUSED5           5
#define GPIO21_FUN_I2C_SDA           6
#define GPIO21_FUN_UART_SIG5         7
#define GPIO21_FUN_PWM_CH1           8
#define GPIO21_FUN_FEM_GPIO_1        9
#define GPIO21_FUN_UNUSED10          10
#define GPIO21_FUN_SWGPIO_21         11
#define GPIO21_FUN_E21_TDI           14
/* GPIO22 function definition */
#define GPIO22_FUN_UNUSED1    1
#define GPIO22_FUN_SF_CLK_OUT 2
#define GPIO22_FUN_UNUSED3    3
#define GPIO22_FUN_SPI_SS     4
#define GPIO22_FUN_UNUSED5    5
#define GPIO22_FUN_I2C_SCL    6
#define GPIO22_FUN_UART_SIG6  7
#define GPIO22_FUN_PWM_CH2    8
#define GPIO22_FUN_FEM_GPIO_2 9
#define GPIO22_FUN_UNUSED10   10
#define GPIO22_FUN_SWGPIO_22  11
#define GPIO22_FUN_E21_TCK    14

#endif /*__BL602_GPIO_H__ */
