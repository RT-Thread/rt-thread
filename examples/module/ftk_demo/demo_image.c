#include "ftk.h"

#ifdef FTK_AS_PLUGIN
#include "ftk_app_demo.h"
FTK_HIDE int FTK_MAIN(int argc, char* argv[]);
FtkApp* ftk_app_demo_image_create()
{
	return ftk_app_demo_create(_("image"), ftk_main);
}
#else
#define FTK_HIDE extern
#endif /*FTK_AS_PLUGIN*/

FTK_HIDE int FTK_MAIN(int argc, char* argv[])
{
	FtkWidget* image = NULL;
	FtkWidget* win = NULL;
	char filename[FTK_MAX_PATH+1] = {0};
	FTK_INIT(argc, argv);
	
	win = ftk_app_window_create();

	ftk_snprintf(filename, FTK_MAX_PATH, "%s/earth.png", 
		ftk_config_get_test_data_dir(ftk_default_config()));

	image = ftk_image_create(win, 0, 0, ftk_widget_width(win)/2, ftk_widget_height(win)/2);
	ftk_image_set_image(image, 
		ftk_bitmap_factory_load(ftk_default_bitmap_factory(), filename));
	
	ftk_snprintf(filename, FTK_MAX_PATH, "%s/png_RGB_tRNS.png", 
		ftk_config_get_test_data_dir(ftk_default_config()));
	image = ftk_image_create(win, 0, 0, ftk_widget_width(win)/2, ftk_widget_height(win)/2);
	ftk_image_set_image(image, 
		ftk_bitmap_factory_load(ftk_default_bitmap_factory(), filename));
	ftk_widget_set_attr(image, FTK_ATTR_TRANSPARENT);

	ftk_snprintf(filename, FTK_MAX_PATH, "%s/Calculator.png", 
		ftk_config_get_test_data_dir(ftk_default_config()));
	image = ftk_image_create(win, ftk_widget_width(win)/2, 0, ftk_widget_width(win)/2, ftk_widget_height(win)/2);
	ftk_image_set_image(image, 
		ftk_bitmap_factory_load(ftk_default_bitmap_factory(), filename));
	ftk_widget_set_attr(image, FTK_ATTR_BG_TILE);

	ftk_snprintf(filename, FTK_MAX_PATH, "%s/t8.bmp", 
		ftk_config_get_test_data_dir(ftk_default_config()));
	image = ftk_image_create(win, 0, ftk_widget_height(win)/2, ftk_widget_width(win)/2, ftk_widget_height(win)/2);
	ftk_image_set_image(image, 
		ftk_bitmap_factory_load(ftk_default_bitmap_factory(), filename));
	ftk_widget_set_attr(image, FTK_ATTR_BG_CENTER);
	
	ftk_snprintf(filename, FTK_MAX_PATH,  "%s/jpeg1.jpg", 
		ftk_config_get_test_data_dir(ftk_default_config()));
	image = ftk_image_create(win, ftk_widget_width(win)/2, ftk_widget_height(win)/2, ftk_widget_width(win)/2, ftk_widget_height(win)/2);
	ftk_image_set_image(image, 
		ftk_bitmap_factory_load(ftk_default_bitmap_factory(), filename));
	ftk_widget_set_attr(image, FTK_ATTR_BG_TILE);

	ftk_widget_set_text(win, "image demo");
	ftk_widget_show_all(win, 1);
	
	FTK_QUIT_WHEN_WIDGET_CLOSE(win);

	FTK_RUN();

	return 0;
}
