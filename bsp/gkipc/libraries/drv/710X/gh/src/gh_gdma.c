/******************************************************************************
**
** \file      gh_gdma.c
**
** \brief     The Graphics DMA unit.
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
#include "gh_gdma.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_GDMA_SOURCE1_BASE_REAL                          FIO_ADDRESS(GDMA,0x60015000) /* read/write */
#define REG_GDMA_SOURCE1_PITCH_REAL                         FIO_ADDRESS(GDMA,0x60015004) /* read/write */
#define REG_GDMA_SOURCE2_BASE_REAL                          FIO_ADDRESS(GDMA,0x60015008) /* read/write */
#define REG_GDMA_SOURCE2_PITCH_REAL                         FIO_ADDRESS(GDMA,0x6001500C) /* read/write */
#define REG_GDMA_DESTINATION_BASE_REAL                      FIO_ADDRESS(GDMA,0x60015010) /* read/write */
#define REG_GDMA_DESTINATION_PITCH_REAL                     FIO_ADDRESS(GDMA,0x60015014) /* read/write */
#define REG_GDMA_WIDTH_REAL                                 FIO_ADDRESS(GDMA,0x60015018) /* read/write */
#define REG_GDMA_HEIGHT_REAL                                FIO_ADDRESS(GDMA,0x6001501C) /* read/write */
#define REG_GDMA_TRANSPARENT_REAL                           FIO_ADDRESS(GDMA,0x60015020) /* read/write */
#define REG_GDMA_OPCODE_REAL                                FIO_ADDRESS(GDMA,0x60015024) /* read/write */
#define REG_GDMA_NUM_PENDING_OPS_REAL                       FIO_ADDRESS(GDMA,0x60015028) /* read */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register GDMA_SOURCE1_BASE (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GDMA_set_SOURCE1_BASE(U32 data)
{
    *(volatile U32 *)REG_GDMA_SOURCE1_BASE_REAL = data;
}
GH_INLINE U32  GH_GDMA_get_SOURCE1_BASE(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_SOURCE1_BASE_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GDMA_SOURCE1_PITCH (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GDMA_set_SOURCE1_PITCH(U32 data)
{
    *(volatile U32 *)REG_GDMA_SOURCE1_PITCH_REAL = data;
}
GH_INLINE U32  GH_GDMA_get_SOURCE1_PITCH(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_SOURCE1_PITCH_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GDMA_SOURCE2_BASE (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GDMA_set_SOURCE2_BASE(U32 data)
{
    *(volatile U32 *)REG_GDMA_SOURCE2_BASE_REAL = data;
}
GH_INLINE U32  GH_GDMA_get_SOURCE2_BASE(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_SOURCE2_BASE_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GDMA_SOURCE2_PITCH (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GDMA_set_SOURCE2_PITCH(U32 data)
{
    *(volatile U32 *)REG_GDMA_SOURCE2_PITCH_REAL = data;
}
GH_INLINE U32  GH_GDMA_get_SOURCE2_PITCH(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_SOURCE2_PITCH_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GDMA_DESTINATION_BASE (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GDMA_set_DESTINATION_BASE(U32 data)
{
    *(volatile U32 *)REG_GDMA_DESTINATION_BASE_REAL = data;
}
GH_INLINE U32  GH_GDMA_get_DESTINATION_BASE(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_DESTINATION_BASE_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GDMA_DESTINATION_PITCH (read/write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GDMA_set_DESTINATION_PITCH(U32 data)
{
    *(volatile U32 *)REG_GDMA_DESTINATION_PITCH_REAL = data;
}
GH_INLINE U32  GH_GDMA_get_DESTINATION_PITCH(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_DESTINATION_PITCH_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GDMA_WIDTH (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GDMA_set_WIDTH(U32 data)
{
    *(volatile U32 *)REG_GDMA_WIDTH_REAL = data;
}
GH_INLINE U32  GH_GDMA_get_WIDTH(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_WIDTH_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GDMA_HEIGHT (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GDMA_set_HEIGHT(U32 data)
{
    *(volatile U32 *)REG_GDMA_HEIGHT_REAL = data;
}
GH_INLINE U32  GH_GDMA_get_HEIGHT(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_HEIGHT_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GDMA_TRANSPARENT (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GDMA_set_TRANSPARENT(U32 data)
{
    *(volatile U32 *)REG_GDMA_TRANSPARENT_REAL = data;
}
GH_INLINE U32  GH_GDMA_get_TRANSPARENT(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_TRANSPARENT_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GDMA_OPCODE (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GDMA_set_OPCODE(U32 data)
{
    *(volatile U32 *)REG_GDMA_OPCODE_REAL = data;
}
GH_INLINE U32  GH_GDMA_get_OPCODE(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_OPCODE_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GDMA_NUM_PENDING_OPS (read)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_GDMA_get_NUM_PENDING_OPS(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_NUM_PENDING_OPS_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GDMA_init(void)
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

