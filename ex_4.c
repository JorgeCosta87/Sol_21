/*Exercise 4. Implement Exercise 1 on the board, making sure that the buttons are properly debounced. Test it again.*/


#include <C8051F340.h>

#define led P1_0

void ConfigBoard(void);
void Configs(void);

unsigned char nA=0, nB=0;

void main(void){
	ConfigBoard();
	Configs();
	while(1)
	{
		
		if(nA==nB)
			led=0; //turns on with 0V
		else
			led=1; //turns off
	}
}

void Configs(void){
	IT0=1; //edge sensing
	IT1=1; //edge sensing
	IT01CF=0b00000000; //IN1PL=0 pois queremos transiÃ§Ã£o descendente
	IE=0b10000101; //enables ext0 and ext1
   	IT01CF=0x10; //Ext0 em P0.0 e Ext1 em P0.1
    	IE= 0b10000101; //0x85;
}


void RSI_ButtonA(void) __interrupt(0) //external 0
{
	int aux;
	nA++;
	for (aux=0;aux<5000;aux++) 
	if(P0_0==0)	//assumes P2_0 is conected to INT0
		aux=0;
	IE0=0;
}

void RSI_ButtonB(void) __interrupt(2) //external 1
{
	int aux;
	nB++;
	for (aux=0;aux<5000;aux++) 
		if(P0_1==0)	//assumes P2_1 is conected to INT1
			aux=0;
	IE1=0;
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
