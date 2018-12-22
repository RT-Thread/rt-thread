/*!
*******************************************************************************
**
** \file      gh_gpio_amba.h
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
#ifndef _GH_GPIO_AMBA_H
#define _GH_GPIO_AMBA_H

#ifdef __LINUX__
#include "reg4linux.h"
#else
#define FIO_ADDRESS(block,address) (address)
#define FIO_MOFFSET(block,moffset) (moffset)
#endif

#ifndef __LINUX__
#include "gtypes.h" /* global type definitions */
#include "gh_lib_cfg.h" /* configuration */
#endif

#define GH_GPIO_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_GPIO_DEBUG_PRINT_FUNCTION printk
#else
#define GH_GPIO_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_GPIO_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_GPIO_DATA                                       FIO_ADDRESS(GPIO,0xa0009000) /* read/write */
#define REG_GPIO_DIR                                        FIO_ADDRESS(GPIO,0xa0009004) /* read/write */
#define REG_GPIO_IS                                         FIO_ADDRESS(GPIO,0xa0009008) /* read/write */
#define REG_GPIO_IBE                                        FIO_ADDRESS(GPIO,0xa000900C) /* read/write */
#define REG_GPIO_IEV                                        FIO_ADDRESS(GPIO,0xa0009010) /* read/write */
#define REG_GPIO_IE                                         FIO_ADDRESS(GPIO,0xa0009014) /* read/write */
#define REG_GPIO_AFSEL                                      FIO_ADDRESS(GPIO,0xa0009018) /* read/write */
#define REG_GPIO_RIS                                        FIO_ADDRESS(GPIO,0xa000901C) /* read */
#define REG_GPIO_MIS                                        FIO_ADDRESS(GPIO,0xa0009020) /* read */
#define REG_GPIO_IC                                         FIO_ADDRESS(GPIO,0xa0009024) /* write */
#define REG_GPIO_MASK                                       FIO_ADDRESS(GPIO,0xa0009028) /* read/write */
#define REG_GPIO_ENABLE                                     FIO_ADDRESS(GPIO,0xa000902C) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* GPIO_ENABLE */
    U32 all;
    struct {
        U32 enb                         : 1;
        U32                             : 31;
    } bitc;
} GH_GPIO_ENABLE_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern U32                                     m_gpio_ic[6];

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register GPIO_DATA (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_DATA'. */
void GH_GPIO_set_DATA(U8 index, U32 data);
/*! \brief Reads the register 'GPIO_DATA'. */
U32  GH_GPIO_get_DATA(U8 index);

/*----------------------------------------------------------------------------*/
/* register GPIO_DIR (read/write)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_DIR'. */
void GH_GPIO_set_DIR(U8 index, U32 data);
/*! \brief Reads the register 'GPIO_DIR'. */
U32  GH_GPIO_get_DIR(U8 index);

/*----------------------------------------------------------------------------*/
/* register GPIO_IS (read/write)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_IS'. */
void GH_GPIO_set_IS(U8 index, U32 data);
/*! \brief Reads the register 'GPIO_IS'. */
U32  GH_GPIO_get_IS(U8 index);

/*----------------------------------------------------------------------------*/
/* register GPIO_IBE (read/write)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_IBE'. */
void GH_GPIO_set_IBE(U8 index, U32 data);
/*! \brief Reads the register 'GPIO_IBE'. */
U32  GH_GPIO_get_IBE(U8 index);

/*----------------------------------------------------------------------------*/
/* register GPIO_IEV (read/write)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_IEV'. */
void GH_GPIO_set_IEV(U8 index, U32 data);
/*! \brief Reads the register 'GPIO_IEV'. */
U32  GH_GPIO_get_IEV(U8 index);

/*----------------------------------------------------------------------------*/
/* register GPIO_IE (read/write)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_IE'. */
void GH_GPIO_set_IE(U8 index, U32 data);
/*! \brief Reads the register 'GPIO_IE'. */
U32  GH_GPIO_get_IE(U8 index);

/*----------------------------------------------------------------------------*/
/* register GPIO_AFSEL (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_AFSEL'. */
void GH_GPIO_set_AFSEL(U8 index, U32 data);
/*! \brief Reads the register 'GPIO_AFSEL'. */
U32  GH_GPIO_get_AFSEL(U8 index);

/*----------------------------------------------------------------------------*/
/* register GPIO_RIS (read)                                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'GPIO_RIS'. */
U32  GH_GPIO_get_RIS(U8 index);

/*----------------------------------------------------------------------------*/
/* register GPIO_MIS (read)                                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'GPIO_MIS'. */
U32  GH_GPIO_get_MIS(U8 index);

/*----------------------------------------------------------------------------*/
/* register GPIO_IC (write)                                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_IC'. */
void GH_GPIO_set_IC(U8 index, U32 data);
/*! \brief Reads the mirror variable of the register 'GPIO_IC'. */
U32  GH_GPIO_getm_IC(U8 index);

/*----------------------------------------------------------------------------*/
/* register GPIO_MASK (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_MASK'. */
void GH_GPIO_set_MASK(U8 index, U32 data);
/*! \brief Reads the register 'GPIO_MASK'. */
U32  GH_GPIO_get_MASK(U8 index);

/*----------------------------------------------------------------------------*/
/* register GPIO_ENABLE (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_ENABLE'. */
void GH_GPIO_set_ENABLE(U8 index, U32 data);
/*! \brief Reads the register 'GPIO_ENABLE'. */
U32  GH_GPIO_get_ENABLE(U8 index);
/*! \brief Writes the bit group 'enb' of register 'GPIO_ENABLE'. */
void GH_GPIO_set_ENABLE_enb(U8 index, U8 data);
/*! \brief Reads the bit group 'enb' of register 'GPIO_ENABLE'. */
U8   GH_GPIO_get_ENABLE_enb(U8 index);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_GPIO_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_gpio_amba.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_GPIO_AMBA_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

