/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright (C) 2001-2003 Free Software Foundation, Inc.
 *
 * Created by David Woodhouse <dwmw2@cambridge.redhat.com>
 *
 * For licensing information, see the file 'LICENCE' in this directory.
 *
 * $Id: dir-ecos.c,v 1.11 2005/02/08 19:36:27 lunn Exp $
 *
 */

#include <linux/kernel.h>
#include <linux/crc32.h>
#include "nodelist.h"

/***********************************************************************/

/* Takes length argument because it can be either NUL-terminated or '/'-terminated */
struct _inode *jffs2_lookup(struct _inode *dir_i, const unsigned char *d_name, int namelen)
{
	struct jffs2_inode_info *dir_f;
	struct jffs2_full_dirent *fd = NULL, *fd_list;
	uint32_t ino = 0;
	uint32_t hash = full_name_hash(d_name, namelen);
	struct _inode *inode = NULL;

	D1(printk("jffs2_lookup()\n"));

	dir_f = JFFS2_INODE_INFO(dir_i);

	down(&dir_f->sem);

	/* NB: The 2.2 backport will need to explicitly check for '.' and '..' here */
	for (fd_list = dir_f->dents; fd_list && fd_list->nhash <= hash; fd_list = fd_list->next) {
		if (fd_list->nhash == hash && 
		    (!fd || fd_list->version > fd->version) &&
		    strlen((char *)fd_list->name) == namelen &&
		    !strncmp((char *)fd_list->name, (char *)d_name, namelen)) {
			fd = fd_list;
		}
	}
	if (fd)
		ino = fd->ino;
	up(&dir_f->sem);
	if (ino) {
		inode = jffs2_iget(dir_i->i_sb, ino);
		if (IS_ERR(inode)) {
			printk("jffs2_iget() failed for ino #%u\n", ino);
			return inode;
		}
	}

	return inode;
}

/***********************************************************************/



int jffs2_create(struct _inode *dir_i, const unsigned char *d_name, int mode,
                 struct _inode **new_i)
{
	struct jffs2_raw_inode *ri;
	struct jffs2_inode_info *f, *dir_f;
	struct jffs2_sb_info *c;
	struct _inode *inode;
	int ret;

	ri = jffs2_alloc_raw_inode();
	if (!ri)
		return -ENOMEM;
	
	c = JFFS2_SB_INFO(dir_i->i_sb);

	D1(printk(KERN_DEBUG "jffs2_create()\n"));

	inode = jffs2_new_inode(dir_i, mode, ri);

	if (IS_ERR(inode)) {
		D1(printk(KERN_DEBUG "jffs2_new_inode() failed\n"));
		jffs2_free_raw_inode(ri);
		return PTR_ERR(inode);
	}

	f = JFFS2_INODE_INFO(inode);
	dir_f = JFFS2_INODE_INFO(dir_i);

	ret = jffs2_do_create(c, dir_f, f, ri, 
			      (const char *)d_name, 
                              strlen((char *)d_name));

	if (ret) {
		inode->i_nlink = 0;
		jffs2_iput(inode);
		jffs2_free_raw_inode(ri);
		return ret;
	}

	jffs2_free_raw_inode(ri);

	D1(printk(KERN_DEBUG "jffs2_create: Created ino #%lu with mode %o, nlink %d(%d)\n",
		  inode->i_ino, inode->i_mode, inode->i_nlink, f->inocache->nlink));
        *new_i = inode;
	return 0;
}

/***********************************************************************/


int jffs2_unlink(struct _inode *dir_i, struct _inode *d_inode, const unsigned char *d_name)
{
	struct jffs2_sb_info *c = JFFS2_SB_INFO(dir_i->i_sb);
	struct jffs2_inode_info *dir_f = JFFS2_INODE_INFO(dir_i);
	struct jffs2_inode_info *dead_f = JFFS2_INODE_INFO(d_inode);
	int ret;

	ret = jffs2_do_unlink(c, dir_f, (const char *)d_name, 
			       strlen((char *)d_name), dead_f);
	if (dead_f->inocache)
		d_inode->i_nlink = dead_f->inocache->nlink;
	return ret;
}
/***********************************************************************/


int jffs2_link (struct _inode *old_d_inode, struct _inode *dir_i, const unsigned char *d_name)
{
	struct jffs2_sb_info *c = JFFS2_SB_INFO(old_d_inode->i_sb);
	struct jffs2_inode_info *f = JFFS2_INODE_INFO(old_d_inode);
	struct jffs2_inode_info *dir_f = JFFS2_INODE_INFO(dir_i);
	int ret;

	/* XXX: This is ugly */
	uint8_t type = (old_d_inode->i_mode & S_IFMT) >> 12;
	if (!type) type = DT_REG;

	ret = jffs2_do_link(c, dir_f, f->inocache->ino, type, 
                            (const char * )d_name, 
                            strlen((char *)d_name));

	if (!ret) {
		down(&f->sem);
		old_d_inode->i_nlink = ++f->inocache->nlink;
		up(&f->sem);
	}
	return ret;
}

int jffs2_mkdir (struct _inode *dir_i, const unsigned char *d_name, int mode)
{
	struct jffs2_inode_info *f, *dir_f;
	struct jffs2_sb_info *c;
	struct _inode *inode;
	struct jffs2_raw_inode *ri;
	struct jffs2_raw_dirent *rd;
	struct jffs2_full_dnode *fn;
	struct jffs2_full_dirent *fd;
	int namelen;
	uint32_t alloclen, phys_ofs;
	int ret;

	mode |= S_IFDIR;

	ri = jffs2_alloc_raw_inode();
	if (!ri)
		return -ENOMEM;
	
	c = JFFS2_SB_INFO(dir_i->i_sb);

	/* Try to reserve enough space for both node and dirent. 
	 * Just the node will do for now, though 
	 */
	namelen = strlen((char *)d_name);
	ret = jffs2_reserve_space(c, sizeof(*ri), &phys_ofs, &alloclen, ALLOC_NORMAL);

	if (ret) {
		jffs2_free_raw_inode(ri);
		return ret;
	}

	inode = jffs2_new_inode(dir_i, mode, ri);

	if (IS_ERR(inode)) {
		jffs2_free_raw_inode(ri);
		jffs2_complete_reservation(c);
		return PTR_ERR(inode);
	}

	f = JFFS2_INODE_INFO(inode);

	ri->data_crc = cpu_to_je32(0);
	ri->node_crc = cpu_to_je32(crc32(0, ri, sizeof(*ri)-8));
	
	fn = jffs2_write_dnode(c, f, ri, NULL, 0, phys_ofs, ALLOC_NORMAL);

	jffs2_free_raw_inode(ri);

	if (IS_ERR(fn)) {
		/* Eeek. Wave bye bye */
		up(&f->sem);
		jffs2_complete_reservation(c);
		inode->i_nlink = 0;
		jffs2_iput(inode);
		return PTR_ERR(fn);
	}
	/* No data here. Only a metadata node, which will be 
	   obsoleted by the first data write
	*/
	f->metadata = fn;
	up(&f->sem);

	jffs2_complete_reservation(c);
	ret = jffs2_reserve_space(c, sizeof(*rd)+namelen, &phys_ofs, &alloclen, ALLOC_NORMAL);
	if (ret) {
		/* Eep. */
		inode->i_nlink = 0;
		jffs2_iput(inode);
		return ret;
	}
	
	rd = jffs2_alloc_raw_dirent();
	if (!rd) {
		/* Argh. Now we treat it like a normal delete */
		jffs2_complete_reservation(c);
		inode->i_nlink = 0;
		jffs2_iput(inode);
		return -ENOMEM;
	}

	dir_f = JFFS2_INODE_INFO(dir_i);
	down(&dir_f->sem);

	rd->magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	rd->nodetype = cpu_to_je16(JFFS2_NODETYPE_DIRENT);
	rd->totlen = cpu_to_je32(sizeof(*rd) + namelen);
	rd->hdr_crc = cpu_to_je32(crc32(0, rd, sizeof(struct jffs2_unknown_node)-4));

	rd->pino = cpu_to_je32(dir_i->i_ino);
	rd->version = cpu_to_je32(++dir_f->highest_version);
	rd->ino = cpu_to_je32(inode->i_ino);
	rd->mctime = cpu_to_je32(jffs2_get_timestamp());
	rd->nsize = namelen;
	rd->type = DT_DIR;
	rd->node_crc = cpu_to_je32(crc32(0, rd, sizeof(*rd)-8));
	rd->name_crc = cpu_to_je32(crc32(0, d_name, namelen));

	fd = jffs2_write_dirent(c, dir_f, rd, d_name, namelen, phys_ofs, ALLOC_NORMAL);
	
	jffs2_complete_reservation(c);
	jffs2_free_raw_dirent(rd);
	
	if (IS_ERR(fd)) {
		/* dirent failed to write. Delete the inode normally 
		   as if it were the final unlink() */
		up(&dir_f->sem);
		inode->i_nlink = 0;
		jffs2_iput(inode);
		return PTR_ERR(fd);
	}

	/* Link the fd into the inode's list, obsoleting an old
	   one if necessary. */
	jffs2_add_fd_to_list(c, fd, &dir_f->dents);
	up(&dir_f->sem);

	jffs2_iput(inode);
	return 0;
}

int jffs2_rmdir (struct _inode *dir_i, struct _inode *d_inode, const unsigned char *d_name)
{
	struct jffs2_inode_info *f = JFFS2_INODE_INFO(d_inode);
	struct jffs2_full_dirent *fd;

	for (fd = f->dents ; fd; fd = fd->next) {
		if (fd->ino)
			return EPERM; //-ENOTEMPTY;
	}
	return jffs2_unlink(dir_i, d_inode, d_name);
}

int jffs2_rename (struct _inode *old_dir_i, struct _inode *d_inode, const unsigned char *old_d_name,
		  struct _inode *new_dir_i, const unsigned char *new_d_name)
{
	int ret;
	struct jffs2_sb_info *c = JFFS2_SB_INFO(old_dir_i->i_sb);
	struct jffs2_inode_info *victim_f = NULL;
	uint8_t type;

#if 0 /* FIXME -- this really doesn't belong in individual file systems. 
	 The fileio code ought to do this for us, or at least part of it */
	if (new_dentry->d_inode) {
		if (S_ISDIR(d_inode->i_mode) && 
		    !S_ISDIR(new_dentry->d_inode->i_mode)) {
			/* Cannot rename directory over non-directory */
			return -EINVAL;
		}

		victim_f = JFFS2_INODE_INFO(new_dentry->d_inode);

		if (S_ISDIR(new_dentry->d_inode->i_mode)) {
			struct jffs2_full_dirent *fd;

			if (!S_ISDIR(d_inode->i_mode)) {
				/* Cannot rename non-directory over directory */
				return -EINVAL;
			}
			down(&victim_f->sem);
			for (fd = victim_f->dents; fd; fd = fd->next) {
				if (fd->ino) {
					up(&victim_f->sem);
					return -ENOTEMPTY;
				}
			}
			up(&victim_f->sem);
		}
	}
#endif

	/* XXX: We probably ought to alloc enough space for
	   both nodes at the same time. Writing the new link, 
	   then getting -ENOSPC, is quite bad :)
	*/

	/* Make a hard link */
	
	/* XXX: This is ugly */
	type = (d_inode->i_mode & S_IFMT) >> 12;
	if (!type) type = DT_REG;

	ret = jffs2_do_link(c, JFFS2_INODE_INFO(new_dir_i), 
			    d_inode->i_ino, type,
			    (const char *)new_d_name, 
                            strlen((char *)new_d_name));

	if (ret)
		return ret;

	if (victim_f) {
		/* There was a victim. Kill it off nicely */
		/* Don't oops if the victim was a dirent pointing to an
		   inode which didn't exist. */
		if (victim_f->inocache) {
			down(&victim_f->sem);
			victim_f->inocache->nlink--;
			up(&victim_f->sem);
		}
	}

	/* Unlink the original */
	ret = jffs2_do_unlink(c, JFFS2_INODE_INFO(old_dir_i), 
                              (const char *)old_d_name, 
                              strlen((char *)old_d_name), NULL);

	if (ret) {
		/* Oh shit. We really ought to make a single node which can do both atomically */
		struct jffs2_inode_info *f = JFFS2_INODE_INFO(d_inode);
		down(&f->sem);
		if (f->inocache)
			d_inode->i_nlink = f->inocache->nlink++;
		up(&f->sem);

		printk(KERN_NOTICE "jffs2_rename(): Link succeeded, unlink failed (err %d). You now have a hard link\n", ret);
	}
	return ret;
}

