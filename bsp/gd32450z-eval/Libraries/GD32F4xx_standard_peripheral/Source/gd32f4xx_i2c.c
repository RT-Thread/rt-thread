/*!
    \file  gd32f4xx_i2c.c
    \brief I2C driver

*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#include "gd32f4xx_i2c.h"

#define I2CCLK_MAX                    0x3fU              /*!< i2cclk max value */
#define I2C_STATE_MASK                0x0000FFFFU        /*!< i2c state mask */

/*!
    \brief      reset I2C
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void i2c_deinit(uint32_t i2c_periph)
{
    switch(i2c_periph){
    case I2C0:
        rcu_periph_reset_enable(RCU_I2C0RST);
        rcu_periph_reset_disable(RCU_I2C0RST);
        break;
    case I2C1:
        rcu_periph_reset_enable(RCU_I2C1RST);
        rcu_periph_reset_disable(RCU_I2C1RST);
        break;
    case I2C2:
        rcu_periph_reset_enable(RCU_I2C2RST);
        rcu_periph_reset_disable(RCU_I2C2RST);
        break;
    default:
        break;
    
    }
}

/*!
    \brief      I2C clock configure
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  clkspeed: i2c clock speed   
    \param[in]  dutycyc: duty cycle in fast mode
      \arg        I2C_DTCY_2:    T_low/T_high=2 
      \arg        I2C_DTCY_16_9: T_low/T_high=16/9
    \param[out] none
    \retval     none
*/
void i2c_clock_config(uint32_t i2c_periph,uint32_t clkspeed,uint32_t dutycyc)
{
    uint32_t pclk1,clkc,i2cclk,risetime;
    pclk1 = rcu_clock_freq_get(CK_APB1);
    /* I2C Peripheral clock frequency */
    i2cclk=((pclk1)/(uint32_t)(1000000));
    if(i2cclk >= I2CCLK_MAX){
        i2cclk = I2CCLK_MAX;
    }
        
    I2C_CTL1(i2c_periph) |= (I2C_CTL1_I2CCLK & i2cclk) ;
    
    if(100000U >= clkspeed){
         /* standard mode the maximum SCL rise time in standard mode is 1000ns  */
        risetime = (uint32_t)((pclk1/1000000U)+1U);
        if(risetime >= I2CCLK_MAX){
            I2C_RT(i2c_periph) |= I2CCLK_MAX;
        }else{
            I2C_RT(i2c_periph) |= (uint32_t)((pclk1/1000000U)+1U);
        }
        clkc = (uint32_t)(pclk1/(clkspeed*2U));
        if(clkc < 0x04U){
            /* The CLKC in standard mode minmum value is 4*/
            clkc = 0x04U;
        }
        I2C_CKCFG(i2c_periph) |= (I2C_CKCFG_CLKC & clkc);        

    }else{
        /* fast mode the maximum SCL rise time in standard mode is 300ns  */
        I2C_RT(i2c_periph) |= (uint16_t)(((i2cclk*(uint16_t)300)/(uint16_t)1000)+(uint16_t)1);
        if(I2C_DTCY_2 == dutycyc){
            /* I2C_DutyCycle == 2 */
            clkc = (uint16_t)(pclk1/(clkspeed*3U));
        } else{
            /* I2C_DutyCycle == 16/9 */
            clkc = (uint16_t)(pclk1/(clkspeed*25U));
            I2C_CKCFG(i2c_periph) |= I2C_CKCFG_DTCY;
        }
        if((clkc & I2C_CKCFG_CLKC) == 0U){
            /* The CLKC in standard mode minmum value is 1*/
            clkc |= (uint16_t)0x0001;  
        }
        I2C_CKCFG(i2c_periph) |= clkc;
    }
}

/*!
    \brief      I2C address configure
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  i2cmod:
      \arg        I2C_I2CMODE_ENABLE:  I2C mode
      \arg        I2C_SMBUSMODE_ENABLE: SMBus mode
    \param[in]  addformat: 7bits or 10bits
      \arg        I2C_ADDFORMAT_7BITS:  7bits
      \arg        I2C_ADDFORMAT_10BITS: 10bits
    \param[in]  addr: I2C address
    \param[out] none
    \retval     none
*/
void i2c_mode_addr_config(uint32_t i2c_periph,uint32_t i2cmod,uint32_t addformat,uint32_t addr)
{
    /* SMBus/I2C mode selected */
    uint32_t ctl = 0U;
    ctl = I2C_CTL0(i2c_periph);
    ctl &= ~(I2C_CTL0_SMBEN); 
    ctl |= i2cmod;
    I2C_CTL0(i2c_periph) = ctl;
    /* configure address */
    I2C_SADDR0(i2c_periph) = (addformat|addr);
    
}

/*!
    \brief      SMBus type selection
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  ack:
      \arg        I2C_SMBUS_DEVICE: device
      \arg        I2C_SMBUS_HOST: host
    \param[out] none
    \retval     none
*/
void i2c_smbus_type_config(uint32_t i2c_periph,uint32_t type)
{
    if(I2C_SMBUS_HOST == type){
       I2C_CTL0(i2c_periph) |= I2C_CTL0_SMBSEL;  
    }else{
       I2C_CTL0(i2c_periph) &= ~(I2C_CTL0_SMBSEL);  
    } 
}

/*!
    \brief      whether or not to send an ACK
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  ack:
      \arg        I2C_ACK_ENABLE: ACK will be sent  
      \arg        I2C_ACK_DISABLE: ACK will not be sent    
    \param[out] none
    \retval     none
*/
void i2c_ack_config(uint32_t i2c_periph,uint8_t ack)
{
    if(I2C_ACK_ENABLE == ack){
       I2C_CTL0(i2c_periph) |= I2C_CTL0_ACKEN;  
    }else{
       I2C_CTL0(i2c_periph) &= ~(I2C_CTL0_ACKEN);  
    } 
}

/*!
    \brief      I2C POAP position configure
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  pos:
      \arg        I2C_ACK_ENABLE: ACK will be sent  
      \arg        I2C_ACK_DISABLE: ACK will not be sent
    \param[out] none
    \retval     none
*/
void i2c_ackpos_config(uint32_t i2c_periph,uint8_t pos)
{
    /* configure i2c POAP position */
    if(I2C_ACKPOS_NEXT == pos){
       I2C_CTL0(i2c_periph) |= I2C_CTL0_POAP;  
    }else{
       I2C_CTL0(i2c_periph) &= ~(I2C_CTL0_POAP);  
    } 

}

/*!
    \brief      master send slave address
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  addr: slave address  
    \param[in]  trandirection: transmitter or receiver
      \arg        I2C_TRANSMITTER: transmitter  
      \arg        I2C_RECEIVER:    receiver  
    \param[out] none
    \retval     none
*/
void i2c_master_addressing(uint32_t i2c_periph,uint8_t addr,uint32_t trandirection)
{
    if(I2C_TRANSMITTER==trandirection){
        addr = (uint8_t)((uint32_t)addr & I2C_TRANSMITTER);
    }else{
        addr = (uint8_t)((uint32_t)addr|I2C_RECEIVER);
    }
    I2C_DATA(i2c_periph) = addr;
}

/*!
    \brief      dual-address mode switch
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  dualaddr:
      \arg        I2C_DUADEN_DISABLE: dual-address mode disabled  
      \arg        I2C_DUADEN_ENABLE: dual-address mode enabled
    \param[out] none
    \retval     none
*/
void i2c_dualaddr_enable(uint32_t i2c_periph,uint8_t dualaddr)
{
    if(I2C_DUADEN_ENABLE == dualaddr){
       I2C_SADDR1(i2c_periph) |= I2C_SADDR1_DUADEN;  
    }else{
       I2C_SADDR1(i2c_periph) &= ~(I2C_SADDR1_DUADEN);  
    }        
}

/*!
    \brief      enable i2c
    \param[in]  i2c_periph: I2Cx(x=0,1,2) 
    \param[out] none
    \retval     none
*/
void i2c_enable(uint32_t i2c_periph)
{
    I2C_CTL0(i2c_periph) |= I2C_CTL0_I2CEN;
}

/*!
    \brief      disable i2c
    \param[in]  i2c_periph: I2Cx(x=0,1,2) 
    \param[out] none
    \retval     none
*/
void i2c_disable(uint32_t i2c_periph)
{
    I2C_CTL0(i2c_periph) &= ~(I2C_CTL0_I2CEN);
    
}

/*!
    \brief      generate a START condition on I2C bus
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void i2c_start_on_bus(uint32_t i2c_periph)
{
    I2C_CTL0(i2c_periph) |= I2C_CTL0_START;
}

/*!
    \brief      generate a STOP condition on I2C bus
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void i2c_stop_on_bus(uint32_t i2c_periph)
{
    I2C_CTL0(i2c_periph) |= I2C_CTL0_STOP;
}

/*!
    \brief      i2c transmit data function
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  data: data of transmission 
    \param[out] none
    \retval     none
*/
void i2c_transmit_data(uint32_t i2c_periph,uint8_t data)
{
    I2C_DATA(i2c_periph) = data;
}

/*!
    \brief      i2c receive data function
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[out] none
    \retval     data of received
*/
uint8_t i2c_receive_data(uint32_t i2c_periph)
{
    return (uint8_t)I2C_DATA(i2c_periph); 
}

/*!
    \brief      I2C DMA mode enable
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  dmastste: 
      \arg        I2C_DMA_ON: DMA mode enabled
      \arg        I2C_DMA_OFF: DMA mode disabled
    \param[out] none
    \retval     none
*/
void i2c_dma_enable(uint32_t i2c_periph,uint32_t dmastste)
{
    /* configure i2c DMA function */
    uint32_t ctl = 0U;
    ctl = I2C_CTL1(i2c_periph);
    ctl &= ~(I2C_CTL1_DMAON); 
    ctl |= dmastste;
    I2C_CTL1(i2c_periph) = ctl;

}

/*!
    \brief      flag indicating DMA last transfer
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  dmastste: 
      \arg        I2C_DMALST_ON: next DMA EOT is the last transfer
      \arg        I2C_DMALST_OFF: next DMA EOT is not the last transfer
    \param[out] none
    \retval     none
*/
void i2c_dma_last_transfer_enable(uint32_t i2c_periph,uint32_t dmalast)
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
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  stretchpara:
      \arg        I2C_SCLSTRETCH_ENABLE: SCL stretching is enabled
      \arg        I2C_SCLSTRETCH_DISABLE: SCL stretching is disabled
    \param[out] none
    \retval     none
*/
void i2c_stretch_scl_low_config(uint32_t i2c_periph,uint32_t stretchpara)
{
    /* configure I2C SCL strerching enable or disable */
    uint32_t ctl = 0U;
    ctl = I2C_CTL0(i2c_periph);
    ctl &= ~(I2C_CTL0_DISSTRC); 
    ctl |= stretchpara;
    I2C_CTL0(i2c_periph) = ctl;
}

/*!
    \brief      whether or not to response to a general Cal 
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
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
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
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
    \brief      check i2c state
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  state:
      \arg        I2C_SBSEND: start condition send out 
      \arg        I2C_ADDSEND: address is sent in master mode or received and matches in slave mode
      \arg        I2C_BTC: byte transmission finishes
      \arg        I2C_ADD10SEND: header of 10-bit address is sent in master mode
      \arg        I2C_STPDET: etop condition detected in slave mode
      \arg        I2C_RBNE: I2C_DATA is not Empty during receiving
      \arg        I2C_TBE: I2C_DATA is empty during transmitting
      \arg        I2C_BERR: a bus error occurs indication a unexpected start or stop condition on I2C bus
      \arg        I2C_LOSTARB: arbitration lost in master mode
      \arg        I2C_AERR: acknowledge error
      \arg        I2C_OUERR: over-run or under-run situation occurs in slave mode
      \arg        I2C_PECERR: PEC error when receiving data
      \arg        I2C_SMBTO: timeout signal in SMBus mode
      \arg        I2C_SMBALT: SMBus alert status
      \arg        I2C_MASTER: a flag indicating whether I2C block is in master or slave mode
      \arg        I2C_I2CBSY: busy flag
      \arg        I2C_TRS: whether the I2C is a transmitter or a receiver
      \arg        I2C_RXGC: general call address (00h) received
      \arg        I2C_DEFSMB: default address of SMBus device
      \arg        I2C_HSTSMB: SMBus host header detected in slave mode
      \arg        I2C_DUMODF: dual flag in slave mode indicating which address is matched in dual-address mode
    \param[out] none
    \retval     state of i2c
*/
FlagStatus i2c_flag_get(uint32_t i2c_periph,uint32_t state )
{
    uint32_t reg = 0U;
    FlagStatus regstate = RESET;
    /* get the state in which register */
    reg = (BIT(31) & state);
    if((BIT(31) == reg)){
        if((I2C_STAT1(i2c_periph)&(state & I2C_STATE_MASK))){
            regstate = SET;
        }else{
            regstate = RESET;
        }
    }else{
        if((I2C_STAT0(i2c_periph)&(state & I2C_STATE_MASK))){
            regstate = SET;
        }else{
            regstate = RESET;
        }        
    }
    /* return the state */
    return regstate;
}

/*!
    \brief      clear i2c state
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  state: state type 
      \@arg       I2C_STAT0_SMBALT: SMBus Alert status
      \@arg       I2C_STAT0_SMBTO: timeout signal in SMBus mode
      \@arg       I2C_STAT0_PECERR: PEC error when receiving data
      \@arg       I2C_STAT0_OUERR: over-run or under-run situation occurs in slave mode    
      \@arg       I2C_STAT0_AERR: acknowledge error
      \@arg       I2C_STAT0_LOSTARB: arbitration lost in master mode   
      \@arg       I2C_STAT0_BERR: a bus error   
      \@arg       I2C_STAT0_ADDSEND: cleared by reading I2C_STAT0 and reading I2C_STAT1
    \param[out] none
    \retval     none
*/
void i2c_flag_clear(uint32_t i2c_periph,uint32_t state)
{
    if(I2C_STAT0_ADDSEND == state){
        /* read I2C_STAT0 and then read I2C_STAT1 to clear ADDSEND */
        I2C_STAT0(i2c_periph);
        I2C_STAT1(i2c_periph);
    }else{
        I2C_STAT0(i2c_periph) &= ~(state);
    }
}

/*!
    \brief      enable i2c interrupt
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  inttype:      interrupt type 
      \arg        I2C_CTL1_ERRIE: error interrupt enable 
      \arg        I2C_CTL1_EVIE:  event interrupt enable 
      \arg        I2C_CTL1_BUFIE: buffer interrupt enable   
    \param[out] none
    \retval     none
*/
void i2c_interrupt_enable(uint32_t i2c_periph,uint32_t inttype)
{
    I2C_CTL1(i2c_periph) |= (inttype);   
}

/*!
    \brief      disable i2c interrupt
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  inttype: interrupt type 
      \arg        I2C_CTL1_ERRIE: error interrupt enable 
      \arg        I2C_CTL1_EVIE: event interrupt enable 
      \arg        I2C_CTL1_BUFIE: buffer interrupt enable   
    \param[out] none
    \retval     none
*/
void i2c_interrupt_disable(uint32_t i2c_periph,uint32_t inttype)
{
    I2C_CTL1(i2c_periph) &= ~(inttype);   
}

/*!
    \brief      I2C PEC calculation on or off
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  pecpara:
      \arg        I2C_PEC_ENABLE: PEC calculation on 
      \arg        I2C_PEC_DISABLE: PEC calculation off 
    \param[out] none
    \retval     none
*/
void i2c_pec_enable(uint32_t i2c_periph,uint32_t pecstate)
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
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  pecpara:
      \arg        I2C_PECTRANS_ENABLE: transfer PEC 
      \arg        I2C_PECTRANS_DISABLE: not transfer PEC 
    \param[out] none
    \retval     none
*/
void i2c_pec_transfer_enable(uint32_t i2c_periph,uint32_t pecpara)
{
    /* whether to transfer PEC */
    uint32_t ctl = 0U;
    ctl = I2C_CTL0(i2c_periph);
    ctl &= ~(I2C_CTL0_PECTRANS); 
    ctl |= pecpara;
    I2C_CTL0(i2c_periph) = ctl;
}

/*!
    \brief      packet error checking value 
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[out] none
    \retval     PEC value
*/
uint8_t i2c_pec_value(uint32_t i2c_periph)
{
    return  (uint8_t)((I2C_STAT1(i2c_periph) &I2C_STAT1_ECV)>>8);
}

/*!
    \brief      I2C issue alert through SMBA pin 
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  smbuspara:
      \arg        I2C_SALTSEND_ENABLE: issue alert through SMBA pin 
      \arg        I2C_SALTSEND_DISABLE: not issue alert through SMBA pin 
    \param[out] none
    \retval     none
*/
void i2c_smbus_alert_issue(uint32_t i2c_periph,uint32_t smbuspara)
{
    /* issue alert through SMBA pin configure*/
    uint32_t ctl = 0U;
    ctl = I2C_CTL0(i2c_periph);
    ctl &= ~(I2C_CTL0_SALT); 
    ctl |= smbuspara;
    I2C_CTL0(i2c_periph) = ctl;
}

/*!
    \brief      I2C ARP protocol in SMBus switch enable or disable 
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  smbuspara:
      \arg        I2C_ARP_ENABLE: ARP is enabled 
      \arg        I2C_ARP_DISABLE: ARP is disabled 
    \param[out] none
    \retval     none
*/
void i2c_smbus_arp_enable(uint32_t i2c_periph,uint32_t arpstate)
{
    /* enable or disable I2C ARP protocol*/
    uint32_t ctl = 0U;
    ctl = I2C_CTL0(i2c_periph);
    ctl &= ~(I2C_CTL0_ARPEN); 
    ctl |= arpstate;
    I2C_CTL0(i2c_periph) = ctl;
}

/*!
    \brief      analog noise filter disable
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void i2c_analog_noise_filter_disable(uint32_t i2c_periph)
{
    I2C_FCTL(i2c_periph) |= I2C_FCTL_AFD;  
}

/*!
    \brief      analog noise filter enable
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void i2c_analog_noise_filter_enable(uint32_t i2c_periph)
{
    I2C_FCTL(i2c_periph) &= ~(I2C_FCTL_AFD);  
}

/*!
    \brief      digital noise filter configuration
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  dfilterpara: refer to enum i2c_gcall_config_enum
    \param[out] none
    \retval     none
*/
void i2c_digital_noise_filter_config(uint32_t i2c_periph,i2c_digital_filter_enum dfilterpara)
{
    I2C_FCTL(i2c_periph) |= dfilterpara;  
}

/*!
    \brief      enable SAM_V interface
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void i2c_sam_enable(uint32_t i2c_periph)
{
    I2C_SAMCS(i2c_periph) |= I2C_SAMCS_SAMEN;  
}

/*!
    \brief      disable SAM_V interface
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void i2c_sam_disable(uint32_t i2c_periph)
{
    I2C_SAMCS(i2c_periph) &= ~(I2C_SAMCS_SAMEN);  
}

/*!
    \brief      enable SAM_V interface timeout detect
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void i2c_sam_timeout_enable(uint32_t i2c_periph)
{
    I2C_SAMCS(i2c_periph) |= I2C_SAMCS_STOEN;  
}

/*!
    \brief      disable SAM_V interface timeout detect
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void i2c_sam_timeout_disable(uint32_t i2c_periph)
{
    I2C_SAMCS(i2c_periph) &= ~(I2C_SAMCS_STOEN);  
}

/*!
    \brief      enable the specified I2C SAM interrupt
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  inttype: interrupt type 
      \@arg       I2C_SAMCS_TFFIE: txframe fall interrupt
      \@arg       I2C_SAMCS_TFRIE: txframe rise interrupt
      \@arg       I2C_SAMCS_RFFIE: rxframe fall interrupt
      \@arg       I2C_SAMCS_RFRIE: rxframe rise interrupt   
    \param[out]  none
    \retval      none
*/
void i2c_sam_interrupt_enable(uint32_t i2c_periph,uint32_t inttype)
{
    I2C_SAMCS(i2c_periph) |= (inttype);   
}

/*!
    \brief      disable i2c interrupt
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  inttype:      interrupt type 
      \@arg       I2C_SAMCS_TFFIE: txframe fall interrupt
      \@arg       I2C_SAMCS_TFRIE: txframe rise interrupt
      \@arg       I2C_SAMCS_RFFIE: rxframe fall interrupt
      \@arg       I2C_SAMCS_RFRIE: rxframe rise interrupt    
    \param[out] none
    \retval     none
*/
void i2c_sam_interrupt_disable(uint32_t i2c_periph,uint32_t inttype)
{
    I2C_SAMCS(i2c_periph) &= ~(inttype);   
}

/*!
    \brief      check i2c SAM state
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  samstate: state type 
      \@arg       I2C_SAMCS_TXF: level of txframe signal
      \@arg       I2C_SAMCS_RXF: level of rxframe signal
      \@arg       I2C_SAMCS_TFF: txframe fall flag
      \@arg       I2C_SAMCS_TFR: txframe rise flag    
      \@arg       I2C_SAMCS_RFF: rxframe fall flag
      \@arg       I2C_SAMCS_RFR: rxframe rise flag   
    \param[out] none
    \retval     state of i2c SAM
*/
FlagStatus i2c_sam_flag_get(uint32_t i2c_periph,uint32_t samstate)
{
    FlagStatus reg = RESET;
    if(I2C_SAMCS(i2c_periph)&samstate){
        reg =SET;
    }else{
        reg =RESET; 
    }
    return reg;
}

/*!
    \brief      clear i2c SAM state
    \param[in]  i2c_periph: I2Cx(x=0,1,2)
    \param[in]  samstate: state type 
      \@arg       I2C_SAMCS_TFF: txframe fall flag
      \@arg       I2C_SAMCS_TFR: txframe rise flag    
      \@arg       I2C_SAMCS_RFF: rxframe fall flag
      \@arg       I2C_SAMCS_RFR: rxframe rise flag   
    \param[out] none
    \retval     none
*/
void i2c_sam_flag_clear(uint32_t i2c_periph,uint32_t samstate)
{
    I2C_SAMCS(i2c_periph) &= ~(samstate);
  
}

