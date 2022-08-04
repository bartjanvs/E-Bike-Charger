/*
 * Charger.c
 *
 * Created: 4-8-2022 16:20:47
 * Author : Bart-Jan
 */ 

#define F_CPU 2000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "analog.h"
#include "digital.h"
#include "serialE0.h"

void FlashLEDS(void)
{
	for ( int i = 0; i < 10; i++ )
	{
		SetChargingLED();
		Set15VLED();
		SetCurrentLED();
		_delay_ms(200);
		ClearChargingLED();
		Clear15VLED();
		ClearCurrentLED();
		_delay_ms(200);
	}
}

int main(void)
{
    
	InitAdc();
	InitIO();
	init_stream(F_CPU);
	
	sei();
	FlashLEDS();
	_delay_ms(1000);
	printf("Starting...\r\n");
	while (1) 
	{
    }
}

