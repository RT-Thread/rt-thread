/*
 * This file is only used for doxygen document generation.
 */

/**
 * @mainpage Introduction
 * @author RT-Thread Development Team
 * @version 1.2.0
 *
 * RT-Thread RTOS is an open source embedded real-time operating system and is
 * designed specifically for small memory footprint platforms. The real-time and
 * embedded characters are the most significant advantages of RT-Thread.
 *
 * - Real-Time Character
 *
 * RT-Thread has a real-time operating system kernel, with fully preempted
 * multi-thread scheduler, inter-thread communication with timing sensitivity
 * and transparent interrupt handling.
 *
 * - Embedded Character
 *
 * RT-Thread is suitable for embedded systems for small footprint characters.
 * The kernel is implemented as a simple C library. The simplest application
 * costs less than 1 Kbytes RAM on the ARM Cortex-M platform.
 *
 * @section kernel_arch RT-Thread Architecture
 *
 * RT-Thread system architecture is like:
 * @image html System_Arch.png "Figure 1: RT-Thread Architecture"
 *
 * @section kernel_service Kernel API
 *
 * The Kernel APIs are the core APIs of RT-Thread, which supports the following
 * features:
 * - Multi-thread management and scheduler
 * - Synchronization mechanisms, semaphore, recursive mutex and event set
 * - Inter-thread communication, mailbox and message queue
 * - Memory management, memory pool and dynamic heap memory management
 * - Asynchronous timer
 *
 * For more details, please refer to @ref Kernel
 *
 * @section system_init System Initialization
 *
 * Once RT-Thread operating system starts up, the facility in system must be initialized
 * firstly.
 *
 * For more details, please refer to @ref SystemInit
 */
