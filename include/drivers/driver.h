#ifndef __MYOS__DRIVERS__DRIVER_H
#define __MYOS__DRIVERS__DRIVER_H

namespace myos
{
    namespace drivers
    {
        class Driver
        {
        public:
            Driver();
            ~Driver();

            // 定义接口
            virtual void Activate();
            virtual int Reset();
            virtual void Deactivate();
        };

        class DriverManager
        {
        public:
            DriverManager();
            ~DriverManager();

            void AddDriver(Driver *);
            void ActivateAll(); // 激活所有驱动
        private:
            Driver *drivers[256];
            int numDrivers;
        };
    }
}

#endif
