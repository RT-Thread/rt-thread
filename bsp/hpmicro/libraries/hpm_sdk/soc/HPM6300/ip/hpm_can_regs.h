/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_CAN_H
#define HPM_CAN_H

typedef struct {
    __RW uint32_t RBUF[20];                    /* 0x0 - 0x4C: receive buffer registers and reception time stamp */
    __RW uint32_t TBUF[18];                    /* 0x50 - 0x94: transmit buffer register */
    __R  uint32_t TTS[2];                      /* 0x98 - 0x9C: transmission time stamp, LSB 32bit */
    __RW uint32_t CMD_STA_CMD_CTRL;            /* 0xA0: config, status, command and control bits */
    __RW uint8_t  RTIE;                        /* 0xA4: Receive and Transmit Interrupt Enable Register RTIE */
    __W  uint8_t  RTIF;                        /* 0xA5: Receive and Transmit Interrupt Flag Register RTIF (0xa5) */
    __RW uint8_t  ERRINT;                      /* 0xA6: ERRor INTerrupt Enable and Flag Register ERRINT */
    __RW uint8_t  LIMIT;                       /* 0xA7: Warning Limits Register LIMIT */
    __RW uint32_t S_PRESC;                     /* 0xA8: Bit Timing Register(Slow Speed) */
    __RW uint32_t F_PRESC;                     /* 0xAC: Bit Timing Register(Fast Speed) */
    __R  uint8_t  EALCAP;                      /* 0xB0: Error and Arbitration Lost Capture Register EALCAP */
    __RW uint8_t  TDC;                         /* 0xB1: Transmitter Delay Compensation Register TDC */
    __R  uint8_t  RECNT;                       /* 0xB2: Error Counter Registers RECNT */
    __R  uint8_t  TECNT;                       /* 0xB3: Error Counter Registers TECNT */
    __RW uint8_t  ACFCTRL;                     /* 0xB4: Acceptance Filter Control Register ACFCTRL */
    __RW uint8_t  TIMECFG;                     /* 0xB5: CiA 603 Time-Stamping TIMECFG */
    __RW uint16_t ACF_EN;                      /* 0xB6: Acceptance Filter Enable ACF_EN */
    __RW uint32_t ACF;                         /* 0xB8: Acceptance CODE ACODE or ACMASK */
    __RW uint16_t VER;                         /* 0xBC: Version Information VER */
    __RW uint8_t  TBSLOT;                      /* 0xBE: TTCAN: TB Slot Pointer TBSLOT */
    __RW uint8_t  TTCFG;                       /* 0xBF: TTCAN: Time Trigger Configuration TTCFG */
    __RW uint32_t REF_MSG;                     /* 0xC0: TTCAN: Reference Message REF_MSG */
    __RW uint16_t TRIG_CFG;                    /* 0xC4: TTCAN: Trigger Configuration TRIG_CFG */
    __RW uint16_t TT_TRIG;                     /* 0xC6: TTCAN: Trigger Time TT_TRIG */
    __RW uint16_t TT_WTRIG;                    /* 0xC8: TTCAN: Watch Trigger Time TT_WTRIG */
} CAN_Type;


/* Bitfield definition for register array: RBUF */
/*
 * RBUF (RW)
 *
 * receive buffer
 */
#define CAN_RBUF_RBUF_MASK (0xFFFFFFFFUL)
#define CAN_RBUF_RBUF_SHIFT (0U)
#define CAN_RBUF_RBUF_SET(x) (((uint32_t)(x) << CAN_RBUF_RBUF_SHIFT) & CAN_RBUF_RBUF_MASK)
#define CAN_RBUF_RBUF_GET(x) (((uint32_t)(x) & CAN_RBUF_RBUF_MASK) >> CAN_RBUF_RBUF_SHIFT)

/* Bitfield definition for register array: TBUF */
/*
 * TBUF (RW)
 *
 * transmit buffer
 */
#define CAN_TBUF_TBUF_MASK (0xFFFFFFFFUL)
#define CAN_TBUF_TBUF_SHIFT (0U)
#define CAN_TBUF_TBUF_SET(x) (((uint32_t)(x) << CAN_TBUF_TBUF_SHIFT) & CAN_TBUF_TBUF_MASK)
#define CAN_TBUF_TBUF_GET(x) (((uint32_t)(x) & CAN_TBUF_TBUF_MASK) >> CAN_TBUF_TBUF_SHIFT)

/* Bitfield definition for register array: TTS */
/*
 * TTS_WRD0 (RO)
 *
 * transmission time stamp, word 0, LSB 32bit
 */
#define CAN_TTS_TTS_WRD0_MASK (0xFFFFFFFFUL)
#define CAN_TTS_TTS_WRD0_SHIFT (0U)
#define CAN_TTS_TTS_WRD0_GET(x) (((uint32_t)(x) & CAN_TTS_TTS_WRD0_MASK) >> CAN_TTS_TTS_WRD0_SHIFT)

/* Bitfield definition for register: CMD_STA_CMD_CTRL */
/*
 * SACK (RW)
 *
 * Self-ACKnowledge
 * 0 – no self-ACK
 * 1 – self-ACK when LBME=1
 */
#define CAN_CMD_STA_CMD_CTRL_SACK_MASK (0x80000000UL)
#define CAN_CMD_STA_CMD_CTRL_SACK_SHIFT (31U)
#define CAN_CMD_STA_CMD_CTRL_SACK_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_SACK_SHIFT) & CAN_CMD_STA_CMD_CTRL_SACK_MASK)
#define CAN_CMD_STA_CMD_CTRL_SACK_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_SACK_MASK) >> CAN_CMD_STA_CMD_CTRL_SACK_SHIFT)

/*
 * ROM (RW)
 *
 * Receive buffer Overflow Mode
 * In case of a full RBUF when a new message is received, then ROM selects the following:
 * 1 – The new message will not be stored.
 * 0 – The oldest message will be overwritten.
 */
#define CAN_CMD_STA_CMD_CTRL_ROM_MASK (0x40000000UL)
#define CAN_CMD_STA_CMD_CTRL_ROM_SHIFT (30U)
#define CAN_CMD_STA_CMD_CTRL_ROM_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_ROM_SHIFT) & CAN_CMD_STA_CMD_CTRL_ROM_MASK)
#define CAN_CMD_STA_CMD_CTRL_ROM_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_ROM_MASK) >> CAN_CMD_STA_CMD_CTRL_ROM_SHIFT)

/*
 * ROV (RO)
 *
 * Receive buffer OVerflow
 * 1 – Overflow. At least one message is lost.
 * 0 – No Overflow.
 * ROV is cleared by setting RREL=1.
 */
#define CAN_CMD_STA_CMD_CTRL_ROV_MASK (0x20000000UL)
#define CAN_CMD_STA_CMD_CTRL_ROV_SHIFT (29U)
#define CAN_CMD_STA_CMD_CTRL_ROV_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_ROV_MASK) >> CAN_CMD_STA_CMD_CTRL_ROV_SHIFT)

/*
 * RREL (RW)
 *
 * Receive buffer RELease
 * The host controller has read the actual RB slot and releases it. Afterwards the CAN-CTRL
 * core points to the next RB slot. RSTAT gets updated.
 * 1 – Release: The host has read the RB.
 * 0 – No release
 */
#define CAN_CMD_STA_CMD_CTRL_RREL_MASK (0x10000000UL)
#define CAN_CMD_STA_CMD_CTRL_RREL_SHIFT (28U)
#define CAN_CMD_STA_CMD_CTRL_RREL_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_RREL_SHIFT) & CAN_CMD_STA_CMD_CTRL_RREL_MASK)
#define CAN_CMD_STA_CMD_CTRL_RREL_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_RREL_MASK) >> CAN_CMD_STA_CMD_CTRL_RREL_SHIFT)

/*
 * RBALL (RW)
 *
 * Receive Buffer stores ALL data frames
 * 0 – normal operation
 * 1 – RB stores correct data frames as well as data frames with error
 */
#define CAN_CMD_STA_CMD_CTRL_RBALL_MASK (0x8000000UL)
#define CAN_CMD_STA_CMD_CTRL_RBALL_SHIFT (27U)
#define CAN_CMD_STA_CMD_CTRL_RBALL_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_RBALL_SHIFT) & CAN_CMD_STA_CMD_CTRL_RBALL_MASK)
#define CAN_CMD_STA_CMD_CTRL_RBALL_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_RBALL_MASK) >> CAN_CMD_STA_CMD_CTRL_RBALL_SHIFT)

/*
 * RSTAT (RO)
 *
 * Receive buffer STATus
 * 00 - empty
 * 01 - > empty and < almost full (AFWL)
 * 10 -  almost full (programmable threshold by AFWL) but not full and no overflow
 * 11 - full (stays set in case of overflow – for overflow signaling see ROV)
 */
#define CAN_CMD_STA_CMD_CTRL_RSTAT_MASK (0x3000000UL)
#define CAN_CMD_STA_CMD_CTRL_RSTAT_SHIFT (24U)
#define CAN_CMD_STA_CMD_CTRL_RSTAT_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_RSTAT_MASK) >> CAN_CMD_STA_CMD_CTRL_RSTAT_SHIFT)

/*
 * FD_ISO (RW)
 *
 * CAN FD ISO mode
 * 0 - Bosch CAN FD (non-ISO) mode
 * 1 - ISO CAN FD mode (ISO 11898-1:2015)
 * ISO CAN FD mode has a different CRC initialization value and an additional stuff bit count.
 * Both modes are incompatible and must not be mixed in one CAN network.
 * This bit has no impact to CAN 2.0B.
 * This bit is only writeable if RESET=1.
 */
#define CAN_CMD_STA_CMD_CTRL_FD_ISO_MASK (0x800000UL)
#define CAN_CMD_STA_CMD_CTRL_FD_ISO_SHIFT (23U)
#define CAN_CMD_STA_CMD_CTRL_FD_ISO_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_FD_ISO_SHIFT) & CAN_CMD_STA_CMD_CTRL_FD_ISO_MASK)
#define CAN_CMD_STA_CMD_CTRL_FD_ISO_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_FD_ISO_MASK) >> CAN_CMD_STA_CMD_CTRL_FD_ISO_SHIFT)

/*
 * TSNEXT (RW)
 *
 * Transmit buffer Secondary NEXT
 * 0 - no action
 * 1 - STB slot filled, select next slot.
 * After all frame bytes are written to the TBUF registers, the host controller has to set
 * TSNEXT to signal that this slot has been filled. Then the CAN-CTRL core connects the TBUF
 * registers to the next slot. Once a slot is marked as filled a transmission can be started
 * using TSONE or TSALL.
 * It is possible to set TSNEXT and TSONE or TSALL together in one write access.
 * TSNEXT has to be set by the host controller and is automatically reset by the CAN-CTRL
 * core immediately after it was set.
 * Setting TSNEXT is meaningless if TBSEL=0. In this case TSNEXT is ignored and
 * automatically cleared. It does not do any harm.
 * If all slots of the STB are filled, TSNEXT stays set until a slot becomes free.
 * TSNEXT has no meaning in TTCAN mode and is fixed to 0.
 */
#define CAN_CMD_STA_CMD_CTRL_TSNEXT_MASK (0x400000UL)
#define CAN_CMD_STA_CMD_CTRL_TSNEXT_SHIFT (22U)
#define CAN_CMD_STA_CMD_CTRL_TSNEXT_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_TSNEXT_SHIFT) & CAN_CMD_STA_CMD_CTRL_TSNEXT_MASK)
#define CAN_CMD_STA_CMD_CTRL_TSNEXT_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_TSNEXT_MASK) >> CAN_CMD_STA_CMD_CTRL_TSNEXT_SHIFT)

/*
 * TSMODE (RW)
 *
 * Transmit buffer Secondary operation MODE
 * 0 - FIFO mode
 * 1 - priority decision mode
 * In FIFO mode frames are transmitted in the order in that they are written into the STB.
 * In priority decision mode the frame with the highest priority in the STB is automatically
 * transmitted first. The ID of a frame is used for the priority decision. A lower ID means a
 * higher priority of a frame. A frame in the PTB has always the highest priority regardless of
 * the ID.
 * TSMODE shall be switched only if the STB if empty
 */
#define CAN_CMD_STA_CMD_CTRL_TSMODE_MASK (0x200000UL)
#define CAN_CMD_STA_CMD_CTRL_TSMODE_SHIFT (21U)
#define CAN_CMD_STA_CMD_CTRL_TSMODE_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_TSMODE_SHIFT) & CAN_CMD_STA_CMD_CTRL_TSMODE_MASK)
#define CAN_CMD_STA_CMD_CTRL_TSMODE_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_TSMODE_MASK) >> CAN_CMD_STA_CMD_CTRL_TSMODE_SHIFT)

/*
 * TTTBM (RW)
 *
 * TTCAN Transmit Buffer Mode
 * If TTEN=0 then TTTBM is ignored, otherwise the following is valid:
 * 0 - separate PTB and STB, behavior defined by TSMODE
 * 1 - full TTCAN support: buffer slots selectable by TBPTR and TTPTR
 * For event-driven CAN communication (TTEN=0), the system provides PTB and STB and
 * the behavior of the STB is defined by TSMODE. Then TTTBM is ignored.
 * For time-triggered CAN communication (TTEN=1) with full support of all features including
 * time-triggered transmissions, TTTBM=1 needs to be chosen. Then the all TB slots are
 * addressable using TTPTR and TBPTR.
 * For time-triggered CAN communication (TTEN=1) with only support of reception timestamps, TTTBM=0 can be chosen. Then the transmit buffer acts as in event-driven mode
 * and the behavior can be selected by TSMODE.
 * TTTBM shall be switched only if the TBUF is empty.
 */
#define CAN_CMD_STA_CMD_CTRL_TTTBM_MASK (0x100000UL)
#define CAN_CMD_STA_CMD_CTRL_TTTBM_SHIFT (20U)
#define CAN_CMD_STA_CMD_CTRL_TTTBM_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_TTTBM_SHIFT) & CAN_CMD_STA_CMD_CTRL_TTTBM_MASK)
#define CAN_CMD_STA_CMD_CTRL_TTTBM_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_TTTBM_MASK) >> CAN_CMD_STA_CMD_CTRL_TTTBM_SHIFT)

/*
 * TSSTAT (RO)
 *
 * Transmission Secondary STATus bits
 * If TTEN=0 or TTTBM=0:
 * 00 – STB is empty
 * 01 – STB is less than or equal to half full
 * 10 – STB is more than half full
 * 11 – STB is full
 * If the STB is disabled using STB_DISABLE, then TSSTAT=00.
 * If TTEN=1 and TTTBM=1:
 * 00 – PTB and STB are empty
 * 01 – PTB and STB are not empty and not full
 * 11 – PTB and STB are full
 */
#define CAN_CMD_STA_CMD_CTRL_TSSTAT_MASK (0x30000UL)
#define CAN_CMD_STA_CMD_CTRL_TSSTAT_SHIFT (16U)
#define CAN_CMD_STA_CMD_CTRL_TSSTAT_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_TSSTAT_MASK) >> CAN_CMD_STA_CMD_CTRL_TSSTAT_SHIFT)

/*
 * TBSEL (RW)
 *
 * Transmit Buffer Select
 * Selects the transmit buffer to be loaded with a message. Use the TBUF registers for
 * access. TBSEL needs to be stable all the time the TBUF registers are written and when
 * TSNEXT is set.
 * 0 - PTB (high-priority buffer)
 * 1 - STB
 * The bit will be reset to the hardware reset value if (TTEN=1 and TTTBM=1)
 */
#define CAN_CMD_STA_CMD_CTRL_TBSEL_MASK (0x8000U)
#define CAN_CMD_STA_CMD_CTRL_TBSEL_SHIFT (15U)
#define CAN_CMD_STA_CMD_CTRL_TBSEL_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_TBSEL_SHIFT) & CAN_CMD_STA_CMD_CTRL_TBSEL_MASK)
#define CAN_CMD_STA_CMD_CTRL_TBSEL_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_TBSEL_MASK) >> CAN_CMD_STA_CMD_CTRL_TBSEL_SHIFT)

/*
 * LOM (RW)
 *
 * Listen Only Mode
 * 0 - Disabled
 * 1 - Enabled
 * LOM cannot be set if TPE, TSONE or TSALL is set. No transmission can be started if LOM
 * is enabled and LBME is disabled.
 * LOM=1 and LBME=0 disables all transmissions.
 * LOM=1 and LBME=1 disables the ACK for received frames and error frames, but enables
 * the transmission of own frames.
 */
#define CAN_CMD_STA_CMD_CTRL_LOM_MASK (0x4000U)
#define CAN_CMD_STA_CMD_CTRL_LOM_SHIFT (14U)
#define CAN_CMD_STA_CMD_CTRL_LOM_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_LOM_SHIFT) & CAN_CMD_STA_CMD_CTRL_LOM_MASK)
#define CAN_CMD_STA_CMD_CTRL_LOM_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_LOM_MASK) >> CAN_CMD_STA_CMD_CTRL_LOM_SHIFT)

/*
 * STBY (RW)
 *
 * Transceiver Standby Mode
 * 0 - Disabled
 * 1 - Enabled
 * This register bit is connected to the output signal stby which can be used to control a
 * standby mode of a transceiver.
 * STBY cannot be set to 1 if TPE=1, TSONE=1 or TSALL=1.
 * If the host sets STBY to 0 then the host needs to wait for the time required by the
 * transceiver to start up before the host requests a new transmission.
 */
#define CAN_CMD_STA_CMD_CTRL_STBY_MASK (0x2000U)
#define CAN_CMD_STA_CMD_CTRL_STBY_SHIFT (13U)
#define CAN_CMD_STA_CMD_CTRL_STBY_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_STBY_SHIFT) & CAN_CMD_STA_CMD_CTRL_STBY_MASK)
#define CAN_CMD_STA_CMD_CTRL_STBY_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_STBY_MASK) >> CAN_CMD_STA_CMD_CTRL_STBY_SHIFT)

/*
 * TPE (RW)
 *
 * Transmit Primary Enable
 * 1 - Transmission enable for the message in the high-priority PTB
 * 0 - No transmission for the PTB
 * If TPE is set, the message from the PTB will be transmitted at the next possible transmit
 * position. A started transmission from the STB will be completed before, but pending new
 * messages are delayed until the PTB message has been transmitted.
 * TPE stays set until the message has been transmitted successfully or it is aborted using
 * TPA.
 * The host controller can set TPE to 1 but can not reset it to 0. This would only be possible
 * using TPA and aborting the message.
 * The bit will be reset to the hardware reset value if RESET=1, STBY=1, (LOM=1 and
 * LBME=0) or (TTEN=1 and TTTBM=1).
 */
#define CAN_CMD_STA_CMD_CTRL_TPE_MASK (0x1000U)
#define CAN_CMD_STA_CMD_CTRL_TPE_SHIFT (12U)
#define CAN_CMD_STA_CMD_CTRL_TPE_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_TPE_SHIFT) & CAN_CMD_STA_CMD_CTRL_TPE_MASK)
#define CAN_CMD_STA_CMD_CTRL_TPE_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_TPE_MASK) >> CAN_CMD_STA_CMD_CTRL_TPE_SHIFT)

/*
 * TPA (RW)
 *
 * Transmit Primary Abort
 * 1 – Aborts a transmission from PTB which has been requested by TPE=1 but not
 * started yet. (The data bytes of the message remains in the PTB.)
 * 0 – no abort
 * The bit has to be set by the host controller and will be reset by CAN-CTRL. Setting TPA
 * automatically de-asserts TPE.
 * The host controller can set TPA to 1 but can not reset it to 0.
 * During the short time while the CAN-CTRL core resets the bit, it cannot be set by the
 * host.
 * The bit will be reset to the hardware reset value if RESET=1 or (TTEN=1 and TTTBM=1).
 * TPA should not be set simultaneously with TPE.
 */
#define CAN_CMD_STA_CMD_CTRL_TPA_MASK (0x800U)
#define CAN_CMD_STA_CMD_CTRL_TPA_SHIFT (11U)
#define CAN_CMD_STA_CMD_CTRL_TPA_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_TPA_SHIFT) & CAN_CMD_STA_CMD_CTRL_TPA_MASK)
#define CAN_CMD_STA_CMD_CTRL_TPA_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_TPA_MASK) >> CAN_CMD_STA_CMD_CTRL_TPA_SHIFT)

/*
 * TSONE (RW)
 *
 * Transmit Secondary ONE frame
 * 1 – Transmission enable of one in the STB. In FIFO mode this is the oldest message
 * and in priority mode this is the one with the highest priority.
 * TSONE in priority mode is difficult to handle, because it is not always clear which
 * message will be transmitted if new messages are written to the STB meanwhile.
 * The controller starts the transmission as soon as the bus becomes vacant and
 * no request of the PTB (bit TPE) is pending.
 * 0 – No transmission for the STB.
 * TSONE stays set until the message has been transmitted successfully or it is aborted
 * using TSA.
 * The host controller can set TSONE to 1 but can not reset it to 0. This would only be
 * possible using TSA and aborting the message.
 * The bit will be reset to the hardware reset value if RESET=1, STBY=1, (LOM=1 and
 * LBME=0) or (TTEN=1 and TTTBM=1).
 */
#define CAN_CMD_STA_CMD_CTRL_TSONE_MASK (0x400U)
#define CAN_CMD_STA_CMD_CTRL_TSONE_SHIFT (10U)
#define CAN_CMD_STA_CMD_CTRL_TSONE_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_TSONE_SHIFT) & CAN_CMD_STA_CMD_CTRL_TSONE_MASK)
#define CAN_CMD_STA_CMD_CTRL_TSONE_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_TSONE_MASK) >> CAN_CMD_STA_CMD_CTRL_TSONE_SHIFT)

/*
 * TSALL (RW)
 *
 * Transmit Secondary ALL frames
 * 1 – Transmission enable of all messages in the STB.
 * The controller starts the transmission as soon as the bus becomes vacant and
 * no request of the PTB (bit TPE) is pending.
 * 0 – No transmission for the STB.
 * TSALL stays set until all messages have been transmitted successfully or they are aborted
 * using TSA.
 * The host controller can set TSALL to 1 but can not reset it to 0. This would only be
 * possible using TSA and aborting the messages.
 * The bit will be reset to the hardware reset value if RESET=1, STBY=1, (LOM=1 and
 * LBME=0) or (TTEN=1 and TTTBM=1).
 * If during a transmission the STB is loaded with a new frame then the new frame will be
 * transmitted too. In other words: a transmission initiated by TSALL is finished when the
 * STB becomes empty.
 */
#define CAN_CMD_STA_CMD_CTRL_TSALL_MASK (0x200U)
#define CAN_CMD_STA_CMD_CTRL_TSALL_SHIFT (9U)
#define CAN_CMD_STA_CMD_CTRL_TSALL_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_TSALL_SHIFT) & CAN_CMD_STA_CMD_CTRL_TSALL_MASK)
#define CAN_CMD_STA_CMD_CTRL_TSALL_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_TSALL_MASK) >> CAN_CMD_STA_CMD_CTRL_TSALL_SHIFT)

/*
 * TSA (RW)
 *
 * Transmit Secondary Abort
 * 1 – Aborts a transmission from STB which has been requested but not started yet.
 * For a TSONE transmission, only one frame is aborted while for a TSALL
 * Transmission, all frames are aborted.
 * One or all message slots will be released which updates TSSTAT.
 * All aborted messages are lost because they are not accessible any more.
 * If in priority mode a TSONE transmission is aborted, then it is not clear which
 * frame will be aborted if new frames are written to the STB meanwhile.
 * 0 – no abort
 * The bit has to be set by the host controller and will be reset by CAN-CTRL. Setting TSA,automatically de-asserts TSONE or TSALL respectively.
 * The host controller can set TSA to 1 but can not reset it to 0.
 * The bit will be reset to the hardware reset value if RESET=1.
 * TSA should not be set simultaneously with TSONE or TSALL.
 */
#define CAN_CMD_STA_CMD_CTRL_TSA_MASK (0x100U)
#define CAN_CMD_STA_CMD_CTRL_TSA_SHIFT (8U)
#define CAN_CMD_STA_CMD_CTRL_TSA_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_TSA_SHIFT) & CAN_CMD_STA_CMD_CTRL_TSA_MASK)
#define CAN_CMD_STA_CMD_CTRL_TSA_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_TSA_MASK) >> CAN_CMD_STA_CMD_CTRL_TSA_SHIFT)

/*
 * RESET (RW)
 *
 * RESET request bit
 * 1 - The host controller performs a local reset of CAN-CTRL.
 * 0 - no local reset of CAN-CTRLThe some register (e.g for node configuration) can only be modified if RESET=1.
 * Bit RESET forces several components to a reset state.
 * RESET is automatically set if the node enters “bus off” state.
 * Note that a CAN node will participate in CAN communication after RESET is switched to 0after 11 CAN bit times.
 * This delay is required by the CAN standard (bus idle time).If RESET is set to 1 and immediately set to 0, then it takes some time until RESET can beread as 0 and becomes inactive.
 * The reason is clock domain crossing from host to CAN clockdomain. RESET is held active as long as needed depending on the relation between host andCAN clock.
 */
#define CAN_CMD_STA_CMD_CTRL_RESET_MASK (0x80U)
#define CAN_CMD_STA_CMD_CTRL_RESET_SHIFT (7U)
#define CAN_CMD_STA_CMD_CTRL_RESET_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_RESET_SHIFT) & CAN_CMD_STA_CMD_CTRL_RESET_MASK)
#define CAN_CMD_STA_CMD_CTRL_RESET_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_RESET_MASK) >> CAN_CMD_STA_CMD_CTRL_RESET_SHIFT)

/*
 * LBME (RW)
 *
 * Loop Back Mode, External
 * 0 - Disabled
 * 1 - EnabledLBME should not be enabled while a transmission is active
 */
#define CAN_CMD_STA_CMD_CTRL_LBME_MASK (0x40U)
#define CAN_CMD_STA_CMD_CTRL_LBME_SHIFT (6U)
#define CAN_CMD_STA_CMD_CTRL_LBME_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_LBME_SHIFT) & CAN_CMD_STA_CMD_CTRL_LBME_MASK)
#define CAN_CMD_STA_CMD_CTRL_LBME_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_LBME_MASK) >> CAN_CMD_STA_CMD_CTRL_LBME_SHIFT)

/*
 * LBMI (RW)
 *
 * Loop Back Mode, Internal
 * 0 - Disabled1 - EnabledLBMI should not be enabled while a transmission is active.
 */
#define CAN_CMD_STA_CMD_CTRL_LBMI_MASK (0x20U)
#define CAN_CMD_STA_CMD_CTRL_LBMI_SHIFT (5U)
#define CAN_CMD_STA_CMD_CTRL_LBMI_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_LBMI_SHIFT) & CAN_CMD_STA_CMD_CTRL_LBMI_MASK)
#define CAN_CMD_STA_CMD_CTRL_LBMI_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_LBMI_MASK) >> CAN_CMD_STA_CMD_CTRL_LBMI_SHIFT)

/*
 * TPSS (RW)
 *
 * Transmission Primary Single Shot mode for PTB
 * 0 - Disabled
 * 1 - Enabled
 */
#define CAN_CMD_STA_CMD_CTRL_TPSS_MASK (0x10U)
#define CAN_CMD_STA_CMD_CTRL_TPSS_SHIFT (4U)
#define CAN_CMD_STA_CMD_CTRL_TPSS_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_TPSS_SHIFT) & CAN_CMD_STA_CMD_CTRL_TPSS_MASK)
#define CAN_CMD_STA_CMD_CTRL_TPSS_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_TPSS_MASK) >> CAN_CMD_STA_CMD_CTRL_TPSS_SHIFT)

/*
 * TSSS (RW)
 *
 * Transmission Secondary Single Shot mode for STB
 * 0 - Disabled
 * 1 - Enabled
 */
#define CAN_CMD_STA_CMD_CTRL_TSSS_MASK (0x8U)
#define CAN_CMD_STA_CMD_CTRL_TSSS_SHIFT (3U)
#define CAN_CMD_STA_CMD_CTRL_TSSS_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_TSSS_SHIFT) & CAN_CMD_STA_CMD_CTRL_TSSS_MASK)
#define CAN_CMD_STA_CMD_CTRL_TSSS_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_TSSS_MASK) >> CAN_CMD_STA_CMD_CTRL_TSSS_SHIFT)

/*
 * RACTIVE (RO)
 *
 * Reception ACTIVE (Receive Status bit)
 * 1 - The controller is currently receiving a frame.
 * 0 - No receive activity.
 */
#define CAN_CMD_STA_CMD_CTRL_RACTIVE_MASK (0x4U)
#define CAN_CMD_STA_CMD_CTRL_RACTIVE_SHIFT (2U)
#define CAN_CMD_STA_CMD_CTRL_RACTIVE_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_RACTIVE_MASK) >> CAN_CMD_STA_CMD_CTRL_RACTIVE_SHIFT)

/*
 * TACTIVE (RO)
 *
 * Transmission ACTIVE (Transmit Status bit)
 * 1 - The controller is currently transmitting a frame.
 * 0 - No transmit activity.
 */
#define CAN_CMD_STA_CMD_CTRL_TACTIVE_MASK (0x2U)
#define CAN_CMD_STA_CMD_CTRL_TACTIVE_SHIFT (1U)
#define CAN_CMD_STA_CMD_CTRL_TACTIVE_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_TACTIVE_MASK) >> CAN_CMD_STA_CMD_CTRL_TACTIVE_SHIFT)

/*
 * BUSOFF (RW)
 *
 * Bus Off (Bus Status bit)
 * 1 - The controller status is “bus off”.
 * 0 - The controller status is “bus on”.
 * Writing a 1 to BUSOFF will reset TECNT and RECNT. This should be done only for debugging.
 * See Chapter 3.9.10.6 for details.
 */
#define CAN_CMD_STA_CMD_CTRL_BUSOFF_MASK (0x1U)
#define CAN_CMD_STA_CMD_CTRL_BUSOFF_SHIFT (0U)
#define CAN_CMD_STA_CMD_CTRL_BUSOFF_SET(x) (((uint32_t)(x) << CAN_CMD_STA_CMD_CTRL_BUSOFF_SHIFT) & CAN_CMD_STA_CMD_CTRL_BUSOFF_MASK)
#define CAN_CMD_STA_CMD_CTRL_BUSOFF_GET(x) (((uint32_t)(x) & CAN_CMD_STA_CMD_CTRL_BUSOFF_MASK) >> CAN_CMD_STA_CMD_CTRL_BUSOFF_SHIFT)

/* Bitfield definition for register: RTIE */
/*
 * RIE (RW)
 *
 * Receive Interrupt Enable
 * 0 – Disabled, 1 – Enabled
 */
#define CAN_RTIE_RIE_MASK (0x80U)
#define CAN_RTIE_RIE_SHIFT (7U)
#define CAN_RTIE_RIE_SET(x) (((uint8_t)(x) << CAN_RTIE_RIE_SHIFT) & CAN_RTIE_RIE_MASK)
#define CAN_RTIE_RIE_GET(x) (((uint8_t)(x) & CAN_RTIE_RIE_MASK) >> CAN_RTIE_RIE_SHIFT)

/*
 * ROIE (RW)
 *
 * RB Overrun Interrupt Enable
 * 0 – Disabled, 1 – Enabled
 */
#define CAN_RTIE_ROIE_MASK (0x40U)
#define CAN_RTIE_ROIE_SHIFT (6U)
#define CAN_RTIE_ROIE_SET(x) (((uint8_t)(x) << CAN_RTIE_ROIE_SHIFT) & CAN_RTIE_ROIE_MASK)
#define CAN_RTIE_ROIE_GET(x) (((uint8_t)(x) & CAN_RTIE_ROIE_MASK) >> CAN_RTIE_ROIE_SHIFT)

/*
 * RFIE (RW)
 *
 * RB Full Interrupt Enable
 * 0 – Disabled, 1 – Enabled
 */
#define CAN_RTIE_RFIE_MASK (0x20U)
#define CAN_RTIE_RFIE_SHIFT (5U)
#define CAN_RTIE_RFIE_SET(x) (((uint8_t)(x) << CAN_RTIE_RFIE_SHIFT) & CAN_RTIE_RFIE_MASK)
#define CAN_RTIE_RFIE_GET(x) (((uint8_t)(x) & CAN_RTIE_RFIE_MASK) >> CAN_RTIE_RFIE_SHIFT)

/*
 * RAFIE (RW)
 *
 * RB Almost Full Interrupt Enable
 * 0 – Disabled, 1 – Enabled
 */
#define CAN_RTIE_RAFIE_MASK (0x10U)
#define CAN_RTIE_RAFIE_SHIFT (4U)
#define CAN_RTIE_RAFIE_SET(x) (((uint8_t)(x) << CAN_RTIE_RAFIE_SHIFT) & CAN_RTIE_RAFIE_MASK)
#define CAN_RTIE_RAFIE_GET(x) (((uint8_t)(x) & CAN_RTIE_RAFIE_MASK) >> CAN_RTIE_RAFIE_SHIFT)

/*
 * TPIE (RW)
 *
 * Transmission Primary Interrupt Enable
 * 0 – Disabled, 1 – Enabled
 */
#define CAN_RTIE_TPIE_MASK (0x8U)
#define CAN_RTIE_TPIE_SHIFT (3U)
#define CAN_RTIE_TPIE_SET(x) (((uint8_t)(x) << CAN_RTIE_TPIE_SHIFT) & CAN_RTIE_TPIE_MASK)
#define CAN_RTIE_TPIE_GET(x) (((uint8_t)(x) & CAN_RTIE_TPIE_MASK) >> CAN_RTIE_TPIE_SHIFT)

/*
 * TSIE (RW)
 *
 * Transmission Secondary Interrupt Enable
 * 0 – Disabled, 1 – Enabled
 */
#define CAN_RTIE_TSIE_MASK (0x4U)
#define CAN_RTIE_TSIE_SHIFT (2U)
#define CAN_RTIE_TSIE_SET(x) (((uint8_t)(x) << CAN_RTIE_TSIE_SHIFT) & CAN_RTIE_TSIE_MASK)
#define CAN_RTIE_TSIE_GET(x) (((uint8_t)(x) & CAN_RTIE_TSIE_MASK) >> CAN_RTIE_TSIE_SHIFT)

/*
 * EIE (RW)
 *
 * Error Interrupt Enable
 * 0 – Disabled, 1 – Enabled
 */
#define CAN_RTIE_EIE_MASK (0x2U)
#define CAN_RTIE_EIE_SHIFT (1U)
#define CAN_RTIE_EIE_SET(x) (((uint8_t)(x) << CAN_RTIE_EIE_SHIFT) & CAN_RTIE_EIE_MASK)
#define CAN_RTIE_EIE_GET(x) (((uint8_t)(x) & CAN_RTIE_EIE_MASK) >> CAN_RTIE_EIE_SHIFT)

/*
 * TSFF (RO)
 *
 * If TTEN=0 or TTTBM=0: Transmit Secondary buffer Full Flag
 * 1 - The STB is filled with the maximal number of messages.
 * 0 - The STB is not filled with the maximal number of messages.
 * If the STB is disabled using STB_DISABLE, then TSFF=0.
 * If TTEN=1 and TTTBM=1: Transmit buffer Slot Full Flag
 * 1 - The buffer slot selected by TBPTR is filled.
 * 0 - The buffer slot selected by TBPTR is empty.
 */
#define CAN_RTIE_TSFF_MASK (0x1U)
#define CAN_RTIE_TSFF_SHIFT (0U)
#define CAN_RTIE_TSFF_GET(x) (((uint8_t)(x) & CAN_RTIE_TSFF_MASK) >> CAN_RTIE_TSFF_SHIFT)

/* Bitfield definition for register: RTIF */
/*
 * RIF (W1C)
 *
 * Receive Interrupt Flag
 * 1 - Data or a remote frame has been received and is available in the receive buffer.
 * 0 - No frame has been received.
 */
#define CAN_RTIF_RIF_MASK (0x80U)
#define CAN_RTIF_RIF_SHIFT (7U)
#define CAN_RTIF_RIF_SET(x) (((uint8_t)(x) << CAN_RTIF_RIF_SHIFT) & CAN_RTIF_RIF_MASK)
#define CAN_RTIF_RIF_GET(x) (((uint8_t)(x) & CAN_RTIF_RIF_MASK) >> CAN_RTIF_RIF_SHIFT)

/*
 * ROIF (W1C)
 *
 * RB Overrun Interrupt Flag
 * 1 - At least one received message has been overwritten in the RB.
 * 0 - No RB overwritten.
 * In case of an overrun both ROIF and RFIF will be set.
 */
#define CAN_RTIF_ROIF_MASK (0x40U)
#define CAN_RTIF_ROIF_SHIFT (6U)
#define CAN_RTIF_ROIF_SET(x) (((uint8_t)(x) << CAN_RTIF_ROIF_SHIFT) & CAN_RTIF_ROIF_MASK)
#define CAN_RTIF_ROIF_GET(x) (((uint8_t)(x) & CAN_RTIF_ROIF_MASK) >> CAN_RTIF_ROIF_SHIFT)

/*
 * RFIF (W1C)
 *
 * RB Full Interrupt Flag
 * 1 - All RBs are full. If no RB will be released until the next valid message is received,
 * the oldest message will be lost.
 * 0 - The RB FIFO is not full.
 */
#define CAN_RTIF_RFIF_MASK (0x20U)
#define CAN_RTIF_RFIF_SHIFT (5U)
#define CAN_RTIF_RFIF_SET(x) (((uint8_t)(x) << CAN_RTIF_RFIF_SHIFT) & CAN_RTIF_RFIF_MASK)
#define CAN_RTIF_RFIF_GET(x) (((uint8_t)(x) & CAN_RTIF_RFIF_MASK) >> CAN_RTIF_RFIF_SHIFT)

/*
 * RAFIF (W1C)
 *
 * RB Almost Full Interrupt Flag
 * 1 - number of filled RB slots >= AFWL_i
 * 0 - number of filled RB slots < AFWL_i
 */
#define CAN_RTIF_RAFIF_MASK (0x10U)
#define CAN_RTIF_RAFIF_SHIFT (4U)
#define CAN_RTIF_RAFIF_SET(x) (((uint8_t)(x) << CAN_RTIF_RAFIF_SHIFT) & CAN_RTIF_RAFIF_MASK)
#define CAN_RTIF_RAFIF_GET(x) (((uint8_t)(x) & CAN_RTIF_RAFIF_MASK) >> CAN_RTIF_RAFIF_SHIFT)

/*
 * TPIF (W1C)
 *
 * Transmission Primary Interrupt Flag
 * 1 - The requested transmission of the PTB has been successfully completed.
 * 0 - No transmission of the PTB has been completed.
 * In TTCAN mode, TPIF will never be set. Then only TSIF is valid.
 */
#define CAN_RTIF_TPIF_MASK (0x8U)
#define CAN_RTIF_TPIF_SHIFT (3U)
#define CAN_RTIF_TPIF_SET(x) (((uint8_t)(x) << CAN_RTIF_TPIF_SHIFT) & CAN_RTIF_TPIF_MASK)
#define CAN_RTIF_TPIF_GET(x) (((uint8_t)(x) & CAN_RTIF_TPIF_MASK) >> CAN_RTIF_TPIF_SHIFT)

/*
 * TSIF (W1C)
 *
 * Transmission Secondary Interrupt Flag
 * 1 - The requested transmission of the STB has been successfully completed.
 * 0 - No transmission of the STB has been completed successfully.
 * In TTCAN mode TSIF will signal all successful transmissions, regardless of storage location of
 * the message.
 */
#define CAN_RTIF_TSIF_MASK (0x4U)
#define CAN_RTIF_TSIF_SHIFT (2U)
#define CAN_RTIF_TSIF_SET(x) (((uint8_t)(x) << CAN_RTIF_TSIF_SHIFT) & CAN_RTIF_TSIF_MASK)
#define CAN_RTIF_TSIF_GET(x) (((uint8_t)(x) & CAN_RTIF_TSIF_MASK) >> CAN_RTIF_TSIF_SHIFT)

/*
 * EIF (W1C)
 *
 * Error Interrupt Flag
 * 1 - The border of the error warning limit has been crossed in either direction,
 * or the BUSOFF bit has been changed in either direction.
 * 0 - There has been no change.
 */
#define CAN_RTIF_EIF_MASK (0x2U)
#define CAN_RTIF_EIF_SHIFT (1U)
#define CAN_RTIF_EIF_SET(x) (((uint8_t)(x) << CAN_RTIF_EIF_SHIFT) & CAN_RTIF_EIF_MASK)
#define CAN_RTIF_EIF_GET(x) (((uint8_t)(x) & CAN_RTIF_EIF_MASK) >> CAN_RTIF_EIF_SHIFT)

/*
 * AIF (W1C)
 *
 * Abort Interrupt Flag
 * 1 - After setting TPA or TSA the appropriated message(s) have been aborted.
 * It is recommended to not set both TPA and TSA simultaneously because both
 * source AIF.
 * 0 - No abort has been executed.
 * The AIF does not have an associated enable register.
 */
#define CAN_RTIF_AIF_MASK (0x1U)
#define CAN_RTIF_AIF_SHIFT (0U)
#define CAN_RTIF_AIF_SET(x) (((uint8_t)(x) << CAN_RTIF_AIF_SHIFT) & CAN_RTIF_AIF_MASK)
#define CAN_RTIF_AIF_GET(x) (((uint8_t)(x) & CAN_RTIF_AIF_MASK) >> CAN_RTIF_AIF_SHIFT)

/* Bitfield definition for register: ERRINT */
/*
 * EWARN (RO)
 *
 * Error WARNing limit reached
 * 1 - One of the error counters RECNT or TECNT is equal or bigger than EWL0 - The values in both counters are less than EWL.
 */
#define CAN_ERRINT_EWARN_MASK (0x80U)
#define CAN_ERRINT_EWARN_SHIFT (7U)
#define CAN_ERRINT_EWARN_GET(x) (((uint8_t)(x) & CAN_ERRINT_EWARN_MASK) >> CAN_ERRINT_EWARN_SHIFT)

/*
 * EPASS (RO)
 *
 * Error Passive mode active
 * 0 - not active (node is error active)
 * 1 - active (node is error passive)
 */
#define CAN_ERRINT_EPASS_MASK (0x40U)
#define CAN_ERRINT_EPASS_SHIFT (6U)
#define CAN_ERRINT_EPASS_GET(x) (((uint8_t)(x) & CAN_ERRINT_EPASS_MASK) >> CAN_ERRINT_EPASS_SHIFT)

/*
 * EPIE (RW)
 *
 * Error Passive Interrupt Enable
 */
#define CAN_ERRINT_EPIE_MASK (0x20U)
#define CAN_ERRINT_EPIE_SHIFT (5U)
#define CAN_ERRINT_EPIE_SET(x) (((uint8_t)(x) << CAN_ERRINT_EPIE_SHIFT) & CAN_ERRINT_EPIE_MASK)
#define CAN_ERRINT_EPIE_GET(x) (((uint8_t)(x) & CAN_ERRINT_EPIE_MASK) >> CAN_ERRINT_EPIE_SHIFT)

/*
 * EPIF (W1C)
 *
 * Error Passive Interrupt Flag. EPIF will be activated if the error status changes from error
 * active to error passive or vice versa and if this interrupt is enabled.
 */
#define CAN_ERRINT_EPIF_MASK (0x10U)
#define CAN_ERRINT_EPIF_SHIFT (4U)
#define CAN_ERRINT_EPIF_SET(x) (((uint8_t)(x) << CAN_ERRINT_EPIF_SHIFT) & CAN_ERRINT_EPIF_MASK)
#define CAN_ERRINT_EPIF_GET(x) (((uint8_t)(x) & CAN_ERRINT_EPIF_MASK) >> CAN_ERRINT_EPIF_SHIFT)

/*
 * ALIE (RW)
 *
 * Arbitration Lost Interrupt Enable
 */
#define CAN_ERRINT_ALIE_MASK (0x8U)
#define CAN_ERRINT_ALIE_SHIFT (3U)
#define CAN_ERRINT_ALIE_SET(x) (((uint8_t)(x) << CAN_ERRINT_ALIE_SHIFT) & CAN_ERRINT_ALIE_MASK)
#define CAN_ERRINT_ALIE_GET(x) (((uint8_t)(x) & CAN_ERRINT_ALIE_MASK) >> CAN_ERRINT_ALIE_SHIFT)

/*
 * ALIF (W1C)
 *
 * Arbitration Lost Interrupt Flag
 */
#define CAN_ERRINT_ALIF_MASK (0x4U)
#define CAN_ERRINT_ALIF_SHIFT (2U)
#define CAN_ERRINT_ALIF_SET(x) (((uint8_t)(x) << CAN_ERRINT_ALIF_SHIFT) & CAN_ERRINT_ALIF_MASK)
#define CAN_ERRINT_ALIF_GET(x) (((uint8_t)(x) & CAN_ERRINT_ALIF_MASK) >> CAN_ERRINT_ALIF_SHIFT)

/*
 * BEIE (RW)
 *
 * Bus Error Interrupt Enable
 */
#define CAN_ERRINT_BEIE_MASK (0x2U)
#define CAN_ERRINT_BEIE_SHIFT (1U)
#define CAN_ERRINT_BEIE_SET(x) (((uint8_t)(x) << CAN_ERRINT_BEIE_SHIFT) & CAN_ERRINT_BEIE_MASK)
#define CAN_ERRINT_BEIE_GET(x) (((uint8_t)(x) & CAN_ERRINT_BEIE_MASK) >> CAN_ERRINT_BEIE_SHIFT)

/*
 * BEIF (W1C)
 *
 * Bus Error Interrupt Flag
 */
#define CAN_ERRINT_BEIF_MASK (0x1U)
#define CAN_ERRINT_BEIF_SHIFT (0U)
#define CAN_ERRINT_BEIF_SET(x) (((uint8_t)(x) << CAN_ERRINT_BEIF_SHIFT) & CAN_ERRINT_BEIF_MASK)
#define CAN_ERRINT_BEIF_GET(x) (((uint8_t)(x) & CAN_ERRINT_BEIF_MASK) >> CAN_ERRINT_BEIF_SHIFT)

/* Bitfield definition for register: LIMIT */
/*
 * AFWL (RW)
 *
 * receive buffer Almost Full Warning Limit
 * AFWL defines the internal warning limit AFWL_i with being the number of availableRB slots.
 * AFWL_i is compared to the number of filled RB slots and triggers RAFIF if equal. Thevalid range of .
 * AFWL = 0 is meaningless and automatically treated as 0x1. (Note that AFWL is meant in this rule and not AFWL_i.)
 * AFWL_i > nRB is meaningless and automatically treated as nRB.
 * AFWL_i = nRB is a valid value, but note that RFIF also exists.
 */
#define CAN_LIMIT_AFWL_MASK (0xF0U)
#define CAN_LIMIT_AFWL_SHIFT (4U)
#define CAN_LIMIT_AFWL_SET(x) (((uint8_t)(x) << CAN_LIMIT_AFWL_SHIFT) & CAN_LIMIT_AFWL_MASK)
#define CAN_LIMIT_AFWL_GET(x) (((uint8_t)(x) & CAN_LIMIT_AFWL_MASK) >> CAN_LIMIT_AFWL_SHIFT)

/*
 * EWL (RW)
 *
 * Programmable Error Warning Limit = (EWL+1)*8. Possible Limit values: 8, 16, … 128.
 * The value of EWL controls EIF.
 */
#define CAN_LIMIT_EWL_MASK (0xFU)
#define CAN_LIMIT_EWL_SHIFT (0U)
#define CAN_LIMIT_EWL_SET(x) (((uint8_t)(x) << CAN_LIMIT_EWL_SHIFT) & CAN_LIMIT_EWL_MASK)
#define CAN_LIMIT_EWL_GET(x) (((uint8_t)(x) & CAN_LIMIT_EWL_MASK) >> CAN_LIMIT_EWL_SHIFT)

/* Bitfield definition for register: S_PRESC */
/*
 * S_PRESC (RW)
 *
 * Prescaler (slow speed)
 * The prescaler divides the system clock to get the time quanta clock tq_clk.Valid range PRESC=[0x00, 0xff] results in divider values 1 to 256.
 */
#define CAN_S_PRESC_S_PRESC_MASK (0xFF000000UL)
#define CAN_S_PRESC_S_PRESC_SHIFT (24U)
#define CAN_S_PRESC_S_PRESC_SET(x) (((uint32_t)(x) << CAN_S_PRESC_S_PRESC_SHIFT) & CAN_S_PRESC_S_PRESC_MASK)
#define CAN_S_PRESC_S_PRESC_GET(x) (((uint32_t)(x) & CAN_S_PRESC_S_PRESC_MASK) >> CAN_S_PRESC_S_PRESC_SHIFT)

/*
 * S_SJW (RW)
 *
 * Synchronization Jump Width (slow speed)
 * The Synchronization Jump Width is the maximum time forshortening or lengthening the Bit Time for resynchronization, where TQ is a timequanta.
 */
#define CAN_S_PRESC_S_SJW_MASK (0x7F0000UL)
#define CAN_S_PRESC_S_SJW_SHIFT (16U)
#define CAN_S_PRESC_S_SJW_SET(x) (((uint32_t)(x) << CAN_S_PRESC_S_SJW_SHIFT) & CAN_S_PRESC_S_SJW_MASK)
#define CAN_S_PRESC_S_SJW_GET(x) (((uint32_t)(x) & CAN_S_PRESC_S_SJW_MASK) >> CAN_S_PRESC_S_SJW_SHIFT)

/*
 * S_SEG_2 (RW)
 *
 * Bit Timing Segment 2 (slow speed)
 * Time after the sample point.
 */
#define CAN_S_PRESC_S_SEG_2_MASK (0x7F00U)
#define CAN_S_PRESC_S_SEG_2_SHIFT (8U)
#define CAN_S_PRESC_S_SEG_2_SET(x) (((uint32_t)(x) << CAN_S_PRESC_S_SEG_2_SHIFT) & CAN_S_PRESC_S_SEG_2_MASK)
#define CAN_S_PRESC_S_SEG_2_GET(x) (((uint32_t)(x) & CAN_S_PRESC_S_SEG_2_MASK) >> CAN_S_PRESC_S_SEG_2_SHIFT)

/*
 * S_SEG_1 (RW)
 *
 * Bit Timing Segment 1 (slow speed)
 * The sample point will be set to after start of bit time.
 */
#define CAN_S_PRESC_S_SEG_1_MASK (0xFFU)
#define CAN_S_PRESC_S_SEG_1_SHIFT (0U)
#define CAN_S_PRESC_S_SEG_1_SET(x) (((uint32_t)(x) << CAN_S_PRESC_S_SEG_1_SHIFT) & CAN_S_PRESC_S_SEG_1_MASK)
#define CAN_S_PRESC_S_SEG_1_GET(x) (((uint32_t)(x) & CAN_S_PRESC_S_SEG_1_MASK) >> CAN_S_PRESC_S_SEG_1_SHIFT)

/* Bitfield definition for register: F_PRESC */
/*
 * F_PRESC (RW)
 *
 * Prescaler (fast speed)
 * The prescaler divides the system clock to get the time quanta clock tq_clk.Valid range PRESC=[0x00, 0xff] results in divider values 1 to 256.
 */
#define CAN_F_PRESC_F_PRESC_MASK (0xFF000000UL)
#define CAN_F_PRESC_F_PRESC_SHIFT (24U)
#define CAN_F_PRESC_F_PRESC_SET(x) (((uint32_t)(x) << CAN_F_PRESC_F_PRESC_SHIFT) & CAN_F_PRESC_F_PRESC_MASK)
#define CAN_F_PRESC_F_PRESC_GET(x) (((uint32_t)(x) & CAN_F_PRESC_F_PRESC_MASK) >> CAN_F_PRESC_F_PRESC_SHIFT)

/*
 * F_SJW (RW)
 *
 * Synchronization Jump Width (fast speed)
 * The Synchronization Jump Width is the maximum time forshortening or lengthening the Bit Time for resynchronization, where TQ is a timequanta.
 */
#define CAN_F_PRESC_F_SJW_MASK (0xF0000UL)
#define CAN_F_PRESC_F_SJW_SHIFT (16U)
#define CAN_F_PRESC_F_SJW_SET(x) (((uint32_t)(x) << CAN_F_PRESC_F_SJW_SHIFT) & CAN_F_PRESC_F_SJW_MASK)
#define CAN_F_PRESC_F_SJW_GET(x) (((uint32_t)(x) & CAN_F_PRESC_F_SJW_MASK) >> CAN_F_PRESC_F_SJW_SHIFT)

/*
 * F_SEG_2 (RW)
 *
 * Bit Timing Segment 2 (fast speed)
 * Time after the sample point
 */
#define CAN_F_PRESC_F_SEG_2_MASK (0xF00U)
#define CAN_F_PRESC_F_SEG_2_SHIFT (8U)
#define CAN_F_PRESC_F_SEG_2_SET(x) (((uint32_t)(x) << CAN_F_PRESC_F_SEG_2_SHIFT) & CAN_F_PRESC_F_SEG_2_MASK)
#define CAN_F_PRESC_F_SEG_2_GET(x) (((uint32_t)(x) & CAN_F_PRESC_F_SEG_2_MASK) >> CAN_F_PRESC_F_SEG_2_SHIFT)

/*
 * F_SEG_1 (RW)
 *
 * Bit Timing Segment 1 (fast speed)
 * The sample point will be set to after start of bit time.
 */
#define CAN_F_PRESC_F_SEG_1_MASK (0xFU)
#define CAN_F_PRESC_F_SEG_1_SHIFT (0U)
#define CAN_F_PRESC_F_SEG_1_SET(x) (((uint32_t)(x) << CAN_F_PRESC_F_SEG_1_SHIFT) & CAN_F_PRESC_F_SEG_1_MASK)
#define CAN_F_PRESC_F_SEG_1_GET(x) (((uint32_t)(x) & CAN_F_PRESC_F_SEG_1_MASK) >> CAN_F_PRESC_F_SEG_1_SHIFT)

/* Bitfield definition for register: EALCAP */
/*
 * KOER (RO)
 *
 * Kind Of ERror (Error code)
 * 000 - no error
 * 001 - BIT ERROR
 * 010 - FORM ERROR
 * 011 - STUFF ERROR
 * 100 - ACKNOWLEDGEMENT ERROR
 * 101 - CRC ERROR
 * 110 - OTHER ERROR(dominant bits after own error flag, received active Error Flag too long,dominant bit during Passive-Error-Flag after ACK error)
 * 111 - not used
 * KOER is updated with each new error. Therefore it stays untouched when frames aresuccessfully transmitted or received.
 */
#define CAN_EALCAP_KOER_MASK (0xE0U)
#define CAN_EALCAP_KOER_SHIFT (5U)
#define CAN_EALCAP_KOER_GET(x) (((uint8_t)(x) & CAN_EALCAP_KOER_MASK) >> CAN_EALCAP_KOER_SHIFT)

/*
 * ALC (RO)
 *
 * Arbitration Lost Capture (bit position in the frame where the arbitration has been lost)
 */
#define CAN_EALCAP_ALC_MASK (0x1FU)
#define CAN_EALCAP_ALC_SHIFT (0U)
#define CAN_EALCAP_ALC_GET(x) (((uint8_t)(x) & CAN_EALCAP_ALC_MASK) >> CAN_EALCAP_ALC_SHIFT)

/* Bitfield definition for register: TDC */
/*
 * TDCEN (RW)
 *
 * Transmitter Delay Compensation ENable
 * TDC will be activated during the data phase of a CAN FD frame if BRS is active if TDCEN=1.
 */
#define CAN_TDC_TDCEN_MASK (0x80U)
#define CAN_TDC_TDCEN_SHIFT (7U)
#define CAN_TDC_TDCEN_SET(x) (((uint8_t)(x) << CAN_TDC_TDCEN_SHIFT) & CAN_TDC_TDCEN_MASK)
#define CAN_TDC_TDCEN_GET(x) (((uint8_t)(x) & CAN_TDC_TDCEN_MASK) >> CAN_TDC_TDCEN_SHIFT)

/*
 * SSPOFF (RW)
 *
 * Secondary Sample Point OFFset
 * The transmitter delay plus SSPOFF defines the time of the secondary sample point for TDC.
 * SSPOFF is given as a number of TQ.
 */
#define CAN_TDC_SSPOFF_MASK (0x7FU)
#define CAN_TDC_SSPOFF_SHIFT (0U)
#define CAN_TDC_SSPOFF_SET(x) (((uint8_t)(x) << CAN_TDC_SSPOFF_SHIFT) & CAN_TDC_SSPOFF_MASK)
#define CAN_TDC_SSPOFF_GET(x) (((uint8_t)(x) & CAN_TDC_SSPOFF_MASK) >> CAN_TDC_SSPOFF_SHIFT)

/* Bitfield definition for register: RECNT */
/*
 * RECNT (RO)
 *
 * Receive Error CouNT (number of errors during reception)
 * RECNT is incremented and decremented as defined in the CAN specification.
 * RECNT does not overflow.
 * If TXB=1, then the error counters are frozen.
 */
#define CAN_RECNT_RECNT_MASK (0xFFU)
#define CAN_RECNT_RECNT_SHIFT (0U)
#define CAN_RECNT_RECNT_GET(x) (((uint8_t)(x) & CAN_RECNT_RECNT_MASK) >> CAN_RECNT_RECNT_SHIFT)

/* Bitfield definition for register: TECNT */
/*
 * TECNT (RO)
 *
 * Transmit Error CouNT (number of errors during transmission)
 * TECNT is incremented and decremented as defined in the CAN specification.
 * In case of the “bus off state” TECNT may overflow.
 * If TXB=1, then the error counters are frozen.
 */
#define CAN_TECNT_TECNT_MASK (0xFFU)
#define CAN_TECNT_TECNT_SHIFT (0U)
#define CAN_TECNT_TECNT_GET(x) (((uint8_t)(x) & CAN_TECNT_TECNT_MASK) >> CAN_TECNT_TECNT_SHIFT)

/* Bitfield definition for register: ACFCTRL */
/*
 * SELMASK (RW)
 *
 * SELect acceptance MASK
 * 0 - Registers ACF_x point to acceptance code
 * 1 - Registers ACF_x point to acceptance mask.
 * ACFADR selects one specific acceptance filter.
 */
#define CAN_ACFCTRL_SELMASK_MASK (0x20U)
#define CAN_ACFCTRL_SELMASK_SHIFT (5U)
#define CAN_ACFCTRL_SELMASK_SET(x) (((uint8_t)(x) << CAN_ACFCTRL_SELMASK_SHIFT) & CAN_ACFCTRL_SELMASK_MASK)
#define CAN_ACFCTRL_SELMASK_GET(x) (((uint8_t)(x) & CAN_ACFCTRL_SELMASK_MASK) >> CAN_ACFCTRL_SELMASK_SHIFT)

/*
 * ACFADR (RW)
 *
 * acceptance filter address
 * ACFADR points to a specific acceptance filter.
 * The selected filter is accessible using theregisters ACF_x.
 * Bit SELMASK selects between acceptance code and mask for theselected acceptance filter.
 * A value of ACFADR>ACF_NUMBER-1 is meaningless and automatically treated as value ACF_NUMBER-1.
 * ACF_NUMBER = 16.
 */
#define CAN_ACFCTRL_ACFADR_MASK (0xFU)
#define CAN_ACFCTRL_ACFADR_SHIFT (0U)
#define CAN_ACFCTRL_ACFADR_SET(x) (((uint8_t)(x) << CAN_ACFCTRL_ACFADR_SHIFT) & CAN_ACFCTRL_ACFADR_MASK)
#define CAN_ACFCTRL_ACFADR_GET(x) (((uint8_t)(x) & CAN_ACFCTRL_ACFADR_MASK) >> CAN_ACFCTRL_ACFADR_SHIFT)

/* Bitfield definition for register: TIMECFG */
/*
 * TIMEPOS (RW)
 *
 * TIME-stamping POSition
 * 0 – SOF1 – EOF (see Chapter 7)TIMEPOS can only be changed if TIMEEN=0, but it is possible to modify TIMPOS withthe same write access that sets TIMEEN=1.
 */
#define CAN_TIMECFG_TIMEPOS_MASK (0x2U)
#define CAN_TIMECFG_TIMEPOS_SHIFT (1U)
#define CAN_TIMECFG_TIMEPOS_SET(x) (((uint8_t)(x) << CAN_TIMECFG_TIMEPOS_SHIFT) & CAN_TIMECFG_TIMEPOS_MASK)
#define CAN_TIMECFG_TIMEPOS_GET(x) (((uint8_t)(x) & CAN_TIMECFG_TIMEPOS_MASK) >> CAN_TIMECFG_TIMEPOS_SHIFT)

/*
 * TIMEEN (RW)
 *
 * TIME-stamping ENable
 * 0 – disabled
 * 1 – enabled
 */
#define CAN_TIMECFG_TIMEEN_MASK (0x1U)
#define CAN_TIMECFG_TIMEEN_SHIFT (0U)
#define CAN_TIMECFG_TIMEEN_SET(x) (((uint8_t)(x) << CAN_TIMECFG_TIMEEN_SHIFT) & CAN_TIMECFG_TIMEEN_MASK)
#define CAN_TIMECFG_TIMEEN_GET(x) (((uint8_t)(x) & CAN_TIMECFG_TIMEEN_MASK) >> CAN_TIMECFG_TIMEEN_SHIFT)

/* Bitfield definition for register: ACF_EN */
/*
 * ACF_EN (RW)
 *
 * Acceptance filter Enable
 * 1 - acceptance filter enabled
 * 0 - acceptance filter disable
 * Each acceptance filter (AMASK / ACODE) can be individually enabled or disabled.
 * Disabled filters reject a message. Only enabled filters can accept a message if the
 * appropriate AMASK / ACODE configuration matches.
 */
#define CAN_ACF_EN_ACF_EN_MASK (0xFFFFU)
#define CAN_ACF_EN_ACF_EN_SHIFT (0U)
#define CAN_ACF_EN_ACF_EN_SET(x) (((uint16_t)(x) << CAN_ACF_EN_ACF_EN_SHIFT) & CAN_ACF_EN_ACF_EN_MASK)
#define CAN_ACF_EN_ACF_EN_GET(x) (((uint16_t)(x) & CAN_ACF_EN_ACF_EN_MASK) >> CAN_ACF_EN_ACF_EN_SHIFT)

/* Bitfield definition for register: ACF */
/*
 * AIDEE (RW)
 *
 * Acceptance mask IDE bit check enable
 * 1 - acceptance filter accepts either standard or extended as defined by AIDE
 * 0 - acceptance filter accepts both standard or extended frames
 * Only filter 0 is affected by the power-on reset. All other filters stay uninitialized.
 */
#define CAN_ACF_AIDEE_MASK (0x40000000UL)
#define CAN_ACF_AIDEE_SHIFT (30U)
#define CAN_ACF_AIDEE_SET(x) (((uint32_t)(x) << CAN_ACF_AIDEE_SHIFT) & CAN_ACF_AIDEE_MASK)
#define CAN_ACF_AIDEE_GET(x) (((uint32_t)(x) & CAN_ACF_AIDEE_MASK) >> CAN_ACF_AIDEE_SHIFT)

/*
 * AIDE (RW)
 *
 * Acceptance mask IDE bit value
 * If AIDEE=1 then:
 * 1 - acceptance filter accepts only extended frames
 * 0 - acceptance filter accepts only standard frames
 * Only filter 0 is affected by the power-on reset. All other filters stay uninitialized.
 */
#define CAN_ACF_AIDE_MASK (0x20000000UL)
#define CAN_ACF_AIDE_SHIFT (29U)
#define CAN_ACF_AIDE_SET(x) (((uint32_t)(x) << CAN_ACF_AIDE_SHIFT) & CAN_ACF_AIDE_MASK)
#define CAN_ACF_AIDE_GET(x) (((uint32_t)(x) & CAN_ACF_AIDE_MASK) >> CAN_ACF_AIDE_SHIFT)

/*
 * CODE_MASK (RW)
 *
 * Acceptance CODE
 * 1 - ACC bit value to compare with ID bit of the received message
 * 0 - ACC bit value to compare with ID bit of the received message
 * ACODE_x(10:0) will be used for extended frames.
 * ACODE_x(28:0) will be used for extended frames.
 * Only filter 0 is affected by the power-on reset.
 * Acceptance MASK(if SELMASK ==1 )
 * 1 - acceptance check for these bits of receive identifier disabled
 * 0 - acceptance check for these bits of receive identifier enable
 * AMASK_x(10:0) will be used for extended frames.
 * AMASK_x(28:0) will be used for extended frames.
 * Disabled bits result in accepting the message. Therefore the default configuration after
 * reset for filter 0 accepts all messages.
 * Only filter 0 is affected by the power-on reset.
 */
#define CAN_ACF_CODE_MASK_MASK (0x1FFFFFFFUL)
#define CAN_ACF_CODE_MASK_SHIFT (0U)
#define CAN_ACF_CODE_MASK_SET(x) (((uint32_t)(x) << CAN_ACF_CODE_MASK_SHIFT) & CAN_ACF_CODE_MASK_MASK)
#define CAN_ACF_CODE_MASK_GET(x) (((uint32_t)(x) & CAN_ACF_CODE_MASK_MASK) >> CAN_ACF_CODE_MASK_SHIFT)

/* Bitfield definition for register: VER */
/*
 * VERSION (RW)
 *
 * Version of CAN-CTRL, given as decimal value. VER_1 holds the major version and
 * VER_0 the minor version.Example: version 5x16N00S00 is represented by VER_1=5 and VER_0=16
 */
#define CAN_VER_VERSION_MASK (0xFFFFU)
#define CAN_VER_VERSION_SHIFT (0U)
#define CAN_VER_VERSION_SET(x) (((uint16_t)(x) << CAN_VER_VERSION_SHIFT) & CAN_VER_VERSION_MASK)
#define CAN_VER_VERSION_GET(x) (((uint16_t)(x) & CAN_VER_VERSION_MASK) >> CAN_VER_VERSION_SHIFT)

/* Bitfield definition for register: TBSLOT */
/*
 * TBE (RW)
 *
 * set TB slot to “Empty”
 * 1 - slot selected by TBPTR shall be marked as “empty”
 * 0 - no actionTBE is automatically reset to 0 as soon as the slot is marked as empty and TSFF=0.
 * If atransmission from this slot is active, then TBE stays set as long as either the transmission completes or after a transmission error or arbitration loss the
 *  transmissionis not active any more.
 * If both TBF and TBE are set, then TBE wins
 */
#define CAN_TBSLOT_TBE_MASK (0x80U)
#define CAN_TBSLOT_TBE_SHIFT (7U)
#define CAN_TBSLOT_TBE_SET(x) (((uint8_t)(x) << CAN_TBSLOT_TBE_SHIFT) & CAN_TBSLOT_TBE_MASK)
#define CAN_TBSLOT_TBE_GET(x) (((uint8_t)(x) & CAN_TBSLOT_TBE_MASK) >> CAN_TBSLOT_TBE_SHIFT)

/*
 * TBF (RW)
 *
 * set TB slot to “Filled”
 * 1 - slot selected by TBPTR shall be marked as “filled”
 * 0 - no actionTBF is automatically reset to 0 as soon as the slot is marked as filled and TSFF=1.
 * If both TBF and TBE are set, then TBE wins.
 */
#define CAN_TBSLOT_TBF_MASK (0x40U)
#define CAN_TBSLOT_TBF_SHIFT (6U)
#define CAN_TBSLOT_TBF_SET(x) (((uint8_t)(x) << CAN_TBSLOT_TBF_SHIFT) & CAN_TBSLOT_TBF_MASK)
#define CAN_TBSLOT_TBF_GET(x) (((uint8_t)(x) & CAN_TBSLOT_TBF_MASK) >> CAN_TBSLOT_TBF_SHIFT)

/*
 * TBPTR (RW)
 *
 * Pointer to a TB message slot.
 * 0x00 - Pointer to the PTB
 * others - Pointer to a slot in the STB
 * The message slot pointed to by TBPTR is readable / writable using the TBUF registers.
 * Write access is only possible if TSFF=0.
 * Setting TBF to 1 marks the selected slot asfilled and setting TBE to 1 marks the selected slot as empty.
 * TBSEL and TSNEXT are unused in TTCAN mode and have no meaning.
 * TBPTR can only point to buffer slots, that exist in the hardware.
 * Unusable bits ofTBPTR are fixed to 0.
 * TBPTR is limited to the PTB and 63 STB slots.
 *  More slots cannot be used in TTCANmode.If TBPTR is too big and points to a slot that is not available, then TBF and TBE arereset automatically and no action takes place.
 */
#define CAN_TBSLOT_TBPTR_MASK (0x3FU)
#define CAN_TBSLOT_TBPTR_SHIFT (0U)
#define CAN_TBSLOT_TBPTR_SET(x) (((uint8_t)(x) << CAN_TBSLOT_TBPTR_SHIFT) & CAN_TBSLOT_TBPTR_MASK)
#define CAN_TBSLOT_TBPTR_GET(x) (((uint8_t)(x) & CAN_TBSLOT_TBPTR_MASK) >> CAN_TBSLOT_TBPTR_SHIFT)

/* Bitfield definition for register: TTCFG */
/*
 * WTIE (RW)
 *
 * Watch Trigger Interrupt Enable
 */
#define CAN_TTCFG_WTIE_MASK (0x80U)
#define CAN_TTCFG_WTIE_SHIFT (7U)
#define CAN_TTCFG_WTIE_SET(x) (((uint8_t)(x) << CAN_TTCFG_WTIE_SHIFT) & CAN_TTCFG_WTIE_MASK)
#define CAN_TTCFG_WTIE_GET(x) (((uint8_t)(x) & CAN_TTCFG_WTIE_MASK) >> CAN_TTCFG_WTIE_SHIFT)

/*
 * WTIF (RW)
 *
 * Watch Trigger Interrupt Flag
 * WTIF will be set if the cycle count reaches the limited defined by TT_WTRIG and WTIE is set.
 */
#define CAN_TTCFG_WTIF_MASK (0x40U)
#define CAN_TTCFG_WTIF_SHIFT (6U)
#define CAN_TTCFG_WTIF_SET(x) (((uint8_t)(x) << CAN_TTCFG_WTIF_SHIFT) & CAN_TTCFG_WTIF_MASK)
#define CAN_TTCFG_WTIF_GET(x) (((uint8_t)(x) & CAN_TTCFG_WTIF_MASK) >> CAN_TTCFG_WTIF_SHIFT)

/*
 * TEIF (RW)
 *
 * Trigger Error Interrupt Flag
 * The conditions when TEIF will be set, are defined in Chapter 6.4. There is no bit toenable or disable the handling of TEIF
 */
#define CAN_TTCFG_TEIF_MASK (0x20U)
#define CAN_TTCFG_TEIF_SHIFT (5U)
#define CAN_TTCFG_TEIF_SET(x) (((uint8_t)(x) << CAN_TTCFG_TEIF_SHIFT) & CAN_TTCFG_TEIF_MASK)
#define CAN_TTCFG_TEIF_GET(x) (((uint8_t)(x) & CAN_TTCFG_TEIF_MASK) >> CAN_TTCFG_TEIF_SHIFT)

/*
 * TTIE (RW)
 *
 * Time Trigger Interrupt Enable
 * If TTIE is set, then TTIF will be set if the cycle time is equal to the trigger timeTT_TRIG.
 */
#define CAN_TTCFG_TTIE_MASK (0x10U)
#define CAN_TTCFG_TTIE_SHIFT (4U)
#define CAN_TTCFG_TTIE_SET(x) (((uint8_t)(x) << CAN_TTCFG_TTIE_SHIFT) & CAN_TTCFG_TTIE_MASK)
#define CAN_TTCFG_TTIE_GET(x) (((uint8_t)(x) & CAN_TTCFG_TTIE_MASK) >> CAN_TTCFG_TTIE_SHIFT)

/*
 * TTIF (RW)
 *
 * Time Trigger Interrupt Flag
 * TTIF will be set if TTIE is set and the cycle time is equal to the trigger time TT_TRIG.
 * Writing a one to TTIF resets it. Writing a zero has no impact.TTIF will be set only once.
 * If TT_TRIG gets not updated, then TTIF will be not setagain in the next basic cycle.
 */
#define CAN_TTCFG_TTIF_MASK (0x8U)
#define CAN_TTCFG_TTIF_SHIFT (3U)
#define CAN_TTCFG_TTIF_SET(x) (((uint8_t)(x) << CAN_TTCFG_TTIF_SHIFT) & CAN_TTCFG_TTIF_MASK)
#define CAN_TTCFG_TTIF_GET(x) (((uint8_t)(x) & CAN_TTCFG_TTIF_MASK) >> CAN_TTCFG_TTIF_SHIFT)

/*
 * T_PRESC (RW)
 *
 * TTCAN Timer PRESCaler
 * 00b - 1
 * 01b - 2
 * 10b - 4
 * 11b - 8
 * The TTCAN time base is a CAN bittime defined by S_PRES, S_SEG_1 and S_SEG_2.With T_PRESC an additional prescaling factor of 1, 2, 4 or 8 is defined.
 * T_PRESC can only be modified if TTEN=0, but it is possible to modify T_PRESC and setTTEN simultaneously with one write access.
 */
#define CAN_TTCFG_T_PRESC_MASK (0x6U)
#define CAN_TTCFG_T_PRESC_SHIFT (1U)
#define CAN_TTCFG_T_PRESC_SET(x) (((uint8_t)(x) << CAN_TTCFG_T_PRESC_SHIFT) & CAN_TTCFG_T_PRESC_MASK)
#define CAN_TTCFG_T_PRESC_GET(x) (((uint8_t)(x) & CAN_TTCFG_T_PRESC_MASK) >> CAN_TTCFG_T_PRESC_SHIFT)

/*
 * TTEN (RW)
 *
 * Time Trigger Enable
 * 1 - TTCAN enabled, timer is running0 - disabled
 */
#define CAN_TTCFG_TTEN_MASK (0x1U)
#define CAN_TTCFG_TTEN_SHIFT (0U)
#define CAN_TTCFG_TTEN_SET(x) (((uint8_t)(x) << CAN_TTCFG_TTEN_SHIFT) & CAN_TTCFG_TTEN_MASK)
#define CAN_TTCFG_TTEN_GET(x) (((uint8_t)(x) & CAN_TTCFG_TTEN_MASK) >> CAN_TTCFG_TTEN_SHIFT)

/* Bitfield definition for register: REF_MSG */
/*
 * REF_IDE (RW)
 *
 * REFerence message IDE bit.
 */
#define CAN_REF_MSG_REF_IDE_MASK (0x80000000UL)
#define CAN_REF_MSG_REF_IDE_SHIFT (31U)
#define CAN_REF_MSG_REF_IDE_SET(x) (((uint32_t)(x) << CAN_REF_MSG_REF_IDE_SHIFT) & CAN_REF_MSG_REF_IDE_MASK)
#define CAN_REF_MSG_REF_IDE_GET(x) (((uint32_t)(x) & CAN_REF_MSG_REF_IDE_MASK) >> CAN_REF_MSG_REF_IDE_SHIFT)

/*
 * REF_MSG (RW)
 *
 * REFerence message IDentifier.
 * If REF_IDE is
 * 1 - REF_ID(28:0) is valid (extended ID)
 * 0 - REF_ID(10:0) is valid (standard ID)
 * REF_ID is used in TTCAN mode to detect a reference message. This holds for time
 * slaves (reception) as well as for the time master (transmission). If the reference
 * message is detected and there are no errors, then the Sync_Mark of this frame will
 * become the Ref_Mark.
 * REF_ID(2:0) is not tested and therefore the appropriate register bits are forced to 0.
 * These bits are used for up to 8 potential time masters.
 * CAN-CTRL recognizes the reference message only by ID. The payload is not tested.
 * Additional note: A time master will transmit a reference message in the same way as a
 * normal frame. REF_ID is intended for detection of a successful transmission of a
 * reference message.
 */
#define CAN_REF_MSG_REF_MSG_MASK (0x1FFFFFFFUL)
#define CAN_REF_MSG_REF_MSG_SHIFT (0U)
#define CAN_REF_MSG_REF_MSG_SET(x) (((uint32_t)(x) << CAN_REF_MSG_REF_MSG_SHIFT) & CAN_REF_MSG_REF_MSG_MASK)
#define CAN_REF_MSG_REF_MSG_GET(x) (((uint32_t)(x) & CAN_REF_MSG_REF_MSG_MASK) >> CAN_REF_MSG_REF_MSG_SHIFT)

/* Bitfield definition for register: TRIG_CFG */
/*
 * TEW (RW)
 *
 * Transmit Enable Window
 * For a single shot transmit trigger there is a time of up to 16 ticks of the cycle time
 * where the frame is allowed to start. TWE+1 defines the number of ticks.
 * TEW=0 is a valid setting and shortens the transmit enable window to 1 tick
 */
#define CAN_TRIG_CFG_TEW_MASK (0xF000U)
#define CAN_TRIG_CFG_TEW_SHIFT (12U)
#define CAN_TRIG_CFG_TEW_SET(x) (((uint16_t)(x) << CAN_TRIG_CFG_TEW_SHIFT) & CAN_TRIG_CFG_TEW_MASK)
#define CAN_TRIG_CFG_TEW_GET(x) (((uint16_t)(x) & CAN_TRIG_CFG_TEW_MASK) >> CAN_TRIG_CFG_TEW_SHIFT)

/*
 * TTYPE (RW)
 *
 * Trigger Type
 * 000b - Immediate Trigger for immediate transmission
 * 001b - Time Trigger for receive triggers
 * 010b - Single Shot Transmit Trigger for exclusive time windows
 * 011b - Transmit Start Trigger for merged arbitrating time windows
 * 100b - Transmit Stop Trigger for merged arbitrating time windows
 * others - no action
 * The time of the trigger is defined by TT_TRIG. TTPTR selects the TB slot for the
 * transmit triggers. See Chapter 6.4 for more details.
 */
#define CAN_TRIG_CFG_TTYPE_MASK (0x700U)
#define CAN_TRIG_CFG_TTYPE_SHIFT (8U)
#define CAN_TRIG_CFG_TTYPE_SET(x) (((uint16_t)(x) << CAN_TRIG_CFG_TTYPE_SHIFT) & CAN_TRIG_CFG_TTYPE_MASK)
#define CAN_TRIG_CFG_TTYPE_GET(x) (((uint16_t)(x) & CAN_TRIG_CFG_TTYPE_MASK) >> CAN_TRIG_CFG_TTYPE_SHIFT)

/*
 * TTPTR (RW)
 *
 * Transmit Trigger TB slot Pointer
 * If TTPTR is too big and points to a slot that is not available, then TEIF is set and no
 * new trigger can be activated after a write access to TT_TRIG_1.
 * If TTPTR points to an empty slot, then TEIF will be set at the moment, when the
 * trigger time is reached.
 */
#define CAN_TRIG_CFG_TTPTR_MASK (0x3FU)
#define CAN_TRIG_CFG_TTPTR_SHIFT (0U)
#define CAN_TRIG_CFG_TTPTR_SET(x) (((uint16_t)(x) << CAN_TRIG_CFG_TTPTR_SHIFT) & CAN_TRIG_CFG_TTPTR_MASK)
#define CAN_TRIG_CFG_TTPTR_GET(x) (((uint16_t)(x) & CAN_TRIG_CFG_TTPTR_MASK) >> CAN_TRIG_CFG_TTPTR_SHIFT)

/* Bitfield definition for register: TT_TRIG */
/*
 * TT_TRIG (RW)
 *
 * Trigger Time
 * TT_TRIG(15:0) defines the cycle time for a trigger.
 * For a transmission trigger theearliest point of transmission of the SOF of the appropriate frame will be TT_TRIG+1.
 */
#define CAN_TT_TRIG_TT_TRIG_MASK (0xFFFFU)
#define CAN_TT_TRIG_TT_TRIG_SHIFT (0U)
#define CAN_TT_TRIG_TT_TRIG_SET(x) (((uint16_t)(x) << CAN_TT_TRIG_TT_TRIG_SHIFT) & CAN_TT_TRIG_TT_TRIG_MASK)
#define CAN_TT_TRIG_TT_TRIG_GET(x) (((uint16_t)(x) & CAN_TT_TRIG_TT_TRIG_MASK) >> CAN_TT_TRIG_TT_TRIG_SHIFT)

/* Bitfield definition for register: TT_WTRIG */
/*
 * TT_WTRIG (RW)
 *
 * Watch Trigger Time
 * TT_WTRIG(15:0) defines the cycle time for a watch trigger. The initial watch trigger isthe maximum cycle time 0xffff.
 */
#define CAN_TT_WTRIG_TT_WTRIG_MASK (0xFFFFU)
#define CAN_TT_WTRIG_TT_WTRIG_SHIFT (0U)
#define CAN_TT_WTRIG_TT_WTRIG_SET(x) (((uint16_t)(x) << CAN_TT_WTRIG_TT_WTRIG_SHIFT) & CAN_TT_WTRIG_TT_WTRIG_MASK)
#define CAN_TT_WTRIG_TT_WTRIG_GET(x) (((uint16_t)(x) & CAN_TT_WTRIG_TT_WTRIG_MASK) >> CAN_TT_WTRIG_TT_WTRIG_SHIFT)



/* RBUF register group index macro definition */
#define CAN_RBUF_BUF0 (0UL)
#define CAN_RBUF_BUF1 (1UL)
#define CAN_RBUF_BUF2 (2UL)
#define CAN_RBUF_BUF3 (3UL)
#define CAN_RBUF_BUF4 (4UL)
#define CAN_RBUF_BUF5 (5UL)
#define CAN_RBUF_BUF6 (6UL)
#define CAN_RBUF_BUF7 (7UL)
#define CAN_RBUF_BUF8 (8UL)
#define CAN_RBUF_BUF9 (9UL)
#define CAN_RBUF_BUF10 (10UL)
#define CAN_RBUF_BUF11 (11UL)
#define CAN_RBUF_BUF12 (12UL)
#define CAN_RBUF_BUF13 (13UL)
#define CAN_RBUF_BUF14 (14UL)
#define CAN_RBUF_BUF15 (15UL)
#define CAN_RBUF_BUF16 (16UL)
#define CAN_RBUF_BUF17 (17UL)
#define CAN_RBUF_BUF18 (18UL)
#define CAN_RBUF_BUF19 (19UL)

/* TBUF register group index macro definition */
#define CAN_TBUF_BUF0 (0UL)
#define CAN_TBUF_BUF1 (1UL)
#define CAN_TBUF_BUF2 (2UL)
#define CAN_TBUF_BUF3 (3UL)
#define CAN_TBUF_BUF4 (4UL)
#define CAN_TBUF_BUF5 (5UL)
#define CAN_TBUF_BUF6 (6UL)
#define CAN_TBUF_BUF7 (7UL)
#define CAN_TBUF_BUF8 (8UL)
#define CAN_TBUF_BUF9 (9UL)
#define CAN_TBUF_BUF10 (10UL)
#define CAN_TBUF_BUF11 (11UL)
#define CAN_TBUF_BUF12 (12UL)
#define CAN_TBUF_BUF13 (13UL)
#define CAN_TBUF_BUF14 (14UL)
#define CAN_TBUF_BUF15 (15UL)
#define CAN_TBUF_BUF16 (16UL)
#define CAN_TBUF_BUF17 (17UL)

/* TTS register group index macro definition */
#define CAN_TTS_WRD0 (0UL)
#define CAN_TTS_WRD1 (1UL)


#endif /* HPM_CAN_H */
