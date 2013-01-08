/*
 * File      : tetris_modal.c
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-08-14     Yi.Qiu       first version
 */
 
#include <rtthread.h>
#include <stdlib.h> 
#include "tetris.h"

struct rt_tetris
{
	rt_uint32_t	width;			/* the width of the tetris */
	rt_uint32_t	height;			/* the height of the tetris */
	rt_uint16_t* 	panel;			/* the panel of the tetris */
	rt_uint32_t* 	brick;			/* the current brick of the tetris */
	rt_uint32_t* 	next_brick;		/* the next brick  of the tetris */
	rt_tetris_view_t* view;			/* the view on which the tetris show */
	rt_uint32_t 	level;			/* game level */
	rt_uint32_t 	lines;			/* released lines count */
	rt_uint32_t 	score;			/* total scores statistic */
	rt_bool_t 		status;			/* game status, pause or runing */
};

static const rt_uint32_t g_brick[][4] = 
{
	{23,7,8,22},
	{23,7,8,24},
	{24,7,8,25},
	{8,7,9,23},	
	{8,7,9,24},
	{8,7,9,25},
	{7,6,8,9},
};

static rt_err_t rt_tetris_append_brick(rt_tetris_t* thiz, rt_uint32_t brick[]);
static rt_err_t rt_tetris_delete_brick(rt_tetris_t* thiz, rt_uint32_t brick[]);
static rt_err_t rt_tetris_release_lines(rt_tetris_t* thiz, rt_uint32_t brick[]);
static rt_err_t rt_tetris_is_reach_top(rt_tetris_t* thiz, rt_uint32_t brick[]);
static rt_err_t rt_tetris_update_brick(rt_tetris_t* thiz);

/**
 * this function create a tetris instance
 *
 * @param width the width of tetris.
 * @param height the height of tetris.
 *
 * @return the tetris instance
 */
rt_tetris_t* rt_tetris_create(rt_uint32_t width, rt_uint32_t height)
{
	int index;

	rt_tetris_t* thiz = (rt_tetris_t*)rt_malloc(sizeof(rt_tetris_t));
	RT_ASSERT(thiz != RT_NULL);

	thiz->height 	= height;
	thiz->width		= width;
	thiz->panel 	= rt_malloc(thiz->height * sizeof(rt_uint32_t));
	rt_memset(thiz->panel, 0, thiz->height * sizeof(rt_uint32_t));	

	thiz->brick		= (rt_uint32_t*)rt_malloc(4 * sizeof(rt_uint32_t));
	index 			= (int)(7.0 * rand()/(RAND_MAX + 1.0)); 
	rt_memcpy(thiz->brick, g_brick[index], 4 * sizeof(rt_uint32_t));

	thiz->next_brick= (rt_uint32_t*)rt_malloc(4 * sizeof(rt_uint32_t));
	index 			= (int)(7.0 * rand()/(RAND_MAX + 1.0)); 
	rt_memcpy(thiz->next_brick, g_brick[index], 4 * sizeof(rt_uint32_t));

	thiz->view		= RT_NULL;
	thiz->level		= 0;
	thiz->lines 	= 0;
	thiz->score		= 0;
	thiz->status	= RT_FALSE;

	return thiz;
}

/**
 * this function destory a tetris instance
 *
 * @param thiz the tetris instance.
 *
 * @return RT_EOK
 */
rt_err_t rt_tetris_destory(rt_tetris_t* thiz)
{
	RT_ASSERT(thiz->panel && thiz->brick && thiz->next_brick);

	rt_free(thiz->panel);
	rt_free(thiz->brick);
	rt_free(thiz->next_brick);
	rt_free(thiz);

	return RT_EOK;
}

/**
 * this function start tetris game
 *
 * @param thiz the tetris instance.
 *
 * @return RT_EOK
 */
rt_err_t rt_tetris_start(rt_tetris_t* thiz)
{
	RT_ASSERT(thiz != RT_NULL);

	/* update next brick on view */
	thiz->view->update_next_brick(thiz->view, thiz);

	/* update level */
	thiz->view->update_level(thiz->view, thiz);

	/* update lines and score */
	thiz->view->update_score_and_lines(thiz->view, thiz);

	thiz->status = RT_TRUE;

	return RT_EOK;
}

/**
 * this function pause tetris game
 *
 * @param thiz the tetris instance.
 *
 * @return RT_EOK
 */
rt_err_t rt_tetris_pause(rt_tetris_t* thiz)
{
	RT_ASSERT(thiz != RT_NULL);

	thiz->status = RT_FALSE;

	return RT_EOK;
}

/**
 * this function get width of a tetris instance
 *
 * @param thiz the tetris instance.
 *
 * @return the width of the tetris instance
 */
rt_uint32_t rt_tetris_width(rt_tetris_t* thiz)
{
	RT_ASSERT(thiz != RT_NULL);

	return thiz->width;
}

/**
 * this function get next brick of a tetris instance
 *
 * @param thiz the tetris instance.
 *
 * @return the next brick of the tetris instance
 */
rt_uint32_t* rt_tetris_next_brick(rt_tetris_t* thiz)
{
	RT_ASSERT(thiz != RT_NULL);

	return thiz->next_brick;
}

/**
 * this function get level of the tetris instance
 *
 * @param thiz the tetris instance.
 *
 * @return the level of the tetris instance
 */
rt_uint32_t rt_tetris_level(rt_tetris_t* thiz)
{
	RT_ASSERT(thiz != RT_NULL);

	return thiz->level;
}

/**
 * this function get released lines of the tetris instance
 *
 * @param thiz the tetris instance.
 *
 * @return the released lines of the tetris instance
 */
rt_uint32_t rt_tetris_lines(rt_tetris_t* thiz)
{
	RT_ASSERT(thiz != RT_NULL);

	return thiz->lines;
}

/**
 * this function get score of the tetris instance
 *
 * @param thiz the tetris instance.
 *
 * @return the score of the tetris instance
 */
rt_uint32_t rt_tetris_score(rt_tetris_t* thiz)
{
	RT_ASSERT(thiz != RT_NULL);

	return thiz->score;
}

/**
 * this function get height of a tetris instance
 *
 * @param thiz the tetris instance.
 *
 * @return the height of the tetris instance
 */
rt_uint32_t rt_tetris_height(rt_tetris_t* thiz)
{
	RT_ASSERT(thiz != RT_NULL);	

	return thiz->height;
}

/**
 * this function get status of a tetris instance
 *
 * @param thiz the tetris instance.
 *
 * @return the status of the tetris instance
 */
rt_bool_t rt_tetris_status(rt_tetris_t* thiz)
{
	RT_ASSERT(thiz != RT_NULL);	

	return thiz->status;
}

/**
 * this function makes current brick move down
 *
 * @param thiz the tetris instance.
 *
 * @return RT_EOK on success, -RT_ERROR on fail
 */
rt_err_t rt_tetris_down(rt_tetris_t* thiz)
{
	int i;

	RT_ASSERT(thiz != RT_NULL);	

	if(thiz->status == RT_FALSE) return -RT_ERROR;

	/* delete the brick from tetris panel */
	rt_tetris_delete_brick(thiz, thiz->brick);

	for(i=0; i<4; i++)
	{
		/* check collision and bottom*/
		if((thiz->brick[i] >= thiz->width * (thiz->height - 1))
			|| rt_tetris_check_collision(thiz, thiz->brick[i] + thiz->width) == RT_EOK)
		{
			/* restore the deleted brick */
			rt_tetris_append_brick(thiz, thiz->brick);

			if(rt_tetris_is_reach_top(thiz, thiz->brick) == RT_EOK)
			{
				rt_memset(thiz->panel, 0xff, thiz->height * sizeof(rt_uint32_t));				

				/* update view */
				thiz->view->update(thiz->view, thiz);

				/* game over */
				return -RT_ETIMEOUT;
			}

			if(rt_tetris_release_lines(thiz, thiz->brick) == RT_EOK) 
			{
				/* update view */
				thiz->view->update(thiz->view, thiz);
			}

			rt_tetris_update_brick(thiz);
			return -RT_ERROR;			
		}
	}	

	for(i=0; i<4; i++)
	{	
		/* increase one line */
		thiz->brick[i] += thiz->width;
	}		

	/* append the brick to tetris panel */
	rt_tetris_append_brick(thiz, thiz->brick);

	/* update view */
	thiz->view->update(thiz->view, thiz);

	return RT_EOK;
}

/**
 * this function makes current brick move left
 *
 * @param thiz the tetris instance.
 *
 * @return RT_EOK on success, -RT_ERROR on fail
 */
rt_err_t rt_tetris_left(rt_tetris_t* thiz)
{
	int i;
	RT_ASSERT(thiz != RT_NULL);	

	if(thiz->status == RT_FALSE) return -RT_ERROR;

	/* delete the brick from tetris panel */
	rt_tetris_delete_brick(thiz, thiz->brick);

	for(i=0; i<4; i++)
	{
		/* check left board */
		if((thiz->brick[i] % thiz->width) == 0)
		{	
			/* restore the deleted brick */
			rt_tetris_append_brick(thiz, thiz->brick);
			return -RT_ERROR;
		}

		if(rt_tetris_check_collision(thiz, thiz->brick[i] - 1) == RT_EOK)
		{	
			/* restore the deleted brick */
			rt_tetris_append_brick(thiz, thiz->brick);
			return -RT_ERROR;
		}
	}	
	
	for(i=0; i<4; i++)
	{	
		/* move one step to left */
		thiz->brick[i] --;;
	}		

	/* append the brick to tetris panel */
	rt_tetris_append_brick(thiz, thiz->brick);

	/* update view */
	thiz->view->update(thiz->view, thiz);

	return RT_EOK;
}

/**
 * this function makes current brick move right
 *
 * @param thiz the tetris instance.
 *
 * @return RT_EOK on success, -RT_ERROR on fail
 */
rt_err_t rt_tetris_right(rt_tetris_t* thiz)
{
	int i;
	RT_ASSERT(thiz != RT_NULL);	

	if(thiz->status == RT_FALSE) return -RT_ERROR;

	/* delete the brick from tetris panel */
	rt_tetris_delete_brick(thiz, thiz->brick);

	for(i=0; i<4; i++)
	{
		/* check left board */
		if(((thiz->brick[i] + 1) % thiz->width) == 0)
		{	
			/* restore the deleted brick */
			rt_tetris_append_brick(thiz, thiz->brick);
			return -RT_ERROR;
		}

		/* check collision */
		if(rt_tetris_check_collision(thiz, thiz->brick[i] + 1) == RT_EOK)
		{	
			/* restore the deleted brick */
			rt_tetris_append_brick(thiz, thiz->brick);
			return -RT_ERROR;
		}
	}	
	
	for(i=0; i<4; i++)
	{	
		/* move one step to right */
		thiz->brick[i] ++;;
	}		

	/* append the brick to tetris panel */
	rt_tetris_append_brick(thiz, thiz->brick);

	/* update view */
	thiz->view->update(thiz->view, thiz);

	return RT_EOK;
}

/**
 * this function makes current brick drop quickly
 *
 * @param thiz the tetris instance.
 *
 * @return RT_EOK on success, -RT_ERROR on fail
 */
rt_err_t rt_tetris_drop(rt_tetris_t* thiz)
{
	rt_err_t ret;
	RT_ASSERT(thiz != RT_NULL);

	if(thiz->status == RT_FALSE) return -RT_ETIMEOUT;

	/* move down until blocked */
	while((ret = rt_tetris_down(thiz)) == RT_EOK);

	return ret;
}

/**
 * this function makes current brick do rotation
 *
 * @param thiz the tetris instance.
 *
 * @return RT_EOK on success, -RT_ERROR on fail
 */
rt_err_t rt_tetris_rotate(rt_tetris_t* thiz, rt_bool_t direction)
{
	int i;
	rt_uint32_t tmp[4];
	RT_ASSERT(thiz != RT_NULL);	

	if(thiz->status == RT_FALSE) return -RT_ERROR;

	rt_tetris_delete_brick(thiz, thiz->brick);

	tmp[0] = thiz->brick[0];
	for(i=1; i<4; i++)
	{
		int diff = thiz->brick[0] - thiz->brick[i];
		if(diff == 1)
		{
			tmp[i] = thiz->brick[0] - thiz->width;
		}
		else if(diff == -1)
		{
			tmp[i] = thiz->brick[0] + thiz->width;
		}
		else if(diff == 2)
		{
			tmp[i] = thiz->brick[0] - 2 * thiz->width;
		}
		else if(diff == -2)
		{
			tmp[i] = thiz->brick[0] + 2 * thiz->width;
		}
		else if(diff == thiz->width - 1)
		{
			tmp[i] = thiz->brick[0] + thiz->width + 1;
		}
		else if(diff == 1 - thiz->width)
		{
			tmp[i] = thiz->brick[0] - thiz->width - 1;
		}
		else if(diff == thiz->width)
		{
			if((thiz->brick[0] + 1) % thiz->width == 0) 
			{
				/* restore the deleted brick */
				rt_tetris_append_brick(thiz, thiz->brick);				
				return -RT_ERROR;
			}
			else tmp[i] = thiz->brick[0] + 1;
		}
		else if(diff == -1 * (thiz->width))
		{
			if(thiz->brick[0] % thiz->width == 0)
			{	
				/* restore the deleted brick */
				rt_tetris_append_brick(thiz, thiz->brick);			
				return -RT_ERROR;
			}
			else tmp[i] = thiz->brick[0] - 1;
		}
		else if(diff == thiz->width + 1)
		{
			tmp[i] = thiz->brick[0] - thiz->width + 1;
		}
		else if(diff == -1 - thiz->width)
		{
			tmp[i] = thiz->brick[0] + thiz->width - 1;
		}
		else if(diff == 2 * thiz->width)
		{
			if((thiz->brick[0] % thiz->width) >= (thiz->width - 2)) 
			{
				/* restore the deleted brick */
				rt_tetris_append_brick(thiz, thiz->brick);			
				return -RT_ERROR;
			}
			else tmp[i] = thiz->brick[0] + 2;
		}
		else if(diff == -2 * thiz->width)
		{
			if((thiz->brick[0] % thiz->width) < 2) 
			{
				/* restore the deleted brick */
				rt_tetris_append_brick(thiz, thiz->brick);			
				return -RT_ERROR;
			}
			else tmp[i] = thiz->brick[0] - 2;
		}
		
		if(tmp[i] > (thiz->height) * thiz->width) 
		{
			/* restore the deleted brick */
			rt_tetris_append_brick(thiz, thiz->brick);
			return -RT_ERROR;		
		}

		if(rt_tetris_check_collision(thiz, tmp[i]) == RT_EOK)
		{
			/* restore the deleted brick */
			rt_tetris_append_brick(thiz, thiz->brick);
			return -RT_ERROR;		
		}
	}

	/* do roration */
	for(i=0; i<4; i++)
	{
		thiz->brick[i] = tmp[i];
	}

	/* append the brick to tetris panel */
	rt_tetris_append_brick(thiz, thiz->brick);

	/* update view */
	thiz->view->update(thiz->view, thiz);

	return RT_EOK;
}

/**
 * this function add a view to the tetris
 *
 * @param thiz the tetris instance.
 * @param view the view instance.
 *
 * @return RT_EOK on success, -RT_ERROR on fail
 */
rt_err_t rt_tetris_add_view(rt_tetris_t* thiz, rt_tetris_view_t* view)
{
	RT_ASSERT(thiz != RT_NULL);

	/* Only suppurt single view now */
	thiz->view = view;

	return RT_EOK;
}

/**
 * this function delete a view from the tetris
 *
 * @param thiz the tetris instance.
 * @param view the view instance.
 *
 * @return RT_EOK on success, -RT_ERROR on fail
 */

rt_err_t rt_tetris_delete_view(rt_tetris_t* thiz, rt_tetris_view_t* view)
{
	RT_ASSERT(thiz != RT_NULL);

	thiz->view = RT_NULL;

	return RT_EOK;
}

/**
 * this function used to check collision
 *
 * @param thiz the tetris instance.
 * @param block the block to be checked.
 *
 * @return RT_EOK on collision, -RT_ERROR on not collision
 */
rt_err_t rt_tetris_check_collision(rt_tetris_t* thiz, rt_uint32_t block)
{
	RT_ASSERT(thiz != RT_NULL);
	RT_ASSERT(block < thiz->height * thiz->width);

	if((thiz->panel[block/thiz->width] & (1 << (block % thiz->width)))
		== (1 << (block % thiz->width)))
	{
		return RT_EOK;
	}
	else
	{
		return -RT_ERROR;
	}
}

static rt_err_t rt_tetris_update_brick(rt_tetris_t* thiz)
{
	int index;

	RT_ASSERT(thiz != RT_NULL);

	index = (int)(7.0 * rand()/(RAND_MAX + 1.0)); 

	rt_memcpy(thiz->brick, thiz->next_brick, 4 * sizeof(rt_uint32_t));
	rt_memcpy(thiz->next_brick, g_brick[index], 4 * sizeof(rt_uint32_t));

	/* update next brick on view */
	thiz->view->update_next_brick(thiz->view, thiz);
		
	return RT_EOK;
}

static rt_err_t rt_tetris_append_brick(rt_tetris_t* thiz, rt_uint32_t brick[])
{
	int i;

	RT_ASSERT(thiz != RT_NULL);
	RT_ASSERT(brick != RT_NULL);

	for(i=0; i<4; i++)
	{
		int y = brick[i]/thiz->width;
		int x = brick[i]%thiz->width;

		thiz->panel[y] |= (1<<x);
	}

	return RT_EOK;
}

static rt_err_t rt_tetris_delete_brick(rt_tetris_t* thiz, rt_uint32_t brick[])
{
	int i;

	RT_ASSERT(thiz != RT_NULL);
	RT_ASSERT(brick != RT_NULL);

	for(i=0; i<4; i++)
	{
		int y = brick[i]/thiz->width;
		int x = brick[i]%thiz->width;

		thiz->panel[y] &= ~(1<<x);
	}

	return RT_EOK;
}

static rt_err_t rt_tetris_is_reach_top(rt_tetris_t* thiz, rt_uint32_t brick[])
{
	int i;

	RT_ASSERT(thiz != RT_NULL);
	RT_ASSERT(brick != RT_NULL);

	for(i=0; i<4; i++)	
	{
		if(brick[i] / thiz->width == 0)
			return RT_EOK;
	}

	return -RT_ERROR;
}

static rt_err_t rt_tetris_release_lines(rt_tetris_t* thiz, rt_uint32_t brick[])
{
	int i, j, check_line = 0;
	rt_bool_t line_released = -RT_ERROR;

	RT_ASSERT(thiz != RT_NULL);
	RT_ASSERT(brick != RT_NULL);

	for(i=0; i<4; i++)
	{
		/* choose a line */
		check_line = brick[i]/thiz->width;	
		if((thiz->panel[check_line]) == ((1 << thiz->width) - 1))
		{
			for(j=check_line; j>0; j--)
			{
				thiz->panel[j] = thiz->panel[j-1];
			}
			
			/* clear the first line */
			thiz->panel[0] = 0;
			
			for(j=i+1; j<4; j++)
			{
				if(brick[j] < brick[i])
				{
					brick[j] += thiz->width;
				}
			}
			
			thiz->lines++;
			thiz->score += 100;
			line_released = RT_EOK;				
		}
	}

	if(line_released == RT_EOK)
	{
		/* update view */
		thiz->view->update_score_and_lines(thiz->view, thiz);
		return RT_EOK;
	}
	else
	{
		return -RT_ERROR;
	}
}

