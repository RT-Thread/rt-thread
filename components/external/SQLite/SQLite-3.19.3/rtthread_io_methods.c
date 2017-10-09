static int _rtthread_io_read(sqlite3_file *file_id, void *pbuf, int cnt, sqlite3_int64 offset)
{
    RTTHREAD_SQLITE_FILE_T *file = (RTTHREAD_SQLITE_FILE_T*)file_id;
    sqlite3_int64 new_offset;
    int r_cnt;

    assert(file_id);
    assert(offset >= 0);
    assert(cnt > 0);

    new_offset = lseek(file->fd, offset, SEEK_SET);

    if (new_offset != offset)
    {
        return SQLITE_IOERR_READ;
    }

    do {
        r_cnt = read(file->fd, pbuf, cnt);

        if (r_cnt == cnt)
        {
            break;
        }

        if (r_cnt < 0)
        {
            if (errno != EINTR)
            {
                return SQLITE_IOERR_READ;
            }

            r_cnt = 1;
            continue;
        }
        else if (r_cnt > 0)
        {
            cnt -= r_cnt;
            pbuf = (void*)(r_cnt + (char*)pbuf);
        }
    } while (r_cnt > 0);

    if (r_cnt != cnt)
    {
        memset(&((char*)pbuf)[r_cnt], 0, cnt - r_cnt);
        return SQLITE_IOERR_SHORT_READ;
    }

    return SQLITE_OK;
}

static int _rtthread_io_write(sqlite3_file* file_id, const void *pbuf, int cnt, sqlite3_int64 offset)
{
    RTTHREAD_SQLITE_FILE_T *file = (RTTHREAD_SQLITE_FILE_T*)file_id;
    sqlite3_int64 new_offset;
    int w_cnt;

    assert(file_id);
    assert(cnt > 0);

    new_offset = lseek(file->fd, offset, SEEK_SET);

    if (new_offset != offset)
    {
        return SQLITE_IOERR_WRITE;
    }

    do {
        w_cnt = write(file->fd, pbuf, cnt);

        if (w_cnt == cnt)
        {
            break;
        }

        if (w_cnt < 0)
        {
            if (errno != EINTR)
            {
                return SQLITE_IOERR_WRITE;
            }

            w_cnt = 1;
            continue;
        }
        else if (w_cnt > 0)
        {
            cnt -= w_cnt;
            pbuf = (void*)(w_cnt + (char*)pbuf);
        }
    } while (w_cnt > 0);

    if (w_cnt != cnt)
    {
        return SQLITE_FULL;
    }

    return SQLITE_OK;
}

static int _rtthread_io_truncate(sqlite3_file* file_id, sqlite3_int64 size)
{
    return SQLITE_IOERR_TRUNCATE;
}

static int _rtthread_io_sync(sqlite3_file* file_id, int flags)
{
    RTTHREAD_SQLITE_FILE_T *file = (RTTHREAD_SQLITE_FILE_T*)file_id;

    assert((flags & 0x0F) == SQLITE_SYNC_NORMAL
        || (flags & 0x0F) == SQLITE_SYNC_FULL);

    fsync(file->fd);

    return SQLITE_OK;
}

static int _rtthread_io_file_size(sqlite3_file* file_id, sqlite3_int64 *psize)
{
    int rc;
    struct stat buf;
    RTTHREAD_SQLITE_FILE_T *file = (RTTHREAD_SQLITE_FILE_T*)file_id;

    assert(file_id);

    rc = fstat(file->fd, &buf);

    if (rc != 0)
    {
        return SQLITE_IOERR_FSTAT;
    }

    *psize = buf.st_size;

    /* When opening a zero-size database, the findInodeInfo() procedure
    ** writes a single byte into that file in order to work around a bug
    ** in the OS-X msdos filesystem.  In order to avoid problems with upper
    ** layers, we need to report this file size as zero even though it is
    ** really 1.   Ticket #3260.
    */
    if (*psize == 1) *psize = 0;

    return SQLITE_OK;
}

/*
** This routine checks if there is a RESERVED lock held on the specified
** file by this or any other process. If such a lock is held, set *pResOut
** to a non-zero value otherwise *pResOut is set to zero.  The return value
** is set to SQLITE_OK unless an I/O error occurs during lock checking.
*/
static int _rtthread_io_check_reserved_lock(sqlite3_file *file_id, int *pResOut)
{
    RTTHREAD_SQLITE_FILE_T *file = (RTTHREAD_SQLITE_FILE_T*)file_id;
    rt_sem_t psem = &file->sem;
    int reserved = 0;

    /* Check if a thread in this process holds such a lock */
    if (file->eFileLock > SHARED_LOCK)
    {
        reserved = 1;
    }

    /* Otherwise see if some other process holds it. */
    if (!reserved)
    {
        if (rt_sem_trytake(psem) != RT_EOK)
        {
            /* someone else has the lock when we are in NO_LOCK */
            reserved = (file->eFileLock < SHARED_LOCK);
        }
        else
        {
            /* we could have it if we want it */
            rt_sem_release(psem);
        }
    }

    *pResOut = reserved;
    return SQLITE_OK;
}

/*
** Lock the file with the lock specified by parameter eFileLock - one
** of the following:
**
**     (1) SHARED_LOCK
**     (2) RESERVED_LOCK
**     (3) PENDING_LOCK
**     (4) EXCLUSIVE_LOCK
**
** Sometimes when requesting one lock state, additional lock states
** are inserted in between.  The locking might fail on one of the later
** transitions leaving the lock state different from what it started but
** still short of its goal.  The following chart shows the allowed
** transitions and the inserted intermediate states:
**
**    UNLOCKED -> SHARED
**    SHARED -> RESERVED
**    SHARED -> (PENDING) -> EXCLUSIVE
**    RESERVED -> (PENDING) -> EXCLUSIVE
**    PENDING -> EXCLUSIVE
**
** Semaphore locks only really support EXCLUSIVE locks.  We track intermediate
** lock states in the sqlite3_file structure, but all locks SHARED or
** above are really EXCLUSIVE locks and exclude all other processes from
** access the file.
**
** This routine will only increase a lock.  Use the sqlite3OsUnlock()
** routine to lower a locking level.
*/
static int _rtthread_io_lock(sqlite3_file *file_id, int eFileLock)
{
    RTTHREAD_SQLITE_FILE_T *file = (RTTHREAD_SQLITE_FILE_T*)file_id;
    rt_sem_t psem = &file->sem;
    int rc = SQLITE_OK;

    /* if we already have a lock, it is exclusive.
    ** Just adjust level and punt on outta here. */
    if (file->eFileLock > NO_LOCK)
    {
        file->eFileLock = eFileLock;
        rc = SQLITE_OK;
        goto sem_end_lock;
    }

    /* lock semaphore now but bail out when already locked. */
    if (rt_sem_trytake(psem) != RT_EOK)
    {
        rc = SQLITE_BUSY;
        goto sem_end_lock;
    }

    /* got it, set the type and return ok */
    file->eFileLock = eFileLock;

sem_end_lock:
    return rc;
}

/*
** Lower the locking level on file descriptor pFile to eFileLock.  eFileLock
** must be either NO_LOCK or SHARED_LOCK.
**
** If the locking level of the file descriptor is already at or below
** the requested locking level, this routine is a no-op.
*/
static int _rtthread_io_unlock(sqlite3_file *file_id, int eFileLock)
{
    RTTHREAD_SQLITE_FILE_T *file = (RTTHREAD_SQLITE_FILE_T*)file_id;
    rt_sem_t psem = &file->sem;

    assert(eFileLock <= SHARED_LOCK);

    /* no-op if possible */
    if (file->eFileLock == eFileLock)
    {
        return SQLITE_OK;
    }

    /* shared can just be set because we always have an exclusive */
    if (eFileLock == SHARED_LOCK)
    {
        file->eFileLock = SHARED_LOCK;
        return SQLITE_OK;
    }

    /* no, really unlock. */
    rt_sem_release(psem);

    file->eFileLock = NO_LOCK;
    return SQLITE_OK;
}

static int _rtthread_io_close(sqlite3_file *file_id)
{
    int rc = 0;
    RTTHREAD_SQLITE_FILE_T *file = (RTTHREAD_SQLITE_FILE_T*)file_id;

    if (file->fd >= 0)
    {
        _rtthread_io_unlock(file_id, NO_LOCK);
        rc = close(file->fd);
        file->fd = -1;
    }

    return rc;
}

static int _rtthread_fcntl_size_hint(sqlite3_file *file_id, i64 nByte)
{
    RTTHREAD_SQLITE_FILE_T *file = (RTTHREAD_SQLITE_FILE_T*)file_id;

    if (file->szChunk > 0)
    {
        i64 nSize;                    /* Required file size */
        struct stat buf;              /* Used to hold return values of fstat() */

        if (fstat(file->fd, &buf))
        {
            return SQLITE_IOERR_FSTAT;
        }

        nSize = ((nByte + file->szChunk - 1) / file->szChunk) * file->szChunk;

        if (nSize > (i64)buf.st_size)
        {
            /* If the OS does not have posix_fallocate(), fake it. Write a
            ** single byte to the last byte in each block that falls entirely
            ** within the extended region. Then, if required, a single byte
            ** at offset (nSize-1), to set the size of the file correctly.
            ** This is a similar technique to that used by glibc on systems
            ** that do not have a real fallocate() call.
            */
            int nBlk = buf.st_blksize;  /* File-system block size */
            int nWrite = 0;             /* Number of bytes written by seekAndWrite */
            i64 iWrite;                 /* Next offset to write to */

            iWrite = (buf.st_size / nBlk) * nBlk + nBlk - 1;
            assert(iWrite >= buf.st_size);
            assert(((iWrite + 1) % nBlk) == 0);

            for (/*no-op*/; iWrite < nSize + nBlk - 1; iWrite += nBlk)
            {
                if (iWrite >= nSize)
                {
                    iWrite = nSize - 1;
                }

                nWrite = _rtthread_io_write(file_id, "", 1, iWrite);

                if (nWrite != 1)
                {
                    return SQLITE_IOERR_WRITE;
                }
            }
        }
    }

    return SQLITE_OK;
}

/*
** Information and control of an open file handle.
*/
static int _rtthread_io_file_ctrl(sqlite3_file *file_id, int op, void *pArg)
{
    RTTHREAD_SQLITE_FILE_T *file = (RTTHREAD_SQLITE_FILE_T*)file_id;

    switch( op )
    {
    case SQLITE_FCNTL_LOCKSTATE: {
        *(int*)pArg = file->eFileLock;
        return SQLITE_OK;
    }

    case SQLITE_LAST_ERRNO: {
        *(int*)pArg = 0;
        return SQLITE_OK;
    }

    case SQLITE_FCNTL_CHUNK_SIZE: {
        file->szChunk = *(int *)pArg;
        return SQLITE_OK;
    }

    case SQLITE_FCNTL_SIZE_HINT: {
        int rc;
        rc = _rtthread_fcntl_size_hint(file_id, *(i64 *)pArg);
        return rc;
    }

    case SQLITE_FCNTL_PERSIST_WAL: {
        return SQLITE_OK;
    }

    case SQLITE_FCNTL_POWERSAFE_OVERWRITE: {
        return SQLITE_OK;
    }

    case SQLITE_FCNTL_VFSNAME: {
        *(char**)pArg = sqlite3_mprintf("%s", file->pvfs->zName);
        return SQLITE_OK;
    }

    case SQLITE_FCNTL_TEMPFILENAME: {
        char *zTFile = sqlite3_malloc(file->pvfs->mxPathname );

        if( zTFile )
        {
            _rtthread_get_temp_name(file->pvfs->mxPathname, zTFile);
            *(char**)pArg = zTFile;
        }
        return SQLITE_OK;
    }
    }

    return SQLITE_NOTFOUND;
}

static int _rtthread_io_sector_size(sqlite3_file *file_id)
{
    return SQLITE_DEFAULT_SECTOR_SIZE;
}

static int _rtthread_io_device_characteristics(sqlite3_file *file_id)
{
    return 0;
}

/*
** If possible, return a pointer to a mapping of file fd starting at offset
** iOff. The mapping must be valid for at least nAmt bytes.
**
** If such a pointer can be obtained, store it in *pp and return SQLITE_OK.
** Or, if one cannot but no error occurs, set *pp to 0 and return SQLITE_OK.
** Finally, if an error does occur, return an SQLite error code. The final
** value of *pp is undefined in this case.
**
** If this function does return a pointer, the caller must eventually
** release the reference by calling unixUnfetch().
*/
static int _rtthread_io_fetch(sqlite3_file *file_id, i64 iOff, int nAmt, void **pp)
{
    *pp = 0;

    return SQLITE_OK;
}

/*
** If the third argument is non-NULL, then this function releases a
** reference obtained by an earlier call to unixFetch(). The second
** argument passed to this function must be the same as the corresponding
** argument that was passed to the unixFetch() invocation.
**
** Or, if the third argument is NULL, then this function is being called
** to inform the VFS layer that, according to POSIX, any existing mapping
** may now be invalid and should be unmapped.
*/
static int _rtthread_io_unfetch(sqlite3_file *fd, i64 iOff, void *p)
{
    return SQLITE_OK;
}

static const sqlite3_io_methods _rtthread_io_method = {
    3,
    _rtthread_io_close,
    _rtthread_io_read,
    _rtthread_io_write,
    _rtthread_io_truncate,
    _rtthread_io_sync,
    _rtthread_io_file_size,
    _rtthread_io_lock,
    _rtthread_io_unlock,
    _rtthread_io_check_reserved_lock,
    _rtthread_io_file_ctrl,
    _rtthread_io_sector_size,
    _rtthread_io_device_characteristics,
    0,
    0,
    0,
    0,
    _rtthread_io_fetch,
    _rtthread_io_unfetch
};

