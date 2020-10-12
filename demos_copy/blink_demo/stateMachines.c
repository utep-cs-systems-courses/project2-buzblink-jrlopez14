#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

char toggle_red()		/* always toggle! */
{
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
  char changed = 0;
  green_on ^= 1;
  

}


void state_advance()		/* alternate between toggling red & green */
{
  static short state_counter = 0;
  static short state = 0;
  if (state_counter == 125){
    switch(state){
    case 0: state = 1; break;
    case 1: state = 2; break;
    case 2: state = 0; break;
    default: state = 0;
    }
    state_counter = 0;
  }
  switch(state){
  case 0: dimLights50(); green_on = 1; break;
  case 1: dimLights33(); green_on = 0; break;
  case 2: dimLights33(); green_on = 1; break;
  default: green_on = 1;
  }
  state_counter++;
}

void dimLights50()
{
  static short count = 0;
  switch(count%2){
  case 0: red_on = 1; count++; break;
  case 1: red_on = 0; count++; break;
  }
  led_changed = 1;
  led_update();
}
void dimLights33()
{
  static short count = 0;
  switch(count%3){
  case 0: red_on = 1; count++; break;
  case 1: red_on = 0; count++; break;
  default: count++; break;
  }
  led_changed = 1;
  led_update();
}

void dimLights25()
{
  static short count = 0;
  switch(count%4){
  case 0: red_on = 1; count++; break;
  case 1: red_on = 0; count++; break;
  default: count++; break;
  }
  led_changed = 1;
  led_update();
}
