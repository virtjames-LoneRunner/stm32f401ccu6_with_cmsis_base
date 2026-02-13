#ifndef PWR_H
#define PWR_H

#include <stdint.h>
#include "stm32f401xc.h"

typedef enum {
  PWR_SCALE3_RES,
  PWR_SCALE3,
  PWR_SCALE2,
  PWR_SCALE1,
} pwr_vos_scale_e;

void pwr_set_vos_scale(pwr_vos_scale_e scale);
void pwr_wait_ready(void);

#endif

