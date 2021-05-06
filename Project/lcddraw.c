/** \file lcddraw.c
 *  \brief Adapted from RobG's EduKit
 */
#include "lcdutils.h"
#include "lcddraw.h"
#include "lcdtypes.h"


/** Draw single pixel at x,row 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */
void drawPixel(u_char col, u_char row, u_int colorBGR) 
{
  lcd_setArea(col, row, col, row);
  lcd_writeColor(colorBGR);
}

/** Fill rectangle
 *
 *  \param colMin Column start
 *  \param rowMin Row start
 *  \param width Width of rectangle
 *  \param height height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, 
		   u_int colorBGR)
{
  u_char colLimit = colMin + width, rowLimit = rowMin + height;
  lcd_setArea(colMin, rowMin, colLimit - 1, rowLimit - 1);
  u_int total = width * height;
  u_int c = 0;
  while ((c++) < total) {
    lcd_writeColor(colorBGR);
  }
}

/** Clear screen (fill with color)
 *  
 *  \param colorBGR The color to fill screen
 */
void clearScreen(u_int colorBGR) 
{
  u_char w = screenWidth;
  u_char h = screenHeight;
  fillRectangle(0, 0, screenWidth, screenHeight, colorBGR);
}

/** 11x16 font - this function draws a character */
void drawChar11x16(u_char rcol, u_char rrow, char c,
		   u_int fgColorBGR, u_int bgColorBGR) 
{
  u_char col = 0;
  u_char row = 0;
  u_int bit = 0x01;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 10, rrow + 16); /* relative to requested col/row */
  while (row < 16) {
    while (col < 11) {
      u_int colorBGR = (font_11x16[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
}

/** Draw string at col,row
 *  Type:
 *  FONT_LG - large (11x16)
 *  FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 *  Adapted from RobG's EduKit
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString11x16(u_char col, u_char row, char *string,
		     u_int fgColorBGR, u_int bgColorBGR)
{ /* We draw each character leaving a column between characters */
  u_char cols = col;
  while (*string) {
    drawChar11x16(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 12;
  }
}

/* Function draws an hexagon whose origin is (offset_c, offset_r)
 * The length of the hxagon is defined as the number of
 * pixels on the bottom side of the hexagon */
void drawHexagon(u_char offset_c, u_char offset_r, u_char length, u_int fgColorBGR)
{
  for (int row = 0; row < (length * 433/500); row++) {
    for (int col = 0; col < (length - (row*250/433)); col++) {
      drawPixel(offset_c + col, offset_r + row, fgColorBGR);
      drawPixel(offset_c + col, offset_r - row, fgColorBGR);
      drawPixel(offset_c - col, offset_r + row, fgColorBGR);
      drawPixel(offset_c - col, offset_r - row, fgColorBGR);
    }
  }
}

/* Similarly to drawing a character, we draw the figure that
 * represents the spaceship based on a bitmap */
void drawSpaceShip (u_char rcol, u_int fgcolorBGR)
{
  u_char col = 0;
  u_char row = 0;
  u_int bit = 0x80;

  lcd_setArea(rcol, 130, rcol + 8, 137); /* relative to requested col/row */
  while (row < 7) {
    while (col < 9) {
      u_int colorBGR = (ships[0][col] & bit) ? fgcolorBGR : COLOR_BLACK;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    row++;
    bit >>= 1;
  }
}

/* We draw four straight lines to simulate a scope */
void drawScope (u_char col, u_int fgcolorBGR)
{
  for (int count = 1; count < 4; count++) {
    drawPixel(col, 20 + count, fgcolorBGR);
    drawPixel(col, 20 - count, fgcolorBGR);
    drawPixel(col + count, 20, fgcolorBGR);
    drawPixel(col - count, 20, fgcolorBGR);
  }
}

/* We use a bitmap to draw the figure of our prey.
 * This figure has different states, so the parameter state decides
 * which is the one we are drawing */
void drawPrey (u_char rcol, u_char rrow, u_char state, u_int fgColorBGR)
{
  u_char col = 0;
  u_char row = 0;
  u_int bit = 0x80;

  lcd_setArea(rcol, rrow, rcol + 8, rrow + 7);
  while (row < 7) {
    while (col < 9) {
      u_int colorBGR = (ships[state+1][col] & bit) ? fgColorBGR : COLOR_BLACK;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    row++;
    bit >>= 1;
  }
}
