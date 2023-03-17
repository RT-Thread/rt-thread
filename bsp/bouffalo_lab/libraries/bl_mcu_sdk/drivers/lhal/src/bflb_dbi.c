#include "bflb_dbi.h"
#include "bflb_clock.h"
#include "hardware/dbi_reg.h"

#if (DBI_YUV_SUPPORT)
/* YUV to RGB parameter list, do not modify. */

#define YUV_PRE_OFFSET_0  0
#define YUV_PRE_OFFSET_1  0x180
#define YUV_PRE_OFFSET_2  0x180

#define YUV_POST_OFFSET_0 0
#define YUV_POST_OFFSET_1 0
#define YUV_POST_OFFSET_2 0

#define YUV_MATRIX00      0x200
#define YUV_MATRIX01      0
#define YUV_MATRIX02      0x2ce

#define YUV_MATRIX10      0x200
#define YUV_MATRIX11      0xf50
#define YUV_MATRIX12      0xe92

#define YUV_MATRIX20      0x200
#define YUV_MATRIX21      0x38b
#define YUV_MATRIX22      0

#endif

void bflb_dbi_init(struct bflb_device_s *dev, const struct bflb_dbi_config_s *config)
{
    uint32_t reg_base;
    uint32_t regval;
    uint32_t div;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + DBI_CONFIG_OFFSET);

    /* disable DBI transaction */
    regval &= ~DBI_CR_DBI_EN;
    putreg32(regval, reg_base + DBI_CONFIG_OFFSET);

    /* dbi work mode select */
    regval &= ~DBI_CR_DBI_SEL_MASK;
    regval |= config->dbi_mode << DBI_CR_DBI_SEL_SHIFT;

    /* clock phase and polarity cfg */
    switch (config->clk_mode) {
        case DBI_CLOCK_MODE_0:
            /* CPOL=0 CHPHA=0 */
            regval &= ~DBI_CR_DBI_SCL_POL;
            regval |= DBI_CR_DBI_SCL_PH;
            break;
        case DBI_CLOCK_MODE_1:
            /* CPOL=0 CHPHA=1 */
            regval &= ~DBI_CR_DBI_SCL_POL;
            regval &= ~DBI_CR_DBI_SCL_PH;
            break;
        case DBI_CLOCK_MODE_2:
            /* CPOL=1 CHPHA=0 */
            regval |= DBI_CR_DBI_SCL_POL;
            regval |= DBI_CR_DBI_SCL_PH;
            break;
        case DBI_CLOCK_MODE_3:
            /* CPOL=1 CHPHA=1 */
            regval |= DBI_CR_DBI_SCL_POL;
            regval &= ~DBI_CR_DBI_SCL_PH;
            break;
        default:
            break;
    }

    /* disable pixel data continuous transfer mode (CS) */
    regval &= ~DBI_CR_DBI_CONT_EN;

    /* disable dummy between command phase and data phase */
    regval &= ~DBI_CR_DBI_DMY_EN;

    /* CS will stay asserted before FIFO is empty */
#if (DBI_QSPI_SUPPORT)
    if (config->dbi_mode == DBI_MODE_EX_QSPI) {
        /* The CS of the qspi must be asserted in a single transaction */
        regval |= DBI_CR_DBI_CS_STRETCH;
    } else
#endif
    {
        /* Other modes don't care */
        regval &= ~DBI_CR_DBI_CS_STRETCH;
    }

    /* enable command phase */
    regval |= DBI_CR_DBI_CMD_EN;
    putreg32(regval, reg_base + DBI_CONFIG_OFFSET);

    /* clock cfg */
    /* integer frequency segmentation by rounding */
    div = (bflb_clk_get_peripheral_clock(BFLB_DEVICE_TYPE_DBI, dev->idx) / 2 * 10 / config->clk_freq_hz + 5) / 10;
    div = (div) ? (div - 1) : 0;
    div = (div > 0xff) ? 0xff : div;
    regval = 0;
    regval |= div << DBI_CR_DBI_PRD_S_SHIFT;
    regval |= div << DBI_CR_DBI_PRD_I_SHIFT;
    regval |= div << DBI_CR_DBI_PRD_D_PH_0_SHIFT;
    regval |= div << DBI_CR_DBI_PRD_D_PH_1_SHIFT;
    putreg32(regval, reg_base + DBI_PRD_OFFSET);

    /* dbi output pixel format cfg */
    regval = getreg32(reg_base + DBI_PIX_CNT_OFFSET);
    if (config->pixel_output_format == DBI_PIXEL_OUTPUT_FORMAT_RGB_565) {
        regval &= ~DBI_CR_DBI_PIX_FORMAT;
    } else {
        regval |= DBI_CR_DBI_PIX_FORMAT;
    }
    putreg32(regval, reg_base + DBI_PIX_CNT_OFFSET);

    /* dbi input pixel format */
    regval = getreg32(reg_base + DBI_FIFO_CONFIG_0_OFFSET);
    regval &= ~DBI_FIFO_FORMAT_MASK;
    regval |= config->pixel_input_format << DBI_FIFO_FORMAT_SHIFT;

    /* clear fifo */
    regval |= DBI_TX_FIFO_CLR;

    /* disable YUV mode */
    regval &= ~DBI_FIFO_YUV_MODE;

    /* disable dma mode */
    regval &= ~DBI_DMA_TX_EN;
    putreg32(regval, reg_base + DBI_FIFO_CONFIG_0_OFFSET);

    /* tx fifo threshold cfg */
    regval = getreg32(reg_base + DBI_FIFO_CONFIG_1_OFFSET);
    regval &= ~DBI_TX_FIFO_TH_MASK;
    regval |= (config->tx_fifo_threshold << DBI_TX_FIFO_TH_SHIFT) & DBI_TX_FIFO_TH_MASK;
    putreg32(regval, reg_base + DBI_FIFO_CONFIG_1_OFFSET);

#if (DBI_QSPI_SUPPORT)
    regval = getreg32(reg_base + DBI_QSPI_CONFIG_OFFSET);

    /* cmd wire */
    if (config->cmd_wire_mode) {
        regval |= DBI_CR_QSPI_CMD_4B;
    } else {
        regval &= ~DBI_CR_QSPI_CMD_4B;
    }

    /* address wire */
    if (config->addr_wire_mode) {
        regval |= DBI_CR_QSPI_ADR_4B;
    } else {
        regval &= ~DBI_CR_QSPI_ADR_4B;
    }

    /* data/pixel wire */
    if (config->data_wire_mode) {
        regval |= DBI_CR_QSPI_DAT_4B;
    } else {
        regval &= ~DBI_CR_QSPI_DAT_4B;
    }

    putreg32(regval, reg_base + DBI_QSPI_CONFIG_OFFSET);
#endif

#if (DBI_YUV_SUPPORT)
    /* YUV to RGB parameter list. */
    regval = 0;
    regval |= (YUV_PRE_OFFSET_0 << DBI_CR_Y2R_PRE_0_SHIFT) & DBI_CR_Y2R_PRE_0_MASK;
    regval |= (YUV_PRE_OFFSET_1 << DBI_CR_Y2R_PRE_1_SHIFT) & DBI_CR_Y2R_PRE_1_MASK;
    regval |= (YUV_PRE_OFFSET_2 << DBI_CR_Y2R_PRE_2_SHIFT) & DBI_CR_Y2R_PRE_2_MASK;
    regval |= DBI_CR_Y2R_EN;
    putreg32(regval, reg_base + DBI_YUV_RGB_CONFIG_0_OFFSET);

    regval = 0;
    regval |= (YUV_POST_OFFSET_0 << DBI_CR_Y2R_POS_0_SHIFT) & DBI_CR_Y2R_POS_0_MASK;
    regval |= (YUV_POST_OFFSET_1 << DBI_CR_Y2R_POS_1_SHIFT) & DBI_CR_Y2R_POS_1_MASK;
    regval |= (YUV_POST_OFFSET_2 << DBI_CR_Y2R_POS_2_SHIFT) & DBI_CR_Y2R_POS_2_MASK;
    putreg32(regval, reg_base + DBI_YUV_RGB_CONFIG_1_OFFSET);

    regval = 0;
    regval |= (YUV_MATRIX00 << DBI_CR_Y2R_MTX_00_SHIFT) & DBI_CR_Y2R_MTX_00_MASK;
    regval |= (YUV_MATRIX01 << DBI_CR_Y2R_MTX_01_SHIFT) & DBI_CR_Y2R_MTX_01_MASK;
    regval |= ((YUV_MATRIX02 & 0x0ff) << DBI_CR_Y2R_MTX_02_L_SHIFT) & DBI_CR_Y2R_MTX_02_L_MASK;
    putreg32(regval, reg_base + DBI_YUV_RGB_CONFIG_2_OFFSET);

    regval = 0;
    regval |= (((YUV_MATRIX02 & 0xf00) >> 8) << DBI_CR_Y2R_MTX_02_U_SHIFT) & DBI_CR_Y2R_MTX_02_U_MASK;
    regval |= (YUV_MATRIX10 << DBI_CR_Y2R_MTX_10_SHIFT) & DBI_CR_Y2R_MTX_10_MASK;
    regval |= (YUV_MATRIX11 << DBI_CR_Y2R_MTX_11_SHIFT) & DBI_CR_Y2R_MTX_11_MASK;
    regval |= ((YUV_MATRIX12 & 0x00f) << DBI_CR_Y2R_MTX_12_L_SHIFT) & DBI_CR_Y2R_MTX_12_L_MASK;
    putreg32(regval, reg_base + DBI_YUV_RGB_CONFIG_3_OFFSET);

    regval = 0;
    regval |= (((YUV_MATRIX12 & 0xff0) >> 4) << DBI_CR_Y2R_MTX_12_U_SHIFT) & DBI_CR_Y2R_MTX_12_U_MASK;
    regval |= (YUV_MATRIX20 << DBI_CR_Y2R_MTX_20_SHIFT) & DBI_CR_Y2R_MTX_20_MASK;
    regval |= (YUV_MATRIX21 << DBI_CR_Y2R_MTX_21_SHIFT) & DBI_CR_Y2R_MTX_21_MASK;
    putreg32(regval, reg_base + DBI_YUV_RGB_CONFIG_4_OFFSET);

    regval = 0;
    regval |= (YUV_MATRIX22 << DBI_CR_Y2R_MTX_22_SHIFT) & DBI_CR_Y2R_MTX_22_MASK;
    putreg32(regval, reg_base + DBI_YUV_RGB_CONFIG_5_OFFSET);
#endif
}

void bflb_dbi_deinit(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    /* disable DBI transaction */
    regval = getreg32(reg_base + DBI_CONFIG_OFFSET);
    regval &= ~DBI_CR_DBI_EN;
    putreg32(regval, reg_base + DBI_CONFIG_OFFSET);

    /* clear fifo */
    regval = getreg32(reg_base + DBI_FIFO_CONFIG_0_OFFSET);
    regval |= DBI_TX_FIFO_CLR;
    putreg32(regval, reg_base + DBI_FIFO_CONFIG_0_OFFSET);
}

#if DBI_QSPI_SUPPORT
void bflb_dbi_qspi_set_addr(struct bflb_device_s *dev, uint8_t addr_byte_size, uint32_t addr_val)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    addr_byte_size = addr_byte_size ? (addr_byte_size - 1) : addr_byte_size;

    /* set address size */
    regval = getreg32(reg_base + DBI_QSPI_CONFIG_OFFSET);
    regval &= ~DBI_CR_QSPI_ADR_BC_MASK;
    regval |= (addr_byte_size << DBI_CR_QSPI_ADR_BC_SHIFT) & DBI_CR_QSPI_ADR_BC_MASK;
    putreg32(regval, reg_base + DBI_QSPI_CONFIG_OFFSET);

    /* set address value */
    putreg32(addr_val, reg_base + DBI_QSPI_ADR_OFFSET);
}
#endif

static void bflb_dbi_fill_fifo(struct bflb_device_s *dev, uint32_t words_cnt, uint32_t *data_buff)
{
    uint32_t reg_base;
    uint32_t regval;
    uint32_t fifo_cnt;

    reg_base = dev->reg_base;

    for (; words_cnt > 0;) {
        /* get fifo available count */
        regval = getreg32(reg_base + DBI_FIFO_CONFIG_1_OFFSET);
        fifo_cnt = (regval & DBI_TX_FIFO_CNT_MASK) >> DBI_TX_FIFO_CNT_SHIFT;

        if (fifo_cnt) {
            fifo_cnt = (fifo_cnt > words_cnt) ? words_cnt : fifo_cnt;
            words_cnt -= fifo_cnt;
        } else {
            continue;
        }

        /* fill fifo */
        for (; fifo_cnt > 0; fifo_cnt--, data_buff++) {
            putreg32(*data_buff, reg_base + DBI_FIFO_WDATA_OFFSET);
        }
    }
}

static uint32_t bflb_dbi_get_words_cnt_form_pixel(struct bflb_device_s *dev, uint32_t pixle_cnt)
{
    uint32_t reg_base;
    uint32_t regval;
    uint32_t words_cnt;
    uint8_t pixel_input_format;

    reg_base = dev->reg_base;

    /* get fifo input pixel_format */
    regval = getreg32(reg_base + DBI_FIFO_CONFIG_0_OFFSET);
    pixel_input_format = (regval & DBI_FIFO_FORMAT_MASK) >> DBI_FIFO_FORMAT_SHIFT;

    switch (pixel_input_format) {
        /* 32-bit/pixel format list */
        case DBI_PIXEL_INPUT_FORMAT_NBGR_8888:
        case DBI_PIXEL_INPUT_FORMAT_NRGB_8888:
        case DBI_PIXEL_INPUT_FORMAT_BGRN_8888:
        case DBI_PIXEL_INPUT_FORMAT_RGBN_8888:
            words_cnt = pixle_cnt;
            break;

        /* 24-bit/pixel format list */
        case DBI_PIXEL_INPUT_FORMAT_RGB_888:
        case DBI_PIXEL_INPUT_FORMAT_BGR_888:
            words_cnt = (pixle_cnt * 3 + 3) / 4;
            break;

        /* 16-bit/pixel format list */
        case DBI_PIXEL_INPUT_FORMAT_BGR_565:
        case DBI_PIXEL_INPUT_FORMAT_RGB_565:
            words_cnt = (pixle_cnt + 1) / 2;
            break;

        default:
            words_cnt = 0;
            break;
    }

    return words_cnt;
}

int bflb_dbi_send_cmd_data(struct bflb_device_s *dev, uint8_t cmd, uint8_t data_len, uint8_t *data_buff)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    /* null */
    if (data_len && data_buff == NULL) {
        return 0;
    }

    /* disable DBI transaction */
    regval = getreg32(reg_base + DBI_CONFIG_OFFSET);
    regval &= ~DBI_CR_DBI_EN;
    putreg32(regval, reg_base + DBI_CONFIG_OFFSET);

    if (((regval & DBI_CR_DBI_CMD_EN) == 0) && (data_len == 0)) {
        /* There is no data or command phase, nothing to do */
        return 0;
    }

    /* normal data mode  */
    regval &= ~DBI_CR_DBI_DAT_TP;

    /* write mode  */
    regval |= DBI_CR_DBI_DAT_WR;

    /* set data len */
    if (data_len) {
        regval |= DBI_CR_DBI_DAT_EN;
        regval &= ~DBI_CR_DBI_DAT_BC_MASK;
        regval |= ((data_len - 1) << DBI_CR_DBI_DAT_BC_SHIFT) & DBI_CR_DBI_DAT_BC_MASK;
    } else {
        regval &= ~DBI_CR_DBI_DAT_EN;
    }
    putreg32(regval, reg_base + DBI_CONFIG_OFFSET);

    /* set cmd */
    if (regval & DBI_CR_DBI_CMD_EN) {
        regval = getreg32(reg_base + DBI_CMD_OFFSET);
        regval &= ~DBI_CR_DBI_CMD_MASK;
        regval |= cmd << DBI_CR_DBI_CMD_SHIFT;
        putreg32(regval, reg_base + DBI_CMD_OFFSET);
    }

    /* clear fifo */
    regval = getreg32(reg_base + DBI_FIFO_CONFIG_0_OFFSET);
    regval |= DBI_TX_FIFO_CLR;
    putreg32(regval, reg_base + DBI_FIFO_CONFIG_0_OFFSET);

    /* clear complete interrupt  */
    regval = getreg32(reg_base + DBI_INT_STS_OFFSET);
    regval |= DBI_CR_DBI_END_CLR;
    putreg32(regval, reg_base + DBI_INT_STS_OFFSET);

    /* first fill some data into the fifo */
    if (data_len) {
        if (data_len <= SPI_FIFO_NUM_MAX * 4) {
            bflb_dbi_fill_fifo(dev, (data_len + 3) / 4, (uint32_t *)data_buff);
            data_len = 0;
        } else {
            bflb_dbi_fill_fifo(dev, SPI_FIFO_NUM_MAX, (uint32_t *)data_buff);
            data_len -= SPI_FIFO_NUM_MAX * 4;
        }
    }

    /* trigger the transaction */
    regval = getreg32(reg_base + DBI_CONFIG_OFFSET);
    regval |= DBI_CR_DBI_EN;
    putreg32(regval, reg_base + DBI_CONFIG_OFFSET);

    /* Fill the rest of the data into the fifo */
    if (data_len) {
        bflb_dbi_fill_fifo(dev, (data_len + 3) / 4, (uint32_t *)data_buff);
    }

    /* Wait transfer complete */
    do {
        regval = getreg32(reg_base + DBI_INT_STS_OFFSET);
    } while ((regval & DBI_END_INT) == 0);

    /* clear end int */
    regval |= DBI_CR_DBI_END_CLR;
    putreg32(regval, reg_base + DBI_INT_STS_OFFSET);

    return 0;
}

int bflb_dbi_send_cmd_read_data(struct bflb_device_s *dev, uint8_t cmd, uint8_t data_len, uint8_t *data_buff)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    /* disable DBI transaction */
    regval = getreg32(reg_base + DBI_CONFIG_OFFSET);
    regval &= ~DBI_CR_DBI_EN;
    putreg32(regval, reg_base + DBI_CONFIG_OFFSET);

    if (((regval & DBI_CR_DBI_CMD_EN) == 0) && (data_len == 0)) {
        /* There is no data or command phase, nothing to do */
        return 0;
    }

    /* normal data mode  */
    regval &= ~DBI_CR_DBI_DAT_TP;

    /* read mode  */
    regval &= ~DBI_CR_DBI_DAT_WR;

    /* set data len */
    if (data_len) {
        regval |= DBI_CR_DBI_DAT_EN;
        regval &= ~DBI_CR_DBI_DAT_BC_MASK;
        regval |= ((data_len - 1) << DBI_CR_DBI_DAT_BC_SHIFT) & DBI_CR_DBI_DAT_BC_MASK;
    } else {
        regval &= ~DBI_CR_DBI_DAT_EN;
    }
    putreg32(regval, reg_base + DBI_CONFIG_OFFSET);

    /* set cmd */
    if (regval & DBI_CR_DBI_CMD_EN) {
        regval = getreg32(reg_base + DBI_CMD_OFFSET);
        regval &= ~DBI_CR_DBI_CMD_MASK;
        regval |= cmd << DBI_CR_DBI_CMD_SHIFT;
        putreg32(regval, reg_base + DBI_CMD_OFFSET);
    }

    /* clear fifo */
    regval = getreg32(reg_base + DBI_FIFO_CONFIG_0_OFFSET);
    regval |= DBI_TX_FIFO_CLR;
    putreg32(regval, reg_base + DBI_FIFO_CONFIG_0_OFFSET);

    /* clear complete interrupt  */
    regval = getreg32(reg_base + DBI_INT_STS_OFFSET);
    regval |= DBI_CR_DBI_END_CLR;
    putreg32(regval, reg_base + DBI_INT_STS_OFFSET);

    /* trigger the transaction */
    regval = getreg32(reg_base + DBI_CONFIG_OFFSET);
    regval |= DBI_CR_DBI_EN;
    putreg32(regval, reg_base + DBI_CONFIG_OFFSET);

    /* Wait transfer complete */
    do {
        regval = getreg32(reg_base + DBI_INT_STS_OFFSET);
    } while ((regval & DBI_END_INT) == 0);

    /* clear end int */
    regval |= DBI_CR_DBI_END_CLR;
    putreg32(regval, reg_base + DBI_INT_STS_OFFSET);

    /* Null pointer error */
    if (data_buff == NULL) {
        return 0;
    }

    /* copy data to buff */
    regval = getreg32(reg_base + DBI_RDATA_0_OFFSET);
    for (uint8_t i = 0; (data_len > 0) && (i < 4); i++, data_len--) {
        *data_buff = (uint8_t)regval;
        data_buff++;
        regval >>= 8;
    }
    regval = getreg32(reg_base + DBI_RDATA_1_OFFSET);
    for (uint8_t i = 0; (data_len > 0) && (i < 4); i++, data_len--) {
        *data_buff = (uint8_t)regval;
        data_buff++;
        regval >>= 8;
    }

    return 0;
}

int bflb_dbi_send_cmd_pixel(struct bflb_device_s *dev, uint8_t cmd, uint32_t pixel_cnt, void *pixel_buff)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    /* disable DBI transaction */
    regval = getreg32(reg_base + DBI_CONFIG_OFFSET);
    regval &= ~DBI_CR_DBI_EN;
    putreg32(regval, reg_base + DBI_CONFIG_OFFSET);

    if (((regval & DBI_CR_DBI_CMD_EN) == 0) && (pixel_cnt == 0)) {
        /* There is no data or command phase, nothing to do */
        return 0;
    }

    /* pixel mode  */
    regval |= DBI_CR_DBI_DAT_TP;

    /* write mode  */
    regval |= DBI_CR_DBI_DAT_WR;

    /* pixle data phase enable */
    if (pixel_cnt) {
        regval |= DBI_CR_DBI_DAT_EN;
    } else {
        regval &= ~DBI_CR_DBI_DAT_EN;
    }
    putreg32(regval, reg_base + DBI_CONFIG_OFFSET);

    /* set cmd  */
    if (regval & DBI_CR_DBI_CMD_EN) {
        regval = getreg32(reg_base + DBI_CMD_OFFSET);
        regval &= ~DBI_CR_DBI_CMD_MASK;
        regval |= cmd << DBI_CR_DBI_CMD_SHIFT;
        putreg32(regval, reg_base + DBI_CMD_OFFSET);
    }

    /* pixel cnt */
    if (pixel_cnt) {
        regval = getreg32(reg_base + DBI_PIX_CNT_OFFSET);
        regval &= ~DBI_CR_DBI_PIX_CNT_MASK;
        regval |= ((pixel_cnt - 1) << DBI_CR_DBI_PIX_CNT_SHIFT) & DBI_CR_DBI_PIX_CNT_MASK;
        putreg32(regval, reg_base + DBI_PIX_CNT_OFFSET);
    }

    /* clear fifo */
    regval = getreg32(reg_base + DBI_FIFO_CONFIG_0_OFFSET);
    regval |= DBI_TX_FIFO_CLR;
    putreg32(regval, reg_base + DBI_FIFO_CONFIG_0_OFFSET);

    /* clear complete interrupt  */
    regval = getreg32(reg_base + DBI_INT_STS_OFFSET);
    regval |= DBI_CR_DBI_END_CLR;
    putreg32(regval, reg_base + DBI_INT_STS_OFFSET);

    /* trigger the transaction */
    regval = getreg32(reg_base + DBI_CONFIG_OFFSET);
    regval |= DBI_CR_DBI_EN;
    putreg32(regval, reg_base + DBI_CONFIG_OFFSET);

    /* No need to fill in fifo, for DMA mode */
    if (pixel_buff == NULL) {
        return 0;
    }

    /* fill the data into the fifo, can only be used in non-DMA mode */
    bflb_dbi_fill_fifo(dev, bflb_dbi_get_words_cnt_form_pixel(dev, pixel_cnt), (uint32_t *)pixel_buff);

    /* Wait transfer complete */
    do {
        regval = getreg32(reg_base + DBI_INT_STS_OFFSET);
    } while ((regval & DBI_END_INT) == 0);

    /* clear end int */
    regval |= DBI_CR_DBI_END_CLR;
    putreg32(regval, reg_base + DBI_INT_STS_OFFSET);

    return 0;
}

void bflb_dbi_link_txdma(struct bflb_device_s *dev, bool enable)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + DBI_FIFO_CONFIG_0_OFFSET);
    if (enable) {
        regval |= DBI_DMA_TX_EN;
    } else {
        regval &= ~DBI_DMA_TX_EN;
    }
    putreg32(regval, reg_base + DBI_FIFO_CONFIG_0_OFFSET);
}

void bflb_dbi_txint_mask(struct bflb_device_s *dev, bool mask)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + DBI_INT_STS_OFFSET);
    if (mask) {
        regval |= DBI_CR_DBI_TXF_MASK;
    } else {
        regval &= ~DBI_CR_DBI_TXF_MASK;
    }
    putreg32(regval, reg_base + DBI_INT_STS_OFFSET);
}

void bflb_dbi_tcint_mask(struct bflb_device_s *dev, bool mask)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + DBI_INT_STS_OFFSET);
    if (mask) {
        regval |= DBI_CR_DBI_END_MASK;
    } else {
        regval &= ~DBI_CR_DBI_END_MASK;
    }
    putreg32(regval, reg_base + DBI_INT_STS_OFFSET);
}

void bflb_dbi_errint_mask(struct bflb_device_s *dev, bool mask)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + DBI_INT_STS_OFFSET);
    if (mask) {
        regval |= DBI_CR_DBI_FER_MASK;
    } else {
        regval &= ~DBI_CR_DBI_FER_MASK;
    }
    putreg32(regval, reg_base + DBI_INT_STS_OFFSET);
}

uint32_t bflb_dbi_get_intstatus(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval;
    uint32_t int_sts;

    reg_base = dev->reg_base;
    int_sts = 0;

    regval = getreg32(reg_base + DBI_INT_STS_OFFSET);

    /* transfer completion interrupt */
    if (regval & DBI_END_INT) {
        int_sts |= DBI_INTSTS_TC;
    }

    /* fifo threshold interrupt */
    if (regval & DBI_TXF_INT) {
        int_sts |= SPI_INTSTS_TX_FIFO;
    }

    /* fifo error (underflow or overflow) interrupt */
    if (regval & DBI_FER_INT) {
        int_sts |= SPI_INTSTS_FIFO_ERR;
    }

    return int_sts;
}

void bflb_dbi_int_clear(struct bflb_device_s *dev, uint32_t int_clear)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + DBI_INT_STS_OFFSET);

    /* transfer completion interrupt */
    if (int_clear & DBI_INTCLR_TC) {
        regval |= DBI_CR_DBI_END_CLR;
    }

    putreg32(regval, reg_base + DBI_INT_STS_OFFSET);
}

int bflb_dbi_feature_control(struct bflb_device_s *dev, int cmd, size_t arg)
{
    int ret = 0;
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    switch (cmd) {
        case DBI_CMD_CLEAR_TX_FIFO:
            /* clear fifo */
            regval = getreg32(reg_base + DBI_FIFO_CONFIG_0_OFFSET);
            regval |= DBI_TX_FIFO_CLR;
            putreg32(regval, reg_base + DBI_FIFO_CONFIG_0_OFFSET);
            break;

        case DBI_CMD_GET_TX_FIFO_CNT:
            /* get fifo available count */
            regval = getreg32(reg_base + DBI_FIFO_CONFIG_1_OFFSET);
            ret = (regval & DBI_TX_FIFO_CNT_MASK) >> DBI_TX_FIFO_CNT_SHIFT;
            break;

        case DBI_CMD_MASK_CMD_PHASE:
            /* mask command phase, arg use true or false,
               true: no command phase, false: command will be sent
               don't-care if QSPI mode is selected (command always sent)
            */
            regval = getreg32(reg_base + DBI_CONFIG_OFFSET);
#if (DBI_QSPI_SUPPORT)
            /* the setting is not valid for the qspi mode */
            if ((regval & DBI_CR_DBI_SEL_MASK) >> DBI_CR_DBI_SEL_SHIFT == DBI_MODE_EX_QSPI) {
                break;
            }
#endif
            if (arg) {
                regval &= ~DBI_CR_DBI_CMD_EN;
            } else {
                regval |= DBI_CR_DBI_CMD_EN;
            }
            putreg32(regval, reg_base + DBI_CONFIG_OFFSET);
            break;

        case DBI_CMD_CS_CONTINUE:
            /* set CS continue mode, arg use true or false */
            regval = getreg32(reg_base + DBI_CONFIG_OFFSET);
            if (arg) {
                regval |= DBI_CR_DBI_CONT_EN;
            } else {
                regval &= ~DBI_CR_DBI_CONT_EN;
            }
            putreg32(regval, reg_base + DBI_CONFIG_OFFSET);
            break;

        case DBI_CMD_SET_DUMMY_CNT:
            /* set dummy cycle(s) between command phase and data phase
               arg range: 0 ~ 16,
               don't-care if QSPI mode is selected (no dummy cycle)
             */
            regval = getreg32(reg_base + DBI_CONFIG_OFFSET);
#if (DBI_QSPI_SUPPORT)
            /* the setting is not valid for the qspi mode */
            if ((regval & DBI_CR_DBI_SEL_MASK) >> DBI_CR_DBI_SEL_SHIFT == DBI_MODE_EX_QSPI) {
                break;
            }
#endif
            if (arg) {
                regval |= DBI_CR_DBI_DMY_EN;
                regval &= ~DBI_CR_DBI_DMY_CNT_MASK;
                regval |= ((arg - 1) << DBI_CR_DBI_DMY_CNT_SHIFT) & DBI_CR_DBI_DMY_CNT_MASK;
            } else {
                regval &= ~DBI_CR_DBI_DMY_EN;
            }
            putreg32(regval, reg_base + DBI_CONFIG_OFFSET);
            break;

        case DBI_CMD_GET_SIZE_OF_PIXEL_CNT:
            /* gets the pixel_data size(byte), arg: pixel number */
            ret = bflb_dbi_get_words_cnt_form_pixel(dev, arg) * 4;
            break;

        case DBI_CMD_INPUT_PIXEL_FORMAT:
            /* dbi input pixel format, arg use @ref DBI_PIXEL_INPUT_FORMAT */
            regval = getreg32(reg_base + DBI_FIFO_CONFIG_0_OFFSET);
            regval &= ~DBI_FIFO_FORMAT_MASK;
            regval |= (arg << DBI_FIFO_FORMAT_SHIFT) & DBI_FIFO_FORMAT_MASK;
            putreg32(regval, reg_base + DBI_FIFO_CONFIG_0_OFFSET);
            break;

        case DBI_CMD_OUTPUT_PIXEL_FORMAT:
            /* dbi output pixel format, arg use @ref DBI_PIXEL_OUTPUT_FORMAT */
            regval = getreg32(reg_base + DBI_PIX_CNT_OFFSET);
            if (arg == DBI_PIXEL_OUTPUT_FORMAT_RGB_565) {
                regval &= ~DBI_CR_DBI_PIX_FORMAT;
            } else if (arg == DBI_PIXEL_OUTPUT_FORMAT_RGB_888) {
                regval |= DBI_CR_DBI_PIX_FORMAT;
            }
            putreg32(regval, reg_base + DBI_PIX_CNT_OFFSET);
            break;

#if (DBI_YUV_SUPPORT)
        case DBI_CMD_YUV_TO_RGB_ENABLE:
            /* yuv to rgb cfg, arg use true or false */
            regval = getreg32(reg_base + DBI_FIFO_CONFIG_0_OFFSET);
            if (arg) {
                regval |= DBI_FIFO_YUV_MODE;
            } else {
                regval &= ~DBI_FIFO_YUV_MODE;
            }
            putreg32(regval, reg_base + DBI_FIFO_CONFIG_0_OFFSET);
            break;
#endif

        default:
            ret = -EPERM;
            break;
    }

    return ret;
}
