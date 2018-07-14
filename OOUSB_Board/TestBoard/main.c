#include "UART.h"
#include "KEY.h"
#include "LED.h"

void delay(unsigned int time)
{
	unsigned int i = 0;
	for( i = 0; i < time; i++ )
	{

	}
}

void main()
{
	int ret = 0;
	unsigned int keyStat; 
	initUart();

	while(1)
	{
		keyScanReal();
		keyStat = getKeyStatus();
		setAllLed(keyStat);
		sendUInt(keyStat, 2);
		sendNewLine();
		delay(1000);
	}

}
