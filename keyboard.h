#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "types.h"
#include "interrupts.h"
#include "port.h"
#include "driver.h"

class KeyboardEventHandler
{
public:
    KeyboardEventHandler();
    ~KeyboardEventHandler();

    // 定义为 virtual，因为是通用的接口
    virtual void OnKeyDown(char);  // 按下了哪个键
    virtual void OnKeyUp(char);  // 弹起了哪个键
};

// 定义一个类继承一些中断的处理函数
class KeyBoardDriver : public InterruptHandler, public Driver
{
public:
    // 传入一个 InterruptManager，通过这个管理者，去处理一些中断程序
    KeyBoardDriver(InterruptManager* manager, KeyboardEventHandler* handler);
    ~KeyBoardDriver();
    virtual uint32_t HandleInterrupt(uint32_t esp);
    virtual void Activate();  // 定义抽象的激活函数

private:
    Port8Bit dataport;
    Port8Bit commandport;
    KeyboardEventHandler* handler;
};

#endif
