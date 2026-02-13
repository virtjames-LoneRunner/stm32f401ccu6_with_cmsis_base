#include "pwr.h"

void pwr_set_vos_scale(pwr_vos_scale_e scale)
{
	uint32_t reg32;
	reg32 = PWR->CR & ~(PWR_CR_VOS);
	reg32 |= (scale << PWR_CR_VOS_Pos);
	PWR->CR = reg32;
}

void pwr_wait_ready(void) {
  while (!(PWR->CSR & PWR_CSR_VOSRDY));
}
