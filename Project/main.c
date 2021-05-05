#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "movement.h"

short move_prey = 0;
short move_ship = 0;
short redrawScreen = 1;
short prey_state = 2;
short redraw_hexagon = 0;


void wdt_c_handler()
{
  static int hexagon_count = 0;
  if (hexagon_count++ == 25) {
    hexagon_count = 0;
    redraw_hexagon = 1;
    redrawScreen = 1;
  }
  
  static int prey_count = 0;
  if (prey_count++ == 20) {
    prey_count = 0;
    move_prey = 1;
    redrawScreen = 1;
  }

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
  configureClocks();
  lcd_init();
  enableWDTInterrupts();
  or_sr(0x8);
  
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLACK);
  drawString11x16(35, 70, "START", COLOR_ROYAL_BLUE, COLOR_BLACK);
  
  while (1) {
    if (redrawScreen) {
      redrawScreen = 0;
      
      if (redraw_hexagon) {
	redraw_hexagon = 0;
	updateHexagon();
      }

      if (move_ship) {
        move_ship = 0;
	static u_int count = 0;
	if (count++ < 120)
	  moveShipR();
	else if (count < 240)
	  moveShipL();
	else
	  count = 0;
      }
      
      if (move_prey) {
        move_prey = 0;
	updatePreyCol(prey_state);
	//prey_state = updatePreyRow(prey_state);
      }
      if (prey_state != 1) {
	prey_state = updatePreyRow(prey_state);
      }
      
    }
    or_sr(0x10);
  }
}
