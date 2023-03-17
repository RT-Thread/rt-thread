
#if defined(BL616)
#include "bl616_memorymap.h"
#include "bl616_glb.h"
#include "bl616_ef_cfg.h"
#elif defined(BL606P)
#include "bl606p_memorymap.h"
#include "bl606p_glb.h"
#elif defined(BL808)
#include "bl808_memorymap.h"
#include "bl808_glb.h"
#elif defined(BL702L)
#include "bl702l_glb.h"
#include "bl702l_ef_ctrl.h"
#elif defined(BL602)
#include "bl602_glb.h"
#include "bl602_sflash_ext.h"
#include "bl602_xip_sflash_ext.h"
#include "bl602_sf_cfg_ext.h"
#elif defined(BL702)
#include "bl702_glb.h"
#include "bl702_xip_sflash_ext.h"
#include "bl702_sf_cfg_ext.h"
#endif
#include "bflb_xip_sflash.h"
#include "bflb_sf_cfg.h"
#include "bflb_flash.h"
#include "hardware/sf_ctrl_reg.h"

#if defined(BL616)
static uint32_t flash1_size = 4 * 1024 * 1024;
static uint32_t flash2_size = 2 * 1024 * 1024;
static uint32_t g_jedec_id2 = 0;
#endif
static uint32_t g_jedec_id = 0;
static spi_flash_cfg_type g_flash_cfg = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0xc8,

    .de_burst_wrap_cmd = 0x77,
    .de_burst_wrap_cmd_dmy_clk = 0x3,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .de_burst_wrap_data = 0xF0,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 1,
    .qe_bit = 0x01,
    .qe_write_reg_len = 0x01,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x31,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 0,
    .c_read_mode = 0x20,

    .burst_wrap_cmd = 0x77,
    .burst_wrap_cmd_dmy_clk = 0x3,
    .burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .burst_wrap_data = 0x40,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = 0x11,
    .clk_delay = 0,
    .clk_invert = 0x03,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(BL702L) || defined(BL702) || defined(BL602)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 300,
    .time_e_32k = 1200,
    .time_e_64k = 1200,
    .time_page_pgm = 5,
    .time_ce = 33 * 1000,
    .pd_delay = 20,
    .qe_data = 0,
};
#if defined(BL616)
static spi_flash_cfg_type g_flash2_cfg = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0xc8,

    .de_burst_wrap_cmd = 0x77,
    .de_burst_wrap_cmd_dmy_clk = 0x3,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .de_burst_wrap_data = 0xF0,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 1,
    .qe_bit = 0x01,
    .qe_write_reg_len = 0x01,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x31,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 0,
    .c_read_mode = 0x20,

    .burst_wrap_cmd = 0x77,
    .burst_wrap_cmd_dmy_clk = 0x3,
    .burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .burst_wrap_data = 0x40,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = 0x10,
    .clk_delay = 0,
    .clk_invert = 0x03,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 300,
    .time_e_32k = 1200,
    .time_e_64k = 1200,
    .time_page_pgm = 5,
    .time_ce = 33 * 1000,
    .pd_delay = 20,
    .qe_data = 0,
};

static bflb_efuse_device_info_type deviceInfo;
#endif

#if defined(BL616)
uint32_t bflb_flash2_get_jedec_id(void)
{
    uint32_t jid = 0;

    jid = ((g_jedec_id2 & 0xff) << 16) + (g_jedec_id2 & 0xff00) + ((g_jedec_id2 & 0xff0000) >> 16);
    return jid;
}
#endif

#if defined(BL616) || defined(BL606P) || defined(BL808) || defined(BL702L)
static int flash_get_clock_delay(spi_flash_cfg_type *cfg)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_0_OFFSET);
    /* bit0-3 for clk delay */
    if (regval & SF_CTRL_SF_IF_READ_DLY_EN) {
        cfg->clk_delay = ((regval & SF_CTRL_SF_IF_READ_DLY_N_MASK) >> SF_CTRL_SF_IF_READ_DLY_N_SHIFT) + 1;
    } else {
        cfg->clk_delay = 0;
    }
    cfg->clk_invert = 0;
    /* bit0 for clk invert */
    cfg->clk_invert |= (((regval & SF_CTRL_SF_CLK_OUT_INV_SEL) ? 1 : 0) << 0);
    /* bit1 for rx clk invert */
    cfg->clk_invert |= (((regval & SF_CTRL_SF_CLK_SF_RX_INV_SEL) ? 1 : 0) << 1);

    regval = getreg32(reg_base + SF_CTRL_SF_IF_IO_DLY_1_OFFSET);
    /* bit4-6 for do delay */
    cfg->clk_delay |= (((regval & SF_CTRL_SF_IO_0_DO_DLY_SEL_MASK) >> SF_CTRL_SF_IO_0_DO_DLY_SEL_SHIFT) << 4);
    /* bit2-4 for di delay */
    cfg->clk_invert |= (((regval & SF_CTRL_SF_IO_0_DI_DLY_SEL_MASK) >> SF_CTRL_SF_IO_0_DI_DLY_SEL_SHIFT) << 2);
    /* bit5-7 for oe delay */
    cfg->clk_invert |= (((regval & SF_CTRL_SF_IO_0_OE_DLY_SEL_MASK) >> SF_CTRL_SF_IO_0_OE_DLY_SEL_SHIFT) << 5);

    return 0;
}
#endif

static void ATTR_TCM_SECTION flash_set_qspi_enable(spi_flash_cfg_type *p_flash_cfg)
{
    if ((p_flash_cfg->io_mode & 0x0f) == SF_CTRL_QO_MODE || (p_flash_cfg->io_mode & 0x0f) == SF_CTRL_QIO_MODE) {
        bflb_sflash_qspi_enable(p_flash_cfg);
    }
}

static void ATTR_TCM_SECTION flash_set_l1c_wrap(spi_flash_cfg_type *p_flash_cfg)
{
    if ((p_flash_cfg->io_mode & 0x1f) == SF_CTRL_QIO_MODE) {
        L1C_Set_Wrap(ENABLE);
        bflb_sflash_set_burst_wrap(p_flash_cfg);
    } else {
        L1C_Set_Wrap(DISABLE);
        bflb_sflash_disable_burst_wrap(p_flash_cfg);
    }
}

/**
 * @brief flash_config_init
 *
 * @return int
 */
static int ATTR_TCM_SECTION flash_config_init(spi_flash_cfg_type *p_flash_cfg, uint8_t *jedec_id)
{
    int ret = -1;
    uint8_t is_aes_enable = 0;
    uint32_t jid = 0;
    uint32_t offset = 0;
    uintptr_t flag;

    flag = bflb_irq_save();
    bflb_xip_sflash_opt_enter(&is_aes_enable);
    bflb_xip_sflash_state_save(p_flash_cfg, &offset, 0, 0);
    bflb_sflash_get_jedecid(p_flash_cfg, (uint8_t *)&jid);
    arch_memcpy(jedec_id, (uint8_t *)&jid, 3);
    jid &= 0xFFFFFF;
    g_jedec_id = jid;
    ret = bflb_sf_cfg_get_flash_cfg_need_lock_ext(jid, p_flash_cfg, 0, 0);
    if (ret == 0) {
        p_flash_cfg->mid = (jid & 0xff);
    }

    // p_flash_cfg->io_mode = 0x11;
    // p_flash_cfg->c_read_support = 0x00;

    /* Set flash controler from p_flash_cfg */
#if defined(BL616) || defined(BL606P) || defined(BL808)
    bflb_flash_set_cmds(p_flash_cfg);
#endif
    flash_set_qspi_enable(p_flash_cfg);
    flash_set_l1c_wrap(p_flash_cfg);
#if defined(BL602)
    bflb_xip_sflash_state_restore_ext(p_flash_cfg, offset, 0, 0);
#else
    bflb_xip_sflash_state_restore(p_flash_cfg, offset, 0, 0);
#endif
    bflb_xip_sflash_opt_exit(is_aes_enable);
    bflb_irq_restore(flag);

    return ret;
}

#if defined(BL616)
/**
 * @brief flash2 init
 *
 * @return int
 */
static int ATTR_TCM_SECTION flash2_init(void)
{
    int stat = -1;
    uint32_t ret = 0;
    uint32_t jid = 0;

    struct sf_ctrl_bank2_cfg sf_bank2_cfg;
    struct sf_ctrl_cmds_cfg cmds_cfg;

    sf_bank2_cfg.sbus2_select = 1;
    sf_bank2_cfg.bank2_rx_clk_invert_src = 0;
    sf_bank2_cfg.bank2_rx_clk_invert_sel = 0;
    sf_bank2_cfg.bank2_delay_src = 0;
    sf_bank2_cfg.bank2_clk_delay = 1;
    sf_bank2_cfg.do_delay = 0;
    sf_bank2_cfg.di_delay = 0;
    sf_bank2_cfg.oe_delay = 0;
    sf_bank2_cfg.remap = SF_CTRL_REMAP_4MB;
    sf_bank2_cfg.remap_lock = 1;

    cmds_cfg.ack_latency = 1;
    cmds_cfg.cmds_core_en = 1;
    cmds_cfg.cmds_en = 1;
    cmds_cfg.cmds_wrap_mode = 1;
    cmds_cfg.cmds_wrap_len = SF_CTRL_WRAP_LEN_4096;

    if (deviceInfo.memoryInfo == 0) {
        /* memoryInfo==0, external flash */
        flash1_size = 64 * 1024 * 1024;
        flash2_size = 0;
    } else if (deviceInfo.memoryInfo == 1) {
        flash1_size = 2 * 1024 * 1024;
        flash2_size = 0;
    } else if (deviceInfo.memoryInfo == 2) {
        flash1_size = 4 * 1024 * 1024;
        flash2_size = 0;
    } else if (deviceInfo.memoryInfo == 3) {
        /* memoryInfo==3, embedded 4MB+2MB flash */
        flash1_size = 4 * 1024 * 1024;
        flash2_size = 2 * 1024 * 1024;
    } else {
        flash1_size = 8 * 1024 * 1024;
        flash2_size = 0;
    }

    if (flash2_size > 0) {
        bflb_sf_cfg_sbus2_flash_init(SF_IO_EMB_SWAP_IO3IO0_AND_SF2, &sf_bank2_cfg);
        bflb_sf_ctrl_sbus2_replace(SF_CTRL_PAD2);
        ret = bflb_sf_cfg_flash_identify_ext(0, SF_IO_EMB_SWAP_IO3IO0_AND_SF2, 0, &g_flash2_cfg, 0, SF_CTRL_FLASH_BANK1);
        if ((ret & BFLB_FLASH_ID_VALID_FLAG) == 0) {
            return -1;
        }
        g_flash2_cfg.io_mode = 0x11;
        g_flash2_cfg.c_read_support = 0;
        g_flash2_cfg.c_read_mode = 0xff;
        bflb_sflash_get_jedecid(&g_flash2_cfg, (uint8_t *)&jid);
        jid &= 0xFFFFFF;
        g_jedec_id2 = jid;

        bflb_sf_ctrl_cmds_set(&cmds_cfg, SF_CTRL_FLASH_BANK1);
        stat = bflb_sflash_xip_read_enable(&g_flash2_cfg, (g_flash2_cfg.io_mode & 0xf), 0, SF_CTRL_FLASH_BANK1);
        if (0 != stat) {
            return -1;
        }
        bflb_sf_ctrl_sbus2_revoke_replace();
    }

    return 0;
}
#endif

/**
 * @brief multi flash adapter
 *
 * @return int
 */
int ATTR_TCM_SECTION bflb_flash_init(void)
{
    int ret = -1;
    uint32_t jedec_id = 0;
#if defined(BL602) || defined(BL702)
    uint8_t clk_delay = 1;
    uint8_t clk_invert = 1;
    uintptr_t flag;
#endif

#if defined(BL616)
    bflb_ef_ctrl_get_device_info(&deviceInfo);
#endif

#if defined(BL602) || defined(BL702)
    flag = bflb_irq_save();
#if defined(BL602)
    bflb_sflash_cache_flush();
#else
    L1C_Cache_Flush();
#endif
    bflb_sf_cfg_get_flash_cfg_need_lock_ext(jedec_id, &g_flash_cfg, 0, 0);
#if defined(BL602)
    bflb_sflash_cache_flush();
#else
    L1C_Cache_Flush();
#endif
    bflb_irq_restore(flag);
    if (g_flash_cfg.mid != 0xff && g_flash_cfg.mid != 0x00) {
        return 0;
    }
    clk_delay = g_flash_cfg.clk_delay;
    clk_invert = g_flash_cfg.clk_invert;
    g_flash_cfg.io_mode &= 0x0f;

    ret = flash_config_init(&g_flash_cfg, (uint8_t *)&jedec_id);

    g_flash_cfg.clk_delay = clk_delay;
    g_flash_cfg.clk_invert = clk_invert;
#else
    jedec_id = GLB_Get_Flash_Id_Value();
    if (jedec_id != 0) {
        ret = bflb_sf_cfg_get_flash_cfg_need_lock_ext(jedec_id, &g_flash_cfg, 0, 0);
        if (ret == 0) {
            g_jedec_id = jedec_id;
            g_flash_cfg.io_mode &= 0x0f;
            flash_get_clock_delay(&g_flash_cfg);
#if defined(BL616)
            flash2_init();
#endif
            return 0;
        }
    }

    g_flash_cfg.io_mode &= 0x0f;
    ret = flash_config_init(&g_flash_cfg, (uint8_t *)&jedec_id);

    g_flash_cfg.io_mode &= 0x0f;
    flash_get_clock_delay(&g_flash_cfg);
    GLB_Set_Flash_Id_Value(g_jedec_id);
#endif

#if defined(BL616)
    flash2_init();
#endif

    return ret;
}

#if defined(BL616) || defined(BL606P) || defined(BL808)
void ATTR_TCM_SECTION bflb_flash_set_cmds(spi_flash_cfg_type *p_flash_cfg)
{
    struct sf_ctrl_cmds_cfg cmds_cfg;

    cmds_cfg.ack_latency = 1;
    cmds_cfg.cmds_core_en = 1;
    cmds_cfg.cmds_en = 1;
    cmds_cfg.cmds_wrap_mode = 1;
    cmds_cfg.cmds_wrap_len = 9;

    if ((p_flash_cfg->io_mode & 0x1f) == SF_CTRL_QIO_MODE) {
        cmds_cfg.cmds_wrap_mode = 2;
        cmds_cfg.cmds_wrap_len = 2;
    }
    bflb_sf_ctrl_cmds_set(&cmds_cfg, 0);
}
#endif

uint32_t bflb_flash_get_jedec_id(void)
{
    uint32_t jid = 0;

    jid = ((g_jedec_id & 0xff) << 16) + (g_jedec_id & 0xff00) + ((g_jedec_id & 0xff0000) >> 16);
    return jid;
}

void bflb_flash_get_cfg(uint8_t **cfg_addr, uint32_t *len)
{
    *cfg_addr = (uint8_t *)&g_flash_cfg;
    *len = sizeof(spi_flash_cfg_type);
}

void ATTR_TCM_SECTION bflb_flash_set_iomode(uint8_t iomode)
{
    uintptr_t flag = 0;
    uint8_t is_aes_enable = 0;
    uint32_t offset = 0;

    flag = bflb_irq_save();
    bflb_xip_sflash_opt_enter(&is_aes_enable);
    bflb_xip_sflash_state_save(&g_flash_cfg, &offset, 0, 0);

    g_flash_cfg.io_mode &= ~0x1f;
    if (iomode&4) {
        g_flash_cfg.io_mode |= iomode;
    } else {
        g_flash_cfg.io_mode |= 0x10;
        g_flash_cfg.io_mode |= iomode;
    }

#if defined(BL616) || defined(BL606P) || defined(BL808)
    bflb_flash_set_cmds(&g_flash_cfg);
#endif
    flash_set_qspi_enable(&g_flash_cfg);
    flash_set_l1c_wrap(&g_flash_cfg);
#if defined(BL602)
    bflb_xip_sflash_state_restore_ext(&g_flash_cfg, offset, 0, 0);
#else
    bflb_xip_sflash_state_restore(&g_flash_cfg, offset, 0, 0);
#endif
    bflb_xip_sflash_opt_exit(is_aes_enable);
    bflb_irq_restore(flag);
}

ATTR_TCM_SECTION uint32_t bflb_flash_get_image_offset(void)
{
    return bflb_sf_ctrl_get_flash_image_offset(0, 0);
}

/**
 * @brief erase flash via sbus
 *
 * @param flash absolute startaddr
 * @param flash absolute endaddr
 * @return int
 */
int ATTR_TCM_SECTION bflb_flash_erase(uint32_t startaddr, uint32_t len)
{
    int stat = -1;
    uintptr_t flag;

#if defined(BL616)
    if ((startaddr + len) > (flash1_size + flash2_size)) {
        return -ENOMEM;
    } else if ((startaddr + len) <= flash1_size) {
        flag = bflb_irq_save();
        stat = bflb_xip_sflash_erase_need_lock(&g_flash_cfg, startaddr, len, 0, 0);
        bflb_irq_restore(flag);
    } else if (startaddr >= flash1_size) {
        bflb_sf_ctrl_sbus2_replace(SF_CTRL_PAD2);
        stat = bflb_sflash_erase(&g_flash2_cfg, startaddr, startaddr + len - 1);
        bflb_sf_ctrl_sbus2_revoke_replace();
    } else {
        flag = bflb_irq_save();
        stat = bflb_xip_sflash_erase_need_lock(&g_flash_cfg, startaddr, flash1_size - startaddr, 0, 0);
        bflb_irq_restore(flag);
        if (stat != 0) {
            return stat;
        }
        bflb_sf_ctrl_sbus2_replace(SF_CTRL_PAD2);
        stat = bflb_sflash_erase(&g_flash2_cfg, flash1_size, startaddr + len - flash1_size - 1);
        bflb_sf_ctrl_sbus2_revoke_replace();
    }
#else
    if (startaddr >= BFLB_FLASH_XIP_END - BFLB_FLASH_XIP_BASE) {
        return -ENOMEM;
    }

    flag = bflb_irq_save();
#if defined(BL602)
    stat = bflb_xip_sflash_erase_need_lock_ext(&g_flash_cfg, startaddr, startaddr+len-1, 0, 0);
#elif defined(BL702)
    uint8_t aes_enabled = 0;
    bflb_xip_sflash_opt_enter(&aes_enabled);
    stat = bflb_xip_sflash_erase_need_lock(&g_flash_cfg, startaddr, len, 0, 0);
    bflb_xip_sflash_opt_exit(aes_enabled);
#else
    stat = bflb_xip_sflash_erase_need_lock(&g_flash_cfg, startaddr, len, 0, 0);
#endif
    bflb_irq_restore(flag);
#endif

    return stat;
}

/**
 * @brief write flash data via sbus
 *
 * @param flash absolute addr
 * @param data
 * @param len
 * @return int
 */
int ATTR_TCM_SECTION bflb_flash_write(uint32_t addr, uint8_t *data, uint32_t len)
{
    int stat = -1;
    uintptr_t flag;

#if defined(BL616)
    if ((addr + len) > (flash1_size + flash2_size)) {
        return -ENOMEM;
    } else if ((addr + len) <= flash1_size) {
        flag = bflb_irq_save();
        stat = bflb_xip_sflash_write_need_lock(&g_flash_cfg, addr, data, len, 0, 0);
        bflb_irq_restore(flag);
    } else if (addr >= flash1_size) {
        bflb_sf_ctrl_sbus2_replace(SF_CTRL_PAD2);
        stat = bflb_sflash_program(&g_flash2_cfg, SF_CTRL_DO_MODE, addr, data, len);
        bflb_sf_ctrl_sbus2_revoke_replace();
    } else {
        flag = bflb_irq_save();
        stat = bflb_xip_sflash_write_need_lock(&g_flash_cfg, addr, data, flash1_size - addr, 0, 0);
        bflb_irq_restore(flag);
        if (stat != 0) {
            return stat;
        }
        bflb_sf_ctrl_sbus2_replace(SF_CTRL_PAD2);
        stat = bflb_sflash_program(&g_flash2_cfg, SF_CTRL_DO_MODE, flash1_size, data + (flash1_size - addr), addr + len - flash1_size);
        bflb_sf_ctrl_sbus2_revoke_replace();
    }
#else
    if (addr >= BFLB_FLASH_XIP_END - BFLB_FLASH_XIP_BASE) {
        return -ENOMEM;
    }

    flag = bflb_irq_save();
#if defined(BL602)
    stat = bflb_xip_sflash_write_need_lock_ext(&g_flash_cfg, addr, data, len, 0, 0);
#elif defined(BL702)
    uint8_t aes_enabled = 0;
    bflb_xip_sflash_opt_enter(&aes_enabled);
    stat = bflb_xip_sflash_write_need_lock(&g_flash_cfg, addr, data, len, 0, 0);
    bflb_xip_sflash_opt_exit(aes_enabled);
#else
    stat = bflb_xip_sflash_write_need_lock(&g_flash_cfg, addr, data, len, 0, 0);
#endif
    bflb_irq_restore(flag);
#endif

    return stat;
}

/**
 * @brief read flash data via sbus
 *
 * @param flash absolute addr
 * @param data
 * @param len
 * @return int
 */
int ATTR_TCM_SECTION bflb_flash_read(uint32_t addr, uint8_t *data, uint32_t len)
{
    int stat = -1;
    uintptr_t flag;

#if defined(BL616)
    if ((addr + len) > (flash1_size + flash2_size)) {
        return -ENOMEM;
    } else if ((addr + len) <= flash1_size) {
        flag = bflb_irq_save();
        stat = bflb_xip_sflash_read_need_lock(&g_flash_cfg, addr, data, len, 0, 0);
        bflb_irq_restore(flag);
    } else if (addr >= flash1_size) {
        bflb_sf_ctrl_sbus2_replace(SF_CTRL_PAD2);
        stat = bflb_sflash_read(&g_flash2_cfg, SF_CTRL_DO_MODE, 0, addr, data, len);
        bflb_sf_ctrl_sbus2_revoke_replace();
    } else {
        flag = bflb_irq_save();
        stat = bflb_xip_sflash_read_need_lock(&g_flash_cfg, addr, data, flash1_size - addr, 0, 0);
        bflb_irq_restore(flag);
        if (stat != 0) {
            return stat;
        }
        bflb_sf_ctrl_sbus2_replace(SF_CTRL_PAD2);
        stat = bflb_sflash_read(&g_flash2_cfg, SF_CTRL_DO_MODE, 0, flash1_size, data + (flash1_size - addr), addr + len - flash1_size);
        bflb_sf_ctrl_sbus2_revoke_replace();
    }
#else
    if (addr >= BFLB_FLASH_XIP_END - BFLB_FLASH_XIP_BASE) {
        return -ENOMEM;
    }

    flag = bflb_irq_save();
#if defined(BL602)
    stat = bflb_xip_sflash_read_need_lock_ext(&g_flash_cfg, addr, data, len, 0, 0);
#elif defined(BL702)
    uint8_t aes_enabled = 0;
    bflb_xip_sflash_opt_enter(&aes_enabled);
    stat = bflb_xip_sflash_read_need_lock(&g_flash_cfg, addr, data, len, 0, 0);
    bflb_xip_sflash_opt_exit(aes_enabled);
#else
    stat = bflb_xip_sflash_read_need_lock(&g_flash_cfg, addr, data, len, 0, 0);
#endif
    bflb_irq_restore(flag);
#endif

    return stat;
}

int ATTR_TCM_SECTION bflb_flash_set_cache(uint8_t cont_read, uint8_t cache_enable, uint8_t cache_way_disable, uint32_t flash_offset)
{
    uint8_t is_aes_enable = 0;
    uint32_t tmp[1];
    int stat;

    bflb_sf_ctrl_set_owner(SF_CTRL_OWNER_SAHB);

    bflb_xip_sflash_opt_enter(&is_aes_enable);
    /* To make it simple, exit cont read anyway */
    bflb_sflash_reset_continue_read(&g_flash_cfg);

    if (g_flash_cfg.c_read_support == 0) {
        cont_read = 0;
    }

    if (cont_read == 1) {
        stat = bflb_sflash_read(&g_flash_cfg, g_flash_cfg.io_mode & 0xf, 1, 0x00000000, (uint8_t *)tmp, sizeof(tmp));

        if (0 != stat) {
            bflb_xip_sflash_opt_exit(is_aes_enable);
            return -1;
        }
    }

#if defined(BL602) || defined(BL702)
#if defined(BL602)
    bflb_sflash_cache_enable_set(0xf);
#else
    L1C_Cache_Enable_Set(0xf);
#endif

    if (cache_enable) {
        bflb_sf_ctrl_set_flash_image_offset(flash_offset, 0, 0);
        bflb_sflash_xip_read_enable(&g_flash_cfg, g_flash_cfg.io_mode & 0xf, cont_read, 0);
    }
#if defined(BL602)
    bflb_sflash_cache_enable_set(cache_way_disable);
#else
    L1C_Cache_Enable_Set(cache_way_disable);
#endif
#else
    bflb_sf_ctrl_set_flash_image_offset(flash_offset, 0, 0);
    bflb_sflash_xip_read_enable(&g_flash_cfg, g_flash_cfg.io_mode & 0xf, cont_read, 0);
#endif

    bflb_xip_sflash_opt_exit(is_aes_enable);

    return 0;
}

void bflb_flash_aes_init(struct bflb_flash_aes_config_s *config)
{
    uint8_t hw_key_enable = 0;

    if (config->key == NULL) {
        hw_key_enable = 1;
    }

    bflb_sf_ctrl_aes_set_key_be(config->region, (uint8_t *)config->key, config->keybits);
    bflb_sf_ctrl_aes_set_iv_be(config->region, (uint8_t *)config->iv, config->start_addr);
    bflb_sf_ctrl_aes_set_region(config->region, config->region_enable, hw_key_enable, config->start_addr, config->end_addr - 1, config->lock_enable);
}

void bflb_flash_aes_enable(void)
{
    bflb_sf_ctrl_aes_enable();
}

void bflb_flash_aes_disable(void)
{
    bflb_sf_ctrl_aes_disable();
}