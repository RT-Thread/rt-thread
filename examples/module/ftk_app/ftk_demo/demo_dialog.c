#include "ftk.h"

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_dialog_create()
{
	return ftk_app_demo_create(_("dialog"), ftk_main);
}
#else
#define FTK_HIDE extern
#endif /*FTK_AS_PLUGIN*/

static Ret button_quit_clicked(void* ctx, void* obj)
{
	if(ctx != NULL)
	{
		/*modal*/
		*(int*)ctx = ftk_widget_id(obj);
	}
	else
	{
		/*modal-less*/
		ftk_widget_unref(ftk_widget_toplevel(obj));
	}

	return RET_QUIT;
}

static Ret button_close_clicked(void* ctx, void* obj)
{
	ftk_widget_unref(ctx);

	return RET_OK;
}

static Ret button_dialog_clicked(void* ctx, void* obj)
{
	int id = 0;
	int width = 0;
	int height = 0;
	FtkWidget* label = NULL;
	FtkWidget* button = NULL;
	FtkWidget* dialog = NULL;
	FtkBitmap* icon = NULL;
	int modal = (int)ctx;
	
	ftk_logd("%s:%d begin\n", __func__, __LINE__);
	dialog = ftk_dialog_create(0, 40, 320, 240);
	
	icon = ftk_theme_load_image(ftk_default_theme(), "info-icon"FTK_STOCK_IMG_SUFFIX); 
	ftk_dialog_set_icon(dialog, icon);

	width = ftk_widget_width(dialog);
	height = ftk_widget_height(dialog);
	label = ftk_label_create(dialog, width/6, height/4, 5*width/6, 20);
	ftk_widget_set_text(label, "Are you sure to quit?");

	button = ftk_button_create(dialog, width/6, height/2, width/3, 50);
	ftk_widget_set_text(button, "yes");
	ftk_button_set_clicked_listener(button, button_quit_clicked, modal ? &id : NULL);
	
	button = ftk_button_create(dialog, width/2, height/2, width/3, 50);
	ftk_widget_set_text(button, "no");
	ftk_button_set_clicked_listener(button, button_quit_clicked, modal ? &id : NULL);
	ftk_window_set_focus(dialog, button);

	ftk_widget_set_text(dialog, modal ? "model dialog" : "normal dialog");
	ftk_widget_show_all(dialog, 1);

	if(modal)
	{
		assert(ftk_dialog_run(dialog) == id);
		ftk_widget_unref(dialog);
	}
	else
	{
		ftk_widget_show_all(dialog, 1);
	}
	ftk_logd("%s:%d end\n", __func__, __LINE__);

	return RET_OK;
}

FTK_HIDE int FTK_MAIN(int argc, char* argv[])
{
	int width = 0;
	int height = 0;
	FtkWidget* win = NULL;
	FtkWidget* button = NULL;
	
	FTK_INIT(argc, argv);

	win = ftk_app_window_create();
	ftk_window_set_animation_hint(win, "app_main_window");
	width = ftk_widget_width(win);
	height = ftk_widget_height(win);

	button = ftk_button_create(win, 0, height/6, width/3, 50);
	ftk_widget_set_text(button, "Normal");
	ftk_button_set_clicked_listener(button, button_dialog_clicked, NULL);

	button = ftk_button_create(win, 2*width/3, height/6, width/3, 50);
	ftk_widget_set_text(button, "Modal");
	ftk_button_set_clicked_listener(button, button_dialog_clicked, (void*)1);

	button = ftk_button_create(win, width/4, height/2, width/2, 60);
	ftk_widget_set_text(button, "quit");
	ftk_button_set_clicked_listener(button, button_close_clicked, win);

	ftk_widget_set_text(win, "demo dialog");
	ftk_widget_show_all(win, 1);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);

	FTK_RUN();

	return 0;
}

