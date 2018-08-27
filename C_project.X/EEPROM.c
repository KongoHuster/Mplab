#include "EEPROM.h"
#include <xc.h>
#include "Display.h"
int key;

void initEEPROM()
{
   EEDATA = 0x00;            //���ݸ���ֵ
   EEADR = 0x00;             //��ַ����ֵ
}

void write_data()  
  {   int i;
    for(i=1;i<=0xFF;++i)
     { PIR2bits.EEIF=0;     
       EECON1bits.EEPGD=0; //���÷���Ŀ��ΪEEPROM
       EECON1bits.WREN=1;  //�������д����
       INTCONbits.GIE=0;   //��ֹ�ж�
       EECON2=0x55;       
       EECON2=0xAA;        //У��
       EECON1bits.WR=1;    //����һ��д����
       EECON1bits.WREN=0;  //�ر�д����
       EEADR=++EEADR;      //��ַ����
       EEDATA=++EEDATA;    //���ݵ��� 
      } 
   }
  
void read_display()
{ 
//  EEDATA=0x00;            //���ݸ���ֵ
//  EEADR=0x00;             //��ַ����ֵ
//  int j;
//  for (j=1;j<=0xFF;j++)
//     { EECON1bits.EEPGD=0; //���÷���Ŀ��ΪEEPROM
//       EECON1bits.RD=1;    //����һ�ζ�����
//       key =  EEDATL;       //����
//       delay();     //��ʱ
//       EEADR=++EEADR;      //��ַ����
//       EEDATA=++EEDATA;    //���ݵ���
    
    EEADRL = 0x00;
;
    EECON1bits.EEPGD=0; //���÷���Ŀ��ΪEEPROM
     EECON1bits.RD=1;
//     ADCON0bits.GO
//       EECON1bits.RD=1; 
//    asm("BCF EECON1, CFGS");
//    asm("BCF EECON1, EEPGD");
//    asm("BSF EECON1, RD");
    key = EEDATL;
     }
