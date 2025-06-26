/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-23     koudaiNEW    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "n32g45x_gpio.h"
#include "n32g45x_dma.h"
#include "drv_usart_v2.h"

#ifdef RT_USING_SERIAL_V2
#if !defined(BSP_USING_USART1) && !defined(BSP_USING_USART2) && !defined(BSP_USING_USART3) && !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5) && !defined(BSP_USING_UART6) && !defined(BSP_USING_UART7) && !defined(BSP_USING_UART8) && !defined(BSP_USING_LPUART1)
#error "Please define at least one BSP_USING_UARTx"
/* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

/******************************* declare ****************************************************************************************** */
enum
{
#ifdef BSP_USING_USART1
    UART1_INDEX,
#endif
#ifdef BSP_USING_USART2
    UART2_INDEX,
#endif
#ifdef BSP_USING_USART3
    UART3_INDEX,
#endif
#ifdef BSP_USING_UART4
    UART4_INDEX,
#endif
#ifdef BSP_USING_UART5
    UART5_INDEX,
#endif
#ifdef BSP_USING_UART6
    UART6_INDEX,
#endif
#ifdef BSP_USING_UART7
    UART7_INDEX,
#endif
};

enum uart_afio_mode
{
#ifdef BSP_USING_USART1
    USART1_AFIO_MODE_PA9_PA10,
    USART1_AFIO_MODE_PB6_PB7,
#endif
#ifdef BSP_USING_USART2
    USART2_AFIO_MODE_PA2_PA3,
    USART2_AFIO_MODE_PD5_PD6,
    USART2_AFIO_MODE_PC8_PC9,
    USART2_AFIO_MODE_PB4_PB5,
#endif
#ifdef BSP_USING_USART3
    USART3_AFIO_MODE_PB10_PB11,
    USART3_AFIO_MODE_PC10_PC11,
    USART3_AFIO_MODE_PD8_PD9,
#endif
#ifdef BSP_USING_UART4
    UART4_AFIO_MODE_PC10_PC11,
    UART4_AFIO_MODE_PB2_PE7,
    UART4_AFIO_MODE_PA13_PA14,
    UART4_AFIO_MODE_PD0_PD1,
#endif
#ifdef BSP_USING_UART5
    UART5_AFIO_MODE_PC12_PD2,
    UART5_AFIO_MODE_PB13_PB14,
    UART5_AFIO_MODE_PE8_PE9,
    UART5_AFIO_MODE_PB8_PB9,
#endif
#ifdef BSP_USING_UART6
    UART6_AFIO_MODE_PE2_PE3,
    UART6_AFIO_MODE_PC0_PC1,
    UART6_AFIO_MODE_PB0_PB1,
#endif
#ifdef BSP_USING_UART7
    UART7_AFIO_MODE_PC4_PC5,
    UART7_AFIO_MODE_PC2_PC3,
    UART7_AFIO_MODE_PG0_PG1,
#endif
};

struct DMA_HandleTypeDef
{
    DMA_ChannelType           *Instance; /* DMA registers base address */
    struct UART_HandleTypeDef *Parent;
    DMA_InitType               Init;     /* DMA initialization parameters */
    rt_uint32_t                dma_rcc;
    IRQn_Type                  dma_irq;
    void (*DMA_ITC_Callback)(void); /* DMA transfer complete callback */
    void (*DMA_IE_Callback)(void);  /* DMA error complete callback */
};

struct UART_HandleTypeDef
{
    USART_Module             *Instance; /*!< UART registers base address        */
    USART_InitType            Init;     /*!< UART communication parameters      */
    struct DMA_HandleTypeDef *HDMA_Tx;  /*!< UART Tx DMA handle parameters */
    struct DMA_HandleTypeDef *HDMA_Rx;  /*!< UART Rx DMA handle parameters */
};

struct n32_uart_config
{
    const char   *name;
    USART_Module *Instance;
    IRQn_Type     irq_type;
    GPIO_Module  *tx_port;
    uint16_t      tx_pin;
    GPIO_Module  *rx_port;
    uint16_t      rx_pin;
    unsigned char use_afio_mode;
};

struct n32_uart
{
    struct UART_HandleTypeDef handle;
    struct n32_uart_config   *config;
#ifdef RT_SERIAL_USING_DMA
    struct
    {
        struct DMA_HandleTypeDef handle;
        rt_size_t                remaining_cnt;
    } dma_rx;
    struct
    {
        struct DMA_HandleTypeDef handle;
    } dma_tx;
#endif
    rt_uint16_t             uart_dma_flag;
    struct rt_serial_device serial;
};
/********************************************************************************************************************************** */
/******************************* funtion ****************************************************************************************** */
static void     n32_uart_mode_set(struct n32_uart_config *uart);
static void     n32_uart_get_config(void);
static rt_err_t n32_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static void     NVIC_Set(IRQn_Type irq, FunctionalState state);
#ifdef RT_SERIAL_USING_DMA
static void n32_uart_dma_config(struct rt_serial_device *serial, rt_ubase_t flag);
#endif
void HAL_UART_TxCpltCallback(struct UART_HandleTypeDef *huart);
static void GPIOInit(GPIO_Module* GPIOx, GPIO_ModeType mode, GPIO_SpeedType speed, uint16_t Pin);
/********************************************************************************************************************************** */
/******************************** value ******************************************************************************************* */
static struct n32_uart_config uart_config[] =
    {
#ifdef BSP_USING_USART1
        {
                               .name = "usart1",
#if defined BSP_USART1_AFIO_MODE_PA9_PA10
                               .use_afio_mode = USART1_AFIO_MODE_PA9_PA10,
#elif defined BSP_USART1_AFIO_MODE_PB6_PB7
            .use_afio_mode = USART1_AFIO_MODE_PB6_PB7,
#endif
                               },
#endif
#ifdef BSP_USING_USART2
        {
                               .name = "usart2",
#if defined BSP_USART2_AFIO_MODE_PA2_PA3
                               .use_afio_mode = USART2_AFIO_MODE_PA2_PA3,
#elif defined BSP_USART2_AFIO_MODE_PD5_PD6
            .use_afio_mode = USART2_AFIO_MODE_PD5_PD6,
#elif defined BSP_USART2_AFIO_MODE_PC8_PC9
            .use_afio_mode = USART2_AFIO_MODE_PC8_PC9,
#elif defined BSP_USART2_AFIO_MODE_PB4_PB5
            .use_afio_mode = USART2_AFIO_MODE_PB4_PB5,
#endif
                               },
#endif
#ifdef BSP_USING_USART3
        {
                               .name = "usart3",
#if defined BSP_USART3_AFIO_MODE_PB10_PB11
                               .use_afio_mode = USART3_AFIO_MODE_PB10_PB11,
#elif defined BSP_USART3_AFIO_MODE_PC10_PC11
            .use_afio_mode = USART3_AFIO_MODE_PC10_PC11,
#elif defined BSP_USART3_AFIO_MODE_PD8_PD9
            .use_afio_mode = USART3_AFIO_MODE_PD8_PD9,
#endif
                               },
#endif
#ifdef BSP_USING_UART4
        {
                               .name = "uart4",
#if defined BSP_UART4_AFIO_MODE_PC10_PC11
                               .use_afio_mode = UART4_AFIO_MODE_PC10_PC11,
#elif defined BSP_UART4_AFIO_MODE_PB2_PE7
            .use_afio_mode = UART4_AFIO_MODE_PB2_PE7,
#elif defined BSP_UART4_AFIO_MODE_PA13_PA14
            .use_afio_mode = UART4_AFIO_MODE_PA13_PA14,
#elif defined BSP_UART4_AFIO_MODE_PD0_PD1
            .use_afio_mode = UART4_AFIO_MODE_PD0_PD1,
#endif
                               },
#endif
#ifdef BSP_USING_UART5
        {
                               .name = "uart5",
#if defined BSP_UART5_AFIO_MODE_PC12_PD2
                               .use_afio_mode = UART5_AFIO_MODE_PC12_PD2,
#elif defined BSP_UART5_AFIO_MODE_PB13_PB14
            .use_afio_mode = UART5_AFIO_MODE_PB13_PB14,
#elif defined BSP_UART5_AFIO_MODE_PE8_PE9
            .use_afio_mode = UART5_AFIO_MODE_PE8_PE9,
#elif defined BSP_UART5_AFIO_MODE_PB8_PB9
            .use_afio_mode = UART5_AFIO_MODE_PB8_PB9,
#endif
                               },
#endif
#ifdef BSP_USING_UART6
        {
                               .name = "uart6",
#if defined BSP_UART6_AFIO_MODE_PE2_PE3
                               .use_afio_mode = UART6_AFIO_MODE_PE2_PE3,
#elif defined BSP_UART6_AFIO_MODE_PC0_PC1
            .use_afio_mode = UART6_AFIO_MODE_PC0_PC1,
#elif defined BSP_UART6_AFIO_MODE_PB0_PB1
            .use_afio_mode = UART6_AFIO_MODE_PB0_PB1,
#endif
                               },
#endif
#ifdef BSP_USING_UART7
        {
                               .name = "uart7",
#if defined BSP_UART7_AFIO_MODE_PC4_PC5
                               .use_afio_mode = UART7_AFIO_MODE_PC4_PC5,
#elif defined BSP_UART7_AFIO_MODE_PC2_PC3
            .use_afio_mode = UART7_AFIO_MODE_PC2_PC3,
#elif defined BSP_UART6_AFIO_MODE_PG0_PG1
            .use_afio_mode = UART7_AFIO_MODE_PG0_PG1,
#endif
                               },
#endif
};

static struct n32_uart uart_obj[sizeof(uart_config) / sizeof(struct n32_uart_config)];
/********************************************************************************************************************************** */

static void GPIOInit(GPIO_Module* GPIOx, GPIO_ModeType mode, GPIO_SpeedType speed, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    /* Enable the GPIO Clock */
    if (GPIOx == GPIOA)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    }
    else if (GPIOx == GPIOD)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
    }
    else if (GPIOx == GPIOE)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOE, ENABLE);
    }
    else if (GPIOx == GPIOF)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOF, ENABLE);
    }
    else
    {
        if (GPIOx == GPIOG)
        {
            RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOG, ENABLE);
        }
    }
    /* Configure the GPIO pin */
    GPIO_InitStructure.Pin        = Pin;
    GPIO_InitStructure.GPIO_Mode  = mode;
    GPIO_InitStructure.GPIO_Speed = speed;
    GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
}

static void n32_uart_mode_set(struct n32_uart_config *uart)
{
    switch (uart->use_afio_mode)
    {
#if defined BSP_USING_USART1
    /* usart1 */
    case USART1_AFIO_MODE_PA9_PA10:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_USART1 | RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIOInit(GPIOA, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_9);
        GPIOInit(GPIOA, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_10);
        NVIC_SetPriority(USART1_IRQn, 0);
        /* save gpio data */
        uart->Instance = USART1;
        uart->irq_type = USART1_IRQn;
        uart->tx_port  = GPIOA;
        uart->tx_pin   = GPIO_PIN_9;
        uart->rx_port  = GPIOA;
        uart->rx_pin   = GPIO_PIN_10;
        break;

    case USART1_AFIO_MODE_PB6_PB7:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_USART1 | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP_USART1, ENABLE);
        GPIOInit(GPIOB, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_6);
        GPIOInit(GPIOB, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_7);
        NVIC_SetPriority(USART1_IRQn, 0);
        /* save gpio data */
        uart->Instance = USART1;
        uart->irq_type = USART1_IRQn;
        uart->tx_port  = GPIOB;
        uart->tx_pin   = GPIO_PIN_6;
        uart->rx_port  = GPIOB;
        uart->rx_pin   = GPIO_PIN_7;
        break;
#endif

#if defined BSP_USING_USART2
    /* usart2 */
    case USART2_AFIO_MODE_PA2_PA3:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_AFIO, ENABLE);
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART2, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP_USART2, DISABLE);
        GPIO_ConfigPinRemap(GPIO_RMP1_USART2, DISABLE);
        GPIOInit(GPIOA, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_2);
        GPIOInit(GPIOA, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_3);
        NVIC_SetPriority(USART2_IRQn, 0);
        /* save gpio data */
        uart->Instance = USART2;
        uart->irq_type = USART2_IRQn;
        uart->tx_port  = GPIOA;
        uart->tx_pin   = GPIO_PIN_2;
        uart->rx_port  = GPIOA;
        uart->rx_pin   = GPIO_PIN_3;
        break;

    case USART2_AFIO_MODE_PD5_PD6:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD | RCC_APB2_PERIPH_AFIO, ENABLE);
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART2, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP_USART2, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP1_USART2, ENABLE);
        GPIOInit(GPIOD, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_5);
        GPIOInit(GPIOD, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_6);
        NVIC_SetPriority(USART2_IRQn, 0);
        /* save gpio data */
        uart->Instance = USART2;
        uart->irq_type = USART2_IRQn;
        uart->tx_port  = GPIOD;
        uart->tx_pin   = GPIO_PIN_5;
        uart->rx_port  = GPIOD;
        uart->rx_pin   = GPIO_PIN_6;
        break;

    case USART2_AFIO_MODE_PC8_PC9:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_AFIO, ENABLE);
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART2, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP_USART2, DISABLE);
        GPIO_ConfigPinRemap(GPIO_RMP1_USART2, ENABLE);
        GPIOInit(GPIOC, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_8);
        GPIOInit(GPIOC, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_9);
        NVIC_SetPriority(USART2_IRQn, 0);
        /* save gpio data */
        uart->Instance = USART2;
        uart->irq_type = USART2_IRQn;
        uart->tx_port  = GPIOC;
        uart->tx_pin   = GPIO_PIN_8;
        uart->rx_port  = GPIOC;
        uart->rx_pin   = GPIO_PIN_9;
        break;

    case USART2_AFIO_MODE_PB4_PB5:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART2, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP_USART2, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP1_USART2, ENABLE);
        GPIOInit(GPIOB, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_4);
        GPIOInit(GPIOB, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_5);
        NVIC_SetPriority(USART2_IRQn, 0);
        /* save gpio data */
        uart->Instance = USART2;
        uart->irq_type = USART2_IRQn;
        uart->tx_port  = GPIOB;
        uart->tx_pin   = GPIO_PIN_4;
        uart->rx_port  = GPIOB;
        uart->rx_pin   = GPIO_PIN_5;
        break;
#endif

#if defined BSP_USING_USART3
    /* usart3 */
    case USART3_AFIO_MODE_PB10_PB11:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART3, ENABLE);
        GPIO_ConfigPinRemap(GPIO_ALL_RMP_USART3, DISABLE);
        GPIOInit(GPIOB, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_10);
        GPIOInit(GPIOB, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_11);
        NVIC_SetPriority(USART3_IRQn, 0);
        /* save gpio data */
        uart->Instance = USART3;
        uart->irq_type = USART3_IRQn;
        uart->tx_port  = GPIOB;
        uart->tx_pin   = GPIO_PIN_10;
        uart->rx_port  = GPIOB;
        uart->rx_pin   = GPIO_PIN_11;
        break;

    case USART3_AFIO_MODE_PC10_PC11:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_AFIO, ENABLE);
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART3, ENABLE);
        GPIO_ConfigPinRemap(GPIO_PART_RMP_USART3, ENABLE);
        GPIOInit(GPIOC, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_10);
        GPIOInit(GPIOC, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_11);
        NVIC_SetPriority(USART3_IRQn, 0);
        /* save gpio data */
        uart->Instance = USART3;
        uart->irq_type = USART3_IRQn;
        uart->tx_port  = GPIOC;
        uart->tx_pin   = GPIO_PIN_10;
        uart->rx_port  = GPIOC;
        uart->rx_pin   = GPIO_PIN_11;
        break;

    case USART3_AFIO_MODE_PD8_PD9:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD | RCC_APB2_PERIPH_AFIO, ENABLE);
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART3, ENABLE);
        GPIO_ConfigPinRemap(GPIO_ALL_RMP_USART3, ENABLE);
        GPIOInit(GPIOD, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_8);
        GPIOInit(GPIOD, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_9);
        NVIC_SetPriority(USART3_IRQn, 0);
        /* save gpio data */
        uart->Instance = USART3;
        uart->irq_type = USART3_IRQn;
        uart->tx_port  = GPIOD;
        uart->tx_pin   = GPIO_PIN_8;
        uart->rx_port  = GPIOD;
        uart->rx_pin   = GPIO_PIN_9;
        break;
#endif

#if defined BSP_USING_UART4
    /* uart4 */
    case UART4_AFIO_MODE_PC10_PC11:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_AFIO, ENABLE);
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_UART4, ENABLE);
        AFIO->RMP_CFG3 &= ~0x300000;
        GPIOInit(GPIOC, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_10);
        GPIOInit(GPIOC, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_11);
        NVIC_SetPriority(UART4_IRQn, 0);
        /* save gpio data */
        uart->Instance = UART4;
        uart->irq_type = UART4_IRQn;
        uart->tx_port  = GPIOC;
        uart->tx_pin   = GPIO_PIN_10;
        uart->rx_port  = GPIOC;
        uart->rx_pin   = GPIO_PIN_11;
        break;

    case UART4_AFIO_MODE_PB2_PE7:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOE | RCC_APB2_PERIPH_AFIO, ENABLE);
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_UART4, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP1_UART4, ENABLE);
        GPIOInit(GPIOB, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_2);
        GPIOInit(GPIOE, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_7);
        NVIC_SetPriority(UART4_IRQn, 0);
        /* save gpio data */
        uart->Instance = UART4;
        uart->irq_type = UART4_IRQn;
        uart->tx_port  = GPIOB;
        uart->tx_pin   = GPIO_PIN_2;
        uart->rx_port  = GPIOE;
        uart->rx_pin   = GPIO_PIN_7;
        break;

    case UART4_AFIO_MODE_PA13_PA14:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_AFIO, ENABLE);
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_UART4, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP2_UART4, ENABLE);
        GPIOInit(GPIOA, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_13);
        GPIOInit(GPIOA, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_14);
        NVIC_SetPriority(UART4_IRQn, 0);
        /* save gpio data */
        uart->Instance = UART4;
        uart->irq_type = UART4_IRQn;
        uart->tx_port  = GPIOA;
        uart->tx_pin   = GPIO_PIN_13;
        uart->rx_port  = GPIOA;
        uart->rx_pin   = GPIO_PIN_14;
        break;

    case UART4_AFIO_MODE_PD0_PD1:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD | RCC_APB2_PERIPH_AFIO, ENABLE);
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_UART4, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP3_UART4, ENABLE);
        GPIOInit(GPIOD, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_0);
        GPIOInit(GPIOD, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_1);
        NVIC_SetPriority(UART4_IRQn, 0);
        /* save gpio data */
        uart->Instance = UART4;
        uart->irq_type = UART4_IRQn;
        uart->tx_port  = GPIOD;
        uart->tx_pin   = GPIO_PIN_0;
        uart->rx_port  = GPIOD;
        uart->rx_pin   = GPIO_PIN_1;
        break;
#endif

#if defined BSP_USING_UART5
    /* uart5 */
    case UART5_AFIO_MODE_PC12_PD2:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOD | RCC_APB2_PERIPH_AFIO, ENABLE);
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_UART5, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP3_UART5, DISABLE);
        GPIOInit(GPIOC, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_12);
        GPIOInit(GPIOD, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_2);
        NVIC_SetPriority(UART5_IRQn, 0);
        /* save gpio data */
        uart->Instance = UART5;
        uart->irq_type = UART5_IRQn;
        uart->tx_port  = GPIOC;
        uart->tx_pin   = GPIO_PIN_12;
        uart->rx_port  = GPIOD;
        uart->rx_pin   = GPIO_PIN_2;
        break;

    case UART5_AFIO_MODE_PB13_PB14:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_UART5, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP1_UART5, ENABLE);
        GPIOInit(GPIOB, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_13);
        GPIOInit(GPIOB, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_14);
        NVIC_SetPriority(UART5_IRQn, 0);
        /* save gpio data */
        uart->Instance = UART5;
        uart->irq_type = UART5_IRQn;
        uart->tx_port  = GPIOB;
        uart->tx_pin   = GPIO_PIN_13;
        uart->rx_port  = GPIOB;
        uart->rx_pin   = GPIO_PIN_14;
        break;

    case UART5_AFIO_MODE_PE8_PE9:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOE | RCC_APB2_PERIPH_AFIO, ENABLE);
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_UART5, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP2_UART5, ENABLE);
        GPIOInit(GPIOE, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_8);
        GPIOInit(GPIOE, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_9);
        NVIC_SetPriority(UART5_IRQn, 0);
        /* save gpio data */
        uart->Instance = UART5;
        uart->irq_type = UART5_IRQn;
        uart->tx_port  = GPIOE;
        uart->tx_pin   = GPIO_PIN_8;
        uart->rx_port  = GPIOE;
        uart->rx_pin   = GPIO_PIN_9;
        break;

    case UART5_AFIO_MODE_PB8_PB9:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_UART5, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP3_UART5, ENABLE);
        GPIOInit(GPIOB, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_8);
        GPIOInit(GPIOB, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_9);
        NVIC_SetPriority(UART5_IRQn, 0);
        /* save gpio data */
        uart->Instance = UART5;
        uart->irq_type = UART5_IRQn;
        uart->tx_port  = GPIOB;
        uart->tx_pin   = GPIO_PIN_8;
        uart->rx_port  = GPIOB;
        uart->rx_pin   = GPIO_PIN_9;
        break;
#endif

#if defined BSP_USING_UART6
    /* uart6 */
    case UART6_AFIO_MODE_PE2_PE3:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOE | RCC_APB2_PERIPH_UART6 | RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP3_UART6, DISABLE);
        GPIOInit(GPIOE, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_2);
        GPIOInit(GPIOE, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_3);
        NVIC_SetPriority(UART6_IRQn, 0);
        /* save gpio data */
        uart->Instance = UART6;
        uart->irq_type = UART6_IRQn;
        uart->tx_port  = GPIOE;
        uart->tx_pin   = GPIO_PIN_2;
        uart->rx_port  = GPIOE;
        uart->rx_pin   = GPIO_PIN_3;
        break;

    case UART6_AFIO_MODE_PC0_PC1:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_UART6 | RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP2_UART6, ENABLE);
        GPIOInit(GPIOC, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_0);
        GPIOInit(GPIOC, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_1);
        NVIC_SetPriority(UART6_IRQn, 0);
        /* save gpio data */
        uart->Instance = UART6;
        uart->irq_type = UART6_IRQn;
        uart->tx_port  = GPIOC;
        uart->tx_pin   = GPIO_PIN_0;
        uart->rx_port  = GPIOC;
        uart->rx_pin   = GPIO_PIN_1;
        break;

    case UART6_AFIO_MODE_PB0_PB1:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_UART6 | RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP3_UART6, ENABLE);
        GPIOInit(GPIOB, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_0);
        GPIOInit(GPIOB, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_1);
        NVIC_SetPriority(UART6_IRQn, 0);
        /* save gpio data */
        uart->Instance = UART6;
        uart->irq_type = UART6_IRQn;
        uart->tx_port  = GPIOB;
        uart->tx_pin   = GPIO_PIN_0;
        uart->rx_port  = GPIOB;
        uart->rx_pin   = GPIO_PIN_1;
        break;
#endif

#if defined BSP_USING_UART7
    /* uart7 */
    case UART7_AFIO_MODE_PC4_PC5:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_UART7 | RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP3_UART7, DISABLE);
        GPIOInit(GPIOC, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_4);
        GPIOInit(GPIOC, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_5);
        NVIC_SetPriority(UART7_IRQn, 0);
        /* save gpio data */
        uart->Instance = UART7;
        uart->irq_type = UART7_IRQn;
        uart->tx_port  = GPIOC;
        uart->tx_pin   = GPIO_PIN_4;
        uart->rx_port  = GPIOC;
        uart->rx_pin   = GPIO_PIN_5;
        break;

    case UART7_AFIO_MODE_PC2_PC3:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_UART7 | RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP1_UART7, ENABLE);
        GPIOInit(GPIOC, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_2);
        GPIOInit(GPIOC, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_3);
        NVIC_SetPriority(UART7_IRQn, 0);
        /* save gpio data */
        uart->Instance = UART7;
        uart->irq_type = UART7_IRQn;
        uart->tx_port  = GPIOC;
        uart->tx_pin   = GPIO_PIN_2;
        uart->rx_port  = GPIOC;
        uart->rx_pin   = GPIO_PIN_3;
        break;

    case UART7_AFIO_MODE_PG0_PG1:
        /* enable GPIO USART AFIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOG | RCC_APB2_PERIPH_UART7 | RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP3_UART7, ENABLE);
        GPIOInit(GPIOG, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, GPIO_PIN_0);
        GPIOInit(GPIOG, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, GPIO_PIN_1);
        NVIC_SetPriority(UART7_IRQn, 0);
        /* save gpio data */
        uart->Instance = UART7;
        uart->irq_type = UART7_IRQn;
        uart->tx_port  = GPIOG;
        uart->tx_pin   = GPIO_PIN_0;
        uart->rx_port  = GPIOG;
        uart->rx_pin   = GPIO_PIN_1;
        break;
#endif
    default:
        break;
    }
}


static rt_err_t n32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = rt_container_of(serial, struct n32_uart, serial);
    n32_uart_mode_set(uart->config);
    uart->handle.Init.BaudRate = cfg->baud_rate;

    switch (cfg->data_bits)
    {
    case DATA_BITS_9:
        uart->handle.Init.WordLength = USART_WL_9B;
        break;

    default:
        uart->handle.Init.WordLength = USART_WL_8B;
        ;
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart->handle.Init.StopBits = USART_STPB_1;
        break;
    case STOP_BITS_2:
        uart->handle.Init.StopBits = USART_STPB_0_5;
        break;
    case STOP_BITS_3:
        uart->handle.Init.StopBits = USART_STPB_2;
        break;
    case STOP_BITS_4:
        uart->handle.Init.StopBits = USART_STPB_1_5;
        break;
    default:
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_ODD:
        uart->handle.Init.Parity = USART_PE_ODD;
        break;
    case PARITY_EVEN:
        uart->handle.Init.Parity = USART_PE_EVEN;
        break;
    case PARITY_NONE:
        uart->handle.Init.Parity = USART_PE_NO;
        break;
    default:
        break;
    }

    switch (cfg->flowcontrol)
    {
    case RT_SERIAL_FLOWCONTROL_NONE:
        uart->handle.Init.HardwareFlowControl = USART_HFCTRL_NONE;
        break;
    case RT_SERIAL_FLOWCONTROL_CTSRTS:
        uart->handle.Init.HardwareFlowControl = USART_HFCTRL_RTS_CTS;
        break;
    default:
        uart->handle.Init.HardwareFlowControl = USART_HFCTRL_NONE;
        break;
    }
    uart->handle.Init.Mode = USART_MODE_TX | USART_MODE_RX;
    USART_DeInit(uart->handle.Instance);
    USART_Init(uart->handle.Instance, &uart->handle.Init);
    USART_Enable(uart->handle.Instance, ENABLE);
#ifdef RT_SERIAL_USING_DMA
    uart->dma_rx.remaining_cnt = serial->config.dma_ping_bufsz;
#endif

    return RT_EOK;
}

/**
 * @brief  Configures the nested vectored interrupt controller.
 */
static void NVIC_Set(IRQn_Type irq, FunctionalState state)
{
    if (state == ENABLE)
    {
        NVIC_SetPriority(irq, 0);
        NVIC_EnableIRQ(irq);
    }
    else if (state == DISABLE)
    {
        NVIC_DisableIRQ(irq);
    }
}

static rt_err_t n32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct n32_uart *uart;
    rt_ubase_t       ctrl_arg = (rt_ubase_t)arg;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct n32_uart, serial);
    if (ctrl_arg & (RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_RX_NON_BLOCKING))
    {
        if (uart->uart_dma_flag & RT_DEVICE_FLAG_DMA_RX)
            ctrl_arg = RT_DEVICE_FLAG_DMA_RX;
        else
            ctrl_arg = RT_DEVICE_FLAG_INT_RX;
    }
    else if (ctrl_arg & (RT_DEVICE_FLAG_TX_BLOCKING | RT_DEVICE_FLAG_TX_NON_BLOCKING))
    {
        if (uart->uart_dma_flag & RT_DEVICE_FLAG_DMA_TX)
            ctrl_arg = RT_DEVICE_FLAG_DMA_TX;
        else
            ctrl_arg = RT_DEVICE_FLAG_INT_TX;
    }

    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        // NVIC_DisableIRQ(uart->config->irq_type);
        NVIC_Set(uart->config->irq_type, DISABLE);
        if (ctrl_arg & RT_DEVICE_FLAG_INT_RX)
        {
            USART_ConfigInt(uart->handle.Instance, USART_INT_RXDNE, DISABLE);
            USART_ClrFlag(uart->handle.Instance, USART_FLAG_RXDNE);
        }
        if (ctrl_arg & RT_DEVICE_FLAG_INT_TX)
        {
            USART_ConfigInt(uart->handle.Instance, USART_INT_TXDE, DISABLE);
            USART_ConfigInt(uart->handle.Instance, USART_INT_TXC, DISABLE);
            USART_ClrFlag(uart->handle.Instance, USART_FLAG_TXDE);
        }
#ifdef RT_SERIAL_USING_DMA
        if (ctrl_arg & RT_DEVICE_FLAG_DMA_RX)
        {
            USART_ConfigInt(uart->handle.Instance, USART_FLAG_RXDNE, DISABLE);
            USART_ConfigInt(uart->handle.Instance, USART_FLAG_IDLEF, DISABLE);
            USART_ClrFlag(uart->handle.Instance, USART_FLAG_RXDNE);
            DMA_DeInit(uart->dma_rx.handle.Instance);
        }
        if (ctrl_arg & RT_DEVICE_FLAG_DMA_TX)
        {
            USART_ConfigInt(uart->handle.Instance, USART_INT_TXC, DISABLE);
            USART_ClrFlag(uart->handle.Instance, USART_FLAG_TXC);
            DMA_DeInit(uart->dma_tx.handle.Instance);
        }
#endif
        break;

    case RT_DEVICE_CTRL_CONFIG:
#ifdef RT_SERIAL_USING_DMA
        if (ctrl_arg & (RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX))
        {
            n32_uart_dma_config(serial, ctrl_arg);
            break;
        }
#endif
    case RT_DEVICE_CTRL_SET_INT:
        if (ctrl_arg & RT_DEVICE_FLAG_INT_RX)
        {
            USART_ClrFlag(uart->handle.Instance, USART_INT_RXDNE);
            USART_ConfigInt(uart->handle.Instance, USART_INT_RXDNE, ENABLE);
        }
        if (ctrl_arg & RT_DEVICE_FLAG_INT_TX)
        {
            USART_ClrFlag(uart->handle.Instance, USART_INT_TXC);
            USART_ConfigInt(uart->handle.Instance, USART_INT_TXC, ENABLE);
        }
        NVIC_Set(uart->config->irq_type, ENABLE);
        break;

    case RT_DEVICE_CHECK_OPTMODE: {
        if (ctrl_arg & RT_DEVICE_FLAG_DMA_TX)
            return RT_SERIAL_TX_BLOCKING_NO_BUFFER;
        else
            return RT_SERIAL_TX_BLOCKING_BUFFER;
    }

    case RT_DEVICE_CTRL_CLOSE:
        DMA_EnableChannel(uart->dma_tx.handle.Instance, DISABLE);
        DMA_EnableChannel(uart->dma_rx.handle.Instance, DISABLE);
        USART_DeInit(uart->handle.Instance);
        GPIOInit(uart->config->tx_port, GPIO_Mode_AIN, GPIO_INPUT, uart->config->tx_pin);
        GPIOInit(uart->config->rx_port, GPIO_Mode_AIN, GPIO_INPUT, uart->config->rx_pin);
        NVIC_DisableIRQ(uart->config->irq_type);
        NVIC_ClearPendingIRQ(uart->config->irq_type);
        break;
    }

    return RT_EOK;
}

static int n32_putc(struct rt_serial_device *serial, char c)
{
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct n32_uart, serial);
    /* Transmit Data */
    uart->handle.Instance->DAT = (c & (uint16_t)0x01FF);
    while ((USART_GetFlagStatus(uart->handle.Instance, USART_FLAG_TXDE) == RESET));

    return 1;
}

static int n32_getc(struct rt_serial_device *serial)
{
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct n32_uart, serial);

    return (int)(uart->handle.Instance->DAT & (uint16_t)0xFF);
}

static rt_size_t n32_transmit(struct rt_serial_device *serial,
                              rt_uint8_t              *buf,
                              rt_size_t                size,
                              rt_uint32_t              tx_flag)
{
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(buf != RT_NULL);
    uart = rt_container_of(serial, struct n32_uart, serial);

    if (uart->uart_dma_flag & RT_DEVICE_FLAG_DMA_TX)
    {
        DMA_EnableChannel(uart->dma_tx.handle.Instance, DISABLE);
        uart->dma_tx.handle.Instance->MADDR = (unsigned int)buf;
        uart->dma_tx.handle.Instance->TXNUM = size & 0xFFFF;
        DMA_EnableChannel(uart->dma_tx.handle.Instance, ENABLE);

        return size & 0xFFFF;
    }

    return size;
}

#ifdef RT_SERIAL_USING_DMA
static void dma_recv_isr(struct rt_serial_device *serial, rt_uint8_t isr_flag)
{
    struct n32_uart *uart;
    rt_base_t        level;
    rt_size_t        recv_len, counter;

    RT_ASSERT(serial != RT_NULL);
    uart     = rt_container_of(serial, struct n32_uart, serial);
    level    = rt_hw_interrupt_disable();
    recv_len = 0;
    counter  = uart->dma_rx.handle.Instance->TXNUM;

    switch (isr_flag)
    {
    case UART_RX_DMA_IT_IDLE_FLAG:
        if (counter <= uart->dma_rx.remaining_cnt)
            recv_len = uart->dma_rx.remaining_cnt - counter;
        else
            recv_len = serial->config.dma_ping_bufsz + uart->dma_rx.remaining_cnt - counter;
        break;

    case UART_RX_DMA_IT_HT_FLAG:
        if (counter < uart->dma_rx.remaining_cnt)
            recv_len = uart->dma_rx.remaining_cnt - counter;
        break;

    case UART_RX_DMA_IT_TC_FLAG:
        if (counter >= uart->dma_rx.remaining_cnt)
            recv_len = serial->config.dma_ping_bufsz + uart->dma_rx.remaining_cnt - counter;

    default:
        break;
    }

    if (recv_len)
    {
        uart->dma_rx.remaining_cnt = counter;
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
    }
    rt_hw_interrupt_enable(level);
}
#endif /* RT_SERIAL_USING_DMA */

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct n32_uart, serial);
    /* If the Read data register is not empty and the RXNE interrupt is enabled  （RDR） */
    if (USART_GetIntStatus(uart->handle.Instance, USART_INT_RXDNE) != RESET && USART_GetFlagStatus(uart->handle.Instance, USART_FLAG_RXDNE) != RESET)
    {
        char chr = uart->handle.Instance->DAT & (rt_uint16_t)0x01FF;
        rt_hw_serial_control_isr(serial, RT_HW_SERIAL_CTRL_PUTC, &chr);
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
    /* If the Transmit data register is empty and the TXE interrupt enable is enabled  （TDR）*/
    else if (USART_GetIntStatus(uart->handle.Instance, USART_INT_TXDE) != RESET && USART_GetFlagStatus(uart->handle.Instance, USART_FLAG_TXDE) != RESET)
    {
        rt_uint8_t put_char = 0;
        if (rt_hw_serial_control_isr(serial, RT_HW_SERIAL_CTRL_GETC, &put_char) == RT_EOK)
        {
            USART_SendData(uart->handle.Instance, put_char);
        }
    }
    else if (USART_GetIntStatus(uart->handle.Instance, USART_INT_TXC) != RESET && USART_GetFlagStatus(uart->handle.Instance, USART_FLAG_TXC))
    {
        /* Clear Transmission complete interrupt flag ( ISR Register ) */
        USART_ClrFlag(uart->handle.Instance, USART_INT_TXC);
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
    }

#ifdef RT_SERIAL_USING_DMA
    else if ((uart->uart_dma_flag) && (USART_GetFlagStatus(uart->handle.Instance, USART_FLAG_IDLEF) != RESET)
             && (USART_GetIntStatus(uart->handle.Instance, USART_INT_IDLEF) != RESET))
    {
        /* clean IDLEF flag */
        USART_ReceiveData(uart->handle.Instance);
        dma_recv_isr(serial, UART_RX_DMA_IT_IDLE_FLAG);
        USART_ClrIntPendingBit(uart->handle.Instance, USART_INT_TXC);
        USART_ClrIntPendingBit(uart->handle.Instance, USART_INT_LINBD);
        USART_ClrIntPendingBit(uart->handle.Instance, USART_INT_RXDNE);
    }
#endif
    else
    {
        if (USART_GetIntStatus(uart->handle.Instance, USART_INT_OREF) != RESET)
        {
        }
        if (USART_GetIntStatus(uart->handle.Instance, USART_INT_NEF) != RESET)
        {
        }
        if (USART_GetIntStatus(uart->handle.Instance, USART_INT_FEF) != RESET)
        {
        }
        if (USART_GetIntStatus(uart->handle.Instance, USART_INT_PEF) != RESET)
        {
        }
        if (USART_GetFlagStatus(uart->handle.Instance, USART_FLAG_TXC) != RESET)
        {
            USART_ClrFlag(uart->handle.Instance, USART_FLAG_TXC);
        }
        if (USART_GetFlagStatus(uart->handle.Instance, USART_FLAG_RXDNE) != RESET)
        {
            USART_ClrFlag(uart->handle.Instance, USART_FLAG_RXDNE);
        }
        USART_ReceiveData(uart->handle.Instance);
    }
}

/**
  * @brief  Handle DMA interrupt request.
  * @param  hdma pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA Channel.
  * @retval None
  */
static void HAL_DMA_IRQHandler(struct DMA_HandleTypeDef *hdma)
{
    DMA_Module *dmax = RT_NULL;

    /* get offset */
    if ((unsigned int)hdma->Instance < DMA2_BASE)
    {
        dmax = DMA1;
    }
    else
    {
        dmax = DMA2;
    }
    unsigned int flag_it        = dmax->INTSTS;
    unsigned int channel_offset = ((unsigned int)hdma->Instance - (unsigned int)dmax - 8) / 20;

    /* Transfer Complete Interrupt management ***********************************/
    if ((flag_it & 2u << (4 * channel_offset)))
    {
        /* Clear the transfer complete flag */
        dmax->INTCLR |= 3u << (4 * channel_offset);
        HAL_UART_TxCpltCallback(hdma->Parent);
    }
    /* Transfer Error Interrupt management **************************************/
    if ((flag_it & 8u << (4 * channel_offset)))
    {
        dmax->INTCLR |= 9u << (4 * channel_offset);
        DMA_EnableChannel(hdma->Instance, DISABLE);
    }
}


#if defined(BSP_USING_USART1)
void USART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART1_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_RX_USING_DMA)
void DMA1_Channel5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART1_INDEX].dma_rx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_RX_USING_DMA) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_TX_USING_DMA)
void DMA1_Channel4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART1_INDEX].dma_tx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_TX_USING_DMA) */
#endif /* BSP_USING_USART1 */

#if defined(BSP_USING_USART2)
void USART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART2_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART2_RX_USING_DMA)
void DMA1_Channel6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART2_INDEX].dma_rx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART2_RX_USING_DMA) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART2_TX_USING_DMA)
void DMA1_Channel7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART2_INDEX].dma_tx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART2_TX_USING_DMA) */
#endif /* BSP_USING_USART2 */

#if defined(BSP_USING_USART3)
void USART3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART3_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART3_RX_USING_DMA)
void DMA1_Channel3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART3_INDEX].dma_rx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_UART_USING_DMA_RX) && defined(BSP_UART3_RX_USING_DMA) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART3_TX_USING_DMA)
void DMA1_Channel2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART3_INDEX].dma_tx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_UART_USING_DMA_TX) && defined(BSP_UART3_TX_USING_DMA) */
#endif /* BSP_USING_USART3*/

#if defined(BSP_USING_UART4)
void UART4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART4_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART4_RX_USING_DMA)
void DMA2_Channel3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART4_INDEX].dma_rx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_UART_USING_DMA_RX) && defined(BSP_UART4_RX_USING_DMA) */

#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART4_TX_USING_DMA)
void DMA2_Channel5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART4_INDEX].dma_tx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_UART_USING_DMA_TX) && defined(BSP_UART4_TX_USING_DMA) */
#endif /* BSP_USING_UART4*/

#if defined(BSP_USING_UART5)
void UART5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART5_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART5_RX_USING_DMA)
void DMA1_Channel8_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART5_INDEX].dma_rx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART5_RX_USING_DMA) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART5_TX_USING_DMA)
void DMA1_Channel1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART5_INDEX].dma_tx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART5_TX_USING_DMA) */
#endif /* BSP_USING_UART5*/

#if defined(BSP_USING_UART6)
void UART6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART6_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART6_RX_USING_DMA)
void DMA2_Channel1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART6_INDEX].dma_rx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART6_RX_USING_DMA) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART6_TX_USING_DMA)
void DMA2_Channel2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART6_INDEX].dma_tx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART6_TX_USING_DMA) */
#endif /* BSP_USING_UART6*/

#if defined(BSP_USING_UART7)
void UART7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART7_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART7_RX_USING_DMA)
void DMA2_Channel6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART7_INDEX].dma_rx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART7_RX_USING_DMA) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART7_TX_USING_DMA)
void DMA2_Channel7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART7_INDEX].dma_tx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART7_TX_USING_DMA) */
#endif /* BSP_USING_UART7*/


static void n32_uart_get_config(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_USART1
    uart_obj[UART1_INDEX].serial.config          = config;
    uart_obj[UART1_INDEX].serial.config.rx_bufsz = BSP_UART1_RX_BUFSIZE;
    uart_obj[UART1_INDEX].serial.config.tx_bufsz = BSP_UART1_TX_BUFSIZE;
    uart_obj[UART1_INDEX].handle.Instance        = USART1;
    uart_obj[UART1_INDEX].uart_dma_flag          = 0;
#ifdef BSP_UART1_RX_USING_DMA
    uart_obj[UART1_INDEX].handle.HDMA_Rx          = &uart_obj[UART1_INDEX].dma_rx.handle;
    uart_obj[UART1_INDEX].serial.config.dma_ping_bufsz = BSP_UART1_DMA_PING_BUFSIZE;
    uart_obj[UART1_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_RX;
    uart_obj[UART1_INDEX].dma_rx.handle.Parent    = &uart_obj[UART1_INDEX].handle;
    uart_obj[UART1_INDEX].dma_rx.handle.Instance  = DMA1_CH5;
    uart_obj[UART1_INDEX].dma_rx.handle.dma_rcc   = RCC_AHBPCLKEN_DMA1EN;
    uart_obj[UART1_INDEX].dma_rx.handle.dma_irq   = DMA1_Channel5_IRQn;
#endif
#ifdef BSP_UART1_TX_USING_DMA
    uart_obj[UART1_INDEX].handle.HDMA_Tx          = &uart_obj[UART1_INDEX].dma_tx.handle;
    uart_obj[UART1_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_TX;
    uart_obj[UART1_INDEX].dma_tx.handle.Parent    = &uart_obj[UART1_INDEX].handle;
    uart_obj[UART1_INDEX].dma_tx.handle.Instance  = DMA1_CH4;
    uart_obj[UART1_INDEX].dma_tx.handle.dma_rcc   = RCC_AHBPCLKEN_DMA1EN;
    uart_obj[UART1_INDEX].dma_tx.handle.dma_irq   = DMA1_Channel4_IRQn;
#endif
#endif

#ifdef BSP_USING_USART2
    uart_obj[UART2_INDEX].serial.config          = config;
    uart_obj[UART2_INDEX].serial.config.rx_bufsz = BSP_UART2_RX_BUFSIZE;
    uart_obj[UART2_INDEX].serial.config.tx_bufsz = BSP_UART2_TX_BUFSIZE;
    uart_obj[UART2_INDEX].handle.Instance        = USART2;
    uart_obj[UART2_INDEX].uart_dma_flag          = 0;
#ifdef BSP_UART2_RX_USING_DMA
    uart_obj[UART2_INDEX].handle.HDMA_Rx          = &uart_obj[UART2_INDEX].dma_rx.handle;
    uart_obj[UART2_INDEX].serial.config.dma_ping_bufsz = BSP_UART2_DMA_PING_BUFSIZE;
    uart_obj[UART2_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_RX;
    uart_obj[UART2_INDEX].dma_rx.handle.Parent    = &uart_obj[UART2_INDEX].handle;
    uart_obj[UART2_INDEX].dma_rx.handle.Instance  = DMA1_CH6;
    uart_obj[UART2_INDEX].dma_rx.handle.dma_rcc   = RCC_AHBPCLKEN_DMA1EN;
    uart_obj[UART2_INDEX].dma_rx.handle.dma_irq   = DMA1_Channel6_IRQn;
#endif
#ifdef BSP_UART2_TX_USING_DMA
    uart_obj[UART2_INDEX].handle.HDMA_Tx          = &uart_obj[UART2_INDEX].dma_tx.handle;
    uart_obj[UART2_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_TX;
    uart_obj[UART2_INDEX].dma_tx.handle.Parent    = &uart_obj[UART2_INDEX].handle;
    uart_obj[UART2_INDEX].dma_tx.handle.Instance  = DMA1_CH7;
    uart_obj[UART2_INDEX].dma_tx.handle.dma_rcc   = RCC_AHBPCLKEN_DMA1EN;
    uart_obj[UART2_INDEX].dma_tx.handle.dma_irq   = DMA1_Channel7_IRQn;
#endif
#endif

#ifdef BSP_USING_USART3
    uart_obj[UART3_INDEX].serial.config          = config;
    uart_obj[UART3_INDEX].serial.config.rx_bufsz = BSP_UART3_RX_BUFSIZE;
    uart_obj[UART3_INDEX].serial.config.tx_bufsz = BSP_UART3_TX_BUFSIZE;
    uart_obj[UART3_INDEX].handle.Instance        = USART3;
    uart_obj[UART3_INDEX].uart_dma_flag          = 0;
#ifdef BSP_UART3_RX_USING_DMA
    uart_obj[UART3_INDEX].handle.HDMA_Rx          = &uart_obj[UART3_INDEX].dma_rx.handle;
    uart_obj[UART3_INDEX].serial.config.dma_ping_bufsz = BSP_UART3_DMA_PING_BUFSIZE;
    uart_obj[UART3_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_RX;
    uart_obj[UART3_INDEX].dma_rx.handle.Parent    = &uart_obj[UART3_INDEX].handle;
    uart_obj[UART3_INDEX].dma_rx.handle.Instance  = DMA1_CH3;
    uart_obj[UART3_INDEX].dma_rx.handle.dma_rcc   = RCC_AHBPCLKEN_DMA1EN;
    uart_obj[UART3_INDEX].dma_rx.handle.dma_irq   = DMA1_Channel3_IRQn;
#endif
#ifdef BSP_UART3_TX_USING_DMA
    uart_obj[UART3_INDEX].handle.HDMA_Tx          = &uart_obj[UART3_INDEX].dma_tx.handle;
    uart_obj[UART3_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_TX;
    uart_obj[UART3_INDEX].dma_tx.handle.Parent    = &uart_obj[UART3_INDEX].handle;
    uart_obj[UART3_INDEX].dma_tx.handle.Instance  = DMA1_CH2;
    uart_obj[UART3_INDEX].dma_tx.handle.dma_rcc   = RCC_AHBPCLKEN_DMA1EN;
    uart_obj[UART3_INDEX].dma_tx.handle.dma_irq   = DMA1_Channel2_IRQn;
#endif
#endif

#ifdef BSP_USING_UART4
    uart_obj[UART4_INDEX].serial.config          = config;
    uart_obj[UART4_INDEX].serial.config.rx_bufsz = BSP_UART4_RX_BUFSIZE;
    uart_obj[UART4_INDEX].serial.config.tx_bufsz = BSP_UART4_TX_BUFSIZE;
    uart_obj[UART4_INDEX].handle.Instance        = UART4;
    uart_obj[UART4_INDEX].uart_dma_flag          = 0;
#ifdef BSP_UART4_RX_USING_DMA
    uart_obj[UART4_INDEX].handle.HDMA_Rx          = &uart_obj[UART4_INDEX].dma_rx.handle;
    uart_obj[UART4_INDEX].serial.config.dma_ping_bufsz = BSP_UART4_DMA_PING_BUFSIZE;
    uart_obj[UART4_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_RX;
    uart_obj[UART4_INDEX].dma_rx.handle.Parent    = &uart_obj[UART4_INDEX].handle;
    uart_obj[UART4_INDEX].dma_rx.handle.Instance  = DMA2_CH3;
    uart_obj[UART4_INDEX].dma_rx.handle.dma_rcc   = RCC_AHBPCLKEN_DMA2EN;
    uart_obj[UART4_INDEX].dma_rx.handle.dma_irq   = DMA2_Channel3_IRQn;
#endif
#ifdef BSP_UART4_TX_USING_DMA
    uart_obj[UART4_INDEX].handle.HDMA_Tx          = &uart_obj[UART4_INDEX].dma_tx.handle;
    uart_obj[UART4_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_TX;
    uart_obj[UART4_INDEX].dma_tx.handle.Parent    = &uart_obj[UART4_INDEX].handle;
    uart_obj[UART4_INDEX].dma_tx.handle.Instance  = DMA2_CH5;
    uart_obj[UART4_INDEX].dma_tx.handle.dma_rcc   = RCC_AHBPCLKEN_DMA2EN;
    uart_obj[UART4_INDEX].dma_tx.handle.dma_irq   = DMA2_Channel5_IRQn;
#endif
#endif

#ifdef BSP_USING_UART5
    uart_obj[UART5_INDEX].serial.config          = config;
    uart_obj[UART5_INDEX].serial.config.rx_bufsz = BSP_UART5_RX_BUFSIZE;
    uart_obj[UART5_INDEX].serial.config.tx_bufsz = BSP_UART5_TX_BUFSIZE;
    uart_obj[UART5_INDEX].handle.Instance        = UART5;
    uart_obj[UART5_INDEX].uart_dma_flag          = 0;
#ifdef BSP_UART5_RX_USING_DMA
    uart_obj[UART5_INDEX].handle.HDMA_Rx          = &uart_obj[UART5_INDEX].dma_rx.handle;
    uart_obj[UART5_INDEX].serial.config.dma_ping_bufsz = BSP_UART5_DMA_PING_BUFSIZE;
    uart_obj[UART5_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_RX;
    uart_obj[UART5_INDEX].dma_rx.handle.Parent    = &uart_obj[UART5_INDEX].handle;
    uart_obj[UART5_INDEX].dma_rx.handle.Instance  = DMA1_CH8;
    uart_obj[UART5_INDEX].dma_rx.handle.dma_rcc   = RCC_AHBPCLKEN_DMA1EN;
    uart_obj[UART5_INDEX].dma_rx.handle.dma_irq   = DMA1_Channel8_IRQn;
#endif
#ifdef BSP_UART5_TX_USING_DMA
    uart_obj[UART5_INDEX].handle.HDMA_Tx          = &uart_obj[UART5_INDEX].dma_tx.handle;
    uart_obj[UART5_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_TX;
    uart_obj[UART5_INDEX].dma_tx.handle.Parent    = &uart_obj[UART5_INDEX].handle;
    uart_obj[UART5_INDEX].dma_tx.handle.Instance  = DMA1_CH1;
    uart_obj[UART5_INDEX].dma_tx.handle.dma_rcc   = RCC_AHBPCLKEN_DMA1EN;
    uart_obj[UART5_INDEX].dma_tx.handle.dma_irq   = DMA1_Channel1_IRQn;
#endif
#endif

#ifdef BSP_USING_UART6
    uart_obj[UART6_INDEX].serial.config          = config;
    uart_obj[UART6_INDEX].serial.config.rx_bufsz = BSP_UART6_RX_BUFSIZE;
    uart_obj[UART6_INDEX].serial.config.tx_bufsz = BSP_UART6_TX_BUFSIZE;
    uart_obj[UART6_INDEX].handle.Instance        = UART6;
    uart_obj[UART6_INDEX].uart_dma_flag          = 0;
#ifdef BSP_UART6_RX_USING_DMA
    uart_obj[UART6_INDEX].handle.HDMA_Rx          = &uart_obj[UART6_INDEX].dma_rx.handle;
    uart_obj[UART6_INDEX].serial.config.dma_ping_bufsz = BSP_UART6_DMA_PING_BUFSIZE;
    uart_obj[UART6_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_RX;
    uart_obj[UART6_INDEX].dma_rx.handle.Parent    = &uart_obj[UART6_INDEX].handle;
    uart_obj[UART6_INDEX].dma_rx.handle.Instance  = DMA2_CH1;
    uart_obj[UART6_INDEX].dma_rx.handle.dma_rcc   = RCC_AHBPCLKEN_DMA2EN;
    uart_obj[UART6_INDEX].dma_rx.handle.dma_irq   = DMA2_Channel1_IRQn;
#endif
#ifdef BSP_UART6_TX_USING_DMA
    uart_obj[UART6_INDEX].handle.HDMA_Tx          = &uart_obj[UART6_INDEX].dma_tx.handle;
    uart_obj[UART6_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_TX;
    uart_obj[UART6_INDEX].dma_tx.handle.Parent    = &uart_obj[UART6_INDEX].handle;
    uart_obj[UART6_INDEX].dma_tx.handle.Instance  = DMA2_CH2;
    uart_obj[UART6_INDEX].dma_tx.handle.dma_rcc   = RCC_AHBPCLKEN_DMA2EN;
    uart_obj[UART6_INDEX].dma_tx.handle.dma_irq   = DMA2_Channel2_IRQn;
#endif
#endif

#ifdef BSP_USING_UART7
    uart_obj[UART7_INDEX].serial.config          = config;
    uart_obj[UART7_INDEX].serial.config.rx_bufsz = BSP_UART7_RX_BUFSIZE;
    uart_obj[UART7_INDEX].serial.config.tx_bufsz = BSP_UART7_TX_BUFSIZE;
    uart_obj[UART7_INDEX].handle.Instance        = UART7;
    uart_obj[UART7_INDEX].uart_dma_flag          = 0;
#ifdef BSP_UART7_RX_USING_DMA
    uart_obj[UART7_INDEX].handle.HDMA_Rx          = &uart_obj[UART7_INDEX].dma_rx.handle;
    uart_obj[UART7_INDEX].serial.config.dma_ping_bufsz = BSP_UART7_DMA_PING_BUFSIZE;
    uart_obj[UART7_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_RX;
    uart_obj[UART7_INDEX].dma_rx.handle.Parent    = &uart_obj[UART7_INDEX].handle;
    uart_obj[UART7_INDEX].dma_rx.handle.Instance  = DMA2_CH6;
    uart_obj[UART7_INDEX].dma_rx.handle.dma_rcc   = RCC_AHBPCLKEN_DMA2EN;
    uart_obj[UART7_INDEX].dma_rx.handle.dma_irq   = DMA2_Channel6_IRQn;
#endif
#ifdef BSP_UART7_TX_USING_DMA
    uart_obj[UART7_INDEX].handle.HDMA_Tx          = &uart_obj[UART7_INDEX].dma_tx.handle;
    uart_obj[UART7_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_TX;
    uart_obj[UART7_INDEX].dma_tx.handle.Parent    = &uart_obj[UART7_INDEX].handle;
    uart_obj[UART7_INDEX].dma_tx.handle.Instance  = DMA2_CH7;
    uart_obj[UART7_INDEX].dma_tx.handle.dma_rcc   = RCC_AHBPCLKEN_DMA2EN;
    uart_obj[UART7_INDEX].dma_tx.handle.dma_irq   = DMA2_Channel7_IRQn;
#endif
#endif
}

#ifdef RT_SERIAL_USING_DMA
static void n32_uart_dma_config(struct rt_serial_device *serial, rt_ubase_t flag)
{
    struct DMA_HandleTypeDef *DMA_Handle;
    struct n32_uart          *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(flag == RT_DEVICE_FLAG_DMA_TX || flag == RT_DEVICE_FLAG_DMA_RX);
    uart = rt_container_of(serial, struct n32_uart, serial);

    if (RT_DEVICE_FLAG_DMA_RX == flag)
    {
        DMA_Handle = &uart->dma_rx.handle;
    }
    else /* RT_DEVICE_FLAG_DMA_TX == flag */
    {
        DMA_Handle = &uart->dma_tx.handle;
    }

    RCC_EnableAHBPeriphClk(DMA_Handle->dma_rcc, ENABLE);
    DMA_DeInit(DMA_Handle->Instance);
    DMA_Handle->Init.PeriphAddr     = (unsigned int)uart->config->Instance + 0x4;
    DMA_Handle->Init.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_Handle->Init.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_Handle->Init.PeriphDataSize = DMA_PERIPH_DATA_SIZE_BYTE;
    DMA_Handle->Init.MemDataSize    = DMA_MemoryDataSize_Byte;
    DMA_Handle->Init.Mem2Mem        = DMA_M2M_DISABLE;
    if (RT_DEVICE_FLAG_DMA_RX == flag)
    {
        rt_uint8_t *ptr = NULL;
        rt_hw_serial_control_isr(serial, RT_HW_SERIAL_CTRL_GET_DMA_PING_BUF, &ptr);
        DMA_Handle->Init.Direction    = DMA_DIR_PERIPH_SRC;
        DMA_Handle->Init.MemAddr      = (unsigned int)ptr;
        DMA_Handle->Init.BufSize      = serial->config.dma_ping_bufsz;
        DMA_Handle->Init.CircularMode = DMA_MODE_CIRCULAR;
        DMA_Handle->Init.Priority     = DMA_PRIORITY_VERY_HIGH;
    }
    else if (RT_DEVICE_FLAG_DMA_TX == flag)
    {
        DMA_Handle->Init.Direction    = DMA_DIR_PERIPH_DST;
        DMA_Handle->Init.MemAddr      = (unsigned int)1;
        DMA_Handle->Init.BufSize      = 1;
        DMA_Handle->Init.CircularMode = DMA_MODE_NORMAL;
        DMA_Handle->Init.Priority     = DMA_PRIORITY_HIGH;
    }
    DMA_Init(DMA_Handle->Instance, &DMA_Handle->Init);
    NVIC_Set(DMA_Handle->dma_irq, ENABLE);
    /* Enable USART DMA Rx or TX request */
    if (RT_DEVICE_FLAG_DMA_RX == flag)
    {
        USART_EnableDMA(uart->handle.Instance, USART_DMAREQ_RX, ENABLE);
        USART_ClrFlag(uart->handle.Instance, USART_INT_IDLEF);
        USART_ConfigInt(uart->handle.Instance, USART_INT_IDLEF, ENABLE);
        NVIC_Set(uart->config->irq_type, ENABLE);
        DMA_EnableChannel(DMA_Handle->Instance, ENABLE);
    }
    if (RT_DEVICE_FLAG_DMA_TX == flag)
    {
        USART_EnableDMA(uart->handle.Instance, USART_DMAREQ_TX, ENABLE);
        DMA_ConfigInt(DMA_Handle->Instance, DMA_INT_TXC, ENABLE);
    }
    USART_Enable(uart->handle.Instance, ENABLE);
}

/**
  * @brief  HAL_UART_TxCpltCallback
  * @param  huart: UART handle
  * @note   This callback can be called by two functions, first in UART_EndTransmit_IT when
  *         UART Tx complete and second in UART_DMATransmitCplt function in DMA Circular mode.
  * @retval None
  */
void HAL_UART_TxCpltCallback(struct UART_HandleTypeDef *huart)
{
    RT_ASSERT(huart != NULL);
    struct n32_uart *uart = (struct n32_uart *)huart;

    rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_TX_DMADONE);
}
#endif /* RT_SERIAL_USING_DMA */

static const struct rt_uart_ops n32_uart_ops =
    {
        .configure = n32_configure,
        .control   = n32_control,
        .putc      = n32_putc,
        .getc      = n32_getc,
        .transmit  = n32_transmit};

int rt_hw_usart_init(void)
{
    rt_err_t  result  = 0;
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct n32_uart);

    n32_uart_get_config();
    for (int i = 0; i < obj_num; i++)
    {
        uart_obj[i].config = &uart_config[i];
        /* init UART object */
        uart_obj[i].serial.ops = &n32_uart_ops;
        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial, uart_obj[i].config->name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_DMA_TX, NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_usart_init);

#endif /* RT_USING_SERIAL_V2 */
