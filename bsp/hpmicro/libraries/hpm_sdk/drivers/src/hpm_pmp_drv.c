/*
 * Copyright (c) 2021-2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "hpm_pmp_drv.h"
#include "hpm_csr_drv.h"

uint32_t read_pmp_cfg(uint32_t idx)
{
    uint32_t pmp_cfg = 0;
    switch (idx) {
    case 0:
        pmp_cfg = read_csr(CSR_PMPCFG0);
        break;
    case 1:
        pmp_cfg = read_csr(CSR_PMPCFG1);
        break;
    case 2:
        pmp_cfg = read_csr(CSR_PMPCFG2);
        break;
    case 3:
        pmp_cfg = read_csr(CSR_PMPCFG3);
        break;
    default:
        /* Do nothing */
        break;
    }
    return pmp_cfg;
}

void write_pmp_cfg(uint32_t value, uint32_t idx)
{
    switch (idx) {
    case 0:
        write_csr(CSR_PMPCFG0, value);
        break;
    case 1:
        write_csr(CSR_PMPCFG1, value);
        break;
    case 2:
        write_csr(CSR_PMPCFG2, value);
        break;
    case 3:
        write_csr(CSR_PMPCFG3, value);
        break;
    default:
        /* Do nothing */
        break;
    }
}

void write_pmp_addr(uint32_t value, uint32_t idx)
{
    switch (idx) {
    case 0:
        write_csr(CSR_PMPADDR0, value);
        break;
    case 1:
        write_csr(CSR_PMPADDR1, value);
        break;
    case 2:
        write_csr(CSR_PMPADDR2, value);
        break;
    case 3:
        write_csr(CSR_PMPADDR3, value);
        break;
    case 4:
        write_csr(CSR_PMPADDR4, value);
        break;
    case 5:
        write_csr(CSR_PMPADDR5, value);
        break;
    case 6:
        write_csr(CSR_PMPADDR6, value);
        break;
    case 7:
        write_csr(CSR_PMPADDR7, value);
        break;
    case 8:
        write_csr(CSR_PMPADDR8, value);
        break;
    case 9:
        write_csr(CSR_PMPADDR9, value);
        break;
    case 10:
        write_csr(CSR_PMPADDR10, value);
        break;
    case 11:
        write_csr(CSR_PMPADDR11, value);
        break;
    case 12:
        write_csr(CSR_PMPADDR12, value);
        break;
    case 13:
        write_csr(CSR_PMPADDR13, value);
        break;
    case 14:
        write_csr(CSR_PMPADDR14, value);
        break;
    case 15:
        write_csr(CSR_PMPADDR15, value);
        break;
    default:
        /* Do nothing */
        break;
    }
}

uint32_t read_pmp_addr(uint32_t idx)
{
    uint32_t ret_val = 0;
    switch (idx) {
    case 0:
        ret_val = read_csr(CSR_PMPADDR0);
        break;
    case 1:
        ret_val = read_csr(CSR_PMPADDR1);
        break;
    case 2:
        ret_val = read_csr(CSR_PMPADDR2);
        break;
    case 3:
        ret_val = read_csr(CSR_PMPADDR3);
        break;
    case 4:
        ret_val = read_csr(CSR_PMPADDR4);
        break;
    case 5:
        ret_val = read_csr(CSR_PMPADDR5);
        break;
    case 6:
        ret_val = read_csr(CSR_PMPADDR6);
        break;
    case 7:
        ret_val = read_csr(CSR_PMPADDR7);
        break;
    case 8:
        ret_val = read_csr(CSR_PMPADDR8);
        break;
    case 9:
        ret_val = read_csr(CSR_PMPADDR9);
        break;
    case 10:
        ret_val = read_csr(CSR_PMPADDR10);
        break;
    case 11:
        ret_val = read_csr(CSR_PMPADDR11);
        break;
    case 12:
        ret_val = read_csr(CSR_PMPADDR12);
        break;
    case 13:
        ret_val = read_csr(CSR_PMPADDR13);
        break;
    case 14:
        ret_val = read_csr(CSR_PMPADDR14);
        break;
    case 15:
        ret_val = read_csr(CSR_PMPADDR15);
        break;
    default:
        /* Do nothing */
        break;
    }
    return ret_val;
}

#if (!defined(PMP_SUPPORT_PMA)) || (defined(PMP_SUPPORT_PMA) && (PMP_SUPPORT_PMA == 1))
uint32_t read_pma_cfg(uint32_t idx)
{
    uint32_t pma_cfg = 0;
    switch (idx) {
    case 0:
        pma_cfg = read_csr(CSR_PMACFG0);
        break;
    case 1:
        pma_cfg = read_csr(CSR_PMACFG1);
        break;
    case 2:
        pma_cfg = read_csr(CSR_PMACFG2);
        break;
    case 3:
        pma_cfg = read_csr(CSR_PMACFG3);
        break;
    default:
        /* Do nothing */
        break;
    }
    return pma_cfg;
}

void write_pma_cfg(uint32_t value, uint32_t idx)
{
    switch (idx) {
    case 0:
        write_csr(CSR_PMACFG0, value);
        break;
    case 1:
        write_csr(CSR_PMACFG1, value);
        break;
    case 2:
        write_csr(CSR_PMACFG2, value);
        break;
    case 3:
        write_csr(CSR_PMACFG3, value);
        break;
    default:
        /* Do nothing */
        break;
    }
}
void write_pma_addr(uint32_t value, uint32_t idx)
{
    switch (idx) {
    case 0:
        write_csr(CSR_PMAADDR0, value);
        break;
    case 1:
        write_csr(CSR_PMAADDR1, value);
        break;
    case 2:
        write_csr(CSR_PMAADDR2, value);
        break;
    case 3:
        write_csr(CSR_PMAADDR3, value);
        break;
    case 4:
        write_csr(CSR_PMAADDR4, value);
        break;
    case 5:
        write_csr(CSR_PMAADDR5, value);
        break;
    case 6:
        write_csr(CSR_PMAADDR6, value);
        break;
    case 7:
        write_csr(CSR_PMAADDR7, value);
        break;
    case 8:
        write_csr(CSR_PMAADDR8, value);
        break;
    case 9:
        write_csr(CSR_PMAADDR9, value);
        break;
    case 10:
        write_csr(CSR_PMAADDR10, value);
        break;
    case 11:
        write_csr(CSR_PMAADDR11, value);
        break;
    case 12:
        write_csr(CSR_PMAADDR12, value);
        break;
    case 13:
        write_csr(CSR_PMAADDR13, value);
        break;
    case 14:
        write_csr(CSR_PMAADDR14, value);
        break;
    case 15:
        write_csr(CSR_PMAADDR15, value);
        break;
    default:
        /* Do nothing */
        break;
    }
}

uint32_t read_pma_addr(uint32_t idx)
{
    uint32_t ret_val = 0;
    switch (idx) {
    case 0:
        ret_val = read_csr(CSR_PMAADDR0);
        break;
    case 1:
        ret_val = read_csr(CSR_PMAADDR1);
        break;
    case 2:
        ret_val = read_csr(CSR_PMAADDR2);
        break;
    case 3:
        ret_val = read_csr(CSR_PMAADDR3);
        break;
    case 4:
        ret_val = read_csr(CSR_PMAADDR4);
        break;
    case 5:
        ret_val = read_csr(CSR_PMAADDR5);
        break;
    case 6:
        ret_val = read_csr(CSR_PMAADDR6);
        break;
    case 7:
        ret_val = read_csr(CSR_PMAADDR7);
        break;
    case 8:
        ret_val = read_csr(CSR_PMAADDR8);
        break;
    case 9:
        ret_val = read_csr(CSR_PMAADDR9);
        break;
    case 10:
        ret_val = read_csr(CSR_PMAADDR10);
        break;
    case 11:
        ret_val = read_csr(CSR_PMAADDR11);
        break;
    case 12:
        ret_val = read_csr(CSR_PMAADDR12);
        break;
    case 13:
        ret_val = read_csr(CSR_PMAADDR13);
        break;
    case 14:
        ret_val = read_csr(CSR_PMAADDR14);
        break;
    case 15:
        ret_val = read_csr(CSR_PMAADDR15);
        break;
    default:
        /* Do nothing */
        break;
    }
    return ret_val;
}
#endif /* #if (!defined(PMP_SUPPORT_PMA)) || (defined(PMP_SUPPORT_PMA) && (PMP_SUPPORT_PMA == 1)) */

hpm_stat_t pmp_config_entry(const pmp_entry_t *entry, uint32_t entry_index)
{
    hpm_stat_t status = status_invalid_argument;
    do {
        HPM_BREAK_IF((entry == NULL) || (entry_index > 15U));

        uint32_t idx = entry_index / 4;
        uint32_t offset = (entry_index * 8) & 0x1F;

        uint32_t pmp_cfg = read_pmp_cfg(idx);
        pmp_cfg &= ~(0xFFUL << offset);
        pmp_cfg |= ((uint32_t) entry->pmp_cfg.val) << offset;
        write_pmp_addr(entry->pmp_addr, entry_index);
        write_pmp_cfg(pmp_cfg, idx);
#if (!defined(PMP_SUPPORT_PMA)) || (defined(PMP_SUPPORT_PMA) && (PMP_SUPPORT_PMA == 1))
        uint32_t pma_cfg = read_pma_cfg(idx);
        pma_cfg &= ~(0xFFUL << offset);
        pma_cfg |= ((uint32_t) entry->pma_cfg.val) << offset;
        write_pma_cfg(pma_cfg, idx);
        write_pma_addr(entry->pma_addr, entry_index);
#endif
        fencei();

        status = status_success;

    } while (false);

    return status;
}

hpm_stat_t pmp_config(const pmp_entry_t *entry, uint32_t num_of_entries)
{
    hpm_stat_t status = status_invalid_argument;
    do {
        HPM_BREAK_IF((entry == NULL) || (num_of_entries < 1U) || (num_of_entries > 15U));

        for (uint32_t i = 0; i < num_of_entries; i++) {
            uint32_t idx = i / 4;
            uint32_t offset = (i * 8) & 0x1F;
            uint32_t pmp_cfg = read_pmp_cfg(idx);
            pmp_cfg &= ~(0xFFUL << offset);
            pmp_cfg |= ((uint32_t) entry->pmp_cfg.val) << offset;
            write_pmp_addr(entry->pmp_addr, i);
            write_pmp_cfg(pmp_cfg, idx);
#if (!defined(PMP_SUPPORT_PMA)) || (defined(PMP_SUPPORT_PMA) && (PMP_SUPPORT_PMA == 1))
            uint32_t pma_cfg = read_pma_cfg(idx);
            pma_cfg &= ~(0xFFUL << offset);
            pma_cfg |= ((uint32_t) entry->pma_cfg.val) << offset;
            write_pma_cfg(pma_cfg, idx);
            write_pma_addr(entry->pma_addr, i);
#endif
            ++entry;
        }
        fencei();

        status = status_success;

    } while (false);

    return status;
}

void pmp_disable(void)
{
    /* Disable caches */
    fencei();
    uint32_t mcache_ctl = read_csr(CSR_MCACHE_CTL);
    write_csr(CSR_MCACHE_CTL, 0x0);
    fencei();

    write_csr(CSR_PMPCFG0, 0);
    write_csr(CSR_PMPCFG1, 0);
    write_csr(CSR_PMPCFG2, 0);
    write_csr(CSR_PMPCFG3, 0);
    write_csr(CSR_PMPADDR0, 0);
    write_csr(CSR_PMPADDR1, 0);
    write_csr(CSR_PMPADDR2, 0);
    write_csr(CSR_PMPADDR3, 0);
    write_csr(CSR_PMPADDR4, 0);
    write_csr(CSR_PMPADDR5, 0);
    write_csr(CSR_PMPADDR6, 0);
    write_csr(CSR_PMPADDR7, 0);
    write_csr(CSR_PMPADDR8, 0);
    write_csr(CSR_PMPADDR9, 0);
    write_csr(CSR_PMPADDR10, 0);
    write_csr(CSR_PMPADDR11, 0);
    write_csr(CSR_PMPADDR12, 0);
    write_csr(CSR_PMPADDR13, 0);
    write_csr(CSR_PMPADDR14, 0);
    write_csr(CSR_PMPADDR15, 0);
#if (!defined(PMP_SUPPORT_PMA)) || (defined(PMP_SUPPORT_PMA) && (PMP_SUPPORT_PMA == 1))
    write_csr(CSR_PMACFG0, 0);
    write_csr(CSR_PMACFG1, 0);
    write_csr(CSR_PMACFG2, 0);
    write_csr(CSR_PMACFG3, 0);
    write_csr(CSR_PMAADDR0, 0);
    write_csr(CSR_PMAADDR1, 0);
    write_csr(CSR_PMAADDR2, 0);
    write_csr(CSR_PMAADDR3, 0);
    write_csr(CSR_PMAADDR4, 0);
    write_csr(CSR_PMAADDR5, 0);
    write_csr(CSR_PMAADDR6, 0);
    write_csr(CSR_PMAADDR7, 0);
    write_csr(CSR_PMAADDR8, 0);
    write_csr(CSR_PMAADDR9, 0);
    write_csr(CSR_PMAADDR10, 0);
    write_csr(CSR_PMAADDR11, 0);
    write_csr(CSR_PMAADDR12, 0);
    write_csr(CSR_PMAADDR13, 0);
    write_csr(CSR_PMAADDR14, 0);
    write_csr(CSR_PMAADDR15, 0);
#endif
    fencei();
    write_csr(CSR_MCACHE_CTL, mcache_ctl);
    fencei();
}
