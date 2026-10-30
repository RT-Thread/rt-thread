/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-31     RT-Thread    first implementation
 * 2026-09-23     CYFS         adapt OSPI0 QSPI flash with MDMA cache and buffer protection
 */

#include "board.h"
#include "drv_gpio.h"
#include "drv_ospi.h"

#ifdef BSP_USING_OSPI0

#include "gd32h77x_78x_ospi.h"
#include "gd32h77x_78x_ospim.h"
#ifdef BSP_OSPI0_USING_MDMA
#include "gd32h77x_78x_mdma.h"
#endif

#define LOG_TAG              "drv.ospi"
#include <drv_log.h>

#define GD32_OSPI_FIFO_CHUNK_SIZE       16U
#define GD32_OSPI_FIFO_WORD_SIZE        4U

#ifdef BSP_OSPI0_USING_MDMA
#define GD32_OSPI_MDMA_CHANNEL          ((mdma_channel_enum)BSP_OSPI0_MDMA_CHANNEL)
#define GD32_OSPI_MDMA_BUFFER_SIZE      16U
#define GD32_OSPI_MDMA_MIN_SIZE         512U
#define GD32_OSPI_MDMA_MAX_SIZE         0x10000U
#define GD32_OSPI_MDMA_TIMEOUT_MS       1000U
#ifdef RT_USING_CACHE
#define GD32_OSPI_MDMA_ALIGNMENT        32U
#else
#define GD32_OSPI_MDMA_ALIGNMENT        GD32_OSPI_MDMA_BUFFER_SIZE
#endif
#define GD32_OSPI_ITCM_START            0x00000000U
#define GD32_OSPI_ITCM_END              0x00020000U
#define GD32_OSPI_DTCM_START            0x20000000U
#define GD32_OSPI_DTCM_END              0x20040000U
#define GD32_OSPI_AHB_SRAM_START        0x30000000U
#define GD32_OSPI_AHB_SRAM_END          0x40000000U
#endif

struct gd32_ospi_pin
{
    const char *name;
    const char *alternate;
};

struct gd32_ospi_bus
{
    struct rt_spi_bus parent;
    ospi_parameter_struct init;
};

static struct gd32_ospi_bus ospi0_bus;

#ifdef BSP_OSPI0_USING_MDMA
#ifdef RT_USING_CONSOLE
static rt_bool_t ospi0_mdma_reported;
#endif

static rt_bool_t gd32_ospi_mdma_can_transfer(const void *data, rt_size_t length)
{
    return data != RT_NULL &&
           ((rt_ubase_t)data & (GD32_OSPI_MDMA_ALIGNMENT - 1U)) == 0U &&
           length >= GD32_OSPI_MDMA_MIN_SIZE &&
           length <= GD32_OSPI_MDMA_MAX_SIZE &&
           (length & (GD32_OSPI_MDMA_ALIGNMENT - 1U)) == 0U;
}

#ifdef RT_USING_CACHE
static void gd32_ospi_mdma_cache_ops(int ops, void *data, rt_size_t length)
{
    rt_base_t level;

    /* Keep cache maintenance atomic with respect to interrupt stack accesses.
     * DMA buffers must own whole cache lines to preserve neighbouring data. */
    level = rt_hw_interrupt_disable();
    rt_hw_cpu_dcache_ops(ops, data, (int)length);
    rt_hw_interrupt_enable(level);
}
#endif

static uint32_t gd32_ospi_mdma_memory_bus(const void *data)
{
    rt_ubase_t address = (rt_ubase_t)data;

    if ((address >= GD32_OSPI_ITCM_START && address < GD32_OSPI_ITCM_END) ||
        (address >= GD32_OSPI_DTCM_START && address < GD32_OSPI_DTCM_END) ||
        (address >= GD32_OSPI_AHB_SRAM_START && address < GD32_OSPI_AHB_SRAM_END))
    {
        return MDMA_SOURCE_AHB_TCM;
    }

    return MDMA_SOURCE_AXI;
}

static void gd32_ospi_mdma_report(const char *operation, rt_size_t length)
{
#ifdef RT_USING_CONSOLE
    if (!ospi0_mdma_reported && rt_console_get_device() != RT_NULL)
    {
        ospi0_mdma_reported = RT_TRUE;
        LOG_I("ospi0 MDMA channel %d active (%s, %u bytes)",
              BSP_OSPI0_MDMA_CHANNEL, operation, (rt_uint32_t)length);
    }
#else
    RT_UNUSED(operation);
    RT_UNUSED(length);
#endif
}

static void gd32_ospi_mdma_configure(void *data, rt_size_t length, rt_bool_t receive)
{
    mdma_parameter_struct mdma_init_struct;
    uint32_t data_bus;

    data_bus = gd32_ospi_mdma_memory_bus(data);
    mdma_channel_deinit(GD32_OSPI_MDMA_CHANNEL);
    mdma_para_struct_init(&mdma_init_struct);
    mdma_init_struct.request = MDMA_REQUEST_OSPI0_FT;
    mdma_init_struct.trans_trig_mode = MDMA_BUFFER_TRANSFER;
    mdma_init_struct.priority = MDMA_PRIORITY_ULTRA_HIGH;
    mdma_init_struct.source_data_size = MDMA_SOURCE_DATASIZE_32BIT;
    mdma_init_struct.dest_data_size = MDMA_DESTINATION_DATASIZE_32BIT;
    mdma_init_struct.buff_trans_len = GD32_OSPI_MDMA_BUFFER_SIZE - 1U;
    mdma_init_struct.tbytes_num_in_block = length;

    if (receive)
    {
        mdma_init_struct.source_inc = MDMA_SOURCE_INCREASE_DISABLE;
        mdma_init_struct.dest_inc = MDMA_DESTINATION_INCREASE_32BIT;
        mdma_init_struct.source_burst = MDMA_SOURCE_BURST_SINGLE;
        mdma_init_struct.dest_burst = MDMA_DESTINATION_BURST_4BEATS;
        mdma_init_struct.source_addr = (uint32_t)&OSPI_DATA(OSPI0);
        mdma_init_struct.destination_addr = (uint32_t)data;
        mdma_init_struct.source_bus = MDMA_SOURCE_AXI;
        mdma_init_struct.destination_bus = data_bus == MDMA_SOURCE_AHB_TCM ?
                                           MDMA_DESTINATION_AHB_TCM :
                                           MDMA_DESTINATION_AXI;
    }
    else
    {
        mdma_init_struct.source_inc = MDMA_SOURCE_INCREASE_32BIT;
        mdma_init_struct.dest_inc = MDMA_DESTINATION_INCREASE_DISABLE;
        mdma_init_struct.source_burst = MDMA_SOURCE_BURST_4BEATS;
        mdma_init_struct.dest_burst = MDMA_DESTINATION_BURST_SINGLE;
        mdma_init_struct.source_addr = (uint32_t)data;
        mdma_init_struct.destination_addr = (uint32_t)&OSPI_DATA(OSPI0);
        mdma_init_struct.source_bus = data_bus;
        mdma_init_struct.destination_bus = MDMA_DESTINATION_AXI;
    }

    mdma_init(GD32_OSPI_MDMA_CHANNEL, &mdma_init_struct);
}

static rt_bool_t gd32_ospi_mdma_has_error(void)
{
    return SET == mdma_flag_get(GD32_OSPI_MDMA_CHANNEL, MDMA_FLAG_ERR) ||
           SET == mdma_flag_get(GD32_OSPI_MDMA_CHANNEL, MDMA_FLAG_LDTERR) ||
           SET == mdma_flag_get(GD32_OSPI_MDMA_CHANNEL, MDMA_FLAG_MDTERR) ||
           SET == mdma_flag_get(GD32_OSPI_MDMA_CHANNEL, MDMA_FLAG_ASERR) ||
           SET == mdma_flag_get(GD32_OSPI_MDMA_CHANNEL, MDMA_FLAG_BZERR);
}

static rt_err_t gd32_ospi_mdma_wait(void)
{
    rt_tick_t start;
    rt_tick_t timeout;
    rt_err_t result = RT_EOK;
    uint32_t ospi_status;

    start = rt_tick_get();
    timeout = rt_tick_from_millisecond(GD32_OSPI_MDMA_TIMEOUT_MS);

    while (RESET == mdma_flag_get(GD32_OSPI_MDMA_CHANNEL, MDMA_FLAG_CHTCF))
    {
        if (gd32_ospi_mdma_has_error() ||
            RESET != (OSPI_STAT(OSPI0) & OSPI_FLAG_TERR))
        {
            result = -RT_EIO;
            break;
        }
        if ((rt_tick_get() - start) >= timeout)
        {
            result = -RT_ETIMEOUT;
            break;
        }
    }

    while (result == RT_EOK && RESET == (OSPI_STAT(OSPI0) & OSPI_FLAG_TC))
    {
        if (RESET != (OSPI_STAT(OSPI0) & OSPI_FLAG_TERR))
        {
            result = -RT_EIO;
            break;
        }
        if ((rt_tick_get() - start) >= timeout)
        {
            result = -RT_ETIMEOUT;
            break;
        }
    }

    ospi_status = OSPI_STAT(OSPI0);
    ospi_mdma_disable(OSPI0);
    mdma_channel_disable(GD32_OSPI_MDMA_CHANNEL);

    if (result != RT_EOK && RESET != (ospi_status & OSPI_FLAG_BUSY))
    {
        OSPI_CTL(OSPI0) |= OSPI_CTL_ABORT;
        start = rt_tick_get();
        while (RESET != (OSPI_STAT(OSPI0) & OSPI_FLAG_BUSY) &&
               (rt_tick_get() - start) < timeout)
        {
        }
    }

    OSPI_STATC(OSPI0) = OSPI_STATC_TCC | OSPI_STATC_TERRC;
    if (result != RT_EOK)
    {
        LOG_E("MDMA failed: %d, OSPI: %08x, MDMA: %08x/%08x, addr: %08x",
              result, ospi_status, MDMA_CHXSTAT0(GD32_OSPI_MDMA_CHANNEL),
              MDMA_CHXSTAT1(GD32_OSPI_MDMA_CHANNEL),
              mdma_transfer_error_address_get(GD32_OSPI_MDMA_CHANNEL));
    }
    mdma_channel_deinit(GD32_OSPI_MDMA_CHANNEL);

    return result;
}

static rt_err_t gd32_ospi_mdma_transmit(const rt_uint8_t *data, rt_size_t length)
{
    gd32_ospi_mdma_configure((void *)data, length, RT_FALSE);
#ifdef RT_USING_CACHE
    gd32_ospi_mdma_cache_ops(RT_HW_CACHE_FLUSH, (void *)data, length);
#endif

    mdma_channel_enable(GD32_OSPI_MDMA_CHANNEL);
    OSPI_CTL(OSPI0) = (OSPI_CTL(OSPI0) & ~OSPI_CTL_FMOD) | OSPI_INDIRECT_WRITE;
    ospi_mdma_enable(OSPI0);
    gd32_ospi_mdma_report("write", length);

    return gd32_ospi_mdma_wait();
}

static rt_err_t gd32_ospi_mdma_receive(const ospi_parameter_struct *configuration,
                                       rt_uint8_t *data,
                                       rt_size_t length)
{
    rt_err_t result;
    rt_uint32_t address;
    rt_uint32_t instruction;

    address = OSPI_ADDR(OSPI0);
    instruction = OSPI_INS(OSPI0);
    gd32_ospi_mdma_configure(data, length, RT_TRUE);
#ifdef RT_USING_CACHE
    gd32_ospi_mdma_cache_ops(RT_HW_CACHE_FLUSH | RT_HW_CACHE_INVALIDATE,
                            data, length);
#endif

    mdma_channel_enable(GD32_OSPI_MDMA_CHANNEL);
    OSPI_CTL(OSPI0) = (OSPI_CTL(OSPI0) & ~OSPI_CTL_FMOD) | OSPI_INDIRECT_READ;
    ospi_mdma_enable(OSPI0);
    gd32_ospi_mdma_report("read", length);

    if (configuration->memory_type == OSPI_HYPERBUS_MEMORY_MODE)
    {
        OSPI_ADDR(OSPI0) = address;
    }
    else if ((OSPI_TCFG(OSPI0) & OSPI_TCFG_ADDRMOD) != OSPI_ADDRESS_NONE)
    {
        OSPI_ADDR(OSPI0) = address;
    }
    else
    {
        OSPI_INS(OSPI0) = instruction;
    }

    result = gd32_ospi_mdma_wait();
#ifdef RT_USING_CACHE
    gd32_ospi_mdma_cache_ops(RT_HW_CACHE_INVALIDATE, data, length);
#endif

    return result;
}
#endif /* BSP_OSPI0_USING_MDMA */

static rt_err_t gd32_ospi_transmit(const rt_uint8_t *data, rt_size_t length)
{
    rt_size_t index;

#ifdef BSP_OSPI0_USING_MDMA
    if (gd32_ospi_mdma_can_transfer(data, length))
    {
        return gd32_ospi_mdma_transmit(data, length);
    }
#endif

    OSPI_CTL(OSPI0) = (OSPI_CTL(OSPI0) & ~OSPI_CTL_FMOD) | OSPI_INDIRECT_WRITE;

    while (length >= GD32_OSPI_FIFO_CHUNK_SIZE)
    {
        while (RESET == (OSPI_STAT(OSPI0) & OSPI_FLAG_FT))
        {
        }

        for (index = 0; index < GD32_OSPI_FIFO_CHUNK_SIZE; index += GD32_OSPI_FIFO_WORD_SIZE)
        {
            OSPI_DATA(OSPI0) = (rt_uint32_t)data[index] |
                               ((rt_uint32_t)data[index + 1U] << 8) |
                               ((rt_uint32_t)data[index + 2U] << 16) |
                               ((rt_uint32_t)data[index + 3U] << 24);
        }
        data += GD32_OSPI_FIFO_CHUNK_SIZE;
        length -= GD32_OSPI_FIFO_CHUNK_SIZE;
    }

    if (length > 0U)
    {
        while (RESET == (OSPI_STAT(OSPI0) & OSPI_FLAG_FT))
        {
        }

        while (length >= GD32_OSPI_FIFO_WORD_SIZE)
        {
            OSPI_DATA(OSPI0) = (rt_uint32_t)data[0] |
                               ((rt_uint32_t)data[1] << 8) |
                               ((rt_uint32_t)data[2] << 16) |
                               ((rt_uint32_t)data[3] << 24);
            data += GD32_OSPI_FIFO_WORD_SIZE;
            length -= GD32_OSPI_FIFO_WORD_SIZE;
        }
        while (length > 0U)
        {
            *((__IO rt_uint8_t *)&OSPI_DATA(OSPI0)) = *data++;
            length--;
        }
    }

    while (RESET == (OSPI_STAT(OSPI0) & OSPI_FLAG_TC))
    {
    }
    OSPI_STATC(OSPI0) = OSPI_STATC_TCC;

    return RT_EOK;
}

static rt_err_t gd32_ospi_receive(const ospi_parameter_struct *configuration,
                                  rt_uint8_t *data,
                                  rt_size_t length)
{
    rt_size_t index;
    rt_uint32_t address;
    rt_uint32_t instruction;
    rt_uint32_t word;

#ifdef BSP_OSPI0_USING_MDMA
    if (gd32_ospi_mdma_can_transfer(data, length))
    {
        return gd32_ospi_mdma_receive(configuration, data, length);
    }
#endif

    address = OSPI_ADDR(OSPI0);
    instruction = OSPI_INS(OSPI0);
    OSPI_CTL(OSPI0) = (OSPI_CTL(OSPI0) & ~OSPI_CTL_FMOD) | OSPI_INDIRECT_READ;

    if (configuration->memory_type == OSPI_HYPERBUS_MEMORY_MODE)
    {
        OSPI_ADDR(OSPI0) = address;
    }
    else if ((OSPI_TCFG(OSPI0) & OSPI_TCFG_ADDRMOD) != OSPI_ADDRESS_NONE)
    {
        OSPI_ADDR(OSPI0) = address;
    }
    else
    {
        OSPI_INS(OSPI0) = instruction;
    }

    while (length >= GD32_OSPI_FIFO_CHUNK_SIZE)
    {
        while (RESET == (OSPI_STAT(OSPI0) & OSPI_FLAG_FT))
        {
        }

        for (index = 0; index < GD32_OSPI_FIFO_CHUNK_SIZE; index += GD32_OSPI_FIFO_WORD_SIZE)
        {
            word = OSPI_DATA(OSPI0);
            data[index] = (rt_uint8_t)word;
            data[index + 1U] = (rt_uint8_t)(word >> 8);
            data[index + 2U] = (rt_uint8_t)(word >> 16);
            data[index + 3U] = (rt_uint8_t)(word >> 24);
        }
        data += GD32_OSPI_FIFO_CHUNK_SIZE;
        length -= GD32_OSPI_FIFO_CHUNK_SIZE;
    }

    if (length > 0U)
    {
        while (RESET == (OSPI_STAT(OSPI0) & OSPI_FLAG_TC))
        {
        }

        while (length >= GD32_OSPI_FIFO_WORD_SIZE)
        {
            word = OSPI_DATA(OSPI0);
            data[0] = (rt_uint8_t)word;
            data[1] = (rt_uint8_t)(word >> 8);
            data[2] = (rt_uint8_t)(word >> 16);
            data[3] = (rt_uint8_t)(word >> 24);
            data += GD32_OSPI_FIFO_WORD_SIZE;
            length -= GD32_OSPI_FIFO_WORD_SIZE;
        }
        while (length > 0U)
        {
            *data++ = *((__IO rt_uint8_t *)&OSPI_DATA(OSPI0));
            length--;
        }
    }
    else
    {
        while (RESET == (OSPI_STAT(OSPI0) & OSPI_FLAG_TC))
        {
        }
    }

    OSPI_STATC(OSPI0) = OSPI_STATC_TCC;

    return RT_EOK;
}

static const struct gd32_ospi_pin ospi0_pins[] =
{
    /* OSPI0 is wired to the board's four-line QSPI flash. */
    {BSP_OSPI0_CS_PIN,  BSP_OSPI0_CS_AFIO},
    {BSP_OSPI0_CLK_PIN, BSP_OSPI0_CLK_AFIO},
    {BSP_OSPI0_D0_PIN,  BSP_OSPI0_D0_AFIO},
    {BSP_OSPI0_D1_PIN,  BSP_OSPI0_D1_AFIO},
    {BSP_OSPI0_D2_PIN,  BSP_OSPI0_D2_AFIO},
    {BSP_OSPI0_D3_PIN,  BSP_OSPI0_D3_AFIO},
};

static rt_err_t gd32_ospi_gpio_init(void)
{
    rt_size_t index;

    for (index = 0; index < sizeof(ospi0_pins) / sizeof(ospi0_pins[0]); index++)
    {
        uint32_t port;
        uint32_t pin;
        uint32_t alternate;
        rcu_periph_enum clock;

        if (get_pin_config(ospi0_pins[index].name, &port, &pin, &clock) != RT_EOK)
        {
            LOG_E("invalid OSPI0 pin: %s", ospi0_pins[index].name);
            return -RT_EINVAL;
        }

        if (pin_alternate_config(ospi0_pins[index].alternate, &alternate) != RT_EOK)
        {
            LOG_E("invalid OSPI0 alternate function: %s", ospi0_pins[index].alternate);
            return -RT_EINVAL;
        }

        rcu_periph_clock_enable(clock);
        gpio_af_set(port, alternate, pin);
        gpio_mode_set(port, GPIO_MODE_AF, GPIO_PUPD_NONE, pin);
        gpio_output_options_set(port, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, pin);
    }

    return RT_EOK;
}

static rt_err_t gd32_ospi_hardware_init(void)
{
    rt_err_t result;

    rcu_ospi_clock_config(RCU_OSPI_AHB);
    rcu_periph_clock_enable(RCU_OSPIM);
    rcu_periph_clock_enable(RCU_OSPI0);
#ifdef BSP_OSPI0_USING_MDMA
    rcu_periph_clock_enable(RCU_MDMA);
#endif

    ospim_deinit();
    ospi_deinit(OSPI0);

    result = gd32_ospi_gpio_init();
    if (result != RT_EOK)
    {
        return result;
    }

    ospim_port_sck_config(OSPIM_PORT0, OSPIM_PORT_SCK_ENABLE);
    ospim_port_dqs_config(OSPIM_PORT0, OSPIM_PORT_DQS_DISABLE);
    ospim_port_csn_config(OSPIM_PORT0, OSPIM_PORT_CSN_ENABLE);
    ospim_port_io3_0_config(OSPIM_PORT0, OSPIM_IO_LOW_ENABLE);
    ospim_port_io7_4_config(OSPIM_PORT0, OSPIM_IO_HIGH_DISABLE);

    ospim_port_sck_source_select(OSPIM_PORT0, OSPIM_SCK_SOURCE_OSPI0_SCK);
    ospim_port_csn_source_select(OSPIM_PORT0, OSPIM_CSN_SOURCE_OSPI0_CSN);
    ospim_port_io3_0_source_select(OSPIM_PORT0, OSPIM_SRCPLIO_OSPI0_IO_LOW);

    return RT_EOK;
}

static rt_bool_t gd32_ospi_width_is_valid(rt_uint8_t width)
{
    return width == 1 || width == 2 || width == 4;
}

static rt_err_t gd32_ospi_instruction_mode(rt_uint8_t lines, uint32_t *mode)
{
    switch (lines)
    {
    case 0:
        *mode = OSPI_INSTRUCTION_NONE;
        break;
    case 1:
        *mode = OSPI_INSTRUCTION_1_LINE;
        break;
    case 2:
        *mode = OSPI_INSTRUCTION_2_LINES;
        break;
    case 4:
        *mode = OSPI_INSTRUCTION_4_LINES;
        break;
    case 8:
        *mode = OSPI_INSTRUCTION_8_LINES;
        break;
    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t gd32_ospi_address_mode(rt_uint8_t lines, uint32_t *mode)
{
    switch (lines)
    {
    case 0:
        *mode = OSPI_ADDRESS_NONE;
        break;
    case 1:
        *mode = OSPI_ADDRESS_1_LINE;
        break;
    case 2:
        *mode = OSPI_ADDRESS_2_LINES;
        break;
    case 4:
        *mode = OSPI_ADDRESS_4_LINES;
        break;
    case 8:
        *mode = OSPI_ADDRESS_8_LINES;
        break;
    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t gd32_ospi_alternate_mode(rt_uint8_t lines, uint32_t *mode)
{
    switch (lines)
    {
    case 0:
        *mode = OSPI_ALTERNATE_BYTES_NONE;
        break;
    case 1:
        *mode = OSPI_ALTERNATE_BYTES_1_LINE;
        break;
    case 2:
        *mode = OSPI_ALTERNATE_BYTES_2_LINES;
        break;
    case 4:
        *mode = OSPI_ALTERNATE_BYTES_4_LINES;
        break;
    case 8:
        *mode = OSPI_ALTERNATE_BYTES_8_LINES;
        break;
    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t gd32_ospi_data_mode(rt_uint8_t lines, uint32_t *mode)
{
    switch (lines)
    {
    case 0:
        *mode = OSPI_DATA_NONE;
        break;
    case 1:
        *mode = OSPI_DATA_1_LINE;
        break;
    case 2:
        *mode = OSPI_DATA_2_LINES;
        break;
    case 4:
        *mode = OSPI_DATA_4_LINES;
        break;
    case 8:
        *mode = OSPI_DATA_8_LINES;
        break;
    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t gd32_ospi_address_size(rt_uint8_t size, uint32_t *address_size)
{
    switch (size)
    {
    case 8:
        *address_size = OSPI_ADDRESS_8_BITS;
        break;
    case 16:
        *address_size = OSPI_ADDRESS_16_BITS;
        break;
    case 24:
        *address_size = OSPI_ADDRESS_24_BITS;
        break;
    case 32:
        *address_size = OSPI_ADDRESS_32_BITS;
        break;
    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t gd32_ospi_alternate_size(rt_uint8_t size, uint32_t *alternate_size)
{
    switch (size)
    {
    case 8:
        *alternate_size = OSPI_ALTERNATE_BYTES_8_BITS;
        break;
    case 16:
        *alternate_size = OSPI_ALTERNATE_BYTES_16_BITS;
        break;
    case 24:
        *alternate_size = OSPI_ALTERNATE_BYTES_24_BITS;
        break;
    case 32:
        *alternate_size = OSPI_ALTERNATE_BYTES_32_BITS;
        break;
    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t gd32_ospi_configure(struct rt_spi_device *device,
                                    struct rt_spi_configuration *configuration)
{
    struct rt_qspi_device *qspi_device;
    struct rt_qspi_configuration *qspi_configuration;
    struct rt_spi_configuration *spi_configuration;
    struct gd32_ospi_bus *ospi_bus;
    uint32_t source_hz;
    uint32_t divider;
    uint32_t medium_size;
    uint32_t address_bits;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    qspi_device = (struct rt_qspi_device *)device;
    qspi_configuration = &qspi_device->config;
    spi_configuration = &qspi_configuration->parent;
    ospi_bus = (struct gd32_ospi_bus *)device->bus->parent.user_data;

    if (spi_configuration->data_width != 8 ||
        (spi_configuration->mode & (RT_SPI_CPOL | RT_SPI_CPHA)) != RT_SPI_MODE_0 ||
        (spi_configuration->mode & RT_SPI_MSB) == 0 ||
        spi_configuration->max_hz == 0 ||
        !gd32_ospi_width_is_valid(qspi_configuration->qspi_dl_width))
    {
        return -RT_EINVAL;
    }

    medium_size = qspi_configuration->medium_size;
    if (medium_size < 2 || (medium_size & (medium_size - 1U)) != 0)
    {
        return -RT_EINVAL;
    }

    source_hz = rcu_clock_freq_get(CK_AHB);
    divider = source_hz / spi_configuration->max_hz;
    if ((source_hz % spi_configuration->max_hz) != 0)
    {
        divider++;
    }
    if (divider == 0)
    {
        divider = 1;
    }
    if (divider > 256)
    {
        LOG_E("requested OSPI0 clock is too low: %u Hz", spi_configuration->max_hz);
        return -RT_EINVAL;
    }

    address_bits = 0;
    while (medium_size > 1)
    {
        address_bits++;
        medium_size >>= 1;
    }

    ospi_disable(OSPI0);
    ospi_struct_init(&ospi_bus->init);
    ospi_bus->init.prescaler = divider - 1U;
    ospi_bus->init.sample_shift = qspi_configuration->ddr_mode ?
                                  OSPI_SAMPLE_SHIFTING_NONE :
                                  OSPI_SAMPLE_SHIFTING_HALF_CYCLE;
    ospi_bus->init.fifo_threshold = OSPI_FIFO_THRESHOLD_16;
    ospi_bus->init.device_size = OSPI_MESZ(address_bits - 1U);
    ospi_bus->init.cs_hightime = OSPI_CS_HIGH_TIME_3_CYCLE;
    ospi_bus->init.memory_type = OSPI_STANDARD_MODE;
    ospi_bus->init.delay_hold_cycle = OSPI_DELAY_HOLD_NONE;
    ospi_init(OSPI0, &ospi_bus->init);
    ospi_enable(OSPI0);

    LOG_D("OSPI0 configured at %u Hz", source_hz / divider);
    return RT_EOK;
}

static rt_ssize_t gd32_ospi_xfer(struct rt_spi_device *device,
                                 struct rt_spi_message *message)
{
    struct rt_qspi_device *qspi_device;
    struct rt_qspi_message *qspi_message;
    struct gd32_ospi_bus *ospi_bus;
    ospi_regular_cmd_struct command = {0};
    rt_uint8_t max_width;
    rt_bool_t ddr_mode;
    rt_err_t result;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    qspi_device = (struct rt_qspi_device *)device;
    qspi_message = (struct rt_qspi_message *)message;
    ospi_bus = (struct gd32_ospi_bus *)device->bus->parent.user_data;
    max_width = qspi_device->config.qspi_dl_width;
    ddr_mode = qspi_device->config.ddr_mode != 0;

    if (qspi_message->instruction.qspi_lines > max_width ||
        qspi_message->address.qspi_lines > max_width ||
        qspi_message->alternate_bytes.qspi_lines > max_width ||
        qspi_message->qspi_data_lines > max_width ||
        qspi_message->dummy_cycles > 31 ||
        (message->send_buf != RT_NULL && message->recv_buf != RT_NULL))
    {
        return -RT_EINVAL;
    }

    if ((message->length != 0 && qspi_message->qspi_data_lines == 0) ||
        (message->length == 0 && qspi_message->qspi_data_lines != 0) ||
        (message->length != 0 && message->send_buf == RT_NULL && message->recv_buf == RT_NULL))
    {
        return -RT_EINVAL;
    }

    command.operation_type = OSPI_OPTYPE_COMMON_CFG;
    command.device_id = OSPI_DEVICE0_SELECT;
    command.instruction = qspi_message->instruction.content;
    command.ins_size = OSPI_INSTRUCTION_8_BITS;
    command.address = qspi_message->address.content;
    command.alter_bytes = qspi_message->alternate_bytes.content;
    command.nbdata = message->length;
    command.dummy_cycles = qspi_message->dummy_cycles;
    command.sioo_mode = OSPI_SIOO_INST_EVERY_CMD;

    if (gd32_ospi_instruction_mode(qspi_message->instruction.qspi_lines, &command.ins_mode) != RT_EOK ||
        gd32_ospi_address_mode(qspi_message->address.qspi_lines, &command.addr_mode) != RT_EOK ||
        gd32_ospi_alternate_mode(qspi_message->alternate_bytes.qspi_lines, &command.alter_bytes_mode) != RT_EOK ||
        gd32_ospi_data_mode(qspi_message->qspi_data_lines, &command.data_mode) != RT_EOK)
    {
        return -RT_EINVAL;
    }

    if (qspi_message->address.qspi_lines != 0 &&
        gd32_ospi_address_size(qspi_message->address.size, &command.addr_size) != RT_EOK)
    {
        return -RT_EINVAL;
    }

    if (qspi_message->alternate_bytes.qspi_lines != 0 &&
        gd32_ospi_alternate_size(qspi_message->alternate_bytes.size, &command.alter_bytes_size) != RT_EOK)
    {
        return -RT_EINVAL;
    }

    command.ins_dtr_mode = ddr_mode && command.ins_mode != OSPI_INSTRUCTION_NONE ?
                           OSPI_INSDTR_MODE_ENABLE : OSPI_INSDTR_MODE_DISABLE;
    command.addr_dtr_mode = ddr_mode && command.addr_mode != OSPI_ADDRESS_NONE ?
                            OSPI_ADDRDTR_MODE_ENABLE : OSPI_ADDRDTR_MODE_DISABLE;
    command.alter_bytes_dtr_mode = ddr_mode && command.alter_bytes_mode != OSPI_ALTERNATE_BYTES_NONE ?
                                   OSPI_ABDTR_MODE_ENABLE : OSPI_ABDTR_MODE_DISABLE;
    command.data_dtr_mode = ddr_mode && command.data_mode != OSPI_DATA_NONE ?
                            OSPI_DADTR_MODE_ENABLE : OSPI_DADTR_MODE_DISABLE;
    command.dqs_mode = ddr_mode && command.data_mode != OSPI_DATA_NONE ?
                       OSPI_DQS_ENABLE : OSPI_DQS_DISABLE;

    ospi_command_config(OSPI0, &ospi_bus->init, &command);

    if (message->length == 0)
    {
        return 1;
    }

    if (message->send_buf != RT_NULL)
    {
        result = gd32_ospi_transmit((const rt_uint8_t *)message->send_buf,
                                    message->length);
        return result == RT_EOK ? message->length : result;
    }

    if (message->recv_buf != RT_NULL)
    {
        result = gd32_ospi_receive(&ospi_bus->init,
                                   (rt_uint8_t *)message->recv_buf,
                                   message->length);
        return result == RT_EOK ? message->length : result;
    }

    return 1;
}

static const struct rt_spi_ops gd32_ospi_ops =
{
    .configure = gd32_ospi_configure,
    .xfer = gd32_ospi_xfer,
};

rt_err_t rt_hw_ospi_device_attach(const char *bus_name,
                                  const char *device_name,
                                  rt_uint8_t data_line_width,
                                  void (*enter_ospi_mode)(struct rt_qspi_device *device),
                                  void (*exit_ospi_mode)(struct rt_qspi_device *device))
{
    struct rt_qspi_device *device;
    rt_err_t result;

    if (bus_name == RT_NULL || device_name == RT_NULL ||
        !gd32_ospi_width_is_valid(data_line_width))
    {
        return -RT_EINVAL;
    }

    device = (struct rt_qspi_device *)rt_calloc(1, sizeof(struct rt_qspi_device));
    if (device == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    device->config.qspi_dl_width = data_line_width;
    device->enter_qspi_mode = enter_ospi_mode;
    device->exit_qspi_mode = exit_ospi_mode;

    result = rt_spi_bus_attach_device_cspin(&device->parent, device_name,
                                            bus_name, PIN_NONE, RT_NULL);
    if (result != RT_EOK)
    {
        rt_free(device);
    }

    return result;
}

static int rt_hw_ospi_init(void)
{
    rt_err_t result;

    result = gd32_ospi_hardware_init();
    if (result != RT_EOK)
    {
        return result;
    }

    ospi0_bus.parent.parent.user_data = &ospi0_bus;
    result = rt_qspi_bus_register(&ospi0_bus.parent, "ospi0", &gd32_ospi_ops);
    if (result == RT_EOK)
    {
        LOG_D("ospi0 bus registered");
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_ospi_init);

#endif /* BSP_USING_OSPI0 */
