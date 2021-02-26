/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-12-12      Wayne        First version
*
******************************************************************************/

#include "board.h"

static void nu_pin_uart_init(void)
{
    /* UART0: GPF11, GPF12 */
    outpw(REG_SYS_GPF_MFPH, (inpw(REG_SYS_GPF_MFPH) & 0xfff00fff) | 0x11000);

    /* UART1: GPF9, GPF10 */
    outpw(REG_SYS_GPF_MFPH, (inpw(REG_SYS_GPF_MFPH) & 0xfffff00f) | 0x00220);
}

static void nu_pin_emac_init(void)
{
    /* EMAC0  */
    outpw(REG_SYS_GPE_MFPL, 0x11111111);
    outpw(REG_SYS_GPE_MFPH, (inpw(REG_SYS_GPE_MFPH) & ~0xFF) | 0x11);

    /* EMAC1  */
//    outpw(REG_SYS_GPF_MFPL, 0x11111111);
//    outpw(REG_SYS_GPF_MFPH, (inpw(REG_SYS_GPF_MFPH) & ~0xFF) | 0x11);
}

static void nu_pin_sdh_init(void)
{
    /* SDH1: PF[0, 6]  */
    outpw(REG_SYS_GPF_MFPL, (inpw(REG_SYS_GPF_MFPL) & ~0x0FFFFFFF) | 0x02222222);
}

static void nu_pin_qspi_init(void)
{
    /* QSPI0: PD[2, 7]  */
    outpw(REG_SYS_GPD_MFPL, (inpw(REG_SYS_GPD_MFPL) & ~0xFFFFFF00) | 0x11111100);
}

static void nu_pin_spi_init(void)
{
    /* SPI0: PD[8, 11]  */
    outpw(REG_SYS_GPD_MFPH, (inpw(REG_SYS_GPD_MFPH) & ~0x0000FFFF) | 0x00001111);
}

static void nu_pin_i2c_init(void)
{
    /* I2C0: PA[0, 1]  */
    outpw(REG_SYS_GPA_MFPL, (inpw(REG_SYS_GPA_MFPL) & ~0x000000FF) | 0x00000033);

    /* I2C2: PB5, PB7  */
    outpw(REG_SYS_GPB_MFPL, (inpw(REG_SYS_GPB_MFPL) & ~0xF0F00000) | 0x20200000);
}


static void nu_pin_pwm_init(void)
{
    /* PWM02, PWM03: PF[7, 8]  */
    outpw(REG_SYS_GPF_MFPL, (inpw(REG_SYS_GPF_MFPL) & ~0xF0000000) | 0x40000000);
    outpw(REG_SYS_GPF_MFPH, (inpw(REG_SYS_GPF_MFPH) & ~0x0000000F) | 0x00000004);
}

static void nu_pin_i2s_init(void)
{
    /* I2S A[2, 6] */
    outpw(REG_SYS_GPA_MFPL, (inpw(REG_SYS_GPA_MFPL) & ~0x0FFFFF00) | 0x02222200);
}

static void nu_pin_can_init(void)
{

}

#if defined(BSP_USING_USBD)
static void nu_pin_usbd_init(void)
{
    /* USB0_VBUSVLD, PE.11  */
    outpw(REG_SYS_GPE_MFPH, (inpw(REG_SYS_GPE_MFPH) & ~0x0000F000) | 0x00001000);
}
#endif

static void nu_pin_usbh_init(void)
{
}

void nu_pin_init(void)
{
    nu_pin_uart_init();
    nu_pin_emac_init();
    nu_pin_sdh_init();
    nu_pin_qspi_init();
    nu_pin_spi_init();
    nu_pin_i2c_init();
    nu_pin_pwm_init();
    nu_pin_i2s_init();
    nu_pin_can_init();

#if defined(BSP_USING_USBD)
    nu_pin_usbd_init();
#endif

    nu_pin_usbh_init();
}

void nu_pin_deinit(void)
{

}
