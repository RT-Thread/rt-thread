#ifndef __DEMO_VIEW_H__
#define __DEMO_VIEW_H__

#include <rtgui/widgets/view.h>

rtgui_view_t* demo_view_create(rtgui_view_t* parent_view, const char* title);

rtgui_view_t* demo_gui_benchmark(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_dc_buffer(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_animation(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_buffer_animation(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_window(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_label(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_button(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_checkbox(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_progressbar(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_scrollbar(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_radiobox(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_textbox(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_listbox(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_menu(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_listctrl(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_listbox(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_combobox(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_slider(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_image(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_fnview(rtgui_view_t* parent_view);
rtgui_view_t* demo_gui_rttab(rtgui_view_t* parent_view);

#endif

