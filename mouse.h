#ifndef __MOUSE_H
#define __MOUSE_H

#include "types.h"
#include "interrupts.h"
#include "port.h"

class MouseDriver : public InterruptHandler
{
public:
    MouseDriver(InterruptManager* manager);
    ~MouseDriver();
    virtual uint32_t HandleInterrupt(uint32_t esp);

private:
    Port8Bit dataport;
    Port8Bit commandport;

    uint8_t buffer[3];  
    uint8_t offset;  // 表示读取的是哪一个字节，初始值为 0
    uint8_t buttons;  // 标志按键的状态：按下状态 or 释放状态

    int8_t x, y;  // 坐标表示鼠标的位置，使用 int8_t 类型
};

#endif
