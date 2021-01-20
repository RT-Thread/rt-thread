/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-25     RT-Thread    the first version
 */

#ifndef __DRV_AC97_H__
#define __DRV_AC97_H__

/* Register offsets */
#define AC97_RESET				0x00
#define AC97_MASTER				0x02
#define AC97_HEADPHONE			0x04
#define AC97_MASTER_MONO		0x06
#define AC97_MASTER_TONE		0x08
#define AC97_PC_BEEP			0x0A    //mixer volume
#define AC97_PHONE				0x0C
#define AC97_MIC				0x0E    //qwert db
#define AC97_LINE				0x10		
#define AC97_CD					0x12
#define AC97_VIDEO				0x14
#define AC97_AUX				0x16
#define AC97_PCM				0x18
#define AC97_REC_SEL			0x1A	//0 represent mic
#define AC97_REC_GAIN			0x1C
#define AC97_REC_GAIN_MIC		0x1E
#define AC97_GENERAL_PURPOSE	0x20
#define AC97_3D_CONTROL			0x22
#define AC97_INT_PAGING			0x24    //qwert
#define AC97_POWERDOWN			0x26
#define AC97_PCM_FRONT_DAC_RATE 0x2c	/* PCM Front DAC Rate */
#define AC97_PCM_SURR_DAC_RATE	0x2e	/* PCM Surround DAC Rate */
#define AC97_PCM_LFE_DAC_RATE	0x30	/* PCM LFE DAC Rate */
#define AC97_PCM_LR_ADC_RATE	0x32	/* PCM LR ADC Rate */
#define AC97_PCM_MIC_ADC_RATE	0x34	/* PCM MIC ADC Rate */
#define AC97_DAC_SLOT_MAP		0x6C
#define AC97_ADC_SLOT_MAP		0x6E

void ac97_reset(void);
rt_err_t ac97_set_vol(int vol);
int ac97_get_vol(void);
rt_err_t ac97_set_rate(int rate);
int ac97_get_rate(void);

#endif
