/*
 * File:   timer.c
 * Author: pooja
 *
 * Created on 9 July, 2024, 6:29 PM
 */


#include <xc.h>
#include "timer.h"

void init_timer(void)
{
	

/*Setting 8 bit timer register*/
	T08BIT = 1;

/* Selecting internal clock source */
	T0CS = 0;

/* Enabling timer0*/
	TMR0ON = 0;

/* disabling prescaler*/
	PSA = 1;

	TMR0 = 6;

	/* Clearing timer0 overflow interrupt flag bit */
	TMR0IF = 0;

	/* Enabling timer0 overflow interrupt */
	TMR0IE = 1;
}
