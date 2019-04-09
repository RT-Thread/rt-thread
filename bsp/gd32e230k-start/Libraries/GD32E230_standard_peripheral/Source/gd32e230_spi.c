/*!
    \file    gd32e230_spi.c
    \brief   SPI driver
    
    \version 2018-06-19, V1.0.0, firmware for GD32E230
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

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

#include "gd32e230_spi.h"

/* SPI/I2S parameter initialization mask */
#define SPI_INIT_MASK                        ((uint32_t)0x00003040U)  /*!< SPI0 parameter initialization mask */
#define SPI_FIFO_INIT_MASK1                  ((uint32_t)0x00003840U)  /*!< SPI1 parameter initialization mask1 */
#define SPI_FIFO_INIT_MASK2                  ((uint32_t)0x0000F0FFU)  /*!< SPI1 parameter initialization mask2*/
#define I2S_INIT_MASK                        ((uint32_t)0x0000F047U)  /*!< I2S parameter initialization mask */

#define SPI_FRAMESIZE_MASK                   ((uint32_t)0x00000800U)  /*!< SPI0 frame size mask */
#define SPI_BYTEN_MASK                       ((uint32_t)0x00001000U)  /*!< SPI1 access to FIFO mask */
#define SPI_TXLVL_EMPTY_MASK                 ((uint32_t)0x00001800U)  /*!< SPI1 TXFIFO empty mask */
#define SPI_RXLVL_EMPTY_MASK                 ((uint32_t)0x00000600U)  /*!< SPI1 RXFIFO empty mask */

/* I2S clock source selection, multiplication and division mask */
#define SPI_I2SPSC_RESET                     ((uint32_t)0x00000002U)  /*!< I2S clock prescaler register reset value */

/*!
    \brief      reset SPI and I2S 
    \param[in]  spi_periph: SPIx(x=0,1)
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
        /* reset SPI1 */
        rcu_periph_reset_enable(RCU_SPI1RST);
        rcu_periph_reset_disable(RCU_SPI1RST);
        break;
    default :
        break;
    }
}

/*!
    \brief      initialize the parameters of SPI struct with the default values
    \param[in]  spi_struct: SPI parameter stuct
    \param[out] none
    \retval     none
*/
void spi_struct_para_init(spi_parameter_struct* spi_struct)
{
    /* set the SPI struct with the default values */
    spi_struct->device_mode = SPI_SLAVE;
    spi_struct->trans_mode = SPI_TRANSMODE_FULLDUPLEX;
    spi_struct->frame_size = SPI_FRAMESIZE_8BIT;
    spi_struct->nss = SPI_NSS_HARD;
    spi_struct->clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
    spi_struct->prescale = SPI_PSC_2;
}

/*!
    \brief      initialize SPI parameter
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[in]  spi_struct: SPI parameter initialization stuct members of the structure 
                            and the member values are shown as below:
                  device_mode: SPI_MASTER, SPI_SLAVE
                  trans_mode: SPI_TRANSMODE_FULLDUPLEX, SPI_TRANSMODE_RECEIVEONLY,
                              SPI_TRANSMODE_BDRECEIVE, SPI_TRANSMODE_BDTRANSMIT
                  frame_size: SPI_FRAMESIZE_4BIT, SPI_FRAMESIZE_5BIT
                              SPI_FRAMESIZE_6BIT, SPI_FRAMESIZE_7BIT
                              SPI_FRAMESIZE_8BIT, SPI_FRAMESIZE_9BIT
                              SPI_FRAMESIZE_10BIT, SPI_FRAMESIZE_11BIT
                              SPI_FRAMESIZE_12BIT, SPI_FRAMESIZE_13BIT
                              SPI_FRAMESIZE_14BIT, SPI_FRAMESIZE_15BIT
                              SPI_FRAMESIZE_16BIT
                  nss: SPI_NSS_SOFT, SPI_NSS_HARD
                  endian: SPI_ENDIAN_MSB, SPI_ENDIAN_LSB
                  clock_polarity_phase: SPI_CK_PL_LOW_PH_1EDGE, SPI_CK_PL_HIGH_PH_1EDGE
                                        SPI_CK_PL_LOW_PH_2EDGE, SPI_CK_PL_HIGH_PH_2EDGE
                  prescale: SPI_PSC_n (n=2,4,8,16,32,64,128,256)
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus spi_init(uint32_t spi_periph, spi_parameter_struct* spi_struct)
{   
    uint32_t reg1, reg2, reg3 = 0U;
    
    reg1 = SPI_CTL0(spi_periph);
    reg1 &= SPI_INIT_MASK;
    
    reg2 = SPI_CTL0(spi_periph);
    reg2 &= SPI_FIFO_INIT_MASK1;

    reg3 = SPI_CTL1(spi_periph);
    reg3 &= SPI_FIFO_INIT_MASK2;

    if( SPI0 == spi_periph){
        /* select SPI as master or slave */
        reg1 |= spi_struct->device_mode;
        /* select SPI transfer mode */
        reg1 |= spi_struct->trans_mode;
        /* select SPI NSS use hardware or software */
        reg1 |= spi_struct->nss;
        /* select SPI LSB or MSB */
        reg1 |= spi_struct->endian;
        /* select SPI polarity and phase */
        reg1 |= spi_struct->clock_polarity_phase;
        /* select SPI prescale to adjust transmit speed */
        reg1 |= spi_struct->prescale;
        /* select SPI frame size */
        /* check SPI0 frame size is 8bits/16bits or not*/
        if((SPI_FRAMESIZE_8BIT != spi_struct->frame_size) && (SPI_FRAMESIZE_16BIT != spi_struct->frame_size))
        {
            return ERROR;
        }else{
            reg1 |= (spi_struct->frame_size & SPI_FRAMESIZE_MASK);
        }
        
        /* write to SPI_CTL0 register */
        SPI_CTL0(spi_periph) = (uint32_t)reg1;
    
    }else{
        /* select SPI as master or slave */
        reg2 |= spi_struct->device_mode;
        /* select SPI transfer mode */
        reg2 |= spi_struct->trans_mode;
        /* select SPI NSS use hardware or software */
        reg2 |= spi_struct->nss;
        /* select SPI LSB or MSB */
        reg2 |= spi_struct->endian;
        /* select SPI polarity and phase */
        reg2 |= spi_struct->clock_polarity_phase;
        /* select SPI prescale to adjust transmit speed */
        reg2 |= spi_struct->prescale;
        /* write to SPI_CTL0 register */
        SPI_CTL0(spi_periph) = (uint32_t)reg2;

        /* select SPI data size */
        reg3 |= spi_struct->frame_size;
        /* write to SPI_CTL0 register */
        SPI_CTL1(spi_periph) = (uint32_t)reg3;
    }
    
    /* select SPI mode */
    SPI_I2SCTL(spi_periph) &= (uint32_t)(~SPI_I2SCTL_I2SSEL);
    
    return SUCCESS;
}

/*!
    \brief      enable SPI
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[out] none
    \retval     none
*/
void spi_enable(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) |= (uint32_t)SPI_CTL0_SPIEN;
}

/*!
    \brief      disable SPI 
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[out] none
    \retval     none
*/
void spi_disable(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) &= (uint32_t)(~SPI_CTL0_SPIEN);
}

/*!
    \brief      initialize I2S parameter 
    \param[in]  spi_periph: SPIx(x=0)
    \param[in]  mode: I2S operation mode
                only one parameter can be selected which is shown as below:
      \arg        I2S_MODE_SLAVETX: I2S slave transmit mode
      \arg        I2S_MODE_SLAVERX: I2S slave receive mode
      \arg        I2S_MODE_MASTERTX: I2S master transmit mode
      \arg        I2S_MODE_MASTERRX: I2S master receive mode
    \param[in]  standard: I2S standard
                only one parameter can be selected which is shown as below:
      \arg        I2S_STD_PHILLIPS: I2S phillips standard
      \arg        I2S_STD_MSB: I2S MSB standard
      \arg        I2S_STD_LSB: I2S LSB standard
      \arg        I2S_STD_PCMSHORT: I2S PCM short standard
      \arg        I2S_STD_PCMLONG: I2S PCM long standard
    \param[in]  ckpl: I2S idle state clock polarity
                only one parameter can be selected which is shown as below:
      \arg        I2S_CKPL_LOW: I2S clock polarity low level
      \arg        I2S_CKPL_HIGH: I2S clock polarity high level
    \param[out] none
    \retval     none
*/
void i2s_init(uint32_t spi_periph, uint32_t mode, uint32_t standard, uint32_t ckpl)
{
    uint32_t reg = 0U;
    reg = SPI_I2SCTL(spi_periph);
    reg &= I2S_INIT_MASK;

    /* enable I2S mode */
    reg |= (uint32_t)SPI_I2SCTL_I2SSEL; 
    /* select I2S mode */
    reg |= (uint32_t)mode;
    /* select I2S standard */
    reg |= (uint32_t)standard;
    /* select I2S polarity */
    reg |= (uint32_t)ckpl;

    /* write to SPI_I2SCTL register */
    SPI_I2SCTL(spi_periph) = (uint32_t)reg;
}

/*!
    \brief      configure I2S prescaler 
    \param[in]  spi_periph: SPIx(x=0)
    \param[in]  audiosample: I2S audio sample rate
                only one parameter can be selected which is shown as below:
      \arg        I2S_AUDIOSAMPLE_8K: audio sample rate is 8KHz
      \arg        I2S_AUDIOSAMPLE_11K: audio sample rate is 11KHz
      \arg        I2S_AUDIOSAMPLE_16K: audio sample rate is 16KHz
      \arg        I2S_AUDIOSAMPLE_22K: audio sample rate is 22KHz
      \arg        I2S_AUDIOSAMPLE_32K: audio sample rate is 32KHz
      \arg        I2S_AUDIOSAMPLE_44K: audio sample rate is 44KHz
      \arg        I2S_AUDIOSAMPLE_48K: audio sample rate is 48KHz
      \arg        I2S_AUDIOSAMPLE_96K: audio sample rate is 96KHz
      \arg        I2S_AUDIOSAMPLE_192K: audio sample rate is 192KHz
    \param[in]  frameformat: I2S data length and channel length
                only one parameter can be selected which is shown as below:
      \arg        I2S_FRAMEFORMAT_DT16B_CH16B: I2S data length is 16 bit and channel length is 16 bit
      \arg        I2S_FRAMEFORMAT_DT16B_CH32B: I2S data length is 16 bit and channel length is 32 bit
      \arg        I2S_FRAMEFORMAT_DT24B_CH32B: I2S data length is 24 bit and channel length is 32 bit
      \arg        I2S_FRAMEFORMAT_DT32B_CH32B: I2S data length is 32 bit and channel length is 32 bit
    \param[in]  mckout: I2S master clock output
                only one parameter can be selected which is shown as below:
      \arg        I2S_MCKOUT_ENABLE: I2S master clock output enable
      \arg        I2S_MCKOUT_DISABLE: I2S master clock output disable
    \param[out] none
    \retval     none
*/
void i2s_psc_config(uint32_t spi_periph, uint32_t audiosample, uint32_t frameformat, uint32_t mckout)
{
    uint32_t i2sdiv = 2U, i2sof = 0U;
    uint32_t clks = 0U;
    uint32_t i2sclock = 0U;

    /* deinit SPI_I2SPSC register */
    SPI_I2SPSC(spi_periph) = SPI_I2SPSC_RESET;

    /* get system clock */
    i2sclock = rcu_clock_freq_get(CK_SYS);
    
    /* config the prescaler depending on the mclk output state, the frame format and audio sample rate */
    if(I2S_MCKOUT_ENABLE == mckout){
        clks = (uint32_t)(((i2sclock / 256U) * 10U) / audiosample);
    }else{
        if(I2S_FRAMEFORMAT_DT16B_CH16B == frameformat){
            clks = (uint32_t)(((i2sclock / 32U) *10U ) / audiosample);
        }else{
            clks = (uint32_t)(((i2sclock / 64U) *10U ) / audiosample);
        }
    }
    
    /* remove the floating point */
    clks = (clks + 5U) / 10U;
    i2sof = (clks & 0x00000001U);
    i2sdiv = ((clks - i2sof) / 2U);
    i2sof  = (i2sof << 8U);

    /* set the default values */
    if((i2sdiv < 2U) || (i2sdiv > 255U)){
        i2sdiv = 2U;
        i2sof = 0U;
    }

    /* configure SPI_I2SPSC */
    SPI_I2SPSC(spi_periph) = (uint32_t)(i2sdiv | i2sof | mckout);

    /* clear SPI_I2SCTL_DTLEN and SPI_I2SCTL_CHLEN bits */
    SPI_I2SCTL(spi_periph) &= (uint32_t)(~(SPI_I2SCTL_DTLEN | SPI_I2SCTL_CHLEN));
    /* configure data frame format */
    SPI_I2SCTL(spi_periph) |= (uint32_t)frameformat;
}


/*!
    \brief      enable I2S 
    \param[in]  spi_periph: SPIx(x=0)
    \param[out] none
    \retval     none
*/
void i2s_enable(uint32_t spi_periph)
{
    SPI_I2SCTL(spi_periph) |= (uint32_t)SPI_I2SCTL_I2SEN;
}

/*!
    \brief      disable I2S 
    \param[in]  spi_periph: SPIx(x=0)
    \param[out] none
    \retval     none
*/
void i2s_disable(uint32_t spi_periph)
{
    SPI_I2SCTL(spi_periph) &= (uint32_t)(~SPI_I2SCTL_I2SEN);
}

/*!
    \brief      enable SPI NSS output 
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[out] none
    \retval     none
*/
void spi_nss_output_enable(uint32_t spi_periph)
{
    SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_NSSDRV;
}

/*!
    \brief      disable SPI NSS output 
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[out] none
    \retval     none
*/
void spi_nss_output_disable(uint32_t spi_periph)
{
    SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_NSSDRV);
}

/*!
    \brief      SPI NSS pin high level in software mode
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[out] none
    \retval     none
*/
void spi_nss_internal_high(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) |= (uint32_t)SPI_CTL0_SWNSS;
}

/*!
    \brief      SPI NSS pin low level in software mode
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[out] none
    \retval     none
*/
void spi_nss_internal_low(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) &= (uint32_t)(~SPI_CTL0_SWNSS);
}

/*!
    \brief      enable SPI DMA send or receive 
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[in]  dma: SPI DMA mode
                only one parameter can be selected which is shown as below:
      \arg        SPI_DMA_TRANSMIT: SPI transmit data using DMA
      \arg        SPI_DMA_RECEIVE: SPI receive data using DMA
    \param[out] none
    \retval     none
*/
void spi_dma_enable(uint32_t spi_periph, uint8_t dma)
{
    if(SPI_DMA_TRANSMIT == dma){
        SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_DMATEN;
    }else{
        SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_DMAREN;
    }
}

/*!
    \brief      disable SPI DMA send or receive 
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[in]  dma: SPI DMA mode
                only one parameter can be selected which is shown as below:
      \arg        SPI_DMA_TRANSMIT: SPI transmit data using DMA
      \arg        SPI_DMA_RECEIVE: SPI receive data using DMA
    \param[out] none
    \retval     none
*/
void spi_dma_disable(uint32_t spi_periph, uint8_t dma)
{
    if(SPI_DMA_TRANSMIT == dma){
        SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_DMATEN);
    }else{
        SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_DMAREN);
    }
}

/*!
    \brief      configure SPI/I2S data frame format
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[in]  frame_format: SPI frame size
                only one parameter can be selected which is shown as below:
      \arg        SPI_FRAMESIZE_4BIT: SPI frame size is 4 bits
      \arg        SPI_FRAMESIZE_5BIT: SPI frame size is 5 bits
      \arg        SPI_FRAMESIZE_6BIT: SPI frame size is 6 bits
      \arg        SPI_FRAMESIZE_7BIT: SPI frame size is 7 bits
      \arg        SPI_FRAMESIZE_8BIT: SPI frame size is 8 bits
      \arg        SPI_FRAMESIZE_9BIT: SPI frame size is 9 bits
      \arg        SPI_FRAMESIZE_10BIT: SPI frame size is 10 bits
      \arg        SPI_FRAMESIZE_11BIT: SPI frame size is 11 bits
      \arg        SPI_FRAMESIZE_12BIT: SPI frame size is 12 bits
      \arg        SPI_FRAMESIZE_13BIT: SPI frame size is 13 bits
      \arg        SPI_FRAMESIZE_14BIT: SPI frame size is 14 bits
      \arg        SPI_FRAMESIZE_15BIT: SPI frame size is 15 bits
      \arg        SPI_FRAMESIZE_16BIT: SPI frame size is 16 bits
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus spi_i2s_data_frame_format_config(uint32_t spi_periph, uint16_t frame_format)
{
    if(SPI0 == spi_periph)
    {
        /* check SPI0 frame size is 8bits/16bits or not*/
        if((SPI_FRAMESIZE_8BIT != frame_format) && (SPI_FRAMESIZE_16BIT != frame_format))
        {
            return ERROR;
        }else{
            /* clear SPI_CTL0_FF16 bit */
            SPI_CTL0(spi_periph) &= (uint32_t)(~SPI_CTL0_FF16);
            /* configure SPI_CTL0_FF16 bit */
            SPI_CTL0(spi_periph) |= ((uint32_t)frame_format & SPI_FRAMESIZE_MASK);
        }
    }
    else{
        /* clear SPI_CTL1_DZ bits */
        SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_DZ);
        /* confige SPI_CTL1_DZ bits */
        SPI_CTL1(spi_periph) |= (uint32_t)frame_format;
    }
    return SUCCESS;
}

/*!
    \brief      SPI transmit data
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[in]  data: 16-bit data
    \param[out] none
    \retval     none
*/
void spi_i2s_data_transmit(uint32_t spi_periph, uint16_t data)
{
    uint32_t reg, byten;
    if(SPI0 == spi_periph)
    {
        SPI_DATA(spi_periph) = (uint32_t)data;
    }
    else
    {
        /* get the access size to FIFO */
        byten = SPI_CTL1(spi_periph) & SPI_BYTEN_MASK;
        if(RESET != byten)
        {
            reg = spi_periph + 0x0CU;
            *( uint8_t *)(reg) = (uint8_t)data;
        }else
        {
            SPI_DATA(spi_periph) = (uint16_t)data;
        }
    }
}

/*!
    \brief      SPI receive data
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[out] none
    \retval     16-bit data
*/
uint16_t spi_i2s_data_receive(uint32_t spi_periph)
{
    uint32_t reg, byten;
    if(SPI0 == spi_periph)
    {
        return ((uint16_t)SPI_DATA(spi_periph));
    }
    else
    {
        /* get the access size to FIFO */
        byten = SPI_CTL1(spi_periph) & SPI_BYTEN_MASK;
        if(RESET != byten)
        {
            reg = spi_periph + 0x0CU;
            return (uint16_t)(*(uint8_t *)(reg));
        }else
        {
            return ((uint16_t)SPI_DATA(spi_periph));
        }
    }
}

/*!
    \brief      configure SPI bidirectional transfer direction
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[in]  transfer_direction: SPI transfer direction
                only one parameter can be selected which is shown as below:
      \arg        SPI_BIDIRECTIONAL_TRANSMIT: SPI work in transmit-only mode
      \arg        SPI_BIDIRECTIONAL_RECEIVE: SPI work in receive-only mode
    \param[out] none
    \retval     none
*/
void spi_bidirectional_transfer_config(uint32_t spi_periph, uint32_t transfer_direction)
{
    if(SPI_BIDIRECTIONAL_TRANSMIT == transfer_direction){
        /* set the transmit-only mode */
        SPI_CTL0(spi_periph) |= (uint32_t)SPI_BIDIRECTIONAL_TRANSMIT;
    }else{
        /* set the receive-only mode */
        SPI_CTL0(spi_periph) &= SPI_BIDIRECTIONAL_RECEIVE;
    }
}

/*!
    \brief      set SPI CRC polynomial 
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[in]  crc_poly: CRC polynomial value
    \param[out] none
    \retval     none
*/
void spi_crc_polynomial_set(uint32_t spi_periph, uint16_t crc_poly)
{
    /* enable SPI CRC */
    SPI_CTL0(spi_periph) |= (uint32_t)SPI_CTL0_CRCEN;
    /* set SPI CRC polynomial */
    SPI_CRCPOLY(spi_periph) = (uint32_t)crc_poly;
}

/*!
    \brief      get SPI CRC polynomial 
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[out] none
    \retval     16-bit CRC polynomial
*/
uint16_t spi_crc_polynomial_get(uint32_t spi_periph)
{
    return ((uint16_t)SPI_CRCPOLY(spi_periph));
}

/*!
    \brief      turn on CRC function 
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[out] none
    \retval     none
*/
void spi_crc_on(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) |= (uint32_t)SPI_CTL0_CRCEN;
}

/*!
    \brief      turn off CRC function 
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[out] none
    \retval     none
*/
void spi_crc_off(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) &= (uint32_t)(~SPI_CTL0_CRCEN);
}

/*!
    \brief      SPI next data is CRC value
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[out] none
    \retval     none
*/
void spi_crc_next(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) |= (uint32_t)SPI_CTL0_CRCNT;
}

/*!
    \brief      get SPI CRC send value or receive value
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[in]  crc: SPI crc value
                only one parameter can be selected which is shown as below:
      \arg        SPI_CRC_TX: get transmit crc value
      \arg        SPI_CRC_RX: get receive crc value
    \param[out] none
    \retval     16-bit CRC value
*/
uint16_t spi_crc_get(uint32_t spi_periph, uint8_t crc)
{
    if(SPI_CRC_TX == crc){
        return ((uint16_t)(SPI_TCRC(spi_periph)));
    }else{
        return ((uint16_t)(SPI_RCRC(spi_periph)));
    }
}

/*!
    \brief      enable SPI TI mode
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[out] none
    \retval     none
*/
void spi_ti_mode_enable(uint32_t spi_periph)
{
    SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_TMOD;
}

/*!
    \brief      disable SPI TI mode
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[out] none
    \retval     none
*/
void spi_ti_mode_disable(uint32_t spi_periph)
{
    SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_TMOD);
}

/*!
    \brief      enable SPI NSS pulse mode
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[out] none
    \retval     none
*/
void spi_nssp_mode_enable(uint32_t spi_periph)
{
    SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_NSSP;
}

/*!
    \brief      disable SPI NSS pulse mode
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[out] none
    \retval     none
*/
void spi_nssp_mode_disable(uint32_t spi_periph)
{
    SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_NSSP);
}

/*!
    \brief      enable quad wire SPI
    \param[in]  spi_periph: SPIx(x=1)
    \param[out] none
    \retval     none
*/
void qspi_enable(uint32_t spi_periph)
{
    SPI_QCTL(spi_periph) |= (uint32_t)SPI_QCTL_QMOD;
}

/*!
    \brief      disable quad wire SPI 
    \param[in]  spi_periph: SPIx(x=1)
    \param[out] none
    \retval     none
*/
void qspi_disable(uint32_t spi_periph)
{
    SPI_QCTL(spi_periph) &= (uint32_t)(~SPI_QCTL_QMOD);
}

/*!
    \brief      enable quad wire SPI write 
    \param[in]  spi_periph: SPIx(x=1)
    \param[out] none
    \retval     none
*/
void qspi_write_enable(uint32_t spi_periph)
{
    SPI_QCTL(spi_periph) &= (uint32_t)(~SPI_QCTL_QRD);
}

/*!
    \brief      enable quad wire SPI read 
    \param[in]  spi_periph: SPIx(x=1)
    \param[out] none
    \retval     none
*/
void qspi_read_enable(uint32_t spi_periph)
{
    SPI_QCTL(spi_periph) |= (uint32_t)SPI_QCTL_QRD;
}

/*!
    \brief      enable SPI_IO2 and SPI_IO3 pin output 
    \param[in]  spi_periph: SPIx(x=1)
    \param[out] none
    \retval     none
*/
void qspi_io23_output_enable(uint32_t spi_periph)
{
    SPI_QCTL(spi_periph) |= (uint32_t)SPI_QCTL_IO23_DRV;
}

 /*!
    \brief      disable SPI_IO2 and SPI_IO3 pin output 
    \param[in]  spi_periph: SPIx(x=1)
    \param[out] none
    \retval     none
*/
 void qspi_io23_output_disable(uint32_t spi_periph)
{
    SPI_QCTL(spi_periph) &= (uint32_t)(~SPI_QCTL_IO23_DRV);
}

/*!
    \brief      enable SPI and I2S interrupt 
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[in]  interrupt: SPI/I2S interrupt
                only one parameter can be selected which is shown as below:
      \arg        SPI_I2S_INT_TBE: transmit buffer empty interrupt
      \arg        SPI_I2S_INT_RBNE: receive buffer not empty interrupt
      \arg        SPI_I2S_INT_ERR: CRC error,configuration error,reception overrun error,
                                   transmission underrun error and format error interrupt
    \param[out] none
    \retval     none
*/
void spi_i2s_interrupt_enable(uint32_t spi_periph, uint8_t interrupt)
{
    switch(interrupt){
    /* SPI/I2S transmit buffer empty interrupt */
    case SPI_I2S_INT_TBE:
        SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_TBEIE;
        break;
    /* SPI/I2S receive buffer not empty interrupt */
    case SPI_I2S_INT_RBNE:
        SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_RBNEIE;
        break;
    /* SPI/I2S error */
    case SPI_I2S_INT_ERR:
        SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_ERRIE;
        break;
    default:
        break;
    }
}

/*!
    \brief      disable SPI and I2S interrupt 
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[in]  interrupt: SPI/I2S interrupt
                only one parameter can be selected which is shown as below:
      \arg        SPI_I2S_INT_TBE: transmit buffer empty interrupt
      \arg        SPI_I2S_INT_RBNE: receive buffer not empty interrupt
      \arg        SPI_I2S_INT_ERR: CRC error,configuration error,reception overrun error,
                                   transmission underrun error and format error interrupt
    \param[out] none
    \retval     none
*/
void spi_i2s_interrupt_disable(uint32_t spi_periph, uint8_t interrupt)
{
    switch(interrupt){
    /* SPI/I2S transmit buffer empty interrupt */
    case SPI_I2S_INT_TBE:
        SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_TBEIE);
        break;
    /* SPI/I2S receive buffer not empty interrupt */
    case SPI_I2S_INT_RBNE:
        SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_RBNEIE);
        break;
    /* SPI/I2S error */
    case SPI_I2S_INT_ERR:
        SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_ERRIE);
        break;
    default :
        break;
    }
}

/*!
    \brief      get SPI and I2S interrupt flag status
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[in]  interrupt: SPI/I2S interrupt flag status
                only one parameter can be selected which is shown as below:
      \arg        SPI_I2S_INT_FLAG_TBE: transmit buffer empty interrupt flag
      \arg        SPI_I2S_INT_FLAG_RBNE: receive buffer not empty interrupt flag
      \arg        SPI_I2S_INT_FLAG_RXORERR: overrun interrupt flag
      \arg        SPI_INT_FLAG_CONFERR: config error interrupt flag
      \arg        SPI_INT_FLAG_CRCERR: CRC error interrupt flag
      \arg        I2S_INT_FLAG_TXURERR: underrun error interrupt flag
      \arg        SPI_I2S_INT_FLAG_FERR: format error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus spi_i2s_interrupt_flag_get(uint32_t spi_periph, uint8_t interrupt)
{
    uint32_t reg1 = SPI_STAT(spi_periph);
    uint32_t reg2 = SPI_CTL1(spi_periph);

    switch(interrupt){
    /* SPI/I2S transmit buffer empty interrupt */
    case SPI_I2S_INT_FLAG_TBE:
        reg1 = reg1 & SPI_STAT_TBE;
        reg2 = reg2 & SPI_CTL1_TBEIE;
        break;
    /* SPI/I2S receive buffer not empty interrupt */
    case SPI_I2S_INT_FLAG_RBNE:
        reg1 = reg1 & SPI_STAT_RBNE;
        reg2 = reg2 & SPI_CTL1_RBNEIE;
        break;
    /* SPI/I2S overrun interrupt */
    case SPI_I2S_INT_FLAG_RXORERR:
        reg1 = reg1 & SPI_STAT_RXORERR;
        reg2 = reg2 & SPI_CTL1_ERRIE;
        break;
    /* SPI config error interrupt */
    case SPI_INT_FLAG_CONFERR:
        reg1 = reg1 & SPI_STAT_CONFERR;
        reg2 = reg2 & SPI_CTL1_ERRIE;
        break;
    /* SPI CRC error interrupt */
    case SPI_INT_FLAG_CRCERR:
        reg1 = reg1 & SPI_STAT_CRCERR;
        reg2 = reg2 & SPI_CTL1_ERRIE;
        break;
    /* I2S underrun error interrupt */
    case I2S_INT_FLAG_TXURERR:
        reg1 = reg1 & SPI_STAT_TXURERR;
        reg2 = reg2 & SPI_CTL1_ERRIE;
        break;
    /* SPI/I2S format error interrupt */
    case SPI_I2S_INT_FLAG_FERR:
        reg1 = reg1 & SPI_STAT_FERR;
        reg2 = reg2 & SPI_CTL1_ERRIE;
        break;
    default :
        break;
    }
    /*get SPI/I2S interrupt flag status */
    if((0U != reg1) && (0U != reg2)){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      get SPI and I2S flag status
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[in]  flag: SPI/I2S flag status
                one or more parameters can be selected which are shown as below:
      \arg        SPI_FLAG_TBE: transmit buffer empty flag
      \arg        SPI_FLAG_RBNE: receive buffer not empty flag
      \arg        SPI_FLAG_TRANS: transmit on-going flag
      \arg        SPI_FLAG_RXORERR: receive overrun error flag
      \arg        SPI_FLAG_CONFERR: mode config error flag
      \arg        SPI_FLAG_CRCERR: CRC error flag
      \arg        SPI_FLAG_FERR: format error interrupt flag
      \arg        I2S_FLAG_TBE: transmit buffer empty flag
      \arg        I2S_FLAG_RBNE: receive buffer not empty flag
      \arg        I2S_FLAG_TRANS: transmit on-going flag
      \arg        I2S_FLAG_RXORERR: overrun error flag
      \arg        I2S_FLAG_TXURERR: underrun error flag
      \arg        I2S_FLAG_CH: channel side flag
                only for SPI1:
      \arg        SPI_TXLVL_EMPTY: SPI TXFIFO is empty
      \arg        SPI_TXLVL_QUARTER_FULL: SPI TXFIFO is a quarter of full
      \arg        SPI_TXLVL_HAlF_FULL: SPI TXFIFO is a half of full
      \arg        SPI_TXLVL_FULL: SPI TXFIFO is full
      \arg        SPI_RXLVL_EMPTY: SPI RXFIFO is empty
      \arg        SPI_RXLVL_QUARTER_FULL: SPI RXFIFO is a quarter of full
      \arg        SPI_RXLVL_HAlF_FULL: SPI RXFIFO is a half of full
      \arg        SPI_RXLVL_FULL: SPI RXFIFO is full
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus spi_i2s_flag_get(uint32_t spi_periph, uint32_t flag)
{
    if(RESET != (SPI_STAT(spi_periph) & flag)){
        return SET;
    }else{
        if(SPI1 == spi_periph){
            /* check TXFIFO is empty or not */
            if(SPI_TXLVL_EMPTY == flag){
                if(RESET != (SPI_STAT(spi_periph) & SPI_TXLVL_EMPTY_MASK)){
                    return RESET;
                }else{
                    return SET;
                }
            }
            /* check RXFIFO is empty or not */
            if(SPI_RXLVL_EMPTY == flag){
                if(RESET != (SPI_STAT(spi_periph) & SPI_RXLVL_EMPTY_MASK)){
                    return RESET;
                }else{
                    return SET;
                }
            }
        }
        return RESET;
    }
}

/*!
    \brief      clear SPI CRC error flag status
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[out] none
    \retval     none
*/
void spi_crc_error_clear(uint32_t spi_periph)
{
    SPI_STAT(spi_periph) &= (uint32_t)(~SPI_FLAG_CRCERR);
}

/*!
    \brief      configure SPI1 access size to FIFO(8bit or 16bit)
    \param[in]  spi_periph: SPIx(x=1)
    \param[in]  fifo_access_size: byte access enable
                only one parameter can be selected which is shown as below:
      \arg        SPI_HALFWORD_ACCESS: half-word access to FIFO
      \arg        SPI_BYTE_ACCESS: byte access to FIFO
    \param[out] none
    \retval     none
*/
void spi_fifo_access_size_config(uint32_t spi_periph, uint16_t fifo_access_size)
{
    /* clear SPI_CTL1_BYTEN bit */
    SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_BYTEN);
    /* confige SPI_CTL1_BYTEN bit */
    SPI_CTL1(spi_periph) |= (uint32_t)fifo_access_size;
}

/*!
    \brief      configure SPI1 total number of data to transmit by DMA is odd or not
    \param[in]  spi_periph: SPIx(x=1)
    \param[in]  odd: odd bytes in TX DMA channel
                only one parameter can be selected which is shown as below:
      \arg        SPI_TXDMA_EVEN: number of byte in TX DMA channel is even
      \arg        SPI_TXDMA_ODD: number of byte in TX DMA channel is odd
    \param[out] none
    \retval     none
*/
void spi_transmit_odd_config(uint32_t spi_periph, uint16_t odd)
{
    /* clear SPI_CTL1_TXDMA_ODD bit */
    SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_TXDMA_ODD);
    /* confige SPI_CTL1_TXDMA_ODD bit */
    SPI_CTL1(spi_periph) |= (uint32_t)odd;
}

/*!
    \brief      configure SPI1 total number of data to receive by DMA is odd or not
    \param[in]  spi_periph: SPIx(x=1)
    \param[in]  odd: odd bytes in RX DMA channel
                only one parameter can be selected which is shown as below:
      \arg        SPI_RXDMA_EVEN: number of bytes in RX DMA channel is even
      \arg        SPI_RXDMA_ODD: number of bytes in RX DMA channel is odd
    \param[out] none
    \retval     none
*/
void spi_receive_odd_config(uint32_t spi_periph, uint16_t odd)
{
    /* clear SPI_CTL1_RXDMA_ODD bit */
    SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_RXDMA_ODD);
    /* confige SPI_CTL1_RXDMA_ODD bit */
    SPI_CTL1(spi_periph) |= (uint32_t)odd;
}

/*!
    \brief      set CRC length
    \param[in]  spi_periph: SPIx(x=1)
    \param[in]  crc_length: CRC length
                only one parameter can be selected which is shown as below:
      \arg        SPI_CRC_8BIT: CRC length is 8 bits
      \arg        SPI_CRC_16BIT: CRC length is 16 bits
    \param[out] none
    \retval     none
*/
void spi_crc_length_set(uint32_t spi_periph, uint16_t crc_length)
{
    /* clear SPI_CTL0_CRCL bit */
    SPI_CTL0(spi_periph) &= (uint32_t)(~SPI_CTL0_CRCL);
    /* confige SPI_CTL0_CRCL bit */
    SPI_CTL0(spi_periph) |= (uint32_t)crc_length;
}
