#include "bl702_romdriver.h"

/******************************************************************************/
__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    AON_Power_On_MBG(void)
{
    return RomDriver_AON_Power_On_MBG();
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    AON_Power_Off_MBG(void)
{
    return RomDriver_AON_Power_Off_MBG();
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    AON_Power_On_XTAL(void)
{
    return RomDriver_AON_Power_On_XTAL();
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    AON_Set_Xtal_CapCode(uint8_t capIn, uint8_t capOut)
{
    return RomDriver_AON_Set_Xtal_CapCode(capIn, capOut);
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    AON_Power_Off_XTAL(void)
{
    return RomDriver_AON_Power_Off_XTAL();
}
/******************************************************************************/

/******************************************************************************/
__ALWAYS_INLINE ATTR_TCM_SECTION void ASM_Delay_Us(uint32_t core, uint32_t cnt)
{
    RomDriver_ASM_Delay_Us(core, cnt);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void BL702_Delay_US(uint32_t cnt)
{
    RomDriver_BL702_Delay_US(cnt);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void BL702_Delay_MS(uint32_t cnt)
{
    RomDriver_BL702_Delay_MS(cnt);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void *BL702_MemCpy(void *dst, const void *src, uint32_t n)
{
    return RomDriver_BL702_MemCpy(dst, src, n);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    uint32_t *
    BL702_MemCpy4(uint32_t *dst, const uint32_t *src, uint32_t n)
{
    return RomDriver_BL702_MemCpy4(dst, src, n);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
void* BL702_MemCpy_Fast(void *pdst, const void *psrc, uint32_t n) {
    return RomDriver_BL702_MemCpy_Fast(pdst, psrc, n);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void *ARCH_MemCpy_Fast(void *pdst, const void *psrc, uint32_t n)
{
    return RomDriver_ARCH_MemCpy_Fast(pdst, psrc, n);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void *BL702_MemSet(void *s, uint8_t c, uint32_t n)
{
    return RomDriver_BL702_MemSet(s, c, n);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    uint32_t *
    BL702_MemSet4(uint32_t *dst, const uint32_t val, uint32_t n)
{
    return RomDriver_BL702_MemSet4(dst, val, n);
}

__ALWAYS_INLINE ATTR_TCM_SECTION int BL702_MemCmp(const void *s1, const void *s2, uint32_t n)
{
    return RomDriver_BL702_MemCmp(s1, s2, n);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    uint32_t
    BFLB_Soft_CRC32(void *dataIn, uint32_t len)
{
    return RomDriver_BFLB_Soft_CRC32(dataIn, len);
}
/******************************************************************************/

/******************************************************************************/
__ALWAYS_INLINE ATTR_CLOCK_SECTION
    GLB_ROOT_CLK_Type
    GLB_Get_Root_CLK_Sel(void)
{
    return RomDriver_GLB_Get_Root_CLK_Sel();
}
#if 0
__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    GLB_Set_System_CLK_Div(uint8_t hclkDiv, uint8_t bclkDiv)
{
    return RomDriver_GLB_Set_System_CLK_Div(hclkDiv, bclkDiv);
}
#endif
__ALWAYS_INLINE ATTR_CLOCK_SECTION
    uint8_t
    GLB_Get_BCLK_Div(void)
{
    return RomDriver_GLB_Get_BCLK_Div();
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    uint8_t
    GLB_Get_HCLK_Div(void)
{
    return RomDriver_GLB_Get_HCLK_Div();
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    Update_SystemCoreClockWith_XTAL(GLB_DLL_XTAL_Type xtalType)
{
    return RomDriver_Update_SystemCoreClockWith_XTAL(xtalType);
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    GLB_Set_System_CLK(GLB_DLL_XTAL_Type xtalType, GLB_SYS_CLK_Type clkFreq)
{
    return RomDriver_GLB_Set_System_CLK(xtalType, clkFreq);
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    System_Core_Clock_Update_From_RC32M(void)
{
    return RomDriver_System_Core_Clock_Update_From_RC32M();
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    GLB_Set_SF_CLK(uint8_t enable, GLB_SFLASH_CLK_Type clkSel, uint8_t div)
{
    return RomDriver_GLB_Set_SF_CLK(enable, clkSel, div);
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    GLB_Power_Off_DLL(void)
{
    return RomDriver_GLB_Power_Off_DLL();
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    GLB_Power_On_DLL(GLB_DLL_XTAL_Type xtalType)
{
    return RomDriver_GLB_Power_On_DLL(xtalType);
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    GLB_Enable_DLL_All_Clks(void)
{
    return RomDriver_GLB_Enable_DLL_All_Clks();
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    GLB_Enable_DLL_Clk(GLB_DLL_CLK_Type dllClk)
{
    return RomDriver_GLB_Enable_DLL_Clk(dllClk);
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    GLB_Disable_DLL_All_Clks(void)
{
    return RomDriver_GLB_Disable_DLL_All_Clks();
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    GLB_Disable_DLL_Clk(GLB_DLL_CLK_Type dllClk)
{
    return RomDriver_GLB_Disable_DLL_Clk(dllClk);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    BL_Err_Type
    GLB_SW_System_Reset(void)
{
    return RomDriver_GLB_SW_System_Reset();
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    BL_Err_Type
    GLB_SW_CPU_Reset(void)
{
    return RomDriver_GLB_SW_CPU_Reset();
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    BL_Err_Type
    GLB_SW_POR_Reset(void)
{
    return RomDriver_GLB_SW_POR_Reset();
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    BL_Err_Type
    GLB_Select_Internal_Flash(void)
{
    return RomDriver_GLB_Select_Internal_Flash();
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    BL_Err_Type
    GLB_Swap_Flash_Pin(void)
{
    return RomDriver_GLB_Swap_Flash_Pin();
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    BL_Err_Type
    GLB_Swap_Flash_CS_IO2_Pin(void)
{
    return RomDriver_GLB_Swap_Flash_CS_IO2_Pin();
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    BL_Err_Type
    GLB_Swap_Flash_IO0_IO3_Pin(void)
{
    return RomDriver_GLB_Swap_Flash_IO0_IO3_Pin();
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    BL_Err_Type
    GLB_Select_Internal_PSram(void)
{
    return RomDriver_GLB_Select_Internal_PSram();
}

/* aon pads GPIO9~GPIO13 IE controlled by HBN reg_aon_pad_ie_smt, abandon romdriver for this reason */
#if 0
__ALWAYS_INLINE ATTR_TCM_SECTION
BL_Err_Type GLB_GPIO_Init(GLB_GPIO_Cfg_Type *cfg)
{
    return RomDriver_GLB_GPIO_Init(cfg);
}
#endif

#if 0
__ALWAYS_INLINE ATTR_TCM_SECTION
BL_Err_Type GLB_GPIO_OUTPUT_Enable(GLB_GPIO_Type gpioPin)
{
    return RomDriver_GLB_GPIO_OUTPUT_Enable(gpioPin);
}
#endif

#if 0
__ALWAYS_INLINE ATTR_TCM_SECTION
BL_Err_Type GLB_GPIO_OUTPUT_Disable(GLB_GPIO_Type gpioPin)
{
    return RomDriver_GLB_GPIO_OUTPUT_Disable(gpioPin);
}
#endif

/* aon pads GPIO9~GPIO13 IE controlled by HBN reg_aon_pad_ie_smt, abandon romdriver for this reason */
#if 0
__ALWAYS_INLINE ATTR_TCM_SECTION
BL_Err_Type GLB_GPIO_Set_HZ(GLB_GPIO_Type gpioPin)
{
    return RomDriver_GLB_GPIO_Set_HZ(gpioPin);
}
#endif

__ALWAYS_INLINE ATTR_TCM_SECTION
    BL_Err_Type
    GLB_Deswap_Flash_Pin(void)
{
    return RomDriver_GLB_Deswap_Flash_Pin();
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    BL_Err_Type
    GLB_Select_External_Flash(void)
{
    return RomDriver_GLB_Select_External_Flash();
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    uint8_t
    GLB_GPIO_Get_Fun(GLB_GPIO_Type gpioPin)
{
    return RomDriver_GLB_GPIO_Get_Fun(gpioPin);
}
/******************************************************************************/

/******************************************************************************/
__ALWAYS_INLINE ATTR_TCM_SECTION
    BL_Sts_Type
    EF_Ctrl_Busy(void)
{
    return RomDriver_EF_Ctrl_Busy();
}

__ALWAYS_INLINE ATTR_TCM_SECTION void EF_Ctrl_Sw_AHB_Clk_0(void)
{
    RomDriver_EF_Ctrl_Sw_AHB_Clk_0();
}

__ALWAYS_INLINE ATTR_TCM_SECTION void EF_Ctrl_Load_Efuse_R0(void)
{
    RomDriver_EF_Ctrl_Load_Efuse_R0();
}

__ALWAYS_INLINE ATTR_TCM_SECTION void EF_Ctrl_Clear(uint32_t index, uint32_t len)
{
    RomDriver_EF_Ctrl_Clear(index, len);
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    uint8_t
    EF_Ctrl_Get_Trim_Parity(uint32_t val, uint8_t len)
{
    return RomDriver_EF_Ctrl_Get_Trim_Parity(val, len);
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION void EF_Ctrl_Read_RC32K_Trim(Efuse_Ana_RC32K_Trim_Type *trim)
{
    RomDriver_EF_Ctrl_Read_RC32K_Trim(trim);
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION void EF_Ctrl_Read_RC32M_Trim(Efuse_Ana_RC32M_Trim_Type *trim)
{
    RomDriver_EF_Ctrl_Read_RC32M_Trim(trim);
}
/******************************************************************************/

/******************************************************************************/
__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    PDS_Trim_RC32M(void)
{
    return RomDriver_PDS_Trim_RC32M();
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    PDS_Select_RC32M_As_PLL_Ref(void)
{
    return RomDriver_PDS_Select_RC32M_As_PLL_Ref();
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    PDS_Select_XTAL_As_PLL_Ref(void)
{
    return RomDriver_PDS_Select_XTAL_As_PLL_Ref();
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    PDS_Power_On_PLL(PDS_PLL_XTAL_Type xtalType)
{
    return RomDriver_PDS_Power_On_PLL(xtalType);
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    PDS_Enable_PLL_All_Clks(void)
{
    return RomDriver_PDS_Enable_PLL_All_Clks();
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    PDS_Disable_PLL_All_Clks(void)
{
    return RomDriver_PDS_Disable_PLL_All_Clks();
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    PDS_Enable_PLL_Clk(PDS_PLL_CLK_Type pllClk)
{
    return RomDriver_PDS_Enable_PLL_Clk(pllClk);
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    PDS_Disable_PLL_Clk(PDS_PLL_CLK_Type pllClk)
{
    return RomDriver_PDS_Disable_PLL_Clk(pllClk);
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    PDS_Power_Off_PLL(void)
{
    return RomDriver_PDS_Power_Off_PLL();
}

__ALWAYS_INLINE ATTR_TCM_SECTION void PDS_Reset(void)
{
    RomDriver_PDS_Reset();
}

__ALWAYS_INLINE ATTR_TCM_SECTION void PDS_Enable(PDS_CFG_Type *cfg, uint32_t pdsSleepCnt)
{
    RomDriver_PDS_Enable(cfg, pdsSleepCnt);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void PDS_Auto_Time_Config(uint32_t sleepDuration)
{
    RomDriver_PDS_Auto_Time_Config(sleepDuration);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void PDS_Auto_Enable(PDS_AUTO_POWER_DOWN_CFG_Type *powerCfg, PDS_AUTO_NORMAL_CFG_Type *normalCfg, BL_Fun_Type enable)
{
    RomDriver_PDS_Auto_Enable(powerCfg, normalCfg, enable);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void PDS_Manual_Force_Turn_Off(PDS_FORCE_Type domain)
{
    RomDriver_PDS_Manual_Force_Turn_Off(domain);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void PDS_Manual_Force_Turn_On(PDS_FORCE_Type domain)
{
    RomDriver_PDS_Manual_Force_Turn_On(domain);
}
/******************************************************************************/

/******************************************************************************/
#if 0
__ALWAYS_INLINE ATTR_TCM_SECTION
void HBN_Enable(uint8_t aGPIOIeCfg, HBN_LDO_LEVEL_Type ldoLevel, HBN_LEVEL_Type hbnLevel)
{
    RomDriver_HBN_Enable(aGPIOIeCfg, ldoLevel, hbnLevel);
}
#endif

__ALWAYS_INLINE ATTR_TCM_SECTION
    BL_Err_Type
    HBN_Reset(void)
{
    return RomDriver_HBN_Reset();
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    BL_Err_Type
    HBN_GPIO_Dbg_Pull_Cfg(BL_Fun_Type pupdEn, BL_Fun_Type dlyEn, uint8_t dlySec, HBN_INT_Type gpioIrq, BL_Mask_Type gpioMask)
{
    return RomDriver_HBN_GPIO_Dbg_Pull_Cfg(pupdEn, dlyEn, dlySec, gpioIrq, gpioMask);
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    HBN_Trim_RC32K(void)
{
    return RomDriver_HBN_Trim_RC32K();
}

__ALWAYS_INLINE ATTR_CLOCK_SECTION
    BL_Err_Type
    HBN_Set_ROOT_CLK_Sel(HBN_ROOT_CLK_Type rootClk)
{
    return RomDriver_HBN_Set_ROOT_CLK_Sel(rootClk);
}
/******************************************************************************/

/******************************************************************************/
__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_xip_sflash_state_save(spi_flash_cfg_type *p_flash_cfg, uint32_t *offset, uint8_t group, uint8_t bank)
{
    return RomDriver_XIP_SFlash_State_Save(p_flash_cfg, offset);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_xip_sflash_state_restore(spi_flash_cfg_type *p_flash_cfg, uint32_t offset, uint8_t group, uint8_t bank)
{
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;
    return RomDriver_XIP_SFlash_State_Restore(p_flash_cfg, io_mode, offset);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_xip_sflash_erase_need_lock(spi_flash_cfg_type *p_flash_cfg, uint32_t startaddr, int len, uint8_t group, uint8_t bank)
{
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;
    return RomDriver_XIP_SFlash_Erase_Need_Lock(p_flash_cfg, io_mode, startaddr, startaddr+len-1);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_xip_sflash_write_need_lock(spi_flash_cfg_type *p_flash_cfg, uint32_t addr, uint8_t *data, uint32_t len, uint8_t group, uint8_t bank)
{
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;
    return RomDriver_XIP_SFlash_Write_Need_Lock(p_flash_cfg, io_mode, addr, data, len);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_xip_sflash_read_need_lock(spi_flash_cfg_type *p_flash_cfg, uint32_t addr, uint8_t *data, uint32_t len, uint8_t group, uint8_t bank)
{
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;
    return RomDriver_XIP_SFlash_Read_Need_Lock(p_flash_cfg, io_mode, addr, data, len);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_xip_sflash_get_jedecid_need_lock(spi_flash_cfg_type *p_flash_cfg, uint8_t *data, uint8_t group, uint8_t bank)
{
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;
    return RomDriver_XIP_SFlash_GetJedecId_Need_Lock(p_flash_cfg, io_mode, data);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_xip_sflash_get_deviceid_need_lock(spi_flash_cfg_type *p_flash_cfg, uint8_t is_32bits_addr, uint8_t *data, uint8_t group, uint8_t bank)
{
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;
    return RomDriver_XIP_SFlash_GetDeviceId_Need_Lock(p_flash_cfg, io_mode, data);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_xip_sflash_get_uniqueid_need_lock(spi_flash_cfg_type *p_flash_cfg, uint8_t *data, uint8_t id_len, uint8_t group, uint8_t bank)
{
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;
    return RomDriver_XIP_SFlash_GetUniqueId_Need_Lock(p_flash_cfg, io_mode, data, id_len);
}

#if 0
__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_xip_sflash_read_via_cache_need_lock(uint32_t addr, uint8_t *data, uint32_t len, uint8_t group, uint8_t bank)
{
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;
    return RomDriver_XIP_SFlash_Read_Via_Cache_Need_Lock(addr, data, len);
}
#endif

__ALWAYS_INLINE ATTR_TCM_SECTION int bflb_xip_sflash_read_with_lock(spi_flash_cfg_type *p_flash_cfg, uint32_t addr, uint8_t *dst, int len, uint8_t group, uint8_t bank)
{
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;
    return RomDriver_XIP_SFlash_Read_With_Lock(p_flash_cfg, io_mode, addr, dst, len);
}

__ALWAYS_INLINE ATTR_TCM_SECTION int bflb_xip_sflash_write_with_lock(spi_flash_cfg_type *p_flash_cfg, uint32_t addr, uint8_t *src, int len, uint8_t group, uint8_t bank)
{
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;
    return RomDriver_XIP_SFlash_Write_With_Lock(p_flash_cfg, io_mode, addr, src, len);
}

__ALWAYS_INLINE ATTR_TCM_SECTION int bflb_xip_sflash_erase_with_lock(spi_flash_cfg_type *p_flash_cfg, uint32_t addr, int len, uint8_t group, uint8_t bank)
{
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;
    return RomDriver_XIP_SFlash_Erase_With_Lock(p_flash_cfg, io_mode, addr, len);
}
/******************************************************************************/

/******************************************************************************/
__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sflash_init(const struct sf_ctrl_cfg_type *p_sf_ctrl_cfg)
{
    RomDriver_SFlash_Init(p_sf_ctrl_cfg);
}

__ALWAYS_INLINE ATTR_TCM_SECTION int bflb_sflash_setspimode(uint8_t mode)
{
    return RomDriver_SFlash_SetSPIMode(mode);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sflash_read_reg(spi_flash_cfg_type *flash_cfg, uint8_t reg_index, uint8_t *reg_value, uint8_t reg_len)
{
    return RomDriver_SFlash_Read_Reg(flash_cfg, reg_index, reg_value, reg_len);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sflash_write_reg(spi_flash_cfg_type *flash_cfg, uint8_t reg_index, uint8_t *reg_value, uint8_t reg_len)
{
    return RomDriver_SFlash_Write_Reg(flash_cfg, reg_index, reg_value, reg_len);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sflash_read_reg_with_cmd(spi_flash_cfg_type *flash_cfg, uint8_t readRegCmd, uint8_t *reg_value, uint8_t reg_len)
{
    return RomDriver_SFlash_Read_Reg_With_Cmd(flash_cfg, readRegCmd, reg_value, reg_len);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sflash_write_reg_with_cmd(spi_flash_cfg_type *flash_cfg, uint8_t writeRegCmd, uint8_t *reg_value, uint8_t reg_len)
{
    return RomDriver_SFlash_Write_Reg_With_Cmd(flash_cfg, writeRegCmd, reg_value, reg_len);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sflash_busy(spi_flash_cfg_type *flash_cfg)
{
    return RomDriver_SFlash_Busy(flash_cfg);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sflash_write_enable(spi_flash_cfg_type *flash_cfg)
{
    return RomDriver_SFlash_Write_Enable(flash_cfg);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sflash_qspi_enable(spi_flash_cfg_type *flash_cfg)
{
    return RomDriver_SFlash_Qspi_Enable(flash_cfg);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sflash_volatile_reg_write_enable(spi_flash_cfg_type *flash_cfg)
{
    RomDriver_SFlash_Volatile_Reg_Write_Enable(flash_cfg);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sflash_chip_erase(spi_flash_cfg_type *flash_cfg)
{
    return RomDriver_SFlash_Chip_Erase(flash_cfg);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sflash_sector_erase(spi_flash_cfg_type *flash_cfg, uint32_t secNum)
{
    return RomDriver_SFlash_Sector_Erase(flash_cfg, secNum);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sflash_blk32_erase(spi_flash_cfg_type *flash_cfg, uint32_t blkNum)
{
    return RomDriver_SFlash_Blk32_Erase(flash_cfg, blkNum);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sflash_blk64_erase(spi_flash_cfg_type *flash_cfg, uint32_t blkNum)
{
    return RomDriver_SFlash_Blk64_Erase(flash_cfg, blkNum);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sflash_erase(spi_flash_cfg_type *flash_cfg, uint32_t startaddr, uint32_t endaddr)
{
    return RomDriver_SFlash_Erase(flash_cfg, startaddr, endaddr);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sflash_program(spi_flash_cfg_type *flash_cfg, uint8_t io_mode, uint32_t addr, uint8_t *data, uint32_t len)
{
    return RomDriver_SFlash_Program(flash_cfg, io_mode, addr, data, len);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sflash_get_uniqueid(uint8_t *data, uint8_t id_len)
{
    RomDriver_SFlash_GetUniqueId(data, id_len);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sflash_get_jedecid(spi_flash_cfg_type *flash_cfg, uint8_t *data)
{
    RomDriver_SFlash_GetJedecId(flash_cfg, data);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sflash_get_deviceid(uint8_t *data, uint8_t is_32bits_addr)
{
    RomDriver_SFlash_GetDeviceId(data);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sflash_powerdown(void)
{
    RomDriver_SFlash_Powerdown();
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sflash_release_powerdown(spi_flash_cfg_type *flash_cfg)
{
    RomDriver_SFlash_Releae_Powerdown(flash_cfg);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sflash_restore_from_powerdown(spi_flash_cfg_type *p_flash_cfg, uint8_t flash_cont_read, uint8_t bank)
{
    return RomDriver_SFlash_Restore_From_Powerdown(p_flash_cfg, flash_cont_read);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sflash_set_burst_wrap(spi_flash_cfg_type *flash_cfg)
{
    RomDriver_SFlash_SetBurstWrap(flash_cfg);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sflash_disable_burst_wrap(spi_flash_cfg_type *flash_cfg)
{
    RomDriver_SFlash_DisableBurstWrap(flash_cfg);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sflash_software_reset(spi_flash_cfg_type *flash_cfg)
{
    return RomDriver_SFlash_Software_Reset(flash_cfg);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sflash_reset_continue_read(spi_flash_cfg_type *flash_cfg)
{
    return RomDriver_SFlash_Reset_Continue_Read(flash_cfg);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sflash_set_idbus_cfg(spi_flash_cfg_type *flash_cfg,
                              uint8_t io_mode, uint8_t contRead, uint32_t addr, uint32_t len, uint8_t bank)
{
    return RomDriver_SFlash_Set_IDbus_Cfg(flash_cfg, io_mode, contRead, addr, len);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sflash_idbus_read_enable(spi_flash_cfg_type *flash_cfg, uint8_t io_mode, uint8_t contRead, uint8_t bank)
{
    return RomDriver_SFlash_IDbus_Read_Enable(flash_cfg, io_mode, contRead);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sflash_cache_read_enable(spi_flash_cfg_type *flash_cfg,
                             uint8_t io_mode, uint8_t contRead, uint8_t wayDisable)
{
    return RomDriver_SFlash_Cache_Read_Enable(flash_cfg, io_mode, contRead, wayDisable);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sflash_cache_read_disable(void)
{
    RomDriver_SFlash_Cache_Read_Disable();
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sflash_read(spi_flash_cfg_type *flash_cfg,
                uint8_t io_mode, uint8_t contRead, uint32_t addr, uint8_t *data, uint32_t len)
{
    return RomDriver_SFlash_Read(flash_cfg, io_mode, contRead, addr, data, len);
}
/******************************************************************************/

/******************************************************************************/
__ALWAYS_INLINE ATTR_TCM_SECTION
    BL_Err_Type
    L1C_Cache_Enable_Set(uint8_t wayDisable)
{
    return RomDriver_L1C_Cache_Enable_Set(wayDisable);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_l1c_cache_write_set(uint8_t wt_en, uint8_t wb_en, uint8_t wa_en)
{
    RomDriver_L1C_Cache_Write_Set(wt_en, wb_en, wa_en);
}

#if 0
__ALWAYS_INLINE ATTR_TCM_SECTION
    BL_Err_Type
    L1C_Cache_Flush(uint8_t wayDisable)
{
    return RomDriver_L1C_Cache_Flush(wayDisable);
}
#endif

__ALWAYS_INLINE ATTR_TCM_SECTION void L1C_Cache_Hit_Count_Get(uint32_t *hitCountLow, uint32_t *hitCountHigh)
{
    RomDriver_L1C_Cache_Hit_Count_Get(hitCountLow, hitCountHigh);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    uint32_t
    L1C_Cache_Miss_Count_Get(void)
{
    return RomDriver_L1C_Cache_Miss_Count_Get();
}

__ALWAYS_INLINE ATTR_TCM_SECTION void L1C_Cache_Read_Disable(void)
{
    RomDriver_L1C_Cache_Read_Disable();
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    BL_Err_Type
    L1C_Set_Wrap(BL_Fun_Type wrap)
{
    return RomDriver_L1C_Set_Wrap(wrap);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    BL_Err_Type
    L1C_Set_Way_Disable(uint8_t disableVal)
{
    return RomDriver_L1C_Set_Way_Disable(disableVal);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    BL_Err_Type
    L1C_IROM_2T_Access_Set(uint8_t enable)
{
    return RomDriver_L1C_IROM_2T_Access_Set(enable);
}
/******************************************************************************/

/******************************************************************************/
__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_enable(const struct sf_ctrl_cfg_type *cfg)
{
    RomDriver_SF_Ctrl_Enable(cfg);
}

#if 0
__ALWAYS_INLINE ATTR_TCM_SECTION
void bflb_sf_ctrl_psram_init(struct sf_ctrl_psram_cfg *psram_cfg)
{
    RomDriver_SF_Ctrl_Psram_Init(psram_cfg);
}
#endif

__ALWAYS_INLINE ATTR_TCM_SECTION
    uint8_t
    bflb_sf_ctrl_get_clock_delay(void)
{
    return RomDriver_SF_Ctrl_Get_Clock_Delay();
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_set_clock_delay(uint8_t delay)
{
    RomDriver_SF_Ctrl_Set_Clock_Delay(delay);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_cmds_set(struct sf_ctrl_cmds_cfg *cmds_cfg, uint8_t sel)
{
    RomDriver_SF_Ctrl_Cmds_Set(cmds_cfg);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_set_owner(uint8_t owner)
{
    RomDriver_SF_Ctrl_Set_Owner(owner);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_disable(void)
{
    RomDriver_SF_Ctrl_Disable();
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_select_pad(uint8_t sel)
{
    RomDriver_SF_Ctrl_Select_Pad(sel);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_select_bank(uint8_t sel)
{
    RomDriver_SF_Ctrl_Select_Bank(sel);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_aes_enable_be(void)
{
    RomDriver_SF_Ctrl_AES_Enable_BE();
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_aes_enable_le(void)
{
    RomDriver_SF_Ctrl_AES_Enable_LE();
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_aes_set_region(uint8_t region, uint8_t enable,
                                                             uint8_t hw_key, uint32_t start_addr, uint32_t end_addr, uint8_t locked)
{
    RomDriver_SF_Ctrl_AES_Set_Region(region, enable, hw_key, start_addr, end_addr, locked);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_aes_set_key(uint8_t region, uint8_t *key, uint8_t key_type)
{
    RomDriver_SF_Ctrl_AES_Set_Key(region, key, key_type);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_aes_set_key_be(uint8_t region, uint8_t *key, uint8_t key_type)
{
    RomDriver_SF_Ctrl_AES_Set_Key_BE(region, key, key_type);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_aes_set_iv(uint8_t region, uint8_t *iv, uint32_t addr_offset)
{
    RomDriver_SF_Ctrl_AES_Set_IV(region, iv, addr_offset);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_aes_set_iv_be(uint8_t region, uint8_t *iv, uint32_t addr_offset)
{
    RomDriver_SF_Ctrl_AES_Set_IV_BE(region, iv, addr_offset);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_aes_enable(void)
{
    RomDriver_SF_Ctrl_AES_Enable();
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_aes_disable(void)
{
    RomDriver_SF_Ctrl_AES_Disable();
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    uint8_t
    bflb_sf_ctrl_is_aes_enable(void)
{
    return RomDriver_SF_Ctrl_Is_AES_Enable();
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_set_flash_image_offset(uint32_t addr_offset, uint8_t group, uint8_t bank)
{
    RomDriver_SF_Ctrl_Set_Flash_Image_Offset(addr_offset);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    uint32_t
    bflb_sf_ctrl_get_flash_image_offset(uint8_t group, uint8_t bank)
{
    return RomDriver_SF_Ctrl_Get_Flash_Image_Offset();
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_select_clock(uint8_t sahb_type)
{
    RomDriver_SF_Ctrl_Select_Clock(sahb_type);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_sendcmd(struct sf_ctrl_cmd_cfg_type *cfg)
{
    RomDriver_SF_Ctrl_SendCmd(cfg);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_flash_read_icache_set(struct sf_ctrl_cmd_cfg_type *cfg, uint8_t cmd_valid)
{
    RomDriver_SF_Ctrl_Flash_Read_Icache_Set(cfg, cmd_valid);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_psram_write_icache_set(struct sf_ctrl_cmd_cfg_type *cfg, uint8_t cmd_valid)
{
    RomDriver_SF_Ctrl_Psram_Write_Icache_Set(cfg, cmd_valid);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_ctrl_psram_read_icache_set(struct sf_ctrl_cmd_cfg_type *cfg, uint8_t cmd_valid)
{
    RomDriver_SF_Ctrl_Psram_Read_Icache_Set(cfg, cmd_valid);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    uint8_t
    bflb_sf_ctrl_get_busy_state(void)
{
    return RomDriver_SF_Ctrl_GetBusyState();
}

__ALWAYS_INLINE ATTR_TCM_SECTION int bflb_sf_cfg_deinit_ext_flash_gpio(uint8_t ext_flash_pin)
{
    return RomDriver_SF_Cfg_Deinit_Ext_Flash_Gpio(ext_flash_pin);
}

#if 0
__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_sf_cfg_init_ext_flash_gpio(uint8_t ext_flash_pin)
{
    RomDriver_SF_Cfg_Init_Ext_Flash_Gpio(ext_flash_pin);
}
#endif

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_sf_cfg_get_flash_cfg_need_lock(uint32_t flash_id, spi_flash_cfg_type *p_flash_cfg, uint8_t group, uint8_t bank)
{
    return RomDriver_SF_Cfg_Get_Flash_Cfg_Need_Lock(flash_id, p_flash_cfg);
}

#if 0
__ALWAYS_INLINE ATTR_TCM_SECTION
void bflb_sf_cfg_init_flash_gpio(uint8_t flash_pin_cfg, uint8_t restore_default)
{
    RomDriver_SF_Cfg_Init_Flash_Gpio(flash_pin_cfg, restore_default);
}
#endif

__ALWAYS_INLINE ATTR_TCM_SECTION
    uint32_t
    bflb_sf_cfg_flash_identify(uint8_t callFromFlash, uint8_t flash_pin_cfg, uint8_t restore_default,
                          spi_flash_cfg_type *p_flash_cfg, uint8_t group, uint8_t bank)
{
    uint8_t auto_scan = 0;
    uint8_t flash_pin = 0;
    auto_scan = ((flash_pin_cfg >> 7) & 1);
    flash_pin = (flash_pin_cfg & 0x7F);
    return RomDriver_SF_Cfg_Flash_Identify(callFromFlash, auto_scan, flash_pin, restore_default, p_flash_cfg);
}
/******************************************************************************/

/******************************************************************************/
#if 0
__ALWAYS_INLINE ATTR_TCM_SECTION
void bflb_psram_init(struct spi_psram_cfg_type *psram_cfg, struct sf_ctrl_cmds_cfg *cmds_cfg, struct sf_ctrl_psram_cfg *psram_cfg)
{
    RomDriver_Psram_Init(psram_cfg, cmds_cfg, psram_cfg);
}
#endif

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_psram_readreg(struct spi_psram_cfg_type *psram_cfg, uint8_t *reg_value)
{
    RomDriver_Psram_ReadReg(psram_cfg, reg_value);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_psram_writereg(struct spi_psram_cfg_type *psram_cfg, uint8_t *reg_value)
{
    RomDriver_Psram_WriteReg(psram_cfg, reg_value);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_psram_setdrivestrength(struct spi_psram_cfg_type *psram_cfg)
{
    return RomDriver_Psram_SetDriveStrength(psram_cfg);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_psram_setburstwrap(struct spi_psram_cfg_type *psram_cfg)
{
    return RomDriver_Psram_SetBurstWrap(psram_cfg);
}

__ALWAYS_INLINE ATTR_TCM_SECTION void bflb_psram_readid(struct spi_psram_cfg_type *psram_cfg, uint8_t *data)
{
    RomDriver_Psram_ReadId(psram_cfg, data);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_psram_enterquadmode(struct spi_psram_cfg_type *psram_cfg)
{
    return RomDriver_Psram_EnterQuadMode(psram_cfg);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_psram_exitquadmode(struct spi_psram_cfg_type *psram_cfg)
{
    return RomDriver_Psram_ExitQuadMode(psram_cfg);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_psram_toggleburstlength(struct spi_psram_cfg_type *psram_cfg, uint8_t ctrl_mode)
{
    return RomDriver_Psram_ToggleBurstLength(psram_cfg, ctrl_mode);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_psram_softwarereset(struct spi_psram_cfg_type *psram_cfg, uint8_t ctrl_mode)
{
    return RomDriver_Psram_SoftwareReset(psram_cfg, ctrl_mode);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_psram_set_idbus_cfg(struct spi_psram_cfg_type *psram_cfg,
                        uint8_t io_mode, uint32_t addr, uint32_t len)
{
    return RomDriver_Psram_Set_IDbus_Cfg(psram_cfg, io_mode, addr, len);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_psram_cache_write_set(struct spi_psram_cfg_type *psram_cfg, uint8_t io_mode,
                               uint8_t wt_en, uint8_t wb_en, uint8_t wa_en)
{
    return RomDriver_Psram_Cache_Write_Set(psram_cfg, io_mode, wt_en, wb_en, wa_en);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_psram_write(struct spi_psram_cfg_type *psram_cfg,
                uint8_t io_mode, uint32_t addr, uint8_t *data, uint32_t len)
{
    return RomDriver_Psram_Write(psram_cfg, io_mode, addr, data, len);
}

__ALWAYS_INLINE ATTR_TCM_SECTION
    int
    bflb_psram_read(struct spi_psram_cfg_type *psram_cfg,
               uint8_t io_mode, uint32_t addr, uint8_t *data, uint32_t len)
{
    return RomDriver_Psram_Read(psram_cfg, io_mode, addr, data, len);
}
/******************************************************************************/
