/*!
    \file    gd32h7xx_ospim.c
    \brief   OSPIM driver

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

#include "gd32h7xx_ospim.h"
#include "gd32h7xx_ospi.h"

/*!
    \brief      reset the OSPIM peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ospim_deinit(void)
{
    /* reset OSPIM */
    rcu_periph_reset_enable(RCU_OSPIMRST);
    rcu_periph_reset_disable(RCU_OSPIMRST);
}

/*!
    \brief      configurate SCK for port
    \param[in]  port: number of port
                only one parameter can be selected which is shown as below:
      \arg        OSPIM_PORT0: port 0
      \arg        OSPIM_PORT1: port 1
    \param[in]  sckconfg: enable or disable SCK
                only one parameter can be selected which is shown as below:
      \arg        OSPIM_PORT_SCK_DISABLE: disable SCK
      \arg        OSPIM_PORT_SCK_ENABLE: enable SCK
    \param[out] none
    \retval     none
*/
void ospim_port_sck_config(uint8_t port, uint32_t sckconfg)
{
    OSPIM_PCFG(port) &= (uint32_t)(~OSPIM_PCFG_SCKEN);
    OSPIM_PCFG(port) |= (uint32_t)sckconfg;
}


/*!
    \brief      select source of SCK for port
    \param[in]  port: number of port
                only one parameter can be selected which is shown as below:
      \arg        OSPIM_PORT0: port 0
      \arg        OSPIM_PORT1: port 1
    \param[in]  sck_source: source of SCK
                only one parameter can be selected which is shown as below:
      \arg        OSPIM_SCK_SOURCE_OSPI0_SCK: the source of SCK is OSPI0_SCK
      \arg        OSPIM_SCK_SOURCE_OSPI1_SCK: the source of SCK is OSPI1_SCK
    \param[out] none
    \retval     none
*/
void ospim_port_sck_source_select(uint8_t port, uint32_t sck_source)
{
    OSPIM_PCFG(port) &= (uint32_t)(~OSPIM_PCFG_SRCPCK);
    OSPIM_PCFG(port) |= (uint32_t)sck_source;
}

/*!
    \brief      configurate CSN for port
    \param[in]  port: number of port
                only one parameter can be selected which is shown as below:
      \arg        OSPIM_PORT0: port 0
      \arg        OSPIM_PORT1: port 1
    \param[in]  csnconfig: enable or disable CSN
                only one parameter can be selected which is shown as below:
      \arg        OSPIM_PORT_CSN_DISABLE: disable CSN
      \arg        OSPIM_PORT_CSN_ENABLE: enable CSN
    \param[out] none
    \retval     none
*/
void ospim_port_csn_config(uint8_t port, uint32_t csnconfig)
{
    OSPIM_PCFG(port) &= (uint32_t)(~OSPIM_PCFG_NCSEN);
    OSPIM_PCFG(port) |= (uint32_t)csnconfig;
}

/*!
    \brief      select source of CSN for port
    \param[in]  port: number of port
                only one parameter can be selected which is shown as below:
      \arg        OSPIM_PORT0: port 0
      \arg        OSPIM_PORT1: port 1
    \param[in]  csn_source: source of CSN
                only one parameter can be selected which is shown as below:
      \arg        OSPIM_CSN_SOURCE_OSPI0_CSN: the source of CSN is OSPI0_CSN
      \arg        OSPIM_CSN_SOURCE_OSPI1_CSN: the source of CSN is OSPI1_CSN
    \param[out] none
    \retval     none
*/
void ospim_port_csn_source_select(uint8_t port, uint32_t csn_source)
{
    OSPIM_PCFG(port) &= (uint32_t)(~OSPIM_PCFG_SRCPCS);
    OSPIM_PCFG(port) |= (uint32_t)csn_source;
}

/*!
    \brief      configurate IO[3:0] for port
    \param[in]  port: number of port
                only one parameter can be selected which is shown as below:
      \arg        OSPIM_PORT0: port 0
      \arg        OSPIM_PORT1: port 1
    \param[in]  ioconfig: enable or disable IO[3:0]
                only one parameter can be selected which is shown as below:
      \arg        OSPIM_IO_LOW_DISABLE: disable IO[3:0]
      \arg        OSPIM_IO_LOW_ENABLE: enable IO[3:0]
    \param[out] none
    \retval     none
*/
void ospim_port_io3_0_config(uint8_t port, uint32_t ioconfig)
{
    OSPIM_PCFG(port) &= (uint32_t)(~OSPIM_PCFG_POLEN);
    OSPIM_PCFG(port) |= (uint32_t)ioconfig;
}

/*!
    \brief      select source of IO[3:0] for port
    \param[in]  port: number of port
                only one parameter can be selected which is shown as below:
      \arg        OSPIM_PORT0: port 0
      \arg        OSPIM_PORT1: port 1
    \param[in]  csn_source: source of IO[3:0]
                only one parameter can be selected which is shown as below:
      \arg        OSPIM_SRCPLIO_OSPI0_IO_LOW: select OSPI0_IO[3:0]
      \arg        OSPIM_SRCPLIO_OSPI0_IO_HIGH: select OSPI0_IO[7:4]
      \arg        OSPIM_SRCPLIO_OSPI1_IO_LOW: select OSPI1_IO[3:0]
      \arg        OSPIM_SRCPLIO_OSPI1_IO_HIGH: select OSPI1_IO[7:4]
    \param[out] none
    \retval     none
*/
void ospim_port_io3_0_source_select(uint8_t port, uint32_t io_source)
{
    OSPIM_PCFG(port) &= (uint32_t)(~OSPIM_PCFG_SRCPLIO);
    OSPIM_PCFG(port) |= (uint32_t)io_source;
}

/*!
    \brief      configurate IO[7:4] for port
    \param[in]  port: number of port
                only one parameter can be selected which is shown as below:
      \arg        OSPIM_PORT0: port 0
      \arg        OSPIM_PORT1: port 1
    \param[in]  ioconfig: enable or disable IO[7:4]
                only one parameter can be selected which is shown as below:
      \arg        OSPIM_IO_HIGH_DISABLE: disable IO[7:4]
      \arg        OSPIM_IO_HIGH_ENABLE: enable IO[7:4]
    \param[out] none
    \retval     none
*/
void ospim_port_io7_4_config(uint8_t port, uint32_t ioconfig)
{
    OSPIM_PCFG(port) &= (uint32_t)(~OSPIM_PCFG_POHEN);
    OSPIM_PCFG(port) |= (uint32_t)ioconfig;
}

/*!
    \brief      select source of IO[7:4] for port
    \param[in]  port: number of port
                only one parameter can be selected which is shown as below:
      \arg        OSPIM_PORT0: port 0
      \arg        OSPIM_PORT1: port 1
    \param[in]  csn_source: source of IO[7:4]
                only one parameter can be selected which is shown as below:
      \arg        OSPIM_SRCPHIO_OSPI0_IO_LOW: select OSPI0_IO[3:0]
      \arg        OSPIM_SRCPHIO_OSPI0_IO_HIGH: select OSPI0_IO[7:4]
      \arg        OSPIM_SRCPHIO_OSPI1_IO_LOW: select OSPI1_IO[3:0]
      \arg        OSPIM_SRCPHIO_OSPI1_IO_HIGH: select OSPI1_IO[7:4]
    \param[out] none
    \retval     none
*/
void ospim_port_io7_4_source_select(uint8_t port, uint32_t io_source)
{
    OSPIM_PCFG(port) &= (uint32_t)(~OSPIM_PCFG_SRCPHIO);
    OSPIM_PCFG(port) |= (uint32_t)io_source;
}
