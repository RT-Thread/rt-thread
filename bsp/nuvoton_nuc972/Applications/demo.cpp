/*
 * File      : demo.cpp
 * This file is part of RT-Thread RTOS
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/05/28     Urey         first implementation
 */

#include <rtthread.h>

#include <iostream>
using namespace std;
class Rectangle
{
public:
    Rectangle()
    {
    };
    Rectangle(int iLeftX, int iLeftY, int iRightX, int iRightY)
    {
        this->iLeftX = iLeftX;
        this->iLeftY = iLeftY;
        this->iRightX = iRightX;
        this->iRightY = iRightY;
    }
    int Area()
    {
        return (iRightX - iLeftX) * (iRightY - iLeftY);
    }
private:
    int iLeftX;
    int iLeftY;
    int iRightX;
    int iRightY;
};


int cpp_test(void)
{
    rt_kprintf("test cpp...\n");
    Rectangle r(1, 1, 2, 2);

    rt_kprintf("area = %d\n",r.Area());
}
extern "C" {

#include <finsh.h>
//extern int cpp_test(void);
MSH_CMD_EXPORT(cpp_test,test cpp function...);
}
