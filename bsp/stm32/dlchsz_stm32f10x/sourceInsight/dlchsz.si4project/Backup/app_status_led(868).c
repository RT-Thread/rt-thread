#include "app_status_led.h"

#include <agile_led.h>

static void __status_led_init(void) {
    agile_led_t *sys_run = RT_NULL;
    
    sys_run = agile_led_create(GET_PIN(C, 13), PIN_LOW, "1000,1000", -1);
    
}
INIT_APP_EXPORT(__status_led_init);
