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

extern int missile;

void far interrupt Missile_ISR(void) {
   
   missile++;

	// Issue EOI
   outport(0xFF22, 0x8000);
}