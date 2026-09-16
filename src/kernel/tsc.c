#include "kernel/tsc.h"
#include "kernel/apic.h"
#include "lib/mathh.h"
#include <stdint.h>
uint64_t tsc_freq_hz;
uint64_t tsc_freq_ms;
uint64_t tsc_freq_us;
uint64_t tsc_freq_ticks;

uint64_t init_time_ticks;
uint64_t init_time_sec;
uint64_t init_time_ms;

extern volatile uintptr_t tick;

uint64_t rdtsc(void) {
    uint32_t l, h;
    asm volatile ("rdtsc" : "=a"(l), "=d"(h));
    return ((uint64_t)h << 32) | l;
}
void calibrate_tsc() {
    uint64_t oldtsc = rdtsc();
    uintptr_t oldsystime = tick;
    while (oldsystime == tick) { // now the diference is tickinms
        asm volatile ("hlt");
    }
    uint64_t newtsc = rdtsc();
    tsc_freq_ticks = (uintptr_t)(newtsc - oldtsc);
    tsc_freq_hz = (tsc_freq_ticks * 1000) / tickinms;
    tsc_freq_ms = tsc_freq_ticks / tickinms;
    tsc_freq_us = tsc_freq_ms / 1000;
    init_time_sec = newtsc / tsc_freq_hz;
    init_time_ticks = newtsc / tsc_freq_ticks;
    init_time_ms = newtsc / tsc_freq_ms;
    tick += init_time_ticks;
}