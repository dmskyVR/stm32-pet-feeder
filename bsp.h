#ifndef BSP_H
#define BSP_H

#include <stdint.h>
#include <stdbool.h>                                                                                                                                         

#define BSP_TICKS_PER_SEC 1000U

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

u32 BSP_getTicks(void);
void BSP_init(void);
void BSP_servoSetPulse(u16 pulse_us);
bool BSP_buttonPressed(void);

#endif