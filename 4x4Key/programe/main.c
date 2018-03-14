#include "LED.h"
#include "KEY.h"

void delay(unsigned int time)
{
	unsigned int i = 0;
	for( i = 0; i < time; i++ )
	{

	}
}

void main()
{
	int i;
	unsigned int val;
	while(1)
	{
		keyScanMutClk();
		val = getKeyStatus();

		for( i = 0; i < 16; i++ )
		{
			if( (val & (1<<i)) != 0 )
			{
				break;
			}
		}

		setAllLed( ~(i) );
		delay(200);
	}
}
