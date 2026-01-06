/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_WM8960_REG_H_
#define _HPM_WM8960_REG_H_

/* WM8960 register number */
#define WM8960_REG_NUM 56U

/* Define the register address of WM8960 */
#define WM8960_LINVOL   0x0U   /* Left Input Volume */
#define WM8960_RINVOL   0x1U   /* Right Input Volume */
#define WM8960_LOUT1    0x2U   /* LOUT1 Volume */
#define WM8960_ROUT1    0x3U   /* ROUT1 Volume */
#define WM8960_CLOCK1   0x4U   /* Clocking(1) */
#define WM8960_DACCTL1  0x5U   /* ADC and DAC Control (1) */
#define WM8960_DACCTL2  0x6U   /* ADC and DAC Control (2) */
#define WM8960_IFACE1   0x7U   /* Audio Interface */
#define WM8960_CLOCK2   0x8U   /* Clocking(2) */
#define WM8960_IFACE2   0x9U   /* Audio Interface */
#define WM8960_LDAC     0xaU   /* Left DAC */
#define WM8960_RDAC     0xbU   /* Right DAC Volume */
#define WM8960_RESET    0xfU   /* RESET */
#define WM8960_3D       0x10U  /* 3D Control */
#define WM8960_ALC1     0x11U  /* ALC (1) */
#define WM8960_ALC2     0x12U  /* ALC (2) */
#define WM8960_ALC3     0x13U  /* ALC (3) */
#define WM8960_NOISEG   0x14U  /* Noise Gate */
#define WM8960_LADC     0x15U  /* Left ADC  Volume */
#define WM8960_RADC     0x16U  /* Right ADC Volume */
#define WM8960_ADDCTL1  0x17U  /* Additional Control (1) */
#define WM8960_ADDCTL2  0x18U  /* Additional Control (2) */
#define WM8960_POWER1   0x19U  /* Power Mgmt (1) */
#define WM8960_POWER2   0x1aU  /* Power Mgmt (2) */
#define WM8960_ADDCTL3  0x1bU  /* Additional Control (3) */
#define WM8960_APOP1    0x1cU  /* Anti-Pop 1 */
#define WM8960_APOP2    0x1dU  /* Anti-pop 2 */
#define WM8960_LINPATH  0x20U  /* ADCL Signal Path */
#define WM8960_RINPATH  0x21U  /* ADCR  Signal  Path */
#define WM8960_LOUTMIX  0x22U  /* Left Out  Mix */
#define WM8960_ROUTMIX  0x25U  /* Right Out  Mix */
#define WM8960_MONOMIX1 0x26U  /* Mono Out Mix (1) */
#define WM8960_MONOMIX2 0x27U  /* Mono Out Mix (2) */
#define WM8960_LOUT2    0x28U  /* Left Speaker Volume */
#define WM8960_ROUT2    0x29U  /* Right Speaker Volume */
#define WM8960_MONO     0x2aU  /* OUT3 Volume */
#define WM8960_INBMIX1  0x2bU  /* Left Input Boost Mixer */
#define WM8960_INBMIX2  0x2cU  /* Right Input Boost Mixer */
#define WM8960_BYPASS1  0x2dU  /* Left Bypass */
#define WM8960_BYPASS2  0x2eU  /* Right Bypass */
#define WM8960_POWER3   0x2fU  /* Power Mgmt (3) */
#define WM8960_ADDCTL4  0x30U  /* Additional Control (4) */
#define WM8960_CLASSD1  0x31U  /* Class D Control (1) */
#define WM8960_CLASSD3  0x33U  /* Class D Control (2) */
#define WM8960_PLL1     0x34U  /* PLL (1) */
#define WM8960_PLL2     0x35U  /* PLL (2) */
#define WM8960_PLL3     0x36U  /* PLL (3) */
#define WM8960_PLL4     0x37U  /* PLL (4) */

/* Bitfield definition for register: LINVO */
/*
 * IPVU (RW)
 *
 * Input PGA Volume Update
 * Writing a 1 to this bit will cause left and right input PGA volumes to be updated (LINVOL and  RINVOL)
 */
#define WM8960_LINVO_IPVU_MASK (0x100U)
#define WM8960_LINVO_IPVU_SHIFT (8U)
#define WM8960_LINVO_IPVU_SET(x) (((uint16_t)(x) << WM8960_LINVO_IPVU_SHIFT) & WM8960_LINVO_IPVU_MASK)
#define WM8960_LINVO_IPVU_GET(x) (((uint16_t)(x) & WM8960_LINVO_IPVU_MASK) >> WM8960_LINVO_IPVU_SHIFT)

/*
 * LINMUTE (RW)
 *
 * Left Input PGA Analogue Mute 1 = Enable Mute 0 = Disable Mute Note: IPVU must be set to un-mute.
 */
#define WM8960_LINVO_LINMUTE_MASK (0x80U)
#define WM8960_LINVO_LINMUTE_SHIFT (7U)
#define WM8960_LINVO_LINMUTE_SET(x) (((uint16_t)(x) << WM8960_LINVO_LINMUTE_SHIFT) & WM8960_LINVO_LINMUTE_MASK)
#define WM8960_LINVO_LINMUTE_GET(x) (((uint16_t)(x) & WM8960_LINVO_LINMUTE_MASK) >> WM8960_LINVO_LINMUTE_SHIFT)

/*
 * LIZC (RW)
 *
 * Left Input PGA Zero Cross Detector 1 = Change gain on zero cross only 0 = Change gain immediately
 */
#define WM8960_LINVO_LIZC_MASK (0x40U)
#define WM8960_LINVO_LIZC_SHIFT (6U)
#define WM8960_LINVO_LIZC_SET(x) (((uint16_t)(x) << WM8960_LINVO_LIZC_SHIFT) & WM8960_LINVO_LIZC_MASK)
#define WM8960_LINVO_LIZC_GET(x) (((uint16_t)(x) & WM8960_LINVO_LIZC_MASK) >> WM8960_LINVO_LIZC_SHIFT)

/*
 * LINVOL (RW)
 *
 * Left Input PGA Volume Control
 * 111111 = +30dB
 * 111110 = +29.25dB
 * . . 0.75dB steps down to
 * 000000 = -17.25dB
 */
#define WM8960_LINVO_LINVOL_MASK (0x3FU)
#define WM8960_LINVO_LINVOL_SHIFT (0U)
#define WM8960_LINVO_LINVOL_SET(x) (((uint16_t)(x) << WM8960_LINVO_LINVOL_SHIFT) & WM8960_LINVO_LINVOL_MASK)
#define WM8960_LINVO_LINVOL_GET(x) (((uint16_t)(x) & WM8960_LINVO_LINVOL_MASK) >> WM8960_LINVO_LINVOL_SHIFT)

/* Bitfield definition for register: RINVOL */
/*
 * IPVU (RW)
 *
 * Input PGA Volume Update
 * Writing a 1 to this bit will cause left and right
 * input PGA volumes to be updated (LINVOL and RINVOL)
 */
#define WM8960_RINVOL_IPVU_MASK (0x100U)
#define WM8960_RINVOL_IPVU_SHIFT (8U)
#define WM8960_RINVOL_IPVU_SET(x) (((uint16_t)(x) << WM8960_RINVOL_IPVU_SHIFT) & WM8960_RINVOL_IPVU_MASK)
#define WM8960_RINVOL_IPVU_GET(x) (((uint16_t)(x) & WM8960_RINVOL_IPVU_MASK) >> WM8960_RINVOL_IPVU_SHIFT)

/*
 * RINMUTE (RW)
 *
 * Right Input PGA Analogue Mute
 * 1 = Enable Mute
 * 0 = Disable Mute
 * Note: IPVU must be set to un-mute.
 */
#define WM8960_RINVOL_RINMUTE_MASK (0x80U)
#define WM8960_RINVOL_RINMUTE_SHIFT (7U)
#define WM8960_RINVOL_RINMUTE_SET(x) (((uint16_t)(x) << WM8960_RINVOL_RINMUTE_SHIFT) & WM8960_RINVOL_RINMUTE_MASK)
#define WM8960_RINVOL_RINMUTE_GET(x) (((uint16_t)(x) & WM8960_RINVOL_RINMUTE_MASK) >> WM8960_RINVOL_RINMUTE_SHIFT)

/*
 * RIZC (RW)
 *
 * Right Input PGA Zero Cross Detector
 * 1 = Change gain on zero cross only
 * 0 = Change gain immediately
 */
#define WM8960_RINVOL_RIZC_MASK (0x40U)
#define WM8960_RINVOL_RIZC_SHIFT (6U)
#define WM8960_RINVOL_RIZC_SET(x) (((uint16_t)(x) << WM8960_RINVOL_RIZC_SHIFT) & WM8960_RINVOL_RIZC_MASK)
#define WM8960_RINVOL_RIZC_GET(x) (((uint16_t)(x) & WM8960_RINVOL_RIZC_MASK) >> WM8960_RINVOL_RIZC_SHIFT)

/*
 * RINVOL (RW)
 *
 * Right Input PGA Volume Control
 * 111111 = +30dB
 * 111110 = +29.25dB
 * . . 0.75dB steps down to
 * 000000 = -17.25dB
 */
#define WM8960_RINVOL_RINVOL_MASK (0x3FU)
#define WM8960_RINVOL_RINVOL_SHIFT (0U)
#define WM8960_RINVOL_RINVOL_SET(x) (((uint16_t)(x) << WM8960_RINVOL_RINVOL_SHIFT) & WM8960_RINVOL_RINVOL_MASK)
#define WM8960_RINVOL_RINVOL_GET(x) (((uint16_t)(x) & WM8960_RINVOL_RINVOL_MASK) >> WM8960_RINVOL_RINVOL_SHIFT)

/* Bitfield definition for register: LOUT1 */
/*
 * OUT1VU (RW)
 *
 * Headphone Output PGA Volume Update
 * Writing a 1 to this bit will cause left and right
 * headphone output volumes to be updated
 * (LOUT1VOL and ROUT1VOL)
 */
#define WM8960_LOUT1_OUT1VU_MASK (0x100U)
#define WM8960_LOUT1_OUT1VU_SHIFT (8U)
#define WM8960_LOUT1_OUT1VU_SET(x) (((uint16_t)(x) << WM8960_LOUT1_OUT1VU_SHIFT) & WM8960_LOUT1_OUT1VU_MASK)
#define WM8960_LOUT1_OUT1VU_GET(x) (((uint16_t)(x) & WM8960_LOUT1_OUT1VU_MASK) >> WM8960_LOUT1_OUT1VU_SHIFT)

/*
 * LO1ZC (RW)
 *
 * Left Headphone Output Zero Cross Enable
 * 0 = Change gain immediately
 * 1 = Change gain on zero cross only
 */
#define WM8960_LOUT1_LO1ZC_MASK (0x80U)
#define WM8960_LOUT1_LO1ZC_SHIFT (7U)
#define WM8960_LOUT1_LO1ZC_SET(x) (((uint16_t)(x) << WM8960_LOUT1_LO1ZC_SHIFT) & WM8960_LOUT1_LO1ZC_MASK)
#define WM8960_LOUT1_LO1ZC_GET(x) (((uint16_t)(x) & WM8960_LOUT1_LO1ZC_MASK) >> WM8960_LOUT1_LO1ZC_SHIFT)

/*
 * LOUT1VOL (RW)
 *
 * LOUT1 Volume
 * 1111111 = +6dB
 * … 1dB steps down to
 * 0110000 = -73dB
 * 0101111 to 0000000 = Analogue MUTE
 */
#define WM8960_LOUT1_LOUT1VOL_MASK (0x7FU)
#define WM8960_LOUT1_LOUT1VOL_SHIFT (0U)
#define WM8960_LOUT1_LOUT1VOL_SET(x) (((uint16_t)(x) << WM8960_LOUT1_LOUT1VOL_SHIFT) & WM8960_LOUT1_LOUT1VOL_MASK)
#define WM8960_LOUT1_LOUT1VOL_GET(x) (((uint16_t)(x) & WM8960_LOUT1_LOUT1VOL_MASK) >> WM8960_LOUT1_LOUT1VOL_SHIFT)

/* Bitfield definition for register: ROUT1 */
/*
 * OUT1VU (RW)
 *
 * Headphone Output PGA Volume Update
 * Writing a 1 to this bit will cause left and right
 * headphone output volumes to be updated
 * (LOUT1VOL and ROUT1VOL)
 */
#define WM8960_ROUT1_OUT1VU_MASK (0x100U)
#define WM8960_ROUT1_OUT1VU_SHIFT (8U)
#define WM8960_ROUT1_OUT1VU_SET(x) (((uint16_t)(x) << WM8960_ROUT1_OUT1VU_SHIFT) & WM8960_ROUT1_OUT1VU_MASK)
#define WM8960_ROUT1_OUT1VU_GET(x) (((uint16_t)(x) & WM8960_ROUT1_OUT1VU_MASK) >> WM8960_ROUT1_OUT1VU_SHIFT)

/*
 * RO1ZC (RW)
 *
 * Right Headphone Output Zero Cross Enable
 * 0 = Change gain immediately
 * 1 = Change gain on zero cross only
 */
#define WM8960_ROUT1_RO1ZC_MASK (0x80U)
#define WM8960_ROUT1_RO1ZC_SHIFT (7U)
#define WM8960_ROUT1_RO1ZC_SET(x) (((uint16_t)(x) << WM8960_ROUT1_RO1ZC_SHIFT) & WM8960_ROUT1_RO1ZC_MASK)
#define WM8960_ROUT1_RO1ZC_GET(x) (((uint16_t)(x) & WM8960_ROUT1_RO1ZC_MASK) >> WM8960_ROUT1_RO1ZC_SHIFT)

/*
 * ROUT1VOL (RW)
 *
 * ROUT1 Volume
 * 1111111 = +6dB
 * … 1dB steps down to
 * 0110000 = -73dB
 * 0101111 to 0000000 = Analogue MUTE
 */
#define WM8960_ROUT1_ROUT1VOL_MASK (0x7FU)
#define WM8960_ROUT1_ROUT1VOL_SHIFT (0U)
#define WM8960_ROUT1_ROUT1VOL_SET(x) (((uint16_t)(x) << WM8960_ROUT1_ROUT1VOL_SHIFT) & WM8960_ROUT1_ROUT1VOL_MASK)
#define WM8960_ROUT1_ROUT1VOL_GET(x) (((uint16_t)(x) & WM8960_ROUT1_ROUT1VOL_MASK) >> WM8960_ROUT1_ROUT1VOL_SHIFT)

/* Bitfield definition for register: CLOCK1 */
/*
 * ADCDIV (RW)
 *
 * ADC Sample rate divider (Also determines
 * ADCLRC in master mode)
 * 000 = SYSCLK / (1.0 * 256)
 * 001 = SYSCLK / (1.5 * 256)
 * 010 = SYSCLK / (2 * 256)
 * 011 = SYSCLK / (3 * 256)
 * 100 = SYSCLK / (4 * 256)
 * 101 = SYSCLK / (5.5 * 256)
 * 110 = SYSCLK / (6 * 256)
 * 111 = Reserved
 */
#define WM8960_CLOCK1_ADCDIV_MASK (0x1C0U)
#define WM8960_CLOCK1_ADCDIV_SHIFT (6U)
#define WM8960_CLOCK1_ADCDIV_SET(x) (((uint16_t)(x) << WM8960_CLOCK1_ADCDIV_SHIFT) & WM8960_CLOCK1_ADCDIV_MASK)
#define WM8960_CLOCK1_ADCDIV_GET(x) (((uint16_t)(x) & WM8960_CLOCK1_ADCDIV_MASK) >> WM8960_CLOCK1_ADCDIV_SHIFT)

/*
 * DACDIV (RW)
 *
 * DAC Sample rate divider (Also determines
 * DACLRC in master mode)
 * 000 = SYSCLK / (1.0 * 256)
 * 001 = SYSCLK / (1.5 * 256)
 * 010 = SYSCLK / (2 * 256)
 * 011 = SYSCLK / (3 * 256)
 * 100 = SYSCLK / (4 * 256)
 * 101 = SYSCLK / (5.5 * 256)
 * 110 = SYSCLK / (6 * 256)
 * 111 = Reserved
 */
#define WM8960_CLOCK1_DACDIV_MASK (0x38U)
#define WM8960_CLOCK1_DACDIV_SHIFT (3U)
#define WM8960_CLOCK1_DACDIV_SET(x) (((uint16_t)(x) << WM8960_CLOCK1_DACDIV_SHIFT) & WM8960_CLOCK1_DACDIV_MASK)
#define WM8960_CLOCK1_DACDIV_GET(x) (((uint16_t)(x) & WM8960_CLOCK1_DACDIV_MASK) >> WM8960_CLOCK1_DACDIV_SHIFT)

/*
 * SYSCLKDIV (RW)
 *
 * SYSCLK Pre-divider. Clock source (MCLK or
 * PLL output) will be divided by this value to
 * generate SYSCLK.
 * 00 = Divide SYSCLK by 1
 * 01 = Reserved
 * 10 = Divide SYSCLK by 2
 * 11 = Reserved
 */
#define WM8960_CLOCK1_SYSCLKDIV_MASK (0x6U)
#define WM8960_CLOCK1_SYSCLKDIV_SHIFT (1U)
#define WM8960_CLOCK1_SYSCLKDIV_SET(x) (((uint16_t)(x) << WM8960_CLOCK1_SYSCLKDIV_SHIFT) & WM8960_CLOCK1_SYSCLKDIV_MASK)
#define WM8960_CLOCK1_SYSCLKDIV_GET(x) (((uint16_t)(x) & WM8960_CLOCK1_SYSCLKDIV_MASK) >> WM8960_CLOCK1_SYSCLKDIV_SHIFT)

/*
 * CLKSEL (RW)
 *
 * SYSCLK Selection
 * 0 = SYSCLK derived from MCLK
 * 1 = SYSCLK derived from PLL output
 */
#define WM8960_CLOCK1_CLKSEL_MASK (0x1U)
#define WM8960_CLOCK1_CLKSEL_SHIFT (0U)
#define WM8960_CLOCK1_CLKSEL_SET(x) (((uint16_t)(x) << WM8960_CLOCK1_CLKSEL_SHIFT) & WM8960_CLOCK1_CLKSEL_MASK)
#define WM8960_CLOCK1_CLKSEL_GET(x) (((uint16_t)(x) & WM8960_CLOCK1_CLKSEL_MASK) >> WM8960_CLOCK1_CLKSEL_SHIFT)

/* Bitfield definition for register: DACCTL1 */
/*
 * DACDIV2 (RW)
 *
 * DAC 6dB Attenuate Enable
 * 0 = Disabled (0dB)
 * 1 = -6dB Enabled
 */
#define WM8960_DACCTL1_DACDIV2_MASK (0x80U)
#define WM8960_DACCTL1_DACDIV2_SHIFT (7U)
#define WM8960_DACCTL1_DACDIV2_SET(x) (((uint16_t)(x) << WM8960_DACCTL1_DACDIV2_SHIFT) & WM8960_DACCTL1_DACDIV2_MASK)
#define WM8960_DACCTL1_DACDIV2_GET(x) (((uint16_t)(x) & WM8960_DACCTL1_DACDIV2_MASK) >> WM8960_DACCTL1_DACDIV2_SHIFT)

/*
 * ADCPOL (RW)
 *
 * ADC polarity control:
 * 00 = Polarity not inverted
 * 01 = ADC L inverted
 * 10 = ADC R inverted
 * 11 = ADC L and R inverted
 */
#define WM8960_DACCTL1_ADCPOL_MASK (0x60U)
#define WM8960_DACCTL1_ADCPOL_SHIFT (5U)
#define WM8960_DACCTL1_ADCPOL_SET(x) (((uint16_t)(x) << WM8960_DACCTL1_ADCPOL_SHIFT) & WM8960_DACCTL1_ADCPOL_MASK)
#define WM8960_DACCTL1_ADCPOL_GET(x) (((uint16_t)(x) & WM8960_DACCTL1_ADCPOL_MASK) >> WM8960_DACCTL1_ADCPOL_SHIFT)

/*
 * DACMU (RW)
 *
 * DAC Digital Soft Mute
 * 1 = Mute
 * 0 = No mute (signal active)
 */
#define WM8960_DACCTL1_DACMU_MASK (0x8U)
#define WM8960_DACCTL1_DACMU_SHIFT (3U)
#define WM8960_DACCTL1_DACMU_SET(x) (((uint16_t)(x) << WM8960_DACCTL1_DACMU_SHIFT) & WM8960_DACCTL1_DACMU_MASK)
#define WM8960_DACCTL1_DACMU_GET(x) (((uint16_t)(x) & WM8960_DACCTL1_DACMU_MASK) >> WM8960_DACCTL1_DACMU_SHIFT)

/*
 * DEEMPH (RW)
 *
 * De-emphasis Control
 * 11 = 48kHz sample rate
 * 10 = 44.1kHz sample rate
 * 01 = 32kHz sample rate
 * 00 = No de-emphasis
 */
#define WM8960_DACCTL1_DEEMPH_MASK (0x6U)
#define WM8960_DACCTL1_DEEMPH_SHIFT (1U)
#define WM8960_DACCTL1_DEEMPH_SET(x) (((uint16_t)(x) << WM8960_DACCTL1_DEEMPH_SHIFT) & WM8960_DACCTL1_DEEMPH_MASK)
#define WM8960_DACCTL1_DEEMPH_GET(x) (((uint16_t)(x) & WM8960_DACCTL1_DEEMPH_MASK) >> WM8960_DACCTL1_DEEMPH_SHIFT)

/*
 * ADCHPD (RW)
 *
 * ADC High Pass Filter Disable
 * 0 = Enable high pass filter on left and right channels
 * 1 = Disable high pass filter on left and right channels
 */
#define WM8960_DACCTL1_ADCHPD_MASK (0x1U)
#define WM8960_DACCTL1_ADCHPD_SHIFT (0U)
#define WM8960_DACCTL1_ADCHPD_SET(x) (((uint16_t)(x) << WM8960_DACCTL1_ADCHPD_SHIFT) & WM8960_DACCTL1_ADCHPD_MASK)
#define WM8960_DACCTL1_ADCHPD_GET(x) (((uint16_t)(x) & WM8960_DACCTL1_ADCHPD_MASK) >> WM8960_DACCTL1_ADCHPD_SHIFT)

/* Bitfield definition for register: DACCTL2 */
/*
 * DACPOL (RW)
 *
 * DAC polarity control:
 * 00 = Polarity not inverted
 * 01 = DAC L inverted
 * 10 = DAC R inverted
 * 11 = DAC L and R inverted
 */
#define WM8960_DACCTL2_DACPOL_MASK (0x60U)
#define WM8960_DACCTL2_DACPOL_SHIFT (5U)
#define WM8960_DACCTL2_DACPOL_SET(x) (((uint16_t)(x) << WM8960_DACCTL2_DACPOL_SHIFT) & WM8960_DACCTL2_DACPOL_MASK)
#define WM8960_DACCTL2_DACPOL_GET(x) (((uint16_t)(x) & WM8960_DACCTL2_DACPOL_MASK) >> WM8960_DACCTL2_DACPOL_SHIFT)

/*
 * DACSMM (RW)
 *
 * DAC Soft Mute Mode
 * 0 = Disabling soft-mute (DACMU=0) will cause
 * the volume to change immediately to the
 * LDACVOL / RDACVOL settings
 * 1 = Disabling soft-mute (DACMU=0) will cause
 * the volume to ramp up gradually to the
 * LDACVOL / RDACVOL settings
 */
#define WM8960_DACCTL2_DACSMM_MASK (0x8U)
#define WM8960_DACCTL2_DACSMM_SHIFT (3U)
#define WM8960_DACCTL2_DACSMM_SET(x) (((uint16_t)(x) << WM8960_DACCTL2_DACSMM_SHIFT) & WM8960_DACCTL2_DACSMM_MASK)
#define WM8960_DACCTL2_DACSMM_GET(x) (((uint16_t)(x) & WM8960_DACCTL2_DACSMM_MASK) >> WM8960_DACCTL2_DACSMM_SHIFT)

/*
 * DACMR (RW)
 *
 * DAC Soft Mute Ramp Rate
 * 0 = Fast ramp (24kHz at fs=48k, providing
 * maximum delay of 10.7ms)
 * 1 = Slow ramp (1.5kHz at fs=48k, providing
 * maximum delay of 171ms)
 */
#define WM8960_DACCTL2_DACMR_MASK (0x4U)
#define WM8960_DACCTL2_DACMR_SHIFT (2U)
#define WM8960_DACCTL2_DACMR_SET(x) (((uint16_t)(x) << WM8960_DACCTL2_DACMR_SHIFT) & WM8960_DACCTL2_DACMR_MASK)
#define WM8960_DACCTL2_DACMR_GET(x) (((uint16_t)(x) & WM8960_DACCTL2_DACMR_MASK) >> WM8960_DACCTL2_DACMR_SHIFT)

/*
 * DACSLOPE (RW)
 *
 * Selects DAC filter characteristics
 * 0 = Normal mode
 * 1 = Sloping stopband
 */
#define WM8960_DACCTL2_DACSLOPE_MASK (0x2U)
#define WM8960_DACCTL2_DACSLOPE_SHIFT (1U)
#define WM8960_DACCTL2_DACSLOPE_SET(x) (((uint16_t)(x) << WM8960_DACCTL2_DACSLOPE_SHIFT) & WM8960_DACCTL2_DACSLOPE_MASK)
#define WM8960_DACCTL2_DACSLOPE_GET(x) (((uint16_t)(x) & WM8960_DACCTL2_DACSLOPE_MASK) >> WM8960_DACCTL2_DACSLOPE_SHIFT)

/* Bitfield definition for register: IFACE1 */
/*
 * ALRSWAP (RW)
 *
 * Left/Right ADC Channel Swap
 * 1 = Swap left and right ADC data in audio
 * interface
 * 0 = Output left and right data as normal
 */
#define WM8960_IFACE1_ALRSWAP_MASK (0x100U)
#define WM8960_IFACE1_ALRSWAP_SHIFT (8U)
#define WM8960_IFACE1_ALRSWAP_SET(x) (((uint16_t)(x) << WM8960_IFACE1_ALRSWAP_SHIFT) & WM8960_IFACE1_ALRSWAP_MASK)
#define WM8960_IFACE1_ALRSWAP_GET(x) (((uint16_t)(x) & WM8960_IFACE1_ALRSWAP_MASK) >> WM8960_IFACE1_ALRSWAP_SHIFT)

/*
 * BCLKINV (RW)
 *
 * BCLK invert bit (for master and slave modes)
 * 0 = BCLK not inverted
 * 1 = BCLK inverted
 */
#define WM8960_IFACE1_BCLKINV_MASK (0x80U)
#define WM8960_IFACE1_BCLKINV_SHIFT (7U)
#define WM8960_IFACE1_BCLKINV_SET(x) (((uint16_t)(x) << WM8960_IFACE1_BCLKINV_SHIFT) & WM8960_IFACE1_BCLKINV_MASK)
#define WM8960_IFACE1_BCLKINV_GET(x) (((uint16_t)(x) & WM8960_IFACE1_BCLKINV_MASK) >> WM8960_IFACE1_BCLKINV_SHIFT)

/*
 * MS (RW)
 *
 * Master / Slave Mode Control
 * 0 = Enable slave mode
 * 1 = Enable master mode
 */
#define WM8960_IFACE1_MS_MASK (0x40U)
#define WM8960_IFACE1_MS_SHIFT (6U)
#define WM8960_IFACE1_MS_SET(x) (((uint16_t)(x) << WM8960_IFACE1_MS_SHIFT) & WM8960_IFACE1_MS_MASK)
#define WM8960_IFACE1_MS_GET(x) (((uint16_t)(x) & WM8960_IFACE1_MS_MASK) >> WM8960_IFACE1_MS_SHIFT)

/*
 * DLRSWAP (RW)
 *
 * Left/Right DAC Channel Swap
 * 0 = Output left and right data as normal
 * 1 = Swap left and right DAC data in audio interface
 */
#define WM8960_IFACE1_DLRSWAP_MASK (0x20U)
#define WM8960_IFACE1_DLRSWAP_SHIFT (5U)
#define WM8960_IFACE1_DLRSWAP_SET(x) (((uint16_t)(x) << WM8960_IFACE1_DLRSWAP_SHIFT) & WM8960_IFACE1_DLRSWAP_MASK)
#define WM8960_IFACE1_DLRSWAP_GET(x) (((uint16_t)(x) & WM8960_IFACE1_DLRSWAP_MASK) >> WM8960_IFACE1_DLRSWAP_SHIFT)

/*
 * LRP (RW)
 *
 * Right, left and I2S modes – LRCLK polarity
 * 0 = normal LRCLK polarity
 * 1 = invert LRCLK polarity
 * DSP Mode – mode A/B select
 * 0 = MSB is available on 2nd BCLK rising edge after LRC rising edge (mode A)
 * 1 = MSB is available on 1st BCLK rising edge after LRC rising edge (mode B)
 */
#define WM8960_IFACE1_LRP_MASK (0x10U)
#define WM8960_IFACE1_LRP_SHIFT (4U)
#define WM8960_IFACE1_LRP_SET(x) (((uint16_t)(x) << WM8960_IFACE1_LRP_SHIFT) & WM8960_IFACE1_LRP_MASK)
#define WM8960_IFACE1_LRP_GET(x) (((uint16_t)(x) & WM8960_IFACE1_LRP_MASK) >> WM8960_IFACE1_LRP_SHIFT)

/*
 * WL (RW)
 *
 * Audio Data Word Length
 * 00 = 16 bits
 * 01 = 20 bits
 * 10 = 24 bits
 * 11 = 32 bits (see Note)
 */
#define WM8960_IFACE1_WL_MASK (0xCU)
#define WM8960_IFACE1_WL_SHIFT (2U)
#define WM8960_IFACE1_WL_SET(x) (((uint16_t)(x) << WM8960_IFACE1_WL_SHIFT) & WM8960_IFACE1_WL_MASK)
#define WM8960_IFACE1_WL_GET(x) (((uint16_t)(x) & WM8960_IFACE1_WL_MASK) >> WM8960_IFACE1_WL_SHIFT)

/*
 * FORMAT (RW)
 *
 * 00 = Right justified
 * 01 = Left justified
 * 10 = I2S Format
 * 11 = DSP Mode
 */
#define WM8960_IFACE1_FORMAT_MASK (0x3U)
#define WM8960_IFACE1_FORMAT_SHIFT (0U)
#define WM8960_IFACE1_FORMAT_SET(x) (((uint16_t)(x) << WM8960_IFACE1_FORMAT_SHIFT) & WM8960_IFACE1_FORMAT_MASK)
#define WM8960_IFACE1_FORMAT_GET(x) (((uint16_t)(x) & WM8960_IFACE1_FORMAT_MASK) >> WM8960_IFACE1_FORMAT_SHIFT)

/* Bitfield definition for register: CLOCK2 */
/*
 * DCLKDIV (RW)
 *
 * Class D switching clock divider.
 * 000 = SYSCLK / 1.5 (Not recommended)
 * 001 = SYSCLK / 2
 * 010 = SYSCLK / 3
 * 011 = SYSCLK / 4
 * 100 = SYSCLK / 6
 * 101 = SYSCLK / 8
 * 110 = SYSCLK / 12
 * 111 = SYSCLK / 16
 */
#define WM8960_CLOCK2_DCLKDIV_MASK (0x1C0U)
#define WM8960_CLOCK2_DCLKDIV_SHIFT (6U)
#define WM8960_CLOCK2_DCLKDIV_SET(x) (((uint16_t)(x) << WM8960_CLOCK2_DCLKDIV_SHIFT) & WM8960_CLOCK2_DCLKDIV_MASK)
#define WM8960_CLOCK2_DCLKDIV_GET(x) (((uint16_t)(x) & WM8960_CLOCK2_DCLKDIV_MASK) >> WM8960_CLOCK2_DCLKDIV_SHIFT)

/*
 * BCLKDIV (RW)
 *
 * BCLK Frequency (Master Mode)
 * 0000 = SYSCLK
 * 0001 = SYSCLK / 1.5
 * 0010 = SYSCLK / 2
 * 0011 = SYSCLK / 3
 * 0100 = SYSCLK / 4
 * 0101 = SYSCLK / 5.5
 * 0110 = SYSCLK / 6
 * 0111 = SYSCLK / 8
 * 1000 = SYSCLK / 11
 * 1001 = SYSCLK / 12
 * 1010 = SYSCLK / 16
 * 1011 = SYSCLK / 22
 * 1100 = SYSCLK / 24
 * 1101 to 1111 = SYSCLK / 32
 */
#define WM8960_CLOCK2_BCLKDIV_MASK (0xFU)
#define WM8960_CLOCK2_BCLKDIV_SHIFT (0U)
#define WM8960_CLOCK2_BCLKDIV_SET(x) (((uint16_t)(x) << WM8960_CLOCK2_BCLKDIV_SHIFT) & WM8960_CLOCK2_BCLKDIV_MASK)
#define WM8960_CLOCK2_BCLKDIV_GET(x) (((uint16_t)(x) & WM8960_CLOCK2_BCLKDIV_MASK) >> WM8960_CLOCK2_BCLKDIV_SHIFT)

/* Bitfield definition for register: IFACE2 */
/*
 * ALRCGPIO (RW)
 *
 * ADCLRC/GPIO1 Pin Function Select
 * 0 = ADCLRC frame clock for ADC
 * 1 = GPIO pin
 */
#define WM8960_IFACE2_ALRCGPIO_MASK (0x40U)
#define WM8960_IFACE2_ALRCGPIO_SHIFT (6U)
#define WM8960_IFACE2_ALRCGPIO_SET(x) (((uint16_t)(x) << WM8960_IFACE2_ALRCGPIO_SHIFT) & WM8960_IFACE2_ALRCGPIO_MASK)
#define WM8960_IFACE2_ALRCGPIO_GET(x) (((uint16_t)(x) & WM8960_IFACE2_ALRCGPIO_MASK) >> WM8960_IFACE2_ALRCGPIO_SHIFT)

/*
 * WL8 (RW)
 *
 * 8-Bit Word Length Select (Used with
 * companding)
 * 0 = Off
 * 1 = Device operates in 8-bit mode.
 */
#define WM8960_IFACE2_WL8_MASK (0x20U)
#define WM8960_IFACE2_WL8_SHIFT (5U)
#define WM8960_IFACE2_WL8_SET(x) (((uint16_t)(x) << WM8960_IFACE2_WL8_SHIFT) & WM8960_IFACE2_WL8_MASK)
#define WM8960_IFACE2_WL8_GET(x) (((uint16_t)(x) & WM8960_IFACE2_WL8_MASK) >> WM8960_IFACE2_WL8_SHIFT)

/*
 * DACCOMP (RW)
 *
 * DAC companding
 * 00 = off
 * 01 = reserved
 * 10 = μ-law
 * 11 = A-law
 */
#define WM8960_IFACE2_DACCOMP_MASK (0x18U)
#define WM8960_IFACE2_DACCOMP_SHIFT (3U)
#define WM8960_IFACE2_DACCOMP_SET(x) (((uint16_t)(x) << WM8960_IFACE2_DACCOMP_SHIFT) & WM8960_IFACE2_DACCOMP_MASK)
#define WM8960_IFACE2_DACCOMP_GET(x) (((uint16_t)(x) & WM8960_IFACE2_DACCOMP_MASK) >> WM8960_IFACE2_DACCOMP_SHIFT)

/*
 * ADCCOMP (RW)
 *
 * ADC companding
 * 00 = off
 * 01 = reserved
 * 10 = μ-law
 * 11 = A-law
 */
#define WM8960_IFACE2_ADCCOMP_MASK (0x6U)
#define WM8960_IFACE2_ADCCOMP_SHIFT (1U)
#define WM8960_IFACE2_ADCCOMP_SET(x) (((uint16_t)(x) << WM8960_IFACE2_ADCCOMP_SHIFT) & WM8960_IFACE2_ADCCOMP_MASK)
#define WM8960_IFACE2_ADCCOMP_GET(x) (((uint16_t)(x) & WM8960_IFACE2_ADCCOMP_MASK) >> WM8960_IFACE2_ADCCOMP_SHIFT)

/*
 * LOOPBACK (RW)
 *
 * Digital Loopback Function
 * 0 = No loopback.
 * 1 = Loopback enabled, ADC data output is fed
 * directly into DAC data input
 */
#define WM8960_IFACE2_LOOPBACK_MASK (0x1U)
#define WM8960_IFACE2_LOOPBACK_SHIFT (0U)
#define WM8960_IFACE2_LOOPBACK_SET(x) (((uint16_t)(x) << WM8960_IFACE2_LOOPBACK_SHIFT) & WM8960_IFACE2_LOOPBACK_MASK)
#define WM8960_IFACE2_LOOPBACK_GET(x) (((uint16_t)(x) & WM8960_IFACE2_LOOPBACK_MASK) >> WM8960_IFACE2_LOOPBACK_SHIFT)

/* Bitfield definition for register: LDAC */
/*
 * DACVU (RW)
 *
 * DAC Volume Update
 * Writing a 1 to this bit will cause left and right
 * DAC volumes to be updated (LDACVOL and RDACVOL)
 */
#define WM8960_LDAC_DACVU_MASK (0x100U)
#define WM8960_LDAC_DACVU_SHIFT (8U)
#define WM8960_LDAC_DACVU_SET(x) (((uint16_t)(x) << WM8960_LDAC_DACVU_SHIFT) & WM8960_LDAC_DACVU_MASK)
#define WM8960_LDAC_DACVU_GET(x) (((uint16_t)(x) & WM8960_LDAC_DACVU_MASK) >> WM8960_LDAC_DACVU_SHIFT)

/*
 * LDACVOL (RW)
 *
 * Left DAC Digital Volume Control
 * 0000 0000 = Digital Mute
 * 0000 0001 = -127dB
 * 0000 0010 = -126.5dB
 * ... 0.5dB steps up to
 * 1111 1111 = 0dB
 */
#define WM8960_LDAC_LDACVOL_MASK (0xFFU)
#define WM8960_LDAC_LDACVOL_SHIFT (0U)
#define WM8960_LDAC_LDACVOL_SET(x) (((uint16_t)(x) << WM8960_LDAC_LDACVOL_SHIFT) & WM8960_LDAC_LDACVOL_MASK)
#define WM8960_LDAC_LDACVOL_GET(x) (((uint16_t)(x) & WM8960_LDAC_LDACVOL_MASK) >> WM8960_LDAC_LDACVOL_SHIFT)

/* Bitfield definition for register: RDAC */
/*
 * DACVU (RW)
 *
 * DAC Volume Update
 * Writing a 1 to this bit will cause left and right
 * DAC volumes to be updated (LDACVOL and RDACVOL)
 */
#define WM8960_RDAC_DACVU_MASK (0x100U)
#define WM8960_RDAC_DACVU_SHIFT (8U)
#define WM8960_RDAC_DACVU_SET(x) (((uint16_t)(x) << WM8960_RDAC_DACVU_SHIFT) & WM8960_RDAC_DACVU_MASK)
#define WM8960_RDAC_DACVU_GET(x) (((uint16_t)(x) & WM8960_RDAC_DACVU_MASK) >> WM8960_RDAC_DACVU_SHIFT)

/*
 * RDACVOL (RW)
 *
 * Right DAC Digital Volume Control
 * 0000 0000 = Digital Mute
 * 0000 0001 = -127dB
 * 0000 0010 = -126.5dB
 * ... 0.5dB steps up to
 * 1111 1111 = 0dB
 */
#define WM8960_RDAC_RDACVOL_MASK (0xFFU)
#define WM8960_RDAC_RDACVOL_SHIFT (0U)
#define WM8960_RDAC_RDACVOL_SET(x) (((uint16_t)(x) << WM8960_RDAC_RDACVOL_SHIFT) & WM8960_RDAC_RDACVOL_MASK)
#define WM8960_RDAC_RDACVOL_GET(x) (((uint16_t)(x) & WM8960_RDAC_RDACVOL_MASK) >> WM8960_RDAC_RDACVOL_SHIFT)

/* Bitfield definition for register: RESET */
/*
 * RESET (RW)
 *
 * Writing to this register resets all registers to their default state.
 */
#define WM8960_RESET_RESET_MASK (0x1FFU)
#define WM8960_RESET_RESET_SHIFT (0U)
#define WM8960_RESET_RESET_SET(x) (((uint16_t)(x) << WM8960_RESET_RESET_SHIFT) & WM8960_RESET_RESET_MASK)
#define WM8960_RESET_RESET_GET(x) (((uint16_t)(x) & WM8960_RESET_RESET_MASK) >> WM8960_RESET_RESET_SHIFT)

/* Bitfield definition for register: 3D */
/*
 * 3DUC (RW)
 *
 * 3D Enhance Filter Upper Cut-Off Frequency
 * 0 = High (Recommended for fs>=32kHz)
 * 1 = Low (Recommended for fs<32kHz)
 */
#define WM8960_3D_3DUC_MASK (0x40U)
#define WM8960_3D_3DUC_SHIFT (6U)
#define WM8960_3D_3DUC_SET(x) (((uint16_t)(x) << WM8960_3D_3DUC_SHIFT) & WM8960_3D_3DUC_MASK)
#define WM8960_3D_3DUC_GET(x) (((uint16_t)(x) & WM8960_3D_3DUC_MASK) >> WM8960_3D_3DUC_SHIFT)

/*
 * 3DLC (RW)
 *
 * 3D Enhance Filter Lower Cut-Off Frequency
 * 0 = Low (Recommended for fs>=32kHz)
 * 1 = High (Recommended for fs<32kHz)
 */
#define WM8960_3D_3DLC_MASK (0x20U)
#define WM8960_3D_3DLC_SHIFT (5U)
#define WM8960_3D_3DLC_SET(x) (((uint16_t)(x) << WM8960_3D_3DLC_SHIFT) & WM8960_3D_3DLC_MASK)
#define WM8960_3D_3DLC_GET(x) (((uint16_t)(x) & WM8960_3D_3DLC_MASK) >> WM8960_3D_3DLC_SHIFT)

/*
 * 3DDEPTH (RW)
 *
 * 3D Stereo Depth
 * 0000 = 0% (minimum 3D effect)
 * 0001 = 6.67%
 * ....
 * 1110 = 93.3%
 * 1111 = 100% (maximum 3D effect)
 */
#define WM8960_3D_3DDEPTH_MASK (0x1EU)
#define WM8960_3D_3DDEPTH_SHIFT (1U)
#define WM8960_3D_3DDEPTH_SET(x) (((uint16_t)(x) << WM8960_3D_3DDEPTH_SHIFT) & WM8960_3D_3DDEPTH_MASK)
#define WM8960_3D_3DDEPTH_GET(x) (((uint16_t)(x) & WM8960_3D_3DDEPTH_MASK) >> WM8960_3D_3DDEPTH_SHIFT)

/*
 * 3DEN (RW)
 *
 * 3D Stereo Enhancement Enable
 * 0 = Disabled
 * 1 = Enabled
 */
#define WM8960_3D_3DEN_MASK (0x1U)
#define WM8960_3D_3DEN_SHIFT (0U)
#define WM8960_3D_3DEN_SET(x) (((uint16_t)(x) << WM8960_3D_3DEN_SHIFT) & WM8960_3D_3DEN_MASK)
#define WM8960_3D_3DEN_GET(x) (((uint16_t)(x) & WM8960_3D_3DEN_MASK) >> WM8960_3D_3DEN_SHIFT)

/* Bitfield definition for register: ALC1 */
/*
 * ALCSEL (RW)
 *
 * ALC Function Select
 * 00 = ALC off (PGA gain set by register)
 * 01 = Right channel only
 * 10 = Left channel only
 * 11 = Stereo (PGA registers unused) Note:
 * ensure that LINVOL and RINVOL settings
 * (reg. 0 and 1) are the same before entering this mode.
 */
#define WM8960_ALC1_ALCSEL_MASK (0x180U)
#define WM8960_ALC1_ALCSEL_SHIFT (7U)
#define WM8960_ALC1_ALCSEL_SET(x) (((uint16_t)(x) << WM8960_ALC1_ALCSEL_SHIFT) & WM8960_ALC1_ALCSEL_MASK)
#define WM8960_ALC1_ALCSEL_GET(x) (((uint16_t)(x) & WM8960_ALC1_ALCSEL_MASK) >> WM8960_ALC1_ALCSEL_SHIFT)

/*
 * MAXGAIN (RW)
 *
 * Set Maximum Gain of PGA (During ALC
 * operation)
 * 111 : +30dB
 * 110 : +24dB
 * ….(-6dB steps)
 * 001 : -6dB
 * 000 : -12dB
 */
#define WM8960_ALC1_MAXGAIN_MASK (0x70U)
#define WM8960_ALC1_MAXGAIN_SHIFT (4U)
#define WM8960_ALC1_MAXGAIN_SET(x) (((uint16_t)(x) << WM8960_ALC1_MAXGAIN_SHIFT) & WM8960_ALC1_MAXGAIN_MASK)
#define WM8960_ALC1_MAXGAIN_GET(x) (((uint16_t)(x) & WM8960_ALC1_MAXGAIN_MASK) >> WM8960_ALC1_MAXGAIN_SHIFT)

/*
 * ALCL (RW)
 *
 * ALC Target (Sets signal level at ADC input)
 * 0000 = -22.5dB FS
 * 0001 = -21.0dB FS
 * … (1.5dB steps)
 * 1101 = -3.0dB FS
 * 1110 = -1.5dB FS
 * 1111 = -1.5dB FS
 */
#define WM8960_ALC1_ALCL_MASK (0xFU)
#define WM8960_ALC1_ALCL_SHIFT (0U)
#define WM8960_ALC1_ALCL_SET(x) (((uint16_t)(x) << WM8960_ALC1_ALCL_SHIFT) & WM8960_ALC1_ALCL_MASK)
#define WM8960_ALC1_ALCL_GET(x) (((uint16_t)(x) & WM8960_ALC1_ALCL_MASK) >> WM8960_ALC1_ALCL_SHIFT)

/* Bitfield definition for register: ALC2 */
/*
 * MINGAIN (RW)
 *
 * Set Minimum Gain of PGA (During ALC
 * operation)
 * 000 = -17.25dB
 * 001 = -11.25dB
 * 010 = -5.25dB
 * 011 = +0.75dB
 * 100 = +6.75dB
 * 101 = +12.75dB
 * 110 = +18.75dB
 * 111 = +24.75dB
 */
#define WM8960_ALC2_MINGAIN_MASK (0x70U)
#define WM8960_ALC2_MINGAIN_SHIFT (4U)
#define WM8960_ALC2_MINGAIN_SET(x) (((uint16_t)(x) << WM8960_ALC2_MINGAIN_SHIFT) & WM8960_ALC2_MINGAIN_MASK)
#define WM8960_ALC2_MINGAIN_GET(x) (((uint16_t)(x) & WM8960_ALC2_MINGAIN_MASK) >> WM8960_ALC2_MINGAIN_SHIFT)

/*
 * HLD (RW)
 *
 * ALC hold time before gain is increased.
 * 0000 = 0ms
 * 0001 = 2.67ms
 * 0010 = 5.33ms
 * … (time doubles with every step)
 * 1111 = 43.691s
 */
#define WM8960_ALC2_HLD_MASK (0xFU)
#define WM8960_ALC2_HLD_SHIFT (0U)
#define WM8960_ALC2_HLD_SET(x) (((uint16_t)(x) << WM8960_ALC2_HLD_SHIFT) & WM8960_ALC2_HLD_MASK)
#define WM8960_ALC2_HLD_GET(x) (((uint16_t)(x) & WM8960_ALC2_HLD_MASK) >> WM8960_ALC2_HLD_SHIFT)

/* Bitfield definition for register: ALC3 */
/*
 * ALCMODE (RW)
 *
 * Determines the ALC mode of operation:
 * 0 = ALC mode
 * 1 = Limiter mode
 */
#define WM8960_ALC3_ALCMODE_MASK (0x100U)
#define WM8960_ALC3_ALCMODE_SHIFT (8U)
#define WM8960_ALC3_ALCMODE_SET(x) (((uint16_t)(x) << WM8960_ALC3_ALCMODE_SHIFT) & WM8960_ALC3_ALCMODE_MASK)
#define WM8960_ALC3_ALCMODE_GET(x) (((uint16_t)(x) & WM8960_ALC3_ALCMODE_MASK) >> WM8960_ALC3_ALCMODE_SHIFT)

/*
 * DCY (RW)
 *
 * ALC decay (gain ramp-up) time
 * 0000 = 24ms
 * 0001 = 48ms
 * 0010 = 96ms
 * … (time doubles with every step)
 * 1010 or higher = 24.58s
 */
#define WM8960_ALC3_DCY_MASK (0xF0U)
#define WM8960_ALC3_DCY_SHIFT (4U)
#define WM8960_ALC3_DCY_SET(x) (((uint16_t)(x) << WM8960_ALC3_DCY_SHIFT) & WM8960_ALC3_DCY_MASK)
#define WM8960_ALC3_DCY_GET(x) (((uint16_t)(x) & WM8960_ALC3_DCY_MASK) >> WM8960_ALC3_DCY_SHIFT)

/*
 * ATK (RW)
 *
 * ALC attack (gain ramp-down) time
 * 0000 = 6ms
 * 0001 = 12ms
 * 0010 = 24ms
 * … (time doubles with every step)
 * 1010 or higher = 6.14s
 */
#define WM8960_ALC3_ATK_MASK (0xFU)
#define WM8960_ALC3_ATK_SHIFT (0U)
#define WM8960_ALC3_ATK_SET(x) (((uint16_t)(x) << WM8960_ALC3_ATK_SHIFT) & WM8960_ALC3_ATK_MASK)
#define WM8960_ALC3_ATK_GET(x) (((uint16_t)(x) & WM8960_ALC3_ATK_MASK) >> WM8960_ALC3_ATK_SHIFT)

/* Bitfield definition for register: NOISEG */
/*
 * NGTH (RW)
 *
 * Noise gate threshold
 * 00000 -76.5dBfs
 * 00001 -75dBfs
 * … 1.5 dB steps
 * 11110 -31.5dBfs
 * 11111 -30dBfs
 */
#define WM8960_NOISEG_NGTH_MASK (0xF8U)
#define WM8960_NOISEG_NGTH_SHIFT (3U)
#define WM8960_NOISEG_NGTH_SET(x) (((uint16_t)(x) << WM8960_NOISEG_NGTH_SHIFT) & WM8960_NOISEG_NGTH_MASK)
#define WM8960_NOISEG_NGTH_GET(x) (((uint16_t)(x) & WM8960_NOISEG_NGTH_MASK) >> WM8960_NOISEG_NGTH_SHIFT)

/*
 * NGAT (RW)
 *
 * Noise gate function enable
 * 0 = disable
 * 1 = enable
 */
#define WM8960_NOISEG_NGAT_MASK (0x1U)
#define WM8960_NOISEG_NGAT_SHIFT (0U)
#define WM8960_NOISEG_NGAT_SET(x) (((uint16_t)(x) << WM8960_NOISEG_NGAT_SHIFT) & WM8960_NOISEG_NGAT_MASK)
#define WM8960_NOISEG_NGAT_GET(x) (((uint16_t)(x) & WM8960_NOISEG_NGAT_MASK) >> WM8960_NOISEG_NGAT_SHIFT)

/* Bitfield definition for register: LADC */
/*
 * ADCVU (RW)
 *
 * ADC Volume Update
 * Writing a 1 to this bit will cause left and right
 * ADC volumes to be updated (LADCVOL and
 * RADCVOL)
 */
#define WM8960_LADC_ADCVU_MASK (0x100U)
#define WM8960_LADC_ADCVU_SHIFT (8U)
#define WM8960_LADC_ADCVU_SET(x) (((uint16_t)(x) << WM8960_LADC_ADCVU_SHIFT) & WM8960_LADC_ADCVU_MASK)
#define WM8960_LADC_ADCVU_GET(x) (((uint16_t)(x) & WM8960_LADC_ADCVU_MASK) >> WM8960_LADC_ADCVU_SHIFT)

/*
 * LADCVOL (RW)
 *
 * Left ADC Digital Volume Control
 * 0000 0000 = Digital Mute
 * 0000 0001 = -97dB
 * 0000 0010 = -96.5dB
 * ... 0.5dB steps up to
 * 1111 1111 = +30dB
 */
#define WM8960_LADC_LADCVOL_MASK (0xFFU)
#define WM8960_LADC_LADCVOL_SHIFT (0U)
#define WM8960_LADC_LADCVOL_SET(x) (((uint16_t)(x) << WM8960_LADC_LADCVOL_SHIFT) & WM8960_LADC_LADCVOL_MASK)
#define WM8960_LADC_LADCVOL_GET(x) (((uint16_t)(x) & WM8960_LADC_LADCVOL_MASK) >> WM8960_LADC_LADCVOL_SHIFT)

/* Bitfield definition for register: RADC */
/*
 * ADCVU (RW)
 *
 * ADC Volume Update
 * Writing a 1 to this bit will cause left and right
 * ADC volumes to be updated (LADCVOL and RADCVOL)
 */
#define WM8960_RADC_ADCVU_MASK (0x100U)
#define WM8960_RADC_ADCVU_SHIFT (8U)
#define WM8960_RADC_ADCVU_SET(x) (((uint16_t)(x) << WM8960_RADC_ADCVU_SHIFT) & WM8960_RADC_ADCVU_MASK)
#define WM8960_RADC_ADCVU_GET(x) (((uint16_t)(x) & WM8960_RADC_ADCVU_MASK) >> WM8960_RADC_ADCVU_SHIFT)

/*
 * RADCVOL (RW)
 *
 * Right ADC Digital Volume Control
 * 0000 0000 = Digital Mute
 * 0000 0001 = -97dB
 * 0000 0010 = -96.5dB
 * ... 0.5dB steps up to
 * 1111 1111 = +30dB
 */
#define WM8960_RADC_RADCVOL_MASK (0xFFU)
#define WM8960_RADC_RADCVOL_SHIFT (0U)
#define WM8960_RADC_RADCVOL_SET(x) (((uint16_t)(x) << WM8960_RADC_RADCVOL_SHIFT) & WM8960_RADC_RADCVOL_MASK)
#define WM8960_RADC_RADCVOL_GET(x) (((uint16_t)(x) & WM8960_RADC_RADCVOL_MASK) >> WM8960_RADC_RADCVOL_SHIFT)

/* Bitfield definition for register: ADDCTL1 */
/*
 * TSDEN (RW)
 *
 * Thermal Shutdown Enable
 * 0 = Thermal shutdown disabled
 * 1 = Thermal shutdown enabled
 * (TSENSEN must be enabled for this function to work)
 */
#define WM8960_ADDCTL1_TSDEN_MASK (0x100U)
#define WM8960_ADDCTL1_TSDEN_SHIFT (8U)
#define WM8960_ADDCTL1_TSDEN_SET(x) (((uint16_t)(x) << WM8960_ADDCTL1_TSDEN_SHIFT) & WM8960_ADDCTL1_TSDEN_MASK)
#define WM8960_ADDCTL1_TSDEN_GET(x) (((uint16_t)(x) & WM8960_ADDCTL1_TSDEN_MASK) >> WM8960_ADDCTL1_TSDEN_SHIFT)

/*
 * VSEL (RW)
 *
 * Analogue Bias Optimisation
 * 00 = Reserved
 * 01 = Increased bias current optimized for
 * AVDD=2.7V
 * 1X = Lowest bias current, optimized for
 * AVDD=3.3V
 */
#define WM8960_ADDCTL1_VSEL_MASK (0xC0U)
#define WM8960_ADDCTL1_VSEL_SHIFT (6U)
#define WM8960_ADDCTL1_VSEL_SET(x) (((uint16_t)(x) << WM8960_ADDCTL1_VSEL_SHIFT) & WM8960_ADDCTL1_VSEL_MASK)
#define WM8960_ADDCTL1_VSEL_GET(x) (((uint16_t)(x) & WM8960_ADDCTL1_VSEL_MASK) >> WM8960_ADDCTL1_VSEL_SHIFT)

/*
 * DMONOMIX (RW)
 *
 * DAC Mono Mix
 * 0 = Stereo
 * 1 = Mono (Mono MIX output on enabled DACs
 */
#define WM8960_ADDCTL1_DMONOMIX_MASK (0x10U)
#define WM8960_ADDCTL1_DMONOMIX_SHIFT (4U)
#define WM8960_ADDCTL1_DMONOMIX_SET(x) (((uint16_t)(x) << WM8960_ADDCTL1_DMONOMIX_SHIFT) & WM8960_ADDCTL1_DMONOMIX_MASK)
#define WM8960_ADDCTL1_DMONOMIX_GET(x) (((uint16_t)(x) & WM8960_ADDCTL1_DMONOMIX_MASK) >> WM8960_ADDCTL1_DMONOMIX_SHIFT)

/*
 * DATSEL (RW)
 *
 * ADC Data Output Select
 * 00: left data = left ADC; right data =right ADC
 * 01: left data = left ADC; right data = left ADC
 * 10: left data = right ADC; right data =right ADC
 * 11: left data = right ADC; right data = left ADC
 */
#define WM8960_ADDCTL1_DATSEL_MASK (0xCU)
#define WM8960_ADDCTL1_DATSEL_SHIFT (2U)
#define WM8960_ADDCTL1_DATSEL_SET(x) (((uint16_t)(x) << WM8960_ADDCTL1_DATSEL_SHIFT) & WM8960_ADDCTL1_DATSEL_MASK)
#define WM8960_ADDCTL1_DATSEL_GET(x) (((uint16_t)(x) & WM8960_ADDCTL1_DATSEL_MASK) >> WM8960_ADDCTL1_DATSEL_SHIFT)

/*
 * TOCLKSEL (RW)
 *
 * Slow Clock Select (Used for volume update
 * timeouts and for jack detect debounce)
 * 0 = SYSCLK / 221 (Slower Response)
 * 1 = SYSCLK / 219 (Faster Response)
 */
#define WM8960_ADDCTL1_TOCLKSEL_MASK (0x2U)
#define WM8960_ADDCTL1_TOCLKSEL_SHIFT (1U)
#define WM8960_ADDCTL1_TOCLKSEL_SET(x) (((uint16_t)(x) << WM8960_ADDCTL1_TOCLKSEL_SHIFT) & WM8960_ADDCTL1_TOCLKSEL_MASK)
#define WM8960_ADDCTL1_TOCLKSEL_GET(x) (((uint16_t)(x) & WM8960_ADDCTL1_TOCLKSEL_MASK) >> WM8960_ADDCTL1_TOCLKSEL_SHIFT)

/*
 * TOEN (RW)
 *
 * Enables Slow Clock for Volume Update Timeout
 * and Jack Detect Debounce
 * 0 = Slow clock disabled
 * 1 = Slow clock enabled
 */
#define WM8960_ADDCTL1_TOEN_MASK (0x1U)
#define WM8960_ADDCTL1_TOEN_SHIFT (0U)
#define WM8960_ADDCTL1_TOEN_SET(x) (((uint16_t)(x) << WM8960_ADDCTL1_TOEN_SHIFT) & WM8960_ADDCTL1_TOEN_MASK)
#define WM8960_ADDCTL1_TOEN_GET(x) (((uint16_t)(x) & WM8960_ADDCTL1_TOEN_MASK) >> WM8960_ADDCTL1_TOEN_SHIFT)

/* Bitfield definition for register: ADDCTL2 */
/*
 * HPSWEN (RW)
 *
 * Headphone Switch Enable
 * 0 = Headphone switch disabled
 * 1 = Headphone switch enabled
 */
#define WM8960_ADDCTL2_HPSWEN_MASK (0x40U)
#define WM8960_ADDCTL2_HPSWEN_SHIFT (6U)
#define WM8960_ADDCTL2_HPSWEN_SET(x) (((uint16_t)(x) << WM8960_ADDCTL2_HPSWEN_SHIFT) & WM8960_ADDCTL2_HPSWEN_MASK)
#define WM8960_ADDCTL2_HPSWEN_GET(x) (((uint16_t)(x) & WM8960_ADDCTL2_HPSWEN_MASK) >> WM8960_ADDCTL2_HPSWEN_SHIFT)

/*
 * HPSWPOL (RW)
 *
 * Headphone Switch Polarity
 * 0 = HPDETECT high = headphone
 * 1 = HPDETECT high = speaker
 */
#define WM8960_ADDCTL2_HPSWPOL_MASK (0x20U)
#define WM8960_ADDCTL2_HPSWPOL_SHIFT (5U)
#define WM8960_ADDCTL2_HPSWPOL_SET(x) (((uint16_t)(x) << WM8960_ADDCTL2_HPSWPOL_SHIFT) & WM8960_ADDCTL2_HPSWPOL_MASK)
#define WM8960_ADDCTL2_HPSWPOL_GET(x) (((uint16_t)(x) & WM8960_ADDCTL2_HPSWPOL_MASK) >> WM8960_ADDCTL2_HPSWPOL_SHIFT)

/*
 * TRIS (RW)
 *
 * Tristates ADCDAT and switches ADCLRC,
 * DACLRC and BCLK to inputs.
 * 0 = ADCDAT is an output; ADCLRC, DACLRC
 * and BCLK are inputs (slave mode) or outputs
 * (master mode)
 * 1 = ADCDAT is tristated; DACLRC and BCLK
 * are inputs; ADCLRC is an input (when not
 * configured as a GPIO)
 */
#define WM8960_ADDCTL2_TRIS_MASK (0x8U)
#define WM8960_ADDCTL2_TRIS_SHIFT (3U)
#define WM8960_ADDCTL2_TRIS_SET(x) (((uint16_t)(x) << WM8960_ADDCTL2_TRIS_SHIFT) & WM8960_ADDCTL2_TRIS_MASK)
#define WM8960_ADDCTL2_TRIS_GET(x) (((uint16_t)(x) & WM8960_ADDCTL2_TRIS_MASK) >> WM8960_ADDCTL2_TRIS_SHIFT)

/*
 * LRCM (RW)
 *
 * Selects disable mode for ADCLRC and DACLRC
 * (Master mode)
 * 0 = ADCLRC disabled when ADC (Left and
 * Right) disabled; DACLRC disabled when
 * DAC (Left and Right) disabled.
 * 1 = ADCLRC and DACLRC disabled only when
 * ADC (Left and Right) and DAC (Left and Right)
 * are disabled.
 */
#define WM8960_ADDCTL2_LRCM_MASK (0x4U)
#define WM8960_ADDCTL2_LRCM_SHIFT (2U)
#define WM8960_ADDCTL2_LRCM_SET(x) (((uint16_t)(x) << WM8960_ADDCTL2_LRCM_SHIFT) & WM8960_ADDCTL2_LRCM_MASK)
#define WM8960_ADDCTL2_LRCM_GET(x) (((uint16_t)(x) & WM8960_ADDCTL2_LRCM_MASK) >> WM8960_ADDCTL2_LRCM_SHIFT)

/* Bitfield definition for register: POWER1 */
/*
 * VMIDSEL (RW)
 *
 * Vmid Divider Enable and Select
 * 00 = Vmid disabled (for OFF mode)
 * 01 = 2 x 50k divider enabled (for playback /
 * record)
 * 10 = 2 x 250k divider enabled (for low-power
 * standby)
 * 11 = 2 x 5k divider enabled (for fast start-up)
 */
#define WM8960_POWER1_VMIDSEL_MASK (0x180U)
#define WM8960_POWER1_VMIDSEL_SHIFT (7U)
#define WM8960_POWER1_VMIDSEL_SET(x) (((uint16_t)(x) << WM8960_POWER1_VMIDSEL_SHIFT) & WM8960_POWER1_VMIDSEL_MASK)
#define WM8960_POWER1_VMIDSEL_GET(x) (((uint16_t)(x) & WM8960_POWER1_VMIDSEL_MASK) >> WM8960_POWER1_VMIDSEL_SHIFT)

/*
 * VREF (RW)
 *
 * VREF (necessary for all other functions)
 * 0 = Power down
 * 1 = Power up
 */
#define WM8960_POWER1_VREF_MASK (0x40U)
#define WM8960_POWER1_VREF_SHIFT (6U)
#define WM8960_POWER1_VREF_SET(x) (((uint16_t)(x) << WM8960_POWER1_VREF_SHIFT) & WM8960_POWER1_VREF_MASK)
#define WM8960_POWER1_VREF_GET(x) (((uint16_t)(x) & WM8960_POWER1_VREF_MASK) >> WM8960_POWER1_VREF_SHIFT)

/*
 * AINL (RW)
 *
 * Analogue in PGA Left
 * 0 = Power down
 * 1 = Power up
 */
#define WM8960_POWER1_AINL_MASK (0x20U)
#define WM8960_POWER1_AINL_SHIFT (5U)
#define WM8960_POWER1_AINL_SET(x) (((uint16_t)(x) << WM8960_POWER1_AINL_SHIFT) & WM8960_POWER1_AINL_MASK)
#define WM8960_POWER1_AINL_GET(x) (((uint16_t)(x) & WM8960_POWER1_AINL_MASK) >> WM8960_POWER1_AINL_SHIFT)

/*
 * AINR (RW)
 *
 * Analogue in PGA Right
 * 0 = Power down
 * 1 = Power up
 */
#define WM8960_POWER1_AINR_MASK (0x10U)
#define WM8960_POWER1_AINR_SHIFT (4U)
#define WM8960_POWER1_AINR_SET(x) (((uint16_t)(x) << WM8960_POWER1_AINR_SHIFT) & WM8960_POWER1_AINR_MASK)
#define WM8960_POWER1_AINR_GET(x) (((uint16_t)(x) & WM8960_POWER1_AINR_MASK) >> WM8960_POWER1_AINR_SHIFT)

/*
 * ADCL (RW)
 *
 * ADC Left
 * 0 = Power down
 * 1 = Power up
 */
#define WM8960_POWER1_ADCL_MASK (0x8U)
#define WM8960_POWER1_ADCL_SHIFT (3U)
#define WM8960_POWER1_ADCL_SET(x) (((uint16_t)(x) << WM8960_POWER1_ADCL_SHIFT) & WM8960_POWER1_ADCL_MASK)
#define WM8960_POWER1_ADCL_GET(x) (((uint16_t)(x) & WM8960_POWER1_ADCL_MASK) >> WM8960_POWER1_ADCL_SHIFT)

/*
 * ADCR (RW)
 *
 * ADC Right
 * 0 = Power down
 * 1 = Power up
 */
#define WM8960_POWER1_ADCR_MASK (0x4U)
#define WM8960_POWER1_ADCR_SHIFT (2U)
#define WM8960_POWER1_ADCR_SET(x) (((uint16_t)(x) << WM8960_POWER1_ADCR_SHIFT) & WM8960_POWER1_ADCR_MASK)
#define WM8960_POWER1_ADCR_GET(x) (((uint16_t)(x) & WM8960_POWER1_ADCR_MASK) >> WM8960_POWER1_ADCR_SHIFT)

/*
 * MICB (RW)
 *
 * MICBIAS
 * 0 = Power down
 * 1 = Power up
 */
#define WM8960_POWER1_MICB_MASK (0x2U)
#define WM8960_POWER1_MICB_SHIFT (1U)
#define WM8960_POWER1_MICB_SET(x) (((uint16_t)(x) << WM8960_POWER1_MICB_SHIFT) & WM8960_POWER1_MICB_MASK)
#define WM8960_POWER1_MICB_GET(x) (((uint16_t)(x) & WM8960_POWER1_MICB_MASK) >> WM8960_POWER1_MICB_SHIFT)

/*
 * DIGENB (RW)
 *
 * Master Clock Disable
 * 0 = Master clock enabled
 * 1 = Master clock disabled
 */
#define WM8960_POWER1_DIGENB_MASK (0x1U)
#define WM8960_POWER1_DIGENB_SHIFT (0U)
#define WM8960_POWER1_DIGENB_SET(x) (((uint16_t)(x) << WM8960_POWER1_DIGENB_SHIFT) & WM8960_POWER1_DIGENB_MASK)
#define WM8960_POWER1_DIGENB_GET(x) (((uint16_t)(x) & WM8960_POWER1_DIGENB_MASK) >> WM8960_POWER1_DIGENB_SHIFT)

/* Bitfield definition for register: POWER2 */
/*
 * DACL (RW)
 *
 * DAC Left
 * 0 = Power down
 * 1 = Power up
 */
#define WM8960_POWER2_DACL_MASK (0x100U)
#define WM8960_POWER2_DACL_SHIFT (8U)
#define WM8960_POWER2_DACL_SET(x) (((uint16_t)(x) << WM8960_POWER2_DACL_SHIFT) & WM8960_POWER2_DACL_MASK)
#define WM8960_POWER2_DACL_GET(x) (((uint16_t)(x) & WM8960_POWER2_DACL_MASK) >> WM8960_POWER2_DACL_SHIFT)

/*
 * DACR (RW)
 *
 * DAC Right
 * 0 = Power down
 * 1 = Power up
 */
#define WM8960_POWER2_DACR_MASK (0x80U)
#define WM8960_POWER2_DACR_SHIFT (7U)
#define WM8960_POWER2_DACR_SET(x) (((uint16_t)(x) << WM8960_POWER2_DACR_SHIFT) & WM8960_POWER2_DACR_MASK)
#define WM8960_POWER2_DACR_GET(x) (((uint16_t)(x) & WM8960_POWER2_DACR_MASK) >> WM8960_POWER2_DACR_SHIFT)

/*
 * LOUT1 (RW)
 *
 * LOUT1 Output Buffer
 * 0 = Power down
 * 1 = Power up
 */
#define WM8960_POWER2_LOUT1_MASK (0x40U)
#define WM8960_POWER2_LOUT1_SHIFT (6U)
#define WM8960_POWER2_LOUT1_SET(x) (((uint16_t)(x) << WM8960_POWER2_LOUT1_SHIFT) & WM8960_POWER2_LOUT1_MASK)
#define WM8960_POWER2_LOUT1_GET(x) (((uint16_t)(x) & WM8960_POWER2_LOUT1_MASK) >> WM8960_POWER2_LOUT1_SHIFT)

/*
 * ROUT1 (RW)
 *
 * ROUT1 Output Buffer
 * 0 = Power down
 * 1 = Power up
 */
#define WM8960_POWER2_ROUT1_MASK (0x20U)
#define WM8960_POWER2_ROUT1_SHIFT (5U)
#define WM8960_POWER2_ROUT1_SET(x) (((uint16_t)(x) << WM8960_POWER2_ROUT1_SHIFT) & WM8960_POWER2_ROUT1_MASK)
#define WM8960_POWER2_ROUT1_GET(x) (((uint16_t)(x) & WM8960_POWER2_ROUT1_MASK) >> WM8960_POWER2_ROUT1_SHIFT)

/*
 * SPKL (RW)
 *
 * SPK_LP/SPK_LN Output Buffers
 * 0 = Power down
 * 1 = Power up
 */
#define WM8960_POWER2_SPKL_MASK (0x10U)
#define WM8960_POWER2_SPKL_SHIFT (4U)
#define WM8960_POWER2_SPKL_SET(x) (((uint16_t)(x) << WM8960_POWER2_SPKL_SHIFT) & WM8960_POWER2_SPKL_MASK)
#define WM8960_POWER2_SPKL_GET(x) (((uint16_t)(x) & WM8960_POWER2_SPKL_MASK) >> WM8960_POWER2_SPKL_SHIFT)

/*
 * SPKR (RW)
 *
 * SPK_RP/SPK_RN Output Buffers
 * 0 = Power down
 * 1 = Power up
 */
#define WM8960_POWER2_SPKR_MASK (0x8U)
#define WM8960_POWER2_SPKR_SHIFT (3U)
#define WM8960_POWER2_SPKR_SET(x) (((uint16_t)(x) << WM8960_POWER2_SPKR_SHIFT) & WM8960_POWER2_SPKR_MASK)
#define WM8960_POWER2_SPKR_GET(x) (((uint16_t)(x) & WM8960_POWER2_SPKR_MASK) >> WM8960_POWER2_SPKR_SHIFT)

/*
 * OUT3 (RW)
 *
 * OUT3 Output Buffer
 * 0 = Power down
 * 1 = Power up
 */
#define WM8960_POWER2_OUT3_MASK (0x2U)
#define WM8960_POWER2_OUT3_SHIFT (1U)
#define WM8960_POWER2_OUT3_SET(x) (((uint16_t)(x) << WM8960_POWER2_OUT3_SHIFT) & WM8960_POWER2_OUT3_MASK)
#define WM8960_POWER2_OUT3_GET(x) (((uint16_t)(x) & WM8960_POWER2_OUT3_MASK) >> WM8960_POWER2_OUT3_SHIFT)

/*
 * PLL_EN (RW)
 *
 * PLL Enable
 * 0 = Power down
 * 1 = Power up
 */
#define WM8960_POWER2_PLL_EN_MASK (0x1U)
#define WM8960_POWER2_PLL_EN_SHIFT (0U)
#define WM8960_POWER2_PLL_EN_SET(x) (((uint16_t)(x) << WM8960_POWER2_PLL_EN_SHIFT) & WM8960_POWER2_PLL_EN_MASK)
#define WM8960_POWER2_PLL_EN_GET(x) (((uint16_t)(x) & WM8960_POWER2_PLL_EN_MASK) >> WM8960_POWER2_PLL_EN_SHIFT)

/* Bitfield definition for register: ADDCTL3 */
/*
 * VROI (RW)
 *
 * VREF to Analogue Output Resistance (Disabled
 * Outputs)
 * 0 = 500 VMID to output
 * 1 = 20k VMID to output
 */
#define WM8960_ADDCTL3_VROI_MASK (0x40U)
#define WM8960_ADDCTL3_VROI_SHIFT (6U)
#define WM8960_ADDCTL3_VROI_SET(x) (((uint16_t)(x) << WM8960_ADDCTL3_VROI_SHIFT) & WM8960_ADDCTL3_VROI_MASK)
#define WM8960_ADDCTL3_VROI_GET(x) (((uint16_t)(x) & WM8960_ADDCTL3_VROI_MASK) >> WM8960_ADDCTL3_VROI_SHIFT)

/*
 * OUT3CAP (RW)
 *
 * Capless Mode Headphone Switch Enable
 * 0 = OUT3 unaffected by jack detect events
 * 1 = OUT3 enabled and disabled together with
 * HP_L and HP_R in response to jack detect
 * events
 */
#define WM8960_ADDCTL3_OUT3CAP_MASK (0x8U)
#define WM8960_ADDCTL3_OUT3CAP_SHIFT (3U)
#define WM8960_ADDCTL3_OUT3CAP_SET(x) (((uint16_t)(x) << WM8960_ADDCTL3_OUT3CAP_SHIFT) & WM8960_ADDCTL3_OUT3CAP_MASK)
#define WM8960_ADDCTL3_OUT3CAP_GET(x) (((uint16_t)(x) & WM8960_ADDCTL3_OUT3CAP_MASK) >> WM8960_ADDCTL3_OUT3CAP_SHIFT)

/*
 * ADC_ALC_SR (RW)
 *
 * ALC Sample Rate
 * 000 = 44.1k / 48k
 * 001 = 32k
 * 010 = 22.05k / 24k
 * 011 = 16k
 * 100 = 11.25k / 12k
 * 101 = 8k
 * 110 and 111 = Reserved
 */
#define WM8960_ADDCTL3_ADC_ALC_SR_MASK (0x7U)
#define WM8960_ADDCTL3_ADC_ALC_SR_SHIFT (0U)
#define WM8960_ADDCTL3_ADC_ALC_SR_SET(x) (((uint16_t)(x) << WM8960_ADDCTL3_ADC_ALC_SR_SHIFT) & WM8960_ADDCTL3_ADC_ALC_SR_MASK)
#define WM8960_ADDCTL3_ADC_ALC_SR_GET(x) (((uint16_t)(x) & WM8960_ADDCTL3_ADC_ALC_SR_MASK) >> WM8960_ADDCTL3_ADC_ALC_SR_SHIFT)

/* Bitfield definition for register: APOP1 */
/*
 * POBCTRL (RW)
 *
 * Selects the bias current source for output
 * amplifiers and VMID buffer
 * 0 = VMID / R bias
 * 1 = VGS / R bias
 */
#define WM8960_APOP1_POBCTRL_MASK (0x80U)
#define WM8960_APOP1_POBCTRL_SHIFT (7U)
#define WM8960_APOP1_POBCTRL_SET(x) (((uint16_t)(x) << WM8960_APOP1_POBCTRL_SHIFT) & WM8960_APOP1_POBCTRL_MASK)
#define WM8960_APOP1_POBCTRL_GET(x) (((uint16_t)(x) & WM8960_APOP1_POBCTRL_MASK) >> WM8960_APOP1_POBCTRL_SHIFT)

/*
 * BUFDCOPEN (RW)
 *
 * Enables the VGS / R current generator
 * 0 = Disabled
 * 1 = Enabled
 */
#define WM8960_APOP1_BUFDCOPEN_MASK (0x10U)
#define WM8960_APOP1_BUFDCOPEN_SHIFT (4U)
#define WM8960_APOP1_BUFDCOPEN_SET(x) (((uint16_t)(x) << WM8960_APOP1_BUFDCOPEN_SHIFT) & WM8960_APOP1_BUFDCOPEN_MASK)
#define WM8960_APOP1_BUFDCOPEN_GET(x) (((uint16_t)(x) & WM8960_APOP1_BUFDCOPEN_MASK) >> WM8960_APOP1_BUFDCOPEN_SHIFT)

/*
 * BUFIOEN (RW)
 *
 * Enables the VGS / R current generator and the
 * analogue input and output bias
 * 0 = Disabled
 * 1 = Enabled
 */
#define WM8960_APOP1_BUFIOEN_MASK (0x8U)
#define WM8960_APOP1_BUFIOEN_SHIFT (3U)
#define WM8960_APOP1_BUFIOEN_SET(x) (((uint16_t)(x) << WM8960_APOP1_BUFIOEN_SHIFT) & WM8960_APOP1_BUFIOEN_MASK)
#define WM8960_APOP1_BUFIOEN_GET(x) (((uint16_t)(x) & WM8960_APOP1_BUFIOEN_MASK) >> WM8960_APOP1_BUFIOEN_SHIFT)

/*
 * SOFT_ST (RW)
 *
 * Enables VMID soft start
 * 0 = Disabled
 * 1 = Enabled
 */
#define WM8960_APOP1_SOFT_ST_MASK (0x4U)
#define WM8960_APOP1_SOFT_ST_SHIFT (2U)
#define WM8960_APOP1_SOFT_ST_SET(x) (((uint16_t)(x) << WM8960_APOP1_SOFT_ST_SHIFT) & WM8960_APOP1_SOFT_ST_MASK)
#define WM8960_APOP1_SOFT_ST_GET(x) (((uint16_t)(x) & WM8960_APOP1_SOFT_ST_MASK) >> WM8960_APOP1_SOFT_ST_SHIFT)

/*
 * HPSTBY (RW)
 *
 * Headphone Amplifier Standby
 * 0 = Standby mode disabled (Normal operation)
 * 1 = Standby mode enabled
 */
#define WM8960_APOP1_HPSTBY_MASK (0x1U)
#define WM8960_APOP1_HPSTBY_SHIFT (0U)
#define WM8960_APOP1_HPSTBY_SET(x) (((uint16_t)(x) << WM8960_APOP1_HPSTBY_SHIFT) & WM8960_APOP1_HPSTBY_MASK)
#define WM8960_APOP1_HPSTBY_GET(x) (((uint16_t)(x) & WM8960_APOP1_HPSTBY_MASK) >> WM8960_APOP1_HPSTBY_SHIFT)

/* Bitfield definition for register: APOP2 */
/*
 * DISOP (RW)
 *
 * Discharges the DC-blocking headphone
 * capacitors on HP_L and HP_R
 * 0 = Disabled
 * 1 = Enabled
 */
#define WM8960_APOP2_DISOP_MASK (0x40U)
#define WM8960_APOP2_DISOP_SHIFT (6U)
#define WM8960_APOP2_DISOP_SET(x) (((uint16_t)(x) << WM8960_APOP2_DISOP_SHIFT) & WM8960_APOP2_DISOP_MASK)
#define WM8960_APOP2_DISOP_GET(x) (((uint16_t)(x) & WM8960_APOP2_DISOP_MASK) >> WM8960_APOP2_DISOP_SHIFT)

/*
 * DRES (RW)
 *
 * DRES determines the value of the resistors used
 * to discharge the DC-blocking headphone
 * capacitors when DISOP=1
 * DRES[1:0] Resistance (Ohms)
 * 0 0 400
 * 0 1 200
 * 1 0 600
 * 1 1 150
 */
#define WM8960_APOP2_DRES_MASK (0x30U)
#define WM8960_APOP2_DRES_SHIFT (4U)
#define WM8960_APOP2_DRES_SET(x) (((uint16_t)(x) << WM8960_APOP2_DRES_SHIFT) & WM8960_APOP2_DRES_MASK)
#define WM8960_APOP2_DRES_GET(x) (((uint16_t)(x) & WM8960_APOP2_DRES_MASK) >> WM8960_APOP2_DRES_SHIFT)

/* Bitfield definition for register: LINPATH */
/*
 * LMN1 (RW)
 *
 * Connect LINPUT1 to inverting input of Left Input
 * PGA
 * 0 = LINPUT1 not connected to PGA
 * 1 = LINPUT1 connected to PGA
 */
#define WM8960_LINPATH_LMN1_MASK (0x100U)
#define WM8960_LINPATH_LMN1_SHIFT (8U)
#define WM8960_LINPATH_LMN1_SET(x) (((uint16_t)(x) << WM8960_LINPATH_LMN1_SHIFT) & WM8960_LINPATH_LMN1_MASK)
#define WM8960_LINPATH_LMN1_GET(x) (((uint16_t)(x) & WM8960_LINPATH_LMN1_MASK) >> WM8960_LINPATH_LMN1_SHIFT)

/*
 * LMP3 (RW)
 *
 * Connect LINPUT3 to non-inverting input of Left
 * Input PGA
 * 0 = LINPUT3 not connected to PGA
 * 1 = LINPUT3 connected to PGA (Constant input
 * impedance)
 */
#define WM8960_LINPATH_LMP3_MASK (0x80U)
#define WM8960_LINPATH_LMP3_SHIFT (7U)
#define WM8960_LINPATH_LMP3_SET(x) (((uint16_t)(x) << WM8960_LINPATH_LMP3_SHIFT) & WM8960_LINPATH_LMP3_MASK)
#define WM8960_LINPATH_LMP3_GET(x) (((uint16_t)(x) & WM8960_LINPATH_LMP3_MASK) >> WM8960_LINPATH_LMP3_SHIFT)

/*
 * LMP2 (RW)
 *
 * Connect LINPUT2 to non-inverting input of Left
 * Input PGA
 * 0 = LINPUT2 not connected to PGA
 * 1 = LINPUT2 connected to PGA (Constant input impedance)
 */
#define WM8960_LINPATH_LMP2_MASK (0x40U)
#define WM8960_LINPATH_LMP2_SHIFT (6U)
#define WM8960_LINPATH_LMP2_SET(x) (((uint16_t)(x) << WM8960_LINPATH_LMP2_SHIFT) & WM8960_LINPATH_LMP2_MASK)
#define WM8960_LINPATH_LMP2_GET(x) (((uint16_t)(x) & WM8960_LINPATH_LMP2_MASK) >> WM8960_LINPATH_LMP2_SHIFT)

/*
 * LMICBOOST (RW)
 *
 * Left Channel Input PGA Boost Gain
 * 00 = +0dB
 * 01 = +13dB
 * 10 = +20dB
 * 11 = +29dB
 */
#define WM8960_LINPATH_LMICBOOST_MASK (0x30U)
#define WM8960_LINPATH_LMICBOOST_SHIFT (4U)
#define WM8960_LINPATH_LMICBOOST_SET(x) (((uint16_t)(x) << WM8960_LINPATH_LMICBOOST_SHIFT) & WM8960_LINPATH_LMICBOOST_MASK)
#define WM8960_LINPATH_LMICBOOST_GET(x) (((uint16_t)(x) & WM8960_LINPATH_LMICBOOST_MASK) >> WM8960_LINPATH_LMICBOOST_SHIFT)

/*
 * LMIC2B (RW)
 *
 * Connect Left Input PGA to Left Input Boost Mixer
 * 0 = Not connected
 * 1 = Connected
 */
#define WM8960_LINPATH_LMIC2B_MASK (0x8U)
#define WM8960_LINPATH_LMIC2B_SHIFT (3U)
#define WM8960_LINPATH_LMIC2B_SET(x) (((uint16_t)(x) << WM8960_LINPATH_LMIC2B_SHIFT) & WM8960_LINPATH_LMIC2B_MASK)
#define WM8960_LINPATH_LMIC2B_GET(x) (((uint16_t)(x) & WM8960_LINPATH_LMIC2B_MASK) >> WM8960_LINPATH_LMIC2B_SHIFT)

/* Bitfield definition for register: RINPATH */
/*
 * RMN1 (RW)
 *
 * Connect RINPUT1 to inverting input of Right
 * Input PGA
 * 0 = RINPUT1 not connected to PGA
 * 1 = RINPUT1 connected to PGA
 */
#define WM8960_RINPATH_RMN1_MASK (0x100U)
#define WM8960_RINPATH_RMN1_SHIFT (8U)
#define WM8960_RINPATH_RMN1_SET(x) (((uint16_t)(x) << WM8960_RINPATH_RMN1_SHIFT) & WM8960_RINPATH_RMN1_MASK)
#define WM8960_RINPATH_RMN1_GET(x) (((uint16_t)(x) & WM8960_RINPATH_RMN1_MASK) >> WM8960_RINPATH_RMN1_SHIFT)

/*
 * RMP3 (RW)
 *
 * Connect RINPUT3 to non-inverting input of Right
 * Input PGA
 * 0 = RINPUT3 not connected to PGA
 * 1 = RINPUT3 connected to PGA (Constant input impedance)
 */
#define WM8960_RINPATH_RMP3_MASK (0x80U)
#define WM8960_RINPATH_RMP3_SHIFT (7U)
#define WM8960_RINPATH_RMP3_SET(x) (((uint16_t)(x) << WM8960_RINPATH_RMP3_SHIFT) & WM8960_RINPATH_RMP3_MASK)
#define WM8960_RINPATH_RMP3_GET(x) (((uint16_t)(x) & WM8960_RINPATH_RMP3_MASK) >> WM8960_RINPATH_RMP3_SHIFT)

/*
 * RMP2 (RW)
 *
 * Connect RINPUT2 to non-inverting input of Right
 * Input PGA
 * 0 = RINPUT2 not connected to PGA
 * 1 = RINPUT2 connected to PGA (Constant input
 * impedance)
 */
#define WM8960_RINPATH_RMP2_MASK (0x40U)
#define WM8960_RINPATH_RMP2_SHIFT (6U)
#define WM8960_RINPATH_RMP2_SET(x) (((uint16_t)(x) << WM8960_RINPATH_RMP2_SHIFT) & WM8960_RINPATH_RMP2_MASK)
#define WM8960_RINPATH_RMP2_GET(x) (((uint16_t)(x) & WM8960_RINPATH_RMP2_MASK) >> WM8960_RINPATH_RMP2_SHIFT)

/*
 * RMICBOOST (RW)
 *
 * Right Channel Input PGA Boost Gain
 * 00 = +0dB
 * 01 = +13dB
 * 10 = +20dB
 * 11 = +29dB
 */
#define WM8960_RINPATH_RMICBOOST_MASK (0x30U)
#define WM8960_RINPATH_RMICBOOST_SHIFT (4U)
#define WM8960_RINPATH_RMICBOOST_SET(x) (((uint16_t)(x) << WM8960_RINPATH_RMICBOOST_SHIFT) & WM8960_RINPATH_RMICBOOST_MASK)
#define WM8960_RINPATH_RMICBOOST_GET(x) (((uint16_t)(x) & WM8960_RINPATH_RMICBOOST_MASK) >> WM8960_RINPATH_RMICBOOST_SHIFT)

/*
 * RMIC2B (RW)
 *
 * Connect Right Input PGA to Right Input Boost
 * Mixer
 * 0 = Not connected
 * 1 = Connected
 */
#define WM8960_RINPATH_RMIC2B_MASK (0x8U)
#define WM8960_RINPATH_RMIC2B_SHIFT (3U)
#define WM8960_RINPATH_RMIC2B_SET(x) (((uint16_t)(x) << WM8960_RINPATH_RMIC2B_SHIFT) & WM8960_RINPATH_RMIC2B_MASK)
#define WM8960_RINPATH_RMIC2B_GET(x) (((uint16_t)(x) & WM8960_RINPATH_RMIC2B_MASK) >> WM8960_RINPATH_RMIC2B_SHIFT)

/* Bitfield definition for register: LOUTMIX */
/*
 * LD2LO (RW)
 *
 * Left DAC to Left Output Mixer
 * 0 = Disable (Mute)
 * 1 = Enable Path
 */
#define WM8960_LOUTMIX_LD2LO_MASK (0x100U)
#define WM8960_LOUTMIX_LD2LO_SHIFT (8U)
#define WM8960_LOUTMIX_LD2LO_SET(x) (((uint16_t)(x) << WM8960_LOUTMIX_LD2LO_SHIFT) & WM8960_LOUTMIX_LD2LO_MASK)
#define WM8960_LOUTMIX_LD2LO_GET(x) (((uint16_t)(x) & WM8960_LOUTMIX_LD2LO_MASK) >> WM8960_LOUTMIX_LD2LO_SHIFT)

/*
 * LI2LO (RW)
 *
 * LINPUT3 to Left Output Mixer
 * 0 = Disable (Mute)
 * 1 = Enable Path
 */
#define WM8960_LOUTMIX_LI2LO_MASK (0x80U)
#define WM8960_LOUTMIX_LI2LO_SHIFT (7U)
#define WM8960_LOUTMIX_LI2LO_SET(x) (((uint16_t)(x) << WM8960_LOUTMIX_LI2LO_SHIFT) & WM8960_LOUTMIX_LI2LO_MASK)
#define WM8960_LOUTMIX_LI2LO_GET(x) (((uint16_t)(x) & WM8960_LOUTMIX_LI2LO_MASK) >> WM8960_LOUTMIX_LI2LO_SHIFT)

/*
 * LI2LOVOL (RW)
 *
 * LINPUT3 to Left Output Mixer Volume
 * 000 = 0dB
 * ...(3dB steps)
 * 111 = -21dB
 */
#define WM8960_LOUTMIX_LI2LOVOL_MASK (0x70U)
#define WM8960_LOUTMIX_LI2LOVOL_SHIFT (4U)
#define WM8960_LOUTMIX_LI2LOVOL_SET(x) (((uint16_t)(x) << WM8960_LOUTMIX_LI2LOVOL_SHIFT) & WM8960_LOUTMIX_LI2LOVOL_MASK)
#define WM8960_LOUTMIX_LI2LOVOL_GET(x) (((uint16_t)(x) & WM8960_LOUTMIX_LI2LOVOL_MASK) >> WM8960_LOUTMIX_LI2LOVOL_SHIFT)

/* Bitfield definition for register: ROUTMIX */
/*
 * RD2RO (RW)
 *
 * Right DAC to Right Output Mixer
 * 0 = Disable (Mute)
 * 1 = Enable Path
 */
#define WM8960_ROUTMIX_RD2RO_MASK (0x100U)
#define WM8960_ROUTMIX_RD2RO_SHIFT (8U)
#define WM8960_ROUTMIX_RD2RO_SET(x) (((uint16_t)(x) << WM8960_ROUTMIX_RD2RO_SHIFT) & WM8960_ROUTMIX_RD2RO_MASK)
#define WM8960_ROUTMIX_RD2RO_GET(x) (((uint16_t)(x) & WM8960_ROUTMIX_RD2RO_MASK) >> WM8960_ROUTMIX_RD2RO_SHIFT)

/*
 * RI2RO (RW)
 *
 * RINPUT3 to Right Output Mixer
 * 0 = Disable (Mute)
 * 1 = Enable Path
 */
#define WM8960_ROUTMIX_RI2RO_MASK (0x80U)
#define WM8960_ROUTMIX_RI2RO_SHIFT (7U)
#define WM8960_ROUTMIX_RI2RO_SET(x) (((uint16_t)(x) << WM8960_ROUTMIX_RI2RO_SHIFT) & WM8960_ROUTMIX_RI2RO_MASK)
#define WM8960_ROUTMIX_RI2RO_GET(x) (((uint16_t)(x) & WM8960_ROUTMIX_RI2RO_MASK) >> WM8960_ROUTMIX_RI2RO_SHIFT)

/*
 * RI2ROVOL (RW)
 *
 * RINPUT3 to Right Output Mixer Volume
 * 000 = 0dB
 * ...(3dB steps)
 * 111 = -21dB
 */
#define WM8960_ROUTMIX_RI2ROVOL_MASK (0x70U)
#define WM8960_ROUTMIX_RI2ROVOL_SHIFT (4U)
#define WM8960_ROUTMIX_RI2ROVOL_SET(x) (((uint16_t)(x) << WM8960_ROUTMIX_RI2ROVOL_SHIFT) & WM8960_ROUTMIX_RI2ROVOL_MASK)
#define WM8960_ROUTMIX_RI2ROVOL_GET(x) (((uint16_t)(x) & WM8960_ROUTMIX_RI2ROVOL_MASK) >> WM8960_ROUTMIX_RI2ROVOL_SHIFT)

/* Bitfield definition for register: MONOMIX1 */
/*
 * L2MO (RW)
 *
 * Left Output Mixer to Mono Output Mixer Control
 * 0 = Left channel mix disabled
 * 1 = Left channel mix enabled
 */
#define WM8960_MONOMIX1_L2MO_MASK (0x80U)
#define WM8960_MONOMIX1_L2MO_SHIFT (7U)
#define WM8960_MONOMIX1_L2MO_SET(x) (((uint16_t)(x) << WM8960_MONOMIX1_L2MO_SHIFT) & WM8960_MONOMIX1_L2MO_MASK)
#define WM8960_MONOMIX1_L2MO_GET(x) (((uint16_t)(x) & WM8960_MONOMIX1_L2MO_MASK) >> WM8960_MONOMIX1_L2MO_SHIFT)

/* Bitfield definition for register: MONOMIX2 */
/*
 * R2MO (RW)
 *
 * Right Output Mixer to Mono Output Mixer Control
 * 0 = Right channel mix disabled
 * 1 = Right channel mix enabled
 */
#define WM8960_MONOMIX2_R2MO_MASK (0x80U)
#define WM8960_MONOMIX2_R2MO_SHIFT (7U)
#define WM8960_MONOMIX2_R2MO_SET(x) (((uint16_t)(x) << WM8960_MONOMIX2_R2MO_SHIFT) & WM8960_MONOMIX2_R2MO_MASK)
#define WM8960_MONOMIX2_R2MO_GET(x) (((uint16_t)(x) & WM8960_MONOMIX2_R2MO_MASK) >> WM8960_MONOMIX2_R2MO_SHIFT)

/* Bitfield definition for register: LOUT2 */
/*
 * SPKVU (RW)
 *
 * Speaker Volume Update
 * Writing a 1 to this bit will cause left and right speaker volumes to be updated (SPKLVOL and SPKRVOL)
 */
#define WM8960_LOUT2_SPKVU_MASK (0x100U)
#define WM8960_LOUT2_SPKVU_SHIFT (8U)
#define WM8960_LOUT2_SPKVU_SET(x) (((uint16_t)(x) << WM8960_LOUT2_SPKVU_SHIFT) & WM8960_LOUT2_SPKVU_MASK)
#define WM8960_LOUT2_SPKVU_GET(x) (((uint16_t)(x) & WM8960_LOUT2_SPKVU_MASK) >> WM8960_LOUT2_SPKVU_SHIFT)

/*
 * SPKLZC (RW)
 *
 * Left Speaker Zero Cross Enable
 * 1 = Change gain on zero cross only
 * 0 = Change gain immediately
 */
#define WM8960_LOUT2_SPKLZC_MASK (0x80U)
#define WM8960_LOUT2_SPKLZC_SHIFT (7U)
#define WM8960_LOUT2_SPKLZC_SET(x) (((uint16_t)(x) << WM8960_LOUT2_SPKLZC_SHIFT) & WM8960_LOUT2_SPKLZC_MASK)
#define WM8960_LOUT2_SPKLZC_GET(x) (((uint16_t)(x) & WM8960_LOUT2_SPKLZC_MASK) >> WM8960_LOUT2_SPKLZC_SHIFT)

/*
 * SPKLVOL (RW)
 *
 * SPK_LP/SPK_LN Volume
 * 1111111 = +6dB
 * … 1dB steps down to
 * 0110000 = -73dB
 * 0101111 to 0000000 = Analogue MUTE
 */
#define WM8960_LOUT2_SPKLVOL_MASK (0x7FU)
#define WM8960_LOUT2_SPKLVOL_SHIFT (0U)
#define WM8960_LOUT2_SPKLVOL_SET(x) (((uint16_t)(x) << WM8960_LOUT2_SPKLVOL_SHIFT) & WM8960_LOUT2_SPKLVOL_MASK)
#define WM8960_LOUT2_SPKLVOL_GET(x) (((uint16_t)(x) & WM8960_LOUT2_SPKLVOL_MASK) >> WM8960_LOUT2_SPKLVOL_SHIFT)

/* Bitfield definition for register: ROUT2 */
/*
 * SPKVU (RW)
 *
 * Speaker Volume Update
 * Writing a 1 to this bit will cause left and right
 * speaker volumes to be updated (SPKLVOL and SPKRVOL)
 */
#define WM8960_ROUT2_SPKVU_MASK (0x100U)
#define WM8960_ROUT2_SPKVU_SHIFT (8U)
#define WM8960_ROUT2_SPKVU_SET(x) (((uint16_t)(x) << WM8960_ROUT2_SPKVU_SHIFT) & WM8960_ROUT2_SPKVU_MASK)
#define WM8960_ROUT2_SPKVU_GET(x) (((uint16_t)(x) & WM8960_ROUT2_SPKVU_MASK) >> WM8960_ROUT2_SPKVU_SHIFT)

/*
 * SPKRZC (RW)
 *
 * Right Speaker Zero Cross Enable
 * 1 = Change gain on zero cross only
 * 0 = Change gain immediately
 */
#define WM8960_ROUT2_SPKRZC_MASK (0x80U)
#define WM8960_ROUT2_SPKRZC_SHIFT (7U)
#define WM8960_ROUT2_SPKRZC_SET(x) (((uint16_t)(x) << WM8960_ROUT2_SPKRZC_SHIFT) & WM8960_ROUT2_SPKRZC_MASK)
#define WM8960_ROUT2_SPKRZC_GET(x) (((uint16_t)(x) & WM8960_ROUT2_SPKRZC_MASK) >> WM8960_ROUT2_SPKRZC_SHIFT)

/*
 * SPKRVOL (RW)
 *
 * SPK_RP/SPK_RN Volume
 * 1111111 = +6dB
 * … 1dB steps down to
 * 0110000 = -73dB
 * 0101111 to 0000000 = Analogue MUTE
 */
#define WM8960_ROUT2_SPKRVOL_MASK (0x7FU)
#define WM8960_ROUT2_SPKRVOL_SHIFT (0U)
#define WM8960_ROUT2_SPKRVOL_SET(x) (((uint16_t)(x) << WM8960_ROUT2_SPKRVOL_SHIFT) & WM8960_ROUT2_SPKRVOL_MASK)
#define WM8960_ROUT2_SPKRVOL_GET(x) (((uint16_t)(x) & WM8960_ROUT2_SPKRVOL_MASK) >> WM8960_ROUT2_SPKRVOL_SHIFT)

/* Bitfield definition for register: MONO */
/*
 * MOUTVOL (RW)
 *
 * Mono Output Mixer Volume Control
 * 0 = 0dB
 * 1 = -6dB
 */
#define WM8960_MONO_MOUTVOL_MASK (0x40U)
#define WM8960_MONO_MOUTVOL_SHIFT (6U)
#define WM8960_MONO_MOUTVOL_SET(x) (((uint16_t)(x) << WM8960_MONO_MOUTVOL_SHIFT) & WM8960_MONO_MOUTVOL_MASK)
#define WM8960_MONO_MOUTVOL_GET(x) (((uint16_t)(x) & WM8960_MONO_MOUTVOL_MASK) >> WM8960_MONO_MOUTVOL_SHIFT)

/* Bitfield definition for register: INBMIX1 */
/*
 * LIN3BOOST (RW)
 *
 * LINPUT3 to Boost Mixer Gain
 * 000 = Mute
 * 001 = -12dB
 * ...3dB steps up to
 * 111 = +6dB
 */
#define WM8960_INBMIX1_LIN3BOOST_MASK (0x70U)
#define WM8960_INBMIX1_LIN3BOOST_SHIFT (4U)
#define WM8960_INBMIX1_LIN3BOOST_SET(x) (((uint16_t)(x) << WM8960_INBMIX1_LIN3BOOST_SHIFT) & WM8960_INBMIX1_LIN3BOOST_MASK)
#define WM8960_INBMIX1_LIN3BOOST_GET(x) (((uint16_t)(x) & WM8960_INBMIX1_LIN3BOOST_MASK) >> WM8960_INBMIX1_LIN3BOOST_SHIFT)

/*
 * LIN2BOOST (RW)
 *
 * LINPUT2 to Boost Mixer Gain
 * 000 = Mute
 * 001 = -12dB
 * ...3dB steps up to
 * 111 = +6dB
 */
#define WM8960_INBMIX1_LIN2BOOST_MASK (0xEU)
#define WM8960_INBMIX1_LIN2BOOST_SHIFT (1U)
#define WM8960_INBMIX1_LIN2BOOST_SET(x) (((uint16_t)(x) << WM8960_INBMIX1_LIN2BOOST_SHIFT) & WM8960_INBMIX1_LIN2BOOST_MASK)
#define WM8960_INBMIX1_LIN2BOOST_GET(x) (((uint16_t)(x) & WM8960_INBMIX1_LIN2BOOST_MASK) >> WM8960_INBMIX1_LIN2BOOST_SHIFT)

/* Bitfield definition for register: INBMIX2 */
/*
 * RIN3BOOST (RW)
 *
 * RINPUT3 to Boost Mixer Gain
 * 000 = Mute
 * 001 = -12dB
 * ...3dB steps up to
 * 111 = +6dB
 */
#define WM8960_INBMIX2_RIN3BOOST_MASK (0x70U)
#define WM8960_INBMIX2_RIN3BOOST_SHIFT (4U)
#define WM8960_INBMIX2_RIN3BOOST_SET(x) (((uint16_t)(x) << WM8960_INBMIX2_RIN3BOOST_SHIFT) & WM8960_INBMIX2_RIN3BOOST_MASK)
#define WM8960_INBMIX2_RIN3BOOST_GET(x) (((uint16_t)(x) & WM8960_INBMIX2_RIN3BOOST_MASK) >> WM8960_INBMIX2_RIN3BOOST_SHIFT)

/*
 * RIN2BOOST (RW)
 *
 * RINPUT2 to Boost Mixer Gain
 * 000 = Mute
 * 001 = -12dB
 * ...3dB steps up to
 * 111 = +6dB
 */
#define WM8960_INBMIX2_RIN2BOOST_MASK (0xEU)
#define WM8960_INBMIX2_RIN2BOOST_SHIFT (1U)
#define WM8960_INBMIX2_RIN2BOOST_SET(x) (((uint16_t)(x) << WM8960_INBMIX2_RIN2BOOST_SHIFT) & WM8960_INBMIX2_RIN2BOOST_MASK)
#define WM8960_INBMIX2_RIN2BOOST_GET(x) (((uint16_t)(x) & WM8960_INBMIX2_RIN2BOOST_MASK) >> WM8960_INBMIX2_RIN2BOOST_SHIFT)

/* Bitfield definition for register: BYPASS1 */
/*
 * LB2LO (RW)
 *
 * Left Input Boost Mixer to Left Output Mixer
 * 0 = Disable (Mute)
 * 1 = Enable Path
 */
#define WM8960_BYPASS1_LB2LO_MASK (0x80U)
#define WM8960_BYPASS1_LB2LO_SHIFT (7U)
#define WM8960_BYPASS1_LB2LO_SET(x) (((uint16_t)(x) << WM8960_BYPASS1_LB2LO_SHIFT) & WM8960_BYPASS1_LB2LO_MASK)
#define WM8960_BYPASS1_LB2LO_GET(x) (((uint16_t)(x) & WM8960_BYPASS1_LB2LO_MASK) >> WM8960_BYPASS1_LB2LO_SHIFT)

/*
 * LB2LOVOL (RW)
 *
 * Left Input Boost Mixer to Left Output Mixer
 * Volume
 * 000 = 0dB
 * ...(3dB steps)
 * 111 = -21dB
 */
#define WM8960_BYPASS1_LB2LOVOL_MASK (0x70U)
#define WM8960_BYPASS1_LB2LOVOL_SHIFT (4U)
#define WM8960_BYPASS1_LB2LOVOL_SET(x) (((uint16_t)(x) << WM8960_BYPASS1_LB2LOVOL_SHIFT) & WM8960_BYPASS1_LB2LOVOL_MASK)
#define WM8960_BYPASS1_LB2LOVOL_GET(x) (((uint16_t)(x) & WM8960_BYPASS1_LB2LOVOL_MASK) >> WM8960_BYPASS1_LB2LOVOL_SHIFT)

/* Bitfield definition for register: BYPASS2 */
/*
 * RB2RO (RW)
 *
 * Right Input Boost Mixer to Right Output Mixer
 * 0 = Disable (Mute)
 * 1 = Enable Path
 */
#define WM8960_BYPASS2_RB2RO_MASK (0x80U)
#define WM8960_BYPASS2_RB2RO_SHIFT (7U)
#define WM8960_BYPASS2_RB2RO_SET(x) (((uint16_t)(x) << WM8960_BYPASS2_RB2RO_SHIFT) & WM8960_BYPASS2_RB2RO_MASK)
#define WM8960_BYPASS2_RB2RO_GET(x) (((uint16_t)(x) & WM8960_BYPASS2_RB2RO_MASK) >> WM8960_BYPASS2_RB2RO_SHIFT)

/*
 * RB2ROVOL (RW)
 *
 * Right Input Boost Mixer to Right Output Mixer
 * Volume
 * 000 = 0dB
 * ...(3dB steps)
 * 111 = -21dB
 */
#define WM8960_BYPASS2_RB2ROVOL_MASK (0x70U)
#define WM8960_BYPASS2_RB2ROVOL_SHIFT (4U)
#define WM8960_BYPASS2_RB2ROVOL_SET(x) (((uint16_t)(x) << WM8960_BYPASS2_RB2ROVOL_SHIFT) & WM8960_BYPASS2_RB2ROVOL_MASK)
#define WM8960_BYPASS2_RB2ROVOL_GET(x) (((uint16_t)(x) & WM8960_BYPASS2_RB2ROVOL_MASK) >> WM8960_BYPASS2_RB2ROVOL_SHIFT)

/* Bitfield definition for register: POWER3 */
/*
 * LMIC (RW)
 *
 * Left Channel Input PGA Enable
 * 0 = PGA disabled
 * 1 = PGA enabled (if AINL = 1)
 */
#define WM8960_POWER3_LMIC_MASK (0x20U)
#define WM8960_POWER3_LMIC_SHIFT (5U)
#define WM8960_POWER3_LMIC_SET(x) (((uint16_t)(x) << WM8960_POWER3_LMIC_SHIFT) & WM8960_POWER3_LMIC_MASK)
#define WM8960_POWER3_LMIC_GET(x) (((uint16_t)(x) & WM8960_POWER3_LMIC_MASK) >> WM8960_POWER3_LMIC_SHIFT)

/*
 * RMIC (RW)
 *
 * Right Channel Input PGA Enable
 * 0 = PGA disabled
 * 1 = PGA enabled (if AINR = 1)
 */
#define WM8960_POWER3_RMIC_MASK (0x10U)
#define WM8960_POWER3_RMIC_SHIFT (4U)
#define WM8960_POWER3_RMIC_SET(x) (((uint16_t)(x) << WM8960_POWER3_RMIC_SHIFT) & WM8960_POWER3_RMIC_MASK)
#define WM8960_POWER3_RMIC_GET(x) (((uint16_t)(x) & WM8960_POWER3_RMIC_MASK) >> WM8960_POWER3_RMIC_SHIFT)

/*
 * LOMIX (RW)
 *
 * Left Output Mixer Enable Control
 * 0 = Disabled
 * 1 = Enabled
 */
#define WM8960_POWER3_LOMIX_MASK (0x8U)
#define WM8960_POWER3_LOMIX_SHIFT (3U)
#define WM8960_POWER3_LOMIX_SET(x) (((uint16_t)(x) << WM8960_POWER3_LOMIX_SHIFT) & WM8960_POWER3_LOMIX_MASK)
#define WM8960_POWER3_LOMIX_GET(x) (((uint16_t)(x) & WM8960_POWER3_LOMIX_MASK) >> WM8960_POWER3_LOMIX_SHIFT)

/*
 * ROMIX (RW)
 *
 * Right Output Mixer Enable Control
 * 0 = Disabled
 * 1 = Enabled
 */
#define WM8960_POWER3_ROMIX_MASK (0x4U)
#define WM8960_POWER3_ROMIX_SHIFT (2U)
#define WM8960_POWER3_ROMIX_SET(x) (((uint16_t)(x) << WM8960_POWER3_ROMIX_SHIFT) & WM8960_POWER3_ROMIX_MASK)
#define WM8960_POWER3_ROMIX_GET(x) (((uint16_t)(x) & WM8960_POWER3_ROMIX_MASK) >> WM8960_POWER3_ROMIX_SHIFT)

/* Bitfield definition for register: ADDCTL4 */
/*
 * GPIOPOL (RW)
 *
 * GPIO Polarity Invert
 * 0 = Non inverted
 * 1 = Inverted
 */
#define WM8960_ADDCTL4_GPIOPOL_MASK (0x80U)
#define WM8960_ADDCTL4_GPIOPOL_SHIFT (7U)
#define WM8960_ADDCTL4_GPIOPOL_SET(x) (((uint16_t)(x) << WM8960_ADDCTL4_GPIOPOL_SHIFT) & WM8960_ADDCTL4_GPIOPOL_MASK)
#define WM8960_ADDCTL4_GPIOPOL_GET(x) (((uint16_t)(x) & WM8960_ADDCTL4_GPIOPOL_MASK) >> WM8960_ADDCTL4_GPIOPOL_SHIFT)

/*
 * GPIOSEL (RW)
 *
 * ADCLRC/GPIO1 GPIO Function Select:
 * 000 = Jack detect input
 * 001 = Reserved
 * 010 = Temperature ok
 * 011 = Debounced jack detect output
 * 100 = SYSCLK output
 * 101 = PLL lock
 * 110 = Logic 0
 * 111 = Logic 1
 */
#define WM8960_ADDCTL4_GPIOSEL_MASK (0x70U)
#define WM8960_ADDCTL4_GPIOSEL_SHIFT (4U)
#define WM8960_ADDCTL4_GPIOSEL_SET(x) (((uint16_t)(x) << WM8960_ADDCTL4_GPIOSEL_SHIFT) & WM8960_ADDCTL4_GPIOSEL_MASK)
#define WM8960_ADDCTL4_GPIOSEL_GET(x) (((uint16_t)(x) & WM8960_ADDCTL4_GPIOSEL_MASK) >> WM8960_ADDCTL4_GPIOSEL_SHIFT)

/*
 * HPSEL (RW)
 *
 * Headphone Switch Input Select
 * 0X = GPIO1 used for jack detect input (Requires
 * ADCLRC pin to be configured as a GPIO)
 * 10 = JD2 used for jack detect input
 * 11 = JD3 used for jack detect input
 */
#define WM8960_ADDCTL4_HPSEL_MASK (0xCU)
#define WM8960_ADDCTL4_HPSEL_SHIFT (2U)
#define WM8960_ADDCTL4_HPSEL_SET(x) (((uint16_t)(x) << WM8960_ADDCTL4_HPSEL_SHIFT) & WM8960_ADDCTL4_HPSEL_MASK)
#define WM8960_ADDCTL4_HPSEL_GET(x) (((uint16_t)(x) & WM8960_ADDCTL4_HPSEL_MASK) >> WM8960_ADDCTL4_HPSEL_SHIFT)

/*
 * TSENSEN (RW)
 *
 * Temperature Sensor Enable
 * 0 = Temperature sensor disabled
 * 1 = Temperature sensor enabled
 */
#define WM8960_ADDCTL4_TSENSEN_MASK (0x2U)
#define WM8960_ADDCTL4_TSENSEN_SHIFT (1U)
#define WM8960_ADDCTL4_TSENSEN_SET(x) (((uint16_t)(x) << WM8960_ADDCTL4_TSENSEN_SHIFT) & WM8960_ADDCTL4_TSENSEN_MASK)
#define WM8960_ADDCTL4_TSENSEN_GET(x) (((uint16_t)(x) & WM8960_ADDCTL4_TSENSEN_MASK) >> WM8960_ADDCTL4_TSENSEN_SHIFT)

/*
 * MBSEL (RW)
 *
 * Microphone Bias Voltage Control
 * 0 = 0.9 * AVDD
 * 1 = 0.65 * AVDD
 */
#define WM8960_ADDCTL4_MBSEL_MASK (0x1U)
#define WM8960_ADDCTL4_MBSEL_SHIFT (0U)
#define WM8960_ADDCTL4_MBSEL_SET(x) (((uint16_t)(x) << WM8960_ADDCTL4_MBSEL_SHIFT) & WM8960_ADDCTL4_MBSEL_MASK)
#define WM8960_ADDCTL4_MBSEL_GET(x) (((uint16_t)(x) & WM8960_ADDCTL4_MBSEL_MASK) >> WM8960_ADDCTL4_MBSEL_SHIFT)

/* Bitfield definition for register: CLASSD1 */
/*
 * SPK_OP_EN (RW)
 *
 * Enable Class D Speaker Outputs
 * 00 = Off
 * 01 = Left speaker only
 * 10 = Right speaker only
 * 11 = Left and right speakers enabled
 */
#define WM8960_CLASSD1_SPK_OP_EN_MASK (0xC0U)
#define WM8960_CLASSD1_SPK_OP_EN_SHIFT (6U)
#define WM8960_CLASSD1_SPK_OP_EN_SET(x) (((uint16_t)(x) << WM8960_CLASSD1_SPK_OP_EN_SHIFT) & WM8960_CLASSD1_SPK_OP_EN_MASK)
#define WM8960_CLASSD1_SPK_OP_EN_GET(x) (((uint16_t)(x) & WM8960_CLASSD1_SPK_OP_EN_MASK) >> WM8960_CLASSD1_SPK_OP_EN_SHIFT)

/* Bitfield definition for register: CLASSD3 */
/*
 * DCGAIN (RW)
 *
 * DC Speaker Boost (Boosts speaker DC output
 * level by up to 1.8 x on left and right channels)
 * 000 = 1.00x boost (+0dB)
 * 001 = 1.27x boost (+2.1dB)
 * 010 = 1.40x boost (+2.9dB)
 * 011 = 1.52x boost (+3.6dB)
 * 100 = 1.67x boost (+4.5dB)
 * 101 = 1.8x boost (+5.1dB)
 * 110 to 111 = Reserved
 */
#define WM8960_CLASSD3_DCGAIN_MASK (0x38U)
#define WM8960_CLASSD3_DCGAIN_SHIFT (3U)
#define WM8960_CLASSD3_DCGAIN_SET(x) (((uint16_t)(x) << WM8960_CLASSD3_DCGAIN_SHIFT) & WM8960_CLASSD3_DCGAIN_MASK)
#define WM8960_CLASSD3_DCGAIN_GET(x) (((uint16_t)(x) & WM8960_CLASSD3_DCGAIN_MASK) >> WM8960_CLASSD3_DCGAIN_SHIFT)

/*
 * ACGAIN (RW)
 *
 * AC Speaker Boost (Boosts speaker AC output
 * signal by up to 1.8 x on left and right channels)
 * 000 = 1.00x boost (+0dB)
 * 001 = 1.27x boost (+2.1dB)
 * 010 = 1.40x boost (+2.9dB)
 * 011 = 1.52x boost (+3.6dB)
 * 100 = 1.67x boost (+4.5dB)
 * 101 = 1.8x boost (+5.1dB)
 * 110 to 111 = Reserved
 */
#define WM8960_CLASSD3_ACGAIN_MASK (0x7U)
#define WM8960_CLASSD3_ACGAIN_SHIFT (0U)
#define WM8960_CLASSD3_ACGAIN_SET(x) (((uint16_t)(x) << WM8960_CLASSD3_ACGAIN_SHIFT) & WM8960_CLASSD3_ACGAIN_MASK)
#define WM8960_CLASSD3_ACGAIN_GET(x) (((uint16_t)(x) & WM8960_CLASSD3_ACGAIN_MASK) >> WM8960_CLASSD3_ACGAIN_SHIFT)

/* Bitfield definition for register: PLL1 */
/*
 * OPCLKDIV (RW)
 *
 * SYSCLK Output to GPIO Clock Division ratio
 * 000 = SYSCLK
 * 001 = SYSCLK / 2
 * 010 = SYSCLK / 3
 * 011 = SYSCLK / 4
 * 100 = SYSCLK / 5.5
 * 101 = SYSCLK / 6
 */
#define WM8960_PLL1_OPCLKDIV_MASK (0x1C0U)
#define WM8960_PLL1_OPCLKDIV_SHIFT (6U)
#define WM8960_PLL1_OPCLKDIV_SET(x) (((uint16_t)(x) << WM8960_PLL1_OPCLKDIV_SHIFT) & WM8960_PLL1_OPCLKDIV_MASK)
#define WM8960_PLL1_OPCLKDIV_GET(x) (((uint16_t)(x) & WM8960_PLL1_OPCLKDIV_MASK) >> WM8960_PLL1_OPCLKDIV_SHIFT)

/*
 * SDM (RW)
 *
 * Enable Integer Mode
 * 0 = Integer mode
 * 1 = Fractional mode
 */
#define WM8960_PLL1_SDM_MASK (0x20U)
#define WM8960_PLL1_SDM_SHIFT (5U)
#define WM8960_PLL1_SDM_SET(x) (((uint16_t)(x) << WM8960_PLL1_SDM_SHIFT) & WM8960_PLL1_SDM_MASK)
#define WM8960_PLL1_SDM_GET(x) (((uint16_t)(x) & WM8960_PLL1_SDM_MASK) >> WM8960_PLL1_SDM_SHIFT)

/*
 * PLLPRESCALE (RW)
 *
 * Divide MCLK by 2 before input to PLL
 * 0 = Divide by 1
 * 1 = Divide by 2
 */
#define WM8960_PLL1_PLLPRESCALE_MASK (0x10U)
#define WM8960_PLL1_PLLPRESCALE_SHIFT (4U)
#define WM8960_PLL1_PLLPRESCALE_SET(x) (((uint16_t)(x) << WM8960_PLL1_PLLPRESCALE_SHIFT) & WM8960_PLL1_PLLPRESCALE_MASK)
#define WM8960_PLL1_PLLPRESCALE_GET(x) (((uint16_t)(x) & WM8960_PLL1_PLLPRESCALE_MASK) >> WM8960_PLL1_PLLPRESCALE_SHIFT)

/*
 * PLLN (RW)
 *
 * Integer (N) part of PLL input/output frequency
 * ratio. Use values greater than 5 and less than 13
 */
#define WM8960_PLL1_PLLN_MASK (0xFU)
#define WM8960_PLL1_PLLN_SHIFT (0U)
#define WM8960_PLL1_PLLN_SET(x) (((uint16_t)(x) << WM8960_PLL1_PLLN_SHIFT) & WM8960_PLL1_PLLN_MASK)
#define WM8960_PLL1_PLLN_GET(x) (((uint16_t)(x) & WM8960_PLL1_PLLN_MASK) >> WM8960_PLL1_PLLN_SHIFT)

/* Bitfield definition for register: PLL2 */
/*
 * PLLK (RW)
 *
 * Fractional (K) part of PLL1 input/output
 * frequency ratio (treat as one 24-digit binary number).
 */
#define WM8960_PLL2_PLLK_MASK (0xFFU)
#define WM8960_PLL2_PLLK_SHIFT (0U)
#define WM8960_PLL2_PLLK_SET(x) (((uint16_t)(x) << WM8960_PLL2_PLLK_SHIFT) & WM8960_PLL2_PLLK_MASK)
#define WM8960_PLL2_PLLK_GET(x) (((uint16_t)(x) & WM8960_PLL2_PLLK_MASK) >> WM8960_PLL2_PLLK_SHIFT)

/* Bitfield definition for register: PLL3 */
/*
 * PLLK (RW)
 *
 * Fractional (K) part of PLL1 input/output
 * frequency ratio (treat as one 24-digit binary number).
 */
#define WM8960_PLL3_PLLK_MASK (0xFFU)
#define WM8960_PLL3_PLLK_SHIFT (0U)
#define WM8960_PLL3_PLLK_SET(x) (((uint16_t)(x) << WM8960_PLL3_PLLK_SHIFT) & WM8960_PLL3_PLLK_MASK)
#define WM8960_PLL3_PLLK_GET(x) (((uint16_t)(x) & WM8960_PLL3_PLLK_MASK) >> WM8960_PLL3_PLLK_SHIFT)

/* Bitfield definition for register: PLL4 */
/*
 * PLLK (RW)
 *
 * Fractional (K) part of PLL1 input/output
 * frequency ratio (treat as one 24-digit binary number).
 */
#define WM8960_PLL4_PLLK_MASK (0xFFU)
#define WM8960_PLL4_PLLK_SHIFT (0U)
#define WM8960_PLL4_PLLK_SET(x) (((uint16_t)(x) << WM8960_PLL4_PLLK_SHIFT) & WM8960_PLL4_PLLK_MASK)
#define WM8960_PLL4_PLLK_GET(x) (((uint16_t)(x) & WM8960_PLL4_PLLK_MASK) >> WM8960_PLL4_PLLK_SHIFT)


#endif /* _HPM_WM8960_REG_H_ */
