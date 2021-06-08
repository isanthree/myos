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

void kernelMain(void* multiboot_structure, unsigned int magicnumber)
{
    printf("hello world!");
    while(1);
}