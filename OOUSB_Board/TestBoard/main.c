#include "UART.h"
#include "KEY.h"
#include "LED.h"
#include "TIMER.h"

/*******************************************************************************
 *  定时任务到期时将会执行的函数
 ******************************************************************************/

void keyScanFun()
{
	keyScanReal();
}

void ledCtrlFun()
{
	unsigned int keyStat; 
	keyStat = getKeyStatus();
	setAllLed(keyStat);

	sendUInt(keyStat, 2);
	sendNewLine();
}

void main()
{
	initUart();

	sendString("main start", 11);
	sendNewLine();
	
	addTIMER0Task(5, keyScanFun, 1);
	addTIMER0Task(10, ledCtrlFun, 2);

	while(1)
	{
		ledUpdate();
		TIMER0Update();
	}
}
