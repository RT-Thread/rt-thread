/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-11-23     Bernard      Add extern "C"
 * 2020-06-13     armink       fix the 3 wires issue
 * 2022-09-01     liYony       fix api rt_spi_sendrecv16 about MSB and LSB bug
 */

#ifndef __DEV_SPI_H__
#define __DEV_SPI_H__

#include <stdlib.h>
#include <rtthread.h>
#include <drivers/dev_pin.h>
/**
 * @addtogroup  Drivers          RTTHREAD Driver
 * @defgroup    SPI              SPI
 *
 * @brief       SPI driver api
 *
 * <b>Example</b>
 * @code {.c}
 * #include <rtthread.h>
 * #include <rtdevice.h>
 *
 * #define W25Q_SPI_DEVICE_NAME     "qspi10"
 *
 * static void spi_w25q_sample(int argc, char *argv[])
 * {
 *     struct rt_spi_device *spi_dev_w25q;
 *     char name[RT_NAME_MAX];
 *     rt_uint8_t w25x_read_id = 0x90;
 *     rt_uint8_t id[5] = {0};
 *
 *     if (argc == 2)
 *     {
 *         rt_strncpy(name, argv[1], RT_NAME_MAX);
 *     }
 *     else
 *     {
 *         rt_strncpy(name, W25Q_SPI_DEVICE_NAME, RT_NAME_MAX);
 *     }
 *
 *     // 查找 spi 设备获取设备句柄
 *     spi_dev_w25q = (struct rt_spi_device *)rt_device_find(name);
 *     if (!spi_dev_w25q)
 *     {
 *         rt_kprintf("spi sample run failed! can't find %s device!\n", name);
 *     }
 *     else
 *     {
 *         // 方式1：使用 rt_spi_send_then_recv()发送命令读取ID
 *         rt_spi_send_then_recv(spi_dev_w25q, &w25x_read_id, 1, id, 5);
 *         rt_kprintf("use rt_spi_send_then_recv() read w25q ID is:%x%x\n", id[3], id[4]);
 *
 *         // 方式2：使用 rt_spi_transfer_message()发送命令读取ID
 *         struct rt_spi_message msg1, msg2;
 *
 *         msg1.send_buf   = &w25x_read_id;
 *         msg1.recv_buf   = RT_NULL;
 *         msg1.length     = 1;
 *         msg1.cs_take    = 1;
 *         msg1.cs_release = 0;
 *         msg1.next       = &msg2;
 *
 *         msg2.send_buf   = RT_NULL;
 *         msg2.recv_buf   = id;
 *         msg2.length     = 5;
 *         msg2.cs_take    = 0;
 *         msg2.cs_release = 1;
 *         msg2.next       = RT_NULL;
 *
 *         rt_spi_transfer_message(spi_dev_w25q, &msg1);
 *         rt_kprintf("use rt_spi_transfer_message() read w25q ID is:%x%x\n", id[3], id[4]);
 *
 *     }
 * }
 * // 导出到 msh 命令列表中
 * MSH_CMD_EXPORT(spi_w25q_sample, spi w25q sample);
 * @endcode
 *
 * @ingroup     Drivers
 */

/*!
 * @addtogroup SPI
 * @{
 */
#ifdef __cplusplus
extern "C"{
#endif

/**
 * At CPOL=0 the base value of the clock is zero
 *  - For CPHA=0, data are captured on the clock's rising edge (low->high transition)
 *    and data are propagated on a falling edge (high->low clock transition).
 *  - For CPHA=1, data are captured on the clock's falling edge and data are
 *    propagated on a rising edge.
 * At CPOL=1 the base value of the clock is one (inversion of CPOL=0)
 *  - For CPHA=0, data are captured on clock's falling edge and data are propagated
 *    on a rising edge.
 *  - For CPHA=1, data are captured on clock's rising edge and data are propagated
 *    on a falling edge.
 */
#define RT_SPI_CPHA     (1<<0)                             /*!< bit[0]:CPHA, clock phase */
#define RT_SPI_CPOL     (1<<1)                             /*!< bit[1]:CPOL, clock polarity */

#define RT_SPI_LSB      (0<<2)                             /*!< bit[2]: 0-LSB */
#define RT_SPI_MSB      (1<<2)                             /*!< bit[2]: 1-MSB */

#define RT_SPI_MASTER   (0<<3)                             /*!< SPI master device */
#define RT_SPI_SLAVE    (1<<3)                             /*!< SPI slave device */

#define RT_SPI_CS_HIGH  (1<<4)                             /*!< Chipselect active high */
#define RT_SPI_NO_CS    (1<<5)                             /*!< No chipselect */
#define RT_SPI_3WIRE    (1<<6)                             /*!< SI/SO pin shared */
#define RT_SPI_READY    (1<<7)                             /*!< Slave pulls low to pause */

#define RT_SPI_MODE_MASK    (RT_SPI_CPHA | RT_SPI_CPOL | RT_SPI_MSB | RT_SPI_SLAVE | RT_SPI_CS_HIGH | RT_SPI_NO_CS | RT_SPI_3WIRE | RT_SPI_READY)

#define RT_SPI_MODE_0       (0 | 0)                        /*!< CPOL = 0, CPHA = 0 */
#define RT_SPI_MODE_1       (0 | RT_SPI_CPHA)              /*!< CPOL = 0, CPHA = 1 */
#define RT_SPI_MODE_2       (RT_SPI_CPOL | 0)              /*!< CPOL = 1, CPHA = 0 */
#define RT_SPI_MODE_3       (RT_SPI_CPOL | RT_SPI_CPHA)    /*!< CPOL = 1, CPHA = 1 */

#define RT_SPI_BUS_MODE_SPI         (1<<0)
#define RT_SPI_BUS_MODE_QSPI        (1<<1)

/**
 * @brief SPI message structure
 */
struct rt_spi_message
{
    const void *send_buf;
    void *recv_buf;
    rt_size_t length;
    struct rt_spi_message *next;

    unsigned cs_take    : 1;
    unsigned cs_release : 1;
};

/**
 * @brief SPI configuration structure
 */
struct rt_spi_configuration
{
    rt_uint8_t mode;
    rt_uint8_t data_width;
    rt_uint16_t reserved;

    rt_uint32_t max_hz;
};

struct rt_spi_ops;

/**
 * @brief SPI bus structure
 */
struct rt_spi_bus
{
    struct rt_device parent;
    rt_uint8_t mode;
    const struct rt_spi_ops *ops;

    struct rt_mutex lock;
    struct rt_spi_device *owner;
};

/**
 * @brief SPI operators
 */
struct rt_spi_ops
{
    rt_err_t (*configure)(struct rt_spi_device *device, struct rt_spi_configuration *configuration);
    rt_ssize_t (*xfer)(struct rt_spi_device *device, struct rt_spi_message *message);
};

/**
 * @brief SPI Virtual BUS, one device must connected to a virtual BUS
 */
struct rt_spi_device
{
    struct rt_device parent;
    struct rt_spi_bus *bus;

    struct rt_spi_configuration config;
    rt_base_t cs_pin;
    void   *user_data;
};

/**
 * @brief QSPI message structure
 */
struct rt_qspi_message
{
    struct rt_spi_message parent;

    /* instruction stage */
    struct
    {
        rt_uint8_t content;
        rt_uint8_t qspi_lines;
    } instruction;

    /* address and alternate_bytes stage */
    struct
    {
        rt_uint32_t content;
        rt_uint8_t size;
        rt_uint8_t qspi_lines;
    } address, alternate_bytes;

    /* dummy_cycles stage */
    rt_uint32_t dummy_cycles;

    /* number of lines in qspi data stage, the other configuration items are in parent */
    rt_uint8_t qspi_data_lines;
};

/**
 * @brief QSPI configuration structure
 */
struct rt_qspi_configuration
{
    struct rt_spi_configuration parent;
    /* The size of medium */
    rt_uint32_t medium_size;
    /* double data rate mode */
    rt_uint8_t ddr_mode;
    /* the data lines max width which QSPI bus supported, such as 1, 2, 4 */
    rt_uint8_t qspi_dl_width ;
};

/**
 * @brief QSPI operators
 */
struct rt_qspi_device
{
    struct rt_spi_device parent;

    struct rt_qspi_configuration config;

    void (*enter_qspi_mode)(struct rt_qspi_device *device);

    void (*exit_qspi_mode)(struct rt_qspi_device *device);
};

#define SPI_DEVICE(dev) ((struct rt_spi_device *)(dev))

/**
 * @brief register a SPI bus
 *
 * @param bus the SPI bus
 * @param name the name of SPI bus
 * @param ops the operations of SPI bus
 *
 * @return rt_err_t error code
 */
rt_err_t rt_spi_bus_register(struct rt_spi_bus       *bus,
                             const char              *name,
                             const struct rt_spi_ops *ops);


/**
 * @brief attach a device on SPI bus
 *
 * @param device the SPI device
 * @param name the name of SPI device
 * @param bus_name the name of SPI bus
 * @param user_data the user data of SPI device
 *
 * @return rt_err_t error code
 */
rt_err_t rt_spi_bus_attach_device(struct rt_spi_device *device,
                                  const char           *name,
                                  const char           *bus_name,
                                  void                 *user_data);


/**
 * @brief attach a device on SPI bus with CS pin
 *
 * @param device the SPI device
 * @param name the name of SPI device
 * @param bus_name the name of SPI bus
 * @param cs_pin the CS pin of SPI device
 * @param user_data the user data of SPI device
 *
 * @return rt_err_t error code
 */
rt_err_t rt_spi_bus_attach_device_cspin(struct rt_spi_device *device,
                                        const char           *name,
                                        const char           *bus_name,
                                        rt_base_t             cs_pin,
                                        void                 *user_data);

/**
 * @brief  Reconfigure the SPI bus for the specified device.
 *
 * @param  device: Pointer to the SPI device attached to the SPI bus.
 * @retval RT_EOK if the SPI device was successfully released and the bus was configured.
 *         RT_EBUSY if the SPI bus is currently in use; the new configuration will take effect once the device releases the bus.
 *         Other return values indicate failure to configure the SPI bus due to various reasons.
 * @note   If the configuration of the SPI device has been updated and requires bus re-initialization,
 *         call this function directly. This function will reconfigure the SPI bus for the specified device.
 *         If this is the first time to initialize the SPI device, please call rt_spi_configure or rt_qspi_configure.
 *         This function is used to reconfigure the SPI bus when the SPI device is already in use.
 *         For further details, refer to:
 *         https://github.com/RT-Thread/rt-thread/pull/8528
 */
rt_err_t rt_spi_bus_configure(struct rt_spi_device *device);

/**
 * @brief This function takes SPI bus.
 *
 * @param device the SPI device attached to SPI bus
 *
 * @return RT_EOK on taken SPI bus successfully. others on taken SPI bus failed.
 */
rt_err_t rt_spi_take_bus(struct rt_spi_device *device);

/**
 * @brief This function releases SPI bus.
 *
 * @param device the SPI device attached to SPI bus
 *
 * @return RT_EOK on release SPI bus successfully.
 */
rt_err_t rt_spi_release_bus(struct rt_spi_device *device);

/**
 * @brief This function take SPI device (takes CS of SPI device).
 *
 * @param device the SPI device attached to SPI bus
 *
 * @return RT_EOK on release SPI bus successfully. others on taken SPI bus failed.
 */
rt_err_t rt_spi_take(struct rt_spi_device *device);

/**
 * @brief This function releases SPI device (releases CS of SPI device).
 *
 * @param device the SPI device attached to SPI bus
 *
 * @return RT_EOK on release SPI device successfully.
 */
rt_err_t rt_spi_release(struct rt_spi_device *device);

/**
 * @brief  This function can set configuration on SPI device.
 *
 * @param  device: the SPI device attached to SPI bus
 * @param  cfg: the configuration pointer.
 *
 * @retval RT_EOK on release SPI device successfully.
 *         RT_EBUSY is not an error condition and the configuration will take effect once the device has the bus
 *         others on taken SPI bus failed.
 */
rt_err_t rt_spi_configure(struct rt_spi_device        *device,
                          struct rt_spi_configuration *cfg);


/**
 * @brief This function can send data then receive data from SPI device.
 *
 * @param device the SPI device attached to SPI bus
 * @param send_buf the buffer to be transmitted to SPI device.
 * @param send_length the number of data to be transmitted.
 * @param recv_buf the buffer to be recivied from SPI device.
 * @param recv_length the data to be recivied.
 *
 * @return rt_err_t error code
 */
rt_err_t rt_spi_send_then_recv(struct rt_spi_device *device,
                               const void           *send_buf,
                               rt_size_t             send_length,
                               void                 *recv_buf,
                               rt_size_t             recv_length);

/**
 * @brief This function can send data then send data from SPI device.
 *
 * @param device the SPI device attached to SPI bus
 * @param send_buf1 the buffer to be transmitted to SPI device.
 * @param send_length1 the number of data to be transmitted.
 * @param send_buf2 the buffer to be transmitted to SPI device.
 * @param send_length2 the number of data to be transmitted.
 *
 * @return the status of transmit.
 */
rt_err_t rt_spi_send_then_send(struct rt_spi_device *device,
                               const void           *send_buf1,
                               rt_size_t             send_length1,
                               const void           *send_buf2,
                               rt_size_t             send_length2);

/**
 * @brief This function transmits data to SPI device.
 *
 * @param device the SPI device attached to SPI bus
 * @param send_buf the buffer to be transmitted to SPI device.
 * @param recv_buf the buffer to save received data from SPI device.
 * @param length the length of transmitted data.
 *
 * @return the actual length of transmitted.
 */
rt_ssize_t rt_spi_transfer(struct rt_spi_device *device,
                           const void           *send_buf,
                           void                 *recv_buf,
                           rt_size_t             length);

/**
 * @brief The SPI device transmits 8 bytes of data
 *
 * @param device the SPI device attached to SPI bus
 * @param senddata send data buffer
 * @param recvdata receive data buffer
 *
 * @return rt_err_t error code
 */
rt_err_t rt_spi_sendrecv8(struct rt_spi_device *device,
                          rt_uint8_t            senddata,
                          rt_uint8_t           *recvdata);

/**
 * @brief The SPI device transmits 16 bytes of data
 *
 * @param device the SPI device attached to SPI bus
 * @param senddata send data buffer
 * @param recvdata receive data buffer
 *
 * @return rt_err_t error code
 */
rt_err_t rt_spi_sendrecv16(struct rt_spi_device *device,
                           rt_uint16_t           senddata,
                           rt_uint16_t          *recvdata);

/**
 * @brief This function transfers a message list to the SPI device.
 *
 * @param device the SPI device attached to SPI bus
 * @param message the message list to be transmitted to SPI device
 *
 * @return RT_NULL if transmits message list successfully,
 *         SPI message which be transmitted failed.
 */
struct rt_spi_message *rt_spi_transfer_message(struct rt_spi_device  *device,
                                               struct rt_spi_message *message);

/**
 * @brief This function receives data from SPI device.
 *
 * @param device the SPI device attached to SPI bus
 * @param recv_buf the buffer to be recivied from SPI device.
 * @param length the data to be recivied.
 *
 * @return the actual length of received.
*/
rt_inline rt_size_t rt_spi_recv(struct rt_spi_device *device,
                                void                 *recv_buf,
                                rt_size_t             length)
{
    return rt_spi_transfer(device, RT_NULL, recv_buf, length);
}

/**
 * @brief This function sends data to SPI device.
 *
 * @param device the SPI device attached to SPI bus
 * @param send_buf the buffer to be transmitted to SPI device.
 * @param length the number of data to be transmitted.
 *
 * @return the actual length of send.
 */
rt_inline rt_size_t rt_spi_send(struct rt_spi_device *device,
                                const void           *send_buf,
                                rt_size_t             length)
{
    return rt_spi_transfer(device, send_buf, RT_NULL, length);
}

/**
 * @brief This function appends a message to the SPI message list.
 *
 * @param list the SPI message list header.
 * @param message the message pointer to be appended to the message list.
 */
rt_inline void rt_spi_message_append(struct rt_spi_message *list,
                                     struct rt_spi_message *message)
{
    RT_ASSERT(list != RT_NULL);
    if (message == RT_NULL)
        return; /* not append */

    while (list->next != RT_NULL)
    {
        list = list->next;
    }

    list->next = message;
    message->next = RT_NULL;
}

/**
 * @brief This function can set configuration on QSPI device.
 *
 * @param device the QSPI device attached to QSPI bus.
 * @param cfg the configuration pointer.
 *
 * @return the actual length of transmitted.
 */
rt_err_t rt_qspi_configure(struct rt_qspi_device *device, struct rt_qspi_configuration *cfg);

/**
 * @brief This function can register a SPI bus for QSPI mode.
 *
 * @param bus the SPI bus for QSPI mode.
 * @param name The name of the spi bus.
 * @param ops the SPI bus instance to be registered.
 *
 * @return the actual length of transmitted.
 */
rt_err_t rt_qspi_bus_register(struct rt_spi_bus *bus, const char *name, const struct rt_spi_ops *ops);

/**
 * @brief This function transmits data to QSPI device.
 *
 * @param device the QSPI device attached to QSPI bus.
 * @param message the message pointer.
 *
 * @return the actual length of transmitted.
 */
rt_size_t rt_qspi_transfer_message(struct rt_qspi_device  *device, struct rt_qspi_message *message);

/**
 * @brief This function can send data then receive data from QSPI device
 *
 * @param device the QSPI device attached to QSPI bus.
 * @param send_buf the buffer to be transmitted to QSPI device.
 * @param send_length the number of data to be transmitted.
 * @param recv_buf the buffer to be recivied from QSPI device.
 * @param recv_length the data to be recivied.
 *
 * @return the status of transmit.
 */
rt_err_t rt_qspi_send_then_recv(struct rt_qspi_device *device, const void *send_buf, rt_size_t send_length,void *recv_buf, rt_size_t recv_length);

/**
 * @brief This function can send data to QSPI device
 *
 * @param device the QSPI device attached to QSPI bus.
 * @param send_buf the buffer to be transmitted to QSPI device.
 * @param send_length the number of data to be transmitted.
 *
 * @return the status of transmit.
 */
rt_err_t rt_qspi_send(struct rt_qspi_device *device, const void *send_buf, rt_size_t length);

#ifdef __cplusplus
}
#endif

/*! @}*/

#endif
