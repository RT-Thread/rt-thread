/******************************************************************************
**
** \file      gh_vic.c
**
** \brief     VIC.
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
#include "gh_vic.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
U32                                     m_vic_enclr[2];
U32                                     m_vic_softintrclr[2];
U32                                     m_vic_edgeclr[2];

/*----------------------------------------------------------------------------*/
/* register VIC_Sense (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VIC_set_Sense(U8 index, U32 data)
{
    *(volatile U32 *)(REG_VIC_SENSE + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_Sense] <-- 0x%08x\n",
                        (REG_VIC_SENSE + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
U32  GH_VIC_get_Sense(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_SENSE + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_Sense] --> 0x%08x\n",
                        (REG_VIC_SENSE + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_Event (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VIC_set_Event(U8 index, U32 data)
{
    *(volatile U32 *)(REG_VIC_EVENT + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_Event] <-- 0x%08x\n",
                        (REG_VIC_EVENT + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
U32  GH_VIC_get_Event(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_EVENT + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_Event] --> 0x%08x\n",
                        (REG_VIC_EVENT + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_BothEdge (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VIC_set_BothEdge(U8 index, U32 data)
{
    *(volatile U32 *)(REG_VIC_BOTHEDGE + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_BothEdge] <-- 0x%08x\n",
                        (REG_VIC_BOTHEDGE + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
U32  GH_VIC_get_BothEdge(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_BOTHEDGE + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_BothEdge] --> 0x%08x\n",
                        (REG_VIC_BOTHEDGE + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_Select (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VIC_set_Select(U8 index, U32 data)
{
    *(volatile U32 *)(REG_VIC_SELECT + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_Select] <-- 0x%08x\n",
                        (REG_VIC_SELECT + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
U32  GH_VIC_get_Select(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_SELECT + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_Select] --> 0x%08x\n",
                        (REG_VIC_SELECT + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_Enable (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VIC_set_Enable(U8 index, U32 data)
{
    *(volatile U32 *)(REG_VIC_ENABLE + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_Enable] <-- 0x%08x\n",
                        (REG_VIC_ENABLE + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
U32  GH_VIC_get_Enable(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_ENABLE + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_Enable] --> 0x%08x\n",
                        (REG_VIC_ENABLE + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_EnClr (write)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VIC_set_EnClr(U8 index, U32 data)
{
    m_vic_enclr[index] = data;
    *(volatile U32 *)(REG_VIC_ENCLR + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_EnClr] <-- 0x%08x\n",
                        (REG_VIC_ENCLR + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
U32  GH_VIC_getm_EnClr(U8 index)
{
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "[GH_VIC_getm_EnClr] --> 0x%08x\n",
                        m_vic_enclr[index]);
    #endif
    return m_vic_enclr[index];
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VIC_RawSts (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_VIC_get_RawSts(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_RAWSTS + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_RawSts] --> 0x%08x\n",
                        (REG_VIC_RAWSTS + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_SoftInt (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VIC_set_SoftInt(U8 index, U32 data)
{
    *(volatile U32 *)(REG_VIC_SOFTINT + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_SoftInt] <-- 0x%08x\n",
                        (REG_VIC_SOFTINT + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
U32  GH_VIC_get_SoftInt(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_SOFTINT + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_SoftInt] --> 0x%08x\n",
                        (REG_VIC_SOFTINT + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_SoftIntrClr (write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VIC_set_SoftIntrClr(U8 index, U32 data)
{
    m_vic_softintrclr[index] = data;
    *(volatile U32 *)(REG_VIC_SOFTINTRCLR + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_SoftIntrClr] <-- 0x%08x\n",
                        (REG_VIC_SOFTINTRCLR + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
U32  GH_VIC_getm_SoftIntrClr(U8 index)
{
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "[GH_VIC_getm_SoftIntrClr] --> 0x%08x\n",
                        m_vic_softintrclr[index]);
    #endif
    return m_vic_softintrclr[index];
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VIC_Protect (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VIC_set_Protect(U8 index, U32 data)
{
    *(volatile U32 *)(REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_Protect] <-- 0x%08x\n",
                        (REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
U32  GH_VIC_get_Protect(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_Protect] --> 0x%08x\n",
                        (REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
void GH_VIC_set_Protect_Protect(U8 index, U8 data)
{
    GH_VIC_PROTECT_S d;
    d.all = *(volatile U32 *)(REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x00001000));
    d.bitc.protect = data;
    *(volatile U32 *)(REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x00001000)) = d.all;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_Protect_Protect] <-- 0x%08x\n",
                        (REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x00001000)),d.all,d.all);
    #endif
}
U8   GH_VIC_get_Protect_Protect(U8 index)
{
    GH_VIC_PROTECT_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x00001000)));

    tmp_value.all = value;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_Protect_Protect] --> 0x%08x\n",
                        (REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return tmp_value.bitc.protect;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_IRQSts (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_VIC_get_IRQSts(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_IRQSTS + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_IRQSts] --> 0x%08x\n",
                        (REG_VIC_IRQSTS + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_FIQSts (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_VIC_get_FIQSts(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_FIQSTS + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_FIQSts] --> 0x%08x\n",
                        (REG_VIC_FIQSTS + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_EdgeClr (write)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VIC_set_EdgeClr(U8 index, U32 data)
{
    m_vic_edgeclr[index] = data;
    *(volatile U32 *)(REG_VIC_EDGECLR + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_EdgeClr] <-- 0x%08x\n",
                        (REG_VIC_EDGECLR + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
U32  GH_VIC_getm_EdgeClr(U8 index)
{
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "[GH_VIC_getm_EdgeClr] --> 0x%08x\n",
                        m_vic_edgeclr[index]);
    #endif
    return m_vic_edgeclr[index];
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_VIC_init(void)
{
    int i;

    for (i=0; i<2; i++)
    {
        GH_VIC_set_Sense(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_VIC_set_Event(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_VIC_set_BothEdge(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_VIC_set_Select(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_VIC_set_Enable(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_VIC_set_EnClr(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_VIC_set_SoftInt(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_VIC_set_SoftIntrClr(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_VIC_set_Protect(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_VIC_set_EdgeClr(i, (U32)0x00000000);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

