/*!
*******************************************************************************
**
** \file      gh_debug_rct.h
**
** \brief     PLL Registers.
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
#ifndef _GH_DEBUG_RCT_H
#define _GH_DEBUG_RCT_H

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
#define REG_PLL_VIDEO_CTRL                                  FIO_ADDRESS(PLL,0xA0170000) /* read/write */
#define REG_PLL_SCALER_VIDEO_PRE                            FIO_ADDRESS(PLL,0xA0170004) /* read/write */
#define REG_PLL_VIDEO_FRAC                                  FIO_ADDRESS(PLL,0xA017000C) /* read/write */
#define REG_PLL_CORE_CTRL                                   FIO_ADDRESS(PLL,0xA0170014) /* read/write */
#define REG_PLL_SCALER_SD48                                 FIO_ADDRESS(PLL,0xA0170018) /* read/write */
#define REG_PLL_CORE_FRAC                                   FIO_ADDRESS(PLL,0xA017001C) /* read/write */
#define REG_PLL_AUDIO_CTRL                                  FIO_ADDRESS(PLL,0xA0170024) /* read/write */
#define REG_PLL_SCALER_UART                                 FIO_ADDRESS(PLL,0xA0170028) /* read/write */
#define REG_PLL_SCALER_SENSOR_PRE                           FIO_ADDRESS(PLL,0xA017002C) /* read/write */
#define REG_PLL_SCALER_SSI                                  FIO_ADDRESS(PLL,0xA0170030) /* read/write */
#define REG_PLL_SCALER_SENSOR_POST                          FIO_ADDRESS(PLL,0xA0170038) /* read/write */
#define REG_PLL_SENSOR_FRAC                                 FIO_ADDRESS(PLL,0xA017004C) /* read/write */
#define REG_PLL_USB_GRST                                    FIO_ADDRESS(PLL,0xA0170050) /* read/write */
#define REG_PLL_SENSOR_CTRL                                 FIO_ADDRESS(PLL,0xA0170054) /* read/write */
#define REG_PLL_WDT_RST_L                                   FIO_ADDRESS(PLL,0xA0170058) /* read */
#define REG_PLL_SCALER_PWM                                  FIO_ADDRESS(PLL,0xA0170060) /* read/write */
#define REG_PLL_AUDIO_FRAC                                  FIO_ADDRESS(PLL,0xA0170078) /* read/write */
#define REG_PLL_SCALER_AUDIO_PRE                            FIO_ADDRESS(PLL,0xA0170080) /* read/write */
#define REG_PLL_SCALER_AUDIO_POST                           FIO_ADDRESS(PLL,0xA0170084) /* read/write */
#define REG_PLL_USB_SRST                                    FIO_ADDRESS(PLL,0xA0170088) /* read/write */
#define REG_PLL_IDSP_CTRL                                   FIO_ADDRESS(PLL,0xA017008C) /* read/write */
#define REG_PLL_IDSP_FRAC                                   FIO_ADDRESS(PLL,0xA017009C) /* read/write */
#define REG_PLL_SCALER_SSI2                                 FIO_ADDRESS(PLL,0xA01700A0) /* read/write */
#define REG_PLL_CLK_OUT                                     FIO_ADDRESS(PLL,0xA01700C0) /* read/write */
#define REG_PLL_CLK_VOUT                                    FIO_ADDRESS(PLL,0xA01700D4) /* read/write */
#define REG_PLL_SCALER_ADC                                  FIO_ADDRESS(PLL,0xA01700E8) /* read/write */
#define REG_PLL_SCALER_VIDEO_POST                           FIO_ADDRESS(PLL,0xA01700EC) /* read/write */
#define REG_PLL_IDSP_CTRL2                                  FIO_ADDRESS(PLL,0xA0170100) /* read/write */
#define REG_PLL_CORE_CTRL2                                  FIO_ADDRESS(PLL,0xA0170108) /* read/write */
#define REG_PLL_SCALER_CORE_POST                            FIO_ADDRESS(PLL,0xA0170118) /* read/write */
#define REG_PLL_VIDEO_CTRL2                                 FIO_ADDRESS(PLL,0xA017011C) /* read/write */
#define REG_PLL_SENSOR_CTRL2                                FIO_ADDRESS(PLL,0xA0170124) /* read/write */
#define REG_PLL_AUDIO_CTRL2                                 FIO_ADDRESS(PLL,0xA0170130) /* read/write */
#define REG_PLL_IOCTRL_JTAG                                 FIO_ADDRESS(PLL,0xA0170148) /* read/write */
#define REG_PLL_IOCTRL_SFLASH                               FIO_ADDRESS(PLL,0xA0170198) /* read/write */
#define REG_PLL_IOCTRL_SENSOR                               FIO_ADDRESS(PLL,0xA017019C) /* read/write */
#define REG_PLL_CLOCK_VO                                    FIO_ADDRESS(PLL,0xA01701D4) /* read/write */
#define REG_PLL_CLOCK_OBSV                                  FIO_ADDRESS(PLL,0xA01701E0) /* read/write */
#define REG_PLL_SCALER_IDSP_POST                            FIO_ADDRESS(PLL,0xA01701F4) /* read/write */
#define REG_PLL_GENERAL_CONFIG                              FIO_ADDRESS(PLL,0xA0170208) /* read/write */
#define REG_PLL_CLK_REF_SSI                                 FIO_ADDRESS(PLL,0xA0170214) /* read/write */
#define REG_PLL_DDRC_IDSP_RESET                             FIO_ADDRESS(PLL,0xA0170228) /* read/write */
#define REG_PLL_IOCTRL_GPIO                                 FIO_ADDRESS(PLL,0xA0170230) /* read/write */
#define REG_PLL_IOCTRL_GPIO56                               FIO_ADDRESS(PLL,0xA0170268) /* read/write */
#define REG_PLL_IOCTRL_XCLK                                 FIO_ADDRESS(PLL,0xA0170270) /* read/write */
#define REG_PLL_SCALER_DDR_CALIB                            FIO_ADDRESS(PLL,0xA0170274) /* read/write */
#define REG_PLL_LOCK                                        FIO_ADDRESS(PLL,0xA0170278) /* read */
#define REG_PLL_SCALER_DEBOUNCE                             FIO_ADDRESS(PLL,0xA017027C) /* read/write */
#define REG_PLL_CKEN_VDSP                                   FIO_ADDRESS(PLL,0xA017008C) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* PLL_VIDEO_CTRL */
    U32 all;
    struct {
        U32 fbdiv                       : 12;
        U32 pstdiv1                     : 3;
        U32                             : 1;
        U32 pstdiv2                     : 3;
        U32                             : 1;
        U32 refdiv                      : 6;
        U32                             : 6;
    } bitc;
} GH_PLL_VIDEO_CTRL_S;

typedef union { /* PLL_SCALER_VIDEO_PRE */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_PLL_SCALER_VIDEO_PRE_S;

typedef union { /* PLL_VIDEO_FRAC */
    U32 all;
    struct {
        U32 div                         : 24;
        U32                             : 8;
    } bitc;
} GH_PLL_VIDEO_FRAC_S;

typedef union { /* PLL_CORE_CTRL */
    U32 all;
    struct {
        U32 fbdiv                       : 12;
        U32 pstdiv1                     : 3;
        U32                             : 1;
        U32 pstdiv2                     : 3;
        U32                             : 1;
        U32 refdiv                      : 6;
        U32                             : 6;
    } bitc;
} GH_PLL_CORE_CTRL_S;

typedef union { /* PLL_SCALER_SD48 */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_PLL_SCALER_SD48_S;

typedef union { /* PLL_CORE_FRAC */
    U32 all;
    struct {
        U32 div                         : 24;
        U32                             : 8;
    } bitc;
} GH_PLL_CORE_FRAC_S;

typedef union { /* PLL_AUDIO_CTRL */
    U32 all;
    struct {
        U32 fbdiv                       : 12;
        U32 pstdiv1                     : 3;
        U32                             : 1;
        U32 pstdiv2                     : 3;
        U32                             : 1;
        U32 refdiv                      : 6;
        U32                             : 6;
    } bitc;
} GH_PLL_AUDIO_CTRL_S;

typedef union { /* PLL_SCALER_UART */
    U32 all;
    struct {
        U32 div                         : 24;
        U32                             : 8;
    } bitc;
} GH_PLL_SCALER_UART_S;

typedef union { /* PLL_SCALER_SENSOR_PRE */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_PLL_SCALER_SENSOR_PRE_S;

typedef union { /* PLL_SCALER_SSI */
    U32 all;
    struct {
        U32 div                         : 24;
        U32                             : 8;
    } bitc;
} GH_PLL_SCALER_SSI_S;

typedef union { /* PLL_SCALER_SENSOR_POST */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_PLL_SCALER_SENSOR_POST_S;

typedef union { /* PLL_SENSOR_FRAC */
    U32 all;
    struct {
        U32 div                         : 24;
        U32                             : 8;
    } bitc;
} GH_PLL_SENSOR_FRAC_S;

typedef union { /* PLL_USB_GRST */
    U32 all;
    struct {
        U32                             : 1;
        U32 en                          : 1;
        U32                             : 30;
    } bitc;
} GH_PLL_USB_GRST_S;

typedef union { /* PLL_SENSOR_CTRL */
    U32 all;
    struct {
        U32 fbdiv                       : 12;
        U32 pstdiv1                     : 3;
        U32                             : 1;
        U32 pstdiv2                     : 3;
        U32                             : 1;
        U32 refdiv                      : 6;
        U32                             : 6;
    } bitc;
} GH_PLL_SENSOR_CTRL_S;

typedef union { /* PLL_WDT_RST_L */
    U32 all;
    struct {
        U32 reset                       : 1;
        U32                             : 31;
    } bitc;
} GH_PLL_WDT_RST_L_S;

typedef union { /* PLL_SCALER_PWM */
    U32 all;
    struct {
        U32 div                         : 24;
        U32                             : 8;
    } bitc;
} GH_PLL_SCALER_PWM_S;

typedef union { /* PLL_AUDIO_FRAC */
    U32 all;
    struct {
        U32 div                         : 24;
        U32                             : 8;
    } bitc;
} GH_PLL_AUDIO_FRAC_S;

typedef union { /* PLL_SCALER_AUDIO_PRE */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_PLL_SCALER_AUDIO_PRE_S;

typedef union { /* PLL_SCALER_AUDIO_POST */
    U32 all;
    struct {
        U32 div                         : 16;
        U32                             : 16;
    } bitc;
} GH_PLL_SCALER_AUDIO_POST_S;

typedef union { /* PLL_USB_SRST */
    U32 all;
    struct {
        U32                             : 29;
        U32 en                          : 1;
        U32                             : 2;
    } bitc;
} GH_PLL_USB_SRST_S;

typedef union { /* PLL_IDSP_CTRL */
    U32 all;
    struct {
        U32 fbdiv                       : 12;
        U32 pstdiv1                     : 3;
        U32                             : 1;
        U32 pstdiv2                     : 3;
        U32                             : 1;
        U32 refdiv                      : 6;
        U32                             : 6;
    } bitc;
} GH_PLL_IDSP_CTRL_S;

typedef union { /* PLL_IDSP_FRAC */
    U32 all;
    struct {
        U32 div                         : 24;
        U32                             : 8;
    } bitc;
} GH_PLL_IDSP_FRAC_S;

typedef union { /* PLL_SCALER_SSI2 */
    U32 all;
    struct {
        U32 div                         : 24;
        U32                             : 8;
    } bitc;
} GH_PLL_SCALER_SSI2_S;

typedef union { /* PLL_CLK_OUT */
    U32 all;
    struct {
        U32 div1                        : 16;
        U32 div2                        : 16;
    } bitc;
} GH_PLL_CLK_OUT_S;

typedef union { /* PLL_CLK_VOUT */
    U32 all;
    struct {
        U32 sel                         : 1;
        U32                             : 31;
    } bitc;
} GH_PLL_CLK_VOUT_S;

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

typedef union { /* PLL_IDSP_CTRL2 */
    U32 all;
    struct {
        U32 foutvcopd                   : 1;
        U32 fout4phasepd                : 1;
        U32 foutpostdivpd               : 1;
        U32 dsmpd                       : 1;
        U32 dacpd                       : 1;
        U32 pwrdn                       : 1;
        U32 bypass                      : 1;
        U32                             : 13;
        U32 lock_force                  : 1;
        U32                             : 11;
    } bitc;
} GH_PLL_IDSP_CTRL2_S;

typedef union { /* PLL_CORE_CTRL2 */
    U32 all;
    struct {
        U32 foutvcopd                   : 1;
        U32 fout4phasepd                : 1;
        U32 foutpostdivpd               : 1;
        U32 dsmpd                       : 1;
        U32 dacpd                       : 1;
        U32 pwrdn                       : 1;
        U32 bypass                      : 1;
        U32                             : 13;
        U32 lock_force                  : 1;
        U32                             : 11;
    } bitc;
} GH_PLL_CORE_CTRL2_S;

typedef union { /* PLL_SCALER_CORE_POST */
    U32 all;
    struct {
        U32 div                         : 4;
        U32                             : 28;
    } bitc;
} GH_PLL_SCALER_CORE_POST_S;

typedef union { /* PLL_VIDEO_CTRL2 */
    U32 all;
    struct {
        U32 foutvcopd                   : 1;
        U32 fout4phasepd                : 1;
        U32 foutpostdivpd               : 1;
        U32 dsmpd                       : 1;
        U32 dacpd                       : 1;
        U32 pwrdn                       : 1;
        U32 bypass                      : 1;
        U32                             : 13;
        U32 lock_force                  : 1;
        U32                             : 11;
    } bitc;
} GH_PLL_VIDEO_CTRL2_S;

typedef union { /* PLL_SENSOR_CTRL2 */
    U32 all;
    struct {
        U32 foutvcopd                   : 1;
        U32 fout4phasepd                : 1;
        U32 foutpostdivpd               : 1;
        U32 dsmpd                       : 1;
        U32 dacpd                       : 1;
        U32 pwrdn                       : 1;
        U32 bypass                      : 1;
        U32                             : 13;
        U32 lock_force                  : 1;
        U32                             : 11;
    } bitc;
} GH_PLL_SENSOR_CTRL2_S;

typedef union { /* PLL_AUDIO_CTRL2 */
    U32 all;
    struct {
        U32 foutvcopd                   : 1;
        U32 fout4phasepd                : 1;
        U32 foutpostdivpd               : 1;
        U32 dsmpd                       : 1;
        U32 dacpd                       : 1;
        U32 pwrdn                       : 1;
        U32 bypass                      : 1;
        U32                             : 13;
        U32 lock_force                  : 1;
        U32                             : 11;
    } bitc;
} GH_PLL_AUDIO_CTRL2_S;

typedef union { /* PLL_IOCTRL_JTAG */
    U32 all;
    struct {
        U32 level                       : 6;
        U32                             : 26;
    } bitc;
} GH_PLL_IOCTRL_JTAG_S;

typedef union { /* PLL_IOCTRL_SFLASH */
    U32 all;
    struct {
        U32 level                       : 6;
        U32                             : 26;
    } bitc;
} GH_PLL_IOCTRL_SFLASH_S;

typedef union { /* PLL_IOCTRL_SENSOR */
    U32 all;
    struct {
        U32 level                       : 6;
        U32                             : 26;
    } bitc;
} GH_PLL_IOCTRL_SENSOR_S;

typedef union { /* PLL_CLOCK_VO */
    U32 all;
    struct {
        U32 clk_voa_common_vob          : 1;
        U32                             : 31;
    } bitc;
} GH_PLL_CLOCK_VO_S;

typedef union { /* PLL_CLOCK_OBSV */
    U32 all;
    struct {
        U32 en                          : 1;
        U32                             : 3;
        U32 pll                         : 4;
        U32                             : 24;
    } bitc;
} GH_PLL_CLOCK_OBSV_S;

typedef union { /* PLL_SCALER_IDSP_POST */
    U32 all;
    struct {
        U32 div                         : 4;
        U32                             : 28;
    } bitc;
} GH_PLL_SCALER_IDSP_POST_S;

typedef union { /* PLL_GENERAL_CONFIG */
    U32 all;
    struct {
        U32 sdata_width                 : 1;
        U32 bt1120_in                   : 1;
        U32 bt1120_out                  : 1;
        U32 sdata_swap                  : 1;
        U32 spclk_sel                   : 1;
        U32                             : 27;
    } bitc;
} GH_PLL_GENERAL_CONFIG_S;

typedef union { /* PLL_CLK_REF_SSI */
    U32 all;
    struct {
        U32 clk                         : 1;
        U32                             : 31;
    } bitc;
} GH_PLL_CLK_REF_SSI_S;

typedef union { /* PLL_DDRC_IDSP_RESET */
    U32 all;
    struct {
        U32 ddrc                        : 1;
        U32 idsp                        : 1;
        U32 nr3d                        : 1;
        U32                             : 29;
    } bitc;
} GH_PLL_DDRC_IDSP_RESET_S;

typedef union { /* PLL_IOCTRL_GPIO */
    U32 all;
    struct {
        U32 io0                         : 6;
        U32                             : 2;
        U32 io1                         : 6;
        U32                             : 2;
        U32 io2                         : 6;
        U32                             : 2;
        U32 io3                         : 6;
        U32                             : 2;
    } bitc;
} GH_PLL_IOCTRL_GPIO_S;



typedef union { /* PLL_IOCTRL_GPIO56 */
    U32 all;
    struct {
        U32 io0                         : 6;
        U32                             : 2;
        U32 io1                         : 6;
        U32                             : 2;
        U32 io2                         : 6;
        U32                             : 2;
        U32 io3                         : 6;
        U32                             : 2;
    } bitc;
} GH_PLL_IOCTRL_GPIO56_S;

typedef union { /* PLL_IOCTRL_XCLK */
    U32 all;
    struct {
        U32 bypass                      : 1;
        U32                             : 31;
    } bitc;
} GH_PLL_IOCTRL_XCLK_S;

typedef union { /* PLL_SCALER_DDR_CALIB */
    U32 all;
    struct {
        U32 div                         : 4;
        U32                             : 28;
    } bitc;
} GH_PLL_SCALER_DDR_CALIB_S;

typedef union { /* PLL_LOCK */
    U32 all;
    struct {
        U32 video2                      : 1;
        U32 video                       : 1;
        U32                             : 1;
        U32 sensor                      : 1;
        U32 idsp                        : 1;
        U32 ddr                         : 1;
        U32 core                        : 1;
        U32 audio                       : 1;
        U32                             : 24;
    } bitc;
} GH_PLL_LOCK_S;

typedef union { /* PLL_SCALER_DEBOUNCE */
    U32 all;
    struct {
        U32 div                         : 24;
        U32                             : 8;
    } bitc;
} GH_PLL_SCALER_DEBOUNCE_S;

typedef union { /* PLL_CKEN_VDSP */
    U32 all;
    struct {
        U32 memd                        : 1;
        U32 tsfm                        : 1;
        U32 code                        : 1;
        U32 smem                        : 1;
        U32 md                          : 1;
        U32 me                          : 1;
        U32 mctf                        : 1;
        U32                             : 25;
    } bitc;
} GH_PLL_CKEN_VDSP_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register PLL_VIDEO_CTRL (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_VIDEO_CTRL'. */
void GH_PLL_set_VIDEO_CTRL(U32 data);
/*! \brief Reads the register 'PLL_VIDEO_CTRL'. */
U32  GH_PLL_get_VIDEO_CTRL(void);
/*! \brief Writes the bit group 'FBDIV' of register 'PLL_VIDEO_CTRL'. */
void GH_PLL_set_VIDEO_CTRL_FBDIV(U16 data);
/*! \brief Reads the bit group 'FBDIV' of register 'PLL_VIDEO_CTRL'. */
U16  GH_PLL_get_VIDEO_CTRL_FBDIV(void);
/*! \brief Writes the bit group 'PSTDIV1' of register 'PLL_VIDEO_CTRL'. */
void GH_PLL_set_VIDEO_CTRL_PSTDIV1(U8 data);
/*! \brief Reads the bit group 'PSTDIV1' of register 'PLL_VIDEO_CTRL'. */
U8   GH_PLL_get_VIDEO_CTRL_PSTDIV1(void);
/*! \brief Writes the bit group 'PSTDIV2' of register 'PLL_VIDEO_CTRL'. */
void GH_PLL_set_VIDEO_CTRL_PSTDIV2(U8 data);
/*! \brief Reads the bit group 'PSTDIV2' of register 'PLL_VIDEO_CTRL'. */
U8   GH_PLL_get_VIDEO_CTRL_PSTDIV2(void);
/*! \brief Writes the bit group 'REFDIV' of register 'PLL_VIDEO_CTRL'. */
void GH_PLL_set_VIDEO_CTRL_REFDIV(U8 data);
/*! \brief Reads the bit group 'REFDIV' of register 'PLL_VIDEO_CTRL'. */
U8   GH_PLL_get_VIDEO_CTRL_REFDIV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_VIDEO_CTRL(U32 data)
{
    *(volatile U32 *)REG_PLL_VIDEO_CTRL = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_VIDEO_CTRL] <-- 0x%08x\n",
                        REG_PLL_VIDEO_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_VIDEO_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_VIDEO_CTRL);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_VIDEO_CTRL] --> 0x%08x\n",
                        REG_PLL_VIDEO_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_VIDEO_CTRL_FBDIV(U16 data)
{
    GH_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_VIDEO_CTRL;
    d.bitc.fbdiv = data;
    *(volatile U32 *)REG_PLL_VIDEO_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_VIDEO_CTRL_FBDIV] <-- 0x%08x\n",
                        REG_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PLL_get_VIDEO_CTRL_FBDIV(void)
{
    GH_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_VIDEO_CTRL_FBDIV] --> 0x%08x\n",
                        REG_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.fbdiv;
}
GH_INLINE void GH_PLL_set_VIDEO_CTRL_PSTDIV1(U8 data)
{
    GH_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_VIDEO_CTRL;
    d.bitc.pstdiv1 = data;
    *(volatile U32 *)REG_PLL_VIDEO_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_VIDEO_CTRL_PSTDIV1] <-- 0x%08x\n",
                        REG_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_VIDEO_CTRL_PSTDIV1(void)
{
    GH_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_VIDEO_CTRL_PSTDIV1] --> 0x%08x\n",
                        REG_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.pstdiv1;
}
GH_INLINE void GH_PLL_set_VIDEO_CTRL_PSTDIV2(U8 data)
{
    GH_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_VIDEO_CTRL;
    d.bitc.pstdiv2 = data;
    *(volatile U32 *)REG_PLL_VIDEO_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_VIDEO_CTRL_PSTDIV2] <-- 0x%08x\n",
                        REG_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_VIDEO_CTRL_PSTDIV2(void)
{
    GH_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_VIDEO_CTRL_PSTDIV2] --> 0x%08x\n",
                        REG_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.pstdiv2;
}
GH_INLINE void GH_PLL_set_VIDEO_CTRL_REFDIV(U8 data)
{
    GH_PLL_VIDEO_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_VIDEO_CTRL;
    d.bitc.refdiv = data;
    *(volatile U32 *)REG_PLL_VIDEO_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_VIDEO_CTRL_REFDIV] <-- 0x%08x\n",
                        REG_PLL_VIDEO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_VIDEO_CTRL_REFDIV(void)
{
    GH_PLL_VIDEO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_VIDEO_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_VIDEO_CTRL_REFDIV] --> 0x%08x\n",
                        REG_PLL_VIDEO_CTRL,value);
    #endif
    return tmp_value.bitc.refdiv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_VIDEO_PRE (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_SCALER_VIDEO_PRE'. */
void GH_PLL_set_SCALER_VIDEO_PRE(U32 data);
/*! \brief Reads the register 'PLL_SCALER_VIDEO_PRE'. */
U32  GH_PLL_get_SCALER_VIDEO_PRE(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_VIDEO_PRE'. */
void GH_PLL_set_SCALER_VIDEO_PRE_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_VIDEO_PRE'. */
U16  GH_PLL_get_SCALER_VIDEO_PRE_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_SCALER_VIDEO_PRE(U32 data)
{
    *(volatile U32 *)REG_PLL_SCALER_VIDEO_PRE = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_VIDEO_PRE] <-- 0x%08x\n",
                        REG_PLL_SCALER_VIDEO_PRE,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_VIDEO_PRE(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_VIDEO_PRE);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_VIDEO_PRE] --> 0x%08x\n",
                        REG_PLL_SCALER_VIDEO_PRE,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_SCALER_VIDEO_PRE_Div(U16 data)
{
    GH_PLL_SCALER_VIDEO_PRE_S d;
    d.all = *(volatile U32 *)REG_PLL_SCALER_VIDEO_PRE;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_SCALER_VIDEO_PRE = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_VIDEO_PRE_Div] <-- 0x%08x\n",
                        REG_PLL_SCALER_VIDEO_PRE,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PLL_get_SCALER_VIDEO_PRE_Div(void)
{
    GH_PLL_SCALER_VIDEO_PRE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_VIDEO_PRE);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_VIDEO_PRE_Div] --> 0x%08x\n",
                        REG_PLL_SCALER_VIDEO_PRE,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_VIDEO_FRAC (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_VIDEO_FRAC'. */
void GH_PLL_set_VIDEO_FRAC(U32 data);
/*! \brief Reads the register 'PLL_VIDEO_FRAC'. */
U32  GH_PLL_get_VIDEO_FRAC(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_VIDEO_FRAC'. */
void GH_PLL_set_VIDEO_FRAC_Div(U32 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_VIDEO_FRAC'. */
U32  GH_PLL_get_VIDEO_FRAC_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_VIDEO_FRAC(U32 data)
{
    *(volatile U32 *)REG_PLL_VIDEO_FRAC = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_VIDEO_FRAC] <-- 0x%08x\n",
                        REG_PLL_VIDEO_FRAC,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_VIDEO_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_VIDEO_FRAC);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_VIDEO_FRAC] --> 0x%08x\n",
                        REG_PLL_VIDEO_FRAC,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_VIDEO_FRAC_Div(U32 data)
{
    GH_PLL_VIDEO_FRAC_S d;
    d.all = *(volatile U32 *)REG_PLL_VIDEO_FRAC;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_VIDEO_FRAC = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_VIDEO_FRAC_Div] <-- 0x%08x\n",
                        REG_PLL_VIDEO_FRAC,d.all,d.all);
    #endif
}
GH_INLINE U32  GH_PLL_get_VIDEO_FRAC_Div(void)
{
    GH_PLL_VIDEO_FRAC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_VIDEO_FRAC);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_VIDEO_FRAC_Div] --> 0x%08x\n",
                        REG_PLL_VIDEO_FRAC,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_CORE_CTRL (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_CORE_CTRL'. */
void GH_PLL_set_CORE_CTRL(U32 data);
/*! \brief Reads the register 'PLL_CORE_CTRL'. */
U32  GH_PLL_get_CORE_CTRL(void);
/*! \brief Writes the bit group 'FBDIV' of register 'PLL_CORE_CTRL'. */
void GH_PLL_set_CORE_CTRL_FBDIV(U16 data);
/*! \brief Reads the bit group 'FBDIV' of register 'PLL_CORE_CTRL'. */
U16  GH_PLL_get_CORE_CTRL_FBDIV(void);
/*! \brief Writes the bit group 'PSTDIV1' of register 'PLL_CORE_CTRL'. */
void GH_PLL_set_CORE_CTRL_PSTDIV1(U8 data);
/*! \brief Reads the bit group 'PSTDIV1' of register 'PLL_CORE_CTRL'. */
U8   GH_PLL_get_CORE_CTRL_PSTDIV1(void);
/*! \brief Writes the bit group 'PSTDIV2' of register 'PLL_CORE_CTRL'. */
void GH_PLL_set_CORE_CTRL_PSTDIV2(U8 data);
/*! \brief Reads the bit group 'PSTDIV2' of register 'PLL_CORE_CTRL'. */
U8   GH_PLL_get_CORE_CTRL_PSTDIV2(void);
/*! \brief Writes the bit group 'REFDIV' of register 'PLL_CORE_CTRL'. */
void GH_PLL_set_CORE_CTRL_REFDIV(U8 data);
/*! \brief Reads the bit group 'REFDIV' of register 'PLL_CORE_CTRL'. */
U8   GH_PLL_get_CORE_CTRL_REFDIV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_CORE_CTRL(U32 data)
{
    *(volatile U32 *)REG_PLL_CORE_CTRL = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CORE_CTRL] <-- 0x%08x\n",
                        REG_PLL_CORE_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_CORE_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_CORE_CTRL);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CORE_CTRL] --> 0x%08x\n",
                        REG_PLL_CORE_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_CORE_CTRL_FBDIV(U16 data)
{
    GH_PLL_CORE_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_CORE_CTRL;
    d.bitc.fbdiv = data;
    *(volatile U32 *)REG_PLL_CORE_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CORE_CTRL_FBDIV] <-- 0x%08x\n",
                        REG_PLL_CORE_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PLL_get_CORE_CTRL_FBDIV(void)
{
    GH_PLL_CORE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CORE_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CORE_CTRL_FBDIV] --> 0x%08x\n",
                        REG_PLL_CORE_CTRL,value);
    #endif
    return tmp_value.bitc.fbdiv;
}
GH_INLINE void GH_PLL_set_CORE_CTRL_PSTDIV1(U8 data)
{
    GH_PLL_CORE_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_CORE_CTRL;
    d.bitc.pstdiv1 = data;
    *(volatile U32 *)REG_PLL_CORE_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CORE_CTRL_PSTDIV1] <-- 0x%08x\n",
                        REG_PLL_CORE_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CORE_CTRL_PSTDIV1(void)
{
    GH_PLL_CORE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CORE_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CORE_CTRL_PSTDIV1] --> 0x%08x\n",
                        REG_PLL_CORE_CTRL,value);
    #endif
    return tmp_value.bitc.pstdiv1;
}
GH_INLINE void GH_PLL_set_CORE_CTRL_PSTDIV2(U8 data)
{
    GH_PLL_CORE_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_CORE_CTRL;
    d.bitc.pstdiv2 = data;
    *(volatile U32 *)REG_PLL_CORE_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CORE_CTRL_PSTDIV2] <-- 0x%08x\n",
                        REG_PLL_CORE_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CORE_CTRL_PSTDIV2(void)
{
    GH_PLL_CORE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CORE_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CORE_CTRL_PSTDIV2] --> 0x%08x\n",
                        REG_PLL_CORE_CTRL,value);
    #endif
    return tmp_value.bitc.pstdiv2;
}
GH_INLINE void GH_PLL_set_CORE_CTRL_REFDIV(U8 data)
{
    GH_PLL_CORE_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_CORE_CTRL;
    d.bitc.refdiv = data;
    *(volatile U32 *)REG_PLL_CORE_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CORE_CTRL_REFDIV] <-- 0x%08x\n",
                        REG_PLL_CORE_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CORE_CTRL_REFDIV(void)
{
    GH_PLL_CORE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CORE_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CORE_CTRL_REFDIV] --> 0x%08x\n",
                        REG_PLL_CORE_CTRL,value);
    #endif
    return tmp_value.bitc.refdiv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_SD48 (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_SCALER_SD48'. */
void GH_PLL_set_SCALER_SD48(U32 data);
/*! \brief Reads the register 'PLL_SCALER_SD48'. */
U32  GH_PLL_get_SCALER_SD48(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_SD48'. */
void GH_PLL_set_SCALER_SD48_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_SD48'. */
U16  GH_PLL_get_SCALER_SD48_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_SCALER_SD48(U32 data)
{
    *(volatile U32 *)REG_PLL_SCALER_SD48 = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_SD48] <-- 0x%08x\n",
                        REG_PLL_SCALER_SD48,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_SD48(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_SD48);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_SD48] --> 0x%08x\n",
                        REG_PLL_SCALER_SD48,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_SCALER_SD48_Div(U16 data)
{
    GH_PLL_SCALER_SD48_S d;
    d.all = *(volatile U32 *)REG_PLL_SCALER_SD48;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_SCALER_SD48 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_SD48_Div] <-- 0x%08x\n",
                        REG_PLL_SCALER_SD48,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PLL_get_SCALER_SD48_Div(void)
{
    GH_PLL_SCALER_SD48_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_SD48);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_SD48_Div] --> 0x%08x\n",
                        REG_PLL_SCALER_SD48,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_CORE_FRAC (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_CORE_FRAC'. */
void GH_PLL_set_CORE_FRAC(U32 data);
/*! \brief Reads the register 'PLL_CORE_FRAC'. */
U32  GH_PLL_get_CORE_FRAC(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_CORE_FRAC'. */
void GH_PLL_set_CORE_FRAC_Div(U32 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_CORE_FRAC'. */
U32  GH_PLL_get_CORE_FRAC_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_CORE_FRAC(U32 data)
{
    *(volatile U32 *)REG_PLL_CORE_FRAC = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CORE_FRAC] <-- 0x%08x\n",
                        REG_PLL_CORE_FRAC,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_CORE_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_CORE_FRAC);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CORE_FRAC] --> 0x%08x\n",
                        REG_PLL_CORE_FRAC,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_CORE_FRAC_Div(U32 data)
{
    GH_PLL_CORE_FRAC_S d;
    d.all = *(volatile U32 *)REG_PLL_CORE_FRAC;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_CORE_FRAC = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CORE_FRAC_Div] <-- 0x%08x\n",
                        REG_PLL_CORE_FRAC,d.all,d.all);
    #endif
}
GH_INLINE U32  GH_PLL_get_CORE_FRAC_Div(void)
{
    GH_PLL_CORE_FRAC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CORE_FRAC);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CORE_FRAC_Div] --> 0x%08x\n",
                        REG_PLL_CORE_FRAC,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_AUDIO_CTRL (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_AUDIO_CTRL'. */
void GH_PLL_set_AUDIO_CTRL(U32 data);
/*! \brief Reads the register 'PLL_AUDIO_CTRL'. */
U32  GH_PLL_get_AUDIO_CTRL(void);
/*! \brief Writes the bit group 'FBDIV' of register 'PLL_AUDIO_CTRL'. */
void GH_PLL_set_AUDIO_CTRL_FBDIV(U16 data);
/*! \brief Reads the bit group 'FBDIV' of register 'PLL_AUDIO_CTRL'. */
U16  GH_PLL_get_AUDIO_CTRL_FBDIV(void);
/*! \brief Writes the bit group 'PSTDIV1' of register 'PLL_AUDIO_CTRL'. */
void GH_PLL_set_AUDIO_CTRL_PSTDIV1(U8 data);
/*! \brief Reads the bit group 'PSTDIV1' of register 'PLL_AUDIO_CTRL'. */
U8   GH_PLL_get_AUDIO_CTRL_PSTDIV1(void);
/*! \brief Writes the bit group 'PSTDIV2' of register 'PLL_AUDIO_CTRL'. */
void GH_PLL_set_AUDIO_CTRL_PSTDIV2(U8 data);
/*! \brief Reads the bit group 'PSTDIV2' of register 'PLL_AUDIO_CTRL'. */
U8   GH_PLL_get_AUDIO_CTRL_PSTDIV2(void);
/*! \brief Writes the bit group 'REFDIV' of register 'PLL_AUDIO_CTRL'. */
void GH_PLL_set_AUDIO_CTRL_REFDIV(U8 data);
/*! \brief Reads the bit group 'REFDIV' of register 'PLL_AUDIO_CTRL'. */
U8   GH_PLL_get_AUDIO_CTRL_REFDIV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_AUDIO_CTRL(U32 data)
{
    *(volatile U32 *)REG_PLL_AUDIO_CTRL = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_AUDIO_CTRL] <-- 0x%08x\n",
                        REG_PLL_AUDIO_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_AUDIO_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_AUDIO_CTRL);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_AUDIO_CTRL] --> 0x%08x\n",
                        REG_PLL_AUDIO_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_AUDIO_CTRL_FBDIV(U16 data)
{
    GH_PLL_AUDIO_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_AUDIO_CTRL;
    d.bitc.fbdiv = data;
    *(volatile U32 *)REG_PLL_AUDIO_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_AUDIO_CTRL_FBDIV] <-- 0x%08x\n",
                        REG_PLL_AUDIO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PLL_get_AUDIO_CTRL_FBDIV(void)
{
    GH_PLL_AUDIO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_AUDIO_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_AUDIO_CTRL_FBDIV] --> 0x%08x\n",
                        REG_PLL_AUDIO_CTRL,value);
    #endif
    return tmp_value.bitc.fbdiv;
}
GH_INLINE void GH_PLL_set_AUDIO_CTRL_PSTDIV1(U8 data)
{
    GH_PLL_AUDIO_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_AUDIO_CTRL;
    d.bitc.pstdiv1 = data;
    *(volatile U32 *)REG_PLL_AUDIO_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_AUDIO_CTRL_PSTDIV1] <-- 0x%08x\n",
                        REG_PLL_AUDIO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_AUDIO_CTRL_PSTDIV1(void)
{
    GH_PLL_AUDIO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_AUDIO_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_AUDIO_CTRL_PSTDIV1] --> 0x%08x\n",
                        REG_PLL_AUDIO_CTRL,value);
    #endif
    return tmp_value.bitc.pstdiv1;
}
GH_INLINE void GH_PLL_set_AUDIO_CTRL_PSTDIV2(U8 data)
{
    GH_PLL_AUDIO_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_AUDIO_CTRL;
    d.bitc.pstdiv2 = data;
    *(volatile U32 *)REG_PLL_AUDIO_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_AUDIO_CTRL_PSTDIV2] <-- 0x%08x\n",
                        REG_PLL_AUDIO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_AUDIO_CTRL_PSTDIV2(void)
{
    GH_PLL_AUDIO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_AUDIO_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_AUDIO_CTRL_PSTDIV2] --> 0x%08x\n",
                        REG_PLL_AUDIO_CTRL,value);
    #endif
    return tmp_value.bitc.pstdiv2;
}
GH_INLINE void GH_PLL_set_AUDIO_CTRL_REFDIV(U8 data)
{
    GH_PLL_AUDIO_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_AUDIO_CTRL;
    d.bitc.refdiv = data;
    *(volatile U32 *)REG_PLL_AUDIO_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_AUDIO_CTRL_REFDIV] <-- 0x%08x\n",
                        REG_PLL_AUDIO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_AUDIO_CTRL_REFDIV(void)
{
    GH_PLL_AUDIO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_AUDIO_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_AUDIO_CTRL_REFDIV] --> 0x%08x\n",
                        REG_PLL_AUDIO_CTRL,value);
    #endif
    return tmp_value.bitc.refdiv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_UART (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_SCALER_UART'. */
void GH_PLL_set_SCALER_UART(U32 data);
/*! \brief Reads the register 'PLL_SCALER_UART'. */
U32  GH_PLL_get_SCALER_UART(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_UART'. */
void GH_PLL_set_SCALER_UART_Div(U32 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_UART'. */
U32  GH_PLL_get_SCALER_UART_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_SCALER_UART(U32 data)
{
    *(volatile U32 *)REG_PLL_SCALER_UART = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_UART] <-- 0x%08x\n",
                        REG_PLL_SCALER_UART,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_UART(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_UART);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_UART] --> 0x%08x\n",
                        REG_PLL_SCALER_UART,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_SCALER_UART_Div(U32 data)
{
    GH_PLL_SCALER_UART_S d;
    d.all = *(volatile U32 *)REG_PLL_SCALER_UART;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_SCALER_UART = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_UART_Div] <-- 0x%08x\n",
                        REG_PLL_SCALER_UART,d.all,d.all);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_UART_Div(void)
{
    GH_PLL_SCALER_UART_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_UART);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_UART_Div] --> 0x%08x\n",
                        REG_PLL_SCALER_UART,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_SENSOR_PRE (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_SCALER_SENSOR_PRE'. */
void GH_PLL_set_SCALER_SENSOR_PRE(U32 data);
/*! \brief Reads the register 'PLL_SCALER_SENSOR_PRE'. */
U32  GH_PLL_get_SCALER_SENSOR_PRE(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_SENSOR_PRE'. */
void GH_PLL_set_SCALER_SENSOR_PRE_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_SENSOR_PRE'. */
U16  GH_PLL_get_SCALER_SENSOR_PRE_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_SCALER_SENSOR_PRE(U32 data)
{
    *(volatile U32 *)REG_PLL_SCALER_SENSOR_PRE = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_SENSOR_PRE] <-- 0x%08x\n",
                        REG_PLL_SCALER_SENSOR_PRE,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_SENSOR_PRE(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_SENSOR_PRE);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_SENSOR_PRE] --> 0x%08x\n",
                        REG_PLL_SCALER_SENSOR_PRE,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_SCALER_SENSOR_PRE_Div(U16 data)
{
    GH_PLL_SCALER_SENSOR_PRE_S d;
    d.all = *(volatile U32 *)REG_PLL_SCALER_SENSOR_PRE;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_SCALER_SENSOR_PRE = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_SENSOR_PRE_Div] <-- 0x%08x\n",
                        REG_PLL_SCALER_SENSOR_PRE,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PLL_get_SCALER_SENSOR_PRE_Div(void)
{
    GH_PLL_SCALER_SENSOR_PRE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_SENSOR_PRE);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_SENSOR_PRE_Div] --> 0x%08x\n",
                        REG_PLL_SCALER_SENSOR_PRE,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_SSI (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_SCALER_SSI'. */
void GH_PLL_set_SCALER_SSI(U32 data);
/*! \brief Reads the register 'PLL_SCALER_SSI'. */
U32  GH_PLL_get_SCALER_SSI(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_SSI'. */
void GH_PLL_set_SCALER_SSI_Div(U32 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_SSI'. */
U32  GH_PLL_get_SCALER_SSI_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_SCALER_SSI(U32 data)
{
    *(volatile U32 *)REG_PLL_SCALER_SSI = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_SSI] <-- 0x%08x\n",
                        REG_PLL_SCALER_SSI,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_SSI(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_SSI);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_SSI] --> 0x%08x\n",
                        REG_PLL_SCALER_SSI,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_SCALER_SSI_Div(U32 data)
{
    GH_PLL_SCALER_SSI_S d;
    d.all = *(volatile U32 *)REG_PLL_SCALER_SSI;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_SCALER_SSI = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_SSI_Div] <-- 0x%08x\n",
                        REG_PLL_SCALER_SSI,d.all,d.all);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_SSI_Div(void)
{
    GH_PLL_SCALER_SSI_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_SSI);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_SSI_Div] --> 0x%08x\n",
                        REG_PLL_SCALER_SSI,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_SENSOR_POST (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_SCALER_SENSOR_POST'. */
void GH_PLL_set_SCALER_SENSOR_POST(U32 data);
/*! \brief Reads the register 'PLL_SCALER_SENSOR_POST'. */
U32  GH_PLL_get_SCALER_SENSOR_POST(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_SENSOR_POST'. */
void GH_PLL_set_SCALER_SENSOR_POST_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_SENSOR_POST'. */
U16  GH_PLL_get_SCALER_SENSOR_POST_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_SCALER_SENSOR_POST(U32 data)
{
    *(volatile U32 *)REG_PLL_SCALER_SENSOR_POST = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_SENSOR_POST] <-- 0x%08x\n",
                        REG_PLL_SCALER_SENSOR_POST,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_SENSOR_POST(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_SENSOR_POST);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_SENSOR_POST] --> 0x%08x\n",
                        REG_PLL_SCALER_SENSOR_POST,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_SCALER_SENSOR_POST_Div(U16 data)
{
    GH_PLL_SCALER_SENSOR_POST_S d;
    d.all = *(volatile U32 *)REG_PLL_SCALER_SENSOR_POST;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_SCALER_SENSOR_POST = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_SENSOR_POST_Div] <-- 0x%08x\n",
                        REG_PLL_SCALER_SENSOR_POST,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PLL_get_SCALER_SENSOR_POST_Div(void)
{
    GH_PLL_SCALER_SENSOR_POST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_SENSOR_POST);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_SENSOR_POST_Div] --> 0x%08x\n",
                        REG_PLL_SCALER_SENSOR_POST,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_SENSOR_FRAC (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_SENSOR_FRAC'. */
void GH_PLL_set_SENSOR_FRAC(U32 data);
/*! \brief Reads the register 'PLL_SENSOR_FRAC'. */
U32  GH_PLL_get_SENSOR_FRAC(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SENSOR_FRAC'. */
void GH_PLL_set_SENSOR_FRAC_Div(U32 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SENSOR_FRAC'. */
U32  GH_PLL_get_SENSOR_FRAC_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_SENSOR_FRAC(U32 data)
{
    *(volatile U32 *)REG_PLL_SENSOR_FRAC = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SENSOR_FRAC] <-- 0x%08x\n",
                        REG_PLL_SENSOR_FRAC,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_SENSOR_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_SENSOR_FRAC);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SENSOR_FRAC] --> 0x%08x\n",
                        REG_PLL_SENSOR_FRAC,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_SENSOR_FRAC_Div(U32 data)
{
    GH_PLL_SENSOR_FRAC_S d;
    d.all = *(volatile U32 *)REG_PLL_SENSOR_FRAC;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_SENSOR_FRAC = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SENSOR_FRAC_Div] <-- 0x%08x\n",
                        REG_PLL_SENSOR_FRAC,d.all,d.all);
    #endif
}
GH_INLINE U32  GH_PLL_get_SENSOR_FRAC_Div(void)
{
    GH_PLL_SENSOR_FRAC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SENSOR_FRAC);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SENSOR_FRAC_Div] --> 0x%08x\n",
                        REG_PLL_SENSOR_FRAC,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_USB_GRST (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_USB_GRST'. */
void GH_PLL_set_USB_GRST(U32 data);
/*! \brief Reads the register 'PLL_USB_GRST'. */
U32  GH_PLL_get_USB_GRST(void);
/*! \brief Writes the bit group 'en' of register 'PLL_USB_GRST'. */
void GH_PLL_set_USB_GRST_en(U8 data);
/*! \brief Reads the bit group 'en' of register 'PLL_USB_GRST'. */
U8   GH_PLL_get_USB_GRST_en(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_USB_GRST(U32 data)
{
    *(volatile U32 *)REG_PLL_USB_GRST = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_USB_GRST] <-- 0x%08x\n",
                        REG_PLL_USB_GRST,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_USB_GRST(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_USB_GRST);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_USB_GRST] --> 0x%08x\n",
                        REG_PLL_USB_GRST,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_USB_GRST_en(U8 data)
{
    GH_PLL_USB_GRST_S d;
    d.all = *(volatile U32 *)REG_PLL_USB_GRST;
    d.bitc.en = data;
    *(volatile U32 *)REG_PLL_USB_GRST = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_USB_GRST_en] <-- 0x%08x\n",
                        REG_PLL_USB_GRST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_USB_GRST_en(void)
{
    GH_PLL_USB_GRST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_USB_GRST);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_USB_GRST_en] --> 0x%08x\n",
                        REG_PLL_USB_GRST,value);
    #endif
    return tmp_value.bitc.en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_SENSOR_CTRL (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_SENSOR_CTRL'. */
void GH_PLL_set_SENSOR_CTRL(U32 data);
/*! \brief Reads the register 'PLL_SENSOR_CTRL'. */
U32  GH_PLL_get_SENSOR_CTRL(void);
/*! \brief Writes the bit group 'FBDIV' of register 'PLL_SENSOR_CTRL'. */
void GH_PLL_set_SENSOR_CTRL_FBDIV(U16 data);
/*! \brief Reads the bit group 'FBDIV' of register 'PLL_SENSOR_CTRL'. */
U16  GH_PLL_get_SENSOR_CTRL_FBDIV(void);
/*! \brief Writes the bit group 'PSTDIV1' of register 'PLL_SENSOR_CTRL'. */
void GH_PLL_set_SENSOR_CTRL_PSTDIV1(U8 data);
/*! \brief Reads the bit group 'PSTDIV1' of register 'PLL_SENSOR_CTRL'. */
U8   GH_PLL_get_SENSOR_CTRL_PSTDIV1(void);
/*! \brief Writes the bit group 'PSTDIV2' of register 'PLL_SENSOR_CTRL'. */
void GH_PLL_set_SENSOR_CTRL_PSTDIV2(U8 data);
/*! \brief Reads the bit group 'PSTDIV2' of register 'PLL_SENSOR_CTRL'. */
U8   GH_PLL_get_SENSOR_CTRL_PSTDIV2(void);
/*! \brief Writes the bit group 'REFDIV' of register 'PLL_SENSOR_CTRL'. */
void GH_PLL_set_SENSOR_CTRL_REFDIV(U8 data);
/*! \brief Reads the bit group 'REFDIV' of register 'PLL_SENSOR_CTRL'. */
U8   GH_PLL_get_SENSOR_CTRL_REFDIV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_SENSOR_CTRL(U32 data)
{
    *(volatile U32 *)REG_PLL_SENSOR_CTRL = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SENSOR_CTRL] <-- 0x%08x\n",
                        REG_PLL_SENSOR_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_SENSOR_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_SENSOR_CTRL);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SENSOR_CTRL] --> 0x%08x\n",
                        REG_PLL_SENSOR_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_SENSOR_CTRL_FBDIV(U16 data)
{
    GH_PLL_SENSOR_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_SENSOR_CTRL;
    d.bitc.fbdiv = data;
    *(volatile U32 *)REG_PLL_SENSOR_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SENSOR_CTRL_FBDIV] <-- 0x%08x\n",
                        REG_PLL_SENSOR_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PLL_get_SENSOR_CTRL_FBDIV(void)
{
    GH_PLL_SENSOR_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SENSOR_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SENSOR_CTRL_FBDIV] --> 0x%08x\n",
                        REG_PLL_SENSOR_CTRL,value);
    #endif
    return tmp_value.bitc.fbdiv;
}
GH_INLINE void GH_PLL_set_SENSOR_CTRL_PSTDIV1(U8 data)
{
    GH_PLL_SENSOR_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_SENSOR_CTRL;
    d.bitc.pstdiv1 = data;
    *(volatile U32 *)REG_PLL_SENSOR_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SENSOR_CTRL_PSTDIV1] <-- 0x%08x\n",
                        REG_PLL_SENSOR_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_SENSOR_CTRL_PSTDIV1(void)
{
    GH_PLL_SENSOR_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SENSOR_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SENSOR_CTRL_PSTDIV1] --> 0x%08x\n",
                        REG_PLL_SENSOR_CTRL,value);
    #endif
    return tmp_value.bitc.pstdiv1;
}
GH_INLINE void GH_PLL_set_SENSOR_CTRL_PSTDIV2(U8 data)
{
    GH_PLL_SENSOR_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_SENSOR_CTRL;
    d.bitc.pstdiv2 = data;
    *(volatile U32 *)REG_PLL_SENSOR_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SENSOR_CTRL_PSTDIV2] <-- 0x%08x\n",
                        REG_PLL_SENSOR_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_SENSOR_CTRL_PSTDIV2(void)
{
    GH_PLL_SENSOR_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SENSOR_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SENSOR_CTRL_PSTDIV2] --> 0x%08x\n",
                        REG_PLL_SENSOR_CTRL,value);
    #endif
    return tmp_value.bitc.pstdiv2;
}
GH_INLINE void GH_PLL_set_SENSOR_CTRL_REFDIV(U8 data)
{
    GH_PLL_SENSOR_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_SENSOR_CTRL;
    d.bitc.refdiv = data;
    *(volatile U32 *)REG_PLL_SENSOR_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SENSOR_CTRL_REFDIV] <-- 0x%08x\n",
                        REG_PLL_SENSOR_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_SENSOR_CTRL_REFDIV(void)
{
    GH_PLL_SENSOR_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SENSOR_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SENSOR_CTRL_REFDIV] --> 0x%08x\n",
                        REG_PLL_SENSOR_CTRL,value);
    #endif
    return tmp_value.bitc.refdiv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_WDT_RST_L (read)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'PLL_WDT_RST_L'. */
U32  GH_PLL_get_WDT_RST_L(void);
/*! \brief Reads the bit group 'reset' of register 'PLL_WDT_RST_L'. */
U8   GH_PLL_get_WDT_RST_L_reset(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_PLL_get_WDT_RST_L(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_WDT_RST_L);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_WDT_RST_L] --> 0x%08x\n",
                        REG_PLL_WDT_RST_L,value);
    #endif
    return value;
}
GH_INLINE U8   GH_PLL_get_WDT_RST_L_reset(void)
{
    GH_PLL_WDT_RST_L_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_WDT_RST_L);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_WDT_RST_L_reset] --> 0x%08x\n",
                        REG_PLL_WDT_RST_L,value);
    #endif
    return tmp_value.bitc.reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_PWM (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_SCALER_PWM'. */
void GH_PLL_set_SCALER_PWM(U32 data);
/*! \brief Reads the register 'PLL_SCALER_PWM'. */
U32  GH_PLL_get_SCALER_PWM(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_PWM'. */
void GH_PLL_set_SCALER_PWM_Div(U32 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_PWM'. */
U32  GH_PLL_get_SCALER_PWM_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_SCALER_PWM(U32 data)
{
    *(volatile U32 *)REG_PLL_SCALER_PWM = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_PWM] <-- 0x%08x\n",
                        REG_PLL_SCALER_PWM,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_PWM(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_PWM);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_PWM] --> 0x%08x\n",
                        REG_PLL_SCALER_PWM,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_SCALER_PWM_Div(U32 data)
{
    GH_PLL_SCALER_PWM_S d;
    d.all = *(volatile U32 *)REG_PLL_SCALER_PWM;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_SCALER_PWM = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_PWM_Div] <-- 0x%08x\n",
                        REG_PLL_SCALER_PWM,d.all,d.all);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_PWM_Div(void)
{
    GH_PLL_SCALER_PWM_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_PWM);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_PWM_Div] --> 0x%08x\n",
                        REG_PLL_SCALER_PWM,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_AUDIO_FRAC (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_AUDIO_FRAC'. */
void GH_PLL_set_AUDIO_FRAC(U32 data);
/*! \brief Reads the register 'PLL_AUDIO_FRAC'. */
U32  GH_PLL_get_AUDIO_FRAC(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_AUDIO_FRAC'. */
void GH_PLL_set_AUDIO_FRAC_Div(U32 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_AUDIO_FRAC'. */
U32  GH_PLL_get_AUDIO_FRAC_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_AUDIO_FRAC(U32 data)
{
    *(volatile U32 *)REG_PLL_AUDIO_FRAC = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_AUDIO_FRAC] <-- 0x%08x\n",
                        REG_PLL_AUDIO_FRAC,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_AUDIO_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_AUDIO_FRAC);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_AUDIO_FRAC] --> 0x%08x\n",
                        REG_PLL_AUDIO_FRAC,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_AUDIO_FRAC_Div(U32 data)
{
    GH_PLL_AUDIO_FRAC_S d;
    d.all = *(volatile U32 *)REG_PLL_AUDIO_FRAC;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_AUDIO_FRAC = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_AUDIO_FRAC_Div] <-- 0x%08x\n",
                        REG_PLL_AUDIO_FRAC,d.all,d.all);
    #endif
}
GH_INLINE U32  GH_PLL_get_AUDIO_FRAC_Div(void)
{
    GH_PLL_AUDIO_FRAC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_AUDIO_FRAC);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_AUDIO_FRAC_Div] --> 0x%08x\n",
                        REG_PLL_AUDIO_FRAC,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_AUDIO_PRE (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_SCALER_AUDIO_PRE'. */
void GH_PLL_set_SCALER_AUDIO_PRE(U32 data);
/*! \brief Reads the register 'PLL_SCALER_AUDIO_PRE'. */
U32  GH_PLL_get_SCALER_AUDIO_PRE(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_AUDIO_PRE'. */
void GH_PLL_set_SCALER_AUDIO_PRE_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_AUDIO_PRE'. */
U16  GH_PLL_get_SCALER_AUDIO_PRE_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_SCALER_AUDIO_PRE(U32 data)
{
    *(volatile U32 *)REG_PLL_SCALER_AUDIO_PRE = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_AUDIO_PRE] <-- 0x%08x\n",
                        REG_PLL_SCALER_AUDIO_PRE,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_AUDIO_PRE(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_AUDIO_PRE);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_AUDIO_PRE] --> 0x%08x\n",
                        REG_PLL_SCALER_AUDIO_PRE,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_SCALER_AUDIO_PRE_Div(U16 data)
{
    GH_PLL_SCALER_AUDIO_PRE_S d;
    d.all = *(volatile U32 *)REG_PLL_SCALER_AUDIO_PRE;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_SCALER_AUDIO_PRE = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_AUDIO_PRE_Div] <-- 0x%08x\n",
                        REG_PLL_SCALER_AUDIO_PRE,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PLL_get_SCALER_AUDIO_PRE_Div(void)
{
    GH_PLL_SCALER_AUDIO_PRE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_AUDIO_PRE);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_AUDIO_PRE_Div] --> 0x%08x\n",
                        REG_PLL_SCALER_AUDIO_PRE,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_AUDIO_POST (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_SCALER_AUDIO_POST'. */
void GH_PLL_set_SCALER_AUDIO_POST(U32 data);
/*! \brief Reads the register 'PLL_SCALER_AUDIO_POST'. */
U32  GH_PLL_get_SCALER_AUDIO_POST(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_AUDIO_POST'. */
void GH_PLL_set_SCALER_AUDIO_POST_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_AUDIO_POST'. */
U16  GH_PLL_get_SCALER_AUDIO_POST_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_SCALER_AUDIO_POST(U32 data)
{
    *(volatile U32 *)REG_PLL_SCALER_AUDIO_POST = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_AUDIO_POST] <-- 0x%08x\n",
                        REG_PLL_SCALER_AUDIO_POST,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_AUDIO_POST(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_AUDIO_POST);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_AUDIO_POST] --> 0x%08x\n",
                        REG_PLL_SCALER_AUDIO_POST,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_SCALER_AUDIO_POST_Div(U16 data)
{
    GH_PLL_SCALER_AUDIO_POST_S d;
    d.all = *(volatile U32 *)REG_PLL_SCALER_AUDIO_POST;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_SCALER_AUDIO_POST = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_AUDIO_POST_Div] <-- 0x%08x\n",
                        REG_PLL_SCALER_AUDIO_POST,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PLL_get_SCALER_AUDIO_POST_Div(void)
{
    GH_PLL_SCALER_AUDIO_POST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_AUDIO_POST);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_AUDIO_POST_Div] --> 0x%08x\n",
                        REG_PLL_SCALER_AUDIO_POST,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_USB_SRST (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_USB_SRST'. */
void GH_PLL_set_USB_SRST(U32 data);
/*! \brief Reads the register 'PLL_USB_SRST'. */
U32  GH_PLL_get_USB_SRST(void);
/*! \brief Writes the bit group 'en' of register 'PLL_USB_SRST'. */
void GH_PLL_set_USB_SRST_en(U8 data);
/*! \brief Reads the bit group 'en' of register 'PLL_USB_SRST'. */
U8   GH_PLL_get_USB_SRST_en(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_USB_SRST(U32 data)
{
    *(volatile U32 *)REG_PLL_USB_SRST = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_USB_SRST] <-- 0x%08x\n",
                        REG_PLL_USB_SRST,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_USB_SRST(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_USB_SRST);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_USB_SRST] --> 0x%08x\n",
                        REG_PLL_USB_SRST,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_USB_SRST_en(U8 data)
{
    GH_PLL_USB_SRST_S d;
    d.all = *(volatile U32 *)REG_PLL_USB_SRST;
    d.bitc.en = data;
    *(volatile U32 *)REG_PLL_USB_SRST = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_USB_SRST_en] <-- 0x%08x\n",
                        REG_PLL_USB_SRST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_USB_SRST_en(void)
{
    GH_PLL_USB_SRST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_USB_SRST);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_USB_SRST_en] --> 0x%08x\n",
                        REG_PLL_USB_SRST,value);
    #endif
    return tmp_value.bitc.en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_IDSP_CTRL (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_IDSP_CTRL'. */
void GH_PLL_set_IDSP_CTRL(U32 data);
/*! \brief Reads the register 'PLL_IDSP_CTRL'. */
U32  GH_PLL_get_IDSP_CTRL(void);
/*! \brief Writes the bit group 'FBDIV' of register 'PLL_IDSP_CTRL'. */
void GH_PLL_set_IDSP_CTRL_FBDIV(U16 data);
/*! \brief Reads the bit group 'FBDIV' of register 'PLL_IDSP_CTRL'. */
U16  GH_PLL_get_IDSP_CTRL_FBDIV(void);
/*! \brief Writes the bit group 'PSTDIV1' of register 'PLL_IDSP_CTRL'. */
void GH_PLL_set_IDSP_CTRL_PSTDIV1(U8 data);
/*! \brief Reads the bit group 'PSTDIV1' of register 'PLL_IDSP_CTRL'. */
U8   GH_PLL_get_IDSP_CTRL_PSTDIV1(void);
/*! \brief Writes the bit group 'PSTDIV2' of register 'PLL_IDSP_CTRL'. */
void GH_PLL_set_IDSP_CTRL_PSTDIV2(U8 data);
/*! \brief Reads the bit group 'PSTDIV2' of register 'PLL_IDSP_CTRL'. */
U8   GH_PLL_get_IDSP_CTRL_PSTDIV2(void);
/*! \brief Writes the bit group 'REFDIV' of register 'PLL_IDSP_CTRL'. */
void GH_PLL_set_IDSP_CTRL_REFDIV(U8 data);
/*! \brief Reads the bit group 'REFDIV' of register 'PLL_IDSP_CTRL'. */
U8   GH_PLL_get_IDSP_CTRL_REFDIV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_IDSP_CTRL(U32 data)
{
    *(volatile U32 *)REG_PLL_IDSP_CTRL = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IDSP_CTRL] <-- 0x%08x\n",
                        REG_PLL_IDSP_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_IDSP_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_IDSP_CTRL);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IDSP_CTRL] --> 0x%08x\n",
                        REG_PLL_IDSP_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_IDSP_CTRL_FBDIV(U16 data)
{
    GH_PLL_IDSP_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_IDSP_CTRL;
    d.bitc.fbdiv = data;
    *(volatile U32 *)REG_PLL_IDSP_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IDSP_CTRL_FBDIV] <-- 0x%08x\n",
                        REG_PLL_IDSP_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PLL_get_IDSP_CTRL_FBDIV(void)
{
    GH_PLL_IDSP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_IDSP_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IDSP_CTRL_FBDIV] --> 0x%08x\n",
                        REG_PLL_IDSP_CTRL,value);
    #endif
    return tmp_value.bitc.fbdiv;
}
GH_INLINE void GH_PLL_set_IDSP_CTRL_PSTDIV1(U8 data)
{
    GH_PLL_IDSP_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_IDSP_CTRL;
    d.bitc.pstdiv1 = data;
    *(volatile U32 *)REG_PLL_IDSP_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IDSP_CTRL_PSTDIV1] <-- 0x%08x\n",
                        REG_PLL_IDSP_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IDSP_CTRL_PSTDIV1(void)
{
    GH_PLL_IDSP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_IDSP_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IDSP_CTRL_PSTDIV1] --> 0x%08x\n",
                        REG_PLL_IDSP_CTRL,value);
    #endif
    return tmp_value.bitc.pstdiv1;
}
GH_INLINE void GH_PLL_set_IDSP_CTRL_PSTDIV2(U8 data)
{
    GH_PLL_IDSP_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_IDSP_CTRL;
    d.bitc.pstdiv2 = data;
    *(volatile U32 *)REG_PLL_IDSP_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IDSP_CTRL_PSTDIV2] <-- 0x%08x\n",
                        REG_PLL_IDSP_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IDSP_CTRL_PSTDIV2(void)
{
    GH_PLL_IDSP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_IDSP_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IDSP_CTRL_PSTDIV2] --> 0x%08x\n",
                        REG_PLL_IDSP_CTRL,value);
    #endif
    return tmp_value.bitc.pstdiv2;
}
GH_INLINE void GH_PLL_set_IDSP_CTRL_REFDIV(U8 data)
{
    GH_PLL_IDSP_CTRL_S d;
    d.all = *(volatile U32 *)REG_PLL_IDSP_CTRL;
    d.bitc.refdiv = data;
    *(volatile U32 *)REG_PLL_IDSP_CTRL = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IDSP_CTRL_REFDIV] <-- 0x%08x\n",
                        REG_PLL_IDSP_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IDSP_CTRL_REFDIV(void)
{
    GH_PLL_IDSP_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_IDSP_CTRL);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IDSP_CTRL_REFDIV] --> 0x%08x\n",
                        REG_PLL_IDSP_CTRL,value);
    #endif
    return tmp_value.bitc.refdiv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_IDSP_FRAC (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_IDSP_FRAC'. */
void GH_PLL_set_IDSP_FRAC(U32 data);
/*! \brief Reads the register 'PLL_IDSP_FRAC'. */
U32  GH_PLL_get_IDSP_FRAC(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_IDSP_FRAC'. */
void GH_PLL_set_IDSP_FRAC_Div(U32 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_IDSP_FRAC'. */
U32  GH_PLL_get_IDSP_FRAC_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_IDSP_FRAC(U32 data)
{
    *(volatile U32 *)REG_PLL_IDSP_FRAC = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IDSP_FRAC] <-- 0x%08x\n",
                        REG_PLL_IDSP_FRAC,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_IDSP_FRAC(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_IDSP_FRAC);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IDSP_FRAC] --> 0x%08x\n",
                        REG_PLL_IDSP_FRAC,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_IDSP_FRAC_Div(U32 data)
{
    GH_PLL_IDSP_FRAC_S d;
    d.all = *(volatile U32 *)REG_PLL_IDSP_FRAC;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_IDSP_FRAC = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IDSP_FRAC_Div] <-- 0x%08x\n",
                        REG_PLL_IDSP_FRAC,d.all,d.all);
    #endif
}
GH_INLINE U32  GH_PLL_get_IDSP_FRAC_Div(void)
{
    GH_PLL_IDSP_FRAC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_IDSP_FRAC);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IDSP_FRAC_Div] --> 0x%08x\n",
                        REG_PLL_IDSP_FRAC,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_SSI2 (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_SCALER_SSI2'. */
void GH_PLL_set_SCALER_SSI2(U32 data);
/*! \brief Reads the register 'PLL_SCALER_SSI2'. */
U32  GH_PLL_get_SCALER_SSI2(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_SSI2'. */
void GH_PLL_set_SCALER_SSI2_Div(U32 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_SSI2'. */
U32  GH_PLL_get_SCALER_SSI2_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_SCALER_SSI2(U32 data)
{
    *(volatile U32 *)REG_PLL_SCALER_SSI2 = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_SSI2] <-- 0x%08x\n",
                        REG_PLL_SCALER_SSI2,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_SSI2(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_SSI2);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_SSI2] --> 0x%08x\n",
                        REG_PLL_SCALER_SSI2,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_SCALER_SSI2_Div(U32 data)
{
    GH_PLL_SCALER_SSI2_S d;
    d.all = *(volatile U32 *)REG_PLL_SCALER_SSI2;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_SCALER_SSI2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_SSI2_Div] <-- 0x%08x\n",
                        REG_PLL_SCALER_SSI2,d.all,d.all);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_SSI2_Div(void)
{
    GH_PLL_SCALER_SSI2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_SSI2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_SSI2_Div] --> 0x%08x\n",
                        REG_PLL_SCALER_SSI2,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_CLK_OUT (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_CLK_OUT'. */
void GH_PLL_set_CLK_OUT(U32 data);
/*! \brief Reads the register 'PLL_CLK_OUT'. */
U32  GH_PLL_get_CLK_OUT(void);
/*! \brief Writes the bit group 'Div1' of register 'PLL_CLK_OUT'. */
void GH_PLL_set_CLK_OUT_Div1(U16 data);
/*! \brief Reads the bit group 'Div1' of register 'PLL_CLK_OUT'. */
U16  GH_PLL_get_CLK_OUT_Div1(void);
/*! \brief Writes the bit group 'Div2' of register 'PLL_CLK_OUT'. */
void GH_PLL_set_CLK_OUT_Div2(U16 data);
/*! \brief Reads the bit group 'Div2' of register 'PLL_CLK_OUT'. */
U16  GH_PLL_get_CLK_OUT_Div2(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_CLK_OUT(U32 data)
{
    *(volatile U32 *)REG_PLL_CLK_OUT = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CLK_OUT] <-- 0x%08x\n",
                        REG_PLL_CLK_OUT,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_CLK_OUT(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_CLK_OUT);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CLK_OUT] --> 0x%08x\n",
                        REG_PLL_CLK_OUT,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_CLK_OUT_Div1(U16 data)
{
    GH_PLL_CLK_OUT_S d;
    d.all = *(volatile U32 *)REG_PLL_CLK_OUT;
    d.bitc.div1 = data;
    *(volatile U32 *)REG_PLL_CLK_OUT = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CLK_OUT_Div1] <-- 0x%08x\n",
                        REG_PLL_CLK_OUT,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PLL_get_CLK_OUT_Div1(void)
{
    GH_PLL_CLK_OUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CLK_OUT);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CLK_OUT_Div1] --> 0x%08x\n",
                        REG_PLL_CLK_OUT,value);
    #endif
    return tmp_value.bitc.div1;
}
GH_INLINE void GH_PLL_set_CLK_OUT_Div2(U16 data)
{
    GH_PLL_CLK_OUT_S d;
    d.all = *(volatile U32 *)REG_PLL_CLK_OUT;
    d.bitc.div2 = data;
    *(volatile U32 *)REG_PLL_CLK_OUT = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CLK_OUT_Div2] <-- 0x%08x\n",
                        REG_PLL_CLK_OUT,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PLL_get_CLK_OUT_Div2(void)
{
    GH_PLL_CLK_OUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CLK_OUT);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CLK_OUT_Div2] --> 0x%08x\n",
                        REG_PLL_CLK_OUT,value);
    #endif
    return tmp_value.bitc.div2;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_CLK_VOUT (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_CLK_VOUT'. */
void GH_PLL_set_CLK_VOUT(U32 data);
/*! \brief Reads the register 'PLL_CLK_VOUT'. */
U32  GH_PLL_get_CLK_VOUT(void);
/*! \brief Writes the bit group 'sel' of register 'PLL_CLK_VOUT'. */
void GH_PLL_set_CLK_VOUT_sel(U8 data);
/*! \brief Reads the bit group 'sel' of register 'PLL_CLK_VOUT'. */
U8   GH_PLL_get_CLK_VOUT_sel(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_CLK_VOUT(U32 data)
{
    *(volatile U32 *)REG_PLL_CLK_VOUT = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CLK_VOUT] <-- 0x%08x\n",
                        REG_PLL_CLK_VOUT,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_CLK_VOUT(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_CLK_VOUT);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CLK_VOUT] --> 0x%08x\n",
                        REG_PLL_CLK_VOUT,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_CLK_VOUT_sel(U8 data)
{
    GH_PLL_CLK_VOUT_S d;
    d.all = *(volatile U32 *)REG_PLL_CLK_VOUT;
    d.bitc.sel = data;
    *(volatile U32 *)REG_PLL_CLK_VOUT = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CLK_VOUT_sel] <-- 0x%08x\n",
                        REG_PLL_CLK_VOUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CLK_VOUT_sel(void)
{
    GH_PLL_CLK_VOUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CLK_VOUT);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CLK_VOUT_sel] --> 0x%08x\n",
                        REG_PLL_CLK_VOUT,value);
    #endif
    return tmp_value.bitc.sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_ADC (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_SCALER_ADC'. */
void GH_PLL_set_SCALER_ADC(U32 data);
/*! \brief Reads the register 'PLL_SCALER_ADC'. */
U32  GH_PLL_get_SCALER_ADC(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_ADC'. */
void GH_PLL_set_SCALER_ADC_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_ADC'. */
U16  GH_PLL_get_SCALER_ADC_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_SCALER_ADC(U32 data)
{
    *(volatile U32 *)REG_PLL_SCALER_ADC = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_ADC] <-- 0x%08x\n",
                        REG_PLL_SCALER_ADC,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_ADC(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_ADC);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_ADC] --> 0x%08x\n",
                        REG_PLL_SCALER_ADC,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_SCALER_ADC_Div(U16 data)
{
    GH_PLL_SCALER_ADC_S d;
    d.all = *(volatile U32 *)REG_PLL_SCALER_ADC;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_SCALER_ADC = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_ADC_Div] <-- 0x%08x\n",
                        REG_PLL_SCALER_ADC,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PLL_get_SCALER_ADC_Div(void)
{
    GH_PLL_SCALER_ADC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_ADC);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_ADC_Div] --> 0x%08x\n",
                        REG_PLL_SCALER_ADC,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_VIDEO_POST (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_SCALER_VIDEO_POST'. */
void GH_PLL_set_SCALER_VIDEO_POST(U32 data);
/*! \brief Reads the register 'PLL_SCALER_VIDEO_POST'. */
U32  GH_PLL_get_SCALER_VIDEO_POST(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_VIDEO_POST'. */
void GH_PLL_set_SCALER_VIDEO_POST_Div(U16 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_VIDEO_POST'. */
U16  GH_PLL_get_SCALER_VIDEO_POST_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_SCALER_VIDEO_POST(U32 data)
{
    *(volatile U32 *)REG_PLL_SCALER_VIDEO_POST = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_VIDEO_POST] <-- 0x%08x\n",
                        REG_PLL_SCALER_VIDEO_POST,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_VIDEO_POST(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_VIDEO_POST);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_VIDEO_POST] --> 0x%08x\n",
                        REG_PLL_SCALER_VIDEO_POST,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_SCALER_VIDEO_POST_Div(U16 data)
{
    GH_PLL_SCALER_VIDEO_POST_S d;
    d.all = *(volatile U32 *)REG_PLL_SCALER_VIDEO_POST;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_SCALER_VIDEO_POST = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_VIDEO_POST_Div] <-- 0x%08x\n",
                        REG_PLL_SCALER_VIDEO_POST,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_PLL_get_SCALER_VIDEO_POST_Div(void)
{
    GH_PLL_SCALER_VIDEO_POST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_VIDEO_POST);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_VIDEO_POST_Div] --> 0x%08x\n",
                        REG_PLL_SCALER_VIDEO_POST,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_IDSP_CTRL2 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_IDSP_CTRL2'. */
void GH_PLL_set_IDSP_CTRL2(U32 data);
/*! \brief Reads the register 'PLL_IDSP_CTRL2'. */
U32  GH_PLL_get_IDSP_CTRL2(void);
/*! \brief Writes the bit group 'FOUTVCOPD' of register 'PLL_IDSP_CTRL2'. */
void GH_PLL_set_IDSP_CTRL2_FOUTVCOPD(U8 data);
/*! \brief Reads the bit group 'FOUTVCOPD' of register 'PLL_IDSP_CTRL2'. */
U8   GH_PLL_get_IDSP_CTRL2_FOUTVCOPD(void);
/*! \brief Writes the bit group 'FOUT4PHASEPD' of register 'PLL_IDSP_CTRL2'. */
void GH_PLL_set_IDSP_CTRL2_FOUT4PHASEPD(U8 data);
/*! \brief Reads the bit group 'FOUT4PHASEPD' of register 'PLL_IDSP_CTRL2'. */
U8   GH_PLL_get_IDSP_CTRL2_FOUT4PHASEPD(void);
/*! \brief Writes the bit group 'FOUTPOSTDIVPD' of register 'PLL_IDSP_CTRL2'. */
void GH_PLL_set_IDSP_CTRL2_FOUTPOSTDIVPD(U8 data);
/*! \brief Reads the bit group 'FOUTPOSTDIVPD' of register 'PLL_IDSP_CTRL2'. */
U8   GH_PLL_get_IDSP_CTRL2_FOUTPOSTDIVPD(void);
/*! \brief Writes the bit group 'DSMPD' of register 'PLL_IDSP_CTRL2'. */
void GH_PLL_set_IDSP_CTRL2_DSMPD(U8 data);
/*! \brief Reads the bit group 'DSMPD' of register 'PLL_IDSP_CTRL2'. */
U8   GH_PLL_get_IDSP_CTRL2_DSMPD(void);
/*! \brief Writes the bit group 'DACPD' of register 'PLL_IDSP_CTRL2'. */
void GH_PLL_set_IDSP_CTRL2_DACPD(U8 data);
/*! \brief Reads the bit group 'DACPD' of register 'PLL_IDSP_CTRL2'. */
U8   GH_PLL_get_IDSP_CTRL2_DACPD(void);
/*! \brief Writes the bit group 'PWRDN' of register 'PLL_IDSP_CTRL2'. */
void GH_PLL_set_IDSP_CTRL2_PWRDN(U8 data);
/*! \brief Reads the bit group 'PWRDN' of register 'PLL_IDSP_CTRL2'. */
U8   GH_PLL_get_IDSP_CTRL2_PWRDN(void);
/*! \brief Writes the bit group 'BYPASS' of register 'PLL_IDSP_CTRL2'. */
void GH_PLL_set_IDSP_CTRL2_BYPASS(U8 data);
/*! \brief Reads the bit group 'BYPASS' of register 'PLL_IDSP_CTRL2'. */
U8   GH_PLL_get_IDSP_CTRL2_BYPASS(void);
/*! \brief Writes the bit group 'LOCK_FORCE' of register 'PLL_IDSP_CTRL2'. */
void GH_PLL_set_IDSP_CTRL2_LOCK_FORCE(U8 data);
/*! \brief Reads the bit group 'LOCK_FORCE' of register 'PLL_IDSP_CTRL2'. */
U8   GH_PLL_get_IDSP_CTRL2_LOCK_FORCE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_IDSP_CTRL2(U32 data)
{
    *(volatile U32 *)REG_PLL_IDSP_CTRL2 = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IDSP_CTRL2] <-- 0x%08x\n",
                        REG_PLL_IDSP_CTRL2,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_IDSP_CTRL2(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_IDSP_CTRL2);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IDSP_CTRL2] --> 0x%08x\n",
                        REG_PLL_IDSP_CTRL2,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_IDSP_CTRL2_FOUTVCOPD(U8 data)
{
    GH_PLL_IDSP_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_IDSP_CTRL2;
    d.bitc.foutvcopd = data;
    *(volatile U32 *)REG_PLL_IDSP_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IDSP_CTRL2_FOUTVCOPD] <-- 0x%08x\n",
                        REG_PLL_IDSP_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IDSP_CTRL2_FOUTVCOPD(void)
{
    GH_PLL_IDSP_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_IDSP_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IDSP_CTRL2_FOUTVCOPD] --> 0x%08x\n",
                        REG_PLL_IDSP_CTRL2,value);
    #endif
    return tmp_value.bitc.foutvcopd;
}
GH_INLINE void GH_PLL_set_IDSP_CTRL2_FOUT4PHASEPD(U8 data)
{
    GH_PLL_IDSP_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_IDSP_CTRL2;
    d.bitc.fout4phasepd = data;
    *(volatile U32 *)REG_PLL_IDSP_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IDSP_CTRL2_FOUT4PHASEPD] <-- 0x%08x\n",
                        REG_PLL_IDSP_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IDSP_CTRL2_FOUT4PHASEPD(void)
{
    GH_PLL_IDSP_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_IDSP_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IDSP_CTRL2_FOUT4PHASEPD] --> 0x%08x\n",
                        REG_PLL_IDSP_CTRL2,value);
    #endif
    return tmp_value.bitc.fout4phasepd;
}
GH_INLINE void GH_PLL_set_IDSP_CTRL2_FOUTPOSTDIVPD(U8 data)
{
    GH_PLL_IDSP_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_IDSP_CTRL2;
    d.bitc.foutpostdivpd = data;
    *(volatile U32 *)REG_PLL_IDSP_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IDSP_CTRL2_FOUTPOSTDIVPD] <-- 0x%08x\n",
                        REG_PLL_IDSP_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IDSP_CTRL2_FOUTPOSTDIVPD(void)
{
    GH_PLL_IDSP_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_IDSP_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IDSP_CTRL2_FOUTPOSTDIVPD] --> 0x%08x\n",
                        REG_PLL_IDSP_CTRL2,value);
    #endif
    return tmp_value.bitc.foutpostdivpd;
}
GH_INLINE void GH_PLL_set_IDSP_CTRL2_DSMPD(U8 data)
{
    GH_PLL_IDSP_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_IDSP_CTRL2;
    d.bitc.dsmpd = data;
    *(volatile U32 *)REG_PLL_IDSP_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IDSP_CTRL2_DSMPD] <-- 0x%08x\n",
                        REG_PLL_IDSP_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IDSP_CTRL2_DSMPD(void)
{
    GH_PLL_IDSP_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_IDSP_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IDSP_CTRL2_DSMPD] --> 0x%08x\n",
                        REG_PLL_IDSP_CTRL2,value);
    #endif
    return tmp_value.bitc.dsmpd;
}
GH_INLINE void GH_PLL_set_IDSP_CTRL2_DACPD(U8 data)
{
    GH_PLL_IDSP_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_IDSP_CTRL2;
    d.bitc.dacpd = data;
    *(volatile U32 *)REG_PLL_IDSP_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IDSP_CTRL2_DACPD] <-- 0x%08x\n",
                        REG_PLL_IDSP_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IDSP_CTRL2_DACPD(void)
{
    GH_PLL_IDSP_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_IDSP_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IDSP_CTRL2_DACPD] --> 0x%08x\n",
                        REG_PLL_IDSP_CTRL2,value);
    #endif
    return tmp_value.bitc.dacpd;
}
GH_INLINE void GH_PLL_set_IDSP_CTRL2_PWRDN(U8 data)
{
    GH_PLL_IDSP_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_IDSP_CTRL2;
    d.bitc.pwrdn = data;
    *(volatile U32 *)REG_PLL_IDSP_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IDSP_CTRL2_PWRDN] <-- 0x%08x\n",
                        REG_PLL_IDSP_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IDSP_CTRL2_PWRDN(void)
{
    GH_PLL_IDSP_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_IDSP_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IDSP_CTRL2_PWRDN] --> 0x%08x\n",
                        REG_PLL_IDSP_CTRL2,value);
    #endif
    return tmp_value.bitc.pwrdn;
}
GH_INLINE void GH_PLL_set_IDSP_CTRL2_BYPASS(U8 data)
{
    GH_PLL_IDSP_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_IDSP_CTRL2;
    d.bitc.bypass = data;
    *(volatile U32 *)REG_PLL_IDSP_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IDSP_CTRL2_BYPASS] <-- 0x%08x\n",
                        REG_PLL_IDSP_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IDSP_CTRL2_BYPASS(void)
{
    GH_PLL_IDSP_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_IDSP_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IDSP_CTRL2_BYPASS] --> 0x%08x\n",
                        REG_PLL_IDSP_CTRL2,value);
    #endif
    return tmp_value.bitc.bypass;
}
GH_INLINE void GH_PLL_set_IDSP_CTRL2_LOCK_FORCE(U8 data)
{
    GH_PLL_IDSP_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_IDSP_CTRL2;
    d.bitc.lock_force = data;
    *(volatile U32 *)REG_PLL_IDSP_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IDSP_CTRL2_LOCK_FORCE] <-- 0x%08x\n",
                        REG_PLL_IDSP_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IDSP_CTRL2_LOCK_FORCE(void)
{
    GH_PLL_IDSP_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_IDSP_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IDSP_CTRL2_LOCK_FORCE] --> 0x%08x\n",
                        REG_PLL_IDSP_CTRL2,value);
    #endif
    return tmp_value.bitc.lock_force;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_CORE_CTRL2 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_CORE_CTRL2'. */
void GH_PLL_set_CORE_CTRL2(U32 data);
/*! \brief Reads the register 'PLL_CORE_CTRL2'. */
U32  GH_PLL_get_CORE_CTRL2(void);
/*! \brief Writes the bit group 'FOUTVCOPD' of register 'PLL_CORE_CTRL2'. */
void GH_PLL_set_CORE_CTRL2_FOUTVCOPD(U8 data);
/*! \brief Reads the bit group 'FOUTVCOPD' of register 'PLL_CORE_CTRL2'. */
U8   GH_PLL_get_CORE_CTRL2_FOUTVCOPD(void);
/*! \brief Writes the bit group 'FOUT4PHASEPD' of register 'PLL_CORE_CTRL2'. */
void GH_PLL_set_CORE_CTRL2_FOUT4PHASEPD(U8 data);
/*! \brief Reads the bit group 'FOUT4PHASEPD' of register 'PLL_CORE_CTRL2'. */
U8   GH_PLL_get_CORE_CTRL2_FOUT4PHASEPD(void);
/*! \brief Writes the bit group 'FOUTPOSTDIVPD' of register 'PLL_CORE_CTRL2'. */
void GH_PLL_set_CORE_CTRL2_FOUTPOSTDIVPD(U8 data);
/*! \brief Reads the bit group 'FOUTPOSTDIVPD' of register 'PLL_CORE_CTRL2'. */
U8   GH_PLL_get_CORE_CTRL2_FOUTPOSTDIVPD(void);
/*! \brief Writes the bit group 'DSMPD' of register 'PLL_CORE_CTRL2'. */
void GH_PLL_set_CORE_CTRL2_DSMPD(U8 data);
/*! \brief Reads the bit group 'DSMPD' of register 'PLL_CORE_CTRL2'. */
U8   GH_PLL_get_CORE_CTRL2_DSMPD(void);
/*! \brief Writes the bit group 'DACPD' of register 'PLL_CORE_CTRL2'. */
void GH_PLL_set_CORE_CTRL2_DACPD(U8 data);
/*! \brief Reads the bit group 'DACPD' of register 'PLL_CORE_CTRL2'. */
U8   GH_PLL_get_CORE_CTRL2_DACPD(void);
/*! \brief Writes the bit group 'PWRDN' of register 'PLL_CORE_CTRL2'. */
void GH_PLL_set_CORE_CTRL2_PWRDN(U8 data);
/*! \brief Reads the bit group 'PWRDN' of register 'PLL_CORE_CTRL2'. */
U8   GH_PLL_get_CORE_CTRL2_PWRDN(void);
/*! \brief Writes the bit group 'BYPASS' of register 'PLL_CORE_CTRL2'. */
void GH_PLL_set_CORE_CTRL2_BYPASS(U8 data);
/*! \brief Reads the bit group 'BYPASS' of register 'PLL_CORE_CTRL2'. */
U8   GH_PLL_get_CORE_CTRL2_BYPASS(void);
/*! \brief Writes the bit group 'LOCK_FORCE' of register 'PLL_CORE_CTRL2'. */
void GH_PLL_set_CORE_CTRL2_LOCK_FORCE(U8 data);
/*! \brief Reads the bit group 'LOCK_FORCE' of register 'PLL_CORE_CTRL2'. */
U8   GH_PLL_get_CORE_CTRL2_LOCK_FORCE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_CORE_CTRL2(U32 data)
{
    *(volatile U32 *)REG_PLL_CORE_CTRL2 = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CORE_CTRL2] <-- 0x%08x\n",
                        REG_PLL_CORE_CTRL2,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_CORE_CTRL2(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_CORE_CTRL2);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CORE_CTRL2] --> 0x%08x\n",
                        REG_PLL_CORE_CTRL2,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_CORE_CTRL2_FOUTVCOPD(U8 data)
{
    GH_PLL_CORE_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_CORE_CTRL2;
    d.bitc.foutvcopd = data;
    *(volatile U32 *)REG_PLL_CORE_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CORE_CTRL2_FOUTVCOPD] <-- 0x%08x\n",
                        REG_PLL_CORE_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CORE_CTRL2_FOUTVCOPD(void)
{
    GH_PLL_CORE_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CORE_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CORE_CTRL2_FOUTVCOPD] --> 0x%08x\n",
                        REG_PLL_CORE_CTRL2,value);
    #endif
    return tmp_value.bitc.foutvcopd;
}
GH_INLINE void GH_PLL_set_CORE_CTRL2_FOUT4PHASEPD(U8 data)
{
    GH_PLL_CORE_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_CORE_CTRL2;
    d.bitc.fout4phasepd = data;
    *(volatile U32 *)REG_PLL_CORE_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CORE_CTRL2_FOUT4PHASEPD] <-- 0x%08x\n",
                        REG_PLL_CORE_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CORE_CTRL2_FOUT4PHASEPD(void)
{
    GH_PLL_CORE_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CORE_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CORE_CTRL2_FOUT4PHASEPD] --> 0x%08x\n",
                        REG_PLL_CORE_CTRL2,value);
    #endif
    return tmp_value.bitc.fout4phasepd;
}
GH_INLINE void GH_PLL_set_CORE_CTRL2_FOUTPOSTDIVPD(U8 data)
{
    GH_PLL_CORE_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_CORE_CTRL2;
    d.bitc.foutpostdivpd = data;
    *(volatile U32 *)REG_PLL_CORE_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CORE_CTRL2_FOUTPOSTDIVPD] <-- 0x%08x\n",
                        REG_PLL_CORE_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CORE_CTRL2_FOUTPOSTDIVPD(void)
{
    GH_PLL_CORE_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CORE_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CORE_CTRL2_FOUTPOSTDIVPD] --> 0x%08x\n",
                        REG_PLL_CORE_CTRL2,value);
    #endif
    return tmp_value.bitc.foutpostdivpd;
}
GH_INLINE void GH_PLL_set_CORE_CTRL2_DSMPD(U8 data)
{
    GH_PLL_CORE_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_CORE_CTRL2;
    d.bitc.dsmpd = data;
    *(volatile U32 *)REG_PLL_CORE_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CORE_CTRL2_DSMPD] <-- 0x%08x\n",
                        REG_PLL_CORE_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CORE_CTRL2_DSMPD(void)
{
    GH_PLL_CORE_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CORE_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CORE_CTRL2_DSMPD] --> 0x%08x\n",
                        REG_PLL_CORE_CTRL2,value);
    #endif
    return tmp_value.bitc.dsmpd;
}
GH_INLINE void GH_PLL_set_CORE_CTRL2_DACPD(U8 data)
{
    GH_PLL_CORE_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_CORE_CTRL2;
    d.bitc.dacpd = data;
    *(volatile U32 *)REG_PLL_CORE_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CORE_CTRL2_DACPD] <-- 0x%08x\n",
                        REG_PLL_CORE_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CORE_CTRL2_DACPD(void)
{
    GH_PLL_CORE_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CORE_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CORE_CTRL2_DACPD] --> 0x%08x\n",
                        REG_PLL_CORE_CTRL2,value);
    #endif
    return tmp_value.bitc.dacpd;
}
GH_INLINE void GH_PLL_set_CORE_CTRL2_PWRDN(U8 data)
{
    GH_PLL_CORE_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_CORE_CTRL2;
    d.bitc.pwrdn = data;
    *(volatile U32 *)REG_PLL_CORE_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CORE_CTRL2_PWRDN] <-- 0x%08x\n",
                        REG_PLL_CORE_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CORE_CTRL2_PWRDN(void)
{
    GH_PLL_CORE_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CORE_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CORE_CTRL2_PWRDN] --> 0x%08x\n",
                        REG_PLL_CORE_CTRL2,value);
    #endif
    return tmp_value.bitc.pwrdn;
}
GH_INLINE void GH_PLL_set_CORE_CTRL2_BYPASS(U8 data)
{
    GH_PLL_CORE_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_CORE_CTRL2;
    d.bitc.bypass = data;
    *(volatile U32 *)REG_PLL_CORE_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CORE_CTRL2_BYPASS] <-- 0x%08x\n",
                        REG_PLL_CORE_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CORE_CTRL2_BYPASS(void)
{
    GH_PLL_CORE_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CORE_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CORE_CTRL2_BYPASS] --> 0x%08x\n",
                        REG_PLL_CORE_CTRL2,value);
    #endif
    return tmp_value.bitc.bypass;
}
GH_INLINE void GH_PLL_set_CORE_CTRL2_LOCK_FORCE(U8 data)
{
    GH_PLL_CORE_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_CORE_CTRL2;
    d.bitc.lock_force = data;
    *(volatile U32 *)REG_PLL_CORE_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CORE_CTRL2_LOCK_FORCE] <-- 0x%08x\n",
                        REG_PLL_CORE_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CORE_CTRL2_LOCK_FORCE(void)
{
    GH_PLL_CORE_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CORE_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CORE_CTRL2_LOCK_FORCE] --> 0x%08x\n",
                        REG_PLL_CORE_CTRL2,value);
    #endif
    return tmp_value.bitc.lock_force;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_CORE_POST (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_SCALER_CORE_POST'. */
void GH_PLL_set_SCALER_CORE_POST(U32 data);
/*! \brief Reads the register 'PLL_SCALER_CORE_POST'. */
U32  GH_PLL_get_SCALER_CORE_POST(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_CORE_POST'. */
void GH_PLL_set_SCALER_CORE_POST_Div(U8 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_CORE_POST'. */
U8   GH_PLL_get_SCALER_CORE_POST_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_SCALER_CORE_POST(U32 data)
{
    *(volatile U32 *)REG_PLL_SCALER_CORE_POST = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_CORE_POST] <-- 0x%08x\n",
                        REG_PLL_SCALER_CORE_POST,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_CORE_POST(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_CORE_POST);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_CORE_POST] --> 0x%08x\n",
                        REG_PLL_SCALER_CORE_POST,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_SCALER_CORE_POST_Div(U8 data)
{
    GH_PLL_SCALER_CORE_POST_S d;
    d.all = *(volatile U32 *)REG_PLL_SCALER_CORE_POST;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_SCALER_CORE_POST = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_CORE_POST_Div] <-- 0x%08x\n",
                        REG_PLL_SCALER_CORE_POST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_SCALER_CORE_POST_Div(void)
{
    GH_PLL_SCALER_CORE_POST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_CORE_POST);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_CORE_POST_Div] --> 0x%08x\n",
                        REG_PLL_SCALER_CORE_POST,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_VIDEO_CTRL2 (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_VIDEO_CTRL2'. */
void GH_PLL_set_VIDEO_CTRL2(U32 data);
/*! \brief Reads the register 'PLL_VIDEO_CTRL2'. */
U32  GH_PLL_get_VIDEO_CTRL2(void);
/*! \brief Writes the bit group 'FOUTVCOPD' of register 'PLL_VIDEO_CTRL2'. */
void GH_PLL_set_VIDEO_CTRL2_FOUTVCOPD(U8 data);
/*! \brief Reads the bit group 'FOUTVCOPD' of register 'PLL_VIDEO_CTRL2'. */
U8   GH_PLL_get_VIDEO_CTRL2_FOUTVCOPD(void);
/*! \brief Writes the bit group 'FOUT4PHASEPD' of register 'PLL_VIDEO_CTRL2'. */
void GH_PLL_set_VIDEO_CTRL2_FOUT4PHASEPD(U8 data);
/*! \brief Reads the bit group 'FOUT4PHASEPD' of register 'PLL_VIDEO_CTRL2'. */
U8   GH_PLL_get_VIDEO_CTRL2_FOUT4PHASEPD(void);
/*! \brief Writes the bit group 'FOUTPOSTDIVPD' of register 'PLL_VIDEO_CTRL2'. */
void GH_PLL_set_VIDEO_CTRL2_FOUTPOSTDIVPD(U8 data);
/*! \brief Reads the bit group 'FOUTPOSTDIVPD' of register 'PLL_VIDEO_CTRL2'. */
U8   GH_PLL_get_VIDEO_CTRL2_FOUTPOSTDIVPD(void);
/*! \brief Writes the bit group 'DSMPD' of register 'PLL_VIDEO_CTRL2'. */
void GH_PLL_set_VIDEO_CTRL2_DSMPD(U8 data);
/*! \brief Reads the bit group 'DSMPD' of register 'PLL_VIDEO_CTRL2'. */
U8   GH_PLL_get_VIDEO_CTRL2_DSMPD(void);
/*! \brief Writes the bit group 'DACPD' of register 'PLL_VIDEO_CTRL2'. */
void GH_PLL_set_VIDEO_CTRL2_DACPD(U8 data);
/*! \brief Reads the bit group 'DACPD' of register 'PLL_VIDEO_CTRL2'. */
U8   GH_PLL_get_VIDEO_CTRL2_DACPD(void);
/*! \brief Writes the bit group 'PWRDN' of register 'PLL_VIDEO_CTRL2'. */
void GH_PLL_set_VIDEO_CTRL2_PWRDN(U8 data);
/*! \brief Reads the bit group 'PWRDN' of register 'PLL_VIDEO_CTRL2'. */
U8   GH_PLL_get_VIDEO_CTRL2_PWRDN(void);
/*! \brief Writes the bit group 'BYPASS' of register 'PLL_VIDEO_CTRL2'. */
void GH_PLL_set_VIDEO_CTRL2_BYPASS(U8 data);
/*! \brief Reads the bit group 'BYPASS' of register 'PLL_VIDEO_CTRL2'. */
U8   GH_PLL_get_VIDEO_CTRL2_BYPASS(void);
/*! \brief Writes the bit group 'LOCK_FORCE' of register 'PLL_VIDEO_CTRL2'. */
void GH_PLL_set_VIDEO_CTRL2_LOCK_FORCE(U8 data);
/*! \brief Reads the bit group 'LOCK_FORCE' of register 'PLL_VIDEO_CTRL2'. */
U8   GH_PLL_get_VIDEO_CTRL2_LOCK_FORCE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_VIDEO_CTRL2(U32 data)
{
    *(volatile U32 *)REG_PLL_VIDEO_CTRL2 = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_VIDEO_CTRL2] <-- 0x%08x\n",
                        REG_PLL_VIDEO_CTRL2,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_VIDEO_CTRL2(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_VIDEO_CTRL2);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_VIDEO_CTRL2] --> 0x%08x\n",
                        REG_PLL_VIDEO_CTRL2,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_VIDEO_CTRL2_FOUTVCOPD(U8 data)
{
    GH_PLL_VIDEO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_VIDEO_CTRL2;
    d.bitc.foutvcopd = data;
    *(volatile U32 *)REG_PLL_VIDEO_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_VIDEO_CTRL2_FOUTVCOPD] <-- 0x%08x\n",
                        REG_PLL_VIDEO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_VIDEO_CTRL2_FOUTVCOPD(void)
{
    GH_PLL_VIDEO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_VIDEO_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_VIDEO_CTRL2_FOUTVCOPD] --> 0x%08x\n",
                        REG_PLL_VIDEO_CTRL2,value);
    #endif
    return tmp_value.bitc.foutvcopd;
}
GH_INLINE void GH_PLL_set_VIDEO_CTRL2_FOUT4PHASEPD(U8 data)
{
    GH_PLL_VIDEO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_VIDEO_CTRL2;
    d.bitc.fout4phasepd = data;
    *(volatile U32 *)REG_PLL_VIDEO_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_VIDEO_CTRL2_FOUT4PHASEPD] <-- 0x%08x\n",
                        REG_PLL_VIDEO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_VIDEO_CTRL2_FOUT4PHASEPD(void)
{
    GH_PLL_VIDEO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_VIDEO_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_VIDEO_CTRL2_FOUT4PHASEPD] --> 0x%08x\n",
                        REG_PLL_VIDEO_CTRL2,value);
    #endif
    return tmp_value.bitc.fout4phasepd;
}
GH_INLINE void GH_PLL_set_VIDEO_CTRL2_FOUTPOSTDIVPD(U8 data)
{
    GH_PLL_VIDEO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_VIDEO_CTRL2;
    d.bitc.foutpostdivpd = data;
    *(volatile U32 *)REG_PLL_VIDEO_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_VIDEO_CTRL2_FOUTPOSTDIVPD] <-- 0x%08x\n",
                        REG_PLL_VIDEO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_VIDEO_CTRL2_FOUTPOSTDIVPD(void)
{
    GH_PLL_VIDEO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_VIDEO_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_VIDEO_CTRL2_FOUTPOSTDIVPD] --> 0x%08x\n",
                        REG_PLL_VIDEO_CTRL2,value);
    #endif
    return tmp_value.bitc.foutpostdivpd;
}
GH_INLINE void GH_PLL_set_VIDEO_CTRL2_DSMPD(U8 data)
{
    GH_PLL_VIDEO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_VIDEO_CTRL2;
    d.bitc.dsmpd = data;
    *(volatile U32 *)REG_PLL_VIDEO_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_VIDEO_CTRL2_DSMPD] <-- 0x%08x\n",
                        REG_PLL_VIDEO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_VIDEO_CTRL2_DSMPD(void)
{
    GH_PLL_VIDEO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_VIDEO_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_VIDEO_CTRL2_DSMPD] --> 0x%08x\n",
                        REG_PLL_VIDEO_CTRL2,value);
    #endif
    return tmp_value.bitc.dsmpd;
}
GH_INLINE void GH_PLL_set_VIDEO_CTRL2_DACPD(U8 data)
{
    GH_PLL_VIDEO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_VIDEO_CTRL2;
    d.bitc.dacpd = data;
    *(volatile U32 *)REG_PLL_VIDEO_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_VIDEO_CTRL2_DACPD] <-- 0x%08x\n",
                        REG_PLL_VIDEO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_VIDEO_CTRL2_DACPD(void)
{
    GH_PLL_VIDEO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_VIDEO_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_VIDEO_CTRL2_DACPD] --> 0x%08x\n",
                        REG_PLL_VIDEO_CTRL2,value);
    #endif
    return tmp_value.bitc.dacpd;
}
GH_INLINE void GH_PLL_set_VIDEO_CTRL2_PWRDN(U8 data)
{
    GH_PLL_VIDEO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_VIDEO_CTRL2;
    d.bitc.pwrdn = data;
    *(volatile U32 *)REG_PLL_VIDEO_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_VIDEO_CTRL2_PWRDN] <-- 0x%08x\n",
                        REG_PLL_VIDEO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_VIDEO_CTRL2_PWRDN(void)
{
    GH_PLL_VIDEO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_VIDEO_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_VIDEO_CTRL2_PWRDN] --> 0x%08x\n",
                        REG_PLL_VIDEO_CTRL2,value);
    #endif
    return tmp_value.bitc.pwrdn;
}
GH_INLINE void GH_PLL_set_VIDEO_CTRL2_BYPASS(U8 data)
{
    GH_PLL_VIDEO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_VIDEO_CTRL2;
    d.bitc.bypass = data;
    *(volatile U32 *)REG_PLL_VIDEO_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_VIDEO_CTRL2_BYPASS] <-- 0x%08x\n",
                        REG_PLL_VIDEO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_VIDEO_CTRL2_BYPASS(void)
{
    GH_PLL_VIDEO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_VIDEO_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_VIDEO_CTRL2_BYPASS] --> 0x%08x\n",
                        REG_PLL_VIDEO_CTRL2,value);
    #endif
    return tmp_value.bitc.bypass;
}
GH_INLINE void GH_PLL_set_VIDEO_CTRL2_LOCK_FORCE(U8 data)
{
    GH_PLL_VIDEO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_VIDEO_CTRL2;
    d.bitc.lock_force = data;
    *(volatile U32 *)REG_PLL_VIDEO_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_VIDEO_CTRL2_LOCK_FORCE] <-- 0x%08x\n",
                        REG_PLL_VIDEO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_VIDEO_CTRL2_LOCK_FORCE(void)
{
    GH_PLL_VIDEO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_VIDEO_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_VIDEO_CTRL2_LOCK_FORCE] --> 0x%08x\n",
                        REG_PLL_VIDEO_CTRL2,value);
    #endif
    return tmp_value.bitc.lock_force;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_SENSOR_CTRL2 (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_SENSOR_CTRL2'. */
void GH_PLL_set_SENSOR_CTRL2(U32 data);
/*! \brief Reads the register 'PLL_SENSOR_CTRL2'. */
U32  GH_PLL_get_SENSOR_CTRL2(void);
/*! \brief Writes the bit group 'FOUTVCOPD' of register 'PLL_SENSOR_CTRL2'. */
void GH_PLL_set_SENSOR_CTRL2_FOUTVCOPD(U8 data);
/*! \brief Reads the bit group 'FOUTVCOPD' of register 'PLL_SENSOR_CTRL2'. */
U8   GH_PLL_get_SENSOR_CTRL2_FOUTVCOPD(void);
/*! \brief Writes the bit group 'FOUT4PHASEPD' of register 'PLL_SENSOR_CTRL2'. */
void GH_PLL_set_SENSOR_CTRL2_FOUT4PHASEPD(U8 data);
/*! \brief Reads the bit group 'FOUT4PHASEPD' of register 'PLL_SENSOR_CTRL2'. */
U8   GH_PLL_get_SENSOR_CTRL2_FOUT4PHASEPD(void);
/*! \brief Writes the bit group 'FOUTPOSTDIVPD' of register 'PLL_SENSOR_CTRL2'. */
void GH_PLL_set_SENSOR_CTRL2_FOUTPOSTDIVPD(U8 data);
/*! \brief Reads the bit group 'FOUTPOSTDIVPD' of register 'PLL_SENSOR_CTRL2'. */
U8   GH_PLL_get_SENSOR_CTRL2_FOUTPOSTDIVPD(void);
/*! \brief Writes the bit group 'DSMPD' of register 'PLL_SENSOR_CTRL2'. */
void GH_PLL_set_SENSOR_CTRL2_DSMPD(U8 data);
/*! \brief Reads the bit group 'DSMPD' of register 'PLL_SENSOR_CTRL2'. */
U8   GH_PLL_get_SENSOR_CTRL2_DSMPD(void);
/*! \brief Writes the bit group 'DACPD' of register 'PLL_SENSOR_CTRL2'. */
void GH_PLL_set_SENSOR_CTRL2_DACPD(U8 data);
/*! \brief Reads the bit group 'DACPD' of register 'PLL_SENSOR_CTRL2'. */
U8   GH_PLL_get_SENSOR_CTRL2_DACPD(void);
/*! \brief Writes the bit group 'PWRDN' of register 'PLL_SENSOR_CTRL2'. */
void GH_PLL_set_SENSOR_CTRL2_PWRDN(U8 data);
/*! \brief Reads the bit group 'PWRDN' of register 'PLL_SENSOR_CTRL2'. */
U8   GH_PLL_get_SENSOR_CTRL2_PWRDN(void);
/*! \brief Writes the bit group 'BYPASS' of register 'PLL_SENSOR_CTRL2'. */
void GH_PLL_set_SENSOR_CTRL2_BYPASS(U8 data);
/*! \brief Reads the bit group 'BYPASS' of register 'PLL_SENSOR_CTRL2'. */
U8   GH_PLL_get_SENSOR_CTRL2_BYPASS(void);
/*! \brief Writes the bit group 'LOCK_FORCE' of register 'PLL_SENSOR_CTRL2'. */
void GH_PLL_set_SENSOR_CTRL2_LOCK_FORCE(U8 data);
/*! \brief Reads the bit group 'LOCK_FORCE' of register 'PLL_SENSOR_CTRL2'. */
U8   GH_PLL_get_SENSOR_CTRL2_LOCK_FORCE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_SENSOR_CTRL2(U32 data)
{
    *(volatile U32 *)REG_PLL_SENSOR_CTRL2 = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SENSOR_CTRL2] <-- 0x%08x\n",
                        REG_PLL_SENSOR_CTRL2,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_SENSOR_CTRL2(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_SENSOR_CTRL2);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SENSOR_CTRL2] --> 0x%08x\n",
                        REG_PLL_SENSOR_CTRL2,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_SENSOR_CTRL2_FOUTVCOPD(U8 data)
{
    GH_PLL_SENSOR_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_SENSOR_CTRL2;
    d.bitc.foutvcopd = data;
    *(volatile U32 *)REG_PLL_SENSOR_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SENSOR_CTRL2_FOUTVCOPD] <-- 0x%08x\n",
                        REG_PLL_SENSOR_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_SENSOR_CTRL2_FOUTVCOPD(void)
{
    GH_PLL_SENSOR_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SENSOR_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SENSOR_CTRL2_FOUTVCOPD] --> 0x%08x\n",
                        REG_PLL_SENSOR_CTRL2,value);
    #endif
    return tmp_value.bitc.foutvcopd;
}
GH_INLINE void GH_PLL_set_SENSOR_CTRL2_FOUT4PHASEPD(U8 data)
{
    GH_PLL_SENSOR_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_SENSOR_CTRL2;
    d.bitc.fout4phasepd = data;
    *(volatile U32 *)REG_PLL_SENSOR_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SENSOR_CTRL2_FOUT4PHASEPD] <-- 0x%08x\n",
                        REG_PLL_SENSOR_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_SENSOR_CTRL2_FOUT4PHASEPD(void)
{
    GH_PLL_SENSOR_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SENSOR_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SENSOR_CTRL2_FOUT4PHASEPD] --> 0x%08x\n",
                        REG_PLL_SENSOR_CTRL2,value);
    #endif
    return tmp_value.bitc.fout4phasepd;
}
GH_INLINE void GH_PLL_set_SENSOR_CTRL2_FOUTPOSTDIVPD(U8 data)
{
    GH_PLL_SENSOR_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_SENSOR_CTRL2;
    d.bitc.foutpostdivpd = data;
    *(volatile U32 *)REG_PLL_SENSOR_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SENSOR_CTRL2_FOUTPOSTDIVPD] <-- 0x%08x\n",
                        REG_PLL_SENSOR_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_SENSOR_CTRL2_FOUTPOSTDIVPD(void)
{
    GH_PLL_SENSOR_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SENSOR_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SENSOR_CTRL2_FOUTPOSTDIVPD] --> 0x%08x\n",
                        REG_PLL_SENSOR_CTRL2,value);
    #endif
    return tmp_value.bitc.foutpostdivpd;
}
GH_INLINE void GH_PLL_set_SENSOR_CTRL2_DSMPD(U8 data)
{
    GH_PLL_SENSOR_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_SENSOR_CTRL2;
    d.bitc.dsmpd = data;
    *(volatile U32 *)REG_PLL_SENSOR_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SENSOR_CTRL2_DSMPD] <-- 0x%08x\n",
                        REG_PLL_SENSOR_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_SENSOR_CTRL2_DSMPD(void)
{
    GH_PLL_SENSOR_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SENSOR_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SENSOR_CTRL2_DSMPD] --> 0x%08x\n",
                        REG_PLL_SENSOR_CTRL2,value);
    #endif
    return tmp_value.bitc.dsmpd;
}
GH_INLINE void GH_PLL_set_SENSOR_CTRL2_DACPD(U8 data)
{
    GH_PLL_SENSOR_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_SENSOR_CTRL2;
    d.bitc.dacpd = data;
    *(volatile U32 *)REG_PLL_SENSOR_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SENSOR_CTRL2_DACPD] <-- 0x%08x\n",
                        REG_PLL_SENSOR_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_SENSOR_CTRL2_DACPD(void)
{
    GH_PLL_SENSOR_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SENSOR_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SENSOR_CTRL2_DACPD] --> 0x%08x\n",
                        REG_PLL_SENSOR_CTRL2,value);
    #endif
    return tmp_value.bitc.dacpd;
}
GH_INLINE void GH_PLL_set_SENSOR_CTRL2_PWRDN(U8 data)
{
    GH_PLL_SENSOR_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_SENSOR_CTRL2;
    d.bitc.pwrdn = data;
    *(volatile U32 *)REG_PLL_SENSOR_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SENSOR_CTRL2_PWRDN] <-- 0x%08x\n",
                        REG_PLL_SENSOR_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_SENSOR_CTRL2_PWRDN(void)
{
    GH_PLL_SENSOR_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SENSOR_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SENSOR_CTRL2_PWRDN] --> 0x%08x\n",
                        REG_PLL_SENSOR_CTRL2,value);
    #endif
    return tmp_value.bitc.pwrdn;
}
GH_INLINE void GH_PLL_set_SENSOR_CTRL2_BYPASS(U8 data)
{
    GH_PLL_SENSOR_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_SENSOR_CTRL2;
    d.bitc.bypass = data;
    *(volatile U32 *)REG_PLL_SENSOR_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SENSOR_CTRL2_BYPASS] <-- 0x%08x\n",
                        REG_PLL_SENSOR_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_SENSOR_CTRL2_BYPASS(void)
{
    GH_PLL_SENSOR_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SENSOR_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SENSOR_CTRL2_BYPASS] --> 0x%08x\n",
                        REG_PLL_SENSOR_CTRL2,value);
    #endif
    return tmp_value.bitc.bypass;
}
GH_INLINE void GH_PLL_set_SENSOR_CTRL2_LOCK_FORCE(U8 data)
{
    GH_PLL_SENSOR_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_SENSOR_CTRL2;
    d.bitc.lock_force = data;
    *(volatile U32 *)REG_PLL_SENSOR_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SENSOR_CTRL2_LOCK_FORCE] <-- 0x%08x\n",
                        REG_PLL_SENSOR_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_SENSOR_CTRL2_LOCK_FORCE(void)
{
    GH_PLL_SENSOR_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SENSOR_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SENSOR_CTRL2_LOCK_FORCE] --> 0x%08x\n",
                        REG_PLL_SENSOR_CTRL2,value);
    #endif
    return tmp_value.bitc.lock_force;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_AUDIO_CTRL2 (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_AUDIO_CTRL2'. */
void GH_PLL_set_AUDIO_CTRL2(U32 data);
/*! \brief Reads the register 'PLL_AUDIO_CTRL2'. */
U32  GH_PLL_get_AUDIO_CTRL2(void);
/*! \brief Writes the bit group 'FOUTVCOPD' of register 'PLL_AUDIO_CTRL2'. */
void GH_PLL_set_AUDIO_CTRL2_FOUTVCOPD(U8 data);
/*! \brief Reads the bit group 'FOUTVCOPD' of register 'PLL_AUDIO_CTRL2'. */
U8   GH_PLL_get_AUDIO_CTRL2_FOUTVCOPD(void);
/*! \brief Writes the bit group 'FOUT4PHASEPD' of register 'PLL_AUDIO_CTRL2'. */
void GH_PLL_set_AUDIO_CTRL2_FOUT4PHASEPD(U8 data);
/*! \brief Reads the bit group 'FOUT4PHASEPD' of register 'PLL_AUDIO_CTRL2'. */
U8   GH_PLL_get_AUDIO_CTRL2_FOUT4PHASEPD(void);
/*! \brief Writes the bit group 'FOUTPOSTDIVPD' of register 'PLL_AUDIO_CTRL2'. */
void GH_PLL_set_AUDIO_CTRL2_FOUTPOSTDIVPD(U8 data);
/*! \brief Reads the bit group 'FOUTPOSTDIVPD' of register 'PLL_AUDIO_CTRL2'. */
U8   GH_PLL_get_AUDIO_CTRL2_FOUTPOSTDIVPD(void);
/*! \brief Writes the bit group 'DSMPD' of register 'PLL_AUDIO_CTRL2'. */
void GH_PLL_set_AUDIO_CTRL2_DSMPD(U8 data);
/*! \brief Reads the bit group 'DSMPD' of register 'PLL_AUDIO_CTRL2'. */
U8   GH_PLL_get_AUDIO_CTRL2_DSMPD(void);
/*! \brief Writes the bit group 'DACPD' of register 'PLL_AUDIO_CTRL2'. */
void GH_PLL_set_AUDIO_CTRL2_DACPD(U8 data);
/*! \brief Reads the bit group 'DACPD' of register 'PLL_AUDIO_CTRL2'. */
U8   GH_PLL_get_AUDIO_CTRL2_DACPD(void);
/*! \brief Writes the bit group 'PWRDN' of register 'PLL_AUDIO_CTRL2'. */
void GH_PLL_set_AUDIO_CTRL2_PWRDN(U8 data);
/*! \brief Reads the bit group 'PWRDN' of register 'PLL_AUDIO_CTRL2'. */
U8   GH_PLL_get_AUDIO_CTRL2_PWRDN(void);
/*! \brief Writes the bit group 'BYPASS' of register 'PLL_AUDIO_CTRL2'. */
void GH_PLL_set_AUDIO_CTRL2_BYPASS(U8 data);
/*! \brief Reads the bit group 'BYPASS' of register 'PLL_AUDIO_CTRL2'. */
U8   GH_PLL_get_AUDIO_CTRL2_BYPASS(void);
/*! \brief Writes the bit group 'LOCK_FORCE' of register 'PLL_AUDIO_CTRL2'. */
void GH_PLL_set_AUDIO_CTRL2_LOCK_FORCE(U8 data);
/*! \brief Reads the bit group 'LOCK_FORCE' of register 'PLL_AUDIO_CTRL2'. */
U8   GH_PLL_get_AUDIO_CTRL2_LOCK_FORCE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_AUDIO_CTRL2(U32 data)
{
    *(volatile U32 *)REG_PLL_AUDIO_CTRL2 = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_AUDIO_CTRL2] <-- 0x%08x\n",
                        REG_PLL_AUDIO_CTRL2,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_AUDIO_CTRL2(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_AUDIO_CTRL2);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_AUDIO_CTRL2] --> 0x%08x\n",
                        REG_PLL_AUDIO_CTRL2,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_AUDIO_CTRL2_FOUTVCOPD(U8 data)
{
    GH_PLL_AUDIO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_AUDIO_CTRL2;
    d.bitc.foutvcopd = data;
    *(volatile U32 *)REG_PLL_AUDIO_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_AUDIO_CTRL2_FOUTVCOPD] <-- 0x%08x\n",
                        REG_PLL_AUDIO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_AUDIO_CTRL2_FOUTVCOPD(void)
{
    GH_PLL_AUDIO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_AUDIO_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_AUDIO_CTRL2_FOUTVCOPD] --> 0x%08x\n",
                        REG_PLL_AUDIO_CTRL2,value);
    #endif
    return tmp_value.bitc.foutvcopd;
}
GH_INLINE void GH_PLL_set_AUDIO_CTRL2_FOUT4PHASEPD(U8 data)
{
    GH_PLL_AUDIO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_AUDIO_CTRL2;
    d.bitc.fout4phasepd = data;
    *(volatile U32 *)REG_PLL_AUDIO_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_AUDIO_CTRL2_FOUT4PHASEPD] <-- 0x%08x\n",
                        REG_PLL_AUDIO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_AUDIO_CTRL2_FOUT4PHASEPD(void)
{
    GH_PLL_AUDIO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_AUDIO_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_AUDIO_CTRL2_FOUT4PHASEPD] --> 0x%08x\n",
                        REG_PLL_AUDIO_CTRL2,value);
    #endif
    return tmp_value.bitc.fout4phasepd;
}
GH_INLINE void GH_PLL_set_AUDIO_CTRL2_FOUTPOSTDIVPD(U8 data)
{
    GH_PLL_AUDIO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_AUDIO_CTRL2;
    d.bitc.foutpostdivpd = data;
    *(volatile U32 *)REG_PLL_AUDIO_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_AUDIO_CTRL2_FOUTPOSTDIVPD] <-- 0x%08x\n",
                        REG_PLL_AUDIO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_AUDIO_CTRL2_FOUTPOSTDIVPD(void)
{
    GH_PLL_AUDIO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_AUDIO_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_AUDIO_CTRL2_FOUTPOSTDIVPD] --> 0x%08x\n",
                        REG_PLL_AUDIO_CTRL2,value);
    #endif
    return tmp_value.bitc.foutpostdivpd;
}
GH_INLINE void GH_PLL_set_AUDIO_CTRL2_DSMPD(U8 data)
{
    GH_PLL_AUDIO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_AUDIO_CTRL2;
    d.bitc.dsmpd = data;
    *(volatile U32 *)REG_PLL_AUDIO_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_AUDIO_CTRL2_DSMPD] <-- 0x%08x\n",
                        REG_PLL_AUDIO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_AUDIO_CTRL2_DSMPD(void)
{
    GH_PLL_AUDIO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_AUDIO_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_AUDIO_CTRL2_DSMPD] --> 0x%08x\n",
                        REG_PLL_AUDIO_CTRL2,value);
    #endif
    return tmp_value.bitc.dsmpd;
}
GH_INLINE void GH_PLL_set_AUDIO_CTRL2_DACPD(U8 data)
{
    GH_PLL_AUDIO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_AUDIO_CTRL2;
    d.bitc.dacpd = data;
    *(volatile U32 *)REG_PLL_AUDIO_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_AUDIO_CTRL2_DACPD] <-- 0x%08x\n",
                        REG_PLL_AUDIO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_AUDIO_CTRL2_DACPD(void)
{
    GH_PLL_AUDIO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_AUDIO_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_AUDIO_CTRL2_DACPD] --> 0x%08x\n",
                        REG_PLL_AUDIO_CTRL2,value);
    #endif
    return tmp_value.bitc.dacpd;
}
GH_INLINE void GH_PLL_set_AUDIO_CTRL2_PWRDN(U8 data)
{
    GH_PLL_AUDIO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_AUDIO_CTRL2;
    d.bitc.pwrdn = data;
    *(volatile U32 *)REG_PLL_AUDIO_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_AUDIO_CTRL2_PWRDN] <-- 0x%08x\n",
                        REG_PLL_AUDIO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_AUDIO_CTRL2_PWRDN(void)
{
    GH_PLL_AUDIO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_AUDIO_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_AUDIO_CTRL2_PWRDN] --> 0x%08x\n",
                        REG_PLL_AUDIO_CTRL2,value);
    #endif
    return tmp_value.bitc.pwrdn;
}
GH_INLINE void GH_PLL_set_AUDIO_CTRL2_BYPASS(U8 data)
{
    GH_PLL_AUDIO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_AUDIO_CTRL2;
    d.bitc.bypass = data;
    *(volatile U32 *)REG_PLL_AUDIO_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_AUDIO_CTRL2_BYPASS] <-- 0x%08x\n",
                        REG_PLL_AUDIO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_AUDIO_CTRL2_BYPASS(void)
{
    GH_PLL_AUDIO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_AUDIO_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_AUDIO_CTRL2_BYPASS] --> 0x%08x\n",
                        REG_PLL_AUDIO_CTRL2,value);
    #endif
    return tmp_value.bitc.bypass;
}
GH_INLINE void GH_PLL_set_AUDIO_CTRL2_LOCK_FORCE(U8 data)
{
    GH_PLL_AUDIO_CTRL2_S d;
    d.all = *(volatile U32 *)REG_PLL_AUDIO_CTRL2;
    d.bitc.lock_force = data;
    *(volatile U32 *)REG_PLL_AUDIO_CTRL2 = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_AUDIO_CTRL2_LOCK_FORCE] <-- 0x%08x\n",
                        REG_PLL_AUDIO_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_AUDIO_CTRL2_LOCK_FORCE(void)
{
    GH_PLL_AUDIO_CTRL2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_AUDIO_CTRL2);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_AUDIO_CTRL2_LOCK_FORCE] --> 0x%08x\n",
                        REG_PLL_AUDIO_CTRL2,value);
    #endif
    return tmp_value.bitc.lock_force;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_IOCTRL_JTAG (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_IOCTRL_JTAG'. */
void GH_PLL_set_IOCTRL_JTAG(U32 data);
/*! \brief Reads the register 'PLL_IOCTRL_JTAG'. */
U32  GH_PLL_get_IOCTRL_JTAG(void);
/*! \brief Writes the bit group 'level' of register 'PLL_IOCTRL_JTAG'. */
void GH_PLL_set_IOCTRL_JTAG_level(U8 data);
/*! \brief Reads the bit group 'level' of register 'PLL_IOCTRL_JTAG'. */
U8   GH_PLL_get_IOCTRL_JTAG_level(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_IOCTRL_JTAG(U32 data)
{
    *(volatile U32 *)REG_PLL_IOCTRL_JTAG = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IOCTRL_JTAG] <-- 0x%08x\n",
                        REG_PLL_IOCTRL_JTAG,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_IOCTRL_JTAG(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_IOCTRL_JTAG);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IOCTRL_JTAG] --> 0x%08x\n",
                        REG_PLL_IOCTRL_JTAG,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_IOCTRL_JTAG_level(U8 data)
{
    GH_PLL_IOCTRL_JTAG_S d;
    d.all = *(volatile U32 *)REG_PLL_IOCTRL_JTAG;
    d.bitc.level = data;
    *(volatile U32 *)REG_PLL_IOCTRL_JTAG = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IOCTRL_JTAG_level] <-- 0x%08x\n",
                        REG_PLL_IOCTRL_JTAG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IOCTRL_JTAG_level(void)
{
    GH_PLL_IOCTRL_JTAG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_IOCTRL_JTAG);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IOCTRL_JTAG_level] --> 0x%08x\n",
                        REG_PLL_IOCTRL_JTAG,value);
    #endif
    return tmp_value.bitc.level;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_IOCTRL_SFLASH (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_IOCTRL_SFLASH'. */
void GH_PLL_set_IOCTRL_SFLASH(U32 data);
/*! \brief Reads the register 'PLL_IOCTRL_SFLASH'. */
U32  GH_PLL_get_IOCTRL_SFLASH(void);
/*! \brief Writes the bit group 'level' of register 'PLL_IOCTRL_SFLASH'. */
void GH_PLL_set_IOCTRL_SFLASH_level(U8 data);
/*! \brief Reads the bit group 'level' of register 'PLL_IOCTRL_SFLASH'. */
U8   GH_PLL_get_IOCTRL_SFLASH_level(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_IOCTRL_SFLASH(U32 data)
{
    *(volatile U32 *)REG_PLL_IOCTRL_SFLASH = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IOCTRL_SFLASH] <-- 0x%08x\n",
                        REG_PLL_IOCTRL_SFLASH,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_IOCTRL_SFLASH(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_IOCTRL_SFLASH);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IOCTRL_SFLASH] --> 0x%08x\n",
                        REG_PLL_IOCTRL_SFLASH,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_IOCTRL_SFLASH_level(U8 data)
{
    GH_PLL_IOCTRL_SFLASH_S d;
    d.all = *(volatile U32 *)REG_PLL_IOCTRL_SFLASH;
    d.bitc.level = data;
    *(volatile U32 *)REG_PLL_IOCTRL_SFLASH = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IOCTRL_SFLASH_level] <-- 0x%08x\n",
                        REG_PLL_IOCTRL_SFLASH,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IOCTRL_SFLASH_level(void)
{
    GH_PLL_IOCTRL_SFLASH_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_IOCTRL_SFLASH);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IOCTRL_SFLASH_level] --> 0x%08x\n",
                        REG_PLL_IOCTRL_SFLASH,value);
    #endif
    return tmp_value.bitc.level;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_IOCTRL_SENSOR (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_IOCTRL_SENSOR'. */
void GH_PLL_set_IOCTRL_SENSOR(U32 data);
/*! \brief Reads the register 'PLL_IOCTRL_SENSOR'. */
U32  GH_PLL_get_IOCTRL_SENSOR(void);
/*! \brief Writes the bit group 'level' of register 'PLL_IOCTRL_SENSOR'. */
void GH_PLL_set_IOCTRL_SENSOR_level(U8 data);
/*! \brief Reads the bit group 'level' of register 'PLL_IOCTRL_SENSOR'. */
U8   GH_PLL_get_IOCTRL_SENSOR_level(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_IOCTRL_SENSOR(U32 data)
{
    *(volatile U32 *)REG_PLL_IOCTRL_SENSOR = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IOCTRL_SENSOR] <-- 0x%08x\n",
                        REG_PLL_IOCTRL_SENSOR,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_IOCTRL_SENSOR(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_IOCTRL_SENSOR);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IOCTRL_SENSOR] --> 0x%08x\n",
                        REG_PLL_IOCTRL_SENSOR,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_IOCTRL_SENSOR_level(U8 data)
{
    GH_PLL_IOCTRL_SENSOR_S d;
    d.all = *(volatile U32 *)REG_PLL_IOCTRL_SENSOR;
    d.bitc.level = data;
    *(volatile U32 *)REG_PLL_IOCTRL_SENSOR = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IOCTRL_SENSOR_level] <-- 0x%08x\n",
                        REG_PLL_IOCTRL_SENSOR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IOCTRL_SENSOR_level(void)
{
    GH_PLL_IOCTRL_SENSOR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_IOCTRL_SENSOR);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IOCTRL_SENSOR_level] --> 0x%08x\n",
                        REG_PLL_IOCTRL_SENSOR,value);
    #endif
    return tmp_value.bitc.level;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_CLOCK_VO (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_CLOCK_VO'. */
void GH_PLL_set_CLOCK_VO(U32 data);
/*! \brief Reads the register 'PLL_CLOCK_VO'. */
U32  GH_PLL_get_CLOCK_VO(void);
/*! \brief Writes the bit group 'clk_voa_common_vob' of register 'PLL_CLOCK_VO'. */
void GH_PLL_set_CLOCK_VO_clk_voa_common_vob(U8 data);
/*! \brief Reads the bit group 'clk_voa_common_vob' of register 'PLL_CLOCK_VO'. */
U8   GH_PLL_get_CLOCK_VO_clk_voa_common_vob(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_CLOCK_VO(U32 data)
{
    *(volatile U32 *)REG_PLL_CLOCK_VO = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CLOCK_VO] <-- 0x%08x\n",
                        REG_PLL_CLOCK_VO,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_CLOCK_VO(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_CLOCK_VO);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CLOCK_VO] --> 0x%08x\n",
                        REG_PLL_CLOCK_VO,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_CLOCK_VO_clk_voa_common_vob(U8 data)
{
    GH_PLL_CLOCK_VO_S d;
    d.all = *(volatile U32 *)REG_PLL_CLOCK_VO;
    d.bitc.clk_voa_common_vob = data;
    *(volatile U32 *)REG_PLL_CLOCK_VO = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CLOCK_VO_clk_voa_common_vob] <-- 0x%08x\n",
                        REG_PLL_CLOCK_VO,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CLOCK_VO_clk_voa_common_vob(void)
{
    GH_PLL_CLOCK_VO_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CLOCK_VO);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CLOCK_VO_clk_voa_common_vob] --> 0x%08x\n",
                        REG_PLL_CLOCK_VO,value);
    #endif
    return tmp_value.bitc.clk_voa_common_vob;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_CLOCK_OBSV (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_CLOCK_OBSV'. */
void GH_PLL_set_CLOCK_OBSV(U32 data);
/*! \brief Reads the register 'PLL_CLOCK_OBSV'. */
U32  GH_PLL_get_CLOCK_OBSV(void);
/*! \brief Writes the bit group 'en' of register 'PLL_CLOCK_OBSV'. */
void GH_PLL_set_CLOCK_OBSV_en(U8 data);
/*! \brief Reads the bit group 'en' of register 'PLL_CLOCK_OBSV'. */
U8   GH_PLL_get_CLOCK_OBSV_en(void);
/*! \brief Writes the bit group 'pll' of register 'PLL_CLOCK_OBSV'. */
void GH_PLL_set_CLOCK_OBSV_pll(U8 data);
/*! \brief Reads the bit group 'pll' of register 'PLL_CLOCK_OBSV'. */
U8   GH_PLL_get_CLOCK_OBSV_pll(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_CLOCK_OBSV(U32 data)
{
    *(volatile U32 *)REG_PLL_CLOCK_OBSV = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CLOCK_OBSV] <-- 0x%08x\n",
                        REG_PLL_CLOCK_OBSV,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_CLOCK_OBSV(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_CLOCK_OBSV);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CLOCK_OBSV] --> 0x%08x\n",
                        REG_PLL_CLOCK_OBSV,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_CLOCK_OBSV_en(U8 data)
{
    GH_PLL_CLOCK_OBSV_S d;
    d.all = *(volatile U32 *)REG_PLL_CLOCK_OBSV;
    d.bitc.en = data;
    *(volatile U32 *)REG_PLL_CLOCK_OBSV = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CLOCK_OBSV_en] <-- 0x%08x\n",
                        REG_PLL_CLOCK_OBSV,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CLOCK_OBSV_en(void)
{
    GH_PLL_CLOCK_OBSV_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CLOCK_OBSV);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CLOCK_OBSV_en] --> 0x%08x\n",
                        REG_PLL_CLOCK_OBSV,value);
    #endif
    return tmp_value.bitc.en;
}
GH_INLINE void GH_PLL_set_CLOCK_OBSV_pll(U8 data)
{
    GH_PLL_CLOCK_OBSV_S d;
    d.all = *(volatile U32 *)REG_PLL_CLOCK_OBSV;
    d.bitc.pll = data;
    *(volatile U32 *)REG_PLL_CLOCK_OBSV = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CLOCK_OBSV_pll] <-- 0x%08x\n",
                        REG_PLL_CLOCK_OBSV,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CLOCK_OBSV_pll(void)
{
    GH_PLL_CLOCK_OBSV_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CLOCK_OBSV);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CLOCK_OBSV_pll] --> 0x%08x\n",
                        REG_PLL_CLOCK_OBSV,value);
    #endif
    return tmp_value.bitc.pll;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_IDSP_POST (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_SCALER_IDSP_POST'. */
void GH_PLL_set_SCALER_IDSP_POST(U32 data);
/*! \brief Reads the register 'PLL_SCALER_IDSP_POST'. */
U32  GH_PLL_get_SCALER_IDSP_POST(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_IDSP_POST'. */
void GH_PLL_set_SCALER_IDSP_POST_Div(U8 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_IDSP_POST'. */
U8   GH_PLL_get_SCALER_IDSP_POST_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_SCALER_IDSP_POST(U32 data)
{
    *(volatile U32 *)REG_PLL_SCALER_IDSP_POST = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_IDSP_POST] <-- 0x%08x\n",
                        REG_PLL_SCALER_IDSP_POST,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_IDSP_POST(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_IDSP_POST);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_IDSP_POST] --> 0x%08x\n",
                        REG_PLL_SCALER_IDSP_POST,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_SCALER_IDSP_POST_Div(U8 data)
{
    GH_PLL_SCALER_IDSP_POST_S d;
    d.all = *(volatile U32 *)REG_PLL_SCALER_IDSP_POST;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_SCALER_IDSP_POST = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_IDSP_POST_Div] <-- 0x%08x\n",
                        REG_PLL_SCALER_IDSP_POST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_SCALER_IDSP_POST_Div(void)
{
    GH_PLL_SCALER_IDSP_POST_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_IDSP_POST);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_IDSP_POST_Div] --> 0x%08x\n",
                        REG_PLL_SCALER_IDSP_POST,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_GENERAL_CONFIG (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_GENERAL_CONFIG'. */
void GH_PLL_set_GENERAL_CONFIG(U32 data);
/*! \brief Reads the register 'PLL_GENERAL_CONFIG'. */
U32  GH_PLL_get_GENERAL_CONFIG(void);
/*! \brief Writes the bit group 'sdata_width' of register 'PLL_GENERAL_CONFIG'. */
void GH_PLL_set_GENERAL_CONFIG_sdata_width(U8 data);
/*! \brief Reads the bit group 'sdata_width' of register 'PLL_GENERAL_CONFIG'. */
U8   GH_PLL_get_GENERAL_CONFIG_sdata_width(void);
/*! \brief Writes the bit group 'bt1120_in' of register 'PLL_GENERAL_CONFIG'. */
void GH_PLL_set_GENERAL_CONFIG_bt1120_in(U8 data);
/*! \brief Reads the bit group 'bt1120_in' of register 'PLL_GENERAL_CONFIG'. */
U8   GH_PLL_get_GENERAL_CONFIG_bt1120_in(void);
/*! \brief Writes the bit group 'bt1120_out' of register 'PLL_GENERAL_CONFIG'. */
void GH_PLL_set_GENERAL_CONFIG_bt1120_out(U8 data);
/*! \brief Reads the bit group 'bt1120_out' of register 'PLL_GENERAL_CONFIG'. */
U8   GH_PLL_get_GENERAL_CONFIG_bt1120_out(void);
/*! \brief Writes the bit group 'sdata_swap' of register 'PLL_GENERAL_CONFIG'. */
void GH_PLL_set_GENERAL_CONFIG_sdata_swap(U8 data);
/*! \brief Reads the bit group 'sdata_swap' of register 'PLL_GENERAL_CONFIG'. */
U8   GH_PLL_get_GENERAL_CONFIG_sdata_swap(void);
/*! \brief Writes the bit group 'spclk_sel' of register 'PLL_GENERAL_CONFIG'. */
void GH_PLL_set_GENERAL_CONFIG_spclk_sel(U8 data);
/*! \brief Reads the bit group 'spclk_sel' of register 'PLL_GENERAL_CONFIG'. */
U8   GH_PLL_get_GENERAL_CONFIG_spclk_sel(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_GENERAL_CONFIG(U32 data)
{
    *(volatile U32 *)REG_PLL_GENERAL_CONFIG = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_GENERAL_CONFIG] <-- 0x%08x\n",
                        REG_PLL_GENERAL_CONFIG,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_GENERAL_CONFIG(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_GENERAL_CONFIG);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_GENERAL_CONFIG] --> 0x%08x\n",
                        REG_PLL_GENERAL_CONFIG,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_GENERAL_CONFIG_sdata_width(U8 data)
{
    GH_PLL_GENERAL_CONFIG_S d;
    d.all = *(volatile U32 *)REG_PLL_GENERAL_CONFIG;
    d.bitc.sdata_width = data;
    *(volatile U32 *)REG_PLL_GENERAL_CONFIG = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_GENERAL_CONFIG_sdata_width] <-- 0x%08x\n",
                        REG_PLL_GENERAL_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_GENERAL_CONFIG_sdata_width(void)
{
    GH_PLL_GENERAL_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_GENERAL_CONFIG);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_GENERAL_CONFIG_sdata_width] --> 0x%08x\n",
                        REG_PLL_GENERAL_CONFIG,value);
    #endif
    return tmp_value.bitc.sdata_width;
}
GH_INLINE void GH_PLL_set_GENERAL_CONFIG_bt1120_in(U8 data)
{
    GH_PLL_GENERAL_CONFIG_S d;
    d.all = *(volatile U32 *)REG_PLL_GENERAL_CONFIG;
    d.bitc.bt1120_in = data;
    *(volatile U32 *)REG_PLL_GENERAL_CONFIG = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_GENERAL_CONFIG_bt1120_in] <-- 0x%08x\n",
                        REG_PLL_GENERAL_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_GENERAL_CONFIG_bt1120_in(void)
{
    GH_PLL_GENERAL_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_GENERAL_CONFIG);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_GENERAL_CONFIG_bt1120_in] --> 0x%08x\n",
                        REG_PLL_GENERAL_CONFIG,value);
    #endif
    return tmp_value.bitc.bt1120_in;
}
GH_INLINE void GH_PLL_set_GENERAL_CONFIG_bt1120_out(U8 data)
{
    GH_PLL_GENERAL_CONFIG_S d;
    d.all = *(volatile U32 *)REG_PLL_GENERAL_CONFIG;
    d.bitc.bt1120_out = data;
    *(volatile U32 *)REG_PLL_GENERAL_CONFIG = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_GENERAL_CONFIG_bt1120_out] <-- 0x%08x\n",
                        REG_PLL_GENERAL_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_GENERAL_CONFIG_bt1120_out(void)
{
    GH_PLL_GENERAL_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_GENERAL_CONFIG);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_GENERAL_CONFIG_bt1120_out] --> 0x%08x\n",
                        REG_PLL_GENERAL_CONFIG,value);
    #endif
    return tmp_value.bitc.bt1120_out;
}
GH_INLINE void GH_PLL_set_GENERAL_CONFIG_sdata_swap(U8 data)
{
    GH_PLL_GENERAL_CONFIG_S d;
    d.all = *(volatile U32 *)REG_PLL_GENERAL_CONFIG;
    d.bitc.sdata_swap = data;
    *(volatile U32 *)REG_PLL_GENERAL_CONFIG = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_GENERAL_CONFIG_sdata_swap] <-- 0x%08x\n",
                        REG_PLL_GENERAL_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_GENERAL_CONFIG_sdata_swap(void)
{
    GH_PLL_GENERAL_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_GENERAL_CONFIG);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_GENERAL_CONFIG_sdata_swap] --> 0x%08x\n",
                        REG_PLL_GENERAL_CONFIG,value);
    #endif
    return tmp_value.bitc.sdata_swap;
}
GH_INLINE void GH_PLL_set_GENERAL_CONFIG_spclk_sel(U8 data)
{
    GH_PLL_GENERAL_CONFIG_S d;
    d.all = *(volatile U32 *)REG_PLL_GENERAL_CONFIG;
    d.bitc.spclk_sel = data;
    *(volatile U32 *)REG_PLL_GENERAL_CONFIG = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_GENERAL_CONFIG_spclk_sel] <-- 0x%08x\n",
                        REG_PLL_GENERAL_CONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_GENERAL_CONFIG_spclk_sel(void)
{
    GH_PLL_GENERAL_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_GENERAL_CONFIG);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_GENERAL_CONFIG_spclk_sel] --> 0x%08x\n",
                        REG_PLL_GENERAL_CONFIG,value);
    #endif
    return tmp_value.bitc.spclk_sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_CLK_REF_SSI (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_CLK_REF_SSI'. */
void GH_PLL_set_CLK_REF_SSI(U32 data);
/*! \brief Reads the register 'PLL_CLK_REF_SSI'. */
U32  GH_PLL_get_CLK_REF_SSI(void);
/*! \brief Writes the bit group 'clk' of register 'PLL_CLK_REF_SSI'. */
void GH_PLL_set_CLK_REF_SSI_clk(U8 data);
/*! \brief Reads the bit group 'clk' of register 'PLL_CLK_REF_SSI'. */
U8   GH_PLL_get_CLK_REF_SSI_clk(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_CLK_REF_SSI(U32 data)
{
    *(volatile U32 *)REG_PLL_CLK_REF_SSI = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CLK_REF_SSI] <-- 0x%08x\n",
                        REG_PLL_CLK_REF_SSI,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_CLK_REF_SSI(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_CLK_REF_SSI);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CLK_REF_SSI] --> 0x%08x\n",
                        REG_PLL_CLK_REF_SSI,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_CLK_REF_SSI_clk(U8 data)
{
    GH_PLL_CLK_REF_SSI_S d;
    d.all = *(volatile U32 *)REG_PLL_CLK_REF_SSI;
    d.bitc.clk = data;
    *(volatile U32 *)REG_PLL_CLK_REF_SSI = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CLK_REF_SSI_clk] <-- 0x%08x\n",
                        REG_PLL_CLK_REF_SSI,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CLK_REF_SSI_clk(void)
{
    GH_PLL_CLK_REF_SSI_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CLK_REF_SSI);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CLK_REF_SSI_clk] --> 0x%08x\n",
                        REG_PLL_CLK_REF_SSI,value);
    #endif
    return tmp_value.bitc.clk;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_DDRC_IDSP_RESET (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
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
/*! \brief Writes the bit group 'nr3d' of register 'PLL_DDRC_IDSP_RESET'. */
void GH_PLL_set_DDRC_IDSP_RESET_nr3d(U8 data);
/*! \brief Reads the bit group 'nr3d' of register 'PLL_DDRC_IDSP_RESET'. */
U8   GH_PLL_get_DDRC_IDSP_RESET_nr3d(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_DDRC_IDSP_RESET(U32 data)
{
    *(volatile U32 *)REG_PLL_DDRC_IDSP_RESET = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_DDRC_IDSP_RESET] <-- 0x%08x\n",
                        REG_PLL_DDRC_IDSP_RESET,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_DDRC_IDSP_RESET(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_DDRC_IDSP_RESET);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_DDRC_IDSP_RESET] --> 0x%08x\n",
                        REG_PLL_DDRC_IDSP_RESET,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_DDRC_IDSP_RESET_ddrc(U8 data)
{
    GH_PLL_DDRC_IDSP_RESET_S d;
    d.all = *(volatile U32 *)REG_PLL_DDRC_IDSP_RESET;
    d.bitc.ddrc = data;
    *(volatile U32 *)REG_PLL_DDRC_IDSP_RESET = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_DDRC_IDSP_RESET_ddrc] <-- 0x%08x\n",
                        REG_PLL_DDRC_IDSP_RESET,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_DDRC_IDSP_RESET_ddrc(void)
{
    GH_PLL_DDRC_IDSP_RESET_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_DDRC_IDSP_RESET);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_DDRC_IDSP_RESET_ddrc] --> 0x%08x\n",
                        REG_PLL_DDRC_IDSP_RESET,value);
    #endif
    return tmp_value.bitc.ddrc;
}
GH_INLINE void GH_PLL_set_DDRC_IDSP_RESET_idsp(U8 data)
{
    GH_PLL_DDRC_IDSP_RESET_S d;
    d.all = *(volatile U32 *)REG_PLL_DDRC_IDSP_RESET;
    d.bitc.idsp = data;
    *(volatile U32 *)REG_PLL_DDRC_IDSP_RESET = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_DDRC_IDSP_RESET_idsp] <-- 0x%08x\n",
                        REG_PLL_DDRC_IDSP_RESET,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_DDRC_IDSP_RESET_idsp(void)
{
    GH_PLL_DDRC_IDSP_RESET_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_DDRC_IDSP_RESET);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_DDRC_IDSP_RESET_idsp] --> 0x%08x\n",
                        REG_PLL_DDRC_IDSP_RESET,value);
    #endif
    return tmp_value.bitc.idsp;
}
GH_INLINE void GH_PLL_set_DDRC_IDSP_RESET_nr3d(U8 data)
{
    GH_PLL_DDRC_IDSP_RESET_S d;
    d.all = *(volatile U32 *)REG_PLL_DDRC_IDSP_RESET;
    d.bitc.nr3d = data;
    *(volatile U32 *)REG_PLL_DDRC_IDSP_RESET = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_DDRC_IDSP_RESET_nr3d] <-- 0x%08x\n",
                        REG_PLL_DDRC_IDSP_RESET,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_DDRC_IDSP_RESET_nr3d(void)
{
    GH_PLL_DDRC_IDSP_RESET_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_DDRC_IDSP_RESET);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_DDRC_IDSP_RESET_nr3d] --> 0x%08x\n",
                        REG_PLL_DDRC_IDSP_RESET,value);
    #endif
    return tmp_value.bitc.nr3d;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_IOCTRL_GPIO (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_IOCTRL_GPIO'. */
void GH_PLL_set_IOCTRL_GPIO(U8 index, U32 data);
/*! \brief Reads the register 'PLL_IOCTRL_GPIO'. */
U32  GH_PLL_get_IOCTRL_GPIO(U8 index);
/*! \brief Writes the bit group 'io1' of register 'PLL_IOCTRL_GPIO'. */
void GH_PLL_set_IOCTRL_GPIO_io1(U8 index, U8 data);
/*! \brief Reads the bit group 'io1' of register 'PLL_IOCTRL_GPIO'. */
U8   GH_PLL_get_IOCTRL_GPIO_io1(U8 index);
/*! \brief Writes the bit group 'io0' of register 'PLL_IOCTRL_GPIO'. */
void GH_PLL_set_IOCTRL_GPIO_io0(U8 index, U8 data);
/*! \brief Reads the bit group 'io0' of register 'PLL_IOCTRL_GPIO'. */
U8   GH_PLL_get_IOCTRL_GPIO_io0(U8 index);
/*! \brief Writes the bit group 'io2' of register 'PLL_IOCTRL_GPIO'. */
void GH_PLL_set_IOCTRL_GPIO_io2(U8 index, U8 data);
/*! \brief Reads the bit group 'io2' of register 'PLL_IOCTRL_GPIO'. */
U8   GH_PLL_get_IOCTRL_GPIO_io2(U8 index);
/*! \brief Writes the bit group 'io3' of register 'PLL_IOCTRL_GPIO'. */
void GH_PLL_set_IOCTRL_GPIO_io3(U8 index, U8 data);
/*! \brief Reads the bit group 'io3' of register 'PLL_IOCTRL_GPIO'. */
U8   GH_PLL_get_IOCTRL_GPIO_io3(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_IOCTRL_GPIO(U8 index, U32 data)
{
    *(volatile U32 *)(REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)) = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IOCTRL_GPIO] <-- 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)),data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_IOCTRL_GPIO(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)));

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IOCTRL_GPIO] --> 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)),value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_IOCTRL_GPIO_io1(U8 index, U8 data)
{
    GH_PLL_IOCTRL_GPIO_S d;
    d.all = *(volatile U32 *)(REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004));
    d.bitc.io1 = data;
    *(volatile U32 *)(REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)) = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IOCTRL_GPIO_io1] <-- 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IOCTRL_GPIO_io1(U8 index)
{
    GH_PLL_IOCTRL_GPIO_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)));

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IOCTRL_GPIO_io1] --> 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)),value);
    #endif
    return tmp_value.bitc.io1;
}
GH_INLINE void GH_PLL_set_IOCTRL_GPIO_io0(U8 index, U8 data)
{
    GH_PLL_IOCTRL_GPIO_S d;
    d.all = *(volatile U32 *)(REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004));
    d.bitc.io0 = data;
    *(volatile U32 *)(REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)) = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IOCTRL_GPIO_io0] <-- 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IOCTRL_GPIO_io0(U8 index)
{
    GH_PLL_IOCTRL_GPIO_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)));

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IOCTRL_GPIO_io0] --> 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)),value);
    #endif
    return tmp_value.bitc.io0;
}
GH_INLINE void GH_PLL_set_IOCTRL_GPIO_io2(U8 index, U8 data)
{
    GH_PLL_IOCTRL_GPIO_S d;
    d.all = *(volatile U32 *)(REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004));
    d.bitc.io2 = data;
    *(volatile U32 *)(REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)) = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IOCTRL_GPIO_io2] <-- 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IOCTRL_GPIO_io2(U8 index)
{
    GH_PLL_IOCTRL_GPIO_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)));

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IOCTRL_GPIO_io2] --> 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)),value);
    #endif
    return tmp_value.bitc.io2;
}
GH_INLINE void GH_PLL_set_IOCTRL_GPIO_io3(U8 index, U8 data)
{
    GH_PLL_IOCTRL_GPIO_S d;
    d.all = *(volatile U32 *)(REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004));
    d.bitc.io3 = data;
    *(volatile U32 *)(REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)) = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IOCTRL_GPIO_io3] <-- 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IOCTRL_GPIO_io3(U8 index)
{
    GH_PLL_IOCTRL_GPIO_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)));

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IOCTRL_GPIO_io3] --> 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO + index * FIO_MOFFSET(PLL,0x00000004)),value);
    #endif
    return tmp_value.bitc.io3;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_IOCTRL_GPIO56 (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_IOCTRL_GPIO56'. */
void GH_PLL_set_IOCTRL_GPIO56(U8 index, U32 data);
/*! \brief Reads the register 'PLL_IOCTRL_GPIO56'. */
U32  GH_PLL_get_IOCTRL_GPIO56(U8 index);
/*! \brief Writes the bit group 'io0' of register 'PLL_IOCTRL_GPIO56'. */
void GH_PLL_set_IOCTRL_GPIO56_io0(U8 index, U8 data);
/*! \brief Reads the bit group 'io0' of register 'PLL_IOCTRL_GPIO56'. */
U8   GH_PLL_get_IOCTRL_GPIO56_io0(U8 index);
/*! \brief Writes the bit group 'io1' of register 'PLL_IOCTRL_GPIO56'. */
void GH_PLL_set_IOCTRL_GPIO56_io1(U8 index, U8 data);
/*! \brief Reads the bit group 'io1' of register 'PLL_IOCTRL_GPIO56'. */
U8   GH_PLL_get_IOCTRL_GPIO56_io1(U8 index);
/*! \brief Writes the bit group 'io2' of register 'PLL_IOCTRL_GPIO56'. */
void GH_PLL_set_IOCTRL_GPIO56_io2(U8 index, U8 data);
/*! \brief Reads the bit group 'io2' of register 'PLL_IOCTRL_GPIO56'. */
U8   GH_PLL_get_IOCTRL_GPIO56_io2(U8 index);
/*! \brief Writes the bit group 'io3' of register 'PLL_IOCTRL_GPIO56'. */
void GH_PLL_set_IOCTRL_GPIO56_io3(U8 index, U8 data);
/*! \brief Reads the bit group 'io3' of register 'PLL_IOCTRL_GPIO56'. */
U8   GH_PLL_get_IOCTRL_GPIO56_io3(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_IOCTRL_GPIO56(U8 index, U32 data)
{
    *(volatile U32 *)(REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)) = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IOCTRL_GPIO56] <-- 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)),data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_IOCTRL_GPIO56(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)));

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IOCTRL_GPIO56] --> 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)),value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_IOCTRL_GPIO56_io0(U8 index, U8 data)
{
    GH_PLL_IOCTRL_GPIO56_S d;
    d.all = *(volatile U32 *)(REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004));
    d.bitc.io0 = data;
    *(volatile U32 *)(REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)) = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IOCTRL_GPIO56_io0] <-- 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IOCTRL_GPIO56_io0(U8 index)
{
    GH_PLL_IOCTRL_GPIO56_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)));

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IOCTRL_GPIO56_io0] --> 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)),value);
    #endif
    return tmp_value.bitc.io0;
}
GH_INLINE void GH_PLL_set_IOCTRL_GPIO56_io1(U8 index, U8 data)
{
    GH_PLL_IOCTRL_GPIO56_S d;
    d.all = *(volatile U32 *)(REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004));
    d.bitc.io1 = data;
    *(volatile U32 *)(REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)) = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IOCTRL_GPIO56_io1] <-- 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IOCTRL_GPIO56_io1(U8 index)
{
    GH_PLL_IOCTRL_GPIO56_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)));

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IOCTRL_GPIO56_io1] --> 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)),value);
    #endif
    return tmp_value.bitc.io1;
}
GH_INLINE void GH_PLL_set_IOCTRL_GPIO56_io2(U8 index, U8 data)
{
    GH_PLL_IOCTRL_GPIO56_S d;
    d.all = *(volatile U32 *)(REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004));
    d.bitc.io2 = data;
    *(volatile U32 *)(REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)) = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IOCTRL_GPIO56_io2] <-- 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IOCTRL_GPIO56_io2(U8 index)
{
    GH_PLL_IOCTRL_GPIO56_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)));

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IOCTRL_GPIO56_io2] --> 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)),value);
    #endif
    return tmp_value.bitc.io2;
}
GH_INLINE void GH_PLL_set_IOCTRL_GPIO56_io3(U8 index, U8 data)
{
    GH_PLL_IOCTRL_GPIO56_S d;
    d.all = *(volatile U32 *)(REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004));
    d.bitc.io3 = data;
    *(volatile U32 *)(REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)) = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IOCTRL_GPIO56_io3] <-- 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IOCTRL_GPIO56_io3(U8 index)
{
    GH_PLL_IOCTRL_GPIO56_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)));

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IOCTRL_GPIO56_io3] --> 0x%08x\n",
                        (REG_PLL_IOCTRL_GPIO56 + index * FIO_MOFFSET(PLL,0x00000004)),value);
    #endif
    return tmp_value.bitc.io3;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_IOCTRL_XCLK (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_IOCTRL_XCLK'. */
void GH_PLL_set_IOCTRL_XCLK(U32 data);
/*! \brief Reads the register 'PLL_IOCTRL_XCLK'. */
U32  GH_PLL_get_IOCTRL_XCLK(void);
/*! \brief Writes the bit group 'bypass' of register 'PLL_IOCTRL_XCLK'. */
void GH_PLL_set_IOCTRL_XCLK_bypass(U8 data);
/*! \brief Reads the bit group 'bypass' of register 'PLL_IOCTRL_XCLK'. */
U8   GH_PLL_get_IOCTRL_XCLK_bypass(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_IOCTRL_XCLK(U32 data)
{
    *(volatile U32 *)REG_PLL_IOCTRL_XCLK = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IOCTRL_XCLK] <-- 0x%08x\n",
                        REG_PLL_IOCTRL_XCLK,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_IOCTRL_XCLK(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_IOCTRL_XCLK);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IOCTRL_XCLK] --> 0x%08x\n",
                        REG_PLL_IOCTRL_XCLK,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_IOCTRL_XCLK_bypass(U8 data)
{
    GH_PLL_IOCTRL_XCLK_S d;
    d.all = *(volatile U32 *)REG_PLL_IOCTRL_XCLK;
    d.bitc.bypass = data;
    *(volatile U32 *)REG_PLL_IOCTRL_XCLK = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_IOCTRL_XCLK_bypass] <-- 0x%08x\n",
                        REG_PLL_IOCTRL_XCLK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_IOCTRL_XCLK_bypass(void)
{
    GH_PLL_IOCTRL_XCLK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_IOCTRL_XCLK);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_IOCTRL_XCLK_bypass] --> 0x%08x\n",
                        REG_PLL_IOCTRL_XCLK,value);
    #endif
    return tmp_value.bitc.bypass;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_DDR_CALIB (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_SCALER_DDR_CALIB'. */
void GH_PLL_set_SCALER_DDR_CALIB(U32 data);
/*! \brief Reads the register 'PLL_SCALER_DDR_CALIB'. */
U32  GH_PLL_get_SCALER_DDR_CALIB(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_DDR_CALIB'. */
void GH_PLL_set_SCALER_DDR_CALIB_Div(U8 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_DDR_CALIB'. */
U8   GH_PLL_get_SCALER_DDR_CALIB_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_SCALER_DDR_CALIB(U32 data)
{
    *(volatile U32 *)REG_PLL_SCALER_DDR_CALIB = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_DDR_CALIB] <-- 0x%08x\n",
                        REG_PLL_SCALER_DDR_CALIB,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_DDR_CALIB(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_DDR_CALIB);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_DDR_CALIB] --> 0x%08x\n",
                        REG_PLL_SCALER_DDR_CALIB,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_SCALER_DDR_CALIB_Div(U8 data)
{
    GH_PLL_SCALER_DDR_CALIB_S d;
    d.all = *(volatile U32 *)REG_PLL_SCALER_DDR_CALIB;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_SCALER_DDR_CALIB = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_DDR_CALIB_Div] <-- 0x%08x\n",
                        REG_PLL_SCALER_DDR_CALIB,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_SCALER_DDR_CALIB_Div(void)
{
    GH_PLL_SCALER_DDR_CALIB_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_DDR_CALIB);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_DDR_CALIB_Div] --> 0x%08x\n",
                        REG_PLL_SCALER_DDR_CALIB,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_LOCK (read)                                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'PLL_LOCK'. */
U32  GH_PLL_get_LOCK(void);
/*! \brief Reads the bit group 'VIDEO2' of register 'PLL_LOCK'. */
U8   GH_PLL_get_LOCK_VIDEO2(void);
/*! \brief Reads the bit group 'VIDEO' of register 'PLL_LOCK'. */
U8   GH_PLL_get_LOCK_VIDEO(void);
/*! \brief Reads the bit group 'SENSOR' of register 'PLL_LOCK'. */
U8   GH_PLL_get_LOCK_SENSOR(void);
/*! \brief Reads the bit group 'IDSP' of register 'PLL_LOCK'. */
U8   GH_PLL_get_LOCK_IDSP(void);
/*! \brief Reads the bit group 'DDR' of register 'PLL_LOCK'. */
U8   GH_PLL_get_LOCK_DDR(void);
/*! \brief Reads the bit group 'CORE' of register 'PLL_LOCK'. */
U8   GH_PLL_get_LOCK_CORE(void);
/*! \brief Reads the bit group 'AUDIO' of register 'PLL_LOCK'. */
U8   GH_PLL_get_LOCK_AUDIO(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_PLL_get_LOCK(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_LOCK);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_LOCK] --> 0x%08x\n",
                        REG_PLL_LOCK,value);
    #endif
    return value;
}
GH_INLINE U8   GH_PLL_get_LOCK_VIDEO2(void)
{
    GH_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_LOCK);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_LOCK_VIDEO2] --> 0x%08x\n",
                        REG_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.video2;
}
GH_INLINE U8   GH_PLL_get_LOCK_VIDEO(void)
{
    GH_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_LOCK);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_LOCK_VIDEO] --> 0x%08x\n",
                        REG_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.video;
}
GH_INLINE U8   GH_PLL_get_LOCK_SENSOR(void)
{
    GH_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_LOCK);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_LOCK_SENSOR] --> 0x%08x\n",
                        REG_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.sensor;
}
GH_INLINE U8   GH_PLL_get_LOCK_IDSP(void)
{
    GH_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_LOCK);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_LOCK_IDSP] --> 0x%08x\n",
                        REG_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.idsp;
}
GH_INLINE U8   GH_PLL_get_LOCK_DDR(void)
{
    GH_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_LOCK);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_LOCK_DDR] --> 0x%08x\n",
                        REG_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.ddr;
}
GH_INLINE U8   GH_PLL_get_LOCK_CORE(void)
{
    GH_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_LOCK);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_LOCK_CORE] --> 0x%08x\n",
                        REG_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.core;
}
GH_INLINE U8   GH_PLL_get_LOCK_AUDIO(void)
{
    GH_PLL_LOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_LOCK);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_LOCK_AUDIO] --> 0x%08x\n",
                        REG_PLL_LOCK,value);
    #endif
    return tmp_value.bitc.audio;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_SCALER_DEBOUNCE (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_SCALER_DEBOUNCE'. */
void GH_PLL_set_SCALER_DEBOUNCE(U32 data);
/*! \brief Reads the register 'PLL_SCALER_DEBOUNCE'. */
U32  GH_PLL_get_SCALER_DEBOUNCE(void);
/*! \brief Writes the bit group 'Div' of register 'PLL_SCALER_DEBOUNCE'. */
void GH_PLL_set_SCALER_DEBOUNCE_Div(U32 data);
/*! \brief Reads the bit group 'Div' of register 'PLL_SCALER_DEBOUNCE'. */
U32  GH_PLL_get_SCALER_DEBOUNCE_Div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_SCALER_DEBOUNCE(U32 data)
{
    *(volatile U32 *)REG_PLL_SCALER_DEBOUNCE = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_DEBOUNCE] <-- 0x%08x\n",
                        REG_PLL_SCALER_DEBOUNCE,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_DEBOUNCE(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_DEBOUNCE);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_DEBOUNCE] --> 0x%08x\n",
                        REG_PLL_SCALER_DEBOUNCE,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_SCALER_DEBOUNCE_Div(U32 data)
{
    GH_PLL_SCALER_DEBOUNCE_S d;
    d.all = *(volatile U32 *)REG_PLL_SCALER_DEBOUNCE;
    d.bitc.div = data;
    *(volatile U32 *)REG_PLL_SCALER_DEBOUNCE = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_SCALER_DEBOUNCE_Div] <-- 0x%08x\n",
                        REG_PLL_SCALER_DEBOUNCE,d.all,d.all);
    #endif
}
GH_INLINE U32  GH_PLL_get_SCALER_DEBOUNCE_Div(void)
{
    GH_PLL_SCALER_DEBOUNCE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_SCALER_DEBOUNCE);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_SCALER_DEBOUNCE_Div] --> 0x%08x\n",
                        REG_PLL_SCALER_DEBOUNCE,value);
    #endif
    return tmp_value.bitc.div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PLL_CKEN_VDSP (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'PLL_CKEN_VDSP'. */
void GH_PLL_set_CKEN_VDSP(U32 data);
/*! \brief Reads the register 'PLL_CKEN_VDSP'. */
U32  GH_PLL_get_CKEN_VDSP(void);
/*! \brief Writes the bit group 'memd' of register 'PLL_CKEN_VDSP'. */
void GH_PLL_set_CKEN_VDSP_memd(U8 data);
/*! \brief Reads the bit group 'memd' of register 'PLL_CKEN_VDSP'. */
U8   GH_PLL_get_CKEN_VDSP_memd(void);
/*! \brief Writes the bit group 'tsfm' of register 'PLL_CKEN_VDSP'. */
void GH_PLL_set_CKEN_VDSP_tsfm(U8 data);
/*! \brief Reads the bit group 'tsfm' of register 'PLL_CKEN_VDSP'. */
U8   GH_PLL_get_CKEN_VDSP_tsfm(void);
/*! \brief Writes the bit group 'code' of register 'PLL_CKEN_VDSP'. */
void GH_PLL_set_CKEN_VDSP_code(U8 data);
/*! \brief Reads the bit group 'code' of register 'PLL_CKEN_VDSP'. */
U8   GH_PLL_get_CKEN_VDSP_code(void);
/*! \brief Writes the bit group 'smem' of register 'PLL_CKEN_VDSP'. */
void GH_PLL_set_CKEN_VDSP_smem(U8 data);
/*! \brief Reads the bit group 'smem' of register 'PLL_CKEN_VDSP'. */
U8   GH_PLL_get_CKEN_VDSP_smem(void);
/*! \brief Writes the bit group 'md' of register 'PLL_CKEN_VDSP'. */
void GH_PLL_set_CKEN_VDSP_md(U8 data);
/*! \brief Reads the bit group 'md' of register 'PLL_CKEN_VDSP'. */
U8   GH_PLL_get_CKEN_VDSP_md(void);
/*! \brief Writes the bit group 'me' of register 'PLL_CKEN_VDSP'. */
void GH_PLL_set_CKEN_VDSP_me(U8 data);
/*! \brief Reads the bit group 'me' of register 'PLL_CKEN_VDSP'. */
U8   GH_PLL_get_CKEN_VDSP_me(void);
/*! \brief Writes the bit group 'mctf' of register 'PLL_CKEN_VDSP'. */
void GH_PLL_set_CKEN_VDSP_mctf(U8 data);
/*! \brief Reads the bit group 'mctf' of register 'PLL_CKEN_VDSP'. */
U8   GH_PLL_get_CKEN_VDSP_mctf(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_PLL_set_CKEN_VDSP(U32 data)
{
    *(volatile U32 *)REG_PLL_CKEN_VDSP = data;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CKEN_VDSP] <-- 0x%08x\n",
                        REG_PLL_CKEN_VDSP,data,data);
    #endif
}
GH_INLINE U32  GH_PLL_get_CKEN_VDSP(void)
{
    U32 value = (*(volatile U32 *)REG_PLL_CKEN_VDSP);

    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CKEN_VDSP] --> 0x%08x\n",
                        REG_PLL_CKEN_VDSP,value);
    #endif
    return value;
}
GH_INLINE void GH_PLL_set_CKEN_VDSP_memd(U8 data)
{
    GH_PLL_CKEN_VDSP_S d;
    d.all = *(volatile U32 *)REG_PLL_CKEN_VDSP;
    d.bitc.memd = data;
    *(volatile U32 *)REG_PLL_CKEN_VDSP = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CKEN_VDSP_memd] <-- 0x%08x\n",
                        REG_PLL_CKEN_VDSP,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CKEN_VDSP_memd(void)
{
    GH_PLL_CKEN_VDSP_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CKEN_VDSP);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CKEN_VDSP_memd] --> 0x%08x\n",
                        REG_PLL_CKEN_VDSP,value);
    #endif
    return tmp_value.bitc.memd;
}
GH_INLINE void GH_PLL_set_CKEN_VDSP_tsfm(U8 data)
{
    GH_PLL_CKEN_VDSP_S d;
    d.all = *(volatile U32 *)REG_PLL_CKEN_VDSP;
    d.bitc.tsfm = data;
    *(volatile U32 *)REG_PLL_CKEN_VDSP = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CKEN_VDSP_tsfm] <-- 0x%08x\n",
                        REG_PLL_CKEN_VDSP,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CKEN_VDSP_tsfm(void)
{
    GH_PLL_CKEN_VDSP_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CKEN_VDSP);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CKEN_VDSP_tsfm] --> 0x%08x\n",
                        REG_PLL_CKEN_VDSP,value);
    #endif
    return tmp_value.bitc.tsfm;
}
GH_INLINE void GH_PLL_set_CKEN_VDSP_code(U8 data)
{
    GH_PLL_CKEN_VDSP_S d;
    d.all = *(volatile U32 *)REG_PLL_CKEN_VDSP;
    d.bitc.code = data;
    *(volatile U32 *)REG_PLL_CKEN_VDSP = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CKEN_VDSP_code] <-- 0x%08x\n",
                        REG_PLL_CKEN_VDSP,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CKEN_VDSP_code(void)
{
    GH_PLL_CKEN_VDSP_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CKEN_VDSP);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CKEN_VDSP_code] --> 0x%08x\n",
                        REG_PLL_CKEN_VDSP,value);
    #endif
    return tmp_value.bitc.code;
}
GH_INLINE void GH_PLL_set_CKEN_VDSP_smem(U8 data)
{
    GH_PLL_CKEN_VDSP_S d;
    d.all = *(volatile U32 *)REG_PLL_CKEN_VDSP;
    d.bitc.smem = data;
    *(volatile U32 *)REG_PLL_CKEN_VDSP = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CKEN_VDSP_smem] <-- 0x%08x\n",
                        REG_PLL_CKEN_VDSP,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CKEN_VDSP_smem(void)
{
    GH_PLL_CKEN_VDSP_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CKEN_VDSP);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CKEN_VDSP_smem] --> 0x%08x\n",
                        REG_PLL_CKEN_VDSP,value);
    #endif
    return tmp_value.bitc.smem;
}
GH_INLINE void GH_PLL_set_CKEN_VDSP_md(U8 data)
{
    GH_PLL_CKEN_VDSP_S d;
    d.all = *(volatile U32 *)REG_PLL_CKEN_VDSP;
    d.bitc.md = data;
    *(volatile U32 *)REG_PLL_CKEN_VDSP = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CKEN_VDSP_md] <-- 0x%08x\n",
                        REG_PLL_CKEN_VDSP,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CKEN_VDSP_md(void)
{
    GH_PLL_CKEN_VDSP_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CKEN_VDSP);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CKEN_VDSP_md] --> 0x%08x\n",
                        REG_PLL_CKEN_VDSP,value);
    #endif
    return tmp_value.bitc.md;
}
GH_INLINE void GH_PLL_set_CKEN_VDSP_me(U8 data)
{
    GH_PLL_CKEN_VDSP_S d;
    d.all = *(volatile U32 *)REG_PLL_CKEN_VDSP;
    d.bitc.me = data;
    *(volatile U32 *)REG_PLL_CKEN_VDSP = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CKEN_VDSP_me] <-- 0x%08x\n",
                        REG_PLL_CKEN_VDSP,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CKEN_VDSP_me(void)
{
    GH_PLL_CKEN_VDSP_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CKEN_VDSP);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CKEN_VDSP_me] --> 0x%08x\n",
                        REG_PLL_CKEN_VDSP,value);
    #endif
    return tmp_value.bitc.me;
}
GH_INLINE void GH_PLL_set_CKEN_VDSP_mctf(U8 data)
{
    GH_PLL_CKEN_VDSP_S d;
    d.all = *(volatile U32 *)REG_PLL_CKEN_VDSP;
    d.bitc.mctf = data;
    *(volatile U32 *)REG_PLL_CKEN_VDSP = d.all;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PLL_set_CKEN_VDSP_mctf] <-- 0x%08x\n",
                        REG_PLL_CKEN_VDSP,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_PLL_get_CKEN_VDSP_mctf(void)
{
    GH_PLL_CKEN_VDSP_S tmp_value;
    U32 value = (*(volatile U32 *)REG_PLL_CKEN_VDSP);

    tmp_value.all = value;
    #if GH_PLL_ENABLE_DEBUG_PRINT
    GH_PLL_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PLL_get_CKEN_VDSP_mctf] --> 0x%08x\n",
                        REG_PLL_CKEN_VDSP,value);
    #endif
    return tmp_value.bitc.mctf;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_PLL_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_DEBUG_RCT_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

