/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright (C) 2001-2003 Free Software Foundation, Inc.
 *
 * Created by Dominic Ostrowski <dominic.ostrowski@3glab.com>
 * Contributors: David Woodhouse, Nick Garnett, Richard Panton.
 *
 * For licensing information, see the file 'LICENCE' in this directory.
 *
 * $Id: fs-ecos.c,v 1.44 2005/07/24 15:29:57 dedekind Exp $
 *
 */

#include <stdio.h>	//prife for SEEK_SET SEEK_CUR SEEK_END
#include <linux/kernel.h>
#include "nodelist.h"
#include <linux/pagemap.h>
#include <linux/crc32.h>
#include "compr.h"
#include <string.h>

#include <rtdevice.h>

//--------------------------------------------
cyg_mtab_entry *cyg_cdir_mtab_entry = NULL;
cyg_dir cyg_cdir_dir = CYG_DIR_NULL;
//==========================================================================
// Default functions

__externC int cyg_fileio_enosys() { return ENOSYS; }
__externC int cyg_fileio_erofs() { return EROFS; }
__externC int cyg_fileio_enoerr() { return ENOERR; }
__externC int cyg_fileio_enotdir() { return ENOTDIR; }

__externC cyg_bool cyg_fileio_seltrue (struct CYG_FILE_TAG *fp, int which, CYG_ADDRWORD info)
{ return 1; }

//--------------------------------------------
//==========================================================================
// Forward definitions

// Filesystem operations
int jffs2_mount(cyg_fstab_entry * fste, cyg_mtab_entry * mte);
static int jffs2_umount(cyg_mtab_entry * mte);
int jffs2_open(cyg_mtab_entry * mte, cyg_dir dir, const char *name,
		      int mode, cyg_file * fte);
#ifdef CYGOPT_FS_JFFS2_WRITE
static int jffs2_ops_unlink(cyg_mtab_entry * mte, cyg_dir dir,
			    const char *name);
static int jffs2_ops_mkdir(cyg_mtab_entry * mte, cyg_dir dir, const char *name);
static int jffs2_ops_rmdir(cyg_mtab_entry * mte, cyg_dir dir, const char *name);
static int jffs2_ops_rename(cyg_mtab_entry * mte, cyg_dir dir1,
			    const char *name1, cyg_dir dir2, const char *name2);
static int jffs2_ops_link(cyg_mtab_entry * mte, cyg_dir dir1, const char *name1,
			  cyg_dir dir2, const char *name2, int type);
#endif
static int jffs2_opendir(cyg_mtab_entry * mte, cyg_dir dir, const char *name,
			 cyg_file * fte);
static int jffs2_chdir(cyg_mtab_entry * mte, cyg_dir dir, const char *name,
		       cyg_dir * dir_out);
static int jffs2_stat(cyg_mtab_entry * mte, cyg_dir dir, const char *name,
		      struct stat *buf);
static int jffs2_getinfo(cyg_mtab_entry * mte, cyg_dir dir, const char *name,
			 int key, void *buf, int len);
static int jffs2_setinfo(cyg_mtab_entry * mte, cyg_dir dir, const char *name,
			 int key, void *buf, int len);

// File operations
int jffs2_fo_read(struct CYG_FILE_TAG *fp, struct CYG_UIO_TAG *uio);
#ifdef CYGOPT_FS_JFFS2_WRITE
static int jffs2_fo_write(struct CYG_FILE_TAG *fp, struct CYG_UIO_TAG *uio);
#endif
static int jffs2_fo_lseek(struct CYG_FILE_TAG *fp, off_t * pos, int whence);
static int jffs2_fo_ioctl(struct CYG_FILE_TAG *fp, CYG_ADDRWORD com,
			  CYG_ADDRWORD data);
static int jffs2_fo_fsync(struct CYG_FILE_TAG *fp, int mode);
static int jffs2_fo_close(struct CYG_FILE_TAG *fp);
static int jffs2_fo_fstat(struct CYG_FILE_TAG *fp, struct stat *buf);
static int jffs2_fo_getinfo(struct CYG_FILE_TAG *fp, int key, void *buf,
			    int len);
static int jffs2_fo_setinfo(struct CYG_FILE_TAG *fp, int key, void *buf,
			    int len);

// Directory operations
static int jffs2_fo_dirread(struct CYG_FILE_TAG *fp, struct CYG_UIO_TAG *uio);
static int jffs2_fo_dirlseek(struct CYG_FILE_TAG *fp, off_t * pos, int whence);


static int jffs2_read_inode (struct _inode *inode);
static void jffs2_clear_inode (struct _inode *inode);
static int jffs2_truncate_file (struct _inode *inode);

//==========================================================================
// Filesystem table entries

// -------------------------------------------------------------------------
// Fstab entry.
// This defines the entry in the filesystem table.
// For simplicity we use _FILESYSTEM synchronization for all accesses since
// we should never block in any filesystem operations.

#ifdef CYGOPT_FS_JFFS2_WRITE
FSTAB_ENTRY(jffs2_fste, "jffs2", 0,
	    CYG_SYNCMODE_FILE_FILESYSTEM | CYG_SYNCMODE_IO_FILESYSTEM,
	    jffs2_mount,
	    jffs2_umount,
	    jffs2_open,
	    jffs2_ops_unlink,
	    jffs2_ops_mkdir,
	    jffs2_ops_rmdir,
	    jffs2_ops_rename,
	    jffs2_ops_link,
	    jffs2_opendir,
	    jffs2_chdir, jffs2_stat, jffs2_getinfo, jffs2_setinfo);
#else
FSTAB_ENTRY(jffs2_fste, "jffs2", 0,
	    CYG_SYNCMODE_FILE_FILESYSTEM | CYG_SYNCMODE_IO_FILESYSTEM,
	    jffs2_mount,
	    jffs2_umount,
	    jffs2_open,
	    (cyg_fsop_unlink *)cyg_fileio_erofs,
	    (cyg_fsop_mkdir *)cyg_fileio_erofs,
	    (cyg_fsop_rmdir *)cyg_fileio_erofs,
	    (cyg_fsop_rename *)cyg_fileio_erofs,
	    (cyg_fsop_link *)cyg_fileio_erofs,
	    jffs2_opendir,
	    jffs2_chdir, jffs2_stat, jffs2_getinfo, jffs2_setinfo);
#endif

// -------------------------------------------------------------------------
// File operations.
// This set of file operations are used for normal open files.

cyg_fileops jffs2_fileops = {
	jffs2_fo_read,
#ifdef CYGOPT_FS_JFFS2_WRITE
	jffs2_fo_write,
#else
	(cyg_fileop_write *) cyg_fileio_erofs,
#endif
	jffs2_fo_lseek,
	jffs2_fo_ioctl,
	cyg_fileio_seltrue,
	jffs2_fo_fsync,
	jffs2_fo_close,
	jffs2_fo_fstat,
	jffs2_fo_getinfo,
	jffs2_fo_setinfo
};

// -------------------------------------------------------------------------
// Directory file operations.
// This set of operations are used for open directories. Most entries
// point to error-returning stub functions. Only the read, lseek and
// close entries are functional.

cyg_fileops jffs2_dirops = {
	jffs2_fo_dirread,
	(cyg_fileop_write *) cyg_fileio_enosys,
	jffs2_fo_dirlseek,
	(cyg_fileop_ioctl *) cyg_fileio_enosys,
	cyg_fileio_seltrue,
	(cyg_fileop_fsync *) cyg_fileio_enosys,
	jffs2_fo_close,
	(cyg_fileop_fstat *) cyg_fileio_enosys,
	(cyg_fileop_getinfo *) cyg_fileio_enosys,
	(cyg_fileop_setinfo *) cyg_fileio_enosys
};

//==========================================================================
// STATIC VARIABLES !!!

static unsigned char gc_buffer[PAGE_CACHE_SIZE];	//avoids malloc when user may be under memory pressure
static unsigned char n_fs_mounted = 0;  // a counter to track the number of jffs2 instances mounted

//==========================================================================
// Directory operations

struct jffs2_dirsearch {
	struct _inode *dir;	    // directory to search
	const unsigned char *path;  // path to follow
	struct _inode *node;	    // Node found
	const unsigned char *name;  // last name fragment used
	int namelen;		    // name fragment length
	cyg_bool last;		    // last name in path?
};

typedef struct jffs2_dirsearch jffs2_dirsearch;

//==========================================================================
// Ref count and nlink management


// FIXME: This seems like real cruft. Wouldn't it be better just to do the
// right thing?
static void icache_evict(struct _inode *root_i, struct _inode *i)
{
	struct _inode *this = root_i, *next;

 restart:
	D2(printf("icache_evict\n"));
	// If this is an absolute search path from the root,
	// remove all cached inodes with i_count of zero (these are only
	// held where needed for dotdot filepaths)
	while (this) {
		next = this->i_cache_next;
		if (this != i && this->i_count == 0) {
			struct _inode *parent = this->i_parent;
			if (this->i_cache_next)
				this->i_cache_next->i_cache_prev = this->i_cache_prev;
			if (this->i_cache_prev)
				this->i_cache_prev->i_cache_next = this->i_cache_next;
			jffs2_clear_inode(this);
			memset(this, 0x5a, sizeof(*this));
			rt_free(this);
			if (parent && parent != this) {
				parent->i_count--;
				this = root_i;
				goto restart;
			}
		}
		this = next;
	}
}

//==========================================================================
// Directory search

// -------------------------------------------------------------------------
// init_dirsearch()
// Initialize a dirsearch object to start a search

static void init_dirsearch(jffs2_dirsearch * ds,
			   struct _inode *dir, const unsigned char *name)
{
	D2(printf("init_dirsearch name = %s\n", name));
	D2(printf("init_dirsearch dir = %x\n", dir));

	dir->i_count++;
	ds->dir = dir;
	ds->path = name;
	ds->node = dir;
	ds->name = name;
	ds->namelen = 0;
	ds->last = false;
}

// -------------------------------------------------------------------------
// find_entry()
// Search a single directory for the next name in a path and update the
// dirsearch object appropriately.

static int find_entry(jffs2_dirsearch * ds)
{
	struct _inode *dir = ds->dir;
	const unsigned char *name = ds->path;
	const unsigned char *n = name;
	char namelen = 0;
	struct _inode *d;

	D2(printf("find_entry\n"));

	// check that we really have a directory
	if (!S_ISDIR(dir->i_mode))
		return ENOTDIR;

	// Isolate the next element of the path name.
	while (*n != '\0' && *n != '/')
		n++, namelen++;

	// Check if this is the last path element.
	while( *n == '/') n++;
	if (*n == '\0')
		ds->last = true;

	// update name in dirsearch object
	ds->name = name;
	ds->namelen = namelen;

	if (name[0] == '.')
		switch (namelen) {
		default:
			break;
		case 2:
			// Dot followed by not Dot, treat as any other name
			if (name[1] != '.')
				break;
			// Dot Dot
			// Move back up the search path
			D2(printf("find_entry found ..\n"));
			ds->dir = ds->node;
			ds->node = ds->dir->i_parent;
			ds->node->i_count++;
			return ENOERR;
		case 1:
			// Dot is consumed
			D2(printf("find_entry found .\n"));
			ds->node = ds->dir;
			ds->dir->i_count++;
			return ENOERR;
		}

	// Here we have the name and its length set up.
	// Search the directory for a matching entry

	D2(printf("find_entry for name = %s\n", ds->path));
	d = jffs2_lookup(dir, name, namelen);
	D2(printf("find_entry got dir = %x\n", d));

	if (d == NULL)
		return ENOENT;
	if (IS_ERR(d))
		return -PTR_ERR(d);

	// If it's a new directory inode, increase refcount on its parent
	if (S_ISDIR(d->i_mode) && !d->i_parent) {
		d->i_parent = dir;
		dir->i_count++;
	}

	// pass back the node we have found
	ds->node = d;
	return ENOERR;

}

// -------------------------------------------------------------------------
// jffs2_find()
// Main interface to directory search code. This is used in all file
// level operations to locate the object named by the pathname.

// Returns with use count incremented on both the sought object and
// the directory it was found in
static int jffs2_find(jffs2_dirsearch * d)
{
	int err;

	D2(printf("jffs2_find for path =%s\n", d->path));

	// Short circuit empty paths
	if (*(d->path) == '\0') {
		d->node->i_count++;
		return ENOERR;
	}

	// iterate down directory tree until we find the object
	// we want.
	for (;;) {
		err = find_entry(d);

		if (err != ENOERR)
			return err;

		if (d->last)
			return ENOERR;

		/* We're done with it, although it we found a subdir that
		   will have caused the refcount to have been increased */
		jffs2_iput(d->dir);

		// Update dirsearch object to search next directory.
		d->dir = d->node;
		d->path += d->namelen;
		while (*(d->path) == '/')
			d->path++;	// skip dirname separators
	}
}

//==========================================================================
// Pathconf support
// This function provides support for pathconf() and fpathconf().

static int jffs2_pathconf(struct _inode *node, struct cyg_pathconf_info *info)
{
	int err = ENOERR;
	D2(printf("jffs2_pathconf\n"));

	switch (info->name) {
	case _PC_LINK_MAX:
		info->value = LINK_MAX;
		break;

	case _PC_MAX_CANON:
		info->value = -1;	// not supported
		err = EINVAL;
		break;

	case _PC_MAX_INPUT:
		info->value = -1;	// not supported
		err = EINVAL;
		break;

	case _PC_NAME_MAX:
		info->value = JFFS2_NAME_MAX;
		break;

	case _PC_PATH_MAX:
		info->value = JFFS2_PATH_MAX;
		break;

	case _PC_PIPE_BUF:
		info->value = -1;	// not supported
		err = EINVAL;
		break;

	case _PC_ASYNC_IO:
		info->value = -1;	// not supported
		err = EINVAL;
		break;

	case _PC_CHOWN_RESTRICTED:
		info->value = -1;	// not supported
		err = EINVAL;
		break;

	case _PC_NO_TRUNC:
		info->value = 0;
		break;

	case _PC_PRIO_IO:
		info->value = 0;
		break;

	case _PC_SYNC_IO:
		info->value = 0;
		break;

	case _PC_VDISABLE:
		info->value = -1;	// not supported
		err = EINVAL;
		break;

	default:
		err = EINVAL;
		break;
	}

	return err;
}

//==========================================================================
// Filesystem operations
// -------------------------------------------------------------------------
// jffs2_mount()
// Process a mount request. This mainly creates a root for the
// filesystem.
static int jffs2_read_super(struct super_block *sb)
{
	Cyg_ErrNo err;
	struct jffs2_sb_info *c;
	struct rt_mtd_nor_device *device;
	
	c = JFFS2_SB_INFO(sb);
	device = RT_MTD_NOR_DEVICE(sb->s_dev);

	/* initialize mutex lock */
	init_MUTEX(&c->alloc_sem);
	init_MUTEX(&c->erase_free_sem);

	/* sector size is the erase block size */
	c->sector_size = device->block_size;
	c->flash_size  = (device->block_end - device->block_start) * device->block_size;
	c->cleanmarker_size = sizeof(struct jffs2_unknown_node);

	err = jffs2_do_mount_fs(c);
	if (err) return -err;

	D1(printk(KERN_DEBUG "jffs2_read_super(): Getting root inode\n"));
	sb->s_root = jffs2_iget(sb, 1);
	if (IS_ERR(sb->s_root)) {
		D1(printk(KERN_WARNING "get root inode failed\n"));
		err = PTR_ERR(sb->s_root);
		sb->s_root = NULL;
		goto out_nodes;
	}
	return 0;

out_nodes:
	jffs2_free_ino_caches(c);
	jffs2_free_raw_node_refs(c);
	rt_free(c->blocks);

	return err;
}

int jffs2_mount(cyg_fstab_entry * fste, cyg_mtab_entry * mte)
{
//	extern cyg_mtab_entry cyg_mtab[], cyg_mtab_end;
	struct super_block *jffs2_sb = NULL;
	struct jffs2_sb_info *c;
//	cyg_mtab_entry *m;
	cyg_io_handle_t t;
	Cyg_ErrNo err;

	D2(printf("jffs2_mount\n"));

//prife
//	err = cyg_io_lookup(mte->devname, &t);
//	if (err != ENOERR)
//		return -err;

//	// Iterate through the mount table to see if we're mounted
//	// FIXME: this should be done better - perhaps if the superblock
//	// can be stored as an inode in the icache.
//	for (m = &cyg_mtab[0]; m != &cyg_mtab_end; m++) {
//		// stop if there are more than the configured maximum
//		if (m - &cyg_mtab[0] >= CYGNUM_FILEIO_MTAB_MAX) {
//			m = &cyg_mtab_end;
//			break;
//		}
//		if (m->valid && strcmp(m->fsname, "jffs2") == 0 &&
//		    strcmp(m->devname, mte->devname) == 0) {
//			jffs2_sb = (struct super_block *) m->data;
//		}
//	}
    jffs2_sb = NULL;
	t = (cyg_io_handle_t)mte->data; //get from dfs_jffs2;
	if (jffs2_sb == NULL) {
		jffs2_sb = rt_malloc(sizeof (struct super_block));

		if (jffs2_sb == NULL)
			return ENOMEM;

		c = JFFS2_SB_INFO(jffs2_sb);
		memset(jffs2_sb, 0, sizeof (struct super_block));
		jffs2_sb->s_dev = t;

		c->inocache_list = rt_malloc(sizeof(struct jffs2_inode_cache *) * INOCACHE_HASHSIZE);
		if (!c->inocache_list) {
			rt_free(jffs2_sb);
			return ENOMEM;
		}
		memset(c->inocache_list, 0, sizeof(struct jffs2_inode_cache *) * INOCACHE_HASHSIZE);
                if (n_fs_mounted++ == 0) {
                        jffs2_create_slab_caches(); // No error check, cannot fail
			jffs2_compressors_init();
		}

		err = jffs2_read_super(jffs2_sb);

		if (err) {
                        if (--n_fs_mounted == 0) {
                                jffs2_destroy_slab_caches();
				jffs2_compressors_exit();
			}

			rt_free(jffs2_sb);
			rt_free(c->inocache_list);
			return err;
		}

		jffs2_sb->s_root->i_parent = jffs2_sb->s_root;	// points to itself, no dotdot paths above mountpoint
		jffs2_sb->s_root->i_cache_prev = NULL;	// root inode, so always null
		jffs2_sb->s_root->i_cache_next = NULL;
		jffs2_sb->s_root->i_count = 1;	// Ensures the root inode is always in ram until umount

		D2(printf("jffs2_mount erasing pending blocks\n"));
#ifdef CYGOPT_FS_JFFS2_WRITE
		if (!jffs2_is_readonly(c))
		    jffs2_erase_pending_blocks(c,0);
#endif
#ifdef CYGOPT_FS_JFFS2_GCTHREAD
		jffs2_start_garbage_collect_thread(c);
#endif
	}
	mte->data = (CYG_ADDRWORD) jffs2_sb;

	jffs2_sb->s_mount_count++;
	mte->root = (cyg_dir) jffs2_sb->s_root;
	D2(printf("jffs2_mounted superblock at %x\n", mte->root));

	return ENOERR;
}

extern cyg_dir cyg_cdir_dir;
extern cyg_mtab_entry *cyg_cdir_mtab_entry;

// -------------------------------------------------------------------------
// jffs2_umount()
// Unmount the filesystem.

static int jffs2_umount(cyg_mtab_entry * mte)
{
	struct _inode *root = (struct _inode *) mte->root;
	struct super_block *jffs2_sb = root->i_sb;
	struct jffs2_sb_info *c = JFFS2_SB_INFO(jffs2_sb);
        struct jffs2_full_dirent *fd, *next;

	D2(printf("jffs2_umount\n"));

	// Only really umount if this is the only mount
	if (jffs2_sb->s_mount_count == 1) {
		icache_evict(root, NULL);
		if (root->i_cache_next != NULL)	{
			struct _inode *inode = root;
			printf("Refuse to unmount.\n");
			while (inode) {
				printf("Ino #%u has use count %d\n",
				       inode->i_ino, inode->i_count);
				inode = inode->i_cache_next;
			}
			// root icount was set to 1 on mount
			return EBUSY;
                }
		if (root->i_count == 2 &&
		    cyg_cdir_mtab_entry == mte &&
		    cyg_cdir_dir == (cyg_dir)root &&
		    !strcmp(mte->name, "/")) {
			/* If we were mounted on root, there's no
			   way for the cwd to change out and free
			   the file system for unmounting. So we hack
			   it -- if cwd is '/' we unset it. Perhaps
			   we should allow chdir(NULL) to unset
			   cyg_cdir_dir? */
			cyg_cdir_dir = CYG_DIR_NULL;
			jffs2_iput(root);
		}
		/* Argh. The fileio code sets this; never clears it */
		if (cyg_cdir_mtab_entry == mte)
			cyg_cdir_mtab_entry = NULL;

		if (root->i_count != 1) {
			printf("Ino #1 has use count %d\n",
			       root->i_count);
			return EBUSY;
		}
#ifdef CYGOPT_FS_JFFS2_GCTHREAD
		jffs2_stop_garbage_collect_thread(c);
#endif
		jffs2_iput(root);	// Time to free the root inode

		// free directory entries
		for (fd = root->jffs2_i.dents; fd; fd = next) {
		  next=fd->next;
		  jffs2_free_full_dirent(fd);
		}

		rt_free(root);
		//Clear root inode
		//root_i = NULL;

		// Clean up the super block and root inode
		jffs2_free_ino_caches(c);
		jffs2_free_raw_node_refs(c);
		rt_free(c->blocks);
		rt_free(c->inocache_list);
		rt_free(jffs2_sb);
		// Clear superblock & root pointer
		mte->root = CYG_DIR_NULL;
                mte->data = 0;
		mte->fs->data = 0;	// fstab entry, visible to all mounts. No current mount
		// That's all folks.
		D2(printf("jffs2_umount No current mounts\n"));
	} else {
		jffs2_sb->s_mount_count--;
        }
        if (--n_fs_mounted == 0) {
                jffs2_destroy_slab_caches();
		jffs2_compressors_exit();
	}
	return ENOERR;
}

// -------------------------------------------------------------------------
// jffs2_open()
// Open a file for reading or writing.

int jffs2_open(cyg_mtab_entry * mte, cyg_dir dir, const char *name,
		      int mode, cyg_file * file)
{

	jffs2_dirsearch ds;
	struct _inode *node = NULL;
	int err;

	D2(printf("jffs2_open\n"));

	/* If no chdir has been called and we were the first file system
	   mounted, we get called with dir == NULL. Deal with it */
	if (!dir)
		dir = mte->root;

#ifndef CYGOPT_FS_JFFS2_WRITE
	if (mode & (O_CREAT|O_TRUNC|O_WRONLY))
		return EROFS;
#endif
	init_dirsearch(&ds, (struct _inode *) dir,
                       (const unsigned char *) name);

	err = jffs2_find(&ds);

	if (err == ENOENT) {
#ifdef CYGOPT_FS_JFFS2_WRITE
		if (ds.last && (mode & O_CREAT)) {

			// No node there, if the O_CREAT bit is set then we must
			// create a new one. The dir and name fields of the dirsearch
			// object will have been updated so we know where to put it.

			err = jffs2_create(ds.dir, ds.name, S_IRUGO|S_IXUGO|S_IWUSR|S_IFREG, &node);

			if (err != 0) {
                                //Possible orphaned inode on the flash - but will be gc'd
                          	jffs2_iput(ds.dir);
                                return -err;
			}

			err = ENOERR;
		}
#endif
	} else if (err == ENOERR) {
		// The node exists. If the O_CREAT and O_EXCL bits are set, we
		// must fail the open.

		if ((mode & (O_CREAT | O_EXCL)) == (O_CREAT | O_EXCL)) {
			jffs2_iput(ds.node);
			err = EEXIST;
		} else
			node = ds.node;
	}

	// Finished with the directory now
	jffs2_iput(ds.dir);

	if (err != ENOERR)
		return err;

	// Check that we actually have a file here
	if (S_ISDIR(node->i_mode)) {
		jffs2_iput(node);
		return EISDIR;
	}

             // If the O_TRUNC bit is set we must clean out the file data.
	if (mode & O_TRUNC) {
#ifdef CYGOPT_FS_JFFS2_WRITE
             err = jffs2_truncate_file(node);
             if (err) {
                  jffs2_iput(node);
                  return err;
             }
#else
             jffs2_iput(node);
             return EROFS;
#endif
        }

	// Initialise the file object
	file->f_flag = mode & CYG_FILE_MODE_MASK;
	file->f_type = CYG_FILE_TYPE_FILE;
	file->f_ops = &jffs2_fileops;
	file->f_offset = (mode & O_APPEND) ? node->i_size : 0;
	file->f_data = (CYG_ADDRWORD) node;
	file->f_xops = 0;

	return ENOERR;
}

#ifdef CYGOPT_FS_JFFS2_WRITE
// -------------------------------------------------------------------------
// jffs2_ops_unlink()
// Remove a file link from its directory.

static int jffs2_ops_unlink(cyg_mtab_entry * mte, cyg_dir dir, const char *name)
{
	jffs2_dirsearch ds;
	int err;

	D2(printf("jffs2_ops_unlink\n"));

	init_dirsearch(&ds, (struct _inode *) dir,
                       (const unsigned char *)name);

	err = jffs2_find(&ds);

	if (err != ENOERR) {
		jffs2_iput(ds.dir);
		return err;
	}

	// Cannot unlink directories, use rmdir() instead
	if (S_ISDIR(ds.node->i_mode)) {
		jffs2_iput(ds.dir);
		jffs2_iput(ds.node);
		return EPERM;
	}

	// Delete it from its directory

	err = jffs2_unlink(ds.dir, ds.node, ds.name);
	jffs2_iput(ds.dir);
	jffs2_iput(ds.node);

	return -err;
}

// -------------------------------------------------------------------------
// jffs2_ops_mkdir()
// Create a new directory.

static int jffs2_ops_mkdir(cyg_mtab_entry * mte, cyg_dir dir, const char *name)
{
	jffs2_dirsearch ds;
	int err;

	D2(printf("jffs2_ops_mkdir\n"));

	init_dirsearch(&ds, (struct _inode *) dir,
                       (const unsigned char *)name);

	err = jffs2_find(&ds);

	if (err == ENOENT) {
		if (ds.last) {
			// The entry does not exist, and it is the last element in
			// the pathname, so we can create it here.

			err = -jffs2_mkdir(ds.dir, ds.name, S_IRUGO|S_IXUGO|S_IWUSR);
		}
		// If this was not the last element, then an intermediate
		// directory does not exist.
	} else {
		// If there we no error, something already exists with that
		// name, so we cannot create another one.
               if (err == ENOERR) {
            		jffs2_iput(ds.node);
                        err = EEXIST;
               }
	}
	jffs2_iput(ds.dir);
	return err;
}

// -------------------------------------------------------------------------
// jffs2_ops_rmdir()
// Remove a directory.

static int jffs2_ops_rmdir(cyg_mtab_entry * mte, cyg_dir dir, const char *name)
{
	jffs2_dirsearch ds;
	int err;

	D2(printf("jffs2_ops_rmdir\n"));

	init_dirsearch(&ds, (struct _inode *) dir,
                       (const unsigned char *)name);

	err = jffs2_find(&ds);

	if (err != ENOERR) {
		jffs2_iput(ds.dir);
		return err;
	}

	// Check that this is actually a directory.
	if (!S_ISDIR(ds.node->i_mode)) {
		jffs2_iput(ds.dir);
		jffs2_iput(ds.node);
		return EPERM;
	}

	err = jffs2_rmdir(ds.dir, ds.node, ds.name);

	jffs2_iput(ds.dir);
	jffs2_iput(ds.node);
	return -err;
}

// -------------------------------------------------------------------------
// jffs2_ops_rename()
// Rename a file/dir.

static int jffs2_ops_rename(cyg_mtab_entry * mte, cyg_dir dir1,
			    const char *name1, cyg_dir dir2, const char *name2)
{
	jffs2_dirsearch ds1, ds2;
	int err;

	D2(printf("jffs2_ops_rename\n"));

	init_dirsearch(&ds1, (struct _inode *) dir1,
                       (const unsigned char *)name1);

	err = jffs2_find(&ds1);

	if (err != ENOERR) {
		jffs2_iput(ds1.dir);
		return err;
	}

	init_dirsearch(&ds2, (struct _inode *) dir2,
                       (const unsigned char *)name2);

	err = jffs2_find(&ds2);

	// Allow through renames to non-existent objects.
	if (ds2.last && err == ENOENT) {
		ds2.node = NULL;
		err = ENOERR;
	}

	if (err != ENOERR) {
		jffs2_iput(ds1.dir);
		jffs2_iput(ds1.node);
		jffs2_iput(ds2.dir);
		return err;
	}

	// Null rename, just return
	if (ds1.node == ds2.node) {
		err = ENOERR;
		goto out;
	}

	// First deal with any entry that is at the destination
	if (ds2.node) {
		// Check that we are renaming like-for-like

		if (!S_ISDIR(ds1.node->i_mode) && S_ISDIR(ds2.node->i_mode)) {
			err = EISDIR;
			goto out;
		}

		if (S_ISDIR(ds1.node->i_mode) && !S_ISDIR(ds2.node->i_mode)) {
			err = ENOTDIR;
			goto out;
		}

		// Now delete the destination directory entry
		/* Er, what happened to atomicity of rename()? */
		err = -jffs2_unlink(ds2.dir, ds2.node, ds2.name);

		if (err != 0)
			goto out;

	}
	// Now we know that there is no clashing node at the destination,
	// make a new direntry at the destination and delete the old entry
	// at the source.

	err = -jffs2_rename(ds1.dir, ds1.node, ds1.name, ds2.dir, ds2.name);

	// Update directory times
	if (!err)
		ds1.dir->i_ctime =
		    ds1.dir->i_mtime =
		    ds2.dir->i_ctime = ds2.dir->i_mtime = jffs2_get_timestamp();
 out:
	jffs2_iput(ds1.dir);
	if (S_ISDIR(ds1.node->i_mode)) {
		/* Renamed a directory to elsewhere... so fix up its
		   i_parent pointer and the i_counts of its old and
		   new parents. */
		jffs2_iput(ds1.node->i_parent);
		ds1.node->i_parent = ds2.dir;
		/* We effectively increase its use count by not... */
	} else {
		jffs2_iput(ds2.dir); /* ... doing this */
	}
	jffs2_iput(ds1.node);
	if (ds2.node)
		jffs2_iput(ds2.node);

	return err;
}

// -------------------------------------------------------------------------
// jffs2_ops_link()
// Make a new directory entry for a file.

static int jffs2_ops_link(cyg_mtab_entry * mte, cyg_dir dir1, const char *name1,
			  cyg_dir dir2, const char *name2, int type)
{
	jffs2_dirsearch ds1, ds2;
	int err;

	D2(printf("jffs2_ops_link\n"));

	// Only do hard links for now in this filesystem
	if (type != CYG_FSLINK_HARD)
		return EINVAL;

	init_dirsearch(&ds1, (struct _inode *) dir1,
                       (const unsigned char *) name1);

	err = jffs2_find(&ds1);

	if (err != ENOERR) {
		jffs2_iput(ds1.dir);
		return err;
	}

	init_dirsearch(&ds2, (struct _inode *) dir2,
                       (const unsigned char *) name2);

	err = jffs2_find(&ds2);

	// Don't allow links to existing objects
	if (err == ENOERR) {
		jffs2_iput(ds1.dir);
		jffs2_iput(ds1.node);
		jffs2_iput(ds2.dir);
		jffs2_iput(ds2.node);
		return EEXIST;
	}

	// Allow through links to non-existing terminal objects
	if (ds2.last && err == ENOENT) {
		ds2.node = NULL;
		err = ENOERR;
	}

	if (err != ENOERR) {
		jffs2_iput(ds1.dir);
		jffs2_iput(ds1.node);
		jffs2_iput(ds2.dir);
		return err;
	}

	// Now we know that there is no existing node at the destination,
	// make a new direntry at the destination.

	err = jffs2_link(ds1.node, ds2.dir, ds2.name);

	if (err == 0)
		ds1.node->i_ctime =
		    ds2.dir->i_ctime = ds2.dir->i_mtime = jffs2_get_timestamp();

	jffs2_iput(ds1.dir);
	jffs2_iput(ds1.node);
	jffs2_iput(ds2.dir);

	return -err;
}
#endif /* CYGOPT_FS_JFFS2_WRITE */
// -------------------------------------------------------------------------
// jffs2_opendir()
// Open a directory for reading.

static int jffs2_opendir(cyg_mtab_entry * mte, cyg_dir dir, const char *name,
			 cyg_file * file)
{
	jffs2_dirsearch ds;
	int err;

	D2(printf("jffs2_opendir\n"));

	init_dirsearch(&ds, (struct _inode *) dir,
                       (const unsigned char *) name);

	err = jffs2_find(&ds);

	jffs2_iput(ds.dir);

	if (err != ENOERR)
		return err;

	// check it is really a directory.
	if (!S_ISDIR(ds.node->i_mode)) {
		jffs2_iput(ds.node);
		return ENOTDIR;
	}

	// Initialize the file object, setting the f_ops field to a
	// special set of file ops.

	file->f_flag = 0;
	file->f_type = CYG_FILE_TYPE_FILE;
	file->f_ops = &jffs2_dirops;
	file->f_offset = 0;
	file->f_data = (CYG_ADDRWORD) ds.node;
	file->f_xops = 0;

	return ENOERR;

}

// -------------------------------------------------------------------------
// jffs2_chdir()
// Change directory support.

static int jffs2_chdir(cyg_mtab_entry * mte, cyg_dir dir, const char *name,
		       cyg_dir * dir_out)
{
	D2(printf("jffs2_chdir\n"));

	if (dir_out != NULL) {
		// This is a request to get a new directory pointer in
		// *dir_out.

		jffs2_dirsearch ds;
		int err;

		init_dirsearch(&ds, (struct _inode *) dir,
                               (const unsigned char *) name);

		err = jffs2_find(&ds);
		jffs2_iput(ds.dir);

		if (err != ENOERR)
			return err;

		// check it is a directory
		if (!S_ISDIR(ds.node->i_mode)) {
                        jffs2_iput(ds.node);
			return ENOTDIR;
                }

		// Pass it out
		*dir_out = (cyg_dir) ds.node;
	} else {
		// If no output dir is required, this means that the mte and
		// dir arguments are the current cdir setting and we should
		// forget this fact.

		struct _inode *node = (struct _inode *) dir;

		// Just decrement directory reference count.
		jffs2_iput(node);
	}

	return ENOERR;
}

// -------------------------------------------------------------------------
// jffs2_stat()
// Get struct stat info for named object.

static int jffs2_stat(cyg_mtab_entry * mte, cyg_dir dir, const char *name,
		      struct stat *buf)
{
	jffs2_dirsearch ds;
	int err;

	D2(printf("jffs2_stat\n"));

	init_dirsearch(&ds, (struct _inode *) dir,
                       (const unsigned char *) name);

	err = jffs2_find(&ds);
	jffs2_iput(ds.dir);

	if (err != ENOERR)
		return err;

	// Fill in the status
	buf->st_mode = ds.node->i_mode;
	buf->st_ino = ds.node->i_ino;
	buf->st_dev = 0;
	buf->st_nlink = ds.node->i_nlink;
	buf->st_uid = ds.node->i_uid;
	buf->st_gid = ds.node->i_gid;
	buf->st_size = ds.node->i_size;
	buf->st_atime = ds.node->i_atime;
	buf->st_mtime = ds.node->i_mtime;
	buf->st_ctime = ds.node->i_ctime;

	jffs2_iput(ds.node);

	return ENOERR;
}

// -------------------------------------------------------------------------
// jffs2_getinfo()
// Getinfo. Currently only support pathconf().

static int jffs2_getinfo(cyg_mtab_entry * mte, cyg_dir dir, const char *name,
			 int key, void *buf, int len)
{
	jffs2_dirsearch ds;
	int err;

	D2(printf("jffs2_getinfo\n"));

	init_dirsearch(&ds, (struct _inode *) dir,
                       (const unsigned char *) name);

	err = jffs2_find(&ds);
	jffs2_iput(ds.dir);

	if (err != ENOERR)
		return err;

	switch (key) {
	case FS_INFO_CONF:
		err = jffs2_pathconf(ds.node, (struct cyg_pathconf_info *) buf);
		break;

	default:
		err = EINVAL;
	}

	jffs2_iput(ds.node);
	return err;
}

// -------------------------------------------------------------------------
// jffs2_setinfo()
// Setinfo. Nothing to support here at present.

static int jffs2_setinfo(cyg_mtab_entry * mte, cyg_dir dir, const char *name,
			 int key, void *buf, int len)
{
	// No setinfo keys supported at present

	D2(printf("jffs2_setinfo\n"));

	return EINVAL;
}

//==========================================================================
// File operations

// -------------------------------------------------------------------------
// jffs2_fo_read()
// Read data from the file.

int jffs2_fo_read(struct CYG_FILE_TAG *fp, struct CYG_UIO_TAG *uio)
{
	struct _inode *inode = (struct _inode *) fp->f_data;
	struct jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	struct jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	int i;
	ssize_t resid = uio->uio_resid;
	off_t pos = fp->f_offset;

	down(&f->sem);

	// Loop over the io vectors until there are none left
	for (i = 0; i < uio->uio_iovcnt && pos < inode->i_size; i++) {
		int ret;
		cyg_iovec *iov = &uio->uio_iov[i];
		off_t len = min(iov->iov_len, inode->i_size - pos);

		D2(printf("jffs2_fo_read inode size %d\n", inode->i_size));

		ret =
		    jffs2_read_inode_range(c, f,
					   (unsigned char *) iov->iov_base, pos,
					   len);
		if (ret) {
			D1(printf
			   ("jffs2_fo_read(): read_inode_range failed %d\n",
			    ret));
			uio->uio_resid = resid;
			up(&f->sem);
			return -ret;
		}
		resid -= len;
		pos += len;
	}

	// We successfully read some data, update the node's access time
	// and update the file offset and transfer residue.

	inode->i_atime = jffs2_get_timestamp();

	uio->uio_resid = resid;
	fp->f_offset = pos;

	up(&f->sem);

	return ENOERR;
}


#ifdef CYGOPT_FS_JFFS2_WRITE
// -------------------------------------------------------------------------
// jffs2_fo_write()
// Write data to file.
static int jffs2_extend_file (struct _inode *inode, struct jffs2_raw_inode *ri,
		       unsigned long offset)
{
	struct jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	struct jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	struct jffs2_full_dnode *fn;
	uint32_t phys_ofs, alloc_len;
	int ret = 0;

	/* Make new hole frag from old EOF to new page */
	D1(printk(KERN_DEBUG "Writing new hole frag 0x%x-0x%x between current EOF and new page\n",
		  (unsigned int)inode->i_size, offset));

	ret = jffs2_reserve_space(c, sizeof(*ri), &phys_ofs, &alloc_len, ALLOC_NORMAL);
	if (ret)
		return ret;

	down(&f->sem);

	ri->magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	ri->nodetype = cpu_to_je16(JFFS2_NODETYPE_INODE);
	ri->totlen = cpu_to_je32(sizeof(*ri));
	ri->hdr_crc = cpu_to_je32(crc32(0, ri, sizeof(struct jffs2_unknown_node)-4));

	ri->version = cpu_to_je32(++f->highest_version);
	ri->isize = cpu_to_je32(max((uint32_t)inode->i_size, offset));

	ri->offset = cpu_to_je32(inode->i_size);
	ri->dsize = cpu_to_je32(offset - inode->i_size);
	ri->csize = cpu_to_je32(0);
	ri->compr = JFFS2_COMPR_ZERO;
	ri->node_crc = cpu_to_je32(crc32(0, ri, sizeof(*ri)-8));
	ri->data_crc = cpu_to_je32(0);

	fn = jffs2_write_dnode(c, f, ri, NULL, 0, phys_ofs, ALLOC_NORMAL);
	jffs2_complete_reservation(c);
	if (IS_ERR(fn)) {
		ret = PTR_ERR(fn);
		up(&f->sem);
		return ret;
	}
	ret = jffs2_add_full_dnode_to_inode(c, f, fn);
	if (f->metadata) {
		jffs2_mark_node_obsolete(c, f->metadata->raw);
		jffs2_free_full_dnode(f->metadata);
		f->metadata = NULL;
	}
	if (ret) {
		D1(printk(KERN_DEBUG "Eep. add_full_dnode_to_inode() failed in prepare_write, returned %d\n", ret));
		jffs2_mark_node_obsolete(c, fn->raw);
		jffs2_free_full_dnode(fn);
		up(&f->sem);
		return ret;
	}
	inode->i_size = offset;
	up(&f->sem);
	return 0;
}

// jffs2_fo_open()
// Truncate a file
static int jffs2_truncate_file (struct _inode *inode)
{
     struct jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
     struct jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
     struct jffs2_full_dnode *new_metadata, * old_metadata;
     struct jffs2_raw_inode *ri;
     uint32_t phys_ofs, alloclen;
     int err;

     ri = jffs2_alloc_raw_inode();
     if (!ri) {
          return ENOMEM;
     }
     err = jffs2_reserve_space(c, sizeof(*ri), &phys_ofs, &alloclen, ALLOC_NORMAL);

     if (err) {
          jffs2_free_raw_inode(ri);
          return err;
     }
     down(&f->sem);
     ri->magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
     ri->nodetype = cpu_to_je16(JFFS2_NODETYPE_INODE);
     ri->totlen = cpu_to_je32(sizeof(*ri));
     ri->hdr_crc = cpu_to_je32(crc32(0, ri, sizeof(struct jffs2_unknown_node)-4));

     ri->ino = cpu_to_je32(inode->i_ino);
     ri->version = cpu_to_je32(++f->highest_version);

     ri->uid = cpu_to_je16(inode->i_uid);
     ri->gid = cpu_to_je16(inode->i_gid);
     ri->mode = cpu_to_jemode(inode->i_mode);
     ri->isize = cpu_to_je32(0);
     ri->atime = cpu_to_je32(inode->i_atime);
     ri->mtime = cpu_to_je32(jffs2_get_timestamp());
     ri->offset = cpu_to_je32(0);
     ri->csize = ri->dsize = cpu_to_je32(0);
     ri->compr = JFFS2_COMPR_NONE;
     ri->node_crc = cpu_to_je32(crc32(0, ri, sizeof(*ri)-8));
     ri->data_crc = cpu_to_je32(0);
     new_metadata = jffs2_write_dnode(c, f, ri, NULL, 0,
                                      phys_ofs, ALLOC_NORMAL);
     if (IS_ERR(new_metadata)) {
          jffs2_complete_reservation(c);
          jffs2_free_raw_inode(ri);
          up(&f->sem);
          return PTR_ERR(new_metadata);
     }

     /* It worked. Update the inode */
     inode->i_mtime = jffs2_get_timestamp();
     inode->i_size = 0;
     old_metadata = f->metadata;
     jffs2_truncate_fragtree (c, &f->fragtree, 0);
     f->metadata = new_metadata;
     if (old_metadata) {
          jffs2_mark_node_obsolete(c, old_metadata->raw);
          jffs2_free_full_dnode(old_metadata);
     }
     jffs2_free_raw_inode(ri);

     up(&f->sem);
     jffs2_complete_reservation(c);

     return 0;
}

static int jffs2_fo_write(struct CYG_FILE_TAG *fp, struct CYG_UIO_TAG *uio)
{
	struct _inode *inode = (struct _inode *) fp->f_data;
	off_t pos = fp->f_offset;
	ssize_t resid = uio->uio_resid;
	struct jffs2_raw_inode ri;
	struct jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	struct jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	int i;

	// If the APPEND mode bit was supplied, force all writes to
	// the end of the file.
	if (fp->f_flag & CYG_FAPPEND)
		pos = fp->f_offset = inode->i_size;

	if (pos < 0)
		return EINVAL;

	memset(&ri, 0, sizeof(ri));

	ri.ino = cpu_to_je32(f->inocache->ino);
	ri.mode = cpu_to_jemode(inode->i_mode);
	ri.uid = cpu_to_je16(inode->i_uid);
	ri.gid = cpu_to_je16(inode->i_gid);
	ri.atime = ri.ctime = ri.mtime = cpu_to_je32(jffs2_get_timestamp());

	if (pos > inode->i_size) {
		int err;
		ri.version = cpu_to_je32(++f->highest_version);
		err = jffs2_extend_file(inode, &ri, pos);
		if (err)
			return -err;
	}
	ri.isize = cpu_to_je32(inode->i_size);

	// Now loop over the iovecs until they are all done, or
	// we get an error.
	for (i = 0; i < uio->uio_iovcnt; i++) {
		cyg_iovec *iov = &uio->uio_iov[i];
		unsigned char *buf = iov->iov_base;
		off_t len = iov->iov_len;

		uint32_t writtenlen;
		int err;

		D2(printf("jffs2_fo_write page_start_pos %d\n", pos));
		D2(printf("jffs2_fo_write transfer size %d\n", len));

		err = jffs2_write_inode_range(c, f, &ri, buf,
					      pos, len, &writtenlen);
		if (err)
			return -err;

		if (writtenlen != len)
			return ENOSPC;

		pos += len;
		resid -= len;
	}

	// We wrote some data successfully, update the modified and access
	// times of the inode, increase its size appropriately, and update
	// the file offset and transfer residue.
	inode->i_mtime = inode->i_ctime = je32_to_cpu(ri.mtime);
	if (pos > inode->i_size)
		inode->i_size = pos;

	uio->uio_resid = resid;
	fp->f_offset = pos;

	return ENOERR;
}
#endif /* CYGOPT_FS_JFFS2_WRITE */

// -------------------------------------------------------------------------
// jffs2_fo_lseek()
// Seek to a new file position.

static int jffs2_fo_lseek(struct CYG_FILE_TAG *fp, off_t * apos, int whence)
{
	struct _inode *node = (struct _inode *) fp->f_data;
	off_t pos = *apos;

	D2(printf("jffs2_fo_lseek\n"));

	switch (whence) {
	case SEEK_SET:
		// Pos is already where we want to be.
		break;

	case SEEK_CUR:
		// Add pos to current offset.
		pos += fp->f_offset;
		break;

	case SEEK_END:
		// Add pos to file size.
		pos += node->i_size;
		break;

	default:
		return EINVAL;
	}

        if (pos < 0 )
                return EINVAL;

	// All OK, set fp offset and return new position.
	*apos = fp->f_offset = pos;

	return ENOERR;
}

// -------------------------------------------------------------------------
// jffs2_fo_ioctl()
// Handle ioctls. Currently none are defined.

static int jffs2_fo_ioctl(struct CYG_FILE_TAG *fp, CYG_ADDRWORD com,
			  CYG_ADDRWORD data)
{
	// No Ioctls currenly defined.

	D2(printf("jffs2_fo_ioctl\n"));

	return EINVAL;
}

// -------------------------------------------------------------------------
// jffs2_fo_fsync().
// Force the file out to data storage.

static int jffs2_fo_fsync(struct CYG_FILE_TAG *fp, int mode)
{
	// Data is always permanently where it belongs, nothing to do
	// here.

	D2(printf("jffs2_fo_fsync\n"));

	return ENOERR;
}

// -------------------------------------------------------------------------
// jffs2_fo_close()
// Close a file. We just decrement the refcnt and let it go away if
// that is all that is keeping it here.

static int jffs2_fo_close(struct CYG_FILE_TAG *fp)
{
	struct _inode *node = (struct _inode *) fp->f_data;

	D2(printf("jffs2_fo_close\n"));

	jffs2_iput(node);

	fp->f_data = 0;		// zero data pointer

	return ENOERR;
}

// -------------------------------------------------------------------------
//jffs2_fo_fstat()
// Get file status.

static int jffs2_fo_fstat(struct CYG_FILE_TAG *fp, struct stat *buf)
{
	struct _inode *node = (struct _inode *) fp->f_data;

	D2(printf("jffs2_fo_fstat\n"));

	// Fill in the status
	buf->st_mode = node->i_mode;
	buf->st_ino = node->i_ino;
	buf->st_dev = 0;
	buf->st_nlink = node->i_nlink;
	buf->st_uid = node->i_uid;
	buf->st_gid = node->i_gid;
	buf->st_size = node->i_size;
	buf->st_atime = node->i_atime;
	buf->st_mtime = node->i_mtime;
	buf->st_ctime = node->i_ctime;

	return ENOERR;
}

// -------------------------------------------------------------------------
// jffs2_fo_getinfo()
// Get info. Currently only supports fpathconf().

static int jffs2_fo_getinfo(struct CYG_FILE_TAG *fp, int key, void *buf,
			    int len)
{
	struct _inode *node = (struct _inode *) fp->f_data;
	int err;

	D2(printf("jffs2_fo_getinfo\n"));

	switch (key) {
	case FS_INFO_CONF:
		err = jffs2_pathconf(node, (struct cyg_pathconf_info *) buf);
		break;

	default:
		err = EINVAL;
	}
	return err;
}

// -------------------------------------------------------------------------
// jffs2_fo_setinfo()
// Set info. Nothing supported here.

static int jffs2_fo_setinfo(struct CYG_FILE_TAG *fp, int key, void *buf,
			    int len)
{
	// No setinfo key supported at present

	D2(printf("jffs2_fo_setinfo\n"));

	return ENOERR;
}

//==========================================================================
// Directory operations

// -------------------------------------------------------------------------
// jffs2_fo_dirread()
// Read a single directory entry from a file.

static __inline void filldir(char *nbuf, int nlen, const unsigned char *name, int namlen)
{
	int len = nlen < namlen ? nlen : namlen;
	memcpy(nbuf, name, len);
	nbuf[len] = '\0';
}

static int jffs2_fo_dirread(struct CYG_FILE_TAG *fp, struct CYG_UIO_TAG *uio)
{
	struct _inode *d_inode = (struct _inode *) fp->f_data;
	struct dirent *ent = (struct dirent *) uio->uio_iov[0].iov_base;
	char *nbuf = ent->d_name;
#ifdef CYGPKG_FS_JFFS2_RET_DIRENT_DTYPE
	struct _inode *c_ino;
#endif
	int nlen = sizeof (ent->d_name) - 1;
	off_t len = uio->uio_iov[0].iov_len;
	struct jffs2_inode_info *f;
	struct _inode *inode = d_inode;
	struct jffs2_full_dirent *fd;
	unsigned long offset, curofs;
	int found = 1;

	if (len < sizeof (struct dirent))
		return EINVAL;

	D1(printk
	   (KERN_DEBUG "jffs2_readdir() for dir_i #%lu\n", d_inode->i_ino));

	f = JFFS2_INODE_INFO(inode);

	offset = fp->f_offset;

	if (offset == 0) {
		D1(printk
		   (KERN_DEBUG "Dirent 0: \".\", ino #%lu\n", inode->i_ino));
		filldir(nbuf, nlen, (const unsigned char *) ".", 1);
#ifdef CYGPKG_FS_JFFS2_RET_DIRENT_DTYPE
 		// Flags here are the same as jffs2_mkdir. Make sure
                // d_type is the same as st_mode of calling stat.
                ent->d_type =
                  jemode_to_cpu(cpu_to_jemode(S_IRUGO|S_IXUGO|S_IWUSR|S_IFDIR));
#endif
                goto out;
	}
	if (offset == 1) {
		filldir(nbuf, nlen, (const unsigned char *) "..", 2);
#ifdef CYGPKG_FS_JFFS2_RET_DIRENT_DTYPE
                // Flags here are the same as jffs2_mkdir. Make sure
                // d_type is the same as st_mode of calling stat.
                ent->d_type =
                  jemode_to_cpu(cpu_to_jemode(S_IRUGO|S_IXUGO|S_IWUSR|S_IFDIR));
#endif
                goto out;
	}

	curofs = 1;
	down(&f->sem);
	for (fd = f->dents; fd; fd = fd->next) {

		curofs++;
		/* First loop: curofs = 2; offset = 2 */
		if (curofs < offset) {
			D2(printk
			   (KERN_DEBUG
			    "Skipping dirent: \"%s\", ino #%u, type %d, because curofs %ld < offset %ld\n",
			    fd->name, fd->ino, fd->type, curofs, offset));
			continue;
		}
		if (!fd->ino) {
			D2(printk
			   (KERN_DEBUG "Skipping deletion dirent \"%s\"\n",
			    fd->name));
			offset++;
			continue;
		}
		D2(printk
		   (KERN_DEBUG "Dirent %ld: \"%s\", ino #%u, type %d\n", offset,
		    fd->name, fd->ino, fd->type));
		filldir(nbuf, nlen, fd->name, strlen((char *)fd->name));
#ifdef CYGPKG_FS_JFFS2_RET_DIRENT_DTYPE
		c_ino = jffs2_iget(inode->i_sb, fd->ino);
		if(IS_ERR(c_ino)) {
			D1(printk(KERN_WARNING "get entry inode failed\n"));
			// fileio already set it to zero, so not needed here
			// ent->d_type = 0;
		}
		else {
			ent->d_type = c_ino->i_mode;
			jffs2_iput(c_ino);
		}
#endif
		goto out_sem;
	}
	/* Reached the end of the directory */
	found = 0;
      out_sem:
	up(&f->sem);
      out:
	fp->f_offset = ++offset;
	if (found) {
		uio->uio_resid -= sizeof (struct dirent);
	}
	return ENOERR;
}

// -------------------------------------------------------------------------
// jffs2_fo_dirlseek()
// Seek directory to start.

static int jffs2_fo_dirlseek(struct CYG_FILE_TAG *fp, off_t * pos, int whence)
{
	// Only allow SEEK_SET to zero

	D2(printf("jffs2_fo_dirlseek\n"));

	if (whence != SEEK_SET || *pos != 0)
		return EINVAL;

	*pos = fp->f_offset = 0;

	return ENOERR;
}

//==========================================================================
//
// Called by JFFS2
// ===============
//
//
//==========================================================================

unsigned char *jffs2_gc_fetch_page(struct jffs2_sb_info *c,
				   struct jffs2_inode_info *f,
				   unsigned long offset,
				   unsigned long *priv)
{
	/* FIXME: This works only with one file system mounted at a time */
	int ret;

	ret = jffs2_read_inode_range(c, f, gc_buffer,
				     offset & ~(PAGE_CACHE_SIZE-1), PAGE_CACHE_SIZE);
	if (ret)
		return ERR_PTR(ret);

	return gc_buffer;
}

void jffs2_gc_release_page(struct jffs2_sb_info *c,
			   unsigned char *ptr,
			   unsigned long *priv)
{
	/* Do nothing */
}

static struct _inode *new_inode(struct super_block *sb)
{
	struct _inode *inode;
	struct _inode *cached_inode;

	inode = rt_malloc(sizeof (struct _inode));
	if (inode == NULL)
		return 0;

	D2(printf("malloc new_inode %x ####################################\n",
	    inode));

	memset(inode, 0, sizeof (struct _inode));
	inode->i_sb = sb;
	inode->i_ino = 1;
	inode->i_count = 1;
	inode->i_nlink = 1;	// Let JFFS2 manage the link count
	inode->i_size = 0;

	inode->i_cache_next = NULL;	// Newest inode, about to be cached

	// Add to the icache
	for (cached_inode = sb->s_root; cached_inode != NULL;
	     cached_inode = cached_inode->i_cache_next) {
		if (cached_inode->i_cache_next == NULL) {
			cached_inode->i_cache_next = inode;	// Current last in cache points to newcomer
			inode->i_cache_prev = cached_inode;	// Newcomer points back to last
			break;
		}
	}
	return inode;
}

static struct _inode *ilookup(struct super_block *sb, cyg_uint32 ino)
{
	struct _inode *inode = NULL;

	D2(printf("ilookup\n"));
	// Check for this inode in the cache
	for (inode = sb->s_root; inode != NULL; inode = inode->i_cache_next) {
		if (inode->i_ino == ino) {
			inode->i_count++;
			break;
		}
	}
	return inode;
}

struct _inode *jffs2_iget(struct super_block *sb, cyg_uint32 ino)
{
	// Called in super.c jffs2_read_super, dir.c jffs2_lookup,
	// and gc.c jffs2_garbage_collect_pass

	// Must first check for cached inode
	// If this fails let new_inode create one

	struct _inode *inode;
	int err;

	D2(printf("jffs2_iget\n"));

	inode = ilookup(sb, ino);
	if (inode)
		return inode;

	// Not cached, so malloc it
	inode = new_inode(sb);
	if (inode == NULL)
		return ERR_PTR(-ENOMEM);

	inode->i_ino = ino;

	err = jffs2_read_inode(inode);
	if (err) {
		printf("jffs2_read_inode() failed\n");
                inode->i_nlink = 0; // free _this_ bad inode right now
		jffs2_iput(inode);
		inode = NULL;
		return ERR_PTR(err);
	}
	return inode;
}

// -------------------------------------------------------------------------
// Decrement the reference count on an inode. If this makes the ref count
// zero, then this inode can be freed.

void jffs2_iput(struct _inode *i)
{
	// Called in jffs2_find
	// (and jffs2_open and jffs2_ops_mkdir?)
	// super.c jffs2_read_super,
	// and gc.c jffs2_garbage_collect_pass
 recurse:
	if (!i) {
		printf("jffs2_iput() called with NULL inode\n");
		// and let it fault...
	}

	i->i_count--;

	if (i->i_count < 0)
		BUG();

	if (i->i_count)
                return;

	if (!i->i_nlink) {
		struct _inode *parent;

		// Remove from the icache linked list and free immediately
		if (i->i_cache_prev)
			i->i_cache_prev->i_cache_next = i->i_cache_next;
		if (i->i_cache_next)
			i->i_cache_next->i_cache_prev = i->i_cache_prev;

		parent = i->i_parent;
		jffs2_clear_inode(i);
		memset(i, 0x5a, sizeof(*i));
		rt_free(i);

		if (parent && parent != i) {
			i = parent;
			goto recurse;
		}

	} else {
		// Evict some _other_ inode with i_count zero, leaving
		// this latest one in the cache for a while
		icache_evict(i->i_sb->s_root, i);
	}
}


// -------------------------------------------------------------------------
// EOF jffs2.c


static inline void jffs2_init_inode_info(struct jffs2_inode_info *f)
{
	memset(f, 0, sizeof(*f));
	init_MUTEX_LOCKED(&f->sem);
}

static void jffs2_clear_inode (struct _inode *inode)
{
        /* We can forget about this inode for now - drop all
         *  the nodelists associated with it, etc.
         */
        struct jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
        struct jffs2_inode_info *f = JFFS2_INODE_INFO(inode);

        D1(printk(KERN_DEBUG "jffs2_clear_inode(): ino #%lu mode %o\n", inode->i_ino, inode->i_mode));

        jffs2_do_clear_inode(c, f);
}


/* jffs2_new_inode: allocate a new inode and inocache, add it to the hash,
   fill in the raw_inode while you're at it. */
struct _inode *jffs2_new_inode (struct _inode *dir_i, int mode, struct jffs2_raw_inode *ri)
{
	struct _inode *inode;
	struct super_block *sb = dir_i->i_sb;
	struct jffs2_sb_info *c;
	struct jffs2_inode_info *f;
	int ret;

	D1(printk(KERN_DEBUG "jffs2_new_inode(): dir_i %ld, mode 0x%x\n", dir_i->i_ino, mode));

	c = JFFS2_SB_INFO(sb);

	inode = new_inode(sb);

	if (!inode)
		return ERR_PTR(-ENOMEM);

	f = JFFS2_INODE_INFO(inode);
	jffs2_init_inode_info(f);

	memset(ri, 0, sizeof(*ri));
	/* Set OS-specific defaults for new inodes */
	ri->uid = ri->gid = cpu_to_je16(0);
	ri->mode =  cpu_to_jemode(mode);
	ret = jffs2_do_new_inode (c, f, mode, ri);
	if (ret) {
                // forceful evict: f->sem is locked already, and the
                // inode is bad.
                if (inode->i_cache_prev)
                       inode->i_cache_prev->i_cache_next = inode->i_cache_next;
                if (inode->i_cache_next)
                       inode->i_cache_next->i_cache_prev = inode->i_cache_prev;
                up(&(f->sem));
                jffs2_clear_inode(inode);
                memset(inode, 0x6a, sizeof(*inode));
                rt_free(inode);
                return ERR_PTR(ret);
	}
	inode->i_nlink = 1;
	inode->i_ino = je32_to_cpu(ri->ino);
	inode->i_mode = jemode_to_cpu(ri->mode);
	inode->i_gid = je16_to_cpu(ri->gid);
	inode->i_uid = je16_to_cpu(ri->uid);
	inode->i_atime = inode->i_ctime = inode->i_mtime = jffs2_get_timestamp();
	ri->atime = ri->mtime = ri->ctime = cpu_to_je32(inode->i_mtime);

	inode->i_size = 0;

	return inode;
}


static int jffs2_read_inode (struct _inode *inode)
{
	struct jffs2_inode_info *f;
	struct jffs2_sb_info *c;
	struct jffs2_raw_inode latest_node;
	int ret;

	D1(printk(KERN_DEBUG "jffs2_read_inode(): inode->i_ino == %lu\n", inode->i_ino));

	f = JFFS2_INODE_INFO(inode);
	c = JFFS2_SB_INFO(inode->i_sb);

	jffs2_init_inode_info(f);

	ret = jffs2_do_read_inode(c, f, inode->i_ino, &latest_node);

	if (ret) {
		up(&f->sem);
		return ret;
	}
	inode->i_mode = jemode_to_cpu(latest_node.mode);
	inode->i_uid = je16_to_cpu(latest_node.uid);
	inode->i_gid = je16_to_cpu(latest_node.gid);
	inode->i_size = je32_to_cpu(latest_node.isize);
	inode->i_atime = je32_to_cpu(latest_node.atime);
	inode->i_mtime = je32_to_cpu(latest_node.mtime);
	inode->i_ctime = je32_to_cpu(latest_node.ctime);

	inode->i_nlink = f->inocache->nlink;
	up(&f->sem);

	D1(printk(KERN_DEBUG "jffs2_read_inode() returning\n"));
	return 0;
}


void jffs2_gc_release_inode(struct jffs2_sb_info *c,
				   struct jffs2_inode_info *f)
{
	jffs2_iput(OFNI_EDONI_2SFFJ(f));
}

struct jffs2_inode_info *jffs2_gc_fetch_inode(struct jffs2_sb_info *c,
						     int inum, int nlink)
{
	struct _inode *inode;
	struct jffs2_inode_cache *ic;
	if (!nlink) {
		/* The inode has zero nlink but its nodes weren't yet marked
		   obsolete. This has to be because we're still waiting for
		   the final (close() and) jffs2_iput() to happen.

		   There's a possibility that the final jffs2_iput() could have
		   happened while we were contemplating. In order to ensure
		   that we don't cause a new read_inode() (which would fail)
		   for the inode in question, we use ilookup() in this case
		   instead of jffs2_iget().

		   The nlink can't _become_ zero at this point because we're
		   holding the alloc_sem, and jffs2_do_unlink() would also
		   need that while decrementing nlink on any inode.
		*/
		inode = ilookup(OFNI_BS_2SFFJ(c), inum);
		if (!inode) {
			D1(printk(KERN_DEBUG "ilookup() failed for ino #%u; inode is probably deleted.\n",
				  inum));

			spin_lock(&c->inocache_lock);
			ic = jffs2_get_ino_cache(c, inum);
			if (!ic) {
				D1(printk(KERN_DEBUG "Inode cache for ino #%u is gone.\n", inum));
				spin_unlock(&c->inocache_lock);
				return NULL;
			}
			if (ic->state != INO_STATE_CHECKEDABSENT) {
				/* Wait for progress. Don't just loop */
				D1(printk(KERN_DEBUG "Waiting for ino #%u in state %d\n",
					  ic->ino, ic->state));
				sleep_on_spinunlock(&c->inocache_wq, &c->inocache_lock);
			} else {
				spin_unlock(&c->inocache_lock);
			}

			return NULL;
		}
	} else {
		/* Inode has links to it still; they're not going away because
		   jffs2_do_unlink() would need the alloc_sem and we have it.
		   Just jffs2_iget() it, and if read_inode() is necessary that's OK.
		*/
		inode = jffs2_iget(OFNI_BS_2SFFJ(c), inum);
		if (IS_ERR(inode))
			return (void *)inode;
	}

	return JFFS2_INODE_INFO(inode);
}



uint32_t jffs2_from_os_mode(uint32_t osmode)
{
	uint32_t jmode = ((osmode & S_IRUSR)?00400:0) |
		((osmode & S_IWUSR)?00200:0) |
		((osmode & S_IXUSR)?00100:0) |
		((osmode & S_IRGRP)?00040:0) |
		((osmode & S_IWGRP)?00020:0) |
		((osmode & S_IXGRP)?00010:0) |
		((osmode & S_IROTH)?00004:0) |
		((osmode & S_IWOTH)?00002:0) |
		((osmode & S_IXOTH)?00001:0);

	switch (osmode & S_IFMT) {
//	case S_IFSOCK:
//		return jmode | 0140000;
//	case S_IFLNK:
//		return jmode | 0120000;
	case S_IFREG:
		return jmode | 0100000;
	case S_IFBLK:
		return jmode | 0060000;
	case S_IFDIR:
		return jmode | 0040000;
	case S_IFCHR:
		return jmode | 0020000;
	case S_IFIFO:
		return jmode | 0010000;
	case S_ISUID:
		return jmode | 0004000;
	case S_ISGID:
		return jmode | 0002000;
#ifdef S_ISVTX
	case S_ISVTX:
		return jmode | 0001000;
#endif
	}
	printf("os_to_jffs2_mode() cannot convert 0x%x\n", osmode);
	BUG();
	return 0;
}

uint32_t jffs2_to_os_mode (uint32_t jmode)
{
	uint32_t osmode = ((jmode & 00400)?S_IRUSR:0) |
		((jmode & 00200)?S_IWUSR:0) |
		((jmode & 00100)?S_IXUSR:0) |
		((jmode & 00040)?S_IRGRP:0) |
		((jmode & 00020)?S_IWGRP:0) |
		((jmode & 00010)?S_IXGRP:0) |
		((jmode & 00004)?S_IROTH:0) |
		((jmode & 00002)?S_IWOTH:0) |
		((jmode & 00001)?S_IXOTH:0);

	switch(jmode & 00170000) {
//	case 0140000:                       prife
//		return osmode | S_IFSOCK;       prife
//	case 0120000:                       prife
//		return osmode | S_IFLNK;        prife
	case 0100000:
		return osmode | S_IFREG;
	case 0060000:
		return osmode | S_IFBLK;
	case 0040000:
		return osmode | S_IFDIR;
	case 0020000:
		return osmode | S_IFCHR;
	case 0010000:
		return osmode | S_IFIFO;
	case 0004000:
		return osmode | S_ISUID;
	case 0002000:
		return osmode | S_ISGID;
#ifdef S_ISVTX
	case 0001000:
		return osmode | S_ISVTX;
#endif
	}
	printf("jffs2_to_os_mode() cannot convert 0x%x\n", osmode);
	BUG();
	return 0;
}
