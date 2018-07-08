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
	char ch;
	initUart(9600);

	while(1)
	{
		ch = readChar();

		if(ch != 0)
		{
			LEDDATA = ch;
		}
		delay(2000);
	}

}
