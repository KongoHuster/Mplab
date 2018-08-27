#include <xc.h>
#include "II2.h"
    
/********************定义数据线************************************************/
 
#define     IIC_SCLK    RC2     //24C02时钟线
#define     IIC_SDAT    RC3     //24C02数据线
 
/********************定义全局变量**********************************************/


/*******************************************************************************
* 函 数 名: DelayUS(uint8 delay)
* 函数功能: 微秒延时    for 20MHZ
* 入口参数: delay
* 返    回: 无
*******************************************************************************/
 
void DelayUS(uint8 delay)
{
    while(--delay);
}
 
/*******************************************************************************
* 函 数 名: DelayMS(uint16 delay)
* 函数功能: 毫秒延时    for20MHZ
* 入口参数: delay
* 返    回: 无
*******************************************************************************/
 
void DelayMS(uint16 delay)
{
    uint16 i;
    for(; delay > 0; delay--)
        for(i = 0; i < 453; i++);
}
 
/******************************************************************************
* 函 数 名: IIC_WriteACK(void)
* 函数功能: 从机接收数据正常时，向主机发送应答信号
* 入口参数: 无
* 返    回: 无
*******************************************************************************/
 
void IIC_WriteACK(void)
{
    TRISC4 = 0;
    
    IIC_SDAT = 0; 
    DelayUS(4);
    IIC_SCLK = 1;
    IIC_SCLK = 0;
    TRISA1=1;
//    IIC_SDAT = 0;           //拉低数据线,给主机发送一个低电平
//    IIC_SCLK = 1;           //时钟有效，发送数据
//    DelayUS(4);
//    IIC_SCLK = 0;
//    TRISC4 = 1;
//    //    IIC_SDAT = 1;
}
 
/******************************************************************************
* 函 数 名: IIC_Writenoack(void)
* 函数功能: 从机接收数据结束时，向主机发送无应答信号
* 入口参数: 无
* 返    回: 无
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
//    IIC_SDAT = 1;         //发送高电平，表示无应答
//    DelayUS(2);
//    IIC_SCLK = 1;         //时钟有效
//    DelayUS(2);
//    IIC_SCLK = 0;
    TRISC4 = 1;
}
 
/******************************************************************************
* 函 数 名: IIC_Start(void)
* 函数功能: 启动EEPROM读写操作
* 入口参数: 无
* 返    回: 无
*******************************************************************************/
 
void IIC_Start(void)
{
    TRISC4 = 0;
    IIC_SDAT = 1;         //数据线置位

    IIC_SCLK = 1;         //时钟有效
    DelayUS(4);
    IIC_SDAT = 0;         //数据线复位，在时钟有效期间，数据线产生一个下降沿表示启动EEPROM读写操作
    DelayUS(4);
    IIC_SCLK = 0;         //时钟无效

     TRISC4 = 1;
    NOP();
    NOP();
}
 
/******************************************************************************
* 函 数 名: IIC_Stop(void)
* 函数功能: 停止对EEPROM读写操作
* 入口参数: 无
* 返    回: 无
*******************************************************************************/
 
void IIC_Stop(void)
{
    TRISC4 = 0;
    IIC_SDAT = 0;         //数据线复位
    IIC_SCLK = 0;         //时钟有效
    DelayUS(4);
    IIC_SDAT = 1;         //数据线复位
    IIC_SCLK = 1;         //数据线置位，在时钟有效期间，数据线产生一个上升沿表示停止EEPROM读写操作
    DelayUS(4);
     
}
 
/******************************************************************************
* 函 数 名: IIC_WriteByte(uint8 wdata)
* 函数功能: 进行8位字节数据写操作
* 入口参数: wdata待写数据
* 返    回: status:0:成功 1：失败
*******************************************************************************/
uint8 IIC_WriteByte(uint8 wdata)
{
     
    uint8 i, status;
    IIC_SCLK = 0;                   //时钟无效
    TRISC4=0;

    for(i = 0; i < 8; i++)              //写8位字节数据
    {
        if((wdata & 0x80) == 0x80)  //读最高位数据
        {        
            IIC_SDAT = 1;
          
        }
        else
        {
            IIC_SDAT = 0;
            
        }
        DelayUS(4); 
        IIC_SCLK = 1;           //时    钟有效
        
        wdata <<= 1;            //数据左移一位
        DelayUS(4); 
        IIC_SCLK = 0;
        DelayUS(2);
    }
     IIC_SCLK = 0;       //时钟有效
    TRISC4 = 1;         //数据线设置为输入模式

    DelayUS(2);
    IIC_SCLK = 1;       //????
    DelayUS(2); 
    NOP();
    NOP();
    NOP();
    if(IIC_SDAT)        //第九个时钟数据为1，则写失败成功，IIC器件没有应答
    {
        status = 1;
    }
    else
    {
        status = 0;
    }
    IIC_SCLK = 0;
    TRISC4 = 0;         //数据线设置回输出模式
    return status;      //返回写成功与否状态
}
 
/******************************************************************************
* 函 数 名: IIC_WriteData(uint8 commond,uint8 reg_addr,*mdatapointer,uint8 bytenum)
* 函数功能: 写多字节数据
* 入口参数: commond：读写指令，reg_addr写操作地址，mdata待写数据,bytenum字节数
* 返    回: 无
*******************************************************************************/
//void IIC_Write_Mulit_Data(uint8 commond, uint8 reg_addr, uint8 *mdatapointer, uint8 bytenum)
//{
//    uint8 i, status;
//    IIC_Start();    //启动IIC
//    status = IIC_WriteByte(commond);    //写器件地址
//    if(!status)
//    {
//        status = IIC_WriteByte(reg_addr);   //写寄存器地址
//    }
//    for(i = 0; i < bytenum; i++)
//    {
//        if(!status)
//        {
//            status = IIC_WriteByte(*(mdatapointer + i));        //写数据
//        }
//    }
//    IIC_Stop();     //结束IIC
//}
 
/******************************************************************************
* 函 数 名: IIC_ReadByte(void)
* 函数功能: 8位数据读操作
* 入口参数: 无
* 返    回: bytedata读取的8位数据
*******************************************************************************/
uint8 IIC_ReadByte(void)
{
    uint8 i, bytedata = 0;
    TRISC4 = 1;     //数据线设置为输入模式
    IIC_SDAT = 1;   //数据线拉高
//    DelayUS(2);
//    IIC_SCLK = 0;
//    DelayUS(2);
    for(i = 0; i < 8; i++)      //读8位数据
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
    TRISC4 = 0;     //数据线设置回输出模式
    return(bytedata);//返回数据
}
 
/******************************************************************************
* 函 数 名: IIC_Read_Mulit_Data(uint8 commond,uint8 address,uint8 *addrpoint,uint8 bytenum)
* 函数功能: 对IIC行进多字节读操作
* 入口参数: commond地址读写命令，address读数据的起始地址,addrpoint数据存放地址指针，bytenum字节数
* 返    回: 无
*******************************************************************************/
 
void IIC_Read_Mulit_Data(uint8 commond, uint8 address, uint8 *addrpoint, uint8 bytenum)
{
    uint8 i, status;
    IIC_Start();                        //启动EEPROM读写操作
//    status = IIC_WriteByte(commond);     //写从机地址及写操作指令
 
//    if(!status)
//    {
//        status = IIC_WriteByte(address);    //写寄存器地址
//    }
//    if(!status)
//    {
////        IIC_Start();    //重新启动IIC
        status = IIC_WriteByte(commond + 0x01); //写读指令
//    }
    for(i = 0; i < bytenum; i++)
    {
        if(!status)
        {
            addrpoint[i] = IIC_ReadByte();  //读取数据存放到数组
            if(i < (bytenum - 1))
            {
                IIC_WriteACK();             //返回应答信号
            }
            else
            {
                IIC_Writenoack();           //读完最后一个数据返回无应答信号，表示结束读操作
            }
        }
    }
    IIC_Stop();                     //停止EEPROM读写操作
    DelayUS(1);
}
 
/*******************************************************************************
* 函 数 名: LED_Display(uint8 chosebit,uint8 wdata)
* 函数功能: 单个数码管显示
* 入口参数: chosebit选择字位，wdata字型
* 返    回: 无
*******************************************************************************/
 
//void LED_Display(uint8 chosebit, uint8 wdata)
//{
//    if((chosebit < 0) || (chosebit > 4))
//        return;
//    ADCON1 = 0x86;  //10000110  PORTA口设置为数字IO口
//    TRISA &= 0x00;
//    TRISE &= 0xEF;      //配置PORTD为普通IO口，对PORTD的操作务必加上这句
//    TRISD = 0x00;       //数据线配置为输出
//    PORTA = (PORTA & 0xE3) | ((chosebit + 3) << 2); //RA2:RA3:RA4:011 选通第一位 100选通第二位 101选通第三位 110选通第四位
//    PORTD = wdata;  //送显示数字的断码
//    DelayUS(100);       //延时
//    PORTD = 0xFF;       //关闭显示
//}


void initII2()
{
    IRCF0 = 1   ;       //OSSCON  4M
    IRCF1 = 1   ;
    IRCF2 = 1   ;
    IRCF3 = 1   ;
    
    TRISC3 = 0;             //配置时钟线为输出
    TRISC4 = 0;             //配置数据线为输出
    
    

//    TRISB = 0X20;        //INPUT TRISB 00010000
//    ANSELB = 0X00;       //SIMULATEB 00010000
//    PORTB = 0X20;
//    
//   OPTION_REG = 0X42; //32?? : 01000100
}