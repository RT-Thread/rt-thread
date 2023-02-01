#include "bl808.h"
#include "bl808_clock.h"
#include "bl808_pds.h"
#include "tzc_sec_reg.h"
#include "rv_hart.h"
#include "rv_pmp.h"

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define SYSTEM_CLOCK (32000000UL)

/*----------------------------------------------------------------------------
  System initialization function
 *----------------------------------------------------------------------------*/

__WEAK__ void System_Environment_Init(void)
{
    csi_icache_enable();
    csi_dcache_enable();

    /* enable preload $ AMR for D$ */
    __set_MHINT(0x000c);
}

void System_BOR_Init(void)
{
    //HBN_BOR_CFG_Type borCfg = {1/* pu_bor */, 0/* irq_bor_en */, 1/* bor_vth */, 1/* bor_sel */};
    //HBN_Set_BOR_Cfg(&borCfg);
}

static void Tzc_Sec_PSRAMA_Access_Set_Not_Lock(uint8_t region, uint32_t startAddr, uint32_t endAddr, uint8_t group)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMA_TZSRG_CTRL);
    tmpVal &= (~(3 << (region * 2)));
    tmpVal |= (group << (region * 2));
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMA_TZSRG_CTRL, tmpVal);

    tmpVal = ((((endAddr >> 10) & 0xffff) - 1) & 0xffff) | (((startAddr >> 10) & 0xffff) << 16);
    BL_WR_WORD(TZC_SEC_BASE + TZC_SEC_TZC_PSRAMA_TZSRG_R0_OFFSET + region * 4, tmpVal);

    /* set enable but not lock */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMA_TZSRG_CTRL);
    tmpVal |= 1 << (region + 16);
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMA_TZSRG_CTRL, tmpVal);
}

static void Tzc_Sec_PSRAMB_Access_Set_Not_Lock(uint8_t region, uint32_t startAddr, uint32_t endAddr, uint8_t group)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMB_TZSRG_CTRL);
    tmpVal &= (~(3 << (region * 2)));
    tmpVal |= (group << (region * 2));
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMB_TZSRG_CTRL, tmpVal);

    tmpVal = ((((endAddr >> 10) & 0xffff) - 1) & 0xffff) | (((startAddr >> 10) & 0xffff) << 16);
    BL_WR_WORD(TZC_SEC_BASE + TZC_SEC_TZC_PSRAMB_TZSRG_R0_OFFSET + region * 4, tmpVal);

    /* set enable but not lock */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMB_TZSRG_CTRL);
    tmpVal |= 1 << (region + 16);
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMB_TZSRG_CTRL, tmpVal);
}

static void pmp_init(void)
{
    const pmp_config_entry_t pmp_entry_tab[1] = {
        /* no access */
        [0] = {
            .entry_flag = ENTRY_FLAG_ADDR_NAPOT | ENTRY_FLAG_M_MODE_L,
            .entry_pa_base = 0x80000000,
            .entry_pa_length = PMP_REG_SZ_256M,
        }
    };
    rvpmp_init(pmp_entry_tab, sizeof(pmp_entry_tab) / sizeof(pmp_config_entry_t));
}

void System_Init(void)
{
    uint32_t i = 0;

    /* CPU Prefetching barrier */
    Tzc_Sec_PSRAMA_Access_Set_Not_Lock(0, 0x0, 64 * 1024 * 1024, 0);
    Tzc_Sec_PSRAMB_Access_Set_Not_Lock(0, 0x0, 64 * 1024 * 1024, 0);
    pmp_init();

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

    System_Environment_Init();

    /* init bor for all platform */
    System_BOR_Init();

    GLB_Set_EM_Sel(GLB_WRAM160KB_EM0KB);
}

__WEAK__ void System_Post_Init(void)
{
    PDS_Power_On_MM_System();

    BL_WR_REG(GLB_BASE, GLB_UART_CFG1, 0xffffffff);
    BL_WR_REG(GLB_BASE, GLB_UART_CFG2, 0x0000ffff);

    /* make D0 all ram avalable for mcu usage */
    GLB_Set_DSP_L2SRAM_Available_Size(3, 1, 1, 1);

    System_Interrupt_Init();

    CPU_Interrupt_Enable(MSOFT_IRQn);

    /* global IRQ enable */
    __enable_irq();
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
