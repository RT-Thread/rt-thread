/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_OV7725_H
#define HPM_OV7725_H
#include "hpm_common.h"
#include "hpm_camera_config.h"

/**
 * @brief OV7725 sensor driver APIs
 * @defgroup ov7725_interface sensor driver APIs
 * @ingroup component_interfaces
 * @{
 *

 */
/***********************************************************************************************************************
 *
 * Definitions
 *
 **********************************************************************************************************************/

/**
 * @brief OV7725 definition
 */
#define OV7725_ACTIVE_IMAGE_WIDTH  (480U)
#define OV7725_ACTIVE_IMAGE_HEIGHT (480U)
#define OV7725_I2C_ADDR (0x21U)
#define OV7725_CHIP_ID_HIGH_BYTE_ADDR             (0x0A)
#define OV7725_CHIP_ID_HIGH_BYTE_VALUE            (0x77)
#define OV7725_CHIP_ID_LOW_BYTE_ADDR              (0x0B)
#define OV7725_CHIP_ID_LOW_BYTE_VALUE             (0x21) /* need to check */

#define OV7725_RST_ACTIVE    0
#define OV7725_RST_INACTIVE  1
#define OV7725_PWDN_ACTIVE   1
#define OV7725_PWDN_INACTIVE 0
/**
 * @brief OV7725 registers
 */
#define GAIN                    (0x00U) /* AGC – Gain control gain setting */
#define BLUE                    (0x01U) /* AWB – Blue channel gain setting */
#define RED                     (0x02U) /* AWB – Red channel gain setting */
#define GREEN                   (0x03U) /* AWB – Green channel gain setting */

#define BAVG                    (0x05U) /* U/B Average Level */
#define GAVG                    (0x06U) /* Y/Gb Average Level */
#define RAVG                    (0x07U) /* V/R Average Level */
#define AECH                    (0x08U) /* Exposure Value – AEC MSBs */

#define COM2                    (0x09U) /* Common Control 2 */
#define COM2_SOFT_SLEEP         (0x10U) /* Soft sleep mode */
#define COM2_OUT_DRIVE_1x       (0x00U) /* Output drive capability 1x */
#define COM2_OUT_DRIVE_2x       (0x01U) /* Output drive capability 2x */
#define COM2_OUT_DRIVE_3x       (0x02U) /* Output drive capability 3x */
#define COM2_OUT_DRIVE_4x       (0x03U) /* Output drive capability 4x */

#define PID                 (0x0AU) /* Product ID Number MSB */
#define VER                 (0x0BU) /* Product ID Number LSB */

#define COM3                    (0x0CU) /* Common Control 3 */
#define COM3_VFLIP              (0x80U) /* Vertical flip image ON/OFF selection */
#define COM3_MIRROR             (0x40U) /* Horizontal mirror image ON/OFF selection */
#define COM3_SWAP_BR            (0x20U) /* Swap B/R output sequence in RGB output mode */
#define COM3_SWAP_YUV           (0x10U) /* Swap Y/UV output sequence in YUV output mode */
#define COM3_SWAP_MSB           (0x08U) /* Swap output MSB/LSB */
#define COM3_TRI_CLOCK          (0x04U) /* Tri-state option for output clock at power-down period */
#define COM3_TRI_DATA           (0x02U) /* Tri-state option for output data at power-down period */
#define COM3_COLOR_BAR          (0x01U) /* Sensor color bar test pattern output enable */

#define COM4                    (0x0DU) /* Common Control 4 */
#define COM4_PLL_BYPASS         (0x00U) /* Bypass PLL */
#define COM4_PLL_4x             (0x40U) /* PLL frequency 4x */
#define COM4_PLL_6x             (0x80U) /* PLL frequency 6x */
#define COM4_PLL_8x             (0xc0U) /* PLL frequency 8x */
#define COM4_AEC_FULL           (0x00U) /* AEC evaluate full window */
#define COM4_AEC_1_2            (0x10U) /* AEC evaluate 1/2 window */
#define COM4_AEC_1_4            (0x20U) /* AEC evaluate 1/4 window */
#define COM4_AEC_2_3            (0x30U) /* AEC evaluate 2/3 window */

#define COM5                    (0x0EU) /* Common Control 5 */
#define COM5_AFR                (0x80U) /* Auto frame rate control ON/OFF selection (night mode) */
#define COM5_AFR_SPEED          (0x40U) /* Auto frame rate control speed selection */
#define COM5_AFR_0              (0x00U) /* No reduction of frame rate */
#define COM5_AFR_1_2            (0x10U) /* Max reduction to 1/2 frame rate */
#define COM5_AFR_1_4            (0x20U) /* Max reduction to 1/4 frame rate */
#define COM5_AFR_1_8            (0x30U) /* Max reduction to 1/8 frame rate */
#define COM5_AFR_4x             (0x04U) /* Add frame when AGC reaches 4x gain */
#define COM5_AFR_8x             (0x08U) /* Add frame when AGC reaches 8x gain */
#define COM5_AFR_16x            (0x0cU) /* Add frame when AGC reaches 16x gain */
#define COM5_AEC_NO_LIMIT       (0x01U) /* No limit to AEC increase step */

#define COM6                    (0x0FU) /* Common Control 6 */
#define COM6_AUTO_WINDOW        (0x01U) /* Auto window setting ON/OFF selection when format changes */

#define AEC                     (0x10U) /* AEC[7:0] (see register AECH for AEC[15:8]) */
#define CLKRC                   (0x11U) /* Internal Clock */

#define COM7                    (0x12U) /* Common Control 7 */
#define COM7_RESET              (0x80U) /* SCCB Register Reset */
#define COM7_RES_VGA            (0x00U) /* Resolution VGA */
#define COM7_RES_QVGA           (0x40U) /* Resolution QVGA */
#define COM7_BT656              (0x20U) /* BT.656 protocol ON/OFF */
#define COM7_SENSOR_RAW         (0x10U) /* Sensor RAW */
#define COM7_FMT_GBR422         (0x02U) /* RGB output format GBR422 */
#define COM7_FMT_RGB565         (0x06U) /* RGB output format RGB565 */
#define COM7_FMT_RGB555         (0x0AU) /* RGB output format RGB555 */
#define COM7_FMT_RGB444         (0x0EU) /* RGB output format RGB444 */
#define COM7_FMT_YUV            (0x00U) /* Output format YUV */
#define COM7_FMT_P_BAYER        (0x01U) /* Output format Processed Bayer RAW */
#define COM7_FMT_R_BAYER        (0x03U) /* Output format Bayer RAW */

#define COM8                    (0x13U) /* Common Control 8 */
#define COM8_FAST_AUTO          (0x80U) /* Enable fast AGC/AEC algorithm */
#define COM8_STEP_VSYNC         (0x00U) /* AEC - Step size limited to vertical blank */
#define COM8_STEP_UNLIMIT       (0x40U) /* AEC - Step size unlimited step size */
#define COM8_BANDF_EN           (0x20U) /* Banding filter ON/OFF */
#define COM8_AEC_BANDF          (0x10U) /* Enable AEC below banding value */
#define COM8_AEC_FINE_EN        (0x08U) /* Fine AEC ON/OFF control */
#define COM8_AGC_EN             (0x04U) /* AGC Enable */
#define COM8_AWB_EN             (0x02U) /* AWB Enable */
#define COM8_AEC_EN             (0x01U) /* AEC Enable */

#define COM9                    (0x14U) /* Common Control 9 */
#define COM9_HISTO_AVG          (0x80U) /* Histogram or average based AEC/AGC selection */
#define COM9_AGC_GAIN_2x        (0x00U) /* Automatic Gain Ceiling 2x */
#define COM9_AGC_GAIN_4x        (0x10U) /* Automatic Gain Ceiling 4x */
#define COM9_AGC_GAIN_8x        (0x20U) /* Automatic Gain Ceiling 8x */
#define COM9_AGC_GAIN_16x       (0x30U) /* Automatic Gain Ceiling 16x */
#define COM9_AGC_GAIN_32x       (0x40U) /* Automatic Gain Ceiling 32x */
#define COM9_DROP_VSYNC         (0x04U) /* Drop VSYNC output of corrupt frame */
#define COM9_DROP_HREF          (0x02U) /* Drop HREF output of corrupt frame */

#define COM10                   (0x15U) /* Common Control 10 */
#define COM10_NEGATIVE          (0x80U) /* Output negative data */
#define COM10_HSYNC_EN          (0x40U) /* HREF changes to HSYNC */
#define COM10_PCLK_FREE         (0x00U) /* PCLK output option: free running PCLK */
#define COM10_PCLK_MASK         (0x20U) /* PCLK output option: masked during horizontal blank */
#define COM10_PCLK_REV          (0x10U) /* PCLK reverse */
#define COM10_HREF_REV          (0x08U) /* HREF reverse */
#define COM10_VSYNC_FALLING     (0x00U) /* VSYNC changes on falling edge of PCLK */
#define COM10_VSYNC_RISING      (0x04U) /* VSYNC changes on rising edge of PCLK */
#define COM10_VSYNC_NEG         (0x02U) /* VSYNC negative */
#define COM10_OUT_RANGE_8       (0x01U) /* Output data range: Full range */
#define COM10_OUT_RANGE_10      (0x00U) /* Output data range: Data from [10] to [F0] (8 MSBs) */

#define REG16                   (0x16U) /* Register 16 */
#define REG16_BIT_SHIFT         (0x80U) /* Bit shift test pattern options */
#define HSTART                  (0x17U) /* Horizontal Frame (HREF column) Start 8 MSBs (2 LSBs are at HREF[5:4]) */
#define HSIZE                   (0x18U) /* Horizontal Sensor Size (2 LSBs are at HREF[1:0]) */
#define VSTART                  (0x19U) /* Vertical Frame (row) Start 8 MSBs (1 LSB is at HREF[6]) */
#define VSIZE                   (0x1AU) /* Vertical Sensor Size (1 LSB is at HREF[2]) */
#define PSHFT                   (0x1BU) /* Data Format - Pixel Delay Select */
#define REG_MIDH                (0x1CU) /* Manufacturer ID Byte – High */
#define REG_MIDL                (0x1DU) /* Manufacturer ID Byte – Low */
#define LAEC                    (0x1FU) /* Fine AEC Value - defines exposure value less than one row period */

#define COM11                   (0x20U) /* Common Control 11 */
#define COM11_SNGL_FRAME_EN     (0x02U) /* Single frame ON/OFF selection */
#define COM11_SNGL_XFR_TRIG     (0x01U) /* Single frame transfer trigger */

#define BDBASE                  (0x22U) /* Banding Filter Minimum AEC Value */
#define DBSTEP                  (0x23U) /* Banding Filter Maximum Step */
#define AEW                     (0x24U) /* AGC/AEC - Stable Operating Region (Upper Limit) */
#define AEB                     (0x25U) /* AGC/AEC - Stable Operating Region (Lower Limit) */
#define VPT                     (0x26U) /* AGC/AEC Fast Mode Operating Region */
#define REG28                   (0x28U) /* Selection on the number of dummy rows, N */
#define HOUTSIZE                (0x29U) /* Horizontal Data Output Size MSBs (2 LSBs at register EXHCH[1:0]) */
#define EXHCH                   (0x2AU) /* Dummy Pixel Insert MSB */
#define EXHCL                   (0x2BU) /* Dummy Pixel Insert LSB */
#define VOUTSIZE                (0x2CU) /* Vertical Data Output Size MSBs (LSB at register EXHCH[2]) */
#define ADVFL                   (0x2DU) /* LSB of Insert Dummy Rows in Vertical Sync (1 bit equals 1 row) */
#define ADVFH                   (0x2EU) /* MSB of Insert Dummy Rows in Vertical Sync */
#define YAVE                    (0x2FU) /* Y/G Channel Average Value */
#define LUMHTH                  (0x30U) /* Histogram AEC/AGC Luminance High Level Threshold */
#define LUMLTH                  (0x31U) /* Histogram AEC/AGC Luminance Low Level Threshold */
#define HREF                    (0x32U) /* Image Start and Size Control */
#define DM_LNL                  (0x33U) /* Dummy Row Low 8 Bits */
#define DM_LNH                  (0x34U) /* Dummy Row High 8 Bits */
#define ADOFF_B                 (0x35U) /* AD Offset Compensation Value for B Channel */
#define ADOFF_R                 (0x36U) /* AD Offset Compensation Value for R Channel */
#define ADOFF_GB                (0x37U) /* AD Offset Compensation Value for GB Channel */
#define ADOFF_GR                (0x38U) /* AD Offset Compensation Value for GR Channel */
#define OFF_B                   (0x39U) /* AD Offset Compensation Value for B Channel */
#define OFF_R                   (0x3AU) /* AD Offset Compensation Value for R Channel */
#define OFF_GB                  (0x3BU) /* AD Offset Compensation Value for GB Channel */
#define OFF_GR                  (0x3CU) /* AD Offset Compensation Value for GR Channel */
#define COM12                   (0x3DU) /* DC offset compensation for analog process */

#define COM13                   (0x3EU) /* Common Control 13 */
#define COM13_BLC_EN            (0x80U) /* BLC enable */
#define COM13_ADC_EN            (0x40U) /* ADC channel BLC ON/OFF control */
#define COM13_ANALOG_BLC        (0x20U) /* Analog processing channel BLC ON/OFF control */
#define COM13_ABLC_GAIN_EN      (0x04U) /* ABLC gain trigger enable */

#define COM14                   (0x3FU) /* Common Control 14 */
#define COM15                   (0x40U) /* Common Control 15 */
#define COM16                   (0x41U) /* Common Control 16 */
#define TGT_B                   (0x42U) /* BLC Blue Channel Target Value */
#define TGT_R                   (0x43U) /* BLC Red Channel Target Value */
#define TGT_GB                  (0x44U) /* BLC Gb Channel Target Value */
#define TGT_GR                  (0x45U) /* BLC Gr Channel Target Value */

#define LC_CTR                  (0x46U) /* Lens Correction Control */
#define LC_CTR_RGB_COMP_1       (0x00U) /* R, G, and B channel compensation coefficient is set by LC_COEF ((0x49U)) */
/* R, G, and B channel compensation coefficient is set by registers LC_COEFB ((0x4BU)), LC_COEF ((0x49U)), and LC_COEFR ((0x4CU)), respectively */
#define LC_CTR_RGB_COMP_3       (0x04U)
#define LC_CTR_EN               (0x01U) /* Lens correction enable */
#define LC_XC                   (0x47U) /* X Coordinate of Lens Correction Center Relative to Array Center */
#define LC_YC                   (0x48U) /* Y Coordinate of Lens Correction Center Relative to Array Center */
#define LC_COEF                 (0x49U) /* Lens Correction Coefficient */
#define LC_RADI                 (0x4AU) /* Lens Correction Radius */
#define LC_COEFB                (0x4BU) /* Lens Correction B Channel Compensation Coefficient */
#define LC_COEFR                (0x4CU) /* Lens Correction R Channel Compensation Coefficient */

#define FIXGAIN                 (0x4DU) /* Analog Fix Gain Amplifier */
#define AREF0                   (0x4EU) /* Sensor Reference Control */
#define AREF1                   (0x4FU) /* Sensor Reference Current Control */
#define AREF2                   (0x50U) /* Analog Reference Control */
#define AREF3                   (0x51U) /* ADC Reference Control */
#define AREF4                   (0x52U) /* ADC Reference Control */
#define AREF5                   (0x53U) /* ADC Reference Control */
#define AREF6                   (0x54U) /* Analog Reference Control */
#define AREF7                   (0x55U) /* Analog Reference Control */
#define UFIX                    (0x60U) /* U Channel Fixed Value Output */
#define VFIX                    (0x61U) /* V Channel Fixed Value Output */
#define AWBB_BLK                (0x62U) /* AWB Option for Advanced AWB */

#define AWB_CTRL0               (0x63U) /* AWB Control Byte 0 */
#define AWB_CTRL0_GAIN_EN       (0x80U) /* AWB gain enable */
#define AWB_CTRL0_CALC_EN       (0x40U) /* AWB calculate enable */
#define AWB_CTRL0_WBC_MASK      (0x0FU) /* WBC threshold 2 */

#define DSP_CTRL1               (0x64U) /* DSP Control Byte 1 */
#define DSP_CTRL1_FIFO_EN       (0x80U) /* FIFO enable/disable selection */
#define DSP_CTRL1_UV_EN         (0x40U) /* UV adjust function ON/OFF selection */
#define DSP_CTRL1_SDE_EN        (0x20U) /* SDE enable */
#define DSP_CTRL1_MTRX_EN       (0x10U) /* Color matrix ON/OFF selection */
#define DSP_CTRL1_INTRP_EN      (0x08U) /* Interpolation ON/OFF selection */
#define DSP_CTRL1_GAMMA_EN      (0x04U) /* Gamma function ON/OFF selection */
#define DSP_CTRL1_BLACK_EN      (0x02U) /* Black defect auto correction ON/OFF */
#define DSP_CTRL1_WHITE_EN      (0x01U) /* White defect auto correction ON/OFF */

#define DSP_CTRL2               (0x65U) /* DSP Control Byte 2 */
#define DSP_CTRL2_VDCW_EN       (0x08U) /* Vertical DCW enable */
#define DSP_CTRL2_HDCW_EN       (0x04U) /* Horizontal DCW enable */
#define DSP_CTRL2_VZOOM_EN      (0x02U) /* Vertical zoom out enable */
#define DSP_CTRL2_HZOOM_EN      (0x01U) /* Horizontal zoom out enable */

#define DSP_CTRL3               (0x66U) /* DSP Control Byte 3 */
#define DSP_CTRL3_UV_EN         (0x80U) /* UV output sequence option */
#define DSP_CTRL3_CBAR_EN       (0x20U) /* DSP color bar ON/OFF selection */
#define DSP_CTRL3_FIFO_EN       (0x08U) /* FIFO power down ON/OFF selection */
#define DSP_CTRL3_SCAL1_PWDN    (0x04U) /* Scaling module power down control 1 */
#define DSP_CTRL3_SCAL2_PWDN    (0x02U) /* Scaling module power down control 2 */
#define DSP_CTRL3_INTRP_PWDN    (0x01U) /* Interpolation module power down control */

#define DSP_CTRL4               (0x67U) /* DSP Control Byte 4 */
#define DSP_CTRL4_YUV_RGB       (0x00U) /* Output selection YUV or RGB */
#define DSP_CTRL4_RAW8          (0x02U) /* Output selection RAW8 */
#define DSP_CTRL4_RAW10         (0x03U) /* Output selection RAW10 */

#define AWB_BIAS                (0x68U) /* AWB BLC Level Clip */
#define AWB_CTRL1               (0x69U) /* AWB Control 1 */
#define AWB_CTRL2               (0x6AU) /* AWB Control 2 */

#define AWB_CTRL3               (0x6BU) /* AWB Control 3 */
#define AWB_CTRL3_ADVANCED      (0x80U) /* AWB mode select - Advanced AWB */
#define AWB_CTRL3_SIMPLE        (0x00U) /* AWB mode select - Simple AWB */

#define AWB_CTRL4               (0x6CU) /* AWB Control 4 */
#define AWB_CTRL5               (0x6DU) /* AWB Control 5 */
#define AWB_CTRL6               (0x6EU) /* AWB Control 6 */
#define AWB_CTRL7               (0x6FU) /* AWB Control 7 */
#define AWB_CTRL8               (0x70U) /* AWB Control 8 */
#define AWB_CTRL9               (0x71U) /* AWB Control 9 */
#define AWB_CTRL10              (0x72U) /* AWB Control 10 */
#define AWB_CTRL11              (0x73U) /* AWB Control 11 */
#define AWB_CTRL12              (0x74U) /* AWB Control 12 */
#define AWB_CTRL13              (0x75U) /* AWB Control 13 */
#define AWB_CTRL14              (0x76U) /* AWB Control 14 */
#define AWB_CTRL15              (0x77U) /* AWB Control 15 */
#define AWB_CTRL16              (0x78U) /* AWB Control 16 */
#define AWB_CTRL17              (0x79U) /* AWB Control 17 */
#define AWB_CTRL18              (0x7AU) /* AWB Control 18 */
#define AWB_CTRL19              (0x7BU) /* AWB Control 19 */
#define AWB_CTRL20              (0x7CU) /* AWB Control 20 */
#define AWB_CTRL21              (0x7DU) /* AWB Control 21 */
#define GAM1                    (0x7EU) /* Gamma Curve 1st Segment Input End Point (0x04U) Output Value */
#define GAM2                    (0x7FU) /* Gamma Curve 2nd Segment Input End Point (0x08U) Output Value */
#define GAM3                    (0x80U) /* Gamma Curve 3rd Segment Input End Point (0x10U) Output Value */
#define GAM4                    (0x81U) /* Gamma Curve 4th Segment Input End Point (0x20U) Output Value */
#define GAM5                    (0x82U) /* Gamma Curve 5th Segment Input End Point (0x28U) Output Value */
#define GAM6                    (0x83U) /* Gamma Curve 6th Segment Input End Point (0x30U) Output Value */
#define GAM7                    (0x84U) /* Gamma Curve 7th Segment Input End Point (0x38U) Output Value */
#define GAM8                    (0x85U) /* Gamma Curve 8th Segment Input End Point (0x40U) Output Value */
#define GAM9                    (0x86U) /* Gamma Curve 9th Segment Input End Point (0x48U) Output Value */
#define GAM10                   (0x87U) /* Gamma Curve 10th Segment Input End Point (0x50U) Output Value */
#define GAM11                   (0x88U) /* Gamma Curve 11th Segment Input End Point (0x60U) Output Value */
#define GAM12                   (0x89U) /* Gamma Curve 12th Segment Input End Point (0x70U) Output Value */
#define GAM13                   (0x8AU) /* Gamma Curve 13th Segment Input End Point (0x90U) Output Value */
#define GAM14                   (0x8BU) /* Gamma Curve 14th Segment Input End Point (0xB0U) Output Value */
#define GAM15                   (0x8CU) /* Gamma Curve 15th Segment Input End Point (0xD0U) Output Value */
#define SLOP                    (0x8DU) /* Gamma Curve Highest Segment Slope */
#define DNSTH                   (0x8EU) /* De-noise Threshold */
#define EDGE0                   (0x8FU) /* Edge Enhancement Strength Control */
#define EDGE1                   (0x90U) /* Edge Enhancement Threshold Control */
#define DNSOFF                  (0x91U) /* Auto De-noise Threshold Control */
#define EDGE2                   (0x92U) /* Edge Enhancement Strength Upper Limit */
#define EDGE3                   (0x93U) /* Edge Enhancement Strength Upper Limit */
#define MTX1                    (0x94U) /* Matrix Coefficient 1 */
#define MTX2                    (0x95U) /* Matrix Coefficient 2 */
#define MTX3                    (0x96U) /* Matrix Coefficient 3 */
#define MTX4                    (0x97U) /* Matrix Coefficient 4 */
#define MTX5                    (0x98U) /* Matrix Coefficient 5 */
#define MTX6                    (0x99U) /* Matrix Coefficient 6 */

#define MTX_CTRL                (0x9AU) /* Matrix Control */
#define MTX_CTRL_DBL_EN         (0x80U) /* Matrix double ON/OFF selection */

#define BRIGHTNESS              (0x9BU) /* Brightness Control */
#define CONTRAST                (0x9CU) /* Contrast Gain */
#define UVADJ0                  (0x9EU) /* Auto UV Adjust Control 0 */
#define UVADJ1                  (0x9FU) /* Auto UV Adjust Control 1 */
#define SCAL0                   (0xA0U) /* DCW Ratio Control */
#define SCAL1                   (0xA1U) /* Horizontal Zoom Out Control */
#define SCAL2                   (0xA2U) /* Vertical Zoom Out Control */
#define FIFODLYM                (0xA3U) /* FIFO Manual Mode Delay Control */
#define FIFODLYA                (0xA4U) /* FIFO Auto Mode Delay Control */

#define SDE                     (0xA6U) /* Special Digital Effect Control */
#define SDE_NEGATIVE_EN         (0x40U) /* Negative image enable */
#define SDE_GRAYSCALE_EN        (0x20U) /* Gray scale image enable */
#define SDE_V_FIXED_EN          (0x10U) /* V fixed value enable */
#define SDE_U_FIXED_EN          (0x08U) /* U fixed value enable */
#define SDE_CONT_BRIGHT_EN      (0x04U) /* Contrast/Brightness enable */
#define SDE_SATURATION_EN       (0x02U) /* Saturation enable */
#define SDE_HUE_EN              (0x01U) /* Hue enable */

#define USAT                    (0xA7U) /* U Component Saturation Gain */
#define VSAT                    (0xA8U) /* V Component Saturation Gain */
#define HUECOS                  (0xA9U) /* Cosine value × (0x80U) */
#define HUESIN                  (0xAAU) /* Sine value × (0x80U) */
#define SIGN_BIT                (0xABU) /* Sign Bit for Hue and Brightness */

#define DSPAUTO                 (0xACU) /* DSP Auto Function ON/OFF Control */
#define DSPAUTO_AWB_EN          (0x80U) /* AWB auto threshold control */
#define DSPAUTO_DENOISE_EN      (0x40U) /* De-noise auto threshold control */
#define DSPAUTO_EDGE_EN         (0x20U) /* Sharpness (edge enhancement) auto strength control */
#define DSPAUTO_UV_EN           (0x10U) /* UV adjust auto slope control */
#define DSPAUTO_SCAL0_EN        (0x08U) /* Auto scaling factor control (register SCAL0 ((0xA0U))) */
#define DSPAUTO_SCAL1_EN        (0x04U) /* Auto scaling factor control (registers SCAL1 ((0xA1U) and SCAL2 ((0xA2U)))*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ov7725 initialization routine
 * @param [in] context camera_context_t
 * @param [in] ov_config camera config structure
 */
hpm_stat_t ov7725_init(camera_context_t *context, camera_config_t *ov_config);

/**
 * @brief ov7725 read register
 * @param [in] context camera_context_t
 * @param [in] reg register address
 * @param [in] buf buffer to store read data
 * @retval status_success if everything is okay
 */
hpm_stat_t ov7725_read_register(camera_context_t *context, uint8_t reg, uint8_t *buf);

/**
 * @brief ov7725 write register
 * @param [in] context camera_context_t
 * @param [in] reg register address
 * @param [in] val value to be written
 * @retval status_success if everything is okay
 */
hpm_stat_t ov7725_write_register(camera_context_t *context, uint8_t reg, uint8_t val);

/**
 * @brief ov7725 reset
 * @param [in] context camera_context_t
 */
hpm_stat_t ov7725_software_reset(camera_context_t *context);

/**
 * @brief ov7725 check chip id
 * @param [in] context camera_context_t
 */
hpm_stat_t ov7725_check_chip_id(camera_context_t *context);


/**
 * @brief ov7725 load set of register-value pairs
 *
 * @param [in] context camera_context_t
 * @param [in] reg_values register-value pair in 2-d array form, ex. reg_values[][2] = {{COM3, 0x1}};
 * @parma [in] count register-value pair count in 2-d array
 * @retval status_success if everything is okay
 */
hpm_stat_t ov7725_load_settings(camera_context_t *context, uint8_t *reg_values, uint32_t count);

/**
 * @brief ov7725 power up
 *
 * @param [in] context camera_context_t
 */
void ov7725_power_up(camera_context_t *context);

#ifdef __cplusplus
}
#endif

/**
 * @}
 *
 */

#endif /* HPM_OV7725_H */
