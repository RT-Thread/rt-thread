#ifdef SQLITE_OS_RTTHREAD

#ifndef SQLITE_OMIT_LOAD_EXTENSION
    #error "rt-thread not support load extension, compile with SQLITE_OMIT_LOAD_EXTENSION."
#endif

#define RTTHREAD_MAX_PATHNAME       256

#include <dfs_posix.h>

/*
** Define various macros that are missing from some systems.
*/
#ifndef O_LARGEFILE
# define O_LARGEFILE 0
#endif
#ifdef SQLITE_DISABLE_LFS
# undef O_LARGEFILE
# define O_LARGEFILE 0
#endif
#ifndef O_NOFOLLOW
# define O_NOFOLLOW 0
#endif
#ifndef O_BINARY
# define O_BINARY 0
#endif

#ifndef RT_USING_NEWLIB

#ifndef EINTR
#define EINTR        4  /* Interrupted system call */
#endif

#ifndef ENOLCK
#define ENOLCK      46  /* No record locks available */
#endif

#ifndef EACCES
#define EACCES      13  /* Permission denied */
#endif

#ifndef EPERM
#define EPERM        1  /* Operation not permitted */
#endif

#ifndef ETIMEDOUT
#define ETIMEDOUT   145 /* Connection timed out */
#endif

#ifndef ENOTCONN
#define ENOTCONN    134 /* Transport endpoint is not connected */
#endif

#if defined(__GNUC__) || defined(__ADSPBLACKFIN__)
int _gettimeofday(struct timeval *tp, void *ignore) __attribute__((weak));
int _gettimeofday(struct timeval *tp, void *ignore)
#elif defined(__CC_ARM)
__weak int _gettimeofday(struct timeval *tp, void *ignore)
#elif defined(__IAR_SYSTEMS_ICC__)
    #if __VER__ > 540
    __weak
    #endif
int _gettimeofday(struct timeval *tp, void *ignore)
#else
int _gettimeofday(struct timeval *tp, void *ignore)
#endif
{
    return 0;
}

#endif /* RT_USING_NEWLIB */

static int _Access(const char *pathname, int mode)
{
    int fd;

    fd = open(pathname, O_RDONLY, mode);

    if (fd >= 0)
    {
        close(fd);
        return 0;
    }

    return -1;
}

#define _RTTHREAD_LOG_ERROR(a,b,c) _rtthread_log_error_at_line(a,b,c,__LINE__)

static int _rtthread_log_error_at_line(
  int errcode,                    /* SQLite error code */
  const char *zFunc,              /* Name of OS function that failed */
  const char *zPath,              /* File path associated with error */
  int iLine                       /* Source line number where error occurred */
)
{
    char *zErr;                     /* Message from strerror() or equivalent */
    int iErrno = errno;             /* Saved syscall error number */

    /* If this is not a threadsafe build (SQLITE_THREADSAFE==0), then use
    ** the strerror() function to obtain the human-readable error message
    ** equivalent to errno. Otherwise, use strerror_r().
    */
#if SQLITE_THREADSAFE && defined(HAVE_STRERROR_R)
    char aErr[80];
    memset(aErr, 0, sizeof(aErr));
    zErr = aErr;

    /* If STRERROR_R_CHAR_P (set by autoconf scripts) or __USE_GNU is defined,
    ** assume that the system provides the GNU version of strerror_r() that
    ** returns a pointer to a buffer containing the error message. That pointer
    ** may point to aErr[], or it may point to some static storage somewhere.
    ** Otherwise, assume that the system provides the POSIX version of
    ** strerror_r(), which always writes an error message into aErr[].
    **
    ** If the code incorrectly assumes that it is the POSIX version that is
    ** available, the error message will often be an empty string. Not a
    ** huge problem. Incorrectly concluding that the GNU version is available
    ** could lead to a segfault though.
    */
#if defined(STRERROR_R_CHAR_P) || defined(__USE_GNU)
    zErr =
#endif
    strerror_r(iErrno, aErr, sizeof(aErr)-1);

#elif SQLITE_THREADSAFE
    /* This is a threadsafe build, but strerror_r() is not available. */
    zErr = "";
#else
    /* Non-threadsafe build, use strerror(). */
    zErr = strerror(iErrno);
#endif

    if( zPath==0 )
        zPath = "";

    sqlite3_log(errcode, "os_rtthread.c:%d: (%d) %s(%s) - %s",
                iLine, iErrno, zFunc, zPath, zErr);

    return errcode;
}

typedef struct
{
    sqlite3_io_methods const *pMethod;
    sqlite3_vfs *pvfs;
    int fd;
    int eFileLock;
    int szChunk;
    struct rt_semaphore sem;
} RTTHREAD_SQLITE_FILE_T;

static const char* _rtthread_temp_file_dir(void)
{
    const char *azDirs[] = {
        0,
        "/sql",
        "/sql/tmp"
        "/tmp",
        0        /* List terminator */
    };
    unsigned int i;
    struct stat buf;
    const char *zDir = 0;

    azDirs[0] = sqlite3_temp_directory;

    for (i = 0; i < sizeof(azDirs) / sizeof(azDirs[0]); zDir = azDirs[i++])
    {
        if( zDir == 0 ) continue;
        if( stat(zDir, &buf) ) continue;
        if( !S_ISDIR(buf.st_mode) ) continue;
        break;
    }

    return zDir;
}

/*
** Create a temporary file name in zBuf.  zBuf must be allocated
** by the calling process and must be big enough to hold at least
** pVfs->mxPathname bytes.
*/
static int _rtthread_get_temp_name(int nBuf, char *zBuf)
{
    const unsigned char zChars[] = "abcdefghijklmnopqrstuvwxyz"
                                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                    "0123456789";
    unsigned int i, j;
    const char *zDir;

    zDir = _rtthread_temp_file_dir();

    if (zDir == 0)
    {
        zDir = ".";
    }

    /* Check that the output buffer is large enough for the temporary file
    ** name. If it is not, return SQLITE_ERROR.
    */
    if ((strlen(zDir) + strlen(SQLITE_TEMP_FILE_PREFIX) + 18) >= (size_t)nBuf)
    {
        return SQLITE_ERROR;
    }

    do {
        sqlite3_snprintf(nBuf-18, zBuf, "%s/"SQLITE_TEMP_FILE_PREFIX, zDir);
        j = (int)strlen(zBuf);
        sqlite3_randomness(15, &zBuf[j]);

        for (i = 0; i < 15; i++, j++)
        {
            zBuf[j] = (char)zChars[((unsigned char)zBuf[j]) % (sizeof(zChars) - 1)];
        }

        zBuf[j] = 0;
        zBuf[j + 1] = 0;
    } while (_Access(zBuf, 0) == 0);

    return SQLITE_OK;
}

#include "rtthread_io_methods.c"

/*
** Invoke open().  Do so multiple times, until it either succeeds or
** fails for some reason other than EINTR.
**
** If the file creation mode "m" is 0 then set it to the default for
** SQLite.  The default is SQLITE_DEFAULT_FILE_PERMISSIONS (normally
** 0644) as modified by the system umask.  If m is not 0, then
** make the file creation mode be exactly m ignoring the umask.
**
** The m parameter will be non-zero only when creating -wal, -journal,
** and -shm files.  We want those files to have *exactly* the same
** permissions as their original database, unadulterated by the umask.
** In that way, if a database file is -rw-rw-rw or -rw-rw-r-, and a
** transaction crashes and leaves behind hot journals, then any
** process that is able to write to the database will also be able to
** recover the hot journals.
*/
static int _rtthread_fs_open(const char *file_path, int f, mode_t m)
{
    int fd = -1;

    while (fd < 0)
    {
    #if defined(O_CLOEXEC)
        fd = open(file_path, f | O_CLOEXEC, m);
    #else
        fd = open(file_path, f, m);
    #endif

        if (fd < 0)
        {
            if (errno == EINTR)
                continue;

            break;
        }
    }

    return fd;
}

static int _rtthread_vfs_open(sqlite3_vfs *pvfs, const char *file_path, sqlite3_file *file_id, int flags, int *pOutFlags)
{
    RTTHREAD_SQLITE_FILE_T *p;
    int fd;
    int eType = flags & 0xFFFFFF00;  /* Type of file to open */
    int rc = SQLITE_OK;            /* Function Return Code */
    int openFlags = 0;
    mode_t openMode = 0;

    int isExclusive  = (flags & SQLITE_OPEN_EXCLUSIVE);
    int isDelete     = (flags & SQLITE_OPEN_DELETEONCLOSE);
    int isCreate     = (flags & SQLITE_OPEN_CREATE);
    int isReadonly   = (flags & SQLITE_OPEN_READONLY);
    int isReadWrite  = (flags & SQLITE_OPEN_READWRITE);

    /* If argument zPath is a NULL pointer, this function is required to open
    ** a temporary file. Use this buffer to store the file name in.
    */
    char zTmpname[RTTHREAD_MAX_PATHNAME + 2];

    p = (RTTHREAD_SQLITE_FILE_T*)file_id;

    /* Check the following statements are true:
    **
    **   (a) Exactly one of the READWRITE and READONLY flags must be set, and
    **   (b) if CREATE is set, then READWRITE must also be set, and
    **   (c) if EXCLUSIVE is set, then CREATE must also be set.
    **   (d) if DELETEONCLOSE is set, then CREATE must also be set.
    */
    assert((isReadonly==0 || isReadWrite==0) && (isReadWrite || isReadonly));
    assert(isCreate==0 || isReadWrite);
    assert(isExclusive==0 || isCreate);
    assert(isDelete==0 || isCreate);

    /* The main DB, main journal, WAL file and master journal are never
    ** automatically deleted. Nor are they ever temporary files.  */
    assert( (!isDelete && file_path) || eType!=SQLITE_OPEN_MAIN_DB );
    assert( (!isDelete && file_path) || eType!=SQLITE_OPEN_MAIN_JOURNAL );
    assert( (!isDelete && file_path) || eType!=SQLITE_OPEN_MASTER_JOURNAL );
    assert( (!isDelete && file_path) || eType!=SQLITE_OPEN_WAL );

    /* Assert that the upper layer has set one of the "file-type" flags. */
    assert( eType==SQLITE_OPEN_MAIN_DB      || eType==SQLITE_OPEN_TEMP_DB
        || eType==SQLITE_OPEN_MAIN_JOURNAL || eType==SQLITE_OPEN_TEMP_JOURNAL
        || eType==SQLITE_OPEN_SUBJOURNAL   || eType==SQLITE_OPEN_MASTER_JOURNAL
        || eType==SQLITE_OPEN_TRANSIENT_DB || eType==SQLITE_OPEN_WAL
    );

    /* Database filenames are double-zero terminated if they are not
    ** URIs with parameters.  Hence, they can always be passed into
    ** sqlite3_uri_parameter(). */
    assert((eType != SQLITE_OPEN_MAIN_DB) || (flags & SQLITE_OPEN_URI) || file_path[strlen(file_path) + 1] == 0);

    memset(p, 0, sizeof(RTTHREAD_SQLITE_FILE_T));
    if (!file_path)
    {
        rc = _rtthread_get_temp_name(RTTHREAD_MAX_PATHNAME + 2, zTmpname);
        if (rc != SQLITE_OK )
        {
            return rc;
        }
        file_path = zTmpname;

        /* Generated temporary filenames are always double-zero terminated
        ** for use by sqlite3_uri_parameter(). */
        assert(file_path[strlen(file_path) + 1] == 0);
    }

    /* Determine the value of the flags parameter passed to POSIX function
    ** open(). These must be calculated even if open() is not called, as
    ** they may be stored as part of the file handle and used by the
    ** 'conch file' locking functions later on.  */
    if (isReadonly)  openFlags |= O_RDONLY;
    if (isReadWrite) openFlags |= O_RDWR;
    if (isCreate)    openFlags |= O_CREAT;
    if (isExclusive) openFlags |= (O_EXCL | O_NOFOLLOW);
    openFlags |= (O_LARGEFILE | O_BINARY);

    fd = _rtthread_fs_open(file_path, openFlags, openMode);

    if (fd < 0 && (errno != DFS_STATUS_EISDIR) && isReadWrite && !isExclusive)
    {
        /* Failed to open the file for read/write access. Try read-only. */
        flags &= ~(SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
        openFlags &= ~(O_RDWR | O_CREAT);
        flags |= SQLITE_OPEN_READONLY;
        openFlags |= O_RDONLY;
        isReadonly = 1;
        fd = _rtthread_fs_open(file_path, openFlags, openMode);
    }

    if (fd < 0)
    {
        rc = _RTTHREAD_LOG_ERROR(SQLITE_CANTOPEN_BKPT, "open", file_path);
        return rc;
    }

    if (pOutFlags)
    {
        *pOutFlags = flags;
    }

    if (isDelete)
    {
        unlink(file_path);
    }

    p->fd = fd;
    p->pMethod = &_rtthread_io_method;
    p->eFileLock = NO_LOCK;
    p->szChunk = 0;
    p->pvfs = pvfs;
    rt_sem_init(&p->sem, "vfssem", 1, RT_IPC_FLAG_PRIO);

    return rc;
}

int _rtthread_vfs_delete(sqlite3_vfs* pvfs, const char *file_path, int syncDir)
{
    int rc = SQLITE_OK;

    if (unlink(file_path) == (-1))
    {
        if (errno == DFS_STATUS_ENOENT)
        {
            rc = SQLITE_IOERR_DELETE_NOENT;
        }
        else
        {
            rc = _RTTHREAD_LOG_ERROR(SQLITE_IOERR_DELETE, "unlink", file_path);
        }

        return rc;
    }

    // sync dir: open dir -> fsync -> close
    if ((syncDir & 1) != 0)
    {
        int ii;
        int fd = -1;
        char zDirname[RTTHREAD_MAX_PATHNAME + 1];

        sqlite3_snprintf(RTTHREAD_MAX_PATHNAME, zDirname, "%s", file_path);
        for (ii=(int)strlen(zDirname); ii > 1 && zDirname[ii] != '/'; ii--);

        if (ii > 0)
        {
            zDirname[ii] = '\0';
            fd = _rtthread_fs_open(zDirname, O_RDONLY | O_BINARY, 0);
        }

        if (fd >= 0)
        {
            if (fsync(fd))
            {
                rc = _RTTHREAD_LOG_ERROR(SQLITE_IOERR_DIR_FSYNC, "fsync", file_path);
            }

            close(fd);
        }

        rc = SQLITE_OK;
    }

    return rc;
}

static int _rtthread_vfs_access(sqlite3_vfs* pvfs, const char *file_path, int flags, int *pResOut)
{
    int amode = 0;

#ifndef F_OK
# define F_OK 0
#endif
#ifndef R_OK
# define R_OK 4
#endif
#ifndef W_OK
# define W_OK 2
#endif

    switch (flags)
    {
    case SQLITE_ACCESS_EXISTS:
        amode = F_OK;
        break;

    case SQLITE_ACCESS_READWRITE:
        amode = W_OK | R_OK;
        break;

    case SQLITE_ACCESS_READ:
        amode = R_OK;
        break;

    default:
        _RTTHREAD_LOG_ERROR(flags, "access", file_path);
        return -1;
    }

    *pResOut = (_Access(file_path, amode) == 0);

    if (flags == SQLITE_ACCESS_EXISTS && *pResOut)
    {
        struct stat buf;

        if (0 == stat(file_path, &buf) && (buf.st_size == 0))
        {
            *pResOut = 0;
        }
    }

    return SQLITE_OK;
}

static int _rtthread_vfs_fullpathname(sqlite3_vfs* pvfs, const char *file_path, int nOut, char *zOut)
{
    assert(pvfs->mxPathname == RTTHREAD_MAX_PATHNAME);

    zOut[nOut - 1] = '\0';

    if (file_path[0] == '/')
    {
        sqlite3_snprintf(nOut, zOut, "%s", file_path);
    }
    else
    {
        int nCwd;

        if (getcwd(zOut, nOut - 1) == 0)
        {
            return _RTTHREAD_LOG_ERROR(SQLITE_CANTOPEN_BKPT, "getcwd", file_path);
        }

        nCwd = (int)strlen(zOut);
        sqlite3_snprintf(nOut - nCwd, &zOut[nCwd], "/%s", file_path);
    }

    return SQLITE_OK;
}

static int _rtthread_vfs_randomness(sqlite3_vfs* pvfs, int nByte, char *zOut)
{
    assert((size_t)nByte >= (sizeof(time_t) + sizeof(int)));

    memset(zOut, 0, nByte);
    {
        int i;
        char tick8, tick16;

        tick8 = (char)rt_tick_get();
        tick16 = (char)(rt_tick_get() >> 8);

        for (i = 0; i < nByte; i++)
        {
            zOut[i] = (char)(i ^ tick8 ^ tick16);
            tick8 = zOut[i];
            tick16 = ~(tick8 ^ tick16);
        }
    }

    return nByte;
}

static int _rtthread_vfs_sleep(sqlite3_vfs* pvfs, int microseconds)
{
    int millisecond = (microseconds + 999) / 1000;

    rt_thread_delay(rt_tick_from_millisecond(millisecond));

    return millisecond * 1000;
}

static int _rtthread_vfs_current_time_int64(sqlite3_vfs*, sqlite3_int64*);
static int _rtthread_vfs_current_time(sqlite3_vfs* pvfs, double* pnow)
{
    sqlite3_int64 i = 0;
    int rc;

    rc = _rtthread_vfs_current_time_int64(0, &i);

    *pnow = i / 86400000.0;

    return rc;
}

static int _rtthread_vfs_get_last_error(sqlite3_vfs* pvfs, int nBuf, char *zBuf)
{
    return 0;
}

static int _rtthread_vfs_current_time_int64(sqlite3_vfs* pvfs, sqlite3_int64*pnow)
{
#ifndef NO_GETTOD
#define NO_GETTOD 1
#endif

    static const sqlite3_int64 rtthreadEpoch = 24405875 * (sqlite3_int64)8640000;
    int rc = SQLITE_OK;

#if defined(NO_GETTOD)
    time_t t;
    time(&t);
    *pnow = ((sqlite3_int64)t) * 1000 + rtthreadEpoch;
#else

    struct timeval sNow;

    if (gettimeofday(&sNow, 0) == 0)
    {
        *pnow = rtthreadEpoch + 1000 * (sqlite3_int64)sNow.tv_sec + sNow.tv_usec / 1000;
    }
    else
    {
        rc = SQLITE_ERROR;
    }

#endif

#ifdef SQLITE_TEST

    if( sqlite3_current_time )
    {
        *pnow = 1000 * (sqlite3_int64)sqlite3_current_time + rtthreadEpoch;
    }

#endif

    return rc;
}

static int _rtthread_vfs_set_system_call(sqlite3_vfs* pvfs, const char *file_path, sqlite3_syscall_ptr pfn)
{
    return SQLITE_NOTFOUND;
}

static sqlite3_syscall_ptr _rtthread_vfs_get_system_call(sqlite3_vfs* pvfs, const char *file_path)
{
    return 0;
}

static const char*  _rtthread_vfs_next_system_call(sqlite3_vfs *pvfs, const char *file_path)
{
    return 0;
}

/*
** Initialize and deinitialize the operating system interface.
*/
SQLITE_API int sqlite3_os_init(void)
{
    static sqlite3_vfs _rtthread_vfs = {
        3,                     /* iVersion */
        sizeof(RTTHREAD_SQLITE_FILE_T),       /* szOsFile */
        RTTHREAD_MAX_PATHNAME, /* mxPathname */
        0,                     /* pNext */
        "rt-thread",               /* zName */
        0,           /* pAppData */
        _rtthread_vfs_open,               /* xOpen */
        _rtthread_vfs_delete,             /* xDelete */
        _rtthread_vfs_access,             /* xAccess */
        _rtthread_vfs_fullpathname,       /* xFullPathname */
        0,             /* xDlOpen */
        0,            /* xDlError */
        0,              /* xDlSym */
        0,            /* xDlClose */
        _rtthread_vfs_randomness,         /* xRandomness */
        _rtthread_vfs_sleep,              /* xSleep */
        _rtthread_vfs_current_time,        /* xCurrentTime */
        _rtthread_vfs_get_last_error,       /* xGetLastError */
        _rtthread_vfs_current_time_int64,   /* xCurrentTimeInt64 */
        _rtthread_vfs_set_system_call,      /* xSetSystemCall */
        _rtthread_vfs_get_system_call,      /* xGetSystemCall */
        _rtthread_vfs_next_system_call,     /* xNextSystemCall */
    };

    sqlite3_vfs_register(&_rtthread_vfs, 1);

    return SQLITE_OK;
}

SQLITE_API int sqlite3_os_end(void)
{
    return SQLITE_OK;
}

#endif  /* SQLITE_OS_RTTHREAD */

