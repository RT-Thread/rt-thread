/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the people's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef __SUNXI_MAD_H_
#define __SUNXI_MAD_H_

#include <aw_common.h>
#include <hal_clk.h>
#include <hal_dma.h>
#include <snd_core.h>
#include <snd_pcm.h>
#include <snd_io.h>

#include "sunxi-pcm.h"

/* memory mapping */
#define MAD_BASE SUNXI_MAD_PBASE
#define MAD_SRAM_DMA_SRC_ADDR SUNXI_MAD_SRAM_PBASE

#ifdef CONFIG_ARCH_SUN8IW18P1
/* SUN8IW18P1 should not be setup. */
#undef MAD_CLK_ALWAYS_ON
//#undef SUNXI_LPSD_CLK_ALWAYS_ON
#define SUNXI_LPSD_CLK_ALWAYS_ON
#undef SUNXI_MAD_DATA_INT_USE
//#define SUNXI_MAD_DATA_INT_USE
#define SUNXI_MAD_SRAM_SUSPEND_RESET

/* 128k bytes */
#define MAD_SRAM_SIZE_VALUE 0x80
#endif

/*memory mapping*/
#ifndef MAD_BASE
#define MAD_BASE (0x05400000)
#endif
#ifndef MAD_SRAM_DMA_SRC_ADDR
#define MAD_SRAM_DMA_SRC_ADDR (0x05480000)
#endif
/* 128k bytes */
#ifndef MAD_SRAM_SIZE_VALUE
#define MAD_SRAM_SIZE_VALUE 0x80
#endif

enum mad_sram_bmode {
        MAD_SRAM_BMODE_NORMAL = 0,
        MAD_SRAM_BMODE_BOOT = 1,
};

enum mad_path_sel {
        MAD_PATH_NONE = 0,
        MAD_PATH_I2S0 = 1,
        MAD_PATH_CODEC = 2,
        MAD_PATH_DMIC = 3,
        MAD_PATH_I2S1 = 4,
        MAD_PATH_I2S2 = 5,
};

#ifdef CONFIG_ARCH_SUN8IW18P1
#undef SUNXI_MAD_DATA_INT_USE
#endif

#define EVT_MAX_SIZE            256
#define SUNXI_NETLINK_MAD       30

/*------------------MAD register definition--------------------*/
#define SUNXI_MAD_CTRL                  0x00
#define SUNXI_MAD_SRAM_POINT            0x04
#define SUNXI_MAD_SRAM_SIZE             0x08
#define SUNXI_MAD_SRAM_RD_POINT         0x0C
#define SUNXI_MAD_RD_SIZE               0x10
#define SUNXI_MAD_SRAM_STORE_TH         0x14
#define SUNXI_MAD_SRAM_AHB1_TX_TH       0x18
#define SUNXI_MAD_SRAM_AHB1_RX_TH       0x1C
#define SUNXI_MAD_SRAM_WAKE_BACK_DATA   0x20
#define SUNXI_MAD_AD_PATH_SEL           0x24
#define SUNXI_MAD_LPSD_AD_SYNC_FC       0x28
#define SUNXI_MAD_LPSD_TH               0x2C
#define SUNXI_MAD_LPSD_RRUN             0x30
#define SUNXI_MAD_LPSD_RSTOP            0x34
#define SUNXI_MAD_LPSD_ECNT             0x38
#define SUNXI_MAD_SRAM_CH_MASK          0x3C
#define SUNXI_MAD_LPSD_CH_MASK          0x40
#define SUNXI_MAD_SRAM_SEC_REGION_REG   0x44
#define SUNXI_MAD_SRAM_PRE_DSIZE        0x48
#define SUNXI_MAD_DMA_TF_SIZE           0x4C
#define SUNXI_MAD_DMA_TF_LAST_SIZE      0x50
#define SUNXI_MAD_INT_ST_CLR            0x60
#define SUNXI_MAD_INT_MASK              0x64
#define SUNXI_MAD_STA                   0x68
#define SUNXI_MAD_DEBUG                 0x6C

/*SUNXI_MAD_CTRL: 0x00*/
#define AUDIO_DATA_SYNC_FRC             7
#define SRAM_RST                        6
#define DMA_TYPE                        5
#define DMA_EN                          4
#define CPUS_RD_DONE                    3
#define GO_ON_SLEEP                     2
#define KEY_WORD_OK                     1
#define MAD_EN                          0
/* DMA type*/
#define DMA_TYPE_MASK                   0x1
#define DMA_TYPE_IO                     0x1
#define DMA_TYPE_MEM                    0x0

/*SUNXI_MAD_SRAM_POINT: 0x04*/
#define MAD_SRAM_PONT                   0

/*SUNXI_MAD_SRAM_SIZE: 0x08*/
#define MAD_SRAM_SIZE                   0

/*SUNXI_MAD_SRAM_RD_POINT: 0x0C*/
#define MAD_SRAM_RD_POINT               0

/*SUNXI_MAD_SRAM_RD_SIZE(unit: half word): 0x10*/
#define MAD_SRAM_RD_SIZE                0

/*SUNXI_MAD_SRAM_STORE_TH(unit: half word): 0x14*/
#define MAD_SRAM_STORE_TH               0

/*SUNXI_MAD_SRAM_AHB1_TX_TH(unit: byte): 0x18*/
#define MAD_SRAM_AHB1_TX_TH             0

/*SUNXI_MAD_SRAM_AHB1_RX_TH(unit: byte): 0x1C*/
#define MAD_SRAM_AHB1_RX_TH             0

/*SUNXI_MAD_SRAM_WAKE_BACK_DATA(unit: frame): 0x20*/
#define MAD_SRAM_WAKE_BACK_DATA         0

/*SUNXI_MAD_AD_PATH_SEL: 0x24*/
#define MAD_AD_PATH_SEL                 0
#define MAD_AD_PATH_SEL_MASK            0xF
/*MAD audio src sel*/
#define MAD_AD_PATH_NO_SRC              0x0
#define MAD_AD_PATH_I2S0_SRC            0x1
#define MAD_AD_PATH_CODEC_SRC           0x2
#define MAD_AD_PATH_DMIC_SRC            0x3
#define MAD_AD_PATH_I2S1_SRC            0x4
#define MAD_AD_PATH_I2S2_SRC            0x5

/*SUNXI_MAD_LPSD_AD_SYNC_FC: 0x28*/
#define MAD_LPSD_AD_SYNC_FC             0
#define MAD_LPSD_AD_SYNC_FC_DEF         0X20

/*SUNXI_MAD_LPSD_TH: 0x2C*/
#define MAD_LPSD_TH                     0

/*SUNXI_MAD_LPSD_RRUN: 0x30*/
#define MAD_LPSD_RRUN                   0

/*SUNXI_MAD_LPSD_RSTOP: 0x34*/
#define MAD_LPSD_RSTOP                  0

/*SUNXI_MAD_LPSD_ECNT: 0x38*/
#define MAD_LPSD_ECNT                   0

/*SUNXI_MAD_SRAM_CH_MASK: 0x3C*/
#define MAD_CH_CHANGE_EN                30
#define MAD_CH_COM_NUM                  26
#define MAD_AD_SRC_CH_NUM               21
#define MAD_SRAM_CH_NUM                 16
#define MAD_SRAM_CH_MASK                0

#define MAD_SRAM_CH_NUM_MASK    0x1F

/*MAD channel change sel*/
#define MAD_CH_COM_NUM_MASK             0xF
#define MAD_CH_COM_NON                  0x0
#define MAD_CH_COM_2CH_TO_4CH           0x1
#define MAD_CH_COM_2CH_TO_6CH           0x2
#define MAD_CH_COM_2CH_TO_8CH           0x3
#define MAD_CH_COM_4CH_TO_6CH           0x4
#define MAD_CH_COM_4CH_TO_8CH           0x5

/*SUNXI_MAD_LPSD_CH_MASK: 0x40*/
#define MAD_LPSD_DCBLOCK_EN             20
#define MAD_LPSD_CH_NUM                 16
#define MAD_LPSD_CH_MASK                0
/*LPSD receive 0/1 audio channel mask*/
#define MAD_LPSD_CH_NUM_MASK            0xF
/*LPSD AUDIO channel num sel*/
#define MAD_LPSD_CH_NUM_NON             0x0
#define MAD_LPSD_CH_NUM_1CH             0x1

/*SUNXI_MAD_SRAM_SEC_REGION: 0x44*/
#define MAD_SRAM_SEC_REGION             0

/*SUNXI_MAD_SRAM_PRE_DATA_SIZE(unit: half word): 0x48*/
#define MAD_SRAM_PRE_DATA_SIZE          0

/*SUNXI_MAD_DMA_TF_SIZE: 0x4C*/
#define MAD_DMA_TF_SIZE                 0

/*SUNXI_MAD_DMA_TF_LAST_SIZE: 0x50*/
#define MAD_DMA_TF_LAST_SIZE            0

/*SUNXI_MAD_INT_ST_CLR: 0x60*/
#define DATA_REQ_INT                    1
#define WAKE_INT                        0

/*SUNXI_MAD_INT_MASK: 0x64*/
#define DATA_REQ_INT_MASK               1
#define MAD_REQ_INT_MASK                0

/*SUNXI_MAD_STATE_REG: 0x68*/
#define MAD_LPSD_STAT                   8
#define MAD_STATE                       4
#define MAD_SRAM_FULL                   2
#define MAD_SRAM_EMPTY                  1
#define MAD_RUN                         0
/*MAD STATE(read only)*/
#define MAD_STATE_IDLE                  0x0
#define MAD_STATE_WAIT                  0x1
#define MAD_STATE_RUN                   0x2
#define MAD_STATE_NORMAL                0x4

/*SUNXI_MAD_DEBUG: 0x6C*/
#define MAD_CFG_ERR                     4
#define MAD_SRAM_FULL_ERR               3
#define MAD_SRAM_EMPTY_ERR              2
#define DATA_SRAM_ADDR_ERR              1
#define MAD_SRAM_SEC_ERR                0
/*MAD_CFG_ERR mask*/
#define MAD_CFG_ERR_MASK                0x3

/* for mad clk*/
#define MAD_SRAM_BMODE_CTRL 24
#define SRAM_BMODE_CTRL_REG 0x3000004

enum sunxi_mad_standby_debug_flag {
    SUNXI_MAD_DEBUG_STANDBY_NULL = 0,
    SUNXI_MAD_DEBUG_STANDBY_SUSPEND = 1,
    SUNXI_MAD_DEBUG_STANDBY_RESUME = 2,
};

enum sunxi_mad_irq_work_flag {
    SUNXI_MAD_NULL_IRQ_WORK = 0,
    SUNXI_MAD_LPSD_IRQ_WORK = 1,
    SUNXI_MAD_DATA_IRQ_WORK = 2,
};

enum sunxi_mad_sram_reset_flag {
    SUNXI_MAD_SRAM_RESET_IDLE = 0,
    SUNXI_MAD_SRAM_RESET_START = 1,
    SUNXI_MAD_SRAM_RESET_END = 2,
};

enum sunxi_mad_status {
    SUNXI_MAD_OPEN = 0,
    SUNXI_MAD_PARAMS = 1,
    SUNXI_MAD_SUSPEND = 2,
    SUNXI_MAD_RESUME = 3,
    SUNXI_MAD_CLOSE = 4,
};

enum sunxi_mad_dma_type {
    SUNXI_MAD_DMA_MEM = 0,
    SUNXI_MAD_DMA_IO = 1,
};

enum sunxi_mad_standby_flag {
    /* bit0 for sram IO type when standby */
    SUNXI_MAD_STANDBY_SRAM_MEM = 0x1,
};

enum sunxi_mad_wakeup_flag {
    /* bit0 for wakeup source */
    SUNXI_MAD_WAKEUP_OFF = 0x0,
    SUNXI_MAD_WAKEUP_ON = 0x1,
    /* bit1 for wakeup use or no */
    SUNXI_MAD_WAKEUP_USE = 0x2,

    /* bit2 for lpsd wakeup */
    SUNXI_MAD_WAKEUP_LPSD_IRQ = 0x4,
    /* bit3 for mad irq wakeup */
    SUNXI_MAD_WAKEUP_MAD_IRQ = 0x8,
    /* bit4 for other irq wakeup */
    SUNXI_MAD_WAKEUP_OTHER = 0x10,
};

struct sunxi_mad_priv {
    struct sunxi_mad_info *sunxi_mad;
    unsigned int mad_bind;
    unsigned int mad_suspend;
    /* mad params */
    unsigned int sample_rate;
    unsigned int lpsd_chan_sel;
    unsigned int standby_chan_sel;
    unsigned int audio_src_chan_num;
};

struct sunxi_mad_info {
    hal_clk_id_t mad_clk;
    hal_clk_id_t mad_cfg_clk;
    hal_clk_id_t mad_ad_clk;
    hal_clk_id_t lpsd_clk;
    hal_clk_id_t pll_clk;
    hal_clk_id_t hosc_clk;

    freert_spinlock_t resume_spin;

    unsigned int pll_audio_src_used;
    unsigned int hosc_src_used;

    void *mem_base;

    unsigned int mad_irq;
    unsigned int lpsd_irq;
    QueueHandle_t irq_queue;
    TaskHandle_t pxMadIrqTask;

    unsigned int sram_rd_point;
    unsigned int audio_src_path;

    unsigned int mad_bind;

    int status;
    unsigned int wakeup_flag;
    unsigned int suspend_flag;
    unsigned int sram_reset_flag;
    int standby_sram_type;
    int wakeup_irq_en;
    unsigned int ref_count;

    struct sunxi_mad_priv mad_priv;

    void *private_data;
};

int sunxi_mad_sram_set_reset_flag(enum sunxi_mad_sram_reset_flag reset_flag);
enum sunxi_mad_sram_reset_flag sunxi_mad_sram_get_reset_flag(void);
int sunxi_mad_sram_wait_reset_flag(enum sunxi_mad_sram_reset_flag reset_flag,
                        unsigned int time_out_msecond);

void sunxi_mad_sram_chan_params(unsigned int mad_channels);
struct sunxi_mad_info *sunxi_mad_get_mad_info(void);

void sunxi_mad_clk_enable(bool val);
void sunxi_mad_ad_clk_enable(bool val);
void sunxi_mad_cfg_clk_enable(bool val);
void sunxi_mad_module_clk_enable(bool val);
void sunxi_lpsd_clk_enable(bool val);

/* for mad interrupt */
void sunxi_lpsd_int_stat_clr(void);
void sunxi_mad_set_lpsd_req(bool enable);
void sunxi_mad_set_data_req(bool enable);

/* for mad init */
int sunxi_mad_open(void);
int sunxi_mad_close(void);
void sunxi_mad_sram_init(void);
void sunxi_mad_lpsd_init(void);
void sunxi_sram_ahb1_threshole_init(void);
void sunxi_mad_standby_chan_sel(unsigned int num);
void sunxi_lpsd_chan_sel(unsigned int num);
void sunxi_mad_audio_src_chan_num(unsigned int num);
void sunxi_sram_dma_config(struct sunxi_dma_params *capture_dma_param);
int sunxi_mad_hw_params(unsigned int mad_channels, unsigned int sample_rate);
int sunxi_mad_audio_source_sel(unsigned int path_sel, unsigned int enable);
int sunxi_mad_suspend_external(void);
int sunxi_mad_resume_external(void);
void sunxi_mad_dma_enable(bool enable);
void sunxi_mad_dma_type(enum sunxi_mad_dma_type dma_type);
int sunxi_mad_enable(bool enable);
void sunxi_mad_set_go_on_sleep(bool enable);
void sunxi_mad_sram_set_reset_bit(void);

#ifdef CONFIG_SUNXI_MAD_DEBUG
int sunxi_mad_schd_timeout(SemaphoreHandle_t semaphore, long ms);
void sunxi_mad_schd_wakeup(SemaphoreHandle_t semaphore);
#endif

/* for probe mad module */
int sunxi_mad_platform_probe(struct snd_platform *platform);
int sunxi_mad_platform_remove(struct snd_platform *platform);
#endif /* SUNXI_MAD_H */
