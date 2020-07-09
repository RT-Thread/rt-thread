/*!
*******************************************************************************
**
** \file      gh_sflash.h
**
** \brief     Serial Flash Interface.
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
#ifndef _GH_SFLASH_H
#define _GH_SFLASH_H

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

#define GH_SFLASH_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_SFLASH_DEBUG_PRINT_FUNCTION printk
#else
#define GH_SFLASH_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_SFLASH_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_SFLASH_DATA                                     FIO_ADDRESS(SFLASH,0x90016000) /* read/write */
#define REG_SFLASH_COMMAND                                  FIO_ADDRESS(SFLASH,0x90016004) /* read/write */
#define REG_SFLASH_CE                                       FIO_ADDRESS(SFLASH,0x90016008) /* read/write */
#define REG_SFLASH_SPEED                                    FIO_ADDRESS(SFLASH,0x9001600C) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* SFLASH_Command */
    U32 all;
    struct {
        U32 code                        : 8;
        U32 sendcmd                     : 1;
        U32 adrnum                      : 3;
        U32 dummynum                    : 3;
        U32 rwn                         : 2;
        U32 cmdmode                     : 2;
        U32 adrmode                     : 2;
        U32 datamode                    : 2;
        U32 datanum                     : 5;
        U32 holdtime                    : 2;
        U32                             : 2;
    } bitc;
} GH_SFLASH_COMMAND_S;

typedef union { /* SFLASH_CE */
    U32 all;
    struct {
        U32 ce                          : 1;
        U32 wp                          : 1;
        U32 hold                        : 1;
        U32 cemode                      : 1;
        U32 wpmode                      : 1;
        U32 holdmode                    : 1;
        U32 chselect                    : 1;
        U32                             : 25;
    } bitc;
} GH_SFLASH_CE_S;

typedef union { /* SFLASH_Speed */
    U32 all;
    struct {
        U32 sf_sclk_sel                 : 3;
        U32                             : 29;
    } bitc;
} GH_SFLASH_SPEED_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register SFLASH_Data (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SFLASH_Data'. */
void GH_SFLASH_set_Data(U32 data);
/*! \brief Reads the register 'SFLASH_Data'. */
U32  GH_SFLASH_get_Data(void);

/*----------------------------------------------------------------------------*/
/* register SFLASH_Command (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SFLASH_Command'. */
void GH_SFLASH_set_Command(U32 data);
/*! \brief Reads the register 'SFLASH_Command'. */
U32  GH_SFLASH_get_Command(void);
/*! \brief Writes the bit group 'CODE' of register 'SFLASH_Command'. */
void GH_SFLASH_set_Command_CODE(U8 data);
/*! \brief Reads the bit group 'CODE' of register 'SFLASH_Command'. */
U8   GH_SFLASH_get_Command_CODE(void);
/*! \brief Writes the bit group 'SENDCMD' of register 'SFLASH_Command'. */
void GH_SFLASH_set_Command_SENDCMD(U8 data);
/*! \brief Reads the bit group 'SENDCMD' of register 'SFLASH_Command'. */
U8   GH_SFLASH_get_Command_SENDCMD(void);
/*! \brief Writes the bit group 'ADRNUM' of register 'SFLASH_Command'. */
void GH_SFLASH_set_Command_ADRNUM(U8 data);
/*! \brief Reads the bit group 'ADRNUM' of register 'SFLASH_Command'. */
U8   GH_SFLASH_get_Command_ADRNUM(void);
/*! \brief Writes the bit group 'DUMMYNUM' of register 'SFLASH_Command'. */
void GH_SFLASH_set_Command_DUMMYNUM(U8 data);
/*! \brief Reads the bit group 'DUMMYNUM' of register 'SFLASH_Command'. */
U8   GH_SFLASH_get_Command_DUMMYNUM(void);
/*! \brief Writes the bit group 'RWN' of register 'SFLASH_Command'. */
void GH_SFLASH_set_Command_RWN(U8 data);
/*! \brief Reads the bit group 'RWN' of register 'SFLASH_Command'. */
U8   GH_SFLASH_get_Command_RWN(void);
/*! \brief Writes the bit group 'CMDMODE' of register 'SFLASH_Command'. */
void GH_SFLASH_set_Command_CMDMODE(U8 data);
/*! \brief Reads the bit group 'CMDMODE' of register 'SFLASH_Command'. */
U8   GH_SFLASH_get_Command_CMDMODE(void);
/*! \brief Writes the bit group 'ADRMODE' of register 'SFLASH_Command'. */
void GH_SFLASH_set_Command_ADRMODE(U8 data);
/*! \brief Reads the bit group 'ADRMODE' of register 'SFLASH_Command'. */
U8   GH_SFLASH_get_Command_ADRMODE(void);
/*! \brief Writes the bit group 'DATAMODE' of register 'SFLASH_Command'. */
void GH_SFLASH_set_Command_DATAMODE(U8 data);
/*! \brief Reads the bit group 'DATAMODE' of register 'SFLASH_Command'. */
U8   GH_SFLASH_get_Command_DATAMODE(void);
/*! \brief Writes the bit group 'DATANUM' of register 'SFLASH_Command'. */
void GH_SFLASH_set_Command_DATANUM(U8 data);
/*! \brief Reads the bit group 'DATANUM' of register 'SFLASH_Command'. */
U8   GH_SFLASH_get_Command_DATANUM(void);
/*! \brief Writes the bit group 'HOLDTIME' of register 'SFLASH_Command'. */
void GH_SFLASH_set_Command_HOLDTIME(U8 data);
/*! \brief Reads the bit group 'HOLDTIME' of register 'SFLASH_Command'. */
U8   GH_SFLASH_get_Command_HOLDTIME(void);

/*----------------------------------------------------------------------------*/
/* register SFLASH_CE (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SFLASH_CE'. */
void GH_SFLASH_set_CE(U32 data);
/*! \brief Reads the register 'SFLASH_CE'. */
U32  GH_SFLASH_get_CE(void);
/*! \brief Writes the bit group 'CE' of register 'SFLASH_CE'. */
void GH_SFLASH_set_CE_CE(U8 data);
/*! \brief Reads the bit group 'CE' of register 'SFLASH_CE'. */
U8   GH_SFLASH_get_CE_CE(void);
/*! \brief Writes the bit group 'WP' of register 'SFLASH_CE'. */
void GH_SFLASH_set_CE_WP(U8 data);
/*! \brief Reads the bit group 'WP' of register 'SFLASH_CE'. */
U8   GH_SFLASH_get_CE_WP(void);
/*! \brief Writes the bit group 'HOLD' of register 'SFLASH_CE'. */
void GH_SFLASH_set_CE_HOLD(U8 data);
/*! \brief Reads the bit group 'HOLD' of register 'SFLASH_CE'. */
U8   GH_SFLASH_get_CE_HOLD(void);
/*! \brief Writes the bit group 'CEMODE' of register 'SFLASH_CE'. */
void GH_SFLASH_set_CE_CEMODE(U8 data);
/*! \brief Reads the bit group 'CEMODE' of register 'SFLASH_CE'. */
U8   GH_SFLASH_get_CE_CEMODE(void);
/*! \brief Writes the bit group 'WPMODE' of register 'SFLASH_CE'. */
void GH_SFLASH_set_CE_WPMODE(U8 data);
/*! \brief Reads the bit group 'WPMODE' of register 'SFLASH_CE'. */
U8   GH_SFLASH_get_CE_WPMODE(void);
/*! \brief Writes the bit group 'HOLDMODE' of register 'SFLASH_CE'. */
void GH_SFLASH_set_CE_HOLDMODE(U8 data);
/*! \brief Reads the bit group 'HOLDMODE' of register 'SFLASH_CE'. */
U8   GH_SFLASH_get_CE_HOLDMODE(void);
/*! \brief Writes the bit group 'CHSELECT' of register 'SFLASH_CE'. */
void GH_SFLASH_set_CE_CHSELECT(U8 data);
/*! \brief Reads the bit group 'CHSELECT' of register 'SFLASH_CE'. */
U8   GH_SFLASH_get_CE_CHSELECT(void);

/*----------------------------------------------------------------------------*/
/* register SFLASH_Speed (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SFLASH_Speed'. */
void GH_SFLASH_set_Speed(U32 data);
/*! \brief Reads the register 'SFLASH_Speed'. */
U32  GH_SFLASH_get_Speed(void);
/*! \brief Writes the bit group 'SF_SCLK_SEL' of register 'SFLASH_Speed'. */
void GH_SFLASH_set_Speed_SF_SCLK_SEL(U8 data);
/*! \brief Reads the bit group 'SF_SCLK_SEL' of register 'SFLASH_Speed'. */
U8   GH_SFLASH_get_Speed_SF_SCLK_SEL(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_SFLASH_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_sflash.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_SFLASH_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

