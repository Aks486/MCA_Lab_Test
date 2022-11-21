#include <lpc214x.h>
#define bit(x) (1<<x)

void delay(void);
void lcd_init(void);
void pll_init(void);
void lcd_cmd(unsigned char );
void lcd_data(unsigned char );
void delay_ms(unsigned int );
void ser_init(void);
int rx(void);
void String(char* );

