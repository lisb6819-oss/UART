#ifndef __US_DELAY_H
#define __US_DELAY_H

#include "stm32f1xx_hal.h"

void DWT_Init(void);
void delay_us(uint32_t us);

#endif /* __US_DELAY_H */