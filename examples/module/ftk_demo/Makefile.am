include $(abs_top_srcdir)/src/rules.mk

lib_LTLIBRARIES=libftk_demos.la

noinst_PROGRAMS=demo_label demo_button demo_image demo_image_button demo_dialog demo_multi_win \
	demo_menu demo_entry demo_expand demo_zoom demo_progress_bar demo_check_button demo_wait_box \
	demo_scroll_bar demo_sprite demo_xul demo_transparent demo_listview demo_hello \
	demo_fullscreen demo_icon_view demo_text_view demo_msgbox demo_popup demo_alpha \
	demo_combo_box demo_ime demo_statusbar demo_file_browser demo_tab

LOCAL_CFLAGS=-I$(abs_top_srcdir)/apps/common
libftk_demos_la_SOURCES=demo_button.c demo_alpha.c demo_label.c demo_image.c \
	demo_image_button.c demo_dialog.c demo_multi_win.c demo_menu.c demo_entry.c \
	demo_expand.c demo_zoom.c demo_progress_bar.c demo_check_button.c demo_wait_box.c \
	demo_scroll_bar.c demo_sprite.c demo_xul.c demo_transparent.c demo_listview.c \
	demo_fullscreen.c demo_icon_view.c demo_text_view.c demo_msgbox.c demo_popup.c \
	demo_combo_box.c demo_ime.c demo_statusbar.c demo_file_browser.c ftk_app_demo.c \
	demo_hello.c demo_tab.c

libftk_demos_la_LDFLAGS=$(MYLDFLAGS)
libftk_demos_la_CFLAGS=$(LOCAL_CFLAGS) -DFTK_AS_PLUGIN

if ENABLE_CAIRO
noinst_PROGRAMS+=demo_cairo
demo_cairo_SOURCES=demo_cairo.c
demo_cairo_LDFLAGS=$(MYLDFLAGS)

libftk_demos_la_SOURCES += demo_cairo.c

endif

if ENABLE_FRIBIDI
noinst_PROGRAMS+=demo_bidi
demo_bidi_SOURCES=demo_bidi.c
demo_bidi_LDFLAGS=$(MYLDFLAGS)

libftk_demos_la_SOURCES += demo_bidi.c
endif

demo_tab_SOURCES=demo_tab.c
demo_tab_LDFLAGS=$(MYLDFLAGS)

demo_file_browser_SOURCES=demo_file_browser.c
demo_file_browser_LDFLAGS=$(MYLDFLAGS)

demo_statusbar_SOURCES=demo_statusbar.c
demo_statusbar_LDFLAGS=$(MYLDFLAGS)

demo_ime_SOURCES=demo_ime.c
demo_ime_LDFLAGS=$(MYLDFLAGS)

demo_combo_box_SOURCES=demo_combo_box.c
demo_combo_box_LDFLAGS=$(MYLDFLAGS)

demo_alpha_SOURCES=demo_alpha.c
demo_alpha_LDFLAGS=$(MYLDFLAGS)

demo_zoom_SOURCES=demo_zoom.c
demo_zoom_LDFLAGS=$(MYLDFLAGS)

demo_popup_SOURCES=demo_popup.c
demo_popup_LDFLAGS=$(MYLDFLAGS)

demo_msgbox_SOURCES=demo_msgbox.c
demo_msgbox_LDFLAGS=$(MYLDFLAGS)

demo_text_view_SOURCES=demo_text_view.c
demo_text_view_LDFLAGS=$(MYLDFLAGS)

demo_icon_view_SOURCES=demo_icon_view.c
demo_icon_view_LDFLAGS=$(MYLDFLAGS)

demo_fullscreen_SOURCES=demo_fullscreen.c
demo_fullscreen_LDFLAGS=$(MYLDFLAGS)

demo_hello_SOURCES=demo_hello.c
demo_hello_LDFLAGS=$(MYLDFLAGS)

demo_listview_SOURCES=demo_listview.c
demo_listview_LDFLAGS=$(MYLDFLAGS)

demo_transparent_SOURCES=demo_transparent.c
demo_transparent_LDFLAGS=$(MYLDFLAGS)

demo_xul_SOURCES=demo_xul.c
demo_xul_LDFLAGS=$(MYLDFLAGS)

demo_sprite_SOURCES=demo_sprite.c
demo_sprite_LDFLAGS=$(MYLDFLAGS)

demo_scroll_bar_SOURCES=demo_scroll_bar.c
demo_scroll_bar_LDFLAGS=$(MYLDFLAGS)

demo_wait_box_SOURCES=demo_wait_box.c
demo_wait_box_LDFLAGS=$(MYLDFLAGS)

demo_check_button_SOURCES=demo_check_button.c
demo_check_button_LDFLAGS=$(MYLDFLAGS)

demo_progress_bar_SOURCES=demo_progress_bar.c
demo_progress_bar_LDFLAGS=$(MYLDFLAGS)

demo_expand_SOURCES=demo_expand.c
demo_expand_LDFLAGS=$(MYLDFLAGS)

demo_label_SOURCES=demo_label.c
demo_label_LDFLAGS=$(MYLDFLAGS)

demo_button_SOURCES=demo_button.c
demo_button_LDFLAGS=$(MYLDFLAGS)

demo_image_SOURCES=demo_image.c
demo_image_LDFLAGS=$(MYLDFLAGS)

demo_image_button_SOURCES=demo_image_button.c
demo_image_button_LDFLAGS=$(MYLDFLAGS)

demo_dialog_SOURCES=demo_dialog.c
demo_dialog_LDFLAGS=$(MYLDFLAGS)

demo_multi_win_SOURCES=demo_multi_win.c
demo_multi_win_LDFLAGS=$(MYLDFLAGS)

demo_menu_SOURCES=demo_menu.c
demo_menu_LDFLAGS=$(MYLDFLAGS)

demo_entry_SOURCES=demo_entry.c
demo_entry_LDFLAGS=$(MYLDFLAGS)

desktopdir=$(datadir)/ftk/base/apps
desktop_DATA=demos.desktop

iconsdir=$(datadir)/ftk/demos/icons
icons_DATA=demo.png

EXTRA_DIST=demo.png test_util.c t1.xul  t2.xul  t3.xul  t4.xul  t5.xul  t6.xul  t7.xul demos.desktop \
	ftk_app_demo.h 

