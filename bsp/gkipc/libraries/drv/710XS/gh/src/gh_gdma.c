/******************************************************************************
**
** \file      gh_gdma.c
**
** \brief     The Graphics DMA unit.
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
#include "gh_gdma.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register GDMA_SOURCE1_BASE (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_GDMA_set_SOURCE1_BASE(U32 data)
{
    *(volatile U32 *)REG_GDMA_SOURCE1_BASE = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_SOURCE1_BASE] <-- 0x%08x\n",
                        REG_GDMA_SOURCE1_BASE,data,data);
    #endif
}
U32  GH_GDMA_get_SOURCE1_BASE(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_SOURCE1_BASE);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_SOURCE1_BASE] --> 0x%08x\n",
                        REG_GDMA_SOURCE1_BASE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_SOURCE1_PITCH (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_GDMA_set_SOURCE1_PITCH(U32 data)
{
    *(volatile U32 *)REG_GDMA_SOURCE1_PITCH = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_SOURCE1_PITCH] <-- 0x%08x\n",
                        REG_GDMA_SOURCE1_PITCH,data,data);
    #endif
}
U32  GH_GDMA_get_SOURCE1_PITCH(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_SOURCE1_PITCH);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_SOURCE1_PITCH] --> 0x%08x\n",
                        REG_GDMA_SOURCE1_PITCH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_SOURCE2_BASE (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_GDMA_set_SOURCE2_BASE(U32 data)
{
    *(volatile U32 *)REG_GDMA_SOURCE2_BASE = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_SOURCE2_BASE] <-- 0x%08x\n",
                        REG_GDMA_SOURCE2_BASE,data,data);
    #endif
}
U32  GH_GDMA_get_SOURCE2_BASE(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_SOURCE2_BASE);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_SOURCE2_BASE] --> 0x%08x\n",
                        REG_GDMA_SOURCE2_BASE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_SOURCE2_PITCH (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_GDMA_set_SOURCE2_PITCH(U32 data)
{
    *(volatile U32 *)REG_GDMA_SOURCE2_PITCH = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_SOURCE2_PITCH] <-- 0x%08x\n",
                        REG_GDMA_SOURCE2_PITCH,data,data);
    #endif
}
U32  GH_GDMA_get_SOURCE2_PITCH(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_SOURCE2_PITCH);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_SOURCE2_PITCH] --> 0x%08x\n",
                        REG_GDMA_SOURCE2_PITCH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_DESTINATION_BASE (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_GDMA_set_DESTINATION_BASE(U32 data)
{
    *(volatile U32 *)REG_GDMA_DESTINATION_BASE = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_DESTINATION_BASE] <-- 0x%08x\n",
                        REG_GDMA_DESTINATION_BASE,data,data);
    #endif
}
U32  GH_GDMA_get_DESTINATION_BASE(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_DESTINATION_BASE);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_DESTINATION_BASE] --> 0x%08x\n",
                        REG_GDMA_DESTINATION_BASE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_DESTINATION_PITCH (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_GDMA_set_DESTINATION_PITCH(U32 data)
{
    *(volatile U32 *)REG_GDMA_DESTINATION_PITCH = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_DESTINATION_PITCH] <-- 0x%08x\n",
                        REG_GDMA_DESTINATION_PITCH,data,data);
    #endif
}
U32  GH_GDMA_get_DESTINATION_PITCH(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_DESTINATION_PITCH);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_DESTINATION_PITCH] --> 0x%08x\n",
                        REG_GDMA_DESTINATION_PITCH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_WIDTH (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_GDMA_set_WIDTH(U32 data)
{
    *(volatile U32 *)REG_GDMA_WIDTH = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_WIDTH] <-- 0x%08x\n",
                        REG_GDMA_WIDTH,data,data);
    #endif
}
U32  GH_GDMA_get_WIDTH(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_WIDTH);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_WIDTH] --> 0x%08x\n",
                        REG_GDMA_WIDTH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_HEIGHT (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_GDMA_set_HEIGHT(U32 data)
{
    *(volatile U32 *)REG_GDMA_HEIGHT = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_HEIGHT] <-- 0x%08x\n",
                        REG_GDMA_HEIGHT,data,data);
    #endif
}
U32  GH_GDMA_get_HEIGHT(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_HEIGHT);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_HEIGHT] --> 0x%08x\n",
                        REG_GDMA_HEIGHT,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_TRANSPARENT (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_GDMA_set_TRANSPARENT(U32 data)
{
    *(volatile U32 *)REG_GDMA_TRANSPARENT = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_TRANSPARENT] <-- 0x%08x\n",
                        REG_GDMA_TRANSPARENT,data,data);
    #endif
}
U32  GH_GDMA_get_TRANSPARENT(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_TRANSPARENT);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_TRANSPARENT] --> 0x%08x\n",
                        REG_GDMA_TRANSPARENT,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_OPCODE (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_GDMA_set_OPCODE(U32 data)
{
    *(volatile U32 *)REG_GDMA_OPCODE = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_OPCODE] <-- 0x%08x\n",
                        REG_GDMA_OPCODE,data,data);
    #endif
}
U32  GH_GDMA_get_OPCODE(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_OPCODE);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_OPCODE] --> 0x%08x\n",
                        REG_GDMA_OPCODE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_NUM_PENDING_OPS (read)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_GDMA_get_NUM_PENDING_OPS(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_NUM_PENDING_OPS);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_NUM_PENDING_OPS] --> 0x%08x\n",
                        REG_GDMA_NUM_PENDING_OPS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_GDMA_init(void)
{
    GH_GDMA_set_SOURCE1_BASE((U32)0x00000000);
    GH_GDMA_set_SOURCE1_PITCH((U32)0x00000000);
    GH_GDMA_set_SOURCE2_BASE((U32)0x00000000);
    GH_GDMA_set_SOURCE2_PITCH((U32)0x00000000);
    GH_GDMA_set_DESTINATION_BASE((U32)0x00000000);
    GH_GDMA_set_DESTINATION_PITCH((U32)0x00000000);
    GH_GDMA_set_WIDTH((U32)0x00000000);
    GH_GDMA_set_HEIGHT((U32)0x00000000);
    GH_GDMA_set_TRANSPARENT((U32)0x00000000);
    GH_GDMA_set_OPCODE((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

