/****************************************************************************
 *
 * File Name
 *  oled_gui.cpp
 * Author
 *  wangk
 * Date
 *  2020/09/29
 * Descriptions:
 * OLED屏幕界面功能实现
 *
 ******************************************************************************/
/*----------------------------------------------------------------------------*
**                             Dependencies                                   *
**----------------------------------------------------------------------------*/
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <stdint.h>
#include <stdbool.h>

#include "app.h"
#include "U8g2lib.h"
#include "myfont.h"
#include "common.h"
/**---------------------------------------------------------------------------*
 **                            Debugging Flag                                 *
 **---------------------------------------------------------------------------*/
//#define OLED_GUI_DEBUG
#ifdef OLED_GUI_DEBUG
    #define OLED_GUI_TRACE rt_kprintf
#else
    #define OLED_GUI_TRACE(...)
#endif /* OLED_GUI_DEBUG */

/**---------------------------------------------------------------------------*
**                             Compiler Flag                                  *
**----------------------------------------------------------------------------*/
#ifdef __cplusplus
extern   "C"
{
#endif

/*----------------------------------------------------------------------------*
**                             Mcaro Definitions                              *
**----------------------------------------------------------------------------*/
#define OLED_POWER_PIN         GET_PIN(A, 2) // PA2

#define OLED_SPI_PIN_RES       GET_PIN(A, 4)  // PA4
#define OLED_SPI_PIN_DC        GET_PIN(A, 6)  // PA6
#define OLED_SPI_PIN_CS        GET_PIN(A, 3)  // PA3

// In u8x8.h #define U8X8_USE_PINS
#define U8G2_PIN_UP            U8X8_PIN_NONE
#define U8G2_PIN_DOWN          U8X8_PIN_NONE
#define U8G2_PIN_PREV          GET_PIN(E, 5)      // PE5(KEY0)
#define U8G2_PIN_NEXT          GET_PIN(E, 4)      // PE4(KEY1)
#define U8G2_PIN_SELECT        GET_PIN(E, 3)      // PE3(KEY2)
#define U8G2_PIN_HOME          GET_PIN(E, 2)      // PE2(KEY3)

#define OLED_GUI_THREAD_PRIORITY        25
#define OLED_GUI_THREAD_STACK_SIZE      512
#define OLED_GUI_THREAD_TIMESLICE       5

/*----------------------------------------------------------------------------*
**                             Data Structures                                *
**----------------------------------------------------------------------------*/
typedef struct
{
    uint32_t width;
    uint32_t height;
    const uint8_t* bits;
    const char* tips;
} icon_info_t;

typedef enum
{
    GUI_STATE_ENV_MENU = 0,
    GUI_STATE_ENV_INFO,
    GUI_STATE_VER_MENU,
    GUI_STATE_VER_INFO,
} oled_gui_state_e;

/*----------------------------------------------------------------------------*
**                             Local Vars                                     *
**----------------------------------------------------------------------------*/
static U8G2_SH1107_PIMORONI_128X128_F_4W_HW_SPI u8g2(U8G2_R0, 
    /* cs=*/ OLED_SPI_PIN_CS, /* dc=*/ OLED_SPI_PIN_DC, /* reset=*/ OLED_SPI_PIN_RES);

#define DISCON_ICON_WIDTH 22
#define DISCON_ICON_HEIGHT 22
static const uint8_t discon_icon_bits[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x1c, 0x00, 0xf0, 0x0f, 
    0x00, 0xf8, 0x07, 0x00, 0x1c, 0x07, 0x00, 0x0e, 0x06, 0x00, 0x0e, 0x06, 
    0x00, 0x1e, 0x06, 0xc0, 0x3f, 0x07, 0xe0, 0xf7, 0x03, 0xf0, 0xf7, 0x01, 
    0x38, 0xdf, 0x00, 0x18, 0x1c, 0x00, 0x18, 0x18, 0x00, 0x18, 0x1c, 0x00, 
    0x38, 0x0e, 0x00, 0xf8, 0x07, 0x00, 0xfc, 0x03, 0x00, 0x0e, 0x00, 0x00, 
    0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
};

#define BLE_ICON_WIDTH 24
#define BLE_ICON_HEIGHT 24
static const uint8_t ble_icon_bits[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0xf0, 0x00, 
    0x80, 0xf1, 0x01, 0x80, 0xf3, 0x03, 0x80, 0xb7, 0x07, 0x00, 0x3f, 0x07, 
    0x00, 0xbe, 0x07, 0x00, 0xfc, 0x03, 0x00, 0xf8, 0x01, 0x00, 0xf0, 0x00, 
    0x00, 0xf8, 0x01, 0x00, 0xfc, 0x03, 0x00, 0xbe, 0x07, 0x00, 0x3f, 0x07, 
    0x80, 0xb7, 0x07, 0x80, 0xf3, 0x03, 0x80, 0xf1, 0x01, 0x00, 0xf0, 0x00, 
    0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

#define USB_ICON_WIDTH 24
#define USB_ICON_HEIGHT 24
static const uint8_t usb_icon_bits[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xfe, 0x00, 0x00, 0xff, 0x00, 
    0x00, 0xf7, 0x00, 0x8e, 0x03, 0x00, 0x9f, 0x03, 0x30, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x3f, 0x0e, 0x70, 0x1f, 0x0c, 0x30, 0x00, 0xdc, 0x07, 
    0x00, 0xf8, 0x07, 0x00, 0xf8, 0x07, 0x00, 0xf0, 0x07, 0x00, 0xc0, 0x07, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

#define ENV_ICON_WIDTH 36
#define ENV_ICON_HEIGHT 36
static const uint8_t env_icon_bits[] = {
    0x00, 0xc0, 0x1f, 0x00, 0xf0, 0x00, 0xe0, 0x3f, 0x00, 0xf0, 0x00, 0xf0, 
    0x7f, 0x00, 0xf0, 0x00, 0x78, 0xf0, 0x00, 0xf0, 0x00, 0x38, 0xe0, 0x01, 
    0xf0, 0x00, 0x1c, 0xc0, 0x01, 0xf0, 0x00, 0x1c, 0xc0, 0x3f, 0xf0, 0x00, 
    0x1c, 0xc0, 0x3f, 0xf0, 0x00, 0x1c, 0xc0, 0x01, 0xf0, 0x00, 0x1c, 0xc0, 
    0x01, 0xf0, 0x00, 0x1c, 0xc0, 0x3f, 0xf0, 0x00, 0x1c, 0xc0, 0x3f, 0xf0, 
    0x00, 0x1c, 0xc7, 0x01, 0xf0, 0x00, 0x1c, 0xc7, 0x01, 0xf0, 0x00, 0x1c, 
    0xc7, 0x3f, 0xf0, 0x00, 0x1c, 0xc7, 0x3f, 0xf0, 0x00, 0x1c, 0xc7, 0x01, 
    0xf0, 0x00, 0x1c, 0xc7, 0x01, 0xf0, 0x00, 0x1c, 0xc7, 0x01, 0xf0, 0x00, 
    0x0e, 0x87, 0x03, 0xf0, 0x00, 0x0f, 0x87, 0x03, 0xf0, 0x00, 0x87, 0x0f, 
    0x07, 0xf0, 0x80, 0xc3, 0x1f, 0x0f, 0xf0, 0x80, 0xe3, 0x3f, 0x0e, 0xf0, 
    0x80, 0xe3, 0x3f, 0x0e, 0xf0, 0x80, 0xe3, 0x3f, 0x0e, 0xf0, 0x80, 0xe3, 
    0x3f, 0x0e, 0xf0, 0x80, 0xe3, 0x3f, 0x0e, 0xf0, 0x80, 0xc3, 0x1f, 0x0f, 
    0xf0, 0x00, 0x87, 0x0f, 0x07, 0xf0, 0x00, 0x0f, 0x80, 0x03, 0xf0, 0x00, 
    0x1e, 0xc0, 0x03, 0xf0, 0x00, 0x7c, 0xf0, 0x01, 0xf0, 0x00, 0xf8, 0xff, 
    0x00, 0xf0, 0x00, 0xf0, 0x7f, 0x00, 0xf0, 0x00, 0xc0, 0x1f, 0x00, 0xf0,
};

#define INFO_ICON_WIDTH 36
#define INFO_ICON_HEIGHT 36
static const uint8_t info_icon_bits[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 
    0x7f, 0x00, 0x00, 0x00, 0xf8, 0xff, 0x01, 0x00, 0x00, 0xfe, 0xff, 0x07, 
    0x00, 0x00, 0xff, 0xff, 0x0f, 0x00, 0xc0, 0xff, 0xff, 0x1f, 0x00, 0xc0, 
    0xff, 0xf9, 0x3f, 0x00, 0xe0, 0xff, 0xf0, 0x7f, 0x00, 0xf0, 0xff, 0xf0, 
    0xff, 0x00, 0xf0, 0xff, 0xf9, 0xff, 0x00, 0xf8, 0xff, 0xff, 0xff, 0x01, 
    0xf8, 0xff, 0xff, 0xff, 0x01, 0xfc, 0xff, 0xff, 0xff, 0x03, 0xfc, 0xff, 
    0xff, 0xff, 0x03, 0xfc, 0xff, 0xff, 0xff, 0x03, 0xfc, 0xff, 0xf9, 0xff, 
    0x03, 0xfc, 0xff, 0xf0, 0xff, 0x03, 0xfc, 0xff, 0xf0, 0xff, 0x03, 0xfc, 
    0xff, 0xf0, 0xff, 0x03, 0xfc, 0xff, 0xf0, 0xff, 0x03, 0xfc, 0xff, 0xf0, 
    0xff, 0x03, 0xfc, 0xff, 0xf0, 0xff, 0x03, 0xf8, 0xff, 0xf0, 0xff, 0x01, 
    0xf8, 0xff, 0xf0, 0xff, 0x01, 0xf0, 0xff, 0xf0, 0xff, 0x00, 0xf0, 0xff, 
    0xf0, 0xff, 0x00, 0xe0, 0xff, 0xf0, 0x7f, 0x00, 0xc0, 0xff, 0xf9, 0x3f, 
    0x00, 0xc0, 0xff, 0xff, 0x1f, 0x00, 0x00, 0xff, 0xff, 0x0f, 0x00, 0x00, 
    0xfe, 0xff, 0x07, 0x00, 0x00, 0xf8, 0xff, 0x01, 0x00, 0x00, 0xe0, 0x7f, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static oled_gui_state_e gui_state = GUI_STATE_ENV_MENU;
    
/*----------------------------------------------------------------------------*
**                             Extern Function                                *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Local Function                                 *
**----------------------------------------------------------------------------*/
/*************************************************
* Function: oled_gui_draw_status_bar
* Description: 画状态栏
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
static void oled_gui_draw_status_bar(void)
{
    char buf[32] = "";
    
    /* 画电池图标 */
    u8g2.drawFrame(8, 8, 24, 13);
    u8g2.drawVLine(33, 12, 5);
    u8g2.setFont(u8g2_font_7x14_tn);
    rt_snprintf(buf, sizeof(buf), "%u", get_battery_level());
    u8g2.drawStr(12, (8 + 12), buf);
    
    /* 画连接状态图标 */
    icon_info_t icon_infos[] = {
        {DISCON_ICON_WIDTH, DISCON_ICON_HEIGHT, discon_icon_bits, ""},
        {USB_ICON_WIDTH, USB_ICON_HEIGHT, usb_icon_bits, ""},
        {BLE_ICON_WIDTH, BLE_ICON_HEIGHT, ble_icon_bits, ""},
    };
    
    /* 当前连接状态 */
    int icon_index = 0;
    if (is_changer_connect())
    {
        icon_index = 1;
    }
    else if (is_ble_connect())
    {
        icon_index = 2;
    }
    
    icon_info_t* icon = &(icon_infos[icon_index]);
    u8g2.drawXBMP(114 - (icon->width / 2), 14 - (icon->height / 2), 
        icon->width, icon->height, icon->bits);
}

/*************************************************
* Function: oled_gui_draw_icon_menu_item
* Description: 画图标菜单项
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
static void oled_gui_draw_icon_menu_item(int menu_index)
{
    /* 画图标 */
    icon_info_t icon_infos[] = {
        {ENV_ICON_WIDTH, ENV_ICON_HEIGHT, env_icon_bits, "环境参数"},
        {INFO_ICON_WIDTH, INFO_ICON_HEIGHT, info_icon_bits, "版本信息"},
    };
    icon_info_t* icon = &(icon_infos[menu_index]);
    u8g2.drawXBMP((128 / 2) - (icon->width / 2), ((128 - 28) / 2) - (icon->height / 2) + 28, 
        icon->width, icon->height, icon->bits);
    
    /* 画提示文本 */
    u8g2.setFont(u8g2_font_simsun_u16_myfont);
    u8g2.drawUTF8(32, 120, icon->tips);
}

/*************************************************
* Function: oled_gui_draw_env_menu_info
* Description: 画环境参数子菜单内容
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
static void oled_gui_draw_env_menu_info()
{
    u8g2.setFont(u8g2_font_simsun_u16_myfont);
    u8g2.drawUTF8(16, ((128 - 28) / 2) - (16 / 2) + 28 - 12, "温度");
    u8g2.drawUTF8(16, ((128 - 28) / 2) - (16 / 2) + 28 + 12, "湿度");
    u8g2.drawUTF8(16, ((128 - 28) / 2) - (16 / 2) + 28 + 36, "气压");
    
    char buf[32] = "";
    
    u8g2.setFont(u8g2_font_crox3h_tf);
    
    float temperature = bme280_get_temp();
    rt_snprintf(buf, sizeof(buf), "%d.%d\xb0\x43", (int)temperature, (int)(temperature * 10) % 10);
    u8g2.drawStr(58, ((128 - 28) / 2) - (16 / 2) + 28 - 12, buf);
    float humidity = bme280_get_humi();
    rt_snprintf(buf, sizeof(buf), "%d.%d%%", (int)humidity, (int)(humidity * 10) % 10);
    u8g2.drawStr(58, ((128 - 28) / 2) - (16 / 2) + 28 + 12, buf);
    float baro = bme280_get_baro();
    rt_snprintf(buf, sizeof(buf), "%d.%dPa", (int)baro, (int)(baro * 10) % 10);
    u8g2.drawStr(58, ((128 - 28) / 2) - (16 / 2) + 28 + 36, buf);
}

/*************************************************
* Function: oled_gui_draw_ver_menu_info
* Description: 画版本信息子菜单内容
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
static void oled_gui_draw_ver_menu_info()
{
    u8g2.setFont(u8g2_font_simsun_u16_myfont);
    u8g2.drawUTF8(16, ((128 - 28) / 2) - (16 / 2) + 28 + 16, "当前版本");
    u8g2.setFont(u8g2_font_crox3h_tf);
    u8g2.drawStr(90, ((128 - 28) / 2) - (16 / 2) + 28 + 16, VERSION);
}

/*************************************************
* Function: oled_gui_draw
* Description: 画GUI界面
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
static void oled_gui_draw(void)
{
    /* 画状态栏 */
    oled_gui_draw_status_bar();
    
    /* 画菜单界面 */
    switch (gui_state)
    {
        case GUI_STATE_ENV_MENU:
            oled_gui_draw_icon_menu_item(0);
            break;
        case GUI_STATE_ENV_INFO:
            oled_gui_draw_env_menu_info();
            break;
        case GUI_STATE_VER_MENU:
            oled_gui_draw_icon_menu_item(1);
            break;
        case GUI_STATE_VER_INFO:
            oled_gui_draw_ver_menu_info();
            break;
    }
}

/*************************************************
* Function: oled_gui_thread_entry
* Description: OLED GUI线程入口函数
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
static void oled_gui_thread_entry(void *parameter)
{
    u8g2.begin(/*Select=*/ U8G2_PIN_SELECT, 
        /*Right/Next=*/ U8G2_PIN_NEXT, /*Left/Prev=*/ U8G2_PIN_PREV, 
        /*Up=*/ U8G2_PIN_UP, /*Down=*/ U8G2_PIN_DOWN, 
        /*Home/Cancel=*/ U8G2_PIN_HOME);
    u8g2.setContrast(128);

    while(1)
    {
        u8g2.clearBuffer();
        oled_gui_draw();
        u8g2.sendBuffer();
        
        rt_thread_mdelay(10);
        
        int8_t event = u8g2.getMenuEvent();
        
        if (event == U8X8_MSG_GPIO_MENU_NEXT)
        {
            switch (gui_state)
            {
                case GUI_STATE_ENV_MENU:
                    gui_state = GUI_STATE_VER_MENU;
                    break;
                case GUI_STATE_ENV_INFO:
                    break;
                case GUI_STATE_VER_MENU:
                    break;
                case GUI_STATE_VER_INFO:
                    break;
            }
        }
        else if (event == U8X8_MSG_GPIO_MENU_PREV)
        {
            switch (gui_state)
            {
                case GUI_STATE_ENV_MENU:
                    break;
                case GUI_STATE_ENV_INFO:
                    break;
                case GUI_STATE_VER_MENU:
                    gui_state = GUI_STATE_ENV_MENU;
                    break;
                case GUI_STATE_VER_INFO:
                    break;
            }
        }
        else if (event == U8X8_MSG_GPIO_MENU_SELECT)
        {
            switch (gui_state)
            {
                case GUI_STATE_ENV_MENU:
                    gui_state = GUI_STATE_ENV_INFO;
                    break;
                case GUI_STATE_ENV_INFO:
                    break;
                case GUI_STATE_VER_MENU:
                    gui_state = GUI_STATE_VER_INFO;
                    break;
                case GUI_STATE_VER_INFO:
                    break;
            }
        }
        else if (event == U8X8_MSG_GPIO_MENU_HOME)
        {
            switch (gui_state)
            {
                case GUI_STATE_ENV_MENU:
                    break;
                case GUI_STATE_ENV_INFO:
                    gui_state = GUI_STATE_ENV_MENU;
                    break;
                case GUI_STATE_VER_MENU:
                    break;
                case GUI_STATE_VER_INFO:
                    gui_state = GUI_STATE_VER_MENU;
                    break;
            }
        }
    }
}
    
/*----------------------------------------------------------------------------*
**                             Public Function                                *
**----------------------------------------------------------------------------*/
/*************************************************
* Function: oled_gui_init
* Description: 初始化OLED GUI模块
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
void oled_gui_init(void)
{
    OLED_GUI_TRACE("oled_gui_init()\n");
    // TODO
}

/*************************************************
* Function: oled_gui_start
* Description: 启动OLED GUI模块
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
void oled_gui_start(void)
{
    OLED_GUI_TRACE("oled_gui_start()\n");

    /* 开启OLED电源 */
    rt_pin_mode(OLED_POWER_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(OLED_POWER_PIN, PIN_HIGH);

    rt_thread_t oled_gui_thread = rt_thread_create("oled_gui",
        oled_gui_thread_entry, RT_NULL,
        OLED_GUI_THREAD_STACK_SIZE,
        OLED_GUI_THREAD_PRIORITY, 
        OLED_GUI_THREAD_TIMESLICE);

    if (oled_gui_thread == RT_NULL)
    {
        OLED_GUI_TRACE("oled_gui_start() failed, call rt_thread_create(oled_gui) error!\n");
    }
    else
    {
        rt_thread_startup(oled_gui_thread);
    }
}

/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif
// End of oled_gui.cpp
