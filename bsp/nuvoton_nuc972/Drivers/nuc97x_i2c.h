/*
 * File      : nuc97x_i2c.h
 * This file is part of RT-Thread RTOS
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/05/28     Urey         first implementation
 */
#ifndef PLATFORM_NUC97X_I2C_H_
#define PLATFORM_NUC97X_I2C_H_

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------*/
/* marco, type and constant definitions    */
/*-----------------------------------------*/
#define I2C_NUMBER              2
#define I2C_MAX_BUF_LEN         128

#define I2C_INPUT_CLOCK         33000           /* 33 000 KHz */

/*-----------------------------------------*/
/* global interface variables declarations */
/*-----------------------------------------*/
/*
    bit map in CMDR
*/
#define I2C_CMD_START           0x10
#define I2C_CMD_STOP            0x08
#define I2C_CMD_READ            0x04
#define I2C_CMD_WRITE           0x02
#define I2C_CMD_NACK            0x01

/*
    for transfer use
*/
#define I2C_WRITE               0x00
#define I2C_READ                0x01

/*
    i2c register offset
*/
typedef struct
{
    __IO int32_t CSR     ;  /*!< (0x00) Control and Status Register */
    __IO int32_t DIVIDER ;  /*!< (0x04) Clock Prescale Register */
    __IO int32_t CMDR    ;  /*!< (0x08) Command Register */
    __IO int32_t SWR     ;  /*!< (0x0C) Software Mode Control Register */
    __IO int32_t RXR     ;  /*!< (0x10) Data Receive Register */
    __IO int32_t TXR     ;  /*!< (0x14) Data Transmit Register */
}I2C_Typedef;

#define I2C0    ((I2C_Typedef *)I2C0_BA)
#define I2C1    ((I2C_Typedef *)I2C1_BA)

/// @endcond HIDDEN_SYMBOLS

/*
    ioctl commands
*/
#define I2C_IOC_SET_DEV_ADDRESS     0  /*!< Set device slave address */
#define I2C_IOC_SET_SUB_ADDRESS     1  /*!< Set sub address */
#define I2C_IOC_SET_SPEED           2  /*!< Set I2C interface speed */

/*
    error code
*/
#define I2C_ERR_ID                  0xFFFF1100           /*!< I2C library ID                  */
#define I2C_ERR_NOERROR             (0x00)               /*!< No error                        */
#define I2C_ERR_LOSTARBITRATION     (0x01 | I2C_ERR_ID)  /*!< Arbitration lost error          */
#define I2C_ERR_BUSBUSY             (0x02 | I2C_ERR_ID)  /*!< Bus busy error                  */
#define I2C_ERR_NACK                (0x03 | I2C_ERR_ID)  /*!< data transfer error             */
#define I2C_ERR_SLAVENACK           (0x04 | I2C_ERR_ID)  /*!< slave not respond after address */
#define I2C_ERR_NODEV               (0x05 | I2C_ERR_ID)  /*!< Wrong device                    */
#define I2C_ERR_BUSY                (0x06 | I2C_ERR_ID)  /*!< Device busy                     */
#define I2C_ERR_IO                  (0x07 | I2C_ERR_ID)  /*!< Interface not open              */
#define I2C_ERR_NOTTY               (0x08 | I2C_ERR_ID)  /*!< Command not support             */


#define I2C_TIMEOUT     100


/*-----------------------------------------*/
/* interface function declarations         */
/*-----------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_NUC97X_I2C_H_ */
