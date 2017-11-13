/*
 * drv_rtc.h
 *
 *  Created on: 2016Äê12ÔÂ9ÈÕ
 *      Author: Urey
 */

#ifndef _DRV_RTC_H_
#define _DRV_RTC_H_

#include <stdint.h>
#include "x1000.h"

#ifndef	RTC_BASE
#define	RTC_BASE	0xB0003000
#endif

/*************************************************************************
 * RTC
 *************************************************************************/

#define REG_RTC_RTCCR		REG32(RTC_BASE + RTC_RTCCR)
#define REG_RTC_RTCSR		REG32(RTC_BASE + RTC_RTCSR)
#define REG_RTC_RTCSAR		REG32(RTC_BASE + RTC_RTCSAR)
#define REG_RTC_RTCGR		REG32(RTC_BASE + RTC_RTCGR)
#define REG_RTC_HCR		REG32(RTC_BASE + RTC_HCR)
#define REG_RTC_HWFCR		REG32(RTC_BASE + RTC_HWFCR)
#define REG_RTC_HRCR		REG32(RTC_BASE + RTC_HRCR)
#define REG_RTC_HWCR		REG32(RTC_BASE + RTC_HWCR)
#define REG_RTC_HWRSR		REG32(RTC_BASE + RTC_HWRSR)
#define REG_RTC_HSPR		REG32(RTC_BASE + RTC_HSPR)
#define REG_RTC_WENR		REG32(RTC_BASE + RTC_WENR)
#define REG_RTC_CKPCR		REG32(RTC_BASE + RTC_CKPCR)
#define REG_RTC_OWIPCR		REG32(RTC_BASE + RTC_OWIPCR)
#define REG_RTC_PWRONCR 	REG32(RTC_BASE + RTC_PWRONCR)

#define	COLD_BOOT_SIG	0x12345678

/* RTC Control Register */
#define RTC_RTCCR_WRDY_BIT	7
#define RTC_RTCCR_WRDY		(1 << RTC_RTCCR_WRDY_BIT)  /* Write Ready Flag */
#define RTC_RTCCR_1HZ_BIT	6
#define RTC_RTCCR_1HZ		(1 << RTC_RTCCR_1HZ_BIT)  /* 1Hz Flag */
#define RTC_RTCCR_1HZIE_BIT	5
#define RTC_RTCCR_1HZIE		(1 << RTC_RTCCR_1HZIE_BIT)  /* 1Hz Interrupt Enable */
#define RTC_RTCCR_AF_BIT	4
#define RTC_RTCCR_AF		(1 << RTC_RTCCR_AF_BIT)  /* Alarm Flag */
#define RTC_RTCCR_AIE_BIT	3
#define RTC_RTCCR_AIE		(1 << RTC_RTCCR_AIE_BIT)  /* Alarm Interrupt Enable */
#define RTC_RTCCR_AE_BIT	2
#define RTC_RTCCR_AE		(1 << RTC_RTCCR_AE_BIT)  /* Alarm Enable */
#define RTC_RTCCR_SELEXC_BIT	1
#define RTC_RTCCR_SELEXC	(1 << RTC_RTCCR_SELEXC_BIT)
#define RTC_RTCCR_RTCE_BIT	0
#define RTC_RTCCR_RTCE		(1 << RTC_RTCCR_RTCE_BIT)  /* RTC Enable */

/* RTC Regulator Register */
#define RTC_RTCGR_LOCK		(1 << 31) /* Lock Bit */
#define RTC_RTCGR_ADJC_BIT	16
#define RTC_RTCGR_ADJC_MASK	(0x3ff << RTC_RTCGR_ADJC_BIT)
#define RTC_RTCGR_NC1HZ_BIT	0
#define RTC_RTCGR_NC1HZ_MASK	(0xffff << RTC_RTCGR_NC1HZ_BIT)
#define RTCGR_DIV_1HZ		((32767 << RTC_RTCGR_NC1HZ_BIT) & RTC_RTCGR_NC1HZ_MASK )

/* Hibernate Control Register */
#define RTC_HCR_PD		(1 << 0)  /* Power Down */

/* Hibernate Wakeup Filter Counter Register */
#define RTC_HWFCR_BIT		5
#define RTC_HWFCR_MASK		(0x7ff << RTC_HWFCR_BIT)
#define HWFCR_WAIT_TIME(ms)	(((ms) << RTC_HWFCR_BIT) > RTC_HWFCR_MASK ? RTC_HWFCR_MASK : ((ms) << RTC_HWFCR_BIT))

/* Hibernate Reset Counter Register */
#define RTC_HRCR_BIT		5
#define RTC_HRCR_MASK		(0x7f << RTC_HRCR_BIT)
#define HRCR_WAIT_TIME(ms)     (((ms) << RTC_HRCR_BIT) > RTC_HRCR_MASK ? RTC_HRCR_MASK : ((ms) << RTC_HRCR_BIT))

/* Hibernate Wakeup Control Register */
#define RTC_HWCR_EALM		(1 << 0)  /* RTC alarm wakeup enable */

/* Hibernate Wakeup Status Register */
#define RTC_HWRSR_HR		(1 << 5)  /* Hibernate reset */
#define RTC_HWRSR_PPR		(1 << 4)  /* PPR reset */
#define RTC_HWRSR_PIN		(1 << 1)  /* Wakeup pin status bit */
#define RTC_HWRSR_ALM		(1 << 0)  /* RTC alarm status bit */

/* Write Enable Pattern Register */
#define RTC_WENR_WEN		(1 << 31)  /* The write enable flag */
#define RTC_WENR_WENPAT_BIT	0
#define RTC_WENR_WENPAT_MASK	(0xffff << RTC_WENR_WENPAT_BIT)
#define WENR_WENPAT_WRITABLE	(0xa55a)

/* CLK32K Pin Control Register */
#define RTC_CKPCR_CK32RD	(1 << 5)  /* Read this bit will return CLK32K pin status. */
#define RTC_CKPCR_CK32PULL	(1 << 4)  /* Pull up configures. */
#define RTC_CKPCR_CK32CTL_BIT	1
#define RTC_CKPCR_CK32CTL_MASK	(0x3 << RTC_CKPCR_CK32CTL_BIT)
#define RTC_CKPCR_CK32D		(1 << 0)

/* Power Monitor Register */
#define RTC_PMCR_NBF		(1 << 0)  /* No RTC battery flag */

/* Hibernate scratch pattern register(HSPR) */
#define HSPR_RTCV               0x52544356      /* The value is 'RTCV', means rtc is valid */

#ifndef __ASSEMBLER__
/***************************************************************************
 * RTC ops
 ***************************************************************************/

#define __rtc_write_ready()  			( (REG_RTC_RTCCR & RTC_RTCCR_WRDY) >> RTC_RTCCR_WRDY_BIT )
#define __rtc_enabled()        		( REG_RTC_RTCCR |= RTC_RTCCR_RTCE )
#define __rtc_disabled()         		( REG_RTC_RTCCR &= ~RTC_RTCCR_RTCE )
#define __rtc_enable_alarm()         	( REG_RTC_RTCCR |= RTC_RTCCR_AE )
#define __rtc_disable_alarm()         	( REG_RTC_RTCCR &= ~RTC_RTCCR_AE )
#define __rtc_enable_alarm_irq()       ( REG_RTC_RTCCR |= RTC_RTCCR_AIE )
#define __rtc_disable_alarm_irq()      ( REG_RTC_RTCCR &= ~RTC_RTCCR_AIE )
#define __rtc_enable_1Hz_irq()         ( REG_RTC_RTCCR |= RTC_RTCCR_1HZIE )
#define __rtc_disable_1Hz_irq()        ( REG_RTC_RTCCR &= ~RTC_RTCCR_1HZIE )

#define __rtc_get_1Hz_flag()           ( (REG_RTC_RTCCR >> RTC_RTCCR_1HZIE_BIT) & 0x1 )
#define __rtc_clear_1Hz_flag()         ( REG_RTC_RTCCR &= ~RTC_RTCCR_1HZ )
#define __rtc_get_alarm_flag()         ( (REG_RTC_RTCCR >> RTC_RTCCR_AF_BIT) & 0x1 )
#define __rtc_clear_alarm_flag()       ( REG_RTC_RTCCR &= ~RTC_RTCCR_AF )

#define __rtc_get_second()   			( REG_RTC_RTCSR )
#define __rtc_set_second(v)   			( REG_RTC_RTCSR = v )

#define __rtc_get_alarm_second()   	( REG_RTC_RTCSAR )
#define __rtc_set_alarm_second(v)   	( REG_RTC_RTCSAR = v )

#define __rtc_RGR_is_locked()       	( (REG_RTC_RTCGR >> RTC_RTCGR_LOCK) )
#define __rtc_lock_RGR()       		( REG_RTC_RTCGR |= RTC_RTCGR_LOCK )
#define __rtc_unlock_RGR()       		( REG_RTC_RTCGR &= ~RTC_RTCGR_LOCK )
#define __rtc_get_adjc_val()       	( (REG_RTC_RTCGR & RTC_RTCGR_ADJC_MASK) >> RTC_RTCGR_ADJC_BIT )
#define __rtc_set_adjc_val(v)      \
       ( REG_RTC_RTCGR = ( (REG_RTC_RTCGR & ~RTC_RTCGR_ADJC_MASK) | (v << RTC_RTCGR_ADJC_BIT) ))
#define __rtc_get_nc1Hz_val()       	( (REG_RTC_RTCGR & RTC_RTCGR_NC1HZ_MASK) >> RTC_RTCGR_NC1HZ_BIT )
#define __rtc_set_nc1Hz_val(v)      \
       ( REG_RTC_RTCGR = ( (REG_RTC_RTCGR & ~RTC_RTCGR_NC1HZ_MASK) | (v << RTC_RTCGR_NC1HZ_BIT) ))

#define __rtc_power_down()            	( REG_RTC_HCR |= RTC_HCR_PD )

#define __rtc_get_hwfcr_val()         	( REG_RTC_HWFCR & RTC_HWFCR_MASK )
#define __rtc_set_hwfcr_val(v)         ( REG_RTC_HWFCR = (v) & RTC_HWFCR_MASK )
#define __rtc_get_hrcr_val()         	( REG_RTC_HRCR & RTC_HRCR_MASK )
#define __rtc_set_hrcr_val(v)         	( REG_RTC_HRCR = (v) & RTC_HRCR_MASK )

#define __rtc_enable_alarm_wakeup()   	( REG_RTC_HWCR |= RTC_HWCR_EALM )
#define __rtc_disable_alarm_wakeup()   ( REG_RTC_HWCR &= ~RTC_HWCR_EALM )

#define __rtc_status_hib_reset_occur()        	( (REG_RTC_HWRSR >> RTC_HWRSR_HR) & 0x1 )
#define __rtc_status_ppr_reset_occur()        	( (REG_RTC_HWRSR >> RTC_HWRSR_PPR) & 0x1 )
#define __rtc_status_wakeup_pin_waken_up()    	( (REG_RTC_HWRSR >> RTC_HWRSR_PIN) & 0x1 )
#define __rtc_status_alarm_waken_up()        	( (REG_RTC_HWRSR >> RTC_HWRSR_ALM) & 0x1 )
#define __rtc_clear_hib_stat_all()          	( REG_RTC_HWRSR = 0 )

#define __rtc_get_scratch_pattern() 	(REG_RTC_HSPR)
#define __rtc_set_scratch_pattern(n) 	(REG_RTC_HSPR = n )


/* Waiting for the RTC register writing finish */
#define __wait_write_ready()					\
do {											\
	unsigned int timeout = 1;					\
	while (!(rtc_read_reg(RTC_BASE + RTC_RTCCR) & RTC_RTCCR_WRDY) && timeout++);	\
}while(0);

/* Waiting for the RTC register writable */
#define __wait_writable()						\
do {											\
	unsigned int timeout = 1;					\
	__wait_write_ready();						\
	jz_writel((RTC_BASE + RTC_WENR), WENR_WENPAT_WRITABLE);	\
	__wait_write_ready();						\
	while (!(rtc_read_reg(RTC_BASE + RTC_WENR) & RTC_WENR_WEN) && timeout++);	\
}while(0);

/* Basic RTC ops */
#define rtc_read_reg(reg)						\
({												\
	unsigned int data;							\
	do {										\
		data = jz_readl(reg);					\
	} while (jz_readl(reg) != data);				\
	data;										\
})

#define rtc_write_reg(reg, data)				\
do {											\
	__wait_writable();							\
	jz_writel(reg, data);						\
	__wait_write_ready();						\
}while(0);

#define rtc_set_reg(reg, data)	rtc_write_reg(reg, rtc_read_reg(reg) | (data))
#define rtc_clr_reg(reg, data)	rtc_write_reg(reg, rtc_read_reg(reg) & ~(data))


#endif /* __ASSEMBLER__ */

void rtc32k_enable(void);
void rtc32k_disable(void);

#endif /* _DRV_RTC_H_ */
