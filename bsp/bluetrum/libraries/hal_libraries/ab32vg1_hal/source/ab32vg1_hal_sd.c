#include "ab32vg1_hal.h"

#ifdef HAL_SD_MODULE_ENABLED

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

uint8_t sysclk_update_baud(uint8_t baud);

void sdio_setbaud(hal_sfr_t sdiox, uint8_t baud)
{
    sdiox[SDxBAUD] = sysclk_update_baud(baud);
}

void sdio_init(hal_sfr_t sdiox, sdio_init_t init)
{
    sdiox[SDxCON] = 0;

    hal_udelay(20);
    sdiox[SDxCON] |= BIT(0);                 /* SD control enable */
    sdio_setbaud(sdiox, init->clock_div);   /* Set clock */
    if (init->clock_power_save == SDMMC_CLOCK_POWER_SAVE_DISABLE) {
        sdiox[SDxCON] |= BIT(3);                 /* Keep clock output */
    } else {
        sdiox[SDxCON] &= ~BIT(3);                 /* Keep clock output */
    }
    sdiox[SDxCON] |= BIT(5);                 /* Data interrupt enable */

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
    if (sdiox[SDxCON] & BIT(12)) {
        sdiox[SDxCPND] = BIT(12);
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
    return !(sdiox[SDxCON] & BIT(15));
}

bool sdio_send_cmd(hal_sfr_t sdiox, uint32_t cmd, uint32_t arg, uint8_t *abend)
{
    uint32_t time_out = (cmd & CBUSY) ? RSP_BUSY_TIMEOUT : RSP_TIMEOUT;
    sdiox[SDxARG3] = arg;
    sdiox[SDxCMD] = cmd;

    while (sdio_check_finish(sdiox) == false) {
        if (--time_out == 0) {
            HAL_LOG("cmd time out\n");
            if (abend != HAL_NULL) {
                *abend = 1;
            }
            return false;
        }
    }

    return sdio_check_rsp(sdiox);
}

uint8_t sdio_get_cmd_rsp(hal_sfr_t sdiox)
{
    return sdiox[SDxCMD];
}

uint32_t sdio_get_rsp(hal_sfr_t sdiox, uint32_t rsp_reg)
{
    return sdiox[rsp_reg];
}

void sdio_read_kick(hal_sfr_t sdiox, void* buf)
{
    sdiox[SDxDMAADR] = DMA_ADR(buf);
    sdiox[SDxDMACNT] = 512;
}

void sdio_write_kick(hal_sfr_t sdiox, void* buf)
{
    sdiox[SDxDMAADR] = DMA_ADR(buf);
    sdiox[SDxDMACNT] = BIT(18) | BIT(17) | BIT(16) | 512;
}

bool sdio_isbusy(hal_sfr_t sdiox)
{
    return false;
}

bool sdmmc_cmd_go_idle_state(sd_handle_t hsd)
{
    return sdio_send_cmd(hsd->instance, 0 | RSP_NO, hsd->sdcard.rca, &(hsd->sdcard.abend));
}

bool sdmmc_cmd_send_if_cond(sd_handle_t hsd)
{
    return sdio_send_cmd(hsd->instance, 8 | RSP_7, SDMMC_CHECK_PATTERM, &(hsd->sdcard.abend));
}

bool sdmmc_cmd_all_send_cid(sd_handle_t hsd)
{
    return sdio_send_cmd(hsd->instance, 2 | RSP_2, 0, &(hsd->sdcard.abend));
}

void sdmmc_cmd_set_rel_addr(sd_handle_t hsd)
{
    hal_sfr_t sdiox = hsd->instance;

    if (hsd->sdcard.type == CARD_MMC) {
        hsd->sdcard.rca = 0x00010000;
        sdio_send_cmd(sdiox, 3 | RSP_1, hsd->sdcard.rca, &(hsd->sdcard.abend));
    } else {
        sdio_send_cmd(sdiox, 3 | RSP_6, 0, &(hsd->sdcard.abend));
        hsd->sdcard.rca = sdio_get_rsp(sdiox, SDxARG3) & 0xffff0000;
    }
}

void sdmmc_cmd_send_csd(sd_handle_t hsd)
{
    hal_sfr_t sdiox = hsd->instance;

    sdio_send_cmd(sdiox, 9 | RSP_2, hsd->sdcard.rca, &(hsd->sdcard.abend));
    if (hsd->sdcard.type == CARD_MMC) {
        //
    } else {
        if (hsd->sdcard.flag_sdhc == 1) {
            hsd->sdcard.capacity =   (sdio_get_rsp(sdiox, SDxARG2) << 24) & 0x00ff0000;   /* rspbuf[8] */
            hsd->sdcard.capacity |=  ((sdio_get_rsp(sdiox, SDxARG1) >> 16) & 0x0000ffff); /* rspbuf[9] rspbuf[10] */
            hsd->sdcard.capacity +=  1;
            hsd->sdcard.capacity <<= 10;
        }
    }
    HAL_LOG("sd capacity=%d\n", hsd->sdcard.capacity);
}

void sdmmc_cmd_select_card(sd_handle_t hsd)
{
    sdio_send_cmd(hsd->instance, 7 | RSP_1B, hsd->sdcard.rca, &(hsd->sdcard.abend));
}

bool sdmmc_cmd_read_multiblock(sd_handle_t hsd)
{
    return sdio_send_cmd(hsd->instance, REQ_MULTREAD, hsd->sdcard.rca, &(hsd->sdcard.abend));
}

bool sdmmc_cmd_app(sd_handle_t hsd)
{
    return sdio_send_cmd(hsd->instance, 55 | RSP_1, hsd->sdcard.rca, &(hsd->sdcard.abend));
}

bool sdmmc_acmd_op_cond(sd_handle_t hsd, uint32_t voltage)
{
    /* SEND CMD55 APP_CMD with RCA */
    if (sdmmc_cmd_app(hsd)) {
        /* Send CMD41 */
        if (sdio_send_cmd(hsd->instance, 41 | RSP_3, voltage, &(hsd->sdcard.abend))) {
            return true;
        }
    }
    return false;
}

/*************************  HAL ************************************/

static bool sd_type_identification(sd_handle_t hsd)
{
    uint8_t retry = hsd->cfg.identification_retry;
    while (retry-- > 0)
    {
        /* CMD0: GO_IDLE_STATE */
        sdmmc_cmd_go_idle_state(hsd);

        /* CMD8: SEND_IF_COND: Command available only on V2.0 cards */
        if (sdmmc_cmd_send_if_cond(hsd)) {
            if (sdio_get_cmd_rsp(hsd->instance) == 0x08) {
                hsd->sdcard.type = CARD_V2;
                HAL_LOG("SD 2.0\n");
                return true;
            }
            continue;
        }
        if (sdmmc_acmd_op_cond(hsd, 0x00ff8000)) {
            hsd->sdcard.type = CARD_V1;
            HAL_LOG("SD 1.0\n");
            return true;
        }
        hal_mdelay(20);
    }
    return false;
}

static bool sd_go_ready_try(sd_handle_t hsd)
{
    uint32_t tmp = 0;
    switch (hsd->sdcard.type)
    {
    case CARD_V1:
        sdmmc_acmd_op_cond(hsd, 0x00ff8000);
        break;
    
    case CARD_V2:
        sdmmc_acmd_op_cond(hsd, 0x40ff8000);
        break;
    default:
        break;
    }

    if (0 == (hsd->instance[SDxARG3] & BIT(31))) {
        return false; // no ready
    }

    if ((hsd->sdcard.type == CARD_V2) && (hsd->instance[SDxARG3] & BIT(30))) {
        HAL_LOG("SDHC\n");
        hsd->sdcard.flag_sdhc = 1;
    }

    return true;
}

static bool sd_go_ready(sd_handle_t hsd)
{
    if (hsd->sdcard.type == CARD_INVAL) {
        return false;
    }

    uint8_t retry = hsd->cfg.go_ready_retry;
    while (retry-- > 0)
    {
        if (sd_go_ready_try(hsd) == true) {
            return true;
        }
        hal_mdelay(20);
    }

    return false;
}

static bool sd_poweron(sd_handle_t hsd)
{
    if (sd_type_identification(hsd) == false) {
        HAL_LOG("card invalid\n");
        return false;
    }

    if (sd_go_ready(hsd) == false) {
        HAL_LOG("no ready\n");
        return false;
    }

    return true;
}

static void sd_init_card(sd_handle_t hsd)
{
    /* Send CMD2 ALL_SEND_CID */
    sdmmc_cmd_all_send_cid(hsd);
    /* Send CMD3 SET_REL_ADDR */
    sdmmc_cmd_set_rel_addr(hsd);
    /* Send CMD9 SEND_CSD */
    sdmmc_cmd_send_csd(hsd);
    /* Select the Card */
    sdmmc_cmd_select_card(hsd);

    hsd->init.clock_div         = 3;
    hsd->init.clock_power_save  = SDMMC_CLOCK_POWER_SAVE_ENABLE;

    sdio_init(hsd->instance, &(hsd->init));
}

static bool sd_read_wait(sd_handle_t hsd)
{
    bool ret = false;
    hal_sfr_t sdiox = hsd->instance;



    return ret;
}

static void sd_read_start(sd_handle_t hsd, void *buf, uint32_t lba)
{
    if (hsd->sdcard.rw_state == HAL_SD_RW_STATE_READ) {

    } else {
        if (hsd->sdcard.rw_state == HAL_SD_RW_STATE_WRITE) {

        }
        sdio_read_kick(hsd->instance, buf);
        sdmmc_cmd_read_multiblock(hsd);
    }

    hsd->sdcard.rw_state = HAL_SD_RW_STATE_READ;
    // hsd->sdcard.rw_lba
}

static bool sd_read_try(sd_handle_t hsd, void *buf, uint32_t lba)
{
    HAL_LOG("read: %08x\n", lba);

    if (hsd->sdcard.capacity < lba) {
        lba = hsd->sdcard.capacity - 1;
    }
    sd_read_start(hsd, buf, lba);
    return 0;
}

void hal_sd_initcard(sd_handle_t hsd)
{
    hal_sfr_t sdiox = hsd->instance;

    hsd->init.clock_div         = 119; /* SD clk 240KHz when system clk is 48MHz */
    hsd->init.clock_power_save  = SDMMC_CLOCK_POWER_SAVE_DISABLE;

    sdio_init(sdiox, &(hsd->init));
    sd_poweron(hsd);
    sd_init_card(hsd);
}

WEAK void hal_sd_mspinit(sd_handle_t hsd)
{
}

hal_error_t hal_sd_init(sd_handle_t hsd)
{
    if (hsd == HAL_NULL) {
        return -HAL_ERROR;
    }

    hsd->cfg.go_ready_retry         = 200;
    hsd->cfg.identification_retry   = 5;
    hsd->cfg.rw_init_retry          = 3;
    hsd->cfg.rw_retry               = 3;

    hal_sd_mspinit(hsd);
    hal_sd_initcard(hsd);

    return -HAL_ERROR;
}

void hal_sd_deinit(uint32_t sdx)
{
}

bool hal_sd_read(sd_handle_t hsd, void *buf, uint32_t lba)
{
    uint8_t init_retry = hsd->cfg.rw_init_retry;

    while (init_retry-- > 0)
    {
        uint8_t retry = hsd->cfg.rw_retry;
        while (retry-- > 0)
        {
            if (sd_read_try(hsd, buf, lba)) {
                return true;
            }
        }
        hsd->sdcard.state = HAL_SD_STATE_INVAL; 
        
        hal_mdelay(20);
    }

    return false;
}

#endif
