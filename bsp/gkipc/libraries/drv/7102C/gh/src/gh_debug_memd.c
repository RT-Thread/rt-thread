/******************************************************************************
**
** \file      gh_debug_memd.c
**
** \brief     MEMD Debug Registers.
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
#include "gh_debug_memd.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR_S   m_debug_memd_memd_cr_ic_invld_addr;

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_TRESET_ADDR (read/write)                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR = data;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR,data,data);
    #endif
}
U32  GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR,value);
    #endif
    return value;
}
void GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR_reset(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR;
    d.bitc.reset = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR_reset] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR_reset(void)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR_reset] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR,value);
    #endif
    return tmp_value.bitc.reset;
}
void GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR_suspend(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR;
    d.bitc.suspend = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR_suspend] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR_suspend(void)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR_suspend] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR,value);
    #endif
    return tmp_value.bitc.suspend;
}
void GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR_ORC_reset(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR;
    d.bitc.orc_reset = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR_ORC_reset] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR_ORC_reset(void)
{
    GH_DEBUG_MEMD_MEMD_CR_TRESET_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_TRESET_ADDR_ORC_reset] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TRESET_ADDR,value);
    #endif
    return tmp_value.bitc.orc_reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR (write)                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_DEBUG_MEMD_set_MEMD_CR_IC_INVLD_ADDR(U32 data)
{
    m_debug_memd_memd_cr_ic_invld_addr.all = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR = data;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_IC_INVLD_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR,data,data);
    #endif
}
U32  GH_DEBUG_MEMD_getm_MEMD_CR_IC_INVLD_ADDR(void)
{
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "[GH_DEBUG_MEMD_getm_MEMD_CR_IC_INVLD_ADDR] --> 0x%08x\n",
                        m_debug_memd_memd_cr_ic_invld_addr.all);
    #endif
    return m_debug_memd_memd_cr_ic_invld_addr.all;
}
void GH_DEBUG_MEMD_set_MEMD_CR_IC_INVLD_ADDR_icache(U8 data)
{
    m_debug_memd_memd_cr_ic_invld_addr.bitc.icache = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR = m_debug_memd_memd_cr_ic_invld_addr.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_IC_INVLD_ADDR_icache] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_IC_INVLD_ADDR,m_debug_memd_memd_cr_ic_invld_addr.all,m_debug_memd_memd_cr_ic_invld_addr.all);
    #endif
}
U8   GH_DEBUG_MEMD_getm_MEMD_CR_IC_INVLD_ADDR_icache(void)
{
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "[GH_DEBUG_MEMD_getm_MEMD_CR_IC_INVLD_ADDR_icache] --> 0x%08x\n",
                        m_debug_memd_memd_cr_ic_invld_addr.bitc.icache);
    #endif
    return m_debug_memd_memd_cr_ic_invld_addr.bitc.icache;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR (read/write)                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_MEMD_set_MEMD_CR_RESET_PC_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR = data;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_RESET_PC_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR,data,data);
    #endif
}
U32  GH_DEBUG_MEMD_get_MEMD_CR_RESET_PC_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_RESET_PC_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR,value);
    #endif
    return value;
}
void GH_DEBUG_MEMD_set_MEMD_CR_RESET_PC_ADDR_reset(U32 data)
{
    GH_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR;
    d.bitc.reset = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_RESET_PC_ADDR_reset] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR,d.all,d.all);
    #endif
}
U32  GH_DEBUG_MEMD_get_MEMD_CR_RESET_PC_ADDR_reset(void)
{
    GH_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_RESET_PC_ADDR_reset] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_RESET_PC_ADDR,value);
    #endif
    return tmp_value.bitc.reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR (read/write)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR = data;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,data,data);
    #endif
}
U32  GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,value);
    #endif
    return value;
}
void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MCTF(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR;
    d.bitc.mctf = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MCTF] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MCTF(void)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MCTF] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,value);
    #endif
    return tmp_value.bitc.mctf;
}
void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_ME(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR;
    d.bitc.me = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_ME] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_ME(void)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_ME] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,value);
    #endif
    return tmp_value.bitc.me;
}
void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MD(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR;
    d.bitc.md = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MD] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MD(void)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MD] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,value);
    #endif
    return tmp_value.bitc.md;
}
void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MCTF_HW(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR;
    d.bitc.mctf_hw = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MCTF_HW] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MCTF_HW(void)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MCTF_HW] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,value);
    #endif
    return tmp_value.bitc.mctf_hw;
}
void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_ME_HW(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR;
    d.bitc.me_hw = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_ME_HW] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_ME_HW(void)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_ME_HW] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,value);
    #endif
    return tmp_value.bitc.me_hw;
}
void GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MD_HW(U8 data)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR;
    d.bitc.md_hw = data;
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR = d.all;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR_MD_HW] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MD_HW(void)
{
    GH_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_CLKCTRL_ADDR_MD_HW] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CLKCTRL_ADDR,value);
    #endif
    return tmp_value.bitc.md_hw;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_TS_T0_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_MEMD_get_MEMD_CR_TS_T0_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TS_T0_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_TS_T0_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TS_T0_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_TS_T1_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_MEMD_get_MEMD_CR_TS_T1_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TS_T1_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_TS_T1_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TS_T1_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_TS_T2_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_MEMD_get_MEMD_CR_TS_T2_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TS_T2_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_TS_T2_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TS_T2_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_TS_T3_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_MEMD_get_MEMD_CR_TS_T3_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_TS_T3_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_TS_T3_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_TS_T3_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_IS_ADDR (read)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_MEMD_get_MEMD_CR_IS_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_IS_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_IS_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_IS_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_LRU_ADDR (read)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR,value);
    #endif
    return value;
}
U8   GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry0(void)
{
    GH_DEBUG_MEMD_MEMD_CR_LRU_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry0] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR,value);
    #endif
    return tmp_value.bitc.entry0;
}
U8   GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry1(void)
{
    GH_DEBUG_MEMD_MEMD_CR_LRU_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry1] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR,value);
    #endif
    return tmp_value.bitc.entry1;
}
U8   GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry2(void)
{
    GH_DEBUG_MEMD_MEMD_CR_LRU_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry2] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR,value);
    #endif
    return tmp_value.bitc.entry2;
}
U8   GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry3(void)
{
    GH_DEBUG_MEMD_MEMD_CR_LRU_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_LRU_ADDR_entry3] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_LRU_ADDR,value);
    #endif
    return tmp_value.bitc.entry3;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_PC_T0_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_T0_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_T0_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_PC_T0_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_PC_T0_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_PC_T1_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_T1_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_T1_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_PC_T1_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_PC_T1_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_PC_T2_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_T2_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_T2_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_PC_T2_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_PC_T2_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_PC_T3_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_T3_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_T3_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_PC_T3_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_PC_T3_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_PC_D_ADDR (read)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_D_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_D_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_PC_D_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_PC_D_ADDR,value);
    #endif
    return value;
}
U32  GH_DEBUG_MEMD_get_MEMD_CR_PC_D_ADDR_pc_d(void)
{
    GH_DEBUG_MEMD_MEMD_CR_PC_D_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_D_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_PC_D_ADDR_pc_d] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_PC_D_ADDR,value);
    #endif
    return tmp_value.bitc.pc_d;
}
U8   GH_DEBUG_MEMD_get_MEMD_CR_PC_D_ADDR_vld_d(void)
{
    GH_DEBUG_MEMD_MEMD_CR_PC_D_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_PC_D_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_PC_D_ADDR_vld_d] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_PC_D_ADDR,value);
    #endif
    return tmp_value.bitc.vld_d;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_OP_D_ADDR (read)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_MEMD_get_MEMD_CR_OP_D_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_OP_D_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_OP_D_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_OP_D_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_STALL_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_MEMD_get_MEMD_CR_STALL_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_STALL_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_STALL_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_STALL_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_DMAQ0_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_MEMD_get_MEMD_CR_DMAQ0_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_DMAQ0_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_DMAQ0_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_DMAQ0_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_DMAQ1_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_MEMD_get_MEMD_CR_DMAQ1_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_DMAQ1_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_DMAQ1_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_DMAQ1_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_DMAQ2_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_MEMD_get_MEMD_CR_DMAQ2_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_DMAQ2_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_DMAQ2_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_DMAQ2_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_CMDQ0_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_MEMD_get_MEMD_CR_CMDQ0_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_CMDQ0_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_CMDQ0_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_CMDQ0_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_ME_ADDR (read)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_MEMD_get_MEMD_CR_ME_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_ME_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_ME_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_ME_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_MD_ADDR (read)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_MEMD_get_MEMD_CR_MD_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_MD_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_MD_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_MD_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_MEMD_MEMD_CR_RF_ADDR (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_MEMD_set_MEMD_CR_RF_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RF_ADDR = data;
    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_MEMD_set_MEMD_CR_RF_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_RF_ADDR,data,data);
    #endif
}
U32  GH_DEBUG_MEMD_get_MEMD_CR_RF_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_MEMD_MEMD_CR_RF_ADDR);

    #if GH_DEBUG_MEMD_ENABLE_DEBUG_PRINT
    GH_DEBUG_MEMD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_MEMD_get_MEMD_CR_RF_ADDR] --> 0x%08x\n",
                        REG_DEBUG_MEMD_MEMD_CR_RF_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_DEBUG_MEMD_init(void)
{
    GH_DEBUG_MEMD_set_MEMD_CR_TRESET_ADDR((U32)0x00000000);
    GH_DEBUG_MEMD_set_MEMD_CR_IC_INVLD_ADDR((U32)0x00000000);
    GH_DEBUG_MEMD_set_MEMD_CR_RESET_PC_ADDR((U32)0x00000000);
    GH_DEBUG_MEMD_set_MEMD_CR_CLKCTRL_ADDR((U32)0x00000000);
    GH_DEBUG_MEMD_set_MEMD_CR_RF_ADDR((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

