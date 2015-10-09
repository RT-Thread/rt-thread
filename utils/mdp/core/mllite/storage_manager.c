/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */

/**
 *   @defgroup  Storage_Manager storage_manager
 *   @brief     Motion Library - Stores Data for functions.
 *
 *
 *   @{
 *       @file storage_manager.c
 *       @brief Load and Store Manager.
 */

#include <string.h>

#include "storage_manager.h"
#include "log.h"
#include "ml_math_func.h"
#include "mlmath.h"

/* Must be changed if the format of storage changes */
#define DEFAULT_KEY 29681

typedef inv_error_t (*load_func_t)(const unsigned char *data);
typedef inv_error_t (*save_func_t)(unsigned char *data);
/** Max number of entites that can be stored */
#define NUM_STORAGE_BOXES 20

struct data_header_t {
    long size;
    uint32_t checksum;
    unsigned int key;
};

struct data_storage_t {
    int num; /**< Number of differnt save entities */
    size_t total_size; /**< Size in bytes to store non volatile data */
    load_func_t load[NUM_STORAGE_BOXES]; /**< Callback to load data */
    save_func_t save[NUM_STORAGE_BOXES]; /**< Callback to save data */
    struct data_header_t hd[NUM_STORAGE_BOXES]; /**< Header info for each entity */
};
static struct data_storage_t ds;

/** Should be called once before using any of the storage methods. Typically
* called first by inv_init_mpl().*/
void inv_init_storage_manager()
{
    memset(&ds, 0, sizeof(ds));
    ds.total_size = sizeof(struct data_header_t);
}

/** Used to register your mechanism to load and store non-volative data. This should typical be
* called during the enable function for your feature.
* @param[in] load_func function pointer you will use to receive data that was stored for you.
* @param[in] save_func function pointer you will use to save any data you want saved to
*            non-volatile memory between runs.
* @param[in] size The size in bytes of the amount of data you want loaded and saved.
* @param[in] key The key associated with your data type should be unique across MPL.
*                    The key should change when your type of data for storage changes.
* @return Returns INV_SUCCESS if successful or an error code if not.
*/
inv_error_t inv_register_load_store(inv_error_t (*load_func)(const unsigned char *data),
                                    inv_error_t (*save_func)(unsigned char *data), size_t size, unsigned int key)
{
    int kk;
    // Check if this has been registered already
    for (kk=0; kk<ds.num; ++kk) {
        if (key == ds.hd[kk].key) {
            return INV_ERROR_INVALID_PARAMETER;
        }
    }
    // Make sure there is room
    if (ds.num >= NUM_STORAGE_BOXES) {
        return INV_ERROR_INVALID_PARAMETER;
    }
    // Add to list
    ds.hd[ds.num].key = key;
    ds.hd[ds.num].size = size;
    ds.load[ds.num] = load_func;
    ds.save[ds.num] = save_func;
    ds.total_size += size + sizeof(struct data_header_t);
    ds.num++;

    return INV_SUCCESS;
}

/** Returns the memory size needed to perform a store
* @param[out] size Size in bytes of memory needed to store.
* @return Returns INV_SUCCESS if successful or an error code if not.
*/
inv_error_t inv_get_mpl_state_size(size_t *size)
{
    *size = ds.total_size;
    return INV_SUCCESS;
}

/** @internal
 * Finds key in ds.hd[] array and returns location
 * @return location where key exists in array, -1 if not found.
 */
static int inv_find_entry(unsigned int key)
{
    int kk;
    for (kk=0; kk<ds.num; ++kk) {
        if (key == ds.hd[kk].key) {
            return kk;
        }
    }
    return -1;
}

/** This function takes a block of data that has been saved in non-volatile memory and pushes
* to the proper locations. Multiple error checks are performed on the data.
* @param[in] data Data that was saved to be loaded up by MPL
* @param[in] length Length of data vector in bytes
* @return Returns INV_SUCCESS if successful or an error code if not.
*/
inv_error_t inv_load_mpl_states(const unsigned char *data, size_t length)
{
    struct data_header_t *hd;
    int entry;
    uint32_t checksum;
    long len;

    len = length; // Important so we get negative numbers
    if (len < sizeof(struct data_header_t))
        return INV_ERROR_CALIBRATION_LOAD;	// No data
    hd = (struct data_header_t *)data;
    if (hd->key != DEFAULT_KEY)
        return INV_ERROR_CALIBRATION_LOAD;	// Key changed or data corruption
    len = MIN(hd->size, len);
    len = hd->size;
    len -= sizeof(struct data_header_t);
    data += sizeof(struct data_header_t);
    checksum = inv_checksum(data, len);
    if (checksum != hd->checksum)
        return INV_ERROR_CALIBRATION_LOAD;	// Data corruption

    while (len > (long)sizeof(struct data_header_t)) {
        hd = (struct data_header_t *)data;
        entry = inv_find_entry(hd->key);
        data += sizeof(struct data_header_t);
        len -= sizeof(struct data_header_t);
        if (entry >= 0 && len >= hd->size) {
            if (hd->size == ds.hd[entry].size) {
                checksum = inv_checksum(data, hd->size);
                if (checksum == hd->checksum) {
                    ds.load[entry](data);
                } else {
                    return INV_ERROR_CALIBRATION_LOAD;
                }
            }
        }
        len -= hd->size;
        if (len >= 0)
            data = data + hd->size;
    }

    return INV_SUCCESS;
}

/** This function fills up a block of memory to be stored in non-volatile memory.
* @param[out] data Place to store data, size of sz, must be at least size
*                  returned by inv_get_mpl_state_size()
* @param[in] sz Size of data.
* @return Returns INV_SUCCESS if successful or an error code if not.
*/
inv_error_t inv_save_mpl_states(unsigned char *data, size_t sz)
{
    unsigned char *cur;
    int kk;
    struct data_header_t *hd;

    if (sz >= ds.total_size) {
        cur = data + sizeof(struct data_header_t);
        for (kk = 0; kk < ds.num; ++kk) {
            hd = (struct data_header_t *)cur;
            cur += sizeof(struct data_header_t);
            ds.save[kk](cur);
            hd->checksum = inv_checksum(cur, ds.hd[kk].size);
            hd->size = ds.hd[kk].size;
            hd->key = ds.hd[kk].key;
            cur += ds.hd[kk].size;
        }
    } else {
        return INV_ERROR_CALIBRATION_LOAD;
    }

    hd = (struct data_header_t *)data;
    hd->checksum = inv_checksum(data + sizeof(struct data_header_t),
                                ds.total_size - sizeof(struct data_header_t));
    hd->key = DEFAULT_KEY;
    hd->size = ds.total_size;

    return INV_SUCCESS;
}

/**
 * @}
 */