/*
 * ===========================================================================================
 *
 *       Filename:  sunxi_eise.h
 *
 *    Description:  EISE HAL definition.
 *
 *        Version:  Melis3.0
 *         Create:  2020-01-09 11:11:56
 *       Revision:  none
 *       Compiler:
 *
 *         Author:  ganqiuye(ganqiuye@allwinnertech.com)
 *   Organization:  SWC-MPD
 *  Last Modified:  2020-04-02 17:32:52
 *
 * ===========================================================================================
 */

#ifndef SUNXI_HAL_EISE_H
#define SUNXI_HAL_EISE_H
#include <hal_clk.h>
#include "hal_sem.h"
#ifdef __cplusplus
extern "C"
{
#endif

#include "sunxi_hal_common.h"

#define DEVICE_NAME "sunxi_eise"

/* system address */
#define PLL_ISE_CTRL_REG                 (0x00D0)
#define EISE_CLK_REG                     (0x06D0)
#define MBUS_CLK_GATING_REG              (0x0804)
#define EISE_BGR_REG                     (0x06DC)

/* eise register */
#define EISE_CTRL_REG                    (0x00)
#define EISE_IN_SIZE                     (0x28)
#define EISE_OUT_SIZE                    (0x38)
#define EISE_ICFG_REG                    (0x04)
#define EISE_OCFG_REG                    (0x08)
#define EISE_INTERRUPT_EN                (0x0c)
#define EISE_TIME_OUT_NUM                (0x3c)

#define EISE_INTERRUPT_STATUS            (0x10)
#define EISE_ERROR_FLAG                  (0x14)
#define EISE_RESET_REG                   (0x88)


struct eise_register{
  unsigned int addr;
  unsigned int value;
};

typedef struct hal_eise_t{
    unsigned int eise_base_addr;
    unsigned int ccmu_base_addr;
   // unsigned long err_cnt;
    //unsigned long interrupt_times;
    unsigned int irq_id;
    hal_clk_id_t pclk;
    hal_clk_id_t mclk;
    hal_sem_t   hal_sem;
}hal_eise_t;

typedef struct sunxi_hal_driver_eise
{
    int32_t (*initialize)(int32_t dev);

    int32_t (*uninitialize)(int32_t dev);

    int32_t (*send)(int32_t dev, const char *data, uint32_t num);

    int32_t (*receive)(int32_t dev, int *data, uint32_t num);

    int32_t (*control)(int32_t dev, uint32_t control, void* arg);
    sunxi_hal_poll_ops *poll_ops;
} const sunxi_hal_driver_eise_t;

#ifdef __cplusplus
}
#endif

#endif
