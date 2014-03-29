#include <linux/module.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/memblock.h>

#include <asm/cacheflush.h>
#include <mach/hardware.h>

#include "vmm_linux.h"

#define IOMAP_NUM	3
#define BUFF_SZ		(4 * 1024)

struct vmm_iomap *_linux_iomap = NULL;

const char *uart_name = "uart";

/* some exported Linux Kernel patch */
extern void vmm_set_status(int status);
extern void vmm_context_init(void *context_addr);
extern unsigned long vmm_save_irq(void);
extern void vmm_restore_irq(unsigned long flags);

static struct vmm_domain domain =
{
    .kernel    = DOMAIN_KERNEL,
    .user      = DOMAIN_USER,
    .io        = DOMAIN_IO,
    .vmm       = DOMAIN_RTVMM,
    .vmm_share = DOMAIN_RTVMM_SHR,
};

static struct vmm_iomap iomap[RT_VMM_IOMAP_MAXNR] =
{
	{.name = "UART1",    .pa = 0x1000A000, .size = 4096},
	{.name = "TIMER",    .pa = 0x10012000, .size = 4096},
	{.name = "GIC_CPU",  .pa = 0x1E000000, .size = 4096},
	{.name = "GIC_DIST", .pa = 0x1E001000, .size = 4096},
	{.name = "SYS_CTRL", .pa = 0x1001A000, .size = 4096},
	{.pa = 0},
};

void vmm_iomap_init(void)
{
	int index;

	_linux_iomap = &iomap[0];

	BUILD_BUG_ON(ARRAY_SIZE(iomap) > RT_VMM_IOMAP_MAXNR);

	for (index = 0; index < ARRAY_SIZE(iomap); index++) {
		if (_linux_iomap[index].pa == 0)
			break;

		if (_linux_iomap[index].size != 0)
			_linux_iomap[index].va =
				ioremap_nocache(_linux_iomap[index].pa,
						_linux_iomap[index].size);

		printk("%s: 0x%08lx --> 0x%p, size %u\n",
			_linux_iomap[index].name,
			_linux_iomap[index].pa,
			_linux_iomap[index].va,
			_linux_iomap[index].size);
	}

	printk("vmm: init iomap done!\n");
}

#if 0
void trap_set_vector(unsigned long start, unsigned int length)
{
	int sctrl;

	/* C12-C0 is only active when SCTLR.V = 0 */
	asm volatile ("mrc p15, #0, %0, c1, c0, #0"
		      :"=r" (sctrl));
	sctrl &= ~(1 << 13);
	asm volatile ("mcr p15, #0, %0, c1, c0, #0"
		      :
		      :"r" (sctrl));

	asm volatile ("mcr p15, #0, %0, c12, c0, #0"
		      :
		      :"r" (start));
	rmb();
}
#else
extern void trap_set_vector(unsigned long start, unsigned int length);
#endif

static void vmm_open_domain(void)
{
	unsigned long dval;
	asm volatile ("mrc p15, 0, %0, c3, c0\n"
		      : "=r" (dval));
	dval |= (0x1 << (DOMAIN_RTVMM * 2)) |
		(0x1 << (DOMAIN_RTVMM_SHR * 2));
	asm volatile ("mcr p15, 0, %0, c3, c0\n"
		      : : "r" (dval));
}

static void vmm_close_domain(void)
{
	unsigned long dval;
	asm volatile ("mrc p15, 0, %0, c3, c0\n"
		      : "=r" (dval));
	/* we still need access tp DOMAIN_RTVMM_SHR because the IRQ stack is
	 * there. */
	dval &= ~(0x3 << (DOMAIN_RTVMM * 2));
	asm volatile ("mcr p15, 0, %0, c3, c0\n"
		      : : "r" (dval));
}

static DEFINE_SPINLOCK(init_lock);
void vmm_entry(void)
{
	vmm_entry_t entry;
	unsigned long flags;
	struct vmm_entry_param eparam = {
		.iomap = &iomap[0],
		.domain = &domain,
	};

	printk("Entry VMM:0x%08x with iomap 0x%p\n", VMM_BEGIN, _linux_iomap);

	spin_lock_irqsave(&init_lock,  flags);

	memcpy((void*)(LINUX_VECTOR_POS), (void*)0xFFFF0000,
	       LINUX_VECTOR_PGSZ);
	flush_icache_range(LINUX_VECTOR_POS,
			   LINUX_VECTOR_POS + LINUX_VECTOR_PGSZ);

	/*dump_vector(0xFFFF0000);*/
	/* set the interrupt vector to RTT */
	trap_set_vector(VMM_BEGIN, 16 * 4);
	/*dump_vector(VMM_END-LINUX_VECTOR_PGSZ);*/

	entry = (vmm_entry_t)VMM_BEGIN;

	vmm_context_init(&RT_VMM_SHARE->ctx);
	vmm_set_status(0x01);

	pr_info("Linux domain: kernel: %d, user: %d, io: %d\n",
		DOMAIN_KERNEL, DOMAIN_USER, DOMAIN_IO);

	/* switch to RTT and Good Luck */
	entry(&eparam);

	spin_unlock_irqrestore(&init_lock, flags);

	/* we now switched to virtual IRQ but the hardware IRQ is disabled
	 * before entering RT-Thread. So we have to enabled it by hand. */
	{
		asm volatile ("cpsie i":::"memory", "cc");
	}

	printk("come back to Linux.\n");

}

int vmm_load_fw(const char* filename)
{
	mm_segment_t oldfs = {0};
	unsigned long len;
	unsigned long file_sz;
	loff_t pos = 0;
	struct file *flp = NULL;
	char *buf_ptr = (char*)VMM_BEGIN;

	printk("loading RT-Thread:%s ....", filename);
	/* FIXME: we should not need this actually. But currently Linux would
	 * hang without this. Let's just proceed and I will go back to handle
	 * this in the future. */
	memset((void*)VMM_BEGIN, 0, VMM_SIZE);

	flp = filp_open(filename, O_RDONLY, S_IRWXU);
	if (IS_ERR(flp))
	{
		printk("vmm loader: open file failed. "
		       "Return 0x%p\n", flp);
		return -1;
	}

	/* get file size */
	file_sz = vfs_llseek(flp, 0, SEEK_END);
	vfs_llseek(flp, 0, SEEK_SET);

	oldfs = get_fs();
	set_fs(get_ds());
	while (file_sz > 0)
	{
		// len = vfs_read(flp, (void __user __force *)buff, BUFF_SZ, &pos);
		len = vfs_read(flp, (void __user __force*)buf_ptr, BUFF_SZ, &pos);
		file_sz -= len;
		buf_ptr += len;
	}
	set_fs(oldfs);

	filp_close(flp, NULL);

	printk("done!\n");

	/* flush RT-Thread memory */
	flush_cache_vmap(VMM_BEGIN, VMM_END);

	return 0;
}

static int __init vmm_init(void)
{
	printk("VMM started.\n");

	vmm_iomap_init();
	/* Open the domain permission so we could write firmware to it */
	vmm_open_domain();
	if (vmm_load_fw("/vmm/rtthread.bin") == 0)
		vmm_entry();

	return 0;
}

static void __exit vmm_exit(void)
{
	int i;
	unsigned long flags;

	spin_lock_irqsave(&init_lock,  flags);
	vmm_set_status(0x00);
	trap_set_vector(LINUX_VECTOR_POS, 16 * 4);
	spin_unlock_irqrestore(&init_lock, flags);

	for (i = 0; i < ARRAY_SIZE(iomap); i++)
	{
		if (iomap[i].pa == 0)
			break;

		printk("iounmap %s(0x%p)\n",
				iomap[i].name,
				iomap[i].va);
		iounmap(iomap[i].va);
	}

	vmm_close_domain();

	printk("vmm exit\n");
}

module_init(vmm_init);
module_exit(vmm_exit);

MODULE_AUTHOR("bernard.xiong <bernard.xiong@gmail.com>");
MODULE_DESCRIPTION("RT-VMM");
MODULE_LICENSE("GPL");
