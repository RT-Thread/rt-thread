/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-05-26 15:39:16
 * @Description:  This files is for pin mux
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef FT_BSP_MUX_H
#define FT_BSP_MUX_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_types.h"

/* pad pin multi-function demu */
#define FT_PIN_DEMUX_BASE 0x28180000
#define FT_PIN_DEMUX_REG200_OFFSET 0x200
#define FT_PIN_DEMUX_REG204_OFFSET 0x204
#define FT_PIN_DEMUX_REG208_OFFSET 0x208
#define FT_PIN_DEMUX_REG210_OFFSET 0x210
#define FT_PIN_DEMUX_REG214_OFFSET 0x214

/* i2c mux function option */
#define I2C1_SCL_PIN_REG200_MASK ((u32)0x3 << 28) /* all_pll_lock_pad [29:28] */
#define I2C1_SCL_PIN_REG200_BIT ((u32)0x2 << 28)
#define I2C1_SDA_PIN_REG200_MASK ((u32)0x3 << 24) /* cru_clk_obv_pad [25:24] */
#define I2C1_SDA_PIN_REG200_BIT ((u32)0x2 << 24)
#define I2C2_SCL_PIN_REG204_MASK ((u32)0x3 << 8) /* swdo_swj_pad [9: 8] */
#define I2C2_SCL_PIN_REG204_BIT ((u32)0x2 << 8)
#define I2C2_SDA_PIN_REG204_MASK ((u32)0x3 << 6) /* tdo_swj_pad [7: 6] */
#define I2C2_SDA_PIN_REG204_BIT ((u32)0x2 << 6)
#define I2C3_SCL_PIN_REG204_MASK ((u32)0x3 << 0) /* hdt_mb_done_state_pad [1 : 0] */
#define I2C3_SCL_PIN_REG204_BIT ((u32)0x2 << 0)
#define I2C3_SDA_PIN_REG208_MASK ((u32)0x3 << 30) /* hdt_mb_fail_state_pad [31 : 30] */
#define I2C3_SDA_PIN_REG208_BIT ((u32)0x2 << 30)

#define SPI1_PORTA5_PIN_REG208_BIT ((u32)0x1 << 16)

#define SPI1_CSN0_PIN_REG210_MASK ((u32)0x3 << 0) /* uart_2_rxd_pad [1 : 0] */
#define SPI1_CSN0_PIN_REG210_BIT ((u32)0x1 << 0)
#define SPI1_SCK_PIN_REG214_MASK ((u32)0x3 << 28) /* uart_2_txd_pad [29 : 28] */
#define SPI1_SCK_PIN_REG214_BIT ((u32)0x1 << 28)
#define SPI1_SO_PIN_REG214_MASK ((u32)0x3 << 24) /* uart_3_rxd_pad [25 : 24] */
#define SPI1_SO_PIN_REG214_BIT ((u32)0x1 << 24)
#define SPI1_SI_PIN_REG214_MASK ((u32)0x3 << 20) /* uart_3_txd_pad [21 : 20] */
#define SPI1_SI_PIN_REG214_BIT ((u32)0x1 << 20)

/* i2c ctrl instance */
#define I2C0_ID 0
#define I2C1_ID 1
#define I2C2_ID 2
#define I2C3_ID 3

/* spi ctrl instance */
#define SPI0_ID 0
#define SPI1_ID 1

    void Ft_setI2cMux(FT_IN u32 I2cId);
    void Ft_setSpiMux(FT_IN u32 SpiId);

#ifdef __cplusplus
}
#endif

#endif
