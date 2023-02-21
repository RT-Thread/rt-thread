/**
  * @file  hal_sdhost.c
  * @author  ALLWINNERTECH IOT WLAN Team
  */

/*
 * Copyright (C) 2017 ALLWINNERTECH TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of ALLWINNERTECH TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, )|hhst->sdio_irq_maskPROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <hal_gpio.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef CONFIG_KERNEL_FREERTOS
#include <log.h>
#endif
#include "_sdhost.h"
#include "_sd_define.h"

#ifndef SDC_MAX_PIN_NUM
#define SDC_MAX_PIN_NUM   13
#endif

typedef struct
{
    uint32_t *pin;
    uint8_t pin_num : 3;
    uint8_t pin_mux : 3;
    uint8_t pin_drv : 2;
} sdmmc_pin_t;

static sdmmc_pin_t sunxi_sdmmc_pin[4];


int32_t sdmmc_pinctl_set_from_cfg(struct mmc_host *host, char *sdc_str, uint32_t pin_num)
{
#ifdef HAL_SetPin
    int32_t ret = 0;
    user_gpio_set_t gpiocfg[SDC_MAX_PIN_NUM] = {0};
    int i = 0;
    int gpio_num = 0;
    if (pin_num > SDC_MAX_PIN_NUM) {
        SDC_LOGE("pin num over %d\n", SDC_MAX_PIN_NUM);
        return ret;
    }

    ret = Hal_Cfg_GetGPIOSecData(sdc_str, gpiocfg, pin_num);
    if(ret < 0) {
        SDC_LOGE("%s not has pin setting on sys_config.fex\n", sdc_str);
        return ret;
    }

    for (i = 0;i < pin_num; i++) {
        SDC_LOGD("name %s,port %d,port_num %d,mul_sel %d, pull %d, drv_level %d\n",\
                gpiocfg[i].gpio_name, gpiocfg[i].port, gpiocfg[i].port_num, \
                gpiocfg[i].mul_sel, gpiocfg[i].pull, gpiocfg[i].drv_level);
    }

    for(i = 0; i< pin_num; i++ ) {
        gpio_num = (gpiocfg[i].port - 1) * PINS_PER_BANK + gpiocfg[i].port_num;
        ret = hal_gpio_pinmux_set_function(gpio_num, gpiocfg[i].mul_sel);
        if (ret) {
            SDC_LOGE(
                "[sdmmc %s] PIN%lu set function failed! return %d\n",
                sdc_str, gpio_num, ret);
            return -1;
        }

        ret = hal_gpio_set_driving_level(gpio_num, gpiocfg[i].drv_level);
        if (ret) {
            SDC_LOGE(
                "[sdmmc %s] PIN%lu set driving level failed! return %d\n",
                sdc_str, gpio_num, ret);
            return -1;
        }
        ret = hal_gpio_set_pull(gpio_num, gpiocfg[i].pull);
        if (ret) {
            SDC_LOGE(
                "[sdmmc %s] PIN%lu set driving level failed! return %d\n",
                sdc_str, gpio_num, ret);
            return -1;
        }
    }
    return ret;
#else
    SDC_LOGN("unsupport sys fex %d\n");
    return -1;
#endif
}


uint32_t sdmmc_pinctrl_init(struct mmc_host *host)
{
    uint8_t i;
    uint32_t flags = 0;
    int ret;
    uint32_t host_id = host->sdc_id;

    switch (host_id) {
        case 0:
            ret = sdmmc_pinctl_set_from_cfg(host, "sdc0", SDC0_NUM);
            if(ret < 0) {
                sunxi_sdmmc_pin[host_id].pin_num = SDC0_NUM;
                sunxi_sdmmc_pin[host_id].pin_mux = SDMMC_MUXSEL;
                sunxi_sdmmc_pin[host_id].pin_drv = SDMMC_DRVSEL;
                sunxi_sdmmc_pin[host_id].pin = malloc(sizeof(uint32_t) * SDC0_NUM);
                sunxi_sdmmc_pin[host_id].pin[0] = SDC0_CLK;
                sunxi_sdmmc_pin[host_id].pin[1] = SDC0_CMD;
                sunxi_sdmmc_pin[host_id].pin[2] = SDC0_D0;
                sunxi_sdmmc_pin[host_id].pin[3] = SDC0_D1;
                sunxi_sdmmc_pin[host_id].pin[4] = SDC0_D2;
                sunxi_sdmmc_pin[host_id].pin[5] = SDC0_D3;
                SDC_LOGE("sdmmc%ld use default pin setting\n", host_id);
            } else {
                SDC_LOGD("sdmmc%ld use pin setting on sys_config.fex\n", host_id);
                goto out;
            }
            break;
        case 1:
            if (host->param.pwr_mode == POWER_MODE_330) {
                hal_gpio_sel_vol_mode(SDC1_D0, POWER_MODE_330);
            } else {
                hal_gpio_sel_vol_mode(SDC1_D0, POWER_MODE_180);
            }
            ret = sdmmc_pinctl_set_from_cfg(host, "sdc1", SDC1_NUM);
            if(ret < 0) {
                            sunxi_sdmmc_pin[host_id].pin_num = SDC1_NUM;
                            sunxi_sdmmc_pin[host_id].pin_mux = SDMMC_MUXSEL;
                            sunxi_sdmmc_pin[host_id].pin_drv = SDMMC_DRVSEL;
                            sunxi_sdmmc_pin[host_id].pin = malloc(sizeof(uint32_t) * SDC1_NUM);
                            sunxi_sdmmc_pin[host_id].pin[0] = SDC1_CLK;
                            sunxi_sdmmc_pin[host_id].pin[1] = SDC1_CMD;
                            sunxi_sdmmc_pin[host_id].pin[2] = SDC1_D0;
                            // sunxi_sdmmc_pin[host_id].pin[3] = SDC1_D1;
                            // sunxi_sdmmc_pin[host_id].pin[4] = SDC1_D2;
                            // sunxi_sdmmc_pin[host_id].pin[5] = SDC1_D3;
                SDC_LOGE("sdmmc%ld use default pin setting\n", host_id);
            } else {
                SDC_LOGD("sdmmc%ld use pin setting on sys_config.fex\n", host_id);
                goto out;
            }
            break;
        default:
            SDC_LOGE("sdmmc%ld is invalid\n", host_id);
            return -1;

    }

    for (i = 0; i < sunxi_sdmmc_pin[host_id].pin_num; i++)
    {
        ret = hal_gpio_pinmux_set_function(sunxi_sdmmc_pin[host_id].pin[i], sunxi_sdmmc_pin[host_id].pin_mux);
        if (ret)
        {
            SDC_LOGE(
                "[sdmmc%ld] PIN%lu set function failed! return %d\n",
                host_id, sunxi_sdmmc_pin[host_id].pin[i], ret);
            return -1;
        }
        ret = hal_gpio_set_driving_level(sunxi_sdmmc_pin[host_id].pin[i], sunxi_sdmmc_pin[host_id].pin_drv);
        if (ret)
        {
            SDC_LOGE(
                "[sdmmc%ld] PIN%lu set driving level failed! return %d\n",
                host_id, sunxi_sdmmc_pin[host_id].pin[i], ret);
            return -1;
        }
        ret = hal_gpio_set_pull(sunxi_sdmmc_pin[host_id].pin[i], GPIO_PULL_UP);
        // ret = drv_gpio_set_pull_state(sunxi_sdmmc_pin[host_id].pin[i], DRV_GPIO_PULL_DOWN_DISABLE);
    }
out:
    return 0;
}

int mmc_gpiod_request_cd_irq(struct mmc_host *host)
{
    uint32_t irq;
    int ret = 0;
    gpio_pull_status_t pull_state;
    gpio_direction_t gpio_direction;
    gpio_data_t gpio_data;

    host->cd_gpio_pin = SDC0_DET;
    /*set gpio detect-clk 24M*/
    hal_gpio_set_debounce(host->cd_gpio_pin, 1);
    ret = hal_gpio_to_irq(host->cd_gpio_pin, &irq);
    if (ret < 0)
    {
        SDC_LOGE("gpio to irq error, error num: %d\n", ret);
        return ret;
    }

    /*set pin mux*/
    ret = hal_gpio_pinmux_set_function(host->cd_gpio_pin, 0);
    ret = hal_gpio_set_driving_level(host->cd_gpio_pin, 3);
    ret = hal_gpio_set_pull(host->cd_gpio_pin, 1);
    if (ret < 0)
    {
        SDC_LOGE("set pin mux error!\n");
        return -1;
    }

    host->cd_irq = irq;
    ret = hal_gpio_irq_request(irq, host->cd_gpio_isr, IRQ_TYPE_EDGE_BOTH, host);
    if (ret < 0)
    {
        SDC_LOGE("request irq error, irq num:%lu error num: %d\n", (unsigned long)irq, ret);
        return ret;
    }

#if 0
    ret = drv_gpio_irq_enable(irq);
    if (ret < 0)
    {
        printf("request irq error, error num: %d\n", ret);
        return ret;
    }
    ret = drv_gpio_irq_disable(irq);
    if (ret < 0)
    {
        printf("disable irq error, irq num:%lu,error num: %d\n", irq, ret);
        return ret;
    }

    ret = drv_gpio_irq_free(irq);
    if (ret < 0)
    {
        printf("free irq error, error num: %d\n", ret);
        return ret;
    }
#endif
    return ret;
}

