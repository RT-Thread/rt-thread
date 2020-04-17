/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of Nuvoton Technology Corp. nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* Change Logs:
* Date            Author           Notes
* 2020-2-7        Wayne            First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_PDMA)

#include <rtdevice.h>
#include <rtthread.h>
#include <drv_pdma.h>
#include <nu_bitutil.h>

/* Private define ---------------------------------------------------------------*/
// RT_DEV_NAME_PREFIX pdma

#ifndef NU_PDMA_MEMFUN_ACTOR_MAX
    #define NU_PDMA_MEMFUN_ACTOR_MAX 4
#endif

#define NU_PDMA_CH_MAX (PDMA_CH_MAX)     /* Specify maximum channels of PDMA */
#define NU_PDMA_CH_Pos (0)               /* Specify first channel number of PDMA */
#define NU_PDMA_CH_Msk (((1 << NU_PDMA_CH_MAX) - 1) << NU_PDMA_CH_Pos)

/* Private typedef --------------------------------------------------------------*/
struct nu_pdma_periph_ctl
{
    uint32_t     m_u32Peripheral;
    nu_pdma_memctrl_t  m_eMemCtl;
};
typedef struct nu_pdma_periph_ctl nu_pdma_periph_ctl_t;

struct nu_pdma_chn
{
    nu_pdma_cb_handler_t   m_pfnCBHandler;
    void                  *m_pvUserData;
    uint32_t               m_u32EventFilter;
    uint32_t               m_u32IdleTimeout_us;
    nu_pdma_periph_ctl_t   m_spPeripCtl;
};
typedef struct nu_pdma_chn nu_pdma_chn_t;

struct nu_pdma_memfun_actor
{
    int         m_i32ChannID;
    uint32_t    m_u32Result;
    uint32_t    m_u32TrigTransferCnt;
    rt_sem_t    m_psSemMemFun;
} ;
typedef struct nu_pdma_memfun_actor *nu_pdma_memfun_actor_t;

/* Private functions ------------------------------------------------------------*/
static int nu_pdma_peripheral_set(uint32_t u32PeriphType);
static void nu_pdma_init(void);
static void nu_pdma_channel_enable(int i32ChannID);
static void nu_pdma_channel_disable(int i32ChannID);
static void nu_pdma_channel_reset(int i32ChannID);
static rt_err_t nu_pdma_timeout_set(int i32ChannID, int i32Timeout_us);
static void nu_pdma_periph_ctrl_fill(int i32ChannID, int i32CtlPoolIdx);
static rt_size_t nu_pdma_memfun(void *dest, void *src, uint32_t u32DataWidth, unsigned int count, nu_pdma_memctrl_t eMemCtl);
static void nu_pdma_memfun_cb(void *pvUserData, uint32_t u32Events);
static void nu_pdma_memfun_actor_init(void);
static int nu_pdma_memfun_employ(void);
static int nu_pdma_non_transfer_count_get(int32_t i32ChannID);

/* Public functions -------------------------------------------------------------*/


/* Private variables ------------------------------------------------------------*/
static volatile int nu_pdma_inited = 0;
static volatile uint32_t nu_pdma_chn_mask = 0;
static nu_pdma_chn_t nu_pdma_chn_arr[NU_PDMA_CH_MAX];
static rt_mutex_t g_mutex_res = RT_NULL;
static volatile uint32_t nu_pdma_memfun_actor_mask = 0;
static volatile uint32_t nu_pdma_memfun_actor_maxnum = 0;
static rt_sem_t nu_pdma_memfun_actor_pool_sem = RT_NULL;
static rt_mutex_t nu_pdma_memfun_actor_pool_lock = RT_NULL;

static const nu_pdma_periph_ctl_t g_nu_pdma_peripheral_ctl_pool[ ] =
{
    // M2M
    { PDMA_MEM, eMemCtl_SrcInc_DstInc },

    // M2P
    { PDMA_USB_TX,   eMemCtl_SrcInc_DstFix },

    { PDMA_UART0_TX, eMemCtl_SrcInc_DstFix },
    { PDMA_UART1_TX, eMemCtl_SrcInc_DstFix },
    { PDMA_UART2_TX, eMemCtl_SrcInc_DstFix },
    { PDMA_UART3_TX, eMemCtl_SrcInc_DstFix },
    { PDMA_UART4_TX, eMemCtl_SrcInc_DstFix },
    { PDMA_UART5_TX, eMemCtl_SrcInc_DstFix },
    { PDMA_UART6_TX, eMemCtl_SrcInc_DstFix },
    { PDMA_UART7_TX, eMemCtl_SrcInc_DstFix },

    { PDMA_USCI0_TX, eMemCtl_SrcInc_DstFix },
    { PDMA_USCI1_TX, eMemCtl_SrcInc_DstFix },

    { PDMA_QSPI0_TX, eMemCtl_SrcInc_DstFix },
    { PDMA_QSPI1_TX, eMemCtl_SrcInc_DstFix },

    { PDMA_SPI0_TX,  eMemCtl_SrcInc_DstFix },
    { PDMA_SPI1_TX,  eMemCtl_SrcInc_DstFix },
    { PDMA_SPI2_TX,  eMemCtl_SrcInc_DstFix },
    { PDMA_SPI3_TX,  eMemCtl_SrcInc_DstFix },

    { PDMA_I2C0_TX,  eMemCtl_SrcInc_DstFix },
    { PDMA_I2C1_TX,  eMemCtl_SrcInc_DstFix },
    { PDMA_I2C2_TX,  eMemCtl_SrcInc_DstFix },

    { PDMA_I2S0_TX,  eMemCtl_SrcInc_DstFix },

    { PDMA_DAC0_TX,  eMemCtl_SrcInc_DstFix },
    { PDMA_DAC1_TX,  eMemCtl_SrcInc_DstFix },

    { PDMA_EPWM0_CH0_TX, eMemCtl_SrcInc_DstFix },
    { PDMA_EPWM0_CH1_TX, eMemCtl_SrcInc_DstFix },
    { PDMA_EPWM0_CH2_TX, eMemCtl_SrcInc_DstFix },
    { PDMA_EPWM0_CH3_TX, eMemCtl_SrcInc_DstFix },
    { PDMA_EPWM0_CH4_TX, eMemCtl_SrcInc_DstFix },
    { PDMA_EPWM1_CH0_TX, eMemCtl_SrcInc_DstFix },
    { PDMA_EPWM1_CH1_TX, eMemCtl_SrcInc_DstFix },
    { PDMA_EPWM1_CH2_TX, eMemCtl_SrcInc_DstFix },
    { PDMA_EPWM1_CH3_TX, eMemCtl_SrcInc_DstFix },
    { PDMA_EPWM1_CH4_TX, eMemCtl_SrcInc_DstFix },

    // P2M
    { PDMA_USB_RX, eMemCtl_SrcFix_DstInc },

    { PDMA_UART0_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_UART1_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_UART2_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_UART3_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_UART4_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_UART5_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_UART6_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_UART7_RX, eMemCtl_SrcFix_DstInc },

    { PDMA_USCI0_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_USCI1_RX, eMemCtl_SrcFix_DstInc },

    { PDMA_QSPI0_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_QSPI1_RX, eMemCtl_SrcFix_DstInc },

    { PDMA_SPI0_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_SPI1_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_SPI2_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_SPI3_RX, eMemCtl_SrcFix_DstInc },

    { PDMA_EPWM0_P1_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_EPWM0_P2_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_EPWM0_P3_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_EPWM1_P1_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_EPWM1_P2_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_EPWM1_P3_RX, eMemCtl_SrcFix_DstInc },

    { PDMA_I2C0_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_I2C1_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_I2C2_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_I2S0_RX, eMemCtl_SrcFix_DstInc },

    { PDMA_EADC0_RX, eMemCtl_SrcFix_DstInc },
    { PDMA_EADC1_RX, eMemCtl_SrcFix_DstInc },
};
#define NU_PERIPHERAL_SIZE ( sizeof(g_nu_pdma_peripheral_ctl_pool) / sizeof(g_nu_pdma_peripheral_ctl_pool[0]) )

static struct nu_pdma_memfun_actor nu_pdma_memfun_actor_arr[NU_PDMA_MEMFUN_ACTOR_MAX];

static int nu_pdma_peripheral_set(uint32_t u32PeriphType)
{
    int idx = 0;

    while (idx < NU_PERIPHERAL_SIZE)
    {
        if (g_nu_pdma_peripheral_ctl_pool[idx].m_u32Peripheral == u32PeriphType)
            return idx;
        idx++;
    }

    // Not such peripheral
    return -1;
}

static void nu_pdma_periph_ctrl_fill(int i32ChannID, int i32CtlPoolIdx)
{
    nu_pdma_chn_t *psPdmaChann = &nu_pdma_chn_arr[i32ChannID - NU_PDMA_CH_Pos];
    psPdmaChann->m_spPeripCtl.m_u32Peripheral = g_nu_pdma_peripheral_ctl_pool[i32CtlPoolIdx].m_u32Peripheral;
    psPdmaChann->m_spPeripCtl.m_eMemCtl = g_nu_pdma_peripheral_ctl_pool[i32CtlPoolIdx].m_eMemCtl;
}

static void nu_pdma_init(void)
{
    if (nu_pdma_inited)
        return;

    g_mutex_res = rt_mutex_create("pdmalock", RT_IPC_FLAG_FIFO);

    nu_pdma_chn_mask = ~NU_PDMA_CH_Msk;
    rt_memset(nu_pdma_chn_arr, 0x00, sizeof(nu_pdma_chn_t));

    NVIC_EnableIRQ(PDMA_IRQn);

    /* Initialize PDMA setting */
    PDMA_Open(PDMA, NU_PDMA_CH_Msk);
    PDMA_Close(PDMA);

    nu_pdma_inited = 1;
}

static void nu_pdma_channel_enable(int i32ChannID)
{
    PDMA_Open(PDMA, 1 << i32ChannID);
}

static inline void nu_pdma_channel_disable(int i32ChannID)
{
    PDMA->CHCTL &= ~(1 << i32ChannID);
}

static inline void nu_pdma_channel_reset(int i32ChannID)
{
    PDMA->CHRST = (1 << i32ChannID);
}

void nu_pdma_channel_terminate(int i32ChannID)
{
    int i;
    uint32_t u32EnabledChans;
    int ch_mask = 0;

    if (!(nu_pdma_chn_mask & (1 << i32ChannID)))
        goto exit_pdma_channel_terminate;

    rt_mutex_take(g_mutex_res, RT_WAITING_FOREVER);

    // Suspend all channels.
    u32EnabledChans = nu_pdma_chn_mask & NU_PDMA_CH_Msk;
    while ((i = nu_ctz(u32EnabledChans)) != 32)
    {
        ch_mask = (1 << i);
        if (i == i32ChannID)
        {
            u32EnabledChans &= ~ch_mask;
            continue;
        }

        // Pause the channel
        PDMA_PAUSE(PDMA, i);

        // Wait for channel to finish current transfer
        while (PDMA->TACTSTS & ch_mask) { }

        u32EnabledChans &= ~ch_mask;
    } //while

    // Reset specified channel ID
    nu_pdma_channel_reset(i32ChannID);

    // Clean descriptor table control register.
    PDMA->DSCT[i32ChannID].CTL = 0UL;

    // Resume all channels.
    u32EnabledChans = nu_pdma_chn_mask & NU_PDMA_CH_Msk;
    while ((i = nu_ctz(u32EnabledChans)) != 32)
    {
        ch_mask = (1 << i);

        PDMA->CHCTL |= ch_mask;
        PDMA_Trigger(PDMA, i);
        u32EnabledChans &= ~ch_mask;
    }

    rt_mutex_release(g_mutex_res);

exit_pdma_channel_terminate:

    return;
}

static rt_err_t nu_pdma_timeout_set(int i32ChannID, int i32Timeout_us)
{
    rt_err_t ret = RT_EINVAL;

    if (!(nu_pdma_chn_mask & (1 << i32ChannID)))
        goto exit_nu_pdma_timeout_set;

    nu_pdma_chn_arr[i32ChannID - NU_PDMA_CH_Pos].m_u32IdleTimeout_us = i32Timeout_us;

    if (i32Timeout_us && i32ChannID <= 1)   // M480 limit
    {
        uint32_t u32ToClk_Max = 1000000 / (CLK_GetHCLKFreq() / (1 << 8));
        uint32_t u32Divider     = (i32Timeout_us / u32ToClk_Max) / (1 << 16);
        uint32_t u32TOutCnt     = (i32Timeout_us / u32ToClk_Max) % (1 << 16);

        PDMA_DisableTimeout(PDMA,  1 << i32ChannID);
        PDMA_EnableInt(PDMA, i32ChannID, PDMA_INT_TIMEOUT);    // Interrupt type

        if (u32Divider > 7)
        {
            u32Divider = 7;
            u32TOutCnt = (1 << 16);
        }
        PDMA->TOUTPSC |= (u32Divider << (PDMA_TOUTPSC_TOUTPSC1_Pos * i32ChannID));
        PDMA_SetTimeOut(PDMA,  i32ChannID, 1, u32TOutCnt);

        ret = RT_EOK;
    }
    else
    {
        PDMA_DisableInt(PDMA, i32ChannID, PDMA_INT_TIMEOUT);    // Interrupt type
        PDMA_DisableTimeout(PDMA,  1 << i32ChannID);
    }

exit_nu_pdma_timeout_set:

    return -(ret);
}

int nu_pdma_channel_allocate(int32_t i32PeripType)
{
    int i, i32PeripCtlIdx;

    nu_pdma_init();

    if ((i32PeripCtlIdx = nu_pdma_peripheral_set(i32PeripType)) < 0)
        goto exit_nu_pdma_channel_allocate;

    /* Find the position of first '0' in nu_pdma_chn_mask. */
    i = nu_cto(nu_pdma_chn_mask);
    if (i != 32)
    {
        nu_pdma_chn_mask |= (1 << i);
        rt_memset(nu_pdma_chn_arr + i - NU_PDMA_CH_Pos, 0x00, sizeof(nu_pdma_chn_t));

        /* Set idx number of g_nu_pdma_peripheral_ctl_pool */
        nu_pdma_periph_ctrl_fill(i, i32PeripCtlIdx);

        /* Reset channel */
        nu_pdma_channel_reset(i);

        nu_pdma_channel_enable(i);

        return i;
    }

exit_nu_pdma_channel_allocate:
    // No channel available
    return -(RT_ERROR);
}

rt_err_t nu_pdma_channel_free(int i32ChannID)
{
    rt_err_t ret = RT_EINVAL;

    if (! nu_pdma_inited)
        goto exit_nu_pdma_channel_free;

    if (i32ChannID < NU_PDMA_CH_MAX && i32ChannID >= NU_PDMA_CH_Pos)
    {
        nu_pdma_chn_mask &= ~(1 << i32ChannID);
        nu_pdma_channel_disable(i32ChannID);
        ret =  RT_EOK;
    }
exit_nu_pdma_channel_free:

    return -(ret);
}

rt_err_t nu_pdma_callback_register(int i32ChannID, nu_pdma_cb_handler_t pfnHandler, void *pvUserData, uint32_t u32EventFilter)
{
    rt_err_t ret = RT_EINVAL;

    if (!(nu_pdma_chn_mask & (1 << i32ChannID)))
        goto exit_nu_pdma_callback_register;

    nu_pdma_chn_arr[i32ChannID - NU_PDMA_CH_Pos].m_pfnCBHandler = pfnHandler;
    nu_pdma_chn_arr[i32ChannID - NU_PDMA_CH_Pos].m_pvUserData = pvUserData;
    nu_pdma_chn_arr[i32ChannID - NU_PDMA_CH_Pos].m_u32EventFilter = u32EventFilter;

    ret = RT_EOK;

exit_nu_pdma_callback_register:

    return -(ret) ;
}

nu_pdma_cb_handler_t nu_pdma_callback_hijack(int i32ChannID, nu_pdma_cb_handler_t *ppfnHandler_Hijack,
        void **ppvUserData_Hijack, uint32_t *pu32Events_Hijack)
{
    nu_pdma_cb_handler_t pfnHandler_Org = NULL;
    void    *pvUserData_Org;
    uint32_t u32Events_Org;

    RT_ASSERT(ppfnHandler_Hijack != NULL);
    RT_ASSERT(ppvUserData_Hijack != NULL);
    RT_ASSERT(pu32Events_Hijack != NULL);

    if (!(nu_pdma_chn_mask & (1 << i32ChannID)))
        goto exit_nu_pdma_callback_hijack;

    pfnHandler_Org = nu_pdma_chn_arr[i32ChannID - NU_PDMA_CH_Pos].m_pfnCBHandler;
    pvUserData_Org = nu_pdma_chn_arr[i32ChannID - NU_PDMA_CH_Pos].m_pvUserData;
    u32Events_Org  = nu_pdma_chn_arr[i32ChannID - NU_PDMA_CH_Pos].m_u32EventFilter;

    nu_pdma_chn_arr[i32ChannID - NU_PDMA_CH_Pos].m_pfnCBHandler = *ppfnHandler_Hijack;
    nu_pdma_chn_arr[i32ChannID - NU_PDMA_CH_Pos].m_pvUserData = *ppvUserData_Hijack;
    nu_pdma_chn_arr[i32ChannID - NU_PDMA_CH_Pos].m_u32EventFilter = *pu32Events_Hijack;

    *ppfnHandler_Hijack = pfnHandler_Org;
    *ppvUserData_Hijack = pvUserData_Org;
    *pu32Events_Hijack  = u32Events_Org;

exit_nu_pdma_callback_hijack:

    return pfnHandler_Org;
}

static int nu_pdma_non_transfer_count_get(int32_t i32ChannID)
{
    return ((PDMA->DSCT[i32ChannID].CTL & PDMA_DSCT_CTL_TXCNT_Msk) >> PDMA_DSCT_CTL_TXCNT_Pos) + 1;
}

int nu_pdma_transferred_byte_get(int32_t i32ChannID, int32_t i32TriggerByteLen)
{
    int i32BitWidth = 0;
    int cur_txcnt = 0;

    if (!(nu_pdma_chn_mask & (1 << i32ChannID)))
        goto exit_nu_pdma_transferred_byte_get;

    i32BitWidth = PDMA->DSCT[i32ChannID].CTL & PDMA_DSCT_CTL_TXWIDTH_Msk;
    i32BitWidth = (i32BitWidth == PDMA_WIDTH_8) ? 1 : (i32BitWidth == PDMA_WIDTH_16) ? 2 : (i32BitWidth == PDMA_WIDTH_32) ? 4 : 0;

    cur_txcnt = nu_pdma_non_transfer_count_get(i32ChannID);

    return (i32TriggerByteLen - (cur_txcnt) * i32BitWidth);

exit_nu_pdma_transferred_byte_get:

    return -1;
}

nu_pdma_memctrl_t nu_pdma_channel_memctrl_get(int i32ChannID)
{
    nu_pdma_memctrl_t eMemCtrl = eMemCtl_Undefined;

    if (!(nu_pdma_chn_mask & (1 << i32ChannID)))
        goto exit_nu_pdma_channel_memctrl_get;

    eMemCtrl = nu_pdma_chn_arr[i32ChannID - NU_PDMA_CH_Pos].m_spPeripCtl.m_eMemCtl;

exit_nu_pdma_channel_memctrl_get:

    return eMemCtrl;
}

rt_err_t nu_pdma_channel_memctrl_set(int i32ChannID, nu_pdma_memctrl_t eMemCtrl)
{
    rt_err_t ret = RT_EINVAL;
    nu_pdma_chn_t *psPdmaChann = &nu_pdma_chn_arr[i32ChannID - NU_PDMA_CH_Pos];


    if (!(nu_pdma_chn_mask & (1 << i32ChannID)))
        goto exit_nu_pdma_channel_memctrl_set;
    else if ((eMemCtrl < eMemCtl_SrcFix_DstFix) || (eMemCtrl > eMemCtl_SrcInc_DstInc))
        goto exit_nu_pdma_channel_memctrl_set;

    /* PDMA_MEM/SAR_FIX/BURST mode is not supported. */
    if ((psPdmaChann->m_spPeripCtl.m_u32Peripheral == PDMA_MEM) &&
            ((eMemCtrl == eMemCtl_SrcFix_DstInc) || (eMemCtrl == eMemCtl_SrcFix_DstFix)))
        goto exit_nu_pdma_channel_memctrl_set;

    nu_pdma_chn_arr[i32ChannID - NU_PDMA_CH_Pos].m_spPeripCtl.m_eMemCtl = eMemCtrl;

    ret = RT_EOK;

exit_nu_pdma_channel_memctrl_set:

    return -(ret);
}

static void nu_pdma_channel_memctrl_fill(nu_pdma_memctrl_t eMemCtl, uint32_t *pu32SrcCtl, uint32_t *pu32DstCtl)
{
    switch ((int)eMemCtl)
    {
    case eMemCtl_SrcFix_DstFix:
        *pu32SrcCtl = PDMA_SAR_FIX;
        *pu32DstCtl = PDMA_DAR_FIX;
        break;
    case eMemCtl_SrcFix_DstInc:
        *pu32SrcCtl = PDMA_SAR_FIX;
        *pu32DstCtl = PDMA_DAR_INC;
        break;
    case eMemCtl_SrcInc_DstFix:
        *pu32SrcCtl = PDMA_SAR_INC;
        *pu32DstCtl = PDMA_DAR_FIX;
        break;
    case eMemCtl_SrcInc_DstInc:
        *pu32SrcCtl = PDMA_SAR_INC;
        *pu32DstCtl = PDMA_DAR_INC;
        break;
    }
}

rt_err_t nu_pdma_transfer(int i32ChannID, uint32_t u32DataWidth, uint32_t u32AddrSrc, uint32_t u32AddrDst, int32_t i32Length, uint32_t u32IdleTimeout_us)
{
    nu_pdma_periph_ctl_t *psPeriphCtl = NULL;

    uint32_t u32SrcCtl = 0;
    uint32_t u32DstCtl = 0;

    rt_err_t ret = RT_EINVAL;

    if (!(nu_pdma_chn_mask & (1 << i32ChannID)))
        goto exit_nu_pdma_transfer;
    else if (!(u32DataWidth == 8 || u32DataWidth == 16 || u32DataWidth == 32))
        goto exit_nu_pdma_transfer;
    else if ((u32AddrSrc % (u32DataWidth / 8)) || (u32AddrDst % (u32DataWidth / 8)))
        goto exit_nu_pdma_transfer;

    psPeriphCtl = &nu_pdma_chn_arr[i32ChannID - NU_PDMA_CH_Pos].m_spPeripCtl;

    nu_pdma_channel_memctrl_fill(psPeriphCtl->m_eMemCtl, &u32SrcCtl, &u32DstCtl);

    PDMA_DisableTimeout(PDMA,  1 << i32ChannID);

    PDMA_SetTransferCnt(PDMA,
                        i32ChannID,
                        (u32DataWidth == 8) ? PDMA_WIDTH_8 : (u32DataWidth == 16) ? PDMA_WIDTH_16 : PDMA_WIDTH_32,
                        i32Length);

    PDMA_SetTransferAddr(PDMA,
                         i32ChannID, // Channel ID
                         u32AddrSrc, // Source address
                         u32SrcCtl,  // Source address is incremental or fixed
                         u32AddrDst, // Destination address
                         u32DstCtl); // Destination address is incremental or fixed

    PDMA_SetBurstType(PDMA,
                      i32ChannID,
                      PDMA_REQ_SINGLE,    // Single mode
                      0); // Burst size

    PDMA_EnableInt(PDMA,   i32ChannID, PDMA_INT_TRANS_DONE);    // Interrupt type

    nu_pdma_timeout_set(i32ChannID, u32IdleTimeout_us);

    PDMA_SetTransferMode(PDMA,
                         i32ChannID,
                         psPeriphCtl->m_u32Peripheral,
                         0,
                         0);

    /* Memory to memory transfer */
    if (psPeriphCtl->m_u32Peripheral == PDMA_MEM)
    {
        PDMA_SetBurstType(PDMA,
                          i32ChannID,
                          PDMA_REQ_BURST, /* Burst mode */
                          PDMA_BURST_32); /* Burst size */

        PDMA_Trigger(PDMA, i32ChannID);
    }

    ret = RT_EOK;

exit_nu_pdma_transfer:

    return -(ret);
}


void PDMA_IRQHandler(void)
{
    int i;

    /* enter interrupt */
    rt_interrupt_enter();

    uint32_t intsts = PDMA_GET_INT_STATUS(PDMA);
    uint32_t abtsts = PDMA_GET_ABORT_STS(PDMA);
    uint32_t tdsts  = PDMA_GET_TD_STS(PDMA);
    uint32_t reqto  = intsts & (PDMA_INTSTS_REQTOF0_Msk | PDMA_INTSTS_REQTOF1_Msk);
    uint32_t reqto_ch = ((reqto & PDMA_INTSTS_REQTOF0_Msk) ? (1 << 0) : 0x0) | ((reqto & PDMA_INTSTS_REQTOF1_Msk) ? (1 << 1) : 0x0);

    int allch_sts = (reqto_ch | tdsts | abtsts);

    // Abort
    if (intsts & PDMA_INTSTS_ABTIF_Msk)
    {
        // Clear all Abort flags
        PDMA_CLR_ABORT_FLAG(PDMA, abtsts);
    }

    // Transfer done
    if (intsts & PDMA_INTSTS_TDIF_Msk)
    {
        // Clear all transfer done flags
        PDMA_CLR_TD_FLAG(PDMA, tdsts);
    }

    // Timeout
    if (reqto)
    {
        // Clear all Timeout flags
        PDMA->INTSTS = reqto;
    }

    // Find the position of first '1' in allch_sts.
    while ((i = nu_ctz(allch_sts)) != 32)
    {
        int ch_mask = (1 << i);

        if (nu_pdma_chn_mask & ch_mask)
        {
            int ch_event = 0;
            nu_pdma_chn_t *dma_chn = nu_pdma_chn_arr + i - NU_PDMA_CH_Pos;

            if (dma_chn->m_pfnCBHandler)
            {
                if (abtsts   & ch_mask)
                {
                    ch_event |= NU_PDMA_EVENT_ABORT;
                }

                if (tdsts    & ch_mask) ch_event |= NU_PDMA_EVENT_TRANSFER_DONE;

                if (reqto_ch & ch_mask)
                {
                    PDMA_DisableTimeout(PDMA,  ch_mask);
                    ch_event |= NU_PDMA_EVENT_TIMEOUT;
                }

                if (dma_chn->m_u32EventFilter & ch_event)
                    dma_chn->m_pfnCBHandler(dma_chn->m_pvUserData, ch_event);

                if (reqto_ch & ch_mask)
                    nu_pdma_timeout_set(i, nu_pdma_chn_arr[i - NU_PDMA_CH_Pos].m_u32IdleTimeout_us);

            }//if(dma_chn->handler)
        } //if (nu_pdma_chn_mask & ch_mask)

        // Clear the served bit.
        allch_sts &= ~ch_mask;

    } //while

    /* leave interrupt */
    rt_interrupt_leave();
}

static void nu_pdma_memfun_actor_init(void)
{
    int i = 0 ;
    nu_pdma_init();
    for (i = 0; i < NU_PDMA_MEMFUN_ACTOR_MAX; i++)
    {
        rt_memset(&nu_pdma_memfun_actor_arr[i], 0, sizeof(struct nu_pdma_memfun_actor));
        if (-(RT_ERROR) != (nu_pdma_memfun_actor_arr[i].m_i32ChannID = nu_pdma_channel_allocate(PDMA_MEM)))
        {
            nu_pdma_memfun_actor_arr[i].m_psSemMemFun = rt_sem_create("memactor_sem", 0, RT_IPC_FLAG_FIFO);
        }
        else
            break;
    }
    if (i)
    {
        nu_pdma_memfun_actor_maxnum = i;
        nu_pdma_memfun_actor_mask = ~(((1 << i) - 1));
        nu_pdma_memfun_actor_pool_sem = rt_sem_create("mempool_sem", nu_pdma_memfun_actor_maxnum, RT_IPC_FLAG_FIFO);
        nu_pdma_memfun_actor_pool_lock = rt_mutex_create("mempool_lock", RT_IPC_FLAG_FIFO);
    }
}

#if 0
static void nu_pdma_memfun_actor_fini(void)
{
    int i = 0 ;
    for (i = 0; i < nu_pdma_memfun_actor_maxnum; i++)
    {
        if (nu_pdma_memfun_actor_arr[i].m_i32ChannID != -(RT_ERROR))
            nu_pdma_channel_free(nu_pdma_memfun_actor_arr[i].m_i32ChannID);

        if (nu_pdma_memfun_actor_arr[i].m_psSemMemFun)
            rt_sem_delete(nu_pdma_memfun_actor_arr[i].m_psSemMemFun);
    }
    rt_mutex_delete(nu_pdma_memfun_actor_pool_lock);
    rt_sem_delete(nu_pdma_memfun_actor_pool_sem);
}
#endif

static void nu_pdma_memfun_cb(void *pvUserData, uint32_t u32Events)
{
    nu_pdma_memfun_actor_t psMemFunActor = (nu_pdma_memfun_actor_t)pvUserData;
    psMemFunActor->m_u32Result = u32Events;
    rt_sem_release(psMemFunActor->m_psSemMemFun);
}

static int nu_pdma_memfun_employ(void)
{
    int idx = -1 ;

    /* Headhunter */
    if (nu_pdma_memfun_actor_pool_sem && (rt_sem_take(nu_pdma_memfun_actor_pool_sem, RT_WAITING_FOREVER) == RT_EOK))
    {
        rt_mutex_take(nu_pdma_memfun_actor_pool_lock, RT_WAITING_FOREVER);
        /* Find the position of first '0' in nu_pdma_memfun_actor_mask. */
        idx = nu_cto(nu_pdma_memfun_actor_mask);
        if (idx != 32)
        {
            nu_pdma_memfun_actor_mask |= (1 << idx);
        }
        else
        {
            idx = -1;
        }
        rt_mutex_release(nu_pdma_memfun_actor_pool_lock);
    }

    return idx;
}

static rt_size_t nu_pdma_memfun(void *dest, void *src, uint32_t u32DataWidth, unsigned int count, nu_pdma_memctrl_t eMemCtl)
{
    nu_pdma_memfun_actor_t psMemFunActor = NULL;
    int idx;
    rt_size_t ret = 0;
    while (1)
    {
        /* Employ actor */
        if ((idx = nu_pdma_memfun_employ()) < 0)
            continue;

        psMemFunActor = &nu_pdma_memfun_actor_arr[idx];

        psMemFunActor->m_u32TrigTransferCnt = count;

        /* Set PDMA memory control to eMemCtl. */
        nu_pdma_channel_memctrl_set(psMemFunActor->m_i32ChannID, eMemCtl);

        /* Register ISR callback function */
        nu_pdma_callback_register(psMemFunActor->m_i32ChannID, nu_pdma_memfun_cb, (void *)psMemFunActor, NU_PDMA_EVENT_ABORT | NU_PDMA_EVENT_TRANSFER_DONE);

        psMemFunActor->m_u32Result = 0;

        /* Trigger it */
        nu_pdma_transfer(psMemFunActor->m_i32ChannID, u32DataWidth, (uint32_t)src, (uint32_t)dest, count, 0);

        /* Wait it done. */
        rt_sem_take(psMemFunActor->m_psSemMemFun, RT_WAITING_FOREVER);

        /* Give result if get NU_PDMA_EVENT_TRANSFER_DONE.*/
        if (psMemFunActor->m_u32Result & NU_PDMA_EVENT_TRANSFER_DONE)
        {
            ret = psMemFunActor->m_u32TrigTransferCnt;
        }
        else
        {
            ret = psMemFunActor->m_u32TrigTransferCnt - nu_pdma_non_transfer_count_get(psMemFunActor->m_i32ChannID);
        }

        /* Terminate it if get ABORT event */
        if (psMemFunActor->m_u32Result & NU_PDMA_EVENT_ABORT)
        {
            nu_pdma_channel_terminate(psMemFunActor->m_i32ChannID);
        }

        rt_mutex_take(nu_pdma_memfun_actor_pool_lock, RT_WAITING_FOREVER);
        nu_pdma_memfun_actor_mask &= ~(1 << idx);
        rt_mutex_release(nu_pdma_memfun_actor_pool_lock);

        /* Fire actor */
        rt_sem_release(nu_pdma_memfun_actor_pool_sem);

        break;
    }

    return ret;
}

rt_size_t nu_pdma_mempush(void *dest, void *src, uint32_t data_width, unsigned int transfer_count)
{
    if (data_width == 8 || data_width == 16 || data_width == 32)
        return nu_pdma_memfun(dest, src, data_width, transfer_count, eMemCtl_SrcInc_DstFix);
    return 0;
}

void *nu_pdma_memcpy(void *dest, void *src, unsigned int count)
{
    if (count == nu_pdma_memfun(dest, src, 8, count, eMemCtl_SrcInc_DstInc))
        return dest;
    else
        return NULL;
}

/**
 * PDMA memfun actor initialization
 */
int rt_hw_pdma_memfun_init(void)
{
    nu_pdma_memfun_actor_init();
    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_pdma_memfun_init);
#endif // #if defined(BSP_USING_PDMA)
