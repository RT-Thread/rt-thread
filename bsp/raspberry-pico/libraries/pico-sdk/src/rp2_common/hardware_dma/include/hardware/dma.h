/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_DMA_H_
#define _HARDWARE_DMA_H_

#include "pico.h"
#include "hardware/structs/dma.h"
#include "hardware/regs/dreq.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file hardware/dma.h
 *  \defgroup hardware_dma hardware_dma
 *
 * DMA Controller API
 *
 * The RP2040 Direct Memory Access (DMA) master performs bulk data transfers on a processor’s
 * behalf. This leaves processors free to attend to other tasks, or enter low-power sleep states. The
 * data throughput of the DMA is also significantly higher than one of RP2040’s processors.
 *
 * The DMA can perform one read access and one write access, up to 32 bits in size, every clock cycle.
 * There are 12 independent channels, which each supervise a sequence of bus transfers, usually in
 * one of the following scenarios:
 *
 * * Memory to peripheral
 * * Peripheral to memory
 * * Memory to memory
 */

// this is not defined in generated dreq.h
#define DREQ_FORCE  63

/*! \brief Mark a dma channel as used
 *  \ingroup hardware_dma
 *
 * Method for cooperative claiming of hardware. Will cause a panic if the channel
 * is already claimed. Use of this method by libraries detects accidental
 * configurations that would fail in unpredictable ways.
 *
 * \param channel the dma channel
 */
void dma_channel_claim(uint channel);

/*! \brief Mark multiple dma channels as used
 *  \ingroup hardware_dma
 *
 * Method for cooperative claiming of hardware. Will cause a panic if any of the channels
 * are already claimed. Use of this method by libraries detects accidental
 * configurations that would fail in unpredictable ways.
 *
 * \param channel_mask Bitfield of all required channels to claim (bit 0 == channel 0, bit 1 == channel 1 etc)
 */
void dma_claim_mask(uint32_t channel_mask);

/*! \brief Mark a dma channel as no longer used
 *  \ingroup hardware_dma
 *
 * Method for cooperative claiming of hardware.
 *
 * \param channel the dma channel to release
 */
void dma_channel_unclaim(uint channel);

/*! \brief Claim a free dma channel
 *  \ingroup hardware_dma
 *
 * \param required if true the function will panic if none are available
 * \return the dma channel number or -1 if required was false, and none were free
 */
int dma_claim_unused_channel(bool required);

/** \brief DMA channel configuration
 *  \defgroup channel_config channel_config
 *  \ingroup hardware_dma
 *
 * A DMA channel needs to be configured, these functions provide handy helpers to set up configuration
 * structures. See \ref dma_channel_config
 *
 */

/*! \brief Enumeration of available DMA channel transfer sizes.
 *  \ingroup hardware_dma
 *
 * Names indicate the number of bits.
 */
enum dma_channel_transfer_size {
    DMA_SIZE_8 = 0,    ///< Byte transfer (8 bits)
    DMA_SIZE_16 = 1,   ///< Half word transfer (16 bits)
    DMA_SIZE_32 = 2    ///< Word transfer (32 bits)
};

typedef struct {
    uint32_t ctrl;
} dma_channel_config;

/*! \brief  Set DMA channel read increment
 *  \ingroup channel_config
 *
 * \param c Pointer to channel configuration data
 * \param incr True to enable read address increments, if false, each read will be from the same address
 *             Usually disabled for peripheral to memory transfers
 */
static inline void channel_config_set_read_increment(dma_channel_config *c, bool incr) {
    c->ctrl = incr ? (c->ctrl | DMA_CH0_CTRL_TRIG_INCR_READ_BITS) : (c->ctrl & ~DMA_CH0_CTRL_TRIG_INCR_READ_BITS);
}

/*! \brief  Set DMA channel write increment
 *  \ingroup channel_config
 *
 * \param c Pointer to channel configuration data
 * \param incr True to enable write address increments, if false, each write will be to the same address
 *             Usually disabled for memory to peripheral transfers
 * Usually disabled for memory to peripheral transfers
 */
static inline void channel_config_set_write_increment(dma_channel_config *c, bool incr) {
    c->ctrl = incr ? (c->ctrl | DMA_CH0_CTRL_TRIG_INCR_WRITE_BITS) : (c->ctrl & ~DMA_CH0_CTRL_TRIG_INCR_WRITE_BITS);
}

/*! \brief  Select a transfer request signal
 *  \ingroup channel_config
 *
 * The channel uses the transfer request signal to pace its data transfer rate.
 * Sources for TREQ signals are internal (TIMERS) or external (DREQ, a Data Request from the system).
 * 0x0 to 0x3a -> select DREQ n as TREQ
 * 0x3b -> Select Timer 0 as TREQ
 * 0x3c -> Select Timer 1 as TREQ
 * 0x3d -> Select Timer 2 as TREQ (Optional)
 * 0x3e -> Select Timer 3 as TREQ (Optional)
 * 0x3f -> Permanent request, for unpaced transfers.
 *
 * \param c Pointer to channel configuration data
 * \param dreq Source (see description)
 */
static inline void channel_config_set_dreq(dma_channel_config *c, uint dreq) {
    assert(dreq <= DREQ_FORCE);
    c->ctrl = (c->ctrl & ~DMA_CH0_CTRL_TRIG_TREQ_SEL_BITS) | (dreq << DMA_CH0_CTRL_TRIG_TREQ_SEL_LSB);
}

/*! \brief  Set DMA channel completion channel
 *  \ingroup channel_config
 *
 * When this channel completes, it will trigger the channel indicated by chain_to. Disable by
 * setting chain_to to itself (the same channel)
 *
 * \param c Pointer to channel configuration data
 * \param chain_to Channel to trigger when this channel completes.
 */
static inline void channel_config_set_chain_to(dma_channel_config *c, uint chain_to) {
    assert(chain_to <= NUM_DMA_CHANNELS);
    c->ctrl = (c->ctrl & ~DMA_CH0_CTRL_TRIG_CHAIN_TO_BITS) | (chain_to << DMA_CH0_CTRL_TRIG_CHAIN_TO_LSB);
}

/*! \brief Set the size of each DMA bus transfer
 *  \ingroup channel_config
 *
 * Set the size of each bus transfer (byte/halfword/word). The read and write addresses
 * advance by the specific amount (1/2/4 bytes) with each transfer.
 *
 * \param c Pointer to channel configuration data
 * \param size See enum for possible values.
 */
static inline void channel_config_set_transfer_data_size(dma_channel_config *c, enum dma_channel_transfer_size size) {
    assert(size == DMA_SIZE_8 || size == DMA_SIZE_16 || size == DMA_SIZE_32);
    c->ctrl = (c->ctrl & ~DMA_CH0_CTRL_TRIG_DATA_SIZE_BITS) | (size << DMA_CH0_CTRL_TRIG_DATA_SIZE_LSB);
}

/*! \brief  Set address wrapping parameters
 *  \ingroup channel_config
 *
 * Size of address wrap region. If 0, don’t wrap. For values n > 0, only the lower n bits of the address
 * will change. This wraps the address on a (1 << n) byte boundary, facilitating access to naturally-aligned
 * ring buffers.
 * Ring sizes between 2 and 32768 bytes are possible (size_bits from 1 - 15)
 *
 * 0x0 -> No wrapping.
 *
 * \param c Pointer to channel configuration data
 * \param write True to apply to write addresses, false to apply to read addresses
 * \param size_bits 0 to disable wrapping. Otherwise the size in bits of the changing part of the address.
 *        Effectively wraps the address on a (1 << size_bits) byte boundary.
 */
static inline void channel_config_set_ring(dma_channel_config *c, bool write, uint size_bits) {
    assert(size_bits < 32);
    c->ctrl = (c->ctrl & ~(DMA_CH0_CTRL_TRIG_RING_SIZE_BITS | DMA_CH0_CTRL_TRIG_RING_SEL_BITS)) |
              (size_bits << DMA_CH0_CTRL_TRIG_RING_SIZE_LSB) |
              (write ? DMA_CH0_CTRL_TRIG_RING_SEL_BITS : 0);
}

/*! \brief  Set DMA byte swapping
 *  \ingroup channel_config
 *
 * No effect for byte data, for halfword data, the two bytes of each halfword are
 * swapped. For word data, the four bytes of each word are swapped to reverse their order.
 *
 * \param c Pointer to channel configuration data
 * \param bswap True to enable byte swapping
 */
static inline void channel_config_set_bswap(dma_channel_config *c, bool bswap) {
    c->ctrl = bswap ? (c->ctrl | DMA_CH0_CTRL_TRIG_BSWAP_BITS) : (c->ctrl & ~DMA_CH0_CTRL_TRIG_BSWAP_BITS);
}

/*! \brief  Set IRQ quiet mode
 *  \ingroup channel_config
 *
 * In QUIET mode, the channel does not generate IRQs at the end of every transfer block. Instead,
 * an IRQ is raised when NULL is written to a trigger register, indicating the end of a control
 * block chain.
 *
 * \param c Pointer to channel configuration data
 * \param irq_quiet True to enable quiet mode, false to disable.
 */
static inline void channel_config_set_irq_quiet(dma_channel_config *c, bool irq_quiet) {
    c->ctrl = irq_quiet ? (c->ctrl | DMA_CH0_CTRL_TRIG_IRQ_QUIET_BITS) : (c->ctrl & ~DMA_CH0_CTRL_TRIG_IRQ_QUIET_BITS);
}

/*!
 *  \brief Enable/Disable the DMA channel
 *  \ingroup channel_config
 *
 * When false, the channel will ignore triggers, stop issuing transfers, and pause the current transfer sequence (i.e. BUSY will
 * remain high if already high)
 *
 * \param c Pointer to channel configuration data
 * \param enable True to enable the DMA channel. When enabled, the channel will respond to triggering events, and start transferring data.
 *
 */
static inline void channel_config_set_enable(dma_channel_config *c, bool enable) {
    c->ctrl = enable ? (c->ctrl | DMA_CH0_CTRL_TRIG_EN_BITS) : (c->ctrl & ~DMA_CH0_CTRL_TRIG_EN_BITS);
}

/*! \brief  Enable access to channel by sniff hardware.
 *  \ingroup channel_config
 *
 * Sniff HW must be enabled and have this channel selected.
 *
 * \param c Pointer to channel configuration data
 * \param sniff_enable True to enable the Sniff HW access to this DMA channel.
 */
static inline void channel_config_set_sniff_enable(dma_channel_config *c, bool sniff_enable) {
    c->ctrl = sniff_enable ? (c->ctrl | DMA_CH0_CTRL_TRIG_SNIFF_EN_BITS) : (c->ctrl &
                                                                             ~DMA_CH0_CTRL_TRIG_SNIFF_EN_BITS);
}

/*! \brief  Get the default channel configuration for a given channel
 *  \ingroup channel_config
 *
 * Setting | Default
 * --------|--------
 * Read Increment | true
 * Write Increment | false
 * DReq | DREQ_FORCE
 * Chain to | self
 * Data size | DMA_SIZE_32
 * Ring | write=false, size=0 (i.e. off)
 * Byte Swap | false
 * Quiet IRQs | false
 * Channel Enable | true
 * Sniff Enable | false
 *
 * \param channel DMA channel
 * \return the default configuration which can then be modified.
 */
static inline dma_channel_config dma_channel_get_default_config(uint channel) {
    dma_channel_config c = {0};
    channel_config_set_read_increment(&c, true);
    channel_config_set_write_increment(&c, false);
    channel_config_set_dreq(&c, DREQ_FORCE);
    channel_config_set_chain_to(&c, channel);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
    channel_config_set_ring(&c, false, 0);
    channel_config_set_bswap(&c, false);
    channel_config_set_irq_quiet(&c, false);
    channel_config_set_enable(&c, true);
    channel_config_set_sniff_enable(&c, false);
    return c;
}

/*! \brief  Get the current configuration for the specified channel.
 *  \ingroup channel_config
 *
 * \param channel DMA channel
 * \return The current configuration as read from the HW register (not cached)
 */
static inline dma_channel_config dma_get_channel_config(uint channel) {
    dma_channel_config c;
    c.ctrl = dma_channel_hw_addr(channel)->ctrl_trig;
    return c;
}

/*! \brief  Get the raw configuration register from a channel configuration
 *  \ingroup channel_config
 *
 * \param config Pointer to a config structure.
 * \return Register content
 */
static inline uint32_t channel_config_get_ctrl_value(const dma_channel_config *config) {
    return config->ctrl;
}

/*! \brief  Set a channel configuration
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \param config Pointer to a config structure with required configuration
 * \param trigger True to trigger the transfer immediately
 */
static inline void dma_channel_set_config(uint channel, const dma_channel_config *config, bool trigger) {
    // Don't use CTRL_TRIG since we don't want to start a transfer
    if (!trigger) {
        dma_channel_hw_addr(channel)->al1_ctrl = channel_config_get_ctrl_value(config);
    } else {
        dma_channel_hw_addr(channel)->ctrl_trig = channel_config_get_ctrl_value(config);
    }
}

/*! \brief  Set the DMA initial read address.
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \param read_addr Initial read address of transfer.
 * \param trigger True to start the transfer immediately
 */
static inline void dma_channel_set_read_addr(uint channel, const volatile void *read_addr, bool trigger) {
    if (!trigger) {
        dma_channel_hw_addr(channel)->read_addr = (uintptr_t) read_addr;
    } else {
        dma_channel_hw_addr(channel)->al3_read_addr_trig = (uintptr_t) read_addr;
    }
}

/*! \brief  Set the DMA initial read address
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \param write_addr Initial write address of transfer.
 * \param trigger True to start the transfer immediately
 */
static inline void dma_channel_set_write_addr(uint channel, volatile void *write_addr, bool trigger) {
    if (!trigger) {
        dma_channel_hw_addr(channel)->write_addr = (uintptr_t) write_addr;
    } else {
        dma_channel_hw_addr(channel)->al2_write_addr_trig = (uintptr_t) write_addr;
    }
}

/*! \brief  Set the number of bus transfers the channel will do
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \param trans_count The number of transfers (not NOT bytes, see channel_config_set_transfer_data_size)
 * \param trigger True to start the transfer immediately
 */
static inline void dma_channel_set_trans_count(uint channel, uint32_t trans_count, bool trigger) {
    if (!trigger) {
        dma_channel_hw_addr(channel)->transfer_count = trans_count;
    } else {
        dma_channel_hw_addr(channel)->al1_transfer_count_trig = trans_count;
    }
}

/*! \brief  Configure all DMA parameters and optionally start transfer
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \param config Pointer to DMA config structure
 * \param write_addr Initial write address
 * \param read_addr Initial read address
 * \param transfer_count Number of transfers to perform
 * \param trigger True to start the transfer immediately
 */
static inline void dma_channel_configure(uint channel, const dma_channel_config *config, volatile void *write_addr,
                                         const volatile void *read_addr,
                                         uint transfer_count, bool trigger) {
    dma_channel_set_read_addr(channel, read_addr, false);
    dma_channel_set_write_addr(channel, write_addr, false);
    dma_channel_set_trans_count(channel, transfer_count, false);
    dma_channel_set_config(channel, config, trigger);
}

/*! \brief Start a DMA transfer from a buffer immediately
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \param read_addr Sets the initial read address
 * \param transfer_count Number of transfers to make. Not bytes, but the number of transfers of channel_config_set_transfer_data_size() to be sent.
 */
inline static void __attribute__((always_inline)) dma_channel_transfer_from_buffer_now(uint channel, void *read_addr,
                                                                                       uint32_t transfer_count) {
//    check_dma_channel_param(channel);
    dma_channel_hw_t *hw = dma_channel_hw_addr(channel);
    hw->read_addr = (uintptr_t) read_addr;
    hw->al1_transfer_count_trig = transfer_count;
}

/*! \brief Start a DMA transfer to a buffer immediately
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \param write_addr Sets the initial write address
 * \param transfer_count Number of transfers to make. Not bytes, but the number of transfers of channel_config_set_transfer_data_size() to be sent.
 */
inline static void dma_channel_transfer_to_buffer_now(uint channel, void *write_addr, uint32_t transfer_count) {
    dma_channel_hw_t *hw = dma_channel_hw_addr(channel);
    hw->write_addr = (uintptr_t) write_addr;
    hw->al1_transfer_count_trig = transfer_count;
}

/*! \brief  Start one or more channels simultaneously
 *  \ingroup hardware_dma
 *
 * \param chan_mask Bitmask of all the channels requiring starting. Channel 0 = bit 0, channel 1 = bit 1 etc.
 */
static inline void dma_start_channel_mask(uint32_t chan_mask) {
    valid_params_if(DMA, chan_mask && chan_mask < (1u << NUM_DMA_CHANNELS));
    dma_hw->multi_channel_trigger = chan_mask;
}

/*! \brief  Start a single DMA channel
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 */
static inline void dma_channel_start(uint channel) {
    dma_start_channel_mask(1u << channel);
}

/*! \brief  Stop a DMA transfer
 *  \ingroup hardware_dma
 *
 * Function will only return once the DMA has stopped.
 *
 * \param channel DMA channel
 */
static inline void dma_channel_abort(uint channel) {
    check_dma_channel_param(channel);
    dma_hw->abort = 1u << channel;
    // Bit will go 0 once channel has reached safe state
    // (i.e. any in-flight transfers have retired)
    while (dma_hw->abort & (1ul << channel)) tight_loop_contents();
}

/*! \brief  Enable single DMA channel interrupt 0
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \param enabled true to enable interrupt 0 on specified channel, false to disable.
 */
static inline void dma_channel_set_irq0_enabled(uint channel, bool enabled) {
    check_dma_channel_param(channel);
    check_hw_layout(dma_hw_t, inte0, DMA_INTE0_OFFSET);
    if (enabled)
        hw_set_bits(&dma_hw->inte0, 1u << channel);
    else
        hw_clear_bits(&dma_hw->inte0, 1u << channel);
}

/*! \brief  Enable multiple DMA channels interrupt 0
 *  \ingroup hardware_dma
 *
 * \param channel_mask Bitmask of all the channels to enable/disable. Channel 0 = bit 0, channel 1 = bit 1 etc.
 * \param enabled true to enable all the interrupts specified in the mask, false to disable all the interrupts specified in the mask.
 */
static inline void dma_set_irq0_channel_mask_enabled(uint32_t channel_mask, bool enabled) {
    if (enabled) {
        hw_set_bits(&dma_hw->inte0, channel_mask);
    } else {
        hw_clear_bits(&dma_hw->inte0, channel_mask);
    }
}

/*! \brief  Enable single DMA channel interrupt 1
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \param enabled true to enable interrupt 1 on specified channel, false to disable.
 */
static inline void dma_channel_set_irq1_enabled(uint channel, bool enabled) {
    check_dma_channel_param(channel);
    check_hw_layout(dma_hw_t, inte1, DMA_INTE1_OFFSET);
    if (enabled)
        hw_set_bits(&dma_hw->inte1, 1u << channel);
    else
        hw_clear_bits(&dma_hw->inte1, 1u << channel);
}

/*! \brief  Enable multiple DMA channels interrupt 0
 *  \ingroup hardware_dma
 *
 * \param channel_mask Bitmask of all the channels to enable/disable. Channel 0 = bit 0, channel 1 = bit 1 etc.
 * \param enabled true to enable all the interrupts specified in the mask, false to disable all the interrupts specified in the mask.
 */
static inline void dma_set_irq1_channel_mask_enabled(uint32_t channel_mask, bool enabled) {
    if (enabled) {
        hw_set_bits(&dma_hw->inte1, channel_mask);
    } else {
        hw_clear_bits(&dma_hw->inte1, channel_mask);
    }
}

/*! \brief  Check if DMA channel is busy
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \return true if the channel is currently busy
 */
inline static bool dma_channel_is_busy(uint channel) {
    check_dma_channel_param(channel);
    return !!(dma_hw->ch[channel].al1_ctrl & DMA_CH0_CTRL_TRIG_BUSY_BITS);
}

/*! \brief  Wait for a DMA channel transfer to complete
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 */
inline static void dma_channel_wait_for_finish_blocking(uint channel) {
    while (dma_channel_is_busy(channel)) tight_loop_contents();
}

/*! \brief Enable the DMA sniffing targeting the specified channel
 *  \ingroup hardware_dma
 *
 * The mode can be one of the following:
 *
 * Mode | Function
 * -----|---------
 * 0x0 | Calculate a CRC-32 (IEEE802.3 polynomial)
 * 0x1 | Calculate a CRC-32 (IEEE802.3 polynomial) with bit reversed data
 * 0x2 | Calculate a CRC-16-CCITT
 * 0x3 | Calculate a CRC-16-CCITT with bit reversed data
 * 0xe | XOR reduction over all data. == 1 if the total 1 population count is odd.
 * 0xf | Calculate a simple 32-bit checksum (addition with a 32 bit accumulator)
 *
 * \param channel DMA channel
 * \param mode See description
 * \param force_channel_enable Set true to also turn on sniffing in the channel configuration (this
 * is usually what you want, but sometimes you might have a chain DMA with only certain segments
 * of the chain sniffed, in which case you might pass false).
 */
inline static void dma_sniffer_enable(uint channel, uint mode, bool force_channel_enable) {
    check_dma_channel_param(channel);
    check_hw_layout(dma_hw_t, sniff_ctrl, DMA_SNIFF_CTRL_OFFSET);
    if (force_channel_enable) {
        hw_set_bits(&dma_hw->ch[channel].al1_ctrl, DMA_CH0_CTRL_TRIG_SNIFF_EN_BITS);
    }
    dma_hw->sniff_ctrl = ((channel << DMA_SNIFF_CTRL_DMACH_LSB) & DMA_SNIFF_CTRL_DMACH_BITS) |
                         ((mode << DMA_SNIFF_CTRL_CALC_LSB) & DMA_SNIFF_CTRL_CALC_BITS) |
                         DMA_SNIFF_CTRL_EN_BITS;
}

/*! \brief Enable the Sniffer byte swap function
 *  \ingroup hardware_dma
 *
 * Locally perform a byte reverse on the sniffed data, before feeding into checksum.
 *
 * Note that the sniff hardware is downstream of the DMA channel byteswap performed in the
 * read master: if channel_config_set_bswap() and dma_sniffer_set_byte_swap_enabled() are both enabled,
 * their effects cancel from the sniffer’s point of view.
 *
 * \param swap Set true to enable byte swapping
 */
inline static void dma_sniffer_set_byte_swap_enabled(bool swap) {
    if (swap)
        hw_set_bits(&dma_hw->sniff_ctrl, DMA_SNIFF_CTRL_BSWAP_BITS);
    else
        hw_clear_bits(&dma_hw->sniff_ctrl, DMA_SNIFF_CTRL_BSWAP_BITS);
}

/*! \brief Disable the DMA sniffer
 *  \ingroup hardware_dma
 *
 */
inline static void dma_sniffer_disable() {
    dma_hw->sniff_ctrl = 0;
}

#ifndef NDEBUG
void print_dma_ctrl(dma_channel_hw_t *channel);
#endif

#ifdef __cplusplus
}
#endif

#endif
