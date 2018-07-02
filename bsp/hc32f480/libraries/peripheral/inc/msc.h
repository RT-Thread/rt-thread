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
/** \file msc.h
 **
 ** A detailed description is available at
 ** @link MscGroup Msc description @endlink
 **
 **   - 2018-05-03  1.0  Jason First version for Device Driver Library of Msc.
 **
 ******************************************************************************/

#ifndef __MSC_H__
#define __MSC_H__

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
 ** \defgroup MscGroup Multifunction serial communication(MSC)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/**
 *******************************************************************************
 ** \brief  Msc spi mode.
 **
 ******************************************************************************/
typedef enum en_msc_spi_mode
{
    MscSpiMaster                    = 0u,   ///< Msc spi master mode.
    MscSpiSlave                     = 1u,   ///< Msc spi slave mode.
} en_msc_spi_mode_t;

/**
 *******************************************************************************
 ** \brief  Msc spi function.
 **
 ******************************************************************************/
typedef enum en_msc_spi_func
{
    MscSpiFuncTx                    = 0u,   ///< Msc spi tx.
    MscSpiFuncRx                    = 1u,   ///< Msc spi rx.
    MscSpiFuncCs                    = 2u,   ///< Msc spi chip selection.
    MscSpiFuncCsErrOccu             = 3u,   ///< Msc spi chip selection error occurs.
    MscSpiFuncCsActiveHold          = 4u,   ///< Msc spi chip selection hold active status.
    MscSpiFuncSOTHigh               = 5u,   ///< Msc spi SOT high.
    MscSpiFuncOutputData            = 6u,   ///< Msc spi output data.Default is set.
} en_msc_spi_func_t;

/**
 *******************************************************************************
 ** \brief  Msc spi interrupt request.
 **
 ******************************************************************************/
typedef enum en_msc_spi_irq
{
    MscSpiIrqTx                     = 0u,   ///< Transfer buffer empty interrupt.
    MscSpiIrqRx                     = 1u,   ///< Receiver buffer full or overrun interrupt.
    MscSpiIrqTxIdle                 = 2u,   ///< Transfer bus idle interrupt.
    MscSpiIrqCsErr                  = 3u,   ///< Chip selection error occurs interrupt.
} en_msc_spi_irq_t;

/**
 *******************************************************************************
 ** \brief  Msc spi status flag.
 **
 ******************************************************************************/
typedef enum en_msc_spi_flag
{
    MscSpiFlagOvr                   = 0u,   ///< Receiver buffer overrun flag.
    MscSpiFlagRxFull                = 1u,   ///< Receiver buffer full flag.
    MscSpiFlagTxEmpty               = 2u,   ///< Transfer buffer empty flag.
    MscSpiFlagTxIdle                = 3u,   ///< Transfer bus idle flag.
    MscSpiFlagCsErr                 = 4u,   ///< Chip selection error occurs flag.
} en_msc_spi_flag_t;

/**
 *******************************************************************************
 ** \brief  Msc spi data size.
 **
 ******************************************************************************/
typedef enum en_msc_spi_data_size
{
    MscSpiDataSize8                 = 0u,   ///< 8 bits.
    MscSpiDataSize5                 = 1u,   ///< 5 bits.
    MscSpiDataSize6                 = 2u,   ///< 6 bits.
    MscSpiDataSize7                 = 3u,   ///< 7 bits.
    MscSpiDataSize9                 = 4u,   ///< 9 bits.
    MscSpiDataSize10                = 5u,   ///< 10 bits.
    MscSpiDataSize11                = 6u,   ///< 11 bits.
    MscSpiDataSize12                = 7u,   ///< 12 bits.
    MscSpiDataSize13                = 8u,   ///< 13 bits.
    MscSpiDataSize14                = 9u,   ///< 14 bits.
    MscSpiDataSize15                = 10u,  ///< 15 bits.
    MscSpiDataSize16                = 11u,  ///< 16 bits
} en_msc_spi_data_size_t;

/**
 *******************************************************************************
 ** \brief  Msc spi clock polarity.
 **
 ******************************************************************************/
typedef enum en_msc_spi_clk_pol
{
    MscSpiClkPolHigh                = 0u,   ///< Clock polarity high.
    MscSpiClkPolLow                 = 1u,   ///< Clock polarit low.
} en_msc_spi_clk_pol_t;

/**
 *******************************************************************************
 ** \brief  Msc spi first bit direction.
 **
 ******************************************************************************/
typedef enum en_msc_spi_first_bit
{
    MscSpiFirstBitLsb               = 0u,   ///< Lsb first.
    MscSpiFirstBitMsb               = 1u,   ///< Msb first.
} en_msc_spi_first_bit_t;

/**
 *******************************************************************************
 ** \brief  The wait count for data continuous transmission or reception.
 **         In slava mode,it should be MscSpiDataWait0.
 **
 ******************************************************************************/
typedef enum en_msc_spi_data_wt_bit
{
    MscSpiDataWait0                 = 0u,   ///< 0 bit wait.
    MscSpiDataWait1                 = 1u,   ///< 1 bit wait.
    MscSpiDataWait2                 = 2u,   ///< 2 bit wait.
    MscSpiDataWait3                 = 3u,   ///< 3 bit wait.
} en_msc_spi_data_wt_bit_t;

/**
 *******************************************************************************
 ** \brief  Msc spi chip selection msc pin polarity.
 **
 ******************************************************************************/
typedef enum en_msc_spi_cs_pin_pol
{
    MscSpiCsPinPolLow               = 0u,   ///< Chip selection polarity low.
    MscSpiCsPinPolHigh              = 1u,   ///< Chip selection polarity high.
} en_msc_spi_cs_pin_pol_t;

/**
 *******************************************************************************
 ** \brief  Msc spi chip selection clock division.
 **
 ******************************************************************************/
typedef enum en_msc_spi_cs_clk_div
{
    MscSpiCsClkDiv1                 = 0u,   ///< cs clock = pclk1.
    MscSpiCsClkDiv2                 = 1u,   ///< cs clock = pclk1/2.
    MscSpiCsClkDiv4                 = 2u,   ///< cs clock = pclk1/4.
    MscSpiCsClkDiv8                 = 3u,   ///< cs clock = pclk1/8.
    MscSpiCsClkDiv16                = 4u,   ///< cs clock = pclk1/16.
    MscSpiCsClkDiv32                = 5u,   ///< cs clock = pclk1/32.
    MscSpiCsClkDiv64                = 6u,   ///< cs clock = pclk1/64.
} en_msc_spi_cs_clk_div_t;

/**
 *******************************************************************************
 ** \brief  Configuration structure of msc spi chip selection pin.
 **
 ** \note   Configures the chip selection pin if needed.
 **
 ******************************************************************************/
typedef struct stc_msc_spi_cs_pin_config
{
    en_msc_spi_cs_pin_pol_t         enPinPol;           ///< Cs pin polarity.

    en_msc_spi_clk_pol_t            enClkPol;           ///< Clock polarity for current chip selection.

    en_msc_spi_first_bit_t          enFirstBit;         ///< First bit direction for current chip selection.

    en_msc_spi_data_size_t          enDataSize;         ///< Data size for current chip selection.
} stc_msc_spi_cs_pin_config_t;

/**
 *******************************************************************************
 ** \brief  Configuration structure of msc spi chip selection.
 **
 ** \note   Configures the chip selection pin if needed.
 **
 ******************************************************************************/
typedef struct stc_msc_spi_cs_config
{
    uint8_t                         u8SetupDelay;       ///< Setup delay time.The time between SCS set to valid and SCK begin to output.

    uint8_t                         u8HoldDelay;        ///< Hold delay time.The time between SCS set to invalid and SCK end to output.

    uint16_t                        u16DeselectDelay;   ///< Deselect delay time.The time between SCS last invalid and next valid.

    uint8_t                         u8ScsPinSel;        ///< Select scs pin.Eg:MSC_SPI_CS_PIN0 | MSC_SPI_CS_PIN1.

    uint8_t                         u8ScsPinStart;      ///< Scs start pin.

    uint8_t                         u8ScsPinEnd;        ///< Scs end pin.

    en_msc_spi_cs_pin_pol_t         enScs0PinPol;       ///< Scs0 pin polarity.

    en_msc_spi_cs_clk_div_t         enCsClkDiv;         ///< Clock division for chip selection.For setup,hold,deselect delay.

    stc_msc_spi_cs_pin_config_t     *pstcScs1Cfg;       ///< Configuration structure for scs1 pin.

    stc_msc_spi_cs_pin_config_t     *pstcScs2Cfg;       ///< Configuration structure for scs2 pin.
}stc_msc_spi_cs_config_t;

/**
 *******************************************************************************
 ** \brief  Configuration structure of msc spi.
 **
 ******************************************************************************/
typedef struct stc_msc_spi_config
{
    uint32_t                        u32BaudRate;        ///< Baudrate.

    en_msc_spi_mode_t               enMode;             ///< Master mode or slave mode.

    en_msc_spi_data_size_t          enDataSize;         ///< Data size.

    en_msc_spi_clk_pol_t            enClkPol;           ///< Clock polarity.Only valid in master mode.

    en_msc_spi_first_bit_t          enFirstBit;         ///< First bit direction.

    en_msc_spi_data_wt_bit_t        enWaitBit;          ///< Wait count for data continuous transmission or reception.

} stc_msc_spi_config_t;
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

#define MSC_SPI_CS_PIN0             0x80
#define MSC_SPI_CS_PIN1             0x01
#define MSC_SPI_CS_PIN2             0x02

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/

/* Function used to set the M4_MSCx_SPI configuration to the default reset state. */
void Msc_Spi_DeInit(M4_MSC_SPI_TypeDef *M4_MSCx_SPI);

/* Initialization and Configuration functions. */
void Msc_Spi_Init(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, stc_msc_spi_config_t *pstcMscSpiCfg);

void Msc_Spi_CsConfig(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, stc_msc_spi_cs_config_t *pstcMscSpiCsCfg);

void Msc_Spi_StructInit(stc_msc_spi_config_t *pstcMscSpiCfg);

void Msc_Spi_CsStructInit(stc_msc_spi_cs_config_t *pstcMscSpiCsCfg);

void Msc_Spi_FuncCmd(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, en_msc_spi_func_t enFunc, en_functional_state_t enNewState);

void Msc_Spi_SetBaudRate(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, uint32_t u32BaudRate);

void Msc_Spi_SetDataSize(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, en_msc_spi_data_size_t enDataSize);

void Msc_Spi_SetCsTxBytes(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, uint8_t u8CsPin, uint8_t u8Cnt);

/* Data transfers functions. */
void Msc_Spi_SendData(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, uint16_t u16Data);

uint16_t Msc_Spi_ReceiveData(M4_MSC_SPI_TypeDef *M4_MSCx_SPI);

/* Interrupts and flags management functions. */
void Msc_Spi_ITConfig(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, en_msc_spi_irq_t enIrq, en_functional_state_t enNewState);

en_flag_status_t Msc_Spi_GetFlagStatus(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, en_msc_spi_flag_t enFlag);

void Msc_Spi_ClearFlagStatus(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, en_msc_spi_flag_t enFlag);

//@} // MscGroup

#ifdef __cplusplus
}
#endif

#endif /* __MSC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

