/**************************************************************************//**
 * @file     nu_disp.h
 * @brief    DISP driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_DISP_H__
#define __NU_DISP_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup DISP_Driver DISP Driver
  @{
*/

/** @addtogroup DISP_EXPORTED_CONSTANTS DISP Exported Constants
  @{
*/

typedef enum
{
    eDispLcd_1024x600   = 0,
    eDispLcd_800x480    = 1,
    eDispLcd_1920x1080  = 2,
    eDispLcd_Cnt
} E_DISP_LCD;


typedef enum
{
    ePolarity_Disable  = -1,
    ePolarity_Positive = 0,
    ePolarity_Negative = 1
} E_POLARITY;

typedef enum
{
    eDPIFmt_D16CFG1,
    eDPIFmt_D16CFG2,
    eDPIFmt_D16CFG3,
    eDPIFmt_D18CFG1,
    eDPIFmt_D18CFG2,
    eDPIFmt_D24
} E_DPI_DATA_FMT;

typedef enum
{
    eLayer_Video   = 0,
    eLayer_Overlay = 1,
    eLayer_Cnt
} E_DISP_LAYER;

typedef enum
{
    eYUV_709_BT709   = 1,
    eYUV_2020_BT2020 = 3,
} E_YUV_STANDARD;

typedef enum
{
    eFBFmt_X4R4G4B4      = 0,
    eFBFmt_A4R4G4B4      = 1,
    eFBFmt_X1R5G5B5      = 2,
    eFBFmt_A1R5G5B5      = 3,
    eFBFmt_R5G6B5        = 4,
    eFBFmt_X8R8G8B8      = 5,
    eFBFmt_A8R8G8B8      = 6,
    eFBFmt_YUY2          = 7,
    eFBFmt_UYVY          = 8,
    eFBFmt_INDEX8        = 9,
    eFBFmt_MONOCHROME    = 10,
    eFBFmt_YV12          = 15,
    eFBFmt_A8            = 16,
    eFBFmt_NV12          = 17,
    eFBFmt_NV16          = 18,
    eFBFmt_RG16          = 19,
    eFBFmt_R8            = 20,
    eFBFmt_NV12_10BIT    = 21,
    eFBFmt_A2R10G10B10   = 22,
    eFBFmt_NV16_10BIT    = 23,
    eFBFmt_INDEX1        = 24,
    eFBFmt_INDEX2        = 25,
    eFBFmt_INDEX4        = 26,
    eFBFmt_P010          = 27,
    eFBFmt_NV12_10BIT_L1 = 28,
    eFBFmt_NV16_10BIT_L1 = 29
} E_FB_FMT;

typedef enum
{
    eOPAQUE,
    eMASK,
    eKEY
} E_TRANSPARENCY_MODE;

typedef enum
{
    DC_BLEND_MODE_CLEAR,
    DC_BLEND_MODE_SRC,
    DC_BLEND_MODE_DST,
    DC_BLEND_MODE_SRC_OVER,
    DC_BLEND_MODE_DST_OVER,
    DC_BLEND_MODE_SRC_IN,
    DC_BLEND_MODE_DST_IN,
    DC_BLEND_MODE_SRC_OUT
} E_DC_BLEND_MODE;

typedef enum
{
    eGloAM_NORMAL,
    eGloAM_GLOBAL,
    eGloAM_SCALED
} E_GLOBAL_ALPHA_MODE;


typedef enum
{
    eBM_ZERO,
    eBM_ONE,
    eBM_NORMAL,
    eBM_INVERSED,
    eBM_COLOR,
    eBM_COLOR_INVERSED,
    eBM_SATURATED_ALPHA,
    eBM_SATURATED_DEST_ALPHA
} E_BLENDING_MODE;

typedef struct
{
    /*
    htotal: u32HA + u32HBP + u32HFP + u32HSL
    vtotal: u32VA + u32VBP + u32VFP + u32VSL
    clock-frequency: htotal * vtotal * fps
    */
    uint32_t u32PCF;     // Pixel Clock Frequency

    uint32_t u32HA;      // Horizontal Active
    uint32_t u32HSL;     // Horizontal Sync Length
    uint32_t u32HFP;     // Horizontal Front Porch
    uint32_t u32HBP;     // Horizontal Back Porch
    uint32_t u32VA;      // Vertical Active
    uint32_t u32VSL;     // Vertical Sync Len
    uint32_t u32VFP;     // Vertical Front Porch
    uint32_t u32VBP;     // Vertical Back Porch

    E_POLARITY eHSPP;    // HSync Pulse Polarity
    E_POLARITY eVSPP;    // VSync Pulse Polarity

} DISP_LCD_TIMING;

typedef struct
{
    E_DPI_DATA_FMT eDpiFmt; // DPI Data Format
    E_POLARITY     eDEP;    // DE Polarity
    E_POLARITY     eDP;     // DATA Polarity
    E_POLARITY     eCP;     // CLOCK Polarity
} DISP_PANEL_CONF;

typedef struct
{
    uint32_t u32ResolutionWidth;
    uint32_t u32ResolutionHeight;
    DISP_LCD_TIMING sLcdTiming;
    DISP_PANEL_CONF sPanelConf;
} DISP_LCD_INFO;

#define DISP_ENABLE_INT()     (DISP->DisplayIntrEnable |=  DISP_DisplayIntrEnable_DISP0_Msk)
#define DISP_DISABLE_INT()    (DISP->DisplayIntrEnable &= ~DISP_DisplayIntrEnable_DISP0_Msk)
#define DISP_GET_INTSTS()     (DISP->DisplayIntr & DISP_DisplayIntr_DISP0_Msk)

const DISP_LCD_INFO *DISP_GetLCDInst(E_DISP_LCD eDispLcd);
int32_t DISP_LCDInit(const DISP_LCD_INFO *psLCDInfo);
int32_t DISP_LCDDeinit(void);
int DISP_SetFBConfig(E_DISP_LAYER eLayer, E_FB_FMT eFbFmt, uint32_t u32ResWidth, uint32_t u32ResHeight, uint32_t u32DMAFBStartAddr);
void DISP_SetPanelConf(DISP_PANEL_CONF *psPanelConf);
void DISP_SetTiming(DISP_LCD_TIMING *psLCDTiming);
int DISP_Trigger(E_DISP_LAYER eLayer, uint32_t u32Action);
int DISP_SetTransparencyMode(E_DISP_LAYER eLayer, E_TRANSPARENCY_MODE eTM);
int DISP_SetBlendOpMode(E_DC_BLEND_MODE eDCBM, E_GLOBAL_ALPHA_MODE eGloAM_Src, E_GLOBAL_ALPHA_MODE eGloAM_Dst);
void DISP_SetBlendValue(uint32_t u32GloAV_Src, uint32_t u32GloAV_Dst);
void DISP_SetColorKeyValue(uint32_t u32ColorKeyLow, uint32_t u32ColorKeyHigh);
int DISP_SetFBAddr(E_DISP_LAYER eLayer, uint32_t u32DMAFBStartAddr);
int DISP_SetFBFmt(E_DISP_LAYER eLayer, E_FB_FMT eFbFmt, uint32_t u32Pitch);
uint32_t DISP_LCDTIMING_GetFPS(const DISP_LCD_TIMING* psDispLCDTiming);

/*@}*/ /* end of group DISP_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group DISP_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_DISP_H__ */

