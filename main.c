/*
 * File:   main.c
 * Author: pooja
 * 
 * Created on 6 July, 2024, 1:24 PM
 */


#include <xc.h>
#include "main.h"
#include "adc.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "isr.h"
#include "ds1307.h"
#include "ext_eeprom.h"
#include "uart.h"
#include "timer.h"

void init_config()
{
    init_clcd();
    init_adc();
    init_matrix_keypad();
    init_timer();
    init_i2c();
    init_ds1307();
}
int speed;
char main_f = 0,menu_f = 0;
unsigned char clear_flag;
unsigned char key;
unsigned char overflow_flag;
unsigned char lap = 0;

void main(void)
{
  init_config(); 
    
    while (1)
    {
        /*
         * get the time 
         * based on switch press change the event
         */
        speed = read_adc(CHANNEL4)/10.33;
        key = read_switches(STATE_CHANGE);
        
        
        if(main_f == DASHBOARD)
        {
            dashboard();
        }
       else if(main_f == PASSWORD)
        {
            password(key);       
        }
        else if(main_f == MENU)
        {
            menu();
        }
       else if(main_f == MENU_ENTER)
        {
            if(menu_f == VIEWLOG)
            {
                view_log(key);
            }
            else if(menu_f == DOWNLOADLOG)
            {
                download_log(key);
            }
            else if(menu_f == CLEARLOG)
            {
                clear_log();
            }
            else if(menu_f == SETTIME)
            {
                settime();
            }
            else if(menu_f == CHANGEPASS)
            {
                change_pass(key);
            }
        }
        
    }
   return;
}
