#include "header.h"
//Delay Program
void pll_init(void)                  
{
    PLL0CON=0x01;
    PLL0CFG=0x24;
    PLL0FEED=0xaa;
    PLL0FEED=0x55;
    while(!(PLL0STAT&(1<<10)));
    PLL0CON=0x03;
    PLL0FEED=0xaa;
    PLL0FEED=0x55;
    VPBDIV=0x01;
}
//Initializing the LCD
void lcd_init(){
	lcd_cmd(0x38); //Enable both rows of LCD (5x7)
	lcd_cmd(0x0C); //Display ON cursor OFF
	lcd_cmd(0x06); //Entry Mode
	lcd_cmd(0x01); //Clear Display
	lcd_cmd(0x80); //First row of LCD (80-8F)
}
//LCD Command Mode
void lcd_cmd(unsigned char a){
	IOPIN1=0;
	IOPIN1|=(a<<16);
	IOCLR1|= bit(25); //RS = 0 (P 0.8)
	IOCLR1|= bit(26); //RW = 0 (P 0.9)
	IOSET1|= bit(27); //En = 1 (P 0.10)
	delay_ms(2);
	IOCLR1|=bit(27); //En = 0
}
//LCD Data mode
void lcd_data(unsigned char b){
	IOPIN1=0;
	IOPIN1|=(b<<16);
	IOSET1|= bit(25); //RS = 1 (P 0.8)
	IOCLR1|= bit(26); //RW = 0 (P 0.9)
	IOSET1|= bit(27); //En = 1 (P 0.10)
	delay_ms(2);
	IOCLR1|=bit(27); //En = 0
}
void ser_init(){
	PINSEL0=0x05; //Make PINSEL0 to 5 for UART operation
	U0LCR=0x83; // 8-bit character , 1-stop bit and disable parity bit and set DLAB bit to 1
	U0DLL=135; //9600 Baud rate with 60Mhz frequency
	U0DLM=1;
	U0LCR=0x03; // Make the DLAB bit to 0 in-order to read
}
int rx(){
	unsigned int b;
	while((U0LSR&(1<<0))==0); //Left-shift till the 0th bit becomes 0
	b=U0RBR;
	return b;
}
void delay_ms(unsigned int ms)
{
    T0CTCR=0x0;                                 
    T0TCR=0x00;                
    T0PR=59999;                 
    T0TCR=0x01;                
    while(T0TC<ms);           
    T0TCR=0x00;                 
    T0TC=0;   
}
void String(char* s){ 
	while(*s!='\0'){ 
		lcd_data(*s++);
	}
}
