#include "fee_internal.h"

typedef struct
{
    uint8_t used;
    uint8_t type;
    fee_request_t request;
} fee_sched_slot_t;

static fee_sched_slot_t g_fee_sched_urgent[FEE_CFG_MAX_PENDING_REQUESTS];
static fee_sched_slot_t g_fee_sched_normal[FEE_CFG_MAX_PENDING_REQUESTS];

static void fee_sched_clear_queue(fee_sched_slot_t *queue, uint16_t queue_len)
{
    if ((queue == RT_NULL) || (queue_len == 0U))
    {
        return;
    }

    (void)memset(queue, 0, (rt_size_t)queue_len * sizeof(queue[0]));
}

static rt_bool_t fee_sched_queue_has_work(const fee_sched_slot_t *queue, uint16_t queue_len)
{
    uint16_t idx;

    if ((queue == RT_NULL) || (queue_len == 0U))
    {
        return RT_FALSE;
    }

    for (idx = 0U; idx < queue_len; ++idx)
    {
        if (queue[idx].used != 0U)
        {
            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

static fee_ret_t fee_sched_queue_push(fee_sched_slot_t *queue, uint16_t queue_len,
    fee_request_type_t type, const fee_request_t *request)
{
    uint16_t idx;

    if ((queue == RT_NULL) || (request == RT_NULL) || (type == FEE_REQ_NONE))
    {
        return FEE_E_PARAM;
    }

    for (idx = 0U; idx < queue_len; ++idx)
    {
        if (queue[idx].used == 0U)
        {
            queue[idx].used = 1U;
            queue[idx].type = (uint8_t)type;
            queue[idx].request = *request;
            return FEE_E_OK;
        }
    }

    return FEE_E_BUSY;
}

static rt_bool_t fee_sched_queue_pop(fee_sched_slot_t *queue, uint16_t queue_len, fee_sched_slot_t *slot)
{
    uint16_t idx;

    if ((queue == RT_NULL) || (slot == RT_NULL) || (queue_len == 0U))
    {
        return RT_FALSE;
    }

    if (queue[0].used == 0U)
    {
        return RT_FALSE;
    }

    *slot = queue[0];

    for (idx = 1U; idx < queue_len; ++idx)
    {
        queue[idx - 1U] = queue[idx];
    }

    (void)memset(&queue[queue_len - 1U], 0, sizeof(queue[0]));
    return RT_TRUE;
}

static fee_ret_t fee_sched_enqueue_request(fee_request_type_t type, const fee_request_t *request)
{
    const fee_block_cfg_t *cfg;
    fee_sched_slot_t *queue;

    if (request == RT_NULL)
    {
        return FEE_E_PARAM;
    }

    cfg = fee_cfg_find_block(request->block_id);
    if (cfg == RT_NULL)
    {
        return FEE_E_PARAM;
    }

    queue = (cfg->lane_type == (uint8_t)FEE_LANE_FAST) ? &g_fee_sched_urgent[0] : &g_fee_sched_normal[0];
    return fee_sched_queue_push(queue, FEE_CFG_MAX_PENDING_REQUESTS, type, request);
}

static fee_ret_t fee_sched_dispatch_one(const fee_sched_slot_t *slot)
{
    if (slot == RT_NULL)
    {
        return FEE_E_PARAM;
    }

    if (slot->type == (uint8_t)FEE_REQ_WRITE)
    {
        return fee_core_write(slot->request.block_id, slot->request.src, slot->request.len);
    }

    if (slot->type == (uint8_t)FEE_REQ_INVALIDATE)
    {
        return fee_core_invalidate(slot->request.block_id);
    }

    if (slot->type == (uint8_t)FEE_REQ_ROLLBACK)
    {
        return fee_core_rollback(slot->request.block_id);
    }

    return FEE_E_PARAM;
}

fee_ret_t fee_sched_submit_read(uint16_t block_id, uint16_t offset, uint8_t *dst, uint16_t len)
{
    return fee_core_read(block_id, offset, dst, len);
}

fee_ret_t fee_sched_submit_write(uint16_t block_id, const uint8_t *src, uint16_t len)
{
    fee_request_t request;
    fee_ret_t ret;

    request.block_id = block_id;
    request.offset = 0U;
    request.len = len;
    request.src = src;
    request.dst = RT_NULL;

    ret = fee_sched_enqueue_request(FEE_REQ_WRITE, &request);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    g_fee_ctx.status = FEE_STATUS_BUSY_INTERNAL;
    g_fee_ctx.job_result = FEE_JOB_PENDING;
    return FEE_E_OK;
}

fee_ret_t fee_sched_submit_invalidate(uint16_t block_id)
{
    fee_request_t request;
    fee_ret_t ret;

    request.block_id = block_id;
    request.offset = 0U;
    request.len = 0U;
    request.src = RT_NULL;
    request.dst = RT_NULL;

    ret = fee_sched_enqueue_request(FEE_REQ_INVALIDATE, &request);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    g_fee_ctx.status = FEE_STATUS_BUSY_INTERNAL;
    g_fee_ctx.job_result = FEE_JOB_PENDING;
    return FEE_E_OK;
}

fee_ret_t fee_sched_submit_rollback(uint16_t block_id)
{
    fee_request_t request;
    fee_ret_t ret;

    request.block_id = block_id;
    request.offset = 0U;
    request.len = 0U;
    request.src = RT_NULL;
    request.dst = RT_NULL;

    ret = fee_sched_enqueue_request(FEE_REQ_ROLLBACK, &request);
    if (ret != FEE_E_OK)
    {
        return ret;
    }

    g_fee_ctx.status = FEE_STATUS_BUSY_INTERNAL;
    g_fee_ctx.job_result = FEE_JOB_PENDING;
    return FEE_E_OK;
}

void fee_sched_mainfunction(void)
{
    fee_sched_slot_t slot;
    fee_ret_t ret;
    rt_bool_t has_work = RT_FALSE;

    if (g_fee_ctx.init_state == FEE_INIT_FAILED)
    {
        fee_sched_clear_queue(&g_fee_sched_urgent[0], FEE_CFG_MAX_PENDING_REQUESTS);
        fee_sched_clear_queue(&g_fee_sched_normal[0], FEE_CFG_MAX_PENDING_REQUESTS);
        return;
    }

    if (g_fee_ctx.init_state != FEE_INIT_FULL_READY)
    {
        has_work = fee_sched_has_pending_work();
        if (has_work != RT_FALSE)
        {
            g_fee_ctx.status = FEE_STATUS_BUSY_INTERNAL;
            g_fee_ctx.job_result = FEE_JOB_PENDING;
        }
        return;
    }

    if (fee_sched_queue_pop(&g_fee_sched_urgent[0], FEE_CFG_MAX_PENDING_REQUESTS, &slot) == RT_FALSE)
    {
        if (fee_sched_queue_pop(&g_fee_sched_normal[0], FEE_CFG_MAX_PENDING_REQUESTS, &slot) == RT_FALSE)
        {
            return;
        }
    }

    g_fee_ctx.status = FEE_STATUS_BUSY_INTERNAL;
    g_fee_ctx.job_result = FEE_JOB_PENDING;

    ret = fee_sched_dispatch_one(&slot);
    has_work = fee_sched_has_pending_work();

    if (ret != FEE_E_OK)
    {
        g_fee_ctx.job_result = FEE_JOB_FAILED;
        g_fee_ctx.status = (has_work != RT_FALSE) ? FEE_STATUS_BUSY_INTERNAL : FEE_STATUS_IDLE;
        return;
    }

    g_fee_ctx.job_result = (has_work != RT_FALSE) ? FEE_JOB_PENDING : FEE_JOB_OK;
    g_fee_ctx.status = (has_work != RT_FALSE) ? FEE_STATUS_BUSY_INTERNAL : FEE_STATUS_IDLE;
}

rt_bool_t fee_sched_has_pending_work(void)
{
    if (fee_sched_queue_has_work(&g_fee_sched_urgent[0], FEE_CFG_MAX_PENDING_REQUESTS) != RT_FALSE)
    {
        return RT_TRUE;
    }

    return fee_sched_queue_has_work(&g_fee_sched_normal[0], FEE_CFG_MAX_PENDING_REQUESTS);
}
