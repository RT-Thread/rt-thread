/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_I2C_DRV_H
#define HPM_I2C_DRV_H
#include "hpm_common.h"
#include "hpm_i2c_regs.h"
#include "hpm_soc_feature.h"

/**
 * @brief I2C driver APIs
 * @defgroup i2c_interface I2C driver APIs
 * @ingroup io_interfaces
 * @{
 */

/**
 * @brief I2C status
 */
enum {
    status_i2c_no_ack = MAKE_STATUS(status_group_i2c, 1),
    status_i2c_invalid_data = MAKE_STATUS(status_group_i2c, 2),
    status_i2c_no_addr_hit = MAKE_STATUS(status_group_i2c, 3),
    status_i2c_transmit_not_completed = MAKE_STATUS(status_group_i2c, 4),
    status_i2c_not_supported = MAKE_STATUS(status_group_i2c, 9),
};

/* convert data count value into CTRL[DATACNT] value map */
/* x range from 1 to I2C_SOC_TRANSFER_COUNT_MAX */
/* 0 for I2C_SOC_TRANSFER_COUNT_MAX */
#define I2C_DATACNT_MAP(x) (((x) == I2C_SOC_TRANSFER_COUNT_MAX) ? 0 : x)

/**
 * @brief I2C CMD
 */
#define I2C_CMD_NO_ACTION (I2C_CMD_CMD_SET(0))
#define I2C_CMD_ISSUE_DATA_TRANSMISSION (I2C_CMD_CMD_SET(1))
#define I2C_CMD_ACK (I2C_CMD_CMD_SET(2))
#define I2C_CMD_NACK (I2C_CMD_CMD_SET(3))
#define I2C_CMD_CLEAR_FIFO (I2C_CMD_CMD_SET(4))
#define I2C_CMD_RESET (I2C_CMD_CMD_SET(5))

/**
 * @brief I2C data direction
 */
#define I2C_DIR_MASTER_WRITE (0U)
#define I2C_DIR_MASTER_READ (1U)
#define I2C_DIR_SLAVE_READ (0U)
#define I2C_DIR_SLAVE_WRITE (1U)

/**
 * @brief I2C events for interrupt enable and status check
 */
#define I2C_EVENT_TRANSACTION_COMPLETE  I2C_INTEN_CMPL_MASK
#define I2C_EVENT_BYTE_RECEIVED         I2C_INTEN_BYTERECV_MASK
#define I2C_EVENT_BYTE_TRANSMIT         I2C_INTEN_BYTETRANS_MASK
#define I2C_EVENT_START_CONDITION       I2C_INTEN_START_MASK
#define I2C_EVENT_STOP_CONDITION        I2C_INTEN_STOP_MASK
#define I2C_EVENT_LOSS_ARBITRATION      I2C_INTEN_ARBLOSE_MASK
#define I2C_EVENT_ADDRESS_HIT           I2C_INTEN_ADDRHIT_MASK
#define I2C_EVENT_FIFO_HALF             I2C_INTEN_FIFOHALF_MASK
#define I2C_EVENT_FIFO_FULL             I2C_INTEN_FIFOFULL_MASK
#define I2C_EVENT_FIFO_EMPTY            I2C_INTEN_FIFOEMPTY_MASK

#define I2C_EVENT_ALL_MASK          (I2C_INTEN_CMPL_MASK \
                                        | I2C_INTEN_BYTERECV_MASK \
                                        | I2C_INTEN_BYTETRANS_MASK \
                                        | I2C_INTEN_START_MASK \
                                        | I2C_INTEN_STOP_MASK \
                                        | I2C_INTEN_ARBLOSE_MASK \
                                        | I2C_INTEN_ADDRHIT_MASK \
                                        | I2C_INTEN_FIFOHALF_MASK \
                                        | I2C_INTEN_FIFOFULL_MASK \
                                        | I2C_INTEN_FIFOEMPTY_MASK)
/**
 * @brief I2C status for status check only
 */
#define I2C_STATUS_LINE_SDA             I2C_STATUS_LINESDA_MASK
#define I2C_STATUS_LINE_SCL             I2C_STATUS_LINESCL_MASK
#define I2C_STATUS_GENERAL_CALL         I2C_STATUS_GENCALL_MASK
#define I2C_STATUS_BUS_BUSY             I2C_STATUS_BUSBUSY_MASK
#define I2C_STATUS_ACK                  I2C_STATUS_ACK_MASK

/**
 * @brief I2C config
 */
typedef struct {
    bool is_10bit_addressing;
    uint8_t i2c_mode;
} i2c_config_t;

/**
 * @brief I2C mode
 */
typedef enum i2c_mode {
    i2c_mode_normal,
    i2c_mode_fast,
    i2c_mode_fast_plus,
} i2c_mode_t;

/**
 * @brief I2c sequential transfer options
 * @arg: i2c_frist_frame: has start signal
 * @arg: i2c_next_frame: middle transfer
 * @arg: i2c_last_frame: has stop signal
 */
typedef enum i2c_seq_transfer_opt {
    i2c_frist_frame = 0,
    i2c_next_frame,
    i2c_last_frame,
} i2c_seq_transfer_opt_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief respond NACK
 *
 * @param [in] ptr I2C base address
 */
static inline void i2c_respond_Nack(I2C_Type *ptr)
{
    ptr->CMD = I2C_CMD_NACK;
}

/**
 * @brief respond ACK
 *
 * @param [in] ptr I2C base address
 */
static inline void i2c_respond_ack(I2C_Type *ptr)
{
    ptr->CMD = I2C_CMD_ACK;
}

/**
 * @brief clear I2C fifo
 *
 * @param [in] ptr I2C base address
 */
static inline void i2c_clear_fifo(I2C_Type *ptr)
{
    ptr->CMD = I2C_CMD_CLEAR_FIFO;
}

/**
 * @brief check data count
 *
 * @details It indicates number of bytes to transfer
 *
 * @param [in] ptr I2C base address
 * @retval data count value in byte
 */
static inline uint8_t i2c_get_data_count(I2C_Type *ptr)
{
    return I2C_CTRL_DATACNT_GET(ptr->CTRL);
}

/**
 * @brief check if I2C FIFO is full
 *
 * @param [in] ptr I2C base address
 * @retval true if FIFO is full
 */
static inline bool i2c_fifo_is_full(I2C_Type *ptr)
{
    return ptr->STATUS & I2C_STATUS_FIFOFULL_MASK;
}

/**
 * @brief check if I2C FIFO is half
 *
 * @note When I2C is transmitting data, it indicates if fifo is half-empty;
 * @note When I2C is receiving data, it indicates if fifo is half full.
 *
 * @param [in] ptr I2C base address
 * @retval true if FIFO is half empty or full
 */
static inline bool i2c_fifo_is_half(I2C_Type *ptr)
{
    return ptr->STATUS & I2C_STATUS_FIFOHALF_MASK;
}

/**
 * @brief check if I2C FIFO is empty
 *
 * @param [in] ptr I2C base address
 * @retval true if FIFO is empty
 */
static inline bool i2c_fifo_is_empty(I2C_Type *ptr)
{
    return ptr->STATUS & I2C_STATUS_FIFOEMPTY_MASK;
}

/**
 * @brief check if I2C is writing
 *
 * @param [in] ptr I2C base address
 * @retval bool value
 *  @arg true: receive data if master mode, send data in slave mode
 *  @arg false: send data if master mode, reveive data in slave mode
 *
 */
static inline bool i2c_is_writing(I2C_Type *ptr)
{
    return (ptr->CTRL & I2C_CTRL_DIR_MASK);
}

/**
 * @brief check if I2C is reading
 *
 * @param [in] ptr I2C base address
 * @retval bool value
 *  @arg true: send data if master mode, receive data in slave mode
 *  @arg false: receive data if master mode, send data in slave mode
 *
 */
static inline bool i2c_is_reading(I2C_Type *ptr)
{
    return !i2c_is_writing(ptr);
}

/**
 * @brief get i2c sda line status
 *
 * @param [in] ptr I2C base address
 * @retval bool value
 *  @arg true: the sda line is high
 *  @arg false: the sda line is low
 *
 */
static inline bool i2c_get_line_sda_status(I2C_Type *ptr)
{
    return I2C_STATUS_LINESDA_GET(ptr->STATUS);
}

/**
 * @brief get i2c scl line status
 *
 * @param [in] ptr I2C base address
 * @retval bool value
 *  @arg true: the scl line is high
 *  @arg false: the scl line is low
 *
 */
static inline bool i2c_get_line_scl_status(I2C_Type *ptr)
{
    return I2C_STATUS_LINESCL_GET(ptr->STATUS);
}

/**
 * @brief clear status
 *
 * @details Clear status based on mask
 *
 * @param [in] ptr I2C base address
 * @param [in] mask mask to clear status
 */
static inline void i2c_clear_status(I2C_Type *ptr, uint32_t mask)
{
    ptr->STATUS |= (mask & I2C_EVENT_ALL_MASK);
}

/**
 * @brief get status
 *
 * @details Get current I2C status bits
 *
 * @param [in] ptr I2C base address
 * @retval current I2C status
 */
static inline uint32_t i2c_get_status(I2C_Type *ptr)
{
    return ptr->STATUS;
}

/**
 * @brief i2c get interrupts setting
 *
 * @details Get interrupt setting register value
 *
 * @param [in] ptr I2C base address
 * @retval [out] uint32_t interrupt setting register value
 */
static inline uint32_t i2c_get_irq_setting(I2C_Type *ptr)
{
    return ptr->INTEN;
}

/**
 * @brief disable interrupts
 *
 * @details Disable interrupts based on given mask
 *
 * @param [in] ptr I2C base address
 * @param [in] mask interrupt mask to be disabled
 */
static inline void i2c_disable_irq(I2C_Type *ptr, uint32_t mask)
{
    ptr->INTEN &= ~mask;
}

/**
 * @brief enable interrupts
 *
 * @details Enable interrupts based on given mask
 *
 * @param [in] ptr I2C base address
 * @param [in] mask interrupt mask to be enabled
 */
static inline void i2c_enable_irq(I2C_Type *ptr, uint32_t mask)
{
    ptr->INTEN |= mask;
}

/**
 * @brief disable auto ack
 *
 * @details Disable I2C auto generates proper acknowledgements for each byte received
 *
 * @param [in] ptr I2C base address
 */
static inline void i2c_disable_auto_ack(I2C_Type *ptr)
{
    ptr->INTEN &= ~I2C_EVENT_BYTE_RECEIVED;
}

/**
 * @brief enable auto ack
 *
 * @details Enable I2C auto generates proper acknowledgements for each byte received
 *
 * @param [in] ptr I2C base address
 */
static inline void i2c_enable_auto_ack(I2C_Type *ptr)
{
    ptr->INTEN |= I2C_EVENT_BYTE_RECEIVED;
}

/**
 * @brief enable 10 bit address mode
 *
 * @details enable 10 bit address mode, if not, address is 7 bit mode
 *
 * @param [in] ptr I2C base address
 * @param [in] enable
 *  @arg true: enable 10 bit address mode
 *  @arg false: enable 7 bit address mode
 */
static inline void i2c_enable_10bit_address_mode(I2C_Type *ptr, bool enable)
{
    ptr->SETUP |= I2C_SETUP_ADDRESSING_SET(enable);
}

/**
 * @brief I2C master initialization
 *
 * @details Initialized I2C controller working at master mode
 *
 * @param [in] ptr I2C base address
 * @param [in] src_clk_in_hz I2C controller source clock source frequency in Hz
 * @param [in] config i2c_config_t
 * @retval hpm_stat_t: status_success if initialization is completed without any error
 */
hpm_stat_t i2c_init_master(I2C_Type *ptr,
                           uint32_t src_clk_in_hz,
                           i2c_config_t *config);

/**
 * @brief I2C master write data to specific address of certain slave device
 *
 * @details Write to certain I2C device at specific address within that device
 * @note the sum of addr_size_in_byte and size_in_byte should not not greater than I2C_SOC_TRANSFER_COUNT_MAX
 *
 * @param [in] ptr I2C base address
 * @param [in] device_address I2C slave address
 * @param [in] addr address in that I2C device
 * @param [in] addr_size_in_byte I2C address in byte
 * @param [in] buf pointer of the data to be sent
 * @param [in] size_in_byte size of data to be sent in bytes
 * @retval hpm_stat_t: status_success if writing is completed without any error
 */
hpm_stat_t i2c_master_address_write(I2C_Type *ptr,
                            const uint16_t device_address,
                            uint8_t *addr,
                            uint32_t addr_size_in_byte,
                            uint8_t *buf,
                            const uint32_t size_in_byte);

/**
 * @brief I2C master read data from specific address of certain slave device
 *
 * @details Read fram certain I2C device at specific address within that device
 * @note both addr_size_in_byte and size_in_byte should not not greater than I2C_SOC_TRANSFER_COUNT_MAX
 *
 * @param [in] ptr I2C base address
 * @param [in] device_address I2C slave address
 * @param [in] addr address in that I2C device
 * @param [in] addr_size_in_byte I2C address in byte
 * @param [out] buf pointer of the buffer to receive data read from the device
 * @param [in] size_in_byte size of data to be read in bytes
 * @retval hpm_stat_t: status_success if reading is completed without any error
 */
hpm_stat_t i2c_master_address_read(I2C_Type *ptr,
                           const uint16_t device_address,
                           uint8_t *addr,
                           uint32_t addr_size_in_byte,
                           uint8_t *buf,
                           const uint32_t size_in_byte);

/**
 * @brief I2C master write data to certain slave device
 *
 * @details Write data to I2C device
 * @note size should not not greater than I2C_SOC_TRANSFER_COUNT_MAX
 *
 * @param [in] ptr I2C base address
 * @param [in] device_address I2C slave address
 * @param [in] buf pointer of the data to be sent
 * @param [in] size size of data to be sent in bytes
 * @retval hpm_stat_t: status_success if writing is completed without any error
 */
hpm_stat_t i2c_master_write(I2C_Type *ptr,
                            const uint16_t device_address,
                            uint8_t *buf,
                            const uint32_t size);

/**
 * @brief I2C master start write data by DMA
 *
 * @details Write data to I2C device by DMA
 * @note size should not not greater than I2C_SOC_TRANSFER_COUNT_MAX
 *
 * @param [in] i2c_ptr I2C base address
 * @param [in] device_address I2C slave address
 * @param [in] size size of data to be sent in bytes
 * @retval hpm_stat_t status_success if starting transmission without any error
 */
hpm_stat_t i2c_master_start_dma_write(I2C_Type *i2c_ptr, const uint16_t device_address, uint32_t size);

/**
 * @brief I2C master start read data by DMA
 *
 * @details Read data to I2C device by DMA
 * @note size should not not greater than I2C_SOC_TRANSFER_COUNT_MAX
 *
 * @param [in] i2c_ptr I2C base address
 * @param [in] device_address I2C slave address
 * @param [in] size size of data to be read in bytes
 * @retval hpm_stat_t status_success if starting transmission without any error
 */
hpm_stat_t i2c_master_start_dma_read(I2C_Type *i2c_ptr, const uint16_t device_address, uint32_t size);

/**
 * @brief I2C master read data from certain slave device
 *
 * @details Read data from I2C device
 * @note size should not not greater than I2C_SOC_TRANSFER_COUNT_MAX
 *
 * @param [in] ptr I2C base address
 * @param [in] device_address I2C slave address
 * @param [out] buf pointer of the buffer to store data read from device
 * @param [in] size size of data to be read in bytes
 * @retval hpm_stat_t: status_success if reading is completed without any error
 */
hpm_stat_t i2c_master_read(I2C_Type *ptr,
                           const uint16_t device_address,
                           uint8_t *buf,
                           const uint32_t size);
/**
 * @brief I2C slave initialization
 *
 * @details Initialize I2C controller working at slave mode
 *
 * @param [in] ptr I2C base address
 * @param [in] src_clk_in_hz I2C controller source clock source frequency in Hz
 * @param [in] config I2C configuration structure
 * @param [in] slave_address I2C address to be used at slave mode
 * @retval hpm_stat_t: status_success if initialization is completed without any error
 */
hpm_stat_t i2c_init_slave(I2C_Type *ptr, uint32_t src_clk_in_hz,
                          i2c_config_t *config, const uint16_t slave_address);

/**
 * @brief I2C slave read data
 *
 * @details Read data at slave mode
 * @note size should not not greater than I2C_SOC_TRANSFER_COUNT_MAX
 *
 * @param [in] ptr I2C base address
 * @param [in] buf pointer of the buffer to store data read from device
 * @param [in] size size of data to be read in bytes
 * @retval hpm_stat_t: status_success if reading is completed without any error
 */
hpm_stat_t i2c_slave_read(I2C_Type *ptr, uint8_t *buf, const uint32_t size);

/**
 * @brief I2C slave write data
 *
 * @details Write data at slave mode.
 * @note size should not not greater than I2C_SOC_TRANSFER_COUNT_MAX
 *
 * @param [in] ptr I2C base address
 * @param [in] buf pointer of the buffer to store data sent from device
 * @param [in] size size of data to be sent in bytes
 * @retval hpm_stat_t status_success if writing is completed without any error
 */
hpm_stat_t i2c_slave_write(I2C_Type *ptr, uint8_t *buf, const uint32_t size);

/**
 * @brief reset I2C
 *
 * @param [in] ptr I2C base address
 */
void i2c_reset(I2C_Type *ptr);

/**
 * @brief Enable i2c DMA
 *
 * @param [in] ptr I2C base address
 */
static inline void i2c_dma_enable(I2C_Type *ptr)
{
    ptr->SETUP |= I2C_SETUP_DMAEN_MASK;
}

/**
 * @brief Disable i2c DMA
 *
 * @param [in] ptr I2C base address
 */
static inline void i2c_dma_disable(I2C_Type *ptr)
{
    ptr->SETUP &= ~I2C_SETUP_DMAEN_MASK;
}

/**
 * @brief I2C slave dma transfer data
 *
 * @note The direction of data transmission depends on Master setting
 *
 * @param [in] ptr I2C base address
 * @param [in] size size of data in bytes
 * @retval hpm_stat_t status_success if configuring transmission without any error
 */
hpm_stat_t i2c_slave_dma_transfer(I2C_Type *ptr,  const uint32_t size);

/**
 * @brief I2C write byte into FIFO
 *
 * @param ptr [in] ptr I2C base address
 * @param data [in] byte to ne sent
 */
static inline void i2c_write_byte(I2C_Type *ptr, uint8_t data)
{
    ptr->DATA = I2C_DATA_DATA_SET(data);
}

/**
 * @brief I2C read byte into FIFO
 *
 * @param ptr [in] ptr I2C base address
 * @return uint8_t read byte
 */
static inline uint8_t i2c_read_byte(I2C_Type *ptr)
{
    return (uint8_t)I2C_DATA_DATA_GET(ptr->DATA);
}

/**
 * @brief I2C get direction
 *
 * @note The same value has different meanings in master and slave modes
 *
 * @param ptr [in] ptr I2C base address
 * @return uint8_t direction value
 */
static inline uint8_t i2c_get_direction(I2C_Type *ptr)
{
    return (uint8_t)I2C_CTRL_DIR_GET(ptr->CTRL);
}

/**
 * @brief I2C master configure transfer setting
 *
 * @param i2c_ptr [in] ptr I2C base address
 * @param device_address [in] I2C slave address
 * @param size [in] size of data to be transferred in bytes
 * @param read [in] true for receive, false for transmit
 * @retval hpm_stat_t status_success if configuring transmission without any error
 */
hpm_stat_t i2c_master_configure_transfer(I2C_Type *i2c_ptr, const uint16_t device_address, uint32_t size, bool read);

/**
 * @brief sequential transmit in master I2C mode an amount of data in blocking
 *
 * @param i2c_ptr [in] ptr I2C base address
 * @param device_address [in] I2C slave address
 * @param [in] buf pointer of the buffer to store data sent from device
 * @param [in] size size of data to be sent in bytes
 * @param [in] opt I2c sequential transfer options
 * @retval hpm_stat_t status_success if transmit is completed without any error
 */
hpm_stat_t i2c_master_seq_transmit(I2C_Type *ptr, const uint16_t device_address,
                                   uint8_t *buf, const uint32_t size, i2c_seq_transfer_opt_t opt);

/**
 * @brief sequential receive in master I2C mode an amount of data in blocking
 *
 * @param i2c_ptr [in] ptr I2C base address
 * @param device_address [in] I2C slave address
 * @param [in] buf pointer of the buffer to store data sent from device
 * @param [in] size size of data to be sent in bytes
 * @param [in] opt I2c sequential transfer options
 * @retval hpm_stat_t status_success if receive is completed without any error
 */
hpm_stat_t i2c_master_seq_receive(I2C_Type *ptr, const uint16_t device_address,
                                  uint8_t *buf, const uint32_t size, i2c_seq_transfer_opt_t opt);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* HPM_I2C_DRV_H */

