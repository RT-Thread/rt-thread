#include <pthread.h>
#include <finsh.h>

#define _die_(x)			do { rt_kprintf(x); RT_ASSERT(0); } while (0)
#define pr(x)				do { rt_kprintf(x); } while (0)
#define sleep(n)			rt_thread_sleep((n * RT_TICK_PER_SECOND)/1000)
#define alarm(n)			

/* (0) once test */
void test0_ok() { pr("(once called) "); }
void test0_failed() { _die_("failed...\n"); }
void pth_t0() {
  pthread_once_t v_once=PTHREAD_ONCE_INIT;
  pr("\nTEST 0: once test:\n\n");
  pr("testing once function... ");
  pthread_once(&v_once,test0_ok);
  pthread_once(&v_once,test0_failed);
  pr("OK.\n");
}
FINSH_FUNCTION_EXPORT(pth_t0, pthread testcase0);

/* (1) mutex tests */
void test_rec_mutex() {
  pthread_mutex_t tm;
  pthread_mutexattr_t ta;
  pthread_mutexattr_settype(&ta, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init(&tm, &ta);
  pr("testing recursive mutex... ");
  alarm(5);
  if (pthread_mutex_lock(&tm) != 0) _die_("failed... mutex_lock on unused rec-mutex (c=0)...\n");
  if (tm.lock.owner!=pthread_self()) _die_("failed.. wrong owner....\n");
  if (tm.lock.hold!=1) _die_("failed... wrong counting (c!=1)....\n");
  if (pthread_mutex_lock(&tm) != 0) _die_("failed... mutex_lock on taken rec-mutex (c=1)...\n");
  if (tm.lock.hold!=2) _die_("failed... wrong counting (c!=2)....\n");
  if (pthread_mutex_lock(&tm) != 0) _die_("failed... mutex_lock on taken rec-mutex (c=2)...\n");
  if (tm.lock.hold!=3) _die_("failed... wrong counting (c!=3)....\n");
  if (pthread_mutex_unlock(&tm) != 0) _die_("failed... mutex_unlock on taken rec-mutex (c=3)...\n");
  if (tm.lock.hold!=2) _die_("failed... wrong counting (c!=2)....\n");
  if (tm.lock.owner==0) _die_("failed... mutex has no owner?!?!\n");
  if (pthread_mutex_unlock(&tm) != 0) _die_("failed... mutex_unlock on taken rec-mutex (c=2)...\n");
  if (tm.lock.hold!=1) _die_("failed... wrong counting (c!=1)....\n");
  if (tm.lock.owner==0) _die_("failed... mutex has no owner?!?!\n");
  if (pthread_mutex_unlock(&tm) != 0) _die_("failed... mutex_unlock on taken rec-mutex (c=1)...\n");
  if (tm.lock.hold!=0) _die_("failed... wrong counting (c!=0)....\n");
  if (tm.lock.owner!=0) _die_("failed... mutex still owned ?!?!\n");
  if (pthread_mutex_unlock(&tm) != 0) _die_("failed... mutex_unlock on free rec-mutex (c=0)...\n");
  alarm(0);
  pr("OK.\n");
}

void test_err_mutex() {
  pthread_mutex_t tm;
  pthread_mutexattr_t ta;
 
  pthread_mutexattr_settype(&ta, PTHREAD_MUTEX_ERRORCHECK);
  pthread_mutex_init(&tm, &ta);
  pr("testing errorcheck mutex... ");
  alarm(5);
  if (pthread_mutex_lock(&tm) != 0) _die_("failed... mutex_lock on unused errchk-mutex...\n");
  if (tm.lock.owner!=pthread_self()) _die_("failed.. wrong owner....\n");
  if (pthread_mutex_lock(&tm) != EDEADLK) _die_("failed... mutex_lock on taken errchk-mutex...\n");
  if (pthread_mutex_unlock(&tm) != 0) _die_("failed... mutex_unlock on taken errchk-mutex...\n");
  if (tm.lock.owner!=0) _die_("failed... mutex still owned ?!?!\n");
  if (pthread_mutex_unlock(&tm) != EPERM) _die_("failed... mutex_unlock on free errchk-mutex...\n");
  alarm(0);
  pr("OK.\n");
}

void pth_t1() {
  pr("\nTEST 1: mutex test:\n\n");
  test_rec_mutex();
  test_err_mutex();
}
FINSH_FUNCTION_EXPORT(pth_t1, pthread testcase0);

void* thread(void*arg)
{
  if (0) { arg=0; }
  pr("(thread created) ");
  sleep(1);
  pr("(thread exit) ");
  return 0;
}

void test_thread() {
  pthread_t t;
  pr("testing basic thread creation and join... ");
  if ((pthread_create(&t,0,thread,0))!=0) _die_("failed...\n");
  if (pthread_join(t,0) != 0) _die_("failed... joining thread\n");
  pr("OK.\n");
}

void test_thread_join_detached() {
  pthread_t t;
  pthread_attr_t attr;
  pr("testing for failing join of a detached thread... ");
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
  if ((pthread_create(&t,&attr,thread,0))!=0) _die_("failed...\n");
  if (pthread_join(t,0) == 0) _die_("failed... I had joined a detached thread !\n");
  sleep(2);
  pr("OK.\n");
}

static char alt_stack[4096];
void test_thread_alt_stack() {
  pthread_t t;
  pthread_attr_t attr;
  pr("testing alternate thread stack... ");
  pthread_attr_init(&attr);
  pthread_attr_setstacksize(&attr,sizeof(alt_stack));
  if ((pthread_create(&t,&attr,thread,0))!=0) _die_("failed... creating thread\n");
  if (pthread_join(t,0) != 0) _die_("failed... joining thread\n");
  pthread_attr_setstackaddr(&attr,alt_stack);
  if ((pthread_create(&t,&attr,thread,0))!=0) _die_("failed... creating thread\n");
  if (pthread_join(t,0) != 0) _die_("failed... joining thread\n");
  pr("OK.\n");
}

void pth_t2()
{
  pr("\nTEST 2: thread creation & attributes:\n\n");
  test_thread();
  test_thread_join_detached();
  test_thread_alt_stack();
}
FINSH_FUNCTION_EXPORT(pth_t2, pthread testcase1);
