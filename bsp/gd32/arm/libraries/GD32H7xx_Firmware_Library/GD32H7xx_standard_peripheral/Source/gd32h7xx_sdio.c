/*!
    \file    gd32h7xx_sdio.c
    \brief   SDIO driver

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

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

#include "gd32h7xx_sdio.h"

/* IDMA buffer value offset macro */
#define SDIO_IDMACTL_IDMASIZE_OFFSET    ((uint32_t)5U)

/*!
    \brief      deinitialize the SDIO
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_deinit(uint32_t sdio_periph)
{
    switch(sdio_periph)
    {
    /* reset SDIO0 */
    case SDIO0:
        rcu_periph_reset_enable(RCU_SDIO0RST);
        rcu_periph_reset_disable(RCU_SDIO0RST);
        break;
    /* reset SDIO1 */
    case SDIO1:
        rcu_periph_reset_enable(RCU_SDIO1RST);
        rcu_periph_reset_disable(RCU_SDIO1RST);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure the SDIO clock
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  clock_edge: SDIO_CLK clock edge
                only one parameter can be selected which is shown as below:
      \arg        SDIO_SDIOCLKEDGE_RISING: select the rising edge of the SDIOCLK to generate SDIO_CLK
      \arg        SDIO_SDIOCLKEDGE_FALLING: select the falling edge of the SDIOCLK to generate SDIO_CLK
    \param[in]  clock_powersave: SDIO_CLK clock dynamic switch on/off for power saving
                only one parameter can be selected which is shown as below:
      \arg        SDIO_CLOCKPWRSAVE_ENABLE: SDIO_CLK closed when bus is idle
      \arg        SDIO_CLOCKPWRSAVE_DISABLE: SDIO_CLK clock is always on
    \param[in]  clock_division: clock division, less than 1024
    \param[out] none
    \retval     none
*/
void sdio_clock_config(uint32_t sdio_periph, uint32_t clock_edge, uint32_t clock_powersave, uint32_t clock_division)
{
    uint32_t clock_config = 0U;
    clock_config = SDIO_CLKCTL(sdio_periph);
    /* reset the CLKEDGE, CLKPWRSAV, DIV */
    clock_config &= ~(SDIO_CLKCTL_CLKEDGE | SDIO_CLKCTL_CLKPWRSAV | SDIO_CLKCTL_DIV);
    /* configure the SDIO_CLKCTL according to the parameters */
    clock_config |= (clock_edge | clock_powersave | clock_division);
    SDIO_CLKCTL(sdio_periph) = clock_config;
}

/*!
    \brief      set receive clock
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  clock_receive: SDIO_CLK receive clock selection
                only one parameter can be selected which is shown as below:
      \arg        SDIO_RECEIVECLOCK_INCLK: select SDIO_IN_CLK clock
      \arg        SDIO_RECEIVECLOCK_CLKIN: select SDIO_CLKIN clock
      \arg        SDIO_RECEIVECLOCK_FBCLK: select SDIO_FB_CLK clock
    \param[out] none
    \retval     none
*/
void sdio_clock_receive_set(uint32_t sdio_periph, uint32_t clock_receive)
{
    uint32_t clock_config = 0U;
    clock_config = SDIO_CLKCTL(sdio_periph);
    /* reset the RCLK */
    clock_config &= ~SDIO_CLKCTL_RCLK;
    /* configure the SDIO_CLKCTL according to the parameters */
    clock_config |= clock_receive;
    SDIO_CLKCTL(sdio_periph) = clock_config;
}

/*!
    \brief      enable hardware clock control
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_hardware_clock_enable(uint32_t sdio_periph)
{
    SDIO_CLKCTL(sdio_periph) |= SDIO_CLKCTL_HWEN;
}

/*!
    \brief      disable hardware clock control
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_hardware_clock_disable(uint32_t sdio_periph)
{
    SDIO_CLKCTL(sdio_periph) &= ~SDIO_CLKCTL_HWEN;
}

/*!
    \brief      set different SDIO card bus mode
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  bus_mode: SDIO card bus mode
                only one parameter can be selected which is shown as below:
      \arg        SDIO_BUSMODE_1BIT: 1-bit SDIO card bus mode
      \arg        SDIO_BUSMODE_4BIT: 4-bit SDIO card bus mode
      \arg        SDIO_BUSMODE_8BIT: 8-bit SDIO card bus mode
    \param[out] none
    \retval     none
*/
void sdio_bus_mode_set(uint32_t sdio_periph, uint32_t bus_mode)
{
    /* reset the SDIO card bus mode bits */
    SDIO_CLKCTL(sdio_periph) &= ~SDIO_CLKCTL_BUSMODE;
    /* set the bus mode according to bus_mode */
    SDIO_CLKCTL(sdio_periph) |= bus_mode;
}

/*!
    \brief      set SDIO bus speed
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  bus_mode: SDIO card bus speed
                only one parameter can be selected which is shown as below:
      \arg        SDIO_BUSSPEED_LOW: DS, HS, SDR12, SDR25 bus speed
      \arg        SDIO_BUSSPEED_HIGH: SDR50, SDR104, DDR50 bus speed
    \param[out] none
    \retval     none
*/
void sdio_bus_speed_set(uint32_t sdio_periph, uint32_t bus_speed)
{
    /* reset the SDIO card bus speed bits */
    SDIO_CLKCTL(sdio_periph) &= ~SDIO_CLKCTL_BUSSP;
    /* set the bus mode according to bus_mode */
    SDIO_CLKCTL(sdio_periph) |= bus_speed;
}

/*!
    \brief      set SDIO data rate
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  data_rate: SDIO card data rate
                only one parameter can be selected which is shown as below:
      \arg        SDIO_DATA_RATE_SDR: SDR bus mode selected
      \arg        SDIO_DATA_RATE_DDR: DDR bus mode selected
    \param[out] none
    \retval     none
*/
void sdio_data_rate_set(uint32_t sdio_periph, uint32_t data_rate)
{
    /* reset the SDIO card data rate */
    SDIO_CLKCTL(sdio_periph) &= ~SDIO_CLKCTL_DRSEL;
    /* set the bus mode according to data_rate */
    SDIO_CLKCTL(sdio_periph) |= data_rate;
}

/*!
    \brief      set direction polarity of data and command
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  dirpl: SDIO direction polarity
                only one parameter can be selected which is shown as below:
      \arg        SDIO_DIRECTION_SIGNAL_LOW: direction signal is low, the voltage transceiver IOs driven as output
      \arg        SDIO_DIRECTION_SIGNAL_HIGH: direction signal is high, the voltage transceiver IOs driven as output
    \param[out] none
    \retval     none
*/
void sdio_direction_polarity_set(uint32_t sdio_periph, uint32_t dirpl)
{
    /* reset the SDIO_PWRCTL_DIRPS */
    SDIO_PWRCTL(sdio_periph) &= ~SDIO_PWRCTL_DIRPS;
    /* set the direction polarity according to dirpl */
    SDIO_PWRCTL(sdio_periph) |= dirpl;
}

/*!
    \brief      set the SDIO power state
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  power_state: SDIO power state
                only one parameter can be selected which is shown as below:
      \arg        SDIO_POWER_ON: SDIO power on
      \arg        SDIO_POWER_CYCLE:SDIO power cycle
      \arg        SDIO_POWER_OFF: SDIO power off
    \param[out] none
    \retval     none
*/
void sdio_power_state_set(uint32_t sdio_periph, uint32_t power_state)
{
    /* set SDIO_PWRCTL according to power_state */
    SDIO_PWRCTL(sdio_periph) &= ~SDIO_PWRCTL_PWRCTL;
    SDIO_PWRCTL(sdio_periph) |= power_state;
}

/*!
    \brief      get the SDIO power state
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     SDIO power state
*/
uint32_t sdio_power_state_get(uint32_t sdio_periph)
{
    return SDIO_PWRCTL(sdio_periph);
}

/*!
    \brief      configure the command and response
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  cmd_index: command index, refer to the related specifications
    \param[in]  cmd_argument: command argument, refer to the related specifications
    \param[in]  response_type: response type
                only one parameter can be selected which is shown as below:
      \arg        SDIO_RESPONSETYPE_NO: no response
      \arg        SDIO_RESPONSETYPE_SHORT: short response
      \arg        SDIO_RESPONSETYPE_SHORT_NOCRC: short response without CRC
      \arg        SDIO_RESPONSETYPE_LONG: long response
    \param[out] none
    \retval     none
*/
void sdio_command_response_config(uint32_t sdio_periph, uint32_t cmd_index, uint32_t cmd_argument, uint32_t response_type)
{
    uint32_t cmd_config = 0U;
    /* disable the CSM */
    SDIO_CMDCTL(sdio_periph) &= ~SDIO_CMDCTL_CSMEN;
    /* reset the command index, command argument and response type */
    SDIO_CMDAGMT(sdio_periph) &= ~SDIO_CMDAGMT_CMDAGMT;
    SDIO_CMDAGMT(sdio_periph) = cmd_argument;
    cmd_config = SDIO_CMDCTL(sdio_periph);
    cmd_config &= ~(SDIO_CMDCTL_CMDIDX | SDIO_CMDCTL_CMDRESP);
    /* configure SDIO_CMDCTL and SDIO_CMDAGMT according to the parameters */
    cmd_config |= (cmd_index | response_type);
    SDIO_CMDCTL(sdio_periph) = cmd_config;
}

/*!
    \brief      set the command state machine wait type
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  wait_type: wait type
                only one parameter can be selected which is shown as below:
      \arg        SDIO_WAITTYPE_NO: not wait interrupt
      \arg        SDIO_WAITTYPE_INTERRUPT: wait interrupt
      \arg        SDIO_WAITTYPE_DATAEND: wait the end of data transfer
    \param[out] none
    \retval     none
*/
void sdio_wait_type_set(uint32_t sdio_periph, uint32_t wait_type)
{
    /* reset INTWAIT and WAITDEND */
    SDIO_CMDCTL(sdio_periph) &= ~(SDIO_CMDCTL_INTWAIT | SDIO_CMDCTL_WAITDEND);
    /* set the wait type according to wait_type */
    SDIO_CMDCTL(sdio_periph) |= wait_type;
}

/*!
    \brief      enable the CSM transfer command mode(treats the command as a data transfer command)
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_trans_start_enable(uint32_t sdio_periph)
{
    SDIO_CMDCTL(sdio_periph) |= SDIO_CMDCTL_TREN;
}

/*!
    \brief      disable the CSM transfer command mode(treats the command as a data transfer command)
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_trans_start_disable(uint32_t sdio_periph)
{
    SDIO_CMDCTL(sdio_periph) &= ~SDIO_CMDCTL_TREN;
}

/*!
    \brief      enable the CSM stop command mode(treats the command as a data stop transfer command)
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_trans_stop_enable(uint32_t sdio_periph)
{
    SDIO_CMDCTL(sdio_periph) |= SDIO_CMDCTL_TRSTOP;
}

/*!
    \brief      disable the CSM stop command mode(treats the command as a data stop transfer command)
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_trans_stop_disable(uint32_t sdio_periph)
{
    SDIO_CMDCTL(sdio_periph) &= ~SDIO_CMDCTL_TRSTOP;
}

/*!
    \brief      enable the CSM(command state machine)
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_csm_enable(uint32_t sdio_periph)
{
    SDIO_CMDCTL(sdio_periph) |= SDIO_CMDCTL_CSMEN;
}

/*!
    \brief      disable the CSM(command state machine)
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_csm_disable(uint32_t sdio_periph)
{
    SDIO_CMDCTL(sdio_periph) &= ~SDIO_CMDCTL_CSMEN;
}

/*!
    \brief      get the last response command index
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     last response command index
*/
uint8_t sdio_command_index_get(uint32_t sdio_periph)
{
    return (uint8_t)SDIO_RSPCMDIDX(sdio_periph);
}

/*!
    \brief      get the response for the last received command
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  sdio_responsex: SDIO response
                only one parameter can be selected which is shown as below:
      \arg        SDIO_RESPONSE0: card response[31:0]/card response[127:96]
      \arg        SDIO_RESPONSE1: card response[95:64]
      \arg        SDIO_RESPONSE2: card response[63:32]
      \arg        SDIO_RESPONSE3: card response[31:1], plus bit 0
    \param[out] none
    \retval     response for the last received command
*/
uint32_t sdio_response_get(uint32_t sdio_periph, uint32_t sdio_responsex)
{
    uint32_t resp_content = 0U;

    /* get the content of the last response */
    switch(sdio_responsex)
    {
    case SDIO_RESPONSE0:
        resp_content = SDIO_RESP0(sdio_periph);
        break;
    case SDIO_RESPONSE1:
        resp_content = SDIO_RESP1(sdio_periph);
        break;
    case SDIO_RESPONSE2:
        resp_content = SDIO_RESP2(sdio_periph);
        break;
    case SDIO_RESPONSE3:
        resp_content = SDIO_RESP3(sdio_periph);
        break;
    default:
        break;
    }
    return resp_content;
}

/*!
    \brief      disable the DSM status hold
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_hold_enable(uint32_t sdio_periph)
{
    SDIO_CMDCTL(sdio_periph) |= SDIO_CMDCTL_HOLD;
}

/*!
    \brief      enable the DSM status hold
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_hold_disable(uint32_t sdio_periph)
{
    SDIO_CMDCTL(sdio_periph) &= ~SDIO_CMDCTL_HOLD;
}

/*!
    \brief      enable the SDIO suspend mode (the CSM treats the command as a Suspend command or Resume command)
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_suspend_enable(uint32_t sdio_periph)
{
    SDIO_CMDCTL(sdio_periph) |= SDIO_CMDCTL_CMDSR;
}

/*!
    \brief      disable the SDIO suspend mode (the CSM treats the command as a Suspend command or Resume command)
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_suspend_disable(uint32_t sdio_periph)
{
    SDIO_CMDCTL(sdio_periph) &= ~SDIO_CMDCTL_CMDSR;
}

/*!
    \brief      configure the data timeout, data length and data block size
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  data_timeout: data timeout period in card bus clock periods
    \param[in]  data_length: number of data bytes to be transferred
    \param[in]  data_blocksize: size of data block for block transfer
                only one parameter can be selected which is shown as below:
      \arg        SDIO_DATABLOCKSIZE_1BYTE: block size = 1 byte
      \arg        SDIO_DATABLOCKSIZE_2BYTES: block size = 2 bytes
      \arg        SDIO_DATABLOCKSIZE_4BYTES: block size = 4 bytes
      \arg        SDIO_DATABLOCKSIZE_8BYTES: block size = 8 bytes
      \arg        SDIO_DATABLOCKSIZE_16BYTES: block size = 16 bytes
      \arg        SDIO_DATABLOCKSIZE_32BYTES: block size = 32 bytes
      \arg        SDIO_DATABLOCKSIZE_64BYTES: block size = 64 bytes
      \arg        SDIO_DATABLOCKSIZE_128BYTES: block size = 128 bytes
      \arg        SDIO_DATABLOCKSIZE_256BYTES: block size = 256 bytes
      \arg        SDIO_DATABLOCKSIZE_512BYTES: block size = 512 bytes
      \arg        SDIO_DATABLOCKSIZE_1024BYTES: block size = 1024 bytes
      \arg        SDIO_DATABLOCKSIZE_2048BYTES: block size = 2048 bytes
      \arg        SDIO_DATABLOCKSIZE_4096BYTES: block size = 4096 bytes
      \arg        SDIO_DATABLOCKSIZE_8192BYTES: block size = 8192 bytes
      \arg        SDIO_DATABLOCKSIZE_16384BYTES: block size = 16384 bytes
    \param[out] none
    \retval     none
*/
void sdio_data_config(uint32_t sdio_periph, uint32_t data_timeout, uint32_t data_length, uint32_t data_blocksize)
{
    /* reset data timeout, data length and data block size */
    SDIO_DATATO(sdio_periph) &= ~SDIO_DATATO_DATATO;
    SDIO_DATALEN(sdio_periph) &= ~SDIO_DATALEN_DATALEN;
    SDIO_DATACTL(sdio_periph) &= ~SDIO_DATACTL_BLKSZ;
    /* configure the related parameters of data */
    SDIO_DATATO(sdio_periph) = data_timeout;
    SDIO_DATALEN(sdio_periph) = data_length;
    SDIO_DATACTL(sdio_periph) |= data_blocksize;
}

/*!
    \brief      configure the data transfer mode and direction
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  transfer_mode: mode of data transfer
                only one parameter can be selected which is shown as below:
      \arg        SDIO_TRANSMODE_BLOCKCOUNT: Block count data transfer
      \arg        SDIO_TRANSMODE_MULTIBYTE: multibyte data transfer (only SD/SD I/O)
      \arg        SDIO_TRANSMODE_STREAM: stream transfer (only eMMC)
      \arg        SDIO_TRANSMODE_BLOCKCMD12: Block data transfer ends with CMD12
    \param[in]  transfer_direction: data transfer direction, read or write
                only one parameter can be selected which is shown as below:
      \arg        SDIO_TRANSDIRECTION_TOCARD: write data to card
      \arg        SDIO_TRANSDIRECTION_TOSDIO: read data from card
    \param[out] none
    \retval     none
*/
void sdio_data_transfer_config(uint32_t sdio_periph, uint32_t transfer_mode, uint32_t transfer_direction)
{
    uint32_t data_trans = 0U;
    /* reset the data transfer mode, transfer direction and set according to the parameters */
    data_trans = SDIO_DATACTL(sdio_periph);
    data_trans &= ~(SDIO_DATACTL_TRANSMOD | SDIO_DATACTL_DATADIR);
    data_trans |= (transfer_mode | transfer_direction);
    SDIO_DATACTL(sdio_periph) = data_trans;
}

/*!
    \brief      enable the DSM(data state machine) for data transfer
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sdio_dsm_enable(uint32_t sdio_periph)
{
    SDIO_DATACTL(sdio_periph) |= SDIO_DATACTL_DATAEN;
}

/*!
    \brief      disable the DSM(data state machine) for data transfer
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sdio_dsm_disable(uint32_t sdio_periph)
{
    SDIO_DATACTL(sdio_periph) &= ~SDIO_DATACTL_DATAEN;
}

/*!
    \brief      write data(one word) to the transmit FIFO
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  data: 32-bit data write to card
    \param[out] none
    \retval     none
*/
void sdio_data_write(uint32_t sdio_periph, uint32_t data)
{
    SDIO_FIFO(sdio_periph) = data;
}

/*!
    \brief      read data(one word) from the receive FIFO
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     received data
*/
uint32_t sdio_data_read(uint32_t sdio_periph)
{
    return SDIO_FIFO(sdio_periph);
}

/*!
    \brief      get the number of remaining data bytes to be transferred to card
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     number of remaining data bytes to be transferred
*/
uint32_t sdio_data_counter_get(uint32_t sdio_periph)
{
    return SDIO_DATACNT(sdio_periph);
}

/*!
    \brief      enable the reset of fifo
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_fifo_reset_enable(uint32_t sdio_periph)
{
    SDIO_DATACTL(sdio_periph) |= SDIO_DATACTL_FIFOREST;
}

/*!
    \brief      disable the reset of fifo
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_fifo_reset_disable(uint32_t sdio_periph)
{
    SDIO_DATACTL(sdio_periph) &= ~SDIO_DATACTL_FIFOREST;
}

/*!
    \brief      set IDMA buffer mode and size
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  buffer_mode: set IDMA buffer mode
                only one parameter can be selected which is shown as below:
      \arg        SDIO_IDMA_SINGLE_BUFFER: single buffer mode
      \arg        SDIO_IDMA_DOUBLE_BUFFER: double buffer mode
    \param[in]  buffer_size: 0-0xFF,  set IDMA buffer size
    \param[out] none
    \retval     none
*/
void sdio_idma_set(uint32_t sdio_periph, uint32_t buffer_mode, uint32_t buffer_size)
{
    /* reset the SDIO_IDMACTL_BUFMOD */
    SDIO_IDMACTL(sdio_periph) &= ~SDIO_IDMACTL_BUFMOD;
    /* reset the SDIO_IDMASIZE_IDMASIZE */
    SDIO_IDMASIZE(sdio_periph) &= ~SDIO_IDMASIZE_IDMASIZE;
    /* set the buffer mode according to buffer_mode */
    SDIO_IDMACTL(sdio_periph) |= buffer_mode;
    /* set the buffer size according to buffer_size */
    SDIO_IDMASIZE(sdio_periph) |= ((buffer_size & BITS(0, 7)) << SDIO_IDMACTL_IDMASIZE_OFFSET);
}

/*!
    \brief      set IDMA buffer0 address
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  buffer_address: the address of idma buffer0, buffer_address[0:1] should be 0b'00;
    \param[out] none
    \retval     none
*/
void sdio_idma_buffer0_address_set(uint32_t sdio_periph, uint32_t buffer_address)
{
    /* reset the SDIO_IDMAADDR0_IDMAADDR0 */
    SDIO_IDMAADDR0(sdio_periph) &= ~SDIO_IDMAADDR0_IDMAADDR0;
    /* set the buffer0 address according to buffer_address */
    SDIO_IDMAADDR0(sdio_periph) |= (buffer_address & BITS(2, 31));
}

/*!
    \brief      set IDMA buffer1 address
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  buffer_address: the address of idma buffer1, buffer_address[0:1] should be 0b'00;
    \param[out] none
    \retval     none
*/
void sdio_idma_buffer1_address_set(uint32_t sdio_periph, uint32_t buffer_address)
{
    /* reset the SDIO_IDMAADDR1_IDMAADDR1 */
    SDIO_IDMAADDR1(sdio_periph) &= ~SDIO_IDMAADDR1_IDMAADDR1;
    /* set the buffer1 address according to buffer_address */
    SDIO_IDMAADDR1(sdio_periph) |= (buffer_address & BITS(2, 31));
}

/*!
    \brief      get the IDMA double buffer address selection bit
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval    IDMA buffer selection: SDIO_IDMA_BUFFER0 or SDIO_IDMA_BUFFER1
*/
uint32_t sdio_buffer_selection_get(uint32_t sdio_periph)
{
    return SDIO_IDMACTL(sdio_periph) & SDIO_IDMACTL_BUFSEL;
}

/*!
    \brief      select IDMA buffer
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  buffer_select: the buffer to be used
                only one parameter can be selected which is shown as below:
      \arg        SDIO_IDMA_BUFFER0: select buffer0
      \arg        SDIO_IDMA_BUFFER1: select buffer1
    \param[out] none
    \retval     none
*/
void sdio_idma_buffer_select(uint32_t sdio_periph, uint32_t buffer_select)
{
    /* reset the SDIO_IDMACTL_BUFSEL */
    SDIO_IDMACTL(sdio_periph) &= ~SDIO_IDMACTL_BUFSEL;
    /* select buffer according to buffer_select */
    SDIO_IDMACTL(sdio_periph) |= buffer_select;
}

/*!
    \brief     enable the IDMA request for SDIO
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_idma_enable(uint32_t sdio_periph)
{
    SDIO_IDMACTL(sdio_periph) |= SDIO_IDMACTL_IDMAEN;
}

/*!
    \brief      disable the IDMA request for SDIO
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_idma_disable(uint32_t sdio_periph)
{
    SDIO_IDMACTL(sdio_periph) &= ~SDIO_IDMACTL_IDMAEN;
}

/*!
    \brief      get the flags state of SDIO
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  flag: flags state of SDIO
                one or more parameters can be selected which are shown as below:
      \arg        SDIO_FLAG_CCRCERR: command response received (CRC check failed) flag
      \arg        SDIO_FLAG_DTCRCERR: data block sent/received (CRC check failed) flag
      \arg        SDIO_FLAG_CMDTMOUT: command response timeout flag
      \arg        SDIO_FLAG_DTTMOUT: data timeout flag
      \arg        SDIO_FLAG_TXURE: transmit FIFO underrun error occurs flag
      \arg        SDIO_FLAG_RXORE: received FIFO overrun error occurs flag
      \arg        SDIO_FLAG_CMDRECV: command response received (CRC check passed) flag
      \arg        SDIO_FLAG_CMDSEND: command sent (no response required) flag
      \arg        SDIO_FLAG_DTEND: data end (data counter, SDIO_DATACNT, is zero) flag
      \arg        SDIO_FLAG_DTHOLD: data transfer hold flag
      \arg        SDIO_FLAG_DTBLKEND: data block sent/received (CRC check passed) flag
      \arg        SDIO_FLAG_DTABORT: data transfer aborted by CMD12 flag
      \arg        SDIO_FLAG_CMDSTA: command path active state flag
      \arg        SDIO_FLAG_DATSTA: data path active state flag
      \arg        SDIO_FLAG_TFH: transmit FIFO is half empty flag: at least 8 words can be written into the FIFO
      \arg        SDIO_FLAG_RFH: receive FIFO is half full flag: at least 8 words can be read in the FIFO
      \arg        SDIO_FLAG_TFF: transmit FIFO is full flag
      \arg        SDIO_FLAG_RFF: receive FIFO is full flag
      \arg        SDIO_FLAG_TFE: transmit FIFO is empty flag
      \arg        SDIO_FLAG_RFE: receive FIFO is empty flag
      \arg        SDIO_FLAG_DAT0BSY: DAT0 line signal keep busy flag
      \arg        SDIO_FLAG_DAT0BSYEND: DAT0 line signal changed form busy to ready flag
      \arg        SDIO_FLAG_SDIOINT: SD I/O interrupt received flag
      \arg        SDIO_FLAG_ACKFAIL: boot acknowledgment received and check fail flag
      \arg        SDIO_FLAG_ACKTO: boot acknowledgment timeout flag
      \arg        SDIO_FLAG_VOLSWEND: voltage switch critical timing section end
      \arg        SDIO_FLAG_CLKSTOP: SDIO_CLK stopped in voltage switch procedure flag
      \arg        SDIO_FLAG_IDMAERR: IDMA transfer error flag
      \arg        SDIO_FLAG_IDMAEND: IDMA transfer end flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus sdio_flag_get(uint32_t sdio_periph, uint32_t flag)
{
    FlagStatus temp_flag = RESET;
    if(RESET != (SDIO_STAT(sdio_periph) & flag))
    {
        temp_flag = SET;
    }
    return temp_flag;
}

/*!
    \brief      clear the pending flags of SDIO
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  flag: flags state of SDIO
                one or more parameters can be selected which are shown as below:
      \arg        SDIO_FLAG_CCRCERR: command response received (CRC check failed) flag
      \arg        SDIO_FLAG_DTCRCERR: data block sent/received (CRC check failed) flag
      \arg        SDIO_FLAG_CMDTMOUT: command response timeout flag
      \arg        SDIO_FLAG_DTTMOUT: data timeout flag
      \arg        SDIO_FLAG_TXURE: transmit FIFO underrun error occurs flag
      \arg        SDIO_FLAG_RXORE: received FIFO overrun error occurs flag
      \arg        SDIO_FLAG_CMDRECV: command response received (CRC check passed) flag
      \arg        SDIO_FLAG_CMDSEND: command sent (no response required) flag
      \arg        SDIO_FLAG_DTEND: data end (data counter, SDIO_DATACNT, is zero) flag
      \arg        SDIO_FLAG_DTHOLD: data transfer hold flag
      \arg        SDIO_FLAG_DTBLKEND: data block sent/received (CRC check passed) flag
      \arg        SDIO_FLAG_DTABORT: data transfer aborted (by CMD12) flag
      \arg        SDIO_FLAG_DAT0BSYEND: DAT0 line signal changed form busy to ready flag
      \arg        SDIO_FLAG_SDIOINT: SD I/O interrupt received flag
      \arg        SDIO_FLAG_ACKFAIL: boot acknowledgment received and check fail
      \arg        SDIO_FLAG_ACKTO: boot acknowledgment timeout flag
      \arg        SDIO_FLAG_VOLSWEND: voltage switch critical timing section end flag
      \arg        SDIO_FLAG_CLKSTOP: SDIO_CLK stopped in voltage switch procedure flag
      \arg        SDIO_FLAG_IDMAERR: IDMA transfer error occurs flag
      \arg        SDIO_FLAG_IDMAEND: IDMA transfer end flag
    \param[out] none
    \retval     none
*/
void sdio_flag_clear(uint32_t sdio_periph, uint32_t flag)
{
    SDIO_INTC(sdio_periph) = flag;
}

/*!
    \brief      enable the SDIO interrupt
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  int_flag: interrupt flags state of SDIO
                one or more parameters can be selected which are shown as below:
      \arg        SDIO_INT_CCRCERR: SDIO CCRCERR interrupt
      \arg        SDIO_INT_DTCRCERR: SDIO DTCRCERR interrupt
      \arg        SDIO_INT_CMDTMOUT: SDIO CMDTMOUT interrupt
      \arg        SDIO_INT_DTTMOUT: SDIO DTTMOUT interrupt
      \arg        SDIO_INT_TXURE: SDIO TXURE interrupt
      \arg        SDIO_INT_RXORE: SDIO RXORE interrupt
      \arg        SDIO_INT_CMDRECV: SDIO CMDRECV interrupt
      \arg        SDIO_INT_CMDSEND: SDIO CMDSEND interrupt
      \arg        SDIO_INT_DTEND: SDIO DTEND interrupt
      \arg        SDIO_INT_DTHOLD: SDIO DTHOLD interrupt
      \arg        SDIO_INT_DTBLKEND: SDIO DTBLKEND interrupt
      \arg        SDIO_INT_DTABORT: SDIO DTABORT interrupt
      \arg        SDIO_INT_TFH: SDIO TFH interrupt
      \arg        SDIO_INT_RFH: SDIO RFH interrupt
      \arg        SDIO_INT_RFF: SDIO RFF interrupt
      \arg        SDIO_INT_TFE: SDIO TFE interrupt
      \arg        SDIO_INT_DAT0BSYEND: SDIO DAT0BSYEND interrupt
      \arg        SDIO_INT_SDIOINT: SDIO SDIOINT interrupt
      \arg        SDIO_INT_ACKFAIL: SDIO ACKFAIL interrupt
      \arg        SDIO_INT_ACKTO: SDIO ACKTO interrupt
      \arg        SDIO_INT_VOLSWEND: SDIO VOLSWEND interrupt
      \arg        SDIO_INT_CLKSTOP: SDIO CLKSTOP interrupt
      \arg        SDIO_INT_IDMAERR: SDIO IDMAERR interrupt
      \arg        SDIO_INT_IDMAEND: SDIO IDMAEND interrupt
    \param[out] none
    \retval     none
*/
void sdio_interrupt_enable(uint32_t sdio_periph, uint32_t int_flag)
{
    SDIO_INTEN(sdio_periph) |= int_flag;
}

/*!
    \brief      enable the SDIO interrupt
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  int_flag: interrupt flags state of SDIO
                one or more parameters can be selected which are shown as below:
      \arg        SDIO_INT_CCRCERR: SDIO CCRCERR interrupt
      \arg        SDIO_INT_DTCRCERR: SDIO DTCRCERR interrupt
      \arg        SDIO_INT_CMDTMOUT: SDIO CMDTMOUT interrupt
      \arg        SDIO_INT_DTTMOUT: SDIO DTTMOUT interrupt
      \arg        SDIO_INT_TXURE: SDIO TXURE interrupt
      \arg        SDIO_INT_RXORE: SDIO RXORE interrupt
      \arg        SDIO_INT_CMDRECV: SDIO CMDRECV interrupt
      \arg        SDIO_INT_CMDSEND: SDIO CMDSEND interrupt
      \arg        SDIO_INT_DTEND: SDIO DTEND interrupt
      \arg        SDIO_INT_DTHOLD: SDIO DTHOLD interrupt
      \arg        SDIO_INT_DTBLKEND: SDIO DTBLKEND interrupt
      \arg        SDIO_INT_DTABORT: SDIO DTABORT interrupt
      \arg        SDIO_INT_TFH: SDIO TFH interrupt
      \arg        SDIO_INT_RFH: SDIO RFH interrupt
      \arg        SDIO_INT_RFF: SDIO RFF interrupt
      \arg        SDIO_INT_TFE: SDIO TFE interrupt
      \arg        SDIO_INT_DAT0BSYEND: SDIO DAT0BSYEND interrupt
      \arg        SDIO_INT_SDIOINT: SDIO SDIOINT interrupt
      \arg        SDIO_INT_ACKFAIL: SDIO ACKFAIL interrupt
      \arg        SDIO_INT_ACKTO: SDIO ACKTO interrupt
      \arg        SDIO_INT_VOLSWEND: SDIO VOLSWEND interrupt
      \arg        SDIO_INT_CLKSTOP: SDIO CLKSTOP interrupt
      \arg        SDIO_INT_IDMAERR: SDIO IDMAERR interrupt
      \arg        SDIO_INT_IDMAEND: SDIO IDMAEND interrupt
    \param[out] none
    \retval     none
*/
void sdio_interrupt_disable(uint32_t sdio_periph, uint32_t int_flag)
{
    SDIO_INTEN(sdio_periph) &= ~int_flag;
}

/*!
    \brief      get the interrupt flags state of SDIO
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  int_flag: interrupt flags state of SDIO
                one or more parameters can be selected which are shown as below:
      \arg        SDIO_INT_FLAG_CCRCERR: SDIO CCRCERR interrupt flag
      \arg        SDIO_INT_FLAG_DTCRCERR: SDIO DTCRCERR interrupt flag
      \arg        SDIO_INT_FLAG_CMDTMOUT: SDIO CMDTMOUT interrupt flag
      \arg        SDIO_INT_FLAG_DTTMOUT: SDIO DTTMOUT interrupt flag
      \arg        SDIO_INT_FLAG_TXURE: SDIO TXURE interrupt flag
      \arg        SDIO_INT_FLAG_RXORE: SDIO RXORE interrupt flag
      \arg        SDIO_INT_FLAG_CMDRECV: SDIO CMDRECV interrupt flag
      \arg        SDIO_INT_FLAG_CMDSEND: SDIO CMDSEND interrupt flag
      \arg        SDIO_INT_FLAG_DTEND: SDIO DTEND interrupt flag
      \arg        SDIO_INT_FLAG_DTHOLD: SDIO DTHOLD interrupt flag
      \arg        SDIO_INT_FLAG_DTBLKEND: SDIO DTBLKEND interrupt flag
      \arg        SDIO_INT_FLAG_DTABORT: SDIO DTABORT interrupt flag
      \arg        SDIO_INT_FLAG_TFH: SDIO TFH interrupt flag
      \arg        SDIO_INT_FLAG_RFH: SDIO RFH interrupt flag
      \arg        SDIO_INT_FLAG_RFF: SDIO RFF interrupt flag
      \arg        SDIO_INT_FLAG_TFE: SDIO TFE interrupt flag
      \arg        SDIO_INT_FLAG_DAT0BSYEND: SDIO DAT0BSYEND interrupt flag
      \arg        SDIO_INT_FLAG_SDIOINT: SDIO SDIOINT interrupt flag
      \arg        SDIO_INT_FLAG_ACKFAIL: SDIO ACKFAIL interrupt flag
      \arg        SDIO_INT_FLAG_ACKTO: SDIO ACKTO interrupt flag
      \arg        SDIO_INT_FLAG_VOLSWEND: SDIO VOLSWEND interrupt flag
      \arg        SDIO_INT_FLAG_CLKSTOP: SDIO CLKSTOP interrupt flag
      \arg        SDIO_INT_FLAG_IDMAERR: SDIO IDMAERR interrupt flag
      \arg        SDIO_INT_FLAG_IDMAEND: SDIO IDMAEND interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus sdio_interrupt_flag_get(uint32_t sdio_periph, uint32_t int_flag)
{
    FlagStatus temp_flag = RESET;
    if(RESET != (SDIO_STAT(sdio_periph) & int_flag))
    {
        temp_flag = SET;
    }
    return temp_flag;
}

/*!
    \brief      clear the interrupt pending flags of SDIO
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  int_flag: interrupt flags state of SDIO
                one or more parameters can be selected which are shown as below:
      \arg        SDIO_INT_FLAG_CCRCERR: SDIO CCRCERR interrupt flag
      \arg        SDIO_INT_FLAG_DTCRCERR: SDIO DTCRCERR interrupt flag
      \arg        SDIO_INT_FLAG_CMDTMOUT: SDIO CMDTMOUT interrupt flag
      \arg        SDIO_INT_FLAG_DTTMOUT: SDIO DTTMOUT interrupt flag
      \arg        SDIO_INT_FLAG_TXURE: SDIO TXURE interrupt flag
      \arg        SDIO_INT_FLAG_RXORE: SDIO RXORE interrupt flag
      \arg        SDIO_INT_FLAG_CMDRECV: SDIO CMDRECV interrupt flag
      \arg        SDIO_INT_FLAG_CMDSEND: SDIO CMDSEND interrupt flag
      \arg        SDIO_INT_FLAG_DTEND: SDIO DTEND interrupt flag
      \arg        SDIO_INT_FLAG_DTHOLD: SDIO DTHOLD interrupt flag
      \arg        SDIO_INT_FLAG_DTBLKEND: SDIO DTBLKEND interrupt flag
      \arg        SDIO_INT_FLAG_DTABORT: SDIO DTABORT interrupt flag
      \arg        SDIO_INT_FLAG_DAT0BSYEND: SDIO DAT0BSYEND interrupt flag
      \arg        SDIO_INT_FLAG_SDIOINT: SDIO SDIOINT interrupt flag
      \arg        SDIO_INT_FLAG_ACKFAIL: SDIO ACKFAIL interrupt flag
      \arg        SDIO_INT_FLAG_ACKTO: SDIO ACKTO interrupt flag
      \arg        SDIO_INT_FLAG_VOLSWEND: SDIO VOLSWEND interrupt flag
      \arg        SDIO_INT_FLAG_CLKSTOP: SDIO CLKSTOP interrupt flag
      \arg        SDIO_INT_FLAG_IDMAERR: SDIO IDMAERR interrupt flag
      \arg        SDIO_INT_FLAG_IDMAEND: SDIO IDMAEND interrupt flag
    \param[out] none
    \retval     none
*/
void sdio_interrupt_flag_clear(uint32_t sdio_periph, uint32_t int_flag)
{
    SDIO_INTC(sdio_periph) = int_flag;
}

/*!
    \brief      enable voltage switch
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_voltage_switch_enable(uint32_t sdio_periph)
{
    SDIO_PWRCTL(sdio_periph) |= SDIO_PWRCTL_VSEN;
}

/*!
    \brief      disable voltage switch
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_voltage_switch_disable(uint32_t sdio_periph)
{
    SDIO_PWRCTL(sdio_periph) &= ~SDIO_PWRCTL_VSEN;
}

/*!
    \brief      enable voltage switch sequence
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_voltage_switch_sequence_enable(uint32_t sdio_periph)
{
    SDIO_PWRCTL(sdio_periph) |= SDIO_PWRCTL_VSSTART;
}

/*!
    \brief      disable voltage switch sequence
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_voltage_switch_sequence_disable(uint32_t sdio_periph)
{
    SDIO_PWRCTL(sdio_periph) &= ~SDIO_PWRCTL_VSSTART;
}

/*!
    \brief      set boot mode
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  boot_mode: mode of SDIO boot
                only one parameter can be selected which is shown as below:
      \arg        SDIO_BOOTMODE_NORMAL: normal boot mode
      \arg        SDIO_BOOTMODE_ALTERNATIVE: alternative boot mode
    \param[out] none
    \retval     none
*/
void sdio_boot_mode_set(uint32_t sdio_periph, uint32_t boot_mode)
{
    /* reset boot mode selection bit */
    SDIO_CMDCTL(sdio_periph) &= ~SDIO_CMDCTL_BOOTMOD;
    /* set boot mode according to the boot_mode */
    SDIO_CMDCTL(sdio_periph) |= boot_mode;
}

/*!
    \brief      enbale DSM(data state machine) boot acknowledgment
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_boot_ack_enable(uint32_t sdio_periph)
{
    SDIO_DATACTL(sdio_periph) |= SDIO_DATACTL_ACKEN;
}

/*!
    \brief      disbale DSM(data state machine) boot acknowledgment
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_boot_ack_disable(uint32_t sdio_periph)
{
    SDIO_DATACTL(sdio_periph) &= ~SDIO_DATACTL_ACKEN;
}

/*!
    \brief      set boot ACK timeout period
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[in]  timeout: boot ACK timeout period
    \param[out] none
    \retval     none
*/
void sdio_boot_acktimeout_set(uint32_t sdio_periph, uint32_t timeout)
{
    SDIO_ACKTO(sdio_periph) &= ~SDIO_ACKTO_ACKTO;
    SDIO_ACKTO(sdio_periph) |= timeout & SDIO_ACKTO_ACKTO;
}

/*!
    \brief      enable boot operation
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_boot_enable(uint32_t sdio_periph)
{
    SDIO_CMDCTL(sdio_periph) |= SDIO_CMDCTL_BOOTMODEN;
}

/*!
    \brief      disable boot operation
    \param[in]  sdio_periph: SDIOx(x=0,1)
    \param[out] none
    \retval     none
*/
void sdio_boot_disable(uint32_t sdio_periph)
{
    SDIO_CMDCTL(sdio_periph) &= ~SDIO_CMDCTL_BOOTMODEN;
}
