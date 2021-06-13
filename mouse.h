#ifndef __MOUSE_H
#define __MOUSE_H

#include "types.h"
#include "interrupts.h"
#include "port.h"
#include "driver.h"

class MouseEventHandler
{
public:
    MouseEventHandler();
    ~MouseEventHandler();

    // 定义为 virtual，因为是通用的接口
    virtual void OnActivate();  // 激活函数，用于激活 mouse
    virtual void OnMouseDown(uint8_t button);  // 按下了哪个键
    virtual void OnMouseUp(uint8_t button);  // 弹起了哪个键
    virtual void OnMouseMove(int8_t x, int8_t y);  // 移动


};

class MouseDriver : public InterruptHandler, public Driver
{
public:
    MouseDriver(InterruptManager* manager, MouseEventHandler* handler);
    ~MouseDriver();
    virtual uint32_t HandleInterrupt(uint32_t esp);
    virtual void Activate();  // 定义抽象的激活函数

private:
    Port8Bit dataport;
    Port8Bit commandport;

    uint8_t buffer[3];  
    uint8_t offset;  // 表示读取的是哪一个字节，初始值为 0
    uint8_t buttons;  // 标志按键的状态：按下状态 or 释放状态

    int8_t x, y;  // 坐标表示鼠标的位置，使用 int8_t 类型

    MouseEventHandler* handler;
};

#endif
