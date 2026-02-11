#include "stm32f4xx.h"
#include "test/init.test.h"
// #include "test/blink.test.h"

int main(void) {
  init_test();

  // blink_test();

  while(1) {
    __NOP();
  }
}
