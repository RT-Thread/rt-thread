/******************************************************************************
**
** \file      gh_vo_osd.c
**
** \brief     OSD Rescale Registers.
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
#include "gh_vo_osd.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_VO_OSD_RESCALE_CONTROL_REAL                     FIO_ADDRESS(VO_OSD,0x60008800) /* read/write */
#define REG_VO_OSD_RESCALE_WIDTH_REAL                       FIO_ADDRESS(VO_OSD,0x60008804) /* read/write */
#define REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC_REAL        FIO_ADDRESS(VO_OSD,0x60008808) /* read/write */
#define REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_REAL  FIO_ADDRESS(VO_OSD,0x6000880C) /* read/write */
#define REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD_REAL   FIO_ADDRESS(VO_OSD,0x60008810) /* read/write */
#define REG_VO_OSD_RESCALE_HEIGHT_REAL                      FIO_ADDRESS(VO_OSD,0x60008814) /* read/write */
#define REG_VO_OSD_RESCALE_VERTICAL_PHASE_INC_REAL          FIO_ADDRESS(VO_OSD,0x60008818) /* read/write */
#define REG_VO_OSD_RESCALE_VERTICAL_PHASE_INIT_REAL         FIO_ADDRESS(VO_OSD,0x6000881C) /* read/write */
#define REG_VO_OSD_RESCALE_HORIZONTAL_COEFF_REAL            FIO_ADDRESS(VO_OSD,0x60008820) /* write */
#define REG_VO_OSD_RESCALE_VERTICAL_COEFF_REAL              FIO_ADDRESS(VO_OSD,0x600088A0) /* write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* VO_OSD_RESCALE_CONTROL */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32 vertical_shift              : 1;
        U32                             : 1;
        U32 horizontal_shift            : 1;
        U32 input                       : 2;
        U32                             : 26;
    } bitc;
} GH_VO_OSD_RESCALE_CONTROL_REAL_S;

typedef union { /* VO_OSD_RESCALE_WIDTH */
    U32 all;
    struct {
        U32 width                       : 14;
        U32                             : 18;
    } bitc;
} GH_VO_OSD_RESCALE_WIDTH_REAL_S;

typedef union { /* VO_OSD_RESCALE_HORIZONTAL_PHASE_INC */
    U32 all;
    struct {
        U32 inc                         : 16;
        U32                             : 16;
    } bitc;
} GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC_REAL_S;

typedef union { /* VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN */
    U32 all;
    struct {
        U32 init                        : 28;
        U32                             : 4;
    } bitc;
} GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_REAL_S;

typedef union { /* VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD */
    U32 all;
    struct {
        U32 init                        : 28;
        U32                             : 4;
    } bitc;
} GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD_REAL_S;

typedef union { /* VO_OSD_RESCALE_HEIGHT */
    U32 all;
    struct {
        U32 height                      : 14;
        U32                             : 18;
    } bitc;
} GH_VO_OSD_RESCALE_HEIGHT_REAL_S;

typedef union { /* VO_OSD_RESCALE_VERTICAL_PHASE_INC */
    U32 all;
    struct {
        U32 inc                         : 16;
        U32                             : 16;
    } bitc;
} GH_VO_OSD_RESCALE_VERTICAL_PHASE_INC_REAL_S;

typedef union { /* VO_OSD_RESCALE_VERTICAL_PHASE_INIT */
    U32 all;
    struct {
        U32 init                        : 28;
        U32                             : 4;
    } bitc;
} GH_VO_OSD_RESCALE_VERTICAL_PHASE_INIT_REAL_S;

typedef union { /* VO_OSD_RESCALE_HORIZONTAL_COEFF */
    U32 all;
    struct {
        U32 even_0_odd_4                : 8;
        U32 even_1_odd_5                : 8;
        U32 even_2                      : 8;
        U32 even_3                      : 8;
    } bitc;
} GH_VO_OSD_RESCALE_HORIZONTAL_COEFF_REAL_S;

typedef union { /* VO_OSD_RESCALE_VERTICAL_COEFF */
    U32 all;
    struct {
        U32 even_0_odd_4                : 8;
        U32 even_1_odd_5                : 8;
        U32 even_2                      : 8;
        U32 even_3                      : 8;
    } bitc;
} GH_VO_OSD_RESCALE_VERTICAL_COEFF_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_VO_OSD_RESCALE_HORIZONTAL_COEFF_S    m_vo_osd_rescale_horizontal_coeff[32];
GH_VO_OSD_RESCALE_VERTICAL_COEFF_S      m_vo_osd_rescale_vertical_coeff[32];

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_CONTROL (read/write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_OSD_set_RESCALE_CONTROL(U32 data)
{
    GH_VO_OSD_RESCALE_CONTROL_REAL_S real;
    GH_VO_OSD_RESCALE_CONTROL_S dummy;
    dummy.all = data ;
    real.bitc.enable = dummy.bitc.enable;
    real.bitc.vertical_shift = dummy.bitc.vertical_shift;
    real.bitc.horizontal_shift = dummy.bitc.horizontal_shift;
    real.bitc.input = dummy.bitc.input;
    *(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL_REAL = real.all;
}
GH_INLINE U32  GH_VO_OSD_get_RESCALE_CONTROL(void)
{
    GH_VO_OSD_RESCALE_CONTROL_REAL_S real;
    GH_VO_OSD_RESCALE_CONTROL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL_REAL);

    dummy.bitc.enable = real.bitc.enable;
    dummy.bitc.vertical_shift = real.bitc.vertical_shift;
    dummy.bitc.horizontal_shift = real.bitc.horizontal_shift;
    dummy.bitc.input = real.bitc.input;
    return dummy.all;
}
GH_INLINE void GH_VO_OSD_set_RESCALE_CONTROL_Enable(U8 data)
{
    GH_VO_OSD_RESCALE_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL_REAL;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_OSD_get_RESCALE_CONTROL_Enable(void)
{
    GH_VO_OSD_RESCALE_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enable;
}
GH_INLINE void GH_VO_OSD_set_RESCALE_CONTROL_Vertical_shift(U8 data)
{
    GH_VO_OSD_RESCALE_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL_REAL;
    d.bitc.vertical_shift = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_OSD_get_RESCALE_CONTROL_Vertical_shift(void)
{
    GH_VO_OSD_RESCALE_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vertical_shift;
}
GH_INLINE void GH_VO_OSD_set_RESCALE_CONTROL_Horizontal_shift(U8 data)
{
    GH_VO_OSD_RESCALE_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL_REAL;
    d.bitc.horizontal_shift = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_OSD_get_RESCALE_CONTROL_Horizontal_shift(void)
{
    GH_VO_OSD_RESCALE_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.horizontal_shift;
}
GH_INLINE void GH_VO_OSD_set_RESCALE_CONTROL_Input(U8 data)
{
    GH_VO_OSD_RESCALE_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL_REAL;
    d.bitc.input = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_OSD_get_RESCALE_CONTROL_Input(void)
{
    GH_VO_OSD_RESCALE_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.input;
}

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_WIDTH (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_OSD_set_RESCALE_WIDTH(U32 data)
{
    GH_VO_OSD_RESCALE_WIDTH_REAL_S real;
    GH_VO_OSD_RESCALE_WIDTH_S dummy;
    dummy.all = data ;
    real.bitc.width = dummy.bitc.width;
    *(volatile U32 *)REG_VO_OSD_RESCALE_WIDTH_REAL = real.all;
}
GH_INLINE U32  GH_VO_OSD_get_RESCALE_WIDTH(void)
{
    GH_VO_OSD_RESCALE_WIDTH_REAL_S real;
    GH_VO_OSD_RESCALE_WIDTH_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_OSD_RESCALE_WIDTH_REAL);

    dummy.bitc.width = real.bitc.width;
    return dummy.all;
}
GH_INLINE void GH_VO_OSD_set_RESCALE_WIDTH_width(U16 data)
{
    GH_VO_OSD_RESCALE_WIDTH_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_WIDTH_REAL;
    d.bitc.width = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_WIDTH_REAL = d.all;
}
GH_INLINE U16  GH_VO_OSD_get_RESCALE_WIDTH_width(void)
{
    GH_VO_OSD_RESCALE_WIDTH_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_WIDTH_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.width;
}

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_HORIZONTAL_PHASE_INC (read/write)                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INC(U32 data)
{
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC_REAL_S real;
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC_S dummy;
    dummy.all = data ;
    real.bitc.inc = dummy.bitc.inc;
    *(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC_REAL = real.all;
}
GH_INLINE U32  GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INC(void)
{
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC_REAL_S real;
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC_REAL);

    dummy.bitc.inc = real.bitc.inc;
    return dummy.all;
}
GH_INLINE void GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INC_inc(U16 data)
{
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC_REAL;
    d.bitc.inc = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC_REAL = d.all;
}
GH_INLINE U16  GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INC_inc(void)
{
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.inc;
}

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN (read/write)            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_EVEN(U32 data)
{
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_REAL_S real;
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_S dummy;
    dummy.all = data ;
    real.bitc.init = dummy.bitc.init;
    *(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_REAL = real.all;
}
GH_INLINE U32  GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INIT_EVEN(void)
{
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_REAL_S real;
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_REAL);

    dummy.bitc.init = real.bitc.init;
    return dummy.all;
}
GH_INLINE void GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_init(U32 data)
{
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_REAL;
    d.bitc.init = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_REAL = d.all;
}
GH_INLINE U32  GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_init(void)
{
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.init;
}

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD (read/write)             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_ODD(U32 data)
{
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD_REAL_S real;
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD_S dummy;
    dummy.all = data ;
    real.bitc.init = dummy.bitc.init;
    *(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD_REAL = real.all;
}
GH_INLINE U32  GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INIT_ODD(void)
{
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD_REAL_S real;
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD_REAL);

    dummy.bitc.init = real.bitc.init;
    return dummy.all;
}
GH_INLINE void GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_ODD_init(U32 data)
{
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD_REAL;
    d.bitc.init = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD_REAL = d.all;
}
GH_INLINE U32  GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INIT_ODD_init(void)
{
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.init;
}

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_HEIGHT (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_OSD_set_RESCALE_HEIGHT(U32 data)
{
    GH_VO_OSD_RESCALE_HEIGHT_REAL_S real;
    GH_VO_OSD_RESCALE_HEIGHT_S dummy;
    dummy.all = data ;
    real.bitc.height = dummy.bitc.height;
    *(volatile U32 *)REG_VO_OSD_RESCALE_HEIGHT_REAL = real.all;
}
GH_INLINE U32  GH_VO_OSD_get_RESCALE_HEIGHT(void)
{
    GH_VO_OSD_RESCALE_HEIGHT_REAL_S real;
    GH_VO_OSD_RESCALE_HEIGHT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_OSD_RESCALE_HEIGHT_REAL);

    dummy.bitc.height = real.bitc.height;
    return dummy.all;
}
GH_INLINE void GH_VO_OSD_set_RESCALE_HEIGHT_height(U16 data)
{
    GH_VO_OSD_RESCALE_HEIGHT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_HEIGHT_REAL;
    d.bitc.height = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_HEIGHT_REAL = d.all;
}
GH_INLINE U16  GH_VO_OSD_get_RESCALE_HEIGHT_height(void)
{
    GH_VO_OSD_RESCALE_HEIGHT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_HEIGHT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.height;
}

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_VERTICAL_PHASE_INC (read/write)                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INC(U32 data)
{
    GH_VO_OSD_RESCALE_VERTICAL_PHASE_INC_REAL_S real;
    GH_VO_OSD_RESCALE_VERTICAL_PHASE_INC_S dummy;
    dummy.all = data ;
    real.bitc.inc = dummy.bitc.inc;
    *(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INC_REAL = real.all;
}
GH_INLINE U32  GH_VO_OSD_get_RESCALE_VERTICAL_PHASE_INC(void)
{
    GH_VO_OSD_RESCALE_VERTICAL_PHASE_INC_REAL_S real;
    GH_VO_OSD_RESCALE_VERTICAL_PHASE_INC_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INC_REAL);

    dummy.bitc.inc = real.bitc.inc;
    return dummy.all;
}
GH_INLINE void GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INC_inc(U16 data)
{
    GH_VO_OSD_RESCALE_VERTICAL_PHASE_INC_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INC_REAL;
    d.bitc.inc = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INC_REAL = d.all;
}
GH_INLINE U16  GH_VO_OSD_get_RESCALE_VERTICAL_PHASE_INC_inc(void)
{
    GH_VO_OSD_RESCALE_VERTICAL_PHASE_INC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.inc;
}

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_VERTICAL_PHASE_INIT (read/write)                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INIT(U32 data)
{
    GH_VO_OSD_RESCALE_VERTICAL_PHASE_INIT_REAL_S real;
    GH_VO_OSD_RESCALE_VERTICAL_PHASE_INIT_S dummy;
    dummy.all = data ;
    real.bitc.init = dummy.bitc.init;
    *(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INIT_REAL = real.all;
}
GH_INLINE U32  GH_VO_OSD_get_RESCALE_VERTICAL_PHASE_INIT(void)
{
    GH_VO_OSD_RESCALE_VERTICAL_PHASE_INIT_REAL_S real;
    GH_VO_OSD_RESCALE_VERTICAL_PHASE_INIT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INIT_REAL);

    dummy.bitc.init = real.bitc.init;
    return dummy.all;
}
GH_INLINE void GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INIT_init(U32 data)
{
    GH_VO_OSD_RESCALE_VERTICAL_PHASE_INIT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INIT_REAL;
    d.bitc.init = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INIT_REAL = d.all;
}
GH_INLINE U32  GH_VO_OSD_get_RESCALE_VERTICAL_PHASE_INIT_init(void)
{
    GH_VO_OSD_RESCALE_VERTICAL_PHASE_INIT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INIT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.init;
}

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_HORIZONTAL_COEFF (write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF(U8 index, U32 data)
{
    m_vo_osd_rescale_horizontal_coeff[index].all = data;
    GH_VO_OSD_RESCALE_HORIZONTAL_COEFF_REAL_S real;
    GH_VO_OSD_RESCALE_HORIZONTAL_COEFF_S dummy;
    dummy.all = data ;
    real.bitc.even_0_odd_4 = dummy.bitc.even_0_odd_4;
    real.bitc.even_1_odd_5 = dummy.bitc.even_1_odd_5;
    real.bitc.even_2 = dummy.bitc.even_2;
    real.bitc.even_3 = dummy.bitc.even_3;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_HORIZONTAL_COEFF_REAL + index * FIO_MOFFSET(VO_OSD,0x00000004)) = real.all;
}
GH_INLINE U32  GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF] --> 0x%08x\n",
                        m_vo_osd_rescale_horizontal_coeff[index].all);
    #endif
    return m_vo_osd_rescale_horizontal_coeff[index].all;
}
GH_INLINE void GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF_even_0_odd_4(U8 index, U8 data)
{
    m_vo_osd_rescale_horizontal_coeff[index].bitc.even_0_odd_4 = data;
    GH_VO_OSD_RESCALE_HORIZONTAL_COEFF_REAL_S real;
    real.bitc.even_0_odd_4 = m_vo_osd_rescale_horizontal_coeff[index].bitc.even_0_odd_4;
    real.bitc.even_1_odd_5 = m_vo_osd_rescale_horizontal_coeff[index].bitc.even_1_odd_5;
    real.bitc.even_2 = m_vo_osd_rescale_horizontal_coeff[index].bitc.even_2;
    real.bitc.even_3 = m_vo_osd_rescale_horizontal_coeff[index].bitc.even_3;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_HORIZONTAL_COEFF_REAL + index * FIO_MOFFSET(VO_OSD,0x00000004)) = real.all;
}
GH_INLINE U8   GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_0_odd_4(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_0_odd_4] --> 0x%08x\n",
                        m_vo_osd_rescale_horizontal_coeff[index].bitc.even_0_odd_4);
    #endif
    return m_vo_osd_rescale_horizontal_coeff[index].bitc.even_0_odd_4;
}
GH_INLINE void GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF_even_1_odd_5(U8 index, U8 data)
{
    m_vo_osd_rescale_horizontal_coeff[index].bitc.even_1_odd_5 = data;
    GH_VO_OSD_RESCALE_HORIZONTAL_COEFF_REAL_S real;
    real.bitc.even_0_odd_4 = m_vo_osd_rescale_horizontal_coeff[index].bitc.even_0_odd_4;
    real.bitc.even_1_odd_5 = m_vo_osd_rescale_horizontal_coeff[index].bitc.even_1_odd_5;
    real.bitc.even_2 = m_vo_osd_rescale_horizontal_coeff[index].bitc.even_2;
    real.bitc.even_3 = m_vo_osd_rescale_horizontal_coeff[index].bitc.even_3;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_HORIZONTAL_COEFF_REAL + index * FIO_MOFFSET(VO_OSD,0x00000004)) = real.all;
}
GH_INLINE U8   GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_1_odd_5(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_1_odd_5] --> 0x%08x\n",
                        m_vo_osd_rescale_horizontal_coeff[index].bitc.even_1_odd_5);
    #endif
    return m_vo_osd_rescale_horizontal_coeff[index].bitc.even_1_odd_5;
}
GH_INLINE void GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF_even_2(U8 index, U8 data)
{
    m_vo_osd_rescale_horizontal_coeff[index].bitc.even_2 = data;
    GH_VO_OSD_RESCALE_HORIZONTAL_COEFF_REAL_S real;
    real.bitc.even_0_odd_4 = m_vo_osd_rescale_horizontal_coeff[index].bitc.even_0_odd_4;
    real.bitc.even_1_odd_5 = m_vo_osd_rescale_horizontal_coeff[index].bitc.even_1_odd_5;
    real.bitc.even_2 = m_vo_osd_rescale_horizontal_coeff[index].bitc.even_2;
    real.bitc.even_3 = m_vo_osd_rescale_horizontal_coeff[index].bitc.even_3;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_HORIZONTAL_COEFF_REAL + index * FIO_MOFFSET(VO_OSD,0x00000004)) = real.all;
}
GH_INLINE U8   GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_2(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_2] --> 0x%08x\n",
                        m_vo_osd_rescale_horizontal_coeff[index].bitc.even_2);
    #endif
    return m_vo_osd_rescale_horizontal_coeff[index].bitc.even_2;
}
GH_INLINE void GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF_even_3(U8 index, U8 data)
{
    m_vo_osd_rescale_horizontal_coeff[index].bitc.even_3 = data;
    GH_VO_OSD_RESCALE_HORIZONTAL_COEFF_REAL_S real;
    real.bitc.even_0_odd_4 = m_vo_osd_rescale_horizontal_coeff[index].bitc.even_0_odd_4;
    real.bitc.even_1_odd_5 = m_vo_osd_rescale_horizontal_coeff[index].bitc.even_1_odd_5;
    real.bitc.even_2 = m_vo_osd_rescale_horizontal_coeff[index].bitc.even_2;
    real.bitc.even_3 = m_vo_osd_rescale_horizontal_coeff[index].bitc.even_3;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_HORIZONTAL_COEFF_REAL + index * FIO_MOFFSET(VO_OSD,0x00000004)) = real.all;
}
GH_INLINE U8   GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_3(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_3] --> 0x%08x\n",
                        m_vo_osd_rescale_horizontal_coeff[index].bitc.even_3);
    #endif
    return m_vo_osd_rescale_horizontal_coeff[index].bitc.even_3;
}

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_VERTICAL_COEFF (write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_OSD_set_RESCALE_VERTICAL_COEFF(U8 index, U32 data)
{
    m_vo_osd_rescale_vertical_coeff[index].all = data;
    GH_VO_OSD_RESCALE_VERTICAL_COEFF_REAL_S real;
    GH_VO_OSD_RESCALE_VERTICAL_COEFF_S dummy;
    dummy.all = data ;
    real.bitc.even_0_odd_4 = dummy.bitc.even_0_odd_4;
    real.bitc.even_1_odd_5 = dummy.bitc.even_1_odd_5;
    real.bitc.even_2 = dummy.bitc.even_2;
    real.bitc.even_3 = dummy.bitc.even_3;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_VERTICAL_COEFF_REAL + index * FIO_MOFFSET(VO_OSD,0x00000004)) = real.all;
}
GH_INLINE U32  GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF] --> 0x%08x\n",
                        m_vo_osd_rescale_vertical_coeff[index].all);
    #endif
    return m_vo_osd_rescale_vertical_coeff[index].all;
}
GH_INLINE void GH_VO_OSD_set_RESCALE_VERTICAL_COEFF_even_0_odd_4(U8 index, U8 data)
{
    m_vo_osd_rescale_vertical_coeff[index].bitc.even_0_odd_4 = data;
    GH_VO_OSD_RESCALE_VERTICAL_COEFF_REAL_S real;
    real.bitc.even_0_odd_4 = m_vo_osd_rescale_vertical_coeff[index].bitc.even_0_odd_4;
    real.bitc.even_1_odd_5 = m_vo_osd_rescale_vertical_coeff[index].bitc.even_1_odd_5;
    real.bitc.even_2 = m_vo_osd_rescale_vertical_coeff[index].bitc.even_2;
    real.bitc.even_3 = m_vo_osd_rescale_vertical_coeff[index].bitc.even_3;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_VERTICAL_COEFF_REAL + index * FIO_MOFFSET(VO_OSD,0x00000004)) = real.all;
}
GH_INLINE U8   GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_0_odd_4(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_0_odd_4] --> 0x%08x\n",
                        m_vo_osd_rescale_vertical_coeff[index].bitc.even_0_odd_4);
    #endif
    return m_vo_osd_rescale_vertical_coeff[index].bitc.even_0_odd_4;
}
GH_INLINE void GH_VO_OSD_set_RESCALE_VERTICAL_COEFF_even_1_odd_5(U8 index, U8 data)
{
    m_vo_osd_rescale_vertical_coeff[index].bitc.even_1_odd_5 = data;
    GH_VO_OSD_RESCALE_VERTICAL_COEFF_REAL_S real;
    real.bitc.even_0_odd_4 = m_vo_osd_rescale_vertical_coeff[index].bitc.even_0_odd_4;
    real.bitc.even_1_odd_5 = m_vo_osd_rescale_vertical_coeff[index].bitc.even_1_odd_5;
    real.bitc.even_2 = m_vo_osd_rescale_vertical_coeff[index].bitc.even_2;
    real.bitc.even_3 = m_vo_osd_rescale_vertical_coeff[index].bitc.even_3;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_VERTICAL_COEFF_REAL + index * FIO_MOFFSET(VO_OSD,0x00000004)) = real.all;
}
GH_INLINE U8   GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_1_odd_5(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_1_odd_5] --> 0x%08x\n",
                        m_vo_osd_rescale_vertical_coeff[index].bitc.even_1_odd_5);
    #endif
    return m_vo_osd_rescale_vertical_coeff[index].bitc.even_1_odd_5;
}
GH_INLINE void GH_VO_OSD_set_RESCALE_VERTICAL_COEFF_even_2(U8 index, U8 data)
{
    m_vo_osd_rescale_vertical_coeff[index].bitc.even_2 = data;
    GH_VO_OSD_RESCALE_VERTICAL_COEFF_REAL_S real;
    real.bitc.even_0_odd_4 = m_vo_osd_rescale_vertical_coeff[index].bitc.even_0_odd_4;
    real.bitc.even_1_odd_5 = m_vo_osd_rescale_vertical_coeff[index].bitc.even_1_odd_5;
    real.bitc.even_2 = m_vo_osd_rescale_vertical_coeff[index].bitc.even_2;
    real.bitc.even_3 = m_vo_osd_rescale_vertical_coeff[index].bitc.even_3;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_VERTICAL_COEFF_REAL + index * FIO_MOFFSET(VO_OSD,0x00000004)) = real.all;
}
GH_INLINE U8   GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_2(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_2] --> 0x%08x\n",
                        m_vo_osd_rescale_vertical_coeff[index].bitc.even_2);
    #endif
    return m_vo_osd_rescale_vertical_coeff[index].bitc.even_2;
}
GH_INLINE void GH_VO_OSD_set_RESCALE_VERTICAL_COEFF_even_3(U8 index, U8 data)
{
    m_vo_osd_rescale_vertical_coeff[index].bitc.even_3 = data;
    GH_VO_OSD_RESCALE_VERTICAL_COEFF_REAL_S real;
    real.bitc.even_0_odd_4 = m_vo_osd_rescale_vertical_coeff[index].bitc.even_0_odd_4;
    real.bitc.even_1_odd_5 = m_vo_osd_rescale_vertical_coeff[index].bitc.even_1_odd_5;
    real.bitc.even_2 = m_vo_osd_rescale_vertical_coeff[index].bitc.even_2;
    real.bitc.even_3 = m_vo_osd_rescale_vertical_coeff[index].bitc.even_3;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_VERTICAL_COEFF_REAL + index * FIO_MOFFSET(VO_OSD,0x00000004)) = real.all;
}
GH_INLINE U8   GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_3(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_3] --> 0x%08x\n",
                        m_vo_osd_rescale_vertical_coeff[index].bitc.even_3);
    #endif
    return m_vo_osd_rescale_vertical_coeff[index].bitc.even_3;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_OSD_init(void)
{
    int i;

    GH_VO_OSD_set_RESCALE_CONTROL((U32)0x00000000);
    GH_VO_OSD_set_RESCALE_WIDTH((U32)0x00000000);
    GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INC((U32)0x00000000);
    GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_EVEN((U32)0x00000000);
    GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_ODD((U32)0x00000000);
    GH_VO_OSD_set_RESCALE_HEIGHT((U32)0x00000000);
    GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INC((U32)0x00000000);
    GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INIT((U32)0x00000000);
    GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF(0, (U32)0x00000000);
    for (i=1; i<32; i++)
    {
        GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF(i, (U32)0x00000000);
    }
    GH_VO_OSD_set_RESCALE_VERTICAL_COEFF(0, (U32)0x00000000);
    for (i=1; i<32; i++)
    {
        GH_VO_OSD_set_RESCALE_VERTICAL_COEFF(i, (U32)0x00000000);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

