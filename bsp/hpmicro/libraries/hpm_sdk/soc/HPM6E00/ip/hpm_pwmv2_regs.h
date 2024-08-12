/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_PWMV2_H
#define HPM_PWMV2_H

typedef struct {
    __RW uint32_t WORK_CTRL0;                  /* 0x0:  */
    __RW uint32_t UNLOCK;                      /* 0x4:  */
    __RW uint32_t SHADOW_VAL[28];              /* 0x8 - 0x74:  */
    __RW uint32_t FORCE_MODE;                  /* 0x78:  */
    __RW uint32_t WORK_CTRL1;                  /* 0x7C:  */
    __R  uint8_t  RESERVED0[128];              /* 0x80 - 0xFF: Reserved */
    struct {
        __RW uint32_t CFG0;                    /* 0x100:  */
        __RW uint32_t CFG1;                    /* 0x104:  */
        __RW uint32_t DEAD_AREA;               /* 0x108:  */
        __R  uint8_t  RESERVED0[4];            /* 0x10C - 0x10F: Reserved */
    } PWM[8];
    __RW uint32_t TRIGGER_CFG[8];              /* 0x180 - 0x19C:  */
    __R  uint8_t  RESERVED1[80];               /* 0x1A0 - 0x1EF: Reserved */
    __RW uint32_t GLB_CTRL;                    /* 0x1F0:  */
    __RW uint32_t GLB_CTRL2;                   /* 0x1F4:  */
    __R  uint8_t  RESERVED2[8];                /* 0x1F8 - 0x1FF: Reserved */
    __R  uint32_t CNT_RELOAD_WORK[4];          /* 0x200 - 0x20C:  */
    __R  uint32_t CMP_VAL_WORK[24];            /* 0x210 - 0x26C:  */
    __R  uint8_t  RESERVED3[12];               /* 0x270 - 0x27B: Reserved */
    __R  uint32_t FORCE_WORK;                  /* 0x27C:  */
    __R  uint8_t  RESERVED4[32];               /* 0x280 - 0x29F: Reserved */
    __R  uint32_t CNT_VAL[4];                  /* 0x2A0 - 0x2AC:  */
    __RW uint32_t DAC_VALUE_SV[4];             /* 0x2B0 - 0x2BC:  */
    __R  uint8_t  RESERVED5[64];               /* 0x2C0 - 0x2FF: Reserved */
    __RW uint32_t CAPTURE_POS[8];              /* 0x300 - 0x31C:  */
    __R  uint8_t  RESERVED6[96];               /* 0x320 - 0x37F: Reserved */
    __R  uint32_t CAPTURE_NEG[8];              /* 0x380 - 0x39C:  */
    __R  uint8_t  RESERVED7[96];               /* 0x3A0 - 0x3FF: Reserved */
    __RW uint32_t IRQ_STS;                     /* 0x400:  */
    __RW uint32_t IRQ_EN;                      /* 0x404:  */
    __R  uint8_t  RESERVED8[8];                /* 0x408 - 0x40F: Reserved */
    __W  uint32_t IRQ_STS_CMP;                 /* 0x410:  */
    __W  uint32_t IRQ_STS_RELOAD;              /* 0x414:  */
    __W  uint32_t IRQ_STS_CAP_POS;             /* 0x418:  */
    __W  uint32_t IRQ_STS_CAP_NEG;             /* 0x41C:  */
    __W  uint32_t IRQ_STS_FAULT;               /* 0x420:  */
    __W  uint32_t IRQ_STS_BURSTEND;            /* 0x424:  */
    __R  uint8_t  RESERVED9[8];                /* 0x428 - 0x42F: Reserved */
    __RW uint32_t IRQ_EN_CMP;                  /* 0x430:  */
    __RW uint32_t IRQ_EN_RELOAD;               /* 0x434:  */
    __RW uint32_t IRQ_EN_CAP_POS;              /* 0x438:  */
    __RW uint32_t IRQ_EN_CAP_NEG;              /* 0x43C:  */
    __RW uint32_t IRQ_EN_FAULT;                /* 0x440:  */
    __RW uint32_t IRQ_EN_BURSTEND;             /* 0x444:  */
    __R  uint8_t  RESERVED10[56];              /* 0x448 - 0x47F: Reserved */
    __RW uint32_t DMA_EN;                      /* 0x480:  */
    __R  uint8_t  RESERVED11[124];             /* 0x484 - 0x4FF: Reserved */
    struct {
        __RW uint32_t CFG0;                    /* 0x500:  */
        __RW uint32_t CFG1;                    /* 0x504:  */
        __RW uint32_t CFG2;                    /* 0x508:  */
        __RW uint32_t CFG3;                    /* 0x50C:  */
    } CNT[4];
    __RW uint32_t CNT_GLBCFG;                  /* 0x540:  */
    __R  uint8_t  RESERVED12[188];             /* 0x544 - 0x5FF: Reserved */
    struct {
        __RW uint32_t CFG0;                    /* 0x600:  */
        __RW uint32_t CFG1;                    /* 0x604:  */
        __R  uint8_t  RESERVED0[8];            /* 0x608 - 0x60F: Reserved */
    } CAL[16];
    __R  uint8_t  RESERVED13[256];             /* 0x700 - 0x7FF: Reserved */
    struct {
        __RW uint32_t CFG;                     /* 0x800:  */
        __R  uint8_t  RESERVED0[12];           /* 0x804 - 0x80F: Reserved */
    } CMP[24];
} PWMV2_Type;


/* Bitfield definition for register: WORK_CTRL0 */
/*
 * SHADOW_UNLOCK (RW)
 *
 * write 0x… first to unlock, then set related bits in unlock_sel to unlock following shadow registers(from 0x04 to 0x78),
 * otherwise the shadow registers can not be written.
 * The shadow registers will be loaded to work registers only when shadow_lock is 1 or lock is not enabled
 * This bit can be cleared by set shadow_lock bit in work_ctrl1
 */
#define PWMV2_WORK_CTRL0_SHADOW_UNLOCK_MASK (0x80000000UL)
#define PWMV2_WORK_CTRL0_SHADOW_UNLOCK_SHIFT (31U)
#define PWMV2_WORK_CTRL0_SHADOW_UNLOCK_SET(x) (((uint32_t)(x) << PWMV2_WORK_CTRL0_SHADOW_UNLOCK_SHIFT) & PWMV2_WORK_CTRL0_SHADOW_UNLOCK_MASK)
#define PWMV2_WORK_CTRL0_SHADOW_UNLOCK_GET(x) (((uint32_t)(x) & PWMV2_WORK_CTRL0_SHADOW_UNLOCK_MASK) >> PWMV2_WORK_CTRL0_SHADOW_UNLOCK_SHIFT)

/* Bitfield definition for register: UNLOCK */
/*
 * UNLOCK_BIT (RW)
 *
 * bit2 to bit 29 for value_shadow, bit30 for force_mode
 * the shadow registers can be updated only when related unlock_bit is set;
 * this register can only be updated after unlock
 */
#define PWMV2_UNLOCK_UNLOCK_BIT_MASK (0xFFFFFFFFUL)
#define PWMV2_UNLOCK_UNLOCK_BIT_SHIFT (0U)
#define PWMV2_UNLOCK_UNLOCK_BIT_SET(x) (((uint32_t)(x) << PWMV2_UNLOCK_UNLOCK_BIT_SHIFT) & PWMV2_UNLOCK_UNLOCK_BIT_MASK)
#define PWMV2_UNLOCK_UNLOCK_BIT_GET(x) (((uint32_t)(x) & PWMV2_UNLOCK_UNLOCK_BIT_MASK) >> PWMV2_UNLOCK_UNLOCK_BIT_SHIFT)

/* Bitfield definition for register array: SHADOW_VAL */
/*
 * VALUE (RW)
 *
 * shadow registers, if used as reload or compare point, shall be 24bit clock cycles plus 1bit half cycle and 7bit high-resolution delay
 */
#define PWMV2_SHADOW_VAL_VALUE_MASK (0xFFFFFFFFUL)
#define PWMV2_SHADOW_VAL_VALUE_SHIFT (0U)
#define PWMV2_SHADOW_VAL_VALUE_SET(x) (((uint32_t)(x) << PWMV2_SHADOW_VAL_VALUE_SHIFT) & PWMV2_SHADOW_VAL_VALUE_MASK)
#define PWMV2_SHADOW_VAL_VALUE_GET(x) (((uint32_t)(x) & PWMV2_SHADOW_VAL_VALUE_MASK) >> PWMV2_SHADOW_VAL_VALUE_SHIFT)

/* Bitfield definition for register: FORCE_MODE */
/*
 * POLARITY (RW)
 *
 * one bit for one pwm channel, it's used as shadow register when pwm_cfg0.polarity_opt0 is set.
 * output polarity, set to 1 will invert the output(after pwm selection, pair mode, dead area insertion, before force/fault)
 */
#define PWMV2_FORCE_MODE_POLARITY_MASK (0xFF0000UL)
#define PWMV2_FORCE_MODE_POLARITY_SHIFT (16U)
#define PWMV2_FORCE_MODE_POLARITY_SET(x) (((uint32_t)(x) << PWMV2_FORCE_MODE_POLARITY_SHIFT) & PWMV2_FORCE_MODE_POLARITY_MASK)
#define PWMV2_FORCE_MODE_POLARITY_GET(x) (((uint32_t)(x) & PWMV2_FORCE_MODE_POLARITY_MASK) >> PWMV2_FORCE_MODE_POLARITY_SHIFT)

/*
 * FORCE_MODE (RW)
 *
 * 2bit for each PWM channel(0~7);
 * 00:  force output 0
 * 01:  force output 1
 * 10:  output highz(pad_oe_*=0)
 * 11:  no force
 * this field may be changed by software as shadow register , the update time should be defined by chan_cfg.load, only for PWM channels.
 */
#define PWMV2_FORCE_MODE_FORCE_MODE_MASK (0xFFFFU)
#define PWMV2_FORCE_MODE_FORCE_MODE_SHIFT (0U)
#define PWMV2_FORCE_MODE_FORCE_MODE_SET(x) (((uint32_t)(x) << PWMV2_FORCE_MODE_FORCE_MODE_SHIFT) & PWMV2_FORCE_MODE_FORCE_MODE_MASK)
#define PWMV2_FORCE_MODE_FORCE_MODE_GET(x) (((uint32_t)(x) & PWMV2_FORCE_MODE_FORCE_MODE_MASK) >> PWMV2_FORCE_MODE_FORCE_MODE_SHIFT)

/* Bitfield definition for register: WORK_CTRL1 */
/*
 * SHADOW_LOCK (RW)
 *
 * one to lock,  sofware can't write any shadow registers
 * Software have to write 0x…. to work_ctrl0 to clear this bit.
 */
#define PWMV2_WORK_CTRL1_SHADOW_LOCK_MASK (0x80000000UL)
#define PWMV2_WORK_CTRL1_SHADOW_LOCK_SHIFT (31U)
#define PWMV2_WORK_CTRL1_SHADOW_LOCK_SET(x) (((uint32_t)(x) << PWMV2_WORK_CTRL1_SHADOW_LOCK_SHIFT) & PWMV2_WORK_CTRL1_SHADOW_LOCK_MASK)
#define PWMV2_WORK_CTRL1_SHADOW_LOCK_GET(x) (((uint32_t)(x) & PWMV2_WORK_CTRL1_SHADOW_LOCK_MASK) >> PWMV2_WORK_CTRL1_SHADOW_LOCK_SHIFT)

/* Bitfield definition for register of struct array PWM: CFG0 */
/*
 * TRIG_SEL4 (RW)
 *
 * for N=0/2/4/6, clear to select 2 compare point(N*2~N*2+1);
 * set to select 4 compare point(N*2~N*2+3);
 * or use 2 compare point(N*2+2~N*2+3);
 * for N=1/3/5/7, this bit is no means, it can work on pair mode, or use 2 compare point (N*2+2~N*2+3);
 * assume select ab or abcd,  abcd can between 0 and 2T.
 * output will be 1 when counter value between a and b;
 * if b<=a then output all 0; if b>=(T+a), then output all 1;
 */
#define PWMV2_PWM_CFG0_TRIG_SEL4_MASK (0x1000000UL)
#define PWMV2_PWM_CFG0_TRIG_SEL4_SHIFT (24U)
#define PWMV2_PWM_CFG0_TRIG_SEL4_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG0_TRIG_SEL4_SHIFT) & PWMV2_PWM_CFG0_TRIG_SEL4_MASK)
#define PWMV2_PWM_CFG0_TRIG_SEL4_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG0_TRIG_SEL4_MASK) >> PWMV2_PWM_CFG0_TRIG_SEL4_SHIFT)

/*
 * FAULT_SEL_ASYNC (RW)
 *
 * select from 16bit async fault from pad
 */
#define PWMV2_PWM_CFG0_FAULT_SEL_ASYNC_MASK (0xF00U)
#define PWMV2_PWM_CFG0_FAULT_SEL_ASYNC_SHIFT (8U)
#define PWMV2_PWM_CFG0_FAULT_SEL_ASYNC_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG0_FAULT_SEL_ASYNC_SHIFT) & PWMV2_PWM_CFG0_FAULT_SEL_ASYNC_MASK)
#define PWMV2_PWM_CFG0_FAULT_SEL_ASYNC_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG0_FAULT_SEL_ASYNC_MASK) >> PWMV2_PWM_CFG0_FAULT_SEL_ASYNC_SHIFT)

/*
 * FAULT_POL_ASYNC (RW)
 *
 * fault polarity for input fault from pad, 1-active low;  0-active high;
 */
#define PWMV2_PWM_CFG0_FAULT_POL_ASYNC_MASK (0x40U)
#define PWMV2_PWM_CFG0_FAULT_POL_ASYNC_SHIFT (6U)
#define PWMV2_PWM_CFG0_FAULT_POL_ASYNC_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG0_FAULT_POL_ASYNC_SHIFT) & PWMV2_PWM_CFG0_FAULT_POL_ASYNC_MASK)
#define PWMV2_PWM_CFG0_FAULT_POL_ASYNC_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG0_FAULT_POL_ASYNC_MASK) >> PWMV2_PWM_CFG0_FAULT_POL_ASYNC_SHIFT)

/*
 * FAULT_EN_ASYNC (RW)
 *
 * set to enable the input async faults from pad directly
 */
#define PWMV2_PWM_CFG0_FAULT_EN_ASYNC_MASK (0x20U)
#define PWMV2_PWM_CFG0_FAULT_EN_ASYNC_SHIFT (5U)
#define PWMV2_PWM_CFG0_FAULT_EN_ASYNC_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG0_FAULT_EN_ASYNC_SHIFT) & PWMV2_PWM_CFG0_FAULT_EN_ASYNC_MASK)
#define PWMV2_PWM_CFG0_FAULT_EN_ASYNC_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG0_FAULT_EN_ASYNC_MASK) >> PWMV2_PWM_CFG0_FAULT_EN_ASYNC_SHIFT)

/*
 * FAULT_EN_SYNC (RW)
 *
 * set to enable the input faults from trig_mux(trigger_in[0] for channel0/1, 1 for 23, 2 for 45, 3 for 67)
 */
#define PWMV2_PWM_CFG0_FAULT_EN_SYNC_MASK (0x10U)
#define PWMV2_PWM_CFG0_FAULT_EN_SYNC_SHIFT (4U)
#define PWMV2_PWM_CFG0_FAULT_EN_SYNC_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG0_FAULT_EN_SYNC_SHIFT) & PWMV2_PWM_CFG0_FAULT_EN_SYNC_MASK)
#define PWMV2_PWM_CFG0_FAULT_EN_SYNC_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG0_FAULT_EN_SYNC_MASK) >> PWMV2_PWM_CFG0_FAULT_EN_SYNC_SHIFT)

/*
 * POL_UPDATE_SEL (RW)
 *
 * used when polarity_opt0 is set, define when to update polarity working register.
 * 0:  software set work_ctrl1.shadow_lock bit
 * 1:  update at reload point;
 */
#define PWMV2_PWM_CFG0_POL_UPDATE_SEL_MASK (0x4U)
#define PWMV2_PWM_CFG0_POL_UPDATE_SEL_SHIFT (2U)
#define PWMV2_PWM_CFG0_POL_UPDATE_SEL_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG0_POL_UPDATE_SEL_SHIFT) & PWMV2_PWM_CFG0_POL_UPDATE_SEL_MASK)
#define PWMV2_PWM_CFG0_POL_UPDATE_SEL_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG0_POL_UPDATE_SEL_MASK) >> PWMV2_PWM_CFG0_POL_UPDATE_SEL_SHIFT)

/*
 * OUT_POLARITY (RW)
 *
 * output polarity, set to 1 will invert the output(after pwm selection, pair mode, dead area insertion, before force/fault)
 * when polarity_opt0 is set, this bit is controlled by shadow register, can't be writable; read as working register
 * use compare channel settings(in cmp_cfg) as shadow register update
 */
#define PWMV2_PWM_CFG0_OUT_POLARITY_MASK (0x2U)
#define PWMV2_PWM_CFG0_OUT_POLARITY_SHIFT (1U)
#define PWMV2_PWM_CFG0_OUT_POLARITY_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG0_OUT_POLARITY_SHIFT) & PWMV2_PWM_CFG0_OUT_POLARITY_MASK)
#define PWMV2_PWM_CFG0_OUT_POLARITY_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG0_OUT_POLARITY_MASK) >> PWMV2_PWM_CFG0_OUT_POLARITY_SHIFT)

/*
 * POLARITY_OPT0 (RW)
 *
 * set to use shadow polarity
 */
#define PWMV2_PWM_CFG0_POLARITY_OPT0_MASK (0x1U)
#define PWMV2_PWM_CFG0_POLARITY_OPT0_SHIFT (0U)
#define PWMV2_PWM_CFG0_POLARITY_OPT0_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG0_POLARITY_OPT0_SHIFT) & PWMV2_PWM_CFG0_POLARITY_OPT0_MASK)
#define PWMV2_PWM_CFG0_POLARITY_OPT0_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG0_POLARITY_OPT0_MASK) >> PWMV2_PWM_CFG0_POLARITY_OPT0_SHIFT)

/* Bitfield definition for register of struct array PWM: CFG1 */
/*
 * HIGHZ_EN_N (RW)
 *
 * 0 to highz pwm outputs(pad_oe*=0), software need set this bit to 1 to enable pwm output
 */
#define PWMV2_PWM_CFG1_HIGHZ_EN_N_MASK (0x10000000UL)
#define PWMV2_PWM_CFG1_HIGHZ_EN_N_SHIFT (28U)
#define PWMV2_PWM_CFG1_HIGHZ_EN_N_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG1_HIGHZ_EN_N_SHIFT) & PWMV2_PWM_CFG1_HIGHZ_EN_N_MASK)
#define PWMV2_PWM_CFG1_HIGHZ_EN_N_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG1_HIGHZ_EN_N_MASK) >> PWMV2_PWM_CFG1_HIGHZ_EN_N_SHIFT)

/*
 * FORCE_UPDATE_TIME (RW)
 *
 * define when to use the shadow register value for working register(force_mode)
 * 00:  software set work_ctrl1.shadow_lock bit
 * 01:  use the related counter rld_cmp_sel0 and rld_cmp_sel1, to select one compare point
 * 10:  related counter reload time(selected by pwm_cnt)
 * 11:  use force_trig_sel to select one of the input trigger
 * NOTE: 00/01 are not recommended since the update time is not controllable, may cause error in complex application.
 * 00 is used for initialization or debug, not suggest for real time update
 */
#define PWMV2_PWM_CFG1_FORCE_UPDATE_TIME_MASK (0xC000000UL)
#define PWMV2_PWM_CFG1_FORCE_UPDATE_TIME_SHIFT (26U)
#define PWMV2_PWM_CFG1_FORCE_UPDATE_TIME_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG1_FORCE_UPDATE_TIME_SHIFT) & PWMV2_PWM_CFG1_FORCE_UPDATE_TIME_MASK)
#define PWMV2_PWM_CFG1_FORCE_UPDATE_TIME_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG1_FORCE_UPDATE_TIME_MASK) >> PWMV2_PWM_CFG1_FORCE_UPDATE_TIME_SHIFT)

/*
 * FAULT_MODE (RW)
 *
 * 00:  force output 0
 * 01:  force output 1
 * 1x:  output highz(pad_oe_*=0)
 */
#define PWMV2_PWM_CFG1_FAULT_MODE_MASK (0x3000000UL)
#define PWMV2_PWM_CFG1_FAULT_MODE_SHIFT (24U)
#define PWMV2_PWM_CFG1_FAULT_MODE_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG1_FAULT_MODE_SHIFT) & PWMV2_PWM_CFG1_FAULT_MODE_MASK)
#define PWMV2_PWM_CFG1_FAULT_MODE_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG1_FAULT_MODE_MASK) >> PWMV2_PWM_CFG1_FAULT_MODE_SHIFT)

/*
 * FAULT_REC_TIME (RW)
 *
 * 00:  immediately
 * 01:  after main counter reload time
 * 10:  use fault_rec_sel to select one of the input trigger
 * 11:  software write fault_clear in glb_ctrl2, no effort if pwm_fault is still assert
 */
#define PWMV2_PWM_CFG1_FAULT_REC_TIME_MASK (0xC00000UL)
#define PWMV2_PWM_CFG1_FAULT_REC_TIME_SHIFT (22U)
#define PWMV2_PWM_CFG1_FAULT_REC_TIME_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG1_FAULT_REC_TIME_SHIFT) & PWMV2_PWM_CFG1_FAULT_REC_TIME_MASK)
#define PWMV2_PWM_CFG1_FAULT_REC_TIME_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG1_FAULT_REC_TIME_MASK) >> PWMV2_PWM_CFG1_FAULT_REC_TIME_SHIFT)

/*
 * SW_FORCE_EN (RW)
 *
 * 0 for hardware force, from trig_mux selected by pwm_force_sel
 * 1 for software force, from glb_ctrl.sw_force
 */
#define PWMV2_PWM_CFG1_SW_FORCE_EN_MASK (0x200000UL)
#define PWMV2_PWM_CFG1_SW_FORCE_EN_SHIFT (21U)
#define PWMV2_PWM_CFG1_SW_FORCE_EN_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG1_SW_FORCE_EN_SHIFT) & PWMV2_PWM_CFG1_SW_FORCE_EN_MASK)
#define PWMV2_PWM_CFG1_SW_FORCE_EN_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG1_SW_FORCE_EN_MASK) >> PWMV2_PWM_CFG1_SW_FORCE_EN_SHIFT)

/*
 * PAIR_MODE (RW)
 *
 * if set to 1, PWM work at pair mode,
 * pwm_cfg for channel 2m is used for channel 2m+1(m=0,1,2,3),
 * except the dead area, which is separate for each channel even in pair mode
 * software need set this bit for both channel of one pair, otherwise result unknown.
 */
#define PWMV2_PWM_CFG1_PAIR_MODE_MASK (0x100000UL)
#define PWMV2_PWM_CFG1_PAIR_MODE_SHIFT (20U)
#define PWMV2_PWM_CFG1_PAIR_MODE_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG1_PAIR_MODE_SHIFT) & PWMV2_PWM_CFG1_PAIR_MODE_MASK)
#define PWMV2_PWM_CFG1_PAIR_MODE_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG1_PAIR_MODE_MASK) >> PWMV2_PWM_CFG1_PAIR_MODE_SHIFT)

/*
 * PWM_LOGIC (RW)
 *
 * valid only for pwm0/2/4/6 when trig_sel4 is set
 * 00:  ab OR cd;
 * 01:  ab AND cd;
 * 10:  ab XOR cd;
 * 11:  cd
 */
#define PWMV2_PWM_CFG1_PWM_LOGIC_MASK (0xC0000UL)
#define PWMV2_PWM_CFG1_PWM_LOGIC_SHIFT (18U)
#define PWMV2_PWM_CFG1_PWM_LOGIC_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG1_PWM_LOGIC_SHIFT) & PWMV2_PWM_CFG1_PWM_LOGIC_MASK)
#define PWMV2_PWM_CFG1_PWM_LOGIC_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG1_PWM_LOGIC_MASK) >> PWMV2_PWM_CFG1_PWM_LOGIC_SHIFT)

/*
 * FORCE_TIME (RW)
 *
 * 00:  force immediately
 * 01:  force at main counter reload time
 * 10:  force at trig signal selected by force_act_sel
 * 11: no force
 * the force assert/deassert will happen at the force_time;
 * qeo force and value also latched at this time
 */
#define PWMV2_PWM_CFG1_FORCE_TIME_MASK (0x30000UL)
#define PWMV2_PWM_CFG1_FORCE_TIME_SHIFT (16U)
#define PWMV2_PWM_CFG1_FORCE_TIME_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG1_FORCE_TIME_SHIFT) & PWMV2_PWM_CFG1_FORCE_TIME_MASK)
#define PWMV2_PWM_CFG1_FORCE_TIME_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG1_FORCE_TIME_MASK) >> PWMV2_PWM_CFG1_FORCE_TIME_SHIFT)

/*
 * FORCE_TRIG_SEL (RW)
 *
 * select one trigger from 8, should set to pulse in trig_mux, will load shadow register(force)mode) to force_mode_work at this time
 */
#define PWMV2_PWM_CFG1_FORCE_TRIG_SEL_MASK (0x7000U)
#define PWMV2_PWM_CFG1_FORCE_TRIG_SEL_SHIFT (12U)
#define PWMV2_PWM_CFG1_FORCE_TRIG_SEL_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG1_FORCE_TRIG_SEL_SHIFT) & PWMV2_PWM_CFG1_FORCE_TRIG_SEL_MASK)
#define PWMV2_PWM_CFG1_FORCE_TRIG_SEL_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG1_FORCE_TRIG_SEL_MASK) >> PWMV2_PWM_CFG1_FORCE_TRIG_SEL_SHIFT)

/*
 * FORCE_ACT_SEL (RW)
 *
 * select one trigger from 8, should set to pulse in trig_mux, will load hw/sw force at this time
 */
#define PWMV2_PWM_CFG1_FORCE_ACT_SEL_MASK (0x700U)
#define PWMV2_PWM_CFG1_FORCE_ACT_SEL_SHIFT (8U)
#define PWMV2_PWM_CFG1_FORCE_ACT_SEL_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG1_FORCE_ACT_SEL_SHIFT) & PWMV2_PWM_CFG1_FORCE_ACT_SEL_MASK)
#define PWMV2_PWM_CFG1_FORCE_ACT_SEL_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG1_FORCE_ACT_SEL_MASK) >> PWMV2_PWM_CFG1_FORCE_ACT_SEL_SHIFT)

/*
 * PWM_FORCE_SEL (RW)
 *
 * select one trigger from 8 as force signal, should be level signal, 1 for force active, 0 for no force
 */
#define PWMV2_PWM_CFG1_PWM_FORCE_SEL_MASK (0x70U)
#define PWMV2_PWM_CFG1_PWM_FORCE_SEL_SHIFT (4U)
#define PWMV2_PWM_CFG1_PWM_FORCE_SEL_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG1_PWM_FORCE_SEL_SHIFT) & PWMV2_PWM_CFG1_PWM_FORCE_SEL_MASK)
#define PWMV2_PWM_CFG1_PWM_FORCE_SEL_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG1_PWM_FORCE_SEL_MASK) >> PWMV2_PWM_CFG1_PWM_FORCE_SEL_SHIFT)

/*
 * FAULT_REC_SEL (RW)
 *
 * select one trigger from 8, should set to pulse in trig_mux, used for fault recovery if fault_rec_time is set to 2'b10
 */
#define PWMV2_PWM_CFG1_FAULT_REC_SEL_MASK (0x7U)
#define PWMV2_PWM_CFG1_FAULT_REC_SEL_SHIFT (0U)
#define PWMV2_PWM_CFG1_FAULT_REC_SEL_SET(x) (((uint32_t)(x) << PWMV2_PWM_CFG1_FAULT_REC_SEL_SHIFT) & PWMV2_PWM_CFG1_FAULT_REC_SEL_MASK)
#define PWMV2_PWM_CFG1_FAULT_REC_SEL_GET(x) (((uint32_t)(x) & PWMV2_PWM_CFG1_FAULT_REC_SEL_MASK) >> PWMV2_PWM_CFG1_FAULT_REC_SEL_SHIFT)

/* Bitfield definition for register of struct array PWM: DEAD_AREA */
/*
 * DEAD_AREA (RW)
 *
 * 16bit cycle delay plus 8bit hr_delay
 * min value is 2 cycles, less than 0x200 will be treated as no dead area;
 * NOTE: dead insertion must be configured with pair, that is, for pwm 01/23/45/67.
 * otherwise the result maybe UNKNOWN!!!
 */
#define PWMV2_PWM_DEAD_AREA_DEAD_AREA_MASK (0xFFFFFFUL)
#define PWMV2_PWM_DEAD_AREA_DEAD_AREA_SHIFT (0U)
#define PWMV2_PWM_DEAD_AREA_DEAD_AREA_SET(x) (((uint32_t)(x) << PWMV2_PWM_DEAD_AREA_DEAD_AREA_SHIFT) & PWMV2_PWM_DEAD_AREA_DEAD_AREA_MASK)
#define PWMV2_PWM_DEAD_AREA_DEAD_AREA_GET(x) (((uint32_t)(x) & PWMV2_PWM_DEAD_AREA_DEAD_AREA_MASK) >> PWMV2_PWM_DEAD_AREA_DEAD_AREA_SHIFT)

/* Bitfield definition for register array: TRIGGER_CFG */
/*
 * TRIGGER_OUT_SEL (RW)
 *
 * select one from 24 compare result as trigger out, set at compare point, clear at reload point.
 */
#define PWMV2_TRIGGER_CFG_TRIGGER_OUT_SEL_MASK (0x1FU)
#define PWMV2_TRIGGER_CFG_TRIGGER_OUT_SEL_SHIFT (0U)
#define PWMV2_TRIGGER_CFG_TRIGGER_OUT_SEL_SET(x) (((uint32_t)(x) << PWMV2_TRIGGER_CFG_TRIGGER_OUT_SEL_SHIFT) & PWMV2_TRIGGER_CFG_TRIGGER_OUT_SEL_MASK)
#define PWMV2_TRIGGER_CFG_TRIGGER_OUT_SEL_GET(x) (((uint32_t)(x) & PWMV2_TRIGGER_CFG_TRIGGER_OUT_SEL_MASK) >> PWMV2_TRIGGER_CFG_TRIGGER_OUT_SEL_SHIFT)

/* Bitfield definition for register: GLB_CTRL */
/*
 * SW_FORCE (RW)
 *
 * software write 1 to start software force, if the pwm_cfg<n>.sw_force_en is set, force will take effort
 */
#define PWMV2_GLB_CTRL_SW_FORCE_MASK (0xFF0000UL)
#define PWMV2_GLB_CTRL_SW_FORCE_SHIFT (16U)
#define PWMV2_GLB_CTRL_SW_FORCE_SET(x) (((uint32_t)(x) << PWMV2_GLB_CTRL_SW_FORCE_SHIFT) & PWMV2_GLB_CTRL_SW_FORCE_MASK)
#define PWMV2_GLB_CTRL_SW_FORCE_GET(x) (((uint32_t)(x) & PWMV2_GLB_CTRL_SW_FORCE_MASK) >> PWMV2_GLB_CTRL_SW_FORCE_SHIFT)

/*
 * OUTPUT_DELAY (RW)
 *
 * add delay after dead_area insertiong logic, for hr_pwm
 */
#define PWMV2_GLB_CTRL_OUTPUT_DELAY_MASK (0x300U)
#define PWMV2_GLB_CTRL_OUTPUT_DELAY_SHIFT (8U)
#define PWMV2_GLB_CTRL_OUTPUT_DELAY_SET(x) (((uint32_t)(x) << PWMV2_GLB_CTRL_OUTPUT_DELAY_SHIFT) & PWMV2_GLB_CTRL_OUTPUT_DELAY_MASK)
#define PWMV2_GLB_CTRL_OUTPUT_DELAY_GET(x) (((uint32_t)(x) & PWMV2_GLB_CTRL_OUTPUT_DELAY_MASK) >> PWMV2_GLB_CTRL_OUTPUT_DELAY_SHIFT)

/*
 * HR_PWM_EN (RW)
 *
 * set to enable hr pwm, clear to bypass delay chain.
 */
#define PWMV2_GLB_CTRL_HR_PWM_EN_MASK (0x10U)
#define PWMV2_GLB_CTRL_HR_PWM_EN_SHIFT (4U)
#define PWMV2_GLB_CTRL_HR_PWM_EN_SET(x) (((uint32_t)(x) << PWMV2_GLB_CTRL_HR_PWM_EN_SHIFT) & PWMV2_GLB_CTRL_HR_PWM_EN_MASK)
#define PWMV2_GLB_CTRL_HR_PWM_EN_GET(x) (((uint32_t)(x) & PWMV2_GLB_CTRL_HR_PWM_EN_MASK) >> PWMV2_GLB_CTRL_HR_PWM_EN_SHIFT)

/*
 * FRAC_DISABLE (RW)
 *
 * set to disable bit[7:0] in DAC value when Calculation Unit use it.
 */
#define PWMV2_GLB_CTRL_FRAC_DISABLE_MASK (0x8U)
#define PWMV2_GLB_CTRL_FRAC_DISABLE_SHIFT (3U)
#define PWMV2_GLB_CTRL_FRAC_DISABLE_SET(x) (((uint32_t)(x) << PWMV2_GLB_CTRL_FRAC_DISABLE_SHIFT) & PWMV2_GLB_CTRL_FRAC_DISABLE_MASK)
#define PWMV2_GLB_CTRL_FRAC_DISABLE_GET(x) (((uint32_t)(x) & PWMV2_GLB_CTRL_FRAC_DISABLE_MASK) >> PWMV2_GLB_CTRL_FRAC_DISABLE_SHIFT)

/* Bitfield definition for register: GLB_CTRL2 */
/*
 * DAC_SW_MODE (RW)
 *
 * set for software DAC mode, software can write dac_value*_sv directly, and dac_valid from moto system is ignored
 */
#define PWMV2_GLB_CTRL2_DAC_SW_MODE_MASK (0xF000000UL)
#define PWMV2_GLB_CTRL2_DAC_SW_MODE_SHIFT (24U)
#define PWMV2_GLB_CTRL2_DAC_SW_MODE_SET(x) (((uint32_t)(x) << PWMV2_GLB_CTRL2_DAC_SW_MODE_SHIFT) & PWMV2_GLB_CTRL2_DAC_SW_MODE_MASK)
#define PWMV2_GLB_CTRL2_DAC_SW_MODE_GET(x) (((uint32_t)(x) & PWMV2_GLB_CTRL2_DAC_SW_MODE_MASK) >> PWMV2_GLB_CTRL2_DAC_SW_MODE_SHIFT)

/*
 * DEBUG_IN_EN (RW)
 *
 * set to enable debug_in signal as fault signal, generally disable pwm output
 */
#define PWMV2_GLB_CTRL2_DEBUG_IN_EN_MASK (0x200000UL)
#define PWMV2_GLB_CTRL2_DEBUG_IN_EN_SHIFT (21U)
#define PWMV2_GLB_CTRL2_DEBUG_IN_EN_SET(x) (((uint32_t)(x) << PWMV2_GLB_CTRL2_DEBUG_IN_EN_SHIFT) & PWMV2_GLB_CTRL2_DEBUG_IN_EN_MASK)
#define PWMV2_GLB_CTRL2_DEBUG_IN_EN_GET(x) (((uint32_t)(x) & PWMV2_GLB_CTRL2_DEBUG_IN_EN_MASK) >> PWMV2_GLB_CTRL2_DEBUG_IN_EN_SHIFT)

/*
 * FAULT_CLEAR (RW)
 *
 * software write 1 to clear fault event if pwm_cfg.fault_rec_time is 2'b11.
 * software need to clear it after the fault signal is de-assert and before next fault
 * one bit for one pwm channel
 */
#define PWMV2_GLB_CTRL2_FAULT_CLEAR_MASK (0xFF00U)
#define PWMV2_GLB_CTRL2_FAULT_CLEAR_SHIFT (8U)
#define PWMV2_GLB_CTRL2_FAULT_CLEAR_SET(x) (((uint32_t)(x) << PWMV2_GLB_CTRL2_FAULT_CLEAR_SHIFT) & PWMV2_GLB_CTRL2_FAULT_CLEAR_MASK)
#define PWMV2_GLB_CTRL2_FAULT_CLEAR_GET(x) (((uint32_t)(x) & PWMV2_GLB_CTRL2_FAULT_CLEAR_MASK) >> PWMV2_GLB_CTRL2_FAULT_CLEAR_SHIFT)

/*
 * SHADOW_LOCK_EN (RW)
 *
 * enable shadow_lock feature, if cleared, shadow_lock will be always 0
 */
#define PWMV2_GLB_CTRL2_SHADOW_LOCK_EN_MASK (0x1U)
#define PWMV2_GLB_CTRL2_SHADOW_LOCK_EN_SHIFT (0U)
#define PWMV2_GLB_CTRL2_SHADOW_LOCK_EN_SET(x) (((uint32_t)(x) << PWMV2_GLB_CTRL2_SHADOW_LOCK_EN_SHIFT) & PWMV2_GLB_CTRL2_SHADOW_LOCK_EN_MASK)
#define PWMV2_GLB_CTRL2_SHADOW_LOCK_EN_GET(x) (((uint32_t)(x) & PWMV2_GLB_CTRL2_SHADOW_LOCK_EN_MASK) >> PWMV2_GLB_CTRL2_SHADOW_LOCK_EN_SHIFT)

/* Bitfield definition for register array: CNT_RELOAD_WORK */
/*
 * VALUE (RO)
 *
 * counter0 reload working register
 */
#define PWMV2_CNT_RELOAD_WORK_VALUE_MASK (0xFFFFFFFFUL)
#define PWMV2_CNT_RELOAD_WORK_VALUE_SHIFT (0U)
#define PWMV2_CNT_RELOAD_WORK_VALUE_GET(x) (((uint32_t)(x) & PWMV2_CNT_RELOAD_WORK_VALUE_MASK) >> PWMV2_CNT_RELOAD_WORK_VALUE_SHIFT)

/* Bitfield definition for register array: CMP_VAL_WORK */
/*
 * VALUE (RO)
 *
 * compare point working register
 */
#define PWMV2_CMP_VAL_WORK_VALUE_MASK (0xFFFFFFFFUL)
#define PWMV2_CMP_VAL_WORK_VALUE_SHIFT (0U)
#define PWMV2_CMP_VAL_WORK_VALUE_GET(x) (((uint32_t)(x) & PWMV2_CMP_VAL_WORK_VALUE_MASK) >> PWMV2_CMP_VAL_WORK_VALUE_SHIFT)

/* Bitfield definition for register: FORCE_WORK */
/*
 * OUT_POLARITY (RO)
 *
 * force working register
 */
#define PWMV2_FORCE_WORK_OUT_POLARITY_MASK (0xFF0000UL)
#define PWMV2_FORCE_WORK_OUT_POLARITY_SHIFT (16U)
#define PWMV2_FORCE_WORK_OUT_POLARITY_GET(x) (((uint32_t)(x) & PWMV2_FORCE_WORK_OUT_POLARITY_MASK) >> PWMV2_FORCE_WORK_OUT_POLARITY_SHIFT)

/*
 * FORCE_MODE (RO)
 *
 * force_mode work register
 */
#define PWMV2_FORCE_WORK_FORCE_MODE_MASK (0xFFFFU)
#define PWMV2_FORCE_WORK_FORCE_MODE_SHIFT (0U)
#define PWMV2_FORCE_WORK_FORCE_MODE_GET(x) (((uint32_t)(x) & PWMV2_FORCE_WORK_FORCE_MODE_MASK) >> PWMV2_FORCE_WORK_FORCE_MODE_SHIFT)

/* Bitfield definition for register array: CNT_VAL */
/*
 * VALUE (RO)
 *
 * main counter value
 */
#define PWMV2_CNT_VAL_VALUE_MASK (0xFFFFFFFFUL)
#define PWMV2_CNT_VAL_VALUE_SHIFT (0U)
#define PWMV2_CNT_VAL_VALUE_GET(x) (((uint32_t)(x) & PWMV2_CNT_VAL_VALUE_MASK) >> PWMV2_CNT_VAL_VALUE_SHIFT)

/* Bitfield definition for register array: DAC_VALUE_SV */
/*
 * VALUE (RW)
 *
 * save dac0_value when dac0_valid if dac_sw_mode is 0;
 * software write dac_value directly if dac_sw_mode is 1
 */
#define PWMV2_DAC_VALUE_SV_VALUE_MASK (0xFFFFFFFFUL)
#define PWMV2_DAC_VALUE_SV_VALUE_SHIFT (0U)
#define PWMV2_DAC_VALUE_SV_VALUE_SET(x) (((uint32_t)(x) << PWMV2_DAC_VALUE_SV_VALUE_SHIFT) & PWMV2_DAC_VALUE_SV_VALUE_MASK)
#define PWMV2_DAC_VALUE_SV_VALUE_GET(x) (((uint32_t)(x) & PWMV2_DAC_VALUE_SV_VALUE_MASK) >> PWMV2_DAC_VALUE_SV_VALUE_SHIFT)

/* Bitfield definition for register array: CAPTURE_POS */
/*
 * CAPTURE_POS (RO)
 *
 * related counter value captured at input negedge
 */
#define PWMV2_CAPTURE_POS_CAPTURE_POS_MASK (0xFFFFFF00UL)
#define PWMV2_CAPTURE_POS_CAPTURE_POS_SHIFT (8U)
#define PWMV2_CAPTURE_POS_CAPTURE_POS_GET(x) (((uint32_t)(x) & PWMV2_CAPTURE_POS_CAPTURE_POS_MASK) >> PWMV2_CAPTURE_POS_CAPTURE_POS_SHIFT)

/*
 * CAPTURE_SELGPIO (RW)
 *
 * 0: result from CAP[  7:0],  from trgm
 * 1: result from CAP[15:8],  from gpio
 */
#define PWMV2_CAPTURE_POS_CAPTURE_SELGPIO_MASK (0x10U)
#define PWMV2_CAPTURE_POS_CAPTURE_SELGPIO_SHIFT (4U)
#define PWMV2_CAPTURE_POS_CAPTURE_SELGPIO_SET(x) (((uint32_t)(x) << PWMV2_CAPTURE_POS_CAPTURE_SELGPIO_SHIFT) & PWMV2_CAPTURE_POS_CAPTURE_SELGPIO_MASK)
#define PWMV2_CAPTURE_POS_CAPTURE_SELGPIO_GET(x) (((uint32_t)(x) & PWMV2_CAPTURE_POS_CAPTURE_SELGPIO_MASK) >> PWMV2_CAPTURE_POS_CAPTURE_SELGPIO_SHIFT)

/*
 * CNT_INDEX (RW)
 *
 * related counter
 */
#define PWMV2_CAPTURE_POS_CNT_INDEX_MASK (0x3U)
#define PWMV2_CAPTURE_POS_CNT_INDEX_SHIFT (0U)
#define PWMV2_CAPTURE_POS_CNT_INDEX_SET(x) (((uint32_t)(x) << PWMV2_CAPTURE_POS_CNT_INDEX_SHIFT) & PWMV2_CAPTURE_POS_CNT_INDEX_MASK)
#define PWMV2_CAPTURE_POS_CNT_INDEX_GET(x) (((uint32_t)(x) & PWMV2_CAPTURE_POS_CNT_INDEX_MASK) >> PWMV2_CAPTURE_POS_CNT_INDEX_SHIFT)

/* Bitfield definition for register array: CAPTURE_NEG */
/*
 * CAPTURE_NEG (RO)
 *
 * counter value captured at input negedge
 */
#define PWMV2_CAPTURE_NEG_CAPTURE_NEG_MASK (0xFFFFFF00UL)
#define PWMV2_CAPTURE_NEG_CAPTURE_NEG_SHIFT (8U)
#define PWMV2_CAPTURE_NEG_CAPTURE_NEG_GET(x) (((uint32_t)(x) & PWMV2_CAPTURE_NEG_CAPTURE_NEG_MASK) >> PWMV2_CAPTURE_NEG_CAPTURE_NEG_SHIFT)

/* Bitfield definition for register: IRQ_STS */
/*
 * IRQ_CAL_OVERFLOW (W1C)
 *
 * end of output burst
 */
#define PWMV2_IRQ_STS_IRQ_CAL_OVERFLOW_MASK (0x80000000UL)
#define PWMV2_IRQ_STS_IRQ_CAL_OVERFLOW_SHIFT (31U)
#define PWMV2_IRQ_STS_IRQ_CAL_OVERFLOW_SET(x) (((uint32_t)(x) << PWMV2_IRQ_STS_IRQ_CAL_OVERFLOW_SHIFT) & PWMV2_IRQ_STS_IRQ_CAL_OVERFLOW_MASK)
#define PWMV2_IRQ_STS_IRQ_CAL_OVERFLOW_GET(x) (((uint32_t)(x) & PWMV2_IRQ_STS_IRQ_CAL_OVERFLOW_MASK) >> PWMV2_IRQ_STS_IRQ_CAL_OVERFLOW_SHIFT)

/*
 * IRQ_BURSTEND (RO)
 *
 * end of output burst
 */
#define PWMV2_IRQ_STS_IRQ_BURSTEND_MASK (0x20U)
#define PWMV2_IRQ_STS_IRQ_BURSTEND_SHIFT (5U)
#define PWMV2_IRQ_STS_IRQ_BURSTEND_GET(x) (((uint32_t)(x) & PWMV2_IRQ_STS_IRQ_BURSTEND_MASK) >> PWMV2_IRQ_STS_IRQ_BURSTEND_SHIFT)

/*
 * IRQ_FAULT (RO)
 *
 * for external fault event
 */
#define PWMV2_IRQ_STS_IRQ_FAULT_MASK (0x10U)
#define PWMV2_IRQ_STS_IRQ_FAULT_SHIFT (4U)
#define PWMV2_IRQ_STS_IRQ_FAULT_GET(x) (((uint32_t)(x) & PWMV2_IRQ_STS_IRQ_FAULT_MASK) >> PWMV2_IRQ_STS_IRQ_FAULT_SHIFT)

/*
 * IRQ_CAPTURE_NEG (RO)
 *
 * capture negedge status
 */
#define PWMV2_IRQ_STS_IRQ_CAPTURE_NEG_MASK (0x8U)
#define PWMV2_IRQ_STS_IRQ_CAPTURE_NEG_SHIFT (3U)
#define PWMV2_IRQ_STS_IRQ_CAPTURE_NEG_GET(x) (((uint32_t)(x) & PWMV2_IRQ_STS_IRQ_CAPTURE_NEG_MASK) >> PWMV2_IRQ_STS_IRQ_CAPTURE_NEG_SHIFT)

/*
 * IRQ_CAPTURE_POS (RO)
 *
 * capture posedge status
 */
#define PWMV2_IRQ_STS_IRQ_CAPTURE_POS_MASK (0x4U)
#define PWMV2_IRQ_STS_IRQ_CAPTURE_POS_SHIFT (2U)
#define PWMV2_IRQ_STS_IRQ_CAPTURE_POS_GET(x) (((uint32_t)(x) & PWMV2_IRQ_STS_IRQ_CAPTURE_POS_MASK) >> PWMV2_IRQ_STS_IRQ_CAPTURE_POS_SHIFT)

/*
 * IRQ_RELOAD (RO)
 *
 * when clock counter reach the reload time
 */
#define PWMV2_IRQ_STS_IRQ_RELOAD_MASK (0x2U)
#define PWMV2_IRQ_STS_IRQ_RELOAD_SHIFT (1U)
#define PWMV2_IRQ_STS_IRQ_RELOAD_GET(x) (((uint32_t)(x) & PWMV2_IRQ_STS_IRQ_RELOAD_MASK) >> PWMV2_IRQ_STS_IRQ_RELOAD_SHIFT)

/*
 * IRQ_CMP (RO)
 *
 * for 24 channel, compare event
 */
#define PWMV2_IRQ_STS_IRQ_CMP_MASK (0x1U)
#define PWMV2_IRQ_STS_IRQ_CMP_SHIFT (0U)
#define PWMV2_IRQ_STS_IRQ_CMP_GET(x) (((uint32_t)(x) & PWMV2_IRQ_STS_IRQ_CMP_MASK) >> PWMV2_IRQ_STS_IRQ_CMP_SHIFT)

/* Bitfield definition for register: IRQ_EN */
/*
 * IRQ_EN_OVERFLOW (RW)
 *
 * enable interrupt when calculation unit overflow
 */
#define PWMV2_IRQ_EN_IRQ_EN_OVERFLOW_MASK (0x80000000UL)
#define PWMV2_IRQ_EN_IRQ_EN_OVERFLOW_SHIFT (31U)
#define PWMV2_IRQ_EN_IRQ_EN_OVERFLOW_SET(x) (((uint32_t)(x) << PWMV2_IRQ_EN_IRQ_EN_OVERFLOW_SHIFT) & PWMV2_IRQ_EN_IRQ_EN_OVERFLOW_MASK)
#define PWMV2_IRQ_EN_IRQ_EN_OVERFLOW_GET(x) (((uint32_t)(x) & PWMV2_IRQ_EN_IRQ_EN_OVERFLOW_MASK) >> PWMV2_IRQ_EN_IRQ_EN_OVERFLOW_SHIFT)

/* Bitfield definition for register: IRQ_STS_CMP */
/*
 * IRQ_STS_CMP (W1C)
 *
 * interrupt flag for compare point match event, and each bit means one compare point.
 */
#define PWMV2_IRQ_STS_CMP_IRQ_STS_CMP_MASK (0xFFFFFFUL)
#define PWMV2_IRQ_STS_CMP_IRQ_STS_CMP_SHIFT (0U)
#define PWMV2_IRQ_STS_CMP_IRQ_STS_CMP_SET(x) (((uint32_t)(x) << PWMV2_IRQ_STS_CMP_IRQ_STS_CMP_SHIFT) & PWMV2_IRQ_STS_CMP_IRQ_STS_CMP_MASK)
#define PWMV2_IRQ_STS_CMP_IRQ_STS_CMP_GET(x) (((uint32_t)(x) & PWMV2_IRQ_STS_CMP_IRQ_STS_CMP_MASK) >> PWMV2_IRQ_STS_CMP_IRQ_STS_CMP_SHIFT)

/* Bitfield definition for register: IRQ_STS_RELOAD */
/*
 * IRQ_STS_RELOAD (W1C)
 *
 * interrupt flag for reload event , and each bit means one main counter.
 */
#define PWMV2_IRQ_STS_RELOAD_IRQ_STS_RELOAD_MASK (0xFU)
#define PWMV2_IRQ_STS_RELOAD_IRQ_STS_RELOAD_SHIFT (0U)
#define PWMV2_IRQ_STS_RELOAD_IRQ_STS_RELOAD_SET(x) (((uint32_t)(x) << PWMV2_IRQ_STS_RELOAD_IRQ_STS_RELOAD_SHIFT) & PWMV2_IRQ_STS_RELOAD_IRQ_STS_RELOAD_MASK)
#define PWMV2_IRQ_STS_RELOAD_IRQ_STS_RELOAD_GET(x) (((uint32_t)(x) & PWMV2_IRQ_STS_RELOAD_IRQ_STS_RELOAD_MASK) >> PWMV2_IRQ_STS_RELOAD_IRQ_STS_RELOAD_SHIFT)

/* Bitfield definition for register: IRQ_STS_CAP_POS */
/*
 * IRQ_STS_CAP_POS (W1C)
 *
 * interrupt flag for posedge capture event , and each bit means one capture channel.
 */
#define PWMV2_IRQ_STS_CAP_POS_IRQ_STS_CAP_POS_MASK (0xFFU)
#define PWMV2_IRQ_STS_CAP_POS_IRQ_STS_CAP_POS_SHIFT (0U)
#define PWMV2_IRQ_STS_CAP_POS_IRQ_STS_CAP_POS_SET(x) (((uint32_t)(x) << PWMV2_IRQ_STS_CAP_POS_IRQ_STS_CAP_POS_SHIFT) & PWMV2_IRQ_STS_CAP_POS_IRQ_STS_CAP_POS_MASK)
#define PWMV2_IRQ_STS_CAP_POS_IRQ_STS_CAP_POS_GET(x) (((uint32_t)(x) & PWMV2_IRQ_STS_CAP_POS_IRQ_STS_CAP_POS_MASK) >> PWMV2_IRQ_STS_CAP_POS_IRQ_STS_CAP_POS_SHIFT)

/* Bitfield definition for register: IRQ_STS_CAP_NEG */
/*
 * IRQ_STS_CAP_NEG (W1C)
 *
 * interrupt flag for negedge capture event , and each bit means one capture channel.
 */
#define PWMV2_IRQ_STS_CAP_NEG_IRQ_STS_CAP_NEG_MASK (0xFFU)
#define PWMV2_IRQ_STS_CAP_NEG_IRQ_STS_CAP_NEG_SHIFT (0U)
#define PWMV2_IRQ_STS_CAP_NEG_IRQ_STS_CAP_NEG_SET(x) (((uint32_t)(x) << PWMV2_IRQ_STS_CAP_NEG_IRQ_STS_CAP_NEG_SHIFT) & PWMV2_IRQ_STS_CAP_NEG_IRQ_STS_CAP_NEG_MASK)
#define PWMV2_IRQ_STS_CAP_NEG_IRQ_STS_CAP_NEG_GET(x) (((uint32_t)(x) & PWMV2_IRQ_STS_CAP_NEG_IRQ_STS_CAP_NEG_MASK) >> PWMV2_IRQ_STS_CAP_NEG_IRQ_STS_CAP_NEG_SHIFT)

/* Bitfield definition for register: IRQ_STS_FAULT */
/*
 * IRQ_STS_FAULT (W1C)
 *
 * interrupt flag for external fault event , and each bit means one external fault channel.
 */
#define PWMV2_IRQ_STS_FAULT_IRQ_STS_FAULT_MASK (0xFFU)
#define PWMV2_IRQ_STS_FAULT_IRQ_STS_FAULT_SHIFT (0U)
#define PWMV2_IRQ_STS_FAULT_IRQ_STS_FAULT_SET(x) (((uint32_t)(x) << PWMV2_IRQ_STS_FAULT_IRQ_STS_FAULT_SHIFT) & PWMV2_IRQ_STS_FAULT_IRQ_STS_FAULT_MASK)
#define PWMV2_IRQ_STS_FAULT_IRQ_STS_FAULT_GET(x) (((uint32_t)(x) & PWMV2_IRQ_STS_FAULT_IRQ_STS_FAULT_MASK) >> PWMV2_IRQ_STS_FAULT_IRQ_STS_FAULT_SHIFT)

/* Bitfield definition for register: IRQ_STS_BURSTEND */
/*
 * IRQ_STS_BURSTEND (W1C)
 *
 * interrupt flag for output burst done event , and each bit means one main counter.
 */
#define PWMV2_IRQ_STS_BURSTEND_IRQ_STS_BURSTEND_MASK (0xFU)
#define PWMV2_IRQ_STS_BURSTEND_IRQ_STS_BURSTEND_SHIFT (0U)
#define PWMV2_IRQ_STS_BURSTEND_IRQ_STS_BURSTEND_SET(x) (((uint32_t)(x) << PWMV2_IRQ_STS_BURSTEND_IRQ_STS_BURSTEND_SHIFT) & PWMV2_IRQ_STS_BURSTEND_IRQ_STS_BURSTEND_MASK)
#define PWMV2_IRQ_STS_BURSTEND_IRQ_STS_BURSTEND_GET(x) (((uint32_t)(x) & PWMV2_IRQ_STS_BURSTEND_IRQ_STS_BURSTEND_MASK) >> PWMV2_IRQ_STS_BURSTEND_IRQ_STS_BURSTEND_SHIFT)

/* Bitfield definition for register: IRQ_EN_CMP */
/*
 * IRQ_EN_CMP (RW)
 *
 * interrupt enable field for compare point match event, and each bit means one compare point.
 */
#define PWMV2_IRQ_EN_CMP_IRQ_EN_CMP_MASK (0xFFFFFFUL)
#define PWMV2_IRQ_EN_CMP_IRQ_EN_CMP_SHIFT (0U)
#define PWMV2_IRQ_EN_CMP_IRQ_EN_CMP_SET(x) (((uint32_t)(x) << PWMV2_IRQ_EN_CMP_IRQ_EN_CMP_SHIFT) & PWMV2_IRQ_EN_CMP_IRQ_EN_CMP_MASK)
#define PWMV2_IRQ_EN_CMP_IRQ_EN_CMP_GET(x) (((uint32_t)(x) & PWMV2_IRQ_EN_CMP_IRQ_EN_CMP_MASK) >> PWMV2_IRQ_EN_CMP_IRQ_EN_CMP_SHIFT)

/* Bitfield definition for register: IRQ_EN_RELOAD */
/*
 * IRQ_EN_RELOAD (RW)
 *
 * interrupt enable field for reload event , and each bit means one main counter.
 */
#define PWMV2_IRQ_EN_RELOAD_IRQ_EN_RELOAD_MASK (0xFU)
#define PWMV2_IRQ_EN_RELOAD_IRQ_EN_RELOAD_SHIFT (0U)
#define PWMV2_IRQ_EN_RELOAD_IRQ_EN_RELOAD_SET(x) (((uint32_t)(x) << PWMV2_IRQ_EN_RELOAD_IRQ_EN_RELOAD_SHIFT) & PWMV2_IRQ_EN_RELOAD_IRQ_EN_RELOAD_MASK)
#define PWMV2_IRQ_EN_RELOAD_IRQ_EN_RELOAD_GET(x) (((uint32_t)(x) & PWMV2_IRQ_EN_RELOAD_IRQ_EN_RELOAD_MASK) >> PWMV2_IRQ_EN_RELOAD_IRQ_EN_RELOAD_SHIFT)

/* Bitfield definition for register: IRQ_EN_CAP_POS */
/*
 * IRQ_EN_CAP_POS (RW)
 *
 * interrupt enable field for posedge capture event , and each bit means one capture channel.
 */
#define PWMV2_IRQ_EN_CAP_POS_IRQ_EN_CAP_POS_MASK (0xFFU)
#define PWMV2_IRQ_EN_CAP_POS_IRQ_EN_CAP_POS_SHIFT (0U)
#define PWMV2_IRQ_EN_CAP_POS_IRQ_EN_CAP_POS_SET(x) (((uint32_t)(x) << PWMV2_IRQ_EN_CAP_POS_IRQ_EN_CAP_POS_SHIFT) & PWMV2_IRQ_EN_CAP_POS_IRQ_EN_CAP_POS_MASK)
#define PWMV2_IRQ_EN_CAP_POS_IRQ_EN_CAP_POS_GET(x) (((uint32_t)(x) & PWMV2_IRQ_EN_CAP_POS_IRQ_EN_CAP_POS_MASK) >> PWMV2_IRQ_EN_CAP_POS_IRQ_EN_CAP_POS_SHIFT)

/* Bitfield definition for register: IRQ_EN_CAP_NEG */
/*
 * IRQ_EN_CAP_NEG (RW)
 *
 * interrupt enable field for negedge capture event , and each bit means one capture channel.
 */
#define PWMV2_IRQ_EN_CAP_NEG_IRQ_EN_CAP_NEG_MASK (0xFFU)
#define PWMV2_IRQ_EN_CAP_NEG_IRQ_EN_CAP_NEG_SHIFT (0U)
#define PWMV2_IRQ_EN_CAP_NEG_IRQ_EN_CAP_NEG_SET(x) (((uint32_t)(x) << PWMV2_IRQ_EN_CAP_NEG_IRQ_EN_CAP_NEG_SHIFT) & PWMV2_IRQ_EN_CAP_NEG_IRQ_EN_CAP_NEG_MASK)
#define PWMV2_IRQ_EN_CAP_NEG_IRQ_EN_CAP_NEG_GET(x) (((uint32_t)(x) & PWMV2_IRQ_EN_CAP_NEG_IRQ_EN_CAP_NEG_MASK) >> PWMV2_IRQ_EN_CAP_NEG_IRQ_EN_CAP_NEG_SHIFT)

/* Bitfield definition for register: IRQ_EN_FAULT */
/*
 * IRQ_EN_FAULT (RW)
 *
 * interrupt enable field for external fault event , and each bit means one external fault channel.
 */
#define PWMV2_IRQ_EN_FAULT_IRQ_EN_FAULT_MASK (0xFFU)
#define PWMV2_IRQ_EN_FAULT_IRQ_EN_FAULT_SHIFT (0U)
#define PWMV2_IRQ_EN_FAULT_IRQ_EN_FAULT_SET(x) (((uint32_t)(x) << PWMV2_IRQ_EN_FAULT_IRQ_EN_FAULT_SHIFT) & PWMV2_IRQ_EN_FAULT_IRQ_EN_FAULT_MASK)
#define PWMV2_IRQ_EN_FAULT_IRQ_EN_FAULT_GET(x) (((uint32_t)(x) & PWMV2_IRQ_EN_FAULT_IRQ_EN_FAULT_MASK) >> PWMV2_IRQ_EN_FAULT_IRQ_EN_FAULT_SHIFT)

/* Bitfield definition for register: IRQ_EN_BURSTEND */
/*
 * IRQ_EN_BURSTEND (RW)
 *
 * interrupt enable field for output burst done event , and each bit means one main counter.
 */
#define PWMV2_IRQ_EN_BURSTEND_IRQ_EN_BURSTEND_MASK (0xFU)
#define PWMV2_IRQ_EN_BURSTEND_IRQ_EN_BURSTEND_SHIFT (0U)
#define PWMV2_IRQ_EN_BURSTEND_IRQ_EN_BURSTEND_SET(x) (((uint32_t)(x) << PWMV2_IRQ_EN_BURSTEND_IRQ_EN_BURSTEND_SHIFT) & PWMV2_IRQ_EN_BURSTEND_IRQ_EN_BURSTEND_MASK)
#define PWMV2_IRQ_EN_BURSTEND_IRQ_EN_BURSTEND_GET(x) (((uint32_t)(x) & PWMV2_IRQ_EN_BURSTEND_IRQ_EN_BURSTEND_MASK) >> PWMV2_IRQ_EN_BURSTEND_IRQ_EN_BURSTEND_SHIFT)

/* Bitfield definition for register: DMA_EN */
/*
 * DMA3_EN (RW)
 *
 * enable dma3
 */
#define PWMV2_DMA_EN_DMA3_EN_MASK (0x80000000UL)
#define PWMV2_DMA_EN_DMA3_EN_SHIFT (31U)
#define PWMV2_DMA_EN_DMA3_EN_SET(x) (((uint32_t)(x) << PWMV2_DMA_EN_DMA3_EN_SHIFT) & PWMV2_DMA_EN_DMA3_EN_MASK)
#define PWMV2_DMA_EN_DMA3_EN_GET(x) (((uint32_t)(x) & PWMV2_DMA_EN_DMA3_EN_MASK) >> PWMV2_DMA_EN_DMA3_EN_SHIFT)

/*
 * DMA3_SEL (RW)
 *
 * selelct one of compare point(0~23) or one reload point(24~27) as dma0
 */
#define PWMV2_DMA_EN_DMA3_SEL_MASK (0x1F000000UL)
#define PWMV2_DMA_EN_DMA3_SEL_SHIFT (24U)
#define PWMV2_DMA_EN_DMA3_SEL_SET(x) (((uint32_t)(x) << PWMV2_DMA_EN_DMA3_SEL_SHIFT) & PWMV2_DMA_EN_DMA3_SEL_MASK)
#define PWMV2_DMA_EN_DMA3_SEL_GET(x) (((uint32_t)(x) & PWMV2_DMA_EN_DMA3_SEL_MASK) >> PWMV2_DMA_EN_DMA3_SEL_SHIFT)

/*
 * DMA2_EN (RW)
 *
 * enable dma2
 */
#define PWMV2_DMA_EN_DMA2_EN_MASK (0x800000UL)
#define PWMV2_DMA_EN_DMA2_EN_SHIFT (23U)
#define PWMV2_DMA_EN_DMA2_EN_SET(x) (((uint32_t)(x) << PWMV2_DMA_EN_DMA2_EN_SHIFT) & PWMV2_DMA_EN_DMA2_EN_MASK)
#define PWMV2_DMA_EN_DMA2_EN_GET(x) (((uint32_t)(x) & PWMV2_DMA_EN_DMA2_EN_MASK) >> PWMV2_DMA_EN_DMA2_EN_SHIFT)

/*
 * DMA2_SEL (RW)
 *
 * selelct one of compare point(0~23) or one reload point(24~27) as dma0
 */
#define PWMV2_DMA_EN_DMA2_SEL_MASK (0x1F0000UL)
#define PWMV2_DMA_EN_DMA2_SEL_SHIFT (16U)
#define PWMV2_DMA_EN_DMA2_SEL_SET(x) (((uint32_t)(x) << PWMV2_DMA_EN_DMA2_SEL_SHIFT) & PWMV2_DMA_EN_DMA2_SEL_MASK)
#define PWMV2_DMA_EN_DMA2_SEL_GET(x) (((uint32_t)(x) & PWMV2_DMA_EN_DMA2_SEL_MASK) >> PWMV2_DMA_EN_DMA2_SEL_SHIFT)

/*
 * DMA1_EN (RW)
 *
 * enable dma1
 */
#define PWMV2_DMA_EN_DMA1_EN_MASK (0x8000U)
#define PWMV2_DMA_EN_DMA1_EN_SHIFT (15U)
#define PWMV2_DMA_EN_DMA1_EN_SET(x) (((uint32_t)(x) << PWMV2_DMA_EN_DMA1_EN_SHIFT) & PWMV2_DMA_EN_DMA1_EN_MASK)
#define PWMV2_DMA_EN_DMA1_EN_GET(x) (((uint32_t)(x) & PWMV2_DMA_EN_DMA1_EN_MASK) >> PWMV2_DMA_EN_DMA1_EN_SHIFT)

/*
 * DMA1_SEL (RW)
 *
 * selelct one of compare point(0~23) or one reload point(24~27) as dma0
 */
#define PWMV2_DMA_EN_DMA1_SEL_MASK (0x1F00U)
#define PWMV2_DMA_EN_DMA1_SEL_SHIFT (8U)
#define PWMV2_DMA_EN_DMA1_SEL_SET(x) (((uint32_t)(x) << PWMV2_DMA_EN_DMA1_SEL_SHIFT) & PWMV2_DMA_EN_DMA1_SEL_MASK)
#define PWMV2_DMA_EN_DMA1_SEL_GET(x) (((uint32_t)(x) & PWMV2_DMA_EN_DMA1_SEL_MASK) >> PWMV2_DMA_EN_DMA1_SEL_SHIFT)

/*
 * DMA0_EN (RW)
 *
 * enable dma0
 */
#define PWMV2_DMA_EN_DMA0_EN_MASK (0x80U)
#define PWMV2_DMA_EN_DMA0_EN_SHIFT (7U)
#define PWMV2_DMA_EN_DMA0_EN_SET(x) (((uint32_t)(x) << PWMV2_DMA_EN_DMA0_EN_SHIFT) & PWMV2_DMA_EN_DMA0_EN_MASK)
#define PWMV2_DMA_EN_DMA0_EN_GET(x) (((uint32_t)(x) & PWMV2_DMA_EN_DMA0_EN_MASK) >> PWMV2_DMA_EN_DMA0_EN_SHIFT)

/*
 * DMA0_SEL (RW)
 *
 * selelct one of compare point(0~23) or one reload point(24~27) as dma0
 */
#define PWMV2_DMA_EN_DMA0_SEL_MASK (0x1FU)
#define PWMV2_DMA_EN_DMA0_SEL_SHIFT (0U)
#define PWMV2_DMA_EN_DMA0_SEL_SET(x) (((uint32_t)(x) << PWMV2_DMA_EN_DMA0_SEL_SHIFT) & PWMV2_DMA_EN_DMA0_SEL_MASK)
#define PWMV2_DMA_EN_DMA0_SEL_GET(x) (((uint32_t)(x) & PWMV2_DMA_EN_DMA0_SEL_MASK) >> PWMV2_DMA_EN_DMA0_SEL_SHIFT)

/* Bitfield definition for register of struct array CNT: CFG0 */
/*
 * RLD_CMP_SEL1 (RW)
 *
 * select one compare point from 24, set to 0x1F to disable current selection, used for reload value, compare value, force value update
 */
#define PWMV2_CNT_CFG0_RLD_CMP_SEL1_MASK (0x1F000000UL)
#define PWMV2_CNT_CFG0_RLD_CMP_SEL1_SHIFT (24U)
#define PWMV2_CNT_CFG0_RLD_CMP_SEL1_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG0_RLD_CMP_SEL1_SHIFT) & PWMV2_CNT_CFG0_RLD_CMP_SEL1_MASK)
#define PWMV2_CNT_CFG0_RLD_CMP_SEL1_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG0_RLD_CMP_SEL1_MASK) >> PWMV2_CNT_CFG0_RLD_CMP_SEL1_SHIFT)

/*
 * RLD_CMP_SEL0 (RW)
 *
 * select one compare point from 24, set to 0x1F to disable current selection
 */
#define PWMV2_CNT_CFG0_RLD_CMP_SEL0_MASK (0x1F0000UL)
#define PWMV2_CNT_CFG0_RLD_CMP_SEL0_SHIFT (16U)
#define PWMV2_CNT_CFG0_RLD_CMP_SEL0_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG0_RLD_CMP_SEL0_SHIFT) & PWMV2_CNT_CFG0_RLD_CMP_SEL0_MASK)
#define PWMV2_CNT_CFG0_RLD_CMP_SEL0_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG0_RLD_CMP_SEL0_MASK) >> PWMV2_CNT_CFG0_RLD_CMP_SEL0_SHIFT)

/*
 * RLD_TRIG_SEL (RW)
 *
 * select one trigger from 8, should set to pulse in trig_mux
 */
#define PWMV2_CNT_CFG0_RLD_TRIG_SEL_MASK (0x7000U)
#define PWMV2_CNT_CFG0_RLD_TRIG_SEL_SHIFT (12U)
#define PWMV2_CNT_CFG0_RLD_TRIG_SEL_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG0_RLD_TRIG_SEL_SHIFT) & PWMV2_CNT_CFG0_RLD_TRIG_SEL_MASK)
#define PWMV2_CNT_CFG0_RLD_TRIG_SEL_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG0_RLD_TRIG_SEL_MASK) >> PWMV2_CNT_CFG0_RLD_TRIG_SEL_SHIFT)

/*
 * RLD_UPDATE_TIME (RW)
 *
 * define when to use the calculation output value as reload time
 * 00:  software set work_ctrl1.shadow_lock bit
 * 01:  use compare point selected by rld_cmp_sel0 or rld_cmp_sel1
 * 10:  counter reload time
 * 11:  use rld_trig_sel to select one of the input trigger
 * NOTE: 00 is not recommended since the update time is not controllable, may cause error in complex application.
 */
#define PWMV2_CNT_CFG0_RLD_UPDATE_TIME_MASK (0x300U)
#define PWMV2_CNT_CFG0_RLD_UPDATE_TIME_SHIFT (8U)
#define PWMV2_CNT_CFG0_RLD_UPDATE_TIME_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG0_RLD_UPDATE_TIME_SHIFT) & PWMV2_CNT_CFG0_RLD_UPDATE_TIME_MASK)
#define PWMV2_CNT_CFG0_RLD_UPDATE_TIME_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG0_RLD_UPDATE_TIME_MASK) >> PWMV2_CNT_CFG0_RLD_UPDATE_TIME_SHIFT)

/*
 * CNT_D_PARAM (RW)
 *
 * input dac data parameter
 */
#define PWMV2_CNT_CFG0_CNT_D_PARAM_MASK (0x1FU)
#define PWMV2_CNT_CFG0_CNT_D_PARAM_SHIFT (0U)
#define PWMV2_CNT_CFG0_CNT_D_PARAM_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG0_CNT_D_PARAM_SHIFT) & PWMV2_CNT_CFG0_CNT_D_PARAM_MASK)
#define PWMV2_CNT_CFG0_CNT_D_PARAM_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG0_CNT_D_PARAM_MASK) >> PWMV2_CNT_CFG0_CNT_D_PARAM_SHIFT)

/* Bitfield definition for register of struct array CNT: CFG1 */
/*
 * CNT_DAC_INDEX (RW)
 *
 * select one of the dac value
 */
#define PWMV2_CNT_CFG1_CNT_DAC_INDEX_MASK (0x3000000UL)
#define PWMV2_CNT_CFG1_CNT_DAC_INDEX_SHIFT (24U)
#define PWMV2_CNT_CFG1_CNT_DAC_INDEX_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG1_CNT_DAC_INDEX_SHIFT) & PWMV2_CNT_CFG1_CNT_DAC_INDEX_MASK)
#define PWMV2_CNT_CFG1_CNT_DAC_INDEX_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG1_CNT_DAC_INDEX_MASK) >> PWMV2_CNT_CFG1_CNT_DAC_INDEX_SHIFT)

/*
 * CNT_LU_EN (RW)
 *
 * set to enable up limit, use cnt_lu_off to select one of the shadow register value as limitation
 */
#define PWMV2_CNT_CFG1_CNT_LU_EN_MASK (0x800000UL)
#define PWMV2_CNT_CFG1_CNT_LU_EN_SHIFT (23U)
#define PWMV2_CNT_CFG1_CNT_LU_EN_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG1_CNT_LU_EN_SHIFT) & PWMV2_CNT_CFG1_CNT_LU_EN_MASK)
#define PWMV2_CNT_CFG1_CNT_LU_EN_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG1_CNT_LU_EN_MASK) >> PWMV2_CNT_CFG1_CNT_LU_EN_SHIFT)

/*
 * CNT_LIM_UP (RW)
 *
 * up limit offset selection, from one of the shadow_val
 */
#define PWMV2_CNT_CFG1_CNT_LIM_UP_MASK (0x1F0000UL)
#define PWMV2_CNT_CFG1_CNT_LIM_UP_SHIFT (16U)
#define PWMV2_CNT_CFG1_CNT_LIM_UP_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG1_CNT_LIM_UP_SHIFT) & PWMV2_CNT_CFG1_CNT_LIM_UP_MASK)
#define PWMV2_CNT_CFG1_CNT_LIM_UP_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG1_CNT_LIM_UP_MASK) >> PWMV2_CNT_CFG1_CNT_LIM_UP_SHIFT)

/*
 * CNT_LL_EN (RW)
 *
 * set to enable low limit
 */
#define PWMV2_CNT_CFG1_CNT_LL_EN_MASK (0x8000U)
#define PWMV2_CNT_CFG1_CNT_LL_EN_SHIFT (15U)
#define PWMV2_CNT_CFG1_CNT_LL_EN_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG1_CNT_LL_EN_SHIFT) & PWMV2_CNT_CFG1_CNT_LL_EN_MASK)
#define PWMV2_CNT_CFG1_CNT_LL_EN_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG1_CNT_LL_EN_MASK) >> PWMV2_CNT_CFG1_CNT_LL_EN_SHIFT)

/*
 * CNT_LIM_LO (RW)
 *
 * low limit offset selection, from one of the shadow_val
 */
#define PWMV2_CNT_CFG1_CNT_LIM_LO_MASK (0x1F00U)
#define PWMV2_CNT_CFG1_CNT_LIM_LO_SHIFT (8U)
#define PWMV2_CNT_CFG1_CNT_LIM_LO_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG1_CNT_LIM_LO_SHIFT) & PWMV2_CNT_CFG1_CNT_LIM_LO_MASK)
#define PWMV2_CNT_CFG1_CNT_LIM_LO_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG1_CNT_LIM_LO_MASK) >> PWMV2_CNT_CFG1_CNT_LIM_LO_SHIFT)

/*
 * CNT_IN_OFF (RW)
 *
 * input data offset selection, from one of the shadow_val, default just shadow reload time
 */
#define PWMV2_CNT_CFG1_CNT_IN_OFF_MASK (0x1FU)
#define PWMV2_CNT_CFG1_CNT_IN_OFF_SHIFT (0U)
#define PWMV2_CNT_CFG1_CNT_IN_OFF_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG1_CNT_IN_OFF_SHIFT) & PWMV2_CNT_CFG1_CNT_IN_OFF_MASK)
#define PWMV2_CNT_CFG1_CNT_IN_OFF_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG1_CNT_IN_OFF_MASK) >> PWMV2_CNT_CFG1_CNT_IN_OFF_SHIFT)

/* Bitfield definition for register of struct array CNT: CFG2 */
/*
 * CNT_RELOAD_EN (RW)
 *
 * set to use input signal(selected by cnt_reload_trig) to reload timer
 */
#define PWMV2_CNT_CFG2_CNT_RELOAD_EN_MASK (0x80000000UL)
#define PWMV2_CNT_CFG2_CNT_RELOAD_EN_SHIFT (31U)
#define PWMV2_CNT_CFG2_CNT_RELOAD_EN_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG2_CNT_RELOAD_EN_SHIFT) & PWMV2_CNT_CFG2_CNT_RELOAD_EN_MASK)
#define PWMV2_CNT_CFG2_CNT_RELOAD_EN_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG2_CNT_RELOAD_EN_MASK) >> PWMV2_CNT_CFG2_CNT_RELOAD_EN_SHIFT)

/*
 * CNT_RELOAD_TRIG (RW)
 *
 * select one trigger from 8, should set to pulse in trig_mux
 */
#define PWMV2_CNT_CFG2_CNT_RELOAD_TRIG_MASK (0x7000000UL)
#define PWMV2_CNT_CFG2_CNT_RELOAD_TRIG_SHIFT (24U)
#define PWMV2_CNT_CFG2_CNT_RELOAD_TRIG_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG2_CNT_RELOAD_TRIG_SHIFT) & PWMV2_CNT_CFG2_CNT_RELOAD_TRIG_MASK)
#define PWMV2_CNT_CFG2_CNT_RELOAD_TRIG_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG2_CNT_RELOAD_TRIG_MASK) >> PWMV2_CNT_CFG2_CNT_RELOAD_TRIG_SHIFT)

/*
 * CNT_UPDATE_TRIG1 (RW)
 *
 * select one trigger from 8, should set to pulse in trig_mux
 */
#define PWMV2_CNT_CFG2_CNT_UPDATE_TRIG1_MASK (0x700000UL)
#define PWMV2_CNT_CFG2_CNT_UPDATE_TRIG1_SHIFT (20U)
#define PWMV2_CNT_CFG2_CNT_UPDATE_TRIG1_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG2_CNT_UPDATE_TRIG1_SHIFT) & PWMV2_CNT_CFG2_CNT_UPDATE_TRIG1_MASK)
#define PWMV2_CNT_CFG2_CNT_UPDATE_TRIG1_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG2_CNT_UPDATE_TRIG1_MASK) >> PWMV2_CNT_CFG2_CNT_UPDATE_TRIG1_SHIFT)

/*
 * CNT_UPDATE_EN1 (RW)
 *
 * set to enable using trig1 to load calculation cell output to counter
 */
#define PWMV2_CNT_CFG2_CNT_UPDATE_EN1_MASK (0x80000UL)
#define PWMV2_CNT_CFG2_CNT_UPDATE_EN1_SHIFT (19U)
#define PWMV2_CNT_CFG2_CNT_UPDATE_EN1_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG2_CNT_UPDATE_EN1_SHIFT) & PWMV2_CNT_CFG2_CNT_UPDATE_EN1_MASK)
#define PWMV2_CNT_CFG2_CNT_UPDATE_EN1_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG2_CNT_UPDATE_EN1_MASK) >> PWMV2_CNT_CFG2_CNT_UPDATE_EN1_SHIFT)

/*
 * CNT_TRIG1 (RW)
 *
 * change counter value to one of the calculation cell output when cnt_update_triger1 issued
 */
#define PWMV2_CNT_CFG2_CNT_TRIG1_MASK (0xF000U)
#define PWMV2_CNT_CFG2_CNT_TRIG1_SHIFT (12U)
#define PWMV2_CNT_CFG2_CNT_TRIG1_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG2_CNT_TRIG1_SHIFT) & PWMV2_CNT_CFG2_CNT_TRIG1_MASK)
#define PWMV2_CNT_CFG2_CNT_TRIG1_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG2_CNT_TRIG1_MASK) >> PWMV2_CNT_CFG2_CNT_TRIG1_SHIFT)

/*
 * CNT_UPDATE_TRIG0 (RW)
 *
 * select one trigger from 8, should set to pulse in trig_mux
 */
#define PWMV2_CNT_CFG2_CNT_UPDATE_TRIG0_MASK (0x700U)
#define PWMV2_CNT_CFG2_CNT_UPDATE_TRIG0_SHIFT (8U)
#define PWMV2_CNT_CFG2_CNT_UPDATE_TRIG0_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG2_CNT_UPDATE_TRIG0_SHIFT) & PWMV2_CNT_CFG2_CNT_UPDATE_TRIG0_MASK)
#define PWMV2_CNT_CFG2_CNT_UPDATE_TRIG0_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG2_CNT_UPDATE_TRIG0_MASK) >> PWMV2_CNT_CFG2_CNT_UPDATE_TRIG0_SHIFT)

/*
 * CNT_UPDATE_EN0 (RW)
 *
 * set to enable using trig0 to load calculation cell output to counter
 */
#define PWMV2_CNT_CFG2_CNT_UPDATE_EN0_MASK (0x80U)
#define PWMV2_CNT_CFG2_CNT_UPDATE_EN0_SHIFT (7U)
#define PWMV2_CNT_CFG2_CNT_UPDATE_EN0_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG2_CNT_UPDATE_EN0_SHIFT) & PWMV2_CNT_CFG2_CNT_UPDATE_EN0_MASK)
#define PWMV2_CNT_CFG2_CNT_UPDATE_EN0_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG2_CNT_UPDATE_EN0_MASK) >> PWMV2_CNT_CFG2_CNT_UPDATE_EN0_SHIFT)

/*
 * CNT_TRIG0 (RW)
 *
 * change counter value to one of the calculation cell output when cnt_update_triger0 issued
 */
#define PWMV2_CNT_CFG2_CNT_TRIG0_MASK (0xFU)
#define PWMV2_CNT_CFG2_CNT_TRIG0_SHIFT (0U)
#define PWMV2_CNT_CFG2_CNT_TRIG0_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG2_CNT_TRIG0_SHIFT) & PWMV2_CNT_CFG2_CNT_TRIG0_MASK)
#define PWMV2_CNT_CFG2_CNT_TRIG0_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG2_CNT_TRIG0_MASK) >> PWMV2_CNT_CFG2_CNT_TRIG0_SHIFT)

/* Bitfield definition for register of struct array CNT: CFG3 */
/*
 * CNT_START_SEL (RW)
 *
 * select one trigger from 8, should set to pulse in trig_mux
 */
#define PWMV2_CNT_CFG3_CNT_START_SEL_MASK (0x700000UL)
#define PWMV2_CNT_CFG3_CNT_START_SEL_SHIFT (20U)
#define PWMV2_CNT_CFG3_CNT_START_SEL_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG3_CNT_START_SEL_SHIFT) & PWMV2_CNT_CFG3_CNT_START_SEL_MASK)
#define PWMV2_CNT_CFG3_CNT_START_SEL_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG3_CNT_START_SEL_MASK) >> PWMV2_CNT_CFG3_CNT_START_SEL_SHIFT)

/*
 * CNT_HW_START_EN (RW)
 *
 * enable use trigger to start pwm output(at next reload point), by cnt_start_sel
 */
#define PWMV2_CNT_CFG3_CNT_HW_START_EN_MASK (0x20000UL)
#define PWMV2_CNT_CFG3_CNT_HW_START_EN_SHIFT (17U)
#define PWMV2_CNT_CFG3_CNT_HW_START_EN_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG3_CNT_HW_START_EN_SHIFT) & PWMV2_CNT_CFG3_CNT_HW_START_EN_MASK)
#define PWMV2_CNT_CFG3_CNT_HW_START_EN_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG3_CNT_HW_START_EN_MASK) >> PWMV2_CNT_CFG3_CNT_HW_START_EN_SHIFT)

/*
 * CNT_BURST (RW)
 *
 * output pwm wave for configured burst(timer period),
 * 0 for one burst;  1 for two burst.
 * set to 0xFFFF for always output pwm wave
 * bit's only used when setting cnt_sw_start or trigger selected by cnt_start_sel
 */
#define PWMV2_CNT_CFG3_CNT_BURST_MASK (0xFFFFU)
#define PWMV2_CNT_CFG3_CNT_BURST_SHIFT (0U)
#define PWMV2_CNT_CFG3_CNT_BURST_SET(x) (((uint32_t)(x) << PWMV2_CNT_CFG3_CNT_BURST_SHIFT) & PWMV2_CNT_CFG3_CNT_BURST_MASK)
#define PWMV2_CNT_CFG3_CNT_BURST_GET(x) (((uint32_t)(x) & PWMV2_CNT_CFG3_CNT_BURST_MASK) >> PWMV2_CNT_CFG3_CNT_BURST_SHIFT)

/* Bitfield definition for register: CNT_GLBCFG */
/*
 * CNT_SW_START (WO)
 *
 * set to start pwm output(at next reload point), write only, Auto clear.
 * User can disable pwm output before burst end by start again with cnt_burst=0
 */
#define PWMV2_CNT_GLBCFG_CNT_SW_START_MASK (0xF0000UL)
#define PWMV2_CNT_GLBCFG_CNT_SW_START_SHIFT (16U)
#define PWMV2_CNT_GLBCFG_CNT_SW_START_SET(x) (((uint32_t)(x) << PWMV2_CNT_GLBCFG_CNT_SW_START_SHIFT) & PWMV2_CNT_GLBCFG_CNT_SW_START_MASK)
#define PWMV2_CNT_GLBCFG_CNT_SW_START_GET(x) (((uint32_t)(x) & PWMV2_CNT_GLBCFG_CNT_SW_START_MASK) >> PWMV2_CNT_GLBCFG_CNT_SW_START_SHIFT)

/*
 * TIMER_RESET (WO)
 *
 * set to clear current timer. Auto clear
 */
#define PWMV2_CNT_GLBCFG_TIMER_RESET_MASK (0xF00U)
#define PWMV2_CNT_GLBCFG_TIMER_RESET_SHIFT (8U)
#define PWMV2_CNT_GLBCFG_TIMER_RESET_SET(x) (((uint32_t)(x) << PWMV2_CNT_GLBCFG_TIMER_RESET_SHIFT) & PWMV2_CNT_GLBCFG_TIMER_RESET_MASK)
#define PWMV2_CNT_GLBCFG_TIMER_RESET_GET(x) (((uint32_t)(x) & PWMV2_CNT_GLBCFG_TIMER_RESET_MASK) >> PWMV2_CNT_GLBCFG_TIMER_RESET_SHIFT)

/*
 * TIMER_ENABLE (RW)
 *
 * 1 to enable the main cycle counter; 0 to stop the counter;
 * NOTE:  when counter stopped, the related trigger_out will be cleared to 0, the related pwm output will keep value not changed.
 */
#define PWMV2_CNT_GLBCFG_TIMER_ENABLE_MASK (0xFU)
#define PWMV2_CNT_GLBCFG_TIMER_ENABLE_SHIFT (0U)
#define PWMV2_CNT_GLBCFG_TIMER_ENABLE_SET(x) (((uint32_t)(x) << PWMV2_CNT_GLBCFG_TIMER_ENABLE_SHIFT) & PWMV2_CNT_GLBCFG_TIMER_ENABLE_MASK)
#define PWMV2_CNT_GLBCFG_TIMER_ENABLE_GET(x) (((uint32_t)(x) & PWMV2_CNT_GLBCFG_TIMER_ENABLE_MASK) >> PWMV2_CNT_GLBCFG_TIMER_ENABLE_SHIFT)

/* Bitfield definition for register of struct array CAL: CFG0 */
/*
 * CAL_LU_PARAM (RW)
 *
 * up limit parameter
 */
#define PWMV2_CAL_CFG0_CAL_LU_PARAM_MASK (0x1F000000UL)
#define PWMV2_CAL_CFG0_CAL_LU_PARAM_SHIFT (24U)
#define PWMV2_CAL_CFG0_CAL_LU_PARAM_SET(x) (((uint32_t)(x) << PWMV2_CAL_CFG0_CAL_LU_PARAM_SHIFT) & PWMV2_CAL_CFG0_CAL_LU_PARAM_MASK)
#define PWMV2_CAL_CFG0_CAL_LU_PARAM_GET(x) (((uint32_t)(x) & PWMV2_CAL_CFG0_CAL_LU_PARAM_MASK) >> PWMV2_CAL_CFG0_CAL_LU_PARAM_SHIFT)

/*
 * CAL_LL_PARAM (RW)
 *
 * low limit parameter
 */
#define PWMV2_CAL_CFG0_CAL_LL_PARAM_MASK (0x1F0000UL)
#define PWMV2_CAL_CFG0_CAL_LL_PARAM_SHIFT (16U)
#define PWMV2_CAL_CFG0_CAL_LL_PARAM_SET(x) (((uint32_t)(x) << PWMV2_CAL_CFG0_CAL_LL_PARAM_SHIFT) & PWMV2_CAL_CFG0_CAL_LL_PARAM_MASK)
#define PWMV2_CAL_CFG0_CAL_LL_PARAM_GET(x) (((uint32_t)(x) & PWMV2_CAL_CFG0_CAL_LL_PARAM_MASK) >> PWMV2_CAL_CFG0_CAL_LL_PARAM_SHIFT)

/*
 * CAL_T_PARAM (RW)
 *
 * period parameter
 */
#define PWMV2_CAL_CFG0_CAL_T_PARAM_MASK (0x1F00U)
#define PWMV2_CAL_CFG0_CAL_T_PARAM_SHIFT (8U)
#define PWMV2_CAL_CFG0_CAL_T_PARAM_SET(x) (((uint32_t)(x) << PWMV2_CAL_CFG0_CAL_T_PARAM_SHIFT) & PWMV2_CAL_CFG0_CAL_T_PARAM_MASK)
#define PWMV2_CAL_CFG0_CAL_T_PARAM_GET(x) (((uint32_t)(x) & PWMV2_CAL_CFG0_CAL_T_PARAM_MASK) >> PWMV2_CAL_CFG0_CAL_T_PARAM_SHIFT)

/*
 * CAL_D_PARAM (RW)
 *
 * dac/counter value parameter
 */
#define PWMV2_CAL_CFG0_CAL_D_PARAM_MASK (0x1FU)
#define PWMV2_CAL_CFG0_CAL_D_PARAM_SHIFT (0U)
#define PWMV2_CAL_CFG0_CAL_D_PARAM_SET(x) (((uint32_t)(x) << PWMV2_CAL_CFG0_CAL_D_PARAM_SHIFT) & PWMV2_CAL_CFG0_CAL_D_PARAM_MASK)
#define PWMV2_CAL_CFG0_CAL_D_PARAM_GET(x) (((uint32_t)(x) & PWMV2_CAL_CFG0_CAL_D_PARAM_MASK) >> PWMV2_CAL_CFG0_CAL_D_PARAM_SHIFT)

/* Bitfield definition for register of struct array CAL: CFG1 */
/*
 * CAL_T_INDEX (RW)
 *
 * select one of 4 counter reload time
 */
#define PWMV2_CAL_CFG1_CAL_T_INDEX_MASK (0x30000000UL)
#define PWMV2_CAL_CFG1_CAL_T_INDEX_SHIFT (28U)
#define PWMV2_CAL_CFG1_CAL_T_INDEX_SET(x) (((uint32_t)(x) << PWMV2_CAL_CFG1_CAL_T_INDEX_SHIFT) & PWMV2_CAL_CFG1_CAL_T_INDEX_MASK)
#define PWMV2_CAL_CFG1_CAL_T_INDEX_GET(x) (((uint32_t)(x) & PWMV2_CAL_CFG1_CAL_T_INDEX_MASK) >> PWMV2_CAL_CFG1_CAL_T_INDEX_SHIFT)

/*
 * CAL_IN_INDEX (RW)
 *
 * 0~3 to select one of the dac input value; 4~7 to select one of the current counter value
 */
#define PWMV2_CAL_CFG1_CAL_IN_INDEX_MASK (0x7000000UL)
#define PWMV2_CAL_CFG1_CAL_IN_INDEX_SHIFT (24U)
#define PWMV2_CAL_CFG1_CAL_IN_INDEX_SET(x) (((uint32_t)(x) << PWMV2_CAL_CFG1_CAL_IN_INDEX_SHIFT) & PWMV2_CAL_CFG1_CAL_IN_INDEX_MASK)
#define PWMV2_CAL_CFG1_CAL_IN_INDEX_GET(x) (((uint32_t)(x) & PWMV2_CAL_CFG1_CAL_IN_INDEX_MASK) >> PWMV2_CAL_CFG1_CAL_IN_INDEX_SHIFT)

/*
 * CAL_LU_EN (RW)
 *
 * set to enable up limit
 */
#define PWMV2_CAL_CFG1_CAL_LU_EN_MASK (0x800000UL)
#define PWMV2_CAL_CFG1_CAL_LU_EN_SHIFT (23U)
#define PWMV2_CAL_CFG1_CAL_LU_EN_SET(x) (((uint32_t)(x) << PWMV2_CAL_CFG1_CAL_LU_EN_SHIFT) & PWMV2_CAL_CFG1_CAL_LU_EN_MASK)
#define PWMV2_CAL_CFG1_CAL_LU_EN_GET(x) (((uint32_t)(x) & PWMV2_CAL_CFG1_CAL_LU_EN_MASK) >> PWMV2_CAL_CFG1_CAL_LU_EN_SHIFT)

/*
 * CAL_LIM_UP (RW)
 *
 * up limit offset selection, select from one of the shadow_val
 */
#define PWMV2_CAL_CFG1_CAL_LIM_UP_MASK (0x1F0000UL)
#define PWMV2_CAL_CFG1_CAL_LIM_UP_SHIFT (16U)
#define PWMV2_CAL_CFG1_CAL_LIM_UP_SET(x) (((uint32_t)(x) << PWMV2_CAL_CFG1_CAL_LIM_UP_SHIFT) & PWMV2_CAL_CFG1_CAL_LIM_UP_MASK)
#define PWMV2_CAL_CFG1_CAL_LIM_UP_GET(x) (((uint32_t)(x) & PWMV2_CAL_CFG1_CAL_LIM_UP_MASK) >> PWMV2_CAL_CFG1_CAL_LIM_UP_SHIFT)

/*
 * CAL_LL_EN (RW)
 *
 * set to enable low limit
 */
#define PWMV2_CAL_CFG1_CAL_LL_EN_MASK (0x8000U)
#define PWMV2_CAL_CFG1_CAL_LL_EN_SHIFT (15U)
#define PWMV2_CAL_CFG1_CAL_LL_EN_SET(x) (((uint32_t)(x) << PWMV2_CAL_CFG1_CAL_LL_EN_SHIFT) & PWMV2_CAL_CFG1_CAL_LL_EN_MASK)
#define PWMV2_CAL_CFG1_CAL_LL_EN_GET(x) (((uint32_t)(x) & PWMV2_CAL_CFG1_CAL_LL_EN_MASK) >> PWMV2_CAL_CFG1_CAL_LL_EN_SHIFT)

/*
 * CAL_LIM_LO (RW)
 *
 * low limit offset selection, select from one of the shadow_val
 */
#define PWMV2_CAL_CFG1_CAL_LIM_LO_MASK (0x1F00U)
#define PWMV2_CAL_CFG1_CAL_LIM_LO_SHIFT (8U)
#define PWMV2_CAL_CFG1_CAL_LIM_LO_SET(x) (((uint32_t)(x) << PWMV2_CAL_CFG1_CAL_LIM_LO_SHIFT) & PWMV2_CAL_CFG1_CAL_LIM_LO_MASK)
#define PWMV2_CAL_CFG1_CAL_LIM_LO_GET(x) (((uint32_t)(x) & PWMV2_CAL_CFG1_CAL_LIM_LO_MASK) >> PWMV2_CAL_CFG1_CAL_LIM_LO_SHIFT)

/*
 * CAL_IN_OFF (RW)
 *
 * offset for calculation unit, select from one of the shadow_val.
 */
#define PWMV2_CAL_CFG1_CAL_IN_OFF_MASK (0x1FU)
#define PWMV2_CAL_CFG1_CAL_IN_OFF_SHIFT (0U)
#define PWMV2_CAL_CFG1_CAL_IN_OFF_SET(x) (((uint32_t)(x) << PWMV2_CAL_CFG1_CAL_IN_OFF_SHIFT) & PWMV2_CAL_CFG1_CAL_IN_OFF_MASK)
#define PWMV2_CAL_CFG1_CAL_IN_OFF_GET(x) (((uint32_t)(x) & PWMV2_CAL_CFG1_CAL_IN_OFF_MASK) >> PWMV2_CAL_CFG1_CAL_IN_OFF_SHIFT)

/* Bitfield definition for register of struct array CMP: CFG */
/*
 * CMP_TRIG_SEL (RW)
 *
 * select one trigger from 8, should set to pulse in trig_mux
 */
#define PWMV2_CMP_CFG_CMP_TRIG_SEL_MASK (0x70000000UL)
#define PWMV2_CMP_CFG_CMP_TRIG_SEL_SHIFT (28U)
#define PWMV2_CMP_CFG_CMP_TRIG_SEL_SET(x) (((uint32_t)(x) << PWMV2_CMP_CFG_CMP_TRIG_SEL_SHIFT) & PWMV2_CMP_CFG_CMP_TRIG_SEL_MASK)
#define PWMV2_CMP_CFG_CMP_TRIG_SEL_GET(x) (((uint32_t)(x) & PWMV2_CMP_CFG_CMP_TRIG_SEL_MASK) >> PWMV2_CMP_CFG_CMP_TRIG_SEL_SHIFT)

/*
 * CMP_UPDATE_TIME (RW)
 *
 * define when to use the shadow register value for working register(trig_cmp)
 * 000:  software set work_ctrl1.shadow_lock bit
 * 001:  update immediately(at next cycle)
 * 010:  related counter reload time
 * 011:  use cmp_update_trigger(from trig_mux, selected by cmp_trig_sel)
 * 100:  use the related counter rld_cmp_sel0  to select one compare point
 * 101:  use the related counter rld_cmp_sel1, to select one compare point
 * 11x:  reserved, no update.
 */
#define PWMV2_CMP_CFG_CMP_UPDATE_TIME_MASK (0x7000000UL)
#define PWMV2_CMP_CFG_CMP_UPDATE_TIME_SHIFT (24U)
#define PWMV2_CMP_CFG_CMP_UPDATE_TIME_SET(x) (((uint32_t)(x) << PWMV2_CMP_CFG_CMP_UPDATE_TIME_SHIFT) & PWMV2_CMP_CFG_CMP_UPDATE_TIME_MASK)
#define PWMV2_CMP_CFG_CMP_UPDATE_TIME_GET(x) (((uint32_t)(x) & PWMV2_CMP_CFG_CMP_UPDATE_TIME_MASK) >> PWMV2_CMP_CFG_CMP_UPDATE_TIME_SHIFT)

/*
 * CMP_IN_SEL (RW)
 *
 * 0x00~0x1B select one of the shadow_val directly
 * 0x20~0x2F select one of the calculation cell output
 * 0x30~0x37 select one of capture_pos value(low 8bit are 0)
 * 0x38+k select T/4
 * 0x3E select 0xFFFFF000
 * 0x3F select 0xFFFFFF00
 * others select 0
 */
#define PWMV2_CMP_CFG_CMP_IN_SEL_MASK (0x3F0000UL)
#define PWMV2_CMP_CFG_CMP_IN_SEL_SHIFT (16U)
#define PWMV2_CMP_CFG_CMP_IN_SEL_SET(x) (((uint32_t)(x) << PWMV2_CMP_CFG_CMP_IN_SEL_SHIFT) & PWMV2_CMP_CFG_CMP_IN_SEL_MASK)
#define PWMV2_CMP_CFG_CMP_IN_SEL_GET(x) (((uint32_t)(x) & PWMV2_CMP_CFG_CMP_IN_SEL_MASK) >> PWMV2_CMP_CFG_CMP_IN_SEL_SHIFT)

/*
 * CMP_CNT (RW)
 *
 * select one from 4 counters, only for N>=16.
 * for N<16, this field is0, every 4 compare point related to one counter(0123 for counter0, 4567 for counter1….)
 */
#define PWMV2_CMP_CFG_CMP_CNT_MASK (0xC000U)
#define PWMV2_CMP_CFG_CMP_CNT_SHIFT (14U)
#define PWMV2_CMP_CFG_CMP_CNT_SET(x) (((uint32_t)(x) << PWMV2_CMP_CFG_CMP_CNT_SHIFT) & PWMV2_CMP_CFG_CMP_CNT_MASK)
#define PWMV2_CMP_CFG_CMP_CNT_GET(x) (((uint32_t)(x) & PWMV2_CMP_CFG_CMP_CNT_MASK) >> PWMV2_CMP_CFG_CMP_CNT_SHIFT)



/* SHADOW_VAL register group index macro definition */
#define PWMV2_SHADOW_VAL_0 (0UL)
#define PWMV2_SHADOW_VAL_1 (1UL)
#define PWMV2_SHADOW_VAL_2 (2UL)
#define PWMV2_SHADOW_VAL_3 (3UL)
#define PWMV2_SHADOW_VAL_4 (4UL)
#define PWMV2_SHADOW_VAL_5 (5UL)
#define PWMV2_SHADOW_VAL_6 (6UL)
#define PWMV2_SHADOW_VAL_7 (7UL)
#define PWMV2_SHADOW_VAL_8 (8UL)
#define PWMV2_SHADOW_VAL_9 (9UL)
#define PWMV2_SHADOW_VAL_10 (10UL)
#define PWMV2_SHADOW_VAL_11 (11UL)
#define PWMV2_SHADOW_VAL_12 (12UL)
#define PWMV2_SHADOW_VAL_13 (13UL)
#define PWMV2_SHADOW_VAL_14 (14UL)
#define PWMV2_SHADOW_VAL_15 (15UL)
#define PWMV2_SHADOW_VAL_16 (16UL)
#define PWMV2_SHADOW_VAL_17 (17UL)
#define PWMV2_SHADOW_VAL_18 (18UL)
#define PWMV2_SHADOW_VAL_19 (19UL)
#define PWMV2_SHADOW_VAL_20 (20UL)
#define PWMV2_SHADOW_VAL_21 (21UL)
#define PWMV2_SHADOW_VAL_22 (22UL)
#define PWMV2_SHADOW_VAL_23 (23UL)
#define PWMV2_SHADOW_VAL_24 (24UL)
#define PWMV2_SHADOW_VAL_25 (25UL)
#define PWMV2_SHADOW_VAL_26 (26UL)
#define PWMV2_SHADOW_VAL_27 (27UL)

/* PWM register group index macro definition */
#define PWMV2_PWM_0 (0UL)
#define PWMV2_PWM_1 (1UL)
#define PWMV2_PWM_2 (2UL)
#define PWMV2_PWM_3 (3UL)
#define PWMV2_PWM_4 (4UL)
#define PWMV2_PWM_5 (5UL)
#define PWMV2_PWM_6 (6UL)
#define PWMV2_PWM_7 (7UL)

/* TRIGGER_CFG register group index macro definition */
#define PWMV2_TRIGGER_CFG_0 (0UL)
#define PWMV2_TRIGGER_CFG_1 (1UL)
#define PWMV2_TRIGGER_CFG_2 (2UL)
#define PWMV2_TRIGGER_CFG_3 (3UL)
#define PWMV2_TRIGGER_CFG_4 (4UL)
#define PWMV2_TRIGGER_CFG_5 (5UL)
#define PWMV2_TRIGGER_CFG_6 (6UL)
#define PWMV2_TRIGGER_CFG_7 (7UL)

/* CNT_RELOAD_WORK register group index macro definition */
#define PWMV2_CNT_RELOAD_WORK_0 (0UL)
#define PWMV2_CNT_RELOAD_WORK_1 (1UL)
#define PWMV2_CNT_RELOAD_WORK_2 (2UL)
#define PWMV2_CNT_RELOAD_WORK_3 (3UL)

/* CMP_VAL_WORK register group index macro definition */
#define PWMV2_CMP_VAL_WORK_0 (0UL)
#define PWMV2_CMP_VAL_WORK_1 (1UL)
#define PWMV2_CMP_VAL_WORK_2 (2UL)
#define PWMV2_CMP_VAL_WORK_3 (3UL)
#define PWMV2_CMP_VAL_WORK_4 (4UL)
#define PWMV2_CMP_VAL_WORK_5 (5UL)
#define PWMV2_CMP_VAL_WORK_6 (6UL)
#define PWMV2_CMP_VAL_WORK_7 (7UL)
#define PWMV2_CMP_VAL_WORK_8 (8UL)
#define PWMV2_CMP_VAL_WORK_9 (9UL)
#define PWMV2_CMP_VAL_WORK_10 (10UL)
#define PWMV2_CMP_VAL_WORK_11 (11UL)
#define PWMV2_CMP_VAL_WORK_12 (12UL)
#define PWMV2_CMP_VAL_WORK_13 (13UL)
#define PWMV2_CMP_VAL_WORK_14 (14UL)
#define PWMV2_CMP_VAL_WORK_15 (15UL)
#define PWMV2_CMP_VAL_WORK_16 (16UL)
#define PWMV2_CMP_VAL_WORK_17 (17UL)
#define PWMV2_CMP_VAL_WORK_18 (18UL)
#define PWMV2_CMP_VAL_WORK_19 (19UL)
#define PWMV2_CMP_VAL_WORK_20 (20UL)
#define PWMV2_CMP_VAL_WORK_21 (21UL)
#define PWMV2_CMP_VAL_WORK_22 (22UL)
#define PWMV2_CMP_VAL_WORK_23 (23UL)

/* CNT_VAL register group index macro definition */
#define PWMV2_CNT_VAL_0 (0UL)
#define PWMV2_CNT_VAL_1 (1UL)
#define PWMV2_CNT_VAL_2 (2UL)
#define PWMV2_CNT_VAL_3 (3UL)

/* DAC_VALUE_SV register group index macro definition */
#define PWMV2_DAC_VALUE_SV_0 (0UL)
#define PWMV2_DAC_VALUE_SV_1 (1UL)
#define PWMV2_DAC_VALUE_SV_2 (2UL)
#define PWMV2_DAC_VALUE_SV_3 (3UL)

/* CAPTURE_POS register group index macro definition */
#define PWMV2_CAPTURE_POS_0 (0UL)
#define PWMV2_CAPTURE_POS_1 (1UL)
#define PWMV2_CAPTURE_POS_2 (2UL)
#define PWMV2_CAPTURE_POS_3 (3UL)
#define PWMV2_CAPTURE_POS_4 (4UL)
#define PWMV2_CAPTURE_POS_5 (5UL)
#define PWMV2_CAPTURE_POS_6 (6UL)
#define PWMV2_CAPTURE_POS_7 (7UL)

/* CAPTURE_NEG register group index macro definition */
#define PWMV2_CAPTURE_NEG_0 (0UL)
#define PWMV2_CAPTURE_NEG_1 (1UL)
#define PWMV2_CAPTURE_NEG_2 (2UL)
#define PWMV2_CAPTURE_NEG_3 (3UL)
#define PWMV2_CAPTURE_NEG_4 (4UL)
#define PWMV2_CAPTURE_NEG_5 (5UL)
#define PWMV2_CAPTURE_NEG_6 (6UL)
#define PWMV2_CAPTURE_NEG_7 (7UL)

/* CNT register group index macro definition */
#define PWMV2_CNT_0 (0UL)
#define PWMV2_CNT_1 (1UL)
#define PWMV2_CNT_2 (2UL)
#define PWMV2_CNT_3 (3UL)

/* CAL register group index macro definition */
#define PWMV2_CAL_0 (0UL)
#define PWMV2_CAL_1 (1UL)
#define PWMV2_CAL_2 (2UL)
#define PWMV2_CAL_3 (3UL)
#define PWMV2_CAL_4 (4UL)
#define PWMV2_CAL_5 (5UL)
#define PWMV2_CAL_6 (6UL)
#define PWMV2_CAL_7 (7UL)
#define PWMV2_CAL_8 (8UL)
#define PWMV2_CAL_9 (9UL)
#define PWMV2_CAL_10 (10UL)
#define PWMV2_CAL_11 (11UL)
#define PWMV2_CAL_12 (12UL)
#define PWMV2_CAL_13 (13UL)
#define PWMV2_CAL_14 (14UL)
#define PWMV2_CAL_15 (15UL)

/* CMP register group index macro definition */
#define PWMV2_CMP_0 (0UL)
#define PWMV2_CMP_1 (1UL)
#define PWMV2_CMP_2 (2UL)
#define PWMV2_CMP_3 (3UL)
#define PWMV2_CMP_4 (4UL)
#define PWMV2_CMP_5 (5UL)
#define PWMV2_CMP_6 (6UL)
#define PWMV2_CMP_7 (7UL)
#define PWMV2_CMP_8 (8UL)
#define PWMV2_CMP_9 (9UL)
#define PWMV2_CMP_10 (10UL)
#define PWMV2_CMP_11 (11UL)
#define PWMV2_CMP_12 (12UL)
#define PWMV2_CMP_13 (13UL)
#define PWMV2_CMP_14 (14UL)
#define PWMV2_CMP_15 (15UL)
#define PWMV2_CMP_16 (16UL)
#define PWMV2_CMP_17 (17UL)
#define PWMV2_CMP_18 (18UL)
#define PWMV2_CMP_19 (19UL)
#define PWMV2_CMP_20 (20UL)
#define PWMV2_CMP_21 (21UL)
#define PWMV2_CMP_22 (22UL)
#define PWMV2_CMP_23 (23UL)


#endif /* HPM_PWMV2_H */
