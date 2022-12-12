////////////////////////////////////////////////////////////////////////////////
/// @file     hal_uart.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE UART
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
#ifndef __HAL_UART_H
#define __HAL_UART_H

// Files includes
#include "reg_uart.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

/////////////////////////////////////1///////////////////////////////////////////
/// @defgroup UART_HAL
/// @brief UART HAL modules
/// @{


////////////////////////////////////////////////////////////////////////////////
/// @defgroup UART_Exported_Types
/// @{
///

////////////////////////////////////////////////////////////////////////////////
/// @brief UART Word Length Enumerate definition
/// @anchor UART_Word_Length
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    UART_WordLength_5b = 0U,
    UART_WordLength_6b = 1U << UART_CCR_CHAR_Pos,
    UART_WordLength_7b = 2U << UART_CCR_CHAR_Pos,
    UART_WordLength_8b = 3U << UART_CCR_CHAR_Pos
} UART_WordLength_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief UART Stop Bits Enumerate definition
/// @anchor UART_Stop_Bits
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    UART_StopBits_1 = 0U,
    UART_StopBits_2 = UART_CCR_SPB,

    UART_StopBits_0_5 = UART_CCR_SPB1,
    UART_StopBits_1_5 = UART_CCR_SPB1 | UART_CCR_SPB0,
} UART_Stop_Bits_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief UART Parity Enumerate definition
/// @anchor UART_Parity
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    UART_Parity_No   = 0U,
    UART_Parity_Even = UART_CCR_PEN | UART_CCR_PSEL,
    UART_Parity_Odd  = UART_CCR_PEN
} UART_Parity_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief UART Hardware Flow Control Enumerate definition
/// @anchor UART_Hardware_Flow_Control
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    UART_HWFlowControl_None    = 0U,

    //    UART_HWFlowControl_RTS     = UART_GCR_AUTOFLOW,
    //    UART_HWFlowControl_CTS     = UART_GCR_AUTOFLOW,

    UART_HWFlowControl_RTS_CTS = UART_GCR_AUTOFLOW
} UART_HW_FLOWCONTROL_TypeDef;

typedef enum {
    UART_WakeUp_IdleLine    = 0U,  //
    UART_WakeUp_AddressMark = UART_CCR_WAKE
} UART_WakeUp_TypeDef;

typedef enum {
    UART_9bit_Polarity_Low  = 0U,  //
    UART_9bit_Polarity_High = UART_CCR_B8POL
} UART_9bit_Polarity_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief UART Auto BaudRate definition
////////////////////////////////////////////////////////////////////////////////
typedef enum  {
    Data_F8 = 0,
    Data_FE,
    ABRMODE_FALLING_TO_RISINGEDGE1BIT,
    ABRMODE_FALLING_TO_RISINGEDGE2BIT,
    ABRMODE_FALLING_TO_RISINGEDGE4BIT,
    ABRMODE_FALLING_TO_RISINGEDGE8BIT,
    ABRMODE_FALLING_TO_FALLINGEDGE2BIT,
    ABRMODE_FALLING_TO_FALLINGEDGE4BIT,
    ABRMODE_FALLING_TO_FALLINGEDGE8BIT,
    ABRMODE_STARTBIT,
    ABRMODE_VALUE0X55,
    ABRMODE_VALUE0x7F,
    ABRMODE_VALUE0X80,
    ABRMODE_VALUE0XF7,
    ABRMODE_VALUE0XF8 = Data_F8,
    ABRMODE_VALUE0XFE = Data_FE,
    ABRMODE_VALUE0XFF,
} UART_AutoBaud_TypeDef;
////////////////////////////////////////////////////////////////////////////////
/// @brief UART Init Structure definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    union {
        u32                         BaudRate;                           ///< This member configures the UART communication baud rate.
        u32                         UART_BaudRate;
    };
    union {
        UART_WordLength_TypeDef     WordLength;                         ///< Specifies the number of data bits transmitted or received in a frame.
        u16                         UART_WordLength;
    };
    union {
        UART_Stop_Bits_TypeDef      StopBits;                           ///< Specifies the number of stop bits transmitted.
        u16                         UART_StopBits;
    };
    union {
        UART_Parity_TypeDef         Parity;                             ///< Specifies the parity mode.
        u16                         UART_Parity;
    };
    union {
        u16                         Mode;                               ///< Specifies wether the Receive or Transmit mode is
        u16                         UART_Mode;
    };
    union {
        UART_HW_FLOWCONTROL_TypeDef HWFlowControl;                      ///< Specifies wether the hardware flow control mode is enabled or disabled.
        u16                         UART_HardwareFlowControl;
    };
} UART_InitTypeDef;

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup UART_Exported_Constants
/// @{

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup UART_Exported_Variables
/// @{
#ifdef _HAL_UART_C_

#define GLOBAL
#else
#define GLOBAL extern
#endif

#undef GLOBAL
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup UART_Exported_Functions
/// @{
void UART_DeInit(UART_TypeDef* uart);
void UART_Init(UART_TypeDef* uart, UART_InitTypeDef* init_struct);
void UART_StructInit(UART_InitTypeDef* init_struct);
void UART_Cmd(UART_TypeDef* uart, FunctionalState state);
void UART_ITConfig(UART_TypeDef* uart, u16 it, FunctionalState state);
void UART_DMACmd(UART_TypeDef* uart, u16 dma_request, FunctionalState state);
void UART_SendData(UART_TypeDef* uart, u16 Data);
void UART_ClearITPendingBit(UART_TypeDef* uart, u16 it);

u16        UART_ReceiveData(UART_TypeDef* uart);
FlagStatus UART_GetFlagStatus(UART_TypeDef* uart, u16 flag);

ITStatus   UART_GetITStatus(UART_TypeDef* uart, u16 it);

void UART_WakeUpConfig(UART_TypeDef* uart, UART_WakeUp_TypeDef mode);
void UART_ReceiverWakeUpCmd(UART_TypeDef* uart, FunctionalState state);
void UART_SetRXAddress(UART_TypeDef* uart, u8 address);
void UART_SetRXMASK(UART_TypeDef* uart, u8 address);
void UART_Enable9bit(UART_TypeDef* uart, FunctionalState state);
void UART_Set9bitLevel(UART_TypeDef* uart, FunctionalState state);
void UART_Set9bitPolarity(UART_TypeDef* uart, UART_9bit_Polarity_TypeDef polarity);
void UART_Set9bitAutomaticToggle(UART_TypeDef* uart, FunctionalState state);
void UART_HalfDuplexCmd(UART_TypeDef* uart, FunctionalState state);
void UART_SetGuardTime(UART_TypeDef* uart, u8 guard_time);
void UART_SmartCardCmd(UART_TypeDef* uart, FunctionalState state);
void UART_SmartCardNACKCmd(UART_TypeDef* uart, FunctionalState state);
void UART_SendBreak(UART_TypeDef* uart);
void UART_AutoBaudRateCmd(UART_TypeDef* uart, FunctionalState state);
void UART_AutoBaudRateSet(UART_TypeDef* uart, UART_AutoBaud_TypeDef value, FunctionalState state);

/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif // __HAL_UART_H
////////////////////////////////////////////////////////////////////////////////
