/*Implement a system that controls a door. This system has two buttons A and B connected to pins P0.0 and P0.1. The door unlocks if the user:
Presses A exactly 4 times and then, presses B once.
The door is unlocked by sending the value 0 to pin P1.7. If the door is unlocked, it will lock when any button is pressed.
*/


__bit aberta=0; //global
unsigned char cnt=0; //global

//(...)

void isrE1 (void) __interrupt(2) 
{
	if(aberta) //if unlocked, it'll lock
	{
		aberta=0;
		P1_0=1;
	}
	cnt++;            

	for (aux=0;aux<5000;aux++) 
	if(P0_1==0)	//assumes P2_1 is conected to INT1
		aux=0;
	IE1=0;
}

void isrINT0(void) __interrupt(0)
{
	if (cnt==4) //if button A was already been pressed 4 times and B once
	{
        		aberta=1;
        		P1_0=0;	//unlocks the door
	}
	else
		if(aberta) //if unlocked, it'll lock
		{
			aberta=0;
			P1_0=1;
		}
	
	cnt=0;
	for (aux=0;aux<5000;aux++) 
		if(P0_0==0)	//assumes P2_0 is conected to INT0
			aux=0;
	IE0=0;
}

void ConfigBoard(void)
{
	P2MDOUT	= 0x0C;
	P0SKIP	= 0xFF;
	P1SKIP	= 0xFF;
	XBR1	= 0x70;
	OSCICN	= 0x83;
	PCA0MD	&= 0xBF;
	PCA0MD	= 0x00;
}