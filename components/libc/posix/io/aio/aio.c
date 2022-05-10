/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/12/30     Bernard      The first version.
 */

#include <rtthread.h>
#include <rthw.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/errno.h>
#include "aio.h"

struct rt_workqueue* aio_queue = NULL;

/**
 * The aio_cancel() function shall attempt to cancel one or more asynchronous I/O
 * requests currently outstanding against file descriptor fildes. The aiocbp
 * argument points to the asynchronous I/O control block for a particular request
 * to be canceled. If aiocbp is NULL, then all outstanding cancelable asynchronous
 * I/O requests against fildes shall be canceled.
 *
 * Normal asynchronous notification shall occur for asynchronous I/O operations
 * that are successfully canceled. If there are requests that cannot be canceled,
 * then the normal asynchronous completion process shall take place for those
 * requests when they are completed.
 *
 * For requested operations that are successfully canceled, the associated error
 * status shall be set to [ECANCELED] and the return status shall be -1. For
 * requested operations that are not successfully canceled, the aiocbp shall not
 * be modified by aio_cancel().
 *
 * If aiocbp is not NULL, then if fildes does not have the same value as the file
 * descriptor with which the asynchronous operation was initiated, unspecified results occur.
 *
 * Which operations are cancelable is implementation-defined.
 */
int aio_cancel(int fd, struct aiocb *cb)
{
    rt_err_t ret;

    if (!cb) return -EINVAL;
    if (cb->aio_fildes != fd) return -EINVAL;

    ret = rt_workqueue_cancel_work_sync(aio_queue, &(cb->aio_work));
    if (ret == RT_EOK)
    {
        errno = -ECANCELED;
        return -1;
    }

    return 0;
}

/**
 * The aio_error() function shall return the error status associated with the
 * aiocb structure referenced by the aiocbp argument. The error status for an
 * asynchronous I/O operation is the errno value that would be set by the corresponding
 * read(), write(),
 */
int aio_error (const struct aiocb *cb)
{
    if (cb)
    {
        return cb->aio_result;
    }

    return -EINVAL;
}

/**
 * The aio_fsync() function shall asynchronously perform a file synchronization
 * operation, as specified by the op argument, for I/O operations associated with
 * the file indicated by the file descriptor aio_fildes member of the aiocb
 * structure referenced by the aiocbp argument and queued at the time of the
 * call to aio_fsync(). The function call shall return when the synchronization
 * request has been initiated or queued to the file or device (even when the data
 * cannot be synchronized immediately).
 *
 * option: If op is O_DSYNC, all currently queued I/O operations shall be completed
 * as if by a call to fdatasync(); that is, as defined for synchronized I/O data
 * integrity completion.
 *
 * option: If op is O_SYNC, all currently queued I/O operations shall be completed
 * as if by a call to fsync(); that is, as defined for synchronized I/O file integrity
 * completion. If the aio_fsync() function fails, or if the operation queued by
 * aio_fsync() fails, then outstanding I/O operations are not guaranteed to have
 * been completed.
 *
 * If aio_fsync() succeeds, then it is only the I/O that was queued at the time
 * of the call to aio_fsync() that is guaranteed to be forced to the relevant
 * completion state. The completion of subsequent I/O on the file descriptor is
 * not guaranteed to be completed in a synchronized fashion.
 *
 * The aiocbp argument refers to an asynchronous I/O control block. The aiocbp
 * value may be used as an argument to aio_error() and aio_return() in order to
 * determine the error status and return status, respectively, of the asynchronous
 * operation while it is proceeding. When the request is queued, the error status
 * for the operation is [EINPROGRESS]. When all data has been successfully transferred,
 * the error status shall be reset to reflect the success or failure of the operation.
 * If the operation does not complete successfully, the error status for the
 * operation shall be set to indicate the error. The aio_sigevent member determines
 * the asynchronous notification to occur as specified in Signal Generation and
 * Delivery when all operations have achieved synchronized I/O completion. All
 * other members of the structure referenced by aiocbp are ignored. If the control
 * block referenced by aiocbp becomes an illegal address prior to asynchronous
 * I/O completion, then the behavior is undefined.
 *
 * If the aio_fsync() function fails or aiocbp indicates an error condition,
 * data is not guaranteed to have been successfully transferred.
 */
static void aio_fync_work(struct rt_work* work, void* work_data)
{
    int result;
    rt_base_t level;
    struct aiocb *cb = (struct aiocb*)work_data;

    RT_ASSERT(cb != RT_NULL);

    result = fsync(cb->aio_fildes);
    /* modify result */
    level = rt_hw_interrupt_disable();
    if (result < 0)
        cb->aio_result = errno;
    else
        cb->aio_result = 0;
    rt_hw_interrupt_enable(level);

    return ;
}

int aio_fsync(int op, struct aiocb *cb)
{
    rt_base_t level;
    if (!cb) return -EINVAL;

    level = rt_hw_interrupt_disable();
    cb->aio_result = -EINPROGRESS;
    rt_hw_interrupt_enable(level);

    rt_work_init(&(cb->aio_work), aio_fync_work, cb);
    rt_workqueue_dowork(aio_queue, &(cb->aio_work));

    return 0;
}

static void aio_read_work(struct rt_work* work, void* work_data)
{
    int len;
    rt_base_t level;
    uint8_t *buf_ptr;
    struct aiocb *cb = (struct aiocb*)work_data;

    buf_ptr = (uint8_t*)cb->aio_buf;

    /* seek to offset */
    lseek(cb->aio_fildes, cb->aio_offset, SEEK_SET);
    len = read(cb->aio_fildes, &buf_ptr[cb->aio_offset], cb->aio_nbytes);

    /* modify result */
    level = rt_hw_interrupt_disable();
    if (len <= 0)
        cb->aio_result = errno;
    else
        cb->aio_result = len;
    rt_hw_interrupt_enable(level);

    return ;
}

/**
 * The aio_read() function shall read aiocbp->aio_nbytes from the file associated
 * with aiocbp->aio_fildes into the buffer pointed to by aiocbp->aio_buf. The
 * function call shall return when the read request has been initiated or queued
 * to the file or device (even when the data cannot be delivered immediately).
 *
 * If prioritized I/O is supported for this file, then the asynchronous operation
 * shall be submitted at a priority equal to a base scheduling priority minus
 * aiocbp->aio_reqprio. If Thread Execution Scheduling is not supported, then
 * the base scheduling priority is that of the calling process;
 *
 * otherwise, the base scheduling priority is that of the calling thread.
 *
 * The aiocbp value may be used as an argument to aio_error() and aio_return()
 * in order to determine the error status and return status, respectively, of
 * the asynchronous operation while it is proceeding. If an error condition is
 * encountered during queuing, the function call shall return without having
 * initiated or queued the request. The requested operation takes place at the
 * absolute position in the file as given by aio_offset, as if lseek() were called
 * immediately prior to the operation with an offset equal to aio_offset and a
 * whence equal to SEEK_SET. After a successful call to enqueue an asynchronous
 * I/O operation, the value of the file offset for the file is unspecified.
 *
 * The aio_sigevent member specifies the notification which occurs when the
 * request is completed.
 *
 * The aiocbp->aio_lio_opcode field shall be ignored by aio_read().
 *
 * The aiocbp argument points to an aiocb structure. If the buffer pointed to by
 * aiocbp->aio_buf or the control block pointed to by aiocbp becomes an illegal
 * address prior to asynchronous I/O completion, then the behavior is undefined.
 *
 * Simultaneous asynchronous operations using the same aiocbp produce undefined
 * results.
 *
 * If synchronized I/O is enabled on the file associated with aiocbp->aio_fildes,
 * the behavior of this function shall be according to the definitions of synchronized
 * I/O data integrity completion and synchronized I/O file integrity completion.
 *
 * For any system action that changes the process memory space while an asynchronous
 * I/O is outstanding to the address range being changed, the result of that action
 * is undefined.
 *
 * For regular files, no data transfer shall occur past the offset maximum
 * established in the open file description associated with aiocbp->aio_fildes.
 *
 */
int aio_read(struct aiocb *cb)
{
    rt_base_t level;

    if (!cb) return -EINVAL;
    if (cb->aio_offset < 0) return -EINVAL;

    level = rt_hw_interrupt_disable();
    cb->aio_result = -EINPROGRESS;
    rt_hw_interrupt_enable(level);

    /* en-queue read work */
    rt_work_init(&(cb->aio_work), aio_read_work, cb);
    rt_workqueue_dowork(aio_queue, &(cb->aio_work));

    return 0;
}

/**
 * The aio_return() function shall return the return status associated with the
 * aiocb structure referenced by the aiocbp argument. The return status for an
 * asynchronous I/O operation is the value that would be returned by the corresponding
 * read(), write(), or fsync() function call. If the error status for the operation
 * is equal to [EINPROGRESS], then the return status for the operation is undefined.
 * The aio_return() function may be called exactly once to retrieve the return
 * status of a given asynchronous operation; thereafter, if the same aiocb structure
 * is used in a call to aio_return() or aio_error(), an error may be returned.
 * When the aiocb structure referred to by aiocbp is used to submit another asynchronous
 * operation, then aio_return() may be successfully used to retrieve the return
 * status of that operation.
 */
ssize_t  aio_return(struct aiocb *cb)
{
    if (cb)
    {
        if (cb->aio_result < 0)
            rt_set_errno(cb->aio_result);

        return cb->aio_result;
    }

    return -EINVAL;
}

/**
 * The aio_suspend() function shall suspend the calling thread until at least
 * one of the asynchronous I/O operations referenced by the list argument has
 * completed, until a signal interrupts the function, or, if timeout is not NULL,
 * until the time interval specified by timeout has passed. If any of the aiocb
 * structures in the list correspond to completed asynchronous I/O operations
 * (that is, the error status for the operation is not equal to [EINPROGRESS])
 * at the time of the call, the function shall return without suspending the
 * calling thread. The list argument is an array of pointers to asynchronous I/O
 * control blocks. The nent argument indicates the number of elements in the
 * array. Each aiocb structure pointed to has been used in initiating an asynchronous
 * I/O request via aio_read(), aio_write(), or lio_listio(). This array may
 * contain null pointers, which are ignored. If this array contains pointers
 * that refer to aiocb structures that have not been used in submitting asynchronous
 * I/O, the effect is undefined.
 *
 * If the time interval indicated in the timespec structure pointed to by timeout
 * passes before any of the I/O operations referenced by list are completed, then
 * aio_suspend() shall return with an error.
 */
int aio_suspend(const struct aiocb *const list[], int nent,
             const struct timespec *timeout)
{
    return -ENOSYS;
}

static void aio_write_work(struct rt_work* work, void* work_data)
{
    rt_base_t level;
    int len, oflags;
    uint8_t *buf_ptr;
    struct aiocb *cb = (struct aiocb*)work_data;

    buf_ptr = (uint8_t*)cb->aio_buf;

    /* whether seek offset */
    oflags = fcntl(cb->aio_fildes, F_GETFL, 0);
    if ((oflags & O_APPEND) == 0)
    {
        lseek(cb->aio_fildes, SEEK_SET, cb->aio_offset);
    }

    /* write data */
    len = write(cb->aio_fildes, buf_ptr, cb->aio_nbytes);

    /* modify result */
    level = rt_hw_interrupt_disable();
    if (len <= 0)
        cb->aio_result = errno;
    else
        cb->aio_result = len;
    rt_hw_interrupt_enable(level);

    return;
}

/**
 * The aio_write() function shall write aiocbp->aio_nbytes to the file associated
 * with aiocbp->aio_fildes from the buffer pointed to by aiocbp->aio_buf. The
 * function shall return when the write request has been initiated or, at a minimum,
 * queued to the file or device.
 *
 * The aiocbp argument may be used as an argument to aio_error() and aio_return()
 * in order to determine the error status and return status, respectively, of the
 * asynchronous operation while it is proceeding.
 *
 * The aiocbp argument points to an aiocb structure. If the buffer pointed to by
 * aiocbp->aio_buf or the control block pointed to by aiocbp becomes an illegal
 * address prior to asynchronous I/O completion, then the behavior is undefined.
 *
 * If O_APPEND is not set for the file descriptor aio_fildes, then the requested
 * operation shall take place at the absolute position in the file as given by
 * aio_offset, as if lseek() were called immediately prior to the operation with
 * an offset equal to aio_offset and a whence equal to SEEK_SET. If O_APPEND is
 * set for the file descriptor, or if aio_fildes is associated with a device that
 * is incapable of seeking, write operations append to the file in the same order
 * as the calls were made, except under circumstances described in Asynchronous
 * I/O. After a successful call to enqueue an asynchronous I/O operation, the value
 * of the file offset for the file is unspecified.
 *
 * The aio_sigevent member specifies the notification which occurs when the request
 * is completed.
 *
 * The aiocbp->aio_lio_opcode field shall be ignored by aio_write().
 *
 * Simultaneous asynchronous operations using the same aiocbp produce undefined
 * results.
 *
 * If synchronized I/O is enabled on the file associated with aiocbp->aio_fildes,
 * the behavior of this function shall be according to the definitions of synchronized
 * I/O data integrity completion, and synchronized I/O file integrity completion.
 *
 * For regular files, no data transfer shall occur past the offset maximum established
 * in the open file description associated with aiocbp->aio_fildes.
 */
int aio_write(struct aiocb *cb)
{
    int oflags;
    rt_base_t level;

    if (!cb || (cb->aio_buf == NULL)) return -EINVAL;

    /* check access mode */
    oflags = fcntl(cb->aio_fildes, F_GETFL, 0);
    if ((oflags & O_ACCMODE) != O_WRONLY ||
        (oflags & O_ACCMODE) != O_RDWR)
        return -EINVAL;

    level = rt_hw_interrupt_disable();
    cb->aio_result = -EINPROGRESS;
    rt_hw_interrupt_enable(level);

    rt_work_init(&(cb->aio_work), aio_write_work, cb);
    rt_workqueue_dowork(aio_queue, &(cb->aio_work));

    return 0;
}

/**
 * The lio_listio() function shall initiate a list of I/O requests with a single
 * function call.
 *
 * The mode argument takes one of the values LIO_WAIT or LIO_NOWAIT declared in
 * <aio.h> and determines whether the function returns when the I/O operations
 * have been completed, or as soon as the operations have been queued. If the
 * mode argument is LIO_WAIT, the function shall wait until all I/O is complete
 * and the sig argument shall be ignored.
 *
 * If the mode argument is LIO_NOWAIT, the function shall return immediately, and
 * asynchronous notification shall occur, according to the sig argument, when all
 * the I/O operations complete. If sig is NULL, then no asynchronous notification
 * shall occur. If sig is not NULL, asynchronous notification occurs as specified
 * in Signal Generation and Delivery when all the requests in list have completed.
 *
 * The I/O requests enumerated by list are submitted in an unspecified order.
 *
 * The list argument is an array of pointers to aiocb structures. The array contains
 * nent elements. The array may contain NULL elements, which shall be ignored.
 *
 * If the buffer pointed to by list or the aiocb structures pointed to by the
 * elements of the array list become illegal addresses before all asynchronous I/O
 * completed and, if necessary, the notification is sent, then the behavior is
 * undefined. If the buffers pointed to by the aio_buf member of the aiocb structure
 * pointed to by the elements of the array list become illegal addresses prior to
 * the asynchronous I/O associated with that aiocb structure being completed, the
 * behavior is undefined.
 *
 * The aio_lio_opcode field of each aiocb structure specifies the operation to be
 * performed. The supported operations are LIO_READ, LIO_WRITE, and LIO_NOP; these
 * symbols are defined in <aio.h>. The LIO_NOP operation causes the list entry to
 * be ignored. If the aio_lio_opcode element is equal to LIO_READ, then an I/O operation
 * is submitted as if by a call to aio_read() with the aiocbp equal to the address
 * of the aiocb structure. If the aio_lio_opcode element is equal to LIO_WRITE, then
 * an I/O operation is submitted as if by a call to aio_write() with the aiocbp equal
 * to the address of the aiocb structure.
 *
 * The aio_fildes member specifies the file descriptor on which the operation is to
 * be performed.
 *
 * The aio_buf member specifies the address of the buffer to or from which the data
 * is transferred.
 *
 * The aio_nbytes member specifies the number of bytes of data to be transferred.
 *
 * The members of the aiocb structure further describe the I/O operation to be
 * performed, in a manner identical to that of the corresponding aiocb structure
 * when used by the aio_read() and aio_write() functions.
 *
 * The nent argument specifies how many elements are members of the list; that is,
 * the length of the array.
 *
 * The behavior of this function is altered according to the definitions of synchronized
 * I/O data integrity completion and synchronized I/O file integrity completion if
 * synchronized I/O is enabled on the file associated with aio_fildes.
 *
 * For regular files, no data transfer shall occur past the offset maximum established
 * in the open file description associated with aiocbp->aio_fildes.
 *
 * If sig->sigev_notify is SIGEV_THREAD and sig->sigev_notify_attributes is a
 * non-null pointer and the block pointed to by this pointer becomes an illegal
 * address prior to all asynchronous I/O being completed, then the behavior is
 * undefined.
 */
int lio_listio(int mode, struct aiocb * const list[], int nent,
            struct sigevent *sig)
{
    return -ENOSYS;
}

int aio_system_init(void)
{
    aio_queue = rt_workqueue_create("aio", 2048, RT_THREAD_PRIORITY_MAX/2);
    RT_ASSERT(aio_queue != NULL);

    return 0;
}
INIT_COMPONENT_EXPORT(aio_system_init);
