/*!
*******************************************************************************
**
** \file      gh_debug_test.h
**
** \brief     Debug TEST Registers.
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#ifndef _GH_DEBUG_TEST_H
#define _GH_DEBUG_TEST_H

#ifdef __LINUX__
#include "reg4linux.h"
#else
#define FIO_ADDRESS(block,address) (address)
#define FIO_MOFFSET(block,moffset) (moffset)
#endif

#ifndef __LINUX__
#include "gtypes.h" /* global type definitions */
#include "gh_lib_cfg.h" /* configuration */
#endif

#define GH_DEBUG_TEST_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION printk
#else
#define GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/* check configuration */
#ifndef GH_INLINE_LEVEL
  #error "GH_INLINE_LEVEL is not defined!"
#endif
#if GH_INLINE_LEVEL > 2
  #error "GH_INLINE_LEVEL must be set 0, 1 or 2!"
#endif
#ifndef GH_INLINE
  #error "GH_INLINE is not defined!"
#endif

/* disable inlining for debugging */
#ifdef DEBUG
  #undef GH_INLINE_LEVEL
  #define GH_INLINE_LEVEL 0
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_DEBUG_TEST_PLL_CORE_CTRL                        FIO_ADDRESS(DEBUG_TEST,0x70190000) /* read/write */
#define REG_DEBUG_TEST_PLL_CORE_FRAC                        FIO_ADDRESS(DEBUG_TEST,0x70190004) /* read/write */
#define REG_DEBUG_TEST_HDMI_CTRL                            FIO_ADDRESS(DEBUG_TEST,0x70190008) /* read/write */
#define REG_DEBUG_TEST_SCALER_SD48                          FIO_ADDRESS(DEBUG_TEST,0x7019000C) /* read/write */
#define REG_DEBUG_TEST_PLL_VIDEO_CTRL                       FIO_ADDRESS(DEBUG_TEST,0x70190014) /* read/write */
#define REG_DEBUG_TEST_PLL_VIDEO_FRAC                       FIO_ADDRESS(DEBUG_TEST,0x70190018) /* read/write */
#define REG_DEBUG_TEST_SCALER_VIDEO                         FIO_ADDRESS(DEBUG_TEST,0x7019001C) /* read/write */
#define REG_DEBUG_TEST_PLL_SENSOR_CTRL                      FIO_ADDRESS(DEBUG_TEST,0x70190024) /* read/write */
#define REG_DEBUG_TEST_PLL_SENSOR_FRAC                      FIO_ADDRESS(DEBUG_TEST,0x70190028) /* read/write */
#define REG_DEBUG_TEST_PLL_LOCK                             FIO_ADDRESS(DEBUG_TEST,0x7019002C) /* read */
#define REG_DEBUG_TEST_SCALER_SENSOR_POST                   FIO_ADDRESS(DEBUG_TEST,0x70190030) /* read/write */
#define REG_DEBUG_TEST_SYS_CONFIG                           FIO_ADDRESS(DEBUG_TEST,0x70190034) /* read/write */
#define REG_DEBUG_TEST_CG_UART                              FIO_ADDRESS(DEBUG_TEST,0x70190038) /* read/write */
#define REG_DEBUG_TEST_CG_SSI                               FIO_ADDRESS(DEBUG_TEST,0x7019003C) /* read/write */
#define REG_DEBUG_TEST_CG_MOTOR                             FIO_ADDRESS(DEBUG_TEST,0x70190040) /* read/write */
#define REG_DEBUG_TEST_CG_IR                                FIO_ADDRESS(DEBUG_TEST,0x70190044) /* read/write */
#define REG_DEBUG_TEST_CG_HOST                              FIO_ADDRESS(DEBUG_TEST,0x70190048) /* read/write */
#define REG_DEBUG_TEST_SCALER_SENSOR_PRE                    FIO_ADDRESS(DEBUG_TEST,0x7019004C) /* read/write */
#define REG_DEBUG_TEST_ANA_PWR                              FIO_ADDRESS(DEBUG_TEST,0x70190050) /* read/write */
#define REG_DEBUG_TEST_PLL_AUDIO_CTRL                       FIO_ADDRESS(DEBUG_TEST,0x70190054) /* read/write */
#define REG_DEBUG_TEST_PLL_AUDIO_FRAC                       FIO_ADDRESS(DEBUG_TEST,0x70190058) /* read/write */
#define REG_DEBUG_TEST_SCALER_AUDIO                         FIO_ADDRESS(DEBUG_TEST,0x7019005C) /* read/write */
#define REG_DEBUG_TEST_SCALER_AUDIO_PRE                     FIO_ADDRESS(DEBUG_TEST,0x70190060) /* read/write */
#define REG_DEBUG_TEST_SOFT_OR_DLLRESET                     FIO_ADDRESS(DEBUG_TEST,0x70190068) /* read/write */
#define REG_DEBUG_TEST_FIO_RESET                            FIO_ADDRESS(DEBUG_TEST,0x70190074) /* read/write */
#define REG_DEBUG_TEST_WDT_RST_L                            FIO_ADDRESS(DEBUG_TEST,0x70190078) /* read */
#define REG_DEBUG_TEST_SCALER_USB                           FIO_ADDRESS(DEBUG_TEST,0x7019007C) /* read/write */
#define REG_DEBUG_TEST_CLK_DEBOUNCE                         FIO_ADDRESS(DEBUG_TEST,0x70190080) /* read/write */
#define REG_DEBUG_TEST_CG_PWM                               FIO_ADDRESS(DEBUG_TEST,0x70190084) /* read/write */
#define REG_DEBUG_TEST_USBP_CTRL                            FIO_ADDRESS(DEBUG_TEST,0x70190088) /* read/write */
#define REG_DEBUG_TEST_CKEN_VDSP                            FIO_ADDRESS(DEBUG_TEST,0x7019008C) /* read/write */
#define REG_DEBUG_TEST_DLL0                                 FIO_ADDRESS(DEBUG_TEST,0x70190090) /* read/write */
#define REG_DEBUG_TEST_DLL1                                 FIO_ADDRESS(DEBUG_TEST,0x70190094) /* read/write */
#define REG_DEBUG_TEST_SCALER_ADC                           FIO_ADDRESS(DEBUG_TEST,0x7019009C) /* read/write */
#define REG_DEBUG_TEST_SCALER_VIDEO_POST                    FIO_ADDRESS(DEBUG_TEST,0x701900A0) /* read/write */
#define REG_DEBUG_TEST_CLK_REF_AU_EXTERNAL                  FIO_ADDRESS(DEBUG_TEST,0x701900A4) /* read/write */
#define REG_DEBUG_TEST_USE_EXTERNAL_CLK_AU                  FIO_ADDRESS(DEBUG_TEST,0x701900A8) /* read/write */
#define REG_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL               FIO_ADDRESS(DEBUG_TEST,0x701900AC) /* read/write */
#define REG_DEBUG_TEST_USE_EXTERNAL_VD_CLK                  FIO_ADDRESS(DEBUG_TEST,0x701900B0) /* read/write */
#define REG_DEBUG_TEST_USE_CLK_SI_4_CLK_AU                  FIO_ADDRESS(DEBUG_TEST,0x701900B4) /* read/write */
#define REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO                  FIO_ADDRESS(DEBUG_TEST,0x701900B8) /* read/write */
#define REG_DEBUG_TEST_CLK_SI_INPUT_MODE                    FIO_ADDRESS(DEBUG_TEST,0x701900BC) /* read/write */
#define REG_DEBUG_TEST_PLL_VIDEO2_CTRL                      FIO_ADDRESS(DEBUG_TEST,0x701900C0) /* read/write */
#define REG_DEBUG_TEST_PLL_VIDEO2_FRAC                      FIO_ADDRESS(DEBUG_TEST,0x701900C4) /* read/write */
#define REG_DEBUG_TEST_SCALER_VIDEO2                        FIO_ADDRESS(DEBUG_TEST,0x701900C8) /* read/write */
#define REG_DEBUG_TEST_SCALER_VIDEO2_POST                   FIO_ADDRESS(DEBUG_TEST,0x701900CC) /* read/write */
#define REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2                 FIO_ADDRESS(DEBUG_TEST,0x701900D0) /* read/write */
#define REG_DEBUG_TEST_USE_EXTERNAL_VD2_CLK                 FIO_ADDRESS(DEBUG_TEST,0x701900D4) /* read/write */
#define REG_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL              FIO_ADDRESS(DEBUG_TEST,0x701900D8) /* read/write */
#define REG_DEBUG_TEST_PLL_DDR_CTRL                         FIO_ADDRESS(DEBUG_TEST,0x701900DC) /* read/write */
#define REG_DEBUG_TEST_PLL_DDR_FRAC                         FIO_ADDRESS(DEBUG_TEST,0x701900E0) /* read/write */
#define REG_DEBUG_TEST_PLL_IDSP_CTRL                        FIO_ADDRESS(DEBUG_TEST,0x701900E4) /* read/write */
#define REG_DEBUG_TEST_PLL_IDSP_FRAC                        FIO_ADDRESS(DEBUG_TEST,0x701900E8) /* read/write */
#define REG_DEBUG_TEST_CG_SSI2                              FIO_ADDRESS(DEBUG_TEST,0x701900EC) /* read/write */
#define REG_DEBUG_TEST_LVDS_LVCMOS                          FIO_ADDRESS(DEBUG_TEST,0x701900F8) /* read/write */
#define REG_DEBUG_TEST_LVDS_ASYNC                           FIO_ADDRESS(DEBUG_TEST,0x701900FC) /* read/write */
#define REG_DEBUG_TEST_PLL_CORE_CTRL2                       FIO_ADDRESS(DEBUG_TEST,0x70190100) /* read/write */
#define REG_DEBUG_TEST_PLL_CORE_CTRL3                       FIO_ADDRESS(DEBUG_TEST,0x70190104) /* read/write */
#define REG_DEBUG_TEST_PLL_IDSP_CTRL2                       FIO_ADDRESS(DEBUG_TEST,0x70190108) /* read/write */
#define REG_DEBUG_TEST_PLL_IDSP_CTRL3                       FIO_ADDRESS(DEBUG_TEST,0x7019010C) /* read/write */
#define REG_DEBUG_TEST_PLL_IDSP_CTRL22                      FIO_ADDRESS(DEBUG_TEST,0x70190110) /* read/write */
#define REG_DEBUG_TEST_PLL_IDSP_CTRL32                      FIO_ADDRESS(DEBUG_TEST,0x70190114) /* read/write */
#define REG_DEBUG_TEST_SCALER_CORE_POST                     FIO_ADDRESS(DEBUG_TEST,0x70190118) /* read/write */
#define REG_DEBUG_TEST_PLL_SENSOR_CTRL2                     FIO_ADDRESS(DEBUG_TEST,0x7019011C) /* read/write */
#define REG_DEBUG_TEST_PLL_SENSOR_CTRL3                     FIO_ADDRESS(DEBUG_TEST,0x70190120) /* read/write */
#define REG_DEBUG_TEST_PLL_AUDIO_CTRL2                      FIO_ADDRESS(DEBUG_TEST,0x70190124) /* read/write */
#define REG_DEBUG_TEST_PLL_AUDIO_CTRL3                      FIO_ADDRESS(DEBUG_TEST,0x7019012C) /* read/write */
#define REG_DEBUG_TEST_PLL_VIDEO_CTRL2                      FIO_ADDRESS(DEBUG_TEST,0x70190130) /* read/write */
#define REG_DEBUG_TEST_PLL_VIDEO_CTRL3                      FIO_ADDRESS(DEBUG_TEST,0x70190134) /* read/write */
#define REG_DEBUG_TEST_PLL_VIDEO2_CTRL2                     FIO_ADDRESS(DEBUG_TEST,0x7019013C) /* read/write */
#define REG_DEBUG_TEST_PLL_USB_CTRL2                        FIO_ADDRESS(DEBUG_TEST,0x70190144) /* read/write */
#define REG_DEBUG_TEST_CG_DDR_CALIB                         FIO_ADDRESS(DEBUG_TEST,0x70190148) /* read/write */
#define REG_DEBUG_TEST_DLL_CTRL_SEL                         FIO_ADDRESS(DEBUG_TEST,0x70190158) /* read/write */
#define REG_DEBUG_TEST_DLL_OCD_BITS                         FIO_ADDRESS(DEBUG_TEST,0x7019015C) /* read/write */
#define REG_DEBUG_TEST_PLL_CORE_OBSV                        FIO_ADDRESS(DEBUG_TEST,0x70190174) /* read/write */
#define REG_DEBUG_TEST_PLL_IDSP_OBSV                        FIO_ADDRESS(DEBUG_TEST,0x70190178) /* read/write */
#define REG_DEBUG_TEST_PLL_DDR_OBSV                         FIO_ADDRESS(DEBUG_TEST,0x7019017C) /* read/write */
#define REG_DEBUG_TEST_PLL_SENSOR_OBSV                      FIO_ADDRESS(DEBUG_TEST,0x70190180) /* read/write */
#define REG_DEBUG_TEST_PLL_AUDIO_OBSV                       FIO_ADDRESS(DEBUG_TEST,0x70190184) /* read/write */
#define REG_DEBUG_TEST_PLL_VIDEO_OBSV                       FIO_ADDRESS(DEBUG_TEST,0x70190188) /* read/write */
#define REG_DEBUG_TEST_PLL_VIDEO2_OBSV                      FIO_ADDRESS(DEBUG_TEST,0x7019018C) /* read/write */
#define REG_DEBUG_TEST_ADC16_CTRL_ADDR                      FIO_ADDRESS(DEBUG_TEST,0x70190198) /* read/write */
#define REG_DEBUG_TEST_CLK_REF_SSI_ADDR                     FIO_ADDRESS(DEBUG_TEST,0x7019019C) /* read/write */
#define REG_DEBUG_TEST_CG_DVEN                              FIO_ADDRESS(DEBUG_TEST,0x701901C8) /* read/write */
#define REG_DEBUG_TEST_SCALER_MS                            FIO_ADDRESS(DEBUG_TEST,0x701901CC) /* read/write */
#define REG_DEBUG_TEST_MS_DELAY_CTRL                        FIO_ADDRESS(DEBUG_TEST,0x701901D0) /* read/write */
#define REG_DEBUG_TEST_USE_COMMON_VO_CLOCK                  FIO_ADDRESS(DEBUG_TEST,0x701901D4) /* read/write */
#define REG_DEBUG_TEST_CLOCK_OBSV_ADDR                      FIO_ADDRESS(DEBUG_TEST,0x701901E0) /* read/write */
#define REG_DEBUG_TEST_DISABLE_EXT_BYPASS                   FIO_ADDRESS(DEBUG_TEST,0x701901E4) /* read/write */
#define REG_DEBUG_TEST_ARM_SYNC_LOCK                        FIO_ADDRESS(DEBUG_TEST,0x701901E8) /* read/write */
#define REG_DEBUG_TEST_SCALER_ARM_SYNC                      FIO_ADDRESS(DEBUG_TEST,0x701901EC) /* read/write */
#define REG_DEBUG_TEST_SCALER_ARM_ASYNC                     FIO_ADDRESS(DEBUG_TEST,0x701901F0) /* read/write */
#define REG_DEBUG_TEST_SCALER_IDSP_POST                     FIO_ADDRESS(DEBUG_TEST,0x701901F4) /* read/write */
#define REG_DEBUG_TEST_OCTRL_GPIO                           FIO_ADDRESS(DEBUG_TEST,0x701901F8) /* read/write */
#define REG_DEBUG_TEST_IOCTRL_MISC1                         FIO_ADDRESS(DEBUG_TEST,0x701901FC) /* read/write */
#define REG_DEBUG_TEST_OCTRL_MISC2                          FIO_ADDRESS(DEBUG_TEST,0x70190200) /* read/write */
#define REG_DEBUG_TEST_IOCTRL_SD                            FIO_ADDRESS(DEBUG_TEST,0x70190204) /* read/write */
#define REG_DEBUG_TEST_IOCTRL_SMIO                          FIO_ADDRESS(DEBUG_TEST,0x70190208) /* read/write */
#define REG_DEBUG_TEST_IOCTRL_VD0                           FIO_ADDRESS(DEBUG_TEST,0x7019020C) /* read/write */
#define REG_DEBUG_TEST_IOCTRL_VD1                           FIO_ADDRESS(DEBUG_TEST,0x70190210) /* read/write */
#define REG_DEBUG_TEST_IOCTRL_SENSOR                        FIO_ADDRESS(DEBUG_TEST,0x70190214) /* read/write */
#define REG_DEBUG_TEST_AHB_MISC_EN                          FIO_ADDRESS(DEBUG_TEST,0x7019021C) /* read/write */
#define REG_DEBUG_TEST_CG_DDR_INIT                          FIO_ADDRESS(DEBUG_TEST,0x70190220) /* read/write */
#define REG_DEBUG_TEST_DDR_DIV_RST                          FIO_ADDRESS(DEBUG_TEST,0x70190224) /* read/write */
#define REG_DEBUG_TEST_DDRC_IDSP_RESET                      FIO_ADDRESS(DEBUG_TEST,0x70190228) /* read/write */
#define REG_DEBUG_TEST_CKEN_IDSP                            FIO_ADDRESS(DEBUG_TEST,0x7019022C) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* DEBUG_TEST_HDMI_CTRL */
    U32 all;
    struct {
        U32                             : 1;
        U32 hdmi_phy_test_mode          : 1;
        U32 use_hdmi_phy_clk_v          : 1;
        U32                             : 29;
    } bitc;
} GH_DEBUG_TEST_HDMI_CTRL_S;

typedef union { /* DEBUG_TEST_SCALER_SD48 */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 6;
        U32 sdclk_delay                 : 2;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_SCALER_SD48_S;

typedef union { /* DEBUG_TEST_PLL_VIDEO_CTRL */
    U32 all;
    struct {
        U32 writeenable                 : 1;
        U32                             : 1;
        U32 bypass                      : 1;
        U32 mode                        : 1;
        U32 reset                       : 1;
        U32 powerdown                   : 1;
        U32 halfvco                     : 1;
        U32 tristate                    : 1;
        U32 pll_tout_async              : 4;
        U32 sdiv                        : 4;
        U32 sout                        : 4;
        U32 pll_lock                    : 1;
        U32 gclk_vo                     : 1;
        U32                             : 2;
        U32 intprog                     : 7;
        U32                             : 1;
    } bitc;
} GH_DEBUG_TEST_PLL_VIDEO_CTRL_S;

typedef union { /* DEBUG_TEST_SCALER_VIDEO */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_SCALER_VIDEO_S;

typedef union { /* DEBUG_TEST_PLL_LOCK */
    U32 all;
    struct {
        U32 pll_video2                  : 1;
        U32 pll_video                   : 1;
        U32 pll_usb                     : 1;
        U32 pll_sensor                  : 1;
        U32 pll_idsp                    : 1;
        U32 pll_ddr                     : 1;
        U32 pll_core                    : 1;
        U32 pll_audio                   : 1;
        U32 pll_hdmi                    : 1;
        U32 pll_vin                     : 1;
        U32                             : 22;
    } bitc;
} GH_DEBUG_TEST_PLL_LOCK_S;

typedef union { /* DEBUG_TEST_SCALER_SENSOR_POST */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_SCALER_SENSOR_POST_S;

typedef union { /* DEBUG_TEST_SYS_CONFIG */
    U32 all;
    struct {
        U32 bootmedia                   : 1;
        U32 clock                       : 3;
        U32 grst                        : 1;
        U32 page_size                   : 1;
        U32 read                        : 1;
        U32 enet                        : 1;
        U32 boot_bypass                 : 1;
        U32 fastboot                    : 1;
        U32 io_flash_boot               : 1;
        U32 sd_boot                     : 1;
        U32 ema_sel                     : 1;
        U32 lock_mode                   : 1;
        U32 grst_l                      : 1;
        U32 rmii_sel                    : 1;
        U32 spi_boot                    : 1;
        U32 hif_en                      : 1;
        U32 free                        : 1;
        U32 hif_type                    : 1;
        U32 rdy_pl                      : 1;
        U32 rct_ahb_hif_secure_mode     : 1;
        U32                             : 1;
        U32 usbp                        : 1;
        U32                             : 2;
        U32 ref_clk_is_24mhz            : 1;
        U32 rct_bira_efuse_disable      : 1;
        U32                             : 1;
        U32 hardcoded                   : 2;
        U32 source                      : 1;
    } bitc;
} GH_DEBUG_TEST_SYS_CONFIG_S;

typedef union { /* DEBUG_TEST_SCALER_SENSOR_PRE */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_SCALER_SENSOR_PRE_S;

typedef union { /* DEBUG_TEST_ANA_PWR */
    U32 all;
    struct {
        U32                             : 1;
        U32 usbsuspend                  : 1;
        U32 suspendusbp                 : 1;
        U32                             : 2;
        U32 power_controller            : 1;
        U32                             : 1;
        U32 dllpowerdown                : 1;
        U32                             : 24;
    } bitc;
} GH_DEBUG_TEST_ANA_PWR_S;

typedef union { /* DEBUG_TEST_SCALER_AUDIO */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_SCALER_AUDIO_S;

typedef union { /* DEBUG_TEST_SCALER_AUDIO_PRE */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_SCALER_AUDIO_PRE_S;

typedef union { /* DEBUG_TEST_SOFT_OR_DLLRESET */
    U32 all;
    struct {
        U32 softreset                   : 1;
        U32 dll_rst_l                   : 1;
        U32                             : 30;
    } bitc;
} GH_DEBUG_TEST_SOFT_OR_DLLRESET_S;

typedef union { /* DEBUG_TEST_FIO_RESET */
    U32 all;
    struct {
        U32 flashreset                  : 1;
        U32 xdreset                     : 1;
        U32 cfreset                     : 1;
        U32 fioreset                    : 1;
        U32                             : 28;
    } bitc;
} GH_DEBUG_TEST_FIO_RESET_S;

typedef union { /* DEBUG_TEST_SCALER_USB */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_SCALER_USB_S;

typedef union { /* DEBUG_TEST_USBP_CTRL */
    U32 all;
    struct {
        U32 refclkdiv                   : 2;
        U32 usbphy_reset                : 1;
        U32 refclksel                   : 2;
        U32                             : 1;
        U32 commononn                   : 1;
        U32 compdistune                 : 3;
        U32 otgtune                     : 3;
        U32 sqrxtune                    : 3;
        U32 rxfslstune                  : 4;
        U32 txpreemphasistune           : 1;
        U32 txrisetune                  : 1;
        U32 txvreftune                  : 4;
        U32 txhsxvtune                  : 2;
        U32 atereset                    : 1;
        U32 usbdcsoftreset              : 1;
        U32 sleepm                      : 1;
        U32                             : 1;
    } bitc;
} GH_DEBUG_TEST_USBP_CTRL_S;

typedef union { /* DEBUG_TEST_CKEN_VDSP */
    U32 all;
    struct {
        U32 cken_tsfm                   : 1;
        U32 cken_code                   : 1;
        U32 cken_smem                   : 1;
        U32                             : 29;
    } bitc;
} GH_DEBUG_TEST_CKEN_VDSP_S;

typedef union { /* DEBUG_TEST_DLL0 */
    U32 all;
    struct {
        U32 dll_sel2                    : 8;
        U32 dll_sel1                    : 8;
        U32 dll_sel0                    : 8;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_DLL0_S;

typedef union { /* DEBUG_TEST_DLL1 */
    U32 all;
    struct {
        U32 dll_sel2                    : 8;
        U32 dll_sel1                    : 8;
        U32 dll_sel0                    : 8;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_DLL1_S;

typedef union { /* DEBUG_TEST_SCALER_ADC */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_SCALER_ADC_S;

typedef union { /* DEBUG_TEST_SCALER_VIDEO_POST */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_SCALER_VIDEO_POST_S;

typedef union { /* DEBUG_TEST_CLK_REF_AU_EXTERNAL */
    U32 all;
    struct {
        U32 external                    : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_TEST_CLK_REF_AU_EXTERNAL_S;

typedef union { /* DEBUG_TEST_USE_EXTERNAL_CLK_AU */
    U32 all;
    struct {
        U32 external                    : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_TEST_USE_EXTERNAL_CLK_AU_S;

typedef union { /* DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL */
    U32 all;
    struct {
        U32 external                    : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL_S;

typedef union { /* DEBUG_TEST_USE_EXTERNAL_VD_CLK */
    U32 all;
    struct {
        U32 external                    : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_TEST_USE_EXTERNAL_VD_CLK_S;

typedef union { /* DEBUG_TEST_USE_CLK_SI_4_CLK_AU */
    U32 all;
    struct {
        U32 pllref                      : 2;
        U32                             : 30;
    } bitc;
} GH_DEBUG_TEST_USE_CLK_SI_4_CLK_AU_S;

typedef union { /* DEBUG_TEST_USE_CLK_SI_4_CLK_VO */
    U32 all;
    struct {
        U32 pllref                      : 2;
        U32                             : 30;
    } bitc;
} GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO_S;

typedef union { /* DEBUG_TEST_CLK_SI_INPUT_MODE */
    U32 all;
    struct {
        U32 clk_si                      : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_TEST_CLK_SI_INPUT_MODE_S;

typedef union { /* DEBUG_TEST_PLL_VIDEO2_CTRL */
    U32 all;
    struct {
        U32                             : 20;
        U32 pll_lock                    : 1;
        U32 gclk_vo                     : 1;
        U32                             : 10;
    } bitc;
} GH_DEBUG_TEST_PLL_VIDEO2_CTRL_S;

typedef union { /* DEBUG_TEST_SCALER_VIDEO2 */
    U32 all;
    struct {
        U32 integerdiv                  : 16;
        U32 primediv                    : 5;
        U32                             : 3;
        U32 dutycycle                   : 1;
        U32                             : 7;
    } bitc;
} GH_DEBUG_TEST_SCALER_VIDEO2_S;

typedef union { /* DEBUG_TEST_SCALER_VIDEO2_POST */
    U32 all;
    struct {
        U32 integerdiv                  : 16;
        U32 primediv                    : 5;
        U32                             : 3;
        U32 dutycycle                   : 1;
        U32                             : 7;
    } bitc;
} GH_DEBUG_TEST_SCALER_VIDEO2_POST_S;

typedef union { /* DEBUG_TEST_USE_CLK_SI_4_CLK_VO2 */
    U32 all;
    struct {
        U32 pllref                      : 2;
        U32                             : 30;
    } bitc;
} GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2_S;

typedef union { /* DEBUG_TEST_USE_EXTERNAL_VD2_CLK */
    U32 all;
    struct {
        U32 external                    : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_TEST_USE_EXTERNAL_VD2_CLK_S;

typedef union { /* DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL */
    U32 all;
    struct {
        U32 external                    : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL_S;

typedef union { /* DEBUG_TEST_PLL_DDR_FRAC */
    U32 all;
    struct {
        U32 fraction                    : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_PLL_DDR_FRAC_S;

typedef union { /* DEBUG_TEST_PLL_IDSP_FRAC */
    U32 all;
    struct {
        U32 fraction                    : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_PLL_IDSP_FRAC_S;

typedef union { /* DEBUG_TEST_LVDS_LVCMOS */
    U32 all;
    struct {
        U32 lvcoms_sd                   : 16;
        U32 lvcmos_spclk                : 4;
        U32                             : 12;
    } bitc;
} GH_DEBUG_TEST_LVDS_LVCMOS_S;

typedef union { /* DEBUG_TEST_LVDS_ASYNC */
    U32 all;
    struct {
        U32 async_sd                    : 16;
        U32 async_spclk                 : 4;
        U32 lvds_pd                     : 1;
        U32 lvds_ib_ctrl                : 2;
        U32                             : 1;
        U32 lvds_bit_mode               : 4;
        U32                             : 4;
    } bitc;
} GH_DEBUG_TEST_LVDS_ASYNC_S;

typedef union { /* DEBUG_TEST_PLL_CORE_CTRL2 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_PLL_CORE_CTRL2_S;

typedef union { /* DEBUG_TEST_PLL_CORE_CTRL3 */
    U32 all;
    struct {
        U32 vco                         : 1;
        U32 pll_vco                     : 2;
        U32 clamp                       : 2;
        U32 dsm_dither                  : 1;
        U32                             : 1;
        U32 dsm_dither_gain             : 2;
        U32                             : 4;
        U32 feedforward                 : 4;
        U32 bias                        : 3;
        U32 jdiv                        : 1;
        U32                             : 11;
    } bitc;
} GH_DEBUG_TEST_PLL_CORE_CTRL3_S;

typedef union { /* DEBUG_TEST_PLL_IDSP_CTRL2 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_PLL_IDSP_CTRL2_S;

typedef union { /* DEBUG_TEST_PLL_IDSP_CTRL3 */
    U32 all;
    struct {
        U32 vco                         : 1;
        U32 pll_vco                     : 2;
        U32 clamp                       : 2;
        U32 dsm_dither                  : 1;
        U32                             : 1;
        U32 dsm_dither_gain             : 2;
        U32                             : 4;
        U32 feedforward                 : 4;
        U32 bias                        : 3;
        U32 jdiv                        : 1;
        U32                             : 11;
    } bitc;
} GH_DEBUG_TEST_PLL_IDSP_CTRL3_S;

typedef union { /* DEBUG_TEST_PLL_IDSP_CTRL22 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_PLL_IDSP_CTRL22_S;

typedef union { /* DEBUG_TEST_PLL_IDSP_CTRL32 */
    U32 all;
    struct {
        U32 vco                         : 1;
        U32 pll_vco                     : 2;
        U32 clamp                       : 2;
        U32 dsm_dither                  : 1;
        U32                             : 1;
        U32 dsm_dither_gain             : 2;
        U32                             : 4;
        U32 feedforward                 : 4;
        U32 bias                        : 3;
        U32 jdiv                        : 1;
        U32                             : 11;
    } bitc;
} GH_DEBUG_TEST_PLL_IDSP_CTRL32_S;

typedef union { /* DEBUG_TEST_SCALER_CORE_POST */
    U32 all;
    struct {
        U32 div                         : 4;
        U32                             : 28;
    } bitc;
} GH_DEBUG_TEST_SCALER_CORE_POST_S;

typedef union { /* DEBUG_TEST_PLL_SENSOR_CTRL2 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_PLL_SENSOR_CTRL2_S;

typedef union { /* DEBUG_TEST_PLL_SENSOR_CTRL3 */
    U32 all;
    struct {
        U32 vco                         : 1;
        U32 pll_vco                     : 2;
        U32 clamp                       : 2;
        U32 dsm_dither                  : 1;
        U32                             : 1;
        U32 dsm_dither_gain             : 2;
        U32                             : 4;
        U32 feedforward                 : 4;
        U32 bias                        : 3;
        U32 jdiv                        : 1;
        U32                             : 11;
    } bitc;
} GH_DEBUG_TEST_PLL_SENSOR_CTRL3_S;

typedef union { /* DEBUG_TEST_PLL_AUDIO_CTRL2 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_PLL_AUDIO_CTRL2_S;

typedef union { /* DEBUG_TEST_PLL_AUDIO_CTRL3 */
    U32 all;
    struct {
        U32 vco                         : 1;
        U32 pll_vco                     : 2;
        U32 clamp                       : 2;
        U32 dsm_dither                  : 1;
        U32                             : 1;
        U32 dsm_dither_gain             : 2;
        U32                             : 4;
        U32 feedforward                 : 4;
        U32 bias                        : 3;
        U32 jdiv                        : 1;
        U32                             : 11;
    } bitc;
} GH_DEBUG_TEST_PLL_AUDIO_CTRL3_S;

typedef union { /* DEBUG_TEST_PLL_VIDEO_CTRL2 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_PLL_VIDEO_CTRL2_S;

typedef union { /* DEBUG_TEST_PLL_VIDEO_CTRL3 */
    U32 all;
    struct {
        U32 vco                         : 1;
        U32 pll_vco                     : 2;
        U32 clamp                       : 2;
        U32 dsm_dither                  : 1;
        U32                             : 1;
        U32 dsm_dither_gain             : 2;
        U32                             : 4;
        U32 feedforward                 : 4;
        U32 bias                        : 3;
        U32 jdiv                        : 1;
        U32                             : 11;
    } bitc;
} GH_DEBUG_TEST_PLL_VIDEO_CTRL3_S;

typedef union { /* DEBUG_TEST_PLL_VIDEO2_CTRL2 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_PLL_VIDEO2_CTRL2_S;

typedef union { /* DEBUG_TEST_PLL_USB_CTRL2 */
    U32 all;
    struct {
        U32 vco                         : 1;
        U32 pll_vco                     : 2;
        U32 clamp                       : 2;
        U32 dsm_dither                  : 1;
        U32                             : 1;
        U32 dsm_dither_gain             : 2;
        U32                             : 4;
        U32 feedforward                 : 4;
        U32 bias                        : 3;
        U32 jdiv                        : 1;
        U32                             : 11;
    } bitc;
} GH_DEBUG_TEST_PLL_USB_CTRL2_S;

typedef union { /* DEBUG_TEST_DLL_CTRL_SEL */
    U32 all;
    struct {
        U32 rct_ddrio_dll_sbc           : 12;
        U32 rct_ddrio_dll_selm          : 3;
        U32 rct_ddrio_single_end        : 1;
        U32 rct_ddrio_pue_dq            : 1;
        U32 rct_ddrio_pde_dq            : 1;
        U32 rct_ddrio_npue_dqs          : 1;
        U32 rct_ddrio_npde_dqs          : 1;
        U32 rct_ddrio_ppde_dqs          : 1;
        U32 rct_ddrio_ppue_dqs          : 1;
        U32 rct_ddrio_cmosrcv           : 1;
        U32 rct_ddrio_pue_cmd           : 1;
        U32 rct_ddrio_pde_cmd           : 1;
        U32 rct_ddrio_npue_dqs2         : 1;
        U32 rct_ddrio_npde_dqs2         : 1;
        U32 rct_ddrio_ppde_dqs2         : 1;
        U32 rct_ddrio_ppue_dqs2         : 1;
        U32                             : 3;
    } bitc;
} GH_DEBUG_TEST_DLL_CTRL_SEL_S;

typedef union { /* DEBUG_TEST_DLL_OCD_BITS */
    U32 all;
    struct {
        U32                             : 1;
        U32 rct_ddrio_ddr2              : 1;
        U32 rct_ddrio_ocd_cmd           : 5;
        U32                             : 1;
        U32 rct_ddrio_ocd               : 5;
        U32                             : 3;
        U32 rct_ddrio_odt               : 5;
        U32                             : 11;
    } bitc;
} GH_DEBUG_TEST_DLL_OCD_BITS_S;

typedef union { /* DEBUG_TEST_ADC16_CTRL_ADDR */
    U32 all;
    struct {
        U32 adc_power_down              : 1;
        U32 adc_clock_select            : 1;
        U32                             : 30;
    } bitc;
} GH_DEBUG_TEST_ADC16_CTRL_ADDR_S;

typedef union { /* DEBUG_TEST_CLK_REF_SSI_ADDR */
    U32 all;
    struct {
        U32 clk                         : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_TEST_CLK_REF_SSI_ADDR_S;

typedef union { /* DEBUG_TEST_MS_DELAY_CTRL */
    U32 all;
    struct {
        U32                             : 8;
        U32 delay_sclk                  : 3;
        U32                             : 5;
        U32 input_delay                 : 3;
        U32                             : 5;
        U32 output_delay                : 3;
        U32                             : 1;
        U32 timing                      : 4;
    } bitc;
} GH_DEBUG_TEST_MS_DELAY_CTRL_S;

typedef union { /* DEBUG_TEST_CLOCK_OBSV_ADDR */
    U32 all;
    struct {
        U32 pll                         : 4;
        U32 observation                 : 1;
        U32                             : 27;
    } bitc;
} GH_DEBUG_TEST_CLOCK_OBSV_ADDR_S;

typedef union { /* DEBUG_TEST_ARM_SYNC_LOCK */
    U32 all;
    struct {
        U32 mode                        : 1;
        U32 reset                       : 1;
        U32                             : 30;
    } bitc;
} GH_DEBUG_TEST_ARM_SYNC_LOCK_S;

typedef union { /* DEBUG_TEST_SCALER_ARM_ASYNC */
    U32 all;
    struct {
        U32 div                         : 4;
        U32                             : 28;
    } bitc;
} GH_DEBUG_TEST_SCALER_ARM_ASYNC_S;

typedef union { /* DEBUG_TEST_SCALER_IDSP_POST */
    U32 all;
    struct {
        U32 div                         : 4;
        U32                             : 28;
    } bitc;
} GH_DEBUG_TEST_SCALER_IDSP_POST_S;

typedef union { /* DEBUG_TEST_AHB_MISC_EN */
    U32 all;
    struct {
        U32 rct_ahb                     : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_TEST_AHB_MISC_EN_S;

typedef union { /* DEBUG_TEST_CG_DDR_INIT */
    U32 all;
    struct {
        U32 divide                      : 8;
        U32 en                          : 1;
        U32                             : 23;
    } bitc;
} GH_DEBUG_TEST_CG_DDR_INIT_S;

typedef union { /* DEBUG_TEST_DDRC_IDSP_RESET */
    U32 all;
    struct {
        U32 ddrc                        : 1;
        U32 idsp                        : 1;
        U32                             : 30;
    } bitc;
} GH_DEBUG_TEST_DDRC_IDSP_RESET_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_CORE_CTRL (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_CORE_CTRL'. */
void GH_DEBUG_TEST_set_PLL_CORE_CTRL(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_CORE_CTRL'. */
U32  GH_DEBUG_TEST_get_PLL_CORE_CTRL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_CORE_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_CORE_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_CORE_CTRL] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_CORE_FRAC (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_CORE_FRAC'. */
void GH_DEBUG_TEST_set_PLL_CORE_FRAC(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_CORE_FRAC'. */
U32  GH_DEBUG_TEST_get_PLL_CORE_FRAC(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_FRAC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_FRAC = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_CORE_FRAC] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_FRAC,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_CORE_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_FRAC);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_CORE_FRAC] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_FRAC,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_HDMI_CTRL (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_HDMI_CTRL'. */
void GH_DEBUG_TEST_set_HDMI_CTRL(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_HDMI_CTRL'. */
U32  GH_DEBUG_TEST_get_HDMI_CTRL(void);
/*! \brief Writes the bit group 'Hdmi_phy_test_mode' of register 'DEBUG_TEST_HDMI_CTRL'. */
void GH_DEBUG_TEST_set_HDMI_CTRL_Hdmi_phy_test_mode(U8 data);
/*! \brief Reads the bit group 'Hdmi_phy_test_mode' of register 'DEBUG_TEST_HDMI_CTRL'. */
U8   GH_DEBUG_TEST_get_HDMI_CTRL_Hdmi_phy_test_mode(void);
/*! \brief Writes the bit group 'use_hdmi_phy_clk_v' of register 'DEBUG_TEST_HDMI_CTRL'. */
void GH_DEBUG_TEST_set_HDMI_CTRL_use_hdmi_phy_clk_v(U8 data);
/*! \brief Reads the bit group 'use_hdmi_phy_clk_v' of register 'DEBUG_TEST_HDMI_CTRL'. */
U8   GH_DEBUG_TEST_get_HDMI_CTRL_use_hdmi_phy_clk_v(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_HDMI_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_HDMI_CTRL = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_HDMI_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_TEST_HDMI_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_HDMI_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_HDMI_CTRL);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_HDMI_CTRL] --> 0x%08x\n",
                        REG_DEBUG_TEST_HDMI_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_HDMI_CTRL_Hdmi_phy_test_mode(U8 data)
{
    GH_DEBUG_TEST_HDMI_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_HDMI_CTRL;
    d.bitc.hdmi_phy_test_mode = data;
    *(volatile U32 *)REG_DEBUG_TEST_HDMI_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_HDMI_CTRL_Hdmi_phy_test_mode] <-- 0x%08x\n",
                        REG_DEBUG_TEST_HDMI_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_HDMI_CTRL_Hdmi_phy_test_mode(void)
{
    GH_DEBUG_TEST_HDMI_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_HDMI_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_HDMI_CTRL_Hdmi_phy_test_mode] --> 0x%08x\n",
                        REG_DEBUG_TEST_HDMI_CTRL,value);
    #endif
    return tmp_value.bitc.hdmi_phy_test_mode;
}
GH_INLINE void GH_DEBUG_TEST_set_HDMI_CTRL_use_hdmi_phy_clk_v(U8 data)
{
    GH_DEBUG_TEST_HDMI_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_HDMI_CTRL;
    d.bitc.use_hdmi_phy_clk_v = data;
    *(volatile U32 *)REG_DEBUG_TEST_HDMI_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_HDMI_CTRL_use_hdmi_phy_clk_v] <-- 0x%08x\n",
                        REG_DEBUG_TEST_HDMI_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_HDMI_CTRL_use_hdmi_phy_clk_v(void)
{
    GH_DEBUG_TEST_HDMI_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_HDMI_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_HDMI_CTRL_use_hdmi_phy_clk_v] --> 0x%08x\n",
                        REG_DEBUG_TEST_HDMI_CTRL,value);
    #endif
    return tmp_value.bitc.use_hdmi_phy_clk_v;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_SD48 (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_SCALER_SD48'. */
void GH_DEBUG_TEST_set_SCALER_SD48(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_SCALER_SD48'. */
U32  GH_DEBUG_TEST_get_SCALER_SD48(void);
/*! \brief Writes the bit group 'Div' of register 'DEBUG_TEST_SCALER_SD48'. */
void GH_DEBUG_TEST_set_SCALER_SD48_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'DEBUG_TEST_SCALER_SD48'. */
U16  GH_DEBUG_TEST_get_SCALER_SD48_Div(void);
/*! \brief Writes the bit group 'SDCLK_delay' of register 'DEBUG_TEST_SCALER_SD48'. */
void GH_DEBUG_TEST_set_SCALER_SD48_SDCLK_delay(U8 data);
/*! \brief Reads the bit group 'SDCLK_delay' of register 'DEBUG_TEST_SCALER_SD48'. */
U8   GH_DEBUG_TEST_get_SCALER_SD48_SDCLK_delay(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_SCALER_SD48(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_SD48 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_SD48] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_SD48,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_SD48(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_SD48);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_SD48] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_SD48,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_SD48_Div(U16 data)
{
    GH_DEBUG_TEST_SCALER_SD48_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_SD48;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_SD48 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_SD48_Div] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_SD48,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_SD48_Div(void)
{
    GH_DEBUG_TEST_SCALER_SD48_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_SD48);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_SD48_Div] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_SD48,value);
    #endif
    return tmp_value.bitc.div;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_SD48_SDCLK_delay(U8 data)
{
    GH_DEBUG_TEST_SCALER_SD48_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_SD48;
    d.bitc.sdclk_delay = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_SD48 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_SD48_SDCLK_delay] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_SD48,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SCALER_SD48_SDCLK_delay(void)
{
    GH_DEBUG_TEST_SCALER_SD48_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_SD48);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_SD48_SDCLK_delay] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_SD48,value);
    #endif
    return tmp_value.bitc.sdclk_delay;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_VIDEO_CTRL (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
U32  GH_DEBUG_TEST_get_PLL_VIDEO_CTRL(void);
/*! \brief Writes the bit group 'WriteEnable' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_WriteEnable(U8 data);
/*! \brief Reads the bit group 'WriteEnable' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_WriteEnable(void);
/*! \brief Writes the bit group 'BYPASS' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_BYPASS(U8 data);
/*! \brief Reads the bit group 'BYPASS' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_BYPASS(void);
/*! \brief Writes the bit group 'Mode' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_Mode(U8 data);
/*! \brief Reads the bit group 'Mode' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_Mode(void);
/*! \brief Writes the bit group 'reset' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_reset(U8 data);
/*! \brief Reads the bit group 'reset' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_reset(void);
/*! \brief Writes the bit group 'PowerDown' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_PowerDown(U8 data);
/*! \brief Reads the bit group 'PowerDown' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_PowerDown(void);
/*! \brief Writes the bit group 'HalfVCO' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_HalfVCO(U8 data);
/*! \brief Reads the bit group 'HalfVCO' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_HalfVCO(void);
/*! \brief Writes the bit group 'Tristate' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_Tristate(U8 data);
/*! \brief Reads the bit group 'Tristate' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_Tristate(void);
/*! \brief Writes the bit group 'pll_tout_async' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_pll_tout_async(U8 data);
/*! \brief Reads the bit group 'pll_tout_async' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_pll_tout_async(void);
/*! \brief Writes the bit group 'SDIV' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_SDIV(U8 data);
/*! \brief Reads the bit group 'SDIV' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_SDIV(void);
/*! \brief Writes the bit group 'SOUT' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_SOUT(U8 data);
/*! \brief Reads the bit group 'SOUT' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_SOUT(void);
/*! \brief Writes the bit group 'pll_lock' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_pll_lock(U8 data);
/*! \brief Reads the bit group 'pll_lock' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_pll_lock(void);
/*! \brief Writes the bit group 'gclk_vo' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_gclk_vo(U8 data);
/*! \brief Reads the bit group 'gclk_vo' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_gclk_vo(void);
/*! \brief Writes the bit group 'INTPROG' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_INTPROG(U8 data);
/*! \brief Reads the bit group 'INTPROG' of register 'DEBUG_TEST_PLL_VIDEO_CTRL'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_INTPROG(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_VIDEO_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_WriteEnable(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL;
    d.bitc.writeenable = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_WriteEnable] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_WriteEnable(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_WriteEnable] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.writeenable;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_BYPASS(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL;
    d.bitc.bypass = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_BYPASS] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_BYPASS(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_BYPASS] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.bypass;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_Mode(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL;
    d.bitc.mode = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_Mode] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_Mode(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_Mode] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.mode;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_reset(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL;
    d.bitc.reset = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_reset] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_reset(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_reset] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.reset;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_PowerDown(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL;
    d.bitc.powerdown = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_PowerDown] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_PowerDown(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_PowerDown] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.powerdown;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_HalfVCO(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL;
    d.bitc.halfvco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_HalfVCO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_HalfVCO(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_HalfVCO] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.halfvco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_Tristate(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL;
    d.bitc.tristate = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_Tristate] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_Tristate(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_Tristate] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.tristate;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_pll_tout_async(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL;
    d.bitc.pll_tout_async = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_pll_tout_async] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_pll_tout_async(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_pll_tout_async] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.pll_tout_async;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_SDIV(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL;
    d.bitc.sdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_SDIV] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_SDIV(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_SDIV] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.sdiv;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_SOUT(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL;
    d.bitc.sout = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_SOUT] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_SOUT(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_SOUT] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.sout;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_pll_lock(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL;
    d.bitc.pll_lock = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_pll_lock] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_pll_lock(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_pll_lock] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.pll_lock;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_gclk_vo(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL;
    d.bitc.gclk_vo = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_gclk_vo] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_gclk_vo(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_gclk_vo] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.gclk_vo;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_INTPROG(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL;
    d.bitc.intprog = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_INTPROG] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_INTPROG(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_INTPROG] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.intprog;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_VIDEO_FRAC (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_VIDEO_FRAC'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_FRAC(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_VIDEO_FRAC'. */
U32  GH_DEBUG_TEST_get_PLL_VIDEO_FRAC(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_FRAC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_FRAC = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_FRAC] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_FRAC,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_VIDEO_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_FRAC);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_FRAC] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_FRAC,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_VIDEO (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_SCALER_VIDEO'. */
void GH_DEBUG_TEST_set_SCALER_VIDEO(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_SCALER_VIDEO'. */
U32  GH_DEBUG_TEST_get_SCALER_VIDEO(void);
/*! \brief Writes the bit group 'Div' of register 'DEBUG_TEST_SCALER_VIDEO'. */
void GH_DEBUG_TEST_set_SCALER_VIDEO_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'DEBUG_TEST_SCALER_VIDEO'. */
U16  GH_DEBUG_TEST_get_SCALER_VIDEO_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_VIDEO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_VIDEO(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_VIDEO] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO_Div(U16 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_VIDEO_Div] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_VIDEO_Div(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_VIDEO_Div] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_SENSOR_CTRL (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_SENSOR_CTRL'. */
void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_SENSOR_CTRL'. */
U32  GH_DEBUG_TEST_get_PLL_SENSOR_CTRL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_SENSOR_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_SENSOR_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_SENSOR_CTRL] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_SENSOR_FRAC (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_SENSOR_FRAC'. */
void GH_DEBUG_TEST_set_PLL_SENSOR_FRAC(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_SENSOR_FRAC'. */
U32  GH_DEBUG_TEST_get_PLL_SENSOR_FRAC(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_FRAC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_FRAC = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_SENSOR_FRAC] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_FRAC,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_SENSOR_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_FRAC);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_SENSOR_FRAC] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_FRAC,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_LOCK (read)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TEST_PLL_LOCK'. */
U32  GH_DEBUG_TEST_get_PLL_LOCK(void);
/*! \brief Reads the bit group 'PLL_VIDEO2' of register 'DEBUG_TEST_PLL_LOCK'. */
U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_VIDEO2(void);
/*! \brief Reads the bit group 'PLL_VIDEO' of register 'DEBUG_TEST_PLL_LOCK'. */
U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_VIDEO(void);
/*! \brief Reads the bit group 'PLL_USB' of register 'DEBUG_TEST_PLL_LOCK'. */
U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_USB(void);
/*! \brief Reads the bit group 'PLL_SENSOR' of register 'DEBUG_TEST_PLL_LOCK'. */
U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_SENSOR(void);
/*! \brief Reads the bit group 'PLL_IDSP' of register 'DEBUG_TEST_PLL_LOCK'. */
U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_IDSP(void);
/*! \brief Reads the bit group 'PLL_DDR' of register 'DEBUG_TEST_PLL_LOCK'. */
U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_DDR(void);
/*! \brief Reads the bit group 'PLL_CORE' of register 'DEBUG_TEST_PLL_LOCK'. */
U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_CORE(void);
/*! \brief Reads the bit group 'PLL_AUDIO' of register 'DEBUG_TEST_PLL_LOCK'. */
U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_AUDIO(void);
/*! \brief Reads the bit group 'PLL_HDMI' of register 'DEBUG_TEST_PLL_LOCK'. */
U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_HDMI(void);
/*! \brief Reads the bit group 'PLL_VIN' of register 'DEBUG_TEST_PLL_LOCK'. */
U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_VIN(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_LOCK(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_LOCK] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_LOCK,value);
    #endif
    return value;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_VIDEO2(void)
{
    GH_DEBUG_TEST_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_LOCK_PLL_VIDEO2] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_video2;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_VIDEO(void)
{
    GH_DEBUG_TEST_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_LOCK_PLL_VIDEO] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_video;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_USB(void)
{
    GH_DEBUG_TEST_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_LOCK_PLL_USB] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_usb;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_SENSOR(void)
{
    GH_DEBUG_TEST_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_LOCK_PLL_SENSOR] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_sensor;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_IDSP(void)
{
    GH_DEBUG_TEST_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_LOCK_PLL_IDSP] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_idsp;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_DDR(void)
{
    GH_DEBUG_TEST_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_LOCK_PLL_DDR] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_ddr;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_CORE(void)
{
    GH_DEBUG_TEST_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_LOCK_PLL_CORE] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_core;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_AUDIO(void)
{
    GH_DEBUG_TEST_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_LOCK_PLL_AUDIO] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_audio;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_HDMI(void)
{
    GH_DEBUG_TEST_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_LOCK_PLL_HDMI] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_hdmi;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_VIN(void)
{
    GH_DEBUG_TEST_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_LOCK_PLL_VIN] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.pll_vin;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_SENSOR_POST (read/write)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_SCALER_SENSOR_POST'. */
void GH_DEBUG_TEST_set_SCALER_SENSOR_POST(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_SCALER_SENSOR_POST'. */
U32  GH_DEBUG_TEST_get_SCALER_SENSOR_POST(void);
/*! \brief Writes the bit group 'Div' of register 'DEBUG_TEST_SCALER_SENSOR_POST'. */
void GH_DEBUG_TEST_set_SCALER_SENSOR_POST_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'DEBUG_TEST_SCALER_SENSOR_POST'. */
U16  GH_DEBUG_TEST_get_SCALER_SENSOR_POST_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_SCALER_SENSOR_POST(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_POST = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_SENSOR_POST] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_SENSOR_POST,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_SENSOR_POST(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_POST);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_SENSOR_POST] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_SENSOR_POST,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_SENSOR_POST_Div(U16 data)
{
    GH_DEBUG_TEST_SCALER_SENSOR_POST_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_POST;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_POST = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_SENSOR_POST_Div] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_SENSOR_POST,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_SENSOR_POST_Div(void)
{
    GH_DEBUG_TEST_SCALER_SENSOR_POST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_POST);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_SENSOR_POST_Div] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_SENSOR_POST,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SYS_CONFIG (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_SYS_CONFIG'. */
U32  GH_DEBUG_TEST_get_SYS_CONFIG(void);
/*! \brief Writes the bit group 'BootMedia' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_BootMedia(U8 data);
/*! \brief Reads the bit group 'BootMedia' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_BootMedia(void);
/*! \brief Writes the bit group 'clock' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_clock(U8 data);
/*! \brief Reads the bit group 'clock' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_clock(void);
/*! \brief Writes the bit group 'grst' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_grst(U8 data);
/*! \brief Reads the bit group 'grst' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_grst(void);
/*! \brief Writes the bit group 'page_size' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_page_size(U8 data);
/*! \brief Reads the bit group 'page_size' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_page_size(void);
/*! \brief Writes the bit group 'read' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_read(U8 data);
/*! \brief Reads the bit group 'read' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_read(void);
/*! \brief Writes the bit group 'enet' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_enet(U8 data);
/*! \brief Reads the bit group 'enet' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_enet(void);
/*! \brief Writes the bit group 'Boot_Bypass' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_Boot_Bypass(U8 data);
/*! \brief Reads the bit group 'Boot_Bypass' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_Boot_Bypass(void);
/*! \brief Writes the bit group 'fastboot' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_fastboot(U8 data);
/*! \brief Reads the bit group 'fastboot' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_fastboot(void);
/*! \brief Writes the bit group 'IO_Flash_boot' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_IO_Flash_boot(U8 data);
/*! \brief Reads the bit group 'IO_Flash_boot' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_IO_Flash_boot(void);
/*! \brief Writes the bit group 'SD_BOOT' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_SD_BOOT(U8 data);
/*! \brief Reads the bit group 'SD_BOOT' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_SD_BOOT(void);
/*! \brief Writes the bit group 'EMA_SEL' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_EMA_SEL(U8 data);
/*! \brief Reads the bit group 'EMA_SEL' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_EMA_SEL(void);
/*! \brief Writes the bit group 'lock_mode' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_lock_mode(U8 data);
/*! \brief Reads the bit group 'lock_mode' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_lock_mode(void);
/*! \brief Writes the bit group 'grst_l' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_grst_l(U8 data);
/*! \brief Reads the bit group 'grst_l' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_grst_l(void);
/*! \brief Writes the bit group 'RMII_SEL' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_RMII_SEL(U8 data);
/*! \brief Reads the bit group 'RMII_SEL' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_RMII_SEL(void);
/*! \brief Writes the bit group 'spi_boot' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_spi_boot(U8 data);
/*! \brief Reads the bit group 'spi_boot' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_spi_boot(void);
/*! \brief Writes the bit group 'hif_en' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_hif_en(U8 data);
/*! \brief Reads the bit group 'hif_en' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_hif_en(void);
/*! \brief Writes the bit group 'FREE' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_FREE(U8 data);
/*! \brief Reads the bit group 'FREE' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_FREE(void);
/*! \brief Writes the bit group 'hif_type' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_hif_type(U8 data);
/*! \brief Reads the bit group 'hif_type' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_hif_type(void);
/*! \brief Writes the bit group 'rdy_pl' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_rdy_pl(U8 data);
/*! \brief Reads the bit group 'rdy_pl' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_rdy_pl(void);
/*! \brief Writes the bit group 'rct_ahb_hif_secure_mode' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_rct_ahb_hif_secure_mode(U8 data);
/*! \brief Reads the bit group 'rct_ahb_hif_secure_mode' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_rct_ahb_hif_secure_mode(void);
/*! \brief Writes the bit group 'usbp' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_usbp(U8 data);
/*! \brief Reads the bit group 'usbp' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_usbp(void);
/*! \brief Writes the bit group 'ref_clk_is_24Mhz' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_ref_clk_is_24Mhz(U8 data);
/*! \brief Reads the bit group 'ref_clk_is_24Mhz' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_ref_clk_is_24Mhz(void);
/*! \brief Writes the bit group 'rct_bira_efuse_disable' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_rct_bira_efuse_disable(U8 data);
/*! \brief Reads the bit group 'rct_bira_efuse_disable' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_rct_bira_efuse_disable(void);
/*! \brief Writes the bit group 'hardcoded' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_hardcoded(U8 data);
/*! \brief Reads the bit group 'hardcoded' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_hardcoded(void);
/*! \brief Writes the bit group 'source' of register 'DEBUG_TEST_SYS_CONFIG'. */
void GH_DEBUG_TEST_set_SYS_CONFIG_source(U8 data);
/*! \brief Reads the bit group 'source' of register 'DEBUG_TEST_SYS_CONFIG'. */
U8   GH_DEBUG_TEST_get_SYS_CONFIG_source(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_SYS_CONFIG(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_BootMedia(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.bootmedia = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_BootMedia] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_BootMedia(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_BootMedia] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.bootmedia;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_clock(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.clock = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_clock] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_clock(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_clock] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.clock;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_grst(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.grst = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_grst] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_grst(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_grst] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.grst;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_page_size(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.page_size = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_page_size] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_page_size(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_page_size] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.page_size;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_read(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.read = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_read] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_read(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_read] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.read;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_enet(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.enet = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_enet] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_enet(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_enet] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.enet;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_Boot_Bypass(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.boot_bypass = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_Boot_Bypass] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_Boot_Bypass(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_Boot_Bypass] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.boot_bypass;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_fastboot(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.fastboot = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_fastboot] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_fastboot(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_fastboot] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.fastboot;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_IO_Flash_boot(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.io_flash_boot = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_IO_Flash_boot] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_IO_Flash_boot(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_IO_Flash_boot] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.io_flash_boot;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_SD_BOOT(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.sd_boot = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_SD_BOOT] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_SD_BOOT(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_SD_BOOT] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.sd_boot;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_EMA_SEL(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.ema_sel = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_EMA_SEL] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_EMA_SEL(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_EMA_SEL] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.ema_sel;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_lock_mode(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.lock_mode = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_lock_mode] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_lock_mode(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_lock_mode] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.lock_mode;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_grst_l(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.grst_l = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_grst_l] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_grst_l(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_grst_l] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.grst_l;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_RMII_SEL(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.rmii_sel = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_RMII_SEL] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_RMII_SEL(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_RMII_SEL] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.rmii_sel;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_spi_boot(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.spi_boot = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_spi_boot] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_spi_boot(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_spi_boot] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.spi_boot;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_hif_en(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.hif_en = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_hif_en] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_hif_en(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_hif_en] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.hif_en;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_FREE(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.free = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_FREE] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_FREE(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_FREE] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.free;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_hif_type(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.hif_type = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_hif_type] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_hif_type(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_hif_type] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.hif_type;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_rdy_pl(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.rdy_pl = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_rdy_pl] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_rdy_pl(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_rdy_pl] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.rdy_pl;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_rct_ahb_hif_secure_mode(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.rct_ahb_hif_secure_mode = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_rct_ahb_hif_secure_mode] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_rct_ahb_hif_secure_mode(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_rct_ahb_hif_secure_mode] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.rct_ahb_hif_secure_mode;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_usbp(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.usbp = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_usbp] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_usbp(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_usbp] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.usbp;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_ref_clk_is_24Mhz(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.ref_clk_is_24mhz = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_ref_clk_is_24Mhz] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_ref_clk_is_24Mhz(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_ref_clk_is_24Mhz] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.ref_clk_is_24mhz;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_rct_bira_efuse_disable(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.rct_bira_efuse_disable = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_rct_bira_efuse_disable] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_rct_bira_efuse_disable(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_rct_bira_efuse_disable] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.rct_bira_efuse_disable;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_hardcoded(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.hardcoded = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_hardcoded] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_hardcoded(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_hardcoded] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.hardcoded;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_source(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG;
    d.bitc.source = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SYS_CONFIG_source] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_source(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SYS_CONFIG_source] --> 0x%08x\n",
                        REG_DEBUG_TEST_SYS_CONFIG,value);
    #endif
    return tmp_value.bitc.source;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_UART (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_CG_UART'. */
void GH_DEBUG_TEST_set_CG_UART(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_CG_UART'. */
U32  GH_DEBUG_TEST_get_CG_UART(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_CG_UART(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CG_UART = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CG_UART] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CG_UART,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_UART(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_UART);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CG_UART] --> 0x%08x\n",
                        REG_DEBUG_TEST_CG_UART,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_SSI (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_CG_SSI'. */
void GH_DEBUG_TEST_set_CG_SSI(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_CG_SSI'. */
U32  GH_DEBUG_TEST_get_CG_SSI(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_CG_SSI(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CG_SSI = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CG_SSI] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CG_SSI,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_SSI(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_SSI);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CG_SSI] --> 0x%08x\n",
                        REG_DEBUG_TEST_CG_SSI,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_MOTOR (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_CG_MOTOR'. */
void GH_DEBUG_TEST_set_CG_MOTOR(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_CG_MOTOR'. */
U32  GH_DEBUG_TEST_get_CG_MOTOR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_CG_MOTOR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CG_MOTOR = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CG_MOTOR] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CG_MOTOR,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_MOTOR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_MOTOR);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CG_MOTOR] --> 0x%08x\n",
                        REG_DEBUG_TEST_CG_MOTOR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_IR (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_CG_IR'. */
void GH_DEBUG_TEST_set_CG_IR(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_CG_IR'. */
U32  GH_DEBUG_TEST_get_CG_IR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_CG_IR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CG_IR = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CG_IR] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CG_IR,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_IR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_IR);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CG_IR] --> 0x%08x\n",
                        REG_DEBUG_TEST_CG_IR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_HOST (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_CG_HOST'. */
void GH_DEBUG_TEST_set_CG_HOST(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_CG_HOST'. */
U32  GH_DEBUG_TEST_get_CG_HOST(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_CG_HOST(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CG_HOST = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CG_HOST] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CG_HOST,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_HOST(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_HOST);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CG_HOST] --> 0x%08x\n",
                        REG_DEBUG_TEST_CG_HOST,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_SENSOR_PRE (read/write)                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_SCALER_SENSOR_PRE'. */
void GH_DEBUG_TEST_set_SCALER_SENSOR_PRE(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_SCALER_SENSOR_PRE'. */
U32  GH_DEBUG_TEST_get_SCALER_SENSOR_PRE(void);
/*! \brief Writes the bit group 'Div' of register 'DEBUG_TEST_SCALER_SENSOR_PRE'. */
void GH_DEBUG_TEST_set_SCALER_SENSOR_PRE_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'DEBUG_TEST_SCALER_SENSOR_PRE'. */
U16  GH_DEBUG_TEST_get_SCALER_SENSOR_PRE_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_SCALER_SENSOR_PRE(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_PRE = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_SENSOR_PRE] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_SENSOR_PRE,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_SENSOR_PRE(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_PRE);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_SENSOR_PRE] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_SENSOR_PRE,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_SENSOR_PRE_Div(U16 data)
{
    GH_DEBUG_TEST_SCALER_SENSOR_PRE_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_PRE;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_PRE = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_SENSOR_PRE_Div] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_SENSOR_PRE,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_SENSOR_PRE_Div(void)
{
    GH_DEBUG_TEST_SCALER_SENSOR_PRE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_PRE);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_SENSOR_PRE_Div] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_SENSOR_PRE,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_ANA_PWR (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_ANA_PWR'. */
void GH_DEBUG_TEST_set_ANA_PWR(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_ANA_PWR'. */
U32  GH_DEBUG_TEST_get_ANA_PWR(void);
/*! \brief Writes the bit group 'USBsuspend' of register 'DEBUG_TEST_ANA_PWR'. */
void GH_DEBUG_TEST_set_ANA_PWR_USBsuspend(U8 data);
/*! \brief Reads the bit group 'USBsuspend' of register 'DEBUG_TEST_ANA_PWR'. */
U8   GH_DEBUG_TEST_get_ANA_PWR_USBsuspend(void);
/*! \brief Writes the bit group 'suspendUSBP' of register 'DEBUG_TEST_ANA_PWR'. */
void GH_DEBUG_TEST_set_ANA_PWR_suspendUSBP(U8 data);
/*! \brief Reads the bit group 'suspendUSBP' of register 'DEBUG_TEST_ANA_PWR'. */
U8   GH_DEBUG_TEST_get_ANA_PWR_suspendUSBP(void);
/*! \brief Writes the bit group 'power_controller' of register 'DEBUG_TEST_ANA_PWR'. */
void GH_DEBUG_TEST_set_ANA_PWR_power_controller(U8 data);
/*! \brief Reads the bit group 'power_controller' of register 'DEBUG_TEST_ANA_PWR'. */
U8   GH_DEBUG_TEST_get_ANA_PWR_power_controller(void);
/*! \brief Writes the bit group 'DLLpowerdown' of register 'DEBUG_TEST_ANA_PWR'. */
void GH_DEBUG_TEST_set_ANA_PWR_DLLpowerdown(U8 data);
/*! \brief Reads the bit group 'DLLpowerdown' of register 'DEBUG_TEST_ANA_PWR'. */
U8   GH_DEBUG_TEST_get_ANA_PWR_DLLpowerdown(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_ANA_PWR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_ANA_PWR = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_ANA_PWR] <-- 0x%08x\n",
                        REG_DEBUG_TEST_ANA_PWR,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_ANA_PWR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_ANA_PWR);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_ANA_PWR] --> 0x%08x\n",
                        REG_DEBUG_TEST_ANA_PWR,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_ANA_PWR_USBsuspend(U8 data)
{
    GH_DEBUG_TEST_ANA_PWR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_ANA_PWR;
    d.bitc.usbsuspend = data;
    *(volatile U32 *)REG_DEBUG_TEST_ANA_PWR = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_ANA_PWR_USBsuspend] <-- 0x%08x\n",
                        REG_DEBUG_TEST_ANA_PWR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_ANA_PWR_USBsuspend(void)
{
    GH_DEBUG_TEST_ANA_PWR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_ANA_PWR);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_ANA_PWR_USBsuspend] --> 0x%08x\n",
                        REG_DEBUG_TEST_ANA_PWR,value);
    #endif
    return tmp_value.bitc.usbsuspend;
}
GH_INLINE void GH_DEBUG_TEST_set_ANA_PWR_suspendUSBP(U8 data)
{
    GH_DEBUG_TEST_ANA_PWR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_ANA_PWR;
    d.bitc.suspendusbp = data;
    *(volatile U32 *)REG_DEBUG_TEST_ANA_PWR = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_ANA_PWR_suspendUSBP] <-- 0x%08x\n",
                        REG_DEBUG_TEST_ANA_PWR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_ANA_PWR_suspendUSBP(void)
{
    GH_DEBUG_TEST_ANA_PWR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_ANA_PWR);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_ANA_PWR_suspendUSBP] --> 0x%08x\n",
                        REG_DEBUG_TEST_ANA_PWR,value);
    #endif
    return tmp_value.bitc.suspendusbp;
}
GH_INLINE void GH_DEBUG_TEST_set_ANA_PWR_power_controller(U8 data)
{
    GH_DEBUG_TEST_ANA_PWR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_ANA_PWR;
    d.bitc.power_controller = data;
    *(volatile U32 *)REG_DEBUG_TEST_ANA_PWR = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_ANA_PWR_power_controller] <-- 0x%08x\n",
                        REG_DEBUG_TEST_ANA_PWR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_ANA_PWR_power_controller(void)
{
    GH_DEBUG_TEST_ANA_PWR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_ANA_PWR);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_ANA_PWR_power_controller] --> 0x%08x\n",
                        REG_DEBUG_TEST_ANA_PWR,value);
    #endif
    return tmp_value.bitc.power_controller;
}
GH_INLINE void GH_DEBUG_TEST_set_ANA_PWR_DLLpowerdown(U8 data)
{
    GH_DEBUG_TEST_ANA_PWR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_ANA_PWR;
    d.bitc.dllpowerdown = data;
    *(volatile U32 *)REG_DEBUG_TEST_ANA_PWR = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_ANA_PWR_DLLpowerdown] <-- 0x%08x\n",
                        REG_DEBUG_TEST_ANA_PWR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_ANA_PWR_DLLpowerdown(void)
{
    GH_DEBUG_TEST_ANA_PWR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_ANA_PWR);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_ANA_PWR_DLLpowerdown] --> 0x%08x\n",
                        REG_DEBUG_TEST_ANA_PWR,value);
    #endif
    return tmp_value.bitc.dllpowerdown;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_AUDIO_CTRL (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_AUDIO_CTRL'. */
void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_AUDIO_CTRL'. */
U32  GH_DEBUG_TEST_get_PLL_AUDIO_CTRL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_AUDIO_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_AUDIO_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_AUDIO_CTRL] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_AUDIO_FRAC (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_AUDIO_FRAC'. */
void GH_DEBUG_TEST_set_PLL_AUDIO_FRAC(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_AUDIO_FRAC'. */
U32  GH_DEBUG_TEST_get_PLL_AUDIO_FRAC(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_FRAC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_FRAC = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_AUDIO_FRAC] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_FRAC,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_AUDIO_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_FRAC);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_AUDIO_FRAC] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_FRAC,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_AUDIO (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_SCALER_AUDIO'. */
void GH_DEBUG_TEST_set_SCALER_AUDIO(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_SCALER_AUDIO'. */
U32  GH_DEBUG_TEST_get_SCALER_AUDIO(void);
/*! \brief Writes the bit group 'Div' of register 'DEBUG_TEST_SCALER_AUDIO'. */
void GH_DEBUG_TEST_set_SCALER_AUDIO_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'DEBUG_TEST_SCALER_AUDIO'. */
U16  GH_DEBUG_TEST_get_SCALER_AUDIO_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_SCALER_AUDIO(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_AUDIO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_AUDIO,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_AUDIO(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_AUDIO] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_AUDIO,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_AUDIO_Div(U16 data)
{
    GH_DEBUG_TEST_SCALER_AUDIO_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_AUDIO_Div] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_AUDIO,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_AUDIO_Div(void)
{
    GH_DEBUG_TEST_SCALER_AUDIO_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_AUDIO_Div] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_AUDIO,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_AUDIO_PRE (read/write)                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_SCALER_AUDIO_PRE'. */
void GH_DEBUG_TEST_set_SCALER_AUDIO_PRE(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_SCALER_AUDIO_PRE'. */
U32  GH_DEBUG_TEST_get_SCALER_AUDIO_PRE(void);
/*! \brief Writes the bit group 'Div' of register 'DEBUG_TEST_SCALER_AUDIO_PRE'. */
void GH_DEBUG_TEST_set_SCALER_AUDIO_PRE_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'DEBUG_TEST_SCALER_AUDIO_PRE'. */
U16  GH_DEBUG_TEST_get_SCALER_AUDIO_PRE_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_SCALER_AUDIO_PRE(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO_PRE = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_AUDIO_PRE] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_AUDIO_PRE,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_AUDIO_PRE(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO_PRE);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_AUDIO_PRE] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_AUDIO_PRE,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_AUDIO_PRE_Div(U16 data)
{
    GH_DEBUG_TEST_SCALER_AUDIO_PRE_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO_PRE;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO_PRE = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_AUDIO_PRE_Div] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_AUDIO_PRE,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_AUDIO_PRE_Div(void)
{
    GH_DEBUG_TEST_SCALER_AUDIO_PRE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO_PRE);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_AUDIO_PRE_Div] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_AUDIO_PRE,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SOFT_OR_DLLRESET (read/write)                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_SOFT_OR_DLLRESET'. */
void GH_DEBUG_TEST_set_SOFT_OR_DLLRESET(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_SOFT_OR_DLLRESET'. */
U32  GH_DEBUG_TEST_get_SOFT_OR_DLLRESET(void);
/*! \brief Writes the bit group 'Softreset' of register 'DEBUG_TEST_SOFT_OR_DLLRESET'. */
void GH_DEBUG_TEST_set_SOFT_OR_DLLRESET_Softreset(U8 data);
/*! \brief Reads the bit group 'Softreset' of register 'DEBUG_TEST_SOFT_OR_DLLRESET'. */
U8   GH_DEBUG_TEST_get_SOFT_OR_DLLRESET_Softreset(void);
/*! \brief Writes the bit group 'dll_rst_l' of register 'DEBUG_TEST_SOFT_OR_DLLRESET'. */
void GH_DEBUG_TEST_set_SOFT_OR_DLLRESET_dll_rst_l(U8 data);
/*! \brief Reads the bit group 'dll_rst_l' of register 'DEBUG_TEST_SOFT_OR_DLLRESET'. */
U8   GH_DEBUG_TEST_get_SOFT_OR_DLLRESET_dll_rst_l(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_SOFT_OR_DLLRESET(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SOFT_OR_DLLRESET = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SOFT_OR_DLLRESET] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SOFT_OR_DLLRESET,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_SOFT_OR_DLLRESET(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SOFT_OR_DLLRESET);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SOFT_OR_DLLRESET] --> 0x%08x\n",
                        REG_DEBUG_TEST_SOFT_OR_DLLRESET,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_SOFT_OR_DLLRESET_Softreset(U8 data)
{
    GH_DEBUG_TEST_SOFT_OR_DLLRESET_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SOFT_OR_DLLRESET;
    d.bitc.softreset = data;
    *(volatile U32 *)REG_DEBUG_TEST_SOFT_OR_DLLRESET = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SOFT_OR_DLLRESET_Softreset] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SOFT_OR_DLLRESET,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SOFT_OR_DLLRESET_Softreset(void)
{
    GH_DEBUG_TEST_SOFT_OR_DLLRESET_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SOFT_OR_DLLRESET);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SOFT_OR_DLLRESET_Softreset] --> 0x%08x\n",
                        REG_DEBUG_TEST_SOFT_OR_DLLRESET,value);
    #endif
    return tmp_value.bitc.softreset;
}
GH_INLINE void GH_DEBUG_TEST_set_SOFT_OR_DLLRESET_dll_rst_l(U8 data)
{
    GH_DEBUG_TEST_SOFT_OR_DLLRESET_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SOFT_OR_DLLRESET;
    d.bitc.dll_rst_l = data;
    *(volatile U32 *)REG_DEBUG_TEST_SOFT_OR_DLLRESET = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SOFT_OR_DLLRESET_dll_rst_l] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SOFT_OR_DLLRESET,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SOFT_OR_DLLRESET_dll_rst_l(void)
{
    GH_DEBUG_TEST_SOFT_OR_DLLRESET_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SOFT_OR_DLLRESET);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SOFT_OR_DLLRESET_dll_rst_l] --> 0x%08x\n",
                        REG_DEBUG_TEST_SOFT_OR_DLLRESET,value);
    #endif
    return tmp_value.bitc.dll_rst_l;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_FIO_RESET (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_FIO_RESET'. */
void GH_DEBUG_TEST_set_FIO_RESET(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_FIO_RESET'. */
U32  GH_DEBUG_TEST_get_FIO_RESET(void);
/*! \brief Writes the bit group 'flashreset' of register 'DEBUG_TEST_FIO_RESET'. */
void GH_DEBUG_TEST_set_FIO_RESET_flashreset(U8 data);
/*! \brief Reads the bit group 'flashreset' of register 'DEBUG_TEST_FIO_RESET'. */
U8   GH_DEBUG_TEST_get_FIO_RESET_flashreset(void);
/*! \brief Writes the bit group 'xdreset' of register 'DEBUG_TEST_FIO_RESET'. */
void GH_DEBUG_TEST_set_FIO_RESET_xdreset(U8 data);
/*! \brief Reads the bit group 'xdreset' of register 'DEBUG_TEST_FIO_RESET'. */
U8   GH_DEBUG_TEST_get_FIO_RESET_xdreset(void);
/*! \brief Writes the bit group 'cfreset' of register 'DEBUG_TEST_FIO_RESET'. */
void GH_DEBUG_TEST_set_FIO_RESET_cfreset(U8 data);
/*! \brief Reads the bit group 'cfreset' of register 'DEBUG_TEST_FIO_RESET'. */
U8   GH_DEBUG_TEST_get_FIO_RESET_cfreset(void);
/*! \brief Writes the bit group 'fioreset' of register 'DEBUG_TEST_FIO_RESET'. */
void GH_DEBUG_TEST_set_FIO_RESET_fioreset(U8 data);
/*! \brief Reads the bit group 'fioreset' of register 'DEBUG_TEST_FIO_RESET'. */
U8   GH_DEBUG_TEST_get_FIO_RESET_fioreset(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_FIO_RESET(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_FIO_RESET = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_FIO_RESET] <-- 0x%08x\n",
                        REG_DEBUG_TEST_FIO_RESET,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_FIO_RESET(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_FIO_RESET);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_FIO_RESET] --> 0x%08x\n",
                        REG_DEBUG_TEST_FIO_RESET,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_FIO_RESET_flashreset(U8 data)
{
    GH_DEBUG_TEST_FIO_RESET_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_FIO_RESET;
    d.bitc.flashreset = data;
    *(volatile U32 *)REG_DEBUG_TEST_FIO_RESET = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_FIO_RESET_flashreset] <-- 0x%08x\n",
                        REG_DEBUG_TEST_FIO_RESET,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_FIO_RESET_flashreset(void)
{
    GH_DEBUG_TEST_FIO_RESET_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_FIO_RESET);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_FIO_RESET_flashreset] --> 0x%08x\n",
                        REG_DEBUG_TEST_FIO_RESET,value);
    #endif
    return tmp_value.bitc.flashreset;
}
GH_INLINE void GH_DEBUG_TEST_set_FIO_RESET_xdreset(U8 data)
{
    GH_DEBUG_TEST_FIO_RESET_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_FIO_RESET;
    d.bitc.xdreset = data;
    *(volatile U32 *)REG_DEBUG_TEST_FIO_RESET = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_FIO_RESET_xdreset] <-- 0x%08x\n",
                        REG_DEBUG_TEST_FIO_RESET,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_FIO_RESET_xdreset(void)
{
    GH_DEBUG_TEST_FIO_RESET_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_FIO_RESET);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_FIO_RESET_xdreset] --> 0x%08x\n",
                        REG_DEBUG_TEST_FIO_RESET,value);
    #endif
    return tmp_value.bitc.xdreset;
}
GH_INLINE void GH_DEBUG_TEST_set_FIO_RESET_cfreset(U8 data)
{
    GH_DEBUG_TEST_FIO_RESET_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_FIO_RESET;
    d.bitc.cfreset = data;
    *(volatile U32 *)REG_DEBUG_TEST_FIO_RESET = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_FIO_RESET_cfreset] <-- 0x%08x\n",
                        REG_DEBUG_TEST_FIO_RESET,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_FIO_RESET_cfreset(void)
{
    GH_DEBUG_TEST_FIO_RESET_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_FIO_RESET);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_FIO_RESET_cfreset] --> 0x%08x\n",
                        REG_DEBUG_TEST_FIO_RESET,value);
    #endif
    return tmp_value.bitc.cfreset;
}
GH_INLINE void GH_DEBUG_TEST_set_FIO_RESET_fioreset(U8 data)
{
    GH_DEBUG_TEST_FIO_RESET_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_FIO_RESET;
    d.bitc.fioreset = data;
    *(volatile U32 *)REG_DEBUG_TEST_FIO_RESET = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_FIO_RESET_fioreset] <-- 0x%08x\n",
                        REG_DEBUG_TEST_FIO_RESET,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_FIO_RESET_fioreset(void)
{
    GH_DEBUG_TEST_FIO_RESET_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_FIO_RESET);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_FIO_RESET_fioreset] --> 0x%08x\n",
                        REG_DEBUG_TEST_FIO_RESET,value);
    #endif
    return tmp_value.bitc.fioreset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_WDT_RST_L (read)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TEST_WDT_RST_L'. */
U32  GH_DEBUG_TEST_get_WDT_RST_L(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TEST_get_WDT_RST_L(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_WDT_RST_L);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_WDT_RST_L] --> 0x%08x\n",
                        REG_DEBUG_TEST_WDT_RST_L,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_USB (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_SCALER_USB'. */
void GH_DEBUG_TEST_set_SCALER_USB(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_SCALER_USB'. */
U32  GH_DEBUG_TEST_get_SCALER_USB(void);
/*! \brief Writes the bit group 'Div' of register 'DEBUG_TEST_SCALER_USB'. */
void GH_DEBUG_TEST_set_SCALER_USB_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'DEBUG_TEST_SCALER_USB'. */
U16  GH_DEBUG_TEST_get_SCALER_USB_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_SCALER_USB(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_USB = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_USB] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_USB,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_USB(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_USB);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_USB] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_USB,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_USB_Div(U16 data)
{
    GH_DEBUG_TEST_SCALER_USB_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_USB;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_USB = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_USB_Div] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_USB,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_USB_Div(void)
{
    GH_DEBUG_TEST_SCALER_USB_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_USB);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_USB_Div] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_USB,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CLK_DEBOUNCE (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_CLK_DEBOUNCE'. */
void GH_DEBUG_TEST_set_CLK_DEBOUNCE(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_CLK_DEBOUNCE'. */
U32  GH_DEBUG_TEST_get_CLK_DEBOUNCE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_CLK_DEBOUNCE(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CLK_DEBOUNCE = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CLK_DEBOUNCE] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CLK_DEBOUNCE,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_CLK_DEBOUNCE(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLK_DEBOUNCE);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CLK_DEBOUNCE] --> 0x%08x\n",
                        REG_DEBUG_TEST_CLK_DEBOUNCE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_PWM (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_CG_PWM'. */
void GH_DEBUG_TEST_set_CG_PWM(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_CG_PWM'. */
U32  GH_DEBUG_TEST_get_CG_PWM(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_CG_PWM(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CG_PWM = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CG_PWM] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CG_PWM,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_PWM(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_PWM);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CG_PWM] --> 0x%08x\n",
                        REG_DEBUG_TEST_CG_PWM,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_USBP_CTRL (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_USBP_CTRL'. */
void GH_DEBUG_TEST_set_USBP_CTRL(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_USBP_CTRL'. */
U32  GH_DEBUG_TEST_get_USBP_CTRL(void);
/*! \brief Writes the bit group 'refclkdiv' of register 'DEBUG_TEST_USBP_CTRL'. */
void GH_DEBUG_TEST_set_USBP_CTRL_refclkdiv(U8 data);
/*! \brief Reads the bit group 'refclkdiv' of register 'DEBUG_TEST_USBP_CTRL'. */
U8   GH_DEBUG_TEST_get_USBP_CTRL_refclkdiv(void);
/*! \brief Writes the bit group 'usbphy_reset' of register 'DEBUG_TEST_USBP_CTRL'. */
void GH_DEBUG_TEST_set_USBP_CTRL_usbphy_reset(U8 data);
/*! \brief Reads the bit group 'usbphy_reset' of register 'DEBUG_TEST_USBP_CTRL'. */
U8   GH_DEBUG_TEST_get_USBP_CTRL_usbphy_reset(void);
/*! \brief Writes the bit group 'refclksel' of register 'DEBUG_TEST_USBP_CTRL'. */
void GH_DEBUG_TEST_set_USBP_CTRL_refclksel(U8 data);
/*! \brief Reads the bit group 'refclksel' of register 'DEBUG_TEST_USBP_CTRL'. */
U8   GH_DEBUG_TEST_get_USBP_CTRL_refclksel(void);
/*! \brief Writes the bit group 'commononn' of register 'DEBUG_TEST_USBP_CTRL'. */
void GH_DEBUG_TEST_set_USBP_CTRL_commononn(U8 data);
/*! \brief Reads the bit group 'commononn' of register 'DEBUG_TEST_USBP_CTRL'. */
U8   GH_DEBUG_TEST_get_USBP_CTRL_commononn(void);
/*! \brief Writes the bit group 'compdistune' of register 'DEBUG_TEST_USBP_CTRL'. */
void GH_DEBUG_TEST_set_USBP_CTRL_compdistune(U8 data);
/*! \brief Reads the bit group 'compdistune' of register 'DEBUG_TEST_USBP_CTRL'. */
U8   GH_DEBUG_TEST_get_USBP_CTRL_compdistune(void);
/*! \brief Writes the bit group 'otgtune' of register 'DEBUG_TEST_USBP_CTRL'. */
void GH_DEBUG_TEST_set_USBP_CTRL_otgtune(U8 data);
/*! \brief Reads the bit group 'otgtune' of register 'DEBUG_TEST_USBP_CTRL'. */
U8   GH_DEBUG_TEST_get_USBP_CTRL_otgtune(void);
/*! \brief Writes the bit group 'sqrxtune' of register 'DEBUG_TEST_USBP_CTRL'. */
void GH_DEBUG_TEST_set_USBP_CTRL_sqrxtune(U8 data);
/*! \brief Reads the bit group 'sqrxtune' of register 'DEBUG_TEST_USBP_CTRL'. */
U8   GH_DEBUG_TEST_get_USBP_CTRL_sqrxtune(void);
/*! \brief Writes the bit group 'rxfslstune' of register 'DEBUG_TEST_USBP_CTRL'. */
void GH_DEBUG_TEST_set_USBP_CTRL_rxfslstune(U8 data);
/*! \brief Reads the bit group 'rxfslstune' of register 'DEBUG_TEST_USBP_CTRL'. */
U8   GH_DEBUG_TEST_get_USBP_CTRL_rxfslstune(void);
/*! \brief Writes the bit group 'txpreemphasistune' of register 'DEBUG_TEST_USBP_CTRL'. */
void GH_DEBUG_TEST_set_USBP_CTRL_txpreemphasistune(U8 data);
/*! \brief Reads the bit group 'txpreemphasistune' of register 'DEBUG_TEST_USBP_CTRL'. */
U8   GH_DEBUG_TEST_get_USBP_CTRL_txpreemphasistune(void);
/*! \brief Writes the bit group 'txrisetune' of register 'DEBUG_TEST_USBP_CTRL'. */
void GH_DEBUG_TEST_set_USBP_CTRL_txrisetune(U8 data);
/*! \brief Reads the bit group 'txrisetune' of register 'DEBUG_TEST_USBP_CTRL'. */
U8   GH_DEBUG_TEST_get_USBP_CTRL_txrisetune(void);
/*! \brief Writes the bit group 'txvreftune' of register 'DEBUG_TEST_USBP_CTRL'. */
void GH_DEBUG_TEST_set_USBP_CTRL_txvreftune(U8 data);
/*! \brief Reads the bit group 'txvreftune' of register 'DEBUG_TEST_USBP_CTRL'. */
U8   GH_DEBUG_TEST_get_USBP_CTRL_txvreftune(void);
/*! \brief Writes the bit group 'txhsxvtune' of register 'DEBUG_TEST_USBP_CTRL'. */
void GH_DEBUG_TEST_set_USBP_CTRL_txhsxvtune(U8 data);
/*! \brief Reads the bit group 'txhsxvtune' of register 'DEBUG_TEST_USBP_CTRL'. */
U8   GH_DEBUG_TEST_get_USBP_CTRL_txhsxvtune(void);
/*! \brief Writes the bit group 'ATERESET' of register 'DEBUG_TEST_USBP_CTRL'. */
void GH_DEBUG_TEST_set_USBP_CTRL_ATERESET(U8 data);
/*! \brief Reads the bit group 'ATERESET' of register 'DEBUG_TEST_USBP_CTRL'. */
U8   GH_DEBUG_TEST_get_USBP_CTRL_ATERESET(void);
/*! \brief Writes the bit group 'USBDCsoftreset' of register 'DEBUG_TEST_USBP_CTRL'. */
void GH_DEBUG_TEST_set_USBP_CTRL_USBDCsoftreset(U8 data);
/*! \brief Reads the bit group 'USBDCsoftreset' of register 'DEBUG_TEST_USBP_CTRL'. */
U8   GH_DEBUG_TEST_get_USBP_CTRL_USBDCsoftreset(void);
/*! \brief Writes the bit group 'SLEEPM' of register 'DEBUG_TEST_USBP_CTRL'. */
void GH_DEBUG_TEST_set_USBP_CTRL_SLEEPM(U8 data);
/*! \brief Reads the bit group 'SLEEPM' of register 'DEBUG_TEST_USBP_CTRL'. */
U8   GH_DEBUG_TEST_get_USBP_CTRL_SLEEPM(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USBP_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_USBP_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USBP_CTRL] --> 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_refclkdiv(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL;
    d.bitc.refclkdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USBP_CTRL_refclkdiv] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_refclkdiv(void)
{
    GH_DEBUG_TEST_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USBP_CTRL_refclkdiv] --> 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.refclkdiv;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_usbphy_reset(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL;
    d.bitc.usbphy_reset = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USBP_CTRL_usbphy_reset] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_usbphy_reset(void)
{
    GH_DEBUG_TEST_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USBP_CTRL_usbphy_reset] --> 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.usbphy_reset;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_refclksel(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL;
    d.bitc.refclksel = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USBP_CTRL_refclksel] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_refclksel(void)
{
    GH_DEBUG_TEST_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USBP_CTRL_refclksel] --> 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.refclksel;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_commononn(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL;
    d.bitc.commononn = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USBP_CTRL_commononn] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_commononn(void)
{
    GH_DEBUG_TEST_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USBP_CTRL_commononn] --> 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.commononn;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_compdistune(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL;
    d.bitc.compdistune = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USBP_CTRL_compdistune] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_compdistune(void)
{
    GH_DEBUG_TEST_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USBP_CTRL_compdistune] --> 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.compdistune;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_otgtune(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL;
    d.bitc.otgtune = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USBP_CTRL_otgtune] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_otgtune(void)
{
    GH_DEBUG_TEST_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USBP_CTRL_otgtune] --> 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.otgtune;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_sqrxtune(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL;
    d.bitc.sqrxtune = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USBP_CTRL_sqrxtune] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_sqrxtune(void)
{
    GH_DEBUG_TEST_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USBP_CTRL_sqrxtune] --> 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.sqrxtune;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_rxfslstune(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL;
    d.bitc.rxfslstune = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USBP_CTRL_rxfslstune] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_rxfslstune(void)
{
    GH_DEBUG_TEST_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USBP_CTRL_rxfslstune] --> 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.rxfslstune;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_txpreemphasistune(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL;
    d.bitc.txpreemphasistune = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USBP_CTRL_txpreemphasistune] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_txpreemphasistune(void)
{
    GH_DEBUG_TEST_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USBP_CTRL_txpreemphasistune] --> 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.txpreemphasistune;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_txrisetune(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL;
    d.bitc.txrisetune = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USBP_CTRL_txrisetune] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_txrisetune(void)
{
    GH_DEBUG_TEST_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USBP_CTRL_txrisetune] --> 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.txrisetune;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_txvreftune(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL;
    d.bitc.txvreftune = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USBP_CTRL_txvreftune] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_txvreftune(void)
{
    GH_DEBUG_TEST_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USBP_CTRL_txvreftune] --> 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.txvreftune;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_txhsxvtune(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL;
    d.bitc.txhsxvtune = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USBP_CTRL_txhsxvtune] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_txhsxvtune(void)
{
    GH_DEBUG_TEST_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USBP_CTRL_txhsxvtune] --> 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.txhsxvtune;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_ATERESET(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL;
    d.bitc.atereset = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USBP_CTRL_ATERESET] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_ATERESET(void)
{
    GH_DEBUG_TEST_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USBP_CTRL_ATERESET] --> 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.atereset;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_USBDCsoftreset(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL;
    d.bitc.usbdcsoftreset = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USBP_CTRL_USBDCsoftreset] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_USBDCsoftreset(void)
{
    GH_DEBUG_TEST_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USBP_CTRL_USBDCsoftreset] --> 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.usbdcsoftreset;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_SLEEPM(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL;
    d.bitc.sleepm = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USBP_CTRL_SLEEPM] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_SLEEPM(void)
{
    GH_DEBUG_TEST_USBP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USBP_CTRL_SLEEPM] --> 0x%08x\n",
                        REG_DEBUG_TEST_USBP_CTRL,value);
    #endif
    return tmp_value.bitc.sleepm;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CKEN_VDSP (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_CKEN_VDSP'. */
void GH_DEBUG_TEST_set_CKEN_VDSP(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_CKEN_VDSP'. */
U32  GH_DEBUG_TEST_get_CKEN_VDSP(void);
/*! \brief Writes the bit group 'cken_tsfm' of register 'DEBUG_TEST_CKEN_VDSP'. */
void GH_DEBUG_TEST_set_CKEN_VDSP_cken_tsfm(U8 data);
/*! \brief Reads the bit group 'cken_tsfm' of register 'DEBUG_TEST_CKEN_VDSP'. */
U8   GH_DEBUG_TEST_get_CKEN_VDSP_cken_tsfm(void);
/*! \brief Writes the bit group 'cken_code' of register 'DEBUG_TEST_CKEN_VDSP'. */
void GH_DEBUG_TEST_set_CKEN_VDSP_cken_code(U8 data);
/*! \brief Reads the bit group 'cken_code' of register 'DEBUG_TEST_CKEN_VDSP'. */
U8   GH_DEBUG_TEST_get_CKEN_VDSP_cken_code(void);
/*! \brief Writes the bit group 'cken_smem' of register 'DEBUG_TEST_CKEN_VDSP'. */
void GH_DEBUG_TEST_set_CKEN_VDSP_cken_smem(U8 data);
/*! \brief Reads the bit group 'cken_smem' of register 'DEBUG_TEST_CKEN_VDSP'. */
U8   GH_DEBUG_TEST_get_CKEN_VDSP_cken_smem(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_CKEN_VDSP(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CKEN_VDSP] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CKEN_VDSP,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_CKEN_VDSP(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CKEN_VDSP] --> 0x%08x\n",
                        REG_DEBUG_TEST_CKEN_VDSP,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_CKEN_VDSP_cken_tsfm(U8 data)
{
    GH_DEBUG_TEST_CKEN_VDSP_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP;
    d.bitc.cken_tsfm = data;
    *(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CKEN_VDSP_cken_tsfm] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CKEN_VDSP,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_CKEN_VDSP_cken_tsfm(void)
{
    GH_DEBUG_TEST_CKEN_VDSP_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CKEN_VDSP_cken_tsfm] --> 0x%08x\n",
                        REG_DEBUG_TEST_CKEN_VDSP,value);
    #endif
    return tmp_value.bitc.cken_tsfm;
}
GH_INLINE void GH_DEBUG_TEST_set_CKEN_VDSP_cken_code(U8 data)
{
    GH_DEBUG_TEST_CKEN_VDSP_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP;
    d.bitc.cken_code = data;
    *(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CKEN_VDSP_cken_code] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CKEN_VDSP,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_CKEN_VDSP_cken_code(void)
{
    GH_DEBUG_TEST_CKEN_VDSP_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CKEN_VDSP_cken_code] --> 0x%08x\n",
                        REG_DEBUG_TEST_CKEN_VDSP,value);
    #endif
    return tmp_value.bitc.cken_code;
}
GH_INLINE void GH_DEBUG_TEST_set_CKEN_VDSP_cken_smem(U8 data)
{
    GH_DEBUG_TEST_CKEN_VDSP_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP;
    d.bitc.cken_smem = data;
    *(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CKEN_VDSP_cken_smem] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CKEN_VDSP,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_CKEN_VDSP_cken_smem(void)
{
    GH_DEBUG_TEST_CKEN_VDSP_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CKEN_VDSP_cken_smem] --> 0x%08x\n",
                        REG_DEBUG_TEST_CKEN_VDSP,value);
    #endif
    return tmp_value.bitc.cken_smem;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_DLL0 (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_DLL0'. */
void GH_DEBUG_TEST_set_DLL0(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_DLL0'. */
U32  GH_DEBUG_TEST_get_DLL0(void);
/*! \brief Writes the bit group 'DLL_SEL2' of register 'DEBUG_TEST_DLL0'. */
void GH_DEBUG_TEST_set_DLL0_DLL_SEL2(U8 data);
/*! \brief Reads the bit group 'DLL_SEL2' of register 'DEBUG_TEST_DLL0'. */
U8   GH_DEBUG_TEST_get_DLL0_DLL_SEL2(void);
/*! \brief Writes the bit group 'DLL_SEL1' of register 'DEBUG_TEST_DLL0'. */
void GH_DEBUG_TEST_set_DLL0_DLL_SEL1(U8 data);
/*! \brief Reads the bit group 'DLL_SEL1' of register 'DEBUG_TEST_DLL0'. */
U8   GH_DEBUG_TEST_get_DLL0_DLL_SEL1(void);
/*! \brief Writes the bit group 'DLL_SEL0' of register 'DEBUG_TEST_DLL0'. */
void GH_DEBUG_TEST_set_DLL0_DLL_SEL0(U8 data);
/*! \brief Reads the bit group 'DLL_SEL0' of register 'DEBUG_TEST_DLL0'. */
U8   GH_DEBUG_TEST_get_DLL0_DLL_SEL0(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_DLL0(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_DLL0 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL0] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL0,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_DLL0(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL0);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL0] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL0,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL0_DLL_SEL2(U8 data)
{
    GH_DEBUG_TEST_DLL0_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL0;
    d.bitc.dll_sel2 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL0 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL0_DLL_SEL2] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL0_DLL_SEL2(void)
{
    GH_DEBUG_TEST_DLL0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL0);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL0_DLL_SEL2] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL0,value);
    #endif
    return tmp_value.bitc.dll_sel2;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL0_DLL_SEL1(U8 data)
{
    GH_DEBUG_TEST_DLL0_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL0;
    d.bitc.dll_sel1 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL0 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL0_DLL_SEL1] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL0_DLL_SEL1(void)
{
    GH_DEBUG_TEST_DLL0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL0);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL0_DLL_SEL1] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL0,value);
    #endif
    return tmp_value.bitc.dll_sel1;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL0_DLL_SEL0(U8 data)
{
    GH_DEBUG_TEST_DLL0_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL0;
    d.bitc.dll_sel0 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL0 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL0_DLL_SEL0] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL0_DLL_SEL0(void)
{
    GH_DEBUG_TEST_DLL0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL0);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL0_DLL_SEL0] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL0,value);
    #endif
    return tmp_value.bitc.dll_sel0;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_DLL1 (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_DLL1'. */
void GH_DEBUG_TEST_set_DLL1(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_DLL1'. */
U32  GH_DEBUG_TEST_get_DLL1(void);
/*! \brief Writes the bit group 'DLL_SEL2' of register 'DEBUG_TEST_DLL1'. */
void GH_DEBUG_TEST_set_DLL1_DLL_SEL2(U8 data);
/*! \brief Reads the bit group 'DLL_SEL2' of register 'DEBUG_TEST_DLL1'. */
U8   GH_DEBUG_TEST_get_DLL1_DLL_SEL2(void);
/*! \brief Writes the bit group 'DLL_SEL1' of register 'DEBUG_TEST_DLL1'. */
void GH_DEBUG_TEST_set_DLL1_DLL_SEL1(U8 data);
/*! \brief Reads the bit group 'DLL_SEL1' of register 'DEBUG_TEST_DLL1'. */
U8   GH_DEBUG_TEST_get_DLL1_DLL_SEL1(void);
/*! \brief Writes the bit group 'DLL_SEL0' of register 'DEBUG_TEST_DLL1'. */
void GH_DEBUG_TEST_set_DLL1_DLL_SEL0(U8 data);
/*! \brief Reads the bit group 'DLL_SEL0' of register 'DEBUG_TEST_DLL1'. */
U8   GH_DEBUG_TEST_get_DLL1_DLL_SEL0(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_DLL1(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_DLL1 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL1] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL1,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_DLL1(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL1);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL1] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL1,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL1_DLL_SEL2(U8 data)
{
    GH_DEBUG_TEST_DLL1_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL1;
    d.bitc.dll_sel2 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL1 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL1_DLL_SEL2] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL1_DLL_SEL2(void)
{
    GH_DEBUG_TEST_DLL1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL1);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL1_DLL_SEL2] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL1,value);
    #endif
    return tmp_value.bitc.dll_sel2;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL1_DLL_SEL1(U8 data)
{
    GH_DEBUG_TEST_DLL1_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL1;
    d.bitc.dll_sel1 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL1 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL1_DLL_SEL1] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL1_DLL_SEL1(void)
{
    GH_DEBUG_TEST_DLL1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL1);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL1_DLL_SEL1] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL1,value);
    #endif
    return tmp_value.bitc.dll_sel1;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL1_DLL_SEL0(U8 data)
{
    GH_DEBUG_TEST_DLL1_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL1;
    d.bitc.dll_sel0 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL1 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL1_DLL_SEL0] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL1_DLL_SEL0(void)
{
    GH_DEBUG_TEST_DLL1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL1);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL1_DLL_SEL0] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL1,value);
    #endif
    return tmp_value.bitc.dll_sel0;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_ADC (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_SCALER_ADC'. */
void GH_DEBUG_TEST_set_SCALER_ADC(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_SCALER_ADC'. */
U32  GH_DEBUG_TEST_get_SCALER_ADC(void);
/*! \brief Writes the bit group 'Div' of register 'DEBUG_TEST_SCALER_ADC'. */
void GH_DEBUG_TEST_set_SCALER_ADC_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'DEBUG_TEST_SCALER_ADC'. */
U16  GH_DEBUG_TEST_get_SCALER_ADC_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_SCALER_ADC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_ADC = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_ADC] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_ADC,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_ADC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_ADC);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_ADC] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_ADC,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_ADC_Div(U16 data)
{
    GH_DEBUG_TEST_SCALER_ADC_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_ADC;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_ADC = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_ADC_Div] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_ADC,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_ADC_Div(void)
{
    GH_DEBUG_TEST_SCALER_ADC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_ADC);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_ADC_Div] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_ADC,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_VIDEO_POST (read/write)                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_SCALER_VIDEO_POST'. */
void GH_DEBUG_TEST_set_SCALER_VIDEO_POST(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_SCALER_VIDEO_POST'. */
U32  GH_DEBUG_TEST_get_SCALER_VIDEO_POST(void);
/*! \brief Writes the bit group 'Div' of register 'DEBUG_TEST_SCALER_VIDEO_POST'. */
void GH_DEBUG_TEST_set_SCALER_VIDEO_POST_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'DEBUG_TEST_SCALER_VIDEO_POST'. */
U16  GH_DEBUG_TEST_get_SCALER_VIDEO_POST_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO_POST(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO_POST = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_VIDEO_POST] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO_POST,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_VIDEO_POST(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO_POST);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_VIDEO_POST] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO_POST,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO_POST_Div(U16 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO_POST_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO_POST;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO_POST = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_VIDEO_POST_Div] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO_POST,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_VIDEO_POST_Div(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO_POST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO_POST);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_VIDEO_POST_Div] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO_POST,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CLK_REF_AU_EXTERNAL (read/write)                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_CLK_REF_AU_EXTERNAL'. */
void GH_DEBUG_TEST_set_CLK_REF_AU_EXTERNAL(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_CLK_REF_AU_EXTERNAL'. */
U32  GH_DEBUG_TEST_get_CLK_REF_AU_EXTERNAL(void);
/*! \brief Writes the bit group 'external' of register 'DEBUG_TEST_CLK_REF_AU_EXTERNAL'. */
void GH_DEBUG_TEST_set_CLK_REF_AU_EXTERNAL_external(U8 data);
/*! \brief Reads the bit group 'external' of register 'DEBUG_TEST_CLK_REF_AU_EXTERNAL'. */
U8   GH_DEBUG_TEST_get_CLK_REF_AU_EXTERNAL_external(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_CLK_REF_AU_EXTERNAL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_AU_EXTERNAL = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CLK_REF_AU_EXTERNAL] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CLK_REF_AU_EXTERNAL,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_CLK_REF_AU_EXTERNAL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLK_REF_AU_EXTERNAL);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CLK_REF_AU_EXTERNAL] --> 0x%08x\n",
                        REG_DEBUG_TEST_CLK_REF_AU_EXTERNAL,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_CLK_REF_AU_EXTERNAL_external(U8 data)
{
    GH_DEBUG_TEST_CLK_REF_AU_EXTERNAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_AU_EXTERNAL;
    d.bitc.external = data;
    *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_AU_EXTERNAL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CLK_REF_AU_EXTERNAL_external] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CLK_REF_AU_EXTERNAL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_CLK_REF_AU_EXTERNAL_external(void)
{
    GH_DEBUG_TEST_CLK_REF_AU_EXTERNAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLK_REF_AU_EXTERNAL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CLK_REF_AU_EXTERNAL_external] --> 0x%08x\n",
                        REG_DEBUG_TEST_CLK_REF_AU_EXTERNAL,value);
    #endif
    return tmp_value.bitc.external;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_USE_EXTERNAL_CLK_AU (read/write)                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_USE_EXTERNAL_CLK_AU'. */
void GH_DEBUG_TEST_set_USE_EXTERNAL_CLK_AU(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_USE_EXTERNAL_CLK_AU'. */
U32  GH_DEBUG_TEST_get_USE_EXTERNAL_CLK_AU(void);
/*! \brief Writes the bit group 'external' of register 'DEBUG_TEST_USE_EXTERNAL_CLK_AU'. */
void GH_DEBUG_TEST_set_USE_EXTERNAL_CLK_AU_external(U8 data);
/*! \brief Reads the bit group 'external' of register 'DEBUG_TEST_USE_EXTERNAL_CLK_AU'. */
U8   GH_DEBUG_TEST_get_USE_EXTERNAL_CLK_AU_external(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_USE_EXTERNAL_CLK_AU(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_CLK_AU = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USE_EXTERNAL_CLK_AU] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USE_EXTERNAL_CLK_AU,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_USE_EXTERNAL_CLK_AU(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_CLK_AU);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USE_EXTERNAL_CLK_AU] --> 0x%08x\n",
                        REG_DEBUG_TEST_USE_EXTERNAL_CLK_AU,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_USE_EXTERNAL_CLK_AU_external(U8 data)
{
    GH_DEBUG_TEST_USE_EXTERNAL_CLK_AU_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_CLK_AU;
    d.bitc.external = data;
    *(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_CLK_AU = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USE_EXTERNAL_CLK_AU_external] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USE_EXTERNAL_CLK_AU,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USE_EXTERNAL_CLK_AU_external(void)
{
    GH_DEBUG_TEST_USE_EXTERNAL_CLK_AU_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_CLK_AU);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USE_EXTERNAL_CLK_AU_external] --> 0x%08x\n",
                        REG_DEBUG_TEST_USE_EXTERNAL_CLK_AU,value);
    #endif
    return tmp_value.bitc.external;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL (read/write)                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL'. */
void GH_DEBUG_TEST_set_CLK_REF_VIDEO_EXTERNAL(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL'. */
U32  GH_DEBUG_TEST_get_CLK_REF_VIDEO_EXTERNAL(void);
/*! \brief Writes the bit group 'external' of register 'DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL'. */
void GH_DEBUG_TEST_set_CLK_REF_VIDEO_EXTERNAL_external(U8 data);
/*! \brief Reads the bit group 'external' of register 'DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL'. */
U8   GH_DEBUG_TEST_get_CLK_REF_VIDEO_EXTERNAL_external(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_CLK_REF_VIDEO_EXTERNAL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CLK_REF_VIDEO_EXTERNAL] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_CLK_REF_VIDEO_EXTERNAL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CLK_REF_VIDEO_EXTERNAL] --> 0x%08x\n",
                        REG_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_CLK_REF_VIDEO_EXTERNAL_external(U8 data)
{
    GH_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL;
    d.bitc.external = data;
    *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CLK_REF_VIDEO_EXTERNAL_external] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_CLK_REF_VIDEO_EXTERNAL_external(void)
{
    GH_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CLK_REF_VIDEO_EXTERNAL_external] --> 0x%08x\n",
                        REG_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL,value);
    #endif
    return tmp_value.bitc.external;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_USE_EXTERNAL_VD_CLK (read/write)                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_USE_EXTERNAL_VD_CLK'. */
void GH_DEBUG_TEST_set_USE_EXTERNAL_VD_CLK(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_USE_EXTERNAL_VD_CLK'. */
U32  GH_DEBUG_TEST_get_USE_EXTERNAL_VD_CLK(void);
/*! \brief Writes the bit group 'external' of register 'DEBUG_TEST_USE_EXTERNAL_VD_CLK'. */
void GH_DEBUG_TEST_set_USE_EXTERNAL_VD_CLK_external(U8 data);
/*! \brief Reads the bit group 'external' of register 'DEBUG_TEST_USE_EXTERNAL_VD_CLK'. */
U8   GH_DEBUG_TEST_get_USE_EXTERNAL_VD_CLK_external(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_USE_EXTERNAL_VD_CLK(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD_CLK = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USE_EXTERNAL_VD_CLK] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USE_EXTERNAL_VD_CLK,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_USE_EXTERNAL_VD_CLK(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD_CLK);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USE_EXTERNAL_VD_CLK] --> 0x%08x\n",
                        REG_DEBUG_TEST_USE_EXTERNAL_VD_CLK,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_USE_EXTERNAL_VD_CLK_external(U8 data)
{
    GH_DEBUG_TEST_USE_EXTERNAL_VD_CLK_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD_CLK;
    d.bitc.external = data;
    *(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD_CLK = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USE_EXTERNAL_VD_CLK_external] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USE_EXTERNAL_VD_CLK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USE_EXTERNAL_VD_CLK_external(void)
{
    GH_DEBUG_TEST_USE_EXTERNAL_VD_CLK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD_CLK);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USE_EXTERNAL_VD_CLK_external] --> 0x%08x\n",
                        REG_DEBUG_TEST_USE_EXTERNAL_VD_CLK,value);
    #endif
    return tmp_value.bitc.external;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_USE_CLK_SI_4_CLK_AU (read/write)                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_USE_CLK_SI_4_CLK_AU'. */
void GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_AU(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_USE_CLK_SI_4_CLK_AU'. */
U32  GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_AU(void);
/*! \brief Writes the bit group 'PLLref' of register 'DEBUG_TEST_USE_CLK_SI_4_CLK_AU'. */
void GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_AU_PLLref(U8 data);
/*! \brief Reads the bit group 'PLLref' of register 'DEBUG_TEST_USE_CLK_SI_4_CLK_AU'. */
U8   GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_AU_PLLref(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_AU(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_AU = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_AU] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USE_CLK_SI_4_CLK_AU,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_AU(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_AU);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_AU] --> 0x%08x\n",
                        REG_DEBUG_TEST_USE_CLK_SI_4_CLK_AU,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_AU_PLLref(U8 data)
{
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_AU_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_AU;
    d.bitc.pllref = data;
    *(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_AU = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_AU_PLLref] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USE_CLK_SI_4_CLK_AU,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_AU_PLLref(void)
{
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_AU_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_AU);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_AU_PLLref] --> 0x%08x\n",
                        REG_DEBUG_TEST_USE_CLK_SI_4_CLK_AU,value);
    #endif
    return tmp_value.bitc.pllref;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_USE_CLK_SI_4_CLK_VO (read/write)                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_USE_CLK_SI_4_CLK_VO'. */
void GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_VO(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_USE_CLK_SI_4_CLK_VO'. */
U32  GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_VO(void);
/*! \brief Writes the bit group 'PLLref' of register 'DEBUG_TEST_USE_CLK_SI_4_CLK_VO'. */
void GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_VO_PLLref(U8 data);
/*! \brief Reads the bit group 'PLLref' of register 'DEBUG_TEST_USE_CLK_SI_4_CLK_VO'. */
U8   GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_VO_PLLref(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_VO(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_VO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_VO(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_VO] --> 0x%08x\n",
                        REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_VO_PLLref(U8 data)
{
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO;
    d.bitc.pllref = data;
    *(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_VO_PLLref] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_VO_PLLref(void)
{
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_VO_PLLref] --> 0x%08x\n",
                        REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO,value);
    #endif
    return tmp_value.bitc.pllref;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CLK_SI_INPUT_MODE (read/write)                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_CLK_SI_INPUT_MODE'. */
void GH_DEBUG_TEST_set_CLK_SI_INPUT_MODE(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_CLK_SI_INPUT_MODE'. */
U32  GH_DEBUG_TEST_get_CLK_SI_INPUT_MODE(void);
/*! \brief Writes the bit group 'clk_si' of register 'DEBUG_TEST_CLK_SI_INPUT_MODE'. */
void GH_DEBUG_TEST_set_CLK_SI_INPUT_MODE_clk_si(U8 data);
/*! \brief Reads the bit group 'clk_si' of register 'DEBUG_TEST_CLK_SI_INPUT_MODE'. */
U8   GH_DEBUG_TEST_get_CLK_SI_INPUT_MODE_clk_si(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_CLK_SI_INPUT_MODE(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CLK_SI_INPUT_MODE = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CLK_SI_INPUT_MODE] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CLK_SI_INPUT_MODE,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_CLK_SI_INPUT_MODE(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLK_SI_INPUT_MODE);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CLK_SI_INPUT_MODE] --> 0x%08x\n",
                        REG_DEBUG_TEST_CLK_SI_INPUT_MODE,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_CLK_SI_INPUT_MODE_clk_si(U8 data)
{
    GH_DEBUG_TEST_CLK_SI_INPUT_MODE_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CLK_SI_INPUT_MODE;
    d.bitc.clk_si = data;
    *(volatile U32 *)REG_DEBUG_TEST_CLK_SI_INPUT_MODE = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CLK_SI_INPUT_MODE_clk_si] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CLK_SI_INPUT_MODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_CLK_SI_INPUT_MODE_clk_si(void)
{
    GH_DEBUG_TEST_CLK_SI_INPUT_MODE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLK_SI_INPUT_MODE);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CLK_SI_INPUT_MODE_clk_si] --> 0x%08x\n",
                        REG_DEBUG_TEST_CLK_SI_INPUT_MODE,value);
    #endif
    return tmp_value.bitc.clk_si;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_VIDEO2_CTRL (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_VIDEO2_CTRL'. */
void GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_VIDEO2_CTRL'. */
U32  GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL(void);
/*! \brief Writes the bit group 'pll_lock' of register 'DEBUG_TEST_PLL_VIDEO2_CTRL'. */
void GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL_pll_lock(U8 data);
/*! \brief Reads the bit group 'pll_lock' of register 'DEBUG_TEST_PLL_VIDEO2_CTRL'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL_pll_lock(void);
/*! \brief Writes the bit group 'gclk_vo' of register 'DEBUG_TEST_PLL_VIDEO2_CTRL'. */
void GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL_gclk_vo(U8 data);
/*! \brief Reads the bit group 'gclk_vo' of register 'DEBUG_TEST_PLL_VIDEO2_CTRL'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL_gclk_vo(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO2_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO2_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL_pll_lock(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL;
    d.bitc.pll_lock = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL_pll_lock] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO2_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL_pll_lock(void)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL_pll_lock] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO2_CTRL,value);
    #endif
    return tmp_value.bitc.pll_lock;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL_gclk_vo(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL;
    d.bitc.gclk_vo = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL_gclk_vo] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO2_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL_gclk_vo(void)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL_gclk_vo] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO2_CTRL,value);
    #endif
    return tmp_value.bitc.gclk_vo;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_VIDEO2_FRAC (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_VIDEO2_FRAC'. */
void GH_DEBUG_TEST_set_PLL_VIDEO2_FRAC(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_VIDEO2_FRAC'. */
U32  GH_DEBUG_TEST_get_PLL_VIDEO2_FRAC(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO2_FRAC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_FRAC = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO2_FRAC] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO2_FRAC,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_VIDEO2_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_FRAC);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO2_FRAC] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO2_FRAC,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_VIDEO2 (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_SCALER_VIDEO2'. */
void GH_DEBUG_TEST_set_SCALER_VIDEO2(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_SCALER_VIDEO2'. */
U32  GH_DEBUG_TEST_get_SCALER_VIDEO2(void);
/*! \brief Writes the bit group 'IntegerDiv' of register 'DEBUG_TEST_SCALER_VIDEO2'. */
void GH_DEBUG_TEST_set_SCALER_VIDEO2_IntegerDiv(U16 data);
/*! \brief Reads the bit group 'IntegerDiv' of register 'DEBUG_TEST_SCALER_VIDEO2'. */
U16  GH_DEBUG_TEST_get_SCALER_VIDEO2_IntegerDiv(void);
/*! \brief Writes the bit group 'PrimeDiv' of register 'DEBUG_TEST_SCALER_VIDEO2'. */
void GH_DEBUG_TEST_set_SCALER_VIDEO2_PrimeDiv(U8 data);
/*! \brief Reads the bit group 'PrimeDiv' of register 'DEBUG_TEST_SCALER_VIDEO2'. */
U8   GH_DEBUG_TEST_get_SCALER_VIDEO2_PrimeDiv(void);
/*! \brief Writes the bit group 'DutyCycle' of register 'DEBUG_TEST_SCALER_VIDEO2'. */
void GH_DEBUG_TEST_set_SCALER_VIDEO2_DutyCycle(U8 data);
/*! \brief Reads the bit group 'DutyCycle' of register 'DEBUG_TEST_SCALER_VIDEO2'. */
U8   GH_DEBUG_TEST_get_SCALER_VIDEO2_DutyCycle(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_VIDEO2] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO2,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_VIDEO2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_VIDEO2] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO2,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO2_IntegerDiv(U16 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2;
    d.bitc.integerdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_VIDEO2_IntegerDiv] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO2,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_VIDEO2_IntegerDiv(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_VIDEO2_IntegerDiv] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO2,value);
    #endif
    return tmp_value.bitc.integerdiv;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO2_PrimeDiv(U8 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2;
    d.bitc.primediv = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_VIDEO2_PrimeDiv] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SCALER_VIDEO2_PrimeDiv(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_VIDEO2_PrimeDiv] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO2,value);
    #endif
    return tmp_value.bitc.primediv;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO2_DutyCycle(U8 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2;
    d.bitc.dutycycle = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_VIDEO2_DutyCycle] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SCALER_VIDEO2_DutyCycle(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_VIDEO2_DutyCycle] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO2,value);
    #endif
    return tmp_value.bitc.dutycycle;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_VIDEO2_POST (read/write)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_SCALER_VIDEO2_POST'. */
void GH_DEBUG_TEST_set_SCALER_VIDEO2_POST(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_SCALER_VIDEO2_POST'. */
U32  GH_DEBUG_TEST_get_SCALER_VIDEO2_POST(void);
/*! \brief Writes the bit group 'IntegerDiv' of register 'DEBUG_TEST_SCALER_VIDEO2_POST'. */
void GH_DEBUG_TEST_set_SCALER_VIDEO2_POST_IntegerDiv(U16 data);
/*! \brief Reads the bit group 'IntegerDiv' of register 'DEBUG_TEST_SCALER_VIDEO2_POST'. */
U16  GH_DEBUG_TEST_get_SCALER_VIDEO2_POST_IntegerDiv(void);
/*! \brief Writes the bit group 'PrimeDiv' of register 'DEBUG_TEST_SCALER_VIDEO2_POST'. */
void GH_DEBUG_TEST_set_SCALER_VIDEO2_POST_PrimeDiv(U8 data);
/*! \brief Reads the bit group 'PrimeDiv' of register 'DEBUG_TEST_SCALER_VIDEO2_POST'. */
U8   GH_DEBUG_TEST_get_SCALER_VIDEO2_POST_PrimeDiv(void);
/*! \brief Writes the bit group 'DutyCycle' of register 'DEBUG_TEST_SCALER_VIDEO2_POST'. */
void GH_DEBUG_TEST_set_SCALER_VIDEO2_POST_DutyCycle(U8 data);
/*! \brief Reads the bit group 'DutyCycle' of register 'DEBUG_TEST_SCALER_VIDEO2_POST'. */
U8   GH_DEBUG_TEST_get_SCALER_VIDEO2_POST_DutyCycle(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO2_POST(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_VIDEO2_POST] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO2_POST,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_VIDEO2_POST(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_VIDEO2_POST] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO2_POST,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO2_POST_IntegerDiv(U16 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_POST_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST;
    d.bitc.integerdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_VIDEO2_POST_IntegerDiv] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO2_POST,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_VIDEO2_POST_IntegerDiv(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_POST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_VIDEO2_POST_IntegerDiv] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO2_POST,value);
    #endif
    return tmp_value.bitc.integerdiv;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO2_POST_PrimeDiv(U8 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_POST_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST;
    d.bitc.primediv = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_VIDEO2_POST_PrimeDiv] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO2_POST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SCALER_VIDEO2_POST_PrimeDiv(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_POST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_VIDEO2_POST_PrimeDiv] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO2_POST,value);
    #endif
    return tmp_value.bitc.primediv;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO2_POST_DutyCycle(U8 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_POST_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST;
    d.bitc.dutycycle = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_VIDEO2_POST_DutyCycle] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO2_POST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SCALER_VIDEO2_POST_DutyCycle(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_POST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_VIDEO2_POST_DutyCycle] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_VIDEO2_POST,value);
    #endif
    return tmp_value.bitc.dutycycle;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_USE_CLK_SI_4_CLK_VO2 (read/write)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_USE_CLK_SI_4_CLK_VO2'. */
void GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_VO2(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_USE_CLK_SI_4_CLK_VO2'. */
U32  GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_VO2(void);
/*! \brief Writes the bit group 'PLLref' of register 'DEBUG_TEST_USE_CLK_SI_4_CLK_VO2'. */
void GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_VO2_PLLref(U8 data);
/*! \brief Reads the bit group 'PLLref' of register 'DEBUG_TEST_USE_CLK_SI_4_CLK_VO2'. */
U8   GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_VO2_PLLref(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_VO2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_VO2] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_VO2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_VO2] --> 0x%08x\n",
                        REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_VO2_PLLref(U8 data)
{
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2;
    d.bitc.pllref = data;
    *(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_VO2_PLLref] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_VO2_PLLref(void)
{
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_VO2_PLLref] --> 0x%08x\n",
                        REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2,value);
    #endif
    return tmp_value.bitc.pllref;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_USE_EXTERNAL_VD2_CLK (read/write)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_USE_EXTERNAL_VD2_CLK'. */
void GH_DEBUG_TEST_set_USE_EXTERNAL_VD2_CLK(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_USE_EXTERNAL_VD2_CLK'. */
U32  GH_DEBUG_TEST_get_USE_EXTERNAL_VD2_CLK(void);
/*! \brief Writes the bit group 'external' of register 'DEBUG_TEST_USE_EXTERNAL_VD2_CLK'. */
void GH_DEBUG_TEST_set_USE_EXTERNAL_VD2_CLK_external(U8 data);
/*! \brief Reads the bit group 'external' of register 'DEBUG_TEST_USE_EXTERNAL_VD2_CLK'. */
U8   GH_DEBUG_TEST_get_USE_EXTERNAL_VD2_CLK_external(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_USE_EXTERNAL_VD2_CLK(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD2_CLK = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USE_EXTERNAL_VD2_CLK] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USE_EXTERNAL_VD2_CLK,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_USE_EXTERNAL_VD2_CLK(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD2_CLK);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USE_EXTERNAL_VD2_CLK] --> 0x%08x\n",
                        REG_DEBUG_TEST_USE_EXTERNAL_VD2_CLK,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_USE_EXTERNAL_VD2_CLK_external(U8 data)
{
    GH_DEBUG_TEST_USE_EXTERNAL_VD2_CLK_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD2_CLK;
    d.bitc.external = data;
    *(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD2_CLK = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USE_EXTERNAL_VD2_CLK_external] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USE_EXTERNAL_VD2_CLK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_USE_EXTERNAL_VD2_CLK_external(void)
{
    GH_DEBUG_TEST_USE_EXTERNAL_VD2_CLK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD2_CLK);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USE_EXTERNAL_VD2_CLK_external] --> 0x%08x\n",
                        REG_DEBUG_TEST_USE_EXTERNAL_VD2_CLK,value);
    #endif
    return tmp_value.bitc.external;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL (read/write)                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL'. */
void GH_DEBUG_TEST_set_CLK_REF_VIDEO2_EXTERNAL(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL'. */
U32  GH_DEBUG_TEST_get_CLK_REF_VIDEO2_EXTERNAL(void);
/*! \brief Writes the bit group 'external' of register 'DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL'. */
void GH_DEBUG_TEST_set_CLK_REF_VIDEO2_EXTERNAL_external(U8 data);
/*! \brief Reads the bit group 'external' of register 'DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL'. */
U8   GH_DEBUG_TEST_get_CLK_REF_VIDEO2_EXTERNAL_external(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_CLK_REF_VIDEO2_EXTERNAL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CLK_REF_VIDEO2_EXTERNAL] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_CLK_REF_VIDEO2_EXTERNAL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CLK_REF_VIDEO2_EXTERNAL] --> 0x%08x\n",
                        REG_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_CLK_REF_VIDEO2_EXTERNAL_external(U8 data)
{
    GH_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL;
    d.bitc.external = data;
    *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CLK_REF_VIDEO2_EXTERNAL_external] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_CLK_REF_VIDEO2_EXTERNAL_external(void)
{
    GH_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CLK_REF_VIDEO2_EXTERNAL_external] --> 0x%08x\n",
                        REG_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL,value);
    #endif
    return tmp_value.bitc.external;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_DDR_CTRL (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_DDR_CTRL'. */
void GH_DEBUG_TEST_set_PLL_DDR_CTRL(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_DDR_CTRL'. */
U32  GH_DEBUG_TEST_get_PLL_DDR_CTRL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_DDR_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_DDR_CTRL = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_DDR_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_DDR_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_DDR_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_DDR_CTRL);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_DDR_CTRL] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_DDR_CTRL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_DDR_FRAC (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_DDR_FRAC'. */
void GH_DEBUG_TEST_set_PLL_DDR_FRAC(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_DDR_FRAC'. */
U32  GH_DEBUG_TEST_get_PLL_DDR_FRAC(void);
/*! \brief Writes the bit group 'fraction' of register 'DEBUG_TEST_PLL_DDR_FRAC'. */
void GH_DEBUG_TEST_set_PLL_DDR_FRAC_fraction(U16 data);
/*! \brief Reads the bit group 'fraction' of register 'DEBUG_TEST_PLL_DDR_FRAC'. */
U16  GH_DEBUG_TEST_get_PLL_DDR_FRAC_fraction(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_DDR_FRAC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_DDR_FRAC = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_DDR_FRAC] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_DDR_FRAC,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_DDR_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_DDR_FRAC);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_DDR_FRAC] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_DDR_FRAC,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_DDR_FRAC_fraction(U16 data)
{
    GH_DEBUG_TEST_PLL_DDR_FRAC_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_DDR_FRAC;
    d.bitc.fraction = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_DDR_FRAC = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_DDR_FRAC_fraction] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_DDR_FRAC,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_PLL_DDR_FRAC_fraction(void)
{
    GH_DEBUG_TEST_PLL_DDR_FRAC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_DDR_FRAC);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_DDR_FRAC_fraction] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_DDR_FRAC,value);
    #endif
    return tmp_value.bitc.fraction;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_IDSP_CTRL (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_IDSP_CTRL'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_IDSP_CTRL'. */
U32  GH_DEBUG_TEST_get_PLL_IDSP_CTRL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_IDSP_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_IDSP_FRAC (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_IDSP_FRAC'. */
void GH_DEBUG_TEST_set_PLL_IDSP_FRAC(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_IDSP_FRAC'. */
U32  GH_DEBUG_TEST_get_PLL_IDSP_FRAC(void);
/*! \brief Writes the bit group 'fraction' of register 'DEBUG_TEST_PLL_IDSP_FRAC'. */
void GH_DEBUG_TEST_set_PLL_IDSP_FRAC_fraction(U16 data);
/*! \brief Reads the bit group 'fraction' of register 'DEBUG_TEST_PLL_IDSP_FRAC'. */
U16  GH_DEBUG_TEST_get_PLL_IDSP_FRAC_fraction(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_FRAC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_FRAC = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_FRAC] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_FRAC,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_IDSP_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_FRAC);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_FRAC] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_FRAC,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_FRAC_fraction(U16 data)
{
    GH_DEBUG_TEST_PLL_IDSP_FRAC_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_FRAC;
    d.bitc.fraction = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_FRAC = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_FRAC_fraction] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_FRAC,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_PLL_IDSP_FRAC_fraction(void)
{
    GH_DEBUG_TEST_PLL_IDSP_FRAC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_FRAC);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_FRAC_fraction] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_FRAC,value);
    #endif
    return tmp_value.bitc.fraction;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_SSI2 (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_CG_SSI2'. */
void GH_DEBUG_TEST_set_CG_SSI2(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_CG_SSI2'. */
U32  GH_DEBUG_TEST_get_CG_SSI2(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_CG_SSI2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CG_SSI2 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CG_SSI2] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CG_SSI2,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_SSI2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_SSI2);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CG_SSI2] --> 0x%08x\n",
                        REG_DEBUG_TEST_CG_SSI2,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_LVDS_LVCMOS (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_LVDS_LVCMOS'. */
void GH_DEBUG_TEST_set_LVDS_LVCMOS(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_LVDS_LVCMOS'. */
U32  GH_DEBUG_TEST_get_LVDS_LVCMOS(void);
/*! \brief Writes the bit group 'lvcoms_sd' of register 'DEBUG_TEST_LVDS_LVCMOS'. */
void GH_DEBUG_TEST_set_LVDS_LVCMOS_lvcoms_sd(U16 data);
/*! \brief Reads the bit group 'lvcoms_sd' of register 'DEBUG_TEST_LVDS_LVCMOS'. */
U16  GH_DEBUG_TEST_get_LVDS_LVCMOS_lvcoms_sd(void);
/*! \brief Writes the bit group 'lvcmos_spclk' of register 'DEBUG_TEST_LVDS_LVCMOS'. */
void GH_DEBUG_TEST_set_LVDS_LVCMOS_lvcmos_spclk(U8 data);
/*! \brief Reads the bit group 'lvcmos_spclk' of register 'DEBUG_TEST_LVDS_LVCMOS'. */
U8   GH_DEBUG_TEST_get_LVDS_LVCMOS_lvcmos_spclk(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_LVDS_LVCMOS(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_LVDS_LVCMOS = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_LVDS_LVCMOS] <-- 0x%08x\n",
                        REG_DEBUG_TEST_LVDS_LVCMOS,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_LVDS_LVCMOS(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_LVDS_LVCMOS);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_LVDS_LVCMOS] --> 0x%08x\n",
                        REG_DEBUG_TEST_LVDS_LVCMOS,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_LVDS_LVCMOS_lvcoms_sd(U16 data)
{
    GH_DEBUG_TEST_LVDS_LVCMOS_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_LVDS_LVCMOS;
    d.bitc.lvcoms_sd = data;
    *(volatile U32 *)REG_DEBUG_TEST_LVDS_LVCMOS = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_LVDS_LVCMOS_lvcoms_sd] <-- 0x%08x\n",
                        REG_DEBUG_TEST_LVDS_LVCMOS,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_LVDS_LVCMOS_lvcoms_sd(void)
{
    GH_DEBUG_TEST_LVDS_LVCMOS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_LVDS_LVCMOS);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_LVDS_LVCMOS_lvcoms_sd] --> 0x%08x\n",
                        REG_DEBUG_TEST_LVDS_LVCMOS,value);
    #endif
    return tmp_value.bitc.lvcoms_sd;
}
GH_INLINE void GH_DEBUG_TEST_set_LVDS_LVCMOS_lvcmos_spclk(U8 data)
{
    GH_DEBUG_TEST_LVDS_LVCMOS_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_LVDS_LVCMOS;
    d.bitc.lvcmos_spclk = data;
    *(volatile U32 *)REG_DEBUG_TEST_LVDS_LVCMOS = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_LVDS_LVCMOS_lvcmos_spclk] <-- 0x%08x\n",
                        REG_DEBUG_TEST_LVDS_LVCMOS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_LVDS_LVCMOS_lvcmos_spclk(void)
{
    GH_DEBUG_TEST_LVDS_LVCMOS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_LVDS_LVCMOS);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_LVDS_LVCMOS_lvcmos_spclk] --> 0x%08x\n",
                        REG_DEBUG_TEST_LVDS_LVCMOS,value);
    #endif
    return tmp_value.bitc.lvcmos_spclk;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_LVDS_ASYNC (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_LVDS_ASYNC'. */
void GH_DEBUG_TEST_set_LVDS_ASYNC(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_LVDS_ASYNC'. */
U32  GH_DEBUG_TEST_get_LVDS_ASYNC(void);
/*! \brief Writes the bit group 'async_sd' of register 'DEBUG_TEST_LVDS_ASYNC'. */
void GH_DEBUG_TEST_set_LVDS_ASYNC_async_sd(U16 data);
/*! \brief Reads the bit group 'async_sd' of register 'DEBUG_TEST_LVDS_ASYNC'. */
U16  GH_DEBUG_TEST_get_LVDS_ASYNC_async_sd(void);
/*! \brief Writes the bit group 'async_spclk' of register 'DEBUG_TEST_LVDS_ASYNC'. */
void GH_DEBUG_TEST_set_LVDS_ASYNC_async_spclk(U8 data);
/*! \brief Reads the bit group 'async_spclk' of register 'DEBUG_TEST_LVDS_ASYNC'. */
U8   GH_DEBUG_TEST_get_LVDS_ASYNC_async_spclk(void);
/*! \brief Writes the bit group 'lvds_pd' of register 'DEBUG_TEST_LVDS_ASYNC'. */
void GH_DEBUG_TEST_set_LVDS_ASYNC_lvds_pd(U8 data);
/*! \brief Reads the bit group 'lvds_pd' of register 'DEBUG_TEST_LVDS_ASYNC'. */
U8   GH_DEBUG_TEST_get_LVDS_ASYNC_lvds_pd(void);
/*! \brief Writes the bit group 'lvds_ib_ctrl' of register 'DEBUG_TEST_LVDS_ASYNC'. */
void GH_DEBUG_TEST_set_LVDS_ASYNC_lvds_ib_ctrl(U8 data);
/*! \brief Reads the bit group 'lvds_ib_ctrl' of register 'DEBUG_TEST_LVDS_ASYNC'. */
U8   GH_DEBUG_TEST_get_LVDS_ASYNC_lvds_ib_ctrl(void);
/*! \brief Writes the bit group 'lvds_bit_mode' of register 'DEBUG_TEST_LVDS_ASYNC'. */
void GH_DEBUG_TEST_set_LVDS_ASYNC_lvds_bit_mode(U8 data);
/*! \brief Reads the bit group 'lvds_bit_mode' of register 'DEBUG_TEST_LVDS_ASYNC'. */
U8   GH_DEBUG_TEST_get_LVDS_ASYNC_lvds_bit_mode(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_LVDS_ASYNC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_LVDS_ASYNC] <-- 0x%08x\n",
                        REG_DEBUG_TEST_LVDS_ASYNC,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_LVDS_ASYNC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_LVDS_ASYNC] --> 0x%08x\n",
                        REG_DEBUG_TEST_LVDS_ASYNC,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_LVDS_ASYNC_async_sd(U16 data)
{
    GH_DEBUG_TEST_LVDS_ASYNC_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC;
    d.bitc.async_sd = data;
    *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_LVDS_ASYNC_async_sd] <-- 0x%08x\n",
                        REG_DEBUG_TEST_LVDS_ASYNC,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_LVDS_ASYNC_async_sd(void)
{
    GH_DEBUG_TEST_LVDS_ASYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_LVDS_ASYNC_async_sd] --> 0x%08x\n",
                        REG_DEBUG_TEST_LVDS_ASYNC,value);
    #endif
    return tmp_value.bitc.async_sd;
}
GH_INLINE void GH_DEBUG_TEST_set_LVDS_ASYNC_async_spclk(U8 data)
{
    GH_DEBUG_TEST_LVDS_ASYNC_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC;
    d.bitc.async_spclk = data;
    *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_LVDS_ASYNC_async_spclk] <-- 0x%08x\n",
                        REG_DEBUG_TEST_LVDS_ASYNC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_LVDS_ASYNC_async_spclk(void)
{
    GH_DEBUG_TEST_LVDS_ASYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_LVDS_ASYNC_async_spclk] --> 0x%08x\n",
                        REG_DEBUG_TEST_LVDS_ASYNC,value);
    #endif
    return tmp_value.bitc.async_spclk;
}
GH_INLINE void GH_DEBUG_TEST_set_LVDS_ASYNC_lvds_pd(U8 data)
{
    GH_DEBUG_TEST_LVDS_ASYNC_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC;
    d.bitc.lvds_pd = data;
    *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_LVDS_ASYNC_lvds_pd] <-- 0x%08x\n",
                        REG_DEBUG_TEST_LVDS_ASYNC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_LVDS_ASYNC_lvds_pd(void)
{
    GH_DEBUG_TEST_LVDS_ASYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_LVDS_ASYNC_lvds_pd] --> 0x%08x\n",
                        REG_DEBUG_TEST_LVDS_ASYNC,value);
    #endif
    return tmp_value.bitc.lvds_pd;
}
GH_INLINE void GH_DEBUG_TEST_set_LVDS_ASYNC_lvds_ib_ctrl(U8 data)
{
    GH_DEBUG_TEST_LVDS_ASYNC_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC;
    d.bitc.lvds_ib_ctrl = data;
    *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_LVDS_ASYNC_lvds_ib_ctrl] <-- 0x%08x\n",
                        REG_DEBUG_TEST_LVDS_ASYNC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_LVDS_ASYNC_lvds_ib_ctrl(void)
{
    GH_DEBUG_TEST_LVDS_ASYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_LVDS_ASYNC_lvds_ib_ctrl] --> 0x%08x\n",
                        REG_DEBUG_TEST_LVDS_ASYNC,value);
    #endif
    return tmp_value.bitc.lvds_ib_ctrl;
}
GH_INLINE void GH_DEBUG_TEST_set_LVDS_ASYNC_lvds_bit_mode(U8 data)
{
    GH_DEBUG_TEST_LVDS_ASYNC_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC;
    d.bitc.lvds_bit_mode = data;
    *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_LVDS_ASYNC_lvds_bit_mode] <-- 0x%08x\n",
                        REG_DEBUG_TEST_LVDS_ASYNC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_LVDS_ASYNC_lvds_bit_mode(void)
{
    GH_DEBUG_TEST_LVDS_ASYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_LVDS_ASYNC_lvds_bit_mode] --> 0x%08x\n",
                        REG_DEBUG_TEST_LVDS_ASYNC,value);
    #endif
    return tmp_value.bitc.lvds_bit_mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_CORE_CTRL2 (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_CORE_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_CORE_CTRL2(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_CORE_CTRL2'. */
U32  GH_DEBUG_TEST_get_PLL_CORE_CTRL2(void);
/*! \brief Writes the bit group 'Controllability' of register 'DEBUG_TEST_PLL_CORE_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_CORE_CTRL2_Controllability(U16 data);
/*! \brief Reads the bit group 'Controllability' of register 'DEBUG_TEST_PLL_CORE_CTRL2'. */
U16  GH_DEBUG_TEST_get_PLL_CORE_CTRL2_Controllability(void);
/*! \brief Writes the bit group 'Charge' of register 'DEBUG_TEST_PLL_CORE_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_CORE_CTRL2_Charge(U8 data);
/*! \brief Reads the bit group 'Charge' of register 'DEBUG_TEST_PLL_CORE_CTRL2'. */
U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL2_Charge(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL2 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_CORE_CTRL2] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL2,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_CORE_CTRL2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL2);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_CORE_CTRL2] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL2,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL2_Controllability(U16 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL2;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_CORE_CTRL2_Controllability] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_PLL_CORE_CTRL2_Controllability(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_CORE_CTRL2_Controllability] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL2,value);
    #endif
    return tmp_value.bitc.controllability;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL2_Charge(U8 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL2;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_CORE_CTRL2_Charge] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL2_Charge(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_CORE_CTRL2_Charge] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL2,value);
    #endif
    return tmp_value.bitc.charge;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_CORE_CTRL3 (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_CORE_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_CORE_CTRL3(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_CORE_CTRL3'. */
U32  GH_DEBUG_TEST_get_PLL_CORE_CTRL3(void);
/*! \brief Writes the bit group 'VCO' of register 'DEBUG_TEST_PLL_CORE_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_VCO(U8 data);
/*! \brief Reads the bit group 'VCO' of register 'DEBUG_TEST_PLL_CORE_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_VCO(void);
/*! \brief Writes the bit group 'PLL_VCO' of register 'DEBUG_TEST_PLL_CORE_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_PLL_VCO(U8 data);
/*! \brief Reads the bit group 'PLL_VCO' of register 'DEBUG_TEST_PLL_CORE_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_PLL_VCO(void);
/*! \brief Writes the bit group 'Clamp' of register 'DEBUG_TEST_PLL_CORE_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_Clamp(U8 data);
/*! \brief Reads the bit group 'Clamp' of register 'DEBUG_TEST_PLL_CORE_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_Clamp(void);
/*! \brief Writes the bit group 'DSM_dither' of register 'DEBUG_TEST_PLL_CORE_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_DSM_dither(U8 data);
/*! \brief Reads the bit group 'DSM_dither' of register 'DEBUG_TEST_PLL_CORE_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_DSM_dither(void);
/*! \brief Writes the bit group 'DSM_dither_gain' of register 'DEBUG_TEST_PLL_CORE_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_DSM_dither_gain(U8 data);
/*! \brief Reads the bit group 'DSM_dither_gain' of register 'DEBUG_TEST_PLL_CORE_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_DSM_dither_gain(void);
/*! \brief Writes the bit group 'Feedforward' of register 'DEBUG_TEST_PLL_CORE_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_Feedforward(U8 data);
/*! \brief Reads the bit group 'Feedforward' of register 'DEBUG_TEST_PLL_CORE_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_Feedforward(void);
/*! \brief Writes the bit group 'Bias' of register 'DEBUG_TEST_PLL_CORE_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_Bias(U8 data);
/*! \brief Reads the bit group 'Bias' of register 'DEBUG_TEST_PLL_CORE_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_Bias(void);
/*! \brief Writes the bit group 'JDIV' of register 'DEBUG_TEST_PLL_CORE_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_JDIV(U8 data);
/*! \brief Reads the bit group 'JDIV' of register 'DEBUG_TEST_PLL_CORE_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_JDIV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL3(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_CORE_CTRL3] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL3,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_CORE_CTRL3(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_CORE_CTRL3] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL3,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_CORE_CTRL3_VCO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_VCO(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_CORE_CTRL3_VCO] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL3,value);
    #endif
    return tmp_value.bitc.vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_PLL_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_CORE_CTRL3_PLL_VCO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_PLL_VCO(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_CORE_CTRL3_PLL_VCO] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL3,value);
    #endif
    return tmp_value.bitc.pll_vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_Clamp(U8 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_CORE_CTRL3_Clamp] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_Clamp(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_CORE_CTRL3_Clamp] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL3,value);
    #endif
    return tmp_value.bitc.clamp;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_DSM_dither(U8 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_CORE_CTRL3_DSM_dither] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_DSM_dither(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_CORE_CTRL3_DSM_dither] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_DSM_dither_gain(U8 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_CORE_CTRL3_DSM_dither_gain] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_DSM_dither_gain(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_CORE_CTRL3_DSM_dither_gain] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither_gain;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_Feedforward(U8 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_CORE_CTRL3_Feedforward] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_Feedforward(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_CORE_CTRL3_Feedforward] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL3,value);
    #endif
    return tmp_value.bitc.feedforward;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_Bias(U8 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_CORE_CTRL3_Bias] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_Bias(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_CORE_CTRL3_Bias] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL3,value);
    #endif
    return tmp_value.bitc.bias;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_JDIV(U8 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_CORE_CTRL3_JDIV] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_JDIV(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_CORE_CTRL3_JDIV] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_CTRL3,value);
    #endif
    return tmp_value.bitc.jdiv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_IDSP_CTRL2 (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_IDSP_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL2(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_IDSP_CTRL2'. */
U32  GH_DEBUG_TEST_get_PLL_IDSP_CTRL2(void);
/*! \brief Writes the bit group 'Controllability' of register 'DEBUG_TEST_PLL_IDSP_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL2_Controllability(U16 data);
/*! \brief Reads the bit group 'Controllability' of register 'DEBUG_TEST_PLL_IDSP_CTRL2'. */
U16  GH_DEBUG_TEST_get_PLL_IDSP_CTRL2_Controllability(void);
/*! \brief Writes the bit group 'Charge' of register 'DEBUG_TEST_PLL_IDSP_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL2_Charge(U8 data);
/*! \brief Reads the bit group 'Charge' of register 'DEBUG_TEST_PLL_IDSP_CTRL2'. */
U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL2_Charge(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL2 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL2] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL2,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_IDSP_CTRL2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL2);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL2] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL2,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL2_Controllability(U16 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL2;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL2_Controllability] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_PLL_IDSP_CTRL2_Controllability(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL2_Controllability] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL2,value);
    #endif
    return tmp_value.bitc.controllability;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL2_Charge(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL2;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL2_Charge] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL2_Charge(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL2_Charge] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL2,value);
    #endif
    return tmp_value.bitc.charge;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_IDSP_CTRL3 (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_IDSP_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_IDSP_CTRL3'. */
U32  GH_DEBUG_TEST_get_PLL_IDSP_CTRL3(void);
/*! \brief Writes the bit group 'VCO' of register 'DEBUG_TEST_PLL_IDSP_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_VCO(U8 data);
/*! \brief Reads the bit group 'VCO' of register 'DEBUG_TEST_PLL_IDSP_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_VCO(void);
/*! \brief Writes the bit group 'PLL_VCO' of register 'DEBUG_TEST_PLL_IDSP_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_PLL_VCO(U8 data);
/*! \brief Reads the bit group 'PLL_VCO' of register 'DEBUG_TEST_PLL_IDSP_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_PLL_VCO(void);
/*! \brief Writes the bit group 'Clamp' of register 'DEBUG_TEST_PLL_IDSP_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_Clamp(U8 data);
/*! \brief Reads the bit group 'Clamp' of register 'DEBUG_TEST_PLL_IDSP_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_Clamp(void);
/*! \brief Writes the bit group 'DSM_dither' of register 'DEBUG_TEST_PLL_IDSP_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_DSM_dither(U8 data);
/*! \brief Reads the bit group 'DSM_dither' of register 'DEBUG_TEST_PLL_IDSP_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_DSM_dither(void);
/*! \brief Writes the bit group 'DSM_dither_gain' of register 'DEBUG_TEST_PLL_IDSP_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_DSM_dither_gain(U8 data);
/*! \brief Reads the bit group 'DSM_dither_gain' of register 'DEBUG_TEST_PLL_IDSP_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_DSM_dither_gain(void);
/*! \brief Writes the bit group 'Feedforward' of register 'DEBUG_TEST_PLL_IDSP_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_Feedforward(U8 data);
/*! \brief Reads the bit group 'Feedforward' of register 'DEBUG_TEST_PLL_IDSP_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_Feedforward(void);
/*! \brief Writes the bit group 'Bias' of register 'DEBUG_TEST_PLL_IDSP_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_Bias(U8 data);
/*! \brief Reads the bit group 'Bias' of register 'DEBUG_TEST_PLL_IDSP_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_Bias(void);
/*! \brief Writes the bit group 'JDIV' of register 'DEBUG_TEST_PLL_IDSP_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_JDIV(U8 data);
/*! \brief Reads the bit group 'JDIV' of register 'DEBUG_TEST_PLL_IDSP_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_JDIV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL3] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL3,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_IDSP_CTRL3(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL3] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL3,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_VCO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_VCO(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_VCO] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL3,value);
    #endif
    return tmp_value.bitc.vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_PLL_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_PLL_VCO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_PLL_VCO(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_PLL_VCO] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL3,value);
    #endif
    return tmp_value.bitc.pll_vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_Clamp(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_Clamp] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_Clamp(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_Clamp] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL3,value);
    #endif
    return tmp_value.bitc.clamp;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_DSM_dither(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_DSM_dither] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_DSM_dither(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_DSM_dither] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_DSM_dither_gain(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_DSM_dither_gain] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_DSM_dither_gain(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_DSM_dither_gain] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither_gain;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_Feedforward(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_Feedforward] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_Feedforward(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_Feedforward] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL3,value);
    #endif
    return tmp_value.bitc.feedforward;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_Bias(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_Bias] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_Bias(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_Bias] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL3,value);
    #endif
    return tmp_value.bitc.bias;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_JDIV(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_JDIV] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_JDIV(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_JDIV] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL3,value);
    #endif
    return tmp_value.bitc.jdiv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_IDSP_CTRL22 (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_IDSP_CTRL22'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL22(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_IDSP_CTRL22'. */
U32  GH_DEBUG_TEST_get_PLL_IDSP_CTRL22(void);
/*! \brief Writes the bit group 'Controllability' of register 'DEBUG_TEST_PLL_IDSP_CTRL22'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL22_Controllability(U16 data);
/*! \brief Reads the bit group 'Controllability' of register 'DEBUG_TEST_PLL_IDSP_CTRL22'. */
U16  GH_DEBUG_TEST_get_PLL_IDSP_CTRL22_Controllability(void);
/*! \brief Writes the bit group 'Charge' of register 'DEBUG_TEST_PLL_IDSP_CTRL22'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL22_Charge(U8 data);
/*! \brief Reads the bit group 'Charge' of register 'DEBUG_TEST_PLL_IDSP_CTRL22'. */
U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL22_Charge(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL22(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL22 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL22] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL22,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_IDSP_CTRL22(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL22);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL22] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL22,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL22_Controllability(U16 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL22_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL22;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL22 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL22_Controllability] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL22,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_PLL_IDSP_CTRL22_Controllability(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL22_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL22);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL22_Controllability] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL22,value);
    #endif
    return tmp_value.bitc.controllability;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL22_Charge(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL22_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL22;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL22 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL22_Charge] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL22,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL22_Charge(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL22_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL22);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL22_Charge] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL22,value);
    #endif
    return tmp_value.bitc.charge;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_IDSP_CTRL32 (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_IDSP_CTRL32'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_IDSP_CTRL32'. */
U32  GH_DEBUG_TEST_get_PLL_IDSP_CTRL32(void);
/*! \brief Writes the bit group 'VCO' of register 'DEBUG_TEST_PLL_IDSP_CTRL32'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_VCO(U8 data);
/*! \brief Reads the bit group 'VCO' of register 'DEBUG_TEST_PLL_IDSP_CTRL32'. */
U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_VCO(void);
/*! \brief Writes the bit group 'PLL_VCO' of register 'DEBUG_TEST_PLL_IDSP_CTRL32'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_PLL_VCO(U8 data);
/*! \brief Reads the bit group 'PLL_VCO' of register 'DEBUG_TEST_PLL_IDSP_CTRL32'. */
U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_PLL_VCO(void);
/*! \brief Writes the bit group 'Clamp' of register 'DEBUG_TEST_PLL_IDSP_CTRL32'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_Clamp(U8 data);
/*! \brief Reads the bit group 'Clamp' of register 'DEBUG_TEST_PLL_IDSP_CTRL32'. */
U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_Clamp(void);
/*! \brief Writes the bit group 'DSM_dither' of register 'DEBUG_TEST_PLL_IDSP_CTRL32'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_DSM_dither(U8 data);
/*! \brief Reads the bit group 'DSM_dither' of register 'DEBUG_TEST_PLL_IDSP_CTRL32'. */
U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_DSM_dither(void);
/*! \brief Writes the bit group 'DSM_dither_gain' of register 'DEBUG_TEST_PLL_IDSP_CTRL32'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_DSM_dither_gain(U8 data);
/*! \brief Reads the bit group 'DSM_dither_gain' of register 'DEBUG_TEST_PLL_IDSP_CTRL32'. */
U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_DSM_dither_gain(void);
/*! \brief Writes the bit group 'Feedforward' of register 'DEBUG_TEST_PLL_IDSP_CTRL32'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_Feedforward(U8 data);
/*! \brief Reads the bit group 'Feedforward' of register 'DEBUG_TEST_PLL_IDSP_CTRL32'. */
U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_Feedforward(void);
/*! \brief Writes the bit group 'Bias' of register 'DEBUG_TEST_PLL_IDSP_CTRL32'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_Bias(U8 data);
/*! \brief Reads the bit group 'Bias' of register 'DEBUG_TEST_PLL_IDSP_CTRL32'. */
U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_Bias(void);
/*! \brief Writes the bit group 'JDIV' of register 'DEBUG_TEST_PLL_IDSP_CTRL32'. */
void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_JDIV(U8 data);
/*! \brief Reads the bit group 'JDIV' of register 'DEBUG_TEST_PLL_IDSP_CTRL32'. */
U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_JDIV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL32] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL32,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_IDSP_CTRL32(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL32] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL32,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_VCO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL32,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_VCO(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_VCO] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL32,value);
    #endif
    return tmp_value.bitc.vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_PLL_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_PLL_VCO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL32,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_PLL_VCO(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_PLL_VCO] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL32,value);
    #endif
    return tmp_value.bitc.pll_vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_Clamp(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_Clamp] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL32,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_Clamp(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_Clamp] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL32,value);
    #endif
    return tmp_value.bitc.clamp;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_DSM_dither(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_DSM_dither] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL32,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_DSM_dither(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_DSM_dither] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL32,value);
    #endif
    return tmp_value.bitc.dsm_dither;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_DSM_dither_gain(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_DSM_dither_gain] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL32,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_DSM_dither_gain(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_DSM_dither_gain] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL32,value);
    #endif
    return tmp_value.bitc.dsm_dither_gain;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_Feedforward(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_Feedforward] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL32,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_Feedforward(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_Feedforward] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL32,value);
    #endif
    return tmp_value.bitc.feedforward;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_Bias(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_Bias] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL32,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_Bias(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_Bias] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL32,value);
    #endif
    return tmp_value.bitc.bias;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_JDIV(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_JDIV] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL32,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_JDIV(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_JDIV] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_CTRL32,value);
    #endif
    return tmp_value.bitc.jdiv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_CORE_POST (read/write)                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_SCALER_CORE_POST'. */
void GH_DEBUG_TEST_set_SCALER_CORE_POST(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_SCALER_CORE_POST'. */
U32  GH_DEBUG_TEST_get_SCALER_CORE_POST(void);
/*! \brief Writes the bit group 'Div' of register 'DEBUG_TEST_SCALER_CORE_POST'. */
void GH_DEBUG_TEST_set_SCALER_CORE_POST_Div(U8 data);
/*! \brief Reads the bit group 'Div' of register 'DEBUG_TEST_SCALER_CORE_POST'. */
U8   GH_DEBUG_TEST_get_SCALER_CORE_POST_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_SCALER_CORE_POST(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_CORE_POST = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_CORE_POST] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_CORE_POST,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_CORE_POST(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_CORE_POST);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_CORE_POST] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_CORE_POST,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_CORE_POST_Div(U8 data)
{
    GH_DEBUG_TEST_SCALER_CORE_POST_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_CORE_POST;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_CORE_POST = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_CORE_POST_Div] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_CORE_POST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SCALER_CORE_POST_Div(void)
{
    GH_DEBUG_TEST_SCALER_CORE_POST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_CORE_POST);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_CORE_POST_Div] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_CORE_POST,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_SENSOR_CTRL2 (read/write)                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_SENSOR_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL2(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_SENSOR_CTRL2'. */
U32  GH_DEBUG_TEST_get_PLL_SENSOR_CTRL2(void);
/*! \brief Writes the bit group 'Controllability' of register 'DEBUG_TEST_PLL_SENSOR_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL2_Controllability(U16 data);
/*! \brief Reads the bit group 'Controllability' of register 'DEBUG_TEST_PLL_SENSOR_CTRL2'. */
U16  GH_DEBUG_TEST_get_PLL_SENSOR_CTRL2_Controllability(void);
/*! \brief Writes the bit group 'Charge' of register 'DEBUG_TEST_PLL_SENSOR_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL2_Charge(U8 data);
/*! \brief Reads the bit group 'Charge' of register 'DEBUG_TEST_PLL_SENSOR_CTRL2'. */
U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL2_Charge(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL2 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_SENSOR_CTRL2] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL2,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_SENSOR_CTRL2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL2);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_SENSOR_CTRL2] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL2,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL2_Controllability(U16 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL2;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_SENSOR_CTRL2_Controllability] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_PLL_SENSOR_CTRL2_Controllability(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_SENSOR_CTRL2_Controllability] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL2,value);
    #endif
    return tmp_value.bitc.controllability;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL2_Charge(U8 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL2;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_SENSOR_CTRL2_Charge] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL2_Charge(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_SENSOR_CTRL2_Charge] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL2,value);
    #endif
    return tmp_value.bitc.charge;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_SENSOR_CTRL3 (read/write)                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_SENSOR_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_SENSOR_CTRL3'. */
U32  GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3(void);
/*! \brief Writes the bit group 'VCO' of register 'DEBUG_TEST_PLL_SENSOR_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_VCO(U8 data);
/*! \brief Reads the bit group 'VCO' of register 'DEBUG_TEST_PLL_SENSOR_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_VCO(void);
/*! \brief Writes the bit group 'PLL_VCO' of register 'DEBUG_TEST_PLL_SENSOR_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_PLL_VCO(U8 data);
/*! \brief Reads the bit group 'PLL_VCO' of register 'DEBUG_TEST_PLL_SENSOR_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_PLL_VCO(void);
/*! \brief Writes the bit group 'Clamp' of register 'DEBUG_TEST_PLL_SENSOR_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_Clamp(U8 data);
/*! \brief Reads the bit group 'Clamp' of register 'DEBUG_TEST_PLL_SENSOR_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_Clamp(void);
/*! \brief Writes the bit group 'DSM_dither' of register 'DEBUG_TEST_PLL_SENSOR_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_DSM_dither(U8 data);
/*! \brief Reads the bit group 'DSM_dither' of register 'DEBUG_TEST_PLL_SENSOR_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_DSM_dither(void);
/*! \brief Writes the bit group 'DSM_dither_gain' of register 'DEBUG_TEST_PLL_SENSOR_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_DSM_dither_gain(U8 data);
/*! \brief Reads the bit group 'DSM_dither_gain' of register 'DEBUG_TEST_PLL_SENSOR_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_DSM_dither_gain(void);
/*! \brief Writes the bit group 'Feedforward' of register 'DEBUG_TEST_PLL_SENSOR_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_Feedforward(U8 data);
/*! \brief Reads the bit group 'Feedforward' of register 'DEBUG_TEST_PLL_SENSOR_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_Feedforward(void);
/*! \brief Writes the bit group 'Bias' of register 'DEBUG_TEST_PLL_SENSOR_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_Bias(U8 data);
/*! \brief Reads the bit group 'Bias' of register 'DEBUG_TEST_PLL_SENSOR_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_Bias(void);
/*! \brief Writes the bit group 'JDIV' of register 'DEBUG_TEST_PLL_SENSOR_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_JDIV(U8 data);
/*! \brief Reads the bit group 'JDIV' of register 'DEBUG_TEST_PLL_SENSOR_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_JDIV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL3,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL3,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_VCO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_VCO(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_VCO] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL3,value);
    #endif
    return tmp_value.bitc.vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_PLL_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_PLL_VCO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_PLL_VCO(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_PLL_VCO] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL3,value);
    #endif
    return tmp_value.bitc.pll_vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_Clamp(U8 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_Clamp] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_Clamp(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_Clamp] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL3,value);
    #endif
    return tmp_value.bitc.clamp;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_DSM_dither(U8 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_DSM_dither] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_DSM_dither(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_DSM_dither] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_DSM_dither_gain(U8 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_DSM_dither_gain] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_DSM_dither_gain(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_DSM_dither_gain] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither_gain;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_Feedforward(U8 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_Feedforward] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_Feedforward(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_Feedforward] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL3,value);
    #endif
    return tmp_value.bitc.feedforward;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_Bias(U8 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_Bias] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_Bias(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_Bias] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL3,value);
    #endif
    return tmp_value.bitc.bias;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_JDIV(U8 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_JDIV] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_JDIV(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_JDIV] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_CTRL3,value);
    #endif
    return tmp_value.bitc.jdiv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_AUDIO_CTRL2 (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_AUDIO_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL2(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_AUDIO_CTRL2'. */
U32  GH_DEBUG_TEST_get_PLL_AUDIO_CTRL2(void);
/*! \brief Writes the bit group 'Controllability' of register 'DEBUG_TEST_PLL_AUDIO_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL2_Controllability(U16 data);
/*! \brief Reads the bit group 'Controllability' of register 'DEBUG_TEST_PLL_AUDIO_CTRL2'. */
U16  GH_DEBUG_TEST_get_PLL_AUDIO_CTRL2_Controllability(void);
/*! \brief Writes the bit group 'Charge' of register 'DEBUG_TEST_PLL_AUDIO_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL2_Charge(U8 data);
/*! \brief Reads the bit group 'Charge' of register 'DEBUG_TEST_PLL_AUDIO_CTRL2'. */
U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL2_Charge(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL2 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_AUDIO_CTRL2] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL2,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_AUDIO_CTRL2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL2);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_AUDIO_CTRL2] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL2,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL2_Controllability(U16 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL2;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_AUDIO_CTRL2_Controllability] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_PLL_AUDIO_CTRL2_Controllability(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_AUDIO_CTRL2_Controllability] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL2,value);
    #endif
    return tmp_value.bitc.controllability;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL2_Charge(U8 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL2;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_AUDIO_CTRL2_Charge] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL2_Charge(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_AUDIO_CTRL2_Charge] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL2,value);
    #endif
    return tmp_value.bitc.charge;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_AUDIO_CTRL3 (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_AUDIO_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_AUDIO_CTRL3'. */
U32  GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3(void);
/*! \brief Writes the bit group 'VCO' of register 'DEBUG_TEST_PLL_AUDIO_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_VCO(U8 data);
/*! \brief Reads the bit group 'VCO' of register 'DEBUG_TEST_PLL_AUDIO_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_VCO(void);
/*! \brief Writes the bit group 'PLL_VCO' of register 'DEBUG_TEST_PLL_AUDIO_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_PLL_VCO(U8 data);
/*! \brief Reads the bit group 'PLL_VCO' of register 'DEBUG_TEST_PLL_AUDIO_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_PLL_VCO(void);
/*! \brief Writes the bit group 'Clamp' of register 'DEBUG_TEST_PLL_AUDIO_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_Clamp(U8 data);
/*! \brief Reads the bit group 'Clamp' of register 'DEBUG_TEST_PLL_AUDIO_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_Clamp(void);
/*! \brief Writes the bit group 'DSM_dither' of register 'DEBUG_TEST_PLL_AUDIO_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_DSM_dither(U8 data);
/*! \brief Reads the bit group 'DSM_dither' of register 'DEBUG_TEST_PLL_AUDIO_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_DSM_dither(void);
/*! \brief Writes the bit group 'DSM_dither_gain' of register 'DEBUG_TEST_PLL_AUDIO_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_DSM_dither_gain(U8 data);
/*! \brief Reads the bit group 'DSM_dither_gain' of register 'DEBUG_TEST_PLL_AUDIO_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_DSM_dither_gain(void);
/*! \brief Writes the bit group 'Feedforward' of register 'DEBUG_TEST_PLL_AUDIO_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_Feedforward(U8 data);
/*! \brief Reads the bit group 'Feedforward' of register 'DEBUG_TEST_PLL_AUDIO_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_Feedforward(void);
/*! \brief Writes the bit group 'Bias' of register 'DEBUG_TEST_PLL_AUDIO_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_Bias(U8 data);
/*! \brief Reads the bit group 'Bias' of register 'DEBUG_TEST_PLL_AUDIO_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_Bias(void);
/*! \brief Writes the bit group 'JDIV' of register 'DEBUG_TEST_PLL_AUDIO_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_JDIV(U8 data);
/*! \brief Reads the bit group 'JDIV' of register 'DEBUG_TEST_PLL_AUDIO_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_JDIV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL3,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL3,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_VCO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_VCO(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_VCO] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL3,value);
    #endif
    return tmp_value.bitc.vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_PLL_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_PLL_VCO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_PLL_VCO(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_PLL_VCO] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL3,value);
    #endif
    return tmp_value.bitc.pll_vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_Clamp(U8 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_Clamp] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_Clamp(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_Clamp] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL3,value);
    #endif
    return tmp_value.bitc.clamp;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_DSM_dither(U8 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_DSM_dither] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_DSM_dither(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_DSM_dither] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_DSM_dither_gain(U8 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_DSM_dither_gain] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_DSM_dither_gain(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_DSM_dither_gain] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither_gain;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_Feedforward(U8 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_Feedforward] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_Feedforward(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_Feedforward] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL3,value);
    #endif
    return tmp_value.bitc.feedforward;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_Bias(U8 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_Bias] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_Bias(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_Bias] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL3,value);
    #endif
    return tmp_value.bitc.bias;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_JDIV(U8 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_JDIV] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_JDIV(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_JDIV] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_CTRL3,value);
    #endif
    return tmp_value.bitc.jdiv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_VIDEO_CTRL2 (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_VIDEO_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL2(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_VIDEO_CTRL2'. */
U32  GH_DEBUG_TEST_get_PLL_VIDEO_CTRL2(void);
/*! \brief Writes the bit group 'Controllability' of register 'DEBUG_TEST_PLL_VIDEO_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL2_Controllability(U16 data);
/*! \brief Reads the bit group 'Controllability' of register 'DEBUG_TEST_PLL_VIDEO_CTRL2'. */
U16  GH_DEBUG_TEST_get_PLL_VIDEO_CTRL2_Controllability(void);
/*! \brief Writes the bit group 'Charge' of register 'DEBUG_TEST_PLL_VIDEO_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL2_Charge(U8 data);
/*! \brief Reads the bit group 'Charge' of register 'DEBUG_TEST_PLL_VIDEO_CTRL2'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL2_Charge(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL2 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL2] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL2,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_VIDEO_CTRL2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL2);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL2] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL2,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL2_Controllability(U16 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL2;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL2_Controllability] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_PLL_VIDEO_CTRL2_Controllability(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL2_Controllability] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL2,value);
    #endif
    return tmp_value.bitc.controllability;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL2_Charge(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL2;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL2_Charge] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL2_Charge(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL2_Charge] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL2,value);
    #endif
    return tmp_value.bitc.charge;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_VIDEO_CTRL3 (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_VIDEO_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_VIDEO_CTRL3'. */
U32  GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3(void);
/*! \brief Writes the bit group 'VCO' of register 'DEBUG_TEST_PLL_VIDEO_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_VCO(U8 data);
/*! \brief Reads the bit group 'VCO' of register 'DEBUG_TEST_PLL_VIDEO_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_VCO(void);
/*! \brief Writes the bit group 'PLL_VCO' of register 'DEBUG_TEST_PLL_VIDEO_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_PLL_VCO(U8 data);
/*! \brief Reads the bit group 'PLL_VCO' of register 'DEBUG_TEST_PLL_VIDEO_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_PLL_VCO(void);
/*! \brief Writes the bit group 'Clamp' of register 'DEBUG_TEST_PLL_VIDEO_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_Clamp(U8 data);
/*! \brief Reads the bit group 'Clamp' of register 'DEBUG_TEST_PLL_VIDEO_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_Clamp(void);
/*! \brief Writes the bit group 'DSM_dither' of register 'DEBUG_TEST_PLL_VIDEO_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_DSM_dither(U8 data);
/*! \brief Reads the bit group 'DSM_dither' of register 'DEBUG_TEST_PLL_VIDEO_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_DSM_dither(void);
/*! \brief Writes the bit group 'DSM_dither_gain' of register 'DEBUG_TEST_PLL_VIDEO_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_DSM_dither_gain(U8 data);
/*! \brief Reads the bit group 'DSM_dither_gain' of register 'DEBUG_TEST_PLL_VIDEO_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_DSM_dither_gain(void);
/*! \brief Writes the bit group 'Feedforward' of register 'DEBUG_TEST_PLL_VIDEO_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_Feedforward(U8 data);
/*! \brief Reads the bit group 'Feedforward' of register 'DEBUG_TEST_PLL_VIDEO_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_Feedforward(void);
/*! \brief Writes the bit group 'Bias' of register 'DEBUG_TEST_PLL_VIDEO_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_Bias(U8 data);
/*! \brief Reads the bit group 'Bias' of register 'DEBUG_TEST_PLL_VIDEO_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_Bias(void);
/*! \brief Writes the bit group 'JDIV' of register 'DEBUG_TEST_PLL_VIDEO_CTRL3'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_JDIV(U8 data);
/*! \brief Reads the bit group 'JDIV' of register 'DEBUG_TEST_PLL_VIDEO_CTRL3'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_JDIV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL3,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL3,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_VCO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_VCO(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_VCO] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL3,value);
    #endif
    return tmp_value.bitc.vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_PLL_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_PLL_VCO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_PLL_VCO(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_PLL_VCO] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL3,value);
    #endif
    return tmp_value.bitc.pll_vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_Clamp(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_Clamp] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_Clamp(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_Clamp] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL3,value);
    #endif
    return tmp_value.bitc.clamp;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_DSM_dither(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_DSM_dither] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_DSM_dither(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_DSM_dither] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_DSM_dither_gain(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_DSM_dither_gain] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_DSM_dither_gain(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_DSM_dither_gain] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL3,value);
    #endif
    return tmp_value.bitc.dsm_dither_gain;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_Feedforward(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_Feedforward] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_Feedforward(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_Feedforward] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL3,value);
    #endif
    return tmp_value.bitc.feedforward;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_Bias(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_Bias] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_Bias(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_Bias] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL3,value);
    #endif
    return tmp_value.bitc.bias;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_JDIV(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_JDIV] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_JDIV(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_JDIV] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_CTRL3,value);
    #endif
    return tmp_value.bitc.jdiv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_VIDEO2_CTRL2 (read/write)                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_VIDEO2_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL2(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_VIDEO2_CTRL2'. */
U32  GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL2(void);
/*! \brief Writes the bit group 'Controllability' of register 'DEBUG_TEST_PLL_VIDEO2_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL2_Controllability(U16 data);
/*! \brief Reads the bit group 'Controllability' of register 'DEBUG_TEST_PLL_VIDEO2_CTRL2'. */
U16  GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL2_Controllability(void);
/*! \brief Writes the bit group 'Charge' of register 'DEBUG_TEST_PLL_VIDEO2_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL2_Charge(U8 data);
/*! \brief Reads the bit group 'Charge' of register 'DEBUG_TEST_PLL_VIDEO2_CTRL2'. */
U8   GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL2_Charge(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL2 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL2] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO2_CTRL2,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL2);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL2] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO2_CTRL2,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL2_Controllability(U16 data)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL2;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL2_Controllability] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO2_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL2_Controllability(void)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL2_Controllability] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO2_CTRL2,value);
    #endif
    return tmp_value.bitc.controllability;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL2_Charge(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL2;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL2_Charge] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO2_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL2_Charge(void)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL2_Charge] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO2_CTRL2,value);
    #endif
    return tmp_value.bitc.charge;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_USB_CTRL2 (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_USB_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_USB_CTRL2(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_USB_CTRL2'. */
U32  GH_DEBUG_TEST_get_PLL_USB_CTRL2(void);
/*! \brief Writes the bit group 'VCO' of register 'DEBUG_TEST_PLL_USB_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_USB_CTRL2_VCO(U8 data);
/*! \brief Reads the bit group 'VCO' of register 'DEBUG_TEST_PLL_USB_CTRL2'. */
U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_VCO(void);
/*! \brief Writes the bit group 'PLL_VCO' of register 'DEBUG_TEST_PLL_USB_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_USB_CTRL2_PLL_VCO(U8 data);
/*! \brief Reads the bit group 'PLL_VCO' of register 'DEBUG_TEST_PLL_USB_CTRL2'. */
U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_PLL_VCO(void);
/*! \brief Writes the bit group 'Clamp' of register 'DEBUG_TEST_PLL_USB_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_USB_CTRL2_Clamp(U8 data);
/*! \brief Reads the bit group 'Clamp' of register 'DEBUG_TEST_PLL_USB_CTRL2'. */
U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_Clamp(void);
/*! \brief Writes the bit group 'DSM_dither' of register 'DEBUG_TEST_PLL_USB_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_USB_CTRL2_DSM_dither(U8 data);
/*! \brief Reads the bit group 'DSM_dither' of register 'DEBUG_TEST_PLL_USB_CTRL2'. */
U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_DSM_dither(void);
/*! \brief Writes the bit group 'DSM_dither_gain' of register 'DEBUG_TEST_PLL_USB_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_USB_CTRL2_DSM_dither_gain(U8 data);
/*! \brief Reads the bit group 'DSM_dither_gain' of register 'DEBUG_TEST_PLL_USB_CTRL2'. */
U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_DSM_dither_gain(void);
/*! \brief Writes the bit group 'Feedforward' of register 'DEBUG_TEST_PLL_USB_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_USB_CTRL2_Feedforward(U8 data);
/*! \brief Reads the bit group 'Feedforward' of register 'DEBUG_TEST_PLL_USB_CTRL2'. */
U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_Feedforward(void);
/*! \brief Writes the bit group 'Bias' of register 'DEBUG_TEST_PLL_USB_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_USB_CTRL2_Bias(U8 data);
/*! \brief Reads the bit group 'Bias' of register 'DEBUG_TEST_PLL_USB_CTRL2'. */
U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_Bias(void);
/*! \brief Writes the bit group 'JDIV' of register 'DEBUG_TEST_PLL_USB_CTRL2'. */
void GH_DEBUG_TEST_set_PLL_USB_CTRL2_JDIV(U8 data);
/*! \brief Reads the bit group 'JDIV' of register 'DEBUG_TEST_PLL_USB_CTRL2'. */
U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_JDIV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_USB_CTRL2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_USB_CTRL2] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_USB_CTRL2,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_USB_CTRL2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_USB_CTRL2] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_USB_CTRL2,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_USB_CTRL2_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_USB_CTRL2_VCO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_USB_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_VCO(void)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_USB_CTRL2_VCO] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_USB_CTRL2,value);
    #endif
    return tmp_value.bitc.vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_USB_CTRL2_PLL_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_USB_CTRL2_PLL_VCO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_USB_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_PLL_VCO(void)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_USB_CTRL2_PLL_VCO] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_USB_CTRL2,value);
    #endif
    return tmp_value.bitc.pll_vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_USB_CTRL2_Clamp(U8 data)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_USB_CTRL2_Clamp] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_USB_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_Clamp(void)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_USB_CTRL2_Clamp] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_USB_CTRL2,value);
    #endif
    return tmp_value.bitc.clamp;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_USB_CTRL2_DSM_dither(U8 data)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_USB_CTRL2_DSM_dither] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_USB_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_DSM_dither(void)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_USB_CTRL2_DSM_dither] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_USB_CTRL2,value);
    #endif
    return tmp_value.bitc.dsm_dither;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_USB_CTRL2_DSM_dither_gain(U8 data)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_USB_CTRL2_DSM_dither_gain] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_USB_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_DSM_dither_gain(void)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_USB_CTRL2_DSM_dither_gain] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_USB_CTRL2,value);
    #endif
    return tmp_value.bitc.dsm_dither_gain;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_USB_CTRL2_Feedforward(U8 data)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_USB_CTRL2_Feedforward] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_USB_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_Feedforward(void)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_USB_CTRL2_Feedforward] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_USB_CTRL2,value);
    #endif
    return tmp_value.bitc.feedforward;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_USB_CTRL2_Bias(U8 data)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_USB_CTRL2_Bias] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_USB_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_Bias(void)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_USB_CTRL2_Bias] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_USB_CTRL2,value);
    #endif
    return tmp_value.bitc.bias;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_USB_CTRL2_JDIV(U8 data)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2 = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_USB_CTRL2_JDIV] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_USB_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_JDIV(void)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_USB_CTRL2_JDIV] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_USB_CTRL2,value);
    #endif
    return tmp_value.bitc.jdiv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_DDR_CALIB (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_CG_DDR_CALIB'. */
void GH_DEBUG_TEST_set_CG_DDR_CALIB(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_CG_DDR_CALIB'. */
U32  GH_DEBUG_TEST_get_CG_DDR_CALIB(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_CG_DDR_CALIB(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CG_DDR_CALIB = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CG_DDR_CALIB] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CG_DDR_CALIB,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_DDR_CALIB(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_DDR_CALIB);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CG_DDR_CALIB] --> 0x%08x\n",
                        REG_DEBUG_TEST_CG_DDR_CALIB,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_DLL_CTRL_SEL (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_DLL_CTRL_SEL'. */
void GH_DEBUG_TEST_set_DLL_CTRL_SEL(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_DLL_CTRL_SEL'. */
U32  GH_DEBUG_TEST_get_DLL_CTRL_SEL(void);
/*! \brief Writes the bit group 'rct_ddrio_dll_sbc' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_dll_sbc(U16 data);
/*! \brief Reads the bit group 'rct_ddrio_dll_sbc' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
U16  GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_dll_sbc(void);
/*! \brief Writes the bit group 'rct_ddrio_dll_selm' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_dll_selm(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_dll_selm' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_dll_selm(void);
/*! \brief Writes the bit group 'rct_ddrio_single_end' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_single_end(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_single_end' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_single_end(void);
/*! \brief Writes the bit group 'rct_ddrio_pue_dq' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_pue_dq(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_pue_dq' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_pue_dq(void);
/*! \brief Writes the bit group 'rct_ddrio_pde_dq' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_pde_dq(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_pde_dq' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_pde_dq(void);
/*! \brief Writes the bit group 'rct_ddrio_npue_dqs' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_npue_dqs(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_npue_dqs' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_npue_dqs(void);
/*! \brief Writes the bit group 'rct_ddrio_npde_dqs' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_npde_dqs(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_npde_dqs' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_npde_dqs(void);
/*! \brief Writes the bit group 'rct_ddrio_ppde_dqs' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_ppde_dqs(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_ppde_dqs' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_ppde_dqs(void);
/*! \brief Writes the bit group 'rct_ddrio_ppue_dqs' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_ppue_dqs(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_ppue_dqs' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_ppue_dqs(void);
/*! \brief Writes the bit group 'rct_ddrio_cmosrcv' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_cmosrcv(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_cmosrcv' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_cmosrcv(void);
/*! \brief Writes the bit group 'rct_ddrio_pue_cmd' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_pue_cmd(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_pue_cmd' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_pue_cmd(void);
/*! \brief Writes the bit group 'rct_ddrio_pde_cmd' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_pde_cmd(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_pde_cmd' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_pde_cmd(void);
/*! \brief Writes the bit group 'rct_ddrio_npue_dqs2' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_npue_dqs2(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_npue_dqs2' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_npue_dqs2(void);
/*! \brief Writes the bit group 'rct_ddrio_npde_dqs2' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_npde_dqs2(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_npde_dqs2' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_npde_dqs2(void);
/*! \brief Writes the bit group 'rct_ddrio_ppde_dqs2' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_ppde_dqs2(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_ppde_dqs2' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_ppde_dqs2(void);
/*! \brief Writes the bit group 'rct_ddrio_ppue_dqs2' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_ppue_dqs2(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_ppue_dqs2' of register 'DEBUG_TEST_DLL_CTRL_SEL'. */
U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_ppue_dqs2(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_CTRL_SEL] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_DLL_CTRL_SEL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_CTRL_SEL] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_dll_sbc(U16 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_dll_sbc = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_dll_sbc] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_dll_sbc(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_dll_sbc] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_dll_sbc;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_dll_selm(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_dll_selm = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_dll_selm] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_dll_selm(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_dll_selm] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_dll_selm;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_single_end(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_single_end = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_single_end] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_single_end(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_single_end] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_single_end;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_pue_dq(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_pue_dq = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_pue_dq] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_pue_dq(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_pue_dq] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_pue_dq;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_pde_dq(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_pde_dq = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_pde_dq] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_pde_dq(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_pde_dq] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_pde_dq;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_npue_dqs(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_npue_dqs = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_npue_dqs] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_npue_dqs(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_npue_dqs] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_npue_dqs;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_npde_dqs(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_npde_dqs = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_npde_dqs] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_npde_dqs(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_npde_dqs] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_npde_dqs;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_ppde_dqs(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_ppde_dqs = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_ppde_dqs] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_ppde_dqs(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_ppde_dqs] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_ppde_dqs;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_ppue_dqs(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_ppue_dqs = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_ppue_dqs] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_ppue_dqs(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_ppue_dqs] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_ppue_dqs;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_cmosrcv(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_cmosrcv = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_cmosrcv] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_cmosrcv(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_cmosrcv] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_cmosrcv;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_pue_cmd(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_pue_cmd = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_pue_cmd] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_pue_cmd(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_pue_cmd] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_pue_cmd;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_pde_cmd(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_pde_cmd = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_pde_cmd] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_pde_cmd(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_pde_cmd] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_pde_cmd;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_npue_dqs2(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_npue_dqs2 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_npue_dqs2] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_npue_dqs2(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_npue_dqs2] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_npue_dqs2;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_npde_dqs2(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_npde_dqs2 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_npde_dqs2] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_npde_dqs2(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_npde_dqs2] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_npde_dqs2;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_ppde_dqs2(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_ppde_dqs2 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_ppde_dqs2] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_ppde_dqs2(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_ppde_dqs2] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_ppde_dqs2;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_ppue_dqs2(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL;
    d.bitc.rct_ddrio_ppue_dqs2 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_ppue_dqs2] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_ppue_dqs2(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_ppue_dqs2] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_CTRL_SEL,value);
    #endif
    return tmp_value.bitc.rct_ddrio_ppue_dqs2;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_DLL_OCD_BITS (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_DLL_OCD_BITS'. */
void GH_DEBUG_TEST_set_DLL_OCD_BITS(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_DLL_OCD_BITS'. */
U32  GH_DEBUG_TEST_get_DLL_OCD_BITS(void);
/*! \brief Writes the bit group 'rct_ddrio_ddr2' of register 'DEBUG_TEST_DLL_OCD_BITS'. */
void GH_DEBUG_TEST_set_DLL_OCD_BITS_rct_ddrio_ddr2(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_ddr2' of register 'DEBUG_TEST_DLL_OCD_BITS'. */
U8   GH_DEBUG_TEST_get_DLL_OCD_BITS_rct_ddrio_ddr2(void);
/*! \brief Writes the bit group 'rct_ddrio_ocd_cmd' of register 'DEBUG_TEST_DLL_OCD_BITS'. */
void GH_DEBUG_TEST_set_DLL_OCD_BITS_rct_ddrio_ocd_cmd(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_ocd_cmd' of register 'DEBUG_TEST_DLL_OCD_BITS'. */
U8   GH_DEBUG_TEST_get_DLL_OCD_BITS_rct_ddrio_ocd_cmd(void);
/*! \brief Writes the bit group 'rct_ddrio_ocd' of register 'DEBUG_TEST_DLL_OCD_BITS'. */
void GH_DEBUG_TEST_set_DLL_OCD_BITS_rct_ddrio_ocd(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_ocd' of register 'DEBUG_TEST_DLL_OCD_BITS'. */
U8   GH_DEBUG_TEST_get_DLL_OCD_BITS_rct_ddrio_ocd(void);
/*! \brief Writes the bit group 'rct_ddrio_odt' of register 'DEBUG_TEST_DLL_OCD_BITS'. */
void GH_DEBUG_TEST_set_DLL_OCD_BITS_rct_ddrio_odt(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_odt' of register 'DEBUG_TEST_DLL_OCD_BITS'. */
U8   GH_DEBUG_TEST_get_DLL_OCD_BITS_rct_ddrio_odt(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_DLL_OCD_BITS(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_OCD_BITS] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_OCD_BITS,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_DLL_OCD_BITS(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_OCD_BITS] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_OCD_BITS,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_OCD_BITS_rct_ddrio_ddr2(U8 data)
{
    GH_DEBUG_TEST_DLL_OCD_BITS_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS;
    d.bitc.rct_ddrio_ddr2 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_OCD_BITS_rct_ddrio_ddr2] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_OCD_BITS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_OCD_BITS_rct_ddrio_ddr2(void)
{
    GH_DEBUG_TEST_DLL_OCD_BITS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_OCD_BITS_rct_ddrio_ddr2] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_OCD_BITS,value);
    #endif
    return tmp_value.bitc.rct_ddrio_ddr2;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_OCD_BITS_rct_ddrio_ocd_cmd(U8 data)
{
    GH_DEBUG_TEST_DLL_OCD_BITS_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS;
    d.bitc.rct_ddrio_ocd_cmd = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_OCD_BITS_rct_ddrio_ocd_cmd] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_OCD_BITS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_OCD_BITS_rct_ddrio_ocd_cmd(void)
{
    GH_DEBUG_TEST_DLL_OCD_BITS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_OCD_BITS_rct_ddrio_ocd_cmd] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_OCD_BITS,value);
    #endif
    return tmp_value.bitc.rct_ddrio_ocd_cmd;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_OCD_BITS_rct_ddrio_ocd(U8 data)
{
    GH_DEBUG_TEST_DLL_OCD_BITS_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS;
    d.bitc.rct_ddrio_ocd = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_OCD_BITS_rct_ddrio_ocd] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_OCD_BITS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_OCD_BITS_rct_ddrio_ocd(void)
{
    GH_DEBUG_TEST_DLL_OCD_BITS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_OCD_BITS_rct_ddrio_ocd] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_OCD_BITS,value);
    #endif
    return tmp_value.bitc.rct_ddrio_ocd;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_OCD_BITS_rct_ddrio_odt(U8 data)
{
    GH_DEBUG_TEST_DLL_OCD_BITS_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS;
    d.bitc.rct_ddrio_odt = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DLL_OCD_BITS_rct_ddrio_odt] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DLL_OCD_BITS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_OCD_BITS_rct_ddrio_odt(void)
{
    GH_DEBUG_TEST_DLL_OCD_BITS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DLL_OCD_BITS_rct_ddrio_odt] --> 0x%08x\n",
                        REG_DEBUG_TEST_DLL_OCD_BITS,value);
    #endif
    return tmp_value.bitc.rct_ddrio_odt;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_CORE_OBSV (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_CORE_OBSV'. */
void GH_DEBUG_TEST_set_PLL_CORE_OBSV(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_CORE_OBSV'. */
U32  GH_DEBUG_TEST_get_PLL_CORE_OBSV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_OBSV = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_CORE_OBSV] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_OBSV,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_CORE_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_OBSV);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_CORE_OBSV] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_CORE_OBSV,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_IDSP_OBSV (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_IDSP_OBSV'. */
void GH_DEBUG_TEST_set_PLL_IDSP_OBSV(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_IDSP_OBSV'. */
U32  GH_DEBUG_TEST_get_PLL_IDSP_OBSV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_OBSV = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_IDSP_OBSV] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_OBSV,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_IDSP_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_OBSV);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_IDSP_OBSV] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_IDSP_OBSV,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_DDR_OBSV (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_DDR_OBSV'. */
void GH_DEBUG_TEST_set_PLL_DDR_OBSV(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_DDR_OBSV'. */
U32  GH_DEBUG_TEST_get_PLL_DDR_OBSV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_DDR_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_DDR_OBSV = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_DDR_OBSV] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_DDR_OBSV,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_DDR_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_DDR_OBSV);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_DDR_OBSV] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_DDR_OBSV,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_SENSOR_OBSV (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_SENSOR_OBSV'. */
void GH_DEBUG_TEST_set_PLL_SENSOR_OBSV(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_SENSOR_OBSV'. */
U32  GH_DEBUG_TEST_get_PLL_SENSOR_OBSV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_OBSV = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_SENSOR_OBSV] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_OBSV,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_SENSOR_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_OBSV);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_SENSOR_OBSV] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_SENSOR_OBSV,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_AUDIO_OBSV (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_AUDIO_OBSV'. */
void GH_DEBUG_TEST_set_PLL_AUDIO_OBSV(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_AUDIO_OBSV'. */
U32  GH_DEBUG_TEST_get_PLL_AUDIO_OBSV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_OBSV = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_AUDIO_OBSV] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_OBSV,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_AUDIO_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_OBSV);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_AUDIO_OBSV] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_AUDIO_OBSV,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_VIDEO_OBSV (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_VIDEO_OBSV'. */
void GH_DEBUG_TEST_set_PLL_VIDEO_OBSV(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_VIDEO_OBSV'. */
U32  GH_DEBUG_TEST_get_PLL_VIDEO_OBSV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_OBSV = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO_OBSV] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_OBSV,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_VIDEO_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_OBSV);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO_OBSV] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO_OBSV,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_VIDEO2_OBSV (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_PLL_VIDEO2_OBSV'. */
void GH_DEBUG_TEST_set_PLL_VIDEO2_OBSV(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_PLL_VIDEO2_OBSV'. */
U32  GH_DEBUG_TEST_get_PLL_VIDEO2_OBSV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO2_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_OBSV = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_PLL_VIDEO2_OBSV] <-- 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO2_OBSV,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_VIDEO2_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_OBSV);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_PLL_VIDEO2_OBSV] --> 0x%08x\n",
                        REG_DEBUG_TEST_PLL_VIDEO2_OBSV,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_ADC16_CTRL_ADDR (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_ADC16_CTRL_ADDR'. */
void GH_DEBUG_TEST_set_ADC16_CTRL_ADDR(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_ADC16_CTRL_ADDR'. */
U32  GH_DEBUG_TEST_get_ADC16_CTRL_ADDR(void);
/*! \brief Writes the bit group 'adc_power_down' of register 'DEBUG_TEST_ADC16_CTRL_ADDR'. */
void GH_DEBUG_TEST_set_ADC16_CTRL_ADDR_adc_power_down(U8 data);
/*! \brief Reads the bit group 'adc_power_down' of register 'DEBUG_TEST_ADC16_CTRL_ADDR'. */
U8   GH_DEBUG_TEST_get_ADC16_CTRL_ADDR_adc_power_down(void);
/*! \brief Writes the bit group 'adc_clock_select' of register 'DEBUG_TEST_ADC16_CTRL_ADDR'. */
void GH_DEBUG_TEST_set_ADC16_CTRL_ADDR_adc_clock_select(U8 data);
/*! \brief Reads the bit group 'adc_clock_select' of register 'DEBUG_TEST_ADC16_CTRL_ADDR'. */
U8   GH_DEBUG_TEST_get_ADC16_CTRL_ADDR_adc_clock_select(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_ADC16_CTRL_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_ADC16_CTRL_ADDR = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_ADC16_CTRL_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_TEST_ADC16_CTRL_ADDR,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_ADC16_CTRL_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_ADC16_CTRL_ADDR);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_ADC16_CTRL_ADDR] --> 0x%08x\n",
                        REG_DEBUG_TEST_ADC16_CTRL_ADDR,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_ADC16_CTRL_ADDR_adc_power_down(U8 data)
{
    GH_DEBUG_TEST_ADC16_CTRL_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_ADC16_CTRL_ADDR;
    d.bitc.adc_power_down = data;
    *(volatile U32 *)REG_DEBUG_TEST_ADC16_CTRL_ADDR = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_ADC16_CTRL_ADDR_adc_power_down] <-- 0x%08x\n",
                        REG_DEBUG_TEST_ADC16_CTRL_ADDR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_ADC16_CTRL_ADDR_adc_power_down(void)
{
    GH_DEBUG_TEST_ADC16_CTRL_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_ADC16_CTRL_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_ADC16_CTRL_ADDR_adc_power_down] --> 0x%08x\n",
                        REG_DEBUG_TEST_ADC16_CTRL_ADDR,value);
    #endif
    return tmp_value.bitc.adc_power_down;
}
GH_INLINE void GH_DEBUG_TEST_set_ADC16_CTRL_ADDR_adc_clock_select(U8 data)
{
    GH_DEBUG_TEST_ADC16_CTRL_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_ADC16_CTRL_ADDR;
    d.bitc.adc_clock_select = data;
    *(volatile U32 *)REG_DEBUG_TEST_ADC16_CTRL_ADDR = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_ADC16_CTRL_ADDR_adc_clock_select] <-- 0x%08x\n",
                        REG_DEBUG_TEST_ADC16_CTRL_ADDR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_ADC16_CTRL_ADDR_adc_clock_select(void)
{
    GH_DEBUG_TEST_ADC16_CTRL_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_ADC16_CTRL_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_ADC16_CTRL_ADDR_adc_clock_select] --> 0x%08x\n",
                        REG_DEBUG_TEST_ADC16_CTRL_ADDR,value);
    #endif
    return tmp_value.bitc.adc_clock_select;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CLK_REF_SSI_ADDR (read/write)                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_CLK_REF_SSI_ADDR'. */
void GH_DEBUG_TEST_set_CLK_REF_SSI_ADDR(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_CLK_REF_SSI_ADDR'. */
U32  GH_DEBUG_TEST_get_CLK_REF_SSI_ADDR(void);
/*! \brief Writes the bit group 'clk' of register 'DEBUG_TEST_CLK_REF_SSI_ADDR'. */
void GH_DEBUG_TEST_set_CLK_REF_SSI_ADDR_clk(U8 data);
/*! \brief Reads the bit group 'clk' of register 'DEBUG_TEST_CLK_REF_SSI_ADDR'. */
U8   GH_DEBUG_TEST_get_CLK_REF_SSI_ADDR_clk(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_CLK_REF_SSI_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_SSI_ADDR = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CLK_REF_SSI_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CLK_REF_SSI_ADDR,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_CLK_REF_SSI_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLK_REF_SSI_ADDR);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CLK_REF_SSI_ADDR] --> 0x%08x\n",
                        REG_DEBUG_TEST_CLK_REF_SSI_ADDR,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_CLK_REF_SSI_ADDR_clk(U8 data)
{
    GH_DEBUG_TEST_CLK_REF_SSI_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_SSI_ADDR;
    d.bitc.clk = data;
    *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_SSI_ADDR = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CLK_REF_SSI_ADDR_clk] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CLK_REF_SSI_ADDR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_CLK_REF_SSI_ADDR_clk(void)
{
    GH_DEBUG_TEST_CLK_REF_SSI_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLK_REF_SSI_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CLK_REF_SSI_ADDR_clk] --> 0x%08x\n",
                        REG_DEBUG_TEST_CLK_REF_SSI_ADDR,value);
    #endif
    return tmp_value.bitc.clk;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_DVEN (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_CG_DVEN'. */
void GH_DEBUG_TEST_set_CG_DVEN(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_CG_DVEN'. */
U32  GH_DEBUG_TEST_get_CG_DVEN(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_CG_DVEN(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CG_DVEN = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CG_DVEN] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CG_DVEN,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_DVEN(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_DVEN);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CG_DVEN] --> 0x%08x\n",
                        REG_DEBUG_TEST_CG_DVEN,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_MS (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_SCALER_MS'. */
void GH_DEBUG_TEST_set_SCALER_MS(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_SCALER_MS'. */
U32  GH_DEBUG_TEST_get_SCALER_MS(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_SCALER_MS(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_MS = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_MS] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_MS,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_MS(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_MS);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_MS] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_MS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_MS_DELAY_CTRL (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_MS_DELAY_CTRL'. */
void GH_DEBUG_TEST_set_MS_DELAY_CTRL(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_MS_DELAY_CTRL'. */
U32  GH_DEBUG_TEST_get_MS_DELAY_CTRL(void);
/*! \brief Writes the bit group 'delay_sclk' of register 'DEBUG_TEST_MS_DELAY_CTRL'. */
void GH_DEBUG_TEST_set_MS_DELAY_CTRL_delay_sclk(U8 data);
/*! \brief Reads the bit group 'delay_sclk' of register 'DEBUG_TEST_MS_DELAY_CTRL'. */
U8   GH_DEBUG_TEST_get_MS_DELAY_CTRL_delay_sclk(void);
/*! \brief Writes the bit group 'input_delay' of register 'DEBUG_TEST_MS_DELAY_CTRL'. */
void GH_DEBUG_TEST_set_MS_DELAY_CTRL_input_delay(U8 data);
/*! \brief Reads the bit group 'input_delay' of register 'DEBUG_TEST_MS_DELAY_CTRL'. */
U8   GH_DEBUG_TEST_get_MS_DELAY_CTRL_input_delay(void);
/*! \brief Writes the bit group 'output_delay' of register 'DEBUG_TEST_MS_DELAY_CTRL'. */
void GH_DEBUG_TEST_set_MS_DELAY_CTRL_output_delay(U8 data);
/*! \brief Reads the bit group 'output_delay' of register 'DEBUG_TEST_MS_DELAY_CTRL'. */
U8   GH_DEBUG_TEST_get_MS_DELAY_CTRL_output_delay(void);
/*! \brief Writes the bit group 'timing' of register 'DEBUG_TEST_MS_DELAY_CTRL'. */
void GH_DEBUG_TEST_set_MS_DELAY_CTRL_timing(U8 data);
/*! \brief Reads the bit group 'timing' of register 'DEBUG_TEST_MS_DELAY_CTRL'. */
U8   GH_DEBUG_TEST_get_MS_DELAY_CTRL_timing(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_MS_DELAY_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_MS_DELAY_CTRL] <-- 0x%08x\n",
                        REG_DEBUG_TEST_MS_DELAY_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_MS_DELAY_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_MS_DELAY_CTRL] --> 0x%08x\n",
                        REG_DEBUG_TEST_MS_DELAY_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_MS_DELAY_CTRL_delay_sclk(U8 data)
{
    GH_DEBUG_TEST_MS_DELAY_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL;
    d.bitc.delay_sclk = data;
    *(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_MS_DELAY_CTRL_delay_sclk] <-- 0x%08x\n",
                        REG_DEBUG_TEST_MS_DELAY_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_MS_DELAY_CTRL_delay_sclk(void)
{
    GH_DEBUG_TEST_MS_DELAY_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_MS_DELAY_CTRL_delay_sclk] --> 0x%08x\n",
                        REG_DEBUG_TEST_MS_DELAY_CTRL,value);
    #endif
    return tmp_value.bitc.delay_sclk;
}
GH_INLINE void GH_DEBUG_TEST_set_MS_DELAY_CTRL_input_delay(U8 data)
{
    GH_DEBUG_TEST_MS_DELAY_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL;
    d.bitc.input_delay = data;
    *(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_MS_DELAY_CTRL_input_delay] <-- 0x%08x\n",
                        REG_DEBUG_TEST_MS_DELAY_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_MS_DELAY_CTRL_input_delay(void)
{
    GH_DEBUG_TEST_MS_DELAY_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_MS_DELAY_CTRL_input_delay] --> 0x%08x\n",
                        REG_DEBUG_TEST_MS_DELAY_CTRL,value);
    #endif
    return tmp_value.bitc.input_delay;
}
GH_INLINE void GH_DEBUG_TEST_set_MS_DELAY_CTRL_output_delay(U8 data)
{
    GH_DEBUG_TEST_MS_DELAY_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL;
    d.bitc.output_delay = data;
    *(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_MS_DELAY_CTRL_output_delay] <-- 0x%08x\n",
                        REG_DEBUG_TEST_MS_DELAY_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_MS_DELAY_CTRL_output_delay(void)
{
    GH_DEBUG_TEST_MS_DELAY_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_MS_DELAY_CTRL_output_delay] --> 0x%08x\n",
                        REG_DEBUG_TEST_MS_DELAY_CTRL,value);
    #endif
    return tmp_value.bitc.output_delay;
}
GH_INLINE void GH_DEBUG_TEST_set_MS_DELAY_CTRL_timing(U8 data)
{
    GH_DEBUG_TEST_MS_DELAY_CTRL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL;
    d.bitc.timing = data;
    *(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_MS_DELAY_CTRL_timing] <-- 0x%08x\n",
                        REG_DEBUG_TEST_MS_DELAY_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_MS_DELAY_CTRL_timing(void)
{
    GH_DEBUG_TEST_MS_DELAY_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_MS_DELAY_CTRL_timing] --> 0x%08x\n",
                        REG_DEBUG_TEST_MS_DELAY_CTRL,value);
    #endif
    return tmp_value.bitc.timing;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_USE_COMMON_VO_CLOCK (read/write)                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_USE_COMMON_VO_CLOCK'. */
void GH_DEBUG_TEST_set_USE_COMMON_VO_CLOCK(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_USE_COMMON_VO_CLOCK'. */
U32  GH_DEBUG_TEST_get_USE_COMMON_VO_CLOCK(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_USE_COMMON_VO_CLOCK(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_USE_COMMON_VO_CLOCK = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_USE_COMMON_VO_CLOCK] <-- 0x%08x\n",
                        REG_DEBUG_TEST_USE_COMMON_VO_CLOCK,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_USE_COMMON_VO_CLOCK(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_COMMON_VO_CLOCK);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_USE_COMMON_VO_CLOCK] --> 0x%08x\n",
                        REG_DEBUG_TEST_USE_COMMON_VO_CLOCK,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CLOCK_OBSV_ADDR (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_CLOCK_OBSV_ADDR'. */
void GH_DEBUG_TEST_set_CLOCK_OBSV_ADDR(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_CLOCK_OBSV_ADDR'. */
U32  GH_DEBUG_TEST_get_CLOCK_OBSV_ADDR(void);
/*! \brief Writes the bit group 'pll' of register 'DEBUG_TEST_CLOCK_OBSV_ADDR'. */
void GH_DEBUG_TEST_set_CLOCK_OBSV_ADDR_pll(U8 data);
/*! \brief Reads the bit group 'pll' of register 'DEBUG_TEST_CLOCK_OBSV_ADDR'. */
U8   GH_DEBUG_TEST_get_CLOCK_OBSV_ADDR_pll(void);
/*! \brief Writes the bit group 'observation' of register 'DEBUG_TEST_CLOCK_OBSV_ADDR'. */
void GH_DEBUG_TEST_set_CLOCK_OBSV_ADDR_observation(U8 data);
/*! \brief Reads the bit group 'observation' of register 'DEBUG_TEST_CLOCK_OBSV_ADDR'. */
U8   GH_DEBUG_TEST_get_CLOCK_OBSV_ADDR_observation(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_CLOCK_OBSV_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CLOCK_OBSV_ADDR = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CLOCK_OBSV_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CLOCK_OBSV_ADDR,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_CLOCK_OBSV_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLOCK_OBSV_ADDR);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CLOCK_OBSV_ADDR] --> 0x%08x\n",
                        REG_DEBUG_TEST_CLOCK_OBSV_ADDR,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_CLOCK_OBSV_ADDR_pll(U8 data)
{
    GH_DEBUG_TEST_CLOCK_OBSV_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CLOCK_OBSV_ADDR;
    d.bitc.pll = data;
    *(volatile U32 *)REG_DEBUG_TEST_CLOCK_OBSV_ADDR = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CLOCK_OBSV_ADDR_pll] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CLOCK_OBSV_ADDR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_CLOCK_OBSV_ADDR_pll(void)
{
    GH_DEBUG_TEST_CLOCK_OBSV_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLOCK_OBSV_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CLOCK_OBSV_ADDR_pll] --> 0x%08x\n",
                        REG_DEBUG_TEST_CLOCK_OBSV_ADDR,value);
    #endif
    return tmp_value.bitc.pll;
}
GH_INLINE void GH_DEBUG_TEST_set_CLOCK_OBSV_ADDR_observation(U8 data)
{
    GH_DEBUG_TEST_CLOCK_OBSV_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CLOCK_OBSV_ADDR;
    d.bitc.observation = data;
    *(volatile U32 *)REG_DEBUG_TEST_CLOCK_OBSV_ADDR = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CLOCK_OBSV_ADDR_observation] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CLOCK_OBSV_ADDR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_CLOCK_OBSV_ADDR_observation(void)
{
    GH_DEBUG_TEST_CLOCK_OBSV_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLOCK_OBSV_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CLOCK_OBSV_ADDR_observation] --> 0x%08x\n",
                        REG_DEBUG_TEST_CLOCK_OBSV_ADDR,value);
    #endif
    return tmp_value.bitc.observation;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_DISABLE_EXT_BYPASS (read/write)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_DISABLE_EXT_BYPASS'. */
void GH_DEBUG_TEST_set_DISABLE_EXT_BYPASS(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_DISABLE_EXT_BYPASS'. */
U32  GH_DEBUG_TEST_get_DISABLE_EXT_BYPASS(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_DISABLE_EXT_BYPASS(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_DISABLE_EXT_BYPASS = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DISABLE_EXT_BYPASS] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DISABLE_EXT_BYPASS,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_DISABLE_EXT_BYPASS(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DISABLE_EXT_BYPASS);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DISABLE_EXT_BYPASS] --> 0x%08x\n",
                        REG_DEBUG_TEST_DISABLE_EXT_BYPASS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_ARM_SYNC_LOCK (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_ARM_SYNC_LOCK'. */
void GH_DEBUG_TEST_set_ARM_SYNC_LOCK(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_ARM_SYNC_LOCK'. */
U32  GH_DEBUG_TEST_get_ARM_SYNC_LOCK(void);
/*! \brief Writes the bit group 'mode' of register 'DEBUG_TEST_ARM_SYNC_LOCK'. */
void GH_DEBUG_TEST_set_ARM_SYNC_LOCK_mode(U8 data);
/*! \brief Reads the bit group 'mode' of register 'DEBUG_TEST_ARM_SYNC_LOCK'. */
U8   GH_DEBUG_TEST_get_ARM_SYNC_LOCK_mode(void);
/*! \brief Writes the bit group 'reset' of register 'DEBUG_TEST_ARM_SYNC_LOCK'. */
void GH_DEBUG_TEST_set_ARM_SYNC_LOCK_reset(U8 data);
/*! \brief Reads the bit group 'reset' of register 'DEBUG_TEST_ARM_SYNC_LOCK'. */
U8   GH_DEBUG_TEST_get_ARM_SYNC_LOCK_reset(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_ARM_SYNC_LOCK(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_ARM_SYNC_LOCK = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_ARM_SYNC_LOCK] <-- 0x%08x\n",
                        REG_DEBUG_TEST_ARM_SYNC_LOCK,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_ARM_SYNC_LOCK(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_ARM_SYNC_LOCK);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_ARM_SYNC_LOCK] --> 0x%08x\n",
                        REG_DEBUG_TEST_ARM_SYNC_LOCK,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_ARM_SYNC_LOCK_mode(U8 data)
{
    GH_DEBUG_TEST_ARM_SYNC_LOCK_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_ARM_SYNC_LOCK;
    d.bitc.mode = data;
    *(volatile U32 *)REG_DEBUG_TEST_ARM_SYNC_LOCK = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_ARM_SYNC_LOCK_mode] <-- 0x%08x\n",
                        REG_DEBUG_TEST_ARM_SYNC_LOCK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_ARM_SYNC_LOCK_mode(void)
{
    GH_DEBUG_TEST_ARM_SYNC_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_ARM_SYNC_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_ARM_SYNC_LOCK_mode] --> 0x%08x\n",
                        REG_DEBUG_TEST_ARM_SYNC_LOCK,value);
    #endif
    return tmp_value.bitc.mode;
}
GH_INLINE void GH_DEBUG_TEST_set_ARM_SYNC_LOCK_reset(U8 data)
{
    GH_DEBUG_TEST_ARM_SYNC_LOCK_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_ARM_SYNC_LOCK;
    d.bitc.reset = data;
    *(volatile U32 *)REG_DEBUG_TEST_ARM_SYNC_LOCK = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_ARM_SYNC_LOCK_reset] <-- 0x%08x\n",
                        REG_DEBUG_TEST_ARM_SYNC_LOCK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_ARM_SYNC_LOCK_reset(void)
{
    GH_DEBUG_TEST_ARM_SYNC_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_ARM_SYNC_LOCK);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_ARM_SYNC_LOCK_reset] --> 0x%08x\n",
                        REG_DEBUG_TEST_ARM_SYNC_LOCK,value);
    #endif
    return tmp_value.bitc.reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_ARM_SYNC (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_SCALER_ARM_SYNC'. */
void GH_DEBUG_TEST_set_SCALER_ARM_SYNC(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_SCALER_ARM_SYNC'. */
U32  GH_DEBUG_TEST_get_SCALER_ARM_SYNC(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_SCALER_ARM_SYNC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_ARM_SYNC = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_ARM_SYNC] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_ARM_SYNC,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_ARM_SYNC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_ARM_SYNC);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_ARM_SYNC] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_ARM_SYNC,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_ARM_ASYNC (read/write)                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_SCALER_ARM_ASYNC'. */
void GH_DEBUG_TEST_set_SCALER_ARM_ASYNC(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_SCALER_ARM_ASYNC'. */
U32  GH_DEBUG_TEST_get_SCALER_ARM_ASYNC(void);
/*! \brief Writes the bit group 'Div' of register 'DEBUG_TEST_SCALER_ARM_ASYNC'. */
void GH_DEBUG_TEST_set_SCALER_ARM_ASYNC_Div(U8 data);
/*! \brief Reads the bit group 'Div' of register 'DEBUG_TEST_SCALER_ARM_ASYNC'. */
U8   GH_DEBUG_TEST_get_SCALER_ARM_ASYNC_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_SCALER_ARM_ASYNC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_ARM_ASYNC = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_ARM_ASYNC] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_ARM_ASYNC,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_ARM_ASYNC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_ARM_ASYNC);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_ARM_ASYNC] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_ARM_ASYNC,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_ARM_ASYNC_Div(U8 data)
{
    GH_DEBUG_TEST_SCALER_ARM_ASYNC_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_ARM_ASYNC;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_ARM_ASYNC = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_ARM_ASYNC_Div] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_ARM_ASYNC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SCALER_ARM_ASYNC_Div(void)
{
    GH_DEBUG_TEST_SCALER_ARM_ASYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_ARM_ASYNC);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_ARM_ASYNC_Div] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_ARM_ASYNC,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_IDSP_POST (read/write)                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_SCALER_IDSP_POST'. */
void GH_DEBUG_TEST_set_SCALER_IDSP_POST(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_SCALER_IDSP_POST'. */
U32  GH_DEBUG_TEST_get_SCALER_IDSP_POST(void);
/*! \brief Writes the bit group 'Div' of register 'DEBUG_TEST_SCALER_IDSP_POST'. */
void GH_DEBUG_TEST_set_SCALER_IDSP_POST_Div(U8 data);
/*! \brief Reads the bit group 'Div' of register 'DEBUG_TEST_SCALER_IDSP_POST'. */
U8   GH_DEBUG_TEST_get_SCALER_IDSP_POST_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_SCALER_IDSP_POST(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_IDSP_POST = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_IDSP_POST] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_IDSP_POST,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_IDSP_POST(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_IDSP_POST);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_IDSP_POST] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_IDSP_POST,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_IDSP_POST_Div(U8 data)
{
    GH_DEBUG_TEST_SCALER_IDSP_POST_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_IDSP_POST;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_IDSP_POST = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_SCALER_IDSP_POST_Div] <-- 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_IDSP_POST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_SCALER_IDSP_POST_Div(void)
{
    GH_DEBUG_TEST_SCALER_IDSP_POST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_IDSP_POST);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_SCALER_IDSP_POST_Div] --> 0x%08x\n",
                        REG_DEBUG_TEST_SCALER_IDSP_POST,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_OCTRL_GPIO (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_OCTRL_GPIO'. */
void GH_DEBUG_TEST_set_OCTRL_GPIO(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_OCTRL_GPIO'. */
U32  GH_DEBUG_TEST_get_OCTRL_GPIO(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_OCTRL_GPIO(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_OCTRL_GPIO = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_OCTRL_GPIO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_OCTRL_GPIO,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_OCTRL_GPIO(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_OCTRL_GPIO);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_OCTRL_GPIO] --> 0x%08x\n",
                        REG_DEBUG_TEST_OCTRL_GPIO,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_IOCTRL_MISC1 (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_IOCTRL_MISC1'. */
void GH_DEBUG_TEST_set_IOCTRL_MISC1(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_IOCTRL_MISC1'. */
U32  GH_DEBUG_TEST_get_IOCTRL_MISC1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_IOCTRL_MISC1(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_IOCTRL_MISC1 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_IOCTRL_MISC1] <-- 0x%08x\n",
                        REG_DEBUG_TEST_IOCTRL_MISC1,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_IOCTRL_MISC1(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_IOCTRL_MISC1);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_IOCTRL_MISC1] --> 0x%08x\n",
                        REG_DEBUG_TEST_IOCTRL_MISC1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_OCTRL_MISC2 (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_OCTRL_MISC2'. */
void GH_DEBUG_TEST_set_OCTRL_MISC2(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_OCTRL_MISC2'. */
U32  GH_DEBUG_TEST_get_OCTRL_MISC2(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_OCTRL_MISC2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_OCTRL_MISC2 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_OCTRL_MISC2] <-- 0x%08x\n",
                        REG_DEBUG_TEST_OCTRL_MISC2,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_OCTRL_MISC2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_OCTRL_MISC2);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_OCTRL_MISC2] --> 0x%08x\n",
                        REG_DEBUG_TEST_OCTRL_MISC2,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_IOCTRL_SD (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_IOCTRL_SD'. */
void GH_DEBUG_TEST_set_IOCTRL_SD(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_IOCTRL_SD'. */
U32  GH_DEBUG_TEST_get_IOCTRL_SD(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_IOCTRL_SD(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_IOCTRL_SD = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_IOCTRL_SD] <-- 0x%08x\n",
                        REG_DEBUG_TEST_IOCTRL_SD,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_IOCTRL_SD(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_IOCTRL_SD);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_IOCTRL_SD] --> 0x%08x\n",
                        REG_DEBUG_TEST_IOCTRL_SD,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_IOCTRL_SMIO (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_IOCTRL_SMIO'. */
void GH_DEBUG_TEST_set_IOCTRL_SMIO(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_IOCTRL_SMIO'. */
U32  GH_DEBUG_TEST_get_IOCTRL_SMIO(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_IOCTRL_SMIO(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_IOCTRL_SMIO = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_IOCTRL_SMIO] <-- 0x%08x\n",
                        REG_DEBUG_TEST_IOCTRL_SMIO,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_IOCTRL_SMIO(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_IOCTRL_SMIO);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_IOCTRL_SMIO] --> 0x%08x\n",
                        REG_DEBUG_TEST_IOCTRL_SMIO,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_IOCTRL_VD0 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_IOCTRL_VD0'. */
void GH_DEBUG_TEST_set_IOCTRL_VD0(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_IOCTRL_VD0'. */
U32  GH_DEBUG_TEST_get_IOCTRL_VD0(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_IOCTRL_VD0(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_IOCTRL_VD0 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_IOCTRL_VD0] <-- 0x%08x\n",
                        REG_DEBUG_TEST_IOCTRL_VD0,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_IOCTRL_VD0(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_IOCTRL_VD0);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_IOCTRL_VD0] --> 0x%08x\n",
                        REG_DEBUG_TEST_IOCTRL_VD0,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_IOCTRL_VD1 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_IOCTRL_VD1'. */
void GH_DEBUG_TEST_set_IOCTRL_VD1(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_IOCTRL_VD1'. */
U32  GH_DEBUG_TEST_get_IOCTRL_VD1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_IOCTRL_VD1(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_IOCTRL_VD1 = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_IOCTRL_VD1] <-- 0x%08x\n",
                        REG_DEBUG_TEST_IOCTRL_VD1,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_IOCTRL_VD1(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_IOCTRL_VD1);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_IOCTRL_VD1] --> 0x%08x\n",
                        REG_DEBUG_TEST_IOCTRL_VD1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_IOCTRL_SENSOR (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_IOCTRL_SENSOR'. */
void GH_DEBUG_TEST_set_IOCTRL_SENSOR(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_IOCTRL_SENSOR'. */
U32  GH_DEBUG_TEST_get_IOCTRL_SENSOR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_IOCTRL_SENSOR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_IOCTRL_SENSOR = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_IOCTRL_SENSOR] <-- 0x%08x\n",
                        REG_DEBUG_TEST_IOCTRL_SENSOR,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_IOCTRL_SENSOR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_IOCTRL_SENSOR);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_IOCTRL_SENSOR] --> 0x%08x\n",
                        REG_DEBUG_TEST_IOCTRL_SENSOR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_AHB_MISC_EN (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_AHB_MISC_EN'. */
void GH_DEBUG_TEST_set_AHB_MISC_EN(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_AHB_MISC_EN'. */
U32  GH_DEBUG_TEST_get_AHB_MISC_EN(void);
/*! \brief Writes the bit group 'rct_ahb' of register 'DEBUG_TEST_AHB_MISC_EN'. */
void GH_DEBUG_TEST_set_AHB_MISC_EN_rct_ahb(U8 data);
/*! \brief Reads the bit group 'rct_ahb' of register 'DEBUG_TEST_AHB_MISC_EN'. */
U8   GH_DEBUG_TEST_get_AHB_MISC_EN_rct_ahb(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_AHB_MISC_EN(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_AHB_MISC_EN = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_AHB_MISC_EN] <-- 0x%08x\n",
                        REG_DEBUG_TEST_AHB_MISC_EN,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_AHB_MISC_EN(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_AHB_MISC_EN);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_AHB_MISC_EN] --> 0x%08x\n",
                        REG_DEBUG_TEST_AHB_MISC_EN,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_AHB_MISC_EN_rct_ahb(U8 data)
{
    GH_DEBUG_TEST_AHB_MISC_EN_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_AHB_MISC_EN;
    d.bitc.rct_ahb = data;
    *(volatile U32 *)REG_DEBUG_TEST_AHB_MISC_EN = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_AHB_MISC_EN_rct_ahb] <-- 0x%08x\n",
                        REG_DEBUG_TEST_AHB_MISC_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_AHB_MISC_EN_rct_ahb(void)
{
    GH_DEBUG_TEST_AHB_MISC_EN_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_AHB_MISC_EN);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_AHB_MISC_EN_rct_ahb] --> 0x%08x\n",
                        REG_DEBUG_TEST_AHB_MISC_EN,value);
    #endif
    return tmp_value.bitc.rct_ahb;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_DDR_INIT (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_CG_DDR_INIT'. */
void GH_DEBUG_TEST_set_CG_DDR_INIT(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_CG_DDR_INIT'. */
U32  GH_DEBUG_TEST_get_CG_DDR_INIT(void);
/*! \brief Writes the bit group 'Divide' of register 'DEBUG_TEST_CG_DDR_INIT'. */
void GH_DEBUG_TEST_set_CG_DDR_INIT_Divide(U8 data);
/*! \brief Reads the bit group 'Divide' of register 'DEBUG_TEST_CG_DDR_INIT'. */
U8   GH_DEBUG_TEST_get_CG_DDR_INIT_Divide(void);
/*! \brief Writes the bit group 'en' of register 'DEBUG_TEST_CG_DDR_INIT'. */
void GH_DEBUG_TEST_set_CG_DDR_INIT_en(U8 data);
/*! \brief Reads the bit group 'en' of register 'DEBUG_TEST_CG_DDR_INIT'. */
U8   GH_DEBUG_TEST_get_CG_DDR_INIT_en(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_CG_DDR_INIT(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CG_DDR_INIT = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CG_DDR_INIT] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CG_DDR_INIT,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_DDR_INIT(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_DDR_INIT);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CG_DDR_INIT] --> 0x%08x\n",
                        REG_DEBUG_TEST_CG_DDR_INIT,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_CG_DDR_INIT_Divide(U8 data)
{
    GH_DEBUG_TEST_CG_DDR_INIT_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CG_DDR_INIT;
    d.bitc.divide = data;
    *(volatile U32 *)REG_DEBUG_TEST_CG_DDR_INIT = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CG_DDR_INIT_Divide] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CG_DDR_INIT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_CG_DDR_INIT_Divide(void)
{
    GH_DEBUG_TEST_CG_DDR_INIT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_DDR_INIT);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CG_DDR_INIT_Divide] --> 0x%08x\n",
                        REG_DEBUG_TEST_CG_DDR_INIT,value);
    #endif
    return tmp_value.bitc.divide;
}
GH_INLINE void GH_DEBUG_TEST_set_CG_DDR_INIT_en(U8 data)
{
    GH_DEBUG_TEST_CG_DDR_INIT_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CG_DDR_INIT;
    d.bitc.en = data;
    *(volatile U32 *)REG_DEBUG_TEST_CG_DDR_INIT = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CG_DDR_INIT_en] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CG_DDR_INIT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_CG_DDR_INIT_en(void)
{
    GH_DEBUG_TEST_CG_DDR_INIT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_DDR_INIT);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CG_DDR_INIT_en] --> 0x%08x\n",
                        REG_DEBUG_TEST_CG_DDR_INIT,value);
    #endif
    return tmp_value.bitc.en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_DDR_DIV_RST (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_DDR_DIV_RST'. */
void GH_DEBUG_TEST_set_DDR_DIV_RST(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_DDR_DIV_RST'. */
U32  GH_DEBUG_TEST_get_DDR_DIV_RST(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_DDR_DIV_RST(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_DDR_DIV_RST = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DDR_DIV_RST] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DDR_DIV_RST,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_DDR_DIV_RST(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DDR_DIV_RST);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DDR_DIV_RST] --> 0x%08x\n",
                        REG_DEBUG_TEST_DDR_DIV_RST,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_DDRC_IDSP_RESET (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_DDRC_IDSP_RESET'. */
void GH_DEBUG_TEST_set_DDRC_IDSP_RESET(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_DDRC_IDSP_RESET'. */
U32  GH_DEBUG_TEST_get_DDRC_IDSP_RESET(void);
/*! \brief Writes the bit group 'ddrc' of register 'DEBUG_TEST_DDRC_IDSP_RESET'. */
void GH_DEBUG_TEST_set_DDRC_IDSP_RESET_ddrc(U8 data);
/*! \brief Reads the bit group 'ddrc' of register 'DEBUG_TEST_DDRC_IDSP_RESET'. */
U8   GH_DEBUG_TEST_get_DDRC_IDSP_RESET_ddrc(void);
/*! \brief Writes the bit group 'idsp' of register 'DEBUG_TEST_DDRC_IDSP_RESET'. */
void GH_DEBUG_TEST_set_DDRC_IDSP_RESET_idsp(U8 data);
/*! \brief Reads the bit group 'idsp' of register 'DEBUG_TEST_DDRC_IDSP_RESET'. */
U8   GH_DEBUG_TEST_get_DDRC_IDSP_RESET_idsp(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_DDRC_IDSP_RESET(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_DDRC_IDSP_RESET = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DDRC_IDSP_RESET] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DDRC_IDSP_RESET,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_DDRC_IDSP_RESET(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DDRC_IDSP_RESET);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DDRC_IDSP_RESET] --> 0x%08x\n",
                        REG_DEBUG_TEST_DDRC_IDSP_RESET,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_TEST_set_DDRC_IDSP_RESET_ddrc(U8 data)
{
    GH_DEBUG_TEST_DDRC_IDSP_RESET_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DDRC_IDSP_RESET;
    d.bitc.ddrc = data;
    *(volatile U32 *)REG_DEBUG_TEST_DDRC_IDSP_RESET = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DDRC_IDSP_RESET_ddrc] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DDRC_IDSP_RESET,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DDRC_IDSP_RESET_ddrc(void)
{
    GH_DEBUG_TEST_DDRC_IDSP_RESET_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DDRC_IDSP_RESET);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DDRC_IDSP_RESET_ddrc] --> 0x%08x\n",
                        REG_DEBUG_TEST_DDRC_IDSP_RESET,value);
    #endif
    return tmp_value.bitc.ddrc;
}
GH_INLINE void GH_DEBUG_TEST_set_DDRC_IDSP_RESET_idsp(U8 data)
{
    GH_DEBUG_TEST_DDRC_IDSP_RESET_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DDRC_IDSP_RESET;
    d.bitc.idsp = data;
    *(volatile U32 *)REG_DEBUG_TEST_DDRC_IDSP_RESET = d.all;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_DDRC_IDSP_RESET_idsp] <-- 0x%08x\n",
                        REG_DEBUG_TEST_DDRC_IDSP_RESET,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_TEST_get_DDRC_IDSP_RESET_idsp(void)
{
    GH_DEBUG_TEST_DDRC_IDSP_RESET_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DDRC_IDSP_RESET);

    tmp_value.all = value;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_DDRC_IDSP_RESET_idsp] --> 0x%08x\n",
                        REG_DEBUG_TEST_DDRC_IDSP_RESET,value);
    #endif
    return tmp_value.bitc.idsp;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CKEN_IDSP (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TEST_CKEN_IDSP'. */
void GH_DEBUG_TEST_set_CKEN_IDSP(U32 data);
/*! \brief Reads the register 'DEBUG_TEST_CKEN_IDSP'. */
U32  GH_DEBUG_TEST_get_CKEN_IDSP(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TEST_set_CKEN_IDSP(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CKEN_IDSP = data;
    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TEST_set_CKEN_IDSP] <-- 0x%08x\n",
                        REG_DEBUG_TEST_CKEN_IDSP,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TEST_get_CKEN_IDSP(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CKEN_IDSP);

    #if GH_DEBUG_TEST_ENABLE_DEBUG_PRINT
    GH_DEBUG_TEST_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TEST_get_CKEN_IDSP] --> 0x%08x\n",
                        REG_DEBUG_TEST_CKEN_IDSP,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_DEBUG_TEST_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_DEBUG_TEST_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

