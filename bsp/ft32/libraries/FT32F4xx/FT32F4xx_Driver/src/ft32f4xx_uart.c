/**
  ******************************************************************************
  * @file    ft32f4xx_uart.c
  * @author  FMD AE
  * @brief   This file provides firmware functions to manage the following
  *          functionalities of the Universal Asynchronous Receiver Transmitter
  *          Peripheral (UART) and the Low-Power Universal Asynchronous Receiver
  *          Transmitter Peripheral (LPUART).
  *          + Initialization and de-initialization functions
  *          + Normal command and configuration functions
  *          + Fractional baudrate function
  *          + Break command functions
  *          + Receiver time-out and transmitter timeguard functions
  *          + Multidrop mode command function
  *          + IrDA mode function
  *          + LIN mode functions
  *          + Data transfers functions
  *          + DMA transfers management functions
  *          + Low-Power SLEEP and STOP wakeup management functions
  *          + Interrupts and flags management functions
  * @version V1.0.0
  * @date    2025-03-28
  *
  @verbatim
  *
  * [..]
  *   The functionalities supported by different UART and LPUART are listed in following:
  *
  *          Table 1. UART / LPUART feature.
  *          +---------------------------------------------------------+
  *          |     Functionalities    | UART4 | UART5 | UART7 | LPUART |
  *          |---------------------------------------------------------+
  *          |    DMA Communication   |   X   |   X   |   X   |   X    |
  *          |---------------------------------------------------------+
  *          |        IrDA mode       |   X   |   X   |   X   |   -    |
  *          |---------------------------------------------------------+
  *          |     Low-Power wakeup   |   X   |   X   |   X   |   X    |
  *          |---------------------------------------------------------+
  *          |         LIN mode       |   X   |   X   |   X   |   -    |
  *          |---------------------------------------------------------+
  *          |   Fractional baudrate  |   X   |   X   |   -   |   -    |
  *          |---------------------------------------------------------+
  *          | Timeguard and Time-out |   X   |   X   |   X   |   -    |
  *          |---------------------------------------------------------+
  *          |      Multidrop mode    |   X   |   X   |   X   |   X    |
  *          |---------------------------------------------------------+
  *
  *          [+] X - Supported
  *          [+] - - Not supported
  *          [+] Low-Power wakeup: UART can wakeup from SLEEP mode.
  *                                LPUART can wakeup from SLEEP and STOP mode.
  *
  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_uart.h"
#include "ft32f4xx_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup UART_Private_Constants UART Private Constants
  * @{
  */
/*!< UART and LPUART CR register mode field Mask     ((~(uint32_t)0xFFFFFF5F)) */
#define CR_CLEAR_MODE_MASK        ((uint32_t)(USART_CR_TXDIS  | USART_CR_RXDIS))      /*!< UART CR mode fields of parameters set by UART_Init API         */

/*!< UART and LPUART MR register normal Mask         ((~(uint32_t)0xFF740100)) */
#define MR_CLEAR_NORMAL_MASK      ((uint32_t)(USART_MR_INVDATA | USART_MR_OVER       | \
                                                                 USART_MR_MODE9      | \
                                              USART_MR_MSBF    | USART_MR_CHMODE     | \
                                              USART_MR_NBSTOP  | USART_MR_PAR        | \
                                                                 USART_MR_CHRL       | \
                                              USART_MR_USCLKS  | USART_MR_USART_MODE))/*!< UART MR normal fields of parameters set by UART_Init API       */

/**
  * @}
  */

/** @defgroup UART and LPUAR init and de-init functions
  * @brief    None
  *
@verbatim
 ===============================================================================
                           ##### Init and DeInit Functions #####
 ===============================================================================
    [..] This subsection provides a set of functions about UART and LPUART
         initialization and de-initialization.

    [..] Most UART and LPUART configurations can be set in the UART_init() function.
         However, After UART_Init() function, user can use others configurations
         (cfg) functions to change UART and LPUART configurational. The command (Cmd)
         functions can execute control operations under different configurations.

    [..] The configuration procedure of UART_Init() function is as follows:
        (++) Check the parameters
        (++) Enable UARTx and LPUART work clock and configuration clock.
        (++) UART and LPUART CR configuration
             (#) Configure the UART_Mode:
                 (-) transmitter disable
                 (-) transmitter enable
                 (-) receiver disable
                 (-) receiver enable
        (++) UART and LPUART MR configuration
             (#) Normal configuration:
                 (-) Inverted data
                 (-) Oversampling mode
                 (-) 9-bit character length
                 (-) Bit order
                 (-) channel mode
                 (-) Number of STOP bits
                 (-) Parity type
                 (-) Character length
                 (-) Clock selection
                 (-) UART mode of operation
        (++) UART BRGR configuration except fractional part
        (++) UART IF configuration
        (++) UART LINMR configuration:
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

    (#) The UART and LPUART init API's :
        (++) UART_Init()

    (#) The UART and LPUART Struct init API's :
        (++) UART_StructInit()

    (#) The UART and LPUART de-init API's :
        (++) UART_DeInit()
@endverbatim
  * @{
  */

/**
  * @brief  Initialize the UART and LPUART peripheral according to the specified
  *         parameters in the UART_InitStruct.
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  UART_InitStruct: pointer to a UART_InitTypeDef structure that contains
  *         the configuration information for the specified UART peripheral.
  * @retval None
  */
void UART_Init(USART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct)
{
    uint32_t clock_divider = 0, frac_divider = 0, apbclock = 0, tmpreg = 0;

    RCC_ClocksTypeDef RCC_ClocksStatus;

    /*---------------------------- Check the Parameter -------------------------*/
    /* Check UART PERIPH */
    if ((UART_InitStruct->UART_OperationMode == UART_MODE_OPERATION_IrDA) ||
            (UART_InitStruct->UART_OperationMode == UART_MODE_OPERATION_LIN_MASTER) ||
            (UART_InitStruct->UART_OperationMode == UART_MODE_OPERATION_LIN_SLAVE))
    {
        assert_param(IS_UART_457_PERIPH(UARTx));
    }
    else if (UART_InitStruct->UART_OperationMode == UART_MODE_OPERATION_NORMAL)
    {
        assert_param(IS_UART_ALL_PERIPH(UARTx));
    }

    if (UART_InitStruct->UART_INVData == UART_INVDATA_ENABLE)
    {
        assert_param(IS_UART_457_PERIPH(UARTx));
    }
    else
    {
        assert_param(IS_UART_ALL_PERIPH(UARTx));
    }

    /* Check normal parameter*/
    assert_param(IS_UART_BAUDRATE(UART_InitStruct->UART_BaudRate));
    assert_param(IS_UART_CHAR_LENGTH(UART_InitStruct->UART_WordLength));
    assert_param(IS_UART_STOPBITS(UART_InitStruct->UART_StopBits));
    assert_param(IS_UART_PARITY(UART_InitStruct->UART_Parity));
    assert_param(IS_UART_MODE(UART_InitStruct->UART_Mode));
    assert_param(IS_UART_CLOCK_SELECT(UART_InitStruct->UART_CLKSelect));
    assert_param(IS_UART_MODE_OPERATION(UART_InitStruct->UART_OperationMode));
    assert_param(IS_UART_BIT_ORDER(UART_InitStruct->UART_BitOrder));
    assert_param(IS_UART_CHANNEL_MODE(UART_InitStruct->UART_ChannelMode));
    assert_param(IS_UART_OVERSAMPLING(UART_InitStruct->UART_OverSampling));
    assert_param(IS_UART_INVDATA(UART_InitStruct->UART_INVData));

    /* Check IrDA mode parameter */
    if (UART_InitStruct->UART_OperationMode == UART_MODE_OPERATION_IrDA)
    {
        assert_param(IS_UART_IF(UART_InitStruct->UART_IrDAFilter));
        assert_param(IS_UART_FIDIRATIO(UART_InitStruct->UART_FiDiRatio));
    }

    /* Check LIN mode parameter*/
    if ((UART_InitStruct->UART_OperationMode == UART_MODE_OPERATION_LIN_MASTER) ||
            (UART_InitStruct->UART_OperationMode == UART_MODE_OPERATION_LIN_SLAVE))
    {
        assert_param(IS_UART_SYNC_DISABLE(UART_InitStruct->UART_SYNCDisable));
        assert_param(IS_UART_PDC_MODE_LINMR(UART_InitStruct->UART_PDCMode));
        assert_param(IS_UART_DLC(UART_InitStruct->UART_DataLengthControl));
        assert_param(IS_UART_WKUP_TYPE(UART_InitStruct->UART_WkupType));
        assert_param(IS_UART_FRAME_SLOT_DISABLE(UART_InitStruct->UART_FrameSlotDisable));
        assert_param(IS_UART_DATA_LENGTH_MODE(UART_InitStruct->UART_DataLengthMode));
        assert_param(IS_UART_CHECKSUM_TYPE(UART_InitStruct->UART_CheckSumType));
        assert_param(IS_UART_CHECKSUM_DISABLE(UART_InitStruct->UART_CheckSumDisable));
        assert_param(IS_UART_PARITY_DISABLE(UART_InitStruct->UART_ParityDisable));
        assert_param(IS_UART_NODE_ACTIVE(UART_InitStruct->UART_NodeAction));
    }

    /*--------------------------- Enable The Peripheral ------------------------*/
    if (UARTx == UART4)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,  ENABLE);
    }
    else if (UARTx == UART5)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,  ENABLE);
    }
    else if (UARTx == UART7)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7,  ENABLE);
    }
    else if (UARTx == LPUART)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_LPUART, ENABLE);
    }

    /*---------------------- UART and LPUART CR Configuration ------------------*/
    tmpreg = UARTx->CR;

    /* Configure the UART_Mode                        */
    /* Configure the TXDIS and RXDIS bits             */
    UARTx->CR |= ((uint32_t)(CR_CLEAR_MODE_MASK));
    /* Configure the TXEN and RXEN bits               */
    tmpreg |= UART_InitStruct->UART_Mode;

    /* Write to UART and LPUART CR */
    UARTx->CR = tmpreg;

    /*---------------------- UART and LPUART MR Configuration ------------------*/
    tmpreg = UARTx->MR;

    /* Normal configuration                                                */
    /* Set the [23:23]_INVDATA       ascording to UART_INVData       value */
    /* Set the [19:19]_OVER          ascording to UART_OverSampling  value */
    /* Set the [17:17]_MODE9         ascording to UART_WordLength    value */
    /* Set the [16:16]_MSBF          ascording to UART_BitOrder      value */
    /* Set the [15:14]_CHMODE        ascording to UART_ChannelMode   value */
    /* Set the [13:12]_NBSTOP        ascording to UART_StopBits      value */
    /* Set the [11: 9]_PAR           ascording to UART_Parity        value */
    /* Set the [ 7: 6]_CHRL          ascording to UART_WordLength    value */
    /* Set the [ 5: 4]_USCLKS        ascording to UART_CLKSelect     value */
    /* Set the [ 3: 0]_USART_MODE    ascording to UART_OperationMode value */
    /* Clear the normal cfg bits     */
    tmpreg &= (uint32_t)~((uint32_t)MR_CLEAR_NORMAL_MASK);
    /* Configure the normal cfg bits */
    tmpreg |= (uint32_t)UART_InitStruct->UART_INVData                   |
              UART_InitStruct->UART_OverSampling              |
              UART_InitStruct->UART_WordLength                |
              UART_InitStruct->UART_BitOrder                  |
              UART_InitStruct->UART_ChannelMode               |
              UART_InitStruct->UART_StopBits                  |
              UART_InitStruct->UART_Parity                    |
              UART_InitStruct->UART_CLKSelect                 |
              UART_InitStruct->UART_OperationMode             ;

    /* Write to UART and LPUART MR */
    UARTx->MR = tmpreg;

    /*---------------------------- USART FIDI Configuration -----------------------*/
    if (UART_InitStruct->UART_OperationMode == UART_MODE_OPERATION_IrDA)
    {
        UARTx->FIDI = (uint32_t)UART_InitStruct->UART_FiDiRatio;
    }

    /*---------------------- UART and LPUART BRGR Configuration ----------------*/
    tmpreg = UARTx->BRGR;

    /* Configure the UART and LPUART Baud Rate */
    RCC_GetClocksFreq(&RCC_ClocksStatus);

    if (UARTx == UART4)
    {
        apbclock = RCC_ClocksStatus.PCLK_Frequency     ;
    }
    else if (UARTx == UART5)
    {
        apbclock = RCC_ClocksStatus.PCLK_Frequency     ;
    }
    else if (UARTx == UART7)
    {
        apbclock = RCC_ClocksStatus.PCLK_Frequency     ;
    }
    else if (UARTx == LPUART)
    {
        apbclock = RCC_ClocksStatus.LPUARTCLK_Frequency;
    }

    /* Determine the integer part and fraction part disable (fractional part can configure in UART_FracDivider_Cfg()) */
    /* BaudRate not equal 0*/
    if ((UART_InitStruct->UART_BaudRate) >  0)
    {
        /* x16 Oversample in Async mode */
        if (UART_InitStruct->UART_OverSampling == UART_OVERSAMPLING_16)
        {
            clock_divider = (uint32_t)(((apbclock) / ((UART_InitStruct->UART_BaudRate) * 16)));
            frac_divider  = 0;
        }
        /* x8  Oversample in Async mode */
        else if (UART_InitStruct->UART_OverSampling == UART_OVERSAMPLING_8)
        {
            clock_divider = (uint32_t)(((apbclock) / ((UART_InitStruct->UART_BaudRate) * 8)));
            frac_divider  = 0;
        }
    }
    /* BaudRate     equal 0*/
    else if ((UART_InitStruct->UART_BaudRate) == 0)
    {
        clock_divider = 0;
        frac_divider  = 0;
    }

    /* Write to UART and LPUART BRGR */
    UARTx->BRGR = (((uint32_t)(clock_divider)) | ((uint32_t)(frac_divider) << 16U));

    /*---------------------- UART and LPUART IF Configuration -------------------*/
    /* Write to UART and LPUART IF in IrDA mode */
    if (UART_InitStruct->UART_OperationMode == UART_MODE_OPERATION_IrDA)
    {
        UARTx->IF = (uint16_t)UART_InitStruct->UART_IrDAFilter;
    }

    /*---------------------- UART and LPUART LINMR Configuration ----------------*/
    tmpreg = 0;

    if ((UART_InitStruct->UART_OperationMode == UART_MODE_OPERATION_LIN_MASTER) ||
            (UART_InitStruct->UART_OperationMode == UART_MODE_OPERATION_LIN_SLAVE))
    {
        /* Set the [17:17]_SYNCDIS ascording to UART_SYNCDisable       value */
        /* Set the [16:16]_PDCM    ascording to UART_PDCMode           value */
        /* Set the [15: 8]_DLC     ascording to UART_DataLengthControl value */
        /* Set the [ 7: 7]_WKUPTYP ascording to UART_WkupType          value */
        /* Set the [ 6: 6]_FSDIS   ascording to UART_FrameSlotDisable  value */
        /* Set the [ 5: 5]_DLM     ascording to UART_DataLengthMode    value */
        /* Set the [ 4: 4]_CHKTYP  ascording to UART_CheckSumType      value */
        /* Set the [ 3: 3]_CHKDIS  ascording to UART_CheckSumDisable   value */
        /* Set the [ 2: 2]_PARDIS  ascording to UART_ParityDisable     value */
        /* Set the [ 1: 0]_NACT    ascording to UART_NodeAction        value */
        tmpreg |= (uint32_t)UART_InitStruct-> UART_SYNCDisable                        |
                  UART_InitStruct-> UART_PDCMode                            |
                  ((UART_InitStruct-> UART_DataLengthControl << (uint32_t)8)) |
                  UART_InitStruct-> UART_WkupType                           |
                  UART_InitStruct-> UART_FrameSlotDisable                   |
                  UART_InitStruct-> UART_DataLengthMode                     |
                  UART_InitStruct-> UART_CheckSumType                       |
                  UART_InitStruct-> UART_CheckSumDisable                    |
                  UART_InitStruct-> UART_ParityDisable                      |
                  ((UART_InitStruct-> UART_NodeAction        << (uint32_t)0)) ;

        /* Write to UART and LPUART LINMR*/
        UARTx->LINMR = tmpreg;
    }
}

/**
  * @brief  Configure each UART_InitStruct member with its default value.
  * @param  UART_InitStruct: pointer to a UART_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void UART_StructInit(UART_InitTypeDef* UART_InitStruct)
{
    /* UART_InitStruct members default value */
    UART_InitStruct->UART_BaudRate            = 9600                           ;
    UART_InitStruct->UART_FiDiRatio           = 174                             ;
    UART_InitStruct->UART_IrDAFilter          = 0                              ;
    UART_InitStruct->UART_WordLength          = UART_CHAR_LENGTH_8BIT          ;
    UART_InitStruct->UART_StopBits            = UART_STOPBITS_1                ;
    UART_InitStruct->UART_Parity              = UART_PARITY_NONE               ;
    UART_InitStruct->UART_Mode                = UART_MODE_TX | UART_MODE_RX    ;
    UART_InitStruct->UART_CLKSelect           = UART_CLOCK_SELECT_MCK          ;
    UART_InitStruct->UART_OperationMode       = UART_MODE_OPERATION_NORMAL     ;
    UART_InitStruct->UART_BitOrder            = UART_BIT_ORDER_LSBF            ;
    UART_InitStruct->UART_ChannelMode         = UART_CHANNEL_MODE_NORMAL       ;
    UART_InitStruct->UART_OverSampling        = UART_OVERSAMPLING_16           ;
    UART_InitStruct->UART_INVData             = UART_INVDATA_DISABLE           ;
    UART_InitStruct->UART_SYNCDisable         = UART_SYNC_DISABLE_NONE         ;
    UART_InitStruct->UART_PDCMode             = UART_PDC_MODE_LINMR_NOTWRITE   ;
    UART_InitStruct->UART_DataLengthControl   = 0                              ;
    UART_InitStruct->UART_WkupType            = UART_WKUP_TYPE_LIN_2_0         ;
    UART_InitStruct->UART_FrameSlotDisable    = UART_FRAME_SLOT_DISABLE_NONE   ;
    UART_InitStruct->UART_DataLengthMode      = UART_DATA_LENGTH_MODE_DLC      ;
    UART_InitStruct->UART_CheckSumType        = UART_CHECKSUM_TYPE_ENHANCED    ;
    UART_InitStruct->UART_CheckSumDisable     = UART_CHECKSUM_DISABLE_NONE     ;
    UART_InitStruct->UART_ParityDisable       = UART_PARITY_DISABLE_NONE       ;
    UART_InitStruct->UART_NodeAction          = UART_NODE_ACTIVE_PUBLISH       ;
}

/**
  * @brief  De-Initialize the UARTx peripheral to their default reset value.
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @retval None
  */
void UART_DeInit(USART_TypeDef* UARTx)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));

    /* UARTx reset operation */
    if (UARTx == UART4)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4,  ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4,  DISABLE);
    }
    else if (UARTx == UART5)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5,  ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5,  DISABLE);
    }
    else if (UARTx == UART7)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART7,  ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART7,  DISABLE);
    }
    else if (UARTx == LPUART)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_LPUART, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_LPUART, DISABLE);
    }
}

/**
  * @}
  */

/** @defgroup UART and LPUART normal cmd and cfg functions
  * @brief    UART and LPUART normal command and configuration functions
  *
@verbatim
 ===============================================================================
              ##### Normal Command And Configuration Functions #####
 ===============================================================================
    [..] This subsection provides a set of normal command and configuration
         function.

    [..]

    (#) The Normal cmd API's :
        (++) UART_Cmd()
        (++) UART_RSTSTA_Cmd()
        (++) UART_TXDIS_Cmd()
        (++) UART_TXEN_Cmd()
        (++) UART_RXDIS_Cmd()
        (++) UART_RXEN_Cmd()
        (++) UART_RSTTX_Cmd()
        (++) UART_RSTRX_Cmd()

    (#) The Normal cfg API's :
        (++) UART_InvData_Cfg()
        (++) UART_OverSampling8_Cfg()
        (++) UART_DataLength9_Cfg()
        (++) UART_MSBFirst_Cfg()
        (++) UART_ChannelMode_Cfg()
        (++) UART_StopBit_Cfg()
        (++) UART_Parity_Cfg()
        (++) UART_DataLength_Cfg()
        (++) UART_CLKSelect_Cfg()
        (++) UART_OperationMode_Cfg()

    (#) The Normal read API's :
        (++) None
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified UART peripheral.
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  NewState: new state of the UARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_Cmd(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected UART by setting the UARTxEN bit in the RCC_APB1ENR register */
        if (UARTx == UART4)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
        }
        else if (UARTx == UART5)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
        }
        else if (UARTx == UART7)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);
        }
        else if (UARTx == LPUART)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_LPUART, ENABLE);
        }
    }
    else
    {
        /* Disable the selected UART by clearing the UARTxEN bit in the RCC_APB1ENR register */
        if (UARTx == UART4)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, DISABLE);
        }
        else if (UARTx == UART5)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, DISABLE);
        }
        else if (UARTx == UART7)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, DISABLE);
        }
        else if (UARTx == LPUART)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_LPUART, DISABLE);
        }
    }
}

/**
  * @brief  Reset status bits.
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  NewState: new state of the UARTx reset status bits.
  *         This parameter can be:
  *           @arg ENABLE : Resets the status bits PARE, FRAME, OVER, LINBE,
  *                         LINISFE, LINIPE, LINCE, LINSNRE, LINSTE, LINHTE,
  *                         LINID, LINTC, LINBK and RXBRK in US_CSR.
  *           @arg DISABLE: No effect
  * @retval None
  */
void UART_RSTSTA_Cmd(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* The status bits reset by setting RSTSTA bit in the CR register */
        UARTx->CR |= USART_CR_RSTSTA;
    }
    else
    {
        /* No effect */
        UARTx->CR &= (uint32_t)~((uint32_t)USART_CR_RSTSTA);
    }
}

/**
  * @brief  Transmitter disable.
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  NewState: new state of the UARTx transmitter disable.
  *         This parameter can be:
  *           @arg ENABLE : Disable the transmitter.
  *           @arg DISABLE: No effect
  * @retval None
  */
void UART_TXDIS_Cmd(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* The transmitter disable by setting TXDIS bit in the CR register */
        UARTx->CR |= USART_CR_TXDIS;
    }
    else
    {
        /* No effect */
        UARTx->CR &= (uint32_t)~((uint32_t)USART_CR_TXDIS);
    }
}

/**
  * @brief  Transmitter enable.
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  NewState: new state of the UARTx transmitter enable.
  *         This parameter can be:
  *           @arg ENABLE : Enable the transmitter if TXDIS is 0.
  *           @arg DISABLE: No effect
  * @retval None
  */
void UART_TXEN_Cmd(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* The transmitter enable by setting TXEN bit in the CR register */
        UARTx->CR |= USART_CR_TXEN;
    }
    else
    {
        /* No effect */
        UARTx->CR &= (uint32_t)~((uint32_t)USART_CR_TXEN);
    }
}

/**
  * @brief  Receiver disable.
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  NewState: new state of the UARTx receiver disable.
  *         This parameter can be:
  *           @arg ENABLE : Disable the receiver.
  *           @arg DISABLE: No effect
  * @retval None
  */
void UART_RXDIS_Cmd(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* The receiver disable by setting RXDIS bit in the CR register */
        UARTx->CR |= USART_CR_RXDIS;
    }
    else
    {
        /* No effect */
        UARTx->CR &= (uint32_t)~((uint32_t)USART_CR_RXDIS);
    }
}

/**
  * @brief  Receiver enable.
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  NewState: new state of the UARTx receiver enable.
  *         This parameter can be:
  *           @arg ENABLE : Enable the receiver if RXDIS is 0.
  *           @arg DISABLE: No effect
  * @retval None
  */
void UART_RXEN_Cmd(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* The receiver enable by setting RXEN bit in the CR register */
        UARTx->CR |= USART_CR_RXEN;
    }
    else
    {
        /* No effect */
        UARTx->CR &= (uint32_t)~((uint32_t)USART_CR_RXEN);
    }
}

/**
  * @brief  Reset transmitter
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  NewState: new state of the UARTx reset transmitter.
  *         This parameter can be:
  *           @arg ENABLE : Resets the transmitter.
  *           @arg DISABLE: No effect
  * @retval None
  */
void UART_RSTTX_Cmd(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* The transmitter reset by setting RSTTX bit in the CR register */
        UARTx->CR |= USART_CR_RSTTX;
    }
    else
    {
        /* No effect */
        UARTx->CR &= (uint32_t)~((uint32_t)USART_CR_RSTTX);
    }
}

/**
  * @brief  Reset receiver
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  NewState: new state of the UARTx reset receiver.
  *         This parameter can be:
  *           @arg ENABLE : Resets the receiver.
  *           @arg DISABLE: No effect
  * @retval None
  */
void UART_RSTRX_Cmd(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* The receiver reset by setting RSTRX bit in the CR register */
        UARTx->CR |= USART_CR_RSTRX;
    }
    else
    {
        /* No effect */
        UARTx->CR &= (uint32_t)~((uint32_t)USART_CR_RSTRX);
    }
}

/**
  * @brief  Inverted data
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  NewState: new state of the UARTx inverted data.
  *         This parameter can be:
  *           @arg ENABLE : The data field transmitted on TXD line is inverted
  *                         compared to the value writted on US_THR register or
  *                         the content read in US_RHR is inverted compared to
  *                         what is received on TXD line.
  *           @arg DISABLE: The data field transmitted on TXD line is the same
  *                         as one written in US_THR register or content read in
  *                         US_RHR is the same as RXD line. Normal mode of operation.
  * @retval None
  */
void UART_InvData_Cfg(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the invert data function by setting INVDATA bit in the MR register */
        UARTx->MR |= USART_MR_INVDATA;
    }
    else
    {
        /* Disable the invert data function by clearing INVDATA bit in the MR register */
        UARTx->MR &= (uint32_t)~((uint32_t)USART_MR_INVDATA);
    }
}

/**
  * @brief  Oversampling mode
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  NewState: new state of the UARTx oversampling mode.
  *         This parameter can be:
  *           @arg ENABLE : 8x oversampling.
  *           @arg DISABLE: 16x oversampling.
  * @retval None
  */
void UART_OverSampling8_Cfg(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the 8x oversampling function by setting OVER bit in the MR register */
        UARTx->MR |= USART_MR_OVER;
    }
    else
    {
        /* Disable the 8x oversampling function by clearing OVER bit in the MR register */
        UARTx->MR &= (uint32_t)~((uint32_t)USART_MR_OVER);
    }
}

/**
  * @brief  9-bit character length
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  NewState: new state of the UARTx 9-bit character length.
  *         This parameter can be:
  *           @arg ENABLE : 9-bit character length.
  *           @arg DISABLE: UART_Char_Length defines character length.
  * @retval None
  */
void UART_DataLength9_Cfg(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable 9-bit character length by setting MODE9 bit in the MR register */
        UARTx->MR |= USART_MR_MODE9;
    }
    else
    {
        /* Disable 9-bit character length by clearing MODE9 bit in the MR register */
        UARTx->MR &= (uint32_t)~((uint32_t)USART_MR_MODE9);
    }
}

/**
  * @brief  Bit order
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  NewState: new state of the UARTx bit order.
  *         This parameter can be:
  *           @arg ENABLE : Most significant bit is sent/received first.
  *           @arg DISABLE: Least significant bit is sent/received first.
  * @retval None
  */
void UART_MSBFirst_Cfg(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable most significant bit is sent/received by setting MSBF bit in the MR register */
        UARTx->MR |= USART_MR_MSBF;
    }
    else
    {
        /* Enable least significant bit is sent/received by setting MSBF bit in the MR register */
        UARTx->MR &= (uint32_t)~((uint32_t)USART_MR_MSBF);
    }
}

/**
  * @brief  Channel mode
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  UART_ChannelMode: channel mode;
  *         This parameter can be one of the following values:
  *                            UART_CHANNEL_MODE_NORMAL          - Normal mode
  *                            UART_CHANNEL_MODE_AUTOMATIC       - Automatic mode
  *                            UART_CHANNEL_MODE_LOCAL_LOOPBACK  - Local loopback mode
  *                            UART_CHANNEL_MODE_REMOTE_LOOPBACK - Remote loopbak mode
  * @retval None
  */
void UART_ChannelMode_Cfg(USART_TypeDef* UARTx, uint32_t UART_ChannelMode)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_CHANNEL_MODE(UART_ChannelMode));

    /* Clear the channel mode by clearing the CHMODE[15:14] bits in the MR register */
    UARTx->MR &= (uint32_t)~((uint32_t)USART_MR_CHMODE);

    /* Set the channel mode by setting the CHMODE[15:14] bits in the MR register    */
    UARTx->MR |= (uint32_t)((uint32_t)UART_ChannelMode);
}

/**
  * @brief  Number of stop bits
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  UART_StopBits: number of stop bits,
  *         This parameter can be one of the following values:
  *                         UART_STOPBITS_1   - 1 stop bit
  *                         UART_STOPBITS_1_5 - 1.5 stop bit (SYNC = 0) or reserved (SYNC = 1)
  *                         UART_STOPBITS_2   - 2 stop bits
  * @retval None
  */
void UART_StopBit_Cfg(USART_TypeDef* UARTx, uint32_t UART_StopBits)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_STOPBITS(UART_StopBits));

    /* Clear the number of stop bits by clearing the NBSTOP[13:12] bits in the MR register */
    UARTx->MR &= (uint32_t)~((uint32_t)USART_MR_NBSTOP);

    /* Set the number of stop bits by setting the NBSTOP[13:12] bits in the MR register    */
    UARTx->MR |= (uint32_t)((uint32_t)UART_StopBits);
}

/**
  * @brief  Parity type
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  UART_Parity: Parity type
  *         This parameter can be one of the following values:
  *                         UART_PARITY_EVEN      - Even parity
  *                         UART_PARITY_ODD       - Odd parity
  *                         UART_PARITY_SPACE     - Parity forced to 0 (space)
  *                         UART_PARITY_MARK      - Parity forced to 1 (mark)
  *                         UART_PARITY_NONE      - No parity
  *                         UART_PARITY_MULTIDROP - Multidrop mode
  * @retval None
  */
void UART_Parity_Cfg(USART_TypeDef* UARTx, uint32_t UART_Parity)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_PARITY(UART_Parity));

    /* Clear the parity type by clearing the PAR[11:9] bits in the MR register */
    UARTx->MR &= (uint32_t)~((uint32_t)USART_MR_PAR);

    /* Set the parity type by setting the PAR[11:9] bits in the MR register    */
    UARTx->MR |= (uint32_t)((uint32_t)UART_Parity);
}

/**
  * @brief  Character length
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  UART_WordLength: character length
  *         This parameter can be one of the following values:
  *                         UART_CHAR_LENGTH_5BIT - character length is 5 bits
  *                         UART_CHAR_LENGTH_6BIT - character length is 6 bits
  *                         UART_CHAR_LENGTH_7BIT - character length is 7 bits
  *                         UART_CHAR_LENGTH_8BIT - character length is 8 bits
  * @retval None
  */
void UART_DataLength_Cfg(USART_TypeDef* UARTx, uint32_t UART_WordLength)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_CHAR_LENGTH(UART_WordLength));

    /* Clear the character length by clearing the CHRL[7:6] bits in the MR register */
    UARTx->MR &= (uint32_t)~((uint32_t)USART_MR_CHRL);

    /* Set the character length by setting the CHRL[7:6] bits in the MR register    */
    UARTx->MR |= (uint32_t)((uint32_t)UART_WordLength);
}

/**
  * @brief  Clock selection
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  UART_CLKSelect: clock selection
  *         This parameter can be one of the following values:
  *                         UART_CLOCK_SELECT_MCK     - MCK
  *                         UART_CLOCK_SELECT_MCKDIV8 - MCK / 8
  * @retval None
  */
void UART_CLKSelect_Cfg(USART_TypeDef* UARTx, uint32_t UART_CLKSelect)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_CLOCK_SELECT(UART_CLKSelect));

    /* Clear the clock select by clearing the USCLKS[5:4] bits in the MR register */
    UARTx->MR &= (uint32_t)~((uint32_t)USART_MR_USCLKS);

    /* Set the clock select by setting the USCLKS[5:4] bits in the MR register    */
    UARTx->MR |= (uint32_t)((uint32_t)UART_CLKSelect);
}

/**
  * @brief  UART mode of operation
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  UART_OperationMode: UART mode of operation
  *         This parameter can be one of the following values:
  *                         UART_MODE_OPERATION_NORMAL      - Normal mode
  *                         UART_MODE_OPERATION_IrDA        - IrDA
  *                         UART_MODE_OPERATION_LIN_MASTER  - LIN master
  *                         UART_MODE_OPERATION_LIN_SLAVE   - LIN slave
  * @retval None
  */
void UART_OperationMode_Cfg(USART_TypeDef* UARTx, uint32_t UART_OperationMode)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_MODE_OPERATION(UART_OperationMode));

    /* Clear the UART mode of operation by clearing the USART_MODE[3:0] bits in the MR register */
    UARTx->MR &= (uint32_t)~((uint32_t)USART_MR_USART_MODE);

    /* Set the UART mode of operation by setting the USART_MODE[3:0] bits in the MR register    */
    UARTx->MR |= (uint32_t)((uint32_t)UART_OperationMode);
}

/**
  * @}
  */

/** @defgroup UART fractional baudrate function
  * @brief    UART fractional part of baudrate function
  *
@verbatim
 ===============================================================================
                     ##### Fractional Baudrate Functions #####
 ===============================================================================
    [..] This subsection provides a function, which can configure fractional part
         of baudrate.

    [..]

    (#) The fractional part of baudrate API's :
        (++) UART_FracDivider_Cfg()
@endverbatim
  * @{
  */

/**
  * @brief  UART fractional part of BaudRate
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  UART_BaudRate: user confige baudrate
  * @note   This function has to be called after calling UART_Init() function
  *         in order to have correct fractional part baudrate Divider value.
  * @retval None
  */
void UART_FracDivider_Cfg(USART_TypeDef* UARTx, uint32_t UART_BaudRate)
{
    double clock_divider = 0, frac_divider = 0, apbclock = 0;

    RCC_ClocksTypeDef RCC_ClocksStatus;

    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_UART_BAUDRATE(UART_BaudRate));

    RCC_GetClocksFreq(&RCC_ClocksStatus);

    /* Get UARTx work clock*/
    apbclock = RCC_ClocksStatus.PCLK_Frequency;

    /* BaudRate not equal 0*/
    if (UART_BaudRate >  0)
    {
        /* Async mode x16 Oversample*/
        if (((UARTx->MR)&USART_MR_OVER) == UART_OVERSAMPLING_16)
        {
            clock_divider = (uint32_t)(((apbclock) / ((UART_BaudRate) * 16)));
            frac_divider  = (uint32_t)(((apbclock) / ((UART_BaudRate) * 16) - clock_divider) * 8);
        }
        /* Async mode x8  Oversample*/
        if (((UARTx->MR)&USART_MR_OVER) == UART_OVERSAMPLING_8)
        {
            clock_divider = (uint32_t)(((apbclock) / ((UART_BaudRate) * 8)));
            frac_divider  = (uint32_t)(((apbclock) / ((UART_BaudRate) * 8) - clock_divider) * 8);
        }
    }

    /* Clear the UART fractional part by clearing the FP[18:16] bits in the BRGR register */
    UARTx->BRGR &= (uint32_t)~((uint32_t)USART_BRGR_FP);

    /* Set the UART fractional part by setting the FP[18:16] bits in the BRGR register    */
    UARTx->BRGR |= (((uint32_t)frac_divider) << 16U);
}

/**
  * @}
  */

/** @defgroup UART and LPUART BREAK command functions
  * @brief    None
  *
@verbatim
 ===============================================================================
                        ##### Break Command Functions #####
 ===============================================================================
    [..] This subsection provides a set of BREAK command functions.

    [..]

    (#) The stop break command API's :
        (++) UART_STPBRK_Cmd()

    (#) The start break command API's :
        (++) UART_STTBRK_Cmd()
@endverbatim
  * @{
  */

/**
  * @brief  Stop break.
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  NewState: new state of the UARTx stop break.
  *         This parameter can be:
  *           @arg ENABLE : Stops transmission of break after a minimum of one character length and
  *                         transmits a high level during 12-bit periods.
  *           @arg DISABLE: No effect
  * @retval None
  */
void UART_STPBRK_Cmd(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Stops transmission of break after a minimum of one character by setting
           STPBRK bit in the CR register */
        UARTx->CR |= USART_CR_STPBRK;
    }
    else
    {
        /* No effect */
        UARTx->CR &= (uint32_t)~((uint32_t)USART_CR_STPBRK);
    }
}

/**
  * @brief  Start break.
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  NewState: new state of the UARTx start break.
  *         This parameter can be:
  *           @arg ENABLE : Starts transmission of break after the character present in US_THR and
  *                         the transmit shift register have been transmitted. No effect if a break
  *                         is already being transmitted.
  *           @arg DISABLE: No effect
  * @retval None
  */
void UART_STTBRK_Cmd(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Starts transmission of break after the characters present in US_THR and the transmit
           shift register have been transmitted by setting STTBRK bit in the CR register */
        UARTx->CR |= USART_CR_STTBRK;
    }
    else
    {
        /* No effect */
        UARTx->CR &= (uint32_t)~((uint32_t)USART_CR_STTBRK);
    }
}

/**
  * @}
  */

/** @defgroup UART receiver time-out and transmitter timeguard functions
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
        (++) UART_Receiver_TimeOut_Cfg()

    (#) The receiver time-out cmd API's :
        (++) UART_RETTO_After_Timeout_Cmd()
        (++) UART_STTTO_After_Timeout_Cmd()

    (#) The transmitter timeguard cfg API's :
        (++) UART_Transmitter_TimeGuard_Cfg()
@endverbatim
  * @{
  */

/**
  * @brief  Receiver time-out value
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  UART_ReceiverTimeOut: Time-out value
  *                                0         : The receiver time-out is disabled.
  *                                1 - 65535 : The receiver time-out is enabled and time-out
  *                                            delay is TO * bit period.
  *                                1 - 131071: The receiver time-out is enabled and time-out
  *                                            delay is TO * bit period.
  * @note   This function has to be called before calling UART_Init() function
  *         in order to have correct receiver time-out value.
  * @retval None
  */
void UART_Receiver_TimeOut_Cfg(USART_TypeDef* UARTx, uint32_t UART_ReceiverTimeOut)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_UART_TIMEOUT(UART_ReceiverTimeOut));

    /* Clear the time-out value of receiver by clearing the TO[16:0] bits in the RTOR register */
    UARTx->RTOR &= (uint32_t)~((uint32_t)USART_RTOR_TO);

    /* Set the time-out value of receiver setting the TO[16:0] bits in the RTOR register       */
    UARTx->RTOR |= (uint32_t)((uint32_t)UART_ReceiverTimeOut);
}

/**
  * @brief  Rearm Time-out.
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  NewState: new state of the UARTx rearm Time-out.
  *         This parameter can be:
  *           @arg ENABLE : Restart Time-out
  *           @arg DISABLE: No effect
  * @retval None
  */
void UART_RETTO_After_Timeout_Cmd(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Restart time-out by setting RETTO bit in the CR register */
        UARTx->CR |= USART_CR_RETTO;
    }
    else
    {
        /* No effect */
        UARTx->CR &= (uint32_t)~((uint32_t)USART_CR_RETTO);
    }
}

/**
  * @brief  Start time-out.
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  NewState: new state of the UARTx start time-out.
  *         This parameter can be:
  *           @arg ENABLE : Starts waiting for a character before clocking the time-out counter.
  *                         Resets the status bit TIMEOUT in US_CSR.
  *           @arg DISABLE: No effect
  * @retval None
  */
void UART_STTTO_After_Timeout_Cmd(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Starts waiting for a character before clocking the time-out counter by setting
           STTTO bit in the CR register */
        UARTx->CR |= USART_CR_STTTO;
    }
    else
    {
        /* No effect */
        UARTx->CR &= (uint32_t)~((uint32_t)USART_CR_STTTO);
    }
}

/**
  * @brief  Transmitter timeguard value
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  UART_TransmitterTimeGuard: timeguard value
  *                                0      : The transmitter timeguard value is disabled.
  *                                1 - 255: The transmitter timeguard is enabled and the
  *                                         timeguard delay is TG * bit period.
  * @note   This function has to be called before calling UART_Init() function
  *         in order to have correct transmitter timeguard value.
  * @retval None
  */
void UART_Transmitter_TimeGuard_Cfg(USART_TypeDef* UARTx, uint32_t UART_TransmitterTimeGuard)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_UART_TIMGUARD(UART_TransmitterTimeGuard));

    /* Clear the timeguard value of transmitter by clearing the TG[7:0] bits in the TTGR register */
    UARTx->TTGR &= (uint32_t)~((uint32_t)USART_TTGR_TG);

    /* Set the timeguard value of transmitter setting the TG[7:0] bits in the TTGR register       */
    UARTx->TTGR |= (uint32_t)((uint32_t)UART_TransmitterTimeGuard);
}

/**
  * @}
  */

/** @defgroup UART and LPUART multidrop mode cmd function
  * @brief    Multidrop mode command function.
  *
@verbatim
 ===============================================================================
                   ##### Multidrop Mode Command Function #####
 ===============================================================================
    [..] This subsection provides the multidrop mode command function.

    [..]

    (#) The multidrop mode command API's :
        (++) UART_SENDAInMultidropMode_Cmd()

@endverbatim
  * @{
  */

/**
  * @brief  Send address.
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  NewState: new state of the UARTx send address.
  *         This parameter can be:
  *           @arg ENABLE : In multidrop mode only, the next character written to
  *                         the US_THR is sent with address bit set.
  *           @arg DISABLE: No effect
  * @retval None
  */
void UART_SENDAInMultidropMode_Cmd(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* In multidrop mode only, the next character writted to the US_THR is sent with
           address bit set by setting SENDA bit in the CR register */
        UARTx->CR |= USART_CR_SENDA;
    }
    else
    {
        /* No effect */
        UARTx->CR &= (uint32_t)~((uint32_t)USART_CR_SENDA);
    }
}

/**
  * @}
  */

/** @defgroup UART IrDA mode cfg functions
  * @brief    UART IrDA mode mode configuration function
  *
@verbatim
 ===============================================================================
                        ##### IrDA Mode Functions #####
 ===============================================================================
    [..] This subsection provides a IrDA mode function.

    [..]

    (#) The IrDA mode cfg API's :
        (++) UART_IrDAFilter_Cfg()

@endverbatim
  * @{
  */

/**
  * @brief  IrDA Filter
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  UART_IrDAFilter: The IRDA_FILTER value must be defined to meet the
  *         following criteria:
  *                             tMCK * (IDA_FILTER + 3) < 1.41us
  * @retval None
  */
void UART_IrDAFilter_Cfg(USART_TypeDef* UARTx, uint32_t UART_IrDAFilter)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_UART_IF(UART_IrDAFilter));

    /* Clear the IrDA filter value by clearing the IRDA_FILTER[7:0] bits in the IF register */
    UARTx->IF &= (uint32_t)~((uint32_t)USART_IF_IRDA_FILTER);

    /* Set the IrDA filter value by setting the IRDA_FILTER[7:0] bits in the IF register */
    UARTx->IF |= (uint32_t)((uint32_t)UART_IrDAFilter);
}

/**
  * @}
  */

/** @defgroup UART LIN mode cmd, cfg, and read functions
  * @brief    UART LIN mode mode command, configuration and read functions
  *
@verbatim
 ===============================================================================
                             ##### LIN Mode Functions #####
 ===============================================================================
    [..] This subsection provides a set of LIN mode functions.

    [..]

    (#) The LIN mode cmd API's :
        (++) UART_LINWKUP_Cmd()
        (++) UART_LINABT_Cmd()

    (#) The LIN mode cfg API's :
        (++) UART_Write_LINIR_In_LIN_Master()
        (++) UART_SYNCDisable_Cfg()
        (++) UART_PDCMode_Cfg()
        (++) UART_DataLengthControl_Cfg()
        (++) UART_WkupType_Cfg()
        (++) UART_FrameSlotDisable_Cfg()
        (++) UART_DataLengthMode_Cfg()
        (++) UART_CheckSumType_Cfg()
        (++) UART_CheckSumDisable_Cfg()
        (++) UART_ParityDisable_Cfg()
        (++) UART_NodeAction_Cfg()

    (#) The LIN mode read API's :
        (++) UART_Read_LINIR_In_LIN_Slave()
        (++) UART_LINBaudRate()
@endverbatim
  * @{
  */

/**
  * @brief  Send LIN Wakeup Signal.
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  NewState: new state of the UARTx send LIN wakeup signal.
  *         This parameter can be:
  *           @arg ENABLE : Sends a wakeup signal on LIN bus
  *           @arg DISABLE: No effect
  * @retval None
  */
void UART_LINWKUP_Cmd(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Send a wakeup signal on LIN bus by setting LINWKUP bit in the CR register */
        UARTx->CR |= USART_CR_LINWKUP;
    }
    else
    {
        /* No effect */
        UARTx->CR &= (uint32_t)~((uint32_t)USART_CR_LINWKUP);
    }
}

/**
  * @brief  Abort LIN Transmission.
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  NewState: new state of the UARTx abort LIN transmission.
  *         This parameter can be:
  *           @arg ENABLE : Abort LIN transmission
  *           @arg DISABLE: No effect
  * @retval None
  */
void UART_LINABT_Cmd(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Abort LIN transmission by setting LINABT bit in the CR register */
        UARTx->CR |= USART_CR_LINABT;
    }
    else
    {
        /* No effect */
        UARTx->CR &= (uint32_t)~((uint32_t)USART_CR_LINABT);
    }
}

/**
  * @brief  Write identifier character in LIN master mode
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  UART_LINIR_Data: if UART_OperationMode = 0xA (Master node configure),
  *                           UART_LINIR_Data is read-write and its value is the
  *                           identifier character to be transmitted.
  * @note   This function has to be called after calling UART_Init() function
  *         in order to have correct identifer value in LIN master mode.
  * @retval None
  */
void UART_Write_LINIR_In_LIN_Master(USART_TypeDef* UARTx, uint32_t UART_LINIR_Data)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_UART_LINIR_WR(UART_LINIR_Data));

    /* Clear the identifier value to be transmitted in LIN master node by clearing
       the IDCHR[7:0] bits in the LINIR register */
    UARTx->LINIR &= (uint32_t)~((uint32_t)USART_LINIR_IDCHR);

    /* Set the identifier value to be transmitted in LIN master node by setting
       the IDCHR[7:0] bits in the LINIR register */
    UARTx->LINIR |= (uint32_t)((uint32_t)UART_LINIR_Data);
}

/**
  * @brief  Synchronization disable in LIN mode
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  NewState: new state of the UARTx LIN synchronization disable,
  *         applicable if UART operates in LIN mode.
  *         This parameter can be:
  *           @arg ENABLE : The synchronization procedure is not performed in LIN
  *                         slave node configure.
  *           @arg DISABLE: The synchronization procedure is performed in LIN
  *                         slave node configure.
  * @retval None
  */
void UART_SYNCDisable_Cfg(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the synchronization procedure's disable by setting SYNCDIS bit in the LINMR register */
        UARTx->LINMR |= USART_LINMR_SYNCDIS;
    }
    else
    {
        /* Disable the synchronization procedure's disable by clearing SYNCDIS bit in the LINMR register */
        UARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_SYNCDIS);
    }
}

/**
  * @brief  DMA mode in LIN mode
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  NewState: new state of the UARTx LIN DMA mode, applicable if UART
  *         operates in LIN mode.
  *         This parameter can be:
  *           @arg ENABLE : The LIN mode register US_LINMR (excepting that flag)
  *                         is written by the DMA.
  *           @arg DISABLE: The LIN mode register US_LINMR is not written by the DMA.
  * @retval None
  */
void UART_PDCMode_Cfg(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the DMA written of LINMR by setting PDCM bit in the LINMR register */
        UARTx->LINMR |= USART_LINMR_PDCM;
    }
    else
    {
        /* Disable the DMA written of LINMR by clearing PDCM bit in the LINMR register */
        UARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_PDCM);
    }
}

/**
  * @brief  Data length control in LIN mode
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  UART_DataLengthControl: (0 - 255) Defines the response data length
  *                                 if UART_DataLengthMode = 0, in that case
  *                                 the response data length is equal to
  *                                 UART_DataLengthControl + 1 bytes;
  * @retval None
  */
void UART_DataLengthControl_Cfg(USART_TypeDef* UARTx, uint32_t UART_DataLengthControl)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_UART_DLC(UART_DataLengthControl));

    /* Clear the response data length value of LIN mode (UART_DataLengthMode = 0)
       by clearing the DLC[15:8] bits in the LINMR register */
    UARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_DLC);

    /* Set the response data length value of LIN mode (UART_DataLengthMode = 0)
       by setting the DLC[15:8] bits in the LINMR register */
    UARTx->LINMR |= (uint32_t)((uint32_t)UART_DataLengthControl << 8U);
}

/**
  * @brief  Wakeup signal type in LIN mode
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  NewState: new state of the UARTx LIN wakeup signal type.
  *         This parameter can be:
  *           @arg ENABLE : Setting the bit LINWKUP in the control register send
  *                         a LIN 1.3 wakeup signal.
  *           @arg DISABLE: Setting the bit LINWKUP in the control register send
  *                         a LIN 2.0 wakeup signal.
  * @retval None
  */
void UART_WkupType_Cfg(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the LIN 1.3 wakeup signal as the wakeup type to send by setting WKUPTYP
           bit in the LINMR register */
        UARTx->LINMR |= USART_LINMR_WKUPTYP;
    }
    else
    {
        /* Disable the LIN 1.3 wakeup signal as the wakeup type to send by clearing WKUPTYP
           bit in the LINMR register */
        UARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_WKUPTYP);
    }
}

/**
  * @brief  Frame slot mode disable in LIN mode
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  NewState: new state of the UARTx LIN frame slot mode disable.
  *         This parameter can be:
  *           @arg ENABLE : The frame slot mode is disabled.
  *           @arg DISABLE: The frame slot mode is enabled.
  * @retval None
  */
void UART_FrameSlotDisable_Cfg(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the frame slot mode's disable by setting FSDIS bit in the LINMR register */
        UARTx->LINMR |= USART_LINMR_FSDIS;
    }
    else
    {
        /* Disable the frame slot mode's disable by clearing FSDIS bit in the LINMR register */
        UARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_FSDIS);
    }
}

/**
  * @brief  Data length mode in LIN mode
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  NewState: new state of the UARTx LIN data length mode.
  *         This parameter can be:
  *           @arg ENABLE : The response data length is defined by the bits 5
  *                         and 6 of the identifier (IDCHR in US_LINIR).
  *           @arg DISABLE: The response data length is defined by the field
  *                         DLC of US_LINMR register.
  * @retval None
  */
void UART_DataLengthMode_Cfg(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the response data length is defined by the bits 5 and 6 of the identifier
           (IDCHR in US_LINIR) by setting DLM bit in the LINMR register */
        UARTx->LINMR |= USART_LINMR_DLM;
    }
    else
    {
        /* Disable the response data length is defined by the bits 5 and 6 of the identifier
           (IDCHR in US_LINIR) by clearing DLM bit in the LINMR register */
        UARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_DLM);
    }
}

/**
  * @brief  Checksum type in LIN mode
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  NewState: new state of the UARTx LIN checksum type.
  *         This parameter can be:
  *           @arg ENABLE : LIN 1.3 "Classic" checksum.
  *           @arg DISABLE: LIN 2.0 "Enhanced" checksum.
  * @retval None
  */
void UART_CheckSumType_Cfg(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the LIN 1.3 "Classic" checksum type by setting CHKTYP bit in the LINMR register */
        UARTx->LINMR |= USART_LINMR_CHKTYP;
    }
    else
    {
        /* Disable the LIN 1.3 "Classic" checksum type by clearing CHKTYP bit in the LINMR register */
        UARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_CHKTYP);
    }
}

/**
  * @brief  Checksum disable in LIN mode
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  NewState: new state of the UARTx LIN checksum disable.
  *         This parameter can be:
  *           @arg ENABLE : Whatever the node configuration is, the checksum is
  *                         not computed/sent and it is not checked.
  *           @arg DISABLE: In Master node configuration, the cheksum is computed
  *                         and sent automatically. In Slave node configure, the
  *                         checksum is checked automatically.
  * @retval None
  */
void UART_CheckSumDisable_Cfg(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the checksum's disable by setting CHKDIS bit in the LINMR register */
        UARTx->LINMR |= USART_LINMR_CHKDIS;
    }
    else
    {
        /* Disable the checksum's disable by clearing CHKDIS bit in the LINMR register */
        UARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_CHKDIS);
    }
}

/**
  * @brief  Parity disable in LIN mode
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  NewState: new state of the UARTx LIN parity disable.
  *         This parameter can be:
  *           @arg ENABLE : Whatever the node configuration is, the identifier
  *                         parity is not computed/sent and it is not checked.
  *           @arg DISABLE: In Master node configuration, the identifier parity
  *                         is computed and sent automatically. In Master node
  *                         and Slave node configuration, the parity is checked
  *                         automatically.
  * @retval None
  */
void UART_ParityDisable_Cfg(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the identifier parity's disable by setting PARDIS bit in the LINMR register */
        UARTx->LINMR |= USART_LINMR_PARDIS;
    }
    else
    {
        /* Disable the identifier parity's disable by clearing PARDIS bit in the LINMR register */
        UARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_PARDIS);
    }
}

/**
  * @brief  LIN node action
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @param  UART_NodeAction: LIN node action
  *         This parameter can be one of the following values:
  *                           UART_NODE_ACTIVE_PUBLISH   - PUBLISH  ; The UART transmits the response.
  *                           UART_NODE_ACTIVE_SUBSCRIBE - SUBSCRIBE; The UART receives the response.
  *                           UART_NODE_ACTIVE_IGNORE    - IGNORE   ; The UART does not transmits and
  *                                                                   does not receives the response.
  * @retval None
  */
void UART_NodeAction_Cfg(USART_TypeDef* UARTx, uint32_t UART_NodeAction)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));
    assert_param(IS_UART_NODE_ACTIVE(UART_NodeAction));

    /* Clear the LIN node action by clearing the NACT[1:0] bits in the LINMR register */
    UARTx->LINMR &= (uint32_t)~((uint32_t)USART_LINMR_NACT);

    /* Set the LIN node action by setting the NACT[1:0] bits in the LINMR register */
    UARTx->LINMR |= (uint32_t)((uint32_t)UART_NodeAction);
}

/**
  * @brief  Returns the identifier character by the UARTx peripheral.
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @note   If UART_OperationMode = 0xB (Slave node configuration), IDCHR[7:0]
  *         in US_LINIR is read-only and its value is the last identifier character
  *         that has been received.
  * @retval The last identifier character.
  */
uint32_t UART_Read_LINIR_In_LIN_Slave(USART_TypeDef* UARTx)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));

    /* Return the last identifier character if operation in slave node configuration*/
    return (uint32_t)((UARTx->LINIR));
}

/**
  * @brief  Returns the baud rate value after the synchronization process completion
  *         by the UARTx peripheral.
  * @param  UARTx: Select UART peripheral from among UART4, UART5 and UART7 (Except LPUART).
  * @note   The return value [18:16] bits is LINFP[18:16], which means fractional part
  *         after synchronization.
  * @note   The return value [15: 0] bits is LINCD[15: 0], which means clock driver
  *         after synchronization.
  * @retval The baud rate value after the synchronization process completion.
  */
uint32_t UART_LINBaudRate(USART_TypeDef* UARTx)
{
    /* Check the parameters */
    assert_param(IS_UART_457_PERIPH(UARTx));

    /* Return the baud rate value after the synchronization process completion */
    return (uint32_t)((UARTx->LINBRR));
}

/**
  * @}
  */

/** @defgroup UART and LPUART Transfers functions
  * @brief    UART and LPUART Transmit and Receive functions
  *
@verbatim
 ===============================================================================
                      ##### Data Transfers Functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the UART
         and LPUART data transfers.

    [..]

    (#) The UART and LPUART data transmit API's :
        (++) UART_Transmit()

    (#) The UART and LPUART data receive API's :
        (++) UART_Receive()
@endverbatim
  * @{
  */

/**
  * @brief  Transmits single data through the UARTx peripheral.
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  Data: the data to transmit.
  * @retval None
  */
void UART_Transmit(USART_TypeDef* UARTx, uint16_t Data)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_DATA(Data));

    /* Transmit Data */
    UARTx->THR = (Data & (uint16_t)0x01FF);
}

/**
  * @brief  Returns the most recent received data by the UARTx peripheral.
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @retval The received data.
  */
uint16_t UART_Receive(USART_TypeDef* UARTx)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));

    /* Received Data */
    return (uint16_t)(UARTx->RHR & (uint16_t)0x01FF);
}

/**
  * @}
  */

/** @defgroup UART and LPUART DMA Transfers functions
  * @brief    UART and LPUART DMA Transmit and Receive enable functions
  *
@verbatim
 ===============================================================================
                   ##### DMA Transfer Management Functions #####
 ===============================================================================
    [..] This subsection provides a set of functions about DMA Tx/Rx enable functions.

    [..]

    (#) The UART and LPUART DMA enable transmitter API's :
        (++) UART_DMATxEnable_Cmd()

    (#) The UART and LPUART DMA enable receiver API's :
        (++) UART_DMARxEnable_Cmd()
@endverbatim
  * @{
  */

/**
  * @brief  DMA enable transmitter
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  NewState: new state of the UARTx DMA enable transmitter.
  *         This parameter can be:
  *           @arg ENABLE : DMA mode is enable for transmission.
  *           @arg DISABLE: DMA mode is disable for transmission.
  * @retval None
  */
void UART_DMATxEnable_Cmd(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the transmission function of DMA mode by setting DMAT bit in the CR register */
        UARTx->CR |= USART_CR_DMAT_EN;
    }
    else
    {
        /* Disable the transmission function of DMA mode by clearing DMAT bit in the CR register */
        UARTx->CR &= (uint32_t)~((uint32_t)USART_CR_DMAT_EN);
    }
}

/**
  * @brief  DMA enable receiver
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  NewState: new state of the UARTx DMA enable receiver.
  *         This parameter can be:
  *           @arg ENABLE : DMA mode is enable for reception.
  *           @arg DISABLE: DMA mode is disable for reception.
  * @retval None
  */
void UART_DMARxEnable_Cmd(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the reception function of DMA mode by setting DMAR bit in the CR register */
        UARTx->CR |= USART_CR_DMAR_EN;
    }
    else
    {
        /* Disable the reception function of DMA mode by clearing DMAR bit in the CR register */
        UARTx->CR &= (uint32_t)~((uint32_t)USART_CR_DMAR_EN);
    }
}

/**
  * @}
  */

/** @defgroup UART and LPUART low-power management functions
  * @brief    UART low-power sleep wakeup functions
  *           LPUART low-power sleep or stop wakeup functions
  *
@verbatim
 ===============================================================================
        ##### Low-Power SLEEP and STOP Wakeup Management Functions #####
 ===============================================================================
    [..] This subsection provides a set of functions about UART and LPUART
         low-power wakeup management functions.

    [..]

    (#) The UART and LPUART Low-Power SLEEP wakeup configurations API's :
        (++) UART_LowPowerSleepWkupConfig()

    (#) The LPUART Low-Power STOP wakeup configurations API's :
        (++) LPUART_LowPowerStopWkupConfig()
@endverbatim
  * @{
  */

/**
  * @brief  UART and LPUART Low-Power SLEEP wakeup configurations
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  NewState: new state of the UARTx Low-Power SLEEP wakeup configurations.
  *         This parameter can be:
  *           @arg ENABLE : Enable UARTx module clock in SLEEP mode.
  *           @arg DISABLE: Disable UARTx module clock in SLEEP mode.
  * @retval None
  */
void UART_LowPowerSleepWkupConfig(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (UARTx == UART4)
    {
        if (NewState != DISABLE)
        {
            /* Enable the UART4 module clock in SLEEP mode by setting UART4LPEN bit in the
               RCC_APB1LPENR register */
            RCC_APB1PeriphLpenCmd(RCC_APB1PeriphLpen_UART4, ENABLE);
        }
        else
        {
            /* Disable the UART4 module clock in SLEEP mode by clearing UART4LPEN bit in the
               RCC_APB1LPENR register */
            RCC_APB1PeriphLpenCmd(RCC_APB1PeriphLpen_UART4, DISABLE);
        }
    }
    else if (UARTx == UART5)
    {
        if (NewState != DISABLE)
        {
            /* Enable the UART5 module clock in SLEEP mode by setting UART5LPEN bit in the
               RCC_APB1LPENR register */
            RCC_APB1PeriphLpenCmd(RCC_APB1PeriphLpen_UART5, ENABLE);
        }
        else
        {
            /* Disable the UART5 module clock in SLEEP mode by clearing UART5LPEN bit in the
               RCC_APB1LPENR register */
            RCC_APB1PeriphLpenCmd(RCC_APB1PeriphLpen_UART5, DISABLE);
        }
    }
    else if (UARTx == UART7)
    {
        if (NewState != DISABLE)
        {
            /* Enable the UART7 module clock in SLEEP mode by setting UART7LPEN bit in the
               RCC_APB1LPENR register */
            RCC_APB1PeriphLpenCmd(RCC_APB1PeriphLpen_UART7, ENABLE);
        }
        else
        {
            /* Disable the UART7 module clock in SLEEP mode by clearing UART7LPEN bit in the
               RCC_APB1LPENR register */
            RCC_APB1PeriphLpenCmd(RCC_APB1PeriphLpen_UART7, DISABLE);
        }
    }
    else if (UARTx == LPUART)
    {
        if (NewState != DISABLE)
        {
            /* Enable the LPUART module clock in SLEEP mode by setting LPUARTLPEN bit in the
               RCC_APB1LPENR register */
            RCC_APB1PeriphLpenCmd(RCC_APB1PeriphLpen_LPUART, ENABLE);
        }
        else
        {
            /* Disable the LPUART module clock in SLEEP mode by clearing LPUARTLPEN bit in the
               RCC_APB1LPENR register */
            RCC_APB1PeriphLpenCmd(RCC_APB1PeriphLpen_LPUART, DISABLE);
        }
    }
}

/**
  * @brief  LPUART Low-Power STOP wakeup configurations
  * @param  UARTx: UART peripheral only for LPUART.
  * @param  NewState: new state of the LPUART Low-Power STOP wakeup configurations.
  *         This parameter can be:
  *           @arg ENABLE : LSE as LPUART clock in STOP mode.
  *           @arg DISABLE: PCLK as LPUART clock in STOP mode.
  * @retval None
  */
void LPUART_LowPowerStopWkupConfig(USART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_LP_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* LSE as LPUART clock in STOP mode by setting LPUARTSEL bit in the RCC_CCIPR register */
        RCC_LPUARTCLKConfig(RCC_LPUARTCLK_LSE);
    }
    else
    {
        /* PCLK as LPUART clock in STOP mode by clearing LPUARTSEL bit in the RCC_CCIPR register */
        RCC_LPUARTCLKConfig(RCC_LPUARTCLK_PCLK);
    }
}

/**
  * @}
  */

/** @defgroup UART and LPUART Transfers functions
  * @brief    UART and LPUART Transmit and Receive functions
  *
@verbatim
 ===============================================================================
                ##### Interrupts And Flags Management Functions #####
 ===============================================================================
    [..] This subsection provides a set of functions, which is about the UART
         and LPUART interrupts and the flags management.

    [..]

    (#) The UART and LPUART interrupts enable API's :
        (++) UART_ITConfig()

    (#) The UART and LPUART flags status check API's :
        (++) UART_GetFlagStatus()

    (#) The UART and LPUART flags clear API's :
        (++) UART_ClearFlag()

    (#) The UART and LPUART interrupt mask check API's :
        (++) UART_GetITStatus()

    (#) The UART and LPUART interrupt disable API's :
        (++) UART_ITDisableConfig()
@endverbatim
  * @{
  */

/**
  * @brief  Enables the specified UART and LPUART interrupts.
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  UART_IT: specifies the UART interrupt sources to be enabled or disabled.
  *         This parameter can be one of the following values:
  *            @arg UART_IT_TXEMPTY: UART transmitter empty interruption
  *            @arg UART_IT_TIMEOUT: UART receiver time-out interruption
  *            @arg UART_IT_PARE   : UART parity error interruption
  *            @arg UART_IT_FRAME  : UART framing error interruption
  *            @arg UART_IT_OVER   : UART overrun error interruption
  *            @arg UART_IT_RXBRK  : UART break receive/end of break interruption
  *            @arg UART_IT_TXRDY  : UART transmitter ready interruption
  *            @arg UART_IT_RXRDY  : UART receiver ready interruption
  *            @arg UART_IT_LINHTE : UART LIN header timeout error interruption
  *            @arg UART_IT_LINSTE : UART LIN synch tolerance eror interruption
  *            @arg UART_IT_LINSNRE: UART LIN slave not response error interruption
  *            @arg UART_IT_LINCE  : UART LIN checksum error interruption
  *            @arg UART_IT_LINIPE : UART LIN identifier parity error interruption
  *            @arg UART_IT_LINISFE: UART LIN inconsistent synch field error interruption
  *            @arg UART_IT_LINBE  : UART LIN bit error interruption
  *            @arg UART_IT_LINTC  : UART LIN transfer completed interruption
  *            @arg UART_IT_LINID  : UART LIN identifier sent or LIN identifier received interruption
  *            @arg UART_IT_LINBK  : UART LIN break sent or LIN break received interruption
  *         The following values are only available for UART4, UART5 and UART7, not for LPUART:
  *            @arg UART_IT_TIMEOUT
  *            @arg UART_IT_LINHTE
  *            @arg UART_IT_LINSTE
  *            @arg UART_IT_LINSNRE
  *            @arg UART_IT_LINCE
  *            @arg UART_IT_LINIPE
  *            @arg UART_IT_LINISFE
  *            @arg UART_IT_LINBE
  *            @arg UART_IT_LINTC
  *            @arg UART_IT_LINID
  *            @arg UART_IT_LINBK
  * @param  NewState: new state of the specified UARTx interrupts.
  *         This parameter can be:
  *           @arg ENABLE : Enable corresponding interrupt.
  *           @arg DISABLE: No effect.
  * @retval None
  * @retval None
  */
void UART_ITConfig(USART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_ENABLE_IT(UART_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        UARTx->IER |= (uint32_t)((uint32_t)UART_IT);
    }
    else
    {
        UARTx->IER &= (uint32_t)~((uint32_t)UART_IT);
    }
}

/**
  * @brief  Checks whether the specified UART flag is set or not.
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  UART_FLAG: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg UART_FLAG_TXEMPTY: transmitter empty
  *            @arg UART_FLAG_TIMEOUT: receiver time-out
  *            @arg UART_FLAG_PARE   : parity error
  *            @arg UART_FLAG_FRAME  : framing error
  *            @arg UART_FLAG_OVER   : overrun error
  *            @arg UART_FLAG_RXBRK  : break receive/end of break
  *            @arg UART_FLAG_TXRDY  : transmitter ready
  *            @arg UART_FLAG_RXRDY  : receiver ready
  *            @arg UART_FLAG_LINHTE : LIN header timeout error
  *            @arg UART_FLAG_LINSTE : LIN synch tolerance eror
  *            @arg UART_FLAG_LINSNRE: LIN slave not response error
  *            @arg UART_FLAG_LINCE  : LIN checksum error
  *            @arg UART_FLAG_LINIPE : LIN identifier parity error
  *            @arg UART_FLAG_LINISFE: LIN inconsistent synch field error
  *            @arg UART_FLAG_LINBE  : LIN bit error
  *            @arg UART_FLAG_LINBLS : LIN bus line status
  *            @arg UART_FLAG_LINTC  : LIN transfer completed
  *            @arg UART_FLAG_LINID  : LIN identifier sent or LIN identifier received
  *            @arg UART_FLAG_LINBK  : LIN break sent or LIN break received
  *         The following values are only available for UART4, UART5 and UART7, not for LPUART:
  *            @arg UART_FLAG_TIMEOUT
  *            @arg UART_FLAG_LINHTE
  *            @arg UART_FLAG_LINSTE
  *            @arg UART_FLAG_LINSNRE
  *            @arg UART_FLAG_LINCE
  *            @arg UART_FLAG_LINIPE
  *            @arg UART_FLAG_LINISFE
  *            @arg UART_FLAG_LINBE
  *            @arg UART_FLAG_LINBLS
  *            @arg UART_FLAG_LINTC
  *            @arg UART_FLAG_LINID
  *            @arg UART_FLAG_LINBK
  * @retval The new state of UART_FLAG (SET or RESET).
  */
FlagStatus UART_GetFlagStatus(USART_TypeDef* UARTx, uint32_t UART_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_GET_FLAG(UART_FLAG));

    if ((UARTx->CSR & UART_FLAG) != (uint32_t)RESET)
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
  * @brief  Clears the UARTx's pending flags.
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  UART_FLAG: specifies the flag to clear.
  *         This parameter can be any combination of the following values:
  *            @arg UART_CLEAR_TXEMPTY:  transmitter empty interrupt clear
  *            @arg UART_CLEAR_TIMEOUT:  receiver time-out interrupt clear
  *            @arg UART_CLEAR_PARE   :  parity error interrupt clear
  *            @arg UART_CLEAR_FRAME  :  framing error interrupt clear
  *            @arg UART_CLEAR_OVER   :  overrun error interrupt clear
  *            @arg UART_CLEAR_RXBRK  :  break receive/end of break interrupt clear
  *            @arg UART_CLEAR_TXRDY  :  transmitter ready interrupt clear
  *            @arg UART_CLEAR_RXRDY  :  receiver ready interrupt clear
  *            @arg UART_CLEAR_LINHTE :  LIN header timeout error interrupt clear
  *            @arg UART_CLEAR_LINSTE :  LIN synch tolerance eror interrupt clear
  *            @arg UART_CLEAR_LINSNRE:  LIN slave not response error interrupt clear
  *            @arg UART_CLEAR_LINCE  :  LIN checksum error interrupt clear
  *            @arg UART_CLEAR_LINIPE :  LIN identifier parity error interrupt clear
  *            @arg UART_CLEAR_LINISFE:  LIN inconsistent synch field error interrupt clear
  *            @arg UART_CLEAR_LINBE  :  LIN bit error interrupt clear
  *            @arg UART_CLEAR_LINTC  :  LIN transfer completed interrupt clear
  *            @arg UART_CLEAR_LINID  :  LIN identifier sent or LIN identifier received interrupt clear
  *            @arg UART_CLEAR_LINBK  :  LIN break sent or LIN break received interrupt clear
  *         The following values are only available for UART4, UART5 and UART7, not for LPUART:
  *            @arg UART_CLEAR_TIMEOUT
  *            @arg UART_CLEAR_LINHTE
  *            @arg UART_CLEAR_LINSTE
  *            @arg UART_CLEAR_LINSNRE
  *            @arg UART_CLEAR_LINCE
  *            @arg UART_CLEAR_LINIPE
  *            @arg UART_CLEAR_LINISFE
  *            @arg UART_CLEAR_LINBE
  *            @arg UART_CLEAR_LINTC
  *            @arg UART_CLEAR_LINID
  *            @arg UART_CLEAR_LINBK
  * @note   LINBLS LIN bus line status bit is cleared when LINRX pin is 0.
  * @note   TXEMPTY flag bit also can be cleared by a write to the US_THR register (UART_Transmit()).
  * @note   TXRDY flag bit also can be cleared by a write to the US_THR register (UART_Transmit()).
  * @note   RXRDY flag bit also can be cleared by a read to the US_RHR register (UART_Receive()).
  * @retval None
  */
void UART_ClearFlag(USART_TypeDef* UARTx, uint32_t UART_FLAG)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_CLEAR_FLAG(UART_FLAG));

    UARTx->CR |= (uint32_t)UART_FLAG;
}

/**
  * @brief  Checks whether the specified UART interrupt has enabled or disabled.
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  UART_IT: specifies the UART interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg UART_MASK_TXEMPTY:  transmitter empty interrupt mask
  *            @arg UART_MASK_TIMEOUT:  receiver time-out interrupt mask
  *            @arg UART_MASK_PARE   :  parity error interrupt mask
  *            @arg UART_MASK_FRAME  :  framing error interrupt mask
  *            @arg UART_MASK_OVER   :  overrun error interrupt mask
  *            @arg UART_MASK_RXBRK  :  break receive/end of break interrupt mask
  *            @arg UART_MASK_TXRDY  :  transmitter ready interrupt mask
  *            @arg UART_MASK_RXRDY  :  receiver ready interrupt mask
  *            @arg UART_MASK_LINHTE :  LIN header timeout error interrupt mask
  *            @arg UART_MASK_LINSTE :  LIN synch tolerance eror interrupt mask
  *            @arg UART_MASK_LINSNRE:  LIN slave not response error interrupt mask
  *            @arg UART_MASK_LINCE  :  LIN checksum error interrupt mask
  *            @arg UART_MASK_LINIPE :  LIN identifier parity error interrupt mask
  *            @arg UART_MASK_LINISFE:  LIN inconsistent synch field error interrupt mask
  *            @arg UART_MASK_LINBE  :  LIN bit error interrupt mask
  *            @arg UART_MASK_LINTC  :  LIN transfer completed interrupt mask
  *            @arg UART_MASK_LINID  :  LIN identifier sent or LIN identifier received interrupt mask
  *            @arg UART_MASK_LINBK  :  LIN break sent or LIN break received interrupt mask
  *         The following values are only available for UART4, UART5 and UART7, not for LPUART:
  *            @arg UART_MASK_TIMEOUT
  *            @arg UART_MASK_LINHTE
  *            @arg UART_MASK_LINSTE
  *            @arg UART_MASK_LINSNRE
  *            @arg UART_MASK_LINCE
  *            @arg UART_MASK_LINIPE
  *            @arg UART_MASK_LINISFE
  *            @arg UART_MASK_LINBE
  *            @arg UART_MASK_LINTC
  *            @arg UART_MASK_LINID
  *            @arg UART_MASK_LINBK
  * @retval The new state of UART_IT (SET or RESET).
  */
ITStatus UART_GetITStatus(USART_TypeDef* UARTx, uint32_t UART_IT)
{
    ITStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_GET_IT(UART_IT));

    if ((UARTx->IMR & UART_IT) != (uint32_t)RESET)
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
  * @brief  UARTx's interrupt disable configure.
  * @param  UARTx: Select UART peripheral from among UART4, UART5, UART7 and LPUART.
  * @param  UART_IT: specifies the interrupt pending bit to clear.
  *         This parameter can be one of the following values:
  *           @arg UART_DIS_TXEMPTY:  transmitter empty interrupt disable
  *           @arg UART_DIS_TIMEOUT:  receiver time-out interrupt disable
  *           @arg UART_DIS_PARE   :  parity error interrupt disable
  *           @arg UART_DIS_FRAME  :  framing error interrupt disable
  *           @arg UART_DIS_OVER   :  overrun error interrupt disable
  *           @arg UART_DIS_RXBRK  :  break receive/end of break interrupt disable
  *           @arg UART_DIS_TXRDY  :  transmitter ready interrupt disable
  *           @arg UART_DIS_RXRDY  :  receiver ready interrupt disable
  *           @arg UART_DIS_LINHTE :  LIN header timeout error interrupt disable
  *           @arg UART_DIS_LINSTE :  LIN synch tolerance eror interrupt disable
  *           @arg UART_DIS_LINSNRE:  LIN slave not response error interrupt disable
  *           @arg UART_DIS_LINCE  :  LIN checksum error interrupt disable
  *           @arg UART_DIS_LINIPE :  LIN identifier parity error interrupt disable
  *           @arg UART_DIS_LINISFE:  LIN inconsistent synch field error interrupt disable
  *           @arg UART_DIS_LINBE  :  LIN bit error interrupt disable
  *           @arg UART_DIS_LINTC  :  LIN transfer completed interrupt disable
  *           @arg UART_DIS_LINID  :  LIN identifier sent or LIN identifier received interrupt disable
  *           @arg UART_DIS_LINBK  :  LIN break sent or LIN break received interrupt disable
  *         The following values are only available for UART4, UART5 and UART7, not for LPUART:
  *            @arg UART_DIS_TIMEOUT
  *            @arg UART_DIS_LINHTE
  *            @arg UART_DIS_LINSTE
  *            @arg UART_DIS_LINSNRE
  *            @arg UART_DIS_LINCE
  *            @arg UART_DIS_LINIPE
  *            @arg UART_DIS_LINISFE
  *            @arg UART_DIS_LINBE
  *            @arg UART_DIS_LINTC
  *            @arg UART_DIS_LINID
  *            @arg UART_DIS_LINBK
  * @param  NewState: new state of the specified UARTx interrupts.
  *         This parameter can be:
  *           @arg ENABLE : Disable corresponding interrupt.
  *           @arg DISABLE: No effect.
  * @retval None
  */
void UART_ITDisableConfig(USART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_CLEAR_IT(UART_IT));

    if (NewState != DISABLE)
    {
        UARTx->IDR |= (uint32_t)((uint32_t)UART_IT);
    }
    else
    {
        UARTx->IDR &= (uint32_t)~((uint32_t)UART_IT);
    }
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
