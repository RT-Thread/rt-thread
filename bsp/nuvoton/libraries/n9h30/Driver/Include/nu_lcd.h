/**************************************************************************//**
* @file     lcd.h
* @version  V1.00
* @brief    N9H30 LCD driver header file
*
* SPDX-License-Identifier: Apache-2.0
* @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __NU_LCD_H__
#define __NU_LCD_H__

#ifdef __cplusplus
extern "C"
{
#endif

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

/* bit definition of REG_LCM_DCCS register */
#define VPOSTB_HC_EN        ((UINT32)1<<31)
#define VPOSTB_DISP_ON              (1<<25)
#define VPOSTB_ITUEN                (1<<15)
#define VPOSTB_OSD_SRC_YUV422       (0<<12)
#define VPOSTB_OSD_SRC_YCBCR422     (1<<12)
#define VPOSTB_OSD_SRC_RGB888       (2<<12)
#define VPOSTB_OSD_SRC_RGB666       (3<<12)
#define VPOSTB_OSD_SRC_RGB565       (4<<12)
#define VPOSTB_OSD_SRC_RGB444_LOW   (5<<12)
#define VPOSTB_OSD_SRC_RGB444_HIGH  (7<<12)
#define VPOSTB_VA_SRC_YUV422        (0<<8 )
#define VPOSTB_VA_SRC_YCBCR422      (1<<8 )
#define VPOSTB_VA_SRC_RGB888        (2<<8 )
#define VPOSTB_VA_SRC_RGB666        (3<<8 )
#define VPOSTB_VA_SRC_RGB565        (4<<8 )
#define VPOSTB_VA_SRC_RGB444_LOW    (5<<8 )
#define VPOSTB_VA_SRC_RGB444_HIGH   (7<<8 )
#define VPOSTB_SINGLE               (1<<7 )
#define VPOSTB_FIELD_INTR           (1<<6 )
#define VPOSTB_CMD_ON               (1<<5 )
#define VPOSTB_DISP_INT_EN          (1<<4 )
#define VPOSTB_DISP_OUT_EN          (1<<3 )
#define VPOSTB_OSD_EN               (1<<2 )
#define VPOSTB_VA_EN                (1<<1 )
#define VPOSTB_ENG_RST              (1)


/* bit definition of REG_LCM_DEV_CTRL register */
#define VPOSTB_CMDHIGH  (0)
#define VPOSTB_CMDLOW   ((UINT32)1<<31)
#define VPOSTB_CM16t18LOW   (0)
#define VPOSTB_CM16t18HIGH  ((UINT32)1<<30)
#define VPOSTB_CMD8    (0)
#define VPOSTB_CMD16    ((UINT32)1<<29)
#define VPOSTB_IM256K_9or18 (0)
#define VPOSTB_IM256K_8or16 ((UINT32)1<<28)
#define VPOSTB_MPU80    (0)
#define VPOSTB_MPU68    (1<<27)
#define VPOSTB_DATA8or9   (0)
#define VPOSTB_DATA16or18   (1<<26)
#define VPOSTB_COLORTYPE_4K         (0)
#define VPOSTB_COLORTYPE_64K        (1<<24)
#define VPOSTB_COLORTYPE_256K       (2<<24)
#define VPOSTB_COLORTYPE_16M        (3<<24)
#define VPOSTB_LACE     (1<<23)
#define VPOSTB_VR_LACE  (1<<22)
#define VPOSTB_V_POL    (1<<21)
#define VPOSTB_H_POL    (1<<20)
#define VPOSTB_FAL_D    (1<<19)
#define VPOSTB_YUV2CCIR (1<<16)
#define VPOSTB_DEVICE_SYNC_YUV422       (0)
#define VPOSTB_DEVICE_SYNC_UNIPAC       (4<<5)
#define VPOSTB_DEVICE_SYNC_EPSON        (5<<5)
#define VPOSTB_DEVICE_SYNC_HIGHCOLOR    (6<<5)
#define VPOSTB_DEVICE_MPU               (7<<5)
#define VPOSTB_SWAP_YUYV    (1<<1)

/* bit definition of REG_LCM_INT_CS register */
#define VPOSTB_DISP_F_INT           ((UINT32)1<<31)
#define VPOSTB_DISP_F_STATUS        (1<<30)
#define VPOSTB_UNDERRUN_INT         (1<<29)
#define VPOSTB_BUS_ERROR_INT        (1<<28)
#define VPOSTB_FLY_ERR              (1<<27)
#define VPOSTB_UNDERRUN_EN          (1<<1)
#define VPOSTB_DISP_F_EN            (1)

/* bit definition of REG_LCM_VA_FBCTRL register */
#define VPOSTB_DB_EN    ((UINT32)1<<31)
#define VPOSTB_FLY_EN   (1<<12)

/* bit definition of REG_LCM_OSD_OVERLAY register */
#define VPOSTB_BLI_ON   (1<<9)
#define VPOSTB_CKEY_ON  (1<<8)

#define DISPLAY_VIDEO           (0)
#define DISPLAY_OSD             (1)
#define DISPLAY_SYNTHESIZED     (2)

/// @endcond HIDDEN_SYMBOLS

#define VA_SRC_YUV422       (0<<8 )     /*!< YUV422 format */
#define VA_SRC_YCBCR422     (1<<8 )     /*!< YCBCR422 format */
#define VA_SRC_RGB888       (2<<8 )     /*!< RGB888 format */
#define VA_SRC_RGB666       (3<<8 )     /*!< RGB666 format */
#define VA_SRC_RGB565       (4<<8 )     /*!< RGB565 format */
#define VA_SRC_RGB444_LOW   (5<<8 )     /*!< RGB444 low nibble format */
#define VA_SRC_RGB444_HIGH  (7<<8 )     /*!< RGB444 high nibble format */

#define OSD_SRC_YUV422      (0<<12)     /*!< YUV422 format */
#define OSD_SRC_YCBCR422    (1<<12)     /*!< YCBCR422 format */
#define OSD_SRC_RGB888      (2<<12)     /*!< RGB888 format */
#define OSD_SRC_RGB666      (3<<12)     /*!< RGB666 format */
#define OSD_SRC_RGB565      (4<<12)     /*!< RGB565 format */
#define OSD_SRC_RGB444_LOW  (5<<12)     /*!< RGB444 low nibble format */
#define OSD_SRC_RGB444_HIGH (7<<12)     /*!< RGB444 high nibble format */
#define OSD_SRC_RGB332      (6<<12)     /*!< RGB332 format */

#define VPOST_DISPLAY_SINGLE        1   /*!< Single display mode */
#define VPOST_DISPLAY_CONTINUOUS    0   /*!< Continuous display mode */

#define VPOSTB_OSD_VUP_1X           (0<<16)     /*!< OSD vertical scale up 1x */
#define VPOSTB_OSD_VUP_2X           (1<<16)     /*!< OSD vertical scale up 2x */
#define VPOSTB_OSD_VUP_4X           (2<<16)     /*!< OSD vertical scale up 4x */

#define DISPLAY_VIDEO           (0)     /*!< Display video data */
#define DISPLAY_OSD             (1)     /*!< Display OSD data */
#define DISPLAY_SYNTHESIZED     (2)     /*!< Display synthesized data */

#define VA_SCALE_INTERPOLATION  (0)     /*!< Scale mode is interpolation */
#define VA_SCALE_DUPLICATION    (1<<15) /*!< Scale mode is duplication */

#pragma anon_unions

typedef enum va_hcmode_e
{
    HC_MODE0,           /*!< 32X32X2bpp 4 color */
    HC_MODE1,           /*!< 32X32X2bpp 3 color and 1 transparent */
    HC_MODE2,           /*!< 64X64X2bpp 4 color */
    HC_MODE3,           /*!< 64X64X2bpp 3 color and 1 transparent */
    HC_MODE4,           /*!< 128X128X1bpp 2 color */
    HC_MODE5            /*!< 128X128X1bpp 1 color and 1 transparent */
} VA_HCMODE_E;

typedef struct
{
    uint32_t ucVASrcFormat;         /*!< User input Display source format */
    uint32_t nScreenWidth;          /*!< Driver output,LCD width */
    uint32_t nScreenHeight;         /*!< Driver output,LCD height */
    uint32_t nFrameBufferSize;      /*!< Driver output,Frame buffer size(malloc by driver) */
    uint8_t ucROT90;                /*!< Rotate 90 degree or not */
} LCDFORMATEX;

typedef struct
{
    uint32_t ucOSDSrcFormat;         /*!< User input, OSD source format */
    uint32_t nXstart;                /*!< User input, OSD X axis position */
    uint32_t nYstart;                /*!< User input, OSD Y axis position */
    uint32_t nOSDWidth;              /*!< User input, OSD width */
    uint32_t nOSDHeight;             /*!< User input, OSD height */
    uint32_t nImageWidth;            /*!< User input, The width of OSD source image width */
    uint32_t *pFrameBuffer;          /*!< User input, The address of OSD source image */
} OSDFORMATEX;

enum DIS_PANEL
{
    DIS_PANEL_E50A2V1 = 0,
    DIS_PANEL_ILI9341_MPU80,
    DIS_LSA40AT9001,
    DIS_PANEL_FW070TFT,
    DIS_PANEL_FW043TFT,
    DIS_PANEL_FW070TFT_WSVGA,
    DIS_PANEL_CNT
};

typedef struct
{
    uint32_t u32DevWidth;           /*!< Panel width */
    uint32_t u32DevHeight;          /*!< Panel height */
    uint32_t u32CmdLow;             /*!< MPU command line low indicator */
    uint32_t u32Cmd16t18;           /*!< MPU command width */
    uint32_t u32CmdBusWidth;        /*!< MPU bus width */
    uint32_t u32DataBusWidth;       /*!< Display bus width */
    uint32_t u32MPU_Mode;           /*!< MPU mode */
    uint32_t u32DisplayColors;      /*!< Display colors */
    uint32_t u32DevType;            /*!< Type of display panel */
    union
    {
        uint32_t u32Reg_CRTCSIZE;   /*!< CRTCSIZE register value */
        struct
        {
            uint32_t HTT: 11;       /*!< Horizontal Total Pixels */
            uint32_t : 5;
            uint32_t VTT: 11;       /*!< Vertical Total Scan Lines */
            uint32_t : 5;
        } sCRTCSIZE;
    };
    union
    {
        uint32_t u32Reg_CRTCDEND;   /*!< CRTCDEND register value */
        struct
        {
            uint32_t HDEND: 11;     /*!< Horizontal Display Enable End */
            uint32_t : 5;
            uint32_t VDEND: 11;     /*!< Vertical Display Enable End */
            uint32_t : 5;
        } sCRTCDEND;
    };
    union
    {
        uint32_t u32Reg_CRTCHR;     /*!< CRTCHR register value */
        struct
        {
            uint32_t HRS: 11;       /*!< Internal Horizontal Retrace Start Timing */
            uint32_t : 5;
            uint32_t HRE: 11;       /*!< Internal Horizontal Retrace End Low */
            uint32_t : 5;
        } sCRTCHR;
    };
    union
    {
        uint32_t u32Reg_CRTCHSYNC;  /*!< CRTCHSYNC register value */
        struct
        {
            uint32_t HSYNC_S: 11;   /*!< Horizontal Sync Start Timing */
            uint32_t : 5;
            uint32_t HSYNC_E: 11;   /*!< Horizontal Sync End Timing */
            uint32_t : 3;
            uint32_t HSYNC_SHIFT: 2; /*!< Hsync Signal Adjustment For Multi-Cycles Per Pixel Mode Of Sync-Based Unipac-LCD */
        } sCRTCHSYNC;
    };
    union
    {
        uint32_t u32Reg_CRTCVR;     /*!< CRTCVR register value */
        struct
        {
            uint32_t VRS: 11;       /*!< Vertical Internal Retrace Start Timing */
            uint32_t : 5;
            uint32_t VRE: 11;       /*!< Vertical Internal Retrace End Low */
            uint32_t : 5;
        } sCRTCVR;
    };
} VPOST_T;

#define LCM_ERR_ID      0xFFFF0400  /*!< LCM library ID */

/* error code */
#define ERR_NULL_BUF            (LCM_ERR_ID | 0x04)  /*!< error memory location */
#define ERR_NO_DEVICE           (LCM_ERR_ID | 0x05)  /*!< error no device */
#define ERR_BAD_PARAMETER       (LCM_ERR_ID | 0x06)  /*!< error for bad parameter */
#define ERR_POWER_STATE         (LCM_ERR_ID | 0x07)  /*!< error power state control */
/*@}*/ /* end of group N9H30_LCD_EXPORTED_CONSTANTS */

/** @addtogroup N9H30_LCD_EXPORTED_FUNCTIONS LCD Exported Functions
  @{
*/

void vpostLCMInit(uint32_t u32DisplayPanelID);
uint8_t *vpostGetFrameBuffer(void);
uint8_t *vpostGetMultiFrameBuffer(uint32_t u32Cnt);
void vpostLCMDeinit(void);
void vpostSetDisplayMode(uint8_t u8DisplayMode);
void vpostSetVASrc(uint32_t u32VASrcType);
void vpostVAStartTrigger(void);
void vpostVAStopTrigger(void);
void vpostVAScalingCtrl(uint8_t u8HIntegral, uint16_t u16HDecimal, uint8_t u8VIntegral, uint16_t u16VDecimal, uint32_t u32Mode);

void vpostOSDSetColKey(uint8_t u8CKeyColorR, uint8_t u8CKeyColorG, uint8_t u8CKeyColorB);
void vpostOSDSetColMask(uint8_t u8MaskColorR, uint8_t u8MaskColorG, uint8_t u8MaskColorB);
void vpostOSDSetBlinking(uint8_t u8OSDBlinkVcnt);
void vpostOSDDisableBlinking(void);
void vpostSetOSDSrc(uint32_t u32OSDSrcType);
uint8_t *vpostGetOSDBuffer(void);
void vpostOSDEnable(void);
void vpostOSDDisable(void);
void vpostOSDScalingCtrl(uint8_t u8HIntegral, uint16_t u16HDecimal, uint8_t u8VScall);
void vpostOSDSetWindow(uint32_t u32XStart, uint32_t u32YStart, uint32_t u32Width, uint32_t u32Height);
void vpostHCInit(uint32_t *u32CursorBMPBuff, VA_HCMODE_E ucMode);
void vpostHCPosCtrl(uint32_t u32CursorX, uint32_t u32CursorY);
void vpostOSDSetOverlay(uint8_t u8OSDDisplayMatch, uint8_t u8OSDDisplayUnMatch, uint8_t u8OSDSynW);
void vpostMPUWriteAddr(uint16_t uscmd);
void vpostMPUWriteData(uint16_t usdata);
uint32_t vpostMPUReadData(void);
VPOST_T *vpostLCMGetInstance(uint32_t u32DisplayPanelID);
void vpostSetFrameBuffer(uint8_t *pu8BufPtr);
void vpostSetOSDBuffer(uint8_t *pu8BufPtr);
uint8_t *vpostGetMultiOSDBuffer(uint32_t u32Cnt);

/*@}*/ /* end of group N9H30_LCD_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_LCD_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__NU_LCD_H__


