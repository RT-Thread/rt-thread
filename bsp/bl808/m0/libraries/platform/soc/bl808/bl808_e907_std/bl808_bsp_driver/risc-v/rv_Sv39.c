/**
  ******************************************************************************
  * @file    rv_Sv39.c
  * @version V1.0
  * @date
  * @brief   This file is the RISC-V arch c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2021 Bouffalo Lab</center></h2>
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
  *
  ******************************************************************************
  */

#include <stdint.h>
#include "rv_Sv39.h"

/** @addtogroup  RISCV_ARCH_Driver
 *  @{
 */

/** @addtogroup  SV39
 *  @{
 */

/* allocate 4KB page table buffer */
__attribute__((weak))
uint64_t *
RV_Sv39_alloc_PageTable_buf(void)
{
    return NULL;
}

/** @defgroup  SV39_Public_Functions
 *  @{
 */

/******************************************************************************
 * @brief  OSD blend layer configuration
 *
 * @param  cfg: point to the Page Table Entry.
 * @param  tlb_index: return the TLB index in use if MAP is created directly in TLB.
 * @param  ttb0: the root translation table in memory.
 *
 * @return Result of the operation.
 *
*******************************************************************************/

BL_Err_Type RV_Sv39_Create_PageMapping(Sv39_PTE_cfg_t *cfg, uintptr_t *tlb_index, volatile uintptr_t *ttb0)
{
    uintptr_t smeh, smel, smcir;
    uintptr_t t0;
    volatile uint64_t *ttb1 = NULL;
    volatile uint64_t *ttb2 = NULL;

    /* TODO: check parameters */

    if (Sv39_PTE_LOC_JTLB == cfg->where) {
        t0 = cfg->va;
        smeh = ((t0 >> 12) << SMEH_VPN_OFFSET) | cfg->size | cfg->asid;
        __asm volatile("csrw smeh, %0"
                       :
                       : "r"(smeh)
                       : "memory");

        t0 = cfg->pa;
        smel = cfg->flags | ((t0 >> 12) << PTE_PPN_OFFSET);
        __asm volatile("csrw smel, %0"
                       :
                       : "r"(smel)
                       : "memory");

        if (cfg->tlb_entry >= SV39_JTLB_ENTRY_CNT) {
            /* random write */
            smcir = SMCIR_TLBWR;
        } else {
            RV_Sv39_Set_SMIR(cfg->tlb_entry);
            smcir = SMCIR_TLBWI;
        }

        smcir |= cfg->asid;
        RV_Sv39_Set_SMCIR(smcir);

        RV_Sv39_Set_SMCIR(SMCIR_TLBP);
        t0 = RV_Sv39_Get_SMIR();

        *tlb_index = t0;

        return (t0 & (SMCIR_PF | SMCIR_TF)) ? ERROR : SUCCESS;
    } else {
        /* top level: 1GB */
        t0 = SV39_VPN2(cfg->va);

        if (!ttb0[t0]) {
            /* no translation for this 1GB range */
            if (Sv39_PAGESIZE_1GB == cfg->size) {
                /* finish map for top level */
                ttb0[t0] = (SV39_PA2PPN(cfg->pa) << PTE_PPN_OFFSET) |
                           (cfg->flags);
                return SUCCESS;
            } else {
                ttb1 = RV_Sv39_alloc_PageTable_buf();

                if (NULL == ttb1) {
                    return NORESC;
                }

                __COMPILE_BARRIER();
                ttb0[t0] = (SV39_PA2PPN((uint64_t)ttb1) << PTE_PPN_OFFSET) |
                           PTE_D | PTE_A |
                           PTE_XWR_NEXT | PTE_V;
            }
        } else {
            /* already mapped, get the next level table pointer */
            ttb1 = (volatile uint64_t *)SV39_PTE2PA(ttb0[t0]);
        }

        /* second level: 2MB */
        t0 = SV39_VPN1(cfg->va);

        if (!ttb1[t0]) {
            /* no translation for this 2MB range */
            if (Sv39_PAGESIZE_2MB == cfg->size) {
                ttb1[t0] = (SV39_PA2PPN(cfg->pa) << PTE_PPN_OFFSET) |
                           (cfg->flags);
                return SUCCESS;
            } else {
                ttb2 = RV_Sv39_alloc_PageTable_buf();

                if (NULL == ttb2) {
                    return NORESC;
                }

                ttb1[t0] = (SV39_PA2PPN((uint64_t)ttb2) << PTE_PPN_OFFSET) |
                           PTE_D | PTE_A |
                           PTE_XWR_NEXT | PTE_V;
            }
        } else {
            ttb2 = (volatile uint64_t *)SV39_PTE2PA(ttb1[t0]);
        }

        /* third level: 4KB */
        t0 = SV39_VPN0(cfg->va);
        __COMPILE_BARRIER();
        ttb2[t0] = (SV39_PA2PPN(cfg->pa) << PTE_PPN_OFFSET) |
                   (cfg->flags);
    }

    /* flush the D cache */

    return SUCCESS;
}

/*@} end of group SV39_Public_Functions */

/*@} end of group SV39 */

/*@} end of group RISCV_ARCH_Driver */
