/* ===================================================================================
 * Copyright (c) <2009> Synopsys, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software annotated with this license and associated documentation files
 * (the "Software"), to deal in the Software without restriction, including without
 * limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * =================================================================================== */

/** \file
 * This file defines the synopsys GMAC device dependent functions.
 * Most of the operations on the GMAC device are available in this file.
 * Functions for initiliasing and accessing MAC/DMA/PHY registers and the DMA descriptors
 * are encapsulated in this file. The functions are platform/host/OS independent.
 * These functions in turn use the low level device dependent (HAL) functions to
 * access the register space.
 * \internal
 * ------------------------REVISION HISTORY---------------------------------
 * Synopsys                 01/Aug/2007                              Created
 */

#include "synopGMAC_Dev.h"
#include "synopGMAC_network_interface.h"

/**
  * Function to set the MDC clock for mdio transactiona
  *
  * @param[in] pointer to device structure.
  * @param[in] clk divider value.
  * \return Reuturns 0 on success else return the error value.
  */
s32 synopGMAC_set_mdc_clk_div(synopGMACdevice *gmacdev, u32 clk_div_val)
{
    u32 orig_data;
    orig_data = synopGMACReadReg(gmacdev->MacBase, GmacGmiiAddr); //set the mdc clock to the user defined value
    orig_data &= (~ GmiiCsrClkMask);
    orig_data |= clk_div_val;
    synopGMACWriteReg(gmacdev->MacBase, GmacGmiiAddr, orig_data);
    return 0;
}

/**
  * Returns the current MDC divider value programmed in the ip.
  *
  * @param[in] pointer to device structure.
  * @param[in] clk divider value.
  * \return Returns the MDC divider value read.
  */
u32 synopGMAC_get_mdc_clk_div(synopGMACdevice *gmacdev)
{
    u32 data;
    data = synopGMACReadReg(gmacdev->MacBase, GmacGmiiAddr);
    data &= GmiiCsrClkMask;
    return data;
}


/**
  * Function to read the Phy register. The access to phy register
  * is a slow process as the data is moved accross MDI/MDO interface
  * @param[in] pointer to Register Base (It is the mac base in our case) .
  * @param[in] PhyBase register is the index of one of supported 32 PHY devices.
  * @param[in] Register offset is the index of one of the 32 phy register.
  * @param[out] u16 data read from the respective phy register (only valid iff return value is 0).
  * \return Returns 0 on success else return the error status.
  */
s32 synopGMAC_read_phy_reg(u32 RegBase, u32 PhyBase, u32 RegOffset, u16 *data)
{
    u32 addr;
    u32 loop_variable;
    addr = ((PhyBase << GmiiDevShift) & GmiiDevMask) | ((RegOffset << GmiiRegShift) & GmiiRegMask);
    addr = addr | GmiiBusy ; //Gmii busy bit
    synopGMACWriteReg(RegBase, GmacGmiiAddr, addr); //write the address from where the data to be read in GmiiGmiiAddr register of synopGMAC ip

    for (loop_variable = 0; loop_variable < DEFAULT_LOOP_VARIABLE; loop_variable++)  //Wait till the busy bit gets cleared with in a certain amount of time
    {
        if (!(synopGMACReadReg(RegBase, GmacGmiiAddr) & GmiiBusy))
        {
            break;
        }
        plat_delay(DEFAULT_DELAY_VARIABLE);
    }
    if (loop_variable < DEFAULT_LOOP_VARIABLE)
        * data = (u16)(synopGMACReadReg(RegBase, GmacGmiiData) & 0xFFFF);
    else
    {
        TR("Error::: PHY not responding Busy bit didnot get cleared !!!!!!\n");
        return -ESYNOPGMACPHYERR;
    }
    return 0;
}

/**
  * Function to write to the Phy register. The access to phy register
  * is a slow process as the data is moved accross MDI/MDO interface
  * @param[in] pointer to Register Base (It is the mac base in our case) .
  * @param[in] PhyBase register is the index of one of supported 32 PHY devices.
  * @param[in] Register offset is the index of one of the 32 phy register.
  * @param[in] data to be written to the respective phy register.
  * \return Returns 0 on success else return the error status.
  */
s32 synopGMAC_write_phy_reg(u32 RegBase, u32 PhyBase, u32 RegOffset, u16 data)
{
    u32 addr;
    u32 loop_variable;

    synopGMACWriteReg(RegBase, GmacGmiiData, data); // write the data in to GmacGmiiData register of synopGMAC ip

    addr = ((PhyBase << GmiiDevShift) & GmiiDevMask) | ((RegOffset << GmiiRegShift) & GmiiRegMask) | GmiiWrite;

    addr = addr | GmiiBusy ; //set Gmii clk to 20-35 Mhz and Gmii busy bit

    synopGMACWriteReg(RegBase, GmacGmiiAddr, addr);
    for (loop_variable = 0; loop_variable < DEFAULT_LOOP_VARIABLE; loop_variable++)
    {
        if (!(synopGMACReadReg(RegBase, GmacGmiiAddr) & GmiiBusy))
        {
            break;
        }
        plat_delay(DEFAULT_DELAY_VARIABLE);
    }

    if (loop_variable < DEFAULT_LOOP_VARIABLE)
    {
        return 0;
    }
    else
    {
        TR("Error::: PHY not responding Busy bit didnot get cleared !!!!!!\n");
        return -ESYNOPGMACPHYERR;
    }
}

/**
  * Function to configure the phy in loopback mode.
  *
  * @param[in] pointer to synopGMACdevice.
  * @param[in] enable or disable the loopback.
  * \return 0 on success else return the error status.
  * \note Don't get confused with mac loop-back synopGMAC_loopback_on(synopGMACdevice *)
  * and synopGMAC_loopback_off(synopGMACdevice *) functions.
  */
s32 synopGMAC_phy_loopback(synopGMACdevice *gmacdev, bool loopback)
{
    s32 status = 0;
#ifndef EMULATION
    if (loopback)
        status = synopGMAC_write_phy_reg(gmacdev->MacBase, gmacdev->PhyBase, PHY_CONTROL_REG, Mii_Loopback);
    else
        status = synopGMAC_write_phy_reg(gmacdev->MacBase, gmacdev->PhyBase, PHY_CONTROL_REG, Mii_NoLoopback);
#endif
    return status;
}



/**
  * Function to read the GMAC IP Version and populates the same in device data structure.
  * @param[in] pointer to synopGMACdevice.
  * \return Always return 0.
  */

s32 synopGMAC_read_version(synopGMACdevice *gmacdev)
{
    u32 data = 0;
    data = synopGMACReadReg(gmacdev->MacBase, GmacVersion);
    gmacdev->Version = data;
    TR("The data read from %08x is %08x\n", (gmacdev->MacBase + GmacVersion), data);
    return 0;
}


/**
  * Function to reset the GMAC core.
  * This reests the DMA and GMAC core. After reset all the registers holds their respective reset value
  * @param[in] pointer to synopGMACdevice.
  * \return 0 on success else return the error status.
  */

s32 synopGMAC_reset(synopGMACdevice *gmacdev)
{
    u32 data = 0;
    synopGMACWriteReg(gmacdev->DmaBase, DmaBusMode, DmaResetOn);
    plat_delay(DEFAULT_LOOP_VARIABLE);

    do
    {
        data = synopGMACReadReg(gmacdev->DmaBase, DmaBusMode);
    }
    while (data & 1);

    TR("DATA after Reset = %08x\n", data);

    return 0;
}

s32 synopGMAC_reset_nocheck(synopGMACdevice *gmacdev)
{
    synopGMACWriteReg(gmacdev->DmaBase, DmaBusMode, DmaResetOn);
    plat_delay(DEFAULT_LOOP_VARIABLE);
    return 0;
}

/**
  * Function to program DMA bus mode register.
  *
  * The Bus Mode register is programmed with the value given. The bits to be set are
  * bit wise or'ed and sent as the second argument to this function.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] the data to be programmed.
  * \return 0 on success else return the error status.
  */
s32 synopGMAC_dma_bus_mode_init(synopGMACdevice *gmacdev, u32 init_value)
{
    synopGMACWriteReg(gmacdev->DmaBase, DmaBusMode, init_value);
    return 0;

}

/**
  * Function to program DMA Control register.
  *
  * The Dma Control register is programmed with the value given. The bits to be set are
  * bit wise or'ed and sent as the second argument to this function.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] the data to be programmed.
  * \return 0 on success else return the error status.
  */
s32 synopGMAC_dma_control_init(synopGMACdevice *gmacdev, u32 init_value)
{
    synopGMACWriteReg(gmacdev->DmaBase, DmaControl, init_value);
    return 0;
}


/*Gmac configuration functions*/

/**
  * Enable the watchdog timer on the receiver.
  * When enabled, Gmac enables Watchdog timer, and GMAC allows no more than
  * 2048 bytes of data (10,240 if Jumbo frame enabled).
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_wd_enable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacWatchdog);
    return;
}
/**
  * Disable the watchdog timer on the receiver.
  * When disabled, Gmac disabled watchdog timer, and can receive frames up to
  * 16,384 bytes.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_wd_disable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacWatchdog);
    return;
}

/**
  * Enables the Jabber frame support.
  * When enabled, GMAC disabled the jabber timer, and can transfer 16,384 byte frames.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_jab_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacJabber);
    return;
}
/**
  * Disables the Jabber frame support.
  * When disabled, GMAC enables jabber timer. It cuts of transmitter if application
  * sends more than 2048 bytes of data (10240 if Jumbo frame enabled).
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_jab_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacJabber);
    return;
}

/**
  * Enables Frame bursting (Only in Half Duplex Mode).
  * When enabled, GMAC allows frame bursting in GMII Half Duplex mode.
  * Reserved in 10/100 and Full-Duplex configurations.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_frame_burst_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacFrameBurst);
    return;
}
/**
  * Disables Frame bursting.
  * When Disabled, frame bursting is not supported.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_frame_burst_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacFrameBurst);
    return;
}

/**
  * Enable Jumbo frame support.
  * When Enabled GMAC supports jumbo frames of 9018/9022(VLAN tagged).
  * Giant frame error is not reported in receive frame status.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_jumbo_frame_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacJumboFrame);
    return;
}
/**
  * Disable Jumbo frame support.
  * When Disabled GMAC does not supports jumbo frames.
  * Giant frame error is reported in receive frame status.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_jumbo_frame_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacJumboFrame);
    return;
}

/**
  * Disable Carrier sense.
  * When Disabled GMAC ignores CRS signal during frame transmission
  * in half duplex mode.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */

void synopGMAC_disable_crs(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacDisableCrs);
    return;
}



/**
  * Selects the GMII port.
  * When called GMII (1000Mbps) port is selected (programmable only in 10/100/1000 Mbps configuration).
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_select_gmii(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacMiiGmii);
    return;
}
/**
  * Selects the MII port.
  * When called MII (10/100Mbps) port is selected (programmable only in 10/100/1000 Mbps configuration).
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_select_mii(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacMiiGmii);
    return;
}

/**
  * Enables Receive Own bit (Only in Half Duplex Mode).
  * When enaled GMAC receives all the packets given by phy while transmitting.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_rx_own_enable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacRxOwn);
    return;
}
/**
  * Disables Receive Own bit (Only in Half Duplex Mode).
  * When enaled GMAC disables the reception of frames when gmii_txen_o is asserted.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_rx_own_disable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacRxOwn);
    return;
}

/**
  * Sets the GMAC in loopback mode.
  * When on GMAC operates in loop-back mode at GMII/MII.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  * \note (G)MII Receive clock is required for loopback to work properly, as transmit clock is
  * not looped back internally.
  */
void synopGMAC_loopback_on(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacLoopback);
    return;
}
/**
  * Sets the GMAC in Normal mode.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_loopback_off(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacLoopback);
    return;
}

/**
  * Sets the GMAC core in Full-Duplex mode.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_set_full_duplex(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacDuplex);
    return;
}
/**
  * Sets the GMAC core in Half-Duplex mode.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_set_half_duplex(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacDuplex);
    return;
}

/**
  * GMAC tries retransmission (Only in Half Duplex mode).
  * If collision occurs on the GMII/MII, GMAC attempt retries based on the
  * back off limit configured.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  * \note This function is tightly coupled with synopGMAC_back_off_limit(synopGMACdev *, u32).
  */
void synopGMAC_retry_enable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacRetry);
    return;
}
/**
  * GMAC tries only one transmission (Only in Half Duplex mode).
  * If collision occurs on the GMII/MII, GMAC will ignore the current frami
  * transmission and report a frame abort with excessive collision in tranmit frame status.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_retry_disable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacRetry);
    return;
}

/**
  * GMAC strips the Pad/FCS field of incoming frames.
  * This is true only if the length field value is less than or equal to
  * 1500 bytes. All received frames with length field greater than or equal to
  * 1501 bytes are passed to the application without stripping the Pad/FCS field.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_pad_crc_strip_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacPadCrcStrip);
    return;
}
/**
  * GMAC doesnot strips the Pad/FCS field of incoming frames.
  * GMAC will pass all the incoming frames to Host unmodified.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_pad_crc_strip_disable(synopGMACdevice *gmacdev)
{
    u32 status;
    synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacPadCrcStrip);
    status = synopGMACReadReg(gmacdev->MacBase, GmacConfig);
    if ((status & GmacPadCrcStrip))
    {
        TR("strips status : %u\n", status & GmacPadCrcStrip);
    }
    return;
}
/**
  * GMAC programmed with the back off limit value.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  * \note This function is tightly coupled with synopGMAC_retry_enable(synopGMACdevice * gmacdev)
  */
void synopGMAC_back_off_limit(synopGMACdevice *gmacdev, u32 value)
{
    u32 data;
    data = synopGMACReadReg(gmacdev->MacBase, GmacConfig);
    data &= (~GmacBackoffLimit);
    data |= value;
    synopGMACWriteReg(gmacdev->MacBase, GmacConfig, data);
    return;
}

/**
  * Enables the Deferral check in GMAC (Only in Half Duplex mode)
  * GMAC issues a Frame Abort Status, along with the excessive deferral error bit set in the
  * transmit frame status when transmit state machine is deferred for more than
  *     - 24,288 bit times in 10/100Mbps mode
  *     - 155,680 bit times in 1000Mbps mode or Jumbo frame mode in 10/100Mbps operation.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  * \note Deferral begins when transmitter is ready to transmit, but is prevented because  of
  * an active CRS (carrier sense)
  */
void synopGMAC_deferral_check_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacDeferralCheck);
    return;
}
/**
  * Disables the Deferral check in GMAC (Only in Half Duplex mode).
  * GMAC defers until the CRS signal goes inactive.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_deferral_check_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacDeferralCheck);
    return;
}
/**
  * Enable the reception of frames on GMII/MII.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_rx_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacRx);
    return;
}
/**
  * Disable the reception of frames on GMII/MII.
  * GMAC receive state machine is disabled after completion of reception of current frame.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_rx_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacRx);
    return;
}
/**
  * Enable the transmission of frames on GMII/MII.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_tx_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacTx);
    return;
}
/**
  * Disable the transmission of frames on GMII/MII.
  * GMAC transmit state machine is disabled after completion of transmission of current frame.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_tx_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacTx);
    return;
}


/*Receive frame filter configuration functions*/

/**
  * Enables reception of all the frames to application.
  * GMAC passes all the frames received to application irrespective of whether they
  * pass SA/DA address filtering or not.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_frame_filter_enable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacFrameFilter, GmacFilter);
    return;
}
/**
  * Disables reception of all the frames to application.
  * GMAC passes only those received frames to application which
  * pass SA/DA address filtering.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_frame_filter_disable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacFrameFilter, GmacFilter);
    return;
}

/**
  * Populates the Hash High register with the data supplied.
  * This function is called when the Hash filtering is to be enabled.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] data to be written to hash table high register.
  * \return void.
  */
void synopGMAC_write_hash_table_high(synopGMACdevice *gmacdev, u32 data)
{
    synopGMACWriteReg(gmacdev->MacBase, GmacHashHigh, data);
    return;
}

/**
  * Populates the Hash Low register with the data supplied.
  * This function is called when the Hash filtering is to be enabled.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] data to be written to hash table low register.
  * \return void.
  */
void synopGMAC_write_hash_table_low(synopGMACdevice *gmacdev, u32 data)
{
    synopGMACWriteReg(gmacdev->MacBase, GmacHashLow, data);
    return;
}

/**
  * Enables Hash or Perfect filter (only if Hash filter is enabled in H/W).
  * Only frames matching either perfect filtering or Hash Filtering as per HMC and HUC
  * configuration are sent to application.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_hash_perfect_filter_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacFrameFilter, GmacHashPerfectFilter);
    return;
}

/**
  * Enables only Hash(only if Hash filter is enabled in H/W).
  * Only frames matching Hash Filtering as per HMC and HUC
  * configuration are sent to application.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_Hash_filter_only_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacFrameFilter, GmacHashPerfectFilter);
    return;
}

/**
  * Enables Source address filtering.
  * When enabled source address filtering is performed. Only frames matching SA filtering are passed  to application with
  * SAMatch bit of RxStatus is set. GMAC drops failed frames.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  * \note This function is overriden by synopGMAC_frame_filter_disable(synopGMACdevice *)
  */
void synopGMAC_src_addr_filter_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacFrameFilter, GmacSrcAddrFilter);
    return;
}
/**
  * Disables Source address filtering.
  * When disabled GMAC forwards the received frames with updated SAMatch bit in RxStatus.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_src_addr_filter_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacFrameFilter, GmacSrcAddrFilter);
    return;
}
/**
  * Enables Inverse Destination address filtering.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_dst_addr_filter_inverse(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacFrameFilter, GmacDestAddrFilterNor);
    return;
}
/**
  * Enables the normal Destination address filtering.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_dst_addr_filter_normal(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacFrameFilter, GmacDestAddrFilterNor);
    return;
}

/**
  * Enables forwarding of control frames.
  * When set forwards all the control frames (incl. unicast and multicast PAUSE frames).
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  * \note Depends on RFE of FlowControlRegister[2]
  */
void synopGMAC_set_pass_control(synopGMACdevice *gmacdev, u32 passcontrol)
{
    u32 data;
    data = synopGMACReadReg(gmacdev->MacBase, GmacFrameFilter);
    data &= (~GmacPassControl);
    data |= passcontrol;
    synopGMACWriteReg(gmacdev->MacBase, GmacFrameFilter, data);
    return;
}

/**
  * Enables Broadcast frames.
  * When enabled Address filtering module passes all incoming broadcast frames.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_broadcast_enable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacFrameFilter, GmacBroadcast);
    return;
}

/**
  * Disable Broadcast frames.
  * When disabled Address filtering module filters all incoming broadcast frames.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_broadcast_disable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacFrameFilter, GmacBroadcast);
    return;
}

/**
  * Enables Multicast frames.
  * When enabled all multicast frames are passed.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_multicast_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacFrameFilter, GmacMulticastFilter);
    return;
}
/**
  * Disable Multicast frames.
  * When disabled multicast frame filtering depends on HMC bit.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_multicast_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacFrameFilter, GmacMulticastFilter);
    return;
}

/**
  * Enables multicast hash filtering.
  * When enabled GMAC performs teh destination address filtering according to the hash table.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_multicast_hash_filter_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacFrameFilter, GmacMcastHashFilter);
    return;
}
/**
  * Disables multicast hash filtering.
  * When disabled GMAC performs perfect destination address filtering for multicast frames, it compares
  * DA field with the value programmed in DA register.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_multicast_hash_filter_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacFrameFilter, GmacMcastHashFilter);
    return;
}

/**
  * Enables promiscous mode.
  * When enabled Address filter modules pass all incoming frames regardless of their Destination
  * and source addresses.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_promisc_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacFrameFilter, GmacPromiscuousMode);
    return;
}
/**
  * Clears promiscous mode.
  * When called the GMAC falls back to normal operation from promiscous mode.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_promisc_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacFrameFilter, GmacPromiscuousMode);
    return;
}


/**
  * Enables unicast hash filtering.
  * When enabled GMAC performs the destination address filtering of unicast frames according to the hash table.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_unicast_hash_filter_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacFrameFilter, GmacUcastHashFilter);
    return;
}
/**
  * Disables multicast hash filtering.
  * When disabled GMAC performs perfect destination address filtering for unicast frames, it compares
  * DA field with the value programmed in DA register.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_unicast_hash_filter_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacFrameFilter, GmacUcastHashFilter);
    return;
}

/*Flow control configuration functions*/

/**
  * Enables detection of pause frames with stations unicast address.
  * When enabled GMAC detects the pause frames with stations unicast address in addition to the
  * detection of pause frames with unique multicast address.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_unicast_pause_frame_detect_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacFlowControl, GmacUnicastPauseFrame);
    return;
}
/**
  * Disables detection of pause frames with stations unicast address.
  * When disabled GMAC only detects with the unique multicast address (802.3x).
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_unicast_pause_frame_detect_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacFlowControl, GmacUnicastPauseFrame);
    return;
}
/**
  * Rx flow control enable.
  * When Enabled GMAC will decode the rx pause frame and disable the tx for a specified time.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_rx_flow_control_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacFlowControl, GmacRxFlowControl);
    return;
}
/**
  * Rx flow control disable.
  * When disabled GMAC will not decode pause frame.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_rx_flow_control_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacFlowControl, GmacRxFlowControl);
    return;
}
/**
  * Tx flow control enable.
  * When Enabled
  *     - In full duplex GMAC enables flow control operation to transmit pause frames.
  * - In Half duplex GMAC enables the back pressure operation
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_tx_flow_control_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacFlowControl, GmacTxFlowControl);
    return;
}

/**
  * Tx flow control disable.
  * When Disabled
  *     - In full duplex GMAC will not transmit any pause frames.
  * - In Half duplex GMAC disables the back pressure feature.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_tx_flow_control_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacFlowControl, GmacTxFlowControl);
    return;
}

/**
  * Initiate Flowcontrol operation.
  * When Set
  *     - In full duplex GMAC initiates pause control frame.
  * - In Half duplex GMAC initiates back pressure function.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_tx_activate_flow_control(synopGMACdevice *gmacdev)
{
    //In case of full duplex check for this bit to b'0. if it is read as b'1 indicates that
    //control frame transmission is in progress.
    if (gmacdev->Speed == FULLDUPLEX)
    {
        if (!synopGMACCheckBits(gmacdev->MacBase, GmacFlowControl, GmacFlowControlBackPressure))
            synopGMACSetBits(gmacdev->MacBase, GmacFlowControl, GmacFlowControlBackPressure);
    }
    else  //if half duplex mode
    {

        synopGMACSetBits(gmacdev->MacBase, GmacFlowControl, GmacFlowControlBackPressure);
    }

    return;
}

/**
  * stops Flowcontrol operation.
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_tx_deactivate_flow_control(synopGMACdevice *gmacdev)
{
    //In full duplex this bit is automatically cleared after transmitting a pause control frame.
    if (gmacdev->Speed == HALFDUPLEX)
    {
        synopGMACSetBits(gmacdev->MacBase, GmacFlowControl, GmacFlowControlBackPressure);
    }
    return;
}

/**
  * This enables the pause frame generation after programming the appropriate registers.
  * presently activation is set at 3k and deactivation set at 4k. These may have to tweaked
  * if found any issues
  * @param[in] pointer to synopGMACdevice.
  * \return void.
  */
void synopGMAC_pause_control(synopGMACdevice *gmacdev)
{
    u32 omr_reg;
    u32 mac_flow_control_reg;
    omr_reg = synopGMACReadReg(gmacdev->DmaBase, DmaControl);
    omr_reg |= DmaRxFlowCtrlAct4K | DmaRxFlowCtrlDeact5K | DmaEnHwFlowCtrl;
    synopGMACWriteReg(gmacdev->DmaBase, DmaControl, omr_reg);

    mac_flow_control_reg = synopGMACReadReg(gmacdev->MacBase, GmacFlowControl);
    mac_flow_control_reg |= GmacRxFlowControl | GmacTxFlowControl | 0xFFFF0000;
    synopGMACWriteReg(gmacdev->MacBase, GmacFlowControl, mac_flow_control_reg);

    return;

}

/**
  * Example mac initialization sequence.
  * This function calls the initialization routines to initialize the GMAC register.
  * One can change the functions invoked here to have different configuration as per the requirement
  * @param[in] pointer to synopGMACdevice.
  * \return Returns 0 on success.
  */
s32 synopGMAC_mac_init(synopGMACdevice *gmacdev)
{
    u32 PHYreg;

    if (gmacdev->DuplexMode == FULLDUPLEX)
    {
        synopGMAC_wd_enable(gmacdev);
        synopGMAC_jab_enable(gmacdev);
        synopGMAC_frame_burst_enable(gmacdev);
        synopGMAC_jumbo_frame_disable(gmacdev);
        synopGMAC_rx_own_enable(gmacdev);
        synopGMAC_loopback_off(gmacdev);
        synopGMAC_set_full_duplex(gmacdev);
        synopGMAC_retry_enable(gmacdev);
        synopGMAC_pad_crc_strip_disable(gmacdev);
        synopGMAC_back_off_limit(gmacdev, GmacBackoffLimit0);
        synopGMAC_deferral_check_disable(gmacdev);


        if (gmacdev->Speed == SPEED1000)
            synopGMAC_select_gmii(gmacdev);
        else
            synopGMAC_select_mii(gmacdev);

        // Cannot enable tx/rx while changing Speed/mode.
        synopGMAC_tx_enable(gmacdev);
        synopGMAC_rx_enable(gmacdev);
        /*Frame Filter Configuration*/
        synopGMAC_frame_filter_enable(gmacdev);
        synopGMAC_set_pass_control(gmacdev, GmacPassControl0);
        synopGMAC_broadcast_enable(gmacdev);
        synopGMAC_src_addr_filter_disable(gmacdev);
        synopGMAC_multicast_disable(gmacdev);
        synopGMAC_dst_addr_filter_normal(gmacdev);
        synopGMAC_multicast_hash_filter_disable(gmacdev);
        synopGMAC_promisc_disable(gmacdev);
        synopGMAC_unicast_hash_filter_disable(gmacdev);

        /*Flow Control Configuration*/
        synopGMAC_unicast_pause_frame_detect_disable(gmacdev);
        synopGMAC_rx_flow_control_enable(gmacdev);
        synopGMAC_tx_flow_control_enable(gmacdev);
    }
    else     //for Half Duplex configuration
    {

        synopGMAC_wd_enable(gmacdev);
        synopGMAC_jab_enable(gmacdev);
        synopGMAC_frame_burst_enable(gmacdev);
        synopGMAC_jumbo_frame_disable(gmacdev);
        synopGMAC_rx_own_enable(gmacdev);
        synopGMAC_loopback_off(gmacdev);
        synopGMAC_set_half_duplex(gmacdev);
        synopGMAC_retry_enable(gmacdev);
        synopGMAC_pad_crc_strip_disable(gmacdev);
        synopGMAC_back_off_limit(gmacdev, GmacBackoffLimit0);
        synopGMAC_deferral_check_disable(gmacdev);


        if (gmacdev->Speed == SPEED1000)
            synopGMAC_select_gmii(gmacdev);
        else
            synopGMAC_select_mii(gmacdev);

        synopGMAC_tx_enable(gmacdev);
        synopGMAC_rx_enable(gmacdev);
        /*Frame Filter Configuration*/
        synopGMAC_frame_filter_enable(gmacdev);
        synopGMAC_set_pass_control(gmacdev, GmacPassControl0);
        synopGMAC_broadcast_enable(gmacdev);
        synopGMAC_src_addr_filter_disable(gmacdev);
        synopGMAC_multicast_disable(gmacdev);
        synopGMAC_dst_addr_filter_normal(gmacdev);
        synopGMAC_multicast_hash_filter_disable(gmacdev);
        synopGMAC_promisc_disable(gmacdev);
        synopGMAC_unicast_hash_filter_disable(gmacdev);

        /*Flow Control Configuration*/
        synopGMAC_unicast_pause_frame_detect_disable(gmacdev);
        synopGMAC_rx_flow_control_disable(gmacdev);
        synopGMAC_tx_flow_control_disable(gmacdev);

        /*To set PHY register to enable CRS on Transmit*/
        synopGMACWriteReg(gmacdev->MacBase, GmacGmiiAddr, GmiiBusy | 0x00000408);
        PHYreg = synopGMACReadReg(gmacdev->MacBase, GmacGmiiData);
        synopGMACWriteReg(gmacdev->MacBase, GmacGmiiData, PHYreg   | 0x00000800);
        synopGMACWriteReg(gmacdev->MacBase, GmacGmiiAddr, GmiiBusy | 0x0000040a);
    }
    return 0;
}

/**
  * Sets the Mac address in to GMAC register.
  * This function sets the MAC address to the MAC register in question.
  * @param[in] pointer to synopGMACdevice to populate mac dma and phy addresses.
  * @param[in] Register offset for Mac address high
  * @param[in] Register offset for Mac address low
  * @param[in] buffer containing mac address to be programmed.
  * \return 0 upon success. Error code upon failure.
  */
s32 synopGMAC_set_mac_addr(synopGMACdevice *gmacdev, u32 MacHigh, u32 MacLow, u8 *MacAddr)
{
    u32 data;

    data = (MacAddr[5] << 8) | MacAddr[4];
    synopGMACWriteReg(gmacdev->MacBase, MacHigh, data);
    data = (MacAddr[3] << 24) | (MacAddr[2] << 16) | (MacAddr[1] << 8) | MacAddr[0] ;
    synopGMACWriteReg(gmacdev->MacBase, MacLow, data);

    return 0;
}


/**
  * Get the Mac address in to the address specified.
  * The mac register contents are read and written to buffer passed.
  * @param[in] pointer to synopGMACdevice to populate mac dma and phy addresses.
  * @param[in] Register offset for Mac address high
  * @param[in] Register offset for Mac address low
  * @param[out] buffer containing the device mac address.
  * \return 0 upon success. Error code upon failure.
  */
s32 synopGMAC_get_mac_addr(synopGMACdevice *gmacdev, u32 MacHigh, u32 MacLow, u8 *MacAddr)
{
    u32 data;

    data = synopGMACReadReg(gmacdev->MacBase, MacHigh);
    MacAddr[5] = (data >> 8) & 0xff;
    MacAddr[4] = (data)      & 0xff;

    data = synopGMACReadReg(gmacdev->MacBase, MacLow);
    MacAddr[3] = (data >> 24) & 0xff;
    MacAddr[2] = (data >> 16) & 0xff;
    MacAddr[1] = (data >> 8)  & 0xff;
    MacAddr[0] = (data)       & 0xff;

    return 0;
}
/**
  * Attaches the synopGMAC device structure to the hardware.
  * Device structure is populated with MAC/DMA and PHY base addresses.
  * @param[in] pointer to synopGMACdevice to populate mac dma and phy addresses.
  * @param[in] GMAC IP mac base address.
  * @param[in] GMAC IP dma base address.
  * @param[in] GMAC IP phy base address.
  * \return 0 upon success. Error code upon failure.
  * \note This is important function. No kernel api provided by Synopsys
  */
static s32 synopGMAC_scan_phyid(synopGMACdevice *gmacdev, u32 phyBase)
{
    int i, j;
    u16 data;

    for (i = phyBase, j = 0; j < 32; i = (i + 1) & 0x1f, j++)
    {
        synopGMAC_read_phy_reg(gmacdev->MacBase, i, 2, &data);
        if (data != 0 && data != 0xffff) break;
        synopGMAC_read_phy_reg(gmacdev->MacBase, i, 3, &data);
        if (data != 0 && data != 0xffff) break;
    }
    if (j == 32)
    {
        j = -1;
    }
    return j;
}

s32 synopGMAC_attach(synopGMACdevice *gmacdev, u32 macBase, u32 dmaBase, u32 phyBase, u8 *mac_addr)
{
    /*Make sure the Device data strucure is cleared before we proceed further*/
    rt_memset((void *) gmacdev, 0, sizeof(synopGMACdevice));

    /*Populate the mac and dma base addresses*/
    gmacdev->MacBase = macBase;
    gmacdev->DmaBase = dmaBase;
    gmacdev->PhyBase = phyBase;

    /* Program/flash in the station/IP's Mac address */
    //synopGMAC_set_mac_addr(gmacdev, GmacAddr0High, GmacAddr0Low, mac_addr);

    if (synopGMAC_scan_phyid(gmacdev, phyBase) < 0)
    {
        return -1;
    }

    return 0;
}


/**
  * Initialize the rx descriptors for ring or chain mode operation.
  *     - Status field is initialized to 0.
  * - EndOfRing set for the last descriptor.
  * - buffer1 and buffer2 set to 0 for ring mode of operation. (note)
  * - data1 and data2 set to 0. (note)
  * @param[in] pointer to DmaDesc structure.
  * @param[in] whether end of ring
  * \return void.
  * \note Initialization of the buffer1, buffer2, data1,data2 and status are not done here. This only initializes whether one wants to use this descriptor
  * in chain mode or ring mode. For chain mode of operation the buffer2 and data2 are programmed before calling this function.
  */
void synopGMAC_rx_desc_init_ring(DmaDesc *desc, bool last_ring_desc)
{
    desc->status = 0;
    desc->length = last_ring_desc ? RxDescEndOfRing : 0;
    desc->buffer1 = 0;
    desc->buffer2 = 0;
    //desc->data1 = 0;
    //desc->data2 = 0;
    return;
}
/**
  * Initialize the tx descriptors for ring or chain mode operation.
  *     - Status field is initialized to 0.
  * - EndOfRing set for the last descriptor.
  * - buffer1 and buffer2 set to 0 for ring mode of operation. (note)
  * - data1 and data2 set to 0. (note)
  * @param[in] pointer to DmaDesc structure.
  * @param[in] whether end of ring
  * \return void.
  * \note Initialization of the buffer1, buffer2, data1,data2 and status are not done here. This only initializes whether one wants to use this descriptor
  * in chain mode or ring mode. For chain mode of operation the buffer2 and data2 are programmed before calling this function.
  */
void synopGMAC_tx_desc_init_ring(DmaDesc *desc, bool last_ring_desc)
{

    desc->status = last_ring_desc ? TxDescEndOfRing : 0;
    desc->length = 0;

    desc->buffer1 = 0;
    desc->buffer2 = 0;
    //desc->data1 = 0;
    //desc->data2 = 0;

    return;
}

s32 synopGMAC_init_tx_rx_desc_queue(synopGMACdevice *gmacdev)
{
    s32 i;
    for (i = 0; i < gmacdev -> TxDescCount; i++)
    {
        synopGMAC_tx_desc_init_ring(gmacdev->TxDesc + i, i == gmacdev->TxDescCount - 1);
    }
    TR("At line %d\n", __LINE__);
    for (i = 0; i < gmacdev -> RxDescCount; i++)
    {
        synopGMAC_rx_desc_init_ring(gmacdev->RxDesc + i, i == gmacdev->RxDescCount - 1);
    }

    gmacdev->TxNext = 0;
    gmacdev->TxBusy = 0;
    gmacdev->RxNext = 0;
    gmacdev->RxBusy = 0;

    return 0;
}

/**
  * Programs the DmaRxBaseAddress with the Rx descriptor base address.
  * Rx Descriptor's base address is available in the gmacdev structure. This function progrms the
  * Dma Rx Base address with the starting address of the descriptor ring or chain.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_init_rx_desc_base(synopGMACdevice *gmacdev)
{
    synopGMACWriteReg(gmacdev->DmaBase, DmaRxBaseAddr, (u32)gmacdev->RxDescDma);
    return;
}

/**
  * Programs the DmaTxBaseAddress with the Tx descriptor base address.
  * Tx Descriptor's base address is available in the gmacdev structure. This function progrms the
  * Dma Tx Base address with the starting address of the descriptor ring or chain.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_init_tx_desc_base(synopGMACdevice *gmacdev)
{
    synopGMACWriteReg(gmacdev->DmaBase, DmaTxBaseAddr, (u32)gmacdev->TxDescDma);
    return;
}


/**
  * Checks whether the descriptor is owned by DMA.
  * If descriptor is owned by DMA then the OWN bit is set to 1. This API is same for both ring and chain mode.
  * @param[in] pointer to DmaDesc structure.
  * \return returns true if Dma owns descriptor and false if not.
  */
bool synopGMAC_is_desc_owned_by_dma(DmaDesc *desc)
{
    return ((desc->status & DescOwnByDma) == DescOwnByDma);
}

/**
  * returns the byte length of received frame including CRC.
  * This returns the no of bytes received in the received ethernet frame including CRC(FCS).
  * @param[in] pointer to DmaDesc structure.
  * \return returns the length of received frame lengths in bytes.
  */
u32 synopGMAC_get_rx_desc_frame_length(u32 status)
{
    return ((status & DescFrameLengthMask) >> DescFrameLengthShift);
}

/**
  * Checks whether the descriptor is valid
  * if no errors such as CRC/Receive Error/Watchdog Timeout/Late collision/Giant Frame/Overflow/Descriptor
  * error the descritpor is said to be a valid descriptor.
  * @param[in] pointer to DmaDesc structure.
  * \return True if desc valid. false if error.
  */
bool synopGMAC_is_desc_valid(u32 status)
{
    return ((status & DescError) == 0);
}

/**
  * Checks whether the descriptor is empty.
  * If the buffer1 and buffer2 lengths are zero in ring mode descriptor is empty.
  * In chain mode buffer2 length is 0 but buffer2 itself contains the next descriptor address.
  * @param[in] pointer to DmaDesc structure.
  * \return returns true if descriptor is empty, false if not empty.
  */
bool synopGMAC_is_desc_empty(DmaDesc *desc)
{
    //if both the buffer1 length and buffer2 length are zero desc is empty
    return (((desc->length  & DescSize1Mask) == 0) && ((desc->length  & DescSize2Mask) == 0));
}


/**
  * Checks whether the rx descriptor is valid.
  * if rx descripor is not in error and complete frame is available in the same descriptor
  * @param[in] pointer to DmaDesc structure.
  * \return returns true if no error and first and last desc bits are set, otherwise it returns false.
  */
bool synopGMAC_is_rx_desc_valid(u32 status)
{
    return ((status & DescError) == 0) && ((status & DescRxFirst) == DescRxFirst) && ((status & DescRxLast) == DescRxLast);
}

/**
  * Checks whether the tx is aborted due to collisions.
  * @param[in] pointer to DmaDesc structure.
  * \return returns true if collisions, else returns false.
  */
bool synopGMAC_is_tx_aborted(u32 status)
{
    return (((status & DescTxLateCollision) == DescTxLateCollision) | ((status & DescTxExcCollisions) == DescTxExcCollisions));

}

/**
  * Checks whether the tx carrier error.
  * @param[in] pointer to DmaDesc structure.
  * \return returns true if carrier error occured, else returns falser.
  */
bool synopGMAC_is_tx_carrier_error(u32 status)
{
    return (((status & DescTxLostCarrier) == DescTxLostCarrier)  | ((status & DescTxNoCarrier) == DescTxNoCarrier));
}


/**
  * Gives the transmission collision count.
  * returns the transmission collision count indicating number of collisions occured before the frame was transmitted.
  * Make sure to check excessive collision didnot happen to ensure the count is valid.
  * @param[in] pointer to DmaDesc structure.
  * \return returns the count value of collision.
  */
u32 synopGMAC_get_tx_collision_count(u32 status)
{
    return ((status & DescTxCollMask) >> DescTxCollShift);
}
u32 synopGMAC_is_exc_tx_collisions(u32 status)
{
    return ((status & DescTxExcCollisions) == DescTxExcCollisions);
}


/**
  * Check for damaged frame due to overflow or collision.
  * Retruns true if rx frame was damaged due to buffer overflow in MTL or late collision in half duplex mode.
  * @param[in] pointer to DmaDesc structure.
  * \return returns true if error else returns false.
  */
bool synopGMAC_is_rx_frame_damaged(u32 status)
{
//bool synopGMAC_dma_rx_collisions(u32 status)
    return (((status & DescRxDamaged) == DescRxDamaged) | ((status & DescRxCollision) == DescRxCollision));
}

/**
  * Check for damaged frame due to collision.
  * Retruns true if rx frame was damaged due to late collision in half duplex mode.
  * @param[in] pointer to DmaDesc structure.
  * \return returns true if error else returns false.
  */
bool synopGMAC_is_rx_frame_collision(u32 status)
{
//bool synopGMAC_dma_rx_collisions(u32 status)
    return ((status & DescRxCollision) == DescRxCollision);
}

/**
  * Check for receive CRC error.
  * Retruns true if rx frame CRC error occured.
  * @param[in] pointer to DmaDesc structure.
  * \return returns true if error else returns false.
  */
bool synopGMAC_is_rx_crc(u32 status)
{
//u32 synopGMAC_dma_rx_crc(u32 status)
    return ((status & DescRxCrc) == DescRxCrc);
}

/**
  * Indicates rx frame has non integer multiple of bytes. (odd nibbles).
  * Retruns true if dribbling error in rx frame.
  * @param[in] pointer to DmaDesc structure.
  * \return returns true if error else returns false.
  */
bool synopGMAC_is_frame_dribbling_errors(u32 status)
{
//u32 synopGMAC_dma_rx_frame_errors(u32 status)
    return ((status & DescRxDribbling) == DescRxDribbling);
}

/**
  * Indicates error in rx frame length.
  * Retruns true if received frame length doesnot match with the length field
  * @param[in] pointer to DmaDesc structure.
  * \return returns true if error else returns false.
  */
bool synopGMAC_is_rx_frame_length_errors(u32 status)
{
//u32 synopGMAC_dma_rx_length_errors(u32 status)
    return ((status & DescRxLengthError) == DescRxLengthError);
}

/**
  * Checks whether this rx descriptor is last rx descriptor.
  * This returns true if it is last descriptor either in ring mode or in chain mode.
  * @param[in] pointer to devic structure.
  * @param[in] pointer to DmaDesc structure.
  * \return returns true if it is last descriptor, false if not.
  * \note This function should not be called before initializing the descriptor using synopGMAC_desc_init().
  */
bool synopGMAC_is_last_rx_desc(synopGMACdevice *gmacdev, DmaDesc *desc)
{
//bool synopGMAC_is_last_desc(DmaDesc *desc)
    return (((desc->length & RxDescEndOfRing) == RxDescEndOfRing) /*|| ((u32)((u64)gmacdev->RxDesc & 0xFFFFFFFF) == desc->data2)*/);
}

/**
  * Checks whether this tx descriptor is last tx descriptor.
  * This returns true if it is last descriptor either in ring mode or in chain mode.
  * @param[in] pointer to devic structure.
  * @param[in] pointer to DmaDesc structure.
  * \return returns true if it is last descriptor, false if not.
  * \note This function should not be called before initializing the descriptor using synopGMAC_desc_init().
  */
bool synopGMAC_is_last_tx_desc(synopGMACdevice *gmacdev, DmaDesc *desc)
{
//bool synopGMAC_is_last_desc(DmaDesc *desc)

    return (((desc->status & TxDescEndOfRing) == TxDescEndOfRing) /*|| ((u32)((u64)gmacdev->TxDesc & 0xFFFFFFFF) == desc->data2)*/);

}


/**
  * This function is defined two times. Once when the code is compiled for ENHANCED DESCRIPTOR SUPPORT and Once for Normal descriptor
  * Get the index and address of Tx desc.
  * This api is same for both ring mode and chain mode.
  * This function tracks the tx descriptor the DMA just closed after the transmission of data from this descriptor is
  * over. This returns the descriptor fields to the caller.
  * @param[in] pointer to synopGMACdevice.
  * @param[out] status field of the descriptor.
  * @param[out] Dma-able buffer1 pointer.
  * @param[out] length of buffer1 (Max is 2048).
  * @param[out] virtual pointer for buffer1.
  * @param[out] u32 data indicating whether the descriptor is in ring mode or chain mode.
  * \return returns present tx descriptor index on success. Negative value if error.
  */
s32 synopGMAC_get_tx_qptr(synopGMACdevice *gmacdev, u32 *Status, u32 *Buffer1, u32 *Length1, u32 *Data1, u32 *Ext_Status, u32 *Time_Stamp_High, u32 *Time_Stamp_Low)
{
    u32  txover      = gmacdev->TxBusy;
#ifdef CACHE_ON
    DmaDesc *txdesc = (DmaDesc *)((u32)(gmacdev->TxBusyDesc) | UNCACHEABLE);
#else
    DmaDesc *txdesc = gmacdev->TxBusyDesc;
#endif
    if (synopGMAC_is_desc_owned_by_dma(txdesc))
        return -1;
    if (synopGMAC_is_desc_empty(txdesc))
        return -1;

    (gmacdev->BusyTxDesc)--; //busy tx descriptor is reduced by one as it will be handed over to Processor now

    if (Status != 0)
        *Status = txdesc->status;

    if (Ext_Status != 0)
        *Ext_Status = txdesc->extstatus;
    if (Time_Stamp_High != 0)
        *Time_Stamp_High = txdesc->timestamphigh;
    if (Time_Stamp_Low != 0)
        *Time_Stamp_Low = txdesc->timestamplow;

    if (Buffer1 != 0)
        *Buffer1 = txdesc->buffer1;
    if (Length1 != 0)
        *Length1 = (txdesc->length & DescSize1Mask) >> DescSize1Shift;
    //if(Data1 != 0)
    //    *Data1 = txdesc->data1;


    gmacdev->TxBusy     = synopGMAC_is_last_tx_desc(gmacdev, txdesc) ? 0 : txover + 1;

    if (1 /* ring mode */)
    {
        gmacdev->TxBusyDesc = synopGMAC_is_last_tx_desc(gmacdev, txdesc) ? gmacdev->TxDesc : (txdesc + 1);
        synopGMAC_tx_desc_init_ring(txdesc, synopGMAC_is_last_tx_desc(gmacdev, txdesc));
    }
//    TR("%02d %08x %08x %08x %08x %08x %08x %08x\n", txover, (u32)txdesc, txdesc->status, txdesc->length, txdesc->buffer1, txdesc->buffer2, txdesc->data1, txdesc->data2);
    TR("%02d %08x %08x %08x %08x %08x\n", txover, (u32)txdesc, txdesc->status, txdesc->length, txdesc->buffer1, txdesc->buffer2);

    return txover;
}

DmaDesc *prevtx;
void synopGMAC_set_crc_replacement(synopGMACdevice *gmacdev)
{
#ifdef CACHE_ON
    DmaDesc *txdesc = (DmaDesc *)((u32)(gmacdev->TxNextDesc) | UNCACHEABLE);
#else
    DmaDesc *txdesc = gmacdev->TxNextDesc;
#endif
    txdesc->status |= DescTxDisableCrc | DescTxCrcReplacement;

    prevtx = txdesc;
}

void synopGMAC_clr_crc_replacement(synopGMACdevice *gmacdev)
{
    prevtx->status &= ~(DescTxDisableCrc | DescTxCrcReplacement);
    prevtx = NULL;
}

/**
  * Populate the tx desc structure with the buffer address.
  * Once the driver has a packet ready to be transmitted, this function is called with the
  * valid dma-able buffer addresses and their lengths. This function populates the descriptor
  * and make the DMA the owner for the descriptor. This function also controls whetther Checksum
  * offloading to be done in hardware or not.
  * This api is same for both ring mode and chain mode.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] Dma-able buffer1 pointer.
  * @param[in] length of buffer1 (Max is 2048).
  * @param[in] virtual pointer for buffer1.

  * @param[in] u32 data indicating whether the descriptor is in ring mode or chain mode.
  * @param[in] u32 indicating whether the checksum offloading in HW/SW.
  * \return returns present tx descriptor index on success. Negative value if error.
  */
s32 synopGMAC_set_tx_qptr(synopGMACdevice *gmacdev, u32 Buffer1, u32 Length1, u32 Data1, u32 offload_needed, u32 ts)
{
    u32  txnext      = gmacdev->TxNext;
#ifdef CACHE_ON
    DmaDesc *txdesc = (DmaDesc *)((u32)(gmacdev->TxNextDesc) | UNCACHEABLE);
#else
    DmaDesc *txdesc = gmacdev->TxNextDesc;
#endif
    if (!synopGMAC_is_desc_empty(txdesc))
        return -1;

    (gmacdev->BusyTxDesc)++; //busy tx descriptor is incremented by one as it will be handed over to DMA

    txdesc->length |= ((Length1 << DescSize1Shift) & DescSize1Mask);

    txdesc->status |= (DescTxFirst | DescTxLast | DescTxIntEnable | (ts == 1 ? DescTxTSEnable : 0));   //ENH_DESC  // FIXME: Need to set DescTxTSEnable?

    txdesc->buffer1 = Buffer1;
    //txdesc->data1 = Data1;

    if (offload_needed)
    {
        /*
          Make sure that the OS you are running supports the IP and TCP checkusm offloaidng,
          before calling any of the functions given below.
          */

        //TODO:
        synopGMAC_tx_checksum_offload_ipv4hdr(gmacdev, txdesc);
        synopGMAC_tx_checksum_offload_tcponly(gmacdev, txdesc);
        synopGMAC_tx_checksum_offload_tcp_pseudo(gmacdev, txdesc);
    }
    else
    {
        synopGMAC_tx_checksum_offload_bypass(gmacdev, txdesc);
    }

    txdesc->status |= DescOwnByDma;//ENH_DESC

    gmacdev->TxNext = synopGMAC_is_last_tx_desc(gmacdev, txdesc) ? 0 : txnext + 1;
    gmacdev->TxNextDesc = synopGMAC_is_last_tx_desc(gmacdev, txdesc) ? gmacdev->TxDesc : (txdesc + 1);

    TR("(set)%02d %08x %08x %08x %08x %08x\n", txnext, (u32)txdesc, txdesc->status, txdesc->length, txdesc->buffer1, txdesc->buffer2);
    //rt_kprintf("(set)%02d %08x %08x %08x %08x %08x\n", txnext, (u32)txdesc, txdesc->status, txdesc->length, txdesc->buffer1, txdesc->buffer2);
    return txnext;
}

/**
  * Prepares the descriptor to receive packets.
  * The descriptor is allocated with the valid buffer addresses (sk_buff address) and the length fields
  * and handed over to DMA by setting the ownership. After successful return from this function the
  * descriptor is added to the receive descriptor pool/queue.
  * This api is same for both ring mode and chain mode.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] Dma-able buffer1 pointer.
  * @param[in] length of buffer1 (Max is 2048).
  * @param[in] Dma-able buffer2 pointer.
  * @param[in] length of buffer2 (Max is 2048).
  * @param[in] u32 data indicating whether the descriptor is in ring mode or chain mode.
  * \return returns present rx descriptor index on success. Negative value if error.
  */
s32 synopGMAC_set_rx_qptr(synopGMACdevice *gmacdev, u32 Buffer1, u32 Length1, u32 Data1)
{
    u32  rxnext      = gmacdev->RxNext;
#ifdef CACHE_ON
    DmaDesc *rxdesc = (DmaDesc *)((u32)(gmacdev->RxNextDesc) | UNCACHEABLE);
#else
    DmaDesc *rxdesc = gmacdev->RxNextDesc;
#endif
    if (!synopGMAC_is_desc_empty(rxdesc))
    {
        return -1;
    }

    rxdesc->length |= ((Length1 << DescSize1Shift) & DescSize1Mask);

    rxdesc->buffer1 = Buffer1;
    //rxdesc->data1 = Data1;

    rxdesc->extstatus = 0;
    rxdesc->reserved1 = 0;
    rxdesc->timestamplow = 0;
    rxdesc->timestamphigh = 0;

    rxdesc->buffer2 = 0;
    //rxdesc->data2 = 0;

    if ((rxnext % MODULO_INTERRUPT) != 0)
        rxdesc->length |= RxDisIntCompl;

    rxdesc->status = DescOwnByDma;

    gmacdev->RxNext     = synopGMAC_is_last_rx_desc(gmacdev, rxdesc) ? 0 : rxnext + 1;
    gmacdev->RxNextDesc = synopGMAC_is_last_rx_desc(gmacdev, rxdesc) ? gmacdev->RxDesc : (rxdesc + 1);

//    TR("%02d %08x %08x %08x %08x %08x %08x %08x\n", rxnext, (u32)rxdesc, rxdesc->status, rxdesc->length, rxdesc->buffer1, rxdesc->buffer2, rxdesc->data1, rxdesc->data2);
    TR("%02d %08x %08x %08x %08x %08x\n", rxnext, (u32)rxdesc, rxdesc->status, rxdesc->length, rxdesc->buffer1, rxdesc->buffer2);

    (gmacdev->BusyRxDesc)++; //One descriptor will be given to Hardware. So busy count incremented by one
    return rxnext;
}


/**
  * This function is defined two times. Once when the code is compiled for ENHANCED DESCRIPTOR SUPPORT and Once for Normal descriptor
  * Get back the descriptor from DMA after data has been received.
  * When the DMA indicates that the data is received (interrupt is generated), this function should be
  * called to get the descriptor and hence the data buffers received. With successful return from this
  * function caller gets the descriptor fields for processing. check the parameters to understand the
  * fields returned.`
  * @param[in] pointer to synopGMACdevice.
  * @param[out] pointer to hold the status of DMA.
  * @param[out] Dma-able buffer1 pointer.
  * @param[out] pointer to hold length of buffer1 (Max is 2048).
  * @param[out] virtual pointer for buffer1.
  * \return returns present rx descriptor index on success. Negative value if error.
  */

s32 synopGMAC_get_rx_qptr(synopGMACdevice *gmacdev, u32 *Status, u32 *Buffer1, u32 *Length1, u32 *Data1,
                          u32 *Ext_Status, u32 *Time_Stamp_High, u32 *Time_Stamp_Low)
{
    u32 rxnext       = gmacdev->RxBusy; // index of descriptor the DMA just completed. May be useful when data
    //is spread over multiple buffers/descriptors
#ifdef CACHE_ON
    DmaDesc *rxdesc = (DmaDesc *)((u32)(gmacdev->RxBusyDesc) | UNCACHEABLE);
#else
    DmaDesc *rxdesc = gmacdev->RxBusyDesc;
#endif
    if (synopGMAC_is_desc_owned_by_dma(rxdesc))
        return -1;

    if (synopGMAC_is_desc_empty(rxdesc))
        return -1;

    if (Status != 0)
        *Status = rxdesc->status;// send the status of this descriptor

    if (Ext_Status != 0)
        *Ext_Status = rxdesc->extstatus;

    if (Time_Stamp_High != 0)
        *Time_Stamp_High = rxdesc->timestamphigh;

    if (Time_Stamp_Low != 0)
        *Time_Stamp_Low = rxdesc->timestamplow;

    if (Length1 != 0)
        *Length1 = (rxdesc->length & DescSize1Mask) >> DescSize1Shift;

    if (Buffer1 != 0)
        *Buffer1 = rxdesc->buffer1;

    //if(Data1 != 0)
    //    *Data1 = rxdesc->data1;

    gmacdev->RxBusy     = synopGMAC_is_last_rx_desc(gmacdev, rxdesc) ? 0 : rxnext + 1;

    /* Ring */
    gmacdev->RxBusyDesc = synopGMAC_is_last_rx_desc(gmacdev, rxdesc) ? gmacdev->RxDesc : (rxdesc + 1);

    /* Wayne's modification */
    synopGMAC_rx_desc_init_ring(rxdesc, synopGMAC_is_last_rx_desc(gmacdev, rxdesc));
    // why init here.... should change onwer to DMA --ya
    //rxdesc->status = DescOwnByDma;
    //rxdesc->extstatus = 0;
    //rxdesc->reserved1 = 0;
    //rxdesc->timestamplow = 0;
    //rxdesc->timestamphigh = 0;
    TR("%02d %08x %08x %08x %08x %08x\n", rxnext, (u32)rxdesc, rxdesc->status, rxdesc->length, rxdesc->buffer1, rxdesc->buffer2);

    TR("%02d %08x %08x %08x %08x %08x\n", rxnext, (u32)rxdesc, rxdesc->status, rxdesc->length, rxdesc->buffer1, rxdesc->buffer2);
    (gmacdev->BusyRxDesc)--; //busy tx descriptor is reduced by one as it will be handed over to Processor now
    return (rxnext);

}


/**
  * Clears all the pending interrupts.
  * If the Dma status register is read then all the interrupts gets cleared
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_clear_interrupt(synopGMACdevice *gmacdev)
{
    u32 data;
    data = synopGMACReadReg(gmacdev->DmaBase, DmaStatus);
    synopGMACWriteReg(gmacdev->DmaBase, DmaStatus, data);
}

/**
  * Returns the all unmasked interrupt status after reading the DmaStatus register.
  * @param[in] pointer to synopGMACdevice.
  * \return 0 upon success. Error code upon failure.
  */
u32 synopGMAC_get_interrupt_type(synopGMACdevice *gmacdev)
{
    u32 data;
    u32 interrupts = 0;
    data = synopGMACReadReg(gmacdev->DmaBase, DmaStatus);
    synopGMACWriteReg(gmacdev->DmaBase, DmaStatus, data); //This is the appropriate location to clear the interrupts
    //TR("DMA status reg is  %08x\n", data);
    if (data & DmaIntErrorMask)  interrupts     |= synopGMACDmaError;
    if (data & DmaIntRxNormMask) interrupts     |= synopGMACDmaRxNormal;
    if (data & DmaIntRxAbnMask)  interrupts     |= synopGMACDmaRxAbnormal;
    if (data & DmaIntRxStoppedMask)  interrupts |= synopGMACDmaRxStopped;
    if (data & DmaIntTxNormMask) interrupts     |= synopGMACDmaTxNormal;
    if (data & DmaIntTxAbnMask)  interrupts     |= synopGMACDmaTxAbnormal;
    if (data & DmaIntTxStoppedMask)  interrupts |= synopGMACDmaTxStopped;

    return interrupts;
}


/**
  * Enable all the interrupts.
  * Enables the DMA interrupt as specified by the bit mask.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] bit mask of interrupts to be enabled.
  * \return returns void.
  */
void synopGMAC_enable_interrupt(synopGMACdevice *gmacdev, u32 interrupts)
{
    synopGMACWriteReg(gmacdev->DmaBase, DmaInterrupt, interrupts);
    return;
}

void synopGMAC_get_ie(synopGMACdevice *gmacdev)
{
    synopGMACReadReg(gmacdev->DmaBase, DmaInterrupt);
    return;
}

/**
  * Disable all the interrupts.
  * Disables all DMA interrupts.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  * \note This function disabled all the interrupts, if you want to disable a particular interrupt then
  *  use synopGMAC_disable_interrupt().
  */
void synopGMAC_disable_interrupt_all(synopGMACdevice *gmacdev)
{
    synopGMACWriteReg(gmacdev->DmaBase, DmaInterrupt, DmaIntDisable);
    return;
}

/**
  * Disable interrupt according to the bitfield supplied.
  * Disables only those interrupts specified in the bit mask in second argument.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] bit mask for interrupts to be disabled.
  * \return returns void.
  */
void synopGMAC_disable_interrupt(synopGMACdevice *gmacdev, u32 interrupts)
{
    synopGMACClearBits(gmacdev->DmaBase, DmaInterrupt, interrupts);
    return;
}
/**
  * Enable the DMA Reception.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_enable_dma_rx(synopGMACdevice *gmacdev)
{
//  synopGMACSetBits(gmacdev->DmaBase, DmaControl, DmaRxStart);
    u32 data;
    data = synopGMACReadReg(gmacdev->DmaBase, DmaControl);
    data |= DmaRxStart;
    synopGMACWriteReg(gmacdev->DmaBase, DmaControl, data);

}

/**
  * Enable the DMA Transmission.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_enable_dma_tx(synopGMACdevice *gmacdev)
{
//  synopGMACSetBits(gmacdev->DmaBase, DmaControl, DmaTxStart);
    u32 data;
    data = synopGMACReadReg(gmacdev->DmaBase, DmaControl);
    data |= DmaTxStart;
    synopGMACWriteReg(gmacdev->DmaBase, DmaControl, data);

}

void synopGMAC_enable_under_size_pkt(synopGMACdevice *gmacdev)
{
    u32 data;
    data = synopGMACReadReg(gmacdev->DmaBase, DmaControl);
    data |= DmaFwdUnderSzFrames;
    synopGMACWriteReg(gmacdev->DmaBase, DmaControl, data);

}

void synopGMAC_disable_under_size_pkt(synopGMACdevice *gmacdev)
{
    u32 data;
    data = synopGMACReadReg(gmacdev->DmaBase, DmaControl);
    data &= ~DmaFwdUnderSzFrames;
    synopGMACWriteReg(gmacdev->DmaBase, DmaControl, data);

}

void synopGMAC_enable_crc_err_pkt(synopGMACdevice *gmacdev)
{
    u32 data;
    data = synopGMACReadReg(gmacdev->DmaBase, DmaControl);
    data |= DmaFwdErrorFrames;
    synopGMACWriteReg(gmacdev->DmaBase, DmaControl, data);

}

void synopGMAC_disable_crc_err_pkt(synopGMACdevice *gmacdev)
{
    u32 data;
    data = synopGMACReadReg(gmacdev->DmaBase, DmaControl);
    data &= ~DmaFwdErrorFrames;
    synopGMACWriteReg(gmacdev->DmaBase, DmaControl, data);

}


/**
  * Resumes the DMA Transmission.
  * the DmaTxPollDemand is written. (the data writeen could be anything).
  * This forces the DMA to resume transmission.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_resume_dma_tx(synopGMACdevice *gmacdev)
{
    synopGMACWriteReg(gmacdev->DmaBase, DmaTxPollDemand, 0);

}
/**
  * Resumes the DMA Reception.
  * the DmaRxPollDemand is written. (the data writeen could be anything).
  * This forces the DMA to resume reception.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_resume_dma_rx(synopGMACdevice *gmacdev)
{
    synopGMACWriteReg(gmacdev->DmaBase, DmaRxPollDemand, 0);

}
/**
  * Take ownership of this Descriptor.
  * The function is same for both the ring mode and the chain mode DMA structures.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_take_desc_ownership(DmaDesc *desc)
{
    if (desc)
    {
        desc->status &= ~DescOwnByDma;  //Clear the DMA own bit
//      desc->status |= DescError;  // Set the error to indicate this descriptor is bad
    }
}

/**
  * Take ownership of all the rx Descriptors.
  * This function is called when there is fatal error in DMA transmission.
  * When called it takes the ownership of all the rx descriptor in rx descriptor pool/queue from DMA.
  * The function is same for both the ring mode and the chain mode DMA structures.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  * \note Make sure to disable the transmission before calling this function, otherwise may result in racing situation.
  */
void synopGMAC_take_desc_ownership_rx(synopGMACdevice *gmacdev)
{
    s32 i;
    DmaDesc *desc;
    desc = gmacdev->RxDesc;
    for (i = 0; i < gmacdev->RxDescCount; i++)
    {
        synopGMAC_take_desc_ownership(desc + i);
    }
}

/**
  * Take ownership of all the rx Descriptors.
  * This function is called when there is fatal error in DMA transmission.
  * When called it takes the ownership of all the tx descriptor in tx descriptor pool/queue from DMA.
  * The function is same for both the ring mode and the chain mode DMA structures.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  * \note Make sure to disable the transmission before calling this function, otherwise may result in racing situation.
  */
void synopGMAC_take_desc_ownership_tx(synopGMACdevice *gmacdev)
{
    s32 i;
    DmaDesc *desc;
    desc = gmacdev->TxDesc;
    for (i = 0; i < gmacdev->TxDescCount; i++)
    {
        synopGMAC_take_desc_ownership(desc + i);
    }

}

/**
  * Disable the DMA for Transmission.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */

void synopGMAC_disable_dma_tx(synopGMACdevice *gmacdev)
{
//  synopGMACClearBits(gmacdev->DmaBase, DmaControl, DmaTxStart);
    u32 data;
    data = synopGMACReadReg(gmacdev->DmaBase, DmaControl);
    data &= (~DmaTxStart);
    synopGMACWriteReg(gmacdev->DmaBase, DmaControl, data);
}
/**
  * Disable the DMA for Reception.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_disable_dma_rx(synopGMACdevice *gmacdev)
{
//  synopGMACClearBits(gmacdev->DmaBase, DmaControl, DmaRxStart);
    u32 data;
    data = synopGMACReadReg(gmacdev->DmaBase, DmaControl);
    data &= (~DmaRxStart);
    synopGMACWriteReg(gmacdev->DmaBase, DmaControl, data);
}



/*******************PMT APIs***************************************/




/**
  * Enables the assertion of PMT interrupt.
  * This enables the assertion of PMT interrupt due to Magic Pkt or Wakeup frame
  * reception.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_pmt_int_enable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacInterruptMask, GmacPmtIntMask);
    return;
}
/**
  * Disables the assertion of PMT interrupt.
  * This disables the assertion of PMT interrupt due to Magic Pkt or Wakeup frame
  * reception.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_pmt_int_disable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacInterruptMask, GmacPmtIntMask);
    return;
}
/**
  * Enables the power down mode of GMAC.
  * This function puts the Gmac in power down mode.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_power_down_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacPmtCtrlStatus, GmacPmtPowerDown);
    return;
}
/**
  * Disables the powerd down setting of GMAC.
  * If the driver wants to bring up the GMAC from powerdown mode, even though the magic packet or the
  * wake up frames received from the network, this function should be called.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_power_down_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacPmtCtrlStatus, GmacPmtPowerDown);
    return;
}
/**
  * Enables the pmt interrupt generation in powerdown mode.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_enable_pmt_interrupt(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacInterruptMask, GmacPmtIntMask);
}
/**
  * Disables the pmt interrupt generation in powerdown mode.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_disable_pmt_interrupt(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacInterruptMask, GmacPmtIntMask);
}
/**
  * Enables GMAC to look for Magic packet.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_magic_packet_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacPmtCtrlStatus, GmacPmtMagicPktEnable);
    return;
}

void synopGMAC_magic_packet_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacPmtCtrlStatus, GmacPmtMagicPktEnable);
    return;
}

/**
  * Enables GMAC to look for wake up frame.
  * Wake up frame is defined by the user.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_wakeup_frame_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacPmtCtrlStatus, GmacPmtWakeupFrameEnable);
    return;
}

/**
  * Enables wake-up frame filter to handle unicast packets.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_pmt_unicast_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacPmtCtrlStatus, GmacPmtGlobalUnicast);
    return;
}
/**
  * Checks whether the packet received is a magic packet?.
  * @param[in] pointer to synopGMACdevice.
  * \return returns True if magic packet received else returns false.
  */
bool synopGMAC_is_magic_packet_received(synopGMACdevice *gmacdev)
{
    u32 data;
    data =  synopGMACReadReg(gmacdev->MacBase, GmacPmtCtrlStatus);
    return ((data & GmacPmtMagicPktReceived) == GmacPmtMagicPktReceived);
}
/**
  * Checks whether the packet received is a wakeup frame?.
  * @param[in] pointer to synopGMACdevice.
  * \return returns true if wakeup frame received else returns false.
  */
bool synopGMAC_is_wakeup_frame_received(synopGMACdevice *gmacdev)
{
    u32 data;
    data =  synopGMACReadReg(gmacdev->MacBase, GmacPmtCtrlStatus);
    return ((data & GmacPmtWakeupFrameReceived) == GmacPmtWakeupFrameReceived);
}

/**
  * Populates the remote wakeup frame registers.
  * Consecutive 8 writes to GmacWakeupAddr writes the wakeup frame filter registers.
  * Before commensing a new write, frame filter pointer is reset to 0x0000.
  * A small delay is introduced to allow frame filter pointer reset operation.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] pointer to frame filter contents array.
  * \return returns void.
  */
#if 0
void synopGMAC_write_wakeup_frame_register(synopGMACdevice *gmacdev, u32 *filter_contents)
{
    s32 i;
    synopGMACSetBits(gmacdev->MacBase, GmacPmtCtrlStatus, GmacPmtFrmFilterPtrReset);
    plat_delay(10);
    for (i = 0; i < WAKEUP_REG_LENGTH; i++)
        synopGMACWriteReg(gmacdev->MacBase, GmacWakeupAddr,  *(filter_contents + i));
    return;

}
#endif
/*******************PMT APIs***************************************/

/*******************Ip checksum offloading APIs***************************************/

/**
  * Enables the ip checksum offloading in receive path.
  * When set GMAC calculates 16 bit 1's complement of all received ethernet frame payload.
  * It also checks IPv4 Header checksum is correct. GMAC core appends the 16 bit checksum calculated
  * for payload of IP datagram and appends it to Ethernet frame transferred to the application.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_enable_rx_chksum_offload(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacRxIpcOffload);
    return;
}
/**
  * Disable the ip checksum offloading in receive path.
  * Ip checksum offloading is disabled in the receive path.
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_disable_rx_chksum_offload(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacRxIpcOffload);
}
/**
  * Instruct the DMA to drop the packets fails tcp ip checksum.
  * This is to instruct the receive DMA engine to drop the recevied packet if they
  * fails the tcp/ip checksum in hardware. Valid only when full checksum offloading is enabled(type-2).
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_rx_tcpip_chksum_drop_enable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->DmaBase, DmaControl, DmaDisableDropTcpCs);
    return;
}
/**
  * Instruct the DMA not to drop the packets even if it fails tcp ip checksum.
  * This is to instruct the receive DMA engine to allow the packets even if recevied packet
  * fails the tcp/ip checksum in hardware. Valid only when full checksum offloading is enabled(type-2).
  * @param[in] pointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_rx_tcpip_chksum_drop_disable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->DmaBase, DmaControl, DmaDisableDropTcpCs);
    return;
}

/**
  * When the Enhanced Descriptor is enabled then the bit 0 of RDES0 indicates whether the
  * Extended Status is available (RDES4). Time Stamp feature and the Checksum Offload Engine2
  * makes use of this extended status to provide the status of the received packet.
  * @param[in] pointer to synopGMACdevice
  * \return returns TRUE or FALSE
  */


/**
  * This function indicates whether extended status is available in the RDES0.
  * Any function which accesses the fields of extended status register must ensure a check on this has been made
  * This is valid only for Enhanced Descriptor.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] u32 status field of the corresponding descriptor.
  * \return returns TRUE or FALSE.
  */
bool synopGMAC_is_ext_status(synopGMACdevice *gmacdev, u32 status)            // extended status present indicates that the RDES4 need to be probed
{
    return ((status & DescRxEXTsts) != 0);  // if extstatus set then it returns 1
}
/**
  * This function returns true if the IP header checksum bit is set in the extended status.
  * Valid only when enhaced status available is set in RDES0 bit 0.
  * This is valid only for Enhanced Descriptor.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] u32 status field of the corresponding descriptor.
  * \return returns TRUE or FALSE.
  */
bool synopGMAC_ES_is_IP_header_error(synopGMACdevice *gmacdev, u32 ext_status)         // IP header (IPV4) checksum error
{
    return ((ext_status & DescRxIpHeaderError) != 0); // if IPV4 header error return 1
}
/**
  * This function returns true if the Checksum is bypassed in the hardware.
  * Valid only when enhaced status available is set in RDES0 bit 0.
  * This is valid only for Enhanced Descriptor.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] u32 status field of the corresponding descriptor.
  * \return returns TRUE or FALSE.
  */
bool synopGMAC_ES_is_rx_checksum_bypassed(synopGMACdevice *gmacdev, u32 ext_status)    // Hardware engine bypassed the checksum computation/checking
{
    return ((ext_status & DescRxChkSumBypass) != 0);  // if checksum offloading bypassed return 1
}
/**
  * This function returns true if payload checksum error is set in the extended status.
  * Valid only when enhaced status available is set in RDES0 bit 0.
  * This is valid only for Enhanced Descriptor.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] u32 status field of the corresponding descriptor.
  * \return returns TRUE or FALSE.
  */
bool synopGMAC_ES_is_IP_payload_error(synopGMACdevice *gmacdev, u32 ext_status)        // IP payload checksum is in error (UDP/TCP/ICMP checksum error)
{
    return ((ext_status & DescRxIpPayloadError) != 0); // if IP payload error return 1
}




/**
  * Decodes the Rx Descriptor status to various checksum error conditions.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] u32 status field of the corresponding descriptor.
  * \return returns decoded enum (u32) indicating the status.
  */
u32 synopGMAC_is_rx_checksum_error(synopGMACdevice *gmacdev, u32 status)
{
    if (((status & DescRxChkBit5) == 0) && ((status & DescRxChkBit7) == 0) && ((status & DescRxChkBit0) == 0))
        return RxLenLT600;
    else if (((status & DescRxChkBit5) == 0) && ((status & DescRxChkBit7) == 0) && ((status & DescRxChkBit0) != 0))
        return RxIpHdrPayLoadChkBypass;
    else if (((status & DescRxChkBit5) == 0) && ((status & DescRxChkBit7) != 0) && ((status & DescRxChkBit0) != 0))
        return RxChkBypass;
    else if (((status & DescRxChkBit5) != 0) && ((status & DescRxChkBit7) == 0) && ((status & DescRxChkBit0) == 0))
        return RxNoChkError;
    else if (((status & DescRxChkBit5) != 0) && ((status & DescRxChkBit7) == 0) && ((status & DescRxChkBit0) != 0))
        return RxPayLoadChkError;
    else if (((status & DescRxChkBit5) != 0) && ((status & DescRxChkBit7) != 0) && ((status & DescRxChkBit0) == 0))
        return RxIpHdrChkError;
    else if (((status & DescRxChkBit5) != 0) && ((status & DescRxChkBit7) != 0) && ((status & DescRxChkBit0) != 0))
        return RxIpHdrPayLoadChkError;
    else
        return RxIpHdrPayLoadRes;
}
/**
  * Checks if any Ipv4 header checksum error in the frame just transmitted.
  * This serves as indication that error occureed in the IPv4 header checksum insertion.
  * The sent out frame doesnot carry any ipv4 header checksum inserted by the hardware.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] u32 status field of the corresponding descriptor.
  * \return returns true if error in ipv4 header checksum, else returns false.
  */
bool synopGMAC_is_tx_ipv4header_checksum_error(synopGMACdevice *gmacdev, u32 status)
{
    return ((status & DescTxIpv4ChkError) == DescTxIpv4ChkError);
}


/**
  * Checks if any payload checksum error in the frame just transmitted.
  * This serves as indication that error occureed in the payload checksum insertion.
  * The sent out frame doesnot carry any payload checksum inserted by the hardware.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] u32 status field of the corresponding descriptor.
  * \return returns true if error in ipv4 header checksum, else returns false.
  */
bool synopGMAC_is_tx_payload_checksum_error(synopGMACdevice *gmacdev, u32 status)
{
    return ((status & DescTxPayChkError) == DescTxPayChkError);
}
/**
  * The check summ offload engine is bypassed in the tx path.
  * Checksum is not computed in the Hardware.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] Pointer to tx descriptor for which  ointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_tx_checksum_offload_bypass(synopGMACdevice *gmacdev, DmaDesc *desc)
{
    desc->status = (desc->status & (~DescTxCisMask));//ENH_DESC


}
/**
  * The check summ offload engine is enabled to do only IPV4 header checksum.
  * IPV4 header Checksum is computed in the Hardware.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] Pointer to tx descriptor for which  ointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_tx_checksum_offload_ipv4hdr(synopGMACdevice *gmacdev, DmaDesc *desc)
{

    desc->status = ((desc->status & (~DescTxCisMask)) | DescTxCisIpv4HdrCs);//ENH_DESC


}

/**
  * The check summ offload engine is enabled to do TCPIP checsum assuming Pseudo header is available.
  * Hardware computes the tcp ip checksum assuming pseudo header checksum is computed in software.
  * Ipv4 header checksum is also inserted.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] Pointer to tx descriptor for which  ointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_tx_checksum_offload_tcponly(synopGMACdevice *gmacdev, DmaDesc *desc)
{

    desc->status = ((desc->status & (~DescTxCisMask)) | DescTxCisTcpOnlyCs);//ENH_DESC


}
/**
  * The check summ offload engine is enabled to do complete checksum computation.
  * Hardware computes the tcp ip checksum including the pseudo header checksum.
  * Here the tcp payload checksum field should be set to 0000.
  * Ipv4 header checksum is also inserted.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] Pointer to tx descriptor for which  ointer to synopGMACdevice.
  * \return returns void.
  */
void synopGMAC_tx_checksum_offload_tcp_pseudo(synopGMACdevice *gmacdev, DmaDesc *desc)
{

    desc->status = ((desc->status & (~DescTxCisMask)) | DescTxCisTcpPseudoCs);


}
/*******************Ip checksum offloading APIs***************************************/





/*******************IEEE 1588 Timestamping API***************************************/


/*
 * At this time the driver supports the IEEE time stamping feature when the Enhanced Descriptors are enabled.
 * For normal descriptor and the IEEE time stamp (version 1), driver support is not proviced
 * Please make sure you have enabled the Advanced timestamp feature in the hardware and the driver should
 * be compiled with the ADV_TME_STAMP feature.
 * Some of the APIs provided here may not be valid for all configurations. Please make sure you call the
 * API with due care.
 */

/**
  * This function enables the timestamping. This enables the timestamping for transmit and receive frames.
  * When disabled timestamp is not added to tx and receive frames and timestamp generator is suspended.
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacTSControl, GmacTSENA);
    return;
}
/**
  * This function disables the timestamping.
  * When disabled timestamp is not added to tx and receive frames and timestamp generator is suspended.
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacTSControl, GmacTSENA);
    return;
}


/**
  * Enable the interrupt to get timestamping interrupt.
  * This enables the host to get the interrupt when (1) system time is greater or equal to the
  * target time high and low register or (2) there is a overflow in th esecond register.
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_int_enable(synopGMACdevice *gmacdev)
{
    //synopGMACClearBits(gmacdev->MacBase,GmacInterruptMask,GmacTSIntMask);
    synopGMACSetBits(gmacdev->MacBase, GmacTSControl, GmacTSTRIG);
    return;
}

/**
  * Disable the interrupt to get timestamping interrupt.
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_int_disable(synopGMACdevice *gmacdev)
{
    //synopGMACSetBits(gmacdev->MacBase,GmacInterruptMask,GmacTSIntMask);
    synopGMACClearBits(gmacdev->MacBase, GmacTSControl, GmacTSTRIG);
    return;
}

/**
  * Enable MAC address for PTP frame filtering.
  * When enabled, uses MAC address (apart from MAC address 0) to filter the PTP frames when
  * PTP is sent directly over Ethernet.
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_mac_addr_filt_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacTSControl, GmacTSENMACADDR);
    return;
}

/**
  * Disables MAC address for PTP frame filtering.
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_mac_addr_filt_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacTSControl, GmacTSENMACADDR);
    return;
}


/**
  * Selet the type of clock mode for PTP.
  * Please note to use one of the follwoing as the clk_type argument.
  * GmacTSOrdClk          = 0x00000000,      00=> Ordinary clock
  * GmacTSBouClk          = 0x00010000,      01=> Boundary clock
  * GmacTSEtoEClk         = 0x00020000,      10=> End-to-End transparent clock
  * GmacTSPtoPClk         = 0x00030000,      11=> P-to-P transparent clock
  * @param[in] pointer to synopGMACdevice
  * @param[in] u32 value representing one of the above clk value
  * \return returns void
  */
void synopGMAC_TS_set_clk_type(synopGMACdevice *gmacdev, u32 clk_type)
{
    u32 clkval;
    clkval = synopGMACReadReg(gmacdev->MacBase, GmacTSControl); //set the mdc clock to the user defined value
    clkval = (clkval & ~GmacTSCLKTYPE) | clk_type;
    synopGMACWriteReg(gmacdev->MacBase, GmacTSControl, clkval);
    return;
}

/**
  * Enable Snapshot for messages relevant to Master.
  * When enabled, snapshot is taken for messages relevant to master mode only, else snapshot is taken for messages relevant
  * to slave node.
  * Valid only for Ordinary clock and Boundary clock
  * Reserved when "Advanced Time Stamp" is not selected
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_master_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacTSControl, GmacTSMSTRENA);
    return;
}
/**
  * Disable Snapshot for messages relevant to Master.
  * When disabled, snapshot is taken for messages relevant
  * to slave node.
  * Valid only for Ordinary clock and Boundary clock
  * Reserved when "Advanced Time Stamp" is not selected
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_master_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacTSControl, GmacTSMSTRENA);
    return;
}
/**
  * Enable Snapshot for Event messages.
  * When enabled, snapshot is taken for event messages only (SYNC, Delay_Req, Pdelay_Req or Pdelay_Resp)
  * When disabled, snapshot is taken for all messages except Announce, Management and Signaling.
  * Reserved when "Advanced Time Stamp" is not selected
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_event_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacTSControl, GmacTSEVNTENA);
    return;
}
/**
  * Disable Snapshot for Event messages.
  * When disabled, snapshot is taken for all messages except Announce, Management and Signaling.
  * Reserved when "Advanced Time Stamp" is not selected
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_event_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacTSControl, GmacTSEVNTENA);
    return;
}

/**
  * Enable time stamp snapshot for IPV4 frames.
  * When enabled, time stamp snapshot is taken for IPV4 frames
  * Reserved when "Advanced Time Stamp" is not selected
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_IPV4_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacTSControl, GmacTSIPV4ENA);
    return;
}
/**
  * Disable time stamp snapshot for IPV4 frames.
  * When disabled, time stamp snapshot is not taken for IPV4 frames
  * Reserved when "Advanced Time Stamp" is not selected
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_IPV4_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacTSControl, GmacTSIPV4ENA);
    return;
}                    // Only for "Advanced Time Stamp"
/**
  * Enable time stamp snapshot for IPV6 frames.
  * When enabled, time stamp snapshot is taken for IPV6 frames
  * Reserved when "Advanced Time Stamp" is not selected
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_IPV6_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacTSControl, GmacTSIPV6ENA);
    return;
}
/**
  * Disable time stamp snapshot for IPV6 frames.
  * When disabled, time stamp snapshot is not taken for IPV6 frames
  * Reserved when "Advanced Time Stamp" is not selected
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_IPV6_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacTSControl, GmacTSIPV6ENA);
    return;
}

/**
  * Enable time stamp snapshot for PTP over Ethernet frames.
  * When enabled, time stamp snapshot is taken for PTP over Ethernet frames
  * Reserved when "Advanced Time Stamp" is not selected
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_ptp_over_ethernet_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacTSControl, GmacTSIPENA);
    return;
}
/**
  * Disable time stamp snapshot for PTP over Ethernet frames.
  * When disabled, time stamp snapshot is not taken for PTP over Ethernet frames
  * Reserved when "Advanced Time Stamp" is not selected
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_ptp_over_ethernet_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacTSControl, GmacTSIPENA);
    return;
}


/**
  * Snoop PTP packet for version 2 format
  * When set the PTP packets are snooped using the version 2 format.
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_pkt_snoop_ver2(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacTSControl, GmacTSVER2ENA);
    return;
}
/**
  * Snoop PTP packet for version 2 format
  * When set the PTP packets are snooped using the version 2 format.
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_pkt_snoop_ver1(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacTSControl, GmacTSVER2ENA);
    return;
}

/**
  * Timestamp digital rollover
  * When set the timestamp low register rolls over after 0x3B9A_C9FF value.
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_digital_rollover_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacTSControl, GmacTSCTRLSSR);
    return;
}
/**
  * Timestamp binary rollover
  * When set the timestamp low register rolls over after 0x7FFF_FFFF value.
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_binary_rollover_enable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacTSControl, GmacTSCTRLSSR);
    return;
}
/**
  * Enable Time Stamp for All frames
  * When set the timestamp snap shot is enabled for all frames received by the core.
  * Reserved when "Advanced Time Stamp" is not selected
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_all_frames_enable(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacTSControl, GmacTSENALL);
    return;
}
/**
  * Disable Time Stamp for All frames
  * When reset the timestamp snap shot is not enabled for all frames received by the core.
  * Reserved when "Advanced Time Stamp" is not selected
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_all_frames_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacTSControl, GmacTSENALL);
    return;
}
/**
  * Addend Register Update
  * This function loads the contents of Time stamp addend register with the supplied 32 value.
  * This is reserved function when only coarse correction option is selected
  * @param[in] pointer to synopGMACdevice
  * @param[in] 32 bit addend value
  * \return returns 0 for Success or else Failure
  */
s32 synopGMAC_TS_addend_update(synopGMACdevice *gmacdev, u32 addend_value)
{
    u32 loop_variable;
    synopGMACWriteReg(gmacdev->MacBase, GmacTSAddend, addend_value); // Load the addend_value in to Addend register
    for (loop_variable = 0; loop_variable < DEFAULT_LOOP_VARIABLE; loop_variable++)  //Wait till the busy bit gets cleared with in a certain amount of time
    {
        if (!((synopGMACReadReg(gmacdev->MacBase, GmacTSControl)) & GmacTSADDREG)) // if it is cleared then break
        {
            break;
        }
        plat_delay(DEFAULT_DELAY_VARIABLE);
    }
    if (loop_variable < DEFAULT_LOOP_VARIABLE)
        synopGMACSetBits(gmacdev->MacBase, GmacTSControl, GmacTSADDREG);
    else
    {
        TR("Error::: The TSADDREG bit is not getting cleared !!!!!!\n");
        return -ESYNOPGMACPHYERR;
    }
    return 0;

}
/**
  * time stamp Update
  * This function updates (adds/subtracts) with the value specified in the Timestamp High Update and
  * Timestamp Low Update register.
  * @param[in] pointer to synopGMACdevice
  * @param[in] Timestamp High Update value
  * @param[in] Timestamp Low Update value
  * \return returns 0 for Success or else Failure
  */
s32 synopGMAC_TS_timestamp_update(synopGMACdevice *gmacdev, u32 high_value, u32 low_value)
{
    u32 loop_variable;
    synopGMACWriteReg(gmacdev->MacBase, GmacTSHighUpdate, high_value); // Load the high value to Timestamp High register
    synopGMACWriteReg(gmacdev->MacBase, GmacTSLowUpdate, low_value); // Load the high value to Timestamp High register
    for (loop_variable = 0; loop_variable < DEFAULT_LOOP_VARIABLE; loop_variable++)  //Wait till the busy bit gets cleared with in a certain amount of time
    {
        if (!((synopGMACReadReg(gmacdev->MacBase, GmacTSControl)) & GmacTSUPDT)) // if it is cleared then break
        {
            break;
        }
        plat_delay(DEFAULT_DELAY_VARIABLE);
    }
    if (loop_variable < DEFAULT_LOOP_VARIABLE)
        synopGMACSetBits(gmacdev->MacBase, GmacTSControl, GmacTSUPDT);
    else
    {
        TR("Error::: The TSADDREG bit is not getting cleared !!!!!!\n");
        return -ESYNOPGMACPHYERR;
    }
    return 0;
}

/**
  * time stamp Initialize
  * This function Loads/Initializes h the value specified in the Timestamp High Update and
  * Timestamp Low Update register.
  * @param[in] pointer to synopGMACdevice
  * @param[in] Timestamp High Load value
  * @param[in] Timestamp Low Load value
  * \return returns 0 for Success or else Failure
  */
s32 synopGMAC_TS_timestamp_init(synopGMACdevice *gmacdev, u32 high_value, u32 low_value)
{
    u32 loop_variable;
    synopGMACWriteReg(gmacdev->MacBase, GmacTSHighUpdate, high_value); // Load the high value to Timestamp High register
    synopGMACWriteReg(gmacdev->MacBase, GmacTSLowUpdate, low_value); // Load the high value to Timestamp High register
    for (loop_variable = 0; loop_variable < DEFAULT_LOOP_VARIABLE; loop_variable++)  //Wait till the busy bit gets cleared with in a certain amount of time
    {
        if (!((synopGMACReadReg(gmacdev->MacBase, GmacTSControl)) & GmacTSINT)) // if it is cleared then break
        {
            break;
        }
        plat_delay(DEFAULT_DELAY_VARIABLE);
    }
    if (loop_variable < DEFAULT_LOOP_VARIABLE)
        synopGMACSetBits(gmacdev->MacBase, GmacTSControl, GmacTSINT);
    else
    {
        TR("Error::: The TSADDREG bit is not getting cleared !!!!!!\n");
        return -ESYNOPGMACPHYERR;
    }
    return 0;
}

/**
  * Time Stamp Update Coarse
  * When reset the timestamp update is done using coarse method.
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_coarse_update(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacTSControl, GmacTSCFUPDT);
    return;
}
/**
  * Time Stamp Update Fine
  * When reset the timestamp update is done using Fine method.
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_fine_update(synopGMACdevice *gmacdev)
{
    synopGMACSetBits(gmacdev->MacBase, GmacTSControl, GmacTSCFUPDT);
    return;
}

/**
  * Load the Sub Second Increment value in to Sub Second increment register
  * @param[in] pointer to synopGMACdevice
  * \return returns void
  */
void synopGMAC_TS_subsecond_init(synopGMACdevice *gmacdev, u32 sub_sec_inc_value)
{
    synopGMACWriteReg(gmacdev->MacBase, GmacTSSubSecIncr, (sub_sec_inc_value & GmacSSINCMsk));
    return;
}
/**
  * Reads the time stamp contents in to the respective pointers
  * These registers are readonly.
  * This function returns the 48 bit time stamp assuming Version 2 timestamp with higher word is selected.
  * @param[in] pointer to synopGMACdevice
  * @param[in] pointer to hold 16 higher bit second register contents
  * @param[in] pointer to hold 32 bit second register contents
  * @param[in] pointer to hold 32 bit subnanosecond register contents
  * \return returns void
  * \note Please note that since the atomic access to the timestamp registers is not possible,
  *  the contents read may be different from the actual time stamp.
  */
void synopGMAC_TS_read_timestamp(synopGMACdevice *gmacdev, u16 *higher_sec_val, u32 *sec_val, u32   *sub_sec_val)
{
    * higher_sec_val = (u16)(synopGMACReadReg(gmacdev->MacBase, GmacTSHighWord) & GmacTSHighWordMask);
    * sec_val        = synopGMACReadReg(gmacdev->MacBase, GmacTSHigh);
    * sub_sec_val    = synopGMACReadReg(gmacdev->MacBase, GmacTSLow);
    return;
}
/**
  * Loads the time stamp higher sec value from the value supplied
  * @param[in] pointer to synopGMACdevice
  * @param[in] 16 higher bit second register contents passed as 32 bit value
  * \return returns void
  */
void synopGMAC_TS_load_timestamp_higher_val(synopGMACdevice *gmacdev, u32 higher_sec_val)
{
    synopGMACWriteReg(gmacdev->MacBase, GmacTSHighWord, (higher_sec_val & GmacTSHighWordMask));
    return;
}
/**
  * Reads the time stamp higher sec value to respective pointers
  * @param[in] pointer to synopGMACdevice
  * @param[in] pointer to hold 16 higher bit second register contents
  * \return returns void
  */
void synopGMAC_TS_read_timestamp_higher_val(synopGMACdevice *gmacdev, u16 *higher_sec_val)
{
    * higher_sec_val = (u16)(synopGMACReadReg(gmacdev->MacBase, GmacTSHighWord) & GmacTSHighWordMask);
    return;
}
/**
  * Load the Target time stamp registers
  * This function Loads the target time stamp registers with the values proviced
  * @param[in] pointer to synopGMACdevice
  * @param[in] target Timestamp High value
  * @param[in] target Timestamp Low  value
  * \return returns 0 for Success or else Failure
  */
void synopGMAC_TS_load_target_timestamp(synopGMACdevice *gmacdev, u32 sec_val, u32 sub_sec_val)
{
    synopGMACWriteReg(gmacdev->MacBase, GmacTSTargetTimeHigh, sec_val);
    synopGMACWriteReg(gmacdev->MacBase, GmacTSTargetTimeLow, sub_sec_val);
    return;
}
/**
  * Reads the Target time stamp registers
  * This function Loads the target time stamp registers with the values proviced
  * @param[in] pointer to synopGMACdevice
  * @param[in] pointer to hold target Timestamp High value
  * @param[in] pointer to hold target Timestamp Low  value
  * \return returns 0 for Success or else Failure
  */
void synopGMAC_TS_read_target_timestamp(synopGMACdevice *gmacdev, u32 *sec_val, u32 *sub_sec_val)
{
    * sec_val     = synopGMACReadReg(gmacdev->MacBase, GmacTSTargetTimeHigh);
    * sub_sec_val = synopGMACReadReg(gmacdev->MacBase, GmacTSTargetTimeLow);
    return;
}

void synopGMAC_src_addr_insert_enable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacSrcAddrInsRpl);
    synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacSrcAddrIns);

}
void synopGMAC_src_addr_insert_disable(synopGMACdevice *gmacdev)
{

    synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacSrcAddrInsRpl);

}
void synopGMAC_src_addr_replace_enable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacSrcAddrInsRpl);
    synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacSrcAddrRpl);


}
void synopGMAC_src_addr_replace_disable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacSrcAddrInsRpl);

}


void synopGMAC_svlan_insertion_enable(synopGMACdevice *gmacdev, u16 vlantag)
{

    synopGMACWriteReg(gmacdev->MacBase, GmacVLANIncRep, GmacVLP | GmacSVLAN | GmacVLANIns | vlantag);


}

void synopGMAC_cvlan_insertion_enable(synopGMACdevice *gmacdev, u16 vlantag)
{
    synopGMACWriteReg(gmacdev->MacBase, GmacVLANIncRep, GmacVLP | GmacCVLAN | GmacVLANIns | vlantag);


}

void synopGMAC_svlan_replace_enable(synopGMACdevice *gmacdev, u16 vlantag)
{
    synopGMACWriteReg(gmacdev->MacBase, GmacVLANIncRep, GmacVLP | GmacSVLAN | GmacVLANRep | vlantag);

}

void synopGMAC_cvlan_replace_enable(synopGMACdevice *gmacdev, u16 vlantag)
{
    synopGMACWriteReg(gmacdev->MacBase, GmacVLANIncRep, GmacVLP | GmacCVLAN | GmacVLANRep | vlantag);

}

void synopGMAC_vlan_deletion_enable(synopGMACdevice *gmacdev)
{
    synopGMACWriteReg(gmacdev->MacBase, GmacVLANIncRep, GmacVLP | GmacVLANDel);


}


void synopGMAC_vlan_no_act_enable(synopGMACdevice *gmacdev)
{
    synopGMACClearBits(gmacdev->MacBase, GmacVLANIncRep, 0xFFFFFFFF);
}


