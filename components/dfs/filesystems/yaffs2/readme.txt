how to use yaffs under rt-thread.

There are three steps.
1. get yaffs tarball from official repo.
   the repo of official repo is here.
     http://www.aleph1.co.uk/gitweb?p=yaffs2.git;a=summary
   then you should find the 2011-6-28's snapshot, download the tarball
     http://www.aleph1.co.uk/gitweb?p=yaffs2.git;a=snapshot;h=2df51cdb98e799c4d10b4cc7dd7e8858aa79e7d8;sf=tgz
  
   decompress the yaffs.tar.gz to rt-thread\components\dfs\filesystems\yaffs2\yaffs

2. patch yaffs.diff    
    open an terminal.
    (1) on windows
       open cmd command prompt, then use [cd] command to come current path
       for example 
         F:\Project\svn\rt-thread\components\dfs\filesystems\yaffs2>
       then type command 
         patch -p1 < yaffs.diff

       you will get some log information as followings 
         F:\Project\svn\rt-thread\components\dfs\filesystems\yaffs2>patch -p1 < yaffs.diff
         patching file `dfs_yaffs2.c'
         patching file `yaffs/direct/yaffs_list.h'
         patching file `yaffs/direct/yaffs_nandif.c'
         patching file `yaffs/direct/ydirectenv.h'
         patching file `yaffs/direct/yportenv.h'
         patching file `yaffs_nandcfg.c'
         patching file `yaffs_osglue.c'

       now you can delete yaffs.diff
       there is another patch file, as the name shows, it is to fix compile
       warning, so it is not necessary. If you want, you can use the
       following command.
         patch -p1 < fixwarning.diff

    (2) on linux
       Help yourself. Since you have use linux as your os, I believe in you. 

3.add nand driver and compile 
    In order to use yaffs, you should provide a nand driver which is needed
    by yaffs. There is an example file in rt-thread\components\dfs\filesystems\uffs\nand.
    you should modify yaffs_nandcfg.c according to your nand driver.
 then you can use scons or IDE like MDK or IAR to compile.

 enjoy !
