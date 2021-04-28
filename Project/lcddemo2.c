/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLACK);

  drawString11x16(35,60, "START", COLOR_GREEN, COLOR_BLACK);
  drawScope(70);
  drawSpaceShip(10);
  drawPrey(30, 100, 0);
  drawPrey(50, 100, 1);
  drawPrey(70, 100, 2);
  drawPrey(90, 100, 3);

  //fillRectangle(30,30, 60, 60, COLOR_ORANGE);

  //drawHexagon(50, 70, 10, COLOR_ORANGE);
}
