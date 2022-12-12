////////////////////////////////////////////////////////////////////////////////
/// @file     hal_can.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE CAN
///           FIRMWARE LIBRARY.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#ifndef __HAL_CAN_H
#define __HAL_CAN_H

// Files includes
#include "types.h"
#include "reg_can.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup CAN_HAL
/// @brief CAN HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup CAN_Exported_Types
/// @{



////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_Initialization
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    CANINITFAILED = 0x00000000,  ///< CAN initialization failed
    CANINITOK     = 0x00000001   ///< CAN initialization ok
} emCAN_INIT_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_sleep_constants
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    CANSLEEPFAILED = 0x00000000,  ///< CAN did not enter the sleep mode
    CANSLEEPOK     = 0x00000001   ///< CAN entered the sleep mode
} emCAN_SLEEP_conts_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_wake_up_constants
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    CANWAKEUPFAILED = 0x00000000,  ///< CAN did not leave the sleep mode
    CANWAKEUPOK     = 0x00000001   ///< CAN leaved the sleep mode
} emCAN_WAKE_conts_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_Mode
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    CAN_BASICMode         = 0x00000000,
    CAN_PELIMode          = 0x00000080,
    CAN_WorkMode          = 0x00000080,
    CAN_ResetMode         = 0x00000001,
    CAN_ListenOnlyMode    = 0x00000002,
    CAN_SeftTestMode      = 0x00000004,
    CAN_FilterMode_Singal = 0x00000008,
    CAN_FilterMode_Double = 0x000000f7,
    CAN_SleepMode         = 0x00000010
} emCAN_CAN_Mode_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief BASIC_CAN_interrupt
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    CAN_IT_RIE = CAN_CR_RIE,                                                    ///< Overflow interrupt enable
    CAN_IT_TIE = CAN_CR_TIE,                                                    ///< Transmit interrupt enable
    CAN_IT_EIE = CAN_CR_EIE,                                                    ///< Error interrupt enable
    CAN_IT_OIE = CAN_CR_OIE                                                     ///< Receive interrupt enable
} emCAN_BASIC_IntEn_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief PELI_CAN_interrupt
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    CAN_IT_RI  = CAN_IR_RI,                                                     ///< Overflow interrupt enable
    CAN_IT_TI  = CAN_IR_TI,                                                     ///< Transmit interrupt enable
    CAN_IT_EI  = CAN_IR_EI,                                                     ///< Error interrupt enable
    CAN_IT_DOI = CAN_IR_DOI,                                                    ///< Receive interrupt enable
    CAN_IT_WUI = 0x00001010,                                                    ///< Receive interrupt enable
    CAN_IT_EPI = CAN_IR_EPI,                                                    ///< Receive interrupt enable
    CAN_IT_ALI = CAN_IR_ALI,                                                    ///< Receive interrupt enable
    CAN_IT_BEI = CAN_IR_BEI,                                                    ///< Receive interrupt enable
    CAN_IT_ALL = 0xFFFF                                                         ///< Receive interrupt enable

} emCAN_PELI_IntEn_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_Status
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    CAN_STATUS_RBS = CAN_SR_RBS,
    CAN_STATUS_DOS = CAN_SR_DOS,
    CAN_STATUS_TBS = CAN_SR_TBS,
    CAN_STATUS_TCS = CAN_SR_TCS,
    CAN_STATUS_RS  = CAN_SR_RS,
    CAN_STATUS_TS  = CAN_SR_TS,
    CAN_STATUS_ES  = CAN_SR_ES,
    CAN_STATUS_BS  = CAN_SR_BS
} emCAN_Status_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_Command_register
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    CAN_TR  = CAN_CMR_TR,  ///< Transmission request
    CAN_AT  = CAN_CMR_AT,
    CAN_RRB = CAN_CMR_RRB,
    CAN_CDO = CAN_CMR_CDO
} emCAN_Command_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  CAN_Peli transmit frame definition
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    DataFrame   = 0,  ///< Data Frame
    RemoteFrame = !DataFrame
} TransFrame;

////////////////////////////////////////////////////////////////////////////////
/// @brief  CAN_Basic init structure definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    u8              SJW;
    u8              BRP;
    FlagStatus      SAM;
    u8              TESG2;
    u8              TESG1;
    FunctionalState GTS;
    u8              CDCLK;
    u8              CLOSE_OPEN_CLK;
    u8              RXINTEN;
    u8              CBP;
} CAN_Basic_InitTypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  CAN_Peli init structure definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    u8              SJW;
    u8              BRP;
    FlagStatus      SAM;
    u8              TESG2;
    u8              TESG1;
    FunctionalState LOM;
    FunctionalState STM;
    FunctionalState SM;
    FunctionalState SRR;
    u32             EWLR;
} CAN_Peli_InitTypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  CAN_Basic filter init structure definition
////////////////////////////////////////////////////////////////////////////////

typedef struct {
    u8 CAN_FilterId;      ///< Specifies the filter identification number. This parameter can be a value between 0x00 and 0xFF.
    u8 CAN_FilterMaskId;  ///< Specifies the filter mask number or identification number, This parameter can be a value between
    ///< 0x00 and 0xFF.
} CAN_Basic_FilterInitTypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  CAN_Peli filter init structure definition
////////////////////////////////////////////////////////////////////////////////

typedef struct {
    u8 AFM;
    u8 CAN_FilterId0;  ///< Specifies the filter identification number, This parameter can be a value between 0x00 and 0xFF
    u8 CAN_FilterId1;
    u8 CAN_FilterId2;
    u8 CAN_FilterId3;
    u8 CAN_FilterMaskId0;  ///< Specifies the filter mask number or identification number, This parameter can be a value between
    ///< 0x00 and 0xFF
    u8 CAN_FilterMaskId1;
    u8 CAN_FilterMaskId2;
    u8 CAN_FilterMaskId3;
} CAN_Peli_FilterInitTypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  CAN_Basic Tx message structure definition
////////////////////////////////////////////////////////////////////////////////

typedef struct {
    u8 IDH;      ///< Specifies the standard high identifier. This parameter can be a value between 0 to 0xFF.
    u8 IDL;      ///< Specifies the standard low identifier. This parameter can be a value between 0 to 0x7.
    u8 RTR;      ///< Specifies the type of frame for the message that will be transmitted. This parameter can be @TransFrame.
    u8 DLC;      ///< Specifies the length of the frame that will be transmitted. This parameter can be a value between 0 to 8.
    u8 Data[8];  ///< Contains the data to be transmitted. It ranges from 0 to 0xFF.
} CanBasicTxMsg;

////////////////////////////////////////////////////////////////////////////////
/// @brief  CAN_Basic Rx message structure definition
////////////////////////////////////////////////////////////////////////////////

typedef struct {
    u16 ID;       ///< Specifies the standard identifier. This parameter can be a value between 0 to 0x7FF.
    u8  RTR;      ///< Specifies the type of frame for the received message. This parameter can be a value of @ref TransFrame
    u8  DLC;      ///< Specifies the length of the frame that will be received. This parameter can be a value between 0 to 8
    u8  Data[8];  ///< Contains the data to be received. It ranges from 0 to  0xFF.
} CanBasicRxMsg;

///////////////////////////////////////////////////////////////////////////////
/// @brief  CAN_Peli_Tx message structure definition
///////////////////////////////////////////////////////////////////////////////

typedef struct {
    u8 IDLL;  ///< Specifies the extended identifier.
    ///< This parameter can be a value between 0 to 0xFF.
    u8 IDLH;
    u8 IDHL;
    u8 IDHH;
    u8 FF;   ///< Specifies the type of identifier for the message that will be transmitted. This parameter can be a value of @ref
    ///< CAN_identifier_type
    u8 RTR;  ///< Specifies the type of frame for the message that will be transmitted. This parameter can be a value of @ref
    ///< TransFrame.
    u8 DLC;  ///< Specifies the length of the frame that will be transmitted. This parameter can be a value between 0 to 8.
    u8 Data[8];  ///< Contains the data to be transmitted. It ranges from 0 to 0xFF.
} CanPeliTxMsg;

////////////////////////////////////////////////////////////////////////////////
/// @brief  CAN Rx message structure definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    u32 ID;  ///< Specifies the extended identifier. This parameter can be a value between 0 to 0x1FFFFFFF.
    u8  FF;  ///< Specifies the type of identifier for the message that will be received. This parameter can be a value of @ref
    ///< CAN_identifier_type.
    u8 RTR;  ///< Specifies the type of frame for the received message. This parameter can be a value of @ref TransFrame.
    u8 DLC;  ///< Specifies the length of the frame that will be received. This parameter can be a value between 0 to 8.
    u8 Data[8];  ///< Contains the data to be received. It ranges from 0 to0xFF.
} CanPeliRxMsg;

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup  CAN_Exported_Constants
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup  parasmeter_of_CAN_transmission_register
/// @{
#define CANTXFAILED (0x00U)   ///< CAN transmission failed
#define CANTXOK (0x01U)       ///< CAN transmission succeeded
#define CANTXPENDING (0x02U)  ///< CAN transmission pending
#define CAN_NO_MB (0x04U)     ///< CAN cell did not provide an empty mailbox
/// @}


/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup CAN_Exported_Variables
/// @{
#ifdef _HAL_CAN_C_

#define GLOBAL
#else
#define GLOBAL extern
#endif

#undef GLOBAL
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup CAN_Exported_Functions
/// @{

// Basic and Peli Work all need function ---------------------------------------

void CAN_Mode_Cmd(CAN_TypeDef* can, u32 mode);
void CAN_ResetMode_Cmd(CAN_TypeDef* can, FunctionalState state);
void CAN_ClearDataOverflow(CAN_TypeDef* can);
void CAN_ClearITPendingBit(CAN_TypeDef* can);

// Basic Work function ---------------------------------------------------------
void CAN_DeInit(CAN_TypeDef* can);
void CAN_FilterInit(CAN_Basic_FilterInitTypeDef* basic_filter_init_struct);
void CAN_StructInit(CAN_Basic_InitTypeDef* basic_init_struct);
void CAN_ITConfig(CAN_TypeDef* can, u32 it, FunctionalState state);
void CAN_CancelTransmit(CAN_TypeDef* can);
void CAN_FIFORelease(CAN_TypeDef* can);
void CAN_Receive(CAN_TypeDef* can, CanBasicRxMsg* basic_receive_message);

u8 CAN_Transmit(CAN_TypeDef* can, CanBasicTxMsg* basic_transmit_message);
u8 CAN_Init(CAN_TypeDef* can, CAN_Basic_InitTypeDef* basic_init_struct);
u8 CAN_Sleep(CAN_TypeDef* can);
u8 CAN_WakeUp(CAN_TypeDef* can);

FlagStatus CAN_GetFlagStatus(CAN_TypeDef* can, u32 flag);
ITStatus   CAN_GetITStatus(CAN_TypeDef* can, u32 it);

// Peli Work function ----------------------------------------------------------
void CAN_Peli_SleepMode_Cmd(FunctionalState state);
void CAN_Peli_Init(CAN_Peli_InitTypeDef* init_struct);
void CAN_Peli_StructInit(CAN_Peli_InitTypeDef* peli_init_struct);
void CAN_Peli_FilterInit(CAN_Peli_FilterInitTypeDef* peli_filter_init_struct);
void CAN_Peli_FilterStructInit(CAN_Peli_FilterInitTypeDef* peli_filter_init_struct);
void CAN_Peli_Transmit(CanPeliTxMsg* peli_transmit_message);
void CAN_Peli_TransmitRepeat(CanPeliTxMsg* peli_transmit_message);
void CAN_Peli_Receive(CanPeliRxMsg* peli_receive_message);
void CAN_Peli_ITConfig(u32 it, FunctionalState state);
void CAN_AutoCfg_BaudParam(CAN_Peli_InitTypeDef* init_struct, u32 src_clk, u32 baud);

u32 CAN_Peli_GetRxFIFOInfo(void);
u8  CAN_Peli_GetLastErrorCode(void);
u8  CAN_Peli_GetReceiveErrorCounter(void);
u8  CAN_Peli_GetLSBTransmitErrorCounter(void);

ITStatus CAN_Peli_GetITStatus(u32 it);



/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

