/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_WM8978_REG_H_
#define _HPM_WM8978_REG_H_

/* Define the register address of WM8978 */
#define WM8978_RESET                   0x00U    /* software reset */
#define WM8978_POWER_MANAGET_1         0x01U    /* power managet 1 */
#define WM8978_POWER_MANAGET_2         0x02U    /* power managet 2 */
#define WM8978_POWER_MANAGET_3         0x03U    /* power managet 3 */
#define WM8978_AUDIO_INTERFACE         0x04U   /* audio interface */
#define WM8978_CLOCK_GEN_CTRL          0x06U   /* clock gen ctrl */
#define WM8978_GPIO_CTRL               0x08U   /* GPIO ctrl */
#define WM8978_DAC_CTRL                0x0AU   /* DAC ctrl */
#define WM8978_LEFT_DAC_VOL            0x0BU   /* Left DAC digital vol */
#define WM8978_RIGHT_DAC_VOL           0x0CU   /* Right DAC digital vol  */
#define WM8978_ADC_CONTROL             0x0EU   /* ADC control */
#define WM8978_LEFT_ADC_VOL            0x0FU   /* Left ADC digital vol */
#define WM8978_RIGHT_ADC_VOL           0x10U   /* Right ADC digital vol  */
#define WM8978_NOTCH_FILTER1           0x1BU   /* notch filter1 */
#define WM8978_NOTCH_FILTER2           0x1CU   /* notch filter2 */
#define WM8978_NOTCH_FILTER3           0x1DU   /* notch filter3 */
#define WM8978_NOTCH_FILTER4           0x1EU   /* notch filter4 */
#define WM8978_ALC_CONTROL1            0x20U   /* ALC control1 */
#define WM8978_ALC_CONTROL2            0x21U   /* ALC control2 */
#define WM8978_ALC_CONTROL3            0x22U   /* ALC control3 */
#define WM8978_NOISE_GATE              0x23U   /* noise Gate */
#define WM8978_BEEP_CONTROL            0x2BU   /* beep control */
#define WM8978_INPUT_CTRL              0x2CU   /* input ctrl */
#define WM8978_LOUT1_VOLUME_CTRL       0x34U   /* LOUT1 (HP)volume ctrl */
#define WM8978_ROUT1_VOLUME_CTRL       0x35U   /* ROUT1 (HP)volume ctrl */
#define WM8978_LOUT2_VOLUME_CTRL       0x36U   /* LOUT2 (SPK)volume ctrl */
#define WM8978_ROUT2_VOLUME_CTRL       0x37U   /* ROUT2 (SPK)volume ctrl */
#define WM8978_LINP_PGA_GAIM_CTRL      0x2DU   /* Left INP PGA gain ctrl */
#define WM8978_RINP_PGA_GAIM_CTRL      0x2EU   /* Right INP PGA gain ctrl */
#define WM8978_LADC_BOOST_CTRL         0x2FU   /* Left INP PGA gain ctrl */
#define WM8978_RADC_BOOST_CTRL         0x30U   /* Right INP PGA gain ctrl */
#define WM8978_OUTPUT_CTRL             0x31U   /* Output ctrl */
#define WM8978_LEFT_MIXER_CTRL         0x32U   /* left mixer ctrl */
#define WM8978_RIGHT_MIXER_CTRL        0x33U   /* right mixer ctrl */
#define WM8978_OUT3_MIXER_CTRL         0x38U   /* out3 mixer ctrl */
#define WM8978_OUT4_MIXER_CTRL         0x39U   /* out4 mixer ctrl */

/*
 * BUFDCOPEN (RW)
 * Dedicated buffer for DC level shifting output stages when in 1.5x gain boost configuration
 */
#define WM8978_BUFDCOPEN_R1_MASK   (0x100U)
#define WM8978_BUFDCOPEN_R1_SHIFT  (8U)
#define WM8978_BUFDCOPEN_R1_SET(x) (((uint16_t)(x) << WM8978_BUFDCOPEN_R1_SHIFT) & WM8978_BUFDCOPEN_R1_MASK)
#define WM8978_BUFDCOPEN_R1_GET(x) (((uint16_t)(x) & WM8978_BUFDCOPEN_R1_MASK) >> WM8978_BUFDCOPEN_R1_SHIFT)

/*
 * OUT4MIXEN (RW)
 * OUT4 mixer enable
 */
#define WM8978_OUT4MIXEN_R1_MASK   (0x80U)
#define WM8978_OUT4MIXEN_R1_SHIFT  (7U)
#define WM8978_OUT4MIXEN_R1_SET(x) (((uint16_t)(x) << WM8978_OUT4MIXEN_R1_SHIFT) & WM8978_OUT4MIXEN_R1_MASK)
#define WM8978_OUT4MIXEN_R1_GET(x) (((uint16_t)(x) & WM8978_OUT4MIXEN_R1_MASK) >> WM8978_OUT4MIXEN_R1_SHIFT)

/*
 * OUT3MIXEN (RW)
 * OUT3 mixer enable
 */
#define WM8978_OUT3MIXEN_R1_MASK   (0x40U)
#define WM8978_OUT3MIXEN_R1_SHIFT  (6U)
#define WM8978_OUT3MIXEN_R1_SET(x) (((uint16_t)(x) << WM8978_OUT3MIXEN_R1_SHIFT) & WM8978_OUT3MIXEN_R1_MASK)
#define WM8978_OUT3MIXEN_R1_GET(x) (((uint16_t)(x) & WM8978_OUT3MIXEN_R1_MASK) >> WM8978_OUT3MIXEN_R1_SHIFT)

/*
 * PLLEN (RW)
 * PLL enable
 */
#define WM8978_PLLEN_R1_MASK   (0x20U)
#define WM8978_PLLEN_R1_SHIFT  (5U)
#define WM8978_PLLEN_R1_SET(x) (((uint16_t)(x) << WM8978_PLLEN_R1_SHIFT) & WM8978_PLLEN_R1_MASK)
#define WM8978_PLLEN_R1_GET(x) (((uint16_t)(x) & WM8978_PLLEN_R1_MASK) >> WM8978_PLLEN_R1_SHIFT)

/*
 * MICBEN (RW)
 * Microphone Bias Enable
 */
#define WM8978_MICBEN_R1_MASK   (0x10U)
#define WM8978_MICBEN_R1_SHIFT  (4U)
#define WM8978_MICBEN_R1_SET(x) (((uint16_t)(x) << WM8978_MICBEN_R1_SHIFT) & WM8978_MICBEN_R1_MASK)
#define WM8978_MICBEN_R1_GET(x) (((uint16_t)(x) & WM8978_MICBEN_R1_MASK) >> WM8978_MICBEN_R1_SHIFT)

/*
 * BIASEN (RW)
 * Analogue amplifier bias control
 */
#define WM8978_BIASEN_R1_MASK   (0x08U)
#define WM8978_BIASEN_R1_SHIFT  (3U)
#define WM8978_BIASEN_R1_SET(x) (((uint16_t)(x) << WM8978_BIASEN_R1_SHIFT) & WM8978_BIASEN_R1_MASK)
#define WM8978_BIASEN_R1_GET(x) (((uint16_t)(x) & WM8978_BIASEN_R1_MASK) >> WM8978_BIASEN_R1_SHIFT)


/*
 * BUFIOEN (RW)
 * Unused input/output tie off buffer enable
 */
#define WM8978_BUFIOEN_R1_MASK   (0x04U)
#define WM8978_BUFIOEN_R1_SHIFT  (2U)
#define WM8978_BUFIOEN_R1_SET(x) (((uint16_t)(x) << WM8978_BUFIOEN_R1_SHIFT) & WM8978_BUFIOEN_R1_MASK)
#define WM8978_BUFIOEN_R1_GET(x) (((uint16_t)(x) & WM8978_BUFIOEN_R1_MASK) >> WM8978_BUFIOEN_R1_SHIFT)

/*
 * VMIDSEL (RW)
 * Reference string impedance to VMID pin
 */
#define WM8978_VMIDSEL_R1_MASK   (0x03U)
#define WM8978_VMIDSEL_R1_SHIFT  (0U)
#define WM8978_VMIDSEL_R1_SET(x) (((uint16_t)(x) << WM8978_VMIDSEL_R1_SHIFT) & WM8978_VMIDSEL_R1_MASK)
#define WM8978_VMIDSEL_R1_GET(x) (((uint16_t)(x) & WM8978_VMIDSEL_R1_MASK) >> WM8978_VMIDSEL_R1_SHIFT)

/*
 * ROUT1EN (RW)
 * ROUT1 output enable
 */
#define WM8978_ROUT1EN_R2_MASK   (0x100U)
#define WM8978_ROUT1EN_R2_SHIFT  (8U)
#define WM8978_ROUT1EN_R2_SET(x) (((uint16_t)(x) << WM8978_ROUT1EN_R2_SHIFT) & WM8978_ROUT1EN_R2_MASK)
#define WM8978_ROUT1EN_R2_GET(x) (((uint16_t)(x) & WM8978_ROUT1EN_R2_MASK) >> WM8978_ROUT1EN_R2_SHIFT)

/*
 * LOUT1EN (RW)
 * LOUT1 output enable
 */
#define WM8978_LOUT1EN_R2_MASK   (0x80U)
#define WM8978_LOUT1EN_R2_SHIFT  (7U)
#define WM8978_LOUT1EN_R2_SET(x) (((uint16_t)(x) << WM8978_LOUT1EN_R2_SHIFT) & WM8978_LOUT1EN_R2_MASK)
#define WM8978_LOUT1EN_R2_GET(x) (((uint16_t)(x) & WM8978_LOUT1EN_R2_MASK) >> WM8978_LOUT1EN_R2_SHIFT)

/*
 * SLEEP (RW)
 * residual current reduced in device standby mode if 1
 */
#define WM8978_SLEEP_R2_MASK   (0x40U)
#define WM8978_SLEEP_R2_SHIFT  (6U)
#define WM8978_SLEEP_R2_SET(x) (((uint16_t)(x) << WM8978_SLEEP_R2_SHIFT) & WM8978_SLEEP_R2_MASK)
#define WM8978_SLEEP_R2_GET(x) (((uint16_t)(x) & WM8978_SLEEP_R2_MASK) >> WM8978_SLEEP_R2_SHIFT)

/*
 * BOOSTENR (RW)
 * Right channel Input BOOST enable
 */
#define WM8978_BOOSTENR_R2_MASK   (0x20U)
#define WM8978_BOOSTENR_R2_SHIFT  (5U)
#define WM8978_BOOSTENR_R2_SET(x) (((uint16_t)(x) << WM8978_BOOSTENR_R2_SHIFT) & WM8978_BOOSTENR_R2_MASK)
#define WM8978_BOOSTENR_R2_GET(x) (((uint16_t)(x) & WM8978_BOOSTENR_R2_MASK) >> WM8978_BOOSTENR_R2_SHIFT)

/*
 * BOOSTENL (RW)
 * Left channel Input BOOST enable
 */
#define WM8978_BOOSTENL_R2_MASK   (0x10U)
#define WM8978_BOOSTENL_R2_SHIFT  (4U)
#define WM8978_BOOSTENL_R2_SET(x) (((uint16_t)(x) << WM8978_BOOSTENL_R2_SHIFT) & WM8978_BOOSTENL_R2_MASK)
#define WM8978_BOOSTENL_R2_GET(x) (((uint16_t)(x) & WM8978_BOOSTENL_R2_MASK) >> WM8978_BOOSTENL_R2_SHIFT)

/*
 * INPPGAENR (RW)
 * Right channel input PGA enable
 */
#define WM8978_INPPGAENR_R2_MASK   (0x08U)
#define WM8978_INPPGAENR_R2_SHIFT  (3U)
#define WM8978_INPPGAENR_R2_SET(x) (((uint16_t)(x) << WM8978_INPPGAENR_R2_SHIFT) & WM8978_INPPGAENR_R2_MASK)
#define WM8978_INPPGAENR_R2_GET(x) (((uint16_t)(x) & WM8978_INPPGAENR_R2_MASK) >> WM8978_INPPGAENR_R2_SHIFT)


/*
 * INPPGAENL (RW)
 * Left channel input PGA enable
 */
#define WM8978_INPPGAENL_R2_MASK   (0x04U)
#define WM8978_INPPGAENL_R2_SHIFT  (2U)
#define WM8978_INPPGAENL_R2_SET(x) (((uint16_t)(x) << WM8978_INPPGAENL_R2_SHIFT) & WM8978_INPPGAENL_R2_MASK)
#define WM8978_INPPGAENL_R2_GET(x) (((uint16_t)(x) & WM8978_INPPGAENL_R2_MASK) >> WM8978_INPPGAENL_R2_SHIFT)

/*
 * ADCENR (RW)
 * Enable ADC right channel
 */
#define WM8978_ADCENR_R2_MASK   (0x02U)
#define WM8978_ADCENR_R2_SHIFT  (1U)
#define WM8978_ADCENR_R2_SET(x) (((uint16_t)(x) << WM8978_ADCENR_R2_SHIFT) & WM8978_ADCENR_R2_MASK)
#define WM8978_ADCENR_R2_GET(x) (((uint16_t)(x) & WM8978_ADCENR_R2_MASK) >> WM8978_ADCENR_R2_SHIFT)

/*
 * ADCENL (RW)
 * Enable ADC left channel
 */
#define WM8978_ADCENL_R2_MASK   (0x01U)
#define WM8978_ADCENL_R2_SHIFT  (0U)
#define WM8978_ADCENL_R2_SET(x) (((uint16_t)(x) << WM8978_ADCENL_R2_SHIFT) & WM8978_ADCENL_R2_MASK)
#define WM8978_ADCENL_R2_GET(x) (((uint16_t)(x) & WM8978_ADCENL_R2_MASK) >> WM8978_ADCENL_R2_SHIFT)

/*
 * MBVSEL (RW)
 * Microphone Bias Voltage Control
 */
#define WM8978_OUT4EN_R3_MASK   (0x100U)
#define WM8978_OUT4EN_R3_SHIFT  (8U)
#define WM8978_OUT4EN_R3_SET(x) (((uint16_t)(x) << WM8978_OUT4EN_R3_SHIFT) & WM8978_OUT4EN_R3_MASK)
#define WM8978_OUT4EN_R3_GET(x) (((uint16_t)(x) & WM8978_OUT4EN_R3_MASK) >> WM8978_OUT4EN_R3_SHIFT)

/*
 * OUT3EN (RW)
 * OUT3 enable
 */
#define WM8978_OUT3EN_R3_MASK   (0x80U)
#define WM8978_OUT3EN_R3_SHIFT  (7U)
#define WM8978_OUT3EN_R3_SET(x) (((uint16_t)(x) << WM8978_OUT3EN_R3_SHIFT) & WM8978_OUT3EN_R3_MASK)
#define WM8978_OUT3EN_R3_GET(x) (((uint16_t)(x) & WM8978_OUT3EN_R3_MASK) >> WM8978_OUT3EN_R3_SHIFT)

/*
 * LOUT2EN (RW)
 * LOUT2 enable
 */
#define WM8978_LOUT2EN_R3_MASK   (0x40U)
#define WM8978_LOUT2EN_R3_SHIFT  (6U)
#define WM8978_LOUT2EN_R3_SET(x) (((uint16_t)(x) << WM8978_LOUT2EN_R3_SHIFT) & WM8978_LOUT2EN_R3_MASK)
#define WM8978_LOUT2EN_R3_GET(x) (((uint16_t)(x) & WM8978_LOUT2EN_R3_MASK) >> WM8978_LOUT2EN_R3_SHIFT)

/*
 * ROUT2EN (RW)
 * ROUT2 enable
 */
#define WM8978_ROUT2EN_R3_MASK   (0x20U)
#define WM8978_ROUT2EN_R3_SHIFT  (5U)
#define WM8978_ROUT2EN_R3_SET(x) (((uint16_t)(x) << WM8978_ROUT2EN_R3_SHIFT) & WM8978_ROUT2EN_R3_MASK)
#define WM8978_ROUT2EN_R3_GET(x) (((uint16_t)(x) & WM8978_ROUT2EN_R3_MASK) >> WM8978_ROUT2EN_R3_SHIFT)

/*
 * RMIXEN (RW)
 * Right output channel mixer enable
 */
#define WM8978_RMIXEN_R3_MASK   (0x08U)
#define WM8978_RMIXEN_R3_SHIFT  (3U)
#define WM8978_RMIXEN_R3_SET(x) (((uint16_t)(x) << WM8978_RMIXEN_R3_SHIFT) & WM8978_RMIXEN_R3_MASK)
#define WM8978_RMIXEN_R3_GET(x) (((uint16_t)(x) & WM8978_RMIXEN_R3_MASK) >> WM8978_RMIXEN_R3_SHIFT)

/*
 * LMIXEN (RW)
 * Left output channel mixer enable
 */
#define WM8978_LMIXEN_R3_MASK   (0x04U)
#define WM8978_LMIXEN_R3_SHIFT  (2U)
#define WM8978_LMIXEN_R3_SET(x) (((uint16_t)(x) << WM8978_LMIXEN_R3_SHIFT) & WM8978_LMIXEN_R3_MASK)
#define WM8978_LMIXEN_R3_GET(x) (((uint16_t)(x) & WM8978_LMIXEN_R3_MASK) >> WM8978_LMIXEN_R3_SHIFT)

/*
 * DACENR (RW)
 * Right channel DAC enable
 */
#define WM8978_DACENR_R3_MASK   (0x02U)
#define WM8978_DACENR_R3_SHIFT  (1U)
#define WM8978_DACENR_R3_SET(x) (((uint16_t)(x) << WM8978_DACENR_R3_SHIFT) & WM8978_DACENR_R3_MASK)
#define WM8978_DACENR_R3_GET(x) (((uint16_t)(x) & WM8978_DACENR_R3_MASK) >> WM8978_DACENR_R3_SHIFT)

/*
 * DACENL (RW)
 * Left channel DAC enable
 */
#define WM8978_DACENL_R3_MASK   (0x01U)
#define WM8978_DACENL_R3_SHIFT  (0U)
#define WM8978_DACENL_R3_SET(x) (((uint16_t)(x) << WM8978_DACENL_R3_SHIFT) & WM8978_DACENL_R3_MASK)
#define WM8978_DACENL_R3_GET(x) (((uint16_t)(x) & WM8978_DACENL_R3_MASK) >> WM8978_DACENL_R3_SHIFT)

/*
 * HPFEN (RW)
 * High Pass Filter Enable
 */
#define WM8978_HPFEN_R14_MASK   (0x100U)
#define WM8978_HPFEN_R14_SHIFT  (8U)
#define WM8978_HPFEN_R14_SET(x) (((uint16_t)(x) << WM8978_HPFEN_R14_SHIFT) & WM8978_HPFEN_R14_MASK)
#define WM8978_HPFEN_R14_GET(x) (((uint16_t)(x) & WM8978_HPFEN_R14_MASK) >> WM8978_HPFEN_R14_SHIFT)

/*
 * ADCOSR128 (RW)
 * ADC oversample rate select
 */
#define WM8978_ADCOSR128_R14_MASK   (0x08U)
#define WM8978_ADCOSR128_R14_SHIFT  (3U)
#define WM8978_ADCOSR128_R14_SET(x) (((uint16_t)(x) << WM8978_ADCOSR128_R14_SHIFT) & WM8978_ADCOSR128_R14_MASK)
#define WM8978_ADCOSR128_R14_GET(x) (((uint16_t)(x) & WM8978_ADCOSR128_R14_MASK) >> WM8978_ADCOSR128_R14_SHIFT)

/*
 * ADCRPOL (RW)
 * ADC right channel polarity adjust
 */
#define WM8978_ADCRPOL_R14_MASK   (0x02U)
#define WM8978_ADCRPOL_R14_SHIFT  (1U)
#define WM8978_ADCRPOL_R14_SET(x) (((uint16_t)(x) << WM8978_ADCRPOL_R14_SHIFT) & WM8978_ADCRPOL_R14_MASK)
#define WM8978_ADCRPOL_R14_GET(x) (((uint16_t)(x) & WM8978_ADCRPOL_R14_MASK) >> WM8978_ADCRPOL_R14_SHIFT)

/*
 * ADCLPOL (RW)
 * ADC left channel polarity adjust
 */
#define WM8978_ADCLPOL_R14_MASK   (0x01U)
#define WM8978_ADCLPOL_R14_SHIFT  (0U)
#define WM8978_ADCLPOL_R14_SET(x) (((uint16_t)(x) << WM8978_ADCLPOL_R14_SHIFT) & WM8978_ADCLPOL_R14_MASK)
#define WM8978_ADCLPOL_R14_GET(x) (((uint16_t)(x) & WM8978_ADCLPOL_R14_MASK) >> WM8978_ADCLPOL_R14_SHIFT)

/*
 * MBVSEL (RW)
 * Microphone Bias Voltage Control
 */
#define WM8978_MBVSEL_R44_MASK   (0x100U)
#define WM8978_MBVSEL_R44_SHIFT  (8U)
#define WM8978_MBVSEL_R44_SET(x) (((uint16_t)(x) << WM8978_MBVSEL_R44_SHIFT) & WM8978_MBVSEL_R44_MASK)
#define WM8978_MBVSEL_R44_GET(x) (((uint16_t)(x) & WM8978_MBVSEL_R44_MASK) >> WM8978_MBVSEL_R44_SHIFT)

/*
 * R2_2INPPGA (RW)
 * Connect R2 pin to right channel input PGA positive terminal
 */
#define WM8978_R2_2INPPGA_R44_MASK   (0x40U)
#define WM8978_R2_2INPPGA_R44_SHIFT  (6U)
#define WM8978_R2_2INPPGA_R44_SET(x) (((uint16_t)(x) << WM8978_R2_2INPPGA_R44_SHIFT) & WM8978_R2_2INPPGA_R44_MASK)
#define WM8978_R2_2INPPGA_R44_GET(x) (((uint16_t)(x) & WM8978_R2_2INPPGA_R44_MASK) >> WM8978_R2_2INPPGA_R44_SHIFT)

/*
 * RIN2INPPGA (RW)
 * Connect RIN pin to right channel input PGA negative terminaL
 */
#define WM8978_RIN2INPPGA_R44_MASK   (0x20U)
#define WM8978_RIN2INPPGA_R44_SHIFT  (5U)
#define WM8978_RIN2INPPGA_R44_SET(x) (((uint16_t)(x) << WM8978_RIN2INPPGA_R44_SHIFT) & WM8978_RIN2INPPGA_R44_MASK)
#define WM8978_RIN2INPPGA_R44_GET(x) (((uint16_t)(x) & WM8978_RIN2INPPGA_R44_MASK) >> WM8978_RIN2INPPGA_R44_SHIFT)

/*
 * RIP2INPPGA (RW)
 * Connect RIP pin to right channel input PGA amplifier positive terminal
 */
#define WM8978_RIP2INPPGA_R44_MASK   (0x10U)
#define WM8978_RIP2INPPGA_R44_SHIFT  (4U)
#define WM8978_RIP2INPPGA_R44_SET(x) (((uint16_t)(x) << WM8978_RIP2INPPGA_R44_SHIFT) & WM8978_RIP2INPPGA_R44_MASK)
#define WM8978_RIP2INPPGA_R44_GET(x) (((uint16_t)(x) & WM8978_RIP2INPPGA_R44_MASK) >> WM8978_RIP2INPPGA_R44_SHIFT)

/*
 * L2_2INPPGA (RW)
 * Connect L2 pin to left channel input PGA positive terminal
 */
#define WM8978_L2_2INPPGA_R44_MASK   (0x04U)
#define WM8978_L2_2INPPGA_R44_SHIFT  (2U)
#define WM8978_L2_2INPPGA_R44_SET(x) (((uint16_t)(x) << WM8978_L2_2INPPGA_R44_SHIFT) & WM8978_L2_2INPPGA_R44_MASK)
#define WM8978_L2_2INPPGA_R44_GET(x) (((uint16_t)(x) & WM8978_L2_2INPPGA_R44_MASK) >> WM8978_L2_2INPPGA_R44_SHIFT)

/*
 * LIN2INPPGA (RW)
 * Connect LIN pin to left channel input PGA negative terminal
 */
#define WM8978_LIN2INPPGA_R44_MASK   (0x02U)
#define WM8978_LIN2INPPGA_R44_SHIFT  (1U)
#define WM8978_LIN2INPPGA_R44_SET(x) (((uint16_t)(x) << WM8978_LIN2INPPGA_R44_SHIFT) & WM8978_LIN2INPPGA_R44_MASK)
#define WM8978_LIN2INPPGA_R44_GET(x) (((uint16_t)(x) & WM8978_LIN2INPPGA_R44_MASK) >> WM8978_LIN2INPPGA_R44_SHIFT)

/*
 * DACENL (RW)
 * Connect LIP pin to left channel input PGA amplifier positive terminal
 */
#define WM8978_LIP2INPPGA_R44_MASK   (0x01U)
#define WM8978_LIP2INPPGA_R44_SHIFT  (0U)
#define WM8978_LIP2INPPGA_R44_SET(x) (((uint16_t)(x) << WM8978_LIP2INPPGA_R44_SHIFT) & WM8978_LIP2INPPGA_R44_MASK)
#define WM8978_LIP2INPPGA_R44_GET(x) (((uint16_t)(x) & WM8978_LIP2INPPGA_R44_MASK) >> WM8978_LIP2INPPGA_R44_SHIFT)

/*
 * BCP (RW)
 * BCLK polarity
 * for 0x04 reg
 */
#define WM8978_BCP_MASK   (0x100U)
#define WM8978_BCP_SHIFT  (8U)
#define WM8978_BCP_SET(x) (((uint16_t)(x) << WM8978_BCP_SHIFT) & WM8978_BCP_MASK)
#define WM8978_BCP_GET(x) (((uint16_t)(x) & WM8978_BCP_MASK) >> WM8978_BCP_SHIFT)

/*
 * LRP (RW)
 * LRC clock polarity
 * for 0x04 reg
 */
#define WM8978_LRP_MASK   (0x80U)
#define WM8978_LRP_SHIFT  (7U)
#define WM8978_LRP_SET(x) (((uint16_t)(x) << WM8978_LRP_SHIFT) & WM8978_LRP_MASK)
#define WM8978_LRP_GET(x) (((uint16_t)(x) & WM8978_LRP_MASK) >> WM8978_LRP_SHIFT)

/*
 * WL (RW)
 * word length
 * for 0x04 reg
 */
#define WM8978_WL_MASK   (0x60U)
#define WM8978_WL_SHIFT  (5U)
#define WM8978_WL_SET(x) (((uint16_t)(x) << WM8978_WL_SHIFT) & WM8978_WL_MASK)
#define WM8978_WL_GET(x) (((uint16_t)(x) & WM8978_WL_MASK) >> WM8978_WL_SHIFT)

/*
 * FMT (RW)
 * addio interface data format select
 * for 0x04 reg
 */
#define WM8978_FMT_MASK   (0x18U)
#define WM8978_FMT_SHIFT  (3U)
#define WM8978_FMT_SET(x) (((uint16_t)(x) << WM8978_FMT_SHIFT) & WM8978_FMT_MASK)
#define WM8978_FMT_GET(x) (((uint16_t)(x) & WM8978_FMT_MASK) >> WM8978_FMT_SHIFT)

/*
 * DACLRSWAP (RW)
 * Controls whether DAC data appears in 'right'orleft’ phases of LRC clock
 * for 0x04 reg
 */
#define WM8978_DACLRSWAP_MASK   (0x04U)
#define WM8978_DACLRSWAP_SHIFT  (2U)
#define WM8978_DACLRSWAP_SET(x) (((uint16_t)(x) << WM8978_DACLRSWAP_SHIFT) & WM8978_DACLRSWAP_MASK)
#define WM8978_DACLRSWAP_GET(x) (((uint16_t)(x) & WM8978_DACLRSWAP_MASK) >> WM8978_DACLRSWAP_SHIFT)

/*
 * ADCLRSWAP (RW)
 * Controls whether ADC data appears in 'right' orleft’ phases of LRC clock
 * for 0x04 reg
 */
#define WM8978_ADCLRSWAP_MASK   (0x02U)
#define WM8978_ADCLRSWAP_SHIFT  (1U)
#define WM8978_ADCLRSWAP_SET(x) (((uint16_t)(x) << WM8978_ADCLRSWAP_SHIFT) & WM8978_ADCLRSWAP_MASK)
#define WM8978_ADCLRSWAP_GET(x) (((uint16_t)(x) & WM8978_ADCLRSWAP_MASK) >> WM8978_ADCLRSWAP_SHIFT)

/*
 * MONO (RW)
 * Selects between stereo and mono deviceoperation
 * for 0x04 reg
 */
#define WM8978_MONO_MASK   (0x01U)
#define WM8978_MONO_SHIFT  (0U)
#define WM8978_MONO_SET(x) (((uint16_t)(x) << WM8978_MONO_SHIFT) & WM8978_MONO_MASK)
#define WM8978_MONO_GET(x) (((uint16_t)(x) & WM8978_MONO_MASK) >> WM8978_MONO_SHIFT)

/*
 * ROUTVOL (RW)
 *
 * OUT Volume
 * 000000 = -57dB
 * 111001 = 0dB
 * 111111 = 6dB
 * for 0x34/0x35/0x36/0x37 regs
 */
#define WM8978_OUT_VOLUME_MASK (0x7FU)
#define WM8978_OUT_VOLUME_SHIFT (0U)
#define WM8978_OUT_VOLUME_SET(x) (((uint16_t)(x) << WM8978_OUT_VOLUME_SHIFT) & WM8978_OUT_VOLUME_MASK)
#define WM8978_OUT_VOLUME_GET(x) (((uint16_t)(x) & WM8978_OUT_VOLUME_MASK) >> WM8978_OUT_VOLUME_SHIFT)

/*
 * OUT_SPKVU (RW)
 * LOUT1/2 and ROUT1/2 volumes do not update untila 1 is written to SPKkVU
 * for 0x34/0x35/0x36/0x37 regs
 */
#define WM8978_OUT_SPKVU_MASK (0x100U)
#define WM8978_OUT_SPKVU_SHIFT (8U)
#define WM8978_OUT_SPKVU_SET(x) (((uint16_t)(x) << WM8978_OUT_SPKVU_SHIFT) & WM8978_OUT_SPKVU_MASK)
#define WM8978_OUT_SPKVU_GET(x) (((uint16_t)(x) & WM8978_OUT_SPKVU_MASK) >> WM8978_OUT_SPKVU_SHIFT)

/*
 * OUT_MUTE (RW)
 * LOUT1/2 and ROUT1/2 headphone output mute
 * for 0x34/0x35/0x36/0x37 regs
 */
#define WM8978_OUT_MUTE_MASK (0x40U)
#define WM8978_OUT_MUTE_SHIFT (6U)
#define WM8978_OUT_MUTE_SET(x) (((uint16_t)(x) << WM8978_OUT_MUTE_SHIFT) & WM8978_OUT_MUTE_MASK)
#define WM8978_OUT_MUTE_GET(x) (((uint16_t)(x) & WM8978_OUT_MUTE_MASK) >> WM8978_OUT_MUTE_SHIFT)

/*
 * INPGA_UPDATE (RW)
 * inpga update
 * for 0x45/0x46 regs
 */
#define WM8978_INPGA_UPDATE_MASK (0x100U)
#define WM8978_INPGA_UPDATE_SHIFT (8U)
#define WM8978_INPGA_UPDATE_SET(x) (((uint16_t)(x) << WM8978_INPGA_UPDATE_SHIFT) & WM8978_INPGA_UPDATE_MASK)
#define WM8978_INPGA_UPDATE_GET(x) (((uint16_t)(x) & WM8978_INPGA_UPDATE_MASK) >> WM8978_INPGA_UPDATE_SHIFT)

/*
 * NPPGAZCR/L (RW)
 * Left/Right channel input PGA zero cross enable
 * for 0x45/0x46 regs
 */
#define WM8978_NP_PGA_ZC_MASK (0x80U)
#define WM8978_NP_PGA_ZC_SHIFT (7U)
#define WM8978_NP_PGA_ZC_SET(x) (((uint16_t)(x) << WM8978_NP_PGA_ZC_SHIFT) & WM8978_NP_PGA_ZC_MASK)
#define WM8978_NP_PGA_ZC_GET(x) (((uint16_t)(x) & WM8978_NP_PGA_ZC_MASK) >> WM8978_NP_PGA_ZC_SHIFT)

/*
 * NPPGA_MUTEL (RW)
 * Mute control for left/right channel input PGA
 * for 0x45/0x46 regs
 */
#define WM8978_INPPGA_MUTEL_MASK (0x40U)
#define WM8978_INPPGA_MUTEL_SHIFT (6U)
#define WM8978_INPPGA_MUTEL_SET(x) (((uint16_t)(x) << WM8978_INPPGA_MUTEL_SHIFT) & WM8978_INPPGA_MUTEL_MASK)
#define WM8978_INPPGA_MUTEL_GET(x) (((uint16_t)(x) & WM8978_INPPGA_MUTEL_MASK) >> WM8978_INPPGA_MUTEL_SHIFT)

/*
 * INPPGA_VOL (RW)
 * Left/Right channel input PGA volume
 * for 0x2d/0x2e regs
 */
#define WM8978_INPPGA_VOL_MASK (0x3FU)
#define WM8978_INPPGA_VOL_SHIFT (0U)
#define WM8978_INPPGA_VOL_SET(x) (((uint16_t)(x) << WM8978_INPPGA_VOL_SHIFT) & WM8978_INPPGA_VOL_MASK)
#define WM8978_INPPGA_VOL_GET(x) (((uint16_t)(x) & WM8978_INPPGA_VOL_MASK) >> WM8978_INPPGA_VOL_SHIFT)

/*
 * PGABOOST (RW)
 * Boost enable for left/right channel input PGA
 * for 0x2f/0x30 regs
 */
#define WM8978_PGABOOST_MASK (0x100U)
#define WM8978_PGABOOST_SHIFT (8U)
#define WM8978_PGABOOST_SET(x) (((uint16_t)(x) << WM8978_PGABOOST_SHIFT) & WM8978_PGABOOST_MASK)
#define WM8978_PGABOOST_GET(x) (((uint16_t)(x) & WM8978_PGABOOST_MASK) >> WM8978_PGABOOST_SHIFT)

/*
 * LR2_2BOOSTVOL (RW)
 * Controls the L2 pin to the left/right channel input
 * for 0x2f/0x30 regs
 */
#define WM8978_2_2_BOOSTVOL_MASK (0x70U)
#define WM8978_2_2_BOOSTVOL_SHIFT (4U)
#define WM8978_2_2_BOOSTVOL_SET(x) (((uint16_t)(x) << WM8978_2_2_BOOSTVOL_SHIFT) & WM8978_2_2_BOOSTVOL_MASK)
#define WM8978_2_2_BOOSTVOL_GET(x) (((uint16_t)(x) & WM8978_2_2_BOOSTVOL_MASK) >> WM8978_2_2_BOOSTVOL_SHIFT)

/*
 * AUXL2BOOSTVOL (RW)
 * Controls the auxiliary amplifer to the left/right channelinput boost stage
 * for 0x2f/0x30 regs
 */
#define WM8978_AUXL2BOOSTVOL_MASK (0x07U)
#define WM8978_AUXL2BOOSTVOL_SHIFT (0U)
#define WM8978_AUXL2BOOSTVOL_SET(x) (((uint16_t)(x) << WM8978_AUXL2BOOSTVOL_SHIFT) & WM8978_AUXL2BOOSTVOL_MASK)
#define WM8978_AUXL2BOOSTVOL_GET(x) (((uint16_t)(x) & WM8978_AUXL2BOOSTVOL_MASK) >> WM8978_AUXL2BOOSTVOL_SHIFT)
#endif

