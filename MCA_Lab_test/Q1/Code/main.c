#include "header.h"

int main(void){
	int i;
	pll();
	while(1){
	for(i=0;i<4;i++){
		pinWrite(i,1); //Set value to pin (i=0,1,2,3) and write 1 to pin
		delay_ms(50); //Delay for 50ms
		pinWrite(i,0); //Clear the pin
		}
	}
	return 0;
}
