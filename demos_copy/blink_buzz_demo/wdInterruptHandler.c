#include <msp430.h>
#include "stateMachines.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static short count = 0;
  if(count == 125){
    state_advance();
    buzzer_advance();
    count = 0;
  }
  count++;
}
