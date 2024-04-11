#ifndef PHYTIUM_INTERRUPT_H
#define PHYTIUM_INTERRUPT_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "rtconfig.h"
#if defined(TARGET_ARMV8_AARCH64)
void phytium_interrupt_init(void);

int phytium_aarch64_arm_gic_redist_init(void);
#endif
#ifdef __cplusplus
}
#endif
#endif