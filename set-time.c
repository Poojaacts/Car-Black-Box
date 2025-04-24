/*
 * File:   set-time.c
 * Author: pooja
 *
 * Created on 16 July, 2024, 10:22 PM
 */

#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "ds1307.h"
#include "matrix_keypad.h"

extern char time[9],main_f;

void settime(void)
{
    static char hr,min,sec;
    static char once,field_flag,s_key,E_key,key_flag=0;
    static unsigned int blink;
    static int count2,wait=500;

    s_key=read_switches(LEVEL_CHANGE);
    
    if(!once) {
        clcd_print("Time       ",LINE1(0));
        clcd_print(time,LINE2(0));
        hr = ((time[0]-'0')*10)+(time[1]-'0');
        min = ((time[3]-'0')*10)+(time[4]-'0');
        sec = ((time[6]-'0')*10)+(time[7]-'0');
    }
    once=1;
    
    if(blink++ == 2000) 
    {
        if(field_flag==0) 
        {
            clcd_print("  ",LINE2(0));
        } else if (field_flag==1) 
        {
            clcd_print("  ",LINE2(3));
        } else if (field_flag==2) 
        {
            clcd_print("  ",LINE2(6));
        }
    }
    else if(blink == 4000)
    {
        clcd_putch((hr/10)+'0',LINE2(0));
        clcd_putch((hr%10)+'0',LINE2(1));
        clcd_putch(':',LINE2(2));
        clcd_putch((min/10)+'0',LINE2(3));
        clcd_putch((min%10)+'0',LINE2(4));
        clcd_putch(':',LINE2(5));
        clcd_putch((sec/10)+'0',LINE2(6));
        clcd_putch((sec%10)+'0',LINE2(7));
        blink=0;
    }
    
    
    E_key=read_switches(STATE_CHANGE);
    
    if(E_key== 5 && !key_flag) 
    {
        field_flag=(field_flag+1)%3;
        key_flag=1;       
    }
    else if (E_key!= 5)
        key_flag=0;
    

    if(E_key== 4) {
        if(field_flag==0) {
            hr=(hr+1)%24;
        } else if (field_flag==1) {
            min=(min+1)%60;
        } else if (field_flag==2) {
            sec=(sec+1)%60;
        }
       
    }
   
    if(s_key == 5)
        count2++;
    if(count2>=10000) {
        write_ds1307(HOUR_ADDR,(((hr/10)<<4)|(hr%10)));
        write_ds1307(MIN_ADDR,(((min/10)<<4)|(min%10)));
        write_ds1307(SEC_ADDR,(((sec/10)<<4)|(sec%10)));
    
        clcd_print("    Time  Set   ",LINE1(0));
        clcd_print("  Successfully  ",LINE2(0));
        
        if(!wait--) {
            once=0;
            key_flag=1;
            field_flag=0;
            wait=500;
            count2 = 0;
            main_f= 2;
            CLEAR_DISP_SCREEN;
        }
    }
}