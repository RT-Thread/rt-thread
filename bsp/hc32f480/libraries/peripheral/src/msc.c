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
/** \file msc.c
 **
 ** A detailed description is available at
 ** @link MscGroup Msc description @endlink
 **
 **   - 2018-05-03  1.0  Jason First version for Device Driver Library of Msc.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "clk.h"
#include "msc.h"

/**
 *******************************************************************************
 ** \addtogroup MscGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
typedef enum en_msc_mode
{
    MscModeUsartNormal                  = 0u,
    MscModeUsartMultiSlave              = 1u,
    MscModeUsartSpi                     = 2u,
    MscModeUsartI2c                     = 4u,
} en_msc_mode_t;

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

#define MSC_SPI_BR_MIN                  3
#define MSC_SPI_BR_DEFAULT              (200*1000)

#define MSC_SPI_CR_DEFAULT              (0x00)
#define MSC_SPI_MR_DEFAULT              (0x00)
#define MSC_SPI_SR_DEFAULT              (0x03)
#define MSC_SPI_ECR_DEFAULT             (0x00)
#define MSC_SPI_EACR_DEFAULT            (0x0000)
#define MSC_SPI_CSCR_DEFAULT            (0x00)
#define MSC_SPI_CSTMG0_DEFAULT          (0x00)
#define MSC_SPI_CSTMG1_DEFAULT          (0x00)
#define MSC_SPI_CSTMG23_DEFAULT         (0x0000)
#define MSC_SPI_CSFR1_DEFAULT           (0x00)
#define MSC_SPI_CSFR2_DEFAULT           (0x00)
#define MSC_SPI_TBYTE0_DEFAULT          (0x00)
#define MSC_SPI_TBYTE1_DEFAULT          (0x00)
#define MSC_SPI_TBYTE2_DEFAULT          (0x00)
#define MSC_SPI_BR_RESET_DEFAULT        (0x0000)

#define MSC_MODE(mscx, mode)            (mscx->SMR_f.MODE = mode)

/*! Parameter validity check for spi peripheral \a per. */
#define IS_MSC_SPI_ALL_PERIPH(per)                                             \
(   ((M4_MSC0_SPI)          ==  (per))  ||                                     \
    ((M4_MSC1_SPI)          ==  (per))  ||                                     \
    ((M4_MSC2_SPI)          ==  (per))                                         \
)

/*! Parameter validity check for spi mode \a mode. */
#define IS_MSC_SPI_MODE(mode)                                                  \
(   ((MscSpiMaster)         ==  (mode)) ||                                     \
    ((MscSpiSlave)          ==  (mode))                                        \
)

/*! Parameter validity check for spi data size \a size. */
#define IS_MSC_SPI_DATA_SIZE(size)                                             \
(   ((MscSpiDataSize8)      ==  (size)) ||                                     \
    ((MscSpiDataSize5)      ==  (size)) ||                                     \
    ((MscSpiDataSize6)      ==  (size)) ||                                     \
    ((MscSpiDataSize7)      ==  (size)) ||                                     \
    ((MscSpiDataSize9)      ==  (size)) ||                                     \
    ((MscSpiDataSize10)     ==  (size)) ||                                     \
    ((MscSpiDataSize11)     ==  (size)) ||                                     \
    ((MscSpiDataSize12)     ==  (size)) ||                                     \
    ((MscSpiDataSize13)     ==  (size)) ||                                     \
    ((MscSpiDataSize14)     ==  (size)) ||                                     \
    ((MscSpiDataSize15)     ==  (size))                                        \
)

/*! Parameter validity check for spi clock polarity \a pol. */
#define IS_MSC_SPI_CLK_POL(pol)                                                \
(   ((MscSpiClkPolHigh)     ==  (pol))  ||                                     \
    ((MscSpiClkPolLow)      ==  (pol))                                         \
)

/*! Parameter validity check for spi first bit \a bit. */
#define IS_MSC_SPI_FIRST_BIT(bit)                                              \
(   ((MscSpiFirstBitLsb)    ==  (bit))  ||                                     \
    ((MscSpiFirstBitMsb)    ==  (bit))                                         \
)

/*! Parameter validity check for spi wait time bit \a bit during tx or rx
    continuously in master mode. */
#define IS_MSC_SPI_WAIT_BIT(bit)                                               \
(   ((MscSpiDataWait0)      ==  (bit))  ||                                     \
    ((MscSpiDataWait1)      ==  (bit))  ||                                     \
    ((MscSpiDataWait2)      ==  (bit))  ||                                     \
    ((MscSpiDataWait3)      ==  (bit))                                         \
)

/*! Parameter validity check for spi function \a func. */
#define IS_MSC_SPI_FUNC(func)                                                  \
(   ((MscSpiFuncTx)         ==  (func)) ||                                     \
    ((MscSpiFuncRx)         ==  (func)) ||                                     \
    ((MscSpiFuncCs)         ==  (func)) ||                                     \
    ((MscSpiFuncCsErrOccu)  ==  (func)) ||                                     \
    ((MscSpiFuncCsActiveHold)== (func)) ||                                     \
    ((MscSpiFuncSOTHigh)    ==  (func)) ||                                     \
    ((MscSpiFuncOutputData) ==  (func))                                        \
)

/*! Parameter validity check for spi interrupt request \a irq. */
#define IS_MSC_SPI_IRQ(irq)                                                    \
(   ((MscSpiIrqTx)          ==  (irq))      ||                                 \
    ((MscSpiIrqRx)          ==  (irq))      ||                                 \
    ((MscSpiIrqTxIdle)      ==  (irq))      ||                                 \
    ((MscSpiIrqCsErr)       ==  (irq))                                         \
)

/*! Parameter validity check for spi flag \a flag. */
#define IS_MSC_SPI_FLAG(flag)                                                  \
(   ((MscSpiFlagOvr)        ==  (flag)) ||                                     \
    ((MscSpiFlagRxFull)     ==  (flag)) ||                                     \
    ((MscSpiFlagTxEmpty)    ==  (flag)) ||                                     \
    ((MscSpiFlagTxIdle)     ==  (flag)) ||                                     \
    ((MscSpiFlagCsErr)      ==  (flag))                                        \
)

/*! Parameter validity check for spi cs pin \a pin. */
#define IS_MSC_SPI_CS_PIN(pin)                                                 \
(   ((MSC_SPI_CS_PIN0)      ==  (pin))  ||                                     \
    ((MSC_SPI_CS_PIN1)      ==  (pin))  ||                                     \
    ((MSC_SPI_CS_PIN2)      ==  (pin))                                         \
)

/*! Parameter validity check for spi cs pin polarity \a pol. */
#define IS_MSC_SPI_CS_PIN_POL(pol)                                             \
(   ((MscSpiCsPinPolLow)    ==  (pol))  ||                                     \
    ((MscSpiCsPinPolHigh)   ==  (pol))                                         \
)

/*! Parameter validity check for spi cs clock division \a div. */
#define IS_MSC_SPI_CS_CLK_DIV(div)                                             \
(   ((MscSpiCsClkDiv1)      ==  (div))  ||                                     \
    ((MscSpiCsClkDiv2)      ==  (div))  ||                                     \
    ((MscSpiCsClkDiv4)      ==  (div))  ||                                     \
    ((MscSpiCsClkDiv8)      ==  (div))  ||                                     \
    ((MscSpiCsClkDiv16)     ==  (div))  ||                                     \
    ((MscSpiCsClkDiv32)     ==  (div))  ||                                     \
    ((MscSpiCsClkDiv64)     ==  (div))                                         \
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
 ** \brief  Deinitialize the M4_MSCx_SPI peripheral registers to their default
 **         reset values.
 **
 ** \param  [in] M4_MSCx_SPI            To select the msc spi peripheral,where x
 **                                     can be:0,1 or 2.
 ** \arg    M4_MSC0_SPI                 The spi peripheral of msc0.
 ** \arg    M4_MSC1_SPI                 The spi peripheral of msc1.
 ** \arg    M4_MSC2_SPI                 The spi peripheral of msc2.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Msc_Spi_DeInit(M4_MSC_SPI_TypeDef *M4_MSCx_SPI)
{
    DDL_ASSERT(IS_MSC_SPI_ALL_PERIPH(M4_MSCx_SPI));

    M4_MSCx_SPI->SCR = MSC_SPI_CR_DEFAULT;
    M4_MSCx_SPI->SMR = MSC_SPI_MR_DEFAULT;
    M4_MSCx_SPI->SR = MSC_SPI_SR_DEFAULT;
    M4_MSCx_SPI->ECR = MSC_SPI_ECR_DEFAULT;
    M4_MSCx_SPI->EACR = MSC_SPI_EACR_DEFAULT;
    M4_MSCx_SPI->CSCR = MSC_SPI_CSCR_DEFAULT;
    M4_MSCx_SPI->CSTMG0 = MSC_SPI_CSTMG0_DEFAULT;
    M4_MSCx_SPI->CSTMG1 = MSC_SPI_CSTMG1_DEFAULT;
    M4_MSCx_SPI->CSTMG23 = MSC_SPI_CSTMG23_DEFAULT;
    M4_MSCx_SPI->CSFR1 = MSC_SPI_CSFR1_DEFAULT;
    M4_MSCx_SPI->CSFR2 = MSC_SPI_CSFR2_DEFAULT;
    M4_MSCx_SPI->TBYTE0 = MSC_SPI_TBYTE0_DEFAULT;
    M4_MSCx_SPI->TBYTE1 = MSC_SPI_TBYTE1_DEFAULT;
    M4_MSCx_SPI->TBYTE2 = MSC_SPI_TBYTE2_DEFAULT;
    M4_MSCx_SPI->BRS = MSC_SPI_BR_RESET_DEFAULT;
}

/**
 *******************************************************************************
 ** \brief  Initialize the M4_MSCx_SPI peripheral registers according to the
 **         specified parameters in the pstcMscSpiCfg.
 **
 ** \param  [in] M4_MSCx_SPI            To select the msc spi peripheral,where x
 **                                     can be:0,1 or 2.
 ** \arg    M4_MSC0_SPI                 The spi peripheral of msc0.
 ** \arg    M4_MSC1_SPI                 The spi peripheral of msc1.
 ** \arg    M4_MSC2_SPI                 The spi peripheral of msc2.
 **
 ** \param  [in] pstcMscSpiCfg          Pointer to a stc_msc_spi_config_t
 **                                     structure that contains the configuration
 **                                     information for the specified msc spi peripheral.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Msc_Spi_Init(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, stc_msc_spi_config_t *pstcMscSpiCfg)
{
    DDL_ASSERT(IS_MSC_SPI_ALL_PERIPH(M4_MSCx_SPI));
    DDL_ASSERT(NULL != pstcMscSpiCfg);

    DDL_ASSERT(IS_MSC_SPI_MODE(pstcMscSpiCfg->enMode));
    DDL_ASSERT(IS_MSC_SPI_DATA_SIZE(pstcMscSpiCfg->enDataSize));
    DDL_ASSERT(IS_MSC_SPI_CLK_POL(pstcMscSpiCfg->enClkPol));
    DDL_ASSERT(IS_MSC_SPI_FIRST_BIT(pstcMscSpiCfg->enFirstBit));
    DDL_ASSERT(IS_MSC_SPI_WAIT_BIT(pstcMscSpiCfg->enWaitBit));

    /* Reset. Set PCL bit to reset spi. */
    M4_MSCx_SPI->SCR_f.PCL = Set;

    /* Switch msc to spi mode after set PCL. */
    MSC_MODE(M4_MSCx_SPI, MscModeUsartSpi);

    /* Default is Set. */
    M4_MSCx_SPI->SCR_f.SPIMODE = Set;
    M4_MSCx_SPI->SMR_f.DOE = Set;

    /* Master mode or slave mode. */
    M4_MSCx_SPI->SCR_f.MSS = pstcMscSpiCfg->enMode;
    if(MscSpiMaster == pstcMscSpiCfg->enMode)
    {
        /* Enable SCK output and set wait bit by config in master mode. */
        M4_MSCx_SPI->SMR_f.CKE = Set;
        M4_MSCx_SPI->ECR_f.DTRWS = pstcMscSpiCfg->enWaitBit;
    }
    else
    {
        /* Disable SCK output and reset wait bit in slave mode. */
        M4_MSCx_SPI->SMR_f.CKE = Reset;
        M4_MSCx_SPI->ECR_f.DTRWS = Reset;
    }

    /* Set data size by config. */
    M4_MSCx_SPI->ECR_f.DL = pstcMscSpiCfg->enDataSize & 0x7;
    if(MscSpiDataSize13 <= pstcMscSpiCfg->enDataSize)
    {
        M4_MSCx_SPI->ECR_f.DL3 = Set;
    }

    /* Set SCK polarity and first bit by config. */
    M4_MSCx_SPI->SMR_f.CINV = pstcMscSpiCfg->enClkPol;
    M4_MSCx_SPI->SMR_f.TDS = pstcMscSpiCfg->enFirstBit;

    Msc_Spi_SetBaudRate(M4_MSCx_SPI, pstcMscSpiCfg->u32BaudRate);
}

/**
 *******************************************************************************
 ** \brief  Initialize the M4_MSCx_SPI peripheral registers according to the
 **         specified parameters in the pstcMscSpiCsCfg.
 **
 ** \param  [in] M4_MSCx_SPI            To select the msc spi peripheral,where x
 **                                     can be:0,1 or 2.
 ** \arg    M4_MSC0_SPI                 The spi peripheral of msc0.
 ** \arg    M4_MSC1_SPI                 The spi peripheral of msc1.
 ** \arg    M4_MSC2_SPI                 The spi peripheral of msc2.
 **
 ** \param  [in] pstcMscSpiCsCfg        Pointer to a stc_msc_spi_cs_config_t
 **                                     structure that contains the configuration
 **                                     information for the specified msc spi
 **                                     peripheral about chip selection.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Msc_Spi_CsConfig(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, stc_msc_spi_cs_config_t *pstcMscSpiCsCfg)
{
    DDL_ASSERT(IS_MSC_SPI_ALL_PERIPH(M4_MSCx_SPI));
    DDL_ASSERT(NULL != pstcMscSpiCsCfg);

    DDL_ASSERT(MscSpiSlave != M4_MSCx_SPI->SCR_f.MSS);
    DDL_ASSERT(IS_MSC_SPI_CS_PIN(pstcMscSpiCsCfg->u8ScsPinStart));
    DDL_ASSERT(IS_MSC_SPI_CS_PIN(pstcMscSpiCsCfg->u8ScsPinEnd));
    DDL_ASSERT(IS_MSC_SPI_CS_PIN_POL(pstcMscSpiCsCfg->enScs0PinPol));
    DDL_ASSERT(IS_MSC_SPI_CS_CLK_DIV(pstcMscSpiCsCfg->enCsClkDiv));

    /* Start and End pin. */
    M4_MSCx_SPI->CSCR_f.CSAS = pstcMscSpiCsCfg->u8ScsPinStart;
    M4_MSCx_SPI->CSCR_f.CSAE = pstcMscSpiCsCfg->u8ScsPinEnd;

    /* Clock div. */
    M4_MSCx_SPI->CSCR_f.CSTODIV = pstcMscSpiCsCfg->enCsClkDiv;

    /* Delay time. */
    M4_MSCx_SPI->CSTMG1 = pstcMscSpiCsCfg->u8SetupDelay;
    M4_MSCx_SPI->CSTMG0 = pstcMscSpiCsCfg->u8HoldDelay;
    M4_MSCx_SPI->CSTMG23 = pstcMscSpiCsCfg->u16DeselectDelay;

    /* Config scs0 pin. */
    if(MSC_SPI_CS_PIN0 & pstcMscSpiCsCfg->u8ScsPinSel)
    {
        /* Scs0 pin enable. */
        M4_MSCx_SPI->CSCR_f.CSEN0 = Set;
        /* Scs0 pin polarity. */
        M4_MSCx_SPI->CSCR_f.CSLVS = Set;
    }

    /* If scs1 or scs2 pin selected.Enable csfe and config them. */
    if(MSC_SPI_CS_PIN1 & pstcMscSpiCsCfg->u8ScsPinSel || MSC_SPI_CS_PIN2 & pstcMscSpiCsCfg->u8ScsPinSel)
    {
        M4_MSCx_SPI->ECR_f.CSFE = Set;
    }

    /* Scs1 pin config. */
    if(MSC_SPI_CS_PIN1 & pstcMscSpiCsCfg->u8ScsPinSel)
    {
        DDL_ASSERT(NULL != pstcMscSpiCsCfg->pstcScs1Cfg);
        DDL_ASSERT(IS_MSC_SPI_CS_PIN_POL(pstcMscSpiCsCfg->pstcScs1Cfg->enPinPol));
        DDL_ASSERT(IS_MSC_SPI_CLK_POL(pstcMscSpiCsCfg->pstcScs1Cfg->enClkPol));
        DDL_ASSERT(IS_MSC_SPI_FIRST_BIT(pstcMscSpiCsCfg->pstcScs1Cfg->enFirstBit));
        DDL_ASSERT(IS_MSC_SPI_DATA_SIZE(pstcMscSpiCsCfg->pstcScs1Cfg->enDataSize));

        /* Scs1 pin enable. */
        M4_MSCx_SPI->CSCR_f.CSEN1 = Set;
        /* Scs1 pin polarity,clock polarity,first bit and data size. */
        M4_MSCx_SPI->CSFR1_f.CSLVS = pstcMscSpiCsCfg->pstcScs1Cfg->enPinPol;
        M4_MSCx_SPI->CSFR1_f.CINV = pstcMscSpiCsCfg->pstcScs1Cfg->enClkPol;
        M4_MSCx_SPI->CSFR1_f.TDS = pstcMscSpiCsCfg->pstcScs1Cfg->enFirstBit;
        M4_MSCx_SPI->CSFR1_f.DL = pstcMscSpiCsCfg->pstcScs1Cfg->enDataSize;
    }

    /* Scs2 pin config. */
    if(MSC_SPI_CS_PIN2 & pstcMscSpiCsCfg->u8ScsPinSel)
    {
        DDL_ASSERT(NULL != pstcMscSpiCsCfg->pstcScs2Cfg);
        DDL_ASSERT(IS_MSC_SPI_CS_PIN_POL(pstcMscSpiCsCfg->pstcScs2Cfg->enPinPol));
        DDL_ASSERT(IS_MSC_SPI_CLK_POL(pstcMscSpiCsCfg->pstcScs2Cfg->enClkPol));
        DDL_ASSERT(IS_MSC_SPI_FIRST_BIT(pstcMscSpiCsCfg->pstcScs2Cfg->enFirstBit));
        DDL_ASSERT(IS_MSC_SPI_DATA_SIZE(pstcMscSpiCsCfg->pstcScs2Cfg->enDataSize));

        /* Scs2 pin enable. */
        M4_MSCx_SPI->CSCR_f.CSEN2 = Set;
        /* Scs2 pin polarity,clock polarity,first bit and data size. */
        M4_MSCx_SPI->CSFR2_f.CSLVS = pstcMscSpiCsCfg->pstcScs2Cfg->enPinPol;
        M4_MSCx_SPI->CSFR2_f.CINV = pstcMscSpiCsCfg->pstcScs2Cfg->enClkPol;
        M4_MSCx_SPI->CSFR2_f.TDS = pstcMscSpiCsCfg->pstcScs2Cfg->enFirstBit;
        M4_MSCx_SPI->CSFR2_f.DL = pstcMscSpiCsCfg->pstcScs2Cfg->enDataSize;
    }
}

/**
 *******************************************************************************
 ** \brief  Fills each pstcMscSpiCfg member with its default value.
 **
 ** \param  [in] pstcMscSpiCfg          Pointer to a stc_msc_spi_config_t
 **                                     structure that contains the configuration
 **                                     information for the specified msc spi peripheral.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Msc_Spi_StructInit(stc_msc_spi_config_t *pstcMscSpiCfg)
{
    DDL_ASSERT(NULL != pstcMscSpiCfg);

    pstcMscSpiCfg->u32BaudRate = MSC_SPI_BR_DEFAULT;

    pstcMscSpiCfg->enMode = MscSpiMaster;

    pstcMscSpiCfg->enDataSize = MscSpiDataSize8;

    pstcMscSpiCfg->enClkPol = MscSpiClkPolHigh;

    pstcMscSpiCfg->enFirstBit = MscSpiFirstBitLsb;

    pstcMscSpiCfg->enWaitBit = MscSpiDataWait0;
}

/**
 *******************************************************************************
 ** \brief  Fills each pstcMscSpiCsCfg member with its default value.
 **
 ** \param  [in] pstcMscSpiCsCfg        Pointer to a stc_msc_spi_cs_config_t
 **                                     structure that contains the configuration
 **                                     information for the specified msc spi
 **                                     peripheral about chip selection.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Msc_Spi_CsStructInit(stc_msc_spi_cs_config_t *pstcMscSpiCsCfg)
{
    DDL_ASSERT(NULL != pstcMscSpiCsCfg);

    /* Setup,hold,deselect delay. */
    pstcMscSpiCsCfg->u8SetupDelay = 0u;
    pstcMscSpiCsCfg->u8HoldDelay = 0u;
    pstcMscSpiCsCfg->u16DeselectDelay = 0u;

    /* Scs pin select. */
    pstcMscSpiCsCfg->u8ScsPinSel = MSC_SPI_CS_PIN0;
    pstcMscSpiCsCfg->u8ScsPinStart = MSC_SPI_CS_PIN0;
    pstcMscSpiCsCfg->u8ScsPinEnd = MSC_SPI_CS_PIN0;

    /* Scs0 pin polarity and clock division for cs. */
    pstcMscSpiCsCfg->enScs0PinPol = MscSpiCsPinPolLow;
    pstcMscSpiCsCfg->enCsClkDiv = MscSpiCsClkDiv1;

    /* Configurature pointer for scs1 and scs2. */
    pstcMscSpiCsCfg->pstcScs1Cfg = NULL;
    pstcMscSpiCsCfg->pstcScs2Cfg = NULL;
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the specified Msc spi function.
 **
 ** \param  [in] M4_MSCx_SPI            To select the msc spi peripheral,where x
 **                                     can be:0,1 or 2.
 ** \arg    M4_MSC0_SPI                 The spi peripheral of msc0.
 ** \arg    M4_MSC1_SPI                 The spi peripheral of msc1.
 ** \arg    M4_MSC2_SPI                 The spi peripheral of msc2.
 **
 ** \param  [in] enFunc                 Msc spi function types.
 ** \arg    MscSpiFuncTx                Enable msc spi data transmission or not.
 ** \arg    MscSpiFuncRx                Enable msc spi data reception or not.
 ** \arg    MscSpiFuncCs                Output msc spi chip selection or not.
 ** \arg    MscSpiFuncCsErrOccu         Occur msc spi chip selection error or not.
 ** \arg    MscSpiFuncCsActiveHold      Hold msc spi chip selection active status or not.
 ** \arg    MscSpiFuncSOTHigh           Set to SOT high.Reset to ignore.
 ** \arg    MscSpiFuncOutputData        Set to data output.Reset to SCK output only.
 **
 ** \param  [in] enNewState             The new state of the msc spi function.
 ** \arg    Enable                      Enable.
 ** \arg    Disable                     Disable.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Msc_Spi_FuncCmd(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, en_msc_spi_func_t enFunc, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_MSC_SPI_ALL_PERIPH(M4_MSCx_SPI));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_MSC_SPI_FUNC(enFunc));

    switch(enFunc)
    {
        /* Enable or disable msc spi data transmission. */
        case MscSpiFuncTx:
            M4_MSCx_SPI->SCR_f.TXE = (Enable == enNewState ? Set : Reset);
            break;
        /* Enable or disable msc spi data reception. */
        case MscSpiFuncRx:
            M4_MSCx_SPI->SCR_f.RXE = (Enable == enNewState ? Set : Reset);
            break;
        /* Output msc spi chip select or not. */
        case MscSpiFuncCs:
            M4_MSCx_SPI->CSCR_f.CSOE = (Enable == enNewState ? Set : Reset);
            break;
        /* Enable or disable msc spi chip select occur error. */
        case MscSpiFuncCsErrOccu:
            M4_MSCx_SPI->EACR_f.TBEE = (Enable == enNewState ? Set : Reset);
            break;
        /* Enable or disable msc spi chip select occur error. */
        case MscSpiFuncCsActiveHold:
            M4_MSCx_SPI->CSCR_f.CSAH = (Enable == enNewState ? Set : Reset);
            break;
        case MscSpiFuncSOTHigh:
            M4_MSCx_SPI->ECR_f.SOPS = (Enable == enNewState ? Set : Reset);
            break;
        case MscSpiFuncOutputData:
            M4_MSCx_SPI->SMR_f.DOE = (Enable == enNewState ? Set : Reset);
            break;

        /* Do not add default because assert function has check parameter. */
    }
}

/**
 *******************************************************************************
 ** \brief  Set baudrate for M4_MSCx_SPI.
 **
 ** \param  [in] M4_MSCx_SPI            To select the msc spi peripheral,where x
 **                                     can be:0,1 or 2.
 ** \arg    M4_MSC0_SPI                 The spi peripheral of msc0.
 ** \arg    M4_MSC1_SPI                 The spi peripheral of msc1.
 ** \arg    M4_MSC2_SPI                 The spi peripheral of msc2.
 **
 ** \param  [in] u32BaudRate            Baudrate value.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Msc_Spi_SetBaudRate(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, uint32_t u32BaudRate)
{
    uint16_t temp;
    stc_clk_freq_t stcClkFreq;

    DDL_ASSERT(IS_MSC_SPI_ALL_PERIPH(M4_MSCx_SPI));
    DDL_ASSERT(0 != u32BaudRate);

    Clk_GetClockFreq(&stcClkFreq);
    temp = stcClkFreq.pclk1Freq / u32BaudRate - 1;

    DDL_ASSERT(MSC_SPI_BR_MIN < temp);

    M4_MSCx_SPI->BRS = temp;
}

/**
 *******************************************************************************
 ** \brief  Set data size for M4_MSCx_SPI.
 **
 ** \param  [in] M4_MSCx_SPI            To select the msc spi peripheral,where x
 **                                     can be:0,1 or 2.
 ** \arg    M4_MSC0_SPI                 The spi peripheral of msc0.
 ** \arg    M4_MSC1_SPI                 The spi peripheral of msc1.
 ** \arg    M4_MSC2_SPI                 The spi peripheral of msc2.
 **
 ** \param  [in] en_msc_spi_data_size_t enDataSize.
 ** \arg    MscSpiDataSize8             8-bit size.
 ** \arg    MscSpiDataSize5             5-bit size.
 ** \arg    MscSpiDataSize6             6-bit size.
 ** \arg    MscSpiDataSize7             7-bit size.
 ** \arg    MscSpiDataSize9             9-bit size.
 ** \arg    MscSpiDataSize10            10-bit size.
 ** \arg    MscSpiDataSize11            11-bit size.
 ** \arg    MscSpiDataSize12            12-bit size.
 ** \arg    MscSpiDataSize13            13-bit size.
 ** \arg    MscSpiDataSize14            14-bit size.
 ** \arg    MscSpiDataSize15            15-bit size.
 ** \arg    MscSpiDataSize16            16-bit size.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Msc_Spi_SetDataSize(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, en_msc_spi_data_size_t enDataSize)
{
    DDL_ASSERT(IS_MSC_SPI_ALL_PERIPH(M4_MSCx_SPI));
    DDL_ASSERT(IS_MSC_SPI_DATA_SIZE(enDataSize));

    M4_MSCx_SPI->ECR_f.DL = enDataSize;
    if(MscSpiDataSize13 <= enDataSize)
    {
        M4_MSCx_SPI->ECR_f.DL3 = Set;
    }
}

/**
 *******************************************************************************
 ** \brief  Set chip select data transmission count for M4_MSCx_SPI.
 **
 ** \param  [in] M4_MSCx_SPI            To select the msc spi peripheral,where x
 **                                     can be:0,1 or 2.
 ** \arg    M4_MSC0_SPI                 The spi peripheral of msc0.
 ** \arg    M4_MSC1_SPI                 The spi peripheral of msc1.
 ** \arg    M4_MSC2_SPI                 The spi peripheral of msc2.
 **
 ** \param  [in] u8CsPin                Scs pin 0-2.
 ** \arg    MSC_SPI_CS_PIN0             Scs0.
 ** \arg    MSC_SPI_CS_PIN1             Scs1.
 ** \arg    MSC_SPI_CS_PIN2             Scs2.
 **
 ** \param  [in] u8Cnt                  Transfer count.
 **
 ** \retval None
 **
 ** \note   Send en_msc_spi_data_size_t*u8Cnt data in a chip select and then
 **         current scs pin is invalid.
 **
 ******************************************************************************/
void Msc_Spi_SetCsTxBytes(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, uint8_t u8CsPin, uint8_t u8Cnt)
{
    DDL_ASSERT(IS_MSC_SPI_ALL_PERIPH(M4_MSCx_SPI));
    DDL_ASSERT(IS_MSC_SPI_CS_PIN(u8CsPin));

    switch(u8CsPin)
    {
        case MSC_SPI_CS_PIN0:
            M4_MSCx_SPI->TBYTE0 = u8Cnt;
            break;
        case MSC_SPI_CS_PIN1:
            M4_MSCx_SPI->TBYTE1 = u8Cnt;
            break;
        case MSC_SPI_CS_PIN2:
            M4_MSCx_SPI->TBYTE2 = u8Cnt;
            break;

        /* Do not add default because assert function has check parameter. */
    }
}

/**
 *******************************************************************************
 ** \brief  Send a data through a M4_MSCx_SPI.
 **
 ** \param  [in] M4_MSCx_SPI            To select the msc spi peripheral,where x
 **                                     can be:0,1 or 2.
 ** \arg    M4_MSC0_SPI                 The spi peripheral of msc0.
 ** \arg    M4_MSC1_SPI                 The spi peripheral of msc1.
 ** \arg    M4_MSC2_SPI                 The spi peripheral of msc2.
 **
 ** \param  [in] u16Data                Data.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Msc_Spi_SendData(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, uint16_t u16Data)
{
    DDL_ASSERT(IS_MSC_SPI_ALL_PERIPH(M4_MSCx_SPI));

    M4_MSCx_SPI->TXDR_RXDR = u16Data;
}

/**
 *******************************************************************************
 ** \brief  Receive a data through a M4_MSCx_SPI.
 **
 ** \param  [in] M4_MSCx_SPI            To select the msc spi peripheral,where x
 **                                     can be:0,1 or 2.
 ** \arg    M4_MSC0_SPI                 The spi peripheral of msc0.
 ** \arg    M4_MSC1_SPI                 The spi peripheral of msc1.
 ** \arg    M4_MSC2_SPI                 The spi peripheral of msc2.
 **
 ** \retval uint16_t                    Data received.
 **
 ** \note   None
 **
 ******************************************************************************/
uint16_t Msc_Spi_ReceiveData(M4_MSC_SPI_TypeDef *M4_MSCx_SPI)
{
    DDL_ASSERT(IS_MSC_SPI_ALL_PERIPH(M4_MSCx_SPI));

    return M4_MSCx_SPI->TXDR_RXDR;
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the specified M4_MSCx_SPI interrupts.
 **
 ** \param  [in] M4_MSCx_SPI            To select the msc spi peripheral,where x
 **                                     can be:0,1 or 2.
 ** \arg    M4_MSC0_SPI                 The spi peripheral of msc0.
 ** \arg    M4_MSC1_SPI                 The spi peripheral of msc1.
 ** \arg    M4_MSC2_SPI                 The spi peripheral of msc2.
 **
 ** \param  [in] enIrq                  Specifies the msc spi interrupt type.
 ** \arg    MscSpiIrqTx                 TX interrupt.
 ** \arg    MscSpiIrqRx                 RX interrupt
 ** \arg    MscSpiIrqTxIdle             TX bus idle interrupt.
 ** \arg    MscSpiIrqCsErr              Chip selection error interrupt.
 **
 ** \param  [in] enNewState             The new state of the msc spi interrupt.
 ** \arg    Enable                      Enable.
 ** \arg    Disable                     Disable.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Msc_Spi_ITConfig(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, en_msc_spi_irq_t enIrq, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_MSC_SPI_ALL_PERIPH(M4_MSCx_SPI));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_MSC_SPI_IRQ(enIrq));

    switch(enIrq)
    {
        case MscSpiIrqTx:
            M4_MSCx_SPI->SCR_f.TXIE = (Enable == enNewState ? Set : Reset);
            break;
        case MscSpiIrqRx:
            M4_MSCx_SPI->SCR_f.RXIE = (Enable == enNewState ? Set : Reset);
            break;
        case MscSpiIrqTxIdle:
            M4_MSCx_SPI->SCR_f.TBIE = (Enable == enNewState ? Set : Reset);
            break;
        case MscSpiIrqCsErr:
            M4_MSCx_SPI->EACR_f.CSEIE = (Enable == enNewState ? Set : Reset);
            break;

        /* Do not add default because assert function has check parameter. */
    }
}

/**
 *******************************************************************************
 ** \brief  Check whether the specified M4_MSCx_SPI flag is set or not.
 **
 ** \param  [in] M4_MSCx_SPI            To select the msc spi peripheral,where x
 **                                     can be:0,1 or 2.
 ** \arg    M4_MSC0_SPI                 The spi peripheral of msc0.
 ** \arg    M4_MSC1_SPI                 The spi peripheral of msc1.
 ** \arg    M4_MSC2_SPI                 The spi peripheral of msc2.
 **
 ** \param  [in] enFlag                 Specifies the msc spi flag to check.
 ** \arg    MscSpiFlagOvr               Receive buffer overrun or not.
 ** \arg    MscSpiFlagRxFull            Receive buffer is full or not.
 ** \arg    MscSpiFlagTxEmpty           Transfer buffer is empty or not.
 ** \arg    MscSpiFlagTxIdle            Transfer bus is idle or not.
 ** \arg    MscSpiFlagCsErr             Chip selection error occurs or not.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
en_flag_status_t Msc_Spi_GetFlagStatus(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, en_msc_spi_flag_t enFlag)
{
    en_flag_status_t status;

    DDL_ASSERT(IS_MSC_SPI_ALL_PERIPH(M4_MSCx_SPI));
    DDL_ASSERT(IS_MSC_SPI_FLAG(enFlag));

    switch(enFlag)
    {
        case MscSpiFlagOvr:
            status = ((1 == M4_MSCx_SPI->SR_f.ORF) ? Set : Reset);
            break;
        case MscSpiFlagRxFull:
            status = ((1 == M4_MSCx_SPI->SR_f.RDFF) ? Set : Reset);
            break;
        case MscSpiFlagTxEmpty:
            status = ((1 == M4_MSCx_SPI->SR_f.TDEF) ? Set : Reset);
            break;
        case MscSpiFlagTxIdle:
            status = ((1 == M4_MSCx_SPI->SR_f.TBIF) ? Set : Reset);
            break;
        case MscSpiFlagCsErr:
            status = ((1 == M4_MSCx_SPI->EACR_f.CSER) ? Set : Reset);
            break;


        /* Do not add default because assert function has check parameter. */
    }

    return status;
}

/**
 *******************************************************************************
 ** \brief  Clear the specified M4_MSCx_SPI flag.
 **
 ** \param  [in] M4_MSCx_SPI            To select the msc spi peripheral,where x
 **                                     can be:0,1 or 2.
 ** \arg    M4_MSC0_SPI                 The spi peripheral of msc0.
 ** \arg    M4_MSC1_SPI                 The spi peripheral of msc1.
 ** \arg    M4_MSC2_SPI                 The spi peripheral of msc2.
 **
 ** \param  [in] enFlag                 Specifies the msc spi flag to clear.
 ** \arg    MscSpiFlagOvr               Clear receive buffer overrun flag or not.
 ** \arg    MscSpiFlagRxFull            Clear by receive data operation.
 ** \arg    MscSpiFlagTxEmpty           Clear by send data operation.
 ** \arg    MscSpiFlagTxIdle            Clear by send data operation.
 ** \arg    MscSpiFlagCsErr             Clear chip selection error occurs flag or not.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Msc_Spi_ClearFlagStatus(M4_MSC_SPI_TypeDef *M4_MSCx_SPI, en_msc_spi_flag_t enFlag)
{
    DDL_ASSERT(IS_MSC_SPI_ALL_PERIPH(M4_MSCx_SPI));
    DDL_ASSERT(IS_MSC_SPI_FLAG(enFlag));

    switch(enFlag)
    {
        case MscSpiFlagOvr:
            M4_MSCx_SPI->SR_f.RECLR = Set;
            break;

        /* Do not set or reset to clear flag. */
        case MscSpiFlagRxFull:
        case MscSpiFlagTxEmpty:
        case MscSpiFlagTxIdle:
            break;

        case MscSpiFlagCsErr:
            M4_MSCx_SPI->EACR_f.CSER = Reset;
            break;


        /* Do not add default because assert function has check parameter. */
    }
}

//@} // MscGroup

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/

