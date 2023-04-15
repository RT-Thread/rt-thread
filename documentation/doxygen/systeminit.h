/*
 * This file is only used for doxygen document generation.
 */

/**
 * @defgroup SystemInit System Initialization
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

/**
 * @ingroup SystemInit
 *
 * This function will initialize user application.
 *
 * This function will be invoked when system initialization and system scheduler
 * has not started. User can allocate memory, create thread, semaphore etc. However,
 * user shall not suspend 'current' thread.
 */
void rt_application_init();

/**
 * @ingroup SystemInit
 */
void rt_system_heap_init(void* begin_addr, void* end_addr);
