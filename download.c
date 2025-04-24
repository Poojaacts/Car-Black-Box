/*
 * File:   download.c
 * Author: pooja
 *
 * Created on 15 July, 2024, 10:18 PM
 */


#include <xc.h>
#include "main.h"
#include "uart.h"
#include "ext_eeprom.h"
#include "clcd.h"

extern char main_f;
extern unsigned char clear_flag;

void download_log(char key)
{
    unsigned char arr3[11] = {};
    static int lap2; 
    static int a = 0; //no of logs
    static int j=0; //time
    init_uart();
    if(clear_flag)
    {
   
   // if(key ==1 || key ==2 || key==3)
     //   count++;
    if(a < 10)
    {
        if(j <= 1000)
        {
            j++;
            clcd_print("DISPLAYED DATA ",LINE1(0));
	        clcd_print("  SUCCESSFULLY  ",LINE2(0));
            if(j == 1000)
            {
            a++;
            j = 0;
            }
        }
    }
    else
    {
        a = 0;
        j = 0;
        CLEAR_DISP_SCREEN;
        main_f = 2;
    }
    if(lap2 <= 10)
    {
    for(int i = 0; i<10; i++)
    {
    arr3[i] = read_ext_eeprom(lap2 * 10 + i);
    }
        puts(arr3);
        puts("\n\r");  
        lap2++;        
    }
    }
    else
    {
        clcd_print("  DATA EMPTY  ",LINE1(0));
    __delay_ms(5000);
    main_f = 2;
    }
}
