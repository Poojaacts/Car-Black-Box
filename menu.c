/*
 * File:   menu.c
 * Author: pooja
 *
 * Created on 11 July, 2024, 1:13 PM
 */


#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "ext_eeprom.h"
#include <string.h>

extern char main_f;
extern char menu_f;
unsigned char menu_log[5][17] = {"View Log        ","Download Log    ","Clear Log       ","Set Time        ","ChangePassword"};
unsigned char menu_i = 0,ar_i = 0;  // menu index and arrow index
void menu()
{
    //CLEAR_DISP_SCREEN;
    clcd_putch(' ',LINE1(1));
    clcd_print(menu_log[menu_i],LINE1(2));
    clcd_print(menu_log[menu_i+1],LINE2(2));
    if(ar_i == 0)
    {
        clcd_putch(0x7E,LINE1(0));
        clcd_putch(' ',LINE2(0));
    }
    else
    {
      clcd_putch(' ',LINE1(0));
      clcd_putch(0x7E,LINE2(0));  
    }
    
    unsigned char key1 = read_switches(LEVEL_CHANGE);
    
    static int count1 = 0,count2 = 0;
    if(key1 == 5 )
    {
        count1++;
        if(count1 > 500)
        {
            count1=0;
         CLEAR_DISP_SCREEN;
         main_f = 0;
        }
    }
    else if (count1 < 200 && count1 > 0) {
        count1 = 0;
        if (ar_i == 0) {
            ar_i = 1;
        } else if (menu_i < 3) {
            menu_i++;
        }
    }
    
    if (key1 == 4) 
    {
        count2++;
        if (count2 > 500)
        {
            count2 = 0;
                CLEAR_DISP_SCREEN;
                main_f = MENU_ENTER;
                menu_f = menu_i + ar_i; 
        }
    } 
    else if (count2 < 200 && count2 > 0)
    {
        count2 = 0;
        if (ar_i == 1) {
            ar_i = 0;
        } else if (menu_i > 0) {
            menu_i--;
        }
    }
}
