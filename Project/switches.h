#ifndef switches_included
#define switches_included

#define SW0 BIT0
#define SW2 BIT2
#define SW3 BIT3                        /* We only use three switches */
#define SWITCHES (SW0 | SW2 | SW3)	/* Since switch1 does not work properly */

static char switch_update_interrupt_sense(); /* Updates interrupt senses to save battery */
void switch_init();                          /* Initializes switches */
void switch_interrupt_handler();             /* Updates switches dependant variables */

extern char switch0_down, switch2_down, switch3_down;
extern char button_pressed; /* effectively boolean */

#endif // included
