#include "ftk_xul.h"
#include "ftk_expr.h"
#include "ftk_app_calc.h"

typedef struct _PrivInfo
{
	FtkBitmap* icon;
}PrivInfo;

#define IDC_ENTRY 100

static Ret ftk_calc_on_button_clicked(void* ctx, void* obj);

const char* ftk_translate_path(const char* path, char out_path[FTK_MAX_PATH+1])
{
	snprintf(out_path, FTK_MAX_PATH, "%s/%s", APP_DATA_DIR, path);
	if(access(out_path, R_OK) < 0)
	{
		snprintf(out_path, FTK_MAX_PATH, "%s/%s", APP_LOCAL_DATA_DIR, path);
	}
	ftk_logd("%s->%s\n", path, out_path);

	return out_path;
}

const char* buttons[] =
{
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	".",
	"+",
	"-",
	"*",
	"/",
	"(",
	")",
	"=",
	"<--",
	"Quit"
};

static FtkWidget* ftk_calc_create_window(void)
{
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	int row = 0;
	int col = 0;
	int small = 0;
	int xoffset = 0;
	int yoffset = 0;
	int width   = 0;
	int height  = 0;
	int v_margin  = 5;
	int h_margin  = 5;
	int item_width = 0;
	int item_height = 0;
	FtkGc gc = {0};
	FtkWidget* entry = NULL;
	FtkWidget* button = NULL;
	FtkBitmap* bitmap_normal = NULL;
	FtkBitmap* bitmap_active = NULL;
	FtkBitmap* bitmap_focus = NULL;
	char path[FTK_MAX_PATH+1] = {0};
	FtkWidget* win =  ftk_app_window_create();
	ftk_window_set_animation_hint(win, "app_main_window");
	width = ftk_widget_width(win);
	height = ftk_widget_height(win);
	entry = ftk_entry_create(win, 0, 0, width, 30);
	ftk_widget_set_id(entry, IDC_ENTRY);
	height -= ftk_widget_height(entry);

	row = width > height ? 4 : 5;
	col = width > height ? 5 : 4;

	item_width = width / col;
	item_height = height /row;
	small = (item_width < 60 || item_height < 60) ? 1 : 0;

	item_width = item_height = small ? 36 : 60;
	
	h_margin = width/col - item_width;
	h_margin = h_margin > 5 ? 5 : h_margin;

	v_margin = height/row - item_height;
	v_margin = v_margin > 5 ? 5 : v_margin;

	xoffset = (width - (h_margin + item_width) * col) >> 1;
	yoffset = (height - (v_margin + item_height) * row) >> 1;

	xoffset = xoffset < 0 ? 0 : xoffset;
	yoffset = yoffset < 0 ? 0 : yoffset;

	yoffset += ftk_widget_height(entry);
	gc.mask = FTK_GC_BITMAP;
	if(small)
	{
		bitmap_normal =  ftk_bitmap_factory_load(ftk_default_bitmap_factory(), ftk_translate_path("icons/button-small.png", path));
		bitmap_active =  ftk_bitmap_factory_load(ftk_default_bitmap_factory(), ftk_translate_path("icons/button-pressed-small.png", path));
		bitmap_focus =  ftk_bitmap_factory_load(ftk_default_bitmap_factory(), ftk_translate_path("icons/button-selected-small.png", path));
	}
	else
	{
		bitmap_normal =  ftk_bitmap_factory_load(ftk_default_bitmap_factory(), ftk_translate_path("icons/button.png", path));
		bitmap_active =  ftk_bitmap_factory_load(ftk_default_bitmap_factory(), ftk_translate_path("icons/button-pressed.png", path));
		bitmap_focus =  ftk_bitmap_factory_load(ftk_default_bitmap_factory(), ftk_translate_path("icons/button-selected.png", path));
	}

	for(i = 0; i < row; i++)
	{
		y = yoffset + i * (item_height + v_margin);
		for(j = 0; j < col; j++)
		{
			const char* text = buttons[i * col + j];
			if(text != NULL)
			{
				x = xoffset + j * (item_width + h_margin);
				button = ftk_button_create(win, x, y, item_width, item_height);
				ftk_widget_set_text(button, text);
				ftk_button_set_clicked_listener(button, ftk_calc_on_button_clicked, win);
				gc.bitmap = bitmap_normal;
				ftk_widget_set_gc(button, FTK_WIDGET_NORMAL, &gc);
				
				gc.bitmap = bitmap_focus;
				ftk_widget_set_gc(button, FTK_WIDGET_FOCUSED, &gc);
				
				gc.bitmap = bitmap_active;
				ftk_widget_set_gc(button, FTK_WIDGET_ACTIVE, &gc);
			}
		}
	}

	ftk_bitmap_unref(bitmap_normal);
	ftk_bitmap_unref(bitmap_active);
	ftk_bitmap_unref(bitmap_focus);

	return win;
}

static Ret ftk_calc_on_shutdown(void* ctx, void* obj)
{
	ftk_widget_unref(ctx);

	return RET_OK;
}

static Ret ftk_calc_on_prepare_options_menu(void* ctx, FtkWidget* menu_panel)
{
	FtkWidget* item = ftk_menu_item_create(menu_panel);
	ftk_widget_set_text(item, _("Quit"));
	ftk_menu_item_set_clicked_listener(item, ftk_calc_on_shutdown, ctx);
	ftk_widget_show(item, 1);

	return RET_OK;
}

static Ret ftk_calc_on_button_clicked(void* ctx, void* obj)
{
	FtkWidget* entry = ftk_widget_lookup(ctx, IDC_ENTRY);
	const char* text = ftk_widget_get_text(obj);
	return_val_if_fail(text != NULL && entry != NULL, RET_FAIL);
	
	if(text[0] == '=')
	{
		char buff[32] = {0};
		double val = ftk_expr_eval(ftk_entry_get_text(entry));
		ftk_snprintf(buff, sizeof(buff), "%lf", val);
		ftk_entry_set_text(entry, buff);
	}
	else if(text[0] == '<')
	{
		ftk_entry_set_text(entry, "");
	}
	else if(text[0] == 'Q' || strcmp(text, _("Quit")) == 0)
	{
		ftk_widget_unref(ctx);
	}
	else
	{
		ftk_entry_insert_text(entry, -1, text);
	}

	return RET_OK;
}

static FtkBitmap* ftk_app_calc_get_icon(FtkApp* thiz)
{
	DECL_PRIV(thiz, priv);
	const char* name="calc.png";
	char file_name[FTK_MAX_PATH + 1] = {0};
	return_val_if_fail(priv != NULL, NULL);
	
	if(priv->icon != NULL) return priv->icon;
	
	snprintf(file_name, FTK_MAX_PATH, "%s/icons/%s", APP_DATA_DIR, name);
	priv->icon = ftk_bitmap_factory_load(ftk_default_bitmap_factory(), file_name);
	if(priv->icon != NULL) return priv->icon;

	snprintf(file_name, FTK_MAX_PATH, "%s/icons/%s", APP_LOCAL_DATA_DIR, name);
	priv->icon = ftk_bitmap_factory_load(ftk_default_bitmap_factory(), file_name);

	return priv->icon;
}

static const char* ftk_app_calc_get_name(FtkApp* thiz)
{
	return _("Calculator");
}

static Ret ftk_app_calc_run(FtkApp* thiz, int argc, char* argv[])
{
	DECL_PRIV(thiz, priv);
	FtkWidget* win = NULL;
	return_val_if_fail(priv != NULL, RET_FAIL);

	win = ftk_calc_create_window();
	ftk_app_window_set_on_prepare_options_menu(win, ftk_calc_on_prepare_options_menu, win);
	ftk_widget_show_all(win, 1);

#ifdef HAS_MAIN
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);
#endif	

	return RET_OK;
}

static void ftk_app_calc_destroy(FtkApp* thiz)
{
	if(thiz != NULL)
	{
		DECL_PRIV(thiz, priv);
		ftk_bitmap_unref(priv->icon);
		FTK_FREE(thiz);
	}

	return;
}

FtkApp* ftk_app_calc_create(void)
{
	FtkApp* thiz = FTK_ZALLOC(sizeof(FtkApp) + sizeof(PrivInfo));

	if(thiz != NULL)
	{
		thiz->run  = ftk_app_calc_run;
		thiz->get_icon = ftk_app_calc_get_icon;
		thiz->get_name = ftk_app_calc_get_name;
		thiz->destroy = ftk_app_calc_destroy;
	}

	return thiz;
}

