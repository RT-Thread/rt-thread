/*
 * This file is only used for doxygen document generation.
 */

/**
 * @defgroup group_kernel_core Kernel
 *
 * Core of RT-Thread, see @ref page_kernel_core for more details.
 */

/**
 * @addtogroup group_kernel_core
 * @{
 */

/**
 * @defgroup group_object_management Object Management
 * @brief See @ref page_object_management
 *
 * The Kernel object system can access and manage all of the kernel objects.
 *
 * Kernel objects include most of the facilities in the kernel:
 * - thread
 * - semaphore and mutex
 * - event/fast event, mailbox, messagequeue
 * - memory pool
 * - timer
 * @image html Kernel_Object.png "Figure 2: Kernel Object"
 * @image rtf  Kernel_Object.png "Figure 2: Kernel Object"
 *
 * Kernel objects can be static objects, whose memory is allocated in compiling.
 * It can be dynamic objects as well, whose memory is allocated from system heaps
 * in runtime.
 */

/**
 * @defgroup group_thread_management Thread Management
 * @brief See @ref page_thread_management
 */

/**
 * @defgroup group_clock_management Clock and Timer Management
 * @brief See @ref page_clock_management
 */

/**
 * @defgroup group_thread_comm Inter-Thread Communication
 * @brief See @ref page_thread_comm
 */

/**
 * @defgroup group_memory_management Memory Management
 * @brief memory management for memory pool and heap memory
 *
 * RT-Thread operating system supports two types memory management:
 * - Static memory pool management
 * - Dynamic memory heap management.
 *
 * The time to allocate a memory block from the memory pool is determinant. When
 * the memory pool is empty, the allocated thread can be blocked (or immediately return,
 * or waiting for sometime to return, which are determined by a timeout parameter).
 * When other thread releases memory blocks to this memory pool, the blocked thread is
 * wake up.
 *
 * There are two methods in dynamic memory heap management, one is used for small memory,
 * such as less than 1MB.  Another is a SLAB like memory management, which is suitable
 * for large memory system. All of them has no real-time character.
 */

/**
 * @defgroup group_hook Runtime Trace and Record
 * @brief the hook function set in runtime
 *
 * In order to trace and record RT-Thread activity in runtime, a hook mechanism
 * is introduced.
 *
 * The hooks are a series of routines, which are invoked in some special checkpoints.
 * The hook routines include:
 * - object hook, invoked at object created, deleted, taken and put etc.
 * - scheduler hook, invoked at thread switch and idle thread loop.
 * - memory hook, invoked when allocate or free memory block.
 * - timer hook, invoked when timer is timeout.
 */

/**
 * @defgroup group_kernel_service Other useful kernel service
 * @brief other useful service in the kernel
 */

/**
 * @defgroup group_error Error Code
 * @brief error code
 *
 * The error code is defined to identify which kind of error occurs. When some
 * bad things happen, the current thread's errno will be set.
 */

/**
 * @defgroup group_system_init System Initialization
 *
 * @brief System initialization procedure.
 *
 * When RT-Thread operating system starts up, the basic operating system facility
 * initialization routines must be invoked.
 *
 * The suggested initialization sequence is:
 *
 * - initialize device hardware
 * rt_hw_board_init();
 *
 * User can put the low level hardware initialization in this function, such as
 * DDR memory setting, pinmux setting, console device setting etc.
 *
 * - show version
 * rt_show_version();
 *
 * - initialize timer system
 * rt_system_timer_init();
 *
 * - initialize system heap memory
 * rt_system_heap_init(__bss_end, __end_of_memory);
 *
 * - initialize module system
 * rt_system_module_init();
 *
 * - initialize scheduler system
 * rt_system_scheduler_init();
 *
 * - initialize application
 * rt_application_init();
 *
 * - initialize system timer thread
 * rt_system_timer_thread_init();
 *
 * - initialize idle thread
 * rt_thread_idle_init();
 *
 * - start scheduler
 * rt_system_scheduler_start();
 */

/**@}*/
