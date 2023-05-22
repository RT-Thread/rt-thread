/**
    *****************************************************************************
    * @file     cmem7_i2c.h
    *
    * @brief    CMEM7 I2C header file
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#ifndef __CMEM7_I2C_H
#define __CMEM7_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "cmem7.h"
#include "cmem7_conf.h"


#define IS_I2C_ALL_PERIPH(PERIPH) (((PERIPH) == I2C0) || \
                                   ((PERIPH) == I2C1))

/** @defgroup I2C_Mode
  * @{
  */
#define I2C_Mode_Slave                  0
#define I2C_Mode_Master                 1
#define IS_I2C_MODE(MODE) (((MODE) == I2C_Mode_Slave) || \
                           ((MODE) == I2C_Mode_Master))
/**
  * @}
  */

/** @defgroup I2C_ADDR_WIDTH
  * @{
  */
#define I2C_ADDR_WIDTH_7BIT                  0
#define I2C_ADDR_WIDTH_10BIT                 1
#define IS_I2C_ADDR_WIDTH(WIDTH) (((WIDTH) == I2C_ADDR_WIDTH_7BIT) || \
                                  ((WIDTH) == I2C_ADDR_WIDTH_10BIT))
/**
  * @}
  */

/** @defgroup I2C_INT
  * @{
  */
#define I2C_INT_RX_FIFO_NOT_EMPTY      0x00000004       /*!< Can't be clear but read FIFO */
#define I2C_INT_RD_REQUEST             0x00000020     /*!< Slave was requested to send data */
#define I2C_INT_TX_ABORT               0x00000040     /*!< Error while sending data */
#define I2C_INT_RX_DONE                0x00000080     /*!< Slave sent all requested data */
#define I2C_INT_TX_DONE                0x00000100     /*!< Master accomplish to send all data */

#define I2C_INT_ALL                    (I2C_INT_RX_FIFO_NOT_EMPTY | \
                                                                                I2C_INT_RD_REQUEST | \
                                                                                I2C_INT_TX_ABORT | \
                                                                                I2C_INT_RX_DONE | \
                                                                                I2C_INT_TX_DONE)

#define IS_I2C_INT(INT)                (((INT) != 0) && (((INT) & ~I2C_INT_ALL) == 0))
/**
  * @}
  */

/** @defgroup I2C_STATUS
  * @{
  */
#define I2C_STATUS_RX_FIFO_NOT_EMPTY   0x00200000       /*!< Can't be clear but read FIFO */
#define I2C_STATUS_RD_REQUEST          0x01000000     /*!< Slave was requested to send data */
#define I2C_STATUS_TX_ABORT            0x02000000     /*!< Error while sending data */
#define I2C_STATUS_RX_DONE             0x04000000     /*!< Slave sent all requested data */
#define I2C_STATUS_TX_DONE             0x08000000     /*!< Master accomplish to send all data */

#define I2C_STATUS_ALL                 (I2C_STATUS_RX_FIFO_NOT_EMPTY | \
                                                                                I2C_STATUS_RD_REQUEST | \
                                                                                I2C_STATUS_TX_ABORT | \
                                                                                I2C_STATUS_RX_DONE | \
                                                                                I2C_STATUS_TX_DONE)

#define IS_I2C_STATUS(STATUS)          (((STATUS) != 0) && (((STATUS) & ~I2C_STATUS_ALL) == 0))
/**
  * @}
  */

/**
  * @brief  I2C timing structure
    */
typedef struct
{
  uint32_t I2C_Freq;                /*!< I2C frquency */

    uint16_t I2C_TsuDat;              /*!< nano second of TSU:DAT */
  uint16_t I2C_Tsetup;              /*!< nano second of THD:STA and TSU:STO */
  uint16_t I2C_Tbuf;                /*!< nano second of TBUF */
    uint16_t I2C_TsuSta;              /*!< nano second of TSU:STA */

    BOOL I2C_SdaFilterEn;             /*!< enabled flag of SDA filter */
    uint8_t I2C_SdaFilterSpike;       /*!< spikes of SDA filter */
    BOOL I2C_SclFilterEn;             /*!< enabled flag of SCL filter */
    uint8_t I2C_SclFilterSpike;       /*!< spikes of SCL filter */

} I2C_InitTimingDef;

/**
  * @brief  I2C initialization structure
    */
typedef struct
{
  uint8_t I2C_Mode;                 /*!< Specifies the I2C mode.
                                         This parameter can be a value of @ref I2C_mode */
    uint8_t I2C_AddressWidth;         /*!< 7- or 10-bits width address, ref as @ref I2C_ADDR_WIDTH */
    uint8_t I2C_Address;              /*!< 7- or 10-bits address */
    I2C_InitTimingDef* timing;        /*!< timing structure, null if don't set */
} I2C_InitTypeDef;

/**
  * @brief  I2C initialization
  * @note   This function should be called at first before any other interfaces.
    * @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
    * @param[in] init A pointer to structure I2C_InitTypeDef
  * @retval None
    */
void I2C_Init(I2C0_Type* I2Cx, I2C_InitTypeDef* I2C_Init);

/**
  * @brief  Enable or disable I2C.
    * @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
    * @param[in] Enable The bit indicates if the specific I2C is enable or not
  * @retval None
    */
void I2C_Enable(I2C0_Type* I2Cx, BOOL enable);

/**
  * @brief  Enable or disable I2C interrupt.
    * @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
    * @param[in] Int interrupt mask bits, which can be the combination of @ref I2C_Int
    * @param[in] Enable The bit indicates if specific interrupts are enable or not
  * @retval None
    */
void I2C_EnableInt(I2C0_Type* I2Cx, uint32_t Int, BOOL enable);

/**
  * @brief  Check specific interrupts are set or not
    * @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
    * @param[in] Int interrupt mask bits, which can be the combination of @ref I2C_Int
  * @retval BOOL The bit indicates if specific interrupts are enable or not
    */
BOOL I2C_GetIntStatus(I2C0_Type* I2Cx, uint32_t Int);

/**
  * @brief  Clear specific interrupts
    * @note   Specific interrupt clear will clear correspective status as well
    * @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
    * @param[in] Int interrupt mask bits, which can be the combination of @ref I2C_Int
  * @retval None
    */
void I2C_ClearInt(I2C0_Type* I2Cx, uint32_t Int);

/**
  * @brief  Check specific status are set or not
    * @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
    * @param[in] Status Status mask bits, which can be the combination of @ref I2C_STATUS
  * @retval BOOL The bit indicates if specific status are set or not
    */
BOOL I2C_GetStatus(I2C0_Type* I2Cx, uint32_t Status);

/**
  * @brief  Clear specific status
    * @note   Specific status clear will clear correspective interrupt as well
    * @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
    * @param[in] Status Status mask bits, which can be the combination of @ref I2C_STATUS
  * @retval None
    */
void I2C_ClearStatus(I2C0_Type* I2Cx, uint32_t Status);

/**
  * @brief  I2C send read request in master mode
    * @note   Users must call I2C_StopReq between 2 requests
    * @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
    * @param[in] size Expected data size to be read
  * @retval BOOL The bit indicates if read request to be sent is valid
    * @see      I2C_StopReq
    */
BOOL I2C_MasterReadReq(I2C0_Type* I2Cx, uint8_t size);

/**
  * @brief  Read data from I2C
    * @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
    * @param[in] size Expected data size to be read
    * @param[out] Data A user-allocated buffer to fetch data to be read
  * @retval uint8_t Actual read data size
    */
uint8_t I2C_ReadFifo(I2C0_Type* I2Cx, uint8_t size, uint8_t* data);

/**
  * @brief  I2C send write request in master or slave mode
    * @note   Users must call I2C_StopReq between 2 requests
    * @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
    * @param[in] size Expected data size to be written, includes the first data
    * @param[in] firstData The first data to be written
  * @retval BOOL The bit indicates if write request to be sent is valid
    * @see      I2C_StopReq
    */
BOOL I2C_WriteReq(I2C0_Type* I2Cx, uint8_t size, uint8_t firstData);

/**
  * @brief  Write data to I2C
    * @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
    * @param[in] size Expected data size to be written
    * @param[in] Data A pointer to the data to be written
  * @retval uint8_t Actual written data size
    */
uint8_t I2C_WriteFifo(I2C0_Type* I2Cx, uint8_t size, uint8_t* data);

/**
  * @brief  I2C stop request
    * @note   Users must call I2C_StopReq between 2 requests
    * @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
    * @retval BOOL The bit indicates if request is stopped.
    * @see      I2C_MasterReadReq I2C_WriteReq
    */
BOOL I2C_StopReq(I2C0_Type* I2Cx);

#ifdef __cplusplus
}
#endif

#endif /*__CMEM7_I2C_H */

