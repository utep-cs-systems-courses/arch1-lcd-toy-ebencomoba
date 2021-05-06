#ifndef switches_included
#define switches_included

#define SW0 BIT0
#define SW1 BIT1
#define SW2 BIT2
#define SW3 BIT3
#define SWITCHES (SW0 | SW1 | SW2 | SW3)	/* We use the four switches */

static char switch_update_interrupt_sense(); /* Updates interrupt senses to save battery */
void switch_init();                          /* Initializes switches */
void switch_interrupt_handler();             /* Updates switches dependant variables */

extern char switch0_down, switch1_down, switch2_down, switch3_down;
extern char button_pressed; /* effectively boolean */

#endif // included
