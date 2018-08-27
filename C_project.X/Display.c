#include "Display.h"
#include <xc.h>

//int table[10];

extern int lowCount = 5;
extern int highCount = 7;
extern int key;
extern int type = 1;
void delay();



void initDisplay()
{
    //init PORTA
   	PORTA = 0x00;
    LATA =0x00;

    ANSELA = 0x00;
    TRISA = 0x00;
        
    PORTC = 0x00;
    TRISC = 0x00;
    
    LATC = 0x00;
//    ANSELC = 
    
    OPTION_REG = 0x07;
    OSCCON = 0x22;
    
    INTCON = 0xA0;
    return;
}

void display()
{
//    delay();
    PORTA = table[highCount];
    PORTC = 0xFB;
    delay();
    
    PORTA = table[key];
    PORTC = 0xFD;

    delay();
    
    PORTA = table[type];
    PORTC = 0xFE; 

    delay();
    
    PORTA = table[lowCount];
    PORTC = 0xF7;

    delay();
//     delay();
    return;
}

void delay()
{
    int i = 2;
    while(i--);
    return;
}


void my_printf(int a, int b, int c, int d)
{
    key = a;
    type = b;
    highCount = c;
    lowCount = d;
    return;
}