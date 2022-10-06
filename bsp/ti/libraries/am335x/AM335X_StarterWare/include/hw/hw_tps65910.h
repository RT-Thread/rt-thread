

/**
 *  @Component:   PMIC
 *
 *  @Filename:    hw_tps65910.h
 *
 ============================================================================ */
/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/



#ifndef _TPS65910_H_
#define _TPS65910_H_


/***********************************************************************\
 * Register arrays Definition
\***********************************************************************/


/***********************************************************************\
 * Bundle arrays Definition
\***********************************************************************/


/***********************************************************************\
 * Bundles Definition
\***********************************************************************/



/*************************************************************************\
 * Registers Definition
\*************************************************************************/

/* Address of TPS65910A (PMIC - SR)  over I2C0 */
#define  PMIC_SR_I2C_SLAVE_ADDR     (0x12)

#define  PMIC_CNTL_I2C_SLAVE_ADDR   (0x2D)

#define		SECONDS_REG				(0x00)
#define 	MINUTES_REG 			(0x01)
#define 	HOURS_REG 				(0x02)
#define		DAYS_REG				(0x03)
#define		MONTHS_REG 				(0x04)
#define		YEARS_REG				(0x05)
#define		WEEKS_REG				(0x06)
#define		ALARM_SECONDS_REG		(0x08)
#define		ALARM_MINUTES_REG		(0x09)
#define		ALARM_HOURS_REG     	(0x0A)
#define		ALARM_DAYS_REG RW		(0x0B)
#define		ALARM_MONTHS_REG    	(0x0C)
#define		ALARM_YEARS_REG     	(0x0D)
#define		RTC_CTRL_REG RW 		(0x10)
#define		RTC_STATUS_REG			(0x11)
#define		RTC_INTERRUPTS_REG  	(0x12)
#define		RTC_COMP_LSB_REG    	(0x13)
#define		RTC_COMP_MSB_REG    	(0x14)
#define		RTC_RES_PROG_REG    	(0x15)
#define		RTC_RESET_STATUS_REG 	(0x16)
#define		BCK1_REG				(0x17)
#define		BCK2_REG				(0x18)
#define		BCK3_REG				(0x19)
#define		BCK4_REG				(0x1A)
#define		BCK5_REG				(0x1B)
#define		PUADEN_REG				(0x1C)
#define		REF_REG					(0x1D)
#define		VRTC_REG				(0x1E)
#define		VIO_REG					(0x20)
#define		VDD1_REG				(0x21)
#define		VDD1_OP_REG				(0x22)
#define		VDD1_SR_REG				(0x23)
#define		VDD2_REG				(0x24)
#define		VDD2_OP_REG				(0x25)
#define		VDD2_SR_REG				(0x26)
#define		VDD3_REG				(0x27)
#define		VDIG1_REG				(0x30)
#define		VDIG2_REG 				(0x31)
#define		VAUX1_REG 				(0x32)
#define		VAUX2_REG 				(0x33)
#define		VAUX33_REG 				(0x34)
#define		VMMC_REG 				(0x35)
#define		VPLL_REG 				(0x36)
#define		VDAC_REG 				(0x37)
#define		THERM_REG 				(0x38)
#define		BBCH_REG 				(0x39)
#define		DCDCCTRL_REG 			(0x3E)
#define		DEVCTRL_REG 			(0x3F)
#define		DEVCTRL2_REG 			(0x40)
#define		SLEEP_KEEP_LDO_ON_REG   (0x41)
#define		SLEEP_KEEP_RES_ON_REG   (0x42)
#define		SLEEP_SET_LDO_OFF_REG   (0x43)
#define		SLEEP_SET_RES_OFF_REG   (0x44)
#define		EN1_LDO_ASS_REG         (0x45)
#define		EN1_SMPS_ASS_REG       	(0x46)
#define		EN2_LDO_ASS_REG         (0x47)
#define		EN2_SMPS_ASS_REG       	(0x48)
#define		EN3_LDO_ASS_REG         (0x49)
#define		SPARE_REG 				(0x4A)
#define		INT_STS_REG 			(0x50)
#define		INT_MSK_REG 			(0x51)
#define		INT_STS2_REG 			(0x52)
#define		INT_MSK2_REG 			(0x53)
#define		GPIO0_REG 				(0x60)
#define		JTAGVERNUM_REG          (0x80)

/**************************************************************************\
 * Field Definition Macros
\**************************************************************************/

/*	SECONDS_REG	*/
#define PMIC_SECONDS_REG_SEC0						(0x0Fu)
#define PMIC_SECONDS_REG_SEC0_SHIFT					(0x00u)
#define PMIC_SECONDS_REG_SEC1						(0x70u)
#define PMIC_SECONDS_REG_SEC1_SHIFT					(0x04u)

/*	MINUTES_REG	*/
#define PMIC_MINUTES_REG_MIN0						(0x0Fu)
#define PMIC_MINUTES_REG_MIN0_SHIFT                 (0x00u)
#define PMIC_MINUTES_REG_MIN1                       (0x70u)
#define PMIC_MINUTES_REG_MIN1_SHIFT                 (0x04u)

/*	 HOURS_REG	*/
#define PMIC_HOURS_REG_HOUR0						(0x0Fu)
#define PMIC_HOURS_REG_HOUR0_SHIFT					(0x00u)
#define PMIC_HOURS_REG_HOUR1						(0x30u)
#define PMIC_HOURS_REG_HOUR1_SHIFT					(0x04u)
#define PMIC_HOURS_REG_PM_NAM						(0x80u)
#define PMIC_HOURS_REG_PM_NAM_SHIFT					(0x07u)
#define PMIC_HOURS_REG_PM_NAM_AM					(0x0u)
#define PMIC_HOURS_REG_PM_NAM_PM					(0x1u)

/*	DAYS_REG	*/
#define PMIC_DAYS_REG_DAY0							(0x0Fu)
#define PMIC_DAYS_REG_DAY0_SHIFT					(0x00u)
#define PMIC_DAYS_REG_DAY1							(0x30u)
#define PMIC_DAYS_REG_DAY1_SHIFT					(0x04u)

/*	MONTHS_REG	*/
#define PMIC_MONTHS_REG_MONTH0						(0x0Fu)
#define PMIC_MONTHS_REG_MONTH0_SHIFT				(0x00u)
#define PMIC_MONTHS_REG_MONTH1						(0x10u)
#define PMIC_MONTHS_REG_MONTH1_SHIFT				(0x04u)

/*	YEARS_REG	*/
#define PMIC_YEARS_REG_YEAR0						(0x0Fu)
#define PMIC_YEARS_REG_YEAR0_SHIFT					(0x00u)
#define PMIC_YEARS_REG_YEAR1						(0xF0u)
#define PMIC_YEARS_REG_YEAR1_SHIFT					(0x04u)

/*	WEEKS_REG	*/
#define PMIC_WEEKS_REG_WEEK							(0x07u)
#define PMIC_WEEKS_REG_WEEK_SHIFT					(0x00u)

/*	ALARM_SECONDS_REG	*/
#define PMIC_ALARM_SECONDS_REGALARM_SEC0			(0x0Fu)
#define PMIC_ALARM_SECONDS_REGALARM_SEC0_SHIFT		(0x00u)
#define PMIC_ALARM_SECONDS_REGALARM_SEC1			(0x70u)
#define PMIC_ALARM_SECONDS_REGALARM_SEC1_SHIFT		(0x04u)

/*	ALARM_MINUTES_REG	*/
#define PMIC_ALARM_MINUTES_REG_ALARM_MIN0			(0x0Fu)
#define PMIC_ALARM_MINUTES_REG_ALARM_MIN0_SHIFT		(0x00u)
#define PMIC_ALARM_MINUTES_REG_ALARM_MIN1			(0x70u)
#define PMIC_ALARM_MINUTES_REG_ALARM_MIN1_SHIFT		(0x04u)

/*	ALARM_HOURS_REG	*/
#define PMIC_ALARM_HOURS_REG_ALARM_HOUR0			(0x0Fu)
#define PMIC_ALARM_HOURS_REG_ALARM_HOUR0_SHIFT		(0x00u)
#define PMIC_ALARM_HOURS_REG_ALARM_HOUR1			(0x30u)
#define PMIC_ALARM_HOURS_REG_ALARM_HOUR1_SHIFT		(0x04u)
#define PMIC_ALARM_HOURS_REG_ALARM_PM_NAM			(0x80u)
#define PMIC_ALARM_HOURS_REG_ALARM_PM_NAM_AM		(0x0u)
#define PMIC_ALARM_HOURS_REG_ALARM_PM_NAM_PM		(0x1u)

/*	ALARM_DAYS_REG	*/
#define PMIC_ALARM_DAYS_REG_ALARM_DAY0				(0x0Fu)
#define PMIC_ALARM_DAYS_REG_ALARM_DAY0_SHIFT		(0x00u)
#define PMIC_ALARM_DAYS_REG_ALARM_DAY1				(0x30u)
#define PMIC_ALARM_DAYS_REG_ALARM_DAY1_SHIFT		(0x04u)

/*	ALARM_MONTHS_REG	*/
#define PMIC_ALARM_MONTHS_REG_ALARM_MONTH0			(0x0Fu)
#define PMIC_ALARM_MONTHS_REG_ALARM_MONTH0_SHIFT	(0x00u)
#define PMIC_ALARM_MONTHS_REG_ALARM_MONTH1			(0x10u)
#define PMIC_ALARM_MONTHS_REG_ALARM_MONTH1_SHIFT	(0x04u)

/*	ALARM_YEARS_REG	*/
#define PMIC_ALARM_YEARS_REG_ALARM_YEAR0			(0x0Fu)
#define PMIC_ALARM_YEARS_REG_ALARM_YEAR0_SHIFT		(0x00u)
#define PMIC_ALARM_YEARS_REG_ALARM_YEAR1			(0xF0u)
#define PMIC_ALARM_YEARS_REG_ALARM_YEAR1_SHIFT		(0x04u)

/*	RTC_CTRL_REG	*/
#define PMIC_RTC_CTRL_REG_STOP_RTC					(0x01u)
#define PMIC_RTC_CTRL_REG_STOP_RTC_SHIFT			(0x00u)
#define PMIC_RTC_CTRL_REG_STOP_RTC_FROZEN			(0x0u)
#define PMIC_RTC_CTRL_REG_STOP_RTC_RUNNING			(0x1u)

#define PMIC_RTC_CTRL_REG_ROUND_30S					(0x02u)
#define PMIC_RTC_CTRL_REG_ROUND_30S_SHIFT			(0x01u)
#define PMIC_RTC_CTRL_REG_ROUND_30S_NO_ROUND_30S	(0x0u)
#define PMIC_RTC_CTRL_REG_ROUND_30S_ROUND_30S		(0x1u)

#define PMIC_RTC_CTRL_REG_AUTO_COMP					(0x04u)
#define PMIC_RTC_CTRL_REG_AUTO_COMP_SHIFT			(0x02u)
#define PMIC_RTC_CTRL_REG_AUTO_COMP_NO_AUTO_COMP	(0x0u)
#define PMIC_RTC_CTRL_REG_AUTO_COMP_AUTO_COMP		(0x1u)

#define PMIC_RTC_CTRL_REG_MODE_12_24				(0x08u)
#define PMIC_RTC_CTRL_REG_MODE_12_24_SHIFT			(0x03u)
#define PMIC_RTC_CTRL_REG_MODE_12_24_MODE_24		(0x0u)
#define PMIC_RTC_CTRL_REG_MODE_12_24_MODE_12		(0x1u)

#define PMIC_RTC_CTRL_REG_TEST_MODE					(0x10u)
#define PMIC_RTC_CTRL_REG_TEST_MODE_SHIFT			(0x04u)
#define PMIC_RTC_CTRL_REG_TEST_MODE_FUNC_MODE		(0x0u)
#define PMIC_RTC_CTRL_REG_TEST_MODE_TEST_MODE		(0x1u)

#define PMIC_RTC_CTRL_REG_SET_32_COUNTER			(0x20u)
#define PMIC_RTC_CTRL_REG_SET_32_COUNTER_SHIFT		(0x05u)
#define PMIC_RTC_CTRL_REG_SET_32_COUNTER_NO_ACTION	(0x0u)
#define PMIC_RTC_CTRL_REG_SET_32_COUNTER_SET_COMP	(0x1u)

#define PMIC_RTC_CTRL_REG_GET_TIME					(0x40u)
#define PMIC_RTC_CTRL_REG_GET_TIME_SHIFT			(0x06u)
#define PMIC_RTC_CTRL_REG_GET_TIME_RESET			(0x0u)
#define PMIC_RTC_CTRL_REG_GET_TIME_ASSERT			(0x1u)

#define PMIC_RTC_CTRL_REG_RTC_V_OPT					(0x80u)
#define PMIC_RTC_CTRL_REG_RTC_V_OPT_SHIFT			(0x07u)
#define PMIC_RTC_CTRL_REG_RTC_V_OPT_DYN_REG			(0x0u)
#define PMIC_RTC_CTRL_REG_RTC_V_OPT_SHDW_REG		(0x1u)

/*	RTC_STATUS_REG	*/
#define PMIC_RTC_STATUS_REG_RUN						(0x02u)
#define PMIC_RTC_STATUS_REG_RUN_SHIFT				(0x01u)
#define PMIC_RTC_STATUS_REG_RUN_FROZEN				(0x0u)
#define PMIC_RTC_STATUS_REG_RUN_RUNNING				(0x1u)

#define PMIC_RTC_STATUS_REG_EVENT_1S				(0x04u)
#define PMIC_RTC_STATUS_REG_EVENT_1S_SHIFT			(0x02u)

#define PMIC_RTC_STATUS_REG_EVENT_1M				(0x08u)
#define PMIC_RTC_STATUS_REG_EVENT_1M_SHIFT			(0x03u)

#define PMIC_RTC_STATUS_REG_EVENT_1H				(0x10u)
#define PMIC_RTC_STATUS_REG_EVENT_1H_SHIFT			(0x04u)

#define PMIC_RTC_STATUS_REG_EVENT_1D				(0x20u)
#define PMIC_RTC_STATUS_REG_EVENT_1D_SHIFT			(0x05u)

#define PMIC_RTC_STATUS_REG_ALARM					(0x40u)
#define PMIC_RTC_STATUS_REG_ALARM_SHIFT				(0x06u)

#define PMIC_RTC_STATUS_REG_POWER_UP				(0x80u)
#define PMIC_RTC_STATUS_REG_POWER_UP_SHIFT			(0x07u)

/*	RTC_INTERRUPTS_REG	*/
#define PMIC_RTC_INTERRUPTS_REG_EVERY				(0x0Fu)
#define PMIC_RTC_INTERRUPTS_REG_EVERY_SHFT			(0x00u)
#define PMIC_RTC_INTERRUPTS_REG_EVERY_SEC			(0x0u)
#define PMIC_RTC_INTERRUPTS_REG_EVERY_MIN			(0x1u)
#define PMIC_RTC_INTERRUPTS_REG_EVERY_HR			(0x2u)
#define PMIC_RTC_INTERRUPTS_REG_EVERY_DAY			(0x3u)

/*	RTC_COMP_LSB_REG	*/
#define PMIC_RTC_COMP_LSB_REG_RTC_COMP_LSB			(0xFFu)
#define PMIC_RTC_COMP_LSB_REG_RTC_COMP_LSB_SHIFT	(0x00u)

/*	RTC_COMP_MSB_REG	*/
#define PMIC_RTC_COMP_MSB_REG_RTC_COMP_MSB			(0xFFu)
#define PMIC_RTC_COMP_MSB_REG_RTC_COMP_MSB_SHIFT	(0x00u)

/*	RTC_RES_PROG_REG	*/
#define PMIC_RTC_RES_PROG_REG_SW_RES_PROG			(0x3Fu)
#define PMIC_RTC_RES_PROG_REG_SW_RES_PROG_SHIFT		(0x00u)

/*	RTC_RESET_STATUS_REG	*/
#define PMIC_RTC_RESET_STATUS_REG_RESET_STATUS		(0x01u)
#define PMIC_RTC_RESET_STATUS_REG_RESET_STATUS_SHIFT (0x00u)

/*	BCK1_REG	*/
#define PMIC_BCK1_REG_BCKUP							(0xFFu)
#define PMIC_BCK1_REG_BCKUP_SHIFT					(0x00u)

/*	BCK2_REG	*/
#define PMIC_BCK2_REG_BCKUP							(0xFFu)
#define PMIC_BCK2_REG_BCKUP_SHIFT					(0x00u)

/*	BCK3_REG	*/
#define PMIC_BCK3_REG_BCKUP							(0xFFu)
#define PMIC_BCK3_REG_BCKUP_SHIFT					(0x00u)

/*	BCK4_REG	*/
#define PMIC_BCK4_REG_BCKUP							(0xFFu)
#define PMIC_BCK4_REG_BCKUP_SHIFT					(0x00u)

/*	BCK5_REG	*/
#define PMIC_BCK5_REG_BCKUP							(0xFFu)
#define PMIC_BCK5_REG_BCKUP_SHIFT					(0x00u)

/*	PUADEN_REG	*/
#define PMIC_PUADEN_REG_BOOT0P						(0x01u)
#define PMIC_PUADEN_REG_BOOT0P_SHIFT				(0x00u)
#define PMIC_PUADEN_REG_BOOT0P_ENABLED				(0x1u)
#define PMIC_PUADEN_REG_BOOT0P_DISABLED				(0x0u)

#define PMIC_PUADEN_REG_BOOT1P						(0x02u)
#define PMIC_PUADEN_REG_BOOT1P_SHIFT				(0x01u)
#define PMIC_PUADEN_REG_BOOT1P_ENABLED				(0x1u)
#define PMIC_PUADEN_REG_BOOT1P_DISABLED				(0x0u)

#define PMIC_PUADEN_REG_PWRHOLDP					(0x04u)
#define PMIC_PUADEN_REG_PWRHOLDP_SHIFT				(0x02u)
#define PMIC_PUADEN_REG_PWRHOLDP_ENABLED			(0x1u)
#define PMIC_PUADEN_REG_PWRHOLDP_DISABLED			(0x0u)

#define PMIC_PUADEN_REG_SLEEPP						(0x08u)
#define PMIC_PUADEN_REG_SLEEPP_SHIFT				(0x03u)
#define PMIC_PUADEN_REG_SLEEPP_ENABLED				(0x1u)
#define PMIC_PUADEN_REG_SLEEPP_DISABLED				(0x0u)

#define PMIC_PUADEN_REG_PWRONP						(0x10u)
#define PMIC_PUADEN_REG_PWRONP_SHIFT				(0x04u)
#define PMIC_PUADEN_REG_PWRONP_ENABLED				(0x1u)
#define PMIC_PUADEN_REG_PWRONP_DISABLED				(0x0u)

#define PMIC_PUADEN_REG_I2CSRP						(0x20u)
#define PMIC_PUADEN_REG_I2CSRP_SHIFT				(0x05u)
#define PMIC_PUADEN_REG_I2CSRP_ENABLED				(0x1u)
#define PMIC_PUADEN_REG_I2CSRP_DISABLED				(0x0u)

#define PMIC_PUADEN_REG_I2CCTLP						(0x40u)
#define PMIC_PUADEN_REG_I2CCTLP_SHIFT				(0x06u)
#define PMIC_PUADEN_REG_I2CCTLP_ENABLED				(0x1u)
#define PMIC_PUADEN_REG_I2CCTLP_DISABLED			(0x0u)

#define PMIC_PUADEN_REG_EN3P						(0x80u)
#define PMIC_PUADEN_REG_EN3P_SHIFT					(0x07u)
#define PMIC_PUADEN_REG_EN3P_ENABLED				(0x1u)
#define PMIC_PUADEN_REG_EN3P_DISABLED				(0x0u)

/*	REF_REG	*/
#define PMIC_REF_REG_ST								(0x03u)
#define PMIC_REF_REG_ST_SHIFT						(0x00u)
#define PMIC_REF_REG_ST_OFF							(0x0u)
#define PMIC_REF_REG_ST_ON_HI_POW					(0x1u)
#define PMIC_REF_REG_ST_RSVD						(0x2u)
#define PMIC_REF_REG_ST_ON_LOW_POW					(0x3u)

#define PMIC_REF_REG_VMBCH_SEL						(0x0Cu)
#define PMIC_REF_REG_VMBCH_SEL_SHIFT				(0x02u)
#define PMIC_REF_REG_VMBCH_SEL_BYPASS				(0x0u)
#define PMIC_REF_REG_VMBCH_SEL_2_8_V                (0x1u)
#define PMIC_REF_REG_VMBCH_SEL_2_9_V                (0x2u)
#define PMIC_REF_REG_VMBCH_SEL_3_0_V                (0x3u)

/*	VRTC_REG	*/
#define PMIC_VRTC_REG_ST							(0x03u)
#define PMIC_VRTC_REG_ST_SHIFT						(0x00u)
#define PMIC_VRTC_REG_ST_RSVD						(0x0u)
#define PMIC_VRTC_REG_ST_ON_HI_POW                  (0x1u)
#define PMIC_VRTC_REG_ST_RSVD_1                     (0x2u)
#define PMIC_VRTC_REG_ST_ON_LOW_POW                 (0x3u)

#define PMIC_VRTC_REG_VRTC_OFFMASK					(0x08u)
#define PMIC_VRTC_REG_VRTC_OFFMASK_SHIFT			(0x03u)
#define PMIC_VRTC_REG_VRTC_OFFMASK_FULL_LOAD		(0x1u)
#define PMIC_VRTC_REG_VRTC_OFFMASK_LOW_POW			(0x0u)

/*	VIO_REG	*/
#define PMIC_VIO_REG_ST								(0x03u)
#define PMIC_VIO_REG_ST_SHIFT						(0x00u)
#define PMIC_VIO_REG_ST_OFF							(0x0u)
#define PMIC_VIO_REG_ST_ON_HI_POW                   (0x1u)
#define PMIC_VIO_REG_ST_OFF_1                       (0x2u)
#define PMIC_VIO_REG_ST_ON_LOW_POW                  (0x3u)

#define PMIC_VIO_REG_SEL							(0x0Cu)
#define PMIC_VIO_REG_SEL_SHIFT						(0x02u)
#define PMIC_VIO_REG_SEL_1_5_V						(0x0u)
#define PMIC_VIO_REG_SEL_1_8_V                      (0x1u)
#define PMIC_VIO_REG_SEL_2_5_V                      (0x2u)
#define PMIC_VIO_REG_SEL_3_3_V                      (0x3u)

#define PMIC_VIO_REG_ILMAX							(0xC0u)
#define PMIC_VIO_REG_ILMAX_SHIFT					(0x06u)
#define PMIC_VIO_REG_ILMAX_0_5_A					(0x0u)
#define PMIC_VIO_REG_ILMAX_1_0_A_1                  (0x1u)
#define PMIC_VIO_REG_ILMAX_1_0_A_2                  (0x2u)
#define PMIC_VIO_REG_ILMAX_1_0_A_3                  (0x3u)

/*	VDD1_REG	*/
#define PMIC_VDD1_REG_ST							(0x03u)
#define PMIC_VDD1_REG_ST_SHIFT						(0x00u)
#define PMIC_VDD1_REG_ST_OFF						(0x0u)
#define PMIC_VDD1_REG_ST_ON_HI_POW                  (0x1u)
#define PMIC_VDD1_REG_ST_OFF1                       (0x2u)
#define PMIC_VDD1_REG_ST_ON_LOW_POW                 (0x3u)

#define PMIC_VDD1_REG_TSTEP							(0x1Cu)
#define PMIC_VDD1_REG_TSTEP_SHIFT					(0x02u)
#define PMIC_VDD1_REG_TSTEP_0						(0x0u)
#define PMIC_VDD1_REG_TSTEP_12_5					(0x1u)
#define PMIC_VDD1_REG_TSTEP_9_4						(0x2u)
#define PMIC_VDD1_REG_TSTEP_7_5						(0x3u)
#define PMIC_VDD1_REG_TSTEP_6_25					(0x4u)
#define PMIC_VDD1_REG_TSTEP_4_7						(0x5u)
#define PMIC_VDD1_REG_TSTEP_3_12					(0x6u)
#define PMIC_VDD1_REG_TSTEP_2_5						(0x7u)

#define PMIC_VDD1_REG_ILMAX							(0x20u)
#define PMIC_VDD1_REG_ILMAX_SHIFT					(0x05u)
#define PMIC_VDD1_REG_ILMAX_1_0_A					(0x0u)
#define PMIC_VDD1_REG_ILMAX_1_5_A					(0x1u)

#define PMIC_VDD1_REG_VGAIN_SEL						(0xC0u)
#define PMIC_VDD1_REG_VGAIN_SEL_SHIFT				(0x06u)
#define PMIC_VDD1_REG_VGAIN_SEL_X1					(0x0u)
#define PMIC_VDD1_REG_VGAIN_SEL_X1_1                (0x1u)
#define PMIC_VDD1_REG_VGAIN_SEL_X2                  (0x2u)
#define PMIC_VDD1_REG_VGAIN_SEL_X3                  (0x3u)

/*	VDD1_OP_REG	*/
#define PMIC_VDD1_OP_REG_SEL						(0x7Fu)
#define PMIC_VDD1_OP_REG_SEL_SHIFT					(0x00u)

#define PMIC_VDD1_OP_REG_CMD						(0x80u)
#define PMIC_VDD1_OP_REG_CMD_SHIFT					(0x07u)
#define PMIC_VDD1_OP_REG_CMD_OP						(0x0u)
#define PMIC_VDD1_OP_REG_CMD_SR	                    (0x1u)

/*	VDD1_SR_REG	*/
#define PMIC_VDD1_SR_REG_SEL						(0x7Fu)
#define PMIC_VDD1_SR_REG_SEL_SHIFT					(0x00u)

/*	VDD2_REG	*/
#define PMIC_VDD2_REG_ST							(0x03u)
#define PMIC_VDD2_REG_ST_SHIFT						(0x00u)
#define PMIC_VDD2_REG_ST_OFF						(0x0u)
#define PMIC_VDD2_REG_ST_ON_HI_POW                  (0x1u)
#define PMIC_VDD2_REG_ST_OFF_1                      (0x2u)
#define PMIC_VDD2_REG_ST_ON_LOW_POW                 (0x3u)

#define PMIC_VDD2_REG_TSTEP							(0x1Cu)
#define PMIC_VDD2_REG_TSTEP_SHIFT					(0x02u)
#define PMIC_VDD2_REG_TSTEP_0						(0x0u)
#define PMIC_VDD2_REG_TSTEP_12_5					(0x1u)
#define PMIC_VDD2_REG_TSTEP_9_4						(0x2u)
#define PMIC_VDD2_REG_TSTEP_7_5						(0x3u)
#define PMIC_VDD2_REG_TSTEP_6_25					(0x4u)
#define PMIC_VDD2_REG_TSTEP_4_7						(0x5u)
#define PMIC_VDD2_REG_TSTEP_3_12					(0x6u)
#define PMIC_VDD2_REG_TSTEP_2_5						(0x7u)

#define PMIC_VDD2_REG_ILMAX							(0x20u)
#define PMIC_VDD2_REG_ILMAX_SHIFT					(0x05u)
#define PMIC_VDD2_REG_ILMAX_1_0_A					(0x0u)
#define PMIC_VDD2_REG_ILMAX_1_5_A					(0x1u)

#define PMIC_VDD2_REG_VGAIN_SEL						(0xC0u)
#define PMIC_VDD2_REG_VGAIN_SEL_SHIFT				(0x06u)
#define PMIC_VDD2_REG_VGAIN_SEL_X1					(0x0u)
#define PMIC_VDD2_REG_VGAIN_SEL_X1_0                (0x1u)
#define PMIC_VDD2_REG_VGAIN_SEL_X3                  (0x2u)
#define PMIC_VDD2_REG_VGAIN_SEL_X4                  (0x3u)

/*	VDD2_OP_REG	*/
#define PMIC_VDD2_OP_REG_SEL						(0x7Fu)
#define PMIC_VDD2_OP_REG_SEL_SHIFT					(0x00u)

#define PMIC_VDD2_OP_REG_CMD						(0x80u)
#define PMIC_VDD2_OP_REG_CMD_SHIFT					(0x07u)
#define PMIC_VDD2_OP_REG_CMD_OP						(0x0u)
#define PMIC_VDD2_OP_REG_CMD_SR						(0x1u)

/*	VDD2_SR_REG	*/
#define PMIC_VDD2_SR_REG_SEL						(0x7Fu)
#define PMIC_VDD2_SR_REG_SEL_SHIFT					(0x00u)

/*	VDD3_REG	*/
#define PMIC_VDD3_REG_ST							(0x03u)
#define PMIC_VDD3_REG_ST_SHIFT						(0x00u)
#define PMIC_VDD3_REG_ST_OFF						(0x0u)
#define PMIC_VDD3_REG_ST_ON_HI_POW                  (0x1u)
#define PMIC_VDD3_REG_ST_OFF_1                      (0x2u)
#define PMIC_VDD3_REG_ST_ON_LOW_POW                 (0x3u)

#define PMIC_VDD3_REG_CKINEN						(0x04u)
#define PMIC_VDD3_REG_CKINEN_SHIFT					(0x02u)

/*	VDIG1_REG	*/
#define PMIC_VDIG1_REG_ST							(0x03u)
#define PMIC_VDIG1_REG_ST_SHIFT						(0x00u)
#define PMIC_VDIG1_REG_ST_OFF						(0x0u)
#define PMIC_VDIG1_REG_ST_ON_HI_POW                 (0x1u)
#define PMIC_VDIG1_REG_ST_OFF_1                     (0x2u)
#define PMIC_VDIG1_REG_ST_ON_LOW_POW                (0x3u)

#define PMIC_VDIG1_REG_SEL							(0x0Cu)
#define PMIC_VDIG1_REG_SEL_SHIFT					(0x02u)
#define PMIC_VDIG1_REG_SEL_1_2_V					(0x0u)
#define PMIC_VDIG1_REG_SEL_1_5_V                    (0x1u)
#define PMIC_VDIG1_REG_SEL_1_8_V                    (0x2u)
#define PMIC_VDIG1_REG_SEL_2_7_v                    (0x3u)

/*	VDIG2_REG	*/
#define PMIC_VDIG2_REG_ST							(0x03u)
#define PMIC_VDIG2_REG_ST_SHIFT						(0x00u)
#define PMIC_VDIG2_REG_ST_OFF						(0x0u)
#define PMIC_VDIG2_REG_ST_ON_HI_POW                 (0x1u)
#define PMIC_VDIG2_REG_ST_OFF_1                     (0x2u)
#define PMIC_VDIG2_REG_ST_ON_LOW_POW                (0x3u)

#define PMIC_VDIG2_REG_SEL							(0x0Cu)
#define PMIC_VDIG2_REG_SEL_SHIFT					(0x02u)
#define PMIC_VDIG2_REG_SEL_1_0_V					(0x0u)
#define PMIC_VDIG2_REG_SEL_1_1_V                    (0x1u)
#define PMIC_VDIG2_REG_SEL_1_2_V                    (0x2u)
#define PMIC_VDIG2_REG_SEL_1_8_v                    (0x3u)

/*	VAUX1_REG	*/
#define PMIC_VAUX1_REG_ST							(0x03u)
#define PMIC_VAUX1_REG_ST_SHIFT						(0x00u)
#define PMIC_VAUX1_REG_ST_OFF						(0x0u)
#define PMIC_VAUX1_REG_ST_ON_HI_POW                 (0x1u)
#define PMIC_VAUX1_REG_ST_OFF_1                     (0x2u)
#define PMIC_VAUX1_REG_ST_ON_LOW_POW                (0x3u)

#define PMIC_VAUX1_REG_SEL							(0x0Cu)
#define PMIC_VAUX1_REG_SEL_SHIFT					(0x00u)
#define PMIC_VAUX1_REG_SEL_1_8_V					(0x0u)
#define PMIC_VAUX1_REG_SEL_2_5_V                    (0x1u)
#define PMIC_VAUX1_REG_SEL_2_8_V                    (0x2u)
#define PMIC_VAUX1_REG_SEL_2_85_V                   (0x3u)

/*	VAUX2_REG	*/
#define PMIC_VAUX2_REG_ST							(0x03u)
#define PMIC_VAUX2_REG_ST_SHIFT						(0x00u)
#define PMIC_VAUX2_REG_ST_OFF						(0x0u)
#define PMIC_VAUX2_REG_ST_ON_HI_POW                 (0x1u)
#define PMIC_VAUX2_REG_ST_OFF_1                     (0x2u)
#define PMIC_VAUX2_REG_ST_ON_LOW_POW                (0x3u)

#define PMIC_VAUX2_REG_SEL							(0x0Cu)
#define PMIC_VAUX2_REG_SEL_SHIFT					(0x00u)
#define PMIC_VAUX2_REG_SEL_1_8_V					(0x0u)
#define PMIC_VAUX2_REG_SEL_2_8_V                    (0x1u)
#define PMIC_VAUX2_REG_SEL_2_9_V                    (0x2u)
#define PMIC_VAUX2_REG_SEL_3_3_V 	                (0x3u)

/*	VAUX33_REG	*/
#define PMIC_VAUX33_REG_ST							(0x03u)
#define PMIC_VAUX33_REG_ST_SHIFT					(0x00u)
#define PMIC_VAUX33_REG_ST_OFF						(0x0u)
#define PMIC_VAUX33_REG_ST_ON_HI_POW                (0x1u)
#define PMIC_VAUX33_REG_ST_OFF_1                    (0x2u)
#define PMIC_VAUX33_REG_ST_ON_LOW_POW               (0x3u)

#define PMIC_VAUX33_REG_SEL							(0x0Cu)
#define PMIC_VAUX33_REG_SEL_SHIFT					(0x00u)
#define PMIC_VAUX33_REG_SEL_1_8_V					(0x0u)
#define PMIC_VAUX33_REG_SEL_2_0_V                   (0x1u)
#define PMIC_VAUX33_REG_SEL_2_8_V                   (0x2u)
#define PMIC_VAUX33_REG_SEL_3_3_V 	                (0x3u)

/*	VMMC_REG	*/
#define PMIC_VMMC_REG_ST							(0x03u)
#define PMIC_VMMC_REG_ST_SHIFT						(0x00u)
#define PMIC_VMMC_REG_ST_OFF						(0x0u)
#define PMIC_VMMC_REG_ST_ON_HI_POW          	    (0x1u)
#define PMIC_VMMC_REG_ST_OFF_1                  	(0x2u)
#define PMIC_VMMC_REG_ST_ON_LOW_POW               	(0x3u)

#define PMIC_VMMC_REG_SEL							(0x0Cu)
#define PMIC_VMMC_REG_SEL_SHIFT						(0x00u)
#define PMIC_VMMC_REG_SEL_1_8_V						(0x0u)
#define PMIC_VMMC_REG_SEL_2_8_V                   	(0x1u)
#define PMIC_VMMC_REG_SEL_3_0_V                   	(0x2u)
#define PMIC_VMMC_REG_SEL_3_3_V 	                (0x3u)

/*	VPLL_REG	*/
#define PMIC_VPLL_REG_ST							(0x03u)
#define PMIC_VPLL_REG_ST_SHIFT						(0x00u)
#define PMIC_VPLL_REG_ST_OFF						(0x0u)
#define PMIC_VPLL_REG_ST_ON_HI_POW          	    (0x1u)
#define PMIC_VPLL_REG_ST_OFF_1                    	(0x2u)
#define PMIC_VPLL_REG_ST_ON_LOW_POW               	(0x3u)

#define PMIC_VPLL_REG_SEL							(0x0Cu)
#define PMIC_VPLL_REG_SEL_SHIFT						(0x00u)
#define PMIC_VPLL_REG_SEL_1_0_V						(0x0u)
#define PMIC_VPLL_REG_SEL_1_1_V                   	(0x1u)
#define PMIC_VPLL_REG_SEL_1_8_V                   	(0x2u)
#define PMIC_VPLL_REG_SEL_2_5_V 	                (0x3u)

/*	VDAC_REG	*/
#define PMIC_VDAC_REG_ST							(0x03u)
#define PMIC_VDAC_REG_ST_SHIFT						(0x00u)
#define PMIC_VDAC_REG_ST_OFF						(0x0u)
#define PMIC_VDAC_REG_ST_ON_HI_POW          	    (0x1u)
#define PMIC_VDAC_REG_ST_OFF_1                    	(0x2u)
#define PMIC_VDAC_REG_ST_ON_LOW_POW               	(0x3u)

#define PMIC_VDAC_REG_SEL							(0x0Cu)
#define PMIC_VDAC_REG_SEL_SHIFT						(0x00u)
#define PMIC_VDAC_REG_SEL_1_8_V						(0x0u)
#define PMIC_VDAC_REG_SEL_2_6_V                   	(0x1u)
#define PMIC_VDAC_REG_SEL_2_8_V                   	(0x2u)
#define PMIC_VDAC_REG_SEL_2_85_V 	                (0x3u)

/*	Therm_REG	*/
#define PMIC_THERM_REG_THERM_STATE					(0x01u)
#define PMIC_THERM_REG_THERM_STATE_SHIFT			(0x00u)
#define PMIC_THERM_REG_THERM_STATE_DISABLE			(0x0u)
#define PMIC_THERM_REG_THERM_STATE_ENABLE			(0x1u)

#define PMIC_THERM_REG_THERM_HDSEL					(0xC0u)
#define PMIC_THERM_REG_THERM_HDSEL_SHIFT			(0x02u)
#define PMIC_THERM_REG_THERM_HDSEL_LOW				(0x0u)
#define PMIC_THERM_REG_THERM_HDSEL_HIGH				(0x3u)

#define PMIC_THERM_REG_THERM_TS						(0x10u)
#define PMIC_THERM_REG_THERM_TS_SHIFT				(0x04u)
#define PMIC_THERM_REG_THERM_TS_TSH_REACHED			(0x0u)
#define PMIC_THERM_REG_THERM_TS_TSH_NOT_REACHED		(0x1u)

#define PMIC_THERM_REG_THERM_HD						(0x20u)
#define PMIC_THERM_REG_THERM_HD_SHIFT				(0x05u)
#define PMIC_THERM_REG_THERM_HD_TSH_REACHED			(0x0u)
#define PMIC_THERM_REG_THERM_HD_TSH_NOT_REACHED		(0x1u)

/*	BBCH_REG	*/
#define PMIC_BBCH_REG_BBCHEN						(0x01u)
#define PMIC_BBCH_REG_BBCHEN_SHIFT					(0x00u)

#define PMIC_BBCH_REG_BBSEL							(0x06u)
#define PMIC_BBCH_REG_BBSEL_SHIFT					(0x01u)

/*	DCDCCTRL_REG	*/
#define PMIC_DCDCCTRL_REG_DCDCCKSYNC				(0x03u)
#define PMIC_DCDCCTRL_REG_DCDCCKSYNC_SHIFT			(0x00u)
#define PMIC_DCDCCTRL_REG_DCDCCKSYNC_NO_SYNC		(0x0u)
#define PMIC_DCDCCTRL_REG_DCDCCKSYNC_SYNC_WITH_PHASE_SHIFT	(0x1u)
#define PMIC_DCDCCTRL_REG_DCDCCKSYNC_NO_SYNCH       (0x2u)
#define PMIC_DCDCCTRL_REG_DCDCCKSYNC_SYNC           (0x3u)

#define PMIC_DCDCCTRL_REG_DCDCCKEXT					(0x04u)
#define PMIC_DCDCCTRL_REG_DCDCCKEXT_SHIFT			(0x02u)
#define PMIC_DCDCCTRL_REG_DCDCCKEXT_GPIO			(0x0u)
#define PMIC_DCDCCTRL_REG_DCDCCKEXT_EXT_CLK			(0x1u)

#define PMIC_DCDCCTRL_REG_VIO_PSKIP					(0x08u)
#define PMIC_DCDCCTRL_REG_VIO_PSKIP_SHIFT			(0x03u)

#define PMIC_DCDCCTRL_REG_VDD1_PSKIP				(0x10u)
#define PMIC_DCDCCTRL_REG_VDD1_PSKIP_SHIFT			(0x04u)

#define PMIC_DCDCCTRL_REG_VDD2_PSKIP				(0x20u)
#define PMIC_DCDCCTRL_REG_VDD2_PSKIP_SHIFT			(0x05u)

/*	DEVCTRL_REG	*/
#define PMIC_DEVCTRL_REG_DEV_OFF					(0x01u)
#define PMIC_DEVCTRL_REG_DEV_OFF_SHIFT				(0x00u)
#define PMIC_DEVCTRL_REG_DEV_OFF_TO_OFF				(0x1u)

#define PMIC_DEVCTRL_REG_DEV_SLP					(0x02u)
#define PMIC_DEVCTRL_REG_DEV_SLP_SHIFT				(0x01u)
#define PMIC_DEVCTRL_REG_DEV_SLP_SLEEP_TO_ACTIVE	(0x0u)
#define PMIC_DEVCTRL_REG_DEV_SLP_TO_SLEEP			(0x1u)

#define PMIC_DEVCTRL_REG_DEV_ON						(0x04u)
#define PMIC_DEVCTRL_REG_DEV_ON_SHIFT				(0x02u)
#define PMIC_DEVCTRL_REG_DEV_ON_MAINTAIN			(0x1u)

#define PMIC_DEVCTRL_REG_DEV_OFF_RST				(0x08u)
#define PMIC_DEVCTRL_REG_DEV_OFF_RST_SHIFT			(0x03u)
#define PMIC_DEVCTRL_REG_DEV_OFF_RST_TO_OFF			(0x1u)

#define PMIC_DEVCTRL_REG_SR_CTL_I2C_SEL				(0x10u)
#define PMIC_DEVCTRL_REG_SR_CTL_I2C_SEL_SHIFT		(0x04u)
#define PMIC_DEVCTRL_REG_SR_CTL_I2C_SEL_SR_I2C		(0x0u)
#define PMIC_DEVCTRL_REG_SR_CTL_I2C_SEL_CTL_I2C		(0x1u)

#define PMIC_DEVCTRL_REG_CK32K_CTRL					(0x20u)
#define PMIC_DEVCTRL_REG_CK32K_CTRL_SHIFT			(0x05u)
#define PMIC_DEVCTRL_REG_CK32K_CTRL_X_OSC			(0x0u)
#define PMIC_DEVCTRL_REG_CK32K_CTRL_RC_OSC			(0x1u)

#define PMIC_DEVCTRL_REG_RTC_PWDN					(0x40u)
#define PMIC_DEVCTRL_REG_RTC_PWDN_SHIFT				(0x06u)
#define PMIC_DEVCTRL_REG_RTC_PWDN_DIS_RTC			(0x1u)

/*	DEVCTRL2_REG	*/
#define PMIC_DEVCTRL2_REG_IT_POL					(0x01u)
#define PMIC_DEVCTRL2_REG_IT_POL_SHIFT				(0x00u)
#define PMIC_DEVCTRL2_REG_IT_POL_ACTIVE_LOW			(0x0u)
#define PMIC_DEVCTRL2_REG_IT_POL_ACTIVE_HIGH		(0x1u)

#define PMIC_DEVCTRL2_REG_PWRON_LP_RST				(0x02u)
#define PMIC_DEVCTRL2_REG_PWRON_LP_RST_SHIFT		(0x01u)
#define PMIC_DEVCTRL2_REG_PWRON_LP_RST_ALLOW_RST	(0x1u)

#define PMIC_DEVCTRL2_REG_PWRON_LP_OFF				(0x04u)
#define PMIC_DEVCTRL2_REG_PWRON_LP_OFF_SHIFT		(0x02u)
#define PMIC_DEVCTRL2_REG_PWRON_LP_OFF_TURN_OFF		(0x1u)

#define PMIC_DEVCTRL2_REG_SLEEPSIG_POL				(0x08u)
#define PMIC_DEVCTRL2_REG_SLEEPSIG_POL_SHIFT		(0x03u)
#define PMIC_DEVCTRL2_REG_SLEEPSIG_POL_LOW			(0x0u)
#define PMIC_DEVCTRL2_REG_SLEEPSIG_POL_HIGH			(0x1u)

#define PMIC_DEVCTRL2_REG_TSLOT_LENGTH				(0x30u)
#define PMIC_DEVCTRL2_REG_TSLOT_LENGTH_SHIFT		(0x04u)
#define PMIC_DEVCTRL2_REG_TSLOT_LENGTH_0_us			(0x0u)
#define PMIC_DEVCTRL2_REG_TSLOT_LENGTH_200_us       (0x1u)
#define PMIC_DEVCTRL2_REG_TSLOT_LENGTH_500_us       (0x2u)
#define PMIC_DEVCTRL2_REG_TSLOT_LENGTH_2000_us      (0x3u)

/*	SLEEP_KEEP_LDO_ON_REG	*/
#define PMIC_SLEEP_KEEP_LDO_ON_REG_VMMC_KEEPON			(0x01u)
#define PMIC_SLEEP_KEEP_LDO_ON_REG_VMMC_KEEPON_SHIFT	(0x00u)

#define PMIC_SLEEP_KEEP_LDO_ON_REG_VDIG1_KEEPON			(0x02u)
#define PMIC_SLEEP_KEEP_LDO_ON_REG_VDIG1_KEEPON_SHIFT	(0x01u)

#define PMIC_SLEEP_KEEP_LDO_ON_REG_VDIG2_KEEPON			(0x04u)
#define PMIC_SLEEP_KEEP_LDO_ON_REG_VDIG2_KEEPON_SHIFT	(0x02u)

#define PMIC_SLEEP_KEEP_LDO_ON_REG_VAUX1_KEEPON			(0x08u)
#define PMIC_SLEEP_KEEP_LDO_ON_REG_VAUX1_KEEPON_SHIFT	(0x03u)

#define PMIC_SLEEP_KEEP_LDO_ON_REG_VAUX2_KEEPON			(0x10u)
#define PMIC_SLEEP_KEEP_LDO_ON_REG_VAUX2_KEEPON_SHIFT	(0x04u)

#define PMIC_SLEEP_KEEP_LDO_ON_REG_VAUX33_KEEPON		(0x20u)
#define PMIC_SLEEP_KEEP_LDO_ON_REG_VAUX33_KEEPON_SHIFT	(0x05u)

#define PMIC_SLEEP_KEEP_LDO_ON_REG_VPLL_KEEPON			(0x40u)
#define PMIC_SLEEP_KEEP_LDO_ON_REG_VPLL_KEEPON_SHIFT	(0x06u)

#define PMIC_SLEEP_KEEP_LDO_ON_REG_VDAC_KEEPON			(0x80u)
#define PMIC_SLEEP_KEEP_LDO_ON_REG_VDAC_KEEPON_SHIFT	(0x07u)

/*	SLEEP_KEEP_RES_ON_REG	*/
#define PMIC_SLEEP_KEEP_RES_ON_REG_VIO_KEEPON			(0x01u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_VIO_KEEPON_SHIFT		(0x00u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_VIO_KEEPON_SET		(0x0u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_VIO_KEEPON_MAINT		(0x1u)

#define PMIC_SLEEP_KEEP_RES_ON_REG_VDD1_KEEPON			(0x02u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_VDD1_KEEPON_SHIFT    (0x01u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_VDD1_KEEPON_SET		(0x0u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_VDD1_KEEPON_MAINT    (0x1u)

#define PMIC_SLEEP_KEEP_RES_ON_REG_VDD2_KEEPON			(0x04u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_VDD2_KEEPON_SHIFT    (0x02u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_VDD2_KEEPON_SET		(0x0u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_VDD2_KEEPON_MAINT    (0x1u)

#define PMIC_SLEEP_KEEP_RES_ON_REG_VDD3_KEEPON			(0x08u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_VDD3_KEEPON_SHIFT    (0x03u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_VDD3_KEEPON_SET		(0x0u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_VDD3_KEEPON_MAINT    (0x1u)

#define PMIC_SLEEP_KEEP_RES_ON_REG_I2CHS_KEEPON			(0x10u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_I2CHS_KEEPON_SHIFT   (0x04u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_I2CHS_KEEPON_OFF		(0x0u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_I2CHS_KEEPON_MAINT   (0x1u)

#define PMIC_SLEEP_KEEP_RES_ON_REG_VRTC_KEEPON			(0x20u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_VRTC_KEEPON_SHIFT    (0x05u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_VRTC_KEEPON_SET		(0x0u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_VRTC_KEEPON_MAINT    (0x1u)

#define PMIC_SLEEP_KEEP_RES_ON_REG_CLKOUT32K_KEEPON			(0x40u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_CLKOUT32K_KEEPON_SHIFT   (0x06u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_CLKOUT32K_KEEPON_SET		(0x0u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_CLKOUT32K_KEEPON_MAINT   (0x1u)

#define PMIC_SLEEP_KEEP_RES_ON_REG_THERM_KEEPON			(0x80u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_THERM_KEEPON_SHIFT   (0x07u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_THERM_KEEPON_OFF		(0x0u)
#define PMIC_SLEEP_KEEP_RES_ON_REG_THERM_KEEPON_MAINT   (0x1u)

/*	SLEEP_SET_LDO_OFF_REG	*/
#define PMIC_SLEEP_SET_LDO_OFF_REG_VMMC_SETOFF			(0x01u)
#define PMIC_SLEEP_SET_LDO_OFF_REG_VMMC_SETOFF_SHIFT    (0x00u)
#define PMIC_SLEEP_SET_LDO_OFF_REG_VMMC_SETOFF_OFF		(0x1u)

#define PMIC_SLEEP_SET_LDO_OFF_REG_VDIG1_SETOFF         (0x02u)
#define PMIC_SLEEP_SET_LDO_OFF_REG_VDIG1_SETOFF_SHIFT   (0x01u)
#define PMIC_SLEEP_SET_LDO_OFF_REG_VDIG1_SETOFF_OFF		(0x1u)

#define PMIC_SLEEP_SET_LDO_OFF_REG_VDIG2_SETOFF         (0x04u)
#define PMIC_SLEEP_SET_LDO_OFF_REG_VDIG2_SETOFF_SHIFT   (0x02u)
#define PMIC_SLEEP_SET_LDO_OFF_REG_VDIG2_SETOFF_OFF		(0x1u)

#define PMIC_SLEEP_SET_LDO_OFF_REG_VAUX1_SETOFF         (0x08u)
#define PMIC_SLEEP_SET_LDO_OFF_REG_VAUX1_SETOFF_SHIFT   (0x03u)
#define PMIC_SLEEP_SET_LDO_OFF_REG_VAUX1_SETOFF_OFF		(0x1u)

#define PMIC_SLEEP_SET_LDO_OFF_REG_VAUX2_SETOFF         (0x10u)
#define PMIC_SLEEP_SET_LDO_OFF_REG_VAUX2_SETOFF_SHIFT   (0x04u)
#define PMIC_SLEEP_SET_LDO_OFF_REG_VAUX2_SETOFF_OFF		(0x1u)

#define PMIC_SLEEP_SET_LDO_OFF_REG_VAUX33_SETOFF        (0x20u)
#define PMIC_SLEEP_SET_LDO_OFF_REG_VAUX33_SETOFF_SHIFT  (0x05u)
#define PMIC_SLEEP_SET_LDO_OFF_REG_VAUX33_SETOFF_OFF	(0x1u)

#define PMIC_SLEEP_SET_LDO_OFF_REG_VPLL_SETOFF         	(0x40u)
#define PMIC_SLEEP_SET_LDO_OFF_REG_VPLL_SETOFF_SHIFT    (0x06u)
#define PMIC_SLEEP_SET_LDO_OFF_REG_VPLL_SETOFF_OFF		(0x1u)

#define PMIC_SLEEP_SET_LDO_OFF_REG_VDAC_SETOFF          (0x80u)
#define PMIC_SLEEP_SET_LDO_OFF_REG_VDAC_SETOFF_SHIFT    (0x07u)
#define PMIC_SLEEP_SET_LDO_OFF_REG_VDAC_SETOFF_OFF		(0x1u)

/*	SLEEP_SET_RES_OFF_REG	*/
#define PMIC_SLEEP_SET_RES_OFF_REG_VIO_SETOFF			(0x01u)
#define PMIC_SLEEP_SET_RES_OFF_REG_VIO_SETOFF_SHIFT     (0x00u)
#define PMIC_SLEEP_SET_RES_OFF_REG_VIO_SETOFF_OFF		(0x1u)

#define PMIC_SLEEP_SET_RES_OFF_REG_VDD1_SETOFF          (0x02u)
#define PMIC_SLEEP_SET_RES_OFF_REG_VDD1_SETOFF_SHIFT    (0x01u)
#define PMIC_SLEEP_SET_RES_OFF_REG_VDD1_SETOFF_OFF		(0x1u)

#define PMIC_SLEEP_SET_RES_OFF_REG_VDD2_SETOFF          (0x04u)
#define PMIC_SLEEP_SET_RES_OFF_REG_VDD2_SETOFF_SHIFT    (0x02u)
#define PMIC_SLEEP_SET_RES_OFF_REG_VDD2_SETOFF_OFF		(0x1u)

#define PMIC_SLEEP_SET_RES_OFF_REG_VDD3_SETOFF          (0x08u)
#define PMIC_SLEEP_SET_RES_OFF_REG_VDD3_SETOFF_SHIFT    (0x03u)
#define PMIC_SLEEP_SET_RES_OFF_REG_VDD3_SETOFF_OFF		(0x1u)

#define PMIC_SLEEP_SET_RES_OFF_REG_SPARE_SETOFF         (0x10u)
#define PMIC_SLEEP_SET_RES_OFF_REG_SPARE_SETOFF_SHIFT   (0x04u)
#define PMIC_SLEEP_SET_RES_OFF_REG_SPARE_SETOFF_OFF		(0x1u)

#define PMIC_SLEEP_SET_RES_OFF_REG_RSVD

#define PMIC_SLEEP_SET_RES_OFF_REG_DEFAULT_VOLT			(0x80u)
#define PMIC_SLEEP_SET_RES_OFF_REG_DEFAULT_VOLT_SHIFT   (0x07u)
#define PMIC_SLEEP_SET_RES_OFF_REG_DEFAULT_VOLT_PRG		(0x0u)
#define PMIC_SLEEP_SET_RES_OFF_REG_DEFAULT_VOLT_DEF		(0x1u)

/*	EN1_LDO_ASS_REG	*/
#define PMIC_EN1_LDO_ASS_REG_VMMC_EN1					(0x01u)
#define PMIC_EN1_LDO_ASS_REG_VMMC_EN1_SHIFT				(0x00u)

#define PMIC_EN1_LDO_ASS_REG_VDIG1_EN1					(0x02u)
#define PMIC_EN1_LDO_ASS_REG_VDIG1_EN1_SHIFT            (0x01u)

#define PMIC_EN1_LDO_ASS_REG_VDIG2_EN1					(0x04u)
#define PMIC_EN1_LDO_ASS_REG_VDIG2_EN1_SHIFT            (0x02u)

#define PMIC_EN1_LDO_ASS_REG_VAUX1_EN1					(0x08u)
#define PMIC_EN1_LDO_ASS_REG_VAUX1_EN1_SHIFT            (0x03u)

#define PMIC_EN1_LDO_ASS_REG_VAUX2_EN1					(0x10u)
#define PMIC_EN1_LDO_ASS_REG_VAUX2_EN1_SHIFT            (0x04u)

#define PMIC_EN1_LDO_ASS_REG_VAUX33_EN1					(0x20u)
#define PMIC_EN1_LDO_ASS_REG_VAUX33_EN1_SHIFT           (0x05u)

#define PMIC_EN1_LDO_ASS_REG_VPLL_EN1					(0x40u)
#define PMIC_EN1_LDO_ASS_REG_VPLL_EN1_SHIFT             (0x06u)

#define PMIC_EN1_LDO_ASS_REG_VDAC_EN1					(0x80u)
#define PMIC_EN1_LDO_ASS_REG_VDAC_EN1_SHIFT             (0x07u)

/*	EN1_SMPS_ASS_REG	*/
#define PMIC_EN1_SMPS_ASS_REG_VIO_EN1					(0x01u)
#define PMIC_EN1_SMPS_ASS_REG_VIO_EN1_SHIFT             (0x00u)
#define PMIC_EN1_SMPS_ASS_REG_VIO_EN1_SCLSR_EN1         (0x0u)
#define PMIC_EN1_SMPS_ASS_REG_VIO_EN1_NO_EFFECT			(0x1u)

#define PMIC_EN1_SMPS_ASS_REG_VDD1_EN1					(0x02u)
#define PMIC_EN1_SMPS_ASS_REG_VDD1_EN1_SHIFT            (0x01u)
#define PMIC_EN1_SMPS_ASS_REG_VIO_EN1_SCLSR_EN1         (0x0u)
#define PMIC_EN1_SMPS_ASS_REG_VIO_EN1_NO_EFFECT			(0x1u)

#define PMIC_EN1_SMPS_ASS_REG_VDD2_EN1					(0x04u)
#define PMIC_EN1_SMPS_ASS_REG_VDD2_EN1_SHIFT            (0x02u)
#define PMIC_EN1_SMPS_ASS_REG_VIO_EN1_SCLSR_EN1         (0x0u)
#define PMIC_EN1_SMPS_ASS_REG_VIO_EN1_NO_EFFECT			(0x1u)

#define PMIC_EN1_SMPS_ASS_REG_VDD3_EN1					(0x08u)
#define PMIC_EN1_SMPS_ASS_REG_VDD3_EN1_SHIFT            (0x03u)
#define PMIC_EN1_SMPS_ASS_REG_VIO_EN1_SCLSR_EN1	        (0x0u)
#define PMIC_EN1_SMPS_ASS_REG_VIO_EN1_NO_EFFECT			(0x1u)

#define PMIC_EN1_SMPS_ASS_REG_SPARE_EN1					(0x10u)
#define PMIC_EN1_SMPS_ASS_REG_SPARE_EN1_SHIFT           (0x04u)

/*	EN2_LDO_ASS_REG	*/
#define PMIC_EN2_LDO_ASS_REG_VMMC_EN2					(0x01u)
#define PMIC_EN2_LDO_ASS_REG_VMMC_EN2_SHIFT             (0x00u)

#define PMIC_EN2_LDO_ASS_REG_VDIG1_EN2                  (0x02u)
#define PMIC_EN2_LDO_ASS_REG_VDIG1_EN2_SHIFT            (0x01u)

#define PMIC_EN2_LDO_ASS_REG_VDIG2_EN2                  (0x04u)
#define PMIC_EN2_LDO_ASS_REG_VDIG2_EN2_SHIFT            (0x02u)

#define PMIC_EN2_LDO_ASS_REG_VAUX1_EN2                  (0x08u)
#define PMIC_EN2_LDO_ASS_REG_VAUX1_EN2_SHIFT            (0x03u)

#define PMIC_EN2_LDO_ASS_REG_VAUX2_EN2                  (0x10u)
#define PMIC_EN2_LDO_ASS_REG_VAUX2_EN2_SHIFT            (0x04u)

#define PMIC_EN2_LDO_ASS_REG_VAUX33_EN2                 (0x20u)
#define PMIC_EN2_LDO_ASS_REG_VAUX33_EN2_SHIFT           (0x05u)

#define PMIC_EN2_LDO_ASS_REG_VPLL_EN2                   (0x40u)
#define PMIC_EN2_LDO_ASS_REG_VPLL_EN2_SHIFT             (0x06u)

#define PMIC_EN2_LDO_ASS_REG_VDAC_EN2                   (0x80u)
#define PMIC_EN2_LDO_ASS_REG_VDAC_EN2_SHIFT             (0x07u)

/*	EN2_SMPS_ASS_REG	*/
#define PMIC_EN2_SMPS_ASS_REG_VIO_EN2					(0x01u)
#define PMIC_EN2_SMPS_ASS_REG_VIO_EN2_SHIFT             (0x00u)
#define PMIC_EN2_SMPS_ASS_REG_VIO_EN2_REG				(0x0u)
#define PMIC_EN2_SMPS_ASS_REG_VIO_EN2_SCLSR_EN2			(0x1u)

#define PMIC_EN2_SMPS_ASS_REG_VDD1_EN2                  (0x02u)
#define PMIC_EN2_SMPS_ASS_REG_VDD1_EN2_SHIFT            (0x01u)
#define PMIC_EN2_SMPS_ASS_REG_VDD1_EN2_REG				(0x0u)
#define PMIC_EN2_SMPS_ASS_REG_VDD1_EN2_SR_OP            (0x1u)

#define PMIC_EN2_SMPS_ASS_REG_VDD2_EN2                  (0x04u)
#define PMIC_EN2_SMPS_ASS_REG_VDD2_EN2_SHIFT            (0x02u)
#define PMIC_EN2_SMPS_ASS_REG_VDD2_EN2_REG				(0x0u)
#define PMIC_EN2_SMPS_ASS_REG_VDD2_EN2_SR_OP            (0x1u)

#define PMIC_EN2_SMPS_ASS_REG_VDD3_EN2                  (0x08u)
#define PMIC_EN2_SMPS_ASS_REG_VDD3_EN2_SHIFT            (0x03u)
#define PMIC_EN2_SMPS_ASS_REG_VDD3_EN2_REG				(0x0u)
#define PMIC_EN2_SMPS_ASS_REG_VDD3_EN2_SDASR_EN2        (0x1u)

/*	EN3_LDO_ASS_REG	*/
#define PMIC_EN3_LDO_ASS_REG_VMMC_EN3					(0x01u)
#define PMIC_EN3_LDO_ASS_REG_VMMC_EN3_SHIFT             (0x00u)

#define PMIC_EN3_LDO_ASS_REG_VDIG1_EN3                  (0x02u)
#define PMIC_EN3_LDO_ASS_REG_VDIG1_EN3_SHIFT            (0x01u)

#define PMIC_EN3_LDO_ASS_REG_VDIG2_EN3                  (0x04u)
#define PMIC_EN3_LDO_ASS_REG_VDIG2_EN3_SHIFT            (0x02u)

#define PMIC_EN3_LDO_ASS_REG_VAUX1_EN3                  (0x08u)
#define PMIC_EN3_LDO_ASS_REG_VAUX1_EN3_SHIFT            (0x03u)

#define PMIC_EN3_LDO_ASS_REG_VAUX2_EN3                  (0x10u)
#define PMIC_EN3_LDO_ASS_REG_VAUX2_EN3_SHIFT            (0x04u)

#define PMIC_EN3_LDO_ASS_REG_VAUX33_EN3                 (0x20u)
#define PMIC_EN3_LDO_ASS_REG_VAUX33_EN3_SHIFT           (0x05u)

#define PMIC_EN3_LDO_ASS_REG_VPLL_EN3                   (0x40u)
#define PMIC_EN3_LDO_ASS_REG_VPLL_EN3_SHIFT             (0x06u)

#define PMIC_EN3_LDO_ASS_REG_VDAC_EN3                   (0x80u)
#define PMIC_EN3_LDO_ASS_REG_VDAC_EN3_SHIFT             (0x07u)

/*	SPARE_REG	*/
#define PMIC_SPARE_REG									(0xFFu)
#define PMIC_SPARE_REG_SHIFT							(0x00u)

/*	INT_STS_REG	*/
#define PMIC_INT_STS_REG_VMBDCH_IT						(0x01u)
#define PMIC_INT_STS_REG_VMBDCH_IT_SHIFT                (0x00u)

#define PMIC_INT_STS_REG_VMBHI_IT                       (0x02u)
#define PMIC_INT_STS_REG_VMBHI_IT_SHIFT                 (0x01u)

#define PMIC_INT_STS_REG_PWRON_IT                       (0x04u)
#define PMIC_INT_STS_REG_PWRON_IT_SHIFT                 (0x02u)

#define PMIC_INT_STS_REG_PWRON_LP_IT                    (0x08u)
#define PMIC_INT_STS_REG_PWRON_LP_IT_SHIFT              (0x03u)

#define PMIC_INT_STS_REG_PWRHOLD_IT                     (0x10u)
#define PMIC_INT_STS_REG_PWRHOLD_IT_SHIFT               (0x04u)

#define PMIC_INT_STS_REG_HOTDIE_IT                      (0x20u)
#define PMIC_INT_STS_REG_HOTDIE_IT_SHIFT                (0x05u)

#define PMIC_INT_STS_REG_RTC_ALARM_IT                   (0x40u)
#define PMIC_INT_STS_REG_RTC_ALARM_IT_SHIFT             (0x06u)

#define PMIC_INT_STS_REG_RTC_PERIOD_IT                  (0x80u)
#define PMIC_INT_STS_REG_RTC_PERIOD_IT_SHIFT            (0x07u)

/*	INT_MSK_REG	*/
#define PMIC_INT_MSK_REG_VMBDCH_IT_MSK					(0x01u)
#define PMIC_INT_MSK_REG_VMBDCH_IT_MSK_SHIFT            (0x00u)

#define PMIC_INT_MSK_REG_VMBHI_IT_MSK                   (0x02u)
#define PMIC_INT_MSK_REG_VMBHI_IT_MSK_SHIFT             (0x01u)

#define PMIC_INT_MSK_REG_PWRON_IT_MSK                   (0x04u)
#define PMIC_INT_MSK_REG_PWRON_IT_MSK_SHIFT             (0x02u)

#define PMIC_INT_MSK_REG_PWRON_LP_IT_MSK                (0x08u)
#define PMIC_INT_MSK_REG_PWRON_LP_IT_MSK_SHIFT          (0x03u)

#define PMIC_INT_MSK_REG_PWRHOLD_IT_MSK                 (0x10u)
#define PMIC_INT_MSK_REG_PWRHOLD_IT_MSK_SHIFT           (0x04u)

#define PMIC_INT_MSK_REG_HOTDIE_IT_MSK                  (0x20u)
#define PMIC_INT_MSK_REG_HOTDIE_IT_MSK_SHIFT            (0x05u)

#define PMIC_INT_MSK_REG_RTC_ALARM_IT_MSK               (0x40u)
#define PMIC_INT_MSK_REG_RTC_ALARM_IT_MSK_SHIFT         (0x06u)

#define PMIC_INT_MSK_REG_RTC_PERIOD_IT_MSK              (0x80u)
#define PMIC_INT_MSK_REG_RTC_PERIOD_IT_MSK_SHIFT        (0x07u)

/*	INT_STS2_REG	*/
#define PMIC_INT_STS2_REG_GPIO0_R_IT					(0x01u)
#define PMIC_INT_STS2_REG_GPIO0_R_IT_SHIFT				(0x00u)

#define PMIC_INT_STS2_REG_GPIO0_F_IT					(0x02u)
#define PMIC_INT_STS2_REG_GPIO0_F_IT_SHIFT				(0x01u)

/*	INT_MSK2_REG	*/
#define PMIC_INT_MSK2_REG_GPIO0_R_IT_MSK				(0x01u)
#define PMIC_INT_MSK2_REG_GPIO0_R_IT_MSK_SHIFT          (0x00u)

#define PMIC_INT_MSK2_REG_GPIO0_F_IT_MSK                (0x02u)
#define PMIC_INT_MSK2_REG_GPIO0_F_IT_MSK_SHIFT          (0x01u)

/*	GPIO0_REG	*/
#define PMIC_GPIO0_REG_GPIO_SET							(0x01u)
#define PMIC_GPIO0_REG_GPIO_SET_SHIFT                   (0x00u)

#define PMIC_GPIO0_REG_GPIO_STS                         (0x02u)
#define PMIC_GPIO0_REG_GPIO_STS_SHIFT                   (0x01u)

#define PMIC_GPIO0_REG_GPIO_CFG                         (0x04u)
#define PMIC_GPIO0_REG_GPIO_CFG_SHIFT                   (0x02u)
#define PMIC_GPIO0_REG_GPIO_CFG_INPUT					(0x0u)
#define PMIC_GPIO0_REG_GPIO_CFG_OUTPUT                  (0x1u)

#define PMIC_GPIO0_REG_GPIO_PUEN                        (0x08u)
#define PMIC_GPIO0_REG_GPIO_PUEN_SHIFT                  (0x03u)
#define PMIC_GPIO0_REG_GPIO_PUEN_PULL_UP_DIS			(0x0u)
#define PMIC_GPIO0_REG_GPIO_PUEN_PULL_UP_EN             (0x1u)

#define PMIC_GPIO0_REG_GPIO_DEB                         (0x10u)
#define PMIC_GPIO0_REG_GPIO_DEB_SHIFT                   (0x04u)
#define PMIC_GPIO0_REG_GPIO_DEB_91_5_US					(0x0u)
#define PMIC_GPIO0_REG_GPIO_DEB_150_MS                  (0x1u)

/*	JTAGVERNUM_REG	*/
#define PMIC_JTAGVERNUM_REG_VERNUM						(0x0Fu)
#define PMIC_JTAGVERNUM_REG_VERNUM_SHIFT				(0x00u)

#endif


