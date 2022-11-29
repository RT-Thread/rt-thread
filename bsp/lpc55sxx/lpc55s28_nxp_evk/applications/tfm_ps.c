/*
 * Copyright (c) 2019-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-01-10     Kevin/Karl   Add PS demo
 *
 */

#include <rtdevice.h>
#include <string.h>
#include "tfm_ns_lock.h"
#include "psa_protected_storage.h"

#define TEST_UID_A      2U
#define ASSET_A         "THEQUICKBROWNFOXJUMPSOVERALAZYDOG"
#define ASSET_A_SIZE    (sizeof( ASSET_A ) - 1)
#define RESETDATA       "THISIS"
#define RESETDATA_SIZE  (sizeof( RESETDATA ) - 1)
#define READ_LENGTH     (ASSET_A_SIZE > RESETDATA_SIZE ? \
                         ASSET_A_SIZE : RESETDATA_SIZE)

void protected_storage_demo_thread(void * parameters)
{
    psa_ps_status_t status;
    const psa_ps_uid_t uid = TEST_UID_A;
    const psa_ps_create_flags_t flags = PSA_PS_FLAG_NONE;
    uint8_t write_data[] = ASSET_A;
    const uint32_t data_length = ASSET_A_SIZE;
    uint8_t rewrite_data[] = RESETDATA;
    const uint32_t reset_data_length = RESETDATA_SIZE;
    uint8_t get_data[READ_LENGTH];
    uint32_t counter = 0;

    tfm_ns_lock_init();

    for ( ; ; )
    {
        /* Call TF-M protected storage service and set the asset. */
        status = psa_ps_set(uid, data_length, write_data, flags);
        if (status != PSA_PS_SUCCESS)
        {
            rt_kprintf("[Protected Storage Asset A Set Round %ld] Fail\r\n", counter);
            for( ; ; );
        }

        rt_kprintf("[Protected Storage Asset A Set Round %ld] Success\r\n", counter);

        /* Read the asset. */
        status = psa_ps_get(uid, 0, data_length, get_data);
        if (status != PSA_PS_SUCCESS)
        {
            rt_kprintf("[Protected Storage Asset A Get Round %ld] Fail\r\n", counter);
            for ( ; ; );
        }

        rt_kprintf("[Protected Storage Asset A Get Round %ld] Success\r\n", counter);

        /* Check the read data. */
        if (memcmp(write_data, get_data, sizeof(write_data) - 1) != 0)
        {
            rt_kprintf("[Protected Storage Asset A Get Round %ld] Get the wrong data\r\n", counter);
            for ( ; ; );
        }

        /* Change the asset. */
        status = psa_ps_set(uid, reset_data_length, rewrite_data, flags);
        if (status != PSA_PS_SUCCESS)
        {
            rt_kprintf("[Protected Storage Asset A Reset Round %ld] Fail\r\n", counter);
        }

        rt_kprintf("[Protected Storage Asset A Reset Round %ld] Success\r\n", counter);

        /* Read the asset. */
        status = psa_ps_get(uid, 0, reset_data_length, get_data);
        if (status != PSA_PS_SUCCESS)
        {
            rt_kprintf("[Protected Storage Asset A Get Round %ld] Fail\r\n", counter);
            for ( ; ; );
        }

        rt_kprintf("[Protected Storage Asset A Get Round %ld] Success\r\n", counter);

        /* Check the read data. */
        if (memcmp(rewrite_data, get_data, sizeof(rewrite_data) - 1) != 0)
        {
            rt_kprintf("[Protected Storage Asset A Get Round %ld] Get the wrong data\r\n", counter);
            for ( ; ; );
        }

        /* Remove the asset. */
        status = psa_ps_remove(uid);
        if (status != PSA_PS_SUCCESS)
        {
            rt_kprintf("[Protected Storage Asset A Remove Round %ld] Fail\r\n", counter);
            for ( ; ; );
        }

        rt_kprintf("[Protected Storage Asset A Remove Round %ld] Success\r\n\n", counter);

        /* Wait for a second. */
        rt_thread_mdelay(1000);
        counter++;
    }
}

// end file
