/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#ifndef __BOARD_INFO_H__
#define __BOARD_INFO_H__

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 * #include section
 *	add #include here if any
 ***************************************************************************/

/****************************************************************************
 * #define section
 *	add constant #define here if any
 ***************************************************************************/

/****************************************************************************
 * ADT section
 *	add Abstract Data Type definition here
 ***************************************************************************/

typedef int (*probe_p)(void *);
typedef int (*exit_p)(void *);

struct fh_board_ops {
	//void *ops_data;
	probe_p probe;
	probe_p exit;
};

struct fh_board_info {
	char *name;
	void *data;
	struct fh_board_ops *ops;

};

/****************************************************************************
 *  extern variable declaration section
 ***************************************************************************/

int fh_board_info_init(void);
struct fh_board_info *fh_board_info_register(char *info_name, void *data);
int fh_board_driver_register(char *info_name, struct fh_board_ops *ops);
void fh_print_all_board_info(void);
void fh_free_all_info(void);
/****************************************************************************
 *  section
 *	add function prototype here if any
 ***************************************************************************/

#ifdef __cplusplus
}
#endif

#endif
