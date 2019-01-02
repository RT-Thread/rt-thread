/******************************************************************************
**
** \file      gh_sflash.c
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
#include "gh_sflash.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register SFLASH_Data (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SFLASH_set_Data(U32 data)
{
    *(volatile U32 *)REG_SFLASH_DATA = data;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_Data] <-- 0x%08x\n",
                        REG_SFLASH_DATA,data,data);
    #endif
}
U32  GH_SFLASH_get_Data(void)
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
void GH_SFLASH_set_Command(U32 data)
{
    *(volatile U32 *)REG_SFLASH_COMMAND = data;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_Command] <-- 0x%08x\n",
                        REG_SFLASH_COMMAND,data,data);
    #endif
}
U32  GH_SFLASH_get_Command(void)
{
    U32 value = (*(volatile U32 *)REG_SFLASH_COMMAND);

    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_Command] --> 0x%08x\n",
                        REG_SFLASH_COMMAND,value);
    #endif
    return value;
}
void GH_SFLASH_set_Command_CODE(U8 data)
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
U8   GH_SFLASH_get_Command_CODE(void)
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
void GH_SFLASH_set_Command_SENDCMD(U8 data)
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
U8   GH_SFLASH_get_Command_SENDCMD(void)
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
void GH_SFLASH_set_Command_ADRNUM(U8 data)
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
U8   GH_SFLASH_get_Command_ADRNUM(void)
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
void GH_SFLASH_set_Command_DUMMYNUM(U8 data)
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
U8   GH_SFLASH_get_Command_DUMMYNUM(void)
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
void GH_SFLASH_set_Command_RWN(U8 data)
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
U8   GH_SFLASH_get_Command_RWN(void)
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
void GH_SFLASH_set_Command_CMDMODE(U8 data)
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
U8   GH_SFLASH_get_Command_CMDMODE(void)
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
void GH_SFLASH_set_Command_ADRMODE(U8 data)
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
U8   GH_SFLASH_get_Command_ADRMODE(void)
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
void GH_SFLASH_set_Command_DATAMODE(U8 data)
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
U8   GH_SFLASH_get_Command_DATAMODE(void)
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
void GH_SFLASH_set_Command_DATANUM(U8 data)
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
U8   GH_SFLASH_get_Command_DATANUM(void)
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
void GH_SFLASH_set_Command_HOLDTIME(U8 data)
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
U8   GH_SFLASH_get_Command_HOLDTIME(void)
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
void GH_SFLASH_set_CE(U32 data)
{
    *(volatile U32 *)REG_SFLASH_CE = data;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_CE] <-- 0x%08x\n",
                        REG_SFLASH_CE,data,data);
    #endif
}
U32  GH_SFLASH_get_CE(void)
{
    U32 value = (*(volatile U32 *)REG_SFLASH_CE);

    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_CE] --> 0x%08x\n",
                        REG_SFLASH_CE,value);
    #endif
    return value;
}
void GH_SFLASH_set_CE_CE(U8 data)
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
U8   GH_SFLASH_get_CE_CE(void)
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
void GH_SFLASH_set_CE_WP(U8 data)
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
U8   GH_SFLASH_get_CE_WP(void)
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
void GH_SFLASH_set_CE_HOLD(U8 data)
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
U8   GH_SFLASH_get_CE_HOLD(void)
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
void GH_SFLASH_set_CE_CEMODE(U8 data)
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
U8   GH_SFLASH_get_CE_CEMODE(void)
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
void GH_SFLASH_set_CE_WPMODE(U8 data)
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
U8   GH_SFLASH_get_CE_WPMODE(void)
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
void GH_SFLASH_set_CE_HOLDMODE(U8 data)
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
U8   GH_SFLASH_get_CE_HOLDMODE(void)
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
void GH_SFLASH_set_CE_CHSELECT(U8 data)
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
U8   GH_SFLASH_get_CE_CHSELECT(void)
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
void GH_SFLASH_set_Speed(U32 data)
{
    *(volatile U32 *)REG_SFLASH_SPEED = data;
    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SFLASH_set_Speed] <-- 0x%08x\n",
                        REG_SFLASH_SPEED,data,data);
    #endif
}
U32  GH_SFLASH_get_Speed(void)
{
    U32 value = (*(volatile U32 *)REG_SFLASH_SPEED);

    #if GH_SFLASH_ENABLE_DEBUG_PRINT
    GH_SFLASH_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SFLASH_get_Speed] --> 0x%08x\n",
                        REG_SFLASH_SPEED,value);
    #endif
    return value;
}
void GH_SFLASH_set_Speed_SF_SCLK_SEL(U8 data)
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
U8   GH_SFLASH_get_Speed_SF_SCLK_SEL(void)
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
void GH_SFLASH_init(void)
{
    GH_SFLASH_set_Data((U32)0x00000000);
    GH_SFLASH_set_Command((U32)0x00000000);
    GH_SFLASH_set_CE((U32)0x00000000);
    GH_SFLASH_set_Speed((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

