#ifndef _RISCV_ARCH_H
#define _RISCV_ARCH_H

#define getreg8(a)                         (*(volatile uint8_t *)(uintptr_t)(a))
#define putreg8(v, a)                      (*(volatile uint8_t *)(uintptr_t)(a) = (v))
#define getreg16(a)                        (*(volatile uint16_t *)(uintptr_t)(a))
#define putreg16(v, a)                     (*(volatile uint16_t *)(uintptr_t)(a) = (v))
#define getreg32(a)                        (*(volatile uint32_t *)(uintptr_t)(a))
#define putreg32(v, a)                     (*(volatile uint32_t *)(uintptr_t)(a) = (v))
// #define getreg64(a)                        (*(volatile uint64_t *)(a))
// #define putreg64(v, a)                     (*(volatile uint64_t *)(a) = (v))
// #define modifyreg32(a, clearbits, setbits) putreg32((getreg32(a) & (~clearbits)) | setbits, a)

#endif