/*
 * File:   ext_eeprom.c
 * Author: pooja
 *
 * Created on 10 July, 2024, 5:25 PM
 */


#include <xc.h>
#include "main.h"
#include "ext_eeprom.h"



/* 
 * DS1307 Slave address
 * D0  -  Write Mode
 * D1  -  Read Mode
 */
/*void init_ext_eeprom()
{
    init_clcd();
    init_i2c();
    
   // clcd_print("YASH",LINE1(0));
}
*/
void write_ext_eeprom(unsigned char address, unsigned char data)
{
	i2c_start();
	i2c_write(SLAVE_WRITE);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
    for(int i=3000;i--;); //we need to give some time to write the data
}

unsigned char read_ext_eeprom(unsigned char address)
{
	unsigned char data;

	i2c_start();
	i2c_write(SLAVE_WRITE);
	i2c_write(address);
	i2c_rep_start();
	i2c_write(SLAVE_READ);
	data = i2c_read();
	i2c_stop();

	return data;
}