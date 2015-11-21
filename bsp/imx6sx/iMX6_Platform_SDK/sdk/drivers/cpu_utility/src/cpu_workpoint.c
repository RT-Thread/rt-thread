/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*----------------------------------------------------------------------------
		File Includes
----------------------------------------------------------------------------*/
#include "sdk.h"
#include "cpu_utility/cpu_utility.h"
#include "core/cortex_a9.h"
#include "core/mmu.h"
#include "pmu/pmu_driver.h"
#include "registers/regsccm.h"
#include "registers/regsccmanalog.h"
#include "registers/regspmu.h"

typedef struct cpu_wp_s {
    uint32_t cpu_freq;          // MHz
    uint32_t vdd_pu;            //mV
    uint32_t vdd_soc;           //mV
    uint32_t vdd_arm;           //mV
} cpu_wp_t;

static cpu_wp_t mx6_cpu_wp[] = {
    {
     .cpu_freq = 1200,
     .vdd_pu = 1275,
     .vdd_soc = 1275,
     .vdd_arm = 1275,
     },
    {
     .cpu_freq = 996,
     .vdd_pu = 1250,
     .vdd_soc = 1250,
     .vdd_arm = 1250,
     },
    {
     .cpu_freq = 792,
     .vdd_pu = 1175,
     .vdd_soc = 1175,
     .vdd_arm = 1150,
     },
    {
     .cpu_freq = 396,
     .vdd_pu = 1175,
     .vdd_soc = 1175,
     .vdd_arm = 950,
     },
};

uint32_t cpu_workpoint_set(cpu_wp_e cpu_wp_mode)
{
    unsigned int div = 0;

    if (cpu_wp_mode >= CPU_WORKPOINT_OUTOFRANGE) {
        printf("CPU work point mode not exist !!\n");
        return 0;
    }

    cpu_wp_t *wp = &mx6_cpu_wp[cpu_wp_mode];

    pmu_init();

    /* calculate the pll loop divider. target Fout = Fin * div / 2 */
    div = wp->cpu_freq * 2 / 24;

    /* first, switch the cpu clock root to step clock */
    HW_CCM_CCSR.B.PLL1_SW_CLK_SEL = 1;

    /* set clock to target frequency */
    HW_CCM_ANALOG_PLL_ARM.B.POWERDOWN = 1;
    HW_CCM_ANALOG_PLL_ARM.B.DIV_SELECT = div;
    HW_CCM_ANALOG_PLL_ARM.B.POWERDOWN = 0;
    while (!HW_CCM_ANALOG_PLL_ARM.B.LOCK) ;
    HW_CCM_ANALOG_PLL_ARM.B.BYPASS = 0;

    /* set the power rail */
    switch (wp->cpu_freq) {
    case 1200:
    case 996:
    case 792:
    case 396:
        pmu_set_property(kPMURegulator_ArmCore, kPMUProperty_OutputMillivolts, &wp->vdd_arm);
        pmu_set_property(kPMURegulator_Graphics, kPMUProperty_OutputMillivolts, &wp->vdd_pu);
        pmu_set_property(kPMURegulator_SoC, kPMUProperty_OutputMillivolts, &wp->vdd_soc);
        break;
    default:
        printf("Unsupported CPU workpoint mode!!\n");
        return 0;
    }

    /*switch back to PLL1 */
    HW_CCM_CCSR.B.PLL1_SW_CLK_SEL = 0;

    return wp->cpu_freq;
}
