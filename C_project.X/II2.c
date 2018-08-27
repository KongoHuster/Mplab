#include <xc.h>
#include "II2.h"
    
/********************����������************************************************/
 
#define     IIC_SCLK    RC2     //24C02ʱ����
#define     IIC_SDAT    RC3     //24C02������
 
/********************����ȫ�ֱ���**********************************************/


/*******************************************************************************
* �� �� ��: DelayUS(uint8 delay)
* ��������: ΢����ʱ    for 20MHZ
* ��ڲ���: delay
* ��    ��: ��
*******************************************************************************/
 
void DelayUS(uint8 delay)
{
    while(--delay);
}
 
/*******************************************************************************
* �� �� ��: DelayMS(uint16 delay)
* ��������: ������ʱ    for20MHZ
* ��ڲ���: delay
* ��    ��: ��
*******************************************************************************/
 
void DelayMS(uint16 delay)
{
    uint16 i;
    for(; delay > 0; delay--)
        for(i = 0; i < 453; i++);
}
 
/******************************************************************************
* �� �� ��: IIC_WriteACK(void)
* ��������: �ӻ�������������ʱ������������Ӧ���ź�
* ��ڲ���: ��
* ��    ��: ��
*******************************************************************************/
 
void IIC_WriteACK(void)
{
    TRISC4 = 0;
    
    IIC_SDAT = 0; 
    DelayUS(4);
    IIC_SCLK = 1;
    IIC_SCLK = 0;
    TRISA1=1;
//    IIC_SDAT = 0;           //����������,����������һ���͵�ƽ
//    IIC_SCLK = 1;           //ʱ����Ч����������
//    DelayUS(4);
//    IIC_SCLK = 0;
//    TRISC4 = 1;
//    //    IIC_SDAT = 1;
}
 
/******************************************************************************
* �� �� ��: IIC_Writenoack(void)
* ��������: �ӻ��������ݽ���ʱ��������������Ӧ���ź�
* ��ڲ���: ��
* ��    ��: ��
*******************************************************************************/
 
void IIC_Writenoack(void)
{
    TRISC4 = 0;
    IIC_SCLK = 0;
    IIC_SDAT = 1;
    IIC_SCLK = 1;
    IIC_SCLK = 0;
//    IIC_SCLK = 0;
//    DelayUS(2);
//    IIC_SDAT = 1;         //���͸ߵ�ƽ����ʾ��Ӧ��
//    DelayUS(2);
//    IIC_SCLK = 1;         //ʱ����Ч
//    DelayUS(2);
//    IIC_SCLK = 0;
    TRISC4 = 1;
}
 
/******************************************************************************
* �� �� ��: IIC_Start(void)
* ��������: ����EEPROM��д����
* ��ڲ���: ��
* ��    ��: ��
*******************************************************************************/
 
void IIC_Start(void)
{
    TRISC4 = 0;
    IIC_SDAT = 1;         //��������λ

    IIC_SCLK = 1;         //ʱ����Ч
    DelayUS(4);
    IIC_SDAT = 0;         //�����߸�λ����ʱ����Ч�ڼ䣬�����߲���һ���½��ر�ʾ����EEPROM��д����
    DelayUS(4);
    IIC_SCLK = 0;         //ʱ����Ч

     TRISC4 = 1;
    NOP();
    NOP();
}
 
/******************************************************************************
* �� �� ��: IIC_Stop(void)
* ��������: ֹͣ��EEPROM��д����
* ��ڲ���: ��
* ��    ��: ��
*******************************************************************************/
 
void IIC_Stop(void)
{
    TRISC4 = 0;
    IIC_SDAT = 0;         //�����߸�λ
    IIC_SCLK = 0;         //ʱ����Ч
    DelayUS(4);
    IIC_SDAT = 1;         //�����߸�λ
    IIC_SCLK = 1;         //��������λ����ʱ����Ч�ڼ䣬�����߲���һ�������ر�ʾֹͣEEPROM��д����
    DelayUS(4);
     
}
 
/******************************************************************************
* �� �� ��: IIC_WriteByte(uint8 wdata)
* ��������: ����8λ�ֽ�����д����
* ��ڲ���: wdata��д����
* ��    ��: status:0:�ɹ� 1��ʧ��
*******************************************************************************/
uint8 IIC_WriteByte(uint8 wdata)
{
     
    uint8 i, status;
    IIC_SCLK = 0;                   //ʱ����Ч
    TRISC4=0;

    for(i = 0; i < 8; i++)              //д8λ�ֽ�����
    {
        if((wdata & 0x80) == 0x80)  //�����λ����
        {        
            IIC_SDAT = 1;
          
        }
        else
        {
            IIC_SDAT = 0;
            
        }
        DelayUS(4); 
        IIC_SCLK = 1;           //ʱ    ����Ч
        
        wdata <<= 1;            //��������һλ
        DelayUS(4); 
        IIC_SCLK = 0;
        DelayUS(2);
    }
     IIC_SCLK = 0;       //ʱ����Ч
    TRISC4 = 1;         //����������Ϊ����ģʽ

    DelayUS(2);
    IIC_SCLK = 1;       //????
    DelayUS(2); 
    NOP();
    NOP();
    NOP();
    if(IIC_SDAT)        //�ھŸ�ʱ������Ϊ1����дʧ�ܳɹ���IIC����û��Ӧ��
    {
        status = 1;
    }
    else
    {
        status = 0;
    }
    IIC_SCLK = 0;
    TRISC4 = 0;         //���������û����ģʽ
    return status;      //����д�ɹ����״̬
}
 
/******************************************************************************
* �� �� ��: IIC_WriteData(uint8 commond,uint8 reg_addr,*mdatapointer,uint8 bytenum)
* ��������: д���ֽ�����
* ��ڲ���: commond����дָ�reg_addrд������ַ��mdata��д����,bytenum�ֽ���
* ��    ��: ��
*******************************************************************************/
//void IIC_Write_Mulit_Data(uint8 commond, uint8 reg_addr, uint8 *mdatapointer, uint8 bytenum)
//{
//    uint8 i, status;
//    IIC_Start();    //����IIC
//    status = IIC_WriteByte(commond);    //д������ַ
//    if(!status)
//    {
//        status = IIC_WriteByte(reg_addr);   //д�Ĵ�����ַ
//    }
//    for(i = 0; i < bytenum; i++)
//    {
//        if(!status)
//        {
//            status = IIC_WriteByte(*(mdatapointer + i));        //д����
//        }
//    }
//    IIC_Stop();     //����IIC
//}
 
/******************************************************************************
* �� �� ��: IIC_ReadByte(void)
* ��������: 8λ���ݶ�����
* ��ڲ���: ��
* ��    ��: bytedata��ȡ��8λ����
*******************************************************************************/
uint8 IIC_ReadByte(void)
{
    uint8 i, bytedata = 0;
    TRISC4 = 1;     //����������Ϊ����ģʽ
    IIC_SDAT = 1;   //����������
//    DelayUS(2);
//    IIC_SCLK = 0;
//    DelayUS(2);
    for(i = 0; i < 8; i++)      //��8λ����
    {
//        IIC_SCLK = 0;
//        DelayUS(2);
//        bytedata <<= 1;
//        bytedata |= IIC_SDAT;
//        IIC_SCLK = 0;
//        DelayUS(2);
//        NOP();
        NOP();
        IIC_SCLK = 0;
        DelayUS(4);
        IIC_SCLK = 1;
        NOP();
        NOP();
        bytedata <<= 1;
        bytedata |= IIC_SDAT;
        
        NOP();
        NOP();
    }
    TRISC4 = 0;     //���������û����ģʽ
    return(bytedata);//��������
}
 
/******************************************************************************
* �� �� ��: IIC_Read_Mulit_Data(uint8 commond,uint8 address,uint8 *addrpoint,uint8 bytenum)
* ��������: ��IIC�н����ֽڶ�����
* ��ڲ���: commond��ַ��д���address�����ݵ���ʼ��ַ,addrpoint���ݴ�ŵ�ַָ�룬bytenum�ֽ���
* ��    ��: ��
*******************************************************************************/
 
void IIC_Read_Mulit_Data(uint8 commond, uint8 address, uint8 *addrpoint, uint8 bytenum)
{
    uint8 i, status;
    IIC_Start();                        //����EEPROM��д����
//    status = IIC_WriteByte(commond);     //д�ӻ���ַ��д����ָ��
 
//    if(!status)
//    {
//        status = IIC_WriteByte(address);    //д�Ĵ�����ַ
//    }
//    if(!status)
//    {
////        IIC_Start();    //��������IIC
        status = IIC_WriteByte(commond + 0x01); //д��ָ��
//    }
    for(i = 0; i < bytenum; i++)
    {
        if(!status)
        {
            addrpoint[i] = IIC_ReadByte();  //��ȡ���ݴ�ŵ�����
            if(i < (bytenum - 1))
            {
                IIC_WriteACK();             //����Ӧ���ź�
            }
            else
            {
                IIC_Writenoack();           //�������һ�����ݷ�����Ӧ���źţ���ʾ����������
            }
        }
    }
    IIC_Stop();                     //ֹͣEEPROM��д����
    DelayUS(1);
}
 
/*******************************************************************************
* �� �� ��: LED_Display(uint8 chosebit,uint8 wdata)
* ��������: �����������ʾ
* ��ڲ���: chosebitѡ����λ��wdata����
* ��    ��: ��
*******************************************************************************/
 
//void LED_Display(uint8 chosebit, uint8 wdata)
//{
//    if((chosebit < 0) || (chosebit > 4))
//        return;
//    ADCON1 = 0x86;  //10000110  PORTA������Ϊ����IO��
//    TRISA &= 0x00;
//    TRISE &= 0xEF;      //����PORTDΪ��ͨIO�ڣ���PORTD�Ĳ�����ؼ������
//    TRISD = 0x00;       //����������Ϊ���
//    PORTA = (PORTA & 0xE3) | ((chosebit + 3) << 2); //RA2:RA3:RA4:011 ѡͨ��һλ 100ѡͨ�ڶ�λ 101ѡͨ����λ 110ѡͨ����λ
//    PORTD = wdata;  //����ʾ���ֵĶ���
//    DelayUS(100);       //��ʱ
//    PORTD = 0xFF;       //�ر���ʾ
//}


void initII2()
{
    IRCF0 = 1   ;       //OSSCON  4M
    IRCF1 = 1   ;
    IRCF2 = 1   ;
    IRCF3 = 1   ;
    
    TRISC3 = 0;             //����ʱ����Ϊ���
    TRISC4 = 0;             //����������Ϊ���
    
    

//    TRISB = 0X20;        //INPUT TRISB 00010000
//    ANSELB = 0X00;       //SIMULATEB 00010000
//    PORTB = 0X20;
//    
//   OPTION_REG = 0X42; //32?? : 01000100
}