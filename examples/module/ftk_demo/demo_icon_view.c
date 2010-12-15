#include "ftk.h"

#define IDC_TEST_BUTTON 1000
static Ret button_quit_clicked(void* ctx, void* obj)
{
	ftk_widget_unref(ctx);

	return RET_OK;
}

static int i = 0;
static Ret button_more_clicked(void* ctx, void* obj)
{
	int j = 0;
	FtkIconViewItem item;
	FtkWidget* icon_view = ftk_widget_lookup(ctx, 100);
	item.icon = ftk_theme_load_image(ftk_default_theme(), "flag-32.png");
	
	for(j=0; j < 4; j++)
	{
		char text[100] = {0};
		ftk_snprintf(text, sizeof(text), "%d", i);
		item.text = text;
		ftk_bitmap_ref(item.icon);
		item.user_data = (void*)i;
		ftk_icon_view_add(icon_view, &item);
		i+=1000;
	}
	ftk_bitmap_unref(item.icon);

	return RET_OK;
}

static Ret item_clicked(void* ctx, void* obj)
{
	FtkIconViewItem* item = obj;
	
	ftk_logd("%s: %s: user_data=%d\n", __func__, item->text, item->user_data);

	return RET_OK;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_icon_view_create()
{
	return ftk_app_demo_create(_("icon_view"), ftk_main);
}
#else
#define FTK_HIDE extern
#endif /*FTK_AS_PLUGIN*/

FTK_HIDE int FTK_MAIN(int argc, char* argv[])
{
	int width = 0;
	int height = 0;
	FtkWidget* win = NULL;
	FtkWidget* button = NULL;
	FtkWidget* icon_view = NULL;
	FtkIconViewItem item;
	FTK_INIT(argc, argv);
	
	win = ftk_app_window_create();
	width = ftk_widget_width(win);
	height = ftk_widget_height(win);

	button = ftk_button_create(win, 10, 0, width/3-10, 60);
	ftk_widget_set_text(button, "more");
	ftk_button_set_clicked_listener(button, button_more_clicked, win);
	ftk_window_set_focus(win, button);
	
	button = ftk_button_create(win, 2*width/3, 0, width/3-10, 60);
	ftk_widget_set_text(button, "quit");
	ftk_button_set_clicked_listener(button, button_quit_clicked, win);
	ftk_window_set_focus(win, button);

	item.icon = ftk_theme_load_image(ftk_default_theme(), "flag-32.png");
	icon_view = ftk_icon_view_create(win, 5, 70, width-10, height-80);
	ftk_widget_set_id(icon_view, 100);
	ftk_icon_view_set_clicked_listener(icon_view, item_clicked, win);
	for(; i < 4; i++)
	{
		char text[100] = {0};
		ftk_snprintf(text, sizeof(text), "%d", i);
		item.text = text;
		item.user_data = (void*)i;
		ftk_icon_view_add(icon_view, &item);
	}
	
	ftk_bitmap_unref(item.icon);
	ftk_widget_set_text(win, "icon view demo");
	ftk_widget_show_all(win, 1);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);

	FTK_RUN();

	return 0;
}

