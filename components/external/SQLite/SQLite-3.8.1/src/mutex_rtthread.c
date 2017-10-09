/*
** 2007 August 28
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** This file contains the C functions that implement mutexes for rtthread
*/
#include "sqliteInt.h"

/*
** The code in this file is only used if we are compiling threadsafe
** under rt-thread with rt_mutex.
**
** Note that this implementation requires a version of rt-thread that
** supports recursive mutexes.
*/
#ifdef SQLITE_MUTEX_RTTHREAD

#include <rtthread.h>

/*
** The sqlite3_mutex.id, sqlite3_mutex.nRef, and sqlite3_mutex.owner fields
** are necessary under two condidtions:  (1) Debug builds and (2) using
** home-grown mutexes.  Encapsulate these conditions into a single #define.
*/
#if defined(SQLITE_DEBUG) || defined(SQLITE_HOMEGROWN_RECURSIVE_MUTEX)
# define SQLITE_MUTEX_NREF 1
#else
# define SQLITE_MUTEX_NREF 0
#endif

/*
** Each recursive mutex is an instance of the following structure.
*/
struct sqlite3_mutex {
  struct rt_mutex mutex;     /* Mutex controlling the lock */
#if SQLITE_MUTEX_NREF
  int id;                    /* Mutex type */
  volatile int nRef;         /* Number of entrances */
  volatile rt_thread_t owner;  /* Thread that is within this mutex */
  int trace;                 /* True to trace changes */
#endif
};
#define RTT_MUTEX_INITIALIZER   { 0 }
#if SQLITE_MUTEX_NREF
#define SQLITE3_MUTEX_INITIALIZER { RTT_MUTEX_INITIALIZER, 0, 0, (rt_thread_t)0, 0 }
#else
#define SQLITE3_MUTEX_INITIALIZER { RTT_MUTEX_INITIALIZER }
#endif

/*
** The sqlite3_mutex_held() and sqlite3_mutex_notheld() routine are
** intended for use only inside assert() statements.  On some platforms,
** there might be race conditions that can cause these routines to
** deliver incorrect results.  In particular, if rtthread_equal() is
** not an atomic operation, then these routines might delivery
** incorrect results.  On most platforms, rtthread_equal() is a
** comparison of two integers and is therefore atomic.  But we are
** told that HPUX is not such a platform.  If so, then these routines
** will not always work correctly on HPUX.
**
** On those platforms where rtthread_equal() is not atomic, SQLite
** should be compiled without -DSQLITE_DEBUG and with -DNDEBUG to
** make sure no assert() statements are evaluated and hence these
** routines are never called.
*/
#if !defined(NDEBUG) || defined(SQLITE_DEBUG)
static int rtthreadMutexHeld(sqlite3_mutex *p){
  return (p->nRef != 0 && p->owner == rt_thread_self());
}
static int rtthreadMutexNotheld(sqlite3_mutex *p){
  return (p->nRef == 0 || p->owner != rt_thread_self());
}
#endif

/*
** Initialize and deinitialize the mutex subsystem.
*/
static int rtthreadMutexInit(void){ return SQLITE_OK; }
static int rtthreadMutexEnd(void){ return SQLITE_OK; }

/*
** The sqlite3_mutex_alloc() routine allocates a new
** mutex and returns a pointer to it.  If it returns NULL
** that means that a mutex could not be allocated.  SQLite
** will unwind its stack and return an error.  The argument
** to sqlite3_mutex_alloc() is one of these integer constants:
**
** <ul>
** <li>  SQLITE_MUTEX_FAST
** <li>  SQLITE_MUTEX_RECURSIVE
** <li>  SQLITE_MUTEX_STATIC_MASTER
** <li>  SQLITE_MUTEX_STATIC_MEM
** <li>  SQLITE_MUTEX_STATIC_MEM2
** <li>  SQLITE_MUTEX_STATIC_PRNG
** <li>  SQLITE_MUTEX_STATIC_LRU
** <li>  SQLITE_MUTEX_STATIC_PMEM
** </ul>
**
** The first two constants cause sqlite3_mutex_alloc() to create
** a new mutex.  The new mutex is recursive when SQLITE_MUTEX_RECURSIVE
** is used but not necessarily so when SQLITE_MUTEX_FAST is used.
** The mutex implementation does not need to make a distinction
** between SQLITE_MUTEX_RECURSIVE and SQLITE_MUTEX_FAST if it does
** not want to.  But SQLite will only request a recursive mutex in
** cases where it really needs one.  If a faster non-recursive mutex
** implementation is available on the host platform, the mutex subsystem
** might return such a mutex in response to SQLITE_MUTEX_FAST.
**
** The other allowed parameters to sqlite3_mutex_alloc() each return
** a pointer to a static preexisting mutex.  Six static mutexes are
** used by the current version of SQLite.  Future versions of SQLite
** may add additional static mutexes.  Static mutexes are for internal
** use by SQLite only.  Applications that use SQLite mutexes should
** use only the dynamic mutexes returned by SQLITE_MUTEX_FAST or
** SQLITE_MUTEX_RECURSIVE.
**
** Note that if one of the dynamic mutex parameters (SQLITE_MUTEX_FAST
** or SQLITE_MUTEX_RECURSIVE) is used then sqlite3_mutex_alloc()
** returns a different mutex on every call.  But for the static
** mutex types, the same mutex is returned on every call that has
** the same type number.
*/
static sqlite3_mutex* rtthreadMutexAlloc(int iType){
  static sqlite3_mutex staticMutexes[] = {
    SQLITE3_MUTEX_INITIALIZER,
    SQLITE3_MUTEX_INITIALIZER,
    SQLITE3_MUTEX_INITIALIZER,
    SQLITE3_MUTEX_INITIALIZER,
    SQLITE3_MUTEX_INITIALIZER,
    SQLITE3_MUTEX_INITIALIZER
  };
  sqlite3_mutex *p;
  switch( iType ){
    case SQLITE_MUTEX_RECURSIVE: {
      p = sqlite3MallocZero( sizeof(*p) );
      if( p ){
        /* Use a recursive mutex if it is available */
       rt_mutex_init(&p->mutex, "sqlmtx", RT_IPC_FLAG_PRIO);
#if SQLITE_MUTEX_NREF
        p->id = iType;
#endif
      }
      break;
    }
    case SQLITE_MUTEX_FAST: {
      p = sqlite3MallocZero( sizeof(*p) );
      if( p ){
#if SQLITE_MUTEX_NREF
        p->id = iType;
#endif
        rt_mutex_init(&p->mutex, "sqlmtx", RT_IPC_FLAG_PRIO);
      }
      break;
    }
    default: {
      assert( iType-2 >= 0 );
      assert( iType-2 < ArraySize(staticMutexes) );
      p = &staticMutexes[iType-2];
#if SQLITE_MUTEX_NREF
      p->id = iType;
#endif
      rt_mutex_init(&p->mutex, "sqlmtx", RT_IPC_FLAG_PRIO);
      break;
    }
  }
  return p;
}


/*
** This routine deallocates a previously
** allocated mutex.  SQLite is careful to deallocate every
** mutex that it allocates.
*/
static void rtthreadMutexFree(sqlite3_mutex *p){
  assert( p->nRef==0 );
  assert( p->id==SQLITE_MUTEX_FAST || p->id==SQLITE_MUTEX_RECURSIVE );
  rt_mutex_detach(&p->mutex);
  sqlite3_free(p);
}

/*
** The sqlite3_mutex_enter() and sqlite3_mutex_try() routines attempt
** to enter a mutex.  If another thread is already within the mutex,
** sqlite3_mutex_enter() will block and sqlite3_mutex_try() will return
** SQLITE_BUSY.  The sqlite3_mutex_try() interface returns SQLITE_OK
** upon successful entry.  Mutexes created using SQLITE_MUTEX_RECURSIVE can
** be entered multiple times by the same thread.  In such cases the,
** mutex must be exited an equal number of times before another thread
** can enter.  If the same thread tries to enter any other kind of mutex
** more than once, the behavior is undefined.
*/
static void rtthreadMutexEnter(sqlite3_mutex *p){
  assert( p->id==SQLITE_MUTEX_RECURSIVE || rtthreadMutexNotheld(p) );

#ifdef SQLITE_HOMEGROWN_RECURSIVE_MUTEX
  /* If recursive mutexes are not available, then we have to grow
  ** our own.  This implementation assumes that rtthread_equal()
  ** is atomic - that it cannot be deceived into thinking self
  ** and p->owner are equal if p->owner changes between two values
  ** that are not equal to self while the comparison is taking place.
  ** This implementation also assumes a coherent cache - that
  ** separate processes cannot read different values from the same
  ** address at the same time.  If either of these two conditions
  ** are not met, then the mutexes will fail and problems will result.
  */
  {
    rt_thread_t self = rt_thread_self();
    if( p->nRef>0 && (p->owner == self) ){
      p->nRef++;
    }else{
      rt_mutex_take(&p->mutex, RT_WAITING_FOREVER);
      assert( p->nRef==0 );
      p->owner = self;
      p->nRef = 1;
    }
  }
#else
  /* Use the built-in recursive mutexes if they are available.
  */
  rt_mutex_take(&p->mutex, RT_WAITING_FOREVER);
#if SQLITE_MUTEX_NREF
  assert( p->nRef>0 || p->owner==0 );
  p->owner = rt_thread_self();
  p->nRef++;
#endif
#endif

#ifdef SQLITE_DEBUG
  if( p->trace ){
    rt_kprintf("enter mutex %p (%d) with nRef=%d\n", p, p->trace, p->nRef);
  }
#endif
}
static int rtthreadMutexTry(sqlite3_mutex *p){
  int rc;
  assert( p->id==SQLITE_MUTEX_RECURSIVE || rtthreadMutexNotheld(p) );

#ifdef SQLITE_HOMEGROWN_RECURSIVE_MUTEX
  /* If recursive mutexes are not available, then we have to grow
  ** our own.  This implementation assumes that rtthread_equal()
  ** is atomic - that it cannot be deceived into thinking self
  ** and p->owner are equal if p->owner changes between two values
  ** that are not equal to self while the comparison is taking place.
  ** This implementation also assumes a coherent cache - that
  ** separate processes cannot read different values from the same
  ** address at the same time.  If either of these two conditions
  ** are not met, then the mutexes will fail and problems will result.
  */
  {
    rt_thread_t self = rt_thread_self();
    if( p->nRef>0 && (p->owner == self) ){
      p->nRef++;
      rc = SQLITE_OK;
    }else if( rt_mutex_take(&p->mutex, RT_WAITING_NO)==RT_EOK ){
      assert( p->nRef==0 );
      p->owner = self;
      p->nRef = 1;
      rc = SQLITE_OK;
    }else{
      rc = SQLITE_BUSY;
    }
  }
#else
  /* Use the built-in recursive mutexes if they are available.
  */
  if( rt_mutex_take(&p->mutex, RT_WAITING_NO)==RT_EOK ){
#if SQLITE_MUTEX_NREF
    p->owner = rt_thread_self();
    p->nRef++;
#endif
    rc = SQLITE_OK;
  }else{
    rc = SQLITE_BUSY;
  }
#endif

#ifdef SQLITE_DEBUG
  if( rc==SQLITE_OK && p->trace ){
    rt_kprintf("enter mutex %p (%d) with nRef=%d\n", p, p->trace, p->nRef);
  }
#endif
  return rc;
}

/*
** The sqlite3_mutex_leave() routine exits a mutex that was
** previously entered by the same thread.  The behavior
** is undefined if the mutex is not currently entered or
** is not currently allocated.  SQLite will never do either.
*/
static void rtthreadMutexLeave(sqlite3_mutex *p){
  assert( rtthreadMutexHeld(p) );
#if SQLITE_MUTEX_NREF
  p->nRef--;
  if( p->nRef==0 ) p->owner = 0;
#endif
  assert( p->nRef==0 || p->id==SQLITE_MUTEX_RECURSIVE );

#ifdef SQLITE_HOMEGROWN_RECURSIVE_MUTEX
  if( p->nRef==0 ){
    rt_mutex_release(&p->mutex);
  }
#else
  rt_mutex_release(&p->mutex);
#endif

#ifdef SQLITE_DEBUG
  if( p->trace ){
    rt_kprintf("leave mutex %p (%d) with nRef=%d\n", p, p->trace, p->nRef);
  }
#endif
}

sqlite3_mutex_methods const *sqlite3DefaultMutex(void){
  static const sqlite3_mutex_methods sMutex = {
    rtthreadMutexInit,
    rtthreadMutexEnd,
    rtthreadMutexAlloc,
    rtthreadMutexFree,
    rtthreadMutexEnter,
    rtthreadMutexTry,
    rtthreadMutexLeave,
#ifdef SQLITE_DEBUG
    rtthreadMutexHeld,
    rtthreadMutexNotheld
#else
    0,
    0
#endif
  };

  return &sMutex;
}

#endif /* SQLITE_MUTEX_RTTHREAD */

