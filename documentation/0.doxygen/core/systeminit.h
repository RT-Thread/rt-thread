/*
 * This file is only used for doxygen document generation.
 */

/**
 * @ingroup group_system_init
 *
 * This function will initialize user application.
 *
 * This function will be invoked when system initialization and system scheduler
 * has not started. User can allocate memory, create thread, semaphore etc. However,
 * user shall not suspend 'current' thread.
 */
void rt_application_init();

/**
 * @ingroup group_system_init
 */
void rt_system_heap_init(void* begin_addr, void* end_addr);
