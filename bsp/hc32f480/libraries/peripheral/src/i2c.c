/*******************************************************************************
* Copyright (C) 2017, Huada Semiconductor Co.,Ltd All rights reserved.
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
/** \\file i2c.C
**
** History:
**
**   - 2018-03-12  1.0  LB   First version for Device Driver Library of I2C.
**
******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "i2c.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup I2CGroup ("Intel-Integrated Circuit")
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
* Local pre-processor symbols/macros ('#define')
*******************************************************************************/
#define I2C_BAUDRATE_MAX                400000ul
#define I2C_DIGITAL_FILTER_MAX          3u              



#define I2C_STATUS_MASK                 ((uint8_t)0x0C)
#define I2C_SLAVEADDRESS_MASK           ((uint16_t)0x07FF)
#define I2C_BAUDRATE_MASK               ((uint16_t)0xFFFF)

/* Define if I2C interruptions */
#define I2C_IT_TXEMPTY                  ((uint32_t)0x00800000)
#define I2C_IT_TXEND                    ((uint32_t)0x00400000)
#define I2C_IT_RXFULL                   ((uint32_t)0x00200000)
#define I2C_IT_NACK                     ((uint32_t)0x00100000)
#define I2C_IT_STOP                     ((uint32_t)0x00080000)
#define I2C_IT_START                    ((uint32_t)0x00040000)
#define I2C_IT_ARBI                     ((uint32_t)0x00020000)
#define I2C_IT_TMOUT                    ((uint32_t)0x00010000)
#define IS_I2C_CONFIG_IT(IT)            ((((IT) & (uint32_t)0xFF00FFFF) == 0x00) && ((IT) != 0x00))

#define I2C_SLR_ADDR0                   ((uint8_t)0x01)

#define I2C_CR1_DEFAULT                 ((uint32_t)0x0000001F)
#define I2C_CR2_DEFAULT                 ((uint32_t)0x08000608)
#define I2C_CR3_DEFAULT                 ((uint32_t)0x00000972)
#define I2C_SR0_DEFAULT                 ((uint32_t)0x00000000)
#define I2C_SR1_DEFAULT                 ((uint32_t)0x00000000)
#define I2C_BR_DEFAULT                  ((uint32_t)0x0000FFFF)

/*! Parameter check for I2C channel !*/
#define IS_VALID_I2C(i2c)               (i2c == M4_I2C)

/*! Parameter check for I2C baudrate value !*/
#define IS_VALID_SPEED(speed)           (speed <= (I2C_BAUDRATE_MAX))

/*! Parameter check for I2C digital noise filter value !*/
#define IS_DIGITAL_FILTER(filter)       (filter <= (I2C_DIGITAL_FILTER_MAX))

/*! Parameter check for I2C acknowledge !*/
#define IS_VALID_ACK(ack)               ((ack == (I2cAck))                      || \
                                         (ack == (I2cNack)))

/*! Parameter check for I2C data flow direction !*/
#define IS_VALID_DIRECTION(direction)   ((direction == (I2c_masterTx_slaverRx)) || \
                                         (direction == (I2c_masterRx_slaverTx)))

/*! Parameter check for I2C status !*/
#define IS_VALID_STATUS(status)         ((status == (I2cTxEmpty))               || \
                                         (status == (I2cTxDone))                || \
                                         (status == (I2cRxFull))                || \
                                         (status == (I2cStartDetect))           || \
                                         (status == (I2cStopDetect))            || \
                                         (status == (I2cTimeOut))               || \
                                         (status == (I2cGcMatch))               || \
                                         (status == (I2cSlAddrMatch))           || \
                                         (status == (I2cBusBusy))               || \
                                         (status == (I2cNackDetect)))

/*! Parameter check for I2C DNF !*/
#define IS_VALID_DNF(dnf)               ((dnf == (I2cDnf1))                     || \
                                         (dnf == (I2cDnf2))                     || \
                                         (dnf == (I2cDnf3)))
/*! Parameter check for I2C mode !*/                                                     
#define IS_I2C_MODE(mode)               ((mode == (I2cMaster))                  || \
                                         (mode == (I2cSlave)))

/*! Parameter check for I2C slave chanel !*/
#define IS_SLAVEADDRESS_CH(channel)     ((channel == (I2cSlaveAddr0))           || \
                                         (channel == (I2cSlaveAddr1))           || \
                                         (channel == (I2cSlaveAddr2)))

/*! Parameter check for I2C interruption !*/
#define IS_VALID_IRQ(irq)               ((irq == (TxEmptyIrq))                  || \
                                         (irq == (RxFullIrq))                   || \
                                         (irq == (TxDoneIrq))                   || \
                                         (irq == (ArlofIrq))                    || \
                                         (irq == (NackIrq))                     || \
                                         (irq == (TimeOutIrq))                  || \
                                         (irq == (StarDetectIrq))              || \
                                         (irq == (StopDetectIrq)))
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
 ** \brief  Deinitializes the I2Cx peripheral register to default value.
 **
 ** \param  [in] I2Cx               where x is the channel of i2c peripheral.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t I2C_DeInit(M4_I2C_TypeDef* I2Cx)
{
    /* Check the parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    
    /* Set the register to default value */
    I2Cx->I2CCR1 = I2C_CR1_DEFAULT;
    I2Cx->I2CCR2 = I2C_CR2_DEFAULT;
    I2Cx->I2CCR3 = I2C_CR3_DEFAULT;
    I2Cx->I2CSR0 = I2C_SR0_DEFAULT;
    I2Cx->I2CSR1 = I2C_SR1_DEFAULT;
    I2Cx->I2CBR  = I2C_BR_DEFAULT;
    
    return (Ok);
}

/**
 *******************************************************************************
 ** \brief  Initializes the I2Cx peripheral.
 **
 ** \param  [in] I2Cx               where x is the channel of i2c.
 **         [in] stcI2cInit         structure of I2C initializes parameters.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t I2C_Init(M4_I2C_TypeDef* I2Cx, stc_i2c_init_t* pstcI2cInit)
{
    stc_i2c_i2ccr2_field_t          stcCR2  = { 0u };
    
    /* Check the parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    DDL_ASSERT(IS_VALID_SPEED(pstcI2cInit->u32BaudRate));
    DDL_ASSERT(IS_I2C_MODE(pstcI2cInit->enMsMode));
    DDL_ASSERT(IS_VALID_DNF(pstcI2cInit->enI2cDnf));
    
    if(pstcI2cInit == NULL)
    {
        return (ErrorInvalidParameter);
    }
    
    /* Disable I2C before reset */
    I2Cx->I2CCR1_f.PE = Disable;
    /* Reset communication by software */
    I2Cx->I2CCR1_f.SWRST = Enable;
    /* Enable I2C */
    I2Cx->I2CCR1_f.PE = Enable;
    /* Set the I2C work mode */
    I2Cx->I2CCR1_f.MSL = pstcI2cInit->enMsMode;
    /* Slave address setting */
    if(I2cSlave == pstcI2cInit->enMsMode)
    {
        /* I2C slave address0 setting */
        if(NULL != pstcI2cInit->u16SlaveAddr0)
        {
            I2Cx->I2CSLR0 |= (pstcI2cInit->u16SlaveAddr0 & I2C_SLAVEADDRESS_MASK);
        }
        
        /* I2C slave address1 setting */
        if(NULL != pstcI2cInit->u16SlaveAddr0)
        {
            I2Cx->I2CSLR1 |= (pstcI2cInit->u16SlaveAddr1 & I2C_SLAVEADDRESS_MASK);
        }
         
        /* I2C slave address2 setting */
        if(NULL != pstcI2cInit->u16SlaveAddr0)
        {
            I2Cx->I2CSLR2 |= (pstcI2cInit->u16SlaveAddr2 & I2C_SLAVEADDRESS_MASK);
        }
        
    }
    /* Setting I2c digital noise filter parameters */
    stcCR2.DNF = pstcI2cInit->enI2cDnf;
    /* I2c pclk division setting */
    stcCR2.CKDIV = pstcI2cInit->enI2cClkDiv;
    
    I2C_SetBaudRate(I2Cx, pstcI2cInit->u32BaudRate);
    

    /* I2c high level time out setting */
    stcCR2.HTMOUT = pstcI2cInit->enHTimeout;
    /* I2c low level time out setting */
    stcCR2.LTMOUT = pstcI2cInit->enLTimeout;
    /* I2c time out counter bits setting */
    stcCR2.TMOUTM = pstcI2cInit->enTimeoutCntBits;
    /* Set the CR2 value*/
    I2Cx->I2CCR2_f = stcCR2;
    
    I2Cx->I2CCR1_f.SWRST = 0u;
    
    /* Enable the i2c low_level auto hold */ 
    (*(volatile uint32_t *)0x4004b404) |= 0x00400000;
    return (Ok);
}

/**
 *******************************************************************************
 ** \brief  Set the buadrate for I2C peripheral.
 **
 ** \param  [in] I2Cx               where x is the channel of I2C peripheral.
 **         [in] u32Baudrate        the value of baudarate.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t I2C_SetBaudRate(M4_I2C_TypeDef* I2Cx, uint32_t u32Baudrate)
{
    uint32_t pclk3                  = 8000000;
    uint8_t u8MinValue              = 0;
    uint8_t u8Result                = 0;
    uint16_t u16Result              = 0;
    uint8_t u8temp                  = 0;
    stc_clk_freq_t                  enClkFreq;
        
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    DDL_ASSERT(IS_VALID_SPEED(u32Baudrate));
    
    /* Check the buadrate validity */
    if(u32Baudrate == NULL)
    {
        return (ErrorInvalidParameter);
    }
    else
    {
        /* Get the I2c peripheral clk frequence */
        Clk_GetClockFreq(&enClkFreq);
        pclk3 = enClkFreq.pclk3Freq;
        u8temp = (uint8_t)(pclk3 / (u32Baudrate));
        
        /* If the ditigal noise filter is enabled */
        if(Enable == I2Cx->I2CCR3_f.DNFEN)
        {
            /* If the clock division is 0x00 */
            if(I2cPclkDiv1 == I2Cx->I2CCR2_f.CKDIV)
            {
                u8Result = (uint8_t)((u8temp / 2) - 3 - I2Cx->I2CCR2_f.DNF);
            }
            /* If the clock division is not 0x00 */
            else
            {
                u8Result = (uint8_t)((u8temp / 2) - 2 - I2Cx->I2CCR2_f.DNF);
            }
        }
        /* If the digital noise filter is disabled */
        else
        {
            /* If the clock division is 0x00 */
            if(I2cPclkDiv1 == I2Cx->I2CCR2_f.CKDIV)
            {
                u8Result = (uint8_t)((u8temp / 2) - 3);
            }
            /* If the clock division is not 0x00 */
            else
            {
                u8Result = (uint8_t)((u8temp / 2) - 2);
            }
        }
        
        u16Result = (uint16_t)(I2Cx->I2CBR & (u8Result<<8));
        /* Get the minimum result value for register */
        if(u32Baudrate <= 100000)
        {
            u8MinValue = ((250 * (pclk3 / 1000000)) / 1000);
        }
        else/* Baudrate <= 400000 */
        {
            u8MinValue = ((100 * (pclk3 / 1000000)) / 1000);
        }
        
        if(I2cSlave == I2Cx->I2CCR1_f.MSL)
        {
            /* Set the minimum value for the register */
            if(u8Result <= u8MinValue)
            {
                u8Result = u8MinValue;
            }
        }
        
        I2Cx->I2CBR = (uint16_t)(u16Result | u8Result);
    }
    return (Ok);
}

/**
 *******************************************************************************
 ** \brief  Check whether I2c get ack or nack.
 **
 ** \param  [in] I2Cx               where x is the channel of I2C peripheral.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
en_i2c_ack_type_t I2C_GetAck(M4_I2C_TypeDef* I2Cx)
{    
    en_i2c_ack_type_t enFlag;
    
    /* Check the parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    
    /* Get the I2C ACK flag */
    enFlag = (0u == I2Cx->I2CCR2_f.ACKRF) ? I2cAck : I2cNack;

    return enFlag;
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the specified I2C peripheral.
 **
 ** \param  [in] I2Cx               where x is the channel of I2C peripheral.
 **         [in] StateCmd           new state of the I2C peripheral.
 ** \arg    -Enable.
 ** \arg    -Disable.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void I2C_Cmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t StateCmd)
{    
    /* Check the parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(StateCmd));

    /* Set the Enable or Disable of selected I2C peripheral */
    I2Cx->I2CCR1_f.PE = (((Enable) == StateCmd) ? Set : Reset);
}

/**
 *******************************************************************************
 ** \brief  I2C generates start condition
 **
 ** \param  [in] I2Cx               where x is the channle of i2c peripheral.
 **         [in] StateCmd           new state of the I2C peripheral.
 ** \arg    -Enable.
 ** \arg    -Disable.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void I2C_GenerateStart(M4_I2C_TypeDef* I2Cx, en_functional_state_t StateCmd)
{
    /* Check the parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(StateCmd));
    
    /* Generate the START condition or not */
    I2Cx->I2CCR1_f.START = (((Enable) == StateCmd) ? Set : Reset);
}

/**
 *******************************************************************************
 ** \brief  I2C generates stop condition
 **
 ** \param  [in] I2Cx               where x is the channle of i2c peripheral.
 **         [in] StateCmd           new state of the I2C peripheral.
 ** \arg    -Enable.
 ** \arg    -Disable.
 **
 ** \retval None
 ** 
 ** \note   None
 **
 ******************************************************************************/
void I2C_GenerateStop(M4_I2C_TypeDef* I2Cx, en_functional_state_t StateCmd)
{
    /* Check the parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(StateCmd));
    
    /* Generate the STOP condition or not */
    I2Cx->I2CCR1_f.STOP = (((Enable) == StateCmd) ? Set : Reset);
}

/**
 *******************************************************************************
 ** \brief  I2C generates restart condition
 **
 ** \param  [in] I2Cx               where x is the channle of i2c peripheral.
 **         [in] StateCmd           new state of the I2C peripheral.
 ** \arg    -Enable.
 ** \arg    -Disable.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void I2C_GenerateRestart(M4_I2C_TypeDef* I2Cx, en_functional_state_t StateCmd)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(StateCmd));
        
    /* Generate the RESTART condition or not */
    I2Cx->I2CCR1_f.RESTART = (((Enable) == StateCmd) ? Set : Reset);
}

/**
 *******************************************************************************
 ** \brief  Configures the digital noise filter of I2C peripheral.
 **
 ** \param  [in] I2Cx               where x is the channel of I2C peripheral.
 **         [in] I2C_DigitalFiler:  Coefficient of digital noise filter.
 ** \arg    -I2cDnf1.
 ** \arg    -I2cDnf2.
 ** \arg    -I2cDnf3.
 ** \arg    -I2cDnf4.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void I2C_DigitalFilterConfig(M4_I2C_TypeDef* I2Cx,\
                             en_i2c_digital_filter_t I2C_DigitalFilter)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    DDL_ASSERT(IS_DIGITAL_FILTER(I2C_DigitalFilter));

    /* Enable the digital noise filter write protection */
    I2Cx->I2CCR3_f.DNFEN = 1u;

    /* Set the I2C digital noise filter clock period */
    I2Cx->I2CCR2_f.DNF = I2C_DigitalFilter;

}

/**
 *******************************************************************************
 ** \brief  Set the acknowledge type.
 **
 ** \param  [in] I2Cx               where x is the channel of I2C peripheral.
 **         [in] AckCmd             AckCmd is the type to send acknowledge.
 ** \arg    -Ack.
 ** \arg    -Nack.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void I2C_AckConfig(M4_I2C_TypeDef* I2Cx, en_i2c_ack_type_t AckCmd)
{
    uint8_t u8temp;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    DDL_ASSERT(IS_VALID_ACK(AckCmd));
    
    u8temp = I2Cx->I2CCR2_f.ACKWEN;
    /* Enable ACK write protection */
    I2Cx->I2CCR2_f.ACKWEN = 1u;

    /* Set the ack type to send */
    I2Cx->I2CCR2_f.ACK = ((I2cAck == AckCmd) ? (I2cAck) : (I2cNack));
    
    /* Resume the ack write enable */
    I2Cx->I2CCR2_f.ACKWEN = u8temp;
}

/**
 *******************************************************************************
 ** \brief  Set the slave address for I2C slave device.
 **
 ** \param  [in] I2Cx               where x is the channel of I2C peripheral.
 **         [in] channel            channel is the I2C slave device
 ** \arg    -I2cSlaveAddr0.
 ** \arg    -I2cSlaveAddr1.
 ** \arg    -I2cSlaveAddr2.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void I2C_SlaveAddrConfig(M4_I2C_TypeDef* I2Cx, en_slaveaddr_ch_t channel,\
                          uint16_t Address)
{
    uint16_t u16tmpReg = 0;
    
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    DDL_ASSERT(IS_SLAVEADDRESS_CH(channel));
    
    /* Get the address value */
    u16tmpReg = Address & I2C_SLAVEADDRESS_MASK;
    
    /* Set the address value to specific device */
    switch(channel)
    {
        case I2cSlaveAddr0:
            I2Cx->I2CSLR0 |= u16tmpReg;
            break;
        case I2cSlaveAddr1:
            I2Cx->I2CSLR1 |= u16tmpReg;
            break;
        case I2cSlaveAddr2:
            I2Cx->I2CSLR2 |= u16tmpReg;
            break;
        default:
            break;
    }
}

/**
 *******************************************************************************
 ** \brief  Set the general call enable or not
 **
 ** \param  [in] I2Cx               where x is the channel of I2C peripheral.
 **         [in] StateCmd           new state of the I2C peripheral.
 ** \arg    -Enable.
 ** \arg    -Disable.
 **
 ** \retval None
 **
 *8 \note   None
 **
 ******************************************************************************/
void I2C_GeneralCallConfig(M4_I2C_TypeDef* I2Cx, en_functional_state_t StateCmd)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(StateCmd));
    
    /* Enable or Disable the general call address detection */
    I2Cx->I2CCR3_f.GCEN = (((Enable) == StateCmd) ? Set : Reset);
}

/**
 ******************************************************************************
 ** \brief  Enable/Disable I2C interrupts
 **
 ** \param  [in] I2Cx             where x is the channel of I2C peripheral.
 ** \param  [in] enIrqSel         Enumeration of I2C interrupt selection
 ** \arg    -TxEmptyIrq           TX empty interrupt of I2C
 ** \arg    -RxFullIrq            RX full interrupt of I2C
 ** \arg    -TxDoneIrq            TX done interrupt of I2C
 ** \arg    -ArlofIrq             Arlof allow interrpt of I2C
 ** \arg    -NackIrq              Nack allow interrupt of I2C
 ** \arg    -TimeOutIrq           TimeOut interrupt of I2C
 ** \arg    -StarDetectIrq        Start detect interrupt of I2C
 ** \arg    -StopDetectIrq        Stop detect interrupt of I2C
 **
 ** \retval Ok                    Interrupts has been enabled
 ** \retval ErrorInvalidParameter If one of following conditions are met:
 **                               - enIrqSel == NULL
 **                               - Other invalid configuration
 **
 ******************************************************************************/
en_result_t I2C_ConfigIrq(M4_I2C_TypeDef* I2Cx, en_i2c_irq_en_t enIrqSel, \
                          en_functional_state_t StateCmd)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    DDL_ASSERT(IS_VALID_IRQ(enIrqSel));

    switch (enIrqSel)
    {
        case TxEmptyIrq:
            I2Cx->I2CCR3_f.TEMPTYIE = StateCmd;
            break;
        case RxFullIrq:
            I2Cx->I2CCR3_f.RFULLIE = StateCmd;
            break;
        case TxDoneIrq:
            I2Cx->I2CCR3_f.TENDIE = StateCmd;
            break;
        case ArlofIrq:
            I2Cx->I2CCR3_f.ARLOIE = StateCmd;
            break;
        case NackIrq:
            I2Cx->I2CCR3_f.NACKIE = StateCmd;
            break;
        case TimeOutIrq:
            I2Cx->I2CCR3_f.TMOUTIE = StateCmd;
            break;
        case StarDetectIrq:
            I2Cx->I2CCR3_f.STARTIE = StateCmd;
            break;
        case StopDetectIrq:
            I2Cx->I2CCR3_f.STOPIE = StateCmd;
            break;
        default:
            return (ErrorInvalidParameter);
    }

    return (Ok);
}

/**
 *******************************************************************************
 ** \brief  Reset the I2C peripheral by software.
 **
 ** \param  [in] I2Cx               x is the channel of I2C peripheral.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
en_i2c_tr_mode_t I2C_GetDir(M4_I2C_TypeDef* I2Cx)
{
    en_i2c_tr_mode_t enFlag;
    
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    
    /* Get the flag of i2c data flow diretion */
    enFlag = ((0u == I2Cx->I2CCR1_f.TRA) ? I2c_masterTx_slaverRx : I2c_masterRx_slaverTx);
    
    return enFlag;
}
/**
 *******************************************************************************
 ** \brief  Reset the I2C peripheral by software.
 **
 ** \param  [in] I2Cx               x is the channel of I2C peripheral.
 **         [in] StateCmd           New state of the I2C peripheral.
 ** \arg    -Enable
 ** \arg    -Disable
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void I2C_SoftwareReset(M4_I2C_TypeDef* I2Cx, en_functional_state_t StateCmd)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(StateCmd));
    
    /* Set the PE as communication reset */
    I2Cx->I2CCR1_f.PE = 0u;

    /* Reset the I2C peripheral */
    I2Cx->I2CCR1_f.SWRST = (((Enable) == StateCmd) ? Set : Reset);
}

/**
 *******************************************************************************
 ** \brief  Send a data byte throught the i2cx peripheral.
 **
 ** \param  [in] I2Cx               where x is the channel of I2C peripheral.
 **         [in] Data               one byte data to send.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void I2C_SendData(M4_I2C_TypeDef* I2Cx, uint8_t Data)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    
    /* Return the data in the DTR register */
    I2Cx->I2CDTR = Data;
}

/**
 *******************************************************************************
 ** \brief  Returns the most recent received data by the I2Cx peripheral.
 **
 ** \param  [in]I2Cx                where x is the channel of I2C peripheral.
 **         
 ** \retval None.
 **
 ** \note   None.
 **
 ******************************************************************************/
uint8_t I2C_ReceiveData(M4_I2C_TypeDef* I2Cx)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    
    /* Return the data in the DRR register */
    return I2Cx->I2CDRR;
}


/**
 *******************************************************************************
 ** \brief  Get the flag of different status 
 **
 ** \param  [in] I2Cx               where x is the channel of I2C peripheral.
 **         [in] enStatus           the name of bus status.
 ** \arg    -I2cTxEmpty.
 ** \arg    -I2cTxDone.
 ** \arg    -I2cRxFull.
 ** \arg    -I2cStartDetect.
 ** \arg    -I2cStopDetect.
 ** \arg    -I2cTimeOut.
 ** \arg    -I2cGcMatch.
 ** \arg    -I2cSlAddrMatch.
 ** \arg    -I2cBusBusy.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
en_flag_status_t I2C_GetStatus(M4_I2C_TypeDef* I2Cx, en_i2c_status_t enStatus)
{
    en_flag_status_t enFlag;
    
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    DDL_ASSERT(IS_VALID_STATUS(enStatus));
    
    /* Get the different bus status */
    switch(enStatus)
    {
        case I2cTxEmpty:
            enFlag = (1u == I2Cx->I2CSR1_f.TEMPTYF) ? Set : Reset;
            break;
        case I2cTxDone:
            enFlag = (1u == I2Cx->I2CSR1_f.TENDF) ? Set : Reset;
            break;
        case I2cRxFull:
            enFlag = (1u == I2Cx->I2CSR1_f.RFULLF) ? Set : Reset;
            break;
        case I2cStartDetect:
            enFlag = (1u == I2Cx->I2CSR1_f.STARTF) ? Set : Reset;
            break;
        case I2cStopDetect:
            enFlag = (1u == I2Cx->I2CSR1_f.STOPF) ? Set : Reset;
            break;
        case I2cTimeOut:
            enFlag = (1u == I2Cx->I2CSR1_f.TMOUTF) ? Set : Reset;
            break;
        case I2cGcMatch:
            enFlag = (1u == I2Cx->I2CSR0_f.GCF) ? Set : Reset;
            break;
        case I2cSlAddrMatch:
            enFlag = (((1u == I2Cx->I2CSR0_f.SLADDR0F)                  || \
                      (1u == I2Cx->I2CSR0_f.SLADDR1F)                   || \
                      (1u == I2Cx->I2CSR0_f.SLADDR2F)) ? Set : Reset);
            break;
        case I2cBusBusy:
            enFlag = (1u == I2Cx->I2CCR1_f.BUSY) ? Set : Reset;
            break;
        case I2cNackDetect:
            enFlag = (1u == I2Cx->I2CSR1_f.NACKF) ? Set : Reset;
            break;
        default:
            break;
    }
    
    return enFlag;
}

/**
 *******************************************************************************
 ** \brief  Clear the flag of different bus status 
 **
 ** \param  [in] I2Cx               where x is the channel of I2C peripheral.
 **         [in] enStatus           the name of bus status.
 ** \arg    -I2cTxEmpty.
 ** \arg    -I2cTxDone.
 ** \arg    -I2cRxFull.
 ** \arg    -I2cStartDetect.
 ** \arg    -I2cStopDetect.
 ** \arg    -I2cTimeOut.
 ** \arg    -I2cGcMatch.
 ** \arg    -I2cSlAddrMatch.
 ** \arg    -I2cBusBusy.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void I2C_ClrStatus(M4_I2C_TypeDef* I2Cx, en_i2c_status_t enStatus)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    DDL_ASSERT(IS_VALID_STATUS(enStatus));
    
    /* Clear the different bus status */
    switch(enStatus)
    {
        case I2cTxEmpty:
            I2Cx->I2CSR1_f.TEMPTYF = Reset;
            break;
        case I2cTxDone:
            break;
        case I2cRxFull:
            I2Cx->I2CSR1_f.RFULLF = Reset;
            break;
        case I2cStartDetect:
            I2Cx->I2CSR1_f.STARTF = Reset;
            break;
        case I2cStopDetect:
            I2Cx->I2CSR1_f.STOPF = Reset;
            break;
        case I2cTimeOut:
            I2Cx->I2CSR1_f.TMOUTF = Reset;
            break;
        case I2cGcMatch:
            break;
        case I2cSlAddrMatch:
            break;
        case I2cBusBusy:
            break;
        case I2cNackDetect:
            I2Cx->I2CSR1_f.NACKF = Reset;
            break;
        default:
            break;
    }
}

/**
 *******************************************************************************
 ** \brief  Send the 7 bits address to bus.
 **
 ** \param  [in] I2Cx               where x is the channel of I2C peripheral.
 **         [in] Address            the address value of I2C slave device.
 **         [in] enDir              the direction of bus
 ** \arg    -I2cReceive.
 ** \arg    -I2cTransmit.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void I2C_Send7BitAddress(M4_I2C_TypeDef* I2Cx, uint8_t Address, \
                         en_i2c_tr_mode_t enDir)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2C(I2Cx));
    DDL_ASSERT(IS_VALID_DIRECTION(enDir));
    
    /* Set the last bit of slave address by bus direction */
    if(enDir != I2c_masterTx_slaverRx)
    {
        Address |= I2C_SLR_ADDR0;
    }
    else
    {
        Address &= (uint8_t)~(I2C_SLR_ADDR0);
    }
    
    /* Send the slave address value to DTR */
    I2Cx->I2CDTR = Address; 
}



#ifdef __cplusplus
}
#endif

//@} // I2cGroup

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
