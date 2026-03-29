/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <mm_page.h>
#include <mm_aspace.h>

#define DBG_TAG "rtdm.ufs"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* UTP slot index used for all SCSI commands (single-threaded transfer) */
#define RT_UFS_SLOT_ID                  0
/* Timeout for UTP transfer completion (ms) */
#define RT_UFS_UTP_TIMEOUT_MS           5000
/* UIC command timeout (ms) */
#define RT_UFS_UIC_TIMEOUT_MS           500
/* UTRL/UTMRL base address must be 1KB aligned (UTRLBA/UTMRLBA bits[31:10]). */
#define RT_UFS_UTR_LIST_ALIGN           1024
#define RT_UFS_UTR_LIST_BYTES(n)        ((rt_size_t)(n) * sizeof(struct rt_utp_transfer_req_desc))
/* UTRD dword_0 data direction bits */
#define RT_UFS_UTRD_DD_NONE             0x00000000U
#define RT_UFS_UTRD_DD_HOST_TO_DEVICE   0x02000000U
#define RT_UFS_UTRD_DD_DEVICE_TO_HOST   0x04000000U
/* UTRD dword_0 command type bits */
#define RT_UFS_UTRD_CMD_TYPE_SCSI       (1U << RT_UFS_UPIU_COMMAND_TYPE_OFFSET)

static rt_uint8_t ufs_scsi_cmd_data_dir(struct rt_scsi_cmd *cmd)
{
    switch (cmd->op.unknow.opcode)
    {
    case RT_SCSI_CMD_READ10:
    case RT_SCSI_CMD_READ12:
    case RT_SCSI_CMD_READ16:
    case RT_SCSI_CMD_READ_CAPACITY10:
    case RT_SCSI_CMD_READ_CAPACITY16:
    case RT_SCSI_CMD_INQUIRY:
    case RT_SCSI_CMD_REQUEST_SENSE:
        return RT_UTP_DEVICE_TO_HOST;
    case RT_SCSI_CMD_WRITE10:
    case RT_SCSI_CMD_WRITE12:
    case RT_SCSI_CMD_WRITE16:
        return RT_UTP_HOST_TO_DEVICE;
    default:
        return RT_UTP_NO_DATA_TRANSFER;
    }
}

static void ufs_prepare_upiu_cmd(struct rt_ufs_host *ufs, struct rt_utp_upiu_req *req, struct rt_utp_upiu_rsp *rsp,
        struct rt_scsi_device *sdev, struct rt_scsi_cmd *cmd)
{
    rt_uint16_t cdb_len;
    rt_size_t data_len = cmd->data.size;
    rt_uint8_t flags = RT_UPIU_CMD_FLAGS_NONE;

    if (ufs_scsi_cmd_data_dir(cmd) == RT_UTP_DEVICE_TO_HOST)
    {
        flags = RT_UPIU_CMD_FLAGS_READ;
    }
    else if (ufs_scsi_cmd_data_dir(cmd) == RT_UTP_HOST_TO_DEVICE)
    {
        flags = RT_UPIU_CMD_FLAGS_WRITE;
    }

    rt_memset(req, 0, sizeof(*req));
    req->header.transaction_code = RT_UPIU_TRANSACTION_COMMAND;
    req->header.flags = flags;
    req->header.lun = (rt_uint8_t)(sdev->lun & 0x7f);
    req->header.task_tag = RT_UFS_SLOT_ID;
    req->header.command_set_type = RT_UPIU_COMMAND_SET_TYPE_SCSI;
    req->header.data_segment_length = rt_cpu_to_be16((rt_uint16_t)data_len);

    req->sc.exp_data_transfer_len = rt_cpu_to_be32((rt_uint32_t)data_len);
    cdb_len = cmd->op_size < RT_UFS_CDB_SIZE ? (rt_uint16_t)cmd->op_size : RT_UFS_CDB_SIZE;
    rt_memcpy(req->sc.cdb, &cmd->op, cdb_len);

    rt_memset(rsp, 0, sizeof(*rsp));
}

/* Fill UTRD header and link to UCD; PRDT filled separately. */
static rt_err_t ufs_prepare_utrd(struct rt_ufs_host *ufs, rt_uint8_t data_dir, rt_size_t data_len)
{
    rt_uint64_t ucd_phys = ufs->ucd_handle;
    rt_uint32_t utp_dd_dword = RT_UFS_UTRD_DD_NONE;
    rt_uint16_t resp_off_dw, resp_len_dw, prdt_off_dw, prdt_len_entries;
    struct rt_utp_transfer_req_desc *utrd = ufs->utrd;

    /* Clear whole descriptor to avoid any leftover fields */
    rt_memset(utrd, 0, sizeof(*utrd));

    /* UFSHCI: offset/length in DWORDs (4 bytes) */
    resp_off_dw = (rt_uint16_t)(RT_UFS_ALIGNED_UPIU_SIZE >> 2);
    prdt_off_dw = (rt_uint16_t)((RT_UFS_ALIGNED_UPIU_SIZE * 2) >> 2);
    resp_len_dw = (rt_uint16_t)(RT_UFS_ALIGNED_UPIU_SIZE >> 2);
    prdt_len_entries = (data_len > 0) ? 1 : 0;

    /* RequestDescHeader.dword_0..dword_3 */
    if (data_dir == RT_UTP_HOST_TO_DEVICE)
    {
        utp_dd_dword = RT_UFS_UTRD_DD_HOST_TO_DEVICE;
    }
    else if (data_dir == RT_UTP_DEVICE_TO_HOST)
    {
        utp_dd_dword = RT_UFS_UTRD_DD_DEVICE_TO_HOST;
    }

    /* Always set INT_CMD to ensure UTRCS gets asserted */
    utrd->header.dword_0 = rt_cpu_to_le32(RT_UFS_UTRD_CMD_TYPE_SCSI | utp_dd_dword | RT_UFS_UTP_REQ_DESC_INT_CMD);
    utrd->header.dword_1 = 0;
    utrd->header.dword_2 = rt_cpu_to_le32(RT_UFS_OCS_INVALID_COMMAND_STATUS);
    utrd->header.dword_3 = 0;

    /* UFSHCI expects LE for descriptor fields */
    utrd->command_desc_base_addr_lo = rt_cpu_to_le32(rt_lower_32_bits(ucd_phys));
    utrd->command_desc_base_addr_hi = rt_cpu_to_le32(rt_upper_32_bits(ucd_phys));
    utrd->response_upiu_offset = rt_cpu_to_le16(resp_off_dw);
    utrd->response_upiu_length = rt_cpu_to_le16(resp_len_dw);
    utrd->prd_table_offset = rt_cpu_to_le16(prdt_off_dw);
    utrd->prd_table_length = rt_cpu_to_le16(prdt_len_entries);

    return RT_EOK;
}

/* Fill PRDT with entries for cmd->data.ptr (split by page boundary). */
static rt_err_t ufs_prepare_prdt(struct rt_ufs_host *ufs, const void *data_ptr, rt_size_t len, rt_uint16_t *out_entries)
{
    rt_size_t left;
    rt_uint8_t *ptr;
    rt_uint16_t n = 0;
    struct rt_utp_transfer_cmd_desc *ucd = (struct rt_utp_transfer_cmd_desc *)ufs->ucd_base;
    struct rt_ufs_sg_entry *prd = ucd->prd_table;

    if (out_entries)
    {
        *out_entries = 0;
    }

    if (len == 0)
    {
        return RT_EOK;
    }

    left = len;
    ptr = (rt_uint8_t *)(rt_ubase_t)data_ptr;

    while (left)
    {
        rt_uint64_t addr;
        rt_size_t chunk, page_off;

        if (n >= RT_UFS_PRDT_ENTRIES_PER_SLOT)
        {
            LOG_E("%s: UFS: PRDT entries overflow (len=%u left=%u n=%u)", rt_dm_dev_get_name(ufs->parent.dev),
                    len, left, n);
            return -RT_EIO;
        }

        page_off = ((rt_ubase_t)ptr) & (ARCH_PAGE_SIZE - 1);
        chunk = ARCH_PAGE_SIZE - page_off;
        if (chunk > left)
        {
            chunk = left;
        }

        if (ptr >= ufs->bounce && ptr < (ufs->bounce + ufs->bounce_size))
        {
            addr = (rt_uint64_t)ufs->bounce_handle + (rt_uint64_t)(ptr - ufs->bounce);
        }
        else
        {
            addr = (rt_uint64_t)rt_kmem_v2p(ptr);
        }

        prd[n].addr = rt_cpu_to_le64(addr);
        prd[n].reserved = 0;
        prd[n].size = rt_cpu_to_le32((rt_uint32_t)(chunk - 1)); /* 0-based byte count */

        ptr += chunk;
        left -= chunk;
        ++n;
    }

    if (out_entries)
    {
        *out_entries = n;
    }

    return RT_EOK;
}

static rt_err_t ufs_utp_transfer(struct rt_ufs_host *ufs, struct rt_scsi_device *sdev, struct rt_scsi_cmd *cmd)
{
    struct rt_utp_transfer_cmd_desc *ucd = (struct rt_utp_transfer_cmd_desc *)ufs->ucd_base;
    struct rt_utp_upiu_req *req = (struct rt_utp_upiu_req *)ucd->command_upiu;
    struct rt_utp_upiu_rsp *rsp = (struct rt_utp_upiu_rsp *)ucd->response_upiu;
    struct rt_utp_transfer_req_desc *utrd = ufs->utrd;
    void *regs = ufs->regs;
    rt_uint8_t data_dir;
    rt_uint32_t is;
    rt_err_t err = RT_EOK;
    rt_uint16_t prdt_entries = 0;
    rt_uint8_t ocs;
    rt_bool_t use_bounce = RT_FALSE;
    void *orig_ptr = cmd->data.ptr, *resp_buf;
    rt_size_t orig_size = cmd->data.size;
    void *dma_ptr = cmd->data.ptr;
    rt_size_t dma_size = cmd->data.size;
    rt_bool_t bounce_copied = RT_FALSE;

    data_dir = ufs_scsi_cmd_data_dir(cmd);
    /* Basic controller readiness checks to avoid hard timeouts */
    if (regs)
    {
        rt_uint32_t hcs = HWREG32(regs + RT_UFS_REG_HCS);
        rt_uint32_t hce = HWREG32(regs + RT_UFS_REG_HCE);

        if (!(hce & 0x1) || !(hcs & RT_UFS_REG_HCS_UTRLRDY) || !(hcs & RT_UFS_REG_HCS_UCRDY))
        {
            LOG_E("%s: UFS not ready for UTP: HCE=%#08x HCS=%#08x (UTRLRDY=%u UCRDY=%u)",
                  rt_dm_dev_get_name(ufs->parent.dev),
                  hce, hcs,
                  (hcs & RT_UFS_REG_HCS_UTRLRDY) ? 1 : 0,
                  (hcs & RT_UFS_REG_HCS_UCRDY) ? 1 : 0);

            return -RT_EIO;
        }
    }

    /*
     * Bounce small I/O buffers.
     * Many SCSI helper commands use stack-allocated buffers (embedded in rt_scsi_cmd),
     * which are unsafe for DMA in Smart/MMU environments. Use a pre-allocated
     * DMA-friendly bounce buffer for small transfers.
     */
    if (cmd->data.ptr && cmd->data.size && ufs->bounce && ufs->bounce_size && cmd->data.size <= ufs->bounce_size)
    {
        use_bounce = RT_TRUE;

        if (data_dir == RT_UTP_HOST_TO_DEVICE)
        {
            rt_memcpy(ufs->bounce, orig_ptr, orig_size);
        }
        dma_ptr = ufs->bounce;
        dma_size = orig_size;
    }

    ufs_prepare_upiu_cmd(ufs, req, rsp, sdev, cmd);
    if ((err = ufs_prepare_utrd(ufs, data_dir, cmd->data.size)))
    {
        goto _end;
    }

    if ((err = ufs_prepare_prdt(ufs, dma_ptr, dma_size, &prdt_entries)))
    {
        goto _end;
    }
    utrd->prd_table_length = rt_cpu_to_le16(prdt_entries);

    /* Basic debug information before submitting UTP */
    LOG_D("%s: UTP submit: opcode=%#02x dir=%u data_len=%u slot=%u",
            rt_dm_dev_get_name(ufs->parent.dev),
            cmd->op.unknow.opcode, data_dir,
            cmd->data.size, RT_UFS_SLOT_ID);
    LOG_D("%s: UTP ctrl regs: HCS=%#08x IE=%#08x HCE=%#08x",
            rt_dm_dev_get_name(ufs->parent.dev),
            HWREG32(regs + RT_UFS_REG_HCS),
            HWREG32(regs + RT_UFS_REG_IE),
            HWREG32(regs + RT_UFS_REG_HCE));
    LOG_D("%s: UTP ctrl ready bits: UTRLRDY=%u UTMRLRDY=%u UICRDY=%u",
            rt_dm_dev_get_name(ufs->parent.dev),
            (HWREG32(regs + RT_UFS_REG_HCS) & RT_UFS_REG_HCS_UTRLRDY) ? 1 : 0,
            (HWREG32(regs + RT_UFS_REG_HCS) & RT_UFS_REG_HCS_UTMRLRDY) ? 1 : 0,
            (HWREG32(regs + RT_UFS_REG_HCS) & RT_UFS_REG_HCS_UCRDY) ? 1 : 0);
    LOG_D("%s: UTP UTRD: dword_0=%#08x dword_2(ocs)=%#08x",
            rt_dm_dev_get_name(ufs->parent.dev),
            rt_le32_to_cpu(utrd->header.dword_0),
            rt_le32_to_cpu(utrd->header.dword_2));
    LOG_D("%s: UTP UTRD: ucd_base_lo=%#08x ucd_base_hi=%#08x resp_off_dw=%u resp_len_dw=%u prd_off_dw=%u prd_len=%u",
            rt_dm_dev_get_name(ufs->parent.dev),
            rt_le32_to_cpu(utrd->command_desc_base_addr_lo),
            rt_le32_to_cpu(utrd->command_desc_base_addr_hi),
            rt_le16_to_cpu(utrd->response_upiu_offset),
            rt_le16_to_cpu(utrd->response_upiu_length),
            rt_le16_to_cpu(utrd->prd_table_offset),
            rt_le16_to_cpu(utrd->prd_table_length));

    /*
     * DMA descriptors/data must be visible to controller.
     * Clean dcache for UTRD + UCD (command/response/PRDT) before ringing doorbell.
     */
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, ufs->utrd, sizeof(*utrd));
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, ufs->ucd_base, ufs->ucd_size);

    if (dma_ptr && dma_size && data_dir == RT_UTP_HOST_TO_DEVICE)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, dma_ptr, dma_size);
    }

    /* Clear interrupt status for transfer complete */
    ufs->irq_status = 0;
    /* Ack any stale pending IRQ bits before kicking */
    HWREG32(regs + RT_UFS_REG_IS) = RT_UINT32_MAX;
    /* Enable UTP completion/error interrupts */
    HWREG32(regs + RT_UFS_REG_IE) = RT_UFS_REG_IE_UTRCE | RT_UFS_REG_IE_UTPEE | RT_UFS_REG_IE_DFEE | RT_UFS_REG_IE_UEE;

    /* Ring door bell for slot 0 */
    rt_spin_lock(&ufs->lock);
    HWREG32(regs + RT_UFS_REG_UTRLDBR) = RT_BIT(RT_UFS_SLOT_ID);
    rt_spin_unlock(&ufs->lock);

    /* Interrupt mode: wait for completion signaled by ISR */
    if ((err = rt_completion_wait(&ufs->done, rt_tick_from_millisecond(RT_UFS_UTP_TIMEOUT_MS))))
    {
        LOG_E("%s: UFS UTP wait timeout: IS=%#08x irq_status=%#08x",
                rt_dm_dev_get_name(ufs->parent.dev),
                HWREG32(regs + RT_UFS_REG_IS), ufs->irq_status);

        /* Dump UPIU header and PRDT entry for post-mortem */
        LOG_E("%s: UTP UPIU: tx=%u flags=%#02x lun=%u tag=%u seg_len(be16)=%u",
                rt_dm_dev_get_name(ufs->parent.dev),
                req->header.transaction_code, req->header.flags,
                req->header.lun, req->header.task_tag,
                rt_be16_to_cpu(req->header.data_segment_length));

        if (cmd->data.size > 0)
        {
            LOG_E("%s: UTP PRDT[0]: addr=%#llx size(le32)=%#08x",
                    rt_dm_dev_get_name(ufs->parent.dev),
                    (rt_uint64_t)(&((struct rt_utp_transfer_cmd_desc *)ufs->ucd_base)->prd_table[0])->addr,
                    (&((struct rt_utp_transfer_cmd_desc *)ufs->ucd_base)->prd_table[0])->size);
        }

        goto _end;
    }

    is = ufs->irq_status | HWREG32(regs + RT_UFS_REG_IS);
    if (is & (RT_UFS_REG_IS_UTPES | RT_UFS_REG_IS_DFES | RT_UFS_REG_IS_UE))
    {
        err = -RT_ERROR;
        goto _end;
    }

    /* Ensure controller-written status/data are seen */
    /* UTRL is 1KB aligned; invalidate a full slot region to avoid cacheline/alias issues */
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, ufs->utrl_base, RT_UFS_UTR_LIST_ALIGN);
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, ufs->ucd_base, ufs->ucd_size);
    if (dma_ptr && dma_size && data_dir == RT_UTP_DEVICE_TO_HOST)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, dma_ptr, dma_size);
    }

    /*
     * If bounce buffer is used for device->host, copy it back immediately after
     * invalidation so that any post-processing (e.g. READ CAPACITY emulation)
     * operates on the latest data. Otherwise, the late copy at out_restore would
     * overwrite any modifications.
     */
    if (use_bounce && data_dir == RT_UTP_DEVICE_TO_HOST && orig_ptr && orig_size)
    {
        rt_memcpy(orig_ptr, ufs->bounce, orig_size);
        bounce_copied = RT_TRUE;
    }

    LOG_D("%s: UFS UTRD complete: dword_2=%#08x (ocs=%#x)",
            rt_dm_dev_get_name(ufs->parent.dev),
            rt_le32_to_cpu(utrd->header.dword_2),
            (rt_le32_to_cpu(utrd->header.dword_2) & 0x0f));

    /*
     * Post-process SCSI response in resp_buf (INQUIRY etc.).
     * READ CAPACITY: pass through device-reported block_size / last_block.
     * Use resp_buf: after bounce_copied, cmd->data.ptr may alias response memory.
     */
    resp_buf = (bounce_copied && orig_ptr) ? orig_ptr : cmd->data.ptr;

    if (!resp_buf)
    {
        goto _no_resp_buf;
    }

    if (cmd->op.unknow.opcode == RT_SCSI_CMD_INQUIRY &&
        cmd->data.size >= sizeof(struct rt_scsi_inquiry_data))
    {
        struct rt_scsi_inquiry_data *inq = (struct rt_scsi_inquiry_data *)resp_buf;

        /* Align with AHCI behavior: always expose direct-access block device */
        inq->devtype = SCSI_DEVICE_TYPE_DIRECT;
        inq->rmb = 0;
        inq->length = 95 - 4;
    }

_no_resp_buf:
    /* Log response header for troubleshooting */
    LOG_D("%s: UFS RSP: tc=%#02x rsp=%#02x sts=%#02x seg_len=%u sense_len=%u",
          rt_dm_dev_get_name(ufs->parent.dev),
          rsp->header.transaction_code,
          rsp->header.response,
          rsp->header.status,
          rt_be16_to_cpu(rsp->header.data_segment_length),
          rt_be16_to_cpu(rsp->sr.sense_data_len));

    ocs = rt_le32_to_cpu(utrd->header.dword_2) & 0xf;
    if (ocs != RT_UFS_OCS_SUCCESS)
    {
        LOG_E("%s: UFS OCS %#x", rt_dm_dev_get_name(ufs->parent.dev), ocs);
        err = -RT_ERROR;
        goto _end;
    }

    if (rsp->header.transaction_code != RT_UPIU_TRANSACTION_RESPONSE)
    {
        err = -RT_ERROR;
        goto _end;
    }

    if (rsp->header.status != 0)
    {
        err = -RT_ERROR;
        goto _end;
    }

    /* Sense data: copy to cmd when check condition (BSP may use cmd->data.ptr for sense) */
    if (err != RT_EOK && rsp->sr.sense_data_len != 0 && cmd->data.ptr && cmd->data.size >= RT_UFS_SENSE_SIZE)
    {
        rt_uint16_t sense_len = rt_be16_to_cpu(rsp->sr.sense_data_len);

        sense_len = rt_min_t(rt_uint16_t, sense_len, RT_UFS_SENSE_SIZE);
        rt_memcpy(cmd->data.ptr, rsp->sr.sense_data, sense_len);
    }

_end:
    if (use_bounce && !bounce_copied && err == RT_EOK && data_dir == RT_UTP_DEVICE_TO_HOST && orig_ptr && orig_size)
    {
        rt_memcpy(orig_ptr, ufs->bounce, orig_size);
    }

    return err;
}

static rt_err_t ufs_host_reset(struct rt_scsi_device *sdev)
{
    struct rt_ufs_host *ufs = rt_container_of(sdev->host, struct rt_ufs_host, parent);

    if (ufs->ops->reset)
    {
        return ufs->ops->reset(ufs);
    }

    return RT_EOK;
}

static rt_err_t ufs_host_transfer(struct rt_scsi_device *sdev, struct rt_scsi_cmd *cmd)
{
    rt_err_t err;
    struct rt_ufs_host *ufs = rt_container_of(sdev->host, struct rt_ufs_host, parent);

    switch (cmd->op.unknow.opcode)
    {
    case RT_SCSI_CMD_REQUEST_SENSE:
    case RT_SCSI_CMD_READ10:
    case RT_SCSI_CMD_READ12:
    case RT_SCSI_CMD_READ16:
    case RT_SCSI_CMD_WRITE10:
    case RT_SCSI_CMD_WRITE12:
    case RT_SCSI_CMD_WRITE16:
    case RT_SCSI_CMD_SYNCHRONIZE_CACHE10:
    case RT_SCSI_CMD_SYNCHRONIZE_CACHE16:
    case RT_SCSI_CMD_READ_CAPACITY10:
    case RT_SCSI_CMD_READ_CAPACITY16:
    case RT_SCSI_CMD_TEST_UNIT_READY:
    case RT_SCSI_CMD_INQUIRY:
        err = ufs_utp_transfer(ufs, sdev, cmd);
        break;

    case RT_SCSI_CMD_WRITE_SAME10:
    case RT_SCSI_CMD_WRITE_SAME16:
    case RT_SCSI_CMD_MODE_SENSE:
    case RT_SCSI_CMD_MODE_SENSE10:
    case RT_SCSI_CMD_MODE_SELECT:
    case RT_SCSI_CMD_MODE_SELECT10:
        err = -RT_ENOSYS;
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

static struct rt_scsi_ops ufs_host_ops =
{
    .reset = ufs_host_reset,
    .transfer = ufs_host_transfer,
};

static void ufs_isr(int irqno, void *param)
{
    rt_uint32_t is;
    struct rt_ufs_host *ufs = param;

    if (!(is = HWREG32(ufs->regs + RT_UFS_REG_IS)))
    {
        return;
    }

    ufs->irq_status |= is;
    HWREG32(ufs->regs + RT_UFS_REG_IS) = is;

    if (is & (RT_UFS_REG_IS_UTRCS | RT_UFS_REG_IS_UTPES | RT_UFS_REG_IS_DFES | RT_UFS_REG_IS_UE))
    {
        rt_completion_done(&ufs->done);
    }
}

rt_err_t rt_ufs_host_register(struct rt_ufs_host *ufs)
{
    rt_err_t err;
    rt_uint32_t value;
    char dev_name[RT_NAME_MAX];
    struct rt_scsi_host *scsi;

    if (!ufs || !ufs->ops || !ufs->regs)
    {
        return -RT_EINVAL;
    }

    ufs->cap = HWREG32(ufs->regs + RT_UFS_REG_CAP);
    ufs->nutrs = RT_UFS_REG_CAP_NUTRS(ufs->cap) + 1;
    ufs->nutrs = rt_min_t(rt_uint32_t, 32, ufs->nutrs);

    /* Allocate UTRL (UTRD list) with required 1KB alignment */
    ufs->utrl_size = RT_UFS_UTR_LIST_BYTES(ufs->nutrs);
    ufs->utrl_size = rt_max_t(rt_size_t, ufs->utrl_size, RT_UFS_UTR_LIST_ALIGN);
    ufs->utrl_base = rt_dma_alloc_coherent(ufs->parent.dev, ufs->utrl_size, &ufs->utrl_handle);

    if (!ufs->utrl_base)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    rt_memset(ufs->utrl_base, 0, ufs->utrl_size);
    ufs->utrd = (struct rt_utp_transfer_req_desc *)ufs->utrl_base; /* Slot0 */

    /* Allocate UCD (Command Descriptor) */
    ufs->ucd_size = ufs->ucd_size ? : RT_UFS_UCD_SIZE;
    ufs->ucd_base = rt_dma_alloc_coherent(ufs->parent.dev, ufs->ucd_size, &ufs->ucd_handle);

    if (!ufs->ucd_base)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    rt_memset(ufs->ucd_base, 0, ufs->ucd_size);

    /* Allocate bounce buffer for small DMA transfers (512B is enough for inquiry/sense/capacity) */
    ufs->bounce_size = 4096;
    ufs->bounce_handle = 0;
    ufs->bounce = rt_dma_alloc_coherent(ufs->parent.dev, ufs->bounce_size, &ufs->bounce_handle);

    if (!ufs->bounce)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    rt_memset(ufs->bounce, 0, ufs->bounce_size);

    /* Variant/board specific init (clocks/reset/phy) */
    if (ufs->ops->init && (err = ufs->ops->init(ufs)))
    {
        goto _fail;
    }

    /* Enable controller (HCE 1) */
    HWREG32(ufs->regs + RT_UFS_REG_HCE) = 0;
    rt_thread_mdelay(1);
    HWREG32(ufs->regs + RT_UFS_REG_HCE) = 0x1;
    rt_thread_mdelay(1);

    /* Program UTRD/UTMRD list base addresses */
    HWREG32(ufs->regs + RT_UFS_REG_UTRLBA) = rt_lower_32_bits(ufs->utrl_handle);
    HWREG32(ufs->regs + RT_UFS_REG_UTRLBAU) = rt_upper_32_bits(ufs->utrl_handle);

    /* UTMRL: allocate minimal aligned list if not provided */
    ufs->utmrl_size = RT_UFS_UTR_LIST_ALIGN;
    ufs->utmrl_handle = 0;
    ufs->utmrl_base = rt_dma_alloc_coherent(ufs->parent.dev, ufs->utmrl_size, &ufs->utmrl_handle);
    if (ufs->utmrl_base)
    {
        rt_memset(ufs->utmrl_base, 0, ufs->utmrl_size);
    }

    HWREG32(ufs->regs + RT_UFS_REG_UTMRLBA) = rt_lower_32_bits(ufs->utmrl_handle);
    HWREG32(ufs->regs + RT_UFS_REG_UTMRLBAU) = rt_upper_32_bits(ufs->utmrl_handle);

    /* Start run/stop */
    HWREG32(ufs->regs + RT_UFS_REG_UTRLRSR) = 0x1;
    HWREG32(ufs->regs + RT_UFS_REG_UTMRLRSR) = 0x1;

    /* Link startup: set UTRLRDY/UTMRLRDY */
    value = HWREG32(ufs->regs + RT_UFS_REG_HCS);
    if (!(value & RT_UFS_REG_HCS_UTRLRDY) || !(value & RT_UFS_REG_HCS_UTMRLRDY) || !(value & RT_UFS_REG_HCS_UCRDY))
    {
        if (ufs->ops->link_startup_notify)
        {
            ufs->ops->link_startup_notify(ufs, RT_UFS_NOTIFY_CHANGE_STATUS_PRE);
        }

        if ((err = rt_ufs_uic_cmd_send(ufs, RT_UFS_CMDOP_DME_LINKSTARTUP, 0, &value, 0)))
        {
            goto _fail;
        }

        if (ufs->ops->link_startup_notify)
        {
            ufs->ops->link_startup_notify(ufs, RT_UFS_NOTIFY_CHANGE_STATUS_POST);
        }
    }

    ufs->pwr_active_valid = 0;
    /* ahit==0 lets rt_ufs_pm_post_linkup apply RT_UFS_AHIT_DEFAULT when CAP_AUTOH8 */
    rt_ufs_pm_post_linkup(ufs);

    rt_completion_init(&ufs->done);
    rt_spin_lock_init(&ufs->lock);

    rt_snprintf(dev_name, sizeof(dev_name), "ufs-%s", rt_dm_dev_get_name(ufs->parent.dev));

    rt_hw_interrupt_install(ufs->irq, ufs_isr, ufs, dev_name);
    rt_hw_interrupt_umask(ufs->irq);

    scsi = &ufs->parent;
    scsi->ops = &ufs_host_ops;
    scsi->max_id = rt_max_t(rt_size_t, scsi->max_id, 1);
    scsi->max_lun = rt_max_t(rt_size_t, scsi->max_lun, 1);
    scsi->parallel_io = RT_TRUE;

    if ((err = rt_scsi_host_register(scsi)))
    {
        goto _free_irq;
    }

    return RT_EOK;

_free_irq:
    rt_hw_interrupt_mask(ufs->irq);
    rt_pic_detach_irq(ufs->irq, ufs);

_fail:
    if (ufs->utrl_base)
    {
        rt_dma_free_coherent(ufs->parent.dev, ufs->utrl_size, ufs->utrl_base, ufs->utrl_handle);
        ufs->utrl_base = RT_NULL;
    }
    if (ufs->utmrl_base)
    {
        rt_dma_free_coherent(ufs->parent.dev, ufs->utmrl_size, ufs->utmrl_base, ufs->utmrl_handle);
        ufs->utmrl_base = RT_NULL;
    }
    if (ufs->ucd_base)
    {
        rt_dma_free_coherent(ufs->parent.dev, ufs->ucd_size, ufs->ucd_base, ufs->ucd_handle);
        ufs->ucd_base = RT_NULL;
    }
    if (ufs->bounce)
    {
        rt_dma_free_coherent(ufs->parent.dev, ufs->bounce_size, ufs->bounce, ufs->bounce_handle);
        ufs->bounce = RT_NULL;
    }

    return err;
}

rt_err_t rt_ufs_host_unregister(struct rt_ufs_host *ufs)
{
    rt_err_t err = RT_EOK;

    rt_scsi_host_unregister(&ufs->parent);

    if (ufs->ops->exit && (err = ufs->ops->exit(ufs)))
    {
        LOG_W("%s: UFS ops->exit failed: %s", rt_dm_dev_get_name(ufs->parent.dev), rt_strerror(err));
    }

    if (ufs->utrl_base)
    {
        rt_dma_free_coherent(ufs->parent.dev, ufs->utrl_size, ufs->utrl_base, ufs->utrl_handle);
        ufs->utrl_base = RT_NULL;
    }
    if (ufs->utmrl_base)
    {
        rt_dma_free_coherent(ufs->parent.dev, ufs->utmrl_size, ufs->utmrl_base, ufs->utmrl_handle);
        ufs->utmrl_base = RT_NULL;
    }
    if (ufs->ucd_base)
    {
        rt_dma_free_coherent(ufs->parent.dev, ufs->ucd_size, ufs->ucd_base, ufs->ucd_handle);
        ufs->ucd_base = RT_NULL;
    }
    if (ufs->bounce)
    {
        rt_dma_free_coherent(ufs->parent.dev, ufs->bounce_size, ufs->bounce, ufs->bounce_handle);
        ufs->bounce = RT_NULL;
    }

    return err;
}

rt_err_t rt_ufs_uic_cmd_send(struct rt_ufs_host *ufs, rt_uint32_t cmd,
        rt_uint32_t arg1, rt_uint32_t *arg2, rt_uint32_t arg3)
{
    rt_uint32_t is;
    rt_int32_t timeout;
    void *regs = ufs->regs;

    if (!regs)
    {
        return -RT_EINVAL;
    }

    timeout = rt_tick_from_millisecond(RT_UFS_UIC_TIMEOUT_MS);
    timeout += rt_tick_get();

    while (!(HWREG32(regs + RT_UFS_REG_HCS) & RT_UFS_REG_HCS_UCRDY))
    {
        if (rt_tick_get() >= timeout)
        {
            LOG_E("%s: UFS UIC not ready", rt_dm_dev_get_name(ufs->parent.dev));
            return -RT_ETIMEOUT;
        }

        rt_thread_mdelay(1);
    }

    HWREG32(regs + RT_UFS_REG_UCMDARG1) = arg1;
    HWREG32(regs + RT_UFS_REG_UCMDARG2) = arg2 ? *arg2 : 0;
    HWREG32(regs + RT_UFS_REG_UCMDARG3) = arg3;
    HWREG32(regs + RT_UFS_REG_UICCMD) = cmd & 0xff;

    timeout = rt_tick_from_millisecond(RT_UFS_UIC_TIMEOUT_MS);
    timeout += rt_tick_get();

    do {
        is = HWREG32(regs + RT_UFS_REG_IS);
        if (is & RT_UFS_REG_IS_UCCS)
        {
            break;
        }
        if (is & (RT_UFS_REG_IS_UE | RT_UFS_REG_IS_DFES))
        {
            return -RT_ERROR;
        }
        rt_thread_mdelay(1);
    } while (rt_tick_get() < timeout);

    if (!(is & RT_UFS_REG_IS_UCCS))
    {
        return -RT_ETIMEOUT;
    }

    HWREG32(regs + RT_UFS_REG_IS) = RT_UFS_REG_IS_UCCS;

    if (arg2)
    {
        *arg2 = HWREG32(regs + RT_UFS_REG_UCMDARG2);
    }

    return RT_EOK;
}
