#include "ftk.h"
#include "ftk_tab.h"

static Ret button_default_clicked(void* ctx, void* obj)
{
	printf("%s: button %s is clicked.\n", __func__, ftk_widget_get_text(obj));

	return RET_OK;
}

static Ret button_quit_clicked(void* ctx, void* obj)
{
	ftk_widget_unref(ctx);

	return RET_OK;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_tab_create()
{
	return ftk_app_demo_create(_("tab"), ftk_main);
}
#else
#define FTK_HIDE extern
#endif /*FTK_AS_PLUGIN*/

static void add_page(FtkWidget* tab, const char* text, FtkBitmap* bitmap)
{
	int width = 0;
	int height = 0;
	FtkWidget* page = NULL;
	FtkWidget* button = NULL;
	
	page = ftk_tab_add_page(tab, text, bitmap);
	width = ftk_widget_width(page);
	height = ftk_widget_height(page);

	button = ftk_button_create(page, 0, height/2-30, width/2, 60);
	ftk_widget_set_text(button, text); 
	ftk_widget_show(button, 1);
	ftk_button_set_clicked_listener(button, button_default_clicked, tab);
	
	button = ftk_button_create(page, width/2, height/2-30, width/2, 60);
	ftk_widget_set_text(button, text); 
	ftk_widget_show(button, 1);
	ftk_button_set_clicked_listener(button, button_default_clicked, tab);

	return;
}

FTK_HIDE int FTK_MAIN(int argc, char* argv[])
{
	int width = 0;
	int height = 0;
	FtkWidget* win = NULL;
	FtkWidget* tab = NULL;
	FtkWidget* button = NULL;
	FtkBitmap* bitmap = NULL;
	FTK_INIT(argc, argv);
	
	bitmap = ftk_theme_load_image(ftk_default_theme(), "mime_audio"FTK_STOCK_IMG_SUFFIX);
	win = ftk_app_window_create();
	width = ftk_widget_width(win);
	height = ftk_widget_height(win);

	tab = ftk_tab_create(win, 0, 0, width, height - 50);

	add_page(tab, "General", bitmap);
	add_page(tab, "Graphic", bitmap);
	add_page(tab, "Audio", bitmap);

	ftk_tab_set_active_page(tab, 0);
	
	button = ftk_button_create(win, width/4, height - 50, width/2, 50);
	ftk_widget_set_text(button, _("Quit")); 
	ftk_widget_show(button, 1);

	ftk_button_set_clicked_listener(button, button_quit_clicked, win);

	ftk_widget_show_all(win, 1);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);
	FTK_BITMAP_UNREF(bitmap);

	FTK_RUN();

	return 0;
}
