// 获取显示器的物理地址
void printf(char* str)
{
    unsigned short* VideoMemory = (unsigned short*)0xb8000;  
    // 取出低16位，高位不取
    for(int i=0; str[i]; i++)
    {
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
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

extern "C" void kernelMain(void* multiboot_structure, unsigned int magicnumber)
{
    printf((char*)"hello world!");
    while(1);
}