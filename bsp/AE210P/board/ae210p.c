#include <nds32_intrinsic.h>
#include "debug.h"
#include "nds32.h"
#include "cache.h"


#define CACHE_NONE              0
#define CACHE_WRITEBACK         2
#define CACHE_WRITETHROUGH      3

#if (defined(CONFIG_CPU_ICACHE_ENABLE) || defined(CONFIG_CPU_DCACHE_ENABLE))
/* Cacheable */
#ifdef CONFIG_CPU_DCACHE_WRITETHROUGH
#define CACHE_MODE              CACHE_WRITETHROUGH
#else
#define CACHE_MODE              CACHE_WRITEBACK
#endif
#else
/* Uncacheable */
#define CACHE_MODE              CACHE_NONE
#endif


#define MMU_CTL_MSK                                     \
        (MMU_CTL_mskD                                   \
         | MMU_CTL_mskNTC0                              \
         | MMU_CTL_mskNTC1                              \
         | MMU_CTL_mskNTC2                              \
         | MMU_CTL_mskNTC3                              \
         | MMU_CTL_mskTBALCK                            \
         | MMU_CTL_mskMPZIU                             \
         | MMU_CTL_mskNTM0                              \
         | MMU_CTL_mskNTM1                              \
         | MMU_CTL_mskNTM2                              \
         | MMU_CTL_mskNTM3)
/*
 * NTC0: CACHE_MODE, NTC1~NTC3: Non-cacheable
 * MSC_CFG.ADR24 = 0 : NTM0~NTM3 are mapped to partition 0/0/0/0
 * MSC_CFG.ADR24 = 1 : NTM0~NTM3 are mapped to partition 0/1/2/3
 */
#define MMU_CTL_INIT                                    \
        (0x0UL << MMU_CTL_offD                          \
         | (CACHE_MODE) << MMU_CTL_offNTC0              \
         | 0x0UL << MMU_CTL_offNTC1                     \
         | 0x0UL << MMU_CTL_offNTC2                     \
         | 0x0UL << MMU_CTL_offNTC3                     \
         | 0x0UL << MMU_CTL_offTBALCK                   \
         | 0x0UL << MMU_CTL_offMPZIU                    \
         | 0x0UL << MMU_CTL_offNTM0                     \
         | 0x0UL << MMU_CTL_offNTM1                     \
         | 0x0UL << MMU_CTL_offNTM2                     \
         | 0x0UL << MMU_CTL_offNTM3)

#define MMU_CTL_INIT_ADR24                              \
        (MMU_CTL_INIT                                   \
         | 0x0UL << MMU_CTL_offNTM0                     \
         | 0x1UL << MMU_CTL_offNTM1                     \
         | 0x2UL << MMU_CTL_offNTM2                     \
         | 0x3UL << MMU_CTL_offNTM3)

#define CACHE_CTL_MSK                                   \
        (CACHE_CTL_mskIC_EN                             \
         | CACHE_CTL_mskDC_EN                           \
         | CACHE_CTL_mskICALCK                          \
         | CACHE_CTL_mskDCALCK                          \
         | CACHE_CTL_mskDCCWF                           \
         | CACHE_CTL_mskDCPMW)
/* ICache/DCache enable */
#define CACHE_CTL_CACHE_ON                              \
        (0x1UL << CACHE_CTL_offIC_EN                    \
         | 0x1UL << CACHE_CTL_offDC_EN                  \
         | 0x0UL << CACHE_CTL_offICALCK                 \
         | 0x0UL << CACHE_CTL_offDCALCK                 \
         | 0x1UL << CACHE_CTL_offDCCWF                  \
         | 0x1UL << CACHE_CTL_offDCPMW)

/*
 * Interrupt priority :
 * PIT(IRQ #2): highest priority
 * Others: lowest priority
 */
#define PRI1_DEFAULT            0xFFFFFFFF
#define PRI2_DEFAULT            0xFFFFFFFF


/* This must be a leaf function, no child function */
void _nds32_init_mem(void) __attribute__((naked, optimize("Os")));
void _nds32_init_mem(void)
{
	/* Enable DLM */
	__nds32__mtsr(EDLM_BASE | 0x1, NDS32_SR_DLMB);
	__nds32__dsb();
}

/*
 * Initialize MMU configure and cache ability.
 */
static void mmu_init(void)
{
//#ifndef __NDS32_ISA_V3M__
//	unsigned int reg;
//
//	/* MMU initialization: NTC0~NTC3, NTM0~NTM3 */
//	reg = (__nds32__mfsr(NDS32_SR_MMU_CTL) & ~MMU_CTL_MSK) | MMU_CTL_INIT;
//
//	if (__nds32__mfsr(NDS32_SR_MSC_CFG) & MSC_CFG_mskADR24)
//		reg = (__nds32__mfsr(NDS32_SR_MMU_CTL) & ~MMU_CTL_MSK) | MMU_CTL_INIT_ADR24;
//	else
//		reg = (__nds32__mfsr(NDS32_SR_MMU_CTL) & ~MMU_CTL_MSK) | MMU_CTL_INIT;
//
//	__nds32__mtsr(reg, NDS32_SR_MMU_CTL);
//	__nds32__dsb();
//#endif
}

/*
 * Platform specific initialization
 */
static void plf_init(void)
{
	/* Set default Hardware interrupts priority */
	__nds32__mtsr(PRI1_DEFAULT, NDS32_SR_INT_PRI);
	__nds32__mtsr(PRI2_DEFAULT, NDS32_SR_INT_PRI2);

	/* Mask all HW interrupts except SWI */
	__nds32__mtsr((1 << IRQ_SYS_TICK_VECTOR) | (1 << IRQ_SWI_VECTOR), NDS32_SR_INT_MASK2);

	/* Reset the PIT (timers) */
	REG32(PIT_INT_EN) = 0;		/* disable all timer interrupt */
	REG32(PIT_CH_EN)  = 0;		/* disable all timer */
	REG32(PIT_INT_ST) = -1;		/* clear pending events */
	REG32(PIT_CHNx_LOAD(0)) = 0;	/* clean channel 0 reload */
	REG32(PIT_CHNx_LOAD(1)) = 0;	/* clean channel 1 reload */
	REG32(PIT_CHNx_LOAD(2)) = 0;	/* clean channel 2 reload */
	REG32(PIT_CHNx_LOAD(3)) = 0;	/* clean channel 3 reload */
}

/*
 * All AE210P hardware initialization
 */
void hardware_init(void)
{
	mmu_init();                     /* mmu/cache */
	plf_init();                     /* Perform any platform specific initializations */

#if (defined(CONFIG_CPU_ICACHE_ENABLE) || defined(CONFIG_CPU_DCACHE_ENABLE))
	unsigned int reg;

	/* Invalid ICache */
	nds32_icache_flush();

	/* Invalid DCache */
	nds32_dcache_invalidate();

	/* Enable I/Dcache */
	reg = (__nds32__mfsr(NDS32_SR_CACHE_CTL) & ~CACHE_CTL_MSK) | CACHE_CTL_CACHE_ON;
	__nds32__mtsr(reg, NDS32_SR_CACHE_CTL);
#endif
}


/********************************
 * 	HAL Level : Interrupt
 ********************************/
/* 32IVIC without SOC INTC */

/*
 *	mask/unmask priority >= _irqs_ interrupts
 *	used in ISR & gie diable
 */
uint32_t hal_intc_irq_mask(int _irqs_)
{
	uint32_t prv_msk = __nds32__mfsr(NDS32_SR_INT_MASK2);
	if (_irqs_ == -1 )
	{
		__nds32__mtsr(0, NDS32_SR_INT_MASK2);
	}
	else if (_irqs_ < 32 )
	{
		SR_CLRB32(NDS32_SR_INT_MASK2,_irqs_);
	}
	else
	{
		DEBUG(1,1,"_irqs_:%d, is invalid!\r\n",_irqs_);
		return -1;
	}

	return prv_msk;
}

void hal_intc_irq_unmask(uint32_t _msk_)
{
	__nds32__mtsr( _msk_ , NDS32_SR_INT_MASK2);
}

void hal_intc_irq_clean(int _irqs_)
{
	if ( _irqs_ == IRQ_SWI_VECTOR )
	{
		SR_CLRB32(NDS32_SR_INT_PEND, INT_PEND_offSWI);
	}
	else
	{
		/* PEND2 is W1C */
		SR_SETB32(NDS32_SR_INT_PEND2,_irqs_);
	}
}

void hal_intc_irq_clean_all()
{
	__nds32__mtsr(-1,NDS32_SR_INT_PEND2);
}

void hal_intc_irq_disable(int _irqs_)
{
	SR_CLRB32(NDS32_SR_INT_MASK2,_irqs_);
}

void hal_intc_irq_disable_all()
{
	__nds32__mtsr(0x0,NDS32_SR_INT_MASK2);
}

void hal_intc_irq_enable(int _irqs_)
{
	SR_SETB32(NDS32_SR_INT_MASK2,_irqs_);
}

void hal_intc_irq_set_priority( uint32_t _prio1_, uint32_t _prio2_ )
{
	__nds32__mtsr(_prio1_, NDS32_SR_INT_PRI);
	__nds32__mtsr(_prio2_, NDS32_SR_INT_PRI2);
}

void hal_intc_irq_config(uint8_t _irq_, uint8_t _edge_, uint8_t _falling_){}

void hal_intc_swi_enable()
{
	//SR_SETB32(NDS32_SR_INT_MASK,16);
	SR_SETB32(NDS32_SR_INT_MASK2,IRQ_SWI_VECTOR);
}

void hal_intc_swi_disable()
{
	SR_CLRB32(NDS32_SR_INT_MASK2,IRQ_SWI_VECTOR);
}

void hal_intc_swi_clean()
{
	SR_CLRB32(NDS32_SR_INT_PEND, INT_PEND_offSWI);
}

void hal_intc_swi_trigger()
{
	SR_SETB32(NDS32_SR_INT_PEND,INT_PEND_offSWI);
}

uint32_t hal_intc_get_all_pend()
{
	return __nds32__mfsr(NDS32_SR_INT_PEND2);
}

/********************************
 * 	TIMER HAL Function
 ********************************/
static const uint8_t timer_irq[4] = {IRQ_PIT_VECTOR, IRQ_PIT_VECTOR, IRQ_PIT_VECTOR, IRQ_PIT_VECTOR};


uint32_t hal_timer_irq_mask(uint32_t _tmr_ )
{
	return hal_intc_irq_mask(timer_irq[_tmr_-1]);
}
void hal_timer_irq_unmask(uint32_t _msk_ )
{
	hal_intc_irq_unmask(_msk_);
}

void hal_timer_irq_clear(uint32_t _tmr_ )
{
	/* Clean IP pending, W1C */
#ifndef CONFIG_TX_DEMO
	REG32(PIT_INT_ST) = (0x1 << (5*(_tmr_-1)));
#endif

	hal_intc_irq_clean(timer_irq[_tmr_-1]);
}

void hal_timer_set_period(uint32_t _tmr_, uint32_t _period_ )
{
	REG32(PIT_CHNx_LOAD(_tmr_-1)) = _period_;
	//REG32(PIT_CHNx_COUNT(_tmr_-1))= _period_;
}

void hal_timer_irq_control(uint32_t _tmr_, uint32_t enable )
{
	if (enable)
		REG32(PIT_INT_EN) = REG32(PIT_INT_EN) | (0x1 << (5*(_tmr_-1)));
	else
		REG32(PIT_INT_EN) = REG32(PIT_INT_EN) & ~(0x1 << (5*(_tmr_-1)));
}

void hal_timer_set_upward(uint32_t _tmr_ ,uint32_t up)
{
	if ( up )
		DEBUG(1,1,"PIT Timer only support downward!\r\n");
}
void hal_timer_start(uint32_t _tmr_)
{
	/* 	config channel mode 	 */
	/* 	32 bits timer, APB clock */
	REG32(PIT_CHNx_CTL(_tmr_-1)) = ( PIT_CH_CTL_APBCLK | PIT_CH_CTL_TMR32  );
	/* 	enable channel 	 */
	REG32(PIT_CH_EN) = REG32(PIT_CH_EN) | (0x1 << (5*(_tmr_-1)));
}

void hal_timer_stop(uint32_t _tmr_ )
{
	REG32(PIT_CH_EN) = REG32(PIT_CH_EN) & ~(0x1 << (5*(_tmr_-1)));
}

uint32_t hal_timer_read(uint32_t _tmr_ )
{
	/* By default, timer  would decrease from load value to 0 */
	return REG32( PIT_CHNx_LOAD(_tmr_-1) ) - REG32( PIT_CHNx_COUNT(_tmr_-1) );
}

uint32_t hal_timer_count_read(uint32_t _tmr_ )
{
	return REG32( PIT_CHNx_COUNT(_tmr_-1) );
}

uint32_t hal_timer_irq_status(uint32_t _tmr_)
{
	/* return PIT int status	*/
	/* PIT need #channel & #timer 	*/
	/* just return all int status	*/
	return REG32(PIT_INT_ST);
}
