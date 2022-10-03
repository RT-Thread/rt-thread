#include "rtconfig.h"

/*
 *enable gtimer
 */
.globl gtimer_set_control
gtimer_set_control:
	MSR CNTP_CTL_EL0, X0
	RET

/*
 *set gtimer CNTP_TVAL_EL0 value
 */

.globl gtimer_set_load_value
gtimer_set_load_value:
	MSR CNTP_TVAL_EL0,X0
	RET

/*
 *get gtimer CNTP_TVAL_EL0 value
 */
.globl rt_hw_get_gtimer_val
rt_hw_get_gtimer_val:
	MRS X0,CNTP_TVAL_EL0
	RET

.globl gtimer_get_current_value
gtimer_get_current_value:
	MRS X0,CNTP_TVAL_EL0
	RET

.globl rt_hw_get_cntpct_val
rt_hw_get_cntpct_val:
	MRS X0, CNTPCT_EL0
	RET

/*
 *get gtimer frq value
 */
.globl gtimer_get_counter_frequency
gtimer_get_counter_frequency:
	MRS X0,CNTFRQ_EL0
	RET
