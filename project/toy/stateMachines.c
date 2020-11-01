#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

static short freq = 500;
static short state2_status = 1;

char state1()
{
  char changed = 0;
  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }
  leds_changed = changed;
  led_update();
}

char toggle_red()
{
  static char stateS1 = 1;

  switch (stateS1) {
  case 0:
    red_on = 1;
    buzzer_set_period(1000);
    stateS1 = 1;
    break;
  case 1:
    red_on = 0;
    buzzer_set_period(0);
    stateS1 = 0;
    break;
  }
  
  return 1;
}
char toggle_green()
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    buzzer_set_period(3000);
    changed = 1;
  }
  return changed;
}

char state2()
{
  static short stateS2 = 0;

  switch(stateS2){
  case 0:
  case 1: up_state(); stateS2++; break;
  case 2: down_state(); stateS2 = 0;
  default: break;
  }
  return 1;
}

void up_state()
{
  state2_status = 1; red_on = 1; green_on = 0;
  leds_changed = 1; led_update();
}
void down_state()
{
  state2_status = 0; red_on = 0; green_on = 1;
  leds_changed= 1; led_update();
}

void buzzer_advance(){
  if (state2_status) freq += 225;
  else freq -= 450;

  short cycles = 2000000/freq;
  buzzer_set_period(cycles);
}

char state3()
{
  static short s3Counter = 0;
  static short stateS3 = 0;
  if (++s3Counter == 125) { stateS3++; s3Counter = 0;}
  switch (stateS3){
  case 0: red_on = 1; green_on = 1; buzzer_set_period(0); break;
  case 1: dimLights(2); buzzer_set_period(500); break;
  case 2: dimLights(3); buzzer_set_period(333); break;
  case 3: dimLights(4); buzzer_set_period(250); break;
  case 4: dimLights(8); buzzer_set_period(125); break;
  case 5: dimLights(16); buzzer_set_period(0); stateS3 = 0; break;
  }
}

void dimLights(char x){
  
  static short dimCount = 0;
  switch(dimCount % x){
  case 0: red_on = 1; green_on = 1; dimCount++; break;
  case 1: red_on = 0; green_on = 0; dimCount++; break;
  default: red_on = 0; green_on = 0; dimCount++; break;
  }
  leds_changed = 1;
  led_update();
}


char state4(){
  buzzer_set_period(0);
  red_on = 0;
  green_on = 0;
  leds_changed = 1;
  led_update();
  return 1; 
}


void state_advance()
{
  char changed = 0;
  switch(super_state){    
  case 1:
    changed = state1();
    break;
  case 2:
    changed = state2();
    break;
  case 3:
    changed = state3();
    break;
  case 4:
    changed = state4();
    break;
  }
  leds_changed = changed;
  led_update();
}
