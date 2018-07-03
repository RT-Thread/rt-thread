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
/** \\file i2c.h
**
** History:
**
**   - 2018-03-12  1.0   LB   First version for Device Driver Library of I2C.
**
 ******************************************************************************/

#ifndef __I2C_H__
#define __I2C_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"
#include "clk.h"
#include "base_types.h"
#include "hc32f480.h"

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
 * Global type definitions ('typedef')
 ******************************************************************************/

/**
 *******************************************************************************
 ** \breif  I2C mode type.
 **
 ******************************************************************************/
typedef enum en_i2c_mode
{
    I2cMaster                       = 1u,   ///< I2C is master mode.
    I2cSlave                        = 0u,   ///< I2C is slave mode.
} en_i2c_mode_t;

/**
 *******************************************************************************
 ** \breif  I2C is transmiter mode or receiver mode.
 **
 ******************************************************************************/
typedef enum en_i2c_tr_mode
{
    I2c_masterTx_slaverRx            = 0u,   ///< I2C transmit data.
    I2c_masterRx_slaverTx            = 1u,   ///< I2C receive data.
} en_i2c_tr_mode_t;

/**
 *******************************************************************************
 ** \breif  I2C ack write enable.
 **
 ******************************************************************************/
typedef enum en_i2c_ack_write_en
{
    I2cAckWriteDis                  = 0u,   ///< I2C ack write disable.
    I2cAckWriteEn                   = 1u,   ///< I2C ack write enable.
} en_i2c_ack_write_en;

/**
 *******************************************************************************
 ** \breif  I2C acknowledge type.
 **
 ******************************************************************************/
typedef enum en_i2c_ack_type
{
    I2cAck                          = 0u,   ///< I2C send ACK.
    I2cNack                         = 1u,   ///< I2C send NAC.
} en_i2c_ack_type_t;

/**
 *******************************************************************************
 ** \breif  I2C capacity of digital-noise-filter.
 **
 ******************************************************************************/
typedef enum en_i2c_digital_filter
{
    I2cDnf1                         = 0u,   ///< I2C digital filter is 1 clock.      
    I2cDnf2                         = 1u,   ///< I2C digital filter is 2 clock.
    I2cDnf3                         = 2u,   ///< I2C digital filter is 3 clock.
    I2cDnf4                         = 3u,   ///< I2C digital filter is 4 clock.
} en_i2c_digital_filter_t;

/**
 *******************************************************************************
 ** \breif  I2C slave address channel.
 **
 ******************************************************************************/
typedef enum en_slaveaddr_ch
{
    I2cSlaveAddr0                   = 0u,   ///< I2C slave address channel 0.
    I2cSlaveAddr1                   = 1u,   ///< I2C slave address channel 1.
    I2cSlaveAddr2                   = 2u,   ///< I2C slave address channel 2.  
} en_slaveaddr_ch_t;

/**
 *******************************************************************************
 ** \breif  I2C internal base clock devide selection.
 **
 ******************************************************************************/
typedef enum en_i2c_clk_div
{
    I2cPclkDiv1                     = 0u,   ///< I2C clock is 1/1 of Pclk.
    I2cPclkDiv2                     = 1u,   ///< I2C clock is 1/2 of Pclk.
    I2cPclkDiv4                     = 2u,   ///< I2C clock is 1/4 of Pclk.
    I2cPlckDiv8                     = 3u,   ///< I2C clock is 1/8 of Pclk.
    I2cPclkDiv16                    = 4u,   ///< I2C clock is 1/16 of Pclk.
    I2cPclkDiv32                    = 5u,   ///< I2C clock is 1/32 of Pclk.
    I2cPclkDiv64                    = 6u,   ///< I2C clock is 1/64 of Pclk.
    I2cPclkDiv128                   = 7u,   ///< I2C clock is 1/128 of Pclk.
} en_i2c_clk_div_t;

/******************************************************************************
 ** \brief  I2C communication status enumeration.
 **
 ******************************************************************************/
typedef enum en_i2c_status
{
    I2cTxEmpty                      = 0u,   ///< I2C transmit register empty.
    I2cTxDone                       = 1u,   ///< I2C transmit complete.
    I2cRxFull                       = 2u,   ///< I2C receieve register full.
    I2cTimeOut                      = 3u,   ///< I2C detect the SCL timeout.
    I2cStartDetect                  = 4u,   ///< I2C detect the start condition.
    I2cStopDetect                   = 5u,   ///< I2C detect the stop condition.
    I2cGcMatch                      = 6u,   ///< I2C GC address match.
    I2cSlAddrMatch                  = 7u,   ///< I2C slave address match.
    I2cBusBusy                      = 8u,   ///< I2C bus is busy or not.
    I2cNackDetect                   = 9u,   ///< I2C detect the NACK
}en_i2c_status_t;

/**
 ******************************************************************************
 ** \brief  I2C time out counter bits.
 **
 ******************************************************************************/
typedef enum
{
    TimeoutCnt16Bits                = 0u,   ///< I2C timeout counter 16 bits.
    TimeoutCnt14Bits                = 1u,   ///< I2C timeout counter 14 bits.
}en_i2c_timeout_bits_t;

/**
 ******************************************************************************
 ** \brief  I2C interrupt enable strucure.
 **
 ******************************************************************************/
typedef enum
{
    TxEmptyIrq                      = 0u,  ///< I2C transfer empty interrupt.           
    RxFullIrq                       = 1u,  ///< I2C receive full interrupt.
    TxDoneIrq                       = 2u,  ///< I2C transfer done interrupt.
    ArlofIrq                        = 3u,  ///< I2C communication error interrupt.
    NackIrq                         = 4u,  ///< I2C nack interrupt.
    TimeOutIrq                      = 5u,  ///< I2C timeout interrupt.
    StarDetectIrq                   = 6u,  ///< I2C detect start interrupt.
    StopDetectIrq                   = 7u,  ///< I2C detect stop interrupt.
}en_i2c_irq_en_t;

/**
 ******************************************************************************
 ** \brief: I2C initialize structure definition
 ******************************************************************************/
typedef struct
{
    en_i2c_mode_t               enMsMode;        ///< I2C master mode or slave mode
    uint32_t                    u32BaudRate;     ///< I2C baudrate(bps)
    en_functional_state_t       enDnfEn;         ///< I2C DNF enable setting
    en_i2c_ack_type_t           enAck;           ///< I2C ACK Type
  
    en_functional_state_t       enHTimeout;      ///< I2C high level time out detection
    en_functional_state_t       enLTimeout;      ///< I2C low levle time out detection
    
    uint16_t                    u16SlaveAddr0;   ///< I2C slave address0 value.
    uint16_t                    u16SlaveAddr1;   ///< I2C slave address1 value.
    uint16_t                    u16SlaveAddr2;   ///< I2C slave address2 value.
    
    en_i2c_timeout_bits_t       enTimeoutCntBits;///< I2C time out counter bits
    en_i2c_digital_filter_t     enI2cDnf;        ///< I2C digital noise filter setting
    en_i2c_clk_div_t            enI2cClkDiv;     ///< I2C plck division setting
} stc_i2c_init_t;


/******************************************************************************
*
* @defgroup I2C private functions
*
******************************************************************************/
en_result_t I2C_DeInit(M4_I2C_TypeDef* I2Cx);
en_result_t I2C_Init(M4_I2C_TypeDef* I2Cx, stc_i2c_init_t* stcI2CInit);
en_i2c_ack_type_t I2C_GetAck(M4_I2C_TypeDef* I2Cx);
void I2C_Cmd(M4_I2C_TypeDef* I2Cx, en_functional_state_t NewState);
en_i2c_tr_mode_t I2C_GetDir(M4_I2C_TypeDef* I2Cx);
void I2C_GenerateStart(M4_I2C_TypeDef* I2Cx, en_functional_state_t NewState);
void I2C_GenerateStop(M4_I2C_TypeDef* I2Cx, en_functional_state_t NewState);
void I2C_GenerateRestart(M4_I2C_TypeDef* I2Cx, en_functional_state_t NewState);
void I2C_DigitalFilterConfig(M4_I2C_TypeDef* I2Cx, en_i2c_digital_filter_t I2C_DigitalFilter);
en_result_t I2C_SetBaudRate(M4_I2C_TypeDef* I2Cx, uint32_t u32Baudrate);
void I2C_ClrStatus(M4_I2C_TypeDef* I2Cx, en_i2c_status_t enStatus);
en_flag_status_t I2C_GetStatus(M4_I2C_TypeDef* I2Cx, en_i2c_status_t enStatus);
void I2C_SendData(M4_I2C_TypeDef* I2Cx, uint8_t Data);
uint8_t I2C_ReceiveData(M4_I2C_TypeDef* I2Cx);
void I2C_AckConfig(M4_I2C_TypeDef* I2Cx, en_i2c_ack_type_t AckCmd);
void I2C_Send7BitAddress(M4_I2C_TypeDef* I2Cx, uint8_t Address, en_i2c_tr_mode_t enDir);
en_result_t I2C_ConfigIrq(M4_I2C_TypeDef* I2Cx, en_i2c_irq_en_t enIrqSel, \
en_functional_state_t StateCmd);

#ifdef __cplusplus
}
#endif
/******************************************************************************
*
 * Global type definitions ('typedef')
 
******************************************************************************/
#endif 
/**
 *******************************************************************************
 *  \brief function pointer type to void/void function
 **
 ******************************************************************************/
