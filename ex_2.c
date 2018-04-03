/*Consider a system that controls an autonomous electric vehicle. The system has a forward proximity sensor that detects the presence of a near obstacle. This sensor inputs a signal at level 0 to pin 3.2 when an obstacle is near. For safety reasons, the system should brake (continuously) whenever such an obstacle is present. The brakes are controlled by pin P1.0 (0 - no brake, 1 -brake).  */

#include "8051.h"

//#include <C8051F340.h>

#define brake P1_0

void Configs(void);


void main(void){
	Configs();
	while(1)
		brake=0; //the rsi executes continously while P3.2 has 0V, sine we configure it by (low)level sensing
}

void Configs(void){
	IT0=0; //active low, level sensing
	IE=0b10000001; //enables ext0 and ext1
}



void RSI_Obstacle(void) __interrupt(0) //external 0
{
	brake=1; //the rsi executes continously while P3.2 (INT0 pin) has 0V, since we configure it by (low)level sensing
}
