/*
 * ===========================================================================================
 *
 *       Filename:  hal_eise.c
 *
 *    Description:  hal impl. of eise.
 *
 *        Version:  Melis3.0
 *         Create:  2020-01-08 14:20:56
 *       Revision:  none
 *       Compiler:
 *
 *         Author:  ganqiuye(ganqiuye@allwinnertech.com)
 *   Organization:  SWC-MPD
 *  Last Modified:  2020-04-02 17:33:33
 *
 * ===========================================================================================
 */


#include <interrupt.h>
#include <hal_queue.h>
#include <sunxi_hal_common.h>
#include "sunxi_hal_eise.h"
#include <init.h>
#include <hal_clk.h>
#include <interrupt.h>
#include <log.h>
#define eise_err(x, arg...) printf("[EISE_ERR] (%s, %d)"x"\n", __func__, __LINE__, ##arg)
#define eise_warn(x, arg...) printf("[EISE_WARN] (%s, %d)"x"\n", __func__, __LINE__, ##arg)
#define eise_print(x, arg...) printf("[EISE] (%s, %d)"x"\n", __func__, __LINE__, ##arg)
#define eise_debug(x, arg...) printf("[EISE_DEBUG] (%s, %d)"x"\n", __func__, __LINE__, ##arg)

typedef enum
{
    EISE_WRITE_REGISTER = 0x100,
    EISE_READ_REGISTER,
    ENABLE_EISE,
    DISABLE_EISE,
    WAIT_EISE_FINISH,
    SET_EISE_FREQ
} hal_eise_transfer_cmd_t;


#define EISE_CLK_HIGH_WATER  (700)
#define EISE_CLK_LOW_WATER   (300)
#define EISE_DEFAULT_RATE    (432000000)
#define EISE_INTERRUPT_ID    (58)
#define EISE_BASE_ADDR       (0x02300000)
#define CCMU_BASE_ADDR       (0x03001000)

static hal_eise_t sHalEise;

static irqreturn_t eise_interrupt(int irq, void* dev_id)
{
    int irq_status;
    hal_eise_t* pHe = &sHalEise;
    hal_writel(0x00, pHe->eise_base_addr + EISE_INTERRUPT_EN);

    irq_status = hal_readl(pHe->eise_base_addr + EISE_INTERRUPT_STATUS);
    if (0x00 != (irq_status & 0x07))
    {
        hal_sem_post(pHe->hal_sem);
    }
/*
    if (0x01 != (irq_status & 0x01))
    {
        pHe->err_cnt++;
    }

    pHe->interrupt_times++;
*/
    return IRQ_HANDLED;
}

static int32_t eise_hal_init(int32_t dev)
{
    hal_eise_t* pHe = &sHalEise;
    pHe->irq_id = EISE_INTERRUPT_ID;
    pHe->eise_base_addr = EISE_BASE_ADDR;
    pHe->ccmu_base_addr = CCMU_BASE_ADDR;
    pHe->pclk = HAL_CLK_PLL_PERI0;
    pHe->mclk = HAL_CLK_PERIPH_EISE;
    hal_clk_set_parent(pHe->mclk, pHe->pclk);
    pHe->hal_sem = hal_sem_create(0);
    if (pHe->hal_sem == NULL)
    {
        eise_err("creating hal semaphore failed\n");
        return SUNXI_HAL_ERROR;
    }
    int ret = request_irq(pHe->irq_id, (irq_handler_t)eise_interrupt, 0, "sunxi_eise", NULL);
    if (ret < 0) {
        eise_err("Request EISE Irq error! return %d\n", ret);
        return SUNXI_HAL_ERROR;
    } else {
        //eise_print("Request EISE Irq success! irq_id = %d, return %d\n", pHe->irq_id, ret);
    }
    enable_irq(pHe->irq_id);
    return SUNXI_HAL_OK;
}

static int32_t eise_hal_uninit(int32_t dev)
{
    hal_eise_t* pHe = &sHalEise;
    hal_clock_disable(pHe->mclk);
    free_irq(pHe->irq_id, NULL);
    eise_print("EISE device has been removed!\n");
    return 0;
}

static int32_t eise_hal_write(int32_t dev, const char *data, uint32_t num)
{
    return 0;
}

static int32_t eise_hal_read(int32_t dev, int *data, uint32_t size)
{
    return 0;
}

static int32_t eise_hal_ctl(int32_t dev, uint32_t cmd, void* arg)
{
    hal_eise_t* pHe = &sHalEise;
    struct eise_register reg;
    long  ret = 0;
    int hal_sem_ret;
    unsigned int rData = 0x5a5a5a5a;
    memcpy(&reg, arg, sizeof(struct eise_register));
    switch (cmd) {
        case EISE_WRITE_REGISTER:
            hal_writel(reg.value, pHe->eise_base_addr + reg.addr);
            return 0;
        case EISE_READ_REGISTER:
            rData = hal_readl(pHe->eise_base_addr + reg.addr);
            return rData;
        case ENABLE_EISE:
            if (hal_clock_enable(pHe->mclk))
                eise_err("[SYS] enable eise_moduleclk failed!\n");
            break;
        case DISABLE_EISE:
            hal_clock_disable(pHe->mclk);
            break;
        case WAIT_EISE_FINISH:
            hal_sem_ret = hal_sem_timedwait(pHe->hal_sem, reg.value);//1 tick = 10ms
            if (hal_sem_ret < 0)
                eise_print("[SYS] wait_event_timeout!\n");
            break;
        case SET_EISE_FREQ:
        {
            unsigned int arg_rate = reg.value;
            if (arg_rate >= EISE_CLK_LOW_WATER &&
                arg_rate <= EISE_CLK_HIGH_WATER) {
                if (!hal_clk_set_rate(pHe->mclk, arg_rate*1000000)) {
                    //eise_err("set clock failed!\n");
                }
                else
                {
                    //eise_print("set clock success!");
                }
            }
            //ret = hal_clk_get_rate(pHe->mclk);
            //eise_print("eise real_fre=%ld\n", ret);
            break;
        }
        default:
        {
            eise_warn("[SYS] do not supprot this ioctrl now!\n");
            break;
        }
    }

    return 0;
}

const sunxi_hal_driver_eise_t sunxi_hal_eise_driver =
{
    .initialize   = eise_hal_init,
    .uninitialize = eise_hal_uninit,
    .send         = eise_hal_write,
    .receive      = eise_hal_read,
    .control      = eise_hal_ctl,
};

int eise_driver_init(void)
{
    __log("eise hal driver init");
    return 0;
}

//late_initcall(eise_driver_init);
