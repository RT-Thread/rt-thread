#include "bl808_clock.h"
#include "bl808_ef_cfg.h"

#define BL808_B0 (0x0)
#define BL808_B1 (0x1)

void SystemInit(void)
{
    uintptr_t tmpVal = 0;

    while ((BL_RD_WORD(IPC_SYNC_ADDR1) != IPC_SYNC_FLAG) ||
           (BL_RD_WORD(IPC_SYNC_ADDR2) != IPC_SYNC_FLAG)) {
        // clang-format off
        __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP();
        // clang-format on
        /* if cache is off, comment this and this api need to start load itcm*/
        // L1C_DCache_Invalid_By_Addr(IPC_SYNC_ADDR1, 8);
    };
    /* clear this flags for system reboot */
    BL_WR_WORD(IPC_SYNC_ADDR1, 0x0);
    BL_WR_WORD(IPC_SYNC_ADDR2, 0x0);

    /* turn on cache to speed up boot sequence */
    csi_icache_enable();
    csi_dcache_enable();

    /* enable I/D Cache preload. */
    tmpVal = __get_MHINT();
    tmpVal |= (1 << 8) | (1 << 2);
    /* clear AMR */
    tmpVal &= (~0x18);
    __set_MHINT(tmpVal);
}

void System_Post_Init(void)
{
    csi_dcache_clean();
    csi_icache_invalid();

    /* fix amr setting */
    uintptr_t tmpVal = 0;
    bflb_efuse_device_info_type chip_info;
    bflb_ef_ctrl_get_device_info(&chip_info);
    /* if not B0 enable AMR */
    if (chip_info.chipInfo != BL808_B0) {
        tmpVal = __get_MHINT();
        tmpVal |= (1 << 3);
        __set_MHINT(tmpVal);
    }

    /* global IRQ enable */
    __enable_irq();
}