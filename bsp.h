#ifndef BSP_H
#define BSP_H

#include <stdint.h>                                                                                                                                         

#define BSP_TICKS_PER_SEC 1000U

typedef uint32_t u32;

u32 BSP_getTicks(void);
void BSP_init(void);

#endif