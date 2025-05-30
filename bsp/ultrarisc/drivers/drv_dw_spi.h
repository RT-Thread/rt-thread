/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * spi driver for synopsys dw apb spi
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-03     ZhangJing   first version
 */
#ifndef __DRV_DW_SPI_H__
#define __DRV_DW_SPI_H__

/* dw spi register */
struct dw_spi_regs
{
    uint32_t ctrl0; /* 0x00:Control Register 0 (ctrl0) */
    uint32_t ctrl1; /* 0x04:Control Register 1 (ctrl1) */
    uint32_t ssienr;    /* 0x08:Synchronous Serial Interface Enable Register (ssienr) */
    uint32_t mwcr;  /* 0x0c:Master Mode Control Register (mwcr) */
    uint32_t ser;   /* 0x10:Slave Enable Register (ser) */
    uint32_t baudr; /* 0x14:Baud Rate Select Register (baudr) */
    uint32_t txftlr;    /* 0x18:Transmit FIFO Threshold Level Register (txftlr) */
    uint32_t rxftlr;    /* 0x1c:Receive FIFO Threshold Level Register (rxftlr) */
    uint32_t txflr; /* 0x20:Transmit FIFO Level Register (txflr) */
    uint32_t rxflr; /* 0x24:Receive FIFO Level Register (rxflr) */
    uint32_t sr;    /* 0x28:Status Register (sr) */
    uint32_t imr;   /* 0x2c:Interrupt Mask Register (imr) */
    uint32_t isr;   /* 0x30:Interrupt Status Register (isr) */
    uint32_t risr;  /* 0x34:Raw Interrupt Status Register (risr) */
    uint32_t txoicr;    /* 0x38:Transmit FIFO Overflow Interrupt Clear Register (txoicr) */
    uint32_t rxoicr;    /* 0x3c:Receive FIFO Overflow Interrupt Clear Register (rxoicr) */
    uint32_t rxuicr;    /* 0x40:Receive FIFO Underflow Interrupt Clear Register (rxuicr) */
    uint32_t msticr;    /* 0x44:Multi-Master Contention Interrupt Clear Register (msticr) */
    uint32_t icr;   /* 0x48:Interrupt Clear Register (icr) */
    uint32_t dmacr; /* 0x4c:DMA Control Register (dmacr) */
    uint32_t dmatdlr;   /* 0x50:DMA Transmit Data Level Register (dmatdlr) */
    uint32_t dmardlr;   /* 0x54:DMA Receive Data Level Register (dmardlr) */
    uint32_t idr;   /* 0x58:Identification Register (idr) */
    uint32_t version;   /* 0x5c:Version Register (version) */
    uint32_t dr[36];    /* 0x60:Data Register (dr) */
    uint32_t rx_sample_delay; /* 0xf0: RX Sample Delay Register */
    uint32_t spi_ctrl0; /* 0xf4*/
    uint32_t txd_drive_edge; /* 0xf8*/
    uint32_t rsvd; /* 0xfc*/
};

/* dw spi device */
struct dw_spi
{
    struct dw_spi_regs *reg;
    struct rt_spi_bus spi_bus;
    char    *device_name;
    uint32_t    version;
    int         irq;
    uint32_t    fifo_len;
    uint32_t    max_freq;
    int bits_per_word;
    void            *tx;
    void            *tx_end;
    void            *rx;
    void            *rx_end;
    unsigned int        tx_len;
    unsigned int        rx_len;
    uint32_t (*update_cr0)(struct dw_spi *dw_spi_dev);
    uint8_t mode;
    uint8_t cs;             /* chip select pin */
    uint8_t tmode;          /* TR/TO/RO/EEPROM */
    uint8_t type;           /* SPI/SSP/MicroWire */
};

/* CTRLR0 bit definiation */
#define DW_SPI_CTRLR0_DFS_MASK                 ((uint32_t)0x000F)
#define CTRLR0_DFS_SHIFT                        0
#define DW_SPI_CTRLR0_DFS_0                    ((uint32_t)(1<<0))
#define DW_SPI_CTRLR0_DFS_1                    ((uint32_t)(1<<1))
#define DW_SPI_CTRLR0_DFS_2                    ((uint32_t)(1<<2))
#define DW_SPI_CTRLR0_DFS_3                    ((uint32_t)(1<<3))

#define DW_SPI_CTRLR0_FRF_SHIFT                (4)
#define DW_SPI_CTRLR0_FRF_MOT                  (0)
#define DW_SPI_CTRLR0_FRF_TI                   (1)
#define DW_SPI_CTRLR0_FRF_MICROWIRE            (2)
#define DW_SPI_CTRLR0_FRF_RESV                 (3)

#define DW_SPI_CTRLR0_MODE_SHIFT               (6)
#define DW_SPI_CTRLR0_SCPH                     ((uint32_t)(1<<6))
#define DW_SPI_CTRLR0_SCPOL                    ((uint32_t)(1<<7))

#define DW_SPI_CTRLR0_TMOD_SHIFT               (8)
#define DW_SPI_CTRLR0_TMOD_TX_RX               (0) /* transmit and receive */
#define DW_SPI_CTRLR0_TMOD_TX                  (1) /* transmit only */
#define DW_SPI_CTRLR0_TMOD_RX                  (2) /* receive only */
#define DW_SPI_CTRLR0_TMOD_EEPROM_READ         (3) /* eeprom read mode */

#define CTRLR0_DFS_32_SHIFT                     (16)

#define DW_SPI_CTRLR0_SLV_OE                   ((uint32_t)(1<<10)) /* salve output enable */
#define DW_SPI_CTRLR0_SRL                      ((uint32_t)(1<<11)) /* shift register loop */
#define DW_SPI_CTRLR0_CFS                      ((uint32_t)(0xF << 12)) /* control frame size */

#define DW_SPI_SR_BUSY                         ((uint32_t)(1<<0))
#define DW_SPI_SR_TX_EMPTY                     ((uint32_t)(1<<2))
#endif /* __DRV_DW_SPI_H__ */