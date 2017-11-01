#ifndef __CACHE_H__
#define __CACHE_H__

#include "nds32_intrinsic.h"
#include "nds32.h"

enum cache_t{ICACHE, DCACHE};

static inline unsigned long CACHE_SET(enum cache_t cache){

	if(cache == ICACHE)
		return 64 << ((__nds32__mfsr(NDS32_SR_ICM_CFG) & ICM_CFG_mskISET) >> ICM_CFG_offISET);
	else
		return 64 << ((__nds32__mfsr(NDS32_SR_DCM_CFG) & DCM_CFG_mskDSET) >> DCM_CFG_offDSET);
}

static inline unsigned long CACHE_WAY(enum cache_t cache){

	if(cache == ICACHE)
		return 1 + ((__nds32__mfsr(NDS32_SR_ICM_CFG) & ICM_CFG_mskIWAY) >> ICM_CFG_offIWAY);
	else
		return 1 + ((__nds32__mfsr(NDS32_SR_DCM_CFG) & DCM_CFG_mskDWAY) >> DCM_CFG_offDWAY);
}

static inline unsigned long CACHE_LINE_SIZE(enum cache_t cache){

	if(cache == ICACHE)
		return 8 << (((__nds32__mfsr(NDS32_SR_ICM_CFG) & ICM_CFG_mskISZ) >> ICM_CFG_offISZ) - 1);
	else
		return 8 << (((__nds32__mfsr(NDS32_SR_DCM_CFG) & DCM_CFG_mskDSZ) >> DCM_CFG_offDSZ) - 1);
}

extern void nds32_dcache_invalidate(void);
extern void nds32_dcache_flush(void);
extern void nds32_icache_flush(void);
extern void nds32_dcache_clean_range(unsigned long start, unsigned long end);
extern void nds32_dma_clean_range(unsigned long start, unsigned long end);
extern void nds32_dcache_invalidate_range(unsigned long start, unsigned long end);
extern void nds32_dcache_flush_range(unsigned long start, unsigned long end);
extern void nds32_dcache_writeback_range(unsigned long start, unsigned long end);
extern void nds32_dma_inv_range(unsigned long start, unsigned long end);
extern void nds32_dma_flush_range(unsigned long start, unsigned long end);
extern void nds32_icache_invalidate_range(unsigned long start, unsigned long end);

#endif /* __CACHE_H__ */
