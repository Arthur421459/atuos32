#ifndef TIME_H
#define TIME_H
#include <atuos/core.h>
typedef uint32_t nixt;
void sleep(uint32_t sec);
void msleep(uint32_t msec);
nixt get_nixt();
uint32_t get_exectime();
#endif