#include <msp430.h>
#include "stateMachines.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static short count = 0;
  if( (++ count % 25) == 0) buzzer_advance();
  if( count == 250){
    state_advance();
    count = 0;
  }
}
