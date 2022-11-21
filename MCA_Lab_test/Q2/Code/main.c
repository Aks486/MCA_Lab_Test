#include "header.h"
int main(void){
	int i=0;	
	unsigned char c;
	pll_init();
	char string[16]; //Creating a Char array to store the string 
	IO1DIR=0XFFFFFFFF; //LCD connected to Port-1 
	ser_init(); //Initilaise the UART0
	lcd_init(); //Initilaise the LCD
	while(1){ 
		i=0; //Count that holds number of characters recieved
		c=rx(); //Recieve one character
		while(c!=13 && i<14){  //13 is ASCII value for "Enter",whenever enter is encountered loop stops  
				string[i++]=c;  
				c=rx();
			}
	  string[i]='\0'; //Make ith element the end of string
		lcd_cmd(0x01);  //Clear screen
		String("STRING RECIEVED:"); //string is used to print the whole string 
		lcd_cmd(0xC0); //Go to line 2 of lcd
		String(&string[0]); //Print the received String
		lcd_cmd(0x80); //Go to line 1
		delay_ms(2);
	}
	return 0;
}