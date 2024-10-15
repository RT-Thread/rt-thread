/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_PWM_H
#define HPM_PWM_H

typedef struct {
    __RW uint32_t UNLK;                        /* 0x0: Shadow registers unlock register */
    union {
        __RW uint32_t STA;                     /* 0x4: Counter start register */
    };
    union {
        __RW uint32_t RLD;                     /* 0x8: Counter reload register */
    };
    union {
        __RW uint32_t CMP[24];                 /* 0xC - 0x68: Comparator register */
    };
    __R  uint8_t  RESERVED0[12];               /* 0x6C - 0x77: Reserved */
    __RW uint32_t FRCMD;                       /* 0x78: Force output mode register */
    __RW uint32_t SHLK;                        /* 0x7C: Shadow registers lock register */
    __RW uint32_t CHCFG[24];                   /* 0x80 - 0xDC: Output channel configure register */
    __R  uint8_t  RESERVED1[16];               /* 0xE0 - 0xEF: Reserved */
    __RW uint32_t GCR;                         /* 0xF0: Global control register */
    __RW uint32_t SHCR;                        /* 0xF4: Shadow register control register */
    __R  uint8_t  RESERVED2[8];                /* 0xF8 - 0xFF: Reserved */
    __R  uint32_t CAPPOS[24];                  /* 0x100 - 0x15C: Capture rising edge register */
    __R  uint8_t  RESERVED3[16];               /* 0x160 - 0x16F: Reserved */
    __R  uint32_t CNT;                         /* 0x170: Counter */
    __R  uint8_t  RESERVED4[12];               /* 0x174 - 0x17F: Reserved */
    __R  uint32_t CAPNEG[24];                  /* 0x180 - 0x1DC: Capture falling edge register */
    __R  uint8_t  RESERVED5[16];               /* 0x1E0 - 0x1EF: Reserved */
    __R  uint32_t CNTCOPY;                     /* 0x1F0: Counter copy */
    __R  uint8_t  RESERVED6[12];               /* 0x1F4 - 0x1FF: Reserved */
    __RW uint32_t PWMCFG[8];                   /* 0x200 - 0x21C: PWM channel configure register */
    __W  uint32_t SR;                          /* 0x220: Status register */
    __RW uint32_t IRQEN;                       /* 0x224: Interrupt request enable register */
    __R  uint8_t  RESERVED7[4];                /* 0x228 - 0x22B: Reserved */
    __RW uint32_t DMAEN;                       /* 0x22C: DMA request enable register */
    __RW uint32_t CMPCFG[24];                  /* 0x230 - 0x28C: Comparator configure register */
} PWM_Type;


/* Bitfield definition for register: UNLK */
/*
 * SHUNLK (RW)
 *
 * write 0xB0382607 to unlock the shadow registers of register offset from 0x04 to 0x78,
 * otherwise the shadow registers can not be written.
 */
#define PWM_UNLK_SHUNLK_MASK (0xFFFFFFFFUL)
#define PWM_UNLK_SHUNLK_SHIFT (0U)
#define PWM_UNLK_SHUNLK_SET(x) (((uint32_t)(x) << PWM_UNLK_SHUNLK_SHIFT) & PWM_UNLK_SHUNLK_MASK)
#define PWM_UNLK_SHUNLK_GET(x) (((uint32_t)(x) & PWM_UNLK_SHUNLK_MASK) >> PWM_UNLK_SHUNLK_SHIFT)

/* Bitfield definition for register: STA */
/*
 * XSTA (RW)
 *
 * pwm timer counter extended start point, should back to this value after reach xrld
 */
#define PWM_STA_XSTA_MASK (0xF0000000UL)
#define PWM_STA_XSTA_SHIFT (28U)
#define PWM_STA_XSTA_SET(x) (((uint32_t)(x) << PWM_STA_XSTA_SHIFT) & PWM_STA_XSTA_MASK)
#define PWM_STA_XSTA_GET(x) (((uint32_t)(x) & PWM_STA_XSTA_MASK) >> PWM_STA_XSTA_SHIFT)

/*
 * STA (RW)
 *
 * pwm timer counter start value
 *  sta/rld will be loaded from shadow register to work register at main counter reload time, or software write unlk.shunlk
 */
#define PWM_STA_STA_MASK (0xFFFFFF0UL)
#define PWM_STA_STA_SHIFT (4U)
#define PWM_STA_STA_SET(x) (((uint32_t)(x) << PWM_STA_STA_SHIFT) & PWM_STA_STA_MASK)
#define PWM_STA_STA_GET(x) (((uint32_t)(x) & PWM_STA_STA_MASK) >> PWM_STA_STA_SHIFT)

/* Bitfield definition for register: RLD */
/*
 * XRLD (RW)
 *
 * timeout counter extended reload point, counter will reload to xsta after reach this point
 */
#define PWM_RLD_XRLD_MASK (0xF0000000UL)
#define PWM_RLD_XRLD_SHIFT (28U)
#define PWM_RLD_XRLD_SET(x) (((uint32_t)(x) << PWM_RLD_XRLD_SHIFT) & PWM_RLD_XRLD_MASK)
#define PWM_RLD_XRLD_GET(x) (((uint32_t)(x) & PWM_RLD_XRLD_MASK) >> PWM_RLD_XRLD_SHIFT)

/*
 * RLD (RW)
 *
 * pwm timer counter reload value
 */
#define PWM_RLD_RLD_MASK (0xFFFFFF0UL)
#define PWM_RLD_RLD_SHIFT (4U)
#define PWM_RLD_RLD_SET(x) (((uint32_t)(x) << PWM_RLD_RLD_SHIFT) & PWM_RLD_RLD_MASK)
#define PWM_RLD_RLD_GET(x) (((uint32_t)(x) & PWM_RLD_RLD_MASK) >> PWM_RLD_RLD_SHIFT)

/* Bitfield definition for register: 0 */
/*
 * XCMP (RW)
 *
 * extended counter compare value
 */
#define PWM_CMP_XCMP_MASK (0xF0000000UL)
#define PWM_CMP_XCMP_SHIFT (28U)
#define PWM_CMP_XCMP_SET(x) (((uint32_t)(x) << PWM_CMP_XCMP_SHIFT) & PWM_CMP_XCMP_MASK)
#define PWM_CMP_XCMP_GET(x) (((uint32_t)(x) & PWM_CMP_XCMP_MASK) >> PWM_CMP_XCMP_SHIFT)

/*
 * CMP (RW)
 *
 * clock counter compare value, the compare output is 0 at default, set to 1 when compare value meet,
 * and clr to 0 when timer reload. Software can invert the output by setting chan_cfg.out_polarity.
 */
#define PWM_CMP_CMP_MASK (0xFFFFFF0UL)
#define PWM_CMP_CMP_SHIFT (4U)
#define PWM_CMP_CMP_SET(x) (((uint32_t)(x) << PWM_CMP_CMP_SHIFT) & PWM_CMP_CMP_MASK)
#define PWM_CMP_CMP_GET(x) (((uint32_t)(x) & PWM_CMP_CMP_MASK) >> PWM_CMP_CMP_SHIFT)

/*
 * CMPHLF (RW)
 *
 * half clock counter compare value
 */
#define PWM_CMP_CMPHLF_MASK (0x8U)
#define PWM_CMP_CMPHLF_SHIFT (3U)
#define PWM_CMP_CMPHLF_SET(x) (((uint32_t)(x) << PWM_CMP_CMPHLF_SHIFT) & PWM_CMP_CMPHLF_MASK)
#define PWM_CMP_CMPHLF_GET(x) (((uint32_t)(x) & PWM_CMP_CMPHLF_MASK) >> PWM_CMP_CMPHLF_SHIFT)

/*
 * CMPJIT (RW)
 *
 * jitter counter compare value
 */
#define PWM_CMP_CMPJIT_MASK (0x7U)
#define PWM_CMP_CMPJIT_SHIFT (0U)
#define PWM_CMP_CMPJIT_SET(x) (((uint32_t)(x) << PWM_CMP_CMPJIT_SHIFT) & PWM_CMP_CMPJIT_MASK)
#define PWM_CMP_CMPJIT_GET(x) (((uint32_t)(x) & PWM_CMP_CMPJIT_MASK) >> PWM_CMP_CMPJIT_SHIFT)

/* Bitfield definition for register: FRCMD */
/*
 * FRCMD (RW)
 *
 * 2bit for each PWM output channel (0-7);
 * 00:  force output 0
 * 01:  force output 1
 * 10:  output highz
 * 11:  no force
 */
#define PWM_FRCMD_FRCMD_MASK (0xFFFFU)
#define PWM_FRCMD_FRCMD_SHIFT (0U)
#define PWM_FRCMD_FRCMD_SET(x) (((uint32_t)(x) << PWM_FRCMD_FRCMD_SHIFT) & PWM_FRCMD_FRCMD_MASK)
#define PWM_FRCMD_FRCMD_GET(x) (((uint32_t)(x) & PWM_FRCMD_FRCMD_MASK) >> PWM_FRCMD_FRCMD_SHIFT)

/* Bitfield definition for register: SHLK */
/*
 * SHLK (RW)
 *
 * write 1 to lock all shawdow register, write access is not permitted
 */
#define PWM_SHLK_SHLK_MASK (0x80000000UL)
#define PWM_SHLK_SHLK_SHIFT (31U)
#define PWM_SHLK_SHLK_SET(x) (((uint32_t)(x) << PWM_SHLK_SHLK_SHIFT) & PWM_SHLK_SHLK_MASK)
#define PWM_SHLK_SHLK_GET(x) (((uint32_t)(x) & PWM_SHLK_SHLK_MASK) >> PWM_SHLK_SHLK_SHIFT)

/* Bitfield definition for register array: CHCFG */
/*
 * CMPSELEND (RW)
 *
 * assign the last comparator for this output channel
 */
#define PWM_CHCFG_CMPSELEND_MASK (0x1F000000UL)
#define PWM_CHCFG_CMPSELEND_SHIFT (24U)
#define PWM_CHCFG_CMPSELEND_SET(x) (((uint32_t)(x) << PWM_CHCFG_CMPSELEND_SHIFT) & PWM_CHCFG_CMPSELEND_MASK)
#define PWM_CHCFG_CMPSELEND_GET(x) (((uint32_t)(x) & PWM_CHCFG_CMPSELEND_MASK) >> PWM_CHCFG_CMPSELEND_SHIFT)

/*
 * CMPSELBEG (RW)
 *
 * assign the first comparator for this output channel
 */
#define PWM_CHCFG_CMPSELBEG_MASK (0x1F0000UL)
#define PWM_CHCFG_CMPSELBEG_SHIFT (16U)
#define PWM_CHCFG_CMPSELBEG_SET(x) (((uint32_t)(x) << PWM_CHCFG_CMPSELBEG_SHIFT) & PWM_CHCFG_CMPSELBEG_MASK)
#define PWM_CHCFG_CMPSELBEG_GET(x) (((uint32_t)(x) & PWM_CHCFG_CMPSELBEG_MASK) >> PWM_CHCFG_CMPSELBEG_SHIFT)

/*
 * OUTPOL (RW)
 *
 * output polarity, set to 1 will invert the output
 */
#define PWM_CHCFG_OUTPOL_MASK (0x2U)
#define PWM_CHCFG_OUTPOL_SHIFT (1U)
#define PWM_CHCFG_OUTPOL_SET(x) (((uint32_t)(x) << PWM_CHCFG_OUTPOL_SHIFT) & PWM_CHCFG_OUTPOL_MASK)
#define PWM_CHCFG_OUTPOL_GET(x) (((uint32_t)(x) & PWM_CHCFG_OUTPOL_MASK) >> PWM_CHCFG_OUTPOL_SHIFT)

/* Bitfield definition for register: GCR */
/*
 * FAULTI3EN (RW)
 *
 * 1- enable the internal fault input 3
 */
#define PWM_GCR_FAULTI3EN_MASK (0x80000000UL)
#define PWM_GCR_FAULTI3EN_SHIFT (31U)
#define PWM_GCR_FAULTI3EN_SET(x) (((uint32_t)(x) << PWM_GCR_FAULTI3EN_SHIFT) & PWM_GCR_FAULTI3EN_MASK)
#define PWM_GCR_FAULTI3EN_GET(x) (((uint32_t)(x) & PWM_GCR_FAULTI3EN_MASK) >> PWM_GCR_FAULTI3EN_SHIFT)

/*
 * FAULTI2EN (RW)
 *
 * 1- enable the internal fault input 2
 */
#define PWM_GCR_FAULTI2EN_MASK (0x40000000UL)
#define PWM_GCR_FAULTI2EN_SHIFT (30U)
#define PWM_GCR_FAULTI2EN_SET(x) (((uint32_t)(x) << PWM_GCR_FAULTI2EN_SHIFT) & PWM_GCR_FAULTI2EN_MASK)
#define PWM_GCR_FAULTI2EN_GET(x) (((uint32_t)(x) & PWM_GCR_FAULTI2EN_MASK) >> PWM_GCR_FAULTI2EN_SHIFT)

/*
 * FAULTI1EN (RW)
 *
 * 1- enable the internal fault input 1
 */
#define PWM_GCR_FAULTI1EN_MASK (0x20000000UL)
#define PWM_GCR_FAULTI1EN_SHIFT (29U)
#define PWM_GCR_FAULTI1EN_SET(x) (((uint32_t)(x) << PWM_GCR_FAULTI1EN_SHIFT) & PWM_GCR_FAULTI1EN_MASK)
#define PWM_GCR_FAULTI1EN_GET(x) (((uint32_t)(x) & PWM_GCR_FAULTI1EN_MASK) >> PWM_GCR_FAULTI1EN_SHIFT)

/*
 * FAULTI0EN (RW)
 *
 * 1- enable the internal fault input 0
 */
#define PWM_GCR_FAULTI0EN_MASK (0x10000000UL)
#define PWM_GCR_FAULTI0EN_SHIFT (28U)
#define PWM_GCR_FAULTI0EN_SET(x) (((uint32_t)(x) << PWM_GCR_FAULTI0EN_SHIFT) & PWM_GCR_FAULTI0EN_MASK)
#define PWM_GCR_FAULTI0EN_GET(x) (((uint32_t)(x) & PWM_GCR_FAULTI0EN_MASK) >> PWM_GCR_FAULTI0EN_SHIFT)

/*
 * DEBUGFAULT (RW)
 *
 * 1- enable debug mode output protection
 */
#define PWM_GCR_DEBUGFAULT_MASK (0x8000000UL)
#define PWM_GCR_DEBUGFAULT_SHIFT (27U)
#define PWM_GCR_DEBUGFAULT_SET(x) (((uint32_t)(x) << PWM_GCR_DEBUGFAULT_SHIFT) & PWM_GCR_DEBUGFAULT_MASK)
#define PWM_GCR_DEBUGFAULT_GET(x) (((uint32_t)(x) & PWM_GCR_DEBUGFAULT_MASK) >> PWM_GCR_DEBUGFAULT_SHIFT)

/*
 * FRCPOL (RW)
 *
 * polarity of input pwm_force,
 * 1- active low
 * 0- active high
 */
#define PWM_GCR_FRCPOL_MASK (0x4000000UL)
#define PWM_GCR_FRCPOL_SHIFT (26U)
#define PWM_GCR_FRCPOL_SET(x) (((uint32_t)(x) << PWM_GCR_FRCPOL_SHIFT) & PWM_GCR_FRCPOL_MASK)
#define PWM_GCR_FRCPOL_GET(x) (((uint32_t)(x) & PWM_GCR_FRCPOL_MASK) >> PWM_GCR_FRCPOL_SHIFT)

/*
 * HWSHDWEDG (RW)
 *
 * When hardware event is selected as shawdow register effective time and the select comparator is configured as input capture mode.
 * This bit assign its which edge is used as compare shadow register hardware load event.
 * 1- Falling edge
 * 0- Rising edge
 */
#define PWM_GCR_HWSHDWEDG_MASK (0x1000000UL)
#define PWM_GCR_HWSHDWEDG_SHIFT (24U)
#define PWM_GCR_HWSHDWEDG_SET(x) (((uint32_t)(x) << PWM_GCR_HWSHDWEDG_SHIFT) & PWM_GCR_HWSHDWEDG_MASK)
#define PWM_GCR_HWSHDWEDG_GET(x) (((uint32_t)(x) & PWM_GCR_HWSHDWEDG_MASK) >> PWM_GCR_HWSHDWEDG_SHIFT)

/*
 * CMPSHDWSEL (RW)
 *
 * This bitfield select one of the comparators as hardware event time to load comparator shadow registers
 */
#define PWM_GCR_CMPSHDWSEL_MASK (0xF80000UL)
#define PWM_GCR_CMPSHDWSEL_SHIFT (19U)
#define PWM_GCR_CMPSHDWSEL_SET(x) (((uint32_t)(x) << PWM_GCR_CMPSHDWSEL_SHIFT) & PWM_GCR_CMPSHDWSEL_MASK)
#define PWM_GCR_CMPSHDWSEL_GET(x) (((uint32_t)(x) & PWM_GCR_CMPSHDWSEL_MASK) >> PWM_GCR_CMPSHDWSEL_SHIFT)

/*
 * FAULTRECEDG (RW)
 *
 * When hardware load is selected as output fault recover trigger and the selected channel is capture mode.
 * This bit assign its effective edge of fault recover trigger.
 * 1- Falling edge
 * 0- Rising edge
 */
#define PWM_GCR_FAULTRECEDG_MASK (0x40000UL)
#define PWM_GCR_FAULTRECEDG_SHIFT (18U)
#define PWM_GCR_FAULTRECEDG_SET(x) (((uint32_t)(x) << PWM_GCR_FAULTRECEDG_SHIFT) & PWM_GCR_FAULTRECEDG_MASK)
#define PWM_GCR_FAULTRECEDG_GET(x) (((uint32_t)(x) & PWM_GCR_FAULTRECEDG_MASK) >> PWM_GCR_FAULTRECEDG_SHIFT)

/*
 * FAULTRECHWSEL (RW)
 *
 * Selec one of the 24 comparators as fault output recover trigger.
 */
#define PWM_GCR_FAULTRECHWSEL_MASK (0x3E000UL)
#define PWM_GCR_FAULTRECHWSEL_SHIFT (13U)
#define PWM_GCR_FAULTRECHWSEL_SET(x) (((uint32_t)(x) << PWM_GCR_FAULTRECHWSEL_SHIFT) & PWM_GCR_FAULTRECHWSEL_MASK)
#define PWM_GCR_FAULTRECHWSEL_GET(x) (((uint32_t)(x) & PWM_GCR_FAULTRECHWSEL_MASK) >> PWM_GCR_FAULTRECHWSEL_SHIFT)

/*
 * FAULTE1EN (RW)
 *
 * 1- enable the external fault input 1
 */
#define PWM_GCR_FAULTE1EN_MASK (0x1000U)
#define PWM_GCR_FAULTE1EN_SHIFT (12U)
#define PWM_GCR_FAULTE1EN_SET(x) (((uint32_t)(x) << PWM_GCR_FAULTE1EN_SHIFT) & PWM_GCR_FAULTE1EN_MASK)
#define PWM_GCR_FAULTE1EN_GET(x) (((uint32_t)(x) & PWM_GCR_FAULTE1EN_MASK) >> PWM_GCR_FAULTE1EN_SHIFT)

/*
 * FAULTE0EN (RW)
 *
 * 1- enable the external fault input 0
 */
#define PWM_GCR_FAULTE0EN_MASK (0x800U)
#define PWM_GCR_FAULTE0EN_SHIFT (11U)
#define PWM_GCR_FAULTE0EN_SET(x) (((uint32_t)(x) << PWM_GCR_FAULTE0EN_SHIFT) & PWM_GCR_FAULTE0EN_MASK)
#define PWM_GCR_FAULTE0EN_GET(x) (((uint32_t)(x) & PWM_GCR_FAULTE0EN_MASK) >> PWM_GCR_FAULTE0EN_SHIFT)

/*
 * FAULTEXPOL (RW)
 *
 * external fault polarity
 * 1-active low
 * 0-active high
 */
#define PWM_GCR_FAULTEXPOL_MASK (0x600U)
#define PWM_GCR_FAULTEXPOL_SHIFT (9U)
#define PWM_GCR_FAULTEXPOL_SET(x) (((uint32_t)(x) << PWM_GCR_FAULTEXPOL_SHIFT) & PWM_GCR_FAULTEXPOL_MASK)
#define PWM_GCR_FAULTEXPOL_GET(x) (((uint32_t)(x) & PWM_GCR_FAULTEXPOL_MASK) >> PWM_GCR_FAULTEXPOL_SHIFT)

/*
 * RLDSYNCEN (RW)
 *
 * 1- pwm timer counter reset to reload value (rld) by synci is enabled
 */
#define PWM_GCR_RLDSYNCEN_MASK (0x100U)
#define PWM_GCR_RLDSYNCEN_SHIFT (8U)
#define PWM_GCR_RLDSYNCEN_SET(x) (((uint32_t)(x) << PWM_GCR_RLDSYNCEN_SHIFT) & PWM_GCR_RLDSYNCEN_MASK)
#define PWM_GCR_RLDSYNCEN_GET(x) (((uint32_t)(x) & PWM_GCR_RLDSYNCEN_MASK) >> PWM_GCR_RLDSYNCEN_SHIFT)

/*
 * CEN (RW)
 *
 * 1- enable the pwm timer counter
 * 0- stop the pwm timer counter
 */
#define PWM_GCR_CEN_MASK (0x80U)
#define PWM_GCR_CEN_SHIFT (7U)
#define PWM_GCR_CEN_SET(x) (((uint32_t)(x) << PWM_GCR_CEN_SHIFT) & PWM_GCR_CEN_MASK)
#define PWM_GCR_CEN_GET(x) (((uint32_t)(x) & PWM_GCR_CEN_MASK) >> PWM_GCR_CEN_SHIFT)

/*
 * FAULTCLR (RW)
 *
 * 1- Write 1 to clear the fault condition. The output will recover if FAULTRECTIME is set to 2b'11.
 * User should write 1 to this bit after the active FAULT signal de-assert and before it re-assert again.
 */
#define PWM_GCR_FAULTCLR_MASK (0x40U)
#define PWM_GCR_FAULTCLR_SHIFT (6U)
#define PWM_GCR_FAULTCLR_SET(x) (((uint32_t)(x) << PWM_GCR_FAULTCLR_SHIFT) & PWM_GCR_FAULTCLR_MASK)
#define PWM_GCR_FAULTCLR_GET(x) (((uint32_t)(x) & PWM_GCR_FAULTCLR_MASK) >> PWM_GCR_FAULTCLR_SHIFT)

/*
 * XRLDSYNCEN (RW)
 *
 * 1- pwm timer extended counter (xcnt) reset to extended reload value (xrld) by synci is enabled
 */
#define PWM_GCR_XRLDSYNCEN_MASK (0x20U)
#define PWM_GCR_XRLDSYNCEN_SHIFT (5U)
#define PWM_GCR_XRLDSYNCEN_SET(x) (((uint32_t)(x) << PWM_GCR_XRLDSYNCEN_SHIFT) & PWM_GCR_XRLDSYNCEN_MASK)
#define PWM_GCR_XRLDSYNCEN_GET(x) (((uint32_t)(x) & PWM_GCR_XRLDSYNCEN_MASK) >> PWM_GCR_XRLDSYNCEN_SHIFT)

/*
 * TIMERRESET (RW)
 *
 * set to clear current timer(total 28bit, main counter and tmout_count ). Auto clear
 */
#define PWM_GCR_TIMERRESET_MASK (0x8U)
#define PWM_GCR_TIMERRESET_SHIFT (3U)
#define PWM_GCR_TIMERRESET_SET(x) (((uint32_t)(x) << PWM_GCR_TIMERRESET_SHIFT) & PWM_GCR_TIMERRESET_MASK)
#define PWM_GCR_TIMERRESET_GET(x) (((uint32_t)(x) & PWM_GCR_TIMERRESET_MASK) >> PWM_GCR_TIMERRESET_SHIFT)

/*
 * FRCTIME (WO)
 *
 * This bit field select the force effective time
 * 00:  force immediately
 * 01:  force at main counter reload time
 * 10:  force at FRCSYNCI
 * 11: no force
 */
#define PWM_GCR_FRCTIME_MASK (0x6U)
#define PWM_GCR_FRCTIME_SHIFT (1U)
#define PWM_GCR_FRCTIME_SET(x) (((uint32_t)(x) << PWM_GCR_FRCTIME_SHIFT) & PWM_GCR_FRCTIME_MASK)
#define PWM_GCR_FRCTIME_GET(x) (((uint32_t)(x) & PWM_GCR_FRCTIME_MASK) >> PWM_GCR_FRCTIME_SHIFT)

/*
 * SWFRC (RW)
 *
 * 1- write 1 to enable software force, if the frcsrcsel is set to 0, force will take effect
 */
#define PWM_GCR_SWFRC_MASK (0x1U)
#define PWM_GCR_SWFRC_SHIFT (0U)
#define PWM_GCR_SWFRC_SET(x) (((uint32_t)(x) << PWM_GCR_SWFRC_SHIFT) & PWM_GCR_SWFRC_MASK)
#define PWM_GCR_SWFRC_GET(x) (((uint32_t)(x) & PWM_GCR_SWFRC_MASK) >> PWM_GCR_SWFRC_SHIFT)

/* Bitfield definition for register: SHCR */
/*
 * FRCSHDWSEL (RW)
 *
 * This bitfield select one of the comparators as hardware event time to load FRCMD shadow registers
 */
#define PWM_SHCR_FRCSHDWSEL_MASK (0x1F00U)
#define PWM_SHCR_FRCSHDWSEL_SHIFT (8U)
#define PWM_SHCR_FRCSHDWSEL_SET(x) (((uint32_t)(x) << PWM_SHCR_FRCSHDWSEL_SHIFT) & PWM_SHCR_FRCSHDWSEL_MASK)
#define PWM_SHCR_FRCSHDWSEL_GET(x) (((uint32_t)(x) & PWM_SHCR_FRCSHDWSEL_MASK) >> PWM_SHCR_FRCSHDWSEL_SHIFT)

/*
 * CNTSHDWSEL (RW)
 *
 * This bitfield select one of the comparators as hardware event time to load the counter related shadow registers (STA and RLD)
 */
#define PWM_SHCR_CNTSHDWSEL_MASK (0xF8U)
#define PWM_SHCR_CNTSHDWSEL_SHIFT (3U)
#define PWM_SHCR_CNTSHDWSEL_SET(x) (((uint32_t)(x) << PWM_SHCR_CNTSHDWSEL_SHIFT) & PWM_SHCR_CNTSHDWSEL_MASK)
#define PWM_SHCR_CNTSHDWSEL_GET(x) (((uint32_t)(x) & PWM_SHCR_CNTSHDWSEL_MASK) >> PWM_SHCR_CNTSHDWSEL_SHIFT)

/*
 * CNTSHDWUPT (RW)
 *
 * This bitfield select when the counter related shadow registers (STA and RLD) will be loaded to its work register
 * 00:  after software set shlk bit of shlk register
 * 01:  immediately after the register being modified
 * 10:  after hardware event assert, user can select one of the comparators to generate this hardware event.
 *        The comparator can be either output compare mode or input capture mode.
 * 11:  after SHSYNCI assert
 */
#define PWM_SHCR_CNTSHDWUPT_MASK (0x6U)
#define PWM_SHCR_CNTSHDWUPT_SHIFT (1U)
#define PWM_SHCR_CNTSHDWUPT_SET(x) (((uint32_t)(x) << PWM_SHCR_CNTSHDWUPT_SHIFT) & PWM_SHCR_CNTSHDWUPT_MASK)
#define PWM_SHCR_CNTSHDWUPT_GET(x) (((uint32_t)(x) & PWM_SHCR_CNTSHDWUPT_MASK) >> PWM_SHCR_CNTSHDWUPT_SHIFT)

/*
 * SHLKEN (RW)
 *
 * 1- enable shadow registers lock feature,
 * 0- disable shadow registers lock, shlk bit will always be 0
 */
#define PWM_SHCR_SHLKEN_MASK (0x1U)
#define PWM_SHCR_SHLKEN_SHIFT (0U)
#define PWM_SHCR_SHLKEN_SET(x) (((uint32_t)(x) << PWM_SHCR_SHLKEN_SHIFT) & PWM_SHCR_SHLKEN_MASK)
#define PWM_SHCR_SHLKEN_GET(x) (((uint32_t)(x) & PWM_SHCR_SHLKEN_MASK) >> PWM_SHCR_SHLKEN_SHIFT)

/* Bitfield definition for register array: CAPPOS */
/*
 * CAPPOS (RO)
 *
 * counter value captured at input posedge
 */
#define PWM_CAPPOS_CAPPOS_MASK (0xFFFFFFF0UL)
#define PWM_CAPPOS_CAPPOS_SHIFT (4U)
#define PWM_CAPPOS_CAPPOS_GET(x) (((uint32_t)(x) & PWM_CAPPOS_CAPPOS_MASK) >> PWM_CAPPOS_CAPPOS_SHIFT)

/* Bitfield definition for register: CNT */
/*
 * XCNT (RO)
 *
 * current extended counter  value
 */
#define PWM_CNT_XCNT_MASK (0xF0000000UL)
#define PWM_CNT_XCNT_SHIFT (28U)
#define PWM_CNT_XCNT_GET(x) (((uint32_t)(x) & PWM_CNT_XCNT_MASK) >> PWM_CNT_XCNT_SHIFT)

/*
 * CNT (RO)
 *
 * current clock counter  value
 */
#define PWM_CNT_CNT_MASK (0xFFFFFF0UL)
#define PWM_CNT_CNT_SHIFT (4U)
#define PWM_CNT_CNT_GET(x) (((uint32_t)(x) & PWM_CNT_CNT_MASK) >> PWM_CNT_CNT_SHIFT)

/* Bitfield definition for register array: CAPNEG */
/*
 * CAPNEG (RO)
 *
 * counter value captured at input signal falling edge
 */
#define PWM_CAPNEG_CAPNEG_MASK (0xFFFFFFFFUL)
#define PWM_CAPNEG_CAPNEG_SHIFT (0U)
#define PWM_CAPNEG_CAPNEG_GET(x) (((uint32_t)(x) & PWM_CAPNEG_CAPNEG_MASK) >> PWM_CAPNEG_CAPNEG_SHIFT)

/* Bitfield definition for register: CNTCOPY */
/*
 * XCNT (RO)
 *
 * current extended counter  value
 */
#define PWM_CNTCOPY_XCNT_MASK (0xF0000000UL)
#define PWM_CNTCOPY_XCNT_SHIFT (28U)
#define PWM_CNTCOPY_XCNT_GET(x) (((uint32_t)(x) & PWM_CNTCOPY_XCNT_MASK) >> PWM_CNTCOPY_XCNT_SHIFT)

/*
 * CNT (RO)
 *
 * current clock counter  value
 */
#define PWM_CNTCOPY_CNT_MASK (0xFFFFFF0UL)
#define PWM_CNTCOPY_CNT_SHIFT (4U)
#define PWM_CNTCOPY_CNT_GET(x) (((uint32_t)(x) & PWM_CNTCOPY_CNT_MASK) >> PWM_CNTCOPY_CNT_SHIFT)

/* Bitfield definition for register array: PWMCFG */
/*
 * OEN (RW)
 *
 * PWM output enable
 * 1- output is enabled
 * 0- output is disabled
 */
#define PWM_PWMCFG_OEN_MASK (0x10000000UL)
#define PWM_PWMCFG_OEN_SHIFT (28U)
#define PWM_PWMCFG_OEN_SET(x) (((uint32_t)(x) << PWM_PWMCFG_OEN_SHIFT) & PWM_PWMCFG_OEN_MASK)
#define PWM_PWMCFG_OEN_GET(x) (((uint32_t)(x) & PWM_PWMCFG_OEN_MASK) >> PWM_PWMCFG_OEN_SHIFT)

/*
 * FRCSHDWUPT (RW)
 *
 * This bitfield select when the FRCMD shadow register will be loaded to its work register
 * 00:  after software set shlk bit of shlk register
 * 01:  immediately after the register being modified
 * 10:  after hardware event assert, user can select one of the comparators to generate this hardware event.
 *        The comparator can be either output compare mode or input capture mode.
 * 11:  after SHSYNCI assert
 */
#define PWM_PWMCFG_FRCSHDWUPT_MASK (0xC000000UL)
#define PWM_PWMCFG_FRCSHDWUPT_SHIFT (26U)
#define PWM_PWMCFG_FRCSHDWUPT_SET(x) (((uint32_t)(x) << PWM_PWMCFG_FRCSHDWUPT_SHIFT) & PWM_PWMCFG_FRCSHDWUPT_MASK)
#define PWM_PWMCFG_FRCSHDWUPT_GET(x) (((uint32_t)(x) & PWM_PWMCFG_FRCSHDWUPT_MASK) >> PWM_PWMCFG_FRCSHDWUPT_SHIFT)

/*
 * FAULTMODE (RW)
 *
 * This bitfield defines the PWM output status when fault condition happen
 * 00:  force output 0
 * 01:  force output 1
 * 1x:  output highz
 */
#define PWM_PWMCFG_FAULTMODE_MASK (0x3000000UL)
#define PWM_PWMCFG_FAULTMODE_SHIFT (24U)
#define PWM_PWMCFG_FAULTMODE_SET(x) (((uint32_t)(x) << PWM_PWMCFG_FAULTMODE_SHIFT) & PWM_PWMCFG_FAULTMODE_MASK)
#define PWM_PWMCFG_FAULTMODE_GET(x) (((uint32_t)(x) & PWM_PWMCFG_FAULTMODE_MASK) >> PWM_PWMCFG_FAULTMODE_SHIFT)

/*
 * FAULTRECTIME (RW)
 *
 * This bitfield select when to recover PWM output after fault condition removed.
 * 00:  immediately
 * 01:  after pwm timer counter reload time
 * 10:  after hardware event assert, user can select one of the comparators to generate this hardware event.
 *        The comparator can be either output compare mode or input capture mode.
 * 11:  after software write faultclr bit in GCR register
 */
#define PWM_PWMCFG_FAULTRECTIME_MASK (0xC00000UL)
#define PWM_PWMCFG_FAULTRECTIME_SHIFT (22U)
#define PWM_PWMCFG_FAULTRECTIME_SET(x) (((uint32_t)(x) << PWM_PWMCFG_FAULTRECTIME_SHIFT) & PWM_PWMCFG_FAULTRECTIME_MASK)
#define PWM_PWMCFG_FAULTRECTIME_GET(x) (((uint32_t)(x) & PWM_PWMCFG_FAULTRECTIME_MASK) >> PWM_PWMCFG_FAULTRECTIME_SHIFT)

/*
 * FRCSRCSEL (RW)
 *
 * Select sources for force output
 * 0- force output is enabled when FRCI assert
 * 1- force output is enabled by software write swfrc to 1
 */
#define PWM_PWMCFG_FRCSRCSEL_MASK (0x200000UL)
#define PWM_PWMCFG_FRCSRCSEL_SHIFT (21U)
#define PWM_PWMCFG_FRCSRCSEL_SET(x) (((uint32_t)(x) << PWM_PWMCFG_FRCSRCSEL_SHIFT) & PWM_PWMCFG_FRCSRCSEL_MASK)
#define PWM_PWMCFG_FRCSRCSEL_GET(x) (((uint32_t)(x) & PWM_PWMCFG_FRCSRCSEL_MASK) >> PWM_PWMCFG_FRCSRCSEL_SHIFT)

/*
 * PAIR (RW)
 *
 * 1- PWM output is in pair mode. Note the two PWM outputs need to be both set to pair mode.
 * 0- PWM output is in indepandent mode.
 */
#define PWM_PWMCFG_PAIR_MASK (0x100000UL)
#define PWM_PWMCFG_PAIR_SHIFT (20U)
#define PWM_PWMCFG_PAIR_SET(x) (((uint32_t)(x) << PWM_PWMCFG_PAIR_SHIFT) & PWM_PWMCFG_PAIR_MASK)
#define PWM_PWMCFG_PAIR_GET(x) (((uint32_t)(x) & PWM_PWMCFG_PAIR_MASK) >> PWM_PWMCFG_PAIR_SHIFT)

/*
 * DEADAREA (RW)
 *
 * This bitfield define the PWM pair deadarea length. The unit is 0.5 cycle. The minimum length of deadarea is 1 cycle.
 * Note: user should configure pair bit and this bitfield before PWM output is enabled.
 */
#define PWM_PWMCFG_DEADAREA_MASK (0xFFFFFUL)
#define PWM_PWMCFG_DEADAREA_SHIFT (0U)
#define PWM_PWMCFG_DEADAREA_SET(x) (((uint32_t)(x) << PWM_PWMCFG_DEADAREA_SHIFT) & PWM_PWMCFG_DEADAREA_MASK)
#define PWM_PWMCFG_DEADAREA_GET(x) (((uint32_t)(x) & PWM_PWMCFG_DEADAREA_MASK) >> PWM_PWMCFG_DEADAREA_SHIFT)

/* Bitfield definition for register: SR */
/*
 * FAULTF (W1C)
 *
 * fault condition flag
 */
#define PWM_SR_FAULTF_MASK (0x8000000UL)
#define PWM_SR_FAULTF_SHIFT (27U)
#define PWM_SR_FAULTF_SET(x) (((uint32_t)(x) << PWM_SR_FAULTF_SHIFT) & PWM_SR_FAULTF_MASK)
#define PWM_SR_FAULTF_GET(x) (((uint32_t)(x) & PWM_SR_FAULTF_MASK) >> PWM_SR_FAULTF_SHIFT)

/*
 * XRLDF (W1C)
 *
 * extended reload flag, this flag set when xcnt count to xrld value or when SYNCI assert
 */
#define PWM_SR_XRLDF_MASK (0x4000000UL)
#define PWM_SR_XRLDF_SHIFT (26U)
#define PWM_SR_XRLDF_SET(x) (((uint32_t)(x) << PWM_SR_XRLDF_SHIFT) & PWM_SR_XRLDF_MASK)
#define PWM_SR_XRLDF_GET(x) (((uint32_t)(x) & PWM_SR_XRLDF_MASK) >> PWM_SR_XRLDF_SHIFT)

/*
 * HALFRLDF (W1C)
 *
 * half reload flag, this flag set when cnt count to rld/2
 */
#define PWM_SR_HALFRLDF_MASK (0x2000000UL)
#define PWM_SR_HALFRLDF_SHIFT (25U)
#define PWM_SR_HALFRLDF_SET(x) (((uint32_t)(x) << PWM_SR_HALFRLDF_SHIFT) & PWM_SR_HALFRLDF_MASK)
#define PWM_SR_HALFRLDF_GET(x) (((uint32_t)(x) & PWM_SR_HALFRLDF_MASK) >> PWM_SR_HALFRLDF_SHIFT)

/*
 * RLDF (W1C)
 *
 * reload flag, this flag set when cnt count to rld value or when SYNCI assert
 */
#define PWM_SR_RLDF_MASK (0x1000000UL)
#define PWM_SR_RLDF_SHIFT (24U)
#define PWM_SR_RLDF_SET(x) (((uint32_t)(x) << PWM_SR_RLDF_SHIFT) & PWM_SR_RLDF_MASK)
#define PWM_SR_RLDF_GET(x) (((uint32_t)(x) & PWM_SR_RLDF_MASK) >> PWM_SR_RLDF_SHIFT)

/*
 * CMPFX (W1C)
 *
 * comparator output compare or input capture flag
 */
#define PWM_SR_CMPFX_MASK (0xFFFFFFUL)
#define PWM_SR_CMPFX_SHIFT (0U)
#define PWM_SR_CMPFX_SET(x) (((uint32_t)(x) << PWM_SR_CMPFX_SHIFT) & PWM_SR_CMPFX_MASK)
#define PWM_SR_CMPFX_GET(x) (((uint32_t)(x) & PWM_SR_CMPFX_MASK) >> PWM_SR_CMPFX_SHIFT)

/* Bitfield definition for register: IRQEN */
/*
 * FAULTIRQE (RW)
 *
 * fault condition interrupt enable
 */
#define PWM_IRQEN_FAULTIRQE_MASK (0x8000000UL)
#define PWM_IRQEN_FAULTIRQE_SHIFT (27U)
#define PWM_IRQEN_FAULTIRQE_SET(x) (((uint32_t)(x) << PWM_IRQEN_FAULTIRQE_SHIFT) & PWM_IRQEN_FAULTIRQE_MASK)
#define PWM_IRQEN_FAULTIRQE_GET(x) (((uint32_t)(x) & PWM_IRQEN_FAULTIRQE_MASK) >> PWM_IRQEN_FAULTIRQE_SHIFT)

/*
 * XRLDIRQE (RW)
 *
 * extended reload flag interrupt enable
 */
#define PWM_IRQEN_XRLDIRQE_MASK (0x4000000UL)
#define PWM_IRQEN_XRLDIRQE_SHIFT (26U)
#define PWM_IRQEN_XRLDIRQE_SET(x) (((uint32_t)(x) << PWM_IRQEN_XRLDIRQE_SHIFT) & PWM_IRQEN_XRLDIRQE_MASK)
#define PWM_IRQEN_XRLDIRQE_GET(x) (((uint32_t)(x) & PWM_IRQEN_XRLDIRQE_MASK) >> PWM_IRQEN_XRLDIRQE_SHIFT)

/*
 * HALFRLDIRQE (RW)
 *
 * half reload flag interrupt enable
 */
#define PWM_IRQEN_HALFRLDIRQE_MASK (0x2000000UL)
#define PWM_IRQEN_HALFRLDIRQE_SHIFT (25U)
#define PWM_IRQEN_HALFRLDIRQE_SET(x) (((uint32_t)(x) << PWM_IRQEN_HALFRLDIRQE_SHIFT) & PWM_IRQEN_HALFRLDIRQE_MASK)
#define PWM_IRQEN_HALFRLDIRQE_GET(x) (((uint32_t)(x) & PWM_IRQEN_HALFRLDIRQE_MASK) >> PWM_IRQEN_HALFRLDIRQE_SHIFT)

/*
 * RLDIRQE (RW)
 *
 * reload flag interrupt enable
 */
#define PWM_IRQEN_RLDIRQE_MASK (0x1000000UL)
#define PWM_IRQEN_RLDIRQE_SHIFT (24U)
#define PWM_IRQEN_RLDIRQE_SET(x) (((uint32_t)(x) << PWM_IRQEN_RLDIRQE_SHIFT) & PWM_IRQEN_RLDIRQE_MASK)
#define PWM_IRQEN_RLDIRQE_GET(x) (((uint32_t)(x) & PWM_IRQEN_RLDIRQE_MASK) >> PWM_IRQEN_RLDIRQE_SHIFT)

/*
 * CMPIRQEX (RW)
 *
 * comparator output compare or input capture flag interrupt enable
 */
#define PWM_IRQEN_CMPIRQEX_MASK (0xFFFFFFUL)
#define PWM_IRQEN_CMPIRQEX_SHIFT (0U)
#define PWM_IRQEN_CMPIRQEX_SET(x) (((uint32_t)(x) << PWM_IRQEN_CMPIRQEX_SHIFT) & PWM_IRQEN_CMPIRQEX_MASK)
#define PWM_IRQEN_CMPIRQEX_GET(x) (((uint32_t)(x) & PWM_IRQEN_CMPIRQEX_MASK) >> PWM_IRQEN_CMPIRQEX_SHIFT)

/* Bitfield definition for register: DMAEN */
/*
 * FAULTEN (RW)
 *
 * fault condition DMA request enable
 */
#define PWM_DMAEN_FAULTEN_MASK (0x8000000UL)
#define PWM_DMAEN_FAULTEN_SHIFT (27U)
#define PWM_DMAEN_FAULTEN_SET(x) (((uint32_t)(x) << PWM_DMAEN_FAULTEN_SHIFT) & PWM_DMAEN_FAULTEN_MASK)
#define PWM_DMAEN_FAULTEN_GET(x) (((uint32_t)(x) & PWM_DMAEN_FAULTEN_MASK) >> PWM_DMAEN_FAULTEN_SHIFT)

/*
 * XRLDEN (RW)
 *
 * extended reload flag DMA request enable
 */
#define PWM_DMAEN_XRLDEN_MASK (0x4000000UL)
#define PWM_DMAEN_XRLDEN_SHIFT (26U)
#define PWM_DMAEN_XRLDEN_SET(x) (((uint32_t)(x) << PWM_DMAEN_XRLDEN_SHIFT) & PWM_DMAEN_XRLDEN_MASK)
#define PWM_DMAEN_XRLDEN_GET(x) (((uint32_t)(x) & PWM_DMAEN_XRLDEN_MASK) >> PWM_DMAEN_XRLDEN_SHIFT)

/*
 * HALFRLDEN (RW)
 *
 * half reload flag DMA request enable
 */
#define PWM_DMAEN_HALFRLDEN_MASK (0x2000000UL)
#define PWM_DMAEN_HALFRLDEN_SHIFT (25U)
#define PWM_DMAEN_HALFRLDEN_SET(x) (((uint32_t)(x) << PWM_DMAEN_HALFRLDEN_SHIFT) & PWM_DMAEN_HALFRLDEN_MASK)
#define PWM_DMAEN_HALFRLDEN_GET(x) (((uint32_t)(x) & PWM_DMAEN_HALFRLDEN_MASK) >> PWM_DMAEN_HALFRLDEN_SHIFT)

/*
 * RLDEN (RW)
 *
 * reload flag DMA request enable
 */
#define PWM_DMAEN_RLDEN_MASK (0x1000000UL)
#define PWM_DMAEN_RLDEN_SHIFT (24U)
#define PWM_DMAEN_RLDEN_SET(x) (((uint32_t)(x) << PWM_DMAEN_RLDEN_SHIFT) & PWM_DMAEN_RLDEN_MASK)
#define PWM_DMAEN_RLDEN_GET(x) (((uint32_t)(x) & PWM_DMAEN_RLDEN_MASK) >> PWM_DMAEN_RLDEN_SHIFT)

/*
 * CMPENX (RW)
 *
 * comparator output compare or input capture flag DMA request enable
 */
#define PWM_DMAEN_CMPENX_MASK (0xFFFFFFUL)
#define PWM_DMAEN_CMPENX_SHIFT (0U)
#define PWM_DMAEN_CMPENX_SET(x) (((uint32_t)(x) << PWM_DMAEN_CMPENX_SHIFT) & PWM_DMAEN_CMPENX_MASK)
#define PWM_DMAEN_CMPENX_GET(x) (((uint32_t)(x) & PWM_DMAEN_CMPENX_MASK) >> PWM_DMAEN_CMPENX_SHIFT)

/* Bitfield definition for register array: CMPCFG */
/*
 * XCNTCMPEN (RW)
 *
 * This bitfield enable the comparator to compare xcmp with xcnt.
 */
#define PWM_CMPCFG_XCNTCMPEN_MASK (0xF0U)
#define PWM_CMPCFG_XCNTCMPEN_SHIFT (4U)
#define PWM_CMPCFG_XCNTCMPEN_SET(x) (((uint32_t)(x) << PWM_CMPCFG_XCNTCMPEN_SHIFT) & PWM_CMPCFG_XCNTCMPEN_MASK)
#define PWM_CMPCFG_XCNTCMPEN_GET(x) (((uint32_t)(x) & PWM_CMPCFG_XCNTCMPEN_MASK) >> PWM_CMPCFG_XCNTCMPEN_SHIFT)

/*
 * CMPSHDWUPT (RW)
 *
 * This bitfield select when the comparator shadow register will be loaded to its work register
 * 00:  after software set shlk bit of shlk register
 * 01:  immediately after the register being modified
 * 10:  after hardware event assert, user can select one of the comparators to generate this hardware event.
 *        The comparator can be either output compare mode or input capture mode.
 * 11:  after SHSYNCI assert
 */
#define PWM_CMPCFG_CMPSHDWUPT_MASK (0xCU)
#define PWM_CMPCFG_CMPSHDWUPT_SHIFT (2U)
#define PWM_CMPCFG_CMPSHDWUPT_SET(x) (((uint32_t)(x) << PWM_CMPCFG_CMPSHDWUPT_SHIFT) & PWM_CMPCFG_CMPSHDWUPT_MASK)
#define PWM_CMPCFG_CMPSHDWUPT_GET(x) (((uint32_t)(x) & PWM_CMPCFG_CMPSHDWUPT_MASK) >> PWM_CMPCFG_CMPSHDWUPT_SHIFT)

/*
 * CMPMODE (RW)
 *
 * comparator mode
 * 0- output compare mode
 * 1- input capture mode
 */
#define PWM_CMPCFG_CMPMODE_MASK (0x2U)
#define PWM_CMPCFG_CMPMODE_SHIFT (1U)
#define PWM_CMPCFG_CMPMODE_SET(x) (((uint32_t)(x) << PWM_CMPCFG_CMPMODE_SHIFT) & PWM_CMPCFG_CMPMODE_MASK)
#define PWM_CMPCFG_CMPMODE_GET(x) (((uint32_t)(x) & PWM_CMPCFG_CMPMODE_MASK) >> PWM_CMPCFG_CMPMODE_SHIFT)



/* CMP register group index macro definition */
#define PWM_CMP_0 (0UL)
#define PWM_CMP_1 (1UL)
#define PWM_CMP_2 (2UL)
#define PWM_CMP_3 (3UL)
#define PWM_CMP_4 (4UL)
#define PWM_CMP_5 (5UL)
#define PWM_CMP_6 (6UL)
#define PWM_CMP_7 (7UL)
#define PWM_CMP_8 (8UL)
#define PWM_CMP_9 (9UL)
#define PWM_CMP_10 (10UL)
#define PWM_CMP_11 (11UL)
#define PWM_CMP_12 (12UL)
#define PWM_CMP_13 (13UL)
#define PWM_CMP_14 (14UL)
#define PWM_CMP_15 (15UL)
#define PWM_CMP_16 (16UL)
#define PWM_CMP_17 (17UL)
#define PWM_CMP_18 (18UL)
#define PWM_CMP_19 (19UL)
#define PWM_CMP_20 (20UL)
#define PWM_CMP_21 (21UL)
#define PWM_CMP_22 (22UL)
#define PWM_CMP_23 (23UL)

/* CHCFG register group index macro definition */
#define PWM_CHCFG_0 (0UL)
#define PWM_CHCFG_1 (1UL)
#define PWM_CHCFG_2 (2UL)
#define PWM_CHCFG_3 (3UL)
#define PWM_CHCFG_4 (4UL)
#define PWM_CHCFG_5 (5UL)
#define PWM_CHCFG_6 (6UL)
#define PWM_CHCFG_7 (7UL)
#define PWM_CHCFG_8 (8UL)
#define PWM_CHCFG_9 (9UL)
#define PWM_CHCFG_10 (10UL)
#define PWM_CHCFG_11 (11UL)
#define PWM_CHCFG_12 (12UL)
#define PWM_CHCFG_13 (13UL)
#define PWM_CHCFG_14 (14UL)
#define PWM_CHCFG_15 (15UL)
#define PWM_CHCFG_16 (16UL)
#define PWM_CHCFG_17 (17UL)
#define PWM_CHCFG_18 (18UL)
#define PWM_CHCFG_19 (19UL)
#define PWM_CHCFG_20 (20UL)
#define PWM_CHCFG_21 (21UL)
#define PWM_CHCFG_22 (22UL)
#define PWM_CHCFG_23 (23UL)

/* CAPPOS register group index macro definition */
#define PWM_CAPPOS_0 (0UL)
#define PWM_CAPPOS_1 (1UL)
#define PWM_CAPPOS_2 (2UL)
#define PWM_CAPPOS_3 (3UL)
#define PWM_CAPPOS_4 (4UL)
#define PWM_CAPPOS_5 (5UL)
#define PWM_CAPPOS_6 (6UL)
#define PWM_CAPPOS_7 (7UL)
#define PWM_CAPPOS_8 (8UL)
#define PWM_CAPPOS_9 (9UL)
#define PWM_CAPPOS_10 (10UL)
#define PWM_CAPPOS_11 (11UL)
#define PWM_CAPPOS_12 (12UL)
#define PWM_CAPPOS_13 (13UL)
#define PWM_CAPPOS_14 (14UL)
#define PWM_CAPPOS_15 (15UL)
#define PWM_CAPPOS_16 (16UL)
#define PWM_CAPPOS_17 (17UL)
#define PWM_CAPPOS_18 (18UL)
#define PWM_CAPPOS_19 (19UL)
#define PWM_CAPPOS_20 (20UL)
#define PWM_CAPPOS_21 (21UL)
#define PWM_CAPPOS_22 (22UL)
#define PWM_CAPPOS_23 (23UL)

/* CAPNEG register group index macro definition */
#define PWM_CAPNEG_0 (0UL)
#define PWM_CAPNEG_1 (1UL)
#define PWM_CAPNEG_2 (2UL)
#define PWM_CAPNEG_3 (3UL)
#define PWM_CAPNEG_4 (4UL)
#define PWM_CAPNEG_5 (5UL)
#define PWM_CAPNEG_6 (6UL)
#define PWM_CAPNEG_7 (7UL)
#define PWM_CAPNEG_8 (8UL)
#define PWM_CAPNEG_9 (9UL)
#define PWM_CAPNEG_10 (10UL)
#define PWM_CAPNEG_11 (11UL)
#define PWM_CAPNEG_12 (12UL)
#define PWM_CAPNEG_13 (13UL)
#define PWM_CAPNEG_14 (14UL)
#define PWM_CAPNEG_15 (15UL)
#define PWM_CAPNEG_16 (16UL)
#define PWM_CAPNEG_17 (17UL)
#define PWM_CAPNEG_18 (18UL)
#define PWM_CAPNEG_19 (19UL)
#define PWM_CAPNEG_20 (20UL)
#define PWM_CAPNEG_21 (21UL)
#define PWM_CAPNEG_22 (22UL)
#define PWM_CAPNEG_23 (23UL)

/* PWMCFG register group index macro definition */
#define PWM_PWMCFG_0 (0UL)
#define PWM_PWMCFG_1 (1UL)
#define PWM_PWMCFG_2 (2UL)
#define PWM_PWMCFG_3 (3UL)
#define PWM_PWMCFG_4 (4UL)
#define PWM_PWMCFG_5 (5UL)
#define PWM_PWMCFG_6 (6UL)
#define PWM_PWMCFG_7 (7UL)

/* CMPCFG register group index macro definition */
#define PWM_CMPCFG_CMPCFG0 (0UL)
#define PWM_CMPCFG_1 (1UL)
#define PWM_CMPCFG_2 (2UL)
#define PWM_CMPCFG_3 (3UL)
#define PWM_CMPCFG_4 (4UL)
#define PWM_CMPCFG_5 (5UL)
#define PWM_CMPCFG_6 (6UL)
#define PWM_CMPCFG_7 (7UL)
#define PWM_CMPCFG_8 (8UL)
#define PWM_CMPCFG_9 (9UL)
#define PWM_CMPCFG_10 (10UL)
#define PWM_CMPCFG_11 (11UL)
#define PWM_CMPCFG_12 (12UL)
#define PWM_CMPCFG_13 (13UL)
#define PWM_CMPCFG_14 (14UL)
#define PWM_CMPCFG_15 (15UL)
#define PWM_CMPCFG_16 (16UL)
#define PWM_CMPCFG_17 (17UL)
#define PWM_CMPCFG_18 (18UL)
#define PWM_CMPCFG_19 (19UL)
#define PWM_CMPCFG_20 (20UL)
#define PWM_CMPCFG_21 (21UL)
#define PWM_CMPCFG_22 (22UL)
#define PWM_CMPCFG_23 (23UL)


#endif /* HPM_PWM_H */
