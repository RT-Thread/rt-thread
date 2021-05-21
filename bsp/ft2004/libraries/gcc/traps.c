/*
 * @Author: your name
 * @Date: 2021-02-24 09:28:38
 * @LastEditTime: 2021-02-24 09:40:25
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \freertos\devices\ft2004\gcc\traps.c
 */

#include "ft_aarch32_asm.h"
#include "ft_debug.h"
#define TRAPS_DEBUG_TAG "TRAPS"

#define TRAPS_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(TRAPS_DEBUG_TAG, format, ##__VA_ARGS__)
#define TRAPS_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(TRAPS_DEBUG_TAG, format, ##__VA_ARGS__)
#define TRAPS_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(TRAPS_DEBUG_TAG, format, ##__VA_ARGS__)

void Ft_Arrch32_Registers(struct ft_hw_exp_stack *Regs)
{
    TRAPS_DEBUG_E("Execption:\n");
    TRAPS_DEBUG_E("r00:0x%08x r01:0x%08x r02:0x%08x r03:0x%08x\n", Regs->r0, Regs->r1, Regs->r2, Regs->r3);
    TRAPS_DEBUG_E("r04:0x%08x r05:0x%08x r06:0x%08x r07:0x%08x\n", Regs->r4, Regs->r5, Regs->r6, Regs->r7);
    TRAPS_DEBUG_E("r08:0x%08x r09:0x%08x r10:0x%08x\n", Regs->r8, Regs->r9, Regs->r10);
    TRAPS_DEBUG_E("fp :0x%08x ip :0x%08x\n", Regs->fp, Regs->ip);
    TRAPS_DEBUG_E("sp :0x%08x lr :0x%08x pc :0x%08x\n", Regs->sp, Regs->lr, Regs->pc);
    TRAPS_DEBUG_E("cpsr:0x%08x\n", Regs->cpsr);
}

void Ft_Arrch32_trap_dabt(struct ft_hw_exp_stack *Regs)
{
    TRAPS_DEBUG_E("data abort:");
    Ft_Arrch32_Registers(Regs);
    while (1)
        ;
}
