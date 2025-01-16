/*********************************************************************************************************//**
 * @file    ht32f5xxxx_i2c.h
 * @version $Rev:: 7698         $
 * @date    $Date:: 2024-04-15 #$
 * @brief   The header file of the I2C library.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F5XXXX_I2C_H
#define __HT32F5XXXX_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup I2C
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup I2C_Exported_Types I2C exported types
  * @{
  */

#if (LIBCFG_I2C_TWO_DEV_ADDR)
typedef u8 I2C_AddressTypeDef;
#else
typedef u16 I2C_AddressTypeDef;
#endif

typedef struct
{
  u8  I2C_GeneralCall;
  u8  I2C_AddressingMode;
  u8  I2C_Acknowledge;
  u8  I2C_SpeedOffset;  /* Offset value to reach real speed, recommended I2C_SpeedOffset = I2C PCLK/8000000 */
                        /* which based on 4.7K Pull up                                                      */
  u32 I2C_Speed;
  u16 I2C_OwnAddress;
} I2C_InitTypeDef;

#if (LIBCFG_I2C_TWO_DEV_ADDR)
typedef enum
{
  I2C_DEV_ADDR_0 = 0,
  I2C_DEV_ADDR_1
} I2C_ADDR_Enum;

#define IS_I2C_ADDR(x)  ((x == I2C_DEV_ADDR_0) || (x == I2C_DEV_ADDR_1))
#endif
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup I2C_Exported_Constants I2C exported constants
  * @{
  */
#define I2C_GENERALCALL_ENABLE                      ((u32)0x00000004)
#define I2C_GENERALCALL_DISABLE                     ((u32)0x00000000)

#define IS_I2C_GENERAL_CALL(CALL)                   ((CALL == I2C_GENERALCALL_ENABLE) || \
                                                     (CALL == I2C_GENERALCALL_DISABLE))

#define I2C_ADDRESSING_7BIT                         ((u32)0x00000000)
#if (LIBCFG_I2C_NO_10BIT_MODE)
#define IS_I2C_ACKNOWLEDGE_ADDRESS(ADDRESS)         ((ADDRESS == I2C_ADDRESSING_7BIT))
#else
#define I2C_ADDRESSING_10BIT                        ((u32)0x00000080)

#define IS_I2C_ACKNOWLEDGE_ADDRESS(ADDRESS)         ((ADDRESS == I2C_ADDRESSING_7BIT) || \
                                                     (ADDRESS == I2C_ADDRESSING_10BIT))
#endif

#define I2C_ACK_ENABLE                              ((u32)0x00000001)
#define I2C_ACK_DISABLE                             ((u32)0x00000000)

#define IS_I2C_ACKNOWLEDGE(ACKNOWLEDGE)             ((ACKNOWLEDGE == I2C_ACK_ENABLE) || \
                                                     (ACKNOWLEDGE == I2C_ACK_DISABLE))

#if (LIBCFG_I2C_TWO_DEV_ADDR)
#define I2C_DEV_ADDR0_ENABLE                        ((u32)0x00008000)
#define I2C_DEV_ADDR0_DISABLE                       ((u32)0x00000000)

#define IS_I2C_ADDR0_ENABLE(ADDR)                   ((ADDR == I2C_ADDR0_ENABLE) || \
                                                     (ADDR == I2C_ADDR0_DISABLE))

#define I2C_DEV_ADDR1_ENABLE                        ((u32)0x80000000)
#define I2C_DEV_ADDR1_DISABLE                       ((u32)0x00000000)

#define IS_I2C_ADDR1(ADDR)                          ((ADDR == I2C_ADDR1_ENABLE) || \
                                                     (ADDR == I2C_ADDR1_DISABLE))
#endif

#define I2C_INT_STA                                 ((u32)0x00000001)
#define I2C_INT_STO                                 ((u32)0x00000002)
#define I2C_INT_ADRS                                ((u32)0x00000004)
#define I2C_INT_GCS                                 ((u32)0x00000008)
#if (LIBCFG_I2C_NO_ARBLOS == 0)
#define I2C_INT_ARBLOS                              ((u32)0x00000100)
#endif
#define I2C_INT_RXNACK                              ((u32)0x00000200)
#define I2C_INT_BUSERR                              ((u32)0x00000400)
#define I2C_INT_TOUT                                ((u32)0x00000800)
#define I2C_INT_RXDNE                               ((u32)0x00010000)
#define I2C_INT_TXDE                                ((u32)0x00020000)
#define I2C_INT_RXBF                                ((u32)0x00040000)
#if (LIBCFG_I2C_NO_ARBLOS)
#define I2C_INT_ALL                                 ((u32)0x00070E0F)
#else
#define I2C_INT_ALL                                 ((u32)0x00070F0F)
#endif

#if (LIBCFG_I2C_NO_ARBLOS)
#define IS_I2C_INT(int)                             (((int & 0xFFF8F1F0) == 0x0) && (int != 0x0))
#else
#define IS_I2C_INT(int)                             (((int & 0xFFF8F0F0) == 0x0) && (int != 0x0))
#endif

#define I2C_MASTER_READ                             ((u32)0x00000400)
#define I2C_MASTER_WRITE                            ((u32)0x00000000)

#define IS_I2C_DIRECTION(DIRECTION)                 ((DIRECTION == I2C_MASTER_READ) || \
                                                     (DIRECTION == I2C_MASTER_WRITE))


#define I2C_REGISTER_CR                             ((u8)0x00)
#define I2C_REGISTER_IER                            ((u8)0x04)
#define I2C_REGISTER_ADDR                           ((u8)0x08)
#define I2C_REGISTER_SR                             ((u8)0x0C)
#define I2C_REGISTER_SHPGR                          ((u8)0x10)
#define I2C_REGISTER_SLPGR                          ((u8)0x14)
#define I2C_REGISTER_DR                             ((u8)0x18)
#define I2C_REGISTER_BFCLR                          ((u8)0x1C)
#define I2C_REGISTER_TAR                            ((u8)0x20)

#define IS_I2C_REGISTER(REGISTER)                   ((REGISTER == I2C_REGISTER_CR) || \
                                                     (REGISTER == I2C_REGISTER_IER) || \
                                                     (REGISTER == I2C_REGISTER_ADDR) || \
                                                     (REGISTER == I2C_REGISTER_SR) || \
                                                     (REGISTER == I2C_REGISTER_SHPGR) || \
                                                     (REGISTER == I2C_REGISTER_SLPGR) || \
                                                     (REGISTER == I2C_REGISTER_DR) || \
                                                     (REGISTER == I2C_REGISTER_BFCLR) || \
                                                     (REGISTER == I2C_REGISTER_TAR))


#define I2C_FLAG_STA                                ((u32)0x00000001)
#define I2C_FLAG_STO                                ((u32)0x00000002)
#define I2C_FLAG_ADRS                               ((u32)0x00000004)
#define I2C_FLAG_GCS                                ((u32)0x00000008)
#if (LIBCFG_I2C_NO_ARBLOS)
#define IS_FLAG_ARBLOS(x)                           (0)
#else
#define I2C_FLAG_ARBLOS                             ((u32)0x00000100)
#define IS_FLAG_ARBLOS(x)                           (x == I2C_FLAG_ARBLOS)
#endif
#define I2C_FLAG_RXNACK                             ((u32)0x00000200)
#define I2C_FLAG_BUSERR                             ((u32)0x00000400)
#define I2C_FLAG_TOUTF                              ((u32)0x00000800)
#define I2C_FLAG_RXDNE                              ((u32)0x00010000)
#define I2C_FLAG_TXDE                               ((u32)0x00020000)
#define I2C_FLAG_RXBF                               ((u32)0x00040000)
#define I2C_FLAG_BUSBUSY                            ((u32)0x00080000)
#define I2C_FLAG_MASTER                             ((u32)0x00100000)
#define I2C_FLAG_TXNRX                              ((u32)0x00200000)

#define IS_I2C_FLAG(FLAG)                           ((FLAG == I2C_FLAG_STA)    || \
                                                     (FLAG == I2C_FLAG_STO)    || \
                                                     (FLAG == I2C_FLAG_ADRS)   || \
                                                     (FLAG == I2C_FLAG_GCS)    || \
                                                     IS_FLAG_ARBLOS(FLAG)      || \
                                                     (FLAG == I2C_FLAG_RXNACK) || \
                                                     (FLAG == I2C_FLAG_BUSERR) || \
                                                     (FLAG == I2C_FLAG_TOUTF)  || \
                                                     (FLAG == I2C_FLAG_RXDNE)  || \
                                                     (FLAG == I2C_FLAG_TXDE)   || \
                                                     (FLAG == I2C_FLAG_RXBF)   || \
                                                     (FLAG == I2C_FLAG_BUSBUSY)|| \
                                                     (FLAG == I2C_FLAG_MASTER) || \
                                                     (FLAG == I2C_FLAG_TXNRX))

#define IS_I2C_CLEAR_FLAG(FLAG)                     (IS_FLAG_ARBLOS(FLAG)      || \
                                                     (FLAG == I2C_FLAG_RXNACK) || \
                                                     (FLAG == I2C_FLAG_BUSERR) || \
                                                     (FLAG == I2C_FLAG_TOUTF))

#define I2C_MASTER_SEND_START                       ((u32)0x00180001)
#define I2C_MASTER_RECEIVER_MODE                    ((u32)0x00180004)
#define I2C_MASTER_TRANSMITTER_MODE                 ((u32)0x003A0004)
#define I2C_MASTER_RX_NOT_EMPTY                     ((u32)0x00190000)
#define I2C_MASTER_RX_NOT_EMPTY_NOBUSY              ((u32)0x00010000)
#define I2C_MASTER_TX_EMPTY                         ((u32)0x003A0000)
#define I2C_MASTER_RX_BUFFER_FULL                   ((u32)0x001D0000)
#define I2C_SLAVE_ACK_TRANSMITTER_ADDRESS           ((u32)0x002A0004)
#define I2C_SLAVE_ACK_RECEIVER_ADDRESS              ((u32)0x00080004)
#define I2C_SLAVE_ACK_GCALL_ADDRESS                 ((u32)0x00080008)
#define I2C_SLAVE_RX_NOT_EMPTY                      ((u32)0x00090000)
#define I2C_SLAVE_RX_NOT_EMPTY_STOP                 ((u32)0x00010002)
#define I2C_SLAVE_TX_EMPTY                          ((u32)0x002A0000)
#define I2C_SLAVE_RX_BUFFER_FULL                    ((u32)0x000D0000)
#define I2C_SLAVE_RECEIVED_NACK                     ((u32)0x00080200)
#define I2C_SLAVE_RECEIVED_NACK_STOP                ((u32)0x00000202)
#define I2C_SLAVE_STOP_DETECTED                     ((u32)0x00000002)


#define IS_I2C_STATUS(STATUS)                       ((STATUS == I2C_MASTER_SEND_START)             || \
                                                     (STATUS == I2C_MASTER_RECEIVER_MODE)          || \
                                                     (STATUS == I2C_MASTER_TRANSMITTER_MODE)       || \
                                                     (STATUS == I2C_MASTER_RX_NOT_EMPTY)           || \
                                                     (STATUS == I2C_MASTER_RX_NOT_EMPTY_NOBUSY)    || \
                                                     (STATUS == I2C_MASTER_TX_EMPTY)               || \
                                                     (STATUS == I2C_MASTER_RX_BUFFER_FULL)         || \
                                                     (STATUS == I2C_SLAVE_ACK_TRANSMITTER_ADDRESS) || \
                                                     (STATUS == I2C_SLAVE_ACK_RECEIVER_ADDRESS)    || \
                                                     (STATUS == I2C_SLAVE_ACK_GCALL_ADDRESS)       || \
                                                     (STATUS == I2C_SLAVE_RX_NOT_EMPTY)            || \
                                                     (STATUS == I2C_SLAVE_RX_NOT_EMPTY_STOP)       || \
                                                     (STATUS == I2C_SLAVE_TX_EMPTY)                || \
                                                     (STATUS == I2C_SLAVE_RX_BUFFER_FULL)          || \
                                                     (STATUS == I2C_SLAVE_RECEIVED_NACK)           || \
                                                     (STATUS == I2C_SLAVE_RECEIVED_NACK_STOP)      || \
                                                     (STATUS == I2C_SLAVE_STOP_DETECTED))

#if (LIBCFG_PDMA)
#define I2C_PDMAREQ_TX                              ((u32)0x00000100)
#define I2C_PDMAREQ_RX                              ((u32)0x00000200)

#define IS_I2C_PDMA_REQ(REQ)                        (((REQ & 0xFFFFFCFF) == 0x0) && (REQ != 0x0))
#endif

#define I2C_PRESCALER_1                             ((u32)0x00000000)
#define I2C_PRESCALER_2                             ((u32)0x00010000)
#define I2C_PRESCALER_4                             ((u32)0x00020000)
#define I2C_PRESCALER_8                             ((u32)0x00030000)
#if (LIBCFG_I2C_PRESCALER_2BIT == 0)
#define I2C_PRESCALER_16                            ((u32)0x00040000)
#define I2C_PRESCALER_32                            ((u32)0x00050000)
#define I2C_PRESCALER_64                            ((u32)0x00060000)
#define I2C_PRESCALER_128                           ((u32)0x00070000)
#endif

#if (LIBCFG_I2C_PRESCALER_2BIT)
#define IS_I2C_PRESCALER(PRESCALER)                 ((PRESCALER == I2C_PRESCALER_1) || \
                                                     (PRESCALER == I2C_PRESCALER_2) || \
                                                     (PRESCALER == I2C_PRESCALER_4) || \
                                                     (PRESCALER == I2C_PRESCALER_8))
#else
#define IS_I2C_PRESCALER(PRESCALER)                 ((PRESCALER == I2C_PRESCALER_1)  || \
                                                     (PRESCALER == I2C_PRESCALER_2)  || \
                                                     (PRESCALER == I2C_PRESCALER_4)  || \
                                                     (PRESCALER == I2C_PRESCALER_8)  || \
                                                     (PRESCALER == I2C_PRESCALER_16) || \
                                                     (PRESCALER == I2C_PRESCALER_32) || \
                                                     (PRESCALER == I2C_PRESCALER_64) || \
                                                     (PRESCALER == I2C_PRESCALER_128))
#endif

#if (LIBCFG_I2C_NO_ADDR_MASK == 0)
#define I2C_MASKBIT_0                               ((u32)0x00000001)
#define I2C_MASKBIT_1                               ((u32)0x00000002)
#define I2C_MASKBIT_2                               ((u32)0x00000004)
#define I2C_MASKBIT_3                               ((u32)0x00000008)
#define I2C_MASKBIT_4                               ((u32)0x00000010)
#define I2C_MASKBIT_5                               ((u32)0x00000020)
#define I2C_MASKBIT_6                               ((u32)0x00000040)
#define I2C_MASKBIT_7                               ((u32)0x00000080)
#define I2C_MASKBIT_8                               ((u32)0x00000100)
#define I2C_MASKBIT_9                               ((u32)0x00000200)


#define IS_I2C_ADDRESS_MASK(MASK)                   ((MASK == I2C_MASKBIT_0) || \
                                                     (MASK == I2C_MASKBIT_1) || \
                                                     (MASK == I2C_MASKBIT_2) || \
                                                     (MASK == I2C_MASKBIT_3) || \
                                                     (MASK == I2C_MASKBIT_4) || \
                                                     (MASK == I2C_MASKBIT_5) || \
                                                     (MASK == I2C_MASKBIT_6) || \
                                                     (MASK == I2C_MASKBIT_7) || \
                                                     (MASK == I2C_MASKBIT_8) || \
                                                     (MASK == I2C_MASKBIT_9))
#endif

#define IS_I2C(x)                                   (IS_I2C0(x) || IS_I2C1(x) || IS_I2C2(x))
#define IS_I2C0(x)                                  (x == HT_I2C0)

#if (LIBCFG_I2C1)
#define IS_I2C1(x)                                  (x == HT_I2C1)
#else
#define IS_I2C1(x)                                  (0)
#endif

#if (LIBCFG_I2C2)
#define IS_I2C2(x)                                  (x == HT_I2C2)
#else
#define IS_I2C2(x)                                  (0)
#endif

#if (LIBCFG_I2C_NO_10BIT_MODE)
#define IS_I2C_ADDRESS(ADDRESS)                     (ADDRESS <= 0x7F)
#else
#define IS_I2C_ADDRESS(ADDRESS)                     (ADDRESS <= 0x3FF)
#endif

#define IS_I2C_SPEED(SPEED)                         ((SPEED >= 1) && (SPEED <= 1000000))

#define IS_I2C_SCL_HIGH(HIGH)                       (HIGH <= 0xFFFF)

#define IS_I2C_SCL_LOW(LOW)                         (LOW <= 0xFFFF)

#if (LIBCFG_I2C_TOUT_COUNT_8BIT)
#define IS_I2C_TIMEOUT(TIMEOUT)                     (TIMEOUT <= 0xFF)
#else
#define IS_I2C_TIMEOUT(TIMEOUT)                     (TIMEOUT <= 0xFFFF)
#endif

#define SEQ_FILTER_DISABLE                          ((u32)0x00000000)
#define SEQ_FILTER_1_PCLK                           ((u32)0x00004000)
#define SEQ_FILTER_2_PCLK                           ((u32)0x00008000)

#define IS_I2C_SEQ_FILTER_MASK(CONFIG)              ((CONFIG == SEQ_FILTER_DISABLE) || \
                                                     (CONFIG == SEQ_FILTER_1_PCLK)  || \
                                                     (CONFIG == SEQ_FILTER_2_PCLK))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup I2C_Exported_Functions I2C exported functions
  * @{
  */
void I2C_DeInit(HT_I2C_TypeDef* I2Cx);
void I2C_Init(HT_I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStructure);
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStructure);
void I2C_Cmd(HT_I2C_TypeDef* I2Cx, ControlStatus NewState);
void I2C_GenerateSTOP(HT_I2C_TypeDef* I2Cx);
void I2C_IntConfig(HT_I2C_TypeDef* I2Cx, u32 I2C_Int, ControlStatus NewState);
void I2C_GeneralCallCmd(HT_I2C_TypeDef* I2Cx, ControlStatus NewState);
void I2C_AckCmd(HT_I2C_TypeDef* I2Cx, ControlStatus NewState);
void I2C_SetOwnAddress(HT_I2C_TypeDef* I2Cx, I2C_AddressTypeDef I2C_Address);
#if (LIBCFG_I2C_TWO_DEV_ADDR)
void I2C_SetOwnAddress1(HT_I2C_TypeDef* I2Cx, I2C_AddressTypeDef I2C_Address);
void I2C_OwnAddressCmd(HT_I2C_TypeDef* I2Cx, I2C_ADDR_Enum Address, ControlStatus NewState);
#endif
void I2C_TargetAddressConfig(HT_I2C_TypeDef* I2Cx, I2C_AddressTypeDef I2C_Address, u32 I2C_Direction);
void I2C_SendData(HT_I2C_TypeDef* I2Cx, u8 I2C_Data);
u8 I2C_ReceiveData(HT_I2C_TypeDef* I2Cx);
u32 I2C_ReadRegister(HT_I2C_TypeDef* I2Cx, u8 I2C_Register);
FlagStatus I2C_GetFlagStatus(HT_I2C_TypeDef* I2Cx, u32 I2C_Flag);
ErrStatus I2C_CheckStatus(HT_I2C_TypeDef* I2Cx, u32 I2C_Status);
void I2C_ClearFlag(HT_I2C_TypeDef* I2Cx, u32 I2C_Flag);
void I2C_SetSCLHighPeriod(HT_I2C_TypeDef* I2Cx, u32 I2C_HighPeriod);
void I2C_SetSCLLowPeriod(HT_I2C_TypeDef* I2Cx, u32 I2C_LowPeriod);
#if (LIBCFG_PDMA)
void I2C_PDMACmd(HT_I2C_TypeDef* I2Cx, u32 I2C_PDMAREQ, ControlStatus NewState);
void I2C_PDMANACKCmd(HT_I2C_TypeDef* I2Cx, ControlStatus NewState);
#endif
void I2C_TimeOutCmd(HT_I2C_TypeDef* I2Cx, ControlStatus NewState);
void I2C_SetTimeOutValue(HT_I2C_TypeDef* I2Cx, u32 I2C_Timeout);
void I2C_SetTimeOutPrescaler(HT_I2C_TypeDef* I2Cx, u32 I2C_Prescaler);
#if (LIBCFG_I2C_NO_ADDR_MASK == 0)
void I2C_AddressMaskConfig(HT_I2C_TypeDef* I2Cx, u32 I2C_Mask);
#endif
u16 I2C_GetAddressBuffer(HT_I2C_TypeDef* I2Cx);
void I2C_CombFilterCmd(HT_I2C_TypeDef* I2Cx, ControlStatus NewState);
void I2C_SequentialFilterConfig(HT_I2C_TypeDef* I2Cx, u32 Seq_Filter_Select);
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
