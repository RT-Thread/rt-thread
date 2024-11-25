/*!
    \file    gd32e50x_i2c.c
    \brief   I2C driver

    \version 2023-12-31, V1.4.0, firmware for GD32E50x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32e50x_i2c.h"

#define I2C_ERROR_HANDLE(s)           do{}while(1)

/* I2C register bit mask */
#define I2CCLK_MAX                    ((uint32_t)0x0000007FU)             /*!< i2cclk maximum value */
#define I2CCLK_MIN                    ((uint32_t)0x00000002U)             /*!< i2cclk minimum value */
#define I2C_FLAG_MASK                 ((uint32_t)0x0000FFFFU)             /*!< i2c flag mask */
#define I2C_ADDRESS_MASK              ((uint32_t)0x000003FFU)             /*!< i2c address mask */
#define I2C_ADDRESS2_MASK             ((uint32_t)0x000000FEU)             /*!< the second i2c address mask */

/* I2C register bit offset */
#define STAT1_PECV_OFFSET             ((uint32_t)8U)                      /* bit offset of PECV in I2C_STAT1 */

/* I2C2 register bit offset */
#define CTL0_DNF_OFFSET               ((uint32_t)0x00000008U)             /*!< bit offset of DNF in I2C2_CTL0 */
#define CTL1_BYTENUM_OFFSET           ((uint32_t)0x00000010U)             /*!< bit offset of BYTENUM in I2C2_CTL1 */
#define STAT_READDR_OFFSET            ((uint32_t)0x00000011U)             /*!< bit offset of READDR in I2C2_STAT */
#define TIMING_SCLL_OFFSET            ((uint32_t)0x00000000U)             /*!< bit offset of SCLL in I2C2_TIMING */
#define TIMING_SCLH_OFFSET            ((uint32_t)0x00000008U)             /*!< bit offset of SCLH in I2C2_TIMING */
#define TIMING_SDADELY_OFFSET         ((uint32_t)0x00000010U)             /*!< bit offset of SDADELY in I2C2_TIMING */
#define TIMING_SCLDELY_OFFSET         ((uint32_t)0x00000014U)             /*!< bit offset of SCLDELY in I2C2_TIMING */
#define TIMING_PSC_OFFSET             ((uint32_t)0x0000001CU)             /*!< bit offset of PSC in I2C2_TIMING */
#define SADDR1_ADDMSK_OFFSET          ((uint32_t)0x00000008U)             /*!< bit offset of ADDMSK in I2C2_SADDR1 */
#define TIMEOUT_BUSTOB_OFFSET         ((uint32_t)0x00000010U)             /*!< bit offset of BUSTOB in I2C2_TIMEOUT */

/*!
    \brief      reset I2C
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void i2c_deinit(uint32_t i2c_periph)
{
    switch(i2c_periph)
    {
    case I2C0:
        /* reset I2C0 */
        rcu_periph_reset_enable(RCU_I2C0RST);
        rcu_periph_reset_disable(RCU_I2C0RST);
        break;
    case I2C1:
        /* reset I2C1 */
        rcu_periph_reset_enable(RCU_I2C1RST);
        rcu_periph_reset_disable(RCU_I2C1RST);
        break;
    case I2C2:
        /* reset I2C2 */
        rcu_periph_reset_enable(RCU_I2C2RST);
        rcu_periph_reset_disable(RCU_I2C2RST);
        break;
    default:
        break;
    }
}

/*!
    \brief      enable I2C
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void i2c_enable(uint32_t i2c_periph)
{
    if((I2C0 == i2c_periph) || (I2C1 == i2c_periph))
    {
        I2C_CTL0(i2c_periph) |= I2C_CTL0_I2CEN;
    } else {
        I2C2_CTL0(i2c_periph) |= I2C2_CTL0_I2CEN;
    }
}

/*!
    \brief      disable I2C
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void i2c_disable(uint32_t i2c_periph)
{
    if((I2C0 == i2c_periph) || (I2C1 == i2c_periph))
    {
        I2C_CTL0(i2c_periph) &= ~I2C_CTL0_I2CEN;
    } else {
        I2C2_CTL0(i2c_periph) &= ~I2C2_CTL0_I2CEN;
    }
}

/*!
    \brief      generate a START condition on I2C bus
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void i2c_start_on_bus(uint32_t i2c_periph)
{
    if((I2C0 == i2c_periph) || (I2C1 == i2c_periph))
    {
        I2C_CTL0(i2c_periph) |= I2C_CTL0_START;
    } else {
        I2C2_CTL1(i2c_periph) |= I2C2_CTL1_START;
    }
}

/*!
    \brief      generate a STOP condition on I2C bus
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void i2c_stop_on_bus(uint32_t i2c_periph)
{
    if((I2C0 == i2c_periph) || (I2C1 == i2c_periph))
    {
        I2C_CTL0(i2c_periph) |= I2C_CTL0_STOP;
    } else {
        I2C2_CTL1(i2c_periph) |= I2C2_CTL1_STOP;
    }
}

/*!
    \brief      enable the response to a general call
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void i2c_slave_response_to_gcall_enable(uint32_t i2c_periph)
{
    if((I2C0 == i2c_periph) || (I2C1 == i2c_periph))
    {
        I2C_CTL0(i2c_periph) |= I2C_CTL0_GCEN;
    } else {
        I2C2_CTL0(i2c_periph) |= I2C2_CTL0_GCEN;
    }
}

/*!
    \brief      disable the response to a general call
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void i2c_slave_response_to_gcall_disable(uint32_t i2c_periph)
{
    if((I2C0 == i2c_periph) || (I2C1 == i2c_periph))
    {
        I2C_CTL0(i2c_periph) &= ~I2C_CTL0_GCEN;
    } else {
        I2C2_CTL0(i2c_periph) &= ~I2C2_CTL0_GCEN;
    }
}

/*!
    \brief      enable to stretch SCL low when data is not ready in slave mode
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void i2c_stretch_scl_low_enable(uint32_t i2c_periph)
{
    if((I2C0 == i2c_periph) || (I2C1 == i2c_periph))
    {
        I2C_CTL0(i2c_periph) &= ~I2C_CTL0_SS;
    } else {
        I2C2_CTL0(i2c_periph) &= ~I2C2_CTL0_SS;
    }
}

/*!
    \brief      disable to stretch SCL low when data is not ready in slave mode
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void i2c_stretch_scl_low_disable(uint32_t i2c_periph)
{
    if((I2C0 == i2c_periph) || (I2C1 == i2c_periph))
    {
        I2C_CTL0(i2c_periph) |= I2C_CTL0_SS;
    } else {
        I2C2_CTL0(i2c_periph) |= I2C2_CTL0_SS;
    }
}

/*!
    \brief      I2C transmit data function
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  data: data of transmission
    \param[out] none
    \retval     none
*/
void i2c_data_transmit(uint32_t i2c_periph, uint32_t data)
{
    if((I2C0 == i2c_periph) || (I2C1 == i2c_periph))
    {
        I2C_DATA(i2c_periph) = (I2C_DATA_TRB & data);
    } else {
        I2C2_TDATA(i2c_periph) = (I2C2_TDATA_TDATA & data);
    }
}

/*!
    \brief      I2C receive data function
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[out] none
    \retval     data of received
*/
uint32_t i2c_data_receive(uint32_t i2c_periph)
{
    uint32_t data = 0U;

    if((I2C0 == i2c_periph) || (I2C1 == i2c_periph))
    {
        data = I2C_DATA(i2c_periph) & I2C_DATA_TRB;
    } else {
        data = I2C2_RDATA(i2c_periph) & I2C2_RDATA_RDATA;
    }
    return data;
}

/*!
    \brief      I2C transfers PEC value
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void i2c_pec_transfer(uint32_t i2c_periph)
{
    if((I2C0 == i2c_periph) || (I2C1 == i2c_periph))
    {
        I2C_CTL0(i2c_periph) |= I2C_CTL0_PECTRANS;
    } else {
        I2C2_CTL1(i2c_periph) |= I2C2_CTL1_PECTRANS;
    }
}

/*!
    \brief      enable I2C PEC calculation
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void i2c_pec_enable(uint32_t i2c_periph)
{
    if((I2C0 == i2c_periph) || (I2C1 == i2c_periph))
    {
        I2C_CTL0(i2c_periph) |= I2C_CTL0_PECEN;
    } else {
        I2C2_CTL0(i2c_periph) |= I2C2_CTL0_PECEN;
    }
}

/*!
    \brief      disable I2C PEC calculation
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void i2c_pec_disable(uint32_t i2c_periph)
{
    if((I2C0 == i2c_periph) || (I2C1 == i2c_periph))
    {
        I2C_CTL0(i2c_periph) &= ~I2C_CTL0_PECEN;
    } else {
        I2C2_CTL0(i2c_periph) &= ~I2C2_CTL0_PECEN;
    }
}

/*!
    \brief      get packet error checking value
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[out] none
    \retval     PEC value
*/
uint32_t i2c_pec_value_get(uint32_t i2c_periph)
{
    uint32_t value = 0U;

    if((I2C0 == i2c_periph) || (I2C1 == i2c_periph))
    {
        value = (I2C_STAT1(i2c_periph) & I2C_STAT1_PECV) >> STAT1_PECV_OFFSET;
    } else {
        value = I2C2_PEC(i2c_periph) & I2C2_PEC_PECV;
    }
    return value;
}

/*!
    \brief      configure I2C clock
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  clkspeed: I2C clock speed, supports standard mode (up to 100 kHz), fast mode (up to 400 kHz)
                          and fast mode plus (up to 1MHz)
    \param[in]  dutycyc: duty cycle in fast mode or fast mode plus
                only one parameter can be selected which is shown as below:
      \arg        I2C_DTCY_2: T_low/T_high=2
      \arg        I2C_DTCY_16_9: T_low/T_high=16/9
    \param[out] none
    \retval     none
*/
void i2c_clock_config(uint32_t i2c_periph, uint32_t clkspeed, uint32_t dutycyc)
{
    uint32_t pclk1, clkc, freq, risetime;
    uint32_t temp;

    if(0U == clkspeed)
    {
        I2C_ERROR_HANDLE("the parameter can not be 0 \r\n");
    }

    pclk1 = rcu_clock_freq_get(CK_APB1);
    /* I2C peripheral clock frequency */
    freq = (uint32_t)(pclk1 / 1000000U);
    if(freq >= I2CCLK_MAX)
    {
        freq = I2CCLK_MAX;
    }
    temp = I2C_CTL1(i2c_periph);
    temp &= ~I2C_CTL1_I2CCLK;
    temp |= freq;

    I2C_CTL1(i2c_periph) = temp;

    if(100000U >= clkspeed)
    {
        /* the maximum SCL rise time is 1000ns in standard mode */
        risetime = (uint32_t)((pclk1 / 1000000U) + 1U);
        if(risetime >= I2CCLK_MAX)
        {
            I2C_RT(i2c_periph) = I2CCLK_MAX;
        } else if(risetime <= I2CCLK_MIN)
        {
            I2C_RT(i2c_periph) = I2CCLK_MIN;
        } else {
            I2C_RT(i2c_periph) = risetime;
        }
        clkc = (uint32_t)(pclk1 / (clkspeed * 2U));
        if(clkc < 0x04U)
        {
            /* the CLKC in standard mode minmum value is 4 */
            clkc = 0x04U;
        }
        I2C_CKCFG(i2c_periph) |= (I2C_CKCFG_CLKC & clkc);

    } else if(400000U >= clkspeed)
    {
        /* the maximum SCL rise time is 300ns in fast mode */
        I2C_RT(i2c_periph) = (uint32_t)(((freq * (uint32_t)300U) / (uint32_t)1000U) + (uint32_t)1U);
        if(I2C_DTCY_2 == dutycyc)
        {
            /* I2C duty cycle is 2 */
            clkc = (uint32_t)(pclk1 / (clkspeed * 3U));
            I2C_CKCFG(i2c_periph) &= ~I2C_CKCFG_DTCY;
        } else {
            /* I2C duty cycle is 16/9 */
            clkc = (uint32_t)(pclk1 / (clkspeed * 25U));
            I2C_CKCFG(i2c_periph) |= I2C_CKCFG_DTCY;
        }
        if(0U == (clkc & I2C_CKCFG_CLKC))
        {
            /* the CLKC in fast mode minmum value is 1 */
            clkc |= 0x0001U;
        }
        I2C_CKCFG(i2c_periph) |= I2C_CKCFG_FAST;
        I2C_CKCFG(i2c_periph) |= clkc;
    } else {
        /* fast mode plus, the maximum SCL rise time is 120ns */
        I2C_RT(i2c_periph) = (uint32_t)(((freq * (uint32_t)120U) / (uint32_t)1000U) + (uint32_t)1U);
        if(I2C_DTCY_2 == dutycyc)
        {
            /* I2C duty cycle is 2 */
            clkc = (uint32_t)(pclk1 / (clkspeed * 3U));
            I2C_CKCFG(i2c_periph) &= ~I2C_CKCFG_DTCY;
        } else {
            /* I2C duty cycle is 16/9 */
            clkc = (uint32_t)(pclk1 / (clkspeed * 25U));
            I2C_CKCFG(i2c_periph) |= I2C_CKCFG_DTCY;
        }
        /* enable fast mode */
        I2C_CKCFG(i2c_periph) |= I2C_CKCFG_FAST;
        I2C_CKCFG(i2c_periph) |= clkc;
        /* enable I2C fast mode plus */
        I2C_CTL2(i2c_periph)  |= I2C_FAST_MODE_PLUS_ENABLE;
    }
}

/*!
    \brief      configure I2C address
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  mode:
                only one parameter can be selected which is shown as below:
      \arg        I2C_I2CMODE_ENABLE: I2C mode
      \arg        I2C_SMBUSMODE_ENABLE: SMBus mode
    \param[in]  addformat: 7bits or 10bits
                only one parameter can be selected which is shown as below:
      \arg        I2C_ADDFORMAT_7BITS: address format is 7 bits
      \arg        I2C_ADDFORMAT_10BITS: address format is 10 bits
    \param[in]  addr: I2C address
    \param[out] none
    \retval     none
*/
void i2c_mode_addr_config(uint32_t i2c_periph, uint32_t mode, uint32_t addformat, uint32_t addr)
{
    /* SMBus/I2C mode selected */
    uint32_t ctl = 0U;

    ctl = I2C_CTL0(i2c_periph);
    ctl &= ~(I2C_CTL0_SMBEN);
    ctl |= mode;
    I2C_CTL0(i2c_periph) = ctl;
    /* configure address */
    addr = addr & I2C_ADDRESS_MASK;
    I2C_SADDR0(i2c_periph) = (addformat | addr);
}

/*!
    \brief      select SMBus type
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  type:
                only one parameter can be selected which is shown as below:
      \arg        I2C_SMBUS_DEVICE: device
      \arg        I2C_SMBUS_HOST: host
    \param[out] none
    \retval     none
*/
void i2c_smbus_type_config(uint32_t i2c_periph, uint32_t type)
{
    if(I2C_SMBUS_HOST == type)
    {
        I2C_CTL0(i2c_periph) |= I2C_CTL0_SMBSEL;
    } else {
        I2C_CTL0(i2c_periph) &= ~(I2C_CTL0_SMBSEL);
    }
}

/*!
    \brief      whether or not to send an ACK
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  ack:
                only one parameter can be selected which is shown as below:
      \arg        I2C_ACK_ENABLE: ACK will be sent
      \arg        I2C_ACK_DISABLE: ACK will not be sent
    \param[out] none
    \retval     none
*/
void i2c_ack_config(uint32_t i2c_periph, uint32_t ack)
{
    uint32_t ctl = 0U;

    ctl = I2C_CTL0(i2c_periph);
    ctl &= ~(I2C_CTL0_ACKEN);
    ctl |= ack;
    I2C_CTL0(i2c_periph) = ctl;
}

/*!
    \brief      configure I2C POAP position
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  pos:
                only one parameter can be selected which is shown as below:
      \arg        I2C_ACKPOS_CURRENT: whether to send ACK or not for the current
      \arg        I2C_ACKPOS_NEXT: whether to send ACK or not for the next byte
    \param[out] none
    \retval     none
*/
void i2c_ackpos_config(uint32_t i2c_periph, uint32_t pos)
{
    uint32_t ctl = 0U;
    /* configure I2C POAP position */
    ctl = I2C_CTL0(i2c_periph);
    ctl &= ~(I2C_CTL0_POAP);
    ctl |= pos;
    I2C_CTL0(i2c_periph) = ctl;
}

/*!
    \brief      master sends slave address
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  addr: slave address
    \param[in]  trandirection: transmitter or receiver
                only one parameter can be selected which is shown as below:
      \arg        I2C_TRANSMITTER: transmitter
      \arg        I2C_RECEIVER: receiver
    \param[out] none
    \retval     none
*/
void i2c_master_addressing(uint32_t i2c_periph, uint32_t addr, uint32_t trandirection)
{
    /* master is a transmitter or a receiver */
    if(I2C_TRANSMITTER == trandirection)
    {
        addr = addr & I2C_TRANSMITTER;
    } else {
        addr = addr | I2C_RECEIVER;
    }
    /* send slave address */
    I2C_DATA(i2c_periph) = addr;
}

/*!
    \brief      enable dual-address mode
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  addr: the second address in dual-address mode
    \param[out] none
    \retval     none
*/
void i2c_dualaddr_enable(uint32_t i2c_periph, uint32_t addr)
{
    /* configure address */
    addr = addr & I2C_ADDRESS2_MASK;
    I2C_SADDR1(i2c_periph) = (I2C_SADDR1_DUADEN | addr);
}

/*!
    \brief      disable dual-address mode
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[out] none
    \retval     none
*/
void i2c_dualaddr_disable(uint32_t i2c_periph)
{
    I2C_SADDR1(i2c_periph) &= ~(I2C_SADDR1_DUADEN);
}

/*!
    \brief      configure I2C DMA mode
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  dmastate:
                only one parameter can be selected which is shown as below:
      \arg        I2C_DMA_ON: enable DMA mode
      \arg        I2C_DMA_OFF: disable DMA mode
    \param[out] none
    \retval     none
*/
void i2c_dma_config(uint32_t i2c_periph, uint32_t dmastate)
{
    /* configure I2C DMA function */
    uint32_t ctl = 0U;

    ctl = I2C_CTL1(i2c_periph);
    ctl &= ~(I2C_CTL1_DMAON);
    ctl |= dmastate;
    I2C_CTL1(i2c_periph) = ctl;
}

/*!
    \brief      configure whether next DMA EOT is DMA last transfer or not
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  dmalast:
                only one parameter can be selected which is shown as below:
      \arg        I2C_DMALST_ON: next DMA EOT is the last transfer
      \arg        I2C_DMALST_OFF: next DMA EOT is not the last transfer
    \param[out] none
    \retval     none
*/
void i2c_dma_last_transfer_config(uint32_t i2c_periph, uint32_t dmalast)
{
    /* configure DMA last transfer */
    uint32_t ctl = 0U;

    ctl = I2C_CTL1(i2c_periph);
    ctl &= ~(I2C_CTL1_DMALST);
    ctl |= dmalast;
    I2C_CTL1(i2c_periph) = ctl;
}

/*!
    \brief      configure software reset I2C
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  sreset:
                only one parameter can be selected which is shown as below:
      \arg        I2C_SRESET_SET: I2C is under reset
      \arg        I2C_SRESET_RESET: I2C is not under reset
    \param[out] none
    \retval     none
*/
void i2c_software_reset_config(uint32_t i2c_periph, uint32_t sreset)
{
    /* modify CTL0 and configure software reset I2C state */
    uint32_t ctl = 0U;

    ctl = I2C_CTL0(i2c_periph);
    ctl &= ~(I2C_CTL0_SRESET);
    ctl |= sreset;
    I2C_CTL0(i2c_periph) = ctl;
}

/*!
    \brief      configure I2C alert through SMBA pin
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  smbuspara:
                only one parameter can be selected which is shown as below:
      \arg        I2C_SALTSEND_ENABLE: issue alert through SMBA pin
      \arg        I2C_SALTSEND_DISABLE: not issue alert through SMBA pin
    \param[out] none
    \retval     none
*/
void i2c_smbus_alert_config(uint32_t i2c_periph, uint32_t smbuspara)
{
    /* configure smubus alert through SMBA pin */
    uint32_t ctl = 0U;

    ctl = I2C_CTL0(i2c_periph);
    ctl &= ~(I2C_CTL0_SALT);
    ctl |= smbuspara;
    I2C_CTL0(i2c_periph) = ctl;
}

/*!
    \brief      configure I2C ARP protocol in SMBus
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  arpstate:
                only one parameter can be selected which is shown as below:
      \arg        I2C_ARP_ENABLE: enable ARP
      \arg        I2C_ARP_DISABLE: disable ARP
    \param[out] none
    \retval     none
*/
void i2c_smbus_arp_config(uint32_t i2c_periph, uint32_t arpstate)
{
    /* enable or disable I2C ARP protocol*/
    uint32_t ctl = 0U;

    ctl = I2C_CTL0(i2c_periph);
    ctl &= ~(I2C_CTL0_ARPEN);
    ctl |= arpstate;
    I2C_CTL0(i2c_periph) = ctl;
}

/*!
    \brief      enable SAM_V interface
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[out] none
    \retval     none
*/
void i2c_sam_enable(uint32_t i2c_periph)
{
    I2C_SAMCS(i2c_periph) |= I2C_SAMCS_SAMEN;
}

/*!
    \brief      disable SAM_V interface
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[out] none
    \retval     none
*/
void i2c_sam_disable(uint32_t i2c_periph)
{
    I2C_SAMCS(i2c_periph) &= ~(I2C_SAMCS_SAMEN);
}

/*!
    \brief      enable SAM_V interface timeout detect
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[out] none
    \retval     none
*/
void i2c_sam_timeout_enable(uint32_t i2c_periph)
{
    I2C_SAMCS(i2c_periph) |= I2C_SAMCS_STOEN;
}

/*!
    \brief      disable SAM_V interface timeout detect
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[out] none
    \retval     none
*/
void i2c_sam_timeout_disable(uint32_t i2c_periph)
{
    I2C_SAMCS(i2c_periph) &= ~(I2C_SAMCS_STOEN);
}

/*!
    \brief      configure I2C start early termination mode
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  mode:
                only one parameter can be selected which is shown as below:
                STANDARD_I2C_PROTOCOL_MODE: do as the standard i2c protocol
                ARBITRATION_LOST_MODE: do the same thing as arbitration lost
    \param[out] none
    \retval     none
*/
void i2c_start_early_termination_mode_config(uint32_t i2c_periph, uint32_t mode)
{
    I2C_CTL2(i2c_periph) &= ~(I2C_CTL2_SETM);
    I2C_CTL2(i2c_periph) |= mode;
}

/*!
    \brief      enable I2C timeout calculation
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[out] none
    \retval     none
*/
void i2c_timeout_calculation_enable(uint32_t i2c_periph)
{
    I2C_CTL2(i2c_periph) |= I2C_CTL2_TOEN;
}

/*!
    \brief      disable I2C timeout calculation
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[out] none
    \retval     none
*/
void i2c_timeout_calculation_disable(uint32_t i2c_periph)
{
    I2C_CTL2(i2c_periph) &= ~(I2C_CTL2_TOEN);
}

/*!
    \brief      enable I2C record the received slave address to the transfer buffer register
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[out] none
    \retval     none
*/
void i2c_record_received_slave_address_enable(uint32_t i2c_periph)
{
    I2C_CTL2(i2c_periph) |= I2C_CTL2_RADD;
}

/*!
    \brief      disable I2C record the received slave address to the transfer buffer register
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[out] none
    \retval     none
*/
void i2c_record_received_slave_address_disable(uint32_t i2c_periph)
{
    I2C_CTL2(i2c_periph) &= ~(I2C_CTL2_RADD);
}

/*!
    \brief      define which bits of ADDRESS[7:1] need to compare with the incoming address byte
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  compare_bits: the bits need to compare
                one or more parameters can be selected which are shown as below:
                ADDRESS_BIT1_COMPARE: address bit1 needs compare
                ADDRESS_BIT2_COMPARE: address bit2 needs compare
                ADDRESS_BIT3_COMPARE: address bit3 needs compare
                ADDRESS_BIT4_COMPARE: address bit4 needs compare
                ADDRESS_BIT5_COMPARE: address bit5 needs compare
                ADDRESS_BIT6_COMPARE: address bit6 needs compare
                ADDRESS_BIT7_COMPARE: address bit7 needs compare
    \param[out] none
    \retval     none
*/
void i2c_address_bit_compare_config(uint32_t i2c_periph, uint16_t compare_bits)
{
    I2C_CTL2(i2c_periph) &= ~(I2C_CTL2_ADDM);
    I2C_CTL2(i2c_periph) |= (uint32_t)compare_bits;
}

/*!
    \brief      enable I2C status register clear
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[out] none
    \retval     none
*/
void i2c_status_clear_enable(uint32_t i2c_periph)
{
    I2C_STATC(i2c_periph) |= I2C_STATC_SRCEN;
}

/*!
    \brief      disable I2C status register clear
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[out] none
    \retval     none
*/
void i2c_status_clear_disable(uint32_t i2c_periph)
{
    I2C_STATC(i2c_periph) &= ~(I2C_STATC_SRCEN);
}

/*!
    \brief      clear I2C status in I2C_STAT0 register
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  clear_bit: which bit needs to clear
                one or more parameters can be selected which are shown as below:
                CLEAR_STPDET: clear STPDET bit in I2C_STAT0
                CLEAR_ADD10SEND: clear ADD10SEND bit in I2C_STAT0
                CLEAR_BTC: clear BTC bit in I2C_STAT0
                CLEAR_ADDSEND: clear ADDSEND bit in I2C_STAT0
                CLEAR_SBSEND: clear SBSEND bit in I2C_STAT0
    \param[out] none
    \retval     none
*/
void i2c_status_bit_clear(uint32_t i2c_periph, uint32_t clear_bit)
{
    I2C_STATC(i2c_periph) |= clear_bit;
}

/*!
    \brief      get I2C flag status
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  flag: I2C flags, refer to i2c_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        I2C_FLAG_SBSEND: start condition send out
      \arg        I2C_FLAG_ADDSEND: address is sent in master mode or received and matches in slave mode
      \arg        I2C_FLAG_BTC: byte transmission finishes
      \arg        I2C_FLAG_ADD10SEND: header of 10-bit address is sent in master mode
      \arg        I2C_FLAG_STPDET: stop condition detected in slave mode
      \arg        I2C_FLAG_RBNE: I2C_DATA is not Empty during receiving
      \arg        I2C_FLAG_TBE: I2C_DATA is empty during transmitting
      \arg        I2C_FLAG_BERR: a bus error occurs indication a unexpected start or stop condition on I2C bus
      \arg        I2C_FLAG_LOSTARB: arbitration lost in master mode
      \arg        I2C_FLAG_AERR: acknowledge error
      \arg        I2C_FLAG_OUERR: overrun or underrun situation occurs in slave mode
      \arg        I2C_FLAG_PECERR: PEC error when receiving data
      \arg        I2C_FLAG_SMBTO: timeout signal in SMBus mode
      \arg        I2C_FLAG_SMBALT: SMBus alert status
      \arg        I2C_FLAG_MASTER: a flag indicating whether I2C block is in master or slave mode
      \arg        I2C_FLAG_I2CBSY: busy flag
      \arg        I2C_FLAG_TR: whether the I2C is a transmitter or a receiver
      \arg        I2C_FLAG_RXGC: general call address (00h) received
      \arg        I2C_FLAG_DEFSMB: default address of SMBus device
      \arg        I2C_FLAG_HSTSMB: SMBus host header detected in slave mode
      \arg        I2C_FLAG_DUMOD: dual flag in slave mode indicating which address is matched in dual-address mode
      \arg        I2C_FLAG_TFF: txframe fall flag
      \arg        I2C_FLAG_TFR: txframe rise flag
      \arg        I2C_FLAG_RFF: rxframe fall flag
      \arg        I2C_FLAG_RFR: rxframe rise flag
      \arg        I2C_FLAG_STLO: start lost flag
      \arg        I2C_FLAG_STPSEND: stop condition sent flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus i2c_flag_get(uint32_t i2c_periph, i2c_flag_enum flag)
{
    if(RESET != (I2C_REG_VAL(i2c_periph, flag) & BIT(I2C_BIT_POS(flag))))
    {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear I2C flag status
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  flag: I2C flags, refer to i2c_flag_enum
                only one parameter can be selected which is shown as below:
      \arg       I2C_FLAG_SMBALT: SMBus Alert status
      \arg       I2C_FLAG_SMBTO: timeout signal in SMBus mode
      \arg       I2C_FLAG_PECERR: PEC error when receiving data
      \arg       I2C_FLAG_OUERR: over-run or under-run situation occurs in slave mode
      \arg       I2C_FLAG_AERR: acknowledge error
      \arg       I2C_FLAG_LOSTARB: arbitration lost in master mode
      \arg       I2C_FLAG_BERR: a bus error
      \arg       I2C_FLAG_ADDSEND: address is sent in master mode or received and matches in slave mode flag
      \arg       I2C_FLAG_TFF: txframe fall flag
      \arg       I2C_FLAG_TFR: txframe rise flag
      \arg       I2C_FLAG_RFF: rxframe fall flag
      \arg       I2C_FLAG_RFR: rxframe rise flag
      \arg       I2C_FLAG_STLO: start lost flag
      \arg       I2C_FLAG_STPSEND: stop condition sent flag
    \param[out] none
    \retval     none
*/
void i2c_flag_clear(uint32_t i2c_periph, i2c_flag_enum flag)
{
    if(I2C_FLAG_ADDSEND == flag)
    {
        /* read I2C_STAT0 and then read I2C_STAT1 to clear ADDSEND */
        I2C_STAT0(i2c_periph);
        I2C_STAT1(i2c_periph);
    } else {
        I2C_REG_VAL(i2c_periph, flag) &= ~BIT(I2C_BIT_POS(flag));
    }
}

/*!
    \brief      enable I2C interrupt
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  interrupt: I2C interrupts, refer to i2c_interrupt_enum
                only one parameter can be selected which is shown as below:
      \arg        I2C_INT_ERR: error interrupt enable
      \arg        I2C_INT_EV: event interrupt enable
      \arg        I2C_INT_BUF: buffer interrupt enable
      \arg        I2C_INT_TFF: txframe fall interrupt enable
      \arg        I2C_INT_TFR: txframe rise interrupt enable
      \arg        I2C_INT_RFF: rxframe fall interrupt enable
      \arg        I2C_INT_RFR: rxframe rise interrupt enable
      \arg        I2C_INT_STLO: start lost interrupt enable
      \arg        I2C_INT_STPSEND: stop condition sent interrupt enable
    \param[out] none
    \retval     none
*/
void i2c_interrupt_enable(uint32_t i2c_periph, i2c_interrupt_enum interrupt)
{
    I2C_REG_VAL(i2c_periph, interrupt) |= BIT(I2C_BIT_POS(interrupt));
}

/*!
    \brief      disable I2C interrupt
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  interrupt: I2C interrupts, refer to i2c_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        I2C_INT_ERR: error interrupt enable
      \arg        I2C_INT_EV: event interrupt enable
      \arg        I2C_INT_BUF: buffer interrupt enable
      \arg        I2C_INT_TFF: txframe fall interrupt enable
      \arg        I2C_INT_TFR: txframe rise interrupt enable
      \arg        I2C_INT_RFF: rxframe fall interrupt enable
      \arg        I2C_INT_RFR: rxframe rise interrupt enable
      \arg        I2C_INT_STLO: start lost interrupt enable
      \arg        I2C_INT_STPSEND: stop condition sent interrupt enable
    \param[out] none
    \retval     none
*/
void i2c_interrupt_disable(uint32_t i2c_periph, i2c_interrupt_enum interrupt)
{
    I2C_REG_VAL(i2c_periph, interrupt) &= ~BIT(I2C_BIT_POS(interrupt));
}

/*!
    \brief      get I2C interrupt flag status
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  int_flag: I2C interrupt flags, refer to i2c_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        I2C_INT_FLAG_SBSEND: start condition sent out in master mode interrupt flag
      \arg        I2C_INT_FLAG_ADDSEND: address is sent in master mode or received and matches in slave mode interrupt flag
      \arg        I2C_INT_FLAG_BTC: byte transmission finishes
      \arg        I2C_INT_FLAG_ADD10SEND: header of 10-bit address is sent in master mode interrupt flag
      \arg        I2C_INT_FLAG_STPDET: etop condition detected in slave mode interrupt flag
      \arg        I2C_INT_FLAG_RBNE: I2C_DATA is not Empty during receiving interrupt flag
      \arg        I2C_INT_FLAG_TBE: I2C_DATA is empty during transmitting interrupt flag
      \arg        I2C_INT_FLAG_BERR: a bus error occurs indication a unexpected start or stop condition on I2C bus interrupt flag
      \arg        I2C_INT_FLAG_LOSTARB: arbitration lost in master mode interrupt flag
      \arg        I2C_INT_FLAG_AERR: acknowledge error interrupt flag
      \arg        I2C_INT_FLAG_OUERR: over-run or under-run situation occurs in slave mode interrupt flag
      \arg        I2C_INT_FLAG_PECERR: PEC error when receiving data interrupt flag
      \arg        I2C_INT_FLAG_SMBTO: timeout signal in SMBus mode interrupt flag
      \arg        I2C_INT_FLAG_SMBALT: SMBus Alert status interrupt flag
      \arg        I2C_INT_FLAG_TFF: txframe fall interrupt flag
      \arg        I2C_INT_FLAG_TFR: txframe rise interrupt flag
      \arg        I2C_INT_FLAG_RFF: rxframe fall interrupt flag
      \arg        I2C_INT_FLAG_RFR: rxframe rise interrupt flag
      \arg        I2C_INT_FLAG_STLO: start lost interrupt flag
      \arg        I2C_INT_FLAG_STPSEND: stop condition sent interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus i2c_interrupt_flag_get(uint32_t i2c_periph, i2c_interrupt_flag_enum int_flag)
{
    uint32_t intenable = 0U, flagstatus = 0U, bufie;

    /* check BUFIE */
    bufie = I2C_CTL1(i2c_periph)&I2C_CTL1_BUFIE;

    /* get the interrupt enable bit status */
    intenable = (I2C_REG_VAL(i2c_periph, int_flag) & BIT(I2C_BIT_POS(int_flag)));
    /* get the corresponding flag bit status */
    flagstatus = (I2C_REG_VAL2(i2c_periph, int_flag) & BIT(I2C_BIT_POS2(int_flag)));

    if((I2C_INT_FLAG_RBNE == int_flag) || (I2C_INT_FLAG_TBE == int_flag))
    {
        if(intenable && bufie)
        {
            intenable = 1U;
        } else {
            intenable = 0U;
        }
    }
    if((0U != flagstatus) && (0U != intenable))
    {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear I2C interrupt flag status
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  int_flag: I2C interrupt flags, refer to i2c_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        I2C_INT_FLAG_ADDSEND: address is sent in master mode or received and matches in slave mode interrupt flag
      \arg        I2C_INT_FLAG_BERR: a bus error occurs indication a unexpected start or stop condition on I2C bus interrupt flag
      \arg        I2C_INT_FLAG_LOSTARB: arbitration lost in master mode interrupt flag
      \arg        I2C_INT_FLAG_AERR: acknowledge error interrupt flag
      \arg        I2C_INT_FLAG_OUERR: over-run or under-run situation occurs in slave mode interrupt flag
      \arg        I2C_INT_FLAG_PECERR: PEC error when receiving data interrupt flag
      \arg        I2C_INT_FLAG_SMBTO: timeout signal in SMBus mode interrupt flag
      \arg        I2C_INT_FLAG_SMBALT: SMBus Alert status interrupt flag
      \arg        I2C_INT_FLAG_TFF: txframe fall interrupt flag
      \arg        I2C_INT_FLAG_TFR: txframe rise interrupt flag
      \arg        I2C_INT_FLAG_RFF: rxframe fall interrupt flag
      \arg        I2C_INT_FLAG_RFR: rxframe rise interrupt flag
      \arg        I2C_INT_FLAG_STLO: start lost interrupt flag
      \arg        I2C_INT_FLAG_STPSEND: stop condition sent interrupt flag
    \param[out] none
    \retval     none
*/
void i2c_interrupt_flag_clear(uint32_t i2c_periph, i2c_interrupt_flag_enum int_flag)
{
    if(I2C_INT_FLAG_ADDSEND == int_flag)
    {
        /* read I2C_STAT0 and then read I2C_STAT1 to clear ADDSEND */
        I2C_STAT0(i2c_periph);
        I2C_STAT1(i2c_periph);
    } else {
        I2C_REG_VAL2(i2c_periph, int_flag) &= ~BIT(I2C_BIT_POS2(int_flag));
    }
}

/*!
    \brief      configure the timing parameters
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[in]  psc: 0-0x0000000F, timing prescaler
    \param[in]  scl_dely: 0-0x0000000F, data setup time
    \param[in]  sda_dely: 0-0x0000000F, data hold time
    \param[out] none
    \retval     none
*/
void i2c_timing_config(uint32_t i2c_periph, uint32_t psc, uint32_t scl_dely, uint32_t sda_dely)
{
    /* clear PSC, SCLDELY, SDADELY bits in I2C2_TIMING register */
    I2C2_TIMING(i2c_periph) &= ~I2C2_TIMING_PSC;
    I2C2_TIMING(i2c_periph) &= ~I2C2_TIMING_SCLDELY;
    I2C2_TIMING(i2c_periph) &= ~I2C2_TIMING_SDADELY;
    /* mask PSC, SCLDELY, SDADELY bits in I2C2_TIMING register */
    psc = (uint32_t)(psc << TIMING_PSC_OFFSET) & I2C2_TIMING_PSC;
    scl_dely = (uint32_t)(scl_dely << TIMING_SCLDELY_OFFSET) & I2C2_TIMING_SCLDELY;
    sda_dely = (uint32_t)(sda_dely << TIMING_SDADELY_OFFSET) & I2C2_TIMING_SDADELY;
    /* write PSC, SCLDELY, SDADELY bits in I2C2_TIMING register */
    I2C2_TIMING(i2c_periph) |= (psc | scl_dely | sda_dely);
}

/*!
    \brief      configure digital noise filter
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[in]  filter_length: the length of filter spikes
                only one parameter can be selected which is shown as below:
      \arg        FILTER_DISABLE: digital filter is disabled
      \arg        FILTER_LENGTH_1: digital filter is enabled and filter spikes with a length of up to 1 tI2CCLK
      \arg        FILTER_LENGTH_2: digital filter is enabled and filter spikes with a length of up to 2 tI2CCLK
      \arg        FILTER_LENGTH_3: digital filter is enabled and filter spikes with a length of up to 3 tI2CCLK
      \arg        FILTER_LENGTH_4: digital filter is enabled and filter spikes with a length of up to 4 tI2CCLK
      \arg        FILTER_LENGTH_5: digital filter is enabled and filter spikes with a length of up to 5 tI2CCLK
      \arg        FILTER_LENGTH_6: digital filter is enabled and filter spikes with a length of up to 6 tI2CCLK
      \arg        FILTER_LENGTH_7: digital filter is enabled and filter spikes with a length of up to 7 tI2CCLK
      \arg        FILTER_LENGTH_8: digital filter is enabled and filter spikes with a length of up to 8 tI2CCLK
      \arg        FILTER_LENGTH_9: digital filter is enabled and filter spikes with a length of up to 9 tI2CCLK
      \arg        FILTER_LENGTH_10: digital filter is enabled and filter spikes with a length of up to 10 tI2CCLK
      \arg        FILTER_LENGTH_11: digital filter is enabled and filter spikes with a length of up to 11 tI2CCLK
      \arg        FILTER_LENGTH_12: digital filter is enabled and filter spikes with a length of up to 12 tI2CCLK
      \arg        FILTER_LENGTH_13: digital filter is enabled and filter spikes with a length of up to 13 tI2CCLK
      \arg        FILTER_LENGTH_14: digital filter is enabled and filter spikes with a length of up to 14 tI2CCLK
      \arg        FILTER_LENGTH_15: digital filter is enabled and filter spikes with a length of up to 15 tI2CCLK
    \param[out] none
    \retval     none
*/
void i2c_digital_noise_filter_config(uint32_t i2c_periph, uint32_t filter_length)
{
    I2C2_CTL0(i2c_periph) &= (uint32_t)(~I2C2_CTL0_DNF);
    I2C2_CTL0(i2c_periph) |= (uint32_t)(filter_length << CTL0_DNF_OFFSET);
}

/*!
    \brief      enable analog noise filter
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_analog_noise_filter_enable(uint32_t i2c_periph)
{
    I2C2_CTL0(i2c_periph) &= ~I2C2_CTL0_ANOFF;
}

/*!
    \brief      disable analog noise filter
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_analog_noise_filter_disable(uint32_t i2c_periph)
{
    I2C2_CTL0(i2c_periph) |= I2C2_CTL0_ANOFF;
}

/*!
    \brief      enable wakeup from deep-sleep mode
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_wakeup_from_deepsleep_enable(uint32_t i2c_periph)
{
    I2C2_CTL0(i2c_periph) |= I2C2_CTL0_WUEN;
}

/*!
    \brief      disable wakeup from deep-sleep mode
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_wakeup_from_deepsleep_disable(uint32_t i2c_periph)
{
    I2C2_CTL0(i2c_periph) &= ~I2C2_CTL0_WUEN;
}

/*!
    \brief      configure the SCL high and low period of clock in master mode
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[in]  sclh: 0-0x000000FF, SCL high period
    \param[in]  scll: 0-0x000000FF, SCL low period
    \param[out] none
    \retval     none
*/
void i2c_master_clock_config(uint32_t i2c_periph, uint32_t sclh, uint32_t scll)
{
    /* clear SCLH, SCLL bits in I2C2_TIMING register */
    I2C2_TIMING(i2c_periph) &= ~I2C2_TIMING_SCLH;
    I2C2_TIMING(i2c_periph) &= ~I2C2_TIMING_SCLL;
    /* mask SCLH, SCLL bits in I2C2_TIMING register */
    sclh = (uint32_t)(sclh << TIMING_SCLH_OFFSET) & I2C2_TIMING_SCLH;
    scll = (uint32_t)(scll << TIMING_SCLL_OFFSET) & I2C2_TIMING_SCLL;
    /* write SCLH, SCLL bits in I2C2_TIMING register */
    I2C2_TIMING(i2c_periph) |= (sclh | scll);
}

/*!
    \brief      configure I2C slave address and transfer direction in master mode
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[in]  address: 0-0x3FF except reserved address, I2C slave address to be sent
    \param[in]  trans_direction: I2C transfer direction in master mode
                only one parameter can be selected which is shown as below:
      \arg        I2C2_MASTER_TRANSMIT: master transmit
      \arg        I2C2_MASTER_RECEIVE: master receive
    \param[out] none
    \retval     none
*/
void i2c2_master_addressing(uint32_t i2c_periph, uint32_t address, uint32_t trans_direction)
{
    /* configure slave address */
    I2C2_CTL1(i2c_periph) &= ~I2C2_CTL1_SADDRESS;
    I2C2_CTL1(i2c_periph) |= address;
    /* configure transfer direction */
    I2C2_CTL1(i2c_periph) &= ~I2C2_CTL1_TRDIR;
    I2C2_CTL1(i2c_periph) |= trans_direction;
}

/*!
    \brief      10-bit address header executes read direction only in master receive mode
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_address10_header_enable(uint32_t i2c_periph)
{
    I2C2_CTL1(i2c_periph) |= I2C2_CTL1_HEAD10R;
}

/*!
    \brief      10-bit address header executes complete sequence in master receive mode
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_address10_header_disable(uint32_t i2c_periph)
{
    I2C2_CTL1(i2c_periph) &= ~I2C2_CTL1_HEAD10R;
}

/*!
    \brief      enable 10-bit addressing mode in master mode
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_address10_enable(uint32_t i2c_periph)
{
    I2C2_CTL1(i2c_periph) |= I2C2_CTL1_ADD10EN;
}

/*!
    \brief      disable 10-bit addressing mode in master mode
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_address10_disable(uint32_t i2c_periph)
{
    I2C2_CTL1(i2c_periph) &= ~I2C2_CTL1_ADD10EN;
}

/*!
    \brief      enable I2C automatic end mode in master mode
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_automatic_end_enable(uint32_t i2c_periph)
{
    I2C2_CTL1(i2c_periph) |= I2C2_CTL1_AUTOEND;
}

/*!
    \brief      disable I2C automatic end mode in master mode
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_automatic_end_disable(uint32_t i2c_periph)
{
    I2C2_CTL1(i2c_periph) &= ~I2C2_CTL1_AUTOEND;
}

/*!
    \brief      configure I2C slave address
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[in]  address: I2C address
    \param[in]  addr_format: 7bits or 10bits
                only one parameter can be selected which is shown as below:
      \arg        I2C2_ADDFORMAT_7BITS: 7bits
      \arg        I2C2_ADDFORMAT_10BITS: 10bits
    \param[out] none
    \retval     none
*/
void i2c_address_config(uint32_t i2c_periph, uint32_t address, uint32_t addr_format)
{
    /* configure ADDRESS[7:1] and address format */
    address = address & I2C_ADDRESS_MASK;
    I2C2_SADDR0(i2c_periph) = (addr_format | address);
    /* enable i2c address in slave mode */
    I2C2_SADDR0(i2c_periph) |= I2C2_SADDR0_ADDRESSEN;
}

/*!
    \brief      disable I2C address in slave mode
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_address_disable(uint32_t i2c_periph)
{
    I2C2_SADDR0(i2c_periph) &= ~I2C2_SADDR0_ADDRESSEN;
}

/*!
    \brief      configure I2C second slave address
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[in]  address: I2C address
    \param[in]  addr_mask: the bits not need to compare
                one or more parameters can be selected which are shown as below:
      \arg        ADDRESS2_NO_MASK: no mask, all the bits must be compared
      \arg        ADDRESS2_MASK_BIT1: ADDRESS2[1] is masked, only ADDRESS2[7:2] are compared
      \arg        ADDRESS2_MASK_BIT1_2: ADDRESS2[2:1] is masked, only ADDRESS2[7:3] are compared
      \arg        ADDRESS2_MASK_BIT1_3: ADDRESS2[3:1] is masked, only ADDRESS2[7:4] are compared
      \arg        ADDRESS2_MASK_BIT1_4: ADDRESS2[4:1] is masked, only ADDRESS2[7:5] are compared
      \arg        ADDRESS2_MASK_BIT1_5: ADDRESS2[5:1] is masked, only ADDRESS2[7:6] are compared
      \arg        ADDRESS2_MASK_BIT1_6: ADDRESS2[6:1] is masked, only ADDRESS2[7] are compared
      \arg        ADDRESS2_MASK_ALL: all the ADDRESS2[7:1] bits are masked
    \param[out] none
    \retval     none
*/
void i2c_second_address_config(uint32_t i2c_periph, uint32_t address, uint32_t addr_mask)
{
    /* configure ADDRESS2[7:1] */
    address = address & I2C_ADDRESS2_MASK;
    I2C2_SADDR1(i2c_periph) |= address;
    /* configure ADDRESS2[7:1] mask */
    I2C2_SADDR1(i2c_periph) &= ~I2C2_SADDR1_ADDMSK2;
    I2C2_SADDR1(i2c_periph) |= (uint32_t)(addr_mask << SADDR1_ADDMSK_OFFSET);
    /* enable i2c second address in slave mode */
    I2C2_SADDR1(i2c_periph) |= I2C2_SADDR1_ADDRESS2EN;
}

/*!
    \brief      disable I2C second address in slave mode
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_second_address_disable(uint32_t i2c_periph)
{
    I2C2_SADDR1(i2c_periph) &= ~I2C2_SADDR1_ADDRESS2EN;
}

/*!
    \brief      get received match address in slave mode
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     received match address
*/
uint32_t i2c_recevied_address_get(uint32_t i2c_periph)
{
    return (uint32_t)((I2C2_STAT(i2c_periph) & I2C2_STAT_READDR) >> STAT_READDR_OFFSET);
}

/*!
    \brief      enable slave byte control
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_slave_byte_control_enable(uint32_t i2c_periph)
{
    I2C2_CTL0(i2c_periph) |= I2C2_CTL0_SBCTL;
}

/*!
    \brief      disable slave byte control
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_slave_byte_control_disable(uint32_t i2c_periph)
{
    I2C2_CTL0(i2c_periph) &= ~I2C2_CTL0_SBCTL;
}

/*!
    \brief      generate a NACK in slave mode
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_nack_enable(uint32_t i2c_periph)
{
    I2C2_CTL1(i2c_periph) |= I2C2_CTL1_NACKEN;
}

/*!
    \brief      generate an ACK in slave mode
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_nack_disable(uint32_t i2c_periph)
{
    I2C2_CTL1(i2c_periph) &= ~I2C2_CTL1_NACKEN;
}

/*!
    \brief      enable I2C reload mode
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_reload_enable(uint32_t i2c_periph)
{
    I2C2_CTL1(i2c_periph) |= I2C2_CTL1_RELOAD;
}

/*!
    \brief      disable I2C reload mode
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_reload_disable(uint32_t i2c_periph)
{
    I2C2_CTL1(i2c_periph) &= ~I2C2_CTL1_RELOAD;
}

/*!
    \brief      configure number of bytes to be transferred
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[in]  byte_number: 0x0-0xFF, number of bytes to be transferred
    \param[out] none
    \retval     none
*/
void i2c_transfer_byte_number_config(uint32_t i2c_periph, uint32_t byte_number)
{
    I2C2_CTL1(i2c_periph) &= (uint32_t)(~I2C2_CTL1_BYTENUM);
    I2C2_CTL1(i2c_periph) |= (uint32_t)(byte_number << CTL1_BYTENUM_OFFSET);
}

/*!
    \brief      enable I2C DMA for transmission or reception
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[in]  dma: I2C DMA
                only one parameter can be selected which is shown as below:
      \arg        I2C2_DMA_TRANSMIT: transmit data using DMA
      \arg        I2C2_DMA_RECEIVE: receive data using DMA
    \param[out] none
    \retval     none
*/
void i2c2_dma_enable(uint32_t i2c_periph, uint8_t dma)
{
    if(I2C2_DMA_TRANSMIT == dma)
    {
        I2C2_CTL0(i2c_periph) |= I2C2_CTL0_DENT;
    } else {
        I2C2_CTL0(i2c_periph) |= I2C2_CTL0_DENR;
    }
}

/*!
    \brief      disable I2C DMA for transmission or reception
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[in]  dma: I2C DMA
                only one parameter can be selected which is shown as below:
      \arg        I2C2_DMA_TRANSMIT: transmit data using DMA
      \arg        I2C2_DMA_RECEIVE: receive data using DMA
    \param[out] none
    \retval     none
*/
void i2c2_dma_disable(uint32_t i2c_periph, uint8_t dma)
{
    if(I2C2_DMA_TRANSMIT == dma)
    {
        I2C2_CTL0(i2c_periph) &= ~I2C2_CTL0_DENT;
    } else {
        I2C2_CTL0(i2c_periph) &= ~I2C2_CTL0_DENR;
    }
}

/*!
    \brief      enable SMBus alert
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_smbus_alert_enable(uint32_t i2c_periph)
{
    I2C2_CTL0(i2c_periph) |= I2C2_CTL0_SMBALTEN;
}

/*!
    \brief      disable SMBus alert
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_smbus_alert_disable(uint32_t i2c_periph)
{
    I2C2_CTL0(i2c_periph) &= ~I2C2_CTL0_SMBALTEN;
}

/*!
    \brief      enable SMBus device default address
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_smbus_default_addr_enable(uint32_t i2c_periph)
{
    I2C2_CTL0(i2c_periph) |= I2C2_CTL0_SMBDAEN;
}

/*!
    \brief      disable SMBus device default address
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_smbus_default_addr_disable(uint32_t i2c_periph)
{
    I2C2_CTL0(i2c_periph) &= ~I2C2_CTL0_SMBDAEN;
}

/*!
    \brief      enable SMBus host address
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_smbus_host_addr_enable(uint32_t i2c_periph)
{
    I2C2_CTL0(i2c_periph) |= I2C2_CTL0_SMBHAEN;
}

/*!
    \brief      disable SMBus host address
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_smbus_host_addr_disable(uint32_t i2c_periph)
{
    I2C2_CTL0(i2c_periph) &= ~I2C2_CTL0_SMBHAEN;
}

/*!
    \brief      enable extended clock timeout detection
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_extented_clock_timeout_enable(uint32_t i2c_periph)
{
    I2C2_TIMEOUT(i2c_periph) |= I2C2_TIMEOUT_EXTOEN;
}

/*!
    \brief      disable extended clock timeout detection
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_extented_clock_timeout_disable(uint32_t i2c_periph)
{
    I2C2_TIMEOUT(i2c_periph) &= ~I2C2_TIMEOUT_EXTOEN;
}

/*!
    \brief      enable clock timeout detection
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_clock_timeout_enable(uint32_t i2c_periph)
{
    I2C2_TIMEOUT(i2c_periph) |= I2C2_TIMEOUT_TOEN;
}

/*!
    \brief      disable clock timeout detection
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[out] none
    \retval     none
*/
void i2c_clock_timeout_disable(uint32_t i2c_periph)
{
    I2C2_TIMEOUT(i2c_periph) &= ~I2C2_TIMEOUT_TOEN;
}

/*!
    \brief      configure bus timeout B
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[in]  timeout: bus timeout B
    \param[out] none
    \retval     none
*/
void i2c_bus_timeout_b_config(uint32_t i2c_periph, uint32_t timeout)
{
    I2C2_TIMEOUT(i2c_periph) &= ~I2C2_TIMEOUT_BUSTOB;
    I2C2_TIMEOUT(i2c_periph) |= (uint32_t)(timeout << TIMEOUT_BUSTOB_OFFSET);
}

/*!
    \brief      configure bus timeout A
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[in]  timeout: bus timeout A
    \param[out] none
    \retval     none
*/
void i2c_bus_timeout_a_config(uint32_t i2c_periph, uint32_t timeout)
{
    I2C2_TIMEOUT(i2c_periph) &= ~I2C2_TIMEOUT_BUSTOA;
    I2C2_TIMEOUT(i2c_periph) |= timeout;
}

/*!
    \brief      configure idle clock timeout detection
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[in]  timeout: bus timeout A
      \arg        BUSTOA_DETECT_SCL_LOW: BUSTOA is used to detect SCL low timeout
      \arg        BUSTOA_DETECT_IDLE: BUSTOA is used to detect both SCL and SDA high timeout when the bus is idle
    \param[out] none
    \retval     none
*/
void i2c_idle_clock_timeout_config(uint32_t i2c_periph, uint32_t timeout)
{
    I2C2_TIMEOUT(i2c_periph) &= ~I2C2_TIMEOUT_TOIDLE;
    I2C2_TIMEOUT(i2c_periph) |= timeout;
}

/*!
    \brief      get I2C flag status
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[in]  flag: I2C flags
                only one parameter can be selected which is shown as below:
      \arg        I2C2_FLAG_TBE: I2C2_TDATA is empty during transmitting
      \arg        I2C2_FLAG_TI: transmit interrupt
      \arg        I2C2_FLAG_RBNE: I2C2_RDATA is not empty during receiving
      \arg        I2C2_FLAG_ADDSEND: address received matches in slave mode
      \arg        I2C2_FLAG_NACK: not acknowledge flag
      \arg        I2C2_FLAG_STPDET: STOP condition detected in slave mode
      \arg        I2C2_FLAG_TC: transfer complete in master mode
      \arg        I2C2_FLAG_TCR: transfer complete reload
      \arg        I2C2_FLAG_BERR: bus error
      \arg        I2C2_FLAG_LOSTARB: arbitration Lost
      \arg        I2C2_FLAG_OUERR: overrun/underrun error in slave mode
      \arg        I2C2_FLAG_PECERR: PEC error
      \arg        I2C2_FLAG_TIMEOUT: timeout flag
      \arg        I2C2_FLAG_SMBALT: SMBus Alert
      \arg        I2C2_FLAG_I2CBSY: busy flag
      \arg        I2C2_FLAG_TR: whether the I2C is a transmitter or a receiver in slave mode
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus i2c2_flag_get(uint32_t i2c_periph, uint32_t flag)
{
    if(RESET != (I2C2_STAT(i2c_periph) & flag))
    {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear I2C flag status
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[in]  flag: I2C flags
                one or more parameters can be selected which are shown as below:
      \arg        I2C2_FLAG_ADDSEND: address received matches in slave mode
      \arg        I2C2_FLAG_NACK: not acknowledge flag
      \arg        I2C2_FLAG_STPDET: STOP condition detected in slave mode
      \arg        I2C2_FLAG_BERR: bus error
      \arg        I2C2_FLAG_LOSTARB: arbitration Lost
      \arg        I2C2_FLAG_OUERR: overrun/underrun error in slave mode
      \arg        I2C2_FLAG_PECERR: PEC error
      \arg        I2C2_FLAG_TIMEOUT: timeout flag
      \arg        I2C2_FLAG_SMBALT: SMBus Alert
    \param[out] none
    \retval     none
*/
void i2c2_flag_clear(uint32_t i2c_periph, uint32_t flag)
{
    I2C2_STATC(i2c_periph) |= flag;
}

/*!
    \brief      enable I2C interrupt
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[in]  interrupt: I2C interrupts
                one or more parameters can be selected which are shown as below:
      \arg        I2C2_INT_ERR: error interrupt
      \arg        I2C2_INT_TC: transfer complete interrupt
      \arg        I2C2_INT_STPDET: stop detection interrupt
      \arg        I2C2_INT_NACK: not acknowledge received interrupt
      \arg        I2C2_INT_ADDM: address match interrupt
      \arg        I2C2_INT_RBNE: receive interrupt
      \arg        I2C2_INT_TI: transmit interrupt
    \param[out] none
    \retval     none
*/
void i2c2_interrupt_enable(uint32_t i2c_periph, uint32_t interrupt)
{
    I2C2_CTL0(i2c_periph) |= interrupt;
}

/*!
    \brief      disable I2C interrupt
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[in]  interrupt: I2C interrupts
                one or more parameters can be selected which are shown as below:
      \arg        I2C2_INT_ERR: error interrupt
      \arg        I2C2_INT_TC: transfer complete interrupt
      \arg        I2C2_INT_STPDET: stop detection interrupt
      \arg        I2C2_INT_NACK: not acknowledge received interrupt
      \arg        I2C2_INT_ADDM: address match interrupt
      \arg        I2C2_INT_RBNE: receive interrupt
      \arg        I2C2_INT_TI: transmit interrupt
    \param[out] none
    \retval     none
*/
void i2c2_interrupt_disable(uint32_t i2c_periph, uint32_t interrupt)
{
    I2C2_CTL0(i2c_periph) &= ~interrupt;
}

/*!
    \brief      get I2C interrupt flag status
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[in]  int_flag: I2C interrupt flags, refer to i2c2_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        I2C2_INT_FLAG_TI: transmit interrupt flag
      \arg        I2C2_INT_FLAG_RBNE: I2C2_RDATA is not empty during receiving interrupt flag
      \arg        I2C2_INT_FLAG_ADDSEND: address received matches in slave mode interrupt flag
      \arg        I2C2_INT_FLAG_NACK: not acknowledge interrupt flag
      \arg        I2C2_INT_FLAG_STPDET: stop condition detected in slave mode interrupt flag
      \arg        I2C2_INT_FLAG_TC: transfer complete in master mode interrupt flag
      \arg        I2C2_INT_FLAG_TCR: transfer complete reload interrupt flag
      \arg        I2C2_INT_FLAG_BERR: bus error interrupt flag
      \arg        I2C2_INT_FLAG_LOSTARB: arbitration lost interrupt flag
      \arg        I2C2_INT_FLAG_OUERR: overrun/underrun error in slave mode interrupt flag
      \arg        I2C2_INT_FLAG_PECERR: PEC error interrupt flag
      \arg        I2C2_INT_FLAG_TIMEOUT: timeout interrupt flag
      \arg        I2C2_INT_FLAG_SMBALT: SMBus Alert interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus i2c2_interrupt_flag_get(uint32_t i2c_periph, i2c2_interrupt_flag_enum int_flag)
{
    uint32_t ret1 = RESET;
    uint32_t ret2 = RESET;

    /* get the status of interrupt enable bit */
    ret1 = (I2C_REG_VAL(i2c_periph, int_flag) & BIT(I2C_BIT_POS(int_flag)));
    /* get the status of interrupt flag */
    ret2 = (I2C_REG_VAL2(i2c_periph, int_flag) & BIT(I2C_BIT_POS2(int_flag)));
    if(ret1 && ret2)
    {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear I2C interrupt flag status
    \param[in]  i2c_periph: I2Cx(x=2)
    \param[in]  int_flag: I2C interrupt flags, refer to i2c2_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        I2C2_INT_FLAG_ADDSEND: address received matches in slave mode interrupt flag
      \arg        I2C2_INT_FLAG_NACK: not acknowledge interrupt flag
      \arg        I2C2_INT_FLAG_STPDET: stop condition detected in slave mode interrupt flag
      \arg        I2C2_INT_FLAG_BERR: bus error interrupt flag
      \arg        I2C2_INT_FLAG_LOSTARB: arbitration lost interrupt flag
      \arg        I2C2_INT_FLAG_OUERR: overrun/underrun error in slave mode interrupt flag
      \arg        I2C2_INT_FLAG_PECERR: PEC error interrupt flag
      \arg        I2C2_INT_FLAG_TIMEOUT: timeout interrupt flag
      \arg        I2C2_INT_FLAG_SMBALT: SMBus Alert interrupt flag
    \param[out] none
    \retval     none
*/
void i2c2_interrupt_flag_clear(uint32_t i2c_periph, i2c2_interrupt_flag_enum int_flag)
{
    I2C2_STATC(i2c_periph) |= BIT(I2C_BIT_POS2(int_flag));
}
