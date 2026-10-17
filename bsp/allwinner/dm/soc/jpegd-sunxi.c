/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <drivers/syscon.h>

#define DBG_TAG "jpegd.sunxi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <sunxi-jpegd.h>
#include <sunxi-jpege.h>
#include <sunxi-pngd.h>

#define SUNXI_VE_MODE                         0x0000
#define SUNXI_VE_VERSION                      0x00f0
#define SUNXI_VE_MODE_DISABLED                0x0007
/* F101 selects the MPEG decoder with the SoC-specific mode bit set. */
#define SUNXI_VE_MODE_DEC_MPEG                RT_BIT(3)
#define SUNXI_VE_MODE_DEC_PNG                 0x000e
#define SUNXI_VE_MODE_ENC_AVC                 0x000b
#define SUNXI_VE_MODE_ENC_ISP                 RT_BIT(6)
#define SUNXI_VE_MODE_ENC_AVC_ENABLE          RT_BIT(7)
#define SUNXI_VE_MODE_REC_WR_MODE_2MB         RT_BIT(20)
#define SUNXI_VE_MODE_DDR_MODE_BW_128         (3U << 16)

#define SUNXI_VE_TOP_PRI_CHROMA_BUF_LEN       0x00c4
#define SUNXI_VE_TOP_PRI_BUF_LINE_STRIDE      0x00c8
#define SUNXI_VE_TOP_SEC_BUF_LINE_STRIDE      0x00cc
#define SUNXI_VE_TOP_CHROMA_BUF_LEN0          0x00e8
#define SUNXI_VE_TOP_OUTPUT_FORMAT            0x00ec

#define SUNXI_VE_MPEG_OFFSET                  0x0100
#define SUNXI_VE_MPEG_CTRL                    (SUNXI_VE_MPEG_OFFSET + 0x14)
#define SUNXI_VE_MPEG_TRIGGER                 (SUNXI_VE_MPEG_OFFSET + 0x18)
#define SUNXI_VE_MPEG_STATUS                  (SUNXI_VE_MPEG_OFFSET + 0x1c)
#define SUNXI_VE_MPEG_VLD_ADDR                (SUNXI_VE_MPEG_OFFSET + 0x28)
#define SUNXI_VE_MPEG_VLD_OFFSET              (SUNXI_VE_MPEG_OFFSET + 0x2c)
#define SUNXI_VE_MPEG_VLD_LENGTH              (SUNXI_VE_MPEG_OFFSET + 0x30)
#define SUNXI_VE_MPEG_VLD_END                 (SUNXI_VE_MPEG_OFFSET + 0x34)
#define SUNXI_VE_MPEG_IQ_INPUT                (SUNXI_VE_MPEG_OFFSET + 0x80)
#define SUNXI_VE_MPEG_JPEG_SIZE               (SUNXI_VE_MPEG_OFFSET + 0xb8)
#define SUNXI_VE_MPEG_JPEG_RESTART            (SUNXI_VE_MPEG_OFFSET + 0xc0)
#define SUNXI_VE_MPEG_JPEG_LUMA               (SUNXI_VE_MPEG_OFFSET + 0xcc)
#define SUNXI_VE_MPEG_JPEG_CHROMA             (SUNXI_VE_MPEG_OFFSET + 0xd0)
#define SUNXI_VE_MPEG_JPEG_SCALE              (SUNXI_VE_MPEG_OFFSET + 0xd4)
#define SUNXI_VE_MPEG_SRAM_OFFSET             (SUNXI_VE_MPEG_OFFSET + 0xe0)
#define SUNXI_VE_MPEG_SRAM_DATA               (SUNXI_VE_MPEG_OFFSET + 0xe4)

#define SUNXI_VE_MPEG_CTRL_JPEG_FORCE_420     RT_BIT(18)
#define SUNXI_VE_MPEG_CTRL_IRQ_MASK           (RT_BIT(5) | RT_BIT(4) | RT_BIT(3))
#define SUNXI_VE_MPEG_CTRL_F101_420           (RT_BIT(8) | RT_BIT(7) | \
                                                RT_BIT(6) | RT_BIT(5) | \
                                                RT_BIT(4) | RT_BIT(3))
#define SUNXI_VE_MPEG_STATUS_MASK             (RT_BIT(3) | RT_BIT(2) | \
                                                RT_BIT(1) | RT_BIT(0))
#define SUNXI_VE_MPEG_VLD_FIRST               RT_BIT(30)
#define SUNXI_VE_MPEG_VLD_LAST                RT_BIT(29)
#define SUNXI_VE_MPEG_VLD_VALID               RT_BIT(28)
#define SUNXI_VE_MPEG_IQ_LUMA                 RT_BIT(14)
#define SUNXI_VE_MPEG_TRIGGER_JPEG            (3U << 24)
#define SUNXI_VE_MPEG_TRIGGER_JPEG_VLD        0x0e
#define SUNXI_VE_MPEG_TRIGGER_420             (0U << 27)
#define SUNXI_VE_MPEG_TRIGGER_422             (2U << 27)
#define SUNXI_VE_MPEG_TRIGGER_444             (3U << 27)
#define SUNXI_VE_MPEG_TRIGGER_422T            (4U << 27)

#define SUNXI_VE_ISP_OFFSET                   0x0a00
#define SUNXI_VE_ISP_INPUT_SIZE               (SUNXI_VE_ISP_OFFSET + 0x00)
#define SUNXI_VE_ISP_INPUT_STRIDE             (SUNXI_VE_ISP_OFFSET + 0x04)
#define SUNXI_VE_ISP_CTRL                     (SUNXI_VE_ISP_OFFSET + 0x08)
#define SUNXI_VE_ISP_INPUT_LUMA               (SUNXI_VE_ISP_OFFSET + 0x78)
#define SUNXI_VE_ISP_INPUT_CHROMA             (SUNXI_VE_ISP_OFFSET + 0x7c)

#define SUNXI_VE_AVC_OFFSET                   0x0b00
#define SUNXI_VE_AVC_JPEG_CTRL                (SUNXI_VE_AVC_OFFSET + 0x04)
#define SUNXI_VE_AVC_CTRL                     (SUNXI_VE_AVC_OFFSET + 0x14)
#define SUNXI_VE_AVC_TRIGGER                  (SUNXI_VE_AVC_OFFSET + 0x18)
#define SUNXI_VE_AVC_STATUS                   (SUNXI_VE_AVC_OFFSET + 0x1c)
#define SUNXI_VE_AVC_VLE_ADDR                 (SUNXI_VE_AVC_OFFSET + 0x80)
#define SUNXI_VE_AVC_VLE_END                  (SUNXI_VE_AVC_OFFSET + 0x84)
#define SUNXI_VE_AVC_VLE_OFFSET               (SUNXI_VE_AVC_OFFSET + 0x88)
#define SUNXI_VE_AVC_VLE_MAX                  (SUNXI_VE_AVC_OFFSET + 0x8c)
#define SUNXI_VE_AVC_VLE_LENGTH               (SUNXI_VE_AVC_OFFSET + 0x90)
#define SUNXI_VE_AVC_SRAM_OFFSET              (SUNXI_VE_AVC_OFFSET + 0xe0)
#define SUNXI_VE_AVC_SRAM_DATA                (SUNXI_VE_AVC_OFFSET + 0xe4)

#define SUNXI_VE_AVC_CTRL_IRQ_ENABLE          RT_BIT(7)
#define SUNXI_VE_AVC_TRIGGER_JPEG             RT_BIT(16)
#define SUNXI_VE_AVC_TRIGGER_LAUNCH           0x08
#define SUNXI_VE_AVC_STATUS_SUCCESS           RT_BIT(0)
#define SUNXI_VE_AVC_STATUS_ERROR             RT_BIT(1)
#define SUNXI_VE_AVC_STATUS_MASK              0x07
#define SUNXI_VE_AVC_JPEG_FILL_ONE            RT_BIT(31)
#define SUNXI_VE_AVC_JPEG_BYTE_STUFF          RT_BIT(30)

#define SUNXI_VE_PNG_OFFSET                   0x0600
#define SUNXI_VE_PNG_CTRL                     (SUNXI_VE_PNG_OFFSET + 0x00)
#define SUNXI_VE_PNG_INT_EN                   (SUNXI_VE_PNG_OFFSET + 0x04)
#define SUNXI_VE_PNG_INT_STATUS               (SUNXI_VE_PNG_OFFSET + 0x0c)
#define SUNXI_VE_PNG_STATUS                   (SUNXI_VE_PNG_OFFSET + 0x10)
#define SUNXI_VE_PNG_RX_ADDR                  (SUNXI_VE_PNG_OFFSET + 0x14)
#define SUNXI_VE_PNG_RX_LEN                   (SUNXI_VE_PNG_OFFSET + 0x18)
#define SUNXI_VE_PNG_TX_ADDR                  (SUNXI_VE_PNG_OFFSET + 0x1c)
#define SUNXI_VE_PNG_TX_LEN                   (SUNXI_VE_PNG_OFFSET + 0x20)

#define SUNXI_VE_PNG_CTRL_START               RT_BIT(0)
#define SUNXI_VE_PNG_INT_DONE                 RT_BIT(0)
#define SUNXI_VE_PNG_INT_ERROR                RT_BIT(1)
#define SUNXI_VE_PNG_INT_MASK                 (SUNXI_VE_PNG_INT_DONE | \
                                                SUNXI_VE_PNG_INT_ERROR)

#define SUNXI_JPEGD_BUFFER_ALIGN              1024
#define SUNXI_JPEGD_MAX_WIDTH                 2048
#define SUNXI_JPEGD_MAX_HEIGHT                2048
#define SUNXI_JPEGD_DEFAULT_TIMEOUT_MS        500
#define SUNXI_JPEGE_MAX_WIDTH                 8192
#define SUNXI_JPEGE_MAX_HEIGHT                8192
#define SUNXI_JPEGE_MIN_OUTPUT_SIZE           (8 * 1024)
#define SUNXI_JPEGE_HEADER_SIZE               1024
#define SUNXI_PNGD_DEFAULT_TIMEOUT_MS         1000

#define JPEG_MARKER_SOI                       0xd8
#define JPEG_MARKER_EOI                       0xd9
#define JPEG_MARKER_SOS                       0xda
#define JPEG_MARKER_DQT                       0xdb
#define JPEG_MARKER_DHT                       0xc4
#define JPEG_MARKER_DRI                       0xdd
#define JPEG_MARKER_SOF0                      0xc0

struct sunxi_jpegd_buffer_entry
{
    rt_list_t list;
    struct sunxi_jpegd_buffer buffer;
    void *alloc_addr;
    rt_ubase_t alloc_phys;
    rt_size_t alloc_size;
};

struct sunxi_jpegd_quant_table
{
    rt_uint16_t value[64];
    rt_bool_t valid;
};

struct sunxi_jpegd_huffman_table
{
    rt_uint8_t counts[16];
    rt_uint8_t symbols[256];
    rt_uint16_t symbol_count;
    rt_bool_t valid;
};

struct sunxi_jpegd_component
{
    rt_uint8_t id;
    rt_uint8_t hfactor;
    rt_uint8_t vfactor;
    rt_uint8_t quant_table;
    rt_uint8_t dc_table;
    rt_uint8_t ac_table;
};

struct sunxi_jpegd_header
{
    struct sunxi_jpegd_quant_table quant[4];
    struct sunxi_jpegd_huffman_table huffman[2][2];
    struct sunxi_jpegd_component component[3];
    rt_size_t entropy_offset;
    rt_size_t eoi_offset;
    rt_uint16_t width;
    rt_uint16_t height;
    rt_uint16_t restart_interval;
    rt_uint8_t precision;
    rt_uint8_t component_count;
};

static rt_size_t sunxi_jpegd_find_eoi(const rt_uint8_t *data, rt_size_t size,
        rt_size_t position)
{
    while (position + 1 < size)
    {
        if (data[position++] != 0xff)
        {
            continue;
        }
        if (data[position] == 0x00 ||
                (data[position] >= 0xd0 && data[position] <= 0xd7))
        {
            ++position;
            continue;
        }
        if (data[position] == JPEG_MARKER_EOI)
        {
            return position - 1;
        }
    }

    return size;
}

enum sunxi_jpegd_engine
{
    SUNXI_JPEGD_ENGINE_IDLE,
    SUNXI_JPEGD_ENGINE_DECODE,
    SUNXI_JPEGD_ENGINE_ENCODE,
    SUNXI_JPEGD_ENGINE_PNG_DECODE,
};

struct sunxi_jpege_header
{
    rt_uint8_t data[SUNXI_JPEGE_HEADER_SIZE];
    rt_size_t size;
};

struct sunxi_jpegd
{
    struct rt_device parent;
    struct rt_device encoder;
    struct rt_device png_decoder;
    struct rt_device *dev;
    struct rt_clk_array *clks;
    struct rt_reset_control *resets;
    void *base;
    int irq;

    struct rt_mutex lock;
    struct rt_completion completion;
    rt_list_t buffers;
    rt_uint32_t version;
    rt_uint32_t irq_status;
    rt_err_t error;
    rt_bool_t clocks_enabled;
    rt_bool_t lock_initialized;
    rt_bool_t device_registered;
    rt_bool_t encoder_registered;
    rt_bool_t png_registered;
    rt_bool_t irq_installed;
    rt_bool_t running;
    enum sunxi_jpegd_engine engine;
};

static rt_err_t sunxi_jpegd_claim_sram(struct sunxi_jpegd *jpegd)
{
    struct rt_ofw_node *section_np;
    struct rt_ofw_node *sram_np;
    struct rt_ofw_node *syscon_np;
    struct rt_syscon *syscon;
    rt_err_t err = -RT_EINVAL;

    section_np = rt_ofw_parse_phandle(jpegd->dev->ofw_node,
            "allwinner,sram", 0);
    if (!section_np)
    {
        return -RT_EINVAL;
    }

    if (!rt_ofw_node_is_compatible(section_np,
            "allwinner,sun252i-f101-sram-ve"))
    {
        goto _out_section;
    }

    sram_np = rt_ofw_get_parent(section_np);
    syscon_np = rt_ofw_get_parent(sram_np);
    if (!sram_np || !syscon_np)
    {
        goto _out_parent;
    }

    /* Clear VE_SRAM_BMODE_CTRL so the DT-described SRAM belongs to VE. */
    syscon = rt_syscon_find_by_ofw_node(syscon_np);
    if (syscon)
    {
        err = rt_syscon_update_bits(syscon, 0x4, RT_BIT(24), 0);
    }

    rt_ofw_node_put(syscon_np);
_out_parent:
    rt_ofw_node_put(sram_np);
_out_section:
    rt_ofw_node_put(section_np);

    return err;
}

static const rt_uint8_t sunxi_jpegd_default_dc_luma_counts[16] =
{
    0, 1, 5, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
};

static const rt_uint8_t sunxi_jpegd_default_dc_chroma_counts[16] =
{
    0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
};

static const rt_uint8_t sunxi_jpegd_default_dc_values[12] =
{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
};

static const rt_uint8_t sunxi_jpegd_default_ac_luma_counts[16] =
{
    0, 2, 1, 3, 3, 2, 4, 3, 5, 5, 4, 4, 0, 0, 1, 125,
};

static const rt_uint8_t sunxi_jpegd_default_ac_luma_values[162] =
{
    0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12, 0x21, 0x31,
    0x41, 0x06, 0x13, 0x51, 0x61, 0x07, 0x22, 0x71, 0x14, 0x32,
    0x81, 0x91, 0xa1, 0x08, 0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52,
    0xd1, 0xf0, 0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16,
    0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a,
    0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x43, 0x44, 0x45,
    0x46, 0x47, 0x48, 0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57,
    0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
    0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x83,
    0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x92, 0x93, 0x94,
    0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5,
    0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6,
    0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
    0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8,
    0xd9, 0xda, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8,
    0xe9, 0xea, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
    0xf9, 0xfa,
};

static const rt_uint8_t sunxi_jpegd_default_ac_chroma_counts[16] =
{
    0, 2, 1, 2, 4, 4, 3, 4, 7, 5, 4, 4, 0, 1, 2, 119,
};

static const rt_uint8_t sunxi_jpegd_default_ac_chroma_values[162] =
{
    0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21, 0x31, 0x06,
    0x12, 0x41, 0x51, 0x07, 0x61, 0x71, 0x13, 0x22, 0x32, 0x81,
    0x08, 0x14, 0x42, 0x91, 0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33,
    0x52, 0xf0, 0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34,
    0xe1, 0x25, 0xf1, 0x17, 0x18, 0x19, 0x1a, 0x26, 0x27, 0x28,
    0x29, 0x2a, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x43, 0x44,
    0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x53, 0x54, 0x55, 0x56,
    0x57, 0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
    0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a,
    0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x92,
    0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3,
    0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4,
    0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5,
    0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6,
    0xd7, 0xd8, 0xd9, 0xda, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
    0xe8, 0xe9, 0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
    0xf9, 0xfa,
};

static const rt_uint8_t sunxi_jpege_luma_quant[64] =
{
    16, 11, 10, 16, 24, 40, 51, 61,
    12, 12, 14, 19, 26, 58, 60, 55,
    14, 13, 16, 24, 40, 57, 69, 56,
    14, 17, 22, 29, 51, 87, 80, 62,
    18, 22, 37, 56, 68, 109, 103, 77,
    24, 35, 55, 64, 81, 104, 113, 92,
    49, 64, 78, 87, 103, 121, 120, 101,
    72, 92, 95, 98, 112, 100, 103, 99,
};

static const rt_uint8_t sunxi_jpege_chroma_quant[64] =
{
    17, 18, 24, 47, 99, 99, 99, 99,
    18, 21, 26, 66, 99, 99, 99, 99,
    24, 26, 56, 99, 99, 99, 99, 99,
    47, 66, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
};

static const rt_uint8_t sunxi_jpege_zigzag[64] =
{
     0,  1,  8, 16,  9,  2,  3, 10,
    17, 24, 32, 25, 18, 11,  4,  5,
    12, 19, 26, 33, 40, 48, 41, 34,
    27, 20, 13,  6,  7, 14, 21, 28,
    35, 42, 49, 56, 57, 50, 43, 36,
    29, 22, 15, 23, 30, 37, 44, 51,
    58, 59, 52, 45, 38, 31, 39, 46,
    53, 60, 61, 54, 47, 55, 62, 63,
};

#define raw_to_sunxi_jpegd(raw) \
    rt_container_of(raw, struct sunxi_jpegd, parent)
#define raw_to_sunxi_jpege(raw) \
    rt_container_of(raw, struct sunxi_jpegd, encoder)
#define raw_to_sunxi_pngd(raw) \
    rt_container_of(raw, struct sunxi_jpegd, png_decoder)

static rt_uint32_t sunxi_jpegd_readl(struct sunxi_jpegd *jpegd,
        rt_uint32_t offset)
{
    return HWREG32(jpegd->base + offset);
}

static void sunxi_jpegd_writel(struct sunxi_jpegd *jpegd,
        rt_uint32_t offset, rt_uint32_t value)
{
    HWREG32(jpegd->base + offset) = value;
}

static rt_err_t sunxi_jpegd_read_be16(const rt_uint8_t *data,
        rt_size_t size, rt_size_t *position, rt_uint16_t *value)
{
    if (*position > size || size - *position < 2)
    {
        return -RT_EINVAL;
    }

    *value = ((rt_uint16_t)data[*position] << 8) |
            data[*position + 1];
    *position += 2;

    return RT_EOK;
}

static rt_err_t sunxi_jpegd_parse_dqt(const rt_uint8_t *data,
        rt_size_t start, rt_size_t end, struct sunxi_jpegd_header *header)
{
    struct sunxi_jpegd_quant_table *table;
    rt_uint16_t value;
    rt_size_t position = start;
    rt_uint8_t selector;
    rt_uint8_t precision;
    rt_uint8_t index;
    int i;

    while (position < end)
    {
        selector = data[position++];
        precision = selector >> 4;
        index = selector & 0x0f;
        if (precision > 1 || index >= RT_ARRAY_SIZE(header->quant) ||
            position > end || end - position < (precision ? 128 : 64))
        {
            return -RT_EINVAL;
        }

        table = &header->quant[index];
        for (i = 0; i < RT_ARRAY_SIZE(table->value); i++)
        {
            if (precision)
            {
                if (sunxi_jpegd_read_be16(data, end, &position, &value))
                {
                    return -RT_EINVAL;
                }
            }
            else
            {
                value = data[position++];
            }

            if (!value || value > 0xff)
            {
                return -RT_EINVAL;
            }
            table->value[i] = value;
        }
        table->valid = RT_TRUE;
    }

    return position == end ? RT_EOK : -RT_EINVAL;
}

static rt_err_t sunxi_jpegd_parse_dht(const rt_uint8_t *data,
        rt_size_t start, rt_size_t end, struct sunxi_jpegd_header *header)
{
    struct sunxi_jpegd_huffman_table *table;
    rt_size_t position = start;
    rt_uint16_t count;
    rt_uint8_t selector;
    rt_uint8_t table_class;
    rt_uint8_t table_id;
    int i;

    while (position < end)
    {
        if (end - position < 17)
        {
            return -RT_EINVAL;
        }

        selector = data[position++];
        table_class = selector >> 4;
        table_id = selector & 0x0f;
        if (table_class > 1 || table_id > 1)
        {
            return -RT_EINVAL;
        }

        table = &header->huffman[table_class][table_id];
        count = 0;
        for (i = 0; i < RT_ARRAY_SIZE(table->counts); i++)
        {
            table->counts[i] = data[position++];
            count += table->counts[i];
        }
        if (count > RT_ARRAY_SIZE(table->symbols) || position > end ||
            end - position < count)
        {
            return -RT_EINVAL;
        }

        rt_memcpy(table->symbols, &data[position], count);
        table->symbol_count = count;
        table->valid = RT_TRUE;
        position += count;
    }

    return position == end ? RT_EOK : -RT_EINVAL;
}

static rt_err_t sunxi_jpegd_parse_sof0(const rt_uint8_t *data,
        rt_size_t start, rt_size_t end, struct sunxi_jpegd_header *header)
{
    struct sunxi_jpegd_component *component;
    rt_size_t position = start;
    rt_uint16_t width;
    rt_uint16_t height;
    rt_uint8_t count;
    rt_uint8_t sampling;
    int i;

    if (end - start < 6)
    {
        return -RT_EINVAL;
    }

    header->precision = data[position++];
    if (sunxi_jpegd_read_be16(data, end, &position, &height) ||
        sunxi_jpegd_read_be16(data, end, &position, &width))
    {
        return -RT_EINVAL;
    }

    count = data[position++];
    if (count != RT_ARRAY_SIZE(header->component) ||
        end - position != (rt_size_t)count * 3)
    {
        return -RT_EINVAL;
    }

    for (i = 0; i < count; i++)
    {
        component = &header->component[i];
        component->id = data[position++];
        sampling = data[position++];
        component->hfactor = sampling >> 4;
        component->vfactor = sampling & 0x0f;
        component->quant_table = data[position++];
        if (!component->hfactor || !component->vfactor ||
            component->quant_table >= RT_ARRAY_SIZE(header->quant))
        {
            return -RT_EINVAL;
        }
    }

    header->width = width;
    header->height = height;
    header->component_count = count;

    return RT_EOK;
}

static rt_err_t sunxi_jpegd_parse_sos(const rt_uint8_t *data,
        rt_size_t start, rt_size_t end, struct sunxi_jpegd_header *header)
{
    struct sunxi_jpegd_component *component;
    rt_size_t position = start;
    rt_uint8_t count;
    rt_uint8_t component_id;
    rt_uint8_t tables;
    rt_uint8_t scan_start;
    rt_uint8_t scan_end;
    rt_uint8_t successive;
    int index;
    int i;
    int j;

    if (end - start < 4 || !header->component_count)
    {
        return -RT_EINVAL;
    }

    count = data[position++];
    if (count != header->component_count ||
        end - position < (rt_size_t)count * 2 + 3)
    {
        return -RT_EINVAL;
    }

    for (i = 0; i < count; i++)
    {
        component_id = data[position++];
        tables = data[position++];
        index = -1;
        for (j = 0; j < header->component_count; j++)
        {
            if (header->component[j].id == component_id)
            {
                index = j;
                break;
            }
        }
        if (index < 0 || (tables >> 4) > 1 || (tables & 0x0f) > 1)
        {
            return -RT_EINVAL;
        }

        component = &header->component[index];
        component->dc_table = tables >> 4;
        component->ac_table = tables & 0x0f;
    }

    scan_start = data[position++];
    scan_end = data[position++];
    successive = data[position++];
    if (position != end || scan_start || scan_end != 63 || successive)
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static void sunxi_jpegd_set_huffman_table(struct sunxi_jpegd_huffman_table *table,
        const rt_uint8_t *counts, const rt_uint8_t *symbols,
        rt_uint16_t symbol_count)
{
    if (table->valid)
    {
        return;
    }

    rt_memcpy(table->counts, counts, sizeof(table->counts));
    rt_memcpy(table->symbols, symbols, symbol_count);
    table->symbol_count = symbol_count;
    table->valid = RT_TRUE;
}

static void sunxi_jpegd_set_default_huffman_tables(
        struct sunxi_jpegd_header *header)
{
    sunxi_jpegd_set_huffman_table(&header->huffman[0][0],
            sunxi_jpegd_default_dc_luma_counts,
            sunxi_jpegd_default_dc_values,
            sizeof(sunxi_jpegd_default_dc_values));
    sunxi_jpegd_set_huffman_table(&header->huffman[1][0],
            sunxi_jpegd_default_ac_luma_counts,
            sunxi_jpegd_default_ac_luma_values,
            sizeof(sunxi_jpegd_default_ac_luma_values));
    sunxi_jpegd_set_huffman_table(&header->huffman[0][1],
            sunxi_jpegd_default_dc_chroma_counts,
            sunxi_jpegd_default_dc_values,
            sizeof(sunxi_jpegd_default_dc_values));
    sunxi_jpegd_set_huffman_table(&header->huffman[1][1],
            sunxi_jpegd_default_ac_chroma_counts,
            sunxi_jpegd_default_ac_chroma_values,
            sizeof(sunxi_jpegd_default_ac_chroma_values));
}

static rt_err_t sunxi_jpegd_parse_header(const rt_uint8_t *data,
        rt_size_t size, struct sunxi_jpegd_header *header)
{
    rt_size_t position;
    rt_size_t segment_start;
    rt_size_t segment_end;
    rt_uint16_t segment_length;
    rt_uint8_t marker;
    rt_err_t err;

    if (!data || size < 4 || data[0] != 0xff || data[1] != JPEG_MARKER_SOI)
    {
        LOG_E("invalid JPEG SOI: size=%u first=%02x%02x", size,
                data && size ? data[0] : 0,
                data && size > 1 ? data[1] : 0);
        return -RT_EINVAL;
    }

    rt_memset(header, 0, sizeof(*header));
    position = 2;
    while (position < size)
    {
        while (position < size && data[position] != 0xff)
        {
            position++;
        }
        while (position < size && data[position] == 0xff)
        {
            position++;
        }
        if (position >= size)
        {
            LOG_E("JPEG reaches EOF before SOS");
            return -RT_EINVAL;
        }

        marker = data[position++];
        if (marker == 0x00 || (marker >= 0xd0 && marker <= 0xd7))
        {
            continue;
        }
        if (marker == JPEG_MARKER_EOI)
        {
            LOG_E("JPEG EOI appears before SOS");
            return -RT_EINVAL;
        }
        if (sunxi_jpegd_read_be16(data, size, &position, &segment_length) ||
            segment_length < 2 || position > size ||
            size - position < segment_length - 2)
        {
            LOG_E("invalid JPEG segment %02x at %u", marker, position - 1);
            return -RT_EINVAL;
        }

        segment_start = position;
        segment_end = position + segment_length - 2;
        switch (marker)
        {
        case JPEG_MARKER_DQT:
            err = sunxi_jpegd_parse_dqt(data, segment_start, segment_end,
                    header);
            break;
        case JPEG_MARKER_DHT:
            err = sunxi_jpegd_parse_dht(data, segment_start, segment_end,
                    header);
            break;
        case JPEG_MARKER_DRI:
            if (segment_end - segment_start != 2)
            {
                LOG_E("invalid JPEG DRI length %u", segment_end - segment_start);
                return -RT_EINVAL;
            }
            header->restart_interval = ((rt_uint16_t)data[segment_start] << 8) |
                    data[segment_start + 1];
            err = RT_EOK;
            break;
        case JPEG_MARKER_SOF0:
            err = sunxi_jpegd_parse_sof0(data, segment_start, segment_end,
                    header);
            break;
        case JPEG_MARKER_SOS:
            err = sunxi_jpegd_parse_sos(data, segment_start, segment_end,
                    header);
            if (err)
            {
                LOG_E("invalid JPEG SOS: %d", err);
                return err;
            }
            header->entropy_offset = segment_end;
            header->eoi_offset = sunxi_jpegd_find_eoi(data, size,
                    header->entropy_offset);
            if (header->eoi_offset == size)
            {
                LOG_E("JPEG reaches EOF before EOI");
                return -RT_EINVAL;
            }
            goto _validate;
        default:
            if ((marker >= 0xc0 && marker <= 0xcf) ||
                (marker >= 0xd0 && marker <= 0xdf))
            {
                return -RT_ENOSYS;
            }
            err = RT_EOK;
            break;
        }
        if (err)
        {
            LOG_E("invalid JPEG marker %02x: %d", marker, err);
            return err;
        }
        position = segment_end;
    }

    return -RT_EINVAL;

_validate:
    sunxi_jpegd_set_default_huffman_tables(header);

    if (header->precision != 8 || !header->width || !header->height ||
        header->width > SUNXI_JPEGD_MAX_WIDTH ||
        header->height > SUNXI_JPEGD_MAX_HEIGHT || !header->entropy_offset ||
        !header->quant[header->component[0].quant_table].valid ||
        !header->quant[header->component[1].quant_table].valid ||
        !header->huffman[0][header->component[0].dc_table].valid ||
        !header->huffman[1][header->component[0].ac_table].valid ||
        !header->huffman[0][header->component[1].dc_table].valid ||
        !header->huffman[1][header->component[1].ac_table].valid)
    {
        LOG_E("invalid JPEG frame: %ux%u precision=%u", header->width,
                header->height, header->precision);
        return -RT_EINVAL;
    }

    if (header->component[1].quant_table != header->component[2].quant_table ||
        header->component[1].dc_table != header->component[2].dc_table ||
        header->component[1].ac_table != header->component[2].ac_table)
    {
        return -RT_ENOSYS;
    }

    LOG_D("JPEG header: %ux%u precision=%u entropy=%u..%u restart=%u",
            header->width, header->height, header->precision,
            (rt_uint32_t)header->entropy_offset,
            (rt_uint32_t)header->eoi_offset, header->restart_interval);

    return RT_EOK;
}

static rt_err_t sunxi_jpegd_sampling(const struct sunxi_jpegd_header *header,
        rt_uint32_t *sampling)
{
    const struct sunxi_jpegd_component *y = &header->component[0];
    const struct sunxi_jpegd_component *cb = &header->component[1];
    const struct sunxi_jpegd_component *cr = &header->component[2];

    if (y->hfactor == 2 && y->vfactor == 2 && cb->hfactor == 1 &&
        cb->vfactor == 1 && cr->hfactor == 1 && cr->vfactor == 1)
    {
        *sampling = SUNXI_VE_MPEG_TRIGGER_420;
    }
    else if (y->hfactor == 2 && y->vfactor == 1 && cb->hfactor == 1 &&
            cb->vfactor == 1 && cr->hfactor == 1 && cr->vfactor == 1)
    {
        *sampling = SUNXI_VE_MPEG_TRIGGER_422;
    }
    else if (y->hfactor == 1 && y->vfactor == 1 && cb->hfactor == 1 &&
            cb->vfactor == 1 && cr->hfactor == 1 && cr->vfactor == 1)
    {
        *sampling = SUNXI_VE_MPEG_TRIGGER_444;
    }
    else if (y->hfactor == 1 && y->vfactor == 2 && cb->hfactor == 1 &&
            cb->vfactor == 1 && cr->hfactor == 1 && cr->vfactor == 1)
    {
        *sampling = SUNXI_VE_MPEG_TRIGGER_422T;
    }
    else
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static rt_err_t sunxi_jpegd_configure_output(struct sunxi_jpegd *jpegd,
        const struct sunxi_jpegd_header *header, rt_uint32_t sampling,
        struct sunxi_jpegd_buffer_entry *output, rt_size_t *out_stride,
        rt_size_t *out_luma_size, rt_size_t *out_size)
{
    rt_size_t stride;
    rt_size_t aligned_height;
    rt_size_t luma_size;
    rt_size_t chroma_size;

    if (sampling != SUNXI_VE_MPEG_TRIGGER_420)
    {
        return -RT_ENOSYS;
    }

    stride = RT_ALIGN(header->width, 32);
    aligned_height = RT_ALIGN(header->height, 32);
    luma_size = stride * aligned_height;
    chroma_size = luma_size / 4;

    if (output->buffer.size < luma_size + chroma_size * 2 ||
        (output->buffer.phys_addr & (SUNXI_JPEGD_BUFFER_ALIGN - 1)))
    {
        return -RT_ENOMEM;
    }

    /* The F101 VE writes a 32-pixel aligned YV12 image. */
    sunxi_jpegd_writel(jpegd, SUNXI_VE_TOP_OUTPUT_FORMAT, 0x33);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_TOP_CHROMA_BUF_LEN0,
            chroma_size | RT_BIT(29) | (3U << 30));
    sunxi_jpegd_writel(jpegd, SUNXI_VE_TOP_PRI_CHROMA_BUF_LEN, chroma_size);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_TOP_PRI_BUF_LINE_STRIDE,
            ((rt_uint32_t)(stride >> 1) << 16) | stride);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_TOP_SEC_BUF_LINE_STRIDE,
            ((rt_uint32_t)(stride >> 1) << 16) | stride);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_JPEG_LUMA,
            output->buffer.phys_addr);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_JPEG_CHROMA,
            output->buffer.phys_addr + luma_size);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_JPEG_SCALE, 0);

    *out_stride = stride;
    *out_luma_size = luma_size;
    *out_size = luma_size + chroma_size * 2;

    return RT_EOK;
}

static void sunxi_jpegd_write_huffman_header(struct sunxi_jpegd *jpegd,
        const struct sunxi_jpegd_huffman_table *table)
{
    rt_uint16_t start_code[16];
    rt_uint8_t offset[16];
    rt_uint32_t code;
    rt_uint32_t count;
    rt_uint32_t value;
    int i;

    code = 0;
    count = 0;
    for (i = 0; i < RT_ARRAY_SIZE(start_code); i++)
    {
        start_code[i] = code;
        offset[i] = count;
        count += table->counts[i];
        code = (code + table->counts[i]) << 1;
    }
    for (i = RT_ARRAY_SIZE(start_code) - 1; i >= 0 && !table->counts[i]; i--)
    {
        start_code[i] = 0xffff;
    }

    for (i = 0; i < 8; i++)
    {
        value = start_code[i * 2] | ((rt_uint32_t)start_code[i * 2 + 1] << 16);
        sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_SRAM_DATA, value);
    }
    for (i = 0; i < 4; i++)
    {
        value = offset[i * 4] | ((rt_uint32_t)offset[i * 4 + 1] << 8) |
                ((rt_uint32_t)offset[i * 4 + 2] << 16) |
                ((rt_uint32_t)offset[i * 4 + 3] << 24);
        sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_SRAM_DATA, value);
    }
    for (i = 0; i < 4; i++)
    {
        sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_SRAM_DATA, 0);
    }
}

static void sunxi_jpegd_write_huffman_data(struct sunxi_jpegd *jpegd,
        const struct sunxi_jpegd_huffman_table *table)
{
    rt_uint32_t value;
    int i;
    int j;

    for (i = 0; i < 64; i++)
    {
        value = 0;
        for (j = 0; j < 4; j++)
        {
            if ((rt_uint16_t)(i * 4 + j) < table->symbol_count)
            {
                value |= (rt_uint32_t)table->symbols[i * 4 + j] << (j * 8);
            }
        }
        sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_SRAM_DATA, value);
    }
}

static void sunxi_jpegd_write_huffman_tables(struct sunxi_jpegd *jpegd,
        const struct sunxi_jpegd_header *header)
{
    const struct sunxi_jpegd_component *y = &header->component[0];
    const struct sunxi_jpegd_component *c = &header->component[1];
    const struct sunxi_jpegd_huffman_table *table[4];
    int i;

    table[0] = &header->huffman[0][y->dc_table];
    table[1] = &header->huffman[1][y->ac_table];
    table[2] = &header->huffman[0][c->dc_table];
    table[3] = &header->huffman[1][c->ac_table];

    sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_SRAM_OFFSET, 0);
    for (i = 0; i < RT_ARRAY_SIZE(table); i++)
    {
        sunxi_jpegd_write_huffman_header(jpegd, table[i]);
    }
    for (i = 0; i < 192; i++)
    {
        sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_SRAM_DATA, 0);
    }
    for (i = 0; i < RT_ARRAY_SIZE(table); i++)
    {
        sunxi_jpegd_write_huffman_data(jpegd, table[i]);
    }
}

static void sunxi_jpegd_write_quant_table(struct sunxi_jpegd *jpegd,
        const struct sunxi_jpegd_quant_table *table, rt_uint32_t flags)
{
    rt_uint32_t value;
    int i;

    for (i = 0; i < RT_ARRAY_SIZE(table->value); i++)
    {
        value = ((rt_uint32_t)i << 8) | table->value[i] | flags;
        sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_IQ_INPUT, value);
    }
}

static rt_err_t sunxi_jpege_header_put(struct sunxi_jpege_header *header,
        const void *data, rt_size_t size)
{
    if (size > sizeof(header->data) - header->size)
    {
        return -RT_ENOMEM;
    }

    rt_memcpy(header->data + header->size, data, size);
    header->size += size;

    return RT_EOK;
}

static rt_err_t sunxi_jpege_header_put_u8(struct sunxi_jpege_header *header,
        rt_uint8_t value)
{
    return sunxi_jpege_header_put(header, &value, sizeof(value));
}

static rt_err_t sunxi_jpege_header_put_be16(struct sunxi_jpege_header *header,
        rt_uint16_t value)
{
    rt_uint8_t data[2];

    data[0] = value >> 8;
    data[1] = value;

    return sunxi_jpege_header_put(header, data, sizeof(data));
}

static void sunxi_jpege_scale_quant_table(rt_uint16_t *scaled,
        const rt_uint8_t *base, rt_uint8_t quality)
{
    rt_uint32_t scale;
    rt_uint32_t value;
    int i;

    scale = quality < 50 ? 5000 / quality : 200 - quality * 2;
    for (i = 0; i < 64; i++)
    {
        value = (base[i] * scale + 50) / 100;
        scaled[i] = value < 1 ? 1 : (value > 255 ? 255 : value);
    }
}

static rt_err_t sunxi_jpege_write_dht(struct sunxi_jpege_header *header,
        rt_uint8_t table_id, const rt_uint8_t *counts,
        const rt_uint8_t *values, rt_size_t value_count)
{
    rt_err_t err;

    err = sunxi_jpege_header_put_u8(header, table_id);
    if (err)
    {
        return err;
    }
    err = sunxi_jpege_header_put(header, counts, 16);
    if (err)
    {
        return err;
    }

    return sunxi_jpege_header_put(header, values, value_count);
}

static rt_err_t sunxi_jpege_build_header(struct sunxi_jpege_header *header,
        rt_uint16_t width, rt_uint16_t height, rt_uint16_t *luma_quant,
        rt_uint16_t *chroma_quant)
{
    static const rt_uint8_t sof0[] =
    {
        0xff, 0xc0, 0x00, 0x11, 0x08,
    };
    static const rt_uint8_t components[] =
    {
        0x03, 0x01, 0x22, 0x00, 0x02, 0x11, 0x01, 0x03, 0x11, 0x01,
    };
    static const rt_uint8_t sos[] =
    {
        0xff, 0xda, 0x00, 0x0c, 0x03, 0x01, 0x00, 0x02,
        0x11, 0x03, 0x11, 0x00, 0x3f, 0x00,
    };
    rt_err_t err;
    int i;

    header->size = 0;
    err = sunxi_jpege_header_put_be16(header, 0xffd8);
    if (err)
    {
        return err;
    }
    err = sunxi_jpege_header_put_be16(header, 0xffdb);
    if (err)
    {
        return err;
    }
    err = sunxi_jpege_header_put_be16(header, 2 + 2 * (1 + 64));
    if (err)
    {
        return err;
    }
    err = sunxi_jpege_header_put_u8(header, 0);
    if (err)
    {
        return err;
    }
    for (i = 0; i < 64; i++)
    {
        err = sunxi_jpege_header_put_u8(header,
                luma_quant[sunxi_jpege_zigzag[i]]);
        if (err)
        {
            return err;
        }
    }
    err = sunxi_jpege_header_put_u8(header, 1);
    if (err)
    {
        return err;
    }
    for (i = 0; i < 64; i++)
    {
        err = sunxi_jpege_header_put_u8(header,
                chroma_quant[sunxi_jpege_zigzag[i]]);
        if (err)
        {
            return err;
        }
    }
    err = sunxi_jpege_header_put(header, sof0, sizeof(sof0));
    if (err)
    {
        return err;
    }
    err = sunxi_jpege_header_put_be16(header, height);
    if (err)
    {
        return err;
    }
    err = sunxi_jpege_header_put_be16(header, width);
    if (err)
    {
        return err;
    }
    err = sunxi_jpege_header_put(header, components, sizeof(components));
    if (err)
    {
        return err;
    }
    err = sunxi_jpege_header_put_be16(header, 0xffc4);
    if (err)
    {
        return err;
    }
    err = sunxi_jpege_header_put_be16(header, 0x01a2);
    if (err)
    {
        return err;
    }
    err = sunxi_jpege_write_dht(header, 0x00,
            sunxi_jpegd_default_dc_luma_counts,
            sunxi_jpegd_default_dc_values,
            sizeof(sunxi_jpegd_default_dc_values));
    if (err)
    {
        return err;
    }
    err = sunxi_jpege_write_dht(header, 0x10,
            sunxi_jpegd_default_ac_luma_counts,
            sunxi_jpegd_default_ac_luma_values,
            sizeof(sunxi_jpegd_default_ac_luma_values));
    if (err)
    {
        return err;
    }
    err = sunxi_jpege_write_dht(header, 0x01,
            sunxi_jpegd_default_dc_chroma_counts,
            sunxi_jpegd_default_dc_values,
            sizeof(sunxi_jpegd_default_dc_values));
    if (err)
    {
        return err;
    }
    err = sunxi_jpege_write_dht(header, 0x11,
            sunxi_jpegd_default_ac_chroma_counts,
            sunxi_jpegd_default_ac_chroma_values,
            sizeof(sunxi_jpegd_default_ac_chroma_values));
    if (err)
    {
        return err;
    }

    return sunxi_jpege_header_put(header, sos, sizeof(sos));
}

static void sunxi_jpege_write_quant_tables(struct sunxi_jpegd *jpegd,
        const rt_uint16_t *luma_quant, const rt_uint16_t *chroma_quant)
{
    rt_uint32_t value;
    rt_uint16_t quant;
    int i;

    sunxi_jpegd_writel(jpegd, SUNXI_VE_AVC_SRAM_OFFSET, 0);
    for (i = 0; i < 128; i++)
    {
        quant = i < 64 ? luma_quant[i] : chroma_quant[i - 64];
        value = ((quant + 1) / 2 << 16) | (0xffff / quant);
        sunxi_jpegd_writel(jpegd, SUNXI_VE_AVC_SRAM_DATA, value);
    }
}

static struct sunxi_jpegd_buffer_entry *sunxi_jpegd_find_buffer(
        struct sunxi_jpegd *jpegd, const struct sunxi_jpegd_buffer *buffer)
{
    struct sunxi_jpegd_buffer_entry *entry;

    if (!buffer)
    {
        return RT_NULL;
    }

    rt_list_for_each_entry(entry, &jpegd->buffers, list)
    {
        if (entry->buffer.virt_addr == buffer->virt_addr &&
            entry->buffer.phys_addr == buffer->phys_addr &&
            entry->buffer.size == buffer->size)
        {
            return entry;
        }
    }

    return RT_NULL;
}

static rt_err_t sunxi_jpegd_alloc_buffer(struct sunxi_jpegd *jpegd,
        struct sunxi_jpegd_buffer *buffer)
{
    struct sunxi_jpegd_buffer_entry *entry;
    rt_ubase_t physical;
    rt_size_t allocated;
    rt_size_t offset;

    if (!buffer || !buffer->size || buffer->size > (rt_size_t)-1 -
        SUNXI_JPEGD_BUFFER_ALIGN)
    {
        return -RT_EINVAL;
    }

    entry = rt_calloc(1, sizeof(*entry));
    if (!entry)
    {
        return -RT_ENOMEM;
    }

    allocated = buffer->size + SUNXI_JPEGD_BUFFER_ALIGN - 1;
    LOG_D("alloc DMA buffer: requested=%u allocated=%u", (rt_uint32_t)buffer->size,
            (rt_uint32_t)allocated);
    entry->alloc_addr = rt_dma_alloc_coherent(jpegd->dev, allocated, &physical);
    if (!entry->alloc_addr)
    {
        rt_free(entry);
        return -RT_ENOMEM;
    }

    offset = RT_ALIGN(physical, SUNXI_JPEGD_BUFFER_ALIGN) - physical;
    entry->alloc_phys = physical;
    entry->alloc_size = allocated;
    entry->buffer.virt_addr = (rt_uint8_t *)entry->alloc_addr + offset;
    entry->buffer.phys_addr = physical + offset;
    entry->buffer.size = buffer->size;
    *buffer = entry->buffer;
    rt_list_insert_before(&jpegd->buffers, &entry->list);
    LOG_D("DMA buffer: va=%p pa=0x%08x", entry->buffer.virt_addr,
            (rt_uint32_t)entry->buffer.phys_addr);

    return RT_EOK;
}

static rt_err_t sunxi_jpegd_free_buffer(struct sunxi_jpegd *jpegd,
        struct sunxi_jpegd_buffer *buffer)
{
    struct sunxi_jpegd_buffer_entry *entry;

    entry = sunxi_jpegd_find_buffer(jpegd, buffer);
    if (!entry)
    {
        return -RT_EINVAL;
    }

    rt_list_remove(&entry->list);
    rt_dma_free_coherent(jpegd->dev, entry->alloc_size, entry->alloc_addr,
            entry->alloc_phys);
    rt_memset(buffer, 0, sizeof(*buffer));
    rt_free(entry);

    return RT_EOK;
}

static rt_err_t sunxi_jpegd_reset(struct sunxi_jpegd *jpegd)
{
    rt_err_t err;

    sunxi_jpegd_writel(jpegd, SUNXI_VE_MODE, SUNXI_VE_MODE_DISABLED);
    err = rt_reset_control_assert(jpegd->resets);
    if (err)
    {
        LOG_E("VE reset assert failed: %d", err);
        return err;
    }
    rt_hw_us_delay(1);

    err = rt_reset_control_deassert(jpegd->resets);
    if (err)
    {
        LOG_E("VE reset deassert failed: %d", err);
    }

    return err;
}

static rt_err_t sunxi_jpegd_get_info(struct sunxi_jpegd *jpegd,
        struct sunxi_jpegd_info *info)
{
    struct sunxi_jpegd_header header;
    struct sunxi_jpegd_buffer_entry *input;
    rt_uint32_t sampling;
    rt_size_t stride;
    rt_size_t aligned_height;
    rt_size_t luma_size;
    rt_err_t err;

    if (!info || !info->input || !info->input_size ||
        info->input_size > info->input->size)
    {
        return -RT_EINVAL;
    }

    input = sunxi_jpegd_find_buffer(jpegd, info->input);
    if (!input)
    {
        return -RT_EINVAL;
    }

    err = sunxi_jpegd_parse_header(input->buffer.virt_addr,
            info->input_size, &header);
    if (err)
    {
        LOG_E("unsupported JPEG header: %d", err);
        return err;
    }
    if ((err = sunxi_jpegd_sampling(&header, &sampling)) != RT_EOK)
    {
        return err;
    }
    if (sampling != SUNXI_VE_MPEG_TRIGGER_420)
    {
        return -RT_ENOSYS;
    }

    stride = RT_ALIGN(header.width, 32);
    aligned_height = RT_ALIGN(header.height, 32);
    luma_size = stride * aligned_height;

    info->width = header.width;
    info->height = header.height;
    info->stride = stride;
    /* The F101 VE stores JPEG 4:2:0 reconstruction surfaces as MB32. */
    info->format = SUNXI_JPEGD_FORMAT_MB32_420;
    info->luma_size = luma_size;
    info->output_size = luma_size + stride * aligned_height / 2;

    LOG_D("JPEG info: input=%u output=%u stride=%u sampling=%08x",
            (rt_uint32_t)info->input_size, (rt_uint32_t)info->output_size,
            (rt_uint32_t)stride, sampling);

    return RT_EOK;
}

#ifdef RT_SOC_SUNXI_PNG_DEC
struct sunxi_pngd_header
{
    rt_uint32_t width;
    rt_uint32_t height;
    rt_uint8_t bit_depth;
    rt_uint8_t color_type;
    rt_uint8_t compression;
    rt_uint8_t filter;
    rt_uint8_t interlace;
};

static rt_uint32_t sunxi_pngd_read_be32(const rt_uint8_t *data)
{
    return ((rt_uint32_t)data[0] << 24) |
            ((rt_uint32_t)data[1] << 16) |
            ((rt_uint32_t)data[2] << 8) | data[3];
}

static rt_err_t sunxi_pngd_parse_header(const void *data, rt_size_t size,
        struct sunxi_pngd_header *header)
{
    static const rt_uint8_t signature[] =
    {
        0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a,
    };
    const rt_uint8_t *png = data;

    if (!data || !header || size < 33 ||
        rt_memcmp(png, signature, sizeof(signature)) ||
        sunxi_pngd_read_be32(png + 8) != 13 ||
        rt_memcmp(png + 12, "IHDR", 4))
    {
        return -RT_EINVAL;
    }

    header->width = sunxi_pngd_read_be32(png + 16);
    header->height = sunxi_pngd_read_be32(png + 20);
    header->bit_depth = png[24];
    header->color_type = png[25];
    header->compression = png[26];
    header->filter = png[27];
    header->interlace = png[28];
    if (!header->width || !header->height || header->bit_depth != 8 ||
        (header->color_type != 2 && header->color_type != 6) ||
        header->compression || header->filter || header->interlace)
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static rt_err_t sunxi_pngd_get_info(struct sunxi_jpegd *jpegd,
        struct sunxi_pngd_info *info)
{
    struct sunxi_jpegd_buffer_entry *input;
    struct sunxi_pngd_header header;
    rt_size_t stride;
    rt_err_t err;

    if (!info || !info->input || !info->input_size ||
        info->input_size > info->input->size)
    {
        return -RT_EINVAL;
    }

    input = sunxi_jpegd_find_buffer(jpegd, info->input);
    if (!input)
    {
        return -RT_EINVAL;
    }

    err = sunxi_pngd_parse_header(input->buffer.virt_addr, info->input_size,
            &header);
    if (err)
    {
        return err;
    }
    if (header.width > (rt_size_t)-1 / 4)
    {
        return -RT_EINVAL;
    }

    stride = header.width * 4;
    if (header.height > (rt_size_t)-1 / stride)
    {
        return -RT_EINVAL;
    }

    info->width = header.width;
    info->height = header.height;
    info->stride = stride;
    info->format = SUNXI_PNGD_FORMAT_RGBA8888;
    info->output_size = stride * header.height;

    return RT_EOK;
}

static rt_err_t sunxi_pngd_decode(struct sunxi_jpegd *jpegd,
        struct sunxi_pngd_decode *request)
{
    struct sunxi_jpegd_buffer_entry *input;
    struct sunxi_jpegd_buffer_entry *output;
    struct sunxi_pngd_header header;
    rt_size_t stride;
    rt_size_t output_size;
    rt_tick_t timeout;
    rt_err_t err;

    if (!request || !request->input || !request->output ||
        !request->input_size || request->input_size > request->input->size)
    {
        return -RT_EINVAL;
    }

    input = sunxi_jpegd_find_buffer(jpegd, request->input);
    output = sunxi_jpegd_find_buffer(jpegd, request->output);
    if (!input || !output || input == output)
    {
        return -RT_EINVAL;
    }

    err = sunxi_pngd_parse_header(input->buffer.virt_addr,
            request->input_size, &header);
    if (err)
    {
        return err;
    }
    if (header.width > (rt_size_t)-1 / 4)
    {
        return -RT_EINVAL;
    }
    stride = header.width * 4;
    if (header.height > (rt_size_t)-1 / stride)
    {
        return -RT_EINVAL;
    }
    output_size = stride * header.height;
    if (output->buffer.size < output_size)
    {
        return -RT_ENOMEM;
    }

    if ((err = sunxi_jpegd_reset(jpegd)) != RT_EOK)
    {
        return err;
    }

    sunxi_jpegd_writel(jpegd, SUNXI_VE_MODE, SUNXI_VE_MODE_DEC_PNG);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_PNG_INT_STATUS, SUNXI_VE_PNG_INT_MASK);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_PNG_RX_ADDR, input->buffer.phys_addr);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_PNG_RX_LEN, request->input_size);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_PNG_TX_ADDR, output->buffer.phys_addr);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_PNG_INT_EN, SUNXI_VE_PNG_INT_MASK);

    jpegd->engine = SUNXI_JPEGD_ENGINE_PNG_DECODE;
    jpegd->running = RT_TRUE;
    jpegd->error = RT_EOK;
    jpegd->irq_status = 0;
    rt_completion_init(&jpegd->completion);
    rt_hw_dsb();
    sunxi_jpegd_writel(jpegd, SUNXI_VE_PNG_CTRL, SUNXI_VE_PNG_CTRL_START);

    timeout = request->timeout ? request->timeout :
            rt_tick_from_millisecond(SUNXI_PNGD_DEFAULT_TIMEOUT_MS);
    err = rt_completion_wait(&jpegd->completion, timeout);
    jpegd->running = RT_FALSE;
    jpegd->engine = SUNXI_JPEGD_ENGINE_IDLE;
    if (err)
    {
        LOG_E("PNG decode timed out, status=%08x control=%08x",
                sunxi_jpegd_readl(jpegd, SUNXI_VE_PNG_STATUS),
                sunxi_jpegd_readl(jpegd, SUNXI_VE_PNG_CTRL));
        sunxi_jpegd_reset(jpegd);
        return -RT_ETIMEOUT;
    }
    if (jpegd->error)
    {
        return jpegd->error;
    }

    request->width = header.width;
    request->height = header.height;
    request->stride = stride;
    request->format = SUNXI_PNGD_FORMAT_RGBA8888;

    return RT_EOK;
}

#endif /* RT_SOC_SUNXI_PNG_DEC */

static rt_err_t sunxi_jpegd_decode(struct sunxi_jpegd *jpegd,
        struct sunxi_jpegd_decode *request)
{
    struct sunxi_jpegd_header header;
    struct sunxi_jpegd_buffer_entry *input;
    struct sunxi_jpegd_buffer_entry *output;
    rt_uint32_t sampling;
    rt_uint32_t ctrl;
    rt_uint32_t address;
    rt_size_t stride;
    rt_size_t luma_size;
    rt_size_t output_size;
    rt_tick_t timeout;
    rt_err_t err;

    if (!request || !request->input || !request->output ||
        !request->input_size || request->input_size > request->input->size)
    {
        return -RT_EINVAL;
    }

    input = sunxi_jpegd_find_buffer(jpegd, request->input);
    output = sunxi_jpegd_find_buffer(jpegd, request->output);
    if (!input || !output)
    {
        return -RT_EINVAL;
    }

    err = sunxi_jpegd_parse_header(input->buffer.virt_addr,
            request->input_size, &header);
    if (err)
    {
        LOG_E("unsupported JPEG header: %d", err);
        return err;
    }
    if ((err = sunxi_jpegd_sampling(&header, &sampling)) != RT_EOK)
    {
        return err;
    }

    if ((err = sunxi_jpegd_reset(jpegd)) != RT_EOK)
    {
        return err;
    }

    sunxi_jpegd_writel(jpegd, SUNXI_VE_MODE, SUNXI_VE_MODE_DEC_MPEG);
    if ((err = sunxi_jpegd_configure_output(jpegd, &header, sampling, output,
            &stride, &luma_size, &output_size)) != RT_EOK)
    {
        return err;
    }
    sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_TRIGGER,
            SUNXI_VE_MPEG_TRIGGER_JPEG | sampling);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_JPEG_RESTART,
            header.restart_interval);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_JPEG_SIZE,
            (((RT_ALIGN(header.height, 8 * header.component[0].vfactor) /
                    (8 * header.component[0].vfactor)) - 1) << 16) |
            ((RT_ALIGN(header.width, 8 * header.component[0].hfactor) /
                    (8 * header.component[0].hfactor)) - 1));
    sunxi_jpegd_write_quant_table(jpegd,
            &header.quant[header.component[0].quant_table],
            SUNXI_VE_MPEG_IQ_LUMA);
    sunxi_jpegd_write_quant_table(jpegd,
            &header.quant[header.component[1].quant_table], 0);
    sunxi_jpegd_write_huffman_tables(jpegd, &header);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_VLD_OFFSET,
            header.entropy_offset * 8);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_VLD_LENGTH,
            (input->buffer.size - header.entropy_offset) * 8);
    /*
     * Unlike older VE generations, F101 takes the unmodified physical
     * address here.  The input buffer is a 1 KiB-aligned VLD ring.
     */
    address = input->buffer.phys_addr | SUNXI_VE_MPEG_VLD_FIRST |
            SUNXI_VE_MPEG_VLD_LAST | SUNXI_VE_MPEG_VLD_VALID;
    sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_VLD_ADDR, address);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_VLD_END,
            input->buffer.phys_addr + input->buffer.size - 1);

    LOG_D("decode: input=%p/0x%08x size=%u output=%p/0x%08x size=%u vld=%08x..%08x",
            input->buffer.virt_addr, (rt_uint32_t)input->buffer.phys_addr,
            (rt_uint32_t)request->input_size, output->buffer.virt_addr,
            (rt_uint32_t)output->buffer.phys_addr, (rt_uint32_t)output_size,
            address, (rt_uint32_t)(input->buffer.phys_addr + input->buffer.size - 1));

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, input->buffer.virt_addr,
            request->input_size);
    rt_hw_cpu_dcache_clean_and_invalidate(output->buffer.virt_addr, output_size);

    ctrl = SUNXI_VE_MPEG_CTRL_F101_420;
    jpegd->engine = SUNXI_JPEGD_ENGINE_DECODE;
    jpegd->running = RT_TRUE;
    jpegd->error = RT_EOK;
    jpegd->irq_status = 0;
    rt_completion_init(&jpegd->completion);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_STATUS, SUNXI_VE_MPEG_STATUS_MASK);
    rt_hw_dsb();
    sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_CTRL, ctrl);
    rt_hw_dsb();
    sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_TRIGGER,
            SUNXI_VE_MPEG_TRIGGER_JPEG | sampling |
            SUNXI_VE_MPEG_TRIGGER_JPEG_VLD);

    timeout = request->timeout ? request->timeout :
            rt_tick_from_millisecond(SUNXI_JPEGD_DEFAULT_TIMEOUT_MS);
    err = rt_completion_wait(&jpegd->completion, timeout);
    jpegd->running = RT_FALSE;
    jpegd->engine = SUNXI_JPEGD_ENGINE_IDLE;
    if (err)
    {
        LOG_E("decode timed out: mode=%08x status=%08x control=%08x vld=%08x offset=%08x length=%08x end=%08x",
                sunxi_jpegd_readl(jpegd, SUNXI_VE_MODE),
                sunxi_jpegd_readl(jpegd, SUNXI_VE_MPEG_STATUS),
                sunxi_jpegd_readl(jpegd, SUNXI_VE_MPEG_CTRL),
                sunxi_jpegd_readl(jpegd, SUNXI_VE_MPEG_VLD_ADDR),
                sunxi_jpegd_readl(jpegd, SUNXI_VE_MPEG_VLD_OFFSET),
                sunxi_jpegd_readl(jpegd, SUNXI_VE_MPEG_VLD_LENGTH),
                sunxi_jpegd_readl(jpegd, SUNXI_VE_MPEG_VLD_END));
        sunxi_jpegd_reset(jpegd);
        return -RT_ETIMEOUT;
    }
    if (jpegd->error)
    {
        LOG_E("decode failed: status=%08x control=%08x",
                jpegd->irq_status,
                sunxi_jpegd_readl(jpegd, SUNXI_VE_MPEG_CTRL));
        return jpegd->error;
    }

    request->width = header.width;
    request->height = header.height;
    request->stride = stride;
    request->format = SUNXI_JPEGD_FORMAT_MB32_420;
    request->luma_size = luma_size;

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, output->buffer.virt_addr,
            output_size);

    LOG_D("decode complete: irq=%08x status=%08x", jpegd->irq_status,
            sunxi_jpegd_readl(jpegd, SUNXI_VE_MPEG_STATUS));

    return RT_EOK;
}

static rt_err_t sunxi_jpege_encode(struct sunxi_jpegd *jpegd,
        struct sunxi_jpege_encode *request)
{
    struct sunxi_jpegd_buffer_entry *input;
    struct sunxi_jpegd_buffer_entry *output;
    struct sunxi_jpege_header header;
    rt_uint16_t luma_quant[64];
    rt_uint16_t chroma_quant[64];
    rt_size_t aligned_height;
    rt_size_t luma_size;
    rt_size_t input_size;
    rt_size_t bitstream_size;
    rt_size_t encoded_size;
    rt_uint32_t width_mb;
    rt_uint32_t height_mb;
    rt_uint32_t jpeg_ctrl;
    rt_uint32_t bit_length;
    rt_tick_t timeout;
    rt_uint8_t quality;
    rt_err_t err;

    if (!request || !request->input || !request->output || !request->width ||
        !request->height || request->width > SUNXI_JPEGE_MAX_WIDTH ||
        request->height > SUNXI_JPEGE_MAX_HEIGHT ||
        request->format != SUNXI_JPEGD_FORMAT_NV12)
    {
        return -RT_EINVAL;
    }

    input = sunxi_jpegd_find_buffer(jpegd, request->input);
    output = sunxi_jpegd_find_buffer(jpegd, request->output);
    if (!input || !output || input == output ||
        (input->buffer.phys_addr & (SUNXI_JPEGD_BUFFER_ALIGN - 1)) ||
        (output->buffer.phys_addr & (SUNXI_JPEGD_BUFFER_ALIGN - 1)))
    {
        return -RT_EINVAL;
    }

    if (request->stride < RT_ALIGN(request->width, 16) ||
        request->stride & 15)
    {
        return -RT_EINVAL;
    }

    aligned_height = RT_ALIGN(request->height, 16);
    luma_size = request->stride * aligned_height;
    input_size = luma_size + luma_size / 2;
    if (input->buffer.size < input_size)
    {
        return -RT_ENOMEM;
    }

    bitstream_size = output->buffer.size & ~(SUNXI_JPEGE_MIN_OUTPUT_SIZE - 1);
    if (bitstream_size < SUNXI_JPEGE_MIN_OUTPUT_SIZE)
    {
        return -RT_ENOMEM;
    }

    quality = request->quality ? request->quality : 75;
    if (quality > 100)
    {
        return -RT_EINVAL;
    }
    sunxi_jpege_scale_quant_table(luma_quant, sunxi_jpege_luma_quant, quality);
    sunxi_jpege_scale_quant_table(chroma_quant, sunxi_jpege_chroma_quant,
            quality);
    err = sunxi_jpege_build_header(&header, request->width, request->height,
            luma_quant, chroma_quant);
    if (err)
    {
        return err;
    }
    if (header.size + 2 > bitstream_size)
    {
        return -RT_ENOMEM;
    }
    rt_memcpy(output->buffer.virt_addr, header.data, header.size);

    if ((err = sunxi_jpegd_reset(jpegd)) != RT_EOK)
    {
        return err;
    }

    width_mb = request->stride / 16;
    height_mb = aligned_height / 16;
    sunxi_jpegd_writel(jpegd, SUNXI_VE_MODE, SUNXI_VE_MODE_ENC_AVC |
            SUNXI_VE_MODE_ENC_ISP | SUNXI_VE_MODE_ENC_AVC_ENABLE |
            SUNXI_VE_MODE_REC_WR_MODE_2MB | SUNXI_VE_MODE_DDR_MODE_BW_128);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_ISP_INPUT_SIZE,
            (width_mb << 16) | height_mb);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_ISP_INPUT_STRIDE,
            (width_mb << 16) | width_mb);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_ISP_CTRL, 0);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_ISP_INPUT_LUMA,
            input->buffer.phys_addr);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_ISP_INPUT_CHROMA,
            input->buffer.phys_addr + luma_size);
    sunxi_jpege_write_quant_tables(jpegd, luma_quant, chroma_quant);

    jpeg_ctrl = SUNXI_VE_AVC_JPEG_FILL_ONE | SUNXI_VE_AVC_JPEG_BYTE_STUFF |
            (((0x400 / chroma_quant[0]) & 0x7ff) << 16) |
            ((0x400 / luma_quant[0]) & 0x7ff);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_AVC_JPEG_CTRL, jpeg_ctrl);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_AVC_VLE_ADDR,
            output->buffer.phys_addr);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_AVC_VLE_END,
            output->buffer.phys_addr + bitstream_size - 1);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_AVC_VLE_OFFSET, header.size * 8);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_AVC_VLE_MAX, bitstream_size * 8);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_AVC_STATUS, SUNXI_VE_AVC_STATUS_MASK);
    sunxi_jpegd_writel(jpegd, SUNXI_VE_AVC_CTRL, SUNXI_VE_AVC_CTRL_IRQ_ENABLE);

    jpegd->engine = SUNXI_JPEGD_ENGINE_ENCODE;
    jpegd->running = RT_TRUE;
    jpegd->error = RT_EOK;
    jpegd->irq_status = 0;
    rt_completion_init(&jpegd->completion);
    rt_hw_dsb();
    sunxi_jpegd_writel(jpegd, SUNXI_VE_AVC_TRIGGER,
            SUNXI_VE_AVC_TRIGGER_JPEG | SUNXI_VE_AVC_TRIGGER_LAUNCH);

    timeout = request->timeout ? request->timeout :
            rt_tick_from_millisecond(SUNXI_JPEGD_DEFAULT_TIMEOUT_MS);
    err = rt_completion_wait(&jpegd->completion, timeout);
    jpegd->running = RT_FALSE;
    jpegd->engine = SUNXI_JPEGD_ENGINE_IDLE;
    if (err)
    {
        LOG_E("encode timed out, status=%08x", sunxi_jpegd_readl(jpegd,
                SUNXI_VE_AVC_STATUS));
        sunxi_jpegd_reset(jpegd);
        return -RT_ETIMEOUT;
    }
    if (jpegd->error)
    {
        return jpegd->error;
    }

    bit_length = sunxi_jpegd_readl(jpegd, SUNXI_VE_AVC_VLE_LENGTH);
    encoded_size = (bit_length + 7) / 8;
    if (encoded_size <= header.size || encoded_size + 2 > bitstream_size)
    {
        LOG_E("invalid encoded bit length: %u", bit_length);
        return -RT_EIO;
    }
    if (((rt_uint8_t *)output->buffer.virt_addr)[encoded_size - 2] == 0xff &&
        ((rt_uint8_t *)output->buffer.virt_addr)[encoded_size - 1] == 0xd9)
    {
        request->output_size = encoded_size;
    }
    else
    {
        ((rt_uint8_t *)output->buffer.virt_addr)[encoded_size] = 0xff;
        ((rt_uint8_t *)output->buffer.virt_addr)[encoded_size + 1] = 0xd9;
        request->output_size = encoded_size + 2;
    }

    return RT_EOK;
}

static rt_err_t sunxi_jpegd_control(rt_device_t dev, int cmd, void *args)
{
    struct sunxi_jpegd *jpegd = raw_to_sunxi_jpegd(dev);
    rt_err_t err;

    if (cmd == SUNXI_JPEGD_CMD_ALLOC_BUFFER)
    {
        LOG_D("allocate request: waiting for decoder lock");
    }
    rt_mutex_take(&jpegd->lock, RT_WAITING_FOREVER);
    if (cmd == SUNXI_JPEGD_CMD_ALLOC_BUFFER)
    {
        LOG_D("allocate request: decoder lock acquired");
    }
    switch (cmd)
    {
    case SUNXI_JPEGD_CMD_ALLOC_BUFFER:
        err = sunxi_jpegd_alloc_buffer(jpegd, args);
        break;
    case SUNXI_JPEGD_CMD_FREE_BUFFER:
        err = jpegd->running ? -RT_EBUSY : sunxi_jpegd_free_buffer(jpegd, args);
        break;
    case SUNXI_JPEGD_CMD_DECODE:
        err = jpegd->running ? -RT_EBUSY : sunxi_jpegd_decode(jpegd, args);
        break;
    case SUNXI_JPEGD_CMD_GET_INFO:
        err = jpegd->running ? -RT_EBUSY : sunxi_jpegd_get_info(jpegd, args);
        break;
    case SUNXI_JPEGD_CMD_GET_VERSION:
        if (!args)
        {
            err = -RT_EINVAL;
        }
        else
        {
            *(rt_uint32_t *)args = jpegd->version;
            err = RT_EOK;
        }
        break;
    default:
        err = -RT_ENOSYS;
        break;
    }
    rt_mutex_release(&jpegd->lock);

    return err;
}

static rt_err_t sunxi_jpege_control(rt_device_t dev, int cmd, void *args)
{
    struct sunxi_jpegd *jpegd = raw_to_sunxi_jpege(dev);
    rt_err_t err;

    rt_mutex_take(&jpegd->lock, RT_WAITING_FOREVER);
    switch (cmd)
    {
    case SUNXI_JPEGE_CMD_ALLOC_BUFFER:
        err = sunxi_jpegd_alloc_buffer(jpegd, args);
        break;
    case SUNXI_JPEGE_CMD_FREE_BUFFER:
        err = jpegd->running ? -RT_EBUSY : sunxi_jpegd_free_buffer(jpegd, args);
        break;
    case SUNXI_JPEGE_CMD_ENCODE:
        err = jpegd->running ? -RT_EBUSY : sunxi_jpege_encode(jpegd, args);
        break;
    case SUNXI_JPEGE_CMD_GET_VERSION:
        if (!args)
        {
            err = -RT_EINVAL;
        }
        else
        {
            *(rt_uint32_t *)args = jpegd->version;
            err = RT_EOK;
        }
        break;
    default:
        err = -RT_ENOSYS;
        break;
    }
    rt_mutex_release(&jpegd->lock);

    return err;
}

#ifdef RT_SOC_SUNXI_PNG_DEC
static rt_err_t sunxi_pngd_control(rt_device_t dev, int cmd, void *args)
{
    struct sunxi_jpegd *jpegd = raw_to_sunxi_pngd(dev);
    rt_err_t err;

    rt_mutex_take(&jpegd->lock, RT_WAITING_FOREVER);
    switch (cmd)
    {
    case SUNXI_PNGD_CMD_ALLOC_BUFFER:
        err = sunxi_jpegd_alloc_buffer(jpegd, args);
        break;
    case SUNXI_PNGD_CMD_FREE_BUFFER:
        err = jpegd->running ? -RT_EBUSY : sunxi_jpegd_free_buffer(jpegd, args);
        break;
    case SUNXI_PNGD_CMD_DECODE:
        err = jpegd->running ? -RT_EBUSY : sunxi_pngd_decode(jpegd, args);
        break;
    case SUNXI_PNGD_CMD_GET_INFO:
        err = jpegd->running ? -RT_EBUSY : sunxi_pngd_get_info(jpegd, args);
        break;
    case SUNXI_PNGD_CMD_GET_VERSION:
        if (!args)
        {
            err = -RT_EINVAL;
        }
        else
        {
            *(rt_uint32_t *)args = jpegd->version;
            err = RT_EOK;
        }
        break;
    default:
        err = -RT_ENOSYS;
        break;
    }
    rt_mutex_release(&jpegd->lock);

    return err;
}
#endif /* RT_SOC_SUNXI_PNG_DEC */

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops sunxi_jpegd_ops =
{
    .control = sunxi_jpegd_control,
};

static const struct rt_device_ops sunxi_jpege_ops =
{
    .control = sunxi_jpege_control,
};

#ifdef RT_SOC_SUNXI_PNG_DEC
static const struct rt_device_ops sunxi_pngd_ops =
{
    .control = sunxi_pngd_control,
};
#endif
#endif /* RT_USING_DEVICE_OPS */

static void sunxi_jpegd_isr(int irqno, void *parameter)
{
    struct sunxi_jpegd *jpegd = parameter;
    rt_uint32_t status;

    RT_UNUSED(irqno);

#ifdef RT_SOC_SUNXI_PNG_DEC
    if (jpegd->engine == SUNXI_JPEGD_ENGINE_PNG_DECODE)
    {
        status = sunxi_jpegd_readl(jpegd, SUNXI_VE_PNG_INT_STATUS) &
                SUNXI_VE_PNG_INT_MASK;
        if (!status)
        {
            return;
        }

        sunxi_jpegd_writel(jpegd, SUNXI_VE_PNG_INT_STATUS, status);
        jpegd->irq_status = status;
        if ((status & SUNXI_VE_PNG_INT_ERROR) ||
            !(status & SUNXI_VE_PNG_INT_DONE))
        {
            jpegd->error = -RT_EIO;
        }
        rt_completion_done(&jpegd->completion);
        return;
    }
#endif /* RT_SOC_SUNXI_PNG_DEC */

    if (jpegd->engine == SUNXI_JPEGD_ENGINE_ENCODE)
    {
        status = sunxi_jpegd_readl(jpegd, SUNXI_VE_AVC_STATUS) &
                SUNXI_VE_AVC_STATUS_MASK;
        if (!status)
        {
            return;
        }

        sunxi_jpegd_writel(jpegd, SUNXI_VE_AVC_STATUS, status);
        jpegd->irq_status = status;
        if (status & SUNXI_VE_AVC_STATUS_ERROR ||
            !(status & SUNXI_VE_AVC_STATUS_SUCCESS))
        {
            jpegd->error = -RT_EIO;
        }
        rt_completion_done(&jpegd->completion);
        return;
    }
    if (jpegd->engine != SUNXI_JPEGD_ENGINE_DECODE)
    {
        return;
    }

    status = sunxi_jpegd_readl(jpegd, SUNXI_VE_MPEG_STATUS) &
            SUNXI_VE_MPEG_STATUS_MASK;
    if (!status)
    {
        return;
    }

    sunxi_jpegd_writel(jpegd, SUNXI_VE_MPEG_STATUS, status);
    jpegd->irq_status = status;
    /* F101 reports JPEG completion with any of MPEG status bits 0..3. */
    rt_completion_done(&jpegd->completion);
}

static void sunxi_jpegd_release(struct sunxi_jpegd *jpegd)
{
    struct sunxi_jpegd_buffer_entry *entry;
    struct sunxi_jpegd_buffer_entry *next;

    rt_list_for_each_entry_safe(entry, next, &jpegd->buffers, list)
    {
        rt_list_remove(&entry->list);
        rt_dma_free_coherent(jpegd->dev, entry->alloc_size, entry->alloc_addr,
                entry->alloc_phys);
        rt_free(entry);
    }
    if (jpegd->png_registered)
    {
        rt_device_unregister(&jpegd->png_decoder);
    }
    if (jpegd->encoder_registered)
    {
        rt_device_unregister(&jpegd->encoder);
    }
    if (jpegd->device_registered)
    {
        rt_device_unregister(&jpegd->parent);
    }
    if (jpegd->lock_initialized)
    {
        rt_mutex_detach(&jpegd->lock);
    }
    if (!rt_is_err_or_null(jpegd->resets))
    {
        rt_reset_control_assert(jpegd->resets);
        rt_reset_control_put(jpegd->resets);
    }
    if (!rt_is_err_or_null(jpegd->clks))
    {
        if (jpegd->clocks_enabled)
        {
            rt_clk_array_disable_unprepare(jpegd->clks);
        }
        rt_clk_array_put(jpegd->clks);
    }
    if (jpegd->base)
    {
        rt_iounmap(jpegd->base);
    }
    rt_free(jpegd);
}

static rt_err_t sunxi_jpegd_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct sunxi_jpegd *jpegd;
    const char *decoder_name;
    const char *encoder_name;
#ifdef RT_SOC_SUNXI_PNG_DEC
    const char *png_name;
#endif
    rt_err_t err;

    jpegd = rt_calloc(1, sizeof(*jpegd));
    if (!jpegd)
    {
        return -RT_ENOMEM;
    }

    jpegd->dev = dev;
    jpegd->irq = -1;
    rt_list_init(&jpegd->buffers);
    jpegd->base = rt_dm_dev_iomap(dev, 0);
    if (!jpegd->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    if ((err = sunxi_jpegd_claim_sram(jpegd)) != RT_EOK)
    {
        LOG_E("failed to claim VE SRAM: %d", err);
        goto _fail;
    }

    jpegd->clks = rt_clk_get_array(dev);
    if (rt_is_err(jpegd->clks))
    {
        err = rt_ptr_err(jpegd->clks);
        goto _fail;
    }
    if ((err = rt_clk_array_prepare_enable(jpegd->clks)) != RT_EOK)
    {
        goto _fail;
    }
    jpegd->clocks_enabled = RT_TRUE;

    jpegd->resets = rt_reset_control_get_array(dev);
    if (rt_is_err(jpegd->resets))
    {
        err = rt_ptr_err(jpegd->resets);
        goto _fail;
    }
    if ((err = sunxi_jpegd_reset(jpegd)) != RT_EOK)
    {
        goto _fail;
    }

    jpegd->irq = rt_dm_dev_get_irq(dev, 0);
    if (jpegd->irq < 0)
    {
        err = jpegd->irq;
        goto _fail;
    }

    jpegd->version = sunxi_jpegd_readl(jpegd, SUNXI_VE_VERSION);
    rt_dm_dev_set_name_auto(&jpegd->parent, "jpegd");
    decoder_name = rt_dm_dev_get_name(&jpegd->parent);
    jpegd->parent.type = RT_Device_Class_Char;
    jpegd->parent.bus = dev->bus;
    jpegd->parent.ofw_node = dev->ofw_node;
#ifdef RT_USING_DEVICE_OPS
    jpegd->parent.ops = &sunxi_jpegd_ops;
#else
    jpegd->parent.control = sunxi_jpegd_control;
#endif
    if ((err = rt_mutex_init(&jpegd->lock, decoder_name, RT_IPC_FLAG_PRIO)) != RT_EOK)
    {
        goto _fail;
    }
    jpegd->lock_initialized = RT_TRUE;
    rt_completion_init(&jpegd->completion);
#ifdef RT_SOC_SUNXI_JPEG_DEC
    if ((err = rt_device_register(&jpegd->parent, decoder_name,
            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE)) != RT_EOK)
    {
        goto _fail;
    }
    jpegd->device_registered = RT_TRUE;
#endif /* RT_SOC_SUNXI_JPEG_DEC */

#ifdef RT_SOC_SUNXI_JPEG_ENC
    rt_dm_dev_set_name_auto(&jpegd->encoder, "jpege");
    encoder_name = rt_dm_dev_get_name(&jpegd->encoder);
    jpegd->encoder.type = RT_Device_Class_Char;
    jpegd->encoder.bus = dev->bus;
    jpegd->encoder.ofw_node = dev->ofw_node;
#ifdef RT_USING_DEVICE_OPS
    jpegd->encoder.ops = &sunxi_jpege_ops;
#else
    jpegd->encoder.control = sunxi_jpege_control;
#endif
    if ((err = rt_device_register(&jpegd->encoder, encoder_name,
            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE)) != RT_EOK)
    {
        goto _fail;
    }
    jpegd->encoder_registered = RT_TRUE;
#endif /* RT_SOC_SUNXI_JPEG_ENC */

#ifdef RT_SOC_SUNXI_PNG_DEC
    rt_dm_dev_set_name_auto(&jpegd->png_decoder, "pngd");
    png_name = rt_dm_dev_get_name(&jpegd->png_decoder);
    jpegd->png_decoder.type = RT_Device_Class_Char;
    jpegd->png_decoder.bus = dev->bus;
    jpegd->png_decoder.ofw_node = dev->ofw_node;
#ifdef RT_USING_DEVICE_OPS
    jpegd->png_decoder.ops = &sunxi_pngd_ops;
#else
    jpegd->png_decoder.control = sunxi_pngd_control;
#endif
    if ((err = rt_device_register(&jpegd->png_decoder, png_name,
            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE)) != RT_EOK)
    {
        goto _fail;
    }
    jpegd->png_registered = RT_TRUE;
#endif /* RT_SOC_SUNXI_PNG_DEC */

    rt_hw_interrupt_install(jpegd->irq, sunxi_jpegd_isr, jpegd, "ve");
    rt_hw_interrupt_umask(jpegd->irq);
    jpegd->irq_installed = RT_TRUE;
    dev->user_data = jpegd;

    LOG_D("VE codec version %08x", jpegd->version);
    return RT_EOK;

_fail:
    sunxi_jpegd_release(jpegd);
    return err;
}

static rt_err_t sunxi_jpegd_remove(struct rt_platform_device *pdev)
{
    struct sunxi_jpegd *jpegd = pdev->parent.user_data;

    if (jpegd->irq_installed)
    {
        rt_hw_interrupt_mask(jpegd->irq);
        rt_pic_detach_irq(jpegd->irq, jpegd);
    }
    sunxi_jpegd_release(jpegd);

    return RT_EOK;
}

static const struct rt_ofw_node_id sunxi_jpegd_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-video-engine" },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_jpegd_driver =
{
    .name = "sunxi-jpegd",
    .ids = sunxi_jpegd_ofw_ids,
    .probe = sunxi_jpegd_probe,
    .remove = sunxi_jpegd_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sunxi_jpegd_driver);
