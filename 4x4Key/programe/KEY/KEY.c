#include "KEY.h"

unsigned char keyBuf[4][4] = {
	{0xFF,0xFF,0xFF,0xFF},
	{0xFF,0xFF,0xFF,0xFF},
	{0xFF,0xFF,0xFF,0xFF},
	{0xFF,0xFF,0xFF,0xFF},
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
	
	keyBuf[raw][0] = (keyBuf[raw][0]<<1) | KEYIN1;
	keyBuf[raw][1] = (keyBuf[raw][1]<<1) | KEYIN2;
	keyBuf[raw][2] = (keyBuf[raw][2]<<1) | KEYIN3;
	keyBuf[raw][3] = (keyBuf[raw][3]<<1) | KEYIN4;
	
	for(i = 0; i < 4; i++)
	{
		if(keyBuf[raw][i] == 0x00)
		{
			keyStatus |= (1 << (raw*4+i) );
			keyBuf[raw][i] = 0xFF;
		}
	}
	
	switch(raw)
	{
		case 0: KEYOUT1 = 1; KEYOUT2 = 0; raw = 1;break;  //下一行是第2行
		case 1: KEYOUT2 = 1; KEYOUT3 = 0; raw = 2;break;  //下一行是第3行
		case 2: KEYOUT3 = 1; KEYOUT4 = 0; raw = 3;break;  //下一行是第4行
		case 3: KEYOUT4 = 1; KEYOUT1 = 0; raw = 0;break;  //下一行是第1行
	}
}


/*******************************************************************************
 * 函数名称 : keyScanMutClk
 * 函数介绍 : 扫描按键,允许连续按键
 * 参数介绍 : 无
 * 返回值  :  无
 ******************************************************************************/
void keyScanMutClk()
{
	char i = 0;
	static unsigned char raw = 0;
	
	keyBuf[raw][0] = (keyBuf[raw][0]<<1) | KEYIN1;
	keyBuf[raw][1] = (keyBuf[raw][1]<<1) | KEYIN2;
	keyBuf[raw][2] = (keyBuf[raw][2]<<1) | KEYIN3;
	keyBuf[raw][3] = (keyBuf[raw][3]<<1) | KEYIN4;
	
	for(i = 0; i < 4; i++)
	{
		if(keyBuf[raw][i] == 0x00)
		{
			keyStatus |= (1 << (raw*4+i) );
		}
		else
		{
			keyStatus &= ~(1 << (raw*4+i) );
		}
	}
	
	switch(raw)
	{
		case 0: KEYOUT1 = 1; KEYOUT2 = 0; raw = 1;break;  //下一行是第2行
		case 1: KEYOUT2 = 1; KEYOUT3 = 0; raw = 2;break;  //下一行是第3行
		case 2: KEYOUT3 = 1; KEYOUT4 = 0; raw = 3;break;  //下一行是第4行
		case 3: KEYOUT4 = 1; KEYOUT1 = 0; raw = 0;break;  //下一行是第1行
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
void clearKeyStatus(unsigned char which)
{
	//if which < 0, reset all key
	if ( which < 0 )
	{
		keyStatus = 0;
		return;
	}
	keyStatus &= ~(1 << which);
}

