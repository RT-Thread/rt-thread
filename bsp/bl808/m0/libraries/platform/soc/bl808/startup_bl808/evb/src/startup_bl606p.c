#ifdef BL808
#include "bl808.h"
#include "bl808_clock.h"
#include "bl808_pds.h"
#include "bl808_glb.h"
#elif defined(BL606P)
#include "bl606p.h"
#include "bl606p_clock.h"
#include "bl606p_pds.h"
#include "bl606p_glb.h"
#else
#error "Use CHIP BL808/BL606P for this module"
#endif

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define SYSTEM_CLOCK (32000000UL)

/*----------------------------------------------------------------------------
  System initialization function
 *----------------------------------------------------------------------------*/

void System_BOR_Init(void)
{
    //HBN_BOR_CFG_Type borCfg = {1/* pu_bor */, 0/* irq_bor_en */, 1/* bor_vth */, 1/* bor_sel */};
    //HBN_Set_BOR_Cfg(&borCfg);
}

void System_Core_Clock_Set(BL_System_Clock_Type type, uint32_t clock)
{
    Clock_Cfg_Type *pClk = (Clock_Cfg_Type *)SYS_CLOCK_CFG_ADDR;

    CHECK_PARAM(IS_BL_SYSTEM_CLOCK_TYPE(type));

    if (type < BL_SYSTEM_CLOCK_MAX) {
        pClk->systemClock[type] = clock;
        pClk->magic = SYS_CLOCK_CFG_MAGIC;
    }
}

void board_init(void)
{

}

void system_init_bl606p(void)
#if 0
{
    uint32_t i = 0;

    /* enable mstatus FS */
    uint32_t mstatus = __get_MSTATUS();
    mstatus |= (1 << 13);
    __set_MSTATUS(mstatus);

    /* enable mxstatus THEADISAEE */
    uint32_t mxstatus = __get_MXSTATUS();
    mxstatus |= (1 << 22);
    /* enable mxstatus MM */
    mxstatus |= (1 << 15);
    __set_MXSTATUS(mxstatus);

    /* get interrupt level from info */
    CLIC->CLICCFG = (((CLIC->CLICINFO & CLIC_INFO_CLICINTCTLBITS_Msk) >> CLIC_INFO_CLICINTCTLBITS_Pos) << CLIC_CLICCFG_NLBIT_Pos);

    /* Every interrupt should be clear by software*/
    for (i = 0; i < IRQn_LAST; i++) {
        CLIC->CLICINT[i].IP = 0;
        CLIC->CLICINT[i].IE = 0;
        CLIC->CLICINT[i].ATTR = 1; /* use vector interrupt */
    }

    /* tspend interrupt will be clear auto*/
    /* tspend use positive interrupt */
    CLIC->CLICINT[MSOFT_IRQn].ATTR = 0x3;

#ifdef BOOTROM
    /* i cache enable d cache disable*/
    uint32_t cache;
    __DSB();
    __ISB();
    __ICACHE_IALL();
    cache = __get_MHCR();
    cache |= CACHE_MHCR_IE_Msk;
    //cache &= ~(uint32_t)CACHE_MHCR_DE_Msk; /* disable all Cache */
    cache |= (CACHE_MHCR_DE_Msk | CACHE_MHCR_WB_Msk | CACHE_MHCR_WA_Msk | CACHE_MHCR_RS_Msk | CACHE_MHCR_BPE_Msk | CACHE_MHCR_L0BTB_Msk); /* enable all Cache */
    __set_MHCR(cache);
    __DCACHE_IALL(); /* invalidate all Cache */
    __DSB();
    __ISB();
    //csi_dcache_disable();
#else
    csi_icache_enable();
    csi_dcache_enable();
    /* enable preload $ AMR for D$ */
    __set_MHINT(0x000c);
#endif

#ifndef CONFIG_OS_SUPPORT
    /* enable mexstatus SPUSHEN and SPSWAPEN for ipush/ipop and irq stack */
    uint32_t mexstatus = __get_MEXSTATUS();
    mexstatus |= (0x03 << 16);
    __set_MEXSTATUS(mexstatus);
#else
    /* enable mexstatus SPUSHEN and SPSWAPEN for ipush/ipop and irq stack*/
    uint32_t mexstatus = __get_MEXSTATUS();
    mexstatus |= (0x3 << 16);
    __set_MEXSTATUS(mexstatus);
#endif

#ifdef BOOTROM
    extern void GLB_Power_On_LDO18_IO(void);
    extern void WDT_Disable(void);
    extern BL_Err_Type HBN_Clear_RTC_INT(void);
    uint32_t *p;
    BMX_TO_Cfg_Type bmxCfg = {
        .arbMod = BMX_ARB_FIX,
        .timeoutEn = 0x1F,
        //.errEn=DISABLE,
    };

    /* M0 boot log Flag */
    extern uint32_t __bootrom_data_section_end;
    p = (uint32_t *)(&__bootrom_data_section_end);
    *p = 0x5A5AA5A5;
    /*diable BMX error incase Sbooten=0xf,while user send vector(core) reset and CPU read deadbeef,
	if not disable this bit, CPU will also get hardfault at the same time*/
    GLB_BMX_TO_Init(&bmxCfg);
    //GLB_BMX_Addr_Monitor_Disable();

    /* Do the same for L1C BMX*/
    //L1C_BMX_Init(&l1cBmxCfg);
    //L1C_BMX_Addr_Monitor_Disable();

    /* make ram max*/
    //L1C_Set_Way_Disable(0x0f);
    //GLB_Set_EM_Sel(GLB_EM_0KB);

    /* Disable Watchdog */
    WDT_Disable();
    /* Clear RTC */
    HBN_Clear_RTC_INT();

    /*TODO*/
    /* Make OCRAM Idle from retention or sleep */
    //GLB_Set_OCRAM_Idle();
    //GLB_Set_SRAM_RET(0x0);
    //GLB_Set_SRAM_SLP(0x0);
    /* Disable embedded flash power up*/
    //HBN_Set_Embedded_Flash_Pullup(DISABLE);
#if 0
	/* disable hardware_pullup_pull_down (reg_en_hw_pu_pd = 0) */
	tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_MODE);
	tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_REG_EN_HW_PU_PD);
	BL_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

	/* Restore default setting*/
	GLB_UART_Sig_Swap_Set(UART_SIG_SWAP_NONE);
	GLB_JTAG_Sig_Swap_Set(JTAG_SIG_SWAP_NONE);

	/*Power up soc 11 power domain,TODO: This should be optional */
	//AON_Power_On_SOC_11();
	/* Record LDO18 pu flag before power up. This maybe not neccessary but copy from 606*/
	//BL_WR_WORD(BFLB_BOOTROM_AP_BOOT_LOG_ADDR,GLB->ldo18io.BF.pu_ldo18io);
	/* Power up flash power*/
	//GLB_Power_On_LDO18_IO();

#endif
#endif

    GLB_UART_Sig_Swap_Set(GLB_UART_SIG_SWAP_GRP_GPIO12_GPIO23, 1);
    GLB_UART_Sig_Swap_Set(GLB_UART_SIG_SWAP_GRP_GPIO36_GPIO45, 1);

    /* init bor for all platform */
    System_BOR_Init();
}
#else
{
    uint32_t i=0;

    /* enable mstatus FS */
    uint32_t mstatus = __get_MSTATUS();
    mstatus |= (1 << 13);
    __set_MSTATUS(mstatus);

    /* enable mxstatus THEADISAEE */
    uint32_t mxstatus = __get_MXSTATUS();
    mxstatus |= (1 << 22);
    /* enable mxstatus MM */
    mxstatus |= (1 << 15);
    __set_MXSTATUS(mxstatus);

    /* get interrupt level from info */
    CLIC->CLICCFG = (((CLIC->CLICINFO & CLIC_INFO_CLICINTCTLBITS_Msk) >> CLIC_INFO_CLICINTCTLBITS_Pos) << CLIC_CLICCFG_NLBIT_Pos);

    /* Every interrupt should be clear by software*/
    for (i = 0; i < IRQn_LAST; i++) {
        CLIC->CLICINT[i].IP = 0;
        CLIC->CLICINT[i].ATTR = 1; /* use vector interrupt */
    }

    /* tspend interrupt will be clear auto*/
    /* tspend use positive interrupt */
    CLIC->CLICINT[MSOFT_IRQn].ATTR = 0x3;

    csi_dcache_enable();
    csi_icache_enable();
    /* enable preload $ AMR for D$*/
    __set_MHINT(0x0004);
    CPU_Interrupt_Enable(MSOFT_IRQn);

    /* disable mexstatus SPUSHEN and SPSWAPEN for ipush/ipop*/
    uint32_t mexstatus = __get_MEXSTATUS();
    mexstatus &= ~(0x3 << 16);
    __set_MEXSTATUS(mexstatus);

#ifdef BOOTROM
    extern void GLB_Power_On_LDO18_IO(void);
    extern void WDT_Disable(void);
    extern void HBN_Clear_RTC_INT(void);

    BMX_Cfg_Type bmxCfg={
            .timeoutEn=0,
            .errEn=DISABLE,
            .arbMod=BMX_ARB_FIX
    };
    L1C_BMX_Cfg_Type  l1cBmxCfg={
            .timeoutEn=0,
            .errEn=DISABLE,
            .arbMod=L1C_BMX_ARB_FIX,
    };

    /* NP boot log Flag */
    p= (uint32_t *)(BFLB_BOOTROM_NP_BOOT_LOG_ADDR);
    *p=0x5A5AA5A5;
    /*diable BMX error incase Sbooten=0xf,while user send vector(core) reset and CPU read deadbeef,
    if not disable this bit, CPU will also get hardfault at the same time*/
    //GLB->bmx_cfg1.BF.bmx_err_en=0;
    //GLB->bmx_cfg1.BF.bmx_timeout_en=0;
    //GLB->bmx_cfg2.BF.bmx_err_addr_dis=1;
    GLB_BMX_Init(&bmxCfg);
    GLB_BMX_Addr_Monitor_Disable();
    //L1C->l1c_config.BF.l1c_bmx_err_en=0;
    //L1C->l1c_config.BF.l1c_bmx_timeout_en=0;
    //L1C->l1c_bmx_err_addr_en.BF.l1c_bmx_err_addr_dis=1;
    L1C_BMX_Init(&l1cBmxCfg);
    L1C_BMX_Addr_Monitor_Disable();
    //L1C->l1c_config.BF.l1c_way_dis=0xf;
    L1C_Set_Way_Disable(0x0f);
    /* Disable Watchdog */
    WDT_Disable();
    /* Clear RTC */
    HBN_Clear_RTC_INT();
    /* Make OCRAM Idle from retention or sleep */
    GLB_Set_OCRAM_Idle();
    /* Disable embedded flash power up*/
    HBN_Set_Embedded_Flash_Pullup(DISABLE);
#endif

#if 0
    /* disable hardware_pullup_pull_down (reg_en_hw_pu_pd = 0) */
    tmpVal=BL_RD_REG(HBN_BASE,HBN_IRQ_MODE);
    tmpVal=BL_CLR_REG_BIT(tmpVal,HBN_REG_EN_HW_PU_PD);
    BL_WR_REG(HBN_BASE,HBN_IRQ_MODE,tmpVal);

    GLB_Set_EM_Sel(GLB_EM_0KB);

    /* Fix 26M xtal clkpll_sdmin */
    tmpVal=BL_RD_REG(PDS_BASE,PDS_CLKPLL_SDM);
    if(0x49D39D==BL_GET_REG_BITS_VAL(tmpVal,PDS_CLKPLL_SDMIN)){
        tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_CLKPLL_SDMIN,0x49D89E);
        BL_WR_REG(PDS_BASE,PDS_CLKPLL_SDM,tmpVal);
    }

    /* Restore default setting*/
    GLB_UART_Sig_Swap_Set(UART_SIG_SWAP_NONE);
    GLB_JTAG_Sig_Swap_Set(JTAG_SIG_SWAP_NONE);

    /* CLear all interrupt */
    p=(uint32_t *)(CLIC_HART0_ADDR+CLIC_INTIE);
    for(i=0;i<(IRQn_LAST+3)/4;i++){
        p[i]=0;
    }
    p=(uint32_t *)(CLIC_HART0_ADDR+CLIC_INTIP);
    for(i=0;i<(IRQn_LAST+3)/4;i++){
        p[i]=0;
    }
#endif
    /* global IRQ disable */
    __disable_irq();

    //__asm volatile("csrw mnxti, %0" : : "i"(0x1 << 3));
    /* init bor for all platform */
    //system_bor_init();

#ifdef BOOTROM
    /*Power up soc 11 power domain,TODO: This should be optional */
    //AON_Power_On_SOC_11();
    /* Record LDO18 pu flag before power up. This maybe not neccessary but copy from 606*/
    //BL_WR_WORD(BFLB_BOOTROM_AP_BOOT_LOG_ADDR,GLB->ldo18io.BF.pu_ldo18io);
    /* Power up flash power*/
    //GLB_Power_On_LDO18_IO();
#endif

}
#endif

void System_Post_Init(void)
{
#ifndef BOOTROM
    //PDS_Power_On_MM_System();
    //FIXME
    GLB_Set_EM_Sel(1);
#endif

    System_Interrupt_Init();

    CPU_Interrupt_Enable(MSOFT_IRQn);

#ifndef BOOTROM
    /* global IRQ enable */
    __enable_irq();
#endif
}

void System_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
    csi_vic_set_prio(IRQn, PreemptPriority);
}

int32_t drv_get_cpu_id(void)
{
    return __get_MHARTID();
}

int32_t drv_get_cpu_freq(int32_t idx)
{
    return 32 * 1000 * 1000UL;
}

#if defined(DUAL_CORE)
extern void Reset_Handler(void);
#endif

/**
  \brief       enable irq.
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
__attribute__((weak)) void CPU_Interrupt_Enable(uint32_t irq_num)
{
    if (irq_num >= IRQn_LAST) {
        // MSG("Error! This interrupt don't support!\n");
    } else {
#ifdef CONFIG_SYSTEM_SECURE
        csi_vic_enable_sirq(irq_num);
#else
        csi_vic_enable_irq(irq_num);
#endif
    }
}

/**
  \brief       disable irq.
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
__attribute__((weak)) void CPU_Interrupt_Disable(uint32_t irq_num)
{
    if (irq_num >= IRQn_LAST) {
        //MSG("Error! This interrupt don't support!\n");
    } else {
#ifdef CONFIG_SYSTEM_SECURE
        csi_vic_disable_sirq(irq_num);
#else
        csi_vic_disable_irq(irq_num);
#endif
    }
}

/**
  \brief   Clear Pending Interrupt
  \details Clear the pending bit of an external interrupt.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__attribute__((weak)) void CPU_Interrupt_Pending_Clear(uint32_t irq_num)
{
    if (irq_num >= IRQn_LAST) {
        //MSG("Error! This interrupt don't support!\n");
        return;
    } else {
#ifdef CONFIG_SYSTEM_SECURE
        csi_vic_clear_pending_irq(irq_num);
#else
        csi_vic_clear_pending_irq(irq_num);
#endif
    }
}
