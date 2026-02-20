#ifndef EXTI_H
#define EXTI_H

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"

typedef enum {
  EXTI_0,
  EXTI_1,
  EXTI_2,
  EXTI_3,
  EXTI_4,
  EXTI_5,
  EXTI_6,
  EXTI_7,
  EXTI_8,
  EXTI_9,
  EXTI_10,
  EXTI_11,
  EXTI_12,
  EXTI_13,
  EXTI_14,
  EXTI_15,
  EXTI_16,
  EXTI_17,
  EXTI_18,
  EXTI_19,
  EXTI_20,
  EXTI_21,
  EXTI_22,
} exti_line_e;

typedef enum {
  EXTI_SOURCE_PORTA,
  EXTI_SOURCE_PORTB,
  EXTI_SOURCE_PORTC,
  EXTI_SOURCE_PORTD,
  EXTI_SOURCE_PORTE,
  EXTI_RESERVED_1,
  EXTI_RESERVED_2,
  EXTI_SOURCE_PORTH,
} exti_source_e;

typedef enum {
  EXTI_STATE_DISABLED,
  EXTI_STATE_ENABLED,
} exti_state_e;


void exti_configure(const exti_line_e line, const exti_source_e source);
void exti_set_interrupt_mask(const exti_line_e line, const exti_state_e state);
void exti_set_event_mask(const exti_line_e line, const exti_state_e state);

void exti_set_rising_trig(const exti_line_e line, const exti_state_e state);
void exti_set_falling_trig(const exti_line_e line, const exti_state_e state);
void exti_set_software_trig(const exti_line_e line, const exti_state_e state);
void exti_clear_pending(const exti_line_e line);
bool exti_read_pending_reg(const exti_line_e line, const exti_state_e state);

#endif
