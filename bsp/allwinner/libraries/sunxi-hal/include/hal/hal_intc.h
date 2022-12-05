#ifndef __HAL_INTC_H
#define __HAL_INTC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <intc/intc.h>
#include <intc/platform-intc.h>

/* INTC HAL API return status */
typedef enum {
    HAL_INTC_STATUS_OK = 0,
    HAL_INTC_STATUS_FAIL = -1,
} hal_intc_status_t;


hal_intc_status_t hal_intc_init(uint32_t irq_no);


#ifdef __cplusplus
}
#endif

#endif /* __HAL_INTC_H */
