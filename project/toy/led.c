#include <msp430.h>
#include "led.h"
#include "switches.h"

void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  super_state_changed = 1;
  led_update();
}

void led_update(){
  if (super_state_changed) {
    char ledFlags = 0; /* by default, no LEDs on */

    P1OUT &= (0xff - LEDS) | ledFlags; // clear bits for off leds
    P1OUT |= ledFlags;         // set bits for on leds
  }
  super_state_changed = 0;
}

