#include <msp430.h>
#include "stateMachines.h"
unsigned char super_state;
void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char s1Count = 0;
  static char s2Count = 0;
  
  if (super_state == 1){
    if (++ s1Count == 125){
      state_advance();
      s1Count = 0;
    }
  }
  else if (super_state == 2){
    if ( (++ s2Count % 25) == 0) buzzer_advance();
    if (s2Count == 250){
      state_advance();
      s2Count = 0;
    }
  }
  else if (super_state == 3){
    state_advance();
  }
}
