#ifndef __MYOS__HARDWARECOMMUNICATION__PCI_H
#define __MYOS__HARDWARECOMMUNICATION__PCI_H

#include "common/types.h"
#include "hardwarecommunication/port.h"
#include "hardwarecommunication/interrupts.h"
#include "drivers/driver.h"

namespace myos
{
    namespace hardwarecommunication
    {
        class PeripheralComponentInterconnectDeviceDescriptor
        {
        public:
            PeripheralComponentInterconnectDeviceDescriptor();
            ~PeripheralComponentInterconnectDeviceDescriptor();

            myos::common::uint32_t portBase;  // 基址
            myos::common::uint32_t interrupt; // 中断

            myos::common::uint8_t bus;
            myos::common::uint8_t device;
            myos::common::uint8_t function;

            myos::common::uint16_t device_id;
            myos::common::uint16_t vendor_id;  // 设备号；0 和 0xffff 都是无效的

            myos::common::uint8_t class_id;
            myos::common::uint8_t subclass_id;
            myos::common::uint8_t interface_id;
            myos::common::uint8_t revision;
        };

        class PeripheralComponentInterconnectController
        {
        public:
            PeripheralComponentInterconnectController();
            ~PeripheralComponentInterconnectController();

            myos::common::uint32_t Read(myos::common::uint8_t bus,
                                        myos::common::uint8_t device,
                                        myos::common::uint8_t function,
                                        myos::common::uint8_t registeroffset); // 寄存器偏移

            void Write(myos::common::uint8_t bus,
                       myos::common::uint8_t device,
                       myos::common::uint8_t function,
                       myos::common::uint8_t registeroffset,
                       myos::common::uint32_t value);

            bool DeviceHasFunctions(myos::common::uint8_t bus, myos::common::uint8_t device); // 0000000
            void SelectDrivers(myos::drivers::DriverManager *driverManager);

            // 获取 device descriptor
            PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor (
                myos::common::uint8_t bus,
                myos::common::uint8_t device,
                myos::common::uint8_t function);

        private:
            Port32Bit dataPort;
            Port32Bit commandPort;
        };
    }
}

#endif