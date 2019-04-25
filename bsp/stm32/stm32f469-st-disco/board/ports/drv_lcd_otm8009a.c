/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2018-07-28     liu2guang      the first version for STM32F469NI-Discovery.
 * 2019-04-19     WillianChan    porting STM32F469NI-Discovery lcd driver to
 *                               the new STM32 BSP framework.
 */
 
#include <board.h>

#ifdef BSP_USING_LCD_OTM8009A
#include <lcd_port.h>

struct stm32_lcd
{
    struct rt_device device;
    struct rt_device_graphic_info info; 
    
    LTDC_HandleTypeDef  ltdc;
    DSI_HandleTypeDef   dsi;
    DSI_VidCfgTypeDef   dsi_video;
    DMA2D_HandleTypeDef dma2d;
};
static struct stm32_lcd lcd; 

#define  LCD_WIDTH    ((uint16_t)800) 
#define  LCD_HEIGHT   ((uint16_t)480) 

#define  LCD_HSYNC    ((uint16_t)1) 
#define  LCD_HBP      ((uint16_t)15) 
#define  LCD_HFP      ((uint16_t)16) 
#define  LCD_VSYNC    ((uint16_t)2) 
#define  LCD_VBP      ((uint16_t)34) 
#define  LCD_VFP      ((uint16_t)34) 

const rt_uint8_t RDL01[] = {0x80, 0x09, 0x01, 0xFF};
const rt_uint8_t RDL02[] = {0x80, 0x09, 0xFF};
const rt_uint8_t RDL03[] = {0x00, 0x09, 0x0F, 0x0E, 0x07, 0x10, 0x0B, 0x0A, 0x04, 0x07, 0x0B, 0x08, 0x0F, 0x10, 0x0A, 0x01, 0xE1};
const rt_uint8_t RDL04[] = {0x00, 0x09, 0x0F, 0x0E, 0x07, 0x10, 0x0B, 0x0A, 0x04, 0x07, 0x0B, 0x08, 0x0F, 0x10, 0x0A, 0x01, 0xE2};
const rt_uint8_t RDL05[] = {0x79, 0x79, 0xD8};
const rt_uint8_t RDL06[] = {0x00, 0x01, 0xB3};
const rt_uint8_t RDL07[] = {0x85, 0x01, 0x00, 0x84, 0x01, 0x00, 0xCE};
const rt_uint8_t RDL08[] = {0x18, 0x04, 0x03, 0x39, 0x00, 0x00, 0x00, 0x18, 0x03, 0x03, 0x3A, 0x00, 0x00, 0x00, 0xCE};
const rt_uint8_t RDL09[] = {0x18, 0x02, 0x03, 0x3B, 0x00, 0x00, 0x00, 0x18, 0x01, 0x03, 0x3C, 0x00, 0x00, 0x00, 0xCE};
const rt_uint8_t RDL10[] = {0x01, 0x01, 0x20, 0x20, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0xCF};
const rt_uint8_t RDL11[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t RDL12[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t RDL13[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t RDL14[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t RDL15[] = {0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t RDL16[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t RDL17[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t RDL18[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCB};
const rt_uint8_t RDL19[] = {0x00, 0x26, 0x09, 0x0B, 0x01, 0x25, 0x00, 0x00, 0x00, 0x00, 0xCC};
const rt_uint8_t RDL20[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x0A, 0x0C, 0x02, 0xCC};
const rt_uint8_t RDL21[] = {0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC};
const rt_uint8_t RDL22[] = {0x00, 0x25, 0x0C, 0x0A, 0x02, 0x26, 0x00, 0x00, 0x00, 0x00, 0xCC};
const rt_uint8_t RDL23[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x0B, 0x09, 0x01, 0xCC};
const rt_uint8_t RDL24[] = {0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC};
const rt_uint8_t RDL25[] = {0xFF, 0xFF, 0xFF, 0xFF};
const rt_uint8_t RDL27[] = {0x00, 0x00, 0x03, 0x1F, 0x2A};
const rt_uint8_t RDL28[] = {0x00, 0x00, 0x01, 0xDF, 0x2B};

const rt_uint8_t RDS01[] = {0x00, 0x00};
const rt_uint8_t RDS02[] = {0x00, 0x80};
const rt_uint8_t RDS03[] = {0xC4, 0x30};
const rt_uint8_t RDS04[] = {0x00, 0x8A};
const rt_uint8_t RDS05[] = {0xC4, 0x40};
const rt_uint8_t RDS06[] = {0x00, 0xB1};
const rt_uint8_t RDS07[] = {0xC5, 0xA9};
const rt_uint8_t RDS08[] = {0x00, 0x91};
const rt_uint8_t RDS09[] = {0xC5, 0x34};
const rt_uint8_t RDS10[] = {0x00, 0xB4};
const rt_uint8_t RDS11[] = {0xC0, 0x50};
const rt_uint8_t RDS12[] = {0xD9, 0x4E};
const rt_uint8_t RDS13[] = {0x00, 0x81};
const rt_uint8_t RDS14[] = {0xC1, 0x66};
const rt_uint8_t RDS15[] = {0x00, 0xA1};
const rt_uint8_t RDS16[] = {0xC1, 0x08};
const rt_uint8_t RDS17[] = {0x00, 0x92};
const rt_uint8_t RDS18[] = {0xC5, 0x01};
const rt_uint8_t RDS19[] = {0x00, 0x95};
const rt_uint8_t RDS20[] = {0x00, 0x94};
const rt_uint8_t RDS21[] = {0xC5, 0x33};
const rt_uint8_t RDS22[] = {0x00, 0xA3};
const rt_uint8_t RDS23[] = {0xC0, 0x1B};
const rt_uint8_t RDS24[] = {0x00, 0x82};
const rt_uint8_t RDS25[] = {0xC5, 0x83};
const rt_uint8_t RDS26[] = {0xC4, 0x83};
const rt_uint8_t RDS27[] = {0xC1, 0x0E};
const rt_uint8_t RDS28[] = {0x00, 0xA6};
const rt_uint8_t RDS29[] = {0x00, 0xA0};
const rt_uint8_t RDS30[] = {0x00, 0xB0};
const rt_uint8_t RDS31[] = {0x00, 0xC0};
const rt_uint8_t RDS32[] = {0x00, 0xD0};
const rt_uint8_t RDS33[] = {0x00, 0x90};
const rt_uint8_t RDS34[] = {0x00, 0xE0};
const rt_uint8_t RDS35[] = {0x00, 0xF0};
const rt_uint8_t RDS36[] = {0x11, 0x00};
const rt_uint8_t RDS37[] = {0x3A, 0x55};
const rt_uint8_t RDS38[] = {0x3A, 0x77};
const rt_uint8_t RDS39[] = {0x36, 0x60};
const rt_uint8_t RDS40[] = {0x51, 0x7F};
const rt_uint8_t RDS41[] = {0x53, 0x2C};
const rt_uint8_t RDS42[] = {0x55, 0x02};
const rt_uint8_t RDS43[] = {0x5E, 0xFF};
const rt_uint8_t RDS44[] = {0x29, 0x00};
const rt_uint8_t RDS45[] = {0x2C, 0x00};
const rt_uint8_t RDS46[] = {0xCF, 0x00};
const rt_uint8_t RDS47[] = {0xC5, 0x66};
const rt_uint8_t RDS48[] = {0x00, 0xB6};
const rt_uint8_t RDS49[] = {0xF5, 0x06};
const rt_uint8_t RDS50[] = {0x00, 0xB1};
const rt_uint8_t RDS51[] = {0xC6, 0x06};

static void otm8009a_reset(void) 
{
    rt_pin_mode (GET_PIN(H, 7), PIN_MODE_OUTPUT); 
    rt_pin_write(GET_PIN(H, 7), PIN_LOW);
    rt_thread_delay(rt_tick_from_millisecond(20));
    rt_pin_write(GET_PIN(H, 7), PIN_HIGH);
    rt_thread_delay(rt_tick_from_millisecond(20));
}

void otm8009a_write_cmd(uint8_t *p, uint32_t num)
{
    if (num <= 1)
    {
        HAL_DSI_ShortWrite(&(lcd.dsi), lcd.dsi_video.VirtualChannelID, DSI_DCS_SHORT_PKT_WRITE_P1, p[0], p[1]);
    }
    else
    {
        HAL_DSI_LongWrite(&(lcd.dsi), lcd.dsi_video.VirtualChannelID, DSI_DCS_LONG_PKT_WRITE, num, p[num], p);
    }
}

void otm8009a_delay(uint32_t d)
{
    rt_thread_delay(rt_tick_from_millisecond(d)); 
}

static void otm8009a_config(rt_uint32_t pixel_format)
{
    otm8009a_write_cmd((rt_uint8_t *)RDS01, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL01, 3);
    otm8009a_write_cmd((rt_uint8_t *)RDS02, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL02, 2);
    otm8009a_write_cmd((rt_uint8_t *)RDS02, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS03, 0);
    otm8009a_delay(10); 

    otm8009a_write_cmd((rt_uint8_t *)RDS04, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS05, 0);
    otm8009a_delay(10); 

    otm8009a_write_cmd((rt_uint8_t *)RDS06, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS07, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS08, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS09, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS10, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS11, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS01, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS12, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS13, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS14, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS15, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS16, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS17, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS18, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS19, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS09, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS01, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL05, 2);
    otm8009a_write_cmd((rt_uint8_t *)RDS20, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS21, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS22, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS23, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS24, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS25, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS13, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS26, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS15, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS27, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS28, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL06, 2);
    otm8009a_write_cmd((rt_uint8_t *)RDS02, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL07, 6);
    otm8009a_write_cmd((rt_uint8_t *)RDS29, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL08, 14);
    otm8009a_write_cmd((rt_uint8_t *)RDS30, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL09, 14);
    otm8009a_write_cmd((rt_uint8_t *)RDS31, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL10, 10);
    otm8009a_write_cmd((rt_uint8_t *)RDS32, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS46, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS02, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL11, 10);
    otm8009a_write_cmd((rt_uint8_t *)RDS33, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL12, 15);
    otm8009a_write_cmd((rt_uint8_t *)RDS29, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL13, 15);
    otm8009a_write_cmd((rt_uint8_t *)RDS30, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL14, 10);
    otm8009a_write_cmd((rt_uint8_t *)RDS31, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL15, 15);
    otm8009a_write_cmd((rt_uint8_t *)RDS32, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL16, 15);
    otm8009a_write_cmd((rt_uint8_t *)RDS34, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL17, 10);
    otm8009a_write_cmd((rt_uint8_t *)RDS35, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL18, 10);
    otm8009a_write_cmd((rt_uint8_t *)RDS02, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL19, 10);
    otm8009a_write_cmd((rt_uint8_t *)RDS33, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL20, 15);
    otm8009a_write_cmd((rt_uint8_t *)RDS29, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL21, 15);
    otm8009a_write_cmd((rt_uint8_t *)RDS30, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL22, 10);
    otm8009a_write_cmd((rt_uint8_t *)RDS31, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL23, 15);
    otm8009a_write_cmd((rt_uint8_t *)RDS32, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL24, 15);
    otm8009a_write_cmd((rt_uint8_t *)RDS13, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS47, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS48, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS49, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS50, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS51, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS01, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL25, 3);
    otm8009a_write_cmd((rt_uint8_t *)RDS01, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS01, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL03, 16);
    otm8009a_write_cmd((rt_uint8_t *)RDS01, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL04, 16);
    otm8009a_write_cmd((rt_uint8_t *)RDS36, 0);
    otm8009a_delay(120); 
    
    switch (pixel_format)
    {
    case RTGRAPHIC_PIXEL_FORMAT_RGB565:
        otm8009a_write_cmd((rt_uint8_t *)RDS37, 0);
        break;
    case RTGRAPHIC_PIXEL_FORMAT_RGB888:
    case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
        otm8009a_write_cmd((rt_uint8_t *)RDS38, 0);
        break;
    }

    otm8009a_write_cmd((rt_uint8_t *)RDS39, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL27, 4);
    otm8009a_write_cmd((rt_uint8_t *)RDL28, 4);
    otm8009a_write_cmd((rt_uint8_t *)RDS40, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS41, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS42, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS43, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS44, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS01, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS45, 0);
}

rt_err_t otm8009a_init(void)
{
    uint32_t lcd_clock      = 27429; 
    uint32_t lanebyte_clock = 62500;
    
    uint32_t HSA = LCD_HSYNC, HFP = LCD_HFP, HBP = LCD_HBP, HACT = LCD_WIDTH;
    uint32_t VSA = LCD_VSYNC, VFP = LCD_VFP, VBP = LCD_VBP, VACT = LCD_HEIGHT;
    
    /* ��λOTM8009A��ʾ�� */ 
    otm8009a_reset(); 
    
    /* ��ʼ��STM32��ʾ��ʱ�� */ 
    __HAL_RCC_LTDC_CLK_ENABLE();
    __HAL_RCC_LTDC_FORCE_RESET();
    __HAL_RCC_LTDC_RELEASE_RESET();

    __HAL_RCC_DMA2D_CLK_ENABLE();
    __HAL_RCC_DMA2D_FORCE_RESET();
    __HAL_RCC_DMA2D_RELEASE_RESET();

    __HAL_RCC_DSI_CLK_ENABLE();
    __HAL_RCC_DSI_FORCE_RESET();
    __HAL_RCC_DSI_RELEASE_RESET();
    
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
    
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    PeriphClkInitStruct.PLLSAI.PLLSAIN       = 384;
    PeriphClkInitStruct.PLLSAI.PLLSAIR       = 7;
    PeriphClkInitStruct.PLLSAIDivR           = RCC_PLLSAIDIVR_2;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
    
    /* ����NVIC */ 
    HAL_NVIC_SetPriority(LTDC_IRQn,  3, 0);
    HAL_NVIC_SetPriority(DMA2D_IRQn, 3, 0);
    HAL_NVIC_SetPriority(DSI_IRQn,   3, 0);

    HAL_NVIC_EnableIRQ(LTDC_IRQn);
    HAL_NVIC_EnableIRQ(DMA2D_IRQn);
    HAL_NVIC_EnableIRQ(DSI_IRQn);
    
    /* ����DSI */ 
    DSI_PLLInitTypeDef dsi_pll;
    
    lcd.dsi.Instance = DSI; 
    lcd.dsi.Init.NumberOfLanes = DSI_TWO_DATA_LANES;
    lcd.dsi.Init.TXEscapeCkdiv = lanebyte_clock / 15620;
    
    dsi_pll.PLLNDIV  = 125;
    dsi_pll.PLLIDF   = DSI_PLL_IN_DIV2;
    dsi_pll.PLLODF   = DSI_PLL_OUT_DIV1; 
    
    HAL_DSI_DeInit(&(lcd.dsi)); 
    HAL_DSI_Init(&(lcd.dsi), &(dsi_pll)); 
    
    /* ����DSI Video */ 
    lcd.dsi_video.VirtualChannelID             = 0;
    lcd.dsi_video.ColorCoding                  = DSI_RGB888;
    lcd.dsi_video.VSPolarity                   = DSI_VSYNC_ACTIVE_HIGH;
    lcd.dsi_video.HSPolarity                   = DSI_HSYNC_ACTIVE_HIGH;
    lcd.dsi_video.DEPolarity                   = DSI_DATA_ENABLE_ACTIVE_HIGH;
    lcd.dsi_video.Mode                         = DSI_VID_MODE_BURST; 
    lcd.dsi_video.NullPacketSize               = 0xFFF;
    lcd.dsi_video.NumberOfChunks               = 0;
    lcd.dsi_video.PacketSize                   = HACT; 
    lcd.dsi_video.HorizontalSyncActive         = (HSA * lanebyte_clock) / lcd_clock;
    lcd.dsi_video.HorizontalBackPorch          = (HBP * lanebyte_clock) / lcd_clock;
    lcd.dsi_video.HorizontalLine               = ((HACT + HSA + HBP + HFP) * lanebyte_clock) / lcd_clock; 
    lcd.dsi_video.VerticalSyncActive           = VSA;
    lcd.dsi_video.VerticalBackPorch            = VBP;
    lcd.dsi_video.VerticalFrontPorch           = VFP;
    lcd.dsi_video.VerticalActive               = VACT; 
    lcd.dsi_video.LPCommandEnable              = DSI_LP_COMMAND_ENABLE; 
    lcd.dsi_video.LPLargestPacketSize          = 16;
    lcd.dsi_video.LPVACTLargestPacketSize      = 0;
    lcd.dsi_video.LPHorizontalFrontPorchEnable = DSI_LP_HFP_ENABLE; 
    lcd.dsi_video.LPHorizontalBackPorchEnable  = DSI_LP_HBP_ENABLE; 
    lcd.dsi_video.LPVerticalActiveEnable       = DSI_LP_VACT_ENABLE; 
    lcd.dsi_video.LPVerticalFrontPorchEnable   = DSI_LP_VFP_ENABLE; 
    lcd.dsi_video.LPVerticalBackPorchEnable    = DSI_LP_VBP_ENABLE; 
    lcd.dsi_video.LPVerticalSyncActiveEnable   = DSI_LP_VSYNC_ENABLE; 
    HAL_DSI_ConfigVideoMode(&(lcd.dsi), &(lcd.dsi_video)); 
    
    /* ����DSI PHY */ 
    DSI_PHY_TimerTypeDef dsi_phy;
    
    dsi_phy.ClockLaneHS2LPTime  = 35;
    dsi_phy.ClockLaneLP2HSTime  = 35;
    dsi_phy.DataLaneHS2LPTime   = 35;
    dsi_phy.DataLaneLP2HSTime   = 35;
    dsi_phy.DataLaneMaxReadTime = 0;
    dsi_phy.StopWaitTime        = 10;
    HAL_DSI_ConfigPhyTimer(&(lcd.dsi), &dsi_phy); 
    
    /* ����LTDC */ 
    lcd.ltdc.Instance = LTDC;
    
    lcd.ltdc.Init.PCPolarity         = LTDC_PCPOLARITY_IPC;
    lcd.ltdc.Init.HorizontalSync     = (HSA - 1);
    lcd.ltdc.Init.AccumulatedHBP     = (HSA + HBP - 1);
    lcd.ltdc.Init.AccumulatedActiveW = (LCD_WIDTH + HSA + HBP - 1);
    lcd.ltdc.Init.TotalWidth         = (LCD_WIDTH + HSA + HBP + HFP - 1);
    
    lcd.ltdc.LayerCfg->ImageWidth    = LCD_WIDTH;
    lcd.ltdc.LayerCfg->ImageHeight   = LCD_HEIGHT; 
    lcd.ltdc.Init.Backcolor.Blue     = 0x00;
    lcd.ltdc.Init.Backcolor.Green    = 0x00;
    lcd.ltdc.Init.Backcolor.Red      = 0x00;
    HAL_LTDCEx_StructInitFromVideoConfig(&(lcd.ltdc), &(lcd.dsi_video)); 
    HAL_LTDC_Init(&(lcd.ltdc));
    
    HAL_DSI_Start(&(lcd.dsi)); 
    
    otm8009a_config(RTGRAPHIC_PIXEL_FORMAT_ARGB888); 
    
    return RT_EOK; 
}

void otm8009a_layer_init(uint16_t index, uint32_t framebuffer)
{
    LTDC_LayerCfgTypeDef layer_cfg;

    layer_cfg.WindowX0        = 0;
    layer_cfg.WindowX1        = LCD_WIDTH; 
    layer_cfg.WindowY0        = 0;
    layer_cfg.WindowY1        = LCD_HEIGHT;
    layer_cfg.PixelFormat     = LTDC_PIXEL_FORMAT_ARGB8888;
    layer_cfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
    layer_cfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
    layer_cfg.Alpha           = 255;
    layer_cfg.Alpha0          = 0;
    layer_cfg.ImageWidth      = LCD_WIDTH;
    layer_cfg.ImageHeight     = LCD_HEIGHT;
    layer_cfg.Backcolor.Blue  = 0;
    layer_cfg.Backcolor.Green = 0;
    layer_cfg.Backcolor.Red   = 0;
    layer_cfg.FBStartAdress   = framebuffer;

    HAL_LTDC_ConfigLayer(&(lcd.ltdc), &layer_cfg, index);
}

static void otm8009a_display_on(void)
{
    HAL_DSI_ShortWrite(&(lcd.dsi), lcd.dsi_video.VirtualChannelID, DSI_DCS_SHORT_PKT_WRITE_P1, 0x29, 0x00);
}

static void otm8009a_display_off(void)
{
    HAL_DSI_ShortWrite(&(lcd.dsi), lcd.dsi_video.VirtualChannelID, DSI_DCS_SHORT_PKT_WRITE_P1, 0x28, 0x00);
}

void LTDC_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_LTDC_IRQHandler(&(lcd.ltdc)); 
    rt_interrupt_leave();
}

/* ���Դ���: ---------------------------------------- */ 
static void lcd_fill_buffer(void *addr, uint32_t x_size, uint32_t y_size, uint32_t offset, uint32_t color)
{
    lcd.dma2d.Instance = DMA2D;
    
    lcd.dma2d.Init.Mode         = DMA2D_R2M;
    lcd.dma2d.Init.ColorMode    = DMA2D_ARGB8888;
    lcd.dma2d.Init.OutputOffset = offset;
    
    if (HAL_DMA2D_Init(&lcd.dma2d) == HAL_OK)
    {
        if (HAL_DMA2D_ConfigLayer(&lcd.dma2d, 0) == HAL_OK)
        {
            if (HAL_DMA2D_Start(&lcd.dma2d, color, (uint32_t)addr, x_size, y_size) == HAL_OK)
            {
                HAL_DMA2D_PollForTransfer(&lcd.dma2d, 10);
            }
        }
    }
} 

void lcd_clear(uint32_t color)
{
    /* Clear the LCD */
    lcd_fill_buffer((uint32_t *)(lcd.ltdc.LayerCfg[0].FBStartAdress), LCD_WIDTH, LCD_HEIGHT, 0, color);
}

void lcd_fill_rect(uint16_t x_pos, uint16_t y_pos, uint16_t width, uint16_t height)
{
    uint32_t Xaddress = (lcd.ltdc.LayerCfg[0].FBStartAdress) + 4 * (LCD_WIDTH * x_pos + y_pos);
    lcd_fill_buffer((uint32_t *)Xaddress, width, height, (LCD_WIDTH - width), 0xFF00FF00);
}

/* ���Դ��� ----------------------------------------- */

static rt_err_t stm32_lcd_init(rt_device_t device)
{
    lcd.info.width          = LCD_WIDTH;
    lcd.info.height         = LCD_HEIGHT;
    lcd.info.pixel_format   = RTGRAPHIC_PIXEL_FORMAT_ARGB888;
    lcd.info.bits_per_pixel = 32;
    lcd.info.framebuffer    = (void *)rt_malloc_align(LCD_WIDTH * LCD_HEIGHT * (lcd.info.bits_per_pixel / 8), 32); 
    otm8009a_init(); 
    otm8009a_layer_init(0, (uint32_t)lcd.info.framebuffer); 
    lcd_clear(0xFF000000); 
    
    return RT_EOK;
}

static rt_err_t stm32_lcd_control(rt_device_t device, int cmd, void *args)
{
    switch(cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
        break;

    case RTGRAPHIC_CTRL_POWERON: 
        otm8009a_display_on(); 
        break;

    case RTGRAPHIC_CTRL_POWEROFF: 
        otm8009a_display_off(); 
        break;

    case RTGRAPHIC_CTRL_GET_INFO:
        rt_memcpy(args, &lcd.info, sizeof(lcd.info));
        break;

    case RTGRAPHIC_CTRL_SET_MODE:
        break;

    case RTGRAPHIC_CTRL_GET_EXT:
        break;
    }

    return RT_EOK;
}

int rt_hw_lcd_init(void)
{
    rt_err_t ret; 
    
    rt_memset(&lcd, 0x00, sizeof(lcd)); 

    lcd.device.type    = RT_Device_Class_Graphic;
    lcd.device.init    = stm32_lcd_init;
    lcd.device.open    = RT_NULL;
    lcd.device.close   = RT_NULL;
    lcd.device.read    = RT_NULL;
    lcd.device.write   = RT_NULL;
    lcd.device.control = stm32_lcd_control;

    lcd.device.user_data = (void *)&lcd.info;

    ret = rt_device_register(&lcd.device, "lcd", RT_DEVICE_FLAG_RDWR);

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_lcd_init);

#endif /* BSP_USING_LCD_OTM8009A */
