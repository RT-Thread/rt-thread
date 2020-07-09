/*
 * drv_codec_icodec.h
 *
 *  Created on: 2017Äê1ÔÂ10ÈÕ
 *      Author: Urey
 */

#ifndef _DRV_CODEC_ICODEC_H_
#define _DRV_CODEC_ICODEC_H_

#include <stdint.h>

#include "x1000.h"
#include "drv_clock.h"


struct jz_icodec
{
    struct jz_i2s               *i2s;
    struct rt_audio_configure	 replay_config;
#ifdef AUDIO_DEVICE_USE_PRIVATE_BUFFER
    struct rt_mempool  			mp;
#endif /* AUDIO_DEVICE_USE_PRIVATE_BUFFER */
	uint32_t mapped_base;

	/* replay */
    int     user_replay_volume;
    int 	dac_user_mute;              	/*dac user mute state*/
    int 	aohp_in_pwsq;               	/*aohp in power up/down seq*/
    int 	hpl_wished_gain;                /*keep original hpl/r gain register value*/
    int 	hpr_wished_gain;
    int 	linl_wished_gain;               /*keep original hpl/r gain register value*/
    int 	linr_wished_gain;

};

#define ICODEC_PCM_FORMAT       AUDIO_FMT_PCM_S16_LE
#define ICODEC_SAMPLING_RATE    44100


/*  icodec internal register space */
enum {
    SCODA_REG_SR = 0x0,
    SCODA_REG_SR2,
    SCODA_REG_SIGR,
    SCODA_REG_SIGR2,
    SCODA_REG_SIGR3,
    SCODA_REG_SIGR5,
    SCODA_REG_SIGR7,
    SCODA_REG_MR,
    SCODA_REG_AICR_DAC,
    SCODA_REG_AICR_ADC,
    SCODA_REG_CR_DMIC,
    SCODA_REG_CR_MIC1,
    SCODA_REG_CR_MIC2,
    SCODA_REG_CR_DAC,
    SCODA_REG_CR_DAC2,
    SCODA_REG_CR_ADC,
    SCODA_REG_CR_MIX,
    SCODA_REG_DR_MIX,
    SCODA_REG_CR_VIC,
    SCODA_REG_CR_CK,
    SCODA_REG_FCR_DAC,
    SCODA_REG_SFCCR_DAC,
    SCODA_REG_SFFCR_DAC,
    SCODA_REG_FCR_ADC,
    SCODA_REG_CR_TIMER_MSB,
    SCODA_REG_CR_TIMER_LSB,
    SCODA_REG_ICR,
    SCODA_REG_IMR,
    SCODA_REG_IFR,
    SCODA_REG_IMR2,
    SCODA_REG_IFR2,
    SCODA_REG_GCR_DACL,
    SCODA_REG_GCR_DACR,
    SCODA_REG_GCR_DACL2,
    SCODA_REG_GCR_DACR2,
    SCODA_REG_GCR_MIC1,
    SCODA_REG_GCR_MIC2,
    SCODA_REG_GCR_ADCL,
    SCODA_REG_GCR_ADCR,
    SCODA_REG_GCR_MIXDACL,
    SCODA_REG_GCR_MIXDACR,
    SCODA_REG_GCR_MIXADCL,
    SCODA_REG_GCR_MIXADCR,
    SCODA_REG_CR_DAC_AGC,
    SCODA_REG_DR_DAC_AGC,
    SCODA_REG_CR_DAC2_AGC,
    SCODA_REG_DR_DAC2_AGC,
    SCODA_REG_CR_ADC_AGC,
    SCODA_REG_DR_ADC_AGC,
    SCODA_REG_SR_ADC_AGCDGL,
    SCODA_REG_SR_ADC_AGCDGR,
    SCODA_REG_SR_ADC_AGCAGL,
    SCODA_REG_SR_ADC_AGCAGR,
    SCODA_REG_CR_TR,
    SCODA_REG_DR_TR,
    SCODA_REG_SR_TR1,
    SCODA_REG_SR_TR2,
    SCODA_REG_SR_TR_SRCDAC,

/*  icodec internal register extend space */
    SCODA_MIX_0,
    SCODA_MIX_1,
    SCODA_MIX_2,
    SCODA_MIX_3,
    SCODA_MIX_4,

    SCODA_DAC_AGC0,
    SCODA_DAC_AGC1,
    SCODA_DAC_AGC2,
    SCODA_DAC_AGC3,

    SCODA_DAC2_AGC0,
    SCODA_DAC2_AGC1,
    SCODA_DAC2_AGC2,
    SCODA_DAC2_AGC3,

    SCODA_ADC_AGC0,
    SCODA_ADC_AGC1,
    SCODA_ADC_AGC2,
    SCODA_ADC_AGC3,
    SCODA_ADC_AGC4,
    SCODA_MAX_REG_NUM,
};



/*aicr dac*/
#define SCODA_AICR_DAC_ADWL_SHIFT (6)
#define SCODA_AICR_DAC_ADWL_MASK (0x3 << SCODA_AICR_DAC_ADWL_SHIFT)
#define SCODA_AICR_DAC_SLAVE_SHIFT (5)
#define SCODA_AICR_DAC_SLAVE_MASK (0x1 << SCODA_AICR_DAC_SLAVE_SHIFT)
#define SCODA_AICR_DAC_SLAVE (1 << 5)
#define SCODA_AICR_DAC_SB_SHIFT (4)
#define SCODA_AICR_DAC_SB_MASK (0x1 << SCODA_AICR_DAC_SB_SHIFT)
#define SCODA_AICR_DAC_AUDIOIF_SHIFT (0)
#define SCODA_AICR_DAC_AUDIO_MASK (0x3 << SCODA_AICR_DAC_AUDIOIF_SHIFT)
#define SCODA_AICR_DAC_AUDIOIF_I2S (0x3)

/* aicr adc */
#define SCODA_AICR_ADC_ADWL_SHIFT (6)
#define SCODA_AICR_ADC_ADWL_MASK (0x3 << SCODA_AICR_ADC_ADWL_SHIFT)
#define SCODA_AICR_ADC_SB_SHIFT (4)
#define SCODA_AICR_ADC_SB_MASK (0x1 << SCODA_AICR_ADC_SB_SHIFT)
#define SCODA_AICR_ADC_AUDIOIF_SHIFT (0)
#define SCODA_AICR_ADC_AUDIO_MASK (0x3 << SCODA_AICR_ADC_AUDIOIF_SHIFT)
#define SCODA_AICR_ADC_AUDIOIF_I2S (0x3)

/* cr vic */
#define SCODA_CR_VIC_SB_SHIFT (0)
#define SCODA_CR_VIC_SB_MASK (1 << SCODA_CR_VIC_SB_SHIFT)
#define SCODA_CR_VIC_SB_SLEEP_SHIFT (1)
#define SCODA_CR_VIC_SB_SLEEP_MASK (1 << SCODA_CR_VIC_SB_SLEEP_SHIFT)

/* fcr adc/dac */
#define SCODA_FCR_FREQ_SHIFT (0)
#define SCODA_FCR_FREQ_MASK (0xf << SCODA_FCR_FREQ_SHIFT)

/* cr dac */
#define SCODA_CR_DAC_SMUTE_SHIFT (7)
#define SCODA_CR_DAC_SMUTE_MASK (0x1 << SCODA_CR_DAC_SMUTE_SHIFT)
#define SCODA_CR_DAC_SB_SHIFT (4)
#define SCODA_CR_DAC_SB_MASK (0x1 << SCODA_CR_DAC_SB_SHIFT)
#define SCODA_CR_DAC_ZERO_SHIFT (0)
#define SCODA_CR_DAC_ZERO_MASK (0x1 << SCODA_CR_DAC_ZERO_SHIFT)

/* cr dac */
#define SCODA_CR_ADC_SMUTE_SHIFT (7)
#define SCODA_CR_ADC_SMUTE_MASK (0x1 << SCODA_CR_ADC_SMUTE_SHIFT)
#define SCODA_CR_ADC_MIC_SEL_SHIFT (6)
#define SCODA_CR_ADC_MIC_SEL_MASK (0x1 << SCODA_CR_ADC_MIC_SEL_SHIFT)
#define SCODA_CR_ADC_SB_SHIFT (4)
#define SCODA_CR_ADC_SB_MASK (0x1 << SCODA_CR_ADC_SB_SHIFT)
#define SCODA_CR_ADC_ZERO_SHIFT (0)
#define SCODA_CR_ADC_ZERO_MASK (0x1 << SCODA_CR_ADC_ZERO_SHIFT)

/* ifr */
#define SCODA_IFR_DAC_MUTE_SHIFT (0)
#define SCODA_IFR_DAC_MUTE_MASK (0x1 << SCODA_IFR_DAC_MUTE_SHIFT)
#define SCODA_IFR_ADC_MUTE_SHIFT (2)
#define SCODA_IFR_ADC_MUTE_MASK (0x1 << SCODA_IFR_ADC_MUTE_SHIFT)
#define SCODA_IFR_ADAS_LOCK_SHIFT (7)
#define SCODA_IFR_ADAS_LOCK_MASK (0x1 << SCODA_IFR_ADAS_LOCK_SHIFT)

/* cr ck */
#define SCODA_CR_CK_MCLK_DIV_SHIFT (6)
#define SCODA_CR_CK_MCLK_DIV_MASK (0x1 << SCODA_CR_CK_MCLK_DIV_SHIFT)
#define SCODA_CR_CK_SDCLK_SHIFT (4)
#define SCODA_CR_CK_SDCLK_MASK (0x1 << SCODA_CR_CK_SDCLK_SHIFT)
#define SCODA_CR_CRYSTAL_SHIFT (0)
#define SCODA_CR_CRYSTAL_MASK (0xf << SCODA_CR_CRYSTAL_SHIFT)

/* icr */
#define SCODA_ICR_INT_FORM_SHIFT (6)
#define SCODA_ICR_INT_FORM_MASK (0x3 << SCODA_ICR_INT_FORM_SHIFT)
#define SCODA_ICR_INT_FORM_HIGH (0)
#define SCODA_ICR_INT_FORM_LOW  (1)

/* imr */
#define SCODA_IMR_COMMON_MASK (0xff)
#define SCODA_IMR2_COMMON_MASK (0xff)

/*For Codec*/
#define RGADW       (0x4)
#define RGDATA      (0x8)


static inline void icodec_mapped_reg_set(uint32_t xreg, int xmask, int xval)
{
    int val = readl(xreg);
    val &= ~(xmask);
    val |= xval;
    writel(val, xreg);
}


static inline int icodec_mapped_test_bits(uint32_t xreg, int xmask, int xval)
{
    int val = readl(xreg);
    val &= xmask;
    return (val == xval);
}


/*
 * RGADW
 */
#define SCODA_RGDIN_BIT         (0)
#define SCODA_RGDIN_MASK        (0xff << SCODA_RGDIN_BIT)
#define SCODA_RGADDR_BIT        (8)
#define SCODA_RGADDR_MASK       (0x7f << SCODA_RGADDR_BIT)
#define SCODA_RGWR_BIT          (16)
#define SCODA_RGWR_MASK         (0x1  << SCODA_RGWR_BIT)

#define icodec_test_rw_inval(icodec)      \
    icodec_mapped_test_bits((icodec->mapped_base + RGADW), SCODA_RGWR_MASK, (1 << SCODA_RGWR_BIT))
/*
 * RGDATA
 */
#define SCODA_RGDOUT_BIT        (0)
#define SCODA_RGDOUT_MASK       (0xff << SCODA_RGDOUT_BIT)
#define SCODA_IRQ_BIT           (8)
#define SCODA_IRQ_MASK          (0x1  << SCODA_IRQ_BIT)

#define icodec_test_irq(icodec)   \
    icodec_mapped_test_bits((icodec->mapped_base + RGDATA), SCODA_IRQ_MASK, (1 << SCODA_IRQ_BIT))

static inline uint8_t icodec_hw_read_normal(struct jz_icodec *icodec, int reg)
{
    uint32_t mapped_base = icodec->mapped_base;
    int reval;
    int timeout = 0xfffff;
    uint32_t flags;

    while (icodec_test_rw_inval(icodec))
    {
        timeout--;
        if (!timeout)
        {
//            rt_kprintf("icodec test_rw_inval timeout\n");
            break;
        }
    }

    icodec_mapped_reg_set((mapped_base + RGADW), SCODA_RGWR_MASK,(0 << SCODA_RGWR_BIT));
    icodec_mapped_reg_set((mapped_base + RGADW), SCODA_RGADDR_MASK,(reg << SCODA_RGADDR_BIT));

    reval = readl((mapped_base + RGDATA));
    reval = readl((mapped_base + RGDATA));
    reval = readl((mapped_base + RGDATA));
    reval = readl((mapped_base + RGDATA));
    reval = readl((mapped_base + RGDATA));
    reval = ((reval & SCODA_RGDOUT_MASK) >> SCODA_RGDOUT_BIT);
//  rt_kprintf("reg %x = %x\n", reg, reval);

    return (uint8_t) reval;
}


static inline int icodec_hw_write_normal(struct jz_icodec *icodec, int reg, int data)
{
    uint32_t mapped_base = icodec->mapped_base;
    int ret = 0;
    int timeout = 0xfffff;
    uint32_t flags;


    while (icodec_test_rw_inval(icodec))
    {
        timeout--;
        if (!timeout)
        {
//            rt_kprintf("icodec test_rw_inval timeout\n");
            break;
        }
    }
    icodec_mapped_reg_set((mapped_base + RGADW), SCODA_RGDIN_MASK | SCODA_RGADDR_MASK,
                             (data << SCODA_RGDIN_BIT) | (reg << SCODA_RGADDR_BIT));
    icodec_mapped_reg_set((mapped_base + RGADW), SCODA_RGWR_MASK ,
                             1 << SCODA_RGWR_BIT);

    if (reg != SCODA_REG_IFR && reg != SCODA_REG_IFR2)
    {
        ret = icodec_hw_read_normal(icodec, reg);
        if (data != ret)
        {
//            rt_kprintf("icdc write reg %x err exp %x now is %x\n", reg, data, ret);
            ret = -1;
        }
    }
    return ret;
}

static int icodec_hw_write_extend(struct jz_icodec *icodec, uint8_t sreg, uint8_t sdata)
{
    int creg, cdata, dreg;
    switch (sreg) {
        case SCODA_MIX_0 ... SCODA_MIX_4:
            creg = SCODA_REG_CR_MIX;
            dreg = SCODA_REG_DR_MIX;
            sreg -= (SCODA_REG_SR_TR_SRCDAC + 1);
            break;
        case SCODA_DAC_AGC0 ... SCODA_DAC_AGC3:
            creg = SCODA_REG_CR_DAC_AGC;
            dreg = SCODA_REG_DR_DAC_AGC;
            sreg -= (SCODA_MIX_4 +1);
            break;
        case SCODA_DAC2_AGC0 ... SCODA_DAC2_AGC3:
            creg = SCODA_REG_CR_DAC2;
            dreg = SCODA_REG_DR_DAC2_AGC;
            sreg -= (SCODA_DAC_AGC3 + 1);
            break;
        case SCODA_ADC_AGC0 ... SCODA_ADC_AGC4:
            creg = SCODA_REG_CR_ADC_AGC;
            dreg = SCODA_REG_DR_ADC_AGC;
            sreg -= (SCODA_ADC_AGC4 + 1);
            break;
        default:
            return 0;
    }
//    rt_kprintf("write extend : sreg: %d [0 - 4], creg: %x sdata: %d\n", sreg, creg, sdata);

    cdata = (icodec_hw_read_normal(icodec,creg)&(~0x3f))|((sreg&0x3f)|0x40);

    icodec_hw_write_normal(icodec, creg, cdata);
    icodec_hw_write_normal(icodec, dreg, sdata);
    if(sdata!=icodec_hw_read_normal(icodec,dreg))
        return -1;
    return 0;
}


static uint8_t icodec_hw_read_extend(struct jz_icodec *icodec, uint8_t sreg)
{
    int creg, cdata, dreg, ddata;
    switch (sreg)
    {
        case SCODA_MIX_0 ... SCODA_MIX_4:
            creg = SCODA_REG_CR_MIX;
            dreg = SCODA_REG_DR_MIX;
            sreg -= (SCODA_REG_SR_TR_SRCDAC + 1);
            break;
        case SCODA_DAC_AGC0 ... SCODA_DAC_AGC3:
            creg = SCODA_REG_CR_DAC_AGC;
            dreg = SCODA_REG_DR_DAC_AGC;
            sreg -= (SCODA_MIX_4 +1);
            break;
        case SCODA_DAC2_AGC0 ... SCODA_DAC2_AGC3:
            creg = SCODA_REG_CR_DAC2;
            dreg = SCODA_REG_DR_DAC2_AGC;
            sreg -= (SCODA_DAC_AGC3 + 1);
            break;
        case SCODA_ADC_AGC0 ... SCODA_ADC_AGC4:
            creg = SCODA_REG_CR_ADC_AGC;
            dreg = SCODA_REG_DR_ADC_AGC;
            sreg -= (SCODA_ADC_AGC4 + 1);
            break;
        default:
            return 0;
    }
    cdata = (icodec_hw_read_normal(icodec, creg) & (~0x7f)) | (sreg & 0x3f);
    icodec_hw_write_normal(icodec, creg, cdata);
    ddata = icodec_hw_read_normal(icodec, dreg);

    return (uint8_t) ddata;
}


static inline uint8_t icodec_hw_read(struct jz_icodec *icodec, int reg)
{
    if (reg > SCODA_REG_SR_TR_SRCDAC)
        return icodec_hw_read_extend(icodec, reg);
    else
        return icodec_hw_read_normal(icodec, reg);
}
static inline int icodec_hw_write(struct jz_icodec *icodec, int reg, int data)
{
	if (reg > SCODA_REG_SR_TR_SRCDAC)
		return icodec_hw_write_extend(icodec, reg, data);
	else
		return icodec_hw_write_normal(icodec, reg, data);
}


#endif /* _DRV_CODEC_ICODEC_H_ */
