#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "types.h"
#include "port.h"
#include "gdt.h"

class InterruptManager
{
public:
    InterruptManager(uint16_t hardwareInterruptOffset, GlobalDescriptorTable* gdt);
    ~InterruptManager();

    // 写一个方法，让 CPU 开启中断
    void Activate();  // 实现放在构造函数下面

protected:
    // 中断门描述符
    struct GateDescriptor
    {
        uint16_t handleAddressLowBits;
        uint16_t gdt_codeSegmentSelector;
        uint8_t reserved;  // 保留
        uint8_t access;  // 访问控制
        uint16_t handleAddressHighBits;
    } __attribute__((packed));

    static GateDescriptor interruptDescriptorTable[256];

    // https://cdn.jsdelivr.net/gh/isanthree/blog-gallery/pic/20210610010504.png
    // 实现 IDRT 寄存器，用来定位 IDT 表的位置
    struct InterruptDescriptorTablePointer
    {
        uint16_t size;
        uint32_t base;
    } __attribute__((packed));

    // 定义中断的入口地址
    static void SetInterruptDescriptorTableEntry(
        uint8_t interruptNumber,  // 中断编号
        uint16_t codeSegmentSelectorOffset,
        void (*handler)(),  //函数指针
        uint8_t DescriptorPrivilegelLevel,  // descriptor 的级别
        uint8_t DescriptorType
    );

    uint16_t hardwareInterruptOffset;

    static void InterruptIgnore();

    static uint32_t handleInterrupt(uint8_t InterruptNumber, uint32_t esp);  // 定义一个静态函数，使其处理一些中断的请求

    // 处理编号为 0xXX 的中断，需要实现对应的汇编
    static void HandleInterruptRequest0x00();  // 时间中断
    static void HandleInterruptRequest0x01();
    static void HandleInterruptRequest0x02();
    static void HandleInterruptRequest0x03();
    static void HandleInterruptRequest0x04();
    static void HandleInterruptRequest0x05();
    static void HandleInterruptRequest0x06();
    static void HandleInterruptRequest0x07();
    static void HandleInterruptRequest0x08();
    static void HandleInterruptRequest0x09();
    static void HandleInterruptRequest0x0A();
    static void HandleInterruptRequest0x0B();
    static void HandleInterruptRequest0x0C();
    static void HandleInterruptRequest0x0D();
    static void HandleInterruptRequest0x0E();
    static void HandleInterruptRequest0x0F();
    static void HandleInterruptRequest0x31();

    // 定义异常函数
    static void HandleException0x00();
    static void HandleException0x01();
    static void HandleException0x02();
    static void HandleException0x03();
    static void HandleException0x04();
    static void HandleException0x05();
    static void HandleException0x06();
    static void HandleException0x07();
    static void HandleException0x08();
    static void HandleException0x09();
    static void HandleException0x0A();
    static void HandleException0x0B();
    static void HandleException0x0C();
    static void HandleException0x0D();
    static void HandleException0x0E();
    static void HandleException0x0F();
    static void HandleException0x10();
    static void HandleException0x11();
    static void HandleException0x12();
    static void HandleException0x13();

    Port8BitSlow picMasterCommand;
    Port8BitSlow picMasterData;
    Port8BitSlow picSlaveCommad;
    Port8BitSlow picSlaveData;

}__attribute__((packed));

#endif