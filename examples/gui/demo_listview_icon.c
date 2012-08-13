/*
 * 程序清单：列表视图演示
 *
 * 这个例子会先创建出一个演示用的view，当点击上面的按钮时会按照模式显示的形式显示
 * 新的列表视图
 */
#include "demo_view.h"
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/list_view.h>

static struct rtgui_application *application = RT_NULL;
static rtgui_list_view_t *_view = RT_NULL;

/* 列表项的动作函数 */
static void listitem_action(rtgui_widget_t *widget, void *parameter)
{
    char label_text[32];
    rtgui_win_t *win;
    rtgui_label_t *label;
    rtgui_rect_t rect = {0, 0, 150, 80};
    int no = (int)parameter;

    rtgui_rect_moveto(&rect, 20, 50);

    /* 显示消息窗口 */
    win = rtgui_win_create(RTGUI_TOPLEVEL(application),
                           "窗口", &rect, RTGUI_WIN_STYLE_DEFAULT);

    rect.x1 += 20;
    rect.x2 -= 5;
    rect.y1 += 5;
    rect.y2 = rect.y1 + 20;

    /* 添加相应的标签 */
    rt_sprintf(label_text, "动作 %d", no);
    label = rtgui_label_create(label_text);

    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(label));

    /* 非模态显示窗口 */
    rtgui_win_show(win, RT_FALSE);
}

/* 返回功能的动作函数 */
static void return_action(rtgui_widget_t *widget, void *parameter)
{
    /* 退出模态显示 */
    rtgui_container_end_modal(RTGUI_CONTAINER(_view), RTGUI_MODAL_OK);
}

/* 列表项 */
#define ITEM_MAX    50
static struct rtgui_list_item *items = RT_NULL;
static rtgui_image_t *item_icon = RT_NULL;
static rtgui_image_t *exit_icon = RT_NULL;

static const char *image_xpm[] =
{
    "16 16 106 2",
    "  	c None",
    ". 	c #D0C83F",
    "+ 	c #D0C840",
    "@ 	c #D0C030",
    "# 	c #D0B820",
    "$ 	c #D0B020",
    "% 	c #D0B01F",
    "& 	c #5F571F",
    "* 	c #F0F0C0",
    "= 	c #FFF8D0",
    "- 	c #FFF8C0",
    "; 	c #FFF8B0",
    "> 	c #FFF8A0",
    ", 	c #F0E870",
    "' 	c #707030",
    ") 	c #4F87EF",
    "! 	c #4F78C0",
    "~ 	c #5088E0",
    "{ 	c #5078C0",
    "] 	c #C0D0F0",
    "^ 	c #FFF8E0",
    "/ 	c #FFF090",
    "( 	c #F0E070",
    "_ 	c #6F97D0",
    ": 	c #C0D8FE",
    "< 	c #80A8F0",
    "[ 	c #7088D0",
    "} 	c #B0D0FF",
    "| 	c #90B0F0",
    "1 	c #1040A0",
    "2 	c #F0F080",
    "3 	c #707040",
    "4 	c #7098F0",
    "5 	c #3068E0",
    "6 	c #A0B8F0",
    "7 	c #4070C0",
    "8 	c #002880",
    "9 	c #404040",
    "0 	c #505050",
    "a 	c #F0F090",
    "b 	c #F0E860",
    "c 	c #F0D860",
    "d 	c #807840",
    "e 	c #2F5FC0",
    "f 	c #1050D0",
    "g 	c #1048B0",
    "h 	c #002870",
    "i 	c #C0C080",
    "j 	c #C0C070",
    "k 	c #F0F070",
    "l 	c #F0E060",
    "m 	c #E0D050",
    "n 	c #00277F",
    "o 	c #00287F",
    "p 	c #1F3F6F",
    "q 	c #1048C0",
    "r 	c #0040B0",
    "s 	c #204080",
    "t 	c #FFF890",
    "u 	c #F0D850",
    "v 	c #E0C840",
    "w 	c #807040",
    "x 	c #A0B06F",
    "y 	c #204880",
    "z 	c #2048A0",
    "A 	c #90A8C0",
    "B 	c #FFF080",
    "C 	c #F0D050",
    "D 	c #C0A830",
    "E 	c #6F682F",
    "F 	c #F0F0A0",
    "G 	c #E0D060",
    "H 	c #B0A040",
    "I 	c #D0B840",
    "J 	c #E0C040",
    "K 	c #D0B030",
    "L 	c #706820",
    "M 	c #5F581F",
    "N 	c #CFBF3F",
    "O 	c #FFF0A0",
    "P 	c #A09830",
    "Q 	c #A08820",
    "R 	c #908030",
    "S 	c #807830",
    "T 	c #707020",
    "U 	c #605820",
    "V 	c #6F672F",
    "W 	c #D0C040",
    "X 	c #F0E880",
    "Y 	c #907820",
    "Z 	c #B09820",
    "` 	c #B09010",
    " .	c #B08820",
    "..	c #806820",
    "+.	c #5F5F1F",
    "@.	c #F0E080",
    "#.	c #B09020",
    "$.	c #C0B040",
    "%.	c #A09030",
    "&.	c #908020",
    "*.	c #606020",
    "=.	c #6F5F1F",
    "-.	c #9F982F",
    ";.	c #A0872F",
    ">.	c #6F681F",
    ",.	c #706020",
    "                                ",
    "          . + + + @ @ # # $ % & ",
    "          + * = = = = - ; > , ' ",
    "  ) !     ~ { ] ^ = - - > / ( ' ",
    "_ : < { [ } | 1 - ; > > / 2 ( 3 ",
    "{ 4 5 1 6 7 5 8 9 0 a / , b c d ",
    "e f g h 8 8 g h i j / k l c m d ",
    "  n o   p q r s t 2 , l c u v w ",
    "        x y z A B , l u C v D E ",
    "        @ F > t k G H I J K L M ",
    "      N @ O / 2 l P Q R S T U V ",
    "      W m 2 X l I Y Z `  ...+.  ",
    "      W @.l u I R #.Z Y U M     ",
    "    $.G I $.%.R &.Y *.& =.      ",
    "  -.;.>.,.L L ,.& M             ",
    "                                "
};

static const char *exit_xpm[] =
{
    "16 16 71 1",
    " 	c None",
    ".	c #CF673F",
    "+	c #D0673F",
    "@	c #C05F3F",
    "#	c #BF5F3F",
    "$	c #D0674F",
    "%	c #E07050",
    "&	c #F07850",
    "*	c #FF7040",
    "=	c #F06830",
    "-	c #E05830",
    ";	c #D05030",
    ">	c #B04F2F",
    ",	c #D06F4F",
    "'	c #F08060",
    ")	c #FF9070",
    "!	c #FF8860",
    "~	c #FF8050",
    "{	c #FF5820",
    "]	c #FF4810",
    "^	c #D04810",
    "/	c #B0482F",
    "(	c #FF9880",
    "_	c #FF6030",
    ":	c #F04000",
    "<	c #C04010",
    "[	c #A03F2F",
    "}	c #E06840",
    "|	c #FF9870",
    "1	c #FF7850",
    "2	c #FF6840",
    "3	c #F04010",
    "4	c #E03800",
    "5	c #A03820",
    "6	c #8F372F",
    "7	c #F06840",
    "8	c #FF8060",
    "9	c #FFFFFF",
    "0	c #FFF8F0",
    "a	c #FFF0F0",
    "b	c #FFE8E0",
    "c	c #FFD0C0",
    "d	c #E04010",
    "e	c #B03010",
    "f	c #7F2F1F",
    "g	c #FFD8D0",
    "h	c #FFC8C0",
    "i	c #C03000",
    "j	c #6F281F",
    "k	c #F04810",
    "l	c #FF6830",
    "m	c #FFE0D0",
    "n	c #F0C0B0",
    "o	c #D04010",
    "p	c #5F1F1F",
    "q	c #E04820",
    "r	c #FF4000",
    "s	c #FF5020",
    "t	c #FF5010",
    "u	c #D03800",
    "v	c #D03000",
    "w	c #B02800",
    "x	c #5F170F",
    "y	c #C05020",
    "z	c #F03800",
    "A	c #802010",
    "B	c #4F0F0F",
    "C	c #A02800",
    "D	c #C03810",
    "E	c #5F0F00",
    "F	c #A03810",
    "                ",
    "     .+@@@#     ",
    "    $%&*=-;>    ",
    "   ,')!~*{]^/   ",
    "  +&)()~*_]:<[  ",
    " .}~!||!12{3456 ",
    " +7899990abcdef ",
    " @{19990bgchdij ",
    " @kl0abmchcnoip ",
    " @qr]stt]3duvwx ",
    " #yz:::z44uvvAB ",
    "  >o4444uvvvCB  ",
    "   /DvvvvvvCE   ",
    "    [FeiiwAB    ",
    "     6fjpxB     ",
    "                "
};

/* 打开列表视图用的按钮触发函数 */
static void open_btn_onbutton(rtgui_widget_t *widget, struct rtgui_event *event)
{
    rtgui_rect_t rect;
    rt_uint32_t index;

    /* 获得顶层的application */
    application = RTGUI_APPLICATION(rtgui_widget_get_toplevel(widget));
    rtgui_widget_get_rect(RTGUI_WIDGET(application), &rect);

    /* 初始化图标列表 */
    if (items == RT_NULL)
    {
        char item_name[32];

        items = (struct rtgui_list_item *) rtgui_malloc((ITEM_MAX + 1) * sizeof(struct rtgui_list_item));
        for (index = 0; index < ITEM_MAX; index ++)
        {
            rt_snprintf(item_name, sizeof(item_name), "图标%d", index);
            items[index].action = listitem_action;
            items[index].image = item_icon;
            items[index].name = rt_strdup(item_name);
            items[index].parameter = (void *) index;
        }

        items[ITEM_MAX].action = return_action;
        items[ITEM_MAX].image = exit_icon;
        items[ITEM_MAX].name = "退出";
        items[ITEM_MAX].parameter = RT_NULL;
    }

    /* 创建一个列表视图， 项指定为items */
    _view = rtgui_list_view_create(items, ITEM_MAX + 1, &rect, RTGUI_LIST_VIEW_ICON);
    /* 在application中添加相应的视图 */
    rtgui_application_add_container(application, RTGUI_CONTAINER(_view));

    /* 模式显示视图 */
    rtgui_container_show(RTGUI_CONTAINER(_view), RT_TRUE);
    rtgui_container_destroy(RTGUI_CONTAINER(_view));

    _view = RT_NULL;
}

/* 创建用于演示列表视图的视图 */
rtgui_container_t *demo_listview_icon_view(struct rtgui_application *app)
{
    rtgui_rect_t rect;
    rtgui_container_t *view;
    rtgui_button_t *open_btn;

    view = demo_view(app, "图标视图演示");

    if (item_icon == RT_NULL)
        item_icon = rtgui_image_create_from_mem("xpm",
                                                (const rt_uint8_t *)image_xpm, sizeof(image_xpm), RT_TRUE);
    if (exit_icon == RT_NULL)
        exit_icon = rtgui_image_create_from_mem("xpm",
                                                (const rt_uint8_t *)exit_xpm, sizeof(exit_xpm), RT_TRUE);

    /* 添加动作按钮 */
    demo_view_get_rect(view, &rect);
    rect.x1 += 5;
    rect.x2 = rect.x1 + 80;
    rect.y1 += 30;
    rect.y2 = rect.y1 + 20;
    open_btn = rtgui_button_create("打开图标列表");
    rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(open_btn));
    rtgui_widget_set_rect(RTGUI_WIDGET(open_btn), &rect);
    rtgui_button_set_onbutton(open_btn, open_btn_onbutton);

    return view;
}
