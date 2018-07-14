/**
 * @brief 用来配置工程
 * 
 * @file config.h
 * @author your name
 * @date 2018-07-10
 */
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <8052.h>

/**
 * @brief 定义工程中使用的引脚
 * 
 */
#define ACTIVITY_STATUS 0
#define LEDDATA P2
#define LED1    P2_0
#define LED2    P2_1
#define LED3    P2_2
#define LED4    P2_3
#define LED5    P2_4
#define LED6    P2_5
#define LED7    P2_6
#define LED8    P2_7


//按键引脚
#define KEYIN0        P1_0
#define KEYIN1        P1_1
#define KEYIN2        P1_2
#define KEYIN3        P1_3
#define KEYIN4        P1_4
#define KEYIN5        P1_5
#define KEYIN6        P1_6
#define KEYIN7        P1_7


/**
 * @brief 定义通用结构体
 * 
 */
#define uint8 unsigned char
#define uint16 unsigned short int
#define uint32 unsigned long int
#define int8 signed char
#define int16 signed short int
#define int32 signed long int
#define uint64 unsigned long long int
#define int64 signed long long int

/**
 * @brief 定义uart软件缓冲区的大小
 * 
 */
#define RX_BUFFER_SIZE 50    //UART接受缓冲区大小
#define TX_BUFFER_SIZE 50    //UART发送缓冲区大小


#define SYSCLK 11059200UL /*使用11.0592M晶体*/
#define BITRATE 9600UL  /*波特率定义为9600*/

#endif