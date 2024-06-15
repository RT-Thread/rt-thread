/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-15     CDT          first version
 * 2023-09-30     CDT          Delete dma transmit interrupt
 * 2024-02-28     CDT          support HC32F448
 * 2024-02-29     CDT          Support multi line write/read
 * 2024-04-18     CDT          support HC32F472
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtthread.h>
#include <rtdevice.h>

#if defined(RT_USING_QSPI)

#if defined(BSP_USING_QSPI)

#include "drv_qspi.h"
#include "board_config.h"

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
// #define DRV_DEBUG
#define LOG_TAG                         "drv.qspi"
#include <drv_log.h>

/* QSPI read/write function */
#define QSPI_READ_FUNC                  (0U)
#define QSPI_WRITE_FUNC                 (1U)

/* QSPI direct communication line */
#define QSPI_DIRECT_COMM_LINE_ONE       (0U)
#define QSPI_DIRECT_COMM_LINE_MULTI     (1U)

#define QSPI_BASE_BLK_SIZE              (0x4000000UL)
#define QSPI_MAX_FLASH_ADDR             (0xFC000000UL)

/* QSPI max division */
#define QSPI_MAX_DIV_VAL                (0x3FU) /* Div64 */

/* QSPI read instruction */
#define QSPI_3LINE_STD_RD               (0x03U)
#define QSPI_3LINE_FAST_RD              (0x0BU)
#define QSPI_3LINE_DUAL_OUTPUT_FAST_RD  (0x3BU)
#define QSPI_3LINE_DUAL_IO_FAST_RD      (0xBBU)
#define QSPI_3LINE_QUAD_OUTPUT_FAST_RD  (0x6BU)
#define QSPI_3LINE_QUAD_IO_FAST_RD      (0xEBU)

#define QSPI_4LINE_STD_RD               (0x13U)
#define QSPI_4LINE_FAST_RD              (0x0CU)
#define QSPI_4LINE_DUAL_OUTPUT_FAST_RD  (0x3CU)
#define QSPI_4LINE_DUAL_IO_FAST_RD      (0xBCU)
#define QSPI_4LINE_QUAD_OUTPUT_FAST_RD  (0x6CU)
#define QSPI_4LINE_QUAD_IO_FAST_RD      (0xECU)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
extern rt_err_t rt_hw_qspi_board_init(void);

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void qspi_err_irq_handler(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
#ifndef BSP_QSPI_USING_SOFT_CS
static const uint8_t qspi_rom_cmd_list[] =
{
    QSPI_3LINE_STD_RD, QSPI_3LINE_FAST_RD, QSPI_3LINE_DUAL_OUTPUT_FAST_RD,
    QSPI_3LINE_DUAL_IO_FAST_RD, QSPI_3LINE_QUAD_OUTPUT_FAST_RD, QSPI_3LINE_QUAD_IO_FAST_RD,
    QSPI_4LINE_STD_RD, QSPI_4LINE_FAST_RD, QSPI_4LINE_DUAL_OUTPUT_FAST_RD,
    QSPI_4LINE_DUAL_IO_FAST_RD, QSPI_4LINE_QUAD_OUTPUT_FAST_RD, QSPI_4LINE_QUAD_IO_FAST_RD,
};
#endif

struct rt_spi_bus spi_bus_obj;
struct hc32_qspi_bus qspi_bus_obj;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
static int hc32_qspi_init(struct rt_qspi_device *device, struct rt_qspi_configuration *qspi_cfg)
{
    int result = RT_EOK;
    uint32_t u32Cnt = 1;
    uint32_t u32BusFreq;
    stc_qspi_init_t stcQspiInit = QSPI_INIT_PARAMS;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(qspi_cfg != RT_NULL);

    struct rt_spi_configuration *cfg = &qspi_cfg->parent;
    struct hc32_qspi_bus *qspi_bus = device->parent.bus->parent.user_data;
    /* Get BUS clock */
    u32BusFreq = CLK_GetBusClockFreq(CLK_BUS_HCLK);
    while (cfg->max_hz < u32BusFreq / (u32Cnt + 1U))
    {
        if (++u32Cnt == QSPI_MAX_DIV_VAL)   /* Div64 */
        {
            break;
        }
    }
    stcQspiInit.u32ClockDiv = (u32Cnt << QSPI_CR_DIV_POS);
    if (!(cfg->mode & RT_SPI_CPOL))
    {
        stcQspiInit.u32SpiMode = QSPI_SPI_MD0;  /* QSPI MODE0 */
    }
    else
    {
        stcQspiInit.u32SpiMode = QSPI_SPI_MD3;  /* QSPI MODE3 */
    }
    /* Enable qspi clock */
    FCG_Fcg1PeriphClockCmd(qspi_bus->config->clock, ENABLE);
    /* qspi port init */
    rt_hw_qspi_board_init();
    /* Init QSPI */
    stcQspiInit.u32ReadMode       = QSPI_RD_MD_STD_RD;
    stcQspiInit.u32DummyCycle     = QSPI_DUMMY_CYCLE4;
    stcQspiInit.u32AddrWidth      = QSPI_ADDR_WIDTH_24BIT;
    (void)QSPI_Init(&stcQspiInit);
    QSPI_SetWpPinLevel(QSPI_WP_PIN_LEVEL);
    /* Enable error interrupt */
    NVIC_EnableIRQ(qspi_bus->config->err_irq.irq_config.irq_num);
    LOG_D("qspi init success!");

#ifdef BSP_QSPI_USING_DMA
    struct dma_config *qspi_dma;
    stc_dma_init_t stcDmaInit;

    /* Get qspi dma */
    qspi_dma = qspi_bus->config->dma_qspi;
    /* Enable Dma clock */
    FCG_Fcg0PeriphClockCmd(qspi_dma->clock, ENABLE);
    /* Config Dma */
    DMA_StructInit(&stcDmaInit);
    stcDmaInit.u32DataWidth     = DMA_DATAWIDTH_8BIT;
    /* Init Dma */
    if (LL_OK != DMA_Init(qspi_dma->Instance, qspi_dma->channel, &stcDmaInit))
    {
        return -RT_ERROR;
    }
    DMA_Cmd(qspi_dma->Instance, ENABLE);
#endif /* BSP_QSPI_USING_DMA */

    return result;
}

#ifndef BSP_QSPI_USING_SOFT_CS
static int32_t hc32_qspi_search_rom_cmd(uint8_t u8Cmd)
{
    uint32_t u32Cnt, u32ListLen;

    u32ListLen = sizeof(qspi_rom_cmd_list);
    for (u32Cnt = 0; u32Cnt < u32ListLen; u32Cnt++)
    {
        if (u8Cmd == qspi_rom_cmd_list[u32Cnt])
        {
            return LL_OK;
        }
    }

    return LL_ERR;
}
#endif


static int32_t hc32_qspi_check_direct_comm_param(struct rt_qspi_message *message, uint8_t line)
{
    if (QSPI_DIRECT_COMM_LINE_ONE == line)
    {
        if (message->instruction.qspi_lines > 1)
        {
            return LL_ERR_INVD_PARAM;
        }
        if (message->address.size != 0)
        {
            if ((message->address.qspi_lines > 1) || ((message->address.size % 8) != 0))
            {
                return LL_ERR_INVD_PARAM;
            }
        }
        if (message->qspi_data_lines > 1)
        {
            return LL_ERR_INVD_PARAM;
        }
        if (0U != message->dummy_cycles)
        {
            if ((message->dummy_cycles < 3) || (message->dummy_cycles > 18) || (message->dummy_cycles % 8) != 0)
            {
                return LL_ERR_INVD_PARAM;
            }
        }
    }
    else
    {
        if ((message->instruction.qspi_lines > 2) && (message->instruction.qspi_lines != 4))
        {
            return LL_ERR_INVD_PARAM;
        }
        if (message->address.size != 0)
        {
            if (((message->address.qspi_lines > 2) && (message->address.qspi_lines != 4)) ||
                    ((message->address.size % 8) != 0))
            {
                return LL_ERR_INVD_PARAM;
            }
        }
        if ((message->qspi_data_lines > 2) && (message->qspi_data_lines != 4))
        {
            return LL_ERR_INVD_PARAM;
        }
        if ((0U != message->dummy_cycles) && ((message->dummy_cycles < 3) || (message->dummy_cycles > 18)))
        {
            return LL_ERR_INVD_PARAM;
        }
        if (0U != message->dummy_cycles)
        {
            if ((message->dummy_cycles < 3) || (message->dummy_cycles > 18))
            {
                return LL_ERR_INVD_PARAM;
            }
        }
    }

    return LL_OK;
}

static int32_t hc32_qspi_send_cmd(struct hc32_qspi_bus *qspi_bus, struct rt_qspi_message *message, uint8_t u8Func)
{
#ifndef BSP_QSPI_USING_SOFT_CS
    uint32_t u32ReadMode = QSPI_RD_MD_STD_RD;
    uint32_t u32DummyCycle = 0U;
    uint32_t u32AddrWidth;
    uint8_t u8Instr, u8CalcDummy = 0U;
#endif

    RT_ASSERT(qspi_bus != RT_NULL);
    RT_ASSERT(message != RT_NULL);

#ifndef BSP_QSPI_USING_SOFT_CS
    CM_QSPI_TypeDef *qspi_instance = qspi_bus->config->Instance;
    u8Instr = message->instruction.content;
    if ((QSPI_READ_FUNC == u8Func) && (LL_OK == hc32_qspi_search_rom_cmd(u8Instr)))
    {
        if ((message->instruction.qspi_lines != 1) ||
                ((message->address.qspi_lines != 1) && (message->address.qspi_lines != 2) && (message->address.qspi_lines != 4)) ||
                ((message->qspi_data_lines != 1) && (message->qspi_data_lines != 2) && (message->qspi_data_lines != 4)))
        {
            return LL_ERR_INVD_PARAM;
        }
        if (((message->address.qspi_lines == 2) && ((message->qspi_data_lines == 1) || (message->qspi_data_lines == 4))) ||
                ((message->address.qspi_lines == 4) && ((message->qspi_data_lines == 1) || (message->qspi_data_lines == 2))))
        {
            return LL_ERR_INVD_PARAM;
        }

        if ((message->instruction.qspi_lines == 1) && (message->address.qspi_lines == 1) && (message->qspi_data_lines == 1))
        {
            if (message->dummy_cycles != 0)
            {
                u32ReadMode += 1U;
                u8CalcDummy = 1U;
            }
        }
        else
        {
            u8CalcDummy = 1U;
            u32ReadMode = message->qspi_data_lines;
            if (message->address.qspi_lines == message->qspi_data_lines)
            {
                u32ReadMode += 1U;
            }
        }
        if (0U != u8CalcDummy)
        {
            if ((message->dummy_cycles < 3) || (message->dummy_cycles > 18))
            {
                return LL_ERR_INVD_PARAM;
            }
            u32DummyCycle = (message->dummy_cycles - 3) << QSPI_FCR_DMCYCN_POS;
        }

        if (message->address.size == 24)
        {
            u32AddrWidth = QSPI_ADDR_WIDTH_24BIT;
        }
        else
        {
            u32AddrWidth = QSPI_ADDR_WIDTH_32BIT_INSTR_32BIT;
        }
        /* configure register */
        MODIFY_REG32(qspi_instance->FCR, (QSPI_FCR_DMCYCN | QSPI_FCR_FOUR_BIC | QSPI_FCR_AWSL),
                     (u32DummyCycle | u32AddrWidth));
        QSPI_SetReadMode(u32ReadMode);
    }
    else
#endif
    {
#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
#ifndef BSP_QSPI_USING_SOFT_CS
        if (LL_OK != hc32_qspi_check_direct_comm_param(message, QSPI_DIRECT_COMM_LINE_ONE))
        {
            return LL_ERR_INVD_PARAM;
        }
        /* Set standard read mode */
        QSPI_SetReadMode(QSPI_RD_MD_STD_RD);
#else
        if (LL_OK != hc32_qspi_check_direct_comm_param(message, QSPI_DIRECT_COMM_LINE_MULTI))
        {
            return LL_ERR_INVD_PARAM;
        }
        /* Set custom read mode */
        QSPI_SetReadMode(QSPI_RD_MD_CUSTOM_FAST_RD);
#endif
#elif defined (HC32F448)
        if (LL_OK != hc32_qspi_check_direct_comm_param(message, QSPI_DIRECT_COMM_LINE_MULTI))
        {
            return LL_ERR_INVD_PARAM;
        }
#endif
    }

    return LL_OK;
}

static void hc32_qspi_word_to_byte(uint32_t u32Word, uint8_t *pu8Byte, uint8_t u8Len)
{
    uint8_t u8Count = 0U;
    uint32_t u32ByteNum = u8Len - 1U;

    do
    {
        pu8Byte[u8Count++] = (uint8_t)(u32Word >> (u32ByteNum * 8U)) & 0xFFU;
    }
    while ((u32ByteNum--) != 0UL);
}

#if defined (HC32F448)
static rt_uint32_t hc32_qspi_get_dcom_protocol_line(rt_uint8_t protocol_line)
{
    rt_uint32_t dcom_protocol_line;

    switch (protocol_line)
    {
    case 2:
        dcom_protocol_line = QSPI_DIRECT_COMM_PROTOCOL_2LINE;
        break;
    case 4:
        dcom_protocol_line = QSPI_DIRECT_COMM_PROTOCOL_4LINE;
        break;
    case 1:
    default:
        dcom_protocol_line = QSPI_DIRECT_COMM_PROTOCOL_1LINE;
        break;
    }

    return dcom_protocol_line;
}
#endif

static void hc32_qspi_write_direct_comm_value(rt_uint8_t protocol_line, rt_uint8_t value)
{
#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
    (void)protocol_line;
    QSPI_WriteDirectCommValue(value);
#elif defined (HC32F448)
    QSPI_WriteDirectCommValue(hc32_qspi_get_dcom_protocol_line(protocol_line), value);
#endif
}

#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
#ifdef BSP_QSPI_USING_SOFT_CS
static void hc32_qspi_set_trans_protocol(uint32_t u32Line)
{
    stc_qspi_custom_mode_t stcCustomMode;

    stcCustomMode.u8InstrCode        = 0U;
    switch (u32Line)
    {
    case 2:
        stcCustomMode.u32InstrProtocol   = QSPI_INSTR_PROTOCOL_2LINE;
        stcCustomMode.u32AddrProtocol    = QSPI_ADDR_PROTOCOL_2LINE;
        stcCustomMode.u32DataProtocol    = QSPI_DATA_PROTOCOL_2LINE;
        break;
    case 4:
        stcCustomMode.u32InstrProtocol   = QSPI_INSTR_PROTOCOL_4LINE;
        stcCustomMode.u32AddrProtocol    = QSPI_ADDR_PROTOCOL_4LINE;
        stcCustomMode.u32DataProtocol    = QSPI_DATA_PROTOCOL_4LINE;
        break;
    case 1:
    default:
        stcCustomMode.u32InstrProtocol   = QSPI_INSTR_PROTOCOL_1LINE;
        stcCustomMode.u32AddrProtocol    = QSPI_ADDR_PROTOCOL_1LINE;
        stcCustomMode.u32DataProtocol    = QSPI_DATA_PROTOCOL_1LINE;
        break;
    }
    QSPI_CustomReadConfig(&stcCustomMode);
}
#endif
#endif

static int32_t hc32_qspi_write_instr(struct hc32_qspi_bus *qspi_bus, struct rt_qspi_message *message,
                                     uint8_t u8Instr, uint32_t u32InstrLen, uint8_t *pu8Addr, uint32_t u32AddrLen,
                                     const uint8_t *pu8WriteBuf, uint32_t u32BufLen)
{
    uint32_t u32Count;
    int32_t i32Ret = LL_OK;
#ifdef BSP_QSPI_USING_DMA
    struct dma_config *qspi_dma;
    stc_dma_init_t stcDmaInit;
    uint32_t u32DmaTransSize;
    uint32_t u32TxIndex = 0U;
    rt_uint32_t u32TimeoutCnt;
    rt_uint32_t src_addr;
#endif

#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
#ifndef BSP_QSPI_USING_SOFT_CS
    /* Enter direct communication mode */
    SET_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif
#elif defined (HC32F448)
    /* Enter direct communication mode */
    SET_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif
    if (0UL != u32InstrLen)
    {
#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
#ifdef BSP_QSPI_USING_SOFT_CS
        hc32_qspi_set_trans_protocol(message->instruction.qspi_lines);
        SET_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif
#endif
        hc32_qspi_write_direct_comm_value(message->instruction.qspi_lines, u8Instr);
#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
#ifdef BSP_QSPI_USING_SOFT_CS
        CLR_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif
#endif
    }
    if ((NULL != pu8Addr) && (0UL != u32AddrLen))
    {
#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
#ifdef BSP_QSPI_USING_SOFT_CS
        hc32_qspi_set_trans_protocol(message->address.qspi_lines);
        SET_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif
#endif
        for (u32Count = 0UL; u32Count < u32AddrLen; u32Count++)
        {
            hc32_qspi_write_direct_comm_value(message->address.qspi_lines, pu8Addr[u32Count]);
        }
#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
#ifdef BSP_QSPI_USING_SOFT_CS
        CLR_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif
#endif
    }
    if ((NULL != pu8WriteBuf) && (0UL != u32BufLen))
    {
#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
#ifdef BSP_QSPI_USING_SOFT_CS
        hc32_qspi_set_trans_protocol(message->qspi_data_lines);
        SET_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif
#endif

#ifdef BSP_QSPI_USING_DMA
        qspi_dma = qspi_bus->config->dma_qspi;
        AOS_SetTriggerEventSrc(qspi_dma->trigger_select, qspi_dma->trigger_event);
        /* Config Dma */
        DMA_StructInit(&stcDmaInit);
#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
        stcDmaInit.u32DataWidth     = DMA_DATAWIDTH_8BIT;
#elif defined (HC32F448)
        rt_uint16_t dcom_line = (rt_uint16_t)hc32_qspi_get_dcom_protocol_line(message->qspi_data_lines);
        stcDmaInit.u32DataWidth     = DMA_DATAWIDTH_16BIT;
#endif
        stcDmaInit.u32SrcAddrInc    = DMA_SRC_ADDR_INC;
        stcDmaInit.u32DestAddrInc   = DMA_DEST_ADDR_FIX;
        DMA_Init(qspi_dma->Instance, qspi_dma->channel, &stcDmaInit);
        while (u32BufLen != 0U)
        {
            if (u32BufLen > DMA_DTCTL_BLKSIZE)
            {
                u32DmaTransSize = DMA_DTCTL_BLKSIZE;
                u32BufLen -= DMA_DTCTL_BLKSIZE;
            }
            else
            {
                u32DmaTransSize = u32BufLen;
                u32BufLen = 0U;
            }

#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
            src_addr = (rt_uint32_t)&pu8WriteBuf[u32TxIndex];
#elif defined (HC32F448)
            if (u32DmaTransSize > qspi_bus->config->dma_tx_buf_size)
            {
                LOG_E("qspi dma transmit size over buffer size!");
                i32Ret = LL_ERR;
                break;
            }
            for (rt_uint32_t i = 0; i < u32DmaTransSize; i++)
            {
                qspi_bus->config->dma_tx_buf[i] = (rt_uint16_t)pu8WriteBuf[u32TxIndex + i] | dcom_line;
            }
            src_addr = (rt_uint32_t)qspi_bus->config->dma_tx_buf;
#endif
            DMA_ClearTransCompleteStatus(qspi_dma->Instance, qspi_dma->flag);
            DMA_SetSrcAddr(qspi_dma->Instance, qspi_dma->channel, src_addr);
            DMA_SetDestAddr(qspi_dma->Instance, qspi_dma->channel, (uint32_t)&qspi_bus->config->Instance->DCOM);
            DMA_SetTransCount(qspi_dma->Instance, qspi_dma->channel, 1UL);
            DMA_SetBlockSize(qspi_dma->Instance, qspi_dma->channel, (uint16_t)u32DmaTransSize);
            (void)DMA_ChCmd(qspi_dma->Instance, qspi_dma->channel, ENABLE);
            AOS_SW_Trigger();   /* 1st trigger for DMA */
            u32TimeoutCnt = 0U;
            /* Wait DMA transfer completed */
            while ((RESET == DMA_GetTransCompleteStatus(qspi_dma->Instance, qspi_dma->flag)) &&
                    (u32TimeoutCnt < qspi_bus->config->timeout))
            {
                rt_thread_mdelay(1);
                u32TimeoutCnt++;
            }
            if (u32TimeoutCnt >= qspi_bus->config->timeout)
            {
                i32Ret = LL_ERR_TIMEOUT;
                break;
            }
            u32TxIndex += u32DmaTransSize;
        }
#else
        for (u32Count = 0UL; u32Count < u32BufLen; u32Count++)
        {
            hc32_qspi_write_direct_comm_value(message->qspi_data_lines, pu8WriteBuf[u32Count]);
        }
#endif

#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
#ifdef BSP_QSPI_USING_SOFT_CS
        /* Exit direct communication mode */
        CLR_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif
#endif
    }
#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
#ifndef BSP_QSPI_USING_SOFT_CS
    /* Exit direct communication mode */
    CLR_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif
#elif defined (HC32F448)
    /* Exit direct communication mode */
    CLR_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif

    return i32Ret;
}

static int32_t hc32_qspi_read_instr(struct hc32_qspi_bus *qspi_bus, struct rt_qspi_message *message,
                                    uint8_t u8Instr, uint32_t u32InstrLen, uint8_t *pu8Addr, uint32_t u32AddrLen,
                                    uint8_t *pu8ReadBuf, uint32_t u32BufLen)
{
    uint32_t u32Count;
    int32_t i32Ret = LL_OK;
#ifdef BSP_QSPI_USING_DMA
    struct dma_config *qspi_dma;
    stc_dma_init_t stcDmaInit;
    uint32_t u32DmaTransSize;
    uint32_t u32RxIndex = 0U;
    rt_uint32_t u32TimeoutCnt;
#endif

#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
#ifndef BSP_QSPI_USING_SOFT_CS
    /* Enter direct communication mode */
    SET_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif
#elif defined (HC32F448)
    /* Enter direct communication mode */
    SET_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif
    if (0UL != u32InstrLen)
    {
#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
#ifdef BSP_QSPI_USING_SOFT_CS
        hc32_qspi_set_trans_protocol(message->instruction.qspi_lines);
        SET_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif
#endif
        hc32_qspi_write_direct_comm_value(message->instruction.qspi_lines, u8Instr);
#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
#ifdef BSP_QSPI_USING_SOFT_CS
        CLR_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif
#endif
    }
    if ((NULL != pu8Addr) && (0UL != u32AddrLen))
    {
#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
#ifdef BSP_QSPI_USING_SOFT_CS
        hc32_qspi_set_trans_protocol(message->address.qspi_lines);
        SET_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif
#endif
        for (u32Count = 0UL; u32Count < u32AddrLen; u32Count++)
        {
            hc32_qspi_write_direct_comm_value(message->address.qspi_lines, pu8Addr[u32Count]);
        }
#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
#ifdef BSP_QSPI_USING_SOFT_CS
        CLR_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif
#endif
    }
    if ((NULL != pu8ReadBuf) && (0UL != u32BufLen))
    {
#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
#ifdef BSP_QSPI_USING_SOFT_CS
        hc32_qspi_set_trans_protocol(message->qspi_data_lines);
        SET_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif
#endif

#ifdef BSP_QSPI_USING_DMA
        qspi_dma = qspi_bus->config->dma_qspi;
        AOS_SetTriggerEventSrc(qspi_dma->trigger_select, qspi_dma->trigger_event);
        /* Config Dma */
        DMA_StructInit(&stcDmaInit);
        stcDmaInit.u32DataWidth     = DMA_DATAWIDTH_8BIT;
        stcDmaInit.u32SrcAddrInc    = DMA_SRC_ADDR_FIX;
        stcDmaInit.u32DestAddrInc   = DMA_DEST_ADDR_INC;
        DMA_Init(qspi_dma->Instance, qspi_dma->channel, &stcDmaInit);
        while (u32BufLen != 0U)
        {
            if (u32BufLen > DMA_DTCTL_BLKSIZE)
            {
                u32DmaTransSize = DMA_DTCTL_BLKSIZE;
                u32BufLen -= DMA_DTCTL_BLKSIZE;
            }
            else
            {
                u32DmaTransSize = u32BufLen;
                u32BufLen = 0U;
            }
            DMA_ClearTransCompleteStatus(qspi_dma->Instance, qspi_dma->flag);
            DMA_SetSrcAddr(qspi_dma->Instance, qspi_dma->channel, (uint32_t)&qspi_bus->config->Instance->DCOM);
            DMA_SetDestAddr(qspi_dma->Instance, qspi_dma->channel, (uint32_t)&pu8ReadBuf[u32RxIndex]);
            DMA_SetTransCount(qspi_dma->Instance, qspi_dma->channel, 1UL);
            DMA_SetBlockSize(qspi_dma->Instance, qspi_dma->channel, (uint16_t)u32DmaTransSize);
            (void)DMA_ChCmd(qspi_dma->Instance, qspi_dma->channel, ENABLE);
            AOS_SW_Trigger();   /* 1st trigger for DMA */
            u32TimeoutCnt = 0U;
            /* Wait DMA transfer completed */
            while ((RESET == DMA_GetTransCompleteStatus(qspi_dma->Instance, qspi_dma->flag)) &&
                    (u32TimeoutCnt < qspi_bus->config->timeout))
            {
                rt_thread_mdelay(1);
                u32TimeoutCnt++;
            }
            if (u32TimeoutCnt >= qspi_bus->config->timeout)
            {
                i32Ret = LL_ERR_TIMEOUT;
                break;
            }
            u32RxIndex += u32DmaTransSize;
        }
#else
        for (u32Count = 0UL; u32Count < u32BufLen; u32Count++)
        {
            pu8ReadBuf[u32Count] = QSPI_ReadDirectCommValue();
        }
#endif

#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
#ifdef BSP_QSPI_USING_SOFT_CS
        /* Exit direct communication mode */
        CLR_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif
#endif
    }
#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
#ifndef BSP_QSPI_USING_SOFT_CS
    /* Exit direct communication mode */
    CLR_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif
#elif defined (HC32F448)
    /* Exit direct communication mode */
    CLR_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
#endif

    return i32Ret;
}

static int32_t hc32_qspi_write(struct hc32_qspi_bus *qspi_bus, struct rt_qspi_message *message)
{
    uint32_t u32Count = 0U;
    const rt_uint8_t *tx_buf = message->parent.send_buf;
    rt_int32_t length = message->parent.length;
    uint32_t u32Addr = message->address.content;
    uint8_t u8Instr = message->instruction.content;
    uint8_t u8AddrBuf[32];
    uint32_t u32AddrLen = 0U, u32DummyLen = 0U;
    uint32_t u32InstrLen = 0U;
    int32_t i32Ret;

    RT_ASSERT(qspi_bus != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    if (message->instruction.qspi_lines != 0)
    {
        u32InstrLen = 1U;
    }
    if (message->address.size != 0)
    {
        u32AddrLen = message->address.size / 8;
        hc32_qspi_word_to_byte(u32Addr, u8AddrBuf, u32AddrLen);
    }
    if (message->dummy_cycles != 0)
    {
        u32DummyLen = message->dummy_cycles * message->address.qspi_lines / 8;
        for (u32Count = 0; u32Count < u32DummyLen; u32Count++)
        {
            u8AddrBuf[u32AddrLen] = 0xFF;
            u32AddrLen += 1;
        }
    }
    i32Ret = hc32_qspi_write_instr(qspi_bus, message, u8Instr, u32InstrLen, u8AddrBuf, u32AddrLen, tx_buf, length);

    return i32Ret;
}

static int32_t hc32_qspi_read(struct hc32_qspi_bus *qspi_bus, struct rt_qspi_message *message)
{
    uint32_t u32Count = 0U;

    rt_uint8_t *rx_buf = message->parent.recv_buf;
    rt_int32_t length = message->parent.length;
    uint32_t u32Addr = message->address.content;
    uint8_t u8Instr = message->instruction.content;
    uint8_t u8AddrBuf[32];
    uint32_t u32AddrLen = 0U, u32DummyLen = 0U;
    uint32_t u32InstrLen = 0U;
    int32_t i32Ret = LL_OK;

#ifndef BSP_QSPI_USING_SOFT_CS
    uint32_t u32ExtBlkStartNum = 0U;
    uint32_t u32GetSize, u32RxIndex = 0U;
#ifdef BSP_QSPI_USING_DMA
    struct dma_config *qspi_dma;
    stc_dma_init_t stcDmaInit;
    uint32_t u32DmaTransSize;
    rt_uint32_t u32TimeoutCnt;
#else
    __IO uint8_t *pu8Read;
#endif
#endif

    RT_ASSERT(qspi_bus != RT_NULL);
    RT_ASSERT(message != RT_NULL);

#ifndef BSP_QSPI_USING_SOFT_CS
    if (LL_OK == hc32_qspi_search_rom_cmd(u8Instr))
    {
        u32ExtBlkStartNum = u32Addr / QSPI_BASE_BLK_SIZE;
        if ((u32Addr + length) > QSPI_MAX_FLASH_ADDR)
        {
            return LL_ERR_INVD_PARAM;
        }
        u32Addr = (u32Addr % QSPI_BASE_BLK_SIZE) + QSPI_ROM_BASE;
#ifdef BSP_QSPI_USING_DMA
        qspi_dma = qspi_bus->config->dma_qspi;
        AOS_SetTriggerEventSrc(qspi_dma->trigger_select, qspi_dma->trigger_event);
        /* Config Dma */
        DMA_StructInit(&stcDmaInit);
        stcDmaInit.u32DataWidth     = DMA_DATAWIDTH_8BIT;
        stcDmaInit.u32SrcAddrInc    = DMA_SRC_ADDR_INC;
        stcDmaInit.u32DestAddrInc   = DMA_DEST_ADDR_INC;
        DMA_Init(qspi_dma->Instance, qspi_dma->channel, &stcDmaInit);
        while (length != 0)
        {
            QSPI_SelectMemoryBlock((uint8_t)u32ExtBlkStartNum);
            if ((u32Addr + length) > (QSPI_ROM_END + 1U))
            {
                u32GetSize = (QSPI_ROM_END + 1U) - u32Addr;
                length -= u32GetSize;
            }
            else
            {
                u32GetSize = length;
                length = 0U;
            }
            while (u32GetSize != 0U)
            {
                if (u32GetSize > DMA_DTCTL_BLKSIZE)
                {
                    u32DmaTransSize = DMA_DTCTL_BLKSIZE;
                    u32GetSize -= DMA_DTCTL_BLKSIZE;
                }
                else
                {
                    u32DmaTransSize = u32GetSize;
                    u32GetSize = 0U;
                }
                DMA_ClearTransCompleteStatus(qspi_dma->Instance, qspi_dma->flag);
                DMA_SetSrcAddr(qspi_dma->Instance, qspi_dma->channel, u32Addr);
                DMA_SetDestAddr(qspi_dma->Instance, qspi_dma->channel, (uint32_t)&rx_buf[u32RxIndex]);
                DMA_SetTransCount(qspi_dma->Instance, qspi_dma->channel, 1UL);
                DMA_SetBlockSize(qspi_dma->Instance, qspi_dma->channel, (uint16_t)u32DmaTransSize);
                (void)DMA_ChCmd(qspi_dma->Instance, qspi_dma->channel, ENABLE);
                AOS_SW_Trigger();   /* 1st trigger for DMA */
                u32TimeoutCnt = 0U;
                /* Wait DMA transfer completed */
                while ((RESET == DMA_GetTransCompleteStatus(qspi_dma->Instance, qspi_dma->flag)) &&
                        (u32TimeoutCnt < qspi_bus->config->timeout))
                {
                    rt_thread_mdelay(1);
                    u32TimeoutCnt++;
                }
                if (u32TimeoutCnt >= qspi_bus->config->timeout)
                {
                    return LL_ERR_TIMEOUT;
                }
                u32Addr += u32DmaTransSize;
                u32RxIndex += u32DmaTransSize;
            }
            if (length != 0U)
            {
                u32ExtBlkStartNum += 1U;
                u32Addr = QSPI_ROM_BASE;
            }
        }
#else
        while (length != 0)
        {
            QSPI_SelectMemoryBlock((uint8_t)u32ExtBlkStartNum);
            pu8Read = (__IO uint8_t *)u32Addr;
            if ((u32Addr + length) > (QSPI_ROM_END + 1U))
            {
                u32GetSize = (QSPI_ROM_END + 1U) - u32Addr;
                length -= u32GetSize;
            }
            else
            {
                u32GetSize = length;
                length = 0U;
            }
            u32Count = 0U;
            while (u32Count < u32GetSize)
            {
                rx_buf[u32RxIndex++] = *pu8Read++;
                u32Count++;
            }
            if (length != 0U)
            {
                u32ExtBlkStartNum += 1U;
                u32Addr = QSPI_ROM_BASE;
            }
        }
#endif
    }
    else
#endif
    {
        if (message->instruction.qspi_lines != 0)
        {
            u32InstrLen = 1U;
        }
        if (message->address.size != 0)
        {
            u32AddrLen = message->address.size / 8;
            hc32_qspi_word_to_byte(u32Addr, u8AddrBuf, u32AddrLen);
        }
        if (message->dummy_cycles != 0)
        {
            u32DummyLen = message->dummy_cycles * message->address.qspi_lines / 8;
            for (u32Count = 0; u32Count < u32DummyLen; u32Count++)
            {
                u8AddrBuf[u32AddrLen] = 0xFF;
                u32AddrLen += 1;
            }
        }
        i32Ret = hc32_qspi_read_instr(qspi_bus, message, u8Instr, u32InstrLen, u8AddrBuf, u32AddrLen, rx_buf, length);
    }

    return i32Ret;
}

static rt_ssize_t qspixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);

    rt_size_t len = 0;
    struct rt_qspi_message *qspi_message = (struct rt_qspi_message *)message;
    struct hc32_qspi_bus *qspi_bus = device->bus->parent.user_data;
#ifdef BSP_QSPI_USING_SOFT_CS
    struct hc32_hw_qspi_cs *cs = device->parent.user_data;
#endif
    rt_int32_t length = message->length;

#ifdef BSP_QSPI_USING_SOFT_CS
    if (message->cs_take)
    {
        rt_pin_write(cs->pin, 0);
    }
#endif
    if (message->send_buf != NULL)     /* send data */
    {
        if (LL_OK != hc32_qspi_send_cmd(qspi_bus, qspi_message, QSPI_WRITE_FUNC))
        {
            LOG_E("QSPI rt_qspi_message format error!");
            goto __exit;
        }
        if (LL_OK == hc32_qspi_write(qspi_bus, qspi_message))
        {
            if (qspi_message->parent.length != 0)
            {
                len = length;
            }
            else
            {
                len = 1;
            }
        }
        else
        {
            LOG_E("QSPI send data failed!");
            goto __exit;
        }
    }
    else if (message->recv_buf != NULL)     /* recv data */
    {
        if (LL_OK != hc32_qspi_send_cmd(qspi_bus, qspi_message, QSPI_READ_FUNC))
        {
            LOG_E("QSPI rt_qspi_message format error!");
            goto __exit;
        }
        if (LL_OK == hc32_qspi_read(qspi_bus, qspi_message))
        {
            len = length;
        }
        else
        {
            LOG_E("QSPI recv data failed!");
            goto __exit;
        }
    }
__exit:
#ifdef BSP_QSPI_USING_SOFT_CS
    if (message->cs_release)
    {
        rt_pin_write(cs->pin, 1);
    }
#endif

    return len;
}

static rt_err_t qspi_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    struct rt_qspi_device *qspi_device = (struct rt_qspi_device *)device;
    return hc32_qspi_init(qspi_device, &qspi_device->config);
}

static const struct rt_spi_ops hc32_qspi_ops =
{
    .configure = qspi_configure,
    .xfer = qspixfer,
};

static int hc32_qspi_register_bus(struct hc32_qspi_bus *qspi_bus, const char *name)
{
    RT_ASSERT(qspi_bus != RT_NULL);
    RT_ASSERT(name != RT_NULL);

    spi_bus_obj.parent.user_data = qspi_bus;
    return rt_qspi_bus_register(&spi_bus_obj, name, &hc32_qspi_ops);
}

static void qspi_err_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    QSPI_ClearStatus(QSPI_FLAG_ROM_ACCESS_ERR);
    /* leave interrupt */
    rt_interrupt_leave();
}

#if defined (HC32F448) || defined (HC32F472)
void QSPI_Handler(void)
{
    qspi_err_irq_handler();
}
#endif

/**
  * @brief  This function attach device to QSPI bus.
  * @param  bus_name                    QSPI bus name
  * @param  device_name                 QSPI device name
  * @param  pin                         QSPI cs pin number
  * @param  data_line_width             QSPI data lines width, such as 1, 2, 4
  * @param  enter_qspi_mode             Callback function that lets FLASH enter QSPI mode
  * @param  exit_qspi_mode              Callback function that lets FLASH exit QSPI mode
  * @retval 0 : success
  *        -1 : failed
  */
rt_err_t rt_hw_qspi_bus_attach_device(const char *bus_name, const char *device_name, rt_uint32_t pin, rt_uint8_t data_line_width, void (*enter_qspi_mode)(), void (*exit_qspi_mode)())
{
    struct rt_qspi_device *qspi_device = RT_NULL;
    struct hc32_hw_qspi_cs *cs_pin = RT_NULL;
    rt_err_t result = RT_EOK;

    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);
    RT_ASSERT(data_line_width == 1 || data_line_width == 2 || data_line_width == 4);

    qspi_device = (struct rt_qspi_device *)rt_malloc(sizeof(struct rt_qspi_device));
    if (qspi_device == RT_NULL)
    {
        LOG_E("no memory, qspi bus attach device failed!");
        result = RT_ENOMEM;
        goto __exit;
    }
    cs_pin = (struct hc32_hw_qspi_cs *)rt_malloc(sizeof(struct hc32_hw_qspi_cs));
    if (qspi_device == RT_NULL)
    {
        LOG_E("no memory, qspi bus attach device failed!");
        result = RT_ENOMEM;
        goto __exit;
    }
    qspi_device->enter_qspi_mode        = enter_qspi_mode;
    qspi_device->exit_qspi_mode         = exit_qspi_mode;
    qspi_device->config.qspi_dl_width   = data_line_width;

    cs_pin->pin = pin;
#ifdef BSP_QSPI_USING_SOFT_CS
    rt_pin_mode(pin, PIN_MODE_OUTPUT);
    rt_pin_write(pin, 1);
#endif

    result = rt_spi_bus_attach_device(&qspi_device->parent, device_name, bus_name, (void *)cs_pin);
__exit:
    if (result != RT_EOK)
    {
        if (qspi_device)
        {
            rt_free(qspi_device);
        }
        if (cs_pin)
        {
            rt_free(cs_pin);
        }
    }

    return  result;
}

static void hc32_get_qspi_info(void)
{
    static struct hc32_qspi_config qspi_config = QSPI_BUS_CONFIG;
    qspi_config.err_irq.irq_callback = qspi_err_irq_handler;
#ifdef BSP_QSPI_USING_DMA
    static struct dma_config qspi_dma = QSPI_DMA_CONFIG;
    qspi_config.dma_qspi    = &qspi_dma;
#if defined (HC32F448)
    qspi_config.dma_tx_buf_size = QSPI_DMA_TX_BUFSIZE;
    qspi_config.dma_tx_buf = rt_malloc(qspi_config.dma_tx_buf_size << 1);
#endif
#endif
    qspi_bus_obj.config = &qspi_config;
}

static int rt_hw_qspi_bus_init(void)
{
    hc32_get_qspi_info();
    /* register the handle */
#if defined (HC32F460) || defined (HC32F4A0)
    hc32_install_irq_handler(&qspi_bus_obj.config->err_irq.irq_config, qspi_bus_obj.config->err_irq.irq_callback, RT_FALSE);
#elif defined (HC32F448) || defined (HC32F472)
    hc32_install_independ_irq_handler(&qspi_bus_obj.config->err_irq.irq_config, RT_FALSE);
#endif

    return hc32_qspi_register_bus(&qspi_bus_obj, "qspi1");
}
INIT_BOARD_EXPORT(rt_hw_qspi_bus_init);

#endif /* BSP_USING_QSPI */

#endif /* RT_USING_QSPI */
