/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_L1_CACHE_H
#define _HPM_L1_CACHE_H
#include "hpm_common.h"
#include "hpm_csr_drv.h"
#include "hpm_soc.h"

/**
 *
 * @brief L1CACHE driver APIs
 * @defgroup l1cache_interface L1CACHE driver APIs
 * @{
 */

/* cache size is 16KB */
#define HPM_L1C_CACHE_SIZE (uint32_t)(16 * SIZE_1KB)
#define HPM_L1C_ICACHE_SIZE (HPM_L1C_CACHE_SIZE)
#define HPM_L1C_DCACHE_SIZE (HPM_L1C_CACHE_SIZE)
/* cache line size is 32B */
#define HPM_L1C_CACHELINE_SIZE (32)
/* cache way is 128 */
#define HPM_L1C_CACHELINES_PER_WAY (128)

/* mcache_ctl register */
/*
 * Controls if the instruction cache is enabled or not.
 *
 * 0 I-Cache is disabled
 * 1 I-Cache is enabled
 */
#define HPM_MCACHE_CTL_IC_EN_SHIFT (0UL)
#define HPM_MCACHE_CTL_IC_EN_MASK  (1UL << HPM_MCACHE_CTL_IC_EN_SHIFT)
#define HPM_MCACHE_CTL_IC_EN(x) \
    (uint32_t)(((x) << HPM_MCACHE_CTL_IC_EN_SHIFT) & HPM_MCACHE_CTL_IC_EN_MASK)

/*
 * Controls if the data cache is enabled or not.
 *
 * 0 D-Cache is disabled
 * 1 D-Cache is enabled
 */
#define HPM_MCACHE_CTL_DC_EN_SHIFT (1UL)
#define HPM_MCACHE_CTL_DC_EN_MASK  (1UL << HPM_MCACHE_CTL_DC_EN_SHIFT)
#define HPM_MCACHE_CTL_DC_EN(x) \
    (uint32_t)(((x) << HPM_MCACHE_CTL_DC_EN_SHIFT) & HPM_MCACHE_CTL_DC_EN_MASK)

/*
 * Parity/ECC error checking enable control for the instruction cache.
 *
 * 0 Disable parity/ECC
 * 1 Reserved
 * 2 Generate exceptions only on uncorrectable parity/ECC errors
 * 3 Generate exceptions on any type of parity/ECC errors
 */
#define HPM_MCACHE_CTL_IC_ECCEN_SHIFT (0x2UL)
#define HPM_MCACHE_CTL_IC_ECCEN_MASK  (0x3UL << HPM_MCACHE_CTL_IC_ECCEN_SHIFT)
#define HPM_MCACHE_CTL_IC_ECCEN(x) \
    (uint32_t)(((x) << HPM_MCACHE_CTL_IC_ECCEN_SHIFT) & HPM_MCACHE_CTL_IC_ECCEN_MASK)

/*
 *
 * Parity/ECC error checking enable control for the data cache.
 *
 * 0 Disable parity/ECC
 * 1 Reserved
 * 2 Generate exceptions only on uncorrectable parity/ECC errors
 * 3 Generate exceptions on any type of parity/ECC errors
 */
#define HPM_MCACHE_CTL_DC_ECCEN_SHIFT (0x4UL)
#define HPM_MCACHE_CTL_DC_ECCEN_MASK  (0x3UL << HPM_MCACHE_CTL_DC_ECCEN_SHIFT)
#define HPM_MCACHE_CTL_DC_ECCEN(x) \
    (uint32_t)(((x) << HPM_MCACHE_CTL_DC_ECCEN_SHIFT) & HPM_MCACHE_CTL_DC_ECCEN_MASK)

/*
 *
 * Controls diagnostic accesses of ECC codes of the instruction cache RAMs.
 * It is set to enable CCTL operations to access the ECC codes. This bit
 * can be set for injecting ECC errors to test the ECC handler.
 *
 * 0 Disable diagnostic accesses of ECC codes
 * 1 Enable diagnostic accesses of ECC codes
 */
#define HPM_MCACHE_CTL_IC_RWECC_SHIFT (0x6UL)
#define HPM_MCACHE_CTL_IC_RWECC_MASK  (0x1UL << HPM_MCACHE_CTL_IC_RWECC_SHIFT)
#define HPM_MCACHE_CTL_IC_RWECC(x) \
    (uint32_t)(((x) << HPM_MCACHE_CTL_IC_RWECC_SHIFT) & HPM_MCACHE_CTL_IC_RWECC_MASK)

/*
 *
 * Controls diagnostic accesses of ECC codes of the data cache RAMs. It is
 * set to enable CCTL operations to access the ECC codes. This bit can be
 * set for injecting
 *
 * ECC errors to test the ECC handler.
 * 0 Disable diagnostic accesses of ECC codes
 * 1 Enable diagnostic accesses of ECC codes
 */
#define HPM_MCACHE_CTL_DC_RWECC_SHIFT (0x7UL)
#define HPM_MCACHE_CTL_DC_RWECC_MASK  (0x1UL << HPM_MCACHE_CTL_DC_RWECC_SHIFT)
#define HPM_MCACHE_CTL_DC_RWECC(x) \
    (uint32_t)(((x) << HPM_MCACHE_CTL_DC_RWECC_SHIFT) & HPM_MCACHE_CTL_DC_RWECC_MASK)

/*
 * Enable bit for Superuser-mode and User-mode software to access
 * ucctlbeginaddr and ucctlcommand CSRs.
 *
 * 0 Disable ucctlbeginaddr and ucctlcommand accesses in S/U mode
 * 1 Enable ucctlbeginaddr and ucctlcommand accesses in S/U mode
 */
#define HPM_MCACHE_CTL_CCTL_SUEN_SHIFT (0x8UL)
#define HPM_MCACHE_CTL_CCTL_SUEN_MASK  (0x1UL << HPM_MCACHE_CTL_CCTL_SUEN_SHIFT)
#define HPM_MCACHE_CTL_CCTL_SUEN(x) \
    (uint32_t)(((x) << HPM_MCACHE_CTL_CCTL_SUEN_SHIFT) & HPM_MCACHE_CTL_CCTL_SUEN_MASK)

/*
 * This bit controls hardware prefetch for instruction fetches to cacheable
 * memory regions when I-Cache size is not 0.
 *
 * 0 Disable hardware prefetch on instruction fetches
 * 1 Enable hardware prefetch on instruction fetches
 */
#define HPM_MCACHE_CTL_IPREF_EN_SHIFT (0x9UL)
#define HPM_MCACHE_CTL_IPREF_EN_MASK  (0x1UL << HPM_MCACHE_CTL_IPREF_EN_SHIFT)
#define HPM_MCACHE_CTL_IPREF_EN(x) \
    (uint32_t)(((x) << HPM_MCACHE_CTL_IPREF_EN_SHIFT) & HPM_MCACHE_CTL_IPREF_EN_MASK)

/*
 * This bit controls hardware prefetch for load/store accesses to cacheable
 * memory regions when D-Cache size is not 0.
 *
 * 0 Disable hardware prefetch on load/store memory accesses.
 * 1 Enable hardware prefetch on load/store memory accesses.
 */
#define HPM_MCACHE_CTL_DPREF_EN_SHIFT (0x10UL)
#define HPM_MCACHE_CTL_DPREF_EN_MASK  (0x1UL << HPM_MCACHE_CTL_DPREF_EN_SHIFT)
#define HPM_MCACHE_CTL_DPREF_EN(x) \
    (uint32_t)(((x) << HPM_MCACHE_CTL_DPREF_EN_SHIFT) & HPM_MCACHE_CTL_DPREF_EN_MASK)

/*
 * I-Cache miss allocation filling policy Value Meaning
 *
 * 0 Cache line data is returned critical (double) word first
 * 1 Cache line data is returned the lowest address (double) word first
 */
#define HPM_MCACHE_CTL_IC_FIRST_WORD_SHIFT (0x11UL)
#define HPM_MCACHE_CTL_IC_FIRST_WORD_MASK  (0x1UL << HPM_MCACHE_CTL_IC_FIRST_WORD_SHIFT)
#define HPM_MCACHE_CTL_IC_FIRST_WORD(x) \
    (uint32_t)(((x) << HPM_MCACHE_CTL_IC_FIRST_WORD_SHIFT) & HPM_MCACHE_CTL_IC_FIRST_WORD_MASK)

/*
 * D-Cache miss allocation filling policy
 *
 * 0 Cache line data is returned critical (double) word first
 * 1 Cache line data is returned the lowest address (double) word first
 */
#define HPM_MCACHE_CTL_DC_FIRST_WORD_SHIFT (0x12UL)
#define HPM_MCACHE_CTL_DC_FIRST_WORD_MASK  (0x1UL << HPM_MCACHE_CTL_DC_FIRST_WORD_SHIFT)
#define HPM_MCACHE_CTL_DC_FIRST_WORD(x) \
    (uint32_t)(((x) << HPM_MCACHE_CTL_DC_FIRST_WORD_SHIFT) & HPM_MCACHE_CTL_DC_FIRST_WORD_MASK)

/*
 * D-Cache Write-Around threshold
 *
 * 0 Disables streaming. All cacheable write misses allocate a cache line
 * according to PMA settings.
 * 1 Override PMA setting and do not allocate D-Cache entries after
 * consecutive stores to 4 cache lines.
 * 2 Override PMA setting and do not allocate D-Cache entries after
 * consecutive stores to 64 cache lines.
 * 3 Override PMA setting and do not allocate D-Cache entries after
 * consecutive stores to 128 cache lines.
 */
#define HPM_MCACHE_CTL_DC_WAROUND_SHIFT (0x13UL)
#define HPM_MCACHE_CTL_DC_WAROUND_MASK  (0x3UL << HPM_MCACHE_CTL_DC_WAROUND_SHIFT)
#define HPM_MCACHE_CTL_DC_WAROUND(x) \
    (uint32_t)(((x) << HPM_MCACHE_CTL_DC_WAROUND_SHIFT) & HPM_MCACHE_CTL_DC_WAROUND_MASK)

/* CCTL command list */
#define HPM_L1C_CCTL_CMD_L1D_VA_INVAL       (0UL)
#define HPM_L1C_CCTL_CMD_L1D_VA_WB          (1UL)
#define HPM_L1C_CCTL_CMD_L1D_VA_WBINVAL     (2UL)
#define HPM_L1C_CCTL_CMD_L1D_VA_LOCK        (3UL)
#define HPM_L1C_CCTL_CMD_L1D_VA_UNLOCK      (4UL)
#define HPM_L1C_CCTL_CMD_L1D_WBINVAL_ALL    (6UL)
#define HPM_L1C_CCTL_CMD_L1D_WB_ALL         (7UL)

#define HPM_L1C_CCTL_CMD_L1I_VA_INVAL       (8UL)
#define HPM_L1C_CCTL_CMD_L1I_VA_LOCK        (11UL)
#define HPM_L1C_CCTL_CMD_L1I_VA_UNLOCK      (12UL)

#define HPM_L1C_CCTL_CMD_L1D_IX_INVAL       (16UL)
#define HPM_L1C_CCTL_CMD_L1D_IX_WB          (17UL)
#define HPM_L1C_CCTL_CMD_L1D_IX_WBINVAL     (18UL)

#define HPM_L1C_CCTL_CMD_L1D_IX_RTAG        (19UL)
#define HPM_L1C_CCTL_CMD_L1D_IX_RDATA       (20UL)
#define HPM_L1C_CCTL_CMD_L1D_IX_WTAG        (21UL)
#define HPM_L1C_CCTL_CMD_L1D_IX_WDATA       (22UL)

#define HPM_L1C_CCTL_CMD_L1D_INVAL_ALL      (23UL)

#define HPM_L1C_CCTL_CMD_L1I_IX_INVAL       (24UL)
#define HPM_L1C_CCTL_CMD_L1I_IX_RTAG        (27UL)
#define HPM_L1C_CCTL_CMD_L1I_IX_RDATA       (28UL)
#define HPM_L1C_CCTL_CMD_L1I_IX_WTAG        (29UL)
#define HPM_L1C_CCTL_CMD_L1I_IX_WDATA       (30UL)

#define HPM_L1C_CCTL_CMD_SUCCESS            (1UL)
#define HPM_L1C_CCTL_CMD_FAIL               (0UL)

#ifdef __cplusplus
extern "C" {
#endif
/* get cache control register value */
__attribute__((always_inline)) static inline uint32_t l1c_get_control(void)
{
    return read_csr(CSR_MCACHE_CTL);
}

__attribute__((always_inline)) static inline bool l1c_dc_is_enabled(void)
{
    return l1c_get_control() & HPM_MCACHE_CTL_DC_EN_MASK;
}

__attribute__((always_inline)) static inline bool l1c_ic_is_enabled(void)
{
    return l1c_get_control() & HPM_MCACHE_CTL_IC_EN_MASK;
}

/* mcctlbeginaddress register bitfield layout for CCTL IX type command */
#define HPM_MCCTLBEGINADDR_OFFSET_SHIFT (2UL)
#define HPM_MCCTLBEGINADDR_OFFSET_MASK ((uint32_t) 0xF << HPM_MCCTLBEGINADDR_OFFSET_SHIFT)
#define HPM_MCCTLBEGINADDR_OFFSET(x) \
    (uint32_t)(((x) << HPM_MCCTLBEGINADDR_OFFSET_SHIFT) & HPM_MCCTLBEGINADDR_OFFSET_MASK)
#define HPM_MCCTLBEGINADDR_INDEX_SHIFT (6UL)
#define HPM_MCCTLBEGINADDR_INDEX_MASK ((uint32_t) 0x3F << HPM_MCCTLBEGINADDR_INDEX_SHIFT)
#define HPM_MCCTLBEGINADDR_INDEX(x) \
    (uint32_t)(((x) << HPM_MCCTLBEGINADDR_INDEX_SHIFT) & HPM_MCCTLBEGINADDR_INDEX_MASK)
#define HPM_MCCTLBEGINADDR_WAY_SHIFT (13UL)
#define HPM_MCCTLBEGINADDR_WAY_MASK ((uint32_t) 0x3 << HPM_MCCTLBEGINADDR_WAY_SHIFT)
#define HPM_MCCTLBEGINADDR_WAY(x) \
    (uint32_t)(((x) << HPM_MCCTLBEGINADDR_WAY_SHIFT) & HPM_MCCTLBEGINADDR_WAY_MASK)

/* send IX command */
__attribute__((always_inline)) static inline void l1c_cctl_address(uint32_t address)
{
    write_csr(CSR_MCCTLBEGINADDR, address);
}

/* send command */
__attribute__((always_inline)) static inline void l1c_cctl_cmd(uint8_t cmd)
{
    write_csr(CSR_MCCTLCOMMAND, cmd);
}

__attribute__((always_inline)) static inline uint32_t l1c_cctl_get_address(void)
{
    return read_csr(CSR_MCCTLBEGINADDR);
}

/* send IX command */
__attribute__((always_inline)) static inline
    void l1c_cctl_address_cmd(uint8_t cmd, uint32_t address)
{
    write_csr(CSR_MCCTLBEGINADDR, address);
    write_csr(CSR_MCCTLCOMMAND, cmd);
}

#define HPM_MCCTLDATA_I_TAG_ADDRESS_SHIFT (2UL)
#define HPM_MCCTLDATA_I_TAG_ADDRESS_MASK (uint32_t)(0XFFFFF << HPM_MCCTLDATA_I_TAG_ADDRESS_SHIFT)
#define HPM_MCCTLDATA_I_TAG_ADDRESS(x) \
    (uint32_t)(((x) << HPM_MCCTLDATA_I_TAG_ADDRESS_SHIFT) & HPM_MCCTLDATA_I_TAG_ADDRESS_MASK)

#define HPM_MCCTLDATA_I_TAG_LOCK_DUP_SHIFT (29UL)
#define HPM_MCCTLDATA_I_TAG_LOCK_DUP_MASK (uint32_t)(1 << HPM_MCCTLDATA_I_TAG_LOCK_DUP_SHIFT)
#define HPM_MCCTLDATA_I_TAG_LOCK_DUP(x) \
    (uint32_t)(((x) << HPM_MCCTLDATA_I_TAG_LOCK_DUP_SHIFT) & HPM_MCCTLDATA_I_TAG_LOCK_DUP_MASK)

#define HPM_MCCTLDATA_I_TAG_LOCK_SHIFT (30UL)
#define HPM_MCCTLDATA_I_TAG_LOCK_MASK (uint32_t)(1 << HPM_MCCTLDATA_I_TAG_LOCK_SHIFT)
#define HPM_MCCTLDATA_I_TAG_LOCK(x) \
    (uint32_t)(((x) << HPM_MCCTLDATA_I_TAG_LOCK_SHIFT) & HPM_MCCTLDATA_I_TAG_LOCK_MASK)

#define HPM_MCCTLDATA_I_TAG_VALID_SHIFT (31UL)
#define HPM_MCCTLDATA_I_TAG_VALID_MASK (uint32_t)(1 << HPM_MCCTLDATA_I_TAG_VALID_SHIFT)
#define HPM_MCCTLDATA_I_TAG_VALID(x) \
    (uint32_t)(((x) << HPM_MCCTLDATA_I_TAG_VALID_SHIFT) & HPM_MCCTLDATA_I_TAG_VALID_MASK)

#define HPM_MCCTLDATA_D_TAG_MESI_SHIFT (0UL)
#define HPM_MCCTLDATA_D_TAG_MESI_MASK (uint32_t)(0x3 << HPM_MCCTLDATA_D_TAG_MESI_SHIFT)
#define HPM_MCCTLDATA_D_TAG_MESI(x) \
    (uint32_t)(((x) << HPM_MCCTLDATA_D_TAG_MESI_SHIFT) & HPM_MCCTLDATA_D_TAG_MESI_MASK)

#define HPM_MCCTLDATA_D_TAG_LOCK_SHIFT (3UL)
#define HPM_MCCTLDATA_D_TAG_LOCK_MASK (uint32_t)(0x1 << HPM_MCCTLDATA_D_TAG_LOCK_SHIFT)
#define HPM_MCCTLDATA_D_TAG_LOCK(x) \
    (uint32_t)(((x) << HPM_MCCTLDATA_D_TAG_LOCK_SHIFT) & HPM_MCCTLDATA_D_TAG_LOCK_MASK)

#define HPM_MCCTLDATA_D_TAG_TAG_SHIFT (4UL)
#define HPM_MCCTLDATA_D_TAG_TAG_MASK (uint32_t)(0xFFFF << HPM_MCCTLDATA_D_TAG_LOCK_SHIFT)
#define HPM_MCCTLDATA_D_TAG_TAG(x) \
    (uint32_t)(((x) << HPM_MCCTLDATA_D_TAG_TAG_SHIFT) & HPM_MCCTLDATA_D_TAG_TAG_MASK)

/*
 * @brief Cache control command read address
 *
 * Send IX read tag/data cmd
 * @param[in] cmd Command code
 * @param[in] address Target address
 * @param[in] ecc_data ECC value
 * @return data read
 */
ATTR_ALWAYS_INLINE static inline
    uint32_t l1c_cctl_address_cmd_read(uint8_t cmd, uint32_t address, uint32_t *ecc_data)
{
    write_csr(CSR_MCCTLBEGINADDR, address);
    write_csr(CSR_MCCTLCOMMAND, cmd);
    *ecc_data = read_csr(CSR_MECC_CODE);
    return read_csr(CSR_MCCTLDATA);
}

/*
 * @brief Cache control command write address
 *
 * Send IX write tag/data cmd
 * @param[in] cmd Command code
 * @param[in] address Target address
 * @param[in] data Data to be written
 * @param[in] ecc_data ECC of data
 */
ATTR_ALWAYS_INLINE static inline
    void l1c_cctl_address_cmd_write(uint8_t cmd, uint32_t address, uint32_t data, uint32_t ecc_data)
{
    write_csr(CSR_MCCTLBEGINADDR, address);
    write_csr(CSR_MCCTLCOMMAND, cmd);
    write_csr(CSR_MCCTLDATA, data);
    write_csr(CSR_MECC_CODE, ecc_data);
}

#define HPM_L1C_CFG_SET_SHIFT      (0UL)
#define HPM_L1C_CFG_SET_MASK       (uint32_t)(0x7 << HPM_L1C_CFG_SET_SHIFT)
#define HPM_L1C_CFG_WAY_SHIFT      (3UL)
#define HPM_L1C_CFG_WAY_MASK       (uint32_t)(0x7 << HPM_L1C_CFG_WAY_SHIFT)
#define HPM_L1C_CFG_SIZE_SHIFT     (6UL)
#define HPM_L1C_CFG_SIZE_MASK      (uint32_t)(0x7 << HPM_L1C_CFG_SIZE_SHIFT)
#define HPM_L1C_CFG_LOCK_SHIFT     (9UL)
#define HPM_L1C_CFG_LOCK_MASK      (uint32_t)(0x1 << HPM_L1C_CFG_LOCK_SHIFT)
#define HPM_L1C_CFG_ECC_SHIFT      (10UL)
#define HPM_L1C_CFG_ECC_MASK       (uint32_t)(0x3 << HPM_L1C_CFG_ECC_SHIFT)
#define HPM_L1C_CFG_LMB_SHIFT      (12UL)
#define HPM_L1C_CFG_LMB_MASK       (uint32_t)(0x7 << HPM_L1C_CFG_LMB_SHIFT)
#define HPM_L1C_CFG_LM_SIZE_SHIFT  (15UL)
#define HPM_L1C_CFG_LM_SIZE_MASK   (uint32_t)(0x1F << HPM_L1C_CFG_LM_SIZE_SHIFT)
#define HPM_L1C_CFG_LM_ECC_SHIFT   (21UL)
#define HPM_L1C_CFG_LM_ECC_MASK    (uint32_t)(0x3 << HPM_L1C_CFG_LM_ECC_SHIFT)
#define HPM_L1C_CFG_SETH_SHIFT     (24UL)
#define HPM_L1C_CFG_SETH_MASK      (uint32_t)(0x1 << HPM_L1C_CFG_SETH_SHIFT)

/**
 * @brief  Align down based on cache line size
 */
#define HPM_L1C_CACHELINE_ALIGN_DOWN(n) ((uint32_t)(n) & ~(HPM_L1C_CACHELINE_SIZE - 1U))

/**
 * @brief Align up based on cache line size
 */
#define HPM_L1C_CACHELINE_ALIGN_UP(n)   HPM_L1C_CACHELINE_ALIGN_DOWN((uint32_t)(n) + HPM_L1C_CACHELINE_SIZE - 1U)

/**
 * @brief   Get I-cache configuration
 *
 * @return I-cache config register
 */
ATTR_ALWAYS_INLINE static inline uint32_t l1c_ic_get_config(void)
{
    return read_csr(CSR_MICM_CFG);
}

/**
 * @brief   Get D-cache configuration
 *
 * @return D-cache config register
 */
ATTR_ALWAYS_INLINE static inline uint32_t l1c_dc_get_config(void)
{
    return read_csr(CSR_MDCM_CFG);
}

/*
 * @brief D-cache disable
 */
void l1c_dc_disable(void);

/*
 * @brief D-cache enable
 */
void l1c_dc_enable(void);

/*
 * @brief D-cache invalidate by address
 * @param[in] address Start address to be invalidated
 * @param[in] size Size of memory to be invalidated
 */
void l1c_dc_invalidate(uint32_t address, uint32_t size);

/*
 * @brief D-cache writeback by address
 * @param[in] address Start address to be writtenback
 * @param[in] size Size of memory to be writtenback
 */
void l1c_dc_writeback(uint32_t address, uint32_t size);

/*
 * @brief D-cache invalidate and writeback by address
 * @param[in] address Start address to be invalidated and writtenback
 * @param[in] size Size of memory to be invalidted and writtenback
 */
void l1c_dc_flush(uint32_t address, uint32_t size);

/*
 * @brief D-cache fill and lock by address
 * @param[in] address Start address to be filled and locked
 * @param[in] size Size of memory to be filled and locked
 */
void l1c_dc_fill_lock(uint32_t address, uint32_t size);

/*
 * @brief I-cache disable
 */
void l1c_ic_disable(void);

/*
 * @brief I-cache enable
 */
void l1c_ic_enable(void);

/*
 * @brief I-cache invalidate by address
 * @param[in] address Start address to be invalidated
 * @param[in] size Size of memory to be invalidated
 */
void l1c_ic_invalidate(uint32_t address, uint32_t size);

/*
 * @brief I-cache fill and lock by address
 * @param[in] address Start address to be locked
 * @param[in] size Size of memory to be locked
 */
void l1c_ic_fill_lock(uint32_t address, uint32_t size);

/*
 * @brief Invalidate all icache and writeback all dcache
 */
void l1c_fence_i(void);

/*
 * @brief Invalidate all d-cache
 */
void l1c_dc_invalidate_all(void);

/*
 * @brief Writeback all d-cache
 */
void l1c_dc_writeback_all(void);

/*
 * @brief Flush all d-cache
 */
void l1c_dc_flush_all(void);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _HPM_L1_CACHE_H */
