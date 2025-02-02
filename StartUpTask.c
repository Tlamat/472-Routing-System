#include "boolean.h"
#include "ucos.h"
#include "td40.h"
#include "TCB_Data_Structs.h"
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <string.h>

#define t2count				5
#define STACK_SIZE         1024

#define TASK1_PRIORITY		11
#define TASK2_PRIORITY		12
#define TASK3_PRIORITY		13
#define TASK4_PRIORITY		14
#define TASK5_PRIORITY		15
#define TASK6_PRIORITY		17
#define TASK7_PRIORITY		18
#define TASK8_PRIORITY		19
#define TASK9_PRIORITY		20

extern int PwdOffTime;
extern int PwdPeriod;

extern UWORD Task1_Stk[STACK_SIZE];
extern UWORD Task2_Stk[STACK_SIZE];
extern UWORD Task3_Stk[STACK_SIZE];
extern UWORD Task4_Stk[STACK_SIZE];
extern UWORD Task5_Stk[STACK_SIZE];
extern UWORD Task6_Stk[STACK_SIZE];
extern UWORD Task7_Stk[STACK_SIZE];
extern UWORD Task8_Stk[STACK_SIZE];
extern UWORD Task9_Stk[STACK_SIZE];

extern TaskDataRead ReaderTaskData;
extern TaskDataDir LeftTaskData;
extern TaskDataDir RightTaskData;
extern TaskDataDir FwdTaskData;
extern TaskDataRout RoutingTaskData;
extern TaskDataWarn IdTaskData;
extern TaskDataWarn JamTaskData;
extern TaskDataWarn SizeTaskData;
extern TaskDataSerCom SerialTaskData;
extern TaskDataInterval IntervalTaskData;
extern TaskDataParse ParseTaskData;
extern TaskDataCommand CommandTaskData;
extern TaskDataMissile MissileTaskData;

// Function Prototypes
void far interrupt Timer2_ISR(void);
void far interrupt Timer1_ISR(void);
void far interrupt Timer0_ISR(void);
void far ReaderTask(void* data);
void far LeftTask(void* data);
void far FwdTask(void* data);
void far RightTask(void* data);
void far RoutingTask(void* data);
void far SerialTask(void* data);
//void far IntervalTask(void* data);
void far ParseTask(void* data);
void far CommandTask(void* data);
void far MissleLauncher(void* data);


void far StartUpTask(void)
{
	OS_ENTER_CRITICAL();

	// Install the uC/OS timer ISR
	setvect(0x0008, (void interrupt (*)(void))OSTickISR);

	// Install applications timer ISR
	setvect(0x0081, Timer0_ISR);

	// Initialize Timer0
	outport(0xFF32, 0x0007);		 // Unmask TIMER0 interrupt and set Timer0
	// interrupt to low priority


	outport(0xFF56, 4000);			// Disable TIMER0
	outport(0xFF52, 10000);			// Initialize TIMER0's count
	outport(0xFF56, 0xE001);		// Enable TIMER0 to generate an interrupt,
											// use maxcount A, don't use prescaled value,
											// use internal clock, continuous operation

   // timer 1 initializatin
//   t1_init(0xE003,PwdOffTime * 10000,(PwdPeriod * 10000) - (PwdOffTime * 10000),Timer1_ISR);


	// Start Timer 2
	*(void far* far*)(0x004C) = Timer2_ISR;
	// TCUCON
    outport(0xFF32, 0x0007);
	// turn T2 off
    outport(0xFF66, 0);
	// setup T2CMPA to counter 10000 ticks (1ms)
    outport(0xFF62, (t2count * 10000));
	// T2CON, start clock
    outport(0xFF66, 0xE001);

	OS_EXIT_CRITICAL();

	OSTaskCreate(ReaderTask, (void*)&ReaderTaskData,(void*)&Task1_Stk[STACK_SIZE-1],TASK1_PRIORITY);
   OSTaskCreate(LeftTask,(void*)&LeftTaskData,(void*)&Task2_Stk[STACK_SIZE-1], TASK2_PRIORITY);
	OSTaskCreate(FwdTask, (void*)&FwdTaskData, (void*)&Task3_Stk[STACK_SIZE-1], TASK3_PRIORITY);
	OSTaskCreate(RightTask, (void*)&RightTaskData, (void*)&Task4_Stk[STACK_SIZE-1], TASK4_PRIORITY);
	OSTaskCreate(RoutingTask, (void*)&RoutingTaskData, (void*)&Task5_Stk[STACK_SIZE-1], TASK5_PRIORITY);
	OSTaskCreate(SerialTask, (void*)&SerialTaskData, (void*)&Task6_Stk[STACK_SIZE-1], TASK6_PRIORITY);
//	OSTaskCreate(ParseTask, (void*)&ParseTaskData, (void*)&Task7_Stk[STACK_SIZE-1], TASK7_PRIORITY);
	OSTaskCreate(CommandTask, (void*)&CommandTaskData, (void*)&Task8_Stk[STACK_SIZE-1], TASK8_PRIORITY);
//   OSTaskCreate(MissleLauncher, (void*)&MissileTaskData, (void*)&Task9_Stk[STACK_SIZE-1], TASK9_PRIORITY);
	OSTaskDel(OS_PRIO_SELF);
}