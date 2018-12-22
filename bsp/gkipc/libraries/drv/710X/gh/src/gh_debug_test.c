/******************************************************************************
**
** \file      gh_debug_test.c
**
** \brief     Debug TEST Registers.
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
#ifndef SRC_INLINE
#include "gh_debug_test.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_DEBUG_TEST_PLL_CORE_CTRL_REAL                   FIO_ADDRESS(DEBUG_TEST,0x70190000) /* read/write */
#define REG_DEBUG_TEST_PLL_CORE_FRAC_REAL                   FIO_ADDRESS(DEBUG_TEST,0x70190004) /* read/write */
#define REG_DEBUG_TEST_HDMI_CTRL_REAL                       FIO_ADDRESS(DEBUG_TEST,0x70190008) /* read/write */
#define REG_DEBUG_TEST_SCALER_SD48_REAL                     FIO_ADDRESS(DEBUG_TEST,0x7019000C) /* read/write */
#define REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL                  FIO_ADDRESS(DEBUG_TEST,0x70190014) /* read/write */
#define REG_DEBUG_TEST_PLL_VIDEO_FRAC_REAL                  FIO_ADDRESS(DEBUG_TEST,0x70190018) /* read/write */
#define REG_DEBUG_TEST_SCALER_VIDEO_REAL                    FIO_ADDRESS(DEBUG_TEST,0x7019001C) /* read/write */
#define REG_DEBUG_TEST_PLL_SENSOR_CTRL_REAL                 FIO_ADDRESS(DEBUG_TEST,0x70190024) /* read/write */
#define REG_DEBUG_TEST_PLL_SENSOR_FRAC_REAL                 FIO_ADDRESS(DEBUG_TEST,0x70190028) /* read/write */
#define REG_DEBUG_TEST_PLL_LOCK_REAL                        FIO_ADDRESS(DEBUG_TEST,0x7019002C) /* read */
#define REG_DEBUG_TEST_SCALER_SENSOR_POST_REAL              FIO_ADDRESS(DEBUG_TEST,0x70190030) /* read/write */
#define REG_DEBUG_TEST_SYS_CONFIG_REAL                      FIO_ADDRESS(DEBUG_TEST,0x70190034) /* read/write */
#define REG_DEBUG_TEST_CG_UART_REAL                         FIO_ADDRESS(DEBUG_TEST,0x70190038) /* read/write */
#define REG_DEBUG_TEST_CG_SSI_REAL                          FIO_ADDRESS(DEBUG_TEST,0x7019003C) /* read/write */
#define REG_DEBUG_TEST_CG_MOTOR_REAL                        FIO_ADDRESS(DEBUG_TEST,0x70190040) /* read/write */
#define REG_DEBUG_TEST_CG_IR_REAL                           FIO_ADDRESS(DEBUG_TEST,0x70190044) /* read/write */
#define REG_DEBUG_TEST_CG_HOST_REAL                         FIO_ADDRESS(DEBUG_TEST,0x70190048) /* read/write */
#define REG_DEBUG_TEST_SCALER_SENSOR_PRE_REAL               FIO_ADDRESS(DEBUG_TEST,0x7019004C) /* read/write */
#define REG_DEBUG_TEST_ANA_PWR_REAL                         FIO_ADDRESS(DEBUG_TEST,0x70190050) /* read/write */
#define REG_DEBUG_TEST_PLL_AUDIO_CTRL_REAL                  FIO_ADDRESS(DEBUG_TEST,0x70190054) /* read/write */
#define REG_DEBUG_TEST_PLL_AUDIO_FRAC_REAL                  FIO_ADDRESS(DEBUG_TEST,0x70190058) /* read/write */
#define REG_DEBUG_TEST_SCALER_AUDIO_REAL                    FIO_ADDRESS(DEBUG_TEST,0x7019005C) /* read/write */
#define REG_DEBUG_TEST_SCALER_AUDIO_PRE_REAL                FIO_ADDRESS(DEBUG_TEST,0x70190060) /* read/write */
#define REG_DEBUG_TEST_SOFT_OR_DLLRESET_REAL                FIO_ADDRESS(DEBUG_TEST,0x70190068) /* read/write */
#define REG_DEBUG_TEST_FIO_RESET_REAL                       FIO_ADDRESS(DEBUG_TEST,0x70190074) /* read/write */
#define REG_DEBUG_TEST_WDT_RST_L_REAL                       FIO_ADDRESS(DEBUG_TEST,0x70190078) /* read */
#define REG_DEBUG_TEST_SCALER_USB_REAL                      FIO_ADDRESS(DEBUG_TEST,0x7019007C) /* read/write */
#define REG_DEBUG_TEST_CLK_DEBOUNCE_REAL                    FIO_ADDRESS(DEBUG_TEST,0x70190080) /* read/write */
#define REG_DEBUG_TEST_CG_PWM_REAL                          FIO_ADDRESS(DEBUG_TEST,0x70190084) /* read/write */
#define REG_DEBUG_TEST_USBP_CTRL_REAL                       FIO_ADDRESS(DEBUG_TEST,0x70190088) /* read/write */
#define REG_DEBUG_TEST_CKEN_VDSP_REAL                       FIO_ADDRESS(DEBUG_TEST,0x7019008C) /* read/write */
#define REG_DEBUG_TEST_DLL0_REAL                            FIO_ADDRESS(DEBUG_TEST,0x70190090) /* read/write */
#define REG_DEBUG_TEST_DLL1_REAL                            FIO_ADDRESS(DEBUG_TEST,0x70190094) /* read/write */
#define REG_DEBUG_TEST_SCALER_ADC_REAL                      FIO_ADDRESS(DEBUG_TEST,0x7019009C) /* read/write */
#define REG_DEBUG_TEST_SCALER_VIDEO_POST_REAL               FIO_ADDRESS(DEBUG_TEST,0x701900A0) /* read/write */
#define REG_DEBUG_TEST_CLK_REF_AU_EXTERNAL_REAL             FIO_ADDRESS(DEBUG_TEST,0x701900A4) /* read/write */
#define REG_DEBUG_TEST_USE_EXTERNAL_CLK_AU_REAL             FIO_ADDRESS(DEBUG_TEST,0x701900A8) /* read/write */
#define REG_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL_REAL          FIO_ADDRESS(DEBUG_TEST,0x701900AC) /* read/write */
#define REG_DEBUG_TEST_USE_EXTERNAL_VD_CLK_REAL             FIO_ADDRESS(DEBUG_TEST,0x701900B0) /* read/write */
#define REG_DEBUG_TEST_USE_CLK_SI_4_CLK_AU_REAL             FIO_ADDRESS(DEBUG_TEST,0x701900B4) /* read/write */
#define REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO_REAL             FIO_ADDRESS(DEBUG_TEST,0x701900B8) /* read/write */
#define REG_DEBUG_TEST_CLK_SI_INPUT_MODE_REAL               FIO_ADDRESS(DEBUG_TEST,0x701900BC) /* read/write */
#define REG_DEBUG_TEST_PLL_VIDEO2_CTRL_REAL                 FIO_ADDRESS(DEBUG_TEST,0x701900C0) /* read/write */
#define REG_DEBUG_TEST_PLL_VIDEO2_FRAC_REAL                 FIO_ADDRESS(DEBUG_TEST,0x701900C4) /* read/write */
#define REG_DEBUG_TEST_SCALER_VIDEO2_REAL                   FIO_ADDRESS(DEBUG_TEST,0x701900C8) /* read/write */
#define REG_DEBUG_TEST_SCALER_VIDEO2_POST_REAL              FIO_ADDRESS(DEBUG_TEST,0x701900CC) /* read/write */
#define REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2_REAL            FIO_ADDRESS(DEBUG_TEST,0x701900D0) /* read/write */
#define REG_DEBUG_TEST_USE_EXTERNAL_VD2_CLK_REAL            FIO_ADDRESS(DEBUG_TEST,0x701900D4) /* read/write */
#define REG_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL_REAL         FIO_ADDRESS(DEBUG_TEST,0x701900D8) /* read/write */
#define REG_DEBUG_TEST_PLL_DDR_CTRL_REAL                    FIO_ADDRESS(DEBUG_TEST,0x701900DC) /* read/write */
#define REG_DEBUG_TEST_PLL_DDR_FRAC_REAL                    FIO_ADDRESS(DEBUG_TEST,0x701900E0) /* read/write */
#define REG_DEBUG_TEST_PLL_IDSP_CTRL_REAL                   FIO_ADDRESS(DEBUG_TEST,0x701900E4) /* read/write */
#define REG_DEBUG_TEST_PLL_IDSP_FRAC_REAL                   FIO_ADDRESS(DEBUG_TEST,0x701900E8) /* read/write */
#define REG_DEBUG_TEST_CG_SSI2_REAL                         FIO_ADDRESS(DEBUG_TEST,0x701900EC) /* read/write */
#define REG_DEBUG_TEST_LVDS_LVCMOS_REAL                     FIO_ADDRESS(DEBUG_TEST,0x701900F8) /* read/write */
#define REG_DEBUG_TEST_LVDS_ASYNC_REAL                      FIO_ADDRESS(DEBUG_TEST,0x701900FC) /* read/write */
#define REG_DEBUG_TEST_PLL_CORE_CTRL2_REAL                  FIO_ADDRESS(DEBUG_TEST,0x70190100) /* read/write */
#define REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL                  FIO_ADDRESS(DEBUG_TEST,0x70190104) /* read/write */
#define REG_DEBUG_TEST_PLL_IDSP_CTRL2_REAL                  FIO_ADDRESS(DEBUG_TEST,0x70190108) /* read/write */
#define REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL                  FIO_ADDRESS(DEBUG_TEST,0x7019010C) /* read/write */
#define REG_DEBUG_TEST_PLL_IDSP_CTRL22_REAL                 FIO_ADDRESS(DEBUG_TEST,0x70190110) /* read/write */
#define REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL                 FIO_ADDRESS(DEBUG_TEST,0x70190114) /* read/write */
#define REG_DEBUG_TEST_SCALER_CORE_POST_REAL                FIO_ADDRESS(DEBUG_TEST,0x70190118) /* read/write */
#define REG_DEBUG_TEST_PLL_SENSOR_CTRL2_REAL                FIO_ADDRESS(DEBUG_TEST,0x7019011C) /* read/write */
#define REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL                FIO_ADDRESS(DEBUG_TEST,0x70190120) /* read/write */
#define REG_DEBUG_TEST_PLL_AUDIO_CTRL2_REAL                 FIO_ADDRESS(DEBUG_TEST,0x70190124) /* read/write */
#define REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL                 FIO_ADDRESS(DEBUG_TEST,0x7019012C) /* read/write */
#define REG_DEBUG_TEST_PLL_VIDEO_CTRL2_REAL                 FIO_ADDRESS(DEBUG_TEST,0x70190130) /* read/write */
#define REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL                 FIO_ADDRESS(DEBUG_TEST,0x70190134) /* read/write */
#define REG_DEBUG_TEST_PLL_VIDEO2_CTRL2_REAL                FIO_ADDRESS(DEBUG_TEST,0x7019013C) /* read/write */
#define REG_DEBUG_TEST_PLL_USB_CTRL2_REAL                   FIO_ADDRESS(DEBUG_TEST,0x70190144) /* read/write */
#define REG_DEBUG_TEST_CG_DDR_CALIB_REAL                    FIO_ADDRESS(DEBUG_TEST,0x70190148) /* read/write */
#define REG_DEBUG_TEST_DLL_CTRL_SEL_REAL                    FIO_ADDRESS(DEBUG_TEST,0x70190158) /* read/write */
#define REG_DEBUG_TEST_DLL_OCD_BITS_REAL                    FIO_ADDRESS(DEBUG_TEST,0x7019015C) /* read/write */
#define REG_DEBUG_TEST_PLL_CORE_OBSV_REAL                   FIO_ADDRESS(DEBUG_TEST,0x70190174) /* read/write */
#define REG_DEBUG_TEST_PLL_IDSP_OBSV_REAL                   FIO_ADDRESS(DEBUG_TEST,0x70190178) /* read/write */
#define REG_DEBUG_TEST_PLL_DDR_OBSV_REAL                    FIO_ADDRESS(DEBUG_TEST,0x7019017C) /* read/write */
#define REG_DEBUG_TEST_PLL_SENSOR_OBSV_REAL                 FIO_ADDRESS(DEBUG_TEST,0x70190180) /* read/write */
#define REG_DEBUG_TEST_PLL_AUDIO_OBSV_REAL                  FIO_ADDRESS(DEBUG_TEST,0x70190184) /* read/write */
#define REG_DEBUG_TEST_PLL_VIDEO_OBSV_REAL                  FIO_ADDRESS(DEBUG_TEST,0x70190188) /* read/write */
#define REG_DEBUG_TEST_PLL_VIDEO2_OBSV_REAL                 FIO_ADDRESS(DEBUG_TEST,0x7019018C) /* read/write */
#define REG_DEBUG_TEST_ADC16_CTRL_ADDR_REAL                 FIO_ADDRESS(DEBUG_TEST,0x70190198) /* read/write */
#define REG_DEBUG_TEST_CLK_REF_SSI_ADDR_REAL                FIO_ADDRESS(DEBUG_TEST,0x7019019C) /* read/write */
#define REG_DEBUG_TEST_CG_DVEN_REAL                         FIO_ADDRESS(DEBUG_TEST,0x701901C8) /* read/write */
#define REG_DEBUG_TEST_SCALER_MS_REAL                       FIO_ADDRESS(DEBUG_TEST,0x701901CC) /* read/write */
#define REG_DEBUG_TEST_MS_DELAY_CTRL_REAL                   FIO_ADDRESS(DEBUG_TEST,0x701901D0) /* read/write */
#define REG_DEBUG_TEST_USE_COMMON_VO_CLOCK_REAL             FIO_ADDRESS(DEBUG_TEST,0x701901D4) /* read/write */
#define REG_DEBUG_TEST_CLOCK_OBSV_ADDR_REAL                 FIO_ADDRESS(DEBUG_TEST,0x701901E0) /* read/write */
#define REG_DEBUG_TEST_DISABLE_EXT_BYPASS_REAL              FIO_ADDRESS(DEBUG_TEST,0x701901E4) /* read/write */
#define REG_DEBUG_TEST_ARM_SYNC_LOCK_REAL                   FIO_ADDRESS(DEBUG_TEST,0x701901E8) /* read/write */
#define REG_DEBUG_TEST_SCALER_ARM_SYNC_REAL                 FIO_ADDRESS(DEBUG_TEST,0x701901EC) /* read/write */
#define REG_DEBUG_TEST_SCALER_ARM_ASYNC_REAL                FIO_ADDRESS(DEBUG_TEST,0x701901F0) /* read/write */
#define REG_DEBUG_TEST_SCALER_IDSP_POST_REAL                FIO_ADDRESS(DEBUG_TEST,0x701901F4) /* read/write */
#define REG_DEBUG_TEST_OCTRL_GPIO_REAL                      FIO_ADDRESS(DEBUG_TEST,0x701901F8) /* read/write */
#define REG_DEBUG_TEST_IOCTRL_MISC1_REAL                    FIO_ADDRESS(DEBUG_TEST,0x701901FC) /* read/write */
#define REG_DEBUG_TEST_OCTRL_MISC2_REAL                     FIO_ADDRESS(DEBUG_TEST,0x70190200) /* read/write */
#define REG_DEBUG_TEST_IOCTRL_SD_REAL                       FIO_ADDRESS(DEBUG_TEST,0x70190204) /* read/write */
#define REG_DEBUG_TEST_IOCTRL_SMIO_REAL                     FIO_ADDRESS(DEBUG_TEST,0x70190208) /* read/write */
#define REG_DEBUG_TEST_IOCTRL_VD0_REAL                      FIO_ADDRESS(DEBUG_TEST,0x7019020C) /* read/write */
#define REG_DEBUG_TEST_IOCTRL_VD1_REAL                      FIO_ADDRESS(DEBUG_TEST,0x70190210) /* read/write */
#define REG_DEBUG_TEST_IOCTRL_SENSOR_REAL                   FIO_ADDRESS(DEBUG_TEST,0x70190214) /* read/write */
#define REG_DEBUG_TEST_AHB_MISC_EN_REAL                     FIO_ADDRESS(DEBUG_TEST,0x7019021C) /* read/write */
#define REG_DEBUG_TEST_CG_DDR_INIT_REAL                     FIO_ADDRESS(DEBUG_TEST,0x70190220) /* read/write */
#define REG_DEBUG_TEST_DDR_DIV_RST_REAL                     FIO_ADDRESS(DEBUG_TEST,0x70190224) /* read/write */
#define REG_DEBUG_TEST_DDRC_IDSP_RESET_REAL                 FIO_ADDRESS(DEBUG_TEST,0x70190228) /* read/write */
#define REG_DEBUG_TEST_CKEN_IDSP_REAL                       FIO_ADDRESS(DEBUG_TEST,0x7019022C) /* read/write */

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
} GH_DEBUG_TEST_HDMI_CTRL_REAL_S;

typedef union { /* DEBUG_TEST_SCALER_SD48 */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 6;
        U32 sdclk_delay                 : 2;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_SCALER_SD48_REAL_S;

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
} GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S;

typedef union { /* DEBUG_TEST_SCALER_VIDEO */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_SCALER_VIDEO_REAL_S;

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
} GH_DEBUG_TEST_PLL_LOCK_REAL_S;

typedef union { /* DEBUG_TEST_SCALER_SENSOR_POST */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_SCALER_SENSOR_POST_REAL_S;

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
} GH_DEBUG_TEST_SYS_CONFIG_REAL_S;

typedef union { /* DEBUG_TEST_SCALER_SENSOR_PRE */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_SCALER_SENSOR_PRE_REAL_S;

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
} GH_DEBUG_TEST_ANA_PWR_REAL_S;

typedef union { /* DEBUG_TEST_SCALER_AUDIO */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_SCALER_AUDIO_REAL_S;

typedef union { /* DEBUG_TEST_SCALER_AUDIO_PRE */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_SCALER_AUDIO_PRE_REAL_S;

typedef union { /* DEBUG_TEST_SOFT_OR_DLLRESET */
    U32 all;
    struct {
        U32 softreset                   : 1;
        U32 dll_rst_l                   : 1;
        U32                             : 30;
    } bitc;
} GH_DEBUG_TEST_SOFT_OR_DLLRESET_REAL_S;

typedef union { /* DEBUG_TEST_FIO_RESET */
    U32 all;
    struct {
        U32 flashreset                  : 1;
        U32 xdreset                     : 1;
        U32 cfreset                     : 1;
        U32 fioreset                    : 1;
        U32                             : 28;
    } bitc;
} GH_DEBUG_TEST_FIO_RESET_REAL_S;

typedef union { /* DEBUG_TEST_SCALER_USB */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_SCALER_USB_REAL_S;

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
} GH_DEBUG_TEST_USBP_CTRL_REAL_S;

typedef union { /* DEBUG_TEST_CKEN_VDSP */
    U32 all;
    struct {
        U32 cken_tsfm                   : 1;
        U32 cken_code                   : 1;
        U32 cken_smem                   : 1;
        U32                             : 29;
    } bitc;
} GH_DEBUG_TEST_CKEN_VDSP_REAL_S;

typedef union { /* DEBUG_TEST_DLL0 */
    U32 all;
    struct {
        U32 dll_sel2                    : 8;
        U32 dll_sel1                    : 8;
        U32 dll_sel0                    : 8;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_DLL0_REAL_S;

typedef union { /* DEBUG_TEST_DLL1 */
    U32 all;
    struct {
        U32 dll_sel2                    : 8;
        U32 dll_sel1                    : 8;
        U32 dll_sel0                    : 8;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_DLL1_REAL_S;

typedef union { /* DEBUG_TEST_SCALER_ADC */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_SCALER_ADC_REAL_S;

typedef union { /* DEBUG_TEST_SCALER_VIDEO_POST */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_SCALER_VIDEO_POST_REAL_S;

typedef union { /* DEBUG_TEST_CLK_REF_AU_EXTERNAL */
    U32 all;
    struct {
        U32 external                    : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_TEST_CLK_REF_AU_EXTERNAL_REAL_S;

typedef union { /* DEBUG_TEST_USE_EXTERNAL_CLK_AU */
    U32 all;
    struct {
        U32 external                    : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_TEST_USE_EXTERNAL_CLK_AU_REAL_S;

typedef union { /* DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL */
    U32 all;
    struct {
        U32 external                    : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL_REAL_S;

typedef union { /* DEBUG_TEST_USE_EXTERNAL_VD_CLK */
    U32 all;
    struct {
        U32 external                    : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_TEST_USE_EXTERNAL_VD_CLK_REAL_S;

typedef union { /* DEBUG_TEST_USE_CLK_SI_4_CLK_AU */
    U32 all;
    struct {
        U32 pllref                      : 2;
        U32                             : 30;
    } bitc;
} GH_DEBUG_TEST_USE_CLK_SI_4_CLK_AU_REAL_S;

typedef union { /* DEBUG_TEST_USE_CLK_SI_4_CLK_VO */
    U32 all;
    struct {
        U32 pllref                      : 2;
        U32                             : 30;
    } bitc;
} GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO_REAL_S;

typedef union { /* DEBUG_TEST_CLK_SI_INPUT_MODE */
    U32 all;
    struct {
        U32 clk_si                      : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_TEST_CLK_SI_INPUT_MODE_REAL_S;

typedef union { /* DEBUG_TEST_PLL_VIDEO2_CTRL */
    U32 all;
    struct {
        U32                             : 20;
        U32 pll_lock                    : 1;
        U32 gclk_vo                     : 1;
        U32                             : 10;
    } bitc;
} GH_DEBUG_TEST_PLL_VIDEO2_CTRL_REAL_S;

typedef union { /* DEBUG_TEST_SCALER_VIDEO2 */
    U32 all;
    struct {
        U32 integerdiv                  : 16;
        U32 primediv                    : 5;
        U32                             : 3;
        U32 dutycycle                   : 1;
        U32                             : 7;
    } bitc;
} GH_DEBUG_TEST_SCALER_VIDEO2_REAL_S;

typedef union { /* DEBUG_TEST_SCALER_VIDEO2_POST */
    U32 all;
    struct {
        U32 integerdiv                  : 16;
        U32 primediv                    : 5;
        U32                             : 3;
        U32 dutycycle                   : 1;
        U32                             : 7;
    } bitc;
} GH_DEBUG_TEST_SCALER_VIDEO2_POST_REAL_S;

typedef union { /* DEBUG_TEST_USE_CLK_SI_4_CLK_VO2 */
    U32 all;
    struct {
        U32 pllref                      : 2;
        U32                             : 30;
    } bitc;
} GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2_REAL_S;

typedef union { /* DEBUG_TEST_USE_EXTERNAL_VD2_CLK */
    U32 all;
    struct {
        U32 external                    : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_TEST_USE_EXTERNAL_VD2_CLK_REAL_S;

typedef union { /* DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL */
    U32 all;
    struct {
        U32 external                    : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL_REAL_S;

typedef union { /* DEBUG_TEST_PLL_DDR_FRAC */
    U32 all;
    struct {
        U32 fraction                    : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_PLL_DDR_FRAC_REAL_S;

typedef union { /* DEBUG_TEST_PLL_IDSP_FRAC */
    U32 all;
    struct {
        U32 fraction                    : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TEST_PLL_IDSP_FRAC_REAL_S;

typedef union { /* DEBUG_TEST_LVDS_LVCMOS */
    U32 all;
    struct {
        U32 lvcoms_sd                   : 16;
        U32 lvcmos_spclk                : 4;
        U32                             : 12;
    } bitc;
} GH_DEBUG_TEST_LVDS_LVCMOS_REAL_S;

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
} GH_DEBUG_TEST_LVDS_ASYNC_REAL_S;

typedef union { /* DEBUG_TEST_PLL_CORE_CTRL2 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_PLL_CORE_CTRL2_REAL_S;

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
} GH_DEBUG_TEST_PLL_CORE_CTRL3_REAL_S;

typedef union { /* DEBUG_TEST_PLL_IDSP_CTRL2 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_PLL_IDSP_CTRL2_REAL_S;

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
} GH_DEBUG_TEST_PLL_IDSP_CTRL3_REAL_S;

typedef union { /* DEBUG_TEST_PLL_IDSP_CTRL22 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_PLL_IDSP_CTRL22_REAL_S;

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
} GH_DEBUG_TEST_PLL_IDSP_CTRL32_REAL_S;

typedef union { /* DEBUG_TEST_SCALER_CORE_POST */
    U32 all;
    struct {
        U32 div                         : 4;
        U32                             : 28;
    } bitc;
} GH_DEBUG_TEST_SCALER_CORE_POST_REAL_S;

typedef union { /* DEBUG_TEST_PLL_SENSOR_CTRL2 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_PLL_SENSOR_CTRL2_REAL_S;

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
} GH_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL_S;

typedef union { /* DEBUG_TEST_PLL_AUDIO_CTRL2 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_PLL_AUDIO_CTRL2_REAL_S;

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
} GH_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL_S;

typedef union { /* DEBUG_TEST_PLL_VIDEO_CTRL2 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_PLL_VIDEO_CTRL2_REAL_S;

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
} GH_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL_S;

typedef union { /* DEBUG_TEST_PLL_VIDEO2_CTRL2 */
    U32 all;
    struct {
        U32 controllability             : 16;
        U32 charge                      : 8;
        U32                             : 8;
    } bitc;
} GH_DEBUG_TEST_PLL_VIDEO2_CTRL2_REAL_S;

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
} GH_DEBUG_TEST_PLL_USB_CTRL2_REAL_S;

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
} GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S;

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
} GH_DEBUG_TEST_DLL_OCD_BITS_REAL_S;

typedef union { /* DEBUG_TEST_ADC16_CTRL_ADDR */
    U32 all;
    struct {
        U32 adc_power_down              : 1;
        U32 adc_clock_select            : 1;
        U32                             : 30;
    } bitc;
} GH_DEBUG_TEST_ADC16_CTRL_ADDR_REAL_S;

typedef union { /* DEBUG_TEST_CLK_REF_SSI_ADDR */
    U32 all;
    struct {
        U32 clk                         : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_TEST_CLK_REF_SSI_ADDR_REAL_S;

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
} GH_DEBUG_TEST_MS_DELAY_CTRL_REAL_S;

typedef union { /* DEBUG_TEST_CLOCK_OBSV_ADDR */
    U32 all;
    struct {
        U32 pll                         : 4;
        U32 observation                 : 1;
        U32                             : 27;
    } bitc;
} GH_DEBUG_TEST_CLOCK_OBSV_ADDR_REAL_S;

typedef union { /* DEBUG_TEST_ARM_SYNC_LOCK */
    U32 all;
    struct {
        U32 mode                        : 1;
        U32 reset                       : 1;
        U32                             : 30;
    } bitc;
} GH_DEBUG_TEST_ARM_SYNC_LOCK_REAL_S;

typedef union { /* DEBUG_TEST_SCALER_ARM_ASYNC */
    U32 all;
    struct {
        U32 div                         : 4;
        U32                             : 28;
    } bitc;
} GH_DEBUG_TEST_SCALER_ARM_ASYNC_REAL_S;

typedef union { /* DEBUG_TEST_SCALER_IDSP_POST */
    U32 all;
    struct {
        U32 div                         : 4;
        U32                             : 28;
    } bitc;
} GH_DEBUG_TEST_SCALER_IDSP_POST_REAL_S;

typedef union { /* DEBUG_TEST_AHB_MISC_EN */
    U32 all;
    struct {
        U32 rct_ahb                     : 1;
        U32                             : 31;
    } bitc;
} GH_DEBUG_TEST_AHB_MISC_EN_REAL_S;

typedef union { /* DEBUG_TEST_CG_DDR_INIT */
    U32 all;
    struct {
        U32 divide                      : 8;
        U32 en                          : 1;
        U32                             : 23;
    } bitc;
} GH_DEBUG_TEST_CG_DDR_INIT_REAL_S;

typedef union { /* DEBUG_TEST_DDRC_IDSP_RESET */
    U32 all;
    struct {
        U32 ddrc                        : 1;
        U32 idsp                        : 1;
        U32                             : 30;
    } bitc;
} GH_DEBUG_TEST_DDRC_IDSP_RESET_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_CORE_CTRL (read/write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_CORE_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_CORE_FRAC (read/write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_FRAC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_FRAC_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_CORE_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_FRAC_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_HDMI_CTRL (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_HDMI_CTRL(U32 data)
{
    GH_DEBUG_TEST_HDMI_CTRL_REAL_S real;
    GH_DEBUG_TEST_HDMI_CTRL_S dummy;
    dummy.all = data ;
    real.bitc.hdmi_phy_test_mode = dummy.bitc.hdmi_phy_test_mode;
    real.bitc.use_hdmi_phy_clk_v = dummy.bitc.use_hdmi_phy_clk_v;
    *(volatile U32 *)REG_DEBUG_TEST_HDMI_CTRL_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_HDMI_CTRL(void)
{
    GH_DEBUG_TEST_HDMI_CTRL_REAL_S real;
    GH_DEBUG_TEST_HDMI_CTRL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_HDMI_CTRL_REAL);

    dummy.bitc.hdmi_phy_test_mode = real.bitc.hdmi_phy_test_mode;
    dummy.bitc.use_hdmi_phy_clk_v = real.bitc.use_hdmi_phy_clk_v;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_HDMI_CTRL_Hdmi_phy_test_mode(U8 data)
{
    GH_DEBUG_TEST_HDMI_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_HDMI_CTRL_REAL;
    d.bitc.hdmi_phy_test_mode = data;
    *(volatile U32 *)REG_DEBUG_TEST_HDMI_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_HDMI_CTRL_Hdmi_phy_test_mode(void)
{
    GH_DEBUG_TEST_HDMI_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_HDMI_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hdmi_phy_test_mode;
}
GH_INLINE void GH_DEBUG_TEST_set_HDMI_CTRL_use_hdmi_phy_clk_v(U8 data)
{
    GH_DEBUG_TEST_HDMI_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_HDMI_CTRL_REAL;
    d.bitc.use_hdmi_phy_clk_v = data;
    *(volatile U32 *)REG_DEBUG_TEST_HDMI_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_HDMI_CTRL_use_hdmi_phy_clk_v(void)
{
    GH_DEBUG_TEST_HDMI_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_HDMI_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.use_hdmi_phy_clk_v;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_SD48 (read/write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_SCALER_SD48(U32 data)
{
    GH_DEBUG_TEST_SCALER_SD48_REAL_S real;
    GH_DEBUG_TEST_SCALER_SD48_S dummy;
    dummy.all = data ;
    real.bitc.div = dummy.bitc.div;
    real.bitc.sdclk_delay = dummy.bitc.sdclk_delay;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_SD48_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_SD48(void)
{
    GH_DEBUG_TEST_SCALER_SD48_REAL_S real;
    GH_DEBUG_TEST_SCALER_SD48_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_SD48_REAL);

    dummy.bitc.div = real.bitc.div;
    dummy.bitc.sdclk_delay = real.bitc.sdclk_delay;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_SD48_Div(U16 data)
{
    GH_DEBUG_TEST_SCALER_SD48_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_SD48_REAL;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_SD48_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_SD48_Div(void)
{
    GH_DEBUG_TEST_SCALER_SD48_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_SD48_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.div;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_SD48_SDCLK_delay(U8 data)
{
    GH_DEBUG_TEST_SCALER_SD48_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_SD48_REAL;
    d.bitc.sdclk_delay = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_SD48_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SCALER_SD48_SDCLK_delay(void)
{
    GH_DEBUG_TEST_SCALER_SD48_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_SD48_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sdclk_delay;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_VIDEO_CTRL (read/write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL(U32 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S real;
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S dummy;
    dummy.all = data ;
    real.bitc.writeenable = dummy.bitc.writeenable;
    real.bitc.bypass = dummy.bitc.bypass;
    real.bitc.mode = dummy.bitc.mode;
    real.bitc.reset = dummy.bitc.reset;
    real.bitc.powerdown = dummy.bitc.powerdown;
    real.bitc.halfvco = dummy.bitc.halfvco;
    real.bitc.tristate = dummy.bitc.tristate;
    real.bitc.pll_tout_async = dummy.bitc.pll_tout_async;
    real.bitc.sdiv = dummy.bitc.sdiv;
    real.bitc.sout = dummy.bitc.sout;
    real.bitc.pll_lock = dummy.bitc.pll_lock;
    real.bitc.gclk_vo = dummy.bitc.gclk_vo;
    real.bitc.intprog = dummy.bitc.intprog;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_VIDEO_CTRL(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S real;
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL);

    dummy.bitc.writeenable = real.bitc.writeenable;
    dummy.bitc.bypass = real.bitc.bypass;
    dummy.bitc.mode = real.bitc.mode;
    dummy.bitc.reset = real.bitc.reset;
    dummy.bitc.powerdown = real.bitc.powerdown;
    dummy.bitc.halfvco = real.bitc.halfvco;
    dummy.bitc.tristate = real.bitc.tristate;
    dummy.bitc.pll_tout_async = real.bitc.pll_tout_async;
    dummy.bitc.sdiv = real.bitc.sdiv;
    dummy.bitc.sout = real.bitc.sout;
    dummy.bitc.pll_lock = real.bitc.pll_lock;
    dummy.bitc.gclk_vo = real.bitc.gclk_vo;
    dummy.bitc.intprog = real.bitc.intprog;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_WriteEnable(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL;
    d.bitc.writeenable = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_WriteEnable(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.writeenable;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_BYPASS(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL;
    d.bitc.bypass = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_BYPASS(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.bypass;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_Mode(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL;
    d.bitc.mode = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_Mode(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mode;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_reset(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL;
    d.bitc.reset = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_reset(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reset;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_PowerDown(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL;
    d.bitc.powerdown = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_PowerDown(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.powerdown;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_HalfVCO(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL;
    d.bitc.halfvco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_HalfVCO(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.halfvco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_Tristate(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL;
    d.bitc.tristate = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_Tristate(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tristate;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_pll_tout_async(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL;
    d.bitc.pll_tout_async = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_pll_tout_async(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_tout_async;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_SDIV(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL;
    d.bitc.sdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_SDIV(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sdiv;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_SOUT(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL;
    d.bitc.sout = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_SOUT(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sout;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_pll_lock(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL;
    d.bitc.pll_lock = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_pll_lock(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_lock;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_gclk_vo(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL;
    d.bitc.gclk_vo = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_gclk_vo(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gclk_vo;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL_INTPROG(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL;
    d.bitc.intprog = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL_INTPROG(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.intprog;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_VIDEO_FRAC (read/write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_FRAC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_FRAC_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_VIDEO_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_FRAC_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_VIDEO (read/write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO(U32 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO_REAL_S real;
    GH_DEBUG_TEST_SCALER_VIDEO_S dummy;
    dummy.all = data ;
    real.bitc.div = dummy.bitc.div;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_VIDEO(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO_REAL_S real;
    GH_DEBUG_TEST_SCALER_VIDEO_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO_REAL);

    dummy.bitc.div = real.bitc.div;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO_Div(U16 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO_REAL;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_VIDEO_Div(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.div;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_SENSOR_CTRL (read/write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_SENSOR_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_SENSOR_FRAC (read/write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_FRAC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_FRAC_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_SENSOR_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_FRAC_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_LOCK (read)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_LOCK(void)
{
    GH_DEBUG_TEST_PLL_LOCK_REAL_S real;
    GH_DEBUG_TEST_PLL_LOCK_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK_REAL);

    dummy.bitc.pll_video2 = real.bitc.pll_video2;
    dummy.bitc.pll_video = real.bitc.pll_video;
    dummy.bitc.pll_usb = real.bitc.pll_usb;
    dummy.bitc.pll_sensor = real.bitc.pll_sensor;
    dummy.bitc.pll_idsp = real.bitc.pll_idsp;
    dummy.bitc.pll_ddr = real.bitc.pll_ddr;
    dummy.bitc.pll_core = real.bitc.pll_core;
    dummy.bitc.pll_audio = real.bitc.pll_audio;
    dummy.bitc.pll_hdmi = real.bitc.pll_hdmi;
    dummy.bitc.pll_vin = real.bitc.pll_vin;
    return dummy.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_VIDEO2(void)
{
    GH_DEBUG_TEST_PLL_LOCK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_video2;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_VIDEO(void)
{
    GH_DEBUG_TEST_PLL_LOCK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_video;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_USB(void)
{
    GH_DEBUG_TEST_PLL_LOCK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_usb;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_SENSOR(void)
{
    GH_DEBUG_TEST_PLL_LOCK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_sensor;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_IDSP(void)
{
    GH_DEBUG_TEST_PLL_LOCK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_idsp;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_DDR(void)
{
    GH_DEBUG_TEST_PLL_LOCK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_ddr;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_CORE(void)
{
    GH_DEBUG_TEST_PLL_LOCK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_core;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_AUDIO(void)
{
    GH_DEBUG_TEST_PLL_LOCK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_audio;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_HDMI(void)
{
    GH_DEBUG_TEST_PLL_LOCK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_hdmi;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_LOCK_PLL_VIN(void)
{
    GH_DEBUG_TEST_PLL_LOCK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_LOCK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_vin;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_SENSOR_POST (read/write)                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_SCALER_SENSOR_POST(U32 data)
{
    GH_DEBUG_TEST_SCALER_SENSOR_POST_REAL_S real;
    GH_DEBUG_TEST_SCALER_SENSOR_POST_S dummy;
    dummy.all = data ;
    real.bitc.div = dummy.bitc.div;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_POST_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_SENSOR_POST(void)
{
    GH_DEBUG_TEST_SCALER_SENSOR_POST_REAL_S real;
    GH_DEBUG_TEST_SCALER_SENSOR_POST_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_POST_REAL);

    dummy.bitc.div = real.bitc.div;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_SENSOR_POST_Div(U16 data)
{
    GH_DEBUG_TEST_SCALER_SENSOR_POST_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_POST_REAL;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_POST_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_SENSOR_POST_Div(void)
{
    GH_DEBUG_TEST_SCALER_SENSOR_POST_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_POST_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.div;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SYS_CONFIG (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG(U32 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S real;
    GH_DEBUG_TEST_SYS_CONFIG_S dummy;
    dummy.all = data ;
    real.bitc.bootmedia = dummy.bitc.bootmedia;
    real.bitc.clock = dummy.bitc.clock;
    real.bitc.grst = dummy.bitc.grst;
    real.bitc.page_size = dummy.bitc.page_size;
    real.bitc.read = dummy.bitc.read;
    real.bitc.enet = dummy.bitc.enet;
    real.bitc.boot_bypass = dummy.bitc.boot_bypass;
    real.bitc.fastboot = dummy.bitc.fastboot;
    real.bitc.io_flash_boot = dummy.bitc.io_flash_boot;
    real.bitc.sd_boot = dummy.bitc.sd_boot;
    real.bitc.ema_sel = dummy.bitc.ema_sel;
    real.bitc.lock_mode = dummy.bitc.lock_mode;
    real.bitc.grst_l = dummy.bitc.grst_l;
    real.bitc.rmii_sel = dummy.bitc.rmii_sel;
    real.bitc.spi_boot = dummy.bitc.spi_boot;
    real.bitc.hif_en = dummy.bitc.hif_en;
    real.bitc.free = dummy.bitc.free;
    real.bitc.hif_type = dummy.bitc.hif_type;
    real.bitc.rdy_pl = dummy.bitc.rdy_pl;
    real.bitc.rct_ahb_hif_secure_mode = dummy.bitc.rct_ahb_hif_secure_mode;
    real.bitc.usbp = dummy.bitc.usbp;
    real.bitc.ref_clk_is_24mhz = dummy.bitc.ref_clk_is_24mhz;
    real.bitc.rct_bira_efuse_disable = dummy.bitc.rct_bira_efuse_disable;
    real.bitc.hardcoded = dummy.bitc.hardcoded;
    real.bitc.source = dummy.bitc.source;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_SYS_CONFIG(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S real;
    GH_DEBUG_TEST_SYS_CONFIG_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    dummy.bitc.bootmedia = real.bitc.bootmedia;
    dummy.bitc.clock = real.bitc.clock;
    dummy.bitc.grst = real.bitc.grst;
    dummy.bitc.page_size = real.bitc.page_size;
    dummy.bitc.read = real.bitc.read;
    dummy.bitc.enet = real.bitc.enet;
    dummy.bitc.boot_bypass = real.bitc.boot_bypass;
    dummy.bitc.fastboot = real.bitc.fastboot;
    dummy.bitc.io_flash_boot = real.bitc.io_flash_boot;
    dummy.bitc.sd_boot = real.bitc.sd_boot;
    dummy.bitc.ema_sel = real.bitc.ema_sel;
    dummy.bitc.lock_mode = real.bitc.lock_mode;
    dummy.bitc.grst_l = real.bitc.grst_l;
    dummy.bitc.rmii_sel = real.bitc.rmii_sel;
    dummy.bitc.spi_boot = real.bitc.spi_boot;
    dummy.bitc.hif_en = real.bitc.hif_en;
    dummy.bitc.free = real.bitc.free;
    dummy.bitc.hif_type = real.bitc.hif_type;
    dummy.bitc.rdy_pl = real.bitc.rdy_pl;
    dummy.bitc.rct_ahb_hif_secure_mode = real.bitc.rct_ahb_hif_secure_mode;
    dummy.bitc.usbp = real.bitc.usbp;
    dummy.bitc.ref_clk_is_24mhz = real.bitc.ref_clk_is_24mhz;
    dummy.bitc.rct_bira_efuse_disable = real.bitc.rct_bira_efuse_disable;
    dummy.bitc.hardcoded = real.bitc.hardcoded;
    dummy.bitc.source = real.bitc.source;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_BootMedia(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.bootmedia = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_BootMedia(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.bootmedia;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_clock(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.clock = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_clock(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clock;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_grst(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.grst = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_grst(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.grst;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_page_size(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.page_size = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_page_size(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.page_size;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_read(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.read = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_read(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.read;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_enet(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.enet = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_enet(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enet;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_Boot_Bypass(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.boot_bypass = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_Boot_Bypass(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.boot_bypass;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_fastboot(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.fastboot = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_fastboot(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fastboot;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_IO_Flash_boot(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.io_flash_boot = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_IO_Flash_boot(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.io_flash_boot;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_SD_BOOT(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.sd_boot = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_SD_BOOT(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sd_boot;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_EMA_SEL(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.ema_sel = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_EMA_SEL(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ema_sel;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_lock_mode(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.lock_mode = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_lock_mode(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.lock_mode;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_grst_l(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.grst_l = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_grst_l(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.grst_l;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_RMII_SEL(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.rmii_sel = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_RMII_SEL(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rmii_sel;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_spi_boot(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.spi_boot = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_spi_boot(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.spi_boot;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_hif_en(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.hif_en = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_hif_en(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hif_en;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_FREE(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.free = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_FREE(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.free;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_hif_type(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.hif_type = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_hif_type(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hif_type;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_rdy_pl(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.rdy_pl = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_rdy_pl(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rdy_pl;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_rct_ahb_hif_secure_mode(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.rct_ahb_hif_secure_mode = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_rct_ahb_hif_secure_mode(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ahb_hif_secure_mode;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_usbp(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.usbp = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_usbp(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.usbp;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_ref_clk_is_24Mhz(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.ref_clk_is_24mhz = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_ref_clk_is_24Mhz(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ref_clk_is_24mhz;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_rct_bira_efuse_disable(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.rct_bira_efuse_disable = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_rct_bira_efuse_disable(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_bira_efuse_disable;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_hardcoded(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.hardcoded = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_hardcoded(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hardcoded;
}
GH_INLINE void GH_DEBUG_TEST_set_SYS_CONFIG_source(U8 data)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL;
    d.bitc.source = data;
    *(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SYS_CONFIG_source(void)
{
    GH_DEBUG_TEST_SYS_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SYS_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.source;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_UART (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_CG_UART(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CG_UART_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_UART(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_UART_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_SSI (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_CG_SSI(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CG_SSI_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_SSI(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_SSI_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_MOTOR (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_CG_MOTOR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CG_MOTOR_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_MOTOR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_MOTOR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_IR (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_CG_IR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CG_IR_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_IR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_IR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_HOST (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_CG_HOST(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CG_HOST_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_HOST(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_HOST_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_SENSOR_PRE (read/write)                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_SCALER_SENSOR_PRE(U32 data)
{
    GH_DEBUG_TEST_SCALER_SENSOR_PRE_REAL_S real;
    GH_DEBUG_TEST_SCALER_SENSOR_PRE_S dummy;
    dummy.all = data ;
    real.bitc.div = dummy.bitc.div;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_PRE_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_SENSOR_PRE(void)
{
    GH_DEBUG_TEST_SCALER_SENSOR_PRE_REAL_S real;
    GH_DEBUG_TEST_SCALER_SENSOR_PRE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_PRE_REAL);

    dummy.bitc.div = real.bitc.div;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_SENSOR_PRE_Div(U16 data)
{
    GH_DEBUG_TEST_SCALER_SENSOR_PRE_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_PRE_REAL;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_PRE_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_SENSOR_PRE_Div(void)
{
    GH_DEBUG_TEST_SCALER_SENSOR_PRE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_SENSOR_PRE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.div;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_ANA_PWR (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_ANA_PWR(U32 data)
{
    GH_DEBUG_TEST_ANA_PWR_REAL_S real;
    GH_DEBUG_TEST_ANA_PWR_S dummy;
    dummy.all = data ;
    real.bitc.usbsuspend = dummy.bitc.usbsuspend;
    real.bitc.suspendusbp = dummy.bitc.suspendusbp;
    real.bitc.power_controller = dummy.bitc.power_controller;
    real.bitc.dllpowerdown = dummy.bitc.dllpowerdown;
    *(volatile U32 *)REG_DEBUG_TEST_ANA_PWR_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_ANA_PWR(void)
{
    GH_DEBUG_TEST_ANA_PWR_REAL_S real;
    GH_DEBUG_TEST_ANA_PWR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_ANA_PWR_REAL);

    dummy.bitc.usbsuspend = real.bitc.usbsuspend;
    dummy.bitc.suspendusbp = real.bitc.suspendusbp;
    dummy.bitc.power_controller = real.bitc.power_controller;
    dummy.bitc.dllpowerdown = real.bitc.dllpowerdown;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_ANA_PWR_USBsuspend(U8 data)
{
    GH_DEBUG_TEST_ANA_PWR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_ANA_PWR_REAL;
    d.bitc.usbsuspend = data;
    *(volatile U32 *)REG_DEBUG_TEST_ANA_PWR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_ANA_PWR_USBsuspend(void)
{
    GH_DEBUG_TEST_ANA_PWR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_ANA_PWR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.usbsuspend;
}
GH_INLINE void GH_DEBUG_TEST_set_ANA_PWR_suspendUSBP(U8 data)
{
    GH_DEBUG_TEST_ANA_PWR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_ANA_PWR_REAL;
    d.bitc.suspendusbp = data;
    *(volatile U32 *)REG_DEBUG_TEST_ANA_PWR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_ANA_PWR_suspendUSBP(void)
{
    GH_DEBUG_TEST_ANA_PWR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_ANA_PWR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.suspendusbp;
}
GH_INLINE void GH_DEBUG_TEST_set_ANA_PWR_power_controller(U8 data)
{
    GH_DEBUG_TEST_ANA_PWR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_ANA_PWR_REAL;
    d.bitc.power_controller = data;
    *(volatile U32 *)REG_DEBUG_TEST_ANA_PWR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_ANA_PWR_power_controller(void)
{
    GH_DEBUG_TEST_ANA_PWR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_ANA_PWR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.power_controller;
}
GH_INLINE void GH_DEBUG_TEST_set_ANA_PWR_DLLpowerdown(U8 data)
{
    GH_DEBUG_TEST_ANA_PWR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_ANA_PWR_REAL;
    d.bitc.dllpowerdown = data;
    *(volatile U32 *)REG_DEBUG_TEST_ANA_PWR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_ANA_PWR_DLLpowerdown(void)
{
    GH_DEBUG_TEST_ANA_PWR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_ANA_PWR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dllpowerdown;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_AUDIO_CTRL (read/write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_AUDIO_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_AUDIO_FRAC (read/write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_FRAC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_FRAC_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_AUDIO_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_FRAC_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_AUDIO (read/write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_SCALER_AUDIO(U32 data)
{
    GH_DEBUG_TEST_SCALER_AUDIO_REAL_S real;
    GH_DEBUG_TEST_SCALER_AUDIO_S dummy;
    dummy.all = data ;
    real.bitc.div = dummy.bitc.div;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_AUDIO(void)
{
    GH_DEBUG_TEST_SCALER_AUDIO_REAL_S real;
    GH_DEBUG_TEST_SCALER_AUDIO_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO_REAL);

    dummy.bitc.div = real.bitc.div;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_AUDIO_Div(U16 data)
{
    GH_DEBUG_TEST_SCALER_AUDIO_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO_REAL;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_AUDIO_Div(void)
{
    GH_DEBUG_TEST_SCALER_AUDIO_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.div;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_AUDIO_PRE (read/write)                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_SCALER_AUDIO_PRE(U32 data)
{
    GH_DEBUG_TEST_SCALER_AUDIO_PRE_REAL_S real;
    GH_DEBUG_TEST_SCALER_AUDIO_PRE_S dummy;
    dummy.all = data ;
    real.bitc.div = dummy.bitc.div;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO_PRE_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_AUDIO_PRE(void)
{
    GH_DEBUG_TEST_SCALER_AUDIO_PRE_REAL_S real;
    GH_DEBUG_TEST_SCALER_AUDIO_PRE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO_PRE_REAL);

    dummy.bitc.div = real.bitc.div;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_AUDIO_PRE_Div(U16 data)
{
    GH_DEBUG_TEST_SCALER_AUDIO_PRE_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO_PRE_REAL;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO_PRE_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_AUDIO_PRE_Div(void)
{
    GH_DEBUG_TEST_SCALER_AUDIO_PRE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_AUDIO_PRE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.div;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SOFT_OR_DLLRESET (read/write)                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_SOFT_OR_DLLRESET(U32 data)
{
    GH_DEBUG_TEST_SOFT_OR_DLLRESET_REAL_S real;
    GH_DEBUG_TEST_SOFT_OR_DLLRESET_S dummy;
    dummy.all = data ;
    real.bitc.softreset = dummy.bitc.softreset;
    real.bitc.dll_rst_l = dummy.bitc.dll_rst_l;
    *(volatile U32 *)REG_DEBUG_TEST_SOFT_OR_DLLRESET_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_SOFT_OR_DLLRESET(void)
{
    GH_DEBUG_TEST_SOFT_OR_DLLRESET_REAL_S real;
    GH_DEBUG_TEST_SOFT_OR_DLLRESET_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_SOFT_OR_DLLRESET_REAL);

    dummy.bitc.softreset = real.bitc.softreset;
    dummy.bitc.dll_rst_l = real.bitc.dll_rst_l;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_SOFT_OR_DLLRESET_Softreset(U8 data)
{
    GH_DEBUG_TEST_SOFT_OR_DLLRESET_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SOFT_OR_DLLRESET_REAL;
    d.bitc.softreset = data;
    *(volatile U32 *)REG_DEBUG_TEST_SOFT_OR_DLLRESET_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SOFT_OR_DLLRESET_Softreset(void)
{
    GH_DEBUG_TEST_SOFT_OR_DLLRESET_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SOFT_OR_DLLRESET_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.softreset;
}
GH_INLINE void GH_DEBUG_TEST_set_SOFT_OR_DLLRESET_dll_rst_l(U8 data)
{
    GH_DEBUG_TEST_SOFT_OR_DLLRESET_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SOFT_OR_DLLRESET_REAL;
    d.bitc.dll_rst_l = data;
    *(volatile U32 *)REG_DEBUG_TEST_SOFT_OR_DLLRESET_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SOFT_OR_DLLRESET_dll_rst_l(void)
{
    GH_DEBUG_TEST_SOFT_OR_DLLRESET_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SOFT_OR_DLLRESET_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dll_rst_l;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_FIO_RESET (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_FIO_RESET(U32 data)
{
    GH_DEBUG_TEST_FIO_RESET_REAL_S real;
    GH_DEBUG_TEST_FIO_RESET_S dummy;
    dummy.all = data ;
    real.bitc.flashreset = dummy.bitc.flashreset;
    real.bitc.xdreset = dummy.bitc.xdreset;
    real.bitc.cfreset = dummy.bitc.cfreset;
    real.bitc.fioreset = dummy.bitc.fioreset;
    *(volatile U32 *)REG_DEBUG_TEST_FIO_RESET_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_FIO_RESET(void)
{
    GH_DEBUG_TEST_FIO_RESET_REAL_S real;
    GH_DEBUG_TEST_FIO_RESET_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_FIO_RESET_REAL);

    dummy.bitc.flashreset = real.bitc.flashreset;
    dummy.bitc.xdreset = real.bitc.xdreset;
    dummy.bitc.cfreset = real.bitc.cfreset;
    dummy.bitc.fioreset = real.bitc.fioreset;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_FIO_RESET_flashreset(U8 data)
{
    GH_DEBUG_TEST_FIO_RESET_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_FIO_RESET_REAL;
    d.bitc.flashreset = data;
    *(volatile U32 *)REG_DEBUG_TEST_FIO_RESET_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_FIO_RESET_flashreset(void)
{
    GH_DEBUG_TEST_FIO_RESET_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_FIO_RESET_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.flashreset;
}
GH_INLINE void GH_DEBUG_TEST_set_FIO_RESET_xdreset(U8 data)
{
    GH_DEBUG_TEST_FIO_RESET_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_FIO_RESET_REAL;
    d.bitc.xdreset = data;
    *(volatile U32 *)REG_DEBUG_TEST_FIO_RESET_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_FIO_RESET_xdreset(void)
{
    GH_DEBUG_TEST_FIO_RESET_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_FIO_RESET_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.xdreset;
}
GH_INLINE void GH_DEBUG_TEST_set_FIO_RESET_cfreset(U8 data)
{
    GH_DEBUG_TEST_FIO_RESET_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_FIO_RESET_REAL;
    d.bitc.cfreset = data;
    *(volatile U32 *)REG_DEBUG_TEST_FIO_RESET_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_FIO_RESET_cfreset(void)
{
    GH_DEBUG_TEST_FIO_RESET_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_FIO_RESET_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cfreset;
}
GH_INLINE void GH_DEBUG_TEST_set_FIO_RESET_fioreset(U8 data)
{
    GH_DEBUG_TEST_FIO_RESET_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_FIO_RESET_REAL;
    d.bitc.fioreset = data;
    *(volatile U32 *)REG_DEBUG_TEST_FIO_RESET_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_FIO_RESET_fioreset(void)
{
    GH_DEBUG_TEST_FIO_RESET_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_FIO_RESET_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fioreset;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_WDT_RST_L (read)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TEST_get_WDT_RST_L(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_WDT_RST_L_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_USB (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_SCALER_USB(U32 data)
{
    GH_DEBUG_TEST_SCALER_USB_REAL_S real;
    GH_DEBUG_TEST_SCALER_USB_S dummy;
    dummy.all = data ;
    real.bitc.div = dummy.bitc.div;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_USB_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_USB(void)
{
    GH_DEBUG_TEST_SCALER_USB_REAL_S real;
    GH_DEBUG_TEST_SCALER_USB_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_USB_REAL);

    dummy.bitc.div = real.bitc.div;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_USB_Div(U16 data)
{
    GH_DEBUG_TEST_SCALER_USB_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_USB_REAL;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_USB_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_USB_Div(void)
{
    GH_DEBUG_TEST_SCALER_USB_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_USB_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.div;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CLK_DEBOUNCE (read/write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_CLK_DEBOUNCE(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CLK_DEBOUNCE_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_CLK_DEBOUNCE(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLK_DEBOUNCE_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_PWM (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_CG_PWM(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CG_PWM_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_PWM(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_PWM_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_USBP_CTRL (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL(U32 data)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S real;
    GH_DEBUG_TEST_USBP_CTRL_S dummy;
    dummy.all = data ;
    real.bitc.refclkdiv = dummy.bitc.refclkdiv;
    real.bitc.usbphy_reset = dummy.bitc.usbphy_reset;
    real.bitc.refclksel = dummy.bitc.refclksel;
    real.bitc.commononn = dummy.bitc.commononn;
    real.bitc.compdistune = dummy.bitc.compdistune;
    real.bitc.otgtune = dummy.bitc.otgtune;
    real.bitc.sqrxtune = dummy.bitc.sqrxtune;
    real.bitc.rxfslstune = dummy.bitc.rxfslstune;
    real.bitc.txpreemphasistune = dummy.bitc.txpreemphasistune;
    real.bitc.txrisetune = dummy.bitc.txrisetune;
    real.bitc.txvreftune = dummy.bitc.txvreftune;
    real.bitc.txhsxvtune = dummy.bitc.txhsxvtune;
    real.bitc.atereset = dummy.bitc.atereset;
    real.bitc.usbdcsoftreset = dummy.bitc.usbdcsoftreset;
    real.bitc.sleepm = dummy.bitc.sleepm;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_USBP_CTRL(void)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S real;
    GH_DEBUG_TEST_USBP_CTRL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL);

    dummy.bitc.refclkdiv = real.bitc.refclkdiv;
    dummy.bitc.usbphy_reset = real.bitc.usbphy_reset;
    dummy.bitc.refclksel = real.bitc.refclksel;
    dummy.bitc.commononn = real.bitc.commononn;
    dummy.bitc.compdistune = real.bitc.compdistune;
    dummy.bitc.otgtune = real.bitc.otgtune;
    dummy.bitc.sqrxtune = real.bitc.sqrxtune;
    dummy.bitc.rxfslstune = real.bitc.rxfslstune;
    dummy.bitc.txpreemphasistune = real.bitc.txpreemphasistune;
    dummy.bitc.txrisetune = real.bitc.txrisetune;
    dummy.bitc.txvreftune = real.bitc.txvreftune;
    dummy.bitc.txhsxvtune = real.bitc.txhsxvtune;
    dummy.bitc.atereset = real.bitc.atereset;
    dummy.bitc.usbdcsoftreset = real.bitc.usbdcsoftreset;
    dummy.bitc.sleepm = real.bitc.sleepm;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_refclkdiv(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL;
    d.bitc.refclkdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_refclkdiv(void)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.refclkdiv;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_usbphy_reset(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL;
    d.bitc.usbphy_reset = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_usbphy_reset(void)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.usbphy_reset;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_refclksel(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL;
    d.bitc.refclksel = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_refclksel(void)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.refclksel;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_commononn(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL;
    d.bitc.commononn = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_commononn(void)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.commononn;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_compdistune(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL;
    d.bitc.compdistune = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_compdistune(void)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.compdistune;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_otgtune(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL;
    d.bitc.otgtune = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_otgtune(void)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.otgtune;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_sqrxtune(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL;
    d.bitc.sqrxtune = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_sqrxtune(void)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sqrxtune;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_rxfslstune(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL;
    d.bitc.rxfslstune = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_rxfslstune(void)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxfslstune;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_txpreemphasistune(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL;
    d.bitc.txpreemphasistune = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_txpreemphasistune(void)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.txpreemphasistune;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_txrisetune(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL;
    d.bitc.txrisetune = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_txrisetune(void)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.txrisetune;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_txvreftune(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL;
    d.bitc.txvreftune = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_txvreftune(void)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.txvreftune;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_txhsxvtune(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL;
    d.bitc.txhsxvtune = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_txhsxvtune(void)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.txhsxvtune;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_ATERESET(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL;
    d.bitc.atereset = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_ATERESET(void)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.atereset;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_USBDCsoftreset(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL;
    d.bitc.usbdcsoftreset = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_USBDCsoftreset(void)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.usbdcsoftreset;
}
GH_INLINE void GH_DEBUG_TEST_set_USBP_CTRL_SLEEPM(U8 data)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL;
    d.bitc.sleepm = data;
    *(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USBP_CTRL_SLEEPM(void)
{
    GH_DEBUG_TEST_USBP_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USBP_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sleepm;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CKEN_VDSP (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_CKEN_VDSP(U32 data)
{
    GH_DEBUG_TEST_CKEN_VDSP_REAL_S real;
    GH_DEBUG_TEST_CKEN_VDSP_S dummy;
    dummy.all = data ;
    real.bitc.cken_tsfm = dummy.bitc.cken_tsfm;
    real.bitc.cken_code = dummy.bitc.cken_code;
    real.bitc.cken_smem = dummy.bitc.cken_smem;
    *(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_CKEN_VDSP(void)
{
    GH_DEBUG_TEST_CKEN_VDSP_REAL_S real;
    GH_DEBUG_TEST_CKEN_VDSP_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP_REAL);

    dummy.bitc.cken_tsfm = real.bitc.cken_tsfm;
    dummy.bitc.cken_code = real.bitc.cken_code;
    dummy.bitc.cken_smem = real.bitc.cken_smem;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_CKEN_VDSP_cken_tsfm(U8 data)
{
    GH_DEBUG_TEST_CKEN_VDSP_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP_REAL;
    d.bitc.cken_tsfm = data;
    *(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_CKEN_VDSP_cken_tsfm(void)
{
    GH_DEBUG_TEST_CKEN_VDSP_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cken_tsfm;
}
GH_INLINE void GH_DEBUG_TEST_set_CKEN_VDSP_cken_code(U8 data)
{
    GH_DEBUG_TEST_CKEN_VDSP_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP_REAL;
    d.bitc.cken_code = data;
    *(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_CKEN_VDSP_cken_code(void)
{
    GH_DEBUG_TEST_CKEN_VDSP_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cken_code;
}
GH_INLINE void GH_DEBUG_TEST_set_CKEN_VDSP_cken_smem(U8 data)
{
    GH_DEBUG_TEST_CKEN_VDSP_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP_REAL;
    d.bitc.cken_smem = data;
    *(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_CKEN_VDSP_cken_smem(void)
{
    GH_DEBUG_TEST_CKEN_VDSP_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CKEN_VDSP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cken_smem;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_DLL0 (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_DLL0(U32 data)
{
    GH_DEBUG_TEST_DLL0_REAL_S real;
    GH_DEBUG_TEST_DLL0_S dummy;
    dummy.all = data ;
    real.bitc.dll_sel2 = dummy.bitc.dll_sel2;
    real.bitc.dll_sel1 = dummy.bitc.dll_sel1;
    real.bitc.dll_sel0 = dummy.bitc.dll_sel0;
    *(volatile U32 *)REG_DEBUG_TEST_DLL0_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_DLL0(void)
{
    GH_DEBUG_TEST_DLL0_REAL_S real;
    GH_DEBUG_TEST_DLL0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_DLL0_REAL);

    dummy.bitc.dll_sel2 = real.bitc.dll_sel2;
    dummy.bitc.dll_sel1 = real.bitc.dll_sel1;
    dummy.bitc.dll_sel0 = real.bitc.dll_sel0;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL0_DLL_SEL2(U8 data)
{
    GH_DEBUG_TEST_DLL0_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL0_REAL;
    d.bitc.dll_sel2 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL0_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL0_DLL_SEL2(void)
{
    GH_DEBUG_TEST_DLL0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dll_sel2;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL0_DLL_SEL1(U8 data)
{
    GH_DEBUG_TEST_DLL0_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL0_REAL;
    d.bitc.dll_sel1 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL0_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL0_DLL_SEL1(void)
{
    GH_DEBUG_TEST_DLL0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dll_sel1;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL0_DLL_SEL0(U8 data)
{
    GH_DEBUG_TEST_DLL0_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL0_REAL;
    d.bitc.dll_sel0 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL0_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL0_DLL_SEL0(void)
{
    GH_DEBUG_TEST_DLL0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dll_sel0;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_DLL1 (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_DLL1(U32 data)
{
    GH_DEBUG_TEST_DLL1_REAL_S real;
    GH_DEBUG_TEST_DLL1_S dummy;
    dummy.all = data ;
    real.bitc.dll_sel2 = dummy.bitc.dll_sel2;
    real.bitc.dll_sel1 = dummy.bitc.dll_sel1;
    real.bitc.dll_sel0 = dummy.bitc.dll_sel0;
    *(volatile U32 *)REG_DEBUG_TEST_DLL1_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_DLL1(void)
{
    GH_DEBUG_TEST_DLL1_REAL_S real;
    GH_DEBUG_TEST_DLL1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_DLL1_REAL);

    dummy.bitc.dll_sel2 = real.bitc.dll_sel2;
    dummy.bitc.dll_sel1 = real.bitc.dll_sel1;
    dummy.bitc.dll_sel0 = real.bitc.dll_sel0;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL1_DLL_SEL2(U8 data)
{
    GH_DEBUG_TEST_DLL1_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL1_REAL;
    d.bitc.dll_sel2 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL1_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL1_DLL_SEL2(void)
{
    GH_DEBUG_TEST_DLL1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dll_sel2;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL1_DLL_SEL1(U8 data)
{
    GH_DEBUG_TEST_DLL1_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL1_REAL;
    d.bitc.dll_sel1 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL1_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL1_DLL_SEL1(void)
{
    GH_DEBUG_TEST_DLL1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dll_sel1;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL1_DLL_SEL0(U8 data)
{
    GH_DEBUG_TEST_DLL1_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL1_REAL;
    d.bitc.dll_sel0 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL1_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL1_DLL_SEL0(void)
{
    GH_DEBUG_TEST_DLL1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dll_sel0;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_ADC (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_SCALER_ADC(U32 data)
{
    GH_DEBUG_TEST_SCALER_ADC_REAL_S real;
    GH_DEBUG_TEST_SCALER_ADC_S dummy;
    dummy.all = data ;
    real.bitc.div = dummy.bitc.div;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_ADC_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_ADC(void)
{
    GH_DEBUG_TEST_SCALER_ADC_REAL_S real;
    GH_DEBUG_TEST_SCALER_ADC_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_ADC_REAL);

    dummy.bitc.div = real.bitc.div;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_ADC_Div(U16 data)
{
    GH_DEBUG_TEST_SCALER_ADC_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_ADC_REAL;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_ADC_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_ADC_Div(void)
{
    GH_DEBUG_TEST_SCALER_ADC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_ADC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.div;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_VIDEO_POST (read/write)                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO_POST(U32 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO_POST_REAL_S real;
    GH_DEBUG_TEST_SCALER_VIDEO_POST_S dummy;
    dummy.all = data ;
    real.bitc.div = dummy.bitc.div;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO_POST_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_VIDEO_POST(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO_POST_REAL_S real;
    GH_DEBUG_TEST_SCALER_VIDEO_POST_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO_POST_REAL);

    dummy.bitc.div = real.bitc.div;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO_POST_Div(U16 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO_POST_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO_POST_REAL;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO_POST_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_VIDEO_POST_Div(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO_POST_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO_POST_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.div;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CLK_REF_AU_EXTERNAL (read/write)                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_CLK_REF_AU_EXTERNAL(U32 data)
{
    GH_DEBUG_TEST_CLK_REF_AU_EXTERNAL_REAL_S real;
    GH_DEBUG_TEST_CLK_REF_AU_EXTERNAL_S dummy;
    dummy.all = data ;
    real.bitc.external = dummy.bitc.external;
    *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_AU_EXTERNAL_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_CLK_REF_AU_EXTERNAL(void)
{
    GH_DEBUG_TEST_CLK_REF_AU_EXTERNAL_REAL_S real;
    GH_DEBUG_TEST_CLK_REF_AU_EXTERNAL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_CLK_REF_AU_EXTERNAL_REAL);

    dummy.bitc.external = real.bitc.external;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_CLK_REF_AU_EXTERNAL_external(U8 data)
{
    GH_DEBUG_TEST_CLK_REF_AU_EXTERNAL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_AU_EXTERNAL_REAL;
    d.bitc.external = data;
    *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_AU_EXTERNAL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_CLK_REF_AU_EXTERNAL_external(void)
{
    GH_DEBUG_TEST_CLK_REF_AU_EXTERNAL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLK_REF_AU_EXTERNAL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.external;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_USE_EXTERNAL_CLK_AU (read/write)                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_USE_EXTERNAL_CLK_AU(U32 data)
{
    GH_DEBUG_TEST_USE_EXTERNAL_CLK_AU_REAL_S real;
    GH_DEBUG_TEST_USE_EXTERNAL_CLK_AU_S dummy;
    dummy.all = data ;
    real.bitc.external = dummy.bitc.external;
    *(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_CLK_AU_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_USE_EXTERNAL_CLK_AU(void)
{
    GH_DEBUG_TEST_USE_EXTERNAL_CLK_AU_REAL_S real;
    GH_DEBUG_TEST_USE_EXTERNAL_CLK_AU_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_CLK_AU_REAL);

    dummy.bitc.external = real.bitc.external;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_USE_EXTERNAL_CLK_AU_external(U8 data)
{
    GH_DEBUG_TEST_USE_EXTERNAL_CLK_AU_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_CLK_AU_REAL;
    d.bitc.external = data;
    *(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_CLK_AU_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USE_EXTERNAL_CLK_AU_external(void)
{
    GH_DEBUG_TEST_USE_EXTERNAL_CLK_AU_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_CLK_AU_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.external;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL (read/write)                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_CLK_REF_VIDEO_EXTERNAL(U32 data)
{
    GH_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL_REAL_S real;
    GH_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL_S dummy;
    dummy.all = data ;
    real.bitc.external = dummy.bitc.external;
    *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_CLK_REF_VIDEO_EXTERNAL(void)
{
    GH_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL_REAL_S real;
    GH_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL_REAL);

    dummy.bitc.external = real.bitc.external;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_CLK_REF_VIDEO_EXTERNAL_external(U8 data)
{
    GH_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL_REAL;
    d.bitc.external = data;
    *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_CLK_REF_VIDEO_EXTERNAL_external(void)
{
    GH_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO_EXTERNAL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.external;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_USE_EXTERNAL_VD_CLK (read/write)                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_USE_EXTERNAL_VD_CLK(U32 data)
{
    GH_DEBUG_TEST_USE_EXTERNAL_VD_CLK_REAL_S real;
    GH_DEBUG_TEST_USE_EXTERNAL_VD_CLK_S dummy;
    dummy.all = data ;
    real.bitc.external = dummy.bitc.external;
    *(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD_CLK_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_USE_EXTERNAL_VD_CLK(void)
{
    GH_DEBUG_TEST_USE_EXTERNAL_VD_CLK_REAL_S real;
    GH_DEBUG_TEST_USE_EXTERNAL_VD_CLK_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD_CLK_REAL);

    dummy.bitc.external = real.bitc.external;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_USE_EXTERNAL_VD_CLK_external(U8 data)
{
    GH_DEBUG_TEST_USE_EXTERNAL_VD_CLK_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD_CLK_REAL;
    d.bitc.external = data;
    *(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD_CLK_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USE_EXTERNAL_VD_CLK_external(void)
{
    GH_DEBUG_TEST_USE_EXTERNAL_VD_CLK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD_CLK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.external;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_USE_CLK_SI_4_CLK_AU (read/write)                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_AU(U32 data)
{
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_AU_REAL_S real;
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_AU_S dummy;
    dummy.all = data ;
    real.bitc.pllref = dummy.bitc.pllref;
    *(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_AU_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_AU(void)
{
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_AU_REAL_S real;
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_AU_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_AU_REAL);

    dummy.bitc.pllref = real.bitc.pllref;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_AU_PLLref(U8 data)
{
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_AU_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_AU_REAL;
    d.bitc.pllref = data;
    *(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_AU_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_AU_PLLref(void)
{
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_AU_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_AU_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pllref;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_USE_CLK_SI_4_CLK_VO (read/write)                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_VO(U32 data)
{
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO_REAL_S real;
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO_S dummy;
    dummy.all = data ;
    real.bitc.pllref = dummy.bitc.pllref;
    *(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_VO(void)
{
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO_REAL_S real;
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO_REAL);

    dummy.bitc.pllref = real.bitc.pllref;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_VO_PLLref(U8 data)
{
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO_REAL;
    d.bitc.pllref = data;
    *(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_VO_PLLref(void)
{
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pllref;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CLK_SI_INPUT_MODE (read/write)                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_CLK_SI_INPUT_MODE(U32 data)
{
    GH_DEBUG_TEST_CLK_SI_INPUT_MODE_REAL_S real;
    GH_DEBUG_TEST_CLK_SI_INPUT_MODE_S dummy;
    dummy.all = data ;
    real.bitc.clk_si = dummy.bitc.clk_si;
    *(volatile U32 *)REG_DEBUG_TEST_CLK_SI_INPUT_MODE_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_CLK_SI_INPUT_MODE(void)
{
    GH_DEBUG_TEST_CLK_SI_INPUT_MODE_REAL_S real;
    GH_DEBUG_TEST_CLK_SI_INPUT_MODE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_CLK_SI_INPUT_MODE_REAL);

    dummy.bitc.clk_si = real.bitc.clk_si;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_CLK_SI_INPUT_MODE_clk_si(U8 data)
{
    GH_DEBUG_TEST_CLK_SI_INPUT_MODE_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CLK_SI_INPUT_MODE_REAL;
    d.bitc.clk_si = data;
    *(volatile U32 *)REG_DEBUG_TEST_CLK_SI_INPUT_MODE_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_CLK_SI_INPUT_MODE_clk_si(void)
{
    GH_DEBUG_TEST_CLK_SI_INPUT_MODE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLK_SI_INPUT_MODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clk_si;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_VIDEO2_CTRL (read/write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL(U32 data)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL_REAL_S real;
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL_S dummy;
    dummy.all = data ;
    real.bitc.pll_lock = dummy.bitc.pll_lock;
    real.bitc.gclk_vo = dummy.bitc.gclk_vo;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL(void)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL_REAL_S real;
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL_REAL);

    dummy.bitc.pll_lock = real.bitc.pll_lock;
    dummy.bitc.gclk_vo = real.bitc.gclk_vo;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL_pll_lock(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL_REAL;
    d.bitc.pll_lock = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL_pll_lock(void)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_lock;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL_gclk_vo(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL_REAL;
    d.bitc.gclk_vo = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL_gclk_vo(void)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gclk_vo;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_VIDEO2_FRAC (read/write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO2_FRAC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_FRAC_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_VIDEO2_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_FRAC_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_VIDEO2 (read/write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO2(U32 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_REAL_S real;
    GH_DEBUG_TEST_SCALER_VIDEO2_S dummy;
    dummy.all = data ;
    real.bitc.integerdiv = dummy.bitc.integerdiv;
    real.bitc.primediv = dummy.bitc.primediv;
    real.bitc.dutycycle = dummy.bitc.dutycycle;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_VIDEO2(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_REAL_S real;
    GH_DEBUG_TEST_SCALER_VIDEO2_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_REAL);

    dummy.bitc.integerdiv = real.bitc.integerdiv;
    dummy.bitc.primediv = real.bitc.primediv;
    dummy.bitc.dutycycle = real.bitc.dutycycle;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO2_IntegerDiv(U16 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_REAL;
    d.bitc.integerdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_VIDEO2_IntegerDiv(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.integerdiv;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO2_PrimeDiv(U8 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_REAL;
    d.bitc.primediv = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SCALER_VIDEO2_PrimeDiv(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.primediv;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO2_DutyCycle(U8 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_REAL;
    d.bitc.dutycycle = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SCALER_VIDEO2_DutyCycle(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dutycycle;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_VIDEO2_POST (read/write)                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO2_POST(U32 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_POST_REAL_S real;
    GH_DEBUG_TEST_SCALER_VIDEO2_POST_S dummy;
    dummy.all = data ;
    real.bitc.integerdiv = dummy.bitc.integerdiv;
    real.bitc.primediv = dummy.bitc.primediv;
    real.bitc.dutycycle = dummy.bitc.dutycycle;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_VIDEO2_POST(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_POST_REAL_S real;
    GH_DEBUG_TEST_SCALER_VIDEO2_POST_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST_REAL);

    dummy.bitc.integerdiv = real.bitc.integerdiv;
    dummy.bitc.primediv = real.bitc.primediv;
    dummy.bitc.dutycycle = real.bitc.dutycycle;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO2_POST_IntegerDiv(U16 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_POST_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST_REAL;
    d.bitc.integerdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_SCALER_VIDEO2_POST_IntegerDiv(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_POST_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.integerdiv;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO2_POST_PrimeDiv(U8 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_POST_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST_REAL;
    d.bitc.primediv = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SCALER_VIDEO2_POST_PrimeDiv(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_POST_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.primediv;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_VIDEO2_POST_DutyCycle(U8 data)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_POST_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST_REAL;
    d.bitc.dutycycle = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SCALER_VIDEO2_POST_DutyCycle(void)
{
    GH_DEBUG_TEST_SCALER_VIDEO2_POST_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_VIDEO2_POST_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dutycycle;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_USE_CLK_SI_4_CLK_VO2 (read/write)                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_VO2(U32 data)
{
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2_REAL_S real;
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2_S dummy;
    dummy.all = data ;
    real.bitc.pllref = dummy.bitc.pllref;
    *(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_VO2(void)
{
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2_REAL_S real;
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2_REAL);

    dummy.bitc.pllref = real.bitc.pllref;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_VO2_PLLref(U8 data)
{
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2_REAL;
    d.bitc.pllref = data;
    *(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USE_CLK_SI_4_CLK_VO2_PLLref(void)
{
    GH_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_CLK_SI_4_CLK_VO2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pllref;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_USE_EXTERNAL_VD2_CLK (read/write)                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_USE_EXTERNAL_VD2_CLK(U32 data)
{
    GH_DEBUG_TEST_USE_EXTERNAL_VD2_CLK_REAL_S real;
    GH_DEBUG_TEST_USE_EXTERNAL_VD2_CLK_S dummy;
    dummy.all = data ;
    real.bitc.external = dummy.bitc.external;
    *(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD2_CLK_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_USE_EXTERNAL_VD2_CLK(void)
{
    GH_DEBUG_TEST_USE_EXTERNAL_VD2_CLK_REAL_S real;
    GH_DEBUG_TEST_USE_EXTERNAL_VD2_CLK_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD2_CLK_REAL);

    dummy.bitc.external = real.bitc.external;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_USE_EXTERNAL_VD2_CLK_external(U8 data)
{
    GH_DEBUG_TEST_USE_EXTERNAL_VD2_CLK_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD2_CLK_REAL;
    d.bitc.external = data;
    *(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD2_CLK_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_USE_EXTERNAL_VD2_CLK_external(void)
{
    GH_DEBUG_TEST_USE_EXTERNAL_VD2_CLK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_EXTERNAL_VD2_CLK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.external;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL (read/write)                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_CLK_REF_VIDEO2_EXTERNAL(U32 data)
{
    GH_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL_REAL_S real;
    GH_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL_S dummy;
    dummy.all = data ;
    real.bitc.external = dummy.bitc.external;
    *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_CLK_REF_VIDEO2_EXTERNAL(void)
{
    GH_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL_REAL_S real;
    GH_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL_REAL);

    dummy.bitc.external = real.bitc.external;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_CLK_REF_VIDEO2_EXTERNAL_external(U8 data)
{
    GH_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL_REAL;
    d.bitc.external = data;
    *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_CLK_REF_VIDEO2_EXTERNAL_external(void)
{
    GH_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLK_REF_VIDEO2_EXTERNAL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.external;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_DDR_CTRL (read/write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_DDR_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_DDR_CTRL_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_DDR_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_DDR_CTRL_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_DDR_FRAC (read/write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_DDR_FRAC(U32 data)
{
    GH_DEBUG_TEST_PLL_DDR_FRAC_REAL_S real;
    GH_DEBUG_TEST_PLL_DDR_FRAC_S dummy;
    dummy.all = data ;
    real.bitc.fraction = dummy.bitc.fraction;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_DDR_FRAC_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_DDR_FRAC(void)
{
    GH_DEBUG_TEST_PLL_DDR_FRAC_REAL_S real;
    GH_DEBUG_TEST_PLL_DDR_FRAC_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_PLL_DDR_FRAC_REAL);

    dummy.bitc.fraction = real.bitc.fraction;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_DDR_FRAC_fraction(U16 data)
{
    GH_DEBUG_TEST_PLL_DDR_FRAC_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_DDR_FRAC_REAL;
    d.bitc.fraction = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_DDR_FRAC_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_PLL_DDR_FRAC_fraction(void)
{
    GH_DEBUG_TEST_PLL_DDR_FRAC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_DDR_FRAC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fraction;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_IDSP_CTRL (read/write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_IDSP_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_IDSP_FRAC (read/write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_FRAC(U32 data)
{
    GH_DEBUG_TEST_PLL_IDSP_FRAC_REAL_S real;
    GH_DEBUG_TEST_PLL_IDSP_FRAC_S dummy;
    dummy.all = data ;
    real.bitc.fraction = dummy.bitc.fraction;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_FRAC_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_IDSP_FRAC(void)
{
    GH_DEBUG_TEST_PLL_IDSP_FRAC_REAL_S real;
    GH_DEBUG_TEST_PLL_IDSP_FRAC_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_FRAC_REAL);

    dummy.bitc.fraction = real.bitc.fraction;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_FRAC_fraction(U16 data)
{
    GH_DEBUG_TEST_PLL_IDSP_FRAC_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_FRAC_REAL;
    d.bitc.fraction = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_FRAC_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_PLL_IDSP_FRAC_fraction(void)
{
    GH_DEBUG_TEST_PLL_IDSP_FRAC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_FRAC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fraction;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_SSI2 (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_CG_SSI2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CG_SSI2_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_SSI2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_SSI2_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_LVDS_LVCMOS (read/write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_LVDS_LVCMOS(U32 data)
{
    GH_DEBUG_TEST_LVDS_LVCMOS_REAL_S real;
    GH_DEBUG_TEST_LVDS_LVCMOS_S dummy;
    dummy.all = data ;
    real.bitc.lvcoms_sd = dummy.bitc.lvcoms_sd;
    real.bitc.lvcmos_spclk = dummy.bitc.lvcmos_spclk;
    *(volatile U32 *)REG_DEBUG_TEST_LVDS_LVCMOS_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_LVDS_LVCMOS(void)
{
    GH_DEBUG_TEST_LVDS_LVCMOS_REAL_S real;
    GH_DEBUG_TEST_LVDS_LVCMOS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_LVDS_LVCMOS_REAL);

    dummy.bitc.lvcoms_sd = real.bitc.lvcoms_sd;
    dummy.bitc.lvcmos_spclk = real.bitc.lvcmos_spclk;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_LVDS_LVCMOS_lvcoms_sd(U16 data)
{
    GH_DEBUG_TEST_LVDS_LVCMOS_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_LVDS_LVCMOS_REAL;
    d.bitc.lvcoms_sd = data;
    *(volatile U32 *)REG_DEBUG_TEST_LVDS_LVCMOS_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_LVDS_LVCMOS_lvcoms_sd(void)
{
    GH_DEBUG_TEST_LVDS_LVCMOS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_LVDS_LVCMOS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.lvcoms_sd;
}
GH_INLINE void GH_DEBUG_TEST_set_LVDS_LVCMOS_lvcmos_spclk(U8 data)
{
    GH_DEBUG_TEST_LVDS_LVCMOS_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_LVDS_LVCMOS_REAL;
    d.bitc.lvcmos_spclk = data;
    *(volatile U32 *)REG_DEBUG_TEST_LVDS_LVCMOS_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_LVDS_LVCMOS_lvcmos_spclk(void)
{
    GH_DEBUG_TEST_LVDS_LVCMOS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_LVDS_LVCMOS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.lvcmos_spclk;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_LVDS_ASYNC (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_LVDS_ASYNC(U32 data)
{
    GH_DEBUG_TEST_LVDS_ASYNC_REAL_S real;
    GH_DEBUG_TEST_LVDS_ASYNC_S dummy;
    dummy.all = data ;
    real.bitc.async_sd = dummy.bitc.async_sd;
    real.bitc.async_spclk = dummy.bitc.async_spclk;
    real.bitc.lvds_pd = dummy.bitc.lvds_pd;
    real.bitc.lvds_ib_ctrl = dummy.bitc.lvds_ib_ctrl;
    real.bitc.lvds_bit_mode = dummy.bitc.lvds_bit_mode;
    *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_LVDS_ASYNC(void)
{
    GH_DEBUG_TEST_LVDS_ASYNC_REAL_S real;
    GH_DEBUG_TEST_LVDS_ASYNC_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC_REAL);

    dummy.bitc.async_sd = real.bitc.async_sd;
    dummy.bitc.async_spclk = real.bitc.async_spclk;
    dummy.bitc.lvds_pd = real.bitc.lvds_pd;
    dummy.bitc.lvds_ib_ctrl = real.bitc.lvds_ib_ctrl;
    dummy.bitc.lvds_bit_mode = real.bitc.lvds_bit_mode;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_LVDS_ASYNC_async_sd(U16 data)
{
    GH_DEBUG_TEST_LVDS_ASYNC_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC_REAL;
    d.bitc.async_sd = data;
    *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_LVDS_ASYNC_async_sd(void)
{
    GH_DEBUG_TEST_LVDS_ASYNC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.async_sd;
}
GH_INLINE void GH_DEBUG_TEST_set_LVDS_ASYNC_async_spclk(U8 data)
{
    GH_DEBUG_TEST_LVDS_ASYNC_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC_REAL;
    d.bitc.async_spclk = data;
    *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_LVDS_ASYNC_async_spclk(void)
{
    GH_DEBUG_TEST_LVDS_ASYNC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.async_spclk;
}
GH_INLINE void GH_DEBUG_TEST_set_LVDS_ASYNC_lvds_pd(U8 data)
{
    GH_DEBUG_TEST_LVDS_ASYNC_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC_REAL;
    d.bitc.lvds_pd = data;
    *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_LVDS_ASYNC_lvds_pd(void)
{
    GH_DEBUG_TEST_LVDS_ASYNC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.lvds_pd;
}
GH_INLINE void GH_DEBUG_TEST_set_LVDS_ASYNC_lvds_ib_ctrl(U8 data)
{
    GH_DEBUG_TEST_LVDS_ASYNC_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC_REAL;
    d.bitc.lvds_ib_ctrl = data;
    *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_LVDS_ASYNC_lvds_ib_ctrl(void)
{
    GH_DEBUG_TEST_LVDS_ASYNC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.lvds_ib_ctrl;
}
GH_INLINE void GH_DEBUG_TEST_set_LVDS_ASYNC_lvds_bit_mode(U8 data)
{
    GH_DEBUG_TEST_LVDS_ASYNC_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC_REAL;
    d.bitc.lvds_bit_mode = data;
    *(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_LVDS_ASYNC_lvds_bit_mode(void)
{
    GH_DEBUG_TEST_LVDS_ASYNC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_LVDS_ASYNC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.lvds_bit_mode;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_CORE_CTRL2 (read/write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL2(U32 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL2_REAL_S real;
    GH_DEBUG_TEST_PLL_CORE_CTRL2_S dummy;
    dummy.all = data ;
    real.bitc.controllability = dummy.bitc.controllability;
    real.bitc.charge = dummy.bitc.charge;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL2_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_CORE_CTRL2(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL2_REAL_S real;
    GH_DEBUG_TEST_PLL_CORE_CTRL2_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL2_REAL);

    dummy.bitc.controllability = real.bitc.controllability;
    dummy.bitc.charge = real.bitc.charge;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL2_Controllability(U16 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL2_REAL;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL2_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_PLL_CORE_CTRL2_Controllability(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.controllability;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL2_Charge(U8 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL2_REAL;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL2_Charge(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.charge;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_CORE_CTRL3 (read/write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL3(U32 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_REAL_S real;
    GH_DEBUG_TEST_PLL_CORE_CTRL3_S dummy;
    dummy.all = data ;
    real.bitc.vco = dummy.bitc.vco;
    real.bitc.pll_vco = dummy.bitc.pll_vco;
    real.bitc.clamp = dummy.bitc.clamp;
    real.bitc.dsm_dither = dummy.bitc.dsm_dither;
    real.bitc.dsm_dither_gain = dummy.bitc.dsm_dither_gain;
    real.bitc.feedforward = dummy.bitc.feedforward;
    real.bitc.bias = dummy.bitc.bias;
    real.bitc.jdiv = dummy.bitc.jdiv;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_CORE_CTRL3(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_REAL_S real;
    GH_DEBUG_TEST_PLL_CORE_CTRL3_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL);

    dummy.bitc.vco = real.bitc.vco;
    dummy.bitc.pll_vco = real.bitc.pll_vco;
    dummy.bitc.clamp = real.bitc.clamp;
    dummy.bitc.dsm_dither = real.bitc.dsm_dither;
    dummy.bitc.dsm_dither_gain = real.bitc.dsm_dither_gain;
    dummy.bitc.feedforward = real.bitc.feedforward;
    dummy.bitc.bias = real.bitc.bias;
    dummy.bitc.jdiv = real.bitc.jdiv;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_VCO(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_PLL_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_PLL_VCO(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_Clamp(U8 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_Clamp(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clamp;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_DSM_dither(U8 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_DSM_dither(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dsm_dither;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_DSM_dither_gain(U8 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_DSM_dither_gain(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dsm_dither_gain;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_Feedforward(U8 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_Feedforward(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.feedforward;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_Bias(U8 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_Bias(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.bias;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_CTRL3_JDIV(U8 data)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_CORE_CTRL3_JDIV(void)
{
    GH_DEBUG_TEST_PLL_CORE_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.jdiv;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_IDSP_CTRL2 (read/write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL2(U32 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL2_REAL_S real;
    GH_DEBUG_TEST_PLL_IDSP_CTRL2_S dummy;
    dummy.all = data ;
    real.bitc.controllability = dummy.bitc.controllability;
    real.bitc.charge = dummy.bitc.charge;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL2_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_IDSP_CTRL2(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL2_REAL_S real;
    GH_DEBUG_TEST_PLL_IDSP_CTRL2_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL2_REAL);

    dummy.bitc.controllability = real.bitc.controllability;
    dummy.bitc.charge = real.bitc.charge;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL2_Controllability(U16 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL2_REAL;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL2_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_PLL_IDSP_CTRL2_Controllability(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.controllability;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL2_Charge(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL2_REAL;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL2_Charge(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.charge;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_IDSP_CTRL3 (read/write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3(U32 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_REAL_S real;
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_S dummy;
    dummy.all = data ;
    real.bitc.vco = dummy.bitc.vco;
    real.bitc.pll_vco = dummy.bitc.pll_vco;
    real.bitc.clamp = dummy.bitc.clamp;
    real.bitc.dsm_dither = dummy.bitc.dsm_dither;
    real.bitc.dsm_dither_gain = dummy.bitc.dsm_dither_gain;
    real.bitc.feedforward = dummy.bitc.feedforward;
    real.bitc.bias = dummy.bitc.bias;
    real.bitc.jdiv = dummy.bitc.jdiv;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_IDSP_CTRL3(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_REAL_S real;
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL);

    dummy.bitc.vco = real.bitc.vco;
    dummy.bitc.pll_vco = real.bitc.pll_vco;
    dummy.bitc.clamp = real.bitc.clamp;
    dummy.bitc.dsm_dither = real.bitc.dsm_dither;
    dummy.bitc.dsm_dither_gain = real.bitc.dsm_dither_gain;
    dummy.bitc.feedforward = real.bitc.feedforward;
    dummy.bitc.bias = real.bitc.bias;
    dummy.bitc.jdiv = real.bitc.jdiv;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_VCO(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_PLL_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_PLL_VCO(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_Clamp(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_Clamp(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clamp;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_DSM_dither(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_DSM_dither(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dsm_dither;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_DSM_dither_gain(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_DSM_dither_gain(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dsm_dither_gain;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_Feedforward(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_Feedforward(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.feedforward;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_Bias(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_Bias(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.bias;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL3_JDIV(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL3_JDIV(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.jdiv;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_IDSP_CTRL22 (read/write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL22(U32 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL22_REAL_S real;
    GH_DEBUG_TEST_PLL_IDSP_CTRL22_S dummy;
    dummy.all = data ;
    real.bitc.controllability = dummy.bitc.controllability;
    real.bitc.charge = dummy.bitc.charge;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL22_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_IDSP_CTRL22(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL22_REAL_S real;
    GH_DEBUG_TEST_PLL_IDSP_CTRL22_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL22_REAL);

    dummy.bitc.controllability = real.bitc.controllability;
    dummy.bitc.charge = real.bitc.charge;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL22_Controllability(U16 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL22_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL22_REAL;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL22_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_PLL_IDSP_CTRL22_Controllability(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL22_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL22_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.controllability;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL22_Charge(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL22_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL22_REAL;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL22_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL22_Charge(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL22_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL22_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.charge;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_IDSP_CTRL32 (read/write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32(U32 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_REAL_S real;
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_S dummy;
    dummy.all = data ;
    real.bitc.vco = dummy.bitc.vco;
    real.bitc.pll_vco = dummy.bitc.pll_vco;
    real.bitc.clamp = dummy.bitc.clamp;
    real.bitc.dsm_dither = dummy.bitc.dsm_dither;
    real.bitc.dsm_dither_gain = dummy.bitc.dsm_dither_gain;
    real.bitc.feedforward = dummy.bitc.feedforward;
    real.bitc.bias = dummy.bitc.bias;
    real.bitc.jdiv = dummy.bitc.jdiv;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_IDSP_CTRL32(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_REAL_S real;
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL);

    dummy.bitc.vco = real.bitc.vco;
    dummy.bitc.pll_vco = real.bitc.pll_vco;
    dummy.bitc.clamp = real.bitc.clamp;
    dummy.bitc.dsm_dither = real.bitc.dsm_dither;
    dummy.bitc.dsm_dither_gain = real.bitc.dsm_dither_gain;
    dummy.bitc.feedforward = real.bitc.feedforward;
    dummy.bitc.bias = real.bitc.bias;
    dummy.bitc.jdiv = real.bitc.jdiv;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_VCO(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_PLL_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_PLL_VCO(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_Clamp(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_Clamp(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clamp;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_DSM_dither(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_DSM_dither(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dsm_dither;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_DSM_dither_gain(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_DSM_dither_gain(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dsm_dither_gain;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_Feedforward(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_Feedforward(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.feedforward;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_Bias(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_Bias(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.bias;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_CTRL32_JDIV(U8 data)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_IDSP_CTRL32_JDIV(void)
{
    GH_DEBUG_TEST_PLL_IDSP_CTRL32_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_CTRL32_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.jdiv;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_CORE_POST (read/write)                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_SCALER_CORE_POST(U32 data)
{
    GH_DEBUG_TEST_SCALER_CORE_POST_REAL_S real;
    GH_DEBUG_TEST_SCALER_CORE_POST_S dummy;
    dummy.all = data ;
    real.bitc.div = dummy.bitc.div;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_CORE_POST_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_CORE_POST(void)
{
    GH_DEBUG_TEST_SCALER_CORE_POST_REAL_S real;
    GH_DEBUG_TEST_SCALER_CORE_POST_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_CORE_POST_REAL);

    dummy.bitc.div = real.bitc.div;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_CORE_POST_Div(U8 data)
{
    GH_DEBUG_TEST_SCALER_CORE_POST_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_CORE_POST_REAL;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_CORE_POST_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SCALER_CORE_POST_Div(void)
{
    GH_DEBUG_TEST_SCALER_CORE_POST_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_CORE_POST_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.div;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_SENSOR_CTRL2 (read/write)                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL2(U32 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL2_REAL_S real;
    GH_DEBUG_TEST_PLL_SENSOR_CTRL2_S dummy;
    dummy.all = data ;
    real.bitc.controllability = dummy.bitc.controllability;
    real.bitc.charge = dummy.bitc.charge;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL2_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_SENSOR_CTRL2(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL2_REAL_S real;
    GH_DEBUG_TEST_PLL_SENSOR_CTRL2_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL2_REAL);

    dummy.bitc.controllability = real.bitc.controllability;
    dummy.bitc.charge = real.bitc.charge;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL2_Controllability(U16 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL2_REAL;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL2_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_PLL_SENSOR_CTRL2_Controllability(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.controllability;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL2_Charge(U8 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL2_REAL;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL2_Charge(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.charge;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_SENSOR_CTRL3 (read/write)                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3(U32 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL_S real;
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_S dummy;
    dummy.all = data ;
    real.bitc.vco = dummy.bitc.vco;
    real.bitc.pll_vco = dummy.bitc.pll_vco;
    real.bitc.clamp = dummy.bitc.clamp;
    real.bitc.dsm_dither = dummy.bitc.dsm_dither;
    real.bitc.dsm_dither_gain = dummy.bitc.dsm_dither_gain;
    real.bitc.feedforward = dummy.bitc.feedforward;
    real.bitc.bias = dummy.bitc.bias;
    real.bitc.jdiv = dummy.bitc.jdiv;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL_S real;
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL);

    dummy.bitc.vco = real.bitc.vco;
    dummy.bitc.pll_vco = real.bitc.pll_vco;
    dummy.bitc.clamp = real.bitc.clamp;
    dummy.bitc.dsm_dither = real.bitc.dsm_dither;
    dummy.bitc.dsm_dither_gain = real.bitc.dsm_dither_gain;
    dummy.bitc.feedforward = real.bitc.feedforward;
    dummy.bitc.bias = real.bitc.bias;
    dummy.bitc.jdiv = real.bitc.jdiv;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_VCO(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_PLL_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_PLL_VCO(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_Clamp(U8 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_Clamp(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clamp;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_DSM_dither(U8 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_DSM_dither(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dsm_dither;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_DSM_dither_gain(U8 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_DSM_dither_gain(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dsm_dither_gain;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_Feedforward(U8 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_Feedforward(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.feedforward;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_Bias(U8 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_Bias(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.bias;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3_JDIV(U8 data)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_SENSOR_CTRL3_JDIV(void)
{
    GH_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.jdiv;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_AUDIO_CTRL2 (read/write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL2(U32 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL2_REAL_S real;
    GH_DEBUG_TEST_PLL_AUDIO_CTRL2_S dummy;
    dummy.all = data ;
    real.bitc.controllability = dummy.bitc.controllability;
    real.bitc.charge = dummy.bitc.charge;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL2_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_AUDIO_CTRL2(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL2_REAL_S real;
    GH_DEBUG_TEST_PLL_AUDIO_CTRL2_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL2_REAL);

    dummy.bitc.controllability = real.bitc.controllability;
    dummy.bitc.charge = real.bitc.charge;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL2_Controllability(U16 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL2_REAL;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL2_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_PLL_AUDIO_CTRL2_Controllability(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.controllability;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL2_Charge(U8 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL2_REAL;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL2_Charge(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.charge;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_AUDIO_CTRL3 (read/write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3(U32 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL_S real;
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_S dummy;
    dummy.all = data ;
    real.bitc.vco = dummy.bitc.vco;
    real.bitc.pll_vco = dummy.bitc.pll_vco;
    real.bitc.clamp = dummy.bitc.clamp;
    real.bitc.dsm_dither = dummy.bitc.dsm_dither;
    real.bitc.dsm_dither_gain = dummy.bitc.dsm_dither_gain;
    real.bitc.feedforward = dummy.bitc.feedforward;
    real.bitc.bias = dummy.bitc.bias;
    real.bitc.jdiv = dummy.bitc.jdiv;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL_S real;
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL);

    dummy.bitc.vco = real.bitc.vco;
    dummy.bitc.pll_vco = real.bitc.pll_vco;
    dummy.bitc.clamp = real.bitc.clamp;
    dummy.bitc.dsm_dither = real.bitc.dsm_dither;
    dummy.bitc.dsm_dither_gain = real.bitc.dsm_dither_gain;
    dummy.bitc.feedforward = real.bitc.feedforward;
    dummy.bitc.bias = real.bitc.bias;
    dummy.bitc.jdiv = real.bitc.jdiv;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_VCO(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_PLL_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_PLL_VCO(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_Clamp(U8 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_Clamp(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clamp;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_DSM_dither(U8 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_DSM_dither(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dsm_dither;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_DSM_dither_gain(U8 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_DSM_dither_gain(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dsm_dither_gain;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_Feedforward(U8 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_Feedforward(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.feedforward;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_Bias(U8 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_Bias(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.bias;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3_JDIV(U8 data)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_AUDIO_CTRL3_JDIV(void)
{
    GH_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.jdiv;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_VIDEO_CTRL2 (read/write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL2(U32 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL2_REAL_S real;
    GH_DEBUG_TEST_PLL_VIDEO_CTRL2_S dummy;
    dummy.all = data ;
    real.bitc.controllability = dummy.bitc.controllability;
    real.bitc.charge = dummy.bitc.charge;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL2_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_VIDEO_CTRL2(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL2_REAL_S real;
    GH_DEBUG_TEST_PLL_VIDEO_CTRL2_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL2_REAL);

    dummy.bitc.controllability = real.bitc.controllability;
    dummy.bitc.charge = real.bitc.charge;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL2_Controllability(U16 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL2_REAL;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL2_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_PLL_VIDEO_CTRL2_Controllability(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.controllability;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL2_Charge(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL2_REAL;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL2_Charge(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.charge;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_VIDEO_CTRL3 (read/write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3(U32 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL_S real;
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_S dummy;
    dummy.all = data ;
    real.bitc.vco = dummy.bitc.vco;
    real.bitc.pll_vco = dummy.bitc.pll_vco;
    real.bitc.clamp = dummy.bitc.clamp;
    real.bitc.dsm_dither = dummy.bitc.dsm_dither;
    real.bitc.dsm_dither_gain = dummy.bitc.dsm_dither_gain;
    real.bitc.feedforward = dummy.bitc.feedforward;
    real.bitc.bias = dummy.bitc.bias;
    real.bitc.jdiv = dummy.bitc.jdiv;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL_S real;
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL);

    dummy.bitc.vco = real.bitc.vco;
    dummy.bitc.pll_vco = real.bitc.pll_vco;
    dummy.bitc.clamp = real.bitc.clamp;
    dummy.bitc.dsm_dither = real.bitc.dsm_dither;
    dummy.bitc.dsm_dither_gain = real.bitc.dsm_dither_gain;
    dummy.bitc.feedforward = real.bitc.feedforward;
    dummy.bitc.bias = real.bitc.bias;
    dummy.bitc.jdiv = real.bitc.jdiv;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_VCO(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_PLL_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_PLL_VCO(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_Clamp(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_Clamp(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clamp;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_DSM_dither(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_DSM_dither(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dsm_dither;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_DSM_dither_gain(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_DSM_dither_gain(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dsm_dither_gain;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_Feedforward(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_Feedforward(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.feedforward;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_Bias(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_Bias(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.bias;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3_JDIV(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO_CTRL3_JDIV(void)
{
    GH_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.jdiv;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_VIDEO2_CTRL2 (read/write)                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL2(U32 data)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL2_REAL_S real;
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL2_S dummy;
    dummy.all = data ;
    real.bitc.controllability = dummy.bitc.controllability;
    real.bitc.charge = dummy.bitc.charge;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL2_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL2(void)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL2_REAL_S real;
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL2_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL2_REAL);

    dummy.bitc.controllability = real.bitc.controllability;
    dummy.bitc.charge = real.bitc.charge;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL2_Controllability(U16 data)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL2_REAL;
    d.bitc.controllability = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL2_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL2_Controllability(void)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.controllability;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL2_Charge(U8 data)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL2_REAL;
    d.bitc.charge = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_VIDEO2_CTRL2_Charge(void)
{
    GH_DEBUG_TEST_PLL_VIDEO2_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.charge;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_USB_CTRL2 (read/write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_USB_CTRL2(U32 data)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_REAL_S real;
    GH_DEBUG_TEST_PLL_USB_CTRL2_S dummy;
    dummy.all = data ;
    real.bitc.vco = dummy.bitc.vco;
    real.bitc.pll_vco = dummy.bitc.pll_vco;
    real.bitc.clamp = dummy.bitc.clamp;
    real.bitc.dsm_dither = dummy.bitc.dsm_dither;
    real.bitc.dsm_dither_gain = dummy.bitc.dsm_dither_gain;
    real.bitc.feedforward = dummy.bitc.feedforward;
    real.bitc.bias = dummy.bitc.bias;
    real.bitc.jdiv = dummy.bitc.jdiv;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_USB_CTRL2(void)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_REAL_S real;
    GH_DEBUG_TEST_PLL_USB_CTRL2_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL);

    dummy.bitc.vco = real.bitc.vco;
    dummy.bitc.pll_vco = real.bitc.pll_vco;
    dummy.bitc.clamp = real.bitc.clamp;
    dummy.bitc.dsm_dither = real.bitc.dsm_dither;
    dummy.bitc.dsm_dither_gain = real.bitc.dsm_dither_gain;
    dummy.bitc.feedforward = real.bitc.feedforward;
    dummy.bitc.bias = real.bitc.bias;
    dummy.bitc.jdiv = real.bitc.jdiv;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_USB_CTRL2_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL;
    d.bitc.vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_VCO(void)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_USB_CTRL2_PLL_VCO(U8 data)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL;
    d.bitc.pll_vco = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_PLL_VCO(void)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll_vco;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_USB_CTRL2_Clamp(U8 data)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL;
    d.bitc.clamp = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_Clamp(void)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clamp;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_USB_CTRL2_DSM_dither(U8 data)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL;
    d.bitc.dsm_dither = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_DSM_dither(void)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dsm_dither;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_USB_CTRL2_DSM_dither_gain(U8 data)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL;
    d.bitc.dsm_dither_gain = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_DSM_dither_gain(void)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dsm_dither_gain;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_USB_CTRL2_Feedforward(U8 data)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL;
    d.bitc.feedforward = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_Feedforward(void)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.feedforward;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_USB_CTRL2_Bias(U8 data)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL;
    d.bitc.bias = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_Bias(void)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.bias;
}
GH_INLINE void GH_DEBUG_TEST_set_PLL_USB_CTRL2_JDIV(U8 data)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL;
    d.bitc.jdiv = data;
    *(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_PLL_USB_CTRL2_JDIV(void)
{
    GH_DEBUG_TEST_PLL_USB_CTRL2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_USB_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.jdiv;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_DDR_CALIB (read/write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_CG_DDR_CALIB(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CG_DDR_CALIB_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_DDR_CALIB(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_DDR_CALIB_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_DLL_CTRL_SEL (read/write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL(U32 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S real;
    GH_DEBUG_TEST_DLL_CTRL_SEL_S dummy;
    dummy.all = data ;
    real.bitc.rct_ddrio_dll_sbc = dummy.bitc.rct_ddrio_dll_sbc;
    real.bitc.rct_ddrio_dll_selm = dummy.bitc.rct_ddrio_dll_selm;
    real.bitc.rct_ddrio_single_end = dummy.bitc.rct_ddrio_single_end;
    real.bitc.rct_ddrio_pue_dq = dummy.bitc.rct_ddrio_pue_dq;
    real.bitc.rct_ddrio_pde_dq = dummy.bitc.rct_ddrio_pde_dq;
    real.bitc.rct_ddrio_npue_dqs = dummy.bitc.rct_ddrio_npue_dqs;
    real.bitc.rct_ddrio_npde_dqs = dummy.bitc.rct_ddrio_npde_dqs;
    real.bitc.rct_ddrio_ppde_dqs = dummy.bitc.rct_ddrio_ppde_dqs;
    real.bitc.rct_ddrio_ppue_dqs = dummy.bitc.rct_ddrio_ppue_dqs;
    real.bitc.rct_ddrio_cmosrcv = dummy.bitc.rct_ddrio_cmosrcv;
    real.bitc.rct_ddrio_pue_cmd = dummy.bitc.rct_ddrio_pue_cmd;
    real.bitc.rct_ddrio_pde_cmd = dummy.bitc.rct_ddrio_pde_cmd;
    real.bitc.rct_ddrio_npue_dqs2 = dummy.bitc.rct_ddrio_npue_dqs2;
    real.bitc.rct_ddrio_npde_dqs2 = dummy.bitc.rct_ddrio_npde_dqs2;
    real.bitc.rct_ddrio_ppde_dqs2 = dummy.bitc.rct_ddrio_ppde_dqs2;
    real.bitc.rct_ddrio_ppue_dqs2 = dummy.bitc.rct_ddrio_ppue_dqs2;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_DLL_CTRL_SEL(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S real;
    GH_DEBUG_TEST_DLL_CTRL_SEL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL);

    dummy.bitc.rct_ddrio_dll_sbc = real.bitc.rct_ddrio_dll_sbc;
    dummy.bitc.rct_ddrio_dll_selm = real.bitc.rct_ddrio_dll_selm;
    dummy.bitc.rct_ddrio_single_end = real.bitc.rct_ddrio_single_end;
    dummy.bitc.rct_ddrio_pue_dq = real.bitc.rct_ddrio_pue_dq;
    dummy.bitc.rct_ddrio_pde_dq = real.bitc.rct_ddrio_pde_dq;
    dummy.bitc.rct_ddrio_npue_dqs = real.bitc.rct_ddrio_npue_dqs;
    dummy.bitc.rct_ddrio_npde_dqs = real.bitc.rct_ddrio_npde_dqs;
    dummy.bitc.rct_ddrio_ppde_dqs = real.bitc.rct_ddrio_ppde_dqs;
    dummy.bitc.rct_ddrio_ppue_dqs = real.bitc.rct_ddrio_ppue_dqs;
    dummy.bitc.rct_ddrio_cmosrcv = real.bitc.rct_ddrio_cmosrcv;
    dummy.bitc.rct_ddrio_pue_cmd = real.bitc.rct_ddrio_pue_cmd;
    dummy.bitc.rct_ddrio_pde_cmd = real.bitc.rct_ddrio_pde_cmd;
    dummy.bitc.rct_ddrio_npue_dqs2 = real.bitc.rct_ddrio_npue_dqs2;
    dummy.bitc.rct_ddrio_npde_dqs2 = real.bitc.rct_ddrio_npde_dqs2;
    dummy.bitc.rct_ddrio_ppde_dqs2 = real.bitc.rct_ddrio_ppde_dqs2;
    dummy.bitc.rct_ddrio_ppue_dqs2 = real.bitc.rct_ddrio_ppue_dqs2;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_dll_sbc(U16 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL;
    d.bitc.rct_ddrio_dll_sbc = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL = d.all;
}
GH_INLINE U16  GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_dll_sbc(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_dll_sbc;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_dll_selm(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL;
    d.bitc.rct_ddrio_dll_selm = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_dll_selm(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_dll_selm;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_single_end(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL;
    d.bitc.rct_ddrio_single_end = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_single_end(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_single_end;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_pue_dq(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL;
    d.bitc.rct_ddrio_pue_dq = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_pue_dq(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_pue_dq;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_pde_dq(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL;
    d.bitc.rct_ddrio_pde_dq = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_pde_dq(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_pde_dq;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_npue_dqs(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL;
    d.bitc.rct_ddrio_npue_dqs = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_npue_dqs(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_npue_dqs;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_npde_dqs(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL;
    d.bitc.rct_ddrio_npde_dqs = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_npde_dqs(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_npde_dqs;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_ppde_dqs(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL;
    d.bitc.rct_ddrio_ppde_dqs = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_ppde_dqs(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_ppde_dqs;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_ppue_dqs(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL;
    d.bitc.rct_ddrio_ppue_dqs = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_ppue_dqs(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_ppue_dqs;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_cmosrcv(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL;
    d.bitc.rct_ddrio_cmosrcv = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_cmosrcv(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_cmosrcv;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_pue_cmd(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL;
    d.bitc.rct_ddrio_pue_cmd = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_pue_cmd(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_pue_cmd;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_pde_cmd(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL;
    d.bitc.rct_ddrio_pde_cmd = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_pde_cmd(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_pde_cmd;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_npue_dqs2(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL;
    d.bitc.rct_ddrio_npue_dqs2 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_npue_dqs2(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_npue_dqs2;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_npde_dqs2(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL;
    d.bitc.rct_ddrio_npde_dqs2 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_npde_dqs2(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_npde_dqs2;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_ppde_dqs2(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL;
    d.bitc.rct_ddrio_ppde_dqs2 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_ppde_dqs2(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_ppde_dqs2;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_CTRL_SEL_rct_ddrio_ppue_dqs2(U8 data)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL;
    d.bitc.rct_ddrio_ppue_dqs2 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_CTRL_SEL_rct_ddrio_ppue_dqs2(void)
{
    GH_DEBUG_TEST_DLL_CTRL_SEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_CTRL_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_ppue_dqs2;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_DLL_OCD_BITS (read/write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_DLL_OCD_BITS(U32 data)
{
    GH_DEBUG_TEST_DLL_OCD_BITS_REAL_S real;
    GH_DEBUG_TEST_DLL_OCD_BITS_S dummy;
    dummy.all = data ;
    real.bitc.rct_ddrio_ddr2 = dummy.bitc.rct_ddrio_ddr2;
    real.bitc.rct_ddrio_ocd_cmd = dummy.bitc.rct_ddrio_ocd_cmd;
    real.bitc.rct_ddrio_ocd = dummy.bitc.rct_ddrio_ocd;
    real.bitc.rct_ddrio_odt = dummy.bitc.rct_ddrio_odt;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_DLL_OCD_BITS(void)
{
    GH_DEBUG_TEST_DLL_OCD_BITS_REAL_S real;
    GH_DEBUG_TEST_DLL_OCD_BITS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS_REAL);

    dummy.bitc.rct_ddrio_ddr2 = real.bitc.rct_ddrio_ddr2;
    dummy.bitc.rct_ddrio_ocd_cmd = real.bitc.rct_ddrio_ocd_cmd;
    dummy.bitc.rct_ddrio_ocd = real.bitc.rct_ddrio_ocd;
    dummy.bitc.rct_ddrio_odt = real.bitc.rct_ddrio_odt;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_OCD_BITS_rct_ddrio_ddr2(U8 data)
{
    GH_DEBUG_TEST_DLL_OCD_BITS_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS_REAL;
    d.bitc.rct_ddrio_ddr2 = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_OCD_BITS_rct_ddrio_ddr2(void)
{
    GH_DEBUG_TEST_DLL_OCD_BITS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_ddr2;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_OCD_BITS_rct_ddrio_ocd_cmd(U8 data)
{
    GH_DEBUG_TEST_DLL_OCD_BITS_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS_REAL;
    d.bitc.rct_ddrio_ocd_cmd = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_OCD_BITS_rct_ddrio_ocd_cmd(void)
{
    GH_DEBUG_TEST_DLL_OCD_BITS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_ocd_cmd;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_OCD_BITS_rct_ddrio_ocd(U8 data)
{
    GH_DEBUG_TEST_DLL_OCD_BITS_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS_REAL;
    d.bitc.rct_ddrio_ocd = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_OCD_BITS_rct_ddrio_ocd(void)
{
    GH_DEBUG_TEST_DLL_OCD_BITS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_ocd;
}
GH_INLINE void GH_DEBUG_TEST_set_DLL_OCD_BITS_rct_ddrio_odt(U8 data)
{
    GH_DEBUG_TEST_DLL_OCD_BITS_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS_REAL;
    d.bitc.rct_ddrio_odt = data;
    *(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DLL_OCD_BITS_rct_ddrio_odt(void)
{
    GH_DEBUG_TEST_DLL_OCD_BITS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DLL_OCD_BITS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ddrio_odt;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_CORE_OBSV (read/write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_CORE_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_OBSV_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_CORE_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_CORE_OBSV_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_IDSP_OBSV (read/write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_IDSP_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_OBSV_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_IDSP_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_IDSP_OBSV_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_DDR_OBSV (read/write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_DDR_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_DDR_OBSV_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_DDR_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_DDR_OBSV_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_SENSOR_OBSV (read/write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_SENSOR_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_OBSV_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_SENSOR_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_SENSOR_OBSV_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_AUDIO_OBSV (read/write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_AUDIO_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_OBSV_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_AUDIO_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_AUDIO_OBSV_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_VIDEO_OBSV (read/write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_OBSV_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_VIDEO_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO_OBSV_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_PLL_VIDEO2_OBSV (read/write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_PLL_VIDEO2_OBSV(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_OBSV_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_PLL_VIDEO2_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_PLL_VIDEO2_OBSV_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_ADC16_CTRL_ADDR (read/write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_ADC16_CTRL_ADDR(U32 data)
{
    GH_DEBUG_TEST_ADC16_CTRL_ADDR_REAL_S real;
    GH_DEBUG_TEST_ADC16_CTRL_ADDR_S dummy;
    dummy.all = data ;
    real.bitc.adc_power_down = dummy.bitc.adc_power_down;
    real.bitc.adc_clock_select = dummy.bitc.adc_clock_select;
    *(volatile U32 *)REG_DEBUG_TEST_ADC16_CTRL_ADDR_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_ADC16_CTRL_ADDR(void)
{
    GH_DEBUG_TEST_ADC16_CTRL_ADDR_REAL_S real;
    GH_DEBUG_TEST_ADC16_CTRL_ADDR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_ADC16_CTRL_ADDR_REAL);

    dummy.bitc.adc_power_down = real.bitc.adc_power_down;
    dummy.bitc.adc_clock_select = real.bitc.adc_clock_select;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_ADC16_CTRL_ADDR_adc_power_down(U8 data)
{
    GH_DEBUG_TEST_ADC16_CTRL_ADDR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_ADC16_CTRL_ADDR_REAL;
    d.bitc.adc_power_down = data;
    *(volatile U32 *)REG_DEBUG_TEST_ADC16_CTRL_ADDR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_ADC16_CTRL_ADDR_adc_power_down(void)
{
    GH_DEBUG_TEST_ADC16_CTRL_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_ADC16_CTRL_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adc_power_down;
}
GH_INLINE void GH_DEBUG_TEST_set_ADC16_CTRL_ADDR_adc_clock_select(U8 data)
{
    GH_DEBUG_TEST_ADC16_CTRL_ADDR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_ADC16_CTRL_ADDR_REAL;
    d.bitc.adc_clock_select = data;
    *(volatile U32 *)REG_DEBUG_TEST_ADC16_CTRL_ADDR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_ADC16_CTRL_ADDR_adc_clock_select(void)
{
    GH_DEBUG_TEST_ADC16_CTRL_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_ADC16_CTRL_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adc_clock_select;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CLK_REF_SSI_ADDR (read/write)                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_CLK_REF_SSI_ADDR(U32 data)
{
    GH_DEBUG_TEST_CLK_REF_SSI_ADDR_REAL_S real;
    GH_DEBUG_TEST_CLK_REF_SSI_ADDR_S dummy;
    dummy.all = data ;
    real.bitc.clk = dummy.bitc.clk;
    *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_SSI_ADDR_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_CLK_REF_SSI_ADDR(void)
{
    GH_DEBUG_TEST_CLK_REF_SSI_ADDR_REAL_S real;
    GH_DEBUG_TEST_CLK_REF_SSI_ADDR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_CLK_REF_SSI_ADDR_REAL);

    dummy.bitc.clk = real.bitc.clk;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_CLK_REF_SSI_ADDR_clk(U8 data)
{
    GH_DEBUG_TEST_CLK_REF_SSI_ADDR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_SSI_ADDR_REAL;
    d.bitc.clk = data;
    *(volatile U32 *)REG_DEBUG_TEST_CLK_REF_SSI_ADDR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_CLK_REF_SSI_ADDR_clk(void)
{
    GH_DEBUG_TEST_CLK_REF_SSI_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLK_REF_SSI_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clk;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_DVEN (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_CG_DVEN(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CG_DVEN_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_DVEN(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_DVEN_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_MS (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_SCALER_MS(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_MS_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_MS(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_MS_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_MS_DELAY_CTRL (read/write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_MS_DELAY_CTRL(U32 data)
{
    GH_DEBUG_TEST_MS_DELAY_CTRL_REAL_S real;
    GH_DEBUG_TEST_MS_DELAY_CTRL_S dummy;
    dummy.all = data ;
    real.bitc.delay_sclk = dummy.bitc.delay_sclk;
    real.bitc.input_delay = dummy.bitc.input_delay;
    real.bitc.output_delay = dummy.bitc.output_delay;
    real.bitc.timing = dummy.bitc.timing;
    *(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_MS_DELAY_CTRL(void)
{
    GH_DEBUG_TEST_MS_DELAY_CTRL_REAL_S real;
    GH_DEBUG_TEST_MS_DELAY_CTRL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL_REAL);

    dummy.bitc.delay_sclk = real.bitc.delay_sclk;
    dummy.bitc.input_delay = real.bitc.input_delay;
    dummy.bitc.output_delay = real.bitc.output_delay;
    dummy.bitc.timing = real.bitc.timing;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_MS_DELAY_CTRL_delay_sclk(U8 data)
{
    GH_DEBUG_TEST_MS_DELAY_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL_REAL;
    d.bitc.delay_sclk = data;
    *(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_MS_DELAY_CTRL_delay_sclk(void)
{
    GH_DEBUG_TEST_MS_DELAY_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.delay_sclk;
}
GH_INLINE void GH_DEBUG_TEST_set_MS_DELAY_CTRL_input_delay(U8 data)
{
    GH_DEBUG_TEST_MS_DELAY_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL_REAL;
    d.bitc.input_delay = data;
    *(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_MS_DELAY_CTRL_input_delay(void)
{
    GH_DEBUG_TEST_MS_DELAY_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.input_delay;
}
GH_INLINE void GH_DEBUG_TEST_set_MS_DELAY_CTRL_output_delay(U8 data)
{
    GH_DEBUG_TEST_MS_DELAY_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL_REAL;
    d.bitc.output_delay = data;
    *(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_MS_DELAY_CTRL_output_delay(void)
{
    GH_DEBUG_TEST_MS_DELAY_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.output_delay;
}
GH_INLINE void GH_DEBUG_TEST_set_MS_DELAY_CTRL_timing(U8 data)
{
    GH_DEBUG_TEST_MS_DELAY_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL_REAL;
    d.bitc.timing = data;
    *(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_MS_DELAY_CTRL_timing(void)
{
    GH_DEBUG_TEST_MS_DELAY_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_MS_DELAY_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.timing;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_USE_COMMON_VO_CLOCK (read/write)                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_USE_COMMON_VO_CLOCK(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_USE_COMMON_VO_CLOCK_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_USE_COMMON_VO_CLOCK(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_USE_COMMON_VO_CLOCK_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CLOCK_OBSV_ADDR (read/write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_CLOCK_OBSV_ADDR(U32 data)
{
    GH_DEBUG_TEST_CLOCK_OBSV_ADDR_REAL_S real;
    GH_DEBUG_TEST_CLOCK_OBSV_ADDR_S dummy;
    dummy.all = data ;
    real.bitc.pll = dummy.bitc.pll;
    real.bitc.observation = dummy.bitc.observation;
    *(volatile U32 *)REG_DEBUG_TEST_CLOCK_OBSV_ADDR_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_CLOCK_OBSV_ADDR(void)
{
    GH_DEBUG_TEST_CLOCK_OBSV_ADDR_REAL_S real;
    GH_DEBUG_TEST_CLOCK_OBSV_ADDR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_CLOCK_OBSV_ADDR_REAL);

    dummy.bitc.pll = real.bitc.pll;
    dummy.bitc.observation = real.bitc.observation;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_CLOCK_OBSV_ADDR_pll(U8 data)
{
    GH_DEBUG_TEST_CLOCK_OBSV_ADDR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CLOCK_OBSV_ADDR_REAL;
    d.bitc.pll = data;
    *(volatile U32 *)REG_DEBUG_TEST_CLOCK_OBSV_ADDR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_CLOCK_OBSV_ADDR_pll(void)
{
    GH_DEBUG_TEST_CLOCK_OBSV_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLOCK_OBSV_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pll;
}
GH_INLINE void GH_DEBUG_TEST_set_CLOCK_OBSV_ADDR_observation(U8 data)
{
    GH_DEBUG_TEST_CLOCK_OBSV_ADDR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CLOCK_OBSV_ADDR_REAL;
    d.bitc.observation = data;
    *(volatile U32 *)REG_DEBUG_TEST_CLOCK_OBSV_ADDR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_CLOCK_OBSV_ADDR_observation(void)
{
    GH_DEBUG_TEST_CLOCK_OBSV_ADDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CLOCK_OBSV_ADDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.observation;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_DISABLE_EXT_BYPASS (read/write)                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_DISABLE_EXT_BYPASS(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_DISABLE_EXT_BYPASS_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_DISABLE_EXT_BYPASS(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DISABLE_EXT_BYPASS_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_ARM_SYNC_LOCK (read/write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_ARM_SYNC_LOCK(U32 data)
{
    GH_DEBUG_TEST_ARM_SYNC_LOCK_REAL_S real;
    GH_DEBUG_TEST_ARM_SYNC_LOCK_S dummy;
    dummy.all = data ;
    real.bitc.mode = dummy.bitc.mode;
    real.bitc.reset = dummy.bitc.reset;
    *(volatile U32 *)REG_DEBUG_TEST_ARM_SYNC_LOCK_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_ARM_SYNC_LOCK(void)
{
    GH_DEBUG_TEST_ARM_SYNC_LOCK_REAL_S real;
    GH_DEBUG_TEST_ARM_SYNC_LOCK_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_ARM_SYNC_LOCK_REAL);

    dummy.bitc.mode = real.bitc.mode;
    dummy.bitc.reset = real.bitc.reset;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_ARM_SYNC_LOCK_mode(U8 data)
{
    GH_DEBUG_TEST_ARM_SYNC_LOCK_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_ARM_SYNC_LOCK_REAL;
    d.bitc.mode = data;
    *(volatile U32 *)REG_DEBUG_TEST_ARM_SYNC_LOCK_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_ARM_SYNC_LOCK_mode(void)
{
    GH_DEBUG_TEST_ARM_SYNC_LOCK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_ARM_SYNC_LOCK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mode;
}
GH_INLINE void GH_DEBUG_TEST_set_ARM_SYNC_LOCK_reset(U8 data)
{
    GH_DEBUG_TEST_ARM_SYNC_LOCK_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_ARM_SYNC_LOCK_REAL;
    d.bitc.reset = data;
    *(volatile U32 *)REG_DEBUG_TEST_ARM_SYNC_LOCK_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_ARM_SYNC_LOCK_reset(void)
{
    GH_DEBUG_TEST_ARM_SYNC_LOCK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_ARM_SYNC_LOCK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reset;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_ARM_SYNC (read/write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_SCALER_ARM_SYNC(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_ARM_SYNC_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_ARM_SYNC(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_ARM_SYNC_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_ARM_ASYNC (read/write)                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_SCALER_ARM_ASYNC(U32 data)
{
    GH_DEBUG_TEST_SCALER_ARM_ASYNC_REAL_S real;
    GH_DEBUG_TEST_SCALER_ARM_ASYNC_S dummy;
    dummy.all = data ;
    real.bitc.div = dummy.bitc.div;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_ARM_ASYNC_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_ARM_ASYNC(void)
{
    GH_DEBUG_TEST_SCALER_ARM_ASYNC_REAL_S real;
    GH_DEBUG_TEST_SCALER_ARM_ASYNC_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_ARM_ASYNC_REAL);

    dummy.bitc.div = real.bitc.div;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_ARM_ASYNC_Div(U8 data)
{
    GH_DEBUG_TEST_SCALER_ARM_ASYNC_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_ARM_ASYNC_REAL;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_ARM_ASYNC_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SCALER_ARM_ASYNC_Div(void)
{
    GH_DEBUG_TEST_SCALER_ARM_ASYNC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_ARM_ASYNC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.div;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_SCALER_IDSP_POST (read/write)                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_SCALER_IDSP_POST(U32 data)
{
    GH_DEBUG_TEST_SCALER_IDSP_POST_REAL_S real;
    GH_DEBUG_TEST_SCALER_IDSP_POST_S dummy;
    dummy.all = data ;
    real.bitc.div = dummy.bitc.div;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_IDSP_POST_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_SCALER_IDSP_POST(void)
{
    GH_DEBUG_TEST_SCALER_IDSP_POST_REAL_S real;
    GH_DEBUG_TEST_SCALER_IDSP_POST_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_IDSP_POST_REAL);

    dummy.bitc.div = real.bitc.div;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_SCALER_IDSP_POST_Div(U8 data)
{
    GH_DEBUG_TEST_SCALER_IDSP_POST_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_SCALER_IDSP_POST_REAL;
    d.bitc.div = data;
    *(volatile U32 *)REG_DEBUG_TEST_SCALER_IDSP_POST_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_SCALER_IDSP_POST_Div(void)
{
    GH_DEBUG_TEST_SCALER_IDSP_POST_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_SCALER_IDSP_POST_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.div;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_OCTRL_GPIO (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_OCTRL_GPIO(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_OCTRL_GPIO_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_OCTRL_GPIO(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_OCTRL_GPIO_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_IOCTRL_MISC1 (read/write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_IOCTRL_MISC1(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_IOCTRL_MISC1_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_IOCTRL_MISC1(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_IOCTRL_MISC1_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_OCTRL_MISC2 (read/write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_OCTRL_MISC2(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_OCTRL_MISC2_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_OCTRL_MISC2(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_OCTRL_MISC2_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_IOCTRL_SD (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_IOCTRL_SD(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_IOCTRL_SD_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_IOCTRL_SD(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_IOCTRL_SD_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_IOCTRL_SMIO (read/write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_IOCTRL_SMIO(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_IOCTRL_SMIO_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_IOCTRL_SMIO(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_IOCTRL_SMIO_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_IOCTRL_VD0 (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_IOCTRL_VD0(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_IOCTRL_VD0_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_IOCTRL_VD0(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_IOCTRL_VD0_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_IOCTRL_VD1 (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_IOCTRL_VD1(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_IOCTRL_VD1_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_IOCTRL_VD1(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_IOCTRL_VD1_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_IOCTRL_SENSOR (read/write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_IOCTRL_SENSOR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_IOCTRL_SENSOR_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_IOCTRL_SENSOR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_IOCTRL_SENSOR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_AHB_MISC_EN (read/write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_AHB_MISC_EN(U32 data)
{
    GH_DEBUG_TEST_AHB_MISC_EN_REAL_S real;
    GH_DEBUG_TEST_AHB_MISC_EN_S dummy;
    dummy.all = data ;
    real.bitc.rct_ahb = dummy.bitc.rct_ahb;
    *(volatile U32 *)REG_DEBUG_TEST_AHB_MISC_EN_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_AHB_MISC_EN(void)
{
    GH_DEBUG_TEST_AHB_MISC_EN_REAL_S real;
    GH_DEBUG_TEST_AHB_MISC_EN_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_AHB_MISC_EN_REAL);

    dummy.bitc.rct_ahb = real.bitc.rct_ahb;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_AHB_MISC_EN_rct_ahb(U8 data)
{
    GH_DEBUG_TEST_AHB_MISC_EN_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_AHB_MISC_EN_REAL;
    d.bitc.rct_ahb = data;
    *(volatile U32 *)REG_DEBUG_TEST_AHB_MISC_EN_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_AHB_MISC_EN_rct_ahb(void)
{
    GH_DEBUG_TEST_AHB_MISC_EN_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_AHB_MISC_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rct_ahb;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CG_DDR_INIT (read/write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_CG_DDR_INIT(U32 data)
{
    GH_DEBUG_TEST_CG_DDR_INIT_REAL_S real;
    GH_DEBUG_TEST_CG_DDR_INIT_S dummy;
    dummy.all = data ;
    real.bitc.divide = dummy.bitc.divide;
    real.bitc.en = dummy.bitc.en;
    *(volatile U32 *)REG_DEBUG_TEST_CG_DDR_INIT_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_CG_DDR_INIT(void)
{
    GH_DEBUG_TEST_CG_DDR_INIT_REAL_S real;
    GH_DEBUG_TEST_CG_DDR_INIT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_CG_DDR_INIT_REAL);

    dummy.bitc.divide = real.bitc.divide;
    dummy.bitc.en = real.bitc.en;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_CG_DDR_INIT_Divide(U8 data)
{
    GH_DEBUG_TEST_CG_DDR_INIT_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CG_DDR_INIT_REAL;
    d.bitc.divide = data;
    *(volatile U32 *)REG_DEBUG_TEST_CG_DDR_INIT_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_CG_DDR_INIT_Divide(void)
{
    GH_DEBUG_TEST_CG_DDR_INIT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_DDR_INIT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.divide;
}
GH_INLINE void GH_DEBUG_TEST_set_CG_DDR_INIT_en(U8 data)
{
    GH_DEBUG_TEST_CG_DDR_INIT_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_CG_DDR_INIT_REAL;
    d.bitc.en = data;
    *(volatile U32 *)REG_DEBUG_TEST_CG_DDR_INIT_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_CG_DDR_INIT_en(void)
{
    GH_DEBUG_TEST_CG_DDR_INIT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CG_DDR_INIT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_DDR_DIV_RST (read/write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_DDR_DIV_RST(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_DDR_DIV_RST_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_DDR_DIV_RST(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DDR_DIV_RST_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_DDRC_IDSP_RESET (read/write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_DDRC_IDSP_RESET(U32 data)
{
    GH_DEBUG_TEST_DDRC_IDSP_RESET_REAL_S real;
    GH_DEBUG_TEST_DDRC_IDSP_RESET_S dummy;
    dummy.all = data ;
    real.bitc.ddrc = dummy.bitc.ddrc;
    real.bitc.idsp = dummy.bitc.idsp;
    *(volatile U32 *)REG_DEBUG_TEST_DDRC_IDSP_RESET_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_TEST_get_DDRC_IDSP_RESET(void)
{
    GH_DEBUG_TEST_DDRC_IDSP_RESET_REAL_S real;
    GH_DEBUG_TEST_DDRC_IDSP_RESET_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TEST_DDRC_IDSP_RESET_REAL);

    dummy.bitc.ddrc = real.bitc.ddrc;
    dummy.bitc.idsp = real.bitc.idsp;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_TEST_set_DDRC_IDSP_RESET_ddrc(U8 data)
{
    GH_DEBUG_TEST_DDRC_IDSP_RESET_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DDRC_IDSP_RESET_REAL;
    d.bitc.ddrc = data;
    *(volatile U32 *)REG_DEBUG_TEST_DDRC_IDSP_RESET_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DDRC_IDSP_RESET_ddrc(void)
{
    GH_DEBUG_TEST_DDRC_IDSP_RESET_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DDRC_IDSP_RESET_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ddrc;
}
GH_INLINE void GH_DEBUG_TEST_set_DDRC_IDSP_RESET_idsp(U8 data)
{
    GH_DEBUG_TEST_DDRC_IDSP_RESET_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_TEST_DDRC_IDSP_RESET_REAL;
    d.bitc.idsp = data;
    *(volatile U32 *)REG_DEBUG_TEST_DDRC_IDSP_RESET_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_TEST_get_DDRC_IDSP_RESET_idsp(void)
{
    GH_DEBUG_TEST_DDRC_IDSP_RESET_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_DDRC_IDSP_RESET_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.idsp;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TEST_CKEN_IDSP (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_set_CKEN_IDSP(U32 data)
{
    *(volatile U32 *)REG_DEBUG_TEST_CKEN_IDSP_REAL = data;
}
GH_INLINE U32  GH_DEBUG_TEST_get_CKEN_IDSP(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TEST_CKEN_IDSP_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TEST_init(void)
{
    GH_DEBUG_TEST_set_PLL_CORE_CTRL((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_CORE_FRAC((U32)0x00000000);
    GH_DEBUG_TEST_set_HDMI_CTRL((U32)0x00000002);
    GH_DEBUG_TEST_set_SCALER_SD48((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_VIDEO_CTRL((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_VIDEO_FRAC((U32)0x00000000);
    GH_DEBUG_TEST_set_SCALER_VIDEO((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_SENSOR_CTRL((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_SENSOR_FRAC((U32)0x00000000);
    GH_DEBUG_TEST_set_SCALER_SENSOR_POST((U32)0x00000000);
    GH_DEBUG_TEST_set_SYS_CONFIG((U32)0x00000000);
    GH_DEBUG_TEST_set_CG_UART((U32)0x00000000);
    GH_DEBUG_TEST_set_CG_SSI((U32)0x00000000);
    GH_DEBUG_TEST_set_CG_MOTOR((U32)0x00000000);
    GH_DEBUG_TEST_set_CG_IR((U32)0x00000000);
    GH_DEBUG_TEST_set_CG_HOST((U32)0x00000000);
    GH_DEBUG_TEST_set_SCALER_SENSOR_PRE((U32)0x00000000);
    GH_DEBUG_TEST_set_ANA_PWR((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_AUDIO_CTRL((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_AUDIO_FRAC((U32)0x00000000);
    GH_DEBUG_TEST_set_SCALER_AUDIO((U32)0x00000000);
    GH_DEBUG_TEST_set_SCALER_AUDIO_PRE((U32)0x00000000);
    GH_DEBUG_TEST_set_SOFT_OR_DLLRESET((U32)0x00000000);
    GH_DEBUG_TEST_set_FIO_RESET((U32)0x00000000);
    GH_DEBUG_TEST_set_SCALER_USB((U32)0x00000000);
    GH_DEBUG_TEST_set_CLK_DEBOUNCE((U32)0x00000000);
    GH_DEBUG_TEST_set_CG_PWM((U32)0x00000000);
    GH_DEBUG_TEST_set_USBP_CTRL((U32)0x00000000);
    GH_DEBUG_TEST_set_CKEN_VDSP((U32)0x00000000);
    GH_DEBUG_TEST_set_DLL0((U32)0x00000000);
    GH_DEBUG_TEST_set_DLL1((U32)0x00000000);
    GH_DEBUG_TEST_set_SCALER_ADC((U32)0x00000000);
    GH_DEBUG_TEST_set_SCALER_VIDEO_POST((U32)0x00000000);
    GH_DEBUG_TEST_set_CLK_REF_AU_EXTERNAL((U32)0x00000000);
    GH_DEBUG_TEST_set_USE_EXTERNAL_CLK_AU((U32)0x00000000);
    GH_DEBUG_TEST_set_CLK_REF_VIDEO_EXTERNAL((U32)0x00000000);
    GH_DEBUG_TEST_set_USE_EXTERNAL_VD_CLK((U32)0x00000000);
    GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_AU((U32)0x00000000);
    GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_VO((U32)0x00000000);
    GH_DEBUG_TEST_set_CLK_SI_INPUT_MODE((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_VIDEO2_FRAC((U32)0x00000000);
    GH_DEBUG_TEST_set_SCALER_VIDEO2((U32)0x00000000);
    GH_DEBUG_TEST_set_SCALER_VIDEO2_POST((U32)0x00000000);
    GH_DEBUG_TEST_set_USE_CLK_SI_4_CLK_VO2((U32)0x00000000);
    GH_DEBUG_TEST_set_USE_EXTERNAL_VD2_CLK((U32)0x00000000);
    GH_DEBUG_TEST_set_CLK_REF_VIDEO2_EXTERNAL((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_DDR_CTRL((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_DDR_FRAC((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_IDSP_CTRL((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_IDSP_FRAC((U32)0x00000000);
    GH_DEBUG_TEST_set_CG_SSI2((U32)0x00000000);
    GH_DEBUG_TEST_set_LVDS_LVCMOS((U32)0x00000000);
    GH_DEBUG_TEST_set_LVDS_ASYNC((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_CORE_CTRL2((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_CORE_CTRL3((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_IDSP_CTRL2((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_IDSP_CTRL3((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_IDSP_CTRL22((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_IDSP_CTRL32((U32)0x00000000);
    GH_DEBUG_TEST_set_SCALER_CORE_POST((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_SENSOR_CTRL2((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_SENSOR_CTRL3((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_AUDIO_CTRL2((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_AUDIO_CTRL3((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_VIDEO_CTRL2((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_VIDEO_CTRL3((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_VIDEO2_CTRL2((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_USB_CTRL2((U32)0x00000000);
    GH_DEBUG_TEST_set_CG_DDR_CALIB((U32)0x00000000);
    GH_DEBUG_TEST_set_DLL_CTRL_SEL((U32)0x00000000);
    GH_DEBUG_TEST_set_DLL_OCD_BITS((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_CORE_OBSV((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_IDSP_OBSV((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_DDR_OBSV((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_SENSOR_OBSV((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_AUDIO_OBSV((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_VIDEO_OBSV((U32)0x00000000);
    GH_DEBUG_TEST_set_PLL_VIDEO2_OBSV((U32)0x00000000);
    GH_DEBUG_TEST_set_ADC16_CTRL_ADDR((U32)0x00000000);
    GH_DEBUG_TEST_set_CLK_REF_SSI_ADDR((U32)0x00000000);
    GH_DEBUG_TEST_set_CG_DVEN((U32)0x00000000);
    GH_DEBUG_TEST_set_SCALER_MS((U32)0x00000000);
    GH_DEBUG_TEST_set_MS_DELAY_CTRL((U32)0x00000000);
    GH_DEBUG_TEST_set_USE_COMMON_VO_CLOCK((U32)0x00000000);
    GH_DEBUG_TEST_set_CLOCK_OBSV_ADDR((U32)0x00000000);
    GH_DEBUG_TEST_set_DISABLE_EXT_BYPASS((U32)0x00000000);
    GH_DEBUG_TEST_set_ARM_SYNC_LOCK((U32)0x00000000);
    GH_DEBUG_TEST_set_SCALER_ARM_SYNC((U32)0x00000000);
    GH_DEBUG_TEST_set_SCALER_ARM_ASYNC((U32)0x00000000);
    GH_DEBUG_TEST_set_SCALER_IDSP_POST((U32)0x00000000);
    GH_DEBUG_TEST_set_OCTRL_GPIO((U32)0x00000000);
    GH_DEBUG_TEST_set_IOCTRL_MISC1((U32)0x00000000);
    GH_DEBUG_TEST_set_OCTRL_MISC2((U32)0x00000000);
    GH_DEBUG_TEST_set_IOCTRL_SD((U32)0x00000000);
    GH_DEBUG_TEST_set_IOCTRL_SMIO((U32)0x00000000);
    GH_DEBUG_TEST_set_IOCTRL_VD0((U32)0x00000000);
    GH_DEBUG_TEST_set_IOCTRL_VD1((U32)0x00000000);
    GH_DEBUG_TEST_set_IOCTRL_SENSOR((U32)0x00000000);
    GH_DEBUG_TEST_set_AHB_MISC_EN((U32)0x00000000);
    GH_DEBUG_TEST_set_CG_DDR_INIT((U32)0x00000000);
    GH_DEBUG_TEST_set_DDR_DIV_RST((U32)0x00000000);
    GH_DEBUG_TEST_set_DDRC_IDSP_RESET((U32)0x00000000);
    GH_DEBUG_TEST_set_CKEN_IDSP((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

