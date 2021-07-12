/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 15:31:10
 * @Description:  This files is for definition of status
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef FT_STATUS_H
#define FT_STATUS_H

/**
@name Common Status Codes
*/

typedef enum
{
    FST_SUCCESS = 0L,
    FST_FAILURE = 1L,
    FST_INSTANCE_NOT_FOUND = 2L,
    FST_DEVICE_BLOCK_NOT_FOUND = 3L,
    FST_INVALID_VERSION = 4L,
    FST_DEVICE_IS_STARTED = 5L,
    FST_DEVICE_IS_STOPPED = 6L,
    FST_FIFO_ERROR = 7L,        /* An error occurred during an \
                operation with a FIFO such as                    \
                an underrun or overrun, this                     \
                error requires the device to                     \
                be reset */
    FST_RESET_ERROR = 8L,       /* An error occurred which requires \
                the device to be reset */
    FST_DMA_ERROR = 9L,         /* A DMA error occurred, this error \
                typically requires the device                         \
                using the DMA to be reset */
    FST_NOT_POLLED = 10L,       /* The device is not configured for \
                polled mode operation */
    FST_FIFO_NO_ROOM = 11L,     /* A FIFO did not have room to put \
                the specified data into */
    FST_BUFFER_TOO_SMALL = 12L, /* The buffer is not large enough \
                to hold the expected data */
    FST_NO_DATA = 13L,          /* There was no data available */
    FST_REGISTER_ERROR = 14L,   /* A register did not contain the \
                expected value */
    FST_INVALID_PARAM = 15L,    /* An invalid parameter was passed \
                into the function */
    FST_NOT_SGDMA = 16L,        /* The device is not configured for \
                scatter-gather DMA operation */
    FST_LOOPBACK_ERROR = 17L,   /* A loopback test failed */
    FST_NO_CALLBACK = 18L,      /* A callback has not yet been \
                registered */
    FST_NO_FEATURE = 19L,       /* Device is not configured with \
                the requested feature */
    FST_NOT_INTERRUPT = 20L,    /* Device is not configured for \
                interrupt mode operation */
    FST_DEVICE_BUSY = 21L,      /* Device is busy */
    FST_ERROR_COUNT_MAX = 22L,  /* The error counters of a device \
                have maxed out */
    FST_IS_STARTED = 23L,       /* Used when part of device is \
                already started i.e.                             \
                sub channel */
    FST_IS_STOPPED = 24L,       /* Used when part of device is \
                already stopped i.e.                             \
                sub channel */
    FST_DATA_LOST = 26L,        /* Driver defined error */
    FST_RECV_ERROR = 27L,       /* Generic receive error */
    FST_SEND_ERROR = 28L,       /* Generic transmit error */
    FST_NOT_ENABLED = 29L,      /* A requested service is not \
                available because it has not                    \
                been enabled */
    FST_ASSERT_RETURN = 30L,    /* Assert occurs defined error */
    FST_TIMEOUT = 31L,
    FST_EILSEQ = 32L,             /* Illegal byte sequence. */
    FST_STATUS_MAX_VALUE = 0xffff /* Status max value */
} Common_status;

#endif // !FT_STATUS_H
