/**
  ******************************************************************************
  * @file               ft32f4xx_i2s.c
  * @author             FMD AE
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the Inter-IC Sound (I2S):
  *                 + Initialization and Configuration
  *                 + Communications management
  *                 + I2S registers management
  *                 + Data transfers management
  *                 + Interrupts management
  * @version            V1.0.0
  * @date                   2025-03-31
    ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_i2s.h"
#include "ft32f4xx_rcc.h"

/** @defgroup I2S I2S
  * @brief I2S module driver
  * @{
  */

/** @defgroup I2S_Exported_Functions I2S Exported Functions
  * @{
  */

/**
  * @brief  Deinitializes the I2Sx peripheral registers to their default reset values.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @retval None
  */
void I2S_DeInit(I2S_TypeDef* I2Sx)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));

    if (I2Sx == I2S2)
    {
        /* Enable I2S2 reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2S2, ENABLE);
        /* Release I2S2 from reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2S2, DISABLE);
    }
    else
    {
        /* Enable I2S3 reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2S3, ENABLE);
        /* Release I2S3 from reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2S3, DISABLE);
    }
}


/**
  * @brief  Initializes the I2Sx peripheral according to the specified
  *         parameters in the I2S_InitStruct.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_InitStruct: pointer to a I2S_InitTypeDef structure that
  *         contains the configuration information for the specified I2S peripheral.
  * @retval None
  */
void I2S_Init(I2S_TypeDef* I2Sx, I2S_InitTypeDef* I2S_InitStruct)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_CH0_CONFIG(I2S_InitStruct->I2S_Channel0));
    assert_param(IS_I2S_CH1_CONFIG(I2S_InitStruct->I2S_Channel1));
    assert_param(IS_I2S_MASTERSLAVE_STATE(I2S_InitStruct->I2S_TranMasterSlaveConfig));
    assert_param(IS_I2S_SAMPLE_RATE(I2S_InitStruct->I2S_TranSampleRate));
    assert_param(IS_I2S_SAMPLE_RATE(I2S_InitStruct->I2S_RecSampleRate));
    assert_param(IS_I2S_RESOLUTION(I2S_InitStruct->I2S_TranSampleResolution));
    assert_param(IS_I2S_RESOLUTION(I2S_InitStruct->I2S_RecSampleResolution));
    assert_param(IS_I2S_FIFO_THRESHOLD(I2S_InitStruct->I2S_TFIFOAEmptyThreshold));
    assert_param(IS_I2S_FIFO_THRESHOLD(I2S_InitStruct->I2S_TFIFOAFullThreshold));
    assert_param(IS_I2S_FIFO_THRESHOLD(I2S_InitStruct->I2S_RFIFOAEmptyThreshold));
    assert_param(IS_I2S_FIFO_THRESHOLD(I2S_InitStruct->I2S_RFIFOAFullThreshold));
    assert_param(IS_I2S_STANDARD(I2S_InitStruct->I2S_Standard));

    /* Software reset I2S special function register
     * Software reset I2S TX FIFO
     * Software reset I2S RX FIFO
     * Software reset I2S TX control unit
     * Software reset I2S RX control unit
     * Software reset I2S channel 0
     * Software reset I2S channel 1 */
    I2Sx->CTRL &= (uint32_t)~(((uint32_t)I2S_CTRL_SFRRST)   |
                              ((uint32_t)I2S_CTRL_TFIFORST) | ((uint32_t)I2S_CTRL_RFIFORST) |
                              ((uint32_t)I2S_CTRL_TSYNCRST) | ((uint32_t)I2S_CTRL_RSYNCRST) |
                              ((uint32_t)I2S_CTRL_I2SEN0)   | ((uint32_t)I2S_CTRL_I2SEN1));

    /*---------------------------- I2Sx Channel0 Configuration ------------------*/
    /* Configure I2Sx channel : enable or disable, transmitter or receiver */
    /* Set I2SEN0 bit according to I2S_Channel0 value */
    /* Set TRCFG0 bits according to I2S_Channel0 value */
    if (I2S_InitStruct->I2S_Channel0 == I2S_Ch0_Disable)
    {
        I2Sx->CTRL &= (uint32_t)~((uint32_t)I2S_CTRL_I2SEN0);
    }
    else if (I2S_InitStruct->I2S_Channel0 == I2S_Ch0_Transmitter)
    {
        I2Sx->CTRL |= I2S_CTRL_TRCFG0;
    }
    else if (I2S_InitStruct->I2S_Channel0 == I2S_Ch0_Receiver)
    {
        I2Sx->CTRL &= (uint32_t)~((uint32_t)I2S_CTRL_TRCFG0);
    }

    /*---------------------------- I2Sx Channel1 Configuration ------------------*/
    /* Configure I2Sx channel : enable or disable, transmitter or receiver */
    /* Set I2SEN1 bit according to I2S_Channel1 value */
    /* Set TRCFG1 bit according to I2S_Channel1 value */
    if (I2S_InitStruct->I2S_Channel1 == I2S_Ch1_Disable)
    {
        I2Sx->CTRL &= (uint32_t)~((uint32_t)I2S_CTRL_I2SEN1);
    }
    else if (I2S_InitStruct->I2S_Channel1 == I2S_Ch1_Transmitter)
    {
        I2Sx->CTRL |= I2S_CTRL_TRCFG1;
    }
    else if (I2S_InitStruct->I2S_Channel1 == I2S_Ch1_Receiver)
    {
        I2Sx->CTRL &= (uint32_t)~((uint32_t)I2S_CTRL_TRCFG1);
    }

    /*-------------------- I2Sx transmitter master or slave configuration --------------*/
    /* Set TMS bit according to I2S_TranMasterSlaveConfig value*/
    if (I2S_InitStruct->I2S_TranMasterSlaveConfig != I2S_SLAVE)
    {
        /* Set I2S transmitter synchronizing unit to master */
        I2Sx->CTRL |= I2S_CTRL_TMS;
    }
    else
    {
        /* Set I2S transmitter synchronizing unit to slave */
        I2Sx->CTRL &= (uint32_t)~((uint32_t)I2S_CTRL_TMS);
    }

    /*-------------------- I2Sx receiver master or slave configuration --------------*/
    /* Set RMS bit according to I2S_RecMasterSlaveConfig value*/
    if (I2S_InitStruct->I2S_RecMasterSlaveConfig != I2S_SLAVE)
    {
        /* Set I2S receiver synchronizing unit to master */
        I2Sx->CTRL |= I2S_CTRL_RMS;
    }
    else
    {
        /* Set I2S receiver synchronizing unit to slave */
        I2Sx->CTRL &= (uint32_t)~((uint32_t)I2S_CTRL_RMS);
    }

    /*-------------- I2Sx tansmitter sample rate configuration -----------------*/
    /* Set TSAMPLERATE bits according to I2S_TranSampleRate values */
    I2Sx->SRR |= I2S_InitStruct->I2S_TranSampleRate;
    /*-------------- I2Sx transmitter sample resolution configuration ----------*/
    /* Set TRESOLUTION bits according to I2S_TranSampleResolution values */
    I2Sx->SRR |= (I2S_InitStruct->I2S_TranSampleResolution << 11);
    /*-------------- I2Sx receiver sample rate configuration -------------------*/
    /* Set RSAMPLERATE bits according to I2S_RecSampleRate values */
    I2Sx->SRR |= (I2S_InitStruct->I2S_RecSampleRate << 16);
    /*-------------- I2Sx receiver sample resolution configuration -------------*/
    /* Set RRESOLUTION bits according to I2S_RecSampleResolution values */
    I2Sx->SRR |= (I2S_InitStruct->I2S_RecSampleResolution << 27);

    /*----------I2S transmit FIFO almost empty threshold configuration ---------*/
    /* Set TAEMPTYTHRESHOLD bits according to I2S_TFIFOAEmptyThreshold values*/
    I2Sx->TFIFO_CTRL |= (I2S_InitStruct->I2S_TFIFOAEmptyThreshold);
    /*----------I2S transmit FIFO almost full threshold configuration ---------*/
    /* Get the old register value */
    tmpreg = I2Sx->TFIFO_CTRL;
    /* Reset I2Sx TAFULLTHRESHOLD bit [2:0] */
    tmpreg &= (uint32_t)~((uint32_t)I2S_TFIFO_CTRL_TAFULLTHRESHOLD);
    /* Set TAFULLTHRESHOLD bits according to I2S_TFIFOAFullThreshold values*/
    tmpreg |= (uint32_t)(((uint32_t)I2S_InitStruct->I2S_TFIFOAFullThreshold << 16) &
                         I2S_TFIFO_CTRL_TAFULLTHRESHOLD);
    /* Store the new register value */
    I2Sx->TFIFO_CTRL = tmpreg;


    /*----------I2S receive FIFO almost empty threshold configuration ---------*/
    /* Set RAEMPTYTHRESHOLD bits according to I2S_RFIFOAEmptyThreshold values*/
    I2Sx->RFIFO_CTRL |= (I2S_InitStruct->I2S_RFIFOAEmptyThreshold << 16);
    /*----------I2S receive FIFO almost full threshold configuration ---------*/
    /* Get the old register value */
    tmpreg = I2Sx->RFIFO_CTRL;
    /* Reset I2Sx RAFULLTHRESHOLD bit [2:0] */
    tmpreg &= (uint32_t)~((uint32_t)I2S_RFIFO_CTRL_RAFULLTHRESHOLD);
    /* Set RAFULLTHRESHOLD bits according to I2S_RFIFOAFullThreshold values*/
    tmpreg |= (uint32_t)(((uint32_t)I2S_InitStruct->I2S_RFIFOAFullThreshold << 16) &
                         I2S_RFIFO_CTRL_RAFULLTHRESHOLD);
    /* Store the new register value */
    I2Sx->RFIFO_CTRL = tmpreg;

    /*------------------I2S standard configuration------------------------------*/
    /* Set DEV_CONF registers according to I2S_STANDARD values */
    I2Sx->DEV_CONF = I2S_InitStruct->I2S_Standard;
}


/**
  * @brief  Fills each I2S_InitStruct member with its default value.
  * @param  I2S_InitStruct: pointer to an I2S_InitTypeDef structure which will be initialized.
  * @retval None
  */
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct)
{
    /*---------------- Reset I2S init structure parameters values --------------*/
    /* Initialize the I2S_Channel0 member */
    I2S_InitStruct->I2S_Channel0 = 0;
    /* Initialize the I2S_Channel1 member */
    I2S_InitStruct->I2S_Channel1 = 0;

    /* Initialize the I2S_TranMasterSlaveConfig member */
    I2S_InitStruct->I2S_TranMasterSlaveConfig = 0;
    /* Initialize the I2S_RecMasterSlaveConfig member */
    I2S_InitStruct->I2S_RecMasterSlaveConfig = 0;

    /* Initialize the I2S_TranSampleRate member */
    I2S_InitStruct->I2S_TranSampleRate = 0;
    /* Initialize the I2S_TranSampleResolution member */
    I2S_InitStruct->I2S_TranSampleResolution = 0;
    /* Initialize the I2S_RecSampleRate member */
    I2S_InitStruct->I2S_RecSampleRate = 0;
    /* Initialize the I2S_RecSampleResolution member */
    I2S_InitStruct->I2S_RecSampleResolution = 0;

    /* Initialize the I2S_TFIFOAEmptyThreshold member */
    I2S_InitStruct->I2S_TFIFOAEmptyThreshold = 0;
    /* Initialize the I2S_TFIFOAFullThreshold member */
    I2S_InitStruct->I2S_TFIFOAFullThreshold = 7;
    /* Initialize the I2S_RFIFOAEmptyThreshold member */
    I2S_InitStruct->I2S_RFIFOAEmptyThreshold = 0;
    /* Initialize the I2S_RFIFOAFullThreshold member */
    I2S_InitStruct->I2S_RFIFOAFullThreshold = 7;

    /* Initialize the I2S_Standard member */
    I2S_InitStruct->I2S_Standard = 0;
}

/**
  * @brief  Enables or disables I2S channel
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  CHy: I2S channel y select, where y can be 0 or 1 to select the I2S channel
  *          This parameter can be any combination of the following values:
  *            @arg I2S_CH0: I2S channel 0 select
  *            @arg I2S_CH1: I2S channel 1 select
  * @param  NewState: new state of the I2Sx channel 0/1.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2S_ChannelConfig(I2S_TypeDef* I2Sx, uint32_t CHy, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_CHANNEL_SEL(CHy));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable channel y */
        I2Sx->CTRL |= CHy;
    }
    else
    {
        /* Disable channel y */
        I2Sx->CTRL &= (uint32_t)~((uint32_t)CHy);
    }
}


/**
  * @brief  I2S channel 0/1 transmitter or receiver config
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  CHy_TRANREC: I2S channel y transmitter or receiver config,
  *          where y can be 0 or 1 to select the I2S channel.
  *          This parameter can be any combination of the following values:
  *            @arg I2S_CH0_TRANREC: I2S channel 0 is transmitter or receiver
  *            @arg I2S_CH1_TRANREC: I2S channel 1 is transmitter or receiver
  * @param  I2S_TranRec: transmitter or receiver of the I2Sx channel 0/1.
  *          This parameter can be one of the following values:
  *            @arg I2S_TRANSMITTER: I2S channel y is transmitter
  *            @arg I2S_RECEIVER   : I2S channel y is receiver
  * @retval None
  */
void I2S_ChannelTranRecConfig(I2S_TypeDef* I2Sx, uint32_t CHy_TRANREC, uint32_t I2S_TranRec)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_CHANNEL_TRANREC(CHy_TRANREC));
    assert_param(IS_I2S_TRANREC_STATE(I2S_TranRec));

    if (I2S_TranRec != I2S_RECEIVER)
    {
        /* Set channel y to transmitter */
        I2Sx->CTRL |= CHy_TRANREC;
    }
    else
    {
        /* Set channel y to receiver */
        I2Sx->CTRL &= (uint32_t)~((uint32_t)CHy_TRANREC);
    }
}


/**
  * @brief  Enables or disables the Loop-back test for I2S channel 0/1
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  NewState: new state of the I2Sx channel 0/1 Loop-back test.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2S_LoopBackCmd(I2S_TypeDef* I2Sx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable Loop-Back test mode */
        I2Sx->CTRL |= I2S_CTRL_LOOPBACK01;
    }
    else
    {
        /* Disable Loop-Back test mode */
        I2Sx->CTRL &= (uint32_t)~((uint32_t)I2S_CTRL_LOOPBACK01);
    }
}


/**
  * @brief  Software reset I2S special function register.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @retval None
  */
void I2S_SFRResetCmd(I2S_TypeDef* I2Sx)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));

    /* Reset SFR */
    I2Sx->CTRL &= (uint32_t)~((uint32_t)I2S_CTRL_SFRRST);
}


/**
  * @brief  Configures I2S transmitter synchronizing unit as the master or slave
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_MS: master or slave of the I2Sx transmitter synchronizing unit.
  *          This parameter can be one of the following values:
  *            @arg I2S_MASTER: I2S transmitter synchronizing unit is master.
  *            @arg I2S_SLAVE : I2S transmitter synchronizing unit is slave.
  * @retval None
  */
void I2S_TranMasterSlaveConfig(I2S_TypeDef* I2Sx, uint32_t I2S_MS)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_MASTERSLAVE_STATE(I2S_MS));

    if (I2S_MS != I2S_SLAVE)
    {
        /* Set I2S transmitter synchronizing unit to master */
        I2Sx->CTRL |= I2S_CTRL_TMS;
    }
    else
    {
        /* Set I2S transmitter synchronizing unit to slave */
        I2Sx->CTRL &= (uint32_t)~((uint32_t)I2S_CTRL_TMS);
    }
}


/**
  * @brief  Configures I2S receiver synchronizing unit as the master or slave
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_MS: master or slave of the I2Sx receiver synchronizing unit.
  *          This parameter can be one of the following values:
  *            @arg I2S_MASTER: I2S receiver synchronizing unit is master.
  *            @arg I2S_SLAVE : I2S receiver synchronizing unit is slave.
  * @retval None
  */
void I2S_RecMasterSlaveConfig(I2S_TypeDef* I2Sx, uint32_t I2S_MS)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_MASTERSLAVE_STATE(I2S_MS));

    if (I2S_MS != I2S_SLAVE)
    {
        /* Set I2S receiver synchronizing unit to master */
        I2Sx->CTRL |= I2S_CTRL_RMS;
    }
    else
    {
        /* Set I2S receiver synchronizing unit to slave */
        I2Sx->CTRL &= (uint32_t)~((uint32_t)I2S_CTRL_RMS);
    }
}


/**
  * @brief  Software reset I2S transmit FIFO.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @retval None
  */
void I2S_TFIFOResetCmd(I2S_TypeDef* I2Sx)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));

    /* Reset transmit FIFO */
    I2Sx->CTRL &= (uint32_t)~((uint32_t)I2S_CTRL_TFIFORST);
}


/**
  * @brief  Software reset I2S receive FIFO.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @retval None
  */
void I2S_RFIFOResetCmd(I2S_TypeDef* I2Sx)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));

    /* Reset receive FIFO */
    I2Sx->CTRL &= (uint32_t)~((uint32_t)I2S_CTRL_RFIFORST);
}


/**
  * @brief  Software reset I2S transmitter synchronizing unit.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  NewState: new state of the I2Sx transmitter synchronizing unit software reset.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2S_TranSyncResetCmd(I2S_TypeDef* I2Sx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Reset transmitter synchronizing unit */
    if (NewState != DISABLE)
    {
        /* Enable software reset transmitter synchronizing unit */
        I2Sx->CTRL &= (uint32_t)~((uint32_t)I2S_CTRL_TSYNCRST);
    }
    else
    {
        /* Disable software reset transmitter synchronizing unit */
        I2Sx->CTRL |= I2S_CTRL_TSYNCRST;
    }
}


/**
  * @brief  Software reset I2S Receiver synchronizing unit.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  NewState: new state of the I2Sx receiver synchronizing unit software reset.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2S_RecSyncResetCmd(I2S_TypeDef* I2Sx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable software reset receiver synchronizing unit */
        I2Sx->CTRL &= (uint32_t)~((uint32_t)I2S_CTRL_RSYNCRST);
    }
    else
    {
        /* Disable software reset receiver synchronizing unit */
        I2Sx->CTRL |= I2S_CTRL_RSYNCRST;
    }
}

/**
  * @brief  Enables or disables the Loop-back test for I2S transmitter
  *         synchronizing unit.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  NewState: new state of the I2Sx transmitter synchronizing unit
  *          loop-back test.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2S_TranSyncLoopBackCmd(I2S_TypeDef* I2Sx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable Loop-back test for I2S transmitter synchronizing unit */
        I2Sx->CTRL |= I2S_CTRL_TSYNCLOOPBACK;
    }
    else
    {
        /* Disable Loop-back test for I2S transmitter synchronizing unit */
        I2Sx->CTRL &= (uint32_t)~((uint32_t)I2S_CTRL_TSYNCLOOPBACK);
    }
}


/**
  * @brief  Enables or disables the Loop-back test for I2S receiver
  *         synchronizing unit.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  NewState: new state of the I2Sx receiver synchronizing unit
  *          loop-back test.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2S_RecSyncLoopBackCmd(I2S_TypeDef* I2Sx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable Loop-back test for I2S receiver synchronizing unit*/
        I2Sx->CTRL |= I2S_CTRL_RSYNCLOOPBACK;
    }
    else
    {
        /* Disable Loop-back test for I2S receiver synchronizing unit */
        I2Sx->CTRL &= (uint32_t)~((uint32_t)I2S_CTRL_RSYNCLOOPBACK);
    }
}


/**
  * @brief  Configures the transmitter sample rate.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  SAMPLE_RATE specifies the sample rate to be programmed.
  * @retval None
  */
void I2S_TranSampleRateConfig(I2S_TypeDef* I2Sx, uint16_t SAMPLE_RATE)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_SAMPLE_RATE(SAMPLE_RATE));

    /* Get the old register value */
    tmpreg = I2Sx->SRR;

    /* Reset I2Sx TSAMPLERATE bit [10:0] */
    tmpreg &= (uint32_t)~((uint32_t)I2S_SRR_TSAMPLERATE);

    /* Set I2Sx TSAMPLERATE */
    tmpreg |= (uint32_t)((uint32_t)SAMPLE_RATE & I2S_SRR_TSAMPLERATE);

    /* Store the new register value */
    I2Sx->SRR = tmpreg;
}


/**
  * @brief  Configures the transmitter sample resolution.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  RESOLUTION specifies the sample resolution to be programmed.
  * @retval None
  */
void I2S_TranSampleResolutionConfig(I2S_TypeDef* I2Sx, uint8_t RESOLUTION)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_RESOLUTION(RESOLUTION));

    /* Get the old register value */
    tmpreg = I2Sx->SRR;

    /* Reset I2Sx TRESOLUTION bit [10:0] */
    tmpreg &= (uint32_t)~((uint32_t)I2S_SRR_TRESOLUTION);

    /* Set I2Sx TRESOLUTION */
    tmpreg |= (uint32_t)(((uint32_t)RESOLUTION << 11) & I2S_SRR_TRESOLUTION);

    /* Store the new register value */
    I2Sx->SRR = tmpreg;
}


/**
  * @brief  Configures the receiver sample rate.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  SAMPLE_RATE specifies the sample rate to be programmed.
  * @retval None
  */
void I2S_RecSampleRateConfig(I2S_TypeDef* I2Sx, uint16_t SAMPLE_RATE)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_SAMPLE_RATE(SAMPLE_RATE));

    /* Get the old register value */
    tmpreg = I2Sx->SRR;

    /* Reset I2Sx RSAMPLERATE bit [10:0] */
    tmpreg &= (uint32_t)~((uint32_t)I2S_SRR_RSAMPLERATE);

    /* Set I2Sx RSAMPLERATE */
    tmpreg |= (uint32_t)(((uint32_t)SAMPLE_RATE << 16) & I2S_SRR_RSAMPLERATE);

    /* Store the new register value */
    I2Sx->SRR = tmpreg;
}


/**
  * @brief  Configures the receiver sample resolution.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  RESOLUTION specifies the sample resolution to be programmed.
  * @retval None
  */
void I2S_RecSampleResolutionConfig(I2S_TypeDef* I2Sx, uint8_t RESOLUTION)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_RESOLUTION(RESOLUTION));

    /* Get the old register value */
    tmpreg = I2Sx->SRR;

    /* Reset I2Sx RRESOLUTION bit [10:0] */
    tmpreg &= (uint32_t)~((uint32_t)I2S_SRR_RRESOLUTION);

    /* Set I2Sx RRESOLUTION */
    tmpreg |= (uint32_t)(((uint32_t)RESOLUTION << 27) & I2S_SRR_RRESOLUTION);

    /* Store the new register value */
    I2Sx->SRR = tmpreg;
}


/**
  * @brief  Enables or disables I2S channel 0/1 clock
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  CHy_CLOCK: I2S channel y clock strobe, where y can be 0 or 1
  *          to select the I2S channel.
  *          This parameter can be any combination of the following values:
  *            @arg I2S_CH0_CLOCK_STROBE: I2S channel 0 clock strobe
  *            @arg I2S_CH1_CLOCK_STROBE: I2S channel 1 clock strobe
  * @param  NewState: new state of the I2Sx channel 0/1 clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2S_ChannelClockConfig(I2S_TypeDef* I2Sx, uint32_t CHy_CLOCK, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_CHANNEL_CLOCK_STROBE(CHy_CLOCK));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable channel y clock */
        I2Sx->CID_CTRL &= (uint32_t)~((uint32_t)CHy_CLOCK);
    }
    else
    {
        /* Disable channel y clock */
        I2Sx->CID_CTRL |= CHy_CLOCK;
    }
}


/**
  * @brief  Enables or disables I2S transmitter synchronizing unit clock
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  NewState: new state of the I2Sx transmitter synchronizing unit clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2S_TranSyncUnitCmd(I2S_TypeDef* I2Sx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable transmitter synchronizing unit clock*/
        I2Sx->CID_CTRL &= (uint32_t)~((uint32_t)I2S_CID_CTRL_STROBETS);
    }
    else
    {
        /* Disable transmitter synchronizing unit clock */
        I2Sx->CID_CTRL |= I2S_CID_CTRL_STROBETS;
    }
}


/**
  * @brief  Enables or disables I2S receiver synchronizing unit clock
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  NewState: new state of the I2Sx receiver synchronizing unit clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2S_RecSyncUnitCmd(I2S_TypeDef* I2Sx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable receiver synchronizing unit clock*/
        I2Sx->CID_CTRL &= (uint32_t)~((uint32_t)I2S_CID_CTRL_STROBERS);
    }
    else
    {
        /* Disable receiver synchronizing unit clock */
        I2Sx->CID_CTRL |= I2S_CID_CTRL_STROBERS;
    }
}


/**
  * @brief  Returns the I2S transmit FIFO level status.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @retval The value of the I2S transmit FIFO level status.
  */
uint8_t I2S_GetTranFIFOLevel(I2S_TypeDef* I2Sx)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));

    /* Return the I2S transmit FIFO level status */
    return (uint8_t)((uint32_t)I2Sx->TFIFO_STAT & I2S_TFIFO_STAT_TLEVEL) ;
}


/**
  * @brief  Returns the I2S receive FIFO level status.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @retval The value of the I2S receive FIFO level status.
  */
uint8_t I2S_GetRecFIFOLevel(I2S_TypeDef* I2Sx)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));

    /* Return the I2S receive FIFO level status */
    return (uint8_t)((uint32_t)I2Sx->RFIFO_STAT & I2S_RFIFO_STAT_RLEVEL) ;
}


/**
  * @brief  Configures the threshold for almost empty flag in I2S transmit fifo.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  FIFO_Threshold specifies the fifo threshold to be programmed.
  * @retval None
  */
void I2S_TFIFOAEmptyThresholdConfig(I2S_TypeDef* I2Sx, uint8_t FIFO_Threshold)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_FIFO_THRESHOLD(FIFO_Threshold));

    /* Get the old register value */
    tmpreg = I2Sx->TFIFO_CTRL;

    /* Reset I2Sx TAEMPTYTHRESHOLD bit [2:0] */
    tmpreg &= (uint32_t)~((uint32_t)I2S_TFIFO_CTRL_TAEMPTYTHRESHOLD);

    /* Set I2Sx TAEMPTYTHRESHOLD */
    tmpreg |= (uint32_t)((uint32_t)FIFO_Threshold & I2S_TFIFO_CTRL_TAEMPTYTHRESHOLD);

    /* Store the new register value */
    I2Sx->TFIFO_CTRL = tmpreg;
}


/**
  * @brief  Configures the threshold for almost full flag in I2S transmit fifo.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  FIFO_Threshold specifies the fifo threshold to be programmed.
  * @retval None
  */
void I2S_TFIFOAFullThresholdConfig(I2S_TypeDef* I2Sx, uint8_t FIFO_Threshold)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_FIFO_THRESHOLD(FIFO_Threshold));

    /* Get the old register value */
    tmpreg = I2Sx->TFIFO_CTRL;

    /* Reset I2Sx TAFULLTHRESHOLD bit [2:0] */
    tmpreg &= (uint32_t)~((uint32_t)I2S_TFIFO_CTRL_TAFULLTHRESHOLD);

    /* Set I2Sx TAFULLTHRESHOLD */
    tmpreg |= (uint32_t)(((uint32_t)FIFO_Threshold << 16) & I2S_TFIFO_CTRL_TAFULLTHRESHOLD);

    /* Store the new register value */
    I2Sx->TFIFO_CTRL = tmpreg;
}


/**
  * @brief  Configures the threshold for almost empty flag in I2S receive fifo.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  FIFO_Threshold specifies the fifo threshold to be programmed.
  * @retval None
  */
void I2S_RFIFOAEmptyThresholdConfig(I2S_TypeDef* I2Sx, uint8_t FIFO_Threshold)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_FIFO_THRESHOLD(FIFO_Threshold));

    /* Get the old register value */
    tmpreg = I2Sx->RFIFO_CTRL;

    /* Reset I2Sx RAEMPTYTHRESHOLD bit [2:0] */
    tmpreg &= (uint32_t)~((uint32_t)I2S_RFIFO_CTRL_RAEMPTYTHRESHOLD);

    /* Set I2Sx RAEMPTYTHRESHOLD */
    tmpreg |= (uint32_t)((uint32_t)FIFO_Threshold & I2S_RFIFO_CTRL_RAEMPTYTHRESHOLD);

    /* Store the new register value */
    I2Sx->RFIFO_CTRL = tmpreg;
}


/**
  * @brief  Configures the threshold for almost full flag in I2S receive fifo.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  FIFO_Threshold specifies the fifo threshold to be programmed.
  * @retval None
  */
void I2S_RFIFOAFullThresholdConfig(I2S_TypeDef* I2Sx, uint8_t FIFO_Threshold)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_FIFO_THRESHOLD(FIFO_Threshold));

    /* Get the old register value */
    tmpreg = I2Sx->RFIFO_CTRL;

    /* Reset I2Sx RAFULLTHRESHOLD bit [2:0] */
    tmpreg &= (uint32_t)~((uint32_t)I2S_RFIFO_CTRL_RAFULLTHRESHOLD);

    /* Set I2Sx RAFULLTHRESHOLD */
    tmpreg |= (uint32_t)(((uint32_t)FIFO_Threshold << 16) & I2S_RFIFO_CTRL_RAFULLTHRESHOLD);

    /* Store the new register value */
    I2Sx->RFIFO_CTRL = tmpreg;
}


/**
  * @brief  Configures the I2S standard.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  STANDARD specifies the standard to be followed in I2S transmittion.
  *          This parameter can be one of the following values:
  *            @arg I2S_Philips        : I2S Philips mode
  *            @arg I2S_Right_Justified: I2S Right-Justified mode
  *            @arg I2S_Left_Justified : I2S Left-Justified mode
  *            @arg I2S_DSP            : I2S DSP mode
  * @retval None
  */
void I2S_StandardConfig(I2S_TypeDef* I2Sx, uint32_t Standard)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_STANDARD(Standard));

    /* Store the new register value */
    I2Sx->DEV_CONF = Standard;
}


/**
  * @brief  Configures I2S continuous serial clock active edge for transmission.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_SCK_Polar specifies the active edge of I2S SCK signals.
  *          This parameter can be one of the following values:
  *            @arg I2S_SCK_POLAR_RISE: Seriral clock active edge is rising edge.
  *            @arg I2S_SCK_POLAR_FALL: Seriral clock active edge is falling edge.
  * @retval None
  */
void I2S_TranSckPolarConfig(I2S_TypeDef* I2Sx, uint8_t I2S_SCK_Polar)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_SCK_POLAR(I2S_SCK_Polar));

    if (I2S_SCK_Polar != I2S_SCK_POLAR_RISE)
    {
        /* Set I2S serial clock active edge for transmission to falling edge */
        I2Sx->DEV_CONF |= I2S_DEV_CONF_TRANSCKPOLAR;
    }
    else
    {
        /* Set I2S serial clock active edge for transmission to rising edge */
        I2Sx->DEV_CONF &= (uint32_t)~((uint32_t)I2S_DEV_CONF_TRANSCKPOLAR);
    }
}


/**
  * @brief  Configures I2S continuous serial clock active edge for reception.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_SCK_Polar specifies the active edge of I2S SCK signals.
  *          This parameter can be one of the following values:
  *            @arg I2S_SCK_POLAR_RISE: Seriral clock active edge is rising edge.
  *            @arg I2S_SCK_POLAR_FALL: Seriral clock active edge is falling edge.
  * @retval None
  */
void I2S_RecSckPolarConfig(I2S_TypeDef* I2Sx, uint8_t I2S_SCK_Polar)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_SCK_POLAR(I2S_SCK_Polar));

    if (I2S_SCK_Polar != I2S_SCK_POLAR_RISE)
    {
        /* Set I2S serial clock active edge for receprion to falling edge */
        I2Sx->DEV_CONF |= I2S_DEV_CONF_RECSCKPOLAR;
    }
    else
    {
        /* Set I2S serial clock active edge for reception to rising edge */
        I2Sx->DEV_CONF &= (uint32_t)~((uint32_t)I2S_DEV_CONF_RECSCKPOLAR);
    }
}


/**
  * @brief  Configures I2S word select signal polarity selection for transmission.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_WS_Polar specifies the polarity of I2S WS signals.
  *          This parameter can be one of the following values:
  *            @arg I2S_WS_POLAR_0: the level of WS signal for the transmitted
  *                  left channel data sample is '0' and the level of WS signal
  *                  for the transmitted right channel data sample is '1'.
  *            @arg I2S_WS_POLAR_1: the level of WS signal for the transmitted
  *                  left channel data sample is '1' and the level of WS signal
  *                  for the transmitted right channel data sample is '0'.
  * @retval None
  */
void I2S_TranWSPolarConfig(I2S_TypeDef* I2Sx, uint8_t I2S_WS_Polar)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_WS_POLAR(I2S_WS_Polar));

    if (I2S_WS_Polar != I2S_WS_POLAR_0)
    {
        /* Set I2S WS signal polarity for transmission to 1 */
        I2Sx->DEV_CONF |= I2S_DEV_CONF_TRANWSPOLAR;
    }
    else
    {
        /* Set I2S WS signal polarity for transmission to 0 */
        I2Sx->DEV_CONF &= (uint32_t)~((uint32_t)I2S_DEV_CONF_TRANWSPOLAR);
    }
}


/**
  * @brief  Configures I2S word select signal polarity selection for reception.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_WS_Polar specifies the polarity of I2S WS signals.
  *          This parameter can be one of the following values:
  *            @arg I2S_WS_POLAR_0: the level of WS signal for the received
  *                  left channel data sample is '0' and the level of WS signal
  *                  for the received right channel data sample is '1'.
  *            @arg I2S_WS_POLAR_1: the level of WS signal for the received
  *                  left channel data sample is '1' and the level of WS signal
  *                  for the received right channel data sample is '0'.
  * @retval None
  */
void I2S_RecWSPolarConfig(I2S_TypeDef* I2Sx, uint8_t I2S_WS_Polar)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_WS_POLAR(I2S_WS_Polar));

    if (I2S_WS_Polar != I2S_WS_POLAR_0)
    {
        /* Set I2S WS signal polarity for reception to 1 */
        I2Sx->DEV_CONF |= I2S_DEV_CONF_RECWSPOLAR;
    }
    else
    {
        /* Set I2S WS signal polarity for reception to 0 */
        I2Sx->DEV_CONF &= (uint32_t)~((uint32_t)I2S_DEV_CONF_RECWSPOLAR);
    }
}


/**
  * @brief  Configures alignment of the transmitted digital data sample at the APB bus.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_ALIGN specifies the alignment of the digital data sample.
  *          This parameter can be one of the following values:
  *            @arg I2S_ALIGN_MSB: the MSB side alignment of the resolution-width
  *                  data sample.
  *            @arg I2S_ALIGN_LSB: the MSB side alignment of the resolution-width
  *                  data sample.
  * @retval None
  */
void I2S_TranAPBAlignConfig(I2S_TypeDef* I2Sx, uint8_t I2S_Align)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_ALIGNMENT(I2S_Align));

    if (I2S_Align != I2S_ALIGN_LSB)
    {
        /* Set the MSB side alignment the resolution-width transmitted
         * digital data sample at the APB bus */
        I2Sx->DEV_CONF |= I2S_DEV_CONF_TRANAPBALIGNLR;
    }
    else
    {
        /* Set the LSB side alignment the resolution-width transmitted
         * digital data sample at the APB bus */
        I2Sx->DEV_CONF &= (uint32_t)~((uint32_t)I2S_DEV_CONF_TRANAPBALIGNLR);
    }
}


/**
  * @brief  Configures alignment of the received digital data sample at the APB bus.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_ALIGN specifies the alignment of the digital data sample.
  *          This parameter can be one of the following values:
  *            @arg I2S_ALIGN_MSB: the MSB side alignment of the resolution-width
  *                  data sample.
  *            @arg I2S_ALIGN_LSB: the MSB side alignment of the resolution-width
  *                  data sample.
  * @retval None
  */
void I2S_RecAPBAlignConfig(I2S_TypeDef* I2Sx, uint8_t I2S_Align)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_ALIGNMENT(I2S_Align));

    if (I2S_Align != I2S_ALIGN_LSB)
    {
        /* Set the MSB side alignment the resolution-width received
         * digital data sample at the APB bus */
        I2Sx->DEV_CONF |= I2S_DEV_CONF_RECAPBALIGNLR;
    }
    else
    {
        /* Set the LSB side alignment the resolution-width received
         * digital data sample at the APB bus */
        I2Sx->DEV_CONF &= (uint32_t)~((uint32_t)I2S_DEV_CONF_RECAPBALIGNLR);
    }
}


/**
  * @brief  Configures alignment of the transmitted digital data sample at the
  *          I2S serial data line.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_ALIGN specifies the alignment of the digital data sample.
  *          This parameter can be one of the following values:
  *            @arg I2S_ALIGN_MSB: the MSB side alignment of the resolution-width
  *                  data sample.
  *            @arg I2S_ALIGN_LSB: the MSB side alignment of the resolution-width
  *                  data sample.
  * @retval None
  */
void I2S_TranI2SAlignConfig(I2S_TypeDef* I2Sx, uint8_t I2S_Align)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_ALIGNMENT(I2S_Align));

    if (I2S_Align != I2S_ALIGN_LSB)
    {
        /* Set the MSB side alignment the resolution-width transmitted
         * digital data sample at the I2S serial data line */
        I2Sx->DEV_CONF |= I2S_DEV_CONF_TRANI2SALIGNLR;
    }
    else
    {
        /* Set the LSB side alignment the resolution-width transmitted
         * digital data sample at the I2S serial data line */
        I2Sx->DEV_CONF &= (uint32_t)~((uint32_t)I2S_DEV_CONF_TRANI2SALIGNLR);
    }
}


/**
  * @brief  Configures alignment of the received digital data sample at the
  *          I2S serial data line.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_ALIGN specifies the alignment of the digital data sample.
  *          This parameter can be one of the following values:
  *            @arg I2S_ALIGN_MSB: the MSB side alignment of the resolution-width
  *                  data sample.
  *            @arg I2S_ALIGN_LSB: the MSB side alignment of the resolution-width
  *                  data sample.
  * @retval None
  */
void I2S_RecI2SAlignConfig(I2S_TypeDef* I2Sx, uint8_t I2S_Align)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_ALIGNMENT(I2S_Align));

    if (I2S_Align != I2S_ALIGN_LSB)
    {
        /* Set the MSB side alignment the resolution-width received
         * digital data sample at the I2S serial data line */
        I2Sx->DEV_CONF |= I2S_DEV_CONF_RECI2SALIGNLR;
    }
    else
    {
        /* Set the LSB side alignment the resolution-width received
         * digital data sample at the I2S serial data line */
        I2Sx->DEV_CONF &= (uint32_t)~((uint32_t)I2S_DEV_CONF_RECI2SALIGNLR);
    }
}


/**
  * @brief  Configures the transmitted valid data delay at the I2S SD
  *          output line afte the WS line edge
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_Tran_data_WS_del specifies the the transmitted valid data delay at
  *          the I2S SD output line afte the WS line edge
  *          This parameter can be one of the following values:
  *            @arg I2S_TRAN_DATA_WS_DEL_0: The serial data for transmission are
  *                  updated on the second rising/falling edge of the clock signal
  *                  after the WS signal change.
  *            @arg I2S_TRAN_DATA_WS_DEL_1: The serial data for transmission are
  *                  updated on the first rising/falling edge of the clock signal
  *                  after the WS signal change.
  * @retval None
  */
void I2S_TranDataWSDelConfig(I2S_TypeDef* I2Sx, uint8_t I2S_Tran_Data_WS_Del)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_TRAN_DATA_WS_DEL(I2S_Tran_Data_WS_Del));

    if (I2S_Tran_Data_WS_Del != I2S_TRAN_DATA_WS_DEL_0)
    {
        /* Set the serial data for transmission are updated on the
         * first rising/falling edge of the clock signal after the
         * WS signal change */
        I2Sx->DEV_CONF |= I2S_DEV_CONF_TRANDATAWSDEL;
    }
    else
    {
        /* Set the serial data for transmission are updated on the
         * second rising/falling edge of the clock signal after the
         * WS signal change */
        I2Sx->DEV_CONF &= (uint32_t)~((uint32_t)I2S_DEV_CONF_TRANDATAWSDEL);
    }
}


/**
  * @brief  Configures the received valid data delay at the I2S SD
  *          input line afte the WS line edge
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_Rec_Data_WS_Del specifies the the received valid data delay at
  *          the I2S SD output line afte the WS line edge
  *          This parameter can be one of the following values:
  *            @arg I2S_REC_DATA_WS_DEL_0: The received serial data are updated
  *                  on the thired rising/falling edge of the clock signal
  *                  after the WS signal change.
  *            @arg I2S_REC_DATA_WS_DEL_1: The received serial data are updated
  *                  on the second rising/falling edge of the clock signal
  *                  after the WS signal change.
  * @retval None
  */
void I2S_RecDataWSDelConfig(I2S_TypeDef* I2Sx, uint8_t I2S_Rec_Data_WS_Del)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_REC_DATA_WS_DEL(I2S_Rec_Data_WS_Del));

    if (I2S_Rec_Data_WS_Del != I2S_REC_DATA_WS_DEL_0)
    {
        /* Set the received serial data are updated on the
         * second rising/falling edge of the clock signal after the
         * WS signal change */
        I2Sx->DEV_CONF |= I2S_DEV_CONF_RECDATAWSDEL;
    }
    else
    {
        /* Set the received serial data are updated on the
         * third rising/falling edge of the clock signal after the
         * WS signal change */
        I2Sx->DEV_CONF &= (uint32_t)~((uint32_t)I2S_DEV_CONF_RECDATAWSDEL);
    }
}


/**
  * @brief  Configures the I2S WS signal format for the transmitter unit.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_WS_Format: I2Sx WS signal format.
  *          This parameter can be one of the following values:
  *         @arg I2S_WS_PHILIPS: WS signal format specific to the standard
  *               Philips I2S interface.
  *         @arg I2S_WS_DSP    : WS signal format specific to the DSP audio
  *               interface mode.
  * @retval None
  */

void I2S_TranWSFormatConfig(I2S_TypeDef* I2Sx, uint8_t I2S_WS_Format)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_WS_FORMAT(I2S_WS_Format));

    if (I2S_WS_Format != I2S_WS_PHILIPS)
    {
        /* Set I2S WS signal format to the DSP audio interface mode
         * for the transmitter unit */
        I2Sx->DEV_CONF |= I2S_DEV_CONF_TRANWSDSPMODE;
    }
    else
    {
        /* Set I2S WS signal format to the standard Philips I2S interface
         * for the transmitter unit */
        I2Sx->DEV_CONF &= (uint32_t)~((uint32_t)I2S_DEV_CONF_TRANWSDSPMODE);
    }
}


/**
  * @brief  Configures the I2S WS signal format for the receiver unit.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_WS_Format: I2Sx WS signal format.
  *          This parameter can be one of the following values:
  *         @arg I2S_WS_PHILIPS: WS signal format specific to the standard
  *               Philips I2S interface.
  *         @arg I2S_WS_DSP    : WS signal format specific to the DSP audio
  *               interface mode.
  * @retval None
  */

void I2S_RecWSFormatConfig(I2S_TypeDef* I2Sx, uint8_t I2S_WS_Format)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_WS_FORMAT(I2S_WS_Format));

    if (I2S_WS_Format != I2S_WS_PHILIPS)
    {
        /* Set I2S WS signal format to the DSP audio interface mode
         * for the receiver unit */
        I2Sx->DEV_CONF |= I2S_DEV_CONF_RECWSDSPMODE;
    }
    else
    {
        /* Set I2S WS signal format to the standard Philips I2S interface
         * for the receiver unit */
        I2Sx->DEV_CONF &= (uint32_t)~((uint32_t)I2S_DEV_CONF_RECWSDSPMODE);
    }
}


/**
  * @brief  Reads the specified I2S register and returns its value.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_Register: specifies the register to read.
  *          This parameter can be one of the following values:
  *            @arg I2S_Register_CTRL      : CTRL register
  *            @arg I2S_Register_INTR_STAT : INTR_STAT register
  *            @arg I2S_Register_SRR       : SRR register
  *            @arg I2S_Register_CID_CTRL  : CID_CTRL register
  *            @arg I2S_Register_TFIFO_STAT: TFIFO_STAT register
  *            @arg I2S_Register_RFIFO_STAT: RFIFO_STAT register
  *            @arg I2S_Register_TFIFO_CTRL: TFIFO_CTRL register
  *            @arg I2S_Register_RFIFO_CTRL: RFIFO_CTRL register
  *            @arg I2S_Register_DEV_CONF  : DEV_CONF register
  *            @arg I2S_Register_POLL_STAT : POLL_STAT register
  * @retval The value of the read register.
  */

uint32_t I2S_ReadRegister(I2S_TypeDef* I2Sx, uint8_t I2S_Register)
{
    __IO uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_REGISTER(I2S_Register));

    tmp = (uint32_t)I2Sx;
    tmp += I2S_Register;

    /* Return the selected register value */
    return (*(__IO uint32_t *) tmp);
}


/**
  * @brief  Transmit a data byte through the I2Sx peripheral.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  Data: Byte to be transmitted..
  * @retval None
  */
void I2S_SendData(I2S_TypeDef* I2Sx, uint32_t Data)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));

    /* Write in the FIFO the data to be sent */
    I2Sx->FIFO = (uint32_t)Data;
}

/**
  * @brief  Returns the most recent received data by the I2Sx peripheral.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @retval The value of the received data.
  */
uint32_t I2S_ReceiveData(I2S_TypeDef* I2Sx)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));

    /* Return the data in the DR register */
    return (uint32_t)I2Sx->FIFO;
}


/**
  * @brief  Enables or disables all the I2S interrupts mask request.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  NewState: new state of all the I2Sx interrupts request.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2S_AllITMaskCmd(I2S_TypeDef* I2Sx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable all the I2S interrupts request mask*/
        I2Sx->CID_CTRL |= I2S_CID_CTRL_INTREQMASK;
    }
    else
    {
        /* I2S interrupts request individual maks*/
        I2Sx->CID_CTRL &= (uint32_t)~((uint32_t)I2S_CID_CTRL_INTREQMASK);
    }
}


/**
  * @brief  Enables or disables the specified I2S FIFO interrupts.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_IT_Mask: specifies the I2S interrupts sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg I2S_TFIFOEMPTY_MASK : Transmit fifo empty flag mask
  *            @arg I2S_TFIFOAEMPTY_MASK: Transmit fifo almost empty flag mask
  *            @arg I2S_TFIFOFULL_MASK  : Transmit fifo full flag mask
  *            @arg I2S_TFIFOAFULL_MASK : Transmit fifo almost full flag mask
  *            @arg I2S_RFIFOEMPTY_MASK : Receive fifo empty flag mask
  *            @arg I2S_RFIFOAEMPTY_MASK: Receive fifo almost empty flag mask
  *            @arg I2S_RFIFOFULL_MASK  : Receive fifo full flag mask
  *            @arg I2S_RFIFOAFULL_MASK : Receive fifo almost full flag mask
  * @param  NewState: new state of the specified I2Sx FIFO interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2S_FIFOITConfig(I2S_TypeDef* I2Sx, uint32_t I2S_IT_Mask, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_I2S_FIFO_IT_MASK(I2S_IT_Mask));

    if (NewState != DISABLE)
    {
        /* Enable the selected I2S FIFO interrupts */
        I2Sx->CID_CTRL |= I2S_IT_Mask;
    }
    else
    {
        /* Disable the selected I2S FIFO interrupts */
        I2Sx->CID_CTRL &= (uint32_t)~((uint32_t)I2S_IT_Mask);
    }
}

/**
  * @brief  Enables or disables the specified I2S channel 0/1 data
  *          underrun/overrun interrupts.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_IT_Mask: specifies the I2S interrupts sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg I2S_0_MASK: I2S channel 0 data underrun/overrun interrupts mask
  *            @arg I2S_1_MASK: I2S channel 1 data underrun/overrun interrupts mask
  * @param  NewState: new state of the specified I2Sx channel 0/1
  *          data underrun/overrun interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2S_DataITConfig(I2S_TypeDef* I2Sx, uint32_t I2S_IT_Mask, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_I2S_DATA_IT_MASK(I2S_IT_Mask));

    if (NewState != DISABLE)
    {
        /* Enable the selected I2S channel 0/1 data underrun/overrun interrupts */
        I2Sx->CID_CTRL |= I2S_IT_Mask;
    }
    else
    {
        /* Disable the selected I2S channel 0/1 data underrun/overrun interrupts */
        I2Sx->CID_CTRL &= (uint32_t)~((uint32_t)I2S_IT_Mask);
    }
}


/**
  * @brief  Checks whether the specified I2S interrupt has occurred or not.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_IT: specifies the interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg I2S_IT_TDATAUNDERR: Transmitter data underrun event
  *            @arg I2S_IT_RDATAOVRERR: Receiver data overrun error
  *            @arg I2S_IT_TFIFOEMPTY : Transmit fifo empty flag
  *            @arg I2S_IT_TFIFOAEMPTY: Transmit fifo almost empty flag
  *            @arg I2S_IT_TFIFOFULL  : Transmit fifo full flag
  *            @arg I2S_IT_TFIFOAFULL : Transmit fifo almost full flag
  *            @arg I2S_IT_RFIFOEMPTY : Receive fifo empty flag
  *            @arg I2S_IT_RFIFOAEMPTY: Receive fifo almost empty flag
  *            @arg I2S_IT_RFIFOFULL  : Receive fifo full flag
  *            @arg I2S_IT_RFIFOAFULL : Receive fifo almost full flag
  * @retval The new state of I2S_IT (SET or RESET).
  */
ITStatus I2S_GetITStatus(I2S_TypeDef* I2Sx, uint32_t I2S_IT)
{
    uint32_t tmpreg = 0;
    ITStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_GET_IT(I2S_IT));

    /* Get the INTR_STAT register value */
    tmpreg = I2Sx->INTR_STAT;

    /* Get flag status */
    tmpreg &= I2S_IT;

    /* Check the status of the specified I2S flag */
    if (tmpreg != RESET)
    {
        /* I2S_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* I2S_IT is reset */
        bitstatus = RESET;
    }

    /* Return the I2S_IT status */
    return bitstatus;
}


/**
  * @brief  Clears the I2Sx's interrupt pending bits.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_IT: specifies the interrupt pending bit to clear.
  *          This parameter can be any combination of the following values:
  *            @arg I2S_IT_TDATAUNDERR: Transmitter data underrun event
  *            @arg I2S_IT_RDATAOVRERR: Receiver data overrun error
  *            @arg I2S_IT_TFIFOEMPTY : Transmit fifo empty flag
  *            @arg I2S_IT_TFIFOAEMPTY: Transmit fifo almost empty flag
  *            @arg I2S_IT_TFIFOFULL  : Transmit fifo full flag
  *            @arg I2S_IT_TFIFOAFULL : Transmit fifo almost full flag
  *            @arg I2S_IT_RFIFOEMPTY : Receive fifo empty flag
  *            @arg I2S_IT_RFIFOAEMPTY: Receive fifo almost empty flag
  *            @arg I2S_IT_RFIFOFULL  : Receive fifo full flag
  *            @arg I2S_IT_RFIFOAFULL : Receive fifo almost full flag
  * @retval The new state of I2S_IT (SET or RESET).
  */
void I2S_ClearITPendingBit(I2S_TypeDef* I2Sx, uint32_t I2S_IT)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_CLEAR_IT(I2S_IT));

    /* Clear the selected flag */
    if ((I2S_IT & I2S_IT_RDATAOVRERR) == I2S_IT_RDATAOVRERR)
    {
        I2Sx->INTR_STAT &= (uint32_t)~((uint32_t)I2S_IT);
    }
    else
    {
        tmpreg = I2Sx->INTR_STAT;
        tmpreg &= (uint32_t)~((uint32_t)I2S_IT);
        tmpreg |= I2S_IT_RDATAOVRERR;
        I2Sx->INTR_STAT = tmpreg;
    }
}


/**
  * @brief  Returns the channel code of the transmitter that caused underrun event.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @retval The channel code of the transmitter that caused underrun event,
  *          it can be channel 0 or channel 1.
  */
uint8_t I2S_GetUnderrunCode(I2S_TypeDef* I2Sx)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));

    /* Return the channel code of the transmitter that caused underrun event
     * in INTR_STAT register */
    return (uint8_t)((uint32_t)I2Sx->INTR_STAT & I2S_INTR_STAT_UNDERRCODE);
}


/**
  * @brief  Returns the channel code of the receiver that caused overrun error.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @retval the channel code of the receiver that caused overrun error,
  *          it can be channel 0 or channel 1.
  */
uint8_t I2S_GetOverrunCode(I2S_TypeDef* I2Sx)
{
    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));

    /* Return the channel code of the receiver that caused overrun error
     * in INTR_STAT register */
    return (uint8_t)((uint32_t)I2Sx->INTR_STAT & I2S_INTR_STAT_OVRERRCODE);
}


/**
  * @brief  Returns the I2S polling status.
  * @param  I2Sx: where x can be 2 or 3 to select the I2S peripheral.
  * @param  I2S_Stat: specifies the I2S current FIFO or data status to check
  *          This parameter can be one of the following values:
  *            @arg I2S_STAT_TFIFOEMPTY : Transmit fifo empty flag
  *            @arg I2S_STAT_TFIFOAEMPTY: Transmit fifo almost flag
  *            @arg I2S_STAT_TXUNDERRUN : Transmitter data underrun
  *            @arg I2S_STAT_RFIFOFULL  : Receive fifo full flag
  *            @arg I2S_STAT_RFIFOAFULL : Receive fifo almost full flag
  *            @arg I2S_STAT_RXOVERRUN  : Receiver data overrun
  * @retval The new state of I2S_STAT (SET or RESET).
  */
FlagStatus I2S_GetPollStatus(I2S_TypeDef* I2Sx, uint32_t I2S_Stat)
{
    uint32_t tmpreg = 0;
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_I2S_ALL_PERIPH(I2Sx));
    assert_param(IS_I2S_GET_STAT(I2S_Stat));

    /* Get the POLL_STAT register value */
    tmpreg = I2Sx->POLL_STAT;

    /* Get flag status */
    tmpreg &= I2S_Stat;

    if (tmpreg != 0)
    {
        /* I2S_Stat is set */
        bitstatus = SET;
    }
    else
    {
        /* I2S_Stat is reset */
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE**********************/
