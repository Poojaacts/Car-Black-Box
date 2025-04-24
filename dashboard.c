/*
 * File:   dashboard.c
 * Author: pooja
 *
 * Created on 6 July, 2024, 1:33 PM
 */


#include <xc.h>
#include "matrix_keypad.h"
#include "main.h"
#include "clcd.h"
#include "adc.h"
#include "ds1307.h"
#include "ext_eeprom.h"

unsigned char clock_reg[3];
unsigned char time[9]; 

unsigned char event[7][3] = {"GN ","GR ","G1 ","G2 ","G3 ","C "};
extern char main_f;

extern int speed;
extern unsigned char key;

unsigned int flag;
extern unsigned char clear_flag;
extern unsigned char overflow_flag;
extern unsigned char lap = 0;

void dashboard()
{
    //display logic
    clcd_print("TIME      EV SP",LINE1(0));
    get_time();
    
    clcd_print(time,LINE2(0));
    if(!flag)
    clcd_print("ON",LINE2(10));
    
    clcd_putch((speed/10)+48,LINE2(13));
    clcd_putch((speed%10)+48,LINE2(14));
    
    event_change();
    
}
static void get_time(void)
{
    clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

	if (clock_reg[0] & 0x40)
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	else
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	time[2] = ':';
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
	time[5] = ':';
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
	time[8] = '\0';

}

void event_change(void)
{
    flag=1;
    static unsigned int count=0;
    static unsigned int event_index = 0;
	unsigned char arr[10];
    
    if(key != ALL_RELEASED)
        {
            if(key == 1)
            {
                event_index = 5;
                read_data_to_eeprom(arr,time,event_index,speed);
                clear_flag = 1;
            }
            else if(key == 2)
            {
                if(event_index == 5)
                    event_index = 0;
                else if(event_index < 4)
                    event_index++;
                read_data_to_eeprom(arr,time,event_index,speed);
                clear_flag = 1;
            }
            else if(key == 3)
            {
                if(event_index == 5)
                    event_index = 0;
                else if(event_index > 0)
                    event_index--;
                read_data_to_eeprom(arr,time,event_index,speed);
                clear_flag = 1;
            }
            clcd_print(event[event_index],LINE2(10));
           // read_data_to_eeprom(arr,time,event[event_index],speed);
            if(key == 4)
            {
               CLEAR_DISP_SCREEN;
               main_f = 1; 
            }
        }
}

void read_data_to_eeprom(unsigned char *arr,unsigned char *time,int event_index,int value)
{
    unsigned char char1 = (value/10) + 48;
    unsigned char char2 = (value%10) + 48;
        arr[0] = time[0];
        arr[1] = time[1];
        arr[2] = time[3];
        arr[3] = time[4];
        arr[4] = time[6];
        arr[5] = time[7];
        arr[6] = event[event_index][0];
        arr[7] = event[event_index][1];
        arr[8] = char1;
        arr[9] = char2;
        for(int i = 0 ; i < 10; i++)
        {
            write_ext_eeprom(lap * 10 + i,arr[i]);
        }
        lap++;
        if(lap == 10)
        {
            lap = 0;
            overflow_flag = 1;
        }
        
}    



