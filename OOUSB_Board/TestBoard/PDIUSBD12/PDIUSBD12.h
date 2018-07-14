#ifndef __PDIUSBD12_H__
#define __PDIUSBD12_H__

#include "config.h"

//命令地址和数据地址
#define D12_COMMAND_ADD           1
#define D12_DATA_ADD              0

//PDIUSBD12芯片连接引脚
#define D12_DATA                  P0
#define D12_A0                    P3_5
#define D12_WR                    P3_6
#define D12_RD                    P3_7
#define D12_INT                   P3_2

//选择命令或数据地址
#define D12SetCommandAddr() D12_A0=D12_COMMAND_ADD
#define D12SetDataAddr()    D12_A0=D12_DATA_ADD
//WR控制
#define D12SetWr() D12_WR=1
#define D12ClrWr() D12_WR=0
//RD控制
#define D12SetRd() D12_RD=1
#define D12ClrRd() D12_RD=0
//获取中断状态
#define D12GetIntPin()  D12_INT
//读写数据
#define D12GetData() D12_DATA
#define D12SetData(Value) D12_DATA=(Value)

//将数据口设置为输入状态，51单片机端口写1就是为输入状态
#define D12SetPortIn() D12_DATA=0xFF

//将数据口设置为输出状态，由于51单片机是准双向IO口，所以不用切换，为空宏
#define D12SetPortOut()

//D12的读ID命令
#define Read_ID                  0xFD

//函数声明
/********************************************************************
函数功能：D12写命令。
入口参数：Command：一字节命令。
返    回：无。
备    注：无。
********************************************************************/
extern void D12WriteCommand(uint8 Command);

/********************************************************************
函数功能：读一字节D12数据。
入口参数：无。
返    回：读回的一字节。
备    注：无。
********************************************************************/
extern uint8 D12ReadByte(void);

/********************************************************************
函数功能：读D12的ID。
入口参数：无。
返    回：D12的ID。
备    注：无。
********************************************************************/
extern uint16 D12ReadID(void);

#endif
