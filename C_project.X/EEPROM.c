#include "EEPROM.h"
#include <xc.h>
#include "Display.h"
int key;

void initEEPROM()
{
   EEDATA = 0x00;            //数据赋初值
   EEADR = 0x00;             //地址赋初值
}

void write_data()  
  {   int i;
    for(i=1;i<=0xFF;++i)
     { PIR2bits.EEIF=0;     
       EECON1bits.EEPGD=0; //设置访问目标为EEPROM
       EECON1bits.WREN=1;  //允许进行写操作
       INTCONbits.GIE=0;   //禁止中断
       EECON2=0x55;       
       EECON2=0xAA;        //校验
       EECON1bits.WR=1;    //启动一次写操作
       EECON1bits.WREN=0;  //关闭写操作
       EEADR=++EEADR;      //地址递增
       EEDATA=++EEDATA;    //数据递增 
      } 
   }
  
void read_display()
{ 
//  EEDATA=0x00;            //数据赋初值
//  EEADR=0x00;             //地址赋初值
//  int j;
//  for (j=1;j<=0xFF;j++)
//     { EECON1bits.EEPGD=0; //设置访问目标为EEPROM
//       EECON1bits.RD=1;    //启动一次读操作
//       key =  EEDATL;       //送显
//       delay();     //延时
//       EEADR=++EEADR;      //地址递增
//       EEDATA=++EEDATA;    //数据递增
    
    EEADRL = 0x00;
;
    EECON1bits.EEPGD=0; //设置访问目标为EEPROM
     EECON1bits.RD=1;
//     ADCON0bits.GO
//       EECON1bits.RD=1; 
//    asm("BCF EECON1, CFGS");
//    asm("BCF EECON1, EEPGD");
//    asm("BSF EECON1, RD");
    key = EEDATL;
     }
