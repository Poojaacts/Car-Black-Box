/*
 * File:   clear.c
 * Author: pooja
 *
 * Created on 16 July, 2024, 2:24 PM
 */


#include <xc.h>
#include "main.h"
#include "clcd.h"

extern char main_f;
extern unsigned char clear_flag;
void clear_log(void)
{
    static int a = 0;   //no of logs
    static int delay = 0;       //time
    if(a<10)
    {
        if(delay <= 300)
        {
            delay++;
            clcd_print("  Data Cleared  ",LINE1(0));
            if(delay == 300)
            {
                clear_flag = 0;
                a++;
                delay = 0;
            }
        }
    }
    else
    {
        a = 0;
        delay = 0;
        CLEAR_DISP_SCREEN;
        main_f = 2;
    }
}
