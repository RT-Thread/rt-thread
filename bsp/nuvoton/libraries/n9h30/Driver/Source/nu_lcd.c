/**************************************************************************//**
* @file     lcd.c
* @brief    N9H30 LCD driver source file
*
* @note
* SPDX-License-Identifier: Apache-2.0
* Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "N9H30.h"
#include "nu_sys.h"
#include "nu_lcd.h"

/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_LCD_Driver LCD Driver
  @{
*/

/** @addtogroup N9H30_LCD_EXPORTED_CONSTANTS LCD Exported Constants
  @{
*/

/// @cond HIDDEN_SYMBOLS

/* LCD attributes */
static VPOST_T DEF_E50A2V1 =
{
    800,                            /*!< Panel width */
    480,                            /*!< Panel height */
    0,                              /*!< MPU command line low indicator */
    0,                              /*!< MPU command width */
    0,                              /*!< MPU bus width */
    VPOSTB_DATA16or18,              /*!< Display bus width */
    0,                              /*!< MPU mode */
    VPOSTB_COLORTYPE_64K,           /*!< Display colors */
    VPOSTB_DEVICE_SYNC_HIGHCOLOR,   /*!< Type of display panel */
    0x020d03a0,                     /*!< CRTCSIZE register value */
    0x01e00320,                     /*!< CRTCDEND register value */
    0x03250321,                     /*!< CRTCHR register value */
    0x03780348,                     /*!< CRTCHSYNC register value */
    0x01f001ed                      /*!< CRTCVR register value */
};

static VPOST_T DEF_ILI9341_MPU80 =
{
    240,                            /*!< Panel width */
    320,                            /*!< Panel height */
    VPOSTB_CMDLOW,                  /*!< MPU command line low indicator */
    VPOSTB_CM16t18HIGH,             /*!< MPU command width */
    VPOSTB_CMD8,                    /*!< MPU bus width */
    VPOSTB_DATA16or18,              /*!< Display bus width */
    VPOSTB_MPU80,                   /*!< MPU mode */
    VPOSTB_COLORTYPE_64K,           /*!< Display colors */
    VPOSTB_DEVICE_MPU,              /*!< Type of display panel */
    0x01600100,                     /*!< CRTCSIZE register value */
    0x014000F0,                     /*!< CRTCDEND register value */
    0x00FA00F5,                     /*!< CRTCHR register value */
    0x00FC00FA,                     /*!< CRTCHSYNC register value */
    0x01500145                      /*!< CRTCVR register value */
};

static VPOST_T DEF_LSA40AT9001 =
{
    800,                            /*!< Panel width */
    600,                            /*!< Panel height */
    0,                              /*!< MPU command line low indicator */
    0,                              /*!< MPU command width */
    0,                              /*!< MPU bus width */
    VPOSTB_DATA16or18,              /*!< Display bus width */
    0,                              /*!< MPU mode */
    VPOSTB_COLORTYPE_64K,           /*!< Display colors */
    VPOSTB_DEVICE_SYNC_HIGHCOLOR,   /*!< Type of display panel */
    0x02800425,                     /*!< CRTCSIZE register value */
    0x02580320,                     /*!< CRTCDEND register value */
    0x032F032A,                     /*!< CRTCHR register value */
    0x0334032A,                     /*!< CRTCHSYNC register value */
    0x026C0262                      /*!< CRTCVR register value */
};


static VPOST_T DEF_FW070TFT =
{
    800,                            /*!< Panel width */
    480,                            /*!< Panel height */
    0,                              /*!< MPU command line low indicator */
    0,                              /*!< MPU command width */
    0,                              /*!< MPU bus width */
    VPOSTB_DATA16or18,              /*!< Display bus width */
    0,                              /*!< MPU mode */
    VPOSTB_COLORTYPE_16M,           /*!< Display colors */
    VPOSTB_DEVICE_SYNC_HIGHCOLOR,   /*!< Type of display panel */
    0x020d0420,                     /*!< CRTCSIZE register value */
    0x01e00320,                     /*!< CRTCDEND register value */
    0x033e0339,                     /*!< CRTCHR register value */
    0x040c03f8,                     /*!< CRTCHSYNC register value */
    0x020001f6                      /*!< CRTCVR register value */
};

#define FW043TFT_WIDTH        480   /*!< XRES */
#define FW043TFT_HEIGHT       272   /*!< YRES */
#define FW043TFT_MARGIN_LEFT  30    /*!< HBP (Horizontal Back Porch) */
#define FW043TFT_MARGIN_RIGHT 5     /*!< HFP (Horizontal Front Porch) */
#define FW043TFT_MARGIN_UPPER 2     /*!< VBP (Vertical Back Porch) */
#define FW043TFT_MARGIN_LOWER 27    /*!< VFP (Vertical Front Porch) */
#define FW043TFT_HSYNC_LEN    41    /*!< HPW (HSYNC plus width) */
#define FW043TFT_VSYNC_LEN    10    /*!< VPW (VSYNC width) */
static VPOST_T DEF_FW043TFT =
{
    FW043TFT_WIDTH,                 /*!< Panel width */
    FW043TFT_HEIGHT,                /*!< Panel height */
    0,                              /*!< MPU command line low indicator */
    0,                              /*!< MPU command width */
    0,                              /*!< MPU bus width */
    VPOSTB_DATA16or18,              /*!< Display bus width */
    0,                              /*!< MPU mode */
    VPOSTB_COLORTYPE_16M,           /*!< Display colors */
    VPOSTB_DEVICE_SYNC_HIGHCOLOR,   /*!< Type of display panel */

    .sCRTCSIZE =
    {
        /*!< Horizontal Total */
        .HTT = FW043TFT_MARGIN_LEFT + FW043TFT_WIDTH + FW043TFT_MARGIN_RIGHT,

        /*!< Vertical Total */
        .VTT = FW043TFT_MARGIN_UPPER + FW043TFT_HEIGHT + FW043TFT_MARGIN_LOWER,
    },
    .sCRTCDEND =
    {
        /*!< Horizontal Display Enable End */
        .HDEND = FW043TFT_WIDTH,

        /*!< Vertical Display Enable End */
        .VDEND = FW043TFT_HEIGHT,
    },
    .sCRTCHR =
    {
        /*!< Internal Horizontal Retrace Start Timing */
        .HRS = FW043TFT_WIDTH + 1,

        /*!< Internal Horizontal Retrace End Low */
        .HRE = FW043TFT_WIDTH + 5,
    },
    .sCRTCHSYNC =
    {
        /*!< Horizontal Sync Start Timing */
        .HSYNC_S = FW043TFT_WIDTH + FW043TFT_MARGIN_LEFT,

        /*!< Horizontal Sync End Timing */
        .HSYNC_E = FW043TFT_WIDTH + FW043TFT_MARGIN_LEFT + FW043TFT_HSYNC_LEN,

        /*!< Hsync Signal Adjustment For Multi-Cycles Per Pixel Mode Of Sync-Based Unipac-LCD */
        .HSYNC_SHIFT = 0,
    },
    .sCRTCVR =
    {
        /*!< Vertical Internal Retrace Start Timing */
        .VRS = FW043TFT_HEIGHT + FW043TFT_MARGIN_UPPER,

        /*!< Vertical Internal Retrace End Low */
        .VRE = FW043TFT_HEIGHT + FW043TFT_MARGIN_UPPER + FW043TFT_VSYNC_LEN,
    }
};

#define FW070TFT_WSVGA_WIDTH        1024  /*!< XRES */
#define FW070TFT_WSVGA_HEIGHT       600   /*!< YRES */
#define FW070TFT_WSVGA_MARGIN_LEFT  160   /*!< HBP (Horizontal Back Porch) */
#define FW070TFT_WSVGA_MARGIN_RIGHT 160   /*!< HFP (Horizontal Front Porch) */
#define FW070TFT_WSVGA_MARGIN_UPPER 12    /*!< VBP (Vertical Back Porch) */
#define FW070TFT_WSVGA_MARGIN_LOWER 23    /*!< VFP (Vertical Front Porch) */
#define FW070TFT_WSVGA_HSYNC_LEN    1     /*!< HPW (HSYNC plus width) */
#define FW070TFT_WSVGA_VSYNC_LEN    1     /*!< VPW (VSYNC width) */
static VPOST_T DEF_FW070TFT_WSVGA  =
{
    FW070TFT_WSVGA_WIDTH,                 /*!< Panel width */
    FW070TFT_WSVGA_HEIGHT,                /*!< Panel height */
    0,                              /*!< MPU command line low indicator */
    0,                              /*!< MPU command width */
    0,                              /*!< MPU bus width */
    VPOSTB_DATA16or18,              /*!< Display bus width */
    0,                              /*!< MPU mode */
    VPOSTB_COLORTYPE_16M,           /*!< Display colors */
    VPOSTB_DEVICE_SYNC_HIGHCOLOR,   /*!< Type of display panel */

    .sCRTCSIZE =
    {
        /*!< Horizontal Total */
        .HTT = FW070TFT_WSVGA_MARGIN_LEFT + FW070TFT_WSVGA_WIDTH + FW070TFT_WSVGA_MARGIN_RIGHT,

        /*!< Vertical Total */
        .VTT = FW070TFT_WSVGA_MARGIN_UPPER + FW070TFT_WSVGA_HEIGHT + FW070TFT_WSVGA_MARGIN_LOWER,
    },
    .sCRTCDEND =
    {
        /*!< Horizontal Display Enable End */
        .HDEND = FW070TFT_WSVGA_WIDTH,

        /*!< Vertical Display Enable End */
        .VDEND = FW070TFT_WSVGA_HEIGHT,
    },
    .sCRTCHR =
    {
        /*!< Internal Horizontal Retrace Start Timing */
        .HRS = FW070TFT_WSVGA_WIDTH + 1,

        /*!< Internal Horizontal Retrace End Low */
        .HRE = FW070TFT_WSVGA_WIDTH + 5,
    },
    .sCRTCHSYNC =
    {
        /*!< Horizontal Sync Start Timing */
        .HSYNC_S = FW070TFT_WSVGA_WIDTH + FW070TFT_WSVGA_MARGIN_LEFT,

        /*!< Horizontal Sync End Timing */
        .HSYNC_E = FW070TFT_WSVGA_WIDTH + FW070TFT_WSVGA_MARGIN_LEFT + FW070TFT_WSVGA_HSYNC_LEN,

        /*!< Hsync Signal Adjustment For Multi-Cycles Per Pixel Mode Of Sync-Based Unipac-LCD */
        .HSYNC_SHIFT = 0,
    },
    .sCRTCVR =
    {
        /*!< Vertical Internal Retrace Start Timing */
        .VRS = FW070TFT_WSVGA_HEIGHT + FW070TFT_WSVGA_MARGIN_UPPER,

        /*!< Vertical Internal Retrace End Low */
        .VRE = FW070TFT_WSVGA_HEIGHT + FW070TFT_WSVGA_MARGIN_UPPER + FW070TFT_WSVGA_VSYNC_LEN,
    }
};

/* LCD build-in support list */
static VPOST_T *DisplayDevList[DIS_PANEL_CNT] =
{
    &DEF_E50A2V1,
    &DEF_ILI9341_MPU80,
    &DEF_LSA40AT9001,
    &DEF_FW070TFT,
    &DEF_FW043TFT,
    &DEF_FW070TFT_WSVGA
};

static VPOST_T curDisplayDev;
static OSDFORMATEX curOSDDev = {0};
static LCDFORMATEX curVADev = {0};

/// @endcond /* HIDDEN_SYMBOLS */

/*@}*/ /* end of group N9H30_I2C_EXPORTED_CONSTANTS */

/** @addtogroup N9H30_LCD_EXPORTED_FUNCTIONS LCD Exported Functions
  @{
*/
/// @cond HIDDEN_SYMBOLS

/* For align 32 */
static uint32_t shift_pointer(uint32_t ptr, uint32_t align)
{
    uint32_t alignedPTR;
    uint32_t remain;

    //printf("pointer position is %x\n",ptr);
    if ((ptr % align) != 0)
    {
        remain = ptr % align;
        alignedPTR = ptr + (align - remain);
        return alignedPTR;
    }
    return ptr;
}

/// @endcond /* HIDDEN_SYMBOLS */

/**
  * @brief Configure attributes of LCD panel,install interrupt handler and enable LCD engine clock
  * @param[in] u32DisplayPanelID is panel id to configure.
  * @return none
  */
void vpostLCMInit(uint32_t u32DisplayPanelID)
{
    // enable lcd engine clock
    outpw(REG_CLK_HCLKEN, inpw(REG_CLK_HCLKEN) | (1 << 25));

    memset((void *)&curDisplayDev, 0, sizeof(curDisplayDev));
    memcpy((void *)&curDisplayDev, DisplayDevList[u32DisplayPanelID], sizeof(curDisplayDev));

    outpw(REG_LCM_DEV_CTRL,   curDisplayDev.u32CmdLow
          | curDisplayDev.u32Cmd16t18
          | curDisplayDev.u32CmdBusWidth
          | curDisplayDev.u32DataBusWidth
          | curDisplayDev.u32MPU_Mode
          | curDisplayDev.u32DisplayColors
          | curDisplayDev.u32DevType);

    outpw(REG_LCM_CRTC_SIZE,    curDisplayDev.u32Reg_CRTCSIZE);
    outpw(REG_LCM_CRTC_DEND,    curDisplayDev.u32Reg_CRTCDEND);
    outpw(REG_LCM_CRTC_HR,      curDisplayDev.u32Reg_CRTCHR);
    outpw(REG_LCM_CRTC_HSYNC,   curDisplayDev.u32Reg_CRTCHSYNC);
    outpw(REG_LCM_CRTC_VR,      curDisplayDev.u32Reg_CRTCVR);

}

/**
  * @brief Query LCM capacity and configuration by ID
  * @param[in] u32DisplayPanelID is panel id to configure.
  * @return LCM instance
  */
VPOST_T *vpostLCMGetInstance(uint32_t u32DisplayPanelID)
{
    if (u32DisplayPanelID > (sizeof(DisplayDevList) / sizeof(VPOST_T *)))
        return NULL;

    return DisplayDevList[u32DisplayPanelID];
}

/**
  * @brief Disable LCD engine
  * @param none
  * @return none
  */
void vpostLCMDeinit(void)
{
    // disable lcd engine clock
    outpw(REG_CLK_HCLKEN, inpw(REG_CLK_HCLKEN) & ~(1 << 25));

    //sysDisableInterrupt(LCD_IRQn);
}

/**
  * @brief Get the pointer of frame buffer
  * @param none
  * @return pointer of frame buffer
  * @retval NULL fail.
  * @note before calling this function, display width, height and source format must be set first.
  */
uint8_t *vpostGetFrameBuffer(void)
{
    uint8_t *u8BufPtr;
    uint8_t u32BytePerPixel;

    if ((curDisplayDev.u32DevWidth == 0) || (curDisplayDev.u32DevHeight == 0))
        return NULL;

    switch (curVADev.ucVASrcFormat)
    {
    case VA_SRC_YUV422:
    case VA_SRC_YCBCR422:
    case VA_SRC_RGB565:
        u32BytePerPixel = 2;
        break;

    case VA_SRC_RGB666:
    case VA_SRC_RGB888:
        u32BytePerPixel = 4;
        break;

    default:
        u32BytePerPixel = 2;
    }

    u8BufPtr = (uint8_t *)malloc((curDisplayDev.u32DevWidth * curDisplayDev.u32DevHeight * u32BytePerPixel) + 32);
    if (u8BufPtr == NULL)
        return NULL;
    u8BufPtr = (uint8_t *)shift_pointer((uint32_t)u8BufPtr, 32);

    outpw(REG_LCM_VA_BADDR0, (uint32_t)((uint32_t)u8BufPtr | 0x80000000));
    outpw(REG_LCM_VA_FBCTRL, inpw(REG_LCM_VA_FBCTRL) & ~(1 << 30) & ~VPOSTB_DB_EN);

    return (uint8_t *)((uint32_t)u8BufPtr | 0x80000000);
}

void vpostSetFrameBuffer(uint8_t *pu8BufPtr)
{
    outpw(REG_LCM_VA_BADDR0, (uint32_t)((uint32_t)pu8BufPtr | 0x80000000));
    outpw(REG_LCM_VA_FBCTRL, inpw(REG_LCM_VA_FBCTRL) & ~(1 << 30) & ~VPOSTB_DB_EN);
}


/**
  * @brief Get the pointer of frame buffer
  * @param[in] u32Cnt is the frame buffer count to allocate. Min value is 1.
  * @return pointer of frame buffer
  * @retval NULL fail.
  * @note before calling this function, display width, height and source format must be set first.
  */
uint8_t *vpostGetMultiFrameBuffer(uint32_t u32Cnt)
{
    uint8_t *u8BufPtr;
    uint8_t u32BytePerPixel;

    if ((curDisplayDev.u32DevWidth == 0) || (curDisplayDev.u32DevHeight == 0) || (u32Cnt == 0))
        return NULL;

    switch (curVADev.ucVASrcFormat)
    {
    case VA_SRC_YUV422:
    case VA_SRC_YCBCR422:
    case VA_SRC_RGB565:
        u32BytePerPixel = 2;
        break;

    case VA_SRC_RGB666:
    case VA_SRC_RGB888:
        u32BytePerPixel = 4;
        break;

    default:
        u32BytePerPixel = 2;
    }

    u8BufPtr = (uint8_t *)malloc((curDisplayDev.u32DevWidth * curDisplayDev.u32DevHeight * u32BytePerPixel) * u32Cnt + 32);
    if (u8BufPtr == NULL)
        return NULL;
    u8BufPtr = (uint8_t *)shift_pointer((uint32_t)u8BufPtr, 32);

    outpw(REG_LCM_VA_BADDR0, (uint32_t)((uint32_t)u8BufPtr | 0x80000000));
    outpw(REG_LCM_VA_FBCTRL, inpw(REG_LCM_VA_FBCTRL) & ~(1 << 30) & ~VPOSTB_DB_EN);

    return (uint8_t *)((uint32_t)u8BufPtr | 0x80000000);
}

/**
  * @brief Set active display window
  * @param[in] u16StartY is y start position
  * @param[in] u16EndY is y end position
  * @param[in] u8BGColorR is background R color
  * @param[in] u8BGColorG is background G color
  * @param[in] u8BGColorB is background B color
  * @return none
  */
void vpostSetActiveWindow(uint16_t u16StartY, uint16_t u16EndY, uint8_t u8BGColorR, uint8_t u8BGColorG, uint8_t u8BGColorB)
{
    outpw(REG_LCM_VA_WIN, (u16StartY << 16) | u16EndY);
    outpw(REG_LCM_VA_STUFF, (u8BGColorR << 16) | (u8BGColorG << 8) | u8BGColorB);
}

/**
  * @brief Configure LCD display mode
  * @param[in] u8DisplayMode is display mode, value could be
  *                                         - \ref VPOST_DISPLAY_SINGLE
  *                                         - \ref VPOST_DISPLAY_CONTINUOUS
  * @return none
  */
void vpostSetDisplayMode(uint8_t u8DisplayMode)
{
    if (u8DisplayMode == 0)
        outpw(REG_LCM_DCCS, inpw(REG_LCM_DCCS) & ~(1 << 7)); //clear setting
    else
        outpw(REG_LCM_DCCS, inpw(REG_LCM_DCCS) | (u8DisplayMode) << 7);
}

/**
  * @brief Configure display attributes of video interface,
  * @param[in] u32VASrcType is display type, value could be
  *                                         - \ref VA_SRC_YUV422
  *                                         - \ref VA_SRC_YCBCR422
  *                                         - \ref VA_SRC_RGB888
  *                                         - \ref VA_SRC_RGB666
  *                                         - \ref VA_SRC_RGB565
  *                                         - \ref VA_SRC_RGB444_LOW
  *                                         - \ref VA_SRC_RGB444_HIGH
  * @return none
  */
void vpostSetVASrc(uint32_t u32VASrcType)
{
    uint32_t u32BytePerPixel, VA_FF, VA_Sride;

    curVADev.ucVASrcFormat = u32VASrcType;

    outpw(REG_LCM_DCCS, inpw(REG_LCM_DCCS) & ~(7 << 8));
    if (u32VASrcType != 0)
        outpw(REG_LCM_DCCS, inpw(REG_LCM_DCCS) | u32VASrcType);
    else
        outpw(REG_LCM_DCCS, inpw(REG_LCM_DCCS) & ~(7 << 8));

    if ((u32VASrcType == VA_SRC_RGB888) || (u32VASrcType == VA_SRC_RGB666))
        outpw(REG_LCM_VA_FBCTRL, inpw(REG_LCM_VA_FBCTRL) & ~0x7ff07ff | (curDisplayDev.u32DevWidth << 16) | curDisplayDev.u32DevWidth);
    else
        outpw(REG_LCM_VA_FBCTRL, inpw(REG_LCM_VA_FBCTRL) & ~0x7ff07ff | ((curDisplayDev.u32DevWidth / 2) << 16) | (curDisplayDev.u32DevWidth / 2));

    switch (u32VASrcType)
    {
    case VA_SRC_YUV422:
    case VA_SRC_YCBCR422:
    case VA_SRC_RGB565:
        u32BytePerPixel = 2;
        break;

    case VA_SRC_RGB666:
    case VA_SRC_RGB888:
        u32BytePerPixel = 4;
        break;

    default:
        u32BytePerPixel = 2;
    }

    /* set video stream frame buffer control */
    VA_FF = curDisplayDev.u32DevWidth * u32BytePerPixel / 4;
    VA_Sride = curDisplayDev.u32DevWidth * u32BytePerPixel / 4;
    outpw(REG_LCM_VA_FBCTRL, inpw(REG_LCM_VA_FBCTRL) & ~0x7ff07ff | (VA_FF << 16) | VA_Sride);
}

/**
  * @brief Start to display
  * @param none
  * @return none
  */
void vpostVAStartTrigger(void)
{
    if ((inpw(REG_LCM_DCCS) & VPOSTB_SINGLE) == VPOSTB_SINGLE)
        while ((inpw(REG_LCM_DCCS) & VPOSTB_VA_EN) == VPOSTB_VA_EN); //wait VA_EN low
    outpw(REG_LCM_DCCS, inpw(REG_LCM_DCCS) | VPOSTB_DISP_OUT_EN); //display_out-enable
    outpw(REG_LCM_DCCS, inpw(REG_LCM_DCCS) | VPOSTB_VA_EN); //va-enable
}

/**
  * @brief Stop to display
  * @param none
  * @return none
  */
void vpostVAStopTrigger(void)
{
    outpw(REG_LCM_DCCS, inpw(REG_LCM_DCCS) & ~(VPOSTB_DISP_OUT_EN | VPOSTB_VA_EN)); //OSD disable
}

/**
  * @brief Configure LCD scaling attribute
  * @param[in] u8HIntegral is horizontal integral
  * @param[in] u16HDecimal is horizontal decimal
  * @param[in] u8VIntegral is vertical integral
  * @param[in] u16VDecimal is vertical decimal
  * @param[in] u32Mode is scale mode, value could be
  *                                      - \ref VA_SCALE_INTERPOLATION
  *                                      - \ref VA_SCALE_DUPLICATION
  * @return none
  */
void vpostVAScalingCtrl(uint8_t u8HIntegral, uint16_t u16HDecimal, uint8_t u8VIntegral, uint16_t u16VDecimal, uint32_t u32Mode)
{
    outpw(REG_LCM_VA_SCALE, ((((uint32_t)u8VIntegral << 10) + ((uint32_t)ceil((double)1024 / 10)*u16VDecimal)) << 16)
          | (((uint32_t)u8HIntegral << 10) + ((uint32_t)ceil((double)1024 / 10)*u16HDecimal)) | u32Mode);
}

/**
  * @brief Set OSD color key
  * @param[in] u8CKeyColorR is color key R color
  * @param[in] u8CKeyColorG is color key G color
  * @param[in] u8CKeyColorB is color key B color
  * @return none
  */
void vpostOSDSetColKey(uint8_t u8CKeyColorR, uint8_t u8CKeyColorG, uint8_t u8CKeyColorB)
{
    outpw(REG_LCM_OSD_OVERLAY, inpw(REG_LCM_OSD_OVERLAY) & ~(VPOSTB_BLI_ON | VPOSTB_CKEY_ON)); //blinking disable, color-key disable
    outpw(REG_LCM_OSD_OVERLAY, inpw(REG_LCM_OSD_OVERLAY) | VPOSTB_CKEY_ON);//color-key enable
    outpw(REG_LCM_OSD_CKEY, ((uint32_t)(u8CKeyColorR << 16) | (uint32_t)(u8CKeyColorG << 8) | u8CKeyColorB));
}

/**
  * @brief Set OSD color mask, OSD data only will be displayed if the mask bit is set as 1.
  * @param[in] u8MaskColorR is color key R color
  * @param[in] u8MaskColorG is color key G color
  * @param[in] u8MaskColorB is color key B color
  * @return none
  */
void vpostOSDSetColMask(uint8_t u8MaskColorR, uint8_t u8MaskColorG, uint8_t u8MaskColorB)
{
    outpw(REG_LCM_OSD_CMASK, ((u8MaskColorR << 16) | (u8MaskColorG << 8) | u8MaskColorB));
}

/**
  * @brief Set OSD blinking function
  * @param[in] u8OSDBlinkVcnt is blinking cycle time, unit is VSync
  * @return none
  */
void vpostOSDSetBlinking(uint8_t u8OSDBlinkVcnt)
{
    outpw(REG_LCM_OSD_OVERLAY, inpw(REG_LCM_OSD_OVERLAY) & ~(VPOSTB_BLI_ON | VPOSTB_CKEY_ON));  //blinking disable, color-key disable
    outpw(REG_LCM_OSD_OVERLAY, inpw(REG_LCM_OSD_OVERLAY) | VPOSTB_BLI_ON);
    outpw(REG_LCM_OSD_OVERLAY, inpw(REG_LCM_OSD_OVERLAY) | ((uint32_t)(u8OSDBlinkVcnt) << 16));
}

/**
  * @brief Disable OSD blinking function
  * @param none
  * @return none
  */
void vpostOSDDisableBlinking(void)
{
    outpw(REG_LCM_OSD_OVERLAY, inpw(REG_LCM_OSD_OVERLAY) & ~ VPOSTB_BLI_ON);
}

/**
  * @brief Configure display attributes of OSD
  * @param[in] u32OSDSrcType is display type, value could be
  *                                         - \ref OSD_SRC_YUV422
  *                                         - \ref OSD_SRC_YCBCR422
  *                                         - \ref OSD_SRC_RGB888
  *                                         - \ref OSD_SRC_RGB666
  *                                         - \ref OSD_SRC_RGB565
  *                                         - \ref OSD_SRC_RGB444_LOW
  *                                         - \ref OSD_SRC_RGB444_HIGH
  *                                         - \ref OSD_SRC_RGB332
  * @return none
  */
void vpostSetOSDSrc(uint32_t u32OSDSrcType)
{
    uint32_t u32BytePerPixel, VA_FF, VA_Sride;

    outpw(REG_LCM_DCCS, inpw(REG_LCM_DCCS) & ~(7 << 12) | u32OSDSrcType);
    curOSDDev.ucOSDSrcFormat = u32OSDSrcType;

    switch (u32OSDSrcType)
    {
    case OSD_SRC_YUV422:
    case OSD_SRC_YCBCR422:
    case OSD_SRC_RGB565:
        u32BytePerPixel = 2;
        break;

    case OSD_SRC_RGB666:
    case OSD_SRC_RGB888:
        u32BytePerPixel = 4;
        break;

    default:
        u32BytePerPixel = 2;
    }

    /* set video stream frame buffer control */
    VA_FF = curOSDDev.nOSDWidth * u32BytePerPixel / 4;
    VA_Sride = curOSDDev.nOSDWidth * u32BytePerPixel / 4;
    outpw(REG_LCM_OSD_FBCTRL, inpw(REG_LCM_OSD_FBCTRL) & ~0x7ff07ff | (VA_FF << 16) | VA_Sride);
}

/**
  * @brief Get the pointer of OSD frame buffer
  * @param none
  * @return pointer of OSD frame buffer
  * @retval NULL fail.
  * @note Must call \ref vpostOSDSetWindow and \ref vpostSetOSDSrc before calling this function
  */
uint8_t *vpostGetOSDBuffer(void)
{
    uint32_t u32BytePerPixel;
    uint8_t *u8BufPtr;

    if ((curOSDDev.nOSDWidth == 0) || (curOSDDev.nOSDHeight == 0))
    {
        return NULL;
    }

    switch (curOSDDev.ucOSDSrcFormat)
    {
    case OSD_SRC_YUV422:
    case OSD_SRC_YCBCR422:
    case OSD_SRC_RGB565:
        u32BytePerPixel = 2;
        break;

    case OSD_SRC_RGB666:
    case OSD_SRC_RGB888:
        u32BytePerPixel = 4;
        break;

    default:
        u32BytePerPixel = 2;
    }

    u8BufPtr = (uint8_t *)malloc((curOSDDev.nOSDWidth * curOSDDev.nOSDHeight * u32BytePerPixel) + 32);
    if (u8BufPtr == NULL)
        return NULL;
    u8BufPtr = (uint8_t *)shift_pointer((uint32_t)u8BufPtr, 32);

    outpw(REG_LCM_OSD_BADDR, (uint32_t)((uint32_t)u8BufPtr | 0x80000000));

    return (uint8_t *)((uint32_t)u8BufPtr | 0x80000000);
}

/**
  * @brief Get the pointer of OSD buffer
  * @param[in] u32Cnt is the frame buffer count to allocate. Min value is 1.
  * @return pointer of frame buffer
  * @retval NULL fail.
  * @note before calling this function, display width, height and source format must be set first.
  */
uint8_t *vpostGetMultiOSDBuffer(uint32_t u32Cnt)
{
    uint32_t u32BytePerPixel;
    uint8_t *u8BufPtr;

    if ((curOSDDev.nOSDWidth == 0) || (curOSDDev.nOSDHeight == 0))
    {
        return NULL;
    }

    switch (curOSDDev.ucOSDSrcFormat)
    {
    case OSD_SRC_YUV422:
    case OSD_SRC_YCBCR422:
    case OSD_SRC_RGB565:
        u32BytePerPixel = 2;
        break;

    case OSD_SRC_RGB666:
    case OSD_SRC_RGB888:
        u32BytePerPixel = 4;
        break;

    default:
        u32BytePerPixel = 2;
    }

    u8BufPtr = (uint8_t *)malloc((curOSDDev.nOSDWidth * curOSDDev.nOSDHeight * u32BytePerPixel) * u32Cnt + 32);
    if (u8BufPtr == NULL)
        return NULL;
    u8BufPtr = (uint8_t *)shift_pointer((uint32_t)u8BufPtr, 32);

    outpw(REG_LCM_OSD_BADDR, (uint32_t)((uint32_t)u8BufPtr | 0x80000000));

    return (uint8_t *)((uint32_t)u8BufPtr | 0x80000000);

}

void vpostSetOSDBuffer(uint8_t *u8BufPtr)
{
    outpw(REG_LCM_OSD_BADDR, (uint32_t)((uint32_t)u8BufPtr | 0x80000000));
}

/**
  * @brief Enable OSD function
  * @param none
  * @return none
  */
void vpostOSDEnable(void)
{
    outpw(REG_LCM_DCCS, inpw(REG_LCM_DCCS) | VPOSTB_OSD_EN); //OSD enable
}

/**
  * @brief Disable OSD function
  * @param none
  * @return none
  */
void vpostOSDDisable(void)
{
    outpw(REG_LCM_DCCS, inpw(REG_LCM_DCCS) & ~VPOSTB_OSD_EN); //OSD disable
}

/**
  * @brief Configure OSD scaling attribute
  * @param[in] u8HIntegral is horizontal integral
  * @param[in] u16HDecimal is horizontal decimal
  * @param[in] u8VScall is scale mode, value could be
  *                                      - \ref VPOSTB_OSD_VUP_1X
  *                                      - \ref VPOSTB_OSD_VUP_2X
  *                                      - \ref VPOSTB_OSD_VUP_4X
  * @return none
  */
void vpostOSDScalingCtrl(uint8_t u8HIntegral, uint16_t u16HDecimal, uint8_t u8VScall)
{
    outpw(REG_LCM_DCCS, inpw(REG_LCM_DCCS) & 0xfff0ffff); //clear OSD scaling setting
    if (u8VScall != 0)
        outpw(REG_LCM_DCCS, inpw(REG_LCM_DCCS) | (u8VScall << 16));
    outpw(REG_LCM_OSD_SCALE, ((uint32_t)u8HIntegral << 10) | ((uint32_t)ceil((double)1024 / 10 * u16HDecimal)) << 6);
}

/**
  * @brief Set OSD display window, including start position, width and height.
  * @param[in] u32XStart is X start position
  * @param[in] u32YStart is Y start position
  * @param[in] u32Width is OSD display width
  * @param[in] u32Height is OSD display height
  * @return none
  */
void vpostOSDSetWindow(uint32_t u32XStart, uint32_t u32YStart, uint32_t u32Width, uint32_t u32Height)
{
    outpw(REG_LCM_OSD_WINS, ((u32YStart + 1) << 16) | (u32XStart + 1));
    outpw(REG_LCM_OSD_WINE, ((u32YStart + u32Height) << 16) | (u32XStart + u32Width));

    curOSDDev.nOSDWidth = u32Width;
    curOSDDev.nOSDHeight = u32Height;
}

/**
  * @brief Initialize hardware cursor function
  * @param[in] u32CursorBMPBuff is pointer of hardware cursor image
  * @param[in] ucMode is hardware cursor mode, value could be
  *                                              - \ref HC_MODE0
  *                                              - \ref HC_MODE1
  *                                              - \ref HC_MODE2
  *                                              - \ref HC_MODE3
  *                                              - \ref HC_MODE4
  *                                              - \ref HC_MODE5
  * @return none
  */
void vpostHCInit(uint32_t *u32CursorBMPBuff, VA_HCMODE_E ucMode)
{
    int bpp = 2;
    int BlockWidth = 32;
    int bpw = 32;

    outpw(REG_LCM_HC_CTRL, inpw(REG_LCM_HC_CTRL) & ~0x003f3f00 | (0x00 << 8) | (0x00 << 16)); //set TIP
    if (ucMode == HC_MODE0)
    {
        bpp = 2;
        BlockWidth = 32;
        outpw(REG_LCM_HC_CTRL, inpw(REG_LCM_HC_CTRL) & ~0x7); //set mode 0 32X32X2bpp 4 color

    }
    else if (ucMode == HC_MODE1)
    {
        bpp = 2;
        BlockWidth = 32;
        outpw(REG_LCM_HC_CTRL, inpw(REG_LCM_HC_CTRL) & ~0x7 | 0x1); //set mode 1 32X32X2bpp 3 color and 1 transparent
    }
    else if (ucMode == HC_MODE2)
    {
        bpp = 2;
        BlockWidth = 64;
        outpw(REG_LCM_HC_CTRL, inpw(REG_LCM_HC_CTRL) & ~0x7 | 0x2); //set mode 2 64X64X2bpp 4 color
    }
    else if (ucMode == HC_MODE3)
    {
        bpp = 2;
        BlockWidth = 64;
        outpw(REG_LCM_HC_CTRL, inpw(REG_LCM_HC_CTRL) & ~0x7 | 0x3); //set mode 3 64X64X2bpp 3 color and 1 transparent
    }
    else if (ucMode == HC_MODE4)
    {
        bpp = 1;
        BlockWidth = 128;
        outpw(REG_LCM_HC_CTRL, inpw(REG_LCM_HC_CTRL) & ~0x7 | 0x4); //set mode 4 128X128X1bpp 2 color
    }
    else if (ucMode == HC_MODE5)
    {
        bpp = 1;
        BlockWidth = 128;
        outpw(REG_LCM_HC_CTRL, inpw(REG_LCM_HC_CTRL) & ~0x7 | 0x5); //set mode 5 128X128X1bpp 1 color and 1 transparent
    }

    outpw(REG_LCM_HC_WBCTRL, ((bpp * BlockWidth / bpw) << 16) | (bpp * BlockWidth / bpw));
    outpw(REG_LCM_HC_BADDR, (uint32_t)u32CursorBMPBuff);
    outpw(REG_LCM_HC_COLOR0, 0x00ff0000);       // RED color
    outpw(REG_LCM_HC_COLOR1, 0x0000ff00);       // GREEN color
    outpw(REG_LCM_HC_COLOR2, 0x000000ff);       // BLUE color
    outpw(REG_LCM_HC_COLOR3, 0x00ffff00);       // YELLOW color
    outpw(REG_LCM_DCCS, inpw(REG_LCM_DCCS) | VPOSTB_HC_EN);
}

/**
  * @brief Set the position of hardware cursor
  * @param[in] u32CursorX is X position
  * @param[in] u32CursorY is Y position
  * @return none
  */
void vpostHCPosCtrl(uint32_t u32CursorX, uint32_t u32CursorY)
{
    outpw(REG_LCM_HC_POS, (u32CursorY << 16) | u32CursorX); //set Cursor position
}

/**
  * @brief Set OSD overlay condition
  * @param[in] u8OSDDisplayMatch is display method when mask bit is matched, value could be
  *                                                         - \ref DISPLAY_VIDEO
  *                                                         - \ref DISPLAY_OSD
  *                                                         - \ref DISPLAY_SYNTHESIZED
  * @param[in] u8OSDDisplayUnMatch is display method when mask bit is unmatched
  *                                                         - \ref DISPLAY_VIDEO
  *                                                         - \ref DISPLAY_OSD
  *                                                         - \ref DISPLAY_SYNTHESIZED
  * @param[in] u8OSDSynW is synthesis video weighting, based on match condition
  * @return none
  */
void vpostOSDSetOverlay(uint8_t u8OSDDisplayMatch, uint8_t u8OSDDisplayUnMatch, uint8_t u8OSDSynW)
{
    /* clear OCR0 and OCR1 */
    outpw(REG_LCM_OSD_OVERLAY, inpw(REG_LCM_OSD_OVERLAY) & 0xfffffff0);

    /* match condition */
    if (u8OSDDisplayMatch != 0)
    {
        outpw(REG_LCM_OSD_OVERLAY, inpw(REG_LCM_OSD_OVERLAY) | (u8OSDDisplayMatch << 2));
    }

    /* unmatch condition */
    if (u8OSDDisplayUnMatch != 0)
    {
        outpw(REG_LCM_OSD_OVERLAY, inpw(REG_LCM_OSD_OVERLAY) | (u8OSDDisplayUnMatch));
    }

    /* synthesized weight */
    if (u8OSDDisplayMatch == DISPLAY_SYNTHESIZED || u8OSDDisplayUnMatch == DISPLAY_SYNTHESIZED)
    {
        outpw(REG_LCM_OSD_OVERLAY, inpw(REG_LCM_OSD_OVERLAY) | (u8OSDSynW << 4));
    }
}

/**
  * @brief Write MPU command
  * @param[in] uscmd MPU command code
  * @return none
  */
void vpostMPUWriteAddr(uint16_t uscmd)
{
    outpw(REG_LCM_MPU_CMD, inpw(REG_LCM_MPU_CMD) & ~(1 << 30));     //RS=0
    outpw(REG_LCM_MPU_CMD, inpw(REG_LCM_MPU_CMD) & ~(1 << 29));     //w

    outpw(REG_LCM_DCCS, (inpw(REG_LCM_DCCS) | (1 << 5)));           //CMD ON
    outpw(REG_LCM_MPU_CMD, (inpw(REG_LCM_MPU_CMD) & 0xffff0000 | uscmd));
    while (inpw(REG_LCM_MPU_CMD) & (1UL << 31));
    outpw(REG_LCM_DCCS, (inpw(REG_LCM_DCCS) & ~(1 << 5)));          //CMD OFF
}

/**
  * @brief Write MPU data
  * @param[in] usdata MPU data
  * @return none
  */
void vpostMPUWriteData(uint16_t usdata)
{
    outpw(REG_LCM_MPU_CMD, inpw(REG_LCM_MPU_CMD) | (1 << 30));      //RS=1
    outpw(REG_LCM_MPU_CMD, inpw(REG_LCM_MPU_CMD) & ~(1 << 29));     //w
    outpw(REG_LCM_DCCS, (inpw(REG_LCM_DCCS) | (1 << 5)));           //CMD ON
    outpw(REG_LCM_MPU_CMD, inpw(REG_LCM_MPU_CMD) & 0xffff0000 | usdata);
    while (inpw(REG_LCM_MPU_CMD) & (1UL << 31));
    outpw(REG_LCM_DCCS, (inpw(REG_LCM_DCCS) & ~(1 << 5)));          //CMD OFF
}

/**
  * @brief Read MPU data
  * @param none
  * @return MPU data
  */
uint32_t vpostMPUReadData(void)
{
    uint32_t udata;

    outpw(REG_LCM_MPU_CMD, inpw(REG_LCM_MPU_CMD) | (1 << 30));      //RS=1
    outpw(REG_LCM_DCCS, (inpw(REG_LCM_DCCS) | (1 << 5)));           //CMD ON
    outpw(REG_LCM_MPU_CMD, inpw(REG_LCM_MPU_CMD) | (1 << 29));      //r
    while (inpw(REG_LCM_MPU_CMD) & (1UL << 31));
    udata = inpw(REG_LCM_MPU_CMD) & 0xffff;
    outpw(REG_LCM_DCCS, (inpw(REG_LCM_DCCS) & ~(1 << 5)));          //CMD OFF

    return udata;
}

/*@}*/ /* end of group N9H30_LCD_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_LCD_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/

