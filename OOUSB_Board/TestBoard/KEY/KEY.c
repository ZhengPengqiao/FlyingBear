#include "KEY.h"

unsigned char keyBuf[8] = {
	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
};
unsigned int keyStatus = 0;

/*******************************************************************************
 * 函数名称 : keyScan
 * 函数介绍 : 扫描按键
 * 参数介绍 : 无
 * 返回值  :  无
 ******************************************************************************/
void keyScan()
{
	char i = 0;
	static unsigned char raw = 0;
	
	keyBuf[0] = (keyBuf[0]<<1) | KEYIN0;
	keyBuf[1] = (keyBuf[1]<<1) | KEYIN1;
	keyBuf[2] = (keyBuf[2]<<1) | KEYIN2;
	keyBuf[3] = (keyBuf[3]<<1) | KEYIN3;
	keyBuf[4] = (keyBuf[4]<<1) | KEYIN4;
	keyBuf[5] = (keyBuf[5]<<1) | KEYIN5;
	keyBuf[6] = (keyBuf[6]<<1) | KEYIN6;
	keyBuf[7] = (keyBuf[7]<<1) | KEYIN7;
	
	for(i = 0; i < 8; i++)
	{
		if(keyBuf[i] == 0x00)
		{
			keyStatus |= (1 << (i) );
			keyBuf[i] = 0xFF;  //在连续8次算一个事件
		}
	}
}


/*******************************************************************************
 * 函数名称 : keyScanReal
 * 函数介绍 : 扫描按键
 * 参数介绍 : 无
 * 返回值  :  无
 ******************************************************************************/
void keyScanReal()
{
	char i = 0;
	static unsigned char raw = 0;
	
	keyBuf[0] = (keyBuf[0]<<1) | KEYIN0;
	keyBuf[1] = (keyBuf[1]<<1) | KEYIN1;
	keyBuf[2] = (keyBuf[2]<<1) | KEYIN2;
	keyBuf[3] = (keyBuf[3]<<1) | KEYIN3;
	keyBuf[4] = (keyBuf[4]<<1) | KEYIN4;
	keyBuf[5] = (keyBuf[5]<<1) | KEYIN5;
	keyBuf[6] = (keyBuf[6]<<1) | KEYIN6;
	keyBuf[7] = (keyBuf[7]<<1) | KEYIN7;
	
	for(i = 0; i < 8; i++)
	{
		if(keyBuf[i] == 0x00)
		{
			keyStatus |= (1 << (i) );
		}
		else if(keyBuf[i] == 0xFF)
		{
			keyStatus &= ~(1 << (i) );
		}
	}
}


/*******************************************************************************
 * 函数名称 : getKeyStatus
 * 函数介绍 : 得到按键状态,每一位代表一个按键状态,1为事件发生,0为无事件
 * 参数介绍 : 无
 * 返回值  :  无
 ******************************************************************************/
unsigned int getKeyStatus()
{
	return keyStatus;
}


/*******************************************************************************
 * 函数名称 : clearKeyStatus
 * 函数介绍 : 清楚指定位事件
 * 参数介绍 : which : 将要清楚的事件位
 * 返回值  :  无
 ******************************************************************************/
void clearKeyStatus(char which)
{
    //if which < 0, reset all key
    if ( which < 0 )
    {
        keyStatus = 0;
        return;
    }
    keyStatus &= ~(1 << which);
}

