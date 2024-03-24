/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-24     Oxlm         first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "fsl_dac.h"

#ifdef RT_USING_DAC

// #define DRV_DEBUG
#define DBG_TAG "drv.dac"
#ifdef DRV_DEBUG
#define DBG_LVL DBG_LOG
#else
#define DBG_LVL DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>

struct mcx_dac {
  struct rt_dac_device mcxn_dac_device;
  LPDAC_Type *dac_base;
  clock_attach_id_t clock_attach_id;
  clock_div_name_t clock_div_name;
  uint8_t clock_div;
  uint8_t referenceVoltageSource; /* kDAC_ReferenceVoltageSourceAlt1, VREFH reference pin */
  char *name;
};

static struct mcx_dac mcx_dac_obj[] = {
#ifdef BSP_USING_DAC0
    {
        .dac_base               = DAC0,
        .clock_attach_id        = kFRO_HF_to_DAC0,
        .clock_div_name         = kCLOCK_DivDac0Clk,
        .clock_div              = 1u,
        .referenceVoltageSource = kDAC_ReferenceVoltageSourceAlt1,
        .name                   = "dac0",
    },
#endif

};

rt_err_t mcxn_dac_disabled(struct rt_dac_device *device, rt_uint32_t channel) {
  RT_ASSERT(device != RT_NULL);
  struct mcx_dac *dac = (struct mcx_dac *)device->parent.user_data;

  DAC_Deinit(dac->dac_base);
  return RT_EOK;
}

rt_err_t mcxn_dac_enabled(struct rt_dac_device *device, rt_uint32_t channel) {
  RT_ASSERT(device != RT_NULL);
  struct mcx_dac *dac = (struct mcx_dac *)device->parent.user_data;
  dac_config_t dacConfigStruct;

  DAC_GetDefaultConfig(&dacConfigStruct);
  dacConfigStruct.referenceVoltageSource = dac->referenceVoltageSource;
  DAC_Init(dac->dac_base, &dacConfigStruct);
  DAC_Enable(dac->dac_base, RT_TRUE);

  return RT_EOK;
}

rt_err_t mcxn_dac_write(struct rt_dac_device *device, rt_uint32_t channel, rt_uint32_t *value) {
  RT_ASSERT(device != RT_NULL);
  struct mcx_dac *dac = (struct mcx_dac *)device->parent.user_data;

  DAC_SetData(dac->dac_base, *value);
  return RT_EOK;
}

struct rt_dac_ops mcxn_dac_ops = {
    .disabled = mcxn_dac_disabled,
    .enabled  = mcxn_dac_enabled,
    .convert  = mcxn_dac_write,
};

static int mcxn_dac_init(void) {
  int i;
  int dac_num = sizeof(mcx_dac_obj) / sizeof(struct mcx_dac);

#ifdef BSP_USING_DAC0
  /* enable DAC0 and VREF */
  SPC0->ACTIVE_CFG1 |= 0x11;
#endif

  for (i = 0; i < dac_num; i++) {
    CLOCK_SetClkDiv(mcx_dac_obj[i].clock_div_name, mcx_dac_obj[i].clock_div);
    CLOCK_AttachClk(mcx_dac_obj[i].clock_attach_id);

    if (RT_EOK != rt_hw_dac_register(&mcx_dac_obj[i].mcxn_dac_device, mcx_dac_obj[i].name, &mcxn_dac_ops,
                                     (void *)(mcx_dac_obj + i))) {
      LOG_E("%s register failed", mcx_dac_obj[i].name);
      return -RT_ERROR;
    }
  }

  return RT_EOK;
}
INIT_DEVICE_EXPORT(mcxn_dac_init);

#endif
