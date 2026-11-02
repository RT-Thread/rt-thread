/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-30     Emuzit            first version
 */
#ifndef __CH56X_SPI_H__
#define __CH56X_SPI_H__

#include "soc.h"
#include "ch56x_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SPI0_BUS_NAME       "spi0"
#define SPI1_BUS_NAME       "spi1"

#ifndef SPI0_SCS_PIN
#define SPI0_SCS_PIN        GET_PIN(A, 12)
#endif
#define SPI0_SCK_PIN        GET_PIN(A, 13)
#define SPI0_MOSI_PIN       GET_PIN(A, 14)
#define SPI0_MISO_PIN       GET_PIN(A, 15)

#ifdef SOC_SERIES_CH569
#ifndef SPI1_SCS_PIN
#define SPI1_SCS_PIN        GET_PIN(B, 11)
#endif
#define SPI1_SCK_PIN        GET_PIN(B, 12)
#define SPI1_MOSI_PIN       GET_PIN(B, 13)
#define SPI1_MISO_PIN       GET_PIN(B, 14)

#else
#define SPI1_SCK_PIN        GET_PIN(A, 0)
#define SPI1_MOSI_PIN       GET_PIN(A, 1)
#define SPI1_MISO_PIN       GET_PIN(A, 2)
#endif

#define SPI_FIFO_SIZE       8

union _spi_ctrl_mod
{
    uint8_t reg;
    struct
    {
        uint8_t mode_slave  : 1;  // RW, SPI master/slave (0/1) mode select
        uint8_t all_clear   : 1;  // RW, clear FIFO/count/int-flag
        uint8_t two_wire    : 1;  // RW, 2/3-wire mode (0/1), SPI slave
        uint8_t mst_sck_mod : 1;  // RW, mode0/mode3 (0/1) for SCK idle L/H
        uint8_t fifo_dir    : 1;  // RW, FIFO direction is output/input (0/1)
        uint8_t sck_oe      : 1;  // RW, SCK pin output enable
        uint8_t mosi_oe     : 1;  // RW, MOSI pin output enable
        uint8_t miso_oe     : 1;  // RW, MISO pin output enable
    };
    struct
    {
        uint8_t stuff_0     : 3;
        uint8_t slv_cmd_mod : 1;  // RW, 1st byte is data/cmd (0/1), SPI slave
        uint8_t stuff_4     : 4;
    };
};
#define RB_SPI_MODE_SLAVE   0x01
#define RB_SPI_ALL_CLEAR    0x02
#define RB_SPI_2WIRE_MOD    0x04
#define RB_SPI_MST_SCK_MOD  0x08
#define RB_SPI_SLV_CMD_MOD  0x08
#define RB_SPI_FIFO_DIR     0x10
#define RB_SPI_SCK_OE       0x20
#define RB_SPI_MOSI_OE      0x40
#define RB_SPI_MISO_OE      0x80

#define MST_SCK_MOD_0       0
#define MST_SCK_MOD_3       1

#define SPI_FIFO_DIR_OUTPUT 0
#define SPI_FIFO_DIR_INPUT  1

union _spi_ctrl_cfg
{
    uint8_t reg;
    struct
    {
        uint8_t dma_enable  : 1;  // RW, enable DMA function
        uint8_t resv_1      : 1;
        uint8_t dma_loop    : 1;  // RW, enable DMA loop mode (0 => single)
        uint8_t resv_3      : 1;
        uint8_t auto_if     : 1;  // RW, enable auto clear RB_SPI_IF_BYTE_END
        uint8_t bit_order   : 1;  // RW, data bit ordering, LSB/MSB first (0/1)
        uint8_t resv_6      : 2;
    };
};
#define RB_SPI_DMA_ENABLE   0x01
#define RB_SPI_DMA_LOOP     0x04
#define RB_SPI_AUTO_IF      0x10
#define RB_SPI_BIT_ORDER    0x20

#define SPI_BIT_ORDER_MSB   0
#define SPI_BIT_ORDER_LSB   1

union _spi_inter_en
{
    uint8_t reg;
    struct
    {
        uint8_t cnt_end     : 1;  // RW, IE for all bytes transfered
        uint8_t byte_end    : 1;  // RW, IE for single byte transfered
        uint8_t fifo_hf     : 1;  // RW, IE for FIFO half full
        uint8_t dma_end     : 1;  // RW, IE for end of DMA
        uint8_t fifo_ov     : 1;  // RW, IE for FIFO full or empty
        uint8_t resv_5      : 2;
        uint8_t fst_byte    : 1;  // RW, IE for 1st byte received, SPI slave
    };
};
#define RB_SPI_IE_CNT_END   0x01
#define RB_SPI_IE_BYTE_END  0x02
#define RB_SPI_IE_FIFO_HF   0x04
#define RB_SPI_IE_DMA_END   0x08
#define RB_SPI_IE_FIFO_OV   0x10
#define RB_SPI_IE_FST_BYTE  0x80

union _spi_run_flag
{
    uint8_t reg;
    struct
    {
        uint8_t resv_0      : 4;
        uint8_t slv_cmd_act : 1;  // RO, SPI slave cmd received
        uint8_t fifo_ready  : 1;  // RO, SPI FIFO ready to transfer
        uint8_t slv_cs_load : 1;  // RO, SPI slave is loading R8_SPIx_SLAVE_PRE
        uint8_t slv_select  : 1;  // RO, SPI slave CS active (selected)
    };
};
#define RB_SPI_SLV_CMD_ACT  0x10
#define RB_SPI_FIFO_READY   0x20
#define RB_SPI_SLV_CS_LOAD  0x40
#define RB_SPI_SLV_SELECT   0x80

union _spi_int_flag
{
    uint8_t reg;
    struct
    {
        uint8_t cnt_end     : 1;  // RW1, IF for all bytes transfered
        uint8_t byte_end    : 1;  // RW1, IF for single byte transfered
        uint8_t fifo_hf     : 1;  // RW1, IF for FIFO half full
        uint8_t dma_end     : 1;  // RW1, IF for end of DMA
        uint8_t fifo_ov     : 1;  // RW1, IF for FIFO full or empty
        uint8_t resv_5      : 1;
        uint8_t free        : 1;  // RO, current SPI state is free
        uint8_t fst_byte    : 1;  // RW1, IF for 1st byte received, SPI slave
    };
};
#define RB_SPI_IF_CNT_END   0x01
#define RB_SPI_IF_BYTE_END  0x02
#define RB_SPI_IF_FIFO_HF   0x04
#define RB_SPI_IF_DMA_END   0x08
#define RB_SPI_IF_FIFO_OV   0x10
#define RB_SPI_FREE         0x40
#define RB_SPI_IF_FST_BYTE  0x80

/*
 * 0x00  R8_SPIx_CTRL_MOD:    SPI mode setting register
 * 0x01  R8_SPIx_CTRL_CFG:    SPI configuration register
 * 0x02  R8_SPIx_INTER_EN:    SPI interrupt enable register
 * 0x03  R8_SPIx_CLOCK_DIV:   SPI master clock divisor, minimum 2
 * 0x03  R8_SPIx_SLAVE_PRE:   SPI slave preset data (reset as 10h)
 * 0x04  R8_SPIx_BUFFER:      SPI data buffer
 * 0x05  R8_SPIx_RUN_FLAG:    SPI working state register
 * 0x06  R8_SPIx_INT_FLAG:    SPI interrupt flags register
 * 0x07  R8_SPIx_FIFO_COUNT:  SPI FIFO data count
 * 0x0c  R16_SPIx_TOTAL_CNT:  SPI total data length to transfer
 * 0x10  R8_SPIx_FIFO:        SPI FIFO
 * 0x13  R8_SPIx_FIFO_COUNT1: SPI FIFO data count
 * 0x14  R32_SPIx_DMA_NOW:    SPI DMA current address
 * 0x18  R32_SPIx_DMA_BEG:    SPI DMA start address
 * 0x1c  R32_SPIx_DMA_END:    SPI DMA end address
 */
struct spi_registers
{
    union _spi_ctrl_mod     CTRL_MOD;
    union _spi_ctrl_cfg     CTRL_CFG;
    union _spi_inter_en     INTER_EN;
    union
    {
        uint8_t             CLOCK_DIV;
        uint8_t             SLAVE_PRE;
    };
    uint8_t                 BUFFER;
    union _spi_run_flag     RUN_FLAG;
    union _spi_int_flag     INT_FLAG;
    uint8_t                 FIFO_COUNT;
    uint32_t                resv_8;
    uint16_t                TOTAL_COUNT;
    uint16_t                resv_0e;
    uint8_t                 FIFO;
    uint8_t                 resv_11[2];
    uint8_t                 FIFO_COUNT1;
    uint32_t                DMA_NOW;
    uint32_t                DMA_BIG;
    uint32_t                DMA_END;
};
CHECK_STRUCT_SIZE(struct spi_registers, 0x20);

rt_err_t spi_cs_pin_assign(int spi_n, rt_base_t cs_pin);

#ifdef __cplusplus
}
#endif

#endif
