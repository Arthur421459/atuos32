#include <atuos/time.h>
void sleep(uint32_t sec) {
    asm volatile ("int $0xA7" :: "a"(2), "b"(sec) : "memory", "cc");
}
void msleep(uint32_t msec) {
    asm volatile ("int $0xA7" :: "a"(0x82), "b"(msec) : "memory", "cc");
}