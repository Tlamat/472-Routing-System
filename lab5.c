//----------------------------------------------------------------------------
// AUTHORS:   Eric Lund
// CREATED:   July 16, 2008
// MODIFIED:  July 16, 2008
// PROJECT:   EE 471 Lab #2
// MODULE:    Main Program
//
// Abstract: This is the core piece of the program. It initializes all the 
//	     		 global variables and structs. It then queues up and runs
// 	     	 the tasks in a round robin fashion.
//----------------------------------------------------------------------------
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

#define BAUD_RATE_9600   	8
#define BUFFSIZE				1024

#define STACK_SIZE         1024
#define STARTUP_Priority   0
#define TASK1_PRIORITY		11
#define TASK2_PRIORITY		13
#define TASK3_PRIORITY		15
#define TASK4_PRIORITY		17
#define TASK5_PRIORITY		19
#define TASK6_PRIORITY		21
#define TASK7_PRIORITY		23
#define TASK8_PRIORITY		25

#define t2count				5

#define ON						0
#define OFF						1

UWORD StartUp_Stk[STACK_SIZE];
UWORD Task1_Stk[STACK_SIZE];
UWORD Task2_Stk[STACK_SIZE];
UWORD Task3_Stk[STACK_SIZE];
UWORD Task4_Stk[STACK_SIZE];
UWORD Task5_Stk[STACK_SIZE];
UWORD Task6_Stk[STACK_SIZE];
UWORD Task7_Stk[STACK_SIZE];
UWORD Task8_Stk[STACK_SIZE];
UWORD Task9_Stk[STACK_SIZE];

// Status Variables
newBool error = FALSE;
int delayTime = 0;		// Counter of total delay time
int displaytime = 0;
newBool itemPresent = FALSE;
newBool inUse = FALSE;
newBool systemReady = TRUE;
newBool startUp = TRUE;

// Warning State Variables
int idState = 0;
int jamState = 0;
int sizeState = 0;
int buzzerState = 0;

char keypadInput = -1;
char line[50];

// Set true when error occurs; otherwise false
newBool idError = FALSE;
newBool sizeError = FALSE;
newBool jamRight = FALSE;
newBool jamLeft = FALSE;
newBool jamFwd = FALSE;
newBool jamPresent = FALSE;

// Directions; True indicates the package is traveling in that direction
newBool left = FALSE;
newBool right = FALSE;
newBool fwd = FALSE;

// RFID Tag
char itemID[9];
unsigned int itemSize = 0;
char itemDirection[3];

// Serial Communications Variables
unsigned char ser1_in_buf[BUFFSIZE];
unsigned char ser1_out_buf[BUFFSIZE];
char baud = 9;
extern COM ser1_com;
COM* c1 = &ser1_com;

char aRXBuffer[BUFFSIZE];
char aTXBuffer[BUFFSIZE];
//char RXBuffer[75];
//char TXBuffer[75];
int aTXBpos = 0;
int aRXBpos = 0;
newBool transmit = FALSE;
newBool recieve = FALSE;

// PWD Variables
int PwdTimer = 0;
// Initialized to run 50% of the time
int PwdOffTime = 100;
int PwdPeriod = 200;

// Parse Variables
char ParseBufferRX;
char ParseBufferTX[150];
char frameTextBuffer[20];
newBool transmitMsg = FALSE;
newBool recievedMsg = FALSE;
char itemDirection[3];
newBool transmitParsed = FALSE;


// Command Variables
char commandBuffer;
newBool dataLogging = FALSE;
newBool mCommand = FALSE;
newBool aCommand = FALSE;
newBool initialize = FALSE;

// Stinger Launcher Variables
newBool missilesFired = FALSE;
int missile = 0;


// Temps
int routCount = 0;
int serCount = 0;
int leftCount = 0;
int rightCount = 0;
int fwdCount = 0;
int readCount = 0;
int parseCount = 0;
int commandCount = 0;


// Declare Task Data Structures
TaskDataDir LeftTaskData;
TaskDataDir RightTaskData;
TaskDataDir FwdTaskData;
TaskDataRout RoutingTaskData;
TaskDataRead ReaderTaskData;
TaskDataWarn IdTaskData;
TaskDataJam JamTaskData;
TaskDataWarn SizeTaskData;
TaskDataSerCom SerialTaskData;
TaskDataInterval IntervalTaskData;
TaskDataFrame FrameTaskData;
TaskDataParse ParseTaskData;
TaskDataCommand CommandTaskData;
TaskDataMissile MissileTaskData;

// Prototypes of functions in the program
void far ReaderTask(void* data);
void far LeftTask(void* data);
void far FwdTask(void* data);
void far RightTask(void* data);
void far RoutingTask(void* data);
void far SerialTask(void* data);
void far IntervalTask(void* data);
void far StartUpTask();
void far ParseTask(void*);
void far CommandTask(void*);
void far MissileLauncher(void*);
// Aux Tasks
int randomInteger(int low, int high);
// Warning Tasks
void jamWarning(void* data);
void idWarning(void* data);
void sizeWarning(void* data);
// ISRs
void interrupt far jamAq_ISR(void);
void interrupt far Timer0_ISR(void);
void interrupt far Timer1_ISR(void);
void interrupt far Timer2_ISR(void);
void interrupt far IncreaseConv_ISR(void);
void interrupt far DecreaseConv_ISR(void);
void interrupt far Missile_ISR(void);


void main(void)
{
	// Local Variables
//	unsigned char err;

	// Initialize Data structures to Global Variables
	LeftTaskData.DirectionPtr = &left;
	LeftTaskData.itemPresentPtr = &itemPresent;
	LeftTaskData.errorPtr = &error;
	LeftTaskData.delayTimePtr = &delayTime;
	LeftTaskData.systemReadyPtr = &systemReady;
   LeftTaskData.cPtr = &c1;
   LeftTaskData.jamPtr = &jamLeft;

	RightTaskData.DirectionPtr = &right;
	RightTaskData.itemPresentPtr = &itemPresent;
	RightTaskData.errorPtr = &error;
	RightTaskData.delayTimePtr = &delayTime;
	RightTaskData.systemReadyPtr = &systemReady;
   RightTaskData.cPtr = &c1;
   RightTaskData.jamPtr = &jamRight;

	FwdTaskData.DirectionPtr = &fwd;
	FwdTaskData.itemPresentPtr = &itemPresent;
	FwdTaskData.errorPtr = &error;
	FwdTaskData.delayTimePtr = &delayTime;
	FwdTaskData.systemReadyPtr = &systemReady;
   FwdTaskData.cPtr = &c1;
   FwdTaskData.jamPtr = &jamFwd;

	RoutingTaskData.FwdPtr = &fwd;
	RoutingTaskData.itemIDPtr = itemID;
	RoutingTaskData.itemSizePtr = &itemSize;
	RoutingTaskData.LeftPtr = &left;
	RoutingTaskData.RightPtr = &right;
	RoutingTaskData.itemPresentPtr = &itemPresent;
	RoutingTaskData.errorPtr = &error;
	RoutingTaskData.displayTimePtr = &displaytime;
	RoutingTaskData.delayTimePtr = &delayTime;
	RoutingTaskData.jamRightPtr = &jamRight;
   RoutingTaskData.jamLeftPtr = &jamLeft;
   RoutingTaskData.jamFwdPtr = &jamFwd;
	RoutingTaskData.idStatePtr = &idState;
	RoutingTaskData.sizeStatePtr = &sizeState;
	RoutingTaskData.JamDataPtr = &JamTaskData;
	RoutingTaskData.IdDataPtr = &IdTaskData;
	RoutingTaskData.inUsePtr = &inUse;
	RoutingTaskData.SizeDataPtr = &SizeTaskData;
	RoutingTaskData.sizeErrorPtr = &sizeError;
	RoutingTaskData.idErrorPtr = &idError;
	RoutingTaskData.jamPresentPtr = &jamPresent;
   RoutingTaskData.transmitPtr = &transmit;
   RoutingTaskData.aTXBufferPtr = aTXBuffer;
   RoutingTaskData.aTXBposPtr = &aTXBpos;
	RoutingTaskData.cPtr = &c1;
	RoutingTaskData.ParseTaskDataPtr = &ParseTaskData;
	RoutingTaskData.Task7StkPtr = Task7_Stk;
	RoutingTaskData.linePtr = line;
   RoutingTaskData.aCommandPtr = &aCommand;
	RoutingTaskData.mCommandPtr = &mCommand;
   RoutingTaskData.itemDirectionPtr = itemDirection;
   RoutingTaskData.dataLogPtr = &dataLogging;
   RoutingTaskData.frameTextPtr = frameTextBuffer;
	
	ReaderTaskData.itemIDPtr = itemID;
	ReaderTaskData.itemSizePtr = &itemSize;
	ReaderTaskData.LeftPtr = &left;
   ReaderTaskData.FwdPtr = &fwd;
	ReaderTaskData.RightPtr = &right;
	ReaderTaskData.itemPresentPtr = &itemPresent;
	ReaderTaskData.jamStatePtr = &jamState;
	ReaderTaskData.errorPtr = &error;
	ReaderTaskData.delayTimePtr = &delayTime;
	ReaderTaskData.systemReadyPtr = &systemReady;
   ReaderTaskData.cPtr = &c1;

	JamTaskData.keypadInputPtr = &keypadInput;
	JamTaskData.errorPtr = &jamPresent;
   JamTaskData.jamLeftPtr = &jamLeft;
   JamTaskData.jamRightPtr = &jamRight;
   JamTaskData.jamFwdPtr = &jamFwd;
	JamTaskData.itemPresentPtr = &itemPresent;
	JamTaskData.errorStatePtr = &jamState;
	JamTaskData.delayTimePtr = &delayTime;
	JamTaskData.warnTimePtr = &delayTime;
	JamTaskData.buzzerStatePtr = &buzzerState;
	JamTaskData.inUsePtr = &inUse;
   JamTaskData.missilesPtr = &missile;
   JamTaskData.missilesFiredPtr = &missilesFired;

	IdTaskData.keypadInputPtr = &keypadInput;
	IdTaskData.errorPtr = &idError;
	IdTaskData.itemPresentPtr = &itemPresent;
	IdTaskData.errorStatePtr = &idState;
	IdTaskData.delayTimePtr = &delayTime;
	IdTaskData.warnTimePtr = &delayTime;
	IdTaskData.inUsePtr = &inUse;

	SizeTaskData.keypadInputPtr = &keypadInput;
	SizeTaskData.errorPtr = &sizeError;
	SizeTaskData.itemPresentPtr = &itemPresent;
	SizeTaskData.errorStatePtr = &sizeState;
	SizeTaskData.delayTimePtr = &delayTime;
	SizeTaskData.warnTimePtr = &delayTime;
	SizeTaskData.inUsePtr = &inUse;

   SerialTaskData.aTXBufferPtr = aTXBuffer;
   SerialTaskData.aRXBufferPtr = &ParseBufferRX;
   SerialTaskData.aTXBposPtr = &aTXBpos;
   SerialTaskData.aRXBposPtr = &aRXBpos;
   SerialTaskData.transmitPtr = &transmit;
   SerialTaskData.recievePtr = &recieve;
	// Status Variables
	SerialTaskData.jamPresentPtr = &jamPresent;
	SerialTaskData.idErrorPtr = &idError;
   SerialTaskData.sizeErrorPtr = &sizeError;
	SerialTaskData.cPtr = &c1;
   SerialTaskData.ParseTaskDataPtr = &ParseTaskData;
   SerialTaskData.Task7StkPtr = Task7_Stk;
   SerialTaskData.transmitParsedPtr = &transmitParsed;
   SerialTaskData.initialPtr = &initialize;

   CommandTaskData.CommandBufferPtr = &commandBuffer;
   CommandTaskData.dataLoggingPtr = &dataLogging;
   CommandTaskData.mCommandPtr = &mCommand;
   CommandTaskData.aCommandPtr = &aCommand;
   CommandTaskData.frameTextPtr = frameTextBuffer;
   CommandTaskData.FrameTaskDataPtr = &FrameTaskData;
   CommandTaskData.cPtr = &c1;
   CommandTaskData.transmitPtr = &transmit;
   CommandTaskData.initialPtr = &initialize;
	CommandTaskData.task1StkPtr = Task1_Stk;
	CommandTaskData.ReaderTaskDataPtr = &ReaderTaskData;
	CommandTaskData.serInBufPtr = ser1_in_buf;
	CommandTaskData.serOutBufPtr = ser1_out_buf;
	
   ParseTaskData.frameTextPtr = frameTextBuffer;
   ParseTaskData.itemDirectionPtr = itemDirection;
   ParseTaskData.itemSizePtr = &itemSize;
   ParseTaskData.jamPresentPtr = &jamPresent;
   ParseTaskData.recievedMsgPtr = &recieve;
   ParseTaskData.transmitPtr = &transmit;
   ParseTaskData.transmitParsedPtr = &transmitParsed;
   ParseTaskData.commandPtr = &ParseBufferRX;
   ParseTaskData.commandBufferPtr = &commandBuffer;
   ParseTaskData.mCommandPtr = &mCommand;
   ParseTaskData.aCommandPtr = &aCommand;
   ParseTaskData.itemIdentificationPtr = itemID;
   ParseTaskData.linePtr = line;
   ParseTaskData.idErrorPtr = &idError;
   ParseTaskData.ParseBufferTXPtr = ParseBufferTX;
   ParseTaskData.frameDataPtr = &FrameTaskData;

   MissileTaskData.missilePtr = &missile;
   MissileTaskData.frameTextPtr = frameTextBuffer;
   MissileTaskData.missilesFiredPtr = &missilesFired;

   FrameTaskData.aTXBufferPtr = aTXBuffer;
   FrameTaskData.textPtr = frameTextBuffer;

	// Initializing the TD40 board
	OSInit();
	ae_init();
	lcd_init();
	pio_init(18,0);
	s1_init(baud, ser1_in_buf, BUFFSIZE, ser1_out_buf, BUFFSIZE, c1);

	int4_init(1,jamAq_ISR);
   int6_init(1,Missile_ISR);
   int3_init(1,IncreaseConv_ISR);
   int1_init(1,DecreaseConv_ISR);

	setvect(uCOS, (void interrupt (*)(void))OSCtxSw);

	outportb(0x0200,OFF);
	outportb(0x0201,OFF);
	outportb(0x0202,OFF);

	OSTaskCreate(StartUpTask, (void*)0,(void*)&StartUp_Stk[STACK_SIZE-1],STARTUP_Priority);
   
	OSStart();
	return;
}
