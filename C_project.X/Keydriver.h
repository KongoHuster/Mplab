/* 
 * File:   Keydriver.h
 * Author: yizihong
 *
 * Created on August 25, 2018, 10:04 PM
 */

#ifndef KEYDRIVER_H
#define	KEYDRIVER_H

#ifdef	__cplusplus
extern "C" {
    void portBInit();
    
    void keyMonitor();
   
    extern int pressCount;
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* KEYDRIVER_H */

