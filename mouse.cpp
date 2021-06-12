#include "mouse.h"

MouseDriver::MouseDriver(InterruptManager* manager)
    : InterruptHandler(0x0C + manager->HardwareInterruptOffset(), manager),  // 0x0C：鼠标中断是 12 号
    dataport(0x60),  // 端口仍是 0x60，因为鼠标和键盘使用的是相同的控制器
    commandport(0x64),
    offset(0),
    buttons(0),
    x(40),
    y(12)
{
    uint16_t* VideoMemory = (uint16_t*)0xb8000;  // 获取内存地址
    // 往这个内存地址做一些操作，这样可以获取到内存对应的位置
    VideoMemory[y*80+x] = ((VideoMemory[y*80+x] & 0xf000) >> 4) |
                          ((VideoMemory[y*80+x] & 0x0f00) << 4) |
                          (VideoMemory[y*80+x] & 0x00ff);
    commandport.Write(0xa8);
    commandport.Write(0x20);
    uint8_t status = (dataport.Read() | 2) & ~0x20;
    commandport.Write(0x60);
    dataport.Write(status);
    commandport.Write(0xd4);
    dataport.Write(0xf4);
    dataport.Read();
}

MouseDriver::~MouseDriver() {}

void printf(const char*);
uint32_t MouseDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t status = commandport.Read();  // 首先从 commandport 里面读取鼠标的状态
    if (!(status & 0x20)) return esp;  // 如果不是鼠标则直接返回；0x20 对应着上面 0x20 相关状态值的操作
    
    return esp;
}
