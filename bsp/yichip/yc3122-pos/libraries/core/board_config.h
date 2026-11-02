/*
 * Copyright (c) 2006-2020, YICHIP Development Team
 * @file     yc_board_config.h
 * @brief    source file for setting board_config
 *
 * Change Logs:
 * Date           Author             Version        Notes
 * 2020-11-05     wushengyan         V1.0.0         the first version
 */

#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

#include "yc3122.h"
#include "yc_gpio.h"

/*鏉垮瓙绫诲瀷*/
#define FPGA_BOARD  (1)
#define EVB_BOARD   (2)
#define APP_BOARD   (3)
#define APP_88PIN_BOARD (4)

#define APP_YC3158AB_BOARD (6)
#define APP_YC3163AB_BOARD (7)
#define APP_YC3164AB_BOARD (8)
#define APP_YC3165AB_BOARD (9)
#define APP_YC3154AB_BOARD (10)

#define APP_194_YC3173AB_DOORLOCK_V1_0_BOARD (80)

#ifndef BOARD_TYPE
#define BOARD_TYPE  APP_YC3165AB_BOARD
#endif

/*General function define*/
#define GPIO_Group_To_GroupIn(Group)  ((((uint32_t)Group - GPIO_BASEADDR)/8) + (uint32_t)GPIO_IN_BASE)//((uint32_t*)GPIO_EN_BASE + (uint32_t *)(((uint32_t*)Group - (uint32_t*)GPIO_BASEADDR) & 0xff)/8)
#define GPIO_Pin_To_PinIn(Pin)        (1 << Pin)

#if (BOARD_TYPE == FPGA_BOARD)

/*function define*/
#define FPGA_reg_write(addr,wdata)  {*((volatile uint8_t*)(0xf856d)) = addr;\
                                     *((volatile uint8_t*)(0xf856e)) = wdata;\
                                     *((volatile uint8_t*)(0xf856c)) = 0x00;\
                                     *((volatile uint8_t*)(0xf856c)) = 0x02;\
                                     *((volatile uint8_t*)(0xf856c)) = 0x00;}

#define FPGA_reg_read(addr)         {*((volatile uint8_t*)(0xf856d)) = addr;\
                                     *((volatile uint8_t*)(0xf856c)) = 0x00;\
                                     *((volatile uint8_t*)(0xf856c)) = 0x01;\
                                     *((volatile uint8_t*)(0xf856c)) = 0x00;\
                                     (*((volatile uint8_t*)(0xf856f)));}

/*Print Port*/

//uart0
#define PRINTPORT           MUART0
#define PRINT_BAUD          (115200)
#define PRINTRX_PORT        GPIOB
#define PRINTRX_IO_PIN      GPIO_Pin_0
#define PRINTTX_PORT        GPIOB
#define PRINTTX_IO_PIN      GPIO_Pin_1
#define PRINTRTS_PORT       GPIOB
#define PRINTRTS_IO_PIN     GPIO_Pin_2
#define PRINTCTS_PORT       GPIOB
#define PRINTCTS_IO_PIN     GPIO_Pin_3

//uart1
#define UART1PORT           MUART1
#define UART1_BAUD          (115200)
#define UART1RX_PORT        GPIOB
#define UART1RX_IO_PIN      GPIO_Pin_0
#define UART1TX_PORT        GPIOB
#define UART1TX_IO_PIN      GPIO_Pin_1
#define UART1RTS_PORT       GPIOB
#define UART1RTS_IO_PIN     GPIO_Pin_2
#define UART1CTS_PORT       GPIOB
#define UART1CTS_IO_PIN     GPIO_Pin_3

//uart2
#define UART2PORT           MUART2
#define UART2_BAUD          (115200)
#define UART2RX_PORT        GPIOC
#define UART2RX_IO_PIN      GPIO_Pin_6
#define UART2TX_PORT        GPIOC
#define UART2TX_IO_PIN      GPIO_Pin_5
#define UART2RTS_PORT       GPIOD
#define UART2RTS_IO_PIN     GPIO_Pin_0
#define UART2CTS_PORT       GPIOD
#define UART2CTS_IO_PIN     GPIO_Pin_1

//uart3
#define UART3PORT           MUART3
#define UART3_BAUD          (115200)
#define UART3RX_PORT        GPIOC
#define UART3RX_IO_PIN      GPIO_Pin_14
#define UART3TX_PORT        GPIOC
#define UART3TX_IO_PIN      GPIO_Pin_13
#define UART3RTS_PORT       GPIOC
#define UART3RTS_IO_PIN     GPIO_Pin_15
#define UART3CTS_PORT       GPIOC
#define UART3CTS_IO_PIN     GPIO_Pin_12

//i2c0
#define I2C0PORT            MI2C0
#define I2C0SCL_PORT        GPIOB
#define I2C0SCL_IO_PIN      GPIO_Pin_2
#define I2C0SDA_PORT        GPIOB
#define I2C0SDA_IO_PIN      GPIO_Pin_3

//i2c1
#define I2C1PORT            MI2C1
#define I2C1SCL_PORT        GPIOB
#define I2C1SCL_IO_PIN      GPIO_Pin_4
#define I2C1SDA_PORT        GPIOB
#define I2C1SDA_IO_PIN      GPIO_Pin_5

//spi0
#define SPI0PORT            MSPI0
#define SPI0NCS_PORT        GPIOD
#define SPI0NCS_IO_PIN      GPIO_Pin_12
#define SPI04MNCS_PORT      GPIOD
#define SPI04MNCS_IO_PIN    GPIO_Pin_12
#define SPI016MNCS_PORT     GPIOD
#define SPI016MNCS_IO_PIN   GPIO_Pin_13
#define SPI0SCK_PORT        GPIOA
#define SPI0SCK_IO_PIN      GPIO_Pin_11
#define SPI0MOSI_PORT       GPIOA
#define SPI0MOSI_IO_PIN     GPIO_Pin_12
#define SPI0MISO_PORT       GPIOA
#define SPI0MISO_IO_PIN     GPIO_Pin_13

//spi1
#define SPI1PORT            MSPI1
#define SPI1NCS_PORT        GPIOC
#define SPI1NCS_IO_PIN      GPIO_Pin_8
#define SPI14MNCS_PORT      GPIOC
#define SPI14MNCS_IO_PIN    GPIO_Pin_8
#define SPI116MNCS_PORT     GPIOC
#define SPI116MNCS_IO_PIN   GPIO_Pin_8
#define SPI1SCK_PORT        GPIOC
#define SPI1SCK_IO_PIN      GPIO_Pin_9
#define SPI1MOSI_PORT       GPIOC
#define SPI1MOSI_IO_PIN     GPIO_Pin_10
#define SPI1MISO_PORT       GPIOC
#define SPI1MISO_IO_PIN     GPIO_Pin_6

//tft
#define ST7789CS_PORT       GPIOD
#define ST7789CS_IO_PIN     GPIO_Pin_15
#define ST7789RST_PORT      GPIOE
#define ST7789RST_IO_PIN    GPIO_Pin_1
#define ST7789A0_PORT       GPIOE
#define ST7789A0_IO_PIN     GPIO_Pin_2
#define ST7789BL_PORT       GPIOE
#define ST7789BL_IO_PIN     GPIO_Pin_9
#define ST7789SCK_PORT      GPIOA
#define ST7789SCK_IO_PIN    GPIO_Pin_11
#define ST7789MOSI_PORT     GPIOA
#define ST7789MOSI_IO_PIN   GPIO_Pin_12
#define ST7789MISO_PORT     GPIOA
#define ST7789MISO_IO_PIN   GPIO_Pin_13

//lcd
#define ST7539CS_PORT  	    GPIOB
#define ST7539CS_IO_PIN   	GPIO_Pin_15
#define ST7539RST_PORT 	    GPIOB
#define ST7539RST_IO_PIN  	GPIO_Pin_2
#define ST7539A0_PORT  	    GPIOB
#define ST7539A0_IO_PIN   	GPIO_Pin_0
#define ST7539BL_PORT  	    GPIOC
#define ST7539BL_IO_PIN   	GPIO_Pin_2
#define ST7539SCK_PORT      GPIOB
#define ST7539SCK_IO_PIN    GPIO_Pin_1
#define ST7539MOSI_PORT     GPIOA
#define ST7539MOSI_IO_PIN   GPIO_Pin_15
#define ST7539MISO_PORT     GPIOA
#define ST7539MISO_IO_PIN   GPIO_Pin_14

//16Mflash
#define FLASH16M_NCS_PORT     GPIOD
#define FLASH16M_NCS_IO_PIN   GPIO_Pin_13
#define FLASH16M_SCK_PORT     GPIOC
#define FLASH16M_SCK_IO_PIN   GPIO_Pin_6
#define FLASH16M_MOSI_PORT    GPIOC
#define FLASH16M_MOSI_IO_PIN  GPIO_Pin_7
#define FLASH16M_MISO_PORT    GPIOC
#define FLASH16M_MISO_IO_PIN  GPIO_Pin_8

#define FLASH4M_NCS_PORT      GPIOD
#define FLASH4M_NCS_IO_PIN    GPIO_Pin_12
#define FLASH4M_SCK_PORT      GPIOC
#define FLASH4M_SCK_IO_PIN    GPIO_Pin_6
#define FLASH4M_MOSI_PORT     GPIOC
#define FLASH4M_MOSI_IO_PIN   GPIO_Pin_7
#define FLASH4M_MISO_PORT     GPIOC
#define FLASH4M_MISO_IO_PIN   GPIO_Pin_8

//pwm
#define PWM0_PORT  	        GPIOB
#define PWM0_IO_PIN   	    GPIO_Pin_8
#define PWM1_PORT 	        GPIOB
#define PWM1_IO_PIN  	    GPIO_Pin_9
#define PWM2_PORT  	        GPIOB
#define PWM2_IO_PIN   	    GPIO_Pin_10
#define PWM3_PORT  	        GPIOB
#define PWM3_IO_PIN   	    GPIO_Pin_11
#define PWM4_PORT  	        GPIOB
#define PWM4_IO_PIN   	    GPIO_Pin_12
#define PWM5_PORT 	        GPIOB
#define PWM5_IO_PIN  	    GPIO_Pin_13
#define PWM6_PORT  	        GPIOB
#define PWM6_IO_PIN   	    GPIO_Pin_14
#define PWM7_PORT  	        GPIOB
#define PWM7_IO_PIN   	    GPIO_Pin_15
#define PWM8_PORT  	        GPIOD
#define PWM8_IO_PIN   	    GPIO_Pin_2

//chgr_event // j6(0308 camera)
#define CHGR_VBAT_OV_FLAG_PORT  	        GPIOE //D2
#define CHGR_VBAT_OV_FLAG_IO_PIN   	        GPIO_Pin_8
#define CHGR_IN_DET_AON_PORT 	            GPIOE //D1
#define CHGR_IN_DET_AON_IO_PIN  	        GPIO_Pin_7
#define CHGR_CC_OV_CV_PORT  	            GPIOE //D3
#define CHGR_CC_OV_CV_IO_PIN   	            GPIO_Pin_9
#define CHGR_DPPM_OV_CC_PORT  	            GPIOE //D0
#define CHGR_DPPM_OV_CC_IO_PIN   	        GPIO_Pin_6
#define CHGR_DPPM_OV_CV_PORT  	            GPIOE //D4
#define CHGR_DPPM_OV_CV_IO_PIN   	        GPIO_Pin_10
#define CHGR_PGOOD_PORT 	                GPIOE //pclk
#define CHGR_PGOOD_IO_PIN  	                GPIO_Pin_0
#define CHGR_UVLO_OK_AON_PORT  	            GPIOE //D5
#define CHGR_UVLO_OK_AON_IO_PIN   	        GPIO_Pin_11
#define CHGR_RESET_PORT  	                GPIOE //D6
#define CHGR_RESET_IO_PIN   	            GPIO_Pin_12
#define CHGR_STSTE_ICHG_PORT  	            GPIOE //mclk
#define CHGR_STSTE_ICHG_IO_PIN   	        GPIO_Pin_4
#define CHGR_STATE_IND_PORT  	            GPIOE //D7
#define CHGR_STATE_IND_IO_PIN   	        GPIO_Pin_13
#define CHGR_STSTE_RCH_EN_PORT  	        GPIOE //hsync
#define CHGR_STSTE_RCH_EN_IO_PIN   	        GPIO_Pin_2
#define CHGR_STSTE_VBAT_LV_PORT  	        GPIOE //stb
#define CHGR_STSTE_VBAT_LV_IO_PIN   	    GPIO_Pin_3

//sci7816
#define SCI7816_RESET_PORT                  GPIOE
#define SCI7816_RESET_IO_PIN                GPIO_Pin_14
#define SCI7816_CLK_PORT                    GPIOE
#define SCI7816_CLK_IO_PIN                  GPIO_Pin_13
#define SCI7816_DATA_PORT                   GPIOE
#define SCI7816_DATA_IO_PIN                 GPIO_Pin_15
#define SCI7816_VCARD_PORT                  GPIOA
#define SCI7816_VCARD_IO_PIN                GPIO_Pin_1
#define SCI7816_DETECT_PORT                 GPIOE
#define SCI7816_DETECT_IO_PIN               GPIO_Pin_12

//dcmi
#define DCMI_LCD_RST_PIN                    (65)
#define DCMI_LCD_CS_PIN                     (63)
#define DCMI_LCD_CLK_PIN                    (11)
#define DCMI_LCD_MOSI_PIN                   (12)
#define DCMI_LCD_MISO_PIN                   (13)
#define DCMI_LCD_A0_PIN                     (66)
#define DCMI_LCD_BL_PIN                     (73)

#define DCMI_CAMERA_SDA_PIN                 (19)
#define DCMI_CAMERA_SCL_PIN                 (18)
#define DCMI_CAMERA_RST_PIN                 (31)
#define DCMI_CAMERA_PWDN_PIN                (36)
#define DCMI_CAMERA_MCLK_PIN                (30)
#define DCMI_CAMERA_PCLK_PIN                (32)
#define DCMI_CAMERA_VSYNC_PIN               (34)
#define DCMI_CAMERA_HSYNC_PIN               (33)
#define DCMI_CAMERA_DATA_WIDTH              (8)
#define DCMI_CAMERA_DATA0_PIN               (48)
#define DCMI_CAMERA_DATA1_PIN               (47)
#define DCMI_CAMERA_DATA2_PIN               (46)
#define DCMI_CAMERA_DATA3_PIN               (45)
#define DCMI_CAMERA_DATA4_PIN               (44)
#define DCMI_CAMERA_DATA5_PIN               (43)
#define DCMI_CAMERA_DATA6_PIN               (42)
#define DCMI_CAMERA_DATA7_PIN               (41)

//fpc1020
#define FPC1020_SPI0_PORT 	    GPIOA
#define FPC1020_SPI0_CS_PIN 	GPIO_Pin_5
#define FPC1020_SPI0_SCLK_PIN 	GPIO_Pin_6
#define FPC1020_SPI0_MOSI_PIN 	GPIO_Pin_7
#define FPC1020_SPI0_MISO_PIN 	GPIO_Pin_8
#define FPC1020_RST_PIN 	    GPIO_Pin_9
#define FPC1020_IRQ_PIN 	    GPIO_Pin_10

#elif (BOARD_TYPE == APP_BOARD)
/*Print Port*/

//uart0
#define PRINTPORT           MUART0
#define PRINT_BAUD          (115200)
#define PRINTRX_PORT        GPIOD
#define PRINTRX_IO_PIN      GPIO_Pin_6
#define PRINTTX_PORT        GPIOD
#define PRINTTX_IO_PIN      GPIO_Pin_5
#define PRINTRTS_PORT       GPIOB
#define PRINTRTS_IO_PIN     GPIO_Pin_2
#define PRINTCTS_PORT       GPIOB
#define PRINTCTS_IO_PIN     GPIO_Pin_3

//uart1
#define UART1PORT           MUART1
#define UART1_BAUD          (115200)
#define UART1RX_PORT        GPIOB
#define UART1RX_IO_PIN      GPIO_Pin_0
#define UART1TX_PORT        GPIOB
#define UART1TX_IO_PIN      GPIO_Pin_1
#define UART1RTS_PORT       GPIOB
#define UART1RTS_IO_PIN     GPIO_Pin_2
#define UART1CTS_PORT       GPIOB
#define UART1CTS_IO_PIN     GPIO_Pin_3
//spi0
#define SPI0PORT            MSPI0
#define SPI0NCS_PORT        GPIOB
#define SPI0NCS_IO_PIN      GPIO_Pin_15
#define SPI04MNCS_PORT      GPIOD
#define SPI04MNCS_IO_PIN    GPIO_Pin_12
#define SPI016MNCS_PORT     GPIOD
#define SPI016MNCS_IO_PIN   GPIO_Pin_13
#define SPI0SCK_PORT        GPIOB
#define SPI0SCK_IO_PIN      GPIO_Pin_1
#define SPI0MOSI_PORT       GPIOA
#define SPI0MOSI_IO_PIN     GPIO_Pin_15
#define SPI0MISO_PORT       GPIOA
#define SPI0MISO_IO_PIN     GPIO_Pin_14

//spi1
#define SPI1PORT            MSPI1
#define SPI1NCS_PORT        GPIOB
#define SPI1NCS_IO_PIN      GPIO_Pin_15
#define SPI14MNCS_PORT      GPIOC
#define SPI14MNCS_IO_PIN    GPIO_Pin_8
#define SPI116MNCS_PORT     GPIOC
#define SPI116MNCS_IO_PIN   GPIO_Pin_8
#define SPI1SCK_PORT        GPIOB
#define SPI1SCK_IO_PIN      GPIO_Pin_1
#define SPI1MOSI_PORT       GPIOA
#define SPI1MOSI_IO_PIN     GPIO_Pin_15
#define SPI1MISO_PORT       GPIOA
#define SPI1MISO_IO_PIN     GPIO_Pin_14

//spi2
#define SPI2PORT            HSPI
#define SPI2NCS_PORT        GPIOB
#define SPI2NCS_IO_PIN      GPIO_Pin_15
#define SPI2SCK_PORT        GPIOB
#define SPI2SCK_IO_PIN      GPIO_Pin_1
#define SPI2MOSI_PORT       GPIOA
#define SPI2MOSI_IO_PIN     GPIO_Pin_15
#define SPI2MISO_PORT       GPIOA
#define SPI2MISO_IO_PIN     GPIO_Pin_14

//lcd
#define ST7539CS_PORT  	    GPIOD
#define ST7539CS_IO_PIN   	GPIO_Pin_15
#define ST7539RST_PORT 	    GPIOE
#define ST7539RST_IO_PIN  	GPIO_Pin_1
#define ST7539A0_PORT  	    GPIOE
#define ST7539A0_IO_PIN   	GPIO_Pin_2
#define ST7539BL_PORT  	    GPIOE
#define ST7539BL_IO_PIN   	GPIO_Pin_9
#define ST7539SCK_PORT      GPIOA
#define ST7539SCK_IO_PIN    GPIO_Pin_11
#define ST7539MOSI_PORT     GPIOA
#define ST7539MOSI_IO_PIN   GPIO_Pin_12
#define ST7539MISO_PORT     GPIOA
#define ST7539MISO_IO_PIN   GPIO_Pin_13
//tft
#define ST7789CS_PORT       GPIOB
#define ST7789CS_IO_PIN     GPIO_Pin_15
#define ST7789RST_PORT      GPIOB
#define ST7789RST_IO_PIN    GPIO_Pin_2
#define ST7789A0_PORT       GPIOB
#define ST7789A0_IO_PIN     GPIO_Pin_0
#define ST7789BL_PORT       GPIOC
#define ST7789BL_IO_PIN     GPIO_Pin_2
#define ST7789SCK_PORT      GPIOB
#define ST7789SCK_IO_PIN    GPIO_Pin_1
#define ST7789MOSI_PORT     GPIOA
#define ST7789MOSI_IO_PIN   GPIO_Pin_15
#define ST7789MISO_PORT     GPIOA
#define ST7789MISO_IO_PIN   GPIO_Pin_14

//pwm
#define PWM0_PORT  	        GPIOB
#define PWM0_IO_PIN   	    GPIO_Pin_8
#define PWM1_PORT 	        GPIOB
#define PWM1_IO_PIN  	    GPIO_Pin_9
#define PWM2_PORT  	        GPIOB
#define PWM2_IO_PIN   	    GPIO_Pin_10
#define PWM3_PORT  	        GPIOB
#define PWM3_IO_PIN   	    GPIO_Pin_11
#define PWM4_PORT  	        GPIOB
#define PWM4_IO_PIN   	    GPIO_Pin_12
#define PWM5_PORT 	        GPIOB
#define PWM5_IO_PIN  	    GPIO_Pin_13
#define PWM6_PORT  	        GPIOB
#define PWM6_IO_PIN   	    GPIO_Pin_14
#define PWM7_PORT  	        GPIOB
#define PWM7_IO_PIN   	    GPIO_Pin_15
#define PWM8_PORT  	        GPIOD
#define PWM8_IO_PIN   	    GPIO_Pin_2

//dcmi
#define DCMI_LCD_RST_PIN                    (18)
#define DCMI_LCD_CS_PIN                     (31)
#define DCMI_LCD_CLK_PIN                    (17)
#define DCMI_LCD_MOSI_PIN                   (15)
#define DCMI_LCD_MISO_PIN                   (14)
#define DCMI_LCD_A0_PIN                     (16)
#define DCMI_LCD_BL_PIN                     (34)

#define DCMI_CAMERA_SDA_PIN                 (40)
#define DCMI_CAMERA_SCL_PIN                 (39)
#define DCMI_CAMERA_RST_PIN                 (31)
#define DCMI_CAMERA_PWDN_PIN                (49)
#define DCMI_CAMERA_MCLK_PIN                (35)
#define DCMI_CAMERA_PCLK_PIN                (36)
#define DCMI_CAMERA_VSYNC_PIN               (38)
#define DCMI_CAMERA_HSYNC_PIN               (37)
#define DCMI_CAMERA_DATA_WIDTH              (8)
#define DCMI_CAMERA_DATA0_PIN               (48)
#define DCMI_CAMERA_DATA1_PIN               (47)
#define DCMI_CAMERA_DATA2_PIN               (46)
#define DCMI_CAMERA_DATA3_PIN               (45)
#define DCMI_CAMERA_DATA4_PIN               (44)
#define DCMI_CAMERA_DATA5_PIN               (43)
#define DCMI_CAMERA_DATA6_PIN               (42)
#define DCMI_CAMERA_DATA7_PIN               (41)

//fpc1020
#define FPC1020_SPI0_PORT 	    GPIOC
#define FPC1020_SPI0_CS_PIN 	GPIO_Pin_6
#define FPC1020_SPI0_SCLK_PIN 	GPIO_Pin_1
#define FPC1020_SPI0_MOSI_PIN 	GPIO_Pin_2
#define FPC1020_SPI0_MISO_PIN 	GPIO_Pin_3
#define FPC1020_RST_PIN 	    GPIO_Pin_4
#define FPC1020_IRQ_PIN 	    GPIO_Pin_5

#elif (BOARD_TYPE == APP_88PIN_BOARD)
/*Print Port*/

//uart0
#define PRINTPORT           MUART0
#define PRINT_BAUD          (921600)
#define PRINTRX_PORT        GPIOD
#define PRINTRX_IO_PIN      GPIO_Pin_6
#define PRINTTX_PORT        GPIOD
#define PRINTTX_IO_PIN      GPIO_Pin_5
#define PRINTRTS_PORT       GPIOB
#define PRINTRTS_IO_PIN     GPIO_Pin_2
#define PRINTCTS_PORT       GPIOB
#define PRINTCTS_IO_PIN     GPIO_Pin_3

//uart1
#define UART1_BAUD          (921600)
#define UART1RX_PORT        GPIOA
#define UART1RX_IO_PIN      GPIO_Pin_0
#define UART1TX_PORT        GPIOA
#define UART1TX_IO_PIN      GPIO_Pin_1

//spi0
#define SPI0PORT            MSPI0
#define SPI0NCS_PORT        GPIOB
#define SPI0NCS_IO_PIN      GPIO_Pin_15
#define SPI04MNCS_PORT      GPIOD
#define SPI04MNCS_IO_PIN    GPIO_Pin_12
#define SPI016MNCS_PORT     GPIOD
#define SPI016MNCS_IO_PIN   GPIO_Pin_13
#define SPI0SCK_PORT        GPIOB
#define SPI0SCK_IO_PIN      GPIO_Pin_1
#define SPI0MOSI_PORT       GPIOA
#define SPI0MOSI_IO_PIN     GPIO_Pin_15
#define SPI0MISO_PORT       GPIOA
#define SPI0MISO_IO_PIN     GPIO_Pin_14

//spi1
#define SPI1PORT            MSPI1
#define SPI1NCS_PORT        GPIOB
#define SPI1NCS_IO_PIN      GPIO_Pin_15
#define SPI14MNCS_PORT      GPIOC
#define SPI14MNCS_IO_PIN    GPIO_Pin_8
#define SPI116MNCS_PORT     GPIOC
#define SPI116MNCS_IO_PIN   GPIO_Pin_8
#define SPI1SCK_PORT        GPIOB
#define SPI1SCK_IO_PIN      GPIO_Pin_1
#define SPI1MOSI_PORT       GPIOA
#define SPI1MOSI_IO_PIN     GPIO_Pin_15
#define SPI1MISO_PORT       GPIOA
#define SPI1MISO_IO_PIN     GPIO_Pin_14

#define SPI2PORT            HSPI
#define SPI2NCS_PORT        GPIOB
#define SPI2NCS_IO_PIN      GPIO_Pin_15
#define SPI2SCK_PORT        GPIOB
#define SPI2SCK_IO_PIN      GPIO_Pin_1
#define SPI2MOSI_PORT       GPIOA
#define SPI2MOSI_IO_PIN     GPIO_Pin_15
#define SPI2MISO_PORT       GPIOA
#define SPI2MISO_IO_PIN     GPIO_Pin_14

//spi0_slaver
#define SPI0NCS_PORT_S        GPIOB
#define SPI0NCS_IO_PIN_S      GPIO_Pin_12
#define SPI0SCK_PORT_S        GPIOB
#define SPI0SCK_IO_PIN_S      GPIO_Pin_13
#define SPI0MOSI_PORT_S       GPIOB
#define SPI0MOSI_IO_PIN_S     GPIO_Pin_14
#define SPI0MISO_PORT_S       GPIOB
#define SPI0MISO_IO_PIN_S     GPIO_Pin_15

//spi1_master
#define SPI1NCS_PORT_M         GPIOC
#define SPI1NCS_IO_PIN_M       GPIO_Pin_1
#define SPI1SCK_PORT_M         GPIOC
#define SPI1SCK_IO_PIN_M       GPIO_Pin_2
#define SPI1MOSI_PORT_M        GPIOC
#define SPI1MOSI_IO_PIN_M      GPIO_Pin_3
#define SPI1MISO_PORT_M        GPIOC
#define SPI1MISO_IO_PIN_M      GPIO_Pin_4

//lcd
#define ST7539CS_PORT       GPIOB
#define ST7539CS_IO_PIN    GPIO_Pin_15
#define ST7539RST_PORT      GPIOB
#define ST7539RST_IO_PIN   GPIO_Pin_2
#define ST7539A0_PORT  	    GPIOB
#define ST7539A0_IO_PIN   	GPIO_Pin_0
#define ST7539BL_PORT  	    GPIOC
#define ST7539BL_IO_PIN   	GPIO_Pin_2
#define ST7539SCK_PORT      GPIOB
#define ST7539SCK_IO_PIN    GPIO_Pin_1
#define ST7539MOSI_PORT     GPIOA
#define ST7539MOSI_IO_PIN   GPIO_Pin_15
#define ST7539MISO_PORT     GPIOA
#define ST7539MISO_IO_PIN   GPIO_Pin_14

//tft
#define ST7789CS_PORT       GPIOB
#define ST7789CS_IO_PIN     GPIO_Pin_15
#define ST7789RST_PORT      GPIOB
#define ST7789RST_IO_PIN    GPIO_Pin_2
#define ST7789A0_PORT       GPIOB
#define ST7789A0_IO_PIN     GPIO_Pin_0
#define ST7789BL_PORT       GPIOC
#define ST7789BL_IO_PIN     GPIO_Pin_2
#define ST7789SCK_PORT      GPIOB
#define ST7789SCK_IO_PIN    GPIO_Pin_1
#define ST7789MOSI_PORT     GPIOA
#define ST7789MOSI_IO_PIN   GPIO_Pin_15
#define ST7789MISO_PORT     GPIOA
#define ST7789MISO_IO_PIN   GPIO_Pin_14

//pwm
#define PWM0_PORT           GPIOB
#define PWM0_IO_PIN         GPIO_Pin_8
#define PWM1_PORT           GPIOB
#define PWM1_IO_PIN         GPIO_Pin_9
#define PWM2_PORT           GPIOB
#define PWM2_IO_PIN         GPIO_Pin_10
#define PWM3_PORT           GPIOB
#define PWM3_IO_PIN         GPIO_Pin_11
#define PWM4_PORT           GPIOB
#define PWM4_IO_PIN         GPIO_Pin_12
#define PWM5_PORT           GPIOB
#define PWM5_IO_PIN         GPIO_Pin_13
#define PWM6_PORT           GPIOB
#define PWM6_IO_PIN         GPIO_Pin_14
#define PWM7_PORT           GPIOB
#define PWM7_IO_PIN         GPIO_Pin_15
#define PWM8_PORT           GPIOD
#define PWM8_IO_PIN         GPIO_Pin_2

//16MFLASH
#define FLASH16M_NCS_PORT     GPIOD
#define FLASH16M_NCS_IO_PIN   GPIO_Pin_7
#define FLASH16M_SCK_PORT     GPIOD
#define FLASH16M_SCK_IO_PIN   GPIO_Pin_11
#define FLASH16M_MOSI_PORT    GPIOD
#define FLASH16M_MOSI_IO_PIN  GPIO_Pin_12
#define FLASH16M_MISO_PORT    GPIOD
#define FLASH16M_MISO_IO_PIN  GPIO_Pin_13

//dcmi
#define DCMI_LCD_RST_PIN                    (18)
#define DCMI_LCD_CS_PIN                     (31)
#define DCMI_LCD_CLK_PIN                    (17)
#define DCMI_LCD_MOSI_PIN                   (15)
#define DCMI_LCD_MISO_PIN                   (14)
#define DCMI_LCD_A0_PIN                     (16)
#define DCMI_LCD_BL_PIN                     (34)

#define DCMI_CAMERA_SDA_PIN                 (40)
#define DCMI_CAMERA_SCL_PIN                 (39)
#define DCMI_CAMERA_RST_PIN                 (32)
#define DCMI_CAMERA_PWDN_PIN                (49)
#define DCMI_CAMERA_MCLK_PIN                (35)
#define DCMI_CAMERA_PCLK_PIN                (36)
#define DCMI_CAMERA_VSYNC_PIN               (38)
#define DCMI_CAMERA_HSYNC_PIN               (37)
#define DCMI_CAMERA_DATA_WIDTH              (8)
#define DCMI_CAMERA_DATA0_PIN               (48)
#define DCMI_CAMERA_DATA1_PIN               (47)
#define DCMI_CAMERA_DATA2_PIN               (46)
#define DCMI_CAMERA_DATA3_PIN               (45)
#define DCMI_CAMERA_DATA4_PIN               (44)
#define DCMI_CAMERA_DATA5_PIN               (43)
#define DCMI_CAMERA_DATA6_PIN               (42)
#define DCMI_CAMERA_DATA7_PIN               (41)

//psram
#define PSRAM_NCS_PIN                       (29)
#define PSRAM_SCK_PIN                       (30)
#define PSRAM_DATA0_PIN                     (28)
#define PSRAM_DATA1_PIN                     (25)
#define PSRAM_DATA2_PIN                     (26)
#define PSRAM_DATA3_PIN                     (27)

//i2c0
#define I2C0PORT            MI2C0
#define I2C0SCL_PORT        GPIOB
#define I2C0SCL_IO_PIN      GPIO_Pin_2
#define I2C0SDA_PORT        GPIOB
#define I2C0SDA_IO_PIN      GPIO_Pin_3

//i2c1
#define I2C1PORT            MI2C1
#define I2C1SCL_PORT        GPIOB
#define I2C1SCL_IO_PIN      GPIO_Pin_4
#define I2C1SDA_PORT        GPIOB
#define I2C1SDA_IO_PIN      GPIO_Pin_5

//sci7816
#define SCI7816_RESET_PORT                  GPIOE
#define SCI7816_RESET_IO_PIN                GPIO_Pin_14
#define SCI7816_CLK_PORT                    GPIOE
#define SCI7816_CLK_IO_PIN                  GPIO_Pin_13
#define SCI7816_DATA_PORT                   GPIOE
#define SCI7816_DATA_IO_PIN                 GPIO_Pin_15

#define SCI7816_VCARD_PORT                  GPIOE
#define SCI7816_VCARD_IO_PIN                GPIO_Pin_12
#define SCI7816_DETECT_PORT                 GPIOC
#define SCI7816_DETECT_IO_PIN               GPIO_Pin_1

//sci17816
#define SCI17816_RESET_PORT                  GPIOE
#define SCI17816_RESET_IO_PIN                GPIO_Pin_10
#define SCI17816_CLK_PORT                    GPIOA
#define SCI17816_CLK_IO_PIN                  GPIO_Pin_7
#define SCI17816_DATA_PORT                   GPIOA
#define SCI17816_DATA_IO_PIN                 GPIO_Pin_6
#define SCI17816_CARD1_EN_PORT               GPIOE
#define SCI17816_CARD1_EN_IO_PIN             GPIO_Pin_11

//fpc1020
#define FPC1020_PORT 	        GPIOC
#define FPC1020_CS_PIN       	GPIO_Pin_6
#define FPC1020_SCLK_PIN 	    GPIO_Pin_1
#define FPC1020_MOSI_PIN 	    GPIO_Pin_2
#define FPC1020_MISO_PIN 	    GPIO_Pin_3
#define FPC1020_RST_PIN 	    GPIO_Pin_4
#define FPC1020_IRQ_PIN 	    GPIO_Pin_5

//nfc
#define NFC_TEMER               TIM0
#define NFC_SPI                 MSPI0
#define NFC_RESET_PORT          GPIOD
#define NFC_RESET_PIN           GPIO_Pin_10
#define NFC_12MCLK_PORT         GPIOD
#define NFC_12MCLK_PIN          GPIO_Pin_2
#define NFC_SPI_CS_PORT         GPIOD
#define NFC_SPI_CS_PIN          GPIO_Pin_4
#define NFC_SPI_SCK_PORT        GPIOD
#define NFC_SPI_SCK_PIN         GPIO_Pin_11
#define NFC_SPI_MOSI_PORT       GPIOD
#define NFC_SPI_MOSI_PIN        GPIO_Pin_12
#define NFC_SPI_MISO_PORT       GPIOD
#define NFC_SPI_MISO_PIN        GPIO_Pin_13

#elif (BOARD_TYPE == APP_YC3158AB_BOARD)
/*Print Port*/

//uart0
#define PRINTPORT           MUART0
#define PRINT_BAUD          (921600)
#define PRINTRX_PORT        GPIOD
#define PRINTRX_IO_PIN      GPIO_Pin_6
#define PRINTTX_PORT        GPIOD
#define PRINTTX_IO_PIN      GPIO_Pin_5
#define PRINTRTS_PORT       GPIOB
#define PRINTRTS_IO_PIN     GPIO_Pin_2
#define PRINTCTS_PORT       GPIOB
#define PRINTCTS_IO_PIN     GPIO_Pin_3

//uart1
#define UART1_BAUD          (921600)
#define UART1RX_PORT        GPIOA
#define UART1RX_IO_PIN      GPIO_Pin_0
#define UART1TX_PORT        GPIOA
#define UART1TX_IO_PIN      GPIO_Pin_1

//spi0
#define SPI0PORT            MSPI0
#define SPI0NCS_PORT        GPIOB
#define SPI0NCS_IO_PIN      GPIO_Pin_15
#define SPI04MNCS_PORT      GPIOD
#define SPI04MNCS_IO_PIN    GPIO_Pin_12
#define SPI016MNCS_PORT     GPIOD
#define SPI016MNCS_IO_PIN   GPIO_Pin_13
#define SPI0SCK_PORT        GPIOB
#define SPI0SCK_IO_PIN      GPIO_Pin_1
#define SPI0MOSI_PORT       GPIOA
#define SPI0MOSI_IO_PIN     GPIO_Pin_15
#define SPI0MISO_PORT       GPIOA
#define SPI0MISO_IO_PIN     GPIO_Pin_14

//spi1
#define SPI1PORT            MSPI1
#define SPI1NCS_PORT        GPIOB
#define SPI1NCS_IO_PIN      GPIO_Pin_15
#define SPI14MNCS_PORT      GPIOC
#define SPI14MNCS_IO_PIN    GPIO_Pin_8
#define SPI116MNCS_PORT     GPIOC
#define SPI116MNCS_IO_PIN   GPIO_Pin_8
#define SPI1SCK_PORT        GPIOB
#define SPI1SCK_IO_PIN      GPIO_Pin_1
#define SPI1MOSI_PORT       GPIOA
#define SPI1MOSI_IO_PIN     GPIO_Pin_15
#define SPI1MISO_PORT       GPIOA
#define SPI1MISO_IO_PIN     GPIO_Pin_14

#define SPI2PORT            HSPI
#define SPI2NCS_PORT        GPIOB
#define SPI2NCS_IO_PIN      GPIO_Pin_15
#define SPI2SCK_PORT        GPIOB
#define SPI2SCK_IO_PIN      GPIO_Pin_1
#define SPI2MOSI_PORT       GPIOA
#define SPI2MOSI_IO_PIN     GPIO_Pin_15
#define SPI2MISO_PORT       GPIOA
#define SPI2MISO_IO_PIN     GPIO_Pin_14

//spi0_slaver
#define SPI0NCS_PORT_S        GPIOB
#define SPI0NCS_IO_PIN_S      GPIO_Pin_12
#define SPI0SCK_PORT_S        GPIOB
#define SPI0SCK_IO_PIN_S      GPIO_Pin_13
#define SPI0MOSI_PORT_S       GPIOB
#define SPI0MOSI_IO_PIN_S     GPIO_Pin_14
#define SPI0MISO_PORT_S       GPIOB
#define SPI0MISO_IO_PIN_S     GPIO_Pin_15

//spi1_master
#define SPI1NCS_PORT_M         GPIOC
#define SPI1NCS_IO_PIN_M       GPIO_Pin_1
#define SPI1SCK_PORT_M         GPIOC
#define SPI1SCK_IO_PIN_M       GPIO_Pin_2
#define SPI1MOSI_PORT_M        GPIOC
#define SPI1MOSI_IO_PIN_M      GPIO_Pin_3
#define SPI1MISO_PORT_M        GPIOC
#define SPI1MISO_IO_PIN_M      GPIO_Pin_4

//lcd
#define ST7539CS_PORT       GPIOB
#define ST7539CS_IO_PIN    GPIO_Pin_15
#define ST7539RST_PORT      GPIOB
#define ST7539RST_IO_PIN   GPIO_Pin_2
#define ST7539A0_PORT  	    GPIOB
#define ST7539A0_IO_PIN   	GPIO_Pin_0
#define ST7539BL_PORT  	    GPIOC
#define ST7539BL_IO_PIN   	GPIO_Pin_2
#define ST7539SCK_PORT      GPIOB
#define ST7539SCK_IO_PIN    GPIO_Pin_1
#define ST7539MOSI_PORT     GPIOA
#define ST7539MOSI_IO_PIN   GPIO_Pin_15
#define ST7539MISO_PORT     GPIOA
#define ST7539MISO_IO_PIN   GPIO_Pin_14

//tft
#define ST7789CS_PORT       GPIOB
#define ST7789CS_IO_PIN     GPIO_Pin_15
#define ST7789RST_PORT      GPIOB
#define ST7789RST_IO_PIN    GPIO_Pin_2
#define ST7789A0_PORT       GPIOB
#define ST7789A0_IO_PIN     GPIO_Pin_0
#define ST7789BL_PORT       GPIOC
#define ST7789BL_IO_PIN     GPIO_Pin_2
#define ST7789SCK_PORT      GPIOB
#define ST7789SCK_IO_PIN    GPIO_Pin_1
#define ST7789MOSI_PORT     GPIOA
#define ST7789MOSI_IO_PIN   GPIO_Pin_15
#define ST7789MISO_PORT     GPIOA
#define ST7789MISO_IO_PIN   GPIO_Pin_14

//pwm
#define PWM0_PORT           GPIOB
#define PWM0_IO_PIN         GPIO_Pin_8
#define PWM1_PORT           GPIOB
#define PWM1_IO_PIN         GPIO_Pin_9
#define PWM2_PORT           GPIOB
#define PWM2_IO_PIN         GPIO_Pin_10
#define PWM3_PORT           GPIOB
#define PWM3_IO_PIN         GPIO_Pin_11
#define PWM4_PORT           GPIOB
#define PWM4_IO_PIN         GPIO_Pin_12
#define PWM5_PORT           GPIOB
#define PWM5_IO_PIN         GPIO_Pin_13
#define PWM6_PORT           GPIOB
#define PWM6_IO_PIN         GPIO_Pin_14
#define PWM7_PORT           GPIOB
#define PWM7_IO_PIN         GPIO_Pin_15
#define PWM8_PORT           GPIOD
#define PWM8_IO_PIN         GPIO_Pin_2

//16MFLASH
#define FLASH16M_NCS_PORT     GPIOD
#define FLASH16M_NCS_IO_PIN   GPIO_Pin_7
#define FLASH16M_SCK_PORT     GPIOD
#define FLASH16M_SCK_IO_PIN   GPIO_Pin_11
#define FLASH16M_MOSI_PORT    GPIOD
#define FLASH16M_MOSI_IO_PIN  GPIO_Pin_12
#define FLASH16M_MISO_PORT    GPIOD
#define FLASH16M_MISO_IO_PIN  GPIO_Pin_13

//dcmi
#define DCMI_LCD_RST_PIN                    (18)
#define DCMI_LCD_CS_PIN                     (33)//(31)
#define DCMI_LCD_CLK_PIN                    (17)
#define DCMI_LCD_MOSI_PIN                   (15)
#define DCMI_LCD_MISO_PIN                   (14)
#define DCMI_LCD_A0_PIN                     (16)
#define DCMI_LCD_BL_PIN                     (34)

#define DCMI_CAMERA_SDA_PIN                 (40)
#define DCMI_CAMERA_SCL_PIN                 (39)
#define DCMI_CAMERA_RST_PIN                 (32)
#define DCMI_CAMERA_PWDN_PIN                (7)//(49)
#define DCMI_CAMERA_MCLK_PIN                (35)
#define DCMI_CAMERA_PCLK_PIN                (36)
#define DCMI_CAMERA_VSYNC_PIN               (38)
#define DCMI_CAMERA_HSYNC_PIN               (37)
#define DCMI_CAMERA_DATA_WIDTH              (8)
#define DCMI_CAMERA_DATA0_PIN               (48)
#define DCMI_CAMERA_DATA1_PIN               (47)
#define DCMI_CAMERA_DATA2_PIN               (46)
#define DCMI_CAMERA_DATA3_PIN               (31)//(45)
#define DCMI_CAMERA_DATA4_PIN               (58)//(44)
#define DCMI_CAMERA_DATA5_PIN               (57)//(43)
#define DCMI_CAMERA_DATA6_PIN               (42)
#define DCMI_CAMERA_DATA7_PIN               (41)

//psram
#define PSRAM_NCS_PIN                       (45)
#define PSRAM_SCK_PIN                       (44)
#define PSRAM_DATA0_PIN                     (52)
#define PSRAM_DATA1_PIN                     (49)
#define PSRAM_DATA2_PIN                     (50)
#define PSRAM_DATA3_PIN                     (43)

//i2c0
#define I2C0PORT            MI2C0
#define I2C0SCL_PORT        GPIOB
#define I2C0SCL_IO_PIN      GPIO_Pin_2
#define I2C0SDA_PORT        GPIOB
#define I2C0SDA_IO_PIN      GPIO_Pin_3

//i2c1
#define I2C1PORT            MI2C1
#define I2C1SCL_PORT        GPIOB
#define I2C1SCL_IO_PIN      GPIO_Pin_4
#define I2C1SDA_PORT        GPIOB
#define I2C1SDA_IO_PIN      GPIO_Pin_5

//sci7816
#define SCI7816_RESET_PORT                  GPIOE
#define SCI7816_RESET_IO_PIN                GPIO_Pin_14
#define SCI7816_CLK_PORT                    GPIOE
#define SCI7816_CLK_IO_PIN                  GPIO_Pin_13
#define SCI7816_DATA_PORT                   GPIOE
#define SCI7816_DATA_IO_PIN                 GPIO_Pin_15

#define SCI7816_VCARD_PORT                  GPIOE
#define SCI7816_VCARD_IO_PIN                GPIO_Pin_12
#define SCI7816_DETECT_PORT                 GPIOC
#define SCI7816_DETECT_IO_PIN               GPIO_Pin_1

//sci17816
#define SCI17816_RESET_PORT                  GPIOE
#define SCI17816_RESET_IO_PIN                GPIO_Pin_10
#define SCI17816_CLK_PORT                    GPIOA
#define SCI17816_CLK_IO_PIN                  GPIO_Pin_7
#define SCI17816_DATA_PORT                   GPIOA
#define SCI17816_DATA_IO_PIN                 GPIO_Pin_6
#define SCI17816_CARD1_EN_PORT               GPIOE
#define SCI17816_CARD1_EN_IO_PIN             GPIO_Pin_11

//fpc1020
#define FPC1020_PORT 	        GPIOC
#define FPC1020_CS_PIN       	GPIO_Pin_6
#define FPC1020_SCLK_PIN 	    GPIO_Pin_1
#define FPC1020_MOSI_PIN 	    GPIO_Pin_2
#define FPC1020_MISO_PIN 	    GPIO_Pin_3
#define FPC1020_RST_PIN 	    GPIO_Pin_4
#define FPC1020_IRQ_PIN 	    GPIO_Pin_5

//nfc
#define NFC_TEMER               TIM0
#define NFC_SPI                 MSPI0
#define NFC_RESET_PORT          GPIOD
#define NFC_RESET_PIN           GPIO_Pin_10
#define NFC_12MCLK_PORT         GPIOD
#define NFC_12MCLK_PIN          GPIO_Pin_2
#define NFC_SPI_CS_PORT         GPIOD
#define NFC_SPI_CS_PIN          GPIO_Pin_4
#define NFC_SPI_SCK_PORT        GPIOD
#define NFC_SPI_SCK_PIN         GPIO_Pin_11
#define NFC_SPI_MOSI_PORT       GPIOD
#define NFC_SPI_MOSI_PIN        GPIO_Pin_12
#define NFC_SPI_MISO_PORT       GPIOD
#define NFC_SPI_MISO_PIN        GPIO_Pin_13
#elif (BOARD_TYPE == APP_YC3163AB_BOARD)
/*Print Port*/

//uart0
#define PRINTPORT           MUART0
#define PRINT_BAUD          (921600)
#define PRINTRX_PORT        GPIOD
#define PRINTRX_IO_PIN      GPIO_Pin_6
#define PRINTTX_PORT        GPIOD
#define PRINTTX_IO_PIN      GPIO_Pin_5
#define PRINTRTS_PORT       GPIOB
#define PRINTRTS_IO_PIN     GPIO_Pin_2
#define PRINTCTS_PORT       GPIOB
#define PRINTCTS_IO_PIN     GPIO_Pin_3

//uart1
#define UART1_BAUD          (921600)
#define UART1RX_PORT        GPIOA
#define UART1RX_IO_PIN      GPIO_Pin_0
#define UART1TX_PORT        GPIOA
#define UART1TX_IO_PIN      GPIO_Pin_1

//spi0
#define SPI0PORT            MSPI0
#define SPI0NCS_PORT        GPIOB
#define SPI0NCS_IO_PIN      GPIO_Pin_15
#define SPI04MNCS_PORT      GPIOD
#define SPI04MNCS_IO_PIN    GPIO_Pin_12
#define SPI016MNCS_PORT     GPIOD
#define SPI016MNCS_IO_PIN   GPIO_Pin_13
#define SPI0SCK_PORT        GPIOB
#define SPI0SCK_IO_PIN      GPIO_Pin_1
#define SPI0MOSI_PORT       GPIOA
#define SPI0MOSI_IO_PIN     GPIO_Pin_15
#define SPI0MISO_PORT       GPIOA
#define SPI0MISO_IO_PIN     GPIO_Pin_14

//spi1
#define SPI1PORT            MSPI1
#define SPI1NCS_PORT        GPIOB
#define SPI1NCS_IO_PIN      GPIO_Pin_15
#define SPI14MNCS_PORT      GPIOC
#define SPI14MNCS_IO_PIN    GPIO_Pin_8
#define SPI116MNCS_PORT     GPIOC
#define SPI116MNCS_IO_PIN   GPIO_Pin_8
#define SPI1SCK_PORT        GPIOB
#define SPI1SCK_IO_PIN      GPIO_Pin_1
#define SPI1MOSI_PORT       GPIOA
#define SPI1MOSI_IO_PIN     GPIO_Pin_15
#define SPI1MISO_PORT       GPIOA
#define SPI1MISO_IO_PIN     GPIO_Pin_14

#define SPI2PORT            HSPI
#define SPI2NCS_PORT        GPIOB
#define SPI2NCS_IO_PIN      GPIO_Pin_15
#define SPI2SCK_PORT        GPIOB
#define SPI2SCK_IO_PIN      GPIO_Pin_1
#define SPI2MOSI_PORT       GPIOA
#define SPI2MOSI_IO_PIN     GPIO_Pin_15
#define SPI2MISO_PORT       GPIOA
#define SPI2MISO_IO_PIN     GPIO_Pin_14

//spi0_slaver
#define SPI0NCS_PORT_S        GPIOB
#define SPI0NCS_IO_PIN_S      GPIO_Pin_12
#define SPI0SCK_PORT_S        GPIOB
#define SPI0SCK_IO_PIN_S      GPIO_Pin_13
#define SPI0MOSI_PORT_S       GPIOB
#define SPI0MOSI_IO_PIN_S     GPIO_Pin_14
#define SPI0MISO_PORT_S       GPIOB
#define SPI0MISO_IO_PIN_S     GPIO_Pin_15

//spi1_master
#define SPI1NCS_PORT_M         GPIOC
#define SPI1NCS_IO_PIN_M       GPIO_Pin_1
#define SPI1SCK_PORT_M         GPIOC
#define SPI1SCK_IO_PIN_M       GPIO_Pin_2
#define SPI1MOSI_PORT_M        GPIOC
#define SPI1MOSI_IO_PIN_M      GPIO_Pin_3
#define SPI1MISO_PORT_M        GPIOC
#define SPI1MISO_IO_PIN_M      GPIO_Pin_4

//lcd
#define ST7539CS_PORT       GPIOB
#define ST7539CS_IO_PIN    GPIO_Pin_15
#define ST7539RST_PORT      GPIOB
#define ST7539RST_IO_PIN   GPIO_Pin_2
#define ST7539A0_PORT  	    GPIOB
#define ST7539A0_IO_PIN   	GPIO_Pin_0
#define ST7539BL_PORT  	    GPIOC
#define ST7539BL_IO_PIN   	GPIO_Pin_2
#define ST7539SCK_PORT      GPIOB
#define ST7539SCK_IO_PIN    GPIO_Pin_1
#define ST7539MOSI_PORT     GPIOA
#define ST7539MOSI_IO_PIN   GPIO_Pin_15
#define ST7539MISO_PORT     GPIOA
#define ST7539MISO_IO_PIN   GPIO_Pin_14

//tft
#define ST7789CS_PORT       GPIOB
#define ST7789CS_IO_PIN     GPIO_Pin_15
#define ST7789RST_PORT      GPIOB
#define ST7789RST_IO_PIN    GPIO_Pin_2
#define ST7789A0_PORT       GPIOB
#define ST7789A0_IO_PIN     GPIO_Pin_0
#define ST7789BL_PORT       GPIOC
#define ST7789BL_IO_PIN     GPIO_Pin_2
#define ST7789SCK_PORT      GPIOB
#define ST7789SCK_IO_PIN    GPIO_Pin_1
#define ST7789MOSI_PORT     GPIOA
#define ST7789MOSI_IO_PIN   GPIO_Pin_15
#define ST7789MISO_PORT     GPIOA
#define ST7789MISO_IO_PIN   GPIO_Pin_14

//pwm
#define PWM0_PORT           GPIOB
#define PWM0_IO_PIN         GPIO_Pin_8
#define PWM1_PORT           GPIOB
#define PWM1_IO_PIN         GPIO_Pin_9
#define PWM2_PORT           GPIOB
#define PWM2_IO_PIN         GPIO_Pin_10
#define PWM3_PORT           GPIOB
#define PWM3_IO_PIN         GPIO_Pin_11
#define PWM4_PORT           GPIOB
#define PWM4_IO_PIN         GPIO_Pin_12
#define PWM5_PORT           GPIOB
#define PWM5_IO_PIN         GPIO_Pin_13
#define PWM6_PORT           GPIOB
#define PWM6_IO_PIN         GPIO_Pin_14
#define PWM7_PORT           GPIOB
#define PWM7_IO_PIN         GPIO_Pin_15
#define PWM8_PORT           GPIOD
#define PWM8_IO_PIN         GPIO_Pin_2

//16MFLASH
#define FLASH16M_NCS_PORT     GPIOD
#define FLASH16M_NCS_IO_PIN   GPIO_Pin_7
#define FLASH16M_SCK_PORT     GPIOD
#define FLASH16M_SCK_IO_PIN   GPIO_Pin_11
#define FLASH16M_MOSI_PORT    GPIOD
#define FLASH16M_MOSI_IO_PIN  GPIO_Pin_12
#define FLASH16M_MISO_PORT    GPIOD
#define FLASH16M_MISO_IO_PIN  GPIO_Pin_13

//dcmi
#define DCMI_LCD_RST_PIN                    (18)
#define DCMI_LCD_CS_PIN                     (31)
#define DCMI_LCD_CLK_PIN                    (17)
#define DCMI_LCD_MOSI_PIN                   (15)
#define DCMI_LCD_MISO_PIN                   (14)
#define DCMI_LCD_A0_PIN                     (16)
#define DCMI_LCD_BL_PIN                     (34)

#define DCMI_CAMERA_SDA_PIN                 (40)
#define DCMI_CAMERA_SCL_PIN                 (39)
#define DCMI_CAMERA_RST_PIN                 (32)
#define DCMI_CAMERA_PWDN_PIN                (49)
#define DCMI_CAMERA_MCLK_PIN                (35)
#define DCMI_CAMERA_PCLK_PIN                (36)
#define DCMI_CAMERA_VSYNC_PIN               (38)
#define DCMI_CAMERA_HSYNC_PIN               (37)
#define DCMI_CAMERA_DATA_WIDTH              (8)
#define DCMI_CAMERA_DATA0_PIN               (48)
#define DCMI_CAMERA_DATA1_PIN               (47)
#define DCMI_CAMERA_DATA2_PIN               (46)
#define DCMI_CAMERA_DATA3_PIN               (45)
#define DCMI_CAMERA_DATA4_PIN               (44)
#define DCMI_CAMERA_DATA5_PIN               (43)
#define DCMI_CAMERA_DATA6_PIN               (42)
#define DCMI_CAMERA_DATA7_PIN               (41)

//psram
#define PSRAM_NCS_PIN                       (29)
#define PSRAM_SCK_PIN                       (30)
#define PSRAM_DATA0_PIN                     (28)
#define PSRAM_DATA1_PIN                     (25)
#define PSRAM_DATA2_PIN                     (26)
#define PSRAM_DATA3_PIN                     (27)

//i2c0
#define I2C0PORT            MI2C0
#define I2C0SCL_PORT        GPIOB
#define I2C0SCL_IO_PIN      GPIO_Pin_2
#define I2C0SDA_PORT        GPIOB
#define I2C0SDA_IO_PIN      GPIO_Pin_3

//i2c1
#define I2C1PORT            MI2C1
#define I2C1SCL_PORT        GPIOB
#define I2C1SCL_IO_PIN      GPIO_Pin_4
#define I2C1SDA_PORT        GPIOB
#define I2C1SDA_IO_PIN      GPIO_Pin_5

//sci7816
#define SCI7816_RESET_PORT                  GPIOE
#define SCI7816_RESET_IO_PIN                GPIO_Pin_14
#define SCI7816_CLK_PORT                    GPIOE
#define SCI7816_CLK_IO_PIN                  GPIO_Pin_13
#define SCI7816_DATA_PORT                   GPIOE
#define SCI7816_DATA_IO_PIN                 GPIO_Pin_15

#define SCI7816_VCARD_PORT                  GPIOE
#define SCI7816_VCARD_IO_PIN                GPIO_Pin_12
#define SCI7816_DETECT_PORT                 GPIOC
#define SCI7816_DETECT_IO_PIN               GPIO_Pin_1

//sci17816
#define SCI17816_RESET_PORT                  GPIOE
#define SCI17816_RESET_IO_PIN                GPIO_Pin_10
#define SCI17816_CLK_PORT                    GPIOA
#define SCI17816_CLK_IO_PIN                  GPIO_Pin_7
#define SCI17816_DATA_PORT                   GPIOA
#define SCI17816_DATA_IO_PIN                 GPIO_Pin_6
#define SCI17816_CARD1_EN_PORT               GPIOE
#define SCI17816_CARD1_EN_IO_PIN             GPIO_Pin_11

//fpc1020
#define FPC1020_PORT 	        GPIOC
#define FPC1020_CS_PIN       	GPIO_Pin_6
#define FPC1020_SCLK_PIN 	    GPIO_Pin_1
#define FPC1020_MOSI_PIN 	    GPIO_Pin_2
#define FPC1020_MISO_PIN 	    GPIO_Pin_3
#define FPC1020_RST_PIN 	    GPIO_Pin_4
#define FPC1020_IRQ_PIN 	    GPIO_Pin_5

//nfc
#define NFC_TEMER               TIM0
#define NFC_SPI                 MSPI0
#define NFC_RESET_PORT          GPIOD
#define NFC_RESET_PIN           GPIO_Pin_10
#define NFC_12MCLK_PORT         GPIOD
#define NFC_12MCLK_PIN          GPIO_Pin_2
#define NFC_SPI_CS_PORT         GPIOD
#define NFC_SPI_CS_PIN          GPIO_Pin_4
#define NFC_SPI_SCK_PORT        GPIOD
#define NFC_SPI_SCK_PIN         GPIO_Pin_11
#define NFC_SPI_MOSI_PORT       GPIOD
#define NFC_SPI_MOSI_PIN        GPIO_Pin_12
#define NFC_SPI_MISO_PORT       GPIOD
#define NFC_SPI_MISO_PIN        GPIO_Pin_13

#elif (BOARD_TYPE == APP_YC3164AB_BOARD)
/*Print Port*/

//uart0
#define PRINTPORT           MUART0
#define PRINT_BAUD          (921600)
#define PRINTRX_PORT        GPIOD
#define PRINTRX_IO_PIN      GPIO_Pin_6
#define PRINTTX_PORT        GPIOD
#define PRINTTX_IO_PIN      GPIO_Pin_5
#define PRINTRTS_PORT       GPIOB
#define PRINTRTS_IO_PIN     GPIO_Pin_2
#define PRINTCTS_PORT       GPIOB
#define PRINTCTS_IO_PIN     GPIO_Pin_3

//uart1
#define UART1_BAUD          (921600)
#define UART1RX_PORT        GPIOA
#define UART1RX_IO_PIN      GPIO_Pin_0
#define UART1TX_PORT        GPIOA
#define UART1TX_IO_PIN      GPIO_Pin_1

//spi0
#define SPI0PORT            MSPI0
#define SPI0NCS_PORT        GPIOB
#define SPI0NCS_IO_PIN      GPIO_Pin_15
#define SPI04MNCS_PORT      GPIOD
#define SPI04MNCS_IO_PIN    GPIO_Pin_12
#define SPI016MNCS_PORT     GPIOD
#define SPI016MNCS_IO_PIN   GPIO_Pin_13
#define SPI0SCK_PORT        GPIOB
#define SPI0SCK_IO_PIN      GPIO_Pin_1
#define SPI0MOSI_PORT       GPIOA
#define SPI0MOSI_IO_PIN     GPIO_Pin_15
#define SPI0MISO_PORT       GPIOA
#define SPI0MISO_IO_PIN     GPIO_Pin_14

//spi1
#define SPI1PORT            MSPI1
#define SPI1NCS_PORT        GPIOB
#define SPI1NCS_IO_PIN      GPIO_Pin_15
#define SPI14MNCS_PORT      GPIOC
#define SPI14MNCS_IO_PIN    GPIO_Pin_8
#define SPI116MNCS_PORT     GPIOC
#define SPI116MNCS_IO_PIN   GPIO_Pin_8
#define SPI1SCK_PORT        GPIOB
#define SPI1SCK_IO_PIN      GPIO_Pin_1
#define SPI1MOSI_PORT       GPIOA
#define SPI1MOSI_IO_PIN     GPIO_Pin_15
#define SPI1MISO_PORT       GPIOA
#define SPI1MISO_IO_PIN     GPIO_Pin_14

#define SPI2PORT            HSPI
#define SPI2NCS_PORT        GPIOB
#define SPI2NCS_IO_PIN      GPIO_Pin_15
#define SPI2SCK_PORT        GPIOB
#define SPI2SCK_IO_PIN      GPIO_Pin_1
#define SPI2MOSI_PORT       GPIOA
#define SPI2MOSI_IO_PIN     GPIO_Pin_15
#define SPI2MISO_PORT       GPIOA
#define SPI2MISO_IO_PIN     GPIO_Pin_14

//spi0_slaver
#define SPI0NCS_PORT_S        GPIOB
#define SPI0NCS_IO_PIN_S      GPIO_Pin_12
#define SPI0SCK_PORT_S        GPIOB
#define SPI0SCK_IO_PIN_S      GPIO_Pin_13
#define SPI0MOSI_PORT_S       GPIOB
#define SPI0MOSI_IO_PIN_S     GPIO_Pin_14
#define SPI0MISO_PORT_S       GPIOB
#define SPI0MISO_IO_PIN_S     GPIO_Pin_15

//spi1_master
#define SPI1NCS_PORT_M         GPIOC
#define SPI1NCS_IO_PIN_M       GPIO_Pin_1
#define SPI1SCK_PORT_M         GPIOC
#define SPI1SCK_IO_PIN_M       GPIO_Pin_2
#define SPI1MOSI_PORT_M        GPIOC
#define SPI1MOSI_IO_PIN_M      GPIO_Pin_3
#define SPI1MISO_PORT_M        GPIOC
#define SPI1MISO_IO_PIN_M      GPIO_Pin_4

//lcd
#define ST7539CS_PORT       GPIOB
#define ST7539CS_IO_PIN    GPIO_Pin_15
#define ST7539RST_PORT      GPIOB
#define ST7539RST_IO_PIN   GPIO_Pin_2
#define ST7539A0_PORT  	    GPIOB
#define ST7539A0_IO_PIN   	GPIO_Pin_0
#define ST7539BL_PORT  	    GPIOC
#define ST7539BL_IO_PIN   	GPIO_Pin_2
#define ST7539SCK_PORT      GPIOB
#define ST7539SCK_IO_PIN    GPIO_Pin_1
#define ST7539MOSI_PORT     GPIOA
#define ST7539MOSI_IO_PIN   GPIO_Pin_15
#define ST7539MISO_PORT     GPIOA
#define ST7539MISO_IO_PIN   GPIO_Pin_14

//tft
#define ST7789CS_PORT       GPIOB
#define ST7789CS_IO_PIN     GPIO_Pin_15
#define ST7789RST_PORT      GPIOB
#define ST7789RST_IO_PIN    GPIO_Pin_2
#define ST7789A0_PORT       GPIOB
#define ST7789A0_IO_PIN     GPIO_Pin_0
#define ST7789BL_PORT       GPIOC
#define ST7789BL_IO_PIN     GPIO_Pin_2
#define ST7789SCK_PORT      GPIOB
#define ST7789SCK_IO_PIN    GPIO_Pin_1
#define ST7789MOSI_PORT     GPIOA
#define ST7789MOSI_IO_PIN   GPIO_Pin_15
#define ST7789MISO_PORT     GPIOA
#define ST7789MISO_IO_PIN   GPIO_Pin_14

//pwm
#define PWM0_PORT           GPIOB
#define PWM0_IO_PIN         GPIO_Pin_8
#define PWM1_PORT           GPIOB
#define PWM1_IO_PIN         GPIO_Pin_9
#define PWM2_PORT           GPIOB
#define PWM2_IO_PIN         GPIO_Pin_10
#define PWM3_PORT           GPIOB
#define PWM3_IO_PIN         GPIO_Pin_11
#define PWM4_PORT           GPIOB
#define PWM4_IO_PIN         GPIO_Pin_12
#define PWM5_PORT           GPIOB
#define PWM5_IO_PIN         GPIO_Pin_13
#define PWM6_PORT           GPIOB
#define PWM6_IO_PIN         GPIO_Pin_14
#define PWM7_PORT           GPIOB
#define PWM7_IO_PIN         GPIO_Pin_15
#define PWM8_PORT           GPIOD
#define PWM8_IO_PIN         GPIO_Pin_2

//16MFLASH
#define FLASH16M_NCS_PORT     GPIOD
#define FLASH16M_NCS_IO_PIN   GPIO_Pin_7
#define FLASH16M_SCK_PORT     GPIOD
#define FLASH16M_SCK_IO_PIN   GPIO_Pin_11
#define FLASH16M_MOSI_PORT    GPIOD
#define FLASH16M_MOSI_IO_PIN  GPIO_Pin_12
#define FLASH16M_MISO_PORT    GPIOD
#define FLASH16M_MISO_IO_PIN  GPIO_Pin_13

//dcmi
#define DCMI_LCD_RST_PIN                    (13)
#define DCMI_LCD_CS_PIN                     (32)
#define DCMI_LCD_CLK_PIN                    (12)
#define DCMI_LCD_MOSI_PIN                   (10)
#define DCMI_LCD_MISO_PIN                   (9)
#define DCMI_LCD_A0_PIN                     (11)
#define DCMI_LCD_BL_PIN                     (34)


#define DCMI_CAMERA_SDA_PIN                 (40)
#define DCMI_CAMERA_SCL_PIN                 (39)
#define DCMI_CAMERA_RST_PIN                 (32)
#define DCMI_CAMERA_PWDN_PIN                (49)
#define DCMI_CAMERA_MCLK_PIN                (35)
#define DCMI_CAMERA_PCLK_PIN                (36)
#define DCMI_CAMERA_VSYNC_PIN               (38)
#define DCMI_CAMERA_HSYNC_PIN               (37)
#define DCMI_CAMERA_DATA_WIDTH              (8)
#define DCMI_CAMERA_DATA0_PIN               (48)
#define DCMI_CAMERA_DATA1_PIN               (47)
#define DCMI_CAMERA_DATA2_PIN               (46)
#define DCMI_CAMERA_DATA3_PIN               (45)
#define DCMI_CAMERA_DATA4_PIN               (44)
#define DCMI_CAMERA_DATA5_PIN               (43)
#define DCMI_CAMERA_DATA6_PIN               (42)
#define DCMI_CAMERA_DATA7_PIN               (41)

//psram
#define PSRAM_NCS_PIN                       (45)
#define PSRAM_SCK_PIN                       (44)
#define PSRAM_DATA0_PIN                     (52)
#define PSRAM_DATA1_PIN                     (49)
#define PSRAM_DATA2_PIN                     (50)
#define PSRAM_DATA3_PIN                     (43)

//i2c0
#define I2C0PORT            MI2C0
#define I2C0SCL_PORT        GPIOB
#define I2C0SCL_IO_PIN      GPIO_Pin_2
#define I2C0SDA_PORT        GPIOB
#define I2C0SDA_IO_PIN      GPIO_Pin_3

//i2c1
#define I2C1PORT            MI2C1
#define I2C1SCL_PORT        GPIOB
#define I2C1SCL_IO_PIN      GPIO_Pin_4
#define I2C1SDA_PORT        GPIOB
#define I2C1SDA_IO_PIN      GPIO_Pin_5

//sci7816
#define SCI7816_RESET_PORT                  GPIOE
#define SCI7816_RESET_IO_PIN                GPIO_Pin_14
#define SCI7816_CLK_PORT                    GPIOE
#define SCI7816_CLK_IO_PIN                  GPIO_Pin_15
#define SCI7816_DATA_PORT                   GPIOE
#define SCI7816_DATA_IO_PIN                 GPIO_Pin_13

#define SCI7816_VCARD_PORT                  GPIOE
#define SCI7816_VCARD_IO_PIN                GPIO_Pin_12
#define SCI7816_DETECT_PORT                 GPIOC
#define SCI7816_DETECT_IO_PIN               GPIO_Pin_1

//sci17816
#define SCI17816_RESET_PORT                  GPIOE
#define SCI17816_RESET_IO_PIN                GPIO_Pin_10
#define SCI17816_CLK_PORT                    GPIOA
#define SCI17816_CLK_IO_PIN                  GPIO_Pin_7
#define SCI17816_DATA_PORT                   GPIOA
#define SCI17816_DATA_IO_PIN                 GPIO_Pin_6
#define SCI17816_CARD1_EN_PORT               GPIOE
#define SCI17816_CARD1_EN_IO_PIN             GPIO_Pin_11

//fpc1020
#define FPC1020_PORT 	        GPIOC
#define FPC1020_CS_PIN       	GPIO_Pin_6
#define FPC1020_SCLK_PIN 	    GPIO_Pin_1
#define FPC1020_MOSI_PIN 	    GPIO_Pin_2
#define FPC1020_MISO_PIN 	    GPIO_Pin_3
#define FPC1020_RST_PIN 	    GPIO_Pin_4
#define FPC1020_IRQ_PIN 	    GPIO_Pin_5

//nfc
#define NFC_TEMER               TIM0
#define NFC_SPI                 MSPI0
#define NFC_RESET_PORT          GPIOD
#define NFC_RESET_PIN           GPIO_Pin_10
#define NFC_12MCLK_PORT         GPIOD
#define NFC_12MCLK_PIN          GPIO_Pin_2
#define NFC_SPI_CS_PORT         GPIOD
#define NFC_SPI_CS_PIN          GPIO_Pin_4
#define NFC_SPI_SCK_PORT        GPIOD
#define NFC_SPI_SCK_PIN         GPIO_Pin_11
#define NFC_SPI_MOSI_PORT       GPIOD
#define NFC_SPI_MOSI_PIN        GPIO_Pin_12
#define NFC_SPI_MISO_PORT       GPIOD
#define NFC_SPI_MISO_PIN        GPIO_Pin_13

#define UART2BTBAUD           115200
#define UART2BT_TX_PORT       GPIOE
#define UART2BT_TX_PIN        GPIO_Pin_0
#define UART2BT_RX_PORT       GPIOD
#define UART2BT_RX_PIN        GPIO_Pin_13
#define UART2BT_UARTx         MUART2
#define UART2BT_Tx_FUNC       UART2_TXD
#define UART2BT_Rx_FUNC       UART2_RXD
#define UART2BT_IRQN          10
#define UART2BT_RTS_SOFT_PORT GPIOD     //鐢ㄤ簬m0鏍镐笌bt鏍歌蒋浠舵祦鎺�
#define UART2BT_RTS_SOFT_PIN  GPIO_Pin_11

#elif (BOARD_TYPE == APP_YC3165AB_BOARD)
//uart0
#define PRINTPORT           MUART0
#define PRINT_BAUD          (921600)
#define PRINTRX_PORT        GPIOD
#define PRINTRX_IO_PIN      GPIO_Pin_6
#define PRINTTX_PORT        GPIOD
#define PRINTTX_IO_PIN      GPIO_Pin_5
#define PRINTRTS_PORT       GPIOB
#define PRINTRTS_IO_PIN     GPIO_Pin_2
#define PRINTCTS_PORT       GPIOB
#define PRINTCTS_IO_PIN     GPIO_Pin_3

//uart1
#define UART1_BAUD          (921600)
#define UART1RX_PORT        GPIOA
#define UART1RX_IO_PIN      GPIO_Pin_0
#define UART1TX_PORT        GPIOA
#define UART1TX_IO_PIN      GPIO_Pin_1

//spi0
#define SPI0PORT            MSPI0
#define SPI0NCS_PORT        GPIOB
#define SPI0NCS_IO_PIN      GPIO_Pin_15
#define SPI04MNCS_PORT      GPIOD
#define SPI04MNCS_IO_PIN    GPIO_Pin_12
#define SPI016MNCS_PORT     GPIOD
#define SPI016MNCS_IO_PIN   GPIO_Pin_13
#define SPI0SCK_PORT        GPIOB
#define SPI0SCK_IO_PIN      GPIO_Pin_1
#define SPI0MOSI_PORT       GPIOA
#define SPI0MOSI_IO_PIN     GPIO_Pin_15
#define SPI0MISO_PORT       GPIOA
#define SPI0MISO_IO_PIN     GPIO_Pin_14

//spi1
#define SPI1PORT            MSPI1
#define SPI1NCS_PORT        GPIOB
#define SPI1NCS_IO_PIN      GPIO_Pin_15
#define SPI14MNCS_PORT      GPIOC
#define SPI14MNCS_IO_PIN    GPIO_Pin_8
#define SPI116MNCS_PORT     GPIOC
#define SPI116MNCS_IO_PIN   GPIO_Pin_8
#define SPI1SCK_PORT        GPIOB
#define SPI1SCK_IO_PIN      GPIO_Pin_1
#define SPI1MOSI_PORT       GPIOA
#define SPI1MOSI_IO_PIN     GPIO_Pin_15
#define SPI1MISO_PORT       GPIOA
#define SPI1MISO_IO_PIN     GPIO_Pin_14

#define SPI2PORT            HSPI
#define SPI2NCS_PORT        GPIOB
#define SPI2NCS_IO_PIN      GPIO_Pin_15
#define SPI2SCK_PORT        GPIOB
#define SPI2SCK_IO_PIN      GPIO_Pin_1
#define SPI2MOSI_PORT       GPIOA
#define SPI2MOSI_IO_PIN     GPIO_Pin_15
#define SPI2MISO_PORT       GPIOA
#define SPI2MISO_IO_PIN     GPIO_Pin_14

//spi0_slaver
#define SPI0NCS_PORT_S        GPIOB
#define SPI0NCS_IO_PIN_S      GPIO_Pin_12
#define SPI0SCK_PORT_S        GPIOB
#define SPI0SCK_IO_PIN_S      GPIO_Pin_13
#define SPI0MOSI_PORT_S       GPIOB
#define SPI0MOSI_IO_PIN_S     GPIO_Pin_14
#define SPI0MISO_PORT_S       GPIOB
#define SPI0MISO_IO_PIN_S     GPIO_Pin_15

//spi1_master
#define SPI1NCS_PORT_M         GPIOC
#define SPI1NCS_IO_PIN_M       GPIO_Pin_1
#define SPI1SCK_PORT_M         GPIOC
#define SPI1SCK_IO_PIN_M       GPIO_Pin_2
#define SPI1MOSI_PORT_M        GPIOC
#define SPI1MOSI_IO_PIN_M      GPIO_Pin_3
#define SPI1MISO_PORT_M        GPIOC
#define SPI1MISO_IO_PIN_M      GPIO_Pin_4

//lcd
#define ST7539CS_PORT       GPIOB
#define ST7539CS_IO_PIN    GPIO_Pin_15
#define ST7539RST_PORT      GPIOB
#define ST7539RST_IO_PIN   GPIO_Pin_2
#define ST7539A0_PORT  	    GPIOB
#define ST7539A0_IO_PIN   	GPIO_Pin_0
#define ST7539BL_PORT  	    GPIOC
#define ST7539BL_IO_PIN   	GPIO_Pin_2
#define ST7539SCK_PORT      GPIOB
#define ST7539SCK_IO_PIN    GPIO_Pin_1
#define ST7539MOSI_PORT     GPIOA
#define ST7539MOSI_IO_PIN   GPIO_Pin_15
#define ST7539MISO_PORT     GPIOA
#define ST7539MISO_IO_PIN   GPIO_Pin_14

//tft
#define ST7789CS_PORT       GPIOC
#define ST7789CS_IO_PIN     GPIO_Pin_7
#define ST7789RST_PORT      GPIOC
#define ST7789RST_IO_PIN    GPIO_Pin_5
#define ST7789A0_PORT       GPIOB
#define ST7789A0_IO_PIN     GPIO_Pin_1
#define ST7789BL_PORT       GPIOC
#define ST7789BL_IO_PIN     GPIO_Pin_8
#define ST7789SCK_PORT      GPIOB
#define ST7789SCK_IO_PIN    GPIO_Pin_0
#define ST7789MOSI_PORT     GPIOA
#define ST7789MOSI_IO_PIN   GPIO_Pin_15
#define ST7789MISO_PORT     GPIOA
#define ST7789MISO_IO_PIN   GPIO_Pin_14
//pwm
#define PWM0_PORT           GPIOB
#define PWM0_IO_PIN         GPIO_Pin_8
#define PWM1_PORT           GPIOB
#define PWM1_IO_PIN         GPIO_Pin_9
#define PWM2_PORT           GPIOB
#define PWM2_IO_PIN         GPIO_Pin_10
#define PWM3_PORT           GPIOB
#define PWM3_IO_PIN         GPIO_Pin_11
#define PWM4_PORT           GPIOB
#define PWM4_IO_PIN         GPIO_Pin_12
#define PWM5_PORT           GPIOB
#define PWM5_IO_PIN         GPIO_Pin_13
#define PWM6_PORT           GPIOB
#define PWM6_IO_PIN         GPIO_Pin_14
#define PWM7_PORT           GPIOB
#define PWM7_IO_PIN         GPIO_Pin_15
#define PWM8_PORT           GPIOD
#define PWM8_IO_PIN         GPIO_Pin_2

//16MFLASH
#define FLASH16M_NCS_PORT     GPIOD
#define FLASH16M_NCS_IO_PIN   GPIO_Pin_7
#define FLASH16M_SCK_PORT     GPIOD
#define FLASH16M_SCK_IO_PIN   GPIO_Pin_11
#define FLASH16M_MOSI_PORT    GPIOD
#define FLASH16M_MOSI_IO_PIN  GPIO_Pin_12
#define FLASH16M_MISO_PORT    GPIOD
#define FLASH16M_MISO_IO_PIN  GPIO_Pin_13

//dcmi
#define DCMI_LCD_RST_PIN                    (37)
#define DCMI_LCD_CS_PIN                     (39)
#define DCMI_LCD_CLK_PIN                    (16)
#define DCMI_LCD_MOSI_PIN                   (14)
#define DCMI_LCD_MISO_PIN                   (15)
#define DCMI_LCD_A0_PIN                     (17)
#define DCMI_LCD_BL_PIN                     (40)


#define DCMI_CAMERA_SDA_PIN                 (51)
#define DCMI_CAMERA_SCL_PIN                 (48)
#define DCMI_CAMERA_RST_PIN                 (0xff)
#define DCMI_CAMERA_PWDN_PIN                (63)
#define DCMI_CAMERA_MCLK_PIN                (41)
#define DCMI_CAMERA_PCLK_PIN                (42)
#define DCMI_CAMERA_VSYNC_PIN               (47)
#define DCMI_CAMERA_HSYNC_PIN               (46)
#define DCMI_CAMERA_DATA_WIDTH              (8)
#define DCMI_CAMERA_DATA0_PIN               (62)
#define DCMI_CAMERA_DATA1_PIN               (61)
#define DCMI_CAMERA_DATA2_PIN               (60)
#define DCMI_CAMERA_DATA3_PIN               (59)
#define DCMI_CAMERA_DATA4_PIN               (58)
#define DCMI_CAMERA_DATA5_PIN               (57)
#define DCMI_CAMERA_DATA6_PIN               (56)
#define DCMI_CAMERA_DATA7_PIN               (55)

//psram
#define PSRAM_NCS_PIN                       (45)
#define PSRAM_SCK_PIN                       (44)
#define PSRAM_DATA0_PIN                     (52)
#define PSRAM_DATA1_PIN                     (49)
#define PSRAM_DATA2_PIN                     (50)
#define PSRAM_DATA3_PIN                     (43)

//i2c0
#define I2C0PORT            MI2C0
#define I2C0SCL_PORT        GPIOB
#define I2C0SCL_IO_PIN      GPIO_Pin_2
#define I2C0SDA_PORT        GPIOB
#define I2C0SDA_IO_PIN      GPIO_Pin_3

//i2c1
#define I2C1PORT            MI2C1
#define I2C1SCL_PORT        GPIOB
#define I2C1SCL_IO_PIN      GPIO_Pin_4
#define I2C1SDA_PORT        GPIOB
#define I2C1SDA_IO_PIN      GPIO_Pin_5

//sci7816
#define SCI7816_RESET_PORT                  GPIOE
#define SCI7816_RESET_IO_PIN                GPIO_Pin_14
#define SCI7816_CLK_PORT                    GPIOE
#define SCI7816_CLK_IO_PIN                  GPIO_Pin_15
#define SCI7816_DATA_PORT                   GPIOE
#define SCI7816_DATA_IO_PIN                 GPIO_Pin_13

#define SCI7816_VCARD_PORT                  GPIOE
#define SCI7816_VCARD_IO_PIN                GPIO_Pin_12
#define SCI7816_DETECT_PORT                 GPIOC
#define SCI7816_DETECT_IO_PIN               GPIO_Pin_1

//sci17816
#define SCI17816_RESET_PORT                  GPIOE
#define SCI17816_RESET_IO_PIN                GPIO_Pin_10
#define SCI17816_CLK_PORT                    GPIOA
#define SCI17816_CLK_IO_PIN                  GPIO_Pin_7
#define SCI17816_DATA_PORT                   GPIOA
#define SCI17816_DATA_IO_PIN                 GPIO_Pin_6
#define SCI17816_CARD1_EN_PORT               GPIOE
#define SCI17816_CARD1_EN_IO_PIN             GPIO_Pin_11

//fpc1020
#define FPC1020_PORT 	        GPIOC
#define FPC1020_CS_PIN       	GPIO_Pin_6
#define FPC1020_SCLK_PIN 	    GPIO_Pin_1
#define FPC1020_MOSI_PIN 	    GPIO_Pin_2
#define FPC1020_MISO_PIN 	    GPIO_Pin_3
#define FPC1020_RST_PIN 	    GPIO_Pin_4
#define FPC1020_IRQ_PIN 	    GPIO_Pin_5

//nfc
#define NFC_TEMER               TIM0
#define NFC_SPI                 MSPI0
#define NFC_RESET_PORT          GPIOD
#define NFC_RESET_PIN           GPIO_Pin_10
#define NFC_12MCLK_PORT         GPIOD
#define NFC_12MCLK_PIN          GPIO_Pin_2
#define NFC_SPI_CS_PORT         GPIOD
#define NFC_SPI_CS_PIN          GPIO_Pin_4
#define NFC_SPI_SCK_PORT        GPIOD
#define NFC_SPI_SCK_PIN         GPIO_Pin_11
#define NFC_SPI_MOSI_PORT       GPIOD
#define NFC_SPI_MOSI_PIN        GPIO_Pin_12
#define NFC_SPI_MISO_PORT       GPIOD
#define NFC_SPI_MISO_PIN        GPIO_Pin_13

#define UART2BTBAUD           115200
#define UART2BT_TX_PORT       GPIOE
#define UART2BT_TX_PIN        GPIO_Pin_0
#define UART2BT_RX_PORT       GPIOD
#define UART2BT_RX_PIN        GPIO_Pin_13
#define UART2BT_UARTx         MUART2
#define UART2BT_Tx_FUNC       UART2_TXD
#define UART2BT_Rx_FUNC       UART2_RXD
#define UART2BT_IRQN          10
#define UART2BT_RTS_SOFT_PORT GPIOD     //鐢ㄤ簬m0鏍镐笌bt鏍歌蒋浠舵祦鎺�
#define UART2BT_RTS_SOFT_PIN  GPIO_Pin_11



#elif (BOARD_TYPE == APP_YC3154AB_BOARD)
//uart0
#define PRINTPORT           MUART0
#define PRINT_BAUD          (921600)
#define PRINTRX_PORT        GPIOD
#define PRINTRX_IO_PIN      GPIO_Pin_6
#define PRINTTX_PORT        GPIOD
#define PRINTTX_IO_PIN      GPIO_Pin_5
#define PRINTRTS_PORT       GPIOB
#define PRINTRTS_IO_PIN     GPIO_Pin_2
#define PRINTCTS_PORT       GPIOB
#define PRINTCTS_IO_PIN     GPIO_Pin_3

//uart1
#define UART1_BAUD          (921600)
#define UART1RX_PORT        GPIOA
#define UART1RX_IO_PIN      GPIO_Pin_0
#define UART1TX_PORT        GPIOA
#define UART1TX_IO_PIN      GPIO_Pin_1

//spi0
#define SPI0PORT            MSPI0
#define SPI0NCS_PORT        GPIOB
#define SPI0NCS_IO_PIN      GPIO_Pin_15
#define SPI04MNCS_PORT      GPIOD
#define SPI04MNCS_IO_PIN    GPIO_Pin_12
#define SPI016MNCS_PORT     GPIOD
#define SPI016MNCS_IO_PIN   GPIO_Pin_13
#define SPI0SCK_PORT        GPIOB
#define SPI0SCK_IO_PIN      GPIO_Pin_1
#define SPI0MOSI_PORT       GPIOA
#define SPI0MOSI_IO_PIN     GPIO_Pin_15
#define SPI0MISO_PORT       GPIOA
#define SPI0MISO_IO_PIN     GPIO_Pin_14

//spi1
#define SPI1PORT            MSPI1
#define SPI1NCS_PORT        GPIOB
#define SPI1NCS_IO_PIN      GPIO_Pin_15
#define SPI14MNCS_PORT      GPIOC
#define SPI14MNCS_IO_PIN    GPIO_Pin_8
#define SPI116MNCS_PORT     GPIOC
#define SPI116MNCS_IO_PIN   GPIO_Pin_8
#define SPI1SCK_PORT        GPIOB
#define SPI1SCK_IO_PIN      GPIO_Pin_1
#define SPI1MOSI_PORT       GPIOA
#define SPI1MOSI_IO_PIN     GPIO_Pin_15
#define SPI1MISO_PORT       GPIOA
#define SPI1MISO_IO_PIN     GPIO_Pin_14

#define SPI2PORT            HSPI
#define SPI2NCS_PORT        GPIOB
#define SPI2NCS_IO_PIN      GPIO_Pin_15
#define SPI2SCK_PORT        GPIOB
#define SPI2SCK_IO_PIN      GPIO_Pin_1
#define SPI2MOSI_PORT       GPIOA
#define SPI2MOSI_IO_PIN     GPIO_Pin_15
#define SPI2MISO_PORT       GPIOA
#define SPI2MISO_IO_PIN     GPIO_Pin_14

//spi0_slaver
#define SPI0NCS_PORT_S        GPIOB
#define SPI0NCS_IO_PIN_S      GPIO_Pin_12
#define SPI0SCK_PORT_S        GPIOB
#define SPI0SCK_IO_PIN_S      GPIO_Pin_13
#define SPI0MOSI_PORT_S       GPIOB
#define SPI0MOSI_IO_PIN_S     GPIO_Pin_14
#define SPI0MISO_PORT_S       GPIOB
#define SPI0MISO_IO_PIN_S     GPIO_Pin_15

//spi1_master
#define SPI1NCS_PORT_M         GPIOC
#define SPI1NCS_IO_PIN_M       GPIO_Pin_1
#define SPI1SCK_PORT_M         GPIOC
#define SPI1SCK_IO_PIN_M       GPIO_Pin_2
#define SPI1MOSI_PORT_M        GPIOC
#define SPI1MOSI_IO_PIN_M      GPIO_Pin_3
#define SPI1MISO_PORT_M        GPIOC
#define SPI1MISO_IO_PIN_M      GPIO_Pin_4

//lcd
#define ST7539CS_PORT       GPIOB
#define ST7539CS_IO_PIN    GPIO_Pin_15
#define ST7539RST_PORT      GPIOB
#define ST7539RST_IO_PIN   GPIO_Pin_2
#define ST7539A0_PORT  	    GPIOB
#define ST7539A0_IO_PIN   	GPIO_Pin_0
#define ST7539BL_PORT  	    GPIOC
#define ST7539BL_IO_PIN   	GPIO_Pin_2
#define ST7539SCK_PORT      GPIOB
#define ST7539SCK_IO_PIN    GPIO_Pin_1
#define ST7539MOSI_PORT     GPIOA
#define ST7539MOSI_IO_PIN   GPIO_Pin_15
#define ST7539MISO_PORT     GPIOA
#define ST7539MISO_IO_PIN   GPIO_Pin_14

//tft
#define ST7789CS_PORT       GPIOC
#define ST7789CS_IO_PIN     GPIO_Pin_7
#define ST7789RST_PORT      GPIOC
#define ST7789RST_IO_PIN    GPIO_Pin_5
#define ST7789A0_PORT       GPIOB
#define ST7789A0_IO_PIN     GPIO_Pin_1
#define ST7789BL_PORT       GPIOC
#define ST7789BL_IO_PIN     GPIO_Pin_8
#define ST7789SCK_PORT      GPIOB
#define ST7789SCK_IO_PIN    GPIO_Pin_0
#define ST7789MOSI_PORT     GPIOA
#define ST7789MOSI_IO_PIN   GPIO_Pin_15
#define ST7789MISO_PORT     GPIOA
#define ST7789MISO_IO_PIN   GPIO_Pin_14
//pwm
#define PWM0_PORT           GPIOB
#define PWM0_IO_PIN         GPIO_Pin_8
#define PWM1_PORT           GPIOB
#define PWM1_IO_PIN         GPIO_Pin_9
#define PWM2_PORT           GPIOB
#define PWM2_IO_PIN         GPIO_Pin_10
#define PWM3_PORT           GPIOB
#define PWM3_IO_PIN         GPIO_Pin_11
#define PWM4_PORT           GPIOB
#define PWM4_IO_PIN         GPIO_Pin_12
#define PWM5_PORT           GPIOB
#define PWM5_IO_PIN         GPIO_Pin_13
#define PWM6_PORT           GPIOB
#define PWM6_IO_PIN         GPIO_Pin_14
#define PWM7_PORT           GPIOB
#define PWM7_IO_PIN         GPIO_Pin_15
#define PWM8_PORT           GPIOD
#define PWM8_IO_PIN         GPIO_Pin_2

//16MFLASH
#define FLASH16M_NCS_PORT     GPIOD
#define FLASH16M_NCS_IO_PIN   GPIO_Pin_7
#define FLASH16M_SCK_PORT     GPIOD
#define FLASH16M_SCK_IO_PIN   GPIO_Pin_11
#define FLASH16M_MOSI_PORT    GPIOD
#define FLASH16M_MOSI_IO_PIN  GPIO_Pin_12
#define FLASH16M_MISO_PORT    GPIOD
#define FLASH16M_MISO_IO_PIN  GPIO_Pin_13

//dcmi
#define DCMI_LCD_RST_PIN                    (74)
#define DCMI_LCD_CS_PIN                     (31)
#define DCMI_LCD_CLK_PIN                    (17)
#define DCMI_LCD_MOSI_PIN                   (15)
#define DCMI_LCD_MISO_PIN                   (14)
#define DCMI_LCD_A0_PIN                     (16)
#define DCMI_LCD_BL_PIN                     (62)


#define DCMI_CAMERA_SDA_PIN                 (40)
#define DCMI_CAMERA_SCL_PIN                 (39)
#define DCMI_CAMERA_RST_PIN                 (0xff)
#define DCMI_CAMERA_PWDN_PIN                (49)
#define DCMI_CAMERA_MCLK_PIN                (32)
#define DCMI_CAMERA_PCLK_PIN                (34)
#define DCMI_CAMERA_VSYNC_PIN               (38)
#define DCMI_CAMERA_HSYNC_PIN               (37)
#define DCMI_CAMERA_DATA_WIDTH              (8)
#define DCMI_CAMERA_DATA0_PIN               (48)
#define DCMI_CAMERA_DATA1_PIN               (47)
#define DCMI_CAMERA_DATA2_PIN               (46)
#define DCMI_CAMERA_DATA3_PIN               (45)
#define DCMI_CAMERA_DATA4_PIN               (44)
#define DCMI_CAMERA_DATA5_PIN               (43)
#define DCMI_CAMERA_DATA6_PIN               (42)
#define DCMI_CAMERA_DATA7_PIN               (41)

//psram
#define PSRAM_NCS_PIN                       (45)
#define PSRAM_SCK_PIN                       (44)
#define PSRAM_DATA0_PIN                     (52)
#define PSRAM_DATA1_PIN                     (49)
#define PSRAM_DATA2_PIN                     (50)
#define PSRAM_DATA3_PIN                     (43)

//i2c0
#define I2C0PORT            MI2C0
#define I2C0SCL_PORT        GPIOB
#define I2C0SCL_IO_PIN      GPIO_Pin_2
#define I2C0SDA_PORT        GPIOB
#define I2C0SDA_IO_PIN      GPIO_Pin_3

//i2c1
#define I2C1PORT            MI2C1
#define I2C1SCL_PORT        GPIOB
#define I2C1SCL_IO_PIN      GPIO_Pin_4
#define I2C1SDA_PORT        GPIOB
#define I2C1SDA_IO_PIN      GPIO_Pin_5

//sci7816
#define SCI7816_RESET_PORT                  GPIOE
#define SCI7816_RESET_IO_PIN                GPIO_Pin_14
#define SCI7816_CLK_PORT                    GPIOE
#define SCI7816_CLK_IO_PIN                  GPIO_Pin_15
#define SCI7816_DATA_PORT                   GPIOE
#define SCI7816_DATA_IO_PIN                 GPIO_Pin_13

#define SCI7816_VCARD_PORT                  GPIOE
#define SCI7816_VCARD_IO_PIN                GPIO_Pin_12
#define SCI7816_DETECT_PORT                 GPIOC
#define SCI7816_DETECT_IO_PIN               GPIO_Pin_1

//sci17816
#define SCI17816_RESET_PORT                  GPIOE
#define SCI17816_RESET_IO_PIN                GPIO_Pin_10
#define SCI17816_CLK_PORT                    GPIOA
#define SCI17816_CLK_IO_PIN                  GPIO_Pin_7
#define SCI17816_DATA_PORT                   GPIOA
#define SCI17816_DATA_IO_PIN                 GPIO_Pin_6
#define SCI17816_CARD1_EN_PORT               GPIOE
#define SCI17816_CARD1_EN_IO_PIN             GPIO_Pin_11

//fpc1020
#define FPC1020_PORT 	        GPIOC
#define FPC1020_CS_PIN       	GPIO_Pin_6
#define FPC1020_SCLK_PIN 	    GPIO_Pin_1
#define FPC1020_MOSI_PIN 	    GPIO_Pin_2
#define FPC1020_MISO_PIN 	    GPIO_Pin_3
#define FPC1020_RST_PIN 	    GPIO_Pin_4
#define FPC1020_IRQ_PIN 	    GPIO_Pin_5

//nfc
#define NFC_TEMER               TIM0
#define NFC_SPI                 MSPI0
#define NFC_RESET_PORT          GPIOD
#define NFC_RESET_PIN           GPIO_Pin_10
#define NFC_12MCLK_PORT         GPIOD
#define NFC_12MCLK_PIN          GPIO_Pin_2
#define NFC_SPI_CS_PORT         GPIOD
#define NFC_SPI_CS_PIN          GPIO_Pin_4
#define NFC_SPI_SCK_PORT        GPIOD
#define NFC_SPI_SCK_PIN         GPIO_Pin_11
#define NFC_SPI_MOSI_PORT       GPIOD
#define NFC_SPI_MOSI_PIN        GPIO_Pin_12
#define NFC_SPI_MISO_PORT       GPIOD
#define NFC_SPI_MISO_PIN        GPIO_Pin_13

#define UART2BTBAUD           115200
#define UART2BT_TX_PORT       GPIOE
#define UART2BT_TX_PIN        GPIO_Pin_0
#define UART2BT_RX_PORT       GPIOD
#define UART2BT_RX_PIN        GPIO_Pin_13
#define UART2BT_UARTx         MUART2
#define UART2BT_Tx_FUNC       UART2_TXD
#define UART2BT_Rx_FUNC       UART2_RXD
#define UART2BT_IRQN          10
#define UART2BT_RTS_SOFT_PORT GPIOD     //鐢ㄤ簬m0鏍镐笌bt鏍歌蒋浠舵祦鎺�
#define UART2BT_RTS_SOFT_PIN  GPIO_Pin_11

#elif(BOARD_TYPE == APP_194_YC3173AB_DOORLOCK_V1_0_BOARD)
//uart0
#define PRINTPORT           MUART0
#define PRINT_BAUD          (921600)
#define PRINTRX_PORT        GPIOD
#define PRINTRX_IO_PIN      GPIO_Pin_6
#define PRINTTX_PORT        GPIOD
#define PRINTTX_IO_PIN      GPIO_Pin_5
#define PRINTRTS_PORT       GPIOB
#define PRINTRTS_IO_PIN     GPIO_Pin_2
#define PRINTCTS_PORT       GPIOB
#define PRINTCTS_IO_PIN     GPIO_Pin_3

//uart1
#define UART1_BAUD          (921600)
#define UART1RX_PORT        GPIOA
#define UART1RX_IO_PIN      GPIO_Pin_0
#define UART1TX_PORT        GPIOA
#define UART1TX_IO_PIN      GPIO_Pin_1

//nfc
#define NFC_TEMER               TIM0
#define NFC_SPI                 MSPI0
#define NFC_RESET_PORT          GPIOE
#define NFC_RESET_PIN           GPIO_Pin_0    //IO64
#define NFC_12MCLK_PORT         GPIOD
#define NFC_12MCLK_PIN          GPIO_Pin_7    //IO55
#define NFC_SPI_CS_PORT         GPIOD
#define NFC_SPI_CS_PIN          GPIO_Pin_11   //IO59
#define NFC_SPI_SCK_PORT        GPIOD
#define NFC_SPI_SCK_PIN         GPIO_Pin_13   //IO61
#define NFC_SPI_MOSI_PORT       GPIOD
#define NFC_SPI_MOSI_PIN        GPIO_Pin_14   //IO62
#define NFC_SPI_MISO_PORT       GPIOD
#define NFC_SPI_MISO_PIN        GPIO_Pin_15   //IO63


//BT
#define UART2BTBAUD           115200
#define UART2BT_TX_PORT       GPIOB
#define UART2BT_TX_PIN        GPIO_Pin_8
#define UART2BT_RX_PORT       GPIOB
#define UART2BT_RX_PIN        GPIO_Pin_7
#define UART2BT_UARTx         MUART2
#define UART2BT_Tx_FUNC       UART2_TXD
#define UART2BT_Rx_FUNC       UART2_RXD
#define UART2BT_IRQN          10
#define UART2BT_RTS_SOFT_PORT GPIOD     //鐢ㄤ簬m0鏍镐笌bt鏍歌蒋浠舵祦鎺�
#define UART2BT_RTS_SOFT_PIN  GPIO_Pin_11

#endif

#endif
