#include "bl616_clock.h"
#include "bl616_pds.h"
#include "tzc_sec_reg.h"
#include "rv_hart.h"
#include "rv_pmp.h"

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
    //tmpVal |= 1<<(region+24);
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMB_TZSRG_CTRL, tmpVal);
}
static void Tzc_Sec_ROM_Access_Set_Not_Lock(uint8_t region, uint32_t startAddr, uint32_t length, uint8_t group)
{
    uint32_t tmpVal = 0;
    uint32_t alignEnd = (startAddr + length + 1023) & ~0x3FF;

    /* check the parameter */
    group = group & 0xf;

    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_TZSRG_CTRL);
    tmpVal &= (~(0xf << (region * 4)));
    tmpVal |= (group << (region * 4));
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_TZSRG_CTRL, tmpVal);

    tmpVal = (((alignEnd >> 10) & 0xffff) - 1) | (((startAddr >> 10) & 0xffff) << 16);
    BL_WR_WORD(TZC_SEC_BASE + TZC_SEC_TZC_ROM_TZSRG_R0_OFFSET + region * 4, tmpVal);

    /* set enable and lock */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_TZSRG_CTRL);
    tmpVal |= 1 << (region + 16);
    // tmpVal |= 1 << (region + 24);
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_TZSRG_CTRL, tmpVal);
}
static void pmp_init(void)
{
    const pmp_config_entry_t pmp_entry_tab[6] = {
        /* no access 0x00000000-0x20000000*/
        [0] = {
            .entry_flag = ENTRY_FLAG_ADDR_NAPOT | ENTRY_FLAG_M_MODE_L,
            .entry_pa_base = 0x00000000,
            .entry_pa_length = PMP_REG_SZ_512M,
        },
        /* no access 0x40000000-0x60000000*/
        [1] = {
            .entry_flag = ENTRY_FLAG_ADDR_NAPOT | ENTRY_FLAG_M_MODE_L,
            .entry_pa_base = 0x40000000,
            .entry_pa_length = PMP_REG_SZ_512M,
        },
        /* no access 0x70000000-0x80000000*/
        [2] = {
            .entry_flag = ENTRY_FLAG_ADDR_NAPOT | ENTRY_FLAG_M_MODE_L,
            .entry_pa_base = 0x70000000,
            .entry_pa_length = PMP_REG_SZ_256M,
        },
        /* no access 0x80000000-0x90000000*/
        [3] = {
            .entry_flag = ENTRY_FLAG_ADDR_NAPOT | ENTRY_FLAG_M_MODE_L,
            .entry_pa_base = 0x80000000,
            .entry_pa_length = PMP_REG_SZ_256M,
        },
        /* no access 0xB0000000-0xC0000000*/
        [4] = {
            .entry_flag = ENTRY_FLAG_ADDR_NAPOT | ENTRY_FLAG_M_MODE_L,
            .entry_pa_base = 0xB0000000,
            .entry_pa_length = PMP_REG_SZ_256M,
        },
        /* no access 0xC0000000-0xE0000000*/
        [5] = {
            .entry_flag = ENTRY_FLAG_ADDR_NAPOT | ENTRY_FLAG_M_MODE_L,
            .entry_pa_base = 0xC0000000,
            .entry_pa_length = PMP_REG_SZ_512M,
        }
    };
    rvpmp_init(pmp_entry_tab, sizeof(pmp_entry_tab) / sizeof(pmp_config_entry_t));
}

void SystemInit(void)
{
    uint32_t i = 0;

    /* CPU Prefetching barrier */
    Tzc_Sec_PSRAMB_Access_Set_Not_Lock(0, 0x0, 64 * 1024 * 1024, 0);
    Tzc_Sec_ROM_Access_Set_Not_Lock(1, 0x90020000, ((256 * 1024 * 1024) - (128 * 1024)), 0);
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
        CLIC->CLICINT[i].IE = 0;
        CLIC->CLICINT[i].IP = 0;
        CLIC->CLICINT[i].ATTR = 1; /* use vector interrupt */
    }

    /* tspend interrupt will be clear auto*/
    /* tspend use positive interrupt */
    CLIC->CLICINT[MSOFT_IRQn].ATTR = 0x3;

    csi_dcache_enable();
    csi_icache_enable();

    /* disable mexstatus SPUSHEN and SPSWAPEN for ipush/ipop*/
    uint32_t mexstatus = __get_MEXSTATUS();
    mexstatus &= ~(0x3 << 16);
    __set_MEXSTATUS(mexstatus);

    BL_WR_REG(GLB_BASE, GLB_UART_CFG1, 0xffffffff);
    BL_WR_REG(GLB_BASE, GLB_UART_CFG2, 0x0000ffff);
}

void System_Post_Init(void)
{
    /* Bootrom not use dcache,so ignore this flush*/
#ifndef BOOTROM
    csi_dcache_clean();
    csi_icache_invalid();
#endif

    /* global IRQ enable */
    __enable_irq();
}
