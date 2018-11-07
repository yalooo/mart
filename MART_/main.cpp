#include "myDef.h"


unsigned tcount=0,sec=0,min=0,hour=8;
ISR(TIMER0_OVF_vect)
{
	TCNT0=6;
	tcount++;
	if(tcount >=1000)
	{
		sec++;
		tcount =0;
	}
	if(sec==60)
	{
		min++;
		sec=0;
	}
	if(min==60)
	{
		hour++;
		min=0;
	}
}

int main(void)
{
	lcd_init();
	DDRD=0x0f;
	PORTD=0xff;
	DDRA=0xff;
	PORTA=0b11100000;
	
	TIMSK = 0b00000001;
	TCCR0 = 0b00000100;
	TCNT0 = 0b00000000;
	sei();

	int inputKey=0;
	char str[16] = {0,};
	
	
	int power = 0;
	int mode=0;
	int flag=0;
	int a = 0;
	int y=0;
	long long int x=0;
	long long int b = 0;
	long long int finish=0;
	
	long long int result=0;
	
	while (1)
	{
		inputKey=getKey();
		
		if(power == 0)
		{
			lcd_putsf(0,0,(unsigned char*)"     MARKET     ");
			lcd_putsf(0,1,(unsigned char*)"     SYSTEM     ");
			_delay_ms(500);
			lcd_putsf(0,0,(unsigned char*)"                ");
			lcd_putsf(0,1,(unsigned char*)"                ");
			_delay_ms(500);
			lcd_putsf(0,0,(unsigned char*)"     MARKET     ");
			lcd_putsf(0,1,(unsigned char*)"     SYSTEM     ");
			_delay_ms(500);
			lcd_putsf(0,0,(unsigned char*)"                ");
			lcd_putsf(0,1,(unsigned char*)"                ");
			_delay_ms(500);
			
			power = 1;
		}
		if(mode ==basic)
		{
			sprintf(str,"    %02d:%02d:%02d    ",hour,min,sec);
			lcd_putsf(0,0,(unsigned char*)"    WELCOME!!   ");
			lcd_putsf(0,1,(unsigned char*)str);
		}
		if(inputKey==Menu && flag==0)
		{
			mode=menu;
			flag=1;						
		}
		
		if(mode ==menu)
		{
			lcd_putsf(0,0,(unsigned char*)"1: Calculation  ");
			lcd_putsf(0,1,(unsigned char*)"2: Total Sales  ");
		}
		
		if(inputKey == sw1 && flag == 0 && mode==menu)
		{
			mode = cal;
			lcd_putsf(0,1,(unsigned char*)"                ");
			flag = 1;
			b=0;
			result=0;
			x=0;
			
		}
		if(inputKey == sw2 && flag == 0 && mode==menu)
		{
			mode = sales;
			lcd_putsf(0,1,(unsigned char*)"                ");
			flag = 1;		
			
		}
		
		
		if(mode ==cal)
		{
			PORTA=0b11011111;
			lcd_putsf(0,0,(unsigned char*)"Calculate Mode  ");
			sprintf(str,"%ld",b);
			lcd_putsf(0,1,(unsigned char*)str);
			
			if(inputKey==sw1 && flag==0)  {a=1; b=(b*10)+a; flag=1;}
			if(inputKey==sw2 && flag==0)  {a=2; b=(b*10)+a; flag=1;}
			if(inputKey==sw3 && flag==0)  {a=3; b=(b*10)+a; flag=1;}
			if(inputKey==sw5 && flag==0)  {a=4; b=(b*10)+a; flag=1;}
			if(inputKey==sw6 && flag==0)  {a=5; b=(b*10)+a; flag=1;}
			if(inputKey==sw7 && flag==0)  {a=6; b=(b*10)+a; flag=1;}
			if(inputKey==sw9 && flag==0)  {a=7; b=(b*10)+a; flag=1;}
			if(inputKey==sw10 && flag==0) {a=8; b=(b*10)+a; flag=1;}
			if(inputKey==sw11 && flag==0) {a=9; b=(b*10)+a; flag=1;}
			if(inputKey==sw13 && flag==0) {a=0; b=(b*10); flag=1;}
			if(inputKey==plus && flag ==0)
			{
				if(b>200000)
				{
					lcd_putsf(0,1,(unsigned char*)"     ERROR!     ");
					_delay_ms(500);
					lcd_putsf(0,1,(unsigned char*)"                ");
					_delay_ms(500);
					lcd_putsf(0,1,(unsigned char*)"     ERROR!     ");
					_delay_ms(500);
					lcd_putsf(0,1,(unsigned char*)"                ");
					_delay_ms(500);
					lcd_putsf(0,1,(unsigned char*)"     ERROR!     ");
					_delay_ms(500);
					lcd_putsf(0,1,(unsigned char*)"                ");
					_delay_ms(500);
					mode=basic;
					b=0;
				}
				result=result+b; flag=1; b=0;
				lcd_putsf(0,1,(unsigned char*)"             ");
			}
			if(inputKey==Enter && flag ==0)
			{
				b=b+result; flag=1; 
				finish =finish +b;
			}
			if(inputKey==change && flag==0)
			{
				mode=Change;
				lcd_putsf(0,1,(unsigned char*)"                ");
			}
								
			if(inputKey ==Enter )
			{
				if(b>200000)
				{
					lcd_putsf(0,1,(unsigned char*)"     ERROR!     ");
					_delay_ms(500);
					lcd_putsf(0,1,(unsigned char*)"                ");
					_delay_ms(500);
					lcd_putsf(0,1,(unsigned char*)"     ERROR!     ");
					_delay_ms(500);
					lcd_putsf(0,1,(unsigned char*)"                ");
					_delay_ms(500);
					lcd_putsf(0,1,(unsigned char*)"     ERROR!     ");
					_delay_ms(500);
					lcd_putsf(0,1,(unsigned char*)"                ");
					_delay_ms(500);
					mode=0;
					b=0;
					result=0;
				}
			}						
		}
			if(mode==Change)
			{
				PORTA=0b10111111;
				lcd_putsf(0,0,(unsigned char*)"Changes Mode    ");
				sprintf(str,"%ld",x);
				lcd_putsf(0,1,(unsigned char*)str);
				
				if(inputKey==sw1 && flag==0)  {y=1; x=(x*10)+y; flag=1;}
				if(inputKey==sw2 && flag==0)  {y=2; x=(x*10)+y; flag=1;}
				if(inputKey==sw3 && flag==0)  {y=3; x=(x*10)+y; flag=1;}
				if(inputKey==sw5 && flag==0)  {y=4; x=(x*10)+y; flag=1;}
				if(inputKey==sw6 && flag==0)  {y=5; x=(x*10)+y; flag=1;}
				if(inputKey==sw7 && flag==0)  {y=6; x=(x*10)+y; flag=1;}
				if(inputKey==sw9 && flag==0)  {y=7; x=(x*10)+y; flag=1;}
				if(inputKey==sw10 && flag==0) {y=8; x=(x*10)+y; flag=1;}
				if(inputKey==sw11 && flag==0) {y=9; x=(x*10)+y; flag=1;}
				if(inputKey==sw13 && flag==0) {y=0; x=(x*10); flag=1;}
					
				if(inputKey==Enter && flag==0)
				{
					flag=1;				
					if(x > b)
					{
						x= x-b;
						lcd_putsf(0,1,(unsigned char*)"                "); 
						
					}
					else
					{
						lcd_putsf(0,1,(unsigned char*)"                "); 
						x=0;
					}
				}
				
			}
			  if(mode == sales)
			  {
				  PORTA=0b01111111;
				  lcd_putsf(0,0,(unsigned char *)"Total Sales     ");
				  sprintf(str,"%ld",finish);
				  lcd_putsf(0,1,(unsigned char *)str);
			  }
		
		if(inputKey == 0 && flag == 1) flag = 0;
		
	}
}

