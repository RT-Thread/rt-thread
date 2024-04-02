#ifndef PHYTIUM_INTERRUPT_H
#define PHYTIUM_INTERRUPT_H

#ifdef __cplusplus
extern "C"
{
#endif

void phytium_interrupt_init(void);

int phytium_aarch64_arm_gic_redist_init(void);

#ifdef __cplusplus
}
#endif
#endif