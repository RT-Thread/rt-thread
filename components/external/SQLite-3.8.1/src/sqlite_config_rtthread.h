#ifndef _SQLITE_CONFIG_RTTHREAD_H_
#define _SQLITE_CONFIG_RTTHREAD_H_
/*
* SQLite compile macro
*/
#ifndef SQLITE_MINIMUM_FILE_DESCRIPTOR
#define SQLITE_MINIMUM_FILE_DESCRIPTOR  0
#endif

#ifndef SQLITE_OMIT_LOAD_EXTENSION
#define SQLITE_OMIT_LOAD_EXTENSION 1
#endif

//#ifndef #define SQLITE_OMIT_WAL
#define SQLITE_OMIT_WAL
//#endif

#ifndef SQLITE_RTTHREAD_NO_WIDE
#define SQLITE_RTTHREAD_NO_WIDE 1
#endif

#ifndef SQLITE_ENABLE_LOCKING_STYLE
#define SQLITE_ENABLE_LOCKING_STYLE 0
#endif

#ifndef SQLITE_DISABLE_LOCKING_STYLE
#define SQLITE_DISABLE_LOCKING_STYLE 1
#endif

#ifndef SQLITE_TEMP_STORE
#define SQLITE_TEMP_STORE 1
#endif

#ifndef SQLITE_THREADSAFE
#define SQLITE_THREADSAFE 1
#endif

#ifndef HAVE_READLINE
#define HAVE_READLINE 0
#endif

#ifndef NDEBUG
#define NDEBUG
#endif

#ifndef _HAVE_SQLITE_CONFIG_H
#define _HAVE_SQLITE_CONFIG_H
#endif

#ifndef BUILD_sqlite
#define BUILD_sqlite
#endif

#ifndef SQLITE_OS_OTHER
#define SQLITE_OS_OTHER 1
#endif

#ifndef SQLITE_OS_RTTHREAD
#define SQLITE_OS_RTTHREAD 1
#endif

#endif
