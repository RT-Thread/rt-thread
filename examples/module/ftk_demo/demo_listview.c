#include "ftk.h"

#include "ftk_list_view.h"
#include "ftk_list_render_default.h"
#include "ftk_list_model_default.h"

#define IDC_TEST_BUTTON 1000
static int g_index = 0;
static FtkBitmap*  left_icon = NULL;
static FtkBitmap* right_icon = NULL;

static Ret button_quit_clicked(void* ctx, void* obj)
{
	ftk_widget_unref(ctx);

	return RET_OK;
}

static Ret button_more_clicked(void* ctx, void* obj)
{
	int i = 0;
	char text[32] = {0};
	FtkListItemInfo info = {0};
	FtkListModel* model = ctx;

	for(i = 0; i < 4; i++)
	{
		g_index++;
		ftk_snprintf(text, sizeof(text), "item%04d", g_index);
		info.text = (text);
		info.left_icon = left_icon;
		info.right_icon = right_icon;
		info.type = g_index%4;
		ftk_list_model_add(model, &info);
	}

	return RET_OK;
}

Ret on_item_clicked(void* ctx, void* list)
{
	FtkListItemInfo* info = NULL;
	FtkListModel* model = ftk_list_view_get_model(list);
	int i = ftk_list_view_get_selected(list);

	ftk_list_model_get_data(model, i, (void**)&info);
	if(info != NULL)
	{
		info->state = !info->state;
	}
	ftk_logd("%s: %d/%d\n", __func__, 
		ftk_list_view_get_selected(list),
		ftk_list_model_get_total(model));

	return RET_OK;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_listview_create()
{
	return ftk_app_demo_create(_("listview"), ftk_main);
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
	FtkWidget* list = NULL;
	FtkListModel* model = NULL;
	FtkListRender* render = NULL;
	FtkListItemInfo info = {0};
	char filename[FTK_MAX_PATH+1] = {0};
	FTK_INIT(argc, argv);
	
	win = ftk_app_window_create();
	width = ftk_widget_width(win);
	height = ftk_widget_height(win);
	
	list = ftk_list_view_create(win, 10, 5, width - 20, 3 * height/4-5);
	ftk_list_view_set_clicked_listener(list, on_item_clicked, NULL);

	model = ftk_list_model_default_create(10);
	render = ftk_list_render_default_create();
	ftk_snprintf(filename, FTK_MAX_PATH, "%s/alarm/%s",
		ftk_config_get_test_data_dir(ftk_default_config()), FTK_STOCK_IMG_SUFFIX);
	left_icon = ftk_bitmap_factory_load(ftk_default_bitmap_factory(), filename);
	ftk_snprintf(filename, FTK_MAX_PATH, "%s/search/%s",  
	ftk_config_get_test_data_dir(ftk_default_config()), FTK_STOCK_IMG_SUFFIX);
	right_icon = ftk_bitmap_factory_load(ftk_default_bitmap_factory(), filename);

	g_index = 0;
	for(g_index = 0; g_index < 4; g_index++)
	{
		info.text = "滚动文字:Only those who attempt the absurd can achieve the impossible.";
		info.left_icon = left_icon;
		info.right_icon = right_icon;
		info.type = g_index%4;
		ftk_list_model_add(model, &info);
	}

	ftk_list_render_default_set_marquee_attr(render, FTK_MARQUEE_AUTO | FTK_MARQUEE_RIGHT2LEFT | FTK_MARQUEE_FOREVER);
	ftk_list_view_init(list, model, render, 40);
	ftk_list_model_unref(model);

	button = ftk_button_create(win, width/4, 3 * height/4 + 5, width/4, 60);
	ftk_widget_set_text(button, "more");
	ftk_button_set_clicked_listener(button, button_more_clicked, model);

	button = ftk_button_create(win, width/2, 3 * height/4 + 5, width/4, 60);
	ftk_widget_set_text(button, "quit");
	ftk_button_set_clicked_listener(button, button_quit_clicked, win);
	ftk_window_set_focus(win, button);

	ftk_widget_set_text(win, "list view demo");
	ftk_widget_show_all(win, 1);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);

	FTK_RUN();

	return 0;
}

