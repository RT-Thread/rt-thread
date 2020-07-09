/*!
*******************************************************************************
**
** \file      gh_debug_rct_amba.h
**
** \brief     RCT Debug Registers.
**
**            Copyright:   2012 - 2016 (C) GoKe Microelectronics
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#ifndef _GH_DEBUG_RCT_AMBA_H
#define _GH_DEBUG_RCT_AMBA_H

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

#define GH_PLL_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_PLL_DEBUG_PRINT_FUNCTION printk
#else
#define GH_PLL_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_PLL_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_PLL_PLL_CORE_CTRL                               FIO_ADDRESS(PLL,0xa0170000) /* read/write */
#define REG_PLL_PLL_CORE_FRAC                               FIO_ADDRESS(PLL,0xa0170004) /* read/write */
#define REG_PLL_HDMI_CTRL                                   FIO_ADDRESS(PLL,0xa0170008) /* read/write */
#define REG_PLL_SCALER_SD48                                 FIO_ADDRESS(PLL,0xa017000C) /* read/write */
#define REG_PLL_PLL_VIDEO_CTRL                              FIO_ADDRESS(PLL,0xa0170014) /* read/write */
#define REG_PLL_PLL_VIDEO_FRAC                              FIO_ADDRESS(PLL,0xa0170018) /* read/write */
#define REG_PLL_SCALER_VIDEO                                FIO_ADDRESS(PLL,0xa017001C) /* read/write */
#define REG_PLL_PLL_SENSOR_CTRL                             FIO_ADDRESS(PLL,0xa0170024) /* read/write */
#define REG_PLL_PLL_SENSOR_FRAC                             FIO_ADDRESS(PLL,0xa0170028) /* read/write */
#define REG_PLL_PLL_LOCK                                    FIO_ADDRESS(PLL,0xa017002C) /* read */
#define REG_PLL_SCALER_SENSOR_POST                          FIO_ADDRESS(PLL,0xa0170030) /* read/write */
#define REG_PLL_SYS_CONFIG                                  FIO_ADDRESS(PLL,0xa0170034) /* read/write */
#define REG_PLL_CG_UART                                     FIO_ADDRESS(PLL,0xa0170038) /* read/write */
#define REG_PLL_CG_SSI                                      FIO_ADDRESS(PLL,0xa017003C) /* read/write */
#define REG_PLL_CG_MOTOR                                    FIO_ADDRESS(PLL,0xa0170040) /* read/write */
#define REG_PLL_CG_IR                                       FIO_ADDRESS(PLL,0xa0170044) /* read/write */
#define REG_PLL_CG_HOST                                     FIO_ADDRESS(PLL,0xa0170048) /* read/write */
#define REG_PLL_SCALER_SENSOR_PRE                           FIO_ADDRESS(PLL,0xa017004C) /* read/write */
#define REG_PLL_ANA_PWR                                     FIO_ADDRESS(PLL,0xa0170050) /* read/write */
#define REG_PLL_PLL_AUDIO_CTRL                              FIO_ADDRESS(PLL,0xa0170054) /* read/write */
#define REG_PLL_PLL_AUDIO_FRAC                              FIO_ADDRESS(PLL,0xa0170058) /* read/write */
#define REG_PLL_SCALER_AUDIO                                FIO_ADDRESS(PLL,0xa017005C) /* read/write */
#define REG_PLL_SCALER_AUDIO_PRE                            FIO_ADDRESS(PLL,0xa0170060) /* read/write */
#define REG_PLL_SOFT_OR_DLLRESET                            FIO_ADDRESS(PLL,0xa0170068) /* read/write */
#define REG_PLL_FIO_RESET                                   FIO_ADDRESS(PLL,0xa0170074) /* read/write */
#define REG_PLL_WDT_RST_L                                   FIO_ADDRESS(PLL,0xa0170078) /* read */
#define REG_PLL_SCALER_USB                                  FIO_ADDRESS(PLL,0xa017007C) /* read/write */
#define REG_PLL_CLK_DEBOUNCE                                FIO_ADDRESS(PLL,0xa0170080) /* read/write */
#define REG_PLL_CG_PWM                                      FIO_ADDRESS(PLL,0xa0170084) /* read/write */
#define REG_PLL_USBP_CTRL                                   FIO_ADDRESS(PLL,0xa0170088) /* read/write */
#define REG_PLL_CKEN_VDSP                                   FIO_ADDRESS(PLL,0xa017008C) /* read/write */
#define REG_PLL_DLL0                                        FIO_ADDRESS(PLL,0xa0170090) /* read/write */
#define REG_PLL_DLL1                                        FIO_ADDRESS(PLL,0xa0170094) /* read/write */
#define REG_PLL_SCALER_ADC                                  FIO_ADDRESS(PLL,0xa017009C) /* read/write */
#define REG_PLL_SCALER_VIDEO_POST                           FIO_ADDRESS(PLL,0xa01700A0) /* read/write */
#define REG_PLL_CLK_REF_AU_EXTERNAL                         FIO_ADDRESS(PLL,0xa01700A4) /* read/write */
#define REG_PLL_USE_EXTERNAL_CLK_AU                         FIO_ADDRESS(PLL,0xa01700A8) /* read/write */
#define REG_PLL_CLK_REF_VIDEO_EXTERNAL                      FIO_ADDRESS(PLL,0xa01700AC) /* read/write */
#define REG_PLL_USE_EXTERNAL_VD_CLK                         FIO_ADDRESS(PLL,0xa01700B0) /* read/write */
#define REG_PLL_USE_CLK_SI_4_CLK_AU                         FIO_ADDRESS(PLL,0xa01700B4) /* read/write */
#define REG_PLL_USE_CLK_SI_4_CLK_VO                         FIO_ADDRESS(PLL,0xa01700B8) /* read/write */
#define REG_PLL_CLK_SI_INPUT_MODE                           FIO_ADDRESS(PLL,0xa01700BC) /* read/write */
#define REG_PLL_PLL_VIDEO2_CTRL                             FIO_ADDRESS(PLL,0xa01700C0) /* read/write */
#define REG_PLL_PLL_VIDEO2_FRAC                             FIO_ADDRESS(PLL,0xa01700C4) /* read/write */
#define REG_PLL_SCALER_VIDEO2                               FIO_ADDRESS(PLL,0xa01700C8) /* read/write */
#define REG_PLL_SCALER_VIDEO2_POST                          FIO_ADDRESS(PLL,0xa01700CC) /* read/write */
#define REG_PLL_USE_CLK_SI_4_CLK_VO2                        FIO_ADDRESS(PLL,0xa01700D0) /* read/write */
#define REG_PLL_USE_EXTERNAL_VD2_CLK                        FIO_ADDRESS(PLL,0xa01700D4) /* read/write */
#define REG_PLL_CLK_REF_VIDEO2_EXTERNAL                     FIO_ADDRESS(PLL,0xa01700D8) /* read/write */
#define REG_PLL_PLL_DDR_CTRL                                FIO_ADDRESS(PLL,0xa01700DC) /* read/write */
#define REG_PLL_PLL_DDR_FRAC                                FIO_ADDRESS(PLL,0xa01700E0) /* read/write */
#define REG_PLL_PLL_IDSP_CTRL                               FIO_ADDRESS(PLL,0xa01700E4) /* read/write */
#define REG_PLL_PLL_IDSP_FRAC                               FIO_ADDRESS(PLL,0xa01700E8) /* read/write */
#define REG_PLL_CG_SSI2                                     FIO_ADDRESS(PLL,0xa01700EC) /* read/write */
#define REG_PLL_LVDS_LVCMOS                                 FIO_ADDRESS(PLL,0xa01700F8) /* read/write */
#define REG_PLL_LVDS_ASYNC                                  FIO_ADDRESS(PLL,0xa01700FC) /* read/write */
#define REG_PLL_PLL_CORE_CTRL2                              FIO_ADDRESS(PLL,0xa0170100) /* read/write */
#define REG_PLL_PLL_CORE_CTRL3                              FIO_ADDRESS(PLL,0xa0170104) /* read/write */
#define REG_PLL_PLL_IDSP_CTRL2                              FIO_ADDRESS(PLL,0xa0170108) /* read/write */
#define REG_PLL_PLL_IDSP_CTRL3                              FIO_ADDRESS(PLL,0xa017010C) /* read/write */
#define REG_PLL_PLL_IDSP_CTRL22                             FIO_ADDRESS(PLL,0xa0170110) /* read/write */
#define REG_PLL_PLL_IDSP_CTRL32                             FIO_ADDRESS(PLL,0xa0170114) /* read/write */
#define REG_PLL_SCALER_CORE_POST                            FIO_ADDRESS(PLL,0xa0170118) /* read/write */
#define REG_PLL_PLL_SENSOR_CTRL2                            FIO_ADDRESS(PLL,0xa017011C) /* read/write */
#define REG_PLL_PLL_SENSOR_CTRL3                            FIO_ADDRESS(PLL,0xa0170120) /* read/write */
#define REG_PLL_PLL_AUDIO_CTRL2                             FIO_ADDRESS(PLL,0xa0170124) /* read/write */
#define REG_PLL_PLL_AUDIO_CTRL3                             FIO_ADDRESS(PLL,0xa017012C) /* read/write */
#define REG_PLL_PLL_VIDEO_CTRL2                             FIO_ADDRESS(PLL,0xa0170130) /* read/write */
#define REG_PLL_PLL_VIDEO_CTRL3                             FIO_ADDRESS(PLL,0xa0170134) /* read/write */
#define REG_PLL_PLL_VIDEO2_CTRL2                            FIO_ADDRESS(PLL,0xa017013C) /* read/write */
#define REG_PLL_PLL_USB_CTRL2                               FIO_ADDRESS(PLL,0xa0170144) /* read/write */
#define REG_PLL_CG_DDR_CALIB                                FIO_ADDRESS(PLL,0xa0170148) /* read/write */
#define REG_PLL_DLL_CTRL_SEL                                FIO_ADDRESS(PLL,0xa0170158) /* read/write */
#define REG_PLL_DLL_OCD_BITS                                FIO_ADDRESS(PLL,0xa017015C) /* read/write */
#define REG_PLL_PLL_CORE_OBSV                               FIO_ADDRESS(PLL,0xa0170174) /* read/write */
#define REG_PLL_PLL_IDSP_OBSV                               FIO_ADDRESS(PLL,0xa0170178) /* read/write */
#define REG_PLL_PLL_DDR_OBSV                                FIO_ADDRESS(PLL,0xa017017C) /* read/write */
#define REG_PLL_PLL_SENSOR_OBSV                             FIO_ADDRESS(PLL,0xa0170180) /* read/write */
#define REG_PLL_PLL_AUDIO_OBSV                              FIO_ADDRESS(PLL,0xa0170184) /* read/write */
#define REG_PLL_PLL_VIDEO_OBSV                              FIO_ADDRESS(PLL,0xa0170188) /* read/write */
#define REG_PLL_PLL_VIDEO2_OBSV                             FIO_ADDRESS(PLL,0xa017018C) /* read/write */
#define REG_PLL_ADC16_CTRL_ADDR                             FIO_ADDRESS(PLL,0xa0170198) /* read/write */
#define REG_PLL_CLK_REF_SSI_ADDR                            FIO_ADDRESS(PLL,0xa017019C) /* read/write */
#define REG_PLL_CG_DVEN                                     FIO_ADDRESS(PLL,0xa01701C8) /* read/write */
#define REG_PLL_SCALER_MS                                   FIO_ADDRESS(PLL,0xa01701CC) /* read/write */
#define REG_PLL_MS_DELAY_CTRL                               FIO_ADDRESS(PLL,0xa01701D0) /* read/write */
#define REG_PLL_USE_COMMON_VO_CLOCK                         FIO_ADDRESS(PLL,0xa01701D4) /* read/write */
#define REG_PLL_CLOCK_OBSV_ADDR                             FIO_ADDRESS(PLL,0xa01701E0) /* read/write */
#define REG_PLL_DISABLE_EXT_BYPASS                          FIO_ADDRESS(PLL,0xa01701E4) /* read/write */
#define REG_PLL_ARM_SYNC_LOCK                               FIO_ADDRESS(PLL,0xa01701E8) /* read/write */
#define REG_PLL_SCALER_ARM_SYNC                             FIO_ADDRESS(PLL,0xa01701EC) /* read/write */
#define REG_PLL_SCALER_ARM_ASYNC                            FIO_ADDRESS(PLL,0xa01701F0) /* read/write */
#define REG_PLL_SCALER_IDSP_POST                            FIO_ADDRESS(PLL,0xa01701F4) /* read/write */
#define REG_PLL_OCTRL_GPIO                                  FIO_ADDRESS(PLL,0xa01701F8) /* read/write */
#define REG_PLL_IOCTRL_MISC1                                FIO_ADDRESS(PLL,0xa01701FC) /* read/write */
#define REG_PLL_OCTRL_MISC2                                 FIO_ADDRESS(PLL,0xa0170200) /* read/write */
#define REG_PLL_IOCTRL_SD                                   FIO_ADDRESS(PLL,0xa0170204) /* read/write */
#define REG_PLL_IOCTRL_SMIO                                 FIO_ADDRESS(PLL,0xa0170208) /* read/write */
#define REG_PLL_IOCTRL_VD0                                  FIO_ADDRESS(PLL,0xa017020C) /* read/write */
#define REG_PLL_IOCTRL_VD1                                  FIO_ADDRESS(PLL,0xa0170210) /* read/write */
#define REG_PLL_IOCTRL_SENSOR                               FIO_ADDRESS(PLL,0xa0170214) /* read/write */
#define REG_PLL_AHB_MISC_EN                                 FIO_ADDRESS(PLL,0xa017021C) /* read/write */
#define REG_PLL_CG_DDR_INIT                                 FIO_ADDRESS(PLL,0xa0170220) /* read/write */
#define REG_PLL_DDR_DIV_RST                                 FIO_ADDRESS(PLL,0xa0170224) /* read/write */
#define REG_PLL_DDRC_IDSP_RESET                             FIO_ADDRESS(PLL,0xa0170228) /* read/write */
#define REG_PLL_CKEN_IDSP                                   FIO_ADDRESS(PLL,0xa017022C) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* PLL_HDMI_CTRL */
    U32 all;
    struct {
        U32                             : 1;
        U32 hdmi_phy_test_mode          : 1;
        U32 use_hdmi_phy_clk_v          : 1;
        U32                             : 29;
    } bitc;
} GH_PLL_HDMI_CTRL_S;

typedef union { /* PLL_SCALER_SD48 */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 6;
        U32 sdclk_delay                 : 2;
        U32                             : 8;
    } bitc;
} GH_PLL_SCALER_SD48_S;

typedef union { /* PLL_PLL_VIDEO_CTRL */
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
} GH_PLL_PLL_VIDEO_CTRL_S;

typedef union { /* PLL_SCALER_VIDEO */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_PLL_SCALER_VIDEO_S;

typedef union { /* PLL_PLL_LOCK */
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
} GH_PLL_PLL_LOCK_S;

typedef union { /* PLL_SCALER_SENSOR_POST */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_PLL_SCALER_SENSOR_POST_S;

typedef union { /* PLL_SYS_CONFIG */
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
} GH_PLL_SYS_CONFIG_S;

typedef union { /* PLL_SCALER_SENSOR_PRE */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_PLL_SCALER_SENSOR_PRE_S;

typedef union { /* PLL_ANA_PWR */
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
} GH_PLL_ANA_PWR_S;

typedef union { /* PLL_SCALER_AUDIO */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_PLL_SCALER_AUDIO_S;

typedef union { /* PLL_SCALER_AUDIO_PRE */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_PLL_SCALER_AUDIO_PRE_S;

typedef union { /* PLL_SOFT_OR_DLLRESET */
    U32 all;
    struct {
        U32 softreset                   : 1;
        U32 dll_rst_l                   : 1;
        U32                             : 30;
    } bitc;
} GH_PLL_SOFT_OR_DLLRESET_S;

typedef union { /* PLL_FIO_RESET */
    U32 all;
    struct {
        U32 flashreset                  : 1;
        U32 xdreset                     : 1;
        U32 cfreset                     : 1;
        U32 fioreset                    : 1;
        U32                             : 28;
    } bitc;
} GH_PLL_FIO_RESET_S;

typedef union { /* PLL_SCALER_USB */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_PLL_SCALER_USB_S;

typedef union { /* PLL_USBP_CTRL */
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
} GH_PLL_USBP_CTRL_S;

typedef union { /* PLL_CKEN_VDSP */
    U32 all;
    struct {
        U32 cken_tsfm                   : 1;
        U32 cken_code                   : 1;
        U32 cken_smem                   : 1;
        U32                             : 29;
    } bitc;
} GH_PLL_CKEN_VDSP_S;

typedef union { /* PLL_DLL0 */
    U32 all;
    struct {
        U32 dll_sel2                    : 8;
        U32 dll_sel1                    : 8;
        U32 dll_sel0                    : 8;
        U32                             : 8;
    } bitc;
} GH_PLL_DLL0_S;

typedef union { /* PLL_DLL1 */
    U32 all;
    struct {
        U32 dll_sel2                    : 8;
        U32 dll_sel1                    : 8;
        U32 dll_sel0                    : 8;
        U32                             : 8;
    } bitc;
} GH_PLL_DLL1_S;

typedef union { /* PLL_SCALER_ADC */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_PLL_SCALER_ADC_S;

typedef union { /* PLL_SCALER_VIDEO_POST */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_PLL_SCALER_VIDEO_POST_S;

typedef union { /* PLL_CLK_REF_AU_EXTERNAL */
    U32 all;
    struct {
        U32 external                    : 1;
        U32                             : 31;
    } bitc;
} GH_PLL_CLK_REF_AU_EXTERNAL_S;

typedef union { /* PLL_USE_EXTERNAL_CLK_AU */
    U32 all;
    struct {
        U32 external                    : 1;
        U32                             : 31;
    } bitc;
} GH_PLL_USE_EXTERNAL_CLK_AU_S;

typedef union { /* PLL_CLK_REF_VIDEO_EXTERNAL */
    U32 all;
    struct {
        U32 external                    : 1;
        U32                             : 31;
    } bitc;
} GH_PLL_CLK_REF_VIDEO_EXTERNAL_S;

typedef union { /* PLL_USE_EXTERNAL_VD_CLK */
    U32 all;
    struct {
        U32 external                    : 1;
        U32                             : 31;
    } bitc;
} GH_PLL_USE_EXTERNAL_VD_CLK_S;

typedef union { /* PLL_USE_CLK_SI_4_CLK_AU */
    U32 all;
    struct {
        U32 pllref                      : 2;
        U32                             : 30;
    } bitc;
} GH_PLL_USE_CLK_SI_4_CLK_AU_S;

typedef union { /* PLL_USE_CLK_SI_4_CLK_VO */
    U32 all;
    struct {
        U32 pllref                      : 2;
        U32                             : 30;
    } bitc;
} GH_PLL_USE_CLK_SI_4_CLK_VO_S;

typedef union { /* PLL_CLK_SI_INPUT_MODE */
    U32 all;
    struct {
        U32 clk_si                      : 1;
        U32                             : 31;
    } bitc;
} GH_PLL_CLK_SI_INPUT_MODE_S;

typedef union { /* PLL_PLL_VIDEO2_CTRL */
    U32 all;
    struct {
        U32                             : 20;
        U32 pll_lock                    : 1;
        U32 gclk_vo                     : 1;
        U32                             : 10;
    } bitc;
} GH_PLL_PLL_VIDEO2_CTRL_S;

typedef union { /* PLL_SCALER_VIDEO2 */
    U32 all;
    struct {
        U32 integerdiv                  : 16;
        U32 primediv                    : 5;
        U32                             : 3;
        U32 dutycycle                   : 1;
        U32                             : 7;
    } bitc;
} GH_PLL_SCALER_VIDEO2_S;

typedef union { /* PLL_SCALER_VIDEO2_POST */
    U32 all;
    struct {
        U32 integerdiv                  : 16;
        U32 primediv                    : 5;
        U32                             : 3;
        U32 dutycycle                   : 1;
        U32                             : 7;
    } bitc;
} GH_PLL_SCALER_VIDEO2_POST_S;

typedef union { /* PLL_USE_CLK_SI_4_CLK_VO2 */
    U32 all;
    struct {
        U32 pllref                      : 2;
        U32                             : 30;
    } bitc;
} GH_PLL_USE_CLK_SI_4_CLK_VO2_S;

typedef union { /* PLL_USE_EXTERNAL_VD2_CLK */
    U32 all;
    struct {
        U32 external                    : 1;
        U32                             : 31;
    } bitc;
} GH_PLL_USE_EXTERNAL_VD2_CLK_S;

typedef union { /* PLL_CLK_REF_VIDEO2_EXTERNAL */
    U32 all;
    struct {
        U32 external                    : 1;
        U32                             : 31;
    } bitc;
} GH_PLL_CLK_REF_VIDEO2_EXTERNAL_S;

typedef union { /* PLL_PLL_DDR_FRAC */
    U32 all;
    struct {
        U32 fraction                    : 16;
        U32                             : 16;
    } bitc;
} GH_PLL_PLL_DDR_FRAC_S;

typedef union { /* PLL_PLL_IDSP_FRAC */
    U32 all;
    struct {
        U32 fraction                    : 16;
        U32                             : 16;
    } bitc;
} GH_PLL_PLL_IDSP_FRAC_S;

typedef union { /* PLL_LVDS_LVCMOS */
    U32 all;
    struct {
        U32 lvcoms_sd                   : 16;
        U32 lvcmos_spclk                : 4;
        U32                             : 12;
    } bitc;
} GH_PLL_LVDS_LVCMOS_S;

typedef union { /* PLL_LVDS_ASYNC */
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
} GH_PLL_LVDS_ASYNC_S;

typedef union { /* PLL_PLL_CORE_CTRL2 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_PLL_PLL_CORE_CTRL2_S;

typedef union { /* PLL_PLL_CORE_CTRL3 */
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
} GH_PLL_PLL_CORE_CTRL3_S;

typedef union { /* PLL_PLL_IDSP_CTRL2 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_PLL_PLL_IDSP_CTRL2_S;

typedef union { /* PLL_PLL_IDSP_CTRL3 */
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
} GH_PLL_PLL_IDSP_CTRL3_S;

typedef union { /* PLL_PLL_IDSP_CTRL22 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_PLL_PLL_IDSP_CTRL22_S;

typedef union { /* PLL_PLL_IDSP_CTRL32 */
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
} GH_PLL_PLL_IDSP_CTRL32_S;

typedef union { /* PLL_SCALER_CORE_POST */
    U32 all;
    struct {
        U32 div                         : 4;
        U32                             : 28;
    } bitc;
} GH_PLL_SCALER_CORE_POST_S;

typedef union { /* PLL_PLL_SENSOR_CTRL2 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_PLL_PLL_SENSOR_CTRL2_S;

typedef union { /* PLL_PLL_SENSOR_CTRL3 */
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
} GH_PLL_PLL_SENSOR_CTRL3_S;

typedef union { /* PLL_PLL_AUDIO_CTRL2 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_PLL_PLL_AUDIO_CTRL2_S;

typedef union { /* PLL_PLL_AUDIO_CTRL3 */
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
} GH_PLL_PLL_AUDIO_CTRL3_S;

typedef union { /* PLL_PLL_VIDEO_CTRL2 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_PLL_PLL_VIDEO_CTRL2_S;

typedef union { /* PLL_PLL_VIDEO_CTRL3 */
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
} GH_PLL_PLL_VIDEO_CTRL3_S;

typedef union { /* PLL_PLL_VIDEO2_CTRL2 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_PLL_PLL_VIDEO2_CTRL2_S;

typedef union { /* PLL_PLL_USB_CTRL2 */
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
} GH_PLL_PLL_USB_CTRL2_S;

typedef union { /* PLL_DLL_CTRL_SEL */
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
} GH_PLL_DLL_CTRL_SEL_S;

typedef union { /* PLL_DLL_OCD_BITS */
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
} GH_PLL_DLL_OCD_BITS_S;

typedef union { /* PLL_ADC16_CTRL_ADDR */
    U32 all;
    struct {
        U32 adc_power_down              : 1;
        U32 adc_clock_select            : 1;
        U32                             : 30;
    } bitc;
} GH_PLL_ADC16_CTRL_ADDR_S;

typedef union { /* PLL_CLK_REF_SSI_ADDR */
    U32 all;
    struct {
        U32 clk                         : 1;
        U32                             : 31;
    } bitc;
} GH_PLL_CLK_REF_SSI_ADDR_S;

typedef union { /* PLL_MS_DELAY_CTRL */
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
} GH_PLL_MS_DELAY_CTRL_S;

typedef union { /* PLL_CLOCK_OBSV_ADDR */
    U32 all;
    struct {
        U32 pll                         : 4;
        U32 observation                 : 1;
        U32                             : 27;
    } bitc;
} GH_PLL_CLOCK_OBSV_ADDR_S;

typedef union { /* PLL_ARM_SYNC_LOCK */
    U32 all;
    struct {
        U32 mode                        : 1;
        U32 reset                       : 1;
        U32                             : 30;
    } bitc;
} GH_PLL_ARM_SYNC_LOCK_S;

typedef union { /* PLL_SCALER_ARM_ASYNC */
    U32 all;
    struct {
        U32 div                         : 4;
        U32                             : 28;
    } bitc;
} GH_PLL_SCALER_ARM_ASYNC_S;

typedef union { /* PLL_SCALER_IDSP_POST */
    U32 all;
    struct {
        U32 div                         : 4;
        U32                             : 28;
    } bitc;
} GH_PLL_SCALER_IDSP_POST_S;

typedef union { /* PLL_AHB_MISC_EN */
    U32 all;
    struct {
        U32 rct_ahb                     : 1;
        U32                             : 31;
    } bitc;
} GH_PLL_AHB_MISC_EN_S;

typedef union { /* PLL_CG_DDR_INIT */
    U32 all;
    struct {
        U32 divide                      : 8;
        U32 en                          : 1;
        U32                             : 23;
    } bitc;
} GH_PLL_CG_DDR_INIT_S;

typedef union { /* PLL_DDRC_IDSP_RESET */
    U32 all;
    struct {
        U32 ddrc                        : 1;
        U32 idsp                        : 1;
        U32                             : 30;
    } bitc;
} GH_PLL_DDRC_IDSP_RESET_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_CORE_CTRL (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_CORE_CTRL'. */
void GH_PLL_set_PLL_CORE_CTRL(U32 data);
/*! \brief Reads the register 'PLL_PLL_CORE_CTRL'. */
U32  GH_PLL_get_PLL_CORE_CTRL(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_CORE_FRAC (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_CORE_FRAC'. */
void GH_PLL_set_PLL_CORE_FRAC(U32 data);
/*! \brief Reads the register 'PLL_PLL_CORE_FRAC'. */
U32  GH_PLL_get_PLL_CORE_FRAC(void);

/*----------------------------------------------------------------------------*/
/* register PLL_HDMI_CTRL (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_HDMI_CTRL'. */
void GH_PLL_set_HDMI_CTRL(U32 data);
/*! \brief Reads the register 'PLL_HDMI_CTRL'. */
U32  GH_PLL_get_HDMI_CTRL(void);
/*! \brief Writes the bit group 'Hdmi_phy_test_mode' of register 'PLL_HDMI_CTRL'. */
void GH_PLL_set_HDMI_CTRL_Hdmi_phy_test_mode(U8 data);
/*! \brief Reads the bit group 'Hdmi_phy_test_mode' of register 'PLL_HDMI_CTRL'. */
U8   GH_PLL_get_HDMI_CTRL_Hdmi_phy_test_mode(void);
/*! \brief Writes the bit group 'use_hdmi_phy_clk_v' of register 'PLL_HDMI_CTRL'. */
void GH_PLL_set_HDMI_CTRL_use_hdmi_phy_clk_v(U8 data);
/*! \brief Reads the bit group 'use_hdmi_phy_clk_v' of register 'PLL_HDMI_CTRL'. */
U8   GH_PLL_get_HDMI_CTRL_use_hdmi_phy_clk_v(void);

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_SD48 (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_SCALER_SD48'. */
void GH_PLL_set_SCALER_SD48(U32 data);
/*! \brief Reads the register 'PLL_SCALER_SD48'. */
U32  GH_PLL_get_SCALER_SD48(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_SD48'. */
void GH_PLL_set_SCALER_SD48_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_SD48'. */
U16  GH_PLL_get_SCALER_SD48_Div(void);
/*! \brief Writes the bit group 'SDCLK_delay' of register 'PLL_SCALER_SD48'. */
void GH_PLL_set_SCALER_SD48_SDCLK_delay(U8 data);
/*! \brief Reads the bit group 'SDCLK_delay' of register 'PLL_SCALER_SD48'. */
U8   GH_PLL_get_SCALER_SD48_SDCLK_delay(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_VIDEO_CTRL (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_VIDEO_CTRL'. */
void GH_PLL_set_PLL_VIDEO_CTRL(U32 data);
/*! \brief Reads the register 'PLL_PLL_VIDEO_CTRL'. */
U32  GH_PLL_get_PLL_VIDEO_CTRL(void);
/*! \brief Writes the bit group 'WriteEnable' of register 'PLL_PLL_VIDEO_CTRL'. */
void GH_PLL_set_PLL_VIDEO_CTRL_WriteEnable(U8 data);
/*! \brief Reads the bit group 'WriteEnable' of register 'PLL_PLL_VIDEO_CTRL'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL_WriteEnable(void);
/*! \brief Writes the bit group 'BYPASS' of register 'PLL_PLL_VIDEO_CTRL'. */
void GH_PLL_set_PLL_VIDEO_CTRL_BYPASS(U8 data);
/*! \brief Reads the bit group 'BYPASS' of register 'PLL_PLL_VIDEO_CTRL'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL_BYPASS(void);
/*! \brief Writes the bit group 'Mode' of register 'PLL_PLL_VIDEO_CTRL'. */
void GH_PLL_set_PLL_VIDEO_CTRL_Mode(U8 data);
/*! \brief Reads the bit group 'Mode' of register 'PLL_PLL_VIDEO_CTRL'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL_Mode(void);
/*! \brief Writes the bit group 'reset' of register 'PLL_PLL_VIDEO_CTRL'. */
void GH_PLL_set_PLL_VIDEO_CTRL_reset(U8 data);
/*! \brief Reads the bit group 'reset' of register 'PLL_PLL_VIDEO_CTRL'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL_reset(void);
/*! \brief Writes the bit group 'PowerDown' of register 'PLL_PLL_VIDEO_CTRL'. */
void GH_PLL_set_PLL_VIDEO_CTRL_PowerDown(U8 data);
/*! \brief Reads the bit group 'PowerDown' of register 'PLL_PLL_VIDEO_CTRL'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL_PowerDown(void);
/*! \brief Writes the bit group 'HalfVCO' of register 'PLL_PLL_VIDEO_CTRL'. */
void GH_PLL_set_PLL_VIDEO_CTRL_HalfVCO(U8 data);
/*! \brief Reads the bit group 'HalfVCO' of register 'PLL_PLL_VIDEO_CTRL'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL_HalfVCO(void);
/*! \brief Writes the bit group 'Tristate' of register 'PLL_PLL_VIDEO_CTRL'. */
void GH_PLL_set_PLL_VIDEO_CTRL_Tristate(U8 data);
/*! \brief Reads the bit group 'Tristate' of register 'PLL_PLL_VIDEO_CTRL'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL_Tristate(void);
/*! \brief Writes the bit group 'pll_tout_async' of register 'PLL_PLL_VIDEO_CTRL'. */
void GH_PLL_set_PLL_VIDEO_CTRL_pll_tout_async(U8 data);
/*! \brief Reads the bit group 'pll_tout_async' of register 'PLL_PLL_VIDEO_CTRL'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL_pll_tout_async(void);
/*! \brief Writes the bit group 'SDIV' of register 'PLL_PLL_VIDEO_CTRL'. */
void GH_PLL_set_PLL_VIDEO_CTRL_SDIV(U8 data);
/*! \brief Reads the bit group 'SDIV' of register 'PLL_PLL_VIDEO_CTRL'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL_SDIV(void);
/*! \brief Writes the bit group 'SOUT' of register 'PLL_PLL_VIDEO_CTRL'. */
void GH_PLL_set_PLL_VIDEO_CTRL_SOUT(U8 data);
/*! \brief Reads the bit group 'SOUT' of register 'PLL_PLL_VIDEO_CTRL'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL_SOUT(void);
/*! \brief Writes the bit group 'pll_lock' of register 'PLL_PLL_VIDEO_CTRL'. */
void GH_PLL_set_PLL_VIDEO_CTRL_pll_lock(U8 data);
/*! \brief Reads the bit group 'pll_lock' of register 'PLL_PLL_VIDEO_CTRL'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL_pll_lock(void);
/*! \brief Writes the bit group 'gclk_vo' of register 'PLL_PLL_VIDEO_CTRL'. */
void GH_PLL_set_PLL_VIDEO_CTRL_gclk_vo(U8 data);
/*! \brief Reads the bit group 'gclk_vo' of register 'PLL_PLL_VIDEO_CTRL'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL_gclk_vo(void);
/*! \brief Writes the bit group 'INTPROG' of register 'PLL_PLL_VIDEO_CTRL'. */
void GH_PLL_set_PLL_VIDEO_CTRL_INTPROG(U8 data);
/*! \brief Reads the bit group 'INTPROG' of register 'PLL_PLL_VIDEO_CTRL'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL_INTPROG(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_VIDEO_FRAC (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_VIDEO_FRAC'. */
void GH_PLL_set_PLL_VIDEO_FRAC(U32 data);
/*! \brief Reads the register 'PLL_PLL_VIDEO_FRAC'. */
U32  GH_PLL_get_PLL_VIDEO_FRAC(void);

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_VIDEO (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_SCALER_VIDEO'. */
void GH_PLL_set_SCALER_VIDEO(U32 data);
/*! \brief Reads the register 'PLL_SCALER_VIDEO'. */
U32  GH_PLL_get_SCALER_VIDEO(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_VIDEO'. */
void GH_PLL_set_SCALER_VIDEO_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_VIDEO'. */
U16  GH_PLL_get_SCALER_VIDEO_Div(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_SENSOR_CTRL (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_SENSOR_CTRL'. */
void GH_PLL_set_PLL_SENSOR_CTRL(U32 data);
/*! \brief Reads the register 'PLL_PLL_SENSOR_CTRL'. */
U32  GH_PLL_get_PLL_SENSOR_CTRL(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_SENSOR_FRAC (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_SENSOR_FRAC'. */
void GH_PLL_set_PLL_SENSOR_FRAC(U32 data);
/*! \brief Reads the register 'PLL_PLL_SENSOR_FRAC'. */
U32  GH_PLL_get_PLL_SENSOR_FRAC(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_LOCK (read)                                               */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'PLL_PLL_LOCK'. */
U32  GH_PLL_get_PLL_LOCK(void);
/*! \brief Reads the bit group 'PLL_VIDEO2' of register 'PLL_PLL_LOCK'. */
U8   GH_PLL_get_PLL_LOCK_PLL_VIDEO2(void);
/*! \brief Reads the bit group 'PLL_VIDEO' of register 'PLL_PLL_LOCK'. */
U8   GH_PLL_get_PLL_LOCK_PLL_VIDEO(void);
/*! \brief Reads the bit group 'PLL_USB' of register 'PLL_PLL_LOCK'. */
U8   GH_PLL_get_PLL_LOCK_PLL_USB(void);
/*! \brief Reads the bit group 'PLL_SENSOR' of register 'PLL_PLL_LOCK'. */
U8   GH_PLL_get_PLL_LOCK_PLL_SENSOR(void);
/*! \brief Reads the bit group 'PLL_IDSP' of register 'PLL_PLL_LOCK'. */
U8   GH_PLL_get_PLL_LOCK_PLL_IDSP(void);
/*! \brief Reads the bit group 'PLL_DDR' of register 'PLL_PLL_LOCK'. */
U8   GH_PLL_get_PLL_LOCK_PLL_DDR(void);
/*! \brief Reads the bit group 'PLL_CORE' of register 'PLL_PLL_LOCK'. */
U8   GH_PLL_get_PLL_LOCK_PLL_CORE(void);
/*! \brief Reads the bit group 'PLL_AUDIO' of register 'PLL_PLL_LOCK'. */
U8   GH_PLL_get_PLL_LOCK_PLL_AUDIO(void);
/*! \brief Reads the bit group 'PLL_HDMI' of register 'PLL_PLL_LOCK'. */
U8   GH_PLL_get_PLL_LOCK_PLL_HDMI(void);
/*! \brief Reads the bit group 'PLL_VIN' of register 'PLL_PLL_LOCK'. */
U8   GH_PLL_get_PLL_LOCK_PLL_VIN(void);

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_SENSOR_POST (read/write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_SCALER_SENSOR_POST'. */
void GH_PLL_set_SCALER_SENSOR_POST(U32 data);
/*! \brief Reads the register 'PLL_SCALER_SENSOR_POST'. */
U32  GH_PLL_get_SCALER_SENSOR_POST(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_SENSOR_POST'. */
void GH_PLL_set_SCALER_SENSOR_POST_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_SENSOR_POST'. */
U16  GH_PLL_get_SCALER_SENSOR_POST_Div(void);

/*----------------------------------------------------------------------------*/
/* register PLL_SYS_CONFIG (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG(U32 data);
/*! \brief Reads the register 'PLL_SYS_CONFIG'. */
U32  GH_PLL_get_SYS_CONFIG(void);
/*! \brief Writes the bit group 'BootMedia' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_BootMedia(U8 data);
/*! \brief Reads the bit group 'BootMedia' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_BootMedia(void);
/*! \brief Writes the bit group 'clock' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_clock(U8 data);
/*! \brief Reads the bit group 'clock' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_clock(void);
/*! \brief Writes the bit group 'grst' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_grst(U8 data);
/*! \brief Reads the bit group 'grst' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_grst(void);
/*! \brief Writes the bit group 'page_size' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_page_size(U8 data);
/*! \brief Reads the bit group 'page_size' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_page_size(void);
/*! \brief Writes the bit group 'read' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_read(U8 data);
/*! \brief Reads the bit group 'read' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_read(void);
/*! \brief Writes the bit group 'enet' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_enet(U8 data);
/*! \brief Reads the bit group 'enet' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_enet(void);
/*! \brief Writes the bit group 'Boot_Bypass' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_Boot_Bypass(U8 data);
/*! \brief Reads the bit group 'Boot_Bypass' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_Boot_Bypass(void);
/*! \brief Writes the bit group 'fastboot' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_fastboot(U8 data);
/*! \brief Reads the bit group 'fastboot' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_fastboot(void);
/*! \brief Writes the bit group 'IO_Flash_boot' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_IO_Flash_boot(U8 data);
/*! \brief Reads the bit group 'IO_Flash_boot' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_IO_Flash_boot(void);
/*! \brief Writes the bit group 'SD_BOOT' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_SD_BOOT(U8 data);
/*! \brief Reads the bit group 'SD_BOOT' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_SD_BOOT(void);
/*! \brief Writes the bit group 'EMA_SEL' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_EMA_SEL(U8 data);
/*! \brief Reads the bit group 'EMA_SEL' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_EMA_SEL(void);
/*! \brief Writes the bit group 'lock_mode' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_lock_mode(U8 data);
/*! \brief Reads the bit group 'lock_mode' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_lock_mode(void);
/*! \brief Writes the bit group 'grst_l' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_grst_l(U8 data);
/*! \brief Reads the bit group 'grst_l' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_grst_l(void);
/*! \brief Writes the bit group 'RMII_SEL' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_RMII_SEL(U8 data);
/*! \brief Reads the bit group 'RMII_SEL' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_RMII_SEL(void);
/*! \brief Writes the bit group 'spi_boot' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_spi_boot(U8 data);
/*! \brief Reads the bit group 'spi_boot' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_spi_boot(void);
/*! \brief Writes the bit group 'hif_en' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_hif_en(U8 data);
/*! \brief Reads the bit group 'hif_en' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_hif_en(void);
/*! \brief Writes the bit group 'FREE' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_FREE(U8 data);
/*! \brief Reads the bit group 'FREE' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_FREE(void);
/*! \brief Writes the bit group 'hif_type' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_hif_type(U8 data);
/*! \brief Reads the bit group 'hif_type' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_hif_type(void);
/*! \brief Writes the bit group 'rdy_pl' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_rdy_pl(U8 data);
/*! \brief Reads the bit group 'rdy_pl' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_rdy_pl(void);
/*! \brief Writes the bit group 'rct_ahb_hif_secure_mode' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_rct_ahb_hif_secure_mode(U8 data);
/*! \brief Reads the bit group 'rct_ahb_hif_secure_mode' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_rct_ahb_hif_secure_mode(void);
/*! \brief Writes the bit group 'usbp' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_usbp(U8 data);
/*! \brief Reads the bit group 'usbp' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_usbp(void);
/*! \brief Writes the bit group 'ref_clk_is_24Mhz' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_ref_clk_is_24Mhz(U8 data);
/*! \brief Reads the bit group 'ref_clk_is_24Mhz' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_ref_clk_is_24Mhz(void);
/*! \brief Writes the bit group 'rct_bira_efuse_disable' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_rct_bira_efuse_disable(U8 data);
/*! \brief Reads the bit group 'rct_bira_efuse_disable' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_rct_bira_efuse_disable(void);
/*! \brief Writes the bit group 'hardcoded' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_hardcoded(U8 data);
/*! \brief Reads the bit group 'hardcoded' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_hardcoded(void);
/*! \brief Writes the bit group 'source' of register 'PLL_SYS_CONFIG'. */
void GH_PLL_set_SYS_CONFIG_source(U8 data);
/*! \brief Reads the bit group 'source' of register 'PLL_SYS_CONFIG'. */
U8   GH_PLL_get_SYS_CONFIG_source(void);

/*----------------------------------------------------------------------------*/
/* register PLL_CG_UART (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_CG_UART'. */
void GH_PLL_set_CG_UART(U32 data);
/*! \brief Reads the register 'PLL_CG_UART'. */
U32  GH_PLL_get_CG_UART(void);

/*----------------------------------------------------------------------------*/
/* register PLL_CG_SSI (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_CG_SSI'. */
void GH_PLL_set_CG_SSI(U32 data);
/*! \brief Reads the register 'PLL_CG_SSI'. */
U32  GH_PLL_get_CG_SSI(void);

/*----------------------------------------------------------------------------*/
/* register PLL_CG_MOTOR (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_CG_MOTOR'. */
void GH_PLL_set_CG_MOTOR(U32 data);
/*! \brief Reads the register 'PLL_CG_MOTOR'. */
U32  GH_PLL_get_CG_MOTOR(void);

/*----------------------------------------------------------------------------*/
/* register PLL_CG_IR (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_CG_IR'. */
void GH_PLL_set_CG_IR(U32 data);
/*! \brief Reads the register 'PLL_CG_IR'. */
U32  GH_PLL_get_CG_IR(void);

/*----------------------------------------------------------------------------*/
/* register PLL_CG_HOST (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_CG_HOST'. */
void GH_PLL_set_CG_HOST(U32 data);
/*! \brief Reads the register 'PLL_CG_HOST'. */
U32  GH_PLL_get_CG_HOST(void);

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_SENSOR_PRE (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_SCALER_SENSOR_PRE'. */
void GH_PLL_set_SCALER_SENSOR_PRE(U32 data);
/*! \brief Reads the register 'PLL_SCALER_SENSOR_PRE'. */
U32  GH_PLL_get_SCALER_SENSOR_PRE(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_SENSOR_PRE'. */
void GH_PLL_set_SCALER_SENSOR_PRE_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_SENSOR_PRE'. */
U16  GH_PLL_get_SCALER_SENSOR_PRE_Div(void);

/*----------------------------------------------------------------------------*/
/* register PLL_ANA_PWR (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_ANA_PWR'. */
void GH_PLL_set_ANA_PWR(U32 data);
/*! \brief Reads the register 'PLL_ANA_PWR'. */
U32  GH_PLL_get_ANA_PWR(void);
/*! \brief Writes the bit group 'USBsuspend' of register 'PLL_ANA_PWR'. */
void GH_PLL_set_ANA_PWR_USBsuspend(U8 data);
/*! \brief Reads the bit group 'USBsuspend' of register 'PLL_ANA_PWR'. */
U8   GH_PLL_get_ANA_PWR_USBsuspend(void);
/*! \brief Writes the bit group 'suspendUSBP' of register 'PLL_ANA_PWR'. */
void GH_PLL_set_ANA_PWR_suspendUSBP(U8 data);
/*! \brief Reads the bit group 'suspendUSBP' of register 'PLL_ANA_PWR'. */
U8   GH_PLL_get_ANA_PWR_suspendUSBP(void);
/*! \brief Writes the bit group 'power_controller' of register 'PLL_ANA_PWR'. */
void GH_PLL_set_ANA_PWR_power_controller(U8 data);
/*! \brief Reads the bit group 'power_controller' of register 'PLL_ANA_PWR'. */
U8   GH_PLL_get_ANA_PWR_power_controller(void);
/*! \brief Writes the bit group 'DLLpowerdown' of register 'PLL_ANA_PWR'. */
void GH_PLL_set_ANA_PWR_DLLpowerdown(U8 data);
/*! \brief Reads the bit group 'DLLpowerdown' of register 'PLL_ANA_PWR'. */
U8   GH_PLL_get_ANA_PWR_DLLpowerdown(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_AUDIO_CTRL (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_AUDIO_CTRL'. */
void GH_PLL_set_PLL_AUDIO_CTRL(U32 data);
/*! \brief Reads the register 'PLL_PLL_AUDIO_CTRL'. */
U32  GH_PLL_get_PLL_AUDIO_CTRL(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_AUDIO_FRAC (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_AUDIO_FRAC'. */
void GH_PLL_set_PLL_AUDIO_FRAC(U32 data);
/*! \brief Reads the register 'PLL_PLL_AUDIO_FRAC'. */
U32  GH_PLL_get_PLL_AUDIO_FRAC(void);

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_AUDIO (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_SCALER_AUDIO'. */
void GH_PLL_set_SCALER_AUDIO(U32 data);
/*! \brief Reads the register 'PLL_SCALER_AUDIO'. */
U32  GH_PLL_get_SCALER_AUDIO(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_AUDIO'. */
void GH_PLL_set_SCALER_AUDIO_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_AUDIO'. */
U16  GH_PLL_get_SCALER_AUDIO_Div(void);

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_AUDIO_PRE (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_SCALER_AUDIO_PRE'. */
void GH_PLL_set_SCALER_AUDIO_PRE(U32 data);
/*! \brief Reads the register 'PLL_SCALER_AUDIO_PRE'. */
U32  GH_PLL_get_SCALER_AUDIO_PRE(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_AUDIO_PRE'. */
void GH_PLL_set_SCALER_AUDIO_PRE_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_AUDIO_PRE'. */
U16  GH_PLL_get_SCALER_AUDIO_PRE_Div(void);

/*----------------------------------------------------------------------------*/
/* register PLL_SOFT_OR_DLLRESET (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_SOFT_OR_DLLRESET'. */
void GH_PLL_set_SOFT_OR_DLLRESET(U32 data);
/*! \brief Reads the register 'PLL_SOFT_OR_DLLRESET'. */
U32  GH_PLL_get_SOFT_OR_DLLRESET(void);
/*! \brief Writes the bit group 'Softreset' of register 'PLL_SOFT_OR_DLLRESET'. */
void GH_PLL_set_SOFT_OR_DLLRESET_Softreset(U8 data);
/*! \brief Reads the bit group 'Softreset' of register 'PLL_SOFT_OR_DLLRESET'. */
U8   GH_PLL_get_SOFT_OR_DLLRESET_Softreset(void);
/*! \brief Writes the bit group 'dll_rst_l' of register 'PLL_SOFT_OR_DLLRESET'. */
void GH_PLL_set_SOFT_OR_DLLRESET_dll_rst_l(U8 data);
/*! \brief Reads the bit group 'dll_rst_l' of register 'PLL_SOFT_OR_DLLRESET'. */
U8   GH_PLL_get_SOFT_OR_DLLRESET_dll_rst_l(void);

/*----------------------------------------------------------------------------*/
/* register PLL_FIO_RESET (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_FIO_RESET'. */
void GH_PLL_set_FIO_RESET(U32 data);
/*! \brief Reads the register 'PLL_FIO_RESET'. */
U32  GH_PLL_get_FIO_RESET(void);
/*! \brief Writes the bit group 'flashreset' of register 'PLL_FIO_RESET'. */
void GH_PLL_set_FIO_RESET_flashreset(U8 data);
/*! \brief Reads the bit group 'flashreset' of register 'PLL_FIO_RESET'. */
U8   GH_PLL_get_FIO_RESET_flashreset(void);
/*! \brief Writes the bit group 'xdreset' of register 'PLL_FIO_RESET'. */
void GH_PLL_set_FIO_RESET_xdreset(U8 data);
/*! \brief Reads the bit group 'xdreset' of register 'PLL_FIO_RESET'. */
U8   GH_PLL_get_FIO_RESET_xdreset(void);
/*! \brief Writes the bit group 'cfreset' of register 'PLL_FIO_RESET'. */
void GH_PLL_set_FIO_RESET_cfreset(U8 data);
/*! \brief Reads the bit group 'cfreset' of register 'PLL_FIO_RESET'. */
U8   GH_PLL_get_FIO_RESET_cfreset(void);
/*! \brief Writes the bit group 'fioreset' of register 'PLL_FIO_RESET'. */
void GH_PLL_set_FIO_RESET_fioreset(U8 data);
/*! \brief Reads the bit group 'fioreset' of register 'PLL_FIO_RESET'. */
U8   GH_PLL_get_FIO_RESET_fioreset(void);

/*----------------------------------------------------------------------------*/
/* register PLL_WDT_RST_L (read)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'PLL_WDT_RST_L'. */
U32  GH_PLL_get_WDT_RST_L(void);

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_USB (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_SCALER_USB'. */
void GH_PLL_set_SCALER_USB(U32 data);
/*! \brief Reads the register 'PLL_SCALER_USB'. */
U32  GH_PLL_get_SCALER_USB(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_USB'. */
void GH_PLL_set_SCALER_USB_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_USB'. */
U16  GH_PLL_get_SCALER_USB_Div(void);

/*----------------------------------------------------------------------------*/
/* register PLL_CLK_DEBOUNCE (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_CLK_DEBOUNCE'. */
void GH_PLL_set_CLK_DEBOUNCE(U32 data);
/*! \brief Reads the register 'PLL_CLK_DEBOUNCE'. */
U32  GH_PLL_get_CLK_DEBOUNCE(void);

/*----------------------------------------------------------------------------*/
/* register PLL_CG_PWM (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_CG_PWM'. */
void GH_PLL_set_CG_PWM(U32 data);
/*! \brief Reads the register 'PLL_CG_PWM'. */
U32  GH_PLL_get_CG_PWM(void);

/*----------------------------------------------------------------------------*/
/* register PLL_USBP_CTRL (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_USBP_CTRL'. */
void GH_PLL_set_USBP_CTRL(U32 data);
/*! \brief Reads the register 'PLL_USBP_CTRL'. */
U32  GH_PLL_get_USBP_CTRL(void);
/*! \brief Writes the bit group 'refclkdiv' of register 'PLL_USBP_CTRL'. */
void GH_PLL_set_USBP_CTRL_refclkdiv(U8 data);
/*! \brief Reads the bit group 'refclkdiv' of register 'PLL_USBP_CTRL'. */
U8   GH_PLL_get_USBP_CTRL_refclkdiv(void);
/*! \brief Writes the bit group 'usbphy_reset' of register 'PLL_USBP_CTRL'. */
void GH_PLL_set_USBP_CTRL_usbphy_reset(U8 data);
/*! \brief Reads the bit group 'usbphy_reset' of register 'PLL_USBP_CTRL'. */
U8   GH_PLL_get_USBP_CTRL_usbphy_reset(void);
/*! \brief Writes the bit group 'refclksel' of register 'PLL_USBP_CTRL'. */
void GH_PLL_set_USBP_CTRL_refclksel(U8 data);
/*! \brief Reads the bit group 'refclksel' of register 'PLL_USBP_CTRL'. */
U8   GH_PLL_get_USBP_CTRL_refclksel(void);
/*! \brief Writes the bit group 'commononn' of register 'PLL_USBP_CTRL'. */
void GH_PLL_set_USBP_CTRL_commononn(U8 data);
/*! \brief Reads the bit group 'commononn' of register 'PLL_USBP_CTRL'. */
U8   GH_PLL_get_USBP_CTRL_commononn(void);
/*! \brief Writes the bit group 'compdistune' of register 'PLL_USBP_CTRL'. */
void GH_PLL_set_USBP_CTRL_compdistune(U8 data);
/*! \brief Reads the bit group 'compdistune' of register 'PLL_USBP_CTRL'. */
U8   GH_PLL_get_USBP_CTRL_compdistune(void);
/*! \brief Writes the bit group 'otgtune' of register 'PLL_USBP_CTRL'. */
void GH_PLL_set_USBP_CTRL_otgtune(U8 data);
/*! \brief Reads the bit group 'otgtune' of register 'PLL_USBP_CTRL'. */
U8   GH_PLL_get_USBP_CTRL_otgtune(void);
/*! \brief Writes the bit group 'sqrxtune' of register 'PLL_USBP_CTRL'. */
void GH_PLL_set_USBP_CTRL_sqrxtune(U8 data);
/*! \brief Reads the bit group 'sqrxtune' of register 'PLL_USBP_CTRL'. */
U8   GH_PLL_get_USBP_CTRL_sqrxtune(void);
/*! \brief Writes the bit group 'rxfslstune' of register 'PLL_USBP_CTRL'. */
void GH_PLL_set_USBP_CTRL_rxfslstune(U8 data);
/*! \brief Reads the bit group 'rxfslstune' of register 'PLL_USBP_CTRL'. */
U8   GH_PLL_get_USBP_CTRL_rxfslstune(void);
/*! \brief Writes the bit group 'txpreemphasistune' of register 'PLL_USBP_CTRL'. */
void GH_PLL_set_USBP_CTRL_txpreemphasistune(U8 data);
/*! \brief Reads the bit group 'txpreemphasistune' of register 'PLL_USBP_CTRL'. */
U8   GH_PLL_get_USBP_CTRL_txpreemphasistune(void);
/*! \brief Writes the bit group 'txrisetune' of register 'PLL_USBP_CTRL'. */
void GH_PLL_set_USBP_CTRL_txrisetune(U8 data);
/*! \brief Reads the bit group 'txrisetune' of register 'PLL_USBP_CTRL'. */
U8   GH_PLL_get_USBP_CTRL_txrisetune(void);
/*! \brief Writes the bit group 'txvreftune' of register 'PLL_USBP_CTRL'. */
void GH_PLL_set_USBP_CTRL_txvreftune(U8 data);
/*! \brief Reads the bit group 'txvreftune' of register 'PLL_USBP_CTRL'. */
U8   GH_PLL_get_USBP_CTRL_txvreftune(void);
/*! \brief Writes the bit group 'txhsxvtune' of register 'PLL_USBP_CTRL'. */
void GH_PLL_set_USBP_CTRL_txhsxvtune(U8 data);
/*! \brief Reads the bit group 'txhsxvtune' of register 'PLL_USBP_CTRL'. */
U8   GH_PLL_get_USBP_CTRL_txhsxvtune(void);
/*! \brief Writes the bit group 'ATERESET' of register 'PLL_USBP_CTRL'. */
void GH_PLL_set_USBP_CTRL_ATERESET(U8 data);
/*! \brief Reads the bit group 'ATERESET' of register 'PLL_USBP_CTRL'. */
U8   GH_PLL_get_USBP_CTRL_ATERESET(void);
/*! \brief Writes the bit group 'USBDCsoftreset' of register 'PLL_USBP_CTRL'. */
void GH_PLL_set_USBP_CTRL_USBDCsoftreset(U8 data);
/*! \brief Reads the bit group 'USBDCsoftreset' of register 'PLL_USBP_CTRL'. */
U8   GH_PLL_get_USBP_CTRL_USBDCsoftreset(void);
/*! \brief Writes the bit group 'SLEEPM' of register 'PLL_USBP_CTRL'. */
void GH_PLL_set_USBP_CTRL_SLEEPM(U8 data);
/*! \brief Reads the bit group 'SLEEPM' of register 'PLL_USBP_CTRL'. */
U8   GH_PLL_get_USBP_CTRL_SLEEPM(void);

/*----------------------------------------------------------------------------*/
/* register PLL_CKEN_VDSP (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_CKEN_VDSP'. */
void GH_PLL_set_CKEN_VDSP(U32 data);
/*! \brief Reads the register 'PLL_CKEN_VDSP'. */
U32  GH_PLL_get_CKEN_VDSP(void);
/*! \brief Writes the bit group 'cken_tsfm' of register 'PLL_CKEN_VDSP'. */
void GH_PLL_set_CKEN_VDSP_cken_tsfm(U8 data);
/*! \brief Reads the bit group 'cken_tsfm' of register 'PLL_CKEN_VDSP'. */
U8   GH_PLL_get_CKEN_VDSP_cken_tsfm(void);
/*! \brief Writes the bit group 'cken_code' of register 'PLL_CKEN_VDSP'. */
void GH_PLL_set_CKEN_VDSP_cken_code(U8 data);
/*! \brief Reads the bit group 'cken_code' of register 'PLL_CKEN_VDSP'. */
U8   GH_PLL_get_CKEN_VDSP_cken_code(void);
/*! \brief Writes the bit group 'cken_smem' of register 'PLL_CKEN_VDSP'. */
void GH_PLL_set_CKEN_VDSP_cken_smem(U8 data);
/*! \brief Reads the bit group 'cken_smem' of register 'PLL_CKEN_VDSP'. */
U8   GH_PLL_get_CKEN_VDSP_cken_smem(void);

/*----------------------------------------------------------------------------*/
/* register PLL_DLL0 (read/write)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_DLL0'. */
void GH_PLL_set_DLL0(U32 data);
/*! \brief Reads the register 'PLL_DLL0'. */
U32  GH_PLL_get_DLL0(void);
/*! \brief Writes the bit group 'DLL_SEL2' of register 'PLL_DLL0'. */
void GH_PLL_set_DLL0_DLL_SEL2(U8 data);
/*! \brief Reads the bit group 'DLL_SEL2' of register 'PLL_DLL0'. */
U8   GH_PLL_get_DLL0_DLL_SEL2(void);
/*! \brief Writes the bit group 'DLL_SEL1' of register 'PLL_DLL0'. */
void GH_PLL_set_DLL0_DLL_SEL1(U8 data);
/*! \brief Reads the bit group 'DLL_SEL1' of register 'PLL_DLL0'. */
U8   GH_PLL_get_DLL0_DLL_SEL1(void);
/*! \brief Writes the bit group 'DLL_SEL0' of register 'PLL_DLL0'. */
void GH_PLL_set_DLL0_DLL_SEL0(U8 data);
/*! \brief Reads the bit group 'DLL_SEL0' of register 'PLL_DLL0'. */
U8   GH_PLL_get_DLL0_DLL_SEL0(void);

/*----------------------------------------------------------------------------*/
/* register PLL_DLL1 (read/write)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_DLL1'. */
void GH_PLL_set_DLL1(U32 data);
/*! \brief Reads the register 'PLL_DLL1'. */
U32  GH_PLL_get_DLL1(void);
/*! \brief Writes the bit group 'DLL_SEL2' of register 'PLL_DLL1'. */
void GH_PLL_set_DLL1_DLL_SEL2(U8 data);
/*! \brief Reads the bit group 'DLL_SEL2' of register 'PLL_DLL1'. */
U8   GH_PLL_get_DLL1_DLL_SEL2(void);
/*! \brief Writes the bit group 'DLL_SEL1' of register 'PLL_DLL1'. */
void GH_PLL_set_DLL1_DLL_SEL1(U8 data);
/*! \brief Reads the bit group 'DLL_SEL1' of register 'PLL_DLL1'. */
U8   GH_PLL_get_DLL1_DLL_SEL1(void);
/*! \brief Writes the bit group 'DLL_SEL0' of register 'PLL_DLL1'. */
void GH_PLL_set_DLL1_DLL_SEL0(U8 data);
/*! \brief Reads the bit group 'DLL_SEL0' of register 'PLL_DLL1'. */
U8   GH_PLL_get_DLL1_DLL_SEL0(void);

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_ADC (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_SCALER_ADC'. */
void GH_PLL_set_SCALER_ADC(U32 data);
/*! \brief Reads the register 'PLL_SCALER_ADC'. */
U32  GH_PLL_get_SCALER_ADC(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_ADC'. */
void GH_PLL_set_SCALER_ADC_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_ADC'. */
U16  GH_PLL_get_SCALER_ADC_Div(void);

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_VIDEO_POST (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_SCALER_VIDEO_POST'. */
void GH_PLL_set_SCALER_VIDEO_POST(U32 data);
/*! \brief Reads the register 'PLL_SCALER_VIDEO_POST'. */
U32  GH_PLL_get_SCALER_VIDEO_POST(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_VIDEO_POST'. */
void GH_PLL_set_SCALER_VIDEO_POST_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_VIDEO_POST'. */
U16  GH_PLL_get_SCALER_VIDEO_POST_Div(void);

/*----------------------------------------------------------------------------*/
/* register PLL_CLK_REF_AU_EXTERNAL (read/write)                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_CLK_REF_AU_EXTERNAL'. */
void GH_PLL_set_CLK_REF_AU_EXTERNAL(U32 data);
/*! \brief Reads the register 'PLL_CLK_REF_AU_EXTERNAL'. */
U32  GH_PLL_get_CLK_REF_AU_EXTERNAL(void);
/*! \brief Writes the bit group 'external' of register 'PLL_CLK_REF_AU_EXTERNAL'. */
void GH_PLL_set_CLK_REF_AU_EXTERNAL_external(U8 data);
/*! \brief Reads the bit group 'external' of register 'PLL_CLK_REF_AU_EXTERNAL'. */
U8   GH_PLL_get_CLK_REF_AU_EXTERNAL_external(void);

/*----------------------------------------------------------------------------*/
/* register PLL_USE_EXTERNAL_CLK_AU (read/write)                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_USE_EXTERNAL_CLK_AU'. */
void GH_PLL_set_USE_EXTERNAL_CLK_AU(U32 data);
/*! \brief Reads the register 'PLL_USE_EXTERNAL_CLK_AU'. */
U32  GH_PLL_get_USE_EXTERNAL_CLK_AU(void);
/*! \brief Writes the bit group 'external' of register 'PLL_USE_EXTERNAL_CLK_AU'. */
void GH_PLL_set_USE_EXTERNAL_CLK_AU_external(U8 data);
/*! \brief Reads the bit group 'external' of register 'PLL_USE_EXTERNAL_CLK_AU'. */
U8   GH_PLL_get_USE_EXTERNAL_CLK_AU_external(void);

/*----------------------------------------------------------------------------*/
/* register PLL_CLK_REF_VIDEO_EXTERNAL (read/write)                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_CLK_REF_VIDEO_EXTERNAL'. */
void GH_PLL_set_CLK_REF_VIDEO_EXTERNAL(U32 data);
/*! \brief Reads the register 'PLL_CLK_REF_VIDEO_EXTERNAL'. */
U32  GH_PLL_get_CLK_REF_VIDEO_EXTERNAL(void);
/*! \brief Writes the bit group 'external' of register 'PLL_CLK_REF_VIDEO_EXTERNAL'. */
void GH_PLL_set_CLK_REF_VIDEO_EXTERNAL_external(U8 data);
/*! \brief Reads the bit group 'external' of register 'PLL_CLK_REF_VIDEO_EXTERNAL'. */
U8   GH_PLL_get_CLK_REF_VIDEO_EXTERNAL_external(void);

/*----------------------------------------------------------------------------*/
/* register PLL_USE_EXTERNAL_VD_CLK (read/write)                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_USE_EXTERNAL_VD_CLK'. */
void GH_PLL_set_USE_EXTERNAL_VD_CLK(U32 data);
/*! \brief Reads the register 'PLL_USE_EXTERNAL_VD_CLK'. */
U32  GH_PLL_get_USE_EXTERNAL_VD_CLK(void);
/*! \brief Writes the bit group 'external' of register 'PLL_USE_EXTERNAL_VD_CLK'. */
void GH_PLL_set_USE_EXTERNAL_VD_CLK_external(U8 data);
/*! \brief Reads the bit group 'external' of register 'PLL_USE_EXTERNAL_VD_CLK'. */
U8   GH_PLL_get_USE_EXTERNAL_VD_CLK_external(void);

/*----------------------------------------------------------------------------*/
/* register PLL_USE_CLK_SI_4_CLK_AU (read/write)                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_USE_CLK_SI_4_CLK_AU'. */
void GH_PLL_set_USE_CLK_SI_4_CLK_AU(U32 data);
/*! \brief Reads the register 'PLL_USE_CLK_SI_4_CLK_AU'. */
U32  GH_PLL_get_USE_CLK_SI_4_CLK_AU(void);
/*! \brief Writes the bit group 'PLLref' of register 'PLL_USE_CLK_SI_4_CLK_AU'. */
void GH_PLL_set_USE_CLK_SI_4_CLK_AU_PLLref(U8 data);
/*! \brief Reads the bit group 'PLLref' of register 'PLL_USE_CLK_SI_4_CLK_AU'. */
U8   GH_PLL_get_USE_CLK_SI_4_CLK_AU_PLLref(void);

/*----------------------------------------------------------------------------*/
/* register PLL_USE_CLK_SI_4_CLK_VO (read/write)                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_USE_CLK_SI_4_CLK_VO'. */
void GH_PLL_set_USE_CLK_SI_4_CLK_VO(U32 data);
/*! \brief Reads the register 'PLL_USE_CLK_SI_4_CLK_VO'. */
U32  GH_PLL_get_USE_CLK_SI_4_CLK_VO(void);
/*! \brief Writes the bit group 'PLLref' of register 'PLL_USE_CLK_SI_4_CLK_VO'. */
void GH_PLL_set_USE_CLK_SI_4_CLK_VO_PLLref(U8 data);
/*! \brief Reads the bit group 'PLLref' of register 'PLL_USE_CLK_SI_4_CLK_VO'. */
U8   GH_PLL_get_USE_CLK_SI_4_CLK_VO_PLLref(void);

/*----------------------------------------------------------------------------*/
/* register PLL_CLK_SI_INPUT_MODE (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_CLK_SI_INPUT_MODE'. */
void GH_PLL_set_CLK_SI_INPUT_MODE(U32 data);
/*! \brief Reads the register 'PLL_CLK_SI_INPUT_MODE'. */
U32  GH_PLL_get_CLK_SI_INPUT_MODE(void);
/*! \brief Writes the bit group 'clk_si' of register 'PLL_CLK_SI_INPUT_MODE'. */
void GH_PLL_set_CLK_SI_INPUT_MODE_clk_si(U8 data);
/*! \brief Reads the bit group 'clk_si' of register 'PLL_CLK_SI_INPUT_MODE'. */
U8   GH_PLL_get_CLK_SI_INPUT_MODE_clk_si(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_VIDEO2_CTRL (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_VIDEO2_CTRL'. */
void GH_PLL_set_PLL_VIDEO2_CTRL(U32 data);
/*! \brief Reads the register 'PLL_PLL_VIDEO2_CTRL'. */
U32  GH_PLL_get_PLL_VIDEO2_CTRL(void);
/*! \brief Writes the bit group 'pll_lock' of register 'PLL_PLL_VIDEO2_CTRL'. */
void GH_PLL_set_PLL_VIDEO2_CTRL_pll_lock(U8 data);
/*! \brief Reads the bit group 'pll_lock' of register 'PLL_PLL_VIDEO2_CTRL'. */
U8   GH_PLL_get_PLL_VIDEO2_CTRL_pll_lock(void);
/*! \brief Writes the bit group 'gclk_vo' of register 'PLL_PLL_VIDEO2_CTRL'. */
void GH_PLL_set_PLL_VIDEO2_CTRL_gclk_vo(U8 data);
/*! \brief Reads the bit group 'gclk_vo' of register 'PLL_PLL_VIDEO2_CTRL'. */
U8   GH_PLL_get_PLL_VIDEO2_CTRL_gclk_vo(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_VIDEO2_FRAC (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_VIDEO2_FRAC'. */
void GH_PLL_set_PLL_VIDEO2_FRAC(U32 data);
/*! \brief Reads the register 'PLL_PLL_VIDEO2_FRAC'. */
U32  GH_PLL_get_PLL_VIDEO2_FRAC(void);

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_VIDEO2 (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_SCALER_VIDEO2'. */
void GH_PLL_set_SCALER_VIDEO2(U32 data);
/*! \brief Reads the register 'PLL_SCALER_VIDEO2'. */
U32  GH_PLL_get_SCALER_VIDEO2(void);
/*! \brief Writes the bit group 'IntegerDiv' of register 'PLL_SCALER_VIDEO2'. */
void GH_PLL_set_SCALER_VIDEO2_IntegerDiv(U16 data);
/*! \brief Reads the bit group 'IntegerDiv' of register 'PLL_SCALER_VIDEO2'. */
U16  GH_PLL_get_SCALER_VIDEO2_IntegerDiv(void);
/*! \brief Writes the bit group 'PrimeDiv' of register 'PLL_SCALER_VIDEO2'. */
void GH_PLL_set_SCALER_VIDEO2_PrimeDiv(U8 data);
/*! \brief Reads the bit group 'PrimeDiv' of register 'PLL_SCALER_VIDEO2'. */
U8   GH_PLL_get_SCALER_VIDEO2_PrimeDiv(void);
/*! \brief Writes the bit group 'DutyCycle' of register 'PLL_SCALER_VIDEO2'. */
void GH_PLL_set_SCALER_VIDEO2_DutyCycle(U8 data);
/*! \brief Reads the bit group 'DutyCycle' of register 'PLL_SCALER_VIDEO2'. */
U8   GH_PLL_get_SCALER_VIDEO2_DutyCycle(void);

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_VIDEO2_POST (read/write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_SCALER_VIDEO2_POST'. */
void GH_PLL_set_SCALER_VIDEO2_POST(U32 data);
/*! \brief Reads the register 'PLL_SCALER_VIDEO2_POST'. */
U32  GH_PLL_get_SCALER_VIDEO2_POST(void);
/*! \brief Writes the bit group 'IntegerDiv' of register 'PLL_SCALER_VIDEO2_POST'. */
void GH_PLL_set_SCALER_VIDEO2_POST_IntegerDiv(U16 data);
/*! \brief Reads the bit group 'IntegerDiv' of register 'PLL_SCALER_VIDEO2_POST'. */
U16  GH_PLL_get_SCALER_VIDEO2_POST_IntegerDiv(void);
/*! \brief Writes the bit group 'PrimeDiv' of register 'PLL_SCALER_VIDEO2_POST'. */
void GH_PLL_set_SCALER_VIDEO2_POST_PrimeDiv(U8 data);
/*! \brief Reads the bit group 'PrimeDiv' of register 'PLL_SCALER_VIDEO2_POST'. */
U8   GH_PLL_get_SCALER_VIDEO2_POST_PrimeDiv(void);
/*! \brief Writes the bit group 'DutyCycle' of register 'PLL_SCALER_VIDEO2_POST'. */
void GH_PLL_set_SCALER_VIDEO2_POST_DutyCycle(U8 data);
/*! \brief Reads the bit group 'DutyCycle' of register 'PLL_SCALER_VIDEO2_POST'. */
U8   GH_PLL_get_SCALER_VIDEO2_POST_DutyCycle(void);

/*----------------------------------------------------------------------------*/
/* register PLL_USE_CLK_SI_4_CLK_VO2 (read/write)                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_USE_CLK_SI_4_CLK_VO2'. */
void GH_PLL_set_USE_CLK_SI_4_CLK_VO2(U32 data);
/*! \brief Reads the register 'PLL_USE_CLK_SI_4_CLK_VO2'. */
U32  GH_PLL_get_USE_CLK_SI_4_CLK_VO2(void);
/*! \brief Writes the bit group 'PLLref' of register 'PLL_USE_CLK_SI_4_CLK_VO2'. */
void GH_PLL_set_USE_CLK_SI_4_CLK_VO2_PLLref(U8 data);
/*! \brief Reads the bit group 'PLLref' of register 'PLL_USE_CLK_SI_4_CLK_VO2'. */
U8   GH_PLL_get_USE_CLK_SI_4_CLK_VO2_PLLref(void);

/*----------------------------------------------------------------------------*/
/* register PLL_USE_EXTERNAL_VD2_CLK (read/write)                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_USE_EXTERNAL_VD2_CLK'. */
void GH_PLL_set_USE_EXTERNAL_VD2_CLK(U32 data);
/*! \brief Reads the register 'PLL_USE_EXTERNAL_VD2_CLK'. */
U32  GH_PLL_get_USE_EXTERNAL_VD2_CLK(void);
/*! \brief Writes the bit group 'external' of register 'PLL_USE_EXTERNAL_VD2_CLK'. */
void GH_PLL_set_USE_EXTERNAL_VD2_CLK_external(U8 data);
/*! \brief Reads the bit group 'external' of register 'PLL_USE_EXTERNAL_VD2_CLK'. */
U8   GH_PLL_get_USE_EXTERNAL_VD2_CLK_external(void);

/*----------------------------------------------------------------------------*/
/* register PLL_CLK_REF_VIDEO2_EXTERNAL (read/write)                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_CLK_REF_VIDEO2_EXTERNAL'. */
void GH_PLL_set_CLK_REF_VIDEO2_EXTERNAL(U32 data);
/*! \brief Reads the register 'PLL_CLK_REF_VIDEO2_EXTERNAL'. */
U32  GH_PLL_get_CLK_REF_VIDEO2_EXTERNAL(void);
/*! \brief Writes the bit group 'external' of register 'PLL_CLK_REF_VIDEO2_EXTERNAL'. */
void GH_PLL_set_CLK_REF_VIDEO2_EXTERNAL_external(U8 data);
/*! \brief Reads the bit group 'external' of register 'PLL_CLK_REF_VIDEO2_EXTERNAL'. */
U8   GH_PLL_get_CLK_REF_VIDEO2_EXTERNAL_external(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_DDR_CTRL (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_DDR_CTRL'. */
void GH_PLL_set_PLL_DDR_CTRL(U32 data);
/*! \brief Reads the register 'PLL_PLL_DDR_CTRL'. */
U32  GH_PLL_get_PLL_DDR_CTRL(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_DDR_FRAC (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_DDR_FRAC'. */
void GH_PLL_set_PLL_DDR_FRAC(U32 data);
/*! \brief Reads the register 'PLL_PLL_DDR_FRAC'. */
U32  GH_PLL_get_PLL_DDR_FRAC(void);
/*! \brief Writes the bit group 'fraction' of register 'PLL_PLL_DDR_FRAC'. */
void GH_PLL_set_PLL_DDR_FRAC_fraction(U16 data);
/*! \brief Reads the bit group 'fraction' of register 'PLL_PLL_DDR_FRAC'. */
U16  GH_PLL_get_PLL_DDR_FRAC_fraction(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_IDSP_CTRL (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_IDSP_CTRL'. */
void GH_PLL_set_PLL_IDSP_CTRL(U32 data);
/*! \brief Reads the register 'PLL_PLL_IDSP_CTRL'. */
U32  GH_PLL_get_PLL_IDSP_CTRL(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_IDSP_FRAC (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_IDSP_FRAC'. */
void GH_PLL_set_PLL_IDSP_FRAC(U32 data);
/*! \brief Reads the register 'PLL_PLL_IDSP_FRAC'. */
U32  GH_PLL_get_PLL_IDSP_FRAC(void);
/*! \brief Writes the bit group 'fraction' of register 'PLL_PLL_IDSP_FRAC'. */
void GH_PLL_set_PLL_IDSP_FRAC_fraction(U16 data);
/*! \brief Reads the bit group 'fraction' of register 'PLL_PLL_IDSP_FRAC'. */
U16  GH_PLL_get_PLL_IDSP_FRAC_fraction(void);

/*----------------------------------------------------------------------------*/
/* register PLL_CG_SSI2 (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_CG_SSI2'. */
void GH_PLL_set_CG_SSI2(U32 data);
/*! \brief Reads the register 'PLL_CG_SSI2'. */
U32  GH_PLL_get_CG_SSI2(void);

/*----------------------------------------------------------------------------*/
/* register PLL_LVDS_LVCMOS (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_LVDS_LVCMOS'. */
void GH_PLL_set_LVDS_LVCMOS(U32 data);
/*! \brief Reads the register 'PLL_LVDS_LVCMOS'. */
U32  GH_PLL_get_LVDS_LVCMOS(void);
/*! \brief Writes the bit group 'lvcoms_sd' of register 'PLL_LVDS_LVCMOS'. */
void GH_PLL_set_LVDS_LVCMOS_lvcoms_sd(U16 data);
/*! \brief Reads the bit group 'lvcoms_sd' of register 'PLL_LVDS_LVCMOS'. */
U16  GH_PLL_get_LVDS_LVCMOS_lvcoms_sd(void);
/*! \brief Writes the bit group 'lvcmos_spclk' of register 'PLL_LVDS_LVCMOS'. */
void GH_PLL_set_LVDS_LVCMOS_lvcmos_spclk(U8 data);
/*! \brief Reads the bit group 'lvcmos_spclk' of register 'PLL_LVDS_LVCMOS'. */
U8   GH_PLL_get_LVDS_LVCMOS_lvcmos_spclk(void);

/*----------------------------------------------------------------------------*/
/* register PLL_LVDS_ASYNC (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_LVDS_ASYNC'. */
void GH_PLL_set_LVDS_ASYNC(U32 data);
/*! \brief Reads the register 'PLL_LVDS_ASYNC'. */
U32  GH_PLL_get_LVDS_ASYNC(void);
/*! \brief Writes the bit group 'async_sd' of register 'PLL_LVDS_ASYNC'. */
void GH_PLL_set_LVDS_ASYNC_async_sd(U16 data);
/*! \brief Reads the bit group 'async_sd' of register 'PLL_LVDS_ASYNC'. */
U16  GH_PLL_get_LVDS_ASYNC_async_sd(void);
/*! \brief Writes the bit group 'async_spclk' of register 'PLL_LVDS_ASYNC'. */
void GH_PLL_set_LVDS_ASYNC_async_spclk(U8 data);
/*! \brief Reads the bit group 'async_spclk' of register 'PLL_LVDS_ASYNC'. */
U8   GH_PLL_get_LVDS_ASYNC_async_spclk(void);
/*! \brief Writes the bit group 'lvds_pd' of register 'PLL_LVDS_ASYNC'. */
void GH_PLL_set_LVDS_ASYNC_lvds_pd(U8 data);
/*! \brief Reads the bit group 'lvds_pd' of register 'PLL_LVDS_ASYNC'. */
U8   GH_PLL_get_LVDS_ASYNC_lvds_pd(void);
/*! \brief Writes the bit group 'lvds_ib_ctrl' of register 'PLL_LVDS_ASYNC'. */
void GH_PLL_set_LVDS_ASYNC_lvds_ib_ctrl(U8 data);
/*! \brief Reads the bit group 'lvds_ib_ctrl' of register 'PLL_LVDS_ASYNC'. */
U8   GH_PLL_get_LVDS_ASYNC_lvds_ib_ctrl(void);
/*! \brief Writes the bit group 'lvds_bit_mode' of register 'PLL_LVDS_ASYNC'. */
void GH_PLL_set_LVDS_ASYNC_lvds_bit_mode(U8 data);
/*! \brief Reads the bit group 'lvds_bit_mode' of register 'PLL_LVDS_ASYNC'. */
U8   GH_PLL_get_LVDS_ASYNC_lvds_bit_mode(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_CORE_CTRL2 (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_CORE_CTRL2'. */
void GH_PLL_set_PLL_CORE_CTRL2(U32 data);
/*! \brief Reads the register 'PLL_PLL_CORE_CTRL2'. */
U32  GH_PLL_get_PLL_CORE_CTRL2(void);
/*! \brief Writes the bit group 'Controllability' of register 'PLL_PLL_CORE_CTRL2'. */
void GH_PLL_set_PLL_CORE_CTRL2_Controllability(U16 data);
/*! \brief Reads the bit group 'Controllability' of register 'PLL_PLL_CORE_CTRL2'. */
U16  GH_PLL_get_PLL_CORE_CTRL2_Controllability(void);
/*! \brief Writes the bit group 'Charge' of register 'PLL_PLL_CORE_CTRL2'. */
void GH_PLL_set_PLL_CORE_CTRL2_Charge(U8 data);
/*! \brief Reads the bit group 'Charge' of register 'PLL_PLL_CORE_CTRL2'. */
U8   GH_PLL_get_PLL_CORE_CTRL2_Charge(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_CORE_CTRL3 (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_CORE_CTRL3'. */
void GH_PLL_set_PLL_CORE_CTRL3(U32 data);
/*! \brief Reads the register 'PLL_PLL_CORE_CTRL3'. */
U32  GH_PLL_get_PLL_CORE_CTRL3(void);
/*! \brief Writes the bit group 'VCO' of register 'PLL_PLL_CORE_CTRL3'. */
void GH_PLL_set_PLL_CORE_CTRL3_VCO(U8 data);
/*! \brief Reads the bit group 'VCO' of register 'PLL_PLL_CORE_CTRL3'. */
U8   GH_PLL_get_PLL_CORE_CTRL3_VCO(void);
/*! \brief Writes the bit group 'PLL_VCO' of register 'PLL_PLL_CORE_CTRL3'. */
void GH_PLL_set_PLL_CORE_CTRL3_PLL_VCO(U8 data);
/*! \brief Reads the bit group 'PLL_VCO' of register 'PLL_PLL_CORE_CTRL3'. */
U8   GH_PLL_get_PLL_CORE_CTRL3_PLL_VCO(void);
/*! \brief Writes the bit group 'Clamp' of register 'PLL_PLL_CORE_CTRL3'. */
void GH_PLL_set_PLL_CORE_CTRL3_Clamp(U8 data);
/*! \brief Reads the bit group 'Clamp' of register 'PLL_PLL_CORE_CTRL3'. */
U8   GH_PLL_get_PLL_CORE_CTRL3_Clamp(void);
/*! \brief Writes the bit group 'DSM_dither' of register 'PLL_PLL_CORE_CTRL3'. */
void GH_PLL_set_PLL_CORE_CTRL3_DSM_dither(U8 data);
/*! \brief Reads the bit group 'DSM_dither' of register 'PLL_PLL_CORE_CTRL3'. */
U8   GH_PLL_get_PLL_CORE_CTRL3_DSM_dither(void);
/*! \brief Writes the bit group 'DSM_dither_gain' of register 'PLL_PLL_CORE_CTRL3'. */
void GH_PLL_set_PLL_CORE_CTRL3_DSM_dither_gain(U8 data);
/*! \brief Reads the bit group 'DSM_dither_gain' of register 'PLL_PLL_CORE_CTRL3'. */
U8   GH_PLL_get_PLL_CORE_CTRL3_DSM_dither_gain(void);
/*! \brief Writes the bit group 'Feedforward' of register 'PLL_PLL_CORE_CTRL3'. */
void GH_PLL_set_PLL_CORE_CTRL3_Feedforward(U8 data);
/*! \brief Reads the bit group 'Feedforward' of register 'PLL_PLL_CORE_CTRL3'. */
U8   GH_PLL_get_PLL_CORE_CTRL3_Feedforward(void);
/*! \brief Writes the bit group 'Bias' of register 'PLL_PLL_CORE_CTRL3'. */
void GH_PLL_set_PLL_CORE_CTRL3_Bias(U8 data);
/*! \brief Reads the bit group 'Bias' of register 'PLL_PLL_CORE_CTRL3'. */
U8   GH_PLL_get_PLL_CORE_CTRL3_Bias(void);
/*! \brief Writes the bit group 'JDIV' of register 'PLL_PLL_CORE_CTRL3'. */
void GH_PLL_set_PLL_CORE_CTRL3_JDIV(U8 data);
/*! \brief Reads the bit group 'JDIV' of register 'PLL_PLL_CORE_CTRL3'. */
U8   GH_PLL_get_PLL_CORE_CTRL3_JDIV(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_IDSP_CTRL2 (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_IDSP_CTRL2'. */
void GH_PLL_set_PLL_IDSP_CTRL2(U32 data);
/*! \brief Reads the register 'PLL_PLL_IDSP_CTRL2'. */
U32  GH_PLL_get_PLL_IDSP_CTRL2(void);
/*! \brief Writes the bit group 'Controllability' of register 'PLL_PLL_IDSP_CTRL2'. */
void GH_PLL_set_PLL_IDSP_CTRL2_Controllability(U16 data);
/*! \brief Reads the bit group 'Controllability' of register 'PLL_PLL_IDSP_CTRL2'. */
U16  GH_PLL_get_PLL_IDSP_CTRL2_Controllability(void);
/*! \brief Writes the bit group 'Charge' of register 'PLL_PLL_IDSP_CTRL2'. */
void GH_PLL_set_PLL_IDSP_CTRL2_Charge(U8 data);
/*! \brief Reads the bit group 'Charge' of register 'PLL_PLL_IDSP_CTRL2'. */
U8   GH_PLL_get_PLL_IDSP_CTRL2_Charge(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_IDSP_CTRL3 (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_IDSP_CTRL3'. */
void GH_PLL_set_PLL_IDSP_CTRL3(U32 data);
/*! \brief Reads the register 'PLL_PLL_IDSP_CTRL3'. */
U32  GH_PLL_get_PLL_IDSP_CTRL3(void);
/*! \brief Writes the bit group 'VCO' of register 'PLL_PLL_IDSP_CTRL3'. */
void GH_PLL_set_PLL_IDSP_CTRL3_VCO(U8 data);
/*! \brief Reads the bit group 'VCO' of register 'PLL_PLL_IDSP_CTRL3'. */
U8   GH_PLL_get_PLL_IDSP_CTRL3_VCO(void);
/*! \brief Writes the bit group 'PLL_VCO' of register 'PLL_PLL_IDSP_CTRL3'. */
void GH_PLL_set_PLL_IDSP_CTRL3_PLL_VCO(U8 data);
/*! \brief Reads the bit group 'PLL_VCO' of register 'PLL_PLL_IDSP_CTRL3'. */
U8   GH_PLL_get_PLL_IDSP_CTRL3_PLL_VCO(void);
/*! \brief Writes the bit group 'Clamp' of register 'PLL_PLL_IDSP_CTRL3'. */
void GH_PLL_set_PLL_IDSP_CTRL3_Clamp(U8 data);
/*! \brief Reads the bit group 'Clamp' of register 'PLL_PLL_IDSP_CTRL3'. */
U8   GH_PLL_get_PLL_IDSP_CTRL3_Clamp(void);
/*! \brief Writes the bit group 'DSM_dither' of register 'PLL_PLL_IDSP_CTRL3'. */
void GH_PLL_set_PLL_IDSP_CTRL3_DSM_dither(U8 data);
/*! \brief Reads the bit group 'DSM_dither' of register 'PLL_PLL_IDSP_CTRL3'. */
U8   GH_PLL_get_PLL_IDSP_CTRL3_DSM_dither(void);
/*! \brief Writes the bit group 'DSM_dither_gain' of register 'PLL_PLL_IDSP_CTRL3'. */
void GH_PLL_set_PLL_IDSP_CTRL3_DSM_dither_gain(U8 data);
/*! \brief Reads the bit group 'DSM_dither_gain' of register 'PLL_PLL_IDSP_CTRL3'. */
U8   GH_PLL_get_PLL_IDSP_CTRL3_DSM_dither_gain(void);
/*! \brief Writes the bit group 'Feedforward' of register 'PLL_PLL_IDSP_CTRL3'. */
void GH_PLL_set_PLL_IDSP_CTRL3_Feedforward(U8 data);
/*! \brief Reads the bit group 'Feedforward' of register 'PLL_PLL_IDSP_CTRL3'. */
U8   GH_PLL_get_PLL_IDSP_CTRL3_Feedforward(void);
/*! \brief Writes the bit group 'Bias' of register 'PLL_PLL_IDSP_CTRL3'. */
void GH_PLL_set_PLL_IDSP_CTRL3_Bias(U8 data);
/*! \brief Reads the bit group 'Bias' of register 'PLL_PLL_IDSP_CTRL3'. */
U8   GH_PLL_get_PLL_IDSP_CTRL3_Bias(void);
/*! \brief Writes the bit group 'JDIV' of register 'PLL_PLL_IDSP_CTRL3'. */
void GH_PLL_set_PLL_IDSP_CTRL3_JDIV(U8 data);
/*! \brief Reads the bit group 'JDIV' of register 'PLL_PLL_IDSP_CTRL3'. */
U8   GH_PLL_get_PLL_IDSP_CTRL3_JDIV(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_IDSP_CTRL22 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_IDSP_CTRL22'. */
void GH_PLL_set_PLL_IDSP_CTRL22(U32 data);
/*! \brief Reads the register 'PLL_PLL_IDSP_CTRL22'. */
U32  GH_PLL_get_PLL_IDSP_CTRL22(void);
/*! \brief Writes the bit group 'Controllability' of register 'PLL_PLL_IDSP_CTRL22'. */
void GH_PLL_set_PLL_IDSP_CTRL22_Controllability(U16 data);
/*! \brief Reads the bit group 'Controllability' of register 'PLL_PLL_IDSP_CTRL22'. */
U16  GH_PLL_get_PLL_IDSP_CTRL22_Controllability(void);
/*! \brief Writes the bit group 'Charge' of register 'PLL_PLL_IDSP_CTRL22'. */
void GH_PLL_set_PLL_IDSP_CTRL22_Charge(U8 data);
/*! \brief Reads the bit group 'Charge' of register 'PLL_PLL_IDSP_CTRL22'. */
U8   GH_PLL_get_PLL_IDSP_CTRL22_Charge(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_IDSP_CTRL32 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_IDSP_CTRL32'. */
void GH_PLL_set_PLL_IDSP_CTRL32(U32 data);
/*! \brief Reads the register 'PLL_PLL_IDSP_CTRL32'. */
U32  GH_PLL_get_PLL_IDSP_CTRL32(void);
/*! \brief Writes the bit group 'VCO' of register 'PLL_PLL_IDSP_CTRL32'. */
void GH_PLL_set_PLL_IDSP_CTRL32_VCO(U8 data);
/*! \brief Reads the bit group 'VCO' of register 'PLL_PLL_IDSP_CTRL32'. */
U8   GH_PLL_get_PLL_IDSP_CTRL32_VCO(void);
/*! \brief Writes the bit group 'PLL_VCO' of register 'PLL_PLL_IDSP_CTRL32'. */
void GH_PLL_set_PLL_IDSP_CTRL32_PLL_VCO(U8 data);
/*! \brief Reads the bit group 'PLL_VCO' of register 'PLL_PLL_IDSP_CTRL32'. */
U8   GH_PLL_get_PLL_IDSP_CTRL32_PLL_VCO(void);
/*! \brief Writes the bit group 'Clamp' of register 'PLL_PLL_IDSP_CTRL32'. */
void GH_PLL_set_PLL_IDSP_CTRL32_Clamp(U8 data);
/*! \brief Reads the bit group 'Clamp' of register 'PLL_PLL_IDSP_CTRL32'. */
U8   GH_PLL_get_PLL_IDSP_CTRL32_Clamp(void);
/*! \brief Writes the bit group 'DSM_dither' of register 'PLL_PLL_IDSP_CTRL32'. */
void GH_PLL_set_PLL_IDSP_CTRL32_DSM_dither(U8 data);
/*! \brief Reads the bit group 'DSM_dither' of register 'PLL_PLL_IDSP_CTRL32'. */
U8   GH_PLL_get_PLL_IDSP_CTRL32_DSM_dither(void);
/*! \brief Writes the bit group 'DSM_dither_gain' of register 'PLL_PLL_IDSP_CTRL32'. */
void GH_PLL_set_PLL_IDSP_CTRL32_DSM_dither_gain(U8 data);
/*! \brief Reads the bit group 'DSM_dither_gain' of register 'PLL_PLL_IDSP_CTRL32'. */
U8   GH_PLL_get_PLL_IDSP_CTRL32_DSM_dither_gain(void);
/*! \brief Writes the bit group 'Feedforward' of register 'PLL_PLL_IDSP_CTRL32'. */
void GH_PLL_set_PLL_IDSP_CTRL32_Feedforward(U8 data);
/*! \brief Reads the bit group 'Feedforward' of register 'PLL_PLL_IDSP_CTRL32'. */
U8   GH_PLL_get_PLL_IDSP_CTRL32_Feedforward(void);
/*! \brief Writes the bit group 'Bias' of register 'PLL_PLL_IDSP_CTRL32'. */
void GH_PLL_set_PLL_IDSP_CTRL32_Bias(U8 data);
/*! \brief Reads the bit group 'Bias' of register 'PLL_PLL_IDSP_CTRL32'. */
U8   GH_PLL_get_PLL_IDSP_CTRL32_Bias(void);
/*! \brief Writes the bit group 'JDIV' of register 'PLL_PLL_IDSP_CTRL32'. */
void GH_PLL_set_PLL_IDSP_CTRL32_JDIV(U8 data);
/*! \brief Reads the bit group 'JDIV' of register 'PLL_PLL_IDSP_CTRL32'. */
U8   GH_PLL_get_PLL_IDSP_CTRL32_JDIV(void);

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_CORE_POST (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_SCALER_CORE_POST'. */
void GH_PLL_set_SCALER_CORE_POST(U32 data);
/*! \brief Reads the register 'PLL_SCALER_CORE_POST'. */
U32  GH_PLL_get_SCALER_CORE_POST(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_CORE_POST'. */
void GH_PLL_set_SCALER_CORE_POST_Div(U8 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_CORE_POST'. */
U8   GH_PLL_get_SCALER_CORE_POST_Div(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_SENSOR_CTRL2 (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_SENSOR_CTRL2'. */
void GH_PLL_set_PLL_SENSOR_CTRL2(U32 data);
/*! \brief Reads the register 'PLL_PLL_SENSOR_CTRL2'. */
U32  GH_PLL_get_PLL_SENSOR_CTRL2(void);
/*! \brief Writes the bit group 'Controllability' of register 'PLL_PLL_SENSOR_CTRL2'. */
void GH_PLL_set_PLL_SENSOR_CTRL2_Controllability(U16 data);
/*! \brief Reads the bit group 'Controllability' of register 'PLL_PLL_SENSOR_CTRL2'. */
U16  GH_PLL_get_PLL_SENSOR_CTRL2_Controllability(void);
/*! \brief Writes the bit group 'Charge' of register 'PLL_PLL_SENSOR_CTRL2'. */
void GH_PLL_set_PLL_SENSOR_CTRL2_Charge(U8 data);
/*! \brief Reads the bit group 'Charge' of register 'PLL_PLL_SENSOR_CTRL2'. */
U8   GH_PLL_get_PLL_SENSOR_CTRL2_Charge(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_SENSOR_CTRL3 (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_SENSOR_CTRL3'. */
void GH_PLL_set_PLL_SENSOR_CTRL3(U32 data);
/*! \brief Reads the register 'PLL_PLL_SENSOR_CTRL3'. */
U32  GH_PLL_get_PLL_SENSOR_CTRL3(void);
/*! \brief Writes the bit group 'VCO' of register 'PLL_PLL_SENSOR_CTRL3'. */
void GH_PLL_set_PLL_SENSOR_CTRL3_VCO(U8 data);
/*! \brief Reads the bit group 'VCO' of register 'PLL_PLL_SENSOR_CTRL3'. */
U8   GH_PLL_get_PLL_SENSOR_CTRL3_VCO(void);
/*! \brief Writes the bit group 'PLL_VCO' of register 'PLL_PLL_SENSOR_CTRL3'. */
void GH_PLL_set_PLL_SENSOR_CTRL3_PLL_VCO(U8 data);
/*! \brief Reads the bit group 'PLL_VCO' of register 'PLL_PLL_SENSOR_CTRL3'. */
U8   GH_PLL_get_PLL_SENSOR_CTRL3_PLL_VCO(void);
/*! \brief Writes the bit group 'Clamp' of register 'PLL_PLL_SENSOR_CTRL3'. */
void GH_PLL_set_PLL_SENSOR_CTRL3_Clamp(U8 data);
/*! \brief Reads the bit group 'Clamp' of register 'PLL_PLL_SENSOR_CTRL3'. */
U8   GH_PLL_get_PLL_SENSOR_CTRL3_Clamp(void);
/*! \brief Writes the bit group 'DSM_dither' of register 'PLL_PLL_SENSOR_CTRL3'. */
void GH_PLL_set_PLL_SENSOR_CTRL3_DSM_dither(U8 data);
/*! \brief Reads the bit group 'DSM_dither' of register 'PLL_PLL_SENSOR_CTRL3'. */
U8   GH_PLL_get_PLL_SENSOR_CTRL3_DSM_dither(void);
/*! \brief Writes the bit group 'DSM_dither_gain' of register 'PLL_PLL_SENSOR_CTRL3'. */
void GH_PLL_set_PLL_SENSOR_CTRL3_DSM_dither_gain(U8 data);
/*! \brief Reads the bit group 'DSM_dither_gain' of register 'PLL_PLL_SENSOR_CTRL3'. */
U8   GH_PLL_get_PLL_SENSOR_CTRL3_DSM_dither_gain(void);
/*! \brief Writes the bit group 'Feedforward' of register 'PLL_PLL_SENSOR_CTRL3'. */
void GH_PLL_set_PLL_SENSOR_CTRL3_Feedforward(U8 data);
/*! \brief Reads the bit group 'Feedforward' of register 'PLL_PLL_SENSOR_CTRL3'. */
U8   GH_PLL_get_PLL_SENSOR_CTRL3_Feedforward(void);
/*! \brief Writes the bit group 'Bias' of register 'PLL_PLL_SENSOR_CTRL3'. */
void GH_PLL_set_PLL_SENSOR_CTRL3_Bias(U8 data);
/*! \brief Reads the bit group 'Bias' of register 'PLL_PLL_SENSOR_CTRL3'. */
U8   GH_PLL_get_PLL_SENSOR_CTRL3_Bias(void);
/*! \brief Writes the bit group 'JDIV' of register 'PLL_PLL_SENSOR_CTRL3'. */
void GH_PLL_set_PLL_SENSOR_CTRL3_JDIV(U8 data);
/*! \brief Reads the bit group 'JDIV' of register 'PLL_PLL_SENSOR_CTRL3'. */
U8   GH_PLL_get_PLL_SENSOR_CTRL3_JDIV(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_AUDIO_CTRL2 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_AUDIO_CTRL2'. */
void GH_PLL_set_PLL_AUDIO_CTRL2(U32 data);
/*! \brief Reads the register 'PLL_PLL_AUDIO_CTRL2'. */
U32  GH_PLL_get_PLL_AUDIO_CTRL2(void);
/*! \brief Writes the bit group 'Controllability' of register 'PLL_PLL_AUDIO_CTRL2'. */
void GH_PLL_set_PLL_AUDIO_CTRL2_Controllability(U16 data);
/*! \brief Reads the bit group 'Controllability' of register 'PLL_PLL_AUDIO_CTRL2'. */
U16  GH_PLL_get_PLL_AUDIO_CTRL2_Controllability(void);
/*! \brief Writes the bit group 'Charge' of register 'PLL_PLL_AUDIO_CTRL2'. */
void GH_PLL_set_PLL_AUDIO_CTRL2_Charge(U8 data);
/*! \brief Reads the bit group 'Charge' of register 'PLL_PLL_AUDIO_CTRL2'. */
U8   GH_PLL_get_PLL_AUDIO_CTRL2_Charge(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_AUDIO_CTRL3 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_AUDIO_CTRL3'. */
void GH_PLL_set_PLL_AUDIO_CTRL3(U32 data);
/*! \brief Reads the register 'PLL_PLL_AUDIO_CTRL3'. */
U32  GH_PLL_get_PLL_AUDIO_CTRL3(void);
/*! \brief Writes the bit group 'VCO' of register 'PLL_PLL_AUDIO_CTRL3'. */
void GH_PLL_set_PLL_AUDIO_CTRL3_VCO(U8 data);
/*! \brief Reads the bit group 'VCO' of register 'PLL_PLL_AUDIO_CTRL3'. */
U8   GH_PLL_get_PLL_AUDIO_CTRL3_VCO(void);
/*! \brief Writes the bit group 'PLL_VCO' of register 'PLL_PLL_AUDIO_CTRL3'. */
void GH_PLL_set_PLL_AUDIO_CTRL3_PLL_VCO(U8 data);
/*! \brief Reads the bit group 'PLL_VCO' of register 'PLL_PLL_AUDIO_CTRL3'. */
U8   GH_PLL_get_PLL_AUDIO_CTRL3_PLL_VCO(void);
/*! \brief Writes the bit group 'Clamp' of register 'PLL_PLL_AUDIO_CTRL3'. */
void GH_PLL_set_PLL_AUDIO_CTRL3_Clamp(U8 data);
/*! \brief Reads the bit group 'Clamp' of register 'PLL_PLL_AUDIO_CTRL3'. */
U8   GH_PLL_get_PLL_AUDIO_CTRL3_Clamp(void);
/*! \brief Writes the bit group 'DSM_dither' of register 'PLL_PLL_AUDIO_CTRL3'. */
void GH_PLL_set_PLL_AUDIO_CTRL3_DSM_dither(U8 data);
/*! \brief Reads the bit group 'DSM_dither' of register 'PLL_PLL_AUDIO_CTRL3'. */
U8   GH_PLL_get_PLL_AUDIO_CTRL3_DSM_dither(void);
/*! \brief Writes the bit group 'DSM_dither_gain' of register 'PLL_PLL_AUDIO_CTRL3'. */
void GH_PLL_set_PLL_AUDIO_CTRL3_DSM_dither_gain(U8 data);
/*! \brief Reads the bit group 'DSM_dither_gain' of register 'PLL_PLL_AUDIO_CTRL3'. */
U8   GH_PLL_get_PLL_AUDIO_CTRL3_DSM_dither_gain(void);
/*! \brief Writes the bit group 'Feedforward' of register 'PLL_PLL_AUDIO_CTRL3'. */
void GH_PLL_set_PLL_AUDIO_CTRL3_Feedforward(U8 data);
/*! \brief Reads the bit group 'Feedforward' of register 'PLL_PLL_AUDIO_CTRL3'. */
U8   GH_PLL_get_PLL_AUDIO_CTRL3_Feedforward(void);
/*! \brief Writes the bit group 'Bias' of register 'PLL_PLL_AUDIO_CTRL3'. */
void GH_PLL_set_PLL_AUDIO_CTRL3_Bias(U8 data);
/*! \brief Reads the bit group 'Bias' of register 'PLL_PLL_AUDIO_CTRL3'. */
U8   GH_PLL_get_PLL_AUDIO_CTRL3_Bias(void);
/*! \brief Writes the bit group 'JDIV' of register 'PLL_PLL_AUDIO_CTRL3'. */
void GH_PLL_set_PLL_AUDIO_CTRL3_JDIV(U8 data);
/*! \brief Reads the bit group 'JDIV' of register 'PLL_PLL_AUDIO_CTRL3'. */
U8   GH_PLL_get_PLL_AUDIO_CTRL3_JDIV(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_VIDEO_CTRL2 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_VIDEO_CTRL2'. */
void GH_PLL_set_PLL_VIDEO_CTRL2(U32 data);
/*! \brief Reads the register 'PLL_PLL_VIDEO_CTRL2'. */
U32  GH_PLL_get_PLL_VIDEO_CTRL2(void);
/*! \brief Writes the bit group 'Controllability' of register 'PLL_PLL_VIDEO_CTRL2'. */
void GH_PLL_set_PLL_VIDEO_CTRL2_Controllability(U16 data);
/*! \brief Reads the bit group 'Controllability' of register 'PLL_PLL_VIDEO_CTRL2'. */
U16  GH_PLL_get_PLL_VIDEO_CTRL2_Controllability(void);
/*! \brief Writes the bit group 'Charge' of register 'PLL_PLL_VIDEO_CTRL2'. */
void GH_PLL_set_PLL_VIDEO_CTRL2_Charge(U8 data);
/*! \brief Reads the bit group 'Charge' of register 'PLL_PLL_VIDEO_CTRL2'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL2_Charge(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_VIDEO_CTRL3 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_VIDEO_CTRL3'. */
void GH_PLL_set_PLL_VIDEO_CTRL3(U32 data);
/*! \brief Reads the register 'PLL_PLL_VIDEO_CTRL3'. */
U32  GH_PLL_get_PLL_VIDEO_CTRL3(void);
/*! \brief Writes the bit group 'VCO' of register 'PLL_PLL_VIDEO_CTRL3'. */
void GH_PLL_set_PLL_VIDEO_CTRL3_VCO(U8 data);
/*! \brief Reads the bit group 'VCO' of register 'PLL_PLL_VIDEO_CTRL3'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL3_VCO(void);
/*! \brief Writes the bit group 'PLL_VCO' of register 'PLL_PLL_VIDEO_CTRL3'. */
void GH_PLL_set_PLL_VIDEO_CTRL3_PLL_VCO(U8 data);
/*! \brief Reads the bit group 'PLL_VCO' of register 'PLL_PLL_VIDEO_CTRL3'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL3_PLL_VCO(void);
/*! \brief Writes the bit group 'Clamp' of register 'PLL_PLL_VIDEO_CTRL3'. */
void GH_PLL_set_PLL_VIDEO_CTRL3_Clamp(U8 data);
/*! \brief Reads the bit group 'Clamp' of register 'PLL_PLL_VIDEO_CTRL3'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL3_Clamp(void);
/*! \brief Writes the bit group 'DSM_dither' of register 'PLL_PLL_VIDEO_CTRL3'. */
void GH_PLL_set_PLL_VIDEO_CTRL3_DSM_dither(U8 data);
/*! \brief Reads the bit group 'DSM_dither' of register 'PLL_PLL_VIDEO_CTRL3'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL3_DSM_dither(void);
/*! \brief Writes the bit group 'DSM_dither_gain' of register 'PLL_PLL_VIDEO_CTRL3'. */
void GH_PLL_set_PLL_VIDEO_CTRL3_DSM_dither_gain(U8 data);
/*! \brief Reads the bit group 'DSM_dither_gain' of register 'PLL_PLL_VIDEO_CTRL3'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL3_DSM_dither_gain(void);
/*! \brief Writes the bit group 'Feedforward' of register 'PLL_PLL_VIDEO_CTRL3'. */
void GH_PLL_set_PLL_VIDEO_CTRL3_Feedforward(U8 data);
/*! \brief Reads the bit group 'Feedforward' of register 'PLL_PLL_VIDEO_CTRL3'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL3_Feedforward(void);
/*! \brief Writes the bit group 'Bias' of register 'PLL_PLL_VIDEO_CTRL3'. */
void GH_PLL_set_PLL_VIDEO_CTRL3_Bias(U8 data);
/*! \brief Reads the bit group 'Bias' of register 'PLL_PLL_VIDEO_CTRL3'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL3_Bias(void);
/*! \brief Writes the bit group 'JDIV' of register 'PLL_PLL_VIDEO_CTRL3'. */
void GH_PLL_set_PLL_VIDEO_CTRL3_JDIV(U8 data);
/*! \brief Reads the bit group 'JDIV' of register 'PLL_PLL_VIDEO_CTRL3'. */
U8   GH_PLL_get_PLL_VIDEO_CTRL3_JDIV(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_VIDEO2_CTRL2 (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_VIDEO2_CTRL2'. */
void GH_PLL_set_PLL_VIDEO2_CTRL2(U32 data);
/*! \brief Reads the register 'PLL_PLL_VIDEO2_CTRL2'. */
U32  GH_PLL_get_PLL_VIDEO2_CTRL2(void);
/*! \brief Writes the bit group 'Controllability' of register 'PLL_PLL_VIDEO2_CTRL2'. */
void GH_PLL_set_PLL_VIDEO2_CTRL2_Controllability(U16 data);
/*! \brief Reads the bit group 'Controllability' of register 'PLL_PLL_VIDEO2_CTRL2'. */
U16  GH_PLL_get_PLL_VIDEO2_CTRL2_Controllability(void);
/*! \brief Writes the bit group 'Charge' of register 'PLL_PLL_VIDEO2_CTRL2'. */
void GH_PLL_set_PLL_VIDEO2_CTRL2_Charge(U8 data);
/*! \brief Reads the bit group 'Charge' of register 'PLL_PLL_VIDEO2_CTRL2'. */
U8   GH_PLL_get_PLL_VIDEO2_CTRL2_Charge(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_USB_CTRL2 (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_USB_CTRL2'. */
void GH_PLL_set_PLL_USB_CTRL2(U32 data);
/*! \brief Reads the register 'PLL_PLL_USB_CTRL2'. */
U32  GH_PLL_get_PLL_USB_CTRL2(void);
/*! \brief Writes the bit group 'VCO' of register 'PLL_PLL_USB_CTRL2'. */
void GH_PLL_set_PLL_USB_CTRL2_VCO(U8 data);
/*! \brief Reads the bit group 'VCO' of register 'PLL_PLL_USB_CTRL2'. */
U8   GH_PLL_get_PLL_USB_CTRL2_VCO(void);
/*! \brief Writes the bit group 'PLL_VCO' of register 'PLL_PLL_USB_CTRL2'. */
void GH_PLL_set_PLL_USB_CTRL2_PLL_VCO(U8 data);
/*! \brief Reads the bit group 'PLL_VCO' of register 'PLL_PLL_USB_CTRL2'. */
U8   GH_PLL_get_PLL_USB_CTRL2_PLL_VCO(void);
/*! \brief Writes the bit group 'Clamp' of register 'PLL_PLL_USB_CTRL2'. */
void GH_PLL_set_PLL_USB_CTRL2_Clamp(U8 data);
/*! \brief Reads the bit group 'Clamp' of register 'PLL_PLL_USB_CTRL2'. */
U8   GH_PLL_get_PLL_USB_CTRL2_Clamp(void);
/*! \brief Writes the bit group 'DSM_dither' of register 'PLL_PLL_USB_CTRL2'. */
void GH_PLL_set_PLL_USB_CTRL2_DSM_dither(U8 data);
/*! \brief Reads the bit group 'DSM_dither' of register 'PLL_PLL_USB_CTRL2'. */
U8   GH_PLL_get_PLL_USB_CTRL2_DSM_dither(void);
/*! \brief Writes the bit group 'DSM_dither_gain' of register 'PLL_PLL_USB_CTRL2'. */
void GH_PLL_set_PLL_USB_CTRL2_DSM_dither_gain(U8 data);
/*! \brief Reads the bit group 'DSM_dither_gain' of register 'PLL_PLL_USB_CTRL2'. */
U8   GH_PLL_get_PLL_USB_CTRL2_DSM_dither_gain(void);
/*! \brief Writes the bit group 'Feedforward' of register 'PLL_PLL_USB_CTRL2'. */
void GH_PLL_set_PLL_USB_CTRL2_Feedforward(U8 data);
/*! \brief Reads the bit group 'Feedforward' of register 'PLL_PLL_USB_CTRL2'. */
U8   GH_PLL_get_PLL_USB_CTRL2_Feedforward(void);
/*! \brief Writes the bit group 'Bias' of register 'PLL_PLL_USB_CTRL2'. */
void GH_PLL_set_PLL_USB_CTRL2_Bias(U8 data);
/*! \brief Reads the bit group 'Bias' of register 'PLL_PLL_USB_CTRL2'. */
U8   GH_PLL_get_PLL_USB_CTRL2_Bias(void);
/*! \brief Writes the bit group 'JDIV' of register 'PLL_PLL_USB_CTRL2'. */
void GH_PLL_set_PLL_USB_CTRL2_JDIV(U8 data);
/*! \brief Reads the bit group 'JDIV' of register 'PLL_PLL_USB_CTRL2'. */
U8   GH_PLL_get_PLL_USB_CTRL2_JDIV(void);

/*----------------------------------------------------------------------------*/
/* register PLL_CG_DDR_CALIB (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_CG_DDR_CALIB'. */
void GH_PLL_set_CG_DDR_CALIB(U32 data);
/*! \brief Reads the register 'PLL_CG_DDR_CALIB'. */
U32  GH_PLL_get_CG_DDR_CALIB(void);

/*----------------------------------------------------------------------------*/
/* register PLL_DLL_CTRL_SEL (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_DLL_CTRL_SEL'. */
void GH_PLL_set_DLL_CTRL_SEL(U32 data);
/*! \brief Reads the register 'PLL_DLL_CTRL_SEL'. */
U32  GH_PLL_get_DLL_CTRL_SEL(void);
/*! \brief Writes the bit group 'rct_ddrio_dll_sbc' of register 'PLL_DLL_CTRL_SEL'. */
void GH_PLL_set_DLL_CTRL_SEL_rct_ddrio_dll_sbc(U16 data);
/*! \brief Reads the bit group 'rct_ddrio_dll_sbc' of register 'PLL_DLL_CTRL_SEL'. */
U16  GH_PLL_get_DLL_CTRL_SEL_rct_ddrio_dll_sbc(void);
/*! \brief Writes the bit group 'rct_ddrio_dll_selm' of register 'PLL_DLL_CTRL_SEL'. */
void GH_PLL_set_DLL_CTRL_SEL_rct_ddrio_dll_selm(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_dll_selm' of register 'PLL_DLL_CTRL_SEL'. */
U8   GH_PLL_get_DLL_CTRL_SEL_rct_ddrio_dll_selm(void);
/*! \brief Writes the bit group 'rct_ddrio_single_end' of register 'PLL_DLL_CTRL_SEL'. */
void GH_PLL_set_DLL_CTRL_SEL_rct_ddrio_single_end(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_single_end' of register 'PLL_DLL_CTRL_SEL'. */
U8   GH_PLL_get_DLL_CTRL_SEL_rct_ddrio_single_end(void);
/*! \brief Writes the bit group 'rct_ddrio_pue_dq' of register 'PLL_DLL_CTRL_SEL'. */
void GH_PLL_set_DLL_CTRL_SEL_rct_ddrio_pue_dq(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_pue_dq' of register 'PLL_DLL_CTRL_SEL'. */
U8   GH_PLL_get_DLL_CTRL_SEL_rct_ddrio_pue_dq(void);
/*! \brief Writes the bit group 'rct_ddrio_pde_dq' of register 'PLL_DLL_CTRL_SEL'. */
void GH_PLL_set_DLL_CTRL_SEL_rct_ddrio_pde_dq(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_pde_dq' of register 'PLL_DLL_CTRL_SEL'. */
U8   GH_PLL_get_DLL_CTRL_SEL_rct_ddrio_pde_dq(void);
/*! \brief Writes the bit group 'rct_ddrio_npue_dqs' of register 'PLL_DLL_CTRL_SEL'. */
void GH_PLL_set_DLL_CTRL_SEL_rct_ddrio_npue_dqs(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_npue_dqs' of register 'PLL_DLL_CTRL_SEL'. */
U8   GH_PLL_get_DLL_CTRL_SEL_rct_ddrio_npue_dqs(void);
/*! \brief Writes the bit group 'rct_ddrio_npde_dqs' of register 'PLL_DLL_CTRL_SEL'. */
void GH_PLL_set_DLL_CTRL_SEL_rct_ddrio_npde_dqs(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_npde_dqs' of register 'PLL_DLL_CTRL_SEL'. */
U8   GH_PLL_get_DLL_CTRL_SEL_rct_ddrio_npde_dqs(void);
/*! \brief Writes the bit group 'rct_ddrio_ppde_dqs' of register 'PLL_DLL_CTRL_SEL'. */
void GH_PLL_set_DLL_CTRL_SEL_rct_ddrio_ppde_dqs(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_ppde_dqs' of register 'PLL_DLL_CTRL_SEL'. */
U8   GH_PLL_get_DLL_CTRL_SEL_rct_ddrio_ppde_dqs(void);
/*! \brief Writes the bit group 'rct_ddrio_ppue_dqs' of register 'PLL_DLL_CTRL_SEL'. */
void GH_PLL_set_DLL_CTRL_SEL_rct_ddrio_ppue_dqs(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_ppue_dqs' of register 'PLL_DLL_CTRL_SEL'. */
U8   GH_PLL_get_DLL_CTRL_SEL_rct_ddrio_ppue_dqs(void);
/*! \brief Writes the bit group 'rct_ddrio_cmosrcv' of register 'PLL_DLL_CTRL_SEL'. */
void GH_PLL_set_DLL_CTRL_SEL_rct_ddrio_cmosrcv(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_cmosrcv' of register 'PLL_DLL_CTRL_SEL'. */
U8   GH_PLL_get_DLL_CTRL_SEL_rct_ddrio_cmosrcv(void);
/*! \brief Writes the bit group 'rct_ddrio_pue_cmd' of register 'PLL_DLL_CTRL_SEL'. */
void GH_PLL_set_DLL_CTRL_SEL_rct_ddrio_pue_cmd(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_pue_cmd' of register 'PLL_DLL_CTRL_SEL'. */
U8   GH_PLL_get_DLL_CTRL_SEL_rct_ddrio_pue_cmd(void);
/*! \brief Writes the bit group 'rct_ddrio_pde_cmd' of register 'PLL_DLL_CTRL_SEL'. */
void GH_PLL_set_DLL_CTRL_SEL_rct_ddrio_pde_cmd(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_pde_cmd' of register 'PLL_DLL_CTRL_SEL'. */
U8   GH_PLL_get_DLL_CTRL_SEL_rct_ddrio_pde_cmd(void);
/*! \brief Writes the bit group 'rct_ddrio_npue_dqs2' of register 'PLL_DLL_CTRL_SEL'. */
void GH_PLL_set_DLL_CTRL_SEL_rct_ddrio_npue_dqs2(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_npue_dqs2' of register 'PLL_DLL_CTRL_SEL'. */
U8   GH_PLL_get_DLL_CTRL_SEL_rct_ddrio_npue_dqs2(void);
/*! \brief Writes the bit group 'rct_ddrio_npde_dqs2' of register 'PLL_DLL_CTRL_SEL'. */
void GH_PLL_set_DLL_CTRL_SEL_rct_ddrio_npde_dqs2(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_npde_dqs2' of register 'PLL_DLL_CTRL_SEL'. */
U8   GH_PLL_get_DLL_CTRL_SEL_rct_ddrio_npde_dqs2(void);
/*! \brief Writes the bit group 'rct_ddrio_ppde_dqs2' of register 'PLL_DLL_CTRL_SEL'. */
void GH_PLL_set_DLL_CTRL_SEL_rct_ddrio_ppde_dqs2(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_ppde_dqs2' of register 'PLL_DLL_CTRL_SEL'. */
U8   GH_PLL_get_DLL_CTRL_SEL_rct_ddrio_ppde_dqs2(void);
/*! \brief Writes the bit group 'rct_ddrio_ppue_dqs2' of register 'PLL_DLL_CTRL_SEL'. */
void GH_PLL_set_DLL_CTRL_SEL_rct_ddrio_ppue_dqs2(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_ppue_dqs2' of register 'PLL_DLL_CTRL_SEL'. */
U8   GH_PLL_get_DLL_CTRL_SEL_rct_ddrio_ppue_dqs2(void);

/*----------------------------------------------------------------------------*/
/* register PLL_DLL_OCD_BITS (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_DLL_OCD_BITS'. */
void GH_PLL_set_DLL_OCD_BITS(U32 data);
/*! \brief Reads the register 'PLL_DLL_OCD_BITS'. */
U32  GH_PLL_get_DLL_OCD_BITS(void);
/*! \brief Writes the bit group 'rct_ddrio_ddr2' of register 'PLL_DLL_OCD_BITS'. */
void GH_PLL_set_DLL_OCD_BITS_rct_ddrio_ddr2(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_ddr2' of register 'PLL_DLL_OCD_BITS'. */
U8   GH_PLL_get_DLL_OCD_BITS_rct_ddrio_ddr2(void);
/*! \brief Writes the bit group 'rct_ddrio_ocd_cmd' of register 'PLL_DLL_OCD_BITS'. */
void GH_PLL_set_DLL_OCD_BITS_rct_ddrio_ocd_cmd(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_ocd_cmd' of register 'PLL_DLL_OCD_BITS'. */
U8   GH_PLL_get_DLL_OCD_BITS_rct_ddrio_ocd_cmd(void);
/*! \brief Writes the bit group 'rct_ddrio_ocd' of register 'PLL_DLL_OCD_BITS'. */
void GH_PLL_set_DLL_OCD_BITS_rct_ddrio_ocd(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_ocd' of register 'PLL_DLL_OCD_BITS'. */
U8   GH_PLL_get_DLL_OCD_BITS_rct_ddrio_ocd(void);
/*! \brief Writes the bit group 'rct_ddrio_odt' of register 'PLL_DLL_OCD_BITS'. */
void GH_PLL_set_DLL_OCD_BITS_rct_ddrio_odt(U8 data);
/*! \brief Reads the bit group 'rct_ddrio_odt' of register 'PLL_DLL_OCD_BITS'. */
U8   GH_PLL_get_DLL_OCD_BITS_rct_ddrio_odt(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_CORE_OBSV (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_CORE_OBSV'. */
void GH_PLL_set_PLL_CORE_OBSV(U32 data);
/*! \brief Reads the register 'PLL_PLL_CORE_OBSV'. */
U32  GH_PLL_get_PLL_CORE_OBSV(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_IDSP_OBSV (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_IDSP_OBSV'. */
void GH_PLL_set_PLL_IDSP_OBSV(U32 data);
/*! \brief Reads the register 'PLL_PLL_IDSP_OBSV'. */
U32  GH_PLL_get_PLL_IDSP_OBSV(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_DDR_OBSV (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_DDR_OBSV'. */
void GH_PLL_set_PLL_DDR_OBSV(U32 data);
/*! \brief Reads the register 'PLL_PLL_DDR_OBSV'. */
U32  GH_PLL_get_PLL_DDR_OBSV(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_SENSOR_OBSV (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_SENSOR_OBSV'. */
void GH_PLL_set_PLL_SENSOR_OBSV(U32 data);
/*! \brief Reads the register 'PLL_PLL_SENSOR_OBSV'. */
U32  GH_PLL_get_PLL_SENSOR_OBSV(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_AUDIO_OBSV (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_AUDIO_OBSV'. */
void GH_PLL_set_PLL_AUDIO_OBSV(U32 data);
/*! \brief Reads the register 'PLL_PLL_AUDIO_OBSV'. */
U32  GH_PLL_get_PLL_AUDIO_OBSV(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_VIDEO_OBSV (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_VIDEO_OBSV'. */
void GH_PLL_set_PLL_VIDEO_OBSV(U32 data);
/*! \brief Reads the register 'PLL_PLL_VIDEO_OBSV'. */
U32  GH_PLL_get_PLL_VIDEO_OBSV(void);

/*----------------------------------------------------------------------------*/
/* register PLL_PLL_VIDEO2_OBSV (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_PLL_VIDEO2_OBSV'. */
void GH_PLL_set_PLL_VIDEO2_OBSV(U32 data);
/*! \brief Reads the register 'PLL_PLL_VIDEO2_OBSV'. */
U32  GH_PLL_get_PLL_VIDEO2_OBSV(void);

/*----------------------------------------------------------------------------*/
/* register PLL_ADC16_CTRL_ADDR (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_ADC16_CTRL_ADDR'. */
void GH_PLL_set_ADC16_CTRL_ADDR(U32 data);
/*! \brief Reads the register 'PLL_ADC16_CTRL_ADDR'. */
U32  GH_PLL_get_ADC16_CTRL_ADDR(void);
/*! \brief Writes the bit group 'adc_power_down' of register 'PLL_ADC16_CTRL_ADDR'. */
void GH_PLL_set_ADC16_CTRL_ADDR_adc_power_down(U8 data);
/*! \brief Reads the bit group 'adc_power_down' of register 'PLL_ADC16_CTRL_ADDR'. */
U8   GH_PLL_get_ADC16_CTRL_ADDR_adc_power_down(void);
/*! \brief Writes the bit group 'adc_clock_select' of register 'PLL_ADC16_CTRL_ADDR'. */
void GH_PLL_set_ADC16_CTRL_ADDR_adc_clock_select(U8 data);
/*! \brief Reads the bit group 'adc_clock_select' of register 'PLL_ADC16_CTRL_ADDR'. */
U8   GH_PLL_get_ADC16_CTRL_ADDR_adc_clock_select(void);

/*----------------------------------------------------------------------------*/
/* register PLL_CLK_REF_SSI_ADDR (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_CLK_REF_SSI_ADDR'. */
void GH_PLL_set_CLK_REF_SSI_ADDR(U32 data);
/*! \brief Reads the register 'PLL_CLK_REF_SSI_ADDR'. */
U32  GH_PLL_get_CLK_REF_SSI_ADDR(void);
/*! \brief Writes the bit group 'clk' of register 'PLL_CLK_REF_SSI_ADDR'. */
void GH_PLL_set_CLK_REF_SSI_ADDR_clk(U8 data);
/*! \brief Reads the bit group 'clk' of register 'PLL_CLK_REF_SSI_ADDR'. */
U8   GH_PLL_get_CLK_REF_SSI_ADDR_clk(void);

/*----------------------------------------------------------------------------*/
/* register PLL_CG_DVEN (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_CG_DVEN'. */
void GH_PLL_set_CG_DVEN(U32 data);
/*! \brief Reads the register 'PLL_CG_DVEN'. */
U32  GH_PLL_get_CG_DVEN(void);

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_MS (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_SCALER_MS'. */
void GH_PLL_set_SCALER_MS(U32 data);
/*! \brief Reads the register 'PLL_SCALER_MS'. */
U32  GH_PLL_get_SCALER_MS(void);

/*----------------------------------------------------------------------------*/
/* register PLL_MS_DELAY_CTRL (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_MS_DELAY_CTRL'. */
void GH_PLL_set_MS_DELAY_CTRL(U32 data);
/*! \brief Reads the register 'PLL_MS_DELAY_CTRL'. */
U32  GH_PLL_get_MS_DELAY_CTRL(void);
/*! \brief Writes the bit group 'delay_sclk' of register 'PLL_MS_DELAY_CTRL'. */
void GH_PLL_set_MS_DELAY_CTRL_delay_sclk(U8 data);
/*! \brief Reads the bit group 'delay_sclk' of register 'PLL_MS_DELAY_CTRL'. */
U8   GH_PLL_get_MS_DELAY_CTRL_delay_sclk(void);
/*! \brief Writes the bit group 'input_delay' of register 'PLL_MS_DELAY_CTRL'. */
void GH_PLL_set_MS_DELAY_CTRL_input_delay(U8 data);
/*! \brief Reads the bit group 'input_delay' of register 'PLL_MS_DELAY_CTRL'. */
U8   GH_PLL_get_MS_DELAY_CTRL_input_delay(void);
/*! \brief Writes the bit group 'output_delay' of register 'PLL_MS_DELAY_CTRL'. */
void GH_PLL_set_MS_DELAY_CTRL_output_delay(U8 data);
/*! \brief Reads the bit group 'output_delay' of register 'PLL_MS_DELAY_CTRL'. */
U8   GH_PLL_get_MS_DELAY_CTRL_output_delay(void);
/*! \brief Writes the bit group 'timing' of register 'PLL_MS_DELAY_CTRL'. */
void GH_PLL_set_MS_DELAY_CTRL_timing(U8 data);
/*! \brief Reads the bit group 'timing' of register 'PLL_MS_DELAY_CTRL'. */
U8   GH_PLL_get_MS_DELAY_CTRL_timing(void);

/*----------------------------------------------------------------------------*/
/* register PLL_USE_COMMON_VO_CLOCK (read/write)                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_USE_COMMON_VO_CLOCK'. */
void GH_PLL_set_USE_COMMON_VO_CLOCK(U32 data);
/*! \brief Reads the register 'PLL_USE_COMMON_VO_CLOCK'. */
U32  GH_PLL_get_USE_COMMON_VO_CLOCK(void);

/*----------------------------------------------------------------------------*/
/* register PLL_CLOCK_OBSV_ADDR (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_CLOCK_OBSV_ADDR'. */
void GH_PLL_set_CLOCK_OBSV_ADDR(U32 data);
/*! \brief Reads the register 'PLL_CLOCK_OBSV_ADDR'. */
U32  GH_PLL_get_CLOCK_OBSV_ADDR(void);
/*! \brief Writes the bit group 'pll' of register 'PLL_CLOCK_OBSV_ADDR'. */
void GH_PLL_set_CLOCK_OBSV_ADDR_pll(U8 data);
/*! \brief Reads the bit group 'pll' of register 'PLL_CLOCK_OBSV_ADDR'. */
U8   GH_PLL_get_CLOCK_OBSV_ADDR_pll(void);
/*! \brief Writes the bit group 'observation' of register 'PLL_CLOCK_OBSV_ADDR'. */
void GH_PLL_set_CLOCK_OBSV_ADDR_observation(U8 data);
/*! \brief Reads the bit group 'observation' of register 'PLL_CLOCK_OBSV_ADDR'. */
U8   GH_PLL_get_CLOCK_OBSV_ADDR_observation(void);

/*----------------------------------------------------------------------------*/
/* register PLL_DISABLE_EXT_BYPASS (read/write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_DISABLE_EXT_BYPASS'. */
void GH_PLL_set_DISABLE_EXT_BYPASS(U32 data);
/*! \brief Reads the register 'PLL_DISABLE_EXT_BYPASS'. */
U32  GH_PLL_get_DISABLE_EXT_BYPASS(void);

/*----------------------------------------------------------------------------*/
/* register PLL_ARM_SYNC_LOCK (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_ARM_SYNC_LOCK'. */
void GH_PLL_set_ARM_SYNC_LOCK(U32 data);
/*! \brief Reads the register 'PLL_ARM_SYNC_LOCK'. */
U32  GH_PLL_get_ARM_SYNC_LOCK(void);
/*! \brief Writes the bit group 'mode' of register 'PLL_ARM_SYNC_LOCK'. */
void GH_PLL_set_ARM_SYNC_LOCK_mode(U8 data);
/*! \brief Reads the bit group 'mode' of register 'PLL_ARM_SYNC_LOCK'. */
U8   GH_PLL_get_ARM_SYNC_LOCK_mode(void);
/*! \brief Writes the bit group 'reset' of register 'PLL_ARM_SYNC_LOCK'. */
void GH_PLL_set_ARM_SYNC_LOCK_reset(U8 data);
/*! \brief Reads the bit group 'reset' of register 'PLL_ARM_SYNC_LOCK'. */
U8   GH_PLL_get_ARM_SYNC_LOCK_reset(void);

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_ARM_SYNC (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_SCALER_ARM_SYNC'. */
void GH_PLL_set_SCALER_ARM_SYNC(U32 data);
/*! \brief Reads the register 'PLL_SCALER_ARM_SYNC'. */
U32  GH_PLL_get_SCALER_ARM_SYNC(void);

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_ARM_ASYNC (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_SCALER_ARM_ASYNC'. */
void GH_PLL_set_SCALER_ARM_ASYNC(U32 data);
/*! \brief Reads the register 'PLL_SCALER_ARM_ASYNC'. */
U32  GH_PLL_get_SCALER_ARM_ASYNC(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_ARM_ASYNC'. */
void GH_PLL_set_SCALER_ARM_ASYNC_Div(U8 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_ARM_ASYNC'. */
U8   GH_PLL_get_SCALER_ARM_ASYNC_Div(void);

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_IDSP_POST (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_SCALER_IDSP_POST'. */
void GH_PLL_set_SCALER_IDSP_POST(U32 data);
/*! \brief Reads the register 'PLL_SCALER_IDSP_POST'. */
U32  GH_PLL_get_SCALER_IDSP_POST(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_IDSP_POST'. */
void GH_PLL_set_SCALER_IDSP_POST_Div(U8 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_IDSP_POST'. */
U8   GH_PLL_get_SCALER_IDSP_POST_Div(void);

/*----------------------------------------------------------------------------*/
/* register PLL_OCTRL_GPIO (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_OCTRL_GPIO'. */
void GH_PLL_set_OCTRL_GPIO(U32 data);
/*! \brief Reads the register 'PLL_OCTRL_GPIO'. */
U32  GH_PLL_get_OCTRL_GPIO(void);

/*----------------------------------------------------------------------------*/
/* register PLL_IOCTRL_MISC1 (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_IOCTRL_MISC1'. */
void GH_PLL_set_IOCTRL_MISC1(U32 data);
/*! \brief Reads the register 'PLL_IOCTRL_MISC1'. */
U32  GH_PLL_get_IOCTRL_MISC1(void);

/*----------------------------------------------------------------------------*/
/* register PLL_OCTRL_MISC2 (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_OCTRL_MISC2'. */
void GH_PLL_set_OCTRL_MISC2(U32 data);
/*! \brief Reads the register 'PLL_OCTRL_MISC2'. */
U32  GH_PLL_get_OCTRL_MISC2(void);

/*----------------------------------------------------------------------------*/
/* register PLL_IOCTRL_SD (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_IOCTRL_SD'. */
void GH_PLL_set_IOCTRL_SD(U32 data);
/*! \brief Reads the register 'PLL_IOCTRL_SD'. */
U32  GH_PLL_get_IOCTRL_SD(void);

/*----------------------------------------------------------------------------*/
/* register PLL_IOCTRL_SMIO (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_IOCTRL_SMIO'. */
void GH_PLL_set_IOCTRL_SMIO(U32 data);
/*! \brief Reads the register 'PLL_IOCTRL_SMIO'. */
U32  GH_PLL_get_IOCTRL_SMIO(void);

/*----------------------------------------------------------------------------*/
/* register PLL_IOCTRL_VD0 (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_IOCTRL_VD0'. */
void GH_PLL_set_IOCTRL_VD0(U32 data);
/*! \brief Reads the register 'PLL_IOCTRL_VD0'. */
U32  GH_PLL_get_IOCTRL_VD0(void);

/*----------------------------------------------------------------------------*/
/* register PLL_IOCTRL_VD1 (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_IOCTRL_VD1'. */
void GH_PLL_set_IOCTRL_VD1(U32 data);
/*! \brief Reads the register 'PLL_IOCTRL_VD1'. */
U32  GH_PLL_get_IOCTRL_VD1(void);

/*----------------------------------------------------------------------------*/
/* register PLL_IOCTRL_SENSOR (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_IOCTRL_SENSOR'. */
void GH_PLL_set_IOCTRL_SENSOR(U32 data);
/*! \brief Reads the register 'PLL_IOCTRL_SENSOR'. */
U32  GH_PLL_get_IOCTRL_SENSOR(void);

/*----------------------------------------------------------------------------*/
/* register PLL_AHB_MISC_EN (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_AHB_MISC_EN'. */
void GH_PLL_set_AHB_MISC_EN(U32 data);
/*! \brief Reads the register 'PLL_AHB_MISC_EN'. */
U32  GH_PLL_get_AHB_MISC_EN(void);
/*! \brief Writes the bit group 'rct_ahb' of register 'PLL_AHB_MISC_EN'. */
void GH_PLL_set_AHB_MISC_EN_rct_ahb(U8 data);
/*! \brief Reads the bit group 'rct_ahb' of register 'PLL_AHB_MISC_EN'. */
U8   GH_PLL_get_AHB_MISC_EN_rct_ahb(void);

/*----------------------------------------------------------------------------*/
/* register PLL_CG_DDR_INIT (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_CG_DDR_INIT'. */
void GH_PLL_set_CG_DDR_INIT(U32 data);
/*! \brief Reads the register 'PLL_CG_DDR_INIT'. */
U32  GH_PLL_get_CG_DDR_INIT(void);
/*! \brief Writes the bit group 'Divide' of register 'PLL_CG_DDR_INIT'. */
void GH_PLL_set_CG_DDR_INIT_Divide(U8 data);
/*! \brief Reads the bit group 'Divide' of register 'PLL_CG_DDR_INIT'. */
U8   GH_PLL_get_CG_DDR_INIT_Divide(void);
/*! \brief Writes the bit group 'en' of register 'PLL_CG_DDR_INIT'. */
void GH_PLL_set_CG_DDR_INIT_en(U8 data);
/*! \brief Reads the bit group 'en' of register 'PLL_CG_DDR_INIT'. */
U8   GH_PLL_get_CG_DDR_INIT_en(void);

/*----------------------------------------------------------------------------*/
/* register PLL_DDR_DIV_RST (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_DDR_DIV_RST'. */
void GH_PLL_set_DDR_DIV_RST(U32 data);
/*! \brief Reads the register 'PLL_DDR_DIV_RST'. */
U32  GH_PLL_get_DDR_DIV_RST(void);

/*----------------------------------------------------------------------------*/
/* register PLL_DDRC_IDSP_RESET (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_DDRC_IDSP_RESET'. */
void GH_PLL_set_DDRC_IDSP_RESET(U32 data);
/*! \brief Reads the register 'PLL_DDRC_IDSP_RESET'. */
U32  GH_PLL_get_DDRC_IDSP_RESET(void);
/*! \brief Writes the bit group 'ddrc' of register 'PLL_DDRC_IDSP_RESET'. */
void GH_PLL_set_DDRC_IDSP_RESET_ddrc(U8 data);
/*! \brief Reads the bit group 'ddrc' of register 'PLL_DDRC_IDSP_RESET'. */
U8   GH_PLL_get_DDRC_IDSP_RESET_ddrc(void);
/*! \brief Writes the bit group 'idsp' of register 'PLL_DDRC_IDSP_RESET'. */
void GH_PLL_set_DDRC_IDSP_RESET_idsp(U8 data);
/*! \brief Reads the bit group 'idsp' of register 'PLL_DDRC_IDSP_RESET'. */
U8   GH_PLL_get_DDRC_IDSP_RESET_idsp(void);

/*----------------------------------------------------------------------------*/
/* register PLL_CKEN_IDSP (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'PLL_CKEN_IDSP'. */
void GH_PLL_set_CKEN_IDSP(U32 data);
/*! \brief Reads the register 'PLL_CKEN_IDSP'. */
U32  GH_PLL_get_CKEN_IDSP(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_PLL_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_debug_rct_amba.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_DEBUG_RCT_AMBA_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

