#ifndef __GDT_H
#define __GDT_H

#include "types.h"

// 定义 GDT，全局描述符表
class GlobalDescriptorTable {
public:
    // 定义段描述符
    class SegmentDescriptor {
    public: 
        SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
        uint32_t Base();  // return base address
        uint32_t Limit();  // return limit
    
    private:
        uint16_t limit_lo;  // Segment Limit 15..0，两个字节构成
        uint16_t base_lo;  // Base Address 15..0，两个字节构成
        uint8_t base_hi;  // Base 23..16，一个字节构成
        uint8_t type;  // TYPE
        uint8_t flags_limit_hi;  // 图4-13 的 23..16
        uint8_t base_vhi;  // Base 31..24，一个字节构成
    }__attribute__((packed));  // __attribute__((packed))：编译器不要进行内存对齐

    // 定义空的段描述符
    SegmentDescriptor nullSegmentDescriptor;
    // 定义未使用的段描述符
    SegmentDescriptor unusedSegmentDescriptor;
    // 定义代码段
    SegmentDescriptor codeSegmentDescriptor;
    // 定义数段
    SegmentDescriptor dataSegmentDescriptor;

public:
    GlobalDescriptorTable();
    ~GlobalDescriptorTable();

    // 定义函数获取代码段
    uint16_t CodeSegmentDescriptor();  // 函数名用大写，成员用小写
    uint16_t DataSegmentDescriptor();
};

#endif 