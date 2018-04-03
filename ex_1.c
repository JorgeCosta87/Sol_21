/*Consider a system with two buttons A and B connected to pins P3.2 and P3.3. The system should light a LED connected to P1.0 if A and B have been pressed the same number of times since the system started running.
*/

#include <C8051F340.h>

#define led P1_0

void Configs(void);

unsigned char nA=0, nB=0;

void main(void){
	Configs();
	while(1)
		if(nA==nB)
			led=0; //turns on with 0V	
		else
			led=1; //turns off	
}

void Configs(void){
	IT0=1; //active low, edge sensing
	IT1=1;
	IE=0b10000101; //enables ext0 and ext1
}


void RSI_ButtonA(void) __interrupt(0) //external 0
{
	nA++;
}

void RSI_ButtonB(void) __interrupt(2) //external 1
{
	nB++;
}
