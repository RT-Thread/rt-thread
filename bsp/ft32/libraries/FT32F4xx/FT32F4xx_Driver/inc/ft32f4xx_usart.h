/**
  * @file                ft32f4xx_usart.h
  * @author              FMD AE
  * @brief               This file contains all the functions prototypes for the USART
  *                      fireware library.
  * @version             V1.0.0
  * @date                2025-03-19
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_USART_H
#define __FT32F4XX_USART_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"

/** @addtogroup ft32f4xx_Driver
  * @{
  */

/** @addtogroup USART
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup USART_Exported_Types USART Exported Types
  * @{
  */

/**
  * @brief USART Init Structure definition
  */
typedef struct
{
    uint32_t USART_BaudRate;                  /*!< This member configures the USART communication baud rate.
                                                 The baud rate is computed using the following formula:
                                                 - CD = 0: Disable baud rate clock

                                                 - Non ISO7816 mode
                                                    - ASYNC X16  : IntegerDivider  = ((PCLKx) / (16 * (USRAT_InitStruct->USART_BaudRate)))
                                                    - ASYNC X8   : IntegerDivider  = ((PCLKx) / (8  * (USRAT_InitStruct->USART_BaudRate)))
                                                    - SYNC or SPI: IntegerDivider  = ((PCLKx) / (     (USRAT_InitStruct->USART_BaudRate)))
                                                 - ISO7816 mode
                                                    - ISO7816    : IntegerDivider  = ((PCLKx) / (USRAT_InitStruct->USART_FiDiRatio *
                                                                                                (USRAT_InitStruct->USART_BaudRate)))

                                                 - Fractional baud rate in asynchronous mode
                                                    - X16        : FractionDivider = (((PCLKx) / (16 * (USRAT_InitStruct->USART_BaudRate))) - IntegerDivider) * 8
                                                    - X8         : FractionDivider = (((PCLKx) / (8  * (USRAT_InitStruct->USART_BaudRate))) - IntegerDivider) * 8
                                                 */

    uint32_t USART_FiDiRatio;                 /*!< Specifies the value of FI over DI ratio value in ISO7816 mode and IrDA mode.*/

    uint32_t USART_IrDAFilter;                /*!< Specifies the value of IrDA filter in IrDA mode.*/

    uint32_t USART_WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
                                                 This parameter can be a value of @ref USART_Char_Length & USART_Char_Length9*/

    uint32_t USART_ClockOutput;               /*!< Specifies whether the USART clock SCK is output or not.
                                                 This parameter can be a value of @ref USART_Clock_Output*/

    uint32_t USART_StopBits;                  /*!< Specifies the number of stop bits transmitted.
                                                 This parameter can be a value of @ref USART_Stop_Bits*/

    uint32_t USART_Parity;                    /*!< Specifies the parity mode.
                                                 This parameter can be a value of @ref USART_Parity
                                                 @note When parity is enabled, the computed parity is inserted
                                                       at the MSB position of the transmitted data (9th bit when
                                                       the word length is set to 9 data bits; 8th bit when the
                                                       word length is set to 8 data bits). */

    uint32_t USART_Mode;                      /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
                                                 This parameter can be a value of @ref USART_Mode*/

    uint32_t USART_CLKSelect;                 /*!< Specifies the selection of clock.
                                                 This parameter can be a value of @ref USART_Clock_Select*/

    uint32_t USART_OperationMode;             /*!< Specifies the mode of operation.
                                                 This parameter can be a value of @ref USART_Mode_Operation*/

    uint32_t USART_HardwareFlowControl;       /*!< Specifies whether the hardware flow control mode is enabled
                                                 or disabled.
                                                 This parameter can be a value of @ref USART_Hardware_Flow_Control*/

    uint32_t USART_Sync;                      /*!< Specifies the synchronous mode select.
                                                 This parameter can be a value of @ref USART_Sync_Mode*/

    uint32_t USART_BitOrder;                  /*!< Specifies whether the Least or Most Significant Bit is sent/received first.
                                                 This parameter can be a value of @ref USART_BIT_ORDER*/

    uint32_t USART_ChannelMode;               /*!< Specifies the channel mode select.
                                                 this parameter can be a value of @ref USART_Channel_Mode*/

    uint32_t USART_WRDBT;                     /*!< Specifies whether wait read data before transfer is enabled or disabled.
                                                 This parameter can be a value of @ref USART_WRDBT*/

    uint32_t USART_OverSampling;              /*!< Specifies whether 16x oversampling or 8x oversampling.
                                                 This parameter can be a value of @ref USART_OverSampling*/

    uint32_t USART_CLKPolarity;               /*!< Specifies the inactive state value of the serial clock in SPI mode.
                                                 This parameter can be a value of @ref USART_Clock_Polarity*/

    uint32_t USART_CLKPhase;                  /*!< Specifies the clock transition on which the bit capture and which bit change
                                                 is made in SPI mode.
                                                 This parameter can be a value of @ref USART_Clock_Phase*/

    uint32_t USART_INVData;                   /*!< Specifies whether the data is inverted.
                                                 This parameter can be a value of @ref USART_InvertData*/

    uint32_t USART_InhibitNACK;               /*!< Specifies whether the NACK is generated in ISO7816 protocol T = 0.
                                                 This parameter can be a value of @ref USART_INACK*/

    uint32_t USART_DisSuccessiveNACK;         /*!< Specifies whether disable the successive NACK in ISO7816 protocol T = 0.
                                                 This parameter can be a value of @ref USART_DSNACK*/

    uint32_t USART_MAXIteration;              /*!< Specifies the maximum number of automatic iteration in ISO7816 protocol T = 0.
                                                 This parameter can be a value of @ref USART_Max_Iteration*/

    uint32_t USART_SYNCDisable;               /*!< Specifies whether disable the synchronization in LIN mode.
                                                 This parameter can be a value of @ref USART_Sync_Disable*/

    uint32_t USART_PDCMode;                   /*!< Specifies the DMA mode selection in LIN mode.
                                                 This parameter can be a value of @ref USART_PDC_Mode*/

    uint32_t USART_DataLengthControl;         /*!< Specifies define the response data length when DataLengthMode = 0 in LIN mode.
                                                 0-255: the response data length is equal to DLC+1 bytes.*/

    uint32_t USART_WkupType;                  /*!< Specifies whether the wakeup signal type is LIN2.0 wakup signal or LIN1.3 wakup signal.
                                                 This parameter can be a value of @ref USART_Wkup_Type*/

    uint32_t USART_FrameSlotDisable;          /*!< Specifies whether disable the frame slot mode in LIN mode.
                                                 This parameter can be a value of @ref USART_Frame_Slot_Disable*/

    uint32_t USART_DataLengthMode;            /*!< Specifies the data length mode in LIN mode.
                                                 This parameter can be a value of @ref USART_Data_Length_Mode*/

    uint32_t USART_CheckSumType;              /*!< Specifies the checksum type in LIN mode.
                                                 This parameter can be a value of @ref USART_Checksum_Type*/

    uint32_t USART_CheckSumDisable;           /*!< Specifies whether disable the checksum in LIN mode.
                                                 This parameter can be a value of @ref USART_Checksum_Disable*/

    uint32_t USART_ParityDisable;             /*!< Specifies whether disable the parity in LIN mode.
                                                 This parameter can be a value of @ref USART_Parity_Disable*/

    uint32_t USART_NodeAction;                /*!< Specifies the LIN Node Active.
                                                 This parameter can be a value of @ref USART_Node_Active*/

} USART_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup USART_Exported_Constants USART Exported Constants
  * @{
  */

#define IS_USART_ALL_PERIPH(PERIPH) (                        \
                                     ((PERIPH) == USART1) || \
                                     ((PERIPH) == USART2) || \
                                     ((PERIPH) == USART3) || \
                                     ((PERIPH) == USART6)    \
                                    )

#define IS_USART_ALL_PERIPH_WP(PERIPH_WP) (                        \
                                     ((PERIPH_WP) == USART1_WP) || \
                                     ((PERIPH_WP) == USART2_WP) || \
                                     ((PERIPH_WP) == USART3_WP) || \
                                     ((PERIPH_WP) == USART6_WP)    \
                                     )

#define IS_USART_12_PERIPH(PERIPH)  (                        \
                                     ((PERIPH) == USART1) || \
                                     ((PERIPH) == USART2)    \
                                    )

#define IS_USART_36_PERIPH(PERIPH)  (                        \
                                     ((PERIPH) == USART3) || \
                                     ((PERIPH) == USART6)    \
                                    )


/** @defgroup USART_Max_Iteration  USART Number of MAX_ITERATION for ISO7816 T = 0
  * @{
  */
#define USART_ISO7816_T0_MAX_ITERATION_0     ((uint32_t)0x00000000U << (uint32_t)24U)        /*!< USART max_iteration with 0 times */
#define USART_ISO7816_T0_MAX_ITERATION_1     ((uint32_t)0x00000001U << (uint32_t)24U)        /*!< USART max_iteration with 1 times */
#define USART_ISO7816_T0_MAX_ITERATION_2     ((uint32_t)0x00000002U << (uint32_t)24U)        /*!< USART max_iteration with 2 times */
#define USART_ISO7816_T0_MAX_ITERATION_3     ((uint32_t)0x00000003U << (uint32_t)24U)        /*!< USART max_iteration with 3 times */
#define USART_ISO7816_T0_MAX_ITERATION_4     ((uint32_t)0x00000004U << (uint32_t)24U)        /*!< USART max_iteration with 4 times */
#define USART_ISO7816_T0_MAX_ITERATION_5     ((uint32_t)0x00000005U << (uint32_t)24U)        /*!< USART max_iteration with 5 times */
#define USART_ISO7816_T0_MAX_ITERATION_6     ((uint32_t)0x00000006U << (uint32_t)24U)        /*!< USART max_iteration with 6 times */
#define USART_ISO7816_T0_MAX_ITERATION_7     ((uint32_t)0x00000007U << (uint32_t)24U)        /*!< USART max_iteration with 7 times */

#define IS_USART_ISO7816_T0_MAX_ITERATION(ITERATION)                                \
                              (                                                     \
                               ((ITERATION) == USART_ISO7816_T0_MAX_ITERATION_0) || \
                               ((ITERATION) == USART_ISO7816_T0_MAX_ITERATION_1) || \
                               ((ITERATION) == USART_ISO7816_T0_MAX_ITERATION_2) || \
                               ((ITERATION) == USART_ISO7816_T0_MAX_ITERATION_3) || \
                               ((ITERATION) == USART_ISO7816_T0_MAX_ITERATION_4) || \
                               ((ITERATION) == USART_ISO7816_T0_MAX_ITERATION_5) || \
                               ((ITERATION) == USART_ISO7816_T0_MAX_ITERATION_6) || \
                               ((ITERATION) == USART_ISO7816_T0_MAX_ITERATION_7)    \
                              )
/**
  * @}
  */

/** @defgroup USART_InvertData  USART Invert Data
  * @{
  */
#define USART_INVDATA_DISABLE                                 ((uint32_t)0x00000000U)        /*!< USART invert data disbale */
#define USART_INVDATA_ENABLE                                  USART_MR_INVDATA               /*!< USART invert data enable  */

#define IS_USART_INVDATA(INVDATA)                                 \
                         (                                        \
                          ((INVDATA) == USART_INVDATA_DISABLE) || \
                          ((INVDATA) == USART_INVDATA_ENABLE )    \
                         )
/**
  * @}
  */

/** @defgroup USART_DSNACK  USART disable successive NACK for ISO7816 T = 0
  * @{
  */
#define USART_ISO7816_T0_DSNACK_DISABLE                       ((uint32_t)0x00000000U)        /*!< USART successive NACK disable*/
#define USART_ISO7816_T0_DSNACK_ENABLE                        USART_MR_DSNACK                /*!< USART successive NACK enable */

#define IS_USART_ISO7816_T0_DSNACK(DSNACK)                                 \
                         (                                                 \
                          ((DSNACK) == USART_ISO7816_T0_DSNACK_DISABLE) || \
                          ((DSNACK) == USART_ISO7816_T0_DSNACK_ENABLE )    \
                         )
/**
  * @}
  */

/** @defgroup USART_INACK  USART inhibit Non Acknowledge for ISO7816 T = 0
  * @{
  */
#define USART_ISO7816_T0_INACK_DISABLE                       ((uint32_t)0x00000000U)         /*!< USART inhibit Non Acknowledge */
#define USART_ISO7816_T0_INACK_ENABLE                        USART_MR_INACK                  /*!< USART         Non Acknowledge */

#define IS_USART_ISO7816_T0_INACK(INACK)                                  \
                         (                                                \
                          ((INACK) == USART_ISO7816_T0_DSNACK_DISABLE) || \
                          ((INACK) == USART_ISO7816_T0_DSNACK_ENABLE )    \
                         )
/**
  * @}
  */

/** @defgroup USART_OverSampling  USART Oversampling mode
  * @{
  */
#define USART_OVERSAMPLING_16                                ((uint32_t)0x00000000U)         /*!< USART 16x sampling */
#define USART_OVERSAMPLING_8                                 USART_MR_OVER                   /*!< USART 8x  sampling */

#define IS_USART_OVERSAMPLING(OVERSAMPLING)                            \
                         (                                             \
                          ((OVERSAMPLING) == USART_OVERSAMPLING_16) || \
                          ((OVERSAMPLING) == USART_OVERSAMPLING_8 )    \
                         )
/**
  * @}
  */

/** @defgroup USART_Clock_Output  USART clock output select
  * @{
  */
#define USART_CLOCK_OUTPUT_DISABLE                           ((uint32_t)0x00000000U)         /*!< USART don't drive the SCK pin                                  */
#define USART_CLOCK_OUTPUT_ENABLE                            USART_MR_CLKO                   /*!< USART drive the SCK pin if don't select the external clock SCK */

#define IS_USART_CLOCK_OUTPUT(OUTPUT)                                 \
                         (                                            \
                          ((OUTPUT) == USART_CLOCK_OUTPUT_DISABLE) || \
                          ((OUTPUT) == USART_CLOCK_OUTPUT_ENABLE )    \
                         )
/**
  * @}
  */

/** @defgroup USART_Char_Length9  USART 9-bit character length
  * @{
  */
#define USART_CHAR_LENGTH9_DISABLE                            ((uint32_t)0x00000000U)         /*!< USART CHRL defined character length */
#define USART_CHAR_LENGTH9_ENABLE                             USART_MR_MODE9                  /*!< USART 9-bit character length        */

/**
  * @}
  */

/** @defgroup USART_BIT_ORDER  USART bit order
  * @{
  */
#define USART_BIT_ORDER_LSBF                                 ((uint32_t)0x00000000U)         /*!< USART Least Significant Bit is sent/received first */
#define USART_BIT_ORDER_MSBF                                 USART_MR_MSBF                   /*!< USART Most  Significant Bit is sent/received first */

#define IS_USART_BIT_ORDER(ORDER)                              \
                         (                                     \
                          ((ORDER) == USART_BIT_ORDER_LSBF) || \
                          ((ORDER) == USART_BIT_ORDER_MSBF)    \
                         )
/**
  * @}
  */

/** @defgroup USART_Channel_Mode  USART channel mode
  * @{
  */
#define USART_CHANNEL_MODE_NORMAL                            (0x0UL << 14U         )         /*!< USART operates in normal mode          */
#define USART_CHANNEL_MODE_AUTOMATIC                         (0x1UL << 14U         )         /*!< USART operates in automatic echo mode  */
#define USART_CHANNEL_MODE_LOCAL_LOOPBACK                    (0x2UL << 14U         )         /*!< USART operates in local loopback mode  */
#define USART_CHANNEL_MODE_REMOTE_LOOPBACK                   (0x3UL << 14U         )         /*!< USART operates in remote loopback mode */

#define IS_USART_CHANNEL_MODE(MODE)                                         \
                         (                                                  \
                          ((MODE) == USART_CHANNEL_MODE_NORMAL         ) || \
                          ((MODE) == USART_CHANNEL_MODE_AUTOMATIC      ) || \
                          ((MODE) == USART_CHANNEL_MODE_LOCAL_LOOPBACK ) || \
                          ((MODE) == USART_CHANNEL_MODE_REMOTE_LOOPBACK)    \
                         )
/**
  * @}
  */

/** @defgroup USART_Stop_Bits  USART Number of Stop Bits
  * @{
  */
#define USART_STOPBITS_1                                     ((uint32_t)0x00000000U)         /*!< USART frame with 1 stop bit    */
#define USART_STOPBITS_1_5                                   (0x1UL << 12U)                  /*!< USART frame with 1.5 stop bits */
#define USART_STOPBITS_2                                     (0x2UL << 12U)                  /*!< USART frame with 2 stop bits   */

#define IS_USART_STOPBITS(STOPBITS)                              \
                         (                                       \
                          ((STOPBITS) ==  USART_STOPBITS_1  ) || \
                          ((STOPBITS) ==  USART_STOPBITS_1_5) || \
                          ((STOPBITS) ==  USART_STOPBITS_2  )    \
                         )
/**
  * @}
  */

/** @defgroup USART_Parity    USART Parity
  * @{
  */
#define USART_PARITY_EVEN                                    (0x0 << 9U)                     /*!< Even  parity   */
#define USART_PARITY_ODD                                     (0x1 << 9U)                     /*!< Odd   parity   */
#define USART_PARITY_SPACE                                   (0x2 << 9U)                     /*!< Space parity   */
#define USART_PARITY_MARK                                    (0x3 << 9U)                     /*!< Mark  parity   */
#define USART_PARITY_NONE                                    (0x4 << 9U)                     /*!< No    parity   */
#define USART_PARITY_MULTIDROP                               (0x6 << 9U)                     /*!< Multidrop Mode */

#define IS_USART_PARITY(PARITY)                                    \
                         (                                         \
                          ((PARITY) ==  USART_PARITY_EVEN     ) || \
                          ((PARITY) ==  USART_PARITY_ODD      ) || \
                          ((PARITY) ==  USART_PARITY_SPACE    ) || \
                          ((PARITY) ==  USART_PARITY_MARK     ) || \
                          ((PARITY) ==  USART_PARITY_NONE     ) || \
                          ((PARITY) ==  USART_PARITY_MULTIDROP)    \
                         )
/**
  * @}
  */

/** @defgroup USART_Sync_Mode    USART synchronous mode select
  * @{
  */
#define USART_SYNC_MODE_ASYNC                                ((uint32_t)0x00000000U)         /*!< USART operates in asynchronous mode */
#define USART_SYNC_MODE_SYNC                                 USART_MR_SYNC                   /*!< USART operates in synchronous  mode */

#define IS_USART_SYNC_MODE(MODE)                               \
                         (                                     \
                          ((MODE) == USART_SYNC_MODE_ASYNC) || \
                          ((MODE) == USART_SYNC_MODE_SYNC )    \
                         )
/**
  * @}
  */

/** @defgroup USART_Char_Length  USART character length
  * @{
  */
#define USART_CHAR_LENGTH_5BIT                               ((uint32_t)0x00000000U)         /*!< USART charcter length is 5bits */
#define USART_CHAR_LENGTH_6BIT                               (0x1U << 6U)                    /*!< USART charcter length is 6bits */
#define USART_CHAR_LENGTH_7BIT                               (0x2U << 6U)                    /*!< USART charcter length is 7bits */
#define USART_CHAR_LENGTH_8BIT                               (0x3U << 6U)                    /*!< USART charcter length is 8bits */

#define IS_USART_CHAR_LENGTH(LENGTH)                                  \
                         (                                            \
                          ((LENGTH) == USART_CHAR_LENGTH_5BIT)     || \
                          ((LENGTH) == USART_CHAR_LENGTH_6BIT)     || \
                          ((LENGTH) == USART_CHAR_LENGTH_7BIT)     || \
                          ((LENGTH) == USART_CHAR_LENGTH_8BIT)     || \
                          ((LENGTH) == USART_CHAR_LENGTH9_DISABLE) || \
                          ((LENGTH) == USART_CHAR_LENGTH9_ENABLE )    \
                         )
/**
  * @}
  */

/** @defgroup USART_Clock_Select  USART clock select
  * @{
  */
#define USART_CLOCK_SELECT_MCK                               ((uint32_t)0x00000000U)         /*!< USART clock source MCK     */
#define USART_CLOCK_SELECT_MCKDIV8                           (0x1U << 4U)                    /*!< USART clock source MCK / 8 */
#define USART_CLOCK_SELECT_SCK                               (0x3U << 4U)                    /*!< USART clock source SCK     */

#define IS_USART_CLOCK_SELECT(SELECT)                                 \
                         (                                            \
                          ((SELECT) == USART_CLOCK_SELECT_MCK    ) || \
                          ((SELECT) == USART_CLOCK_SELECT_MCKDIV8) || \
                          ((SELECT) == USART_CLOCK_SELECT_SCK    )    \
                         )
/**
  * @}
  */

/** @defgroup USART_Mode_Operation  USART mode of operation
  * @{
  */
#define USART_MODE_OPERATION_NORMAL                          ((uint32_t)0x00000000U)         /*!< USART mode of operation select normal                  */
#define USART_MODE_OPERATION_RS485                           (0x1U << 0U)                    /*!< USART mode of operation select rs485                   */
#define USART_MODE_OPERATION_MODEM                           (0x3U << 0U)                    /*!< USART mode of operation select mode                    */
#define USART_MODE_OPERATION_ISO7816_T_0                     (0x4U << 0U)                    /*!< USART mode of operation select iso7816 protocol: t = 0 */
#define USART_MODE_OPERATION_ISO7816_T_1                     (0x6U << 0U)                    /*!< USART mode of operation select iso7816 protocol: t = 1 */
#define USART_MODE_OPERATION_IrDA                            (0x8U << 0U)                    /*!< USART mode of operation select irda                    */
#define USART_MODE_OPERATION_LIN_MASTER                      (0xAU << 0U)                    /*!< USART mode of operation select lin master              */
#define USART_MODE_OPERATION_LIN_SLAVE                       (0xBU << 0U)                    /*!< USART mode of operation select lin slave               */
#define USART_MODE_OPERATION_SPI_MASTER                      (0xEU << 0U)                    /*!< USART mode of operation select spi master              */
#define USART_MODE_OPERATION_SPI_SLAVE                       (0xFU << 0U)                    /*!< USART mode of operation select spi slave               */

#define IS_USART_MODE_OPERATION(OPERATION)                                     \
                         (                                                     \
                          ((OPERATION) == USART_MODE_OPERATION_NORMAL     ) || \
                          ((OPERATION) == USART_MODE_OPERATION_RS485      ) || \
                          ((OPERATION) == USART_MODE_OPERATION_MODEM      ) || \
                          ((OPERATION) == USART_MODE_OPERATION_ISO7816_T_0) || \
                          ((OPERATION) == USART_MODE_OPERATION_ISO7816_T_1) || \
                          ((OPERATION) == USART_MODE_OPERATION_IrDA       ) || \
                          ((OPERATION) == USART_MODE_OPERATION_LIN_MASTER ) || \
                          ((OPERATION) == USART_MODE_OPERATION_LIN_SLAVE  ) || \
                          ((OPERATION) == USART_MODE_OPERATION_SPI_MASTER ) || \
                          ((OPERATION) == USART_MODE_OPERATION_SPI_SLAVE  )    \
                         )
/**
  * @}
  */

/** @defgroup USART_WRDBT   USART wait read data before transfer in spi mode
  * @{
  */
#define USART_WRDBT_DISABLE                                  ((uint32_t)0x00000000)           /*!< the character transmission starts as soon as a character is written into US_THR in SPI mode      */
#define USART_WRDBT_ENABLE                                   USART_MR_WRDBT                   /*!< the character transmission starts when a character and only if RXRDY flag is cleared in SPI mode */

#define IS_USART_WRDBT(TRANSFER)                                 \
                         (                                       \
                          ((TRANSFER) == USART_WRDBT_DISABLE) || \
                          ((TRANSFER) == USART_WRDBT_ENABLE )    \
                         )
/**
  * @}
  */

/** @defgroup USART_Clock_Polarity  USART Clock Polarity in spi mode
  * @{
  */
#define USART_POLARITY_LOW                                   ((uint32_t)0x00000000)          /*!< Driver enable signal is active low in SPI mode  */
#define USART_POLARITY_HIGH                                  USART_MR_CPOL                   /*!< Driver enable signal is active high in SPI mode */

#define IS_USART_POLARITY(POLARITY)                              \
                         (                                       \
                          ((POLARITY) == USART_POLARITY_LOW ) || \
                          ((POLARITY) == USART_POLARITY_HIGH)    \
                         )
/**
  * @}
  */

/** @defgroup USART_Clock_Phase   USART Clock Phase in spi mode
  * @{
  */
#define USART_PHASE_2EDGE                                    ((uint32_t)0x00000000)          /*!< USART frame phase on second clock capture */
#define USART_PHASE_1EDGE                                    USART_MR_CPHA                   /*!< USART frame phase on first clock capture  */

#define IS_USART_PHASE(PHASE)                               \
                         (                                  \
                          ((PHASE) == USART_PHASE_2EDGE) || \
                          ((PHASE) == USART_PHASE_1EDGE)    \
                         )
/**
  * @}
  */

/** @defgroup USART_Mode   USART Mode
  * @{
  */
#define USART_MODE_RX                     USART_CR_RXEN                           /*!< RX mode enable      > */
#define USART_MODE_TX                     USART_CR_TXEN                           /*!< TX mode enable      > */
#define USART_MODE_TX_RX                  (USART_CR_RXEN | USART_CR_TXEN)         /*!< TX & RX mode enable > */
#define IS_USART_MODE(MODE)                               \
                         (                                \
                          ((MODE) == USART_MODE_RX   ) || \
                          ((MODE) == USART_MODE_TX   ) || \
                          ((MODE) == USART_MODE_TX_RX)    \
                         )
/**
  * @}
  */

/** @defgroup USART_Sync_Disable  USART synchronization disable in LIN mode
  * @{
  */
#define USART_SYNC_DISABLE_NONE                              ((uint32_t)0x00000000)          /*!< the synchronization procedure is performed in LIN Slave node configuration in LIN mode     */
#define USART_SYNC_DISABLE_ACTIVE                            USART_LINMR_SYNCDIS             /*!< the synchronization procedure is not performed in LIN Slave node configuration in LIN mode */

#define IS_USART_SYNC_DISABLE(DISABLE) (((DISABLE) == USART_SYNC_DISABLE_NONE  ) || \
                                        ((DISABLE) == USART_SYNC_DISABLE_ACTIVE))
/**
  * @}
  */

/** @defgroup USART_PDC_Mode  USART dma mode in LIN mode
  * @{
  */
#define USART_PDC_MODE_LINMR_NOTWRITE                        ((uint32_t)0x00000000)          /*!< The LIN mode register LINMR is not writted by the DMA                  */
#define USART_PDC_MODE_LINMR_WRITE                           USART_LINMR_PDCM                /*!< The LIN mode register LINMR(excepting that flag) is writted by the DMA */

#define IS_USART_PDC_MODE_LINMR(LINMR)                                  \
                         (                                              \
                          ((LINMR) == USART_PDC_MODE_LINMR_NOTWRITE) || \
                          ((LINMR) == USART_PDC_MODE_LINMR_WRITE   )    \
                         )
/**
  * @}
  */

/** @defgroup USART_Wkup_Type  USART wakeup signal type in LIN mode
  * @{
  */
#define USART_WKUP_TYPE_LIN_2_0                              ((uint32_t)0x00000000)          /*!< Setting the bit LINWKUP in the control register sends a LIN 2.0 wakeup signal */
#define USART_WKUP_TYPE_LIN_1_3                              USART_LINMR_WKUPTYP             /*!< Setting the bit LINWKUP in the control register sends a LIN 1.3 wakeup signal */
#define IS_USART_WKUP_TYPE(TYPE)                                 \
                         (                                       \
                          ((TYPE) == USART_WKUP_TYPE_LIN_2_0) || \
                          ((TYPE) == USART_WKUP_TYPE_LIN_1_3)    \
                         )
/**
  * @}
  */

/** @defgroup USART_Frame_Slot_Disable  USART frame slot mode disable in LIN mode
  * @{
  */
#define USART_FRAME_SLOT_DISABLE_NONE                        ((uint32_t)0x00000000)          /*!< The frame slot mode is enabled in LIN mode  */
#define USART_FRAME_SLOT_DISABLE_ACTIVE                      USART_LINMR_FSDIS               /*!< The frame slot mode is disabled in LIN mode */
#define IS_USART_FRAME_SLOT_DISABLE(DISABLE)                                \
                         (                                                  \
                          ((DISABLE) == USART_FRAME_SLOT_DISABLE_NONE  ) || \
                          ((DISABLE) == USART_FRAME_SLOT_DISABLE_ACTIVE)    )
/**
  * @}
  */

/** @defgroup USART_Data_Length_Mode  USART data length mode in LIN mode
  * @{
  */
#define USART_DATA_LENGTH_MODE_DLC                 ((uint32_t)0x00000000)                    /*!< The response data length is defined by the field DLC in LIN mode                                       */
#define USART_DATA_LENGTH_MODE_ID_5_6              USART_LINMR_DLM                           /*!< The response data length is defined by the bits 5 and 6 of the identifier (IDCHR in LINIR) in LIN mode */
#define IS_USART_DATA_LENGTH_MODE(MODE)                                \
                         (                                             \
                          ((MODE) == USART_DATA_LENGTH_MODE_DLC   ) || \
                          ((MODE) == USART_DATA_LENGTH_MODE_ID_5_6)    \
                         )
/**
  * @}
  */

/** @defgroup USART_Checksum_Type  USART checksum type in LIN mode
  * @{
  */
#define USART_CHECKSUM_TYPE_ENHANCED                         ((uint32_t)0x00000000)          /*!< LIN 2.0 "Enhanced" Checksum */
#define USART_CHECKSUM_TYPE_CLASSIC                          USART_LINMR_CHKTYP              /*!< LIN 1.3 "Classic " Checksum */

#define IS_USART_CHECKSUM_TYPE(TYPE)                                  \
                         (                                            \
                          ((TYPE) == USART_CHECKSUM_TYPE_ENHANCED) || \
                          ((TYPE) == USART_CHECKSUM_TYPE_CLASSIC )    \
                         )
/**
  * @}
  */

/** @defgroup USART_Checksum_Disable  USART checksum disable in LIN mode
  * @{
  */
#define USART_CHECKSUM_DISABLE_NONE                         ((uint32_t)0x00000000)          /*!< LIN Checksum not disable */
#define USART_CHECKSUM_DISABLE_ACTIVE                       USART_LINMR_CHKDIS              /*!< LIN Checksum disable     */

#define IS_USART_CHECKSUM_DISABLE(DISABLE)                                \
                         (                                                \
                          ((DISABLE) == USART_CHECKSUM_DISABLE_NONE  ) || \
                          ((DISABLE) == USART_CHECKSUM_DISABLE_ACTIVE)    \
                         )
/**
  * @}
  */

/** @defgroup USART_Parity_Disable  USART parity disable in LIN mode
  * @{
  */
#define USART_PARITY_DISABLE_NONE                           ((uint32_t)0x00000000)          /*!< LIN Parity not disable */
#define USART_PARITY_DISABLE_ACTIVE                         USART_LINMR_PARDIS              /*!< LIN Parity disable     */

#define IS_USART_PARITY_DISABLE(DISABLE)                                \
                         (                                              \
                          ((DISABLE) == USART_PARITY_DISABLE_NONE  ) || \
                          ((DISABLE) == USART_PARITY_DISABLE_ACTIVE)    \
                         )
/**
  * @}
  */

/** @defgroup USART_Node_Active  USART checksum disable in LIN mode
  * @{
  */
#define USART_NODE_ACTIVE_PUBLISH                           ((uint32_t)0x00000000)          /*!< The USART transmits the response                              */
#define USART_NODE_ACTIVE_SUBSCRIBE                         (0x1U << 0U)                    /*!< The USART receives the response                               */
#define USART_NODE_ACTIVE_IGNORE                            (0x2U << 0U)                    /*!< The USART does not transmit and does not receive the response */

#define IS_USART_NODE_ACTIVE(ACTIVE)                                   \
                         (                                             \
                          ((ACTIVE) == USART_NODE_ACTIVE_PUBLISH  ) || \
                          ((ACTIVE) == USART_NODE_ACTIVE_SUBSCRIBE) || \
                          ((ACTIVE) == USART_NODE_ACTIVE_IGNORE   )    \
                         )
/**
  * @}
  */

/** @defgroup USART_DMA_TX  USART DMA enable transmitter
  * @{
  */
#define USART_DMA_TX_DISABLE                                ((uint32_t)0x00000000)          /*!< DMA mode is disable for transmission */
#define USART_DMA_TX_ENABLE                                 USART_CR_DMAT_EN                /*!< DMA mode is enable for transmission  */

#define IS_USART_DMA_TX_ENABLE(ENABLE)                          \
                         (                                      \
                          ((ENABLE) == USART_DMA_TX_DISABLE) || \
                          ((ENABLE) == USART_DMA_TX_ENABLE )    \
                         )
/**
  * @}
  */

/** @defgroup USART_DMA_RX  USART DMA enable receiver
  * @{
  */
#define USART_DMA_RX_DISABLE                                ((uint32_t)0x00000000)          /*!< DMA mode is disable for reception */
#define USART_DMA_RX_ENABLE                                 USART_CR_DMAR_EN                /*!< DMA mode is enable for reception  */

#define IS_USART_DMA_RX_ENABLE(ENABLE)                          \
                         (                                      \
                          ((ENABLE) == USART_DMA_RX_DISABLE) || \
                          ((ENABLE) == USART_DMA_RX_ENABLE )    \
                         )
/**
  * @}
  */

/** @defgroup USART_Hardware_Flow_Control
  * @{
  */

#define USART_HardwareFlowControl_None      ((uint32_t)0x00000000)
#define USART_HardwareFlowControl_RTS        (USART_CR_RTSEN | USART_CR_FCS)
#define USART_HardwareFlowControl_DTR         USART_CR_DTREN
#define USART_HardwareFlowControl_RTS_DTR   ((USART_CR_RTSEN | USART_CR_FCS) | USART_CR_DTREN)
#define IS_USART_HARDWARE_FLOW_CONTROL(CONTROL)                                    \
                              (                                                    \
                               ((CONTROL) == USART_HardwareFlowControl_None   ) || \
                               ((CONTROL) == USART_HardwareFlowControl_RTS    ) || \
                               ((CONTROL) == USART_HardwareFlowControl_DTR    ) || \
                               ((CONTROL) == USART_HardwareFlowControl_RTS_DTR)    \
                              )

/**
  * @}
  */

/** @defgroup USART_Flags
  * @brief    Flag mask in the CSR register
  * @{
  */
#define USART_FLAG_CTS                      USART_CSR_CTS           /*!< USART image of CTS input                             */
#define USART_FLAG_DSR                      USART_CSR_DSR           /*!< USART image of DSR input                             */
#define USART_FLAG_CTSIC                    USART_CSR_CTSIC         /*!< USART Clear to Send input change flag                */
#define USART_FLAG_DSRIC                    USART_CSR_DSRIC         /*!< USART Data Set Ready input change flag               */
#define USART_FLAG_NACK                     USART_CSR_NACK          /*!< USART non acknowledge interrupt                      */
#define USART_FLAG_ITER                     USART_CSR_ITER          /*!< USART max number of repetitions reached              */
#define USART_FLAG_TXEMPTY                  USART_CSR_TXEMPTY       /*!< USART transmitter empty                              */
#define USART_FLAG_TIMEOUT                  USART_CSR_TIMEOUT       /*!< USART receiver time-out                              */
#define USART_FLAG_PARE                     USART_CSR_PARE          /*!< USART parity error                                   */
#define USART_FLAG_FRAME                    USART_CSR_FRAME         /*!< USART framing error                                  */
#define USART_FLAG_OVER                     USART_CSR_OVRE          /*!< USART overrun error                                  */
#define USART_FLAG_RXBRK                    USART_CSR_RXBRK         /*!< USART break receive/end of break                     */
#define USART_FLAG_TXRDY                    USART_CSR_TXRDY         /*!< USART transmitter ready                              */
#define USART_FLAG_RXRDY                    USART_CSR_RXRDY         /*!< USART receiver ready                                 */

#define USART_FLAG_UNRE                     USART_CSR_UNRE          /*!< USART underrun error                                 */

#define USART_FLAG_LINHTE                   USART_CSR_LINHTE        /*!< USART LIN header timeout error                       */
#define USART_FLAG_LINSTE                   USART_CSR_LINSTE        /*!< USART LIN synch tolerance eror                       */
#define USART_FLAG_LINSNRE                  USART_CSR_LINSNRE       /*!< USART LIN slave not response error                   */
#define USART_FLAG_LINCE                    USART_CSR_LINCE         /*!< USART LIN checksum error                             */
#define USART_FLAG_LINIPE                   USART_CSR_LINIPE        /*!< USART LIN identifier parity error                    */
#define USART_FLAG_LINISFE                  USART_CSR_LINISFE       /*!< USART LIN inconsistent synch field error             */
#define USART_FLAG_LINBE                    USART_CSR_LINBE         /*!< USART LIN bit error                                  */
#define USART_FLAG_LINBLS                   USART_CSR_LINBLS        /*!< USART LIN bus line status                            */
#define USART_FLAG_LINTC                    USART_CSR_LINTC         /*!< USART LIN transfer completed                         */
#define USART_FLAG_LINID                    USART_CSR_LINID         /*!< USART LIN identifier sent or LIN identifier received */
#define USART_FLAG_LINBK                    USART_CSR_LINBK         /*!< USART LIN break sent or LIN break received           */
/**
  * @}
  */

/** @defgroup USART_Clear_Flags
 *  @brief    Flag clear in the CR register
  * @{
  */
#define USART_CLEAR_CTSIC                    USART_CR_RSTTX          /*!< USART Clear to Send input interrupt clear                            */
#define USART_CLEAR_DSRIC                    USART_CR_RSTRX          /*!< USART Data Set Ready input change clear                              */
#define USART_CLEAR_NACK                     USART_CR_RSTNACK        /*!< USART non acknowledge interrupt clear                                */
#define USART_CLEAR_ITER                     USART_CR_RSTIT          /*!< USART max number of repetitions reached interrupt clear              */
#define USART_CLEAR_TXEMPTY                  USART_CR_RSTTX          /*!< USART transmitter empty interrupt clear                              */
#define USART_CLEAR_TIMEOUT                  USART_CR_STTTO          /*!< USART receiver time-out interrupt clear                              */
#define USART_CLEAR_PARE                     USART_CR_RSTSTA         /*!< USART parity error interrupt clear                                   */
#define USART_CLEAR_FRAME                    USART_CR_RSTSTA         /*!< USART framing error interrupt clear                                  */
#define USART_CLEAR_OVER                     USART_CR_RSTSTA         /*!< USART overrun error interrupt clear                                  */
#define USART_CLEAR_RXBRK                    USART_CR_RSTSTA         /*!< USART break receive/end of break interrupt clear                     */
#define USART_CLEAR_TXRDY                    USART_CR_RSTTX          /*!< USART transmitter ready interrupt clear                              */
#define USART_CLEAR_RXRDY                    USART_CR_RSTRX          /*!< USART receiver ready interrupt clear                                 */

#define USART_CLEAR_UNRE                     USART_CR_RSTSTA         /*!< USART underrun error interrupt clear                                 */

#define USART_CLEAR_LINHTE                   USART_CR_RSTSTA         /*!< USART LIN header timeout error interrupt clear                       */
#define USART_CLEAR_LINSTE                   USART_CR_RSTSTA         /*!< USART LIN synch tolerance eror interrupt clear                       */
#define USART_CLEAR_LINSNRE                  USART_CR_RSTSTA         /*!< USART LIN slave not response error interrupt clear                   */
#define USART_CLEAR_LINCE                    USART_CR_RSTSTA         /*!< USART LIN checksum error interrupt clear                             */
#define USART_CLEAR_LINIPE                   USART_CR_RSTSTA         /*!< USART LIN identifier parity error interrupt clear                    */
#define USART_CLEAR_LINISFE                  USART_CR_RSTSTA         /*!< USART LIN inconsistent synch field error interrupt clear             */
#define USART_CLEAR_LINBE                    USART_CR_RSTSTA         /*!< USART LIN bit error interrupt clear                                  */
#define USART_CLEAR_LINTC                    USART_CR_RSTSTA         /*!< USART LIN transfer completed interrupt clear                         */
#define USART_CLEAR_LINID                    USART_CR_RSTSTA         /*!< USART LIN identifier sent or LIN identifier received interrupt clear */
#define USART_CLEAR_LINBK                    USART_CR_RSTSTA         /*!< USART LIN break sent or LIN break received interrupt clear           */
/**
  * @}
  */

/** @defgroup USART_Interrupt_definition
  * @brief Interrupt enable register - IER register
  * @{
  */
#define USART_IT_CTSIC                    USART_IER_CTSIC         /*!< USART Clear to Send input interruption                            */
#define USART_IT_DSRIC                    USART_IER_DSRIC         /*!< USART Data Set Ready input change interruption                    */
#define USART_IT_NACK                     USART_IER_NACK          /*!< USART non acknowledge interruption                                */
#define USART_IT_ITER                     USART_IER_ITER          /*!< USART max number of repetitions reached interruption              */
#define USART_IT_TXEMPTY                  USART_IER_TXEMPTY       /*!< USART transmitter empty interruption                              */
#define USART_IT_TIMEOUT                  USART_IER_TIMEOUT       /*!< USART receiver time-out interruption                              */
#define USART_IT_PARE                     USART_IER_PARE          /*!< USART parity error interruption                                   */
#define USART_IT_FRAME                    USART_IER_FRAME         /*!< USART framing error interruption                                  */
#define USART_IT_OVER                     USART_IER_OVRE          /*!< USART overrun error interruption                                  */
#define USART_IT_RXBRK                    USART_IER_RXBRK         /*!< USART break receive/end of break interruption                     */
#define USART_IT_TXRDY                    USART_IER_TXRDY         /*!< USART transmitter ready interruption                              */
#define USART_IT_RXRDY                    USART_IER_RXRDY         /*!< USART receiver ready interruption                                 */

#define USART_IT_UNRE                     USART_IER_UNRE          /*!< USART underrun error interruption                                 */

#define USART_IT_LINHTE                   USART_IER_LINHTE        /*!< USART LIN header timeout error interruption                       */
#define USART_IT_LINSTE                   USART_IER_LINSTE        /*!< USART LIN synch tolerance eror interruption                       */
#define USART_IT_LINSNRE                  USART_IER_LINSNRE       /*!< USART LIN slave not response error interruption                   */
#define USART_IT_LINCE                    USART_IER_LINCE         /*!< USART LIN checksum error interruption                             */
#define USART_IT_LINIPE                   USART_IER_LINIPE        /*!< USART LIN identifier parity error interruption                    */
#define USART_IT_LINISFE                  USART_IER_LINISFE       /*!< USART LIN inconsistent synch field error interruption             */
#define USART_IT_LINBE                    USART_IER_LINBE         /*!< USART LIN bit error interruption                                  */
#define USART_IT_LINTC                    USART_IER_LINTC         /*!< USART LIN transfer completed interruption                         */
#define USART_IT_LINID                    USART_IER_LINID         /*!< USART LIN identifier sent or LIN identifier received interruption */
#define USART_IT_LINBK                    USART_IER_LINBK         /*!< USART LIN break sent or LIN break received interruption           */
/**
  * @}
  */

/** @defgroup USART_Interrupt_disable
  * @brief Interrupt disable register - IDR register
  * @{
  */
#define USART_DIS_CTSIC                    USART_IDR_CTSIC         /*!< USART Clear to Send input interrupt disable                            */
#define USART_DIS_DSRIC                    USART_IDR_DSRIC         /*!< USART Data Set Ready input change interrupt disable                    */
#define USART_DIS_NACK                     USART_IDR_NACK          /*!< USART non acknowledge interrupt disable                                */
#define USART_DIS_ITER                     USART_IDR_ITER          /*!< USART max number of repetitions reached interrupt disable              */
#define USART_DIS_TXEMPTY                  USART_IDR_TXEMPTY       /*!< USART transmitter empty interrupt disable                              */
#define USART_DIS_TIMEOUT                  USART_IDR_TIMEOUT       /*!< USART receiver time-out interrupt disable                              */
#define USART_DIS_PARE                     USART_IDR_PARE          /*!< USART parity error interrupt disable                                   */
#define USART_DIS_FRAME                    USART_IDR_FRAME         /*!< USART framing error interrupt disable                                  */
#define USART_DIS_OVER                     USART_IDR_OVRE          /*!< USART overrun error interrupt disable                                  */
#define USART_DIS_RXBRK                    USART_IDR_RXBRK         /*!< USART break receive/end of break interrupt disable                     */
#define USART_DIS_TXRDY                    USART_IDR_TXRDY         /*!< USART transmitter ready interrupt disable                              */
#define USART_DIS_RXRDY                    USART_IDR_RXRDY         /*!< USART receiver ready interrupt disable                                 */

#define USART_DIS_UNRE                     USART_IDR_UNRE          /*!< USART underrun error interrupt disable                                 */

#define USART_DIS_LINHTE                   USART_IDR_LINHTE        /*!< USART LIN header timeout error interrupt disable                       */
#define USART_DIS_LINSTE                   USART_IDR_LINSTE        /*!< USART LIN synch tolerance eror interrupt disable                       */
#define USART_DIS_LINSNRE                  USART_IDR_LINSNRE       /*!< USART LIN slave not response error interrupt disable                   */
#define USART_DIS_LINCE                    USART_IDR_LINCE         /*!< USART LIN checksum error interrupt disable                             */
#define USART_DIS_LINIPE                   USART_IDR_LINIPE        /*!< USART LIN identifier parity error interrupt disable                    */
#define USART_DIS_LINISFE                  USART_IDR_LINISFE       /*!< USART LIN inconsistent synch field error interrupt disable             */
#define USART_DIS_LINBE                    USART_IDR_LINBE         /*!< USART LIN bit error interrupt disable                                  */
#define USART_DIS_LINTC                    USART_IDR_LINTC         /*!< USART LIN transfer completed interrupt disable                         */
#define USART_DIS_LINID                    USART_IDR_LINID         /*!< USART LIN identifier sent or LIN identifier received interrupt disable */
#define USART_DIS_LINBK                    USART_IDR_LINBK         /*!< USART LIN break sent or LIN break received interrupt disable           */
/**
  * @}
  */

/** @defgroup USART_Interruption_Mask
  * @brief Interrupt mask register - IMR register
  * @{
  */
#define USART_MASK_CTSIC                    USART_IMR_CTSIC         /*!< USART Clear to Send input interrupt mask                            */
#define USART_MASK_DSRIC                    USART_IMR_DSRIC         /*!< USART Data Set Ready input change mask                              */
#define USART_MASK_NACK                     USART_IMR_NACK          /*!< USART non acknowledge interrupt mask                                */
#define USART_MASK_ITER                     USART_IMR_ITER          /*!< USART max number of repetitions reached interrupt mask              */
#define USART_MASK_TXEMPTY                  USART_IMR_TXEMPTY       /*!< USART transmitter empty interrupt mask                              */
#define USART_MASK_TIMEOUT                  USART_IMR_TIMEOUT       /*!< USART receiver time-out interrupt mask                              */
#define USART_MASK_PARE                     USART_IMR_PARE          /*!< USART parity error interrupt mask                                   */
#define USART_MASK_FRAME                    USART_IMR_FRAME         /*!< USART framing error interrupt mask                                  */
#define USART_MASK_OVER                     USART_IMR_OVRE          /*!< USART overrun error interrupt mask                                  */
#define USART_MASK_RXBRK                    USART_IMR_RXBRK         /*!< USART break receive/end of break interrupt mask                     */
#define USART_MASK_TXRDY                    USART_IMR_TXRDY         /*!< USART transmitter ready interrupt mask                              */
#define USART_MASK_RXRDY                    USART_IMR_RXRDY         /*!< USART receiver ready interrupt mask                                 */

#define USART_MASK_UNRE                     USART_IMR_UNRE          /*!< USART underrun error interrupt mask                                 */

#define USART_MASK_LINHTE                   USART_IMR_LINHTE        /*!< USART LIN header timeout error interrupt mask                       */
#define USART_MASK_LINSTE                   USART_IMR_LINSTE        /*!< USART LIN synch tolerance eror interrupt mask                       */
#define USART_MASK_LINSNRE                  USART_IMR_LINSNRE       /*!< USART LIN slave not response error interrupt mask                   */
#define USART_MASK_LINCE                    USART_IMR_LINCE         /*!< USART LIN checksum error interrupt mask                             */
#define USART_MASK_LINIPE                   USART_IMR_LINIPE        /*!< USART LIN identifier parity error interrupt mask                    */
#define USART_MASK_LINISFE                  USART_IMR_LINISFE       /*!< USART LIN inconsistent synch field error interrupt mask             */
#define USART_MASK_LINBE                    USART_IMR_LINBE         /*!< USART LIN bit error interrupt mask                                  */
#define USART_MASK_LINTC                    USART_IMR_LINTC         /*!< USART LIN transfer completed interrupt mask                         */
#define USART_MASK_LINID                    USART_IMR_LINID         /*!< USART LIN identifier sent or LIN identifier received interrupt mask */
#define USART_MASK_LINBK                    USART_IMR_LINBK         /*!< USART LIN break sent or LIN break received interrupt mask           */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup USART_Exported_Macros USART Exported Macros
  * @{
  */

/** @brief  Check whether the specified USART flag is set or not.
  * @param  None
  * @retval None
  */
#define IS_USART_GET_FLAG(FLAG)                                   \
                             (                                    \
                                ((FLAG) == USART_FLAG_CTS    ) || \
                                ((FLAG) == USART_FLAG_DSR    ) || \
                                ((FLAG) == USART_FLAG_CTSIC  ) || \
                                ((FLAG) == USART_FLAG_DSRIC  ) || \
                                ((FLAG) == USART_FLAG_NACK   ) || \
                                ((FLAG) == USART_FLAG_ITER   ) || \
                                ((FLAG) == USART_FLAG_TXEMPTY) || \
                                ((FLAG) == USART_FLAG_TIMEOUT) || \
                                ((FLAG) == USART_FLAG_PARE   ) || \
                                ((FLAG) == USART_FLAG_FRAME  ) || \
                                ((FLAG) == USART_FLAG_OVER   ) || \
                                ((FLAG) == USART_FLAG_RXBRK  ) || \
                                ((FLAG) == USART_FLAG_TXRDY  ) || \
                                ((FLAG) == USART_FLAG_RXRDY  ) || \
                                ((FLAG) == USART_FLAG_UNRE   ) || \
                                ((FLAG) == USART_FLAG_LINHTE ) || \
                                ((FLAG) == USART_FLAG_LINSTE ) || \
                                ((FLAG) == USART_FLAG_LINSNRE) || \
                                ((FLAG) == USART_FLAG_LINCE  ) || \
                                ((FLAG) == USART_FLAG_LINIPE ) || \
                                ((FLAG) == USART_FLAG_LINISFE) || \
                                ((FLAG) == USART_FLAG_LINBE  ) || \
                                ((FLAG) == USART_FLAG_LINBLS ) || \
                                ((FLAG) == USART_FLAG_LINTC  ) || \
                                ((FLAG) == USART_FLAG_LINID  ) || \
                                ((FLAG) == USART_FLAG_LINBK  )    \
                             )

/** @brief  Clear the specified USART pending flag enable.
  * @param  None
  * @retval None
  */
#define IS_USART_CLEAR_FLAG(FLAG)                                  \
                             (                                     \
                                ((FLAG) == USART_CLEAR_CTSIC  ) || \
                                ((FLAG) == USART_CLEAR_DSRIC  ) || \
                                ((FLAG) == USART_CLEAR_NACK   ) || \
                                ((FLAG) == USART_CLEAR_ITER   ) || \
                                ((FLAG) == USART_CLEAR_TXEMPTY) || \
                                ((FLAG) == USART_CLEAR_TIMEOUT) || \
                                ((FLAG) == USART_CLEAR_PARE   ) || \
                                ((FLAG) == USART_CLEAR_FRAME  ) || \
                                ((FLAG) == USART_CLEAR_OVER   ) || \
                                ((FLAG) == USART_CLEAR_RXBRK  ) || \
                                ((FLAG) == USART_CLEAR_TXRDY  ) || \
                                ((FLAG) == USART_CLEAR_RXRDY  ) || \
                                ((FLAG) == USART_CLEAR_UNRE   ) || \
                                ((FLAG) == USART_CLEAR_LINHTE ) || \
                                ((FLAG) == USART_CLEAR_LINSTE ) || \
                                ((FLAG) == USART_CLEAR_LINSNRE) || \
                                ((FLAG) == USART_CLEAR_LINCE  ) || \
                                ((FLAG) == USART_CLEAR_LINIPE ) || \
                                ((FLAG) == USART_CLEAR_LINISFE) || \
                                ((FLAG) == USART_CLEAR_LINBE  ) || \
                                ((FLAG) == USART_CLEAR_LINTC  ) || \
                                ((FLAG) == USART_CLEAR_LINID  ) || \
                                ((FLAG) == USART_CLEAR_LINBK  )    \
                             )

/** @brief  Enable the specified USART interrupt.
  * @param  None
  * @retval None
  */
#define IS_USART_ENABLE_IT(IT)                                \
                             (                                \
                                ((IT) == USART_IT_CTSIC  ) || \
                                ((IT) == USART_IT_DSRIC  ) || \
                                ((IT) == USART_IT_NACK   ) || \
                                ((IT) == USART_IT_ITER   ) || \
                                ((IT) == USART_IT_TXEMPTY) || \
                                ((IT) == USART_IT_TIMEOUT) || \
                                ((IT) == USART_IT_PARE   ) || \
                                ((IT) == USART_IT_FRAME  ) || \
                                ((IT) == USART_IT_OVER   ) || \
                                ((IT) == USART_IT_RXBRK  ) || \
                                ((IT) == USART_IT_TXRDY  ) || \
                                ((IT) == USART_IT_RXRDY  ) || \
                                ((IT) == USART_IT_UNRE   ) || \
                                ((IT) == USART_IT_LINHTE ) || \
                                ((IT) == USART_IT_LINSTE ) || \
                                ((IT) == USART_IT_LINSNRE) || \
                                ((IT) == USART_IT_LINCE  ) || \
                                ((IT) == USART_IT_LINIPE ) || \
                                ((IT) == USART_IT_LINISFE) || \
                                ((IT) == USART_IT_LINBE  ) || \
                                ((IT) == USART_IT_LINTC  ) || \
                                ((IT) == USART_IT_LINID  ) || \
                                ((IT) == USART_IT_LINBK  )    \
                             )

/** @brief  Disable the specified USART interrupt.
  * @param  None
  * @retval None
  */
#define IS_USART_CLEAR_IT(IT)                                  \
                             (                                 \
                                ((IT) == USART_DIS_CTSIC  ) || \
                                ((IT) == USART_DIS_DSRIC  ) || \
                                ((IT) == USART_DIS_NACK   ) || \
                                ((IT) == USART_DIS_ITER   ) || \
                                ((IT) == USART_DIS_TXEMPTY) || \
                                ((IT) == USART_DIS_TIMEOUT) || \
                                ((IT) == USART_DIS_PARE   ) || \
                                ((IT) == USART_DIS_FRAME  ) || \
                                ((IT) == USART_DIS_OVER   ) || \
                                ((IT) == USART_DIS_RXBRK  ) || \
                                ((IT) == USART_DIS_TXRDY  ) || \
                                ((IT) == USART_DIS_RXRDY  ) || \
                                ((IT) == USART_DIS_UNRE   ) || \
                                ((IT) == USART_DIS_LINHTE ) || \
                                ((IT) == USART_DIS_LINSTE ) || \
                                ((IT) == USART_DIS_LINSNRE) || \
                                ((IT) == USART_DIS_LINCE  ) || \
                                ((IT) == USART_DIS_LINIPE ) || \
                                ((IT) == USART_DIS_LINISFE) || \
                                ((IT) == USART_DIS_LINBE  ) || \
                                ((IT) == USART_DIS_LINTC  ) || \
                                ((IT) == USART_DIS_LINID  ) || \
                                ((IT) == USART_DIS_LINBK  )    \
                             )


/** @brief  Check whether the specified USART interrupt has occurred or not.
  * @param  None
  * @retval None
  */
#define IS_USART_GET_IT(IT)                                     \
                             (                                  \
                                ((IT) == USART_MASK_CTSIC  ) || \
                                ((IT) == USART_MASK_DSRIC  ) || \
                                ((IT) == USART_MASK_NACK   ) || \
                                ((IT) == USART_MASK_ITER   ) || \
                                ((IT) == USART_MASK_TXEMPTY) || \
                                ((IT) == USART_MASK_TIMEOUT) || \
                                ((IT) == USART_MASK_PARE   ) || \
                                ((IT) == USART_MASK_FRAME  ) || \
                                ((IT) == USART_MASK_OVER   ) || \
                                ((IT) == USART_MASK_RXBRK  ) || \
                                ((IT) == USART_MASK_TXRDY  ) || \
                                ((IT) == USART_MASK_RXRDY  ) || \
                                ((IT) == USART_MASK_UNRE   ) || \
                                ((IT) == USART_MASK_LINHTE ) || \
                                ((IT) == USART_MASK_LINSTE ) || \
                                ((IT) == USART_MASK_LINSNRE) || \
                                ((IT) == USART_MASK_LINCE  ) || \
                                ((IT) == USART_MASK_LINIPE ) || \
                                ((IT) == USART_MASK_LINISFE) || \
                                ((IT) == USART_MASK_LINBE  ) || \
                                ((IT) == USART_MASK_LINTC  ) || \
                                ((IT) == USART_MASK_LINID  ) || \
                                ((IT) == USART_MASK_LINBK  )    \
                             )

/**
  * @}
  */

/** @defgroup USART_Global_definition
  * @{
  */
#define IS_USART_BAUDRATE(BAUDRATE)       ((BAUDRATE ) <= 105000000U)
#define IS_USART_BAUDRATE_APB1(BAUDRATE)  ((BAUDRATE ) <= 52500000U )
#define IS_USART_FIDIRATIO(FIDIRATE)      ((FIDIRATE ) <= 2047U     )
#define IS_USART_IF(IF)                   ((IF       ) <= 0xFFU     )
#define IS_USART_TIMEOUT(TIMEOUT)         ((TIMEOUT  ) <= 0x1FFFF   )
#define IS_USART_TIMGUARD(TIMEGUARD)      ((TIMEGUARD) <= 0xFF      )
#define IS_USART_LINIR_WR(LINIR_WR)       ((LINIR_WR ) <= 0xFF      )
#define IS_USART_DATA(DATA)               ((DATA     ) <= 0x1FF     )
#define IS_USART_DLC(DATA)                ((DATA     ) <= 0xFF      )

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup USART_Exported_Functions USART Exported Functions
  * @{
  */
/* Initialization and de-initialization functions *****************************/
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);
void USART_StructInit(USART_InitTypeDef* USART_InitStruct);
void USART_DeInit(USART_TypeDef* USARTx);

/* Normal command and configuration functions *********************************/
/* Normal     Cmd */ void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* Hardware   Cmd */ void USART_RTSDIS_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* Hardware   Cmd */ void USART_RTSEN_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* Hardware   Cmd */ void USART_DTRDIS_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* Hardware   Cmd */ void USART_DTREN_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* Normal     Cmd */ void USART_RSTSTA_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* Normal     Cmd */ void USART_TXDIS_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* Normal     Cmd */ void USART_TXEN_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* Normal     Cmd */ void USART_RXDIS_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* Normal     Cmd */ void USART_RXEN_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* Normal     Cmd */ void USART_RSTTX_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* Normal     Cmd */ void USART_RSTRX_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* Normal     Cfg */ void USART_InvData_Cfg(USART_TypeDef* USARTx, FunctionalState NewState);
/* Normal     Cfg */ void USART_OverSampling8_Cfg(USART_TypeDef* USARTx, FunctionalState NewState);
/* Normal     Cfg */ void USART_ClkOutput_Cfg(USART_TypeDef* USARTx, FunctionalState NewState);
/* Normal     Cfg */ void USART_DataLength9_Cfg(USART_TypeDef* USARTx, FunctionalState NewState);
/* Normal     Cfg */ void USART_MSBFirst_Cfg(USART_TypeDef* USARTx, FunctionalState NewState);
/* Normal     Cfg */ void USART_ChannelMode_Cfg(USART_TypeDef* USARTx, uint32_t USART_ChannelMode);
/* Normal     Cfg */ void USART_StopBit_Cfg(USART_TypeDef* USARTx, uint32_t USART_StopBits);
/* Normal     Cfg */ void USART_Parity_Cfg(USART_TypeDef* USARTx, uint32_t USART_Parity);
/* Normal     Cfg */ void USART_SYNCMode_Cfg(USART_TypeDef* USARTx, FunctionalState NewState);
/* Normal     Cfg */ void USART_DataLength_Cfg(USART_TypeDef* USARTx, uint32_t USART_WordLength);
/* Normal     Cfg */ void USART_CLKSelect_Cfg(USART_TypeDef* USARTx, uint32_t USART_CLKSelect);
/* Normal     Cfg */ void USART_OperationMode_Cfg(USART_TypeDef* USARTx, uint32_t USART_OperationMode);

/* Fractional baudrate function ***********************************************/
/* Normal     Cfg */ void USART_FracDivider_Cfg(USART_TypeDef* USARTx, uint32_t USART_BaudRate);

/* Break command functions ****************************************************/
/* Normal     Cmd */ void USART_STPBRK_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* Normal     Cmd */ void USART_STTBRK_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);

/* Receiver time-out and transmitter timeguard functions **********************/
/* Normal     Cfg */ void USART_Receiver_TimeOut_Cfg(USART_TypeDef* USARTx, uint32_t USART_ReceiverTimeOut);
/* Normal     Cmd */ void USART_RETTO_After_Timeout_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* Normal     Cmd */ void USART_STTTO_After_Timeout_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* Normal     Cfg */ void USART_Transmitter_TimeGuard_Cfg(USART_TypeDef* USARTx, uint32_t USART_TransmitterTimeGuard);

/* Multidrop mode command function ********************************************/
/* Normal     Cmd */ void USART_SENDAInMultidropMode_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);

/* SPI mode functions *********************************************************/
/* SPI        Cmd */ void USART_RCS_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* SPI        Cmd */ void USART_FCS_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* SPI        Cfg */ void USART_WRDBT_Cfg(USART_TypeDef* USARTx, FunctionalState NewState);
/* SPI        Cfg */ void USART_CLKPolarity_Cfg(USART_TypeDef* USARTx, FunctionalState NewState);
/* SPI        Cfg */ void USART_CLKPhase_Cfg(USART_TypeDef* USARTx, FunctionalState NewState);

/* ISO7816 mode functions *****************************************************/
/* ISO7816_T0 Cmd  */ void USART_RSTNACK_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* ISO7816_T0 Cmd  */ void USART_RSTIT_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* ISO7816_T0 Cfg  */ void USART_MaxIteration_Cfg(USART_TypeDef* USARTx, uint32_t USART_MAXIteration);
/* ISO7816_T0 Cfg  */ void USART_DsNack_Cfg(USART_TypeDef* USARTx, FunctionalState NewState);
/* ISO7816_T0 Cfg  */ void USART_INack_Cfg(USART_TypeDef* USARTx, FunctionalState NewState);
/* ISO7816_T0 Read */ uint32_t USART_GetNumberOfError(USART_TypeDef* USARTx);
/* ISO7816    Cfg  */ void USART_FiDiRatio_Cfg(USART_TypeDef* USARTx, uint32_t USART_FiDiRatio, uint32_t USART_BaudRate);

/* IrDA mode function *********************************************************/
/* IrDA       Cfg  */ void USART_IrDAFilter_Cfg(USART_TypeDef* USARTx, uint32_t USART_IrDAFilter);

/* LIN mode functions *********************************************************/
/* LIN        Cmd  */ void USART_LINWKUP_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* LIN        Cmd  */ void USART_LINABT_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
/* LIN        Cfg  */ void USART_Write_LINIR_In_LIN_Master(USART_TypeDef* USARTx, uint32_t USART_LINIR_Data);
/* LIN        Read */ uint32_t USART_Read_LINIR_In_LIN_Slave(USART_TypeDef* USARTx);
/* LIN        Cfg  */ void USART_SYNCDisable_Cfg(USART_TypeDef* USARTx, FunctionalState NewState);
/* LIN        Cfg  */ void USART_PDCMode_Cfg(USART_TypeDef* USARTx, FunctionalState NewState);
/* LIN        Cfg  */ void USART_DataLengthControl_Cfg(USART_TypeDef* USARTx, uint32_t USART_DataLengthControl);
/* LIN        Cfg  */ void USART_WkupType_Cfg(USART_TypeDef* USARTx, FunctionalState NewState);
/* LIN        Cfg  */ void USART_FrameSlotDisable_Cfg(USART_TypeDef* USARTx, FunctionalState NewState);
/* LIN        Cfg  */ void USART_DataLengthMode_Cfg(USART_TypeDef* USARTx, FunctionalState NewState);
/* LIN        Cfg  */ void USART_CheckSumType_Cfg(USART_TypeDef* USARTx, FunctionalState NewState);
/* LIN        Cfg  */ void USART_CheckSumDisable_Cfg(USART_TypeDef* USARTx, FunctionalState NewState);
/* LIN        Cfg  */ void USART_ParityDisable_Cfg(USART_TypeDef* USARTx, FunctionalState NewState);
/* LIN        Cfg  */ void USART_NodeAction_Cfg(USART_TypeDef* USARTx, uint32_t USART_NodeAction);
/* LIN        Read */ uint32_t USART_LINBaudRate(USART_TypeDef* USARTx);

/* Write protection register mode functions ***********************************/
void USART_WriteProtectionRegisterConfig(USART_WP_TypeDef* USARTx_WP, FunctionalState NewState);
FlagStatus USART_GetWriteProtectionRegisterStatus(USART_WP_TypeDef* USARTx_WP);
uint32_t USART_GetWriteProtectionRegisterSource(USART_WP_TypeDef* USARTx_WP);
uint32_t USART_ClearWPSRField(USART_WP_TypeDef* USARTx_WP);

/* Data transfers functions ***************************************************/
void USART_Transmit(USART_TypeDef* USARTx, uint16_t Data);
uint16_t USART_Receive(USART_TypeDef* USARTx);

/* DMA transfers management functions *****************************************/
void USART_DMATxEnable_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_DMARxEnable_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);

/* Low-Power SLEEP wakeup management function *********************************/
void USART_LowPowerSleepWkupConfig(USART_TypeDef* USARTx, FunctionalState NewState);

/* Interrupts and flags management functions **********************************/
void USART_ITConfig(USART_TypeDef* USARTx, uint32_t USART_IT, FunctionalState NewState);
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint32_t USART_FLAG);
void USART_ClearFlag(USART_TypeDef* USARTx, uint32_t USART_FLAG);
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint32_t USART_IT);
void USART_ITDisableConfig(USART_TypeDef* USARTx, uint32_t USART_IT, FunctionalState NewState);

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

#endif /* __FT32F4XX_USART_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
