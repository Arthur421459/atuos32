#ifndef TSC_H
#define TSC_H
#include <stdint.h>

extern uint64_t tsc_freq_hz;
extern uint64_t tsc_freq_ms;
extern uint64_t tsc_freq_us;
extern uint64_t tsc_freq_ticks;

extern uint64_t init_time_ticks;
extern uint64_t init_time_sec;
extern uint64_t init_time_ms;

void calibrate_tsc();
uint64_t rdtsc(void);
#endif