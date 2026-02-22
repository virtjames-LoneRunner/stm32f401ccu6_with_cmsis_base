#include "exti.h"

void exti_configure(const exti_line_e line, const exti_source_e source, const exti_trigger_e trigger) {
  if (line > EXTI_15) return;

  const uint32_t cr_idx = line >> 2; // pin/4
  const uint32_t shift = (line & 0x03U) << 2;

  SYSCFG->EXTICR[cr_idx] &= ~(0xFU << shift);
  SYSCFG->EXTICR[cr_idx] |= (source << shift);

  if (trigger & EXTI_TRIG_RISING) exti_set_rising_trig(line, EXTI_STATE_ENABLED);
  if (trigger & EXTI_TRIG_FALLING) exti_set_falling_trig(line, EXTI_STATE_ENABLED);
  if (trigger & EXTI_TRIG_SOFTWARE) exti_set_software_trig(line, EXTI_STATE_ENABLED);

  exti_clear_pending(line);
}

void exti_set_interrupt_mask(const exti_line_e line, const exti_state_e state) {
  switch (state) {
    case EXTI_STATE_ENABLED:
      EXTI->IMR |= (state << line);
      break;
    default:
      EXTI->IMR &= ~(state << line);
  }
}
void exti_set_event_mask(const exti_line_e line, const exti_state_e state) {
  EXTI->EMR &= ~(state << line);
  EXTI->EMR |= (state << line);
}

void exti_set_rising_trig(const exti_line_e line, const exti_state_e state) {
  EXTI->RTSR &= ~(state << line);
  EXTI->RTSR |= (state << line);
}
void exti_set_falling_trig(const exti_line_e line, const exti_state_e state) {
  EXTI->FTSR &= ~(state << line);
  EXTI->FTSR |= (state << line);
}
void exti_set_software_trig(const exti_line_e line, const exti_state_e state) {
  EXTI->SWIER &= ~(state << line);
  EXTI->SWIER |= (state << line);
}
void exti_clear_pending(const exti_line_e line) {
  EXTI->PR = (1U << line);
}
bool exti_read_pending_reg(const exti_line_e line, const exti_state_e state) {
  return EXTI->PR & (state << line);
}
