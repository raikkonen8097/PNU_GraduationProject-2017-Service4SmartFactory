/**
\brief WSN430v14-specific definition of the "leds" bsp module.

\author Thomas Watteyne <watteyne@eecs.berkeley.edu>, February 2012.
*/

#include "msp430f1611.h"
#include "leds.h"

//=========================== defines =========================================

//=========================== variables =======================================

//=========================== prototypes ======================================

//=========================== public ==========================================

void    leds_init(void) {
   P5OUT     |=  0x70;       // P5OUT = 0bx111xxxx, all LEDs off
   P5DIR     |=  0x70;       // P5DIR = 0bx111xxxx, all LEDs output
}

// red = LED1 = P5.4
void    leds_error_on(void) {
   P5OUT     &= ~0x10;
}
void    leds_error_off(void) {
   P5OUT     |=  0x10;
}
void    leds_error_toggle(void) {
   P5OUT     ^=  0x10;
}
uint8_t leds_error_isOn(void) {
   return (uint8_t)(P5OUT & 0x10)>>4;
}
void leds_error_blink(void) {
   uint8_t i;
   volatile uint16_t delay;
   // turn all LEDs off
   P5OUT     |=  0x70;
   
   // blink error LED for ~10s
   for (i=0;i<80;i++) {
      P5OUT     ^=  0x10;
      for (delay=0xffff;delay>0;delay--);
   }
}

// green = LED2 = P5.5
void    leds_radio_on(void) {
   P5OUT     &= ~0x20;
}
void    leds_radio_off(void) {
   P5OUT     |=  0x20;
}
void    leds_radio_toggle(void) {
   P5OUT     ^=  0x20;
}
uint8_t leds_radio_isOn(void) {
   return (uint8_t)(P5OUT & 0x20)>>5;
}

// blue = LED3 = P5.6
void    leds_sync_on(void) {
   P5OUT     &= ~0x40;
}
void    leds_sync_off(void) {
   P5OUT     |=  0x40;
}
void    leds_sync_toggle(void) {
   P5OUT     ^=  0x40;
}
uint8_t leds_sync_isOn(void) {
   return (uint8_t)(P5OUT & 0x40)>>6;
}

// no debug LED on the WSN430v14 :(
void    leds_debug_on(void) {  
}
void    leds_debug_off(void) {
}

void    leds_debug_toggle(void) {
}
uint8_t leds_debug_isOn(void) {
   return 0;
}

// all leds
void    leds_all_on(void) {
   P5OUT     &= ~0x70;
}
void    leds_all_off(void) {
   P5OUT     |=  0x70;
}
void    leds_all_toggle(void) {
   P5OUT     ^=  0x70;
}

void    leds_circular_shift(void) {
   uint8_t leds_on;
   // get LED state
   leds_on  = (~P5OUT & 0x70) >> 4;
   // modify LED state
   if (leds_on==0) {                             // if no LEDs on, switch on one
      leds_on = 0x01;
   } else {
      leds_on <<= 1;                             // shift by one position
      if ((leds_on & 0x08)!=0) {
         leds_on &= ~0x08;
         leds_on |=  0x01;                       // handle overflow
      }
   }
   // apply updated LED state
   leds_on <<= 4;                                // send back to position 4
   P5OUT |=  (~leds_on & 0x70);                  // switch on the leds marked '1' in leds_on
   P5OUT &= ~( leds_on & 0x70);                  // switch off the leds marked '0' in leds_on
}

void    leds_increment(void) {
   uint8_t leds_on;
   // get LED state
   leds_on  = (~P5OUT & 0x70) >> 4;
   // modify LED state
   if (leds_on==0) {                             // if no LEDs on, switch on one
      leds_on = 0x01;
   } else {
      leds_on += 1;
   }
   // apply updated LED state
   leds_on <<= 4;                                // send back to position 4
   P5OUT |=  (~leds_on & 0x70);                  // switch on the leds marked '1' in leds_on
   P5OUT &= ~( leds_on & 0x70);                  // switch off the leds marked '0' in leds_on
}

//=========================== private =========================================
