/**

  ******************************************************************************

  * @file    bl702_gpio.h

  * @version V1.2

  * @date    2020-09-04

  * @brief   This file is the description of.IP register

  ******************************************************************************

  * @attention

  *

  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>

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

#ifndef __BL702_GPIO_H__
#define __BL702_GPIO_H__

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
    GLB_GPIO_PIN_23,
    GLB_GPIO_PIN_24,
    GLB_GPIO_PIN_25,
    GLB_GPIO_PIN_26,
    GLB_GPIO_PIN_27,
    GLB_GPIO_PIN_28,
    GLB_GPIO_PIN_29,
    GLB_GPIO_PIN_30,
    GLB_GPIO_PIN_31,
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
    GPIO_FUN_CLK_OUT = 0,
    GPIO_FUN_BT_COEXIST = 1,
    GPIO_FUN_FLASH_PSRAM = 2,
    GPIO_FUN_QSPI = 2,
    GPIO_FUN_I2S = 3,
    GPIO_FUN_SPI = 4,
    GPIO_FUN_I2C = 6,
    GPIO_FUN_UART = 7,
    GPIO_FUN_PWM = 8,
    GPIO_FUN_CAM = 9,
    GPIO_FUN_ANALOG = 10,
    GPIO_FUN_GPIO = 11,
    GPIO_FUN_RF_TEST = 12,
    GPIO_FUN_SCAN = 13,
    GPIO_FUN_E21_JTAG = 14,
    GPIO_FUN_DEBUG = 15,
    GPIO_FUN_EXTERNAL_PA = 16,
    GPIO_FUN_USB_TRANCEIVER = 17,
    GPIO_FUN_USB_CONTROLLER = 18,
    GPIO_FUN_ETHER_MAC = 19,
    GPIO_FUN_EMAC = 19,
    GPIO_FUN_QDEC = 20,
    GPIO_FUN_KEY_SCAN_IN = 21,
    GPIO_FUN_KEY_SCAN_ROW = 21,
    GPIO_FUN_KEY_SCAN_DRIVE = 22,
    GPIO_FUN_KEY_SCAN_COL = 22,
    GPIO_FUN_CAM_MISC = 23,
    GPIO_FUN_USB = 0xD0,
    GPIO_FUN_DAC = 0xD1,
    GPIO_FUN_ADC = 0xD2,
    GPIO_FUN_QDEC_LED = 0xD3,
    GPIO_FUN_GPIO_OUTPUT_UP = 0xE0,
    GPIO_FUN_GPIO_OUTPUT_DOWN = 0xE1,
    GPIO_FUN_GPIO_OUTPUT_NONE = 0xE2,
    GPIO_FUN_GPIO_INPUT_UP = 0xE3,
    GPIO_FUN_GPIO_INPUT_DOWN = 0xE4,
    GPIO_FUN_GPIO_INPUT_NONE = 0xE5,
    GPIO_FUN_GPIO_EXTI_RISING_EDGE = 0xE6,
    GPIO_FUN_GPIO_EXTI_FALLING_EDGE = 0xE7,
    GPIO_FUN_GPIO_EXTI_HIGH_LEVEL = 0xE8,
    GPIO_FUN_GPIO_EXTI_LOW_LEVEL = 0xE9,
    GPIO_FUN_UART0_RTS = 0xF0,
    GPIO_FUN_UART0_CTS = 0xF1,
    GPIO_FUN_UART0_TX = 0xF2,
    GPIO_FUN_UART0_RX = 0xF3,
    GPIO_FUN_UART1_RTS = 0xF4,
    GPIO_FUN_UART1_CTS = 0xF5,
    GPIO_FUN_UART1_TX = 0xF6,
    GPIO_FUN_UART1_RX = 0xF7,
    GPIO_FUN_WAKEUP = 0xFE,
    GPIO_FUN_UNUSED = 0xFF
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
#define GPIO0_FUN_CLK_OUT_0             0
#define GPIO0_FUN_BT_ABORT              1
#define GPIO0_FUN_UNUSED2               2
#define GPIO0_FUN_I2S0_BCLK             3
#define GPIO0_FUN_SPI_0_MOSI_SPI_0_MISO 4
#define GPIO0_FUN_I2C0_SCL              6
#define GPIO0_FUN_UART_SIG0_UART_SIG4   7
#define GPIO0_FUN_PWM_CH0               8
#define GPIO0_FUN_PIX_CLK               9
#define GPIO0_FUN_UNUSED10              10
#define GPIO0_FUN_REG_GPIO_0            11
#define GPIO0_FUN_UNUSED12              12
#define GPIO0_FUN_SCAN_IN_0             13
#define GPIO0_FUN_E21_TMS_E21_TCK       14
#define GPIO0_FUN_S_CCI_CLK             15
#define GPIO0_FUN_FEM_GPIO_0            16
#define GPIO0_FUN_USB_TX_DN_USB_RX_DN   17
#define GPIO0_FUN_USB_SUS               18
#define GPIO0_FUN_MII_REF_CLK           19
#define GPIO0_FUN_QDEC0_A               20
#define GPIO0_FUN_ROW_I_0               21
#define GPIO0_FUN_COL_O_0               22
#define GPIO0_FUN_CAM_PWRDN             23
/* GPIO1 function definition */
#define GPIO1_FUN_CLK_OUT_1             0
#define GPIO1_FUN_BT_ACTIVE             1
#define GPIO1_FUN_UNUSED2               2
#define GPIO1_FUN_I2S0_FS               3
#define GPIO1_FUN_SPI_0_MISO_SPI_0_MOSI 4
#define GPIO1_FUN_I2C0_SDA              6
#define GPIO1_FUN_UART_SIG1_UART_SIG5   7
#define GPIO1_FUN_PWM_CH1               8
#define GPIO1_FUN_FRAME_VLD             9
#define GPIO1_FUN_UNUSED10              10
#define GPIO1_FUN_REG_GPIO_1            11
#define GPIO1_FUN_UNUSED12              12
#define GPIO1_FUN_SCAN_IN_1             13
#define GPIO1_FUN_E21_TDI_E21_TDO       14
#define GPIO1_FUN_S_CCI_CS              15
#define GPIO1_FUN_FEM_GPIO_1            16
#define GPIO1_FUN_USB_TX_OE             17
#define GPIO1_FUN_USB_ENUM              18
#define GPIO1_FUN_MII_TXD_0             19
#define GPIO1_FUN_QDEC0_B               20
#define GPIO1_FUN_ROW_I_1               21
#define GPIO1_FUN_COL_O_1               22
#define GPIO1_FUN_CAM_REF_CLK           23
/* GPIO2 function definition */
#define GPIO2_FUN_CLK_OUT_0           0
#define GPIO2_FUN_BT_PRI              1
#define GPIO2_FUN_UNUSED2             2
#define GPIO2_FUN_I2S0_DIO_I2S0_DO    3
#define GPIO2_FUN_SPI_0_SS            4
#define GPIO2_FUN_I2C0_SCL            6
#define GPIO2_FUN_UART_SIG2_UART_SIG6 7
#define GPIO2_FUN_PWM_CH2             8
#define GPIO2_FUN_LINE_VLD            9
#define GPIO2_FUN_UNUSED10            10
#define GPIO2_FUN_REG_GPIO_2          11
#define GPIO2_FUN_UNUSED12            12
#define GPIO2_FUN_SCAN_IN_2           13
#define GPIO2_FUN_E21_TCK_E21_TMS     14
#define GPIO2_FUN_S_CCI_DATA_0        15
#define GPIO2_FUN_FEM_GPIO_2          16
#define GPIO2_FUN_USB_TX_DP_USB_RX_DP 17
#define GPIO2_FUN_USB_OEB             18
#define GPIO2_FUN_MII_TXD_1           19
#define GPIO2_FUN_QDEC0_LED           20
#define GPIO2_FUN_ROW_I_2             21
#define GPIO2_FUN_COL_O_2             22
#define GPIO2_FUN_CAM_RESET           23
/* GPIO3 function definition */
#define GPIO3_FUN_CLK_OUT_1           0
#define GPIO3_FUN_BT_ABORT            1
#define GPIO3_FUN_UNUSED2             2
#define GPIO3_FUN_I2S0_RCLK_O_I2S0_DI 3
#define GPIO3_FUN_SPI_0_SCLK          4
#define GPIO3_FUN_I2C0_SDA            6
#define GPIO3_FUN_UART_SIG3_UART_SIG7 7
#define GPIO3_FUN_PWM_CH3             8
#define GPIO3_FUN_PIX_DAT0            9
#define GPIO3_FUN_UNUSED10            10
#define GPIO3_FUN_REG_GPIO_3          11
#define GPIO3_FUN_RF_TEST_0           12
#define GPIO3_FUN_UNUSED13            13
#define GPIO3_FUN_E21_TDO_E21_TDI     14
#define GPIO3_FUN_DEBUG_0             15
#define GPIO3_FUN_FEM_GPIO_3          16
#define GPIO3_FUN_USB_SUS_EXT         17
#define GPIO3_FUN_VOP                 18
#define GPIO3_FUN_UNUSED19            19
#define GPIO3_FUN_QDEC1_A             20
#define GPIO3_FUN_ROW_I_3             21
#define GPIO3_FUN_COL_O_3             22
#define GPIO3_FUN_CAM_PWRDN           23
/* GPIO4 function definition */
#define GPIO4_FUN_CLK_OUT_0             0
#define GPIO4_FUN_BT_ACTIVE             1
#define GPIO4_FUN_UNUSED2               2
#define GPIO4_FUN_I2S0_BCLK             3
#define GPIO4_FUN_SPI_0_MOSI_SPI_0_MISO 4
#define GPIO4_FUN_I2C0_SCL              6
#define GPIO4_FUN_UART_SIG4_UART_SIG0   7
#define GPIO4_FUN_PWM_CH4               8
#define GPIO4_FUN_PIX_DAT1              9
#define GPIO4_FUN_UNUSED10              10
#define GPIO4_FUN_REG_GPIO_4            11
#define GPIO4_FUN_RF_TEST_1             12
#define GPIO4_FUN_UNUSED13              13
#define GPIO4_FUN_E21_TMS_E21_TCK       14
#define GPIO4_FUN_DEBUG_1               15
#define GPIO4_FUN_FEM_GPIO_4            16
#define GPIO4_FUN_USB_ENUM_EXT          17
#define GPIO4_FUN_VOM                   18
#define GPIO4_FUN_UNUSED19              19
#define GPIO4_FUN_QDEC1_B               20
#define GPIO4_FUN_ROW_I_4               21
#define GPIO4_FUN_COL_O_4               22
#define GPIO4_FUN_CAM_REF_CLK           23
/* GPIO5 function definition */
#define GPIO5_FUN_CLK_OUT_1             0
#define GPIO5_FUN_BT_PRI                1
#define GPIO5_FUN_UNUSED2               2
#define GPIO5_FUN_I2S0_FS               3
#define GPIO5_FUN_SPI_0_MISO_SPI_0_MOSI 4
#define GPIO5_FUN_I2C0_SDA              6
#define GPIO5_FUN_UART_SIG5_UART_SIG1   7
#define GPIO5_FUN_PWM_CH0               8
#define GPIO5_FUN_PIX_DAT2              9
#define GPIO5_FUN_UNUSED10              10
#define GPIO5_FUN_REG_GPIO_5            11
#define GPIO5_FUN_RF_TEST_2             12
#define GPIO5_FUN_UNUSED13              13
#define GPIO5_FUN_E21_TDI_E21_TDO       14
#define GPIO5_FUN_DEBUG_2               15
#define GPIO5_FUN_FEM_GPIO_0            16
#define GPIO5_FUN_USB_TX_DN_USB_RX_DN   17
#define GPIO5_FUN_BD                    18
#define GPIO5_FUN_UNUSED19              19
#define GPIO5_FUN_QDEC1_LED             20
#define GPIO5_FUN_ROW_I_5               21
#define GPIO5_FUN_COL_O_5               22
#define GPIO5_FUN_CAM_RESET             23
/* GPIO6 function definition */
#define GPIO6_FUN_CLK_OUT_0           0
#define GPIO6_FUN_BT_ABORT            1
#define GPIO6_FUN_UNUSED2             2
#define GPIO6_FUN_I2S0_DIO_I2S0_DO    3
#define GPIO6_FUN_SPI_0_SS            4
#define GPIO6_FUN_I2C0_SCL            6
#define GPIO6_FUN_UART_SIG6_UART_SIG2 7
#define GPIO6_FUN_PWM_CH1             8
#define GPIO6_FUN_PIX_DAT3            9
#define GPIO6_FUN_UNUSED10            10
#define GPIO6_FUN_REG_GPIO_6          11
#define GPIO6_FUN_RF_TEST_3           12
#define GPIO6_FUN_UNUSED13            13
#define GPIO6_FUN_E21_TCK_E21_TMS     14
#define GPIO6_FUN_DEBUG_3             15
#define GPIO6_FUN_FEM_GPIO_1          16
#define GPIO6_FUN_USB_TX_OE           17
#define GPIO6_FUN_VIP                 18
#define GPIO6_FUN_UNUSED19            19
#define GPIO6_FUN_QDEC2_A             20
#define GPIO6_FUN_ROW_I_6             21
#define GPIO6_FUN_COL_O_6             22
#define GPIO6_FUN_CAM_PWRDN           23
/* GPIO7 function definition */
#define GPIO7_FUN_CLK_OUT_1                       0
#define GPIO7_FUN_BT_ACTIVE                       1
#define GPIO7_FUN_UNUSED2                         2
#define GPIO7_FUN_I2S0_RCLK_O_I2S0_DI             3
#define GPIO7_FUN_SPI_0_SCLK                      4
#define GPIO7_FUN_I2C0_SDA                        6
#define GPIO7_FUN_UART_SIG7_UART_SIG3             7
#define GPIO7_FUN_PWM_CH2                         8
#define GPIO7_FUN_UNUSED9                         9
#define GPIO7_FUN_USB_DP_GPIP_CH_6_GPDAC_VREF_EXT 10
#define GPIO7_FUN_REG_GPIO_7                      11
#define GPIO7_FUN_UNUSED12                        12
#define GPIO7_FUN_SCAN_RSTB                       13
#define GPIO7_FUN_E21_TDO_E21_TDI                 14
#define GPIO7_FUN_S_CCI_DATA_1                    15
#define GPIO7_FUN_FEM_GPIO_2                      16
#define GPIO7_FUN_USB_TX_DP_USB_RX_DP             17
#define GPIO7_FUN_VIM                             18
#define GPIO7_FUN_MII_RXD_0                       19
#define GPIO7_FUN_QDEC2_B                         20
#define GPIO7_FUN_ROW_I_7                         21
#define GPIO7_FUN_COL_O_7                         22
#define GPIO7_FUN_CAM_REF_CLK                     23
/* GPIO8 function definition */
#define GPIO8_FUN_CLK_OUT_0             0
#define GPIO8_FUN_BT_PRI                1
#define GPIO8_FUN_UNUSED2               2
#define GPIO8_FUN_I2S0_BCLK             3
#define GPIO8_FUN_SPI_0_MOSI_SPI_0_MISO 4
#define GPIO8_FUN_I2C0_SCL              6
#define GPIO8_FUN_UART_SIG0_UART_SIG4   7
#define GPIO8_FUN_PWM_CH3               8
#define GPIO8_FUN_UNUSED9               9
#define GPIO8_FUN_USB_DM_GPIP_CH_0      10
#define GPIO8_FUN_REG_GPIO_8            11
#define GPIO8_FUN_RF_TEST_4             12
#define GPIO8_FUN_SCAN_CLK              13
#define GPIO8_FUN_E21_TMS_E21_TCK       14
#define GPIO8_FUN_DEBUG_4               15
#define GPIO8_FUN_FEM_GPIO_3            16
#define GPIO8_FUN_USB_SUS_EXT           17
#define GPIO8_FUN_RCV                   18
#define GPIO8_FUN_MII_RXD_1             19
#define GPIO8_FUN_QDEC2_LED             20
#define GPIO8_FUN_ROW_I_0               21
#define GPIO8_FUN_COL_O_8               22
#define GPIO8_FUN_CAM_RESET             23
/* GPIO9 function definition */
#define GPIO9_FUN_CLK_OUT_1                         0
#define GPIO9_FUN_BT_ABORT                          1
#define GPIO9_FUN_UNUSED2                           2
#define GPIO9_FUN_I2S0_FS                           3
#define GPIO9_FUN_SPI_0_MISO_SPI_0_MOSI             4
#define GPIO9_FUN_I2C0_SDA                          6
#define GPIO9_FUN_UART_SIG1_UART_SIG5               7
#define GPIO9_FUN_PWM_CH4                           8
#define GPIO9_FUN_UNUSED9                           9
#define GPIO9_FUN_PMIP_DC_TP_CLKPLL_DC_TP_GPIP_CH_7 10
#define GPIO9_FUN_REG_GPIO_9                        11
#define GPIO9_FUN_RF_TEST_5                         12
#define GPIO9_FUN_SCAN_EN                           13
#define GPIO9_FUN_E21_TDI_E21_TDO                   14
#define GPIO9_FUN_DEBUG_5                           15
#define GPIO9_FUN_FEM_GPIO_4                        16
#define GPIO9_FUN_USB_ENUM_EXT                      17
#define GPIO9_FUN_USB_SUS                           18
#define GPIO9_FUN_UNUSED19                          19
#define GPIO9_FUN_QDEC0_A                           20
#define GPIO9_FUN_ROW_I_1                           21
#define GPIO9_FUN_COL_O_9                           22
#define GPIO9_FUN_CAM_PWRDN                         23
/* GPIO10 function definition */
#define GPIO10_FUN_CLK_OUT_0           0
#define GPIO10_FUN_BT_ACTIVE           1
#define GPIO10_FUN_UNUSED2             2
#define GPIO10_FUN_I2S0_DIO_I2S0_DO    3
#define GPIO10_FUN_SPI_0_SS            4
#define GPIO10_FUN_I2C0_SCL            6
#define GPIO10_FUN_UART_SIG2_UART_SIG6 7
#define GPIO10_FUN_PWM_CH0             8
#define GPIO10_FUN_UNUSED9             9
#define GPIO10_FUN_MICBIAS             10
#define GPIO10_FUN_REG_GPIO_10         11
#define GPIO10_FUN_RF_TEST_6           12
#define GPIO10_FUN_UNUSED13            13
#define GPIO10_FUN_E21_TCK_E21_TMS     14
#define GPIO10_FUN_DEBUG_6             15
#define GPIO10_FUN_FEM_GPIO_0          16
#define GPIO10_FUN_USB_TX_DN_USB_RX_DN 17
#define GPIO10_FUN_USB_ENUM            18
#define GPIO10_FUN_UNUSED19            19
#define GPIO10_FUN_QDEC0_B             20
#define GPIO10_FUN_ROW_I_2             21
#define GPIO10_FUN_COL_O_10            22
#define GPIO10_FUN_CAM_REF_CLK         23
/* GPIO11 function definition */
#define GPIO11_FUN_CLK_OUT_1           0
#define GPIO11_FUN_BT_PRI              1
#define GPIO11_FUN_UNUSED2             2
#define GPIO11_FUN_I2S0_RCLK_O_I2S0_DI 3
#define GPIO11_FUN_SPI_0_SCLK          4
#define GPIO11_FUN_I2C0_SDA            6
#define GPIO11_FUN_UART_SIG3_UART_SIG7 7
#define GPIO11_FUN_PWM_CH1             8
#define GPIO11_FUN_UNUSED9             9
#define GPIO11_FUN_GPIP_CH_3           10
#define GPIO11_FUN_REG_GPIO_11         11
#define GPIO11_FUN_RF_TEST_7           12
#define GPIO11_FUN_UNUSED13            13
#define GPIO11_FUN_E21_TDO_E21_TDI     14
#define GPIO11_FUN_DEBUG_7             15
#define GPIO11_FUN_FEM_GPIO_1          16
#define GPIO11_FUN_USB_TX_OE           17
#define GPIO11_FUN_USB_OEB             18
#define GPIO11_FUN_UNUSED19            19
#define GPIO11_FUN_QDEC0_LED           20
#define GPIO11_FUN_ROW_I_3             21
#define GPIO11_FUN_COL_O_11            22
#define GPIO11_FUN_CAM_RESET           23
/* GPIO12 function definition */
#define GPIO12_FUN_CLK_OUT_0             0
#define GPIO12_FUN_BT_ABORT              1
#define GPIO12_FUN_UNUSED2               2
#define GPIO12_FUN_I2S0_BCLK             3
#define GPIO12_FUN_SPI_0_MOSI_SPI_0_MISO 4
#define GPIO12_FUN_I2C0_SCL              6
#define GPIO12_FUN_UART_SIG4_UART_SIG0   7
#define GPIO12_FUN_PWM_CH2               8
#define GPIO12_FUN_PIX_DAT4              9
#define GPIO12_FUN_GPIP_CH_4             10
#define GPIO12_FUN_REG_GPIO_12           11
#define GPIO12_FUN_RF_TEST_8             12
#define GPIO12_FUN_UNUSED13              13
#define GPIO12_FUN_E21_TMS_E21_TCK       14
#define GPIO12_FUN_DEBUG_8               15
#define GPIO12_FUN_FEM_GPIO_2            16
#define GPIO12_FUN_USB_TX_DP_USB_RX_DP   17
#define GPIO12_FUN_VOP                   18
#define GPIO12_FUN_UNUSED19              19
#define GPIO12_FUN_QDEC1_A               20
#define GPIO12_FUN_ROW_I_4               21
#define GPIO12_FUN_COL_O_12              22
#define GPIO12_FUN_CAM_PWRDN             23
/* GPIO13 function definition */
#define GPIO13_FUN_CLK_OUT_1             0
#define GPIO13_FUN_BT_ACTIVE             1
#define GPIO13_FUN_UNUSED2               2
#define GPIO13_FUN_I2S0_FS               3
#define GPIO13_FUN_SPI_0_MISO_SPI_0_MOSI 4
#define GPIO13_FUN_I2C0_SDA              6
#define GPIO13_FUN_UART_SIG5_UART_SIG1   7
#define GPIO13_FUN_PWM_CH3               8
#define GPIO13_FUN_UNUSED9               9
#define GPIO13_FUN_UNUSED10              10
#define GPIO13_FUN_REG_GPIO_13           11
#define GPIO13_FUN_UNUSED12              12
#define GPIO13_FUN_UNUSED13              13
#define GPIO13_FUN_E21_TDI_E21_TDO       14
#define GPIO13_FUN_DEBUG_9               15
#define GPIO13_FUN_FEM_GPIO_3            16
#define GPIO13_FUN_USB_SUS_EXT           17
#define GPIO13_FUN_VOM                   18
#define GPIO13_FUN_UNUSED19              19
#define GPIO13_FUN_QDEC1_B               20
#define GPIO13_FUN_ROW_I_5               21
#define GPIO13_FUN_COL_O_13              22
#define GPIO13_FUN_CAM_REF_CLK           23
/* GPIO14 function definition */
#define GPIO14_FUN_CLK_OUT_0             0
#define GPIO14_FUN_BT_PRI                1
#define GPIO14_FUN_UNUSED2               2
#define GPIO14_FUN_I2S0_DIO_I2S0_DO      3
#define GPIO14_FUN_SPI_0_SS              4
#define GPIO14_FUN_I2C0_SCL              6
#define GPIO14_FUN_UART_SIG6_UART_SIG2   7
#define GPIO14_FUN_PWM_CH4               8
#define GPIO14_FUN_UNUSED9               9
#define GPIO14_FUN_GPIP_CH_5_ATEST_OUT_0 10
#define GPIO14_FUN_REG_GPIO_14           11
#define GPIO14_FUN_RF_TEST_9             12
#define GPIO14_FUN_SCAN_OUT_0            13
#define GPIO14_FUN_E21_TCK_E21_TMS       14
#define GPIO14_FUN_DEBUG_10              15
#define GPIO14_FUN_FEM_GPIO_4            16
#define GPIO14_FUN_USB_ENUM_EXT          17
#define GPIO14_FUN_BD                    18
#define GPIO14_FUN_UNUSED19              19
#define GPIO14_FUN_QDEC1_LED             20
#define GPIO14_FUN_ROW_I_6               21
#define GPIO14_FUN_COL_O_14              22
#define GPIO14_FUN_CAM_RESET             23
/* GPIO15 function definition */
#define GPIO15_FUN_CLK_OUT_1             0
#define GPIO15_FUN_BT_ABORT              1
#define GPIO15_FUN_UNUSED2               2
#define GPIO15_FUN_I2S0_RCLK_O_I2S0_DI   3
#define GPIO15_FUN_SPI_0_SCLK            4
#define GPIO15_FUN_I2C0_SDA              6
#define GPIO15_FUN_UART_SIG7_UART_SIG3   7
#define GPIO15_FUN_PWM_CH0               8
#define GPIO15_FUN_UNUSED9               9
#define GPIO15_FUN_GPIP_CH_1_ATEST_OUT_1 10
#define GPIO15_FUN_REG_GPIO_15           11
#define GPIO15_FUN_RF_TEST_10            12
#define GPIO15_FUN_SCAN_OUT_1            13
#define GPIO15_FUN_E21_TDO_E21_TDI       14
#define GPIO15_FUN_DEBUG_11              15
#define GPIO15_FUN_FEM_GPIO_0            16
#define GPIO15_FUN_USB_TX_DN_USB_RX_DN   17
#define GPIO15_FUN_VIP                   18
#define GPIO15_FUN_UNUSED19              19
#define GPIO15_FUN_QDEC2_A               20
#define GPIO15_FUN_ROW_I_7               21
#define GPIO15_FUN_COL_O_15              22
#define GPIO15_FUN_CAM_PWRDN             23
/* GPIO16 function definition */
#define GPIO16_FUN_CLK_OUT_0             0
#define GPIO16_FUN_BT_ACTIVE             1
#define GPIO16_FUN_UNUSED2               2
#define GPIO16_FUN_I2S0_BCLK             3
#define GPIO16_FUN_SPI_0_MOSI_SPI_0_MISO 4
#define GPIO16_FUN_I2C0_SCL              6
#define GPIO16_FUN_UART_SIG0_UART_SIG4   7
#define GPIO16_FUN_PWM_CH1               8
#define GPIO16_FUN_UNUSED9               9
#define GPIO16_FUN_UNUSED10              10
#define GPIO16_FUN_REG_GPIO_16           11
#define GPIO16_FUN_RF_TEST_11            12
#define GPIO16_FUN_UNUSED13              13
#define GPIO16_FUN_E21_TMS_E21_TCK       14
#define GPIO16_FUN_DEBUG_12              15
#define GPIO16_FUN_FEM_GPIO_1            16
#define GPIO16_FUN_USB_TX_OE             17
#define GPIO16_FUN_VIM                   18
#define GPIO16_FUN_UNUSED19              19
#define GPIO16_FUN_QDEC2_B               20
#define GPIO16_FUN_ROW_I_0               21
#define GPIO16_FUN_COL_O_16              22
#define GPIO16_FUN_CAM_REF_CLK           23
/* GPIO17 function definition */
#define GPIO17_FUN_CLK_OUT_1             0
#define GPIO17_FUN_BT_PRI                1
#define GPIO17_FUN_SF_IO_0_SF2_CS2       2
#define GPIO17_FUN_I2S0_FS               3
#define GPIO17_FUN_SPI_0_MISO_SPI_0_MOSI 4
#define GPIO17_FUN_I2C0_SDA              6
#define GPIO17_FUN_UART_SIG1_UART_SIG5   7
#define GPIO17_FUN_PWM_CH2               8
#define GPIO17_FUN_PIX_DAT4              9
#define GPIO17_FUN_GPIP_CH_2_PSW_IRRCV   10
#define GPIO17_FUN_REG_GPIO_17           11
#define GPIO17_FUN_RF_TEST_12            12
#define GPIO17_FUN_SCAN_OUT_2            13
#define GPIO17_FUN_E21_TDI_E21_TDO       14
#define GPIO17_FUN_DEBUG_13              15
#define GPIO17_FUN_FEM_GPIO_2            16
#define GPIO17_FUN_USB_TX_DP_USB_RX_DP   17
#define GPIO17_FUN_RCV                   18
#define GPIO17_FUN_UNUSED19              19
#define GPIO17_FUN_QDEC2_LED             20
#define GPIO17_FUN_ROW_I_1               21
#define GPIO17_FUN_COL_O_17              22
#define GPIO17_FUN_CAM_RESET             23
/* GPIO18 function definition */
#define GPIO18_FUN_CLK_OUT_0           0
#define GPIO18_FUN_BT_ABORT            1
#define GPIO18_FUN_SF_IO_1             2
#define GPIO18_FUN_I2S0_DIO_I2S0_DO    3
#define GPIO18_FUN_SPI_0_SS            4
#define GPIO18_FUN_I2C0_SCL            6
#define GPIO18_FUN_UART_SIG2_UART_SIG6 7
#define GPIO18_FUN_PWM_CH3             8
#define GPIO18_FUN_PIX_DAT5            9
#define GPIO18_FUN_GPIP_CH_8           10
#define GPIO18_FUN_REG_GPIO_18         11
#define GPIO18_FUN_RF_TEST_13          12
#define GPIO18_FUN_UNUSED13            13
#define GPIO18_FUN_E21_TCK_E21_TMS     14
#define GPIO18_FUN_M_CCI_CLK_DEBUG_14  15
#define GPIO18_FUN_FEM_GPIO_3          16
#define GPIO18_FUN_USB_SUS_EXT         17
#define GPIO18_FUN_USB_SUS             18
#define GPIO18_FUN_RMII_MDC            19
#define GPIO18_FUN_QDEC0_A             20
#define GPIO18_FUN_ROW_I_2             21
#define GPIO18_FUN_COL_O_18            22
#define GPIO18_FUN_CAM_PWRDN           23
/* GPIO19 function definition */
#define GPIO19_FUN_CLK_OUT_1           0
#define GPIO19_FUN_BT_ACTIVE           1
#define GPIO19_FUN_SF_CS               2
#define GPIO19_FUN_I2S0_RCLK_O_I2S0_DI 3
#define GPIO19_FUN_SPI_0_SCLK          4
#define GPIO19_FUN_I2C0_SDA            6
#define GPIO19_FUN_UART_SIG3_UART_SIG7 7
#define GPIO19_FUN_PWM_CH4             8
#define GPIO19_FUN_PIX_DAT6            9
#define GPIO19_FUN_GPIP_CH_9           10
#define GPIO19_FUN_REG_GPIO_19         11
#define GPIO19_FUN_RF_TEST_14          12
#define GPIO19_FUN_UNUSED13            13
#define GPIO19_FUN_E21_TDO_E21_TDI     14
#define GPIO19_FUN_M_CCI_CS_DEBUG_15   15
#define GPIO19_FUN_FEM_GPIO_4          16
#define GPIO19_FUN_USB_ENUM_EXT        17
#define GPIO19_FUN_USB_ENUM            18
#define GPIO19_FUN_RMII_MDIO           19
#define GPIO19_FUN_QDEC0_B             20
#define GPIO19_FUN_ROW_I_3             21
#define GPIO19_FUN_COL_O_19            22
#define GPIO19_FUN_CAM_REF_CLK         23
/* GPIO20 function definition */
#define GPIO20_FUN_CLK_OUT_0             0
#define GPIO20_FUN_BT_PRI                1
#define GPIO20_FUN_SF_IO_3               2
#define GPIO20_FUN_I2S0_BCLK             3
#define GPIO20_FUN_SPI_0_MOSI_SPI_0_MISO 4
#define GPIO20_FUN_I2C0_SCL              6
#define GPIO20_FUN_UART_SIG4_UART_SIG0   7
#define GPIO20_FUN_PWM_CH0               8
#define GPIO20_FUN_PIX_DAT7              9
#define GPIO20_FUN_GPIP_CH_10            10
#define GPIO20_FUN_REG_GPIO_20           11
#define GPIO20_FUN_RF_TEST_15            12
#define GPIO20_FUN_UNUSED13              13
#define GPIO20_FUN_E21_TMS_E21_TCK       14
#define GPIO20_FUN_M_CCI_DI_DEBUG_16     15
#define GPIO20_FUN_FEM_GPIO_0            16
#define GPIO20_FUN_USB_TX_DN_USB_RX_DN   17
#define GPIO20_FUN_USB_OEB               18
#define GPIO20_FUN_RMII_RXERR            19
#define GPIO20_FUN_QDEC0_LED             20
#define GPIO20_FUN_ROW_I_4               21
#define GPIO20_FUN_COL_O_0               22
#define GPIO20_FUN_CAM_RESET             23
/* GPIO21 function definition */
#define GPIO21_FUN_CLK_OUT_1             0
#define GPIO21_FUN_BT_ABORT              1
#define GPIO21_FUN_SF_CLK                2
#define GPIO21_FUN_I2S0_FS               3
#define GPIO21_FUN_SPI_0_MISO_SPI_0_MOSI 4
#define GPIO21_FUN_I2C0_SDA              6
#define GPIO21_FUN_UART_SIG5_UART_SIG1   7
#define GPIO21_FUN_PWM_CH1               8
#define GPIO21_FUN_UNUSED9               9
#define GPIO21_FUN_GPIP_CH_11            10
#define GPIO21_FUN_REG_GPIO_21           11
#define GPIO21_FUN_RF_TEST_16            12
#define GPIO21_FUN_UNUSED13              13
#define GPIO21_FUN_E21_TDI_E21_TDO       14
#define GPIO21_FUN_M_CCI_DO_DEBUG_17     15
#define GPIO21_FUN_FEM_GPIO_1            16
#define GPIO21_FUN_USB_TX_OE             17
#define GPIO21_FUN_VOP                   18
#define GPIO21_FUN_RMII_TX_EN            19
#define GPIO21_FUN_QDEC1_A               20
#define GPIO21_FUN_ROW_I_5               21
#define GPIO21_FUN_COL_O_1               22
#define GPIO21_FUN_CAM_PWRDN             23
/* GPIO22 function definition */
#define GPIO22_FUN_CLK_OUT_0           0
#define GPIO22_FUN_BT_ACTIVE           1
#define GPIO22_FUN_SF_IO_2             2
#define GPIO22_FUN_I2S0_DIO_I2S0_DO    3
#define GPIO22_FUN_SPI_0_SS            4
#define GPIO22_FUN_I2C0_SCL            6
#define GPIO22_FUN_UART_SIG6_UART_SIG2 7
#define GPIO22_FUN_PWM_CH2             8
#define GPIO22_FUN_UNUSED9             9
#define GPIO22_FUN_LEDDRV_0            10
#define GPIO22_FUN_REG_GPIO_22         11
#define GPIO22_FUN_RF_TEST_17          12
#define GPIO22_FUN_UNUSED13            13
#define GPIO22_FUN_E21_TCK_E21_TMS     14
#define GPIO22_FUN_DEBUG_18            15
#define GPIO22_FUN_FEM_GPIO_2          16
#define GPIO22_FUN_USB_TX_DP_USB_RX_DP 17
#define GPIO22_FUN_VOM                 18
#define GPIO22_FUN_RMII_RX_DV          19
#define GPIO22_FUN_QDEC1_B             20
#define GPIO22_FUN_ROW_I_6             21
#define GPIO22_FUN_COL_O_2             22
#define GPIO22_FUN_CAM_REF_CLK         23
/* GPIO23 function definition */
#define GPIO23_FUN_CLK_OUT_1                 0
#define GPIO23_FUN_BT_PRI                    1
#define GPIO23_FUN_SF2_IO_2_SF3_CS2          2
#define GPIO23_FUN_I2S0_RCLK_O_I2S0_DI       3
#define GPIO23_FUN_SPI_0_SCLK                4
#define GPIO23_FUN_I2C0_SDA                  6
#define GPIO23_FUN_UART_SIG7_UART_SIG3       7
#define GPIO23_FUN_PWM_CH3                   8
#define GPIO23_FUN_PIX_DAT4                  9
#define GPIO23_FUN_LEDDRV_1_FLASH_PULL_OUT_0 10
#define GPIO23_FUN_REG_GPIO_23               11
#define GPIO23_FUN_RF_TEST_18                12
#define GPIO23_FUN_UNUSED13                  13
#define GPIO23_FUN_E21_TDO_E21_TDI           14
#define GPIO23_FUN_DEBUG_19                  15
#define GPIO23_FUN_FEM_GPIO_3                16
#define GPIO23_FUN_USB_SUS_EXT               17
#define GPIO23_FUN_BD                        18
#define GPIO23_FUN_UNUSED19                  19
#define GPIO23_FUN_QDEC1_LED                 20
#define GPIO23_FUN_ROW_I_7                   21
#define GPIO23_FUN_COL_O_3                   22
#define GPIO23_FUN_CAM_RESET                 23
/* GPIO24 function definition */
#define GPIO24_FUN_CLK_OUT_0             0
#define GPIO24_FUN_BT_ABORT              1
#define GPIO24_FUN_SF2_IO_1              2
#define GPIO24_FUN_I2S0_BCLK             3
#define GPIO24_FUN_SPI_0_MOSI_SPI_0_MISO 4
#define GPIO24_FUN_I2C0_SCL              6
#define GPIO24_FUN_UART_SIG0_UART_SIG4   7
#define GPIO24_FUN_PWM_CH4               8
#define GPIO24_FUN_PIX_DAT5              9
#define GPIO24_FUN_FLASH_PULL_OUT_1      10
#define GPIO24_FUN_REG_GPIO_24           11
#define GPIO24_FUN_RF_TEST_19            12
#define GPIO24_FUN_UNUSED13              13
#define GPIO24_FUN_E21_TMS_E21_TCK       14
#define GPIO24_FUN_DEBUG_20              15
#define GPIO24_FUN_FEM_GPIO_4            16
#define GPIO24_FUN_USB_ENUM_EXT          17
#define GPIO24_FUN_VIP                   18
#define GPIO24_FUN_RMII_MDC              19
#define GPIO24_FUN_QDEC2_A               20
#define GPIO24_FUN_ROW_I_0               21
#define GPIO24_FUN_COL_O_4               22
#define GPIO24_FUN_CAM_PWRDN             23
/* GPIO25 function definition */
#define GPIO25_FUN_CLK_OUT_1             0
#define GPIO25_FUN_BT_ACTIVE             1
#define GPIO25_FUN_SF2_CS                2
#define GPIO25_FUN_I2S0_FS               3
#define GPIO25_FUN_SPI_0_MISO_SPI_0_MOSI 4
#define GPIO25_FUN_I2C0_SDA              6
#define GPIO25_FUN_UART_SIG1_UART_SIG5   7
#define GPIO25_FUN_PWM_CH0               8
#define GPIO25_FUN_PIX_DAT6              9
#define GPIO25_FUN_FLASH_PULL_OUT_2      10
#define GPIO25_FUN_REG_GPIO_25           11
#define GPIO25_FUN_RF_TEST_20            12
#define GPIO25_FUN_UNUSED13              13
#define GPIO25_FUN_E21_TDI_E21_TDO       14
#define GPIO25_FUN_DEBUG_21              15
#define GPIO25_FUN_FEM_GPIO_0            16
#define GPIO25_FUN_USB_TX_DN_USB_RX_DN   17
#define GPIO25_FUN_VIM                   18
#define GPIO25_FUN_RMII_MDIO             19
#define GPIO25_FUN_QDEC2_B               20
#define GPIO25_FUN_ROW_I_1               21
#define GPIO25_FUN_COL_O_5               22
#define GPIO25_FUN_CAM_REF_CLK           23
/* GPIO26 function definition */
#define GPIO26_FUN_CLK_OUT_0           0
#define GPIO26_FUN_BT_PRI              1
#define GPIO26_FUN_SF2_IO_3            2
#define GPIO26_FUN_I2S0_DIO_I2S0_DO    3
#define GPIO26_FUN_SPI_0_SS            4
#define GPIO26_FUN_I2C0_SCL            6
#define GPIO26_FUN_UART_SIG2_UART_SIG6 7
#define GPIO26_FUN_PWM_CH1             8
#define GPIO26_FUN_PIX_DAT7            9
#define GPIO26_FUN_FLASH_PULL_OUT_3    10
#define GPIO26_FUN_REG_GPIO_26         11
#define GPIO26_FUN_RF_TEST_21          12
#define GPIO26_FUN_UNUSED13            13
#define GPIO26_FUN_E21_TCK_E21_TMS     14
#define GPIO26_FUN_DEBUG_22            15
#define GPIO26_FUN_FEM_GPIO_1          16
#define GPIO26_FUN_USB_TX_OE           17
#define GPIO26_FUN_RCV                 18
#define GPIO26_FUN_RMII_RXERR          19
#define GPIO26_FUN_QDEC2_LED           20
#define GPIO26_FUN_ROW_I_2             21
#define GPIO26_FUN_COL_O_6             22
#define GPIO26_FUN_CAM_RESET           23
/* GPIO27 function definition */
#define GPIO27_FUN_CLK_OUT_1           0
#define GPIO27_FUN_BT_ABORT            1
#define GPIO27_FUN_SF2_CLK             2
#define GPIO27_FUN_I2S0_RCLK_O_I2S0_DI 3
#define GPIO27_FUN_SPI_0_SCLK          4
#define GPIO27_FUN_I2C0_SDA            6
#define GPIO27_FUN_UART_SIG3_UART_SIG7 7
#define GPIO27_FUN_PWM_CH2             8
#define GPIO27_FUN_UNUSED9             9
#define GPIO27_FUN_FLASH_PULL_OUT_4    10
#define GPIO27_FUN_REG_GPIO_27         11
#define GPIO27_FUN_RF_TEST_22          12
#define GPIO27_FUN_UNUSED13            13
#define GPIO27_FUN_E21_TDO_E21_TDI     14
#define GPIO27_FUN_DEBUG_23            15
#define GPIO27_FUN_FEM_GPIO_2          16
#define GPIO27_FUN_USB_TX_DP_USB_RX_DP 17
#define GPIO27_FUN_USB_SUS             18
#define GPIO27_FUN_RMII_TX_EN          19
#define GPIO27_FUN_QDEC0_A             20
#define GPIO27_FUN_ROW_I_3             21
#define GPIO27_FUN_COL_O_7             22
#define GPIO27_FUN_CAM_PWRDN           23
/* GPIO28 function definition */
#define GPIO28_FUN_CLK_OUT_0             0
#define GPIO28_FUN_BT_ACTIVE             1
#define GPIO28_FUN_SF2_IO_0              2
#define GPIO28_FUN_I2S0_BCLK             3
#define GPIO28_FUN_SPI_0_MOSI_SPI_0_MISO 4
#define GPIO28_FUN_I2C0_SCL              6
#define GPIO28_FUN_UART_SIG4_UART_SIG0   7
#define GPIO28_FUN_PWM_CH3               8
#define GPIO28_FUN_PIX_DAT4              9
#define GPIO28_FUN_FLASH_PULL_OUT_5      10
#define GPIO28_FUN_REG_GPIO_28           11
#define GPIO28_FUN_RF_TEST_23            12
#define GPIO28_FUN_UNUSED13              13
#define GPIO28_FUN_E21_TMS_E21_TCK       14
#define GPIO28_FUN_DEBUG_24              15
#define GPIO28_FUN_FEM_GPIO_3            16
#define GPIO28_FUN_USB_SUS_EXT           17
#define GPIO28_FUN_USB_ENUM              18
#define GPIO28_FUN_RMII_RX_DV            19
#define GPIO28_FUN_QDEC0_B               20
#define GPIO28_FUN_ROW_I_4               21
#define GPIO28_FUN_COL_O_8               22
#define GPIO28_FUN_CAM_REF_CLK           23
/* GPIO29 function definition */
#define GPIO29_FUN_CLK_OUT_1             0
#define GPIO29_FUN_BT_PRI                1
#define GPIO29_FUN_UNUSED2               2
#define GPIO29_FUN_I2S0_FS               3
#define GPIO29_FUN_SPI_0_MISO_SPI_0_MOSI 4
#define GPIO29_FUN_I2C0_SDA              6
#define GPIO29_FUN_UART_SIG5_UART_SIG1   7
#define GPIO29_FUN_PWM_CH4               8
#define GPIO29_FUN_PIX_DAT5              9
#define GPIO29_FUN_UNUSED10              10
#define GPIO29_FUN_REG_GPIO_29           11
#define GPIO29_FUN_RF_TEST_24            12
#define GPIO29_FUN_UNUSED13              13
#define GPIO29_FUN_E21_TDI_E21_TDO       14
#define GPIO29_FUN_DEBUG_25              15
#define GPIO29_FUN_FEM_GPIO_4            16
#define GPIO29_FUN_USB_ENUM_EXT          17
#define GPIO29_FUN_USB_OEB               18
#define GPIO29_FUN_UNUSED19              19
#define GPIO29_FUN_QDEC0_LED             20
#define GPIO29_FUN_ROW_I_5               21
#define GPIO29_FUN_COL_O_9               22
#define GPIO29_FUN_CAM_RESET             23
/* GPIO30 function definition */
#define GPIO30_FUN_CLK_OUT_0           0
#define GPIO30_FUN_BT_ABORT            1
#define GPIO30_FUN_UNUSED2             2
#define GPIO30_FUN_I2S0_DIO_I2S0_DO    3
#define GPIO30_FUN_SPI_0_SS            4
#define GPIO30_FUN_I2C0_SCL            6
#define GPIO30_FUN_UART_SIG6_UART_SIG2 7
#define GPIO30_FUN_PWM_CH0             8
#define GPIO30_FUN_PIX_DAT6            9
#define GPIO30_FUN_UNUSED10            10
#define GPIO30_FUN_REG_GPIO_30         11
#define GPIO30_FUN_RF_TEST_25          12
#define GPIO30_FUN_UNUSED13            13
#define GPIO30_FUN_E21_TCK_E21_TMS     14
#define GPIO30_FUN_DEBUG_26            15
#define GPIO30_FUN_FEM_GPIO_0          16
#define GPIO30_FUN_USB_TX_DN_USB_RX_DN 17
#define GPIO30_FUN_VOP                 18
#define GPIO30_FUN_UNUSED19            19
#define GPIO30_FUN_QDEC1_A             20
#define GPIO30_FUN_ROW_I_6             21
#define GPIO30_FUN_COL_O_10            22
#define GPIO30_FUN_CAM_PWRDN           23
/* GPIO31 function definition */
#define GPIO31_FUN_CLK_OUT_1           0
#define GPIO31_FUN_BT_ACTIVE           1
#define GPIO31_FUN_UNUSED2             2
#define GPIO31_FUN_I2S0_RCLK_O_I2S0_DI 3
#define GPIO31_FUN_SPI_0_SCLK          4
#define GPIO31_FUN_I2C0_SDA            6
#define GPIO31_FUN_UART_SIG7_UART_SIG3 7
#define GPIO31_FUN_PWM_CH1             8
#define GPIO31_FUN_PIX_DAT7            9
#define GPIO31_FUN_UNUSED10            10
#define GPIO31_FUN_REG_GPIO_31         11
#define GPIO31_FUN_RF_TEST_26          12
#define GPIO31_FUN_UNUSED13            13
#define GPIO31_FUN_E21_TDO_E21_TDI     14
#define GPIO31_FUN_DEBUG_27            15
#define GPIO31_FUN_FEM_GPIO_1          16
#define GPIO31_FUN_USB_TX_OE           17
#define GPIO31_FUN_VOM                 18
#define GPIO31_FUN_UNUSED19            19
#define GPIO31_FUN_QDEC1_B             20
#define GPIO31_FUN_ROW_I_7             21
#define GPIO31_FUN_COL_O_11            22
#define GPIO31_FUN_CAM_REF_CLK         23


#endif /*__BL702_GPIO_H__ */
