/*!
*******************************************************************************
**
** \file      gh_gpio.h
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
#ifndef _GH_GPIO_H
#define _GH_GPIO_H

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
#define REG_GPIO_IS_LOW                                     FIO_ADDRESS(GPIO,0xa0009000) /* read/write */
#define REG_GPIO_IS_HIGH                                    FIO_ADDRESS(GPIO,0xa0009004) /* read/write */
#define REG_GPIO_IBE_LOW                                    FIO_ADDRESS(GPIO,0xa0009008) /* read/write */
#define REG_GPIO_IBE_HIGH                                   FIO_ADDRESS(GPIO,0xa000900C) /* read/write */
#define REG_GPIO_IEV_LOW                                    FIO_ADDRESS(GPIO,0xa0009010) /* read/write */
#define REG_GPIO_IEV_HIGH                                   FIO_ADDRESS(GPIO,0xa0009014) /* read/write */
#define REG_GPIO_IE_LOW                                     FIO_ADDRESS(GPIO,0xa0009018) /* read/write */
#define REG_GPIO_IE_HIGH                                    FIO_ADDRESS(GPIO,0xa000901C) /* read/write */
#define REG_GPIO_IC_LOW                                     FIO_ADDRESS(GPIO,0xa0009020) /* write */
#define REG_GPIO_IC_HIGH                                    FIO_ADDRESS(GPIO,0xa0009024) /* write */
#define REG_GPIO_RIS_LOW                                    FIO_ADDRESS(GPIO,0xa0009028) /* read */
#define REG_GPIO_RIS_HIGH                                   FIO_ADDRESS(GPIO,0xa000902C) /* read */
#define REG_GPIO_MIS_LOW                                    FIO_ADDRESS(GPIO,0xa0009030) /* read */
#define REG_GPIO_MIS_HIGH                                   FIO_ADDRESS(GPIO,0xa0009034) /* read */
#define REG_GPIO_INT_EN                                     FIO_ADDRESS(GPIO,0xa0009038) /* write */
#define REG_GPIO_PER_SEL                                    FIO_ADDRESS(GPIO,0xa000903C) /* read/write */
#define REG_GPIO_DIN_LOW                                    FIO_ADDRESS(GPIO,0xa0009040) /* read */
#define REG_GPIO_DIN_HIGH                                   FIO_ADDRESS(GPIO,0xa0009044) /* read */
#define REG_GPIO_OUTPUT_CFG                                 FIO_ADDRESS(GPIO,0xa0009100) /* write */
#define REG_GPIO_INPUT_CFG                                  FIO_ADDRESS(GPIO,0xa0009200) /* write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* GPIO_INT_EN */
    U32 all;
    struct {
        U32 int_en                      : 1;
        U32                             : 31;
    } bitc;
} GH_GPIO_INT_EN_S;

typedef union { /* GPIO_PER_SEL */
    U32 all;
    struct {
        U32 enet_sel                    : 1;
        U32 i2s_sel                     : 1;
        U32                             : 30;
    } bitc;
} GH_GPIO_PER_SEL_S;

typedef union { /* GPIO_OUTPUT_CFG */
    U32 all;
    struct {
        U32 out_sel                     : 6;
        U32                             : 2;
        U32 oen_sel                     : 6;
        U32 out_invert                  : 1;
        U32 oen_invert                  : 1;
        U32                             : 16;
    } bitc;
} GH_GPIO_OUTPUT_CFG_S;

typedef union { /* GPIO_INPUT_CFG */
    U32 all;
    struct {
        U32 in_sel                      : 6;
        U32                             : 26;
    } bitc;
} GH_GPIO_INPUT_CFG_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern U32                                     m_gpio_ic_low;
extern U32                                     m_gpio_ic_high;
extern GH_GPIO_INT_EN_S                        m_gpio_int_en;
extern GH_GPIO_OUTPUT_CFG_S                    m_gpio_output_cfg[64];
extern GH_GPIO_INPUT_CFG_S                     m_gpio_input_cfg[64];

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register GPIO_IS_LOW (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_IS_LOW'. */
void GH_GPIO_set_IS_LOW(U32 data);
/*! \brief Reads the register 'GPIO_IS_LOW'. */
U32  GH_GPIO_get_IS_LOW(void);

/*----------------------------------------------------------------------------*/
/* register GPIO_IS_HIGH (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_IS_HIGH'. */
void GH_GPIO_set_IS_HIGH(U32 data);
/*! \brief Reads the register 'GPIO_IS_HIGH'. */
U32  GH_GPIO_get_IS_HIGH(void);

/*----------------------------------------------------------------------------*/
/* register GPIO_IBE_LOW (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_IBE_LOW'. */
void GH_GPIO_set_IBE_LOW(U32 data);
/*! \brief Reads the register 'GPIO_IBE_LOW'. */
U32  GH_GPIO_get_IBE_LOW(void);

/*----------------------------------------------------------------------------*/
/* register GPIO_IBE_HIGH (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_IBE_HIGH'. */
void GH_GPIO_set_IBE_HIGH(U32 data);
/*! \brief Reads the register 'GPIO_IBE_HIGH'. */
U32  GH_GPIO_get_IBE_HIGH(void);

/*----------------------------------------------------------------------------*/
/* register GPIO_IEV_LOW (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_IEV_LOW'. */
void GH_GPIO_set_IEV_LOW(U32 data);
/*! \brief Reads the register 'GPIO_IEV_LOW'. */
U32  GH_GPIO_get_IEV_LOW(void);

/*----------------------------------------------------------------------------*/
/* register GPIO_IEV_HIGH (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_IEV_HIGH'. */
void GH_GPIO_set_IEV_HIGH(U32 data);
/*! \brief Reads the register 'GPIO_IEV_HIGH'. */
U32  GH_GPIO_get_IEV_HIGH(void);

/*----------------------------------------------------------------------------*/
/* register GPIO_IE_LOW (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_IE_LOW'. */
void GH_GPIO_set_IE_LOW(U32 data);
/*! \brief Reads the register 'GPIO_IE_LOW'. */
U32  GH_GPIO_get_IE_LOW(void);

/*----------------------------------------------------------------------------*/
/* register GPIO_IE_HIGH (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_IE_HIGH'. */
void GH_GPIO_set_IE_HIGH(U32 data);
/*! \brief Reads the register 'GPIO_IE_HIGH'. */
U32  GH_GPIO_get_IE_HIGH(void);

/*----------------------------------------------------------------------------*/
/* register GPIO_IC_LOW (write)                                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_IC_LOW'. */
void GH_GPIO_set_IC_LOW(U32 data);
/*! \brief Reads the mirror variable of the register 'GPIO_IC_LOW'. */
U32  GH_GPIO_getm_IC_LOW(void);

/*----------------------------------------------------------------------------*/
/* register GPIO_IC_HIGH (write)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_IC_HIGH'. */
void GH_GPIO_set_IC_HIGH(U32 data);
/*! \brief Reads the mirror variable of the register 'GPIO_IC_HIGH'. */
U32  GH_GPIO_getm_IC_HIGH(void);

/*----------------------------------------------------------------------------*/
/* register GPIO_RIS_LOW (read)                                               */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'GPIO_RIS_LOW'. */
U32  GH_GPIO_get_RIS_LOW(void);

/*----------------------------------------------------------------------------*/
/* register GPIO_RIS_HIGH (read)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'GPIO_RIS_HIGH'. */
U32  GH_GPIO_get_RIS_HIGH(void);

/*----------------------------------------------------------------------------*/
/* register GPIO_MIS_LOW (read)                                               */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'GPIO_MIS_LOW'. */
U32  GH_GPIO_get_MIS_LOW(void);

/*----------------------------------------------------------------------------*/
/* register GPIO_MIS_HIGH (read)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'GPIO_MIS_HIGH'. */
U32  GH_GPIO_get_MIS_HIGH(void);

/*----------------------------------------------------------------------------*/
/* register GPIO_INT_EN (write)                                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_INT_EN'. */
void GH_GPIO_set_INT_EN(U32 data);
/*! \brief Reads the mirror variable of the register 'GPIO_INT_EN'. */
U32  GH_GPIO_getm_INT_EN(void);
/*! \brief Writes the bit group 'int_en' of register 'GPIO_INT_EN'. */
void GH_GPIO_set_INT_EN_int_en(U8 data);
/*! \brief Reads the bit group 'int_en' from the mirror variable of register 'GPIO_INT_EN'. */
U8   GH_GPIO_getm_INT_EN_int_en(void);

/*----------------------------------------------------------------------------*/
/* register GPIO_PER_SEL (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_PER_SEL'. */
void GH_GPIO_set_PER_SEL(U32 data);
/*! \brief Reads the register 'GPIO_PER_SEL'. */
U32  GH_GPIO_get_PER_SEL(void);
/*! \brief Writes the bit group 'enet_sel' of register 'GPIO_PER_SEL'. */
void GH_GPIO_set_PER_SEL_enet_sel(U8 data);
/*! \brief Reads the bit group 'enet_sel' of register 'GPIO_PER_SEL'. */
U8   GH_GPIO_get_PER_SEL_enet_sel(void);
/*! \brief Writes the bit group 'i2s_sel' of register 'GPIO_PER_SEL'. */
void GH_GPIO_set_PER_SEL_i2s_sel(U8 data);
/*! \brief Reads the bit group 'i2s_sel' of register 'GPIO_PER_SEL'. */
U8   GH_GPIO_get_PER_SEL_i2s_sel(void);

/*----------------------------------------------------------------------------*/
/* register GPIO_DIN_LOW (read)                                               */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'GPIO_DIN_LOW'. */
U32  GH_GPIO_get_DIN_LOW(void);

/*----------------------------------------------------------------------------*/
/* register GPIO_DIN_HIGH (read)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'GPIO_DIN_HIGH'. */
U32  GH_GPIO_get_DIN_HIGH(void);

/*----------------------------------------------------------------------------*/
/* register GPIO_OUTPUT_CFG (write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_OUTPUT_CFG'. */
void GH_GPIO_set_OUTPUT_CFG(U8 index, U32 data);
/*! \brief Reads the mirror variable of the register 'GPIO_OUTPUT_CFG'. */
U32  GH_GPIO_getm_OUTPUT_CFG(U8 index);
/*! \brief Writes the bit group 'out_sel' of register 'GPIO_OUTPUT_CFG'. */
void GH_GPIO_set_OUTPUT_CFG_out_sel(U8 index, U8 data);
/*! \brief Reads the bit group 'out_sel' from the mirror variable of register 'GPIO_OUTPUT_CFG'. */
U8   GH_GPIO_getm_OUTPUT_CFG_out_sel(U8 index);
/*! \brief Writes the bit group 'oen_sel' of register 'GPIO_OUTPUT_CFG'. */
void GH_GPIO_set_OUTPUT_CFG_oen_sel(U8 index, U8 data);
/*! \brief Reads the bit group 'oen_sel' from the mirror variable of register 'GPIO_OUTPUT_CFG'. */
U8   GH_GPIO_getm_OUTPUT_CFG_oen_sel(U8 index);
/*! \brief Writes the bit group 'out_invert' of register 'GPIO_OUTPUT_CFG'. */
void GH_GPIO_set_OUTPUT_CFG_out_invert(U8 index, U8 data);
/*! \brief Reads the bit group 'out_invert' from the mirror variable of register 'GPIO_OUTPUT_CFG'. */
U8   GH_GPIO_getm_OUTPUT_CFG_out_invert(U8 index);
/*! \brief Writes the bit group 'oen_invert' of register 'GPIO_OUTPUT_CFG'. */
void GH_GPIO_set_OUTPUT_CFG_oen_invert(U8 index, U8 data);
/*! \brief Reads the bit group 'oen_invert' from the mirror variable of register 'GPIO_OUTPUT_CFG'. */
U8   GH_GPIO_getm_OUTPUT_CFG_oen_invert(U8 index);

/*----------------------------------------------------------------------------*/
/* register GPIO_INPUT_CFG (write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GPIO_INPUT_CFG'. */
void GH_GPIO_set_INPUT_CFG(U8 index, U32 data);
/*! \brief Reads the mirror variable of the register 'GPIO_INPUT_CFG'. */
U32  GH_GPIO_getm_INPUT_CFG(U8 index);
/*! \brief Writes the bit group 'in_sel' of register 'GPIO_INPUT_CFG'. */
void GH_GPIO_set_INPUT_CFG_in_sel(U8 index, U8 data);
/*! \brief Reads the bit group 'in_sel' from the mirror variable of register 'GPIO_INPUT_CFG'. */
U8   GH_GPIO_getm_INPUT_CFG_in_sel(U8 index);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_GPIO_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_gpio.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_GPIO_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

