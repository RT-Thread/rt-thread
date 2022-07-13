/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file drv_dac.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */

#include <rtdbg.h>
#include "drv_dac.h"
#include "board.h"

#ifdef RT_USING_DAC

#if defined(BSP_USING_DAC1) || defined(BSP_USING_DAC2)
    /* this driver can be disabled at menuconfig -> Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable DAC */


static struct n32_dac_config dac_config[] =
{
#ifdef BSP_USING_DAC1
    {
        "dac1",
        DAC_CHANNEL_1,
    },
#endif
    
#ifdef BSP_USING_DAC2
    {
        "dac2",
        DAC_CHANNEL_2,
    },
#endif
};


static struct n32_dac dac_obj[sizeof(dac_config) / sizeof(dac_config[0])];

static void n32_dac_init(struct n32_dac_config *config)
{
    DAC_InitType DAC_InitStructure;

    /* DAC Periph clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_DAC, ENABLE);
    /* DAC channel Configuration */
    DAC_InitStructure.Trigger          = DAC_TRG_SOFTWARE;
    DAC_InitStructure.WaveGen          = DAC_WAVEGEN_NOISE;
    DAC_InitStructure.LfsrUnMaskTriAmp = DAC_UNMASK_LFSRBIT0;
    DAC_InitStructure.BufferOutput     = DAC_BUFFOUTPUT_ENABLE;
    DAC_Init(config->dac_periph, &DAC_InitStructure);
}

static rt_err_t n32_dac_enabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    RT_ASSERT(device != RT_NULL);
    
    DAC_Enable(channel, ENABLE);
    
    return RT_EOK;
}

static rt_err_t n32_dac_disabled(struct rt_dac_device *device, rt_uint32_t channel)
{    
    RT_ASSERT(device != RT_NULL);
    
    DAC_Enable(channel, DISABLE);
    return RT_EOK;
}


static rt_err_t n32_set_dac_value(struct rt_dac_device *device, rt_uint32_t channel, rt_uint32_t *value)
{    
    RT_ASSERT(device != RT_NULL);    
    rt_uint16_t set_value = 0;
    set_value = (rt_uint16_t)*value;
    
    if(set_value > 4096)
    {
        set_value = 4096;
    }
    
    /* Start DAC Channel conversion by software */
    if(channel == DAC_CHANNEL_1)
    {
        DAC_SetCh1Data(DAC_ALIGN_R_12BIT, set_value);
        DAC_SoftTrgEnable(DAC_CHANNEL_1, ENABLE);
    }
    else
    {
        DAC_SetCh2Data(DAC_ALIGN_R_12BIT, set_value);
        DAC_SoftTrgEnable(DAC_CHANNEL_2, ENABLE);
    }

    return RT_EOK;
}

static const struct rt_dac_ops n32_dac_ops =
{
    .disabled = n32_dac_disabled,
    .enabled  = n32_dac_enabled,
    .convert  = n32_set_dac_value,
};


int rt_hw_dac_init(void)
{
    int result = RT_EOK;
    /* save dac name */
    char name_buf[5] = {'d', 'a', 'c', '0', 0};
    int i = 0;

    for (i = 0; i < sizeof(dac_config) / sizeof(dac_config[0]); i++)
    {
        /* dac init */
        name_buf[3] = '0';
        dac_obj[i].config = &dac_config[i];
#if defined(BSP_USING_DAC1)        
        if (dac_obj[i].config->dac_periph == DAC_CHANNEL_1)
        {
            name_buf[3] = '1';
        }
        GPIOInit(GPIOA, GPIO_Mode_AIN, GPIO_Speed_50MHz, GPIO_PIN_4);
#endif
#if defined(BSP_USING_DAC2)
        if (dac_obj[i].config->dac_periph == DAC_CHANNEL_2)
        {
            name_buf[3] = '2';
        }
        GPIOInit(GPIOA, GPIO_Mode_AIN, GPIO_Speed_50MHz, GPIO_PIN_5);
#endif
        
        /* register dac device */
        for (i = 0; i < sizeof(dac_obj) / sizeof(dac_obj[0]); i++)
        {
            n32_dac_init(&dac_config[i]);
            if (rt_hw_dac_register(&dac_obj[i].dac_device, name_buf, &n32_dac_ops, &dac_obj[i].config->dac_periph) == RT_EOK)
            {
                LOG_D("%s init success", name_buf);
            }
            else
            {
                LOG_E("%s register failed", name_buf);
                result = -RT_ERROR;
            }
        }       
    }

    return result;
}
INIT_DEVICE_EXPORT(rt_hw_dac_init);

#endif /* defined(BSP_USING_DAC1) || defined(BSP_USING_DAC2) */
#endif /* RT_USING_DAC */
