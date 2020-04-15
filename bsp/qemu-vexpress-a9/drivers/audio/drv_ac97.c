/*
 * File      : drv_ac97.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-25     RT-Thread    the first version
 */

#include <rtthread.h>
#include <rthw.h>
#include "drv_pl041.h"
#include "drv_ac97.h"

void ac97_reset(void)
{
    aaci_ac97_write(AC97_RESET, 0xFFFF);
}

rt_err_t ac97_set_vol(int vol)
{
    rt_uint16_t tmp = vol | (vol << 8);

    if (vol < 0 || vol > 0x3f)
    {
        return -RT_ERROR;
    }

    aaci_ac97_write(AC97_MASTER, tmp);
    aaci_ac97_write(AC97_HEADPHONE, tmp);
    aaci_ac97_write(AC97_MASTER_MONO, tmp);
    aaci_ac97_write(AC97_PCM, tmp);

    return RT_EOK;
}

int ac97_get_vol(void)
{
    rt_uint16_t v;

    v = aaci_ac97_read(AC97_MASTER);
    if (v == (~0x0))
    {
        v = 0;
    }
    return 0x3F & v;
}

rt_err_t ac97_set_rate(int rate)
{
    if (rate < 0)
    {
        return -RT_ERROR;
    }
    aaci_ac97_write(AC97_PCM_FRONT_DAC_RATE, rate);
    return 0;
}

int ac97_get_rate(void)
{
    rt_uint16_t v;

    v = aaci_ac97_read(AC97_PCM_FRONT_DAC_RATE);
    if (v == (~0x0))
    {
        v = 0;
    }
    return v;
}

#if 0
#define AC97_DUMP(_v)    rt_kprintf("%32s:addr:0x%08x data:0x%08x\n", #_v, (_v), (aaci_ac97_read(_v)))
int _ac97_reg_dump(int argc, char **argv)
{
    AC97_DUMP(AC97_RESET);
    AC97_DUMP(AC97_MASTER);
    AC97_DUMP(AC97_HEADPHONE);
    AC97_DUMP(AC97_MASTER_MONO);
    AC97_DUMP(AC97_MASTER_TONE);
    AC97_DUMP(AC97_PC_BEEP);
    AC97_DUMP(AC97_PHONE);
    AC97_DUMP(AC97_MIC);
    AC97_DUMP(AC97_LINE);
    AC97_DUMP(AC97_CD);
    AC97_DUMP(AC97_VIDEO);
    AC97_DUMP(AC97_AUX);
    AC97_DUMP(AC97_PCM);
    AC97_DUMP(AC97_REC_SEL);
    AC97_DUMP(AC97_REC_GAIN);
    AC97_DUMP(AC97_REC_GAIN_MIC);
    AC97_DUMP(AC97_GENERAL_PURPOSE);
    AC97_DUMP(AC97_3D_CONTROL);
    AC97_DUMP(AC97_INT_PAGING);
    AC97_DUMP(AC97_POWERDOWN);
    AC97_DUMP(AC97_PCM_FRONT_DAC_RATE);
    AC97_DUMP(AC97_PCM_SURR_DAC_RATE);
    AC97_DUMP(AC97_PCM_LFE_DAC_RATE);
    AC97_DUMP(AC97_PCM_LR_ADC_RATE);
    AC97_DUMP(AC97_PCM_MIC_ADC_RATE);
    AC97_DUMP(AC97_DAC_SLOT_MAP);
    AC97_DUMP(AC97_ADC_SLOT_MAP);
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(_ac97_reg_dump, __cmd_ac97_dump, ac97 dump reg.);

#endif
