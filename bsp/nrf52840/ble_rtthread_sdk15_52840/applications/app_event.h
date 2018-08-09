#ifndef APP_EVENT_H__
#define APP_EVENT_H__
#include <rtthread.h>


//////////////////////////////////////////////////////////////////////////////////////
typedef void (*event_func_t)( void *arg );
typedef struct
{
    void *pargs;
    uint32_t debug;
    event_func_t pfunc;
} event_data_handle_t;

void app_event_init(void *args);
uint8_t app_event_push(void *pfunc, void *pargs, uint32_t debug);
void app_event_push_delayed(void *pfunc, void *pargs, uint32_t debug, uint32_t delay);
uint8_t app_event_remove_delayed(void *pfunc);
uint8_t app_thread_push(void (*pfunc)(void *args), void *args, uint32_t stacksize);

#define APP_EVENT_REMOVE_DELAY(pfunc) app_event_remove_delayed(pfunc)

#define APP_EVENT_PUSH_DELAY(pfunc, pargs, delay) \
do{ \
   /*debug_printf("%s:%d:%d: push delay %d\r\n",__FILE__,__LINE__,bsp_get_system_tick(),delay);*/ \
   app_event_push_delayed(pfunc, pargs, __LINE__, delay); \
}while(0)

#endif




