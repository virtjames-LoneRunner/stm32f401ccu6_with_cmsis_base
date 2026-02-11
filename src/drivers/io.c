#include "io.h"
#include "stm32f401xc.h"

void io_configure_pin(GPIO_TypeDef *port, const uint32_t pin, const io_pin_config_t *config) {
  port->MODER &= ~(3U << (pin * 2));
  port->MODER |= (config->mode << (pin * 2));

  port->PUPDR &= ~(3U << (pin * 2));
  port->PUPDR |= (config->pupd << (pin * 2));

  port->OTYPER &= ~(1U << (pin));
  port->OTYPER |= (config->otype << pin);

  port->OSPEEDR &= ~(3U << (pin * 2));
  port->OSPEEDR |= (config->speed << (pin * 2));

  port->PUPDR &= ~(3U << (pin * 2));
  port->PUPDR |= (config->pupd << (pin * 2));

  uint32_t idx = pin >> 3; // Divide by 8
  uint32_t shift = (pin & 0x07) << 2; // (pin % 8) * 4 (since each pin uses 4 bits)

  // Only set the AFR if mode is actually set to alternate mode
  if (config->mode == 0x2) {
    port->AFR[idx] &= ~(0xFU << shift);
    port->AFR[idx] |= (config->altf);
  }
}

void io_toggle_pin(GPIO_TypeDef *port, const uint32_t pin) {
  port->ODR ^= (1U << pin);
}

void io_set_select();
void io_set_direction();
void io_set_resistor();
void io_set_out(); 
io_in_e io_get_input();
