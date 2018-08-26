#include "Display.h"
#include <xc.h>

//int table[10];
const int table[11] = {0x3F,  //0
                          0x06,  //1
                          0x5B,  //2
                          0x4F,  //3
                          0x66,  //4
                          0x6D,  //5
                          0x7D,  //6
                          0x07,  //7
                          0x7F,  //8
                          0x67,  //9
                          0x80   //10
                            };
extern int lowCount = 8;
extern int highCount = 4;
extern int key = 5;
extern int type = 2;
void delay();



void initDisplay()
{
    //init PORTA
   	PORTA = 0x00;
    TRISA = 0x00;
    ANSELA = 0x00;
    
    PORTC = 0x00;
    TRISC = 0x00;
    
    OPTION_REG = 0x07;
    OSCCON = 0x22;
    
    INTCON = 0xA0;
    return;
}

void display()
{

    PORTC = 0xFD;
    delay();
    PORTA = table[key];
    
    PORTC = 0xFE; 
    delay();
    PORTA = table[type];
    
    PORTC = 0xFB;
    delay();
    PORTA = table[highCount];
    
    PORTC = 0xF7;
    delay();
    PORTA = table[lowCount];
    return;
}

void delay()
{
    int i = 5;
    while(i--);
    return;
}


