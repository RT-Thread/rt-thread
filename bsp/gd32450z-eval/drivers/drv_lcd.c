/*
 * File      : usart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-23     Tanek        the first version
 */

#include "gd32f450z_lcd_eval.h"
#include <gd32f4xx.h>
#include <drv_usart.h>
#include <board.h>
#include <finsh.h>

#ifdef PKG_USING_GUIENGINE


#define RT_HW_LCD_WIDTH                ((uint16_t)320)     /* LCD PIXEL WIDTH            */
#define RT_HW_LCD_HEIGHT               ((uint16_t)480)     /* LCD PIXEL HEIGHT           */

#define LCD_480_320_HSYNC              ((uint32_t)10)      /* Horizontal synchronization */
#define LCD_480_320_HBP                ((uint32_t)20)     /* Horizontal back porch      */
#define LCD_480_320_HFP                ((uint32_t)40)      /* Horizontal front porch     */
#define LCD_480_320_VSYNC              ((uint32_t)2)       /* Vertical synchronization   */
#define LCD_480_320_VBP                ((uint32_t)1)      /* Vertical back porch        */
#define LCD_480_320_VFP                ((uint32_t)4)      /* Vertical front porch       */

#define LCD_BITS_PER_PIXEL             16


static rt_uint16_t *lcd_framebuffer = RT_NULL;
static rt_uint16_t *_rt_framebuffer = RT_NULL;

static struct rt_device_graphic_info _lcd_info;
static struct rt_device lcd;

/*!
    \brief      configure TLI GPIO  
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void tli_gpio_config(void)
{
    /* enable the periphral clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOF);
    rcu_periph_clock_enable(RCU_GPIOG);

    /* configure HSYNC(PC6), VSYNC(PA4), PCLK(PG7), DE(PF10) */
    /* configure LCD_R7(PG6), LCD_R6(PA8), LCD_R5(PA12), LCD_R4(PA11), LCD_R3(PB0), 
                 LCD_G7(PD3), LCD_G6(PC7), LCD_G5(PB11), LCD_G4(PB10), LCD_G3(PG10), LCD_G2(PA6),
                 LCD_B7(PB9), LCD_B6(PB8), LCD_B5(PA3), LCD_B4(PG12), LCD_B3(PG11) */
    gpio_af_set(GPIOA,GPIO_AF_14,GPIO_PIN_3);  
    gpio_af_set(GPIOA,GPIO_AF_14,GPIO_PIN_4);
    gpio_af_set(GPIOA,GPIO_AF_14,GPIO_PIN_6);  
    gpio_af_set(GPIOA,GPIO_AF_14,GPIO_PIN_12); 
    gpio_af_set(GPIOA,GPIO_AF_14,GPIO_PIN_11);  
    gpio_af_set(GPIOA,GPIO_AF_14,GPIO_PIN_8); 
    
    gpio_af_set(GPIOB,GPIO_AF_9,GPIO_PIN_0);  
    gpio_af_set(GPIOB,GPIO_AF_14,GPIO_PIN_10);     
    //gpio_af_set(GPIOB,GPIO_AF_14,GPIO_PIN_11);
    gpio_af_set(GPIOB,GPIO_AF_14,GPIO_PIN_8);     
    gpio_af_set(GPIOB,GPIO_AF_14,GPIO_PIN_9);
    
    gpio_af_set(GPIOC,GPIO_AF_14,GPIO_PIN_6);     
    gpio_af_set(GPIOC,GPIO_AF_14,GPIO_PIN_7);
    
    gpio_af_set(GPIOD,GPIO_AF_14,GPIO_PIN_3);     

    gpio_af_set(GPIOF,GPIO_AF_14,GPIO_PIN_10);     
    
    gpio_af_set(GPIOG,GPIO_AF_14,GPIO_PIN_6);     
    gpio_af_set(GPIOG,GPIO_AF_14,GPIO_PIN_7);
    gpio_af_set(GPIOG,GPIO_AF_9,GPIO_PIN_10);
    gpio_af_set(GPIOG,GPIO_AF_14,GPIO_PIN_11);     
    gpio_af_set(GPIOG,GPIO_AF_9,GPIO_PIN_12);    

    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_6
    |GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_4|GPIO_PIN_3
    |GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12);

    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_0|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
    /*|GPIO_PIN_11*/);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
    /*|GPIO_PIN_11*/);

    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_6|GPIO_PIN_7);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ, GPIO_PIN_6|GPIO_PIN_7);

    gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ, GPIO_PIN_3);

    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_10);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_10|GPIO_PIN_11
    |GPIO_PIN_12);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_10|GPIO_PIN_11
    |GPIO_PIN_12);
}

/*!
    \brief      LCD Configuration
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void lcd_config(void)
{
    /* configure the LCD control line */
    lcd_ctrl_line_config();
    lcd_disable();
    lcd_enable();
    
    /* configure the GPIO of TLI */
    tli_gpio_config();
    /* configure the LCD_SPI */
    lcd_spi_config(); 

    /* power on the LCD */
    //lcd_power_on();
	lcd_power_on3();  //New Version 3.5" TFT RGB Hardware needs use this initilize funtion  ---By xufei 2016.10.21
}

/*!
    \brief      configure TLI peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void tli_config(void)
{
    tli_parameter_struct               tli_init_struct;
    tli_layer_parameter_struct         tli_layer_init_struct;
 
    rcu_periph_clock_enable(RCU_TLI);

    /* configure the PLLSAI clock to generate lcd clock */
    if(ERROR == rcu_pllsai_config(192, 2, 3, 3)){
        while(1);
    }
    rcu_tli_clock_div_config(RCU_PLLSAIR_DIV8);
    rcu_osci_on(RCU_PLLSAI_CK);
    if(ERROR == rcu_osci_stab_wait(RCU_PLLSAI_CK)){
        while(1);
    }
    
    /* TLI initialization */
    tli_init_struct.signalpolarity_hs = TLI_HSYN_ACTLIVE_LOW;
    tli_init_struct.signalpolarity_vs = TLI_VSYN_ACTLIVE_LOW;
    tli_init_struct.signalpolarity_de = TLI_DE_ACTLIVE_LOW;
    tli_init_struct.signalpolarity_pixelck = TLI_PIXEL_CLOCK_TLI;
    
    /* LCD display timing configuration */
    tli_init_struct.synpsz_hpsz   = LCD_480_320_HSYNC;
    tli_init_struct.synpsz_vpsz   = LCD_480_320_VSYNC;
    tli_init_struct.backpsz_hbpsz = LCD_480_320_HSYNC + LCD_480_320_HBP; 
    tli_init_struct.backpsz_vbpsz = LCD_480_320_VSYNC + LCD_480_320_VBP;  
    tli_init_struct.activesz_hasz = RT_HW_LCD_WIDTH + LCD_480_320_HSYNC + LCD_480_320_HBP;
    tli_init_struct.activesz_vasz = RT_HW_LCD_HEIGHT + LCD_480_320_VSYNC + LCD_480_320_VBP;
    tli_init_struct.totalsz_htsz  = RT_HW_LCD_WIDTH + LCD_480_320_HSYNC + LCD_480_320_HBP + LCD_480_320_HFP; 
    tli_init_struct.totalsz_vtsz  = RT_HW_LCD_HEIGHT + LCD_480_320_VSYNC + LCD_480_320_VBP + LCD_480_320_VFP;
    
    /* LCD background color configure*/
    tli_init_struct.backcolor_red   = 0x00;
    tli_init_struct.backcolor_green = 0x00;
    tli_init_struct.backcolor_blue  = 0x00; 
    tli_init(&tli_init_struct);
    
    lcd_framebuffer = rt_malloc(sizeof(rt_uint16_t) * RT_HW_LCD_HEIGHT * RT_HW_LCD_WIDTH);
    RT_ASSERT(lcd_framebuffer != NULL);
    rt_memset(lcd_framebuffer, 0, sizeof(rt_uint16_t) * RT_HW_LCD_WIDTH * RT_HW_LCD_HEIGHT);

    /* TLI layer0 configuration */
    tli_layer_init_struct.layer_window_leftpos          = tli_init_struct.backpsz_hbpsz + 1;
    tli_layer_init_struct.layer_window_rightpos         = tli_init_struct.backpsz_hbpsz + RT_HW_LCD_WIDTH; 
    tli_layer_init_struct.layer_window_toppos           = tli_init_struct.backpsz_vbpsz + 1;
    tli_layer_init_struct.layer_window_bottompos        = tli_init_struct.backpsz_vbpsz + RT_HW_LCD_HEIGHT;
    
    tli_layer_init_struct.layer_ppf                     = LAYER_PPF_RGB565;
    tli_layer_init_struct.layer_sa                      = 0xFF;
    tli_layer_init_struct.layer_default_blue            = 0x00;        
    tli_layer_init_struct.layer_default_green           = 0x00;       
    tli_layer_init_struct.layer_default_red             = 0x00;         
    tli_layer_init_struct.layer_default_alpha           = 0x00;
    tli_layer_init_struct.layer_acf1                    = LAYER_ACF1_PASA;    
    tli_layer_init_struct.layer_acf2                    = LAYER_ACF2_PASA;
    tli_layer_init_struct.layer_frame_bufaddr           = (uint32_t)lcd_framebuffer;    
    tli_layer_init_struct.layer_frame_line_length       = ((RT_HW_LCD_WIDTH * 2) + 3); 
    tli_layer_init_struct.layer_frame_buf_stride_offset = (RT_HW_LCD_WIDTH * 2);
    tli_layer_init_struct.layer_frame_total_line_number = RT_HW_LCD_HEIGHT; 
    
    tli_layer_init(LAYER0, &tli_layer_init_struct);
}

static rt_err_t rt_lcd_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
    {        
        memcpy((void *)lcd_framebuffer, _rt_framebuffer, sizeof(rt_uint16_t)*RT_HW_LCD_HEIGHT * RT_HW_LCD_WIDTH);
    }
    break;
    
    case RTGRAPHIC_CTRL_POWERON:
        break;
    
    case RTGRAPHIC_CTRL_POWEROFF:
        break;
    
    case RTGRAPHIC_CTRL_GET_INFO:
        memcpy(args, &_lcd_info, sizeof(_lcd_info));
        break;
    
    case RTGRAPHIC_CTRL_SET_MODE:
        break;
    }

    return RT_EOK;
}

int gd32_hw_lcd_init(void)
{
    _rt_framebuffer = rt_malloc_align(sizeof(rt_uint16_t) * RT_HW_LCD_WIDTH * RT_HW_LCD_HEIGHT, 32);
    if (_rt_framebuffer == RT_NULL) 
        return -1; /* no memory yet */
    
    lcd_config();
    tli_config();
    tli_layer_enable(LAYER0);  
    tli_reload_config(TLI_FRAME_BLANK_RELOAD_EN);
    tli_enable();
    
    _lcd_info.bits_per_pixel = LCD_BITS_PER_PIXEL;
    _lcd_info.pixel_format   = RTGRAPHIC_PIXEL_FORMAT_RGB565;
    _lcd_info.framebuffer    = (void *)_rt_framebuffer;
    _lcd_info.width          = RT_HW_LCD_WIDTH;
    _lcd_info.height         = RT_HW_LCD_HEIGHT;
    
    lcd.type    = RT_Device_Class_Graphic;
    lcd.init    = NULL;
    lcd.open    = NULL;
    lcd.close   = NULL;
    lcd.read    = NULL;
    lcd.write   = NULL;
    lcd.control = rt_lcd_control;
    lcd.user_data = (void *)&_lcd_info;
    
    /* register lcd device to RT-Thread */
    rt_device_register(&lcd, "lcd", RT_DEVICE_FLAG_RDWR);
    
    return 0;
}
INIT_DEVICE_EXPORT(gd32_hw_lcd_init);
#endif
