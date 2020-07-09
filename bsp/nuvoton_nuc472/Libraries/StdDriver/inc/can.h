/**************************************************************************//**
 * @file     can.h
 * @version  V1.00
 * $Revision: 8 $
 * $Date: 14/09/26 3:38p $
 * @brief    NUC472/NUC442 CAN driver header file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __CAN_H__
#define __CAN_H__

#ifdef  __cplusplus
extern "C"
{
#endif

/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_CAN_Driver CAN Driver
  @{
*/

/** @addtogroup NUC472_442_CAN_EXPORTED_TYPEDEF CAN Exported Type Defines
  @{
*/

/**
 * @details  Message ID types.
 */
typedef enum {
    CAN_STD_ID = 0, /*!< Standard Identifier  */
    CAN_EXT_ID = 1  /*!< Extended Identifier  */
} E_CAN_ID_TYPE;

/**
 * @details  Message Frame types.
 */
typedef enum {
    REMOTE_FRAME = 0,  /*!< Remote Frame  */
    DATA_FRAME   = 1   /*!< Data Frame    */
} E_CAN_FRAME_TYPE;

/**
 * @details  CAN message structure.
 */
typedef struct {
    uint32_t  IdType;     /*!< Identifier Type     */
    uint32_t  FrameType;  /*!< Frame Type          */
    uint32_t  Id;         /*!< Message Identifier  */
    uint8_t   DLC;        /*!< Data Length Code    */
    uint8_t   Data[8];    /*!< Data byte 0 ~ 7     */
} STR_CANMSG_T;

/**
 * @details  CAN mask message structure.
 */
typedef struct {
    uint8_t   u8Xtd;     /*!< Extended Identifier  */
    uint8_t   u8Dir;     /*!< Message Direction    */
    uint32_t  u32Id;     /*!< Message Identifier   */
    uint8_t   u8IdType;  /*!< Identifier Type      */
} STR_CANMASK_T;

/**
 * @details  CAN operation mode: normal/basic mode.
 */
typedef enum {
    CAN_NORMAL_MODE = 1, /*!< Normal Mode  */
    CAN_BASIC_MODE = 2   /*!< Basic Mode   */
} CAN_MODE_SELECT;

#define ALL_MSG  32  /*!< All Message ram number   */
#define MSG(id)  id  /*!< Message ram number       */


/*@}*/ /* end of group NUC472_442_CAN_EXPORTED_TYPEDEF */


/** @addtogroup NUC472_442_CAN_EXPORTED_FUNCTIONS CAN Exported Functions
  @{
*/

/**
 *  @brief    Get interrupt status
 *
 *  @param[in]    can  The base address of can module
 *
 *  @return   CAN module status register value
 *  \hideinitializer
 */
#define CAN_GET_INT_STATUS(can)    (can->STATUS)

/**
 *  @brief    Get specified interrupt pending status
 *
 *  @param[in]    can  The base address of can module
 *
 *  @return   The source of the interrupt.
 *  \hideinitializer 
 */
#define CAN_GET_INT_PENDING_STATUS(can)     (can->IIDR)

/**
 *  @brief    Disable Wakeup function
 *
 *  @param[in]    can  The base address of can module
 *
 *  @return   None
 * \hideinitializer 
 */
#define CAN_DISABLE_WAKEUP(can)             (can->WU_IE = 0)

/**
 *  @brief    Enable Wakeup function
 *
 *  @param[in]    can  The base address of can module
 *
 *  @return   None
 * \hideinitializer 
 */
#define CAN_ENABLE_WAKEUP(can)              (can->WU_IE = CAN_WUEN_WAKUP_EN_Msk)

/**
 *  @brief    Get specified Message Object new data into bit value
 *
 *  @param[in]    can        The base address of can module
 *  @param[in]    u32MsgNum  Specified Message Object number. (0 ~ 31)
 *
 *  @return   Specified Message Object new data into bit value.
 * \hideinitializer 
 */
#define CAN_GET_NEW_DATA_IN_BIT(can, u32MsgNum)    (u32MsgNum < 16 ? can->NDAT1 & (1 << u32MsgNum) : can->NDAT2 & (1 << (u32MsgNum-16)))


/*---------------------------------------------------------------------------------------------------------*/
/* Define CAN functions prototype                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
uint32_t CAN_SetBaudRate(CAN_T *tCAN, uint32_t u32BaudRate);
uint32_t CAN_Open(CAN_T *tCAN, uint32_t u32BaudRate, uint32_t u32Mode);
int32_t CAN_Transmit(CAN_T *tCAN, uint32_t u32MsgNum , STR_CANMSG_T* pCanMsg);
int32_t CAN_Receive(CAN_T *tCAN, uint32_t u32MsgNum , STR_CANMSG_T* pCanMsg);
void CAN_CLR_INT_PENDING_BIT(CAN_T *tCAN, uint8_t u32MsgNum);
void CAN_EnableInt(CAN_T  *tCAN, uint32_t u32Mask);
void CAN_DisableInt(CAN_T  *tCAN, uint32_t u32Mask);
int32_t CAN_SetMultiRxMsg(CAN_T *tCAN, uint32_t u32MsgNum , uint32_t u32MsgCount, uint32_t u32IDType, uint32_t u32ID);
int32_t CAN_SetRxMsg(CAN_T *tCAN, uint32_t u32MsgNum , uint32_t u32IDType, uint32_t u32ID);
int32_t CAN_SetTxMsg(CAN_T *tCAN, uint32_t u32MsgNum , STR_CANMSG_T* pCanMsg);
int32_t CAN_TriggerTxMsg(CAN_T  *tCAN, uint32_t u32MsgNum);

/*@}*/ /* end of group NUC472_442_CAN_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_CAN_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__CAN_H__

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/





