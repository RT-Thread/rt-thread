#include "hal_boot2.h"
#include "hal_flash.h"
#include "bl808_ef_ctrl.h"
#include "bl808_ef_cfg.h"
#include "bl808_hbn.h"
#include "bl808_glb.h"
#include "bl808_xip_sflash.h"
#include "bl808_tzc_sec.h"
#include "hal_gpio.h"
#include "hal_sec_hash.h"
#include "bl808_sec_eng.h"
#include "softcrc.h"
#include "bl808_psram_uhs.h"
#include "bl808_romapi_patch.h"

extern sec_hash_handle_t hash_handle;

/**
 * @brief boot2 init system clock
 *
 * @param None
 * @return None
 */
void hal_boot2_init_clock(void)
{
    extern void system_mtimer_clock_init(void);
    extern void peripheral_clock_init(void);

    system_mtimer_clock_init();
    peripheral_clock_init();
}

/**
 * @brief boot2 custom
 *
 * @param custom_param
 * @return uint32_t
 */
uint32_t hal_boot2_custom(void *custom_param)
{
    if (((g_efuse_cfg.dev_info & HAL_BOOT2_PSRAM_INFO_MASK) >> HAL_BOOT2_PSRAM_INFO_POS) != 0) {
        GLB_Config_UHS_PLL(GLB_XTAL_40M, uhsPllCfg_2000M);
        Psram_UHS_x16_Init(2000);
        Tzc_Sec_PSRAMA_Access_Release();

        /* Flush i-cache in case branch prediction logic is wrong when
       psram is not inited by hal_boot2_custom but cpu has already prefetch psram */
        __ISB();
    }
    return 0;
}

/**
 * @brief get efuse Boot2 config
 *
 * @param g_efuse_cfg
 * @param
 * @param
 * @return None
 */
void hal_boot2_get_efuse_cfg(boot2_efuse_hw_config *efuse_cfg)
{
    uint32_t timeout_cnt = 0;
    uint32_t i = 0;
    struct boot_efuse_sw_cfg0_t sw_cfg0;

    /* #define EF_CTRL_LOAD_BEFORE_READ_R0 in ef_ctrl to speed up */
    EF_Ctrl_Load_Efuse_R0();
    EF_Ctrl_Load_Efuse_R1();

    while (EF_Ctrl_AutoLoad_Done() != SET && timeout_cnt < 80) {
        arch_delay_us(1);
        timeout_cnt++;
    }

    /* get hw cfg (signature and aes type) */
    EF_Ctrl_Read_Secure_Boot((EF_Ctrl_SF_AES_Type *)efuse_cfg->encrypted);

    for (i = 0; i < HAL_BOOT2_CPU_GROUP_MAX; i++) {
        if (efuse_cfg->encrypted[i] == EF_CTRL_SF_AES_192) {
            efuse_cfg->encrypted[i] = SF_CTRL_AES_192BITS + 1;
        } else if (efuse_cfg->encrypted[i] == EF_CTRL_SF_AES_256) {
            efuse_cfg->encrypted[i] = SF_CTRL_AES_256BITS + 1;
        }
    }

    /* get sw uasge 0 */
    EF_Ctrl_Read_Sw_Usage(0, (uint32_t *)&sw_cfg0);
    /* get sw uasge 1 */
    //EF_Ctrl_Read_Sw_Usage(1, &sw_cfg1);

    for (i = 0; i < HAL_BOOT2_CPU_GROUP_MAX; i++) {
        efuse_cfg->sign[i] = ((struct boot_efuse_sw_cfg0_t)sw_cfg0).sign_cfg;
    }
    for (i = 1; i < HAL_BOOT2_CPU_GROUP_MAX; i++) {
        efuse_cfg->encrypted[i] = EF_CTRL_SF_AES_NONE;
    }

    efuse_cfg->hbn_check_sign = (uint8_t)(sw_cfg0.hbn_check_sign);
    efuse_cfg->sf_pin_cfg = (uint8_t)(sw_cfg0.sf_pin_cfg);
    efuse_cfg->uart_download_cfg = (uint8_t)(sw_cfg0.uart_download_cfg);
    efuse_cfg->keep_dbg_port_closed = (uint8_t)(sw_cfg0.keep_dbg_port_closed);
    efuse_cfg->boot_pin_cfg = (uint8_t)(sw_cfg0.boot_pin_cfg);

    /* get device info */
    EF_Ctrl_Get_Chip_Info((Efuse_Chip_Info_Type *)&efuse_cfg->dev_info);

    /* get chip id */
    EF_Ctrl_Read_Chip_ID(efuse_cfg->chip_id);

    /* get public key hash */
    EF_Ctrl_Read_AES_Key(0, (uint32_t *)efuse_cfg->pk_hash_cpu0, HAL_BOOT2_PK_HASH_SIZE / 4);
    EF_Ctrl_Read_AES_Key(8, (uint32_t *)efuse_cfg->pk_hash_cpu1, HAL_BOOT2_PK_HASH_SIZE / 4);
}
/**
 * @brief reset sec eng clock
 *
 * @return
 */
void hal_boot2_reset_sec_eng(void)
{
    GLB_AHB_MCU_Software_Reset(GLB_AHB_MCU_SW_SEC_ENG);
    Sec_Eng_Group0_Request_SHA_Access();
    Sec_Eng_Group0_Request_AES_Access();
    Sec_Eng_Group0_Request_Trng_Access();
    Sec_Eng_Trng_Enable();
    GLB_Set_PKA_CLK_Sel(GLB_PKA_CLK_MCU_MUXPLL_160M);
}

/**
 * @brief system soft reset
 *
 * @return
 */
void hal_boot2_sw_system_reset(void)
{
    GLB_SW_System_Reset();
}

/**
 * @brief
 *
 * @param flag
 * @param
 * @param
 * @return
 */
void hal_boot2_set_psmode_status(uint32_t flag)
{
    HBN_Set_Status_Flag(flag);
}

/**
 * @brief
 *
 * @param
 * @param
 * @param
 * @return flag
 */
uint32_t hal_boot2_get_psmode_status(void)
{
    return HBN_Get_Status_Flag();
}

/**
 * @brief
 *
 * @param
 * @param
 * @param
 * @return user define flag
 */
uint32_t hal_boot2_get_user_fw(void)
{
    return BL_RD_WORD(HBN_BASE + HBN_RSV0_OFFSET);
}

/**
 * @brief clr user define flag
 *
 * @param
 * @param
 * @param
 * @return
 */
void hal_boot2_clr_user_fw(void)
{
    uint32_t *p = (uint32_t *)(HBN_BASE + HBN_RSV0_OFFSET);
    *p = 0;
}

/**
 * @brief hal_boot2_sboot_finish
 *
 * @return
 */
void ATTR_TCM_SECTION hal_boot2_sboot_finish(void)
{
    //    uint32_t tmpVal;
    //    if (!g_efuse_cfg.keep_dbg_port_closed) {
    //        /* only after this, JTAG is really open */
    //        tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_TZSRG_CTRL);
    //        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_SBOOT_DONE, 0xf);
    //        BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_TZSRG_CTRL, tmpVal);
    //    }
}

void bflb_boot2_pds_hbn_pad_pn(void)
{
    /* clear pds/hbn ctrl pad pull type */
    PDS_Set_Flash_Pad_Pull_None_Fast((SF_Ctrl_Pin_Select)g_efuse_cfg.sf_pin_cfg);
    HBN_AON_PAD_CFG_Type aonPadCfg = {
        .ctrlEn = ENABLE,
        .inputEn = ENABLE,
        .outputEn = ENABLE,
        .pullCfg = HBN_GPIO_PAD_PULL_NONE,
    };
    HBN_Aon_Pad_Cfg(ENABLE, HBN_AON_PAD_GPIO14, &aonPadCfg);
    HBN_Aon_Pad_Cfg(ENABLE, HBN_AON_PAD_GPIO15, &aonPadCfg);
}

/**
 * @brief hal_boot2_pll_init
 *
 * @return
 */
void hal_boot2_uart_gpio_init(void)
{
    GLB_GPIO_Cfg_Type cfg;

    cfg.pullType = GPIO_PULL_UP;
    cfg.drive = 0;
    cfg.smtCtrl = 1;

    /* ToDo: will crash */
    //bflb_boot2_pds_hbn_pad_pn();

    cfg.gpioPin = GLB_GPIO_PIN_15;
    cfg.gpioFun = GPIO_FUN_UART;
    cfg.gpioMode = GPIO_MODE_INPUT;
    GLB_GPIO_Init(&cfg);

    //GLB_UART_Sig_Swap_Set(GLB_UART_SIG_SWAP_GRP_GPIO12_GPIO23, 0);
    GLB_UART_Fun_Sel(GLB_UART_SIG_3, GLB_UART_SIG_FUN_UART0_RXD);
    GLB_UART_Fun_Sel((GLB_UART_SIG_Type)GLB_UART_SIG_FUN_UART0_RXD, (GLB_UART_SIG_FUN_Type)GLB_UART_SIG_3);

    cfg.gpioPin = GLB_GPIO_PIN_14;
    cfg.gpioFun = GPIO_FUN_UART;
    cfg.gpioMode = GPIO_MODE_OUTPUT;
    GLB_GPIO_Init(&cfg);

    //GLB_UART_Sig_Swap_Set(GLB_UART_SIG_SWAP_GRP_GPIO12_GPIO23, 0);

    GLB_UART_Fun_Sel(GLB_UART_SIG_2, GLB_UART_SIG_FUN_UART0_TXD);
    GLB_UART_Fun_Sel((GLB_UART_SIG_Type)GLB_UART_SIG_FUN_UART0_TXD, (GLB_UART_SIG_FUN_Type)GLB_UART_SIG_2);
}

/**
 * @brief hal_boot2_pll_init
 *
 * @return
 */
void hal_boot2_debug_uart_gpio_init(void)
{
    GLB_GPIO_Cfg_Type cfg;

    cfg.pullType = GPIO_PULL_NONE;
    cfg.drive = 0;
    cfg.smtCtrl = 1;

    /* OTP_BOOTLOG_PIN_CFG() */
    /* 0 -> GPIO39 -> qfn68 */
    /* 1 -> GPIO8  -> qfn88 */
    if (0 == g_efuse_cfg.boot_pin_cfg) {
        cfg.gpioPin = GLB_GPIO_PIN_39;
        cfg.gpioFun = GPIO_FUN_UART;
        cfg.gpioMode = GPIO_MODE_OUTPUT;
        GLB_GPIO_Init(&cfg);

        GLB_UART_Sig_Swap_Set(GLB_UART_SIG_SWAP_GRP_GPIO36_GPIO45, 1);
        GLB_UART_Fun_Sel(GLB_UART_SIG_9, GLB_UART_SIG_FUN_UART1_TXD);
        GLB_UART_Fun_Sel((GLB_UART_SIG_Type)GLB_UART_SIG_FUN_UART1_TXD, (GLB_UART_SIG_FUN_Type)GLB_UART_SIG_9);

    } else {
        cfg.gpioPin = GLB_GPIO_PIN_8;
        cfg.gpioFun = GPIO_FUN_UART;
        cfg.gpioMode = GPIO_MODE_OUTPUT;
        GLB_GPIO_Init(&cfg);

        GLB_UART_Sig_Swap_Set(GLB_UART_SIG_SWAP_GRP_GPIO0_GPIO11, 0);
        GLB_UART_Fun_Sel(GLB_UART_SIG_8, GLB_UART_SIG_FUN_UART1_TXD);
        GLB_UART_Fun_Sel((GLB_UART_SIG_Type)GLB_UART_SIG_FUN_UART1_TXD, (GLB_UART_SIG_FUN_Type)GLB_UART_SIG_8);
    }
}

/**
 * @brief hal_boot2_debug_usb_port_init
 *
 * @return
 */
#if HAL_BOOT2_SUPPORT_USB_IAP
void hal_boot2_debug_usb_port_init(void)
{
}
#endif

/**
 * @brief hal_boot2_debug_uart_gpio_deinit
 *
 * @return
 */
void hal_boot2_debug_uart_gpio_deinit(void)
{
}

/****************************************************************************/ /**
 * @brief  Check bootheader crc
 *
 * @param  data: bootheader data pointer
 *
 * @return boot_error_code type
 *
*******************************************************************************/
static uint32_t hal_boot_check_bootheader(struct hal_bootheader_t *header)
{
    uint32_t crc_pass = 0;
    uint32_t crc;

    if (header->basic_cfg.crc_ignore == 1 && header->crc32 == HAL_BOOT2_DEADBEEF_VAL) {
        //MSG("Crc ignored\r\n");
        crc_pass = 1;
    } else {
        crc = BFLB_Soft_CRC32((uint8_t *)header, sizeof(struct hal_bootheader_t) - sizeof(header->crc32));

        if (header->crc32 == crc) {
            crc_pass = 1;
        }
    }
    return crc_pass;
}

/****************************************************************************/ /**
 * @brief  Check if the input public key is the same as  burned in the efuse
 *
 * @param  g_boot_img_cfg: Boot image config pointer
 * @param  data: Image data pointer
 *
 * @return boot_error_code type
 *
*******************************************************************************/
int32_t hal_boot_parse_bootheader(boot2_image_config *boot_img_cfg, uint8_t *data)
{
    struct hal_bootheader_t *header = (struct hal_bootheader_t *)data;
    uint32_t crc_pass = 0;
    uint32_t i = 0;
    uint32_t *phash = (uint32_t *)header->basic_cfg.hash;

    crc_pass = hal_boot_check_bootheader(header);

    if (!crc_pass) {
        //MSG_ERR("bootheader crc error\r\n");
        //blsp_dump_data((uint8_t *)&crc, 4);
        return 0x0204;
    }

    if (header->basic_cfg.notload_in_bootrom) {
        return 0x0202;
    }

    /* Get which CPU's img it is*/
    for (i = 0; i < HAL_BOOT2_CPU_MAX; i++) {
        if (0 == memcmp((void *)&header->magiccode, HAL_BOOT2_CPU0_MAGIC,
                        sizeof(header->magiccode))) {
            break;
        } else if (0 == memcmp((void *)&header->magiccode, HAL_BOOT2_CPU1_MAGIC,
                               sizeof(header->magiccode))) {
            break;
        }
    }

    if (i == HAL_BOOT2_CPU_MAX) {
        /* No cpu img magic match */
        //MSG_ERR("Magic code error\r\n");
        return 0x0203;
    }

    if (boot_img_cfg == NULL) {
        return 0;
    }

    boot_img_cfg->pk_src = i;
    boot_img_cfg->img_valid = 0;

    arch_memcpy_fast(&boot_img_cfg->basic_cfg, &header->basic_cfg,
                     sizeof(header->basic_cfg));

    /* Check encrypt and sign match*/
    if (g_efuse_cfg.encrypted[i] != boot_img_cfg->basic_cfg.encrypt_type) {
        if (boot_img_cfg->basic_cfg.xts_mode == 0) {
            //("Encrypt not fit\r\n");
            return 0x0205;
        }
    }

    if (g_efuse_cfg.sign[i] != boot_img_cfg->basic_cfg.sign_type) {
        //MSG_ERR("sign not fit\r\n");
        boot_img_cfg->basic_cfg.sign_type = g_efuse_cfg.sign[i];
        return 0x0206;
    }

    if (g_ps_mode == 1 && (!g_efuse_cfg.hbn_check_sign)) {
        /* In HBN Mode, if user select to ignore hash and sign*/
        boot_img_cfg->basic_cfg.hash_ignore = 1;
    } else if ((boot_img_cfg->basic_cfg.hash_ignore == 1 && *phash != HAL_BOOT2_DEADBEEF_VAL) ||
               g_efuse_cfg.sign[i] != 0) {
        /* If signed or user not really want to ignore, hash can't be ignored*/
        boot_img_cfg->basic_cfg.hash_ignore = 0;
    }

    if (g_user_hash_ignored) {
        boot_img_cfg->basic_cfg.hash_ignore = 1;
    }

    if (boot_img_cfg->basic_cfg.img_len_cnt == 0) {
        return 0x0207;
    }

    arch_memcpy_fast(&boot_img_cfg->cpu_cfg, &header->cpu_cfg,
                     sizeof(header->cpu_cfg));
    return 0;
}

void ATTR_TCM_SECTION hal_boot2_clean_cache(void)
{
    L1C_DCache_Clean_Invalid_All();
    L1C_ICache_Invalid_All();
}

BL_Err_Type ATTR_TCM_SECTION hal_boot2_set_cache(uint8_t cont_read, boot2_image_config *boot_img_cfg)
{
    flash_set_cache(cont_read, boot_img_cfg->cpu_cfg[0].cache_enable,
                    boot_img_cfg->cpu_cfg[0].cache_way_dis,
                    boot_img_cfg->basic_cfg.group_image_offset);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get the ram image name and count
 *
 * @param  img_name: ram image name in partition
 * @param  ram_img_cnt: ram image count that support boot from flash
 *
 * @return None
 *
*******************************************************************************/
void hal_boot2_get_ram_img_cnt(char *img_name[], uint32_t *ram_img_cnt)
{
    *ram_img_cnt = 5;
    img_name[0] = "Imgload";
    img_name[1] = "SBI";
    img_name[2] = "Kernel";
    img_name[3] = "Rootfs";
    img_name[4] = "DTB";
}

/****************************************************************************/ /**
 * @brief  get the ram image info
 *
 * @param  data: bootheader information
 * @param  image_offset: ram image offset in flash(from of bootheader)
 * @param  img_len: ram image length
 * @param  hash: pointer to hash pointer
 *
 * @return None
 *
*******************************************************************************/
void hal_boot2_get_img_info(uint8_t *data, uint32_t *image_offset, uint32_t *img_len, uint8_t **hash)
{
    struct hal_bootheader_t *header = (struct hal_bootheader_t *)data;
    uint32_t crc_pass = 0;
    *img_len = 0;
    uint8_t *phash = *hash;
    uint8_t hash_ignore = 1;

    crc_pass = hal_boot_check_bootheader(header);

    if (!crc_pass) {
        return;
    }
    if (0 != memcmp((void *)&header->magiccode, HAL_BOOT2_CPU0_MAGIC, sizeof(header->magiccode)) &&
        0 != memcmp((void *)&header->magiccode, HAL_BOOT2_CPU1_MAGIC, sizeof(header->magiccode))) {
        return;
    }

    /* for ram image, it always download in iot tab, so
       it share the same group with core 0 but use different image offset and
       boot entry */
    *image_offset = 4096 * 1; //bootheader->basic_cfg.group_image_offset;
    *img_len = header->basic_cfg.img_len_cnt;

    if (g_ps_mode == 1 && (!g_efuse_cfg.hbn_check_sign)) {
        /* In HBN Mode, if user select to ignore hash and sign*/
        hash_ignore = 1;
    } else if ((header->basic_cfg.hash_ignore == 1 && header->basic_cfg.hash[0] != HAL_BOOT2_DEADBEEF_VAL) ||
               g_efuse_cfg.sign[0] != 0) {
        /* If signed or user not really want to ignore, hash can't be ignored*/
        hash_ignore = 0;
    }

    if (hash_ignore == 1) {
        *hash = NULL;
    } else {
        memcpy(phash, header->basic_cfg.hash, sizeof(header->basic_cfg.hash));
    }
}

/****************************************************************************/ /**
 * @brief  release other cpu to boot up
 *
 * @param  core: core number
 * @param  boot_addr: boot address
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION hal_boot2_release_cpu(uint32_t core, uint32_t boot_addr)
{
    GLB_Set_CPU_Reset_Address(core, boot_addr);
    GLB_Release_CPU(core);
}

/****************************************************************************/ /**
 * @brief  get xip address according to flash addr
 *
 * @param  flash_addr: flash address
 *
 * @return XIP Address
 *
*******************************************************************************/
uint32_t hal_boot2_get_xip_addr(uint32_t flash_addr)
{
    uint32_t img_offset = SF_Ctrl_Get_Flash_Image_Offset(0, SF_CTRL_FLASH_BANK0);
    if (flash_addr >= img_offset) {
        return BL808_FLASH_XIP_BASE + (flash_addr - img_offset);
    } else {
        return 0;
    }
}

/****************************************************************************/ /**
 * @brief  get if multi-group
 *
 * @param  None
 *
 * @return 1 for multi-group 0 for not
 *
*******************************************************************************/
uint32_t hal_boot2_get_grp_count(void)
{
    return 2;
}

/****************************************************************************/ /**
 * @brief  get cpu count
 *
 * @param  None
 *
 * @return 1 for multi-group 0 for not
 *
*******************************************************************************/
uint32_t hal_boot2_get_cpu_count(void)
{
    return 3;
}

/****************************************************************************/ /**
 * @brief  get cpu count
 *
 * @param  None
 *
 * @return 1 for multi-group 0 for not
 *
*******************************************************************************/
uint32_t ATTR_TCM_SECTION hal_boot2_get_feature_flag(void)
{
    return HAL_BOOT2_MP_FLAG;
}

/****************************************************************************/ /**
 * @brief  get boot header offset
 *
 * @param  None
 *
 * @return bootheader offset
 *
*******************************************************************************/
uint32_t hal_boot2_get_bootheader_offset(void)
{
    return 0x0;
}