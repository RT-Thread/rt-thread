/*
*********************************************************************************************************
*                                                AR100 SYSTEM
*                                     AR100 Software System Develop Kits
*                                         clock control unit module
*
*                                    (c) Copyright 2012-2016, Sunny China
*                                             All Rights Reserved
*
* File    : ccu_regs.h
* By      : Sunny
* Version : v1.0
* Date    : 2012-5-7
* Descript: clock control unit register defines.
* Update  : date                auther      ver     notes
*           2012-5-7 8:47:58    Sunny       1.0     Create this file.
*********************************************************************************************************
*/

#ifndef __CCU_REGS_H__
#define __CCU_REGS_H__

#include <sunxi_hal_common.h>

/* refer to prcm spec register description */
typedef struct ccu_cpus_clk_cfg_reg0000 {
    u32 factor_m:5;             /* bit0,  cpus clock ratio */
    u32 reserved2:3;            /* bit5,  reserved */
    u32 factor_n:2;             /* bit8,  cpus post divider */
    u32 reserved1:14;           /* bit10, reserved */
    u32 src_sel:3;              /* bit24, cpus source select */
    u32 reserved0:5;            /* bit27, reserved */
} ccu_cpus_clk_cfg_reg0000_t;

typedef struct ccu_apbs1_cfg_reg000c {
    u32 factor_m:5;             /* bit0,  apbs1 clock divider ratio */
    u32 reserved2:3;            /* bit5,  reserved */
    u32 factor_n:2;             /* bit8,  cpus post divider */
    u32 reserved1:14;           /* bit10, reserved */
    u32 src_sel:3;              /* bit24, cpus source select */
    u32 reserved0:5;            /* bit27, reserved */
} ccu_apbs1_cfg_reg000c_t;

typedef struct ccu_apbs2_cfg_reg0010 {
    u32 factor_m:5;             /* bit0,  cpus clock ratio */
    u32 reserved2:3;            /* bit5,  reserved */
    u32 factor_n:2;             /* bit8,  cpus post divider */
    u32 reserved1:14;           /* bit10, reserved */
    u32 src_sel:3;              /* bit24, cpus source select */
    u32 reserved0:5;            /* bit27, reserved */
} ccu_apbs2_cfg_reg0010_t;

typedef struct ccu_mod_gate_reset_reg {
    u32 gate:1;                 /* bit0,  gate */
    u32 reserved1:15;           /* bit1,  reserved */
    u32 reset:1;                /* bit16, reset */
    u32 reserved0:15;           /* bit17, reserved */
} ccu_mod_gate_reset_reg_t;

typedef struct ccu_mod_clk_reg {
    u32 factor_m:5;             /* bit0,  clock divider ratio m */
    u32 reserved2:3;            /* bit5,  reserved */
    u32 factor_n:2;             /* bit8,  clock pre-divider ratio n */
    u32 reserved1:14;           /* bit10, reserved */
    u32 src_sel:1;              /* bit24, clock source select */
    u32 reserved0:6;            /* bit25, reserved */
    u32 sclk_gate:1;            /* bit31, gating special clock(max clock = 24M) */
} ccu_mod_clk_reg_t;

typedef struct ccu_mod_lpsd_clk_reg {
    u32 factor_m0:5;             /* bit0,  clock divider ratio m0 */
    u32 reserved3:3;            /* bit5,  reserved */
    u32 factor_m1:5;        /* bit8 - bit12,  clock pre-divider ratio m1 */
    u32 reserved2:3;            /* bit13 - bit15, reserved */
    u32 factor_n:2;             /* bit16 - bit17,  clock pre-divider ratio n */
    u32 reserved1:6;            /* bit18 - bit23, reserved */
    u32 src_sel:2;              /* bit24, clock source select */
    u32 reserved0:5;            /* bit26, reserved */
    u32 sclk_gate:1;            /* bit31, gating */
} ccu_mod_lpsd_clk_reg_t;

typedef struct ccu_mod_audio_clk_reg {
    u32 factor_m:5;             /* bit0,  clock divider ratio m */
    u32 reserved2:3;            /* bit5,  reserved */
    u32 factor_n:2;             /* bit8,  clock pre-divider ratio n */
    u32 reserved1:14;           /* bit10, reserved */
    u32 src_sel:2;              /* bit24, clock source select */
    u32 reserved0:5;            /* bit26, reserved */
    u32 sclk_gate:1;            /* bit31, gating */
} ccu_mod_audio_clk_reg_t;

typedef struct ccu_pll_ctrl_reg0240 {
    u32 pll_bias_en:1;          /* bit0,  pll bias enbale */
    u32 gm0:1;                  /* bit1,  gm0 */
    u32 gm1:1;                  /* bit2,  gm1 */
    u32 reserved1:21;           /* bit3,  reserved */
    u32 test_clk_sel:1;         /* bit24, test clock select */
    u32 reserved0:7;            /* bit25, reserved */
} ccu_pll_ctrl_reg0240_t;

typedef struct ccu_pll_ctrl_reg0244 {
    u32 ldo_en:1;               /* bit0,  ldo enable, all pll digital power */
    u32 reserved2:1;            /* bit1,  reserved */
    u32 osc24M_en:1;            /* bit2,  osc24M enable */
    u32 plltest_en:1;           /* bit3,  clock test enable, for verify */
    u32 mbias_en:1;             /* bit4,  chip master bias enable */
    u32 reserved1:11;           /* bit5,  reserved */
    u32 pllvdd_ldo_out_ctrl:3;  /* bit16, pllvdd ldo output control */
    u32 reserved0:5;            /* bit19, reserved */
    u32 key_field:8;            /* bit24, key field LDO enable bit */
} ccu_pll_ctrl_reg0244_t;

typedef struct ccu_sys_pwroff_gate_reg0250 {
    u32 reserved2:2;            /* bit0, reserved */
    u32 vdd_cpus_gate:1;        /* bit2, gating the corresponding modules to the
                     * CPUS power domain when VDD_SYS power off
                     */
    u32 vdd_sys2usb_gate:1;     /* bit3 */
    u32 vdd_ddr_gate:1;         /* bit4 */
    u32 reserved1:3;            /* bit5, reserved */
    u32 vdd_usb2cpus_gate:1;    /* bit8 */
    u32 reserved0:23;           /* bit9, reserved */
} ccu_sys_pwroff_gate_reg0250_t;

typedef struct ccu_ana_pwroff_gate_reg0254 {
    u32 avcc_a_gate:1;          /* bit0, gating the corresponding modules to the
                     * AVCC_A power domain when VDD_SYS power off
                     */
    u32 res_vdd_on_ctrl:1;      /* bit1 */
    u32 reserved0:30;           /* bit2, reserved */
} ccu_ana_pwroff_gate_reg0254_t;

typedef struct ccu_ve_pwroff_gate_reg0258 {
    u32 poweroff_gate:1;         /* bit0, gating the corresponding modules
                      * when VE power off
                      */
    u32 reserved0:31;            /* bit1, reserved */
} ccu_ve_pwroff_gate_reg0258_t;

typedef struct ccu_sys_pwr_rst_reg0260 {
    u32 module_reset : 1; /* bit0, VDD_SYS power domain modules should be
                   * reset before VDD_SYS power on
                   */
    u32 reserved0 : 31;   /* bit1, reserved */
} ccu_sys_pwr_rst_reg0260_t;

typedef struct ccu_prcm_sec_sw_cfg_reg0290 {
    u32 cpus_clk_sec:1;           /* bit0, cpus clk relevant register's security */
    u32 pll_sec:1;                /* bit1, pll ctrl relevant register's security */
    u32 power_sec:1;              /* bit2, power relevant register' security */
    u32 reserved0:29;             /* bit3, reserved */
} ccu_prcm_sec_sw_cfg_reg0290_t;

typedef struct ccu_reg_list {
    volatile ccu_cpus_clk_cfg_reg0000_t     cpus_clk_cfg;   /* 0x0000 */
    volatile u32                            reserved0[2];   /* 0x0004 */
    volatile ccu_apbs1_cfg_reg000c_t        apbs1_cfg;      /* 0x000c */
    volatile ccu_apbs2_cfg_reg0010_t        apbs2_cfg;      /* 0x0010 */
    volatile u32                            reserved1[47];  /* 0x0014 - 0x0D0 */
    volatile ccu_mod_lpsd_clk_reg_t         r_lpsd;     /* 0x00D0 */
    volatile u32                reserved2[18];  /* 0x00D4- 0x011c */

    volatile ccu_mod_gate_reset_reg_t       r_timer;        /* 0x011c */
    volatile u32                            reserved3[3];   /* 0x0120 - 0x0128 */
    volatile ccu_mod_gate_reset_reg_t       r_twd;          /* 0x012c */
    volatile u32                            reserved4[3];   /* 0x0130 - 0x0138 */
    volatile ccu_mod_gate_reset_reg_t       r_pwm;          /* 0x013c */

    volatile ccu_mod_audio_clk_reg_t        r_ac_adc;       /* 0x0140 */
    volatile ccu_mod_audio_clk_reg_t        r_ac_dac;       /* 0x0144 */
    volatile u32                            reserved5[1];   /* 0x0148 */
    volatile ccu_mod_gate_reset_reg_t       r_ac_gate;      /* 0x014c */
    volatile ccu_mod_audio_clk_reg_t        r_dmic;         /* 0x0150 */
    volatile u32                            reserved6[2];   /* 0x0154 - 0x0158 */
    volatile ccu_mod_gate_reset_reg_t       r_dmic_gate;    /* 0x015C */
    volatile u32                            reserved7[4];   /* 0x0160 - 0x016C */
    volatile ccu_mod_audio_clk_reg_t        r_i2s0;         /* 0x0170 */
    volatile ccu_mod_audio_clk_reg_t        r_i2s0_asrc;    /* 0x0174 */
    volatile ccu_mod_audio_clk_reg_t        r_i2s1;         /* 0x0178 */
    volatile u32                            reserved8[4];   /* 0x017C - 0x0188 */

    volatile ccu_mod_gate_reset_reg_t       r_uart;         /* 0x018c */
    volatile u32                            reserved9[3];   /* 0x0190 - 0x0198 */
    volatile ccu_mod_gate_reset_reg_t       r_twi;          /* 0x019c */
    volatile u32                            reserved10[7];   /* 0x01a0 - 0x01b8 */
    volatile ccu_mod_gate_reset_reg_t       r_rsb;          /* 0x01bc */
    volatile ccu_mod_clk_reg_t              r_ir_clk;       /* 0x01c0 */
    volatile u32                            reserved11[2];   /* 0x01c4 - 0x01c8 */
    volatile ccu_mod_gate_reset_reg_t       r_ir;           /* 0x01cc */
    volatile u32                            reserved12[4];   /* 0x01d0 - 0x01dc */
    /* FIXME: no owc register */
    volatile ccu_mod_clk_reg_t              r_owc_clk;      /* 0x01e0 */
    volatile u32                            reserved13[2];   /* 0x01e4 - 0x01e8 */
    volatile ccu_mod_gate_reset_reg_t       r_owc;          /* 0x01ec */
    volatile u32                            reserved14[7];  /* 0x01f0 - 0x0208 */
    volatile ccu_mod_gate_reset_reg_t       r_rtc;          /* 0x020c */
    volatile u32                            reserved15[12]; /* 0x0210 - 0x023c */
    volatile ccu_pll_ctrl_reg0240_t         pll_ctrl0;      /* 0x0240 */
    volatile ccu_pll_ctrl_reg0244_t         pll_ctrl1;      /* 0x0244 */
    volatile u32                            reserved16[2];  /* 0x0248 - 0x024c */
    volatile ccu_sys_pwroff_gate_reg0250_t  sys_pwroff_gate;/* 0x0250 */
    volatile ccu_ana_pwroff_gate_reg0254_t  ana_pwroff_gate;/* 0x0254 */
    volatile ccu_ve_pwroff_gate_reg0258_t   ve_pwroff_gate; /* 0x0258 */
    volatile u32                            reserved17; /* 0x025c */
    volatile ccu_sys_pwr_rst_reg0260_t      sys_pwr_rst;    /* 0x0260 */
    volatile u32                            reserved18[3];  /* 0x0264 - 0x26c */
    volatile u32                            ram_cfg;        /* 0x0270 */
    volatile u32                            ram_test;       /* 0x0274 */
    volatile u32                            reserved19[6];  /* 0x0278 - 0x028c */
    volatile ccu_prcm_sec_sw_cfg_reg0290_t  prcm_sec_sw_cfg;/* 0x0290 */
    volatile u32                            reserved20[87]; /* 0x0294 - 0x03ec */
    volatile u32                            prcm_version;   /* 0x03f0 */
} ccu_reg_list_t;

/* refer to ccmu spec register description */
typedef struct ccu_pll_c0_cpux_reg0000 {
    volatile u32 factor_m:2;        /* bit0,  PLL1 Factor_M */
    volatile u32 reserved3:6;       /* bit2,  reserved */
    volatile u32 factor_n:8;        /* bit8,  PLL1 Factor_N */
    volatile u32 factor_p:2;        /* bit16, PLL1 Factor_P */
    volatile u32 reserved2:6;       /* bit18, reserved */
    volatile u32 lock_time:3;       /* bit24, lock time:freq scaling step */
    volatile u32 reserved1:1;       /* bit27, reserved */
    volatile u32 lock_st:1;         /* bit28, 0-unlocked, 1-locked(PLL has been stable) */
    volatile u32 lock_en:1;         /* bit29, 0-disable lock, 1-enable lock */
    volatile u32 reserved0:1;       /* bit30, reserved */
    volatile u32 enable:1;          /* bit31, 0-disable, 1-enable, (24Mhz*N*K)/(M) */
} ccu_pll_c0_cpux_reg0000_t;

typedef struct ccu_pll_ddr0_reg0010 {
    volatile u32 factor_m0:1;       /* bit0,  factor_m0 */
    volatile u32 factor_m1:1;       /* bit1,  factor_m1 */
    volatile u32 reserved3:6;       /* bit2, reserved */
    volatile u32 factor_n:8;        /* bit8,  factor_n */
    volatile u32 reserved2:8;       /* bit16, reserved */
    volatile u32 sdm_en:1;          /* bit24, sdm enable */
    volatile u32 reserved1:3;       /* bit25, reserved */
    volatile u32 lock_st:1;         /* bit28, lock state */
    volatile u32 lock_en:1;         /* bit29, lock enable */
    volatile u32 reserved0:1;       /* bit30, reserved */
    volatile u32 enable:1;          /* bit31, 0-disable, 1-enable, (24Mhz*N*K)/(M) */
} ccu_pll_ddr0_reg0010_t;

typedef struct ccu_pll_periph_reg0010 {
    volatile u32 reserved0:1;
    volatile u32 factor_m:1;
    volatile u32 reserved1:6;
    volatile u32 factor_n:8;
    volatile u32 factor_p0:3;
    volatile u32 reserved2:1;
    volatile u32 factor_p1:3;
    volatile u32 reserved3:1;
    volatile u32 sdm_en:1;
    volatile u32 reserved4:2;
    volatile u32 output_en:1;
    volatile u32 lock:1;
    volatile u32 lock_en:1;
    volatile u32 reserved5:1;
    volatile u32 enable:1;
} ccu_pll_periph_reg0010_t;

typedef struct ccu_pll_audio0_reg0020 {
    volatile u32 reserved0:1;
    volatile u32 factor_m:1;
    volatile u32 reserved1:6;
    volatile u32 factor_n:8;
    volatile u32 factor_p0:3;
    volatile u32 reserved2:1;
    volatile u32 factor_p1:3;
    volatile u32 reserved3:1;
    volatile u32 sdm_en:1;
    volatile u32 reserved4:2;
    volatile u32 output_en:1;
    volatile u32 lock:1;
    volatile u32 lock_en:1;
    volatile u32 reserved5:1;
    volatile u32 enable:1;
} ccu_pll_audio0_reg0020_t;

typedef struct ccu_pll_periph0_reg0020 {
    volatile u32 factor_m0:1;       /* bit0,  factor_m0 */
    volatile u32 factor_m1:1;       /* bit1,  factor_m1 */
    volatile u32 reserved2:6;       /* bit2, reserved */
    volatile u32 factor_n:8;        /* bit8,  factor_n */
    volatile u32 reserved1:12;      /* bit16, reserved */
    volatile u32 lock_st:1;         /* bit28, lock state */
    volatile u32 lock_en:1;         /* bit29, lock enable */
    volatile u32 reserved0:1;       /* bit30, reserved */
    volatile u32 enable:1;          /* bit31, 0-disable, 1-enable, (24Mhz*N*K)/(M) */
} ccu_pll_periph0_reg0020_t;

typedef struct ccu_pll_periph1_reg0028 {
    volatile u32 factor_m0:1;       /* bit0,  factor_m0 */
    volatile u32 factor_m1:1;       /* bit1,  factor_m1 */
    volatile u32 reserved2:6;       /* bit2, reserved */
    volatile u32 factor_n:8;        /* bit8,  factor_n */
    volatile u32 reserved1:12;      /* bit16, reserved */
    volatile u32 lock_st:1;         /* bit28, lock state */
    volatile u32 lock_en:1;         /* bit29, lock enable */
    volatile u32 reserved0:1;       /* bit30, reserved */
    volatile u32 enable:1;          /* bit31, 0-disable, 1-enable, (24Mhz*N*K)/(M) */
} ccu_pll_periph1_reg0028_t;

typedef struct ccu_pll_audio0_reg {
    volatile u32 factor_m0:1;       /* bit0,  factor_m0 */
    volatile u32 factor_m1:1;       /* bit1,  factor_m1 */
    volatile u32 reserved3:6;       /* bit2, reserved */
    volatile u32 factor_n:8;        /* bit8,  factor_n */
    volatile u32 div_p0:3;          /* bit16, post div-p0 */
    volatile u32 reserved2:1;       /* bit19, reserved */
    volatile u32 div_p1:3;          /* bit20, post div-p1 */
    volatile u32 sdm_enable:1;      /* bit24, pll sdm enable */
    volatile u32 reserved1:2;       /* bit25, reserved */
    volatile u32 pll_out:1;         /* bit27, pll output enable */
    volatile u32 lock_st:1;         /* bit28, lock state */
    volatile u32 lock_en:1;         /* bit29, lock enable */
    volatile u32 reserved0:1;       /* bit30, reserved */
    volatile u32 enable:1;          /* bit31, 0-disable, 1-enable, 1X:(24Mhz*N*M0/M1)/(P)/4 */
} ccu_pll_audio0_reg_t;

typedef struct ccu_pll_audio1_reg {
    volatile u32 factor_m0:1;       /* bit0,  factor_m0 */
    volatile u32 factor_m1:1;       /* bit1,  factor_m1 */
    volatile u32 reserved3:6;       /* bit2, reserved */
    volatile u32 factor_n:8;        /* bit8,  factor_n */
    volatile u32 div_p:6;           /* bit16, post div-p */
    volatile u32 reserved2:2;       /* bit22, reserved */
    volatile u32 sdm_enable:1;      /* bit24, pll sdm enable */
    volatile u32 reserved1:2;       /* bit25, reserved */
    volatile u32 pll_out:1;         /* bit27, pll output enable */
    volatile u32 lock_st:1;         /* bit28, lock state */
    volatile u32 lock_en:1;         /* bit29, lock enable */
    volatile u32 reserved0:1;       /* bit30, reserved */
    volatile u32 enable:1;          /* bit31, 0-disable, 1-enable, 1X:(24Mhz*N*M0/M1)/(P)/4 */
} ccu_pll_audio1_reg_t;

typedef struct ccu_pll_audio0_pat0_reg {
    volatile u32 wave_bot:17;       /* bit0 - bit16, wave bottom */
    volatile u32 freq:2;            /* bit17 - bit18, frequency */
    volatile u32 clk_sel:1;         /* bit19, 0:24M, 1:12M, SDM clk select */
    volatile u32 wave_step:9;       /* bit20 - bit28, wave step */
    volatile u32 freq_mode:2;       /* bit29 - bit30, Spread frequency mode */
    volatile u32 enable:1;          /* bit31, 0-disable, 1-enable, Sigma-Delta Pattern Enable */
} ccu_pll_audio0_pat0_reg_t;

typedef struct ccu_pll_audio1_pat0_reg {
    volatile u32 wave_bot:17;       /* bit0 - bit16, wave bottom */
    volatile u32 freq:2;            /* bit17 - bit18, frequency */
    volatile u32 clk_sel:1;         /* bit19, 0:24M, 1:12M, SDM clk select */
    volatile u32 wave_step:9;       /* bit20 - bit28, wave step */
    volatile u32 freq_mode:2;       /* bit29 - bit30, Spread frequency mode */
    volatile u32 enable:1;          /* bit31, 0-disable, 1-enable, Sigma-Delta Pattern Enable */
} ccu_pll_audio1_pat0_reg_t;

#endif /* __CCU_REGS_H__ */
