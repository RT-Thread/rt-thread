/******************************************************************************
 * Copyright (C) 2016, Huada Semiconductor Co.,Ltd All rights reserved.
 *
 * This software is owned and published by:
 * Huada Semiconductor Co.,Ltd ("HDSC").
 *
 * BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
 * BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
 *
 * This software contains source code for use with HDSC
 * components. This software is licensed by HDSC to be adapted only
 * for use in systems utilizing HDSC components. HDSC shall not be
 * responsible for misuse or illegal use of this software for devices not
 * supported herein. HDSC is providing this software "AS IS" and will
 * not be responsible for issues arising from incorrect user implementation
 * of the software.
 *
 * Disclaimer:
 * HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
 * REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
 * ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
 * WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
 * WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
 * WARRANTY OF NONINFRINGEMENT.
 * HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
 * NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
 * LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
 * LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
 * INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
 * SAVINGS OR PROFITS,
 * EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
 * INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
 * FROM, THE SOFTWARE.
 *
 * This software may be replicated in part or whole for the licensed use,
 * with the restriction that this Disclaimer and Copyright notice must be
 * included with each copy of this software, whether used in part or whole,
 * at all times.
 */
/******************************************************************************/
/** \file spi.c
 **
 ** A detailed description is available at
 ** @link SpiGroup Spi description @endlink
 **
 **   - 2018-05-14  1.0  Jason First version for Device Driver Library of Spi.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "spi.h"

/**
 *******************************************************************************
 ** \addtogroup SpiGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

#define SPI_SLAVE_BRR_DIV_MIN           6
#define SPI_MASTER_BRR_DIV_MIN          2

#define SPI_CR_DEFAULT                  (0x0000)
#define SPI_OCR_DEFAULT                 (0x00)
#define SPI_FCR_DEFAULT                 (0x00000010)
#define SPI_SR_DEFAULT                  (0x0020)
#define SPI_CMR_DEFAULT                 (0x030d)
#define SPI_BRR_DEFAULT                 (0xff)

/*! Parameter validity check for spi peripheral \a per. */
#define IS_SPI_ALL_PERIPH(per)                                                 \
(   ((M4_SPI)               ==  (per))                                         \
)

/*! Parameter validity check for spi peripheral \a per. */
#define IS_SPI_ALL_CMR(cmr)                                                    \
(   ((&M4_SPI->CMR0_f)      ==  (cmr))  ||                                     \
    ((&M4_SPI->CMR1_f)       ==  (cmr))  ||                                     \
    ((&M4_SPI->CMR2_f)       ==  (cmr))  ||                                     \
    ((&M4_SPI->CMR3_f)       ==  (cmr))                                         \
)

/*! Parameter validity check for spi sck delay \a div. */
#define IS_SPI_CLK_DELAY(delay)                                                \
(   ((SpiDelayClk1)         ==  (delay))    ||                                 \
    ((SpiDelayClk2)         ==  (delay))    ||                                 \
    ((SpiDelayClk3)         ==  (delay))    ||                                 \
    ((SpiDelayClk4)         ==  (delay))    ||                                 \
    ((SpiDelayClk5)         ==  (delay))    ||                                 \
    ((SpiDelayClk6)         ==  (delay))    ||                                 \
    ((SpiDelayClk7)         ==  (delay))    ||                                 \
    ((SpiDelayClk8)         ==  (delay))                                       \
)

/*! Parameter validity check for spi clock division \a div. */
#define IS_SPI_CLOCK_DIV(div)                                                  \
(   ((SpiClkDiv1)           ==  (div))  ||                                     \
    ((SpiClkDiv2)           ==  (div))  ||                                     \
    ((SpiClkDiv4)           ==  (div))  ||                                     \
    ((SpiClkDiv8)           ==  (div))                                         \
)

/*! Parameter validity check for spi master slave mode \a mode. */
#define IS_SPI_MSMODE(mode)                                                    \
(   ((SpiMSSlave)           ==  (mode)) ||                                     \
    ((SpiMSMaster)          ==  (mode))                                        \
)

/*! Parameter validity check for spi data size \a size. */
#define IS_SPI_DATA_SIZE(size)                                                 \
(   ((SpiDataSize20)        ==  (size)) ||                                     \
    ((SpiDataSize24)        ==  (size)) ||                                     \
    ((SpiDataSize32)        ==  (size)) ||                                     \
    ((SpiDataSize8)         ==  (size)) ||                                     \
    ((SpiDataSize9)         ==  (size)) ||                                     \
    ((SpiDataSize10)        ==  (size)) ||                                     \
    ((SpiDataSize11)        ==  (size)) ||                                     \
    ((SpiDataSize12)        ==  (size)) ||                                     \
    ((SpiDataSize13)        ==  (size)) ||                                     \
    ((SpiDataSize14)        ==  (size)) ||                                     \
    ((SpiDataSize15)        ==  (size)) ||                                     \
    ((SpiDataSize16)        ==  (size))                                        \
)

/*! Parameter validity check for spi clock polarity \a pol. */
#define IS_SPI_CLK_POL(pol)                                                    \
(   ((SpiClkPolLow)         ==  (pol))  ||                                     \
    ((SpiClkPolHigh)        ==  (pol))                                         \
)

/*! Parameter validity check for spi clock phase \a pha. */
#define IS_SPI_CLK_PHA(pha)                                                    \
(   ((SpiClkPhaEdgeOdd)     ==  (pha))  ||                                     \
    ((SpiClkPhaEdgeEven)    ==  (pha))                                         \
)

/*! Parameter validity check for spi first bit \a bit. */
#define IS_SPI_FIRST_BIT(bit)                                                  \
(   ((SpiFirstBitMsb)       ==  (bit))  ||                                     \
    ((SpiFirstBitLsb)       ==  (bit))                                         \
)

/*! Parameter validity check for spi duplex mode \a mode. */
#define IS_SPI_DUPLEX_MODE(mode)                                               \
(   ((SpiDuplexFull)        ==  (mode)) ||                                     \
    ((SpiDuplexHalf)        ==  (mode))                                        \
)

/*! Parameter validity check for spi mode \a mode. */
#define IS_SPI_MODE(mode)                                                      \
(   ((SpiModeSpi)           ==  (mode)) ||                                     \
    ((SpiModeSnyc)          ==  (mode))                                        \
)

/*! Parameter validity check for spi ss pin \a pin. */
#define IS_SPI_SS_PIN(pin)                                                     \
(   ((SpiSS0)               ==  (pin))  ||                                     \
    ((SpiSS1)               ==  (pin))  ||                                     \
    ((SpiSS2)               ==  (pin))  ||                                     \
    ((SpiSS3)               ==  (pin))                                         \
)

/*! Parameter validity check for spi function \a func. */
#define IS_SPI_FUNC(func)                                                      \
(   ((SpiFuncParity)        ==  (func)) ||                                     \
    ((SpiFuncParityOdd)     ==  (func)) ||                                     \
    ((SpiFuncDetechModeErr) ==  (func)) ||                                     \
    ((SpiFuncAutoStopSck)   ==  (func)) ||                                     \
    ((SpiFuncMosiIdleFixed) ==  (func))                                        \
)

/*! Parameter validity check for spi mosi idle level \a lvl. */
#define IS_SPI_MOSI_IDLE(lvl)                                                  \
(   ((SpiMosiIdleLvlLow)    ==  (lvl))  ||                                     \
    ((SpiMosiIdleLvlHigh)   ==  (lvl))                                         \
)

/*! Parameter validity check for spi SS polarity \a pol. */
#define IS_SPI_SS_POL(pol)                                                     \
(   ((SpiSSPolLow)          ==  (pol))  ||                                     \
    ((SpiSSPolHigh)         ==  (pol))                                         \
)

/*! Parameter validity check for spi interrupt request \a irq. */
#define IS_SPI_IRQ(irq)                                                        \
(   ((SpiIrqTx)             ==  (irq))  ||                                     \
    ((SpiIrqRx)             ==  (irq))  ||                                     \
    ((SpiIrqIdle)           ==  (irq))  ||                                     \
    ((SpiIrqError)          ==  (irq))                                         \
)

/*! Parameter validity check for spi frame count \a cnt. */
#define IS_SPI_FRAME_CNT(cnt)                                                  \
(   ((SpiFrame1)            ==  (cnt))  ||                                     \
    ((SpiFrame2)            ==  (cnt))  ||                                     \
    ((SpiFrame3)            ==  (cnt))  ||                                     \
    ((SpiFrame4)            ==  (cnt))                                         \
)

/*! Parameter validity check for spi flag \a flag. */
#define IS_SPI_FLAG(flag)                                                      \
(   ((SpiFlagOvr)           ==  (flag)) ||                                     \
    ((SpiFlagUdr)           ==  (flag)) ||                                     \
    ((SpiFlagRxFull)        ==  (flag)) ||                                     \
    ((SpiFlagTxEmpty)       ==  (flag)) ||                                     \
    ((SpiFlagIdle)          ==  (flag)) ||                                     \
    ((SpiFlagParityErr)     ==  (flag)) ||                                     \
    ((SpiFlagModeErr)       ==  (flag))                                        \
)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief  Deinitialize the M4_SPIx peripheral registers to their default
 **         reset values.
 **
 ** \param  [in] M4_SPIx                The spi peripheral.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Spi_DeInit(M4_SPI_TypeDef *M4_SPIx)
{
    DDL_ASSERT(IS_SPI_ALL_PERIPH(M4_SPIx));

    M4_SPIx->CR = SPI_CR_DEFAULT;
    M4_SPIx->OCR = SPI_OCR_DEFAULT;
    M4_SPIx->FCR = SPI_FCR_DEFAULT;
    M4_SPIx->SR = SPI_SR_DEFAULT;
    M4_SPIx->CMR0 = SPI_CMR_DEFAULT;
    M4_SPIx->CMR1 = SPI_CMR_DEFAULT;
    M4_SPIx->CMR2 = SPI_CMR_DEFAULT;
    M4_SPIx->CMR3 = SPI_CMR_DEFAULT;
    M4_SPIx->BRR = SPI_BRR_DEFAULT;
}

/**
 *******************************************************************************
 ** \brief  Initialize the M4_SPIx peripheral registers according to the
 **         specified parameters in the pstcSpiCfg.
 **
 ** \param  [in] M4_SPIx                The spi peripheral.
 **
 ** \param  [in] pstcSpiCfg             Pointer to a pstcSpiCfg structure that
 **                                     contains the configuration information
 **                                     for the specified spi peripheral.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Spi_Init(M4_SPI_TypeDef *M4_SPIx, stc_spi_config_t *pstcSpiCfg)
{
    uint8_t temp;
    stc_spi_cmr_config_t stcSpiCmr0Cfg;

    DDL_ASSERT(IS_SPI_ALL_PERIPH(M4_SPIx));
    DDL_ASSERT(NULL != pstcSpiCfg);

    DDL_ASSERT(IS_SPI_CLK_DELAY(pstcSpiCfg->enSckDelayClk));
    DDL_ASSERT(IS_SPI_CLK_DELAY(pstcSpiCfg->enSSDelayClk));
    DDL_ASSERT(IS_SPI_CLK_DELAY(pstcSpiCfg->enNextDelayClk));
    DDL_ASSERT(IS_SPI_MSMODE(pstcSpiCfg->enMsMode));
    DDL_ASSERT(IS_SPI_DUPLEX_MODE(pstcSpiCfg->enDuplex));
    DDL_ASSERT(IS_SPI_MODE(pstcSpiCfg->enMode));
    DDL_ASSERT(IS_SPI_MOSI_IDLE(pstcSpiCfg->enMosiIdleLvl));
    DDL_ASSERT(IS_SPI_FRAME_CNT(pstcSpiCfg->enFrame));

    /* Reset. Reset SPE bit to initialize spi,Stop transmission and clear tx buffer. */
    /* Disable TXIE first because reset SPE will clear tx buffer and set TDEF. */
    M4_SPIx->CR_f.TXIE = Reset;
    M4_SPIx->CR_f.SPE = Reset;

    /* Config CR. */
    /* Master mode or slave mode. */
    M4_SPIx->CR_f.MSTR = pstcSpiCfg->enMsMode;
    M4_SPIx->CR_f.SPIMDS = pstcSpiCfg->enMode;

    /* Config FCR. */
    /* Set SckDelay, SSDelay, NextDelay. */
    M4_SPIx->FCR_f.SCKDL = pstcSpiCfg->enSckDelayClk;
    M4_SPIx->FCR_f.SSDL = pstcSpiCfg->enSSDelayClk;
    M4_SPIx->FCR_f.NXTDL = pstcSpiCfg->enNextDelayClk;
    /* Set CMRSL.Use CMR0 in default. */
    M4_SPIx->FCR_f.CMRSL = SpiCmr0;
    /* Set frame count. */
    M4_SPIx->FCR_f.FRN = pstcSpiCfg->enFrame;

    /* Config CMR0. */
    if(NULL != pstcSpiCfg->pstcSpiCmr0Cfg)
    {
        /* Use user config. */
        Spi_CmrConfig(&M4_SPIx->CMR0_f, pstcSpiCfg->pstcSpiCmr0Cfg);
    }
    else
    {
        /* Use deault config. */
        Spi_CmrStructInit(&stcSpiCmr0Cfg);
        Spi_CmrConfig(&M4_SPIx->CMR0_f, &stcSpiCmr0Cfg);
    }

    /* Config OCR. */
    M4_SPIx->OCR_f.MOIFV = pstcSpiCfg->enMosiIdleLvl;

    /* Clear flags. */
    /* Read overrun error flag and then reset it if it is set. */
    temp = M4_SPIx->SR_f.OVRERF;
    if(Set == temp)
    {
        M4_SPIx->SR_f.OVRERF = Reset;
    }
    /* Read parity error flag and then reset it if it is set. */
    temp = M4_SPIx->SR_f.PERF;
    if(Set == temp)
    {
        M4_SPIx->SR_f.PERF= Reset;
    }
    /* Reset mode error flag. */
    M4_SPIx->SR_f.MODFERF = Reset;

    /* Config BRR. */
    Spi_SetBaudRate(M4_SPIx, pstcSpiCfg->u8BaudRateDiv);
}

/**
 *******************************************************************************
 ** \brief  Initialize the M4_SPI peripheral registers according to the
 **         specified parameters in the pstcSpiCmrCfg.
 **
 ** \param  [in] M4_SPI_CMR             The cmr register of spi peripheral.
 **
 ** \param  [in] pstcSpiCmrCfg          Pointer to a stc_spi_cmr_config_t
 **                                     structure that contains the configuration
 **                                     information for the specified spi
 **                                     peripheral about command register.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Spi_CmrConfig(stc_spi_cmr_field_t *M4_SPI_CMR, stc_spi_cmr_config_t *pstcSpiCmrCfg)
{
    DDL_ASSERT(IS_SPI_ALL_CMR(M4_SPI_CMR));
    DDL_ASSERT(NULL != pstcSpiCmrCfg);

    DDL_ASSERT(IS_SPI_CLOCK_DIV(pstcSpiCmrCfg->enSpiClkDiv));
    DDL_ASSERT(IS_SPI_DATA_SIZE(pstcSpiCmrCfg->enDataSize));
    DDL_ASSERT(IS_SPI_CLK_POL(pstcSpiCmrCfg->enClkPol));
    DDL_ASSERT(IS_SPI_CLK_PHA(pstcSpiCmrCfg->enClkPha));
    DDL_ASSERT(IS_SPI_FIRST_BIT(pstcSpiCmrCfg->enFirstBit));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcSpiCmrCfg->enSckDelay));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcSpiCmrCfg->enSSDelay));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcSpiCmrCfg->enNextDelay));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcSpiCmrCfg->enBurst));
    DDL_ASSERT(IS_SPI_SS_PIN(pstcSpiCmrCfg->enSSPin));

    M4_SPI_CMR->SCKDLE = pstcSpiCmrCfg->enSckDelay;
    M4_SPI_CMR->SSDLE = pstcSpiCmrCfg->enSSDelay;
    M4_SPI_CMR->NXTDLE = pstcSpiCmrCfg->enNextDelay;
    M4_SPI_CMR->LSBF = pstcSpiCmrCfg->enFirstBit;
    M4_SPI_CMR->SPB = pstcSpiCmrCfg->enDataSize;
    M4_SPI_CMR->BURST = pstcSpiCmrCfg->enBurst;
    M4_SPI_CMR->BRDIV = pstcSpiCmrCfg->enSpiClkDiv;
    M4_SPI_CMR->SSA = pstcSpiCmrCfg->enSSPin;
    M4_SPI_CMR->CPOL = pstcSpiCmrCfg->enClkPol;
    M4_SPI_CMR->CPHA = pstcSpiCmrCfg->enClkPha;
}

/**
 *******************************************************************************
 ** \brief  Initialize the M4_SPIx peripheral registers according to the
 **         specified parameters in the pstcSpiSSCfg.
 **
 ** \param  [in] M4_SPIx                The spi peripheral.
 **
 ** \param  [in] pstcSpiSSCfg           Pointer to a stc_spi_ss_config_t
 **                                     structure that contains the configuration
 **                                     information for the specified spi
 **                                     peripheral about slave selection.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Spi_SsConfig(M4_SPI_TypeDef *M4_SPIx, stc_spi_ss_config_t *pstcSpiSSCfg)
{
    DDL_ASSERT(IS_SPI_ALL_PERIPH(M4_SPIx));
    DDL_ASSERT(NULL != pstcSpiSSCfg);

    DDL_ASSERT(IS_SPI_SS_POL(pstcSpiSSCfg->enSpiSS0Pol));
    DDL_ASSERT(IS_SPI_SS_POL(pstcSpiSSCfg->enSpiSS1Pol));
    DDL_ASSERT(IS_SPI_SS_POL(pstcSpiSSCfg->enSpiSS2Pol));
    DDL_ASSERT(IS_SPI_SS_POL(pstcSpiSSCfg->enSpiSS3Pol));

    M4_SPIx->FCR_f.SS0PV = pstcSpiSSCfg->enSpiSS0Pol;
    M4_SPIx->FCR_f.SS1PV = pstcSpiSSCfg->enSpiSS1Pol;
    M4_SPIx->FCR_f.SS2PV = pstcSpiSSCfg->enSpiSS2Pol;
    M4_SPIx->FCR_f.SS3PV = pstcSpiSSCfg->enSpiSS3Pol;

    if(NULL != pstcSpiSSCfg->pstcSpiCmr0Cfg)
    {
        Spi_CmrConfig(&M4_SPIx->CMR0_f, pstcSpiSSCfg->pstcSpiCmr0Cfg);
    }

    if(NULL != pstcSpiSSCfg->pstcSpiCmr1Cfg)
    {
        Spi_CmrConfig(&M4_SPIx->CMR1_f, pstcSpiSSCfg->pstcSpiCmr1Cfg);
    }

    if(NULL != pstcSpiSSCfg->pstcSpiCmr2Cfg)
    {
        Spi_CmrConfig(&M4_SPIx->CMR2_f, pstcSpiSSCfg->pstcSpiCmr2Cfg);
    }

    if(NULL != pstcSpiSSCfg->pstcSpiCmr3Cfg)
    {
        Spi_CmrConfig(&M4_SPIx->CMR3_f, pstcSpiSSCfg->pstcSpiCmr3Cfg);
    }
}

/**
 *******************************************************************************
 ** \brief  Fills each pstcSpiCmrCfg member with its default value.
 **
 ** \param  [in] pstcSpiCmrCfg          Pointer to a stc_spi_cmr_config_t structure
 **                                     that contains the configuration
 **                                     information for the specified spi peripheral.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Spi_CmrStructInit(stc_spi_cmr_config_t *pstcSpiCmrCfg)
{
    DDL_ASSERT(NULL != pstcSpiCmrCfg);

    pstcSpiCmrCfg->enSckDelay = Disable;
    pstcSpiCmrCfg->enSSDelay = Disable;
    pstcSpiCmrCfg->enNextDelay = Disable;
    pstcSpiCmrCfg->enFirstBit = SpiFirstBitMsb;
    pstcSpiCmrCfg->enDataSize = SpiDataSize32;
    pstcSpiCmrCfg->enBurst = Disable;
    pstcSpiCmrCfg->enSpiClkDiv = SpiClkDiv8;
    pstcSpiCmrCfg->enSSPin = SpiSS0;
    pstcSpiCmrCfg->enClkPol = SpiClkPolLow;
    pstcSpiCmrCfg->enClkPha = SpiClkPhaEdgeEven;
}

/**
 *******************************************************************************
 ** \brief  Fills each pstcSpiCfg member with its default value.
 **
 ** \param  [in] pstcSpiCfg             Pointer to a stc_spi_config_t structure
 **                                     that contains the configuration
 **                                     information for the specified spi peripheral.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Spi_StructInit(stc_spi_config_t *pstcSpiCfg)
{
    DDL_ASSERT(NULL != pstcSpiCfg);

    /* Set spi cmr0 in default. */
    if(NULL != pstcSpiCfg->pstcSpiCmr0Cfg)
    {
        Spi_CmrStructInit(pstcSpiCfg->pstcSpiCmr0Cfg);
    }

    pstcSpiCfg->enSckDelayClk = SpiDelayClk1;
    pstcSpiCfg->enSSDelayClk = SpiDelayClk1;
    /* Default delay clock for next read write is 1 + 2 spi clock. */
    pstcSpiCfg->enNextDelayClk = SpiDelayClk1;
    pstcSpiCfg->enMsMode = SpiMSSlave;
    pstcSpiCfg->enDuplex = SpiDuplexFull;
    pstcSpiCfg->enMode = SpiModeSpi;
    pstcSpiCfg->enMosiIdleLvl = SpiMosiIdleLvlLow;
    pstcSpiCfg->enFrame = SpiFrame1;
    pstcSpiCfg->u8BaudRateDiv = SPI_BRR_DEFAULT;
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the spi function.
 **
 ** \param  [in] M4_SPIx                The spi peripheral.
 **
 ** \param  [in] enNewState             The new state of the spi function.
 ** \arg    Enable                      Enable.
 ** \arg    Disable                     Disable.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Spi_Cmd(M4_SPI_TypeDef *M4_SPIx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_SPI_ALL_PERIPH(M4_SPIx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        DDL_ASSERT(M4_SPIx->SR_f.MODFERF != Set);
        M4_SPIx->CR_f.SPE = Set;
    }
    else
    {
        M4_SPIx->CR_f.SPE = Reset;
    }
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the specified spi function.
 **
 ** \param  [in] M4_SPIx                To select the spi peripheral.
 **
 ** \param  [in] enFunc                 Spi function types.
 ** \arg    SpiFuncParity               Enable spi paity or not.
 ** \arg    SpiFuncParityOdd            Odd parity or not.
 ** \arg    SpiFuncDetechModeErr        Detech mode error or not.
 ** \arg    SpiFuncAutoStopSck          Auto stop sck before overrun error or not.
 **
 ** \param  [in] enNewState             The new state of the spi function.
 ** \arg    Enable                      Enable.
 ** \arg    Disable                     Disable.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Spi_FuncCmd(M4_SPI_TypeDef *M4_SPIx, en_spi_func_t enFunc, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_SPI_ALL_PERIPH(M4_SPIx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_SPI_FUNC(enFunc));

    switch(enFunc)
    {
        /* Enable or disable spi parity. */
        case SpiFuncParity:
            M4_SPIx->CR_f.PAE = (Enable == enNewState ? Set : Reset);
            break;
        /* Enable odd parity or not.Default is even parity. */
        case SpiFuncParityOdd:
            M4_SPIx->CR_f.PAOE = (Enable == enNewState ? Set : Reset);
            break;
        /* Detech mode error or not. */
        case SpiFuncDetechModeErr:
            M4_SPIx->CR_f.MODFE = (Enable == enNewState ? Set : Reset);
            break;
        /* Auto stop sck before overrun error. */
        case SpiFuncAutoStopSck:
            M4_SPIx->CR_f.SCKASTPE = (Enable == enNewState ? Set : Reset);
            break;
        /* Fixed mosi idle level. */
        case SpiFuncMosiIdleFixed:
            M4_SPIx->OCR_f.MOIFE = (Enable == enNewState ? Set : Reset);
            break;

        /* Do not add default because assert function has check parameter. */
    }
}

/**
 *******************************************************************************
 ** \brief  Set baudrate for M4_SPIx.
 **
 ** \param  [in] M4_SPIx                The spi peripheral.
 **
 ** \param  [in] u8Div                  Baudrate division.
 **
 ** \retval None
 **
 ** \note   Baudrate=PCLK1/(((u8Div+1)>>1)*(1>>CMR0_f.BRDIV))
 **
 ******************************************************************************/
void Spi_SetBaudRate(M4_SPI_TypeDef *M4_SPIx, uint8_t u8Div)
{
    uint8_t u8DivMin;
    uint16_t temp;

    DDL_ASSERT(IS_SPI_ALL_PERIPH(M4_SPIx));

    temp = (((u8Div+1)<<1)*(1<<M4_SPIx->CMR0_f.BRDIV));
    u8DivMin = (SpiMSSlave == M4_SPIx->CR_f.MSTR ? SPI_SLAVE_BRR_DIV_MIN : SPI_MASTER_BRR_DIV_MIN);

    DDL_ASSERT(u8DivMin <= temp);

    M4_SPIx->BRR = u8Div;
}

/**
 *******************************************************************************
 ** \brief  Send a data through a M4_SPI.
 **
 ** \param  [in] M4_SPI                 The spi peripheral.
 **
 ** \param  [in] u32Data                Data.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Spi_SendData(M4_SPI_TypeDef *M4_SPIx, uint32_t u32Data)
{
    DDL_ASSERT(IS_SPI_ALL_PERIPH(M4_SPIx));

    M4_SPIx->DR = u32Data;
}

/**
 *******************************************************************************
 ** \brief  Receive a data through a M4_SPIx.
 **
 ** \param  [in] M4_SPIx                The spi peripheral.
 **
 ** \retval uint32_t                    Data received.
 **
 ** \note   None
 **
 ******************************************************************************/
uint32_t Spi_ReceiveData(M4_SPI_TypeDef *M4_SPIx)
{
    DDL_ASSERT(IS_SPI_ALL_PERIPH(M4_SPIx));

    return M4_SPIx->DR;
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the specified M4_SPIx interrupts.
 **
 ** \param  [in] M4_SPIx                The spi peripheral.
 **
 ** \param  [in] enIrq                  Specifies the spi interrupt type.
 ** \arg    SpiIrqTx                    TX interrupt.
 ** \arg    SpiIrqRx                    RX interrupt
 ** \arg    SpiIrqIdle                  Spi idle interrupt.
 ** \arg    SpiIrqError                 Overrun,underrun and parity error interrupt.
 **
 ** \param  [in] enNewState             The new state of the spi interrupt.
 ** \arg    Enable                      Enable.
 ** \arg    Disable                     Disable.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Spi_ITConfig(M4_SPI_TypeDef *M4_SPIx, en_spi_irq_t enIrq, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_SPI_ALL_PERIPH(M4_SPIx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_SPI_IRQ(enIrq));

    switch(enIrq)
    {
        case SpiIrqTx:
            M4_SPIx->CR_f.TXIE = (Enable == enNewState ? Set : Reset);
            break;
        case SpiIrqRx:
            M4_SPIx->CR_f.RXIE = (Enable == enNewState ? Set : Reset);
            break;
        case SpiIrqIdle:
            M4_SPIx->CR_f.IDIE = (Enable == enNewState ? Set : Reset);
            break;
        case SpiIrqError:
            M4_SPIx->CR_f.EIE = (Enable == enNewState ? Set : Reset);
            break;

        /* Do not add default because assert function has check parameter. */
    }
}

/**
 *******************************************************************************
 ** \brief  Check whether the specified M4_SPIx flag is set or not.
 **
 ** \param  [in] M4_SPIx                The spi peripheral.
 **
 ** \param  [in] enFlag                 Specifies the msc spi flag to check.
 ** \arg    SpiFlagOvr                  Receive buffer overrun or not.
 ** \arg    SpiFlagUdr                  Transfer buffer underrun or not.
 ** \arg    SpiFlagRxFull               Receive buffer is full or not.
 ** \arg    SpiFlagTxEmpty              Transfer buffer is empty or not.
 ** \arg    SpiFlagIdle                 Spi is idle or not.
 ** \arg    SpiFlagParityErr            Parity error or not.
 ** \arg    SpiFlagModeErr              Mode error or not.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
en_flag_status_t Spi_GetFlagStatus(M4_SPI_TypeDef *M4_SPIx,  en_spi_flag_t enFlag)
{
    en_flag_status_t status;

    DDL_ASSERT(IS_SPI_ALL_PERIPH(M4_SPIx));
    DDL_ASSERT(IS_SPI_FLAG(enFlag));

    switch(enFlag)
    {
        case SpiFlagOvr:
            status = ((1 == M4_SPIx->SR_f.OVRERF) ? Set : Reset);
            break;
        case SpiFlagUdr:
            status = ((1 == M4_SPIx->SR_f.UDRERF) ? Set : Reset);
            break;
        case SpiFlagRxFull:
            status = ((1 == M4_SPIx->SR_f.RDFF) ? Set : Reset);
            break;
        case SpiFlagTxEmpty:
            status = ((1 == M4_SPIx->SR_f.TDEF) ? Set : Reset);
            break;
        case SpiFlagIdle:
            status = ((1 == M4_SPIx->SR_f.IDLNF) ? Set : Reset);
            break;
        case SpiFlagParityErr:
            status = ((1 == M4_SPIx->SR_f.PERF) ? Set : Reset);
            break;
        case SpiFlagModeErr:
            status = ((1 == M4_SPIx->SR_f.MODFERF) ? Set : Reset);
            break;

        /* Do not add default because assert function has check parameter. */
    }

    return status;
}

/**
 *******************************************************************************
 ** \brief  Clear the specified M4_SPIx flag.
 **
 ** \param  [in] M4_SPIx                The spi peripheral.
 **
 ** \param  [in] enFlag                 Specifies the spi flag to clear.
 ** \arg    SpiFlagOvr                  Receive buffer overrun or not.
 ** \arg    SpiFlagUdr                  Transfer buffer underrun or not.
 ** \arg    SpiFlagRxFull               Receive buffer is full or not.
 ** \arg    SpiFlagTxEmpty              Transfer buffer is empty or not.
 ** \arg    SpiFlagIdle                 Spi is idle or not.
 ** \arg    SpiFlagParityErr            Parity error or not.
 ** \arg    SpiFlagModeErr              Mode error or not.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Spi_ClearFlagStatus(M4_SPI_TypeDef *M4_SPIx,  en_spi_flag_t enFlag)
{
    uint8_t temp;

    DDL_ASSERT(IS_SPI_ALL_PERIPH(M4_SPIx));
    DDL_ASSERT(IS_SPI_FLAG(enFlag));

    switch(enFlag)
    {
        case SpiFlagOvr:
            temp = M4_SPIx->SR_f.OVRERF;
            if(Set == temp)
            {
                M4_SPIx->SR_f.OVRERF = Reset;
            }
            break;

        case SpiFlagUdr:
            M4_SPIx->SR_f.UDRERF = Reset;
            break;

        case SpiFlagRxFull:
        case SpiFlagTxEmpty:
        case SpiFlagIdle:
            break;
        case SpiFlagParityErr:
            temp = M4_SPIx->SR_f.PERF;
            if(Set == temp)
            {
                M4_SPIx->SR_f.PERF= Reset;
            }
            break;

        case SpiFlagModeErr:
            M4_SPIx->SR_f.MODFERF = Reset;
            break;

        /* Do not add default because assert function has check parameter. */
    }
}

//@} // SpiGroup

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


