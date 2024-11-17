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

void far MissleLauncher(void* data) {
	int i = 0;
	while(1) {
   	TaskDataMissile* MissileData = (TaskDataMissile*)data;

      for(i = 0;i<*(MissileData->missilePtr);i++) {
      	// fire a missile

         (MissileData->frameTextPtr) = "Missile Fired";
      }

      *(MissileData->missilesFiredPtr) = TRUE;
      OSTimeDly(5);
   }
}