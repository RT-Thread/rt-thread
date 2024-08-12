/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_LIN_H
#define HPM_LIN_H

typedef struct {
    __RW uint32_t DATABYTE[8];                 /* 0x0 - 0x1C: data byte */
    __RW uint32_t CONTROL;                     /* 0x20: control register */
    __R  uint32_t STATE;                       /* 0x24: state register */
    __R  uint32_t ERROR;                       /* 0x28: error register */
    __RW uint32_t DATA_LEN;                    /* 0x2C: data lenth register */
    __RW uint32_t BAUDRATE_CTL_LOW;            /* 0x30: baudrate control low register */
    __RW uint32_t BARDRATE_CTL_HIGH;           /* 0x34: baudrate control high register */
    __RW uint32_t ID;                          /* 0x38: id register */
    __RW uint32_t TV;                          /* 0x3C: timeout control register */
} LIN_Type;


/* Bitfield definition for register array: DATABYTE */
/*
 * DATA_BYTE (RW)
 *
 * data byte
 */
#define LIN_DATABYTE_DATA_BYTE_MASK (0xFFU)
#define LIN_DATABYTE_DATA_BYTE_SHIFT (0U)
#define LIN_DATABYTE_DATA_BYTE_SET(x) (((uint32_t)(x) << LIN_DATABYTE_DATA_BYTE_SHIFT) & LIN_DATABYTE_DATA_BYTE_MASK)
#define LIN_DATABYTE_DATA_BYTE_GET(x) (((uint32_t)(x) & LIN_DATABYTE_DATA_BYTE_MASK) >> LIN_DATABYTE_DATA_BYTE_SHIFT)

/* Bitfield definition for register: CONTROL */
/*
 * STOP (WO)
 *
 * slave only. Write 1 when the Host determin do not response to the data request according to a unkown ID
 */
#define LIN_CONTROL_STOP_MASK (0x80U)
#define LIN_CONTROL_STOP_SHIFT (7U)
#define LIN_CONTROL_STOP_SET(x) (((uint32_t)(x) << LIN_CONTROL_STOP_SHIFT) & LIN_CONTROL_STOP_MASK)
#define LIN_CONTROL_STOP_GET(x) (((uint32_t)(x) & LIN_CONTROL_STOP_MASK) >> LIN_CONTROL_STOP_SHIFT)

/*
 * SLEEP (RW)
 *
 * The bit is used by the LIN core to determine whether the LIN bus is in sleep mode or not. Set this bit after sending or receiving a Sleep Mode frame or if a bus idle timeout interrupt is requested or if after a wakeup request there is no response from the master and a timeout is signaled. The bit will be automatically reset by the LIN core.
 */
#define LIN_CONTROL_SLEEP_MASK (0x40U)
#define LIN_CONTROL_SLEEP_SHIFT (6U)
#define LIN_CONTROL_SLEEP_SET(x) (((uint32_t)(x) << LIN_CONTROL_SLEEP_SHIFT) & LIN_CONTROL_SLEEP_MASK)
#define LIN_CONTROL_SLEEP_GET(x) (((uint32_t)(x) & LIN_CONTROL_SLEEP_MASK) >> LIN_CONTROL_SLEEP_SHIFT)

/*
 * TRANSMIT (RW)
 *
 * 1: transmit operation 0: receive operation
 */
#define LIN_CONTROL_TRANSMIT_MASK (0x20U)
#define LIN_CONTROL_TRANSMIT_SHIFT (5U)
#define LIN_CONTROL_TRANSMIT_SET(x) (((uint32_t)(x) << LIN_CONTROL_TRANSMIT_SHIFT) & LIN_CONTROL_TRANSMIT_MASK)
#define LIN_CONTROL_TRANSMIT_GET(x) (((uint32_t)(x) & LIN_CONTROL_TRANSMIT_MASK) >> LIN_CONTROL_TRANSMIT_SHIFT)

/*
 * DATA_ACK (RW)
 *
 * slave only. Write 1 after handling a data request interrupt
 */
#define LIN_CONTROL_DATA_ACK_MASK (0x10U)
#define LIN_CONTROL_DATA_ACK_SHIFT (4U)
#define LIN_CONTROL_DATA_ACK_SET(x) (((uint32_t)(x) << LIN_CONTROL_DATA_ACK_SHIFT) & LIN_CONTROL_DATA_ACK_MASK)
#define LIN_CONTROL_DATA_ACK_GET(x) (((uint32_t)(x) & LIN_CONTROL_DATA_ACK_MASK) >> LIN_CONTROL_DATA_ACK_SHIFT)

/*
 * RESET_INT (WO)
 *
 * write 1 to reset the int bit in the status register and the interrupt request output of LIN
 */
#define LIN_CONTROL_RESET_INT_MASK (0x8U)
#define LIN_CONTROL_RESET_INT_SHIFT (3U)
#define LIN_CONTROL_RESET_INT_SET(x) (((uint32_t)(x) << LIN_CONTROL_RESET_INT_SHIFT) & LIN_CONTROL_RESET_INT_MASK)
#define LIN_CONTROL_RESET_INT_GET(x) (((uint32_t)(x) & LIN_CONTROL_RESET_INT_MASK) >> LIN_CONTROL_RESET_INT_SHIFT)

/*
 * RESET_ERROR (WO)
 *
 * assert 1 to reset the error bits in status register and error register. A read access to this bit delivers always the value 0
 */
#define LIN_CONTROL_RESET_ERROR_MASK (0x4U)
#define LIN_CONTROL_RESET_ERROR_SHIFT (2U)
#define LIN_CONTROL_RESET_ERROR_SET(x) (((uint32_t)(x) << LIN_CONTROL_RESET_ERROR_SHIFT) & LIN_CONTROL_RESET_ERROR_MASK)
#define LIN_CONTROL_RESET_ERROR_GET(x) (((uint32_t)(x) & LIN_CONTROL_RESET_ERROR_MASK) >> LIN_CONTROL_RESET_ERROR_SHIFT)

/*
 * WAKEUP_REQ (RW)
 *
 * wakeup request. Assert to terminate the Sleep mode of the LIN bus. The bit will be reset by core
 */
#define LIN_CONTROL_WAKEUP_REQ_MASK (0x2U)
#define LIN_CONTROL_WAKEUP_REQ_SHIFT (1U)
#define LIN_CONTROL_WAKEUP_REQ_SET(x) (((uint32_t)(x) << LIN_CONTROL_WAKEUP_REQ_SHIFT) & LIN_CONTROL_WAKEUP_REQ_MASK)
#define LIN_CONTROL_WAKEUP_REQ_GET(x) (((uint32_t)(x) & LIN_CONTROL_WAKEUP_REQ_MASK) >> LIN_CONTROL_WAKEUP_REQ_SHIFT)

/*
 * START_REQ (RW)
 *
 * master only. Set by host controller of a LIN master to start the LIN transmission. The core will reset the bit after the transmission is finished or an error is occurred
 */
#define LIN_CONTROL_START_REQ_MASK (0x1U)
#define LIN_CONTROL_START_REQ_SHIFT (0U)
#define LIN_CONTROL_START_REQ_SET(x) (((uint32_t)(x) << LIN_CONTROL_START_REQ_SHIFT) & LIN_CONTROL_START_REQ_MASK)
#define LIN_CONTROL_START_REQ_GET(x) (((uint32_t)(x) & LIN_CONTROL_START_REQ_MASK) >> LIN_CONTROL_START_REQ_SHIFT)

/* Bitfield definition for register: STATE */
/*
 * LIN_ACTIVE (RO)
 *
 * The bit indicates whether the LIN bus is active or not
 */
#define LIN_STATE_LIN_ACTIVE_MASK (0x80U)
#define LIN_STATE_LIN_ACTIVE_SHIFT (7U)
#define LIN_STATE_LIN_ACTIVE_GET(x) (((uint32_t)(x) & LIN_STATE_LIN_ACTIVE_MASK) >> LIN_STATE_LIN_ACTIVE_SHIFT)

/*
 * BUS_IDLE_TV (RO)
 *
 * slave only. This bit is set by LIN core if bit sleep  is not set and no bus activity is detected for 4s
 */
#define LIN_STATE_BUS_IDLE_TV_MASK (0x40U)
#define LIN_STATE_BUS_IDLE_TV_SHIFT (6U)
#define LIN_STATE_BUS_IDLE_TV_GET(x) (((uint32_t)(x) & LIN_STATE_BUS_IDLE_TV_MASK) >> LIN_STATE_BUS_IDLE_TV_SHIFT)

/*
 * ABORTED (RO)
 *
 * slave only. This bit is set by LIN core slave if a transmission is aborted after the bneginning of the data field due to a timeout or bit error.
 */
#define LIN_STATE_ABORTED_MASK (0x20U)
#define LIN_STATE_ABORTED_SHIFT (5U)
#define LIN_STATE_ABORTED_GET(x) (((uint32_t)(x) & LIN_STATE_ABORTED_MASK) >> LIN_STATE_ABORTED_SHIFT)

/*
 * DATA_REQ (RO)
 *
 * slave only. Sets after receiving the identifier and requests an interrupt to the host controller.
 */
#define LIN_STATE_DATA_REQ_MASK (0x10U)
#define LIN_STATE_DATA_REQ_SHIFT (4U)
#define LIN_STATE_DATA_REQ_GET(x) (((uint32_t)(x) & LIN_STATE_DATA_REQ_MASK) >> LIN_STATE_DATA_REQ_SHIFT)

/*
 * INT (RO)
 *
 * set when request an interrupt. Reset by reset_int
 */
#define LIN_STATE_INT_MASK (0x8U)
#define LIN_STATE_INT_SHIFT (3U)
#define LIN_STATE_INT_GET(x) (((uint32_t)(x) & LIN_STATE_INT_MASK) >> LIN_STATE_INT_SHIFT)

/*
 * ERROR (RO)
 *
 * set when detecte an error, clear by reset_error
 */
#define LIN_STATE_ERROR_MASK (0x4U)
#define LIN_STATE_ERROR_SHIFT (2U)
#define LIN_STATE_ERROR_GET(x) (((uint32_t)(x) & LIN_STATE_ERROR_MASK) >> LIN_STATE_ERROR_SHIFT)

/*
 * WAKEUP (RO)
 *
 * set when transmitting a wakeup signal or when received a wakeup signal. Clear when reset_error bit is 1
 */
#define LIN_STATE_WAKEUP_MASK (0x2U)
#define LIN_STATE_WAKEUP_SHIFT (1U)
#define LIN_STATE_WAKEUP_GET(x) (((uint32_t)(x) & LIN_STATE_WAKEUP_MASK) >> LIN_STATE_WAKEUP_SHIFT)

/*
 * COMPLETE (RO)
 *
 * set after a transmission has been successful finished and it will reset at the start of a transmission.
 */
#define LIN_STATE_COMPLETE_MASK (0x1U)
#define LIN_STATE_COMPLETE_SHIFT (0U)
#define LIN_STATE_COMPLETE_GET(x) (((uint32_t)(x) & LIN_STATE_COMPLETE_MASK) >> LIN_STATE_COMPLETE_SHIFT)

/* Bitfield definition for register: ERROR */
/*
 * PARITY_ERROR (RO)
 *
 * slave only. identifier parity error
 */
#define LIN_ERROR_PARITY_ERROR_MASK (0x8U)
#define LIN_ERROR_PARITY_ERROR_SHIFT (3U)
#define LIN_ERROR_PARITY_ERROR_GET(x) (((uint32_t)(x) & LIN_ERROR_PARITY_ERROR_MASK) >> LIN_ERROR_PARITY_ERROR_SHIFT)

/*
 * TIMEOUT (RO)
 *
 * timeout error. The master detects a timeout error if it is expecting data from the bus but no slave does respond. The slave detects a timeout error if it is requesting a data acknowledge to the host controller. The slave detects a timeout if it has transmitted a wakeup signal and it detects no sync field within 150ms
 */
#define LIN_ERROR_TIMEOUT_MASK (0x4U)
#define LIN_ERROR_TIMEOUT_SHIFT (2U)
#define LIN_ERROR_TIMEOUT_GET(x) (((uint32_t)(x) & LIN_ERROR_TIMEOUT_MASK) >> LIN_ERROR_TIMEOUT_SHIFT)

/*
 * CHK_ERROR (RO)
 *
 * checksum error
 */
#define LIN_ERROR_CHK_ERROR_MASK (0x2U)
#define LIN_ERROR_CHK_ERROR_SHIFT (1U)
#define LIN_ERROR_CHK_ERROR_GET(x) (((uint32_t)(x) & LIN_ERROR_CHK_ERROR_MASK) >> LIN_ERROR_CHK_ERROR_SHIFT)

/*
 * BIT_ERROR (RO)
 *
 * bit error
 */
#define LIN_ERROR_BIT_ERROR_MASK (0x1U)
#define LIN_ERROR_BIT_ERROR_SHIFT (0U)
#define LIN_ERROR_BIT_ERROR_GET(x) (((uint32_t)(x) & LIN_ERROR_BIT_ERROR_MASK) >> LIN_ERROR_BIT_ERROR_SHIFT)

/* Bitfield definition for register: DATA_LEN */
/*
 * ENH_CHECK (RW)
 *
 * 1:enhence check mode
 */
#define LIN_DATA_LEN_ENH_CHECK_MASK (0x80U)
#define LIN_DATA_LEN_ENH_CHECK_SHIFT (7U)
#define LIN_DATA_LEN_ENH_CHECK_SET(x) (((uint32_t)(x) << LIN_DATA_LEN_ENH_CHECK_SHIFT) & LIN_DATA_LEN_ENH_CHECK_MASK)
#define LIN_DATA_LEN_ENH_CHECK_GET(x) (((uint32_t)(x) & LIN_DATA_LEN_ENH_CHECK_MASK) >> LIN_DATA_LEN_ENH_CHECK_SHIFT)

/*
 * DATA_LENGTH (RW)
 *
 * data length
 */
#define LIN_DATA_LEN_DATA_LENGTH_MASK (0xFU)
#define LIN_DATA_LEN_DATA_LENGTH_SHIFT (0U)
#define LIN_DATA_LEN_DATA_LENGTH_SET(x) (((uint32_t)(x) << LIN_DATA_LEN_DATA_LENGTH_SHIFT) & LIN_DATA_LEN_DATA_LENGTH_MASK)
#define LIN_DATA_LEN_DATA_LENGTH_GET(x) (((uint32_t)(x) & LIN_DATA_LEN_DATA_LENGTH_MASK) >> LIN_DATA_LEN_DATA_LENGTH_SHIFT)

/* Bitfield definition for register: BAUDRATE_CTL_LOW */
/*
 * BT_DIV_LOW (RW)
 *
 * bit div register 7:0
 */
#define LIN_BAUDRATE_CTL_LOW_BT_DIV_LOW_MASK (0xFFU)
#define LIN_BAUDRATE_CTL_LOW_BT_DIV_LOW_SHIFT (0U)
#define LIN_BAUDRATE_CTL_LOW_BT_DIV_LOW_SET(x) (((uint32_t)(x) << LIN_BAUDRATE_CTL_LOW_BT_DIV_LOW_SHIFT) & LIN_BAUDRATE_CTL_LOW_BT_DIV_LOW_MASK)
#define LIN_BAUDRATE_CTL_LOW_BT_DIV_LOW_GET(x) (((uint32_t)(x) & LIN_BAUDRATE_CTL_LOW_BT_DIV_LOW_MASK) >> LIN_BAUDRATE_CTL_LOW_BT_DIV_LOW_SHIFT)

/* Bitfield definition for register: BARDRATE_CTL_HIGH */
/*
 * PRESCL (RW)
 *
 * prescl register
 */
#define LIN_BARDRATE_CTL_HIGH_PRESCL_MASK (0xC0U)
#define LIN_BARDRATE_CTL_HIGH_PRESCL_SHIFT (6U)
#define LIN_BARDRATE_CTL_HIGH_PRESCL_SET(x) (((uint32_t)(x) << LIN_BARDRATE_CTL_HIGH_PRESCL_SHIFT) & LIN_BARDRATE_CTL_HIGH_PRESCL_MASK)
#define LIN_BARDRATE_CTL_HIGH_PRESCL_GET(x) (((uint32_t)(x) & LIN_BARDRATE_CTL_HIGH_PRESCL_MASK) >> LIN_BARDRATE_CTL_HIGH_PRESCL_SHIFT)

/*
 * BT_MUL (RW)
 *
 * bt_mul register
 */
#define LIN_BARDRATE_CTL_HIGH_BT_MUL_MASK (0x3EU)
#define LIN_BARDRATE_CTL_HIGH_BT_MUL_SHIFT (1U)
#define LIN_BARDRATE_CTL_HIGH_BT_MUL_SET(x) (((uint32_t)(x) << LIN_BARDRATE_CTL_HIGH_BT_MUL_SHIFT) & LIN_BARDRATE_CTL_HIGH_BT_MUL_MASK)
#define LIN_BARDRATE_CTL_HIGH_BT_MUL_GET(x) (((uint32_t)(x) & LIN_BARDRATE_CTL_HIGH_BT_MUL_MASK) >> LIN_BARDRATE_CTL_HIGH_BT_MUL_SHIFT)

/*
 * BT_DIV_HIGH (RW)
 *
 * bit div register 8
 */
#define LIN_BARDRATE_CTL_HIGH_BT_DIV_HIGH_MASK (0x1U)
#define LIN_BARDRATE_CTL_HIGH_BT_DIV_HIGH_SHIFT (0U)
#define LIN_BARDRATE_CTL_HIGH_BT_DIV_HIGH_SET(x) (((uint32_t)(x) << LIN_BARDRATE_CTL_HIGH_BT_DIV_HIGH_SHIFT) & LIN_BARDRATE_CTL_HIGH_BT_DIV_HIGH_MASK)
#define LIN_BARDRATE_CTL_HIGH_BT_DIV_HIGH_GET(x) (((uint32_t)(x) & LIN_BARDRATE_CTL_HIGH_BT_DIV_HIGH_MASK) >> LIN_BARDRATE_CTL_HIGH_BT_DIV_HIGH_SHIFT)

/* Bitfield definition for register: ID */
/*
 * ID (RW)
 *
 * id register
 */
#define LIN_ID_ID_MASK (0x3FU)
#define LIN_ID_ID_SHIFT (0U)
#define LIN_ID_ID_SET(x) (((uint32_t)(x) << LIN_ID_ID_SHIFT) & LIN_ID_ID_MASK)
#define LIN_ID_ID_GET(x) (((uint32_t)(x) & LIN_ID_ID_MASK) >> LIN_ID_ID_SHIFT)

/* Bitfield definition for register: TV */
/*
 * INITIAL_MODE (RW)
 *
 * initial_mode
 */
#define LIN_TV_INITIAL_MODE_MASK (0x80U)
#define LIN_TV_INITIAL_MODE_SHIFT (7U)
#define LIN_TV_INITIAL_MODE_SET(x) (((uint32_t)(x) << LIN_TV_INITIAL_MODE_SHIFT) & LIN_TV_INITIAL_MODE_MASK)
#define LIN_TV_INITIAL_MODE_GET(x) (((uint32_t)(x) & LIN_TV_INITIAL_MODE_MASK) >> LIN_TV_INITIAL_MODE_SHIFT)

/*
 * MASTER_MODE (RW)
 *
 * master_mode
 */
#define LIN_TV_MASTER_MODE_MASK (0x40U)
#define LIN_TV_MASTER_MODE_SHIFT (6U)
#define LIN_TV_MASTER_MODE_SET(x) (((uint32_t)(x) << LIN_TV_MASTER_MODE_SHIFT) & LIN_TV_MASTER_MODE_MASK)
#define LIN_TV_MASTER_MODE_GET(x) (((uint32_t)(x) & LIN_TV_MASTER_MODE_MASK) >> LIN_TV_MASTER_MODE_SHIFT)

/*
 * BUS_INACTIVITY_TIME (RW)
 *
 * slave only. LIN bus idle timeout register： 00-4s  01-6s  10-8s  11-10s
 */
#define LIN_TV_BUS_INACTIVITY_TIME_MASK (0xCU)
#define LIN_TV_BUS_INACTIVITY_TIME_SHIFT (2U)
#define LIN_TV_BUS_INACTIVITY_TIME_SET(x) (((uint32_t)(x) << LIN_TV_BUS_INACTIVITY_TIME_SHIFT) & LIN_TV_BUS_INACTIVITY_TIME_MASK)
#define LIN_TV_BUS_INACTIVITY_TIME_GET(x) (((uint32_t)(x) & LIN_TV_BUS_INACTIVITY_TIME_MASK) >> LIN_TV_BUS_INACTIVITY_TIME_SHIFT)

/*
 * WUP_REPEAT_TIME (RW)
 *
 * slave only. wakeup repeat interval time  00-180ms  01-200ms 10-220ms 11-240ms
 */
#define LIN_TV_WUP_REPEAT_TIME_MASK (0x3U)
#define LIN_TV_WUP_REPEAT_TIME_SHIFT (0U)
#define LIN_TV_WUP_REPEAT_TIME_SET(x) (((uint32_t)(x) << LIN_TV_WUP_REPEAT_TIME_SHIFT) & LIN_TV_WUP_REPEAT_TIME_MASK)
#define LIN_TV_WUP_REPEAT_TIME_GET(x) (((uint32_t)(x) & LIN_TV_WUP_REPEAT_TIME_MASK) >> LIN_TV_WUP_REPEAT_TIME_SHIFT)



/* DATABYTE register group index macro definition */
#define LIN_DATABYTE_DATA_BYTE0 (0UL)
#define LIN_DATABYTE_DATA_BYTE1 (1UL)
#define LIN_DATABYTE_DATA_BYTE2 (2UL)
#define LIN_DATABYTE_DATA_BYTE3 (3UL)
#define LIN_DATABYTE_DATA_BYTE4 (4UL)
#define LIN_DATABYTE_DATA_BYTE5 (5UL)
#define LIN_DATABYTE_DATA_BYTE6 (6UL)
#define LIN_DATABYTE_DATA_BYTE7 (7UL)


#endif /* HPM_LIN_H */
