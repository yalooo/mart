

#ifndef MYDEF_H_
#define MYDEF_H_

#define F_CPU 16000000
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

#define sw13 23
#define sw1 30
#define sw2 46
#define sw3 78
#define sw5 29
#define sw6 45
#define sw7 77
#define sw9 27
#define sw10 43
#define sw11 75
#define plus 142
#define Enter 141
#define Menu 139
#define change 71
#define lobby 135
#define basic 0
#define menu 1
#define cal 2
#define Change 3
#define sales 4

unsigned char getKey()
{
	unsigned char key = 0;
	for (int i=0; i<4; i++)
	{
		PORTD = ~(0x00 | (1 << i));
		_delay_ms(5);
		key = (~PIND & 0xf0);
		if (key) return (key | (PORTD & 0x0f));
	}
}



#endif 