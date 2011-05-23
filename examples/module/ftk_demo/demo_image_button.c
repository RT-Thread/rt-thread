#include "ftk.h"

const char* pngs[] = 
{
	"/Camera.png",
	"/Notes.png",
	"/RSS.png",
	"/Calculator.png",
	"/Twitter.png",
	"/Clock.png",
	"/Games.png",
	"/Youtube.png",
	"/AIM.png",
	"/LastFm.png",
	"/IP.png",
	"/Acrobat.png",
	"/Settings.png",
	"/App",
	"/Customize.png",
	"/Skype.png",
	"/Linkedin.png",
	"/Calender.png",
	"/Call.png",
	"/Install.png",
	"/Facebook.png",
	"/iPod.png",
	"/Chat.png",
	"/WLM.png",
	"/Flickr.png",
	"/Photos.png",
	"/Stock.png",
	"/Delicious.png",
	"/Maps.png",
	"/iTunes.png",
	"/Memory.png",
	"/Weather.png",
	"/Wordpress.png",
	"/iradio.png",
	"/Safari.png",
	"/Google.png",
	"/Yahoo.png",
	"/VLC.png",
	"/Sms.png",
	"/Mail.png",
	NULL
};

static Ret button_clicked(void* ctx, void* obj)
{
	ftk_widget_unref(ctx);

	return RET_OK;
}

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_image_button_create()
{
	return ftk_app_demo_create(_("image_button"), ftk_main);
}
#else
#define FTK_HIDE extern
#endif /*FTK_AS_PLUGIN*/

FTK_HIDE int FTK_MAIN(int argc, char* argv[])
{
	int i = 0;
	int j = 0;
	int width = 0;
	int height = 0;
	char filename[FTK_MAX_PATH] = {0};
	FtkGc gc = {0};
	FtkWidget* win = NULL;
	FtkWidget* button = NULL;
	FTK_INIT(argc, argv);

	gc.mask = FTK_GC_BITMAP;
	win = ftk_app_window_create();
	ftk_window_set_animation_hint(win, "app_main_window");
	width = ftk_widget_width(win);
	height = ftk_widget_height(win);
	for(i = 0; i < height/80; i++)
	{
		for(j = 0; j < width/80; j++)
		{
			ftk_snprintf(filename, sizeof(filename), "%s%s", 
				ftk_config_get_test_data_dir(ftk_default_config()), pngs[i + 2]);
			gc.bitmap = ftk_bitmap_factory_load(ftk_default_bitmap_factory(), filename);
			button = ftk_button_create(win, j * 80, i * 80, ftk_bitmap_width(gc.bitmap), ftk_bitmap_height(gc.bitmap));
			if(i == 0)
			{
				ftk_widget_unset_attr(button, FTK_ATTR_TRANSPARENT);
			}
			ftk_widget_set_gc(button, FTK_WIDGET_NORMAL, &gc);
			ftk_bitmap_unref(gc.bitmap);

			ftk_snprintf(filename, sizeof(filename), "%s%s", 
				ftk_config_get_test_data_dir(ftk_default_config()), pngs[1]);
			gc.bitmap = ftk_bitmap_factory_load(ftk_default_bitmap_factory(), filename);
			ftk_widget_set_gc(button, FTK_WIDGET_FOCUSED, &gc);
			ftk_bitmap_unref(gc.bitmap);

			ftk_snprintf(filename, sizeof(filename), "%s%s", 
				ftk_config_get_test_data_dir(ftk_default_config()), pngs[0]);
			gc.bitmap = ftk_bitmap_factory_load(ftk_default_bitmap_factory(), filename);
			ftk_widget_set_gc(button, FTK_WIDGET_ACTIVE, &gc);
			ftk_bitmap_unref(gc.bitmap);

			if(i == 0 && j == 0)
			{
				ftk_button_set_clicked_listener(button, button_clicked, win);
				ftk_widget_set_text(button, "Quit");
			}
		}
	}
	ftk_widget_set_text(win, "image button demo");
	ftk_widget_show_all(win, 1);
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);

	FTK_RUN();

	return 0;
}
