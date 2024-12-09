/*!
    \file    gd32h7xx_mdio.c
    \brief   MDIO driver

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

#include "gd32h7xx_mdio.h"

/*!
    \brief      reset MDIO
    \param[in]  none
    \param[out] none
    \retval     none
*/
void mdio_deinit(void)
{
    /* reset MDIO */
    rcu_periph_reset_enable(RCU_MDIORST);
    rcu_periph_reset_disable(RCU_MDIORST);
}

/*!
    \brief      reset MDIO block
    \param[in]  none
    \param[out] none
    \retval     none
*/
void mdio_software_reset(void)
{
    MDIO_CTL |= MDIO_CTL_SWRST;
}

/*!
    \brief      initialize MDIO for communication
    \param[in]  phy_size: PHY bit length
                only one parameter can be selected which is shown as below:
      \arg        MDIO_PHY_BITS_3: PHY use 3 bits
      \arg        MDIO_PHY_BITS_5: PHY use 5 bits
    \param[in]  phy_softaddr: software provided PHYADR (0 - 31)
    \param[in]  phy_sel: PHYADR select
                only one parameter can be selected which is shown as below:
      \arg        MDIO_PHYADR_HARDWARE: sets expected PHYADR = PHYPIN[4:0]
      \arg        MDIO_PHYADR_HW_SW_MIX(regval): sets Software address valid bits
      \arg        MDIO_PHYADR_SOFTWARE: sets expected PHYADR = PHYSW[4:0]
      \arg        other user defined value: 1 - 30
    \param[in]  devadd: device type
                only one parameter can be selected which is shown as below:
      \arg        DEVADD_PMA_PMD: device type PMA/PMD
      \arg        DEVADD_WIS: device type WIS
      \arg        DEVADD_PCS: device type PCS
      \arg        DEVADD_PHY_XS: device type PHY XS
      \arg        DEVADD_DTE_XS: device type DTE XS
    \param[out] none
    \retval     uint32_t: the PHYADR that the device will respond to 0 - 31
*/
uint32_t mdio_init(uint32_t phy_size, uint32_t phy_softaddr, uint32_t phy_sel, uint16_t devadd)
{
    uint32_t phy_addr = 0U, phy_hard = 0U;

    /* configure MDIO phy bit length */
    MDIO_CTL &= ~MDIO_CTL_PHYB;
    MDIO_CTL |= phy_size;

    /* configure the PHYADR and DEVADD */
    MDIO_CFG &= ~(MDIO_CFG_PHYSW | MDIO_CFG_EPHYSEL | MDIO_CFG_EDEVADD);
    MDIO_CFG |= CFG_PHYSW(phy_softaddr) | CFG_EPHYSEL(phy_sel) | CFG_EDEVADD(devadd);

    /* calculate the PHYADR that the device will respond to */
    phy_hard = mdio_phy_pin_read();
    phy_addr = (phy_hard & (~phy_sel)) | (phy_softaddr & phy_sel);

    return phy_addr;
}

/*!
    \brief      configure MDIO phy bit length
    \param[in]  phy_bit: PHY bit length
                only one parameter can be selected which is shown as below:
      \arg        MDIO_PHY_BITS_3: PHY use 3 bits
      \arg        MDIO_PHY_BITS_5: PHY use 5 bits
    \param[out] none
    \retval     none
*/
void mdio_phy_length_config(uint32_t phy_bit)
{
    MDIO_CTL &= ~MDIO_CTL_PHYB;
    MDIO_CTL |= phy_bit;
}

/*!
    \brief      set the software PHYADR value
    \param[in]  phy_soft: software provided PHYADR (0 - 31)
    \param[out] none
    \retval     none
*/
void mdio_soft_phyadr_set(uint32_t phy_soft)
{
    MDIO_CFG &= ~MDIO_CFG_PHYSW;
    MDIO_CFG |= CFG_PHYSW(phy_soft);
}

/*!
    \brief      select the expected frame field PHYADR
    \param[in]  phy_sel: PHYADR select
                only one parameter can be selected which is shown as below:
      \arg        MDIO_PHYADR_HARDWARE: sets expected PHYADR = PHYPIN[4:0]
      \arg        MDIO_PHYADR_SOFTWARE: sets expected PHYADR = PHYSW[4:0]
      \arg        other user defined value: 1 - 30
    \param[out] none
    \retval     none
*/
void mdio_framefield_phyadr_config(uint32_t phy_sel)
{
    MDIO_CFG &= ~MDIO_CFG_EPHYSEL;
    MDIO_CFG |= CFG_EPHYSEL(phy_sel);
}

/*!
    \brief      configure the expected frame field DEVADD
    \param[in]  type: device type
                only one parameter can be selected which is shown as below:
      \arg        DEVADD_PMA_PMD: device type PMA/PMD
      \arg        DEVADD_WIS: device type WIS
      \arg        DEVADD_PCS: device type PCS
      \arg        DEVADD_PHY_XS: device type PHY XS
      \arg        DEVADD_DTE_XS: device type DTE XS
    \param[out] none
    \retval     none
*/
void mdio_framefield_devadd_config(uint16_t type)
{
    MDIO_CFG &= ~MDIO_CFG_EDEVADD;
    MDIO_CFG |= CFG_EDEVADD(type);
}

/*!
    \brief      read the hardware PRTADR[4:0] value
    \param[in]  none
    \param[out] none
    \retval     uint32_t: 0x0-0x1F
*/
uint32_t mdio_phy_pin_read(void)
{
    return GET_PIN_PHYPIN(MDIO_PIN);
}

/*!
    \brief      configure the expected frame bit timeout
    \param[in]  timeout: timeout counter among frame bits (0 - 0xFFFF)
    \param[out] none
    \retval     none
*/
void mdio_timeout_config(uint16_t timeout)
{
    MDIO_TO &= ~MDIO_TO_TOCNT;
    MDIO_TO |= TO_TOCNT(timeout);
}

/*!
    \brief      enable MDIO frame bit timeout
    \param[in]  none
    \param[out] none
    \retval     none
*/
void mdio_timeout_enable(void)
{
    MDIO_TO |= MDIO_TO_TOEN;
}

/*!
    \brief      disable MDIO frame bit timeout
    \param[in]  none
    \param[out] none
    \retval     none
*/
void mdio_timeout_disable(void)
{
    MDIO_TO &= ~MDIO_TO_TOEN;
}

/*!
    \brief      read the received frame field OP
    \param[in]  none
    \param[out] none
    \retval     uint16_t: 0x0-0x11
*/
uint16_t mdio_op_receive(void)
{
    return (uint16_t)(GET_RFRM_ROP(MDIO_RFRM));
}

/*!
    \brief      read the received frame field PHYADR
    \param[in]  none
    \param[out] none
    \retval     uint16_t: 0x0-0x1F
*/
uint16_t mdio_phyadr_receive(void)
{
    return (uint16_t)(GET_RFRM_RPHY(MDIO_RFRM));
}

/*!
    \brief      read the received frame field DEVADD
    \param[in]  none
    \param[out] none
    \retval     uint16_t: 0x0-0x1F
*/
uint16_t mdio_devadd_receive(void)
{
    return (uint16_t)(GET_RFRM_RDEV(MDIO_RFRM));
}

/*!
    \brief      read the received frame field TA
    \param[in]  none
    \param[out] none
    \retval     uint16_t: 0x0-0x11
*/
uint16_t mdio_ta_receive(void)
{
    return (uint16_t)(GET_RFRM_RTA(MDIO_RFRM));
}

/*!
    \brief      read the received frame field DATA
    \param[in]  none
    \param[out] none
    \retval     uint16_t: 0x0-0xFFFF
*/
uint16_t mdio_data_receive(void)
{
    return (uint16_t)(GET_RDATA_RDATA(MDIO_RDATA));
}

/*!
    \brief      read the received frame field ADDRESS
    \param[in]  none
    \param[out] none
    \retval     uint16_t: 0x0-0xFFFF
*/
uint16_t mdio_address_receive(void)
{
    return (uint16_t)(GET_RADDR_RADDR(MDIO_RADDR));
}

/*!
    \brief      transmit the frame field DATA
    \param[in]  data: data to put in a read or post read increment address frame for transmission (0x0-0xFFFF)
    \param[out] none
    \retval     none
*/
void mdio_data_transmit(uint16_t data)
{
    MDIO_TDATA = (uint32_t)data;
}

/*!
    \brief      get the flag status of the frame
    \param[in]  flag: MDIO flag
                only one parameter can be selected which is shown as below:
      \arg        MDIO_FLAG_WRFRM: a write data frame flag status
      \arg        MDIO_FLAG_ADDRFRM: an address frame flag status
      \arg        MDIO_FLAG_RDINCFRM: a post read increment address frame flag status
      \arg        MDIO_FLAG_RDFRM: a read data frame flag status
      \arg        MDIO_FLAG_DEVM: a DEVADD match frame flag status
      \arg        MDIO_FLAG_DEVNM: a DEVADD nonmatch frame flag status
      \arg        MDIO_FLAG_PHYM: a PHYADR match frame flag status
      \arg        MDIO_FLAG_PHYNM: a PHYADR nonmatch frame flag status
      \arg        MDIO_FLAG_TANM: a TA nonmatch frame flag status
      \arg        MDIO_FLAG_TIMEOUT: timeout flag
      \arg        MDIO_FLAG_TX_UNDERRUN: transmit underrun flag
      \arg        MDIO_FLAG_RX_OVERRUN: receive overrun flag
      \arg        MDIO_FLAG_RBNE: read data buffer not empty flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus mdio_flag_get(uint32_t flag)
{
    __IO uint32_t reg = 0U;

    reg = MDIO_STAT;
    if(RESET != (reg & flag))
    {
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear the flag status
    \param[in]  flag: MDIO flag
                one or more parameters can be selected which are shown as below:
      \arg        MDIO_FLAG_WRFRM: a write data frame flag status
      \arg        MDIO_FLAG_ADDRFRM: an address frame flag status
      \arg        MDIO_FLAG_RDINCFRM: a post read increment address frame flag status
      \arg        MDIO_FLAG_RDFRM: a read data frame flag status
      \arg        MDIO_FLAG_DEVM: a DEVADD match frame flag status
      \arg        MDIO_FLAG_DEVNM: a DEVADD nonmatch frame flag status
      \arg        MDIO_FLAG_PHYM: a PHYADR match frame flag status
      \arg        MDIO_FLAG_PHYNM: a PHYADR nonmatch frame flag status
      \arg        MDIO_FLAG_TANM: a TA nonmatch frame flag status
      \arg        MDIO_FLAG_TIMEOUT: timeout flag
      \arg        MDIO_FLAG_TX_UNDERRUN: transmit underrun flag
      \arg        MDIO_FLAG_RX_OVERRUN: receive overrun flag
      \arg        MDIO_FLAG_RBNE: read data buffer not empty flag
    \param[out] none
    \retval     none
*/
void mdio_flag_clear(uint32_t flag)
{
    __IO uint32_t reg = 0U;

    reg = MDIO_TDATA;

    if((MDIO_FLAG_RX_OVERRUN | MDIO_FLAG_RBNE) & flag)
    {
        (void)(MDIO_RDATA);
    }else if(MDIO_FLAG_TX_UNDERRUN & flag)
    {
        MDIO_TDATA = reg;
    }else if((MDIO_FLAG_WRFRM | MDIO_FLAG_ADDRFRM | MDIO_FLAG_RDINCFRM | MDIO_FLAG_RDFRM
            | MDIO_FLAG_DEVM | MDIO_FLAG_DEVNM | MDIO_FLAG_PHYM | MDIO_FLAG_PHYNM | MDIO_FLAG_TIMEOUT) & flag)
            {
        (void)(MDIO_STAT);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      enable MDIO interrupt
    \param[in]  interrupt: MDIO interrupt
                one or more parameters can be selected which are shown as below:
      \arg        MDIO_INT_WRFRM: a write data frame interrupt
      \arg        MDIO_INT_ADDRFRM: an address frame interrupt
      \arg        MDIO_INT_RDINCFRM: a post read increment address frame interrupt
      \arg        MDIO_INT_RDFRM: a read data frame interrupt
      \arg        MDIO_INT_DEVM: a DEVADD match frame interrupt
      \arg        MDIO_INT_DEVNM: a DEVADD nonmatch frame interrupt
      \arg        MDIO_INT_PHYM: a PHYADR match frame interrupt
      \arg        MDIO_INT_PHYNM: a PHYADR nonmatch frame interrupt
      \arg        MDIO_INT_TANM: a TA nonmatch frame flag interrupt
      \arg        MDIO_INT_TIMEOUT: a timeout interrupt
      \arg        MDIO_INT_TX_UNDERRUN: a transmit underrun interrupt
      \arg        MDIO_INT_RX_OVERRUN: a receive overrun interrupt
      \arg        MDIO_INT_RBNE: a read data buffer not empty interrupt
    \param[out] none
    \retval     none
*/
void mdio_interrupt_enable(uint32_t interrupt)
{
    MDIO_INTEN |= interrupt;
}

/*!
    \brief      disable MDIO interrupt
    \param[in]  interrupt: MDIO interrupt
                one or more parameters can be selected which are shown as below:
      \arg        MDIO_INT_WRFRM: a write data frame interrupt
      \arg        MDIO_INT_ADDRFRM: an address frame interrupt
      \arg        MDIO_INT_RDINCFRM: a post read increment address frame interrupt
      \arg        MDIO_INT_RDFRM: a read data frame interrupt
      \arg        MDIO_INT_DEVM: a DEVADD match frame interrupt
      \arg        MDIO_INT_DEVNM: a DEVADD nonmatch frame interrupt
      \arg        MDIO_INT_PHYM: a PHYADR match frame interrupt
      \arg        MDIO_INT_PHYNM: a PHYADR nonmatch frame interrupt
      \arg        MDIO_INT_TANM: a TA nonmatch frame flag interrupt
      \arg        MDIO_INT_TIMEOUT: a timeout interrupt
      \arg        MDIO_INT_TX_UNDERRUN: a transmit underrun interrupt
      \arg        MDIO_INT_RX_OVERRUN: a receive overrun interrupt
      \arg        MDIO_INT_RBNE: a read data buffer not empty interrupt
    \param[out] none
    \retval     none
*/
void mdio_interrupt_disable(uint32_t interrupt)
{
    MDIO_INTEN &= ~(interrupt);
}
