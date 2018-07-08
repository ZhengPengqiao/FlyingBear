#include "String.h"



/*******************************************************************************
 * 函数名称 : TOHEX
 * 函数介绍 : 将val转换成16进制的字符
 * 参数介绍 : val： 将要转换的数据
 * 返回值  :  转换后的字符
 ******************************************************************************/
unsigned char TOHEX(char val)
{
    if ( 16 <= val || val < 0 )
    {
        return '?';
    }
	else if ( 0 <= val && val <= 9 )
	{
		return val+'0';
	}
	else
	{
		return val-10+'A';
	}
}


/*******************************************************************************
 * 函数名称 : LongToHexChar
 * 函数介绍 : 将unsigned long转换为16进制的字符串
 * 参数介绍 : val： 将要转换的数据， str:调用者用于接收字符串的空间
 * 返回值  :  无
 ******************************************************************************/
void LongToHexChar(unsigned long val, char *str)
{
	str[7] = TOHEX(val%16);
	val = val/16;
	str[6] = TOHEX(val%16);
	val = val/16;

	str[5] = TOHEX(val%16);
	val = val/16;
	str[4] = TOHEX(val%16);
	val = val/16;
	
	str[3] = TOHEX(val%16);
	val = val/16;
	str[2] = TOHEX(val%16);
	val = val/16;
	
	str[1] = TOHEX(val%16);
	val = val/16;
	str[0] = TOHEX(val%16);
	val = val/16;
	
	str[8] = '\n';
}
