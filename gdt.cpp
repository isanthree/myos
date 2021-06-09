/* coding: utf-8 */

#include "gdt.h"

GlobalDescriptorTable::GlobalDescriptorTable()
    : nullSegmentDescriptor(0, 0, 0),
    unusedSegmentDescriptor(0, 0, 0),
    codeSegmentDescriptor(0, 64*1024*1024, 0x9a),  // 64M 寻址大小
    dataSegmentDescriptor(0, 64*1024*1024, 0x92)
{
    uint32_t i[2];  // 定义存放 GDT 描述符(GDT descriptor)的数组
    i[1] = (uint32_t)this;
    i[0] = sizeof(GlobalDescriptorTable) << 16;
    asm volatile("lgdt (%0)": :"p" (((uint8_t *)i)+2))
}

GlobalDescriptorTable::~GlobalDescriptorTable() {}

// 定义函数获取数据段
uint16_t GlobalDescriptorTable::DataSegmentDescriptor()
{
    // 返回段内偏移
    return (uint8_t*)&dataSegmentDescriptor - (uint8_t*)this;
}

// 定义函数获取代码段
uint16_t GlobalDescriptorTable::CodeSegmentDescriptor()
{
    // 返回段内偏移
    return (uint8_t*)&CodeSegmentDescriptor - (uint8_t*)this;
}

GlobalDescriptorTable::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type)
{
    
}