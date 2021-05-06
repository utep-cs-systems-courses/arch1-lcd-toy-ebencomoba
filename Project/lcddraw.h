/** \file lcddraw.h
 *  \brief Adapted from RobG's EduKit
 */

#ifndef lcddraw_included
#define lcddraw_included

/** Draw single pixel at col, row 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */
void drawPixel(u_char col, u_char row, u_int colorBGR);

/** Fill rectangle
 *
 *  \param colMin Column start
 *  \param rowMin Row start
 *  \param width Width of rectangle
 *  \param height height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, u_int colorBGR);

/** Clear screen (fill with color)
 *  
 *  \param colorBGR The color to fill screen
 */
void clearScreen(u_int colorBGR);

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
		     u_int fgColorBGR, u_int bgColorBGR);

/** 11x16 font - this function draws background pixels
 *  Adapted from RobG's EduKit
 */
void drawChar11x16(u_char col, u_char row, char c,
		   u_int fgColorBGR, u_int bgColorBGR);

/* Function draws an hexagon whose origin is (offset_c, offset_r)
 * The length of the hxagon is defined as the number of
 * pixels on the bottom side of the hexagon */
void drawHexagon(u_char offset_c, u_char offset_r, u_char length, u_int fgColorBGR);

/* Similarly to drawing a character, we draw the figure that
 * represents the spaceship based on a bitmap */
void drawSpaceShip(u_char rcol, u_int fgcolorBGR);

/* We draw four straight lines to simulate a scope */
void drawScope(u_char col, u_int fgcolorBGR);

/* We use a bitmap to draw the figure of our prey.
 * This figure has different states, so the parameter state decides
 * which is the one we are drawing */
void drawPrey(u_char col, u_char row, u_char state, u_int fgColorBGR);

#endif // included


