/******************************************************************************
**
** \file      gh_vic.c
**
** \brief     VIC.
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
#ifndef SRC_INLINE
#include "gh_vic.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_VIC_IRQSTS_REAL                                 FIO_ADDRESS(VIC,0x60003000) /* read */
#define REG_VIC_FIQSTS_REAL                                 FIO_ADDRESS(VIC,0x60003004) /* read */
#define REG_VIC_RAWSTS_REAL                                 FIO_ADDRESS(VIC,0x60003008) /* read */
#define REG_VIC_SELECT_REAL                                 FIO_ADDRESS(VIC,0x6000300C) /* read/write */
#define REG_VIC_ENABLE_REAL                                 FIO_ADDRESS(VIC,0x60003010) /* read/write */
#define REG_VIC_ENCLR_REAL                                  FIO_ADDRESS(VIC,0x60003014) /* write */
#define REG_VIC_SOFTINT_REAL                                FIO_ADDRESS(VIC,0x60003018) /* read/write */
#define REG_VIC_SOFTINTRCLR_REAL                            FIO_ADDRESS(VIC,0x6000301C) /* write */
#define REG_VIC_PROTECT_REAL                                FIO_ADDRESS(VIC,0x60003020) /* read/write */
#define REG_VIC_SENSE_REAL                                  FIO_ADDRESS(VIC,0x60003024) /* read/write */
#define REG_VIC_BOTHEDGE_REAL                               FIO_ADDRESS(VIC,0x60003028) /* read/write */
#define REG_VIC_EVENT_REAL                                  FIO_ADDRESS(VIC,0x6000302C) /* read/write */
#define REG_VIC_EDGECLR_REAL                                FIO_ADDRESS(VIC,0x60003038) /* write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* VIC_Protect */
    U32 all;
    struct {
        U32 protect                     : 1;
        U32                             : 31;
    } bitc;
} GH_VIC_PROTECT_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
U32                                     m_vic_enclr[2];
U32                                     m_vic_softintrclr[2];
U32                                     m_vic_edgeclr[2];



GH_INLINE U32 GH_VIC_REG_ENCRYPT(U32 reg)
{
#if defined(_ARM_RVDS)

    __asm{mov    reg, reg, ROR#2 };
    __asm{rev    reg, reg};

#elif defined(_ARM_GNU)
    __asm__ __volatile__ (  \
        "mov %1, %0 ,ROR#2\n"\
        "rev %0, %1\n"\
        : "=r" (reg)\
        : "0" (reg)\
        : "memory");
#endif
	return reg;
}

GH_INLINE U32 GH_VIC_REG_DECRYPT(U32 reg)
{
#if defined(_ARM_RVDS)
    __asm{rev    reg, reg};
    __asm{mov    reg, reg, ROR#30};

#elif defined(_ARM_GNU)
        __asm__ __volatile__ (\
        "rev %1, %0\n"\
        "mov %0, %1 ,ROR#30\n"\
        : "=r" (reg)\
        : "0" (reg)\
        : "memory");
#endif
	return reg;
}


/*----------------------------------------------------------------------------*/
/* register VIC_IRQSts (read)                                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_VIC_get_IRQSts(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_IRQSTS_REAL + index * FIO_MOFFSET(VIC,0x0000D000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_IRQSts] --> 0x%08x\n",
                        (REG_VIC_IRQSTS + index * FIO_MOFFSET(VIC,0x0000D000)),value);
    #endif
    return GH_VIC_REG_ENCRYPT(value);
}

/*----------------------------------------------------------------------------*/
/* register VIC_FIQSts (read)                                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_VIC_get_FIQSts(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_FIQSTS_REAL + index * FIO_MOFFSET(VIC,0x0000D000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_FIQSts] --> 0x%08x\n",
                        (REG_VIC_FIQSTS + index * FIO_MOFFSET(VIC,0x0000D000)),value);
    #endif
    return  GH_VIC_REG_ENCRYPT(value);
}

/*----------------------------------------------------------------------------*/
/* register VIC_RawSts (read)                                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_VIC_get_RawSts(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_RAWSTS_REAL + index * FIO_MOFFSET(VIC,0x0000D000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_RawSts] --> 0x%08x\n",
                        (REG_VIC_RAWSTS + index * FIO_MOFFSET(VIC,0x0000D000)),value);
    #endif
    return  GH_VIC_REG_ENCRYPT(value);
}

/*----------------------------------------------------------------------------*/
/* register VIC_Select (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIC_set_Select(U8 index, U32 data)
{
		data=GH_VIC_REG_DECRYPT(data);
    *(volatile U32 *)(REG_VIC_SELECT_REAL + index * FIO_MOFFSET(VIC,0x0000D000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_Select] <-- 0x%08x\n",
                        (REG_VIC_SELECT + index * FIO_MOFFSET(VIC,0x0000D000)),value,value);
    #endif
}
GH_INLINE U32  GH_VIC_get_Select(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_SELECT_REAL + index * FIO_MOFFSET(VIC,0x0000D000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_Select] --> 0x%08x\n",
                        (REG_VIC_SELECT + index * FIO_MOFFSET(VIC,0x0000D000)),value);
    #endif
    return GH_VIC_REG_ENCRYPT(value);
}

/*----------------------------------------------------------------------------*/
/* register VIC_Enable (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIC_set_Enable(U8 index, U32 data)
{
    data=GH_VIC_REG_DECRYPT(data);
    *(volatile U32 *)(REG_VIC_ENABLE_REAL + index * FIO_MOFFSET(VIC,0x0000D000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_Enable] <-- 0x%08x\n",
                        (REG_VIC_ENABLE + index * FIO_MOFFSET(VIC,0x0000D000)),value,value);
    #endif
}
GH_INLINE U32  GH_VIC_get_Enable(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_ENABLE_REAL + index * FIO_MOFFSET(VIC,0x0000D000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_Enable] --> 0x%08x\n",
                        (REG_VIC_ENABLE + index * FIO_MOFFSET(VIC,0x0000D000)),value);
    #endif
    return GH_VIC_REG_ENCRYPT(value);
}

/*----------------------------------------------------------------------------*/
/* register VIC_EnClr (write)                                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIC_set_EnClr(U8 index, U32 data)
{
    m_vic_enclr[index] = data;
    data=GH_VIC_REG_DECRYPT(data);
    *(volatile U32 *)(REG_VIC_ENCLR_REAL + index * FIO_MOFFSET(VIC,0x0000D000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_EnClr] <-- 0x%08x\n",
                        (REG_VIC_ENCLR + index * FIO_MOFFSET(VIC,0x0000D000)),data,data);
    #endif
}
GH_INLINE U32  GH_VIC_getm_EnClr(U8 index)
{
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "[GH_VIC_getm_EnClr] --> 0x%08x\n",
                        m_vic_enclr[index]);
    #endif
    return m_vic_enclr[index];
}

/*----------------------------------------------------------------------------*/
/* register VIC_SoftInt (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIC_set_SoftInt(U8 index, U32 data)
{
    data=GH_VIC_REG_DECRYPT(data);
    *(volatile U32 *)(REG_VIC_SOFTINT_REAL + index * FIO_MOFFSET(VIC,0x0000D000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_SoftInt] <-- 0x%08x\n",
                        (REG_VIC_SOFTINT + index * FIO_MOFFSET(VIC,0x0000D000)),value,value);
    #endif
}
GH_INLINE U32  GH_VIC_get_SoftInt(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_SOFTINT_REAL + index * FIO_MOFFSET(VIC,0x0000D000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_SoftInt] --> 0x%08x\n",
                        (REG_VIC_SOFTINT + index * FIO_MOFFSET(VIC,0x0000D000)),value);
    #endif
    return GH_VIC_REG_ENCRYPT(value);
}

/*----------------------------------------------------------------------------*/
/* register VIC_SoftIntrClr (write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIC_set_SoftIntrClr(U8 index, U32 data)
{
    m_vic_softintrclr[index] = data;
    data=GH_VIC_REG_DECRYPT(data);
    *(volatile U32 *)(REG_VIC_SOFTINTRCLR_REAL + index * FIO_MOFFSET(VIC,0x0000D000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_SoftIntrClr] <-- 0x%08x\n",
                        (REG_VIC_SOFTINTRCLR + index * FIO_MOFFSET(VIC,0x0000D000)),data,data);
    #endif
}
GH_INLINE U32  GH_VIC_getm_SoftIntrClr(U8 index)
{
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "[GH_VIC_getm_SoftIntrClr] --> 0x%08x\n",
                        m_vic_softintrclr[index]);
    #endif
    return m_vic_softintrclr[index];
}

/*----------------------------------------------------------------------------*/
/* register VIC_Protect (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIC_set_Protect(U8 index, U32 data)
{
    GH_VIC_PROTECT_REAL_S real;
    GH_VIC_PROTECT_S dummy;
    dummy.all = data ;
    real.bitc.protect = dummy.bitc.protect;
    *(volatile U32 *)(REG_VIC_PROTECT_REAL + index * FIO_MOFFSET(VIC,0x0000D000)) = real.all;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_Protect] <-- 0x%08x\n",
                        (REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x0000D000)),dummy.all,dummy.all);
    #endif
}
GH_INLINE U32  GH_VIC_get_Protect(U8 index)
{
    GH_VIC_PROTECT_REAL_S real;
    GH_VIC_PROTECT_S dummy;
     real.all = (*(volatile U32 *)(REG_VIC_PROTECT_REAL + index * FIO_MOFFSET(VIC,0x0000D000)));

    dummy.bitc.protect = real.bitc.protect;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_Protect] --> 0x%08x\n",
                        (REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x0000D000)),dummy.all);
    #endif
    return dummy.all;
}
GH_INLINE void GH_VIC_set_Protect_Protect(U8 index, U8 data)
{
    GH_VIC_PROTECT_REAL_S d;
    d.all = *(volatile U32 *)(REG_VIC_PROTECT_REAL + index * FIO_MOFFSET(VIC,0x0000D000));
    d.bitc.protect = data;
    *(volatile U32 *)(REG_VIC_PROTECT_REAL + index * FIO_MOFFSET(VIC,0x0000D000)) = d.all;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_Protect_Protect] <-- 0x%08x\n",
                        (REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x0000D000)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIC_get_Protect_Protect(U8 index)
{
    GH_VIC_PROTECT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_VIC_PROTECT_REAL + index * FIO_MOFFSET(VIC,0x0000D000)));

    tmp_value.all = value;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_Protect_Protect] --> 0x%08x\n",
                        (REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x0000D000)),value);
    #endif
    return tmp_value.bitc.protect;
}

/*----------------------------------------------------------------------------*/
/* register VIC_Sense (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIC_set_Sense(U8 index, U32 data)
{
    data=GH_VIC_REG_DECRYPT(data);
   *(volatile U32 *)(REG_VIC_SENSE_REAL + index * FIO_MOFFSET(VIC,0x0000D000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_Sense] <-- 0x%08x\n",
                        (REG_VIC_SENSE + index * FIO_MOFFSET(VIC,0x0000D000)),value,value);
    #endif
}
GH_INLINE U32  GH_VIC_get_Sense(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_SENSE_REAL + index * FIO_MOFFSET(VIC,0x0000D000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_Sense] --> 0x%08x\n",
                        (REG_VIC_SENSE + index * FIO_MOFFSET(VIC,0x0000D000)),value);
    #endif
    return GH_VIC_REG_ENCRYPT(value);
}

/*----------------------------------------------------------------------------*/
/* register VIC_BothEdge (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIC_set_BothEdge(U8 index, U32 data)
{
    data=GH_VIC_REG_DECRYPT(data);
    *(volatile U32 *)(REG_VIC_BOTHEDGE_REAL + index * FIO_MOFFSET(VIC,0x0000D000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_BothEdge] <-- 0x%08x\n",
                        (REG_VIC_BOTHEDGE + index * FIO_MOFFSET(VIC,0x0000D000)),value,value);
    #endif
}
GH_INLINE U32  GH_VIC_get_BothEdge(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_BOTHEDGE_REAL + index * FIO_MOFFSET(VIC,0x0000D000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_BothEdge] --> 0x%08x\n",
                        (REG_VIC_BOTHEDGE + index * FIO_MOFFSET(VIC,0x0000D000)),value);
    #endif
    return GH_VIC_REG_ENCRYPT(value);
}

/*----------------------------------------------------------------------------*/
/* register VIC_Event (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIC_set_Event(U8 index, U32 data)
{
    data=GH_VIC_REG_DECRYPT(data);
    *(volatile U32 *)(REG_VIC_EVENT_REAL + index * FIO_MOFFSET(VIC,0x0000D000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_Event] <-- 0x%08x\n",
                        (REG_VIC_EVENT + index * FIO_MOFFSET(VIC,0x0000D000)),value,value);
    #endif
}
GH_INLINE U32  GH_VIC_get_Event(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_EVENT_REAL + index * FIO_MOFFSET(VIC,0x0000D000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_Event] --> 0x%08x\n",
                        (REG_VIC_EVENT + index * FIO_MOFFSET(VIC,0x0000D000)),value);
    #endif
    return GH_VIC_REG_ENCRYPT(value);
}

/*----------------------------------------------------------------------------*/
/* register VIC_EdgeClr (write)                                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIC_set_EdgeClr(U8 index, U32 data)
{
    m_vic_edgeclr[index] = data;
    data=GH_VIC_REG_DECRYPT(data);
    *(volatile U32 *)(REG_VIC_EDGECLR_REAL + index * FIO_MOFFSET(VIC,0x0000D000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_EdgeClr] <-- 0x%08x\n",
                        (REG_VIC_EDGECLR + index * FIO_MOFFSET(VIC,0x0000D000)),data,data);
    #endif
}
GH_INLINE U32  GH_VIC_getm_EdgeClr(U8 index)
{
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "[GH_VIC_getm_EdgeClr] --> 0x%08x\n",
                        m_vic_edgeclr[index]);
    #endif
    return m_vic_edgeclr[index];
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIC_init(void)
{
    int i;

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
        GH_VIC_set_Sense(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_VIC_set_BothEdge(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_VIC_set_Event(i, (U32)0x00000000);
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

