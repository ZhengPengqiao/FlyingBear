#include "UART.h"
__xdata char UART0_CHAR[RX_BUFFER_SIZE];   //接受缓冲区的字符
int end,start;                     //接受缓冲区的使用情况
int sendstatus = 0;                //发送状态
void (*UART0_RXISR_function)();    //接受中断函数
void (*UART0_TXISR_function)();    //发送中断函数

/*******************************************************************************
 * 说明 : 每一位数字对应的进制数
 ******************************************************************************/
__xdata char baseCharArray[16] = {
	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
	'A',
	'B',
	'C',
	'D',
	'E',
	'F',
};

/*******************************************************************************
 * 函数名称 : InterruptUART
 * 函数介绍 : 串口处理程序
 * 参数介绍 : 无
 * 返回值  :  无
 ******************************************************************************/
void InterruptUART() __interrupt 4
{
	if(RI)  //接收到新字符
	{
		RI = 0;
		if(end >= RX_BUFFER_SIZE )
			end = 0;
		UART0_CHAR[end++] = SBUF;
		if( UART0_RXISR_function != 0)
		{
			UART0_RXISR_function();
		}
	}
	
	if(TI)  //字节发送完毕
	{
		TI = 0;
		sendstatus = 1;
		if(UART0_TXISR_function != 0 )
		{
			UART0_TXISR_function();
		}
	}
}


/*******************************************************************************
 * 函数名称 : sendNewLine
 * 函数介绍 : 发送换行符
 * 参数介绍 : 无
 * 返回值  :  无
 ******************************************************************************/
void sendNewLine()
{
	sendString("\r\n",2);
}

/*******************************************************************************
 * 函数名称 : initUart
 * 函数介绍 : 初始化串口
 * 参数介绍 : 无
 * 返回值  :  无
 ******************************************************************************/
void initUart()
{
	EA = 1;
	SCON = 0x50;
	TMOD &= 0x0F;
	TMOD |= 0x20; //配置T1为模式2
	TH1 = 256-(SYSCLK/12/32/BITRATE);
	TL1 = TH1; //初始值等于重载值
	ET1 = 0;   //禁止T1的中断
	ES = 1;    //使能串口中断
	TR1 = 1;   //启动T1
}

/*******************************************************************************
 * 函数名称 : sendChar
 * 函数介绍 : 发送的字符
 * 参数介绍 : ch  :  要发送的字符
 * 返回值  :  无
 ******************************************************************************/
void sendChar(char ch)
{
    SBUF = ch;
    while( sendstatus == 0 ); //在发送成功时,中断会将sendstatus置0,
	sendstatus = 0;
}

/*******************************************************************************
 * 函数名称 : sendString
 * 函数介绍 : 要发送的字符串
 * 参数介绍 : str  :  要发送的字符串
 *           len  :  要发送的个数
 * 返回值  :  无
 ******************************************************************************/
void sendString(char * str, int len)
{
	int i = 0;
	for(i = 0; i < len; i++)
	{
		sendChar( str[i] );
	}
}

/*******************************************************************************
 * 函数名称 : readChar
 * 函数介绍 : 读取字符
 * 参数介绍 : ch  :  读取的字符存放位置
 * 返回值  :  无
 ******************************************************************************/
char readChar()
{
	if(start != end)
	{
		char ch = UART0_CHAR[start];
		UART0_CHAR[start] = 0;
		start++;
		if(start >= RX_BUFFER_SIZE)
		{
			start = 0;
		}

		return ch;
	}
	else
	{
		return 0;
	}
}

/*******************************************************************************
 * 函数名称 : readString
 * 函数介绍 : 读取字符串
 * 参数介绍 : str  :  读取字符串暂存的位置
 * 			len  :   要读取的位数
 * 返回值  :  正真读取的位数
 ******************************************************************************/
int readString(char * str, int len)
{
	char ch = 0;
	int i = 0;
	if(len <= 0)
	{
		return -1;
	}
	ch = readChar();
	while( ch != 0 )
	{
		*(str+i) = ch;
		i++;
		if( i < len )
		{
			ch = readChar();
		}
		else
		{
			break;
		}
	}
	return i;
}


/*******************************************************************************
 * 函数名称 : readStringWait
 * 函数介绍 : 阻塞读取字符串
 * 参数介绍 : str  :  读取字符串暂存的位置
 * 			len  :   将会读取的位数
 * 返回值  :  无
 ******************************************************************************/
void readStringWait(char * str, int len)
{
	unsigned int i = 0;
	while(i < len)
	{
		i += readString(str+i,len-i);
	}
}

/*******************************************************************************
 * 函数名称 : setUartRXFun
 * 函数介绍 : 设置接收中断时,调用的函数,可以做一些相关的事情,比如记录流量,但是时间应尽量短
 * 参数介绍 :  inUART0_RXISR_function :   将要设置的函数
 * 返回值  :  无
 ******************************************************************************/
void setUartRXFun( void (*inUART0_RXISR_function)())
{
	UART0_RXISR_function = inUART0_RXISR_function;
}

/*******************************************************************************
 * 函数名称 : setUartTXFun
 * 函数介绍 : 设置发送中断时,调用的函数,可以做一些相关的事情,比如记录流量,但是时间应尽量短
 * 参数介绍 : inUART0_TXISR_function  :  将要设置的函数
 * 			len  :   将会读取的位数
 * 返回值  :  无
 ******************************************************************************/
void setUartTXFun( void (*inUART0_TXISR_function)())
{
	UART0_TXISR_function = inUART0_TXISR_function;
}


/*******************************************************************************
 * 函数名称 : sendUInt
 * 函数介绍 : 发送一个无符号整形数
 * 参数介绍 : val  :  将要发送的数据
 *           base : 按照几进制发送（2,8,10,16）
 * 返回值  :  int:发送的位数
 ******************************************************************************/
int sendUInt(unsigned int val, unsigned char base)
{
	int sendCharCount = 0;
	unsigned char tmp[16];
	char i = 0;

	//如果大于十六进制，就是函数不支持，直接返回-1表示错误
	if( base > 16 )
	{
		return -1;
	}

	switch(base)
	{
		case 2:
			sendString("0b",2);
			for(i = 0; i < 16; i++)
			{
				tmp[i] = val % base;
				val = val/base;
				sendCharCount++;
			}
			break;
		case 8:
			sendString("0o",2);
			for(i = 0; i < 6; i++)
			{
				tmp[i] = val % base;
				val = val/base;
				sendCharCount++;
			}
			break;
		case 10: 
			sendString("0d",2);
			while( val >= base || val != 0)
			{
				tmp[i++] = val % base;
				val = val/base;
				sendCharCount++;
			}

			if( sendCharCount == 0 )
			{
				tmp[i++] = '0';
				sendCharCount++;
			}
			break;
		case 16:
			sendString("0x",2);
			for(i = 0; i < 4; i++)
			{
				tmp[i] = val % base;
				val = val/base;
				sendCharCount++;
			}
			break;
		default: sendString("ud",2);break;
	}


	for(i = sendCharCount-1; i >= 0; i--)
	{
		sendChar(baseCharArray[tmp[i]]);
	}

	return sendCharCount;
}
