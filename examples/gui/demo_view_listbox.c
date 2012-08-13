/*
 * 程序清单：label控件演示
 *
 * 这个例子会在创建出的container上添加几个不同类型的label控件
 */
#include "demo_view.h"
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/listbox.h>

static rtgui_image_t *item_icon = RT_NULL;
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

static struct rtgui_listbox_item items[] =
{
    {"list #0", RT_NULL},
    {"list #1", RT_NULL},
    {"list #2", RT_NULL},
    {"list #3", RT_NULL},
};

static rt_bool_t on_items(struct rtgui_object *object, struct rtgui_event *event)
{
    rtgui_listbox_t *box;
    /* get listbox */
    box = RTGUI_LISTBOX(object);

    /* 打印当前的项 */
    rt_kprintf("current item: %d\n", box->current_item);

    return RT_TRUE;
}

/* 创建用于演示label控件的视图 */
rtgui_container_t *demo_view_listbox(void)
{
    rtgui_rect_t rect;
    rtgui_container_t *container;
    rtgui_label_t *label;
    rtgui_listbox_t *box;

    /* 先创建一个演示用的视图 */
    container = demo_view("ListBox Demo");

    if (item_icon == RT_NULL)
        item_icon = rtgui_image_create_from_mem("xpm",
                                                (const rt_uint8_t *)image_xpm, sizeof(image_xpm), RT_TRUE);
    items[1].image = item_icon;

    /* 获得视图的位置信息 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 -= 5;
    rect.y1 += 5;
    rect.y2 = rect.y1 + 20;
    /* 创建一个label控件 */
    label = rtgui_label_create("listbox: ");
    /* 设置label的位置 */
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    /* container是一个container控件，调用add_child方法添加这个label控件 */
    rtgui_container_add_child(container, RTGUI_WIDGET(label));

    rect.y1 = rect.y2 + 3;
    rect.y2 = 250;
    box = rtgui_listbox_create(items, sizeof(items) / sizeof(struct rtgui_listbox_item), &rect);
    rtgui_listbox_set_onitem(box, on_items);
    /* container是一个container控件，调用add_child方法添加这个listbox控件 */
    rtgui_container_add_child(container, RTGUI_WIDGET(box));

    return container;
}
