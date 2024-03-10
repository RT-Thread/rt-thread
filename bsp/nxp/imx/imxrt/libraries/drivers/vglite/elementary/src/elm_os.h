#ifndef ELM_OS_H_
#define ELM_OS_H_

#include<stdlib.h>
#include"vg_lite.h"

vg_lite_error_t elm_os_set_tls(void* tls);

void * elm_os_get_tls(void);

void elm_os_reset_tls(void);

#endif
