/*!
*******************************************************************************
**
** \file      gh_sflash.h
**
** \brief     Serial Flash Interface.
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
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SFLASH_Data'. */
void GH_SFLASH_set_Data(U32 data);
/*! \brief Reads the register 'SFLASH_Data'. */
U32  GH_SFLASH_get_Data(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SFLASH_set_Data(U32 data)
{
    *(volatile U32 *)REG_SFLASH_DATA = data;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_Data] <-- 0x%08x\n",
                        REG_SFLASH_DATA,data,data);
    #endif
}
GH_INLINE U32  GH_SFLASH_get_Data(void)
{
    U32 value = (*(volatile U32 *)REG_SFLASH_DATA);

    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_Data] --> 0x%08x\n",
                        REG_SFLASH_DATA,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SFLASH_Command (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
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
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SFLASH_set_Command(U32 data)
{
    *(volatile U32 *)REG_SFLASH_COMMAND = data;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_Command] <-- 0x%08x\n",
                        REG_SFLASH_COMMAND,data,data);
    #endif
}
GH_INLINE U32  GH_SFLASH_get_Command(void)
{
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND);

    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_Command] --> 0x%08x\n",
                        REG_SFLASH_COMMAND,value);
    #endif
    return value;
}
GH_INLINE void GH_SFLASH_set_Command_CODE(U8 data)
{
    GH_SFLASH_COMMAND_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND;
    d.bitc.code = data;
    *(volatile U32 *)REG_SFLASH_COMMAND = d.all;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_Command_CODE] <-- 0x%08x\n",
                        REG_SFLASH_COMMAND,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SFLASH_get_Command_CODE(void)
{
    GH_SFLASH_COMMAND_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND);

    tmp_value.all = value;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_Command_CODE] --> 0x%08x\n",
                        REG_SFLASH_COMMAND,value);
    #endif
    return tmp_value.bitc.code;
}
GH_INLINE void GH_SFLASH_set_Command_SENDCMD(U8 data)
{
    GH_SFLASH_COMMAND_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND;
    d.bitc.sendcmd = data;
    *(volatile U32 *)REG_SFLASH_COMMAND = d.all;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_Command_SENDCMD] <-- 0x%08x\n",
                        REG_SFLASH_COMMAND,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SFLASH_get_Command_SENDCMD(void)
{
    GH_SFLASH_COMMAND_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND);

    tmp_value.all = value;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_Command_SENDCMD] --> 0x%08x\n",
                        REG_SFLASH_COMMAND,value);
    #endif
    return tmp_value.bitc.sendcmd;
}
GH_INLINE void GH_SFLASH_set_Command_ADRNUM(U8 data)
{
    GH_SFLASH_COMMAND_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND;
    d.bitc.adrnum = data;
    *(volatile U32 *)REG_SFLASH_COMMAND = d.all;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_Command_ADRNUM] <-- 0x%08x\n",
                        REG_SFLASH_COMMAND,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SFLASH_get_Command_ADRNUM(void)
{
    GH_SFLASH_COMMAND_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND);

    tmp_value.all = value;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_Command_ADRNUM] --> 0x%08x\n",
                        REG_SFLASH_COMMAND,value);
    #endif
    return tmp_value.bitc.adrnum;
}
GH_INLINE void GH_SFLASH_set_Command_DUMMYNUM(U8 data)
{
    GH_SFLASH_COMMAND_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND;
    d.bitc.dummynum = data;
    *(volatile U32 *)REG_SFLASH_COMMAND = d.all;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_Command_DUMMYNUM] <-- 0x%08x\n",
                        REG_SFLASH_COMMAND,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SFLASH_get_Command_DUMMYNUM(void)
{
    GH_SFLASH_COMMAND_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND);

    tmp_value.all = value;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_Command_DUMMYNUM] --> 0x%08x\n",
                        REG_SFLASH_COMMAND,value);
    #endif
    return tmp_value.bitc.dummynum;
}
GH_INLINE void GH_SFLASH_set_Command_RWN(U8 data)
{
    GH_SFLASH_COMMAND_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND;
    d.bitc.rwn = data;
    *(volatile U32 *)REG_SFLASH_COMMAND = d.all;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_Command_RWN] <-- 0x%08x\n",
                        REG_SFLASH_COMMAND,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SFLASH_get_Command_RWN(void)
{
    GH_SFLASH_COMMAND_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND);

    tmp_value.all = value;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_Command_RWN] --> 0x%08x\n",
                        REG_SFLASH_COMMAND,value);
    #endif
    return tmp_value.bitc.rwn;
}
GH_INLINE void GH_SFLASH_set_Command_CMDMODE(U8 data)
{
    GH_SFLASH_COMMAND_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND;
    d.bitc.cmdmode = data;
    *(volatile U32 *)REG_SFLASH_COMMAND = d.all;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_Command_CMDMODE] <-- 0x%08x\n",
                        REG_SFLASH_COMMAND,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SFLASH_get_Command_CMDMODE(void)
{
    GH_SFLASH_COMMAND_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND);

    tmp_value.all = value;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_Command_CMDMODE] --> 0x%08x\n",
                        REG_SFLASH_COMMAND,value);
    #endif
    return tmp_value.bitc.cmdmode;
}
GH_INLINE void GH_SFLASH_set_Command_ADRMODE(U8 data)
{
    GH_SFLASH_COMMAND_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND;
    d.bitc.adrmode = data;
    *(volatile U32 *)REG_SFLASH_COMMAND = d.all;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_Command_ADRMODE] <-- 0x%08x\n",
                        REG_SFLASH_COMMAND,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SFLASH_get_Command_ADRMODE(void)
{
    GH_SFLASH_COMMAND_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND);

    tmp_value.all = value;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_Command_ADRMODE] --> 0x%08x\n",
                        REG_SFLASH_COMMAND,value);
    #endif
    return tmp_value.bitc.adrmode;
}
GH_INLINE void GH_SFLASH_set_Command_DATAMODE(U8 data)
{
    GH_SFLASH_COMMAND_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND;
    d.bitc.datamode = data;
    *(volatile U32 *)REG_SFLASH_COMMAND = d.all;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_Command_DATAMODE] <-- 0x%08x\n",
                        REG_SFLASH_COMMAND,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SFLASH_get_Command_DATAMODE(void)
{
    GH_SFLASH_COMMAND_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND);

    tmp_value.all = value;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_Command_DATAMODE] --> 0x%08x\n",
                        REG_SFLASH_COMMAND,value);
    #endif
    return tmp_value.bitc.datamode;
}
GH_INLINE void GH_SFLASH_set_Command_DATANUM(U8 data)
{
    GH_SFLASH_COMMAND_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND;
    d.bitc.datanum = data;
    *(volatile U32 *)REG_SFLASH_COMMAND = d.all;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_Command_DATANUM] <-- 0x%08x\n",
                        REG_SFLASH_COMMAND,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SFLASH_get_Command_DATANUM(void)
{
    GH_SFLASH_COMMAND_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND);

    tmp_value.all = value;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_Command_DATANUM] --> 0x%08x\n",
                        REG_SFLASH_COMMAND,value);
    #endif
    return tmp_value.bitc.datanum;
}
GH_INLINE void GH_SFLASH_set_Command_HOLDTIME(U8 data)
{
    GH_SFLASH_COMMAND_S d;
    d.all = *(volatile U32 *)REG_SFLASH_COMMAND;
    d.bitc.holdtime = data;
    *(volatile U32 *)REG_SFLASH_COMMAND = d.all;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_Command_HOLDTIME] <-- 0x%08x\n",
                        REG_SFLASH_COMMAND,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SFLASH_get_Command_HOLDTIME(void)
{
    GH_SFLASH_COMMAND_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND);

    tmp_value.all = value;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_Command_HOLDTIME] --> 0x%08x\n",
                        REG_SFLASH_COMMAND,value);
    #endif
    return tmp_value.bitc.holdtime;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SFLASH_CE (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
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
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SFLASH_set_CE(U32 data)
{
    *(volatile U32 *)REG_SFLASH_CE = data;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_CE] <-- 0x%08x\n",
                        REG_SFLASH_CE,data,data);
    #endif
}
GH_INLINE U32  GH_SFLASH_get_CE(void)
{
    U32 value = (*(volatile U32 *)REG_SFLASH_CE);

    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_CE] --> 0x%08x\n",
                        REG_SFLASH_CE,value);
    #endif
    return value;
}
GH_INLINE void GH_SFLASH_set_CE_CE(U8 data)
{
    GH_SFLASH_CE_S d;
    d.all = *(volatile U32 *)REG_SFLASH_CE;
    d.bitc.ce = data;
    *(volatile U32 *)REG_SFLASH_CE = d.all;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_CE_CE] <-- 0x%08x\n",
                        REG_SFLASH_CE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SFLASH_get_CE_CE(void)
{
    GH_SFLASH_CE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_CE);

    tmp_value.all = value;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_CE_CE] --> 0x%08x\n",
                        REG_SFLASH_CE,value);
    #endif
    return tmp_value.bitc.ce;
}
GH_INLINE void GH_SFLASH_set_CE_WP(U8 data)
{
    GH_SFLASH_CE_S d;
    d.all = *(volatile U32 *)REG_SFLASH_CE;
    d.bitc.wp = data;
    *(volatile U32 *)REG_SFLASH_CE = d.all;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_CE_WP] <-- 0x%08x\n",
                        REG_SFLASH_CE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SFLASH_get_CE_WP(void)
{
    GH_SFLASH_CE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_CE);

    tmp_value.all = value;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_CE_WP] --> 0x%08x\n",
                        REG_SFLASH_CE,value);
    #endif
    return tmp_value.bitc.wp;
}
GH_INLINE void GH_SFLASH_set_CE_HOLD(U8 data)
{
    GH_SFLASH_CE_S d;
    d.all = *(volatile U32 *)REG_SFLASH_CE;
    d.bitc.hold = data;
    *(volatile U32 *)REG_SFLASH_CE = d.all;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_CE_HOLD] <-- 0x%08x\n",
                        REG_SFLASH_CE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SFLASH_get_CE_HOLD(void)
{
    GH_SFLASH_CE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_CE);

    tmp_value.all = value;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_CE_HOLD] --> 0x%08x\n",
                        REG_SFLASH_CE,value);
    #endif
    return tmp_value.bitc.hold;
}
GH_INLINE void GH_SFLASH_set_CE_CEMODE(U8 data)
{
    GH_SFLASH_CE_S d;
    d.all = *(volatile U32 *)REG_SFLASH_CE;
    d.bitc.cemode = data;
    *(volatile U32 *)REG_SFLASH_CE = d.all;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_CE_CEMODE] <-- 0x%08x\n",
                        REG_SFLASH_CE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SFLASH_get_CE_CEMODE(void)
{
    GH_SFLASH_CE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_CE);

    tmp_value.all = value;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_CE_CEMODE] --> 0x%08x\n",
                        REG_SFLASH_CE,value);
    #endif
    return tmp_value.bitc.cemode;
}
GH_INLINE void GH_SFLASH_set_CE_WPMODE(U8 data)
{
    GH_SFLASH_CE_S d;
    d.all = *(volatile U32 *)REG_SFLASH_CE;
    d.bitc.wpmode = data;
    *(volatile U32 *)REG_SFLASH_CE = d.all;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_CE_WPMODE] <-- 0x%08x\n",
                        REG_SFLASH_CE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SFLASH_get_CE_WPMODE(void)
{
    GH_SFLASH_CE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_CE);

    tmp_value.all = value;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_CE_WPMODE] --> 0x%08x\n",
                        REG_SFLASH_CE,value);
    #endif
    return tmp_value.bitc.wpmode;
}
GH_INLINE void GH_SFLASH_set_CE_HOLDMODE(U8 data)
{
    GH_SFLASH_CE_S d;
    d.all = *(volatile U32 *)REG_SFLASH_CE;
    d.bitc.holdmode = data;
    *(volatile U32 *)REG_SFLASH_CE = d.all;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_CE_HOLDMODE] <-- 0x%08x\n",
                        REG_SFLASH_CE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SFLASH_get_CE_HOLDMODE(void)
{
    GH_SFLASH_CE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_CE);

    tmp_value.all = value;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_CE_HOLDMODE] --> 0x%08x\n",
                        REG_SFLASH_CE,value);
    #endif
    return tmp_value.bitc.holdmode;
}
GH_INLINE void GH_SFLASH_set_CE_CHSELECT(U8 data)
{
    GH_SFLASH_CE_S d;
    d.all = *(volatile U32 *)REG_SFLASH_CE;
    d.bitc.chselect = data;
    *(volatile U32 *)REG_SFLASH_CE = d.all;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_CE_CHSELECT] <-- 0x%08x\n",
                        REG_SFLASH_CE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SFLASH_get_CE_CHSELECT(void)
{
    GH_SFLASH_CE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_CE);

    tmp_value.all = value;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_CE_CHSELECT] --> 0x%08x\n",
                        REG_SFLASH_CE,value);
    #endif
    return tmp_value.bitc.chselect;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SFLASH_Speed (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SFLASH_Speed'. */
void GH_SFLASH_set_Speed(U32 data);
/*! \brief Reads the register 'SFLASH_Speed'. */
U32  GH_SFLASH_get_Speed(void);
/*! \brief Writes the bit group 'SF_SCLK_SEL' of register 'SFLASH_Speed'. */
void GH_SFLASH_set_Speed_SF_SCLK_SEL(U8 data);
/*! \brief Reads the bit group 'SF_SCLK_SEL' of register 'SFLASH_Speed'. */
U8   GH_SFLASH_get_Speed_SF_SCLK_SEL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SFLASH_set_Speed(U32 data)
{
    *(volatile U32 *)REG_SFLASH_SPEED = data;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_Speed] <-- 0x%08x\n",
                        REG_SFLASH_SPEED,data,data);
    #endif
}
GH_INLINE U32  GH_SFLASH_get_Speed(void)
{
    U32 value = (*(volatile U32 *)REG_SFLASH_SPEED);

    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_Speed] --> 0x%08x\n",
                        REG_SFLASH_SPEED,value);
    #endif
    return value;
}
GH_INLINE void GH_SFLASH_set_Speed_SF_SCLK_SEL(U8 data)
{
    GH_SFLASH_SPEED_S d;
    d.all = *(volatile U32 *)REG_SFLASH_SPEED;
    d.bitc.sf_sclk_sel = data;
    *(volatile U32 *)REG_SFLASH_SPEED = d.all;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_Speed_SF_SCLK_SEL] <-- 0x%08x\n",
                        REG_SFLASH_SPEED,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SFLASH_get_Speed_SF_SCLK_SEL(void)
{
    GH_SFLASH_SPEED_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SFLASH_SPEED);

    tmp_value.all = value;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_Speed_SF_SCLK_SEL] --> 0x%08x\n",
                        REG_SFLASH_SPEED,value);
    #endif
    return tmp_value.bitc.sf_sclk_sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_SFLASH_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_SFLASH_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

