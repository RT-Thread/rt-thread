/*
 * Copyright (c) 2006-2020, YICHIP Development Team
 * @file     yc_gpio.h
 * @brief    source file for setting gpio
 *
 * Change Logs:
 * Date            Author             Version        Notes
 * 2020-12-23     yangzhengfeng       V1.1.0         Modify the register module configuration
 */

#ifndef __YC_GPIO_H__
#define __YC_GPIO_H__

#include "yc3122.h"
#include "system.h"

#ifdef __cplusplus
extern "C" {
#endif

uint8_t UnMap(uint16_t x);
#define GPIO_CONFIG(x)         *((volatile uint8_t*)(MGPIO_BASE + x))
#define GPIO_GetNum(port, pin)    ((port * GPIO_PIN_NUM) + UnMap(pin))
#define GPIO_OD_TypeDef        uint8_t
#define GPIO_FUN_TYPEDEF       uint8_t
#define GPIO_PORT_NUM          5
#define GPIO_PIN_NUM           16

#define GPIO_OD_PORTA_10           ((GPIO_OD_TypeDef)0x00)     /*!< Pin 10 selected */
#define GPIO_OD_PORTB_06           ((GPIO_OD_TypeDef)0x01)     /*!< Pin 20 selected */
#define GPIO_OD_PORTC_01           ((GPIO_OD_TypeDef)0x02)     /*!< Pin 33 selected */
#define GPIO_OD_PORTC_08           ((GPIO_OD_TypeDef)0x03)     /*!< Pin 40 selected */
#define GPIO_OD_PORTD_00           ((GPIO_OD_TypeDef)0x04)     /*!< Pin 48 selected */
#define GPIO_OD_PORTD_12           ((GPIO_OD_TypeDef)0x05)     /*!< Pin 60 selected */
#define GPIO_OD_PORTE_06           ((GPIO_OD_TypeDef)0x06)     /*!< Pin 76 selected */
#define GPIO_OD_PORTE_12           ((GPIO_OD_TypeDef)0x07)     /*!< Pin 70 selected */

#define IS_GPIO_OD(port_od)         ((port_od == GPIO_OD_PORTA_10) || \
                                    (port_od == GPIO_OD_PORTB_06) || \
                                    (port_od == GPIO_OD_PORTC_01) || \
                                    (port_od == GPIO_OD_PORTC_08) || \
                                    (port_od == GPIO_OD_PORTD_00) || \
                                    (port_od == GPIO_OD_PORTD_12) || \
                                    (port_od == GPIO_OD_PORTE_06) || \
                                    (port_od == GPIO_OD_PORTE_12))
typedef enum
{
    GPIO_Pin_0 = BIT0,
    GPIO_Pin_1 = BIT1,
    GPIO_Pin_2 = BIT2,
    GPIO_Pin_3 = BIT3,
    GPIO_Pin_4 = BIT4,
    GPIO_Pin_5 = BIT5,
    GPIO_Pin_6 = BIT6,
    GPIO_Pin_7 = BIT7,
    GPIO_Pin_8 = BIT8,
    GPIO_Pin_9 = BIT9,
    GPIO_Pin_10 = BIT10,
    GPIO_Pin_11 = BIT11,
    GPIO_Pin_12 = BIT12,
    GPIO_Pin_13 = BIT13,
    GPIO_Pin_14 = BIT14,
    GPIO_Pin_15 = BIT15
} GPIO_Pin_TypeDef;

#define IS_GPIO_PIN(PIN)   (((((PIN) & ~(uint16_t)0xFFFF)) == 0x00) && ((PIN) != (uint16_t)0x00))
#define IS_GPIO_PIN_SINGLE(PIN)    ((PIN == GPIO_Pin_0) || \
                                    (PIN == GPIO_Pin_1) || \
                                    (PIN == GPIO_Pin_2) || \
                                    (PIN == GPIO_Pin_3) || \
                                    (PIN == GPIO_Pin_4) || \
                                    (PIN == GPIO_Pin_5) || \
                                    (PIN == GPIO_Pin_6) || \
                                    (PIN == GPIO_Pin_7) || \
                                    (PIN == GPIO_Pin_8) || \
                                    (PIN == GPIO_Pin_9) || \
                                    (PIN == GPIO_Pin_10) || \
                                    (PIN == GPIO_Pin_11) || \
                                    (PIN == GPIO_Pin_12) || \
                                    (PIN == GPIO_Pin_13) || \
                                    (PIN == GPIO_Pin_14) || \
                                    (PIN == GPIO_Pin_15))

typedef enum
{
    GPIOA = 0,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE
} GPIO_TypeDef;

#define IS_GPIO_PORT(port) (port <= GPIOE)

/*******************  Bit definition for gpio funaction  **********************/
#define INPUT                   ((GPIO_FUN_TYPEDEF) 0)
#define QSPI_NCS                ((GPIO_FUN_TYPEDEF) 2)        /*Mapping the scope GPIO[32:0] and GPIO[76:56]*/
#define QSPI_SCK                ((GPIO_FUN_TYPEDEF) 3)        /*Mapping the scope GPIO[32:0] and GPIO[76:56]*/
#define QSPI_IO0                ((GPIO_FUN_TYPEDEF) 4)        /*Mapping the scope GPIO[32:0] and GPIO[76:56]*/
#define QSPI_IO1                ((GPIO_FUN_TYPEDEF) 5)        /*Mapping the scope GPIO[32:0] and GPIO[76:56]*/
#define QSPI_IO2                ((GPIO_FUN_TYPEDEF) 6)        /*Mapping the scope GPIO[32:0] and GPIO[76:56]*/
#define QSPI_IO3                ((GPIO_FUN_TYPEDEF) 7)        /*Mapping the scope GPIO[32:0] and GPIO[76:56]*/
#define UART0_TXD               ((GPIO_FUN_TYPEDEF) 8)
#define UART0_RXD               ((GPIO_FUN_TYPEDEF) 9)
#define UART0_RTS               ((GPIO_FUN_TYPEDEF)10)
#define UART0_CTS               ((GPIO_FUN_TYPEDEF)11)
#define UART1_TXD               ((GPIO_FUN_TYPEDEF)12)        /*Mapping the scope GPIO[47:0]*/
#define UART1_RXD               ((GPIO_FUN_TYPEDEF)13)        /*Mapping the scope GPIO[47:0]*/
#define UART1_RTS               ((GPIO_FUN_TYPEDEF)14)        /*Mapping the scope GPIO[47:0]*/
#define UART1_CTS               ((GPIO_FUN_TYPEDEF)15)        /*Mapping the scope GPIO[47:0]*/
#define UART2_TXD               ((GPIO_FUN_TYPEDEF)36)        /*Mapping the scope GPIO[79:40]*/
#define UART2_RXD               ((GPIO_FUN_TYPEDEF)37)        /*Mapping the scope GPIO[79:40]*/
#define UART2_RTS               ((GPIO_FUN_TYPEDEF)38)        /*Mapping the scope GPIO[79:40]*/
#define UART2_CTS               ((GPIO_FUN_TYPEDEF)39)        /*Mapping the scope GPIO[79:40]*/
#define UART3_TXD               ((GPIO_FUN_TYPEDEF)53)        /*Each group of 4 GPIOs is mapped to CTS/TXD/RXD/RTS,mapping the scope GPIO[60:20]*/
#define UART3_RXD               ((GPIO_FUN_TYPEDEF)53)        /*Each group of 4 GPIOs is mapped to CTS/TXD/RXD/RTS,mapping the scope GPIO[60:20]*/
#define UART3_RTS               ((GPIO_FUN_TYPEDEF)53)        /*Each group of 4 GPIOs is mapped to CTS/TXD/RXD/RTS,mapping the scope GPIO[60:20]*/
#define UART3_CTS               ((GPIO_FUN_TYPEDEF)53)        /*Each group of 4 GPIOs is mapped to CTS/TXD/RXD/RTS,mapping the scope GPIO[60:20]*/
#define PWM_OUT                 ((GPIO_FUN_TYPEDEF)16)        /*Each group of 8 GPIOs is mapped to PWM0~7*/
#define PWM_OUT8                ((GPIO_FUN_TYPEDEF)17)        /*Mapping the scope GPIO[79:48]*/
#define PWM_OUT01               ((GPIO_FUN_TYPEDEF)40)        /*GPIO_INDEX%8 is not a 0 and 1 pin, each two is a group, respectively mapped to PWM0/PWM1*/
#define PWM_OUT23               ((GPIO_FUN_TYPEDEF)41)        /*GPIO_INDEX%8 is not a 2 and 3 pin, each two is a group, respectively mapped to PWM2/PWM3*/
#define DCMI_PCLK               ((GPIO_FUN_TYPEDEF)18)
#define DCMI_VSYNC              ((GPIO_FUN_TYPEDEF)19)
#define DCMI_HSYNC              ((GPIO_FUN_TYPEDEF)20)
#define DCMI_D0                 ((GPIO_FUN_TYPEDEF)21)
#define DCMI_D1                 ((GPIO_FUN_TYPEDEF)22)
#define DCMI_D0_D13             ((GPIO_FUN_TYPEDEF)23)        /*GPIO[7] to GPIO[76] is a group of 14, which are mapped to D13 to D0 respectively*/
#define SPID_SDIO               ((GPIO_FUN_TYPEDEF)27)        /*Every 3 GPIOs are a group, which are respectively mapped to SPI0_SDIO/SPI1_SDIO/SPI2_SDIO*/
#define SPID0_NCS               ((GPIO_FUN_TYPEDEF)24)        /*Mapping the scope GPIO[79:0]*/
#define SPID0_SCK               ((GPIO_FUN_TYPEDEF)25)        /*Mapping the scope GPIO[79:0]*/
#define SPID0_MOSI              ((GPIO_FUN_TYPEDEF)26)        /*Mapping the scope GPIO[79:0]*/
#define SPID0_MISO              ((GPIO_FUN_TYPEDEF)28)        /*Mapping the scope GPIO[79:0]*/
#define SPID1_NCS               ((GPIO_FUN_TYPEDEF)48)        /*Mapping the scope GPIO[79:0]*/
#define SPID1_SCK               ((GPIO_FUN_TYPEDEF)49)        /*Mapping the scope GPIO[79:0]*/
#define SPID1_MOSI              ((GPIO_FUN_TYPEDEF)50)        /*Mapping the scope GPIO[79:0]*/
#define SPID1_MISO              ((GPIO_FUN_TYPEDEF)52)        /*Mapping the scope GPIO[79:0]*/
#define SPID_SLV_IN             ((GPIO_FUN_TYPEDEF)29)        /*Each of 6 GPIOs is a group, which are mapped to MSPI0~2 NCS_IN/SCK_IN respectively*/
#define XTAL32K                 ((GPIO_FUN_TYPEDEF)30)        /*Mapping the scope GPIO[15:0] and [74:48]*/
#define HSPI_NCS                ((GPIO_FUN_TYPEDEF)31)        /*Map to all pins*/
#define HSPI_SCK                ((GPIO_FUN_TYPEDEF)32)        /*Map to all pins*/
#define HSPI_MOSI               ((GPIO_FUN_TYPEDEF)33)        /*Map to all pins*/
#define HSPI_MISO               ((GPIO_FUN_TYPEDEF)34)        /*Map to all pins*/
#define DAC_OUT                 ((GPIO_FUN_TYPEDEF)35)        /*Each group of 2 GPIOs is mapped to Out P/Out N respectively*/
#define SDIO                    ((GPIO_FUN_TYPEDEF)42)        /*Each of 6 GPIOs is a group mapped to SDIO_CLK/SDIO_CMD/DAT0/DAT1/DAT2/DAT3*/
#define PSRAM_NCS               ((GPIO_FUN_TYPEDEF)43)
#define PSRAM_SCK               ((GPIO_FUN_TYPEDEF)44)
#define PSRAM_DATA_0            ((GPIO_FUN_TYPEDEF)45)        /*Each group of 4 GPIOs is mapped to D0/D1/D2/D3 respectively*/
#define PSRAM_DATA_1            ((GPIO_FUN_TYPEDEF)45)        /*Each group of 4 GPIOs is mapped to D0/D1/D2/D3 respectively*/
#define PSRAM_DATA_2            ((GPIO_FUN_TYPEDEF)45)        /*Each group of 4 GPIOs is mapped to D0/D1/D2/D3 respectively*/
#define PSRAM_DATA_3            ((GPIO_FUN_TYPEDEF)45)        /*Each group of 4 GPIOs is mapped to D0/D1/D2/D3 respectively*/
#define JTAG_RV_TCK             ((GPIO_FUN_TYPEDEF)46)        /*Each group of 4 GPIOs is mapped to TCK/TMS/TDI/TDO*/
#define JTAG_RV_TMS             ((GPIO_FUN_TYPEDEF)46)        /*Each group of 4 GPIOs is mapped to TCK/TMS/TDI/TDO*/
#define JTAG_RV_TDI             ((GPIO_FUN_TYPEDEF)46)        /*Each group of 4 GPIOs is mapped to TCK/TMS/TDI/TDO*/
#define JTAG_RV_TDO             ((GPIO_FUN_TYPEDEF)46)        /*Each group of 4 GPIOs is mapped to TCK/TMS/TDI/TDO*/
#define I2C0_SCL                ((GPIO_FUN_TYPEDEF)58)
#define I2C0_SDA                ((GPIO_FUN_TYPEDEF)59)
#define I2C1_SCL                ((GPIO_FUN_TYPEDEF)47)
#define I2C1_SDA                ((GPIO_FUN_TYPEDEF)47)
#define SCI7816_IO              ((GPIO_FUN_TYPEDEF)56)
#define SCI7816_IO2             ((GPIO_FUN_TYPEDEF)51)
#define NFC_CLK_OUT             ((GPIO_FUN_TYPEDEF)55)
#define ICE                     ((GPIO_FUN_TYPEDEF)57)
#define JTAG_SWCLK              ((GPIO_FUN_TYPEDEF)60)        /*The first 16 pins are mapped to SWCLK, and the latter pins are mapped to SWCLK/SWDIO for a group of 2 GPIOs*/
#define JTAG_SWDIO              ((GPIO_FUN_TYPEDEF)61)        /*The first 16 pins are mapped to SWDIO*/
#define OUTPUT_LOW              ((GPIO_FUN_TYPEDEF)62)
#define OUTPUT_HIGH             ((GPIO_FUN_TYPEDEF)63)
#define PULL_PU                 ((GPIO_FUN_TYPEDEF)64)
#define PULL_PD                 ((GPIO_FUN_TYPEDEF)128)
#define ANALOG                  ((GPIO_FUN_TYPEDEF)192)
#define IS_GPIO_FUN(fun) (fun <= 0xff)

#define IS_GPIO_MODE(mode)  (((mode) == GPIO_Mode_IN_FLOATING) || \
                            ((mode) == GPIO_Mode_IPU)         || \
                            ((mode) == GPIO_Mode_IPD)         || \
                            ((mode) == GPIO_Mode_AIN)         || \
                            ((mode) == GPIO_Mode_Out_PP))

/**
 * @brief Bit_SET and Bit_RESET enumeration
 */
typedef enum
{
    Bit_RESET = 0,
    Bit_SET   = 1
} BitAction;

/**
 * @brief Configuration Mode enumeration
 */
typedef enum
{
    GPIO_Mode_IN_FLOATING = 0x00,
    GPIO_Mode_IPU         = 0x01,
    GPIO_Mode_IPD         = 0x02,
    GPIO_Mode_AIN         = 0x03,
    GPIO_Mode_Out_PP      = 0x3E    /*!< analog signal mode */
} GPIO_ModeTypeDef;

/**
  * @brief Configuration GPIO OD enumeration
  */
typedef enum
{
    GPIO_Mode_OD_RESET  = 0x0,
    GPIO_Mode_OD_SET    = 0x1
} GPIO_ODTypeDef;

#define IS_GPIO_MODE_OUT(mode)     (((mode) == GPIO_Mode_OD_RESET) || \
                                    ((mode) == GPIO_Mode_OD_SET))

/**
 * @brief  GPIO Init structure definition
 */
typedef struct
{
    GPIO_Pin_TypeDef GPIO_Pin;
    GPIO_ModeTypeDef GPIO_Mode;
} GPIO_InitTypeDef;

uint32_t GPIO_GetGPIONum(GPIO_TypeDef GPIOx);
void GPIO_Config(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef GPIO_Pin, GPIO_FUN_TYPEDEF function);
void GPIO_Init(GPIO_TypeDef GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_PullUpCmd(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef GPIO_Pin, FunctionalState NewState);
uint16_t GPIO_ReadInputData(GPIO_TypeDef GPIOx);
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef GPIO_Pin);
void GPIO_ResetBit(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin);
void GPIO_SetBit(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef GPIO_Pin);
void GPIO_SetBits(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin);
void GPIO_Write(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef GPIO_Pin, BitAction BitVal);
void GPIO_ODSet(uint8_t GPIOx_OD, GPIO_ODTypeDef GPIO_OD_Set);

#ifdef __cplusplus
}
#endif

#endif  /* __YC_GPIO_H__ */

/************************ (C) COPYRIGHT Yichip Microelectronics *****END OF FILE****/
