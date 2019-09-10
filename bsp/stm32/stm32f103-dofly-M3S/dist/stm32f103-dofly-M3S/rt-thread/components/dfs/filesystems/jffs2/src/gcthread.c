/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright (C) 2001-2003 Red Hat, Inc.
 *
 * Created by David Woodhouse <dwmw2@redhat.com>
 *
 * For licensing information, see the file 'LICENCE' in this directory.
 *
 * $Id: gcthread.c,v 1.3 2005/01/22 16:01:12 lunn Exp $
 *
 */
#include <linux/kernel.h>
#include "nodelist.h"
//#include <cyg/kernel/kapi.h> prife

#if defined(CYGOPT_FS_JFFS2_GCTHREAD)

#define GC_THREAD_FLAG_TRIG 1
#define GC_THREAD_FLAG_STOP 2
#define GC_THREAD_FLAG_HAS_EXIT 4

#if 0
static cyg_thread_entry_t jffs2_garbage_collect_thread;

void jffs2_garbage_collect_trigger(struct jffs2_sb_info *c)
{
     struct super_block *sb=OFNI_BS_2SFFJ(c);

     /* Wake up the thread */
     D1(printk("jffs2_garbage_collect_trigger\n"));

     cyg_flag_setbits(&sb->s_gc_thread_flags,GC_THREAD_FLAG_TRIG);
}


void
jffs2_start_garbage_collect_thread(struct jffs2_sb_info *c)
{
     struct super_block *sb=OFNI_BS_2SFFJ(c);

     RT_ASSERT(c);
     RT_ASSERT(!sb->s_gc_thread_handle);

     cyg_flag_init(&sb->s_gc_thread_flags);
     cyg_mutex_init(&sb->s_lock);

     D1(printk("jffs2_start_garbage_collect_thread\n"));
     /* Start the thread. Doesn't matter if it fails -- it's only an
      * optimisation anyway */
     cyg_thread_create(CYGNUM_JFFS2_GC_THREAD_PRIORITY,
                       jffs2_garbage_collect_thread,
                       (unsigned long)c,"jffs2 gc thread",
                       (void*)sb->s_gc_thread_stack,
                       sizeof(sb->s_gc_thread_stack),
                       &sb->s_gc_thread_handle,
                       &sb->s_gc_thread);

     cyg_thread_resume(sb->s_gc_thread_handle);
}

void
jffs2_stop_garbage_collect_thread(struct jffs2_sb_info *c)
{
     struct super_block *sb=OFNI_BS_2SFFJ(c);

     RT_ASSERT(sb->s_gc_thread_handle);

     D1(printk("jffs2_stop_garbage_collect_thread\n"));
     /* Stop the thread and wait for it if necessary */

     cyg_flag_setbits(&sb->s_gc_thread_flags,GC_THREAD_FLAG_STOP);

     D1(printk("jffs2_stop_garbage_collect_thread wait\n"));

     cyg_flag_wait(&sb->s_gc_thread_flags,
                   GC_THREAD_FLAG_HAS_EXIT,
                   CYG_FLAG_WAITMODE_OR| CYG_FLAG_WAITMODE_CLR);

     // Kill and free the resources ...  this is safe due to the flag
     // from the thread.
     cyg_thread_kill(sb->s_gc_thread_handle);
     cyg_thread_delete(sb->s_gc_thread_handle);

     cyg_mutex_destroy(&sb->s_lock);
     cyg_flag_destroy(&sb->s_gc_thread_flags);
}


static void
jffs2_garbage_collect_thread(unsigned long data)
{
     struct jffs2_sb_info *c=(struct jffs2_sb_info *)data;
     struct super_block *sb=OFNI_BS_2SFFJ(c);
     cyg_flag_value_t flag;
     cyg_mtab_entry *mte;

     D1(printk("jffs2_garbage_collect_thread START\n"));

     while(1) {
          flag=cyg_flag_timed_wait(&sb->s_gc_thread_flags,
                                   GC_THREAD_FLAG_TRIG|GC_THREAD_FLAG_STOP,
                                   CYG_FLAG_WAITMODE_OR| CYG_FLAG_WAITMODE_CLR,
                                   cyg_current_time()+
                                   CYGNUM_JFFS2_GS_THREAD_TICKS);

          if (flag & GC_THREAD_FLAG_STOP)
               break;

          D1(printk("jffs2: GC THREAD GC BEGIN\n"));

          mte=cyg_fs_root_lookup((cyg_dir *) sb->s_root);
          CYG_ASSERT(mte, "Bad mount point");
          cyg_fs_lock(mte, mte->fs->syncmode);

          if (jffs2_garbage_collect_pass(c) == -ENOSPC) {
               printf("No space for garbage collection. "
                      "Aborting JFFS2 GC thread\n");
               break;
          }
          cyg_fs_unlock(mte, mte->fs->syncmode);
          D1(printk("jffs2: GC THREAD GC END\n"));
     }

     D1(printk("jffs2_garbage_collect_thread EXIT\n"));
     cyg_flag_setbits(&sb->s_gc_thread_flags,GC_THREAD_FLAG_HAS_EXIT);
}
#endif 

rt_uint32_t cyg_current_time(void)
{
	return 0;
}

static void
jffs2_garbage_collect_thread(unsigned long data);

void jffs2_garbage_collect_trigger(struct jffs2_sb_info *c)
{
     struct super_block *sb=OFNI_BS_2SFFJ(c);

     /* Wake up the thread */
     D1(printk("jffs2_garbage_collect_trigger\n"));

     rt_event_send(&sb->s_gc_thread_flags,GC_THREAD_FLAG_TRIG);
}

static struct rt_thread gc_thread;
void
jffs2_start_garbage_collect_thread(struct jffs2_sb_info *c)
{
     struct super_block *sb=OFNI_BS_2SFFJ(c);
     cyg_mtab_entry *mte;
     int result;
	
     RT_ASSERT(c);
     //RT_ASSERT(!sb->s_gc_thread_handle);
	 
     mte=(cyg_dir *) sb->s_root;
     RT_ASSERT(mte);
	 
     rt_event_init(&sb->s_gc_thread_flags, "gc_event", RT_IPC_FLAG_FIFO);	 
     rt_mutex_init(&sb->s_lock, "gc_mutex", RT_IPC_FLAG_FIFO);
//     rt_mutex_init(&mte->fs->syncmode, "fs_lock", RT_IPC_FLAG_FIFO);
	 
     D1(printk("jffs2_start_garbage_collect_thread\n"));
     /* Start the thread. Doesn't matter if it fails -- it's only an
      * optimisation anyway */
     result =  rt_thread_init(&sb->s_gc_thread, 
	                   "jffs2_gc_thread",
                       jffs2_garbage_collect_thread,
                       (void *)c,
                       (void*)sb->s_gc_thread_stack,
                       sizeof(sb->s_gc_thread_stack),
					   CYGNUM_JFFS2_GC_THREAD_PRIORITY,
					   CYGNUM_JFFS2_GC_THREAD_TICKS
					   );
	 if (result != RT_EOK) {
		 rt_thread_startup(&sb->s_gc_thread);
		 /* how to deal with the following filed? */
		 /* sb->s_gc_thread_handle; */
	 }
}

void
jffs2_stop_garbage_collect_thread(struct jffs2_sb_info *c)
{
     struct super_block *sb=OFNI_BS_2SFFJ(c);
     cyg_mtab_entry *mte;
	 rt_uint32_t  e;
	 
     //RT_ASSERT(sb->s_gc_thread_handle);

     D1(printk("jffs2_stop_garbage_collect_thread\n"));
     /* Stop the thread and wait for it if necessary */

     rt_event_send(&sb->s_gc_thread_flags,GC_THREAD_FLAG_STOP);

     D1(printk("jffs2_stop_garbage_collect_thread wait\n"));
	 
     rt_event_recv(&sb->s_gc_thread_flags,
                   GC_THREAD_FLAG_HAS_EXIT,
                   RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
				   RT_WAITING_FOREVER,  &e);

     // Kill and free the resources ...  this is safe due to the flag
     // from the thread.
     rt_thread_detach(&sb->s_gc_thread);
     rt_sem_detach(&sb->s_lock);
     rt_event_detach(&sb->s_gc_thread_flags);
}


static void
jffs2_garbage_collect_thread(unsigned long data)
{
     struct jffs2_sb_info *c=(struct jffs2_sb_info *)data;
     struct super_block *sb=OFNI_BS_2SFFJ(c);
     cyg_mtab_entry *mte;
     rt_uint32_t flag = 0;
	 
     D1(printk("jffs2_garbage_collect_thread START\n"));

     while(1) {
          rt_event_recv(&sb->s_gc_thread_flags,
                        GC_THREAD_FLAG_TRIG | GC_THREAD_FLAG_STOP,
                        RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
				        cyg_current_time() + CYGNUM_JFFS2_GS_THREAD_TICKS,  
						&flag);

          if (flag & GC_THREAD_FLAG_STOP)
               break;

          D1(printk("jffs2: GC THREAD GC BEGIN\n"));

          mte=(cyg_dir *) sb->s_root;
          RT_ASSERT(mte != NULL);
//          rt_mutex_take(&mte->fs->syncmode, RT_WAITING_FOREVER);

          if (jffs2_garbage_collect_pass(c) == -ENOSPC) {
               printf("No space for garbage collection. "
                      "Aborting JFFS2 GC thread\n");
               break;
          }
//          rt_mutex_release(&mte->fs->syncmode);
          D1(printk("jffs2: GC THREAD GC END\n"));
     }

     D1(printk("jffs2_garbage_collect_thread EXIT\n"));
     rt_event_send(&sb->s_gc_thread_flags,GC_THREAD_FLAG_HAS_EXIT);	 
}
#endif
