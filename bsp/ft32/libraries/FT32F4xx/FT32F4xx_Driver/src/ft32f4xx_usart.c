/**
  ******************************************************************************
  * @file    ft32f4xx_usart.c
  * @author  FMD AE
  * @brief   This file provides firmware functions to manage the following
  *          functionalities of the Universal Synchronous/Asynchronous Receiver Transmitter
  *          Peripheral (USART).
  *          + Initialization and de-initialization functions
  *          + Normal command and configuration functions
  *          + Fractional baudrate function
  *          + Break command functions
  *          + Receiver time-out and transmitter timeguard functions
  *          + Multidrop mode command function
  *          + RS485 mode
  *          + MODEM mode
  *          + SPI mode functions
  *          + ISO7816 mode functions
  *          + IrDA mode function
  *          + LIN mode functions
  *          + Write protection register mode functions
  *          + Data transfers functions
  *          + DMA transfers management functions
  *          + Low-Power SLEEP wakeup management function
  *          + Interrupts and flags management functions
  * @version V1.0.0
  * @date    2025-03-21
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_usart.h"
#include "ft32f4xx_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup USART_Private_Constants USART Private Constants
  * @{
  */
/*!< USART CR register mode field Mask     ((~(uint32_t)0xFFFFFF5F)) */
#define CR_CLEAR_MODE_MASK        ((uint32_t)(USART_CR_TXDIS  | USART_CR_RXDIS))      /*!< USART CR mode fields of parameters set by USART_Init API         */

/*!< USART CR register hardware field Mask ((~(uint32_t)0xFFF9FFFF)) */
#define CR_CLEAR_HARDWARE_MASK    ((uint32_t)(USART_CR_RTSDIS | USART_CR_DTRDIS))     /*!< USART CR hardware fields of parameters set by USART_Init API     */

/*!< USART MR register SPI mode Mask       ((~(uint32_t)0xFFEEFEFF)) */
#define MR_CLEAR_SPI_MASK         ((uint32_t)(USART_MR_WRDBT  | USART_MR_CPOL | \
                                              USART_MR_CPHA))                         /*!< USART MR SPI mode fields of parameters set by USART_Init API     */

/*!< USART MR register ISO7816 mode Mask   ((~(uint32_t)0xF8CFFFFF)) */
#define MR_CLEAR_ISO7816_MASK     ((uint32_t)(USART_MR_MAX_ITERATION | USART_MR_DSNACK | \
                                              USART_MR_INACK))                        /*!< USART MR ISO7816 mode fields of parameters set by USART_Init API */

/*!< USART MR register normal Mask         ((~(uint32_t)0xFF700000)) */
#define MR_CLEAR_NORMAL_MASK      ((uint32_t)(USART_MR_INVDATA | USART_MR_OVER       | \
                                              USART_MR_CLKO    | USART_MR_MODE9      | \
                                              USART_MR_MSBF    | USART_MR_CHMODE     | \
                                              USART_MR_NBSTOP  | USART_MR_PAR        | \
                                              USART_MR_SYNC    | USART_MR_CHRL       | \
                                              USART_MR_USCLKS  | USART_MR_USART_MODE))/*!< USART MR normal fields of parameters set by USART_Init API       */

/**
  * @}
  */

/** @defgroup USART init and de-init functions
  * @brief    None
  *
@verbatim
 ===============================================================================
                           ##### Init and DeInit Functions #####
 ===============================================================================
    [..] This subsection provides a set of functions about USART initialization
         and de-initialization.

    [..] Most USART configurations can be set in the USART_init() function.
         However, After USART_Init() function, user can use others configurations
         (cfg) functions to change USART configurational. The command (Cmd)
         functions can execute control operations under different configurations.

    [..] The configuration procedure of USART_Init() function is as follows:
        (++) Check the parameters
        (++) Enable USARTx work clock and configuration clock.
        (++) USART CR configuration
             (#) Configure the USART_Mode:
                 (-) transmitter disable
                 (-) transmitter enable
                 (-) receiver disable
                 (-) receiver enable
             (#) Configure the USART RTS and DTR pins in RS485, MODEM and SPI mode:
                 (-) Request to send disable
                 (-) Request to send enable
                 (-) Data teriminal ready disable
                 (-) Data teriminal ready enable
        (++) USART MR configuration
             (#) Special configuration for SPI mode:
                 (-) Wait read data before transfer
                 (-) SPI clock polarity
                 (-) SPI clock phase
             (#) Special configuration for ISO7816 protocol T = 0 mode:
                 (-) Maximum number of automatic iteration
                 (-) Disable successive NACK
                 (-) Inhibit non acknowledge
             (#) Normal configuration:
                 (-) Inverted data
                 (-) Oversampling mode
                 (-) Clock output select
                 (-) 9-bit character length
                 (-) Bit order
                 (-) channel mode
                 (-) Number of STOP bits
                 (-) Parity type
                 (-) Synchronous mode select
                 (-) Character length
                 (-) Clock selection
                 (-) USART mode of operation
        (++) USART FIDI configuration
        (++) USART BRGR configuration except fractional part
        (++) USART IF configuration
        (++) USART LINMR configuration:
                 (-) Synchronization disable
                 (-) DMA mode
                 (-) Data length control
                 (-) Wakeup signal type
                 (-) Frame slot mode disable
                 (-) Data length mode
                 (-) Checksum type
                 (-) Checksum disable
                 (-) Parity disable
                 (-) LIN node action

    [..]

    (#) The USART init API's :
        (++) USART_Init()

    (#) The USART Struct init API's :
        (++) USART_StructInit()

    (#) The USART de-init API's :
        (++) USART_DeInit()
@endverbatim
  * @{
  */

/**
  * @brief  Initialize the USARTx peripheral according to the specified
  *         parameters in the USART_InitStruct.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure that contains
  *         the configuration information for the specified USART peripheral.
  * @retval None
  */
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct)
{
    uint32_t clock_divider = 0, frac_divider = 0, apbclock = 0, tmpreg = 0;

    RCC_ClocksTypeDef RCC_ClocksStatus;

    /*------------------------------ Check The Parameter ------------------------*/
    /* Check the normal parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));

    if ((USARTx == USART1) || (USARTx == USART6))
    {
        assert_param(IS_USART_BAUDRATE(USART_InitStruct->USART_BaudRate));
    }
    else if ((USARTx == USART2) || (USARTx == USART3))
    {
        assert_param(IS_USART_BAUDRATE_APB1(USART_InitStruct->USART_BaudRate));
    }

    assert_param(IS_USART_CHAR_LENGTH(USART_InitStruct->USART_WordLength));
    assert_param(IS_USART_CLOCK_OUTPUT(USART_InitStruct->USART_ClockOutput));
    assert_param(IS_USART_STOPBITS(USART_InitStruct->USART_StopBits));
    assert_param(IS_USART_PARITY(USART_InitStruct->USART_Parity));
    assert_param(IS_USART_MODE(USART_InitStruct->USART_Mode));
    assert_param(IS_USART_CLOCK_SELECT(USART_InitStruct->USART_CLKSelect));
    assert_param(IS_USART_MODE_OPERATION(USART_InitStruct->USART_OperationMode));
    assert_param(IS_USART_HARDWARE_FLOW_CONTROL(USART_InitStruct->USART_HardwareFlowControl));
    assert_param(IS_USART_SYNC_MODE(USART_InitStruct->USART_Sync));
    assert_param(IS_USART_BIT_ORDER(USART_InitStruct->USART_BitOrder));
    assert_param(IS_USART_CHANNEL_MODE(USART_InitStruct->USART_ChannelMode));
    assert_param(IS_USART_OVERSAMPLING(USART_InitStruct->USART_OverSampling));
    assert_param(IS_USART_INVDATA(USART_InitStruct->USART_INVData));

    /* Check ISO7816 mode special parameter */
    if ((USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_ISO7816_T_0) ||
            (USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_ISO7816_T_1))
    {
        assert_param(IS_USART_FIDIRATIO(USART_InitStruct->USART_FiDiRatio));
        assert_param(IS_USART_ISO7816_T0_INACK(USART_InitStruct->USART_InhibitNACK));
        assert_param(IS_USART_ISO7816_T0_DSNACK(USART_InitStruct->USART_DisSuccessiveNACK));
        assert_param(IS_USART_ISO7816_T0_MAX_ITERATION(USART_InitStruct->USART_MAXIteration));
    }

    /* Check IrDA mode special parameter */
    if (USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_IrDA)
    {
        assert_param(IS_USART_IF(USART_InitStruct->USART_IrDAFilter));
        assert_param(IS_USART_FIDIRATIO(USART_InitStruct->USART_FiDiRatio));
    }

    /* Check SPI mode special parameter */
    if ((USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_SPI_MASTER) ||
            (USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_SPI_SLAVE))
    {
        assert_param(IS_USART_WRDBT(USART_InitStruct->USART_WRDBT));
        assert_param(IS_USART_POLARITY(USART_InitStruct->USART_CLKPolarity));
        assert_param(IS_USART_PHASE(USART_InitStruct->USART_CLKPhase));
    }

    /* Check LIN mode special parameter */
    if ((USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_LIN_MASTER) ||
            (USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_LIN_SLAVE))
    {
        assert_param(IS_USART_SYNC_DISABLE(USART_InitStruct->USART_SYNCDisable));
        assert_param(IS_USART_PDC_MODE_LINMR(USART_InitStruct->USART_PDCMode));
        assert_param(IS_USART_DLC(USART_InitStruct->USART_DataLengthControl));
        assert_param(IS_USART_WKUP_TYPE(USART_InitStruct->USART_WkupType));
        assert_param(IS_USART_FRAME_SLOT_DISABLE(USART_InitStruct->USART_FrameSlotDisable));
        assert_param(IS_USART_DATA_LENGTH_MODE(USART_InitStruct->USART_DataLengthMode));
        assert_param(IS_USART_CHECKSUM_TYPE(USART_InitStruct->USART_CheckSumType));
        assert_param(IS_USART_CHECKSUM_DISABLE(USART_InitStruct->USART_CheckSumDisable));
        assert_param(IS_USART_PARITY_DISABLE(USART_InitStruct->USART_ParityDisable));
        assert_param(IS_USART_NODE_ACTIVE(USART_InitStruct->USART_NodeAction));
    }

    /*----------------------------- Enable The Peripheral -----------------------*/
    if (USARTx == USART1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    }
    else if (USARTx == USART2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART2, ENABLE);
    }
    else if (USARTx == USART3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART3, ENABLE);
    }
    else if (USARTx == USART6)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
    }

    /*---------------------------- USART CR Configuration -----------------------*/
    tmpreg = USARTx->CR;

    /* Configure the USART_Mode                       */
    /* Configure the TXDIS and RXDIS bits             */
    USARTx->CR |= ((uint32_t)(CR_CLEAR_MODE_MASK));
    /* Configure the TXEN and RXEN bits               */
    tmpreg |= USART_InitStruct->USART_Mode;

    /* Configure the USART RTS in SPI mode and DTR in MODEM mode    */
    if ((USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_MODEM) ||
            (USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_SPI_MASTER) ||
            (USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_SPI_SLAVE))
    {
        /* Configure the hardware flow control bits RTSDIS and DTRDIS */
        USARTx->CR |= ((uint32_t)(CR_CLEAR_HARDWARE_MASK));
        /* Configure the hardware flow control bits RTSEN and DTREN   */
        tmpreg |= USART_InitStruct->USART_HardwareFlowControl;
    }

    /* Write to USART CR */
    USARTx->CR = tmpreg;

    /*---------------------------- USART MR Configuration -----------------------*/
    tmpreg = USARTx->MR;

    /* Normal configuration                                                     */
    /* Set the [23:23]_INVDATA       ascording to USART_INVData           value */
    /* Set the [19:19]_OVER          ascording to USART_OverSampling      value */
    /* Set the [18:18]_CLKO          ascording to USART_ClockOutput       value */
    /* Set the [17:17]_MODE9         ascording to USART_WordLength        value */
    /* Set the [16:16]_MSBF          ascording to USART_BitOrder          value */
    /* Set the [15:14]_CHMODE        ascording to USART_ChannelMode       value */
    /* Set the [13:12]_NBSTOP        ascording to USART_StopBits          value */
    /* Set the [11: 9]_PAR           ascording to USART_Parity            value */
    /* Set the [ 8: 8]_SYNC          ascording to USART_Sync              value */
    /* Set the [ 7: 6]_CHRL          ascording to USART_WordLength        value */
    /* Set the [ 5: 4]_USCLKS        ascording to USART_CLKSelect         value */
    /* Set the [ 3: 0]_USART_MODE    ascording to USART_OperationMode     value */
    /* Clear the normal cfg bits     */
    tmpreg &= (uint32_t)~((uint32_t)MR_CLEAR_NORMAL_MASK);
    /* Configure the normal cfg bits */
    tmpreg |= (uint32_t)USART_InitStruct->USART_INVData                   |
              USART_InitStruct->USART_OverSampling              |
              USART_InitStruct->USART_ClockOutput               |
              USART_InitStruct->USART_WordLength                |
              USART_InitStruct->USART_BitOrder                  |
              USART_InitStruct->USART_ChannelMode               |
              USART_InitStruct->USART_StopBits                  |
              USART_InitStruct->USART_Parity                    |
              USART_InitStruct->USART_Sync                      |
              USART_InitStruct->USART_CLKSelect                 |
              USART_InitStruct->USART_OperationMode             ;

    /* Special configuration for SPI mode                                       */
    /* Set the [20:20]_WRDBT(SPI)    ascording to USART_WRDBT             value */
    /* Set the [16:16]_CPOL(SPI)     ascording to USART_CLKPolarity       value */
    /* Set the [ 8: 8]_CPHA(SPI)     ascording to USART_CLKPhase          value */
    if ((USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_SPI_MASTER) ||
            (USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_SPI_SLAVE))
    {
        /* Clear the SPI mode cfg bits WRDBT, CPOL and CPHA bits     */
        tmpreg &= (uint32_t)~((uint32_t)MR_CLEAR_SPI_MASK);
        /* Configure the SPI mode cfg bits WRDBT, CPOL and CPHA bits */
        tmpreg |= (uint32_t)USART_InitStruct->USART_WRDBT                   |
                  USART_InitStruct->USART_CLKPolarity             |
                  USART_InitStruct->USART_CLKPhase                ;
    }

    /* Special configuration for ISO7816 protocol T = 0 mode                    */
    /* Set the [26:24]_MAX_ITERATION ascording to USART_MAXIteration      value */
    /* Set the [21:21]_DSNACK        ascording to USART_DisSuccessiveNACK value */
    /* Set the [20:20]_INACK         ascording to USART_InhibitNACK       value */
    if (USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_ISO7816_T_0)
    {
        /* Clear the ISO7816 mode cfg bits MAX_ITERATION, DSNACK and INACK bits     */
        tmpreg &= (uint32_t)~((uint32_t)MR_CLEAR_ISO7816_MASK);
        /* Configure the ISO7816 mode cfg bits MAX_ITERATION, DSNACK and INACK bits */
        tmpreg |= (uint32_t)USART_InitStruct->USART_MAXIteration            |
                  USART_InitStruct->USART_DisSuccessiveNACK       |
                  USART_InitStruct->USART_InhibitNACK             ;
    }

    /* Write to USART MR */
    USARTx->MR = tmpreg;

    /*---------------------------- USART FIDI Configuration -----------------------*/
    if ((USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_ISO7816_T_0) ||
            (USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_ISO7816_T_1) ||
            (USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_IrDA))
    {
        USARTx->FIDI = (uint32_t)USART_InitStruct->USART_FiDiRatio;
    }

    /*---------------------------- USART BRGR Configuration -----------------------*/
    tmpreg = USARTx->BRGR;

    /* Configure the USART Baud Rate */
    RCC_GetClocksFreq(&RCC_ClocksStatus);

    if (USARTx == USART1)
    {
        apbclock = RCC_ClocksStatus.P2CLK_Frequency;
    }
    else if (USARTx == USART2)
    {
        apbclock = RCC_ClocksStatus.PCLK_Frequency ;
    }
    else if (USARTx == USART3)
    {
        apbclock = RCC_ClocksStatus.PCLK_Frequency ;
    }
    else if (USARTx == USART6)
    {
        apbclock = RCC_ClocksStatus.P2CLK_Frequency;
    }

    /* Determine the integer part and fraction part disable (fractional part can configure in USART_FracDivider_Cfg()) */
    /* BaudRate not equal 0*/
    if ((USART_InitStruct->USART_BaudRate) >  0)
    {
        /* Non ISO7816 Mode*/
        if (!((USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_ISO7816_T_0) ||
                (USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_ISO7816_T_1)))
        {
            /* Async mode*/
            if (!((USART_InitStruct->USART_Sync == USART_SYNC_MODE_SYNC) ||
                    (USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_SPI_MASTER) ||
                    (USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_SPI_SLAVE)))
            {
                /* x16 Oversample*/
                if (USART_InitStruct->USART_OverSampling == USART_OVERSAMPLING_16)
                {
                    clock_divider = (uint32_t)(((apbclock) / ((USART_InitStruct->USART_BaudRate) * 16)));
                    frac_divider  = 0;
                }
                /* x8  Oversample*/
                else if (USART_InitStruct->USART_OverSampling == USART_OVERSAMPLING_8)
                {
                    clock_divider = (uint32_t)(((apbclock) / ((USART_InitStruct->USART_BaudRate) * 8)));
                    frac_divider  = 0;
                }
            }
            /* Sync mode or SPI mode*/
            else if ((USART_InitStruct->USART_Sync == USART_SYNC_MODE_SYNC) ||
                     (USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_SPI_MASTER) ||
                     (USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_SPI_SLAVE))
            {
                clock_divider = (uint32_t)((apbclock) / ((USART_InitStruct->USART_BaudRate)));
            }
        }
        /* ISO7816 Mode*/
        else if (((USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_ISO7816_T_0) ||
                  (USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_ISO7816_T_1)))
        {
            clock_divider = (uint32_t)((apbclock) / ((USART_InitStruct->USART_BaudRate) *
                                       (USART_InitStruct->USART_FiDiRatio)));
        }
    }
    /* BaudRate     equal 0*/
    else if ((USART_InitStruct->USART_BaudRate) == 0)
    {
        clock_divider = 0;
        frac_divider  = 0;
    }

    /* Write to USART BRGR */
    USARTx->BRGR = (((uint32_t)(clock_divider)) | ((uint32_t)(frac_divider) << 16U));

    /*---------------------------- USART IF Configuration -----------------------*/
    /* Write to USART IF in IrDA mode */
    if (USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_IrDA)
    {
        USARTx->IF = (uint16_t)USART_InitStruct->USART_IrDAFilter;
    }

    /*---------------------------- USART LINMR Configuration --------------------*/
    tmpreg = 0;

    if ((USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_LIN_MASTER) ||
            (USART_InitStruct->USART_OperationMode == USART_MODE_OPERATION_LIN_SLAVE))
    {
        /* Set the [17:17]_SYNCDIS ascording to USART_SYNCDisable       value */
        /* Set the [16:16]_PDCM    ascording to USART_PDCMode           value */
        /* Set the [15: 8]_DLC     ascording to USART_DataLengthControl value */
        /* Set the [ 7: 7]_WKUPTYP ascording to USART_WkupType          value */
        /* Set the [ 6: 6]_FSDIS   ascording to USART_FrameSlotDisable  value */
        /* Set the [ 5: 5]_DLM     ascording to USART_DataLengthMode    value */
        /* Set the [ 4: 4]_CHKTYP  ascording to USART_CheckSumType      value */
        /* Set the [ 3: 3]_CHKDIS  ascording to USART_CheckSumDisable   value */
        /* Set the [ 2: 2]_PARDIS  ascording to USART_ParityDisable     value */
        /* Set the [ 1: 0]_NACT    ascording to USART_NodeAction        value */
        tmpreg |= (uint32_t)USART_InitStruct-> USART_SYNCDisable                        |
                  USART_InitStruct-> USART_PDCMode                            |
                  ((USART_InitStruct-> USART_DataLengthControl << (uint32_t)8)) |
                  USART_InitStruct-> USART_WkupType                           |
                  USART_InitStruct-> USART_FrameSlotDisable                   |
                  USART_InitStruct-> USART_DataLengthMode                     |
                  USART_InitStruct-> USART_CheckSumType                       |
                  USART_InitStruct-> USART_CheckSumDisable                    |
                  USART_InitStruct-> USART_ParityDisable                      |
                  ((USART_InitStruct-> USART_NodeAction        << (uint32_t)0)) ;

        /* Write to USART LINMR*/
        USARTx->LINMR = tmpreg;
    }
}

/**
  * @brief  Configure each USART_InitStruct member with its default value.
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void USART_StructInit(USART_InitTypeDef* USART_InitStruct)
{
    /* USART_InitStruct members default value */
    USART_InitStruct->USART_BaudRate            = 9600                            ;
    USART_InitStruct->USART_FiDiRatio           = 174                             ;
    USART_InitStruct->USART_IrDAFilter          = 0                               ;
    USART_InitStruct->USART_WordLength          = USART_CHAR_LENGTH_8BIT          ;
    USART_InitStruct->USART_ClockOutput         = USART_CLOCK_OUTPUT_DISABLE      ;
    USART_InitStruct->USART_StopBits            = USART_STOPBITS_1                ;
    USART_InitStruct->USART_Parity              = USART_PARITY_NONE               ;
    USART_InitStruct->USART_Mode                = USART_MODE_TX | USART_MODE_RX   ;
    USART_InitStruct->USART_CLKSelect           = USART_CLOCK_SELECT_MCK          ;
    USART_InitStruct->USART_OperationMode       = USART_MODE_OPERATION_NORMAL     ;
    USART_InitStruct->USART_HardwareFlowControl = USART_HardwareFlowControl_None  ;
    USART_InitStruct->USART_Sync                = USART_SYNC_MODE_ASYNC           ;
    USART_InitStruct->USART_BitOrder            = USART_BIT_ORDER_LSBF            ;
    USART_InitStruct->USART_ChannelMode         = USART_CHANNEL_MODE_NORMAL       ;
    USART_InitStruct->USART_WRDBT               = USART_WRDBT_DISABLE             ;
    USART_InitStruct->USART_OverSampling        = USART_OVERSAMPLING_16           ;
    USART_InitStruct->USART_CLKPolarity         = USART_POLARITY_LOW              ;
    USART_InitStruct->USART_CLKPhase            = USART_PHASE_2EDGE               ;
    USART_InitStruct->USART_INVData             = USART_INVDATA_DISABLE           ;
    USART_InitStruct->USART_InhibitNACK         = USART_ISO7816_T0_INACK_DISABLE  ;
    USART_InitStruct->USART_DisSuccessiveNACK   = USART_ISO7816_T0_DSNACK_DISABLE ;
    USART_InitStruct->USART_MAXIteration        = USART_ISO7816_T0_MAX_ITERATION_0;
    USART_InitStruct->USART_SYNCDisable         = USART_SYNC_DISABLE_NONE         ;
    USART_InitStruct->USART_PDCMode             = USART_PDC_MODE_LINMR_NOTWRITE   ;
    USART_InitStruct->USART_DataLengthControl   = 0                               ;
    USART_InitStruct->USART_WkupType            = USART_WKUP_TYPE_LIN_2_0         ;
    USART_InitStruct->USART_FrameSlotDisable    = USART_FRAME_SLOT_DISABLE_NONE   ;
    USART_InitStruct->USART_DataLengthMode      = USART_DATA_LENGTH_MODE_DLC      ;
    USART_InitStruct->USART_CheckSumType        = USART_CHECKSUM_TYPE_ENHANCED    ;
    USART_InitStruct->USART_CheckSumDisable     = USART_CHECKSUM_DISABLE_NONE     ;
    USART_InitStruct->USART_ParityDisable       = USART_PARITY_DISABLE_NONE       ;
    USART_InitStruct->USART_NodeAction          = USART_NODE_ACTIVE_PUBLISH       ;
}

/**
  * @brief  De-Initialize the USARTx peripheral to their default reset value.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @retval None
  */
void USART_DeInit(USART_TypeDef* USARTx)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));

    /* USARTx reset operation */
    if (USARTx == USART1)
    {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);
    }
    else if (USARTx == USART2)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART2, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART2, DISABLE);
    }
    else if (USARTx == USART3)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART3, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART3, DISABLE);
    }
    else if (USARTx == USART6)
    {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART6, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART6, DISABLE);
    }
}

/**
  * @}
  */

/** @defgroup USART normal cmd and cfg functions
  * @brief    USART normal command and configuration functions
  *
@verbatim
 ===============================================================================
              ##### Normal Command And Configuration Functions #####
 ===============================================================================
    [..] This subsection provides a set of normal command and configuration
         function.

    [..]

    (#) The Normal cmd API's :
        (++) USART_Cmd()
        (++) USART_RTSDIS_Cmd()
        (++) USART_RTSEN_Cmd()
        (++) USART_DTRDIS_Cmd()
        (++) USART_DTREN_Cmd()
        (++) USART_RSTSTA_Cmd()
        (++) USART_TXDIS_Cmd()
        (++) USART_TXEN_Cmd()
        (++) USART_RXDIS_Cmd()
        (++) USART_RXEN_Cmd()
        (++) USART_RSTTX_Cmd()
        (++) USART_RSTRX_Cmd()

    (#) The Normal cfg API's :
        (++) USART_InvData_Cfg()
        (++) USART_OverSampling8_Cfg()
        (++) USART_ClkOutput_Cfg()
        (++) USART_DataLength9_Cfg()
        (++) USART_MSBFirst_Cfg()
        (++) USART_ChannelMode_Cfg()
        (++) USART_StopBit_Cfg()
        (++) USART_Parity_Cfg()
        (++) USART_SYNCMode_Cfg()
        (++) USART_DataLength_Cfg()
        (++) USART_CLKSelect_Cfg()
        (++) USART_OperationMode_Cfg()

    (#) The Normal read API's :
        (++) None
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified USART peripheral.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected USART by setting the USARTxEN bit in the RCC_APB1ENR/APB2ENR register */
        if (USARTx == USART1)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
        }
        else if (USARTx == USART2)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART2, ENABLE);
        }
        else if (USARTx == USART3)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART3, ENABLE);
        }
        else if (USARTx == USART6)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
        }
    }
    else
    {
        /* Disable the selected USART by clearing the USARTxEN bit in the RCC_APB1ENR/APB2ENR register */
        if (USARTx == USART1)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE);
        }
        else if (USARTx == USART2)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART2, DISABLE);
        }
        else if (USARTx == USART3)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART3, DISABLE);
        }
        else if (USARTx == USART6)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, DISABLE);
        }
    }
}

/**
  * @brief  Request to send disable.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx request to send disable.
  *         This parameter can be:
  *           @arg ENABLE : Drives the pin RTS to 1
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_RTSDIS_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Request to send disable by setting RTSDIS bit in the CR register */
        USARTx->CR |= USART_CR_RTSDIS;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_RTSDIS);
    }
}

/**
  * @brief  Request to send enable.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx request to send enable.
  *         This parameter can be:
  *           @arg ENABLE : Drives the pin RTS to 0
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_RTSEN_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Request to send enable by setting RTSEN bit in the CR register */
        USARTx->CR |= USART_CR_RTSEN;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_RTSEN);
    }
}

/**
  * @brief  Data terminal ready disable.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx data terminal ready disable.
  *         This parameter can be:
  *           @arg ENABLE : Drives the pin DTR to 1
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_DTRDIS_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Data terminal ready disable by setting DTRDIS bit in the CR register */
        USARTx->CR |= USART_CR_DTRDIS;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_DTRDIS);
    }
}

/**
  * @brief  Data terminal ready enable.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx data terminal ready enable.
  *         This parameter can be:
  *           @arg ENABLE : Drives the pin DTR to 0
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_DTREN_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Data terminal ready enable by setting DTREN bit in the CR register */
        USARTx->CR |= USART_CR_DTREN;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_DTREN);
    }
}

/**
  * @brief  Reset status bits.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx reset status bits.
  *         This parameter can be:
  *           @arg ENABLE : Resets the status bits PARE, FRAME, OVER, LINBE,
  *                         LINISFE, LINIPE, LINCE, LINSNRE, LINSTE, LINHTE,
  *                         LINID, LINTC, LINBK and RXBRK in US_CSR.
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_RSTSTA_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* The status bits reset by setting RSTSTA bit in the CR register */
        USARTx->CR |= USART_CR_RSTSTA;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_RSTSTA);
    }
}

/**
  * @brief  Transmitter disable.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx transmitter disable.
  *         This parameter can be:
  *           @arg ENABLE : Disable the transmitter.
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_TXDIS_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* The transmitter disable by setting TXDIS bit in the CR register */
        USARTx->CR |= USART_CR_TXDIS;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_TXDIS);
    }
}

/**
  * @brief  Transmitter enable.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx transmitter enable.
  *         This parameter can be:
  *           @arg ENABLE : Enable the transmitter if TXDIS is 0.
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_TXEN_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* The transmitter enable by setting TXEN bit in the CR register */
        USARTx->CR |= USART_CR_TXEN;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_TXEN);
    }
}

/**
  * @brief  Receiver disable.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx receiver disable.
  *         This parameter can be:
  *           @arg ENABLE : Disable the receiver.
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_RXDIS_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* The receiver disable by setting RXDIS bit in the CR register */
        USARTx->CR |= USART_CR_RXDIS;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_RXDIS);
    }
}

/**
  * @brief  Receiver enable.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx receiver enable.
  *         This parameter can be:
  *           @arg ENABLE : Enable the receiver if RXDIS is 0.
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_RXEN_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* The receiver enable by setting RXEN bit in the CR register */
        USARTx->CR |= USART_CR_RXEN;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_RXEN);
    }
}

/**
  * @brief  Reset transmitter
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx reset transmitter.
  *         This parameter can be:
  *           @arg ENABLE : Resets the transmitter.
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_RSTTX_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* The transmitter reset by setting RSTTX bit in the CR register */
        USARTx->CR |= USART_CR_RSTTX;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_RSTTX);
    }
}

/**
  * @brief  Reset receiver
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx reset receiver.
  *         This parameter can be:
  *           @arg ENABLE : Resets the receiver.
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_RSTRX_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* The receiver reset by setting RSTRX bit in the CR register */
        USARTx->CR |= USART_CR_RSTRX;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_RSTRX);
    }
}

/**
  * @brief  Inverted data
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx inverted data.
  *         This parameter can be:
  *           @arg ENABLE : The data field transmitted on TXD line is inverted
  *                         compared to the value writted on US_THR register or
  *                         the content read in US_RHR is inverted compared to
  *                         what is received on TXD line (or ISO7816 IO line).
  *           @arg DISABLE: The data field transmitted on TXD line is the same
  *                         as one written in US_THR register or content read in
  *                         US_RHR is the same as RXD line. Normal mode of operation.
  * @retval None
  */
void USART_InvData_Cfg(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the invert data function by setting INVDATA bit in the MR register */
        USARTx->MR |= USART_MR_INVDATA;
    }
    else
    {
        /* Disable the invert data function by clearing INVDATA bit in the MR register */
        USARTx->MR &= (uint32_t)~((uint32_t)USART_MR_INVDATA);
    }
}

/**
  * @brief  Oversampling mode
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx oversampling mode.
  *         This parameter can be:
  *           @arg ENABLE : 8x oversampling.
  *           @arg DISABLE: 16x oversampling.
  * @retval None
  */
void USART_OverSampling8_Cfg(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the 8x oversampling function by setting OVER bit in the MR register */
        USARTx->MR |= USART_MR_OVER;
    }
    else
    {
        /* Disable the 8x oversampling function by clearing OVER bit in the MR register */
        USARTx->MR &= (uint32_t)~((uint32_t)USART_MR_OVER);
    }
}

/**
  * @brief  Clock output select
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx clock output select.
  *         This parameter can be:
  *           @arg ENABLE : The USART drives the SCK pin if USART_CLKSelect does
  *                         not select the external clock SCK.
  *           @arg DISABLE: The USART does not drive the SCK pin.
  * @retval None
  */
void USART_ClkOutput_Cfg(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the USART drives the SCK pin if USART_CLKSelect does not select the
           external clock SCK by setting CLKO bit in the MR register */
        USARTx->MR |= USART_MR_CLKO;
    }
    else
    {
        /* Disable the USART drives the SCK pin if USART_CLKSelect does not select the
           external clock SCK by clearing CLKO bit in the MR register */
        USARTx->MR &= (uint32_t)~((uint32_t)USART_MR_CLKO);
    }
}

/**
  * @brief  9-bit character length
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx 9-bit character length.
  *         This parameter can be:
  *           @arg ENABLE : 9-bit character length.
  *           @arg DISABLE: USART_Char_Length defines character length.
  * @retval None
  */
void USART_DataLength9_Cfg(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable 9-bit character length by setting MODE9 bit in the MR register */
        USARTx->MR |= USART_MR_MODE9;
    }
    else
    {
        /* Disable 9-bit character length by clearing MODE9 bit in the MR register */
        USARTx->MR &= (uint32_t)~((uint32_t)USART_MR_MODE9);
    }
}

/**
  * @brief  Bit order
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx bit order.
  *         This parameter can be:
  *           @arg ENABLE : Most significant bit is sent/received first.
  *           @arg DISABLE: Least significant bit is sent/received first.
  * @retval None
  */
void USART_MSBFirst_Cfg(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable most significant bit is sent/received by setting MSBF bit in the MR register */
        USARTx->MR |= USART_MR_MSBF;
    }
    else
    {
        /* Enable least significant bit is sent/received by setting MSBF bit in the MR register */
        USARTx->MR &= (uint32_t)~((uint32_t)USART_MR_MSBF);
    }
}

/**
  * @brief  Channel mode
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_ChannelMode: channel mode
  *         This parameter can be one of the following values:
  *                            USART_CHANNEL_MODE_NORMAL          - Normal mode
  *                            USART_CHANNEL_MODE_AUTOMATIC       - Automatic mode
  *                            USART_CHANNEL_MODE_LOCAL_LOOPBACK  - Local loopback mode
  *                            USART_CHANNEL_MODE_REMOTE_LOOPBACK - Remote loopbak mode
  * @retval None
  */
void USART_ChannelMode_Cfg(USART_TypeDef* USARTx, uint32_t USART_ChannelMode)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_CHANNEL_MODE(USART_ChannelMode));

    /* Clear the channel mode by clearing the CHMODE[15:14] bits in the MR register */
    USARTx->MR &= (uint32_t)~((uint32_t)USART_MR_CHMODE);

    /* Set the channel mode by setting the CHMODE[15:14] bits in the MR register    */
    USARTx->MR |= (uint32_t)((uint32_t)USART_ChannelMode);
}

/**
  * @brief  Number of stop bits
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_StopBits: number of stop bits,
  *         This parameter can be one of the following values:
  *                         USART_STOPBITS_1   - 1 stop bit
  *                         USART_STOPBITS_1_5 - 1.5 stop bit (SYNC = 0) or reserved (SYNC = 1)
  *                         USART_STOPBITS_2   - 2 stop bits
  * @retval None
  */
void USART_StopBit_Cfg(USART_TypeDef* USARTx, uint32_t USART_StopBits)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_STOPBITS(USART_StopBits));

    /* Clear the number of stop bits by clearing the NBSTOP[13:12] bits in the MR register */
    USARTx->MR &= (uint32_t)~((uint32_t)USART_MR_NBSTOP);

    /* Set the number of stop bits by setting the NBSTOP[13:12] bits in the MR register    */
    USARTx->MR |= (uint32_t)((uint32_t)USART_StopBits);
}

/**
  * @brief  Parity type
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_Parity: Parity type
  *         This parameter can be one of the following values:
  *                         USART_PARITY_EVEN      - Even parity
  *                         USART_PARITY_ODD       - Odd parity
  *                         USART_PARITY_SPACE     - Parity forced to 0 (space)
  *                         USART_PARITY_MARK      - Parity forced to 1 (mark)
  *                         USART_PARITY_NONE      - No parity
  *                         USART_PARITY_MULTIDROP - Multidrop mode
  * @retval None
  */
void USART_Parity_Cfg(USART_TypeDef* USARTx, uint32_t USART_Parity)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_PARITY(USART_Parity));

    /* Clear the parity type by clearing the PAR[11:9] bits in the MR register */
    USARTx->MR &= (uint32_t)~((uint32_t)USART_MR_PAR);

    /* Set the parity type by setting the PAR[11:9] bits in the MR register    */
    USARTx->MR |= (uint32_t)((uint32_t)USART_Parity);
}

/**
  * @brief  Synchronous mode select
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx synchronous mode select.
  *         This parameter can be:
  *           @arg ENABLE : USART operates in synchronous mode.
  *           @arg DISABLE: USART operated in asynchronous mode.
  * @retval None
  */
void USART_SYNCMode_Cfg(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the USART operates in sync mode by setting SYNC bit in the MR register */
        USARTx->MR |= USART_MR_SYNC;
    }
    else
    {
        /* Disable the USART operates in sync mode by clearing SYNC bit in the MR register */
        USARTx->MR &= (uint32_t)~((uint32_t)USART_MR_SYNC);
    }
}

/**
  * @brief  Character length
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_WordLength: character length
  *         This parameter can be one of the following values:
  *                         USART_CHAR_LENGTH_5BIT - character length is 5 bits
  *                         USART_CHAR_LENGTH_6BIT - character length is 6 bits
  *                         USART_CHAR_LENGTH_7BIT - character length is 7 bits
  *                         USART_CHAR_LENGTH_8BIT - character length is 8 bits
  * @retval None
  */
void USART_DataLength_Cfg(USART_TypeDef* USARTx, uint32_t USART_WordLength)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_CHAR_LENGTH(USART_WordLength));

    /* Clear the character length by clearing the CHRL[7:6] bits in the MR register */
    USARTx->MR &= (uint32_t)~((uint32_t)USART_MR_CHRL);

    /* Set the character length by setting the CHRL[7:6] bits in the MR register    */
    USARTx->MR |= (uint32_t)((uint32_t)USART_WordLength);
}

/**
  * @brief  Clock selection
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_CLKSelect: clock selection
  *         This parameter can be one of the following values:
  *                         USART_CLOCK_SELECT_MCK     - MCK
  *                         USART_CLOCK_SELECT_MCKDIV8 - MCK / 8
  *                         USART_CLOCK_SELECT_SCK     - SCK
  * @retval None
  */
void USART_CLKSelect_Cfg(USART_TypeDef* USARTx, uint32_t USART_CLKSelect)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_CLOCK_SELECT(USART_CLKSelect));

    /* Clear the clock select by clearing the USCLKS[5:4] bits in the MR register */
    USARTx->MR &= (uint32_t)~((uint32_t)USART_MR_USCLKS);

    /* Set the clock select by setting the USCLKS[5:4] bits in the MR register    */
    USARTx->MR |= (uint32_t)((uint32_t)USART_CLKSelect);
}

/**
  * @brief  USART mode of operation
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_OperationMode: USART mode of operation
  *         This parameter can be one of the following values:
  *                         USART_MODE_OPERATION_NORMAL      - Normal mode
  *                         USART_MODE_OPERATION_RS485       - RS485 mode
  *                         USART_MODE_OPERATION_MODEM       - Modem mode
  *                         USART_MODE_OPERATION_ISO7816_T_0 - ISO7816 protocol: T = 0
  *                         USART_MODE_OPERATION_ISO7816_T_1 - ISO7816 protocol: T = 1
  *                         USART_MODE_OPERATION_IrDA        - IrDA
  *                         USART_MODE_OPERATION_LIN_MASTER  - LIN master
  *                         USART_MODE_OPERATION_LIN_SLAVE   - LIN slave
  *                         USART_MODE_OPERATION_SPI_MASTER  - SPI master
  *                         USART_MODE_OPERATION_SPI_SLAVE   - SPI slave
  *
  * @retval None
  */
void USART_OperationMode_Cfg(USART_TypeDef* USARTx, uint32_t USART_OperationMode)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_MODE_OPERATION(USART_OperationMode));

    /* Clear the USART mode of operation by clearing the USART_MODE[3:0] bits in the MR register */
    USARTx->MR &= (uint32_t)~((uint32_t)USART_MR_USART_MODE);

    /* Set the USART mode of operation by setting the USART_MODE[3:0] bits in the MR register    */
    USARTx->MR |= (uint32_t)((uint32_t)USART_OperationMode);
}

/**
  * @}
  */

/** @defgroup USART fractional baudrate function
  * @brief    USART fractional part of baudrate function
  *
@verbatim
 ===============================================================================
                     ##### Fractional Baudrate Functions #####
 ===============================================================================
    [..] This subsection provides a function, which can configure fractional part
         of baudrate.

    [..]

    (#) The fractional part of baudrate API's :
        (++) USART_FracDivider_Cfg()
@endverbatim
  * @{
  */

/**
  * @brief  USART fractional part of BaudRate
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_BaudRate: user confige baudrate
  * @note   This function has to be called after calling USART_Init() function
  *         in order to have correct fractional part baudrate Divider value.
  * @retval None
  */
void USART_FracDivider_Cfg(USART_TypeDef* USARTx, uint32_t USART_BaudRate)
{
    double clock_divider = 0, frac_divider = 0, apbclock = 0;

    RCC_ClocksTypeDef RCC_ClocksStatus;

    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));

    if ((USARTx == USART1) || (USARTx == USART6))
    {
        assert_param(IS_USART_BAUDRATE(USART_BaudRate));
    }
    else if ((USARTx == USART2) || (USARTx == USART3))
    {
        assert_param(IS_USART_BAUDRATE_APB1(USART_BaudRate));
    }

    RCC_GetClocksFreq(&RCC_ClocksStatus);

    /* Get USARTx work clock*/
    if (USARTx == USART1)
    {
        apbclock = RCC_ClocksStatus.P2CLK_Frequency;
    }
    else if (USARTx == USART2)
    {
        apbclock = RCC_ClocksStatus.PCLK_Frequency ;
    }
    else if (USARTx == USART3)
    {
        apbclock = RCC_ClocksStatus.PCLK_Frequency ;
    }
    else if (USARTx == USART6)
    {
        apbclock = RCC_ClocksStatus.P2CLK_Frequency;
    }

    /* BaudRate not equal 0*/
    if (USART_BaudRate >  0)
    {
        /* Non ISO7816 Mode*/
        if (!((((USARTx->MR)&USART_MR_USART_MODE) == USART_MODE_OPERATION_ISO7816_T_0) ||
                (((USARTx->MR)&USART_MR_USART_MODE) == USART_MODE_OPERATION_ISO7816_T_1)))
        {
            /* Async mode*/
            if (((USARTx->MR)&USART_MR_SYNC) == USART_SYNC_MODE_ASYNC)
            {
                /* x16 Oversample*/
                if (((USARTx->MR)&USART_MR_OVER) == USART_OVERSAMPLING_16)
                {
                    clock_divider = (uint32_t)(((apbclock) / ((USART_BaudRate) * 16)));
                    frac_divider  = (uint32_t)(((apbclock) / ((USART_BaudRate) * 16) - clock_divider) * 8);
                }
                /* x8  Oversample*/
                if (((USARTx->MR)&USART_MR_OVER) == USART_OVERSAMPLING_8)
                {
                    clock_divider = (uint32_t)(((apbclock) / ((USART_BaudRate) * 8)));
                    frac_divider  = (uint32_t)(((apbclock) / ((USART_BaudRate) * 8) - clock_divider) * 8);
                }
            }
        }
    }

    /* Clear the USART fractional part by clearing the FP[18:16] bits in the BRGR register */
    USARTx->BRGR &= (uint32_t)~((uint32_t)USART_BRGR_FP);

    /* Set the USART fractional part by setting the FP[18:16] bits in the BRGR register    */
    USARTx->BRGR |= (((uint32_t)frac_divider) << 16U);
}

/**
  * @}
  */

/** @defgroup USART BREAK command functions
  * @brief    None
  *
@verbatim
 ===============================================================================
                        ##### Break Command Functions #####
 ===============================================================================
    [..] This subsection provides a set of BREAK command functions.

    [..]

    (#) The stop break command API's :
        (++) USART_STPBRK_Cmd()

    (#) The start break command API's :
        (++) USART_STTBRK_Cmd()
@endverbatim
  * @{
  */

/**
  * @brief  Stop break.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx stop break.
  *         This parameter can be:
  *           @arg ENABLE : Stops transmission of break after a minimum of one character length and
  *                         transmits a high level during 12-bit periods.
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_STPBRK_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Stops transmission of break after a minimum of one character by setting STPBRK
           bit in the CR register */
        USARTx->CR |= USART_CR_STPBRK;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_STPBRK);
    }
}

/**
  * @brief  Start break.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx start break.
  *         This parameter can be:
  *           @arg ENABLE : Starts transmission of break after the character present in US_THR and
  *                         the transmit shift register have been transmitted. No effect if a break
  *                         is already being transmitted.
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_STTBRK_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Starts transmission of the break after the characters present in US_THR and the transmit
           shift register have been transmitted by setting STTBRK bit in the CR register */
        USARTx->CR |= USART_CR_STTBRK;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_STTBRK);
    }
}

/**
  * @}
  */

/** @defgroup USART receiver time-out and transmitter timeguard functions
  * @brief    Receiver time-out cfg and cmd functions.
  *           Transmitter timeguard cfg function.
  *
@verbatim
 ===============================================================================
        ##### Receiver Time-out And Transmitter Timeguard Functions #####
 ===============================================================================
    [..] This subsection provides a set of receiver time-out and transmitter
         timeguard functions.

    [..]

    (#) The receiver time-out cfg API's :
        (++) USART_Receiver_TimeOut_Cfg()

    (#) The receiver time-out cmd API's :
        (++) USART_RETTO_After_Timeout_Cmd()
        (++) USART_STTTO_After_Timeout_Cmd()

    (#) The transmitter timeguard cfg API's :
        (++) USART_Transmitter_TimeGuard_Cfg()
@endverbatim
  * @{
  */

/**
  * @brief  Receiver time-out value
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_ReceiverTimeOut: Time-out value
  *                                0         : The receiver time-out is disabled.
  *                                1 - 65535 : The receiver time-out is enabled and time-out
  *                                            delay is TO * bit period.
  *                                1 - 131071: The receiver time-out is enabled and time-out
  *                                            delay is TO * bit period.
  * @note   This function has to be called before calling USART_Init() function
  *         in order to have correct receiver time-out value.
  * @retval None
  */
void USART_Receiver_TimeOut_Cfg(USART_TypeDef* USARTx, uint32_t USART_ReceiverTimeOut)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_TIMEOUT(USART_ReceiverTimeOut));

    /* Clear the time-out value of receiver by clearing the TO[16:0] bits in the RTOR register */
    USARTx->RTOR &= (uint32_t)~((uint32_t)USART_RTOR_TO);

    /* Set the time-out value of receiver setting the TO[16:0] bits in the RTOR register       */
    USARTx->RTOR |= (uint32_t)((uint32_t)USART_ReceiverTimeOut);
}

/**
  * @brief  Rearm Time-out.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx rearm Time-out.
  *         This parameter can be:
  *           @arg ENABLE : Restart Time-out
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_RETTO_After_Timeout_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Restart Time-out by setting RETTO bit in the CR register */
        USARTx->CR |= USART_CR_RETTO;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_RETTO);
    }
}

/**
  * @brief  Start time-out.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx start time-out.
  *         This parameter can be:
  *           @arg ENABLE : Starts waiting for a character before clocking the time-out counter.
  *                         Resets the status bit TIMEOUT in US_CSR.
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_STTTO_After_Timeout_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Starts waiting for a character before clocking the time-out counter by setting
           STTTO bit in the CR register */
        USARTx->CR |= USART_CR_STTTO;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_STTTO);
    }
}

/**
  * @brief  Transmitter timeguard value
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_TransmitterTimeGuard: timeguard value
  *                                0      : The transmitter timeguard value is disabled.
  *                                1 - 255: The transmitter timeguard is enabled and the
  *                                         timeguard delay is TG * bit period.
  * @note   This function has to be called before calling USART_Init() function
  *         in order to have correct transmitter timeguard value.
  * @retval None
  */
void USART_Transmitter_TimeGuard_Cfg(USART_TypeDef* USARTx, uint32_t USART_TransmitterTimeGuard)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_TIMGUARD(USART_TransmitterTimeGuard));

    /* Clear the timeguard value of transmitter by clearing the TG[7:0] bits in the TTGR register */
    USARTx->TTGR &= (uint32_t)~((uint32_t)USART_TTGR_TG);

    /* Set the timeguard value of transmitter setting the TG[7:0] bits in the TTGR register       */
    USARTx->TTGR |= (uint32_t)((uint32_t)USART_TransmitterTimeGuard);
}

/**
  * @}
  */

/** @defgroup USART multidrop mode cmd function
  * @brief    Multidrop mode command function.
  *
@verbatim
 ===============================================================================
                   ##### Multidrop Mode Command Function #####
 ===============================================================================
    [..] This subsection provides the multidrop mode command function.

    [..]

    (#) The multidrop mode command API's :
        (++) USART_SENDAInMultidropMode_Cmd()

@endverbatim
  * @{
  */

/**
  * @brief  Send address.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx send address.
  *         This parameter can be:
  *           @arg ENABLE : In multidrop mode only, the next character written to
  *                         the US_THR is sent with address bit set.
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_SENDAInMultidropMode_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* In multidrop mode only, the next character writted to the US_THR is sent
           with the address bit set by setting SENDA bit in the CR register */
        USARTx->CR |= USART_CR_SENDA;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_SENDA);
    }
}

/**
  * @}
  */

/** @defgroup USART SPI mode cmd, cfg, and read functions
  * @brief    USART SPI mode mode command, configuration and read functions
  *
@verbatim
 ===============================================================================
                            ##### SPI Mode Functions #####
 ===============================================================================
    [..] This subsection provides a set of SPI mode functions.

    [..]

    (#) The SPI mode cmd API's :
        (++) USART_RCS_Cmd()
        (++) USART_FCS_Cmd()

    (#) The SPI mode cfg API's :
        (++) USART_WRDBT_Cfg()
        (++) USART_CLKPolarity_Cfg()
        (++) USART_CLKPhase_Cfg()

    (#) The SPI mode read API's :
        (++) None
@endverbatim
  * @{
  */

/**
  * @brief  Release SPI chip select
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx release SPI chip select.
  *         This parameter can be:
  *           @arg ENABLE : Releases the slave select lin NSS (RTS pin).
  *                         Applicable if USARTx operates in SPI Master.
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_RCS_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Release the slave slect line (RTS pin) by setting RCS bit in
           the CR(SPI_MODE) register */
        USARTx->CR |= USART_CR_RCS;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_RCS);
    }
}

/**
  * @brief  Force SPI chip select
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx force SPI chip select.
  *         This parameter can be:
  *           @arg ENABLE : Forces the slave select lin NSS (RTS pin) to 0,
  *                         even if USART is no transmitting, in order to
  *                         address SPI slave devices supporting the CSAAT
  *                         mode (Chip Select Active After Transfer).
  *                         Applicable if USARTx operates in SPI Master.
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_FCS_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Force the slave slect line (RTS pin) by setting FCS bit in the
           CR(SPI_MODE) register */
        USARTx->CR |= USART_CR_FCS;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_FCS);
    }
}

/**
  * @brief  Wait read data before transfre
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx wait read data before transfer.
  *         This parameter can be:
  *           @arg ENABLE : The character transmission starts when a character
  *                         is written and only if RXRDY flag is cleared (Receiver
  *                         Holding register has been read).
  *           @arg DISABLE: The character transmission starts as soon as a character
  *                         is written into US_THR register (assuming TXRDY was set).
  * @retval None
  */
void USART_WRDBT_Cfg(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the transmission after read data by setting WRDBT bit in the MR register */
        USARTx->MR |= USART_MR_WRDBT;
    }
    else
    {
        /* Disable the transmission after read data by clearing WRDBT bit in the MR register */
        USARTx->MR &= (uint32_t)~((uint32_t)USART_MR_WRDBT);
    }
}

/**
  * @brief  SPI clock polarity
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx spi operates clock polarity,
  *         applicable if USART operates in SPI mode (slave or master).
  *         This parameter can be:
  *           @arg ENABLE : The inactive status value of SPCK is logic level one.
  *           @arg DISABLE: The inactive status value of SPCK is logic level zero.
  * @retval None
  */
void USART_CLKPolarity_Cfg(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the spi clock polarity by setting CPOL bit in the MR register */
        USARTx->MR |= USART_MR_CPOL;
    }
    else
    {
        /* Disable the spi clock polarity by clearing CPOL bit in the MR register */
        USARTx->MR &= (uint32_t)~((uint32_t)USART_MR_CPOL);
    }
}

/**
  * @brief  SPI clock phase
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx spi operates clock phase,
  *         applicable if USART operates in SPI mode (slave or master).
  *         This parameter can be:
  *           @arg ENABLE : Data is captured on the leading edge of SPCK and
  *                         changed on the following edge of SPCK.
  *           @arg DISABLE: Data is changeded on the leading edge of SPCK and
  *                         captured on the following edge of SPCK.
  * @retval None
  */
void USART_CLKPhase_Cfg(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the spi clock phase by setting CPHA bit in the MR register */
        USARTx->MR |= USART_MR_CPHA;
    }
    else
    {
        /* Disable the spi clock phase by clearing CPHA bit in the MR register */
        USARTx->MR &= (uint32_t)~((uint32_t)USART_MR_CPHA);
    }
}

/**
  * @}
  */

/** @defgroup USART ISO7816 mode cmd, cfg, and read functions
  * @brief    USART ISO7816 mode mode command, configuration and read functions
  *
@verbatim
 ===============================================================================
                             ##### ISO7816 Mode Functions #####
 ===============================================================================
    [..] This subsection provides a set of ISO7816 mode functions.

    [..]

    (#) The ISO7816 mode cmd API's :
        (++) USART_RSTNACK_Cmd()
        (++) USART_RSTIT_Cmd()

    (#) The ISO7816 mode cfg API's :
        (++) USART_MaxIteration_Cfg()
        (++) USART_DsNack_Cfg()
        (++) USART_INack_Cfg()
        (++) USART_FiDiRatio_Cfg()

    (#) The ISO7816 mode read API's :
        (++) USART_GetNumberOfError()
@endverbatim
  * @{
  */

/**
  * @brief  Reset non acknowledge.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx reset non acknowledge.
  *         This parameter can be:
  *           @arg ENABLE : Reset NACK in US_CSR
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_RSTNACK_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Reset the NACK in US_CSR by setting RSTNACK bit in the CR register */
        USARTx->CR |= USART_CR_RSTNACK;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_RSTNACK);
    }
}

/**
  * @brief  Reset iterations.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx reset iterations.
  *         This parameter can be:
  *           @arg ENABLE : Reset ITERATION in US_CSR (No effect if the ISO7816 is not enabled).
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_RSTIT_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Reset the ITERATION in US_CSR by setting RSTIT bit in the CR register */
        USARTx->CR |= USART_CR_RSTIT;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_RSTIT);
    }
}

/**
  * @brief  Maximum number of automatic iteration
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_MAXIteration: Defines the maximum number of iterations in mode ISO7816,
  *         protocol T = 0
  *         This parameter can be one of the following values:
  *                     USART_ISO7816_T0_MAX_ITERATION_0 - USART max_iteration with 0 times
  *                     USART_ISO7816_T0_MAX_ITERATION_1 - USART max_iteration with 1 times
  *                     USART_ISO7816_T0_MAX_ITERATION_2 - USART max_iteration with 2 times
  *                     USART_ISO7816_T0_MAX_ITERATION_3 - USART max_iteration with 4 times
  *                     USART_ISO7816_T0_MAX_ITERATION_5 - USART max_iteration with 5 times
  *                     USART_ISO7816_T0_MAX_ITERATION_6 - USART max_iteration with 6 times
  *                     USART_ISO7816_T0_MAX_ITERATION_7 - USART max_iteration with 7 times
  * @retval None
  */
void USART_MaxIteration_Cfg(USART_TypeDef* USARTx, uint32_t USART_MAXIteration)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_ISO7816_T0_MAX_ITERATION(USART_MAXIteration));

    /* Clear the maximum number of automatic iteration value by clearing the MAX_ITERATION[26:24]
       bits in the MR register */
    USARTx->MR &= (uint32_t)~((uint32_t)USART_MR_MAX_ITERATION);

    /* Set the maximum number of automatic iteration value by setting the MAX_ITERATION[26:24]
       bits in the MR register */
    USARTx->MR |= (uint32_t)((uint32_t)USART_MAXIteration);
}

/**
  * @brief  Disable Successive NACK
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx disable successive NACK.
  *         This parameter can be:
  *           @arg ENABLE : Successive parity errors are counted up to the value
  *                         specificed in the MAX_ITERATION field.
  *           @arg DISABLE: NACK is sent on the ISO line as soon as a parity error
  *                         occurs in the received character (unless INACK is set).
  * @retval None
  */
void USART_DsNack_Cfg(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the disable successive NACK function by setting DSNACK bit in the MR register */
        USARTx->MR |= USART_MR_DSNACK;
    }
    else
    {
        /* Disable the disable successive NACK function by clearing DSNACK bit in the MR register */
        USARTx->MR &= (uint32_t)~((uint32_t)USART_MR_DSNACK);
    }
}

/**
  * @brief  Inhibit non acknowledge
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx inhibit non acknowledge.
  *         This parameter can be:
  *           @arg ENABLE : The NACK is not generated.
  *           @arg DISABLE: The NACK is generated.
  * @retval None
  */
void USART_INack_Cfg(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the inhibit non acknowledge function by setting INACK bit in the MR register */
        USARTx->MR |= USART_MR_INACK;
    }
    else
    {
        /* Disable the inhibit non acknowledge function by clearing INACK bit in the MR register */
        USARTx->MR &= (uint32_t)~((uint32_t)USART_MR_INACK);
    }
}

/**
  * @brief  Fi over Di ratio value
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_FiDiRatio: user config Fi_Di_Ratio
  * @param  USART_BaudRate: user confige baudrate
  * @note   This function has to be called when user need to change Fi_Di_Ratio
  *         after USART_Init() function, CD fields of BRGR change as bellow:
  *         CD = MCK / (BaudRate * FiDiRatio).
  * @retval None
  */
void USART_FiDiRatio_Cfg(USART_TypeDef* USARTx, uint32_t USART_FiDiRatio, uint32_t USART_BaudRate)
{
    uint32_t clock_divider = 0, apbclock = 0;
    RCC_ClocksTypeDef RCC_ClocksStatus;

    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));

    if ((USARTx == USART1) || (USARTx == USART6))
    {
        assert_param(IS_USART_BAUDRATE(USART_BaudRate));
    }
    else if ((USARTx == USART2) || (USARTx == USART3))
    {
        assert_param(IS_USART_BAUDRATE_APB1(USART_BaudRate));
    }

    assert_param(IS_USART_FIDIRATIO(USART_FiDiRatio));

    RCC_GetClocksFreq(&RCC_ClocksStatus);

    /* Get USARTx work clock*/
    if (USARTx == USART1)
    {
        apbclock = RCC_ClocksStatus.P2CLK_Frequency;
    }
    else if (USARTx == USART2)
    {
        apbclock = RCC_ClocksStatus.PCLK_Frequency ;
    }
    else if (USARTx == USART3)
    {
        apbclock = RCC_ClocksStatus.PCLK_Frequency ;
    }
    else if (USARTx == USART6)
    {
        apbclock = RCC_ClocksStatus.P2CLK_Frequency;
    }

    /* BaudRate not equal 0*/
    if (USART_BaudRate >  0)
    {
        /* ISO7816 Mode*/
        if ((((USARTx->MR)&USART_MR_USART_MODE) == USART_MODE_OPERATION_ISO7816_T_0) ||
                (((USARTx->MR)&USART_MR_USART_MODE) == USART_MODE_OPERATION_ISO7816_T_1))
        {
            clock_divider = (uint32_t)(((apbclock) / ((USART_BaudRate) * USART_FiDiRatio)));
        }
    }

    /* Clear the USART clock divider by clearing the CD[15:0] bits in the BRGR register         */
    USARTx->BRGR &= (uint32_t)~((uint32_t)USART_BRGR_CD);

    /* Set the USART clock divider by setting the CD[15:0] bits in the BRGR register            */
    USARTx->BRGR |= ((uint32_t)clock_divider);

    /* Clear the USART Fi_Di_Ration by clearing the FI_DI_RATIO[15:0] bits in the FIDI register */
    USARTx->FIDI &= (uint32_t)~((uint32_t)USART_FIDI_FI_DI_RATIO);

    /* Set the USART Fi_Di_Ration by setting the FI_DI_RATIO[15:0] bits in the FIDI register    */
    USARTx->FIDI |= ((uint32_t)USART_FiDiRatio);
}

/**
  * @brief  Returns the number of error by the USARTx peripheral.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @note   Total number of errors that occurred during an ISO7816 transfer.
  *         This register automatically clears when read.
  * @retval The number of error.
  */
uint32_t USART_GetNumberOfError(USART_TypeDef* USARTx)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));

    /* Return the number of errors that occured during an ISO7816 transfer */
    return (uint32_t)((USARTx->NER));
}

/**
  * @}
  */

/** @defgroup USART IrDA mode cfg functions
  * @brief    USART IrDA mode mode configuration function
  *
@verbatim
 ===============================================================================
                        ##### IrDA Mode Functions #####
 ===============================================================================
    [..] This subsection provides a IrDA mode function.

    [..]

    (#) The IrDA mode cfg API's :
        (++) USART_IrDAFilter_Cfg()

@endverbatim
  * @{
  */

/**
  * @brief  IrDA Filter
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_IrDAFilter: The IRDA_FILTER value must be defined to meet the
  *         following criteria:
  *                             tMCK * (IRDA_FILTER + 3) < 1.41us
  * @retval None
  */
void USART_IrDAFilter_Cfg(USART_TypeDef* USARTx, uint32_t USART_IrDAFilter)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_IF(USART_IrDAFilter));

    /* Clear the IrDA filter value by clearing the IRDA_FILTER[7:0] bits in the IF register */
    USARTx->IF &= (uint32_t)~((uint32_t)USART_IF_IRDA_FILTER);

    /* Set the IrDA filter value by setting the IRDA_FILTER[7:0] bits in the IF register */
    USARTx->IF |= (uint32_t)((uint32_t)USART_IrDAFilter);
}

/**
  * @}
  */

/** @defgroup USART LIN mode cmd, cfg, and read functions
  * @brief    USART LIN mode mode command, configuration and read functions
  *
@verbatim
 ===============================================================================
                             ##### LIN Mode Functions #####
 ===============================================================================
    [..] This subsection provides a set of LIN mode functions.

    [..]

    (#) The LIN mode cmd API's :
        (++) USART_LINWKUP_Cmd()
        (++) USART_LINABT_Cmd()

    (#) The LIN mode cfg API's :
        (++) USART_Write_LINIR_In_LIN_Master()
        (++) USART_SYNCDisable_Cfg()
        (++) USART_PDCMode_Cfg()
        (++) USART_DataLengthControl_Cfg()
        (++) USART_WkupType_Cfg()
        (++) USART_FrameSlotDisable_Cfg()
        (++) USART_DataLengthMode_Cfg()
        (++) USART_CheckSumType_Cfg()
        (++) USART_CheckSumDisable_Cfg()
        (++) USART_ParityDisable_Cfg()
        (++) USART_NodeAction_Cfg()

    (#) The LIN mode read API's :
        (++) USART_Read_LINIR_In_LIN_Slave()
        (++) USART_LINBaudRate()
@endverbatim
  * @{
  */

/**
  * @brief  Send LIN Wakeup Signal.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx send LIN wakeup signal.
  *         This parameter can be:
  *           @arg ENABLE : Sends a wakeup signal on LIN bus
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_LINWKUP_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Sends a wakeup signal on LIN bus by setting LINWKUP bit in the CR register */
        USARTx->CR |= USART_CR_LINWKUP;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_LINWKUP);
    }
}

/**
  * @brief  Abort LIN Transmission.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx abort LIN transmission.
  *         This parameter can be:
  *           @arg ENABLE : Abort LIN transmission
  *           @arg DISABLE: No effect
  * @retval None
  */
void USART_LINABT_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Abort the LIN transmission by setting LINABT bit in the CR register */
        USARTx->CR |= USART_CR_LINABT;
    }
    else
    {
        /* No effect */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_LINABT);
    }
}

/**
  * @brief  Write identifier character in LIN master mode
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_LINIR_Data: if USART_OperationMode = 0xA (Master node configure),
  *                           USART_LINIR_Data is read-write and its value is the
  *                           identifier character to be transmitted.
  * @note   This function has to be called after calling USART_Init() function
  *         in order to have correct identifer value in LIN master mode.
  * @retval None
  */
void USART_Write_LINIR_In_LIN_Master(USART_TypeDef* USARTx, uint32_t USART_LINIR_Data)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_LINIR_WR(USART_LINIR_Data));

    /* Clear the identifier value to be transmitted in LIN master node by clearing
       the IDCHR[7:0] bits in the LINIR register */
    USARTx->LINIR &= (uint32_t)~((uint32_t)USART_LINIR_IDCHR);

    /* Set the identifier value to be transmitted in LIN master node by setting
       the IDCHR[7:0] bits in the LINIR register */
    USARTx->LINIR |= (uint32_t)((uint32_t)USART_LINIR_Data);
}

/**
  * @brief  Synchronization disable in LIN mode
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx LIN synchronization disable,
  *         applicable if USART operates in LIN mode.
  *         This parameter can be:
  *           @arg ENABLE : The synchronization procedure is not performed in LIN
  *                         slave node configure.
  *           @arg DISABLE: The synchronization procedure is performed in LIN
  *                         slave node configure.
  * @retval None
  */
void USART_SYNCDisable_Cfg(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the synchronization procedure's disable by setting SYNCDIS bit in the LINMR register */
        USARTx->LINMR |= USART_LINMR_SYNCDIS;
    }
    else
    {
        /* Disable the synchronization procedure's disable by clearing SYNCDIS bit in the LINMR register */
        USARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_SYNCDIS);
    }
}

/**
  * @brief  DMA mode in LIN mode
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx LIN DMA mode,
  *         applicable if USART operates in LIN mode.
  *         This parameter can be:
  *           @arg ENABLE : The LIN mode register US_LINMR (excepting that flag)
  *                         is written by the DMA.
  *           @arg DISABLE: The LIN mode register US_LINMR is not written by the DMA.
  * @retval None
  */
void USART_PDCMode_Cfg(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the DMA written of LINMR by setting PDCM bit in the LINMR register */
        USARTx->LINMR |= USART_LINMR_PDCM;
    }
    else
    {
        /* Disable the DMA written of LINMR by clearing PDCM bit in the LINMR register */
        USARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_PDCM);
    }
}

/**
  * @brief  Data length control in LIN mode
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_DataLengthControl: (0 - 255) Defines the response data length
  *                                  if USART_DataLengthMode = 0, in that case
  *                                  the response data length is equal to
  *                                  USART_DataLengthControl + 1 bytes;
  * @retval None
  */
void USART_DataLengthControl_Cfg(USART_TypeDef* USARTx, uint32_t USART_DataLengthControl)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_DLC(USART_DataLengthControl));

    /* Clear the response data length value of LIN mode (USART_DataLengthMode = 0)
       by clearing the DLC[15:8] bits in the LINMR register */
    USARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_DLC);

    /* Set the response data length value of LIN mode (USART_DataLengthMode = 0)
       by setting the DLC[15:8] bits in the LINMR register */
    USARTx->LINMR |= (uint32_t)((uint32_t)USART_DataLengthControl << 8U);
}

/**
  * @brief  Wakeup signal type in LIN mode
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx LIN wakeup signal type.
  *         This parameter can be:
  *           @arg ENABLE : Setting the bit LINWKUP in the control register send
  *                         a LIN 1.3 wakeup signal.
  *           @arg DISABLE: Setting the bit LINWKUP in the control register send
  *                         a LIN 2.0 wakeup signal.
  * @retval None
  */
void USART_WkupType_Cfg(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the LIN 1.3 wakeup signal as the wakeup type to send by setting WKUPTYP
           bit in the LINMR register */
        USARTx->LINMR |= USART_LINMR_WKUPTYP;
    }
    else
    {
        /* Disable the LIN 1.3 wakeup signal as the wakeup type to send by clearing WKUPTYP
           bit in the LINMR register */
        USARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_WKUPTYP);
    }
}

/**
  * @brief  Frame slot mode disable in LIN mode
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx LIN frame slot mode disable.
  *         This parameter can be:
  *           @arg ENABLE : The frame slot mode is disabled.
  *           @arg DISABLE: The frame slot mode is enabled.
  * @retval None
  */
void USART_FrameSlotDisable_Cfg(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the frame slot mode's disable by setting FSDIS bit in the LINMR register */
        USARTx->LINMR |= USART_LINMR_FSDIS;
    }
    else
    {
        /* Disable the frame slot mode's disable by clearing FSDIS bit in the LINMR register */
        USARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_FSDIS);
    }
}

/**
  * @brief  Data length mode in LIN mode
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx LIN data length mode.
  *         This parameter can be:
  *           @arg ENABLE : The response data length is defined by the bits 5
  *                         and 6 of the identifier (IDCHR in US_LINIR).
  *           @arg DISABLE: The response data length is defined by the field
  *                         DLC of US_LINMR register.
  * @retval None
  */
void USART_DataLengthMode_Cfg(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the response data length is defined by the bits 5 and 6 of the identifier
           (IDCHR in US_LINIR) by setting DLM bit in the LINMR register */
        USARTx->LINMR |= USART_LINMR_DLM;
    }
    else
    {
        /* Disable the response data length is defined by the bits 5 and 6 of the identifier
           (IDCHR in US_LINIR) by clearing DLM bit in the LINMR register */
        USARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_DLM);
    }
}

/**
  * @brief  Checksum type in LIN mode
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx LIN checksum type.
  *         This parameter can be:
  *           @arg ENABLE : LIN 1.3 "Classic" checksum.
  *           @arg DISABLE: LIN 2.0 "Enhanced" checksum.
  * @retval None
  */
void USART_CheckSumType_Cfg(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the LIN 1.3 "Classic" checksum type by setting CHKTYP bit in the LINMR register */
        USARTx->LINMR |= USART_LINMR_CHKTYP;
    }
    else
    {
        /* Disable the LIN 1.3 "Classic" checksum type by clearing CHKTYP bit in the LINMR register */
        USARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_CHKTYP);
    }
}

/**
  * @brief  Checksum disable in LIN mode
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx LIN checksum disable.
  *         This parameter can be:
  *           @arg ENABLE : Whatever the node configuration is, the checksum is
  *                         not computed/sent and it is not checked.
  *           @arg DISABLE: In Master node configuration, the cheksum is computed
  *                         and sent automatically. In Slave node configure, the
  *                         checksum is checked automatically.
  * @retval None
  */
void USART_CheckSumDisable_Cfg(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the checksum's disable by setting CHKDIS bit in the LINMR register */
        USARTx->LINMR |= USART_LINMR_CHKDIS;
    }
    else
    {
        /* Disable the checksum's disable by clearing CHKDIS bit in the LINMR register */
        USARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_CHKDIS);
    }
}

/**
  * @brief  Parity disable in LIN mode
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx LIN parity disable.
  *         This parameter can be:
  *           @arg ENABLE : Whatever the node configuration is, the identifier
  *                         parity is not computed/sent and it is not checked.
  *           @arg DISABLE: In Master node configuration, the identifier parity
  *                         is computed and sent automatically. In Master node
  *                         and Slave node configuration, the parity is checked
  *                         automatically.
  * @retval None
  */
void USART_ParityDisable_Cfg(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the identifier parity's disable by setting PARDIS bit in the LINMR register */
        USARTx->LINMR |= USART_LINMR_PARDIS;
    }
    else
    {
        /* Disable the identifier parity's disable by clearing PARDIS bit in the LINMR register */
        USARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_PARDIS);
    }
}

/**
  * @brief  LIN node action
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_NodeAction: LIN node action
  *         This parameter can be one of the following values:
  *                           USART_NODE_ACTIVE_PUBLISH   - PUBLISH  ; The USART transmits the response.
  *                           USART_NODE_ACTIVE_SUBSCRIBE - SUBSCRIBE; The USART receives the response.
  *                           USART_NODE_ACTIVE_IGNORE    - IGNORE   ; The USART does not transmits and
  *                                                                    does not receives the response.
  * @retval None
  */
void USART_NodeAction_Cfg(USART_TypeDef* USARTx, uint32_t USART_NodeAction)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_NODE_ACTIVE(USART_NodeAction));

    /* Clear the LIN node action by clearing the NACT[1:0] bits in the LINMR register */
    USARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_NACT);

    /* Set the LIN node action by setting the NACT[1:0] bits in the LINMR register */
    USARTx->LINMR |= (uint32_t)((uint32_t)USART_NodeAction);
}

/**
  * @brief  Returns the identifier character by the USARTx peripheral.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @note   If USART_OperationMode = 0xB (Slave node configuration), IDCHR[7:0]
  *         in US_LINIR is read-only and its value is the last identifier character
  *         that has been received.
  * @retval The last identifier character.
  */
uint32_t USART_Read_LINIR_In_LIN_Slave(USART_TypeDef* USARTx)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));

    /* Return the last identifier character if operation in slave node configuration*/
    return (uint32_t)((USARTx->LINIR));
}

/**
  * @brief  Returns the baud rate value after the synchronization process completion
  *         by the USARTx peripheral.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @note   The return value [18:16] bits is LINFP[18:16], which means fractional part
  *         after synchronization.
  * @note   The return value [15: 0] bits is LINCD[15: 0], which means clock driver
  *         after synchronization.
  * @retval The baud rate value after the synchronization process completion.
  */
uint32_t USART_LINBaudRate(USART_TypeDef* USARTx)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));

    /* Return the baud rate value after the synchronization process completion */
    return (uint32_t)((USARTx->LINBRR));
}

/**
  * @}
  */

/** @defgroup USART write protection register functions
  * @brief    USART write protection register mode functions
  *
@verbatim
 ===============================================================================
               ##### Write Protection Register Mode Functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to operate in write
         protection register mode.

    [..] The protected register are:
         (++) US_MR, which offset address is 0x0004
         (++) US_BRGR, which offset address is 0x0020
         (++) US_RTOR, which offset address is 0x0024
         (++) US_TTGR, which offset address is 0x0028
         (++) US_FIDI, which offset address is 0x0040
         (++) US_IF, which offset address is 0x004C

    [..]

    (#) The USART write protection register mode configure API's :
        (++) USART_WriteProtectionRegisterConfig()

    (#) The USART write protection violation status (WPVS bit of US_WPSR) API's :
        (++) USART_GetWriteProtectionRegisterStatus()

    (#) The USART get write protection violation source API's :
        (++) USART_GetWriteProtectionRegisterSource()

    (#) The USART clear write protection register US_WPSR fields API's :
        (++) USART_ClearWPSRField()
@endverbatim
  * @{
  */

/**
  * @brief  Write protect enable
  * @param  USARTx_WP: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx write protect enable.
  *         This parameter can be:
  *           @arg ENABLE : Enables the write protect if WPKEY corresponds to 0x555341.
  *           @arg DISABLE: Disables the write protect if WPKEY corresponds to 0x555341.
  * @retval None
  */
void USART_WriteProtectionRegisterConfig(USART_WP_TypeDef* USARTx_WP, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH_WP(USARTx_WP));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enables the write protect if WPKEY corresponds to 0x555341 by setting WPEN bit in the WPMR register */
        USARTx_WP->WPMR  = (USART_WPMR_WPEN | (0x555341 << 8U));
    }
    else
    {
        /* Disables the write protect if WPKEY corresponds to 0x555341 by clearing WPEN bit in the WPMR register */
        USARTx_WP->WPMR  = 0x55534100;
    }
}

/**
  * @brief  Checks whether the USART write protect violation is set or not.
  * @param  USARTx_WP: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @retval The new state of write protect violation status.
  */
FlagStatus USART_GetWriteProtectionRegisterStatus(USART_WP_TypeDef* USARTx_WP)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH_WP(USARTx_WP));

    if ((USARTx_WP->WPSR & USART_WPSR_WPVS) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
  * @brief  Returns the write protect violation source by the USARTx_WP peripheral.
  * @param  USARTx_WP: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @note   When WPVS bit of WPSR register is active, this field indicates the
  *         write-protected register (through address offset or code) in which a
  *         write access has been attempted.
  * @retval The write protect violation source.
  */
uint32_t USART_GetWriteProtectionRegisterSource(USART_WP_TypeDef* USARTx_WP)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH_WP(USARTx_WP));

    /* Return the write protect violation source, which is WPVSRC[23:8] bits of US_WPSR */
    return (uint32_t)((USARTx_WP->WPSR) >> 8U);
}

/**
  * @brief  Reading US_WPSR automatically clears all fields.
  * @param  USARTx_WP: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @retval US_WPSR value.
  */
uint32_t USART_ClearWPSRField(USART_WP_TypeDef* USARTx_WP)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH_WP(USARTx_WP));

    /* Reading US_WPSR automatically clears all fields */
    return (uint32_t)(USARTx_WP->WPSR);
}

/**
  * @}
  */

/** @defgroup USART Transfers functions
  * @brief    USART Transmit and Receive functions
  *
@verbatim
 ===============================================================================
                      ##### Data Transfers Functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the USART data transfers.

    [..]

    (#) The USART data transmit API's :
        (++) USART_Transmit()

    (#) The USART data receive API's :
        (++) USART_Receive()
@endverbatim
  * @{
  */

/**
  * @brief  Transmits single data through the USARTx peripheral.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  Data: the data to transmit.
  * @retval None
  */
void USART_Transmit(USART_TypeDef* USARTx, uint16_t Data)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_DATA(Data));

    /* Transmit Data */
    USARTx->THR = (Data & (uint16_t)0x01FF);
}

/**
  * @brief  Returns the most recent received data by the USARTx peripheral.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @retval The received data.
  */
uint16_t USART_Receive(USART_TypeDef* USARTx)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));

    /* Received Data */
    return (uint16_t)(USARTx->RHR & (uint16_t)0x01FF);
}

/**
  * @}
  */

/** @defgroup USART DMA Transfers functions
  * @brief    USART DMA Transmit and Receive enable functions
  *
@verbatim
 ===============================================================================
                   ##### DMA Transfer Management Functions #####
 ===============================================================================
    [..] This subsection provides a set of functions about DMA Tx/Rx enable functions.

    [..]

    (#) The USART DMA enable transmitter API's :
        (++) USART_DMATxEnable_Cmd()

    (#) The USART DMA enable receiver API's :
        (++) USART_DMARxEnable_Cmd()
@endverbatim
  * @{
  */

/**
  * @brief  DMA enable transmitter
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx DMA enable transmitter.
  *         This parameter can be:
  *           @arg ENABLE : DMA mode is enable for transmission.
  *           @arg DISABLE: DMA mode is disable for transmission.
  * @retval None
  */
void USART_DMATxEnable_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the transmission function of DMA mode by setting DMAT bit in the CR register */
        USARTx->CR |= USART_CR_DMAT_EN;
    }
    else
    {
        /* Disable the transmission function of DMA mode by clearing DMAT bit in the CR register */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_DMAT_EN);
    }
}

/**
  * @brief  DMA enable receiver
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx DMA enable receiver.
  *         This parameter can be:
  *           @arg ENABLE : DMA mode is enable for reception.
  *           @arg DISABLE: DMA mode is disable for reception.
  * @retval None
  */
void USART_DMARxEnable_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the reception function of DMA mode by setting DMAR bit in the CR register */
        USARTx->CR |= USART_CR_DMAR_EN;
    }
    else
    {
        /* Disable the reception function of DMA mode by clearing DMAR bit in the CR register */
        USARTx->CR &= (uint32_t)~((uint32_t)USART_CR_DMAR_EN);
    }
}

/**
  * @}
  */

/** @defgroup USART low-power management functions
  * @brief    USART low-power sleep wakeup functions
  *
@verbatim
 ===============================================================================
             ##### Low-Power SLEEP Wakeup Management Functions #####
 ===============================================================================
    [..] This subsection provides a set of functions about USART low-power wakeup
         management functions.

    [..]

    (#) The USART Low-Power SLEEP wakeup configurations API's :
        (++) USART_LowPowerSleepWkupConfig()
@endverbatim
  * @{
  */

/**
  * @brief  USART Low-Power SLEEP wakeup configurations
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  NewState: new state of the USARTx Low-Power SLEEP wakeup configurations.
  *         This parameter can be:
  *           @arg ENABLE : Enable USARTx module clock in SLEEP mode.
  *           @arg DISABLE: Disable USARTx module clock in SLEEP mode.
  * @retval None
  */
void USART_LowPowerSleepWkupConfig(USART_TypeDef* USARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (USARTx == USART1)
    {
        if (NewState != DISABLE)
        {
            /* Enable the USART1 module clock in SLEEP mode by setting USART1LPEN bit in the
               RCC_APB2LPENR register */
            RCC_APB2PeriphLpenCmd(RCC_APB2PeriphLpen_USART1, ENABLE);
        }
        else
        {
            /* Disable the USART1 module clock in SLEEP mode by clearing USART1LPEN bit in the
               RCC_APB2LPENR register */
            RCC_APB2PeriphLpenCmd(RCC_APB2PeriphLpen_USART1, DISABLE);
        }
    }
    else if (USARTx == USART2)
    {
        if (NewState != DISABLE)
        {
            /* Enable the USART2 module clock in SLEEP mode by setting USART2LPEN bit in the
               RCC_APB1LPENR register */
            RCC_APB1PeriphLpenCmd(RCC_APB1PeriphLpen_UART2, ENABLE);
        }
        else
        {
            /* Disable the USART2 module clock in SLEEP mode by clearing USART2LPEN bit in the
               RCC_APB1LPENR register */
            RCC_APB1PeriphLpenCmd(RCC_APB1PeriphLpen_UART2, DISABLE);
        }
    }
    else if (USARTx == USART3)
    {
        if (NewState != DISABLE)
        {
            /* Enable the USART3 module clock in SLEEP mode by setting UART3LPEN bit in the
               RCC_APB1LPENR register */
            RCC_APB1PeriphLpenCmd(RCC_APB1PeriphLpen_UART3, ENABLE);
        }
        else
        {
            /* Disable the USART3 module clock in SLEEP mode by clearing UART3LPEN bit in the
               RCC_APB1LPENR register */
            RCC_APB1PeriphLpenCmd(RCC_APB1PeriphLpen_UART3, DISABLE);
        }
    }
    else if (USARTx == USART6)
    {
        if (NewState != DISABLE)
        {
            /* Enable the USART6 module clock in SLEEP mode by setting USART6LPEN bit in the
               RCC_APB2LPENR register */
            RCC_APB2PeriphLpenCmd(RCC_APB2PeriphLpen_USART6, ENABLE);
        }
        else
        {
            /* Disable the USART6 module clock in SLEEP mode by clearing USART6LPEN bit in the
               RCC_APB2LPENR register */
            RCC_APB2PeriphLpenCmd(RCC_APB2PeriphLpen_USART6, DISABLE);
        }
    }
}

/**
  * @}
  */

/** @defgroup USART Transfers functions
  * @brief    USART Transmit and Receive functions
  *
@verbatim
 ===============================================================================
                ##### Interrupts And Flags Management Functions #####
 ===============================================================================
    [..] This subsection provides a set of functions, which is about the USART
         interrupts and the flags management.

    [..]

    (#) The USART interrupts enable API's :
        (++) USART_ITConfig()

    (#) The USART flags status check API's :
        (++) USART_GetFlagStatus()

    (#) The USART flags clear API's :
        (++) USART_ClearFlag()

    (#) The USART interrupt mask check API's :
        (++) USART_GetITStatus()

    (#) The USART interrupt disable API's :
        (++) USART_ITDisableConfig()
@endverbatim
  * @{
  */

/**
  * @brief  Enables the specified USART interrupts.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_IT: specifies the USART interrupt sources to be enabled or disabled.
  *         This parameter can be one of the following values:
  *            @arg USART_IT_CTSIC  : USART Clear to Send input interruption
  *            @arg USART_IT_DSRIC  : USART Data Set Ready input change interruption
  *            @arg USART_IT_NACK   : USART non acknowledge interruption
  *            @arg USART_IT_ITER   : USART max number of repetitions reached interruption
  *            @arg USART_IT_TXEMPTY: USART transmitter empty interruption
  *            @arg USART_IT_TIMEOUT: USART receiver time-out interruption
  *            @arg USART_IT_PARE   : USART parity error interruption
  *            @arg USART_IT_FRAME  : USART framing error interruption
  *            @arg USART_IT_OVER   : USART overrun error interruption
  *            @arg USART_IT_RXBRK  : USART break receive/end of break interruption
  *            @arg USART_IT_TXRDY  : USART transmitter ready interruption
  *            @arg USART_IT_RXRDY  : USART receiver ready interruption
  *            @arg USART_IT_UNRE   : USART LIN header timeout error interruption
  *            @arg USART_IT_LINHTE : USART LIN header timeout error interruption
  *            @arg USART_IT_LINSTE : USART LIN synch tolerance eror interruption
  *            @arg USART_IT_LINSNRE: USART LIN slave not response error interruption
  *            @arg USART_IT_LINCE  : USART LIN checksum error interruption
  *            @arg USART_IT_LINIPE : USART LIN identifier parity error interruption
  *            @arg USART_IT_LINISFE: USART LIN inconsistent synch field error interruption
  *            @arg USART_IT_LINBE  : USART LIN bit error interruption
  *            @arg USART_IT_LINTC  : USART LIN transfer completed interruption
  *            @arg USART_IT_LINID  : USART LIN identifier sent or LIN identifier received interruption
  *            @arg USART_IT_LINBK  : USART LIN break sent or LIN break received interruption
  * @param  NewState: new state of the specified USARTx interrupts.
  *         This parameter can be:
  *           @arg ENABLE : Enable corresponding interrupt.
  *           @arg DISABLE: No effect.
  * @retval None
  * @retval None
  */
void USART_ITConfig(USART_TypeDef* USARTx, uint32_t USART_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_ENABLE_IT(USART_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        USARTx->IER |= (uint32_t)((uint32_t)USART_IT);
    }
    else
    {
        USARTx->IER &= (uint32_t)~((uint32_t)USART_IT);
    }
}

/**
  * @brief  Checks whether the specified USART flag is set or not.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_FLAG: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg USART_FLAG_CTS    : image of CTS input
  *            @arg USART_FLAG_DSR    : image of DSR input
  *            @arg USART_FLAG_CTSIC  : Clear to Send input change flag
  *            @arg USART_FLAG_DSRIC  : Data Set Ready input change flag
  *            @arg USART_FLAG_NACK   : non acknowledge interrupt
  *            @arg USART_FLAG_ITER   : max number of repetitions reached
  *            @arg USART_FLAG_TXEMPTY: transmitter empty
  *            @arg USART_FLAG_TIMEOUT: receiver time-out
  *            @arg USART_FLAG_PARE   : parity error
  *            @arg USART_FLAG_FRAME  : framing error
  *            @arg USART_FLAG_OVER   : overrun error
  *            @arg USART_FLAG_RXBRK  : break receive/end of break
  *            @arg USART_FLAG_TXRDY  : transmitter ready
  *            @arg USART_FLAG_RXRDY  : receiver ready
  *            @arg USART_FLAG_UNRE   : underrun error
  *            @arg USART_FLAG_LINHTE : LIN header timeout error
  *            @arg USART_FLAG_LINSTE : LIN synch tolerance eror
  *            @arg USART_FLAG_LINSNRE: LIN slave not response error
  *            @arg USART_FLAG_LINCE  : LIN checksum error
  *            @arg USART_FLAG_LINIPE : LIN identifier parity error
  *            @arg USART_FLAG_LINISFE: LIN inconsistent synch field error
  *            @arg USART_FLAG_LINBE  : LIN bit error
  *            @arg USART_FLAG_LINBLS : LIN bus line status
  *            @arg USART_FLAG_LINTC  : LIN transfer completed
  *            @arg USART_FLAG_LINID  : LIN identifier sent or LIN identifier received
  *            @arg USART_FLAG_LINBK  : LIN break sent or LIN break received
  * @retval The new state of USART_FLAG (SET or RESET).
  */
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint32_t USART_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_GET_FLAG(USART_FLAG));

    if ((USARTx->CSR & USART_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
  * @brief  Clears the USARTx's pending flags.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_FLAG: specifies the flag to clear.
  *         This parameter can be any combination of the following values:
  *            @arg USART_CLEAR_CTSIC  :  Clear to Send input interrupt clear
  *            @arg USART_CLEAR_DSRIC  :  Data Set Ready input change clear
  *            @arg USART_CLEAR_NACK   :  non acknowledge interrupt clear
  *            @arg USART_CLEAR_ITER   :  max number of repetitions reached interrupt clear
  *            @arg USART_CLEAR_TXEMPTY:  transmitter empty interrupt clear
  *            @arg USART_CLEAR_TIMEOUT:  receiver time-out interrupt clear
  *            @arg USART_CLEAR_PARE   :  parity error interrupt clear
  *            @arg USART_CLEAR_FRAME  :  framing error interrupt clear
  *            @arg USART_CLEAR_OVER   :  overrun error interrupt clear
  *            @arg USART_CLEAR_RXBRK  :  break receive/end of break interrupt clear
  *            @arg USART_CLEAR_TXRDY  :  transmitter ready interrupt clear
  *            @arg USART_CLEAR_RXRDY  :  receiver ready interrupt clear
  *            @arg USART_CLEAR_UNRE   :  underrun error interrupt clear
  *            @arg USART_CLEAR_LINHTE :  LIN header timeout error interrupt clear
  *            @arg USART_CLEAR_LINSTE :  LIN synch tolerance eror interrupt clear
  *            @arg USART_CLEAR_LINSNRE:  LIN slave not response error interrupt clear
  *            @arg USART_CLEAR_LINCE  :  LIN checksum error interrupt clear
  *            @arg USART_CLEAR_LINIPE :  LIN identifier parity error interrupt clear
  *            @arg USART_CLEAR_LINISFE:  LIN inconsistent synch field error interrupt clear
  *            @arg USART_CLEAR_LINBE  :  LIN bit error interrupt clear
  *            @arg USART_CLEAR_LINTC  :  LIN transfer completed interrupt clear
  *            @arg USART_CLEAR_LINID  :  LIN identifier sent or LIN identifier received interrupt clear
  *            @arg USART_CLEAR_LINBK  :  LIN break sent or LIN break received interrupt clear
  * @note   CTS image of CTS input bit is cleared when CTS pin is 0.
  * @note   DST image of DSR input bit is cleared when DSR pin is 0.
  * @note   LINBLS LIN bus line status bit is cleared when LINRX pin is 0.
  * @note   TXEMPTY flag bit also can be cleared by a write to the US_THR register (USART_Transmit()).
  * @note   TXRDY flag bit also can be cleared by a write to the US_THR register (USART_Transmit()).
  * @note   RXRDY flag bit also can be cleared by a read to the US_RHR register (USART_Receive()).
  * @retval None
  */
void USART_ClearFlag(USART_TypeDef* USARTx, uint32_t USART_FLAG)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_CLEAR_FLAG(USART_FLAG));

    USARTx->CR |= (uint32_t)USART_FLAG;
}

/**
  * @brief  Checks whether the specified USART interrupt has enabled or disabled.
  * @param  USARTx: where x can be [1, 2, 3, 6] to select the USART peripheral.
  * @param  USART_IT: specifies the USART interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg USART_MASK_CTSIC  :  mask to Send input interrupt mask
  *            @arg USART_MASK_DSRIC  :  Data Set Ready input change mask
  *            @arg USART_MASK_NACK   :  non acknowledge interrupt mask
  *            @arg USART_MASK_ITER   :  max number of repetitions reached interrupt mask
  *            @arg USART_MASK_TXEMPTY:  transmitter empty interrupt mask
  *            @arg USART_MASK_TIMEOUT:  receiver time-out interrupt mask
  *            @arg USART_MASK_PARE   :  parity error interrupt mask
  *            @arg USART_MASK_FRAME  :  framing error interrupt mask
  *            @arg USART_MASK_OVER   :  overrun error interrupt mask
  *            @arg USART_MASK_RXBRK  :  break receive/end of break interrupt mask
  *            @arg USART_MASK_TXRDY  :  transmitter ready interrupt mask
  *            @arg USART_MASK_RXRDY  :  receiver ready interrupt mask
  *            @arg USART_MASK_UNRE   :  underrun error interrupt mask
  *            @arg USART_MASK_LINHTE :  LIN header timeout error interrupt mask
  *            @arg USART_MASK_LINSTE :  LIN synch tolerance eror interrupt mask
  *            @arg USART_MASK_LINSNRE:  LIN slave not response error interrupt mask
  *            @arg USART_MASK_LINCE  :  LIN checksum error interrupt mask
  *            @arg USART_MASK_LINIPE :  LIN identifier parity error interrupt mask
  *            @arg USART_MASK_LINISFE:  LIN inconsistent synch field error interrupt mask
  *            @arg USART_MASK_LINBE  :  LIN bit error interrupt mask
  *            @arg USART_MASK_LINTC  :  LIN transfer completed interrupt mask
  *            @arg USART_MASK_LINID  :  LIN identifier sent or LIN identifier received interrupt mask
  *            @arg USART_MASK_LINBK  :  LIN break sent or LIN break received interrupt mask
  * @retval The new state of USART_IT (SET or RESET).
  */
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint32_t USART_IT)
{
    ITStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_GET_IT(USART_IT));

    if ((USARTx->IMR & USART_IT) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * @brief  USARTx's interrupt disable configure.
  * @param  USARTx: where x can be [1, 2. 3, 6] to select the USART peripheral.
  * @param  USART_IT: specifies the interrupt pending bit to clear.
  *         This parameter can be one of the following values:
  *           @arg USART_DIS_CTSIC  :  disable to Send input interrupt disable
  *           @arg USART_DIS_DSRIC  :  Data Set Ready input change disable
  *           @arg USART_DIS_NACK   :  non acknowledge interrupt disable
  *           @arg USART_DIS_ITER   :  max number of repetitions reached interrupt disable
  *           @arg USART_DIS_TXEMPTY:  transmitter empty interrupt disable
  *           @arg USART_DIS_TIMEOUT:  receiver time-out interrupt disable
  *           @arg USART_DIS_PARE   :  parity error interrupt disable
  *           @arg USART_DIS_FRAME  :  framing error interrupt disable
  *           @arg USART_DIS_OVER   :  overrun error interrupt disable
  *           @arg USART_DIS_RXBRK  :  break receive/end of break interrupt disable
  *           @arg USART_DIS_TXRDY  :  transmitter ready interrupt disable
  *           @arg USART_DIS_RXRDY  :  receiver ready interrupt disable
  *           @arg USART_DIS_UNRE   :  underrun error interrupt disable
  *           @arg USART_DIS_LINHTE :  LIN header timeout error interrupt disable
  *           @arg USART_DIS_LINSTE :  LIN synch tolerance eror interrupt disable
  *           @arg USART_DIS_LINSNRE:  LIN slave not response error interrupt disable
  *           @arg USART_DIS_LINCE  :  LIN checksum error interrupt disable
  *           @arg USART_DIS_LINIPE :  LIN identifier parity error interrupt disable
  *           @arg USART_DIS_LINISFE:  LIN inconsistent synch field error interrupt disable
  *           @arg USART_DIS_LINBE  :  LIN bit error interrupt disable
  *           @arg USART_DIS_LINTC  :  LIN transfer completed interrupt disable
  *           @arg USART_DIS_LINID  :  LIN identifier sent or LIN identifier received interrupt disable
  *           @arg USART_DIS_LINBK  :  LIN break sent or LIN break received interrupt disable
  * @param  NewState: new state of the specified USARTx interrupts.
  *         This parameter can be:
  *           @arg ENABLE : Disable corresponding interrupt.
  *           @arg DISABLE: No effect.
  * @retval None
  */
void USART_ITDisableConfig(USART_TypeDef* USARTx, uint32_t USART_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_CLEAR_IT(USART_IT));

    if (NewState != DISABLE)
    {
        USARTx->IDR |= (uint32_t)((uint32_t)USART_IT);
    }
    else
    {
        USARTx->IDR &= (uint32_t)~((uint32_t)USART_IT);
    }
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
