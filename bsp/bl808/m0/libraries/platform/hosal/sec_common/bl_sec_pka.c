/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <FreeRTOS.h>
#include <semphr.h>

#include <bl_sec.h>
#include "bl_sec_hw_common.h"

static StaticSemaphore_t pka_mutex_buf;
static SemaphoreHandle_t pka_mutex = NULL;

int bl_sec_pka_init(void)
{
#if defined(BL616) || defined BL808
    GLB_Set_PKA_CLK_Sel(GLB_PKA_CLK_MCU_MUXPLL_160M);
#elif defined(BL702L)
    GLB_Set_PKA_CLK_Sel(GLB_PKA_CLK_SRC_HCLK);
#else
    GLB_Set_PKA_CLK_Sel(GLB_PKA_CLK_HCLK);
#endif

    pka_mutex = xSemaphoreCreateMutexStatic(&pka_mutex_buf);
    if (pka_mutex) {
        return 0;
    } else {
        return -1;
    }
}

int bl_sec_pka_mutex_take(void)
{
    if (pdPASS != xSemaphoreTake(pka_mutex, portMAX_DELAY)) {
        return -1;
    }
    return 0;
}

int bl_sec_pka_mutex_give(void)
{
    if (pdPASS != xSemaphoreGive(pka_mutex)) {
        return -1;
    }
    return 0;
}
