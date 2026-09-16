#ifndef KERNEL_H
#define KERNEL_H
#include <stdint.h>
void print_wpos(const char* str, int color, int pos);
void print(const char* str, int color);

void sleep(uint32_t sec);
void msleep(uint32_t msec);
#endif