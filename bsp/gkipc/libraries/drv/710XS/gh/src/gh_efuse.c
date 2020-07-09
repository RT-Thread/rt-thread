/******************************************************************************
**
** \file      gh_efuse.c
**
** \brief     EFUSE controller.
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
#include "gh_efuse.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register EFUSE_KEY (read)                                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_EFUSE_get_KEY(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_EFUSE_KEY + index * FIO_MOFFSET(EFUSE,0x00000004)));

    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EFUSE_get_KEY] --> 0x%08x\n",
                        (REG_EFUSE_KEY + index * FIO_MOFFSET(EFUSE,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EFUSE_Data (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_EFUSE_get_Data(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_EFUSE_DATA + index * FIO_MOFFSET(EFUSE,0x00000004)));

    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EFUSE_get_Data] --> 0x%08x\n",
                        (REG_EFUSE_DATA + index * FIO_MOFFSET(EFUSE,0x00000004)),value);
    #endif
    return value;
}
U8   GH_EFUSE_get_Data_boot_mode_sel(U8 index)
{
    GH_EFUSE_DATA_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_EFUSE_DATA + index * FIO_MOFFSET(EFUSE,0x00000004)));

    tmp_value.all = value;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EFUSE_get_Data_boot_mode_sel] --> 0x%08x\n",
                        (REG_EFUSE_DATA + index * FIO_MOFFSET(EFUSE,0x00000004)),value);
    #endif
    return tmp_value.bitc.boot_mode_sel;
}
U8   GH_EFUSE_get_Data_engine_sel(U8 index)
{
    GH_EFUSE_DATA_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_EFUSE_DATA + index * FIO_MOFFSET(EFUSE,0x00000004)));

    tmp_value.all = value;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EFUSE_get_Data_engine_sel] --> 0x%08x\n",
                        (REG_EFUSE_DATA + index * FIO_MOFFSET(EFUSE,0x00000004)),value);
    #endif
    return tmp_value.bitc.engine_sel;
}
U32  GH_EFUSE_get_Data_User_Data(U8 index)
{
    GH_EFUSE_DATA_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_EFUSE_DATA + index * FIO_MOFFSET(EFUSE,0x00000004)));

    tmp_value.all = value;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EFUSE_get_Data_User_Data] --> 0x%08x\n",
                        (REG_EFUSE_DATA + index * FIO_MOFFSET(EFUSE,0x00000004)),value);
    #endif
    return tmp_value.bitc.user_data;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EFUSE_User_Data (read)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_EFUSE_get_User_Data(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_EFUSE_USER_DATA + index * FIO_MOFFSET(EFUSE,0x00000004)));

    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EFUSE_get_User_Data] --> 0x%08x\n",
                        (REG_EFUSE_USER_DATA + index * FIO_MOFFSET(EFUSE,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EFUSE_CTRL (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_EFUSE_set_CTRL(U32 data)
{
    *(volatile U32 *)REG_EFUSE_CTRL = data;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EFUSE_set_CTRL] <-- 0x%08x\n",
                        REG_EFUSE_CTRL,data,data);
    #endif
}
U32  GH_EFUSE_get_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_EFUSE_CTRL);

    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EFUSE_get_CTRL] --> 0x%08x\n",
                        REG_EFUSE_CTRL,value);
    #endif
    return value;
}
void GH_EFUSE_set_CTRL_wr_progen_high_cnt(U16 data)
{
    GH_EFUSE_CTRL_S d;
    d.all = *(volatile U32 *)REG_EFUSE_CTRL;
    d.bitc.wr_progen_high_cnt = data;
    *(volatile U32 *)REG_EFUSE_CTRL = d.all;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EFUSE_set_CTRL_wr_progen_high_cnt] <-- 0x%08x\n",
                        REG_EFUSE_CTRL,d.all,d.all);
    #endif
}
U16  GH_EFUSE_get_CTRL_wr_progen_high_cnt(void)
{
    GH_EFUSE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_CTRL);

    tmp_value.all = value;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EFUSE_get_CTRL_wr_progen_high_cnt] --> 0x%08x\n",
                        REG_EFUSE_CTRL,value);
    #endif
    return tmp_value.bitc.wr_progen_high_cnt;
}
void GH_EFUSE_set_CTRL_wr_progen_low_cnt(U8 data)
{
    GH_EFUSE_CTRL_S d;
    d.all = *(volatile U32 *)REG_EFUSE_CTRL;
    d.bitc.wr_progen_low_cnt = data;
    *(volatile U32 *)REG_EFUSE_CTRL = d.all;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EFUSE_set_CTRL_wr_progen_low_cnt] <-- 0x%08x\n",
                        REG_EFUSE_CTRL,d.all,d.all);
    #endif
}
U8   GH_EFUSE_get_CTRL_wr_progen_low_cnt(void)
{
    GH_EFUSE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_CTRL);

    tmp_value.all = value;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EFUSE_get_CTRL_wr_progen_low_cnt] --> 0x%08x\n",
                        REG_EFUSE_CTRL,value);
    #endif
    return tmp_value.bitc.wr_progen_low_cnt;
}
void GH_EFUSE_set_CTRL_wr_addr_setup_cnt(U8 data)
{
    GH_EFUSE_CTRL_S d;
    d.all = *(volatile U32 *)REG_EFUSE_CTRL;
    d.bitc.wr_addr_setup_cnt = data;
    *(volatile U32 *)REG_EFUSE_CTRL = d.all;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EFUSE_set_CTRL_wr_addr_setup_cnt] <-- 0x%08x\n",
                        REG_EFUSE_CTRL,d.all,d.all);
    #endif
}
U8   GH_EFUSE_get_CTRL_wr_addr_setup_cnt(void)
{
    GH_EFUSE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_CTRL);

    tmp_value.all = value;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EFUSE_get_CTRL_wr_addr_setup_cnt] --> 0x%08x\n",
                        REG_EFUSE_CTRL,value);
    #endif
    return tmp_value.bitc.wr_addr_setup_cnt;
}
void GH_EFUSE_set_CTRL_rd_addr_setup_cnt(U8 data)
{
    GH_EFUSE_CTRL_S d;
    d.all = *(volatile U32 *)REG_EFUSE_CTRL;
    d.bitc.rd_addr_setup_cnt = data;
    *(volatile U32 *)REG_EFUSE_CTRL = d.all;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EFUSE_set_CTRL_rd_addr_setup_cnt] <-- 0x%08x\n",
                        REG_EFUSE_CTRL,d.all,d.all);
    #endif
}
U8   GH_EFUSE_get_CTRL_rd_addr_setup_cnt(void)
{
    GH_EFUSE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_CTRL);

    tmp_value.all = value;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EFUSE_get_CTRL_rd_addr_setup_cnt] --> 0x%08x\n",
                        REG_EFUSE_CTRL,value);
    #endif
    return tmp_value.bitc.rd_addr_setup_cnt;
}
void GH_EFUSE_set_CTRL_rd_prchg_setup_cnt(U8 data)
{
    GH_EFUSE_CTRL_S d;
    d.all = *(volatile U32 *)REG_EFUSE_CTRL;
    d.bitc.rd_prchg_setup_cnt = data;
    *(volatile U32 *)REG_EFUSE_CTRL = d.all;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EFUSE_set_CTRL_rd_prchg_setup_cnt] <-- 0x%08x\n",
                        REG_EFUSE_CTRL,d.all,d.all);
    #endif
}
U8   GH_EFUSE_get_CTRL_rd_prchg_setup_cnt(void)
{
    GH_EFUSE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_CTRL);

    tmp_value.all = value;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EFUSE_get_CTRL_rd_prchg_setup_cnt] --> 0x%08x\n",
                        REG_EFUSE_CTRL,value);
    #endif
    return tmp_value.bitc.rd_prchg_setup_cnt;
}
void GH_EFUSE_set_CTRL_rd_prchg_hold_cnt(U8 data)
{
    GH_EFUSE_CTRL_S d;
    d.all = *(volatile U32 *)REG_EFUSE_CTRL;
    d.bitc.rd_prchg_hold_cnt = data;
    *(volatile U32 *)REG_EFUSE_CTRL = d.all;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EFUSE_set_CTRL_rd_prchg_hold_cnt] <-- 0x%08x\n",
                        REG_EFUSE_CTRL,d.all,d.all);
    #endif
}
U8   GH_EFUSE_get_CTRL_rd_prchg_hold_cnt(void)
{
    GH_EFUSE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_CTRL);

    tmp_value.all = value;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EFUSE_get_CTRL_rd_prchg_hold_cnt] --> 0x%08x\n",
                        REG_EFUSE_CTRL,value);
    #endif
    return tmp_value.bitc.rd_prchg_hold_cnt;
}
void GH_EFUSE_set_CTRL_rd_sense_hold_cnt(U8 data)
{
    GH_EFUSE_CTRL_S d;
    d.all = *(volatile U32 *)REG_EFUSE_CTRL;
    d.bitc.rd_sense_hold_cnt = data;
    *(volatile U32 *)REG_EFUSE_CTRL = d.all;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EFUSE_set_CTRL_rd_sense_hold_cnt] <-- 0x%08x\n",
                        REG_EFUSE_CTRL,d.all,d.all);
    #endif
}
U8   GH_EFUSE_get_CTRL_rd_sense_hold_cnt(void)
{
    GH_EFUSE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_CTRL);

    tmp_value.all = value;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EFUSE_get_CTRL_rd_sense_hold_cnt] --> 0x%08x\n",
                        REG_EFUSE_CTRL,value);
    #endif
    return tmp_value.bitc.rd_sense_hold_cnt;
}
void GH_EFUSE_set_CTRL_Wait_rd_addr_update_cnt(U8 data)
{
    GH_EFUSE_CTRL_S d;
    d.all = *(volatile U32 *)REG_EFUSE_CTRL;
    d.bitc.wait_rd_addr_update_cnt = data;
    *(volatile U32 *)REG_EFUSE_CTRL = d.all;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EFUSE_set_CTRL_Wait_rd_addr_update_cnt] <-- 0x%08x\n",
                        REG_EFUSE_CTRL,d.all,d.all);
    #endif
}
U8   GH_EFUSE_get_CTRL_Wait_rd_addr_update_cnt(void)
{
    GH_EFUSE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_CTRL);

    tmp_value.all = value;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EFUSE_get_CTRL_Wait_rd_addr_update_cnt] --> 0x%08x\n",
                        REG_EFUSE_CTRL,value);
    #endif
    return tmp_value.bitc.wait_rd_addr_update_cnt;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EFUSE_BOOT (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_EFUSE_set_BOOT(U32 data)
{
    *(volatile U32 *)REG_EFUSE_BOOT = data;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EFUSE_set_BOOT] <-- 0x%08x\n",
                        REG_EFUSE_BOOT,data,data);
    #endif
}
U32  GH_EFUSE_get_BOOT(void)
{
    U32 value = (*(volatile U32 *)REG_EFUSE_BOOT);

    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EFUSE_get_BOOT] --> 0x%08x\n",
                        REG_EFUSE_BOOT,value);
    #endif
    return value;
}
void GH_EFUSE_set_BOOT_EN(U8 data)
{
    GH_EFUSE_BOOT_S d;
    d.all = *(volatile U32 *)REG_EFUSE_BOOT;
    d.bitc.en = data;
    *(volatile U32 *)REG_EFUSE_BOOT = d.all;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EFUSE_set_BOOT_EN] <-- 0x%08x\n",
                        REG_EFUSE_BOOT,d.all,d.all);
    #endif
}
U8   GH_EFUSE_get_BOOT_EN(void)
{
    GH_EFUSE_BOOT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_BOOT);

    tmp_value.all = value;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EFUSE_get_BOOT_EN] --> 0x%08x\n",
                        REG_EFUSE_BOOT,value);
    #endif
    return tmp_value.bitc.en;
}
void GH_EFUSE_set_BOOT_RD_OK(U8 data)
{
    GH_EFUSE_BOOT_S d;
    d.all = *(volatile U32 *)REG_EFUSE_BOOT;
    d.bitc.rd_ok = data;
    *(volatile U32 *)REG_EFUSE_BOOT = d.all;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EFUSE_set_BOOT_RD_OK] <-- 0x%08x\n",
                        REG_EFUSE_BOOT,d.all,d.all);
    #endif
}
U8   GH_EFUSE_get_BOOT_RD_OK(void)
{
    GH_EFUSE_BOOT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EFUSE_BOOT);

    tmp_value.all = value;
    #if GH_EFUSE_ENABLE_DEBUG_PRINT
    GH_EFUSE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EFUSE_get_BOOT_RD_OK] --> 0x%08x\n",
                        REG_EFUSE_BOOT,value);
    #endif
    return tmp_value.bitc.rd_ok;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_EFUSE_init(void)
{
    GH_EFUSE_set_CTRL((U32)0x4551c119);
    GH_EFUSE_set_BOOT((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

