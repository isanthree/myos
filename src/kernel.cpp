#include "common/types.h"
#include "gdt.h"
#include "hardwarecommunication/interrupts.h"
#include "drivers/keyboard.h"
#include "drivers/mouse.h"
#include "drivers/driver.h"

using namespace myos;
using namespace myos::common;
using namespace myos::drivers;
using namespace myos::hardwarecommunication;

// 获取显示器的物理地址
void printf(const char *str)
{
    static uint16_t *VideoMemory = (uint16_t *)0xb8000; // 改为static
    static uint8_t x = 0, y = 0;
    // 取出低16位，高位不取
    for (int i = 0; str[i]; i++)
    {
        switch (str[i])
        {
        case '\n':
            y++; // 换行
            x = 0;
            break;

        default:
            VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | str[i];
            x++;
            break;
        }

        // 显示器的像素为 80*25
        if (x >= 80) // 写满一行了
        {
            x = 0;
            y++;
        }

        if (y >= 25) // 写满屏了，清屏操作
        {
            for (y = 0; y < 25; y++) // 遍历每一行
            {
                for (x = 0; x < 80; x++) // 遍历每一列
                {
                    VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | ' '; // 和 ' '字符或一下即可清空
                }
            }
            x = 0, y = 0;
        }
    }
}

void printfHex(uint8_t key)
{
    char *foo = (char *)"00\n";
    const char *hex = "0123456789ABCDEF";
    foo[22] = hex[(key >> 4) & 0x0f];
    foo[23] = hex[key & 0x0f];
    printf((const char *)foo);
}

class PrintKeyboardEventHandler : public KeyboardEventHandler
{
public:
    void OnKeyDown(char c)
    {
        char *foo = (char *)" ";
        foo[0] = c;
        printf(foo);
    }
};

class MouseToConsole : public MouseEventHandler
{
public:
    MouseToConsole() : x(40), y(12) {}

    void OnActivate()
    {
        uint16_t *VideoMemory = (uint16_t *)0xb8000; // 获取内存地址
        // 往这个内存地址做一些操作，这样可以获取到鼠标对应的位置
        VideoMemory[y * 80 + x] = ((VideoMemory[y * 80 + x] & 0xf000) >> 4) |
                                  ((VideoMemory[y * 80 + x] & 0x0f00) << 4) |
                                  (VideoMemory[y * 80 + x] & 0x00ff);
    }

    // 重载方法
    void OnMouseMove(int8_t nx, int8_t ny)
    {
        uint16_t *VideoMemory = (uint16_t *)0xb8000; // 获取内存地址
        // 往这个内存地址做一些操作，这样可以获取到鼠标对应的位置
        VideoMemory[y * 80 + x] = ((VideoMemory[y * 80 + x] & 0xf000) >> 4) |
                                  ((VideoMemory[y * 80 + x] & 0x0f00) << 4) |
                                  (VideoMemory[y * 80 + x] & 0x00ff);
        // 鼠标往右移动：x 增大；鼠标往下移动：y 增大，但是 buffer[2] 是相反的，取一下反
        x += nx;
        if (x < 0)
            x = 0;
        else if (x >= 80)
            x = 79;

        y += ny;
        if (y < 0)
            y = 0;
        else if (y >= 25)
            y = 24;

        VideoMemory[y * 80 + x] = ((VideoMemory[y * 80 + x] & 0xf000) >> 4) |
                                  ((VideoMemory[y * 80 + x] & 0x0f00) << 4) |
                                  (VideoMemory[y * 80 + x] & 0x00ff);
    }

private:
    int8_t x, y;
};

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

// 调用 constructor 函数
extern "C" void callConstructors()
{
    for (constructor *i = &start_ctors; i != &end_ctors; i++)
    {
        (*i)();
    }
}

extern "C" void kernelMain(void *multiboot_structure, uint32_t magicnumber)
{
    printf("hello world!\n");
    printf("cpp\n");

    GlobalDescriptorTable gdt;
    InterruptManager interrupts(0x20, &gdt);

    DriverManager drvManager;

    PrintKeyboardEventHandler kbhandler;              // keyboard handler
    KeyBoardDriver keyboard(&interrupts, &kbhandler); // 中断开启前，keyboard 进行初始化
    drvManager.AddDriver(&keyboard);                  // 把 keyboard 放到 drvManager 里面

    MouseToConsole mousehandler;
    MouseDriver mouse(&interrupts, &mousehandler);
    drvManager.AddDriver(&mouse); // 把 mouse 放到 drvManager 里面

    drvManager.ActivateAll(); // 激活所有驱动

    interrupts.Activate(); // 开启中断

    while (1);
}
