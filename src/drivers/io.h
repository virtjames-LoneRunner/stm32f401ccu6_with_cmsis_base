#ifndef IO_H
#define IO_H

#include <stdint.h>

#include "defines.h"

typedef enum {
  // This will be multiplied by 2 to get position in GPIOx_MODER
  IO0 = 0,
  IO1 = 1U, 
  IO2,  IO3,  IO4,
  IO5,  IO6,  IO7,  
  IO8,  IO9,  IO10, 
  IO11, IO12, IO13, 
  IO14, IO15,
} io_mode_pin;

typedef enum {
  IO_MASK_0           = (1U << IO0),
  IO_MASK_1           = (1U << IO1),
  IO_MASK_2           = (1U << IO2),
  IO_MASK_3           = (1U << IO3),
  IO_MASK_4           = (1U << IO4),
  IO_MASK_5           = (1U << IO5),
  IO_MASK_6           = (1U << IO6),
  IO_MASK_7           = (1U << IO7),
  IO_MASK_8           = (1U << IO8),
  IO_MASK_9           = (1U << IO9),
  IO_MASK_10          = (1U << IO10),
  IO_MASK_11          = (1U << IO11),
  IO_MASK_12          = (1U << IO12),
  IO_MASK_13          = (1U << IO13),
  IO_MASK_14          = (1U << IO14),
  IO_MASK_15          = (1U << IO15),
} io_pin_mask_e;

typedef enum
{
  IO_MODE_INPUT       = 0x0,
  IO_MODE_OUTPUT      = 0x1,
  IO_MODE_ALTERNATE   = 0x2,
  IO_MODE_ANALOG      = 0x3,
} io_mode_e;

typedef enum
{
  IO_OTYPE_PP        = 0x0,  // PUSH PULL
  IO_OTYPE_OD        = 0x1,  // OPEN DRAIN
} io_otype_e;

typedef enum {
  IO_SPEED_LOW        = 0x0,
  IO_SPEED_MEDIUM     = 0x1,
  IO_SPEED_HIGH       = 0x2,
  IO_SPEED_VERY_HIGH  = 0x3,
} io_speed_e;

typedef enum {
  IO_PUPD_NO          = 0x0,
  IO_PUPD_UP          = 0x1,
  IO_PUPD_DOWN        = 0x2,
  // Reserved
} io_pupd_e;

typedef enum {
  IO_AF0,
  IO_AF1,
  IO_AF2,
  IO_AF3,
  IO_AF4,
  IO_AF5,
  IO_AF6,
  IO_AF7,
  IO_AF8,
  IO_AF9,
  IO_AF10,
  IO_AF11,
  IO_AF12,
  IO_AF13,
  IO_AF14,
  IO_AF15,
} io_alternate_f_e;

typedef enum {
  IO_OUT_LOW,
  IO_OUT_HIGH
} io_out_e;

typedef enum {
  IO_IN_LOW,
  IO_IN_HIGH
} io_in_e;

typedef struct {
  io_mode_e   mode;
  io_otype_e  otype;
  io_speed_e  speed;
  io_pupd_e   pupd;
  io_alternate_f_e altf;
} io_pin_config_t;


// Configure all pin parameters at once for multiple pins on the same port
// TODO: Add a function to configure the similarly at once using bit masking for pin numbers
void io_configure_pin(GPIO_TypeDef *port, const uint32_t pin, const io_pin_config_t *config);
void io_toggle_pin(GPIO_TypeDef *port, const uint32_t pin);
void io_set_select();       // Determines the pin function i.e. GPIO, SPI, I2C, etc.
void io_set_direction();    // Set whether input or output
void io_set_resistor();     // Set whether to enable internal pull-up or pull-down
void io_set_out(GPIO_TypeDef *port, const uint32_t pin_mask, const io_out_e state);  // Set output value HIGH or LOW
io_in_e io_get_input();     // Get the pin value


#endif
