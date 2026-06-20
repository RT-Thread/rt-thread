/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/pci.h>
#include <drivers/dma.h>
#include <ipc/dataqueue.h>

#include <cpuport.h>

#define DBG_TAG "audio.hda"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define ICH6_REG_BAR                    0

/* Controller MMIO registers (intel_hda_* uses ICH6_REG_##name token pasting) */
#define ICH6_REG_VMIN                   0x02
#define ICH6_REG_VMAJ                   0x03
#define ICH6_REG_GCTL                   0x08
#define   ICH6_GCTL_RESET               (1 << 0)
#define ICH6_REG_WAKEEN                 0x0c
#define ICH6_REG_STATESTS               0x0e
#define ICH6_REG_INTCTL                 0x20
#define ICH6_REG_INTSTS                 0x24
#define ICH6_REG_CORBLBASE              0x40
#define ICH6_REG_CORBUBASE              0x44
#define ICH6_REG_CORBWP                 0x48
#define ICH6_REG_CORBRP                 0x4a
#define   ICH6_CORBRP_RST               (1 << 15)
#define ICH6_REG_CORBCTL                0x4c
#define   ICH6_CORBCTL_RUN              (1 << 1)
#define   ICH6_CORBCTL_CMEIE            (1 << 0)
#define ICH6_REG_CORBSTS                0x4d
#define   ICH6_CORBSTS_CMEI             (1 << 0)
#define ICH6_REG_CORBSIZE               0x4e

#define ICH6_REG_RIRBLBASE              0x50
#define ICH6_REG_RIRBUBASE              0x54
#define ICH6_REG_RIRBWP                 0x58
#define   ICH6_RIRBWP_RST               (1 << 15)
#define ICH6_REG_RINTCNT                0x5a
#define ICH6_REG_RIRBCTL                0x5c
#define   ICH6_RBCTL_IRQ_EN             (1 << 0)
#define   ICH6_RBCTL_DMA_EN             (1 << 1)
#define   ICH6_RBCTL_OVERRUN_EN         (1 << 2)
#define ICH6_REG_RIRBSTS                0x5d
#define   ICH6_RBSTS_IRQ                (1 << 0)
#define   ICH6_RBSTS_OVERRUN            (1 << 2)
#define ICH6_REG_RIRBSIZE               0x5e

#define ICH6_REG_DPLBASE                0x70
#define ICH6_REG_DPUBASE                0x74
#define   ICH6_DPLBASE_ENABLE           0x1

#define ICH6_SDO0_OFF                   0x100
/* SDO0 is stream 4 (streams 0-3 are SDI); INTCTL/INTSTS use one bit per stream */
#define HDA_SDO0_STREAM_NR              4
#define HDA_SDO0_STREAM_INT             (1u << HDA_SDO0_STREAM_NR)

/* Stream descriptor register offsets (sd_* uses ICH6_REG_SD_##name) */
#define ICH6_REG_SD_CTL                 0x00
#define ICH6_REG_SD_STS                 0x03
#define ICH6_REG_SD_LPIB                0x04
#define ICH6_REG_SD_CBL                 0x08
#define ICH6_REG_SD_LVI                 0x0c
#define ICH6_REG_SD_FORMAT              0x12
#define ICH6_REG_SD_BDLPL               0x18
#define ICH6_REG_SD_BDLPU               0x1c

#define AZX_MAX_CODECS                  8

#define SD_CTL_STREAM_RESET             0x01
#define SD_CTL_DMA_START                0x02
#define SD_CTL_STREAM_TAG_SHIFT         20

#define SD_INT_DESC_ERR                 0x10
#define SD_INT_FIFO_ERR                 0x08
#define SD_INT_COMPLETE                 0x04
#define SD_INT_MASK                     (SD_INT_DESC_ERR | SD_INT_FIFO_ERR | SD_INT_COMPLETE)

#define ICH6_INT_CTRL_EN                0x40000000
#define ICH6_INT_GLOBAL_EN              0x80000000

#define ICH6_MAX_CORB_ENTRIES           256
#define ICH6_MAX_RIRB_ENTRIES           256

#define AC_NODE_ROOT                    0x00

enum
{
    AC_GRP_AUDIO_FUNCTION = 0x01,
};

enum
{
    AC_WID_AUD_OUT,
    AC_WID_AUD_IN,
    AC_WID_AUD_MIX,
    AC_WID_AUD_SEL,
    AC_WID_PIN,
};

enum
{
    AC_JACK_LINE_OUT,
    AC_JACK_SPEAKER,
    AC_JACK_HP_OUT,
};

#define AC_VERB_PARAMETERS                0xf0000
#define AC_VERB_GET_CONNECT_LIST          0xf0200
#define AC_VERB_GET_PIN_WIDGET_CONTROL    0xf0700
#define AC_VERB_GET_EAPD_BTLENABLE        0xf0c00
#define AC_VERB_GET_CONFIG_DEFAULT        0xf1c00

#define AC_VERB_SET_STREAM_FORMAT         0x20000
#define AC_VERB_SET_AMP_GAIN_MUTE         0x30000
#define AC_VERB_SET_CONNECT_SEL           0x70100
#define AC_VERB_SET_POWER_STATE           0x70500
#define AC_VERB_SET_CHANNEL_STREAMID      0x70600
#define AC_VERB_SET_PIN_WIDGET_CONTROL    0x70700
#define AC_VERB_SET_EAPD_BTLENABLE        0x70c00
#define AC_VERB_SET_CODEC_RESET           0x7ff00

#define AC_PAR_NODE_COUNT                 0x04
#define AC_PAR_FUNCTION_TYPE              0x05
#define AC_PAR_AUDIO_WIDGET_CAP           0x09
#define AC_PAR_PIN_CAP                    0x0c
#define AC_PAR_CONNLIST_LEN               0x0e
#define AC_PAR_AMP_OUT_CAP                0x12

#define AC_FGT_TYPE                       (0xff << 0)

#define AC_WCAP_POWER                     (1 << 10)
#define AC_WCAP_TYPE                      (0xf << 20)
#define AC_WCAP_TYPE_SHIFT                20

#define AC_FMT_BITS_16                    (1 << 4)

#define AC_PINCAP_OUT                     (1 << 4)

#define AC_AMPCAP_NUM_STEPS_SHIFT         8

#define AC_CLIST_LENGTH                   (0x7f << 0)
#define AC_CLIST_LONG                     (1 << 7)

#define AC_PWRST_D0                       0x00

#define AC_AMP_MUTE                       (1 << 7)
#define AC_AMP_GAIN                       (0x7f)
#define AC_AMP_SET_RIGHT                  (1 << 12)
#define AC_AMP_SET_LEFT                   (1 << 13)
#define AC_AMP_SET_INPUT                  (1 << 14)
#define AC_AMP_SET_OUTPUT                 (1 << 15)

#define AC_PINCTL_OUT_EN                  (1 << 6)

#define AC_DEFCFG_DEVICE_SHIFT            20

/* BDL (Buffer Descriptor List) entry - Intel HDA spec format */
rt_packed(struct hda_bdl_entry
{
    rt_uint64_t addr;       /* Address (64-bit) */
    rt_uint32_t length;     /* Length (32-bit, but only bits 15:0 valid) */
    rt_uint32_t flags;      /* Flags (32-bit, but only bits 2:0 valid) */
});

#define HDA_BDL_FLAGS_IOC               (1 << 0)   /* Interrupt On Completion */

/* Stream configuration defaults (2 x 4KB = 8KB, matches codec ring in emulators) */
#define HDA_BDL_COUNT                   2
#define HDA_BUFFER_SIZE                 4096       /* Match framework BUFSZ */
/*
 * MP pool size == BDL count. Each period keeps its mp_block until LPIB reclaim.
 * evt_notify calls replay_push directly after each queue push.
 */
#define HDA_REPLAY_POLL_MS              2
#define HDA_SAMPLE_RATE_48K             0
#define HDA_SAMPLE_RATE_44K             (1 << 14)

/* CORB/RIRB memory layout offsets within the shared ring buffer */
#define HDA_CORB_OFFSET                 0
#define HDA_CORB_MAX_BYTES              (ICH6_MAX_CORB_ENTRIES * 4)  /* 1024 */
#define HDA_RIRB_OFFSET                 HDA_CORB_MAX_BYTES
#define HDA_RIRB_MAX_BYTES              (ICH6_MAX_RIRB_ENTRIES * 8)  /* 2048 */
#define HDA_BDL_OFFSET                  (HDA_CORB_MAX_BYTES + HDA_RIRB_MAX_BYTES) /* 3072 */
#define HDA_BDL_BYTES_ROUNDED           ((HDA_BDL_COUNT * sizeof(struct hda_bdl_entry) + 127) & ~127)
#define HDA_DMA_POS_OFFSET              (HDA_BDL_OFFSET + HDA_BDL_BYTES_ROUNDED)
#define HDA_RING_BUF_SIZE               (HDA_DMA_POS_OFFSET + 128)   /* Total ring buffer area */

struct hda_output
{
    rt_uint8_t codec;
    rt_uint16_t node_id;        /* DAC / audio output widget */
    rt_uint16_t pin_nid;        /* Pin complex feeding the DAC */

    rt_uint32_t sample_rate;
    int amp_gain_steps;
    int num_channels;
    rt_uint8_t volume;
};

struct intel_hda
{
    struct rt_audio_device parent;

    void *ich6_reg_base;
    struct rt_pci_device *pdev;

    int stream;
    struct rt_audio_configure config;

    struct hda_output output;

    /* Shared DMA-able memory for CORB, RIRB, BDL, DMA Position */
    void *ring_buffer;
    rt_ubase_t ring_buffer_dma;

    rt_uint32_t *corb;              /* Command Outbound Ring Buffer */
    rt_uint64_t *rirb;              /* Response Inbound Ring Buffer */
    struct hda_bdl_entry *bdl;      /* Buffer Descriptor List */
    rt_uint64_t *dma_pos;           /* DMA Position in Current Buffer */

    rt_size_t corb_entries;         /* Number of CORB entries */
    rt_size_t rirb_entries;         /* Number of RIRB entries */
    rt_uint16_t rirb_read_pointer;  /* RIRB software read pointer */

    /* Audio data buffer for DMA */
    void *audio_buffer;
    rt_ubase_t audio_buffer_dma;
    rt_uint32_t audio_buffer_size;

    /* Per-BDL period state */
    struct intel_hda_period
    {
        rt_bool_t pending;
        void *mp_block;
        rt_tick_t submit_tick;  /* when PCM was handed to DMA (for pace reclaim) */
    } periods[HDA_BDL_COUNT];

    rt_uint32_t last_reclaimed_period;   /* Last BDL period reclaimed for refill */
    rt_uint32_t last_lpib;               /* Last LPIB (bytes consumed by controller) */
    volatile rt_bool_t playback_active;
    volatile rt_bool_t dma_started;

    /* Replay worker (bypass dev_audio tx_complete) */
    struct rt_semaphore replay_sem;
    struct rt_thread *replay_thread;
    rt_bool_t replay_thread_exit;
    struct rt_mutex replay_push_lock;

    /* Polling timer: track LPIB consumption (matches controller DMA read) */
    struct rt_timer poll_timer;
};

static struct intel_hda *intel_hda_replay_notify_dev;

#define raw_to_intel_hda(raw) rt_container_of(raw, struct intel_hda, parent)

#define intel_hda_writel(hda, reg, val)   HWREG32((rt_ubase_t)(hda)->ich6_reg_base + ICH6_REG_##reg) = (val)
#define intel_hda_writew(hda, reg, val)   HWREG16((rt_ubase_t)(hda)->ich6_reg_base + ICH6_REG_##reg) = (val)
#define intel_hda_writeb(hda, reg, val)   HWREG8((rt_ubase_t)(hda)->ich6_reg_base + ICH6_REG_##reg) = (val)

#define intel_hda_readl(hda, reg)         HWREG32((rt_ubase_t)(hda)->ich6_reg_base + ICH6_REG_##reg)
#define intel_hda_readw(hda, reg)         HWREG16((rt_ubase_t)(hda)->ich6_reg_base + ICH6_REG_##reg)
#define intel_hda_readb(hda, reg)         HWREG8((rt_ubase_t)(hda)->ich6_reg_base + ICH6_REG_##reg)

/* Output stream descriptor base offset (SDO0) */
#define HDA_SD_OUT_BASE                    ICH6_SDO0_OFF

/* Stream descriptor register access macros */
#define sd_writel(hda, base, reg, val)   HWREG32((rt_ubase_t)(hda)->ich6_reg_base + (base) + ICH6_REG_SD_##reg) = (val)
#define sd_writew(hda, base, reg, val)   HWREG16((rt_ubase_t)(hda)->ich6_reg_base + (base) + ICH6_REG_SD_##reg) = (val)
#define sd_writeb(hda, base, reg, val)   HWREG8((rt_ubase_t)(hda)->ich6_reg_base + (base) + ICH6_REG_SD_##reg) = (val)
#define sd_readl(hda, base, reg)         HWREG32((rt_ubase_t)(hda)->ich6_reg_base + (base) + ICH6_REG_SD_##reg)
#define sd_readw(hda, base, reg)         HWREG16((rt_ubase_t)(hda)->ich6_reg_base + (base) + ICH6_REG_SD_##reg)
#define sd_readb(hda, base, reg)         HWREG8((rt_ubase_t)(hda)->ich6_reg_base + (base) + ICH6_REG_SD_##reg)

/*
 * CORB/RIRB - Codec command/response ring buffers
 */

static rt_uint32_t intel_hda_codec_query(struct intel_hda *hda,
        int codec, int nid, rt_uint32_t payload);

static rt_uint16_t intel_hda_conn_list_entry(struct intel_hda *hda, int codec,
        int wid, rt_uint32_t conn_len, int index)
{
    rt_uint32_t resp;
    rt_uint16_t conn;

    if (conn_len & AC_CLIST_LONG)
    {
        resp = intel_hda_codec_query(hda, codec, wid,
                AC_VERB_GET_CONNECT_LIST | (index / 2));
        if (resp == 0xffffffff)
        {
            return 0xffff;
        }
        conn = (index & 1) ? (resp >> 16) : (resp & 0xffff);
    }
    else
    {
        resp = intel_hda_codec_query(hda, codec, wid,
                AC_VERB_GET_CONNECT_LIST | index);
        if (resp == 0xffffffff)
        {
            return 0xffff;
        }
        conn = resp & 0xff;
    }

    return conn;
}

static rt_bool_t intel_hda_route_to_dac(struct intel_hda *hda, int codec,
        int wid, int dac_nid)
{
    rt_uint32_t conn_len;
    int num_conns;
    int i;

    conn_len = intel_hda_codec_query(hda, codec, wid,
            AC_VERB_PARAMETERS | AC_PAR_CONNLIST_LEN);
    if (conn_len == 0xffffffff)
    {
        return RT_FALSE;
    }
    num_conns = conn_len & AC_CLIST_LENGTH;
    for (i = 0; i < num_conns; i++)
    {
        rt_uint16_t conn_nid;
        rt_uint32_t cap;
        int type;

        conn_nid = intel_hda_conn_list_entry(hda, codec, wid, conn_len, i);
        if (conn_nid == 0xffff)
        {
            continue;
        }
        if (conn_nid == (rt_uint16_t)dac_nid)
        {
            intel_hda_codec_query(hda, codec, wid, AC_VERB_SET_CONNECT_SEL | i);
            return RT_TRUE;
        }

        cap = intel_hda_codec_query(hda, codec, conn_nid,
                AC_VERB_PARAMETERS | AC_PAR_AUDIO_WIDGET_CAP);
        if (cap == 0xffffffff)
        {
            continue;
        }
        type = (cap & AC_WCAP_TYPE) >> AC_WCAP_TYPE_SHIFT;
        if (type == AC_WID_AUD_SEL || type == AC_WID_AUD_MIX)
        {
            if (intel_hda_route_to_dac(hda, codec, conn_nid, dac_nid))
            {
                intel_hda_codec_query(hda, codec, wid, AC_VERB_SET_CONNECT_SEL | i);
                return RT_TRUE;
            }
        }
    }

    return RT_FALSE;
}

static void intel_hda_set_widget_amp(struct intel_hda *hda, int codec, int nid,
        int gain, rt_bool_t output)
{
    rt_uint32_t meta = AC_AMP_SET_LEFT | AC_AMP_SET_RIGHT;

    meta |= output ? AC_AMP_SET_OUTPUT : AC_AMP_SET_INPUT;
    intel_hda_codec_query(hda, codec, nid,
            AC_VERB_SET_AMP_GAIN_MUTE | meta | (gain & AC_AMP_GAIN));
}

static void intel_hda_setup_playback_path(struct intel_hda *hda)
{
    int gain;

    if (!hda->output.node_id)
    {
        return;
    }
    if (hda->output.pin_nid)
    {
        if (!intel_hda_route_to_dac(hda, hda->output.codec,
                hda->output.pin_nid, hda->output.node_id))
        {
            LOG_W("Failed to route pin %d to DAC %d",
                    hda->output.pin_nid, hda->output.node_id);
        }
    }

    gain = hda->output.amp_gain_steps;
    if (gain > 0)
    {
        gain--;
    }
    intel_hda_set_widget_amp(hda, hda->output.codec, hda->output.node_id,
            gain, RT_TRUE);

    if (hda->output.pin_nid)
    {
        intel_hda_set_widget_amp(hda, hda->output.codec, hda->output.pin_nid,
                gain, RT_TRUE);
    }
}

static void intel_hda_setup_corb(struct intel_hda *hda)
{
    rt_uint8_t reg;
    rt_uint64_t corb_base;
    int timeout;

    reg = intel_hda_readb(hda, CORBSIZE);

    /* Choose the largest supported CORB size */
    if (reg & (1 << 6))
    {
        hda->corb_entries = 256;
        reg |= 0x2;
    }
    else if (reg & (1 << 5))
    {
        hda->corb_entries = 16;
        reg |= 0x1;
    }
    else if (reg & (1 << 4))
    {
        hda->corb_entries = 2;
    }
    else
    {
        LOG_E("No supported CORB size!");
        return;
    }

    intel_hda_writeb(hda, CORBSIZE, reg);

    /* Reset CORB pointers */
    intel_hda_writew(hda, CORBWP, 0);

    /* Reset CORB read pointer: set RST, wait for ack, clear RST, wait for ack */
    intel_hda_writew(hda, CORBRP, ICH6_CORBRP_RST);
    timeout = 10000;
    while (!(intel_hda_readw(hda, CORBRP) & ICH6_CORBRP_RST))
    {
        if (--timeout == 0)
        {
            intel_hda_writew(hda, CORBRP, 0);
            goto corbrp_done;
        }
        rt_hw_cpu_relax();
    }
    intel_hda_writew(hda, CORBRP, 0);
    timeout = 10000;
    while (intel_hda_readw(hda, CORBRP) & ICH6_CORBRP_RST)
    {
        if (--timeout == 0)
        {
            break;
        }
        rt_hw_cpu_relax();
    }
corbrp_done:

    /* Set CORB base address */
    corb_base = hda->ring_buffer_dma + HDA_CORB_OFFSET;
    intel_hda_writel(hda, CORBLBASE, (rt_uint32_t)(corb_base & 0xffffffff));
    intel_hda_writel(hda, CORBUBASE, (rt_uint32_t)(corb_base >> 32));

    /* Set virtual pointer */
    hda->corb = (rt_uint32_t *)((rt_ubase_t)hda->ring_buffer + HDA_CORB_OFFSET);

    /* Clear CORB status */
    intel_hda_writeb(hda, CORBSTS, ICH6_CORBSTS_CMEI);

    /* Start CORB DMA engine + enable memory error interrupt */
    intel_hda_writeb(hda, CORBCTL, ICH6_CORBCTL_CMEIE | ICH6_CORBCTL_RUN);

    LOG_D("CORB setup: %d entries", hda->corb_entries);
}

static void intel_hda_setup_rirb(struct intel_hda *hda)
{
    rt_uint8_t reg;
    rt_uint64_t rirb_base;

    reg = intel_hda_readb(hda, RIRBSIZE);

    /* Choose the largest supported RIRB size */
    if (reg & (1 << 6))
    {
        hda->rirb_entries = 256;
        reg |= 0x2;
    }
    else if (reg & (1 << 5))
    {
        hda->rirb_entries = 16;
        reg |= 0x1;
    }
    else if (reg & (1 << 4))
    {
        hda->rirb_entries = 2;
    }
    else
    {
        LOG_E("No supported RIRB size!");
        return;
    }

    intel_hda_writeb(hda, RIRBSIZE, reg);

    /* Reset RIRB write pointer */
    intel_hda_writew(hda, RIRBWP, ICH6_RIRBWP_RST);
    hda->rirb_read_pointer = 0;

    /* Set RIRB base address */
    rirb_base = hda->ring_buffer_dma + HDA_RIRB_OFFSET;
    intel_hda_writel(hda, RIRBLBASE, (rt_uint32_t)(rirb_base & 0xffffffff));
    intel_hda_writel(hda, RIRBUBASE, (rt_uint32_t)(rirb_base >> 32));

    /* Set virtual pointer */
    hda->rirb = (rt_uint64_t *)((rt_ubase_t)hda->ring_buffer + HDA_RIRB_OFFSET);

    /* Set response interrupt count threshold */
    intel_hda_writeb(hda, RINTCNT, hda->rirb_entries - 1);

    /* Clear RIRB status */
    intel_hda_writeb(hda, RIRBSTS, ICH6_RBSTS_IRQ | ICH6_RBSTS_OVERRUN);

    /* Start RIRB DMA engine + enable IRQ + enable overrun interrupt */
    intel_hda_writeb(hda, RIRBCTL, ICH6_RBCTL_IRQ_EN | ICH6_RBCTL_DMA_EN | ICH6_RBCTL_OVERRUN_EN);

    LOG_D("RIRB setup: %d entries", hda->rirb_entries);
}

static int intel_hda_corb_write(struct intel_hda *hda, rt_uint32_t verb)
{
    rt_uint16_t wp, rp, next;
    int timeout = 10000;

    wp = intel_hda_readw(hda, CORBWP) & 0xff;
    next = (wp + 1) % hda->corb_entries;

    /* Wait until there is a free entry in the CORB with timeout */
    do
    {
        rp = intel_hda_readw(hda, CORBRP) & 0xff;
        if (--timeout == 0)
        {
            LOG_E("CORB write timeout! wp=%d rp=%d next=%d", wp, rp, next);
            return -RT_ETIMEOUT;
        }
    } while (next == rp);

    /* Write the command verb and advance the write pointer */
    hda->corb[next] = verb;
    rt_hw_dmb();
    intel_hda_writew(hda, CORBWP, next);

    return RT_EOK;
}

static int intel_hda_rirb_read(struct intel_hda *hda, rt_uint64_t *response)
{
    rt_uint16_t wp;
    rt_uint16_t rp = hda->rirb_read_pointer;
    int timeout = 10000;  /* ~10ms timeout */

    /* Wait for an unread entry in the RIRB with timeout */
    do
    {
        wp = intel_hda_readw(hda, RIRBWP) & 0xff;
        if (--timeout == 0)
        {
            LOG_E("RIRB read timeout! wp=%d rp=%d", wp, rp);
            return -RT_ETIMEOUT;
        }
    } while (wp == rp);

    /* Read from RIRB */
    rp = (rp + 1) % hda->rirb_entries;
    hda->rirb_read_pointer = rp;

    *response = hda->rirb[rp];

    /* Clear RIRB status */
    intel_hda_writeb(hda, RIRBSTS, ICH6_RBSTS_IRQ | ICH6_RBSTS_OVERRUN);

    return RT_EOK;
}

/*
 * Codec communication - send a verb and get a response
 * verb encoding: [codec_addr:4][nid:8][payload:20]
 */
static rt_uint32_t intel_hda_codec_query(struct intel_hda *hda,
        int codec, int nid, rt_uint32_t payload)
{
    rt_uint64_t response;
    rt_uint32_t verb = ((codec & 0xf) << 28) | ((nid & 0xff) << 20) | (payload & 0xfffff);

    LOG_D("codec_query: codec=%d nid=%d payload=0x%05x verb=0x%08x",
          codec, nid, payload & 0xfffff, verb);

    if (intel_hda_corb_write(hda, verb) != RT_EOK)
    {
        LOG_E("CORB write failed: codec=%d nid=%d", codec, nid);
        return 0xffffffff;
    }

    if (intel_hda_rirb_read(hda, &response) != RT_EOK)
    {
        LOG_E("RIRB read failed: codec=%d nid=%d", codec, nid);
        return 0xffffffff;
    }

    LOG_D("  response=0x%08x", (rt_uint32_t)(response & 0xffffffff));

    return (rt_uint32_t)(response & 0xffffffff);
}

/*
 * Codec enumeration and widget initialization
 */

static void intel_hda_widget_init(struct intel_hda *hda, int codec, int nid)
{
    rt_uint32_t widget_cap, amp_cap, eapd_btl;
    int type;

    widget_cap = intel_hda_codec_query(hda, codec, nid,
                    AC_VERB_PARAMETERS | AC_PAR_AUDIO_WIDGET_CAP);
    if (widget_cap == 0xffffffff)
    {
        return;
    }
    type = (widget_cap & AC_WCAP_TYPE) >> AC_WCAP_TYPE_SHIFT;

    amp_cap = intel_hda_codec_query(hda, codec, nid,
                AC_VERB_PARAMETERS | AC_PAR_AMP_OUT_CAP);
    eapd_btl = intel_hda_codec_query(hda, codec, nid, AC_VERB_GET_EAPD_BTLENABLE);

    switch (type)
    {
    case AC_WID_PIN:
    {
        rt_uint32_t pin_cap, ctl, defcfg;
        int device;

        pin_cap = intel_hda_codec_query(hda, codec, nid,
                    AC_VERB_PARAMETERS | AC_PAR_PIN_CAP);
        if (!(pin_cap & AC_PINCAP_OUT))
        {
            return;
        }
        defcfg = intel_hda_codec_query(hda, codec, nid, AC_VERB_GET_CONFIG_DEFAULT);
        device = (defcfg >> AC_DEFCFG_DEVICE_SHIFT) & 0xf;

        if (!hda->output.pin_nid || device == AC_JACK_SPEAKER ||
                device == AC_JACK_HP_OUT || device == AC_JACK_LINE_OUT)
        {
            hda->output.pin_nid = nid;
        }
        ctl = intel_hda_codec_query(hda, codec, nid, AC_VERB_GET_PIN_WIDGET_CONTROL);
        ctl |= AC_PINCTL_OUT_EN;
        intel_hda_codec_query(hda, codec, nid, AC_VERB_SET_PIN_WIDGET_CONTROL | ctl);

        /* Enable EAPD */
        intel_hda_codec_query(hda, codec, nid, AC_VERB_SET_EAPD_BTLENABLE | eapd_btl | 0x2);
        break;
    }

    case AC_WID_AUD_OUT:
    {
        if (!hda->output.node_id)
        {
            LOG_D("Using audio output widget: codec=%d nid=%d", codec, nid);
            hda->output.codec = codec;
            hda->output.node_id = nid;
            hda->output.amp_gain_steps = (amp_cap >> AC_AMPCAP_NUM_STEPS_SHIFT) & 0x7f;
        }

        intel_hda_codec_query(hda, codec, nid, AC_VERB_SET_EAPD_BTLENABLE | eapd_btl | 0x2);
        break;
    }

    default:
        break;
    }

    /* Power up widget if it has power control */
    if (widget_cap & AC_WCAP_POWER)
    {
        intel_hda_codec_query(hda, codec, nid, AC_VERB_SET_POWER_STATE | AC_PWRST_D0);
    }
}

static rt_err_t intel_hda_codec_enumerate_widgets(struct intel_hda *hda, int codec)
{
    rt_uint32_t param;
    int num_fg, fg_start;
    int i, j;

    param = intel_hda_codec_query(hda, codec, AC_NODE_ROOT,
                AC_VERB_PARAMETERS | AC_PAR_NODE_COUNT);

    if (param == 0xffffffff)
    {
        return -RT_ERROR;
    }
    num_fg = param & 0xff;
    fg_start = (param >> 16) & 0xff;

    LOG_D("Codec %d: %d function groups starting at ID %d", codec, num_fg, fg_start);

    for (i = 0; i < num_fg; i++)
    {
        int num_widgets, widgets_start;
        int fg_id = fg_start + i;

        param = intel_hda_codec_query(hda, codec, fg_id,
                    AC_VERB_PARAMETERS | AC_PAR_FUNCTION_TYPE);

        if (param == 0xffffffff)
        {
            continue;
        }
        if ((param & AC_FGT_TYPE) != AC_GRP_AUDIO_FUNCTION)
        {
            LOG_D("  FG %d: non-audio type %d, skipping", fg_id, param & AC_FGT_TYPE);
            continue;
        }

        /* Power up the function group */
        intel_hda_codec_query(hda, codec, fg_id,
            AC_VERB_SET_POWER_STATE | AC_PWRST_D0);
        rt_hw_us_delay(1000);

        param = intel_hda_codec_query(hda, codec, fg_id,
                    AC_VERB_PARAMETERS | AC_PAR_NODE_COUNT);

        if (param == 0xffffffff)
        {
            continue;
        }
        num_widgets = param & 0xff;
        widgets_start = (param >> 16) & 0xff;

        LOG_D("  FG %d: %d widgets starting at ID %d", fg_id, num_widgets, widgets_start);

        for (j = 0; j < num_widgets; j++)
        {
            intel_hda_widget_init(hda, codec, widgets_start + j);
        }
    }

    if (hda->output.node_id)
    {
        intel_hda_setup_playback_path(hda);
    }
    return hda->output.node_id ? RT_EOK : -RT_ERROR;
}

static void intel_hda_enumerate_codecs(struct intel_hda *hda)
{
    rt_uint16_t statests;
    int i;

    statests = intel_hda_readw(hda, STATESTS);
    LOG_D("STATESTS = 0x%04x", statests);

    for (i = 0; i < AZX_MAX_CODECS; i++)
    {
        if (statests & (1 << i))
        {
            LOG_I("Found codec at address %d", i);
            intel_hda_codec_query(hda, i, AC_NODE_ROOT, AC_VERB_SET_CODEC_RESET);
            rt_hw_us_delay(1000);
            if (intel_hda_codec_enumerate_widgets(hda, i) == RT_EOK)
            {
                return;
            }
        }
    }

    LOG_W("No usable audio output widget found!");
}

/*
 * Configure the output widget for the current sample rate/channels
 */
static void intel_hda_configure_output(struct intel_hda *hda)
{
    rt_uint16_t format;

    if (!hda->output.node_id)
    {
        LOG_W("configure_output: no output node");
        return;
    }

    /* Build the HDA format register value */
    format = AC_FMT_BITS_16 | hda->output.sample_rate | (hda->output.num_channels - 1);

    /* Set converter format */
    intel_hda_codec_query(hda, hda->output.codec, hda->output.node_id,
        AC_VERB_SET_STREAM_FORMAT | format);

    /* Set stream tag and channel */
    /* Stream 1 (bit 7:4), Channel 0 (bit 3:0) => 0x10 */
    intel_hda_codec_query(hda, hda->output.codec, hda->output.node_id,
        AC_VERB_SET_CHANNEL_STREAMID | 0x10);

    /* Set the same format in the controller stream descriptor */
    sd_writew(hda, HDA_SD_OUT_BASE, FORMAT, format);

}

/*
 * Setup the BDL (Buffer Descriptor List) and stream descriptor
 */
static void intel_hda_setup_stream(struct intel_hda *hda)
{
    rt_uint64_t bdl_base, dma_pos_base;
    int i;

    /* Reset the stream descriptor */
    sd_writeb(hda, HDA_SD_OUT_BASE, CTL, SD_CTL_STREAM_RESET);
    while (!(sd_readb(hda, HDA_SD_OUT_BASE, CTL) & SD_CTL_STREAM_RESET))
    {
        rt_hw_cpu_relax();
    }
    rt_hw_us_delay(100);
    sd_writeb(hda, HDA_SD_OUT_BASE, CTL, 0);
    while (sd_readb(hda, HDA_SD_OUT_BASE, CTL) & SD_CTL_STREAM_RESET)
    {
        rt_hw_cpu_relax();
    }

    /* Set stream tag in bits [23:20] of CTL (32-bit register) */
    sd_writel(hda, HDA_SD_OUT_BASE, CTL, (1 << SD_CTL_STREAM_TAG_SHIFT));

    /* Set cyclic buffer length = total buffer size */
    sd_writel(hda, HDA_SD_OUT_BASE, CBL, hda->audio_buffer_size);

    /* Set last valid index = BDL_COUNT - 1 (all BDL entries are valid) */
    sd_writew(hda, HDA_SD_OUT_BASE, LVI, HDA_BDL_COUNT - 1);

    /* Set the format */
    {
        rt_uint16_t fmt = AC_FMT_BITS_16 | hda->output.sample_rate | (hda->output.num_channels - 1);
        sd_writew(hda, HDA_SD_OUT_BASE, FORMAT, fmt);
    }

    /* Set BDL base address */
    bdl_base = hda->ring_buffer_dma + HDA_BDL_OFFSET;
    sd_writel(hda, HDA_SD_OUT_BASE, BDLPL, (rt_uint32_t)(bdl_base & 0xffffffff));
    sd_writel(hda, HDA_SD_OUT_BASE, BDLPU, (rt_uint32_t)(bdl_base >> 32));

    /* Fill BDL entries - each entry is a period, set IOC on each */
    hda->bdl = (struct hda_bdl_entry *)((rt_ubase_t)hda->ring_buffer + HDA_BDL_OFFSET);
    for (i = 0; i < HDA_BDL_COUNT; i++)
    {
        rt_uint64_t buf_addr = hda->audio_buffer_dma + (i * HDA_BUFFER_SIZE);
        hda->bdl[i].addr = buf_addr;
        hda->bdl[i].length = HDA_BUFFER_SIZE;  /* Intel HDA: only bits 15:0 used */
        /* Each BDL entry is a period - set IOC on each for per-period interrupt */
        hda->bdl[i].flags = HDA_BDL_FLAGS_IOC;
    }

    /* Clear audio buffer */
    rt_memset(hda->audio_buffer, 0, hda->audio_buffer_size);

    /* Initialize DMA Position Buffer */
    /* Intel HDA spec: Each stream position entry is 32 bytes (aligned) */
    hda->dma_pos = (rt_uint64_t *)((rt_ubase_t)hda->ring_buffer + HDA_DMA_POS_OFFSET);
    /* Clear position buffer for stream 0 (output stream) - 32 bytes */
    rt_memset(hda->dma_pos, 0, 32);

    dma_pos_base = hda->ring_buffer_dma + HDA_DMA_POS_OFFSET;
    intel_hda_writel(hda, DPLBASE, ((rt_uint32_t)(dma_pos_base & 0xffffffff)) | ICH6_DPLBASE_ENABLE);
    intel_hda_writel(hda, DPUBASE, (rt_uint32_t)(dma_pos_base >> 32));

    /*
     * BDL IOC flags stay set for the hardware; stream completion IRQs are
     * left disabled.  LPIB polling drives reclaim/refill — QEMU fires IOC
     * far too often and starves the soft timer / replay worker.
     */
}

/*
 * Audio ops implementation
 */

static rt_err_t intel_hda_audio_getcaps(struct rt_audio_device *audio,
        struct rt_audio_caps *caps)
{
    struct intel_hda *hda = raw_to_intel_hda(audio);

    switch (caps->main_type)
    {
    case AUDIO_TYPE_QUERY:
        switch (caps->sub_type)
        {
        case AUDIO_TYPE_QUERY:
            caps->udata.mask = AUDIO_TYPE_OUTPUT | AUDIO_TYPE_MIXER;
            break;
        default:
            return -RT_ENOSYS;
        }
        break;

    case AUDIO_TYPE_OUTPUT:
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            caps->udata.config.samplerate = hda->config.samplerate;
            caps->udata.config.channels = hda->config.channels;
            caps->udata.config.samplebits = hda->config.samplebits;
            break;
        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate = hda->config.samplerate;
            break;
        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels = hda->config.channels;
            break;
        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits = hda->config.samplebits;
            break;
        default:
            return -RT_ENOSYS;
        }
        break;

    case AUDIO_TYPE_MIXER:
        switch (caps->sub_type)
        {
        case AUDIO_MIXER_QUERY:
            caps->udata.mask = AUDIO_MIXER_VOLUME | AUDIO_MIXER_MUTE;
            break;
        case AUDIO_MIXER_VOLUME:
            caps->udata.value = hda->output.volume;
            break;
        case AUDIO_MIXER_MUTE:
            caps->udata.value = 0;
            break;
        default:
            return -RT_ENOSYS;
        }
        break;

    default:
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static rt_err_t intel_hda_audio_configure(struct rt_audio_device *audio,
        struct rt_audio_caps *caps)
{
    struct intel_hda *hda = raw_to_intel_hda(audio);

    switch (caps->main_type)
    {
    case AUDIO_TYPE_OUTPUT:
        switch (caps->sub_type)
        {
        case AUDIO_DSP_SAMPLERATE:
            hda->config.samplerate = caps->udata.config.samplerate;
            if (hda->config.samplerate == 44100)
            {
                hda->output.sample_rate = HDA_SAMPLE_RATE_44K;
            }
            else
            {
                hda->config.samplerate = 48000;
                hda->output.sample_rate = HDA_SAMPLE_RATE_48K;
            }
            intel_hda_configure_output(hda);
            break;
        case AUDIO_DSP_CHANNELS:
            hda->config.channels = caps->udata.config.channels;
            if (hda->config.channels < 1 || hda->config.channels > 2)
            {
                hda->config.channels = 2;
            }
            hda->output.num_channels = hda->config.channels;
            intel_hda_configure_output(hda);
            break;
        case AUDIO_DSP_SAMPLEBITS:
            hda->config.samplebits = caps->udata.config.samplebits;
            break;
        case AUDIO_DSP_PARAM:
            hda->config.samplerate = caps->udata.config.samplerate;
            hda->config.channels = caps->udata.config.channels;
            hda->config.samplebits = caps->udata.config.samplebits;
            if (hda->config.samplerate == 44100)
            {
                hda->output.sample_rate = HDA_SAMPLE_RATE_44K;
            }
            else
            {
                hda->config.samplerate = 48000;
                hda->output.sample_rate = HDA_SAMPLE_RATE_48K;
            }
            hda->output.num_channels = hda->config.channels;
            intel_hda_configure_output(hda);
            break;
        default:
            return -RT_ENOSYS;
        }
        break;

    case AUDIO_TYPE_MIXER:
        switch (caps->sub_type)
        {
        case AUDIO_MIXER_VOLUME:
        {
            rt_uint32_t vol = caps->udata.value;
            int gain;
            int meta = AC_AMP_SET_LEFT | AC_AMP_SET_RIGHT | AC_AMP_SET_OUTPUT;

            hda->output.volume = (vol > AUDIO_VOLUME_MAX) ? AUDIO_VOLUME_MAX : vol;

            if (hda->output.volume == 0)
            {
                gain = AC_AMP_MUTE;
            }
            else
            {
                gain = hda->output.volume * hda->output.amp_gain_steps / AUDIO_VOLUME_MAX;
            }

            if (hda->output.node_id)
            {
                intel_hda_codec_query(hda, hda->output.codec, hda->output.node_id,
                    AC_VERB_SET_AMP_GAIN_MUTE | meta | gain);
            }
            break;
        }
        case AUDIO_MIXER_MUTE:
        {
            int meta = AC_AMP_SET_LEFT | AC_AMP_SET_RIGHT | AC_AMP_SET_OUTPUT;
            if (hda->output.node_id)
            {
                intel_hda_codec_query(hda, hda->output.codec, hda->output.node_id,
                    AC_VERB_SET_AMP_GAIN_MUTE | meta | AC_AMP_MUTE);
            }
            break;
        }
        default:
            return -RT_ENOSYS;
        }
        break;

    default:
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static rt_err_t intel_hda_audio_init(struct rt_audio_device *audio)
{
    struct intel_hda *hda = raw_to_intel_hda(audio);

    /* Set default audio configuration */
    hda->config.samplerate = 48000;
    hda->config.channels = 2;
    hda->config.samplebits = 16;
    hda->output.sample_rate = HDA_SAMPLE_RATE_48K;
    hda->output.num_channels = 2;
    hda->output.volume = AUDIO_VOLUME_MAX;
    hda->last_reclaimed_period = 0xffffffff;

    return RT_EOK;
}

/* Forward declaration */
static void intel_hda_poll_timer(void *parameter);
static void intel_hda_poll_lpib_nolock(struct intel_hda *hda);
static rt_tick_t intel_hda_period_ticks(struct intel_hda *hda);

static rt_bool_t intel_hda_period_ready_to_reclaim(struct intel_hda *hda, rt_uint32_t period)
{
    rt_tick_t need, elapsed;

    if (!hda->periods[period].pending)
    {
        return RT_FALSE;
    }
    if (hda->periods[period].submit_tick == 0)
    {
        return RT_TRUE;
    }
    need = intel_hda_period_ticks(hda);
    elapsed = rt_tick_get() - hda->periods[period].submit_tick;

    return elapsed >= need;
}

/*
 * dev_audio _audio_send_replay_frame() can spin when read_index is stale;
 * this driver pops the replay queue directly instead of rt_audio_tx_complete.
 */

static void intel_hda_sync_output_format(struct intel_hda *hda)
{
    if (hda->config.samplerate == 44100)
    {
        hda->output.sample_rate = HDA_SAMPLE_RATE_44K;
    }
    else
    {
        hda->output.sample_rate = HDA_SAMPLE_RATE_48K;
        if (hda->config.samplerate != 48000)
        {
            hda->config.samplerate = 48000;
        }
    }

    if (hda->config.channels >= 1 && hda->config.channels <= 2)
    {
        hda->output.num_channels = hda->config.channels;
    }
    else
    {
        hda->output.num_channels = 2;
    }
}

static void intel_hda_replay_queue_reset(struct intel_hda *hda)
{
    struct rt_audio_replay *replay = hda->parent.replay;

    if (!replay)
    {
        return;
    }
    replay->read_index = 0;
    replay->pos = 0;
    replay->write_index = 0;
}

static void intel_hda_schedule_replay(struct intel_hda *hda)
{
    rt_sem_release(&hda->replay_sem);
}

static void intel_hda_period_reset_all(struct intel_hda *hda)
{
    rt_uint32_t i;

    for (i = 0; i < HDA_BDL_COUNT; i++)
    {
        if (hda->periods[i].mp_block)
        {
            rt_mp_free(hda->periods[i].mp_block);
            hda->periods[i].mp_block = RT_NULL;
        }
        hda->periods[i].pending = RT_FALSE;
        hda->periods[i].submit_tick = 0;
    }
}

static rt_tick_t intel_hda_period_ticks(struct intel_hda *hda)
{
    rt_uint32_t ch = hda->output.num_channels ? hda->output.num_channels : 2;
    rt_uint32_t rate = hda->config.samplerate ? hda->config.samplerate : 48000;
    rt_uint32_t frames = HDA_BUFFER_SIZE / (ch * 2);
    rt_uint32_t ms;

    if (rate == 0)
    {
        rate = 48000;
    }
    ms = (frames * 1000U + rate - 1U) / rate;
    if (ms == 0)
    {
        ms = 1;
    }
    return rt_tick_from_millisecond(ms);
}

static rt_int32_t intel_hda_find_free_period(struct intel_hda *hda)
{
    rt_uint32_t i;

    for (i = 0; i < HDA_BDL_COUNT; i++)
    {
        if (!hda->periods[i].pending)
        {
            return (rt_int32_t)i;
        }
    }

    return -1;
}

/*
 * Copy one replay-queue block into a BDL period and hand it to DMA.
 * mp_block is retained until LPIB reclaim.
 */
static rt_bool_t intel_hda_push_one_period(struct intel_hda *hda, rt_uint32_t period)
{
    struct rt_audio_device *audio = &hda->parent;
    struct rt_audio_replay *replay = audio->replay;
    const void *data;
    rt_size_t src_size;
    rt_uint8_t *dst;
    rt_err_t err;

    if (!replay || period >= HDA_BDL_COUNT || hda->periods[period].pending)
    {
        return RT_FALSE;
    }
    err = rt_data_queue_peek(&replay->queue, &data, &src_size);
    if (err != RT_EOK || src_size == 0)
    {
        return RT_FALSE;
    }

    dst = (rt_uint8_t *)hda->audio_buffer + period * HDA_BUFFER_SIZE;
    rt_memset(dst, 0, HDA_BUFFER_SIZE);
    if (src_size > HDA_BUFFER_SIZE)
    {
        src_size = HDA_BUFFER_SIZE;
    }
    rt_memcpy(dst, data, src_size);

    err = rt_data_queue_pop(&replay->queue, &data, &src_size, RT_WAITING_NO);
    if (err != RT_EOK)
    {
        return RT_FALSE;
    }

    hda->periods[period].mp_block = (void *)data;
    hda->periods[period].pending = RT_TRUE;
    if (!hda->dma_started)
    {
        hda->periods[period].submit_tick = rt_tick_get() +
                intel_hda_period_ticks(hda) * period;
    }
    else
    {
        hda->periods[period].submit_tick = rt_tick_get();
    }
    if (audio->ops && audio->ops->transmit)
    {
        audio->ops->transmit(audio, dst, RT_NULL, HDA_BUFFER_SIZE);
    }
    return RT_TRUE;
}

static void intel_hda_replay_push_nolock(struct intel_hda *hda)
{
    struct rt_audio_replay *replay = hda->parent.replay;
    rt_int32_t period;
    rt_uint32_t i;
    rt_bool_t all_pending;

    if (!replay || !hda->playback_active)
    {
        return;
    }
    if (!hda->dma_started)
    {
        for (i = 0; i < HDA_BDL_COUNT; i++)
        {
            if (hda->periods[i].pending)
            {
                continue;
            }
            if (rt_data_queue_len(&replay->queue) == 0)
            {
                break;
            }
            if (!intel_hda_push_one_period(hda, i))
            {
                break;
            }
        }

        all_pending = RT_TRUE;
        for (i = 0; i < HDA_BDL_COUNT; i++)
        {
            if (!hda->periods[i].pending)
            {
                all_pending = RT_FALSE;
                break;
            }
        }

        if (all_pending)
        {
            replay->pos = 0;
            replay->read_index = 0;

            hda->last_lpib = sd_readl(hda, HDA_SD_OUT_BASE, LPIB);
            hda->last_reclaimed_period = (HDA_BDL_COUNT - 1);
            rt_hw_dmb();

            sd_writel(hda, HDA_SD_OUT_BASE, CTL,
                    sd_readl(hda, HDA_SD_OUT_BASE, CTL) | SD_CTL_DMA_START);

            hda->dma_started = RT_TRUE;
        }

        return;
    }

    if (rt_data_queue_len(&replay->queue) == 0)
    {
        return;
    }
    period = intel_hda_find_free_period(hda);
    if (period < 0)
    {
        return;
    }
    intel_hda_push_one_period(hda, (rt_uint32_t)period);
}

static void intel_hda_replay_worker(struct intel_hda *hda)
{
    if (!hda->playback_active || !hda->parent.replay)
    {
        return;
    }
    if (rt_interrupt_get_nest() != 0)
    {
        intel_hda_schedule_replay(hda);
        return;
    }

    rt_mutex_take(&hda->replay_push_lock, RT_WAITING_FOREVER);

    if (hda->dma_started)
    {
        intel_hda_poll_lpib_nolock(hda);

        if (rt_data_queue_len(&hda->parent.replay->queue) > 0 &&
                intel_hda_find_free_period(hda) >= 0)
        {
            intel_hda_replay_push_nolock(hda);
        }
        else if (intel_hda_find_free_period(hda) >= 0)
        {
            intel_hda_schedule_replay(hda);
        }
    }
    else
    {
        intel_hda_replay_push_nolock(hda);
    }

    rt_mutex_release(&hda->replay_push_lock);
}

static void intel_hda_replay_push(struct intel_hda *hda)
{
    intel_hda_replay_worker(hda);
}

static void intel_hda_replay_queue_notify(struct rt_data_queue *queue, rt_uint32_t event)
{
    struct intel_hda *hda = intel_hda_replay_notify_dev;

    RT_UNUSED(queue);

    if (event != RT_DATAQUEUE_EVENT_PUSH || hda == RT_NULL ||
            !hda->playback_active)
    {
        return;
    }

    intel_hda_replay_push(hda);
}

static void intel_hda_replay_thread_entry(void *parameter)
{
    struct intel_hda *hda = parameter;

    while (!hda->replay_thread_exit)
    {
        (void)rt_sem_take(&hda->replay_sem,
                rt_tick_from_millisecond(HDA_REPLAY_POLL_MS));

        if (hda->replay_thread_exit)
        {
            break;
        }
        intel_hda_replay_push(hda);
    }
}

static void intel_hda_replay_thread_stop(struct intel_hda *hda)
{
    if (!hda->replay_thread)
    {
        return;
    }
    hda->replay_thread_exit = RT_TRUE;
    rt_sem_release(&hda->replay_sem);
    rt_thread_mdelay(10);
    rt_thread_delete(hda->replay_thread);
    hda->replay_thread = RT_NULL;
}

static void intel_hda_reclaim_period_index(struct intel_hda *hda, rt_uint32_t period)
{
    if (!hda->playback_active || !hda->dma_started ||
            hda->stream != AUDIO_STREAM_REPLAY)
    {
        return;
    }
    if (period >= HDA_BDL_COUNT)
    {
        return;
    }
    hda->last_reclaimed_period = period;

    if (hda->periods[period].mp_block)
    {
        rt_mp_free(hda->periods[period].mp_block);
        hda->periods[period].mp_block = RT_NULL;
    }

    hda->periods[period].pending = RT_FALSE;
    hda->periods[period].submit_tick = 0;

}

/*
 * LPIB tells which period finished; wall-clock gates reclaim so QEMU cannot
 * run ahead of the configured sample rate.  At most one reclaim per worker pass.
 */
static void intel_hda_poll_lpib_nolock(struct intel_hda *hda)
{
    rt_uint32_t lpib, last;
    rt_uint32_t last_p, cur_p, p;
    rt_bool_t reclaimed;

    if (!hda->dma_started)
    {
        return;
    }
    lpib = sd_readl(hda, HDA_SD_OUT_BASE, LPIB);
    last = hda->last_lpib;

    if (lpib == last)
    {
        return;
    }
    last_p = last / HDA_BUFFER_SIZE;
    cur_p = lpib / HDA_BUFFER_SIZE;
    reclaimed = RT_FALSE;

    hda->last_lpib = lpib;

    if (lpib >= last)
    {
        for (p = last_p; p < cur_p && !reclaimed; p++)
        {
            if (intel_hda_period_ready_to_reclaim(hda, p))
            {
                intel_hda_reclaim_period_index(hda, p);
                reclaimed = RT_TRUE;
            }
        }
    }
    else
    {
        for (p = last_p; p < HDA_BDL_COUNT && !reclaimed; p++)
        {
            if (intel_hda_period_ready_to_reclaim(hda, p))
            {
                intel_hda_reclaim_period_index(hda, p);
                reclaimed = RT_TRUE;
            }
        }

        for (p = 0; p < cur_p && !reclaimed; p++)
        {
            if (intel_hda_period_ready_to_reclaim(hda, p))
            {
                intel_hda_reclaim_period_index(hda, p);
                reclaimed = RT_TRUE;
            }
        }
    }
}

static void intel_hda_stream_irq(struct intel_hda *hda)
{
    rt_uint8_t sts;

    RT_UNUSED(hda);

    sts = sd_readb(hda, HDA_SD_OUT_BASE, STS);
    if (sts & SD_INT_MASK)
    {
        sd_writeb(hda, HDA_SD_OUT_BASE, STS, sts & SD_INT_MASK);
    }
}

static rt_err_t intel_hda_audio_start(struct rt_audio_device *audio, int stream)
{
    struct intel_hda *hda = raw_to_intel_hda(audio);

    if (stream == AUDIO_STREAM_REPLAY)
    {
        hda->stream = AUDIO_STREAM_REPLAY;
        hda->playback_active = RT_TRUE;
        hda->dma_started = RT_FALSE;
        hda->last_reclaimed_period = 0xffffffff;
        hda->last_lpib = 0;

        intel_hda_period_reset_all(hda);
        intel_hda_replay_queue_reset(hda);
        intel_hda_sync_output_format(hda);

        /* Configure the output widget and codec */
        intel_hda_configure_output(hda);

        /* Setup stream descriptor, BDL, and DMA position */
        intel_hda_setup_stream(hda);

        rt_timer_start(&hda->poll_timer);

        if (audio->replay &&
                rt_data_queue_len(&audio->replay->queue) > 0)
        {
            intel_hda_replay_push(hda);
        }
    }

    return RT_EOK;
}

static rt_err_t intel_hda_audio_stop(struct rt_audio_device *audio, int stream)
{
    struct intel_hda *hda = raw_to_intel_hda(audio);

    if (stream == AUDIO_STREAM_REPLAY)
    {
        /* Stop poll timer */
        rt_timer_stop(&hda->poll_timer);

        hda->playback_active = RT_FALSE;
        hda->dma_started = RT_FALSE;

        intel_hda_period_reset_all(hda);
        intel_hda_replay_queue_reset(hda);

        /* Stop DMA - use 32-bit access to preserve Stream Tag */
        sd_writel(hda, HDA_SD_OUT_BASE, CTL,
            sd_readl(hda, HDA_SD_OUT_BASE, CTL) & ~SD_CTL_DMA_START);

        /* Disable SDO0 stream interrupt in INTCTL */
        intel_hda_writel(hda, INTCTL,
            intel_hda_readl(hda, INTCTL) & ~HDA_SDO0_STREAM_INT);

        /* Reset stream */
        sd_writeb(hda, HDA_SD_OUT_BASE, CTL, SD_CTL_STREAM_RESET);
        while (!(sd_readb(hda, HDA_SD_OUT_BASE, CTL) & SD_CTL_STREAM_RESET))
        {
            rt_hw_cpu_relax();
        }
        sd_writeb(hda, HDA_SD_OUT_BASE, CTL, 0);

        /* Clear status */
        sd_writeb(hda, HDA_SD_OUT_BASE, STS, SD_INT_MASK);

        hda->stream = -1;
        hda->last_reclaimed_period = 0xffffffff;
        hda->last_lpib = 0;
    }

    return RT_EOK;
}

static rt_ssize_t intel_hda_audio_transmit(struct rt_audio_device *audio,
        const void *write_buf, void *read_buf, rt_size_t size)
{
    struct intel_hda *hda = raw_to_intel_hda(audio);
    rt_uint32_t offset;

    RT_UNUSED(read_buf);

    offset = (rt_uint32_t)((rt_ubase_t)write_buf - (rt_ubase_t)hda->audio_buffer);
    if (offset >= hda->audio_buffer_size)
    {
        LOG_E("transmit: invalid offset %u >= %u", offset, hda->audio_buffer_size);
        return 0;
    }

    rt_hw_dmb();

    return size;
}

static void intel_hda_audio_buffer_info(struct rt_audio_device *audio,
        struct rt_audio_buf_info *info)
{
    struct intel_hda *hda = raw_to_intel_hda(audio);

    info->buffer = (rt_uint8_t *)hda->audio_buffer;
    info->total_size = hda->audio_buffer_size;
    info->block_size = HDA_BUFFER_SIZE;
    info->block_count = HDA_BDL_COUNT;

}

const static struct rt_audio_ops intel_hda_audio_ops =
{
    .getcaps = intel_hda_audio_getcaps,
    .configure = intel_hda_audio_configure,
    .init = intel_hda_audio_init,
    .start = intel_hda_audio_start,
    .stop = intel_hda_audio_stop,
    .transmit = intel_hda_audio_transmit,
    .buffer_info = intel_hda_audio_buffer_info,
};

static void intel_hda_poll_timer(void *parameter)
{
    struct intel_hda *hda = parameter;

    if (hda->stream != AUDIO_STREAM_REPLAY || !hda->playback_active)
    {
        return;
    }
    intel_hda_schedule_replay(hda);
}

/*
 * Interrupt handler - following Linux driver pattern
 */
static void intel_hda_isr(int irqno, void *param)
{
    struct intel_hda *hda = param;
    rt_uint32_t isr;
    rt_uint8_t sts;
    rt_uint8_t rirbsts;

    RT_UNUSED(irqno);

    isr = intel_hda_readl(hda, INTSTS);

    /* Handle controller interrupt (RIRB, state change) */
    if (isr & ICH6_INT_CTRL_EN)
    {
        rirbsts = intel_hda_readb(hda, RIRBSTS);
        if (rirbsts & (ICH6_RBSTS_IRQ | ICH6_RBSTS_OVERRUN))
        {
            intel_hda_writeb(hda, RIRBSTS, rirbsts);
        }

        /* Clear STATESTS if any */
        rt_uint16_t statests = intel_hda_readw(hda, STATESTS);
        if (statests)
        {
            intel_hda_writew(hda, STATESTS, statests);
        }
    }

    /* SDO0 is stream #4 in INTSTS (see QEMU intel_hda_update_int_sts) */
    if (isr & HDA_SDO0_STREAM_INT)
    {
        sts = sd_readb(hda, HDA_SD_OUT_BASE, STS);

        if (hda->stream == AUDIO_STREAM_REPLAY && hda->playback_active)
        {
            if (sts & SD_INT_COMPLETE)
            {
                intel_hda_stream_irq(hda);
            }
        }

        if (sts & (SD_INT_DESC_ERR | SD_INT_FIFO_ERR))
        {
            LOG_E("Stream error: sts=0x%02x", sts);
        }
    }

    if (isr)
    {
        intel_hda_writel(hda, INTSTS, isr);
    }
}

/*
 * Controller reset
 */
static void intel_hda_reset(struct intel_hda *hda)
{
    int timeout;

    /* Clear CORB/RIRB RUN bits before reset */
    intel_hda_writeb(hda, CORBCTL, 0);
    intel_hda_writeb(hda, RIRBCTL, 0);

    timeout = 10000;
    while ((intel_hda_readb(hda, CORBCTL) & ICH6_CORBCTL_RUN) ||
        (intel_hda_readb(hda, RIRBCTL) & ICH6_RBCTL_DMA_EN))
    {
        if (--timeout == 0)
        {
            break;
        }
        rt_hw_cpu_relax();
    }

    /* Reset the CRST bit and wait until hardware is in reset */
    intel_hda_writel(hda, GCTL, 0);

    timeout = 10000;
    while (intel_hda_readl(hda, GCTL) & ICH6_GCTL_RESET)
    {
        if (--timeout == 0)
        {
            break;
        }
        rt_hw_cpu_relax();
    }

    rt_hw_dmb();

    /* Take the hardware out of reset */
    intel_hda_writel(hda, GCTL, ICH6_GCTL_RESET);

    timeout = 10000;
    while ((intel_hda_readl(hda, GCTL) & ICH6_GCTL_RESET) == 0)
    {
        if (--timeout == 0)
        {
            break;
        }
        rt_hw_cpu_relax();
    }

    /* Second reset cycle for reliable codec discovery */
    intel_hda_writew(hda, WAKEEN, 0);
    intel_hda_writew(hda, STATESTS, intel_hda_readw(hda, STATESTS));

    intel_hda_writel(hda, GCTL, 0);
    timeout = 10000;
    while (intel_hda_readl(hda, GCTL) & ICH6_GCTL_RESET)
    {
        if (--timeout == 0)
        {
            break;
        }
        rt_hw_cpu_relax();
    }
    rt_hw_dmb();
    intel_hda_writel(hda, GCTL, ICH6_GCTL_RESET);
    timeout = 10000;
    while ((intel_hda_readl(hda, GCTL) & ICH6_GCTL_RESET) == 0)
    {
        if (--timeout == 0)
        {
            break;
        }
        rt_hw_cpu_relax();
    }

    intel_hda_writew(hda, WAKEEN, 0x7fff);
    intel_hda_writel(hda, INTCTL, 0);

    intel_hda_setup_corb(hda);
    intel_hda_setup_rirb(hda);

    /* Wait 25 frames (521 us) before enumerating codecs */
    rt_hw_us_delay(521);

    intel_hda_enumerate_codecs(hda);
}

/*
 * PCI driver: probe and remove
 */
static rt_err_t intel_hda_probe(struct rt_pci_device *pdev)
{
    rt_err_t err;
    const char *audio_name;
    char dev_name[RT_NAME_MAX];
    struct intel_hda *hda;
    int timeout;

    hda = rt_calloc(1, sizeof(*hda));
    if (!hda)
    {
        return -RT_ENOMEM;
    }
    hda->pdev = pdev;
    hda->stream = -1;
    hda->playback_active = RT_FALSE;
    hda->last_reclaimed_period = 0xffffffff;

    hda->ich6_reg_base = rt_pci_iomap(pdev, ICH6_REG_BAR);
    if (!hda->ich6_reg_base)
    {
        err = -RT_EIO;
        goto _free_hda;
    }

    hda->ring_buffer = rt_dma_alloc_coherent(&pdev->parent, HDA_RING_BUF_SIZE, &hda->ring_buffer_dma);
    if (!hda->ring_buffer)
    {
        err = -RT_ENOMEM;
        goto _free_iomap;
    }
    rt_memset(hda->ring_buffer, 0, HDA_RING_BUF_SIZE);

    hda->audio_buffer_size = HDA_BDL_COUNT * HDA_BUFFER_SIZE;
    hda->audio_buffer = rt_dma_alloc_coherent(&pdev->parent, hda->audio_buffer_size, &hda->audio_buffer_dma);
    if (!hda->audio_buffer)
    {
        err = -RT_ENOMEM;
        goto _free_ring;
    }
    rt_memset(hda->audio_buffer, 0, hda->audio_buffer_size);

    rt_pci_set_master(pdev);
    intel_hda_reset(hda);

    if (!hda->output.node_id)
    {
        LOG_W("No audio output widget found");
        err = -RT_ERROR;
        goto _free_ring;
    }

    rt_dm_dev_set_name_auto(&hda->parent.parent, "sound");
    audio_name = rt_dm_dev_get_name(&hda->parent.parent);
    hda->parent.ops = (struct rt_audio_ops *)&intel_hda_audio_ops;

    rt_timer_init(&hda->poll_timer, "hda_poll",
                  intel_hda_poll_timer, hda,
                  rt_tick_from_millisecond(HDA_REPLAY_POLL_MS),
                  RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER);

    if ((err = rt_audio_register(&hda->parent, audio_name, RT_DEVICE_FLAG_RDWR, hda)) != RT_EOK)
    {
        goto _free_audio_buf;
    }
    if (hda->parent.replay)
    {
        intel_hda_replay_notify_dev = hda;
        hda->parent.replay->queue.evt_notify = intel_hda_replay_queue_notify;
    }

    rt_mutex_init(&hda->replay_push_lock, "hda_plk", RT_IPC_FLAG_PRIO);
    rt_sem_init(&hda->replay_sem, "hda_rpl", 0, RT_IPC_FLAG_FIFO);
    hda->replay_thread = rt_thread_create("hda_rpl",
            intel_hda_replay_thread_entry, hda, 8192, 12, 10);
    if (!hda->replay_thread)
    {
        err = -RT_ENOMEM;
        goto _free_audio_buf;
    }
    rt_thread_startup(hda->replay_thread);

    pdev->parent.user_data = hda;

    rt_snprintf(dev_name, sizeof(dev_name), "%s-hda", audio_name);
    rt_hw_interrupt_install(pdev->irq, intel_hda_isr, hda, dev_name);

    sd_writeb(hda, HDA_SD_OUT_BASE, CTL, SD_CTL_STREAM_RESET);
    timeout = 10000;
    while (!(sd_readb(hda, HDA_SD_OUT_BASE, CTL) & SD_CTL_STREAM_RESET))
    {
        if (--timeout == 0)
        {
            break;
        }
        rt_hw_cpu_relax();
    }
    rt_hw_us_delay(100);
    sd_writeb(hda, HDA_SD_OUT_BASE, CTL, 0);
    timeout = 10000;
    while (sd_readb(hda, HDA_SD_OUT_BASE, CTL) & SD_CTL_STREAM_RESET)
    {
        if (--timeout == 0)
        {
            break;
        }
        rt_hw_cpu_relax();
    }

    sd_writeb(hda, HDA_SD_OUT_BASE, STS, 0xff);
    intel_hda_writeb(hda, RIRBSTS, ICH6_RBSTS_IRQ | ICH6_RBSTS_OVERRUN);
    intel_hda_writel(hda, INTSTS, intel_hda_readl(hda, INTSTS));
    intel_hda_writel(hda, INTCTL, ICH6_INT_GLOBAL_EN | ICH6_INT_CTRL_EN);
    rt_pci_irq_unmask(pdev);

    LOG_I("Intel HD Audio v%d.%d codec=%d dac=%d pin=%d",
            intel_hda_readb(hda, VMAJ), intel_hda_readb(hda, VMIN),
            hda->output.codec, hda->output.node_id, hda->output.pin_nid);

    return RT_EOK;

_free_audio_buf:
    intel_hda_replay_thread_stop(hda);
    rt_timer_detach(&hda->poll_timer);
    rt_dma_free_coherent(&pdev->parent, hda->audio_buffer_size, hda->audio_buffer, hda->audio_buffer_dma);
_free_ring:
    rt_dma_free_coherent(&pdev->parent, HDA_RING_BUF_SIZE, hda->ring_buffer, hda->ring_buffer_dma);
_free_iomap:
    rt_iounmap(hda->ich6_reg_base);
_free_hda:
    rt_free(hda);

    return err;
}

static rt_err_t intel_hda_remove(struct rt_pci_device *pdev)
{
    struct intel_hda *hda = pdev->parent.user_data;

    if (intel_hda_replay_notify_dev == hda)
    {
        intel_hda_replay_notify_dev = RT_NULL;
    }
    intel_hda_replay_thread_stop(hda);
    rt_timer_stop(&hda->poll_timer);
    rt_timer_detach(&hda->poll_timer);
    rt_pci_irq_mask(pdev);
    rt_pic_detach_irq(pdev->irq, hda);

    rt_device_unregister(&hda->parent.parent);

    if (hda->audio_buffer)
    {
        rt_dma_free_coherent(&pdev->parent, hda->audio_buffer_size, hda->audio_buffer, hda->audio_buffer_dma);
    }
    if (hda->ring_buffer)
    {
        rt_dma_free_coherent(&pdev->parent, HDA_RING_BUF_SIZE, hda->ring_buffer, hda->ring_buffer_dma);
    }
    rt_iounmap(hda->ich6_reg_base);
    rt_free(hda);

    return RT_EOK;
}

static const struct rt_pci_device_id intel_hda_pci_ids[] =
{
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_INTEL, 0x2668), .data = "6" },
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_INTEL, 0x27d8), .data = "9" },
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_INTEL, 0x293e), .data = "9" },
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_INTEL, 0x293f), .data = "9" },
    { /* Sentinel */ }
};

static struct rt_pci_driver intel_hda_driver =
{
    .name = "intel-hda",

    .ids = intel_hda_pci_ids,
    .probe = intel_hda_probe,
    .remove = intel_hda_remove,
};
RT_PCI_DRIVER_EXPORT(intel_hda_driver);
