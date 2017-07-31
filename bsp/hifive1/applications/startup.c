#include <rtthread.h>

extern  void *__bss_end__;
extern  void *_heap_end;
#define HEAP_BEGIN &__bss_end__
#define HEAP_END   &_heap_end
static void rtthread_startup(void)
{
	/* initialize board */
	rt_hw_board_init();

	/* show version */
	rt_show_version();

#ifdef RT_USING_HEAP
	rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

	/* initialize scheduler system */
	rt_system_scheduler_init();
	/* initialize system timer*/
	rt_system_timer_init();
	/* initialize application */
	rt_application_init();

	/* initialize timer thread */
	rt_system_timer_thread_init();

	/* initialize idle thread */
	rt_thread_idle_init();

	/* start scheduler */
	rt_system_scheduler_start();

	/* never reach here */
	return;
}
#include "encoding.h"
#include <platform.h>
int main(void)
{
	rtthread_startup();
	return 0;
}
