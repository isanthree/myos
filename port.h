#ifndef __PORT_H
#define __PORT_H

#include "types.h"

// 这是一个虚拟类，不希望被实例化，使用 protected
class Port {
protected:
    uint16_t portnumber;  // io 操作就是要往一个端口读或写
    Port(uint16_t portnumber);
    ~Port();
};

// 8位 读取，继承 Port 类
class Port8Bit : public Port {
public:
    Port8Bit(uint16_t portnumber);
    ~Port8Bit();
    // 定义写操作，使用 virtual，希望能被 overwrite。
    // 父类的指针可以使用子类的方法
    virtual void write(uint8_t data);  
    virtual uint8_t read();  // 定义读操作
};

// 8位 读，继承 Port8Bit 类，慢操作
class Port8BitSlow : public Port8Bit {
public:
    Port8BitSlow(uint16_t portnumber);
    ~Port8BitSlow();
    // 定义写操作，使用 virtual，希望能被 overwrite。
    // 父类的指针可以使用子类的方法
    virtual void write(uint8_t data);  
    // virtual uint8_t read();  // 定义读操作
};

// 16位 读取，继承 Port 类
class Port16Bit : public Port {
public:
    Port16Bit(uint16_t portnumber);
    ~Port16Bit();
    // 定义写操作，使用 virtual，希望能被 overwrite
    virtual void write(uint16_t data);
    virtual uint16_t read();  // 定义读操作
};

// 32位 读取，继承 Port 类
class Port32Bit : public Port {
public:
    Port32Bit(uint16_t portnumber);
    ~Port32Bit();
    // 定义写操作，使用 virtual，希望能被 overwrite
    virtual void write(uint32_t data);
    virtual uint32_t read();  // 定义读操作
};

// 8位 读取，继承 Port 类
class Port64Bit : public Port {
public:
    Port64Bit(uint16_t portnumber);
    ~Port64Bit();
    // 定义写操作，使用 virtual，希望能被 overwrite
    virtual void write(uint64_t data);
    virtual uint64_t read();  // 定义读操作
};

#endif