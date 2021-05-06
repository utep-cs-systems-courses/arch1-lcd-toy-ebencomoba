#include "movement.h"
#include "lcdutils.h"
#include "lcddraw.h"

signed char prey_col_velocity = 2;
short prey_col = 50;
short ship_col = 50;
signed char prey_row = -10;
short next_prey_col = 50;

/* This function increases the length of the hexagon by one and draws
   this bigger hexagon. Then, it erases the hexagon and starts again. 
   It does this for the two hexagons on our screen. */
void updateHexagon()
{
  static short hex_length = 0;
  if (hex_length++ >= 6) {
    drawHexagon(15, 77, hex_length, COLOR_BLACK);
    drawHexagon(110, 77, hex_length, COLOR_BLACK);
    hex_length = 0;
  }
  drawHexagon(15, 77, hex_length, COLOR_CYAN);
  drawHexagon(110, 77, hex_length, COLOR_CYAN);
}

/* Based on the state of the prey, this function determines
   which prey ship should be selected to be drawn */
short selectPrey(short prey_state)
{
  switch (prey_state) {
  case 0:
  case 1:
  case 2:
    return 0;
  case 3:
  case 4:
    return 1;
  case 5:
  case 6:
    return 2;
  default:
    return 3;
  }
}

/* We move the prey horizontally. If we are in one of the limits, we change of
   sign the velocity so that in moves in the other direction.
   To update, we delete the current position of the prey using the background color
   and then draw it again with green */
void updatePreyCol(short prey_state)
{
  prey_col = next_prey_col;
  next_prey_col += prey_col_velocity;
  if (next_prey_col < 10 || next_prey_col > 110) {
    prey_col_velocity = -prey_col_velocity;
    next_prey_col += prey_col_velocity;
  }
  drawPrey(prey_col, prey_row, selectPrey(prey_state), COLOR_BLACK);
  drawPrey(next_prey_col, prey_row, selectPrey(prey_state), COLOR_GREEN);
}

/* Similarly, we draw the figure with black to delete it and draw it again with green
   to appear. Only in state 1, there is no horizontal movement.
   The last states, the figure of the prey changes to simulate being destroyed */
short updatePreyRow(short prey_state)
{
  switch(prey_state) {
  case 0:
    drawPrey(next_prey_col, prey_row, 0, COLOR_BLACK);
    drawPrey(next_prey_col, ++prey_row, 0, COLOR_GREEN);
    return (prey_row <= 17) ? 0 : 1;
  case 2:
    drawPrey(next_prey_col, prey_row, 0, COLOR_BLACK);
    drawPrey(next_prey_col, ++prey_row, 0, COLOR_GREEN);
    return (prey_row <= 40) ? 2 : 3;
  case 3:
    drawPrey(next_prey_col, prey_row, 1, COLOR_BLACK);
    drawPrey(next_prey_col, ++prey_row, 1, COLOR_GREEN);
    return 4;
  case 4:
    drawPrey(next_prey_col, prey_row, 1, COLOR_BLACK);
    drawPrey(next_prey_col, ++prey_row, 1, COLOR_GREEN);
    return 5;
  case 5:
    drawPrey(next_prey_col, prey_row, 1, COLOR_BLACK);
    drawPrey(next_prey_col, ++prey_row, 1, COLOR_GREEN);
    return 6;
  case 6:
    drawPrey(next_prey_col, prey_row, 2, COLOR_BLACK);
    drawPrey(next_prey_col, ++prey_row, 2, COLOR_GREEN);
    return 7;
  case 7:
    drawPrey(next_prey_col, prey_row, 1, COLOR_BLACK);
    drawPrey(next_prey_col, ++prey_row, 1, COLOR_GREEN);
    return 8;
  case 8:
    drawPrey(next_prey_col, prey_row, 3, COLOR_BLACK);
    drawPrey(next_prey_col, ++prey_row, 3, COLOR_GREEN);
    return 9;
  case 9:
    drawPrey(next_prey_col, prey_row, 3, COLOR_BLACK);
    prey_row = -10;
    return 0;
  }
  return 1;
}

/* If we have not reached the right limit, we move the ship and scope to the right */
void moveShipR()
{
  if (ship_col < 110) {
    drawSpaceShip(ship_col, COLOR_BLACK);
    drawScope(ship_col, COLOR_BLACK);
    ship_col+=3;
    drawSpaceShip(ship_col, COLOR_RED);
    drawScope(ship_col, COLOR_WHITE);
  }
}

/* If we have not reached the left limit, we move the ship and scope to the left */
void moveShipL()
{
  if (ship_col > 10) {
    drawSpaceShip(ship_col, COLOR_BLACK);
    drawScope(ship_col, COLOR_BLACK);
    ship_col-=3;
    drawSpaceShip(ship_col, COLOR_RED);
    drawScope(ship_col, COLOR_WHITE);
  }
}

/* We draw again the scope so that it is not erased by the movement of the prey */
void keepScope()
{
  drawScope(ship_col, COLOR_WHITE);
}

/* When shooting, this function changes to state 2, only if it is in state 1
   and the prey is in sight of the scope */
short shoot(short prey_state)
{
  short range = (ship_col+4) >= next_prey_col;
  range &= (ship_col+4) <= (next_prey_col+9);
  return ((prey_state == 1) && range) ? 2 : prey_state;
}
