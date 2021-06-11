#include "keyboard.h"

KeyBoardDriver::KeyBoardDriver(InterruptManager* manager)
    : InterruptHandler(0x01 + manager->HardwareInterruptOffset(), manager),  // keyboard 控制器对应 0x21
    dataport(0x60),
    commandport(0x64)
{
    while (commandport.Read() & 0x1)
    {
        dataport.Read();
    }
    commandport.Write(0xae);  // 0xae 是激活键盘
    commandport.Write(0x20);  // 键盘激活之后，读取 0x20
    uint8_t status = (dataport.Read() | 1) & ~0x10;  // 或上 1 开启键盘中断；&：把 Bit4 置零
    commandport.Write(0x60);  
    dataport.Write(status);
    dataport.Write(0xf4);  
}

KeyBoardDriver::~KeyBoardDriver() {}

void printf(const char*);
uint32_t KeyBoardDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t key = dataport.Read();
    char* foo = (char*)"\nUNHANDLED INTERRUPT 0x00\n";
    const char* hex = "0123456789ABCDEF";
    foo[22] = hex[(key >> 4) & 0x0f];
    foo[23] = hex[key & 0x0f];
    printf((const char*)foo);

    return esp;
}