/**
    *****************************************************************************
    * @file     cmem7_can.h
    *
    * @brief    CMEM7 CAN header file
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

#ifndef __CMEM7_CAN_H
#define __CMEM7_CAN_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "cmem7.h"
#include "cmem7_conf.h"

#define IS_CAN_ALL_PERIPH(PERIPH) (((PERIPH) == CAN0) || \
                                   ((PERIPH) == CAN1))

/** @defgroup CAN_FLT
  * @{
  */
#define CAN_FLT_STANDARD_SINGLE    0x00000000
#define CAN_FLT_STANDARD_DUAL      0x00000001
#define CAN_FLT_EXTENDED_SINGLE    0x00000002
#define CAN_FLT_EXTENDED_DUAL      0x00000003

#define IS_CAN_FLT_TYPE(FILTER)    (((FILTER) == CAN_FLT_STANDARD_SINGLE) || \
                                    ((FILTER) == CAN_FLT_STANDARD_DUAL) || \
                                                                        ((FILTER) == CAN_FLT_EXTENDED_SINGLE) || \
                                    ((FILTER) == CAN_FLT_EXTENDED_DUAL))

#define IS_CAN_FLT_SINGLE(FILTER)  (((FILTER) == CAN_FLT_STANDARD_SINGLE) || \
                                    ((FILTER) == CAN_FLT_EXTENDED_SINGLE))

#define IS_CAN_FLT_DUAL(FILTER)    (IS_CAN_FLT_TYPE(FILTER) && \
                                    !IS_CAN_FLT_SINGLE(FILTER))

/**
  * @}
  */

/** @defgroup CAN_CDR_DIV
  * @{
  */
#define CAN_CDR_DIV_1_2            0x0
#define CAN_CDR_DIV_1_4            0x1
#define CAN_CDR_DIV_1_6            0x2
#define CAN_CDR_DIV_1_8            0x3
#define CAN_CDR_DIV_1_10           0x4
#define CAN_CDR_DIV_1_12           0x5
#define CAN_CDR_DIV_1_14           0x6
#define CAN_CDR_DIV_1_1            0x7

#define IS_CAN_CDR_DIV(DIV)        (((DIV) == CAN_CDR_DIV_1_2) || \
                                    ((DIV) == CAN_CDR_DIV_1_4) || \
                                                                        ((DIV) == CAN_CDR_DIV_1_6) || \
                                                                        ((DIV) == CAN_CDR_DIV_1_8) || \
                                                                        ((DIV) == CAN_CDR_DIV_1_10) || \
                                                                        ((DIV) == CAN_CDR_DIV_1_12) || \
                                                                        ((DIV) == CAN_CDR_DIV_1_14) || \
                                                                        ((DIV) == CAN_CDR_DIV_1_1))
/**
  * @}
  */

/** @defgroup CAN_INT
  * @{
  */
#define CAN_INT_RBNF               0x01
#define CAN_INT_TB_UNLOCK          0x02
#define CAN_INT_ERR                0x04
#define CAN_INT_DATA_OVERRUN       0x08
#define CAN_INT_WAKEUP             0x10
#define CAN_INT_ERR_PASSIVE        0x20
#define CAN_INT_ARBITRATION_LOST   0x40
#define CAN_INT_BUS_ERR            0x80
#define CAN_INT_All                0xFF

#define IS_CAN_INT(INT)            (((INT) != 0) && (((INT) & ~CAN_INT_All) == 0))
/**
  * @}
  */

/**
  * @brief  CAN standard filter structure
    */
typedef struct {
    uint16_t  ID28_18;               /*!< 11 bits                                      */
  BOOL      RTR;                   /*!< if remote frame                              */
    uint8_t   data1;                 /*!< data byte 1, if not 2nd CAN_FLT_STANDARD_DUAL*/
    uint8_t   data2;                 /*!< data byte 2, if CAN_FLT_STANDARD_SINGLE      */
} CAN_STANDARD_FILTER;

/**
  * @brief  CAN extended filter structure
    */
typedef struct {
    uint16_t  ID28_13;               /*!< 16 bits                                      */
    uint16_t  ID12_0;                /*!< 13 bits, if CAN_FLT_EXTENDED_SINGLE          */
  BOOL      RTR;                   /*!< if remote frame, if CAN_FLT_EXTENDED_SINGLE  */
} CAN_EXTENDED_FILTER;

/**
  * @brief  CAN filter structure
    */
typedef struct {
    uint8_t   type;                  /*!< Filter type, which is a value of @ref CAN_FLT */

    /**
  * @brief  accepted filter
    */
    union {
        CAN_STANDARD_FILTER sf;
        CAN_EXTENDED_FILTER ef;
    } ACCEPT;

    /**
  * @brief  filter mask
    */
    union {
        CAN_STANDARD_FILTER sf;
        CAN_EXTENDED_FILTER ef;
    } MASK;
} CAN_FILTER;

/**
  * @brief  CAN initialization structure
    */
typedef struct {
    BOOL CAN_TxEn;                       /*!< if transmission is enable                                         */
    BOOL CAN_Loopback;                   /*!< loop back mode without phy                                        */
  uint8_t CAN_ClockDiv;                  /*!< input clock divider, ref as @ref CAN_CDR_DIV  */
    uint16_t CAN_Prescaler;              /*!< Specifies the length of a time quantum.
                                                                                Time quantum = (CAN_Prescaler + 1) * 2 * input clock */
  uint8_t CAN_SJW;                       /*!< Specifies the maximum number of time quanta
                                                                                the CAN hardware is allowed to lengthen or
                                                                                shorten a bit to perform resynchronization.     */
    uint8_t CAN_TSEG1;                   /*!< the maximum number of time quanta of
                                                                                propagation and 1st phase segment                       */
  uint8_t CAN_TSEG2;                     /*!< the maximum number of time quanta of 2nd
                                                                                phase segment                                                                   */
  BOOL CAN_HighSpeed;                    /*!< if CAN is running on high speed bus (class C) */
} CAN_InitTypeDef;

/**
  * @brief  CAN frame structure
    */
typedef struct
{
  BOOL SFF;                                      /*!< If standard or extended frame format                  */
    uint32_t Id;                                     /*!< Specifies the identifier.This parameter can
                                                                                be a value between 0 to 0x1FFFFFFF.                     */
  BOOL RTR;                                      /*!< Specifies if the frame is a remote frame      */
  uint8_t DLC;                                   /*!< Specifies the length of the frame, which is
                                                                                a value between  0 to 8                                             */
  uint8_t Data[8];                               /*!< Frame data                                                                        */
} CAN_Frame;

/**
  * @brief  CAN initialization
  * @note   This function should be called at first before any other interfaces.
    * @param[in] CANx CAN peripheral, which is CAN0 or CAN1
    * @param[in] Init A pointer to structure CAN_InitTypeDef
    * @param[in] f1 A pointer to structure CAN_FILTER
    * @param[in] f2 NULL if single filter, or a pointer to second filter while dual filters
  * @retval BOOL The bit indicates if specific CAN is initialized or not
    */
BOOL CAN_Init(CAN0_Type* CANx, CAN_InitTypeDef* Init,
  CAN_FILTER *f1, CAN_FILTER *f2);

/**
  * @brief  CAN is set to sleep or wake up
  * @param[in] CANx CAN peripheral, which is CAN0 or CAN1
    * @param[in] Enable The bit indicates if sleep mode is enable or not
    * @retval None
    */
void CAN_SetSleepMode(CAN0_Type* CANx, BOOL enable);

/**
  * @brief  Enable or disable UART interrupt.
    * @param[in] CANx CAN peripheral, which is CAN0 or CAN1
    * @param[in] Int interrupt mask bits, which can be the combination of @ref CAN_INT
    * @param[in] Enable The bit indicates if specific interrupts are enable or not
  * @retval None
    */
void CAN_EnableInt(CAN0_Type* CANx, uint32_t Int, BOOL enable);

/**
  * @brief  Check specific interrupts are set or not
    * @note   All interrupts except for receive int are cleared after call this func.
    * @param[in] CANx CAN peripheral, which is CAN0 or CAN1
    * @retval uint8_t CAN interrupt bits, which can be the combination of @ref CAN_INT
    */
uint8_t CAN_GetIntStatus(CAN0_Type* CANx);

/**
  * @brief  CAN perform to transmit data
    * @param[in] CANx CAN peripheral, which is CAN0 or CAN1
    * @param[in] frame A pointer to the CAN_Frame to be transmitted
    * @retval BOOL The bit indicates if data is transmitted or not
    */
BOOL CAN_Transmit(CAN0_Type* CANx, CAN_Frame* frame);

/**
  * @brief  CAN perform to receive data
    * @param[in] CANx CAN peripheral, which is CAN0 or CAN1
    * @param[out] frame A user-allocated buffer to fetch received frame
    * @retval BOOL The bit indicates if data is recieved or not
    */
BOOL CAN_Receive(CAN0_Type* CANx, CAN_Frame* frame);

#ifdef __cplusplus
}
#endif

#endif /* __CMEM7_CAN_H */
