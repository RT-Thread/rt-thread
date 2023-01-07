#include <stdint.h>
#include <core_rv32.h>
#define __STARTUP_CLEAR_BSS             1

/*----------------------------------------------------------------------------
  Linker generated Symbols
 *----------------------------------------------------------------------------*/
extern uint32_t __itcm_load_addr;
extern uint32_t __dtcm_load_addr;
extern uint32_t __system_ram_load_addr;
extern uint32_t __psram_ram_load_addr;
extern uint32_t __ram_load_addr;

extern uint32_t __text_code_start__;
extern uint32_t __text_code_end__;
extern uint32_t __tcm_code_start__;
extern uint32_t __tcm_code_end__;
extern uint32_t __tcm_data_start__;
extern uint32_t __tcm_data_end__;
extern uint32_t __system_ram_data_start__;
extern uint32_t __system_ram_data_end__;
extern uint32_t __psram_ram_data_start__;
extern uint32_t __psram_ram_data_end__;
extern uint32_t __ram_data_start__;
extern uint32_t __ram_data_end__;
extern uint32_t __wifi_bss_start;
extern uint32_t __wifi_bss_end;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern uint32_t __ocram_bss_start__;
extern uint32_t __ocram_bss_end__;
extern uint32_t __noinit_data_start__;
extern uint32_t __noinit_data_end__;

extern uint32_t __StackTop;
extern uint32_t __StackLimit;
extern uint32_t __HeapBase;
extern uint32_t __HeapLimit;

//extern uint32_t __copy_table_start__;
//extern uint32_t __copy_table_end__;
//extern uint32_t __zero_table_start__;
//extern uint32_t __zero_table_end__;


void start_load(void) {
    uint32_t *pSrc, *pDest;
    /*boot2 dcache is enable need disable*/
    csi_dcache_disable();

    /* Copy ITCM code */
    pSrc  = &__itcm_load_addr;
    pDest = &__tcm_code_start__;
    for ( ; pDest < &__tcm_code_end__ ; ) {
        *pDest++ = *pSrc++;
    }

    /* Copy DTCM code */
    pSrc  = &__dtcm_load_addr;
    pDest = &__tcm_data_start__;
    for( ; pDest < &__tcm_data_end__; ){
        *pDest++ = *pSrc++;
    }

    /* BF Add system RAM data copy */
    pSrc  = &__system_ram_load_addr;
    pDest = &__system_ram_data_start__;
    for ( ; pDest < &__system_ram_data_end__ ; ) {
        *pDest++ = *pSrc++;
    }

    /* BF Add OCARAM data copy */
    pSrc  = &__ram_load_addr;
    pDest = &__ram_data_start__;
    for ( ; pDest < &__ram_data_end__ ; ) {
        *pDest++ = *pSrc++;
    }

#ifdef __STARTUP_CLEAR_BSS
    /*
     *  The BSS section is specified by following symbols
     *    __bss_start__: start of the BSS section.
     *    __bss_end__: end of the BSS section.
     *
     *  Both addresses must be aligned to 4 bytes boundary.
     */
    pDest = &__bss_start__;
    for ( ; pDest < &__bss_end__ ; ) {
        *pDest++ = 0ul;
    }

    pDest = &__wifi_bss_start;
    for ( ; pDest < &__wifi_bss_end ; ) {
        *pDest++ = 0ul;
    }

    pDest = &__ocram_bss_start__;
    for ( ; pDest < &__ocram_bss_end__ ; ) {
        *pDest++ = 0ul;
    }
#endif

    /* BF Add PSRAM RAM data copy */
    pSrc  = &__psram_ram_load_addr;
    pDest = &__psram_ram_data_start__;
    for ( ; pDest < &__psram_ram_data_end__ ; ) {
        *pDest++ = *pSrc++;
    }
}
