/*!
    \file  gd32f4xx_spi.c
    \brief SPI driver
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.1, firmware for GD32F4xx
*/

#include "gd32f4xx_spi.h"
#include "gd32f4xx_rcu.h"

#define SPI_INIT_MASK                   ((uint32_t)0x00003040U)
#define I2S_INIT_MASK                   ((uint32_t)0x0000F047U)
#define I2S_FULL_DUPLEX_MASK            ((uint32_t)0x0000F040U)

/*!
    \brief      SPI and I2S reset
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5),include I2S1_ADD and I2S2_ADD
    \param[out] none
    \retval     none
*/
void spi_i2s_deinit(uint32_t spi_periph)
{
    switch(spi_periph){
    case SPI0:
        /* reset SPI0 and I2S0 */
        rcu_periph_reset_enable(RCU_SPI0RST);
        rcu_periph_reset_disable(RCU_SPI0RST);
        break;
    case SPI1:
        /* reset SPI1,I2S1 and I2S1_ADD */
        rcu_periph_reset_enable(RCU_SPI1RST);
        rcu_periph_reset_disable(RCU_SPI1RST);
        break;
    case SPI2:
        /* reset SPI2,I2S2 and I2S2_ADD */
        rcu_periph_reset_enable(RCU_SPI2RST);
        rcu_periph_reset_disable(RCU_SPI2RST);
        break;
    case SPI3:
        /* reset SPI3 and I2S3 */
        rcu_periph_reset_enable(RCU_SPI3RST);
        rcu_periph_reset_disable(RCU_SPI3RST);
        break;
    case SPI4:
        /* reset SPI4 and I2S4 */
        rcu_periph_reset_enable(RCU_SPI4RST);
        rcu_periph_reset_disable(RCU_SPI4RST);
        break;
    case SPI5:
        /* reset SPI5 */
        rcu_periph_reset_enable(RCU_SPI5RST);
        rcu_periph_reset_disable(RCU_SPI5RST);
        break;
    default :
        break;
    }
}

/*!
    \brief      SPI parameter initialization
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[in]  spi_struct: SPI parameter initialization stuct
                members of the structure and the member values are shown as below:
                  device_mode          : SPI_MASTER, SPI_SLAVE.
                  trans_mode           : SPI_TRANSMODE_FULLDUPLEX, SPI_TRANSMODE_RECEIVEONLY,
                                         SPI_TRANSMODE_BDRECEIVE, SPI_TRANSMODE_BDTRANSMIT
                  frame_size           : SPI_FRAMESIZE_16BIT, SPI_FRAMESIZE_8BIT
                  nss:                 : SPI_NSS_SOFT, SPI_NSS_HARD
                  endian               : SPI_ENDIAN_MSB, SPI_ENDIAN_LSB
                  clock_polarity_phase : SPI_CK_PL_LOW_PH_1EDGE, SPI_CK_PL_HIGH_PH_1EDGE
                                         SPI_CK_PL_LOW_PH_2EDGE, SPI_CK_PL_HIGH_PH_2EDGE
                  prescale             : SPI_PSC_n (n=2,4,8,16,32,64,128,256)
    \param[out] none
    \retval     none
*/
void spi_init(uint32_t spi_periph, spi_parameter_struct* spi_struct)
{   
    uint32_t reg = 0U;
    reg = SPI_CTL0(spi_periph);
    reg &= SPI_INIT_MASK;

    /* (1) select SPI as master or slave */
    reg |= spi_struct->device_mode;
    /* (2) select SPI transfer mode */
    reg |= spi_struct->trans_mode;
    /* (3) select SPI frame size */
    reg |= spi_struct->frame_size;
    /* (4) select SPI nss use hardware or software */
    reg |= spi_struct->nss;
    /* (5) select SPI LSB or MSB */
    reg |= spi_struct->endian;
    /* (6) select SPI polarity and phase */
    reg |= spi_struct->clock_polarity_phase;
    /* (7) select SPI prescale to adjust transmit speed */
    reg |= spi_struct->prescale;

    /* write to SPI_CTL0 register */
    SPI_CTL0(spi_periph) = (uint32_t)reg;

    SPI_I2SCTL(spi_periph) &= (uint32_t)(~SPI_I2SCTL_I2SSEL);
}

/*!
    \brief      SPI enable
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[out] none
    \retval     none
*/
void spi_enable(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) |= (uint32_t)SPI_CTL0_SPIEN;
}

/*!
    \brief      SPI disable
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[out] none
    \retval     none
*/
void spi_disable(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) &= (uint32_t)(~SPI_CTL0_SPIEN);
}

/*!
    \brief      I2S prescale config
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4)
    \param[in]  audiosample:
      \arg        I2S_AUDIOSAMPLE_8K: audio sample rate is 8khz
      \arg        I2S_AUDIOSAMPLE_11K: audio sample rate is 11khz
      \arg        I2S_AUDIOSAMPLE_16K: audio sample rate is 16khz
      \arg        I2S_AUDIOSAMPLE_22K: audio sample rate is 22khz
      \arg        I2S_AUDIOSAMPLE_32K: audio sample rate is 32khz
      \arg        I2S_AUDIOSAMPLE_44K: audio sample rate is 44khz
      \arg        I2S_AUDIOSAMPLE_48K: audio sample rate is 48khz
      \arg        I2S_AUDIOSAMPLE_96K: audio sample rate is 96khz
      \arg        I2S_AUDIOSAMPLE_192K: audio sample rate is 192khz
    \param[in]  frameformat:
      \arg        I2S_FRAMEFORMAT_DT16B_CH16B: I2S data length is 16 bit and channel length is 16 bit
      \arg        I2S_FRAMEFORMAT_DT16B_CH32B: I2S data length is 16 bit and channel length is 32 bit
      \arg        I2S_FRAMEFORMAT_DT24B_CH32B: I2S data length is 24 bit and channel length is 32 bit
      \arg        I2S_FRAMEFORMAT_DT32B_CH32B: I2S data length is 32 bit and channel length is 32 bit
    \param[in]  mckout:
      \arg        I2S_MCKOUT_ENABLE: I2S master clock output enable
      \arg        I2S_MCKOUT_DISABLE: I2S master clock output disable
    \param[out] none
    \retval     none
*/
void i2s_psc_config(uint32_t spi_periph, uint32_t i2s_audiosample, uint32_t i2s_frameformat, uint32_t i2s_mckout)
{
    uint32_t temp_div = 2U, temp_of = 0U;
    uint32_t temp = 0U;
    uint32_t i2sclock = 0U;

#ifndef I2S_EXTERNAL_CLOCK_IN
  uint32_t plli2sm = 0U, plli2sn = 0U, plli2sr = 0U;
#endif /* I2S_EXTERNAL_CLOCK_IN */

    /* deinit SPI_I2SPSC register */
    SPI_I2SPSC(spi_periph) = 0x0002U;

#ifdef I2S_EXTERNAL_CLOCK_IN
    rcu_i2s_clock_config(RCU_I2SSRC_I2S_CKIN);

    /* set the I2S clock to the external clock input value */
    i2sclock = I2S_EXTERNAL_CLOCK_IN;
#else

    /* turn on the oscillator HXTAL */
    rcu_osci_on(RCU_HXTAL);
    /* wait for oscillator stabilization flags is SET */
    rcu_osci_stab_wait(RCU_HXTAL);
    /* turn on the PLLI2S */
    rcu_osci_on(RCU_PLLI2S_CK);
    /* wait for PLLI2S flags is SET */
    rcu_osci_stab_wait(RCU_PLLI2S_CK);
    /* configure the I2S clock source selection */
    rcu_i2s_clock_config(RCU_I2SSRC_PLLI2S);

    /* get the RCU_PLL_PLLPSC value */
    plli2sm = (uint32_t)(RCU_PLL & RCU_PLL_PLLPSC);
    /* get the RCU_PLLI2S_PLLI2SN value */
    plli2sn = (uint32_t)((RCU_PLLI2S & RCU_PLLI2S_PLLI2SN) >> 6);
    /* get the RCU_PLLI2S_PLLI2SR value */
    plli2sr = (uint32_t)((RCU_PLLI2S & RCU_PLLI2S_PLLI2SR) >> 28);

    if((RCU_PLL & RCU_PLL_PLLSEL) == RCU_PLLSRC_HXTAL)
    {
      /* get the I2S source clock value */
      i2sclock = (uint32_t)(((HXTAL_VALUE / plli2sm) * plli2sn) / plli2sr);
    }
    else
    { /* get the I2S source clock value */
      i2sclock = (uint32_t)(((IRC16M_VALUE / plli2sm) * plli2sn) / plli2sr);
    }
#endif /* I2S_EXTERNAL_CLOCK_IN */

    /* config the prescaler depending on the mclk output state, the frame format and audio sample rate */
    if(I2S_MCKOUT_ENABLE == i2s_mckout){
        temp = (uint32_t)(((i2sclock / 256U) * 10U) / i2s_audiosample);
    }else{
        if(I2S_FRAMEFORMAT_DT16B_CH16B == i2s_frameformat){
            temp = (uint32_t)(((i2sclock / 32U) *10U ) / i2s_audiosample);
        }else{
            temp = (uint32_t)(((i2sclock / 64U) *10U ) / i2s_audiosample);
        }
    }
    /* remove the floating point */
    temp = (temp + 5U) / 10U;
    temp_of = (temp & 0x00000001U);
    temp_div = ((temp - temp_of) / 2U);
    temp_of = (temp_of << 8);

    /* set the default values */
    if((temp_div< 2U) || (temp_div > 255U)){
        temp_div = 2U;
        temp_of = 0U;
    }

    /* configure SPI_I2SPSC */
    SPI_I2SPSC(spi_periph) = (uint32_t)(temp_div | temp_of | i2s_mckout);

    /* clear SPI_I2SCTL_DTLEN and SPI_I2SCTL_CHLEN bits */
    SPI_I2SCTL(spi_periph) &= (uint32_t)(~(SPI_I2SCTL_DTLEN|SPI_I2SCTL_CHLEN));
    /* configure data frame format */
    SPI_I2SCTL(spi_periph) |= (uint32_t)i2s_frameformat;
}

/*!
    \brief      I2S parameter configuration
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4)
    \param[in]  i2s_mode: 
      \arg        I2S_MODE_SLAVETX : I2S slave transmit mode
      \arg        I2S_MODE_SLAVERX : I2S slave receive mode
      \arg        I2S_MODE_MASTERTX : I2S master transmit mode
      \arg        I2S_MODE_MASTERRX : I2S master receive mode
    \param[in]  i2s_std: 
      \arg        I2S_STD_PHILLIPS : I2S phillips standard
      \arg        I2S_STD_MSB : I2S MSB standard
      \arg        I2S_STD_LSB : I2S LSB standard
      \arg        I2S_STD_PCMSHORT : I2S PCM short standard
      \arg        I2S_STD_PCMLONG : I2S PCM long standard
    \param[in]  i2s_ckpl: 
      \arg        I2S_CKPL_LOW : I2S clock polarity low level
      \arg        I2S_CKPL_HIGH : I2S clock polarity high level
    \param[out] none
    \retval     none
*/
void i2s_init(uint32_t spi_periph, uint32_t i2s_mode, uint32_t i2s_standard, uint32_t i2s_ckpl)
{
    uint32_t reg= 0U;
    reg = SPI_I2SCTL(spi_periph);
    reg &= I2S_INIT_MASK;

    /* enable I2S mode */
    reg |= (uint32_t)SPI_I2SCTL_I2SSEL; 
    /* select I2S mode */
    reg |= (uint32_t)i2s_mode;
    /* select I2S standard */
    reg |= (uint32_t)i2s_standard;
    /* select I2S polarity */
    reg |= (uint32_t)i2s_ckpl;

    /* write to SPI_I2SCTL register */
    SPI_I2SCTL(spi_periph) = (uint32_t)reg;
}

/*!
    \brief      I2S enable
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4)
    \param[out] none
    \retval     none
*/
void i2s_enable(uint32_t spi_periph)
{
    SPI_I2SCTL(spi_periph) |= (uint32_t)SPI_I2SCTL_I2SEN;
}

/*!
    \brief      I2S disable
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4)
    \param[out] none
    \retval     none
*/
void i2s_disable(uint32_t spi_periph)
{
    SPI_I2SCTL(spi_periph) &= (uint32_t)(~SPI_I2SCTL_I2SEN);
}

/*!
    \brief      SPI nss output enable
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[out] none
    \retval     none
*/
void spi_nss_output_enable(uint32_t spi_periph)
{
    SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_NSSDRV;
}

/*!
    \brief      SPI nss output disable
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[out] none
    \retval     none
*/
void spi_nss_output_disable(uint32_t spi_periph)
{
    SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_NSSDRV);
}

/*!
    \brief      SPI nss pin high level in software mode
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[out] none
    \retval     none
*/
void spi_nss_internal_high(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) |= (uint32_t)SPI_CTL0_SWNSS;
}

/*!
    \brief      SPI nss pin low level in software mode
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[out] none
    \retval     none
*/
void spi_nss_internal_low(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) &= (uint32_t)(~SPI_CTL0_SWNSS);
}

/*!
    \brief      SPI dma send or receive enable
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[in]  spi_dma: 
      \arg        SPI_DMA_TRANSMIT: enable DMA transmit
      \arg        SPI_DMA_RECEIVE: enable DMA receive
    \param[out] none
    \retval     none
*/
void spi_dma_enable(uint32_t spi_periph, uint8_t spi_dma)
{
    if(SPI_DMA_TRANSMIT == spi_dma){
        SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_DMATEN;
    }else{
        SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_DMAREN;
    }
}

/*!
    \brief      SPI dma send or receive diable
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[in]  spi_dma: 
      \arg        SPI_DMA_TRANSMIT: disable DMA transmit
      \arg        SPI_DMA_RECEIVE: disable DMA receive
    \param[out] none
    \retval     none
*/
void spi_dma_disable(uint32_t spi_periph, uint8_t spi_dma)
{
    if(SPI_DMA_TRANSMIT == spi_dma){
        SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_DMATEN);
    }else{
        SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_DMAREN);
    }
}

/*!
    \brief      configure SPI/I2S data frame format
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[in]  frame_format: 
      \arg        SPI_FRAMESIZE_16BIT: SPI frame size is 16 bits
      \arg        SPI_FRAMESIZE_8BIT: SPI frame size is 8 bits
    \param[out] none
    \retval     none
*/
void spi_i2s_data_frame_format_config(uint32_t spi_periph, uint16_t frame_format)
{
    /* clear SPI_CTL0_FF16 bit */
    SPI_CTL0(spi_periph) &= (uint32_t)(~SPI_CTL0_FF16);
    /* confige SPI_CTL0_FF16 bit */
    SPI_CTL0(spi_periph) |= (uint32_t)frame_format;
}

/*!
    \brief      SPI transmit data
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[in]  data: 16-bit data
    \param[out] none
    \retval     none
*/
void spi_i2s_data_transmit(uint32_t spi_periph, uint16_t data)
{
    SPI_DATA(spi_periph) = (uint32_t)data;
}

/*!
    \brief      receive data
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[out] none
    \retval     16-bit data
*/
uint16_t spi_i2s_data_receive(uint32_t spi_periph)
{
    return ((uint16_t)SPI_DATA(spi_periph));
}

/*!
    \brief      configure SPI bidirectional transfer direction
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[in]  transfer_direction:
      \arg        SPI_BIDIRECTIONAL_TEANSMIT: SPI work in transmit-only mode
      \arg        SPI_BIDIRECTIONAL_RECEIVE: SPI work in receive-only mode
    \retval     none
*/
void spi_bidirectional_transfer_config(uint32_t spi_periph, uint32_t transfer_direction)
{
    if(SPI_BIDIRECTIONAL_TEANSMIT == transfer_direction){
        /* set the transmit only mode */
        SPI_CTL0(spi_periph) |= (uint32_t)SPI_BIDIRECTIONAL_TEANSMIT;
    }else{
        /* set the receive only mode */
        SPI_CTL0(spi_periph) &= SPI_BIDIRECTIONAL_RECEIVE;
    }
}

/*!
    \brief      SPI and I2S interrupt enable
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[in]  spi_i2s_int:
      \arg        SPI_I2S_INT_TBE: transmit buffer empty interrupt
      \arg        SPI_I2S_INT_RBNE: receive buffer not empty interrupt
      \arg        SPI_I2S_INT_ERR: CRC error,configuration error,reception overrun error,
                                   transmission underrun error and format error interrupt
    \param[out] none
    \retval     none
*/
void spi_i2s_interrupt_enable(uint32_t spi_periph, uint8_t spi_i2s_int)
{
    switch(spi_i2s_int){
    case SPI_I2S_INT_TBE:
        SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_TBEIE;
        break;
    case SPI_I2S_INT_RBNE:
        SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_RBNEIE;
        break;
    case SPI_I2S_INT_ERR:
        SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_ERRIE;
        break;
    default:
        break;
    }
}

/*!
    \brief      SPI and I2S interrupt disable
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[in]  spi_i2s_int:
      \arg        SPI_I2S_INT_TBE: transmit buffer empty interrupt
      \arg        SPI_I2S_INT_RBNE: receive buffer not empty interrupt
      \arg        SPI_I2S_INT_ERR: CRC error,configuration error,reception overrun error,
                                   transmission underrun error and format error interrupt
    \param[out] none
    \retval     none
*/
void spi_i2s_interrupt_disable(uint32_t spi_periph, uint8_t spi_i2s_int)
{
    switch(spi_i2s_int){
    case SPI_I2S_INT_TBE :
        SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_TBEIE);
        break;
    case SPI_I2S_INT_RBNE :
        SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_RBNEIE);
        break;
    case SPI_I2S_INT_ERR :
        SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_ERRIE);
        break;
    default :
        break;
    }
}

/*!
    \brief      get interrupt flag status
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[in]  spi_i2s_int:
      \arg        SPI_I2S_INT_TBE: transmit buffer empty interrupt
      \arg        SPI_I2S_INT_RBNE: receive buffer not empty interrupt
      \arg        SPI_I2S_INT_RXORERR: overrun interrupt
      \arg        SPI_INT_CONFERR: config error interrupt
      \arg        SPI_INT_CRCERR: CRC error interrupt
      \arg        I2S_INT_TXURERR: underrun error interrupt
      \arg        SPI_I2S_INT_FERR: format error interrupt
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus spi_i2s_interrupt_flag_get(uint32_t spi_periph, uint8_t spi_i2s_int)
{
    uint32_t reg1 = SPI_STAT(spi_periph);
    uint32_t reg2 = SPI_CTL1(spi_periph);
    
    uint32_t temp1 = 0U;
    uint32_t temp2 = 0U;

    switch(spi_i2s_int){
    case SPI_I2S_INT_TBE :
        temp1 = reg1 & SPI_STAT_TBE;
        temp2 = reg2 & SPI_CTL1_TBEIE;
        break;
    case SPI_I2S_INT_RBNE :
        temp1 = reg1 & SPI_STAT_RBNE;
        temp2 = reg2 & SPI_CTL1_RBNEIE;
        break;
    case SPI_I2S_INT_RXORERR :
        temp1 = reg1 & SPI_STAT_RXORERR;
        temp2 = reg2 & SPI_CTL1_ERRIE;
        break;
    case SPI_INT_CONFERR :
        temp1 = reg1 & SPI_STAT_CONFERR;
        temp2 = reg2 & SPI_CTL1_ERRIE;
        break;
    case SPI_INT_CRCERR :
        temp1 = reg1 & SPI_STAT_CRCERR;
        temp2 = reg2 & SPI_CTL1_ERRIE;
        break;
    case I2S_INT_TXURERR :
        temp1 = reg1 & SPI_STAT_TXURERR;
        temp2 = reg2 & SPI_CTL1_ERRIE;
        break;
    case SPI_I2S_INT_FERR :
        temp1 = reg1 & SPI_STAT_FERR;
        temp2 = reg2 & SPI_CTL1_ERRIE;
        break;
    default :
        break;
    }

    if(temp1 && temp2){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      get flag status
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[in]  spi_i2s_flag:
      \arg        SPI_FLAG_TBE: transmit buffer empty flag
      \arg        SPI_FLAG_RBNE: receive buffer not empty flag
      \arg        SPI_FLAG_TRANS: transmit on-going flag
      \arg        SPI_FLAG_RXORERR: receive Overrun flag
      \arg        SPI_FLAG_CONFERR: mode config error flag
      \arg        SPI_FLAG_CRCERR: CRC error flag
      \arg        SPI_FLAG_FERR: format error interrupt flag
      \arg        I2S_FLAG_TBE: transmit buffer empty flag
      \arg        I2S_FLAG_RBNE: receive buffer not empty flag
      \arg        I2S_FLAG_TRANS: transmit on-going flag
      \arg        I2S_FLAG_RXORERR: overrun flag
      \arg        I2S_FLAG_TXURERR: underrun error flag
      \arg        I2S_FLAG_CH: channel side flag
      \arg        I2S_FLAG_FERR: format error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus spi_i2s_flag_get(uint32_t spi_periph, uint32_t spi_i2s_flag)
{
    if(SPI_STAT(spi_periph) & spi_i2s_flag){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear SPI CRC error flag status
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[out] none
    \retval     none
*/
void spi_crc_error_clear(uint32_t spi_periph)
{
    SPI_STAT(spi_periph) &= (uint32_t)(~SPI_FLAG_CRCERR);
}

/*!
    \brief      CRC function turn on
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[out] none
    \retval     none
*/
void spi_crc_on(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) |= (uint32_t)SPI_CTL0_CRCEN;
}

/*!
    \brief      CRC function turn off
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[out] none
    \retval     none
*/
void spi_crc_off(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) &= (uint32_t)(~SPI_CTL0_CRCEN);
}

/*!
    \brief      CRC polynomial set
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[in]  crc_poly: CRC polynomial value
    \param[out] none
    \retval     none
*/
void spi_crc_polynomial_set(uint32_t spi_periph,uint16_t crc_poly)
{
    /* enable SPI CRC */
    SPI_CTL0(spi_periph) |= (uint32_t)SPI_CTL0_CRCEN;

    /* set SPI CRC polynomial */
    SPI_CRCPOLY(spi_periph) = (uint32_t)crc_poly;
}

/*!
    \brief      get SPI CRC polynomial 
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[out] none
    \retval     16-bit CRC polynomial
*/
uint16_t spi_crc_polynomial_get(uint32_t spi_periph)
{
    return ((uint16_t)SPI_CRCPOLY(spi_periph));
}

/*!
    \brief      SPI next data is CRC value
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[out] none
    \retval     none
*/
void spi_crc_next(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) |= (uint32_t)SPI_CTL0_CRCNT;
}

/*!
    \brief      get SPI CRC send value or receive value
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[in]  spi_crc: 
      \arg        SPI_CRC_TX: get transmit crc value
      \arg        SPI_CRC_RX: get receive crc value
    \param[out] none
    \retval     16-bit CRC value
*/
uint16_t spi_crc_get(uint32_t spi_periph,uint8_t spi_crc)
{
    if(SPI_CRC_TX == spi_crc){
        return ((uint16_t)(SPI_TCRC(spi_periph)));
    }else{
        return ((uint16_t)(SPI_RCRC(spi_periph)));
    }
}

/*!
    \brief      enable SPI TI mode
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[out] none
    \retval     none
*/
void spi_ti_mode_enable(uint32_t spi_periph)
{
    SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_TMOD;
}

/*!
    \brief      disable SPI TI mode
    \param[in]  spi_periph: SPIx(x=0,1,2,3,4,5)
    \param[out] none
    \retval     none
*/
void spi_ti_mode_disable(uint32_t spi_periph)
{
    SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_TMOD);
}

/*!
    \brief      configure i2s full duplex mode
    \param[in]  i2s_add_periph: I2Sx_ADD(x=1,2)
    \param[in]  i2s_mode: 
      \arg        I2S_MODE_SLAVETX : I2S slave transmit mode
      \arg        I2S_MODE_SLAVERX : I2S slave receive mode
      \arg        I2S_MODE_MASTERTX : I2S master transmit mode
      \arg        I2S_MODE_MASTERRX : I2S master receive mode
    \param[in]  i2s_standard: 
      \arg        I2S_STD_PHILLIPS : I2S phillips standard
      \arg        I2S_STD_MSB : I2S MSB standard
      \arg        I2S_STD_LSB : I2S LSB standard
      \arg        I2S_STD_PCMSHORT : I2S PCM short standard
      \arg        I2S_STD_PCMLONG : I2S PCM long standard
    \param[in]  i2s_ckpl: 
      \arg        I2S_CKPL_LOW : I2S clock polarity low level
      \arg        I2S_CKPL_HIGH : I2S clock polarity high level
    \param[in]  i2s_frameformat:
      \arg        I2S_FRAMEFORMAT_DT16B_CH16B: I2S data length is 16 bit and channel length is 16 bit
      \arg        I2S_FRAMEFORMAT_DT16B_CH32B: I2S data length is 16 bit and channel length is 32 bit
      \arg        I2S_FRAMEFORMAT_DT24B_CH32B: I2S data length is 24 bit and channel length is 32 bit
      \arg        I2S_FRAMEFORMAT_DT32B_CH32B: I2S data length is 32 bit and channel length is 32 bit
    \param[out] none
    \retval     none
*/
void i2s_full_duplex_mode_config(uint32_t i2s_add_periph, uint32_t i2s_mode, uint32_t i2s_standard,
                                 uint32_t i2s_ckpl, uint32_t i2s_frameformat)
{
    uint32_t reg = 0U, tmp = 0U;

    reg = I2S_ADD_I2SCTL(i2s_add_periph);
    reg &= I2S_FULL_DUPLEX_MASK;  

    /* get the mode of the extra I2S module I2Sx_ADD */
    if((I2S_MODE_MASTERTX == i2s_mode) || (I2S_MODE_SLAVETX == i2s_mode)){
        tmp = I2S_MODE_SLAVERX;
    }else{
        tmp = I2S_MODE_SLAVETX;
    }

    /* enable I2S mode */
    reg |= (uint32_t)SPI_I2SCTL_I2SSEL; 
    /* select I2S mode */
    reg |= (uint32_t)tmp;
    /* select I2S standard */
    reg |= (uint32_t)i2s_standard;
    /* select I2S polarity */
    reg |= (uint32_t)i2s_ckpl;
    /* configure data frame format */
    reg |= (uint32_t)i2s_frameformat;

    /* write to SPI_I2SCTL register */
    I2S_ADD_I2SCTL(i2s_add_periph) = (uint32_t)reg;
}

/*!
    \brief      quad wire SPI enable 
    \param[in]  spi_periph: SPIx(only x=5)
    \param[out] none
    \retval     none
*/
void qspi_enable(uint32_t spi_periph)
{
    SPI_QCTL(spi_periph) |= (uint32_t)SPI_QCTL_QMOD;
}

/*!
    \brief      quad wire SPI disable
    \param[in]  spi_periph: SPIx(only x=5)
    \param[out] none
    \retval     none
*/
void qspi_disable(uint32_t spi_periph)
{
    SPI_QCTL(spi_periph) &= (uint32_t)(~SPI_QCTL_QMOD);
}

/*!
    \brief      quad wire SPI write enable
    \param[in]  spi_periph: SPIx(only x=5)
    \param[out] none
    \retval     none
*/
void qspi_write_enable(uint32_t spi_periph)
{
    SPI_QCTL(spi_periph) &= (uint32_t)(~SPI_QCTL_QRD);
}

/*!
    \brief      quad wire SPI read enable
    \param[in]  spi_periph: SPIx(only x=5)
    \param[out] none
    \retval     none
*/
void qspi_read_enable(uint32_t spi_periph)
{
    SPI_QCTL(spi_periph) |= (uint32_t)SPI_QCTL_QRD;
}

/*!
    \brief      SPI_IO2 and SPI_IO3 pin output enable
    \param[in]  spi_periph: SPIx(only x=5)
    \param[out] none
    \retval     none
*/
void qspi_io23_output_enable(uint32_t spi_periph)
{
    SPI_QCTL(spi_periph) |= (uint32_t)SPI_QCTL_IO23_DRV;
}

 /*!
    \brief      SPI_IO2 and SPI_IO3 pin output disable
    \param[in]  spi_periph: SPIx(only x=5)
    \param[out] none
    \retval     none
*/
 void qspi_io23_output_disable(uint32_t spi_periph)
{
    SPI_QCTL(spi_periph) &= (uint32_t)(~SPI_QCTL_IO23_DRV);
}
