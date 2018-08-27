/* 
 * File:   Display.h
 * Author: yizihong
 *
 * Created on August 25, 2018, 12:23 PM
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#ifdef	__cplusplus
extern "C" {


    
#endif

void initDisplay();

void display();

void delay();

void my_printf(int a, int b, int c, int d);

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
#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */

