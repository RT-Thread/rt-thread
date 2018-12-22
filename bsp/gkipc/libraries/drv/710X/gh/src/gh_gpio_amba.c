/******************************************************************************
**
** \file      gh_gpio_amba.c
**
** \brief     These GPIO pins can be configured as I/O pins for other hardware modules..
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
#include "gh_gpio_amba.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_GPIO_DATA_REAL                                  FIO_ADDRESS(GPIO,0x70009000) /* read/write */
#define REG_GPIO_DIR_REAL                                   FIO_ADDRESS(GPIO,0x70009004) /* read/write */
#define REG_GPIO_IS_REAL                                    FIO_ADDRESS(GPIO,0x70009008) /* read/write */
#define REG_GPIO_IBE_REAL                                   FIO_ADDRESS(GPIO,0x7000900C) /* read/write */
#define REG_GPIO_IEV_REAL                                   FIO_ADDRESS(GPIO,0x70009010) /* read/write */
#define REG_GPIO_IE_REAL                                    FIO_ADDRESS(GPIO,0x70009014) /* read/write */
#define REG_GPIO_AFSEL_REAL                                 FIO_ADDRESS(GPIO,0x70009018) /* read/write */
#define REG_GPIO_RIS_REAL                                   FIO_ADDRESS(GPIO,0x7000901C) /* read */
#define REG_GPIO_MIS_REAL                                   FIO_ADDRESS(GPIO,0x70009020) /* read */
#define REG_GPIO_IC_REAL                                    FIO_ADDRESS(GPIO,0x70009024) /* write */
#define REG_GPIO_MASK_REAL                                  FIO_ADDRESS(GPIO,0x70009028) /* read/write */
#define REG_GPIO_ENABLE_REAL                                FIO_ADDRESS(GPIO,0x7000902C) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* GPIO_ENABLE */
    U32 all;
    struct {
        U32 enb                         : 1;
        U32                             : 31;
    } bitc;
} GH_GPIO_ENABLE_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
U32                                     m_gpio_ic[6];

/*----------------------------------------------------------------------------*/
/* register GPIO_DATA (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_DATA(U8 index, U32 data)
{
    *(volatile U32 *)(REG_GPIO_DATA_REAL + index * FIO_MOFFSET(GPIO,0x00001000)) = data;
}
GH_INLINE U32  GH_GPIO_get_DATA(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_GPIO_DATA_REAL + index * FIO_MOFFSET(GPIO,0x00001000)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_DIR (read/write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_DIR(U8 index, U32 data)
{
    *(volatile U32 *)(REG_GPIO_DIR_REAL + index * FIO_MOFFSET(GPIO,0x00001000)) = data;
}
GH_INLINE U32  GH_GPIO_get_DIR(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_GPIO_DIR_REAL + index * FIO_MOFFSET(GPIO,0x00001000)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_IS (read/write)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_IS(U8 index, U32 data)
{
    *(volatile U32 *)(REG_GPIO_IS_REAL + index * FIO_MOFFSET(GPIO,0x00001000)) = data;
}
GH_INLINE U32  GH_GPIO_get_IS(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_GPIO_IS_REAL + index * FIO_MOFFSET(GPIO,0x00001000)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_IBE (read/write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_IBE(U8 index, U32 data)
{
    *(volatile U32 *)(REG_GPIO_IBE_REAL + index * FIO_MOFFSET(GPIO,0x00001000)) = data;
}
GH_INLINE U32  GH_GPIO_get_IBE(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_GPIO_IBE_REAL + index * FIO_MOFFSET(GPIO,0x00001000)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_IEV (read/write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_IEV(U8 index, U32 data)
{
    *(volatile U32 *)(REG_GPIO_IEV_REAL + index * FIO_MOFFSET(GPIO,0x00001000)) = data;
}
GH_INLINE U32  GH_GPIO_get_IEV(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_GPIO_IEV_REAL + index * FIO_MOFFSET(GPIO,0x00001000)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_IE (read/write)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_IE(U8 index, U32 data)
{
    *(volatile U32 *)(REG_GPIO_IE_REAL + index * FIO_MOFFSET(GPIO,0x00001000)) = data;
}
GH_INLINE U32  GH_GPIO_get_IE(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_GPIO_IE_REAL + index * FIO_MOFFSET(GPIO,0x00001000)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_AFSEL (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_AFSEL(U8 index, U32 data)
{
    *(volatile U32 *)(REG_GPIO_AFSEL_REAL + index * FIO_MOFFSET(GPIO,0x00001000)) = data;
}
GH_INLINE U32  GH_GPIO_get_AFSEL(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_GPIO_AFSEL_REAL + index * FIO_MOFFSET(GPIO,0x00001000)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_RIS (read)                                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_GPIO_get_RIS(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_GPIO_RIS_REAL + index * FIO_MOFFSET(GPIO,0x00001000)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_MIS (read)                                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_GPIO_get_MIS(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_GPIO_MIS_REAL + index * FIO_MOFFSET(GPIO,0x00001000)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_IC (write)                                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_IC(U8 index, U32 data)
{
    m_gpio_ic[index] = data;
    *(volatile U32 *)(REG_GPIO_IC_REAL + index * FIO_MOFFSET(GPIO,0x00001000)) = data;
}
GH_INLINE U32  GH_GPIO_getm_IC(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_IC] --> 0x%08x\n",
                        m_gpio_ic[index]);
    #endif
    return m_gpio_ic[index];
}

/*----------------------------------------------------------------------------*/
/* register GPIO_MASK (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_MASK(U8 index, U32 data)
{
    *(volatile U32 *)(REG_GPIO_MASK_REAL + index * FIO_MOFFSET(GPIO,0x00001000)) = data;
}
GH_INLINE U32  GH_GPIO_get_MASK(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_GPIO_MASK_REAL + index * FIO_MOFFSET(GPIO,0x00001000)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register GPIO_ENABLE (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_set_ENABLE(U8 index, U32 data)
{
    GH_GPIO_ENABLE_REAL_S real;
    GH_GPIO_ENABLE_S dummy;
    dummy.all = data ;
    real.bitc.enb = dummy.bitc.enb;
    *(volatile U32 *)(REG_GPIO_ENABLE_REAL + index * FIO_MOFFSET(GPIO,0x00001000)) = real.all;
}
GH_INLINE U32  GH_GPIO_get_ENABLE(U8 index)
{
    GH_GPIO_ENABLE_REAL_S real;
    GH_GPIO_ENABLE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_GPIO_ENABLE_REAL + index * FIO_MOFFSET(GPIO,0x00001000)));

    dummy.bitc.enb = real.bitc.enb;
    return dummy.all;
}
GH_INLINE void GH_GPIO_set_ENABLE_enb(U8 index, U8 data)
{
    GH_GPIO_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)(REG_GPIO_ENABLE_REAL + index * FIO_MOFFSET(GPIO,0x00001000));
    d.bitc.enb = data;
    *(volatile U32 *)(REG_GPIO_ENABLE_REAL + index * FIO_MOFFSET(GPIO,0x00001000)) = d.all;
}
GH_INLINE U8   GH_GPIO_get_ENABLE_enb(U8 index)
{
    GH_GPIO_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_GPIO_ENABLE_REAL + index * FIO_MOFFSET(GPIO,0x00001000)));

    tmp_value.all = value;
    return tmp_value.bitc.enb;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_GPIO_init(void)
{
    int i;

    for (i=0; i<6; i++)
    {
        GH_GPIO_set_ENABLE(i, (U32)0x00000000);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

