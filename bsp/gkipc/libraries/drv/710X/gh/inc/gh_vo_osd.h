/*!
*******************************************************************************
**
** \file      gh_vo_osd.h
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
#ifndef _GH_VO_OSD_H
#define _GH_VO_OSD_H

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

#define GH_VO_OSD_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_VO_OSD_DEBUG_PRINT_FUNCTION printk
#else
#define GH_VO_OSD_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_VO_OSD_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_VO_OSD_RESCALE_CONTROL                          FIO_ADDRESS(VO_OSD,0x90008800) /* read/write */
#define REG_VO_OSD_RESCALE_WIDTH                            FIO_ADDRESS(VO_OSD,0x90008804) /* read/write */
#define REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC             FIO_ADDRESS(VO_OSD,0x90008808) /* read/write */
#define REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN       FIO_ADDRESS(VO_OSD,0x9000880C) /* read/write */
#define REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD        FIO_ADDRESS(VO_OSD,0x90008810) /* read/write */
#define REG_VO_OSD_RESCALE_HEIGHT                           FIO_ADDRESS(VO_OSD,0x90008814) /* read/write */
#define REG_VO_OSD_RESCALE_VERTICAL_PHASE_INC               FIO_ADDRESS(VO_OSD,0x90008818) /* read/write */
#define REG_VO_OSD_RESCALE_VERTICAL_PHASE_INIT              FIO_ADDRESS(VO_OSD,0x9000881C) /* read/write */
#define REG_VO_OSD_RESCALE_HORIZONTAL_COEFF                 FIO_ADDRESS(VO_OSD,0x90008820) /* write */
#define REG_VO_OSD_RESCALE_VERTICAL_COEFF                   FIO_ADDRESS(VO_OSD,0x900088A0) /* write */

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
} GH_VO_OSD_RESCALE_CONTROL_S;

typedef union { /* VO_OSD_RESCALE_WIDTH */
    U32 all;
    struct {
        U32 width                       : 14;
        U32                             : 18;
    } bitc;
} GH_VO_OSD_RESCALE_WIDTH_S;

typedef union { /* VO_OSD_RESCALE_HORIZONTAL_PHASE_INC */
    U32 all;
    struct {
        U32 inc                         : 16;
        U32                             : 16;
    } bitc;
} GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC_S;

typedef union { /* VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN */
    U32 all;
    struct {
        U32 init                        : 28;
        U32                             : 4;
    } bitc;
} GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_S;

typedef union { /* VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD */
    U32 all;
    struct {
        U32 init                        : 28;
        U32                             : 4;
    } bitc;
} GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD_S;

typedef union { /* VO_OSD_RESCALE_HEIGHT */
    U32 all;
    struct {
        U32 height                      : 14;
        U32                             : 18;
    } bitc;
} GH_VO_OSD_RESCALE_HEIGHT_S;

typedef union { /* VO_OSD_RESCALE_VERTICAL_PHASE_INC */
    U32 all;
    struct {
        U32 inc                         : 16;
        U32                             : 16;
    } bitc;
} GH_VO_OSD_RESCALE_VERTICAL_PHASE_INC_S;

typedef union { /* VO_OSD_RESCALE_VERTICAL_PHASE_INIT */
    U32 all;
    struct {
        U32 init                        : 28;
        U32                             : 4;
    } bitc;
} GH_VO_OSD_RESCALE_VERTICAL_PHASE_INIT_S;

typedef union { /* VO_OSD_RESCALE_HORIZONTAL_COEFF */
    U32 all;
    struct {
        U32 even_0_odd_4                : 8;
        U32 even_1_odd_5                : 8;
        U32 even_2                      : 8;
        U32 even_3                      : 8;
    } bitc;
} GH_VO_OSD_RESCALE_HORIZONTAL_COEFF_S;

typedef union { /* VO_OSD_RESCALE_VERTICAL_COEFF */
    U32 all;
    struct {
        U32 even_0_odd_4                : 8;
        U32 even_1_odd_5                : 8;
        U32 even_2                      : 8;
        U32 even_3                      : 8;
    } bitc;
} GH_VO_OSD_RESCALE_VERTICAL_COEFF_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern GH_VO_OSD_RESCALE_HORIZONTAL_COEFF_S    m_vo_osd_rescale_horizontal_coeff[32];
extern GH_VO_OSD_RESCALE_VERTICAL_COEFF_S      m_vo_osd_rescale_vertical_coeff[32];

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_CONTROL (read/write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_OSD_RESCALE_CONTROL'. */
void GH_VO_OSD_set_RESCALE_CONTROL(U32 data);
/*! \brief Reads the register 'VO_OSD_RESCALE_CONTROL'. */
U32  GH_VO_OSD_get_RESCALE_CONTROL(void);
/*! \brief Writes the bit group 'Enable' of register 'VO_OSD_RESCALE_CONTROL'. */
void GH_VO_OSD_set_RESCALE_CONTROL_Enable(U8 data);
/*! \brief Reads the bit group 'Enable' of register 'VO_OSD_RESCALE_CONTROL'. */
U8   GH_VO_OSD_get_RESCALE_CONTROL_Enable(void);
/*! \brief Writes the bit group 'Vertical_shift' of register 'VO_OSD_RESCALE_CONTROL'. */
void GH_VO_OSD_set_RESCALE_CONTROL_Vertical_shift(U8 data);
/*! \brief Reads the bit group 'Vertical_shift' of register 'VO_OSD_RESCALE_CONTROL'. */
U8   GH_VO_OSD_get_RESCALE_CONTROL_Vertical_shift(void);
/*! \brief Writes the bit group 'Horizontal_shift' of register 'VO_OSD_RESCALE_CONTROL'. */
void GH_VO_OSD_set_RESCALE_CONTROL_Horizontal_shift(U8 data);
/*! \brief Reads the bit group 'Horizontal_shift' of register 'VO_OSD_RESCALE_CONTROL'. */
U8   GH_VO_OSD_get_RESCALE_CONTROL_Horizontal_shift(void);
/*! \brief Writes the bit group 'Input' of register 'VO_OSD_RESCALE_CONTROL'. */
void GH_VO_OSD_set_RESCALE_CONTROL_Input(U8 data);
/*! \brief Reads the bit group 'Input' of register 'VO_OSD_RESCALE_CONTROL'. */
U8   GH_VO_OSD_get_RESCALE_CONTROL_Input(void);

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_WIDTH (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_OSD_RESCALE_WIDTH'. */
void GH_VO_OSD_set_RESCALE_WIDTH(U32 data);
/*! \brief Reads the register 'VO_OSD_RESCALE_WIDTH'. */
U32  GH_VO_OSD_get_RESCALE_WIDTH(void);
/*! \brief Writes the bit group 'width' of register 'VO_OSD_RESCALE_WIDTH'. */
void GH_VO_OSD_set_RESCALE_WIDTH_width(U16 data);
/*! \brief Reads the bit group 'width' of register 'VO_OSD_RESCALE_WIDTH'. */
U16  GH_VO_OSD_get_RESCALE_WIDTH_width(void);

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_HORIZONTAL_PHASE_INC (read/write)                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_OSD_RESCALE_HORIZONTAL_PHASE_INC'. */
void GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INC(U32 data);
/*! \brief Reads the register 'VO_OSD_RESCALE_HORIZONTAL_PHASE_INC'. */
U32  GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INC(void);
/*! \brief Writes the bit group 'inc' of register 'VO_OSD_RESCALE_HORIZONTAL_PHASE_INC'. */
void GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INC_inc(U16 data);
/*! \brief Reads the bit group 'inc' of register 'VO_OSD_RESCALE_HORIZONTAL_PHASE_INC'. */
U16  GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INC_inc(void);

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN (read/write)            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN'. */
void GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_EVEN(U32 data);
/*! \brief Reads the register 'VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN'. */
U32  GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INIT_EVEN(void);
/*! \brief Writes the bit group 'init' of register 'VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN'. */
void GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_init(U32 data);
/*! \brief Reads the bit group 'init' of register 'VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN'. */
U32  GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_init(void);

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD (read/write)             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD'. */
void GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_ODD(U32 data);
/*! \brief Reads the register 'VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD'. */
U32  GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INIT_ODD(void);
/*! \brief Writes the bit group 'init' of register 'VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD'. */
void GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_ODD_init(U32 data);
/*! \brief Reads the bit group 'init' of register 'VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD'. */
U32  GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INIT_ODD_init(void);

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_HEIGHT (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_OSD_RESCALE_HEIGHT'. */
void GH_VO_OSD_set_RESCALE_HEIGHT(U32 data);
/*! \brief Reads the register 'VO_OSD_RESCALE_HEIGHT'. */
U32  GH_VO_OSD_get_RESCALE_HEIGHT(void);
/*! \brief Writes the bit group 'height' of register 'VO_OSD_RESCALE_HEIGHT'. */
void GH_VO_OSD_set_RESCALE_HEIGHT_height(U16 data);
/*! \brief Reads the bit group 'height' of register 'VO_OSD_RESCALE_HEIGHT'. */
U16  GH_VO_OSD_get_RESCALE_HEIGHT_height(void);

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_VERTICAL_PHASE_INC (read/write)                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_OSD_RESCALE_VERTICAL_PHASE_INC'. */
void GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INC(U32 data);
/*! \brief Reads the register 'VO_OSD_RESCALE_VERTICAL_PHASE_INC'. */
U32  GH_VO_OSD_get_RESCALE_VERTICAL_PHASE_INC(void);
/*! \brief Writes the bit group 'inc' of register 'VO_OSD_RESCALE_VERTICAL_PHASE_INC'. */
void GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INC_inc(U16 data);
/*! \brief Reads the bit group 'inc' of register 'VO_OSD_RESCALE_VERTICAL_PHASE_INC'. */
U16  GH_VO_OSD_get_RESCALE_VERTICAL_PHASE_INC_inc(void);

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_VERTICAL_PHASE_INIT (read/write)                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_OSD_RESCALE_VERTICAL_PHASE_INIT'. */
void GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INIT(U32 data);
/*! \brief Reads the register 'VO_OSD_RESCALE_VERTICAL_PHASE_INIT'. */
U32  GH_VO_OSD_get_RESCALE_VERTICAL_PHASE_INIT(void);
/*! \brief Writes the bit group 'init' of register 'VO_OSD_RESCALE_VERTICAL_PHASE_INIT'. */
void GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INIT_init(U32 data);
/*! \brief Reads the bit group 'init' of register 'VO_OSD_RESCALE_VERTICAL_PHASE_INIT'. */
U32  GH_VO_OSD_get_RESCALE_VERTICAL_PHASE_INIT_init(void);

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_HORIZONTAL_COEFF (write)                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_OSD_RESCALE_HORIZONTAL_COEFF'. */
void GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF(U8 index, U32 data);
/*! \brief Reads the mirror variable of the register 'VO_OSD_RESCALE_HORIZONTAL_COEFF'. */
U32  GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF(U8 index);
/*! \brief Writes the bit group 'even_0_odd_4' of register 'VO_OSD_RESCALE_HORIZONTAL_COEFF'. */
void GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF_even_0_odd_4(U8 index, U8 data);
/*! \brief Reads the bit group 'even_0_odd_4' from the mirror variable of register 'VO_OSD_RESCALE_HORIZONTAL_COEFF'. */
U8   GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_0_odd_4(U8 index);
/*! \brief Writes the bit group 'even_1_odd_5' of register 'VO_OSD_RESCALE_HORIZONTAL_COEFF'. */
void GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF_even_1_odd_5(U8 index, U8 data);
/*! \brief Reads the bit group 'even_1_odd_5' from the mirror variable of register 'VO_OSD_RESCALE_HORIZONTAL_COEFF'. */
U8   GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_1_odd_5(U8 index);
/*! \brief Writes the bit group 'even_2' of register 'VO_OSD_RESCALE_HORIZONTAL_COEFF'. */
void GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF_even_2(U8 index, U8 data);
/*! \brief Reads the bit group 'even_2' from the mirror variable of register 'VO_OSD_RESCALE_HORIZONTAL_COEFF'. */
U8   GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_2(U8 index);
/*! \brief Writes the bit group 'even_3' of register 'VO_OSD_RESCALE_HORIZONTAL_COEFF'. */
void GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF_even_3(U8 index, U8 data);
/*! \brief Reads the bit group 'even_3' from the mirror variable of register 'VO_OSD_RESCALE_HORIZONTAL_COEFF'. */
U8   GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_3(U8 index);

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_VERTICAL_COEFF (write)                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_OSD_RESCALE_VERTICAL_COEFF'. */
void GH_VO_OSD_set_RESCALE_VERTICAL_COEFF(U8 index, U32 data);
/*! \brief Reads the mirror variable of the register 'VO_OSD_RESCALE_VERTICAL_COEFF'. */
U32  GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF(U8 index);
/*! \brief Writes the bit group 'even_0_odd_4' of register 'VO_OSD_RESCALE_VERTICAL_COEFF'. */
void GH_VO_OSD_set_RESCALE_VERTICAL_COEFF_even_0_odd_4(U8 index, U8 data);
/*! \brief Reads the bit group 'even_0_odd_4' from the mirror variable of register 'VO_OSD_RESCALE_VERTICAL_COEFF'. */
U8   GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_0_odd_4(U8 index);
/*! \brief Writes the bit group 'even_1_odd_5' of register 'VO_OSD_RESCALE_VERTICAL_COEFF'. */
void GH_VO_OSD_set_RESCALE_VERTICAL_COEFF_even_1_odd_5(U8 index, U8 data);
/*! \brief Reads the bit group 'even_1_odd_5' from the mirror variable of register 'VO_OSD_RESCALE_VERTICAL_COEFF'. */
U8   GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_1_odd_5(U8 index);
/*! \brief Writes the bit group 'even_2' of register 'VO_OSD_RESCALE_VERTICAL_COEFF'. */
void GH_VO_OSD_set_RESCALE_VERTICAL_COEFF_even_2(U8 index, U8 data);
/*! \brief Reads the bit group 'even_2' from the mirror variable of register 'VO_OSD_RESCALE_VERTICAL_COEFF'. */
U8   GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_2(U8 index);
/*! \brief Writes the bit group 'even_3' of register 'VO_OSD_RESCALE_VERTICAL_COEFF'. */
void GH_VO_OSD_set_RESCALE_VERTICAL_COEFF_even_3(U8 index, U8 data);
/*! \brief Reads the bit group 'even_3' from the mirror variable of register 'VO_OSD_RESCALE_VERTICAL_COEFF'. */
U8   GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_3(U8 index);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_VO_OSD_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_vo_osd.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_VO_OSD_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

