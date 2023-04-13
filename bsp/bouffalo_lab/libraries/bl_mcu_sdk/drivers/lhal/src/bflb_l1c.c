#include "bflb_l1c.h"

#if (defined(BL616) || defined(BL606P) || defined(BL808) || defined(BL628)) && !defined(CPU_LP)
#include "csi_core.h"
void bflb_l1c_icache_enable(void)
{
    csi_icache_enable();
}

void bflb_l1c_icache_disable(void)
{
    csi_icache_disable();
}

ATTR_TCM_SECTION void bflb_l1c_icache_invalid_all(void)
{
    csi_icache_invalid();
}

void bflb_l1c_dcache_enable(void)
{
    csi_dcache_enable();
}

void bflb_l1c_dcache_disable(void)
{
    csi_dcache_disable();
}

ATTR_TCM_SECTION void bflb_l1c_dcache_clean_all(void)
{
    csi_dcache_clean();
}

ATTR_TCM_SECTION void bflb_l1c_dcache_invalidate_all(void)
{
    csi_dcache_invalid();
}

ATTR_TCM_SECTION void bflb_l1c_dcache_clean_invalidate_all(void)
{
    csi_dcache_clean_invalid();
}

ATTR_TCM_SECTION void bflb_l1c_dcache_clean_range(void *addr, uint32_t size)
{
    csi_dcache_clean_range(addr, size);
}

ATTR_TCM_SECTION void bflb_l1c_dcache_invalidate_range(void *addr, uint32_t size)
{
    csi_dcache_invalid_range(addr, size);
}

ATTR_TCM_SECTION void bflb_l1c_dcache_clean_invalidate_range(void *addr, uint32_t size)
{
    csi_dcache_clean_invalid_range(addr, size);
}
#else

#if defined(BL702) || defined(BL702L)
extern void L1C_Cache_Enable_Set(uint8_t wayDisable);
extern void L1C_Cache_Flush(void);
#endif

void bflb_l1c_icache_enable(void)
{
}

void bflb_l1c_icache_disable(void)
{
#if defined(BL702) || defined(BL702L)
    L1C_Cache_Enable_Set(0x0f);
#endif
}

void bflb_l1c_icache_invalid_all(void)
{
}

void bflb_l1c_dcache_enable(void)
{
}

void bflb_l1c_dcache_disable(void)
{
}

void bflb_l1c_dcache_clean_all(void)
{
}

void bflb_l1c_dcache_invalidate_all(void)
{
#if defined(BL702) || defined(BL702L)
    L1C_Cache_Flush();
#endif
}

void bflb_l1c_dcache_clean_invalidate_all(void)
{
#if defined(BL702) || defined(BL702L)
    L1C_Cache_Flush();
#endif
}

void bflb_l1c_dcache_clean_range(void *addr, uint32_t size)
{
}

ATTR_TCM_SECTION void bflb_l1c_dcache_invalidate_range(void *addr, uint32_t size)
{
#if defined(BL702) || defined(BL702L)
    L1C_Cache_Flush();
#endif
}

#if defined(BL702) || defined(BL702L)
/****************************************************************************/ /**
 * @brief  L1C cache write set
 *
 * @param  wt_en: L1C write through enable
 * @param  wb_en: L1C write back enable
 * @param  wa_en: L1C write allocate enable
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_l1c_cache_write_set(uint8_t wt_en, uint8_t wb_en, uint8_t wa_en)
{
    uint32_t regval = 0;

    regval = getreg32(0x40009000 + 0x0);

    if (wt_en) {
        regval |= (1<<4);
    } else {
        regval &= ~(1<<4);
    }

    if (wb_en) {
        regval |= (1<<5);
    } else {
        regval &= ~(1<<5);
    }

    if (wa_en) {
        regval |= (1<<6);
    } else {
        regval &= ~(1<<6);
    }

    putreg32(regval, 0x40009000+0x0);
}
#endif

/****************************************************************************/ /**
 * @brief  Get hit count
 *
 * @param  hit_count_low: hit count low 32 bits pointer
 * @param  hit_count_high: hit count high 32 bits pointer
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_l1c_hit_count_get(uint32_t *hit_count_low, uint32_t *hit_count_high)
{
    *hit_count_low = getreg32(0x40009000 + 0x4);
    *hit_count_high = getreg32(0x40009000 + 0x8);
}

/****************************************************************************/ /**
 * @brief  Get miss count
 *
 * @param  None
 *
 * @return Miss count
 *
*******************************************************************************/
__WEAK
uint32_t ATTR_TCM_SECTION bflb_l1c_miss_count_get(void)
{
    return getreg32(0x40009000 + 0xC);
}

#endif