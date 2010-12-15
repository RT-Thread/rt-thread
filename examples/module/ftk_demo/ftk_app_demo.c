#include "ftk_app_demo.h"

typedef struct _PrivInfo
{
	char* name; 
	FtkMain ftk_main;
	FtkBitmap* icon;
}PrivInfo;

static FtkBitmap* ftk_app_demo_get_icon(FtkApp* thiz)
{
	DECL_PRIV(thiz, priv);
	return_val_if_fail(priv != NULL, NULL);

	return priv->icon;
}

static const char* ftk_app_demo_get_name(FtkApp* thiz)
{
	DECL_PRIV(thiz, priv);
	return_val_if_fail(priv != NULL, NULL);

	return priv->name;
}

static Ret ftk_app_demo_run(FtkApp* thiz, int argc, char* argv[])
{
	DECL_PRIV(thiz, priv);
	return_val_if_fail(priv != NULL, RET_FAIL);

	priv->ftk_main(argc, argv);

	return RET_OK;
}

static void ftk_app_demo_destroy(FtkApp* thiz)
{
	if(thiz != NULL)
	{
		DECL_PRIV(thiz, priv);
		FTK_FREE(priv->name);
		ftk_bitmap_unref(priv->icon);
		FTK_FREE(thiz);
	}

	return;
}

FtkApp* ftk_app_demo_create(const char* name, FtkMain ftk_main)
{
	FtkApp* thiz = FTK_ZALLOC(sizeof(FtkApp) + sizeof(PrivInfo));

	if(thiz != NULL)
	{
		DECL_PRIV(thiz, priv);

		priv->ftk_main = ftk_main;
		priv->name = ftk_strdup(name);
		priv->icon = ftk_theme_load_image(ftk_default_theme(), "flag-32"FTK_STOCK_IMG_SUFFIX);
		thiz->get_icon = ftk_app_demo_get_icon;
		thiz->get_name = ftk_app_demo_get_name;
		thiz->run = ftk_app_demo_run;
		thiz->destroy = ftk_app_demo_destroy;
	}

	return thiz;
}
