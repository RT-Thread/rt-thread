/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __SYSCTL_PWR_H__
#define __SYSCTL_PWR_H__

/* created by yangfan */

#include <stdint.h>
#include <stdbool.h>

/* See TRM 2.3.4 Table 2-3-3 */
typedef struct
{
    volatile uint32_t cpu0_pwr_tim;         /* 0x00 */
    volatile uint32_t cpu0_lpi_tim;         /* 0x04 */
    volatile uint32_t cpu0_pwr_lpi_ctl;     /* 0x08 */
    volatile uint32_t cpu0_pwr_lpi_state;   /* 0x0c */

    volatile uint32_t cpu1_pwr_tim;         /* 0x10 */
    volatile uint32_t cpu1_lpi_tim;         /* 0x14 */
    volatile uint32_t cpu1_pwr_lpi_ctl;     /* 0x18 */
    volatile uint32_t cpu1_pwr_lpi_state;   /* 0x1c */

    volatile uint32_t ai_pwr_tim;           /* 0x20 */
    volatile uint32_t ai_lpi_tim;           /* 0x24 */
    volatile uint32_t ai_pwr_lpi_ctl;       /* 0x28 */
    volatile uint32_t ai_pwr_lpi_state;     /* 0x2c */

    volatile uint32_t disp_pwr_tim;         /* 0x30 */
    volatile uint32_t disp_lpi_tim;         /* 0x34 */
    volatile uint32_t disp_gpu_tim;         /* 0x38 */
    volatile uint32_t disp_lpi_ctl;         /* 0x3c */
    volatile uint32_t disp_lpi_state;       /* 0x40 */
    volatile uint32_t disp_reserved[7];     /* 0x44-0x4c, 0x50-0x5c */

    volatile uint32_t shrm_pwr_tim;         /* 0x60 */
    volatile uint32_t shrm_lpi_tim;         /* 0x64 */
    volatile uint32_t shrm_pwr_lpi_ctl;     /* 0x68 */
    volatile uint32_t shrm_pwr_lpi_state;   /* 0x6c */

    volatile uint32_t vpu_pwr_tim;          /* 0x70 */
    volatile uint32_t vpu_lpi_tim;          /* 0x74 */
    volatile uint32_t vpu_qch_tim;          /* 0x78 */
    volatile uint32_t vpu_pwr_lpi_ctl;      /* 0x7c */
    volatile uint32_t vpu_lpi_state;        /* 0x80 */
    volatile uint32_t vpu_reserved[3];      /* 0x84-0x8c */

    volatile uint32_t mctl_pwr_tim0;        /* 0x90 */
    volatile uint32_t mctl_noc_lpi_tim;     /* 0x94 */
    volatile uint32_t mctl_axi_lpi_tim;     /* 0x98 */
    volatile uint32_t mctl_pwr_lpi_ctl;     /* 0x9c */
    volatile uint32_t mctl_clock_switch;    /* 0xa0 */
    volatile uint32_t mctl_lpi_state;       /* 0xa4 */
    volatile uint32_t mctl_reserved[22];    /* 0xa8-0xac, 0xb0-0xbc, 0xc0-0xcc, 0xd0-0xdc, 0xe0-0xec, 0xf0-0xfc */

    volatile uint32_t dpu_pwr_tim;          /* 0x100 */
    volatile uint32_t dpu_lpi_tim;          /* 0x104 */
    volatile uint32_t dpu_pwr_lpi_ctl;      /* 0x108 */
    volatile uint32_t dpu_pwr_lpi_state;    /* 0x10c */

    volatile uint32_t hi_pwr_tim;           /* 0x110 */
    volatile uint32_t hi_lpi_tim;           /* 0x114 */
    volatile uint32_t hi_pwr_lpi_ctl;       /* 0x118 */
    volatile uint32_t hi_lpi_state;         /* 0x11c */

    volatile uint32_t ls_pwr_tim;           /* 0x120 */
    volatile uint32_t ls_lpi_tim;           /* 0x124 */
    volatile uint32_t ls_pwr_lpi_ctl;       /* 0x128 */
    volatile uint32_t ls_lpi_state;         /* 0x12c */

    volatile uint32_t sec_pwr_tim;          /* 0x130 */
    volatile uint32_t sec_lpi_tim;          /* 0x134 */
    volatile uint32_t sec_pwr_lpi_ctl;      /* 0x138 */
    volatile uint32_t sec_pwr_lpi_state;    /* 0x13c */

    volatile uint32_t isp_pwr_tim;          /* 0x140 */
    volatile uint32_t isp_lpi_tim;          /* 0x144 */
    volatile uint32_t isp_pwr_lpi_ctl;      /* 0x148 */
    volatile uint32_t isp_pwr_lpi_state;    /* 0x14c */

    volatile uint32_t pmu_pwr_tim;          /* 0x150 */
    volatile uint32_t pmu_lpi_tim;          /* 0x154 */
    volatile uint32_t pmu_pwr_lpi_ctl;      /* 0x158 */
    volatile uint32_t pmu_pwr_lpi_state;    /* 0x15c */

    volatile uint32_t repair_status;        /* 0x160 */
    volatile uint32_t sram0_repair_tim;     /* 0x164 */
    volatile uint32_t ssys_ctl_gpio_ctl;    /* 0x168 */
    volatile uint32_t ssys_reserved;        /* 0x16c */
    volatile uint32_t ssys_ctl_gpio_en0;    /* 0x170 */
    volatile uint32_t ssys_ctl_gpio_en1;    /* 0x174 */

    volatile uint32_t cpu_repair_tim;       /* 0x178 */
} sysctl_pwr_s;

/* See TRM 2.3.1 Table 2-3-1 */
typedef enum
{
    SYSCTL_PD_CPU1,
    SYSCTL_PD_AI,
    SYSCTL_PD_DISP,
    SYSCTL_PD_VPU,
    SYSCTL_PD_DPU,
    SYSCTL_PD_MAX,
} sysctl_pwr_domain_e;


typedef enum
{
    SYSCTL_PWR_ACK_TO_TIM,  /* idleReq to idleAck max time */
    SYSCTL_PWR_IDLE_TO_TIM, /* idleAck to idle max time */
    SYSCTL_PWR_IDLE_HD_TIM, /* idle hold tim, from idle to cancel idleReq min time */
    SYSCTL_PWR_ISO_SU_TIM,  /* isolation setup tim */
    SYSCTL_PWR_PD_HD_TIM,   /* power done hardware tim */
    SYSCTL_PWR_SU_TIM,      /* Power bringup tim */
    SYSCTL_PWR_WFI_TIM,     /* wait for interrupt tim*/
    SYSCTL_PWR_MAX_TIM,
} sysctl_pwr_tim_e;


bool sysctl_pwr_set_iso_su_tim(volatile uint32_t *reg, uint32_t iso_su_tim);
bool sysctl_pwr_set_pd_hd_tim(volatile uint32_t *reg, uint32_t pd_hd_tim);
bool sysctl_pwr_set_pwr_su_tim(volatile uint32_t *reg, uint32_t pwr_su_tim);
bool sysctl_pwr_set_ack_to_tim(volatile uint32_t *reg, uint32_t ack_to_tim);
bool sysctl_pwr_set_idle_to_tim(volatile uint32_t *reg, uint32_t idle_to_tim);
bool sysctl_pwr_set_idle_hd_tim(volatile uint32_t *reg, uint32_t idle_hd_tim);
bool sysctl_pwr_set_wfi_tim(volatile uint32_t *reg, uint32_t wfi_tim);
bool sysctl_pwr_set_tim(sysctl_pwr_domain_e powerdomain, sysctl_pwr_tim_e timtype, uint32_t tim_value);
bool sysctl_pwr_get_iso_su_tim(volatile uint32_t *reg, uint32_t *iso_su_tim);
bool sysctl_pwr_get_pd_hd_tim(volatile uint32_t *reg, uint32_t *pd_hd_tim);
bool sysctl_pwr_get_pwr_su_tim(volatile uint32_t *reg, uint32_t *pwr_su_tim);
bool sysctl_pwr_get_ack_to_tim(volatile uint32_t *reg, uint32_t *ack_to_tim);
bool sysctl_pwr_get_idle_to_tim(volatile uint32_t *reg, uint32_t *idle_to_tim);
bool sysctl_pwr_get_idle_hd_tim(volatile uint32_t *reg, uint32_t *idle_hd_tim);
bool sysctl_pwr_get_wfi_tim(volatile uint32_t *reg, uint32_t *wfi_tim);
bool sysctl_pwr_get_tim(sysctl_pwr_domain_e powerdomain, sysctl_pwr_tim_e timtype, uint32_t *tim_value);
bool sysctl_pwr_set_poweroff_keep_reset(sysctl_pwr_domain_e powerdomain, bool enable);
bool sysctl_pwr_get_poweroff_keep_reset(sysctl_pwr_domain_e powerdomain, bool *enable);
bool sysctl_pwr_set_auto_pwr(sysctl_pwr_domain_e powerdomain, bool enable);
bool sysctl_pwr_get_auto_pwr(sysctl_pwr_domain_e powerdomain, bool *enable);
bool sysctl_pwr_set_repair_enable(sysctl_pwr_domain_e powerdomain);
bool sysctl_pwr_check_repair_done(sysctl_pwr_domain_e powerdomain);
bool sysctl_pwr_set_lpi(sysctl_pwr_domain_e powerdomain, bool enable);
bool sysctl_pwr_set_pwr_reg(volatile uint32_t *regctl, volatile uint32_t *regsta, bool enable);
bool sysctl_pwr_set_power(sysctl_pwr_domain_e powerdomain, bool enable);

/* Following two APIs are used to control the power on and off of the SOC power domain */
bool sysctl_pwr_up(sysctl_pwr_domain_e powerdomain);
bool sysctl_pwr_off(sysctl_pwr_domain_e powerdomain);

#endif