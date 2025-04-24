/*
 * File:   change_pass.c
 * Author: pooja
 *
 * Created on 16 July, 2024, 6:38 PM
 */

#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "adc.h"
#include "isr.h"
#include "ext_eeprom.h"

unsigned char original_password[5];
extern char main_f;
extern unsigned char clear_flag;
void change_pass(char key)
{
    static unsigned int index2 = 0;
        clcd_print("New Password", LINE1(0));
        
       if (index2 < 4) 
    {
        if (key == 4) 
        {
            original_password[index2] = '1';
            clcd_putch('_',LINE2(index2));
            __delay_ms(500);
            clcd_putch('*',LINE2(index2));
            index2++;
         
                if(index2 == 4)
                    CLEAR_DISP_SCREEN;
        }
    
    if(key == 5)
    { 
        original_password[index2] = '0';
        clcd_putch('_',LINE2(index2));
        __delay_ms(500);
        clcd_putch('*',LINE2(index2));
        index2++;
        
        if(index2 == 4)
            CLEAR_DISP_SCREEN;
    }
    }
        if(index2 == 4)
        {
        for(int i = 0 ; i < 4; i++)
        {
            write_ext_eeprom(200 + i,original_password[i]);
        }
       
        CLEAR_DISP_SCREEN;
        clcd_print("PASSWORD CHANGED",LINE1(0));
        clcd_print("  SUCCESSFULLY  ",LINE2(0));
        __delay_ms(2000);
        main_f = 2;
        index2 = 0;
        }
}

