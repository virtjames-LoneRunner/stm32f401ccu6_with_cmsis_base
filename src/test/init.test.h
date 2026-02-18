#ifndef INIT_TEST_H
#define INIT_TEST_H

#include "stm32f4xx.h"
#include "rcc.h"
#include "io.h"
#include "dma.h"
#include <stdint.h>

void delay(volatile uint32_t count);
void init_test(uint32_t *srcAddr, uint32_t *dstAddr, uint16_t length);

#endif
