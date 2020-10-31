#include <msp430.h>
#include "led.h"

unsigned char red_on = 0, green_on = 0;
unsigned char leds_changed = 0;

static char redVal[] = {0,LED_RED}, greenVal[] = {0, LED_GREEN};
void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  leds_changed = 1;
  led_update();
}

void led_update(){
  if (leds_changed) {
    char ledFlags = redVal[red_on] | greenVal[green_on];

    P1OUT &= (0xff - LEDS) | ledFlags; // clear bits for off leds
    P1OUT |= ledFlags;         // set bits for on leds
    leds_changed = 0;
  }
}

