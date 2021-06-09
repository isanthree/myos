/* coding: utf-8 */

#include "port.h"

Port::Port(uint16_t portnumber)
    : portnumber(portnumber) {}

Port::~Port() {}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Port8Bit ...
// Port8Bit类构造函数，调用基类的构造函数
Port8Bit::Port8Bit(uint16_t portnumber)
    : Port(portnumber) {}

Port8Bit::~Port8Bit() {}

// 汇编进行操纵端口进行写操作
void Port8Bit::write(uint8_t data)
{
    // inb：从 io 端口写入一个字节
    // 
    __asm__ volatile("outb %1, %0" : "=a" (data) : "Nd" (portnumber));
}

uint8_t Port8Bit::read()
{
    uint8_t result;
    __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (portnumber));
    return result;
}
// ... Port8Bit >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Port8BitSlow ...
// Port8BitSlow类构造函数，调用基类的构造函数
Port8BitSlow::Port8BitSlow(uint16_t portnumber)
    : Port8Bit(portnumber) {}

Port8BitSlow::~Port8BitSlow() {}

// 汇编进行操纵端口进行写操作
void Port8BitSlow::write(uint8_t data)
{
    // inb：从 io 端口写入一个字节
    __asm__ volatile("outb %1, %0\njmp 1f\n1: jmp 1f\n1:" : "=a" (data) : "Nd" (portnumber));
}
// ... Port8BitSlow >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Port16Bit ... 
// Port16Bit类构造函数，调用基类的构造函数
Port16Bit::Port16Bit(uint16_t portnumber)
    : Port(portnumber) {}

Port16Bit::~Port16Bit() {}

// 汇编进行操纵端口进行写操作
void Port16Bit::write(uint16_t data)
{
    // inb：从 io 端口写入一个字节
    // 
    __asm__ volatile("outw %1, %0" : "=a" (data) : "Nd" (portnumber));
}

uint16_t Port16Bit::read()
{
    uint16_t result;
    __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (portnumber));
    return result;
}
// ... Port16Bit >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Port32Bit ...
// Port32Bit类构造函数，调用基类的构造函数
Port32Bit::Port32Bit(uint16_t portnumber)
    : Port(portnumber) {}

Port32Bit::~Port32Bit() {}

// 汇编进行操纵端口进行写操作
void Port32Bit::write(uint32_t data)
{
    // inb：从 io 端口写入一个字节
    // 
    __asm__ volatile("outl %1, %0" : "=a" (data) : "Nd" (portnumber));
}

uint32_t Port32Bit::read()
{
    uint32_t result;
    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (portnumber));
    return result;
}
// ... Port32Bit >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>