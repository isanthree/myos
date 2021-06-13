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
    
}

MouseDriver::~MouseDriver() {}

void MouseDriver::Activate()
{
    uint16_t* VideoMemory = (uint16_t*)0xb8000;  // 获取内存地址
    // 往这个内存地址做一些操作，这样可以获取到鼠标对应的位置
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

void printf(const char*);
uint32_t MouseDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t status = commandport.Read();  // 首先从 commandport 里面读取鼠标的状态
    if (!(status & 0x20)) return esp;  // 如果不是鼠标则直接返回；0x20 对应着上面 0x20 相关状态值的操作
    
    buffer[offset] = dataport.Read();  // 从 buffer 里面读取数据
    offset = (offset + 1) % 3;  // 然后 offset 此时需要往后偏移一位

    if (offset == 0)  // 如果 offset==0，说明 x,y 被操纵过了
    {
        uint16_t* VideoMemory = (uint16_t*)0xb8000;  // 获取内存地址
        // 往这个内存地址做一些操作，这样可以获取到鼠标对应的位置
        VideoMemory[y*80+x] = ((VideoMemory[y*80+x] & 0xf000) >> 4) |
                              ((VideoMemory[y*80+x] & 0x0f00) << 4) |
                              (VideoMemory[y*80+x] & 0x00ff);
        // 鼠标往右移动：x 增大；鼠标往下移动：y 增大，但是 buffer[2] 是相反的，取一下反
        x += buffer[1];
        if (x < 0) x = 0;
        else if (x >= 80) x = 79;

        y -= buffer[2];
        if (y < 0) y = 0;
        else if (y >= 25) y = 24;

        VideoMemory[y*80+x] = ((VideoMemory[y*80+x] & 0xf000) >> 4) |
                              ((VideoMemory[y*80+x] & 0x0f00) << 4) |
                              (VideoMemory[y*80+x] & 0x00ff);

        // 实现按键按下变白的功能
        for(uint8_t i=0; i<3; i++)
        {
            if ((buffer[0] & (1 << i)) != (buttons & (1 << i)))
            {
                VideoMemory[y*80+x] = ((VideoMemory[y*80+x] & 0xf000) >> 4) |
                              ((VideoMemory[y*80+x] & 0x0f00) << 4) |
                              (VideoMemory[y*80+x] & 0x00ff);
            }
        }
        buttons = buffer[0];
    }

    return esp;
}
