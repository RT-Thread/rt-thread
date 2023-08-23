#include "xil_exception.h"
#include "xsdps.h"
#include <stdio.h>
#include "xparameters.h"
#include "rtthread.h"
#include <rtdevice.h>

#define DBG_TAG "drv.mmc"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define EMMC_BLOCK_SIZE (512)

extern u16 TransferMode;
extern s32 XSdPs_CmdTransfer(XSdPs *InstancePtr, u32 Cmd, u32 Arg, u32 BlkCnt);
extern void XSdPs_SetupADMA2DescTbl(XSdPs *InstancePtr, u32 BlkCnt, const u8 *Buff);

// replace XSdPs_ReadPolled, using `rt_thread_mdelay`
s32 XSdPs_ReadPolled_rtt(XSdPs *InstancePtr, u32 Arg, u32 BlkCnt, u8 *Buff)
{
    s32 Status;
    u32 PresentStateReg;
    u32 StatusReg;

    if ((InstancePtr->HC_Version != XSDPS_HC_SPEC_V3) ||
                ((InstancePtr->Host_Caps & XSDPS_CAPS_SLOT_TYPE_MASK)
                != XSDPS_CAPS_EMB_SLOT)) {
        if(InstancePtr->Config.CardDetect != 0U) {
            /* Check status to ensure card is initialized */
            PresentStateReg = XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
                    XSDPS_PRES_STATE_OFFSET);
            if ((PresentStateReg & XSDPS_PSR_CARD_INSRT_MASK) == 0x0U) {
                Status = XST_FAILURE;
                goto RETURN_PATH;
            }
        }
    }

    /* Set block size to 512 if not already set */
    if( XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
            XSDPS_BLK_SIZE_OFFSET) != XSDPS_BLK_SIZE_512_MASK ) {
        Status = XSdPs_SetBlkSize(InstancePtr,
            XSDPS_BLK_SIZE_512_MASK);
        if (Status != XST_SUCCESS) {
            Status = XST_FAILURE;
            goto RETURN_PATH;
        }
    }

    XSdPs_SetupADMA2DescTbl(InstancePtr, BlkCnt, Buff);

    TransferMode = XSDPS_TM_AUTO_CMD12_EN_MASK |
            XSDPS_TM_BLK_CNT_EN_MASK | XSDPS_TM_DAT_DIR_SEL_MASK |
            XSDPS_TM_DMA_EN_MASK | XSDPS_TM_MUL_SIN_BLK_SEL_MASK;

    if (InstancePtr->Config.IsCacheCoherent == 0) {
        Xil_DCacheInvalidateRange((INTPTR)Buff,
            BlkCnt * XSDPS_BLK_SIZE_512_MASK);
    }

    /* Send block read command */
    Status = XSdPs_CmdTransfer(InstancePtr, CMD18, Arg, BlkCnt);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /* Check for transfer complete */
    do {
        StatusReg = XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
                    XSDPS_NORM_INTR_STS_OFFSET);
        if ((StatusReg & XSDPS_INTR_ERR_MASK) != 0U) {
            /* Write to clear error bits */
            XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
                    XSDPS_ERR_INTR_STS_OFFSET,
                    XSDPS_ERROR_INTR_ALL_MASK);
            Status = XST_FAILURE;
            goto RETURN_PATH;
        }

        // delay 1ms
        if ((StatusReg & XSDPS_INTR_TC_MASK) == 0U)
            rt_thread_mdelay(1);

    } while((StatusReg & XSDPS_INTR_TC_MASK) == 0U);

    /* Write to clear bit */
    XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
            XSDPS_NORM_INTR_STS_OFFSET, XSDPS_INTR_TC_MASK);
    Status = (s32)XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
            XSDPS_RESP0_OFFSET);

    Status = XST_SUCCESS;

RETURN_PATH:
    return Status;
}

// replace XSdPs_WritePolled, using rt_thread_mdelay
s32 XSdPs_WritePolled_rtt(XSdPs *InstancePtr, u32 Arg, u32 BlkCnt, const u8 *Buff)
{
    s32 Status;
    u32 PresentStateReg;
    u32 StatusReg;

    if ((InstancePtr->HC_Version != XSDPS_HC_SPEC_V3) ||
                ((InstancePtr->Host_Caps & XSDPS_CAPS_SLOT_TYPE_MASK)
                != XSDPS_CAPS_EMB_SLOT)) {
        if(InstancePtr->Config.CardDetect != 0U) {
            /* Check status to ensure card is initialized */
            PresentStateReg = XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
                    XSDPS_PRES_STATE_OFFSET);
            if ((PresentStateReg & XSDPS_PSR_CARD_INSRT_MASK) == 0x0U) {
                Status = XST_FAILURE;
                goto RETURN_PATH;
            }
        }
    }

    /* Set block size to 512 if not already set */
    if( XSdPs_ReadReg(InstancePtr->Config.BaseAddress,
            XSDPS_BLK_SIZE_OFFSET) != XSDPS_BLK_SIZE_512_MASK ) {
        Status = XSdPs_SetBlkSize(InstancePtr,
            XSDPS_BLK_SIZE_512_MASK);
        if (Status != XST_SUCCESS) {
            Status = XST_FAILURE;
            goto RETURN_PATH;
        }

    }

    XSdPs_SetupADMA2DescTbl(InstancePtr, BlkCnt, Buff);
    if (InstancePtr->Config.IsCacheCoherent == 0) {
        Xil_DCacheFlushRange((INTPTR)Buff,
            BlkCnt * XSDPS_BLK_SIZE_512_MASK);
    }

    TransferMode = XSDPS_TM_AUTO_CMD12_EN_MASK |
            XSDPS_TM_BLK_CNT_EN_MASK |
            XSDPS_TM_MUL_SIN_BLK_SEL_MASK | XSDPS_TM_DMA_EN_MASK;

    /* Send block write command */
    Status = XSdPs_CmdTransfer(InstancePtr, CMD25, Arg, BlkCnt);
    if (Status != XST_SUCCESS) {
        Status = XST_FAILURE;
        goto RETURN_PATH;
    }

    /*
     * Check for transfer complete
     * Polling for response for now
     */
    do {
        StatusReg = XSdPs_ReadReg16(InstancePtr->Config.BaseAddress,
                    XSDPS_NORM_INTR_STS_OFFSET);
        if ((StatusReg & XSDPS_INTR_ERR_MASK) != 0U) {
            /* Write to clear error bits */
            XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
                    XSDPS_ERR_INTR_STS_OFFSET,
                    XSDPS_ERROR_INTR_ALL_MASK);
            Status = XST_FAILURE;
            goto RETURN_PATH;
        }

        if ((StatusReg & XSDPS_INTR_TC_MASK) == 0U)
            rt_thread_mdelay(1);

    } while((StatusReg & XSDPS_INTR_TC_MASK) == 0U);

    /* Write to clear bit */
    XSdPs_WriteReg16(InstancePtr->Config.BaseAddress,
            XSDPS_NORM_INTR_STS_OFFSET, XSDPS_INTR_TC_MASK);

    Status = XST_SUCCESS;

    RETURN_PATH:
        return Status;
}

struct rt_hw_emmc_device {
    struct rt_device dev;
    XSdPs emmc;
    XSdPs_Config *cfg;
    struct rt_mutex lock;
    u16 dev_id;
};

#ifdef BSP_USING_SDIO0
static struct rt_hw_emmc_device emmc0 = {
    .dev_id = XPAR_PS7_SD_0_DEVICE_ID,
};
#endif

#ifdef BSP_USING_SDIO1
static struct rt_hw_emmc_device emmc1 = {
    .dev_id = XPAR_PS7_SD_1_DEVICE_ID,
};
#endif

#define __INIT_CHECK_CFG(cfg) \
    if (Status != XST_SUCCESS) \
    { \
        rt_kprintf("EMMC Config '%s' failed: err: %d\n", cfg, Status); \
        return -RT_EIO; \
    }

static rt_err_t rt_sdcard_init(rt_device_t dev)
{
    RT_ASSERT(dev);
    struct rt_hw_emmc_device *pdev = rt_container_of(dev, struct rt_hw_emmc_device, dev);
    RT_ASSERT(pdev != RT_NULL);

    rt_mutex_take(&pdev->lock, RT_WAITING_FOREVER);
    if (pdev->cfg != RT_NULL)
    {
        LOG_I("init '%s' success", pdev->dev.parent.name);
        rt_mutex_release(&pdev->lock);
        return RT_EOK;
    }

    pdev->cfg = XSdPs_LookupConfig(pdev->dev_id);
    RT_ASSERT(pdev->cfg != RT_NULL);
    s32 Status = XSdPs_CfgInitialize(&pdev->emmc, pdev->cfg, pdev->cfg->BaseAddress);
    __INIT_CHECK_CFG("cfg");

    Status = XSdPs_CardInitialize(&pdev->emmc);
    __INIT_CHECK_CFG("init");

    LOG_I("init '%s' success", pdev->dev.parent.name);
    rt_mutex_release(&pdev->lock);

    return RT_EOK;
}

rt_inline rt_uint32_t _emmc_start_addr(struct rt_hw_emmc_device *pdev)
{
    return 0;
}

rt_inline rt_uint32_t _emmc_size(struct rt_hw_emmc_device *pdev)
{
    return pdev->emmc.SectorCount;
}

rt_inline rt_uint32_t _emmc_end_addr(struct rt_hw_emmc_device *pdev)
{
    return pdev->emmc.SectorCount;
}

static rt_err_t rt_sdcard_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_sdcard_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t rt_sdcard_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    s32 status;
    RT_ASSERT(dev);
    struct rt_hw_emmc_device *pdev = rt_container_of(dev, struct rt_hw_emmc_device, dev);
    RT_ASSERT(pdev != RT_NULL);

    pos += _emmc_start_addr(pdev);
    if (size + pos >= _emmc_end_addr(pdev))
    {
        LOG_E("addr out of ranger: %d %d", pos, size);
        return 0;
    }

    rt_mutex_take(&pdev->lock, RT_WAITING_FOREVER);
    status = XSdPs_ReadPolled_rtt(&pdev->emmc, pos, size, buffer);
    rt_mutex_release(&pdev->lock);

    if (status == XST_SUCCESS)
        return size;

    rt_kprintf("sdcard read failed: %d\n", status);
    return 0;
}

static rt_uint8_t sdio_write_buf[2][EMMC_BLOCK_SIZE] __attribute__((aligned(32)));

static rt_ssize_t rt_sdcard_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    s32 status;
    rt_ssize_t rt = 0;

    RT_ASSERT(dev);
    struct rt_hw_emmc_device *pdev = rt_container_of(dev, struct rt_hw_emmc_device, dev);
    RT_ASSERT(pdev != RT_NULL);

    pos += _emmc_start_addr(pdev);
    if (size + pos >= _emmc_end_addr(pdev))
    {
        LOG_E("addr out of ranger: %d %d", pos, size);
        return 0;
    }

    rt_mutex_take(&pdev->lock, RT_WAITING_FOREVER);
    for (int i = 0; i < size; i++)
    {
        rt_memcpy(sdio_write_buf[pdev->dev_id], ((rt_uint8_t *)buffer) + EMMC_BLOCK_SIZE * i, EMMC_BLOCK_SIZE);

        status = XSdPs_WritePolled_rtt(&pdev->emmc, pos + i, 1, sdio_write_buf[pdev->dev_id]);

        if (status != XST_SUCCESS)
        {
            rt_kprintf("sdcard write failed: %d\n", status);
            break;
        }

        rt++;
    }
    rt_mutex_release(&pdev->lock);

    return rt;
}

static rt_err_t rt_sdcard_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev);
    struct rt_hw_emmc_device *pdev = rt_container_of(dev, struct rt_hw_emmc_device, dev);
    RT_ASSERT(pdev != RT_NULL);

    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;
        if (geometry == RT_NULL)
            return -RT_ERROR;

        geometry->bytes_per_sector = EMMC_BLOCK_SIZE;
        geometry->block_size = EMMC_BLOCK_SIZE;
        geometry->sector_count = _emmc_size(pdev);
    }

    return RT_EOK;
}

static void _init_emmc_dev(struct rt_hw_emmc_device *pdev, const char *name)
{
    rt_mutex_init(&pdev->lock, name, RT_IPC_FLAG_PRIO);

    pdev->dev.type = RT_Device_Class_Block;
    pdev->dev.init = rt_sdcard_init;
    pdev->dev.open = rt_sdcard_open;
    pdev->dev.close = rt_sdcard_close;
    pdev->dev.read = rt_sdcard_read;
    pdev->dev.write = rt_sdcard_write;
    pdev->dev.control = rt_sdcard_control;
    pdev->dev.user_data = RT_NULL;

    rt_device_register(&pdev->dev, name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);
}

int rt_hw_emmc_init(void)
{
#ifdef BSP_USING_SDIO0
    _init_emmc_dev(&emmc0, "sd0");
#endif

#ifdef BSP_USING_SDIO1
    _init_emmc_dev(&emmc1, "sd1");
#endif

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_emmc_init);
