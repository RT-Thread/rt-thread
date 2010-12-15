#include "ftk.h"
#include "ftk_animator_alpha.h"

static void create_ani_window(int type, int sync);

static Ret button_fast_clicked(void* ctx, void* obj)
{
	create_ani_window(1, 0);

	return RET_OK;
}

static Ret button_slow_clicked(void* ctx, void* obj)
{
	create_ani_window(0, 0);

	return RET_OK;
}

static Ret button_quit_clicked(void* ctx, void* obj)
{
	FtkWidget* win = ctx;
	ftk_widget_unref(win);
	ftk_logd("%s: close window %s\n", __func__, ftk_widget_get_text(win));

	return RET_OK;
}

static void create_ani_window(int type, int sync)
{
	FtkGc gc = {0};
	char filename[FTK_MAX_PATH+1] = {0};
	FtkWidget* win = ftk_app_window_create();
	FtkAnimator* ani = ftk_animator_alpha_create(1);
	
	gc.mask = FTK_GC_BITMAP;

	ftk_snprintf(filename, FTK_MAX_PATH, "%s/jpeg1.jpg", 
		ftk_config_get_test_data_dir(ftk_default_config()));
	gc.bitmap = ftk_bitmap_factory_load(ftk_default_bitmap_factory(), filename);
	ftk_widget_set_gc(win, FTK_WIDGET_NORMAL, &gc);
	ftk_gc_reset(&gc);

	ftk_animator_set_param(ani, 0, 0, 0xff, type ? 0x60 : 0x20, type ? 200 : 1000);
	ftk_animator_start(ani, win, 0);

	return;
}

static void create_app_window(void)
{
	char title[32] = {0};
	int width = 0;
	int height = 0;
	FtkWidget* win = ftk_app_window_create();
	FtkWidget* button = NULL;
	
	width = ftk_widget_width(win);
	height = ftk_widget_height(win);

	button = ftk_button_create(win, 5, height/6, width/2-5, 50);
	ftk_widget_set_text(button, "Fast");
	ftk_button_set_clicked_listener(button, button_fast_clicked, win);

	button = ftk_button_create(win, width/2, height/6, width/2-5, 50);
	ftk_widget_set_text(button, "Slow");
	ftk_button_set_clicked_listener(button, button_slow_clicked, win);


	button = ftk_button_create(win, width/4-2, height/6 + 180, width/2-5, 50);
	ftk_widget_set_text(button, "Quit");
	ftk_button_set_clicked_listener(button, button_quit_clicked, win);

	ftk_snprintf(title, sizeof(title), "Alpha Demo");
	ftk_widget_set_text(win, title);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);

	ftk_widget_show_all(win, 1);

	return;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_alpha_create()
{
	return ftk_app_demo_create(_("alpha"), ftk_main);
}
#else
#define FTK_HIDE extern
#endif /*FTK_AS_PLUGIN*/

FTK_HIDE int FTK_MAIN(int argc, char* argv[])
{
	FTK_INIT(argc, argv);
	
	create_app_window();

	FTK_RUN();

	return 0;
}

