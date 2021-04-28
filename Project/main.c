#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

short move_spaceship = 0;
short move_prey = 0;
short redrawScreen = 1;
short prey_state = 0;
short ship_col = 50;
short next_ship_col = 50;
signed char ship_velocity = 5;


void wdt_c_handler()
{
  static int ship_count = 0;
  if (ship_count++ == 50) {
    ship_count = 0;
    move_spaceship = 1;
    next_ship_col += ship_velocity;
    if (next_ship_col < 20 || next_ship_col > 100) {
      ship_velocity = -ship_velocity;
      next_ship_col += ship_velocity;
    }
      
    redrawScreen = 1;
  }
  
  static int prey_count = 0;
  if (prey_count++ == 25) {
    prey_count = 0;
    move_prey = 1;
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

  drawString11x16(35,60, "START", COLOR_GREEN, COLOR_BLACK);
  //fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  //Drawhexagon(50, 70, 10, COLOR_ORANGE);
  
  while (1) {
    if (redrawScreen) {
      redrawScreen = 0;
      
      if (move_spaceship) {
        move_spaceship = 0;
	drawScope(ship_col, COLOR_BLACK);
	drawScope(next_ship_col, COLOR_YELLOW);
	drawSpaceShip(ship_col, COLOR_BLACK);
	drawSpaceShip(next_ship_col, COLOR_RED);
	ship_col = next_ship_col;
      }
      
      if (move_prey) {
        move_prey = 0;
	drawPrey(60, 30, prey_state++);
      }
      if (prey_state >= 4) {
	prey_state = 0;
      }
    }
    or_sr(0x10);
  }
}
