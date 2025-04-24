/*
 * File:   password.c
 * Author: pooja
 *
 * Created on 9 July, 2024, 12:51 PM
 */

#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "adc.h"
#include "ext_eeprom.h"
#include <string.h>
#include "isr.h"

unsigned char original_password[5] = "1111";
unsigned int pas_flag;
extern char main_f;

void password(char key) {
    static char password[5];
    static unsigned int i;
    static unsigned char index = 0;
    static unsigned int attempt = 3;

    int sec = 180;

    if (!pas_flag) {
        CLEAR_DISP_SCREEN;
        pas_flag = 1;
    }
    if (index < 4)
        clcd_print("Enter Password", LINE1(0));
    static int a = 0;
    static int j = 0;
    static int delay_flag = 1;
    if (a < 10) {
        if (j <= 1000) {
            j++;
            if (j == 1000) {
                a++;
                j = 0;
            }
        }
    } else {
        a = 0;
        j = 0;
        main_f = 0;
    }
    if (delay_flag) {
        if (index < 4) {
            if (key == 4) {
                password[index] = '1';
                clcd_putch('_', LINE2(index));
                __delay_ms(500);
                clcd_putch('*', LINE2(index));
                index++;
                delay_flag = 1;
                a = 0;
                if (index == 4)
                    CLEAR_DISP_SCREEN;
            }

            if (key == 5) {
                password[index] = '0';
                clcd_putch('_', LINE2(index));
                __delay_ms(500);
                clcd_putch('*', LINE2(index));
                index++;
                delay_flag = 1;
                a = 0;
                
               /* if (index == 4)
                    CLEAR_DISP_SCREEN;*/
            }

            if (index == 4) {
                if (!strcmp(password, original_password)) {
                    CLEAR_DISP_SCREEN;
                clcd_print("Password Matched", LINE1(0));
                clcd_print("  Successfully  ",LINE2(0));
                __delay_ms(1000);
                CLEAR_DISP_SCREEN;
                    index = 0;
                    main_f = 2;
                } else {
                    CLEAR_DISP_SCREEN;
                    clcd_print("Wrong Password", LINE1(0));
                    clcd_print("Attempt left=", LINE2(0));
                    attempt--;
                    index = 0;
                    clcd_putch((attempt + '0'), LINE2(14));
                    __delay_ms(1000);
                    for (unsigned long int l = 500000; l--;);
                    CLEAR_DISP_SCREEN;
                }

                if (attempt == 0) {
                    clcd_print("You Are Blocked", LINE1(0));
                    clcd_print("Wait For   Sec", LINE2(0));
                    while (sec) {
                        clcd_putch((sec / 100) % 10 + '0', LINE2(9));
                        clcd_putch((sec / 10) % 10 + '0', LINE2(10));
                        clcd_putch((sec % 10) + '0', LINE2(11));
                        __delay_ms(1000);
                        sec--;
                    }
                    sec = 180;
                    index = 0;
                    attempt = 3;
                    CLEAR_DISP_SCREEN;
                    return;
                }
            }
        }
    }
}