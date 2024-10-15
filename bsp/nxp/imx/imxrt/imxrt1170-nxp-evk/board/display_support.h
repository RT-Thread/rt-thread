/*
 * Copyright 2019-2021, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _DISPLAY_SUPPORT_H_
#define _DISPLAY_SUPPORT_H_

#include <rtthread.h>

#include "fsl_dc_fb.h"

#if defined(DISPLAY_USING_RK055AHD091)
#include "fsl_rm68200.h"
#elif defined(DISPLAY_USING_RK055IQH091)
#include "fsl_rm68191.h"
#elif defined(DISPLAY_USING_RK055MHD091)
#include "fsl_hx8394.h"
#else
#error "Please config lcd panel parameters."
#endif
#include "pin_mux.h"
#include "board.h"

#if defined(BSP_USING_LCDIFV2)
#include "fsl_dc_fb_lcdifv2.h"
#elif defined(BSP_USING_ELCDIF)
#include "fsl_dc_fb_elcdif.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* @TEST_ANCHOR */
#define DEMO_BUFFER_FIXED_ADDRESS 0

#if DEMO_BUFFER_FIXED_ADDRESS
#define DEMO_BUFFER0_ADDR 0x80000000
#define DEMO_BUFFER1_ADDR 0x80200000
#endif

/*
 * Use the MIPI dumb panel
 */

/* Definitions for the frame buffer. */
#define DEMO_BUFFER_COUNT 2 /* 2 is enough for DPI interface display. */

#ifndef DEMO_USE_XRGB8888
#define DEMO_USE_XRGB8888 0
#endif

/* Use LCDIF LUT (or named color palette) which is 8-bit per-pixel */
#ifndef DEMO_USE_LUT8
#define DEMO_USE_LUT8 0
#endif

#if DEMO_USE_XRGB8888
#define DEMO_BUFFER_PIXEL_FORMAT   kVIDEO_PixelFormatXRGB8888
#define DEMO_BUFFER_BYTE_PER_PIXEL 4
#elif DEMO_USE_LUT8
#define DEMO_BUFFER_PIXEL_FORMAT   kVIDEO_PixelFormatLUT8
#define DEMO_BUFFER_BYTE_PER_PIXEL 1
#else
#define DEMO_BUFFER_PIXEL_FORMAT   kVIDEO_PixelFormatRGB565
#define DEMO_BUFFER_BYTE_PER_PIXEL 2
#endif

#if (defined(DISPLAY_USING_RK055AHD091) || defined(DISPLAY_USING_RK055MHD091))

#define LCD_MIPI_WIDTH  (720)
#define LCD_MIPI_HEIGHT (1280)

#elif defined(DISPLAY_USING_RK055IQH091)

#define LCD_MIPI_WIDTH  (540)
#define LCD_MIPI_HEIGHT (960)

#endif

#define DEMO_BUFFER_WIDTH  LCD_MIPI_WIDTH
#define DEMO_BUFFER_HEIGHT LCD_MIPI_HEIGHT

/* Where the frame buffer is shown in the screen. */
#define DEMO_BUFFER_START_X 0U
#define DEMO_BUFFER_START_Y 0U

#define DEMO_BUFFER_STRIDE_BYTE (DEMO_BUFFER_WIDTH * DEMO_BUFFER_BYTE_PER_PIXEL)
/* There is not frame buffer aligned requirement, consider the 64-bit AXI data
 * bus width and 32-byte cache line size, the frame buffer alignment is set to
 * 32 byte.
 */
#define FRAME_BUFFER_ALIGN 32

/*
 * MIPI panel pin
 */
#define BOARD_MIPI_PANEL_RST_GPIO   GPIO9
#define BOARD_MIPI_PANEL_RST_PIN    1
#define BOARD_MIPI_PANEL_POWER_GPIO GPIO11
#define BOARD_MIPI_PANEL_POWER_PIN  16
/* Back light pin. */
#define BOARD_MIPI_PANEL_BL_GPIO    GPIO9
#define BOARD_MIPI_PANEL_BL_PIN     29

/*
 * MIPI panel pin for RT-Thread
 */
#define GET_PIN(PORTx, PIN)  (32 * (PORTx - 1) + (PIN & 31))    /* PORTx:1,2,3,4,5 */
#define LCD_MIPI_RST_GPIO_PORT    (3U)
#define LCD_MIPI_RST_GPIO_PIN     (1U)
#define LCD_MIPI_RST_PIN          GET_PIN(LCD_MIPI_RST_GPIO_PORT, LCD_MIPI_RST_GPIO_PIN)
/* Back light pin. */
#define LCD_MIPI_BL_GPIO_PORT     (3U)
#define LCD_MIPI_BL_GPIO_PIN      (29U)
#define LCD_MIPI_BL_PIN           GET_PIN(LCD_MIPI_BL_GPIO_PORT, LCD_MIPI_BL_GPIO_PIN)

/*
 * RK055AHD091 panel
 */

#if defined(DISPLAY_USING_RK055AHD091)
#define LCD_MIPI_HSW 8
#define LCD_MIPI_HFP 32
#define LCD_MIPI_HBP 32
#define LCD_MIPI_VSW 2
#define LCD_MIPI_VFP 16
#define LCD_MIPI_VBP 14

#elif defined(DISPLAY_USING_RK055IQH091)

#define LCD_MIPI_HSW 2
#define LCD_MIPI_HFP 32
#define LCD_MIPI_HBP 30
#define LCD_MIPI_VSW 2
#define LCD_MIPI_VFP 16
#define LCD_MIPI_VBP 14

#elif defined(DISPLAY_USING_RK055MHD091)

#define LCD_MIPI_HSW 6
#define LCD_MIPI_HFP 12
#define LCD_MIPI_HBP 24
#define LCD_MIPI_VSW 2
#define LCD_MIPI_VFP 16
#define LCD_MIPI_VBP 14

#endif

#if defined(BSP_USING_LCDIFV2)

#define DEMO_LCDIF_POL_FLAGS                                                             \
    (kLCDIFV2_DataEnableActiveHigh | kLCDIFV2_VsyncActiveLow | kLCDIFV2_HsyncActiveLow | \
     kLCDIFV2_DriveDataOnFallingClkEdge)

#define DEMO_LCDIF LCDIFV2

#elif defined(BSP_USING_ELCDIF)

#define DEMO_LCDIF_POL_FLAGS \
    (kELCDIF_DataEnableActiveHigh | kELCDIF_VsyncActiveLow | kELCDIF_HsyncActiveLow | kELCDIF_DriveDataOnFallingClkEdge)

#define DEMO_LCDIF LCDIF

#endif

/* Definitions for MIPI. */
#define DEMO_LCD_MIPI          (&g_mipiDsi)
#define DEMO_LCD_MIPI_LANE_NUM 2

extern const dc_fb_t g_dc;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

status_t BOARD_PrepareDisplayController(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _DISPLAY_SUPPORT_H_ */
