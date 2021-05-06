#ifndef movement_included
#define movement_included

extern short ship_col;

/* This function increases the length of the hexagon by one and draws
   this bigger hexagon. Then, it erases the hexagon and starts again. 
   It does this for the two hexagons on our screen. */
void updateHexagon();

/* We move the prey horizontally. If we are in one of the limits, we change of
   sign the velocity so that in moves in the other direction.
   To update, we delete the current position of the prey using the background color
   and then draw it again with green */
void updatePreyCol(short prey_state);

/* Similarly, we draw the figure with black to delete it and draw it again with green
   to appear. Only in state 1, there is no horizontal movement.
   The last states, the figure of the prey changes to simulate being destroyed */
short updatePreyRow(short prey_state);

/* If we have not reached the right limit, we move the ship and scope to the right */
void moveShipR();

/* If we have not reached the left limit, we move the ship and scope to the left */
void moveShipL();

/* When shooting, this function changes to state 2, only if it is in state 1
   and the prey is in sight of the scope */
short shoot(short prey_state);

#endif
