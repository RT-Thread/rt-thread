#ifndef CUSTOM_FEE_API_H
#define CUSTOM_FEE_API_H

#include <stdint.h>
#include "rtdef.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t fee_ret_t;

#define FEE_E_OK        ((fee_ret_t)0U)
#define FEE_E_NOT_OK    ((fee_ret_t)1U)
#define FEE_E_BUSY      ((fee_ret_t)2U)
#define FEE_E_UNINIT    ((fee_ret_t)3U)
#define FEE_E_PARAM     ((fee_ret_t)4U)

typedef enum
{
    FEE_STATUS_UNINIT = 0,
    FEE_STATUS_IDLE,
    FEE_STATUS_BUSY,
    FEE_STATUS_BUSY_INTERNAL
} fee_status_t;

typedef enum
{
    FEE_JOB_NONE = 0,
    FEE_JOB_OK,
    FEE_JOB_PENDING,
    FEE_JOB_FAILED,
    FEE_JOB_CANCELED,
    FEE_JOB_INCONSISTENT
} fee_job_result_t;

typedef enum
{
    FEE_INIT_RESET = 0,
    FEE_INIT_META_SCAN,
    FEE_INIT_CKPT_READY,
    FEE_INIT_TAIL_SCAN,
    FEE_INIT_FULL_READY,
    FEE_INIT_DEGRADED,
    FEE_INIT_FAILED
} fee_init_state_t;

typedef enum
{
    FEE_BLOCK_STATUS_EMPTY = 0,
    FEE_BLOCK_STATUS_VALID,
    FEE_BLOCK_STATUS_INVALIDATED,
    FEE_BLOCK_STATUS_INCONSISTENT
} fee_block_status_t;

fee_ret_t fee_init(void);
fee_ret_t fee_read(uint16_t block_id, uint16_t offset, uint8_t *dst, uint16_t len);
fee_ret_t fee_write(uint16_t block_id, const uint8_t *src, uint16_t len);
fee_ret_t fee_invalidate(uint16_t block_id);
fee_ret_t fee_get_status(uint16_t block_id, fee_block_status_t *status);
fee_ret_t fee_rollback(uint16_t block_id);
void fee_mainfunction(void);

fee_status_t fee_get_memif_status(void);
fee_job_result_t fee_get_job_result(void);
fee_init_state_t fee_get_init_state(void);

#ifdef __cplusplus
}
#endif

#endif
