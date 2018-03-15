#include "UART.h"

void delay(unsigned int time)
{
	unsigned int i = 0;
	for( i = 0; i < time; i++ )
	{

	}
}

void main()
{
	char str[10];
	int ret = 0;
	initUart(9600);

	while(1)
	{
		ret = readString(str, 10);
		if( ret > 0 )
		{
			sendString(str, ret);
		}
	}

}
