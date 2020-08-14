/*
 * Copyright (C) 2016 YunOS Project. All rights reserved.
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

#include <csi_config.h>
#include <soc.h>

extern void Default_Handler(void);
extern void SysTick_Handler(void);
extern void TIM4_NMIHandler(void);

void (*g_irqvector[48])(void);
void (*g_nmivector)(void);

void irq_vectors_init(void)
{
    int i;

    for (i = 0; i < 48; i++) {
        g_irqvector[i] = Default_Handler;
    }

    g_irqvector[CORET_IRQn] = SysTick_Handler;
    g_nmivector = TIM4_NMIHandler;
}
