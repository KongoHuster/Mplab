/* 
 * File:   II2.h
 * Author: yizihong 
 *
 * Created on August 26, 2018, 8:13 PM
 */

#ifndef II2_H
#define	II2_H

#ifdef	__cplusplus
extern "C" {
    
#endif
#define uint8  unsigned char
#define uint16 unsigned int

extern void IIC_WriteACK(void);            //返回应答信号
extern void IIC_Stop(void);                //停止信号
extern void IIC_Writenoack(void);          //无应答信号
extern void IIC_Start(void);               //启动信号
extern void DelayUS(uint8 delay);          //微妙延时
extern void DelayMS(uint16 delay);         //毫秒延时
extern uint8 IIC_ReadByte(void);           //IIC读8位字节数据
extern uint8 IIC_WriteByte(uint8 data);    //IIC写8位字节数据
extern void Display(uint8 chosebit, uint8 data);
extern void IIC_Read_Mulit_Data(uint8 commond, uint8 address, uint8 *addrpoint, uint8 bytenum);
extern void IIC_Write_Mulit_Data(uint8 commond, uint8 reg_addr, uint8 *mdatapointer, uint8 bytenum);
 
extern void initII2();


#ifdef	__cplusplus
}
#endif

#endif	/* II2_H */

