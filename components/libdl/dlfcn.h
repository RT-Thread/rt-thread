#ifndef __DLFCN_H_
#define __DLFCN_H_

#define RTLD_LAZY       0x00000
#define RTLD_NOW        0x00001

#define RTLD_LOCAL      0x00000
#define RTLD_GLOBAL     0x10000

#define RTLD_DEFAULT    ((void*)1)
#define RTLD_NEXT       ((void*)2)

void *rt_dlopen (const char *filename, int flag);
const char *rt_dlerror(void);
void *rt_dlsym(void *handle, const char *symbol);
int rt_dlclose (void *handle);
