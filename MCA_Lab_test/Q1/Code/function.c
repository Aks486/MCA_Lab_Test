#include "header.h"
//Initializing
void pll(){    //Fosc = 12 Mhz
	PLL0CON = 0x01; //Make Enable = 1
	PLL0CFG = 0x24; //Msel = 5 and Psel = 2
	PLL0FEED = 0xAA; //Feed the sequence
	PLL0FEED = 0x55;
	while((PLL0STAT&(1<<10))!=0);
	PLL0CON = 0x03; //Make Enable = 1 and Connect = 1
	PLL0FEED = 0xAA; //Feed the sequence again
	PLL0FEED = 0x55;
	VPBDIV = 0x01; // Pclk = Cclk
}
//Delay function used to generate 50ms delay
void delay_ms(unsigned int a){
	T0CTCR = 0x00; //Set to Timer mode
	T0TCR = 0x00; //Timer OFF
	T0PR = 2999999; //For 50ms delay
	T0TCR=0x02; //Reset the timer
	T0TCR=0x01; //Timer ON
	while(T0TC<a);
	T0TCR=0x00 ;//Timer OFF
	T0TC=0;  //Make the Timer counter as 0
}
//PinWrite function to write to a particular pin
void pinWrite(int pinNr,int pinValue){
	if(pinNr<100){ //Set to Port0
		IODIR0|=(1<<pinNr); //Set the Direction to Output
		if(pinValue==0){ //Check the pin value
			IOCLR0|=(1<<pinNr); //Clear the pin
		}else{
			IOSET0|=(1<<pinNr); //Set the pin 
		}
	}
}

