#include "bl602_romdriver.h"

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION AON_Power_On_MBG(void)
{
    return RomDriver_AON_Power_On_MBG();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION AON_Power_Off_MBG(void)
{
    return RomDriver_AON_Power_Off_MBG();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION AON_Power_On_XTAL(void)
{
    return RomDriver_AON_Power_On_XTAL();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION AON_Set_Xtal_CapCode(uint8_t capIn, uint8_t capOut)
{
    return RomDriver_AON_Set_Xtal_CapCode(capIn, capOut);
}

__ALWAYS_INLINE
uint8_t ATTR_CLOCK_SECTION AON_Get_Xtal_CapCode(void)
{
    return RomDriver_AON_Get_Xtal_CapCode();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION AON_Power_Off_XTAL(void)
{
    return RomDriver_AON_Power_Off_XTAL();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION AON_Power_On_BG(void)
{
    return RomDriver_AON_Power_On_BG();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION AON_Power_Off_BG(void)
{
    return RomDriver_AON_Power_Off_BG();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION AON_Power_On_LDO11_SOC(void)
{
    return RomDriver_AON_Power_On_LDO11_SOC();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION AON_Power_Off_LDO11_SOC(void)
{
    return RomDriver_AON_Power_Off_LDO11_SOC();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION AON_Power_On_LDO15_RF(void)
{
    return RomDriver_AON_Power_On_LDO15_RF();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION AON_Power_Off_LDO15_RF(void)
{
    return RomDriver_AON_Power_Off_LDO15_RF();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION AON_Power_On_SFReg(void)
{
    return RomDriver_AON_Power_On_SFReg();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION AON_Power_Off_SFReg(void)
{
    return RomDriver_AON_Power_Off_SFReg();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION AON_LowPower_Enter_PDS0(void)
{
    return RomDriver_AON_LowPower_Enter_PDS0();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION AON_LowPower_Exit_PDS0(void)
{
    return RomDriver_AON_LowPower_Exit_PDS0();
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION ASM_Delay_Us(uint32_t core, uint32_t cnt)
{
    return RomDriver_ASM_Delay_Us(core, cnt);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION BL602_Delay_US(uint32_t cnt)
{
    return RomDriver_BL602_Delay_US(cnt);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION BL602_Delay_MS(uint32_t cnt)
{
    return RomDriver_BL602_Delay_MS(cnt);
}

__ALWAYS_INLINE
void *ATTR_TCM_SECTION BL602_MemCpy(void *dst, const void *src, uint32_t n)
{
    return RomDriver_BL602_MemCpy(dst, src, n);
}

__ALWAYS_INLINE
uint32_t *ATTR_TCM_SECTION BL602_MemCpy4(uint32_t *dst, const uint32_t *src, uint32_t n)
{
    return RomDriver_BL602_MemCpy4(dst, src, n);
}

__ALWAYS_INLINE
void *ATTR_TCM_SECTION BL602_MemCpy_Fast(void *pdst, const void *psrc, uint32_t n)
{
    return RomDriver_BL602_MemCpy_Fast(pdst, psrc, n);
}

__ALWAYS_INLINE
void *ATTR_TCM_SECTION BL602_MemSet(void *s, uint8_t c, uint32_t n)
{
    return RomDriver_BL602_MemSet(s, c, n);
}

__ALWAYS_INLINE
uint32_t *ATTR_TCM_SECTION BL602_MemSet4(uint32_t *dst, const uint32_t val, uint32_t n)
{
    return RomDriver_BL602_MemSet4(dst, val, n);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION BL602_MemCmp(const void *s1, const void *s2, uint32_t n)
{
    return RomDriver_BL602_MemCmp(s1, s2, n);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION EF_Ctrl_Sw_AHB_Clk_0(void)
{
    return RomDriver_EF_Ctrl_Sw_AHB_Clk_0();
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION EF_Ctrl_Program_Efuse_0(void)
{
    return RomDriver_EF_Ctrl_Program_Efuse_0();
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION EF_Ctrl_Load_Efuse_R0(void)
{
    return RomDriver_EF_Ctrl_Load_Efuse_R0();
}

__ALWAYS_INLINE
BL_Sts_Type ATTR_TCM_SECTION EF_Ctrl_Busy(void)
{
    return RomDriver_EF_Ctrl_Busy();
}

__ALWAYS_INLINE
BL_Sts_Type ATTR_TCM_SECTION EF_Ctrl_AutoLoad_Done(void)
{
    return RomDriver_EF_Ctrl_AutoLoad_Done();
}

__ALWAYS_INLINE
uint8_t ATTR_CLOCK_SECTION EF_Ctrl_Get_Trim_Parity(uint32_t val, uint8_t len)
{
    return RomDriver_EF_Ctrl_Get_Trim_Parity(val, len);
}

__ALWAYS_INLINE
void ATTR_CLOCK_SECTION EF_Ctrl_Read_RC32M_Trim(Efuse_Ana_RC32M_Trim_Type *trim)
{
    return RomDriver_EF_Ctrl_Read_RC32M_Trim(trim);
}

__ALWAYS_INLINE
void ATTR_CLOCK_SECTION EF_Ctrl_Read_RC32K_Trim(Efuse_Ana_RC32K_Trim_Type *trim)
{
    return RomDriver_EF_Ctrl_Read_RC32K_Trim(trim);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION EF_Ctrl_Clear(uint32_t index, uint32_t len)
{
    return RomDriver_EF_Ctrl_Clear(index, len);
}

__ALWAYS_INLINE
GLB_ROOT_CLK_Type ATTR_CLOCK_SECTION GLB_Get_Root_CLK_Sel(void)
{
    return RomDriver_GLB_Get_Root_CLK_Sel();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_System_CLK_Div(uint8_t hclkDiv, uint8_t bclkDiv)
{
    return RomDriver_GLB_Set_System_CLK_Div(hclkDiv, bclkDiv);
}

__ALWAYS_INLINE
uint8_t ATTR_CLOCK_SECTION GLB_Get_BCLK_Div(void)
{
    return RomDriver_GLB_Get_BCLK_Div();
}

__ALWAYS_INLINE
uint8_t ATTR_CLOCK_SECTION GLB_Get_HCLK_Div(void)
{
    return RomDriver_GLB_Get_HCLK_Div();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION Update_SystemCoreClockWith_XTAL(GLB_PLL_XTAL_Type xtalType)
{
    return RomDriver_Update_SystemCoreClockWith_XTAL(xtalType);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_System_CLK(GLB_PLL_XTAL_Type xtalType, GLB_SYS_CLK_Type clkFreq)
{
    return RomDriver_GLB_Set_System_CLK(xtalType, clkFreq);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION System_Core_Clock_Update_From_RC32M(void)
{
    return RomDriver_System_Core_Clock_Update_From_RC32M();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_SF_CLK(uint8_t enable, GLB_SFLASH_CLK_Type clkSel, uint8_t div)
{
    return RomDriver_GLB_Set_SF_CLK(enable, clkSel, div);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_PKA_CLK_Sel(GLB_PKA_CLK_Type clkSel)
{
    return RomDriver_GLB_Set_PKA_CLK_Sel(clkSel);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION GLB_SW_System_Reset(void)
{
    return RomDriver_GLB_SW_System_Reset();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION GLB_SW_CPU_Reset(void)
{
    return RomDriver_GLB_SW_CPU_Reset();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION GLB_SW_POR_Reset(void)
{
    return RomDriver_GLB_SW_POR_Reset();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION GLB_Select_Internal_Flash(void)
{
    return RomDriver_GLB_Select_Internal_Flash();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION GLB_Select_External_Flash(void)
{
    return RomDriver_GLB_Select_External_Flash();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION GLB_Deswap_Flash_Pin(void)
{
    return RomDriver_GLB_Deswap_Flash_Pin();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION GLB_Swap_Flash_Pin(void)
{
    return RomDriver_GLB_Swap_Flash_Pin();
}

#if 0
__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION GLB_GPIO_Init(GLB_GPIO_Cfg_Type *cfg)
{
	return RomDriver_GLB_GPIO_Init(cfg);
}
#endif

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION GLB_GPIO_OUTPUT_Enable(GLB_GPIO_Type gpioPin)
{
    return RomDriver_GLB_GPIO_OUTPUT_Enable(gpioPin);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION GLB_GPIO_OUTPUT_Disable(GLB_GPIO_Type gpioPin)
{
    return RomDriver_GLB_GPIO_OUTPUT_Disable(gpioPin);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION GLB_GPIO_Set_HZ(GLB_GPIO_Type gpioPin)
{
    return RomDriver_GLB_GPIO_Set_HZ(gpioPin);
}

__ALWAYS_INLINE
uint8_t ATTR_TCM_SECTION GLB_GPIO_Get_Fun(GLB_GPIO_Type gpioPin)
{
    return RomDriver_GLB_GPIO_Get_Fun(gpioPin);
}

#if 0
__ALWAYS_INLINE
void ATTR_TCM_SECTION HBN_Mode_Enter(HBN_APP_CFG_Type *cfg)
{
	return RomDriver_HBN_Mode_Enter(cfg);
}
#endif

__ALWAYS_INLINE
void ATTR_TCM_SECTION HBN_Power_Down_Flash(spi_flash_cfg_type *flash_cfg)
{
    return RomDriver_HBN_Power_Down_Flash(flash_cfg);
}

#if 0
__ALWAYS_INLINE
void ATTR_TCM_SECTION HBN_Enable(uint8_t aGPIOIeCfg, HBN_LDO_LEVEL_Type ldoLevel, HBN_LEVEL_Type hbnLevel)
{
    return RomDriver_HBN_Enable(aGPIOIeCfg, ldoLevel, hbnLevel);
}
#endif

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION HBN_Reset(void)
{
    return RomDriver_HBN_Reset();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION HBN_Set_Ldo11_Aon_Vout(HBN_LDO_LEVEL_Type ldoLevel)
{
    return RomDriver_HBN_Set_Ldo11_Aon_Vout(ldoLevel);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION HBN_Set_Ldo11_Rt_Vout(HBN_LDO_LEVEL_Type ldoLevel)
{
    return RomDriver_HBN_Set_Ldo11_Rt_Vout(ldoLevel);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION HBN_Set_Ldo11_Soc_Vout(HBN_LDO_LEVEL_Type ldoLevel)
{
    return RomDriver_HBN_Set_Ldo11_Soc_Vout(ldoLevel);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION HBN_32K_Sel(HBN_32K_CLK_Type clkType)
{
    return RomDriver_HBN_32K_Sel(clkType);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION HBN_Set_ROOT_CLK_Sel(HBN_ROOT_CLK_Type rootClk)
{
    return RomDriver_HBN_Set_ROOT_CLK_Sel(rootClk);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION HBN_Power_On_Xtal_32K(void)
{
    return RomDriver_HBN_Power_On_Xtal_32K();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION HBN_Power_Off_Xtal_32K(void)
{
    return RomDriver_HBN_Power_Off_Xtal_32K();
}

#if 0
__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION HBN_Power_On_RC32K(void)
{
	return RomDriver_HBN_Power_On_RC32K();
}
#endif

#if 0
__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION HBN_Power_Off_RC32K(void)
{
	return RomDriver_HBN_Power_Off_RC32K();
}
#endif

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION HBN_Trim_RC32K(void)
{
    return RomDriver_HBN_Trim_RC32K();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION HBN_Hw_Pu_Pd_Cfg(uint8_t enable)
{
    return RomDriver_HBN_Hw_Pu_Pd_Cfg(enable);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION HBN_Pin_WakeUp_Mask(uint8_t maskVal)
{
    return RomDriver_HBN_Pin_WakeUp_Mask(maskVal);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION HBN_GPIO7_Dbg_Pull_Cfg(BL_Fun_Type pupdEn, BL_Fun_Type iesmtEn, BL_Fun_Type dlyEn, uint8_t dlySec)
{
    return RomDriver_HBN_GPIO7_Dbg_Pull_Cfg(pupdEn, iesmtEn, dlyEn, dlySec);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION HBN_Set_Embedded_Flash_Pullup(uint8_t enable)
{
    return RomDriver_HBN_Set_Embedded_Flash_Pullup(enable);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION L1C_Set_Wrap(BL_Fun_Type wrap)
{
    return RomDriver_L1C_Set_Wrap(wrap);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION L1C_Set_Way_Disable(uint8_t disableVal)
{
    return RomDriver_L1C_Set_Way_Disable(disableVal);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION L1C_IROM_2T_Access_Set(uint8_t enable)
{
    return RomDriver_L1C_IROM_2T_Access_Set(enable);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION PDS_Reset(void)
{
    return RomDriver_PDS_Reset();
}

#if 0
__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION PDS_Enable(PDS_CTL_Type *cfg, PDS_CTL4_Type *cfg4, uint32_t pdsSleepCnt)
{
    return RomDriver_PDS_Enable(cfg, cfg4, pdsSleepCnt);
}
#endif

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION PDS_Force_Config(PDS_CTL2_Type *cfg2, PDS_CTL3_Type *cfg3)
{
    return RomDriver_PDS_Force_Config(cfg2, cfg3);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION PDS_RAM_Config(PDS_RAM_CFG_Type *ramCfg)
{
    return RomDriver_PDS_RAM_Config(ramCfg);
}

#if 0
__ALWAYS_INLINE
BL_Err_Type ATTR_TCM_SECTION PDS_Default_Level_Config(PDS_DEFAULT_LV_CFG_Type *defaultLvCfg, PDS_RAM_CFG_Type *ramCfg, uint32_t pdsSleepCnt)
{
    return RomDriver_PDS_Default_Level_Config(defaultLvCfg, ramCfg, pdsSleepCnt);
}
#endif

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION PDS_Trim_RC32M(void)
{
    return RomDriver_PDS_Trim_RC32M();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION PDS_Select_RC32M_As_PLL_Ref(void)
{
    return RomDriver_PDS_Select_RC32M_As_PLL_Ref();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION PDS_Select_XTAL_As_PLL_Ref(void)
{
    return RomDriver_PDS_Select_XTAL_As_PLL_Ref();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION PDS_Power_On_PLL(PDS_PLL_XTAL_Type xtalType)
{
    return RomDriver_PDS_Power_On_PLL(xtalType);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION PDS_Enable_PLL_All_Clks(void)
{
    return RomDriver_PDS_Enable_PLL_All_Clks();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION PDS_Disable_PLL_All_Clks(void)
{
    return RomDriver_PDS_Disable_PLL_All_Clks();
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION PDS_Enable_PLL_Clk(PDS_PLL_CLK_Type pllClk)
{
    return RomDriver_PDS_Enable_PLL_Clk(pllClk);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION PDS_Disable_PLL_Clk(PDS_PLL_CLK_Type pllClk)
{
    return RomDriver_PDS_Disable_PLL_Clk(pllClk);
}

__ALWAYS_INLINE
BL_Err_Type ATTR_CLOCK_SECTION PDS_Power_Off_PLL(void)
{
    return RomDriver_PDS_Power_Off_PLL();
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION SEC_Eng_Turn_On_Sec_Ring(void)
{
    return RomDriver_SEC_Eng_Turn_On_Sec_Ring();
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION SEC_Eng_Turn_Off_Sec_Ring(void)
{
    return RomDriver_SEC_Eng_Turn_Off_Sec_Ring();
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sflash_init(const struct sf_ctrl_cfg_type *p_sf_ctrl_cfg)
{
    return RomDriver_SFlash_Init(p_sf_ctrl_cfg);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_setspimode(uint8_t mode)
{
    return RomDriver_SFlash_SetSPIMode(mode);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_read_reg(spi_flash_cfg_type *flash_cfg, uint8_t reg_index, uint8_t *reg_value, uint8_t reg_len)
{
    return RomDriver_SFlash_Read_Reg(flash_cfg, reg_index, reg_value, reg_len);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_write_reg(spi_flash_cfg_type *flash_cfg, uint8_t reg_index, uint8_t *reg_value, uint8_t reg_len)
{
    return RomDriver_SFlash_Write_Reg(flash_cfg, reg_index, reg_value, reg_len);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_busy(spi_flash_cfg_type *flash_cfg)
{
    return RomDriver_SFlash_Busy(flash_cfg);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_write_enable(spi_flash_cfg_type *flash_cfg)
{
    return RomDriver_SFlash_Write_Enable(flash_cfg);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_qspi_enable(spi_flash_cfg_type *flash_cfg)
{
    return RomDriver_SFlash_Qspi_Enable(flash_cfg);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sflash_volatile_reg_write_enable(spi_flash_cfg_type *flash_cfg)
{
    return RomDriver_SFlash_Volatile_Reg_Write_Enable(flash_cfg);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_chip_erase(spi_flash_cfg_type *flash_cfg)
{
    return RomDriver_SFlash_Chip_Erase(flash_cfg);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_sector_erase(spi_flash_cfg_type *flash_cfg, uint32_t sec_num)
{
    return RomDriver_SFlash_Sector_Erase(flash_cfg, sec_num);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_blk32_erase(spi_flash_cfg_type *flash_cfg, uint32_t blk_num)
{
    return RomDriver_SFlash_Blk32_Erase(flash_cfg, blk_num);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_blk64_erase(spi_flash_cfg_type *flash_cfg, uint32_t blk_num)
{
    return RomDriver_SFlash_Blk64_Erase(flash_cfg, blk_num);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_erase(spi_flash_cfg_type *flash_cfg, uint32_t startaddr, uint32_t endaddr)
{
    return RomDriver_SFlash_Erase(flash_cfg, startaddr, endaddr);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_program(spi_flash_cfg_type *flash_cfg, uint8_t io_mode, uint32_t addr, uint8_t *data, uint32_t len)
{
    return RomDriver_SFlash_Program(flash_cfg, io_mode, addr, data, len);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sflash_get_uniqueid(uint8_t *data, uint8_t idLen)
{
    return RomDriver_SFlash_GetUniqueId(data, idLen);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sflash_get_jedecid(spi_flash_cfg_type *flash_cfg, uint8_t *data)
{
    return RomDriver_SFlash_GetJedecId(flash_cfg, data);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sflash_get_deviceid(uint8_t *data, uint8_t is_32bits_addr)
{
    return RomDriver_SFlash_GetDeviceId(data);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sflash_powerdown(void)
{
    return RomDriver_SFlash_Powerdown();
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sflash_release_powerdown(spi_flash_cfg_type *flash_cfg)
{
    return RomDriver_SFlash_Releae_Powerdown(flash_cfg);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sflash_set_burst_wrap(spi_flash_cfg_type *flash_cfg)
{
    return RomDriver_SFlash_SetBurstWrap(flash_cfg);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sflash_disable_burst_wrap(spi_flash_cfg_type *flash_cfg)
{
    return RomDriver_SFlash_DisableBurstWrap(flash_cfg);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_software_reset(spi_flash_cfg_type *flash_cfg)
{
    return RomDriver_SFlash_Software_Reset(flash_cfg);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sflash_reset_continue_read(spi_flash_cfg_type *flash_cfg)
{
    return RomDriver_SFlash_Reset_Continue_Read(flash_cfg);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_set_idbus_cfg(spi_flash_cfg_type *flash_cfg, uint8_t io_mode, uint8_t cont_read, uint32_t addr, uint32_t len, uint8_t bank)
{
    return RomDriver_SFlash_Set_IDbus_Cfg(flash_cfg, io_mode, cont_read, addr, len);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_idbus_read_enable(spi_flash_cfg_type *flash_cfg, uint8_t io_mode, uint8_t cont_read, uint8_t bank)
{
    return RomDriver_SFlash_IDbus_Read_Enable(flash_cfg, io_mode, cont_read);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_cache_enable_set(uint8_t way_disable)
{
    return RomDriver_SFlash_Cache_Enable_Set(way_disable);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_cache_flush(void)
{
    return RomDriver_SFlash_Cache_Flush();
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_cache_read_enable(spi_flash_cfg_type *flash_cfg, uint8_t io_mode, uint8_t cont_read, uint8_t way_disable)
{
    return RomDriver_SFlash_Cache_Read_Enable(flash_cfg, io_mode, cont_read, way_disable);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_l1c_hit_count_get(uint32_t *hit_count_low, uint32_t *hit_count_high)
{
    return RomDriver_SFlash_Cache_Hit_Count_Get(hit_count_low, hit_count_high);
}

__ALWAYS_INLINE
uint32_t ATTR_TCM_SECTION bflb_l1c_miss_count_get(void)
{
    return RomDriver_SFlash_Cache_Miss_Count_Get();
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sflash_cache_read_disable(void)
{
    return RomDriver_SFlash_Cache_Read_Disable();
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_read(spi_flash_cfg_type *flash_cfg, uint8_t io_mode, uint8_t cont_read, uint32_t addr, uint8_t *data, uint32_t len)
{
    return RomDriver_SFlash_Read(flash_cfg, io_mode, cont_read, addr, data, len);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_read_reg_with_cmd(spi_flash_cfg_type *flash_cfg, uint8_t read_reg_cmd, uint8_t *reg_value, uint8_t reg_len)
{
    return RomDriver_SFlash_Read_Reg_With_Cmd(flash_cfg, read_reg_cmd, reg_value, reg_len);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_write_reg_with_cmd(spi_flash_cfg_type *flash_cfg, uint8_t write_reg_cmd, uint8_t *reg_value, uint8_t reg_len)
{
    return RomDriver_SFlash_Write_Reg_With_Cmd(flash_cfg, write_reg_cmd, reg_value, reg_len);
}

#if 0
__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sflash_restore_from_powerdown(spi_flash_cfg_type *p_flash_cfg, uint8_t flashContRead)
{
	return RomDriver_SFlash_Restore_From_Powerdown(p_flash_cfg, flashContRead);
}
#endif

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sf_cfg_init_ext_flash_gpio(uint8_t ext_flash_pin)
{
    return RomDriver_SF_Cfg_Init_Ext_Flash_Gpio(ext_flash_pin);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_cfg_init_internal_flash_gpio(void)
{
    return RomDriver_SF_Cfg_Init_Internal_Flash_Gpio();
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sf_cfg_deinit_ext_flash_gpio(uint8_t ext_flash_pin)
{
    return RomDriver_SF_Cfg_Deinit_Ext_Flash_Gpio(ext_flash_pin);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_cfg_restore_gpio17_fun(uint8_t fun)
{
    return RomDriver_SF_Cfg_Restore_GPIO17_Fun(fun);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sf_cfg_get_flash_cfg_need_lock(uint32_t flash_id, spi_flash_cfg_type *p_flash_cfg, uint8_t group, uint8_t bank)
{
    return RomDriver_SF_Cfg_Get_Flash_Cfg_Need_Lock(flash_id, p_flash_cfg);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_sf_cfg_init_flash_gpio(uint8_t flash_pin_cfg, uint8_t restore_default)
{
    return RomDriver_SF_Cfg_Init_Flash_Gpio(flash_pin_cfg, restore_default);
}

__ALWAYS_INLINE
uint32_t ATTR_TCM_SECTION bflb_sf_cfg_flash_identify(uint8_t call_from_flash, uint8_t flash_pin_cfg, uint8_t restore_default, spi_flash_cfg_type *p_flash_cfg, uint8_t group, uint8_t bank)
{
    uint8_t auto_scan = 0;
    uint8_t flash_pin = 0;
    auto_scan = ((flash_pin_cfg >> 7) & 1);
    flash_pin = (flash_pin_cfg & 0x7F);
    return RomDriver_SF_Cfg_Flash_Identify(call_from_flash, auto_scan, flash_pin, restore_default, p_flash_cfg);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_ctrl_enable(const struct sf_ctrl_cfg_type *cfg)
{
    return RomDriver_SF_Ctrl_Enable(cfg);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_ctrl_select_pad(uint8_t sel)
{
    return RomDriver_SF_Ctrl_Select_Pad(sel);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_ctrl_set_owner(uint8_t owner)
{
    return RomDriver_SF_Ctrl_Set_Owner(owner);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_ctrl_disable(void)
{
    return RomDriver_SF_Ctrl_Disable();
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_enable_be(void)
{
    return RomDriver_SF_Ctrl_AES_Enable_BE();
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_enable_le(void)
{
    return RomDriver_SF_Ctrl_AES_Enable_LE();
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_set_region(uint8_t region, uint8_t enable, uint8_t hw_key, uint32_t start_addr, uint32_t end_addr, uint8_t locked)
{
    return RomDriver_SF_Ctrl_AES_Set_Region(region, enable, hw_key, start_addr, end_addr, locked);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_set_key(uint8_t region, uint8_t *key, uint8_t keyType)
{
    return RomDriver_SF_Ctrl_AES_Set_Key(region, key, keyType);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_set_key_be(uint8_t region, uint8_t *key, uint8_t keyType)
{
    return RomDriver_SF_Ctrl_AES_Set_Key_BE(region, key, keyType);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_set_iv(uint8_t region, uint8_t *iv, uint32_t addr_offset)
{
    return RomDriver_SF_Ctrl_AES_Set_IV(region, iv, addr_offset);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_set_iv_be(uint8_t region, uint8_t *iv, uint32_t addr_offset)
{
    return RomDriver_SF_Ctrl_AES_Set_IV_BE(region, iv, addr_offset);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_enable(void)
{
    return RomDriver_SF_Ctrl_AES_Enable();
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_disable(void)
{
    return RomDriver_SF_Ctrl_AES_Disable();
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_ctrl_set_flash_image_offset(uint32_t addr_offset, uint8_t group, uint8_t bank)
{
    return RomDriver_SF_Ctrl_Set_Flash_Image_Offset(addr_offset);
}

__ALWAYS_INLINE
uint32_t ATTR_TCM_SECTION bflb_sf_ctrl_get_flash_image_offset(uint8_t group, uint8_t bank)
{
    return RomDriver_SF_Ctrl_Get_Flash_Image_Offset();
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_ctrl_select_clock(uint8_t sahb_type)
{
    return RomDriver_SF_Ctrl_Select_Clock(sahb_type);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_ctrl_sendcmd(struct sf_ctrl_cmd_cfg_type *cfg)
{
    return RomDriver_SF_Ctrl_SendCmd(cfg);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_ctrl_icache_set(struct sf_ctrl_cmd_cfg_type *cfg, uint8_t cmd_valid)
{
    return RomDriver_SF_Ctrl_Icache_Set(cfg, cmd_valid);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_ctrl_icache2_set(struct sf_ctrl_cmd_cfg_type *cfg, uint8_t cmd_valid)
{
    return RomDriver_SF_Ctrl_Icache2_Set(cfg, cmd_valid);
}

__ALWAYS_INLINE
uint8_t ATTR_TCM_SECTION bflb_sf_ctrl_get_busy_state(void)
{
    return RomDriver_SF_Ctrl_GetBusyState();
}

__ALWAYS_INLINE
uint8_t ATTR_TCM_SECTION bflb_sf_ctrl_is_aes_enable(void)
{
    return RomDriver_SF_Ctrl_Is_AES_Enable();
}

__ALWAYS_INLINE
uint8_t ATTR_TCM_SECTION bflb_sf_ctrl_get_clock_delay(void)
{
    return RomDriver_SF_Ctrl_Get_Clock_Delay();
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_sf_ctrl_set_clock_delay(uint8_t delay)
{
    return RomDriver_SF_Ctrl_Set_Clock_Delay(delay);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_xip_sflash_state_save(spi_flash_cfg_type *p_flash_cfg, uint32_t *offset, uint8_t group, uint8_t bank)
{
    return RomDriver_XIP_SFlash_State_Save(p_flash_cfg, offset);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_xip_sflash_state_restore(spi_flash_cfg_type *p_flash_cfg, uint32_t offset, uint8_t group, uint8_t bank)
{
    return RomDriver_XIP_SFlash_State_Restore(p_flash_cfg, offset);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_xip_sflash_erase_need_lock(spi_flash_cfg_type *p_flash_cfg, uint32_t startaddr, int len, uint8_t group, uint8_t bank)
{
    return RomDriver_XIP_SFlash_Erase_Need_Lock(p_flash_cfg, startaddr, startaddr+len-1);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_xip_sflash_write_need_lock(spi_flash_cfg_type *p_flash_cfg, uint32_t addr, uint8_t *data, uint32_t len, uint8_t group, uint8_t bank)
{
    return RomDriver_XIP_SFlash_Write_Need_Lock(p_flash_cfg, addr, data, len);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_xip_sflash_read_need_lock(spi_flash_cfg_type *p_flash_cfg, uint32_t addr, uint8_t *data, uint32_t len, uint8_t group, uint8_t bank)
{
    return RomDriver_XIP_SFlash_Read_Need_Lock(p_flash_cfg, addr, data, len);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_xip_sflash_get_jedecid_need_lock(spi_flash_cfg_type *p_flash_cfg, uint8_t *data, uint8_t group, uint8_t bank)
{
    return RomDriver_XIP_SFlash_GetJedecId_Need_Lock(p_flash_cfg, data);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_xip_sflash_get_deviceid_need_lock(spi_flash_cfg_type *p_flash_cfg, uint8_t is_32bits_addr, uint8_t *data, uint8_t group, uint8_t bank)
{
    return RomDriver_XIP_SFlash_GetDeviceId_Need_Lock(p_flash_cfg, data);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_xip_sflash_get_uniqueid_need_lock(spi_flash_cfg_type *p_flash_cfg, uint8_t *data, uint8_t idLen, uint8_t group, uint8_t bank)
{
    return RomDriver_XIP_SFlash_GetUniqueId_Need_Lock(p_flash_cfg, data, idLen);
}

__ALWAYS_INLINE
int ATTR_TCM_SECTION bflb_xip_sflash_read_via_cache_need_lock(uint32_t addr, uint8_t *data, uint32_t len, uint8_t group, uint8_t bank)
{
    return RomDriver_XIP_SFlash_Read_Via_Cache_Need_Lock(addr, data, len);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_xip_sflash_opt_enter(uint8_t *aes_enable)
{
    return RomDriver_XIP_SFlash_Opt_Enter(aes_enable);
}

__ALWAYS_INLINE
void ATTR_TCM_SECTION bflb_xip_sflash_opt_exit(uint8_t aes_enable)
{
    return RomDriver_XIP_SFlash_Opt_Exit(aes_enable);
}

__ALWAYS_INLINE
uint32_t ATTR_TCM_SECTION BFLB_Soft_CRC32(void *dataIn, uint32_t len)
{
    return RomDriver_BFLB_Soft_CRC32(dataIn, len);
}