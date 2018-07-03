/*****************************************************************************
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
/** \file spi.h
 **
 ** A detailed description is available at
 ** @link SpiGroup Spi description @endlink
 **
 **   - 2018-05-03  1.0  Jason First version for Device Driver Library of Spi.
 **
 ******************************************************************************/

#ifndef __SPI_H__
#define __SPI_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "base_types.h"
#include "hc32f480.h"
#include "ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup SpiGroup Serial peripheral interface(Spi)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief  Spi clock delay for sck,ss and next read or write.
 **
 ******************************************************************************/
typedef enum en_spi_delay_clk
{
    SpiDelayClk1                    = 0u,   ///< Delay 1 clk.
    SpiDelayClk2                    = 1u,   ///< Delay 2 clk.
    SpiDelayClk3                    = 2u,   ///< Delay 3 clk.
    SpiDelayClk4                    = 3u,   ///< Delay 4 clk.
    SpiDelayClk5                    = 4u,   ///< Delay 5 clk.
    SpiDelayClk6                    = 5u,   ///< Delay 6 clk.
    SpiDelayClk7                    = 6u,   ///< Delay 7 clk.
    SpiDelayClk8                    = 7u,   ///< Delay 8 clk.
} en_spi_delay_clk_t;

/**
 *******************************************************************************
 ** \brief  Spi mode.
 **
 ******************************************************************************/
typedef enum en_spi_msmode
{
    SpiMSSlave                      = 0u,   ///< Spi slave mode.
    SpiMSMaster                     = 1u,   ///< Spi master mode.
} en_spi_msmode_t;

/**
 *******************************************************************************
 ** \brief  Spi data size.
 **
 ******************************************************************************/
typedef enum en_spi_data_size
{
    SpiDataSize20                   = 0u,   ///< 20 bits.
    SpiDataSize24                   = 1u,   ///< 24 bits.
    SpiDataSize32                   = 3u,   ///< 32 bits.
    SpiDataSize8                    = 4u,   ///< 8 bits.
    SpiDataSize9                    = 8u,   ///< 9 bits.
    SpiDataSize10                   = 9u,   ///< 10 bits.
    SpiDataSize11                   = 10u,  ///< 11 bits.
    SpiDataSize12                   = 11u,  ///< 12 bits.
    SpiDataSize13                   = 12u,  ///< 13 bits.
    SpiDataSize14                   = 13u,  ///< 14 bits.
    SpiDataSize15                   = 14u,  ///< 15 bits.
    SpiDataSize16                   = 15u,  ///< 16 bits
} en_spi_data_size_t;

/**
 *******************************************************************************
 ** \brief  Spi clock polarity.
 **
 ******************************************************************************/
typedef enum en_spi_clk_pol
{
    SpiClkPolLow                    = 0u,   ///< Clock polarity low.
    SpiClkPolHigh                   = 1u,   ///< Clock polarit high.
} en_spi_clk_pol_t;

/**
 *******************************************************************************
 ** \brief  Spi clock phase.
 **
 ******************************************************************************/
typedef enum en_spi_clk_pha
{
    SpiClkPhaEdgeOdd                = 0u,   ///< Clock phase odd edge.
    SpiClkPhaEdgeEven               = 1u,   ///< Clock phase even edge.
} en_spi_clk_pha_t;

/**
 *******************************************************************************
 ** \brief  Spi first bit direction.
 **
 ******************************************************************************/
typedef enum en_spi_first_bit
{
    SpiFirstBitMsb                  = 0u,   ///< Msb first.
    SpiFirstBitLsb                  = 1u,   ///< Lsb first.
} en_spi_first_bit_t;

/**
 *******************************************************************************
 ** \brief  Spi clock division.
 **
 ******************************************************************************/
typedef enum en_spi_clock_div
{
    SpiClkDiv1                      = 0u,   ///< Spi clock = Pclk1/1.
    SpiClkDiv2                      = 1u,   ///< Spi clock = Pclk1/2.
    SpiClkDiv4                      = 2u,   ///< Spi clock = Pclk1/4.
    SpiClkDiv8                      = 3u,   ///< Spi clock = Pclk1/8.
} en_spi_clock_div_t;

/**
 *******************************************************************************
 ** \brief  Spi duplex mode.
 **
 ******************************************************************************/
typedef enum en_spi_duplex_mode
{
    SpiDuplexFull                   = 0u,   ///< FUll duplex.
    SpiDuplexHalf                   = 1u,   ///< Half duplex.
} en_spi_duplex_mode_t;

/**
 *******************************************************************************
 ** \brief  Spi mode.
 **
 ******************************************************************************/
typedef enum en_spi_mode
{
    SpiModeSpi                      = 0u,   ///< Spi mode.
    SpiModeSnyc                     = 1u,   ///< Clock snyc mode.
} en_spi_mode_t;

/**
 *******************************************************************************
 ** \brief  Spi command register length.
 **
 ******************************************************************************/
typedef enum en_spi_cmr
{
    SpiCmr0                         = 0u,   ///< Use CMR0.
    SpiCmr01                        = 1u,   ///< Use CMR0-1.
    SpiCmr012                       = 2u,   ///< Use CMR0-2.
    SpiCmr0123                      = 3u,   ///< Use CMR0-3.
} en_spi_cmr_t;

/**
 *******************************************************************************
 ** \brief  Spi ss pin.
 **
 ******************************************************************************/
typedef enum en_spi_ss_pin
{
    SpiSS0                          = 0u,   ///< Use SS0.
    SpiSS1                          = 1u,   ///< Use SS1.
    SpiSS2                          = 2u,   ///< Use SS2.
    SpiSS3                          = 3u,   ///< Use SS3.
} en_spi_ss_pin_t;

/**
 *******************************************************************************
 ** \brief  Spi function.
 **
 ******************************************************************************/
typedef enum en_spi_func
{
    SpiFuncParity                   = 0u,   ///< Spi parity.
    SpiFuncParityOdd                = 1u,   ///< Spi parity odd.
    SpiFuncDetechModeErr            = 2u,   ///< Spi detech mode error.
    SpiFuncAutoStopSck              = 3u,   ///< Spi auto stop sck before overrun error.
    SpiFuncMosiIdleFixed            = 4u,   ///< Spi mosi idle level fixed.
} en_spi_func_t;

/**
 *******************************************************************************
 ** \brief  Spi mosi idle level.
 **
 ******************************************************************************/
typedef enum en_spi_mosi_idle_lvl
{
    SpiMosiIdleLvlLow               = 0u,   ///< Mosi idle level is low.
    SpiMosiIdleLvlHigh              = 1u,   ///< Mosi idle level is high.
} en_spi_mosi_idle_lvl_t;

/**
 *******************************************************************************
 ** \brief  Spi ss polarity.
 **
 ******************************************************************************/
typedef enum en_spi_ss_pol
{
    SpiSSPolLow                     = 0u,   ///< SS polarity low.
    SpiSSPolHigh                    = 1u,   ///< SS polarity high.
} en_spi_ss_pol_t;

/**
 *******************************************************************************
 ** \brief  Spi interrupt request.
 **
 ******************************************************************************/
typedef enum en_spi_irq
{
    SpiIrqTx                        = 0u,   ///< Transfer buffer empty interrupt.
    SpiIrqRx                        = 1u,   ///< Receiver buffer full or overrun interrupt.
    SpiIrqIdle                      = 2u,   ///< Spi idle interrupt.
    SpiIrqError                     = 3u,   ///< Overrun,underrun,parity error.
} en_spi_irq_t;

/**
 *******************************************************************************
 ** \brief  Spi status flag.
 **
 ******************************************************************************/
typedef enum en_spi_flag
{
    SpiFlagOvr                      = 0u,   ///< Receiver buffer overrun flag.
    SpiFlagUdr                      = 1u,   ///< Transfer buffer underrun flag.
    SpiFlagRxFull                   = 2u,   ///< Receiver buffer full flag.
    SpiFlagTxEmpty                  = 3u,   ///< Transfer buffer empty flag.
    SpiFlagIdle                     = 4u,   ///< Spi idle flag.
    SpiFlagParityErr                = 5u,   ///< Parity error flag.
    SpiFlagModeErr                  = 6u,   ///< Mode error flag.
} en_spi_flag_t;

/**
 *******************************************************************************
 ** \brief  Spi frame count.
 **
 ******************************************************************************/
typedef enum en_spi_frame
{
    SpiFrame1                       = 0u,   ///< Spi frame count 1.
    SpiFrame2                       = 1u,   ///< Spi frame count 2.
    SpiFrame3                       = 2u,   ///< Spi frame count 3.
    SpiFrame4                       = 3u,   ///< Spi frame count 4.
} en_spi_frame_t;

/**
 *******************************************************************************
 ** \brief  Configuration structure of spi command register.
 **
 ******************************************************************************/
typedef struct stc_spi_cmr_config
{
    en_functional_state_t           enSckDelay;         ///< Use default delay clock or enSckDelayClk.

    en_functional_state_t           enSSDelay;          ///< Use default delay clock or enSSDelayClk.

    en_functional_state_t           enNextDelay;        ///< Use default delay clock or enNextDelayClk.

    en_spi_first_bit_t              enFirstBit;         ///< First bit direction.

    en_spi_data_size_t              enDataSize;         ///< Data size.

    en_functional_state_t           enBurst;            ///< Keep active level or not.

    en_spi_clock_div_t              enSpiClkDiv;        ///< Spi clock division from pclk1.

    en_spi_ss_pin_t                 enSSPin;            ///< SS pin selection.

    en_spi_clk_pol_t                enClkPol;           ///< Clock polarity.

    en_spi_clk_pha_t                enClkPha;           ///< Clock phase.
} stc_spi_cmr_config_t;

/**
 *******************************************************************************
 ** \brief  Configuration structure of spi slave selection.
 **
 ******************************************************************************/
typedef struct stc_spi_ss_config
{
    en_spi_ss_pol_t                 enSpiSS0Pol;        ///< SS0 polaity.

    en_spi_ss_pol_t                 enSpiSS1Pol;        ///< SS1 polaity.

    en_spi_ss_pol_t                 enSpiSS2Pol;        ///< SS2 polaity.

    en_spi_ss_pol_t                 enSpiSS3Pol;        ///< SS3 polaity.

    stc_spi_cmr_config_t            *pstcSpiCmr0Cfg;    ///< Re-config cmr0 if use one ss pin.

    stc_spi_cmr_config_t            *pstcSpiCmr1Cfg;    ///< Config cmr1 if use two ss pin.

    stc_spi_cmr_config_t            *pstcSpiCmr2Cfg;    ///< Config cmr2 if use three ss pin.

    stc_spi_cmr_config_t            *pstcSpiCmr3Cfg;    ///< Config cmr3 if use four ss pin.
} stc_spi_ss_config_t;

/**
 *******************************************************************************
 ** \brief  Configuration structure of spi.
 **
 ******************************************************************************/
typedef struct stc_spi_config
{
    uint8_t                         u8BaudRateDiv;      ///< Division from spi clock for baudrate.

    en_spi_delay_clk_t              enSckDelayClk;      ///< Sck delay time.The time between SS set to valid and SCK begin to output.

    en_spi_delay_clk_t              enSSDelayClk;       ///< SS delay time.The time between SS set to invalid and SCK end to output.

    en_spi_delay_clk_t              enNextDelayClk;     ///< Next delay time.The time between SS last invalid and next valid.Add 2 clk on this enum.

    en_spi_msmode_t                 enMsMode;           ///< Master mode or slave mode.

    en_spi_duplex_mode_t            enDuplex;           ///< Duplex mode.

    en_spi_mode_t                   enMode;             ///< Spi mode or Clock sync mode.

    en_spi_mosi_idle_lvl_t          enMosiIdleLvl;      ///< Spi mosi idle level.

    en_spi_frame_t                  enFrame;            ///< Frame count.

    stc_spi_cmr_config_t            *pstcSpiCmr0Cfg;    ///< Use cmr0 in default.
} stc_spi_config_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/

/* Function used to set the M4_SPIx configuration to the default reset state. */
void Spi_DeInit(M4_SPI_TypeDef *M4_SPIx);

/* Initialization and Configuration functions. */
void Spi_Init(M4_SPI_TypeDef *spi, stc_spi_config_t *pstcSpiCfg);

void Spi_CmrConfig(stc_spi_cmr_field_t *M4_SPI_CMR, stc_spi_cmr_config_t *pstcSpiCmrCfg);

void Spi_SsConfig(M4_SPI_TypeDef *M4_SPIx, stc_spi_ss_config_t *pstcSpiSSCfg);

void Spi_CmrStructInit(stc_spi_cmr_config_t *pstcSpiCmrCfg);

void Spi_StructInit(stc_spi_config_t *pstcSpiCfg);

void Spi_Cmd(M4_SPI_TypeDef *M4_SPIx, en_functional_state_t enNewState);

void Spi_FuncCmd(M4_SPI_TypeDef *M4_SPIx, en_spi_func_t enFunc, en_functional_state_t enNewState);

void Spi_SetBaudRate(M4_SPI_TypeDef *M4_SPIx, uint8_t u8Div);

/* Data transfers functions. */
void Spi_SendData(M4_SPI_TypeDef *M4_SPIx, uint32_t u32Data);

uint32_t Spi_ReceiveData(M4_SPI_TypeDef *M4_SPIx);

/* Interrupts and flags management functions. */
void Spi_ITConfig(M4_SPI_TypeDef *M4_SPIx, en_spi_irq_t enIrq, en_functional_state_t enNewState);

en_flag_status_t Spi_GetFlagStatus(M4_SPI_TypeDef *M4_SPIx,  en_spi_flag_t enFlag);

void Spi_ClearFlagStatus(M4_SPI_TypeDef *M4_SPIx,  en_spi_flag_t enFlag);

//@} // SpiGroup

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


