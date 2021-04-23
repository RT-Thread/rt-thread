/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : SSI
// Version        : 1
// Bus type       : apb
// Description    : DW_apb_ssi has the following features:
//                  * APB interface – Allows for easy integration into a
//                  DesignWare Synthesizable Components for AMBA 2
//                  implementation.
//                  * APB3 and APB4 protocol support.
//                  * Scalable APB data bus width – Supports APB data bus widths
//                  of 8, 16, and 32 bits.
//                  * Serial-master or serial-slave operation – Enables serial
//                  communication with serial-master or serial-slave peripheral
//                  devices.
//                  * Programmable Dual/Quad/Octal SPI support in Master Mode.
//                  * Dual Data Rate (DDR) and Read Data Strobe (RDS) Support -
//                  Enables the DW_apb_ssi master to perform operations with the
//                  device in DDR and RDS modes when working in Dual/Quad/Octal
//                  mode of operation.
//                  * Data Mask Support - Enables the DW_apb_ssi to selectively
//                  update the bytes in the device. This feature is applicable
//                  only in enhanced SPI modes.
//                  * eXecute-In-Place (XIP) support - Enables the DW_apb_ssi
//                  master to behave as a memory mapped I/O and fetches the data
//                  from the device based on the APB read request. This feature
//                  is applicable only in enhanced SPI modes.
//                  * DMA Controller Interface – Enables the DW_apb_ssi to
//                  interface to a DMA controller over the bus using a
//                  handshaking interface for transfer requests.
//                  * Independent masking of interrupts – Master collision,
//                  transmit FIFO overflow, transmit FIFO empty, receive FIFO
//                  full, receive FIFO underflow, and receive FIFO overflow
//                  interrupts can all be masked independently.
//                  * Multi-master contention detection – Informs the processor
//                  of multiple serial-master accesses on the serial bus.
//                  * Bypass of meta-stability flip-flops for synchronous clocks
//                  – When the APB clock (pclk) and the DW_apb_ssi serial clock
//                  (ssi_clk) are synchronous, meta-stable flip-flops are not
//                  used when transferring control signals across these clock
//                  domains.
//                  * Programmable delay on the sample time of the received
//                  serial data bit (rxd); enables programmable control of
//                  routing delays resulting in higher serial data-bit rates.
//                  * Programmable features:
//                  - Serial interface operation – Choice of Motorola SPI, Texas
//                  Instruments Synchronous Serial Protocol or National
//                  Semiconductor Microwire.
//                  - Clock bit-rate – Dynamic control of the serial bit rate of
//                  the data transfer; used in only serial-master mode of
//                  operation.
//                  - Data Item size (4 to 32 bits) – Item size of each data
//                  transfer under the control of the programmer.
//                  * Configured features:
//                  - FIFO depth – 16 words deep. The FIFO width is fixed at 32
//                  bits.
//                  - 1 slave select output.
//                  - Hardware slave-select – Dedicated hardware slave-select
//                  line.
//                  - Combined interrupt line - one combined interrupt line from
//                  the DW_apb_ssi to the interrupt controller.
//                  - Interrupt polarity – active high interrupt lines.
//                  - Serial clock polarity – low serial-clock polarity directly
//                  after reset.
//                  - Serial clock phase – capture on first edge of serial-clock
//                  directly after reset.
// =============================================================================
#ifndef HARDWARE_REGS_SSI_DEFINED
#define HARDWARE_REGS_SSI_DEFINED
// =============================================================================
// Register    : SSI_CTRLR0
// Description : Control register 0
#define SSI_CTRLR0_OFFSET 0x00000000
#define SSI_CTRLR0_BITS   0x017fffff
#define SSI_CTRLR0_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SSI_CTRLR0_SSTE
// Description : Slave select toggle enable
#define SSI_CTRLR0_SSTE_RESET  0x0
#define SSI_CTRLR0_SSTE_BITS   0x01000000
#define SSI_CTRLR0_SSTE_MSB    24
#define SSI_CTRLR0_SSTE_LSB    24
#define SSI_CTRLR0_SSTE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_CTRLR0_SPI_FRF
// Description : SPI frame format
//               0x0 -> Standard 1-bit SPI frame format; 1 bit per SCK,
//               full-duplex
//               0x1 -> Dual-SPI frame format; two bits per SCK, half-duplex
//               0x2 -> Quad-SPI frame format; four bits per SCK, half-duplex
#define SSI_CTRLR0_SPI_FRF_RESET      0x0
#define SSI_CTRLR0_SPI_FRF_BITS       0x00600000
#define SSI_CTRLR0_SPI_FRF_MSB        22
#define SSI_CTRLR0_SPI_FRF_LSB        21
#define SSI_CTRLR0_SPI_FRF_ACCESS     "RW"
#define SSI_CTRLR0_SPI_FRF_VALUE_STD  0x0
#define SSI_CTRLR0_SPI_FRF_VALUE_DUAL 0x1
#define SSI_CTRLR0_SPI_FRF_VALUE_QUAD 0x2
// -----------------------------------------------------------------------------
// Field       : SSI_CTRLR0_DFS_32
// Description : Data frame size in 32b transfer mode
//               Value of n -> n+1 clocks per frame.
#define SSI_CTRLR0_DFS_32_RESET  0x00
#define SSI_CTRLR0_DFS_32_BITS   0x001f0000
#define SSI_CTRLR0_DFS_32_MSB    20
#define SSI_CTRLR0_DFS_32_LSB    16
#define SSI_CTRLR0_DFS_32_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_CTRLR0_CFS
// Description : Control frame size
//               Value of n -> n+1 clocks per frame.
#define SSI_CTRLR0_CFS_RESET  0x0
#define SSI_CTRLR0_CFS_BITS   0x0000f000
#define SSI_CTRLR0_CFS_MSB    15
#define SSI_CTRLR0_CFS_LSB    12
#define SSI_CTRLR0_CFS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_CTRLR0_SRL
// Description : Shift register loop (test mode)
#define SSI_CTRLR0_SRL_RESET  0x0
#define SSI_CTRLR0_SRL_BITS   0x00000800
#define SSI_CTRLR0_SRL_MSB    11
#define SSI_CTRLR0_SRL_LSB    11
#define SSI_CTRLR0_SRL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_CTRLR0_SLV_OE
// Description : Slave output enable
#define SSI_CTRLR0_SLV_OE_RESET  0x0
#define SSI_CTRLR0_SLV_OE_BITS   0x00000400
#define SSI_CTRLR0_SLV_OE_MSB    10
#define SSI_CTRLR0_SLV_OE_LSB    10
#define SSI_CTRLR0_SLV_OE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_CTRLR0_TMOD
// Description : Transfer mode
//               0x0 -> Both transmit and receive
//               0x1 -> Transmit only (not for FRF == 0, standard SPI mode)
//               0x2 -> Receive only (not for FRF == 0, standard SPI mode)
//               0x3 -> EEPROM read mode (TX then RX; RX starts after control
//               data TX'd)
#define SSI_CTRLR0_TMOD_RESET             0x0
#define SSI_CTRLR0_TMOD_BITS              0x00000300
#define SSI_CTRLR0_TMOD_MSB               9
#define SSI_CTRLR0_TMOD_LSB               8
#define SSI_CTRLR0_TMOD_ACCESS            "RW"
#define SSI_CTRLR0_TMOD_VALUE_TX_AND_RX   0x0
#define SSI_CTRLR0_TMOD_VALUE_TX_ONLY     0x1
#define SSI_CTRLR0_TMOD_VALUE_RX_ONLY     0x2
#define SSI_CTRLR0_TMOD_VALUE_EEPROM_READ 0x3
// -----------------------------------------------------------------------------
// Field       : SSI_CTRLR0_SCPOL
// Description : Serial clock polarity
#define SSI_CTRLR0_SCPOL_RESET  0x0
#define SSI_CTRLR0_SCPOL_BITS   0x00000080
#define SSI_CTRLR0_SCPOL_MSB    7
#define SSI_CTRLR0_SCPOL_LSB    7
#define SSI_CTRLR0_SCPOL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_CTRLR0_SCPH
// Description : Serial clock phase
#define SSI_CTRLR0_SCPH_RESET  0x0
#define SSI_CTRLR0_SCPH_BITS   0x00000040
#define SSI_CTRLR0_SCPH_MSB    6
#define SSI_CTRLR0_SCPH_LSB    6
#define SSI_CTRLR0_SCPH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_CTRLR0_FRF
// Description : Frame format
#define SSI_CTRLR0_FRF_RESET  0x0
#define SSI_CTRLR0_FRF_BITS   0x00000030
#define SSI_CTRLR0_FRF_MSB    5
#define SSI_CTRLR0_FRF_LSB    4
#define SSI_CTRLR0_FRF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_CTRLR0_DFS
// Description : Data frame size
#define SSI_CTRLR0_DFS_RESET  0x0
#define SSI_CTRLR0_DFS_BITS   0x0000000f
#define SSI_CTRLR0_DFS_MSB    3
#define SSI_CTRLR0_DFS_LSB    0
#define SSI_CTRLR0_DFS_ACCESS "RW"
// =============================================================================
// Register    : SSI_CTRLR1
// Description : Master Control register 1
#define SSI_CTRLR1_OFFSET 0x00000004
#define SSI_CTRLR1_BITS   0x0000ffff
#define SSI_CTRLR1_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SSI_CTRLR1_NDF
// Description : Number of data frames
#define SSI_CTRLR1_NDF_RESET  0x0000
#define SSI_CTRLR1_NDF_BITS   0x0000ffff
#define SSI_CTRLR1_NDF_MSB    15
#define SSI_CTRLR1_NDF_LSB    0
#define SSI_CTRLR1_NDF_ACCESS "RW"
// =============================================================================
// Register    : SSI_SSIENR
// Description : SSI Enable
#define SSI_SSIENR_OFFSET 0x00000008
#define SSI_SSIENR_BITS   0x00000001
#define SSI_SSIENR_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SSI_SSIENR_SSI_EN
// Description : SSI enable
#define SSI_SSIENR_SSI_EN_RESET  0x0
#define SSI_SSIENR_SSI_EN_BITS   0x00000001
#define SSI_SSIENR_SSI_EN_MSB    0
#define SSI_SSIENR_SSI_EN_LSB    0
#define SSI_SSIENR_SSI_EN_ACCESS "RW"
// =============================================================================
// Register    : SSI_MWCR
// Description : Microwire Control
#define SSI_MWCR_OFFSET 0x0000000c
#define SSI_MWCR_BITS   0x00000007
#define SSI_MWCR_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SSI_MWCR_MHS
// Description : Microwire handshaking
#define SSI_MWCR_MHS_RESET  0x0
#define SSI_MWCR_MHS_BITS   0x00000004
#define SSI_MWCR_MHS_MSB    2
#define SSI_MWCR_MHS_LSB    2
#define SSI_MWCR_MHS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_MWCR_MDD
// Description : Microwire control
#define SSI_MWCR_MDD_RESET  0x0
#define SSI_MWCR_MDD_BITS   0x00000002
#define SSI_MWCR_MDD_MSB    1
#define SSI_MWCR_MDD_LSB    1
#define SSI_MWCR_MDD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_MWCR_MWMOD
// Description : Microwire transfer mode
#define SSI_MWCR_MWMOD_RESET  0x0
#define SSI_MWCR_MWMOD_BITS   0x00000001
#define SSI_MWCR_MWMOD_MSB    0
#define SSI_MWCR_MWMOD_LSB    0
#define SSI_MWCR_MWMOD_ACCESS "RW"
// =============================================================================
// Register    : SSI_SER
// Description : Slave enable
//               For each bit:
//               0 -> slave not selected
//               1 -> slave selected
#define SSI_SER_OFFSET 0x00000010
#define SSI_SER_BITS   0x00000001
#define SSI_SER_RESET  0x00000000
#define SSI_SER_MSB    0
#define SSI_SER_LSB    0
#define SSI_SER_ACCESS "RW"
// =============================================================================
// Register    : SSI_BAUDR
// Description : Baud rate
#define SSI_BAUDR_OFFSET 0x00000014
#define SSI_BAUDR_BITS   0x0000ffff
#define SSI_BAUDR_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SSI_BAUDR_SCKDV
// Description : SSI clock divider
#define SSI_BAUDR_SCKDV_RESET  0x0000
#define SSI_BAUDR_SCKDV_BITS   0x0000ffff
#define SSI_BAUDR_SCKDV_MSB    15
#define SSI_BAUDR_SCKDV_LSB    0
#define SSI_BAUDR_SCKDV_ACCESS "RW"
// =============================================================================
// Register    : SSI_TXFTLR
// Description : TX FIFO threshold level
#define SSI_TXFTLR_OFFSET 0x00000018
#define SSI_TXFTLR_BITS   0x000000ff
#define SSI_TXFTLR_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SSI_TXFTLR_TFT
// Description : Transmit FIFO threshold
#define SSI_TXFTLR_TFT_RESET  0x00
#define SSI_TXFTLR_TFT_BITS   0x000000ff
#define SSI_TXFTLR_TFT_MSB    7
#define SSI_TXFTLR_TFT_LSB    0
#define SSI_TXFTLR_TFT_ACCESS "RW"
// =============================================================================
// Register    : SSI_RXFTLR
// Description : RX FIFO threshold level
#define SSI_RXFTLR_OFFSET 0x0000001c
#define SSI_RXFTLR_BITS   0x000000ff
#define SSI_RXFTLR_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SSI_RXFTLR_RFT
// Description : Receive FIFO threshold
#define SSI_RXFTLR_RFT_RESET  0x00
#define SSI_RXFTLR_RFT_BITS   0x000000ff
#define SSI_RXFTLR_RFT_MSB    7
#define SSI_RXFTLR_RFT_LSB    0
#define SSI_RXFTLR_RFT_ACCESS "RW"
// =============================================================================
// Register    : SSI_TXFLR
// Description : TX FIFO level
#define SSI_TXFLR_OFFSET 0x00000020
#define SSI_TXFLR_BITS   0x000000ff
#define SSI_TXFLR_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SSI_TXFLR_TFTFL
// Description : Transmit FIFO level
#define SSI_TXFLR_TFTFL_RESET  0x00
#define SSI_TXFLR_TFTFL_BITS   0x000000ff
#define SSI_TXFLR_TFTFL_MSB    7
#define SSI_TXFLR_TFTFL_LSB    0
#define SSI_TXFLR_TFTFL_ACCESS "RO"
// =============================================================================
// Register    : SSI_RXFLR
// Description : RX FIFO level
#define SSI_RXFLR_OFFSET 0x00000024
#define SSI_RXFLR_BITS   0x000000ff
#define SSI_RXFLR_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SSI_RXFLR_RXTFL
// Description : Receive FIFO level
#define SSI_RXFLR_RXTFL_RESET  0x00
#define SSI_RXFLR_RXTFL_BITS   0x000000ff
#define SSI_RXFLR_RXTFL_MSB    7
#define SSI_RXFLR_RXTFL_LSB    0
#define SSI_RXFLR_RXTFL_ACCESS "RO"
// =============================================================================
// Register    : SSI_SR
// Description : Status register
#define SSI_SR_OFFSET 0x00000028
#define SSI_SR_BITS   0x0000007f
#define SSI_SR_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SSI_SR_DCOL
// Description : Data collision error
#define SSI_SR_DCOL_RESET  0x0
#define SSI_SR_DCOL_BITS   0x00000040
#define SSI_SR_DCOL_MSB    6
#define SSI_SR_DCOL_LSB    6
#define SSI_SR_DCOL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SSI_SR_TXE
// Description : Transmission error
#define SSI_SR_TXE_RESET  0x0
#define SSI_SR_TXE_BITS   0x00000020
#define SSI_SR_TXE_MSB    5
#define SSI_SR_TXE_LSB    5
#define SSI_SR_TXE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SSI_SR_RFF
// Description : Receive FIFO full
#define SSI_SR_RFF_RESET  0x0
#define SSI_SR_RFF_BITS   0x00000010
#define SSI_SR_RFF_MSB    4
#define SSI_SR_RFF_LSB    4
#define SSI_SR_RFF_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SSI_SR_RFNE
// Description : Receive FIFO not empty
#define SSI_SR_RFNE_RESET  0x0
#define SSI_SR_RFNE_BITS   0x00000008
#define SSI_SR_RFNE_MSB    3
#define SSI_SR_RFNE_LSB    3
#define SSI_SR_RFNE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SSI_SR_TFE
// Description : Transmit FIFO empty
#define SSI_SR_TFE_RESET  0x0
#define SSI_SR_TFE_BITS   0x00000004
#define SSI_SR_TFE_MSB    2
#define SSI_SR_TFE_LSB    2
#define SSI_SR_TFE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SSI_SR_TFNF
// Description : Transmit FIFO not full
#define SSI_SR_TFNF_RESET  0x0
#define SSI_SR_TFNF_BITS   0x00000002
#define SSI_SR_TFNF_MSB    1
#define SSI_SR_TFNF_LSB    1
#define SSI_SR_TFNF_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SSI_SR_BUSY
// Description : SSI busy flag
#define SSI_SR_BUSY_RESET  0x0
#define SSI_SR_BUSY_BITS   0x00000001
#define SSI_SR_BUSY_MSB    0
#define SSI_SR_BUSY_LSB    0
#define SSI_SR_BUSY_ACCESS "RO"
// =============================================================================
// Register    : SSI_IMR
// Description : Interrupt mask
#define SSI_IMR_OFFSET 0x0000002c
#define SSI_IMR_BITS   0x0000003f
#define SSI_IMR_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SSI_IMR_MSTIM
// Description : Multi-master contention interrupt mask
#define SSI_IMR_MSTIM_RESET  0x0
#define SSI_IMR_MSTIM_BITS   0x00000020
#define SSI_IMR_MSTIM_MSB    5
#define SSI_IMR_MSTIM_LSB    5
#define SSI_IMR_MSTIM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_IMR_RXFIM
// Description : Receive FIFO full interrupt mask
#define SSI_IMR_RXFIM_RESET  0x0
#define SSI_IMR_RXFIM_BITS   0x00000010
#define SSI_IMR_RXFIM_MSB    4
#define SSI_IMR_RXFIM_LSB    4
#define SSI_IMR_RXFIM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_IMR_RXOIM
// Description : Receive FIFO overflow interrupt mask
#define SSI_IMR_RXOIM_RESET  0x0
#define SSI_IMR_RXOIM_BITS   0x00000008
#define SSI_IMR_RXOIM_MSB    3
#define SSI_IMR_RXOIM_LSB    3
#define SSI_IMR_RXOIM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_IMR_RXUIM
// Description : Receive FIFO underflow interrupt mask
#define SSI_IMR_RXUIM_RESET  0x0
#define SSI_IMR_RXUIM_BITS   0x00000004
#define SSI_IMR_RXUIM_MSB    2
#define SSI_IMR_RXUIM_LSB    2
#define SSI_IMR_RXUIM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_IMR_TXOIM
// Description : Transmit FIFO overflow interrupt mask
#define SSI_IMR_TXOIM_RESET  0x0
#define SSI_IMR_TXOIM_BITS   0x00000002
#define SSI_IMR_TXOIM_MSB    1
#define SSI_IMR_TXOIM_LSB    1
#define SSI_IMR_TXOIM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_IMR_TXEIM
// Description : Transmit FIFO empty interrupt mask
#define SSI_IMR_TXEIM_RESET  0x0
#define SSI_IMR_TXEIM_BITS   0x00000001
#define SSI_IMR_TXEIM_MSB    0
#define SSI_IMR_TXEIM_LSB    0
#define SSI_IMR_TXEIM_ACCESS "RW"
// =============================================================================
// Register    : SSI_ISR
// Description : Interrupt status
#define SSI_ISR_OFFSET 0x00000030
#define SSI_ISR_BITS   0x0000003f
#define SSI_ISR_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SSI_ISR_MSTIS
// Description : Multi-master contention interrupt status
#define SSI_ISR_MSTIS_RESET  0x0
#define SSI_ISR_MSTIS_BITS   0x00000020
#define SSI_ISR_MSTIS_MSB    5
#define SSI_ISR_MSTIS_LSB    5
#define SSI_ISR_MSTIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SSI_ISR_RXFIS
// Description : Receive FIFO full interrupt status
#define SSI_ISR_RXFIS_RESET  0x0
#define SSI_ISR_RXFIS_BITS   0x00000010
#define SSI_ISR_RXFIS_MSB    4
#define SSI_ISR_RXFIS_LSB    4
#define SSI_ISR_RXFIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SSI_ISR_RXOIS
// Description : Receive FIFO overflow interrupt status
#define SSI_ISR_RXOIS_RESET  0x0
#define SSI_ISR_RXOIS_BITS   0x00000008
#define SSI_ISR_RXOIS_MSB    3
#define SSI_ISR_RXOIS_LSB    3
#define SSI_ISR_RXOIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SSI_ISR_RXUIS
// Description : Receive FIFO underflow interrupt status
#define SSI_ISR_RXUIS_RESET  0x0
#define SSI_ISR_RXUIS_BITS   0x00000004
#define SSI_ISR_RXUIS_MSB    2
#define SSI_ISR_RXUIS_LSB    2
#define SSI_ISR_RXUIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SSI_ISR_TXOIS
// Description : Transmit FIFO overflow interrupt status
#define SSI_ISR_TXOIS_RESET  0x0
#define SSI_ISR_TXOIS_BITS   0x00000002
#define SSI_ISR_TXOIS_MSB    1
#define SSI_ISR_TXOIS_LSB    1
#define SSI_ISR_TXOIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SSI_ISR_TXEIS
// Description : Transmit FIFO empty interrupt status
#define SSI_ISR_TXEIS_RESET  0x0
#define SSI_ISR_TXEIS_BITS   0x00000001
#define SSI_ISR_TXEIS_MSB    0
#define SSI_ISR_TXEIS_LSB    0
#define SSI_ISR_TXEIS_ACCESS "RO"
// =============================================================================
// Register    : SSI_RISR
// Description : Raw interrupt status
#define SSI_RISR_OFFSET 0x00000034
#define SSI_RISR_BITS   0x0000003f
#define SSI_RISR_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SSI_RISR_MSTIR
// Description : Multi-master contention raw interrupt status
#define SSI_RISR_MSTIR_RESET  0x0
#define SSI_RISR_MSTIR_BITS   0x00000020
#define SSI_RISR_MSTIR_MSB    5
#define SSI_RISR_MSTIR_LSB    5
#define SSI_RISR_MSTIR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SSI_RISR_RXFIR
// Description : Receive FIFO full raw interrupt status
#define SSI_RISR_RXFIR_RESET  0x0
#define SSI_RISR_RXFIR_BITS   0x00000010
#define SSI_RISR_RXFIR_MSB    4
#define SSI_RISR_RXFIR_LSB    4
#define SSI_RISR_RXFIR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SSI_RISR_RXOIR
// Description : Receive FIFO overflow raw interrupt status
#define SSI_RISR_RXOIR_RESET  0x0
#define SSI_RISR_RXOIR_BITS   0x00000008
#define SSI_RISR_RXOIR_MSB    3
#define SSI_RISR_RXOIR_LSB    3
#define SSI_RISR_RXOIR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SSI_RISR_RXUIR
// Description : Receive FIFO underflow raw interrupt status
#define SSI_RISR_RXUIR_RESET  0x0
#define SSI_RISR_RXUIR_BITS   0x00000004
#define SSI_RISR_RXUIR_MSB    2
#define SSI_RISR_RXUIR_LSB    2
#define SSI_RISR_RXUIR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SSI_RISR_TXOIR
// Description : Transmit FIFO overflow raw interrupt status
#define SSI_RISR_TXOIR_RESET  0x0
#define SSI_RISR_TXOIR_BITS   0x00000002
#define SSI_RISR_TXOIR_MSB    1
#define SSI_RISR_TXOIR_LSB    1
#define SSI_RISR_TXOIR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SSI_RISR_TXEIR
// Description : Transmit FIFO empty raw interrupt status
#define SSI_RISR_TXEIR_RESET  0x0
#define SSI_RISR_TXEIR_BITS   0x00000001
#define SSI_RISR_TXEIR_MSB    0
#define SSI_RISR_TXEIR_LSB    0
#define SSI_RISR_TXEIR_ACCESS "RO"
// =============================================================================
// Register    : SSI_TXOICR
// Description : TX FIFO overflow interrupt clear
//               Clear-on-read transmit FIFO overflow interrupt
#define SSI_TXOICR_OFFSET 0x00000038
#define SSI_TXOICR_BITS   0x00000001
#define SSI_TXOICR_RESET  0x00000000
#define SSI_TXOICR_MSB    0
#define SSI_TXOICR_LSB    0
#define SSI_TXOICR_ACCESS "RO"
// =============================================================================
// Register    : SSI_RXOICR
// Description : RX FIFO overflow interrupt clear
//               Clear-on-read receive FIFO overflow interrupt
#define SSI_RXOICR_OFFSET 0x0000003c
#define SSI_RXOICR_BITS   0x00000001
#define SSI_RXOICR_RESET  0x00000000
#define SSI_RXOICR_MSB    0
#define SSI_RXOICR_LSB    0
#define SSI_RXOICR_ACCESS "RO"
// =============================================================================
// Register    : SSI_RXUICR
// Description : RX FIFO underflow interrupt clear
//               Clear-on-read receive FIFO underflow interrupt
#define SSI_RXUICR_OFFSET 0x00000040
#define SSI_RXUICR_BITS   0x00000001
#define SSI_RXUICR_RESET  0x00000000
#define SSI_RXUICR_MSB    0
#define SSI_RXUICR_LSB    0
#define SSI_RXUICR_ACCESS "RO"
// =============================================================================
// Register    : SSI_MSTICR
// Description : Multi-master interrupt clear
//               Clear-on-read multi-master contention interrupt
#define SSI_MSTICR_OFFSET 0x00000044
#define SSI_MSTICR_BITS   0x00000001
#define SSI_MSTICR_RESET  0x00000000
#define SSI_MSTICR_MSB    0
#define SSI_MSTICR_LSB    0
#define SSI_MSTICR_ACCESS "RO"
// =============================================================================
// Register    : SSI_ICR
// Description : Interrupt clear
//               Clear-on-read all active interrupts
#define SSI_ICR_OFFSET 0x00000048
#define SSI_ICR_BITS   0x00000001
#define SSI_ICR_RESET  0x00000000
#define SSI_ICR_MSB    0
#define SSI_ICR_LSB    0
#define SSI_ICR_ACCESS "RO"
// =============================================================================
// Register    : SSI_DMACR
// Description : DMA control
#define SSI_DMACR_OFFSET 0x0000004c
#define SSI_DMACR_BITS   0x00000003
#define SSI_DMACR_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SSI_DMACR_TDMAE
// Description : Transmit DMA enable
#define SSI_DMACR_TDMAE_RESET  0x0
#define SSI_DMACR_TDMAE_BITS   0x00000002
#define SSI_DMACR_TDMAE_MSB    1
#define SSI_DMACR_TDMAE_LSB    1
#define SSI_DMACR_TDMAE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_DMACR_RDMAE
// Description : Receive DMA enable
#define SSI_DMACR_RDMAE_RESET  0x0
#define SSI_DMACR_RDMAE_BITS   0x00000001
#define SSI_DMACR_RDMAE_MSB    0
#define SSI_DMACR_RDMAE_LSB    0
#define SSI_DMACR_RDMAE_ACCESS "RW"
// =============================================================================
// Register    : SSI_DMATDLR
// Description : DMA TX data level
#define SSI_DMATDLR_OFFSET 0x00000050
#define SSI_DMATDLR_BITS   0x000000ff
#define SSI_DMATDLR_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SSI_DMATDLR_DMATDL
// Description : Transmit data watermark level
#define SSI_DMATDLR_DMATDL_RESET  0x00
#define SSI_DMATDLR_DMATDL_BITS   0x000000ff
#define SSI_DMATDLR_DMATDL_MSB    7
#define SSI_DMATDLR_DMATDL_LSB    0
#define SSI_DMATDLR_DMATDL_ACCESS "RW"
// =============================================================================
// Register    : SSI_DMARDLR
// Description : DMA RX data level
#define SSI_DMARDLR_OFFSET 0x00000054
#define SSI_DMARDLR_BITS   0x000000ff
#define SSI_DMARDLR_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SSI_DMARDLR_DMARDL
// Description : Receive data watermark level (DMARDLR+1)
#define SSI_DMARDLR_DMARDL_RESET  0x00
#define SSI_DMARDLR_DMARDL_BITS   0x000000ff
#define SSI_DMARDLR_DMARDL_MSB    7
#define SSI_DMARDLR_DMARDL_LSB    0
#define SSI_DMARDLR_DMARDL_ACCESS "RW"
// =============================================================================
// Register    : SSI_IDR
// Description : Identification register
#define SSI_IDR_OFFSET 0x00000058
#define SSI_IDR_BITS   0xffffffff
#define SSI_IDR_RESET  0x51535049
// -----------------------------------------------------------------------------
// Field       : SSI_IDR_IDCODE
// Description : Peripheral dentification code
#define SSI_IDR_IDCODE_RESET  0x51535049
#define SSI_IDR_IDCODE_BITS   0xffffffff
#define SSI_IDR_IDCODE_MSB    31
#define SSI_IDR_IDCODE_LSB    0
#define SSI_IDR_IDCODE_ACCESS "RO"
// =============================================================================
// Register    : SSI_SSI_VERSION_ID
// Description : Version ID
#define SSI_SSI_VERSION_ID_OFFSET 0x0000005c
#define SSI_SSI_VERSION_ID_BITS   0xffffffff
#define SSI_SSI_VERSION_ID_RESET  0x3430312a
// -----------------------------------------------------------------------------
// Field       : SSI_SSI_VERSION_ID_SSI_COMP_VERSION
// Description : SNPS component version (format X.YY)
#define SSI_SSI_VERSION_ID_SSI_COMP_VERSION_RESET  0x3430312a
#define SSI_SSI_VERSION_ID_SSI_COMP_VERSION_BITS   0xffffffff
#define SSI_SSI_VERSION_ID_SSI_COMP_VERSION_MSB    31
#define SSI_SSI_VERSION_ID_SSI_COMP_VERSION_LSB    0
#define SSI_SSI_VERSION_ID_SSI_COMP_VERSION_ACCESS "RO"
// =============================================================================
// Register    : SSI_DR0
// Description : Data Register 0 (of 36)
#define SSI_DR0_OFFSET 0x00000060
#define SSI_DR0_BITS   0xffffffff
#define SSI_DR0_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SSI_DR0_DR
// Description : First data register of 36
#define SSI_DR0_DR_RESET  0x00000000
#define SSI_DR0_DR_BITS   0xffffffff
#define SSI_DR0_DR_MSB    31
#define SSI_DR0_DR_LSB    0
#define SSI_DR0_DR_ACCESS "RW"
// =============================================================================
// Register    : SSI_RX_SAMPLE_DLY
// Description : RX sample delay
#define SSI_RX_SAMPLE_DLY_OFFSET 0x000000f0
#define SSI_RX_SAMPLE_DLY_BITS   0x000000ff
#define SSI_RX_SAMPLE_DLY_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SSI_RX_SAMPLE_DLY_RSD
// Description : RXD sample delay (in SCLK cycles)
#define SSI_RX_SAMPLE_DLY_RSD_RESET  0x00
#define SSI_RX_SAMPLE_DLY_RSD_BITS   0x000000ff
#define SSI_RX_SAMPLE_DLY_RSD_MSB    7
#define SSI_RX_SAMPLE_DLY_RSD_LSB    0
#define SSI_RX_SAMPLE_DLY_RSD_ACCESS "RW"
// =============================================================================
// Register    : SSI_SPI_CTRLR0
// Description : SPI control
#define SSI_SPI_CTRLR0_OFFSET 0x000000f4
#define SSI_SPI_CTRLR0_BITS   0xff07fb3f
#define SSI_SPI_CTRLR0_RESET  0x03000000
// -----------------------------------------------------------------------------
// Field       : SSI_SPI_CTRLR0_XIP_CMD
// Description : SPI Command to send in XIP mode (INST_L = 8-bit) or to append
//               to Address (INST_L = 0-bit)
#define SSI_SPI_CTRLR0_XIP_CMD_RESET  0x03
#define SSI_SPI_CTRLR0_XIP_CMD_BITS   0xff000000
#define SSI_SPI_CTRLR0_XIP_CMD_MSB    31
#define SSI_SPI_CTRLR0_XIP_CMD_LSB    24
#define SSI_SPI_CTRLR0_XIP_CMD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_SPI_CTRLR0_SPI_RXDS_EN
// Description : Read data strobe enable
#define SSI_SPI_CTRLR0_SPI_RXDS_EN_RESET  0x0
#define SSI_SPI_CTRLR0_SPI_RXDS_EN_BITS   0x00040000
#define SSI_SPI_CTRLR0_SPI_RXDS_EN_MSB    18
#define SSI_SPI_CTRLR0_SPI_RXDS_EN_LSB    18
#define SSI_SPI_CTRLR0_SPI_RXDS_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_SPI_CTRLR0_INST_DDR_EN
// Description : Instruction DDR transfer enable
#define SSI_SPI_CTRLR0_INST_DDR_EN_RESET  0x0
#define SSI_SPI_CTRLR0_INST_DDR_EN_BITS   0x00020000
#define SSI_SPI_CTRLR0_INST_DDR_EN_MSB    17
#define SSI_SPI_CTRLR0_INST_DDR_EN_LSB    17
#define SSI_SPI_CTRLR0_INST_DDR_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_SPI_CTRLR0_SPI_DDR_EN
// Description : SPI DDR transfer enable
#define SSI_SPI_CTRLR0_SPI_DDR_EN_RESET  0x0
#define SSI_SPI_CTRLR0_SPI_DDR_EN_BITS   0x00010000
#define SSI_SPI_CTRLR0_SPI_DDR_EN_MSB    16
#define SSI_SPI_CTRLR0_SPI_DDR_EN_LSB    16
#define SSI_SPI_CTRLR0_SPI_DDR_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_SPI_CTRLR0_WAIT_CYCLES
// Description : Wait cycles between control frame transmit and data reception
//               (in SCLK cycles)
#define SSI_SPI_CTRLR0_WAIT_CYCLES_RESET  0x00
#define SSI_SPI_CTRLR0_WAIT_CYCLES_BITS   0x0000f800
#define SSI_SPI_CTRLR0_WAIT_CYCLES_MSB    15
#define SSI_SPI_CTRLR0_WAIT_CYCLES_LSB    11
#define SSI_SPI_CTRLR0_WAIT_CYCLES_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_SPI_CTRLR0_INST_L
// Description : Instruction length (0/4/8/16b)
//               0x0 -> No instruction
//               0x1 -> 4-bit instruction
//               0x2 -> 8-bit instruction
//               0x3 -> 16-bit instruction
#define SSI_SPI_CTRLR0_INST_L_RESET      0x0
#define SSI_SPI_CTRLR0_INST_L_BITS       0x00000300
#define SSI_SPI_CTRLR0_INST_L_MSB        9
#define SSI_SPI_CTRLR0_INST_L_LSB        8
#define SSI_SPI_CTRLR0_INST_L_ACCESS     "RW"
#define SSI_SPI_CTRLR0_INST_L_VALUE_NONE 0x0
#define SSI_SPI_CTRLR0_INST_L_VALUE_4B   0x1
#define SSI_SPI_CTRLR0_INST_L_VALUE_8B   0x2
#define SSI_SPI_CTRLR0_INST_L_VALUE_16B  0x3
// -----------------------------------------------------------------------------
// Field       : SSI_SPI_CTRLR0_ADDR_L
// Description : Address length (0b-60b in 4b increments)
#define SSI_SPI_CTRLR0_ADDR_L_RESET  0x0
#define SSI_SPI_CTRLR0_ADDR_L_BITS   0x0000003c
#define SSI_SPI_CTRLR0_ADDR_L_MSB    5
#define SSI_SPI_CTRLR0_ADDR_L_LSB    2
#define SSI_SPI_CTRLR0_ADDR_L_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SSI_SPI_CTRLR0_TRANS_TYPE
// Description : Address and instruction transfer format
//               0x0 -> Command and address both in standard SPI frame format
//               0x1 -> Command in standard SPI format, address in format
//               specified by FRF
//               0x2 -> Command and address both in format specified by FRF
//               (e.g. Dual-SPI)
#define SSI_SPI_CTRLR0_TRANS_TYPE_RESET      0x0
#define SSI_SPI_CTRLR0_TRANS_TYPE_BITS       0x00000003
#define SSI_SPI_CTRLR0_TRANS_TYPE_MSB        1
#define SSI_SPI_CTRLR0_TRANS_TYPE_LSB        0
#define SSI_SPI_CTRLR0_TRANS_TYPE_ACCESS     "RW"
#define SSI_SPI_CTRLR0_TRANS_TYPE_VALUE_1C1A 0x0
#define SSI_SPI_CTRLR0_TRANS_TYPE_VALUE_1C2A 0x1
#define SSI_SPI_CTRLR0_TRANS_TYPE_VALUE_2C2A 0x2
// =============================================================================
// Register    : SSI_TXD_DRIVE_EDGE
// Description : TX drive edge
#define SSI_TXD_DRIVE_EDGE_OFFSET 0x000000f8
#define SSI_TXD_DRIVE_EDGE_BITS   0x000000ff
#define SSI_TXD_DRIVE_EDGE_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SSI_TXD_DRIVE_EDGE_TDE
// Description : TXD drive edge
#define SSI_TXD_DRIVE_EDGE_TDE_RESET  0x00
#define SSI_TXD_DRIVE_EDGE_TDE_BITS   0x000000ff
#define SSI_TXD_DRIVE_EDGE_TDE_MSB    7
#define SSI_TXD_DRIVE_EDGE_TDE_LSB    0
#define SSI_TXD_DRIVE_EDGE_TDE_ACCESS "RW"
// =============================================================================
#endif // HARDWARE_REGS_SSI_DEFINED
