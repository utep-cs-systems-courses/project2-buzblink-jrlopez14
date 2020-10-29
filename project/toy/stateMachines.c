#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

void up_state();
void down_state();


static short x = 500;
static short status = 1;


void state_advance()		/* alternate between toggling red & green */
{
  static short state = 0;

  switch(state){
  case 0:
  case 1: up_state(); state++; break;
  case 2: down_state(); state = 0;
  default: break;
  }
  
}
void up_state(){
  status = 1; red_led_state = 1; green_led_state = 0;
  leds_changed = 1; led_update();
}

void down_state(){
  status = 0; red_led_state = 0; green_led_state = 1;
  leds_changed = 1; led_update();
}
void buzzer_advance(){
  if (status) x+= 225;
  else x-= 450;

  short cycles = 2000000/x;
  buzzer_set_period(cycles);
}

