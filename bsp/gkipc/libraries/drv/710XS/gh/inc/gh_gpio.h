/*!
*******************************************************************************
**
** \file      gh_gpio.h
**
** \brief     These GPIO pins can be configured as I/O pins for other hardware modules..
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

/* check configuration */
#ifndef GH_INLINE_LEVEL
  #error "GH_INLINE_LEVEL is not defined!"
#endif
#if GH_INLINE_LEVEL > 2
  #error "GH_INLINE_LEVEL must be set 0, 1 or 2!"
#endif
#ifndef GH_INLINE
  #error "GH_INLINE is not defined!"
#endif

/* disable inlining for debugging */
#ifdef DEBUG
  #undef GH_INLINE_LEVEL
  #define GH_INLINE_LEVEL 0
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_GPIO_IS_LOW                                     FIO_ADDRESS(GPIO,0xA0009000) /* read/write */
#define REG_GPIO_IS_HIGH                                    FIO_ADDRESS(GPIO,0xA0009004) /* read/write */
#define REG_GPIO_IBE_LOW                                    FIO_ADDRESS(GPIO,0xA0009008) /* read/write */
#define REG_GPIO_IBE_HIGH                                   FIO_ADDRESS(GPIO,0xA000900C) /* read/write */
#define REG_GPIO_IEV_LOW                                    FIO_ADDRESS(GPIO,0xA0009010) /* read/write */
#define REG_GPIO_IEV_HIGH                                   FIO_ADDRESS(GPIO,0xA0009014) /* read/write */
#define REG_GPIO_IE_LOW                                     FIO_ADDRESS(GPIO,0xA0009018) /* read/write */
#define REG_GPIO_IE_HIGH                                    FIO_ADDRESS(GPIO,0xA000901C) /* read/write */
#define REG_GPIO_IC_LOW                                     FIO_ADDRESS(GPIO,0xA0009020) /* write */
#define REG_GPIO_IC_HIGH                                    FIO_ADDRESS(GPIO,0xA0009024) /* write */
#define REG_GPIO_RIS_LOW                                    FIO_ADDRESS(GPIO,0xA0009028) /* read */
#define REG_GPIO_RIS_HIGH                                   FIO_ADDRESS(GPIO,0xA000902C) /* read */
#define REG_GPIO_MIS_LOW                                    FIO_ADDRESS(GPIO,0xA0009030) /* read */
#define REG_GPIO_MIS_HIGH                                   FIO_ADDRESS(GPIO,0xA0009034) /* read */
#define REG_GPIO_INT_EN                                     FIO_ADDRESS(GPIO,0xA0009038) /* write */
#define REG_GPIO_PER_SEL                                    FIO_ADDRESS(GPIO,0xA000903C) /* read/write */
#define REG_GPIO_DIN_LOW                                    FIO_ADDRESS(GPIO,0xA0009040) /* read */
#define REG_GPIO_DIN_HIGH                                   FIO_ADDRESS(GPIO,0xA0009044) /* read */
#define REG_GPIO_OUTPUT_CFG                                 FIO_ADDRESS(GPIO,0xA0009100) /* write */
#define REG_GPIO_INPUT_CFG                                  FIO_ADDRESS(GPIO,0xA0009200) /* write */

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
        U32 out_sel                     : 7;
        U32                             : 1;
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
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'GPIO_IS_LOW'. */
void GH_GPIO_set_IS_LOW(U32 data);
/*! \brief Reads the register 'GPIO_IS_LOW'. */
U32  GH_GPIO_get_IS_LOW(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_GPIO_set_IS_LOW(U32 data)
{
    *(volatile U32 *)REG_GPIO_IS_LOW = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IS_LOW] <-- 0x%08x\n",
                        REG_GPIO_IS_LOW,data,data);
    #endif
}
GH_INLINE U32  GH_GPIO_get_IS_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IS_LOW);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_IS_LOW] --> 0x%08x\n",
                        REG_GPIO_IS_LOW,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_IS_HIGH (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'GPIO_IS_HIGH'. */
void GH_GPIO_set_IS_HIGH(U32 data);
/*! \brief Reads the register 'GPIO_IS_HIGH'. */
U32  GH_GPIO_get_IS_HIGH(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_GPIO_set_IS_HIGH(U32 data)
{
    *(volatile U32 *)REG_GPIO_IS_HIGH = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IS_HIGH] <-- 0x%08x\n",
                        REG_GPIO_IS_HIGH,data,data);
    #endif
}
GH_INLINE U32  GH_GPIO_get_IS_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IS_HIGH);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_IS_HIGH] --> 0x%08x\n",
                        REG_GPIO_IS_HIGH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_IBE_LOW (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'GPIO_IBE_LOW'. */
void GH_GPIO_set_IBE_LOW(U32 data);
/*! \brief Reads the register 'GPIO_IBE_LOW'. */
U32  GH_GPIO_get_IBE_LOW(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_GPIO_set_IBE_LOW(U32 data)
{
    *(volatile U32 *)REG_GPIO_IBE_LOW = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IBE_LOW] <-- 0x%08x\n",
                        REG_GPIO_IBE_LOW,data,data);
    #endif
}
GH_INLINE U32  GH_GPIO_get_IBE_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IBE_LOW);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_IBE_LOW] --> 0x%08x\n",
                        REG_GPIO_IBE_LOW,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_IBE_HIGH (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'GPIO_IBE_HIGH'. */
void GH_GPIO_set_IBE_HIGH(U32 data);
/*! \brief Reads the register 'GPIO_IBE_HIGH'. */
U32  GH_GPIO_get_IBE_HIGH(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_GPIO_set_IBE_HIGH(U32 data)
{
    *(volatile U32 *)REG_GPIO_IBE_HIGH = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IBE_HIGH] <-- 0x%08x\n",
                        REG_GPIO_IBE_HIGH,data,data);
    #endif
}
GH_INLINE U32  GH_GPIO_get_IBE_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IBE_HIGH);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_IBE_HIGH] --> 0x%08x\n",
                        REG_GPIO_IBE_HIGH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_IEV_LOW (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'GPIO_IEV_LOW'. */
void GH_GPIO_set_IEV_LOW(U32 data);
/*! \brief Reads the register 'GPIO_IEV_LOW'. */
U32  GH_GPIO_get_IEV_LOW(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_GPIO_set_IEV_LOW(U32 data)
{
    *(volatile U32 *)REG_GPIO_IEV_LOW = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IEV_LOW] <-- 0x%08x\n",
                        REG_GPIO_IEV_LOW,data,data);
    #endif
}
GH_INLINE U32  GH_GPIO_get_IEV_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IEV_LOW);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_IEV_LOW] --> 0x%08x\n",
                        REG_GPIO_IEV_LOW,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_IEV_HIGH (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'GPIO_IEV_HIGH'. */
void GH_GPIO_set_IEV_HIGH(U32 data);
/*! \brief Reads the register 'GPIO_IEV_HIGH'. */
U32  GH_GPIO_get_IEV_HIGH(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_GPIO_set_IEV_HIGH(U32 data)
{
    *(volatile U32 *)REG_GPIO_IEV_HIGH = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IEV_HIGH] <-- 0x%08x\n",
                        REG_GPIO_IEV_HIGH,data,data);
    #endif
}
GH_INLINE U32  GH_GPIO_get_IEV_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IEV_HIGH);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_IEV_HIGH] --> 0x%08x\n",
                        REG_GPIO_IEV_HIGH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_IE_LOW (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'GPIO_IE_LOW'. */
void GH_GPIO_set_IE_LOW(U32 data);
/*! \brief Reads the register 'GPIO_IE_LOW'. */
U32  GH_GPIO_get_IE_LOW(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_GPIO_set_IE_LOW(U32 data)
{
    *(volatile U32 *)REG_GPIO_IE_LOW = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IE_LOW] <-- 0x%08x\n",
                        REG_GPIO_IE_LOW,data,data);
    #endif
}
GH_INLINE U32  GH_GPIO_get_IE_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IE_LOW);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_IE_LOW] --> 0x%08x\n",
                        REG_GPIO_IE_LOW,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_IE_HIGH (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'GPIO_IE_HIGH'. */
void GH_GPIO_set_IE_HIGH(U32 data);
/*! \brief Reads the register 'GPIO_IE_HIGH'. */
U32  GH_GPIO_get_IE_HIGH(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_GPIO_set_IE_HIGH(U32 data)
{
    *(volatile U32 *)REG_GPIO_IE_HIGH = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IE_HIGH] <-- 0x%08x\n",
                        REG_GPIO_IE_HIGH,data,data);
    #endif
}
GH_INLINE U32  GH_GPIO_get_IE_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_IE_HIGH);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_IE_HIGH] --> 0x%08x\n",
                        REG_GPIO_IE_HIGH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_IC_LOW (write)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'GPIO_IC_LOW'. */
void GH_GPIO_set_IC_LOW(U32 data);
/*! \brief Reads the mirror variable of the register 'GPIO_IC_LOW'. */
U32  GH_GPIO_getm_IC_LOW(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_GPIO_set_IC_LOW(U32 data)
{
    m_gpio_ic_low = data;
    *(volatile U32 *)REG_GPIO_IC_LOW = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IC_LOW] <-- 0x%08x\n",
                        REG_GPIO_IC_LOW,data,data);
    #endif
}
GH_INLINE U32  GH_GPIO_getm_IC_LOW(void)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_IC_LOW] --> 0x%08x\n",
                        m_gpio_ic_low);
    #endif
    return m_gpio_ic_low;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register GPIO_IC_HIGH (write)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'GPIO_IC_HIGH'. */
void GH_GPIO_set_IC_HIGH(U32 data);
/*! \brief Reads the mirror variable of the register 'GPIO_IC_HIGH'. */
U32  GH_GPIO_getm_IC_HIGH(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_GPIO_set_IC_HIGH(U32 data)
{
    m_gpio_ic_high = data;
    *(volatile U32 *)REG_GPIO_IC_HIGH = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_IC_HIGH] <-- 0x%08x\n",
                        REG_GPIO_IC_HIGH,data,data);
    #endif
}
GH_INLINE U32  GH_GPIO_getm_IC_HIGH(void)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_IC_HIGH] --> 0x%08x\n",
                        m_gpio_ic_high);
    #endif
    return m_gpio_ic_high;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register GPIO_RIS_LOW (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'GPIO_RIS_LOW'. */
U32  GH_GPIO_get_RIS_LOW(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_GPIO_get_RIS_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_RIS_LOW);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_RIS_LOW] --> 0x%08x\n",
                        REG_GPIO_RIS_LOW,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_RIS_HIGH (read)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'GPIO_RIS_HIGH'. */
U32  GH_GPIO_get_RIS_HIGH(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_GPIO_get_RIS_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_RIS_HIGH);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_RIS_HIGH] --> 0x%08x\n",
                        REG_GPIO_RIS_HIGH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_MIS_LOW (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'GPIO_MIS_LOW'. */
U32  GH_GPIO_get_MIS_LOW(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_GPIO_get_MIS_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_MIS_LOW);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_MIS_LOW] --> 0x%08x\n",
                        REG_GPIO_MIS_LOW,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_MIS_HIGH (read)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'GPIO_MIS_HIGH'. */
U32  GH_GPIO_get_MIS_HIGH(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_GPIO_get_MIS_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_MIS_HIGH);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_MIS_HIGH] --> 0x%08x\n",
                        REG_GPIO_MIS_HIGH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_INT_EN (write)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'GPIO_INT_EN'. */
void GH_GPIO_set_INT_EN(U32 data);
/*! \brief Reads the mirror variable of the register 'GPIO_INT_EN'. */
U32  GH_GPIO_getm_INT_EN(void);
/*! \brief Writes the bit group 'int_en' of register 'GPIO_INT_EN'. */
void GH_GPIO_set_INT_EN_int_en(U8 data);
/*! \brief Reads the bit group 'int_en' from the mirror variable of register 'GPIO_INT_EN'. */
U8   GH_GPIO_getm_INT_EN_int_en(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_GPIO_set_INT_EN(U32 data)
{
    m_gpio_int_en.all = data;
    *(volatile U32 *)REG_GPIO_INT_EN = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_INT_EN] <-- 0x%08x\n",
                        REG_GPIO_INT_EN,data,data);
    #endif
}
GH_INLINE U32  GH_GPIO_getm_INT_EN(void)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_INT_EN] --> 0x%08x\n",
                        m_gpio_int_en.all);
    #endif
    return m_gpio_int_en.all;
}
GH_INLINE void GH_GPIO_set_INT_EN_int_en(U8 data)
{
    m_gpio_int_en.bitc.int_en = data;
    *(volatile U32 *)REG_GPIO_INT_EN = m_gpio_int_en.all;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_INT_EN_int_en] <-- 0x%08x\n",
                        REG_GPIO_INT_EN,m_gpio_int_en.all,m_gpio_int_en.all);
    #endif
}
GH_INLINE U8   GH_GPIO_getm_INT_EN_int_en(void)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_INT_EN_int_en] --> 0x%08x\n",
                        m_gpio_int_en.bitc.int_en);
    #endif
    return m_gpio_int_en.bitc.int_en;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register GPIO_PER_SEL (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
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
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_GPIO_set_PER_SEL(U32 data)
{
    *(volatile U32 *)REG_GPIO_PER_SEL = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_PER_SEL] <-- 0x%08x\n",
                        REG_GPIO_PER_SEL,data,data);
    #endif
}
GH_INLINE U32  GH_GPIO_get_PER_SEL(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_PER_SEL);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_PER_SEL] --> 0x%08x\n",
                        REG_GPIO_PER_SEL,value);
    #endif
    return value;
}
GH_INLINE void GH_GPIO_set_PER_SEL_enet_sel(U8 data)
{
    GH_GPIO_PER_SEL_S d;
    d.all = *(volatile U32 *)REG_GPIO_PER_SEL;
    d.bitc.enet_sel = data;
    *(volatile U32 *)REG_GPIO_PER_SEL = d.all;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_PER_SEL_enet_sel] <-- 0x%08x\n",
                        REG_GPIO_PER_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_GPIO_get_PER_SEL_enet_sel(void)
{
    GH_GPIO_PER_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_GPIO_PER_SEL);

    tmp_value.all = value;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_PER_SEL_enet_sel] --> 0x%08x\n",
                        REG_GPIO_PER_SEL,value);
    #endif
    return tmp_value.bitc.enet_sel;
}
GH_INLINE void GH_GPIO_set_PER_SEL_i2s_sel(U8 data)
{
    GH_GPIO_PER_SEL_S d;
    d.all = *(volatile U32 *)REG_GPIO_PER_SEL;
    d.bitc.i2s_sel = data;
    *(volatile U32 *)REG_GPIO_PER_SEL = d.all;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_PER_SEL_i2s_sel] <-- 0x%08x\n",
                        REG_GPIO_PER_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_GPIO_get_PER_SEL_i2s_sel(void)
{
    GH_GPIO_PER_SEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_GPIO_PER_SEL);

    tmp_value.all = value;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_PER_SEL_i2s_sel] --> 0x%08x\n",
                        REG_GPIO_PER_SEL,value);
    #endif
    return tmp_value.bitc.i2s_sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_DIN_LOW (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'GPIO_DIN_LOW'. */
U32  GH_GPIO_get_DIN_LOW(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_GPIO_get_DIN_LOW(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_DIN_LOW);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_DIN_LOW] --> 0x%08x\n",
                        REG_GPIO_DIN_LOW,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_DIN_HIGH (read)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'GPIO_DIN_HIGH'. */
U32  GH_GPIO_get_DIN_HIGH(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_GPIO_get_DIN_HIGH(void)
{
    U32 value = (*(volatile U32 *)REG_GPIO_DIN_HIGH);

    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GPIO_get_DIN_HIGH] --> 0x%08x\n",
                        REG_GPIO_DIN_HIGH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GPIO_OUTPUT_CFG (write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
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
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_GPIO_set_OUTPUT_CFG(U8 index, U32 data)
{
    m_gpio_output_cfg[index].all = data;
    *(volatile U32 *)(REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)) = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_OUTPUT_CFG] <-- 0x%08x\n",
                        (REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)),data,data);
    #endif
}
GH_INLINE U32  GH_GPIO_getm_OUTPUT_CFG(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_OUTPUT_CFG] --> 0x%08x\n",
                        m_gpio_output_cfg[index].all);
    #endif
    return m_gpio_output_cfg[index].all;
}
GH_INLINE void GH_GPIO_set_OUTPUT_CFG_out_sel(U8 index, U8 data)
{
    m_gpio_output_cfg[index].bitc.out_sel = data;
    *(volatile U32 *)(REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)) = m_gpio_output_cfg[index].all;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_OUTPUT_CFG_out_sel] <-- 0x%08x\n",
                        (REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)),m_gpio_output_cfg[index].all,m_gpio_output_cfg[index].all);
    #endif
}
GH_INLINE U8   GH_GPIO_getm_OUTPUT_CFG_out_sel(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_OUTPUT_CFG_out_sel] --> 0x%08x\n",
                        m_gpio_output_cfg[index].bitc.out_sel);
    #endif
    return m_gpio_output_cfg[index].bitc.out_sel;
}
GH_INLINE void GH_GPIO_set_OUTPUT_CFG_oen_sel(U8 index, U8 data)
{
    m_gpio_output_cfg[index].bitc.oen_sel = data;
    *(volatile U32 *)(REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)) = m_gpio_output_cfg[index].all;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_OUTPUT_CFG_oen_sel] <-- 0x%08x\n",
                        (REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)),m_gpio_output_cfg[index].all,m_gpio_output_cfg[index].all);
    #endif
}
GH_INLINE U8   GH_GPIO_getm_OUTPUT_CFG_oen_sel(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_OUTPUT_CFG_oen_sel] --> 0x%08x\n",
                        m_gpio_output_cfg[index].bitc.oen_sel);
    #endif
    return m_gpio_output_cfg[index].bitc.oen_sel;
}
GH_INLINE void GH_GPIO_set_OUTPUT_CFG_out_invert(U8 index, U8 data)
{
    m_gpio_output_cfg[index].bitc.out_invert = data;
    *(volatile U32 *)(REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)) = m_gpio_output_cfg[index].all;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_OUTPUT_CFG_out_invert] <-- 0x%08x\n",
                        (REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)),m_gpio_output_cfg[index].all,m_gpio_output_cfg[index].all);
    #endif
}
GH_INLINE U8   GH_GPIO_getm_OUTPUT_CFG_out_invert(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_OUTPUT_CFG_out_invert] --> 0x%08x\n",
                        m_gpio_output_cfg[index].bitc.out_invert);
    #endif
    return m_gpio_output_cfg[index].bitc.out_invert;
}
GH_INLINE void GH_GPIO_set_OUTPUT_CFG_oen_invert(U8 index, U8 data)
{
    m_gpio_output_cfg[index].bitc.oen_invert = data;
    *(volatile U32 *)(REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)) = m_gpio_output_cfg[index].all;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_OUTPUT_CFG_oen_invert] <-- 0x%08x\n",
                        (REG_GPIO_OUTPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)),m_gpio_output_cfg[index].all,m_gpio_output_cfg[index].all);
    #endif
}
GH_INLINE U8   GH_GPIO_getm_OUTPUT_CFG_oen_invert(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_OUTPUT_CFG_oen_invert] --> 0x%08x\n",
                        m_gpio_output_cfg[index].bitc.oen_invert);
    #endif
    return m_gpio_output_cfg[index].bitc.oen_invert;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register GPIO_INPUT_CFG (write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'GPIO_INPUT_CFG'. */
void GH_GPIO_set_INPUT_CFG(U8 index, U32 data);
/*! \brief Reads the mirror variable of the register 'GPIO_INPUT_CFG'. */
U32  GH_GPIO_getm_INPUT_CFG(U8 index);
/*! \brief Writes the bit group 'in_sel' of register 'GPIO_INPUT_CFG'. */
void GH_GPIO_set_INPUT_CFG_in_sel(U8 index, U8 data);
/*! \brief Reads the bit group 'in_sel' from the mirror variable of register 'GPIO_INPUT_CFG'. */
U8   GH_GPIO_getm_INPUT_CFG_in_sel(U8 index);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_GPIO_set_INPUT_CFG(U8 index, U32 data)
{
    m_gpio_input_cfg[index].all = data;
    *(volatile U32 *)(REG_GPIO_INPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)) = data;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_INPUT_CFG] <-- 0x%08x\n",
                        (REG_GPIO_INPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)),data,data);
    #endif
}
GH_INLINE U32  GH_GPIO_getm_INPUT_CFG(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_INPUT_CFG] --> 0x%08x\n",
                        m_gpio_input_cfg[index].all);
    #endif
    return m_gpio_input_cfg[index].all;
}
GH_INLINE void GH_GPIO_set_INPUT_CFG_in_sel(U8 index, U8 data)
{
    m_gpio_input_cfg[index].bitc.in_sel = data;
    *(volatile U32 *)(REG_GPIO_INPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)) = m_gpio_input_cfg[index].all;
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GPIO_set_INPUT_CFG_in_sel] <-- 0x%08x\n",
                        (REG_GPIO_INPUT_CFG + index * FIO_MOFFSET(GPIO,0x4)),m_gpio_input_cfg[index].all,m_gpio_input_cfg[index].all);
    #endif
}
GH_INLINE U8   GH_GPIO_getm_INPUT_CFG_in_sel(U8 index)
{
    #if GH_GPIO_ENABLE_DEBUG_PRINT
    GH_GPIO_DEBUG_PRINT_FUNCTION( "[GH_GPIO_getm_INPUT_CFG_in_sel] --> 0x%08x\n",
                        m_gpio_input_cfg[index].bitc.in_sel);
    #endif
    return m_gpio_input_cfg[index].bitc.in_sel;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_GPIO_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_GPIO_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

