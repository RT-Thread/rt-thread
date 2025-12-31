/**
  * @file                ft32f4xx_uart.h
  * @author              FMD AE
  * @brief               This file contains all the functions prototypes for the UART
  *                      fireware library.
  * @version             V1.0.0
  * @date                2025-03-28
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_UART_H
#define __FT32F4XX_UART_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"

/** @addtogroup ft32f4xx_Driver
  * @{
  */

/** @addtogroup UART
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup UART_Exported_Types SART Exported Types
  * @{
  */

/**
  * @brief UART Init Structure definition
  */
typedef struct
{
    uint32_t UART_BaudRate;                  /*!< This member configures the UART communication baud rate.
                                                 The baud rate is computed using the following formula:
                                                 - CD = 0: Disable baud rate clock

                                                 - Asynchronous mode
                                                    - X16        : IntegerDivider  = ((PCLKx) / (16 * (UART_InitStruct->UART_BaudRate)))
                                                    - X8         : IntegerDivider  = ((PCLKx) / (8  * (UART_InitStruct->UART_BaudRate)))
                                           */

    uint32_t UART_FiDiRatio;                 /*!< Specifies the value of FI over DI ratio value in IrDA mode.
                                                @note This parameter is valid only for UART4, UART5 and UART7, except for LPUART.*/

    uint32_t UART_IrDAFilter;                /*!< Specifies the value of IrDA filter in IrDA mode.
                                                @note This parameter is valid only for UART4, UART5 and UART7, except for LPUART.*/

    uint32_t UART_WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
                                                 This parameter can be a value of @ref UART_Char_Length & UART_Char_Length9*/

    uint32_t UART_StopBits;                  /*!< Specifies the number of stop bits transmitted.
                                                 This parameter can be a value of @ref UART_Stop_Bits*/

    uint32_t UART_Parity;                    /*!< Specifies the parity mode.
                                                 This parameter can be a value of @ref UART_Parity
                                                 @note When parity is enabled, the computed parity is inserted
                                                       at the MSB position of the transmitted data (9th bit when
                                                       the word length is set to 9 data bits; 8th bit when the
                                                       word length is set to 8 data bits). */

    uint32_t UART_Mode;                      /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
                                                 This parameter can be a value of @ref UART_Mode*/

    uint32_t UART_CLKSelect;                 /*!< Specifies the selection of clock.
                                                 This parameter can be a value of @ref UART_Clock_Select*/

    uint32_t UART_OperationMode;             /*!< Specifies the mode of operation.
                                                 This parameter can be a value of @ref UART_Mode_Operation*/

    uint32_t UART_BitOrder;                  /*!< Specifies whether the Least or Most Significant Bit is sent/received first.
                                                 This parameter can be a value of @ref UART_BIT_ORDER*/

    uint32_t UART_ChannelMode;               /*!< Specifies the channel mode select.
                                                 this parameter can be a value of @ref UART_Channel_Mode*/

    uint32_t UART_OverSampling;              /*!< Specifies whether 16x oversampling or 8x oversampling.
                                                 This parameter can be a value of @ref UART_OverSampling*/

    uint32_t UART_INVData;                   /*!< Specifies whether the data is inverted.
                                                 This parameter can be a value of @ref UART_InvertData
                                                 @note This parameter is valid only for UART4, UART5 and UART7, except for LPUART.*/

    uint32_t UART_SYNCDisable;               /*!< Specifies whether disable the synchronization in LIN mode.
                                                 This parameter can be a value of @ref UART_Sync_Disable
                                                 @note This parameter is valid only for UART4, UART5 and UART7, except for LPUART.*/

    uint32_t UART_PDCMode;                   /*!< Specifies the DMA mode selection in LIN mode.
                                                 This parameter can be a value of @ref UART_PDC_Mode
                                                 @note This parameter is valid only for UART4, UART5 and UART7, except for LPUART.*/

    uint32_t UART_DataLengthControl;         /*!< Specifies define the response data length when DataLengthMode = 0 in LIN mode.
                                                 0-255: the response data length is equal to DLC+1 bytes.
                                                 @note This parameter is valid only for UART4, UART5 and UART7, except for LPUART.*/

    uint32_t UART_WkupType;                  /*!< Specifies whether the wakeup signal type is LIN2.0 wakup signal or LIN1.3 wakup signal.
                                                 This parameter can be a value of @ref UART_Wkup_Type
                                                 @note This parameter is valid only for UART4, UART5 and UART7, except for LPUART.*/

    uint32_t UART_FrameSlotDisable;          /*!< Specifies whether disable the frame slot mode in LIN mode.
                                                 This parameter can be a value of @ref UART_Frame_Slot_Disable
                                                 @note This parameter is valid only for UART4, UART5 and UART7, except for LPUART.*/

    uint32_t UART_DataLengthMode;            /*!< Specifies the data length mode in LIN mode.
                                                 This parameter can be a value of @ref UART_Data_Length_Mode
                                                 @note This parameter is valid only for UART4, UART5 and UART7, except for LPUART.*/

    uint32_t UART_CheckSumType;              /*!< Specifies the checksum type in LIN mode.
                                                 This parameter can be a value of @ref UART_Checksum_Type
                                                 @note This parameter is valid only for UART4, UART5 and UART7, except for LPUART.*/

    uint32_t UART_CheckSumDisable;           /*!< Specifies whether disable the checksum in LIN mode.
                                                 This parameter can be a value of @ref UART_Checksum_Disable
                                                 @note This parameter is valid only for UART4, UART5 and UART7, except for LPUART.*/

    uint32_t UART_ParityDisable;             /*!< Specifies whether disable the parity in LIN mode.
                                                 This parameter can be a value of @ref UART_Parity_Disable
                                                 @note This parameter is valid only for UART4, UART5 and UART7, except for LPUART.*/

    uint32_t UART_NodeAction;                /*!< Specifies the LIN Node Active.
                                                 This parameter can be a value of @ref UART_Node_Active
                                                 @note This parameter is valid only for UART4, UART5 and UART7, except for LPUART.*/

} UART_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup UART_Exported_Constants UART Exported Constants
  * @{
  */

#define IS_UART_ALL_PERIPH(PERIPH) (                         \
                                     ((PERIPH) == UART4 ) || \
                                     ((PERIPH) == UART5 ) || \
                                     ((PERIPH) == UART7 ) || \
                                     ((PERIPH) == LPUART)    \
                                    )

#define IS_UART_45_PERIPH(PERIPH)  (                         \
                                     ((PERIPH) == UART4 ) || \
                                     ((PERIPH) == UART5 )    \
                                    )

#define IS_UART_457_PERIPH(PERIPH) (                         \
                                     ((PERIPH) == UART4 ) || \
                                     ((PERIPH) == UART5 ) || \
                                     ((PERIPH) == UART7 )    \
                                    )

#define IS_UART_LP_PERIPH(PERIPH)   (                        \
                                     ((PERIPH) == LPUART)    \
                                    )

/** @defgroup UART_InvertData  UART Invert Data
  * @{
  */
#define UART_INVDATA_DISABLE                                 ((uint32_t)0x00000000U)        /*!< UART invert data disbale */
#define UART_INVDATA_ENABLE                                  USART_MR_INVDATA               /*!< UART invert data enable  */

#define IS_UART_INVDATA(INVDATA)                                 \
                         (                                       \
                          ((INVDATA) == UART_INVDATA_DISABLE) || \
                          ((INVDATA) == UART_INVDATA_ENABLE )    \
                         )
/**
  * @}
  */

/** @defgroup UART_OverSampling  UART Oversampling mode
  * @{
  */
#define UART_OVERSAMPLING_16                                ((uint32_t)0x00000000U)         /*!< UART 16x sampling */
#define UART_OVERSAMPLING_8                                 USART_MR_OVER                   /*!< UART 8x  sampling */

#define IS_UART_OVERSAMPLING(OVERSAMPLING)                            \
                         (                                            \
                          ((OVERSAMPLING) == UART_OVERSAMPLING_16) || \
                          ((OVERSAMPLING) == UART_OVERSAMPLING_8 )    \
                         )
/**
  * @}
  */

/** @defgroup UART_Char_Length9  UART 9-bit character length
  * @{
  */
#define UART_CHAR_LENGTH9_DISABLE                            ((uint32_t)0x00000000U)         /*!< UART CHRL defined character length */
#define UART_CHAR_LENGTH9_ENABLE                             USART_MR_MODE9                  /*!< UART 9-bit character length        */

/**
  * @}
  */

/** @defgroup UART_BIT_ORDER  UART bit order
  * @{
  */
#define UART_BIT_ORDER_LSBF                                 ((uint32_t)0x00000000U)         /*!< UART Least Significant Bit is sent/received first */
#define UART_BIT_ORDER_MSBF                                 USART_MR_MSBF                   /*!< UART Most  Significant Bit is sent/received first */

#define IS_UART_BIT_ORDER(ORDER)                              \
                         (                                    \
                          ((ORDER) == UART_BIT_ORDER_LSBF) || \
                          ((ORDER) == UART_BIT_ORDER_MSBF)    \
                         )
/**
  * @}
  */

/** @defgroup UART_Channel_Mode  UART channel mode
  * @{
  */
#define UART_CHANNEL_MODE_NORMAL                            (0x0UL << 14U         )         /*!< UART operates in normal mode          */
#define UART_CHANNEL_MODE_AUTOMATIC                         (0x1UL << 14U         )         /*!< UART operates in automatic echo mode  */
#define UART_CHANNEL_MODE_LOCAL_LOOPBACK                    (0x2UL << 14U         )         /*!< UART operates in local loopback mode  */
#define UART_CHANNEL_MODE_REMOTE_LOOPBACK                   (0x3UL << 14U         )         /*!< UART operates in remote loopback mode */

#define IS_UART_CHANNEL_MODE(MODE)                                         \
                         (                                                 \
                          ((MODE) == UART_CHANNEL_MODE_NORMAL         ) || \
                          ((MODE) == UART_CHANNEL_MODE_AUTOMATIC      ) || \
                          ((MODE) == UART_CHANNEL_MODE_LOCAL_LOOPBACK ) || \
                          ((MODE) == UART_CHANNEL_MODE_REMOTE_LOOPBACK)    \
                         )
/**
  * @}
  */

/** @defgroup UART_Stop_Bits  UART Number of Stop Bits
  * @{
  */
#define UART_STOPBITS_1                                     ((uint32_t)0x00000000U)         /*!< UART frame with 1 stop bit    */
#define UART_STOPBITS_1_5                                   (0x1UL << 12U)                  /*!< UART frame with 1.5 stop bits */
#define UART_STOPBITS_2                                     (0x2UL << 12U)                  /*!< UART frame with 2 stop bits   */

#define IS_UART_STOPBITS(STOPBITS)                             \
                         (                                     \
                          ((STOPBITS) == UART_STOPBITS_1  ) || \
                          ((STOPBITS) == UART_STOPBITS_1_5) || \
                          ((STOPBITS) == UART_STOPBITS_2  )    \
                         )
/**
  * @}
  */

/** @defgroup UART_Parity    UART Parity
  * @{
  */
#define UART_PARITY_EVEN                                    (0x0 << 9U)                     /*!< Even  parity   */
#define UART_PARITY_ODD                                     (0x1 << 9U)                     /*!< Odd   parity   */
#define UART_PARITY_SPACE                                   (0x2 << 9U)                     /*!< Space parity   */
#define UART_PARITY_MARK                                    (0x3 << 9U)                     /*!< Mark  parity   */
#define UART_PARITY_NONE                                    (0x4 << 9U)                     /*!< No    parity   */
#define UART_PARITY_MULTIDROP                               (0x6 << 9U)                     /*!< Multidrop Mode */

#define IS_UART_PARITY(PARITY)                                   \
                         (                                       \
                          ((PARITY) == UART_PARITY_EVEN     ) || \
                          ((PARITY) == UART_PARITY_ODD      ) || \
                          ((PARITY) == UART_PARITY_SPACE    ) || \
                          ((PARITY) == UART_PARITY_MARK     ) || \
                          ((PARITY) == UART_PARITY_NONE     ) || \
                          ((PARITY) == UART_PARITY_MULTIDROP)    \
                         )
/**
  * @}
  */

/** @defgroup UART_Char_Length  UART character length
  * @{
  */
#define UART_CHAR_LENGTH_5BIT                               ((uint32_t)0x00000000U)         /*!< UART charcter length is 5bits */
#define UART_CHAR_LENGTH_6BIT                               (0x1U << 6U)                    /*!< UART charcter length is 6bits */
#define UART_CHAR_LENGTH_7BIT                               (0x2U << 6U)                    /*!< UART charcter length is 7bits */
#define UART_CHAR_LENGTH_8BIT                               (0x3U << 6U)                    /*!< UART charcter length is 8bits */

#define IS_UART_CHAR_LENGTH(LENGTH)                                  \
                         (                                           \
                          ((LENGTH) == UART_CHAR_LENGTH_5BIT)     || \
                          ((LENGTH) == UART_CHAR_LENGTH_6BIT)     || \
                          ((LENGTH) == UART_CHAR_LENGTH_7BIT)     || \
                          ((LENGTH) == UART_CHAR_LENGTH_8BIT)     || \
                          ((LENGTH) == UART_CHAR_LENGTH9_DISABLE) || \
                          ((LENGTH) == UART_CHAR_LENGTH9_ENABLE )    \
                         )
/**
  * @}
  */

/** @defgroup UART_Clock_Select  UART clock select
  * @{
  */
#define UART_CLOCK_SELECT_MCK                               ((uint32_t)0x00000000U)         /*!< UART clock source MCK     */
#define UART_CLOCK_SELECT_MCKDIV8                           (0x1U << 4U)                    /*!< UART clock source MCK / 8 */

#define IS_UART_CLOCK_SELECT(SELECT)                                 \
                         (                                           \
                          ((SELECT) == UART_CLOCK_SELECT_MCK    ) || \
                          ((SELECT) == UART_CLOCK_SELECT_MCKDIV8)    \
                         )
/**
  * @}
  */

/** @defgroup UART_Mode_Operation  UART mode of operation
  * @{
  */
#define UART_MODE_OPERATION_NORMAL                          ((uint32_t)0x00000000U)         /*!< UART mode of operation select normal                                          */
#define UART_MODE_OPERATION_IrDA                            (0x8U << 0U)                    /*!< UART mode of operation select irda
                                                                                                 @note This define is valid only for UART4, UART5 and UART7, except for LPUART.*/
#define UART_MODE_OPERATION_LIN_MASTER                      (0xAU << 0U)                    /*!< UART mode of operation select lin master
                                                                                                 @note This define is valid only for UART4, UART5 and UART7, except for LPUART.*/
#define UART_MODE_OPERATION_LIN_SLAVE                       (0xBU << 0U)                    /*!< UART mode of operation select lin slave
                                                                                                 @note This define is valid only for UART4, UART5 and UART7, except for LPUART.*/

#define IS_UART_MODE_OPERATION(OPERATION)                                     \
                         (                                                    \
                          ((OPERATION) == UART_MODE_OPERATION_NORMAL     ) || \
                          ((OPERATION) == UART_MODE_OPERATION_IrDA       ) || \
                          ((OPERATION) == UART_MODE_OPERATION_LIN_MASTER ) || \
                          ((OPERATION) == UART_MODE_OPERATION_LIN_SLAVE  )    \
                         )
/**
  * @}
  */

/** @defgroup UART_Mode   UART Mode
  * @{
  */
#define UART_MODE_RX                       USART_CR_RXEN                         /*!< RX mode        */
#define UART_MODE_TX                       USART_CR_TXEN                         /*!< TX mode        */
#define UART_MODE_TX_RX                    (USART_CR_TXEN | USART_CR_RXEN)       /*!< RX and TX mode */
#define IS_UART_MODE(MODE)                               \
                         (                               \
                          ((MODE) == UART_MODE_RX   ) || \
                          ((MODE) == UART_MODE_TX   ) || \
                          ((MODE) == UART_MODE_TX_RX)    \
                         )
/**
  * @}
  */

/** @defgroup UART_Sync_Disable  UART synchronization disable in lin mode
  * @{
  */
#define UART_SYNC_DISABLE_NONE                              ((uint32_t)0x00000000)          /*!< the synchronization procedure is performed in LIN Slave node configuration in LIN mode     */
#define UART_SYNC_DISABLE_ACTIVE                            USART_LINMR_SYNCDIS             /*!< the synchronization procedure is not performed in LIN Slave node configuration in LIN mode */

#define IS_UART_SYNC_DISABLE(DISABLE)                                \
                         (                                           \
                          ((DISABLE) == UART_SYNC_DISABLE_NONE  ) || \
                          ((DISABLE) == UART_SYNC_DISABLE_ACTIVE)    \
                         )
/**
  * @}
  */

/** @defgroup UART_PDC_Mode  UART DMA mode in LIN mode
  * @{
  */
#define UART_PDC_MODE_LINMR_NOTWRITE                        ((uint32_t)0x00000000)          /*!< The LIN mode register LINMR is not writted by the DMA                  */
#define UART_PDC_MODE_LINMR_WRITE                           USART_LINMR_PDCM                /*!< The LIN mode register LINMR(excepting that flag) is writted by the DMA */

#define IS_UART_PDC_MODE_LINMR(LINMR)                                  \
                         (                                             \
                          ((LINMR) == UART_PDC_MODE_LINMR_NOTWRITE) || \
                          ((LINMR) == UART_PDC_MODE_LINMR_WRITE   )    \
                         )
/**
  * @}
  */

/** @defgroup UART_Wkup_Type  UART wakeup signal type in LIN mode
  * @{
  */
#define UART_WKUP_TYPE_LIN_2_0                              ((uint32_t)0x00000000)          /*!< Setting the bit LINWKUP in the control register sends a LIN 2.0 wakeup signal */
#define UART_WKUP_TYPE_LIN_1_3                              USART_LINMR_WKUPTYP             /*!< Setting the bit LINWKUP in the control register sends a LIN 1.3 wakeup signal */
#define IS_UART_WKUP_TYPE(TYPE)                                 \
                         (                                      \
                          ((TYPE) == UART_WKUP_TYPE_LIN_2_0) || \
                          ((TYPE) == UART_WKUP_TYPE_LIN_1_3)    \
                         )
/**
  * @}
  */

/** @defgroup UART_Frame_Slot_Disable  UART frame slot mode disable in LIN mode
  * @{
  */
#define UART_FRAME_SLOT_DISABLE_NONE                        ((uint32_t)0x00000000)          /*!< The frame slot mode is enabled in LIN mode  */
#define UART_FRAME_SLOT_DISABLE_ACTIVE                      USART_LINMR_FSDIS               /*!< The frame slot mode is disabled in LIN mode */
#define IS_UART_FRAME_SLOT_DISABLE(DISABLE)                                \
                         (                                                 \
                          ((DISABLE) == UART_FRAME_SLOT_DISABLE_NONE  ) || \
                          ((DISABLE) == UART_FRAME_SLOT_DISABLE_ACTIVE)    \
                         )
/**
  * @}
  */

/** @defgroup UART_Data_Length_Mode  UART data length mode in LIN mode
  * @{
  */
#define UART_DATA_LENGTH_MODE_DLC                 ((uint32_t)0x00000000)                    /*!< The response data length is defined by the field DLC in LIN mode                                       */
#define UART_DATA_LENGTH_MODE_ID_5_6              USART_LINMR_DLM                           /*!< The response data length is defined by the bits 5 and 6 of the identifier (IDCHR in LINIR) in LIN mode */
#define IS_UART_DATA_LENGTH_MODE(MODE)                                \
                         (                                            \
                          ((MODE) == UART_DATA_LENGTH_MODE_DLC   ) || \
                          ((MODE) == UART_DATA_LENGTH_MODE_ID_5_6)    \
                         )
/**
  * @}
  */

/** @defgroup UART_Checksum_Type  UART checksum type in LIN mode
  * @{
  */
#define UART_CHECKSUM_TYPE_ENHANCED                         ((uint32_t)0x00000000)          /*!< LIN 2.0 "Enhanced" Checksum */
#define UART_CHECKSUM_TYPE_CLASSIC                          USART_LINMR_CHKTYP              /*!< LIN 1.3 "Classic " Checksum */

#define IS_UART_CHECKSUM_TYPE(TYPE)                                  \
                         (                                           \
                          ((TYPE) == UART_CHECKSUM_TYPE_ENHANCED) || \
                          ((TYPE) == UART_CHECKSUM_TYPE_CLASSIC )    \
                         )
/**
  * @}
  */

/** @defgroup UART_Checksum_Disable  UART checksum disable in LIN mode
  * @{
  */
#define UART_CHECKSUM_DISABLE_NONE                         ((uint32_t)0x00000000)          /*!< LIN Checksum not disable */
#define UART_CHECKSUM_DISABLE_ACTIVE                       USART_LINMR_CHKDIS              /*!< LIN Checksum disable     */

#define IS_UART_CHECKSUM_DISABLE(DISABLE)                                \
                         (                                               \
                          ((DISABLE) == UART_CHECKSUM_DISABLE_NONE  ) || \
                          ((DISABLE) == UART_CHECKSUM_DISABLE_ACTIVE)    \
                         )
/**
  * @}
  */

/** @defgroup UART_Parity_Disable  UART parity disable in LIN mode
  * @{
  */
#define UART_PARITY_DISABLE_NONE                           ((uint32_t)0x00000000)          /*!< LIN Parity not disable */
#define UART_PARITY_DISABLE_ACTIVE                         USART_LINMR_PARDIS              /*!< LIN Parity disable     */

#define IS_UART_PARITY_DISABLE(DISABLE)                                \
                         (                                             \
                          ((DISABLE) == UART_PARITY_DISABLE_NONE  ) || \
                          ((DISABLE) == UART_PARITY_DISABLE_ACTIVE)    \
                         )
/**
  * @}
  */

/** @defgroup UART_Node_Active  UART checksum disable in LIN mode
  * @{
  */
#define UART_NODE_ACTIVE_PUBLISH                           ((uint32_t)0x00000000)          /*!< The UART transmits the response                              */
#define UART_NODE_ACTIVE_SUBSCRIBE                         (0x1U << 0U)                    /*!< The UART receives the response                               */
#define UART_NODE_ACTIVE_IGNORE                            (0x2U << 0U)                    /*!< The UART does not transmit and does not receive the response */

#define IS_UART_NODE_ACTIVE(ACTIVE)                                   \
                         (                                            \
                          ((ACTIVE) == UART_NODE_ACTIVE_PUBLISH  ) || \
                          ((ACTIVE) == UART_NODE_ACTIVE_SUBSCRIBE) || \
                          ((ACTIVE) == UART_NODE_ACTIVE_IGNORE   )    \
                         )
/**
  * @}
  */

/** @defgroup UART_DMA_TX  UART DMA enable transmitter
  * @{
  */
#define UART_DMA_TX_DISABLE                                ((uint32_t)0x00000000)          /*!< DMA mode is disable for transmission */
#define UART_DMA_TX_ENABLE                                 USART_CR_DMAT_EN                /*!< DMA mode is enable for transmission  */

#define IS_UART_DMA_TX_ENABLE(ENABLE)                          \
                         (                                     \
                          ((ENABLE) == UART_DMA_TX_DISABLE) || \
                          ((ENABLE) == UART_DMA_TX_ENABLE )    \
                         )
/**
  * @}
  */

/** @defgroup UART_DMA_RX  UART DMA enable receiver
  * @{
  */
#define UART_DMA_RX_DISABLE                                ((uint32_t)0x00000000)          /*!< DMA mode is disable for reception */
#define UART_DMA_RX_ENABLE                                 USART_CR_DMAR_EN                /*!< DMA mode is enable for reception  */

#define IS_UART_DMA_RX_ENABLE(ENABLE)                          \
                         (                                     \
                          ((ENABLE) == UART_DMA_RX_DISABLE) || \
                          ((ENABLE) == UART_DMA_RX_ENABLE )    \
                         )
/**
  * @}
  */

/** @defgroup UART_Flags
  * @brief    Flag mask in the CSR register
  * @{
  */
#define UART_FLAG_TXEMPTY                  USART_CSR_TXEMPTY       /*!< UART transmitter empty                              */
#define UART_FLAG_TIMEOUT                  USART_CSR_TIMEOUT       /*!< UART receiver time-out                              */
#define UART_FLAG_PARE                     USART_CSR_PARE          /*!< UART parity error                                   */
#define UART_FLAG_FRAME                    USART_CSR_FRAME         /*!< UART framing error                                  */
#define UART_FLAG_OVER                     USART_CSR_OVRE          /*!< UART overrun error                                  */
#define UART_FLAG_RXBRK                    USART_CSR_RXBRK         /*!< UART break receive/end of break                     */
#define UART_FLAG_TXRDY                    USART_CSR_TXRDY         /*!< UART transmitter ready                              */
#define UART_FLAG_RXRDY                    USART_CSR_RXRDY         /*!< UART receiver ready                                 */

#define UART_FLAG_LINHTE                   USART_CSR_LINHTE        /*!< UART LIN header timeout error                       */
#define UART_FLAG_LINSTE                   USART_CSR_LINSTE        /*!< UART LIN synch tolerance eror                       */
#define UART_FLAG_LINSNRE                  USART_CSR_LINSNRE       /*!< UART LIN slave not response error                   */
#define UART_FLAG_LINCE                    USART_CSR_LINCE         /*!< UART LIN checksum error                             */
#define UART_FLAG_LINIPE                   USART_CSR_LINIPE        /*!< UART LIN identifier parity error                    */
#define UART_FLAG_LINISFE                  USART_CSR_LINISFE       /*!< UART LIN inconsistent synch field error             */
#define UART_FLAG_LINBE                    USART_CSR_LINBE         /*!< UART LIN bit error                                  */
#define UART_FLAG_LINBLS                   USART_CSR_LINBLS        /*!< UART LIN bus line status                            */
#define UART_FLAG_LINTC                    USART_CSR_LINTC         /*!< UART LIN transfer completed                         */
#define UART_FLAG_LINID                    USART_CSR_LINID         /*!< UART LIN identifier sent or LIN identifier received */
#define UART_FLAG_LINBK                    USART_CSR_LINBK         /*!< UART LIN break sent or LIN break received           */
/**
  * @}
  */

/** @defgroup UART_Clear_Flags
 *  @brief    Flag clear in the CR register
  * @{
  */
#define UART_CLEAR_TXEMPTY                  USART_CR_RSTTX          /*!< UART transmitter empty interrupt clear                              */
#define UART_CLEAR_TIMEOUT                  USART_CR_STTTO          /*!< UART receiver time-out interrupt clear                              */
#define UART_CLEAR_PARE                     USART_CR_RSTSTA         /*!< UART parity error interrupt clear                                   */
#define UART_CLEAR_FRAME                    USART_CR_RSTSTA         /*!< UART framing error interrupt clear                                  */
#define UART_CLEAR_OVER                     USART_CR_RSTSTA         /*!< UART overrun error interrupt clear                                  */
#define UART_CLEAR_RXBRK                    USART_CR_RSTSTA         /*!< UART break receive/end of break interrupt clear                     */
#define UART_CLEAR_TXRDY                    USART_CR_RSTTX          /*!< UART transmitter ready interrupt clear                              */
#define UART_CLEAR_RXRDY                    USART_CR_RSTRX          /*!< UART receiver ready interrupt clear                                 */

#define UART_CLEAR_LINHTE                   USART_CR_RSTSTA         /*!< UART LIN header timeout error interrupt clear                       */
#define UART_CLEAR_LINSTE                   USART_CR_RSTSTA         /*!< UART LIN synch tolerance eror interrupt clear                       */
#define UART_CLEAR_LINSNRE                  USART_CR_RSTSTA         /*!< UART LIN slave not response error interrupt clear                   */
#define UART_CLEAR_LINCE                    USART_CR_RSTSTA         /*!< UART LIN checksum error interrupt clear                             */
#define UART_CLEAR_LINIPE                   USART_CR_RSTSTA         /*!< UART LIN identifier parity error interrupt clear                    */
#define UART_CLEAR_LINISFE                  USART_CR_RSTSTA         /*!< UART LIN inconsistent synch field error interrupt clear             */
#define UART_CLEAR_LINBE                    USART_CR_RSTSTA         /*!< UART LIN bit error interrupt clear                                  */
#define UART_CLEAR_LINTC                    USART_CR_RSTSTA         /*!< UART LIN transfer completed interrupt clear                         */
#define UART_CLEAR_LINID                    USART_CR_RSTSTA         /*!< UART LIN identifier sent or LIN identifier received interrupt clear */
#define UART_CLEAR_LINBK                    USART_CR_RSTSTA         /*!< UART LIN break sent or LIN break received interrupt clear           */
/**
  * @}
  */

/** @defgroup UART_Interrupt_definition
  * @brief Interrupt enable register - IER register
  * @{
  */
#define UART_IT_TXEMPTY                  USART_IER_TXEMPTY       /*!< UART transmitter empty interruption                              */
#define UART_IT_TIMEOUT                  USART_IER_TIMEOUT       /*!< UART receiver time-out interruption                              */
#define UART_IT_PARE                     USART_IER_PARE          /*!< UART parity error interruption                                   */
#define UART_IT_FRAME                    USART_IER_FRAME         /*!< UART framing error interruption                                  */
#define UART_IT_OVER                     USART_IER_OVRE          /*!< UART overrun error interruption                                  */
#define UART_IT_RXBRK                    USART_IER_RXBRK         /*!< UART break receive/end of break interruption                     */
#define UART_IT_TXRDY                    USART_IER_TXRDY         /*!< UART transmitter ready interruption                              */
#define UART_IT_RXRDY                    USART_IER_RXRDY         /*!< UART receiver ready interruption                                 */

#define UART_IT_LINHTE                   USART_IER_LINHTE        /*!< UART LIN header timeout error interruption                       */
#define UART_IT_LINSTE                   USART_IER_LINSTE        /*!< UART LIN synch tolerance eror interruption                       */
#define UART_IT_LINSNRE                  USART_IER_LINSNRE       /*!< UART LIN slave not response error interruption                   */
#define UART_IT_LINCE                    USART_IER_LINCE         /*!< UART LIN checksum error interruption                             */
#define UART_IT_LINIPE                   USART_IER_LINIPE        /*!< UART LIN identifier parity error interruption                    */
#define UART_IT_LINISFE                  USART_IER_LINISFE       /*!< UART LIN inconsistent synch field error interruption             */
#define UART_IT_LINBE                    USART_IER_LINBE         /*!< UART LIN bit error interruption                                  */
#define UART_IT_LINTC                    USART_IER_LINTC         /*!< UART LIN transfer completed interruption                         */
#define UART_IT_LINID                    USART_IER_LINID         /*!< UART LIN identifier sent or LIN identifier received interruption */
#define UART_IT_LINBK                    USART_IER_LINBK         /*!< UART LIN break sent or LIN break received interruption           */

/**
  * @}
  */

/** @defgroup UART_Interrupt_disable
  * @brief Interrupt disable register - IDR register
  * @{
  */
#define UART_DIS_TXEMPTY                  USART_IDR_TXEMPTY       /*!< UART transmitter empty interrupt disable                              */
#define UART_DIS_TIMEOUT                  USART_IDR_TIMEOUT       /*!< UART receiver time-out interrupt disable                              */
#define UART_DIS_PARE                     USART_IDR_PARE          /*!< UART parity error interrupt disable                                   */
#define UART_DIS_FRAME                    USART_IDR_FRAME         /*!< UART framing error interrupt disable                                  */
#define UART_DIS_OVER                     USART_IDR_OVRE          /*!< UART overrun error interrupt disable                                  */
#define UART_DIS_RXBRK                    USART_IDR_RXBRK         /*!< UART break receive/end of break interrupt disable                     */
#define UART_DIS_TXRDY                    USART_IDR_TXRDY         /*!< UART transmitter ready interrupt disable                              */
#define UART_DIS_RXRDY                    USART_IDR_RXRDY         /*!< UART receiver ready interrupt disable                                 */

#define UART_DIS_LINHTE                   USART_IDR_LINHTE        /*!< UART LIN header timeout error interrupt disable                       */
#define UART_DIS_LINSTE                   USART_IDR_LINSTE        /*!< UART LIN synch tolerance eror interrupt disable                       */
#define UART_DIS_LINSNRE                  USART_IDR_LINSNRE       /*!< UART LIN slave not response error interrupt disable                   */
#define UART_DIS_LINCE                    USART_IDR_LINCE         /*!< UART LIN checksum error interrupt disable                             */
#define UART_DIS_LINIPE                   USART_IDR_LINIPE        /*!< UART LIN identifier parity error interrupt disable                    */
#define UART_DIS_LINISFE                  USART_IDR_LINISFE       /*!< UART LIN inconsistent synch field error interrupt disable             */
#define UART_DIS_LINBE                    USART_IDR_LINBE         /*!< UART LIN bit error interrupt disable                                  */
#define UART_DIS_LINTC                    USART_IDR_LINTC         /*!< UART LIN transfer completed interrupt disable                         */
#define UART_DIS_LINID                    USART_IDR_LINID         /*!< UART LIN identifier sent or LIN identifier received interrupt disable */
#define UART_DIS_LINBK                    USART_IDR_LINBK         /*!< UART LIN break sent or LIN break received interrupt disable           */
/**
  * @}
  */

/** @defgroup UART_Interruption_Mask
  * @brief Interrupt mask register - IMR register
  * @{
  */
#define UART_MASK_TXEMPTY                  USART_IMR_TXEMPTY       /*!< UART transmitter empty interrupt mask                              */
#define UART_MASK_TIMEOUT                  USART_IMR_TIMEOUT       /*!< UART receiver time-out interrupt mask                              */
#define UART_MASK_PARE                     USART_IMR_PARE          /*!< UART parity error interrupt mask                                   */
#define UART_MASK_FRAME                    USART_IMR_FRAME         /*!< UART framing error interrupt mask                                  */
#define UART_MASK_OVER                     USART_IMR_OVRE          /*!< UART overrun error interrupt mask                                  */
#define UART_MASK_RXBRK                    USART_IMR_RXBRK         /*!< UART break receive/end of break interrupt mask                     */
#define UART_MASK_TXRDY                    USART_IMR_TXRDY         /*!< UART transmitter ready interrupt mask                              */
#define UART_MASK_RXRDY                    USART_IMR_RXRDY         /*!< UART receiver ready interrupt mask                                 */

#define UART_MASK_LINHTE                   USART_IMR_LINHTE        /*!< UART LIN header timeout error interrupt mask                       */
#define UART_MASK_LINSTE                   USART_IMR_LINSTE        /*!< UART LIN synch tolerance eror interrupt mask                       */
#define UART_MASK_LINSNRE                  USART_IMR_LINSNRE       /*!< UART LIN slave not response error interrupt mask                   */
#define UART_MASK_LINCE                    USART_IMR_LINCE         /*!< UART LIN checksum error interrupt mask                             */
#define UART_MASK_LINIPE                   USART_IMR_LINIPE        /*!< UART LIN identifier parity error interrupt mask                    */
#define UART_MASK_LINISFE                  USART_IMR_LINISFE       /*!< UART LIN inconsistent synch field error interrupt mask             */
#define UART_MASK_LINBE                    USART_IMR_LINBE         /*!< UART LIN bit error interrupt mask                                  */
#define UART_MASK_LINTC                    USART_IMR_LINTC         /*!< UART LIN transfer completed interrupt mask                         */
#define UART_MASK_LINID                    USART_IMR_LINID         /*!< UART LIN identifier sent or LIN identifier received interrupt mask */
#define UART_MASK_LINBK                    USART_IMR_LINBK         /*!< UART LIN break sent or LIN break received interrupt mask           */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup UART_Exported_Macros UART Exported Macros
  * @{
  */

/** @brief  Check whether the specified UART flag is set or not.
  * @param  None
  * @retval None
  */
#define IS_UART_GET_FLAG(FLAG)                                   \
                             (                                   \
                                ((FLAG) == UART_FLAG_TXEMPTY) || \
                                ((FLAG) == UART_FLAG_TIMEOUT) || \
                                ((FLAG) == UART_FLAG_PARE   ) || \
                                ((FLAG) == UART_FLAG_FRAME  ) || \
                                ((FLAG) == UART_FLAG_OVER   ) || \
                                ((FLAG) == UART_FLAG_RXBRK  ) || \
                                ((FLAG) == UART_FLAG_TXRDY  ) || \
                                ((FLAG) == UART_FLAG_RXRDY  ) || \
                                ((FLAG) == UART_FLAG_LINHTE ) || \
                                ((FLAG) == UART_FLAG_LINSTE ) || \
                                ((FLAG) == UART_FLAG_LINSNRE) || \
                                ((FLAG) == UART_FLAG_LINCE  ) || \
                                ((FLAG) == UART_FLAG_LINIPE ) || \
                                ((FLAG) == UART_FLAG_LINISFE) || \
                                ((FLAG) == UART_FLAG_LINBE  ) || \
                                ((FLAG) == UART_FLAG_LINBLS ) || \
                                ((FLAG) == UART_FLAG_LINTC  ) || \
                                ((FLAG) == UART_FLAG_LINID  ) || \
                                ((FLAG) == UART_FLAG_LINBK  )    \
                             )

/** @brief  Clear the specified UART pending flag enable.
  * @param  None
  * @retval None
  */
#define IS_UART_CLEAR_FLAG(FLAG)                                  \
                             (                                    \
                                ((FLAG) == UART_CLEAR_TXEMPTY) || \
                                ((FLAG) == UART_CLEAR_TIMEOUT) || \
                                ((FLAG) == UART_CLEAR_PARE   ) || \
                                ((FLAG) == UART_CLEAR_FRAME  ) || \
                                ((FLAG) == UART_CLEAR_OVER   ) || \
                                ((FLAG) == UART_CLEAR_RXBRK  ) || \
                                ((FLAG) == UART_CLEAR_TXRDY  ) || \
                                ((FLAG) == UART_CLEAR_RXRDY  ) || \
                                ((FLAG) == UART_CLEAR_LINHTE ) || \
                                ((FLAG) == UART_CLEAR_LINSTE ) || \
                                ((FLAG) == UART_CLEAR_LINSNRE) || \
                                ((FLAG) == UART_CLEAR_LINCE  ) || \
                                ((FLAG) == UART_CLEAR_LINIPE ) || \
                                ((FLAG) == UART_CLEAR_LINISFE) || \
                                ((FLAG) == UART_CLEAR_LINBE  ) || \
                                ((FLAG) == UART_CLEAR_LINTC  ) || \
                                ((FLAG) == UART_CLEAR_LINID  ) || \
                                ((FLAG) == UART_CLEAR_LINBK  )    \
                             )

/** @brief  Enable the specified UART interrupt.
  * @param  None
  * @retval None
  */
#define IS_UART_ENABLE_IT(IT)                                \
                             (                               \
                                ((IT) == UART_IT_TXEMPTY) || \
                                ((IT) == UART_IT_TIMEOUT) || \
                                ((IT) == UART_IT_PARE   ) || \
                                ((IT) == UART_IT_FRAME  ) || \
                                ((IT) == UART_IT_OVER   ) || \
                                ((IT) == UART_IT_RXBRK  ) || \
                                ((IT) == UART_IT_TXRDY  ) || \
                                ((IT) == UART_IT_RXRDY  ) || \
                                ((IT) == UART_IT_LINHTE ) || \
                                ((IT) == UART_IT_LINSTE ) || \
                                ((IT) == UART_IT_LINSNRE) || \
                                ((IT) == UART_IT_LINCE  ) || \
                                ((IT) == UART_IT_LINIPE ) || \
                                ((IT) == UART_IT_LINISFE) || \
                                ((IT) == UART_IT_LINBE  ) || \
                                ((IT) == UART_IT_LINTC  ) || \
                                ((IT) == UART_IT_LINID  ) || \
                                ((IT) == UART_IT_LINBK  )    \
                             )

/** @brief  Disable the specified UART interrupt.
  * @param  None
  * @retval None
  */
#define IS_UART_CLEAR_IT(IT)                                  \
                             (                                \
                                ((IT) == UART_DIS_TXEMPTY) || \
                                ((IT) == UART_DIS_TIMEOUT) || \
                                ((IT) == UART_DIS_PARE   ) || \
                                ((IT) == UART_DIS_FRAME  ) || \
                                ((IT) == UART_DIS_OVER   ) || \
                                ((IT) == UART_DIS_RXBRK  ) || \
                                ((IT) == UART_DIS_TXRDY  ) || \
                                ((IT) == UART_DIS_RXRDY  ) || \
                                ((IT) == UART_DIS_LINHTE ) || \
                                ((IT) == UART_DIS_LINSTE ) || \
                                ((IT) == UART_DIS_LINSNRE) || \
                                ((IT) == UART_DIS_LINCE  ) || \
                                ((IT) == UART_DIS_LINIPE ) || \
                                ((IT) == UART_DIS_LINISFE) || \
                                ((IT) == UART_DIS_LINBE  ) || \
                                ((IT) == UART_DIS_LINTC  ) || \
                                ((IT) == UART_DIS_LINID  ) || \
                                ((IT) == UART_DIS_LINBK  )    \
                             )


/** @brief  Check whether the specified UART interrupt has occurred or not.
  * @param  None
  * @retval None
  */
#define IS_UART_GET_IT(IT)                                     \
                             (                                 \
                                ((IT) == UART_MASK_TXEMPTY) || \
                                ((IT) == UART_MASK_TIMEOUT) || \
                                ((IT) == UART_MASK_PARE   ) || \
                                ((IT) == UART_MASK_FRAME  ) || \
                                ((IT) == UART_MASK_OVER   ) || \
                                ((IT) == UART_MASK_RXBRK  ) || \
                                ((IT) == UART_MASK_TXRDY  ) || \
                                ((IT) == UART_MASK_RXRDY  ) || \
                                ((IT) == UART_MASK_LINHTE ) || \
                                ((IT) == UART_MASK_LINSTE ) || \
                                ((IT) == UART_MASK_LINSNRE) || \
                                ((IT) == UART_MASK_LINCE  ) || \
                                ((IT) == UART_MASK_LINIPE ) || \
                                ((IT) == UART_MASK_LINISFE) || \
                                ((IT) == UART_MASK_LINBE  ) || \
                                ((IT) == UART_MASK_LINTC  ) || \
                                ((IT) == UART_MASK_LINID  ) || \
                                ((IT) == UART_MASK_LINBK  )    \
                             )

/**
  * @}
  */

/** @defgroup UART_Global_definition
  * @{
  */
#define IS_UART_BAUDRATE(BAUDRATE)  ((BAUDRATE ) <= 6562500U)
#define IS_UART_FIDIRATIO(FIDIRATE) ((FIDIRATE ) <= 2047U   )
#define IS_UART_IF(IF)              ((IF       ) <= 0xFFU   )
#define IS_UART_TIMEOUT(TIMEOUT)    ((TIMEOUT  ) <= 0x1FFFF )
#define IS_UART_TIMGUARD(TIMEGUARD) ((TIMEGUARD) <= 0xFF    )
#define IS_UART_LINIR_WR(LINIR_WR)  ((LINIR_WR ) <= 0xFF    )
#define IS_UART_DATA(DATA)          ((DATA     ) <= 0x1FF   )
#define IS_UART_DLC(DATA)           ((DATA     ) <= 0xFF    )

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup UART_Exported_Functions UART Exported Functions
  * @{
  */
/* Initialization and de-initialization functions *****************************/
void UART_Init(USART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct);
void UART_StructInit(UART_InitTypeDef* UART_InitStruct);
void UART_DeInit(USART_TypeDef* UARTx);

/* Normal command and configuration functions *********************************/
/* Normal     Cmd */ void UART_Cmd(USART_TypeDef* UARTx, FunctionalState NewState);
/* Normal     Cmd */ void UART_RSTSTA_Cmd(USART_TypeDef* UARTx, FunctionalState NewState);
/* Normal     Cmd */ void UART_TXDIS_Cmd(USART_TypeDef* UARTx, FunctionalState NewState);
/* Normal     Cmd */ void UART_TXEN_Cmd(USART_TypeDef* UARTx, FunctionalState NewState);
/* Normal     Cmd */ void UART_RXDIS_Cmd(USART_TypeDef* UARTx, FunctionalState NewState);
/* Normal     Cmd */ void UART_RXEN_Cmd(USART_TypeDef* UARTx, FunctionalState NewState);
/* Normal     Cmd */ void UART_RSTTX_Cmd(USART_TypeDef* UARTx, FunctionalState NewState);
/* Normal     Cmd */ void UART_RSTRX_Cmd(USART_TypeDef* UARTx, FunctionalState NewState);
/* Normal     Cfg */ void UART_InvData_Cfg(USART_TypeDef* UARTx, FunctionalState NewState);
/* Normal     Cfg */ void UART_OverSampling8_Cfg(USART_TypeDef* UARTx, FunctionalState NewState);
/* Normal     Cfg */ void UART_DataLength9_Cfg(USART_TypeDef* UARTx, FunctionalState NewState);
/* Normal     Cfg */ void UART_MSBFirst_Cfg(USART_TypeDef* UARTx, FunctionalState NewState);
/* Normal     Cfg */ void UART_ChannelMode_Cfg(USART_TypeDef* UARTx, uint32_t UART_ChannelMode);
/* Normal     Cfg */ void UART_StopBit_Cfg(USART_TypeDef* UARTx, uint32_t UART_StopBits);
/* Normal     Cfg */ void UART_Parity_Cfg(USART_TypeDef* UARTx, uint32_t UART_Parity);
/* Normal     Cfg */ void UART_DataLength_Cfg(USART_TypeDef* UARTx, uint32_t UART_WordLength);
/* Normal     Cfg */ void UART_CLKSelect_Cfg(USART_TypeDef* UARTx, uint32_t UART_CLKSelect);
/* Normal     Cfg */ void UART_OperationMode_Cfg(USART_TypeDef* UARTx, uint32_t UART_OperationMode);

/* Fractional baudrate function ***********************************************/
/* Normal     Cfg */ void UART_FracDivider_Cfg(USART_TypeDef* UARTx, uint32_t UART_BaudRate);

/* Break command functions ****************************************************/
/* Normal     Cmd */ void UART_STPBRK_Cmd(USART_TypeDef* UARTx, FunctionalState NewState);
/* Normal     Cmd */ void UART_STTBRK_Cmd(USART_TypeDef* UARTx, FunctionalState NewState);

/* Receiver time-out and transmitter timeguard functions **********************/
/* Normal     Cfg */ void UART_Receiver_TimeOut_Cfg(USART_TypeDef* UARTx, uint32_t UART_ReceiverTimeOut);
/* Normal     Cmd */ void UART_RETTO_After_Timeout_Cmd(USART_TypeDef* UARTx, FunctionalState NewState);
/* Normal     Cmd */ void UART_STTTO_After_Timeout_Cmd(USART_TypeDef* UARTx, FunctionalState NewState);
/* Normal     Cfg */ void UART_Transmitter_TimeGuard_Cfg(USART_TypeDef* UARTx, uint32_t UART_TransmitterTimeGuard);

/* Multidrop mode command function ********************************************/
/* Normal     Cmd */ void UART_SENDAInMultidropMode_Cmd(USART_TypeDef* UARTx, FunctionalState NewState);

/* IrDA mode function *********************************************************/
/* IrDA       Cfg  */ void UART_IrDAFilter_Cfg(USART_TypeDef* UARTx, uint32_t UART_IrDAFilter);

/* LIN mode functions *********************************************************/
/* LIN        Cmd  */ void UART_LINWKUP_Cmd(USART_TypeDef* UARTx, FunctionalState NewState);
/* LIN        Cmd  */ void UART_LINABT_Cmd(USART_TypeDef* UARTx, FunctionalState NewState);
/* LIN        Cfg  */ void UART_Write_LINIR_In_LIN_Master(USART_TypeDef* UARTx, uint32_t UART_LINIR_Data);
/* LIN        Read */ uint32_t UART_Read_LINIR_In_LIN_Slave(USART_TypeDef* UARTx);
/* LIN        Cfg  */ void UART_SYNCDisable_Cfg(USART_TypeDef* UARTx, FunctionalState NewState);
/* LIN        Cfg  */ void UART_PDCMode_Cfg(USART_TypeDef* UARTx, FunctionalState NewState);
/* LIN        Cfg  */ void UART_DataLengthControl_Cfg(USART_TypeDef* UARTx, uint32_t UART_DataLengthControl);
/* LIN        Cfg  */ void UART_WkupType_Cfg(USART_TypeDef* UARTx, FunctionalState NewState);
/* LIN        Cfg  */ void UART_FrameSlotDisable_Cfg(USART_TypeDef* UARTx, FunctionalState NewState);
/* LIN        Cfg  */ void UART_DataLengthMode_Cfg(USART_TypeDef* UARTx, FunctionalState NewState);
/* LIN        Cfg  */ void UART_CheckSumType_Cfg(USART_TypeDef* UARTx, FunctionalState NewState);
/* LIN        Cfg  */ void UART_CheckSumDisable_Cfg(USART_TypeDef* UARTx, FunctionalState NewState);
/* LIN        Cfg  */ void UART_ParityDisable_Cfg(USART_TypeDef* UARTx, FunctionalState NewState);
/* LIN        Cfg  */ void UART_NodeAction_Cfg(USART_TypeDef* UARTx, uint32_t UART_NodeAction);
/* LIN        Read */ uint32_t UART_LINBaudRate(USART_TypeDef* UARTx);

/* Data transfers functions ***************************************************/
void UART_Transmit(USART_TypeDef* UARTx, uint16_t Data);
uint16_t UART_Receive(USART_TypeDef* UARTx);

/* DMA transfers management functions *****************************************/
void UART_DMATxEnable_Cmd(USART_TypeDef* UARTx, FunctionalState NewState);
void UART_DMARxEnable_Cmd(USART_TypeDef* UARTx, FunctionalState NewState);

/* Low-Power SLEEP and STOP wakeup management functions ***********************/
void UART_LowPowerSleepWkupConfig(USART_TypeDef* UARTx, FunctionalState NewState);
void LPUART_LowPowerStopWkupConfig(USART_TypeDef* UARTx, FunctionalState NewState);

/* Interrupts and flags management functions **********************************/
void UART_ITConfig(USART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState);
FlagStatus UART_GetFlagStatus(USART_TypeDef* UARTx, uint32_t UART_FLAG);
void UART_ClearFlag(USART_TypeDef* UARTx, uint32_t UART_FLAG);
ITStatus UART_GetITStatus(USART_TypeDef* UARTx, uint32_t UART_IT);
void UART_ITDisableConfig(USART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState);

/**
  * @}
  */

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

#endif /* __FT32F4XX_UART_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
