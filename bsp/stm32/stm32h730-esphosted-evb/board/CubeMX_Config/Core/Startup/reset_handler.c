//
// Created by yekai on 2024/7/3.
//

#include <string.h>
#include "stdint.h"

extern void SystemInit(void);

extern int entry(void);

#pragma GCC push_options
#pragma GCC optimize ("O0")

extern volatile uint32_t _ramfunc_start_lma;
extern volatile uint32_t _ramfunc_start_vma;
extern volatile uint32_t _ramfunc_end;

extern volatile uint32_t _data_start_lma;
extern volatile uint32_t _data_start_vma;
extern volatile uint32_t _data_end;

extern volatile uint32_t _sbss;
extern volatile uint32_t _ebss;

__attribute__((used, section(".text.reset_handler")))
void Reset_Handler(void) {
    __asm volatile ("ldr sp, =_estack");
    volatile uint32_t *pui32Src;
    volatile uint32_t *pui32Dest;

    // copy itcm
    for (pui32Src = &_ramfunc_start_lma, pui32Dest = &_ramfunc_start_vma;
         pui32Dest < &_ramfunc_end;
         pui32Src++, pui32Dest++) {
        *pui32Dest = *pui32Src;
    }

    // copy data
    for (pui32Src = &_data_start_lma, pui32Dest = &_data_start_vma;
         pui32Dest < &_data_end;
         pui32Src++, pui32Dest++
        ) {
        *pui32Dest = *pui32Src;
    }

    // init bss
    for (pui32Dest = &_sbss;
         pui32Dest < &_ebss;
         pui32Dest++
        ) {
        *pui32Dest = 0;
    }

    SystemInit();

    entry();
}

#pragma GCC pop_options
