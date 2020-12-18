#include "ab32vg1_hal.h"
#include "ab32vg1_ll_sdio.h"

#ifdef HAL_SD_MODULE_ENABLED

#include <stdbool.h>

#define HAL_LOG(...)     hal_printf(__VA_ARGS__)

/*************************  LL ************************************/

#define CK8E            BIT(11)             //在命令/数据包后加上8CLK
#define CBUSY           BIT(10)             //Busy Check
#define CLRSP           BIT(9)              //17Byte Long Rsp
#define CRSP            BIT(8)              //Need Rsp

//0x40是CMD中的 01 开头。
#define RSP_NO          (0x40 | CK8E)
#define RSP_1           (0x40 | CRSP | CK8E)                //接收6BYTE
#define RSP_1B          (0x40 | CBUSY | CRSP | CK8E)        //接收6BYTE，并等待BUSY
#define RSP_2           (0x40 | CLRSP | CRSP | CK8E)        //接收17BYTE
#define RSP_3           (0x40 | CRSP | CK8E)                //接收6BYTE
#define RSP_6           (0x40 | CRSP | CK8E)                //接收6BYTE
#define RSP_7           (0x40 | CRSP | CK8E)                //接收6BYTE
#define REQ_MULTREAD    (18 | 0x40 | CRSP)                  //多块读时，不需要增加8CLK。其实，多块读先KICK DATA，这个是无所谓的

#define RSP_BUSY_TIMEOUT            2400000     //大约2s
#define RSP_TIMEOUT                 6000        //大约5ms

enum
{
    SDCON = 0, /* [20]:BUSY [19:17]:CRCS [16]:DCRCE [15]:NRPS [1]:Data bus width [0]:SD enable */
    SDCPND,
    SDBAUD,
    SDCMD,
    SDARG3,
    SDARG2,
    SDARG1,
    SDARG0,
    SDDMAADR,
    SDDMACNT,
};

uint8_t sysclk_update_baud(uint8_t baud);

void sdio_setbaud(hal_sfr_t sdiox, uint8_t baud)
{
    sdiox[SDBAUD] = sysclk_update_baud(baud);
}

void sdio_init(hal_sfr_t sdiox, sdio_init_t init)
{
    /* Set clock */
    sdio_setbaud(sdiox, 199);

    sdiox[SDCON] = 0;
    hal_udelay(20);
    sdiox[SDCON] |= BIT(0);     /* SD control enable */
    sdiox[SDCON] |= BIT(3);     /* Keep clock output */
    sdiox[SDCON] |= BIT(5);     /* Data interrupt enable */
    hal_mdelay(40);
}

/**
 * @brief Check if SDIO command is finished.
 *
 * @param sdiox
 * @return true is finished
 * @return false
 */
bool sdio_check_finish(hal_sfr_t sdiox)
{
    if (sdiox[SDCON] & BIT(12)) {
        sdiox[SDCPND] = BIT(12);
        return true;
    }
    return false;
}

/**
 * @brief Check if SDIO has a response.
 *
 * @param sdiox
 * @return true Have a response.
 * @return false No response.
 */
bool sdio_check_rsp(hal_sfr_t sdiox)
{
    return !(sdiox[SDCON] & BIT(15));
}

bool sdio_send_cmd(hal_sfr_t sdiox, uint32_t cmd, uint32_t arg)
{
    uint32_t time_out = (cmd & CBUSY) ? RSP_BUSY_TIMEOUT : RSP_TIMEOUT;
    sdiox[SDCMD] = cmd;
    sdiox[SDARG3] = arg;

    while (sdio_check_finish(sdiox) == false) {
        if (--time_out == 0) {
            HAL_LOG("cmd time out\n");
            // card.abend = 1;
            return false;
        }
    }

    return sdio_check_rsp(sdiox);
}

uint8_t sdio_get_cmd_rsp(hal_sfr_t sdiox)
{
    return -1;
}

uint32_t sdio_get_rsp(hal_sfr_t sdiox, uint32_t rsp)
{
    return -1;
}

void sdio_read_kick(hal_sfr_t sdiox, void* buf)
{}

void sdio_write_kick(hal_sfr_t sdiox, void* buf)
{}

bool sdio_isbusy(hal_sfr_t sdiox)
{
    return false;
}

void sdmmc_go_idle_state(hal_sfr_t sdiox)
{
    // hal_sfr_t sdiox = hsd->instance;
    sdio_send_cmd(sdiox, 0x00 | RSP_NO, 0);
}

void sdmmc_send_if_cond(hal_sfr_t sdiox)
{
    // hal_sfr_t sdiox = hsd->instance;
    sdio_send_cmd(sdiox, 0x08 | RSP_7, SDMMC_CHECK_PATTERM);
}

/*************************  HAL ************************************/


static void sd_poweron(sd_handle_t hsd)
{
    sdmmc_go_idle_state(hsd->instance);
    sdmmc_send_if_cond(hsd->instance);
    if (hsd->instance[SDCMD] == 0x08) {
        hsd->sdcard.type = CARD_V2;
        HAL_LOG("SD 2.0\n");
    }
}

void hal_sd_initcard(sd_handle_t hsd)
{
    struct sdio_init init = {0};
    hal_sfr_t sdiox = hsd->instance;

    sdio_init(sdiox, &init);
    sd_poweron(hsd);
}

WEAK void hal_sd_mspinit(sd_handle_t hsd)
{
}

hal_error_t hal_sd_init(sd_handle_t hsd)
{
    if (hsd == HAL_NULL) {
        return -HAL_ERROR;
    }

    hal_sd_mspinit(hsd);
    hal_sd_initcard(hsd);

    return -HAL_ERROR;
}

void hal_sd_deinit(uint32_t sdx)
{
}

#endif
