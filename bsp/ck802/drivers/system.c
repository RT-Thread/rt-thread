/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     system_PHOBOS.c
 * @brief    CSI Device System Source File for PHOBOS
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#include "soc.h"
#include "csi_core.h"
#include "config.h"

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
int SystemCoreClock = SYSTEM_CLOCK;  /* System Core Clock Frequency      */

extern int __Vectors;

void SystemCoreClockUpdate(void)
{
    SystemCoreClock = SYSTEM_CLOCK;
}

/**
  * @brief  initialize the system
  *         Initialize the psr and vbr.
  * @param  None
  * @return None
  */
void SystemInit(void)
{
    /* Here we may setting exception vector, MGU, cache, and so on. */
#ifdef CONFIG_SYSTEM_SECURE
    __set_PSR(0xc0000140);
#else
    __set_PSR(0x80000140);
#endif
    __set_VBR((uint32_t) & (__Vectors));

    drv_coret_config(200 * 1000, CORET_IRQn);    //10ms
    drv_nvic_enable_irq(CORET_IRQn);

    SystemCoreClock = SYSTEM_CLOCK;
}
