/* 
 * File:   main.c
 * Author: yizihong
 *
 * Created on August 25, 2018, 12:22 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "Display.h"
#include "Keydriver.h"
#include "EEPROM.h"
#include  "II2.h"


// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = ECH       // Oscillator Selection (ECH, External Clock, High Power Mode (4-32 MHz): device clock supplied to CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = ON      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable bit (Vcap functionality is disabled on RA6.)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low Power Brown-Out Reset Enable Bit (Low power brown-out is disabled)
#pragma config LVP = OFF         // Low-Voltage Programming Enable (Low-voltage programming enabled)
/*
 *  This is main function of this project
 */

int key;
uint8 init[8] = {0x59, 0x43, 0x21, 0x11, 0x03, 0x03, 0x09, 0x00}; 
uint8 recive[2]; 

//int main(int argc, char** argv) {
//    
//    initDisplay();
//    portBInit();
//    initEEPROM();
////    read_display();
//    key = eeprom_read(0x00);
////    void my_printf(int a = 1 , int b = 2, int c = 3, int d = 4);
//    while(1)
//    {
//        display();
//        keyMonitor();
//        
//    }
//    return (EXIT_SUCCESS);
//}

int main(int argc, char** argv) {
    
    initDisplay();
    portBInit();
    initEEPROM();
//    read_display();
    key = eeprom_read(&key);
//    void my_printf(int a = 1 , int b = 2, int c = 3, int d = 4);
//    while(1)
//    {
//        display();
//        keyMonitor();
//        
//    }
    initII2();
//    IIC_Write_Mulit_Data(0x0091, 0x00, init, 1);  //写8字节数据
    DelayMS(5);
    while(1)
    {

//        keyMonitor();
        IIC_Read_Mulit_Data(0x0090, 0x00, recive, 3); //读8字节数据
        my_printf(table[init[0] / 16], table[init[0] % 16], table[recive[0] / 16], table[recive[0] % 16]);
        display();
        DelayMS(1);
    }

    return (EXIT_SUCCESS);
}

