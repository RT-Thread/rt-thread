/******************************************************************************
 * Copyright (C) 2016, Huada Semiconductor Co.,Ltd All rights reserved.
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
/** \file drv_lcd.c
 **
 ** History:
 **
 **   - 2018-06-04  1.0  Jason      First version.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtdevice.h>
#include "clk.h"
#include "gpio.h"
#include "exmc.h"
#include "hw_delay.h"
#include "irq_map.h"
#include "interrupts_hc32f480.h"
#ifdef PKG_USING_EASYLOGGER
#include "elog.h"
#endif
#ifdef PKG_USING_LITTLEVGL2RTT
#include "littlevgl2rtt.h"
#endif
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

struct lcd_info
{
    rt_uint16_t                         width;
    rt_uint16_t                         height;
    rt_uint16_t                         id;
    rt_uint8_t                          dir;
    rt_uint16_t                         wramcmd;
    rt_uint16_t                         setxcmd;
    rt_uint16_t                         setycmd;
};

struct lcd_ili9341
{
    volatile rt_uint16_t                reg;
    volatile rt_uint16_t                ram;
};

struct hc32_lcd
{
    struct rt_device                    device;
    struct rt_device_graphic_ops        ops;
    struct lcd_info                     info;
};



/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define LCD_TAG                         "[LCD]"

/* Use ADD0 as LCD_RS. */
#define LCD_DEV_BASE                    ((rt_uint32_t)(0x70000000))
#define LCD_DEV                         ((struct lcd_ili9341 *)LCD_DEV_BASE)

#define LCD_RST_GPIO_PORT               Port0
#define LCD_RST_GPIO_PIN                Pin13
#define LCD_BK_LIGHT_GPIO_PORT          Port4
#define LCD_BK_LIGHT_GPIO_PIN           Pin04

#define LCD_BACKLIGHT_ON                (1u)
#define LCD_BACKLIGHT_OFF               (0u)

#define LCD_IC_MODEL_NAME               (0x9341)

#define LCD_CMD_IC_MODEL_NAME           (0xD3)
#define LCD_CMD_MEM_ACCESS_CTRL         (0x36)
#define LCD_CMD_MEM_WRITE               (0x2C)
#define LCD_CMD_MEM_READ                (0x2E)
#define LCD_CMD_MEM_COLUMN              (0x2A)
#define LCD_CMD_MEM_PAGE                (0x2B)

#define LCD_DISPLAY_VER                 (1)
#define LCD_DISPLAY_HOR                 (0)

/* Scan direction. */
#define L2R_U2D                         0       //left to right, up to down
#define L2R_D2U                         1       //left to right, down to up
#define R2L_U2D                         2       //right to left, up to down
#define R2L_D2U                         3       //right to left, down to up
#define U2D_L2R                         4       //up to down, left to right
#define U2D_R2L                         5       //up to down, right to left
#define D2U_L2R                         6       //down to up, left to right
#define D2U_R2L                         7       //down to up, right to left
#define DFT_SCAN_DIR                    L2R_U2D //default

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static struct hc32_lcd lcd;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

rt_inline void lcd_write_reg(uint16_t cmd)
{
    LCD_DEV->reg = cmd;
}

rt_inline void lcd_write_data(uint16_t data)
{
    LCD_DEV->ram = data;
}

rt_inline uint16_t lcd_read_data(void)
{
    return LCD_DEV->ram;
}

rt_inline void lcd_prepare_to_write_data(void)
{
    lcd_write_reg(LCD_CMD_MEM_WRITE);
}

rt_inline uint16_t lcd_read_id(void)
{
    uint16_t id = 0;
    lcd_write_reg(LCD_CMD_IC_MODEL_NAME);

    /* Dummy data. */
    id = lcd_read_data();

    /* Ic version. */
    id = lcd_read_data();

    /* Ic model name. */
    id = lcd_read_data();
    id <<= 8;

    id |= lcd_read_data();

    return id;
}

static void lcd_set_cursor(rt_uint16_t x, rt_uint16_t y)
{
    lcd_write_reg(lcd.info.setxcmd);
    lcd_write_data(x >> 8);
    lcd_write_data(x & 0XFF);

    lcd_write_reg(lcd.info.setycmd);
    lcd_write_data(y >> 8);
    lcd_write_data(y & 0XFF);
}

rt_inline void lcd_set_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    /* x1 is start column,x2 is end column. */
    lcd_write_reg(lcd.info.setxcmd);
    lcd_write_data(x1>>8);
    lcd_write_data(x1&0xff);
    lcd_write_data(x2>>8);
    lcd_write_data(x2&0xff);

    /* y1 is start row,y2 is end row. */
    lcd_write_reg(lcd.info.setycmd);
    lcd_write_data(y1>>8);
    lcd_write_data(y1&0xff);
    lcd_write_data(y2>>8);
    lcd_write_data(y2&0xff);
}

rt_inline void lcd_set_scan_direction(rt_uint8_t dir)
{
    rt_uint16_t regval = (1 << 3);
    rt_uint16_t temp;

    switch (dir)
    {
    case L2R_U2D:
        regval |= (0 << 7) | (0 << 6) | (0 << 5);
        break;
    case L2R_D2U:
        regval |= (1 << 7) | (0 << 6) | (0 << 5);
        break;
    case R2L_U2D:
        regval |= (0 << 7) | (1 << 6) | (0 << 5);
        break;
    case R2L_D2U:
        regval |= (1 << 7) | (1 << 6) | (0 << 5);
        break;
    case U2D_L2R:
        regval |= (0 << 7) | (0 << 6) | (1 << 5);
        break;
    case U2D_R2L:
        regval |= (0 << 7) | (1 << 6) | (1 << 5);
        break;
    case D2U_L2R:
        regval |= (1 << 7) | (0 << 6) | (1 << 5);
        break;
    case D2U_R2L:
        regval |= (1 << 7) | (1 << 6) | (1 << 5);
        break;
    }

    lcd_write_reg(LCD_CMD_MEM_ACCESS_CTRL);
    lcd_write_data(regval);

    if (regval & 0X20)
    {
        if (lcd.info.width < lcd.info.height)//Switch x and y.
        {
            temp = lcd.info.width;
            lcd.info.width = lcd.info.height;
            lcd.info.height = temp;
        }
    }
    else
    {
        if (lcd.info.width > lcd.info.height)//Switch x and y.
        {
            temp = lcd.info.width;
            lcd.info.width = lcd.info.height;
            lcd.info.height = temp;
        }
    }

    lcd_set_rect(0, 0, lcd.info.width - 1, lcd.info.height - 1);
}

rt_inline void lcd_set_display_direction(rt_uint8_t dir)
{
    lcd.info.dir = dir;

    if (dir == 0)
    {
        lcd.info.width = RT_LCD_HOR_RES;
        lcd.info.height = RT_LCD_VER_RES;
    }
    else
    {
        lcd.info.width = RT_LCD_VER_RES;
        lcd.info.height = RT_LCD_HOR_RES;
    }

    lcd.info.wramcmd = LCD_CMD_MEM_WRITE;
    lcd.info.setxcmd = LCD_CMD_MEM_COLUMN;
    lcd.info.setycmd = LCD_CMD_MEM_PAGE;

    lcd_set_scan_direction(DFT_SCAN_DIR);
}

static void lcd_set_pixel(const char* pixel, int x, int y)
{
    lcd_set_cursor(x, y);
    lcd_prepare_to_write_data();
    lcd_write_data(*(uint16_t *)pixel);
}

static void lcd_get_pixel(char* pixel, int x, int y)
{
    rt_uint16_t red = 0;
    rt_uint16_t green = 0;
    rt_uint16_t blue = 0;

    if (x >= lcd.info.width || y >= lcd.info.height)
    {
        *(rt_uint16_t*)pixel = 0;
        return;
    }

    lcd_set_cursor(x, y);

    lcd_write_reg(LCD_CMD_MEM_READ);
    lcd_read_data();
    red = lcd_read_data();
    hw_delay_us(2);

    blue = lcd_read_data();
    green = red & 0XFF;

    *(rt_uint16_t*)pixel = (((red >> 11) << 11) | ((green >> 10) << 5) | (blue >> 11));
}

static void lcd_draw_hline(const char* pixel, int x1, int x2, int y)
{
    lcd_set_cursor(x1, y);
    lcd_prepare_to_write_data();

    for (; x1 < x2; x1++)
    {
        lcd_write_data(*(uint16_t *)pixel);
    }
}

static void lcd_draw_vline(const char* pixel, int x, int y1, int y2)
{
    lcd_set_rect(x,y1,x,y2);
    lcd_prepare_to_write_data();

    for (; y1 < y2; y1++)
    {
        lcd_write_data(*(uint16_t *)pixel);
    }
}

static void lcd_blit_line(const char* pixels, int x, int y, rt_size_t size)
{
    rt_uint16_t *ptr = (rt_uint16_t *)pixels;

    lcd_set_cursor(x, y);
    lcd_prepare_to_write_data();

    for(int x = 0; x <= size - 1; x++)
    {
        lcd_write_data(*ptr++);
    }
}

static void lcd_backlight(uint8_t onoff)
{
    if(LCD_BACKLIGHT_ON == onoff)
    {
        Port_ResetBits(LCD_BK_LIGHT_GPIO_PORT, LCD_BK_LIGHT_GPIO_PIN);
    }
    else
    {
        Port_SetBits(LCD_BK_LIGHT_GPIO_PORT, LCD_BK_LIGHT_GPIO_PIN);
    }
}

static void lcd_gpio_init(void)
{
    stc_port_init_t stcPortInit;
    memset(&stcPortInit, 0x00, sizeof(stcPortInit));

    /* Config gpio 4. LCD_BKL. */
    /* Port 4. OUT,NOD,High drive,UP. */
    stcPortInit.enPinMode = Pin_Mode_Out;
    stcPortInit.enPinOType = Pin_OType_Cmos;
    stcPortInit.enPinDrv = Pin_Drv_H;
    stcPortInit.bPuEn = TRUE;
    Port_Init(LCD_BK_LIGHT_GPIO_PORT, LCD_BK_LIGHT_GPIO_PIN, stcPortInit);

    /* Config gpio 2.And mapping to EXMC.Map LCD_D0~LCD_d15 to EXMC_DATA0~EXMC_DATA15. */
    /* Port 0~15. SUB,NOD,High drive,UP. */
    stcPortInit.enPinMode = Pin_Mode_Out;
    stcPortInit.enPinOType = Pin_OType_Cmos;
    stcPortInit.enPinDrv = Pin_Drv_H;
    stcPortInit.bPuEn = TRUE;
    Port_Init(Port2, PinAll, stcPortInit);
    /* enable write  for PORT regs */
    Port_Unlock();
    Port_SetFunc(Port2, Pin00, Func_Exmc, Disable);
    Port_SetFunc(Port2, Pin01, Func_Exmc, Disable);
    Port_SetFunc(Port2, Pin02, Func_Exmc, Disable);
    Port_SetFunc(Port2, Pin03, Func_Exmc, Disable);
    Port_SetFunc(Port2, Pin04, Func_Exmc, Disable);
    Port_SetFunc(Port2, Pin05, Func_Exmc, Disable);
    Port_SetFunc(Port2, Pin06, Func_Exmc, Disable);
    Port_SetFunc(Port2, Pin07, Func_Exmc, Disable);
    Port_SetFunc(Port2, Pin08, Func_Exmc, Disable);
    Port_SetFunc(Port2, Pin09, Func_Exmc, Disable);
    Port_SetFunc(Port2, Pin10, Func_Exmc, Disable);
    Port_SetFunc(Port2, Pin11, Func_Exmc, Disable);
    Port_SetFunc(Port2, Pin12, Func_Exmc, Disable);
    Port_SetFunc(Port2, Pin13, Func_Exmc, Disable);
    Port_SetFunc(Port2, Pin14, Func_Exmc, Disable);
    Port_SetFunc(Port2, Pin15, Func_Exmc, Disable);
    Port_Lock();

    /* Config gpio 6.And mapping to EXMC.Map LCD_RS to EXMC_ADD0. */
    /* Port 7. SUB,NOD,High drive,UP. */
    stcPortInit.enPinMode = Pin_Mode_Out;
    stcPortInit.enPinOType = Pin_OType_Cmos;
    stcPortInit.enPinDrv = Pin_Drv_H;
    stcPortInit.bPuEn = TRUE;
    Port_Init(Port6, Pin07, stcPortInit);
    /* enable write  for PORT regs */
    Port_Unlock();
    Port_SetFunc(Port6, Pin07, Func_Exmc, Disable);
    Port_Lock();

    /* Config gpio 3.And mapping to EXMC.Map LCD_RD and LCD_WR to EXMC_OE and EXMC_WE. */
    /* Port 0~1. SUB,NOD,High drive,UP. */
    stcPortInit.enPinMode = Pin_Mode_Out;
    stcPortInit.enPinOType = Pin_OType_Cmos;
    stcPortInit.enPinDrv = Pin_Drv_H;
    stcPortInit.bPuEn = TRUE;
    Port_Init(Port3, Pin00, stcPortInit);
    Port_Init(Port3, Pin01, stcPortInit);
    /* enable write  for PORT regs */
    Port_Unlock();
    Port_SetFunc(Port3, Pin00, Func_Exmc, Disable);
    Port_SetFunc(Port3, Pin01, Func_Exmc, Disable);
    Port_Lock();

    /* Config gpio 1.And mapping to EXMC.Map LCD_CS to EXMC_CE2. */
    /* Port 5. SUB,NOD,High drive,UP. */
    stcPortInit.enPinMode = Pin_Mode_Out;
    stcPortInit.enPinOType = Pin_OType_Cmos;
    stcPortInit.enPinDrv = Pin_Drv_H;
    stcPortInit.bPuEn = TRUE;
    Port_Init(Port1, Pin05, stcPortInit);
    /* enable write  for PORT regs */
    Port_Unlock();
    Port_SetFunc(Port1, Pin05, Func_Exmc, Disable);
    Port_Lock();

    /* Config gpio 0. LCD_RST. */
    /* Port 13. OUT,NOD,High drive,UP. */
    stcPortInit.enPinMode = Pin_Mode_Out;
    stcPortInit.enPinOType = Pin_OType_Cmos;
    stcPortInit.enPinDrv = Pin_Drv_H;
    stcPortInit.bPuEn = TRUE;
    Port_Init(LCD_RST_GPIO_PORT, LCD_RST_GPIO_PIN, stcPortInit);
}

static void lcd_reset(void)
{
    /* Low level to reset. */
    Port_ResetBits(LCD_RST_GPIO_PORT, LCD_RST_GPIO_PIN);
    hw_delay_ms(50);

    Port_SetBits(LCD_RST_GPIO_PORT, LCD_RST_GPIO_PIN);
    hw_delay_ms(50);
}

static void lcd_exmc_init(void)
{
    stc_SMCInit_TypeDef stc_SmcInit;

    un_SmcTmcr_Typedef unSmcTmcr;
    /* set addr and data not reuse. */
    stc_SmcInit.SmcMux = Disable;
    /* set time parameters for SMC.*/
    unSmcTmcr.smc_tmcr_bit.rc = 3;
    unSmcTmcr.smc_tmcr_bit.wc = 4;
    unSmcTmcr.smc_tmcr_bit.ceoe = 1;
    unSmcTmcr.smc_tmcr_bit.wp = 2;
    unSmcTmcr.smc_tmcr_bit.pc = 0;
    unSmcTmcr.smc_tmcr_bit.tr = 0;
    stc_SmcInit.SmcTmcr.smc_tmcr_byte = unSmcTmcr.smc_tmcr_byte;
    /* set SMC memory width as 16 bit.*/
    stc_SmcInit.SmcBacr.mw = SWidth16;
    /* asynchronous read.*/
    stc_SmcInit.SmcBacr.rsyn = SynEn;
    /* busrt read length : 1.*/
    stc_SmcInit.SmcBacr.rbl = Length_four;
    /* asynchronous write.*/
    stc_SmcInit.SmcBacr.wsyn = SynEn;
    /* busrt write length : 1.*/
    stc_SmcInit.SmcBacr.wbl = Length_four;
    /* Disable BAA.*/
    stc_SmcInit.SmcBacr.baas = Disable;
    /* Disable ADV.*/
    stc_SmcInit.SmcBacr.advs = Disable;
    /* Bls state synchronous with We.*/
    stc_SmcInit.SmcBacr.blss = SynCs;
    /* cmd UpdataRegs*/
    stc_SmcInit.SmcCmdr.cmd = UpdataRegs;
    stc_SmcInit.SmcCmdr.cmdaddr = 0;
    stc_SmcInit.SmcCmdr.cres = Disable;
    /* Enable EXMC clock. */
    Clk_Fcg1PeriphClockCmd(CLK_FCG1_PERIPH_EXMC_SMC, Enable);

    exmc_smc_init(&stc_SmcInit);

    exmc_smc_enable();
}

static void lcd_reg_config(void)
{
    hw_delay_ms(50);

    lcd.info.id = lcd_read_id();

#ifdef PKG_USING_EASYLOGGER
    elog_info(LCD_TAG,"id:0x%x\n",lcd.info.id);
#endif

    RT_ASSERT(LCD_IC_MODEL_NAME == lcd.info.id);

    /* Power control B (CFh)  */
    lcd_write_reg(0xCF);
    lcd_write_data(0x00);
    lcd_write_data(0x81);
    lcd_write_data(0x30);

    /* Power on sequence control (EDh) */
    lcd_write_reg(0xED);
    lcd_write_data(0x64);
    lcd_write_data(0x03);
    lcd_write_data(0x12);
    lcd_write_data(0x81);

    /* Driver timing control A (E8h) */
    lcd_write_reg(0xE8);
    lcd_write_data(0x85);
    lcd_write_data(0x10);
    lcd_write_data(0x78);

    /* Power control A (CBh) */
    lcd_write_reg(0xCB);
    lcd_write_data(0x39);
    lcd_write_data(0x2C);
    lcd_write_data(0x00);
    lcd_write_data(0x34);
    lcd_write_data(0x02);

    /* Pump ratio control (F7h) */
    lcd_write_reg(0xF7);
    lcd_write_data(0x20);

    /* Driver timing control B */
    lcd_write_reg(0xEA);
    lcd_write_data(0x00);
    lcd_write_data(0x00);

    /* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
    lcd_write_reg(0xB1);
    lcd_write_data(0x00);
    lcd_write_data(0x1B);

    /* Display Function Control (B6h) */
    lcd_write_reg(0xB6);
    lcd_write_data(0x0A);
    lcd_write_data(0xA2);

    /* Power Control 1 (C0h) */
    lcd_write_reg(0xC0);
    lcd_write_data(0x35);

    /* Power Control 2 (C1h) */
    lcd_write_reg(0xC1);
    lcd_write_data(0x11);

    /* VCOM Control 1(C5h) */
    lcd_write_reg(0xC5);
    lcd_write_data(0x45);

    /* VCOM Control 2(C7h) */
    lcd_write_reg(0xC7);
    lcd_write_data(0xA2);

    /* Enable 3G (F2h) */
    lcd_write_reg(0xF2);
    lcd_write_data(0x00);

    /* Gamma Set (26h) */
    lcd_write_reg(0x26);
    lcd_write_data(0x01);

    /* Positive Gamma Correction */
    lcd_write_reg(0xE0); //Set Gamma
    lcd_write_data(0x0F);
    lcd_write_data(0x26);
    lcd_write_data(0x24);
    lcd_write_data(0x0B);
    lcd_write_data(0x0E);
    lcd_write_data(0x09);
    lcd_write_data(0x54);
    lcd_write_data(0xA8);
    lcd_write_data(0x46);
    lcd_write_data(0x0C);
    lcd_write_data(0x17);
    lcd_write_data(0x09);
    lcd_write_data(0x0F);
    lcd_write_data(0x07);
    lcd_write_data(0x00);

    /* Negative Gamma Correction (E1h) */
    lcd_write_reg(0XE1); //Set Gamma
    lcd_write_data(0x00);
    lcd_write_data(0x19);
    lcd_write_data(0x1B);
    lcd_write_data(0x04);
    lcd_write_data(0x10);
    lcd_write_data(0x07);
    lcd_write_data(0x2A);
    lcd_write_data(0x47);
    lcd_write_data(0x39);
    lcd_write_data(0x03);
    lcd_write_data(0x06);
    lcd_write_data(0x06);
    lcd_write_data(0x30);
    lcd_write_data(0x38);
    lcd_write_data(0x0F);

    /* memory access control set */
    //lcd_write_reg(0x36);
    //lcd_write_data(LCD_DISPLAY_VER);

    /* column address control set */
    lcd_write_reg(0X2A);
    lcd_write_data(0x00);
    lcd_write_data(0x00);
    lcd_write_data(0x00);
    lcd_write_data(0xEF);

    /* page address control set */
    lcd_write_reg(0X2B);
    lcd_write_data(0x00);
    lcd_write_data(0x00);
    lcd_write_data(0x01);
    lcd_write_data(0x3F);

    /* Pixel Format Set (3Ah)  */
    lcd_write_reg(0x3a);
    lcd_write_data(0x55);

    /* Sleep Out (11h)  */
    lcd_write_reg(0x11);
    hw_delay_ms(120);

    /* Display ON (29h) */
    lcd_write_reg(0x29);
}

static void lcd_cmd_init(void)
{
    lcd_reset();
    lcd_reg_config();
    lcd_set_display_direction(LCD_DISPLAY_HOR);
}

static rt_err_t lcd_init(rt_device_t dev)
{
#ifdef PKG_USING_EASYLOGGER
    elog_info(LCD_TAG,"init in\n");
#endif

    lcd_gpio_init();

    lcd_exmc_init();

    lcd_backlight(LCD_BACKLIGHT_ON);

    lcd_cmd_init();

#ifdef PKG_USING_EASYLOGGER
    elog_info(LCD_TAG,"init success\n");
#endif

    return RT_EOK;
}

static rt_err_t lcd_control(rt_device_t dev, int cmd, void *args)
{
    switch(cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
        break;

    case RTGRAPHIC_CTRL_POWERON:
        lcd_backlight(LCD_BACKLIGHT_ON);
        break;

    case RTGRAPHIC_CTRL_POWEROFF:
        lcd_backlight(LCD_BACKLIGHT_OFF);
        break;

    case RTGRAPHIC_CTRL_GET_INFO:
    {
        struct rt_device_graphic_info *info;

        info = (struct rt_device_graphic_info*) args;
        RT_ASSERT(info != RT_NULL);

        info->bits_per_pixel = 16;
        info->pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565;
        info->framebuffer = RT_NULL;
        info->width = RT_LCD_HOR_RES;
        info->height = RT_LCD_VER_RES;
    }
        break;

    case RTGRAPHIC_CTRL_SET_MODE:
        break;
    }

    return RT_EOK;
}

int hc32_lcd_hw_init(void)
{
    lcd.device.type         = RT_Device_Class_Graphic;
    lcd.device.init         = lcd_init;
    lcd.device.open         = RT_NULL;
    lcd.device.close        = RT_NULL;
    lcd.device.read         = RT_NULL;
    lcd.device.write        = RT_NULL;
    lcd.device.control      = lcd_control;

    lcd.ops.set_pixel       = lcd_set_pixel;
    lcd.ops.get_pixel       = lcd_get_pixel;
    lcd.ops.draw_hline      = lcd_draw_hline;
    lcd.ops.draw_vline      = lcd_draw_vline;
    lcd.ops.blit_line       = lcd_blit_line;

    lcd.device.user_data    = (void *)&lcd.ops;

    rt_device_register(&lcd.device, RT_LCD_DEVICE_NAME, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);

    return 0;
}


INIT_BOARD_EXPORT(hc32_lcd_hw_init);


