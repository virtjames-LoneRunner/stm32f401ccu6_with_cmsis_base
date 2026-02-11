#include "io.h"
#include "rcc.h"
#include "stm32f401xc.h"
#include "init.test.h"

void delay(volatile uint32_t count) {
    while(count--) {
        __NOP();
    }
}


void init_test() {
  rcc_hsi_clock_setup();
  // rcc_clock_pll_setup();
  static periph_clk_config_t periph_config = {
    .ahb1 = (RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIOBEN),
    .ahb2 = 0x0,
    .apb1 = 0x0,
    .apb2 = 0x0,
  };
  rcc_enable_peripherals(&periph_config);

  static io_pin_config_t pin_config = {
    .mode   = IO_MODE_OUTPUT,
    .otype  = IO_OTYPE_PP,
    .pupd   = IO_PUPD_NO,
    .speed  = IO_SPEED_LOW,
    .altf   = IO_AF0,
  };

  // GPIOC->MODER &= ~(3U << (13 * 2)); // Clear bits 26, 27
  // GPIOC->MODER |=  (1U << (13 * 2)); // Set bit 26 (Output mode)
  io_configure_pin((GPIO_TypeDef *)GPIOC_BASE, IO13, &pin_config);
  io_configure_pin((GPIO_TypeDef *)GPIOB_BASE, IO10, &pin_config);

  while(1) {
      /* 3. Toggle PC13 */
      /* ODR = Output Data Register */
      // GPIOC->ODR ^= (1U << 13);
      io_toggle_pin((GPIO_TypeDef *)GPIOC_BASE, IO13);
      io_toggle_pin((GPIO_TypeDef *)GPIOB_BASE, IO10);
      

      /* On many Black Pill boards, the LED is 'active low' */
      /* (Pin LOW = LED ON, Pin HIGH = LED OFF) */
      
      delay(500000); 
  }
}
