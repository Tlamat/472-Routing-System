//----------------------------------------------------------------------------
// AUTHORS:   Eric Lund and Jean Tenca
// CREATED:   July 16, 2008
// MODIFIED:  July 16, 2008
// PROJECT:   EE 471 Lab #2
// MODULE:    Structs
//
// Abstract:  This file defines all the structs we used from the project.
//	      Different structs were used based on the needed application and
//	      data fields.
//----------------------------------------------------------------------------

struct MyStruct
{
	void far (*taskPtr)(void* taskDataPtr);
	void* taskDataPtr;
   void* stackPtr;
   unsigned short priority;
	struct MyStruct* prev;
	struct MyStruct* next;
};
typedef struct MyStruct TCB;

// Used for Directional TCBs
typedef struct
{
	newBool* DirectionPtr;
	newBool* itemPresentPtr;
	newBool* errorPtr;
	int* delayTimePtr;
   newBool* systemReadyPtr;
   COM** cPtr;
   newBool* jamPtr;
} TaskDataDir;

typedef struct
{
	char* aTXBufferPtr;
   char* textPtr;
} TaskDataFrame;

// Used for Warning TCBs
typedef struct
{
	char* keypadInputPtr;
   newBool* errorPtr;
   newBool* itemPresentPtr;
	newBool* inUsePtr;
   int* errorStatePtr;
   int* delayTimePtr;
   int* warnTimePtr;
   int* buzzerStatePtr;
} TaskDataWarn;

typedef struct
{
	char* keypadInputPtr;
   newBool* errorPtr;
   newBool* itemPresentPtr;
	newBool* inUsePtr;
   int* errorStatePtr;
   int* delayTimePtr;
   int* warnTimePtr;
   int* buzzerStatePtr;
   newBool* jamRightPtr;
	newBool* jamLeftPtr;
   newBool* jamFwdPtr;
   newBool* missilesFiredPtr;
   int* missilesPtr;
} TaskDataJam;

typedef struct
{
	char* frameTextPtr;
   char* itemDirectionPtr;
   unsigned int* itemSizePtr;
   newBool* jamPresentPtr;
	newBool* recievedMsgPtr;
   newBool* transmitPtr;
	char* commandPtr;
   char* commandBufferPtr;
   newBool* mCommandPtr;
   newBool* aCommandPtr;
   char* itemIdentificationPtr;
   char* linePtr;
   newBool* idErrorPtr;
   char* ParseBufferTXPtr;
   TaskDataFrame* frameDataPtr;
   newBool* transmitParsedPtr;
} TaskDataParse;

// Used for Serical Communications TCB
typedef struct
{
	COM** cPtr;
	newBool* jamPresentPtr;
	newBool* idErrorPtr;
	newBool* sizeErrorPtr;
	char* aTXBufferPtr;
	char* aRXBufferPtr;
	int* aTXBposPtr;
	int* aRXBposPtr;
	newBool* transmitPtr;
	newBool* recievePtr;
   TaskDataParse* ParseTaskDataPtr;
	unsigned int* Task7StkPtr;
   newBool* transmitParsedPtr;
   newBool* initialPtr;
} TaskDataSerCom;

// Used for Routing TCB
typedef struct
{
	newBool* LeftPtr;
	newBool* RightPtr;
	newBool* FwdPtr;
	newBool* itemPresentPtr;
	char* itemIDPtr;
   char* itemDirectionPtr;
	unsigned int* itemSizePtr;
	// Status Variables
  	newBool* errorPtr;
	newBool* inUsePtr;
	// Timer Variables
  	int* displayTimePtr;
	int* delayTimePtr;
	//newBool* systemReadyPtr;
	// Warning Information
  	int* jamStatePtr;
  	int* idStatePtr;
	int* sizeStatePtr;
	// Warning DataStructs
  	TaskDataJam* JamDataPtr;
  	TaskDataWarn* IdDataPtr;
	TaskDataWarn* SizeDataPtr;
	// Serial Communications Information
	newBool* sizeErrorPtr;
	newBool* idErrorPtr;
	newBool* jamPresentPtr;
	newBool* jamRightPtr;
   newBool* jamLeftPtr;
   newBool* jamFwdPtr;
	newBool* transmitPtr;
	char* aTXBufferPtr;
	int* aTXBposPtr;
	int* s0Ptr;
	int* s1Ptr;
	COM** cPtr;
	TaskDataParse* ParseTaskDataPtr;
	unsigned int* Task7StkPtr;
	char* linePtr;
   newBool* aCommandPtr;
   newBool* mCommandPtr;
   newBool* dataLogPtr;
   char* frameTextPtr;
} TaskDataRout;

// Used for Reading TCB
typedef struct
{
	newBool* LeftPtr;
	newBool* RightPtr;
	newBool* FwdPtr;
	newBool* itemPresentPtr;
   int* jamStatePtr;
	int* delayTimePtr;
	char* itemIDPtr;
	unsigned int* itemSizePtr;
  	newBool* errorPtr;
   newBool* systemReadyPtr;
   COM** cPtr;
} TaskDataRead;

typedef struct
{
	int* ivBufferPtr;
   int* ivPlacePtr;
   newBool* dispIntervalPtr;
   COM** cPtr;
} TaskDataInterval;

typedef struct
{
	char* CommandBufferPtr;
   newBool* dataLoggingPtr;
   newBool* mCommandPtr;
   newBool* aCommandPtr;
   TaskDataFrame* FrameTaskDataPtr;
   char* frameTextPtr;
   COM** cPtr;
   newBool* transmitPtr;
   newBool* initialPtr;
   commandCount;
	unsigned int* task1StkPtr;
	TaskDataRead* ReaderTaskDataPtr;
	char* serInBufPtr;
	char* serOutBufPtr;
} TaskDataCommand;

typedef struct
{
	int* missilePtr;
   char* frameTextPtr;
   newBool* missilesFiredPtr;
} TaskDataMissile;
