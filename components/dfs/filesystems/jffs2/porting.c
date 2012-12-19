#include <linux/kernel.h>
#include "nodelist.h"

#include "porting.h"

time_t jffs2_get_timestamp(void)
{
    return 0;
}

void jffs2_get_info_from_sb(void * data, struct jffs2_fs_info * info)
{
	struct jffs2_fs_info;
	struct super_block *jffs2_sb;
	struct jffs2_sb_info *c;

	jffs2_sb = (struct super_block *)(data);
	c = JFFS2_SB_INFO(jffs2_sb);
	
	info->sector_size = c->sector_size; 
	info->nr_blocks = c->nr_blocks;
	info->free_size = c->free_size + c->dirty_size; //fixme need test!	
}

int jffs2_porting_stat(cyg_mtab_entry * mte, cyg_dir dir, const char *name,
		      void * stat_buf)
{
	return jffs2_fste.stat(mte, mte->root, name, (struct stat *)stat_buf);	
}
