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
    outpw(REG_SYS_GPF_MFPH, (inpw(REG_SYS_GPF_MFPH) & 0xFFF00FFF) | 0x00011000);

    /* UART4: GPC9, GPC10 */
    outpw(REG_SYS_GPC_MFPH, (inpw(REG_SYS_GPC_MFPH) & 0xFFFFF00F) | 0x00000770);

    /* UART8: GPC12, GPC13, GPC14 */
    outpw(REG_SYS_GPC_MFPH, (inpw(REG_SYS_GPC_MFPH) & 0xF000FFFF) | 0x07770000);
}

static void nu_pin_emac_init(void)
{
    /* EMAC1  */
    outpw(REG_SYS_GPF_MFPL, 0x11111111);
    outpw(REG_SYS_GPF_MFPH, (inpw(REG_SYS_GPF_MFPH) & 0xFFFFFF00) | 0x00000011);
}

static void nu_pin_qspi_init(void)
{
    /* QSPI0: PD[2, 5]  */
    outpw(REG_SYS_GPD_MFPL, (inpw(REG_SYS_GPD_MFPL) & 0xFF0000FF) | 0x00111100);
}

static void nu_pin_spi_init(void)
{
    /* SPI0: PC[4, 8]  */
    outpw(REG_SYS_GPC_MFPL, (inpw(REG_SYS_GPC_MFPL) & 0xF000FFFF) | 0x05560000);
    outpw(REG_SYS_GPC_MFPH, (inpw(REG_SYS_GPC_MFPH) & 0xFFFFFFF0) | 0x00000005);
}

static void nu_pin_i2c_init(void)
{
    /* I2C1: PB4, PB6 */
    outpw(REG_SYS_GPB_MFPL, (inpw(REG_SYS_GPB_MFPL) & 0xF0F0FFFF) | 0x02020000);
}

static void nu_pin_can_init(void)
{
    /* CAN3: PA0, PA1 */
    outpw(REG_SYS_GPA_MFPL, (inpw(REG_SYS_GPA_MFPL) & 0xFFFFFF00) | 0x00000077);
}

static void nu_pin_usbd_init(void)
{
    /* USB0_VBUSVLD, PE.11  */
    outpw(REG_SYS_GPE_MFPH, (inpw(REG_SYS_GPE_MFPH) & 0xFFFF0FFF) | 0x00001000);
}

static void nu_pin_usbh_init(void)
{
}

void nu_pin_init(void)
{
    nu_pin_uart_init();
    nu_pin_emac_init();
    nu_pin_qspi_init();
    nu_pin_spi_init();
    nu_pin_i2c_init();
    nu_pin_can_init();

    nu_pin_usbd_init();
    nu_pin_usbh_init();
}

void nu_pin_deinit(void)
{

}
