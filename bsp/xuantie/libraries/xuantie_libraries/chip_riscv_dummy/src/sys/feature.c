 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <csi_core.h>

/* I/D Cache will enable in cache_init */
void cpu_features_init(void)
{
#if CONFIG_CPU_XUANTIE_E901PLUS_CP || CONFIG_CPU_XUANTIE_E901PLUS_B_CP || CONFIG_CPU_XUANTIE_E901PLUS_M_CP || CONFIG_CPU_XUANTIE_E901PLUS_BM_CP
    return;
#endif

#if CONFIG_CPU_XUANTIE_E901_CP || CONFIG_CPU_XUANTIE_E901_B_CP || CONFIG_CPU_XUANTIE_E901_ZM_CP || CONFIG_CPU_XUANTIE_E901_BZM_CP
    return;
#endif

#if CONFIG_CPU_XUANTIE_E902 || CONFIG_CPU_XUANTIE_E902M || CONFIG_CPU_XUANTIE_E902T || CONFIG_CPU_XUANTIE_E902MT
    return;
#endif

#if CONFIG_CPU_XUANTIE_E906 || CONFIG_CPU_XUANTIE_E906F || CONFIG_CPU_XUANTIE_E906FD || CONFIG_CPU_XUANTIE_E906P || CONFIG_CPU_XUANTIE_E906FP || CONFIG_CPU_XUANTIE_E906FDP
    rv_csr_write(CSR_MXSTATUS, 0x440800);
    rv_csr_write(CSR_MHCR, 0x103f & (~0x3));
    return;
#endif

#if CONFIG_CPU_XUANTIE_E907 || CONFIG_CPU_XUANTIE_E907F || CONFIG_CPU_XUANTIE_E907FD || CONFIG_CPU_XUANTIE_E907P || CONFIG_CPU_XUANTIE_E907FP || CONFIG_CPU_XUANTIE_E907FDP
    rv_csr_write(CSR_MXSTATUS, 0x440800);
    rv_csr_write(CSR_MHINT, 0x600c);
    rv_csr_write(CSR_MHCR, 0x103f & (~0x3));
    return;
#endif

    volatile unsigned int i, cpu_type, cpu_ver, cpu_tnmodel;
    unsigned long version[8];

    /* As CPUID is a fifo register, try to find
     * the CPUID[0] whose index(bit[31:28]) == 0  */
    for (i = 0; i < 8; i++)
    {
        version[0] = rv_csr_read(CSR_MCPUID);
        if (((version[0]&0xf0000000) >> 28) == 0)
            break;
    }

    for (i = 1; i < 8; i++)
        version[i] = rv_csr_read(CSR_MCPUID);

    cpu_type    = (version[0] >> 18) & 0xf;
    cpu_tnmodel = (version[0] >> 14) & 0x1;
    cpu_ver     = (version[1] >> 12) & 0xffff;

    rv_csr_write(CSR_MCOR, 0x70013);

    /*
     * Warning: CSR_MCCR2 contains an L2 cache latency setting,
     * you need to confirm it by your own soc design.
     */
    switch (cpu_type)
    {
    case 0x1:
        if (cpu_ver >= 0x0)
        {
            rv_csr_write(CSR_MSMPR, 0x1);
            rv_csr_write(CSR_MCCR2, 0xe249000b);
            rv_csr_write(CSR_MXSTATUS, 0x638000);
            rv_csr_write(CSR_MHINT, 0x1ee30c);
            rv_csr_write(CSR_MHCR, 0x11ff & (~0x3));
            rv_csr_write(CSR_MHINT2,0x180);
        } else {
            while(1);
        }
        break;
    case 0x2:
        if (cpu_ver >= 0x0)
        {
            rv_csr_write(CSR_MSMPR, 0x1);
            rv_csr_write(CSR_MCCR2, 0xa042000a);
            rv_csr_write(CSR_MXSTATUS, 0x438100);
            rv_csr_write(CSR_MHINT, 0x21aa10c);
            rv_csr_write(CSR_MHCR, 0x10011ff & (~0x3));
            rv_csr_write(CSR_MHINT4, 0x10000080);
#if __riscv_xlen == 64
            rv_csr_write(CSR_MENVCFG, 0x4000000000000000);
#endif
        } else {
            while(1);
        }
        break;
    case 0x3:
        if (cpu_ver >= 0x1080 && cpu_ver <= 0x10bf)
        { /* 1.2.0~1.2.x */
            rv_csr_write(CSR_MCCR2, 0xe0010009);
            rv_csr_write(CSR_MXSTATUS, 0x638000);
            rv_csr_write(CSR_MHINT, 0x6e30c);
            rv_csr_write(CSR_MHCR, 0x1ff & (~0x3));
        } else if (cpu_ver == 0x10ca)
        { /* 1.3.10 */
            rv_csr_write(CSR_MSMPR, 0x1);
            rv_csr_write(CSR_MCCR2, 0xe2490009);
            rv_csr_write(CSR_MXSTATUS, 0x638000);
            rv_csr_write(CSR_MHINT, 0x66e30c);
            rv_csr_write(CSR_MHCR, 0x17f & (~0x3));
            rv_csr_write(CSR_MHINT2, 0x420000);
            rv_csr_write(CSR_MHINT4, 0x410);
        } else if (cpu_ver >= 0x1100 && cpu_ver <= 0x113f)
        { /* 1.4.0~1.4.x */
            rv_csr_write(CSR_MSMPR, 0x1);
            rv_csr_write(CSR_MCCR2, 0xe2490009);
            rv_csr_write(CSR_MXSTATUS, 0x638000);
            rv_csr_write(CSR_MHINT, 0x16e30c);
            rv_csr_write(CSR_MHCR, 0x1ff & (~0x3));
        } else if (cpu_ver >= 0x1140 && cpu_ver <= 0x117f)
        { /* 1.5.0~1.5.x */
            rv_csr_write(CSR_MSMPR, 0x1);
            rv_csr_write(CSR_MCCR2, 0xe2490009);
            rv_csr_write(CSR_MXSTATUS, 0x638000);
            rv_csr_write(CSR_MHINT, 0xe6e30c);
            rv_csr_write(CSR_MHINT2, 0x180);
            rv_csr_write(CSR_MHCR, 0x1ff & (~0x3));
        } else if (cpu_ver >= 0x1180 && cpu_ver <= 0x1183)
        { /* 1.6.0~1.6.3 */
            rv_csr_write(CSR_MSMPR, 0x1);
            rv_csr_write(CSR_MCCR2, 0xe249000b);
            rv_csr_write(CSR_MXSTATUS, 0x638000);
            rv_csr_write(CSR_MHINT, 0x1ee30c);
            rv_csr_write(CSR_MHINT2, 0x180);
            rv_csr_write(CSR_MHCR, 0x1ff & (~0x3));
        } else if (cpu_ver >= 0x1184 && cpu_ver <= 0x123f)
        { /* 1.6.4~1.8.x */
            rv_csr_write(CSR_MSMPR, 0x1);
            rv_csr_write(CSR_MCCR2, 0xe249000b);
            rv_csr_write(CSR_MXSTATUS, 0x638000);
            rv_csr_write(CSR_MHINT, 0x1ee30c);
            rv_csr_write(CSR_MHINT2, 0x180);
            rv_csr_write(CSR_MHCR, 0x11ff & (~0x3));
        } else if (cpu_ver >= 0x2000 && cpu_ver <= 0x200e)
        { /* 2.0.0~2.0.14 */
            rv_csr_write(CSR_MSMPR, 0x1);
            rv_csr_write(CSR_MCCR2, 0xe249000b);
            rv_csr_write(CSR_MXSTATUS, 0x438000);
            rv_csr_write(CSR_MHINT, 0x31ea32c);
            rv_csr_write(CSR_MHINT2, 0x180);
            rv_csr_write(CSR_MHCR, 0x11ff & (~0x3));
#if __riscv_xlen == 64
            rv_csr_write(CSR_MENVCFG, 0x4000000000000000);
#endif
        } else if (cpu_ver >= 0x200f && cpu_ver <= 0x2045)
        { /* 2.0.15~2.1.5 */
            rv_csr_write(CSR_MSMPR, 0x1);
            rv_csr_write(CSR_MCCR2, 0xe249000b);
            rv_csr_write(CSR_MXSTATUS, 0x438000);
            rv_csr_write(CSR_MHINT, 0x11ea32c);
            rv_csr_write(CSR_MHINT2, 0x180);
            rv_csr_write(CSR_MHCR, 0x11ff & (~0x3));
#if __riscv_xlen == 64
            rv_csr_write(CSR_MENVCFG, 0x4000000000000000);
#endif
        } else if (cpu_ver >= 0x2046 && cpu_ver <= 0x20c3)
        { /* 2.1.6~2.3.3 */
            rv_csr_write(CSR_MSMPR, 0x1);
            rv_csr_write(CSR_MCCR2, 0xe249000b);
            rv_csr_write(CSR_MXSTATUS, 0x438000);
            rv_csr_write(CSR_MHINT, 0x31ea32c);
            rv_csr_write(CSR_MHINT2, 0x180);
            rv_csr_write(CSR_MHCR, 0x11ff & (~0x3));
#if __riscv_xlen == 64
            rv_csr_write(CSR_MENVCFG, 0x4000000000000000);
#endif
        } else if (cpu_ver >= 0x20c4 && cpu_ver <= 0x2fff)
        { /* 2.3.4~2.x.x */
            rv_csr_write(CSR_MSMPR, 0x1);
            rv_csr_write(CSR_MCCR2, 0xe249000b);
            rv_csr_write(CSR_MXSTATUS, 0x438100);
            rv_csr_write(CSR_MHINT, 0x31ea32c);
            rv_csr_write(CSR_MHINT2, 0x180);
            rv_csr_write(CSR_MHCR, 0x11ff & (~0x3));
            rv_csr_write(CSR_MHINT4, 0x2080);
#if __riscv_xlen == 64
            rv_csr_write(CSR_MENVCFG, 0x4000000000000000);
#endif
        } else if (cpu_ver >= 0x3000 && cpu_ver <= 0x3fff)
        { /* 3.0.0~3.x.x */
            rv_csr_write(CSR_MSMPR, 0x1);
            rv_csr_write(CSR_MCCR2, 0xe249000b);
            rv_csr_write(CSR_MXSTATUS, 0x438100);
            rv_csr_write(CSR_MHINT, 0x31ea32c);
            rv_csr_write(CSR_MHINT2, 0x180);
            rv_csr_write(CSR_MHCR, 0x11ff & (~0x3));
            rv_csr_write(CSR_MHINT4, 0x2080);
#if __riscv_xlen == 64
            rv_csr_write(CSR_MENVCFG, 0x4000000000000000);
#endif
        } else {
            while(1);
        }
        break;
    case 0x4:
        if (cpu_ver >= 0x1002 && cpu_ver <= 0xffff)
        {
            rv_csr_write(CSR_MHCR, 0x17f & (~0x3));
            rv_csr_write(CSR_MXSTATUS, 0x638000);
            rv_csr_write(CSR_MHINT, 0x650c);
        } else {
            while(1);
        }
        break;
    case 0x5:
        if(cpu_tnmodel == 0)
        { /* c908 */
            if (cpu_ver >= 0x0000 && cpu_ver <= 0x0007)
            { /* 0.0.0~0.0.7 */
                rv_csr_write(CSR_MSMPR, 0x1);
                rv_csr_write(CSR_MCCR2, 0xe0420008);
                rv_csr_write(CSR_MXSTATUS, 0x638000);
                rv_csr_write(CSR_MHINT, 0x2c50c);
                rv_csr_write(CSR_MHCR, 0x11ff & (~0x3));
            } else if (cpu_ver >= 0x0040 && cpu_ver <= 0x1002)
            { /* 0.1.0~1.0.2 */
                rv_csr_write(CSR_MSMPR, 0x1);
                rv_csr_write(CSR_MCCR2, 0xa042000a);
                rv_csr_write(CSR_MXSTATUS, 0x438000);
                rv_csr_write(CSR_MHINT, 0x21aa10c);
                rv_csr_write(CSR_MHCR, 0x10011ff & (~0x3));
#if __riscv_xlen == 64
                rv_csr_write(CSR_MENVCFG, 0x4000000000000000);
#endif
            } else if (cpu_ver >= 0x1003 && cpu_ver <= 0x100b)
            { /* 1.0.3~1.0.11 */

                rv_csr_write(CSR_MSMPR, 0x1);
                rv_csr_write(CSR_MCCR2, 0xa042000a);
                rv_csr_write(CSR_MXSTATUS, 0x438000);
                rv_csr_write(CSR_MHINT, 0x1aa10c);
                rv_csr_write(CSR_MHCR, 0x10011ff & (~0x3));
#if __riscv_xlen == 64
                rv_csr_write(CSR_MENVCFG, 0x4000000000000000);
#endif
            } else if (cpu_ver >= 0x100c && cpu_ver <= 0x1fff)
            { /* 1.0.12~ */
                rv_csr_write(CSR_MSMPR, 0x1);
                rv_csr_write(CSR_MCCR2, 0xa042000a);
                rv_csr_write(CSR_MXSTATUS, 0x438100);
                rv_csr_write(CSR_MHINT, 0x21aa10c);
                rv_csr_write(CSR_MHCR, 0x10011ff & (~0x3));
                rv_csr_write(CSR_MHINT4, 0x10000080);
#if __riscv_xlen == 64
                rv_csr_write(CSR_MENVCFG, 0x4000000000000000);
#endif
            } else if (cpu_ver >= 0x2000 && cpu_ver <= 0xffff)
            { /* 2.0.0~ */
                rv_csr_write(CSR_MSMPR, 0x1);
                rv_csr_write(CSR_MCCR2, 0xa042000a);
                rv_csr_write(CSR_MXSTATUS, 0x438100);
                rv_csr_write(CSR_MHINT, 0x21aa10c);
                rv_csr_write(CSR_MHCR, 0x10011ff & (~0x3));
                rv_csr_write(CSR_MHINT4, 0x10000080);
#if __riscv_xlen == 64
                rv_csr_write(CSR_MENVCFG, 0x4000000000000000);
#endif
            } else {
                while(1);
            }
        } else if (cpu_tnmodel == 1)
        {
            if (cpu_ver >= 0x0)
            {
                rv_csr_write(CSR_MSMPR, 0x1);
                rv_csr_write(CSR_MCCR2, 0xA0420002);
                rv_csr_write(CSR_MXSTATUS, 0x438100);
                rv_csr_write(CSR_MHINT, 0x21AA10C);
                rv_csr_write(CSR_MHCR, 0x10011FF & (~0x3));
                rv_csr_write(CSR_MHINT4, 0x10000080);
#if __riscv_xlen == 64
                rv_csr_write(CSR_MENVCFG, 0x4000000000000000);
#endif
            } else {
                while(1);
            }
        } else {
            while(1);
        }
        break;
    case 0x6:
        if (cpu_ver >= 0x0)
        {
            rv_csr_write(CSR_MSMPR, 0x1);
            rv_csr_write(CSR_MCCR2, 0xA0420002);
            rv_csr_write(CSR_MXSTATUS, 0x438000);
            rv_csr_write(CSR_MHINT, 0x3A1AA10C);
            rv_csr_write(CSR_MHCR, 0x10011BF & (~0x3));
#if __riscv_xlen == 64
            rv_csr_write(CSR_MENVCFG, 0x4000000000000000);
#endif
        } else {
            while(1);
        }
        break;
    default:
        /* FIXME: maybe qemu */
        break;
    }
}

