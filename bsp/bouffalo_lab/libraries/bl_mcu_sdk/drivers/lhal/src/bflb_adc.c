#include "bflb_adc.h"
#include "bflb_efuse.h"
#include "hardware/adc_reg.h"

#if defined(BL702) || defined(BL602) || defined(BL702L)
#define ADC_GPIP_BASE ((uint32_t)0x40002000)
#elif defined(BL616) || defined(BL606P) || defined(BL808) || defined(BL628)
#define ADC_GPIP_BASE ((uint32_t)0x20002000)
#endif

volatile float coe = 1.0;
volatile uint32_t tsen_offset;

void bflb_adc_init(struct bflb_device_s *dev, const struct bflb_adc_config_s *config)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    /* adc disable */
    regval = getreg32(reg_base + AON_GPADC_REG_CMD_OFFSET);
    regval &= ~AON_GPADC_GLOBAL_EN;
    putreg32(regval, reg_base + AON_GPADC_REG_CMD_OFFSET);

    regval = getreg32(reg_base + AON_GPADC_REG_CMD_OFFSET);
    regval |= AON_GPADC_GLOBAL_EN;
    putreg32(regval, reg_base + AON_GPADC_REG_CMD_OFFSET);

    /* adc reset */
    regval = getreg32(reg_base + AON_GPADC_REG_CMD_OFFSET);
    regval |= AON_GPADC_SOFT_RST;
    putreg32(regval, reg_base + AON_GPADC_REG_CMD_OFFSET);

    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");

    regval = getreg32(reg_base + AON_GPADC_REG_CMD_OFFSET);
    regval &= ~AON_GPADC_SOFT_RST;
    putreg32(regval, reg_base + AON_GPADC_REG_CMD_OFFSET);

    /* disable int and clear status */
    regval = getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
    regval |= (GPIP_GPADC_FIFO_UNDERRUN_MASK | GPIP_GPADC_FIFO_OVERRUN_MASK | GPIP_GPADC_RDY_MASK |
               GPIP_GPADC_FIFO_UNDERRUN_CLR | GPIP_GPADC_FIFO_OVERRUN_CLR | GPIP_GPADC_RDY_CLR);

#if defined(BL702) || defined(BL702L)
    regval |= (GPIP_GPADC_FIFO_RDY_MASK | GPIP_GPADC_FIFO_RDY);
#endif
    regval |= GPIP_GPADC_FIFO_CLR;
    regval &= ~GPIP_GPADC_FIFO_THL_MASK;
    regval &= ~GPIP_GPADC_DMA_EN;
    putreg32(regval, ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);

    bflb_adc_start_conversion(dev);
    bflb_mtimer_delay_ms(1);
    bflb_adc_stop_conversion(dev);

    regval = 0;
    regval |= (2 << AON_GPADC_V18_SEL_SHIFT);                     /* V18 select 1.82V */
    regval |= (1 << AON_GPADC_V11_SEL_SHIFT);                     /* V11 select 1.1V */
    regval |= (config->clk_div << AON_GPADC_CLK_DIV_RATIO_SHIFT); /* clock div */
    regval |= (config->resolution << AON_GPADC_RES_SEL_SHIFT);    /* resolution */
    if (config->scan_conv_mode) {
        regval |= AON_GPADC_SCAN_EN;
        regval |= AON_GPADC_CLK_ANA_INV;
    }
    if (config->continuous_conv_mode) {
        regval |= AON_GPADC_CONT_CONV_EN;
    }

    putreg32(regval, reg_base + AON_GPADC_REG_CONFIG1_OFFSET);

    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");

    regval = 0;
    regval |= (2 << AON_GPADC_DLY_SEL_SHIFT);
    regval |= (2 << AON_GPADC_CHOP_MODE_SHIFT); /* Vref AZ and PGA chop on */
    regval |= (1 << AON_GPADC_PGA1_GAIN_SHIFT); /* gain 1 */
    regval |= (1 << AON_GPADC_PGA2_GAIN_SHIFT); /* gain 1 */
    regval |= AON_GPADC_PGA_EN;
    regval |= (8 << AON_GPADC_PGA_OS_CAL_SHIFT);
    regval |= (1 << AON_GPADC_PGA_VCM_SHIFT); /* PGA output common mode control 1.4V */

    if (config->vref == ADC_VREF_2P0V) {
        regval |= AON_GPADC_VREF_SEL;
    }

    if (config->differential_mode) {
        regval |= AON_GPADC_DIFF_MODE;
    }

    putreg32(regval, reg_base + AON_GPADC_REG_CONFIG2_OFFSET);

    regval = getreg32(reg_base + AON_GPADC_REG_CMD_OFFSET);
    regval |= AON_GPADC_MIC2_DIFF; /* mic2 diff enable */
    if (config->differential_mode) {
        regval &= ~AON_GPADC_NEG_GND;
    } else {
        regval |= AON_GPADC_NEG_GND;
    }
    putreg32(regval, reg_base + AON_GPADC_REG_CMD_OFFSET);

    /* calibration offset */
    regval = getreg32(reg_base + AON_GPADC_REG_DEFINE_OFFSET);
    regval &= ~AON_GPADC_OS_CAL_DATA_MASK;
    putreg32(regval, reg_base + AON_GPADC_REG_DEFINE_OFFSET);

    /* disable int and clear status */
    regval = getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
    regval |= (GPIP_GPADC_FIFO_UNDERRUN_MASK | GPIP_GPADC_FIFO_OVERRUN_MASK | GPIP_GPADC_RDY_MASK |
               GPIP_GPADC_FIFO_UNDERRUN_CLR | GPIP_GPADC_FIFO_OVERRUN_CLR | GPIP_GPADC_RDY_CLR);

#if defined(BL702) || defined(BL702L)
    regval |= (GPIP_GPADC_FIFO_RDY_MASK | GPIP_GPADC_FIFO_RDY);
#endif
    regval |= GPIP_GPADC_FIFO_CLR;
    regval &= ~GPIP_GPADC_FIFO_THL_MASK;
    regval &= ~GPIP_GPADC_DMA_EN;
    putreg32(regval, ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);

    regval = getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
    regval &= ~(GPIP_GPADC_FIFO_UNDERRUN_CLR |
                GPIP_GPADC_FIFO_OVERRUN_CLR |
                GPIP_GPADC_RDY_CLR |
                GPIP_GPADC_FIFO_CLR);
    putreg32(regval, ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);

    regval = getreg32(reg_base + AON_GPADC_REG_ISR_OFFSET);
    regval |= AON_GPADC_NEG_SATUR_MASK;
    regval |= AON_GPADC_POS_SATUR_MASK;
    putreg32(regval, reg_base + AON_GPADC_REG_ISR_OFFSET);

    coe = bflb_efuse_get_adc_trim();              /* read from efuse */
    tsen_offset = bflb_efuse_get_adc_tsen_trim(); /* read from efuse */
}

void bflb_adc_deinit(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    /* adc disable */
    regval = getreg32(reg_base + AON_GPADC_REG_CMD_OFFSET);
    regval &= ~AON_GPADC_GLOBAL_EN;
    putreg32(regval, reg_base + AON_GPADC_REG_CMD_OFFSET);

    /* adc reset */
    regval = getreg32(reg_base + AON_GPADC_REG_CMD_OFFSET);
    regval |= AON_GPADC_SOFT_RST;
    putreg32(regval, reg_base + AON_GPADC_REG_CMD_OFFSET);

    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");

    regval = getreg32(reg_base + AON_GPADC_REG_CMD_OFFSET);
    regval &= ~AON_GPADC_SOFT_RST;
    putreg32(regval, reg_base + AON_GPADC_REG_CMD_OFFSET);

    putreg32(0, reg_base + AON_GPADC_REG_CONFIG1_OFFSET);
    putreg32(0, reg_base + AON_GPADC_REG_CONFIG2_OFFSET);
}

void bflb_adc_link_rxdma(struct bflb_device_s *dev, bool enable)
{
    uint32_t regval;

    regval = getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
    if (enable) {
        regval |= GPIP_GPADC_DMA_EN;
    } else {
        regval &= ~GPIP_GPADC_DMA_EN;
    }
    putreg32(regval, ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
}

int bflb_adc_channel_config(struct bflb_device_s *dev, struct bflb_adc_channel_s *chan, uint8_t channels)
{
    uint32_t regval;
    uint32_t regval2;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    if (!(getreg32(reg_base + AON_GPADC_REG_CONFIG1_OFFSET) & AON_GPADC_SCAN_EN)) {
        if (channels > 1) {
            return -EINVAL;
        }

        regval = getreg32(reg_base + AON_GPADC_REG_CMD_OFFSET);
        regval &= ~AON_GPADC_POS_SEL_MASK;
        regval &= ~AON_GPADC_NEG_SEL_MASK;
        regval |= (chan->pos_chan << AON_GPADC_POS_SEL_SHIFT);
        regval |= (chan->neg_chan << AON_GPADC_NEG_SEL_SHIFT);
        putreg32(regval, reg_base + AON_GPADC_REG_CMD_OFFSET);
    } else {
        if (channels < 6) {
            regval = 0;
            regval2 = 0;
            for (uint8_t i = 0; i < channels; i++) {
                regval |= (chan[i].pos_chan << (i * 5));
                regval2 |= (chan[i].neg_chan << (i * 5));
            }
            putreg32(regval, reg_base + AON_GPADC_REG_SCN_POS1_OFFSET);
            putreg32(regval2, reg_base + AON_GPADC_REG_SCN_NEG1_OFFSET);
        } else {
            regval = 0;
            regval2 = 0;
            for (uint8_t i = 0; i < 6; i++) {
                regval |= (chan[i].pos_chan << (i * 5));
                regval2 |= (chan[i].neg_chan << (i * 5));
            }
            putreg32(regval, reg_base + AON_GPADC_REG_SCN_POS1_OFFSET);
            putreg32(regval2, reg_base + AON_GPADC_REG_SCN_NEG1_OFFSET);

            regval = 0;
            regval2 = 0;
            for (uint8_t i = 0; i < (channels - 6); i++) {
                regval |= (chan[i + 6].pos_chan << (i * 5));
                regval2 |= (chan[i + 6].neg_chan << (i * 5));
            }
            putreg32(regval, reg_base + AON_GPADC_REG_SCN_POS2_OFFSET);
            putreg32(regval2, reg_base + AON_GPADC_REG_SCN_NEG2_OFFSET);
        }

        regval = getreg32(reg_base + AON_GPADC_REG_CONFIG1_OFFSET);
        regval &= ~AON_GPADC_SCAN_LENGTH_MASK;
        regval |= ((channels - 1) << AON_GPADC_SCAN_LENGTH_SHIFT);
        putreg32(regval, reg_base + AON_GPADC_REG_CONFIG1_OFFSET);
    }
    return 0;
}

void bflb_adc_start_conversion(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + AON_GPADC_REG_CMD_OFFSET);
    regval &= ~AON_GPADC_CONV_START;
    putreg32(regval, reg_base + AON_GPADC_REG_CMD_OFFSET);

    bflb_mtimer_delay_us(100);

    regval = getreg32(reg_base + AON_GPADC_REG_CMD_OFFSET);
    regval |= AON_GPADC_CONV_START;
    putreg32(regval, reg_base + AON_GPADC_REG_CMD_OFFSET);
}

void bflb_adc_stop_conversion(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + AON_GPADC_REG_CMD_OFFSET);
    regval &= ~AON_GPADC_CONV_START;
    putreg32(regval, reg_base + AON_GPADC_REG_CMD_OFFSET);
}

uint8_t bflb_adc_get_count(struct bflb_device_s *dev)
{
    return ((getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET) & GPIP_GPADC_FIFO_DATA_COUNT_MASK) >> GPIP_GPADC_FIFO_DATA_COUNT_SHIFT);
}

uint32_t bflb_adc_read_raw(struct bflb_device_s *dev)
{
    return getreg32(ADC_GPIP_BASE + GPIP_GPADC_DMA_RDATA_OFFSET) & GPIP_GPADC_DMA_RDATA_MASK;
}

void bflb_adc_rxint_mask(struct bflb_device_s *dev, bool mask)
{
    uint32_t regval;

    regval = getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
    if (mask) {
        regval |= GPIP_GPADC_RDY_MASK;
    } else {
        regval &= ~GPIP_GPADC_RDY_MASK;
    }
    putreg32(regval, ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
}

void bflb_adc_errint_mask(struct bflb_device_s *dev, bool mask)
{
    uint32_t regval;
    uint32_t regval2;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + AON_GPADC_REG_ISR_OFFSET);
    regval2 = getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);

    if (mask) {
        regval |= AON_GPADC_POS_SATUR_MASK;
        regval |= AON_GPADC_NEG_SATUR_MASK;
        regval2 |= GPIP_GPADC_FIFO_UNDERRUN_MASK;
        regval2 |= GPIP_GPADC_FIFO_OVERRUN_MASK;
    } else {
        regval &= ~AON_GPADC_POS_SATUR_MASK;
        regval &= ~AON_GPADC_NEG_SATUR_MASK;
        regval2 &= ~GPIP_GPADC_FIFO_UNDERRUN_MASK;
        regval2 &= ~GPIP_GPADC_FIFO_OVERRUN_MASK;
    }
    putreg32(regval, reg_base + AON_GPADC_REG_ISR_OFFSET);
    putreg32(regval2, ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
}

uint32_t bflb_adc_get_intstatus(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval = 0;

    reg_base = dev->reg_base;

    if (getreg32(reg_base + AON_GPADC_REG_ISR_OFFSET) & AON_GPADC_NEG_SATUR) {
        regval |= ADC_INTSTS_NEG_SATURATION;
    }
    if (getreg32(reg_base + AON_GPADC_REG_ISR_OFFSET) & AON_GPADC_POS_SATUR) {
        regval |= ADC_INTSTS_POS_SATURATION;
    }
    if (getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET) & GPIP_GPADC_FIFO_UNDERRUN) {
        regval |= ADC_INTSTS_FIFO_UNDERRUN;
    }
    if (getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET) & GPIP_GPADC_FIFO_OVERRUN) {
        regval |= ADC_INTSTS_FIFO_OVERRUN;
    }
    if (getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET) & GPIP_GPADC_RDY) {
        regval |= ADC_INTSTS_ADC_READY;
    }
    return regval;
}

void bflb_adc_int_clear(struct bflb_device_s *dev, uint32_t int_clear)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    if (int_clear & ADC_INTCLR_NEG_SATURATION) {
        regval = getreg32(reg_base + AON_GPADC_REG_ISR_OFFSET);
        regval &= ~AON_GPADC_NEG_SATUR_CLR;
        putreg32(regval, reg_base + AON_GPADC_REG_ISR_OFFSET);

        regval = getreg32(reg_base + AON_GPADC_REG_ISR_OFFSET);
        regval |= AON_GPADC_NEG_SATUR_CLR;
        putreg32(regval, reg_base + AON_GPADC_REG_ISR_OFFSET);

        regval = getreg32(reg_base + AON_GPADC_REG_ISR_OFFSET);
        regval &= ~AON_GPADC_NEG_SATUR_CLR;
        putreg32(regval, reg_base + AON_GPADC_REG_ISR_OFFSET);
    }
    if (int_clear & ADC_INTCLR_POS_SATURATION) {
        regval = getreg32(reg_base + AON_GPADC_REG_ISR_OFFSET);
        regval &= ~AON_GPADC_POS_SATUR_CLR;
        putreg32(regval, reg_base + AON_GPADC_REG_ISR_OFFSET);

        regval = getreg32(reg_base + AON_GPADC_REG_ISR_OFFSET);
        regval |= AON_GPADC_POS_SATUR_CLR;
        putreg32(regval, reg_base + AON_GPADC_REG_ISR_OFFSET);

        regval = getreg32(reg_base + AON_GPADC_REG_ISR_OFFSET);
        regval &= ~AON_GPADC_POS_SATUR_CLR;
        putreg32(regval, reg_base + AON_GPADC_REG_ISR_OFFSET);
    }
    if (int_clear & ADC_INTCLR_FIFO_UNDERRUN) {
        regval = getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
        regval &= ~GPIP_GPADC_FIFO_UNDERRUN_CLR;
        putreg32(regval, ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);

        regval = getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
        regval |= GPIP_GPADC_FIFO_UNDERRUN_CLR;
        putreg32(regval, ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);

        regval = getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
        regval &= ~GPIP_GPADC_FIFO_UNDERRUN_CLR;
        putreg32(regval, ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
    }
    if (int_clear & ADC_INTCLR_FIFO_OVERRUN) {
        regval = getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
        regval &= ~GPIP_GPADC_FIFO_OVERRUN_CLR;
        putreg32(regval, ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);

        regval = getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
        regval |= GPIP_GPADC_FIFO_OVERRUN_CLR;
        putreg32(regval, ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);

        regval = getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
        regval &= ~GPIP_GPADC_FIFO_OVERRUN_CLR;
        putreg32(regval, ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
    }
    if (int_clear & ADC_INTCLR_ADC_READY) {
        regval = getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
        regval &= ~GPIP_GPADC_RDY_CLR;
        putreg32(regval, ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);

        regval = getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
        regval |= GPIP_GPADC_RDY_CLR;
        putreg32(regval, ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);

        regval = getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
        regval &= ~GPIP_GPADC_RDY_CLR;
        putreg32(regval, ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
    }
}

void bflb_adc_parse_result(struct bflb_device_s *dev, uint32_t *buffer, struct bflb_adc_result_s *result, uint16_t count)
{
    uint32_t reg_base;
    uint8_t resolution;
    uint8_t diff_mode;
    uint8_t vref;
    uint32_t conv_result = 0;
    uint16_t ref = 3200;
    uint8_t neg = 0;
    uint32_t tmp;

    reg_base = dev->reg_base;

    resolution = (getreg32(reg_base + AON_GPADC_REG_CONFIG1_OFFSET) & AON_GPADC_RES_SEL_MASK) >> AON_GPADC_RES_SEL_SHIFT;
    diff_mode = (getreg32(reg_base + AON_GPADC_REG_CONFIG2_OFFSET) & AON_GPADC_DIFF_MODE) >> 2;
    vref = (getreg32(reg_base + AON_GPADC_REG_CONFIG2_OFFSET) & AON_GPADC_VREF_SEL) >> 3;

    if (vref == ADC_VREF_2P0V) {
        ref = 2000;
    }

    /* single mode */
    if (diff_mode == 0) {
        for (uint16_t i = 0; i < count; i++) {
            result[i].pos_chan = buffer[i] >> 21;
            result[i].neg_chan = -1;

            if (resolution == ADC_RESOLUTION_12B) {
                conv_result = (uint32_t)(((buffer[i] & 0xffff) >> 4) / coe);
                if (conv_result > 4095) {
                    conv_result = 4095;
                }
                result[i].value = conv_result;
                result[i].millivolt = (float)result[i].value / 4096 * ref;
            } else if (resolution == ADC_RESOLUTION_14B) {
                conv_result = (uint32_t)(((buffer[i] & 0xffff) >> 2) / coe);
                if (conv_result > 16383) {
                    conv_result = 16383;
                }
                result[i].value = conv_result;
                result[i].millivolt = (float)result[i].value / 16384 * ref;
            } else if (resolution == ADC_RESOLUTION_16B) {
                conv_result = (uint32_t)((buffer[i] & 0xffff) / coe);
                if (conv_result > 65535) {
                    conv_result = 65535;
                }
                result[i].value = conv_result;
                result[i].millivolt = (int32_t)result[i].value / 65536.0 * ref;
            } else {
            }
        }
    } else {
        for (uint16_t i = 0; i < count; i++) {
            result[i].pos_chan = buffer[i] >> 21;
            result[i].neg_chan = (buffer[i] >> 16) & 0x1F;

            tmp = buffer[i];

            if (tmp & 0x8000) {
                tmp = ~tmp;
                tmp += 1;
                neg = 1;
            }

            if (resolution == ADC_RESOLUTION_12B) {
                conv_result = (uint32_t)(((tmp & 0xffff) >> 4) / coe);
                if (conv_result > 2047) {
                    conv_result = 2047;
                }
                result[i].value = conv_result;
                result[i].millivolt = (float)result[i].value / 2048 * ref;
            } else if (resolution == ADC_RESOLUTION_14B) {
                conv_result = (uint32_t)(((tmp & 0xffff) >> 2) / coe);
                if (conv_result > 8191) {
                    conv_result = 8191;
                }
                result[i].value = conv_result;
                result[i].millivolt = (float)result[i].value / 8192 * ref;
            } else if (resolution == ADC_RESOLUTION_16B) {
                conv_result = (uint32_t)((tmp & 0xffff) / coe);
                if (conv_result > 32767) {
                    conv_result = 32767;
                }
                result[i].value = conv_result;
                result[i].millivolt = (float)result[i].value / 32768 * ref;
            } else {
            }

            if (neg) {
                result[i].value = -result[i].value;
                result[i].millivolt = -result[i].millivolt;
            }
        }
    }
}

void bflb_adc_tsen_init(struct bflb_device_s *dev, uint8_t tsen_mod)
{
    uint32_t regval;
    uint32_t reg_base;
    reg_base = dev->reg_base;

    regval = getreg32(reg_base + AON_GPADC_REG_CMD_OFFSET);
    regval &= ~AON_GPADC_SEN_TEST_EN;
    regval |= (0 << AON_GPADC_SEN_SEL_SHIFT);
    regval &= ~AON_GPADC_CHIP_SEN_PU;
    regval |= AON_GPADC_DWA_EN;
    putreg32(regval, reg_base + AON_GPADC_REG_CMD_OFFSET);

    regval = getreg32(reg_base + AON_GPADC_REG_CONFIG2_OFFSET);
    regval &= ~AON_GPADC_TSVBE_LOW;
    regval |= (2 << AON_GPADC_DLY_SEL_SHIFT);
    regval |= (0 << AON_GPADC_TEST_SEL_SHIFT);
    regval &= ~AON_GPADC_TEST_EN;
    regval |= AON_GPADC_TS_EN;
    if (tsen_mod) {
        regval |= AON_GPADC_TSEXT_SEL;
    } else {
        regval &= ~AON_GPADC_TSEXT_SEL;
    }
    regval |= (2 << AON_GPADC_PGA_VCM_SHIFT);
    regval &= ~AON_GPADC_PGA_VCMI_EN;
    regval |= (0 << AON_GPADC_PGA_OS_CAL_SHIFT);
    putreg32(regval, reg_base + AON_GPADC_REG_CONFIG2_OFFSET);

    regval = getreg32(reg_base + AON_GPADC_REG_CONFIG1_OFFSET);
    regval |= AON_GPADC_DITHER_EN;
    putreg32(regval, reg_base + AON_GPADC_REG_CONFIG1_OFFSET);

    regval = getreg32(reg_base + AON_GPADC_REG_CMD_OFFSET);
    regval |= AON_GPADC_MIC2_DIFF;
    putreg32(regval, reg_base + AON_GPADC_REG_CMD_OFFSET);
}

float bflb_adc_tsen_get_temp(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;
    struct bflb_adc_result_s result;
    uint32_t v0 = 0, v1 = 0;
    float temp = 0;
    uint32_t raw_data;
    uint64_t start_time;

    reg_base = dev->reg_base;

    regval = getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
    regval |= (0 << 22);
    regval |= GPIP_GPADC_FIFO_CLR;
    putreg32(regval, ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);

    regval = getreg32(reg_base + AON_GPADC_REG_CONFIG2_OFFSET);
    regval &= ~AON_GPADC_TSVBE_LOW;
    putreg32(regval, reg_base + AON_GPADC_REG_CONFIG2_OFFSET);

    bflb_adc_start_conversion(dev);
    start_time = bflb_mtimer_get_time_ms();
    while (bflb_adc_get_count(dev) == 0) {
        if ((bflb_mtimer_get_time_ms() - start_time) > 100) {
            return -ETIMEDOUT;
        }
    }
    raw_data = bflb_adc_read_raw(dev);
    bflb_adc_parse_result(dev, &raw_data, &result, 1);
    v0 = result.value;
    regval = getreg32(ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);
    regval |= GPIP_GPADC_FIFO_CLR;
    putreg32(regval, ADC_GPIP_BASE + GPIP_GPADC_CONFIG_OFFSET);

    regval = getreg32(reg_base + AON_GPADC_REG_CONFIG2_OFFSET);
    regval |= AON_GPADC_TSVBE_LOW;
    putreg32(regval, reg_base + AON_GPADC_REG_CONFIG2_OFFSET);

    bflb_adc_start_conversion(dev);
    start_time = bflb_mtimer_get_time_ms();
    while (bflb_adc_get_count(dev) == 0) {
        if ((bflb_mtimer_get_time_ms() - start_time) > 100) {
            return -ETIMEDOUT;
        }
    }
    raw_data = bflb_adc_read_raw(dev);
    bflb_adc_parse_result(dev, &raw_data, &result, 1);
    v1 = result.value;
    if (v0 > v1) {
        temp = (((float)v0 - (float)v1) - (float)tsen_offset) / 7.753;
    } else {
        temp = (((float)v1 - (float)v0) - (float)tsen_offset) / 7.753;
    }

    return temp;
}

void bflb_adc_vbat_enable(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + AON_GPADC_REG_CONFIG2_OFFSET);
    regval |= AON_GPADC_VBAT_EN;
    putreg32(regval, reg_base + AON_GPADC_REG_CONFIG2_OFFSET);
}

void bflb_adc_vbat_disable(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + AON_GPADC_REG_CONFIG2_OFFSET);
    regval &= ~AON_GPADC_VBAT_EN;
    putreg32(regval, reg_base + AON_GPADC_REG_CONFIG2_OFFSET);
}