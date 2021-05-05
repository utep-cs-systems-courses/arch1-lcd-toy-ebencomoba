#include "movement.h"
#include "lcdutils.h"
#include "lcddraw.h"

signed char prey_col_velocity = 1;
short prey_col = 50;
short ship_col = 20;
signed char prey_row = -10;
short next_prey_col = 50;

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

short selectPrey(short prey_state)
{
  switch (prey_state) {
  case 0:
  case 1:
  case 2:
    return 0;
  case 3:
    return 1;
  case 4:
    return 2;
  default:
    return 3;
  }
}

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

short updatePreyRow(short prey_state)
{
  switch(prey_state) {
  case 0:
    drawPrey(prey_col, prey_row, 0, COLOR_BLACK);
    drawPrey(prey_col, ++prey_row, 0, COLOR_GREEN);
    return (prey_row <= 17) ? 0 : 1;
  case 2:
    drawPrey(prey_col, prey_row, 0, COLOR_BLACK);
    drawPrey(prey_col, ++prey_row, 0, COLOR_GREEN);
    return (prey_row <= 40) ? 2 : 3;
  case 3:
    drawPrey(prey_col, prey_row, 1, COLOR_BLACK);
    drawPrey(prey_col, ++prey_row, 1, COLOR_GREEN);
    return 4;
  case 4:
    drawPrey(prey_col, prey_row, 2, COLOR_BLACK);
    drawPrey(prey_col, ++prey_row, 2, COLOR_GREEN);
    return 5;
  case 5:
    drawPrey(prey_col, prey_row, 3, COLOR_BLACK);
    drawPrey(prey_col, ++prey_row, 3, COLOR_GREEN);
    return 6;
  case 6:
    drawPrey(prey_col, prey_row, 3, COLOR_BLACK);
    prey_row = -10;
    return 0;
  }
  return 1;
}

void moveShipR()
{
  if (ship_col < 110) {
    drawSpaceShip(ship_col, COLOR_BLACK);
    drawScope(ship_col, COLOR_BLACK);
    ship_col+=2;
    drawSpaceShip(ship_col, COLOR_RED);
    drawScope(ship_col, COLOR_WHITE);
  }
}

void moveShipL()
{
  if (ship_col > 10) {
    drawSpaceShip(ship_col, COLOR_BLACK);
    drawScope(ship_col, COLOR_BLACK);
    ship_col-=2;
    drawSpaceShip(ship_col, COLOR_RED);
    drawScope(ship_col, COLOR_WHITE);
  }
}
