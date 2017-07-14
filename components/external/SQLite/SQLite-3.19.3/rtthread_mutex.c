#if defined(SQLITE_MUTEX_RTTHREAD)

/*
* rt-thread mutex
*/
struct sqlite3_mutex {
    struct rt_mutex mutex;          /* Mutex controlling the lock */
    int id;                         /* Mutex type */
};

SQLITE_PRIVATE void sqlite3MemoryBarrier(void)
{

}

/*
** Initialize and deinitialize the mutex subsystem.
The argument to sqlite3_mutex_alloc() must one of these integer constants:
    SQLITE_MUTEX_FAST
    SQLITE_MUTEX_RECURSIVE
    SQLITE_MUTEX_STATIC_MASTER
    SQLITE_MUTEX_STATIC_MEM
    SQLITE_MUTEX_STATIC_OPEN
    SQLITE_MUTEX_STATIC_PRNG
    SQLITE_MUTEX_STATIC_LRU
    SQLITE_MUTEX_STATIC_PMEM
    SQLITE_MUTEX_STATIC_APP1
    SQLITE_MUTEX_STATIC_APP2
    SQLITE_MUTEX_STATIC_APP3
    SQLITE_MUTEX_STATIC_VFS1
    SQLITE_MUTEX_STATIC_VFS2
    SQLITE_MUTEX_STATIC_VFS3
The first two constants (SQLITE_MUTEX_FAST and SQLITE_MUTEX_RECURSIVE)
cause sqlite3_mutex_alloc() to create a new mutex. The new mutex is recursive
when SQLITE_MUTEX_RECURSIVE is used but not necessarily so when SQLITE_MUTEX_FAST
is used. The mutex implementation does not need to make a distinction between
SQLITE_MUTEX_RECURSIVE and SQLITE_MUTEX_FAST if it does not want to.
SQLite will only request a recursive mutex in cases where it really needs one.
If a faster non-recursive mutex implementation is available on the host platform,
the mutex subsystem might return such a mutex in response to SQLITE_MUTEX_FAST.

The other allowed parameters to sqlite3_mutex_alloc()
(anything other than SQLITE_MUTEX_FAST and SQLITE_MUTEX_RECURSIVE) each return
a pointer to a static preexisting mutex. Nine static mutexes are used by the
current version of SQLite. Future versions of SQLite may add additional static
mutexes. Static mutexes are for internal use by SQLite only. Applications that
use SQLite mutexes should use only the dynamic mutexes returned by SQLITE_MUTEX_FAST
or SQLITE_MUTEX_RECURSIVE.

Note that if one of the dynamic mutex parameters (SQLITE_MUTEX_FAST or SQLITE_MUTEX_RECURSIVE)
is used then sqlite3_mutex_alloc() returns a different mutex on every call.
For the static mutex types, the same mutex is returned on every call that has the same type number.

*/
static sqlite3_mutex _static_mutex[12];

static int _rtthread_mtx_init(void)
{
    int i;
    rt_err_t err;

    for (i = 0; i < sizeof(_static_mutex) / sizeof(_static_mutex[0]); i++)
    {
        err = rt_mutex_init(&_static_mutex[i].mutex, "sqlmtx", RT_IPC_FLAG_PRIO);

        if (err != RT_EOK)
        {
            return SQLITE_ERROR;
        }
    }

    return SQLITE_OK;
}

static int _rtthread_mtx_end(void)
{
    int i;
    rt_err_t err;

    for (i = 0; i < sizeof(_static_mutex) / sizeof(_static_mutex[0]); i++)
    {
        err = rt_mutex_detach(&_static_mutex[i].mutex);
        _static_mutex[i].mutex.owner = 0;
        _static_mutex[i].mutex.hold = 0;

        if (err != RT_EOK)
        {
            return SQLITE_ERROR;
        }
    }

    return SQLITE_OK;
}

static sqlite3_mutex * _rtthread_mtx_alloc(int id)
{
    sqlite3_mutex *p = NULL;

    switch (id)
    {
    case SQLITE_MUTEX_FAST:
    case SQLITE_MUTEX_RECURSIVE:
        p = sqlite3Malloc(sizeof(sqlite3_mutex));

        if (p != NULL)
        {
            rt_mutex_init(&p->mutex, "sqlmtx", RT_IPC_FLAG_PRIO);
            p->id = id;
        }
        break;

    default:
        assert(id - 2 >= 0);
        assert(id - 2 < ArraySize(_static_mutex) );
        p = &_static_mutex[id - 2];
        p->id = id;
        break;
    }

    return p;
}

static void _rtthread_mtx_free(sqlite3_mutex * p)
{
    assert(p != 0);

    rt_mutex_detach(&p->mutex);

    switch (p->id)
    {
    case SQLITE_MUTEX_FAST:
    case SQLITE_MUTEX_RECURSIVE:
        sqlite3_free(p);
        break;

    default:
        break;
    }
}

static void _rtthread_mtx_enter(sqlite3_mutex *p)
{
    assert(p != 0);

    rt_mutex_take(&p->mutex, RT_WAITING_FOREVER);
}

static int _rtthread_mtx_try(sqlite3_mutex *p)
{
    assert(p != 0);

    if (rt_mutex_take(&p->mutex, RT_WAITING_NO) != RT_EOK)
    {
        return SQLITE_BUSY;
    }

    return SQLITE_OK;
}

static void _rtthread_mtx_leave(sqlite3_mutex *p)
{
    assert(p != 0);

    rt_mutex_release(&p->mutex);
}

#ifdef SQLITE_DEBUG

/*
    If the argument to sqlite3_mutex_held() is a NULL pointer then the routine
    should return 1. This seems counter-intuitive since clearly the mutex cannot
    be held if it does not exist. But the reason the mutex does not exist is
    because the build is not using mutexes. And we do not want the assert()
    containing the call to sqlite3_mutex_held() to fail, so a non-zero return
    is the appropriate thing to do. The sqlite3_mutex_notheld() interface should
    also return 1 when given a NULL pointer.
*/
static int _rtthread_mtx_held(sqlite3_mutex *p)
{
    if (p != 0)
    {
        if ((rt_thread_self() == p->mutex.owner) && (p->mutex.hold > 0))
        {
            return 1;
        }

        return 0;
    }

    return 1;
}

static int _rtthread_mtx_noheld(sqlite3_mutex *p)
{
    if (_rtthread_mtx_held(p))
    {
        return 0;
    }

    return 1;
}

#endif  /* SQLITE_DEBUG */

SQLITE_PRIVATE sqlite3_mutex_methods const *sqlite3DefaultMutex(void)
{
    static const sqlite3_mutex_methods sMutex = {
        _rtthread_mtx_init,
        _rtthread_mtx_end,
        _rtthread_mtx_alloc,
        _rtthread_mtx_free,
        _rtthread_mtx_enter,
        _rtthread_mtx_try,
        _rtthread_mtx_leave,
    #ifdef SQLITE_DEBUG
        _rtthread_mtx_held,
        _rtthread_mtx_noheld
    #else
        0,
        0
    #endif
    };

    return &sMutex;
}

#endif  /* SQLITE_MUTEX_RTTHREAD */

