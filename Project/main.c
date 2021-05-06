#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "movement.h"
#include "switches.h"
#include "buzzer.h"
#include "assembly.h"

#define LED_RED BIT6

short move_prey = 0;
short move_ship = 0;
short redrawScreen = 1;
short prey_state = 0;
short redraw_hexagon = 0;


void wdt_c_handler()
{
  // Each 1/10 of a second, we change the hexagon
  static int hexagon_count = 0;
  if (hexagon_count++ == 25) {
    hexagon_count = 0;
    redraw_hexagon = 1;
    redrawScreen = 1;
  }

  // Each 30 tics, we move the prey horizontally
  static int prey_count = 0;
  if (prey_count++ == 30) {
    prey_count = 0;
    move_prey = 1;
    redrawScreen = 1;
  }

  // Each 10 tics, the ship can move horizontally
  static int ship_count = 0;
  if (ship_count++ == 10) {
    ship_count = 0;
    move_ship = 1;
    redrawScreen = 1;
  }
}

/** Initializes everything, clears the screen, draws "hello" and a square */
void main()
{
  P1DIR |= LED_RED;  /** Red led on when CPU on */
  P1OUT |= LED_RED;
  configureClocks();
  lcd_init();
  buzzer_init();
  switch_init();
  enableWDTInterrupts();  // Enable periodic interrupts
  or_sr(0x8);             // Enable interrupts
  
  u_char width = screenWidth, height = screenHeight;

  /* We clean the screen and draw our initial figures */
  clearScreen(COLOR_BLACK);
  drawSpaceShip(50, COLOR_RED);
  drawString11x16(35, 70, "START", COLOR_ROYAL_BLUE, COLOR_BLACK);
  
  while (1) {  // Always running
    if (redrawScreen) {       // If we need to update a drawing
      redrawScreen = 0;
      
      if (redraw_hexagon) {   /* Updating hexagon */
	redraw_hexagon = 0;
	updateHexagon();
      }

      if (move_ship) {        /* If we need to move the ship */
        move_ship = 0;        
	if (switch0_down) {   /* Moving left if switch0 is pressed */
	  moveShipL();
	}
	else if (switch2_down) { /* Moving right if switch2 is pressed */
	  moveShipR();
	}
	else {                /* Else, we just update the scope so that it is */
	  keepScope();        /* not erased by the prey */
	}
	
	if (switch3_down) {     /* If switch3 is pressed, we turn on the red led */
	  P1OUT |= LED_RED;        /* Make a sound indicating fire and go to next state */
	  buzzer_set_period(5000);
	  prey_state = shoot(prey_state); 
	}
	else {
	  buzzer_set_period(0);  /* Else, no sound and turn led off */
	  P1OUT &= ~LED_RED;
	}
      }
      
      if (move_prey) {      /* Finally, if we update the prey, we move it horizontally */
        move_prey = 0;
	updatePreyCol(prey_state);
      }
      if (prey_state != 1) {   /* And only if we are not in state 1, we move it vertically */
	prey_state = updatePreyRow(prey_state);  /* And update its state */
      }
      
    }
    or_sr(0x10); /* Turn CPU off */
  }
}
