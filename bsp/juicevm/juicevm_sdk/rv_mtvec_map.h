/*
 * Copyright (c) 2006-2021, JuiceVm Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021/04/22     Juice        the first version
 */
#ifndef __RV_MTVEC_MAP_H__
#define __RV_MTVEC_MAP_H__
#include "rv_config.h"

#define rv_sim_pdev_base_addr           (RV_CPU_SIM_RAM_START_ADDR+RV_CPU_SIM_RAM_SIZE)
#define rv_sim_pdev_uart0_base_addr     (rv_sim_pdev_base_addr)
#define pdev_uart0_write_addr     (rv_sim_pdev_uart0_base_addr)
#define pdev_uart0_read_addr      (rv_sim_pdev_uart0_base_addr+1)
#define pdev_uart0_free_state      0x00
#define pdev_uart0_readbusy_state      0x01
#define pdev_uart0_state_addr      (rv_sim_pdev_uart0_base_addr+2)

#define rv_sim_pdev_mtime_base_addr     (rv_sim_pdev_base_addr+3)
#define pdev_mtime_mtime_addr           (rv_sim_pdev_mtime_base_addr)
#define pdev_mtime_mtimecmp_addr        (rv_sim_pdev_mtime_base_addr+4)

#define uart0_irq_flag        0
#define uart0_irq_ecode       24

#define RV_exception_Instruction_address_misaligned_IFLAG                         0
#define RV_exception_Instruction_address_misaligned_ECODE                         0
#define RV_exception_Instruction_access_fault_IFLAG                               0
#define RV_exception_Instruction_access_fault_ECODE                               1
#define RV_exception_Illegal_Instruction_IFLAG                          0
#define RV_exception_Illegal_Instruction_ECODE                          2
#define RV_exception_Breakpoint_IFLAG                                   0
#define RV_exception_Breakpoint_ECODE                                   3
#define RV_exception_LoadAddress_Misaligned_IFLAG                       0
#define RV_exception_LoadAddress_Misaligned_ECODE                       4
#define RV_exception_Load_access_fault_IFLAG                            0
#define RV_exception_Load_access_fault_ECODE                            5

#define RV_exception_Store_or_AMO_Address_Misaligned_IFLAG              0
#define RV_exception_Store_or_AMO_Address_Misaligned_ECODE              6

#define RV_exception_Store_or_AMO_access_fault_IFLAG                    0
#define RV_exception_Store_or_AMO_access_fault_ECODE                    7

#define RV_exception_Environment_call_from_Umode_IFLAG                  0
#define RV_exception_Environment_call_from_Umode_ECODE                  8

#define RV_exception_Environment_call_from_Smode_IFLAG                  0
#define RV_exception_Environment_call_from_Smode_ECODE                  9

#define RV_exception_Environment_Call_FromMachine_IFLAG                 0
#define RV_exception_Environment_Call_FromMachine_ECODE                 11

#define RV_exception_FloatingPoint_Disabled_IFLAG
#define RV_exception_FloatingPoint_Disabled_ECODE

#define RV_exception_Instruction_page_fault_IFLAG                       0
#define RV_exception_Instruction_page_fault_ECODE                       12
#define RV_exception_Load_page_fault_IFLAG                              0
#define RV_exception_Load_page_fault_ECODE                              13

#define RV_exception_Store_or_AMO_page_fault_IFLAG                       0
#define RV_exception_Store_or_AMO_page_fault_ECODE                      15


// Interrupt Exception Code Description
// 1 0  Reserved
// 1 1  Supervisor software interrupt       not support
// 1 2  Reserved
// 1 3  Machine software interrupt          not support
// 1 4  Reserved
// 1 5  Supervisor timer interrupt          not support
// 1 6  Reserved
// 1 7  Machine timer interrupt             support
// 1 8  Reserved
// 1 9  Supervisor external interrupt       not support
// 1 10 Reserved
// 1 11 Machine external interrupt          not support
// 1 12 Reserved
// 1 13 Reserved
// 1 14 Reserved
// 1 15 Reserved
// // 1 ≥16 Designated for platform use
// 0 0 Instruction address misaligned       not support
// 0 1 Instruction access fault             not support
// 0 2 Illegal instruction                  support
// 0 3 Breakpoint                           support
// 0 4 Load address misaligned              support
// 0 5 Load access fault                    not support
// 0 6 Store/AMO address misaligned         support
// 0 7 Store/AMO access fault               not support
// 0 8 Environment call from U-mode         not support
// 0 9 Environment call from S-mode         not support
// 0 10 Reserved
// 0 11 Environment call from M-mode        support
// 0 12 Instruction page fault              not support
// 0 13 Load page fault                     not support
// 0 14 Reserved
// 0 15 Store/AMO page fault                not support
// 0 16-23 Reserved
// // 0 24–31 Designated for custom use
// 0 32-47 Reserved
// // 0 48–63 Designated for custom use
// 0 ≥64 Reserved


// #define mtime_irq_flag        1
// #define mtime_irq_ecode       7

#define RV_Supervisor_software_interrupt_IFLAG                           1
#define RV_Supervisor_software_interrupt_ECODE                           1

#define RV_Machine_software_interrupt_IFLAG                              1
#define RV_Machine_software_interrupt_ECODE                              3

#define RV_Supervisor_timer_interrupt_IFLAG                              1
#define RV_Supervisor_timer_interrupt_ECODE                              5

#define RV_Machine_timer_interrupt_IFLAG                                 1
#define RV_Machine_timer_interrupt_ECODE                                 7

#define RV_Supervisor_external_interrupt_IFLAG                           1
#define RV_Supervisor_external_interrupt_ECODE                           9

#define RV_Machine_external_interrupt_IFLAG                              1
#define RV_Machine_external_interrupt_ECODE                             10

#endif // __RV_MTVEC_MAP_H__
