#ifndef __DRT_QSPI_H__
#define __DRT_QSPI_H__

#include <rtthread.h>
#ifdef RT_USING_QSPI
#define PHYTIUM_QSPI_NAME "qspi"

#ifdef __cplusplus
extern "C"
{
#endif

rt_err_t phytium_qspi_bus_attach_device(const char *bus_name, const char *device_name);

#ifdef __cplusplus
}
#endif
#endif
#endif // !DRT_QSPI_H

