#include "UART.h"
#include "HC595.h"
#include "String.h"
#include "HeartModule.h"

void main()
{
	initUart(9600);

	while(1)
	{
		ANAIMAL_A();
		sendString("endA", 5);
		ANAIMAL_B();
		sendString("endB", 5);
		ANAIMAL_C();
		sendString("endC", 5);
		ANAIMAL_E();
		sendString("endD", 5);
		delay(10000);
	}
}
