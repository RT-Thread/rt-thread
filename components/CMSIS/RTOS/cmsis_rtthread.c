#include "cmsis_os.h"

// Kernel Control Public API

/// Start the RTOS Kernel with executing the specified thread
osStatus osKernelStart(osThreadDef_t *thread_def, void *argument)
{
	osThreadCreate(thread_def, argument);

	rt_system_scheduler_start();

	return osOK;
}

/// Check if the RTOS kernel is already started
int32_t osKernelRunning(void)
{
	return (rt_thread_self() != RT_NULL) ?  1 : 0;
}

// Thread Public API

/// Create a thread and add it to Active Threads and set it to state READY
osThreadId osThreadCreate(osThreadDef_t *thread_def, void *argument)
{
	osThreadId thread;
	
	thread = rt_thread_create(thread_def->name, thread_def->entry, argument, thread_def->stack_size, thread_def->priority, thread_def->tick);	
	if (thread != RT_NULL)
        rt_thread_startup(thread); 	

	return thread;
}

/// Return the thread ID of the current running thread
osThreadId osThreadGetId(void)
{
	return rt_thread_self();
}

/// Terminate execution of a thread and remove it from ActiveThreads
osStatus osThreadTerminate(osThreadId thread_id)
{
	rt_err_t result;

	result = rt_thread_delete(thread_id);

	if (result == RT_EOK)
		return osOK;
	else
		return osErrorOS;
}

/// Pass control to next thread that is in state READY
osStatus osThreadYield(void)
{
	rt_err_t result;

	result = rt_thread_yield();

	if (result == RT_EOK)
		return osOK;
	else
		return osErrorOS;
}

/// Change prority of an active thread
osStatus osThreadSetPriority(osThreadId thread_id, osPriority priority)
{
	rt_err_t result;
	
	if (thread_id == RT_NULL)
		return osErrorOS;

	if (priority < osPriorityIdle || priority > osPriorityRealtime)
		return osErrorPriority;

	result = rt_thread_control(thread_id, RT_THREAD_CTRL_CHANGE_PRIORITY, &priority);	
	
	if (result == RT_EOK)
		return osOK;
	else
		return osErrorOS;
}

/// Get current prority of an active thread
osPriority osThreadGetPriority(osThreadId thread_id)
{
	if (thread_id == RT_NULL)
		return osErrorOS;

	if (thread_id->current_priority < osPriorityIdle || thread_id->current_priority > osPriorityRealtime)
		return osPriorityError;
		
	return thread_id->current_priority;
}

// Generic Wait API

/// Wait for Timeout (Time Delay)
osStatus osDelay(uint32_t millisec)
{
	rt_err_t result;
	rt_tick_t ticks;

	ticks = rt_tick_from_millisecond(millisec);
	result = rt_thread_delay(ticks);

	if (result == RT_EOK)
		return osOK;
	else
		return osErrorOS;
}

/// Wait for Signal, Message, Mail, or Timeout
osEvent osWait(uint32_t millisec)
{
	rt_err_t result;
	rt_tick_t ticks;

	ticks = rt_tick_from_millisecond(millisec);
	result = rt_thread_delay(ticks);
/*
	if (result == RT_EOK)
		return osOK;
	else
		return osErrorOS;
*/
}

// Timer Management Public API

/// Create timer
osTimerId osTimerCreate(osTimerDef_t *timer_def, os_timer_type type, void *argument)
{
	return rt_timer_create(timer_def->name, timer_def->timeout, timer_def->parameter, timer_def->time, timer_def->flag);
}

/// Start or restart timer
osStatus osTimerStart(osTimerId timer_id, uint32_t millisec)
{
	rt_err_t result;
	
	result = rt_timer_start(timer_id);
	if (result == RT_EOK)
		return osOK;
	else
		return osErrorOS;
}

/// Stop timer
osStatus osTimerStop(osTimerId timer_id)
{
	rt_err_t result;
	
	result = rt_timer_stop(timer_id);
	if (result == RT_EOK)
		return osOK;
	else
		return osErrorOS;
}

// Mutex Public API

/// Create and Initialize a Mutex object
osMutexId osMutexCreate(osMutexDef_t *mutex_def)
{
	return rt_mutex_create(mutex_def->name, mutex_def->flag);
}

/// Wait until a Mutex becomes available
osStatus osMutexWait(osMutexId mutex_id, uint32_t millisec)
{
	rt_err_t result;
	rt_tick_t ticks;

	ticks = rt_tick_from_millisecond(millisec);
	result = rt_mutex_take(mutex_id, ticks);

	if (result == RT_EOK)
		return osOK;
	else
		return osErrorOS;
}

/// Release a Mutex that was obtained with osMutexWait
osStatus osMutexRelease(osMutexId mutex_id)
{
	rt_err_t result;

	result = rt_mutex_release(mutex_id);

	if (result == RT_EOK)
		return osOK;
	else
		return osErrorOS;
}

// Semaphore Public API

/// Create and Initialize a Semaphore object
osSemaphoreId osSemaphoreCreate(osSemaphoreDef_t *semaphore_def, int32_t count)
{
	return rt_sem_create(semaphore_def->name, count, semaphore_def->flag);
}

/// Wait until a Semaphore becomes available
int32_t osSemaphoreWait(osSemaphoreId semaphore_id, uint32_t millisec)
{
	rt_tick_t ticks;

	if (semaphore_id == RT_NULL)
		return -1;

	ticks = rt_tick_from_millisecond(millisec);
	rt_sem_take(semaphore_id, ticks);

	return semaphore_id->value;
}

/// Release a Semaphore
osStatus osSemaphoreRelease(osSemaphoreId semaphore_id)
{
	rt_err_t result;

	result = rt_sem_release(semaphore_id);

	if (result == RT_EOK)
		return osOK;
	else
		return osErrorOS;
}

// Memory Management Public API

/// Create and Initialize memory pool
osPoolId osPoolCreate(osPoolDef_t *pool_def)
{
	return rt_mp_create(pool_def->name, pool_def->block_count, pool_def->block_size);
}

/// Allocate a memory block from a memory pool
void *osPoolAlloc(osPoolId pool_id)
{
	return rt_mp_alloc(pool_id, 0);
}

/// Allocate a memory block from a memory pool and set memory block to zero
void *osPoolCAlloc(osPoolId pool_id)
{
}

/// Return an allocated memory block back to a specific memory pool
osStatus osPoolFree(osPoolId pool_id, void *block)
{
	rt_mp_free(block);

	return osOK;
}

// Message Queue Management Public API

/// Create and Initialize Message Queue
osMessageQId osMessageCreate(osMessageQDef_t *queue_def, osThreadId thread_id)
{
	return rt_mq_create(queue_def->name, queue_def->msg_size, queue_def->max_msgs, queue_def->flag);
}

/// Put a Message to a Queue
osStatus osMessagePut(osMessageQId queue_id, uint32_t info, uint32_t millisec)
{
	rt_err_t result;

	result = rt_mq_send(queue_id, &info, 1);

	if (result == RT_EOK)
		return osOK;
	else
		return osErrorOS;	
}

/// Get a Message or Wait for a Message from a Queue
osEvent osMessageGet(osMessageQId queue_id, uint32_t millisec)
{
	
}

// Mail Queue Management Public API

/// Create and Initialize mail queue
osMailQId osMailCreate(osMailQDef_t *queue_def, osThreadId thread_id)
{
}

/// Allocate a memory block from a mail
void *osMailAlloc(osMailQId queue_id, uint32_t millisec)
{
}

/// Allocate a memory block from a mail and set memory block to zero
void *osMailCAlloc(osMailQId queue_id, uint32_t millisec)
{
}

/// Free a memory block from a mail
osStatus osMailFree(osMailQId queue_id, void *mail)
{
}

/// Put a mail to a queue
osStatus osMailPut(osMailQId queue_id, void *mail)
{
}

/// Get a mail from a queue
osEvent osMailGet(osMailQId queue_id, uint32_t millisec)
{
  osEvent ret;

  if (queue_id == NULL) {
    ret.status = osErrorParameter;
    return ret;
  }

  ret = osMessageGet(*((void **)queue_id), millisec);
  if (ret.status == osEventMessage) ret.status = osEventMail;

  return ret;
}


