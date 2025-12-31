/**
  **************************************************************************
  * @file      ft32f4xx_eth.c
  * @author    xcao
  * @brief     ssi module driver
  *            This file provides firmware functions to manage the following
  *            functionalities of the ssi peripheral:
  *             + Initialization and deinitialization functions
  *             + IO operation :functions
  *             + Peripheral Control funtions
  *             + Peripheral State and Errors functions
  *
  **************************************************************************
  * @attention
  *
  **************************************************************************
  @verbatim
  ==============================================================================
                  ##### How to use this driver #####
  ==============================================================================

  [..]
    The SSI driver can be used as follows:

    (#) Declare a SSI_HandleTypeDef handle structure (eg. SSI_HandleTypeDef hssi).
    (#) Initialize the SSI low level resources by implementing the SSI_MspInit() API:
        (##) ENABLE the SSI interface clock.
        (##) SSI pins configuration:
            (+++) ENABLE the clock for the SSI GPIOs.
            (+++) Configure these SSI pins as alternate function pull-up.
        (##) NVIC configuration if you need to use interrupt process (SSI_Transmit_IT()
             and SSI_Receive_IT() APIs):
            (+++) Configure the SSI interrupt priority.
            (+++) ENABLE the NVIC SSI IRQ handle.

  [..]
    (@) The specific SSI interrupts (FIFO request and Overrun underrun interrupt)
        will be managed using the macros __SSI_ENABLE_IT() and __SSI_DISABLE_IT()
        inside the transmit and receive process.


  [..]
    Two operation modes are available within this driver :

    *** Polling mode IO operation ***
    =================================
    [..]
      (+) Send an amount of data in blocking mode using _SSI_Transmit()
      (+) Receive an amount of data in blocking mode using _SSI_Receive()

    *** Interrupt mode IO operation ***
    ===================================


  @endverbatim
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_ssi.h"
#include "ft32f4xx_misc.h"
#define MAX_DELAY   0xFFFF
/** @addtogroup FT32F4xx__Driver
  * @{
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup SSI_Private_Functions  SSI Private Functions
  * @{
  */
static void TxClkFreqSet(SSI_HandleTypeDef *ssi, SSI_TxInitTypeDef *ssi_txinit);
static void RxClkFreqSet(SSI_HandleTypeDef *ssi, SSI_RxInitTypeDef *ssi_rxinit);
static void SSI_Fifo0Tx(SSI_HandleTypeDef *ssi, SSI_TxInitTypeDef *ssi_txinit, uint32_t Timeout, uint32_t tickstart);
static void SSI_Fifo1Tx(SSI_HandleTypeDef *ssi, SSI_TxInitTypeDef *ssi_txinit, uint32_t Timeout, uint32_t tickstart);
static void SSI_STX0Tx(SSI_HandleTypeDef *ssi, SSI_TxInitTypeDef *ssi_txinit, uint32_t Timeout, uint32_t tickstart);
static void SSI_SRX0Rx(SSI_HandleTypeDef *ssi, SSI_RxInitTypeDef *ssi_rxinit, uint32_t Timeout, uint32_t tickstart);
static void SSI_Fifo0Rx(SSI_HandleTypeDef *ssi, SSI_RxInitTypeDef *ssi_rxinit, uint32_t Timeout, uint32_t tickstart);
static void SSI_Fifo1Rx(SSI_HandleTypeDef *ssi, SSI_RxInitTypeDef *ssi_rxinit, uint32_t Timeout, uint32_t tickstart);
static void SSI_STX0Rx(SSI_HandleTypeDef *ssi, SSI_RxInitTypeDef *ssi_rxinit, uint32_t Timeout, uint32_t tickstart);
static void SSI_FillDfifo(SSI_HandleTypeDef *ssi, SSI_TxInitTypeDef *ssi_txinit);
static void SSI_FillFifo_0(SSI_HandleTypeDef *ssi, SSI_TxInitTypeDef *ssi_txinit);
static void SSI_FillFifo_1(SSI_HandleTypeDef *ssi, SSI_TxInitTypeDef *ssi_txinit);
/* Exported functions ---------------------------------------------------------*/
/** @defgroup SSI_Exported_Functions SSI Exported Functions
  * @{
  */

/** @defgroup SSI_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief    Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
            ##### Initialization and de-initialization functions #####
 ===============================================================================
  [..]  This subsection provides a set of functions allowing to initialize and
        de-initialize the SSI peripheral:

      (+) User must implement SSI_MspInit() function in which he configures
          all related peripherals resources (CLOCK, GPIO, DMA, IT and NVIC ).

      (+) Call the function SSI_Init() to configure the selected device with
          the selected configuration:
        (++) Mode (Normal/Net/I2S/AC97)
        (++) Data Size
        (++) Bit clk frequency
        (++) FIFO Threshold
        (++) Frame Config
        (++) Slot Config

@endverbatim
  * @{
  */


/**
  * @brief  Initialize the SSI according to the specified parameters.
  *         in the SSI_InitTypeDef structure and initialize the associated handle.
  * @param  ssi pointer to a SSI_HandleTypeDef structure that contains
  *               the configuration information for SSI module.
  * @param  ssi_init pointer to a SSI_InitTypeDef structure that contains
  *         the SSI initialization information
  * @param  ssi_txinit pointer to a SSI_TxInitTypeDef structure that contains
  *         the SSI Tx initialization information
  * @param  ssi_rxinit pointer to a SSI_RxInitTypeDef structure that contains
  *         the SSI Rx initialization information
  * @retval void
  */
void SSI_Init(SSI_HandleTypeDef *ssi,
              SSI_InitTypeDef *ssi_init,
              SSI_TxInitTypeDef *ssi_txinit,
              SSI_RxInitTypeDef *ssi_rxinit)
{
    uint32_t temreg = (uint32_t)0U;

    /* Check the SSI parameters */
    assert_param(IS_SSI_MODE(ssi_init->Mode));

    if (ssi->State == SSI_STATE_RESET)
    {
        /* Init the low level hardware : GPIO, CLOCK, NVIC and DMA */
        SSI_MspInit(ssi);
        printf("Low level initialization finish!\n");
    }

    ssi->State = SSI_STATE_BUSY;

    /*Disable SSI*/
    ssi->Instance->SCR &= ~SSI_SCR_SSIEN;

    switch (ssi_init->Mode)
    {
    case NET :
    {
        temreg |= (uint32_t)SSI_SCR_NET;
    }
    break;
    case I2S_MASTER :
    {
        temreg |= (uint32_t)I2S_MASTER_PARAM;
    }
    break;
    case I2S_SLAVE:
    {
        temreg |= (uint32_t)I2S_SLAVE_PARAM;
    }
    case AC97:
    {
        assert_param(IS_SSI_AC97SLOTWIDTH(ssi_init->AC97SLOTWIDTH));
    }
    break;
    default:
        break;
    }

    if (ssi_init->SyncMode == ENABLE)
    {
        temreg |= (uint32_t)SSI_SCR_SYN;
    }

    if (ssi_init->TCHEN == ENABLE)
    {
        temreg |= (uint32_t)SSI_SCR_TCH_EN;
    }

    if (ssi_init->OVERSAMPLE == ENABLE)
    {
        temreg |= (uint32_t)SSI_SCR_SYS_CLK_EN;
    }

    if (ssi_init->RFRCLKDIS == ENABLE)
    {
        temreg |= (uint32_t)SSI_SCR_RFR_CLK_DIS;
    }

    if (ssi_init->TFRCLKDIS == ENABLE)
    {
        temreg |= (uint32_t)SSI_SCR_TFR_CLK_DIS;
    }

    ssi->Instance->SCR &= (uint32_t)(~(SSI_SCR_RFR_CLK_DIS | SSI_SCR_TFR_CLK_DIS
                                       | SSI_SCR_TCH_EN | SSI_SCR_SYS_CLK_EN
                                       | SSI_SCR_I2SMODE | SSI_SCR_SYN | SSI_SCR_NET
                                       | SSI_SCR_TE | SSI_SCR_RE));

    if (ssi_init->Mode == AC97)
    {
        ssi->Instance->STCCR &= (uint32_t)(~(SSI_STCCR_WL | SSI_STCCR_DC));
        ssi->Instance->SRCCR &= (uint32_t)(~(SSI_SRCCR_WL | SSI_SRCCR_DC));

        /*AC97 word lenth can only set to 16 or 20 , and frame length can only set to 13 slots*/
        if (ssi_init->AC97SLOTWIDTH == SLOTWIDEQ20)
        {
            ssi->Instance->STCCR |= (uint32_t)((SSI_DATA_WL20 << 13U) | (SSI_FRAME_LEN12 << 8U));
            ssi->Instance->SRCCR |= (uint32_t)((SSI_DATA_WL20 << 13U) | (SSI_FRAME_LEN12 << 8U));
        }
        else if (ssi_init->AC97SLOTWIDTH == SLOTWIDEQ16)
        {
            ssi->Instance->STCCR |= (uint32_t)((SSI_DATA_WL16 << 13U) | (SSI_FRAME_LEN12 << 8U));
            ssi->Instance->SRCCR |= (uint32_t)((SSI_DATA_WL16 << 13U) | (SSI_FRAME_LEN12 << 8U));
        }

        ssi->Instance->SACNT &= (uint32_t)(~(SSI_SACNT_FRDIV | SSI_SACNT_TIF
                                             | SSI_SACNT_FV | SSI_SACNT_AC97EN));

        /*AC97 frame rate divider*/
        ssi->Instance->SACNT |= (uint32_t)((ssi_init->AC97FRDIV) << 5U);

        if (ssi_init->AC97RXTAGINFIFO == ENABLE)
        {
            ssi->Instance->SACNT |= SSI_SACNT_TIF;
        }

        if (ssi_init->AC97VarMode == ENABLE)
        {
            ssi->Instance->SACNT |= SSI_SACNT_FV;
        }

    }

    ssi->Instance->SCR |= temreg | (uint32_t)SSI_SCR_SSIEN;

    ssi->State = SSI_STATE_READY;
}
/**
  * @}
  */


/**
  * @brief  Configure TX bit clock frequency using specified parameters.
  * @param  ssi pointer to a SSI_HandleTypeDef structure that contains
  *         the configuration information for SSI module
  *
  * @param  ssi_txinit pointer to a SSI_TxInitTypeDef structure that contains
  *         the SSI initialization information
  * @retval NONE
  */
static void TxClkFreqSet(SSI_HandleTypeDef *ssi, SSI_TxInitTypeDef *ssi_txinit)
{
    uint32_t temreg = (uint32_t)0U;

    assert_param(IS_SSI_BITCLK_FIXDIV(ssi_txinit->FixedDivParam));
    assert_param(IS_SSI_DATA_SIZE(ssi_txinit->DataSize));

    /*Configure bit clock frequency using the following formula :
      f(Bit_clk) = f(ssi_system_clk(pll2_q)) / ((DIV2 + 1) * ((PSR * 7)+1) * ((PM + 1)*2))
      DIV2 and PSR are bit configuration option which belongs fixed prescaler paramter.
      PM can be modify by usrs according to application.
     */

    /* Note:f(Bit_clk) is never greater than 1/5 of the f(pclk1)  */

    switch (ssi_txinit->FixedDivParam)
    {
    case  FIX_CLOCK_DIV4:
    {
        temreg = (uint32_t)SSI_STCCR_DIV2;
    }
    break;
    case  FIX_CLOCK_DIV16:
    {
        temreg = (uint32_t)SSI_STCCR_PSR;
    }
    break;
    case  FIX_CLOCK_DIV32:
    {
        temreg = (uint32_t)(SSI_STCCR_DIV2 | SSI_STCCR_PSR);
    }
    break;
    default:
        break;
    }


    temreg |= (uint32_t)((ssi_txinit->CustomDivParam) & 0x000000ff);

    /* Configure Word clock */
    temreg |= (uint32_t)((ssi_txinit-> DataSize) << 13U);

    /* Configure Frame length */
    temreg |= (uint32_t)((ssi_txinit-> FrameRate) << 8U);

    ssi->Instance->STCCR &= (uint32_t)(~(SSI_STCCR_DIV2 | SSI_STCCR_PSR
                                         | SSI_STCCR_WL  | SSI_STCCR_DC
                                         | SSI_STCCR_PM));
    ssi->Instance->STCCR |= temreg;
}


/**
  * @brief  Configure RX bit clock frequency using specified parameters.
  * @param  ssi pointer to a SSI_HandleTypeDef structure that contains
  *         the configuration information for SSI module
  *
  * @param  ssi_rxinit pointer to a SSI_RxInitTypeDef structure that contains
  *         the SSI Rx initialization information
  * @retval NONE
  */
static void RxClkFreqSet(SSI_HandleTypeDef *ssi, SSI_RxInitTypeDef *ssi_rxinit)
{
    uint32_t temreg = (uint32_t)0U;

    assert_param(IS_SSI_BITCLK_FIXDIV(ssi_rxinit->FixedDivParam));
    assert_param(IS_DATA_SIZE(ssi_rxinit->DataSize));

    /*Configure bit clock frequency using the following formula :
      f(Bit_clk) = f(ssi_system_clk(pll2_q)) / ((DIV2 + 1) * ((PSR * 7)+1) * ((PM + 1)*2))
      DIV2 and PSR are bit configuration option which belongs fixed prescaler paramter.
      PM can be modify by usrs according to application.
     */

    /* Note:f(Bit_clk) is never greater than 1/5 of the f(pclk1)  */

    switch (ssi_rxinit->FixedDivParam)
    {
    case  FIX_CLOCK_DIV4:
    {
        temreg = (uint32_t)SSI_SRCCR_DIV2;
    }
    break;
    case  FIX_CLOCK_DIV16:
    {
        temreg = (uint32_t)SSI_SRCCR_PSR;
    }
    break;
    case  FIX_CLOCK_DIV32:
    {
        temreg = (uint32_t)(SSI_SRCCR_DIV2 | SSI_SRCCR_PSR);
    }
    break;
    default:
        break;
    }


    temreg |= (uint32_t)((ssi_rxinit->CustomDivParam) & 0x000000ff);


    /* Configure Word clock */
    temreg |= (uint32_t)((ssi_rxinit->DataSize) << 13U);

    /* Configure Frame length */
    temreg |= (uint32_t)((ssi_rxinit->FrameRate) << 8U);

    ssi->Instance->SRCCR &= (uint32_t)(~(SSI_SRCCR_DIV2 | SSI_SRCCR_PSR
                                         | SSI_SRCCR_WL  | SSI_SRCCR_DC
                                         | SSI_SRCCR_PM));
    ssi->Instance->SRCCR |= temreg;
}

/** @addtogroup SSI_Private_Functions  SSI Private Functions
  * @{
  */




/**
  * @brief  Configure Transmit initial flow .
  * @param  ssi pointer to a SSI_HandleTypeDef structure that contains
  *         the configuration information for SSI module
  *
  * @param  ssi_txinit pointer to a SSI_TxInitTypeDef structure that contains
  *         the SSI Tx initialization information
  * @retval NONE
  */
void TxConfigInit(SSI_HandleTypeDef *ssi, SSI_InitTypeDef *ssi_init, SSI_TxInitTypeDef *ssi_txinit)
{
    uint32_t temreg1 = (uint32_t)0U;
    uint32_t temreg2 = (uint32_t)0U;

    assert_param(IS_SSI_TRANSDATA_TYPE(ssi_txinit->TxDataType));
    assert_param(IS_SSI_FIFO_WATERMARK(ssi_txinit->FIFO0WaterMark));
    assert_param(IS_SSI_FIFO_WATERMARK(ssi_txinit->FIFO1WaterMark));
    assert_param(IS_SSI_FRAMESYNC_POLARITY(ssi_txinit->FrameSyncPolarity));
    assert_param(IS_SSI_CLOCK_POLARITY(ssi_txinit->TxClkPolarity));

    /* ENABLE Tx FIFO */
    /* Configure Tx FIFO Water Mark */
    if (ssi_txinit->FIFO0EN == ENABLE)
    {
        temreg1 |= (uint32_t)(SSI_STCR_TFEN0);
        temreg2 |= ssi_txinit->FIFO0WaterMark;
    }

    if (ssi_txinit->FIFO1EN == ENABLE)
    {
        temreg1 |= (uint32_t)(SSI_STCR_TFEN1);
        temreg2 |= (uint32_t)(ssi_txinit->FIFO1WaterMark << 16U);
    }

    /*Configure Tx data MSB or LSB transmission*/
    switch (ssi_txinit->TxDataType)
    {
    case  MSB_MSW:
    {
        temreg1 &= (uint32_t)(~(SSI_STCR_TXBIT0 | SSI_STCR_TSHFD));
    }
    break;
    case  LSB_MSW:
    {
        temreg1 |= (uint32_t)SSI_STCR_TSHFD;
        temreg1 &= (uint32_t)(~(SSI_STCR_TXBIT0));
    }
    break;
    case  MSB_LSW:
    {
        temreg1 &= (uint32_t)(~(SSI_STCR_TSHFD));
        temreg1 |= (uint32_t)SSI_STCR_TXBIT0;
    }
    break;
    default:
        break;
    }


    /* Configure frame sync direction */
    if (ssi_txinit->FrameSyncFromExit != ENABLE)
    {
        temreg1 |= (uint32_t)SSI_STCR_TFDIR;
    }

    /* Configure Tx direction */
    if (ssi_txinit->TxClkFromExit != ENABLE)
    {
        temreg1 |= (uint32_t)SSI_STCR_TXDIR;
    }

    /* Configure Tx clock polarity */
    if (ssi_txinit->TxClkPolarity == FALLINGEDGE)
    {
        temreg1 |= (uint32_t)SSI_STCR_TSCKP;
    }

    /* Configure Frame sync Length mode*/
    if (ssi_txinit->FrameSyncLenBit == ENABLE)
    {
        temreg1 |= (uint32_t)SSI_STCR_TFSL;
    }

    /* Configure Frame sync early */
    if (ssi_txinit->FrameSyncEarly == ENABLE)
    {
        temreg1 |= (uint32_t)SSI_STCR_TEFS;
    }

    /* Configure Frame sync polarity */
    if (ssi_txinit->FrameSyncPolarity == ACTIVELOW)
    {
        temreg1 |= (uint32_t)SSI_STCR_TFSI;
    }

    ssi->Instance->STCR &= (uint32_t)(~(SSI_STCR_TFEN0   | SSI_STCR_TFEN1
                                        | SSI_STCR_TSHFD | SSI_STCR_TXBIT0
                                        | SSI_STCR_TFDIR | SSI_STCR_TXDIR
                                        | SSI_STCR_TSCKP | SSI_STCR_TEFS
                                        | SSI_STCR_TFSL  | SSI_STCR_TFSI));

    ssi->Instance->STCR |= temreg1;

    ssi->Instance->SFCSR &= (uint32_t)(~(SSI_SFCSR_TFWM0 | SSI_SFCSR_TFWM1));

    ssi->Instance->SFCSR |= temreg2;

    ssi->Instance->STMSK &= ~(SSI_STMSK_STMSK);

    ssi->Instance->STMSK = ssi_txinit->TxSlotMsk;

    /* fill tag register if AC97 fixed mode */
    if (ssi_init->Mode == AC97)
    {
        if (ssi_init->AC97VarMode != ENABLE)
        {
            ssi->Instance->SATAG &= ~(SSI_SATAG_SATAG);

            ssi->Instance->SATAG |= (uint32_t)(ssi_txinit->AC97TxSlotEn);
        }
        else
        {
            /* Disable all slots when initial ac97 tx flow at variable mode */
            ssi->Instance->SACCDIS |= SSI_SACCDIS_SACCDIS;
        }
    }

    TxClkFreqSet(ssi, ssi_txinit);

}

/**
  * @brief  Configure Receive initial flow .
  * @param  ssi pointer to a SSI_HandleTypeDef structure that contains
  *         the configuration information for SSI module
  *
  * @param  ssi_rxinit pointer to a SSI_RxInitTypeDef structure that contains
  *         the SSI Rx initialization information
  * @retval NONE
  */
void RxConfigInit(SSI_HandleTypeDef *ssi, SSI_RxInitTypeDef *ssi_rxinit)
{
    uint32_t temreg1 = (uint32_t)0U;
    uint32_t temreg2 = (uint32_t)0U;

    assert_param(IS_SSI_TRANSDATA_TYPE(ssi_rxinit->RxDataType));
    assert_param(IS_SSI_FIFO_WATERMARK(ssi_rxinit->FIFO0WaterMark));
    assert_param(IS_SSI_FIFO_WATERMARK(ssi_rxinit->FIFO1WaterMark));
    assert_param(IS_SSI_FRAMESYNC_POLARITY(ssi_rxinit->FrameSyncPolarity));
    assert_param(IS_SSI_CLOCK_POLARITY(ssi_rxinit->RxClkPolarity));

    /* ENABLE Rx FIFO */
    /* Configure Rx FIFO Water Mark */
    if (ssi_rxinit->FIFO0EN == ENABLE)
    {
        temreg1 |= (uint32_t)(SSI_SRCR_RFEN0);
        temreg2 |= (uint32_t)(ssi_rxinit->FIFO0WaterMark << 4U);
    }

    if (ssi_rxinit->FIFO1EN == ENABLE)
    {
        temreg1 |= (uint32_t)(SSI_SRCR_RFEN1);
        temreg2 |= (uint32_t)(ssi_rxinit->FIFO1WaterMark << 20U);
    }

    /*Configure Rx data MSB or LSB transmission*/
    switch (ssi_rxinit->RxDataType)
    {
    case  MSB_MSW:
    {
        temreg1 &= (uint32_t)(~(SSI_SRCR_RXBIT0 | SSI_SRCR_RSHFD));
    }
    break;
    case  LSB_MSW:
    {
        temreg1 |= (uint32_t)SSI_SRCR_RSHFD;
        temreg1 &= (uint32_t)(~(SSI_SRCR_RXBIT0));
    }
    break;
    case  MSB_LSW:
    {
        temreg1 &= (uint32_t)(~(SSI_SRCR_RSHFD));
        temreg1 |= (uint32_t)SSI_SRCR_RXBIT0;
    }
    break;
    default:
        break;
    }

    /* Configure frame sync direction */
    if (ssi_rxinit->FrameSyncFromExit != ENABLE)
    {
        temreg1 |= (uint32_t)SSI_SRCR_RFDIR;
    }

    /* Configure Rx direction */
    if (ssi_rxinit->RxClkFromExit != ENABLE)
    {
        temreg1 |= (uint32_t)SSI_SRCR_RXDIR;
    }

    /* Configure Rx clock polarity */
    if (ssi_rxinit->RxClkPolarity == FALLINGEDGE)
    {
        temreg1 |= (uint32_t)SSI_SRCR_RSCKP;
    }

    /* Configure Frame sync Length mode*/
    if (ssi_rxinit->FrameSyncLenBit == ENABLE)
    {
        temreg1 |= (uint32_t)SSI_SRCR_RFSL;
    }

    /* Configure Frame sync early */
    if (ssi_rxinit->FrameSyncEarly == ENABLE)
    {
        temreg1 |= (uint32_t)SSI_SRCR_REFS;
    }

    /* Configure Frame sync polarity */
    if (ssi_rxinit->FrameSyncPolarity == ACTIVELOW)
    {
        temreg1 |= (uint32_t)SSI_SRCR_RFSI;
    }

    ssi->Instance->SRCR &= (uint32_t)(~(SSI_SRCR_RFEN0   | SSI_SRCR_RFEN1
                                        | SSI_SRCR_RSHFD | SSI_SRCR_RXBIT0
                                        | SSI_SRCR_RFDIR | SSI_SRCR_RXDIR
                                        | SSI_SRCR_RSCKP | SSI_SRCR_REFS
                                        | SSI_SRCR_RFSL  | SSI_SRCR_RFSI));

    ssi->Instance->SRCR |= temreg1;

    ssi->Instance->SFCSR &= (uint32_t)(~(SSI_SFCSR_RFWM0 | SSI_SFCSR_RFWM1));

    ssi->Instance->SFCSR |= temreg2;

    ssi->Instance->SRMSK &= ~(SSI_SRMSK_SRMSK);

    ssi->Instance->SRMSK = ssi_rxinit->RxSlotMsk;

    RxClkFreqSet(ssi, ssi_rxinit);
}


/**
  * @brief Initialize the SSI MSP.
  * @param  ssi pointer to a SSI_HandleTypeDef structure that contains
  *               the configuration information for SSI module.
  * @retval None
  */
void __attribute__((weak)) SSI_MspInit(SSI_HandleTypeDef *ssi)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(ssi);

    /* NOTE : This function should not be modified, when the callback is needed,
              the HAL_SSI_MspInit could be implemented in the user file
     */
}


/**
  * @}
  */

/** @defgroup SSI_Exported_Functions_Group2 IO operation functions
  * @brief    Data transfers functions
  *
@verbatim
  ==============================================================================
                      ##### IO operation functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to manage the SSI data
    transfers.

    (+) There are two modes of transfer:
      (++) Blocking mode : The communication is performed in the polling mode.
           The status of all data processing is returned by the same function
           after finishing transfer.
      (++) No-Blocking mode : The communication is performed using Interrupts
           or DMA. These functions return the status of the transfer startup.
           The end of the data processing will be indicated through the
           dedicated SSI IRQ when using Interrupt mode or the DMA IRQ when
           using DMA mode.

    (+) Blocking mode functions are :
      (++) SSI_Transmit()
      (++) SSI_Receive()

@endverbatim
  * @{
  */

/**
  * @brief  Transmit an amount of data in polling mode.
  * @param  ssi pointer to a SSI_HandleTypeDef structure that contains
  *         the configuration information for SSI module.
  * @param  ssi_txinit pointer to a SSI_TxInitTypeDef structure that contains
  *         the SSI Tx initialization information
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @param  Timeout Timeout duration
  * @retval void
  *
  */
void SSI_Transmit(SSI_HandleTypeDef *ssi, \
                  SSI_InitTypeDef *ssi_init, \
                  SSI_TxInitTypeDef *ssi_txinit, \
                  uint8_t *pData0, \
                  uint8_t *pData1, \
                  uint16_t Size0, \
                  uint16_t Size1, \
                  uint32_t Timeout)
{
    uint32_t tickstart = GetTick();

    if (((pData0 == NULL) && (pData1 == NULL))
            || ((Size0 == 0)) && (Size1 == 0))
    {
        return;
    }

    if (ssi->State == SSI_STATE_READY)
    {
        ssi->XferSize0 = Size0;
        ssi->XferSize1 = Size1;
        ssi->XferCount0 = Size0;
        ssi->XferCount1 = Size1;
        ssi->pBuffPtr0 = pData0;
        ssi->pBuffPtr1 = pData1;
        ssi->State = SSI_STATE_BUSY_TX;
        ssi->ErrorCode = SSI_ERROR_NONE;

        if (ssi_init->Mode == AC97)
        {
            if ((ssi->Instance->SACNT & SSI_SACNT_AC97EN) != SSI_SACNT_AC97EN)
            {
                if (ssi_init->AC97VarMode == ENABLE)
                {
                    ssi->Instance->SACADD = (uint32_t)((ssi_txinit->CODECCMDADDR) & 0x0007ffff);
                    ssi->Instance->SACNT  |= SSI_SACNT_RD | SSI_SACNT_AC97EN;
                }
                else
                {
                    printf("CODEC ADDR = %08x\n", ((ssi_txinit->CODECCMDADDR) & 0x0007ffff));
                    printf("Write data = %08x\n", ((ssi_txinit->CODECCMDDATA) & 0x000fffff));
                    ssi->Instance->SACADD = (uint32_t)((ssi_txinit->CODECCMDADDR) & 0x0007ffff);
                    ssi->Instance->SACDAT = (uint32_t)((ssi_txinit->CODECCMDDATA) & 0x000fffff);
                    ssi->Instance->SACNT  |= SSI_SACNT_WR | SSI_SACNT_AC97EN;
                }
            }
            else if (ssi_init->AC97VarMode == ENABLE)
            {
                ssi->Instance->SACADD = (uint32_t)((ssi_txinit->CODECCMDADDR) & 0x0007ffff);
                ssi->Instance->SACDAT = (uint32_t)((ssi_txinit->CODECCMDDATA) & 0x000fffff);
                ssi->Instance->SACNT  |= SSI_SACNT_WR;

                uint32_t slotreq = ((ssi->Instance->SACCST) & 0x000003ff);

                ssi->Instance->SACCEN = slotreq;

                ssi->Instance->SACCDIS = slotreq;
            }
            else
            {
                ssi->Instance->SACADD = (uint32_t)((ssi_txinit->CODECCMDADDR) & 0x0007ffff);
                ssi->Instance->SACDAT = (uint32_t)((ssi_txinit->CODECCMDDATA) & 0x000fffff);
                ssi->Instance->SACNT  |= SSI_SACNT_WR;
            }
        }

        /* Prepare tx data before trasmit start */
        if ((ssi->Instance->SCR & SSI_SCR_TE) != SSI_SCR_TE)
        {
            if (ssi_init->TCHEN == ENABLE)
            {
                /* Two FIFOs are filled with data if enbale two channels */
                SSI_FillDfifo(ssi, ssi_txinit);
            }
            else if (ssi_txinit->FIFO0EN || ssi_init->Mode == AC97)
            {

                //printf("Use FIFO0 to transmit data!\n");
                /* Only channel 0 is enabled if single channel mode */
                SSI_FillFifo_0(ssi, ssi_txinit);
            }
            else
            {
                if ((ssi->Instance->SISR & SSI_SISR_TDE0) == SSI_SISR_TDE0)
                {
                    if (ssi_txinit->DataSize == SSI_DATA_WL8)
                    {
                        ssi->Instance->STX0 = (*ssi->pBuffPtr0++);
                    }
                    else if (ssi_txinit->DataSize == SSI_DATA_WL16)
                    {
                        ssi->Instance->STX0 = *((uint16_t *)(ssi->pBuffPtr0));
                        ssi->pBuffPtr0 += 2U;
                    }
                    else
                    {
                        ssi->Instance->STX0 = *((uint32_t *)(ssi->pBuffPtr0));
                        ssi->pBuffPtr0 += 4U;
                    }
                    ssi->XferCount0--;
                }
            }
            /* Start transmit */
            ssi->Instance->SCR |= SSI_SCR_TE;
            printf("Start transmit data!\n");
        }

        if (ssi_init->TCHEN == ENABLE)
        {
            while ((ssi->XferCount0 > 0U) || (ssi->XferCount1 > 0U))
            {
                if (ssi->XferCount0 > 0U)
                {
                    SSI_Fifo0Tx(ssi, ssi_txinit, Timeout, tickstart);
                }

                if (ssi->XferCount1 > 0U)
                {
                    SSI_Fifo1Tx(ssi, ssi_txinit, Timeout, tickstart);
                }
            }
        }
        else if ((ssi_txinit->FIFO0EN == ENABLE) || (ssi_init->Mode == AC97))
        {
            while (ssi->XferCount0 > 0U)
            {
                printf("Remain %d data need to be send!\n", ssi->XferCount0);
                SSI_Fifo0Tx(ssi, ssi_txinit, Timeout, tickstart);
            }
        }
        else
        {
            while (ssi->XferCount0 > 0U)
            {
                SSI_STX0Tx(ssi, ssi_txinit, Timeout, tickstart);
            }
        }

    }

    ssi->State = SSI_STATE_READY;

    while ((ssi->Instance->SISR & SSI_SISR_TUE0) != SSI_SISR_TUE0)
    {

    }

    ssi->Instance->SCR &= ~SSI_SCR_TE;
}


/**
  * @brief  Tx fifo_0 transmit function
  * @param  ssi pointer to a SSI_HandleTypeDef structure that contains
  *         the configuration information for SSI module.
  * @param  ssi_txinit pointer to a SSI_TxInitTypeDef structure that contains
  *         the SSI Tx initialization information
  * @param  Timeout Timeout duration
  * @param  tickstart Transmit start time
  * @retval None
  */
static void SSI_Fifo0Tx(SSI_HandleTypeDef *ssi, SSI_TxInitTypeDef *ssi_txinit, uint32_t Timeout, uint32_t tickstart)
{
    if (ssi->Instance->SISR & SSI_SISR_TFE0)
    {

        if (ssi_txinit->DataSize == SSI_DATA_WL8)
        {
            ssi->Instance->STX0 = (*ssi->pBuffPtr0++);
        }
        else if (ssi_txinit->DataSize == SSI_DATA_WL16)
        {
            ssi->Instance->STX0 = *((uint16_t *)(ssi->pBuffPtr0));
            ssi->pBuffPtr0 += 2U;
        }
        else
        {
            ssi->Instance->STX0 = *((uint32_t *)(ssi->pBuffPtr0));
            ssi->pBuffPtr0 += 4U;
        }
        ssi->XferCount0--;
    }
    else
    {
        if ((Timeout != MAX_DELAY) && ((Timeout == 0U) || ((GetTick() - tickstart) > Timeout)))
        {
            /* Update error code */
            ssi->ErrorCode |= SSI_ERROR_TIMEOUT;

            /* Disable SSI peripheral */
            ssi->Instance->SCR &= ~(SSI_SCR_TE);

            /* Flush the fifo */
            ssi->Instance->SOR |= SSI_SOR_TX_CLR;

            /* Change the SSI state */
            ssi->State = SSI_STATE_READY;

            return ;
        }
    }
}


/**
  * @brief  Tx fifo_1 transmit function
  * @param  ssi pointer to a SSI_HandleTypeDef structure that contains
  *         the configuration information for SSI module.
  * @param  ssi_txinit pointer to a SSI_TxInitTypeDef structure that contains
  *         the SSI Tx initialization information
  * @param  Timeout Timeout duration
  * @param  tickstart Transmit start time
  * @retval None
  */
static void SSI_Fifo1Tx(SSI_HandleTypeDef *ssi, SSI_TxInitTypeDef *ssi_txinit, uint32_t Timeout, uint32_t tickstart)
{
    if (ssi->Instance->SISR & SSI_SISR_TFE1)
    {
        if (ssi_txinit->DataSize == SSI_DATA_WL8)
        {
            ssi->Instance->STX1 = (*ssi->pBuffPtr1++);
        }
        else if (ssi_txinit->DataSize == SSI_DATA_WL16)
        {
            ssi->Instance->STX1 = *((uint16_t *)(ssi->pBuffPtr1));
            ssi->pBuffPtr1 += 2U;
        }
        else
        {
            ssi->Instance->STX1 = *((uint32_t *)(ssi->pBuffPtr1));
            ssi->pBuffPtr1 += 4U;
        }
        ssi->XferCount1--;
    }
    else
    {
        if ((Timeout != MAX_DELAY) && ((Timeout == 0U) || ((GetTick() - tickstart) > Timeout)))
        {
            /* Update error code */
            ssi->ErrorCode |= SSI_ERROR_TIMEOUT;

            /* Disable SSI peripheral */
            ssi->Instance->SCR &= ~(SSI_SCR_TE);

            /* Change the SSI state */
            ssi->State = SSI_STATE_READY;

            return ;
        }
    }
}

/**
  * @brief  Tx stx register transmit function
  * @param  ssi pointer to a SSI_HandleTypeDef structure that contains
  *         the configuration information for SSI module.
  * @param  ssi_txinit pointer to a SSI_TxInitTypeDef structure that contains
  *         the SSI Tx initialization information
  * @param  Timeout Timeout duration
  * @param  tickstart Transmit start time
  * @retval None
  */
static void SSI_STX0Tx(SSI_HandleTypeDef *ssi, SSI_TxInitTypeDef *ssi_txinit, uint32_t Timeout, uint32_t tickstart)
{
    if ((ssi->Instance->SISR & SSI_SISR_TDE0) == SSI_SISR_TDE0)
    {
        if (ssi_txinit->DataSize == SSI_DATA_WL8)
        {
            ssi->Instance->STX0 = (*ssi->pBuffPtr0++);
        }
        else if (ssi_txinit->DataSize == SSI_DATA_WL16)
        {
            ssi->Instance->STX0 = *((uint16_t *)(ssi->pBuffPtr0));
            ssi->pBuffPtr0 += 2U;
        }
        else
        {
            ssi->Instance->STX0 = *((uint32_t *)(ssi->pBuffPtr0));
            ssi->pBuffPtr0 += 4U;
        }
        ssi->XferCount0--;
    }
    else
    {
        if ((Timeout != MAX_DELAY) && ((Timeout == 0U) || ((GetTick() - tickstart) > Timeout)))
        {
            /* Update error code */
            ssi->ErrorCode |= SSI_ERROR_TIMEOUT;

            /* Disable SSI peripheral */
            ssi->Instance->SCR &= ~(SSI_SCR_TE);

            /* Change the SSI state */
            ssi->State = SSI_STATE_READY;

            return ;
        }
    }
}
/**
  * @brief  Fill the tx fifo_0
  * @param  ssi pointer to a SSI_HandleTypeDef structure that contains
  *         the configuration information for SSI module.
  * @param  ssi_txinit pointer to a SSI_TxInitTypeDef structure that contains
  *         the SSI Tx initialization information
  * @retval None
  */
static void SSI_FillFifo_0(SSI_HandleTypeDef *ssi, SSI_TxInitTypeDef *ssi_txinit)
{
    /* fill the fifo with data before to enable the SSI*/
    while (((ssi->Instance->SISR & SSI_SISR_TFE0) == SSI_SISR_TFE0) && (ssi->XferCount0 > 0U))
    {
        //printf("Fill FIFO0!\n");
        //printf("There are %d data need to be sended!\n",ssi->XferCount0);
        if (ssi_txinit->DataSize == SSI_DATA_WL8)
        {
            ssi->Instance->STX0 = (*ssi->pBuffPtr0++);
        }
        else if (ssi_txinit->DataSize == SSI_DATA_WL16)
        {
            ssi->Instance->STX0 = *((uint16_t *)(ssi->pBuffPtr0));
            ssi->pBuffPtr0 += 2U;
        }
        else
        {
            //printf("Fill data = %08x\n",*((uint32_t *)(ssi->pBuffPtr0)));
            ssi->Instance->STX0 = *((uint32_t *)(ssi->pBuffPtr0));
            ssi->pBuffPtr0 += 4U;
        }
        ssi->XferCount0--;
    }
}


/**
  * @brief  Fill the tx fifo_1 and fifo_2 alternatively
  * @param  ssi pointer to a SSI_HandleTypeDef structure that contains
  *         the configuration information for SSI module.
  * @param  ssi_txinit pointer to a SSI_TxInitTypeDef structure that contains
  *         the SSI Tx initialization information
  * @retval None
  */
static void SSI_FillDfifo(SSI_HandleTypeDef *ssi, SSI_TxInitTypeDef *ssi_txinit)
{
    while (((ssi->Instance->SISR & SSI_SISR_TFE0) == SSI_SISR_TFE0) && (ssi->XferCount0 > 0U))
    {
        if (ssi_txinit->DataSize == SSI_DATA_WL8)
        {
            ssi->Instance->STX0 = (*ssi->pBuffPtr0++);
        }
        else if (ssi_txinit->DataSize == SSI_DATA_WL16)
        {
            ssi->Instance->STX0 = *((uint16_t *)(ssi->pBuffPtr0));
            ssi->pBuffPtr0 += 2U;
        }
        else
        {
            ssi->Instance->STX0 = *((uint32_t *)(ssi->pBuffPtr0));
            ssi->pBuffPtr0 += 4U;
        }
        ssi->XferCount0--;
    }

    while (((ssi->Instance->SISR & SSI_SISR_TFE1) == SSI_SISR_TFE1) && (ssi->XferCount1 > 0U))
    {
        if (ssi_txinit->DataSize == SSI_DATA_WL8)
        {
            ssi->Instance->STX1 = (*ssi->pBuffPtr1++);
        }
        else if (ssi_txinit->DataSize == SSI_DATA_WL16)
        {
            ssi->Instance->STX1 = *((uint16_t *)(ssi->pBuffPtr1));
            ssi->pBuffPtr1 += 2U;
        }
        else
        {
            ssi->Instance->STX1 = *((uint32_t *)(ssi->pBuffPtr1));
            ssi->pBuffPtr1 += 4U;
        }
        ssi->XferCount1--;
    }
}

/**
  * @brief  Receive an amount of data in polling mode.
  * @param  ssi pointer to a SSI_HandleTypeDef structure that contains
  *         the configuration information for SSI module.
  * @param  ssi_rxinit pointer to a SSI_RxInitTypeDef structure that contains
  *         the SSI Rx initialization information
  * @param  pData0 Pointer to data buffer for channel 0
  * @param  pData1 Pointer to data buffer for channel 1
  * @param  Size0 Amount of data to be sent for channel 0
  * @param  Size1 Amount of data to be sent for channel 1
  * @param  Timeout Timeout duration
  * @retval void
  */
void SSI_Receive(SSI_HandleTypeDef *ssi, \
                 SSI_InitTypeDef *ssi_init, \
                 SSI_RxInitTypeDef *ssi_rxinit, \
                 uint8_t *pData0, \
                 uint8_t *pData1, \
                 uint16_t Size0, \
                 uint16_t Size1, \
                 uint32_t Timeout)
{
    uint32_t tickstart = GetTick();

    if (((pData0 == NULL) && (pData1 == NULL))
            || ((Size0 == 0)) && (Size1 == 0))
    {
        return;
    }

    if (ssi->State == SSI_STATE_READY)
    {
        ssi->XferSize0 = Size0;
        ssi->XferSize1 = Size1;
        ssi->XferCount0 = Size0;
        ssi->XferCount1 = Size1;
        ssi->pBuffPtr0 = pData0;
        ssi->pBuffPtr1 = pData1;
        ssi->State = SSI_STATE_BUSY_RX;
        ssi->ErrorCode = SSI_ERROR_NONE;

        if ((ssi->Instance->SCR & SSI_SCR_RE) != SSI_SCR_RE)
        {
            ssi->Instance->SCR |= SSI_SCR_RE;
        }

        /* Receive Data*/

        if (ssi_init->TCHEN == ENABLE)
        {
            while ((ssi->XferCount0 > 0U) || (ssi->XferCount1 > 0U))
            {
                if (ssi->XferCount0 > 0U)
                {
                    SSI_Fifo0Rx(ssi, ssi_rxinit, Timeout, tickstart);
                }


                if (ssi->XferCount1 > 0U)
                {
                    SSI_Fifo1Rx(ssi, ssi_rxinit, Timeout, tickstart);
                }
            }
        }
        else if (ssi_rxinit->FIFO0EN || ssi_init->Mode == AC97)
        {
            while (ssi->XferCount0 > 0U)
            {
                SSI_Fifo0Rx(ssi, ssi_rxinit, Timeout, tickstart);
            }
        }
        else
        {
            while (ssi->XferCount0 > 0U)
            {
                SSI_SRX0Rx(ssi, ssi_rxinit, Timeout, tickstart);
            }
        }
    }
}


/**
  * @brief  Rx fifo_0 transmit function
  * @param  ssi pointer to a SSI_HandleTypeDef structure that contains
  *         the configuration information for SSI module.
  * @param  ssi_rxinit pointer to a SSI_RxInitTypeDef structure that contains
  *         the SSI Rx initialization information
  * @param  Timeout Timeout duration
  * @param  tickstart Receive start time
  * @retval None
  */
static void SSI_Fifo0Rx(SSI_HandleTypeDef *ssi, SSI_RxInitTypeDef *ssi_rxinit, uint32_t Timeout, uint32_t tickstart)
{
    if ((ssi->Instance->SISR & SSI_SISR_RFF0) == SSI_SISR_RFF0)
    {
        if (ssi_rxinit->DataSize == SSI_DATA_WL8)
        {
            (*ssi->pBuffPtr0++) = ssi->Instance->SRX0;
        }
        else if (ssi_rxinit->DataSize == SSI_DATA_WL16)
        {
            *((uint16_t *)(ssi->pBuffPtr0)) = ssi->Instance->SRX0;
            ssi->pBuffPtr0 += 2U;
        }
        else
        {
            *((uint32_t *)(ssi->pBuffPtr0)) = ssi->Instance->SRX0;
            ssi->pBuffPtr0 += 4U;
        }
        ssi->XferCount0--;
    }
    else
    {
        if ((Timeout != MAX_DELAY) && ((Timeout == 0U) || ((GetTick() - tickstart) > Timeout)))
        {
            /* Update error code */
            ssi->ErrorCode |= SSI_ERROR_TIMEOUT;

            /* Disable SSI Rx channel */
            ssi->Instance->SCR &= ~(SSI_SCR_RE);

            /* Flush the fifo */
            ssi->Instance->SOR |= SSI_SOR_RX_CLR;

            /* Change the SSI state */
            ssi->State = SSI_STATE_READY;

            return ;
        }
    }
}

/**
  * @brief  Rx fifo_1 transmit function
  * @param  ssi pointer to a SSI_HandleTypeDef structure that contains
  *         the configuration information for SSI module.
  * @param  ssi_rxinit pointer to a SSI_RxInitTypeDef structure that contains
  *         the SSI Rx initialization information
  * @param  Timeout Timeout duration
  * @param  tickstart Receive start time
  * @retval None
  */
static void SSI_Fifo1Rx(SSI_HandleTypeDef *ssi, SSI_RxInitTypeDef *ssi_rxinit, uint32_t Timeout, uint32_t tickstart)
{
    if ((ssi->Instance->SISR & SSI_SISR_RFF1) == SSI_SISR_RFF1)
    {
        if (ssi_rxinit->DataSize == SSI_DATA_WL8)
        {
            (*ssi->pBuffPtr1++) = ssi->Instance->SRX1;
        }
        else if (ssi_rxinit->DataSize == SSI_DATA_WL16)
        {
            *((uint16_t *)(ssi->pBuffPtr1)) = ssi->Instance->SRX1;
            ssi->pBuffPtr1 += 2U;
        }
        else
        {
            *((uint32_t *)(ssi->pBuffPtr1)) = ssi->Instance->SRX1;
            ssi->pBuffPtr1 += 4U;
        }
        ssi->XferCount1--;
    }
    else
    {
        if ((Timeout != MAX_DELAY) && ((Timeout == 0U) || ((GetTick() - tickstart) > Timeout)))
        {
            /* Update error code */
            ssi->ErrorCode |= SSI_ERROR_TIMEOUT;

            /* Disable SSI Rx Function */
            ssi->Instance->SCR &= ~(SSI_SCR_RE);

            /* Change the SSI state */
            ssi->State = SSI_STATE_READY;

            return ;
        }
    }
}

/**
  * @brief  Rx srx register transmit function
  * @param  ssi pointer to a SSI_HandleTypeDef structure that contains
  *         the configuration information for SSI module.
  * @param  ssi_rxinit pointer to a SSI_RxInitTypeDef structure that contains
  *         the SSI Rx initialization information
  * @param  Timeout Timeout duration
  * @param  tickstart Receive start time
  * @retval None
  */
static void SSI_SRX0Rx(SSI_HandleTypeDef *ssi, SSI_RxInitTypeDef *ssi_rxinit, uint32_t Timeout, uint32_t tickstart)
{
    if ((ssi->Instance->SISR & SSI_SISR_RDR0) == SSI_SISR_RDR0)
    {
        if (ssi_rxinit->DataSize == SSI_DATA_WL8)
        {
            (*ssi->pBuffPtr0++) = ssi->Instance->SRX0;
        }
        else if (ssi_rxinit->DataSize == SSI_DATA_WL16)
        {
            *((uint16_t *)(ssi->pBuffPtr0)) = ssi->Instance->SRX0;
            ssi->pBuffPtr0 += 2U;
        }
        else
        {
            *((uint32_t *)(ssi->pBuffPtr0)) = ssi->Instance->SRX0;
            ssi->pBuffPtr0 += 4U;
        }
        ssi->XferCount0--;
    }
    else
    {
        if ((Timeout != MAX_DELAY) && ((Timeout == 0U) || ((GetTick() - tickstart) > Timeout)))
        {
            /* Update error code */
            ssi->ErrorCode |= SSI_ERROR_TIMEOUT;

            /* Disable SSI Rx Function */
            ssi->Instance->SCR &= ~(SSI_SCR_RE);

            /* Change the SSI state */
            ssi->State = SSI_STATE_READY;

            return ;
        }
    }
}

