/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-22     yuanjie      first version, function
 */

/**
 *  WS2812B serial LED data timing flow:
 *  | T0H | H | 350ns  | ±150ns   |
 *  | T0L | L | 800ns  | ±150ns   |
 *  | T1H | H | 700ns  | ±150ns   |
 *  | T1L | L | 600ns  | ±150ns   |
 *  | RES | L | ≥50us  | --       |
 *  When using TIM peripheral, to meet 800kHz (1250ns) refresh rate:
 *  - period is:  1250ns
 *  - logic 0 is: 400ns(H) + 900ns(L)
 *  - logic 1 is: 900ns(H) + 400ns(L)
 */

#include <rtdevice.h>
#include <board.h>
#include <drv_matrix_led.h>
#include <drv_common.h>
#include <drv_gpio.h>

#ifndef LED_NUM
#define LED_NUM     19 // LED灯珠个数
#endif
#define LED_MATRIX_EN_PIN   GET_PIN(F, 2)

TIM_HandleTypeDef htim3;
DMA_HandleTypeDef hdma_tim3_ch2;

rt_align(RT_ALIGN_SIZE) uint8_t led_buffer[LED_NUM * 24 * 2];

extern void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

// 模拟bit码: 2为逻辑0, 7为逻辑1
const uint8_t tile[] = {2, 7};


// 常见颜色定义

const RGBColor_TypeDef DARK = {0, 0, 0};
const RGBColor_TypeDef GREEN = {255, 0, 0};
const RGBColor_TypeDef RED = {0, 255, 0};
const RGBColor_TypeDef BLUE = {0, 0, 255};
const RGBColor_TypeDef WHITE = {255, 255, 255};
const RGBColor_TypeDef LT_RED = {0, 32, 0};
const RGBColor_TypeDef LT_GREEN = {32, 0, 0};
const RGBColor_TypeDef LT_BLUE = {0, 0, 32};
const RGBColor_TypeDef LT_WHITE = {16, 16, 16};

// 灯颜色缓存
RGBColor_TypeDef RGB_Data[LED_NUM] = {0};

void led_matrix_rst();
/**
 * @brief This function handles DMA2 stream3 global interrupt.
 */
void DMA1_Stream5_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_tim3_ch2);
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
    {
        __HAL_TIM_SetCompare(htim, TIM_CHANNEL_2,0); //占空比清0
    }
}
/**
 * @brief matrix Initialization Function
 * @param None
 * @retval None
 */
static int matrix_init(void)
{
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    /* TIM3_CH2 Init */
    __HAL_RCC_TIM3_CLK_ENABLE();

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 10-1;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 10-1;    // 840kHz
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.RepetitionCounter = 0;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
    {
        Error_Handler();
    }


    HAL_TIM_MspPostInit(&htim3);

    /* TIM3 DMA Init */
    __HAL_RCC_DMA1_CLK_ENABLE();

    hdma_tim3_ch2.Instance = DMA1_Stream5;
    hdma_tim3_ch2.Init.Channel = DMA_CHANNEL_5;
    hdma_tim3_ch2.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_tim3_ch2.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_tim3_ch2.Init.MemInc = DMA_MINC_ENABLE;
    hdma_tim3_ch2.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_tim3_ch2.Init.MemDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_tim3_ch2.Init.Mode = DMA_NORMAL;
    hdma_tim3_ch2.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_tim3_ch2.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_tim3_ch2) != HAL_OK)
    {
        Error_Handler();
    }
    __HAL_LINKDMA(&htim3, hdma[TIM_DMA_ID_CC2], hdma_tim3_ch2);

    /* NVIC configuration for DMA transfer complete interrupt */
    HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

    rt_pin_mode(LED_MATRIX_EN_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(LED_MATRIX_EN_PIN, PIN_LOW);
    led_matrix_rst();
    return RT_EOK;

}

INIT_APP_EXPORT(matrix_init);

/**
 * @brief           设置灯带颜色发送缓存
 * @param[in]       ID 颜色
 */
void Set_LEDColor(uint16_t LedId, RGBColor_TypeDef Color)
{
    RGB_Data[LedId].G = Color.G;
    RGB_Data[LedId].R = Color.R;
    RGB_Data[LedId].B = Color.B;
}

/**
 * @brief           TIM发送控制ws2812
 * @param[in]       待发送缓存
 */
static void TIM_Send_WS2812(uint8_t *rgb_buffer, uint32_t size)
{
    // 判断上次DMA有没有传输完成
    while (HAL_DMA_GetState(&hdma_tim3_ch2) != HAL_DMA_STATE_READY);
    // 发送一个24bit的RGB数据
    HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_2, (uint32_t *)rgb_buffer, size);

}

/**
 * @brief           控制WS2812
 * @param[in]       待发送缓存
 */

void RGB_Reflash(void)
{
    uint8_t dat_b,dat_r,dat_g;
    // 将数组颜色转化为24个要发送的字节数据
    for (uint16_t i = 0; i < LED_NUM; i++)
    {
        dat_g = RGB_Data[i].G;
        dat_r = RGB_Data[i].R;
        dat_b = RGB_Data[i].B;
        for (uint16_t j = 0; j < 8; j++) {
            led_buffer[(14 + (i * 48))-(j<<1)] = tile[dat_g & 0x01];
            led_buffer[(14 + (i * 48))-(j<<1) + 1] = 0;
            led_buffer[(30 + (i * 48))-(j<<1)] = tile[dat_r & 0x01];
            led_buffer[(30 + (i * 48))-(j<<1) + 1] = 0;
            led_buffer[(46 + (i * 48))-(j<<1)] = tile[dat_b & 0x01];
            led_buffer[(46 + (i * 48))-(j<<1) + 1] = 0;
            dat_g >>=1;
            dat_r >>=1;
            dat_b >>=1;
        }
    }
    TIM_Send_WS2812(led_buffer, sizeof(led_buffer) / 2);

}
void led_matrix_rst()
{
    for (uint32_t i = 0; i < (LED_NUM * 24); i++)
    {
        led_buffer[ (i<<1) ] = 3;
        led_buffer[ (i<<1) + 1] = 0;
    }
    TIM_Send_WS2812(led_buffer, sizeof(led_buffer) / 2 );
}

MSH_CMD_EXPORT(led_matrix_rst, Test led matrix on board)

void led_matrix_fill(RGBColor_TypeDef Color)
{
    rt_memset(RGB_Data, 0x00, sizeof(RGB_Data));
    for (uint8_t i = 0; i < LED_NUM; i++)
    {
        Set_LEDColor(i, Color);
    }
    RGB_Reflash();
}

void led_matrix_fill_test(uint8_t index)
{
    switch (index)
    {
    case 0:
        led_matrix_fill(LT_RED);
        break;
    case 1:
        led_matrix_fill(LT_GREEN);
        break;
    case 2:
        led_matrix_fill(LT_BLUE);
        break;
    case 3:
        led_matrix_fill(LT_WHITE);
        break;
    default:
        break;
    }
}

void led_matrix_test1()
{
    rt_memset(RGB_Data, 0x00, sizeof(RGB_Data));
    Set_LEDColor(0, RED);
    Set_LEDColor(1, GREEN);
    Set_LEDColor(2, BLUE);
    Set_LEDColor(3, RED);
    Set_LEDColor(4, GREEN);
    Set_LEDColor(5, BLUE);
    Set_LEDColor(6, RED);
    Set_LEDColor(7, GREEN);
    Set_LEDColor(8, BLUE);
    Set_LEDColor(9, WHITE);
    // led_matrix_rst();
    RGB_Reflash();
}
MSH_CMD_EXPORT(led_matrix_test1, Test led matrix on board)

void led_matrix_test2()
{
    rt_memset(RGB_Data, 0x00, sizeof(RGB_Data));
    Set_LEDColor(0, BLUE);
    Set_LEDColor(1, RED);
    Set_LEDColor(2, GREEN);
    Set_LEDColor(3, BLUE);
    Set_LEDColor(4, RED);
    Set_LEDColor(5, GREEN);
    Set_LEDColor(6, BLUE);
    Set_LEDColor(7, RED);
    Set_LEDColor(8, GREEN);
    Set_LEDColor(9, RED);

    Set_LEDColor(14, GREEN);
    Set_LEDColor(15, GREEN);
    Set_LEDColor(16, BLUE);
    Set_LEDColor(17, RED);
    Set_LEDColor(18, WHITE);

    RGB_Reflash();
}
MSH_CMD_EXPORT(led_matrix_test2, Test led matrix on board)

void led_matrix_test3()
{
    for (uint8_t i = 0; i < 4; i++)
    {
        led_matrix_fill_test(i);
        rt_thread_mdelay(1000);
    }
    led_matrix_rst();
}

MSH_CMD_EXPORT(led_matrix_test3, Test led matrix on board)

void led_matrix_show_color(uint8_t r, uint8_t g, uint8_t b)
{
    RGBColor_TypeDef color = {g,r,b};
    led_matrix_fill(color);
}
