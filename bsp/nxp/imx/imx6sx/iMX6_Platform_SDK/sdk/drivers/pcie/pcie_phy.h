/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
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


//! @addtogroup diag_pcie
//! @{

/*!
 * @file pcie_phy.h
 * @brief Public interface for PCIE phy.
 */

#ifndef _PCIE_PHY_H_
#define _PCIE_PHY_H_

// SSP ID_CODE
// -----------------
// RTL Version = 8.0          ==>  4'h7
// Product     = SSP          ==>  4'h2
// Foundry     = TSMC 40nm LP ==>  8'h11
// Test_chip   = PHY          ==>  1'h0
// Site ID     = Hillsboro    ==>  3'h6
// Synopsys                   ==> 12'h4CD
#define SSP_JTAG_DR_IDCODE_VAL_HI  0x7211
#define SSP_JTAG_DR_IDCODE_VAL_LO  0x64CD


////////////////////////////////////////////////////////////////////////////////
// API
///////////////////////////////////////////////////////////////////////////////

/*! 
 * @brief This function read the control register of the PCIE phy
 * @param    addr address of the register to be read	
 * @param    data 	register value be read
 *
 * @return   0 on success,
 *           -1 if failed
 */
int pcie_phy_cr_read(uint32_t addr, uint32_t * data);

/*! 
 * @brief This function write the control register of the PCIE phy
 * @param    addr address of the register to be written
 * @param    data 	register value to be written
 *
 * @return   0 on success,
 *           -1 if failed
 */
int pcie_phy_cr_write(uint32_t addr, uint32_t data);

#endif //_PCIE_PHY_REGS_H_
