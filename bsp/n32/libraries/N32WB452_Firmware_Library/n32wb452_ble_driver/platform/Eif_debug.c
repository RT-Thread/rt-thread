#include "Eif_debug.h"
#include "n32wb452_log_level.h"

#if  (PLF_DEBUG)
void eif_assert_warn(int param0, int param1, const char *file, int line)
{
    ble_log(BLE_DEBUG,"WARN: %s %d L, param 0:%d 1:%d\r\n",file, line, param0, param1);
}

void eif_assert_param(int param0, int param1, const char * file, int line)
{
    ble_log(BLE_DEBUG,"INFO: %s %d L, param 0:%d 1:%d\r\n",file, line, param0, param1);
    while (1);
}

void eif_assert_err(const char *condition, const char * file, int line)
{
    if (condition)
    {
        ble_log(BLE_DEBUG,"ERR: %s %d L\r\n", file, line);
    }
    while (1);
}
#endif  ///(PLF_DEBUG)

