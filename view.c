/*
 * File:   view.c
 * Author: pooja
 *
 * Created on 11 July, 2024, 6:45 PM
 */


#include <xc.h>
#include "clcd.h"
#include "matrix_keypad.h"
#include "main.h"
#include "ext_eeprom.h"

extern char main_f, menu_f;
unsigned int i;
extern unsigned char lap;
extern unsigned char overflow_flag;
extern unsigned char clear_flag;

void view_log(char key)
{
    static char i=0;
    if(lap==0 && overflow_flag==0)
        clcd_print("  Empty list  ", LINE1(1));
    
    if(key == 5 )
    {
        if(overflow_flag)
        {
            if(i<9)
                i++;
        }
        else if(i<lap-1)
            i++;
    }
    
    else if(key == 4)
    {
        if(i>0)
            i--;
    }
    unsigned int key1 = read_switches(LEVEL_CHANGE);
    static int count  = 0;
    if(key1 == 5)
    {
        count++;
        if(count == 300)
        {
            count = 0;
            CLEAR_DISP_SCREEN;
            main_f = 2;
        }
    }
    
    if(lap || overflow_flag)
    {  
    clcd_print("#   TIME   EV SP", LINE1(0));
    clcd_putch((i+0)+48, LINE2(0));
    clcd_print(" ", LINE2(1));
    clcd_putch(read_ext_eeprom(i*10+0), LINE2(2));
    clcd_putch(read_ext_eeprom(i*10+1), LINE2(3));
    clcd_print(":", LINE2(4));
    clcd_putch(read_ext_eeprom(i*10+2), LINE2(5));
    clcd_putch(read_ext_eeprom(i*10+3), LINE2(6));
    clcd_print(":", LINE2(7));
    clcd_putch(read_ext_eeprom(i*10+4), LINE2(8));
    clcd_putch(read_ext_eeprom(i*10+5), LINE2(9));
    clcd_print(":", LINE2(10));
    clcd_putch(read_ext_eeprom(i*10+6), LINE2(11));
    clcd_putch(read_ext_eeprom(i*10+7), LINE2(12));
    clcd_print(":", LINE2(13));
    clcd_putch(read_ext_eeprom(i*10+8), LINE2(14));
    clcd_putch(read_ext_eeprom(i*10+9), LINE2(15));
    }
}