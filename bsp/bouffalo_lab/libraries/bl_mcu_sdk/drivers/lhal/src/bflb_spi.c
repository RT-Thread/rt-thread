#include "bflb_spi.h"
#include "bflb_clock.h"
#include "hardware/spi_reg.h"

#if defined(BL602) || defined(BL702) || defined(BL702L)
#define GLB_SPI_MODE_ADDRESS 0x40000080
#elif defined(BL606P) || defined(BL808) || defined(BL616) || defined(BL628)
#define GLB_SPI_MODE_ADDRESS 0x20000510
#endif

void bflb_spi_init(struct bflb_device_s *dev, const struct bflb_spi_config_s *config)
{
    uint32_t reg_base;
    uint32_t regval;
    uint32_t div;

    /* GLB select master or slave mode */
    regval = getreg32(GLB_SPI_MODE_ADDRESS);
    if (config->role == SPI_ROLE_MASTER) {
        regval |= 1 << 12;
    } else {
        regval &= ~(1 << 12);
    }
    putreg32(regval, GLB_SPI_MODE_ADDRESS);

    reg_base = dev->reg_base;
    /* integer frequency segmentation by rounding */
    div = (bflb_clk_get_peripheral_clock(BFLB_DEVICE_TYPE_SPI, dev->idx) / 2 * 10 / config->freq + 5) / 10;
    div = (div) ? (div - 1) : 0;
    div = (div > 0xff) ? 0xff : div;

    regval = 0;
    regval |= div << SPI_CR_SPI_PRD_D_PH_0_SHIFT;
    regval |= div << SPI_CR_SPI_PRD_D_PH_1_SHIFT;
    regval |= div << SPI_CR_SPI_PRD_S_SHIFT;
    regval |= div << SPI_CR_SPI_PRD_P_SHIFT;
    putreg32(regval, reg_base + SPI_PRD_0_OFFSET);

    regval = getreg32(reg_base + SPI_PRD_1_OFFSET);
    regval &= ~SPI_CR_SPI_PRD_I_MASK;
    regval |= (div) << SPI_CR_SPI_PRD_I_SHIFT;
    putreg32(regval, reg_base + SPI_PRD_1_OFFSET);

    /* Disable deglitch and disenable continue function */
    regval = getreg32(reg_base + SPI_CONFIG_OFFSET);
    regval &= ~SPI_CR_SPI_DEG_EN;
    regval &= ~SPI_CR_SPI_DEG_CNT_MASK;
    regval &= ~SPI_CR_SPI_M_CONT_EN;
    regval &= ~SPI_CR_SPI_RXD_IGNR_EN;

    /* Byte-inverse and Bit-inverse */
    if (config->byte_order == SPI_BYTE_LSB) {
        regval &= ~SPI_CR_SPI_BYTE_INV;
    } else {
        regval |= SPI_CR_SPI_BYTE_INV;
    }
    if (config->bit_order == SPI_BIT_LSB) {
        regval |= SPI_CR_SPI_BIT_INV;
    } else {
        regval &= ~SPI_CR_SPI_BIT_INV;
    }

    /* clk phase and polarity cfg */
    switch (config->mode) {
        case SPI_MODE0:
            /* CPOL=0 CHPHA=0 */
            regval &= ~SPI_CR_SPI_SCLK_POL;
            regval |= SPI_CR_SPI_SCLK_PH;
            break;
        case SPI_MODE1:
            /* CPOL=0 CHPHA=1 */
            regval &= ~SPI_CR_SPI_SCLK_POL;
            regval &= ~SPI_CR_SPI_SCLK_PH;
            break;
        case SPI_MODE2:
            /* CPOL=1 CHPHA=0 */
            regval |= SPI_CR_SPI_SCLK_POL;
            regval |= SPI_CR_SPI_SCLK_PH;
            break;
        case SPI_MODE3:
            /* CPOL=1 CHPHA=1 */
            regval |= SPI_CR_SPI_SCLK_POL;
            regval &= ~SPI_CR_SPI_SCLK_PH;
            break;
        default:
            break;
    }

    /* data frame size cfg */
    regval &= ~SPI_CR_SPI_FRAME_SIZE_MASK;
    regval |= (config->data_width - 1) << SPI_CR_SPI_FRAME_SIZE_SHIFT;

    /* disable SPI */
    regval &= ~SPI_CR_SPI_S_EN;
    regval &= ~SPI_CR_SPI_M_EN;

    putreg32(regval, reg_base + SPI_CONFIG_OFFSET);

    /* clear fifo and close dma */
    regval = getreg32(reg_base + SPI_FIFO_CONFIG_0_OFFSET);
    regval |= SPI_TX_FIFO_CLR;
    regval |= SPI_RX_FIFO_CLR;
    regval &= ~SPI_DMA_TX_EN;
    regval &= ~SPI_DMA_RX_EN;
    putreg32(regval, reg_base + SPI_FIFO_CONFIG_0_OFFSET);

    /* fifo threshold cfg */
    regval = getreg32(reg_base + SPI_FIFO_CONFIG_1_OFFSET);
    regval &= ~SPI_TX_FIFO_TH_MASK;
    regval &= ~SPI_RX_FIFO_TH_MASK;
    regval |= (config->tx_fifo_threshold << SPI_TX_FIFO_TH_SHIFT) & SPI_TX_FIFO_TH_MASK;
    regval |= (config->rx_fifo_threshold << SPI_RX_FIFO_TH_SHIFT) & SPI_RX_FIFO_TH_MASK;
    putreg32(regval, reg_base + SPI_FIFO_CONFIG_1_OFFSET);

    /* enable spi */
    regval = getreg32(reg_base + SPI_CONFIG_OFFSET);
    if (config->role == SPI_ROLE_MASTER) {
        regval |= SPI_CR_SPI_M_EN;
        regval &= ~SPI_CR_SPI_S_EN;
    } else {
        regval |= SPI_CR_SPI_S_EN;
        regval &= ~SPI_CR_SPI_M_EN;
    }
    putreg32(regval, reg_base + SPI_CONFIG_OFFSET);
}

void bflb_spi_deinit(struct bflb_device_s *dev)
{
    uint32_t regval;
    /* disable SPI */
    regval = getreg32(dev->reg_base + SPI_CONFIG_OFFSET);
    regval &= ~SPI_CR_SPI_S_EN;
    regval &= ~SPI_CR_SPI_M_EN;
    putreg32(regval, dev->reg_base + SPI_CONFIG_OFFSET);
}

void bflb_spi_link_txdma(struct bflb_device_s *dev, bool enable)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + SPI_FIFO_CONFIG_0_OFFSET);
    if (enable) {
        regval |= SPI_DMA_TX_EN;
    } else {
        regval &= ~SPI_DMA_TX_EN;
    }
    putreg32(regval, reg_base + SPI_FIFO_CONFIG_0_OFFSET);
}

void bflb_spi_link_rxdma(struct bflb_device_s *dev, bool enable)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + SPI_FIFO_CONFIG_0_OFFSET);
    if (enable) {
        regval |= SPI_DMA_RX_EN;
    } else {
        regval &= ~SPI_DMA_RX_EN;
    }
    putreg32(regval, reg_base + SPI_FIFO_CONFIG_0_OFFSET);
}

/* Read and write a frame of data */
ATTR_TCM_SECTION uint32_t bflb_spi_poll_send(struct bflb_device_s *dev, uint32_t data)
{
    uint32_t reg_base = dev->reg_base;
    uint32_t regval;
    uint8_t fifo_cnt;

#if 0
    /* Wait for tx FIFO to be empty */
#if (SPI_FIFO_WIDTH_VARIABLE_SUPPORT)
    do {
        regval = getreg32(reg_base + SPI_FIFO_CONFIG_1_OFFSET);
        fifo_cnt = (regval & SPI_TX_FIFO_CNT_MASK) >> SPI_TX_FIFO_CNT_SHIFT;
    } while (fifo_cnt < SPI_FIFO_BYTE_NUM_MAX);
#else
    do {
        regval = getreg32(reg_base + SPI_FIFO_CONFIG_1_OFFSET);
        fifo_cnt = (regval & SPI_TX_FIFO_CNT_MASK) >> SPI_TX_FIFO_CNT_SHIFT;
    } while (fifo_cnt < SPI_FIFO_WORD_NUM_MAX);
#endif

    /* Wait for SPI to idle */
    do {
        regval = getreg32(reg_base + SPI_BUS_BUSY_OFFSET);
    } while (regval);

    /* clear fifo */
    regval = getreg32(reg_base + SPI_FIFO_CONFIG_0_OFFSET);
    regval |= SPI_TX_FIFO_CLR;
    regval |= SPI_RX_FIFO_CLR;
    putreg32(regval, reg_base + SPI_FIFO_CONFIG_0_OFFSET);

#endif

    /* wtire data to fifo */
    putreg32(data, reg_base + SPI_FIFO_WDATA_OFFSET);

#if (SPI_FIFO_WIDTH_VARIABLE_SUPPORT)

    /* get frame size */
    regval = getreg32(reg_base + SPI_CONFIG_OFFSET);
    uint8_t frame_size = ((regval & SPI_CR_SPI_FRAME_SIZE_MASK) >> SPI_CR_SPI_FRAME_SIZE_SHIFT) + 1;
    if (frame_size == 3) {
        frame_size = 4;
    }

    /* Wait for rx data */
    do {
        regval = getreg32(reg_base + SPI_FIFO_CONFIG_1_OFFSET);
        fifo_cnt = (regval & SPI_RX_FIFO_CNT_MASK) >> SPI_RX_FIFO_CNT_SHIFT;
    } while (fifo_cnt < frame_size);
#else

    /* Wait for rx data */
    do {
        regval = getreg32(reg_base + SPI_FIFO_CONFIG_1_OFFSET);
        fifo_cnt = (regval & SPI_RX_FIFO_CNT_MASK) >> SPI_RX_FIFO_CNT_SHIFT;
    } while (fifo_cnt == 0);
#endif

    regval = getreg32(reg_base + SPI_FIFO_RDATA_OFFSET);

    return regval;
}

/* read and write data */
ATTR_TCM_SECTION int bflb_spi_poll_exchange(struct bflb_device_s *dev, const void *txbuffer, void *rxbuffer, size_t nbytes)
{
    uint32_t regval;
    uint32_t reg_base = dev->reg_base;
    uint32_t tx_cnt;
    uint8_t fifo_cnt, frame_size;

    /* get frame size */
    regval = getreg32(reg_base + SPI_CONFIG_OFFSET);
    frame_size = ((regval & SPI_CR_SPI_FRAME_SIZE_MASK) >> SPI_CR_SPI_FRAME_SIZE_SHIFT) + 1;
    if (frame_size == 3) {
        frame_size = 4;
    }

    nbytes /= frame_size;
    tx_cnt = nbytes;

#if 0
    /* Wait for tx FIFO to be empty */
#if (SPI_FIFO_WIDTH_VARIABLE_SUPPORT)
    do {
        regval = getreg32(reg_base + SPI_FIFO_CONFIG_1_OFFSET);
        fifo_cnt = (regval & SPI_TX_FIFO_CNT_MASK) >> SPI_TX_FIFO_CNT_SHIFT;
    } while (fifo_cnt < SPI_FIFO_BYTE_NUM_MAX);
#else
    do {
        regval = getreg32(reg_base + SPI_FIFO_CONFIG_1_OFFSET);
        fifo_cnt = (regval & SPI_TX_FIFO_CNT_MASK) >> SPI_TX_FIFO_CNT_SHIFT;
    } while (fifo_cnt < SPI_FIFO_WORD_NUM_MAX);
#endif

    /* Wait for SPI to idle */
    do {
        regval = getreg32(reg_base + SPI_BUS_BUSY_OFFSET);
    } while (regval);

    /* clear fifo */
    regval = getreg32(reg_base + SPI_FIFO_CONFIG_0_OFFSET);
    regval |= SPI_TX_FIFO_CLR;
    regval |= SPI_RX_FIFO_CLR;
    putreg32(regval, reg_base + SPI_FIFO_CONFIG_0_OFFSET);

#endif

    /* clear fifo */
    regval = getreg32(reg_base + SPI_FIFO_CONFIG_0_OFFSET);
    regval |= SPI_TX_FIFO_CLR;
    regval |= SPI_RX_FIFO_CLR;
    putreg32(regval, reg_base + SPI_FIFO_CONFIG_0_OFFSET);

    /* get tx fifo cnt */
    regval = getreg32(reg_base + SPI_FIFO_CONFIG_1_OFFSET);
#if (SPI_FIFO_WIDTH_VARIABLE_SUPPORT)
    fifo_cnt = ((regval & SPI_TX_FIFO_CNT_MASK) >> SPI_TX_FIFO_CNT_SHIFT) / frame_size;
#else
    fifo_cnt = ((regval & SPI_TX_FIFO_CNT_MASK) >> SPI_TX_FIFO_CNT_SHIFT);
#endif

    /* first fill tx fifo */
    fifo_cnt = fifo_cnt > nbytes ? nbytes : fifo_cnt;
    tx_cnt -= fifo_cnt;
    if (txbuffer != NULL) {
        /* Send valid data */
        for (; fifo_cnt > 0; fifo_cnt--) {
            switch (frame_size) {
                case 1:
                    regval = *(uint8_t *)txbuffer;
                    putreg32(regval, reg_base + SPI_FIFO_WDATA_OFFSET);
                    txbuffer += 1;
                    break;
                case 2:
                    regval = *(uint16_t *)txbuffer;
                    putreg32(regval, reg_base + SPI_FIFO_WDATA_OFFSET);
                    txbuffer += 2;
                    break;
                case 3:
                case 4:
                    regval = *(uint32_t *)txbuffer;
                    putreg32(regval, reg_base + SPI_FIFO_WDATA_OFFSET);
                    txbuffer += 4;
                    break;
                default:
                    break;
            }
        }
    } else {
        /* Send idle Data */
        for (; fifo_cnt > 0; fifo_cnt--) {
            putreg32(0xFFFFFFFF, reg_base + SPI_FIFO_WDATA_OFFSET);
        }
    }

    /* read and write rest of the data */
    for (; nbytes > 0;) {
        /* get rx fifo cnt */
        regval = getreg32(reg_base + SPI_FIFO_CONFIG_1_OFFSET);

#if (SPI_FIFO_WIDTH_VARIABLE_SUPPORT)
        fifo_cnt = ((regval & SPI_RX_FIFO_CNT_MASK) >> SPI_RX_FIFO_CNT_SHIFT) / frame_size;
#else
        fifo_cnt = ((regval & SPI_RX_FIFO_CNT_MASK) >> SPI_RX_FIFO_CNT_SHIFT);
#endif
        if (fifo_cnt) {
            fifo_cnt = fifo_cnt > nbytes ? nbytes : fifo_cnt;
            nbytes -= fifo_cnt;
        } else {
        }

        /* read and write data */
        for (; fifo_cnt > 0; fifo_cnt--) {
            regval = getreg32(reg_base + SPI_FIFO_RDATA_OFFSET);
            switch (frame_size) {
                case 1:
                    if (rxbuffer) {
                        *((uint8_t *)rxbuffer) = (uint8_t)regval;
                        rxbuffer += 1;
                    }
                    if (tx_cnt) {
                        if (txbuffer) {
                            regval = *(uint8_t *)txbuffer;
                            putreg32(regval, reg_base + SPI_FIFO_WDATA_OFFSET);
                            txbuffer++;
                        } else {
                            putreg32(0xFFFFFFFF, reg_base + SPI_FIFO_WDATA_OFFSET);
                        }
                        tx_cnt--;
                    }
                    break;
                case 2:
                    if (rxbuffer) {
                        *((uint16_t *)rxbuffer) = (uint16_t)regval;
                        rxbuffer += 2;
                    }
                    if (tx_cnt) {
                        if (txbuffer) {
                            regval = *(uint16_t *)txbuffer;
                            putreg32(regval, reg_base + SPI_FIFO_WDATA_OFFSET);
                            txbuffer += 2;
                        } else {
                            putreg32(0xFFFFFFFF, reg_base + SPI_FIFO_WDATA_OFFSET);
                        }
                        tx_cnt--;
                    }
                    break;
                case 3:
                    /* discard the high 8 bits of data when 24bit-frame */
                case 4:
                    if (rxbuffer) {
                        *((uint32_t *)rxbuffer) = (uint32_t)regval;
                        rxbuffer += 4;
                    }
                    if (tx_cnt) {
                        if (txbuffer) {
                            regval = *(uint32_t *)txbuffer;
                            putreg32(regval, reg_base + SPI_FIFO_WDATA_OFFSET);
                            txbuffer += 4;
                        } else {
                            putreg32(0xFFFFFFFF, reg_base + SPI_FIFO_WDATA_OFFSET);
                        }
                        tx_cnt--;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}

void bflb_spi_txint_mask(struct bflb_device_s *dev, bool mask)
{
    uint32_t regval;
    uint32_t reg_base = dev->reg_base;

    regval = getreg32(reg_base + SPI_INT_STS_OFFSET);
    if (mask) {
        regval |= SPI_CR_SPI_TXF_MASK;
    } else {
        regval &= ~SPI_CR_SPI_TXF_MASK;
    }
    putreg32(regval, reg_base + SPI_INT_STS_OFFSET);
}

void bflb_spi_rxint_mask(struct bflb_device_s *dev, bool mask)
{
    uint32_t regval;
    uint32_t reg_base = dev->reg_base;

    regval = getreg32(reg_base + SPI_INT_STS_OFFSET);
    if (mask) {
        regval |= SPI_CR_SPI_RXF_MASK;
    } else {
        regval &= ~SPI_CR_SPI_RXF_MASK;
    }
    putreg32(regval, reg_base + SPI_INT_STS_OFFSET);
}

void bflb_spi_tcint_mask(struct bflb_device_s *dev, bool mask)
{
    uint32_t regval;
    uint32_t reg_base = dev->reg_base;

    regval = getreg32(reg_base + SPI_INT_STS_OFFSET);
    if (mask) {
        regval |= SPI_CR_SPI_END_MASK;
    } else {
        regval &= ~SPI_CR_SPI_END_MASK;
    }
    putreg32(regval, reg_base + SPI_INT_STS_OFFSET);
}

void bflb_spi_errint_mask(struct bflb_device_s *dev, bool mask)
{
    uint32_t regval;
    uint32_t reg_base = dev->reg_base;

    regval = getreg32(reg_base + SPI_INT_STS_OFFSET);
    if (mask) {
        regval |= SPI_CR_SPI_STO_MASK;
        regval |= SPI_CR_SPI_TXU_MASK;
        regval |= SPI_CR_SPI_FER_MASK;
    } else {
        regval &= ~SPI_CR_SPI_STO_MASK;
        regval &= ~SPI_CR_SPI_TXU_MASK;
        regval &= ~SPI_CR_SPI_FER_MASK;
    }
    putreg32(regval, reg_base + SPI_INT_STS_OFFSET);
}

uint32_t bflb_spi_get_intstatus(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t int_status;
    uint32_t int_mask;

    reg_base = dev->reg_base;
    int_status = getreg32(reg_base + SPI_INT_STS_OFFSET) & 0x1f;
    int_mask = getreg32(reg_base + SPI_INT_STS_OFFSET) >> 8 & 0x1f;
    return (int_status & ~int_mask);
}

void bflb_spi_int_clear(struct bflb_device_s *dev, uint32_t int_clear)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + SPI_INT_STS_OFFSET);
    regval |= int_clear;
    putreg32(regval, reg_base + SPI_INT_STS_OFFSET);
}

bool bflb_spi_isbusy(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    /* check tx fifo */
    regval = getreg32(reg_base + SPI_FIFO_CONFIG_1_OFFSET);
#if (SPI_FIFO_WIDTH_VARIABLE_SUPPORT)
    if ((regval & SPI_TX_FIFO_CNT_MASK) >> SPI_TX_FIFO_CNT_SHIFT < SPI_FIFO_BYTE_NUM_MAX) {
        return true;
    }
#else
    if ((regval & SPI_TX_FIFO_CNT_MASK) >> SPI_TX_FIFO_CNT_SHIFT < SPI_FIFO_WORD_NUM_MAX) {
        return true;
    }
#endif

    /* check busy bit */
    regval = getreg32(reg_base + SPI_BUS_BUSY_OFFSET);
    if (regval) {
        return true;
    }

    return false;
}

int bflb_spi_feature_control(struct bflb_device_s *dev, int cmd, size_t arg)
{
    int ret = 0;
    uint32_t reg_base;
    uint32_t regval;
    uint32_t div;

    reg_base = dev->reg_base;

    switch (cmd) {
        case SPI_CMD_SET_DATA_WIDTH:
            /* set data width, arg use @ref SPI_DATA_WIDTH, must clear fifo */
            regval = getreg32(reg_base + SPI_FIFO_CONFIG_0_OFFSET);
            regval |= SPI_TX_FIFO_CLR;
            regval |= SPI_RX_FIFO_CLR;
            putreg32(regval, reg_base + SPI_FIFO_CONFIG_0_OFFSET);

            regval = getreg32(reg_base + SPI_CONFIG_OFFSET);
            regval &= ~SPI_CR_SPI_FRAME_SIZE_MASK;
            regval |= (arg - 1) << SPI_CR_SPI_FRAME_SIZE_SHIFT;
            putreg32(regval, reg_base + SPI_CONFIG_OFFSET);
            break;

        case SPI_CMD_GET_DATA_WIDTH:
            /* set data width, arg use @ref SPI_DATA_WIDTH */
            regval = getreg32(reg_base + SPI_CONFIG_OFFSET);
            regval &= SPI_CR_SPI_FRAME_SIZE_MASK;
            regval >>= SPI_CR_SPI_FRAME_SIZE_SHIFT;
            *(uint32_t *)arg = regval;
            break;

        case SPI_CMD_CLEAR_TX_FIFO:
            /* clear tx fifo */
            regval = getreg32(reg_base + SPI_FIFO_CONFIG_0_OFFSET);
            regval |= SPI_TX_FIFO_CLR;
            putreg32(regval, reg_base + SPI_FIFO_CONFIG_0_OFFSET);
            break;

        case SPI_CMD_CLEAR_RX_FIFO:
            /* clear rx fifo */
            regval = getreg32(reg_base + SPI_FIFO_CONFIG_0_OFFSET);
            regval |= SPI_RX_FIFO_CLR;
            putreg32(regval, reg_base + SPI_FIFO_CONFIG_0_OFFSET);
            break;

        case SPI_CMD_SET_CS_INTERVAL:
            /* set CS continue mode, arg use true or false */
            regval = getreg32(reg_base + SPI_CONFIG_OFFSET);
            if (arg) {
                regval |= SPI_CR_SPI_M_CONT_EN;
            } else {
                regval &= ~SPI_CR_SPI_M_CONT_EN;
            }
            putreg32(regval, reg_base + SPI_CONFIG_OFFSET);
            break;

        case SPI_CMD_RX_IGNORE:
            /* set rx ignore, start: arg[20:16], stop: arg[4:0] */
            regval = getreg32(reg_base + SPI_CONFIG_OFFSET);
            if (arg) {
                regval |= SPI_CR_SPI_RXD_IGNR_EN;
                putreg32(arg, reg_base + SPI_RXD_IGNR_OFFSET);
            } else {
                regval &= ~SPI_CR_SPI_RXD_IGNR_EN;
            }
            putreg32(regval, reg_base + SPI_CONFIG_OFFSET);
            break;

        case SPI_CMD_SET_MODE:
            /* set spi mode (clk phase and polarity),  arg use @ref SPI_MODE*/
            regval = getreg32(reg_base + SPI_CONFIG_OFFSET);
            switch (arg) {
                case SPI_MODE0:
                    /* CPOL=0 CHPHA=0 */
                    regval &= ~SPI_CR_SPI_SCLK_POL;
                    regval |= SPI_CR_SPI_SCLK_PH;
                    break;
                case SPI_MODE1:
                    /* CPOL=0 CHPHA=1 */
                    regval &= ~SPI_CR_SPI_SCLK_POL;
                    regval &= ~SPI_CR_SPI_SCLK_PH;
                    break;
                case SPI_MODE2:
                    /* CPOL=1 CHPHA=0 */
                    regval |= SPI_CR_SPI_SCLK_POL;
                    regval |= SPI_CR_SPI_SCLK_PH;
                    break;
                case SPI_MODE3:
                    /* CPOL=1 CHPHA=1 */
                    regval |= SPI_CR_SPI_SCLK_POL;
                    regval &= ~SPI_CR_SPI_SCLK_PH;
                    break;
                default:
                    break;
            }
            putreg32(regval, reg_base + SPI_CONFIG_OFFSET);
            break;

        case SPI_CMD_GET_MODE:
            /* get spi mode (clk phase and polarity),  ret @ref SPI_MODE*/
            regval = getreg32(reg_base + SPI_CONFIG_OFFSET);
            if (regval & SPI_CR_SPI_SCLK_POL) {
                if (regval & SPI_CR_SPI_SCLK_PH) {
                    ret = SPI_MODE2;
                } else {
                    ret = SPI_MODE3;
                }
            } else {
                if (regval & SPI_CR_SPI_SCLK_PH) {
                    ret = SPI_MODE0;
                } else {
                    ret = SPI_MODE1;
                }
            }
            break;

        case SPI_CMD_SET_FREQ:
            /* set clk frequence, should be less than spi_clk/2*/
            /* integer frequency segmentation by rounding */
            div = (bflb_clk_get_peripheral_clock(BFLB_DEVICE_TYPE_SPI, dev->idx) / 2 * 10 / arg + 5) / 10;
            div = (div) ? (div - 1) : 0;
            div = (div > 0xff) ? 0xff : div;

            regval = 0;
            regval |= div << SPI_CR_SPI_PRD_D_PH_0_SHIFT;
            regval |= div << SPI_CR_SPI_PRD_D_PH_1_SHIFT;
            regval |= div << SPI_CR_SPI_PRD_S_SHIFT;
            regval |= div << SPI_CR_SPI_PRD_P_SHIFT;
            putreg32(regval, reg_base + SPI_PRD_0_OFFSET);
            break;

        case SPI_CMD_GET_FREQ:
            /* get clk frequence */
            regval = getreg32(reg_base + SPI_PRD_0_OFFSET);
            div = (regval & SPI_CR_SPI_PRD_D_PH_0_MASK) >> SPI_CR_SPI_PRD_D_PH_0_SHIFT;
            div += (regval & SPI_CR_SPI_PRD_D_PH_1_MASK) >> SPI_CR_SPI_PRD_D_PH_1_SHIFT;

            ret = bflb_clk_get_peripheral_clock(BFLB_DEVICE_TYPE_SPI, dev->idx) / div;
            break;

        case SPI_CMD_SET_BIT_ORDER:
            /* set bit order, arg use @ref SPI_BIT_ORDER */
            regval = getreg32(reg_base + SPI_CONFIG_OFFSET);
            if (arg == SPI_BIT_LSB) {
                regval |= SPI_CR_SPI_BIT_INV;
            } else {
                regval &= ~SPI_CR_SPI_BIT_INV;
            }
            putreg32(regval, reg_base + SPI_CONFIG_OFFSET);
            break;

        case SPI_CMD_GET_BIT_ORDER:
            regval = getreg32(reg_base + SPI_CONFIG_OFFSET);
            if (regval & SPI_CR_SPI_BIT_INV) {
                ret = SPI_BIT_LSB;
            } else {
                ret = !SPI_BIT_LSB;
            }
            break;

        case SPI_CMD_SET_BYTE_ORDER:
            /* set byte order, arg use @ref SPI_BYTE_ORDER */
            regval = getreg32(reg_base + SPI_CONFIG_OFFSET);
            if (arg == SPI_BYTE_LSB) {
                regval &= ~SPI_CR_SPI_BYTE_INV;
            } else {
                regval |= SPI_CR_SPI_BYTE_INV;
            }
            putreg32(regval, reg_base + SPI_CONFIG_OFFSET);
            break;

        case SPI_CMD_GET_BYTE_ORDER:
            regval = getreg32(reg_base + SPI_CONFIG_OFFSET);
            if (regval & SPI_CR_SPI_BYTE_INV) {
                ret = !SPI_BYTE_LSB;
            } else {
                ret = SPI_BYTE_LSB;
            }
            break;

        default:
            ret = -EPERM;
            break;
    }

    return ret;
}