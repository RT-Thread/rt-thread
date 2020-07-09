/******************************************************************************
**
** \file      gh_crypto.c
**
** \brief     Cryptography Engine.
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
#include "gh_crypto.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Key (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_CRYPTO_set_DES_Key(U8 index, U32 data)
{
    *(volatile U32 *)(REG_CRYPTO_DES_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)) = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_DES_Key] <-- 0x%08x\n",
                        (REG_CRYPTO_DES_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)),data,data);
    #endif
}
U32  GH_CRYPTO_get_DES_Key(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_DES_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_DES_Key] --> 0x%08x\n",
                        (REG_CRYPTO_DES_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Input (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_CRYPTO_set_DES_Input(U8 index, U32 data)
{
    *(volatile U32 *)(REG_CRYPTO_DES_INPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)) = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_DES_Input] <-- 0x%08x\n",
                        (REG_CRYPTO_DES_INPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)),data,data);
    #endif
}
U32  GH_CRYPTO_get_DES_Input(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_DES_INPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_DES_Input] --> 0x%08x\n",
                        (REG_CRYPTO_DES_INPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Opcode (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_CRYPTO_set_DES_Opcode(U32 data)
{
    *(volatile U32 *)REG_CRYPTO_DES_OPCODE = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_DES_Opcode] <-- 0x%08x\n",
                        REG_CRYPTO_DES_OPCODE,data,data);
    #endif
}
U32  GH_CRYPTO_get_DES_Opcode(void)
{
    U32 value = (*(volatile U32 *)REG_CRYPTO_DES_OPCODE);

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_DES_Opcode] --> 0x%08x\n",
                        REG_CRYPTO_DES_OPCODE,value);
    #endif
    return value;
}
void GH_CRYPTO_set_DES_Opcode_mode(U8 data)
{
    GH_CRYPTO_DES_OPCODE_S d;
    d.all = *(volatile U32 *)REG_CRYPTO_DES_OPCODE;
    d.bitc.mode = data;
    *(volatile U32 *)REG_CRYPTO_DES_OPCODE = d.all;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_DES_Opcode_mode] <-- 0x%08x\n",
                        REG_CRYPTO_DES_OPCODE,d.all,d.all);
    #endif
}
U8   GH_CRYPTO_get_DES_Opcode_mode(void)
{
    GH_CRYPTO_DES_OPCODE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_DES_OPCODE);

    tmp_value.all = value;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_DES_Opcode_mode] --> 0x%08x\n",
                        REG_CRYPTO_DES_OPCODE,value);
    #endif
    return tmp_value.bitc.mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Output_Rdy (read)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_CRYPTO_get_DES_Output_Rdy(void)
{
    U32 value = (*(volatile U32 *)REG_CRYPTO_DES_OUTPUT_RDY);

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_DES_Output_Rdy] --> 0x%08x\n",
                        REG_CRYPTO_DES_OUTPUT_RDY,value);
    #endif
    return value;
}
U8   GH_CRYPTO_get_DES_Output_Rdy_Rdy(void)
{
    GH_CRYPTO_DES_OUTPUT_RDY_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_DES_OUTPUT_RDY);

    tmp_value.all = value;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_DES_Output_Rdy_Rdy] --> 0x%08x\n",
                        REG_CRYPTO_DES_OUTPUT_RDY,value);
    #endif
    return tmp_value.bitc.rdy;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Output (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_CRYPTO_get_DES_Output(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_DES_OUTPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_DES_Output] --> 0x%08x\n",
                        (REG_CRYPTO_DES_OUTPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Interrupt (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_CRYPTO_set_DES_Interrupt(U32 data)
{
    *(volatile U32 *)REG_CRYPTO_DES_INTERRUPT = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_DES_Interrupt] <-- 0x%08x\n",
                        REG_CRYPTO_DES_INTERRUPT,data,data);
    #endif
}
U32  GH_CRYPTO_get_DES_Interrupt(void)
{
    U32 value = (*(volatile U32 *)REG_CRYPTO_DES_INTERRUPT);

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_DES_Interrupt] --> 0x%08x\n",
                        REG_CRYPTO_DES_INTERRUPT,value);
    #endif
    return value;
}
void GH_CRYPTO_set_DES_Interrupt_En(U8 data)
{
    GH_CRYPTO_DES_INTERRUPT_S d;
    d.all = *(volatile U32 *)REG_CRYPTO_DES_INTERRUPT;
    d.bitc.en = data;
    *(volatile U32 *)REG_CRYPTO_DES_INTERRUPT = d.all;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_DES_Interrupt_En] <-- 0x%08x\n",
                        REG_CRYPTO_DES_INTERRUPT,d.all,d.all);
    #endif
}
U8   GH_CRYPTO_get_DES_Interrupt_En(void)
{
    GH_CRYPTO_DES_INTERRUPT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_DES_INTERRUPT);

    tmp_value.all = value;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_DES_Interrupt_En] --> 0x%08x\n",
                        REG_CRYPTO_DES_INTERRUPT,value);
    #endif
    return tmp_value.bitc.en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_128_Key (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_CRYPTO_set_AES_128_Key(U8 index, U32 data)
{
    *(volatile U32 *)(REG_CRYPTO_AES_128_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)) = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_AES_128_Key] <-- 0x%08x\n",
                        (REG_CRYPTO_AES_128_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)),data,data);
    #endif
}
U32  GH_CRYPTO_get_AES_128_Key(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_AES_128_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_128_Key] --> 0x%08x\n",
                        (REG_CRYPTO_AES_128_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_192_Key (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_CRYPTO_set_AES_192_Key(U8 index, U32 data)
{
    *(volatile U32 *)(REG_CRYPTO_AES_192_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)) = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_AES_192_Key] <-- 0x%08x\n",
                        (REG_CRYPTO_AES_192_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)),data,data);
    #endif
}
U32  GH_CRYPTO_get_AES_192_Key(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_AES_192_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_192_Key] --> 0x%08x\n",
                        (REG_CRYPTO_AES_192_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_256_Key (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_CRYPTO_set_AES_256_Key(U8 index, U32 data)
{
    *(volatile U32 *)(REG_CRYPTO_AES_256_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)) = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_AES_256_Key] <-- 0x%08x\n",
                        (REG_CRYPTO_AES_256_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)),data,data);
    #endif
}
U32  GH_CRYPTO_get_AES_256_Key(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_AES_256_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_256_Key] --> 0x%08x\n",
                        (REG_CRYPTO_AES_256_KEY + index * FIO_MOFFSET(CRYPTO,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Input (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_CRYPTO_set_AES_Input(U8 index, U32 data)
{
    *(volatile U32 *)(REG_CRYPTO_AES_INPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)) = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_AES_Input] <-- 0x%08x\n",
                        (REG_CRYPTO_AES_INPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)),data,data);
    #endif
}
U32  GH_CRYPTO_get_AES_Input(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_AES_INPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_Input] --> 0x%08x\n",
                        (REG_CRYPTO_AES_INPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Opcode (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_CRYPTO_set_AES_Opcode(U32 data)
{
    *(volatile U32 *)REG_CRYPTO_AES_OPCODE = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_AES_Opcode] <-- 0x%08x\n",
                        REG_CRYPTO_AES_OPCODE,data,data);
    #endif
}
U32  GH_CRYPTO_get_AES_Opcode(void)
{
    U32 value = (*(volatile U32 *)REG_CRYPTO_AES_OPCODE);

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_Opcode] --> 0x%08x\n",
                        REG_CRYPTO_AES_OPCODE,value);
    #endif
    return value;
}
void GH_CRYPTO_set_AES_Opcode_mode(U8 data)
{
    GH_CRYPTO_AES_OPCODE_S d;
    d.all = *(volatile U32 *)REG_CRYPTO_AES_OPCODE;
    d.bitc.mode = data;
    *(volatile U32 *)REG_CRYPTO_AES_OPCODE = d.all;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_AES_Opcode_mode] <-- 0x%08x\n",
                        REG_CRYPTO_AES_OPCODE,d.all,d.all);
    #endif
}
U8   GH_CRYPTO_get_AES_Opcode_mode(void)
{
    GH_CRYPTO_AES_OPCODE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_AES_OPCODE);

    tmp_value.all = value;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_Opcode_mode] --> 0x%08x\n",
                        REG_CRYPTO_AES_OPCODE,value);
    #endif
    return tmp_value.bitc.mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Output_Rdy (read)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_CRYPTO_get_AES_Output_Rdy(void)
{
    U32 value = (*(volatile U32 *)REG_CRYPTO_AES_OUTPUT_RDY);

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_Output_Rdy] --> 0x%08x\n",
                        REG_CRYPTO_AES_OUTPUT_RDY,value);
    #endif
    return value;
}
U8   GH_CRYPTO_get_AES_Output_Rdy_Rdy(void)
{
    GH_CRYPTO_AES_OUTPUT_RDY_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_AES_OUTPUT_RDY);

    tmp_value.all = value;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_Output_Rdy_Rdy] --> 0x%08x\n",
                        REG_CRYPTO_AES_OUTPUT_RDY,value);
    #endif
    return tmp_value.bitc.rdy;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Output (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_CRYPTO_get_AES_Output(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_AES_OUTPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_Output] --> 0x%08x\n",
                        (REG_CRYPTO_AES_OUTPUT + index * FIO_MOFFSET(CRYPTO,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Interrupt (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_CRYPTO_set_AES_Interrupt(U32 data)
{
    *(volatile U32 *)REG_CRYPTO_AES_INTERRUPT = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_AES_Interrupt] <-- 0x%08x\n",
                        REG_CRYPTO_AES_INTERRUPT,data,data);
    #endif
}
U32  GH_CRYPTO_get_AES_Interrupt(void)
{
    U32 value = (*(volatile U32 *)REG_CRYPTO_AES_INTERRUPT);

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_Interrupt] --> 0x%08x\n",
                        REG_CRYPTO_AES_INTERRUPT,value);
    #endif
    return value;
}
void GH_CRYPTO_set_AES_Interrupt_En(U8 data)
{
    GH_CRYPTO_AES_INTERRUPT_S d;
    d.all = *(volatile U32 *)REG_CRYPTO_AES_INTERRUPT;
    d.bitc.en = data;
    *(volatile U32 *)REG_CRYPTO_AES_INTERRUPT = d.all;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_AES_Interrupt_En] <-- 0x%08x\n",
                        REG_CRYPTO_AES_INTERRUPT,d.all,d.all);
    #endif
}
U8   GH_CRYPTO_get_AES_Interrupt_En(void)
{
    GH_CRYPTO_AES_INTERRUPT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_AES_INTERRUPT);

    tmp_value.all = value;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_AES_Interrupt_En] --> 0x%08x\n",
                        REG_CRYPTO_AES_INTERRUPT,value);
    #endif
    return tmp_value.bitc.en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register CRYPTO_EFUSE_BOOT_SW_DIS (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_CRYPTO_set_EFUSE_BOOT_SW_DIS(U32 data)
{
    *(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS = data;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_EFUSE_BOOT_SW_DIS] <-- 0x%08x\n",
                        REG_CRYPTO_EFUSE_BOOT_SW_DIS,data,data);
    #endif
}
U32  GH_CRYPTO_get_EFUSE_BOOT_SW_DIS(void)
{
    U32 value = (*(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS);

    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_EFUSE_BOOT_SW_DIS] --> 0x%08x\n",
                        REG_CRYPTO_EFUSE_BOOT_SW_DIS,value);
    #endif
    return value;
}
void GH_CRYPTO_set_EFUSE_BOOT_SW_DIS_Efuse_boot_dis(U8 data)
{
    GH_CRYPTO_EFUSE_BOOT_SW_DIS_S d;
    d.all = *(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS;
    d.bitc.efuse_boot_dis = data;
    *(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS = d.all;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_EFUSE_BOOT_SW_DIS_Efuse_boot_dis] <-- 0x%08x\n",
                        REG_CRYPTO_EFUSE_BOOT_SW_DIS,d.all,d.all);
    #endif
}
U8   GH_CRYPTO_get_EFUSE_BOOT_SW_DIS_Efuse_boot_dis(void)
{
    GH_CRYPTO_EFUSE_BOOT_SW_DIS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS);

    tmp_value.all = value;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_EFUSE_BOOT_SW_DIS_Efuse_boot_dis] --> 0x%08x\n",
                        REG_CRYPTO_EFUSE_BOOT_SW_DIS,value);
    #endif
    return tmp_value.bitc.efuse_boot_dis;
}
void GH_CRYPTO_set_EFUSE_BOOT_SW_DIS_Efuse_boot_sw(U8 data)
{
    GH_CRYPTO_EFUSE_BOOT_SW_DIS_S d;
    d.all = *(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS;
    d.bitc.efuse_boot_sw = data;
    *(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS = d.all;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_CRYPTO_set_EFUSE_BOOT_SW_DIS_Efuse_boot_sw] <-- 0x%08x\n",
                        REG_CRYPTO_EFUSE_BOOT_SW_DIS,d.all,d.all);
    #endif
}
U8   GH_CRYPTO_get_EFUSE_BOOT_SW_DIS_Efuse_boot_sw(void)
{
    GH_CRYPTO_EFUSE_BOOT_SW_DIS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS);

    tmp_value.all = value;
    #if GH_CRYPTO_ENABLE_DEBUG_PRINT
    GH_CRYPTO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_CRYPTO_get_EFUSE_BOOT_SW_DIS_Efuse_boot_sw] --> 0x%08x\n",
                        REG_CRYPTO_EFUSE_BOOT_SW_DIS,value);
    #endif
    return tmp_value.bitc.efuse_boot_sw;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_CRYPTO_init(void)
{
    int i;

    for (i=0; i<2; i++)
    {
        GH_CRYPTO_set_DES_Key(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_CRYPTO_set_DES_Input(i, (U32)0x00000000);
    }
    GH_CRYPTO_set_DES_Opcode((U32)0x00000000);
    GH_CRYPTO_set_DES_Interrupt((U32)0x00000000);
    for (i=0; i<4; i++)
    {
        GH_CRYPTO_set_AES_128_Key(i, (U32)0x00000000);
    }
    for (i=0; i<6; i++)
    {
        GH_CRYPTO_set_AES_192_Key(i, (U32)0x00000000);
    }
    for (i=0; i<8; i++)
    {
        GH_CRYPTO_set_AES_256_Key(i, (U32)0x00000000);
    }
    for (i=0; i<4; i++)
    {
        GH_CRYPTO_set_AES_Input(i, (U32)0x00000000);
    }
    GH_CRYPTO_set_AES_Opcode((U32)0x00000000);
    GH_CRYPTO_set_AES_Interrupt((U32)0x00000000);
    GH_CRYPTO_set_EFUSE_BOOT_SW_DIS((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

