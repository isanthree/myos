/* coding: utf-8 */

#include "interrupts.h"

void printf(const char*);

uint32_t InterruptManager::handleInterrupt(uint8_t interruptNumber, uint32_t esp)
{
    printf("interrupt");
    return esp;
}

// 实现中断处理函数，注释掉不需要，因为是在汇编里面实现
// 这里是为了得到汇编命名，用完注释
// void InterruptManager::HandleInterruptRequest0x00() {} 

// 实现异常函数，注释掉不需要，因为是在汇编里面实现了
// 这里是为了得到汇编命名，用完注释
// void InterruptManager::HandleException0x00() {}

// 注释掉不需要，因为是在汇编里面实现了
// 这里是为了得到汇编命名，用完注释
// void InterruptManager::InterruptIgnore() {}