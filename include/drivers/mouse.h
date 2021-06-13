#ifndef __MYOS__DRIVERS__MOUSE_H
#define __MYOS__DRIVERS__MOUSE_H

#include "common/types.h"
#include "hardwarecommunication/interrupts.h"
#include "hardwarecommunication/port.h"
#include "drivers/driver.h"

namespace myos
{
    namespace drivers
    {
        class MouseEventHandler
        {
        public:
            MouseEventHandler();
            ~MouseEventHandler();

            // 定义为 virtual，因为是通用的接口
            virtual void OnActivate();                    // 激活函数，用于激活 mouse
            virtual void OnMouseDown(myos::common::uint8_t button);     // 按下了哪个键
            virtual void OnMouseUp(myos::common::uint8_t button);       // 弹起了哪个键
            virtual void OnMouseMove(myos::common::int8_t x, myos::common::int8_t y); // 移动
        };

        class MouseDriver : public myos::hardwarecommunication::InterruptHandler, public Driver
        {
        public:
            MouseDriver(myos::hardwarecommunication::InterruptManager *manager, MouseEventHandler *handler);
            ~MouseDriver();
            virtual myos::common::uint32_t HandleInterrupt(myos::common::uint32_t esp);
            virtual void Activate(); // 定义抽象的激活函数

        private:
            myos::hardwarecommunication::Port8Bit dataport;
            myos::hardwarecommunication::Port8Bit commandport;

            myos::common::uint8_t buffer[3];
            myos::common::uint8_t offset;  // 表示读取的是哪一个字节，初始值为 0
            myos::common::uint8_t buttons; // 标志按键的状态：按下状态 or 释放状态

            myos::common::int8_t x, y; // 坐标表示鼠标的位置，使用 int8_t 类型

            MouseEventHandler *handler;
        };
    }
}

#endif
