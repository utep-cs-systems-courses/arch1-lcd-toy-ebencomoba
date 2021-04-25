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

  clearScreen(COLOR_BLUE);

  drawString11x16(20,20, "hello", COLOR_GREEN, COLOR_RED);

  //fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  
  u_char offset_r = 70, offset_c = 70, size = 10;
  u_char top = size*173/100;
  for (int r = 0; r < top; r++) {
    for (int c = 0; c < top; c++) {
      drawPixel(offset_c + c, offset_r + top - r, COLOR_ORANGE);
      drawPixel(offset_c - c, offset_r + top - r, COLOR_ORANGE);
    }
  }
}
