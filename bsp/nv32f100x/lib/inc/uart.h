/******************************************************************************
*
* @brief provide commond UART utilities. 
*
*******************************************************************************/
#ifndef _UART_H_
#define _UART_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* Includes
******************************************************************************/
#include "common.h"
#include "wdog.h"
/******************************************************************************
* Constants
******************************************************************************/

/******************************************************************************
* Macros
******************************************************************************/
#define MAX_UART_NO             3

/******************************************************************************
* Types
******************************************************************************/

/******************************************************************************
*define uart setting type
*
*//*! @addtogroup uart_setting_type
* @{
*******************************************************************************/  

/*!
* @brief UART setting type.
*
*/ 

typedef struct
{
    uint32_t bEnable      : 1;                /*!< 1: enable, 0: disable */
    uint32_t resvd        : 31;               /*!< 1: reserved bit field */
} UART_SettingType;
/*! @} End of uart_setting_type */

/******************************************************************************
*define uart config type
*
*//*! @addtogroup uart_config_type
* @{
******************************************************************************/
 /*!
 * @brief UART Configuration structure.
 *
 */   
typedef struct 
{
    UART_SettingType    sSettings;              /*!< UART settings */
    uint32_t    u32SysClkHz;        /*!< system clock */
    uint32_t    u32Baudrate;        /*!< UART baudrate */
} UART_ConfigType;
/*! @} End of uart_config_type  */

/******************************************************************************
*define uart config baudrate type
*
*//*! @addtogroup uart_config_baudrate_type
* @{
******************************************************************************/
 /*!
 * @brief UART baudrate type structure.
 *
 */   
typedef struct
{
    uint32_t    u32SysClkHz;        /*!< system clock */
    uint32_t    u32Baudrate;        /*!< UART baudrate */
} UART_ConfigBaudrateType;
/*! @} End of uart_config_baudrate_type */

/******************************************************************************
*define uart config mode type list
*
*//*! @addtogroup uart_mode_type_list
* @{
******************************************************************************/
typedef enum
{
    UART_Mode8Bit,                  /*!< 8 bit mode */
    UART_Mode9Bit,                  /*!< 9 bit mode */
    UART_ModeEnableLoopback,        /*!< enable looback mode */
    UART_ModeDisableLoopback,       /*!< disable loopback mode*/
    UART_ModeEnableSingleWire,      /*!< enable single wire mode */
    UART_ModeDisableSingleWire,     /*!< disable single wire mode */
} UART_ModeType;
/*! @} End of uart_mode_type_list   */

/******************************************************************************
*define uart interrupt type list
*
*//*! @addtogroup uart_interrupt_type_list
* @{
******************************************************************************/

typedef enum
{
    UART_TxBuffEmptyInt,            /*!< transmit buffer empty interrupt */
    UART_TxCompleteInt,             /*!< transmit complete interrupt */
    UART_RxBuffFullInt,             /*!< receive buffer full interrupt */

    UART_IdleLineInt,               /*!< idle line interrupt */

    UART_RxOverrunInt,              /*!< receive overrun interrupt */
    UART_NoiseErrorInt,             /*!< noise error interrupt */
    UART_FramingErrorInt,           /*!< framing error interrupt */
    UART_ParityErrorInt,            /*!< parity error interrupt */
} UART_InterruptType;
/*! @} End of uart_interrupt_type_list  */

/******************************************************************************
*define uart flag type list
*
*//*! @addtogroup uart_flag_type_list
* @{
******************************************************************************/
typedef enum
{
    UART_FlagPF = 0,        /*!< Parity error flag */
    UART_FlagFE,            /*!< Framing error flag */
    UART_FlagNF,            /*!< Noise flag */
    UART_FlagOR,            /*!< Receive overrun */
    UART_FlagIDLE,          /*!< Idle line flag */
    UART_FlagRDRF,          /*!< Receive data register full flag */
    UART_FlagTC,            /*!< Transmission complete flag */
    UART_FlagTDRE,          /*!< Transmit data register flag */

    UART_FlagRAF,           /*!< Receiver active flag */
    UART_FlagLBKDE,         /*!< LIN break detection enable */
    UART_FlagBRK13,         /*!< Break character generation length */ 
    UART_FlagRWUID,         /*!< Receive wake up idle detect */
    UART_FlagRXINV,         /*!< Receive data inversion */
    UART_FlagRev1,          /*!< Reserved */
    UART_FlagRXEDGIF,       /*!< RxD pin active edge interrupt flag */
    UART_FlagLBKDIF,        /*!< LIN break detect interrupt flag */
} UART_FlagType;
/*! @} End of uart_flag_type_list   */

/* callback types */
typedef void (*UART_CallbackType)(UART_Type *pUART);

/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* Inline functions
******************************************************************************/

/******************************************************************************
* define UART APIs
*
*//*! @addtogroup uart_api_list
* @{
*******************************************************************************/

/*****************************************************************************//*!
*
* @brief read receive buffer
*        
* @param[in] pUART       base of UART port
*
* @return unsign char received char
*
*****************************************************************************/
__STATIC_INLINE uint8_t UART_ReadDataReg(UART_Type *pUART)
{
    /* Return the 8-bit data from the receiver */
    return pUART->D;
}
/*****************************************************************************//*!
*
* @brief write transmit buffer
*        
* @param[in] pUART       base of UART port
* @param[in] u8Char      char to send
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_WriteDataReg(UART_Type *pUART, uint8_t u8Char)
{
    /* Send the character */
    pUART->D = (uint8_t)u8Char;
}

/*****************************************************************************//*!
*
* @brief check if a character has been received
*
* @param[in] pUART  base of UART port
*
* @return 0, No character received; no-zero, Character has been received
*
* @ Pass/ Fail criteria:
*****************************************************************************/
__STATIC_INLINE uint8_t UART_CharPresent(UART_Type *pUART)
{  
    return (pUART->S1 & UART_S1_RDRF_MASK);
}
/*****************************************************************************//*!
*
* @brief enable transmit
*        
* @param[in] pUART       base of UART port
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_EnableTx(UART_Type *pUART)
{
    
    pUART->C2 |= UART_C2_TE_MASK;
}
/*****************************************************************************//*!
*
* @brief disable transmit
*        
* @param[in] pUART       base of UART port
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_DisableTx(UART_Type *pUART)
{    
    pUART->C2 &= (~UART_C2_TE_MASK);
}
/*****************************************************************************//*!
*
* @brief enable receive
*        
* @param[in] pUART       base of UART port
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_EnableRx(UART_Type *pUART)
{    
    pUART->C2 |= UART_C2_RE_MASK;
}
/*****************************************************************************//*!
*
* @brief disable receive
*        
* @param[in] pUART       base of UART port
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_DisableRx(UART_Type *pUART)
{    
    pUART->C2 &= (~UART_C2_RE_MASK);
}
/*****************************************************************************//*!
*
* @brief Enable loopback mode
*        
* @param[in] pUART       base of UART port
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_EnableLoopback(UART_Type *pUART)
{
    pUART->C1 |= UART_C1_LOOPS_MASK;
    pUART->C1 &= (~UART_C1_RSRC_MASK);
}
/*****************************************************************************//*!
*
* @brief enable single wire mode
*        
* @param[in] pUART       base of UART port
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_EnableSingleWire(UART_Type *pUART)
{
    pUART->C1 |= UART_C1_LOOPS_MASK;
    pUART->C1 |= UART_C1_RSRC_MASK;
}
/*****************************************************************************//*!
*
* @brief set 8-bit mode
*        
* @param[in] pUART       base of UART port
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_Set8BitMode(UART_Type *pUART)
{
    pUART->C1 &= (~UART_C1_M_MASK);
}
/*****************************************************************************//*!
*
* @brief set 9-bit mode
*        
* @param[in] pUART       base of UART port
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_Set9BitMode(UART_Type *pUART)
{
    pUART->C1 |= UART_C1_M_MASK;
}
/*****************************************************************************//*!
*
* @brief enable transmit buffer empty interrupt
*        
* @param[in] pUART       base of UART port
*
* @return none
*
* @ Pass/ Fail criteria:
*****************************************************************************/
__STATIC_INLINE void UART_EnableTxBuffEmptyInt(UART_Type *pUART)
{
    pUART->C2 |= UART_C2_TIE_MASK;
}
/*****************************************************************************//*!
*
* @brief enable transmit complete interrupt
*        
* @param[in] pUART       base of UART port
*
* @return none
*
* @ Pass/ Fail criteria:
*****************************************************************************/
__STATIC_INLINE void UART_EnableTxCompleteInt(UART_Type *pUART)
{
    pUART->C2 |= UART_C2_TCIE_MASK;
}
/*****************************************************************************//*!
*
* @brief enable receive buffer full interrupt
*        
* @param[in] pUART       base of UART port
*
* @return none
*
* @ Pass/ Fail criteria:
*****************************************************************************/
__STATIC_INLINE void UART_EnableRxBuffFullInt(UART_Type *pUART)
{
    pUART->C2 |= UART_C2_RIE_MASK;
}
/*****************************************************************************//*!
*
* @brief disable transmit buffer empty interrupt
*        
* @param[in] pUART       base of UART port
*
* @return none
*
* @ Pass/ Fail criteria:
*****************************************************************************/
__STATIC_INLINE void UART_DisableTxBuffEmptyInt(UART_Type *pUART)
{
        pUART->C2 &= (~UART_C2_TIE_MASK);    
}
/*****************************************************************************//*!
*
* @brief disable transmit complete interrupt
*        
* @param[in] pUART       base of UART port
*
* @return none
*
* @ Pass/ Fail criteria:
*****************************************************************************/
__STATIC_INLINE void UART_DisableTxCompleteInt(UART_Type *pUART)
{
    pUART->C2 &= (~UART_C2_TCIE_MASK);   
}
/*****************************************************************************//*!
*
* @brief disable receive buffer full interrupt
*        
* @param[in] pUART       base of UART port
*
* @return none
*
* @ Pass/ Fail criteria:
*****************************************************************************/
__STATIC_INLINE void UART_DisableRxBuffFullInt(UART_Type *pUART)
{
    pUART->C2 &= (~UART_C2_RIE_MASK);  
}
/*****************************************************************************//*!
*
* @brief print out break character
*        
* @param[in] pUART  base of UART port
*
* @return       none
*
* @ Pass/ Fail criteria:
*****************************************************************************/
__STATIC_INLINE void UART_PutBreak(UART_Type *pUART)
{
    /* Write 1 then write 0 to UART_C2[SBK] bit, will put break character */
    pUART->C2 |= UART_C2_SBK_MASK; 
    pUART->C2 &= (~UART_C2_SBK_MASK);
}

/*****************************************************************************//*!
*
* @brief check whether tx is complete,i.e. data has been sent out.
*        
* @param[in] pUART  base of UART port
*
* @return       
*               1, Tx complete flag is set
*               0, Tx complete flag is clear
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t UART_IsTxComplete(UART_Type *pUART)
{
    return (pUART->S1 & UART_S1_TC_MASK);
}
/*****************************************************************************//*!
*
* @brief check whether Tx buffer is empty
*        
* @param[in] pUART  base of UART port
*
* @return       
*               1, Tx buffer is empty
*               0, Tx buffer is not empty
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t UART_IsTxBuffEmpty(UART_Type *pUART)
{
    return (pUART->S1 & UART_S1_TDRE_MASK);
}
/*****************************************************************************//*!
*
* @brief check whether Rx buffer is full, i.e. receive a character
*        
* @param[in] pUART  base of UART port
*
* @return       
*               1, Rx buffer is full
*               0, Rx buffer is not full
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE uint8_t UART_IsRxBuffFull(UART_Type *pUART)
{
    return (pUART->S1 & UART_S1_RDRF_MASK);
}
/*! @} End of uart_api_list */


/******************************************************************************
* Global functions declaration
******************************************************************************/
void UART_Init(UART_Type *pUART, UART_ConfigType *pConfig);
uint8_t UART_GetChar(UART_Type *pUART);
void UART_PutChar(UART_Type *pUART, uint8_t u8Char);
void UART_SetBaudrate(UART_Type *pUART, UART_ConfigBaudrateType *pConfig);
void UART_EnableInterrupt(UART_Type *pUART, UART_InterruptType InterruptType);
void UART_DisableInterrupt(UART_Type *pUART, UART_InterruptType InterruptType);
uint16_t UART_GetFlags(UART_Type *pUART);
uint8_t UART_CheckFlag(UART_Type *pUART, UART_FlagType FlagType);
void UART_SendWait(UART_Type *pUART, uint8_t *pSendBuff, uint32_t u32Length);
void UART_ReceiveWait(UART_Type *pUART, uint8_t *pReceiveBuff, uint32_t u32Length);
void UART_WaitTxComplete(UART_Type *pUART);
void UART_SetCallback(UART_CallbackType pfnCallback);
void UART0_Isr(void);
void UART1_Isr(void);
void UART2_Isr(void);


#ifdef __cplusplus
}
#endif
#endif /* #ifndef _UART_H_ */
