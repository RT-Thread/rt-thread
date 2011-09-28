#include <rtthread.h>
#include <dlfcn.h>

typedef void (*func)(void);

int main(void)
{
	func f1, f2, f3, f4, f5;
		
	void* handle = dlopen("/mo/ext.so", RTLD_NOW);
	if(handle != RT_NULL)
	{
		f1= (func)dlsym(handle, "function1");
		f2= (func)dlsym(handle, "function2");
		f3= (func)dlsym(handle, "function3");
		f4= (func)dlsym(handle, "function4");
		f5= (func)dlsym(handle, "function5");

		if(f1 != RT_NULL) f1();
		else rt_kprintf("dlsym function1 failed.\n");
		if(f2 != RT_NULL) f2();
		else rt_kprintf("dlsym function2 failed.\n");
		if(f3 != RT_NULL) f3();
		else rt_kprintf("dlsym function3 failed.\n");		
		if(f4 != RT_NULL) f4();
		else rt_kprintf("dlsym function4 failed.\n");
		if(f5 != RT_NULL) f5();
		else rt_kprintf("dlsym function5 failed.\n");
	}

	if(handle != RT_NULL) dlclose(handle);

	return 0;
}

