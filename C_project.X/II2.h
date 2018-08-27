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

extern void IIC_WriteACK(void);            //����Ӧ���ź�
extern void IIC_Stop(void);                //ֹͣ�ź�
extern void IIC_Writenoack(void);          //��Ӧ���ź�
extern void IIC_Start(void);               //�����ź�
extern void DelayUS(uint8 delay);          //΢����ʱ
extern void DelayMS(uint16 delay);         //������ʱ
extern uint8 IIC_ReadByte(void);           //IIC��8λ�ֽ�����
extern uint8 IIC_WriteByte(uint8 data);    //IICд8λ�ֽ�����
extern void Display(uint8 chosebit, uint8 data);
extern void IIC_Read_Mulit_Data(uint8 commond, uint8 address, uint8 *addrpoint, uint8 bytenum);
extern void IIC_Write_Mulit_Data(uint8 commond, uint8 reg_addr, uint8 *mdatapointer, uint8 bytenum);
 
extern void initII2();


#ifdef	__cplusplus
}
#endif

#endif	/* II2_H */

