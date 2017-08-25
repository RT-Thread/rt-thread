#include <stdio.h>

#include "ndsvfs.h"
#include "dirent.h"

__attribute__((used))
FILE *fopen(const char *path_name, const char *mode)
{
    NDSVFS_DENTRY *vde = HAL_NULL;
    NDSVFS_FILE *file = HAL_NULL;
    UINT32 mode_len;
    UINT32 fmode = 0;
    UINT32 i;

    if (HAL_SUCCESS != _ndsvfs_lock())
        return HAL_NULL;

    // alloc file object
    file = _ndsvfs_alloc_file();
    if (file == HAL_NULL)
        goto _safe_exit;

    // open flags
    if (mode == HAL_NULL)
        mode_len = 0;
    else
        mode_len = (UINT32)strlen(mode);

    for (i = 0; i < mode_len; ++i)
    {
        switch (mode[i])
        {
        case 'r':
            fmode |= NDSVFS_FOPEN_READ;
            break;
        case 'w':
            fmode |= NDSVFS_FOPEN_WRITE;
            break;
        case 'a':
            fmode |= NDSVFS_FOPEN_APPEND;
            break;
        case '+':
            fmode |= NDSVFS_FOPEN_PLUS;
            break;
        }
    }

    if (fmode == 0)
        goto _safe_exit;
#if 0
    // (todo) current imp should be read only
    if (fmode & ~NDSVFS_FOPEN_READ)
        goto _safe_exit;
    if (!(fmode & NDSVFS_FOPEN_READ))
        goto _safe_exit;
    // ~(todo)
#endif
    // lookup file entry
    if (path_name == HAL_NULL)
        goto _safe_exit;

    if ((INT)strlen(path_name) == 0)
        goto _safe_exit;

    vde = _ndsvfs_path_lookup((const char *)path_name);
    if (!vde)
    {
        // (todo) create the file if not exist and flag is not read only
        goto _safe_exit;
    }

    // current imp allows only regular file
    // we can open dir now, so I comments the codes
#if 0
    if (vde->inode->mode & NDSVFS_INM_ATTR_MASK)
        goto _safe_exit;
#endif
    // notify file system to open the file
    // (todo) call this only when user mode reference to the file is 0.
    if (HAL_SUCCESS != vde->sb->open_file(vde, fmode))
        goto _safe_exit;

    file->flags = fmode;
    file->vde = vde;
    //file->pos = 0;

    //DEBUG(0, 1,"fopen() 0x%08lx\r\n", (UINT32)file);

    _ndsvfs_unlock();

    // todo
    return (FILE *)file;

_safe_exit:

    if (vde)
        NDSVFS_DEREF(vde);
    file->vde = HAL_NULL;

    if (file)
        NDSVFS_DEREF(file);

    _ndsvfs_unlock();

    return HAL_NULL;
}

__attribute__((used))
int fclose(FILE *stream)
{
    if (stream == HAL_NULL)
        return (int)-NDS_VFSD_INVALID_PARAMETER;

    if (HAL_SUCCESS != _ndsvfs_lock())
        return (int)HAL_ERR_INVALID_OPERATION;

    //DEBUG(0, 1,"fclose() 0x%08lx\r\n", (UINT32)stream);

    // (todo) flush the file contents if ever been modified

    // notify file system to close the file
    // (todo) call this only when user mode reference to the file decreased to 0.
    ((NDSVFS_FILE *)stream)->vde->sb->close_file(((NDSVFS_FILE *)stream)->vde);

    // release file references
    if (stream)
        NDSVFS_DEREF(stream);

    if (HAL_SUCCESS != _ndsvfs_unlock())
        return (int)HAL_ERR_INVALID_OPERATION;

    return (int)HAL_SUCCESS;
}

__attribute__((used))
size_t fread(void *ptr, size_t size, size_t count, FILE *stream)
{
    STATUS status;
    UINT32 d_size = (UINT32)size * (UINT32)count;
    UINT32 r_size;  // size actually been read

#if 1
    DEBUG(0, 1,"fread() 0x%08lx ptr(0x%08lx) size(0x%08lx) count(0x%08lx)\r\n",
        (UINT32)stream, (UINT32)ptr, (UINT32)size, (UINT32)count);
#endif

    if (stream == HAL_NULL)
    {
        ((NDSVFS_FILE *)stream)->err = NDS_VFSD_INVALID_PARAMETER;
        return 0;
    }

    if (HAL_SUCCESS != _ndsvfs_lock())
    {
        ((NDSVFS_FILE *)stream)->err = HAL_ERR_INVALID_OPERATION;
        return 0;
    }

    DEBUG(0, 1,"fread() 0x%08lx >>\r\n", (UINT32)stream);

    if (((NDSVFS_FILE *)stream)->pos < 0)
    {
        DEBUG(0, 1,"fread() 0x%08lx <<\r\n", (UINT32)stream);
        _ndsvfs_unlock();
        ((NDSVFS_FILE *)stream)->err = HAL_ERR_INVALID_START;
        return 0;
    }

    status = ((NDSVFS_FILE *)stream)->vde->sb->read_file(((NDSVFS_FILE *)stream)->vde,
        ptr, (UINT32)((NDSVFS_FILE *)stream)->pos, d_size, &r_size);

    if (status == NDS_VFSD_END_OF_FILE)
    {
        ((NDSVFS_FILE *)stream)->eof = HAL_TRUE;
        status = HAL_SUCCESS;
    }

    if (status == HAL_SUCCESS)
        ((NDSVFS_FILE *)stream)->pos += (INT32)r_size;
    else
        r_size = 0;

    DEBUG(0, 1,"fread() 0x%08lx <<\r\n", (UINT32)stream);
    if (HAL_SUCCESS != _ndsvfs_unlock())
    {
        ((NDSVFS_FILE *)stream)->err = HAL_ERR_INVALID_OPERATION;
        DEBUG(0, 1,"fread() 0x%08lx << unlock fail\r\n", (UINT32)stream);
        return 0;
    }

    return (int)((size_t)r_size / size);
}

__attribute__((used))
size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream)
{
    STATUS status;
    UINT32 d_size = (UINT32)size * (UINT32)count;
    UINT32 w_size;  // size actually been write

#if 1
    DEBUG(0, 1,"fwrite() 0x%08lx ptr(0x%08lx) size(0x%08lx) count(0x%08lx)\r\n",
        (UINT32)stream, (UINT32)ptr, (UINT32)size, (UINT32)count);
#endif

    if (stream == HAL_NULL)
    {
        ((NDSVFS_FILE *)stream)->err = NDS_VFSD_INVALID_PARAMETER;
        return 0;
    }

    if (HAL_SUCCESS != _ndsvfs_lock())
    {
        ((NDSVFS_FILE *)stream)->err = HAL_ERR_INVALID_OPERATION;
        return 0;
    }

    DEBUG(0, 1,"fwrite() 0x%08lx >>\r\n", (UINT32)stream);

    if (((NDSVFS_FILE *)stream)->pos < 0)
    {
        DEBUG(0, 1,"fwrite() 0x%08lx <<\r\n", (UINT32)stream);
        _ndsvfs_unlock();
        ((NDSVFS_FILE *)stream)->err = HAL_ERR_INVALID_START;
        return 0;
    }
    
	status = ((NDSVFS_FILE *)stream)->vde->sb->write_file(((NDSVFS_FILE *)stream)->vde,
        ptr, (UINT32)((NDSVFS_FILE *)stream)->pos, d_size, &w_size);

    if (status == NDS_VFSD_END_OF_FILE)
    {
        ((NDSVFS_FILE *)stream)->eof = HAL_TRUE;
        status = HAL_SUCCESS;
    }

    if (status == HAL_SUCCESS)
        ((NDSVFS_FILE *)stream)->pos += (INT32)w_size;
    else
        w_size = 0;

    DEBUG(0, 1,"fwrite() 0x%08lx <<\r\n", (UINT32)stream);
    if (HAL_SUCCESS != _ndsvfs_unlock())
    {
        ((NDSVFS_FILE *)stream)->err = HAL_ERR_INVALID_OPERATION;
        DEBUG(0, 1,"fwrite() 0x%08lx << unlock fail\r\n", (UINT32)stream);
        return 0;
    }

    return (int)((size_t)w_size / size);
}

__attribute__((used))
int  fflush(FILE *stream)
{
    if (stream == HAL_NULL)
        return (int)NDS_VFSD_INVALID_PARAMETER;

    // todo
    return (int)HAL_SUCCESS;
}

__attribute__((used))
int fseek(FILE *stream, int offset, int origin)
{
    INT32 pos;

    if (stream == HAL_NULL)
        return (int)NDS_VFSD_INVALID_PARAMETER;

    if (HAL_SUCCESS != _ndsvfs_lock())
        return (int)HAL_ERR_INVALID_OPERATION;

    pos = ((NDSVFS_FILE *)stream)->pos;

    //DEBUG(0, 1,"fseek() 0x%08lx >>\r\n", (UINT32)stream);
    //DEBUG(0, 1,"pos (cur) : 0x%08lx\r\n", pos);
    //DEBUG(0, 1,"offset    : 0x%08lx\r\n", offset);

    switch (origin)
    {
    case FSEEK_CUR:
        pos += offset;
        break;
    case FSEEK_END:
        pos = (INT32)((NDSVFS_FILE *)stream)->vde->inode->size + offset;
        break;
    case FSEEK_SET:
        pos = offset;
        break;
    default:
        //DEBUG(0, 1,"fseek() 0x%08lx <<\r\n", (UINT32)stream);
        _ndsvfs_unlock();
        return (int)NDS_VFSD_INVALID_PARAMETER;
    }

    //DEBUG(0, 1,"pos (new) : 0x%08lx\r\n", pos);

    /*
    if (pos > ((NDSVFS_FILE *)stream)->vde->inode->size)
    {
        _ndsvfs_unlock();
        return (int)NDS_VFSD_INVALID_PARAMETER;  // todo: might be a valid condition for write-mode
    }*/

    ((NDSVFS_FILE *)stream)->pos = pos;

    //DEBUG(0, 1,"fseek() 0x%08lx <<\r\n", (UINT32)stream);

    if (HAL_SUCCESS != _ndsvfs_unlock())
        return (int)HAL_ERR_INVALID_OPERATION;

    return (int)HAL_SUCCESS;
}

__attribute__((used))
long ftell(FILE *stream)
{
    long pos;

    if (stream == HAL_NULL)
        return (int)HAL_ERR_INVALID_OPERATION;

    if (HAL_SUCCESS != _ndsvfs_lock())
        return (int)HAL_ERR_INVALID_OPERATION;

    pos = (long)((NDSVFS_FILE *)stream)->pos;

    if (HAL_SUCCESS != _ndsvfs_unlock())
        return (int)HAL_ERR_INVALID_OPERATION;

    return pos;
}

void frewind(FILE *stream)
{
    if (stream == HAL_NULL)
        return;

    if (HAL_SUCCESS != _ndsvfs_lock())
        return;

    ((NDSVFS_FILE *)stream)->pos = 0;
    ((NDSVFS_FILE *)stream)->err = 0;
    ((NDSVFS_FILE *)stream)->eof = 0;

    if (HAL_SUCCESS != _ndsvfs_unlock())
        return;
}

__attribute__((used))
int fgetpos(FILE *stream, fpos_t *position)
{
    if (stream == HAL_NULL)
        return (int)NDS_VFSD_INVALID_PARAMETER;

    if (position == HAL_NULL)
        return (int)NDS_VFSD_INVALID_PARAMETER;

    if (HAL_SUCCESS != _ndsvfs_lock())
        return (int)HAL_ERR_INVALID_OPERATION;

    *position = ((NDSVFS_FILE *)stream)->pos;

    if (HAL_SUCCESS != _ndsvfs_unlock())
        return (int)HAL_ERR_INVALID_OPERATION;

    return (int)HAL_SUCCESS;
}

__attribute__((used))
int fsetpos(FILE *stream, const fpos_t *position)
{
    if (stream == HAL_NULL)
        return (int)NDS_VFSD_INVALID_PARAMETER;

    if (position == HAL_NULL)
        return (int)NDS_VFSD_INVALID_PARAMETER;

    if (HAL_SUCCESS != _ndsvfs_lock())
        return (int)HAL_ERR_INVALID_OPERATION;

    if (*position > (INT32)((NDSVFS_FILE *)stream)->vde->inode->size)
    {
        _ndsvfs_unlock();
        return (int)NDS_VFSD_INVALID_PARAMETER;  // todo: might be a valid condition for write-mode
    }

    ((NDSVFS_FILE *)stream)->pos = *position;
    ((NDSVFS_FILE *)stream)->eof = 0;  // ?? todo: signal eof if position reaches end of file?

    if (HAL_SUCCESS != _ndsvfs_unlock())
        return (int)HAL_ERR_INVALID_OPERATION;

    return (int)HAL_SUCCESS;
}

__attribute__((used))
int feof(FILE *stream)
{
    UINT32 eof;

    if (HAL_SUCCESS != _ndsvfs_lock())
        return (int)HAL_ERR_INVALID_OPERATION;

    eof = ((NDSVFS_FILE *)stream)->eof > 0 ? HAL_TRUE : HAL_FALSE;

    if (HAL_SUCCESS != _ndsvfs_unlock())
        return (int)HAL_ERR_INVALID_OPERATION;

    return eof;
}

__attribute__((used))
int ferror(FILE *stream)
{
    UINT32 err;

    if (HAL_SUCCESS != _ndsvfs_lock())
        return (int)HAL_ERR_INVALID_OPERATION;

    err = ((NDSVFS_FILE *)stream)->err > 0 ? 1 : 0;

    if (HAL_SUCCESS != _ndsvfs_unlock())
        return (int)HAL_ERR_INVALID_OPERATION;

    return err;
}

void fclearerr(FILE *stream)
{
    if (HAL_SUCCESS != _ndsvfs_lock())
        return;

    ((NDSVFS_FILE *)stream)->err = 0;
    ((NDSVFS_FILE *)stream)->eof = 0;

    if (HAL_SUCCESS != _ndsvfs_unlock())
        return;
}
extern STATUS _ndsvfs_read_dirs(NDSVFS_DENTRY *vde_parent, NDSVFS_DENTRY **vde_list);
__attribute__((used))
struct dir *opendir(const char *path)
{
	NDSVFS_FILE *file = NULL;
	struct dir *dirp = NULL;
	int status;

	file = (NDSVFS_FILE *)fopen(path, "rb");
	if (file == NULL) {
//		ERROR("fopen path=%s\n",path);
		return (void*)0;
	}
	if (!S_ISDIR(file->vde->inode)){
		fclose((FILE *)file);
//		ERROR("Not a dir path=%s\n",path);
		return (void*)0;
	}

	if (!file->dirp){

		file->dirp		= malloc(sizeof(struct dir));
		KASSERT(file->dirp);
		dirp 			= (struct dir*)file->dirp;
		dirp->d_dirent		= malloc(sizeof(struct dirent));
		KASSERT(dirp->d_dirent);
		dirp->d_file		= file;
		dirp->d_off		= 0;
	}

	status = _ndsvfs_read_dirs(file->vde, &(dirp->vde_list));
	dirp->vde_head = dirp->vde_list;
	dirp->vde_list = NULL;
	if(status == HAL_FAILURE)
		return HAL_NULL;
	return dirp;
}

__attribute__((used))
int closedir(struct dir *dirp)
{
	NDSVFS_FILE *file = dirp->d_file;

	if (dirp == NULL)
		return -1;
	if (file == NULL)
		return -1;
	if (dirp->d_dirent != NULL)
		free(dirp->d_dirent);
	free(dirp);
	return fclose((FILE *)file);
}

__attribute__((used))
struct dirent *readdir(struct dir *dirp)
{
	/* this is the first time, becasue the vde_list is pointed to null */
	if (dirp->vde_list == NULL && dirp->vde_head != NULL) {
		strcpy(dirp->d_dirent->d_name, dirp->vde_head->name.utf_name);
		dirp->vde_list = NDS_LIST_ENTITY(dirp->vde_head->c_chain.next, NDSVFS_DENTRY, c_chain);
		return dirp->d_dirent;
	}
	/* this is not the first time. */
	else if (dirp->vde_list != dirp->vde_head) {
		strcpy(dirp->d_dirent->d_name, dirp->vde_list->name.utf_name);
		dirp->vde_list = NDS_LIST_ENTITY(dirp->vde_list->c_chain.next, NDSVFS_DENTRY, c_chain);
		return dirp->d_dirent;
	}
	else
		return NULL;
}

__attribute__((used))
int fstat(FILE* fd, struct stat *buf)
{
	NDSVFS_FILE *file = (NDSVFS_FILE *)fd;
        if (file == HAL_NULL)
                return -1;
    	return file->vde->sb->stat_file(file->vde, buf);
}
