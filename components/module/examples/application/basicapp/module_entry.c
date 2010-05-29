#include <rtthread.h>
#include <interface_help.h>

extern int rt_application_entry(void);
rt_shell_t ishell = RT_NULL;

int rt_module_entry(const void* shell, void** object_info)
{
	/* init shell */
	ishell = (rt_shell_t)shell;

	rt_kprintf("module entry\n");
	struct rt_module_info *info = (struct rt_module_info*)
		rt_malloc(sizeof(struct rt_module_info));

	info->module_refs = 0;
	info->module_type = RT_Module_Class_APP;
	info->module_guid = 0xdead;
	info->exec_entry = (void *)rt_application_entry;
	info->module_interface = RT_NULL;

	*object_info = info;
}

