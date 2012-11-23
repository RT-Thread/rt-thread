#ifndef __BLOCK_PANEL_H__
#define __BLOCK_PANEL_H__
#include <rtgui/widgets/panel.h>

DECLARE_CLASS_TYPE(block_panel);

/** Gets the type of a block panel */
#define BLOCK_PANEL_TYPE       		(RTGUI_TYPE(block_panel))
/** Casts the object to an block panel */
#define BLOCK_PANEL(obj)       		(RTGUI_OBJECT_CAST((obj), BLOCK_PANEL_TYPE, block_panel_t))
/** Checks if the object is an block panel */
#define RTGUI_IS_BLOCK_PANEL(obj)	(RTGUI_OBJECT_CHECK_TYPE((obj), BLOCK_PANEL_TYPE))

/*
 * the block panel widget
 */
struct block_panel
{
	struct rtgui_panel parent;

	int angle_y;
};
typedef struct block_panel block_panel_t;

struct block_panel *block_panel_create(int angle_y, struct rtgui_rect *rect);
void block_panel_destroy(block_panel_t* panel);

rt_bool_t block_panel_event_handler(struct rtgui_object *object, struct rtgui_event* event);
void block_panel_get_client_extent(struct block_panel *panel, struct rtgui_rect *rect);

#endif

