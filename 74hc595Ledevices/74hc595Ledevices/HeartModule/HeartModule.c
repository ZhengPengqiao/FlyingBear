#include "UART.h"
#include "HC595.h"
#include "String.h"
#include "HeartModule.h"

/*******************************************************************************
 * 函数名称 : transformInt
 * 函数介绍 : 转换long內容成灯可认的数据
 * 参数介绍 : baseLong: 将要转换的数据
 * 返回值  :  转换后的数据
 ******************************************************************************/
unsigned long transformInt(unsigned long baseLong)
{
    unsigned long newLong = 0; //新long內容
    int i = 0;//0~22

    newLong |= ((baseLong & (1 << i)) >> i) << LED0; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED1; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED2; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED3; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED4; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED5; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED6; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED7; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED8; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED9; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED10; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED11; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED12; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED13; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED14; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED15; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED16; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED17; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED18; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED19; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED20; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED21; i++;
    newLong |= ((baseLong & (1 << i)) >> i) << LED22; i++;

    return newLong;
}

/*******************************************************************************
 * 函数名称 : pushData
 * 函数介绍 : 上传数据
 * 参数介绍 : needPushData: 将要上传的数据
 * 返回值  :  无
 ******************************************************************************/
void pushData(unsigned long needPushData)
{
    HC595AddData(needPushData % 256);
    HC595AddData(needPushData / 256 % 256);
    HC595AddData(needPushData / 256 / 256 % 256);

    //将数据推到存储寄存器，进行显示
	HC595TransformData();
}

/*******************************************************************************
 * 函数名称 : delay
 * 函数介绍 : 延迟数据
 * 参数介绍 : time: 时间
 * 返回值  :  无
 ******************************************************************************/
void delay(unsigned int time)
{
	unsigned int i = 0;
	for( i = 0; i < time; i++ )
	{

	}
}

/*******************************************************************************
 * 函数名称 : ANAIMAL_A
 * 函数介绍 : 顺时针方向跑马灯
 * 参数介绍 : 无
 * 返回值  :  无
 ******************************************************************************/
void ANAIMAL_A()
{
    int i = 0;
    unsigned long newLong;
    unsigned long baseLong;
    for(i = 0; i < 23; i++)
    {
        baseLong = (long)1 << i;

        newLong = transformInt(baseLong);
        pushData(newLong);

		delay(50000);
    }
}

/*******************************************************************************
 * 函数名称 : ANAIMAL_B
 * 函数介绍 : 逆时针方向跑马灯
 * 参数介绍 : 无
 * 返回值  :  无
 ******************************************************************************/
void ANAIMAL_B()
{
    int i = 0;
    unsigned long newLong;
    unsigned long baseLong;
    for(i = 22; i >= 0; i--)
    {
        baseLong = (long)1 << i;

        newLong = transformInt(baseLong);
        pushData(newLong);

		delay(10000);
    }
}

/*******************************************************************************
 * 函数名称 : ANAIMAL_C
 * 函数介绍 : 旋风式跑马灯
 * 参数介绍 : 无
 * 返回值  :  无
 ******************************************************************************/
void ANAIMAL_C()
{
    int i = 0;
    unsigned long newLong;
    unsigned long baseLong;
    for(i = 0; i < 8; i++)
    {
        baseLong = (long)1 << i;
        baseLong |= (long)1 << (i+8);
        baseLong |= (long)1 << (i+16);

        newLong = transformInt(baseLong);
        pushData(newLong);

		delay(10000);
    }
    for(i = 7; i >= 0; i--)
    {
        baseLong = (long)1 << i;
        baseLong |= (long)1 << (i+8);
        baseLong |= (long)1 << (i+16);

        newLong = transformInt(baseLong);
        pushData(newLong);

		delay(10000);
    }
}


/*******************************************************************************
 * 函数名称 : ANAIMAL_E
 * 函数介绍 : 追赶式跑马灯
 * 参数介绍 : 无
 * 返回值  :  无
 ******************************************************************************/
void ANAIMAL_E()
{
    unsigned long i = 0;
    unsigned long newLong, baseLong;
    long tomActivity = 0, jerryActivity = 1;
    unsigned long tomStep = 5, jerryStep = 10;
    unsigned long tomPos = 0, jerryPos = 0;

    for(i = 0; i < 50000; i++)
    {

        if( tomStep+tomActivity > 200 )
        {
            tomActivity  = -1;
        }
        else  if( tomStep+tomActivity < 10 )
        {
            tomActivity  = 1;
        }

        if( jerryStep+jerryActivity > 200 )
        {
            jerryActivity  = -1;
        }
        else if( jerryStep+jerryActivity < 10 )
        {
            jerryActivity  = 1;
        }


        tomStep += tomActivity;
        jerryStep += jerryActivity;

        //更新位置
        tomPos = (tomPos+tomStep) % 2300;
        jerryPos = (jerryPos+jerryStep) % 2300;

        baseLong = (long)1 << (tomPos / 100);
        baseLong |= (long)1 << (jerryPos / 100);

        newLong = transformInt(baseLong);
        pushData(~newLong);
		delay(5000);
    }
}