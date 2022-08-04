/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_base.h"

#if defined(HAL_PINCTRL_MODULE_ENABLED)

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup PINCTRL
 *  @{
 */

/** @defgroup PINCTRL_How_To_Sel_IO_Func How To Select IO Function
 *  @{

APIs support to set iomux route mode to m0,m1,...

HAL_PINCTRL_IOFuncSelFor<MODULE>(mode)

MODULE support list:

    CIF EMMC FLASH FSPI LCDC MIPICSI RGMII SDIO SDMMC0
    CAN0 CAN1 CAN2 CAN3 CAN4 CAN5
    I2C0 I2C1 I2C2 I2C3 I2C4 I2C5
    I2S0 I2S1 I2S2
    SPI0 SPI1 SPI2 SPI3 SPI4 SPI5
    PWM0 PWM1 ... PWM11
    UART0 UART1 ... UART11

examples:

    HAL_PINCTRL_IOFuncSelForCAN0(IOFUNC_SEL_M0)
    HAL_PINCTRL_IOFuncSelForCIF(IOFUNC_SEL_M0)
    HAL_PINCTRL_IOFuncSelForMIPICSI(IOFUNC_SEL_M1)
    HAL_PINCTRL_IOFuncSelForI2C0(IOFUNC_SEL_M2)
 @} */

/** @defgroup PINCTRL_Private_Definition Private Definition
 *  @{
 */
/********************* Private MACRO Definition ******************************/

/* Basic Definitions */
#define _CHECK(...)        _CHECK_(__VA_ARGS__)
#define _CHECK_(a, b, ...) b
#define _IS_PAREN(x)       _CHECK(_IS_PAREN_ x, 0)
#define _IS_PAREN_(...)    1, 1
#define _CONCAT(a, b)      _CONCAT_(a, b)
#define _CONCAT_(a, b)     a ## b
#define _DEF(x)            _IS_PAREN(x)

/* IOFUNC Select Setting Definitions */
#define _IOMUX_WRITE(REG, DATA, SHIFT, MASK)                       \
{                                                                  \
    HAL_ASSERT((uint32_t)((DATA) << (SHIFT)) <= (uint32_t)(MASK)); \
    HAL_DBG("PINCTRL Write before set reg val=0x%lx\n", REG);      \
    REG = ((DATA) << (SHIFT)) | ((MASK) << 16);                    \
    HAL_DBG("PINCTRL Write after  set reg val=0x%lx\n", REG);      \
    ret = HAL_OK;                                                  \
}

/* IOFUNC Select Basic Definition */
#define S_DEF_IF_0(x, y, z)
#define S_DEF_IF_1(x, y, z) _IOMUX_WRITE(GRF->IOFUNC_SEL##x, z, GRF_IOFUNC_SEL##x##y##_IOMUX_SEL_SHIFT, GRF_IOFUNC_SEL##x##y##_IOMUX_SEL_MASK)
#define S_COND_DEF(x, y, z) _CONCAT(S_DEF_IF_, _DEF(GRF_IOFUNC_SEL##x##y##_IOMUX_SEL_MASK))(x, y, z)
#define C_DEF_IF_0(x, y, z)
#define C_DEF_IF_1(x, y, z) _IOMUX_WRITE(GRF->IOFUNC_CON##x, z, GRF_IOFUNC_CON##x##y##_IOMUX_SEL_SHIFT, GRF_IOFUNC_CON##x##y##_IOMUX_SEL_MASK)
#define C_COND_DEF(x, y, z) _CONCAT(C_DEF_IF_, _DEF(GRF_IOFUNC_CON##x##y##_IOMUX_SEL_MASK))(x, y, z)

/**
 * @brief  HAL IOMUX Select API Basic Definition
 *
 * IOMUX SEL should be defined by members of GRF structure
 *     IOFUNC_CON0
 *     IOFUNC_CON1
 *     IOFUNC_CON2
 *     IOFUNC_CON3
 *     IOFUNC_CON4
 *     IOFUNC_CON5
 *     IOFUNC_SEL0
 *     IOFUNC_SEL1
 *     IOFUNC_SEL2
 *     IOFUNC_SEL3
 *     IOFUNC_SEL4
 *     IOFUNC_SEL5
 *
 * The HAL_PINCTRL_IOFuncSelFor<Module> will try to find valid SHIFT and MASK definition in
 * IOFUNC_CONx or IOFUNC_SELx
 *
 * SHIFT and MASK bits are defined in soc head file.
*/
#define DEFINE_IOMUX_FUNC(name)                          \
HAL_Status HAL_PINCTRL_IOFuncSelFor##name(eIOFUNC_SEL m) \
{                                                        \
    HAL_Status ret = HAL_ERROR;                          \
    S_COND_DEF(0, _##name, m)                            \
    S_COND_DEF(1, _##name, m)                            \
    S_COND_DEF(2, _##name, m)                            \
    S_COND_DEF(3, _##name, m)                            \
    S_COND_DEF(4, _##name, m)                            \
    S_COND_DEF(5, _##name, m)                            \
    C_COND_DEF(0, _##name, m)                            \
    C_COND_DEF(1, _##name, m)                            \
    C_COND_DEF(2, _##name, m)                            \
    C_COND_DEF(3, _##name, m)                            \
    C_COND_DEF(4, _##name, m)                            \
    C_COND_DEF(5, _##name, m)                            \
    HAL_ASSERT(ret != HAL_ERROR);                        \
    return ret;                                          \
}

DEFINE_IOMUX_FUNC(CIF)
DEFINE_IOMUX_FUNC(EMMC)
DEFINE_IOMUX_FUNC(FLASH)
DEFINE_IOMUX_FUNC(FSPI)
DEFINE_IOMUX_FUNC(LCDC)
DEFINE_IOMUX_FUNC(MIPICSI)
DEFINE_IOMUX_FUNC(RGMII)
DEFINE_IOMUX_FUNC(GMAC0)
DEFINE_IOMUX_FUNC(GMAC1)
DEFINE_IOMUX_FUNC(SDIO)
DEFINE_IOMUX_FUNC(SDMMC0)

DEFINE_IOMUX_FUNC(CAN0)
DEFINE_IOMUX_FUNC(CAN1)
DEFINE_IOMUX_FUNC(CAN2)
DEFINE_IOMUX_FUNC(CAN3)
DEFINE_IOMUX_FUNC(CAN4)
DEFINE_IOMUX_FUNC(CAN5)
DEFINE_IOMUX_FUNC(I2C0)
DEFINE_IOMUX_FUNC(I2C1)
DEFINE_IOMUX_FUNC(I2C2)
DEFINE_IOMUX_FUNC(I2C3)
DEFINE_IOMUX_FUNC(I2C4)
DEFINE_IOMUX_FUNC(I2C5)
DEFINE_IOMUX_FUNC(I2S0)
DEFINE_IOMUX_FUNC(I2S1)
DEFINE_IOMUX_FUNC(I2S2)
DEFINE_IOMUX_FUNC(PWM0)
DEFINE_IOMUX_FUNC(PWM1)
DEFINE_IOMUX_FUNC(PWM2)
DEFINE_IOMUX_FUNC(PWM3)
DEFINE_IOMUX_FUNC(PWM4)
DEFINE_IOMUX_FUNC(PWM5)
DEFINE_IOMUX_FUNC(PWM6)
DEFINE_IOMUX_FUNC(PWM7)
DEFINE_IOMUX_FUNC(PWM8)
DEFINE_IOMUX_FUNC(PWM9)
DEFINE_IOMUX_FUNC(PWM10)
DEFINE_IOMUX_FUNC(PWM11)
DEFINE_IOMUX_FUNC(SPI0)
DEFINE_IOMUX_FUNC(SPI1)
DEFINE_IOMUX_FUNC(SPI2)
DEFINE_IOMUX_FUNC(SPI3)
DEFINE_IOMUX_FUNC(SPI4)
DEFINE_IOMUX_FUNC(SPI5)
DEFINE_IOMUX_FUNC(UART0)
DEFINE_IOMUX_FUNC(UART1)
DEFINE_IOMUX_FUNC(UART2)
DEFINE_IOMUX_FUNC(UART3)
DEFINE_IOMUX_FUNC(UART4)
DEFINE_IOMUX_FUNC(UART5)
DEFINE_IOMUX_FUNC(UART6)
DEFINE_IOMUX_FUNC(UART7)
DEFINE_IOMUX_FUNC(UART8)
DEFINE_IOMUX_FUNC(UART9)
DEFINE_IOMUX_FUNC(UART10)
DEFINE_IOMUX_FUNC(UART11)

/** @} */

/** @} */

/** @} */

#endif /* HAL_PINCTRL_MODULE_ENABLED */
