#include "types.h"
#include "gdt.h"

// 获取显示器的物理地址
void printf(char* str)
{
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;  // 改为static
    static uint8_t x = 0, y = 0;
    // 取出低16位，高位不取
    for(int i=0; str[i]; i++)
    {
        switch (str[i])
        {
        case '\n':
            y++;  // 换行
            x = 0;
            break;
        
        default:
            VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
            x++;
            break;
        }

        // 显示器的像素为 80*25
        if (x>=80)  // 写满一行了
        {
            x = 0;
            y++;
        }

        if (y >= 25)  // 写满屏了，清屏操作
        {
            for(y=0; y<25; y++)  // 遍历每一行
            {
                for(x=0; x<80; x++)  // 遍历每一列
                {
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';  // 和 ' '字符或一下即可清空
                }
            }
            x = 0, y = 0;
        }

    }
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

// 调用 constructor 函数
extern "C" void callConstructors()
{
    for(constructor* i=&start_ctors; i!=&end_ctors; i++)
    {
        (*i)();
    }
}

extern "C" void kernelMain(void* multiboot_structure, uint32_t magicnumber)
{
    printf((char*)"hello world!\n");
    printf((char*)"cpp");

    GlobalDescriptorTable gdt;
    while(1);
}