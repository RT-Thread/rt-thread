/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-11     RT-Thread    the first version
 */
#include "rtthread.h"
#include "stm32f4xx_hal.h"
#include "ili9341.h"

/**
  * @brief  LCD Control pin
  */
#define LCD_NCS_PIN                             GPIO_PIN_2
#define LCD_NCS_GPIO_PORT                       GPIOC
#define LCD_NCS_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOC_CLK_ENABLE()
#define LCD_NCS_GPIO_CLK_DISABLE()              __HAL_RCC_GPIOC_CLK_DISABLE()

/**
  * @brief  LCD Command/data pin
  */
#define LCD_WRX_PIN                             GPIO_PIN_13
#define LCD_WRX_GPIO_PORT                       GPIOD
#define LCD_WRX_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOD_CLK_ENABLE()
#define LCD_WRX_GPIO_CLK_DISABLE()              __HAL_RCC_GPIOD_CLK_DISABLE()

#define LCD_RDX_PIN                             GPIO_PIN_12
#define LCD_RDX_GPIO_PORT                       GPIOD
#define LCD_RDX_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOD_CLK_ENABLE()
#define LCD_RDX_GPIO_CLK_DISABLE()              __HAL_RCC_GPIOD_CLK_DISABLE()

/* Maximum Timeout values for flags waiting loops */
#define SPIx_TIMEOUT_MAX              ((uint32_t)0x1000)

/* Chip Select macro definition */
#define LCD_CS_LOW()       HAL_GPIO_WritePin(LCD_NCS_GPIO_PORT, LCD_NCS_PIN, GPIO_PIN_RESET)
#define LCD_CS_HIGH()      HAL_GPIO_WritePin(LCD_NCS_GPIO_PORT, LCD_NCS_PIN, GPIO_PIN_SET)

/* Set WRX High to send data */
#define LCD_WRX_LOW()      HAL_GPIO_WritePin(LCD_WRX_GPIO_PORT, LCD_WRX_PIN, GPIO_PIN_RESET)
#define LCD_WRX_HIGH()     HAL_GPIO_WritePin(LCD_WRX_GPIO_PORT, LCD_WRX_PIN, GPIO_PIN_SET)

/* Set WRX High to send data */
#define LCD_RDX_LOW()      HAL_GPIO_WritePin(LCD_RDX_GPIO_PORT, LCD_RDX_PIN, GPIO_PIN_RESET)
#define LCD_RDX_HIGH()     HAL_GPIO_WritePin(LCD_RDX_GPIO_PORT, LCD_RDX_PIN, GPIO_PIN_SET)

static uint8_t Is_LCD_IO_Initialized = 0;
static SPI_HandleTypeDef SpiHandle;

/**
  * @brief  SPIx Bus initialization
  */
static void SPIx_Init(void)
{
  if(HAL_SPI_GetState(&SpiHandle) == HAL_SPI_STATE_RESET)
  {
    /* SPI configuration -----------------------------------------------------*/
    SpiHandle.Instance = SPI5;
    /* SPI baudrate is set to 5.6 MHz (PCLK2/SPI_BaudRatePrescaler = 90/16 = 5.625 MHz)
    */
    SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;

    /* On STM32F429I-Discovery, LCD ID cannot be read then keep a common configuration */
    /* for LCD and GYRO (SPI_DIRECTION_2LINES) */
    /* Note: To read a register a LCD, SPI_DIRECTION_1LINE should be set */
    SpiHandle.Init.Direction      = SPI_DIRECTION_2LINES;
    SpiHandle.Init.CLKPhase       = SPI_PHASE_1EDGE;
    SpiHandle.Init.CLKPolarity    = SPI_POLARITY_LOW;
    SpiHandle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
    SpiHandle.Init.CRCPolynomial  = 7;
    SpiHandle.Init.DataSize       = SPI_DATASIZE_8BIT;
    SpiHandle.Init.FirstBit       = SPI_FIRSTBIT_MSB;
    SpiHandle.Init.NSS            = SPI_NSS_SOFT;
    SpiHandle.Init.TIMode         = SPI_TIMODE_DISABLED;
    SpiHandle.Init.Mode           = SPI_MODE_MASTER;

    HAL_SPI_Init(&SpiHandle);
  }
}

/**
  * @brief  Configures the LCD_SPI interface.
  */
static void LCD_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  if(Is_LCD_IO_Initialized == 0)
  {
    Is_LCD_IO_Initialized = 1;

    /* Configure NCS in Output Push-Pull mode */
    LCD_WRX_GPIO_CLK_ENABLE();
    GPIO_InitStructure.Pin     = LCD_WRX_PIN;
    GPIO_InitStructure.Mode    = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull    = GPIO_NOPULL;
    GPIO_InitStructure.Speed   = GPIO_SPEED_FAST;
    HAL_GPIO_Init(LCD_WRX_GPIO_PORT, &GPIO_InitStructure);

    LCD_RDX_GPIO_CLK_ENABLE();
    GPIO_InitStructure.Pin     = LCD_RDX_PIN;
    GPIO_InitStructure.Mode    = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull    = GPIO_NOPULL;
    GPIO_InitStructure.Speed   = GPIO_SPEED_FAST;
    HAL_GPIO_Init(LCD_RDX_GPIO_PORT, &GPIO_InitStructure);

    /* Configure the LCD Control pins ----------------------------------------*/
    LCD_NCS_GPIO_CLK_ENABLE();

    /* Configure NCS in Output Push-Pull mode */
    GPIO_InitStructure.Pin     = LCD_NCS_PIN;
    GPIO_InitStructure.Mode    = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull    = GPIO_NOPULL;
    GPIO_InitStructure.Speed   = GPIO_SPEED_FAST;
    HAL_GPIO_Init(LCD_NCS_GPIO_PORT, &GPIO_InitStructure);

    /* Set or Reset the control line */
    LCD_CS_LOW();
    LCD_CS_HIGH();

    SPIx_Init();
  }
}

/**
  * @brief  Writes data to the selected LCD register.
  * @param  data: data to lcd.
  * @retval None
  */
static void ili9341_write_data(uint16_t data)
{
  /* Set WRX to send data */
  LCD_WRX_HIGH();

  /* Reset LCD control line(/CS) and Send data */
  LCD_CS_LOW();

    HAL_SPI_Transmit(&SpiHandle, (uint8_t*) &data, 1, SPIx_TIMEOUT_MAX);

  /* Deselect: Chip Select high */
  LCD_CS_HIGH();
}

/**
  * @brief  Writes  to the selected LCD register.
  * @param  reg: address of the selected register.
  * @retval None
  */
static void ili9341_write_register(uint8_t reg)
{
  /* Reset WRX to send command */
  LCD_WRX_LOW();

  /* Reset LCD control line(/CS) and Send command */
  LCD_CS_LOW();

  HAL_SPI_Transmit(&SpiHandle, (uint8_t*) &reg, 1, SPIx_TIMEOUT_MAX);

  /* Deselect: Chip Select high */
  LCD_CS_HIGH();
}

/**
  * @brief  Power on the LCD.
  * @param  None
  * @retval int
  */
int ili9341_hw_init(void)
{
  /* Initialize ILI9341 low level bus layer ----------------------------------*/
  LCD_GPIO_Init();

  /* Configure LCD */
  ili9341_write_register(0xCA);
  ili9341_write_data(0xC3);
  ili9341_write_data(0x08);
  ili9341_write_data(0x50);
  ili9341_write_register(LCD_POWERB);
  ili9341_write_data(0x00);
  ili9341_write_data(0xC1);
  ili9341_write_data(0x30);
  ili9341_write_register(LCD_POWER_SEQ);
  ili9341_write_data(0x64);
  ili9341_write_data(0x03);
  ili9341_write_data(0x12);
  ili9341_write_data(0x81);
  ili9341_write_register(LCD_DTCA);
  ili9341_write_data(0x85);
  ili9341_write_data(0x00);
  ili9341_write_data(0x78);
  ili9341_write_register(LCD_POWERA);
  ili9341_write_data(0x39);
  ili9341_write_data(0x2C);
  ili9341_write_data(0x00);
  ili9341_write_data(0x34);
  ili9341_write_data(0x02);
  ili9341_write_register(LCD_PRC);
  ili9341_write_data(0x20);
  ili9341_write_register(LCD_DTCB);
  ili9341_write_data(0x00);
  ili9341_write_data(0x00);
  ili9341_write_register(LCD_FRMCTR1);
  ili9341_write_data(0x00);
  ili9341_write_data(0x1B);
  ili9341_write_register(LCD_DFC);
  ili9341_write_data(0x0A);
  ili9341_write_data(0xA2);
  ili9341_write_register(LCD_POWER1);
  ili9341_write_data(0x10);
  ili9341_write_register(LCD_POWER2);
  ili9341_write_data(0x10);
  ili9341_write_register(LCD_VCOM1);
  ili9341_write_data(0x45);
  ili9341_write_data(0x15);
  ili9341_write_register(LCD_VCOM2);
  ili9341_write_data(0x90);
  ili9341_write_register(LCD_MAC);
  ili9341_write_data(0xC8);
  ili9341_write_register(LCD_3GAMMA_EN);
  ili9341_write_data(0x00);
  ili9341_write_register(LCD_RGB_INTERFACE);
  ili9341_write_data(0xC2);
  ili9341_write_register(LCD_DFC);
  ili9341_write_data(0x0A);
  ili9341_write_data(0xA7);
  ili9341_write_data(0x27);
  ili9341_write_data(0x04);

  /* Colomn address set */
  ili9341_write_register(LCD_COLUMN_ADDR);
  ili9341_write_data(0x00);
  ili9341_write_data(0x00);
  ili9341_write_data(0x00);
  ili9341_write_data(0xEF);
  /* Page address set */
  ili9341_write_register(LCD_PAGE_ADDR);
  ili9341_write_data(0x00);
  ili9341_write_data(0x00);
  ili9341_write_data(0x01);
  ili9341_write_data(0x3F);
  ili9341_write_register(LCD_INTERFACE);
  ili9341_write_data(0x01);
  ili9341_write_data(0x00);
  ili9341_write_data(0x06);

  ili9341_write_register(LCD_GRAM);
  rt_thread_mdelay(20);

  ili9341_write_register(LCD_GAMMA);
  ili9341_write_data(0x01);

  ili9341_write_register(LCD_PGAMMA);
  ili9341_write_data(0x0F);
  ili9341_write_data(0x29);
  ili9341_write_data(0x24);
  ili9341_write_data(0x0C);
  ili9341_write_data(0x0E);
  ili9341_write_data(0x09);
  ili9341_write_data(0x4E);
  ili9341_write_data(0x78);
  ili9341_write_data(0x3C);
  ili9341_write_data(0x09);
  ili9341_write_data(0x13);
  ili9341_write_data(0x05);
  ili9341_write_data(0x17);
  ili9341_write_data(0x11);
  ili9341_write_data(0x00);
  ili9341_write_register(LCD_NGAMMA);
  ili9341_write_data(0x00);
  ili9341_write_data(0x16);
  ili9341_write_data(0x1B);
  ili9341_write_data(0x04);
  ili9341_write_data(0x11);
  ili9341_write_data(0x07);
  ili9341_write_data(0x31);
  ili9341_write_data(0x33);
  ili9341_write_data(0x42);
  ili9341_write_data(0x05);
  ili9341_write_data(0x0C);
  ili9341_write_data(0x0A);
  ili9341_write_data(0x28);
  ili9341_write_data(0x2F);
  ili9341_write_data(0x0F);

  ili9341_write_register(LCD_SLEEP_OUT);
  rt_thread_mdelay(20);
  ili9341_write_register(LCD_DISPLAY_ON);
  /* GRAM start writing */
  ili9341_write_register(LCD_GRAM);

    return 0;
}
INIT_DEVICE_EXPORT(ili9341_hw_init);



