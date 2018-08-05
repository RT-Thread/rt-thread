/*!
    \file  gd32f30x_i2c.c
    \brief I2C driver
*/

/*
    Copyright (C) 2017 GigaDevice

    2017-02-10, V1.0.1, firmware for GD32F30x
*/

#include "gd32f30x_i2c.h"

#define I2CCLK_MAX                    0x7fU              /*!< i2cclk max value */
#define I2C_FLAG_MASK                 0x0000FFFFU        /*!< i2c flag mask */

/*!
    \brief      reset I2C
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[out] none
    \retval     none
*/
void i2c_deinit(uint32_t i2c_periph)
{
    switch(i2c_periph){
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
    default:
        break;
    }
}

/*!
    \brief      configure I2C clock
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  clkspeed: I2C clock speed, supports standard mode (up to 100 kHz), fast mode (up to 400 kHz)
                          and fast mode plus (up to 1MHz)
    \param[in]  dutycyc: duty cycle in fast mode or fast mode plus
      \arg        I2C_DTCY_2: T_low/T_high=2 
      \arg        I2C_DTCY_16_9: T_low/T_high=16/9
    \param[out] none
    \retval     none
*/
void i2c_clock_config(uint32_t i2c_periph, uint32_t clkspeed, uint32_t dutycyc)
{
    uint32_t pclk1,clkc,freq,risetime;
    uint32_t temp;
    
    pclk1 = rcu_clock_freq_get(CK_APB1);
    /* I2C peripheral clock frequency */
    freq = (uint32_t)(pclk1/1000000U);
    if(freq >= I2CCLK_MAX){
        freq = I2CCLK_MAX;
    }
    temp = I2C_CTL1(i2c_periph);
    temp &= ~I2C_CTL1_I2CCLK;
    temp |= freq;
    
    I2C_CTL1(i2c_periph) = temp;
    
    if(100000U >= clkspeed){
        /* the maximum SCL rise time is 1000ns in standard mode */
        risetime = (uint32_t)((pclk1/1000000U)+1U);
        if(risetime >= I2CCLK_MAX){
            I2C_RT(i2c_periph) = I2CCLK_MAX;
        }else{
            I2C_RT(i2c_periph) = risetime;
        }
        clkc = (uint32_t)(pclk1/(clkspeed*2U)); 
        if(clkc < 0x04U){
            /* the CLKC in standard mode minmum value is 4 */
            clkc = 0x04U;
        }
        I2C_CKCFG(i2c_periph) |= (I2C_CKCFG_CLKC & clkc);

    }else if(400000U >= clkspeed){
        /* the maximum SCL rise time is 300ns in fast mode */
        I2C_RT(i2c_periph) = (uint32_t)(((freq*(uint32_t)300U)/(uint32_t)1000U)+(uint32_t)1U);
        if(I2C_DTCY_2 == dutycyc){
            /* I2C duty cycle is 2 */
            clkc = (uint32_t)(pclk1/(clkspeed*3U));
            I2C_CKCFG(i2c_periph) &= ~I2C_CKCFG_DTCY;
        }else{
            /* I2C duty cycle is 16/9 */
            clkc = (uint32_t)(pclk1/(clkspeed*25U));
            I2C_CKCFG(i2c_periph) |= I2C_CKCFG_DTCY;
        }
        if(0U == (clkc & I2C_CKCFG_CLKC)){
            /* the CLKC in fast mode minmum value is 1 */
            clkc |= 0x0001U;  
        }
        I2C_CKCFG(i2c_periph) |= I2C_CKCFG_FAST;
        I2C_CKCFG(i2c_periph) |= clkc;
    }else{
        /* fast mode plus, the maximum SCL rise time is 120ns */
        I2C_RT(i2c_periph) = (uint32_t)(((freq*(uint32_t)120U)/(uint32_t)1000U)+(uint32_t)1U);
        if(I2C_DTCY_2 == dutycyc){
            /* I2C duty cycle is 2 */
            clkc = (uint32_t)(pclk1/(clkspeed*3U));	
            I2C_CKCFG(i2c_periph) &= ~I2C_CKCFG_DTCY;
        }else{
            /* I2C duty cycle is 16/9 */
            clkc = (uint32_t)(pclk1/(clkspeed*25U));
            I2C_CKCFG(i2c_periph) |= I2C_CKCFG_DTCY;
        }
        /* enable fast mode */
        I2C_CKCFG(i2c_periph) |= I2C_CKCFG_FAST;
        I2C_CKCFG(i2c_periph) |= clkc;
        /* enable I2C fast mode plus */
        I2C_FMPCFG(i2c_periph) = I2C_FMPCFG_FMPEN;
    }
}

/*!
    \brief      configure I2C address 
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  mode:
      \arg        I2C_I2CMODE_ENABLE: I2C mode
      \arg        I2C_SMBUSMODE_ENABLE: SMBus mode
    \param[in]  addformat: 7bits or 10bits
      \arg        I2C_ADDFORMAT_7BITS: 7bits
      \arg        I2C_ADDFORMAT_10BITS: 10bits
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
    I2C_SADDR0(i2c_periph) = (addformat | addr);
}

/*!
    \brief      SMBus type selection
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  ack:
      \arg        I2C_SMBUS_DEVICE: device
      \arg        I2C_SMBUS_HOST: host
    \param[out] none
    \retval     none
*/
void i2c_smbus_type_config(uint32_t i2c_periph, uint32_t type)
{
    if(I2C_SMBUS_HOST == type){
        I2C_CTL0(i2c_periph) |= I2C_CTL0_SMBSEL;
    }else{
        I2C_CTL0(i2c_periph) &= ~(I2C_CTL0_SMBSEL);
    }
}

/*!
    \brief      whether or not to send an ACK
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  ack:
      \arg        I2C_ACK_ENABLE: ACK will be sent
      \arg        I2C_ACK_DISABLE: ACK will not be sent
    \param[out] none
    \retval     none
*/
void i2c_ack_config(uint32_t i2c_periph, uint32_t ack)
{
    if(I2C_ACK_ENABLE == ack){
        I2C_CTL0(i2c_periph) |= I2C_CTL0_ACKEN;
    }else{
        I2C_CTL0(i2c_periph) &= ~(I2C_CTL0_ACKEN);
    }
}

/*!
    \brief      I2C POAP position configure
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  pos:
      \arg        I2C_ACKPOS_CURRENT: whether to send ACK or not for the current
      \arg        I2C_ACKPOS_NEXT: whether to send ACK or not for the next byte
    \param[out] none
    \retval     none
*/
void i2c_ackpos_config(uint32_t i2c_periph, uint32_t pos)
{
    /* configure I2C POAP position */
    if(I2C_ACKPOS_NEXT == pos){
        I2C_CTL0(i2c_periph) |= I2C_CTL0_POAP;
    }else{
        I2C_CTL0(i2c_periph) &= ~(I2C_CTL0_POAP);
    }
}

/*!
    \brief      master send slave address
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  addr: slave address  
    \param[in]  trandirection: transmitter or receiver
      \arg        I2C_TRANSMITTER: transmitter  
      \arg        I2C_RECEIVER:    receiver  
    \param[out] none
    \retval     none
*/
void i2c_master_addressing(uint32_t i2c_periph, uint32_t addr, uint32_t trandirection)
{
    if(I2C_TRANSMITTER == trandirection){
        addr = addr & I2C_TRANSMITTER;
    }else{
        addr = addr | I2C_RECEIVER;
    }
    I2C_DATA(i2c_periph) = addr;
}

/*!
    \brief      dual-address mode switch
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  dualaddr:
      \arg        I2C_DUADEN_DISABLE: disable dual-address mode  
      \arg        I2C_DUADEN_ENABLE: enable dual-address mode
    \param[out] none
    \retval     none
*/
void i2c_dualaddr_enable(uint32_t i2c_periph, uint32_t dualaddr)
{
    if(I2C_DUADEN_ENABLE == dualaddr){
        I2C_SADDR1(i2c_periph) |= I2C_SADDR1_DUADEN;
    }else{
        I2C_SADDR1(i2c_periph) &= ~(I2C_SADDR1_DUADEN);
    }
}

/*!
    \brief      enable I2C
    \param[in]  i2c_periph: I2Cx(x=0,1) 
    \param[out] none
    \retval     none
*/
void i2c_enable(uint32_t i2c_periph)
{
    I2C_CTL0(i2c_periph) |= I2C_CTL0_I2CEN;
}

/*!
    \brief      disable I2C
    \param[in]  i2c_periph: I2Cx(x=0,1) 
    \param[out] none
    \retval     none
*/
void i2c_disable(uint32_t i2c_periph)
{
    I2C_CTL0(i2c_periph) &= ~(I2C_CTL0_I2CEN);
}

/*!
    \brief      generate a START condition on I2C bus
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[out] none
    \retval     none
*/
void i2c_start_on_bus(uint32_t i2c_periph)
{
    I2C_CTL0(i2c_periph) |= I2C_CTL0_START;
}

/*!
    \brief      generate a STOP condition on I2C bus
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[out] none
    \retval     none
*/
void i2c_stop_on_bus(uint32_t i2c_periph)
{
    I2C_CTL0(i2c_periph) |= I2C_CTL0_STOP;
}

/*!
    \brief      I2C transmit data function
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  data: data of transmission 
    \param[out] none
    \retval     none
*/
void i2c_data_transmit(uint32_t i2c_periph, uint8_t data)
{
    I2C_DATA(i2c_periph) = DATA_TRANS(data);
}

/*!
    \brief      I2C receive data function
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[out] none
    \retval     data of received
*/
uint8_t i2c_data_receive(uint32_t i2c_periph)
{
    return (uint8_t)DATA_RECV(I2C_DATA(i2c_periph));
}

/*!
    \brief      enable I2C DMA mode 
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  dmastate: 
      \arg        I2C_DMA_ON: DMA mode enable
      \arg        I2C_DMA_OFF: DMA mode disable
    \param[out] none
    \retval     none
*/
void i2c_dma_enable(uint32_t i2c_periph, uint32_t dmastate)
{
    /* configure I2C DMA function */
    uint32_t ctl = 0U;
    ctl = I2C_CTL1(i2c_periph);
    ctl &= ~(I2C_CTL1_DMAON); 
    ctl |= dmastate;
    I2C_CTL1(i2c_periph) = ctl;
}

/*!
    \brief      flag indicating DMA last transfer
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  dmalast: 
      \arg        I2C_DMALST_ON: next DMA EOT is the last transfer
      \arg        I2C_DMALST_OFF: next DMA EOT is not the last transfer
    \param[out] none
    \retval     none
*/
void i2c_dma_last_transfer_enable(uint32_t i2c_periph, uint32_t dmalast)
{
    /* configure DMA last transfer */
    uint32_t ctl = 0U;
    ctl = I2C_CTL1(i2c_periph);
    ctl &= ~(I2C_CTL1_DMALST); 
    ctl |= dmalast;
    I2C_CTL1(i2c_periph) = ctl;
}

/*!
    \brief      whether to stretch SCL low when data is not ready in slave mode 
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  stretchpara:
      \arg        I2C_SCLSTRETCH_ENABLE: SCL stretching is enabled
      \arg        I2C_SCLSTRETCH_DISABLE: SCL stretching is disabled
    \param[out] none
    \retval     none
*/
void i2c_stretch_scl_low_config(uint32_t i2c_periph, uint32_t stretchpara)
{
    /* configure I2C SCL strerching enable or disable */
    uint32_t ctl = 0U;
    ctl = I2C_CTL0(i2c_periph);
    ctl &= ~(I2C_CTL0_DISSTRC); 
    ctl |= stretchpara;
    I2C_CTL0(i2c_periph) = ctl;
}

/*!
    \brief      whether or not to response to a general call 
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  gcallpara:
      \arg        I2C_GCEN_ENABLE: slave will response to a general call
      \arg        I2C_GCEN_DISABLE: slave will not response to a general call
    \param[out] none
    \retval     none
*/
void i2c_slave_response_to_gcall_config(uint32_t i2c_periph, uint32_t gcallpara)
{
    /* configure slave response to a general call enable or disable */
    uint32_t ctl = 0U;
    ctl = I2C_CTL0(i2c_periph);
    ctl &= ~(I2C_CTL0_GCEN); 
    ctl |= gcallpara;
    I2C_CTL0(i2c_periph) = ctl;
}

/*!
    \brief      software reset I2C 
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  sreset:
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
    \brief      check I2C flag is set or not
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  flag:
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
      \arg        I2C_FLAG_TRS: whether the I2C is a transmitter or a receiver
      \arg        I2C_FLAG_RXGC: general call address (00h) received
      \arg        I2C_FLAG_DEFSMB: default address of SMBus device
      \arg        I2C_FLAG_HSTSMB: SMBus host header detected in slave mode
      \arg        I2C_FLAG_DUMOD: dual flag in slave mode indicating which address is matched in dual-address mode
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus i2c_flag_get(uint32_t i2c_periph, uint32_t flag)
{
    uint32_t reg = 0U;
    FlagStatus reval = RESET;
    /* get the flag in which register */
    reg = (BIT(31) & flag);
    if((BIT(31) == reg)){
        if((I2C_STAT1(i2c_periph)&(flag & I2C_FLAG_MASK))){
            reval = SET;
        }else{
            reval = RESET;
        }
    }else{
        if((I2C_STAT0(i2c_periph)&(flag & I2C_FLAG_MASK))){
            reval = SET;
        }else{
            reval = RESET;
        }
    }
    /* return the flag status */
    return reval;
}

/*!
    \brief      clear I2C flag
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  flag: flag type
      \arg       I2C_FLAG_SMBALT: SMBus Alert status
      \arg       I2C_FLAG_SMBTO: timeout signal in SMBus mode
      \arg       I2C_FLAG_PECERR: PEC error when receiving data
      \arg       I2C_FLAG_OUERR: over-run or under-run situation occurs in slave mode    
      \arg       I2C_FLAG_AERR: acknowledge error
      \arg       I2C_FLAG_LOSTARB: arbitration lost in master mode   
      \arg       I2C_FLAG_BERR: a bus error   
      \arg       I2C_FLAG_ADDSEND: cleared by reading I2C_STAT0 and reading I2C_STAT1
    \param[out] none
    \retval     none
*/
void i2c_flag_clear(uint32_t i2c_periph, uint32_t flag)
{
    if(I2C_FLAG_ADDSEND == flag){
        /* read I2C_STAT0 and then read I2C_STAT1 to clear ADDSEND */
        I2C_STAT0(i2c_periph);
        I2C_STAT1(i2c_periph);
    }else{
        I2C_STAT0(i2c_periph) &= ~(flag);
    }
}

/*!
    \brief      enable I2C interrupt
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  inttype: interrupt type 
      \arg        I2C_INT_ERR: error interrupt enable 
      \arg        I2C_INT_EV: event interrupt enable 
      \arg        I2C_INT_BUF: buffer interrupt enable   
    \param[out] none
    \retval     none
*/
void i2c_interrupt_enable(uint32_t i2c_periph, uint32_t inttype)
{
    I2C_CTL1(i2c_periph) |= (inttype);
}

/*!
    \brief      disable I2C interrupt
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  inttype: interrupt type 
      \arg        I2C_INT_ERR: error interrupt enable 
      \arg        I2C_INT_EV: event interrupt enable 
      \arg        I2C_INT_BUF: buffer interrupt enable  
    \param[out] none
    \retval     none
*/
void i2c_interrupt_disable(uint32_t i2c_periph, uint32_t inttype)
{
    I2C_CTL1(i2c_periph) &= ~(inttype);
}

/*!
    \brief      check I2C interrupt flag
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  int_flag: interrupt flag 
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
    \param[out] none
    \retval     none
*/
FlagStatus i2c_interrupt_flag_get(uint32_t i2c_periph, uint32_t intflag)
{
    uint32_t evie, errie, bufie;

    evie = I2C_CTL1(i2c_periph)&I2C_CTL1_EVIE;
    errie = I2C_CTL1(i2c_periph)&I2C_CTL1_ERRIE;
    /* check I2C event interrupt enable bit */
    if((intflag&0x00ffU) && evie){
        if(intflag&0x001fU){
            /* check I2C event flags except TBE and RBNE */
            if(intflag & I2C_STAT0(i2c_periph)){
                return SET;
            }else{
                return RESET;
            }
        }else{
            /* check I2C event flags TBE and RBNE */
            bufie = I2C_CTL1(i2c_periph)&I2C_CTL1_BUFIE;
            if(bufie){
                if(intflag & I2C_STAT0(i2c_periph)){
                    return SET;
                }else{
                    return RESET;
                }
            }else{
                return RESET;
            }
        }
    /* check I2C error interrupt enable bit */
    }else if((intflag&0xff00U) && errie){
        /* check I2C error flags */
        if(intflag & I2C_STAT0(i2c_periph)){
            return SET;
        }else{
            return RESET;
        }
    }else{
        return RESET;
    }
}

/*!
    \brief      clear I2C interrupt flag
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  intflag: interrupt flag 
      \arg        I2C_INT_FLAG_ADDSEND: address is sent in master mode or received and matches in slave mode interrupt flag
      \arg        I2C_INT_FLAG_BERR: a bus error occurs indication a unexpected start or stop condition on I2C bus interrupt flag
      \arg        I2C_INT_FLAG_LOSTARB: arbitration lost in master mode interrupt flag
      \arg        I2C_INT_FLAG_AERR: acknowledge error interrupt flag
      \arg        I2C_INT_FLAG_OUERR: over-run or under-run situation occurs in slave mode interrupt flag
      \arg        I2C_INT_FLAG_PECERR: PEC error when receiving data interrupt flag
      \arg        I2C_INT_FLAG_SMBTO: timeout signal in SMBus mode interrupt flag
      \arg        I2C_INT_FLAG_SMBALT: SMBus Alert status interrupt flag
    \param[out] none
    \retval     none
*/
void i2c_interrupt_flag_clear(uint32_t i2c_periph, uint32_t intflag)
{
    if(I2C_INT_FLAG_ADDSEND == intflag){
        /* read I2C_STAT0 and then read I2C_STAT1 to clear ADDSEND */
        I2C_STAT0(i2c_periph);
        I2C_STAT1(i2c_periph);
    }else{
        I2C_STAT0(i2c_periph) &= ~(intflag);
    }
}

/*!
    \brief      I2C PEC calculation on or off
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  pecpara:
      \arg        I2C_PEC_ENABLE: PEC calculation on 
      \arg        I2C_PEC_DISABLE: PEC calculation off 
    \param[out] none
    \retval     none
*/
void i2c_pec_enable(uint32_t i2c_periph, uint32_t pecstate)
{
    /* on/off PEC calculation */
    uint32_t ctl = 0U;
    ctl = I2C_CTL0(i2c_periph);
    ctl &= ~(I2C_CTL0_PECEN);
    ctl |= pecstate;
    I2C_CTL0(i2c_periph) = ctl;
}

/*!
    \brief      I2C whether to transfer PEC value
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  pecpara:
      \arg        I2C_PECTRANS_ENABLE: transfer PEC 
      \arg        I2C_PECTRANS_DISABLE: not transfer PEC 
    \param[out] none
    \retval     none
*/
void i2c_pec_transfer_enable(uint32_t i2c_periph, uint32_t pecpara)
{
    /* whether to transfer PEC */
    uint32_t ctl = 0U;
    ctl = I2C_CTL0(i2c_periph);
    ctl &= ~(I2C_CTL0_PECTRANS);
    ctl |= pecpara;
    I2C_CTL0(i2c_periph) = ctl;
}

/*!
    \brief      get packet error checking value 
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[out] none
    \retval     PEC value
*/
uint8_t i2c_pec_value_get(uint32_t i2c_periph)
{
    return (uint8_t)((I2C_STAT1(i2c_periph) & I2C_STAT1_ECV)>>8);
}

/*!
    \brief      I2C issue alert through SMBA pin 
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  smbuspara:
      \arg        I2C_SALTSEND_ENABLE: issue alert through SMBA pin 
      \arg        I2C_SALTSEND_DISABLE: not issue alert through SMBA pin 
    \param[out] none
    \retval     none
*/
void i2c_smbus_issue_alert(uint32_t i2c_periph, uint32_t smbuspara)
{
    /* issue alert through SMBA pin configure*/
    uint32_t ctl = 0U;
    ctl = I2C_CTL0(i2c_periph);
    ctl &= ~(I2C_CTL0_SALT); 
    ctl |= smbuspara;
    I2C_CTL0(i2c_periph) = ctl;
}

/*!
    \brief      enable or disable I2C ARP protocol in SMBus switch
    \param[in]  i2c_periph: I2Cx(x=0,1)
    \param[in]  smbuspara:
      \arg        I2C_ARP_ENABLE: enable ARP
      \arg        I2C_ARP_DISABLE: disable ARP
    \param[out] none
    \retval     none
*/
void i2c_smbus_arp_enable(uint32_t i2c_periph, uint32_t arpstate)
{
    /* enable or disable I2C ARP protocol*/
    uint32_t ctl = 0U;
    ctl = I2C_CTL0(i2c_periph);
    ctl &= ~(I2C_CTL0_ARPEN);
    ctl |= arpstate;
    I2C_CTL0(i2c_periph) = ctl;
}

