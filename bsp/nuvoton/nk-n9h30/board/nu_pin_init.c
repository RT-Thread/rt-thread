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
    /* UART0: PE[0, 1] */
    outpw(REG_SYS_GPE_MFPL, (inpw(REG_SYS_GPE_MFPL) & 0xffffff00) | 0x00000099);

    /* UART1: PH[4, 7] */
    outpw(REG_SYS_GPH_MFPL, (inpw(REG_SYS_GPH_MFPL) & 0x0000ffff) | 0x99990000);

    /* UART2: PF[11, 14] */
    outpw(REG_SYS_GPF_MFPH, (inpw(REG_SYS_GPF_MFPH) & 0xf0000fff) | 0x09999000);

    /* UART3: PE[12, 13] */
    outpw(REG_SYS_GPE_MFPH, (inpw(REG_SYS_GPE_MFPH) & 0xff00ffff) | 0x00990000);

    /* UART4: PH[8, 11] */
    outpw(REG_SYS_GPH_MFPH, (inpw(REG_SYS_GPH_MFPH) & 0xffff0000) | 0x00009999);

    /* UART5: PB[0, 1] */
    outpw(REG_SYS_GPB_MFPL, (inpw(REG_SYS_GPB_MFPL) & 0xffffff00) | 0x00000099);

    /* UART7: PI[1, 2] */
    outpw(REG_SYS_GPI_MFPL, (inpw(REG_SYS_GPI_MFPL) & 0xfffff00f) | 0x00000990);

    /* UART8: PH[12, 15] */
    outpw(REG_SYS_GPH_MFPH, (inpw(REG_SYS_GPH_MFPH) & 0x0000ffff) | 0x99990000);

    /* UART10: PB[12, 15] */
    outpw(REG_SYS_GPB_MFPH, (inpw(REG_SYS_GPB_MFPH) & 0x0000ffff) | 0x99990000);
}

static void nu_pin_emac_init(void)
{
    /* EMAC0: PF[0, 9] */
    outpw(REG_SYS_GPF_MFPL, 0x11111111);
    outpw(REG_SYS_GPF_MFPH, (inpw(REG_SYS_GPF_MFPH) & 0xffffff00) | 0x00000011);

    /* EMAC1: PE[2, 11] */
    outpw(REG_SYS_GPE_MFPL, (inpw(REG_SYS_GPE_MFPL) & 0x000000ff) | 0x11111100);
    outpw(REG_SYS_GPE_MFPH, (inpw(REG_SYS_GPE_MFPH) & 0xffff0000) | 0x00001111);
}

static void nu_pin_sdh_init(void)
{
    /* SDH0: PD[0, 6] */
    outpw(REG_SYS_GPD_MFPL, (inpw(REG_SYS_GPD_MFPL) & 0xf0000000) | 0x06666666);
}

static void nu_pin_spi_init(void)
{
    /* QSPI0: PB[6, 11] */
    outpw(REG_SYS_GPB_MFPL, (inpw(REG_SYS_GPB_MFPL) & 0x00ffffff) | 0xbb000000);
    outpw(REG_SYS_GPB_MFPH, (inpw(REG_SYS_GPB_MFPH) & 0xffff0000) | 0x0000bbbb);
}

static void nu_pin_i2c_init(void)
{
    /* I2C0: PG[0, 1] */
    outpw(REG_SYS_GPG_MFPL, (inpw(REG_SYS_GPG_MFPL) & 0xffffff00) | 0x00000088);

    /* I2C1: PG[2, 3] */
    outpw(REG_SYS_GPG_MFPL, (inpw(REG_SYS_GPG_MFPL) & 0xffff00ff) | 0x00008800);
}

static void nu_pin_pwm_init(void)
{
    /* PWM0: PB2, LCD_PWM */
    outpw(REG_SYS_GPB_MFPL, (inpw(REG_SYS_GPB_MFPL) & 0xfffff0ff) | 0x00000d00);

    /* PWM1: PB3, Buzzer */
    outpw(REG_SYS_GPB_MFPL, (inpw(REG_SYS_GPB_MFPL) & 0xffff0fff) | 0x0000d000);
}

static void nu_pin_i2s_init(void)
{
    /* I2S: PG[10, 14] */
    outpw(REG_SYS_GPG_MFPH, (inpw(REG_SYS_GPG_MFPH) & 0xf00000ff) | 0x08888800);
}

static void nu_pin_can_init(void)
{
    /* CAN0: PI[3, 4] */
    outpw(REG_SYS_GPI_MFPL, (inpw(REG_SYS_GPI_MFPL) & 0xfff00fff) | 0x000cc000);
}

static void nu_pin_usbd_init(void)
{
    /* USB0_VBUSVLD, PH0  */
    outpw(REG_SYS_GPH_MFPL, (inpw(REG_SYS_GPH_MFPL) & 0xfffffff0) | 0x00000007);
}

static void nu_pin_vpost_init(void)
{
    /* CLK: PG6, HSYNC: PG7 */
    outpw(REG_SYS_GPG_MFPL, (inpw(REG_SYS_GPG_MFPL) & 0x00ffffff) | 0x22000000);
    /* VSYNC: PG8, DEN: PG9 */
    outpw(REG_SYS_GPG_MFPH, (inpw(REG_SYS_GPG_MFPH) & 0xffffff00) | 0x00000022);

    /* DATA pin: 24bit RGB */
    /* PA[0, 7] */
    outpw(REG_SYS_GPA_MFPL, 0x22222222);
    /* PA[8, 15] */
    outpw(REG_SYS_GPA_MFPH, 0x22222222);
#if (BSP_LCD_BPP==32)
    /* PD[8, 15 ] */
    outpw(REG_SYS_GPD_MFPH, 0x22222222);
#endif
}

static void nu_pin_fmi_init(void)
{
    /* select NAND function pins */
    if (inpw(REG_SYS_PWRON) & 0x08000000)
    {
        /* NAND: PI[0, 14] */
        outpw(REG_SYS_GPI_MFPL, 0x55555550);
        outpw(REG_SYS_GPI_MFPH, 0x55555555);
    }
    else
    {
        /* NAND: PC[0, 14] */
        outpw(REG_SYS_GPC_MFPL, 0x55555555);
        outpw(REG_SYS_GPC_MFPH, 0x05555555);
    }
}

static void nu_pin_usbh_init(void)
{

}

void nu_pin_init(void)
{
    nu_pin_uart_init();
    nu_pin_emac_init();
    nu_pin_sdh_init();
    nu_pin_spi_init();
    nu_pin_i2c_init();
    nu_pin_pwm_init();
    nu_pin_i2s_init();
    nu_pin_can_init();
    nu_pin_vpost_init();
    nu_pin_fmi_init();
    nu_pin_usbd_init();
    nu_pin_usbh_init();
}

void nu_pin_deinit(void)
{

}
