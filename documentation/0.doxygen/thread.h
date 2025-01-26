/*
 * This file is only used for doxygen document generation.
 */

/**
 * @addtogroup Thread
 * @{
 */

/**
 * @brief This function will handle IPI interrupt and do a scheduling in system.
 *
 * @param vector is the number of IPI interrupt for system scheduling.
 *
 * @param param is not used, and can be set to RT_NULL.
 *
 * @note this function should be invoke or register as ISR in BSP.
 *
 * @note this function is only implemented in scheduler_mp.c.
 */
void rt_scheduler_ipi_handler(int vector, void *param);

/**
 * @brief This function will perform one scheduling. It will select one thread
 *        with the highest priority level in global ready queue or local ready queue,
 *        then switch to it.
 *
 * @note this function is implemented in both scheduler_up.c and scheduler_mp.c.
 */
void rt_schedule(void);

/**
 * @brief This function checks whether a scheduling is needed after an IRQ context switching. If yes,
 *        it will select one thread with the highest priority level, and then switch
 *        to it.
 *
 * @param context is the context to be switched to.
 *
 * @note this function is only implemented in scheduler_mp.c.
 */
void rt_scheduler_do_irq_switch(void *context);

/**
 * @brief This function will insert a thread to the system ready queue. The state of
 *        thread will be set as READY and the thread will be removed from suspend queue.
 *
 * @param thread is the thread to be inserted.
 *
 * @note  Please do not invoke this function in user application.
 *
 * @note this function is implemented in both scheduler_up.c and scheduler_mp.c.
 */
void rt_schedule_insert_thread(struct rt_thread *thread);

/**
 * @brief This function will remove a thread from system ready queue.
 *
 * @param thread is the thread to be removed.
 *
 * @note  Please do not invoke this function in user application.
 *
 * @note this function is implemented in both scheduler_up.c and scheduler_mp.c.
 */
void rt_schedule_remove_thread(struct rt_thread *thread);

/**
 * @brief This function will lock the thread scheduler.
 *
 * @note this function is implemented in both scheduler_up.c and scheduler_mp.c.
 */
void rt_enter_critical(void);

/**
 * @brief This function will unlock the thread scheduler.
 *
 * @note this function is implemented in both scheduler_up.c and scheduler_mp.c.
 */
void rt_exit_critical(void);

/**
 * @brief Get the scheduler lock level.
 *
 * @return the level of the scheduler lock. 0 means unlocked.
 *
 * @note this function is implemented in both scheduler_up.c and scheduler_mp.c.
 */
rt_uint16_t rt_critical_level(void);

/**@}*/
