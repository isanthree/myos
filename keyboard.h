#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "types.h"
#include "interrupts.h"
#include "port.h"

// 定义一个类继承一些中断的处理函数
class KeyBoardDriver : public InterruptHandler
{
public:
    // 传入一个 InterruptManager，通过这个管理者，去处理一些中断程序
    KeyBoardDriver(InterruptManager* manager);
    ~KeyBoardDriver();
    virtual uint32_t HandleInterrupt(uint32_t esp);

private:
    Port8Bit dataport;
    Port8Bit commandport;
};

#endif
