/*

+------------------------------------------------------------------------------

| Project   : Device Filesystem

+------------------------------------------------------------------------------

| Copyright 2004, 2005  www.fayfayspace.org.

| All rights reserved.

|------------------------------------------------------------------------------

| File      : dfs_init.h, the initilization definitions of Device FileSystem
|------------------------------------------------------------------------------
| Chang Logs:

| Date           Author       Notes

| 2005-02-21     ffxz         The first version.
+------------------------------------------------------------------------------
*/

#ifndef __DFS_INIT_H__
#define __DFS_INIT_H__

#ifdef __cplusplus
extern "C" {
#endif

/* initilization of dfs */
void dfs_init(void);

/* initilization of dfs with filesystem server */
void dfs_server_init(void);

#ifdef __cplusplus
}
#endif

#endif
