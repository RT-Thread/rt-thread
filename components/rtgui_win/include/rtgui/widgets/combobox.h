#ifndef __RTGUI_COMBO_H__
#define __RTGUI_COMBO_H__

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/textbox.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/view.h>
#include <rtgui/widgets/listbox.h>

#define RTGUI_COMBOBOX_HEIGHT				24
#define RTGUI_COMBOBOX_BUTTON_WIDTH			16

#define RTGUI_COMBO_STYLE_DOWNARROW_UP		0x01
#define RTGUI_COMBO_STYLE_DOWNARROW_DOWN	0x02

typedef	struct rtgui_combo	rtgui_combo_t;

/** Gets the type of a textbox */
#define RTGUI_COMBOBOX_TYPE       (rtgui_combo_type_get())
/** Casts the object to a rtgui_textbox_t */
#define RTGUI_COMBOBOX(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_COMBOBOX_TYPE, rtgui_combo_t))
/** Checks if the object is a rtgui_textbox_t */
#define RTGUI_IS_COMBOBOX(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_COMBOBOX_TYPE))

typedef struct rtgui_combo_item
{
	char	*name;
}rtgui_combo_item_t;

struct rtgui_combo
{
	rtgui_container_t parent;

	/* widget private data */
	rt_uint32_t style;

	rtgui_textbox_t *tbox;
	rtgui_listbox_t *lbox;

	/* call back */
	void (*on_selected) (PVOID wdt, rtgui_event_t* event);
	rt_uint32_t (*get_count)(rtgui_combo_t* box);
	void (*add_string)(rtgui_combo_t* box,char* string);
};


rtgui_type_t *rtgui_combo_type_get(void);
rtgui_combo_t* rtgui_combo_create(PVOID parent,const char* text,int left,int top,int w,int h);
void rtgui_combo_destroy(rtgui_combo_t* cbo);

void rtgui_combo_set_onitem(rtgui_combo_t* cbo, rtgui_event_handler_ptr func);
rt_bool_t rtgui_combo_event_handler(PVOID wdt, rtgui_event_t* event);
rt_bool_t rtgui_combo_onitem(PVOID wdt, rtgui_event_t* event);
void rtgui_combo_set_items(rtgui_combo_t* cbo, rtgui_listbox_item_t* items, rt_uint32_t count);

rt_uint32_t rtgui_combo_get_select(rtgui_combo_t* cbo);
char* rtgui_combo_get_string(rtgui_combo_t* cbo);

#endif

