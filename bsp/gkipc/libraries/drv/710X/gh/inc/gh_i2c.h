/*!
*******************************************************************************
**
** \file      gh_i2c.h
**
** \brief     I2C Interface..
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
#ifndef _GH_I2C_H
#define _GH_I2C_H

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

#define GH_I2C_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_I2C_DEBUG_PRINT_FUNCTION printk
#else
#define GH_I2C_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_I2C_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_I2C_ENABLE                                      FIO_ADDRESS(I2C,0xa0003000) /* read/write */
#define REG_I2C_CONTROL                                     FIO_ADDRESS(I2C,0xa0003004) /* read/write */
#define REG_I2C_DATA                                        FIO_ADDRESS(I2C,0xa0003008) /* read/write */
#define REG_I2C_STATUS                                      FIO_ADDRESS(I2C,0xa000300C) /* read */
#define REG_I2C_PRESCALEL                                   FIO_ADDRESS(I2C,0xa0003010) /* read/write */
#define REG_I2C_PRESCALEH                                   FIO_ADDRESS(I2C,0xa0003014) /* read/write */
#define REG_I2C_FMCONTROL                                   FIO_ADDRESS(I2C,0xa0003018) /* read/write */
#define REG_I2C_FMDATA                                      FIO_ADDRESS(I2C,0xa000301C) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* I2C_ENABLE */
    U32 all;
    struct {
        U32 en                          : 1;
        U32                             : 31;
    } bitc;
} GH_I2C_ENABLE_S;

typedef union { /* I2C_CONTROL */
    U32 all;
    struct {
        U32 ack                         : 1;
        U32 intflag                     : 1;
        U32 start                       : 1;
        U32 stop                        : 1;
        U32                             : 28;
    } bitc;
} GH_I2C_CONTROL_S;

typedef union { /* I2C_DATA */
    U32 all;
    struct {
        U32 data                        : 8;
        U32                             : 24;
    } bitc;
} GH_I2C_DATA_S;

typedef union { /* I2C_STATUS */
    U32 all;
    struct {
        U32 mode                        : 1;
        U32                             : 31;
    } bitc;
} GH_I2C_STATUS_S;

typedef union { /* I2C_PRESCALEL */
    U32 all;
    struct {
        U32 scale                       : 8;
        U32                             : 24;
    } bitc;
} GH_I2C_PRESCALEL_S;

typedef union { /* I2C_PRESCALEH */
    U32 all;
    struct {
        U32 scale                       : 8;
        U32                             : 24;
    } bitc;
} GH_I2C_PRESCALEH_S;

typedef union { /* I2C_FMCONTROL */
    U32 all;
    struct {
        U32                             : 1;
        U32 is                          : 1;
        U32 start                       : 1;
        U32 stop                        : 1;
        U32                             : 28;
    } bitc;
} GH_I2C_FMCONTROL_S;

typedef union { /* I2C_FMDATA */
    U32 all;
    struct {
        U32 data                        : 8;
        U32                             : 24;
    } bitc;
} GH_I2C_FMDATA_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register I2C_ENABLE (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2C_ENABLE'. */
void GH_I2C_set_ENABLE(U8 index, U32 data);
/*! \brief Reads the register 'I2C_ENABLE'. */
U32  GH_I2C_get_ENABLE(U8 index);
/*! \brief Writes the bit group 'en' of register 'I2C_ENABLE'. */
void GH_I2C_set_ENABLE_en(U8 index, U8 data);
/*! \brief Reads the bit group 'en' of register 'I2C_ENABLE'. */
U8   GH_I2C_get_ENABLE_en(U8 index);

/*----------------------------------------------------------------------------*/
/* register I2C_CONTROL (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2C_CONTROL'. */
void GH_I2C_set_CONTROL(U8 index, U32 data);
/*! \brief Reads the register 'I2C_CONTROL'. */
U32  GH_I2C_get_CONTROL(U8 index);
/*! \brief Writes the bit group 'ack' of register 'I2C_CONTROL'. */
void GH_I2C_set_CONTROL_ack(U8 index, U8 data);
/*! \brief Reads the bit group 'ack' of register 'I2C_CONTROL'. */
U8   GH_I2C_get_CONTROL_ack(U8 index);
/*! \brief Writes the bit group 'IntFlag' of register 'I2C_CONTROL'. */
void GH_I2C_set_CONTROL_IntFlag(U8 index, U8 data);
/*! \brief Reads the bit group 'IntFlag' of register 'I2C_CONTROL'. */
U8   GH_I2C_get_CONTROL_IntFlag(U8 index);
/*! \brief Writes the bit group 'start' of register 'I2C_CONTROL'. */
void GH_I2C_set_CONTROL_start(U8 index, U8 data);
/*! \brief Reads the bit group 'start' of register 'I2C_CONTROL'. */
U8   GH_I2C_get_CONTROL_start(U8 index);
/*! \brief Writes the bit group 'stop' of register 'I2C_CONTROL'. */
void GH_I2C_set_CONTROL_stop(U8 index, U8 data);
/*! \brief Reads the bit group 'stop' of register 'I2C_CONTROL'. */
U8   GH_I2C_get_CONTROL_stop(U8 index);

/*----------------------------------------------------------------------------*/
/* register I2C_DATA (read/write)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2C_DATA'. */
void GH_I2C_set_DATA(U8 index, U32 data);
/*! \brief Reads the register 'I2C_DATA'. */
U32  GH_I2C_get_DATA(U8 index);
/*! \brief Writes the bit group 'Data' of register 'I2C_DATA'. */
void GH_I2C_set_DATA_Data(U8 index, U8 data);
/*! \brief Reads the bit group 'Data' of register 'I2C_DATA'. */
U8   GH_I2C_get_DATA_Data(U8 index);

/*----------------------------------------------------------------------------*/
/* register I2C_STATUS (read)                                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'I2C_STATUS'. */
U32  GH_I2C_get_STATUS(U8 index);
/*! \brief Reads the bit group 'mode' of register 'I2C_STATUS'. */
U8   GH_I2C_get_STATUS_mode(U8 index);

/*----------------------------------------------------------------------------*/
/* register I2C_PRESCALEL (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2C_PRESCALEL'. */
void GH_I2C_set_PRESCALEL(U8 index, U32 data);
/*! \brief Reads the register 'I2C_PRESCALEL'. */
U32  GH_I2C_get_PRESCALEL(U8 index);
/*! \brief Writes the bit group 'scale' of register 'I2C_PRESCALEL'. */
void GH_I2C_set_PRESCALEL_scale(U8 index, U8 data);
/*! \brief Reads the bit group 'scale' of register 'I2C_PRESCALEL'. */
U8   GH_I2C_get_PRESCALEL_scale(U8 index);

/*----------------------------------------------------------------------------*/
/* register I2C_PRESCALEH (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2C_PRESCALEH'. */
void GH_I2C_set_PRESCALEH(U8 index, U32 data);
/*! \brief Reads the register 'I2C_PRESCALEH'. */
U32  GH_I2C_get_PRESCALEH(U8 index);
/*! \brief Writes the bit group 'scale' of register 'I2C_PRESCALEH'. */
void GH_I2C_set_PRESCALEH_scale(U8 index, U8 data);
/*! \brief Reads the bit group 'scale' of register 'I2C_PRESCALEH'. */
U8   GH_I2C_get_PRESCALEH_scale(U8 index);

/*----------------------------------------------------------------------------*/
/* register I2C_FMCONTROL (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2C_FMCONTROL'. */
void GH_I2C_set_FMCONTROL(U8 index, U32 data);
/*! \brief Reads the register 'I2C_FMCONTROL'. */
U32  GH_I2C_get_FMCONTROL(U8 index);
/*! \brief Writes the bit group 'is' of register 'I2C_FMCONTROL'. */
void GH_I2C_set_FMCONTROL_is(U8 index, U8 data);
/*! \brief Reads the bit group 'is' of register 'I2C_FMCONTROL'. */
U8   GH_I2C_get_FMCONTROL_is(U8 index);
/*! \brief Writes the bit group 'start' of register 'I2C_FMCONTROL'. */
void GH_I2C_set_FMCONTROL_start(U8 index, U8 data);
/*! \brief Reads the bit group 'start' of register 'I2C_FMCONTROL'. */
U8   GH_I2C_get_FMCONTROL_start(U8 index);
/*! \brief Writes the bit group 'stop' of register 'I2C_FMCONTROL'. */
void GH_I2C_set_FMCONTROL_stop(U8 index, U8 data);
/*! \brief Reads the bit group 'stop' of register 'I2C_FMCONTROL'. */
U8   GH_I2C_get_FMCONTROL_stop(U8 index);

/*----------------------------------------------------------------------------*/
/* register I2C_FMDATA (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2C_FMDATA'. */
void GH_I2C_set_FMDATA(U8 index, U32 data);
/*! \brief Reads the register 'I2C_FMDATA'. */
U32  GH_I2C_get_FMDATA(U8 index);
/*! \brief Writes the bit group 'Data' of register 'I2C_FMDATA'. */
void GH_I2C_set_FMDATA_Data(U8 index, U8 data);
/*! \brief Reads the bit group 'Data' of register 'I2C_FMDATA'. */
U8   GH_I2C_get_FMDATA_Data(U8 index);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_I2C_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_i2c.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_I2C_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

