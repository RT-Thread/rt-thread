/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_SPI_H
#define _HARDWARE_SPI_H

#include "pico.h"
#include "pico/time.h"
#include "hardware/structs/spi.h"

// PICO_CONFIG: PARAM_ASSERTIONS_ENABLED_SPI, Enable/disable assertions in the SPI module, type=bool, default=0, group=hardware_spi
#ifndef PARAM_ASSERTIONS_ENABLED_SPI
#define PARAM_ASSERTIONS_ENABLED_SPI 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** \file hardware/spi.h
 *  \defgroup hardware_spi hardware_spi
 *
 * Hardware SPI API
 *
 * RP2040 has 2 identical instances of the Serial Peripheral Interface (SPI) controller.
 *
 * The PrimeCell SSP is a master or slave interface for synchronous serial communication with peripheral devices that have
 * Motorola SPI, National Semiconductor Microwire, or Texas Instruments synchronous serial interfaces.
 *
 * Controller can be defined as master or slave using the \ref spi_set_slave function.
 *
 * Each controller can be connected to a number of GPIO pins, see the datasheet GPIO function selection table for more information.
 */

/**
 * Opaque type representing an SPI instance.
 */
typedef struct spi_inst spi_inst_t;

/** Identifier for the first (SPI 0) hardware SPI instance (for use in SPI functions).
 *
 * e.g. spi_init(spi0, 48000)
 *
 *  \ingroup hardware_spi
 */
#define spi0 ((spi_inst_t * const)spi0_hw)

/** Identifier for the second (SPI 1) hardware SPI instance (for use in SPI functions).
 *
 * e.g. spi_init(spi1, 48000)
 *
 *  \ingroup hardware_spi
 */
#define spi1 ((spi_inst_t * const)spi1_hw)

typedef enum {
    SPI_CPHA_0 = 0,
    SPI_CPHA_1 = 1
} spi_cpha_t;

typedef enum {
    SPI_CPOL_0 = 0,
    SPI_CPOL_1 = 1
} spi_cpol_t;

typedef enum {
    SPI_LSB_FIRST = 0,
    SPI_MSB_FIRST = 1
} spi_order_t;

// ----------------------------------------------------------------------------
// Setup

/*! \brief Initialise SPI instances
 *  \ingroup hardware_spi
 * Puts the SPI into a known state, and enable it. Must be called before other
 * functions.
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param baudrate Baudrate required in Hz
 *
 * \note There is no guarantee that the baudrate requested will be possible, the nearest will be chosen,
 * and this function does not return any indication of this. You can use the \ref spi_set_baudrate function
 * which will return the actual baudrate selected if this is important.
 */
void spi_init(spi_inst_t *spi, uint baudrate);

/*! \brief Deinitialise SPI instances
 *  \ingroup hardware_spi
 * Puts the SPI into a disabled state. Init will need to be called to reenable the device
 * functions.
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 */
void spi_deinit(spi_inst_t *spi);

/*! \brief Set SPI baudrate
 *  \ingroup hardware_spi
 *
 * Set SPI frequency as close as possible to baudrate, and return the actual
 * achieved rate.
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param baudrate Baudrate required in Hz, should be capable of a bitrate of at least 2Mbps, or higher, depending on system clock settings.
 * \return The actual baudrate set
 */
uint spi_set_baudrate(spi_inst_t *spi, uint baudrate);

/*! \brief Convert I2c instance to hardware instance number
 *  \ingroup hardware_spi
 *
 * \param spi SPI instance
 * \return Number of SPI, 0 or 1.
 */
static inline uint spi_get_index(spi_inst_t *spi) {
    invalid_params_if(SPI, spi != spi0 && spi != spi1);
    return spi == spi1 ? 1 : 0;
}

static inline spi_hw_t *spi_get_hw(spi_inst_t *spi) {
    spi_get_index(spi); // check it is a hw spi
    return (spi_hw_t *)spi;
}

/*! \brief Configure SPI
 *  \ingroup hardware_spi
 *
 * Configure how the SPI serialises and deserialises data on the wire
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param data_bits Number of data bits per transfer. Valid values 4..16.
 * \param cpol SSPCLKOUT polarity, applicable to Motorola SPI frame format only.
 * \param cpha SSPCLKOUT phase, applicable to Motorola SPI frame format only
 * \param order Must be SPI_MSB_FIRST, no other values supported on the PL022
 */
static inline void spi_set_format(spi_inst_t *spi, uint data_bits, spi_cpol_t cpol, spi_cpha_t cpha, spi_order_t order) {
    invalid_params_if(SPI, data_bits < 4 || data_bits > 16);
    // LSB-first not supported on PL022:
    invalid_params_if(SPI, order != SPI_MSB_FIRST);
    invalid_params_if(SPI, cpol != SPI_CPOL_0 && cpol != SPI_CPOL_1);
    invalid_params_if(SPI, cpha != SPI_CPHA_0 && cpha != SPI_CPHA_1);
    hw_write_masked(&spi_get_hw(spi)->cr0,
        (data_bits - 1) << SPI_SSPCR0_DSS_LSB |
        cpol << SPI_SSPCR0_SPO_LSB |
        cpha << SPI_SSPCR0_SPH_LSB,
        SPI_SSPCR0_DSS_BITS |
        SPI_SSPCR0_SPO_BITS |
        SPI_SSPCR0_SPH_BITS);
}

/*! \brief Set SPI master/slave
 *  \ingroup hardware_spi
 *
 * Configure the SPI for master- or slave-mode operation. By default,
 * spi_init() sets master-mode.
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param slave true to set SPI device as a slave device, false for master.
 */
static inline void spi_set_slave(spi_inst_t *spi, bool slave) {
    if (slave)
        hw_set_bits(&spi_get_hw(spi)->cr1, SPI_SSPCR1_MS_BITS);
    else
        hw_clear_bits(&spi_get_hw(spi)->cr1, SPI_SSPCR1_MS_BITS);
}

// ----------------------------------------------------------------------------
// Generic input/output

/*! \brief Check whether a write can be done on SPI device
 *  \ingroup hardware_spi
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \return 0 if no space is available to write. Non-zero if a write is possible
 *
 * \note Although the controllers each have a 8 deep TX FIFO, the current HW implementation can only return 0 or 1
 * rather than the space available.
 */
static inline size_t spi_is_writable(spi_inst_t *spi) {
    // PL022 doesn't expose levels directly, so return values are only 0 or 1
    return (spi_get_hw(spi)->sr & SPI_SSPSR_TNF_BITS) >> SPI_SSPSR_TNF_LSB;
}

/*! \brief Check whether a read can be done on SPI device
 *  \ingroup hardware_spi
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \return Non-zero if a read is possible i.e. data is present
 *
 * \note Although the controllers each have a 8 deep RX FIFO, the current HW implementation can only return 0 or 1
 * rather than the data available.
 */
static inline size_t spi_is_readable(spi_inst_t *spi) {
    return (spi_get_hw(spi)->sr & SPI_SSPSR_RNE_BITS) >> SPI_SSPSR_RNE_LSB;
}

/*! \brief Write/Read to/from an SPI device
 *  \ingroup hardware_spi
 *
 * Write \p len bytes from \p src to SPI. Simultaneously read \p len bytes from SPI to \p dst.
 * Blocks until all data is transferred. No timeout, as SPI hardware always transfers at a known data rate.
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param src Buffer of data to write
 * \param dst Buffer for read data
 * \param len Length of BOTH buffers
 * \return Number of bytes written/read
*/
int spi_write_read_blocking(spi_inst_t *spi, const uint8_t *src, uint8_t *dst, size_t len);

/*! \brief Write to an SPI device, blocking
 *  \ingroup hardware_spi
 *
 * Write \p len bytes from \p src to SPI, and discard any data received back
 * Blocks until all data is transferred. No timeout, as SPI hardware always transfers at a known data rate.
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param src Buffer of data to write
 * \param len Length of \p src
 * \return Number of bytes written/read
 */
int spi_write_blocking(spi_inst_t *spi, const uint8_t *src, size_t len);

/*! \brief Read from an SPI device
 *  \ingroup hardware_spi
 *
 * Read \p len bytes from SPI to \p dst.
 * Blocks until all data is transferred. No timeout, as SPI hardware always transfers at a known data rate.
 * \p repeated_tx_data is output repeatedly on TX as data is read in from RX.
 * Generally this can be 0, but some devices require a specific value here,
 * e.g. SD cards expect 0xff
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param repeated_tx_data Buffer of data to write
 * \param dst Buffer for read data
 * \param len Length of buffer \p dst
 * \return Number of bytes written/read
 */
int spi_read_blocking(spi_inst_t *spi, uint8_t repeated_tx_data, uint8_t *dst, size_t len);

// ----------------------------------------------------------------------------
// SPI-specific operations and aliases

// FIXME need some instance-private data for select() and deselect() if we are going that route

/*! \brief Write/Read half words to/from an SPI device
 *  \ingroup hardware_spi
 *
 * Write \p len halfwords from \p src to SPI. Simultaneously read \p len halfwords from SPI to \p dst.
 * Blocks until all data is transferred. No timeout, as SPI hardware always transfers at a known data rate.
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param src Buffer of data to write
 * \param dst Buffer for read data
 * \param len Length of BOTH buffers in halfwords
 * \return Number of bytes written/read
*/
int spi_write16_read16_blocking(spi_inst_t *spi, const uint16_t *src, uint16_t *dst, size_t len);

/*! \brief Write to an SPI device
 *  \ingroup hardware_spi
 *
 * Write \p len halfwords from \p src to SPI. Discard any data received back.
 * Blocks until all data is transferred. No timeout, as SPI hardware always transfers at a known data rate.
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param src Buffer of data to write
 * \param len Length of buffers
 * \return Number of bytes written/read
*/
int spi_write16_blocking(spi_inst_t *spi, const uint16_t *src, size_t len);

/*! \brief Read from an SPI device
 *  \ingroup hardware_spi
 *
 * Read \p len halfwords from SPI to \p dst.
 * Blocks until all data is transferred. No timeout, as SPI hardware always transfers at a known data rate.
 * \p repeated_tx_data is output repeatedly on TX as data is read in from RX.
 * Generally this can be 0, but some devices require a specific value here,
 * e.g. SD cards expect 0xff
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param repeated_tx_data Buffer of data to write
 * \param dst Buffer for read data
 * \param len Length of buffer \p dst  in halfwords
 * \return Number of bytes written/read
 */
int spi_read16_blocking(spi_inst_t *spi, uint16_t repeated_tx_data, uint16_t *dst, size_t len);

#ifdef __cplusplus
}
#endif

#endif
