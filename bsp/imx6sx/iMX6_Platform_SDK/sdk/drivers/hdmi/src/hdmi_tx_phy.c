/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "sdk.h"
#include "hdmi_tx.h"
#include "registers/regshdmi.h"

///////////////////////////////////////////////////////////////////////////////////
// CODE
///////////////////////////////////////////////////////////////////////////////////

void hdmi_phy_int_mask(int mask)
{
    HW_HDMI_PHY_MASK0.U = mask;
}

/*!
 * @brief Set the DE polarity
 *
 * @param	pol High or low for DE active
 */
static void hdmi_phy_de_pol(int pol)
{
    HW_HDMI_PHY_CONF0.B.SELDATAENPOL = pol;
}

/*!
 * @brief Select the interface control
 *
 * @param seldipif Interface selection
 */
static void hdmi_phy_if_sel(int seldipif)
{
    HW_HDMI_PHY_CONF0.B.SELDIPIF = seldipif;
}

/*!
 * @brief Enable TMDS output
 *
 * @param	en Enable or disable the TMDS output
 */
static void hdmi_phy_tmds(int en)
{
    HW_HDMI_PHY_CONF0.B.ENTMDS = en;
}

/*!
 * @brief PHY power down enable
 *
 * @param en Enable or disable PHY
 * 1 - power down disable
 * 0 - power down enable
 */
static void hdmi_phy_pdown(int en)
{
    HW_HDMI_PHY_CONF0.B.PDZ = en;
}

/*!
 * @brief PHY reset
 *
 * @param 	bit: reset PHY
 * 1 - reset PHY
 * 0 - turn PHY to normal
 */
static void hdmi_phy_reset(uint8_t bit)
{
    HW_HDMI_MC_PHYRSTZ.B.PHYRSTZ = bit ? 0 : 1;
}

/*!
 * @brief HDMI TEST mode clear
 * 
 * @param bit Enable or disable
 */
static inline void hdmi_phy_test_clear(uint8_t bit)
{
    HW_HDMI_PHY_TST0.B.TESTCLR = bit;
}

/*!
 * @brief HDMI TEST mode enable
 * 
 * @param bit Enable or disable
 */
static inline void hdmi_phy_test_enable(uint8_t bit)
{
    HW_HDMI_PHY_TST0.B.TESTEN = bit;
}

/*!
 * @brief HDMI PHY TEST clock enable
 * 
 * @param bit Enable or disable
 */
static inline void hdmi_phy_test_clock(uint8_t bit)
{
    HW_HDMI_PHY_TST0.B.TESTCLK = bit;
}

/*!
 * @brief HDMI PHY TEST data input
 * 
 * @param bit Data value
 */
static inline void hdmi_phy_test_din(uint8_t bit)
{
    HW_HDMI_PHY_TST1.U = bit;
}

/*!
 * @brief HDMI PHY TEST data output
 * 
 * @param bit Data value
 */
static inline void hdmi_phy_test_dout(uint8_t bit)
{
    HW_HDMI_PHY_TST2.U = bit;
}

/*!
 * @brief HDMI PHY TEST mode control
 * 
 * @param value Test Data input value
 */
static int hdmi_phy_test_control(uint8_t value)
{
    hdmi_phy_test_din(value);
    hdmi_phy_test_enable(1);
    hdmi_phy_test_clock(1);
    hdmi_phy_test_clock(0);
    hdmi_phy_test_enable(0);

    return TRUE;
}

/*!
 * @brief HDMI PHY TEST data set
 * 
 * @param value Test Data input value
 */
static int hdmi_phy_test_data(uint8_t value)
{
    hdmi_phy_test_din(value);
    hdmi_phy_test_enable(0);
    hdmi_phy_test_clock(1);
    hdmi_phy_test_clock(0);

    return TRUE;
}

/*!
 * @brief HDMI PHY tx power down
 * 
 * @param bit Enable or disable
 */
static void hdmi_phy_gen2_tx_pon(uint8_t bit)
{
    HW_HDMI_PHY_CONF0.B.GEN2_TXPWRON = bit;
}

/*!
 * @brief HDMI PHY tx PDDQ down
 * 
 * @param bit Enable or disable
 */
static void hdmi_phy_gen2_pddq(uint8_t bit)
{
    HW_HDMI_PHY_CONF0.B.GEN2_PDDQ = bit;
}

/*!
 * @brief HDMI PHY reset
 * 
 * @param bit Enable or disable
 */
static void hdmi_heacphy_reset(uint8_t bit)
{
    HW_HDMI_MC_HEACPHY_RST.B.HEACPHYRST = bit;
}

/*!
 * @brief Polling the i2c operation status bit to check if the i2c r/w
 * is done before the time run out.
 *
 * @param msec Time out value, using epit as the timer
 */
static int hdmi_phy_wait_i2c_done(int msec)
{
    unsigned char val = 0;
    val |= (HW_HDMI_IH_I2CMPHY_STAT0.B.I2CMPHYERROR << BP_HDMI_IH_I2CMPHY_STAT0_I2CMPHYERROR);
    val |= (HW_HDMI_IH_I2CMPHY_STAT0.B.I2CMPHYDONE << BP_HDMI_IH_I2CMPHY_STAT0_I2CMPHYDONE);
    while (val == 0) {
        hal_delay_us(1000);
        if (msec-- == 0) {
            printf("HDMI PHY i2c operation time out!!\n");
            return FALSE;
        }
        val |= (HW_HDMI_IH_I2CMPHY_STAT0.B.I2CMPHYERROR << BP_HDMI_IH_I2CMPHY_STAT0_I2CMPHYERROR);
        val |= (HW_HDMI_IH_I2CMPHY_STAT0.B.I2CMPHYDONE << BP_HDMI_IH_I2CMPHY_STAT0_I2CMPHYDONE);
    }
    return TRUE;
}

/*!
 * @brief HDMI phy registers access through internal I2C bus
 *
 * @param	data Value to be send
 * @param	addr Sub-address of registers
 *
 * @return TRUE if I2C write succeed or FALSE if I2C write failed/timeout  
 */
static int hdmi_phy_i2c_write(uint16_t data, uint8_t addr)
{
    HW_HDMI_IH_I2CMPHY_STAT0.U = 0xFF;
    HW_HDMI_PHY_I2CM_ADDRESS_ADDR.U = addr;
    HW_HDMI_PHY_I2CM_DATAO_1_ADDR.U = (uint8_t) (data >> 8);
    HW_HDMI_PHY_I2CM_DATAO_0_ADDR.U = (uint8_t) data;
    HW_HDMI_PHY_I2CM_OPERATION_ADDR.B.WRITE = 1;
    return hdmi_phy_wait_i2c_done(1000);
}

/*!
 * @brief HDMI phy registers read through internal I2C bus
 *
 * @param	addr Sub-address of register
 *
 * @return	value read back
 */
static uint16_t hdmi_phy_i2c_read(uint8_t addr)
{
    uint16_t data;
    uint8_t msb = 0, lsb = 0;

    HW_HDMI_IH_I2CMPHY_STAT0.U = 0xFF;
    HW_HDMI_PHY_I2CM_ADDRESS_ADDR.U = addr;
    HW_HDMI_PHY_I2CM_OPERATION_ADDR.B.READ = 1;
    hdmi_phy_wait_i2c_done(1000);
    msb = HW_HDMI_PHY_I2CM_DATAI_1_ADDR.U;
    lsb = HW_HDMI_PHY_I2CM_DATAI_0_ADDR.U;
    data = (msb << 8) | lsb;
    return data;
}

/*!
 * @brief HDMI phy registers access and verificate through internal I2C bus
 *
 * @param	data Value to be send
 * @param	addr Sub-address of registers
 *
 * @return TRUE if I2C write succeed, or False if the value read back does not 
 * equal to the input  
 */
static int hdmi_phy_i2c_write_verify(uint16_t data, uint8_t addr)
{
    unsigned short val = 0;
    //int repeat = 5;
    hdmi_phy_i2c_write(data, addr);
    val = hdmi_phy_i2c_read(addr);
    if (val != data) {
        printf("I2C data verification failed at REG 0x%02x : 0x%04x vs 0x%04x\n", addr, data, val);
        return FALSE;
    }
    return TRUE;
}

#define PHY_GEN2
#define PHY_TNP
/*!
 * @brief HDMI phy configuration
 *
 * @param	pClk Pixel clock input
 * @param	pRep Repetition setting
 * @param	cRes Color resolution per component
 * @param	cscOn Csc on/off switch
 * @param	audioOn Audio on/off switch
 * @param	cecOn CEC on/off switch
 * @param	hdcpOn HDCP on/off switch
 *
 * @return FALSE if configuration failed or TRUE ifconfiguration succeed
 */
static int hdmi_phy_configure(uint16_t pClk, uint8_t pRep, uint8_t cRes, int cscOn,
                              int audioOn, int cecOn, int hdcpOn)
{
    // colour resolution 0 is 8 bit colour depth
    if (cRes == 0) {
        cRes = 8;
    }
    if (pRep != 0) {
        printf("pixel repetition not supported %d", pRep);
        return FALSE;
    } else if (cRes != 8 && cRes != 12) {
        printf("color resolution not supported %d", cRes);
        return FALSE;
    }
#ifndef PHY_TNP
    uint16_t clk = 0, rep = 0;
    switch (pClk) {
    case 2520:
        clk = 0x93C1;
        rep = (cRes == 8) ? 0x6A4A : 0x6653;
        break;
    case 2700:
        clk = 0x96C1;
        rep = (cRes == 8) ? 0x6A4A : 0x6653;
        break;
    case 5400:
        clk = 0x8CC3;
        rep = (cRes == 8) ? 0x6A4A : 0x6653;
        break;
    case 7200:
        clk = 0x90C4;
        rep = (cRes == 8) ? 0x6A4A : 0x6654;
        break;
    case 7425:
        clk = 0x95C8;
        rep = (cRes == 8) ? 0x6A4A : 0x6654;
        break;
    case 10800:
        clk = 0x98C6;
        rep = (cRes == 8) ? 0x6A4A : 0x6653;
        break;
    case 14850:
        clk = 0x89C9;
        rep = (cRes == 8) ? 0x6A4A : 0x6654;
        break;
    default:
        printf("pixel clock not supported %d", pClk);
        return FALSE;
    }
#endif

    HW_HDMI_MC_FLOWCTRL.B.FEED_THROUGH_OFF = (cscOn == TRUE) ? 1 : 0;
    // clock gate == 0 => turn on modules
    HW_HDMI_MC_CLKDIS.B.PIXELCLK_DISABLE = 0;
    HW_HDMI_MC_CLKDIS.B.TMDSCLK_DISABLE = 0;
    HW_HDMI_MC_CLKDIS.B.PREPCLK_DISABLE = (pRep > 0) ? 1 : 0;
    HW_HDMI_MC_CLKDIS.B.AUDCLK_DISABLE = (audioOn == TRUE) ? 1 : 0;
    HW_HDMI_MC_CLKDIS.B.CSCCLK_DISABLE = (cscOn == TRUE) ? 1 : 0;
    HW_HDMI_MC_CLKDIS.B.CECCLK_DISABLE = (cecOn == TRUE) ? 1 : 0;
    HW_HDMI_MC_CLKDIS.B.HDCPCLK_DISABLE = (hdcpOn == TRUE) ? 1 : 0;

#ifdef PHY_GEN2
    hdmi_phy_gen2_tx_pon(0);
    hdmi_phy_gen2_pddq(1);
    hdmi_phy_reset(0);
    hdmi_phy_reset(1);
    hdmi_heacphy_reset(1);
    hdmi_phy_test_clear(1);
    HW_HDMI_PHY_I2CM_SLAVE_ADDR.U = 0x69;
    hdmi_phy_test_clear(0);

    switch (pClk) {
    case 2520:
        switch (cRes) {
        case 8:
            // PLL/MPLL Cfg
            hdmi_phy_i2c_write(0x01e0, 0x06);
            hdmi_phy_i2c_write(0x091c, 0x10);   // CURRCTRL
            hdmi_phy_i2c_write(0x0000, 0x15);   // GMPCTRL
            hdmi_phy_i2c_write(0x0000, 0x13);   // PLLPHBYCTRL
            hdmi_phy_i2c_write(0x0006, 0x17);
            // RESISTANCE TERM 133Ohm Cfg
            hdmi_phy_i2c_write(0x0005, 0x19);   // TXTERM
            // PREEMP Cgf 0.00
            hdmi_phy_i2c_write(0x8009, 0x09);   // CKSYMTXCTRL
            // TX/CK LVL 10
            hdmi_phy_i2c_write(0x0210, 0x0E);   // VLEVCTRL
            // REMOVE CLK TERM
            hdmi_phy_i2c_write(0x8000, 0x05);   // CKCALCTRL
            break;
        case 10:
            hdmi_phy_i2c_write(0x21e1, 0x06);
            hdmi_phy_i2c_write(0x091c, 0x10);
            hdmi_phy_i2c_write(0x0000, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x8009, 0x09);
            hdmi_phy_i2c_write(0x0210, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        case 12:
            hdmi_phy_i2c_write(0x41e2, 0x06);
            hdmi_phy_i2c_write(0x06dc, 0x10);
            hdmi_phy_i2c_write(0x0000, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x8009, 0x09);
            hdmi_phy_i2c_write(0x0210, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        default:
            printf("color depth not supported %d", pClk);
            return FALSE;
        }
        break;
    case 2700:
        switch (cRes) {
        case 8:
            hdmi_phy_i2c_write(0x01e0, 0x06);
            hdmi_phy_i2c_write(0x091c, 0x10);
            hdmi_phy_i2c_write(0x0000, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x8009, 0x09);
            hdmi_phy_i2c_write(0x0210, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        case 10:
            hdmi_phy_i2c_write(0x21e1, 0x06);
            hdmi_phy_i2c_write(0x091c, 0x10);
            hdmi_phy_i2c_write(0x0000, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x8009, 0x09);
            hdmi_phy_i2c_write(0x0210, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        case 12:
            hdmi_phy_i2c_write(0x41e2, 0x06);
            hdmi_phy_i2c_write(0x06dc, 0x10);
            hdmi_phy_i2c_write(0x0000, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x8009, 0x09);
            hdmi_phy_i2c_write(0x0210, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        default:
            printf("color depth not supported %d", pClk);
            return FALSE;
        }
        break;
    case 5400:
        switch (cRes) {
        case 8:
            hdmi_phy_i2c_write(0x0140, 0x06);
            hdmi_phy_i2c_write(0x091c, 0x10);
            hdmi_phy_i2c_write(0x0005, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x8009, 0x09);
            hdmi_phy_i2c_write(0x0210, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        case 10:
            hdmi_phy_i2c_write(0x2141, 0x06);
            hdmi_phy_i2c_write(0x091c, 0x10);
            hdmi_phy_i2c_write(0x0005, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x8009, 0x09);
            hdmi_phy_i2c_write(0x0210, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        case 12:
            hdmi_phy_i2c_write(0x4142, 0x06);
            hdmi_phy_i2c_write(0x06dc, 0x10);
            hdmi_phy_i2c_write(0x0005, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x8009, 0x09);
            hdmi_phy_i2c_write(0x0210, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        default:
            printf("color depth not supported %d", pClk);
            return FALSE;
        }
        break;
    case 7200:
        switch (cRes) {
        case 8:
            hdmi_phy_i2c_write(0x0140, 0x06);
            hdmi_phy_i2c_write(0x06dc, 0x10);
            hdmi_phy_i2c_write(0x0005, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x8009, 0x09);
            hdmi_phy_i2c_write(0x0210, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        case 10:
            hdmi_phy_i2c_write(0x2141, 0x06);
            hdmi_phy_i2c_write(0x06dc, 0x10);
            hdmi_phy_i2c_write(0x0005, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x8009, 0x09);
            hdmi_phy_i2c_write(0x0210, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        case 12:
            hdmi_phy_i2c_write(0x40a2, 0x06);
            hdmi_phy_i2c_write(0x091c, 0x10);
            hdmi_phy_i2c_write(0x000a, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x8009, 0x09);
            hdmi_phy_i2c_write(0x0210, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        default:
            printf("color depth not supported %d", pClk);
            return FALSE;
        }
        break;
    case 7425:
        switch (cRes) {
        case 8:
            hdmi_phy_i2c_write(0x0140, 0x06);
            hdmi_phy_i2c_write(0x06dc, 0x10);
            hdmi_phy_i2c_write(0x0005, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x8009, 0x09);
            hdmi_phy_i2c_write(0x0210, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        case 10:
            hdmi_phy_i2c_write(0x20a1, 0x06);
            hdmi_phy_i2c_write(0x0b5c, 0x10);
            hdmi_phy_i2c_write(0x000a, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x8009, 0x09);
            hdmi_phy_i2c_write(0x0210, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        case 12:
            hdmi_phy_i2c_write(0x40a2, 0x06);
            hdmi_phy_i2c_write(0x091c, 0x10);
            hdmi_phy_i2c_write(0x000a, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x8009, 0x09);
            hdmi_phy_i2c_write(0x0210, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        default:
            printf("color depth not supported %d", pClk);
            return FALSE;
        }
        break;
    case 10800:
        switch (cRes) {
        case 8:
            hdmi_phy_i2c_write(0x00a0, 0x06);
            hdmi_phy_i2c_write(0x091c, 0x10);
            hdmi_phy_i2c_write(0x000a, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x8009, 0x09);
            hdmi_phy_i2c_write(0x0210, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        case 10:
            hdmi_phy_i2c_write(0x20a1, 0x06);
            hdmi_phy_i2c_write(0x091c, 0x10);
            hdmi_phy_i2c_write(0x000a, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x8009, 0x09);
            hdmi_phy_i2c_write(0x0210, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        case 12:
            hdmi_phy_i2c_write(0x40a2, 0x06);
            hdmi_phy_i2c_write(0x06dc, 0x10);
            hdmi_phy_i2c_write(0x000a, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x8009, 0x09);
            hdmi_phy_i2c_write(0x0210, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        default:
            printf("color depth not supported %d", pClk);
            return FALSE;
        }
        break;
    case 14850:
        switch (cRes) {
        case 8:
            hdmi_phy_i2c_write(0x00a0, 0x06);
            hdmi_phy_i2c_write(0x06dc, 0x10);
            hdmi_phy_i2c_write(0x000a, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x8009, 0x09);
            hdmi_phy_i2c_write(0x0210, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        case 10:
            hdmi_phy_i2c_write(0x2001, 0x06);
            hdmi_phy_i2c_write(0x0b5c, 0x10);
            hdmi_phy_i2c_write(0x000f, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x8009, 0x09);
            hdmi_phy_i2c_write(0x0210, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        case 12:
            hdmi_phy_i2c_write(0x4002, 0x06);
            hdmi_phy_i2c_write(0x091c, 0x10);
            hdmi_phy_i2c_write(0x000f, 0x15);
            hdmi_phy_i2c_write(0x0000, 0x13);
            hdmi_phy_i2c_write(0x0006, 0x17);
            hdmi_phy_i2c_write(0x0005, 0x19);
            hdmi_phy_i2c_write(0x800b, 0x09);
            hdmi_phy_i2c_write(0x0129, 0x0E);
            hdmi_phy_i2c_write(0x8000, 0x05);
            break;
        default:
            printf("color depth not supported %d", pClk);
            return FALSE;
        }
        break;
    default:
        printf("pixel clock not supported %d", pClk);
        return FALSE;
    }
    hdmi_phy_gen2_tx_pon(1);
    hdmi_phy_gen2_pddq(0);
    hal_delay_us(1000);
#else //this is for test mode
    hdmi_phy_test_clear(0);
    hdmi_phy_test_clear(1);
    hdmi_phy_test_clear(0);
#define PHY_TNP
#ifdef PHY_TNP
    printf("TNP build\n");
#else
    printf("CNP build\n");
#endif
#ifndef PHY_TNP
    hdmi_phy_test_clock(0);
    hdmi_phy_test_enable(0);
    if (hdmi_phy_test_control(0x1B) == FALSE) {
        return FALSE;
    }
    hdmi_phy_test_data((unsigned char)(clk >> 8));
    hdmi_phy_test_data((unsigned char)(clk >> 0));
    if (hdmi_phy_test_control(0x1A) == FALSE) {
        return FALSE;
    }
    hdmi_phy_test_data((unsigned char)(rep >> 8));
    hdmi_phy_test_data((unsigned char)(rep >> 0));
#endif

    if (pClk == 14850 && cRes == 12) {
        printf("Applying Pre-Emphase");
        if (hdmi_phy_test_control(0x24) == FALSE) {
            return FALSE;
        }
        hdmi_phy_test_data(0x80);
        hdmi_phy_test_data(0x90);
        hdmi_phy_test_data(0xa0);
#ifndef PHY_TNP
        hdmi_phy_test_data(0xb0);
        if (hdmi_phy_test_control(0x20) == FALSE) { // +11.1ma 3.3 pe
            return FALSE;
        }
        hdmi_phy_test_data(0x04);
        if (hdmi_phy_test_control(0x21) == FALSE) { // +11.1 +2ma 3.3 pe
            return FALSE;
        }
        hdmi_phy_test_data(0x2a);
        // TODO verify
        if (hdmi_phy_test_control(0x11) == FALSE) {
            return FALSE;
        }
        hdmi_phy_test_data(0xf3);
        hdmi_phy_test_data(0x93);
#else
        if (hdmi_phy_test_control(0x20) == FALSE) {
            return FALSE;
        }
        hdmi_phy_test_data(0x00);
        if (hdmi_phy_test_control(0x21) == FALSE) {
            return FALSE;
        }
        hdmi_phy_test_data(0x00);
#endif
    }
    if (hdmi_phy_test_control(0x00) == FALSE) {
        return FALSE;
    }
    hdmi_phy_test_din(0x00);
    hdmi_phy_reset(1);          // reset PHY
    hdmi_phy_reset(0);          // for phy gen2 shoud be 0 => 1
    hdmi_phy_tmds(0);           // toggle TMDS
    hdmi_phy_tmds(1);
#endif
    if (HW_HDMI_IH_PHY_STAT0.B.TX_PHY_LOCK == 0) {
        //printf("PHY PLL not locked");
        return FALSE;
    }
    return TRUE;
}

void hdmi_phy_init(uint8_t de, uint16_t pclk)
{
    hdmi_phy_int_mask(0xFF);
    hdmi_phy_de_pol((de == TRUE) ? 1 : 0);
    hdmi_phy_if_sel(0);
    hdmi_phy_tmds(1);
    hdmi_phy_pdown(1);          //enable PHY

    hdmi_phy_configure(pclk, 0, 8, FALSE, FALSE, FALSE, FALSE);
}

///////////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////////
