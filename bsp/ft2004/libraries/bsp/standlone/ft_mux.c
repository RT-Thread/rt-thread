/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-05-25 10:51:59
 * @Description:  This files is for pin mux
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_mux.h"
#include "ft_io.h"
#include "ft_assert.h"
#include "ft_printf.h"

/**
 * Description: enable i2c 1 ~ 3 pin pad mux
 * Date: 2021-03-24 13:34:06
 * Param:
 * return {*}
 * param {FT_IN u32} I2cId, i2c 0 ~ 3
 */
void Ft_setI2cMux(FT_IN u32 I2cId)
{
    u32 RegValue;

    switch (I2cId)
    {
    case I2C0_ID:
        /* i2c0 is by default enabled */
        break;
    case I2C1_ID:
        /* select i2c1 SCL, SDA mux */
        RegValue = Ft_in32(FT_PIN_DEMUX_BASE + FT_PIN_DEMUX_REG200_OFFSET);
        RegValue |= (I2C1_SCL_PIN_REG200_BIT | I2C1_SDA_PIN_REG200_BIT);
        Ft_out32(FT_PIN_DEMUX_BASE + FT_PIN_DEMUX_REG200_OFFSET, RegValue);
        break;
    case I2C2_ID:
        Ft_assertNoneReturn(0);
        break;
    case I2C3_ID:
        Ft_assertNoneReturn(0);
        break;
    default:
        Ft_assertNoneReturn(0);
        break;
    }

    return;
}

void Ft_setSpiMux(FT_IN u32 SpiId)
{
    u32 RegValue;

    switch (SpiId)
    {
    case SPI0_ID:
        /* spi0 is by default enabled */
        RegValue = Ft_in32(FT_PIN_DEMUX_BASE + FT_PIN_DEMUX_REG208_OFFSET);
        /* clear specific bits to choose Func 0 */
        RegValue |= SPI1_PORTA5_PIN_REG208_BIT;
        Ft_out32(FT_PIN_DEMUX_BASE + FT_PIN_DEMUX_REG208_OFFSET, RegValue);
        Ft_printf("bef reg 208 0x%x\r\n", Ft_in32(FT_PIN_DEMUX_BASE + FT_PIN_DEMUX_REG208_OFFSET));

        break;
    case SPI1_ID:
        /* select spi cs, sck, so, si pin mux */
        Ft_printf("bef reg 210 0x%x\r\n", Ft_in32(FT_PIN_DEMUX_BASE + FT_PIN_DEMUX_REG210_OFFSET));
        RegValue = Ft_in32(FT_PIN_DEMUX_BASE + FT_PIN_DEMUX_REG210_OFFSET);
        RegValue |= SPI1_CSN0_PIN_REG210_BIT;
        Ft_out32(FT_PIN_DEMUX_BASE + FT_PIN_DEMUX_REG210_OFFSET, RegValue);
        Ft_printf("aft reg 210 0x%x\r\n", Ft_in32(FT_PIN_DEMUX_BASE + FT_PIN_DEMUX_REG210_OFFSET));

        Ft_printf("bef reg 214 0x%x\r\n", Ft_in32(FT_PIN_DEMUX_BASE + FT_PIN_DEMUX_REG214_OFFSET));
        RegValue = Ft_in32(FT_PIN_DEMUX_BASE + FT_PIN_DEMUX_REG214_OFFSET);
        RegValue |= SPI1_SCK_PIN_REG214_BIT | SPI1_SO_PIN_REG214_BIT | SPI1_SI_PIN_REG214_BIT;
        Ft_out32(FT_PIN_DEMUX_BASE + FT_PIN_DEMUX_REG214_OFFSET, RegValue);
        Ft_printf("aft reg 214 0x%x\r\n", Ft_in32(FT_PIN_DEMUX_BASE + FT_PIN_DEMUX_REG214_OFFSET));
        break;
    default:
        break;
    }

    return;
}
