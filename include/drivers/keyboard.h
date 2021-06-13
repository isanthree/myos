#ifndef __MYOS__DRIVERS__KEYBOARD_H
#define __MYOS__DRIVERS__KEYBOARD_H

#include "common/types.h"
#include "hardwarecommunication/interrupts.h"
#include "hardwarecommunication/port.h"
#include "drivers/driver.h"

namespace myos
{
    namespace drivers
    {
        class KeyboardEventHandler
        {
        public:
            KeyboardEventHandler();
            ~KeyboardEventHandler();

            // 定义为 virtual，因为是通用的接口
            virtual void OnKeyDown(char); // 按下了哪个键
            virtual void OnKeyUp(char);   // 弹起了哪个键
        };

        // 定义一个类继承一些中断的处理函数
        class KeyBoardDriver : public myos::hardwarecommunication::InterruptHandler, public Driver
        {
        public:
            // 传入一个 InterruptManager，通过这个管理者，去处理一些中断程序
            KeyBoardDriver(myos::hardwarecommunication::InterruptManager *manager, KeyboardEventHandler *handler);
            ~KeyBoardDriver();
            virtual myos::common::uint32_t HandleInterrupt(myos::common::uint32_t esp);
            virtual void Activate(); // 定义抽象的激活函数

        private:
            myos::hardwarecommunication::Port8Bit dataport;
            myos::hardwarecommunication::Port8Bit commandport;
            KeyboardEventHandler *handler;
        };
    }
}

#endif
