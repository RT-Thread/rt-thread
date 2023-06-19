/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-18     Meco Man     The first version
 * 2022-05-17     Ting Liu     Support touchpad
 */

#define LOG_TAG             "LVGL.port.indev"
#include <drv_log.h>

#include "lvgl.h"

#include "board.h"
#include "touchpad.h"
#include "fsl_video_common.h"
#include "fsl_lpi2c.h"
#include "fsl_gpio.h"
#ifdef DEMO_PANEL_RK043FN66HS
#include "fsl_gt911.h"
#else
#include "fsl_ft5406_rt.h"
#endif

#if LV_USE_GPU_NXP_PXP
#include "src/gpu/lv_gpu_nxp_pxp.h"
#include "src/gpu/lv_gpu_nxp_pxp_osa.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* @Brief Board touch panel configuration */
#define BOARD_TOUCH_I2C_BASEADDR LPI2C1
#define BOARD_TOUCH_RST_GPIO     GPIO1
#define BOARD_TOUCH_RST_PIN      2
#define BOARD_TOUCH_INT_GPIO     GPIO1
#define BOARD_TOUCH_INT_PIN      11

/* Macros for the touch touch controller. */
#define TOUCH_I2C LPI2C1

/* Select USB1 PLL (480 MHz) as master lpi2c clock source */
#define TOUCH_LPI2C_CLOCK_SOURCE_SELECT (0U)
/* Clock divider for master lpi2c clock source */
#define TOUCH_LPI2C_CLOCK_SOURCE_DIVIDER (5U)

#define TOUCH_I2C_CLOCK_FREQ ((CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8) / (TOUCH_LPI2C_CLOCK_SOURCE_DIVIDER + 1U))
#define TOUCH_I2C_BAUDRATE   100000U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void DEMO_InitTouch(void);

static void DEMO_ReadTouch(lv_indev_drv_t *drv, lv_indev_data_t *data);
#ifdef DEMO_PANEL_RK043FN66HS
static void BOARD_PullTouchResetPin(bool pullUp);

static void BOARD_ConfigTouchIntPin(gt911_int_pin_mode_t mode);
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
#ifdef DEMO_PANEL_RK043FN66HS
static gt911_handle_t s_touchHandle;
static const gt911_config_t s_touchConfig = {
    .I2C_SendFunc     = BOARD_Touch_I2C_Send,
    .I2C_ReceiveFunc  = BOARD_Touch_I2C_Receive,
    .pullResetPinFunc = BOARD_PullTouchResetPin,
    .intPinFunc       = BOARD_ConfigTouchIntPin,
    .timeDelayMsFunc  = VIDEO_DelayMs,
    .touchPointNum    = 1,
    .i2cAddrMode      = kGT911_I2cAddrMode0,
    .intTrigMode      = kGT911_IntRisingEdge,
};
static int s_touchResolutionX;
static int s_touchResolutionY;
#else
static ft5406_rt_handle_t touchHandle;
#endif

void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;

    /*------------------
     * Touchpad
     * -----------------*/

    /*Initialize your touchpad */
    DEMO_InitTouch();

    /*Register a touchpad input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type    = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = DEMO_ReadTouch;
    lv_indev_drv_register(&indev_drv);
}

#ifdef DEMO_PANEL_RK043FN66HS
static void BOARD_PullTouchResetPin(bool pullUp)
{
    if (pullUp)
    {
        GPIO_PinWrite(BOARD_TOUCH_RST_GPIO, BOARD_TOUCH_RST_PIN, 1);
    }
    else
    {
        GPIO_PinWrite(BOARD_TOUCH_RST_GPIO, BOARD_TOUCH_RST_PIN, 0);
    }
}

static void BOARD_ConfigTouchIntPin(gt911_int_pin_mode_t mode)
{
    if (mode == kGT911_IntPinInput)
    {
        BOARD_TOUCH_INT_GPIO->GDIR &= ~(1UL << BOARD_TOUCH_INT_PIN);
    }
    else
    {
        if (mode == kGT911_IntPinPullDown)
        {
            GPIO_PinWrite(BOARD_TOUCH_INT_GPIO, BOARD_TOUCH_INT_PIN, 0);
        }
        else
        {
            GPIO_PinWrite(BOARD_TOUCH_INT_GPIO, BOARD_TOUCH_INT_PIN, 1);
        }

        BOARD_TOUCH_INT_GPIO->GDIR |= (1UL << BOARD_TOUCH_INT_PIN);
    }
}

/*Initialize your touchpad*/
static void DEMO_InitTouch(void)
{
    status_t status;

    const gpio_pin_config_t resetPinConfig = {
        .direction = kGPIO_DigitalOutput, .outputLogic = 0, .interruptMode = kGPIO_NoIntmode};
    GPIO_PinInit(BOARD_TOUCH_INT_GPIO, BOARD_TOUCH_INT_PIN, &resetPinConfig);
    GPIO_PinInit(BOARD_TOUCH_RST_GPIO, BOARD_TOUCH_RST_PIN, &resetPinConfig);

    /*Clock setting for LPI2C*/
    CLOCK_SetMux(kCLOCK_Lpi2cMux, TOUCH_LPI2C_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, TOUCH_LPI2C_CLOCK_SOURCE_DIVIDER);

    BOARD_LPI2C_Init(TOUCH_I2C, TOUCH_I2C_CLOCK_FREQ);

    status = GT911_Init(&s_touchHandle, &s_touchConfig);

    if (kStatus_Success != status)
    {
        //PRINTF("Touch IC initialization failed\r\n");
        assert(false);
    }

    GT911_GetResolution(&s_touchHandle, &s_touchResolutionX, &s_touchResolutionY);
}

/* Will be called by the library to read the touchpad */
static void DEMO_ReadTouch(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    static int touch_x = 0;
    static int touch_y = 0;

    if (kStatus_Success == GT911_GetSingleTouch(&s_touchHandle, &touch_x, &touch_y))
    {
        data->state = LV_INDEV_STATE_PR;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }

    /*Set the last pressed coordinates*/
    data->point.x = touch_x * LCD_WIDTH / s_touchResolutionX;
    data->point.y = touch_y * LCD_HEIGHT / s_touchResolutionY;
}
#else
/*Initialize your touchpad*/
static void DEMO_InitTouch(void)
{
    status_t status;

    lpi2c_master_config_t masterConfig = {0};

    /*Clock setting for LPI2C*/
    CLOCK_SetMux(kCLOCK_Lpi2cMux, TOUCH_LPI2C_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, TOUCH_LPI2C_CLOCK_SOURCE_DIVIDER);

    /*
     * masterConfig.debugEnable = false;
     * masterConfig.ignoreAck = false;
     * masterConfig.pinConfig = kLPI2C_2PinOpenDrain;
     * masterConfig.baudRate_Hz = 100000U;
     * masterConfig.busIdleTimeout_ns = 0;
     * masterConfig.pinLowTimeout_ns = 0;
     * masterConfig.sdaGlitchFilterWidth_ns = 0;
     * masterConfig.sclGlitchFilterWidth_ns = 0;
     */
    LPI2C_MasterGetDefaultConfig(&masterConfig);

    /* Change the default baudrate configuration */
    masterConfig.baudRate_Hz = TOUCH_I2C_BAUDRATE;

    /* Initialize the LPI2C master peripheral */
    LPI2C_MasterInit(TOUCH_I2C, &masterConfig, TOUCH_I2C_CLOCK_FREQ);

    /* Initialize touch panel controller */
    status = FT5406_RT_Init(&touchHandle, TOUCH_I2C);
    if (status != kStatus_Success)
    {
        //PRINTF("Touch panel init failed\n");
        assert(0);
    }
}

/* Will be called by the library to read the touchpad */
static void DEMO_ReadTouch(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    touch_event_t touch_event;
    static int touch_x = 0;
    static int touch_y = 0;

    data->state = LV_INDEV_STATE_REL;

    if (kStatus_Success == FT5406_RT_GetSingleTouch(&touchHandle, &touch_event, &touch_x, &touch_y))
    {
        if ((touch_event == kTouch_Down) || (touch_event == kTouch_Contact))
        {
            data->state = LV_INDEV_STATE_PR;
        }
    }

    /*Set the last pressed coordinates*/
    data->point.x = touch_y;
    data->point.y = touch_x;
}
#endif
