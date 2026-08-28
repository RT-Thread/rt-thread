/*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mem_layout.h"

#define csr_read_num(num)                               \
    ({                                                  \
        unsigned long __v;                              \
        __asm__ volatile("csrr %0, " #num : "=r"(__v)); \
        __v;                                            \
    })

#define csr_write_num(num, val)                             \
    do                                                      \
    {                                                       \
        unsigned long __v = (unsigned long)(val);           \
        __asm__ volatile("csrw " #num ", %0" : : "r"(__v)); \
    } while (0)

/* satp mode encodings */
#define SATP_MODE_SV39 8
#define SATP_MODE_SV57 10

void m_mode_init(void)
{
    unsigned long v;

    /* ------------------------------------------------------------------
     * 1. T-Head extended state (MXSTATUS 0x7c0):
     *    +THEADISAEE(22) +MM(15, unaligned access), -MAEE(21, keep the
     *    standard Svpbmt PTE format)
     * ------------------------------------------------------------------ */
    v = csr_read_num(0x7c0);
    v |= (1UL << 22) | (1UL << 15);
    v &= ~(1UL << 21);
    csr_write_num(0x7c0, v);

    /* ------------------------------------------------------------------
     * 2. Cache init: invalidate all (MCOR 0x7c2), enable I/D/branch-predict
     *    (MHCR 0x7c1), enable T-Head hardware cache coherency for multi-core 
     *    (MSMPR 0x7f3)
     * ------------------------------------------------------------------ */
    csr_write_num(0x7c2, 0x70003);
    csr_write_num(0x7c1, 0x11ff);
    csr_write_num(0x7f3, 0x1);

    /* ------------------------------------------------------------------
     * 3. PMP: one TOR entry covering the whole address space, RWX
     * ------------------------------------------------------------------ */
    csr_write_num(pmpaddr0, 0x4000000000);
    csr_write_num(pmpcfg0, 0x0f); /* A=TOR | X | W | R */

    /* ------------------------------------------------------------------
     * 4. delegation: route S/U-level traps to S-mode
     *    exceptions: misaligned/access/illegal/breakpoint/ecall-U/
     *                inst-,load-,store-page-fault  (0xB1FF)
     *    interrupts: SSIP | STIP | SEIP             (0x222)
     * ------------------------------------------------------------------ */
    csr_write_num(medeleg, 0xB1FF);
    csr_write_num(mideleg, 0x222);

    /* ------------------------------------------------------------------
     * 5. allow S/U-mode to read cycle/time/instret (rdtime for tick)
     * ------------------------------------------------------------------ */
    csr_write_num(mcounteren, 0xFFFFFFFF);
    csr_write_num(scounteren, 0xFFFFFFFF);

    /* ------------------------------------------------------------------
     * 6. menvcfg.PBMTE(62): honour Svpbmt attributes in S-mode PTEs
     * ------------------------------------------------------------------ */
    v = csr_read_num(menvcfg);
    v |= (1UL << 62);
    csr_write_num(menvcfg, v);

    /* ------------------------------------------------------------------
    * 7. Initialize the parked secondary hart release mask located
    *    boot scratch area under SMP
    * ------------------------------------------------------------------ */
    {
        if (csr_read_num(mhartid) == 0)
        {
            *(volatile unsigned long *)(MEM_PHYS_BASE + MEM_BOOT_SCRATCH_OFF + 8) = 0;
        }
    }

    /* ------------------------------------------------------------------
     * 8. probe hardware supported satp translation modes (WARL, and
     *    satp has no effect on M-mode accesses). Result is passed to
     *    the S-mode kernel through a scratch slot in the boot region
     * ------------------------------------------------------------------ */
    {
        unsigned long mode, mask = 0;

        for (mode = SATP_MODE_SV39; mode <= SATP_MODE_SV57; mode++)
        {
            csr_write_num(satp, mode << 60);
            if (((csr_read_num(satp) >> 60) & 0xF) == mode)
            {
                mask |= (1UL << mode);
            }
        }
        csr_write_num(satp, 0);

        *(volatile unsigned long *)(MEM_PHYS_BASE + MEM_BOOT_SCRATCH_OFF) = mask;
    }
}
