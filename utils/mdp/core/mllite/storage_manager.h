/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */
#include "mltypes.h"

#ifndef INV_STORAGE_MANAGER_H__
#define INV_STORAGE_MANAGER_H__

#ifdef __cplusplus
extern "C" {
#endif

inv_error_t inv_register_load_store(
                           inv_error_t (*load_func)(const unsigned char *data),
                           inv_error_t (*save_func)(unsigned char *data), 
                           size_t size, unsigned int key);
void inv_init_storage_manager(void);

inv_error_t inv_get_mpl_state_size(size_t *size);
inv_error_t inv_load_mpl_states(const unsigned char *data, size_t len);
inv_error_t inv_save_mpl_states(unsigned char *data, size_t len);

#ifdef __cplusplus
}
#endif

#endif  /* INV_STORAGE_MANAGER_H__ */