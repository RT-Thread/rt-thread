/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : FLEXIO
*   Dependencies         : 
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 5.0.0
*   Build Version        : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
*   Copyright 2020 - 2024 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef LPUART_UART_IP_HWACCESS_H
#define LPUART_UART_IP_HWACCESS_H

/**
*   @file
*   @internal
*   @defgroup lpuart_ip Lpuart IPL
*   @addtogroup  lpuart_ip Lpuart  IPL
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
#include "OsIf.h"
#include "Lpuart_Uart_Ip_Defines.h"
#include "SchM_Uart.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LPUART_UART_IP_HWACCESS_VENDOR_ID                    43
#define LPUART_UART_IP_HWACCESS_AR_RELEASE_MAJOR_VERSION     4
#define LPUART_UART_IP_HWACCESS_AR_RELEASE_MINOR_VERSION     7
#define LPUART_UART_IP_HWACCESS_AR_RELEASE_REVISION_VERSION  0
#define LPUART_UART_IP_HWACCESS_SW_MAJOR_VERSION             5
#define LPUART_UART_IP_HWACCESS_SW_MINOR_VERSION             0
#define LPUART_UART_IP_HWACCESS_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Lpuart_Uart_Ip_Defines.h */
#if (LPUART_UART_IP_HWACCESS_VENDOR_ID != LPUART_UART_IP_DEFINES_VENDOR_ID)
    #error "Lpuart_Uart_Ip_HwAccess.h and Lpuart_Uart_Ip_Defines.h have different vendor ids"
#endif
#if ((LPUART_UART_IP_HWACCESS_AR_RELEASE_MAJOR_VERSION    != LPUART_UART_IP_DEFINES_AR_RELEASE_MAJOR_VERSION) || \
     (LPUART_UART_IP_HWACCESS_AR_RELEASE_MINOR_VERSION    != LPUART_UART_IP_DEFINES_AR_RELEASE_MINOR_VERSION) || \
     (LPUART_UART_IP_HWACCESS_AR_RELEASE_REVISION_VERSION != LPUART_UART_IP_DEFINES_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Lpuart_Uart_Ip_HwAccess.h and Lpuart_Uart_Ip_Defines.h are different"
#endif
#if ((LPUART_UART_IP_HWACCESS_SW_MAJOR_VERSION != LPUART_UART_IP_DEFINES_SW_MAJOR_VERSION) || \
     (LPUART_UART_IP_HWACCESS_SW_MINOR_VERSION != LPUART_UART_IP_DEFINES_SW_MINOR_VERSION) || \
     (LPUART_UART_IP_HWACCESS_SW_PATCH_VERSION != LPUART_UART_IP_DEFINES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Lpuart_Uart_Ip_HwAccess.h and Lpuart_Uart_Ip_Defines.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if current file and Std_Types.h header file are of the same Autosar version */
    #if ((LPUART_UART_IP_HWACCESS_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (LPUART_UART_IP_HWACCESS_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION) \
        )
        #error "Lpuart_Uart_Ip_HwAccess.h and Std_Types.h are different"
    #endif
    /* Check if current file and OsIf.h header file are of the same Autosar version */
    #if ((LPUART_UART_IP_HWACCESS_AR_RELEASE_MAJOR_VERSION != OSIF_AR_RELEASE_MAJOR_VERSION) || \
         (LPUART_UART_IP_HWACCESS_AR_RELEASE_MINOR_VERSION != OSIF_AR_RELEASE_MINOR_VERSION) \
        )
        #error "Lpuart_Uart_Ip_HwAccess.h and OsIf.h are different"
    #endif

    /* Check if current file and SchM_Uart.h header file are of the same Autosar version */
    #if ((LPUART_UART_IP_HWACCESS_AR_RELEASE_MAJOR_VERSION != SCHM_UART_AR_RELEASE_MAJOR_VERSION) || \
         (LPUART_UART_IP_HWACCESS_AR_RELEASE_MINOR_VERSION != SCHM_UART_AR_RELEASE_MINOR_VERSION) \
        )
        #error "Lpuart_Uart_Ip_HwAccess.h and SchM_Uart.h are different"
    #endif
#endif
/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

#define LPUART_FEATURE_DEFAULT_OSR                  (0xFU)
#define LPUART_FEATURE_DEFAULT_SBR                  (0x4U)
#define LPUART_FEATURE_STAT_REG_FLAGS_MASK          (0xC01FC000U)

/**
* @brief          Mask used to verify the DATA registers content.
*/

#define LPUART_IP_DATA_MASK_U32   ((uint32)0x000000FFUL)

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/
/*! @brief LPUART number of bits in a character
 *
 *
 */
/* implements     Lpuart_Uart_Ip_BitCountPerCharType_enum */
typedef enum
{
    LPUART_UART_IP_7_BITS_PER_CHAR  = 0x0U, /*!< 7-bit data characters */
    LPUART_UART_IP_8_BITS_PER_CHAR  = 0x1U, /*!< 8-bit data characters */
    LPUART_UART_IP_9_BITS_PER_CHAR  = 0x2U, /*!< 9-bit data characters */
    LPUART_UART_IP_10_BITS_PER_CHAR = 0x3U  /*!< 10-bit data characters */
} Lpuart_Uart_Ip_BitCountPerCharType;

/*! @brief LPUART parity mode
 *
 *
 */
/* implements     Lpuart_Uart_Ip_ParityModeType_enum */
typedef enum
{
    LPUART_UART_IP_PARITY_DISABLED = 0x0U, /*!< parity disabled */
    LPUART_UART_IP_PARITY_EVEN     = 0x2U, /*!< parity enabled, type even, bit setting: PE|PT = 10 */
    LPUART_UART_IP_PARITY_ODD      = 0x3U  /*!< parity enabled, type odd,  bit setting: PE|PT = 11 */
} Lpuart_Uart_Ip_ParityModeType;

typedef enum
{
    LPUART_UART_IP_ONE_STOP_BIT = 0x0U, /*!< one stop bit */
    LPUART_UART_IP_TWO_STOP_BIT = 0x1U  /*!< two stop bits */
} Lpuart_Uart_Ip_StopBitCountType;

/*!
 * @brief LPUART status flags.
 *
 * This provides constants for the LPUART status flags for use in the UART functions.
 */
typedef enum
{
    LPUART_UART_IP_TX_DATA_REG_EMPTY          = (uint32)LPUART_STAT_TDRE_SHIFT,
                                                /*!< Tx data register empty flag, sets when Tx buffer is empty */
    LPUART_UART_IP_TX_COMPLETE                = (uint32)LPUART_STAT_TC_SHIFT,
                                                /*!< Transmission complete flag, sets when transmission activity complete */
    LPUART_UART_IP_DATA_REG_FULL              = (uint32)LPUART_STAT_RDRF_SHIFT,
                                                /*!< Rx data register full flag, sets when the receive data buffer is full */
    LPUART_UART_IP_RX_OVERRUN                 = (uint32)LPUART_STAT_OR_SHIFT,
                                                /*!< Rx Overrun sets if new data is received before data is read */
    LPUART_UART_IP_NOISE_DETECT               = (uint32)LPUART_STAT_NF_SHIFT,
                                                /*!< Rx takes 3 samples of each received bit. If these differ, the flag sets */
    LPUART_UART_IP_FRAME_ERR                  = (uint32)LPUART_STAT_FE_SHIFT,
                                                /*!< Frame error flag, sets if logic 0 was detected where stop bit expected */
    LPUART_UART_IP_PARITY_ERR                 = (uint32)LPUART_STAT_PF_SHIFT,
#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
    LPUART_UART_IP_TIMEOUT                    = (uint32)LPUART_STAT_IDLE_SHIFT
#endif
} Lpuart_Uart_Ip_StatusFlagType;

/*! @brief LPUART interrupt configuration structure, default settings are 0 (disabled) */
typedef enum
{
    LPUART_UART_IP_INT_TX_DATA_REG_EMPTY = (uint32)LPUART_CTRL_TIE_SHIFT,     /*!< Transmit data register empty. */
    LPUART_UART_IP_INT_TX_COMPLETE       = (uint32)LPUART_CTRL_TCIE_SHIFT,    /*!< Transmission complete. */
    LPUART_UART_IP_INT_RX_DATA_REG_FULL  = (uint32)LPUART_CTRL_RIE_SHIFT,     /*!< Receiver data register full. */
    LPUART_UART_IP_INT_RX_OVERRUN        = (uint32)LPUART_CTRL_ORIE_SHIFT,    /*!< Receiver Overrun. */
    LPUART_UART_IP_INT_NOISE_ERR_FLAG    = (uint32)LPUART_CTRL_NEIE_SHIFT,    /*!< Noise error flag. */
    LPUART_UART_IP_INT_FRAME_ERR_FLAG    = (uint32)LPUART_CTRL_FEIE_SHIFT,    /*!< Framing error flag. */
    LPUART_UART_IP_INT_PARITY_ERR_FLAG   = (uint32)LPUART_CTRL_PEIE_SHIFT,    /*!< Parity error flag. */
#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
    LPUART_UART_IP_INT_TIMEOUT           = (uint32)LPUART_CTRL_ILIE_SHIFT
#endif
} Lpuart_Uart_Ip_InterruptType;

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/

#define UART_START_SEC_CODE
#include "Uart_MemMap.h"

/*!
 * @brief Initializes the LPUART controller.
 *
 * This function Initializes the LPUART controller to known state.
 *
 *
 * @param Base LPUART base pointer.
 */
static inline void Lpuart_Uart_Ip_Hw_Init(LPUART_Type * Base)
{
    /* Set the default oversampling ratio (16) and baud-rate divider (4) */
    Base->BAUD = ((uint32)(((uint32)LPUART_FEATURE_DEFAULT_OSR << LPUART_BAUD_OSR_SHIFT) | \
                 (LPUART_FEATURE_DEFAULT_SBR << LPUART_BAUD_SBR_SHIFT)));
    /* Clear the error/interrupt flags */
    Base->STAT = LPUART_FEATURE_STAT_REG_FLAGS_MASK;
    /* Reset all features/interrupts by default */
    Base->CTRL = 0x00000000;
}

/*!
 * @brief Enable/Disable the LPUART transmitter.
 *
 * This function enables or disables the LPUART transmitter, based on the
 * parameter received.
 *
 *
 * @param Base LPUART base pointer.
 * @param Enable Enable(true) or disable(false) transmitter.
 */
static inline void Lpuart_Uart_Ip_SetTransmitterCmd(LPUART_Type * Base, boolean Enable)
{
    Base->CTRL = (Base->CTRL & ~LPUART_CTRL_TE_MASK) | ((Enable ? 1UL : 0UL) << LPUART_CTRL_TE_SHIFT);
}

/*!
 * @brief Enable/Disable the LPUART receiver.
 *
 * This function enables or disables the LPUART receiver, based on the
 * parameter received.
 *
 *
 * @param Base LPUART base pointer
 * @param Enable Enable(true) or disable(false) receiver.
 */
static inline void Lpuart_Uart_Ip_SetReceiverCmd(LPUART_Type * Base, boolean Enable)
{
    Base->CTRL = (Base->CTRL & ~LPUART_CTRL_RE_MASK) | ((Enable ? 1UL : 0UL) << LPUART_CTRL_RE_SHIFT);
}

/*!
 * @brief Sets the LPUART baud rate modulo divisor.
 *
 * This function sets the LPUART baud rate modulo divisor.
 *
 *
 * @param Base LPUART base pointer.
 * @param baudRateDivisor The baud rate modulo division "SBR"
 */
static inline void Lpuart_Uart_Ip_SetBaudRateDivisor(LPUART_Type * Base, uint32 baudRateDivisor)
{
    Base->BAUD = (Base->BAUD & ~LPUART_BAUD_SBR_MASK) | (baudRateDivisor & LPUART_BAUD_SBR_MASK);
}

/*!
 * @brief Gets the LPUART baud rate modulo divisor.
 *
 * This function gets the LPUART baud rate modulo divisor.
 *
 *
 * @param Base LPUART base pointer.
 * @return The baud rate modulo division "SBR"
 */
static inline uint16 Lpuart_Uart_Ip_GetBaudRateDivisor(const LPUART_Type * Base)
{
    return ((uint16)((Base->BAUD & LPUART_BAUD_SBR_MASK) >> LPUART_BAUD_SBR_SHIFT));
}

/*!
 * @brief Sets the LPUART baud rate oversampling ratio
 *
 * This function sets the LPUART baud rate oversampling ratio.
 * (Note: Feature available on select LPUART instances used together with baud rate programming)
 * The oversampling ratio should be set between 4x (00011) and 32x (11111). Writing
 * an invalid oversampling ratio results in an error and is set to a default
 * 16x (01111) oversampling ratio.
 * Disable the transmitter/receiver before calling this function.
 *
 *
 * @param Base LPUART base pointer.
 * @param OverSamplingRatio The oversampling ratio "OSR"
 */
static inline void Lpuart_Uart_Ip_SetOversamplingRatio(LPUART_Type * Base, uint32 OverSamplingRatio)
{
    Base->BAUD = (Base->BAUD & ~LPUART_BAUD_OSR_MASK) | LPUART_BAUD_OSR(OverSamplingRatio);
}

/*!
 * @brief Gets the LPUART baud rate oversampling ratio
 *
 * This function gets the LPUART baud rate oversampling ratio.
 * (Note: Feature available on select LPUART instances used together with baud rate programming)
 *
 *
 * @param Base LPUART base pointer.
 * @return The oversampling ratio "OSR"
 */
static inline uint8 Lpuart_Uart_Ip_GetOversamplingRatio(const LPUART_Type * Base)
{
    return ((uint8)((Base->BAUD & LPUART_BAUD_OSR_MASK) >> LPUART_BAUD_OSR_SHIFT));
}


/*!
 * @brief Configures the LPUART baud rate both edge sampling
 *
 * This function configures the LPUART baud rate both edge sampling.
 * (Note: Feature available on select LPUART instances used with baud rate programming)
 * When enabled, the received data is sampled on both edges of the baud rate clock.
 * This must be set when the oversampling ratio is between 4x and 7x.
 * This function should only be called when the receiver is disabled.
 *
 *
 * @param Base LPUART base pointer.
 */
static inline void Lpuart_Uart_Ip_EnableBothEdgeSamplingCmd(LPUART_Type * Base)
{
    Base->BAUD |= LPUART_BAUD_BOTHEDGE_MASK;
}

/*!
 * @brief Configures the number of bits per character in the LPUART controller.
 *
 * This function configures the number of bits per character in the LPUART controller.
 * In some LPUART instances, the user should disable the transmitter/receiver
 * before calling this function.
 * Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param Base LPUART base pointer.
 * @param BitCountPerChar  Number of bits per char (7, 8, 9, or 10, depending on the LPUART instance)
 * @param Parity  Specifies whether parity bit is enabled
 */
static inline void Lpuart_Uart_Ip_SetBitCountPerChar(LPUART_Type * Base,
                                                     Lpuart_Uart_Ip_BitCountPerCharType BitCountPerChar,
                                                     boolean Parity
                                                    )
{
    uint32 TmpBitCountPerChar = (uint32)BitCountPerChar;

    if (Parity)
    {
        TmpBitCountPerChar += 1U;
    }

    if ((uint32)LPUART_UART_IP_10_BITS_PER_CHAR == TmpBitCountPerChar)
    {
        Base->BAUD = (Base->BAUD & ~LPUART_BAUD_M10_MASK) | ((uint32)1U << LPUART_BAUD_M10_SHIFT);
    }
    else
    {
        if (LPUART_UART_IP_7_BITS_PER_CHAR == BitCountPerChar)
        {
            /* Check if parity is enabled or not*/
            if (Parity)
            {
                /* clear M7 to make sure not 7-bit mode (M7 = 0) and config 8 bits (M = 0) */
                Base->CTRL &= ~(LPUART_CTRL_M7_MASK | LPUART_CTRL_M_MASK);
            }
            else
            {
                /* config 7-bits (M7 = 1)*/
                Base->CTRL = (Base->CTRL & ~LPUART_CTRL_M7_MASK) | ((uint32)1U << LPUART_CTRL_M7_SHIFT);
            }
        }
        else
        {
            TmpBitCountPerChar -= 1U;
            /* config 8-bit (M=0) or 9-bits (M=1) */
            Base->CTRL = (Base->CTRL & ~LPUART_CTRL_M_MASK) | (TmpBitCountPerChar << LPUART_CTRL_M_SHIFT);
        }
        /* clear M10 to make sure not 10-bit mode */
        Base->BAUD &= ~LPUART_BAUD_M10_MASK;
    }
}


/*!
 * @brief Configures parity mode in the LPUART controller.
 *
 * This function configures parity mode in the LPUART controller.
 * In some LPUART instances, the user should disable the transmitter/receiver
 * before calling this function.
 * Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param Base LPUART base pointer.
 * @param ParityModeType  Parity mode (enabled, disable, odd, even - see parity_mode_t struct)
 */
static inline void Lpuart_Uart_Ip_SetParityMode(LPUART_Type * Base, Lpuart_Uart_Ip_ParityModeType ParityModeType)
{
    Base->CTRL = (Base->CTRL & ~LPUART_CTRL_PE_MASK) | (((uint32)ParityModeType >> 1U) << LPUART_CTRL_PE_SHIFT);
    Base->CTRL = (Base->CTRL & ~LPUART_CTRL_PT_MASK) | (((uint32)ParityModeType & 1U) << LPUART_CTRL_PT_SHIFT);
}

/*!
 * @brief Configures the number of stop bits in the LPUART controller.
 *
 * This function configures the number of stop bits in the LPUART controller.
 * In some LPUART instances, the user should disable the transmitter/receiver
 * before calling this function.
 * Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param Base LPUART base pointer.
 * @param StopBitCount Number of stop bits (1 or 2 - see Lpuart_Uart_Ip_StopBitCountType struct)
 */
static inline void Lpuart_Uart_Ip_SetStopBitCount(LPUART_Type * Base, Lpuart_Uart_Ip_StopBitCountType StopBitCount)
{
    Base->BAUD = (Base->BAUD & ~LPUART_BAUD_SBNS_MASK) | ((uint32)StopBitCount << LPUART_BAUD_SBNS_SHIFT);
}


/*!
 * @brief Configures the LPUART module interrupts.
 *
 * This function configures the LPUART module interrupts to enable/disable various interrupt sources.
 *
 *
 * @param   Base LPUART module base pointer.
 * @param   IntSrc LPUART interrupt configuration data.
 * @param   Enable   true: enable, false: disable.
 */
static inline void Lpuart_Uart_Ip_SetIntMode(LPUART_Type * Base, Lpuart_Uart_Ip_InterruptType IntSrc, boolean Enable)
{
    Base->CTRL = (Base->CTRL & ~(1UL << (uint32)IntSrc)) | ((Enable ? 1UL : 0UL) << (uint32)IntSrc);
}

/*!
 * @brief Returns LPUART module interrupts state.
 *
 * This function returns whether a certain LPUART module interrupt is enabled or disabled.
 *
 *
 * @param   Base LPUART module base pointer.
 * @param   IntSrc LPUART interrupt configuration data.
 * @return  true: enable, false: disable.
 */
static inline boolean Lpuart_Uart_Ip_GetIntMode(const LPUART_Type * Base, Lpuart_Uart_Ip_InterruptType IntSrc)
{
    boolean RetVal = FALSE;

    RetVal = (((Base->CTRL >> (uint32)(IntSrc)) & 1U) > 0U);
    return RetVal;
}

#if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
/*!
 * @brief Configures DMA requests.
 *
 * This function configures DMA requests for LPUART Transmitter.
 *
 *
 * @param Base LPUART base pointer
 * @param Enable Transmit DMA request configuration (enable:1 /disable: 0)
 */
static inline void Lpuart_Uart_Ip_SetTxDmaCmd(LPUART_Type * Base, boolean Enable)
{
    Base->BAUD = (Base->BAUD & ~LPUART_BAUD_TDMAE_MASK) | ((Enable ? 1UL : 0UL) << LPUART_BAUD_TDMAE_SHIFT);
}

/*!
 * @brief Configures DMA requests.
 *
 * This function configures DMA requests for LPUART Receiver.
 *
 *
 * @param Base LPUART base pointer
 * @param Enable Receive DMA request configuration (enable: 1/disable: 0)
 */
static inline void Lpuart_Uart_Ip_SetRxDmaCmd(LPUART_Type * Base, boolean Enable)
{
    Base->BAUD = (Base->BAUD & ~LPUART_BAUD_RDMAE_MASK) | ((Enable ? 1UL : 0UL) << LPUART_BAUD_RDMAE_SHIFT);
}
#endif

/*!
 * @brief Sends the LPUART 8-bit character.
 *
 * This functions sends an 8-bit character.
 *
 *
 * @param Base LPUART Instance
 * @param Data     data to send (8-bit)
 */
static inline void Lpuart_Uart_Ip_Putchar(LPUART_Type * Base, uint8 Data)
{
    volatile uint8 * DataRegBytes = (volatile uint8 *)(&(Base->DATA));

    DataRegBytes[0] = Data;
}

/*!
 * @brief Sends the LPUART 9-bit character.
 *
 * This functions sends a 9-bit character.
 *
 *
 * @param Base LPUART Instance
 * @param Data     data to send (9-bit)
 */
static inline void Lpuart_Uart_Ip_Putchar9(LPUART_Type * Base, uint16 Data)
{
    uint8 NinthDataBit;
    volatile uint8 * DataRegBytes = (volatile uint8 *)(&(Base->DATA));


    NinthDataBit = (uint8)((Data >> 8U) & 0x1U);

    /* write to ninth data bit T8(where T[0:7]=8-bits, T8=9th bit) */
    Base->CTRL = (Base->CTRL & ~LPUART_CTRL_R9T8_MASK) | ((uint32)(NinthDataBit) << LPUART_CTRL_R9T8_SHIFT);

    /* write 8-bits to the data register*/
    DataRegBytes[0] = (uint8)Data;
}

/*!
 * @brief Sends the LPUART 10-bit character (Note: Feature available on select LPUART instances).
 *
 * This functions sends a 10-bit character.
 *
 *
 * @param Base LPUART Instance
 * @param Data   data to send (10-bit)
 */
static inline void Lpuart_Uart_Ip_Putchar10(LPUART_Type * Base, uint16 Data)
{
    uint8 NinthDataBit, TenthDataBit;
    uint32 CtrlRegVal;
    volatile uint8 * DataRegBytes = (volatile uint8 *)(&(Base->DATA));

    NinthDataBit = (uint8)((Data >> 8U) & 0x1U);
    TenthDataBit = (uint8)((Data >> 9U) & 0x1U);

    /* write to ninth/tenth data bit (T[0:7]=8-bits, T8=9th bit, T9=10th bit) */
    CtrlRegVal = Base->CTRL;
    CtrlRegVal = (CtrlRegVal & ~LPUART_CTRL_R9T8_MASK) | ((uint32)NinthDataBit << LPUART_CTRL_R9T8_SHIFT);
    CtrlRegVal = (CtrlRegVal & ~LPUART_CTRL_R8T9_MASK) | ((uint32)TenthDataBit << LPUART_CTRL_R8T9_SHIFT);
    /*Note: T8(9th bit) and T9(10th bit) should be written at same time. */
    Base->CTRL = CtrlRegVal;

    /* write to 8-bits to the Data register */
    DataRegBytes[0] = (uint8)Data;
}

/*!
 * @brief Gets the LPUART 8-bit character.
 *
 * This functions receives an 8-bit character.
 *
 *
 * @param Base LPUART base pointer
 * @param ReadData Data read from receive (8-bit)
 */
static inline uint8 Lpuart_Uart_Ip_Getchar(const LPUART_Type * Base)
{
    return (uint8)(Base->DATA & LPUART_IP_DATA_MASK_U32);
}

/*!
 * @brief Gets the LPUART 9-bit character.
 *
 * This functions receives a 9-bit character.
 *
 *
 * @param Base LPUART base pointer
 */
static inline uint16 Lpuart_Uart_Ip_Getchar9(const LPUART_Type * Base)
{
    uint16 ReadData;

    /* get ninth bit from lpuart data register */
    ReadData = (uint16)(((Base->CTRL >> LPUART_CTRL_R8T9_SHIFT) & 1U) << 8);

    /* get 8-bit data from the lpuart data register */
    ReadData |= (uint8)(Base->DATA & LPUART_IP_DATA_MASK_U32);
    return ReadData;
}

/*!
 * @brief Gets the LPUART 10-bit character.
 *
 * This functions receives a 10-bit character.
 *
 *
 * @param Base LPUART Base pointer
 */
static inline uint16 Lpuart_Uart_Ip_Getchar10(const LPUART_Type * Base)
{
    uint16 ReadData;

    /* read tenth data bit */
    ReadData = (uint16)(((Base->CTRL >> LPUART_CTRL_R9T8_SHIFT) & 1U) << 9);
    /* read ninth data bit */
    ReadData |= (uint16)(((Base->CTRL >> LPUART_CTRL_R8T9_SHIFT) & 1U) << 8);

    /* get 8-bit data */
    ReadData |= (uint8)(Base->DATA & LPUART_IP_DATA_MASK_U32);
    return ReadData;
}

/*!
 * @brief  LPUART get status flag
 *
 * This function returns the state of a status flag.
 *
 *
 * @param Base LPUART base pointer
 * @param StatusFlag  The status flag to query
 * @return Whether the current status flag is set(true) or not(false).
 */
static inline boolean Lpuart_Uart_Ip_GetStatusFlag(const LPUART_Type * Base, Lpuart_Uart_Ip_StatusFlagType StatusFlag)
{
    boolean RetVal = FALSE;

    RetVal = (((Base->STAT >> (uint32)(StatusFlag)) & 1U) > 0U);
    return RetVal;
}
/*!
 * @brief LPUART clears an individual status flag.
 *
 * This function clears an individual status flag (see Lpuart_Uart_Ip_StatusFlagType for list of status bits).
 *
 *
 * @param Base LPUART base pointer
 * @param StatusFlag  Desired LPUART status flag to clear
 * @return LPUART_UART_IP_STATUS_SUCCESS if successful or STATUS_ERROR if an error occured
 */
static inline void Lpuart_Uart_Ip_ClearStatusFlag(LPUART_Type * Base, Lpuart_Uart_Ip_StatusFlagType StatusFlag)
{
    switch (StatusFlag)
    {
        case LPUART_UART_IP_RX_OVERRUN:
            Base->STAT = (Base->STAT & (~LPUART_FEATURE_STAT_REG_FLAGS_MASK)) | LPUART_STAT_OR_MASK;
            break;

        case LPUART_UART_IP_NOISE_DETECT:
            Base->STAT = (Base->STAT & (~LPUART_FEATURE_STAT_REG_FLAGS_MASK)) | LPUART_STAT_NF_MASK;
            break;

        case LPUART_UART_IP_FRAME_ERR:
            Base->STAT = (Base->STAT & (~LPUART_FEATURE_STAT_REG_FLAGS_MASK)) | LPUART_STAT_FE_MASK;
            break;

        case LPUART_UART_IP_PARITY_ERR:
            Base->STAT = (Base->STAT & (~LPUART_FEATURE_STAT_REG_FLAGS_MASK)) | LPUART_STAT_PF_MASK;
            break;
#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
        case LPUART_UART_IP_TIMEOUT:
            Base->STAT = (Base->STAT & (~LPUART_FEATURE_STAT_REG_FLAGS_MASK)) | LPUART_STAT_IDLE_MASK;
            break;
#endif
        default:
            /* Dummy code */
            break;
    }
}

/*!
 * @brief LPUART clears an individual status flag.
 *
 * This function clears an individual status flag (see Lpuart_Uart_Ip_StatusFlagType for list of status bits).
 *
 *
 * @param Base LPUART base pointer
 * @param Mask  LPUART Status Register Mask to clear
 */
static inline void Lpuart_Uart_Ip_ClearStatusFlagWithMask(LPUART_Type * Base, uint32 Mask)
{
    Base->STAT = (Base->STAT & (~LPUART_FEATURE_STAT_REG_FLAGS_MASK)) | Mask;
}

/*!
 * @brief  Clears the error flags treated by the driver
 *
 * This function clears the error flags treated by the driver.
 * *
 * @param Base LPUART Base pointer
 */
static inline void Lpuart_Uart_Ip_ClearErrorFlags(LPUART_Type * Base)
{
    uint32 Mask = LPUART_STAT_OR_MASK | \
                  LPUART_STAT_NF_MASK | \
                  LPUART_STAT_FE_MASK | \
                  LPUART_STAT_PF_MASK;

    Base->STAT = (Base->STAT & (~LPUART_FEATURE_STAT_REG_FLAGS_MASK)) | Mask;
}

/**
 * @brief   : Prepare for timeout checking
 * @internal
 * @return  : None
 */
static inline void Lpuart_Uart_Ip_StartTimeout(uint32 *StartTimeOut, uint32 *TimeoutTicksOut, uint32 TimeoutUs, OsIf_CounterType OsifCounter)
{
    *StartTimeOut    = OsIf_GetCounter(OsifCounter);
    *TimeoutTicksOut = OsIf_MicrosToTicks(TimeoutUs, OsifCounter);
}

/**
 * @brief   : Checks for timeout condition
 * @internal
 * @return  TRUE     Timeout occurs
 *          FALSE    Timeout does not occur
 */
static inline boolean Lpuart_Uart_Ip_CheckTimeout(uint32 * StartTime, uint32 * ElapsedTicks, uint32 TimeoutTicks, OsIf_CounterType OsifCounter)
{
    boolean RetVal = FALSE;
    uint32 CurrentElapsedTicks = OsIf_GetElapsed(StartTime, OsifCounter);

    *ElapsedTicks += CurrentElapsedTicks;
    if (*ElapsedTicks >= TimeoutTicks)
    {
        RetVal = TRUE;
    }

    return RetVal;
}

/**
 * @brief   : Flush Tx Buffer
 *
 * This function causes all data that is stored in the transmit FIFO/buffer to be flushed.
 * *
 * @param Base LPUART Base pointer
 */
static inline void Lpuart_Uart_Ip_FlushTxBuffer(LPUART_Type * Base)
{
    Base->FIFO |= LPUART_FIFO_TXFLUSH_MASK;
}

/**
 * @brief   : Flush Rx Buffer
 *
 * This function causes all data that is stored in the receive FIFO/buffer to be flushed.
 * *
 * @param Base LPUART Base pointer
 */
static inline void Lpuart_Uart_Ip_FlushRxBuffer(LPUART_Type * Base)
{
    Base->FIFO |= LPUART_FIFO_RXFLUSH_MASK;
}

#if (LPUART_UART_IP_ENABLE_INTERNAL_LOOPBACK == STD_ON)
/**
 * @brief   : Enter Internal Loopbackmode
 *
 * *
 * @param Base LPUART Base pointer
 */
static inline void Lpuart_Uart_Ip_EnableInternalLoopback(LPUART_Type * Base)
{
    Base->CTRL = (Base->CTRL & ~LPUART_CTRL_RSRC_MASK) | (1UL << LPUART_CTRL_LOOPS_SHIFT);
}
#endif

#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
/**
 * @brief   : Enable Timeout Interrupt
 *
 * *
 * @param Base LPUART Base pointer
 */
static inline void Lpuart_Uart_Ip_SetupIdleInterrupt(LPUART_Type * Base)
{
    /* Configures the number of idle characters that must be received before the IDLE flag is set - 1 idle character */
    Base->CTRL = Base->CTRL | LPUART_CTRL_IDLECFG(0);
    /* Idle character bit count starts after stop bit */
    Base->CTRL = (Base->CTRL & ~LPUART_CTRL_ILT_MASK) | (1UL << LPUART_CTRL_ILT_SHIFT);
}
#endif

#define UART_STOP_SEC_CODE
#include "Uart_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* LPUART_HW_ACCESS_H */
