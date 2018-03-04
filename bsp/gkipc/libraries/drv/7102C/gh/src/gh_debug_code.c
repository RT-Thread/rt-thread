/******************************************************************************
**
** \file      gh_debug_code.c
**
** \brief     CODE Debug Registers.
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
#include "gh_debug_code.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR_S   m_debug_code_code_cr_ic_invld_addr;

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_TRESET_ADDR (read/write)                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_CODE_set_CODE_CR_TRESET_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TRESET_ADDR = data;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_CODE_set_CODE_CR_TRESET_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TRESET_ADDR,data,data);
    #endif
}
U32  GH_DEBUG_CODE_get_CODE_CR_TRESET_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TRESET_ADDR);

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TRESET_ADDR] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TRESET_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_IC_INVLD_ADDR (write)                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_DEBUG_CODE_set_CODE_CR_IC_INVLD_ADDR(U32 data)
{
    m_debug_code_code_cr_ic_invld_addr.all = data;
    *(volatile U32 *)REG_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR = data;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_CODE_set_CODE_CR_IC_INVLD_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR,data,data);
    #endif
}
U32  GH_DEBUG_CODE_getm_CODE_CR_IC_INVLD_ADDR(void)
{
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "[GH_DEBUG_CODE_getm_CODE_CR_IC_INVLD_ADDR] --> 0x%08x\n",
                        m_debug_code_code_cr_ic_invld_addr.all);
    #endif
    return m_debug_code_code_cr_ic_invld_addr.all;
}
void GH_DEBUG_CODE_set_CODE_CR_IC_INVLD_ADDR_invalid_icache(U8 data)
{
    m_debug_code_code_cr_ic_invld_addr.bitc.invalid_icache = data;
    *(volatile U32 *)REG_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR = m_debug_code_code_cr_ic_invld_addr.all;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_CODE_set_CODE_CR_IC_INVLD_ADDR_invalid_icache] <-- 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_IC_INVLD_ADDR,m_debug_code_code_cr_ic_invld_addr.all,m_debug_code_code_cr_ic_invld_addr.all);
    #endif
}
U8   GH_DEBUG_CODE_getm_CODE_CR_IC_INVLD_ADDR_invalid_icache(void)
{
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "[GH_DEBUG_CODE_getm_CODE_CR_IC_INVLD_ADDR_invalid_icache] --> 0x%08x\n",
                        m_debug_code_code_cr_ic_invld_addr.bitc.invalid_icache);
    #endif
    return m_debug_code_code_cr_ic_invld_addr.bitc.invalid_icache;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_RESET_PC_ADDR (read/write)                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_CODE_set_CODE_CR_RESET_PC_ADDR(U32 data)
{
    *(volatile U32 *)REG_DEBUG_CODE_CODE_CR_RESET_PC_ADDR = data;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_CODE_set_CODE_CR_RESET_PC_ADDR] <-- 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_RESET_PC_ADDR,data,data);
    #endif
}
U32  GH_DEBUG_CODE_get_CODE_CR_RESET_PC_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_RESET_PC_ADDR);

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_RESET_PC_ADDR] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_RESET_PC_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_TS_ADDR (read)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_CODE_get_CODE_CR_TS_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return value;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_run(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_run] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t0_run;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_restmr(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_restmr] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t0_restmr;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_dmab4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_dmab4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t0_dmab4;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_codeb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_codeb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t0_codeb4;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_sendb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_sendb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t0_sendb4;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_recb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t0_recb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t0_recb4;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_run(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_run] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t1_run;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_restmr(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_restmr] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t1_restmr;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_dmab4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_dmab4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t1_dmab4;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_codeb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_codeb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t1_codeb4;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_sendb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_sendb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t1_sendb4;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_recb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t1_recb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t1_recb4;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_run(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_run] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t2_run;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_restmr(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_restmr] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t2_restmr;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_dmab4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_dmab4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t2_dmab4;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_codeb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_codeb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t2_codeb4;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_sendb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_sendb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t2_sendb4;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_recb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t2_recb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t2_recb4;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_run(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_run] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t3_run;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_restmr(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_restmr] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t3_restmr;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_dmab4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_dmab4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t3_dmab4;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_codeb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_codeb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t3_codeb4;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_sendb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_sendb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t3_sendb4;
}
U8   GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_recb4(void)
{
    GH_DEBUG_CODE_CODE_CR_TS_ADDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_TS_ADDR);

    tmp_value.all = value;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_TS_ADDR_ts_t3_recb4] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_TS_ADDR,value);
    #endif
    return tmp_value.bitc.ts_t3_recb4;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_PC_T0_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_CODE_get_CODE_CR_PC_T0_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_PC_T0_ADDR);

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_PC_T0_ADDR] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_PC_T0_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_PC_T1_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_CODE_get_CODE_CR_PC_T1_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_PC_T1_ADDR);

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_PC_T1_ADDR] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_PC_T1_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_PC_T2_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_CODE_get_CODE_CR_PC_T2_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_PC_T2_ADDR);

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_PC_T2_ADDR] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_PC_T2_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_PC_T3_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_CODE_get_CODE_CR_PC_T3_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_PC_T3_ADDR);

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_PC_T3_ADDR] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_PC_T3_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_STALL_ADDR (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_CODE_get_CODE_CR_STALL_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_STALL_ADDR);

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_STALL_ADDR] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_STALL_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_RF_ADDR (read)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_CODE_get_CODE_CR_RF_ADDR(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_CODE_CODE_CR_RF_ADDR);

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_RF_ADDR] --> 0x%08x\n",
                        REG_DEBUG_CODE_CODE_CR_RF_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_CODE_CODE_CR_DC_ADDR (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_CODE_set_CODE_CR_DC_ADDR(U16 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_CODE_CODE_CR_DC_ADDR + index * FIO_MOFFSET(DEBUG_CODE,0x00000004)) = data;
    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_CODE_set_CODE_CR_DC_ADDR] <-- 0x%08x\n",
                        (REG_DEBUG_CODE_CODE_CR_DC_ADDR + index * FIO_MOFFSET(DEBUG_CODE,0x00000004)),data,data);
    #endif
}
U32  GH_DEBUG_CODE_get_CODE_CR_DC_ADDR(U16 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_CODE_CODE_CR_DC_ADDR + index * FIO_MOFFSET(DEBUG_CODE,0x00000004)));

    #if GH_DEBUG_CODE_ENABLE_DEBUG_PRINT
    GH_DEBUG_CODE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_CODE_get_CODE_CR_DC_ADDR] --> 0x%08x\n",
                        (REG_DEBUG_CODE_CODE_CR_DC_ADDR + index * FIO_MOFFSET(DEBUG_CODE,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_DEBUG_CODE_init(void)
{
    int i;

    GH_DEBUG_CODE_set_CODE_CR_TRESET_ADDR((U32)0x00000000);
    GH_DEBUG_CODE_set_CODE_CR_IC_INVLD_ADDR((U32)0x00000000);
    GH_DEBUG_CODE_set_CODE_CR_RESET_PC_ADDR((U32)0x00000000);
    for (i=0; i<4096; i++)
    {
        GH_DEBUG_CODE_set_CODE_CR_DC_ADDR(i, (U32)0x00000000);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

