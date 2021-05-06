## Project 3

### Game
This is a little game where you control a spaceship that has a target attached
to it. You can move the spaceship to the left and right of the screen. There
is also a prey that you are hunting (enemy spaceships) They appear from below
up to your range. Once you shoot, the red led will turn on, you will hear a
sound indicating fire and if you hit your prey, the prey will fall and
collapse.
Additionally, there is a string of text that says that you can start shooting
and two animated hexagons at its sides.

#### Animation
Your ship and scope can move horizontally. Your prey is always moving
horizontally and can move vertically, as well as an animation of
disappearing. And two hexagons are constantly growing in size and then
disappearing.

#### Sound
When you shoot, you can hear a sound, emulating that your ships is shooting.

#### ASCII Characters
There is a simple message in the middle of the screen.

#### Buttons
You can move your ship to the left with switch1, to the right with switch2 and
shoot with switch4.

#### Figures
The spaceships are taken from bitmaps I created. And I rendered the hexagons
and the scope with other two simple algorithms.

#### Interrupts and sleep
The CPU is turned off until we have to update something on the screen.
