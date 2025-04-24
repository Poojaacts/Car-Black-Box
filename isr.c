/*
 * File:   isr.c
 * Author: pooja
 *
 * Created on 9 July, 2024, 6:30 PM
 */

#include <xc.h>
#include "timer.h"

int dash_count = 5; 
void __interrupt() isr(void)
{
	static unsigned short count;
     
	if (TMR0IF)
	{
		TMR0 = TMR0 + 8;

		if (count++ == 20000)
		{
			count = 0;
            dash_count--;
		}
		TMR0IF = 0;
	}
}