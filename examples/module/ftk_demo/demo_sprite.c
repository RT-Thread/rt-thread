#include "ftk.h"

static Ret button_quit_clicked(void* ctx, void* obj)
{
	ftk_widget_unref(ctx);
	return RET_OK;
}

Ret on_move(void* ctx, void* obj)
{
	ftk_logd("%s: %d %d\n", __func__, ftk_sprite_get_x(obj), ftk_sprite_get_y(obj));

	return RET_OK;
}

Ret move_cursor(void* ctx, void* obj)
{
	FtkEvent* event = obj;

	if(event->type == FTK_EVT_MOUSE_MOVE)
	{
		ftk_sprite_move(ctx, event->u.mouse.x, event->u.mouse.y);
	}

	return RET_OK;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_sprite_create()
{
	return ftk_app_demo_create(_("sprite"), ftk_main);
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
	FtkSprite* sprite = NULL;
	FtkBitmap* icon = NULL;

	FTK_INIT(argc, argv);
	
	win = ftk_app_window_create();
	width = ftk_widget_width(win);
	height = ftk_widget_height(win);
	
	button = ftk_button_create(win, width/4, height/2, width/2, 60);
	ftk_widget_set_text(button, "quit");
	ftk_button_set_clicked_listener(button, button_quit_clicked, win);
	ftk_window_set_focus(win, button);

	ftk_widget_set_text(win, "sprite demo");
	ftk_widget_show_all(win, 1);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);

#if 0
	/*multi sprite still has some problems.*/
	sprite = ftk_sprite_create();
	icon=ftk_theme_load_image(ftk_default_theme(), "flag-32"FTK_STOCK_IMG_SUFFIX);
	ftk_sprite_set_icon(sprite, icon);
	ftk_sprite_move(sprite, width/2, 0);
	ftk_sprite_set_move_listener(sprite, on_move, NULL);
	ftk_sprite_show(sprite, 1);
	ftk_main_loop_add_source(ftk_default_main_loop(), ftk_source_timer_create(200, timer, sprite));
#endif

	sprite = ftk_sprite_create();
	icon=ftk_theme_load_image(ftk_default_theme(), "cursor"FTK_STOCK_IMG_SUFFIX);
	ftk_sprite_set_icon(sprite, icon);
	ftk_sprite_show(sprite, 1);
	ftk_wnd_manager_add_global_listener(ftk_default_wnd_manager(), move_cursor, sprite);

	FTK_RUN();


	return 0;
}

