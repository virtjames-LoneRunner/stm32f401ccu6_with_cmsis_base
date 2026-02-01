#include "stm32f4xx.h"

/**
 * Simple delay function
 * 'volatile' prevents the compiler from optimizing the loop away
 */
void delay(volatile uint32_t count) {
    while(count--) {
        __NOP();
    }
}

int main(void) {
    /* 1. Enable clock for GPIOC (Bit 2 of AHB1ENR) */
    /* Reference Manual: RCC_AHB1ENR register */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    /* 2. Configure PC13 as Output */
    /* MODER register: 00=Input, 01=Output, 10=Alt, 11=Analog */
    /* Pin 13 uses bits 26 and 27 */
    GPIOC->MODER &= ~(3U << (13 * 2)); // Clear bits 26, 27
    GPIOC->MODER |=  (1U << (13 * 2)); // Set bit 26 (Output mode)

    while(1) {
        /* 3. Toggle PC13 */
        /* ODR = Output Data Register */
        GPIOC->ODR ^= (1U << 13);

        /* On many Black Pill boards, the LED is 'active low' */
        /* (Pin LOW = LED ON, Pin HIGH = LED OFF) */
        
        delay(1000000); 
    }
}
