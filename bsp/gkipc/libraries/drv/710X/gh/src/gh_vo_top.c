/******************************************************************************
**
** \file      gh_vo_top.c
**
** \brief     TOP control Registers.
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
#include "gh_vo_top.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_VO_TOP_RESET_VOUT_REAL                          FIO_ADDRESS(VO_TOP,0x60008A00) /* read/write */
#define REG_VO_TOP_ENABLE_CLOCK_A_REAL                      FIO_ADDRESS(VO_TOP,0x60008A04) /* read/write */
#define REG_VO_TOP_ENABLE_CLOCK_B_REAL                      FIO_ADDRESS(VO_TOP,0x60008A08) /* read/write */
#define REG_VO_TOP_ENABLE_CLOCK_OSDR_REAL                   FIO_ADDRESS(VO_TOP,0x60008A0C) /* read/write */
#define REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING_REAL         FIO_ADDRESS(VO_TOP,0x60008A10) /* read/write */
#define REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING_REAL          FIO_ADDRESS(VO_TOP,0x60008A14) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* VO_TOP_RESET_VOUT */
    U32 all;
    struct {
        U32                             : 31;
        U32 reset                       : 1;
    } bitc;
} GH_VO_TOP_RESET_VOUT_REAL_S;

typedef union { /* VO_TOP_ENABLE_CLOCK_A */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32                             : 31;
    } bitc;
} GH_VO_TOP_ENABLE_CLOCK_A_REAL_S;

typedef union { /* VO_TOP_ENABLE_CLOCK_B */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32                             : 31;
    } bitc;
} GH_VO_TOP_ENABLE_CLOCK_B_REAL_S;

typedef union { /* VO_TOP_ENABLE_CLOCK_OSDR */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32                             : 31;
    } bitc;
} GH_VO_TOP_ENABLE_CLOCK_OSDR_REAL_S;

typedef union { /* VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32                             : 31;
    } bitc;
} GH_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING_REAL_S;

typedef union { /* VO_TOP_ENABLE_CONFIG_CLOCK_GATING */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32                             : 31;
    } bitc;
} GH_VO_TOP_ENABLE_CONFIG_CLOCK_GATING_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register VO_TOP_RESET_VOUT (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_TOP_set_RESET_VOUT(U32 data)
{
    GH_VO_TOP_RESET_VOUT_REAL_S real;
    GH_VO_TOP_RESET_VOUT_S dummy;
    dummy.all = data ;
    real.bitc.reset = dummy.bitc.reset;
    *(volatile U32 *)REG_VO_TOP_RESET_VOUT_REAL = real.all;
}
GH_INLINE U32  GH_VO_TOP_get_RESET_VOUT(void)
{
    GH_VO_TOP_RESET_VOUT_REAL_S real;
    GH_VO_TOP_RESET_VOUT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_TOP_RESET_VOUT_REAL);

    dummy.bitc.reset = real.bitc.reset;
    return dummy.all;
}
GH_INLINE void GH_VO_TOP_set_RESET_VOUT_reset(U8 data)
{
    GH_VO_TOP_RESET_VOUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_TOP_RESET_VOUT_REAL;
    d.bitc.reset = data;
    *(volatile U32 *)REG_VO_TOP_RESET_VOUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_TOP_get_RESET_VOUT_reset(void)
{
    GH_VO_TOP_RESET_VOUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_TOP_RESET_VOUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reset;
}

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_CLOCK_A (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_TOP_set_ENABLE_CLOCK_A(U32 data)
{
    GH_VO_TOP_ENABLE_CLOCK_A_REAL_S real;
    GH_VO_TOP_ENABLE_CLOCK_A_S dummy;
    dummy.all = data ;
    real.bitc.enable = dummy.bitc.enable;
    *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_A_REAL = real.all;
}
GH_INLINE U32  GH_VO_TOP_get_ENABLE_CLOCK_A(void)
{
    GH_VO_TOP_ENABLE_CLOCK_A_REAL_S real;
    GH_VO_TOP_ENABLE_CLOCK_A_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_A_REAL);

    dummy.bitc.enable = real.bitc.enable;
    return dummy.all;
}
GH_INLINE void GH_VO_TOP_set_ENABLE_CLOCK_A_enable(U8 data)
{
    GH_VO_TOP_ENABLE_CLOCK_A_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_A_REAL;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_A_REAL = d.all;
}
GH_INLINE U8   GH_VO_TOP_get_ENABLE_CLOCK_A_enable(void)
{
    GH_VO_TOP_ENABLE_CLOCK_A_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_A_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enable;
}

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_CLOCK_B (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_TOP_set_ENABLE_CLOCK_B(U32 data)
{
    GH_VO_TOP_ENABLE_CLOCK_B_REAL_S real;
    GH_VO_TOP_ENABLE_CLOCK_B_S dummy;
    dummy.all = data ;
    real.bitc.enable = dummy.bitc.enable;
    *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_B_REAL = real.all;
}
GH_INLINE U32  GH_VO_TOP_get_ENABLE_CLOCK_B(void)
{
    GH_VO_TOP_ENABLE_CLOCK_B_REAL_S real;
    GH_VO_TOP_ENABLE_CLOCK_B_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_B_REAL);

    dummy.bitc.enable = real.bitc.enable;
    return dummy.all;
}
GH_INLINE void GH_VO_TOP_set_ENABLE_CLOCK_B_enable(U8 data)
{
    GH_VO_TOP_ENABLE_CLOCK_B_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_B_REAL;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_B_REAL = d.all;
}
GH_INLINE U8   GH_VO_TOP_get_ENABLE_CLOCK_B_enable(void)
{
    GH_VO_TOP_ENABLE_CLOCK_B_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_B_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enable;
}

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_CLOCK_OSDR (read/write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_TOP_set_ENABLE_CLOCK_OSDR(U32 data)
{
    GH_VO_TOP_ENABLE_CLOCK_OSDR_REAL_S real;
    GH_VO_TOP_ENABLE_CLOCK_OSDR_S dummy;
    dummy.all = data ;
    real.bitc.enable = dummy.bitc.enable;
    *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_OSDR_REAL = real.all;
}
GH_INLINE U32  GH_VO_TOP_get_ENABLE_CLOCK_OSDR(void)
{
    GH_VO_TOP_ENABLE_CLOCK_OSDR_REAL_S real;
    GH_VO_TOP_ENABLE_CLOCK_OSDR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_OSDR_REAL);

    dummy.bitc.enable = real.bitc.enable;
    return dummy.all;
}
GH_INLINE void GH_VO_TOP_set_ENABLE_CLOCK_OSDR_enable(U8 data)
{
    GH_VO_TOP_ENABLE_CLOCK_OSDR_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_OSDR_REAL;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_OSDR_REAL = d.all;
}
GH_INLINE U8   GH_VO_TOP_get_ENABLE_CLOCK_OSDR_enable(void)
{
    GH_VO_TOP_ENABLE_CLOCK_OSDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_OSDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enable;
}

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING (read/write)                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_TOP_set_ENABLE_SMEM_IF_CLOCK_GATING(U32 data)
{
    GH_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING_REAL_S real;
    GH_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING_S dummy;
    dummy.all = data ;
    real.bitc.enable = dummy.bitc.enable;
    *(volatile U32 *)REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING_REAL = real.all;
}
GH_INLINE U32  GH_VO_TOP_get_ENABLE_SMEM_IF_CLOCK_GATING(void)
{
    GH_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING_REAL_S real;
    GH_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING_REAL);

    dummy.bitc.enable = real.bitc.enable;
    return dummy.all;
}
GH_INLINE void GH_VO_TOP_set_ENABLE_SMEM_IF_CLOCK_GATING_enable(U8 data)
{
    GH_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING_REAL;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING_REAL = d.all;
}
GH_INLINE U8   GH_VO_TOP_get_ENABLE_SMEM_IF_CLOCK_GATING_enable(void)
{
    GH_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enable;
}

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_CONFIG_CLOCK_GATING (read/write)                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_TOP_set_ENABLE_CONFIG_CLOCK_GATING(U32 data)
{
    GH_VO_TOP_ENABLE_CONFIG_CLOCK_GATING_REAL_S real;
    GH_VO_TOP_ENABLE_CONFIG_CLOCK_GATING_S dummy;
    dummy.all = data ;
    real.bitc.enable = dummy.bitc.enable;
    *(volatile U32 *)REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING_REAL = real.all;
}
GH_INLINE U32  GH_VO_TOP_get_ENABLE_CONFIG_CLOCK_GATING(void)
{
    GH_VO_TOP_ENABLE_CONFIG_CLOCK_GATING_REAL_S real;
    GH_VO_TOP_ENABLE_CONFIG_CLOCK_GATING_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING_REAL);

    dummy.bitc.enable = real.bitc.enable;
    return dummy.all;
}
GH_INLINE void GH_VO_TOP_set_ENABLE_CONFIG_CLOCK_GATING_enable(U8 data)
{
    GH_VO_TOP_ENABLE_CONFIG_CLOCK_GATING_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING_REAL;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING_REAL = d.all;
}
GH_INLINE U8   GH_VO_TOP_get_ENABLE_CONFIG_CLOCK_GATING_enable(void)
{
    GH_VO_TOP_ENABLE_CONFIG_CLOCK_GATING_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enable;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_TOP_init(void)
{
    GH_VO_TOP_set_RESET_VOUT((U32)0x00000000);
    GH_VO_TOP_set_ENABLE_CLOCK_A((U32)0x00000001);
    GH_VO_TOP_set_ENABLE_CLOCK_B((U32)0x00000001);
    GH_VO_TOP_set_ENABLE_CLOCK_OSDR((U32)0x00000001);
    GH_VO_TOP_set_ENABLE_SMEM_IF_CLOCK_GATING((U32)0x00000000);
    GH_VO_TOP_set_ENABLE_CONFIG_CLOCK_GATING((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

