#include <xc.h>
#include "Display.h"

int key;
int pressCount;
int oldPin;


void portBInit()
{
    TRISB = 0xFF;
    ANSELB = 0x00;
    
    WPUB = 0xFF;
    OPTION_REG = OPTION_REG & 0b01111111;
    key = 0;
}

void keyMonitor()
{
    TRISB = TRISB & 0b11111110;
    //S6
    if(RB1 == 0)
    {
        key = 0x06;
        pressCount = 0x01;
        oldPin = 0x01;
    }
    
    //S4
    if(RB2 == 0)
    {
        key = 0x04;
        pressCount = 0x01;
        oldPin = 0x02;
    }
    
    //S2
    if(RB3 == 0)
    {
        key = 0x02;
        pressCount = 0x01;
        oldPin = 0x03;
    }
    
    TRISB = TRISB ^ 0b00000001;
    TRISB = TRISB & 0b11111101;
    //S3
    if(RB2 == 0)
    {
        key = 0x03;
        pressCount = 0x01;
        oldPin = 0x02;
    }
    
    //S1
    if(RB3 == 0)
    {
        key = 0x01;
        pressCount = 0x01;
        oldPin = 0x03;
    }
    
    TRISB = TRISB ^ 0b00000010;
    TRISB = TRISB & 0b11111011;
    //S5
    if(RB3 == 0)
    {
        key = 0x05;
        pressCount = 0x01;
        oldPin = 0x03;
    }
 
    TRISB = 0xFF;
    
    //S10
    if(RB0 == 0)
    {
        key = 0x0A;
        pressCount = 0x01;
        oldPin = 0x00;
    }
    
    //S9
    if(RB1 == 0)
    {
        key = 0x09;
        pressCount = 0x01;
        oldPin = 0x01;
    }
    
    //S8
    if(RB2 == 0)
    {
        key = 0x08;
        pressCount = 0x01;
        oldPin = 0x02;
    }
    
    //S7
    if(RB3 == 0)
    {
        key = 0x07;
        pressCount = 0x01;
        oldPin = 0x03;
    }
    

}
